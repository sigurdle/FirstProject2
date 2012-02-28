#include "stdafx.h"
#include "LXUI2.h"
#include "TextEdit.h"
#include <stdio.h>

#include "UndoManager.h"

#include "AutoListMembersWindow.h"

#include <stdio.h>

#include "IFF/IFFParser.h"

//#include <functional>

#if AMIGA

#include "../amiga_header.h"

#define STREAM_READ	1
#define STREAM_WRITE	2

namespace System
{
namespace UI
{

ClipboardByteStream::ClipboardByteStream()
{
	m_pMsgPort = NULL;
	m_pIOReq = NULL;
	m_unit = -1;
}

ClipboardByteStream::ClipboardByteStream(DWORD ioFlags, LONG unit)
{
	// It must be either Read or Write, and cannot be both Read and Write
	if (ioFlags & STREAM_WRITE)
	{
		if (ioFlags & STREAM_READ)
			THROW(-1);
	}
	else if (!(ioFlags & STREAM_READ))
	{
		THROW(-1);
	}

	m_ioFlags = ioFlags;

	m_pMsgPort = NULL;
	m_pIOReq = NULL;
	m_unit = -1;

	if (unit < 0)
		THROW(-1);

	TRY
	{
		m_pMsgPort = CreateMsgPort();
		if (m_pMsgPort == NULL)
		{
			THROW(-1);
		}

		m_pIOReq = (IOClipReq*)CreateIORequest(m_pMsgPort, sizeof(IOClipReq));
		if (m_pIOReq == NULL)
		{
			THROW(-1);
		}
		
		m_ioError = OpenDevice("clipboard.device", unit, (IORequest*)m_pIOReq, 0);
		if (m_ioError != 0)
		{
			THROW(-1);
		}
	}
	CATCH(int e)
	{
		Free();
		THROW(e);
	}

	m_unit = unit;
	m_pIOReq->io_Offset = 0;
	m_pIOReq->io_ClipID = 0;
}

void ClipboardByteStream::Close()
{
	Free();
}

ClipboardByteStream::~ClipboardByteStream()
{
	Free();
}

void ClipboardByteStream::Free()
{
	if (m_pMsgPort)
	{
		if (m_pIOReq)
		{
			if (m_ioError == 0)
			{
				if (m_ioFlags & STREAM_READ)
				{
					// Tell the device we're finished reading by setting the offset past the end
					m_pIOReq->io_Offset = 0xFFFFFF;	// Some large value
					m_pIOReq->io_Command = CMD_READ;
					m_pIOReq->io_Length = 1;
					m_pIOReq->io_Data = NULL;
					char ioErr = DoIO((IORequest*)m_pIOReq);
				}
				else
				{
					// Tell the device we're finished writing
					m_pIOReq->io_Command = CMD_UPDATE;
					m_pIOReq->io_Length = 0;
					m_pIOReq->io_Data = NULL;
					char ioErr = DoIO((IORequest*)m_pIOReq);
				}

				CloseDevice((IORequest*)m_pIOReq);
			}
			DeleteIORequest((IORequest*)m_pIOReq);
			m_pIOReq = NULL;
		}
		DeleteMsgPort(m_pMsgPort);
		m_pMsgPort = NULL;
	}
}

LONGLONG ClipboardByteStream::GetSize()
{
	return -1;
}

System::IO::ISequentialByteStream* ClipboardByteStream::Clone() const
{
	ClipboardByteStream* p = new ClipboardByteStream(m_ioFlags, m_unit);
//	p->AddRef();
	return p;
}

ULONG ClipboardByteStream::Read(void* pv, ULONG cb)
{
	if (!(m_ioFlags & STREAM_READ))
		THROW(-1);

	m_pIOReq->io_Command = CMD_READ;
	m_pIOReq->io_Length = cb;
	m_pIOReq->io_Data = (char*)pv;

	char ioErr = DoIO((IORequest*)m_pIOReq);

	if (ioErr != 0)
		THROW(-1);

	return m_pIOReq->io_Actual;
};

ULONG ClipboardByteStream::Write(const void* pv, ULONG cb)
{
	if (!(m_ioFlags & STREAM_WRITE))
		THROW(-1);

	m_pIOReq->io_Command = CMD_WRITE;
	m_pIOReq->io_Length = cb;
	m_pIOReq->io_Data = (char*)pv;

	char ioErr = DoIO((IORequest*)m_pIOReq);

	if (ioErr != 0)
		THROW(-1);

	return m_pIOReq->io_Actual;
};

LONGLONG ClipboardByteStream::Seek(LONGLONG move, DWORD origin)
{
	LONG low = (LONG)move;

	if (origin == System::IO::STREAM_SEEK_SET)
		m_pIOReq->io_Offset = low;
	else if (origin == System::IO::STREAM_SEEK_CUR)
		m_pIOReq->io_Offset += low;
	else
		THROW(-1);

	return m_pIOReq->io_Offset;
}

}	// UI
}

#endif

/*
#if AMIGA

#define COLOR_HIGHLIGHT			1
#define COLOR_HIGHLIGHTTEXT	2
#define COLOR_WINDOW				3
#define COLOR_WINDOWTEXT		4

COLORREF GetSysColor(int nIndex)
{
	return 0;
}

#endif
  */

namespace System
{
namespace UI
{

CEditUndoParent::CEditUndoParent()
{
	m_flags = UNDOSTATE_NORMAL;
	m_state = 1;
}

CEditUndoParent::~CEditUndoParent()
{
	ASSERT(0);
#if 0
	while (!m_undoList.empty())
	{
		IUndoUnit* pUU = (IUndoUnit*)m_undoList.RemoveTail();
	//	pUU->Release();
	}
#endif
}

//////////////////////
// CEditUndoTyping

CEditUndoTyping::CEditUndoTyping()
{
	m_kind = 0;

	m_bRedo = false;
	m_pEdit = NULL;
	m_startCharPos = -1;
	m_len = 0;
	m_text = NULL;
}

CEditUndoTyping::~CEditUndoTyping()
{
	if (m_text)
	{
		delete m_text;
		m_text = NULL;
	}

	m_kind = 0;
}

void CEditUndoTyping::Do(/* [in] */ IUndoManager *pUndoManager)
{
	ASSERT(m_pEdit);

	if (m_kind == 1 ||		// Any character
		m_kind == ' ' ||
		m_kind == '\t' || 
		m_kind == '\n' || 
		m_kind == VKEY_DELETE ||
		m_kind == VKEY_BACK)
	{
		if (m_bRedo)
		{
		// Reinsert the text
			m_pEdit->InsertText(m_startCharPos, m_text, m_len);
		//	m_pEdit->BuildRLineOffsets();
		//	m_pEdit->BuildLineOffsets();

		// Free the text
			delete m_text;
			m_text = NULL;

			m_pEdit->LocateCursor(m_startCharPos + m_len);
		}
		else	// Undo
		{
		// Remember the text
			ASSERT(m_text == NULL);
			m_text = new WCHAR[m_pEdit->GetTextData() + m_startCharPos, m_len*sizeof(WCHAR)];//WCHAR[m_len];
			std::memcpy(m_text, m_pEdit->GetTextData() + m_startCharPos, m_len*sizeof(WCHAR));

		// Delete the text
			m_pEdit->DeleteText(m_startCharPos, m_len);
		//	m_pEdit->BuildRLineOffsets();
		//	m_pEdit->BuildLineOffsets();

			m_pEdit->LocateCursor(m_startCharPos);
		}
	}

//	m_pEdit->ResetHScrollSize();
//	m_pEdit->ResetVScrollSize();

	m_pEdit->Invalidate();
	//m_pEdit->UpdateWindow();

//	m_pEdit->OnChange();
	m_pEdit->OnMovedCursor();

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);
}

StringW* CEditUndoTyping::GetDescription()
{
	switch (m_kind)
	{
	case VKEY_DELETE:
	case VKEY_BACK:
		return WSTR("Deleting");

	case '\n':
		return WSTR("Line Break");

	default:
		return WSTR("Typing");
	}
}

#if 0
long CEditUndoTyping::GetUnitType(/* [out] */ CLSID *pClsid)
{
//	*pClsid = CLSID_NULL;	// TODO here
	return m_kind;
}
#endif

void CEditUndoTyping::OnNextAdd()
{
	m_pEdit->m_pRecentUndoTyping = NULL;
}

//////////////////////////////////
// CEditUndoParent

void CEditUndoParent::Add(/* [in] */ IUndoUnit  *pUU)
{
//	pUU->AddRef();

	if (m_state == 0)	// undo state
	{
		m_undoList.push_front(pUU);
	}
	else if (m_state == 1)	// redo state
	{
		m_undoList.push_front(pUU);
	}
}

long CEditUndoParent::GetParentState()
{
	return m_flags;
}

void CEditUndoParent::Do(/* [in] */ IUndoManager *pUndoManager)
{
	pUndoManager->Open(this);

	m_state = !m_state;

	list<IUndoUnit*>::iterator pos = m_undoList.begin();
	while (pos != m_undoList.end())
	{
		list<IUndoUnit*>::iterator pos2 = pos;
		IUndoUnit* pUU = *pos;
		++pos;

		pUU->Do(pUndoManager);
		m_undoList.erase(pos2);

	//	pUU->Release();
	}

	pUndoManager->Close(this, true);
}

StringW* CEditUndoParent::GetDescription()
{
	return WSTR("Typing");
}

void CEditUndoParent::Open(IParentUndoUnit *pPUU)
{
}

void CEditUndoParent::Close(IParentUndoUnit  *pPUU, /* [in] */ bool fCommit)
{
}

#if 0
long CEditUndoParent::GetUnitType(/* [out] */ CLSID  *pClsid)
{
	return 0;
}
#endif

void CEditUndoParent::OnNextAdd(void)
{
}

#if 0
STDMETHODIMP CEditUndoParent::FindUnit(/* [in] */ IUndoUnit *pUU)
{
	return S_OK;
}
#endif

SyntaxElement::SyntaxElement(LDraw::Color _FgColor, LDraw::Color _BgColor)
{
	FgColor = _FgColor;
	BgColor = _BgColor;
}

/////////////////////////////////////////////////////////////////////////////
// TextEdit

TextEdit::TextEdit()
{
	Init();
	set_TextDocument(new TextData());
}

TextEdit::TextEdit(StringW* text)
{
	Init();

	TextData* tdp = new TextData(text);
	//tdp->SetData(text->c_str(), text->Length());

	set_TextDocument(tdp);
	/*
	dynamic_cast<CEventTargetImpl*>(m_tdp)->addEventListener(WSTR("TextInserted"), this, false);
	dynamic_cast<CEventTargetImpl*>(m_tdp)->addEventListener(WSTR("TextDeleted"), this, false);
	dynamic_cast<CEventTargetImpl*>(m_tdp)->addEventListener(WSTR("TextChanged"), this, false);

	OnTextContentChanged();	// TODO remove
	*/
}

TextEdit::TextEdit(ITextData* tdp)
{
	Init();
	set_TextDocument(tdp);
}

TextEdit::~TextEdit()
{
}

void TextEdit::Init()
{
	m_pRecentUndoTyping = NULL;

	m_bMultiLine = false;

	m_bWordWrap = false;
	m_bLineNumbers = false;

//	m_bHorzSB = false;
//	m_bVertSB = false;
	m_bLeftBar = false;
	m_lborWidth = 0;
	m_border = 1;
	m_case = 0;

	m_line = 0;
	m_rline = 0;
	m_col = 0;
	m_rcol = 0;
	m_idealcolX = 0;
	m_offset = 0;

	m_bShowCursor = false;

	m_selStart = 0;
	m_selEnd = -1;
	m_initSel = -1;

	m_bShowTabs = false;
	m_bShowEOL = false;
	m_bShowSpace = false;
	m_tabSize = 3;

	m_dragging = 0;

	m_pAutoListMembersWindow = NULL;

	// TODO
#if 0
	AddAccel(Accel(FACCEL_CONTROL, 'z', ID_EDIT_UNDO));
	AddAccel(Accel(FACCEL_CONTROL, 'y', ID_EDIT_REDO));
	AddAccel(Accel(FACCEL_CONTROL, 'c', ID_EDIT_COPY));
	AddAccel(Accel(FACCEL_CONTROL, 'v', ID_EDIT_PASTE));
#endif

//	m_rlinesArr.SetSize(0, 100);
//	m_linesArr.SetSize(0, 100);

//	m_font = NULL;//font;	// TODO remove
//	ASSERT(m_font);

	ErrorCode hr;

//	m_ch = 0;//16;
	//m_spaceWidth = 16;

//	m_undoManager = NULL;
	m_undoManager = new UndoManager;	// ??

#if 0
	m_horz.CoCreateInstance(CLSID_UIScrollBar);
	m_horz->put_direction(0);

	m_vert.CoCreateInstance(CLSID_UIScrollBar);
	m_vert->put_direction(1);

	ITextDataPtr tdp;
	hr = tdp.CreateInstance(CLSID_TextData);
	if (FAILED(hr)) return E_NOINTERFACE;
#endif
#if 0
	ITextData* tdp;

	put_textDocument(tdp);
	m_tdp->put_data(L"");
#endif

	{
		// Selection
		{
			SyntaxElement style(LDraw::Color::White/*FGetSysColor(COLOR_HIGHLIGHTTEXT)*/, LDraw::Color::Blue/*GetSysColor(COLOR_HIGHLIGHT)*/ );
			m_styles.Add(style);
		}

		// Text
		{
			SyntaxElement style(LDraw::Color::Black/*GetSysColor(COLOR_WINDOWTEXT)*/, 0/*GetSysColor(COLOR_WINDOW)*/ );
			m_styles.Add(style);
		}
	}

	m_tdp = NULL;
	ClearFormatting();

	/*
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
	*/
}

#if 0
int TextEdit::FinalConstruct()
{
	HRESULT hr;

#if 0
	m_horz.CoCreateInstance(CLSID_UIScrollBar);
	m_horz->put_direction(0);

	m_vert.CoCreateInstance(CLSID_UIScrollBar);
	m_vert->put_direction(1);

	ITextDataPtr tdp;
	hr = tdp.CreateInstance(CLSID_TextData);
	if (FAILED(hr)) return E_NOINTERFACE;
#endif
	ITextData* tdp = NULL;

	put_textDocument(tdp);
	m_tdp->put_data(L"");

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
#endif

#if 0
void TextEdit::FinalRelease()
{
	ASSERT(m_hWnd == NULL);
	/*
	if (m_tdp)
	{
		IDispEventImpl<3, TextEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_tdp);
	}
	*/
}
#endif

#if 0
void TextEdit::handleEvent(Event* evt)
{
	/*
	if (handleAccelerator(evt))
		return;
		*/

	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
#if WIN32
		if (*type == L"querycursor")
		{
			evt->stopPropagation();

			QueryCursorEvent* q = dynamic_cast<QueryCursorEvent*>(evt);

			q->m_Cursor = new Cursor(MSWindows::LoadCursorA(NULL, _IDC_IBEAM));
#if 0
			q->m_Cursor->put_HotspotX(0);
			q->m_Cursor->put_HotspotY(0);

			DropShadow* p = new DropShadow;
			{
				Polyline* poly = new Polyline;
				poly->put_Fill(new SolidColorBrush(Color(255, 255, 255)));

				PointCollection* points = new PointCollection;
				points->m_items.Add(Point(0, 0));
				points->m_items.Add(Point(0, 21));
				points->m_items.Add(Point(4, 15));
				points->m_items.Add(Point(8, 23));
				points->m_items.Add(Point(10, 22));
				points->m_items.Add(Point(6, 13));
				points->m_items.Add(Point(12, 13));

				poly->put_Points(points);

				p->put_Content(poly);

				/*
				CLXUIRectangle* rect = new CLXUIRectangle;
				rect->put_RectangleWidth(new Length(20, Length::UnitAbsolute));
				rect->put_RectangleHeight(new Length(20, Length::UnitAbsolute));
				p->put_Content(rect);
				*/
			}
			q->m_Cursor->put_Visual(p);
#endif
		}
		else
#endif
			if (type == MouseEvent::mousedown)
		{
			evt->stopPropagation();
			OnLButtonDown(dynamic_cast<MouseEvent*>(evt));
		}
		else if (type == MouseEvent::mouseup)
		{
			evt->stopPropagation();
			OnLButtonUp(dynamic_cast<MouseEvent*>(evt));
		}
		else if (type == MouseEvent::mousemove)
		{
			evt->stopPropagation();
			OnMouseMove(dynamic_cast<MouseEvent*>(evt));
		}
		else if (*type == L"keydown")
		{
			evt->stopPropagation();
			OnKeyDown(dynamic_cast<KeyEvent*>(evt));
		}
		else if (*type == L"char")
		{
			evt->stopPropagation();
			OnChar(dynamic_cast<CharEvent*>(evt));
		}
		else if (*type == L"getfocus")
		{
			evt->stopPropagation();
			OnSetFocus();
		}
		else if (*type == L"killfocus")
		{
			evt->stopPropagation();
			OnKillFocus();
		}
		else if (*type == L"command")
		{
			CommandInvokeEvent* cmdEvt = dynamic_cast<CommandInvokeEvent*>(evt);

			switch (cmdEvt->get_Command())
			{
			case ID_EDIT_UNDO:
				{
					evt->stopPropagation();
					m_undoManager->UndoTo(NULL);
				}
				break;

			case ID_EDIT_REDO:
				{
					evt->stopPropagation();
					m_undoManager->RedoTo(NULL);
				}
				break;

			case ID_EDIT_COPY:
				{
					evt->stopPropagation();
					OnEditCopy();
				}
				break;

			case ID_EDIT_PASTE:
				{
					evt->stopPropagation();
					OnEditPaste();
				}
				break;
			}
		}
		else if (*type == L"TextInserted")
		{
			TextDataEvent* tdEvt = dynamic_cast<TextDataEvent*>(evt);
			OnTextInsertText(tdEvt->m_offset, tdEvt->m_len);
		}
		else if (*type == L"TextDeleted")
		{
			TextDataEvent* tdEvt = dynamic_cast<TextDataEvent*>(evt);
			OnTextDeleteText(tdEvt->m_offset, tdEvt->m_len);
		}
		else if (*type == L"TextChanged")
		{
			TextDataEvent* tdEvt = dynamic_cast<TextDataEvent*>(evt);
			OnTextContentChanged();
		}
	}

	FrameworkElement::handleEvent(evt);
}
#endif

void TextEdit::OnMouseDown(MouseButtonEventArgs* args)
{
	OnLButtonDown(args, true);
}

void TextEdit::OnLButtonDown(MouseButtonEventArgs* args, bool bStartDrag)
{
	double m_ch = GetFont()->GetSize();

	LDraw::PointD point = args->GetPosition(this);//ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());

#if _WINDOWS
	if (m_pAutoListMembersWindow)
	{
		m_pAutoListMembersWindow->DestroyWindow();
	//	m_pAutoListMembersWindow->Release();
		m_pAutoListMembersWindow = NULL;
	}
#endif

	if (!m_dragging)
	{
		Focus();

	//	CRect scrollRect = m_textArea;
	//	scrollRect.left = 0;

		if (true)//false)//scrollRect.PtInRect(point))
		{
			long scrollposX = 0;// m_horz->get_pos(&scrollposX);
			long scrollposY = 0;// m_vert->get_pos(&scrollposY);

			int line = ((point.Y/* - m_textArea.top*/)/m_ch) + scrollposY;
			int col;

			if (line < 0)
			{
				line = 0;
			}
			else
			{
				int maxline = m_linesArr.GetSize()-1;
				if (line > maxline) line = maxline;
			}

		//	HideCursor();

			if (bStartDrag)
			{
				m_dragging = true;
				CaptureMouse();
			}

			if (point.X < m_textArea.GetLeft())
			{
				LineDef* pLine = m_linesArr[line];

				col = 0;
				line++;

				m_pRecentUndoTyping = NULL;	// Stop inserting changes into this undounit
				LocateCursor(line, col);

				if (true)//(!(nFlags & MK_SHIFT))
				{
					m_initSel = pLine->m_offset;
					m_selStart = m_initSel;
					m_selEnd = m_selStart + pLine->m_lineLength;
				}
			}
			else
			{
				LDraw::PointD pt(point.X - m_textArea.GetLeft()/* + scrollposX*/, point.Y);// = new Point;

				m_idealcolX = pt.X;
				col = ColumnFromPointX(line, m_idealcolX);

				m_pRecentUndoTyping = NULL;	// Stop inserting changes into this undounit
				LocateCursor(line, col);

				if (false)//nFlags & MK_CONTROL)
				{
					//	SelectWordAt(line, col);
				}

				if (bStartDrag)
				{
					if (true)//!(nFlags & MK_SHIFT))
					{
						ClearSelectionAndInvalidate();

						m_initSel = m_offset;
						m_selStart = m_initSel;
						m_selEnd = m_initSel;
					}
				}
			}

		//	ShowCursor();

			OnMouseMove(args);
		}
	}
}

#if 0
LRESULT TextEdit::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	Fire_DblClick(m_offset, m_rline, m_rcol);
#endif
	return 0;
}
#endif

#if 0
LRESULT TextEdit::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if _WINDOWS
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	OnMouseMove(nFlags, point);
#endif
	return 0;
}
#endif

void TextEdit::OnMouseMove(MouseEventArgs* args)
{
	double m_ch = GetFont()->GetSize();

	LDraw::PointD point = args->GetPosition(this);//ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());

	if (m_dragging)
	{
	//	MessageBeep(~0);

		int scrollposX = 0;// m_horz->get_pos(&scrollposX);
		int scrollposY = 0;// m_vert->get_pos(&scrollposY);

		int line = ((point.Y/* - m_textArea.top*/)/m_ch) + scrollposY;
		//int vcol = ((point.x - m_textArea.left)/m_cw) + scrollposX;

		if (line < 0) line = 0;
		else if (line > m_linesArr.GetSize()-1) line = m_linesArr.GetSize()-1;

		m_idealcolX = point.X-m_textArea.GetLeft();// + scrollposX;
		int col = ColumnFromPointX(line, m_idealcolX);//VColumn2Column(line, vcol);

		if (true || (line != m_line) || (col != m_col))
		{
#if 0
			HideCursor();
#endif
			LocateCursor(line, col);

			SetSelectionAndInvalidate(m_initSel, m_offset);

			ScrollIntoView(m_line, m_col);

			ShowCursor();
			Invalidate();
		}
	}
}

void TextEdit::OnMouseUp(MouseButtonEventArgs* evt)
{
	OnLButtonUp();
}

void TextEdit::OnLButtonUp()
{
	if (m_dragging)
	{
		ReleaseMouseCapture();
		m_dragging = 0;

		if (m_selStart == m_selEnd)
		{
			m_initSel = -1; m_selStart = 0; m_selEnd = -1;
		}

#if 0
		Invalidate();//Rect(&m_textArea);
#endif
	}
}

const WCHAR* TextEdit::GetTextData()
{
	ASSERT(m_tdp != NULL);
	return m_tdp->m_textData->GetData();
}

unsigned int TextEdit::GetTextLen() const
{
	ASSERT(m_tdp != NULL);
	return m_tdp->m_textData->GetLen();
}

void TextEdit::ShowCursor()
{
	if (!m_bShowCursor)
	{
		ToggleCursor();
	}
}

void TextEdit::HideCursor()
{
	if (m_bShowCursor)
	{
		ToggleCursor();
	}
}

void TextEdit::ToggleCursor()
{
	m_bShowCursor = !m_bShowCursor;
	Invalidate();

#if 0
	HDC hDC = GetDC();
	int state = SaveDC(hDC);
	IntersectClipRect(hDC, m_textArea.left, m_textArea.top, m_textArea.right, m_textArea.bottom);

	DrawCursor(hDC);

	RestoreDC(hDC, state);
	ReleaseDC(hDC);
#endif
}

void TextEdit::DrawCursor(Graphics* pGraphics)
{
//	CPoint scrollPos;

//	scrollPos.x = m_textArea.left;
//	scrollPos.y = m_textArea.top;

//	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
//	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

//	scrollPos.x -= scrollposX;//*m_cw;
//	scrollPos.y -= scrollposY*m_ch;

#if 0
	CPoint oldOrg;
	SetViewportOrgEx(hDC, scrollPos.x, scrollPos.y, &oldOrg);
#endif

	//int vcol = Column2VColumn(m_line, m_col);
	int colx = PointXFromColumn(m_line, m_col);

	double m_ch = GetFont()->GetSize();

	LDraw::RectD crect(colx, m_line*m_ch, 1, m_ch);

#if 0
	int oldr2 = SetROP2(hDC, R2_NOTXORPEN);
	HPEN pOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
	HBRUSH pOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));
#endif

	__release<LDraw::SolidBrush> brush = new LDraw::SolidBrush(LDraw::Color::Black);
	pGraphics->FillRectangle(brush, crect);

#if 0
	SelectObject(hDC, pOldBrush);
	SelectObject(hDC, pOldPen);
	SetROP2(hDC, oldr2);

	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
#endif
}

void TextEdit::CreateSyntaxFonts()
{
//	m_nFonts = 0;

//	int stylesArray[64] = {0};




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

long TextEdit::GetTextOffset()
{
	return m_offset;
}

long TextEdit::get_line()
{
	return m_rline;
}

long TextEdit::get_column()
{
	return m_rcol;
}

#if 0

long TextEdit::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
#endif

int TextEdit::PointXFromColumn(int line, int col)
{
	uint offset = m_linesArr[line]->m_offset;
	const WCHAR* data = GetTextData();
	int linelen = m_linesArr[line]->m_lineLength;

	LDraw::Font* pFont = GetFont();

	//LDraw::GraphicsO graphics;

	double m_spaceWidth = LDraw::Graphics2D::MeasureString(" ", 1, pFont, LDraw::SmoothingModeNone);

	int x = 0;

	int i = offset;

	int vcol = 0;

	for (int j = 0; j < col; j++)
	{
		WCHAR c = data[i++];

		if (c == '\t')
		{
			int spaces = m_tabSize - (vcol % m_tabSize);
			vcol += spaces;

			x += spaces*m_spaceWidth;
		}
		else
		{
			vcol++;

			LDraw::SizeD size;
			size.Width = LDraw::Graphics2D::MeasureString(&c, 1, pFont, LDraw::SmoothingModeNone);
			x += size.Width;
		}
	}

	return x;
}

int TextEdit::ColumnFromPointX(int line, int x)
{
	uint offset = m_linesArr[line]->m_offset;
	const WCHAR* data = GetTextData();
	int linelen = m_linesArr[line]->m_lineLength;

	LDraw::Font* pFont = GetFont();
	//LDraw::GraphicsO graphics;
	double m_spaceWidth = LDraw::Graphics2D::MeasureString(" ", 1, pFont, LDraw::SmoothingModeNone);

	int i = offset;

	int col = 0;
	int vcol = 0;

	while (x > 0)
	{
		if (col >= linelen)
			break;

		WCHAR c = data[i++];

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

			LDraw::SizeD size;
			size.Width = LDraw::Graphics2D::MeasureString(&c, 1, pFont, LDraw::SmoothingModeNone);
/*
#if _WINDOWS
			GetTextExtentPoint32(hDC, &c, 1, &size);
#else
			printf("TODO\n");
#endif
*/
			width = size.Width;
		}

		if (x <= width/2) break;

		x -= width;

		col++;
	}

	/*
#if _WINDOWS
	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);
#endif
	*/

	return col;
}

void TextEdit::MoveCursorPageUp()
{
	ASSERT(0);
#if 0
	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	if (m_line > scrollposY)	// Move to top of page
	{
		LocateCursor(scrollposY, m_col);
	}
	else	// Scroll up one page
	{
		int visibleLines = m_textArea.Height() / m_ch;

		LocateCursor(m_line - visibleLines, m_col);
	}
#endif
}

void TextEdit::MoveCursorPageDown()
{
	ASSERT(0);
#if 0
	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

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
#endif
}

void TextEdit::MoveCursorLeft()
{
	if (m_offset > 0)
	{
		LocateCursor(m_offset-1);
#if 0
		m_idealcolX = PointXFromColumn(m_line, m_col);
#endif

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

void TextEdit::MoveCursorRight()
{
	if (m_offset < GetTextLen())
	{
		LocateCursor(m_offset+1);
#if 0
		m_idealcolX = PointXFromColumn(m_line, m_col);
#endif

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

void TextEdit::MoveCursorDown()
{
	if (m_line < m_linesArr.GetSize()-1)
	{
		int col = ColumnFromPointX(m_line+1, m_idealcolX);
		LocateCursor(m_line+1, col);

		OnMovedCursor();
	}
}

void TextEdit::MoveCursorUp()
{
	if (m_line > 0)
	{
		int col = ColumnFromPointX(m_line-1, m_idealcolX);
		LocateCursor(m_line-1, col);

	//	TRACE("LINE:%d\n", m_line);

		OnMovedCursor();
	}
}

void TextEdit::MoveCursorBegLine()
{
	LocateCursor(m_linesArr[m_line]->m_offset);//m_offset -= m_col;
	m_idealcolX = PointXFromColumn(m_line, m_col);

	OnMovedCursor();
}

void TextEdit::MoveCursorEndLine()
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

void TextEdit::InsertChar(WCHAR ch)
{
	//ASSERT(ch < 256);
	InsertText(m_offset, &ch, 1);

	/*
	BuildRLineOffsets();
	BuildLineOffsets();
  */
}

void TextEdit::DeleteChar(int offset, int len)
{
	DeleteText(offset, len);
/*
	BuildRLineOffsets();
	BuildLineOffsets();
	*/
}

#if 0
int TextEdit::GetMaxLineLength()
{
	LDraw::Graphics graphics;

	LDraw::Font* pFont = GetFont();

	int nlines = m_linesArr.size();
	LineDef** pLines = m_linesArr.begin();

	int maxx = 0;

	for (int i = 0; i < nlines; i++)
	{
		const WCHAR* data = GetTextData() + pLines[i]->m_offset;
		int len = pLines[i]->m_lineLengthR;
		int n = 0;

		int linemaxx = 0;

		for (int i = 0; i < len; i++)
		{
			TCHAR c = data[i];

			LDraw::SizeD size;

			if (c == '\t')
			{
				int spaces = m_tabSize - (n % m_tabSize);
				LDraw::SizeD size2;
				size2.Width = graphics.MeasureString(" ", 1, pFont);
				size.Width = size2.Width*spaces;
				n += spaces;
			}
			else
			{
				size.Width = graphics.MeasureString(&c, 1, pFont);
				n++;
			}

			linemaxx += size.Width;
		}

		if (linemaxx > maxx)
			maxx = linemaxx;
	}

	return maxx;
}
#endif

#if 0
void TextEdit::ResetHScrollSize()
{
	int maxx = GetMaxLineLength();
#if 0//_WINDOWS
	m_horz->SetInfo(0, maxx, m_textArea.Width());
#endif
}

void TextEdit::ResetVScrollSize()
{
#if 0//_WINDOWS
	m_vert->SetInfo(
		0,
		m_linesArr.GetSize()-1,
		(m_textArea.Height())/m_ch);
#endif
}
#endif

void TextEdit::ScrollIntoView(int line, int col)
{
#if 0
	ASSERT(line < m_linesArr.size());

	long scrollposX = 0; //m_horz->get_pos(&scrollposX);
	long scrollposY = 0; //m_vert->get_pos(&scrollposY);

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
		ASSERT(0);
#if 0
	// Scroll text area
		ScrollWindow(-scrollX, -scrollY*m_ch, &m_textArea, &m_textArea);

		if (scrollY)	// Scroll left border
		{
			CRect lborder(0, m_textArea.top, m_textArea.left, m_textArea.bottom);
			ScrollWindow(-scrollX, -scrollY*m_ch, &lborder, &lborder);
		}

		m_vert->put_pos(scrollposY+scrollY);
		m_horz->put_pos(scrollposX+scrollX);
#endif
	}
#endif
}

void TextEdit::OnKeyDown(KeyEventArgs* args)
{
	int nKey = args->m_key;
	//int lKeyData = lParam;

#if 0
	KillTimer(1);
	HideCursor();
#endif

	bool bShift = false;//evt->bShift;//(GetAsyncKeyState(VK_SHIFT) & (1<<15));

	switch (nKey)
	{
		/*
	case VK_RETURN:
		{
		}
		break;
		*/

	case VKEY_LEFT:
	case VKEY_RIGHT:
	case VKEY_UP:
	case VKEY_DOWN:
	case VKEY_HOME:
	case VKEY_END:
	case VKEY_PRIOR:
	case VKEY_NEXT:
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
				case VKEY_LEFT:
					{
						if (bShift || m_initSel == -1)
						{
							MoveCursorLeft();
						}
						else
						{
							LocateCursor(m_selStart);
							OnMovedCursor();
						}
						//MoveCursorLeft();

#if _WINDOWS
						if (m_pAutoListMembersWindow)
						{
							if (m_offset < m_autoListStartOffset)
							{
								m_pAutoListMembersWindow->DestroyWindow();
							//	m_pAutoListMembersWindow->Release();
								m_pAutoListMembersWindow = NULL;
							}
						}
#endif
					}
					break;

				case VKEY_RIGHT:
					{
						//						MoveCursorRight();
						if (bShift || m_initSel == -1)
						{
							MoveCursorRight();
						}
						else
						{
							LocateCursor(m_selEnd);
							OnMovedCursor();
						}

#if _WINDOWS
						if (m_pAutoListMembersWindow)
						{
							if (m_offset > m_autoListEndOffset)
							{
								m_pAutoListMembersWindow->DestroyWindow();
							//	m_pAutoListMembersWindow->Release();
								m_pAutoListMembersWindow = NULL;
							}
						}
#endif
					}
					break;

				case VKEY_UP:
					{
#if _WINDOWS
						if (m_pAutoListMembersWindow)
						{
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->GetCurSel()-1);
						}
						else
#endif
						{
							if (!bShift && m_initSel > -1)
							{
								LocateCursor(m_selStart);
								OnMovedCursor();
							}
							MoveCursorUp();
						}
					}
					break;

				case VKEY_DOWN:
					{
#if _WINDOWS
						if (m_pAutoListMembersWindow)
						{
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->GetCurSel()+1);
						}
						else
#endif
						{
							if (!bShift && m_initSel > -1)
							{
								LocateCursor(m_selEnd);
								OnMovedCursor();
							}
							MoveCursorDown();
						}
					}
					break;

				case VKEY_PRIOR:
					{
#if _WINDOWS
						if (m_pAutoListMembersWindow)
						{
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->GetCurSel()-(m_pAutoListMembersWindow->GetVisibleLines()-1));
						}
						else
#endif
						{
							MoveCursorPageUp();
						}
					}
					break;

				case VKEY_NEXT:
					{
#if _WINDOWS
						if (m_pAutoListMembersWindow)
						{
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->GetCurSel()+(m_pAutoListMembersWindow->GetVisibleLines()-1));
						}
						else
#endif
						{
							MoveCursorPageDown();
						}
					}
					break;

				case VKEY_HOME:	MoveCursorBegLine(); break;
				case VKEY_END:	MoveCursorEndLine(); break;
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

	case VKEY_DELETE:
#if WIN32
		if (m_pAutoListMembersWindow)
		{
			m_pAutoListMembersWindow->DestroyWindow();
		//	m_pAutoListMembersWindow->Release();
			m_pAutoListMembersWindow = NULL;
		}
#endif
		// Let through

	case VKEY_BACK:
		{
			if (m_selEnd > m_selStart)	// Delete Selection
			{
				DeleteSelection();
			}
			else
			{
				switch (nKey)
				{
				case VKEY_BACK:
					{
#if _WINDOWS
						if (m_pAutoListMembersWindow)
						{
							m_autoListEndOffset--;

							//m_autoListEndOffset = m_offset;
							m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->FindMatch(&GetTextData()[m_autoListStartOffset], m_autoListEndOffset-m_autoListStartOffset));
						}
#endif

						if (m_offset > 0)
						{
							long undokind = VKEY_BACK;

							if (m_undoManager)
							{
								if (m_pRecentUndoTyping == NULL || m_pRecentUndoTyping->m_kind != undokind)
								{
									CEditUndoTyping* pUndo = new CEditUndoTyping;
								//	CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
								//	pUndo->AddRef();

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
									WCHAR* text = new WCHAR[m_pRecentUndoTyping->m_len+1];
									//memcpy(text, m_pRecentUndoTyping->m_text, (m_pRecentUndoTyping->m_len+1)*2);

									std::memcpy(text+1, m_pRecentUndoTyping->m_text, m_pRecentUndoTyping->m_len*sizeof(WCHAR));
									text[0] = GetTextData()[m_offset-1];

									delete m_pRecentUndoTyping->m_text;
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

				case VKEY_DELETE:
					{
						if (m_offset < GetTextLen())
						{
							long undokind = VKEY_DELETE;

							if (m_undoManager)
							{
								if (m_pRecentUndoTyping == NULL || m_pRecentUndoTyping->m_kind != undokind)
								{
									CEditUndoTyping* pUndo = new CEditUndoTyping;
									//CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
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
									WCHAR* text = new WCHAR[m_pRecentUndoTyping->m_len+1];
									std::memcpy(text, m_pRecentUndoTyping->m_text, m_pRecentUndoTyping->m_len*sizeof(WCHAR));
									text[m_pRecentUndoTyping->m_len] = GetTextData()[m_offset];

									delete m_pRecentUndoTyping->m_text;
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
		//	InvalidateMeasure();

		//	InvalidateRect(NULL, TRUE);
		}
		break;

	default:
#if 0
		SetTimer(1, 400);
		ShowCursor();
#endif
		return;// FALSE;
	}

//	ScrollIntoView(m_line, m_col);

//	UpdateWindow();

#if 0
	SetTimer(1, 400);
	ShowCursor();
#endif
	CalcLineCol(m_offset);	// Recalculate: m_line/m_col
	if (nKey == VKEY_LEFT || nKey == VKEY_RIGHT)
	{
		m_idealcolX = PointXFromColumn(m_line, m_col);
	}

	Invalidate();
}

//void TextEdit::OnChar(RoutedEventArgs* evt)
void TextEdit::OnTextInput(TextCompositionEventArgs* args)
{
	StringW* text = args->get_Text();//evt->cCharCode;

	InsertText(m_offset, text->begin(), text->Length());
#if 0
//	int lKeyData = lParam;

	uint16 ch = nKey;
	if (ch == 8) return;	// We ignore backspace here, since it's handled in OnKeyDown
	if (ch == '\r') ch = '\n';

	if (ch == '\n')
	{
#if WIN32
		if (m_pAutoListMembersWindow)
		{
			StringW* str = m_pAutoListMembersWindow->GetStringAt(m_pAutoListMembersWindow->GetCurSel());

			m_pAutoListMembersWindow->DestroyWindow();
		//	m_pAutoListMembersWindow->Release();
			m_pAutoListMembersWindow = NULL;

			ReplaceText(m_autoListStartOffset, m_autoListEndOffset-m_autoListStartOffset, str->c_str(), str->Length());

			LocateCursor(m_autoListStartOffset + str->Length());

			return;
		}
#endif
	}

	if (ch == '\n')
	{
		if (!m_bMultiLine)	// Don't allow new lines unless multiline edit
		{
#if 0
			Fire_OnChar((WCHAR)ch);	// ?
#endif
			return;
		}
	}

//	HideCursor();

	if (m_case == -1)			ch = std::tolower(ch);
	else if (m_case == 1)	ch = std::toupper(ch);

	int undokind;

	if (ch == ' ')			undokind = ' ';
	else if (ch == '\t')	undokind = '\t';
	else if (ch == '\n')	undokind = '\n';
	else						undokind = 1;	// Any other character

	CEditUndoParent* pParentUndo = NULL;//CEditUndoParent* pParentUndo = NULL;

	if (m_selEnd > m_selStart)	// Delete Selection
	{
		if (m_undoManager)
		{
			pParentUndo = new CEditUndoParent;
			//pParentUndo->AddRef();	// ??

			m_undoManager->Open(pParentUndo);
		}

		DeleteSelection();
	}

	if (m_undoManager)
	{
		if (m_pRecentUndoTyping == NULL || m_pRecentUndoTyping->m_kind != undokind)
		{
			CEditUndoTyping* pUndo = new CEditUndoTyping;
		//	CComObject<CEditUndoTyping>::CreateInstance(&pUndo);
		//	pUndo->AddRef();	// ??

			pUndo->m_kind = undokind;
			pUndo->m_bRedo = false;
			pUndo->m_pEdit = this;
			pUndo->m_startCharPos = m_offset;

			m_undoManager->Add(pUndo);
			m_pRecentUndoTyping = pUndo;
		//	pUndo->Release();
		}

		if (m_pRecentUndoTyping)
		{
			m_pRecentUndoTyping->m_len++;
		}

		if (pParentUndo)
		{
			m_undoManager->Close(pParentUndo, true/*commit*/);
		//	pParentUndo->Release();

			m_pRecentUndoTyping = NULL;
		}
	}

	InsertChar(ch);
	//MoveCursorRight();
	LocateCursor(m_offset+1);

	// TODO, remove
	{
		Event* evt = new Event;
		evt->InitEvent(WSTR("changed"), true, false);
		dispatchEvent(evt);
	}

	{
		Event* evt = new Event;
		evt->InitEvent(WSTR("propertychanged"), true, false);
		dispatchEvent(evt);
	}

//	InvalidateMeasure();

#if WIN32
	if (m_pAutoListMembersWindow)
	{
		m_autoListEndOffset++;// = m_offset;
		m_pAutoListMembersWindow->SetCurSel(m_pAutoListMembersWindow->FindMatch(&GetTextData()[m_autoListStartOffset], m_autoListEndOffset-m_autoListStartOffset));
	}
#endif

//	OnMovedCursor();
#if 0
	Fire_OnChar((WCHAR)wParam);
#endif
//	OnChange();

/*
	ResetHScrollSize();	// hm.. not very efficient to do this all the time
	if (ch == '\n') ResetVScrollSize();

	ScrollIntoView(m_line, m_col);

	InvalidateRect(NULL, TRUE);
*/
//	UpdateWindow();

//	ShowCursor();
//	Invalidate();
#endif
}

void TextEdit::BuildRLineOffsets()
{
#if 0
	for (int i = 0; i < m_rlinesArr.GetSize(); i++)
	{
		delete m_rlinesArr[i];
	}
	m_rlinesArr.RemoveAll();

	const WCHAR* data = GetTextData();
	uint length = GetTextLen();

	uint offset = 0;

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
			if (*data == '\n') break;
			offset++;
			data++;
		}

		len += offset-startoffset;

		if (offset < length)
		{
			ASSERT(*data == '\n');

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
#endif

	m_nDispLines.resize(m_tdp->GetNumberOfLines());
}

#if 0
void TextEdit::BuildLineOffsets(double width)
{
	int i;

// Display lines (wrapped or not)
	for (i = 0; i < m_linesArr.size(); i++)
	{
		delete m_linesArr[i];
	}

	if (!m_bWordWrap)
	{
		m_linesArr.resize(m_rlinesArr.size());

		for (int i = 0; i < m_rlinesArr.size(); i++)
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
		m_linesArr.clear();

		LDraw::Graphics graphics;

		LDraw::Font* pFont = GetFont();

		const WCHAR* data = GetTextData();
		double cx = width;

		for (int i = 0; i < m_rlinesArr.size(); i++)
		{
			DWORD offset = m_rlinesArr[i]->m_offset;
			int lineLength = m_rlinesArr[i]->m_lineLength;

			m_rlinesArr[i]->m_nDispLines = 1;

			LineDef* pLine = new LineDef;
			pLine->m_offset = offset;
			m_linesArr.push_back(pLine);

			int len = 0;
			int x = 0;
			int li = 0;

			while (li < lineLength)
			{
				int wordlen = 0;

				const WCHAR* p = data + offset;

				while ((li+wordlen < lineLength) && !isspace(*p))
				{
					p++;
					wordlen++;
				}

				while ((li+wordlen < lineLength) && isspace(*p))
				{
					p++;
					wordlen++;
				}

				LDraw::SizeF size(0,0);
				if (wordlen > 0)
				{
					for (int i = 0; i < wordlen; i++)
					{
						WCHAR c = data[offset+i];

						if (c == '\t')
						{
							int spaces = m_tabSize - (len % m_tabSize);
							LDraw::SizeD size2;
							size2.Width = graphics.MeasureString(" ", 1, pFont);//GetTextExtentPoint32(hDC, " ", 1, &size2);

							size.Width += size2.Width * spaces;
						}
						else
						{
							LDraw::SizeD size2;
							size2.Width = graphics.MeasureString(&c, 1, pFont);////GetTextExtentPoint32(hDC, &c, 1, &size2);

							size.Width += size2.Width;
						}
					}
				}

				if (x > 0 && x+size.Width > cx)
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
					m_linesArr.push_back(pLine);
				}

				x += size.Width;
				len += wordlen;
				li += wordlen;
				offset += wordlen;
			}

			pLine->m_lineLength = len;
			pLine->m_lineLengthR = len + (m_rlinesArr[i]->m_lineLengthR - m_rlinesArr[i]->m_lineLength);
		}
	}
}
#endif

/*
void TextEdit::Update()
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

void TextEdit::OnMovedCursor()
{
//	CRect rect(0, m_textArea.bottom, 60, m_textArea.bottom+16);
//	InvalidateRect(&rect);
#if 0
	Invalidate();
#endif

#if 0
	Fire_MoveCursor(m_offset);
#endif
}

void TextEdit::CalcLineCol(int offset)
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

	ASSERT(0);
}

void TextEdit::CalcRLineCol(int offset)
{
	int nlines = m_tdp->GetNumberOfLines();

	for (int i = nlines-1; i >= 0; i--)
	{
		if (offset >= m_tdp->GetLine(i)->m_offset)
		{
			m_rline = i;
			m_rcol = offset - m_tdp->GetLine(i)->m_offset;
			return;
		}
	}

	ASSERT(0);
}

void TextEdit::LocateCursor(int offset)
{
	m_offset = offset;

//	if (m_hWnd)
	{
//		CalcLineCol(m_offset);
		CalcRLineCol(m_offset);
	}
}

void TextEdit::LocateCursor(int line, int col)
{
	if (line < 0) line = 0;
	else if (line > m_linesArr.GetSize()-1) line = m_linesArr.GetSize()-1;

	int lineLength = m_linesArr[line]->m_lineLength;

	if (col < 0) col = 0;
	else if (col > lineLength) col = lineLength;

	int offset = m_linesArr[line]->m_offset + col;

	m_offset = offset;
	ASSERT(m_offset >= 0 && m_offset <= GetTextLen());

	m_line = line;
	m_col = col;

	CalcRLineCol(m_offset);

	OnMovedCursor();
}

void TextEdit::ClearSelectionAndInvalidate()
{
	if (m_selEnd > m_selStart)	// Clearing previous selection
	{
	//	InvalidateRange(m_selStart, m_selEnd);
		Invalidate();

		m_initSel = -1;
		m_selStart = 0;
		m_selEnd = -1;
	}
}

void TextEdit::SetSelectionAndInvalidate(int start, int end)
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
//	if (m_hWnd)
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
			istart = MIN(m_selStart, oldSelStart);
	#if 1	// TODO
			if (istart < 0) istart = 0;
	#endif
			iend = MAX(m_selEnd, oldSelEnd);
		}

		InvalidateRange(istart, iend);
	}
}

void TextEdit::InvalidateRange(int startchar, int endchar)
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

void TextEdit::InvalidateLine(int line)
{
#if 0//_WINDOWS
//	if (m_hWnd)
	{
		int lcol = m_linesArr[line]->m_lineLengthR;//GetLineLength(line);
		//int endvcol = Column2VColumn(line, lcol);
		int endpx = PointXFromColumn(line, lcol);

		long scrollposY = 0; m_vert->get_pos(&scrollposY);

		int y = (line - scrollposY)*m_ch;
		int x = m_textArea.left;
		int endx = x + endpx + 1;//m_cw;

		CRect lineRect(x, y, endx+1, y+m_ch+1);
		InvalidateRect(&lineRect);
	}
#endif
}

void TextEdit::OnDrawLineNumber(Graphics* pGraphics, const LDraw::RectD& rc, int nline)
{
	char str[64];
	int len = sprintf_s(str, "%d", nline+1);
	pGraphics->DrawString(str, len, GetFont(), LDraw::PointF(rc.X, rc.Y), new LDraw::SolidBrush(LDraw::Color::Black));
//	DrawText(hDC, str, len, &rc, DT_SINGLELINE | DT_VCENTER | DT_RIGHT);
//	pGraphics->ReleaseHDC(hDC);
}

void TextEdit::OnRender(Graphics* pGraphics)
{
//	printf("%f,%f\n", m_computedWidth, m_computedHeight);
	//LDraw::RectD client(0, 0, , );// = GetClientRect();

	{
//	LDraw::SolidBrush bgBrush(LDraw::Color(255, 255, 255));
//	pGraphics->FillRectangle(&bgBrush, 0, 0, m_computedSize.Width, m_computedSize.Height);
	}

#if 0
	if (m_bHorzSB && m_bVertSB)
	{
		//pGraphics->FillRectangle(m_textArea.right, m_textArea.bottom, client.right-m_textArea.right-1, client.bottom-m_textArea.bottom-1, GetSysColor(COLOR_BTNFACE));
	}
#endif

	LDraw::Font* pFont = GetFont();
	double m_ch = pFont->GetSize();

	double m_spaceWidth = pGraphics->MeasureString(" ", 1, pFont/*, LDraw::PointF(x, y), stringFormat, &bounds*/);

	//if (IntersectClipRect(hDC, m_border, m_textArea.top, m_textArea.right, m_textArea.bottom) > NULLREGION)
	{
		/*
		{
			LDraw::RectI lborder(0, m_textArea.top, m_textArea.left, m_textArea.Height());
			pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(210, 210, 210)), lborder);
		}
		*/

		if (m_bLineNumbers)
		{
			long scrollposY = 0;
#if 0
			m_vert->get_pos(&scrollposY);
#endif

		//	POINT oldOrg;
		//	SetViewportOrgEx(hDC, 0, m_textArea.top - scrollposY*m_ch, &oldOrg);
		//	int oldBkMode = SetBkMode(hDC, TRANSPARENT);
			pGraphics->TranslateTransform(0, 0);//m_textArea.top - scrollposY*m_ch);

			int y = 0;

			{
			//	LDraw::Graphics graphics(hDC);

				unsigned int nlines = m_tdp->GetNumberOfLines();

				for (unsigned int i = 0; i < nlines; i++)
				{
					LDraw::RectD rc(0, y, 4*m_spaceWidth, m_ch);

					OnDrawLineNumber(pGraphics, rc, i);

			//		y += m_rlinesArr[i]->m_nDispLines * m_ch;
					y += m_nDispLines[i] * m_ch;
				}
			}

		//	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		//	SetBkMode(hDC, oldBkMode);

			pGraphics->TranslateTransform(m_textArea.GetLeft(), 0);
		}

		//RECT  irect;
		//if (IntersectClipRect(hDC, m_textArea.left, m_textArea.top, m_textArea.right, m_textArea.bottom) > NULLREGION/*IntersectRect(&irect, &clip, &m_textArea)*/)
		{
			/*
			CPoint scrollPos;

			long scrollposX = 0;// m_horz->get_pos(&scrollposX);
			long scrollposY = 0;// m_vert->get_pos(&scrollposY);

			scrollPos.x = m_textArea.left;
			scrollPos.y = m_textArea.top;

			scrollPos.x -= scrollposX;//*m_cw;
			scrollPos.y -= scrollposY*m_ch;

		//	POINT oldOrg;
		//	SetViewportOrgEx(hDC, scrollPos.x, scrollPos.y, &oldOrg);
			pGraphics->TranslateTransform(scrollPos.x, scrollPos.y);
			*/

#if 0
			CRect clip;
			GetClipBox(hDC, &clip);
#endif
			const WCHAR* data = GetTextData();
			uint length = GetTextLen();

			//	pDC->SetTextColor(RGB(200, 0, 0));

		//	HPEN whitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		//	HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

			int nlines = m_linesArr.GetSize();

		//	printf("nlines, %d\n", nlines);

			SyntaxChunk* syntax = m_styleChunks.GetData();

			/*
			int firstVisLine = scrollposY;
			int lastVisLine = firstVisLine + (m_textArea.Height()+m_ch-1)/m_ch;
			*/
		//	pGraphics->GetClipBounds(&clipBounds);
		//	LDraw::RectD::Intersect(clipBounds, clipBounds, m_expandedBBox);

		//	clipBounds = m_expandedBBox;

			LDraw::RectD clipBounds;
			if (false)
			{
				LDraw::RectD bounds = GetWindowToElementBounds();
				LDraw::RectI r;
				m_visibleRegion->GetBounds(&r);

				clipBounds.X = r.X - bounds.X;
				clipBounds.Y = r.Y - bounds.Y;
				clipBounds.Width = r.Width;
				clipBounds.Height = r.Height;
			}
			else
			{
				clipBounds.X = 0;
				clipBounds.Y = 0;
				clipBounds.Width = get_ActualSize().Width;
				clipBounds.Height = get_ActualSize().Height;
			}

			int firstVisLine = (clipBounds.Y) / m_ch;
			if (firstVisLine < 0) firstVisLine = 0;
		//	int lastVisLine = firstVisLine+10;//(clipBounds.Height + m_ch-1)/m_ch;

			int lastVisLine = (clipBounds.GetBottom() + m_ch-1)/m_ch;

			if (lastVisLine > m_linesArr.GetSize()) lastVisLine = m_linesArr.GetSize();

			int y = firstVisLine*m_ch;

			if (lastVisLine > firstVisLine)
			{
				int offset = m_linesArr[firstVisLine]->m_offset;

				SyntaxChunk* styleChunks = m_styleChunks.GetData();

			// Find the style chunk to start at, and the offset into it
				uint startoffset = 0;
				unsigned int styleIndex = 0;
				while (styleIndex < m_styleChunks.GetSize())
				{
					if (startoffset + styleChunks[styleIndex].Length > offset) break;
					startoffset += styleChunks[styleIndex].Length;
					styleIndex++;
				}

				uint styleOffset = offset-startoffset;

				LDraw::Brush* pTextBrush = new LDraw::SolidBrush(m_styles[1].FgColor);
				//LDraw::GraphicsO graphicso;

				LDraw::Brush* pSelectionFgBrush = NULL;
				LDraw::Brush* pSelectionBgBrush = NULL;

				pSelectionFgBrush = new LDraw::SolidBrush(m_styles[0].FgColor);
				pSelectionBgBrush = new LDraw::SolidBrush(m_styles[0].BgColor);

				for (int lin = firstVisLine; lin < lastVisLine; lin++)
				{
					int offset = m_linesArr[lin]->m_offset;
					int len = m_linesArr[lin]->m_lineLengthR;

					if (m_selStart < offset+len && m_selEnd > offset)
					{
						int selStart = m_selStart;
						int selEnd = m_selEnd;

						if (selStart < offset) selStart = offset;
						if (selEnd > offset+len) selEnd = offset+len;

						int len0 = selStart - offset;
						int len1 = selEnd - selStart;
						int len2 = offset+len - selEnd;

					//	if (len0 > len) len0 = len;
					//	if (len0+len1 > len) len1 = len-len0;
					//	if (len0+len1+len2 > len) len2 = len-len1-len0;

						float x = 0;

						if (len0 > 0)
						{
							pGraphics->DrawString(&data[offset], len0, pFont, LDraw::PointF(x, y), pTextBrush);
							x += pGraphics->MeasureString(&data[offset], len0, pFont);
						}

						if (len1 > 0)
						{
							float width = pGraphics->MeasureString(&data[offset+len0], len1, pFont);

							pGraphics->FillRectangle(pSelectionBgBrush, x, y, width, pFont->GetSize());
							pGraphics->DrawString(&data[offset+len0], len1, pFont, LDraw::PointF(x, y), pSelectionFgBrush);

							x += width;
						}

						if (len2 > 0)
						{
							pGraphics->DrawString(&data[offset+len0+len1], len2, pFont, LDraw::PointF(x, y), pTextBrush);
						}
					}
					else
					{
						StringW* str = new StringW(string_copy(&data[offset], len));

						pGraphics->DrawString(str, pFont, LDraw::PointF(0, y), pTextBrush);
					}

					//for (int j = 0; j < m_linesArr[lin]->m_lineLengthR; j++, i++)

#if 0

					int i = offset;
					int vcol = 0;

					//CRect irect;
					bool bDraw = true;

					int x = 0;

					for (int j = 0; j < m_linesArr[lin]->m_lineLengthR; j++, i++)
					{
						if (bDraw)
						{
							bool bInSelection = ((i >= m_selStart) && (i < m_selEnd));	// Selection

							LDraw::Brush* pBrush = NULL;
							LDraw::Brush* pBgBrush = NULL;

							if (bInSelection)
							{
								pBrush = new LDraw::SolidBrush(m_styles[0].FgColor);
								pBgBrush = new LDraw::SolidBrush(m_styles[0].BgColor);
							}
							else
							{
								uint16 el = m_styleChunks[styleIndex].Element;

								pBrush = pTextBrush;//new LDraw::SolidBrush(m_styles[el].FgColor);
							}

							if (data[i] == '\t')	// TAB
							{
								int spaces = m_tabSize - (vcol % m_tabSize);

								for (int i = 0; i < spaces; i++)
								{
									if (pBgBrush != NULL)
									{
										LDraw::RectF bounds;
										bounds.X = x;
										bounds.Y = y;
										bounds.Height = m_ch;
										bounds.Width = m_spaceWidth;
										pGraphics->FillRectangle(pBgBrush, bounds);
									}

									if (i == 0 && m_bShowTabs)
										pGraphics->DrawGlyph(pFont->CharToGlyph('»'), pFont, LDraw::PointF(x, y), pBrush);
									else
										pGraphics->DrawGlyph(pFont->CharToGlyph(' '), pFont, LDraw::PointF(x, y), pBrush);

									//SIZE size2;
									//GetTextExtentPoint32(hDC, " ", 1, &size2);
									//x += size2.cx;
									x += m_spaceWidth;
								}

								vcol += spaces;
							}
							else
							{
								WCHAR ch = data[i];
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

								LDraw::RectF bounds;
								bounds.X = x;
								bounds.Y = y;
								bounds.Height = m_ch;
								bounds.Width = pGraphics->MeasureString(&ch, 1, pFont/*, LDraw::PointF(x, y), stringFormat, &bounds*/);

								if (pBgBrush != NULL)
								{
									pGraphics->FillRectangle(pBgBrush, bounds);
								}

								pGraphics->DrawGlyph(pFont->CharToGlyph(ch), pFont, LDraw::PointF(x, y), pBrush);

								x += bounds.Width;
								/*
								TextOut(hDC, x, y, &ch, 1);
								SIZE size2;
								GetTextExtentPoint32(hDC, &ch, 1, &size2);
								x += size2.cx;
								*/

								vcol++;
							}

							/*
							delete pBrush;
							if (pBgBrush)
							{
								delete pBgBrush;
							}
							*/
						}

						styleOffset++;
						while (styleOffset >= m_styleChunks[styleIndex].Length)
						{
							styleOffset = 0;
							styleIndex++;

							if (styleIndex >= m_styleChunks.GetSize()) break;
						}
					}
#endif
					y += m_ch;
				}

#if 0
			// Draw out bottom of window
				CRect lrc(0, y, /*scrollposX+*/m_textArea.Width(), /*scrollposY+*/m_textArea.Height());
				if (lrc.Height() > 0)
					;//hDC.FillSolidRect(&lrc, RGB(255, 255, 255));
#endif
			}

			/*
			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			SelectObject(hDC, pOldPen);

			DeleteObject(blackPen);
			DeleteObject(whitePen);
			*/

			if (m_bShowCursor)
				DrawCursor(pGraphics);
		}
	}
}

/*
int TextEdit::m_linesArr.size() 
{
	return m_linesArr.size();
}
*/

#if 0
void TextEdit::OnMouseWheel(UINT nFlags, short zDelta)
{
	UINT lines = 3;	// Default
//	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &lines, 0);

//	MessageBeep(-1);
}
#endif

/*
void TextEdit::Arrange(LDraw::SizeD finalSize)
{
//	return 0;
//	OnSize(m_bWordWrap);
//	InvalidateRect(NULL);
}
*/

LDraw::Font* TextEdit::GetFont()
{
	return Control::GetFont(this);
}

LDraw::SizeD TextEdit::MeasureOverride(LDraw::SizeD availSize)
{
//	printf("OnMeasure\n");

//	OnSize(m_bWordWrap);
	LDraw::Font* pFont = GetFont();
	LDraw::GraphicsO graphics;
	double m_spaceWidth = graphics.MeasureString(" ", 1, pFont/*, LDraw::PointF(x, y), stringFormat, &bounds*/);

	double m_ch = pFont->GetSize();

//	double cx = availSize.Width;
//	double cy = m_computedSize.Height;

//	double cx = m_computedSize.Width;
//	double cy = m_computedSize.Height;

//	int sbHeight;
//	int sbWidth;

	int lborwidth;
	if (m_lborWidth == -1)
		lborwidth = 16;	// Default
	else
		lborwidth = m_lborWidth;

	if (m_bLineNumbers)
		lborwidth += 4*m_spaceWidth;

	/*
	if (m_bVertSB)
		sbWidth = 16;//GetSystemMetrics(SM_CXVSCROLL);
	else
		sbWidth = 0;

	if (m_bHorzSB)
		sbHeight = 16;//GetSystemMetrics(SM_CXHSCROLL);
	else
		sbHeight = 0;
		*/

#if 0
	m_axhorz.ShowWindow(m_bHorzSB? SW_SHOW: SW_HIDE);
	m_axvert.ShowWindow(m_bVertSB? SW_SHOW: SW_HIDE);
#endif

	if (m_bLineNumbers)
		m_textArea.X = 32;//m_border+1+lborwidth;
	else
		m_textArea.X = 0;
//	m_textArea.top = m_border;
//	m_textArea.right = cx-sbWidth-1-m_border;
//	m_textArea.bottom = cy-sbHeight-1-m_border;

	/*
	if (FALSE)	// Statusbar
	{
		m_textArea.bottom -= 16;
	}
	*/


	/*
	if (m_bWordWrap)//bBuildLines)
	{
		BuildLineOffsets(availSize.Width);

		CalcLineCol(m_offset);	// Recalculate: m_line/m_col
		m_idealcolX = PointXFromColumn(m_line, m_col);
	}
	*/

	//m_desiredSize.Height = m_linesArr.size()*m_ch;

//	printf("height: %f\n", m_computedHeight);

	/*int maxx = GetMaxLineLength();
	m_desiredSize.Width = maxx;
	if (m_bLineNumbers)
		m_desiredSize.Width += 32;
		*/

	const WCHAR* data = GetTextData();

	LDraw::SizeD desiredSize;

	int nlines = m_tdp->GetNumberOfLines();

	if (!m_bWordWrap)
	{
		desiredSize.Width = 0;

		for (int i = 0; i < nlines; i++)
		{
			uint offset = m_tdp->GetLine(i)->m_offset;
			int lineLength = m_tdp->GetLine(i)->m_lineLength;

			double width = 0;
			const WCHAR* p = data + offset;
			int vcol = 0;

		//	double width = graphics.MeasureString(&data[offset], lineLength, pFont);
			for (int i = 0; i < lineLength; i++)
			{
				WCHAR c = *p++;

				LDraw::SizeD size2;
				if (c == '\t')
				{
					int spaces = m_tabSize - (vcol % m_tabSize);
					size2.Width = m_spaceWidth;//graphics.MeasureString(" ", 1, pFont);//GetTextExtentPoint32(hDC, " ", 1, &size2);

					width += size2.Width * spaces;
					vcol += spaces;
				}
				else
				{
					size2.Width = graphics.MeasureString(&c, 1, pFont);//GetTextExtentPoint32(hDC, " ", 1, &size2);

					width += size2.Width;
					vcol++;
				}
			}

			desiredSize.Width = MAX(desiredSize.Width, width);
		}
		desiredSize.Height = m_ch*nlines;

	/*
		for (int i = 0; i < m_rlinesArr.size(); i++)
		{
			RLineDef* pRLine = m_rlinesArr[i];

			MeasureString(
		//	pRLine->m_nDispLines = 1;

		//	LineDef* pLine = new LineDef;
		//	pLine->m_lineLength = pRLine->m_lineLength;
		//	pLine->m_lineLengthR = pRLine->m_lineLengthR;
		//	pLine->m_offset = pRLine->m_offset;

		//	m_linesArr[i] = pLine;
		}
		*/
	}
	else
	{
		//double cx = finalSize.Width;

		for (int i = 0; i < nlines; i++)
		{
//			uint offset = m_rlinesArr[i]->m_offset;
//			int lineLength = m_rlinesArr[i]->m_lineLength;
			uint offset = m_tdp->GetLine(i)->m_offset;
			int lineLength = m_tdp->GetLine(i)->m_lineLength;

			/*
			m_rlinesArr[i]->m_nDispLines = 1;

			LineDef* pLine = new LineDef;
			pLine->m_offset = offset;
			m_linesArr.push_back(pLine);
			*/
			desiredSize.Width = 0;
			desiredSize.Height = pFont->GetSize();

			int len = 0;
			int x = 0;
			int li = 0;

			while (li < lineLength)
			{
				int wordlen = 0;

				const WCHAR* p = data + offset;

				while ((li+wordlen < lineLength) && !std::isspace(*p))
				{
					p++;
					wordlen++;
				}

				while ((li+wordlen < lineLength) && std::isspace(*p))
				{
					p++;
					wordlen++;
				}

				LDraw::SizeF size(0,0);
				if (wordlen > 0)
				{
					for (int i = 0; i < wordlen; i++)
					{
						WCHAR c = data[offset+i];

						if (c == '\t')
						{
							int spaces = m_tabSize - (len % m_tabSize);
							LDraw::SizeD size2;
							size2.Width = graphics.MeasureString(" ", 1, pFont);//GetTextExtentPoint32(hDC, " ", 1, &size2);

							size.Width += size2.Width * spaces;
						}
						else
						{
							LDraw::SizeD size2;
							size2.Width = graphics.MeasureString(&c, 1, pFont);////GetTextExtentPoint32(hDC, &c, 1, &size2);

							size.Width += size2.Width;
						}
					}
				}

				if (x > 0 && x+size.Width > availSize.Width)
				{
					len = 0;
					x = 0;
					desiredSize.Height += pFont->GetSize();
				}
				x += size.Width;
				desiredSize.Width = MAX(desiredSize.Width, x);
				len += wordlen;
				li += wordlen;
				offset += wordlen;
			}
		}
	}

	desiredSize.Width += m_textArea.X+1;

//	printf("width: %f\n", m_computedWidth);

	/*
	m_expandedBBox.X = 0;
	m_expandedBBox.Y = 0;
	m_expandedBBox.Width = m_computedWidth;
	m_expandedBBox.Height = m_computedHeight;
	*/

	return desiredSize;
}

LDraw::SizeD TextEdit::ArrangeOverride(LDraw::SizeD finalSize)
{
// Display lines (wrapped or not)
	for (int i = 0; i < m_linesArr.GetSize(); i++)
	{
		delete m_linesArr[i];
	}

	VERIFY(m_nDispLines.GetSize() == m_tdp->GetNumberOfLines());
	int nlines = m_tdp->GetNumberOfLines();

	if (!m_bWordWrap)
	{

		m_linesArr.SetSize(nlines);
	//	m_nDispLines.SetSize(m_rlinesArr.GetSize());

		for (int i = 0; i < nlines; i++)
		{
			TextLines::Line* pRLine = m_tdp->GetLine(i);//m_rlinesArr[i];

#if 0
			pRLine->m_nDispLines = 1;
#endif
			m_nDispLines[i] = 1;

			LineDef* pLine = new LineDef;
			pLine->m_lineLength = pRLine->m_lineLength;
			pLine->m_lineLengthR = pRLine->m_lineLengthR;
			pLine->m_offset = pRLine->m_offset;

			m_linesArr[i] = pLine;
		}

		CalcLineCol(m_offset);	// Recalculate: m_line/m_col
		m_idealcolX = PointXFromColumn(m_line, m_col);
	}
	else
	{
		m_linesArr.RemoveAll();

	//	LDraw::GraphicsO graphics;

		LDraw::Font* pFont = GetFont();

		const WCHAR* data = GetTextData();
		double cx = finalSize.Width;

		for (int i = 0; i < nlines; i++)
		{
			TextLines::Line* pRLine = m_tdp->GetLine(i);

			uint offset = pRLine->m_offset;
			int lineLength = pRLine->m_lineLength;

		//	m_rlinesArr[i]->m_nDispLines = 1;
			m_nDispLines[i] = 1;

			LineDef* pLine = new LineDef;
			pLine->m_offset = offset;
			m_linesArr.Add(pLine);

			int len = 0;
			int x = 0;
			int li = 0;

			while (li < lineLength)
			{
				int wordlen = 0;

				const WCHAR* p = data + offset;

				while ((li+wordlen < lineLength) && !std::isspace(*p))
				{
					p++;
					wordlen++;
				}

				while ((li+wordlen < lineLength) && std::isspace(*p))
				{
					p++;
					wordlen++;
				}

				LDraw::SizeF size(0,0);
				if (wordlen > 0)
				{
					for (int i = 0; i < wordlen; i++)
					{
						WCHAR c = data[offset+i];

						if (c == '\t')
						{
							int spaces = m_tabSize - (len % m_tabSize);
							LDraw::SizeD size2;
							size2.Width = LDraw::Graphics2D::MeasureString(" ", 1, pFont, LDraw::SmoothingModeNone);

							size.Width += size2.Width * spaces;
						}
						else
						{
							LDraw::SizeD size2;
							size2.Width = LDraw::Graphics2D::MeasureString(&c, 1, pFont, LDraw::SmoothingModeNone);

							size.Width += size2.Width;
						}
					}
				}

				if (x > 0 && x+size.Width > cx)
				{
				//	m_rlinesArr[i]->m_nDispLines++;
					++m_nDispLines[i];

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

				x += size.Width;
				len += wordlen;
				li += wordlen;
				offset += wordlen;
			}

			pLine->m_lineLength = len;
			pLine->m_lineLengthR = len + (pRLine/*m_rlinesArr[i]*/->m_lineLengthR - pRLine/*m_rlinesArr[i]*/->m_lineLength);
		}

		CalcLineCol(m_offset);	// Recalculate: m_line/m_col
		m_idealcolX = PointXFromColumn(m_line, m_col);
	}

	return finalSize;
}

#if 0
void TextEdit::OnSize(bool bBuildLines) 
{
//	CRect	client = GetClientRect();

	LDraw::Font* pFont = GetFont();
	LDraw::Graphics graphics;
	double m_spaceWidth = graphics.MeasureString(" ", 1, pFont/*, LDraw::PointF(x, y), stringFormat, &bounds*/);

	double cx = m_computedSize.Width;
	double cy = m_computedSize.Height;

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
		sbWidth = 16;//GetSystemMetrics(SM_CXVSCROLL);
	else
		sbWidth = 0;

	if (m_bHorzSB)
		sbHeight = 16;//GetSystemMetrics(SM_CXHSCROLL);
	else
		sbHeight = 0;

#if 0
	m_axhorz.ShowWindow(m_bHorzSB? SW_SHOW: SW_HIDE);
	m_axvert.ShowWindow(m_bVertSB? SW_SHOW: SW_HIDE);
#endif

	if (m_bLineNumbers)
		m_textArea.X = 32;//m_border+1+lborwidth;
	else
		m_textArea.X = 0;
//	m_textArea.top = m_border;
//	m_textArea.right = cx-sbWidth-1-m_border;
//	m_textArea.bottom = cy-sbHeight-1-m_border;

	/*
	if (FALSE)	// Statusbar
	{
		m_textArea.bottom -= 16;
	}
	*/


	if (bBuildLines)
	{
		BuildLineOffsets();

		CalcLineCol(m_offset);	// Recalculate: m_line/m_col
		m_idealcolX = PointXFromColumn(m_line, m_col);
	}

	ResetVScrollSize();
	ResetHScrollSize();
}
#endif

/*
void TextEdit::CutSelectionToClipboard()
{
	CopySelectionToClipboard();
	DeleteChar(m_selStart, m_selEnd - m_selStart+1);
	m_initSel = 0; m_selStart = 0; m_selEnd = -1;
//	TOP()->OnUpdate();
}
*/

void TextEdit::CopySelectionToClipboard()
{
#if WIN32
	if (MSWindows::OpenClipboard(NULL))
	{
		MSWindows::EmptyClipboard();

		// Unicode Text
		{
			uint size = (m_selEnd - m_selStart)*2;

			MSWindows::HGLOBAL hMem = MSWindows::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size+2);
			WCHAR* pMem = (WCHAR*)MSWindows::GlobalLock(hMem);
			std::memcpy(pMem, GetTextData() + m_selStart, size);
			MSWindows::GlobalUnlock(hMem);

			MSWindows::SetClipboardData(CF_UNICODETEXT, hMem);
		}

		// Ansi Text
		{
			uint size = m_selEnd - m_selStart;

			MSWindows::HGLOBAL hMem = MSWindows::GlobalAlloc(GMEM_MOVEABLE, size+1);
			char* pMem = (char*)MSWindows::GlobalLock(hMem);

			const WCHAR* p = GetTextData() + m_selStart;
			int i;
			for (i = 0; i < size; i++)
			{
				pMem[i] = (char)p[i];
			}
			pMem[i] = 0;

			MSWindows::GlobalUnlock(hMem);

			MSWindows::SetClipboardData(CF_TEXT, hMem);
		}

		MSWindows::CloseClipboard();
	}

#elif AMIGA

	const WCHAR* data = GetTextData() + m_selStart;
	ULONG len = m_selEnd - m_selStart;

	ClipboardByteStream* pStream = NULL;
	IFFParser* parser = NULL;

	TRY
	{
		pStream = new ClipboardByteStream(STREAM_WRITE, 0);
	//	pStream->AddRef();

		parser = new IFFParser(pStream);

		IFFCHUNK formCk;
		formCk.ckID = ID_FORM;
		formCk.grpID = ID_FTXT;
		parser->IFFCreateChunk(&formCk);
		{
			IFFCHUNK ck;
			ck.ckID = ID_CHRS;
			ck.ckSize = len;
			parser->IFFCreateChunk(&ck);

			parser->IFFWriteChunkBytes(data, len);
			parser->IFFAscendChunk(&ck);
		}
		parser->IFFAscendChunk(&formCk);
	}
	CATCH(int)
	{
		printf("Failed to copy text to Clipboard\n");
	}

	delete parser;
	pStream->Close();//->Release();

#endif
}

void TextEdit::PasteFromClipboard()
{
#if WIN32
	if (MSWindows::OpenClipboard(NULL))
	{
		if (MSWindows::IsClipboardFormatAvailable(CF_TEXT) ||
			MSWindows::IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			HANDLE hMem;

			WCHAR* text = NULL;
			uint len = 0;
			void* pMem = NULL;

			if (hMem = MSWindows::GetClipboardData(CF_UNICODETEXT))
			{
				pMem = (void*)MSWindows::GlobalLock(hMem);
				len = MIN(std::wcslen((WCHAR*)pMem), MSWindows::GlobalSize(hMem)/2);

				text = (WCHAR*)pMem;
			}
			else
			{
				// Convert to unicode
				pMem = (void*)MSWindows::GlobalLock(hMem);
				len = MIN(std::strlen((char*)pMem), MSWindows::GlobalSize(hMem));

				text = new WCHAR[len];
				for (int i = 0; i < len; i++)
				{
					text[i] = ((char*)pMem)[i];
				}
			}

			InsertText(m_offset, text, len);
#if 0
			BuildRLineOffsets();
			BuildLineOffsets();
#endif

			CEditUndoTyping* pUndo = new CEditUndoTyping;
			//pUndo->AddRef(); ??
			pUndo->m_pEdit = this;
			pUndo->m_kind = 1;
			pUndo->m_startCharPos = m_offset;
			pUndo->m_len = len;

			m_undoManager->Add(pUndo);
			//pUndo->Release();

			m_pRecentUndoTyping = NULL;

			MSWindows::GlobalUnlock(hMem);

			if (text != pMem)
			{
				delete[] text;
			}
		}

		MSWindows::CloseClipboard();
	}

#elif AMIGA

#if 0
	ClipboardByteStream* pStream = new ClipboardByteStream(STREAM_READ, 0);
	//pStream->AddRef();

	IFFParser* parser = new IFFParser(pStream);

	IFFCHUNK grpck;
	if (parser->IFFDescendChunk(&grpck) == IFF_EOC)
	{
		if (grpck.grpID == ID_FTXT)
		{
			StringBuilderA str;

			IFFCHUNK ck;
			while (parser->IFFDescendChunk(&ck) == 0)
			{
				if (ck.ckID == ID_CHRS)
				{
					char* data = new char[ck.ckSize];
					parser->IFFReadChunkBytes(data, ck.ckSize);
					// TODO, append
					ASSERT(0);
					str.Append(data, ck.ckSize);
					delete data;
				}

				parser->IFFAscendChunk(&ck);
			}

			CEditUndoTyping* pUndo = new CEditUndoTyping;
			//pUndo->AddRef(); ??
			pUndo->m_pEdit = this;
			pUndo->m_kind = 1;
			pUndo->m_startCharPos = m_offset;
			pUndo->m_len = str.length();
			m_undoManager->Add(pUndo);
			//pUndo->Release();
			m_pRecentUndoTyping = NULL;

			StringW wstr = str.ToStringW();

			InsertText(m_offset, wstr.c_str(), str.Length());
			LocateCursor(m_offset+wstr.Length());
		}
		parser->IFFAscendChunk(&grpck);
	}

	delete parser;

	pStream->Close();

	#endif

#endif
}

void __stdcall TextEdit::OnHorzScroll(long code, long pos)
{
#if 0
	HideCursor();

	long oldPos; m_horz->get_pos(&oldPos);

	CRect	rect = m_textArea;
	
	m_horz->put_pos(pos);
	ScrollWindow((oldPos-pos), 0, &rect, &rect);

	ShowCursor();
#endif
}

void __stdcall TextEdit::OnVertScroll(long code, long pos)
{
#if 0
	HideCursor();

	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_textArea;
	rect.left = 0;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, (oldPos-pos)*m_ch, &rect, &rect);

	ShowCursor();
#endif
}

void TextEdit::OnSetFocus()
{
//	SetTimer(1, 400);
	ShowCursor();
}

void TextEdit::OnKillFocus()
{
//	KillTimer(1);
	ClearSelectionAndInvalidate();
	HideCursor();
}

#if 0
long TextEdit::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
//	return 0;

	UINT nHitTest = LOWORD(lParam);
	UINT message = HIWORD(lParam);

	if (nHitTest == HTCLIENT)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		CRect	client = GetClientRect();
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
#endif
	return FALSE;
}
#endif

//#include "FindDlg.h"

void TextEdit::Find(const StringW & findStr)
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

			InvalidateRect(&m_textArea);
			break;
		}

		text++;
		textlen--;
		i++;
	}
#endif
}

void TextEdit::OnEditFind()
{
/*	CFindDlg	dlg;
	if (dlg.DoModal() == IDOK)
	{
		Find(dlg.m_findWhat);
	}
*/
}

void TextEdit::OnFindMatchingBracket()
{
#if _WINDOWS
	const WCHAR* text = GetTextData();
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

	LONG bShift = (MSWindows::GetAsyncKeyState(VK_SHIFT) & (1<<15));

	if (dir == -1)
	{
		while (offset >= 0)
		{
			if (text[offset] == c2) count--;
			else if (text[offset] == c) count++;

			if (count == 0)
			{
				LocateCursor(offset);

				Invalidate();//Rect(NULL);
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
				Invalidate();//Rect(NULL);
				OnMovedCursor();
				break;
			}

			offset++;
		}
	}

	ScrollIntoView(m_line, m_col);
#endif
}

//////// Default text data handler

void TextEdit::InsertText(int offset, const WCHAR* data, int len)
{
	ASSERT(m_tdp != NULL);
	m_tdp->m_textData->InsertText(offset, data, len);
}

void TextEdit::DeleteText(int offset, int len)
{
	ASSERT(m_tdp != NULL);
	m_tdp->m_textData->DeleteText(offset, len);
}

void TextEdit::ReplaceText(int offset, int deletelen, WCHAR* data)
{
	ASSERT(m_tdp != NULL);
	m_tdp->m_textData->ReplaceText(offset, deletelen, data);
}

ITextData* TextEdit::get_TextDocument()
{
	return m_tdp->m_textData;
}

void TextEdit::set_TextDocument(ITextData *newVal)
{
	if (m_tdp)
	{
#if 0
		if (m_hWnd)
		{
			HRESULT hr = IDispEventImpl<3, TextEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_tdp);
			ASSERT(SUCCEEDED(hr));
		}
#endif
	}

	if (m_tdp == NULL)
	{
		m_tdp = new TextLines(newVal);
		m_tdp->InsertedText.connect(bind1st_of_2(mem_fun(&TextEdit::OnTextContentChanged), this));
	}
	else
	{
		m_tdp->set_TextData(newVal);
	}

	OnTextContentChanged(0);	// TODO remove ???

	if (m_tdp && false)
	{
		ASSERT(0);
#if 0
		dynamic_cast<EventTargetImpl*>(m_tdp)->addEventListener(WSTR("TextInserted"), this, false);
		dynamic_cast<EventTargetImpl*>(m_tdp)->addEventListener(WSTR("TextDeleted"), this, false);
		dynamic_cast<EventTargetImpl*>(m_tdp)->addEventListener(WSTR("TextChanged"), this, false);
#endif
//		if (m_hWnd)
		{
#if 0
			HRESULT hr = IDispEventImpl<3, TextEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>::DispEventAdvise(m_tdp);
			ASSERT(SUCCEEDED(hr));
#endif
		}
	}
}

void TextEdit::OnTextContentChanged(int)
{
//	if (m_hWnd)
	{
		ClearFormatting();

		BuildRLineOffsets();
	//	BuildLineOffsets(m_computedSize.Width);
		InvalidateMeasure();
	}

	m_offset = 0;
	m_line = 0;
	m_col = 0;

//	if (m_hWnd)
	{
	//	ResetVScrollSize();
	//	ResetHScrollSize();
	//	Invalidate();//Rect(NULL);
	}

#if 0
	Fire_Change();
#endif
}

void TextEdit::OnTextInsertText(long offset, long len)
{
	uint styleoffset = 0;
	int i;
	for (i = 0; i < m_styleChunks.GetSize(); i++)
	{
		if (styleoffset + m_styleChunks[i].Length >= offset) break;
		styleoffset += m_styleChunks[i].Length;
	}
	m_styleChunks[i].Length += len;

	if (true)
	{
		BuildRLineOffsets();
	}
	else
	{
#if 0
		// Find which line offset is on
		int nlines = m_tdp->GetNumberOfLines();

		int line;
		for (line = nlines-1; line >= 0; line--)
		{
			if (offset >= m_tdp->GetLine(line)->m_offset)
				break;
		}

		int linelen = offset- m_tdp->GetLine(line)->m_offset;
		ASSERT(linelen >= 0);

		linelen = m_tdp->GetLine(line)->m_lineLength+len;

		const WCHAR* data = GetTextData();
		uint length = GetTextLen();

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
		m_tdp->GetLine(line)->m_lineLength = linelen;
		m_tdp->GetLine(line)->m_lineLengthR = linelen+1;
		line++;

		{
			// Offset following lines
			for (int i = line; i < m_rlinesArr.GetSize(); i++)
			{
				m_rlinesArr[i]->m_offset += len;
			}
		}
#endif
	}

#if 0	// Had this ??
	BuildLineOffsets();
#endif

#ifdef _DEBUG
	{
		uint tlen = GetTextLen();

		uint total = 0;
		for (int i = 0; i < m_styleChunks.GetSize(); i++)
		{
			total += m_styleChunks[i].Length;
		}
		ASSERT(total == tlen);
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
#if 0
	ResetVScrollSize();
#endif
//	ScrollIntoView(m_line, m_col);	// TODO remove

//	Invalidate();//Rect(NULL);
	InvalidateMeasure();

#if 0
	Fire_Change();
#endif
}

void TextEdit::OnTextDeleteText(long offset, long len)
{
	uint styleoffset = 0;
	int i;
	for (i = 0; i < m_styleChunks.GetSize(); i++)
	{
		if (styleoffset + m_styleChunks[i].Length > offset) break;
		styleoffset += m_styleChunks[i].Length;
	}

	int j = i;
	uint styleoffset2 = styleoffset;
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

		ASSERT(0);
#if 0
		m_styleChunks.RemoveAt(i+1, j-i-1);
#endif
	}

	if (true)
	{
		BuildRLineOffsets();
	}
	else
	{
#if 0
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
#endif
	}

#if 0	// Had this ??
	BuildLineOffsets();
#endif

#ifdef _DEBUG
	{
		uint tlen = GetTextLen();

		uint total = 0;
		for (int k = 0; k < m_styleChunks.GetSize(); k++)
		{
			total += m_styleChunks[k].Length;
		}
		ASSERT(total == tlen);
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
#if 0
	ResetVScrollSize();
#endif
//	ScrollIntoView(m_line, m_col);	// TODO remove

//	Invalidate();//Rect(NULL);
	InvalidateMeasure();

#if 0
	Fire_Change();
#endif
}

IUndoManager * TextEdit::get_undoManager()
{
	return m_undoManager;
}

void TextEdit::set_undoManager(IUndoManager *newVal)
{
	m_undoManager = newVal;
}

void TextEdit::DeleteSelection()
{
	int len = m_selEnd - m_selStart;

	if (m_undoManager)
	{
		CEditUndoTyping* pUndo = new CEditUndoTyping;

	//	pUndo->AddRef();
		pUndo->m_pEdit = this;
		pUndo->m_kind = 1;
		pUndo->m_bRedo = true;
		pUndo->m_startCharPos = m_selStart;
		pUndo->m_len = len;
		pUndo->m_text = new WCHAR[len];
		std::memcpy(pUndo->m_text, GetTextData() + m_selStart, len*sizeof(WCHAR));

		m_undoManager->Add(pUndo);
	//	pUndo->Release();

		m_pRecentUndoTyping = NULL;
	}

	DeleteText(m_selStart, len);
//	BuildLineOffset();

	LocateCursor(m_selStart);
	if (m_dragging)
		m_initSel = m_selStart;
	else
		m_initSel = -1;
	m_selStart = 0;
	m_selEnd = -1;
}

//#include "..\WebEditor\IIDCommands.h"

#if 0
BEGIN_CMD_MAP(TextEdit)
	CMD_HANDLER(ID_EDIT_CUT, OnEditCut)
	CMD_UPDATE(ID_EDIT_CUT, OnEditCutCopyUpdate)
	CMD_HANDLER(ID_EDIT_COPY, OnEditCopy)
	CMD_UPDATE(ID_EDIT_COPY, OnEditCutCopyUpdate)
	CMD_HANDLER(ID_EDIT_PASTE, OnEditPaste)
	CMD_UPDATE(ID_EDIT_PASTE, OnEditPasteUpdate)

	CMD_HANDLER(ID_EDIT_CLEAR, OnEditDelete)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditDeleteUpdate)
END_CMD_MAP()

LRESULT TextEdit::OnEditCut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CopySelectionToClipboard();
	DeleteSelection();

#if 0
	ResetVScrollSize();
	ResetHScrollSize();
	InvalidateRect(NULL);
#endif

//	OnChange();
	OnMovedCursor();

	return 0;
}
#endif

void TextEdit::OnEditCopy()
{
	CopySelectionToClipboard();
}

#if 0
void TextEdit::OnEditCutCopyUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(m_initSel > -1);
}
#endif

void TextEdit::OnEditPaste()
{
	CEditUndoParent* pParentUndo = NULL;

	if (m_initSel > -1)
	{
		pParentUndo = new CEditUndoParent;
		//pParentUndo->AddRef();

		m_undoManager->Open(pParentUndo);

		DeleteSelection();
	}

	PasteFromClipboard();

	if (pParentUndo)
	{
		m_undoManager->Close(pParentUndo, true/*commit*/);
#if 0
		pParentUndo->Release();
#endif
	}

	m_pRecentUndoTyping = NULL;

#if 0
	ResetVScrollSize();
	ResetHScrollSize();
#endif
	//Invalidate();//Rect(NULL);

//	OnChange();
	OnMovedCursor();
}

#if 0

void TextEdit::OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_TEXT) || IsClipboardFormatAvailable(CF_UNICODETEXT));
}

LRESULT TextEdit::OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DeleteSelection();

#if 0
	ResetVScrollSize();
	ResetHScrollSize();
#endif
	InvalidateRect(NULL);

//	OnChange();
	OnMovedCursor();

	return 0;
}

void TextEdit::OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(m_initSel > -1);
}
#endif

StringW* TextEdit::get_Text() const
{
	return m_tdp->m_textData->GetTextAsString();
}

void TextEdit::set_Text(StringW* text)
{
	m_tdp->SetTextAsString(text);
//	OnTextContentChanged(0);	// TODO remove ???
}

#if 0
STDMETHODIMP TextEdit::GetText(BSTR *text)
{
	BSTR b;
	m_tdp->get_data(&b);
	*text = SysAllocString(b);

	return S_OK;
}
#endif

bool TextEdit::get_MultiLine() const
{
	return m_bMultiLine;
}

void TextEdit::set_MultiLine(bool newVal)
{
	m_bMultiLine = newVal;
}

bool TextEdit::get_WordWrap() const
{
	return m_bWordWrap;
}

void TextEdit::set_WordWrap(bool newVal)
{
	m_bWordWrap = newVal;

//	if (m_hWnd)
	{
	//	OnSize(TRUE);
		InvalidateMeasure();
		//Invalidate();
	}
}

bool TextEdit::get_LineNumbers() const
{
	return m_bLineNumbers;
}

void TextEdit::set_LineNumbers(bool newVal)
{
	m_bLineNumbers = newVal;

//	if (m_hWnd)
	{
		//OnSize(m_bWordWrap);
		InvalidateMeasure();
	}
}

ErrorCode TextEdit::FormatRange(long start, long len, long styleIndex)
{
/*
	offset highlight with 1 (so that always 0=selection and 1=text)
	this results in passing -1=selection and 0=text
*/

	styleIndex += 1;

	ASSERT(len >= 0);
	ASSERT(start+len <= GetTextLen());

	int nchunks = m_styleChunks.GetSize();
	SyntaxChunk* chunks = m_styleChunks.GetData();

	uint startSearch;
	/*
	if (pstyleElementIndex)
		startSearch = *pstyleElementIndex;
	else
		*/
		startSearch = 0;

	uint offset = 0;
	uint i;
	for (i = 0; i < nchunks; i++)
	{
		uint offsetend = offset+chunks[i].Length;
		if (offsetend > start) break;
		offset = offsetend;
	}

	int j = i;
	uint offset2 = offset;
	for ( ; j < nchunks; j++)
	{
		uint offsetend = offset2+chunks[j].Length;
		if (offsetend >= start+len) break;
		offset2 = offsetend;
	}

	if (i == j)	// Inserting a chunk in the middle of one single chunk
	{
		SyntaxChunk ck;

		ASSERT(0);
#if 0
		m_styleChunks.InsertAt(i+1, ck, 2);
#endif

		m_styleChunks[i+1].Length = len;
		m_styleChunks[i+1].Element = styleIndex;
		m_styleChunks[i+1].Flags = 0;

		m_styleChunks[i+2].Length = m_styleChunks[i].Length-len - (start-offset);
		m_styleChunks[i+2].Element = m_styleChunks[i].Element;
		m_styleChunks[i+2].Flags = 0;

// Truncate this chunk
		m_styleChunks[i].Length = start-offset;

#if 0	// ??
		if (pstyleElementIndex)
			*pstyleElementIndex = i+2;
#endif
	}
	else
	{
		ASSERT(0);
#if 0
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
#endif
	}

#ifdef _DEBUG
	{
		uint tlen = GetTextLen();

		uint total = 0;
		for (int i = 0; i < m_styleChunks.GetSize(); i++)
		{
			total += m_styleChunks[i].Length;
		}
		ASSERT(total == tlen);
	}
#endif

	return Success;
}

void TextEdit::ClearFormatting()
{
//	m_styleChunks.SetSize(0, 4096);
	m_styleChunks.RemoveAll();

	SyntaxChunk ck;
	if (m_tdp)
		ck.Length = GetTextLen();
	else
		ck.Length = 0;
	ck.Element = 1;	// Text
	ck.Flags = 0;
	m_styleChunks.Add(ck);
}

long TextEdit::NewStyle()
{
	SyntaxElement style;
	/*long index =*/ m_styles.Add(style);

	return m_styles.GetSize()-2;
}

void TextEdit::SetStyle(long index, LDraw::Color fgColor, LDraw::Color bgColor)
{
	index += 1;

	if (index >= 0 && index < m_styles.GetSize())
	{
		m_styles[index].FgColor = fgColor;
		m_styles[index].BgColor = bgColor;

		Invalidate();//Rect(&m_textArea);
	}
	else
	{
		THROW(-1);
	}
}

void TextEdit::get_cursorBox(LDraw::RectD *pRect) const
{
	if (pRect == NULL) THROW(-1);

	ASSERT(0);
#if 0

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
#endif
}

int TextEdit::SetSel(long nStartChar, long nEndChar, bool bNoScroll)
{
	//if (m_hWnd)	// ??
	{
		if (nEndChar == -1)
			nEndChar = GetTextLen();

		SetSelectionAndInvalidate(nStartChar, nEndChar);
		LocateCursor(nEndChar);	// ??
	}

	return 0;
}

int TextEdit::Clear()
{
	// TODO: Add your implementation code here

	return 0;
}

int TextEdit::Cut()
{
	// TODO: Add your implementation code here

	return 0;
}

int TextEdit::Copy()
{
	// TODO: Add your implementation code here

	return 0;
}

int TextEdit::Paste()
{
	// TODO: Add your implementation code here

	return 0;
}

/*
long TextEdit::get_LineHeight() const
{
	return GetFont().GetSize();//m_ch;
}

void TextEdit::put_LineHeight(long newVal)
{
}
*/

bool TextEdit::CanPaste(unsigned long nFormat)
{
	bool bVal = false;

#if _WINDOWS
	if (nFormat == 0)
	{
		if (MSWindows::IsClipboardFormatAvailable(CF_TEXT) ||
			MSWindows::IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			bVal = true;
		}
	}
	else if (nFormat == CF_TEXT || nFormat == CF_UNICODETEXT)
	{
		bVal = true;
	}
#endif
	return bVal;
}

void TextEdit::ReplaceText(long offset, long len, const WCHAR* data, long datalen)
{
#if _WINDOWS
	CEditUndoParent* pParentUndo = NULL;

	if (m_undoManager)
	{
		pParentUndo = new CEditUndoParent;
		//pParentUndo->AddRef();
		m_undoManager->Open(pParentUndo);
	}

	if (len > 0)
	{
		if (m_undoManager)
		{
			CEditUndoTyping* pUndo = new CEditUndoTyping;
			pUndo->m_pEdit = this;
			pUndo->m_kind = 1;
			pUndo->m_bRedo = true;
			pUndo->m_startCharPos = offset;
			//pUndo->m_len = len;
			pUndo->m_text = new WCHAR[len];
			std::memcpy(pUndo->m_text, GetTextData() + offset, len*2);

			m_undoManager->Add(pUndo);

			m_pRecentUndoTyping = NULL;
		}

		DeleteText(offset, len);
	}

	{
		InsertText(offset, data, datalen);

		if (m_undoManager)
		{
			CEditUndoTyping* pUndo = new CEditUndoTyping;
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
		m_undoManager->Close(pParentUndo, true/*commit*/);
	//	pParentUndo->Release();
	}

//	BuildLines();

// ??
#if 0
	ResetVScrollSize();
	ResetHScrollSize();
#endif
	Invalidate();//Rect(NULL);
#endif
}

int TextEdit::GetSel(long *start, long *end)
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

	return 0;
}

StringW* TextEdit::GetSelText()
{
	ASSERT(0);
#if 0
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocStringLen(GetTextData()+m_selStart, m_selEnd-m_selStart);
#endif
	return NULL;
}

void TextEdit::ReplaceSelText(const WCHAR* data, long len)
{
	if (m_selEnd > m_selStart)
		ReplaceText(m_selStart, m_selEnd-m_selStart, data, len);
	else
		ReplaceText(m_offset, 0, data, len);
}

int TextEdit::get_tabSize() const
{
	return m_tabSize;
}

void TextEdit::set_tabSize(int newVal)
{
	m_tabSize = newVal;

	if (m_tabSize < 1) m_tabSize = 1;
	else if (m_tabSize > 99) m_tabSize = 99;

//	if (m_hWnd)
	{
		Invalidate();//Rect(&m_textArea);
	}
}

/*
bool TextEdit::get_viewWhitespace() const
{
	// TODO: Add your implementation code here

	return S_OK;
}

void TextEdit::put_viewWhitespace(bool newVal)
{
}
*/

bool TextEdit::get_viewTabs() const
{
	return m_bShowTabs;
}

void TextEdit::set_viewTabs(bool newVal)
{
	m_bShowTabs = newVal;
	Invalidate();
}

bool TextEdit::get_viewSpaces() const
{
	return m_bShowSpace;
}

void TextEdit::set_viewSpaces(bool newVal)
{
	m_bShowSpace = newVal;
//	if (m_hWnd)
	{
		Invalidate();//Rect(&m_textArea);
	}
}

bool TextEdit::get_viewEOLs() const
{
	return m_bShowEOL;
}

void TextEdit::set_viewEOLs(bool newVal)
{
	m_bShowEOL = newVal;
//	if (m_hWnd)
	{
		Invalidate();//Rect(&m_textArea);
	}
}

long TextEdit::getCursorPosOffset()
{
	return m_offset;
}

void TextEdit::setCursorPosOffset(long offset)
{
	HideCursor();

	LocateCursor(offset);
	ScrollIntoView(m_line, m_col);

	ShowCursor();

	OnMovedCursor();

//	Invalidate();	// TODO remove
}

void TextEdit::setCursorPos(long line, long col)
{
//	HideCursor();

	LocateCursor(line, col);
	ScrollIntoView(m_line, m_col);

	Invalidate();	// ??
//	ShowCursor();

	OnMovedCursor();

//	Invalidate();	// TODO remove
}

#if 0
STDMETHODIMP TextEdit::AutoList(IUIAutoListWindow **pVal)
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
#endif

int TextEdit::AutoListPopup()
{
	ASSERT(0);
#if 0
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
#endif
	return Success;
}

}	// UI
}
