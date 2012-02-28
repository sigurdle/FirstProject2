// SVGFiltersDlg.cpp : Implementation of CSVGFiltersDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGFiltersDlg.h"

#include "EXMLDocument.h"	// TODO, remove
#include "EXMLViewGroup.h"	// TODO, remove

#include "WEUndoNewElement.h"
#include "UndoParent.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CSVGFiltersDlg

int CSVGFiltersDlg::FinalConstruct()
{
	return 0;
}

LRESULT CSVGFiltersDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (CSVGDefinitionsDlgT<CSVGFiltersDlg>::OnCreate(uMsg, wParam, lParam, bHandled) != 0)
		return -1;

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);

	::RegisterDragDrop(m_hWnd, this);

	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		m_listView.m_xmlDocument.Release();
		edocument->get_DOMDocument(&m_listView.m_xmlDocument);

		IDispEventImpl<1, CSVGFiltersDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());
	//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(edocument);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();

		OnSelectionStyleChanged();
	}

	return 0;
}

LRESULT CSVGFiltersDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::RevokeDragDrop(m_hWnd);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

	{
		IDispEventImpl<1, CSVGFiltersDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
		RemoveEventListeners();

		m_listView.RemoveItems();

		m_listView.m_xmlDocument.Release();
	}

	CSVGDefinitionsDlgT<CSVGFiltersDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);

	return 0;
}

LRESULT CSVGFiltersDlg::OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup)
	{
		if (m_listView.m_selectedItemIndex >= 0 && m_listView.m_selectedItemIndex < m_listView.m_items.GetSize())
		{
			_bstr_t filter;

			if (m_listView.m_items[m_listView.m_selectedItemIndex]->m_element)
			{
				CComBSTR id;
				((ILDOMElement*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element)->getAttribute(L"id", &id);

				filter = L"url(#" + _bstr_t(id) + L")";
			}
			else
			{
				filter = L"none";
			}

			CComPtr<ILCSSStyleDeclaration> style;
			CComQIPtr<IECSSSelection>(m_viewGroup)->GetCurrentSelectionCSSStyle(&style);

			style->setProperty(L"filter", filter, NULL);

			CComQIPtr<IECSSSelection>(m_viewGroup)->ApplyCurrentSelectionCSSStyle();
		}
		else
		{
#if 0
			CComBSTR oldval;
			((CEXMLDocument*)m_document.p)->m_defaultStyle->removeProperty(L"filter", &oldval);
#endif
		}
	}

	return 0;
}

LRESULT CSVGFiltersDlg::OnDblClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_listView.m_selectedItemIndex >= 0)
	{
		if (m_viewGroup)
		{
			CComPtr<IEXMLDocument> edocument;
			m_viewGroup->get_eXMLDocument(&edocument);

			CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroup);

			if (m_listView.m_items[m_listView.m_selectedItemIndex]->m_element)
			{
				CComPtr<IEElement> eElement;
				edocument->GetEElementFromDOMElement((ILDOMElement*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element, &eElement);

				pViewGroup->m_activeReferencedElement = eElement;	// ??? reference element is still NULL
				m_viewGroup->ActivateElement(eElement, 0, NULL);

				ATLASSERT(0);
#if 0
				{
					CComPtr<IUIDlgSite> dlgsite;
					m_viewGroup->m_views[15]->GetDlgSite(&dlgsite);
					dlgsite->Show(TRUE);

					// Activate the dialogs frame
					HWND hwnd;
					m_viewGroup->m_views[15]->get_hwnd(&hwnd);
					while (hwnd)
					{
						if (!(::GetWindowLong(hwnd, GWL_STYLE) & WS_CHILD))
							break;
						hwnd = ::GetParent(hwnd);
					}

					::SetActiveWindow(hwnd);
				}
#endif
			}
		}
	}

	return 0;
}

void __stdcall CSVGFiltersDlg::OnSelectionStyleChanged()
{
	ATLASSERT(m_viewGroup);

	m_listView.DeselectAll();

	CComPtr<ILCSSStyleDeclaration> style;
	CComQIPtr<IECSSSelection>(m_viewGroup)->GetCurrentSelectionCSSStyle(&style);

	CComPtr<ILCSSPrimitiveValue> cssvalue;
	style->getPropertyCSSValue(L"filter", (ILCSSValue**)&cssvalue);
	if (cssvalue)
	{
		CComBSTR cssText;
		cssvalue->get_cssText(&cssText);

		if (!wcscmp(cssText, L"none"))
		{
			m_listView.SelectItem(0);
		}
		else if (!wcscmp(cssText, L"inherit"))
		{
		}
		else
		{
			LCSSUnitType primitiveType;
			cssvalue->get_primitiveType(&primitiveType);

			if (primitiveType == CSS_URI)
			{
				CComBSTR uri;
				cssvalue->getStringValue(&uri);

				if (((BSTR)uri)[0] == L'#')
				{
					BSTR luri = &((BSTR)uri)[1];

					for (int i = 0; i < m_listView.m_items.GetSize(); i++)
					{
						if (!wcscmp(m_listView.m_items[i]->m_name, luri))
						{
							m_listView.SelectItem(i);
						}
					}
				}
			}
		}
	}
}

// IDropTarget
STDMETHODIMP CSVGFiltersDlg::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	if (m_viewGroup)
	{
		*pdwEffect = DROPEFFECT_COPY;
	}

	return S_OK;
}

STDMETHODIMP CSVGFiltersDlg::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CSVGFiltersDlg::DragLeave()
{
	return S_OK;
}

// TODO .. global function ??
HRESULT AddSVGElements(IEXMLDocument* m_document, HGLOBAL hData)
{
	ATLASSERT(0);
#if 0
	CComPtr<ILDOMDocument> m_xmlDocument;
	m_document->get_DOMDocument(&m_xmlDocument);

	WCHAR* text = (WCHAR*)GlobalLock(hData);
	if (text)
	{
		int len = GlobalSize(hData);

		LSVG::SVGDocument* svgdocument;

		//svgdocument.CoCreateInstance(CLSID_LSVGDocument);

		svgdocument->loadXML(_bstr_t(text));

		if (bsuccess)
		{
			IEDocument* eDocument = m_document;

			CComPtr<IOleUndoManager> undoManager;
			eDocument->get_undoManager(&undoManager);

			CComObject<CUndoParent>* pParentUndo;
			CComObject<CUndoParent>::CreateInstance(&pParentUndo);
			if (pParentUndo)
			{
				pParentUndo->AddRef();	// ???
				undoManager->Open(pParentUndo);

				LSVG::SVGElement* svgDefsElement;
				m_document->FindOrCreateSVGDefs(&svgDefsElement);

				if (svgDefsElement)
				{
					CComPtr<ILDOMElement> documentElement;
					svgdocument->get_documentElement(&documentElement);

					CComPtr<ILDOMNode> node;
					documentElement->get_firstChild(&node);
					while (node)
					{
						CComPtr<ILDOMNode> nextSibling;
						node->get_nextSibling(&nextSibling);

						CComQIPtr<ILSVGElement> svgFilterElement = node;
						if (svgFilterElement)
						{
							CComBSTR id;
							svgFilterElement->getAttribute(L"id", &id);

							CComPtr<ILDOMElement> existingElement;
							m_xmlDocument->getElementById(id, &existingElement);
							if (existingElement == NULL)
							{
								m_xmlDocument->adoptNode(svgFilterElement, NULL);

								CComObject<CWEUndoNewElement>* pUndo;
								CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
								if (pUndo)
								{
								//	pUndo->AddRef();
									pUndo->m_pDocument = static_cast<CEXMLDocument*>(m_document);

									pUndo->DoInitial(undoManager, svgFilterElement, svgDefsElement, NULL);
								}
							}
						}

						node = nextSibling;
					}
				}

				undoManager->Close(pParentUndo, TRUE/*commit*/);
			}
		}

		GlobalUnlock(hData);
	}
#endif
	return S_OK;
}

STDMETHODIMP CSVGFiltersDlg::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	ATLASSERT(0);
#if 0
	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	ScreenToClient(&point);

	COleDataObjectWrapper dataObject;
	dataObject.Attach(pDataObject);

	HGLOBAL hData;

#if 0
	if (hData = dataObject.GetGlobalData(CF_HDROP))
	{
		DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
		if (dp)
		{
			char* p = (char*)(dp+1);

			int i = 0;
			TCHAR filename[512];
			while (*p)
			{
				filename[i++] = *p++;
			}
			filename[i] = 0;

			CHTMDesignFrame* pFrame = NULL;
			m_pFrameSet->OnButtonDown(0, point, 0, FALSE, &pFrame);
			if (pFrame)
			{
				pFrame->m_pElement->setAttribute(L"src", _bstr_t(filename));
				//m_pDocument->CreateHTMLTree();
				//m_pDocument->UpdateAllViews(NULL);
			}
		}

		GlobalUnlock(hData);

		{
			BuildFrames();

			OnSize();
			InvalidateRect(NULL, TRUE);
		}

		*pdwEffect = DROPEFFECT_COPY;
	}
	else
#endif
	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		if (hData = dataObject.GetGlobalData(CF_UNICODETEXT))
		{
			AddSVGElements(edocument, hData);

			//return TRUE;
		}
	}
#endif

	return S_OK;
}

#if 0
// IUIEventHandler
STDMETHODIMP CSVGFiltersDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		ATLASSERT(m_viewGroup == NULL);
		/*
		if (m_document != NULL)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
			eventTarget->removeEventListener(L"DOMNodeInserted", this, VARIANT_TRUE);

			IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}
		*/

		m_viewGroup = viewGroup;

		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		m_listView.m_xmlDocument.Release();
		edocument->get_DOMDocument(&m_listView.m_xmlDocument);

		IDispEventImpl<1, CSVGFiltersDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);
	//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(edocument);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();

		OnSelectionStyleChanged();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSVGFiltersDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(IsUnknownEqualUnknown(m_viewGroup, object));

	IDispEventImpl<1, CSVGFiltersDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

	CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
	eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
	RemoveEventListeners();

	m_listView.RemoveItems();

	m_listView.m_xmlDocument.Release();
	m_viewGroup.Release();

	return S_OK;
}
#endif

// ILDOMEventListener
STDMETHODIMP CSVGFiltersDlg::handleEvent(ILDOMEvent* evt)
{
	CComBSTR type;
	evt->get_type(&type);

//	BOOL bUpdate = FALSE;

	if (!wcscmp(type, L"DOMNodeInserted"))
	{
		RemoveEventListeners();

		BuildItems();

		AddEventListeners();
	}
	else if (!wcscmp(type, L"DOMNodeRemovedFromDocument"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		for (int i = 0; i < m_listView.m_items.GetSize(); i++)
		{
			if ((ILDOMElement*)m_listView.m_items[i]->m_element == node)
			{
				CComQIPtr<ILDOMEventTarget> eventTarget = (ILDOMElement*)m_listView.m_items[i]->m_element;
				eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);

				m_listView.DeleteItem(i);
				break;
			}
		}
	}

	return S_OK;
}

////////////////

BOOL IsFilterUsed(ILDOMElement* element, BSTR filterId)
{
	CComQIPtr<ILElementCSSInlineStyle> stylable = element;
	if (stylable)
	{
		CComPtr<ILCSSStyleDeclaration> style;
		stylable->get_style(&style);

		CComPtr<ILCSSPrimitiveValue> filter;
		style->getPropertyCSSValue(L"filter", (ILCSSValue**)&filter);
		if (filter)
		{
			LCSSUnitType type;
			filter->get_primitiveType(&type);
			if (type == CSS_URI)
			{
				BSTR burl;
				filter->getStringValue(&burl);
				_bstr_t url = _bstr_t(burl, false);

				if (((BSTR)url)[0] == L'#')
				{
					_bstr_t uri = ((BSTR)url)+1;

					if (!wcscmp(uri, filterId))
						return TRUE;
				}
			}
		}
	}

	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> childElement = node;
		if (childElement)
		{
			BOOL bUsed = IsFilterUsed(childElement, filterId);
			if (bUsed)
				return bUsed;
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return FALSE;
}

void CSVGFiltersDlg::BuildItems()
{
	m_listView.RemoveItems();

	m_listView.AddItem(NULL, L"[none]");
	AddItems();
}

void CSVGFiltersDlg::AddEventListeners()
{
	for (int i = 0; i < m_listView.m_items.GetSize(); i++)
	{
		if (m_listView.m_items[i]->m_element)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = (ILDOMElement*)m_listView.m_items[i]->m_element;
			eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);
		}
	}
}

void CSVGFiltersDlg::RemoveEventListeners()
{
	for (int i = 0; i < m_listView.m_items.GetSize(); i++)
	{
		if (m_listView.m_items[i]->m_element)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = (ILDOMElement*)m_listView.m_items[i]->m_element;
			eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);
		}
	}
}

////////////////

BEGIN_CMD_MAP(CSVGFiltersDlg)
	CMD_HANDLER(ID_FILTERS_NEWFILTER, OnFiltersNewFilter)
	CMD_HANDLER(ID_SVGFILTERS_DELETEFILTER, OnFiltersDeleteFilter)

	CMD_HANDLER(ID_FILTERS_SELECTALLUNUSED, OnSelectAllUnused)

	CMD_HANDLER(ID_SVGLIST_SMALLTHUMBNAILS, OnFiltersSmallThumbnails)
	CMD_HANDLER(ID_SVGLIST_LARGETHUMBNAILS, OnFiltersLargeThumbnails)
	CMD_HANDLER(ID_SVGLIST_SMALLLISTVIEW, OnFiltersSmallListView)
	CMD_HANDLER(ID_SVGLIST_LARGELISTVIEW, OnFiltersLargeListView)
	CMD_UPDATE(ID_SVGLIST_SMALLTHUMBNAILS, OnFiltersSmallThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGETHUMBNAILS, OnFiltersLargeThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_SMALLLISTVIEW, OnFiltersSmallListViewUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGELISTVIEW, OnFiltersLargeListViewUpdate)
END_CMD_MAP()

LRESULT CSVGFiltersDlg::OnFiltersDeleteFilter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMElement> documentElement;
	m_listView.m_xmlDocument->get_documentElement(&documentElement);

	CArray<ILDOMElement*,ILDOMElement*> items;

	BOOL bAnyUsed = FALSE;

	for (int i = 0; i < m_listView.m_selectedItems.GetSize(); i++)
	{
		if (m_listView.m_selectedItems[i]->m_element)
		{
			if (!bAnyUsed)	// Only check once
			{
				CComBSTR id;
				((ILDOMElement*)m_listView.m_selectedItems[i]->m_element)->getAttribute(L"id", &id);

				BOOL bUsed = IsFilterUsed(documentElement, id);
				if (bUsed)
				{
					UINT nID = MessageBox("Some of the filters are in use, Delete anyway?", "WebEditor", MB_YESNO);
					if (nID == IDNO)
						return 0;

					bAnyUsed = TRUE;
				}
			}

			items.Add((ILDOMElement*)m_listView.m_selectedItems[i]->m_element);
		}
	}

	for (i = 0; i < items.GetSize(); i++)
	{
		CComPtr<ILDOMNode> parentNode;
		items[i]->get_parentNode(&parentNode);

		parentNode->removeChild(items[i], NULL);
	}

	return 0;
}

LRESULT CSVGFiltersDlg::OnSelectAllUnused(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_listView.DeselectAll();

	CComPtr<ILDOMElement> documentElement;
	m_listView.m_xmlDocument->get_documentElement(&documentElement);

	for (int i = 0; i < m_listView.m_items.GetSize(); i++)
	{
		if (m_listView.m_items[i]->m_element)
		{
			CComBSTR id;
			((ILDOMElement*)m_listView.m_items[i]->m_element)->getAttribute(L"id", &id);
			BOOL bUsed = IsFilterUsed(documentElement, id);

			if (!bUsed)
			{
				m_listView.SelectItem(i/*m_listView.m_items[i]->m_element*/);
			}
		}
	}

//	InvalidateRect(&m_areaRect);

	return 0;
}

#include "SVGFilterOptionsDlg.h"

LRESULT CSVGFiltersDlg::OnFiltersNewFilter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
//	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> eXMLDocument;
		m_viewGroup->get_eXMLDocument(&eXMLDocument);

		CComQIPtr<IEDocument> eDocument = eXMLDocument;

		CComPtr<ILDOMDocument> document;
		eXMLDocument->get_DOMDocument(&document);

		CSVGFilterOptionsDlg dlg;
		dlg.m_document = document;

		if (dlg.DoModal() == IDOK)
		{
			CComPtr<IOleUndoManager> undoManager;
			eDocument->get_undoManager(&undoManager);

			CComObject<CUndoParent>* pParentUndo;
			CComObject<CUndoParent>::CreateInstance(&pParentUndo);
			if (pParentUndo)
			{
				pParentUndo->AddRef();	// ???
				undoManager->Open(pParentUndo);

				CComPtr<ILSVGElement> svgDefsElement;
				eXMLDocument->FindOrCreateSVGDefs(&svgDefsElement);

				if (svgDefsElement)
				{
					CComPtr<ILSVGFilterElement> svgFilterElement;
					document->createElementNS(L"http://www.w3.org/2000/svg", L"filter", (ILDOMElement**)&svgFilterElement);

					if (svgFilterElement)
					{
						svgFilterElement->setAttribute(L"id", dlg.m_id);

						//CComPtr<IOleUndoManager> undoManager;
						//m_document->get_undoManager(&undoManager);

						CComObject<CWEUndoNewElement>* pUndo;
						CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
						if (pUndo)
						{
						//	pUndo->AddRef();
							pUndo->m_pDocument = static_cast<CEXMLDocument*>(eXMLDocument.p);

							pUndo->DoInitial(undoManager, svgFilterElement, svgDefsElement, NULL);

							{
								CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroup);

								CComPtr<IEElement> eElement;
								eXMLDocument->GetEElementFromDOMElement(svgFilterElement, &eElement);

								pViewGroup->m_activeReferencedElement = eElement;	// ??? reference element is still NULL
								m_viewGroup->ActivateElement(eElement, 0, NULL);
							}
						}
					}
				}

				undoManager->Close(pParentUndo, TRUE/*commit*/);
			}
		}
	}

	return 0;
}

#endif