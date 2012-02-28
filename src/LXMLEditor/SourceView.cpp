// SourceView.cpp : Implementation of CSourceView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SourceView.h"

#include "EXMLDocument.h"
#include "EXMLViewGroup.h"
#include "LXMLEditorApp.h"

#include "../LXUI/TextDocument.h"

namespace System
{
namespace LXmlEdit
{

static long COLOR_XML_ELEMENT_NAME;
static long COLOR_XML_ATTRIBUTE_NAME;
static long COLOR_XML_ATTRIBUTE_VALUE;
static long COLOR_XML_PREPROCESSING_INSTRUCTION;
static long COLOR_XML_TAG_DELIMITER;
static long COLOR_XML_COMMENT;
static long COLOR_XML_OPERATOR;
static long COLOR_XML_INVALID;

static long COLOR_JSCRIPT_KEYWORD;
static long COLOR_JSCRIPT_STRING;
static long COLOR_JSCRIPT_COMMENT;

Node* GetNodeFromOffsets(Node* node, long startoffset, long endoffset, long index0, long index1)
{
// Try children
	Node* child = node->get_firstChild();

	while (child != NULL)
	{
		//LDOMNodeType nodeType;
		//node->get_nodeType(&nodeType);

		//if (nodeType == NODE_ELEMENT)
		{
		//	CComQIPtr<Web::Element> element2 = node;
		// Try the elements children
			Node* f = GetNodeFromOffsets(child, startoffset, endoffset, index0, index1);
			if (f) return f;
		}

		child = child->get_nextSibling();
	}

// Try us

	NamedNodeMap* attributes = node->get_attributes();

	if (attributes)
	{
		long length = attributes->get_length();

		for (int i = 0; i < length; i++)
		{
			Node* attr = attributes->item(i);

			Node* f = GetNodeFromOffsets(attr, startoffset, endoffset, index0, index1);
			if (f)
				return f;
		}
	}

	long offset0 = node->getTextOffset(index0);
	long offset1 = node->getTextOffset(index1);

	if ((startoffset >= offset0) && (endoffset <= offset1))
	{
		return node;
	}

	return NULL;
}

Node* GetNodeFromOffsets(Node* node, bool bAttrs, long startoffset, long endoffset, long index0, long index1)
{
	ASSERT(0);
#if 0
// Try children
	CComPtr<Web::Node> child;
	node->get_firstChild(&child);

	while (child != NULL)
	{
		//LDOMNodeType nodeType;
		//node->get_nodeType(&nodeType);

		//if (nodeType == NODE_ELEMENT)
		{
		//	CComQIPtr<Web::Element> element2 = node;
		// Try the elements children
			Web::Node* f = GetNodeFromOffsets(child, bAttrs, startoffset, endoffset, index0, index1);
			if (f) return f;
		}

		CComPtr<Web::Node> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

// Try us

	if (bAttrs)
	{
		CComPtr<ILDOMNamedNodeMap> attributes;
		node->get_attributes(&attributes);

		if (attributes)
		{
			long length;
			attributes->get_length(&length);

			for (int i = 0; i < length; i++)
			{
				CComPtr<Web::Node> attr;
				attributes->item(i, &attr);

				Web::Node* f = GetNodeFromOffsets(attr, bAttrs, startoffset, endoffset, index0, index1);
				if (f)
					return f;
			}
		}
	}

	long offset0;
	long offset1;
	node->getTextOffset(index0, &offset0);
	node->getTextOffset(index1, &offset1);

	if ((startoffset >= offset0) && (endoffset <= offset1))
	{
		return node;
	}
#endif
	return NULL;
}

Web::Element* GetElementFromOffset(Web::Element* element, long offset)
{
	ASSERT(0);
#if 0
// Try children
	CComPtr<Web::Node> node;
	element->get_firstChild(&node);

	while (node != NULL)
	{
		LDOMNodeType nodeType;
		node->get_nodeType(&nodeType);

		if (nodeType == NODE_ELEMENT)
		{
			CComQIPtr<Web::Element> element2 = node;
		// Try the elements children
			Web::Element* element3 = GetElementFromOffset(element2, offset);
			if (element3) return element3;
		}

		CComPtr<Web::Node> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

// Try us
	long startoffset;
	long endoffset;
	element->getTextOffset(0, &startoffset);
	element->getTextOffset(4, &endoffset);
	ASSERT(endoffset >= startoffset);

	if ((offset > startoffset) && (offset < endoffset))
	{
		return element;
	}
#endif
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CSourceView

CSourceView::CSourceView(CEXMLViewGroup* viewGroup)
{
	m_bErrorsExpanded = false;
//		m_splity = 60;
	m_dragging = 0;

	m_viewGroup = viewGroup;
//	m_document = NULL;

	m_viewWhitespace = false;

	m_bSelectingElement = false;

	m_edit = new UI::TextEdit;
	//m_edit->set_textDocument(new System::TextDocument());
	m_edit->set_MultiLine(true);

	//m_edit->SetText(L"");
	System::ITextData* textDocument = m_viewGroup->m_pDocument->get_textData();
	//eXMLDocument->get_textData(&textDocument);
	m_edit->set_TextDocument(textDocument);

	set_VisualTree(m_edit);

}

#if 0
int CSourceView::FinalConstruct()
{
	ErrorCode hr;
	ASSERT(0);
#if 0

	hr = m_errorListCtl.CoCreateInstance(CLSID_ErrorListCtl);
	if (FAILED(hr)) return hr;

#if 0
	hr = m_edit.CoCreateInstance(CLSID_UIEdit);
	if (FAILED(hr)) return hr;
#endif
/*
	hr = CComObject<CAutoListMembersWindow>::CreateInstance(&m_pAutoListMembersWindow);
	if (FAILED(hr)) return hr;
	m_pAutoListMembersWindow->AddRef();
*/
#endif
	return Success;
}

void CSourceView::FinalRelease()
{
/*	if (m_pAutoListMembersWindow)
	{
		m_pAutoListMembersWindow->Release();
		m_pAutoListMembersWindow = NULL;
	}
	*/
}
#endif

#if 0
// ILElementBehavior
ErrorCode CSourceView::Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
{
	m_behaviorSite = pBehaviorSite;

	CComPtr<Web::Element> element;
	m_behaviorSite->GetElement(&element);

	CComPtr<ILDOMDocument> document;
	element->get_ownerDocument(&document);

	document->createElementNS(L"http://www.w3.org/1999/xhtml", L"object", (Web::Element**)&m_editObjectElement);
	m_editObjectElement->setAttribute(L"classid", L"clsid:{94327EC1-8D79-4A8E-B9B7-ACCCE8C787EF}");
	m_editObjectElement->setAttribute(L"style", L"-moz-box-flex: 1;");

	document->createElementNS(L"http://www.lerstad.com/2004/lxui", L"p", (Web::Element**)&m_statusBarElement);
	m_statusBarElement->put_textContent(L"");

	element->appendChild(m_editObjectElement, NULL);
	element->appendChild(m_statusBarElement, NULL);

	CComPtr<IUnknown> unk;
	m_editObjectElement->get__object(&unk);

	m_edit = CComQIPtr<IUIEdit>(unk);
	if (m_edit == NULL) return E_FAIL;

	OnCreate();

	return Success;
}

ErrorCode CSourceView::Detach()
{
	m_behaviorSite.Release();
	return Success;
}
#endif

ErrorCode CSourceView::OnDragOut(UI::CUIDockBar* dockBar)
{
	m_viewGroup->DragOut(m_view, dockBar);

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

	return Success;
}

ErrorCode CSourceView::OnActivate(bool bActivate, UI::Control* pActivateView, UI::Control* pDeactivateView)
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
	return Success;
}

#if 0
long CSourceView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
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
	return 0;
}

long CSourceView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

long CSourceView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

long CSourceView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}

	return 0;
}

long CSourceView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
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

long CSourceView::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	UI::Control* hwnd = (UI::Control*) wParam;       // handle to window with cursor 
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
#endif

long CSourceView::OnCreate()
{
	ASSERT(0);
#if 0
	/*
	{
		CComPtr<Web::Element> element;
		m_behaviorSite->GetElement(&element);

		CComPtr<IUnknown> unk;
		element->getUserData(L"n", &unk);
		CComQIPtr<IEXMLViewGroup> viewGroup(unk);

		m_viewGroup = static_cast<CEXMLViewGroup*>(viewGroup.p);
	}
	*/
	ASSERT(m_viewGroup);

	CComQIPtr<IEXMLDocument> eXMLDocument = m_viewGroup->m_pDocument;

	CComQIPtr<ITextData> textDocument;
	eXMLDocument->get_textData(&textDocument);

//	m_document->get_textDocument(&textDocument);

	CComQIPtr<IOleUndoManager> undoManager;
	m_viewGroup->m_pDocument->get_undoManager(&undoManager);

#if 0
	IUnknown* p;
	CRect rc(0,0,0,0);

	m_axerrorListCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axerrorListCtl.AttachControl(m_errorListCtl, &p);
#endif

	m_edit->put_undoManager(undoManager);
	m_edit->put_textDocument(textDocument);
	m_edit->put_vertScroll(TRUE);
	m_edit->put_horzScroll(TRUE);
	m_edit->put_multiLine(TRUE);
//	m_axedit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
//	m_axedit.AttachControl(m_edit, &p);

#if 0
	m_statusBar.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_VISIBLE | WS_CHILD);
#endif

	CFormatWindow* pWindow = static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->RegisterFormatWindow(L"Source Windows");
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
		m_edit->NewStyle(&COLOR_XML_INVALID);
		m_edit->NewStyle(&COLOR_JSCRIPT_KEYWORD);
		m_edit->NewStyle(&COLOR_JSCRIPT_STRING);
		m_edit->NewStyle(&COLOR_JSCRIPT_COMMENT);
	}

	OnPrefsChange();	// Initialize edit control

	FormatText();

	ErrorCode hr;

	hr = IDispEventImpl<1, CSourceView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_edit);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<2, CSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>::DispEventAdvise(m_errorListCtl);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<3, CSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->m_pDocument->GetUnknown());
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<4, CSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->m_pDocument->m_app);
	ASSERT(SUCCEEDED(hr));

	CComQIPtr<IErrorList> errorList = m_viewGroup->m_pDocument;

	m_errorListCtl->put_errorList(errorList);
	m_errorListCtl->UpdateList();
#endif
	return 0;
}

void CSourceView::OnDestroy()
{
	ErrorCode hr;

	ASSERT(0);
#if 0
	hr = IDispEventImpl<1, CSourceView, &DIID__IUIEditEvents	, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_edit);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<2, CSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>::DispEventUnadvise(m_errorListCtl);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<3, CSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->m_pDocument->GetUnknown());
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<4, CSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->m_pDocument->m_app);
	ASSERT(SUCCEEDED(hr));
#endif
}

#if 0
long CSourceView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
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
#endif

#if 0
void CSourceView::OnSize()
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
#endif

// TODO remove this method??
CEDocument* CSourceView::get_document()
{
	return m_viewGroup->m_pDocument;
}

#if 0
void __stdcall CSourceView::OnGotoError(IErrorItem* errorItem)
{
	CComBSTR uri;
	errorItem->get_uri(&uri);

	long offset;
	errorItem->GetOffset(&offset);

	m_edit->setCursorPosOffset(offset);

	CComPtr<IUnknown> document;
	m_viewGroup->m_pDocument->m_app->OpenDocument(uri, &document);
	if (document)
	{
	//	edocument->Activate();
	}
}
#endif

void CSourceView::FormatJScript(const WCHAR * data, int& pos, unsigned long length, bool bCDATA)
{
	ASSERT(0);
#if 0
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
#endif
}

void CSourceView::FormatVBScript(const WCHAR * data, int& pos, unsigned long length, bool bCDATA)
{
	ASSERT(0);
#if 0
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
#endif
}

void CSourceView::FormatText()
{
	ASSERT(0);
#if 0
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

	if (TRUE)
	{
		CComPtr<ILDOMDocument> document;
		m_viewGroup->m_pDocument->get_DOMDocument(&document);

		FormatNotwellformed(document);
	}
#endif
}

void CSourceView::FormatNotwellformed(Web::Node* parentNode)
{
	ASSERT(0);
#if 0
	CComPtr<Web::Node> node;
	parentNode->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMNotWellformed> notWell = node;
		if (notWell)
		{
			long start;
			long end;
			notWell->getTextOffset(0, &start);
			notWell->getTextOffset(9, &end);

			long styleIndex;
			m_edit->FormatRange(start, end-start, COLOR_XML_INVALID, &styleIndex);
		}
		else
		{
			FormatNotwellformed(node);	// Recurse
		}

		CComPtr<Web::Node> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
}

long GetTextOffsetFromNode(Web::Node* container, long offset)
{
	ASSERT(0);
#if 0
	LDOMNodeType nodeType;
	container->get_nodeType(&nodeType);

	if (nodeType == LNODE_ELEMENT ||
		nodeType == LNODE_DOCUMENT)
	{
		CComPtr<Web::NodeList> childNodes;
		container->get_childNodes(&childNodes);

		CComPtr<Web::Node> child;
		childNodes->item(offset, &child);
		if (child)
		{
			long toffset;
			child->getTextOffset(0, &toffset);

			return toffset;
		}
		else
		{
			long toffset;
			container->getTextOffset(5, &toffset);

			return toffset; 
		}
	}
	else	// Text
	{
	//	container->getTextOffset(2, &endoffset);

		long startoffset;
		container->getTextOffset(3, &startoffset);

		return startoffset + offset;
	}

#if 0
// Try children
	CComPtr<Web::Node> node;
	element->get_firstChild(&node);

	while (node != NULL)
	{
		LDOMNodeType nodeType;
		node->get_nodeType(&nodeType);

		if (nodeType == NODE_ELEMENT)
		{
			CComQIPtr<Web::Element> element2 = node;
		// Try the elements children
			Web::Element* element3 = GetElementFromOffset(element2, offset);
			if (element3) return element3;
		}

		CComPtr<Web::Node> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

// Try us
	long startoffset;
	long endoffset;
	element->getTextOffset(0, &startoffset);
	element->getTextOffset(2, &endoffset);

	if ((startoffset <= offset) && (endoffset >= offset))
	{
		return element;
	}
#endif
#endif
	return 0;
}

void CSourceView::SetRange(Web::Range* range)
{
	ASSERT(0);
#if 0
	CComPtr<Web::Node> startContainer;
	long startOffset;

	CComPtr<Web::Node> endContainer;
	long endOffset;

	range->get_startContainer(&startContainer);
	range->get_startOffset(&startOffset);

	range->get_endContainer(&endContainer);
	range->get_endOffset(&endOffset);

	if (startContainer && endContainer)
	{
		long start = GetTextOffsetFromNode(startContainer, startOffset);
		long end = GetTextOffsetFromNode(endContainer, endOffset);

		m_edit->SetSel(start, end, true/*bNoScroll*/);
	}
#endif
}

void __stdcall CSourceView::OnEditChanged()
{
	FormatText();
}

#include "CSSProperty.h"

void __stdcall CSourceView::OnEditChar(WCHAR nchar)
{
	ASSERT(0);
#if 0
	/*
	if (m_pAutoListMembersWindow->m_hWnd)
	{
		m_pAutoListMembersWindow->DestroyWindow();
	}
	*/

	if (nchar == L'<')
	{
		CComQIPtr<IEXMLDocument> document = m_viewGroup->m_pDocument;
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
	else if (nchar == L'.')
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

void __stdcall CSourceView::OnEditMovedCursor(long offset)
{
	ASSERT(0);
#if 0
	long nLine;
	m_edit->get_line(&nLine);

	long nCol;
	m_edit->get_column(&nCol);

	{
		CString str;
		str.Format("Ln %d, Col %d", nLine+1, nCol+1);
		m_statusBarElement->put_textContent(_bstr_t(str));
	}

	/*
	{
		long startsel, endsel;
		m_edit->GetSel(&startsel, &endsel);

	// Convert edit selection to range boundary points
	}
	*/

	CComQIPtr<IEXMLDocument> document = m_viewGroup->m_pDocument;
	if (document)
	{
		Web::Document* domDocument = document->get_DOMDocument();

		if (domDocument)
		{
			Web::Element* documentElement = domDocument->get_documentElement();

			//CEXMLDocument* pDocument = ((CEXMLDocument*)svgDocument.p);

			m_bSelectingElement++;

			if (documentElement)
			{
				Web::Element* element = GetElementFromOffset(documentElement, offset);
				if (element)
				{
					IEElement* eElement = document->GetEElementFromDOMElement(element);
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

ErrorCode __stdcall CSourceView::OnDoneParsingDOM()
{
//	m_errorListCtl->UpdateList();
	return Success;
}

void __stdcall CSourceView::OnPrefsChange()
{
	ASSERT(0);
#if 0
	CFormatWindow* pWindow = static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->RegisterFormatWindow(L"Source Windows");
	ASSERT(pWindow);

	{
		long tabSize;
		m_viewGroup->m_pDocument->m_app->get_tabSize(&tabSize);

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
		ErrorCode hr = OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&font);
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

		pWindow->GetFormatColorValues(L"XML Invalid", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_INVALID, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script Keyword", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_KEYWORD, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script String", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_STRING, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script Comment", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_COMMENT, fgColor, bgColor);
	}
#endif
}

void DisplayErrorMsg(long err)
{
	ASSERT(0);
#if 0
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
#endif
}

//#include <oledlg.h>
//#pragma comment(lib, "oledlg.lib")

static const GUID ID_INSERTACTIVEX = {0xF64F316F, 0xF37B, 0x4f86, {0x89, 0x38, 0xA2, 0x76, 0xB1, 0x21, 0x6E, 0x46}};

/*
UINT CALLBACK OFNHookProcOldStyle(
  UI::Control* hdlg,      // handle to the dialog box window
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

#if 0
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

	ILHTMLDocument* m_document;
	ILHTMLElement* m_objectElement;

	BOOL Create(CLSID clsid)
	{
		m_document.CoCreateInstance(CLSID_LHTMLDocument);
		m_document->createElement(L"object", (Web::Element**)&m_objectElement);

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
		return Success;
	}
 
	STDMETHOD(Write)(LPCOLESTR pszPropName, VARIANT* pVar)
	{
		CComQIPtr<ILHTMLElement> param;
		m_document->createElement(L"param", (Web::Element**)&param);

		VARIANT	dvar;
		VariantInit(&dvar);
		ErrorCode hr = VariantChangeType(pVar, &dvar, 0, VT_BSTR);
		if (FAILED(hr))
		{
			return E_FAIL;
		}

		param->setAttribute(L"name", _bstr_t(pszPropName));

		if (dvar.vt == VT_BSTR)
			param->setAttribute(L"value", dvar.bstrVal);
		else
			param->setAttribute(L"value", L"");

		CComPtr<Web::Node> result;
		m_objectElement->appendChild(param, &result);

		return Success;
	}
 
// IErrorLog
	STDMETHOD(AddError)(
	  LPCOLESTR pszPropName,  //Pointer to the name of the property 
                          // involved with the error
	LPEXCEPINFO pException  //Pointer to the caller-initialized 
                          // EXCEPINFO structure describing the error
	)
	{
		return Success;
	}
};

class CCOMObject : public CComObject<CCOMObjectBase>
{
};
#endif

BEGIN_CMD_MAP(CSourceView)
#if 0
// File
	CMD_HANDLER(ID_FILE_PRINT, OnFilePrint)
	CMD_HANDLER(ID_FILE_PAGE_SETUP, OnFilePageSetup)

// Edit
	CMD_HANDLER(ID_EDIT_ADVANCED_MAKESELECTIONUPPERCASE, OnMakeSelectionUppercase)
	CMD_HANDLER(ID_EDIT_ADVANCED_MAKESELECTIONLOWERCASE, OnMakeSelectionLowercase)

// View
	CMD_HANDLER(ID_VIEW_WORDWRAP, OnViewWordWrap)
	CMD_UPDATEUI(ID_VIEW_WORDWRAP, OnViewWordWrapUpdate)
	CMD_HANDLER(ID_VIEW_LINENUMBERS, OnViewLineNumbers)
	CMD_UPDATEUI(ID_VIEW_LINENUMBERS, OnViewLineNumbersUpdate)
	CMD_HANDLER(ID_VIEW_VIEWWHITESPACE, OnViewWhitespace)
	CMD_UPDATEUI(ID_VIEW_VIEWWHITESPACE, OnViewWhitespaceUpdate)
#endif
END_CMD_MAP()

long CSourceView::OnFilePrint(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	PRINTDLG	pd = {0};
	pd.lStructSize = sizeof(pd);
	ASSERT(0);
	pd.hwndOwner = NULL;//GetMainHwnd();
	pd.Flags = PD_RETURNDC;

	if (PrintDlg(&pd))
	{
		DeleteDC(pd.hDC);
	}
#endif

	return 0;
}

long CSourceView::OnFilePageSetup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	PAGESETUPDLG psd = {0};
	psd.lStructSize = sizeof(psd);
	psd.hInstance = NULL;//_Module.m_hInst;
	ASSERT(0);
	psd.hwndOwner = NULL;//GetMainHwnd();

	PageSetupDlg(&psd);
#endif

	return 0;
}

long CSourceView::OnMakeSelectionUppercase(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	long startsel, endsel;
	m_edit->GetSel(&startsel, &endsel);
	if (startsel == endsel)
	{
		m_edit->SetSel(startsel, endsel+1, true);
	}

	CComBSTR data;
	m_edit->GetSelText(&data);

	data.ToUpper();

	m_edit->ReplaceSelText(data, data.Length());
#endif
	return 0;
}

long CSourceView::OnMakeSelectionLowercase(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	long startsel, endsel;
	m_edit->GetSel(&startsel, &endsel);
	if (startsel == endsel)
	{
		m_edit->SetSel(startsel, endsel+1, true);
	}

	CComBSTR data;
	m_edit->GetSelText(&data);

	data.ToLower();

	m_edit->ReplaceSelText(data, data.Length());
#endif
	return 0;
}

long CSourceView::OnViewWordWrap(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	VARIANT_bool wordWrap;
	m_edit->get_wordWrap(&wordWrap);
	m_edit->put_wordWrap(wordWrap? false: true);
#endif
	return 0;
}

void CSourceView::OnViewWordWrapUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	VARIANT_bool wordWrap;
	m_edit->get_wordWrap(&wordWrap);
	pCmdUI->SetCheck(wordWrap? TRUE: FALSE);
#endif
}

long CSourceView::OnViewLineNumbers(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	VARIANT_bool lineNumbers;
	m_edit->get_lineNumbers(&lineNumbers);
	m_edit->put_lineNumbers(lineNumbers? false: true);
#endif
	return 0;
}

void CSourceView::OnViewLineNumbersUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	VARIANT_bool lineNumbers;
	m_edit->get_lineNumbers(&lineNumbers);
	pCmdUI->SetCheck(lineNumbers? TRUE: FALSE);
#endif
}

long CSourceView::OnViewWhitespace(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	m_viewWhitespace = (m_viewWhitespace)? false: true;
	if (m_viewWhitespace)
	{
		m_edit->set_viewTabs(true);
		m_edit->set_viewSpaces(true);
		m_edit->set_viewEOLs(true);
	}
	else
	{
		m_edit->set_viewTabs(false);
		m_edit->set_viewSpaces(false);
		m_edit->set_viewEOLs(false);
	}

	return 0;
}

void CSourceView::OnViewWhitespaceUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_viewWhitespace? true: false);
}

#if 0
// ICommandTarget
ErrorCode CSourceView::OnCmdMsg(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled)
{
// try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return Success;

	CComQIPtr<ICommandTarget> target;

// Try edit control
	target = m_edit;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return Success;
	}

// Try viewgroup
	target = m_viewGroup;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return Success;
	}

	return Success;
}
#endif

#if 0
ErrorCode CSourceView::OnCmdMsg(GUID * iid, UI::IUICmdUpdate * pCmdUI, bool * bHandled)
{
	if (bHandled == NULL) return E_POINTER;
		
	*bHandled = TRUE;

	if (!pCmdUI)
	{
		if  (*iid == ID_INSERTACTIVEX)
		{
			CComQIPtr<IWebEditorFrame> frame;
			gApp->get_frame(&frame);

			TCHAR filename[_MAX_PATH] = {0};

			OLEUIINSERTOBJECT oleio = {0};
			oleio.cbStruct = sizeof(OLEUIINSERTOBJECT);
			oleio.dwFlags = IOF_SELECTCREATECONTROL | IOF_SHOWINSERTCONTROL;
			frame->get_hwnd(&oleio.hWndOwner);
			oleio.lpszFile = filename;
			oleio.cchFile = _MAX_PATH;
			ASSERT(IsWindow(oleio.hWndOwner));

			ErrorCode hr = OleUIInsertObject(&oleio);
			if (hr == OLEUI_OK)
			{
				CCOMObject* obj = new CCOMObject;
				obj->AddRef();

				if (obj->Create(oleio.clsid))
				{
					BSTR text;
					obj->m_objectElement->get_outerHTML(&text);

					MessageBox(NULL, _bstr_t(text), "", MB_OK);
					SysFreeString(text);
				}

				obj->Release();

			/*
				MessageBox(NULL, str, "", MB_OK);
				//GetDoc()->InsertHTMLText(0, str);

				//UpdateAllViews();
			*/
			}
		}
		else
			*bHandled = FALSE;
	}
	else
	{
	}

	return Success;
}
#endif

/*
OLEUI_ERR_STANDARDMIN 
Errors common to all dialog boxes lie in the range OLEUI_ERR_STANDARDMIN to OLEUI_ERR_STANDARDMAX. This value allows the application to test for standard messages in order to display error messages to the user. 
OLEUI_ERR_STRUCTURENULL 
The pointer to an OLEUIXXX structure passed into the function was NULL. 
OLEUI_ERR_STRUCTUREINVALID 
Insufficient permissions for read or write access to an OLEUIXXX structure. 
OLEUI_ERR_CBSTRUCTINCORRECT 
The cbstruct value is incorrect. 
OLEUI_ERR_HWNDOWNERINVALID 
The hWndOwner value is invalid. 
OLEUI_ERR_LPSZCAPTIONINVALID 
The lpszCaption value is invalid. 
OLEUI_ERR_LPFNHOOKINVALID 
The lpfnHook value is invalid. 
OLEUI_ERR_HINSTANCEINVALID 
The hInstance value is invalid. 
OLEUI_ERR_LPSZTEMPLATEINVALID 
The lpszTemplate value is invalid. 
OLEUI_ERR_HRESOURCEINVALID 
The hResource value is invalid. 
Initialization Errors 

OLEUI_ERR_FINDTEMPLATEFAILURE 
Unable to find the dialog box template. 
OLEUI_ERR_LOADTEMPLATEFAILURE 
Unable to load the dialog box template. 
OLEUI_ERR_DIALOGFAILURE 
Dialog box initialization failed. 
OLEUI_ERR_LOCALMEMALLOC 
A call to LocalAlloc or the standard IMalloc allocator failed. 
OLEUI_ERR_GLOBALMEMALLOC 
A call to GlobalAlloc or the standard IMalloc allocator failed. 
OLEUI_ERR_LOADSTRING 
Unable to LoadString localized resources from the library. 
OLEUI_ERR_OLEMEMALLOC 
A call to the standard IMalloc allocator failed. 
Function Specific Errors 

OLEUI_ERR_STANDARDMAX 
Errors common to all dialog boxes lie in the range OLEUI_ERR_STANDARDMIN to OLEUI_ERR_STANDARDMAX. This value allows the application to test for standard messages in order to display error messages to the user. 
OLEUI_IOERR_LPSZFILEINVALID 
The lpszFile value is invalid or user has insufficient write access permissions.. This lpszFile member points to the name of the file linked to or inserted. 
OLEUI_IOERR_LPFORMATETCINVALID 
The lpFormatEtc value is invalid. This member identifies the desired format. 
OLEUI_IOERR_PPVOBJINVALID 
The ppvOjb value is invalid. This member points to the location where the pointer for the object is returned. 
OLEUI_IOERR_LPIOLECLIENTSITEINVALID 
The lpIOleClientSite value is invalid. This member points to the client site for the object. 
OLEUI_IOERR_LPISTORAGEINVALID 
The lpIStorage value is invalid. This member points to the storage to be used for the object. 
OLEUI_IOERR_SCODEHASERROR 
The sc member of lpIO has additional error information. 
OLEUI_IOERR_LPCLSIDEXCLUDEINVALID 
The lpClsidExclude value is invalid. This member contains the list of CLSIDs to exclude. 
OLEUI_IOERR_CCHFILEINVALID 
*/

}	// LXmlEdit
}
