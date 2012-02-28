// CSSSourceView.cpp : Implementation of CCSSSourceView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "CSSSourceView.h"

#include "ECSSViewGroup.h"	// TODO remove
#include "ECSSDocument.h"
#include "LXMLEditorApp.h"

#if 0

#include <string>

static long COLOR_CSS_COMMENT;
static long COLOR_CSS_RULE;
static long COLOR_CSS_PROPERTY_NAME;
static long COLOR_CSS_PROPERTY_VALUE;

#if 0
ILDOMNode* GetNodeFromOffsets(ILDOMNode* node, long startoffset, long endoffset, long index0, long index1)
{
// Try children
	CComPtr<ILDOMNode> child;
	node->get_firstChild(&child);

	while (child != NULL)
	{
		//LDOMNodeType nodeType;
		//node->get_nodeType(&nodeType);

		//if (nodeType == NODE_ELEMENT)
		{
		//	CComQIPtr<ILDOMElement> element2 = node;
		// Try the elements children
			ILDOMNode* f = GetNodeFromOffsets(child, startoffset, endoffset, index0, index1);
			if (f) return f;
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

// Try us

	CComPtr<ILDOMNamedNodeMap> attributes;
	node->get_attributes(&attributes);

	if (attributes)
	{
		long length;
		attributes->get_length(&length);

		for (int i = 0; i < length; i++)
		{
			CComPtr<ILDOMNode> attr;
			attributes->item(i, &attr);

			ILDOMNode* f = GetNodeFromOffsets(attr, startoffset, endoffset, index0, index1);
			if (f)
				return f;
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

	return NULL;
}
#endif

ILCSSRule* GetRuleFromOffset(ILCSSRuleList* rules, long offset)
{
	long nrules;
	rules->get_length(&nrules);

	for (int i = 0; i < nrules; i++)
	{
		CComPtr<ILCSSRule> rule;
		rules->item(i, &rule);

		long offset0;
		rule->getTextOffset(0, &offset0);

		long offset5;
		rule->getTextOffset(5, &offset5);

		if (offset >= offset0 && offset < offset5)
		{
			LCSSType cssType;
			rule->get_type(&cssType);

			if (cssType == MEDIA_RULE)
			{
				CComQIPtr<ILCSSMediaRule> mediaRule = rule;

				CComPtr<ILCSSRuleList> rules;
				mediaRule->get_cssRules(&rules);

				ILCSSRule* rule2 = GetRuleFromOffset(rules, offset);
				if (rule2)
					return rule2;
			}

			return rule;
		}
	}

#if 0
// Try children
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);

	while (node != NULL)
	{
		LDOMNodeType nodeType;
		node->get_nodeType(&nodeType);

		if (nodeType == NODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element2 = node;
		// Try the elements children
			ILDOMElement* element3 = GetElementFromOffset(element2, offset);
			if (element3) return element3;
		}

		CComPtr<ILDOMNode> nextSibling;
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
// CCSSSourceView

int CCSSSourceView::FinalConstruct()
{
	HRESULT hr;

	hr = m_errorListCtl.CoCreateInstance(CLSID_ErrorListCtl);
	if (FAILED(hr)) return hr;

#if 0
	hr = m_edit.CoCreateInstance(CLSID_UIEdit);
	if (FAILED(hr)) return hr;
#endif

	return S_OK;
}

void CCSSSourceView::FinalRelease()
{
}

STDMETHODIMP CCSSSourceView::OnDragOut(IUIDockBar* dockBar)
{
	return S_OK;
}

STDMETHODIMP CCSSSourceView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
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

#if 0
LRESULT CCSSSourceView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

long CCSSSourceView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

long CCSSSourceView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

long CCSSSourceView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}

	return 0;
}

long CCSSSourceView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CCSSSourceView::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
#endif

// ILElementBehavior
STDMETHODIMP CCSSSourceView::Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
{
	m_behaviorSite = pBehaviorSite;

	CComPtr<ILDOMElement> element;
	m_behaviorSite->GetElement(&element);

	CComPtr<ILDOMDocument> document;
	element->get_ownerDocument(&document);

	document->createElementNS(L"http://www.w3.org/1999/xhtml", L"object", (ILDOMElement**)&m_editObjectElement);
	m_editObjectElement->setAttribute(L"classid", L"clsid:{94327EC1-8D79-4A8E-B9B7-ACCCE8C787EF}");
	m_editObjectElement->setAttribute(L"style", L"-moz-box-flex: 1;");

	document->createElementNS(L"http://www.lerstad.com/2004/lxui", L"p", (ILDOMElement**)&m_statusBarElement);
	m_statusBarElement->put_TextContent(L"");

	element->appendChild(m_editObjectElement, NULL);
	element->appendChild(m_statusBarElement, NULL);

	CComPtr<IUnknown> unk;
	m_editObjectElement->get__object(&unk);

	m_edit = CComQIPtr<IUIEdit>(unk);
	if (m_edit == NULL) return E_FAIL;

	OnCreate();

	return S_OK;
}

STDMETHODIMP CCSSSourceView::Detach()
{
	m_behaviorSite.Release();
	return S_OK;
}

LRESULT CCSSSourceView::OnCreate()
{
	CComPtr<IEDocument> edocument;
	m_viewGroup->get_eDocument(&edocument);
	CComQIPtr<IECSSDocument> eCSSDocument = edocument;

	CComQIPtr<IEDocument> eDocument = eCSSDocument;

	CComPtr<ITextData> textDocument;
	eCSSDocument->get_textData(&textDocument);

//	m_document->get_textDocument(&textDocument);

	IUndoManager* undoManager;
	eDocument->get_undoManager(&undoManager);

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
#if 0
	m_axedit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axedit.AttachControl(m_edit, &p);
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

		/*
		m_edit->NewStyle(&COLOR_XML_PREPROCESSING_INSTRUCTION);
		m_edit->NewStyle(&COLOR_XML_ELEMENT_NAME);
		m_edit->NewStyle(&COLOR_XML_ATTRIBUTE_NAME);
		m_edit->NewStyle(&COLOR_XML_ATTRIBUTE_VALUE);
		m_edit->NewStyle(&COLOR_XML_TAG_DELIMITER);
		*/
		m_edit->NewStyle(&COLOR_CSS_RULE);
		m_edit->NewStyle(&COLOR_CSS_PROPERTY_NAME);
		m_edit->NewStyle(&COLOR_CSS_PROPERTY_VALUE);
		m_edit->NewStyle(&COLOR_CSS_COMMENT);
		/*
		m_edit->NewStyle(&COLOR_XML_OPERATOR);
		m_edit->NewStyle(&COLOR_JSCRIPT_KEYWORD);
		m_edit->NewStyle(&COLOR_JSCRIPT_STRING);
		m_edit->NewStyle(&COLOR_JSCRIPT_COMMENT);
		*/
	}

	OnPrefsChange();	// Initialize edit control

	FormatText();

	HRESULT hr;

	hr = IDispEventImpl<1, CCSSSourceView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_edit);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<2, CCSSSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>::DispEventAdvise(m_errorListCtl);
	ASSERT(SUCCEEDED(hr));

//	hr = IDispEventImpl<3, CCSSSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);
//	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<4, CCSSSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->m_pDocument->m_app);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<5, CCSSSourceView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());
	ASSERT(SUCCEEDED(hr));
#if 0
	CComQIPtr<IErrorList> errorList = m_document;

	m_errorListCtl->put_errorList(errorList);
	m_errorListCtl->UpdateList();
#endif

	OnViewGroupSelectionChanged();

	return 0;
}

LRESULT CCSSSourceView::OnDestroy()
{
	HRESULT hr;

	hr = IDispEventImpl<5, CCSSSourceView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<1, CCSSSourceView, &DIID__IUIEditEvents	, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_edit);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<2, CCSSSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>::DispEventUnadvise(m_errorListCtl);
	ASSERT(SUCCEEDED(hr));

//	hr = IDispEventImpl<3, CCSSSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
//	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<4, CCSSSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->m_pDocument->m_app);
	ASSERT(SUCCEEDED(hr));

	return 0;
}

#if 0
LRESULT CCSSSourceView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

void CCSSSourceView::OnSize()
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

	m_axedit.MoveWindow(0, editTop, client.right, client.bottom-editTop, TRUE);
}
#endif

STDMETHODIMP CCSSSourceView::get_document(IEDocument **pVal)
{
	return m_viewGroup->get_eDocument(pVal);
}

void __stdcall CCSSSourceView::OnGotoError(IErrorItem* errorItem)
{
	long offset;
	errorItem->GetOffset(&offset);

	m_edit->setCursorPosOffset(offset);
}

void CCSSSourceView::FormatCSSBlock(BSTR data, int& pos, unsigned long length, bool bCDATA)
{
	long styleIndex = 0;

	if (!bCDATA)
	{
		if (FALSE)	// TODO, take a parameter for this
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

				m_edit->FormatRange(start, pos-start, COLOR_CSS_COMMENT, &styleIndex);
			}
		}
	}

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
			if (FALSE)	// TODO, take a parameter for this
			{
				if (data[pos] == L'<')	// Start of new element
				{
					break;
				}
			}
		}

		if (data[pos] == L'/')
		{
			int start = pos++;

			if (pos < length && data[pos] == L'*')	// Multi-line comment
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

				m_edit->FormatRange(start, pos-start, COLOR_CSS_COMMENT, &styleIndex);
			}
		}
		else if (data[pos] == L'@')
		{
			int start = pos++;
			while (pos < length && iswalnum(data[pos]))
			{
				pos++;
			}
			m_edit->FormatRange(start, pos-start, COLOR_CSS_RULE, &styleIndex);
		}
		else if (iswalnum(data[pos]) || data[pos] == L'*' || data[pos] == L'.' || data[pos] == L'#')
		{
			int start = pos;
			while (pos < length && data[pos] != '{')
			{
				pos++;
			}
		//	m_edit->FormatRange(start, pos-start, COLOR_CSS_PROPERTY_NAME, &styleIndex);
			m_edit->FormatRange(start, pos-start, COLOR_CSS_RULE, &styleIndex);
		}
		else if (data[pos] == L'{')
		{
			pos++;

			// Skip spaces
			while (pos < length && iswspace(data[pos]))
			{
				pos++;
			}

			int curly = 1;

			int start = pos;
			int type = COLOR_CSS_PROPERTY_NAME;

			while (pos < length)
			{
				if (data[pos] == L'{')
				{
					curly++;
					pos++;
				}
				else if (data[pos] == L'}')
				{
					curly--;
					if (curly == 0)
					{
						if (type)
						{
							m_edit->FormatRange(start, pos-start, type, &styleIndex);
						}
						pos++;
						break;
					}
				}
				else
				{
					/*
					int start = pos;
					while (data[pos] != ':')
					{
						pos++;
					}
					*/

					if (data[pos] == ':')
					{
						m_edit->FormatRange(start, pos-start, type, &styleIndex);

						// Start on property value
						start = ++pos;
						type = COLOR_CSS_PROPERTY_VALUE;
					}
					else if (data[pos] == L';')
					{
						m_edit->FormatRange(start, pos-start, type, &styleIndex);

						// Start on property name
						start = ++pos;
						type = COLOR_CSS_PROPERTY_NAME;
					}
					else
						pos++;
				}
			}
		}
		else
		{
			pos++;
		}
	}
}

void CCSSSourceView::FormatText()
{
	m_edit->ClearFormatting();

	CComQIPtr<ITextData> textDoc;
	m_edit->get_textDocument((IDispatch**)&textDoc);

	BSTR data;
	textDoc->get_data(&data);

	long length;
	textDoc->get_len(&length);

	int pos = 0;
	FormatCSSBlock(data, pos, length, false/*bCDATA*/);
}

void CCSSSourceView::SetRange(ILDOMRange* range)
{
#if 0
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
#endif
}

void __stdcall CCSSSourceView::OnEditChanged()
{
	FormatText();
}

#include "CSSProperty.h"

void __stdcall CCSSSourceView::OnEditChar(WCHAR nchar)
{
	/*
	if (m_pAutoListMembersWindow->m_hWnd)
	{
		m_pAutoListMembersWindow->DestroyWindow();
	}
	*/

	if (nchar == L'@')
	{
		CComPtr<IUIAutoListWindow> autolist;
		m_edit->AutoList(&autolist);

		autolist->AddString(-1, L"charset", NULL);
		autolist->AddString(-1, L"color-profile", NULL);
		autolist->AddString(-1, L"import", NULL);
		autolist->AddString(-1, L"media", NULL);

		m_edit->AutoListPopup();
	}
	else if (nchar == L';')
	{
		CComPtr<IUIAutoListWindow> autolist;
		m_edit->AutoList(&autolist);

		for (int i = 0; i < g_nCSSProperties; i++)
		{
			autolist->AddString(-1, CSSProperties[i].m_name, NULL);
		}

		m_edit->AutoListPopup();
	}
	else if (nchar == L':')
	{
		long offset;
		m_edit->getCursorPosOffset(&offset);

		BSTR data;
		m_viewGroup->m_pDocument->m_textData->get_data(&data);

		int i = offset-1;
		if (data[i] == L':')
		{
			i--;
			while (i >= 0 && iswspace(data[i])) i--;

			std::wstring propertyName = L"";

			while (i >= 0)
			{
				if (iswalnum(data[i]) || data[i] == L'-')
				{
					propertyName = data[i] + propertyName;
				}
				else
					break;

				i--;
			}

			int propertyIndex = GetCSSPropertyIndex(propertyName.data());
			if (propertyIndex >= 0)
			{
				CSSProperty* pProperty = &CSSProperties[propertyIndex];

				if (pProperty->d.m_type == CSSType_Enum)
				{
					CComPtr<IUIAutoListWindow> autolist;
					m_edit->AutoList(&autolist);

					WCHAR* p = (BSTR)pProperty->d.m_enums;

					while (*p)
					{
						WCHAR v[512];
						int n = 0;

						while (*p && *p != L'|')
						{
							v[n] = *p;
							n++;
							p++;
						}

						v[n] = 0;	// null-terminate

					//	pProperty->m_enumStrings.Add(v);
						autolist->AddString(-1, v, NULL);

						if (*p)	// Skip |
							p++;
					}

					m_edit->AutoListPopup();
				}
			}
		}
	}
}

void __stdcall CCSSSourceView::OnEditMovedCursor(long offset)
{
	CComPtr<ILCSSRuleList> rules;
	m_viewGroup->m_pDocument->m_styleSheet->get_cssRules(&rules);

	ILCSSRule* rule = GetRuleFromOffset(rules, offset);

	m_bSelectingElement++;

	if (rule)
	{
		m_viewGroup->ActivateElement(rule, 0, NULL);
	}
	else
	{
		m_viewGroup->ActivateElement(NULL, 0, NULL);	// Deselect All
	}

	m_bSelectingElement--;

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
		}
	}
#endif
}

void __stdcall CCSSSourceView::OnViewGroupSelectionChanged()
{
	if (!m_bSelectingElement)
	{
		if (m_viewGroup->m_pActiveElement)
		{
			CComPtr<ILCSSRule> rule;
			m_viewGroup->m_pActiveElement->get_rule(&rule);

			long start;
			long end;
			rule->getTextOffset(0, &start);
			rule->getTextOffset(5, &end);
		
			m_edit->SetSel(start, end, VARIANT_TRUE/*bNoScroll*/);
		}
	}
}

void __stdcall CCSSSourceView::OnDoneParsingDOM()
{
	m_errorListCtl->UpdateList();
}

void __stdcall CCSSSourceView::OnPrefsChange()
{
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
		HRESULT hr = OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&font);
		m_edit->put_font(font);
	}

	{
		COLORREF fgColor, bgColor;

		pWindow->GetFormatColorValues(L"Text Selection", &fgColor, &bgColor);
		m_edit->SetStyle(-1, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Text", &fgColor, &bgColor);
		m_edit->SetStyle(0, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"CSS Comment", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_CSS_COMMENT, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"CSS Rule", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_CSS_RULE, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"CSS Property Name", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_CSS_PROPERTY_NAME, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"CSS Property Value", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_CSS_PROPERTY_VALUE, fgColor, bgColor);
	}
}

BEGIN_CMD_MAP(CCSSSourceView)
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

LRESULT CCSSSourceView::OnFilePrint(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

LRESULT CCSSSourceView::OnFilePageSetup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	PAGESETUPDLG psd = {0};
	psd.lStructSize = sizeof(psd);
	psd.hInstance = NULL;//_Module.m_hInst;
	ASSERT(0);
	psd.hwndOwner = NULL;//GetMainHwnd();

	PageSetupDlg(&psd);

	return 0;
}

LRESULT CCSSSourceView::OnMakeSelectionUppercase(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

LRESULT CCSSSourceView::OnMakeSelectionLowercase(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

LRESULT CCSSSourceView::OnViewWordWrap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL wordWrap;
	m_edit->get_wordWrap(&wordWrap);
	m_edit->put_wordWrap(wordWrap? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CCSSSourceView::OnViewWordWrapUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL wordWrap;
	m_edit->get_wordWrap(&wordWrap);
	pCmdUI->SetCheck(wordWrap? TRUE: FALSE);
}

LRESULT CCSSSourceView::OnViewLineNumbers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL lineNumbers;
	m_edit->get_lineNumbers(&lineNumbers);
	m_edit->put_lineNumbers(lineNumbers? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CCSSSourceView::OnViewLineNumbersUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL lineNumbers;
	m_edit->get_lineNumbers(&lineNumbers);
	pCmdUI->SetCheck(lineNumbers? TRUE: FALSE);
}

LRESULT CCSSSourceView::OnViewWhitespace(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

void CCSSSourceView::OnViewWhitespaceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_viewWhitespace? TRUE: FALSE);
}

#if 0
// ICommandTarget
STDMETHODIMP CCSSSourceView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	CComQIPtr<ICommandTarget> target;
	
// Try viewgroup first
	target = m_viewGroup;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

// Try edit control
	target = m_edit;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

// Then try us
	return ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
}

#endif

#endif