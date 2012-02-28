// TextView.cpp : Implementation of CTextView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "TextView.h"

#include "ETextDocument.h"
#include "LXMLEditorApp.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CTextView

int CTextView::FinalConstruct()
{
	HRESULT hr;

	hr = m_edit.CoCreateInstance(CLSID_UIEdit);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CTextView::FinalRelease()
{
}

STDMETHODIMP CTextView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	if (bActivate)
	{
		uiManager->ActivateObject(NULL, m_document);
		uiManager->ActivateObject(m_document, GetUnknown());

//		m_objectSelection->FromTargets(m_targetObjects.GetData(), m_targetObjects.GetSize());
//		uiManager->ActivateObject(GetUnknown(), m_objectSelection->GetUnknown());
	}
	else
	{
		uiManager->DeactivateObject(GetUnknown());
		uiManager->DeactivateObject(m_document);
	}
#endif

	return S_OK;
}

LRESULT CTextView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComPtr<ITextData> textDocument;
	m_document->get_textData(&textDocument);

	CComQIPtr<IEDocument> eDocument = m_document;

	CComQIPtr<IOleUndoManager> undoManager;
	eDocument->get_undoManager(&undoManager);

	IUnknown* p;
	CRect rc(0,0,0,0);

	m_edit->set_undoManager(undoManager);
	m_edit->set_textDocument(textDocument);
	m_edit->set_vertScroll(TRUE);
	m_edit->set_horzScroll(TRUE);
	m_edit->set_multiLine(TRUE);
	m_axedit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axedit.AttachControl(m_edit, &p);

	m_statusBar.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_VISIBLE | WS_CHILD);

	OnPrefsChange();	// Initialize edit control

	IDispEventImpl<1, CTextView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_edit);
	IDispEventImpl<4, CTextView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document->m_app);

	return 0;
}

LRESULT CTextView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CTextView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_edit);
	IDispEventImpl<4, CTextView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document->m_app);
	return 0;
}

LRESULT CTextView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
//	InvalidateRect(NULL, FALSE);

	return 0;
}

void CTextView::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_axedit.MoveWindow(0, 0, client.right, client.bottom-16, TRUE);
	m_statusBar.MoveWindow(0, client.bottom-16, client.right, 16, TRUE);
}

void __stdcall CTextView::OnEditMovedCursor(long offset)
{
	long nLine;
	m_edit->get_line(&nLine);

	long nCol;
	m_edit->get_column(&nCol);

	m_statusBar.m_text.Format("Ln %d, Col %d", nLine+1, nCol+1);
	m_statusBar.Invalidate();
}

void __stdcall CTextView::OnPrefsChange()
{
	CFormatWindow* pWindow = static_cast<CLXMLEditorApp*>(m_document->m_app.p)->RegisterFormatWindow(L"Source Windows");
	ATLASSERT(pWindow);

	{
		long tabSize;
		m_document->m_app->get_tabSize(&tabSize);

		m_edit->put_tabSize(tabSize);
	}

	{
		HDC hDC = ::GetDC(NULL);

		_bstr_t faceName = pWindow->m_lf.lfFaceName;
		FONTDESC	fd;
		fd.cbSizeofstruct = sizeof(fd);
		fd.lpstrName = faceName;////*/L"Courier";
//		fd.cySize.Hi = 10;//pWindow->m_lf.lfHeight;//MulDiv(-pWindow->m_lf.lfHeight/* - lpntme->ntmTm.tmInternalLeading*/, 72, GetDeviceCaps(hDC, LOGPIXELSY));//pWindow->m_lf.lfHeight;//-10;
//		fd.cySize.Lo = 0;
		fd.cySize.int64 = -10000*MulDiv(pWindow->m_lf.lfHeight, 72, GetDeviceCaps(hDC, LOGPIXELSY));
//		fd.cySize.Lo = 0;
		fd.sWeight = 0;
		fd.sCharset = 0;
		fd.fItalic = FALSE;
		fd.fUnderline = FALSE;
		fd.fStrikethrough = FALSE;

		::ReleaseDC(NULL, hDC);

		CComPtr<IFontDisp> font;
		HRESULT hr = OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&font);
		m_edit->put_font(font);
	}

	/*
	{
		COLORREF fgColor, bgColor;

		pWindow->GetFormatColorValues(L"Text Selection", &fgColor, &bgColor);
		m_edit->SetStyle(-1, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Text", &fgColor, &bgColor);
		m_edit->SetStyle(0, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Preprocessing Instruction", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_PREPROCESSING_INSTRUCTION, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Element Name", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_ELEMENT_NAME, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Attribute Name", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_ATTRIBUTE_NAME, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Attribute Value", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_ATTRIBUTE_VALUE, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Tag Delimiter", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_TAG_DELIMITER, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Comment", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_COMMENT, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Operator", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_OPERATOR, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script Keyword", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_KEYWORD, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script String", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_STRING, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script Comment", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_COMMENT, fgColor, bgColor);
	}
	*/
}

BEGIN_CMD_MAP(CTextView)
// View
	CMD_HANDLER(ID_VIEW_WORDWRAP, OnViewWordWrap)
	CMD_UPDATE(ID_VIEW_WORDWRAP, OnViewWordWrapUpdate)
	CMD_HANDLER(ID_VIEW_LINENUMBERS, OnViewLineNumbers)
	CMD_UPDATE(ID_VIEW_LINENUMBERS, OnViewLineNumbersUpdate)
	CMD_HANDLER(ID_VIEW_VIEWWHITESPACE, OnViewWhitespace)
	CMD_UPDATE(ID_VIEW_VIEWWHITESPACE, OnViewWhitespaceUpdate)

// Window
	CMD_HANDLER(ID_WINDOW_NEW, OnWindowNew)
END_CMD_MAP()

#if 0
// ICommandTarget
STDMETHODIMP CTextView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	CComQIPtr<ICommandTarget> target;

// Try edit control
	target = m_edit;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

// Try document
	target = m_document;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}
#endif

LRESULT CTextView::OnViewWordWrap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL wordWrap;
	m_edit->get_wordWrap(&wordWrap);
	m_edit->put_wordWrap(wordWrap? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CTextView::OnViewWordWrapUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL wordWrap;
	m_edit->get_wordWrap(&wordWrap);
	pCmdUI->SetCheck(wordWrap? TRUE: FALSE);
}

LRESULT CTextView::OnViewLineNumbers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL lineNumbers;
	m_edit->get_lineNumbers(&lineNumbers);
	m_edit->put_lineNumbers(lineNumbers? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CTextView::OnViewLineNumbersUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL lineNumbers;
	m_edit->get_lineNumbers(&lineNumbers);
	pCmdUI->SetCheck(lineNumbers? TRUE: FALSE);
}

LRESULT CTextView::OnViewWhitespace(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_viewWhitespace = (m_viewWhitespace)? VARIANT_FALSE: VARIANT_TRUE;
	if (m_viewWhitespace)
	{
		m_edit->put_viewTabs(VARIANT_TRUE);
		m_edit->put_viewSpaces(VARIANT_TRUE);
		m_edit->put_viewEOLs(VARIANT_TRUE);
	}
	else
	{
		m_edit->put_viewTabs(VARIANT_FALSE);
		m_edit->put_viewSpaces(VARIANT_FALSE);
		m_edit->put_viewEOLs(VARIANT_FALSE);
	}

	return 0;
}

void CTextView::OnViewWhitespaceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_viewWhitespace? TRUE: FALSE);
}

LRESULT CTextView::OnWindowNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	m_document->
	NewWindow(eframe);
#endif
	return 0;
}

#endif