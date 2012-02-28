// UIEdit.cpp : Implementation of CUIEdit
#include "stdafx.h"
#include "UI.h"
#include "UIEdit.h"

#include "AutoListMembersWindow.h"

//////////////////////
// CEditUndoTyping

STDMETHODIMP CEditUndoTyping::Do(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager)
{
	ATLASSERT(m_pEdit);

	if (m_kind == 1 ||		// Any character
		m_kind == ' ' ||
		m_kind == '\t' || 
		m_kind == '\n' || 
		m_kind == VK_DELETE ||
		m_kind == VK_BACK)
	{
		if (m_bRedo)
		{
		// Reinsert the text
			m_pEdit->InsertText(m_startCharPos, m_text, m_len);
		//	m_pEdit->BuildRLineOffsets();
		//	m_pEdit->BuildLineOffsets();

		// Free the text
			SysFreeString(m_text);
			m_text = NULL;

			m_pEdit->LocateCursor(m_startCharPos + m_len);
		}
		else	// Undo
		{
		// Remember the text
			ATLASSERT(m_text == NULL);
			m_text = SysAllocStringLen(NULL, m_len);
			memcpy(m_text, &m_pEdit->GetTextData()[m_startCharPos], m_len*2);

		// Delete the text
			m_pEdit->DeleteText(m_startCharPos, m_len);
		//	m_pEdit->BuildRLineOffsets();
		//	m_pEdit->BuildLineOffsets();

			m_pEdit->LocateCursor(m_startCharPos);
		}
	}

//	m_pEdit->ResetHScrollSize();
//	m_pEdit->ResetVScrollSize();

	m_pEdit->InvalidateRect(NULL, TRUE);
	m_pEdit->UpdateWindow();

//	m_pEdit->OnChange();
	m_pEdit->OnMovedCursor();

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);

	return S_OK;
}

STDMETHODIMP CEditUndoTyping::GetDescription(/* [out] */ BSTR __RPC_FAR *pBstr)
{
	ATLASSERT(pBstr != NULL);
	if (pBstr == NULL) return E_POINTER;

	switch (m_kind)
	{
	case VK_DELETE:
	case VK_BACK:
		*pBstr = SysAllocString(L"Deleting");
		break;

	case '\n':
		*pBstr = SysAllocString(L"Line Break");
		break;

	default:
		*pBstr = SysAllocString(L"Typing");
	}

	return S_OK;
}

STDMETHODIMP CEditUndoTyping::GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID)
{
	*pClsid = CLSID_NULL;	// TODO here
	*plID = m_kind;
	return S_OK;
}

STDMETHODIMP CEditUndoTyping::OnNextAdd()
{
	m_pEdit->m_pRecentUndoTyping = NULL;
	return S_OK;
}

//////////////////////////////////
// CEditUndoParent

STDMETHODIMP CEditUndoParent::Add(/* [in] */ IOleUndoUnit __RPC_FAR *pUU)
{
	pUU->AddRef();

	if (m_state == 0)	// undo state
	{
		m_undoList.AddHead(pUU);
	}
	else if (m_state == 1)	// redo state
	{
		m_undoList.AddHead(pUU);
	}

	return S_OK;
}

STDMETHODIMP CEditUndoParent::GetParentState(/* [out] */ DWORD __RPC_FAR *pdwState)
{
	*pdwState = m_flags;
	return S_OK;
}

STDMETHODIMP CEditUndoParent::Do(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager)
{
	pUndoManager->Open(this);

	m_state = !m_state;

	UPOSITION pos = m_undoList.GetHeadPosition();
	while (pos)
	{
		UPOSITION pos2 = pos;
		IOleUndoUnit* pUU = (IOleUndoUnit*)m_undoList.GetNext(pos);

		pUU->Do(pUndoManager);
		m_undoList.RemoveAt(pos2);

		pUU->Release();
	}

	pUndoManager->Close(this, TRUE);

	return S_OK;
}

STDMETHODIMP CEditUndoParent::GetDescription(/* [out] */ BSTR __RPC_FAR *pBstr)
{
	*pBstr = SysAllocString(L"Typing");
	return S_OK;
}

STDMETHODIMP CEditUndoParent::Open(/* [in] */ IOleParentUndoUnit __RPC_FAR *pPUU)
{
	return S_OK;
}

STDMETHODIMP CEditUndoParent::Close(/* [in] */ IOleParentUndoUnit __RPC_FAR *pPUU, /* [in] */ BOOL fCommit)
{
	return S_OK;
}

STDMETHODIMP CEditUndoParent::GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID)
{
	return S_OK;
}

STDMETHODIMP CEditUndoParent::OnNextAdd(void)
{
	return S_OK;
}

STDMETHODIMP CEditUndoParent::FindUnit(/* [in] */ IOleUndoUnit __RPC_FAR *pUU)
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CUIEdit

CUIEdit::CUIEdit()
{
	m_bWindowOnly = TRUE;

//	m_hFont = NULL;

	m_pRecentUndoTyping = NULL;

	m_bMultiLine = FALSE;

	m_bWordWrap = VARIANT_FALSE;
	m_bLineNumbers = VARIANT_FALSE;

	m_bHorzSB = FALSE;
	m_bVertSB = FALSE;
	m_bLeftBar = FALSE;
	m_lborWidth = 0;
	m_border = 1;
	m_case = 0;

	m_line = 0;
	m_rline = 0;
	m_col = 0;
	m_rcol = 0;
	m_idealcolX = 0;
	m_offset = 0;

	m_bShowCursor = FALSE;

	m_selStart = 0;
	m_selEnd = -1;
	m_initSel = -1;

	m_bShowTabs = FALSE;
	m_bShowEOL = FALSE;
	m_bShowSpace = FALSE;
	m_tabSize = 3;

	m_dragging = 0;

	m_pAutoListMembersWindow = NULL;

	m_rlinesArr.SetSize(0, 100);
	m_linesArr.SetSize(0, 100);
}

CUIEdit::~CUIEdit()
{
}

int CUIEdit::FinalConstruct()
{
	HRESULT hr;

	m_horz.CoCreateInstance(CLSID_UIScrollBar);
	m_horz->put_direction(0);

	m_vert.CoCreateInstance(CLSID_UIScrollBar);
	m_vert->put_direction(1);

	ITextDataPtr tdp;
	hr = tdp.CreateInstance(CLSID_TextData);
	if (FAILED(hr)) return E_NOINTERFACE;

	put_textDocument(tdp);
	m_tdp->put_data(SysAllocString(L""));

	{
		// Selection
		{
			SyntaxElement style = {GetSysColor(COLOR_HIGHLIGHTTEXT), GetSysColor(COLOR_HIGHLIGHT) };
			m_styles.Add(style);
		}

		// Text
		{
			SyntaxElement style = {GetSysColor(COLOR_WINDOWTEXT), GetSysColor(COLOR_WINDOW) };
			m_styles.Add(style);
		}
	}

	return S_OK;
}

void CUIEdit::FinalRelease()
{
	ATLASSERT(m_hWnd == NULL);
	/*
	if (m_tdp)
	{
		IDispEventImpl<3, CUIEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_tdp);
	}
	*/
}

LRESULT CUIEdit::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	if (m_pAutoListMembersWindow)
	{
		m_pAutoListMembersWindow->DestroyWindow();
		m_pAutoListMembersWindow->Release();
		m_pAutoListMembersWindow = NULL;
	}

	if (!m_dragging)
	{
		SetFocus();

		CRect scrollRect = m_textArea;
		scrollRect.left = 0;

		if (scrollRect.PtInRect(point))
		{
			long scrollposX; m_horz->get_pos(&scrollposX);
			long scrollposY; m_vert->get_pos(&scrollposY);

			int line = ((point.y - m_textArea.top)/m_ch) + scrollposY;
			int col;

			if (line < 0) line = 0;
			else if (line > CountLines()-1) line = CountLines()-1;

			HideCursor();

			m_dragging = TRUE;
			SetCapture();

			if (point.x < m_textArea.left)
			{
				LineDef* pLine = m_linesArr[line];

				col = 0;
				line++;

				m_pRecentUndoTyping = NULL;	// Stop inserting changes into this undounit
				LocateCursor(line, col);

				if (!(nFlags & MK_SHIFT))
				{
					m_initSel = pLine->m_offset;
					m_selStart = m_initSel;
					m_selEnd = m_selStart + pLine->m_lineLength;
				}
			}
			else
			{
				point.x -= m_textArea.left;
				point.x += scrollposX;

				m_idealcolX = point.x;
				col = ColumnFromPointX(line, m_idealcolX);

				m_pRecentUndoTyping = NULL;	// Stop inserting changes into this undounit
				LocateCursor(line, col);

				if (nFlags & MK_CONTROL)
				{
					//	SelectWordAt(line, col);
				}

				if (!(nFlags & MK_SHIFT))
				{
					ClearSelectionAndInvalidate();

					m_initSel = m_offset;
					m_selStart = m_initSel;
					m_selEnd = m_initSel;
				}
			}

			ShowCursor();

			BOOL bHandled = TRUE;
			OnMouseMove(WM_MOUSEMOVE, wParam, lParam, bHandled);
		}
	}

	return 0;
}

LRESULT CUIEdit::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Fire_DblClick(m_offset, m_rline, m_rcol);
	return 0;
}

LRESULT CUIEdit::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	if (m_dragging)
	{
		long scrollposX; m_horz->get_pos(&scrollposX);
		long scrollposY; m_vert->get_pos(&scrollposY);

		int line = ((point.y - m_textArea.top)/m_ch) + scrollposY;
		//int vcol = ((point.x - m_textArea.left)/m_cw) + scrollposX;

		if (line < 0) line = 0;
		else if (line > CountLines()-1) line = CountLines()-1;

		m_idealcolX = point.x-m_textArea.left + scrollposX;
		int col = ColumnFromPointX(line, m_idealcolX);//VColumn2Column(line, vcol);

		if (TRUE || (line != m_line) || (col != m_col))
		{
			HideCursor();

			LocateCursor(line, col);

			SetSelectionAndInvalidate(m_initSel, m_offset);

			ScrollIntoView(m_line, m_col);

			ShowCursor();
		}
	}

	return 0;
}

LRESULT CUIEdit::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;

		if (m_selStart == m_selEnd)
		{
			m_initSel = -1; m_selStart = 0; m_selEnd = -1;
		}

		InvalidateRect(m_textArea, TRUE);
	}

	return 0;
}

void CUIEdit::ShowCursor()
{
	if (!m_bShowCursor)
	{
		ToggleCursor();
	}
}

void CUIEdit::HideCursor()
{
	if (m_bShowCursor)
	{
		ToggleCursor();
	}
}

void CUIEdit::ToggleCursor()
{
	m_bShowCursor = !m_bShowCursor;

	HDC hDC = GetDC();
	int state = SaveDC(hDC);
	IntersectClipRect(hDC, m_textArea.left, m_textArea.top, m_textArea.right, m_textArea.bottom);

	DrawCursor(hDC);

	RestoreDC(hDC, state);
	ReleaseDC(hDC);
}

void CUIEdit::DrawCursor(HDC hDC)
{
	POINT scrollPos;

	scrollPos.x = m_textArea.left;
	scrollPos.y = m_textArea.top;

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	scrollPos.x -= scrollposX;//*m_cw;
	scrollPos.y -= scrollposY*m_ch;

	POINT oldOrg;
	SetViewportOrgEx(hDC, scrollPos.x, scrollPos.y, &oldOrg);

	//int vcol = Column2VColumn(m_line, m_col);
	int colx = PointXFromColumn(m_line, m_col);

	CRect crect(colx, m_line*m_ch, 0, 0);
	crect.right = crect.left+3;
	crect.bottom = crect.top+m_ch+1;

	int oldr2 = SetROP2(hDC, R2_NOTXORPEN);
	HPEN pOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
	HBRUSH pOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

	Rectangle(hDC, crect.left, crect.top, crect.right, crect.bottom);

	SelectObject(hDC, pOldBrush);
	SelectObject(hDC, pOldPen);
	SetROP2(hDC, oldr2);

	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
}

void CUIEdit::CreateSyntaxFonts()
{
//	m_nFonts = 0;

//	int stylesArray[64] = {0};

	/*
	LOGFONT lf = {0};

	lf.lfWeight = 0; 
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = FALSE;

	lf.lfHeight = -10;
	lf.lfWidth = 0;
	lf.lfEscapement = 0; 
	lf.lfOrientation = 0; 
	lf.lfCharSet = 0; 
	lf.lfOutPrecision = 0; 
	lf.lfClipPrecision = 0; 
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = FF_DONTCARE; 
	lstrcpy(lf.lfFaceName, "Courier");

	m_hFont = CreateFontIndirect(&lf);
*/

	FONTDESC	fd;
	fd.cbSizeofstruct = sizeof(fd);
	fd.lpstrName = L"Courier";
	fd.cySize.Hi = -10;
	fd.cySize.Lo = 0;
	fd.sWeight = 0;
	fd.sCharset = 0;
	fd.fItalic = FALSE;
	fd.fUnderline = FALSE;
	fd.fStrikethrough = FALSE;

	HRESULT hr = OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&m_pFont);
	ATLASSERT(SUCCEEDED(hr));

	/*
	for (int i = 0; i < 16; i++)
	{
		int findex = -1;

		for (int j = 0; j < m_nFonts; j++)
		{
			if (stylesArray[i] == ElementArray[i].Style)
			{
				findex = j;
				break;
			}
		}

		if (findex >= 0)	// Font is already created
		{
			m_elementFont[i] = findex;
		}
		else
		{
			lf.lfWeight = 0; 
			lf.lfItalic = FALSE;
			lf.lfUnderline = FALSE;
			lf.lfStrikeOut = FALSE;

			if (ElementArray[i].Style & FSF_ITALIC) lf.lfItalic = TRUE;
			if (ElementArray[i].Style & FSF_UNDERLINE) lf.lfUnderline = TRUE;
			if (ElementArray[i].Style & FSF_BOLD) lf.lfWeight = FW_BOLD;

			m_elementFont[i] = m_nFonts;

			stylesArray[m_nFonts] = ElementArray[i].Style;
			m_fonts[m_nFonts] = CreateFontIndirect(&lf);

			m_nFonts++;
		}
	}
	*/
}

long CUIEdit::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	return 0;

	IDispEventImpl<1, CUIEdit, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	IDispEventImpl<2, CUIEdit, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	IUnknown* p;
	CRect rc(0,0,0,0);

	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);

	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

//	CreateSyntaxFonts();
	{
		FONTDESC	fd;
		fd.cbSizeofstruct = sizeof(fd);
		fd.lpstrName = L"Courier";
		fd.cySize.Hi = -10;
		fd.cySize.Lo = 0;
		fd.sWeight = 0;
		fd.sCharset = 0;
		fd.fItalic = FALSE;
		fd.fUnderline = FALSE;
		fd.fStrikethrough = FALSE;

		CComPtr<IFontDisp> font;
		HRESULT hr = OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&font);
		ATLASSERT(SUCCEEDED(hr));

		put_font(font);
	}

/*
	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HDC hDC = CreateCompatibleDC(NULL);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	SIZE size;
	GetTextExtentPoint32(hDC, " ", 1, &size);
	m_spaceWidth = size.cx;
	m_ch = size.cy;

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);
*/
	
	ClearFormatting();

	BuildRLineOffsets();
	BuildLineOffsets();

	if (m_tdp)
	{
		HRESULT hr = IDispEventImpl<3, CUIEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>::DispEventAdvise(m_tdp);
		ATLASSERT(SUCCEEDED(hr));
	}
	return 0;
}

long CUIEdit::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_tdp)
	{
		HRESULT hr = IDispEventImpl<3, CUIEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_tdp);
		ATLASSERT(SUCCEEDED(hr));
	}

	IDispEventImpl<1, CUIEdit, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<2, CUIEdit, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

long CUIEdit::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nIDEvent = wParam;
	switch (nIDEvent)
	{
	case 1:
		ToggleCursor();
		break;
	}

	return 0;
}

long CUIEdit::OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_pFont.Release();

	return DefWindowProc(uMsg, wParam, lParam);
}

int CUIEdit::PointXFromColumn(int line, int col)
{
	DWORD offset = m_linesArr[line]->m_offset;
	BSTR data = GetTextData();
	int linelen = m_linesArr[line]->m_lineLength;

	HDC hDC = CreateCompatibleDC(NULL);

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	int x = 0;

	int i = offset;

	int vcol = 0;

	for (int j = 0; j < col; j++)
	{
		char c = data[i++];

		if (c == '\t')
		{
			int spaces = m_tabSize - (vcol % m_tabSize);
			vcol += spaces;

			x += spaces*m_spaceWidth;
		}
		else
		{
			vcol++;

			SIZE size;
			GetTextExtentPoint32(hDC, &c, 1, &size);

			x += size.cx;
		}
	}

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	return x;
}

int CUIEdit::ColumnFromPointX(int line, int x)
{
	DWORD offset = m_linesArr[line]->m_offset;
	BSTR data = GetTextData();
	int linelen = m_linesArr[line]->m_lineLength;

	HDC hDC = CreateCompatibleDC(NULL);

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	int i = offset;

	int col = 0;
	int vcol = 0;

	while (x > 0)
	{
		TCHAR c = data[i++];

		//if (x <= 0) break;

		int width;

		if (c == '\t')
		{
			int spaces = m_tabSize - (vcol % m_tabSize);
			vcol += spaces;
			width = spaces*m_spaceWidth;
		}
		else
		{
			vcol++;

			SIZE size;
			GetTextExtentPoint32(hDC, &c, 1, &size);

			width = size.cx;
		}

		if (x <= width/2) break;

		x -= width;

		col++;
		if (col > linelen)
			break;
	}

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	return col;
}

void CUIEdit::MoveCursorPageUp()
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_line > scrollposY)	// Move to top of page
	{
		LocateCursor(scrollposY, m_col);
	}
	else	// Scroll up one page
	{
		int visibleLines = m_textArea.Height() / m_ch;

		LocateCursor(m_line - visibleLines, m_col);
	}
}

void CUIEdit::MoveCursorPageDown()
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	int visibleLines = m_textArea.Height() / m_ch;
	int bottomline = scrollposY+visibleLines-1;

	if (m_line < bottomline)	// Move to bottom of page
	{
		LocateCursor(bottomline, m_col);
	}
	else	// Scroll one page down
	{
		LocateCursor(m_line + visibleLines, m_col);
	}
}

void CUIEdit::MoveCursorLeft()
{
	if (m_offset > 0)
	{
		LocateCursor(m_offset-1);
		m_idealcolX = PointXFromColumn(m_line, m_col);

#if 0
		m_offset--;

		if (GetTextData()[m_offset] == '\n')
		{
			m_line--;
			m_col = 0;

			BSTR data = GetTextData();
			int len = m_offset-1;

			while (len >= 0 && data[len] != '\n')
			{
				m_col++;
				len--;
			}
		}
		else
		{
			m_col--;
		}

		m_dcol = m_col;
#endif
	}

	OnMovedCursor();
}

void CUIEdit::MoveCursorRight()
{
	if (m_offset < GetTextLen())
	{
		LocateCursor(m_offset+1);
		m_idealcolX = PointXFromColumn(m_line, m_col);

#if 0
		if (m_offset-m_linesArr[m_line]->m_offset == m_linesArr[m_line]->m_lineLength)
		{
			m_line++;
			m_col = 0;
		}
		else
		{
			m_col++;
		}

		/*
		if (GetTextData()[m_offset] == '\n')
		{
			m_line++;
			m_col = 0;
		}
		else
		{
			m_col++;
		}
		*/

		m_dcol = m_col;
		m_offset++;
#endif
	}

	OnMovedCursor();
}

void CUIEdit::MoveCursorDown()
{
	if (m_line < m_linesArr.GetSize()-1)
	{
		int col = ColumnFromPointX(m_line+1, m_idealcolX);
		LocateCursor(m_line+1, col);

		OnMovedCursor();
	}
}

void CUIEdit::MoveCursorUp()
{
	if (m_line > 0)
	{
		int col = ColumnFromPointX(m_line-1, m_idealcolX);
		LocateCursor(m_line-1, col);

		ATLTRACE("LINE:%d\n", m_line);

		OnMovedCursor();
	}
}

void CUIEdit::MoveCursorBegLine()
{
	LocateCursor(m_linesArr[m_line]->m_offset);//m_offset -= m_col;
	m_idealcolX = PointXFromColumn(m_line, m_col);

	OnMovedCursor();
}

void CUIEdit::MoveCursorEndLine()
{
	LocateCursor(m_linesArr[m_line]->m_offset + m_linesArr[m_line]->m_lineLength);//m_offset -= m_col;
	m_idealcolX = PointXFromColumn(m_line, m_col);

	/*
	int lineLength = m_linesArr[m_line]->m_lineLength;
	m_offset += lineLength - m_col;
	m_col = lineLength;
	*/

	OnMovedCursor();
}

void CUIEdit::InsertChar(WCHAR ch)
{
	ATLASSERT(ch < 256);
	InsertText(m_offset, &ch, 1);

	/*
	BuildRLineOffsets();
	BuildLineOffsets();
  */
}

void CUIEdit::DeleteChar(int offset, int len)
{
	DeleteText(offset, len);
/*
	BuildRLineOffsets();
	BuildLineOffsets();
	*/
}

int CUIEdit::GetMaxLineLength()
{
	HDC hDC = CreateCompatibleDC(NULL);

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	int nlines = m_linesArr.GetSize();
	LineDef** pLines = m_linesArr.GetData();

	int maxx = 0;

	for (int i = 0; i < nlines; i++)
	{
		BSTR data = GetTextData() + pLines[i]->m_offset;
		int len = pLines[i]->m_lineLengthR;
		int n = 0;

		int linemaxx = 0;

		for (int i = 0; i < len; i++)
		{
			TCHAR c = data[i];

			CSize size;

			if (c == '\t')
			{
				int spaces = m_tabSize - (n % m_tabSize);
				SIZE size2;
				GetTextExtentPoint32(hDC, " ", 1, &size2);

				size.cx = size2.cx*spaces;
				n += spaces;
			}
			else
			{
				GetTextExtentPoint32(hDC, &c, 1, &size);
				n++;
			}

			linemaxx += size.cx;
		}

		if (linemaxx > maxx)
			maxx = linemaxx;
	}

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	return maxx;
}

void CUIEdit::ResetHScrollSize()
{
	int maxx = GetMaxLineLength();
	m_horz->SetInfo(0, maxx, m_textArea.Width());
}

void CUIEdit::ResetVScrollSize()
{
	m_vert->SetInfo(
		0,
		m_linesArr.GetSize()-1,
		(m_textArea.Height())/m_ch);
}

void CUIEdit::ScrollIntoView(int line, int col)
{
	ATLASSERT(line < m_linesArr.GetSize());

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	int scrollX = 0;
	int scrollY = 0;

	int visibleLines = (m_textArea.Height())/m_ch;
	int visibleWidth = (m_textArea.Width());

	int colx = PointXFromColumn(line, col);

	if (line < scrollposY)
	{
		scrollY = line - scrollposY;	// scroll up
	}
	else if (line > scrollposY+visibleLines-1)	// scroll down
	{
		scrollY = line - (scrollposY+visibleLines-1);
	}

	if (colx < scrollposX)
	{
		int moreLeftX = 0;
		scrollX = colx - scrollposX - moreLeftX;
	}
	else if (colx > scrollposX+visibleWidth-1)
	{
		int moreRightX = 0;
		scrollX = colx - (scrollposX+visibleWidth)+1 + moreRightX;
	}

	if (scrollX || scrollY)
	{
	// Scroll text area
		ScrollWindow(-scrollX, -scrollY*m_ch, &m_textArea, &m_textArea);

		if (scrollY)	// Scroll left border
		{
			CRect lborder(0, m_textArea.top, m_textArea.left, m_textArea.bottom);
			ScrollWindow(-scrollX, -scrollY*m_ch, &lborder, &lborder);
		}

		m_vert->put_pos(scrollposY+scrollY);
		m_horz->put_pos(scrollposX+scrollX);
	}
}

long CUIEdit::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nKey = wParam;
	int lKeyData = lParam;

	HideCursor();

	LONG bShift = (GetAsyncKeyState(VK_SHIFT) & (1<<15));

	switch (nKey)
	{
		/*
	case VK_RETURN:
		{
		}
		break;
		*/

	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
	case VK_HOME:
	case VK_END:
	case VK_PRIOR:
	case VK_NEXT:
		{
			m_pRecentUndoTyping = NULL;	// Stop inserting changes into this undounit

			//if (bShift)
			{
				if (bShift)
				{
					if (m_initSel == -1)	// Starting new selection
					{
						m_initSel = m_offset;
					}
				}

				switch (nKey)
				{
				case VK_LEFT:
					{
						if (m_initSel == -1)
						{
							MoveCursorLeft();
						}
						else
						{
							LocateCursor(m_selStart);
							OnMovedCursor();
						}
						//MoveCursorLeft();

						if (m_pAutoListMembersWindow)
						{
							if (m_offset < m_autoListStartOffset)
							{
								m_pAutoListMembersWindow->DestroyWindow();
								m_pAutoListMembersWindow->Release();
								m_pAutoListMembersWindow = NULL;
							}
						}
					}
					break;

				case VK_RIGHT:
					{
						//						MoveCursorRight();
						if (m_initSel == -1)
						{
							MoveCursorRight();
						}
						else
						{
							LocateCursor(m_selEnd);
							OnMovedCursor();
						}

						if (m_pAutoListMembersWindow)
						{
							if (m_offset > m_autoListEndOffset)
							{
								m_pAutoListMembersWindow->DestroyWindow();
								m_pAutoListMembersWindow->Release();
								m_pAutoListMembersWindow = NULL;
							}
						}
					}
					break;

				case VK_UP:
					{
						if (m_pAutoListMembersWindow)
						{
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->GetCurSel()-1);
						}
						else
						{
							if (m_initSel > -1)
							{
								LocateCursor(m_selStart);
								OnMovedCursor();
							}
							MoveCursorUp();
						}
					}
					break;

				case VK_DOWN:
					{
						if (m_pAutoListMembersWindow)
						{
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->GetCurSel()+1);
						}
						else
						{
							if (m_initSel > -1)
							{
								LocateCursor(m_selEnd);
								OnMovedCursor();
							}
							MoveCursorDown();
						}
					}
					break;

				case VK_PRIOR:
					{
						if (m_pAutoListMembersWindow)
						{
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->GetCurSel()-(m_pAutoListMembersWindow->GetVisibleLines()-1));
						}
						else
						{
							MoveCursorPageUp();
						}
					}
					break;

				case VK_NEXT:
					{
						if (m_pAutoListMembersWindow)
						{
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->GetCurSel()+(m_pAutoListMembersWindow->GetVisibleLines()-1));
						}
						else
						{
							MoveCursorPageDown();
						}
					}
					break;

				case VK_HOME:	MoveCursorBegLine(); break;
				case VK_END:	MoveCursorEndLine(); break;
				}

				if (bShift)
					SetSelectionAndInvalidate(m_initSel, m_offset);
				else
					ClearSelectionAndInvalidate();
			}
#if 0
			else
			{
				switch (nKey)
				{
				case VK_LEFT:	if (m_initSel == -1)
										MoveCursorLeft();
									else
									{
										LocateCursor(m_selStart);
										OnMovedCursor();
									}
									 break;

				case VK_RIGHT:	if (m_initSel == -1)
										MoveCursorRight();
									else
									{
										LocateCursor(m_selEnd);
										OnMovedCursor();
									}
										break;

				case VK_UP:		if (m_initSel > -1)
									{
										LocateCursor(m_selStart);
										OnMovedCursor();
									}
									MoveCursorUp();
									break;
				
				case VK_DOWN:	if (m_initSel > -1)
									{
										LocateCursor(m_selEnd);
										OnMovedCursor();
									}
									MoveCursorDown();
									break;

				case VK_HOME:	MoveCursorBegLine(); break;
				case VK_END:	MoveCursorEndLine(); break;
				case VK_PRIOR:	MoveCursorPageUp(); break;
				case VK_NEXT:	MoveCursorPageDown(); break;
				}

				ClearSelectionAndInvalidate();
			}
#endif

			ScrollIntoView(m_line, m_col);
		}
		break;

	case VK_DELETE:
		if (m_pAutoListMembersWindow)
		{
			m_pAutoListMembersWindow->DestroyWindow();
			m_pAutoListMembersWindow->Release();
			m_pAutoListMembersWindow = NULL;
		}
		// Let through

	case VK_BACK:
		{
			if (m_selEnd > m_selStart)	// Delete Selection
			{
				DeleteSelection();
			}
			else
			{
				switch (nKey)
				{
				case VK_BACK:
					{
						if (m_pAutoListMembersWindow)
						{
							m_autoListEndOffset--;

							//m_autoListEndOffset = m_offset;
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->FindMatch(&GetTextData()[m_autoListStartOffset], m_autoListEndOffset-m_autoListStartOffset));
						}

						if (m_offset > 0)
						{
							long undokind = VK_BACK;

							if (m_undoManager)
							{
								if (m_pRecentUndoTyping == NULL || m_pRecentUndoTyping->m_kind != undokind)
								{
									CComObject<CEditUndoTyping>* pUndo;
									CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
									pUndo->AddRef();

									pUndo->m_pEdit = this;
									pUndo->m_startCharPos = m_offset;
									pUndo->m_kind = undokind;
									pUndo->m_bRedo = true;

									m_undoManager->Add(pUndo);
									m_pRecentUndoTyping = pUndo;
								}

								if (m_pRecentUndoTyping)
								{
								// Prepend the deleted char to the undo unit
									BSTR text = SysAllocStringLen(m_pRecentUndoTyping->m_text, m_pRecentUndoTyping->m_len+1);
									memcpy(text+1, m_pRecentUndoTyping->m_text, m_pRecentUndoTyping->m_len*2);
									text[0] = GetTextData()[m_offset-1];

									SysFreeString(m_pRecentUndoTyping->m_text);
									m_pRecentUndoTyping->m_text = text;
									m_pRecentUndoTyping->m_len++;
									m_pRecentUndoTyping->m_startCharPos--;
								}
							}

							MoveCursorLeft();
							DeleteChar(m_offset, 1);
						}
					}
					break;

				case VK_DELETE:
					{
						if (m_offset < GetTextLen())
						{
							long undokind = VK_DELETE;

							if (m_undoManager)
							{
								if (m_pRecentUndoTyping == NULL || m_pRecentUndoTyping->m_kind != undokind)
								{
									CComObject<CEditUndoTyping>* pUndo;
									CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
									//pUndo->AddRef();

									pUndo->m_pEdit = this;
									pUndo->m_startCharPos = m_offset;
									pUndo->m_kind = undokind;
									pUndo->m_bRedo = true;

									m_undoManager->Add(pUndo);
									m_pRecentUndoTyping = pUndo;
								}

								if (m_pRecentUndoTyping)
								{
								// Append the deleted char to the undo unit
									BSTR text = SysAllocStringLen(m_pRecentUndoTyping->m_text, m_pRecentUndoTyping->m_len+1);
									text[m_pRecentUndoTyping->m_len] = GetTextData()[m_offset];

									SysFreeString(m_pRecentUndoTyping->m_text);
									m_pRecentUndoTyping->m_text = text;
									m_pRecentUndoTyping->m_len++;
								}
							}

							DeleteChar(m_offset, 1);
						}
					}
				}
			}

		//	ResetVScrollSize();

		//	OnChange();
			OnMovedCursor();

		//	InvalidateRect(NULL, TRUE);
		}
		break;

	default:
		ShowCursor();
		return 0;// FALSE;
	}

//	ScrollIntoView(m_line, m_col);

	UpdateWindow();

	ShowCursor();

	return 0;
}

long CUIEdit::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	TCHAR nKey = wParam;
	int lKeyData = lParam;

	BYTE ch = nKey;
	if (ch == 8) return 0;
	if (ch == '\r') ch = '\n';

	if (ch == '\n')
	{
		if (m_pAutoListMembersWindow)
		{
			_bstr_t str = m_pAutoListMembersWindow->GetStringAt(m_pAutoListMembersWindow->GetCurSel());

			m_pAutoListMembersWindow->DestroyWindow();
			m_pAutoListMembersWindow->Release();
			m_pAutoListMembersWindow = NULL;

			ReplaceText(m_autoListStartOffset, m_autoListEndOffset-m_autoListStartOffset, str, str.length());

			LocateCursor(m_autoListStartOffset + str.length());

			return 0;
		}
	}

	if (ch == '\n')
	{
		if (!m_bMultiLine)	// Don't allow new lines unless multiline edit
		{
			Fire_OnChar((WCHAR)ch);	// ?
			return 0;
		}
	}

	HideCursor();

	if (m_case == -1)			ch = tolower(ch);
	else if (m_case == 1)	ch = toupper(ch);

	long undokind;

	if (ch == ' ')			undokind = ' ';
	else if (ch == '\t')	undokind = '\t';
	else if (ch == '\n')	undokind = '\n';
	else						undokind = 1;	// Any other character

	CComObject<CEditUndoParent>* pParentUndo = NULL;//CEditUndoParent* pParentUndo = NULL;

	if (m_selEnd > m_selStart)	// Delete Selection
	{
		if (m_undoManager)
		{
			CComObject<CEditUndoParent>::CreateInstance(&pParentUndo);
			pParentUndo->AddRef();	// ??

			m_undoManager->Open(pParentUndo);
		}

		DeleteSelection();
	}

	if (m_undoManager)
	{
		if (m_pRecentUndoTyping == NULL || m_pRecentUndoTyping->m_kind != undokind)
		{
			CComObject<CEditUndoTyping>* pUndo;
			CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
			pUndo->AddRef();	// ??

			pUndo->m_kind = undokind;
			pUndo->m_bRedo = false;
			pUndo->m_pEdit = this;
			pUndo->m_startCharPos = m_offset;

			m_undoManager->Add(pUndo);
			m_pRecentUndoTyping = pUndo;
			pUndo->Release();
		}

		if (m_pRecentUndoTyping)
		{
			m_pRecentUndoTyping->m_len++;
		}

		if (pParentUndo)
		{
			m_undoManager->Close(pParentUndo, TRUE/*commit*/);
			pParentUndo->Release();

			m_pRecentUndoTyping = NULL;
		}
	}

	InsertChar(ch);
	MoveCursorRight();

	if (m_pAutoListMembersWindow)
	{
		m_autoListEndOffset++;// = m_offset;
		m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->FindMatch(&GetTextData()[m_autoListStartOffset], m_autoListEndOffset-m_autoListStartOffset));
	}

//	OnMovedCursor();
	Fire_OnChar((WCHAR)wParam);
//	OnChange();

/*
	ResetHScrollSize();	// hm.. not very efficient to do this all the time
	if (ch == '\n') ResetVScrollSize();

	ScrollIntoView(m_line, m_col);

	InvalidateRect(NULL, TRUE);
*/
	UpdateWindow();

	ShowCursor();

	return 0;
}

void CUIEdit::BuildRLineOffsets()
{
	for (int i = 0; i < m_rlinesArr.GetSize(); i++)
	{
		delete m_rlinesArr[i];
	}
	m_rlinesArr.RemoveAll();

	BSTR data = GetTextData();
	DWORD length = GetTextLen();

	DWORD offset = 0;

	RLineDef* pLine;

	pLine = new RLineDef;
	m_rlinesArr.Add(pLine);

	pLine->m_offset = 0;

	int len = 0;

	while (offset < length)
	{
		int startoffset = offset;

		// Run until newline
		while (offset < length)
		{
			if (*data == L'\n') break;
			offset++;
			data++;
		}

		len += offset-startoffset;

		if (offset < length)
		{
			ATLASSERT(*data == L'\n');

			pLine->m_lineLength = len;
			pLine->m_lineLengthR = len+1;
			len = 0;

		// Start new line

			pLine = new RLineDef;
			m_rlinesArr.Add(pLine);
			
			pLine->m_offset = ++offset;

			data++;
		}
	}

	pLine->m_lineLength = len;
	pLine->m_lineLengthR = len;
}

void CUIEdit::BuildLineOffsets()
{
	int i;

// Display lines (wrapped or not)
	for (i = 0; i < m_linesArr.GetSize(); i++)
	{
		delete m_linesArr[i];
	}

	if (!m_bWordWrap)
	{
		m_linesArr.SetSize(m_rlinesArr.GetSize());

		for (int i = 0; i < m_rlinesArr.GetSize(); i++)
		{
			RLineDef* pRLine = m_rlinesArr[i];

			pRLine->m_nDispLines = 1;

			LineDef* pLine = new LineDef;
			pLine->m_lineLength = pRLine->m_lineLength;
			pLine->m_lineLengthR = pRLine->m_lineLengthR;
			pLine->m_offset = pRLine->m_offset;

			m_linesArr[i] = pLine;
		}
	}
	else
	{
		m_linesArr.RemoveAll();

		HDC hDC = CreateCompatibleDC(NULL);

		CComQIPtr<IFont> font = m_pFont;
		HFONT hFont;
		font->get_hFont(&hFont);

		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

		BSTR data = GetTextData();
		int cx = m_textArea.Width();

		for (int i = 0; i < m_rlinesArr.GetSize(); i++)
		{
			DWORD offset = m_rlinesArr[i]->m_offset;
			int lineLength = m_rlinesArr[i]->m_lineLength;

			m_rlinesArr[i]->m_nDispLines = 1;

			LineDef* pLine = new LineDef;
			pLine->m_offset = offset;
			m_linesArr.Add(pLine);

			int len = 0;
			int x = 0;
			int li = 0;

			while (li < lineLength)
			{
				int wordlen = 0;

				BSTR p = data + offset;

				while ((li+wordlen < lineLength) && !iswspace(*p))
				{
					p++;
					wordlen++;
				}

				while ((li+wordlen < lineLength) && iswspace(*p))
				{
					p++;
					wordlen++;
				}

				SIZE size = {0,0};
				if (wordlen > 0)
				{
					for (int i = 0; i < wordlen; i++)
					{
						TCHAR c = data[offset+i];

						if (c == '\t')
						{
							int spaces = m_tabSize - (len % m_tabSize);
							SIZE size2;
							GetTextExtentPoint32(hDC, " ", 1, &size2);

							size.cx += size2.cx*spaces;
						}
						else
						{
							SIZE size2;
							GetTextExtentPoint32(hDC, &c, 1, &size2);

							size.cx += size2.cx;
						}
					}
				}

				if (x > 0 && x+size.cx > cx)
				{
					m_rlinesArr[i]->m_nDispLines++;

				// Finish previous line
					pLine->m_lineLength = len;
					pLine->m_lineLengthR = len;

					len = 0;
					x = 0;

				// Start new line
					pLine = new LineDef;
					pLine->m_offset = offset;
					m_linesArr.Add(pLine);
				}

				x += size.cx;
				len += wordlen;
				li += wordlen;
				offset += wordlen;
			}

			pLine->m_lineLength = len;
			pLine->m_lineLengthR = len + (m_rlinesArr[i]->m_lineLengthR - m_rlinesArr[i]->m_lineLength);
		}

		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);
	}
}

/*
void CUIEdit::Update()
{
	BuildLines();

	HWND hwnd;
	get_hwnd(&hwnd);

	if (hwnd)
	{
		ResetVScrollSize();
		ResetHScrollSize();
		InvalidateRect(NULL, TRUE);
	}
}
*/

void CUIEdit::OnMovedCursor()
{
	RECT rect = { 0, m_textArea.bottom, 60, m_textArea.bottom+16 };
	InvalidateRect(&rect, TRUE);

	Fire_MoveCursor(m_offset);
}

void CUIEdit::CalcLineCol(int offset)
{
	for (int i = m_linesArr.GetSize()-1; i >= 0; i--)
	{
		if (offset >= m_linesArr[i]->m_offset)
		{
			m_line = i;
			m_col = offset - m_linesArr[i]->m_offset;
			return;
		}
	}

	ATLASSERT(0);
}

void CUIEdit::CalcRLineCol(int offset)
{
	for (int i = m_rlinesArr.GetSize()-1; i >= 0; i--)
	{
		if (offset >= m_rlinesArr[i]->m_offset)
		{
			m_rline = i;
			m_rcol = offset - m_rlinesArr[i]->m_offset;
			return;
		}
	}

	ATLASSERT(0);
}

void CUIEdit::LocateCursor(int offset)
{
	m_offset = offset;

	if (m_hWnd)
	{
		CalcLineCol(m_offset);
		CalcRLineCol(m_offset);
	}
}

void CUIEdit::LocateCursor(int line, int col)
{
	if (line < 0) line = 0;
	else if (line > m_linesArr.GetSize()-1) line = m_linesArr.GetSize()-1;

	int lineLength = m_linesArr[line]->m_lineLength;

	if (col < 0) col = 0;
	else if (col > lineLength) col = lineLength;

	int offset = m_linesArr[line]->m_offset + col;

	m_offset = offset;
	ATLASSERT(m_offset >= 0 && m_offset <= GetTextLen());

	m_line = line;
	m_col = col;

	CalcRLineCol(m_offset);

	OnMovedCursor();
}

void CUIEdit::ClearSelectionAndInvalidate()
{
	if (m_selEnd > m_selStart)	// Clearing previous selection
	{
		InvalidateRange(m_selStart, m_selEnd);

		m_initSel = -1;
		m_selStart = 0;
		m_selEnd = -1;
	}
}

void CUIEdit::SetSelectionAndInvalidate(int start, int end)
{
	int oldSelStart;
	int oldSelEnd;
	
	if (m_selEnd > -1)	// There is a previous selection
	{
		oldSelStart = m_selStart;
		oldSelEnd = m_selEnd;
	}
	else
	{
		oldSelStart = m_initSel;
		oldSelEnd = m_initSel;
	}

// Set new selection values
	if (end > start)
	{
		m_selStart = start;
		m_selEnd = end;
	}
	else
	{
		m_selStart = end;
		m_selEnd = start;
	}
	
// Invalidate the difference in range between the previous selection and
// The new selection
	if (m_hWnd)
	{
		int istart, iend;
		
		if (oldSelStart == m_selStart)
		{
			if (oldSelEnd < m_selEnd)
			{
				istart = oldSelEnd;
				iend = m_selEnd;
			}
			else
			{
				istart = m_selEnd;
				iend = oldSelEnd;
			}
		}
		else if (oldSelEnd == m_selEnd)
		{
			if (oldSelStart < m_selStart)
			{
				istart = oldSelStart;
				iend = m_selStart;
			}
			else
			{
				istart = m_selStart;
				iend = oldSelStart;
			}
		}
		else
		{
			istart = min(m_selStart, oldSelStart);
	#if 1	// TODO
			if (istart < 0) istart = 0;
	#endif
			iend = max(m_selEnd, oldSelEnd);
		}

		InvalidateRange(istart, iend);
	}
}

void CUIEdit::InvalidateRange(int startchar, int endchar)
{
	ASSERT(endchar >= startchar);

	LineDef** pLines = m_linesArr.GetData();

// Find the lines corresponding to startchar and endchar
	int i;

	int startline = 0;

	for (i = 0; i < m_linesArr.GetSize(); i++)
	{
		if (pLines[i]->m_offset > startchar) break;
		startline = i;
	}

	int endline = startline;

	for (i = startline; i < m_linesArr.GetSize(); i++)
	{
		if (pLines[i]->m_offset > endchar) break;
		endline = i;
	}

	for (i = startline; i <= endline; i++)
	{
		InvalidateLine(i);
	}
}

void CUIEdit::InvalidateLine(int line)
{
	if (m_hWnd)
	{
		int lcol = m_linesArr[line]->m_lineLengthR;//GetLineLength(line);
		//int endvcol = Column2VColumn(line, lcol);
		int endpx = PointXFromColumn(line, lcol);

		long scrollposY; m_vert->get_pos(&scrollposY);

		int y = (line - scrollposY)*m_ch;
		int x = m_textArea.left;
		int endx = x + endpx + 1;//m_cw;

		CRect lineRect(x, y, endx+1, y+m_ch+1);
		InvalidateRect(&lineRect, TRUE);
	}
}

#include <stdio.h>

HRESULT CUIEdit::OnDraw(ATL_DRAWINFO& di)
{
	HDC hDC = di.hdcDraw;

	CRect& client = *(CRect*)di.prcBounds;

	Draw3DRect(hDC, 0, 0, client.right, client.bottom, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

	int state = SaveDC(hDC);

	if (m_bHorzSB && m_bVertSB)
	{
		FillSolidRect(hDC, m_textArea.right, m_textArea.bottom, client.right-m_textArea.right-1, client.bottom-m_textArea.bottom-1, GetSysColor(COLOR_BTNFACE));
	}

	if (IntersectClipRect(hDC, m_border, m_textArea.top, m_textArea.right, m_textArea.bottom) > NULLREGION)
	{
		{
			CRect lborder(0, m_textArea.top, m_textArea.left, m_textArea.bottom);
			FillSolidRect(hDC, &lborder, RGB(210, 210, 210));
		}

		CComQIPtr<IFont> font = m_pFont;
		HFONT hFont;
		font->get_hFont(&hFont);

		SelectObject(hDC, hFont);

		if (m_bLineNumbers)
		{
			long scrollposY; m_vert->get_pos(&scrollposY);

			POINT oldOrg;
			SetViewportOrgEx(hDC, 0, m_textArea.top - scrollposY*m_ch, &oldOrg);
			int oldBkMode = SetBkMode(hDC, TRANSPARENT);

			int y = 0;

			for (int i = 0; i < m_rlinesArr.GetSize(); i++)
			{
				CRect rc(0, y, 4*m_spaceWidth, y+m_ch);

				char str[64];
				int len = sprintf(str, "%d", i+1);
				DrawText(hDC, str, len, &rc, DT_SINGLELINE | DT_VCENTER | DT_RIGHT);

				y += m_rlinesArr[i]->m_nDispLines * m_ch;
			}

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			SetBkMode(hDC, oldBkMode);
		}

		//RECT  irect;
		if (IntersectClipRect(hDC, m_textArea.left, m_textArea.top, m_textArea.right, m_textArea.bottom) > NULLREGION/*IntersectRect(&irect, &clip, &m_textArea)*/)
		{
			//FillSolidRect(hDC, &m_textArea, RGB(255, 255, 255));	// TBD: Remove this

			HPEN pOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);

			//IntersectClipRect(hDC, m_textArea.left, m_textArea.top, m_textArea.right, m_textArea.bottom);

			POINT scrollPos;

			long scrollposX; m_horz->get_pos(&scrollposX);
			long scrollposY; m_vert->get_pos(&scrollposY);

			scrollPos.x = m_textArea.left;
			scrollPos.y = m_textArea.top;

			scrollPos.x -= scrollposX;//*m_cw;
			scrollPos.y -= scrollposY*m_ch;

			POINT oldOrg;
			SetViewportOrgEx(hDC, scrollPos.x, scrollPos.y, &oldOrg);

			CRect clip;
			GetClipBox(hDC, &clip);

			BSTR data = GetTextData();
			DWORD length = GetTextLen();

			//	pDC->SetTextColor(RGB(200, 0, 0));

			HPEN whitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

			int nlines = CountLines();

			SyntaxChunk* syntax = m_styleChunks.GetData();

			int firstVisLine = scrollposY;
			int lastVisLine = firstVisLine + (m_textArea.Height()+m_ch-1)/m_ch;
			if (lastVisLine > CountLines()) lastVisLine = CountLines();

			int y = firstVisLine*m_ch;

			if (lastVisLine > firstVisLine)
			{
				int offset = m_linesArr[firstVisLine]->m_offset;

				SyntaxChunk* styleChunks = m_styleChunks.GetData();

			// Find the style chunk to start at, and the offset into it
				DWORD startoffset = 0;
				int styleIndex = 0;
				while (styleIndex < m_styleChunks.GetSize())
				{
					if (startoffset + styleChunks[styleIndex].Length > offset) break;
					startoffset += styleChunks[styleIndex].Length;
					styleIndex++;
				}

				DWORD styleOffset = offset-startoffset;

				for (int lin = firstVisLine; lin < lastVisLine; lin++)
				{
					int offset = m_linesArr[lin]->m_offset;

					int i = offset;
					int vcol = 0;

					CRect irect;
					BOOL bDraw = TRUE;

					int x = 0;

					for (int j = 0; j < m_linesArr[lin]->m_lineLengthR; j++, i++)
					{
						if (bDraw)
						{
							BOOL bInSelection = ((i >= m_selStart) && (i < m_selEnd));	// Selection

							if (bInSelection)
							{
								SetTextColor(hDC, m_styles[0].FgColor);
								SetBkColor(hDC, m_styles[0].BgColor);
							}
							else
							{
								WORD el = m_styleChunks[styleIndex].Element;

								SetTextColor(hDC, m_styles[el].FgColor);
								SetBkColor(hDC, m_styles[el].BgColor);
							}

							if (data[i] == '\t')	// TAB
							{
								int spaces = m_tabSize - (vcol % m_tabSize);

								for (int i = 0; i < spaces; i++)
								{
									if (i == 0 && m_bShowTabs)
										TextOut(hDC, x, y, "»", 1);
									else
										TextOut(hDC, x, y, " ", 1);

									SIZE size2;
									GetTextExtentPoint32(hDC, " ", 1, &size2);
									x += size2.cx;
								}

								vcol += spaces;
							}
							else
							{
								TCHAR ch = data[i];
								if (ch == '\n')
								{
									if (m_bShowEOL)
										ch = '¶';
									else
										ch = ' ';
								}
								else if (ch == ' ')
								{
									if (m_bShowSpace)
									{
										ch = '·';
									}
								}

								TextOut(hDC, x, y, &ch, 1);
								SIZE size2;
								GetTextExtentPoint32(hDC, &ch, 1, &size2);
								x += size2.cx;

								vcol++;
							}
						}

						styleOffset++;
						while (styleOffset >= m_styleChunks[styleIndex].Length)
						{
							styleOffset = 0;
							styleIndex++;

							if (styleIndex >= m_styleChunks.GetSize()) break;
						}
					}

				// Draw out line
					CRect lrc(x, y, scrollposX+m_textArea.Width(), y+m_ch);
					if (lrc.Width() > 0)
						FillSolidRect(hDC, &lrc, RGB(255, 255, 255));

					y += m_ch;
				}

			// Draw out bottom of window
				CRect lrc(0, y, scrollposX+m_textArea.Width(), scrollposY+m_textArea.Height());
				if (lrc.Height() > 0)
					FillSolidRect(hDC, &lrc, RGB(255, 255, 255));
			}

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			SelectObject(hDC, pOldPen);

			DeleteObject(blackPen);
			DeleteObject(whitePen);

			if (m_bShowCursor) DrawCursor(hDC);
		}
	}

	RestoreDC(hDC, state);

	return 0;
}

LRESULT CUIEdit::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
// Don't erase background (everything is drawn in OnDraw)
	return TRUE;
}

int CUIEdit::CountLines() 
{
	return m_linesArr.GetSize();
}

#if 0
void CUIEdit::OnMouseWheel(UINT nFlags, short zDelta)
{
	UINT lines = 3;	// Default
//	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &lines, 0);

//	MessageBeep(-1);
}
#endif

long CUIEdit::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	return 0;
	OnSize(m_bWordWrap);
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CUIEdit::OnSize(BOOL bBuildLines) 
{
	CRect	client;
	GetClientRect(&client);

	int cx = client.Width();
	int cy = client.Height();

	int sbHeight;
	int sbWidth;

	int lborwidth;
	if (m_lborWidth == -1)
		lborwidth = 16;	// Default
	else
		lborwidth = m_lborWidth;

	if (m_bLineNumbers)
		lborwidth += 4*m_spaceWidth;

	if (m_bVertSB)
		sbWidth = GetSystemMetrics(SM_CXVSCROLL);
	else
		sbWidth = 0;

	if (m_bHorzSB)
		sbHeight = GetSystemMetrics(SM_CXHSCROLL);
	else
		sbHeight = 0;

	m_axhorz.ShowWindow(m_bHorzSB? SW_SHOW: SW_HIDE);
	m_axvert.ShowWindow(m_bVertSB? SW_SHOW: SW_HIDE);

	m_textArea.left = m_border+1+lborwidth;
	m_textArea.top = m_border;
	m_textArea.right = cx-sbWidth-1-m_border;
	m_textArea.bottom = cy-sbHeight-1-m_border;

	if (FALSE)	// Statusbar
	{
		m_textArea.bottom -= 16;
	}

	m_axhorz.MoveWindow(m_border, cy-sbHeight-m_border, cx-sbWidth-m_border, sbHeight, TRUE);
	m_axvert.MoveWindow(cx-sbWidth-m_border, m_border, sbWidth, cy-sbHeight-m_border, TRUE);

	if (bBuildLines)
	{
		BuildLineOffsets();

		CalcLineCol(m_offset);	// Recalculate: m_line/m_col
		m_idealcolX = PointXFromColumn(m_line, m_col);
	}

	ResetVScrollSize();
	ResetHScrollSize();
}

/*
void CUIEdit::CutSelectionToClipboard()
{
	CopySelectionToClipboard();
	DeleteChar(m_selStart, m_selEnd - m_selStart+1);
	m_initSel = 0; m_selStart = 0; m_selEnd = -1;
//	TOP()->OnUpdate();
}
*/

void CUIEdit::CopySelectionToClipboard()
{
	if (::OpenClipboard(NULL))
	{
		::EmptyClipboard();

		// Unicode Text
		{
			DWORD size = (m_selEnd - m_selStart)*2;

			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size+2);
			BSTR pMem = (BSTR)GlobalLock(hMem);
			CopyMemory(pMem, GetTextData() + m_selStart, size);
			GlobalUnlock(hMem);

			::SetClipboardData(CF_UNICODETEXT, hMem);
		}

		// Ansi Text
		{
			DWORD size = m_selEnd - m_selStart;

			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, size+1);
			LPBYTE pMem = (LPBYTE)GlobalLock(hMem);

			BSTR p = GetTextData() + m_selStart;
			for (int i = 0; i < size; i++)
			{
				pMem[i] = (BYTE)p[i];
			}
			pMem[i] = 0;

			GlobalUnlock(hMem);

			::SetClipboardData(CF_TEXT, hMem);
		}

		::CloseClipboard();
	}
}

void CUIEdit::PasteFromClipboard()
{
	if (::OpenClipboard(NULL))
	{
		if (::IsClipboardFormatAvailable(CF_TEXT) ||
			::IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			HANDLE hMem;

			BSTR text = NULL;
			DWORD len = 0;
			void* pMem = NULL;

			if (hMem = ::GetClipboardData(CF_UNICODETEXT))
			{
				pMem = (void*)GlobalLock(hMem);
				len = min(wcslen((BSTR)pMem), GlobalSize(hMem)/2);

				text = (BSTR)pMem;
			}
			else
			{
				// Convert to unicode
				pMem = (void*)GlobalLock(hMem);
				len = min(strlen((char*)pMem), GlobalSize(hMem));

				text = SysAllocStringLen(NULL, len);
				for (int i = 0; i < len; i++)
				{
					text[i] = ((BYTE*)pMem)[i];
				}
			}

			InsertText(m_offset, text, len);
			BuildRLineOffsets();
			BuildLineOffsets();

			CComObject<CEditUndoTyping>* pUndo;
			CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
			//pUndo->AddRef(); ??
			pUndo->m_pEdit = this;
			pUndo->m_kind = 1;
			pUndo->m_startCharPos = m_offset;
			pUndo->m_len = len;

			m_undoManager->Add(pUndo);
			//pUndo->Release();

			m_pRecentUndoTyping = NULL;

			GlobalUnlock(hMem);

			if (text != pMem)
			{
				SysFreeString(text);
			}
		}

		::CloseClipboard();
	}
}

void __stdcall CUIEdit::OnHorzScroll(long code, long pos)
{
	HideCursor();

	long oldPos; m_horz->get_pos(&oldPos);

	CRect	rect = m_textArea;
	
	m_horz->put_pos(pos);
	ScrollWindow((oldPos-pos), 0, &rect, &rect);

	ShowCursor();
}

void __stdcall CUIEdit::OnVertScroll(long code, long pos)
{
	HideCursor();

	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_textArea;
	rect.left = 0;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, (oldPos-pos)*m_ch, &rect, &rect);

	ShowCursor();
}

long CUIEdit::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	return 0;

	SetTimer(1, 400);
	ShowCursor();

	return 0;
}

long CUIEdit::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	return 0;

	KillTimer(1);
	HideCursor();

	return 0;
}

long CUIEdit::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	return 0;

	UINT nHitTest = LOWORD(lParam);
	UINT message = HIWORD(lParam);

	if (nHitTest == HTCLIENT)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		CRect	client;
		GetClientRect(&client);
		client.right -= GetSystemMetrics(SM_CYHSCROLL);
		client.bottom -= GetSystemMetrics(SM_CXVSCROLL);

		HCURSOR	hCursor = NULL;

		if (client.PtInRect(point))
		{
			hCursor = LoadCursor(NULL, IDC_IBEAM);
		}

		if (hCursor)
		{
			::SetCursor(hCursor);
			return TRUE;
		}
	}

	return FALSE;
}

//#include "FindDlg.h"

void CUIEdit::Find(LPCTSTR findStr)
{
#if 0
	int findlen = lstrlen(findStr);

	BSTR text = GetTextData();
	int textlen = GetTextLen();
	int i = 0;

	while (textlen > 0)
	{
		if (strnicmp(findStr, &text[i], textlen) == 0)
		{
			m_selStart = i;
			m_selEnd = i+findlen;

			InvalidateRect(m_textArea, TRUE);
			break;
		}

		text++;
		textlen--;
		i++;
	}
#endif
}

void CUIEdit::OnEditFind()
{
/*	CFindDlg	dlg;
	if (dlg.DoModal() == IDOK)
	{
		Find(dlg.m_findWhat);
	}
*/
}

void CUIEdit::OnFindMatchingBracket()
{
	BSTR text = GetTextData();
	int textlen = GetTextLen();
	char c = text[m_offset];

	int dir;
	char c2;

	if (c == '(' || c == '[' || c == '{')
	{
		dir = 1;

				if (c == '(') c2 = ')';
		else	if (c == '[') c2 = ']';
		else	if (c == '{') c2 = '}';
	}
	else if (c == ')' || c == ']' || c == '}')
	{
		dir = -1;

				if (c == ')') c2 = '(';
		else	if (c == ']') c2 = '[';
		else	if (c == '}') c2 = '{';
	}
	else
	{
		MessageBeep(-1);
		return;
	}

	int count = 1;
	int offset = m_offset + dir;

	LONG bShift = (GetAsyncKeyState(VK_SHIFT) & (1<<15));

	if (dir == -1)
	{
		while (offset >= 0)
		{
			if (text[offset] == c2) count--;
			else if (text[offset] == c) count++;

			if (count == 0)
			{
				LocateCursor(offset);

				InvalidateRect(NULL, TRUE);
				OnMovedCursor();

				break;
			}

			offset--;
		}
	}
	else
	{
		while (offset < textlen)
		{
			if (text[offset] == c2) count--;
			else if (text[offset] == c) count++;

			if (count == 0)
			{
				LocateCursor(offset);
				InvalidateRect(NULL, TRUE);
				OnMovedCursor();
				break;
			}

			offset++;
		}
	}

	ScrollIntoView(m_line, m_col);
}

//////// Default text data handler

void CUIEdit::InsertText(int offset, BSTR htmstring, int len)
{
	ATLASSERT(m_tdp != NULL);
	m_tdp->insertText(offset, htmstring, len);
}

void CUIEdit::DeleteText(int offset, int len)
{
	ATLASSERT(m_tdp != NULL);
	m_tdp->deleteText(offset, len);
}

void CUIEdit::ReplaceText(int offset, int deletelen, BSTR data)
{
	ATLASSERT(m_tdp != NULL);
	m_tdp->replaceText(offset, deletelen, data);
}

STDMETHODIMP CUIEdit::get_textDocument(IDispatch **pVal)
{
	*pVal = m_tdp;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CUIEdit::put_textDocument(IDispatch *newVal)
{
	if (m_tdp)
	{
		if (m_hWnd)
		{
			HRESULT hr = IDispEventImpl<3, CUIEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_tdp);
			ATLASSERT(SUCCEEDED(hr));
		}
	}

	m_tdp = newVal;

	if (m_tdp)
	{
		if (m_hWnd)
		{
			HRESULT hr = IDispEventImpl<3, CUIEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>::DispEventAdvise(m_tdp);
			ATLASSERT(SUCCEEDED(hr));
		}
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::get_vertScroll(DWORD *pVal)
{
	*pVal = m_bVertSB;
	return S_OK;
}

STDMETHODIMP CUIEdit::put_vertScroll(DWORD newVal)
{
	m_bVertSB = newVal;

	if (m_hWnd)
	{
		OnSize(m_bWordWrap);
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::get_horzScroll(DWORD *pVal)
{
	*pVal = m_bHorzSB;
	return S_OK;
}

STDMETHODIMP CUIEdit::put_horzScroll(DWORD newVal)
{
	m_bHorzSB = newVal;

	if (m_hWnd)
	{
		OnSize(m_bWordWrap);
	}

	return S_OK;
}

void __stdcall CUIEdit::OnTextContentChanged()
{
	if (m_hWnd)
	{
		ClearFormatting();

		BuildRLineOffsets();
		BuildLineOffsets();
	}

	m_offset = 0;
	m_line = 0;
	m_col = 0;

	if (m_hWnd)
	{
		ResetVScrollSize();
		ResetHScrollSize();
		InvalidateRect(NULL, TRUE);
	}

	Fire_Change();
}

void __stdcall CUIEdit::OnTextInsertText(long offset, long len)
{
	DWORD styleoffset = 0;
	for (int i = 0; i < m_styleChunks.GetSize(); i++)
	{
		if (styleoffset + m_styleChunks[i].Length >= offset) break;
		styleoffset += m_styleChunks[i].Length;
	}
	m_styleChunks[i].Length += len;

	if (TRUE)
	{
		BuildRLineOffsets();
	}
	else
	{
		// Find which line offset is on
		int line;
		for (line = m_rlinesArr.GetSize()-1; line >= 0; line--)
		{
			if (offset >= m_rlinesArr[line]->m_offset)
				break;
		}

		int linelen = offset-m_rlinesArr[line]->m_offset;
		ATLASSERT(linelen >= 0);

		linelen = m_rlinesArr[line]->m_lineLength+len;

		BSTR data = GetTextData();
		DWORD length = GetTextLen();

#if 0
		for (int j = offset; j < offset+len; j++)
		{
			/*
			if (data[j] == L'\n')
			{
			// Shorten previous line
				m_rlinesArr[line]->m_lineLength = linelen;
				m_rlinesArr[line]->m_lineLengthR = linelen+1;
				linelen = 0;

			// Create new line
				line++;

				RLineDef* pLine;
				pLine = new RLineDef;
				pLine->m_offset = j;

				m_rlinesArr.InsertAt(line, pLine);
			}
			else
			*/
			{
				linelen++;
			}
		}
#endif

	//	m_rlinesArr[line]->m_offset = j;
		m_rlinesArr[line]->m_lineLength = linelen;
		m_rlinesArr[line]->m_lineLengthR = linelen+1;
		line++;

		{
			// Offset following lines
			for (int i = line; i < m_rlinesArr.GetSize(); i++)
			{
				m_rlinesArr[i]->m_offset += len;
			}
		}
	}

	BuildLineOffsets();

#ifdef _DEBUG
	{
		DWORD tlen = GetTextLen();

		DWORD total = 0;
		for (int i = 0; i < m_styleChunks.GetSize(); i++)
		{
			total += m_styleChunks[i].Length;
		}
		ATLASSERT(total == tlen);
	}
#endif

	if (offset < m_selStart)
		m_selStart = m_offset+len;

	if (offset < m_selEnd)
		m_selEnd = m_offset+len;

	if (offset < m_initSel)
		m_initSel = m_offset+len;

	if (offset < m_offset)
		LocateCursor(m_offset+len);

//	ResetHScrollSize();	// hm.. not very efficient to do this all the time
	ResetVScrollSize();
//	ScrollIntoView(m_line, m_col);	// TODO remove

	if (m_hWnd)
	{
		InvalidateRect(NULL, TRUE);
	}

	Fire_Change();
}

void __stdcall CUIEdit::OnTextDeletedText(long offset, long len)
{
	DWORD styleoffset = 0;
	for (int i = 0; i < m_styleChunks.GetSize(); i++)
	{
		if (styleoffset + m_styleChunks[i].Length > offset) break;
		styleoffset += m_styleChunks[i].Length;
	}

	int j = i;
	DWORD styleoffset2 = styleoffset;
	for (; j < m_styleChunks.GetSize(); j++)
	{
		if (styleoffset2 + m_styleChunks[j].Length >= offset) break;
		styleoffset2 += m_styleChunks[j].Length;
	}

	if (i == j)
	{
		m_styleChunks[i].Length -= len;
	}
	else
	{
		m_styleChunks[i].Length = offset - styleoffset;
		m_styleChunks[j].Length -= (offset+len) - styleoffset2;

		m_styleChunks.RemoveAt(i+1, j-i-1);
	}

	if (TRUE)
	{
		BuildRLineOffsets();
	}
	else
	{
		// Find which line offset is on
		int line;
		for (line = m_rlinesArr.GetSize()-1; line >= 0; line--)
		{
			if (offset >= m_rlinesArr[line]->m_offset)
				break;
		}

		int linelen = m_rlinesArr[line]->m_lineLength-len;

		m_rlinesArr[line]->m_lineLength = linelen;
		m_rlinesArr[line]->m_lineLengthR = linelen+1;
		line++;

		{
			// Offset following lines
			for (int i = line; i < m_rlinesArr.GetSize(); i++)
			{
				m_rlinesArr[i]->m_offset -= len;
			}
		}
	}

	BuildLineOffsets();

#ifdef _DEBUG
	{
		DWORD tlen = GetTextLen();

		DWORD total = 0;
		for (int k = 0; k < m_styleChunks.GetSize(); k++)
		{
			total += m_styleChunks[k].Length;
		}
		ATLASSERT(total == tlen);
	}
#endif

	if (m_selStart >= offset && m_selStart < offset+len)
		m_selStart = offset;
	else if (m_selStart >= offset+len)
		m_selStart = m_selStart - len;

	if (m_selEnd >= offset && m_selEnd < offset+len)
		m_selEnd = offset;
	else if (m_selEnd >= offset+len)
		m_selEnd = m_selEnd - len;

	if (m_initSel >= offset && m_initSel < offset+len)
		m_initSel = offset;
	else if (m_initSel >= offset+len)
		m_initSel = m_initSel - len;

	if (m_offset >= offset && m_offset < offset+len)
		LocateCursor(offset);
	else if (m_offset >= offset+len)
		LocateCursor(m_offset - len);

//	ResetHScrollSize();	// hm.. not very efficient to do this all the time
	ResetVScrollSize();
//	ScrollIntoView(m_line, m_col);	// TODO remove

	if (m_hWnd)
	{
		InvalidateRect(NULL, TRUE);
	}

	Fire_Change();
}

STDMETHODIMP CUIEdit::get_undoManager(IOleUndoManager **pVal)
{
	*pVal = m_undoManager;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CUIEdit::put_undoManager(IOleUndoManager *newVal)
{
	m_undoManager = newVal;
	return S_OK;
}

void CUIEdit::DeleteSelection()
{
	int len = m_selEnd - m_selStart;

	if (m_undoManager)
	{
		CComObject<CEditUndoTyping>* pUndo;
		CComObject<CEditUndoTyping>::CreateInstance(&pUndo);

		pUndo->AddRef();
		pUndo->m_pEdit = this;
		pUndo->m_kind = 1;
		pUndo->m_bRedo = true;
		pUndo->m_startCharPos = m_selStart;
		pUndo->m_len = len;
		pUndo->m_text = SysAllocStringLen(GetTextData() + m_selStart, len);

		m_undoManager->Add(pUndo);
		pUndo->Release();

		m_pRecentUndoTyping = NULL;
	}

	DeleteText(m_selStart, len);
//	BuildLineOffset();

	LocateCursor(m_selStart);
	m_initSel = 0; m_selStart = 0; m_selEnd = -1;
}

//#include "..\WebEditor\IIDCommands.h"

#if 0
BEGIN_CMD_MAP(CUIEdit)
	CMD_HANDLER(ID_EDIT_CUT, OnEditCut)
	CMD_UPDATE(ID_EDIT_CUT, OnEditCutCopyUpdate)
	CMD_HANDLER(ID_EDIT_COPY, OnEditCopy)
	CMD_UPDATE(ID_EDIT_COPY, OnEditCutCopyUpdate)
	CMD_HANDLER(ID_EDIT_PASTE, OnEditPaste)
	CMD_UPDATE(ID_EDIT_PASTE, OnEditPasteUpdate)

	CMD_HANDLER(ID_EDIT_CLEAR, OnEditDelete)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditDeleteUpdate)
END_CMD_MAP()

LRESULT CUIEdit::OnEditCut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CopySelectionToClipboard();
	DeleteSelection();

	ResetVScrollSize();
	ResetHScrollSize();
	InvalidateRect(NULL, TRUE);

//	OnChange();
	OnMovedCursor();

	return 0;
}

LRESULT CUIEdit::OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CopySelectionToClipboard();

	return 0;
}

void CUIEdit::OnEditCutCopyUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(m_initSel > -1);
}

LRESULT CUIEdit::OnEditPaste(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComObject<CEditUndoParent>* pParentUndo = NULL;

	if (m_initSel > -1)
	{
		CComObject<CEditUndoParent>::CreateInstance(&pParentUndo);
		pParentUndo->AddRef();

		m_undoManager->Open(pParentUndo);

		DeleteSelection();
	}

	PasteFromClipboard();

	if (pParentUndo)
	{
		m_undoManager->Close(pParentUndo, TRUE/*commit*/);
		pParentUndo->Release();
	}

	m_pRecentUndoTyping = NULL;

	ResetVScrollSize();
	ResetHScrollSize();
	InvalidateRect(NULL, TRUE);

//	OnChange();
	OnMovedCursor();

	return 0;
}

void CUIEdit::OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_TEXT) || IsClipboardFormatAvailable(CF_UNICODETEXT));
}

LRESULT CUIEdit::OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DeleteSelection();

	ResetVScrollSize();
	ResetHScrollSize();
	InvalidateRect(NULL, TRUE);

//	OnChange();
	OnMovedCursor();

	return 0;
}

void CUIEdit::OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(m_initSel > -1);
}
#endif

STDMETHODIMP CUIEdit::SetText(BSTR text)
{
	m_tdp->put_data(SysAllocString(text));
	return S_OK;
}

STDMETHODIMP CUIEdit::GetText(BSTR *text)
{
	BSTR b;
	m_tdp->get_data(&b);
	*text = SysAllocString(b);

	return S_OK;
}

STDMETHODIMP CUIEdit::get_multiLine(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_bMultiLine;
	return S_OK;
}

STDMETHODIMP CUIEdit::put_multiLine(VARIANT_BOOL newVal)
{
	m_bMultiLine = newVal;
	return S_OK;
}

STDMETHODIMP CUIEdit::get_wordWrap(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_bWordWrap;
	return S_OK;
}

STDMETHODIMP CUIEdit::put_wordWrap(VARIANT_BOOL newVal)
{
	m_bWordWrap = newVal;

	if (m_hWnd)
	{
		OnSize(TRUE);
		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::get_lineNumbers(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_bLineNumbers;
	return S_OK;
}

STDMETHODIMP CUIEdit::put_lineNumbers(VARIANT_BOOL newVal)
{
	m_bLineNumbers = newVal;

	if (m_hWnd)
	{
		OnSize(m_bWordWrap);
		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::FormatRange(long start, long len, long styleIndex, long* pstyleElementIndex)
{
/*
	offset highlight with 1 (so that always 0=selection and 1=text)
	this results in passing -1=selection and 0=text
*/

	styleIndex += 1;

	ATLASSERT(len >= 0);
	ATLASSERT(start+len <= GetTextLen());

	int nchunks = m_styleChunks.GetSize();
	SyntaxChunk* chunks = m_styleChunks.GetData();

	DWORD startSearch;
	/*
	if (pstyleElementIndex)
		startSearch = *pstyleElementIndex;
	else
		*/
		startSearch = 0;

	DWORD offset = 0;
	for (DWORD i = 0; i < nchunks; i++)
	{
		DWORD offsetend = offset+chunks[i].Length;
		if (offsetend > start) break;
		offset = offsetend;
	}

	int j = i;
	DWORD offset2 = offset;
	for ( ; j < nchunks; j++)
	{
		DWORD offsetend = offset2+chunks[j].Length;
		if (offsetend >= start+len) break;
		offset2 = offsetend;
	}

	if (i == j)	// Inserting a chunk in the middle of one single chunk
	{
		SyntaxChunk ck;

		m_styleChunks.InsertAt(i+1, ck, 2);

		m_styleChunks[i+1].Length = len;
		m_styleChunks[i+1].Element = styleIndex;
		m_styleChunks[i+1].Flags = 0;

		m_styleChunks[i+2].Length = m_styleChunks[i].Length-len - (start-offset);
		m_styleChunks[i+2].Element = m_styleChunks[i].Element;
		m_styleChunks[i+2].Flags = 0;

// Truncate this chunk
		m_styleChunks[i].Length = start-offset;

		if (pstyleElementIndex)
			*pstyleElementIndex = i+2;
	}
	else
	{
// Truncate this chunk
		m_styleChunks[i].Length = start-offset;

		SyntaxChunk ck;

		ck.Length = len;
		ck.Element = styleIndex;
		ck.Flags = 0;

		m_styleChunks[j].Length -= (start+len) - offset2;

		m_styleChunks.InsertAt(i+1, ck);

		// Remove any chunks inbetween
		m_styleChunks.RemoveAt(i+2, j-i-1);
	}

#ifdef _DEBUG
	{
		DWORD tlen = GetTextLen();

		DWORD total = 0;
		for (int i = 0; i < m_styleChunks.GetSize(); i++)
		{
			total += m_styleChunks[i].Length;
		}
		ATLASSERT(total == tlen);
	}
#endif

	return S_OK;
}

STDMETHODIMP CUIEdit::ClearFormatting()
{
	m_styleChunks.SetSize(0, 4096);

	SyntaxChunk ck;
	ck.Length = GetTextLen();
	ck.Element = 1;	// Text
	ck.Flags = 0;
	m_styleChunks.Add(ck);

	return S_OK;
}

STDMETHODIMP CUIEdit::NewStyle(long *pVal)
{
	if (pVal == NULL) return E_POINTER;

	SyntaxElement style = {-1, -1 };
	long index = m_styles.Add(style);

	*pVal = index-1;

	return S_OK;
}

STDMETHODIMP CUIEdit::SetStyle(/*[in]*/ long index, /*[in]*/ DWORD fgColor, /*[in]*/ DWORD bgColor)
{
	index += 1;

	if (index >= 0 && index < m_styles.GetSize())
	{
		m_styles[index].FgColor = fgColor;
		m_styles[index].BgColor = bgColor;

		if (m_hWnd)
		{
			InvalidateRect(&m_textArea, FALSE);
		}

		return S_OK;
	}
	else
		return E_FAIL;
}

STDMETHODIMP CUIEdit::get_cursorBox(RECT *pVal)
{
	if (pVal == NULL) return E_POINTER;

	POINT scrollPos;

	scrollPos.x = -m_textArea.left;
	scrollPos.y = -m_textArea.top;

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	scrollPos.x += scrollposX;
	scrollPos.y += scrollposY*m_ch;

	int colx = PointXFromColumn(m_line, m_col);

	(*pVal).left = colx - scrollPos.x;
	(*pVal).top = m_line*m_ch - scrollPos.y;
	(*pVal).right = (*pVal).left;
	(*pVal).bottom = (*pVal).top+m_ch;

	return S_OK;
}

STDMETHODIMP CUIEdit::get_font(IFontDisp **pVal)
{
	*pVal = m_pFont;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CUIEdit::put_font(IFontDisp *newVal)
{
	if (newVal == NULL) return E_INVALIDARG;

	m_pFont = newVal;

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HDC hDC = CreateCompatibleDC(NULL);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	SIZE size;
	GetTextExtentPoint32(hDC, " ", 1, &size);
	m_spaceWidth = size.cx;
	m_ch = size.cy;

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	if (m_hWnd)
	{
		InvalidateRect(&m_textArea, NULL);
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::SetSel(long nStartChar, long nEndChar, VARIANT_BOOL bNoScroll)
{
	//if (m_hWnd)	// ??
	{
		if (nEndChar == -1)
			nEndChar = GetTextLen();

		SetSelectionAndInvalidate(nStartChar, nEndChar);
		LocateCursor(nEndChar);	// ??
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::Clear()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::Cut()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::Copy()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::Paste()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::get_LineHeight(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_ch;
	return S_OK;
}

STDMETHODIMP CUIEdit::put_LineHeight(long newVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CUIEdit::CanPaste(unsigned long nFormat, VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = VARIANT_FALSE;

	if (nFormat == 0)
	{
		if (IsClipboardFormatAvailable(CF_TEXT) ||
			IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			*pVal = VARIANT_TRUE;
		}
	}
	else if (nFormat == CF_TEXT || nFormat == CF_UNICODETEXT)
	{
		*pVal = VARIANT_TRUE;
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::ReplaceText(long offset, long len, BSTR data, long datalen)
{
	CComObject<CEditUndoParent>* pParentUndo;

	if (m_undoManager)
	{
		CComObject<CEditUndoParent>::CreateInstance(&pParentUndo);
		pParentUndo->AddRef();
		m_undoManager->Open(pParentUndo);
	}

	if (len > 0)
	{
		if (m_undoManager)
		{
			CComObject<CEditUndoTyping>* pUndo;
			CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
			pUndo->m_pEdit = this;
			pUndo->m_kind = 1;
			pUndo->m_bRedo = true;
			pUndo->m_startCharPos = offset;
			pUndo->m_len = len;
			pUndo->m_text = SysAllocStringLen(GetTextData() + offset, len);

			m_undoManager->Add(pUndo);

			m_pRecentUndoTyping = NULL;
		}

		DeleteText(offset, len);
	}

	{
		InsertText(offset, data, datalen);

		if (m_undoManager)
		{
			CComObject<CEditUndoTyping>* pUndo;
			CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
			//pUndo->AddRef(); ??
			pUndo->m_pEdit = this;
			pUndo->m_kind = 1;
			pUndo->m_startCharPos = offset;
			pUndo->m_len = datalen;

			m_undoManager->Add(pUndo);
		}
	}

	if (m_undoManager)
	{
		m_undoManager->Close(pParentUndo, TRUE/*commit*/);
		pParentUndo->Release();
	}

//	BuildLines();

// ??
	ResetVScrollSize();
	ResetHScrollSize();
	InvalidateRect(NULL, TRUE);

	return S_OK;
}

STDMETHODIMP CUIEdit::GetSel(long *start, long *end)
{
	if (m_selEnd < m_selStart)	// No selection
	{
		*start = m_offset;
		*end = m_offset;
	}
	else
	{
		*start = m_selStart;
		*end = m_selEnd;
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::GetSelText(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocStringLen(GetTextData()+m_selStart, m_selEnd-m_selStart);
	return S_OK;
}

STDMETHODIMP CUIEdit::ReplaceSelText(BSTR data, long len)
{
	if (m_selEnd > m_selStart)
		return ReplaceText(m_selStart, m_selEnd-m_selStart, data, len);
	else
		return ReplaceText(m_offset, 0, data, len);
}

STDMETHODIMP CUIEdit::get_tabSize(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_tabSize;
	return S_OK;
}

STDMETHODIMP CUIEdit::put_tabSize(long newVal)
{
	m_tabSize = newVal;

	if (m_tabSize < 1) m_tabSize = 1;
	else if (m_tabSize > 99) m_tabSize = 99;

	if (m_hWnd)
	{
		InvalidateRect(&m_textArea);
	}

	return S_OK;
}

STDMETHODIMP CUIEdit::get_viewWhitespace(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::put_viewWhitespace(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::get_viewTabs(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::put_viewTabs(VARIANT_BOOL newVal)
{
	m_bShowTabs = newVal;
	if (m_hWnd)
	{
		InvalidateRect(&m_textArea);
	}
	return S_OK;
}

STDMETHODIMP CUIEdit::get_viewSpaces(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::put_viewSpaces(VARIANT_BOOL newVal)
{
	m_bShowSpace = newVal;
	if (m_hWnd)
	{
		InvalidateRect(&m_textArea);
	}
	return S_OK;
}

STDMETHODIMP CUIEdit::get_viewEOLs(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CUIEdit::put_viewEOLs(VARIANT_BOOL newVal)
{
	m_bShowEOL = newVal;
	if (m_hWnd)
	{
		InvalidateRect(&m_textArea);
	}
	return S_OK;
}

STDMETHODIMP CUIEdit::getCursorPosOffset(/*[out,retval]*/ long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_offset;
	return S_OK;
}

STDMETHODIMP CUIEdit::setCursorPosOffset(long offset)
{
	HideCursor();

	LocateCursor(offset);
	ScrollIntoView(m_line, m_col);

	ShowCursor();

	OnMovedCursor();

	return S_OK;
}

STDMETHODIMP CUIEdit::AutoList(IUIAutoListWindow **pVal)
{
	if (m_pAutoListMembersWindow == NULL)
	{
		CComObject<CAutoListMembersWindow>::CreateInstance(&m_pAutoListMembersWindow);
		m_pAutoListMembersWindow->AddRef();
	}

	*pVal = m_pAutoListMembersWindow;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CUIEdit::AutoListPopup()
{
	CRect crc;
	get_cursorBox(&crc);
	POINT cpt;
	cpt.x = crc.left;
	cpt.y = crc.bottom;
	ClientToScreen(&cpt);

	CRect rc(cpt.x, cpt.y, cpt.x+140, cpt.y+220);

	m_pAutoListMembersWindow->m_str = L"";

	m_autoListStartOffset = m_offset;
	m_autoListEndOffset = m_offset;

	m_pAutoListMembersWindow->Create(m_hWnd, cpt);
	m_pAutoListMembersWindow->SetWindowPos(NULL, 0, 0, 0, 0,
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);

//	_bstr_t value = m_pAutoListMembersWindow->GetString();

//	m_pAutoListMembersWindow->DestroyWindow();

	return S_OK;
}
