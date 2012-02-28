// CScriptSourceView.cpp : Implementation of CScriptSourceView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ScriptSourceView.h"

#include "EScriptDocument.h"
//#include "EXMLViewGroup.h"
#include "LXMLEditorApp.h"

#if 0

static long COLOR_XML_ELEMENT_NAME;
static long COLOR_XML_ATTRIBUTE_NAME;
static long COLOR_XML_ATTRIBUTE_VALUE;
static long COLOR_XML_PREPROCESSING_INSTRUCTION;
static long COLOR_XML_TAG_DELIMITER;
static long COLOR_XML_COMMENT;
static long COLOR_XML_OPERATOR;

static long COLOR_JSCRIPT_KEYWORD;
static long COLOR_JSCRIPT_STRING;
static long COLOR_JSCRIPT_COMMENT;

/////////////////////////////////////////////////////////////////////////////
// CScriptSourceView

int CScriptSourceView::FinalConstruct()
{
	HRESULT hr;

	hr = m_errorListCtl.CoCreateInstance(CLSID_ErrorListCtl);
	if (FAILED(hr)) return hr;

	hr = m_edit.CoCreateInstance(CLSID_UIEdit);
	if (FAILED(hr)) return hr;
/*
	hr = CComObject<CAutoListMembersWindow>::CreateInstance(&m_pAutoListMembersWindow);
	if (FAILED(hr)) return hr;
	m_pAutoListMembersWindow->AddRef();
*/
	return S_OK;
}

void CScriptSourceView::FinalRelease()
{
/*	if (m_pAutoListMembersWindow)
	{
		m_pAutoListMembersWindow->Release();
		m_pAutoListMembersWindow = NULL;
	}
	*/
}

STDMETHODIMP CScriptSourceView::OnDragOut(IUIDockBar* dockBar)
{
//	m_viewGroup->DragOut(m_view, dockBar);

#if 0
	CComQIPtr<ILXAddin> addin = static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p);
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	//CComPtr<IUIDlgSheet> sheet;

	//CComObject<CViewSheet>* pViewSheet;
	//CComObject<CViewSheet>::CreateInstance(&pViewSheet);
	//pViewSheet->AddRef();
	//m_viewGroup->m_sheets.Add(pViewSheet);

	CViewDlg* pViewDlg = new CViewDlg;
	static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_uiManager->CreateDlgSheet(NULL, &/*pViewSheet->m_*/pViewDlg->m_sheet);
	if (m_view->m_ownerSheet)
	{
		m_view->m_ownerSheet->RemoveView(m_view);
	}
	pViewDlg->m_view = m_view;
	m_view->m_ownerSheet = pViewDlg;

	static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_viewDialogs.Add(pViewDlg);

	{
		CComPtr<IUIDlgSite> dlgsite;
		/*pViewSheet->m_*/pViewDlg->m_sheet->GetDlgSite(&dlgsite);
		dockBar->DockControlBar(dlgsite, NULL);
	}

	// Dock all views of all viewgroups of all documents
	for (int i = 0; i < m_viewGroup->m_pDocument->m_viewGroups.GetSize(); i++)
	{
		IUIDlg* dlg = m_viewGroup->m_pDocument->m_viewGroups[i]->m_views[pViewDlg->m_view->m_index];

		CComPtr<IUIDlgSite> dlgSite;
		dlg->GetDlgSite(&dlgSite);;

		m_viewGroup->m_pDocument->m_viewGroups[i]->m_dialogs.Add(dlg);

		CComQIPtr<IUIDockBar>(/*pViewSheet->m_*/pViewDlg->m_sheet)->DockControlBar(dlgSite, NULL);
	}
#endif

#if 0
	CComQIPtr<IEFrame> pFrame = lxframe;

	CComPtr<IUIViewSheet> documentsSheet;
	pFrame->CreateViewSheet(L"", NULL, &documentsSheet);
	static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_documentsSheets.Add(documentsSheet);

	CComPtr<IUIViewSheet> viewGroupSheet;
	pFrame->CreateViewSheet(m_viewGroup->m_pDocument->m_fileTitle, m_viewGroup, &viewGroupSheet);
	//CComPtr<IUIDlgSite> dlgsite;
	//viewGroupSheet->GetDlgSite(&dlgsite);

	m_viewGroup->m_sheets.Add(viewGroupSheet);

	{
		CComPtr<IUIDlgSite> dlgsite;
		viewGroupSheet->GetDlgSite(&dlgsite);
		CComQIPtr<IUIDockBar>(documentsSheet)->DockControlBar(dlgsite, NULL);
	}

	//site->SetName(m_fileTitle);

//	CComPtr<IUIFrame> frame;
//	m_dlgSite->GetParentFrame(&frame);

	static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_documentsSheets.Add(viewGroupSheet);

	{
		CComPtr<IUIDlgSite> dlgsite;
		documentsSheet->GetDlgSite(&dlgsite);
		dockBar->DockControlBar(dlgsite, NULL);
	}

	for (int i = 0; i < static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_xmlDocuments.GetSize(); i++)
	{
		for (int j = 0; j < static_cast<CEXMLDocument*>(static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_xmlDocuments[i])->m_viewGroups.GetSize(); j++)
		{
			CComPtr<IUIDlgSite> site;
		}
	}

	{
		CComPtr<IUIDlgSite> dlgsite;
		GetDlgSite(&dlgsite);
		//static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_uiManager->CreateDlgSite(L"Source", this, &dlgsite);

		CComQIPtr<IUIDockBar>(viewGroupSheet)->DockControlBar(dlgsite, NULL);
	}
#endif

	return S_OK;
}

STDMETHODIMP CScriptSourceView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	if (bActivate)
	{
/*		CComPtr<IDocumentsClass> documentsClass;
		m_document->GetDocumentsClass(&documentsClass);

		uiManager->ActivateObject(documentsClass, m_document);
		uiManager->ActivateObject(m_document, m_viewGroup->GetUnknown());
*/		uiManager->ActivateObject(m_viewGroup->GetUnknown(), GetUnknown());

//		m_objectSelection->FromTargets(m_targetObjects.GetData(), m_targetObjects.GetSize());
//		uiManager->ActivateObject(GetUnknown(), m_objectSelection->GetUnknown());
	}
	else
	{
		uiManager->DeactivateObject(GetUnknown());
//		uiManager->DeactivateObject(m_viewGroup->GetUnknown());
//		uiManager->DeactivateObject(m_document);
	}
#endif
	return S_OK;
}

long CScriptSourceView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	CRect client;
	GetClientRect(&client);

	CRect toprect(0, 0, client.right, 16);
	FillSolidRect(hDC, &toprect, GetSysColor(COLOR_BTNFACE));

	{
		HBITMAP m_expandedBitmap;
		m_expandedBitmap = LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_EXPANDED));

		TransparentBlt(hDC, 2, 2, 10, 14, m_expandedBitmap, m_bErrorsExpanded*10, 0, RGB(192, 192, 192));

		DeleteObject(m_expandedBitmap);
	}

	if (m_bErrorsExpanded)
	{
	// Draw split
		FillSolidRect(hDC, 0, toprect.bottom+m_splity-3, client.right, 6, GetSysColor(COLOR_BTNFACE));
		Draw3DRect(hDC, 0, toprect.bottom+m_splity-3, client.right, 6, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
	}

	EndPaint(&ps);
#endif
	return 0;
}

long CScriptSourceView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

long CScriptSourceView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (point.x < 16 && point.y < 16)
	{
		m_bErrorsExpanded = !m_bErrorsExpanded;
		OnSize();
		InvalidateRect(NULL, TRUE);
	}
	else if (abs(point.y-16-m_splity) < 6)
	{
		m_dragging = 1;
		SetCapture();
	}

	return 0;
}

long CScriptSourceView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}

	return 0;
}

long CScriptSourceView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (m_dragging)
	{
		m_splity = point.y-16;
		if (m_splity > client.bottom-16-16-4) m_splity = client.bottom-16-16-4;
		if (m_splity < 3) m_splity = 3;

		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return 0;
}

long CScriptSourceView::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	int nHittest = (int)LOWORD(lParam);  // hit-test code 
	int wMouseMsg = (int)HIWORD(lParam); // mouse-message identifier 
 
	if (nHittest == HTCLIENT)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (abs(point.y-16-m_splity) < 6)
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			return TRUE;
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

long CScriptSourceView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IEXMLDocument> eXMLDocument = m_document;

	CComQIPtr<ITextData> textDocument = m_document->m_textData;//get_textData(&textDocument);

//	m_document->get_textDocument(&textDocument);

	CComQIPtr<IOleUndoManager> undoManager;
	m_document->get_undoManager(&undoManager);

	IUnknown* p;
	CRect rc(0,0,0,0);

	m_axerrorListCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axerrorListCtl.AttachControl(m_errorListCtl, &p);

	m_edit->put_undoManager(undoManager);
	m_edit->put_textDocument(textDocument);
	m_edit->put_vertScroll(TRUE);
	m_edit->put_horzScroll(TRUE);
	m_edit->put_multiLine(TRUE);
	m_axedit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axedit.AttachControl(m_edit, &p);

	m_statusBar.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_VISIBLE | WS_CHILD);

	CFormatWindow* pWindow = static_cast<CLXMLEditorApp*>(m_document->m_app.p)->RegisterFormatWindow(L"Source Windows");
	ASSERT(pWindow);

	/*
		m_edit->NewStyle(RGB(255, 0, 0), RGB(255, 255, 255), &COLOR_XML_ELEMENT_NAME);
		m_edit->NewStyle(RGB(0, 190, 0), RGB(255, 255, 255), &COLOR_XML_ATTRIBUTE_NAME);
		m_edit->NewStyle(RGB(0, 0, 255), RGB(255, 255, 255), &COLOR_XML_ATTRIBUTE_VALUE);
		m_edit->NewStyle(RGB(255, 0, 255), RGB(255, 255, 255), &COLOR_XML_TAG_DELIMITER);
		m_edit->NewStyle(RGB(170, 170, 170), RGB(255, 255, 255), &COLOR_XML_COMMENT);
		m_edit->NewStyle(RGB(255, 127, 0), RGB(255, 255, 255), &COLOR_XML_OPERATOR);

		m_edit->NewStyle(RGB(0, 0, 200), RGB(255, 255, 255), &COLOR_JSCRIPT_KEYWORD);
		m_edit->NewStyle(RGB(200, 0, 0), RGB(255, 255, 255), &COLOR_JSCRIPT_STRING);
		m_edit->NewStyle(RGB(0, 190, 0), RGB(255, 255, 255), &COLOR_JSCRIPT_COMMENT);
	*/
	{
		//long index;

		m_edit->NewStyle(&COLOR_XML_PREPROCESSING_INSTRUCTION);
		m_edit->NewStyle(&COLOR_XML_ELEMENT_NAME);
		m_edit->NewStyle(&COLOR_XML_ATTRIBUTE_NAME);
		m_edit->NewStyle(&COLOR_XML_ATTRIBUTE_VALUE);
		m_edit->NewStyle(&COLOR_XML_TAG_DELIMITER);
		m_edit->NewStyle(&COLOR_XML_COMMENT);
		m_edit->NewStyle(&COLOR_XML_OPERATOR);
		m_edit->NewStyle(&COLOR_JSCRIPT_KEYWORD);
		m_edit->NewStyle(&COLOR_JSCRIPT_STRING);
		m_edit->NewStyle(&COLOR_JSCRIPT_COMMENT);
	}

	OnPrefsChange();	// Initialize edit control

	FormatText();

	HRESULT hr;

	hr = IDispEventImpl<1, CScriptSourceView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_edit);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<2, CScriptSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>::DispEventAdvise(m_errorListCtl);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<3, CScriptSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document->GetUnknown());
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<4, CScriptSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document->m_app);
	ASSERT(SUCCEEDED(hr));

	CComQIPtr<IErrorList> errorList = m_document;

	m_errorListCtl->put_errorList(errorList);
	m_errorListCtl->UpdateList();

	return 0;
}

long CScriptSourceView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT hr;

	hr = IDispEventImpl<1, CScriptSourceView, &DIID__IUIEditEvents	, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_edit);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<2, CScriptSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>::DispEventUnadvise(m_errorListCtl);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<3, CScriptSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document->GetUnknown());
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<4, CScriptSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document->m_app);
	ASSERT(SUCCEEDED(hr));

	return 0;
}

long CScriptSourceView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	if (client.bottom > 0)
	{
		if (m_splity > client.bottom-16-16-4) m_splity = client.bottom-16-16-4;
		if (m_splity < 3) m_splity = 3;
	}

	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CScriptSourceView::OnSize()
{
	CRect client;
	GetClientRect(&client);

	int editTop = 16;

	if (m_bErrorsExpanded)
	{
		m_axerrorListCtl.MoveWindow(0, editTop, client.right, m_splity-3, TRUE);

		editTop += m_splity+3;
	}
	else
	{
		m_axerrorListCtl.MoveWindow(0, 0, 0, 0, TRUE);
	}

	m_axedit.MoveWindow(0, editTop, client.right, client.bottom-editTop-16, TRUE);
	m_statusBar.MoveWindow(0, client.bottom-16, client.right, 16, TRUE);
}

STDMETHODIMP CScriptSourceView::get_document(IEDocument **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

void __stdcall CScriptSourceView::OnGotoError(IErrorItem* errorItem)
{
	CComBSTR uri;
	errorItem->get_uri(&uri);

	long offset;
	errorItem->GetOffset(&offset);

	m_edit->setCursorPosOffset(offset);

	CComPtr<IUnknown> document;
	m_document->m_app->OpenDocument(uri, &document);
	if (document)
	{
	//	edocument->Activate();
	}
}

void CScriptSourceView::FormatJScript(BSTR data, int& pos, unsigned long length, bool bCDATA)
{
	long styleIndex = 0;

	if (!bCDATA)
	{
// Check for comment <!--

		// Skip spaces
		while (pos < length && iswspace(data[pos])) pos++;

		int start = pos;

		if (
			(						 data[pos] == L'<') &&
			(pos < length-1 && data[pos+1] == L'!') &&
			(pos < length-2 && data[pos+2] == L'-') &&
			(pos < length-2 && data[pos+3] == L'-'))
		{
			pos += 4;

		// Comment out to end of line
			while (pos < length)
			{
				WCHAR c = data[pos++];
				if (c == L'\n') break;
			}

			m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_COMMENT, &styleIndex);
		}
	}

	// JavaScript
	while (pos < length)
	{
		if (bCDATA)
		{
			if (
				(						 data[pos+0] == L']') &&
				(pos < length-1 && data[pos+1] == L']') &&
				(pos < length-2 && data[pos+2] == L'>'))
			{
				pos += 3;
				break;
			}
		}
		else
		{
			if (data[pos] == L'<')	// Start of new element
			{
				break;
			}
		}

		if (iswalpha(data[pos]) || data[pos] == L'_')	// Start of keyword/identifier
		{
			int start = pos;
			BSTR idstr = &data[pos];

			pos++;

			while (pos < length &&
				(iswalnum(data[pos]) || data[pos] == L'_'))
			{
				pos++;
			}

			int len = pos-start;

			if (
				(len == 8 && !wcsncmp(idstr, L"function", 8)) ||
				(len == 3 && !wcsncmp(idstr, L"var", 3)) ||

				(len == 2 && !wcsncmp(idstr, L"if", 2)) ||
				(len == 4 && !wcsncmp(idstr, L"else", 4)) ||
				(len == 5 && !wcsncmp(idstr, L"while", 5)) ||
				(len == 3 && !wcsncmp(idstr, L"for", 3)) ||
				(len == 2 && !wcsncmp(idstr, L"do", 2)) ||
				(len == 4 && !wcsncmp(idstr, L"goto", 4)) ||
				(len == 6 && !wcsncmp(idstr, L"return", 6)) ||
				(len == 5 && !wcsncmp(idstr, L"break", 5)) ||
				(len == 8 && !wcsncmp(idstr, L"continue", 8)) ||

				(len == 6 && !wcsncmp(idstr, L"switch", 6)) ||
				(len == 4 && !wcsncmp(idstr, L"case", 4)) ||
				(len == 7 && !wcsncmp(idstr, L"default", 7)) ||

				(len == 3 && !wcsncmp(idstr, L"try", 3)) ||
				(len == 5 && !wcsncmp(idstr, L"catch", 5)) ||
				// ?? (len == 5 && !wcsncmp(idstr, L"throw", 5)) ||

				(len == 3 && !wcsncmp(idstr, L"new", 3)) ||
				(len == 6 && !wcsncmp(idstr, L"delete", 6)) ||

				(len == 4 && !wcsncmp(idstr, L"true", 4)) ||
				(len == 5 && !wcsncmp(idstr, L"false", 5)) ||
				(len == 4 && !wcsncmp(idstr, L"null", 4)))
			{
				m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_KEYWORD, &styleIndex);
			}
			else	// Identifier
			{
			}
		}
		else if (data[pos] == L'"' || data[pos] == L'\'')	// String
		{
			int start = pos;
			WCHAR delimiter = data[pos++];

			while (pos < length)
			{
				WCHAR c = data[pos++];
				if (c == L'\\')
				{
					pos++;
				}
				else
				{
					if (c == delimiter)
						break;
				}
			}

			m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_STRING, &styleIndex);
		}
		else if (data[pos] == L'/')
		{
			int start = pos++;

			if (pos < length && data[pos] == L'/')	// One-line comment
			{
				pos++;

			// Comment out to end of line
				while (pos < length)
				{
					if (data[pos++] == L'\n')
					{
						break;
					}
				}

				m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_COMMENT, &styleIndex);
			}
			else if (pos < length && data[pos] == L'*')	// Multi-line comment
			{
				pos++;

			// Comment out until we reach */
				while (pos < length)
				{
					if (data[pos++] == L'*')
					{
						if (pos < length)
						{
							if (data[pos++] == L'/')
								break;
						}
					}
				}

				m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_COMMENT, &styleIndex);
			}
			/*
			else
			{
				pos++;
			}
			*/
		}
		else
		{
			pos++;
		}
	}
}

void CScriptSourceView::FormatVBScript(BSTR data, int& pos, unsigned long length, bool bCDATA)
{
	long styleIndex = 0;

	if (!bCDATA)
	{
// Check for comment <!--

		// Skip spaces
		while (pos < length && iswspace(data[pos])) pos++;

		int start = pos;

		if (
			(						 data[pos] == L'<') &&
			(pos < length-1 && data[pos+1] == L'!') &&
			(pos < length-2 && data[pos+2] == L'-') &&
			(pos < length-2 && data[pos+3] == L'-'))
		{
			pos += 4;

		// Comment out to end of line
			while (pos < length)
			{
				WCHAR c = data[pos++];
				if (c == L'\n') break;
			}

			m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_COMMENT, &styleIndex);
		}
	}

	// VBScript
	while (pos < length)
	{
		if (bCDATA)
		{
			if (
				(						 data[pos+0] == L']') &&
				(pos < length-1 && data[pos+1] == L']') &&
				(pos < length-2 && data[pos+2] == L'>'))
			{
				pos += 3;
				break;
			}
		}
		else
		{
			if (data[pos] == L'<')	// Start of new element
			{
				break;
			}
		}

		if (iswalpha(data[pos]) || data[pos] == L'_')	// Start of keyword/identifier
		{
			int start = pos;
			BSTR idstr = &data[pos];

			pos++;

			while (pos < length &&
				(iswalnum(data[pos]) || data[pos] == L'_'))
			{
				pos++;
			}

			int len = pos-start;

#define TESTKEYWORD(x, y) (len == y && !wcsnicmp(idstr, x, y))

			if (
				TESTKEYWORD(L"Abs", 3) ||
				TESTKEYWORD(L"And", 3) ||
				TESTKEYWORD(L"Array", 5) ||
				TESTKEYWORD(L"Asc", 3) ||
				TESTKEYWORD(L"Atn", 3) ||
				TESTKEYWORD(L"Call", 4) ||
				TESTKEYWORD(L"Case", 4) ||
				TESTKEYWORD(L"CBool", 5) ||
				TESTKEYWORD(L"CByte", 5) ||
				TESTKEYWORD(L"CCur", 4) ||
				TESTKEYWORD(L"CDate", 5) ||
				TESTKEYWORD(L"CDbl", 4) ||
				TESTKEYWORD(L"Chr", 3) ||
				TESTKEYWORD(L"CInt", 4) ||
				TESTKEYWORD(L"Class", 5) ||
				TESTKEYWORD(L"Clear", 5) ||
				TESTKEYWORD(L"CLng", 4) ||
				TESTKEYWORD(L"Const", 5) ||
				TESTKEYWORD(L"Cos", 3) ||
				TESTKEYWORD(L"CreateObject", 12) ||
				TESTKEYWORD(L"CSng", 4) ||
				TESTKEYWORD(L"CStr", 4) ||
				TESTKEYWORD(L"Date", 4) ||
				TESTKEYWORD(L"DateAdd", 7) ||
				TESTKEYWORD(L"DateDiff", 8) ||
				TESTKEYWORD(L"DatePart", 8) ||
				TESTKEYWORD(L"DateSerial", 10) ||
				TESTKEYWORD(L"DateValue", 9) ||
				TESTKEYWORD(L"Day", 3) ||
				TESTKEYWORD(L"Dim", 3) ||
				TESTKEYWORD(L"Do", 2) ||
				TESTKEYWORD(L"Else", 4) ||
				TESTKEYWORD(L"ElseIf", 6) ||
				TESTKEYWORD(L"Empty", 5) ||
				TESTKEYWORD(L"End", 3) ||
				TESTKEYWORD(L"Eqv", 3) ||
				TESTKEYWORD(L"Erase", 5) ||
				TESTKEYWORD(L"Err", 3) ||
				TESTKEYWORD(L"Eval", 4) ||
				TESTKEYWORD(L"Execute", 7) ||
				TESTKEYWORD(L"Exit", 4) ||
				TESTKEYWORD(L"Exp", 3) ||
				TESTKEYWORD(L"False", 5) ||
				TESTKEYWORD(L"Filter", 6) ||
				TESTKEYWORD(L"Fix", 3) ||
				TESTKEYWORD(L"For", 3) ||
				TESTKEYWORD(L"FormatCurrency", 14) ||
				TESTKEYWORD(L"FormatDateTime", 14) ||
				TESTKEYWORD(L"FormatNumber", 12) ||
				TESTKEYWORD(L"FormatPercent", 13) ||
				TESTKEYWORD(L"Function", 8) ||
				TESTKEYWORD(L"GetObject", 9) ||
				TESTKEYWORD(L"GetRef", 6) ||
				TESTKEYWORD(L"Hex", 3) ||
				TESTKEYWORD(L"Hour", 4) ||
				TESTKEYWORD(L"If", 2) ||
				TESTKEYWORD(L"Imp", 3) ||
				TESTKEYWORD(L"InputBox", 8) ||
				TESTKEYWORD(L"InStr", 5) ||
				TESTKEYWORD(L"InStrRev", 8) ||
				TESTKEYWORD(L"Int", 3) ||
				TESTKEYWORD(L"Is", 2) ||
				TESTKEYWORD(L"IsArray", 7) ||
				TESTKEYWORD(L"IsDate", 6) ||
				TESTKEYWORD(L"IsEmpty", 7) ||
				TESTKEYWORD(L"IsNull", 6) ||
				TESTKEYWORD(L"IsNumeric", 9) ||
				TESTKEYWORD(L"IsObject", 8) ||
				TESTKEYWORD(L"Join", 4) ||
				TESTKEYWORD(L"LBound", 6) ||
				TESTKEYWORD(L"LCase", 5) ||
				TESTKEYWORD(L"Left", 4) ||
				TESTKEYWORD(L"Len", 3) ||
				TESTKEYWORD(L"LoadPicture", 11) ||
				TESTKEYWORD(L"Log", 3) ||
				TESTKEYWORD(L"Loop", 4) ||
				TESTKEYWORD(L"LTrim", 5) ||
				TESTKEYWORD(L"Mid", 3) ||
				TESTKEYWORD(L"Minute", 6) ||
				TESTKEYWORD(L"Mod", 3) ||
				TESTKEYWORD(L"Month", 5) ||
				TESTKEYWORD(L"MonthName", 9) ||
				TESTKEYWORD(L"MsgBox", 6) ||
				TESTKEYWORD(L"Not", 3) ||
				TESTKEYWORD(L"Now", 3) ||
				TESTKEYWORD(L"Nothing", 7) ||
				TESTKEYWORD(L"Null", 4) ||
				TESTKEYWORD(L"Oct", 3) ||
				TESTKEYWORD(L"On", 2) ||
				TESTKEYWORD(L"Option", 6) ||
				TESTKEYWORD(L"Or", 2) ||
				TESTKEYWORD(L"Private", 7) ||
				TESTKEYWORD(L"Public", 6) ||
				TESTKEYWORD(L"Randomize", 9) ||
				TESTKEYWORD(L"ReDim", 5) ||
				TESTKEYWORD(L"Replace", 7) ||
				TESTKEYWORD(L"RGB", 3) ||
				TESTKEYWORD(L"Right", 5) ||
				TESTKEYWORD(L"Rnd", 3) ||
				TESTKEYWORD(L"Round", 5) ||
				TESTKEYWORD(L"RTrim", 5) ||
				TESTKEYWORD(L"Second", 6) ||
				TESTKEYWORD(L"Select", 6) ||
				TESTKEYWORD(L"Set", 3) ||
				TESTKEYWORD(L"Sgn", 3) ||
				TESTKEYWORD(L"Sin", 3) ||
				TESTKEYWORD(L"Space", 5) ||
				TESTKEYWORD(L"Split", 5) ||
				TESTKEYWORD(L"Sqr", 3) ||
				TESTKEYWORD(L"StrComp", 7) ||
				TESTKEYWORD(L"String", 6) ||
				TESTKEYWORD(L"StrReverse", 10) ||
				TESTKEYWORD(L"Sub", 3) ||
				TESTKEYWORD(L"Tan", 3) ||
				TESTKEYWORD(L"Then", 4) ||
				TESTKEYWORD(L"Time", 4) ||
				TESTKEYWORD(L"Timer", 5) ||
				TESTKEYWORD(L"TimeSerial", 10) ||
				TESTKEYWORD(L"TimeValue", 9) ||
				TESTKEYWORD(L"Trim", 4) ||
				TESTKEYWORD(L"True", 4) ||
				TESTKEYWORD(L"TypeName", 8) ||
				TESTKEYWORD(L"UBound", 6) ||
				TESTKEYWORD(L"UCase", 5) ||
				TESTKEYWORD(L"Until", 5) ||
				TESTKEYWORD(L"VarType", 7) ||
				TESTKEYWORD(L"Weekday", 7) ||
				TESTKEYWORD(L"WeekdayName", 11) ||
				TESTKEYWORD(L"Wend", 4) ||
				TESTKEYWORD(L"While", 5) ||
				TESTKEYWORD(L"With", 4) ||
				TESTKEYWORD(L"Xor", 3) ||
				TESTKEYWORD(L"Year", 4))
			{
				m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_KEYWORD, &styleIndex);
			}
			else	// Identifier
			{
			}
		}
		else if (data[pos] == L'"')	// String
		{
			int start = pos;
			WCHAR delimiter = data[pos++];

			while (pos < length)
			{
				WCHAR c = data[pos++];
				if (c == delimiter)
					break;
			}

			m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_STRING, &styleIndex);
		}
		else if (data[pos] == L'\'') // Comment out to end of line
		{
			int start = pos++;

		// Comment out to end of line
			while (pos < length)
			{
				if (data[pos++] == L'\n')
				{
					break;
				}
			}

			m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_COMMENT, &styleIndex);
		}
		else
		{
			pos++;
		}
	}
}

void CScriptSourceView::FormatText()
{
	m_edit->ClearFormatting();

	//if (TRUE) return;

	CComQIPtr<ITextData> textDoc;
	m_edit->get_textDocument((IDispatch**)&textDoc);

	BSTR data;
	textDoc->get_data(&data);

	long length;
	textDoc->get_len(&length);

	long styleIndex = 0;

	bool bCDATA = false;
	bool bScriptElement = false;
	int scriptLanguage = 0;

	int pos = 0;
	while (pos < length)
	{
		if (data[pos] == L'<')	// Start of new tag/comment/CDATA, or end of tag
		{
			int start = pos++;

			if (data[pos] == L'?')	// start of preprocessing instruction
			{
				pos++;

				while (pos < length)
				{
					// Not sure about this
					if ((data[pos] == L'?') &&
						(pos < length-1 && data[pos+1] == L'>'))
					{
						break;
					}
					pos++;
				}

				m_edit->FormatRange(start, pos-start, COLOR_XML_PREPROCESSING_INSTRUCTION, &styleIndex);
			}
			else if (data[pos] == L'!')	// start of comment/CDATA
			{
				pos++;
				if (pos < length && data[pos] == L'[')
				{
					pos += 6;	// TODO check for CDATA[
					bCDATA = true;

					if (bScriptElement)
					{
						if (scriptLanguage == 1)
							FormatJScript(data, pos, length, bCDATA);
						else if (scriptLanguage == 2)
							FormatVBScript(data, pos, length, bCDATA);
					}
				}
				else	// Comment
				{
					if ((pos < length && data[pos+0] == L'-') &&
						(pos < length-1 && data[pos+1] == L'-'))
					{
						pos += 2;

						while (pos < length)
						{
							if ((data[pos] == L'-') &&
								(pos < length-1 && data[pos+1] == L'-'))
							{
								pos += 2;
								if (pos < length && data[pos] == L'>')
								{
									pos++;
								}

								break;
							}

							pos++;
						}

						m_edit->FormatRange(start, pos-start, COLOR_XML_COMMENT, &styleIndex);
					}
				}
			}
			else
			{
				bCDATA = false;

			// Skip spaces
				while (pos < length && iswspace(data[pos])) pos++;

				if (data[pos] == L'/')	// End of tag
				{
					pos++;
					m_edit->FormatRange(start, pos-start, COLOR_XML_TAG_DELIMITER, &styleIndex);

				// Get element name
					{
						start = pos;

						while (pos < length && (iswalnum(data[pos]) || data[pos] == L'-' || data[pos] == L':' || data[pos] == L'.'))
							pos++;

						m_edit->FormatRange(start, pos-start, COLOR_XML_ELEMENT_NAME, &styleIndex);
					}

				// Get '...>'
					{
						start = pos;

					// Skip spaces
						while (pos < length && iswspace(data[pos])) pos++;

						if (data[pos] == L'>')
						{
							pos++;
							m_edit->FormatRange(start, pos-start, COLOR_XML_TAG_DELIMITER, &styleIndex);
						}
					}

					bScriptElement = false;
				}
				else	// Start of new tag
				{
					m_edit->FormatRange(start, pos-start, COLOR_XML_TAG_DELIMITER, &styleIndex);

				// Get element name
					start = pos;
					WCHAR* elementName = &data[pos];

					while (pos < length && (iswalnum(data[pos]) || data[pos] == L'-' || data[pos] == L':' || data[pos] == L'.'))
						pos++;

					bScriptElement = ((pos-start) == 6) && (wcsnicmp(elementName, L"SCRIPT", 6) == 0);
					scriptLanguage = 1;	// default to JScript

					m_edit->FormatRange(start, pos-start, COLOR_XML_ELEMENT_NAME, &styleIndex);

					// Skip spaces
					while (pos < length && iswspace(data[pos])) pos++;

				// Get element attributes
					while (pos < length)
					{
						if (!iswalpha(data[pos])) break;

					// Get attribute name
						WCHAR* attrName = &data[pos];
						int start = pos++;

						while (pos < length &&
							(iswalnum(data[pos]) || data[pos] == L'_' || data[pos] == L'-' || data[pos] == L':' || data[pos] == L'.'))
						{
							pos++;
						}

						bool bScriptLangAttr = false;
						if (bScriptElement)
						{
							if ((pos-start == 8) && !wcsnicmp(attrName, L"language", 8))
							{
								bScriptLangAttr = true;
							}
						}

						m_edit->FormatRange(start, pos-start, COLOR_XML_ATTRIBUTE_NAME, &styleIndex);

					// Skip spaces
						while (pos < length && iswspace(data[pos])) pos++;

						if (data[pos] == L'=')
						{
							m_edit->FormatRange(pos, 1, COLOR_XML_OPERATOR, &styleIndex);
							pos++;

						// Skip spaces
							while (pos < length && iswspace(data[pos])) pos++;

							int start = pos;

							int attrvalstart;
							int attrvalend;

						// Get attribute value
							WCHAR delimiter = data[pos];
							if (delimiter == L'"' || delimiter == L'\'')	// " delimiter around attribute value (XML valid)
							{
								pos++;
								attrvalstart = pos;

								while (pos < length)
								{
									if (data[pos] == delimiter) break;
									pos++;
								}

								attrvalend = pos;

								if (data[pos] == delimiter)
									pos++;
							}
							else if (true)	// Allow non-XML attribute value
							{
								attrvalstart = pos;
								while (pos < length)
								{
									WCHAR c = data[pos];

									if (iswspace(c) || c == L'>' || c == L'/')
										break;

									pos++;
								}

								attrvalend = pos;
							}

							m_edit->FormatRange(start, pos-start, COLOR_XML_ATTRIBUTE_VALUE, &styleIndex);

							if (bScriptLangAttr)
							{
								WCHAR* attrval = &data[attrvalstart];
								int len = attrvalend-attrvalstart;

								if (
									(len == 7 && !wcsnicmp(attrval, L"JScript", 7)) ||
									(len == 10 && !wcsnicmp(attrval, L"JavaScript", 10)))
								{
									scriptLanguage = 1;
								}
								else if (
									(len == 3 && !wcsnicmp(attrval, L"VBS", 3)) ||
									(len == 8 && !wcsnicmp(attrval, L"VBScript", 8)))
								{
									scriptLanguage = 2;
								}
								else	// Unknown language
								{
									scriptLanguage = 0;
								}
							}
						}

					// Skip spaces
						while (pos < length && iswspace(data[pos])) pos++;
					}

					if (data[pos] == L'/')	// Immediate end tag
					{
						int start = pos++;

					// Skip spaces
						while (pos < length && iswspace(data[pos])) pos++;

						if (data[pos] == L'>')
						{
							pos++;
							m_edit->FormatRange(start, pos-start, COLOR_XML_TAG_DELIMITER, &styleIndex);
						}
					}
					else if (data[pos] == L'>')
					{
						m_edit->FormatRange(pos, 1, COLOR_XML_TAG_DELIMITER, &styleIndex);
						pos++;
					}
				}

				if (bScriptElement)
				{
					if (scriptLanguage == 1)
						FormatJScript(data, pos, length, bCDATA);
					else if (scriptLanguage == 2)
						FormatVBScript(data, pos, length, bCDATA);
				}
			}
		}
		else
		{
			pos++;
		}
	}
}

/*
void CScriptSourceView::SetRange(ILDOMRange* range)
{
	CComPtr<ILDOMNode> startContainer;
	long startOffset;

	CComPtr<ILDOMNode> endContainer;
	long endOffset;

	range->get_startContainer(&startContainer);
	range->get_startOffset(&startOffset);

	range->get_endContainer(&endContainer);
	range->get_endOffset(&endOffset);

	if (startContainer && endContainer)
	{
		long start = GetTextOffsetFromNode(startContainer, startOffset);
		long end = GetTextOffsetFromNode(endContainer, endOffset);

		m_edit->SetSel(start, end, VARIANT_TRUE);
	}
}
*/

void __stdcall CScriptSourceView::OnEditChanged()
{
	FormatText();
}

//#include "CSSProperty.h"

void __stdcall CScriptSourceView::OnEditChar(WCHAR nchar)
{
	/*
	if (m_pAutoListMembersWindow->m_hWnd)
	{
		m_pAutoListMembersWindow->DestroyWindow();
	}
	*/

#if 0
	if (nchar == L'<')
	{
		CComQIPtr<IEXMLDocument> document = m_document;
		if (document)
		{
			CComPtr<ILDOMDocument> domDocument;
			document->get_DOMDocument(&domDocument);

			CComQIPtr<ILDocumentEditVAL> documentEditVAL = domDocument;

			if (documentEditVAL)
			{
				CComPtr<ILDOMNameList> definedElements;
				documentEditVAL->getDefinedElementTypes(&definedElements);

				long length;
				definedElements->get_length(&length);

				CComPtr<IUIAutoListWindow> autolist;
				m_edit->AutoList(&autolist);

				for (int i = 0; i < length; i++)
				{
					CComBSTR name;
					definedElements->getName(i, &name);

					autolist->AddString(-1, name, NULL);
				}

				m_edit->AutoListPopup();
			}
		}
	}
	else
#endif
		if (nchar == L'.')
	{
#if 0
		// TODO Check if it's inside a script

		CRect crc;
		m_edit->get_cursorBox(&crc);
		POINT cpt;
		cpt.x = crc.left;
		cpt.y = crc.bottom;
		m_axedit.ClientToScreen(&cpt);

		CRect rc(cpt.x, cpt.y, cpt.x+140, cpt.y+220);

		CComPtr<IDispatch> disp;
		disp.CoCreateInstance(L"MSComDlg.CommonDialog");

		m_pAutoListMembersWindow->SetDispatch(disp);
		//disp.Detach();

		m_pAutoListMembersWindow->Create(m_hWnd, rc,  NULL, WS_DLGFRAME | WS_POPUP, 0, 0);
		m_pAutoListMembersWindow->SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
#endif
	}
#if 0
	else if (nchar == L';')
	{
#if 0
		CRect crc;
		m_edit->get_cursorBox(&crc);
		POINT cpt;
		cpt.x = crc.left;
		cpt.y = crc.bottom;
		m_axedit.ClientToScreen(&cpt);

		CRect rc(cpt.x, cpt.y, cpt.x+140, cpt.y+220);

		/*
		CComPtr<IDispatch> disp;
		disp.CoCreateInstance(L"MSComDlg.CommonDialog");


		m_pAutoListMembersWindow->SetDispatch(disp);
		*/
		for (int i = 0; i < g_nCSSProperties; i++)
		{
			CMemberItem* pMItem = new CMemberItem;

			pMItem->m_name = CSSProperties[i].m_name;
			pMItem->m_dispid = 0;//pFuncDesc->memid;

			m_pAutoListMembersWindow->m_members.Add(pMItem);
		}
		//disp.Detach();

		m_pAutoListMembersWindow->Create(m_hWnd, rc,  NULL, WS_DLGFRAME | WS_POPUP, 0, 0);
		m_pAutoListMembersWindow->SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);

		_bstr_t value = m_pAutoListMembersWindow->GetString();

		m_pAutoListMembersWindow->DestroyWindow();

		if (value.length())
		{
			m_edit->ReplaceSelText(value, value.length());
		}
#endif
		CComPtr<IUIAutoListWindow> autolist;
		m_edit->AutoList(&autolist);

		for (int i = 0; i < g_nCSSProperties; i++)
		{
			autolist->AddString(-1, CSSProperties[i].m_name, NULL);
		}

		m_edit->AutoListPopup();
	}
#endif
}

void __stdcall CScriptSourceView::OnEditMovedCursor(long offset)
{
	long nLine;
	m_edit->get_line(&nLine);

	long nCol;
	m_edit->get_column(&nCol);

	m_statusBar.m_text.Format("Ln %d, Col %d", nLine+1, nCol+1);
	m_statusBar.Invalidate();

#if 0
	/*
	{
		long startsel, endsel;
		m_edit->GetSel(&startsel, &endsel);

	// Convert edit selection to range boundary points
	}
	*/

	CComQIPtr<IEXMLDocument> document = m_document;
	if (document)
	{
		CComPtr<ILDOMDocument> domDocument;
		document->get_DOMDocument(&domDocument);

		if (domDocument)
		{
			CComPtr<ILDOMElement> documentElement;
			domDocument->get_documentElement(&documentElement);

			//CEXMLDocument* pDocument = ((CEXMLDocument*)svgDocument.p);

			m_bSelectingElement++;

			if (documentElement)
			{
				ILDOMElement* element = GetElementFromOffset(documentElement, offset);
				if (element)
				{
					CComPtr<IEElement> eElement;
					document->GetEElementFromDOMElement(element, &eElement);
					ASSERT(eElement);

					m_viewGroup->ActivateElement(eElement, 0, NULL);
				}
				else
				{
					m_viewGroup->ActivateElement(NULL, 0, NULL);
				}
			}
			else
			{
				m_viewGroup->ActivateElement(NULL, 0, NULL);
			}

			m_bSelectingElement--;
		}
	}
#endif
}

HRESULT __stdcall CScriptSourceView::OnDoneParsingDOM()
{
	m_errorListCtl->UpdateList();
	return S_OK;
}

void __stdcall CScriptSourceView::OnPrefsChange()
{
	CFormatWindow* pWindow = static_cast<CLXMLEditorApp*>(m_document->m_app.p)->RegisterFormatWindow(L"Source Windows");
	ASSERT(pWindow);

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
}

/*
void DisplayErrorMsg(long err)
{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );
}
*/
/*
UINT CALLBACK OFNHookProcOldStyle(
  HWND hdlg,      // handle to the dialog box window
  UINT uiMsg,      // message identifier
  WPARAM wParam,  // message parameter
  LPARAM lParam   // message parameter
)
{
	MessageBox(NULL, "", "", MB_OK);
	return 0;
};
*/

/*
void CreateObjectString(OLEUIINSERTOBJECT* oleio)
{
	CComPtr<IUnknown> spObject;
	spObject.CoCreateInstance(oleio->clsid);
}
*/

/*
_bstr_t CreateObjectString(OLEUIINSERTOBJECT* oleio)
{
}
*/

class ATL_NO_VTABLE CCOMObjectBase : public 
	CComObjectRootEx<CComSingleThreadModel>,
//	IDispatchImpl<IDispatch, &IID_IDispatch>,
	IDispatchImpl<IPropertyBag, &IID_IPropertyBag>
{
public:

public:

	CCOMObjectBase()
	{
	}

	CLSID	m_clsid;

	CComPtr<IUnknown> m_spUnknown;
	CComPtr<IOleObject> m_spOleObject;

	CComQIPtr<ILHTMLDocument> m_document;
	CComQIPtr<ILHTMLElement> m_objectElement;

	BOOL Create(CLSID clsid)
	{
		m_document.CoCreateInstance(CLSID_LHTMLDocument);
		m_document->createElement(L"object", (ILDOMElement**)&m_objectElement);

		LPOLESTR clsidstr;
		StringFromCLSID(clsid, &clsidstr);
		m_objectElement->setAttribute(L"classid", _bstr_t(clsidstr));
		CoTaskMemFree(clsidstr);

		m_spUnknown.CoCreateInstance(clsid);
		if (m_spUnknown)
		{
			CComQIPtr<IPersistPropertyBag> ppbag = m_spUnknown;
			if (ppbag)
			{
				ppbag->InitNew();
				ppbag->Save(this, FALSE, TRUE);
			}

			return TRUE;
		}

		return FALSE;
	}

BEGIN_COM_MAP(CCOMObjectBase)
	COM_INTERFACE_ENTRY(IPropertyBag)
END_COM_MAP()

// IPropertyBag
	STDMETHOD(Read)(LPCOLESTR pszPropName, VARIANT* pVar, IErrorLog* pErrorLog)
	{
		return S_OK;
	}
 
	STDMETHOD(Write)(LPCOLESTR pszPropName, VARIANT* pVar)
	{
		CComQIPtr<ILHTMLElement> param;
		m_document->createElement(L"param", (ILDOMElement**)&param);

		VARIANT	dvar;
		VariantInit(&dvar);
		HRESULT hr = VariantChangeType(pVar, &dvar, 0, VT_BSTR);
		if (FAILED(hr))
		{
			return E_FAIL;
		}

		param->setAttribute(L"name", _bstr_t(pszPropName));

		if (dvar.vt == VT_BSTR)
			param->setAttribute(L"value", dvar.bstrVal);
		else
			param->setAttribute(L"value", L"");

		CComPtr<ILDOMNode> result;
		m_objectElement->appendChild(param, &result);

		return S_OK;
	}
 
// IErrorLog
	STDMETHOD(AddError)(
	  LPCOLESTR pszPropName,  //Pointer to the name of the property 
                          // involved with the error
	LPEXCEPINFO pException  //Pointer to the caller-initialized 
                          // EXCEPINFO structure describing the error
	)
	{
		return S_OK;
	}
};

class CCOMObject : public CComObject<CCOMObjectBase>
{
};

BEGIN_CMD_MAP(CScriptSourceView)
// File
	CMD_HANDLER(ID_FILE_PRINT, OnFilePrint)
	CMD_HANDLER(ID_FILE_PAGE_SETUP, OnFilePageSetup)

// Edit
	CMD_HANDLER(ID_EDIT_ADVANCED_MAKESELECTIONUPPERCASE, OnMakeSelectionUppercase)
	CMD_HANDLER(ID_EDIT_ADVANCED_MAKESELECTIONLOWERCASE, OnMakeSelectionLowercase)

// View
	CMD_HANDLER(ID_VIEW_WORDWRAP, OnViewWordWrap)
	CMD_UPDATE(ID_VIEW_WORDWRAP, OnViewWordWrapUpdate)
	CMD_HANDLER(ID_VIEW_LINENUMBERS, OnViewLineNumbers)
	CMD_UPDATE(ID_VIEW_LINENUMBERS, OnViewLineNumbersUpdate)
	CMD_HANDLER(ID_VIEW_VIEWWHITESPACE, OnViewWhitespace)
	CMD_UPDATE(ID_VIEW_VIEWWHITESPACE, OnViewWhitespaceUpdate)
END_CMD_MAP()

LRESULT CScriptSourceView::OnFilePrint(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	PRINTDLG	pd = {0};
	pd.lStructSize = sizeof(pd);
	ASSERT(0);
	pd.hwndOwner = NULL;//GetMainHwnd();
	pd.Flags = PD_RETURNDC;

	if (PrintDlg(&pd))
	{
		DeleteDC(pd.hDC);
	}

	return 0;
}

LRESULT CScriptSourceView::OnFilePageSetup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	PAGESETUPDLG psd = {0};
	psd.lStructSize = sizeof(psd);
	psd.hInstance = NULL;//_Module.m_hInst;
	ASSERT(0);
	psd.hwndOwner = NULL;//GetMainHwnd();

	PageSetupDlg(&psd);

	return 0;
}

LRESULT CScriptSourceView::OnMakeSelectionUppercase(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long startsel, endsel;
	m_edit->GetSel(&startsel, &endsel);
	if (startsel == endsel)
	{
		m_edit->SetSel(startsel, endsel+1, VARIANT_TRUE);
	}

	CComBSTR data;
	m_edit->GetSelText(&data);

	data.ToUpper();

	m_edit->ReplaceSelText(data, data.Length());

	return 0;
}

LRESULT CScriptSourceView::OnMakeSelectionLowercase(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long startsel, endsel;
	m_edit->GetSel(&startsel, &endsel);
	if (startsel == endsel)
	{
		m_edit->SetSel(startsel, endsel+1, VARIANT_TRUE);
	}

	CComBSTR data;
	m_edit->GetSelText(&data);

	data.ToLower();

	m_edit->ReplaceSelText(data, data.Length());

	return 0;
}

LRESULT CScriptSourceView::OnViewWordWrap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL wordWrap;
	m_edit->get_wordWrap(&wordWrap);
	m_edit->put_wordWrap(wordWrap? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CScriptSourceView::OnViewWordWrapUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL wordWrap;
	m_edit->get_wordWrap(&wordWrap);
	pCmdUI->SetCheck(wordWrap? TRUE: FALSE);
}

LRESULT CScriptSourceView::OnViewLineNumbers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL lineNumbers;
	m_edit->get_lineNumbers(&lineNumbers);
	m_edit->put_lineNumbers(lineNumbers? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CScriptSourceView::OnViewLineNumbersUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL lineNumbers;
	m_edit->get_lineNumbers(&lineNumbers);
	pCmdUI->SetCheck(lineNumbers? TRUE: FALSE);
}

LRESULT CScriptSourceView::OnViewWhitespace(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

void CScriptSourceView::OnViewWhitespaceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_viewWhitespace? TRUE: FALSE);
}

#if 0
// ICommandTarget
STDMETHODIMP CScriptSourceView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// try us
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

#endif