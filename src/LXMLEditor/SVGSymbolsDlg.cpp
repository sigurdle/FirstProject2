#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGSymbolsDlg.h"

#include "EXMLDocument.h"	// TODO, remove (needed by undo so far)
#include "EXMLViewGroup.h"	// TODO, remove

#include "WEUndoNewElement.h"
#include "UndoParent.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CSVGSymbolsDlg

int CSVGSymbolsDlg::FinalConstruct()
{
	return 0;
}

LRESULT CSVGSymbolsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (CSVGDefinitionsDlgT<CSVGSymbolsDlg>::OnCreate(uMsg, wParam, lParam, bHandled) != 0)
		return -1;

	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

//		m_listView.m_xmlDocument.Release();
		edocument->get_DOMDocument(&m_listView.m_xmlDocument);
//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_document);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();
	}

	::RegisterDragDrop(m_hWnd, this);

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CSVGSymbolsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	{
		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		m_listView.RemoveItems();

		m_listView.m_xmlDocument.Release();
//		m_document.Release();

#if 0	// This isn't necessary is it?
		m_viewGroup->m_pDocument->g_selectedSymbol = NULL;
#endif
	}
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	::RevokeDragDrop(m_hWnd);

	CSVGDefinitionsDlgT<CSVGSymbolsDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);

	return 0;
}

LRESULT CSVGSymbolsDlg::OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_listView.m_selectedItemIndex >= 0 && m_listView.m_selectedItemIndex < m_listView.m_items.GetSize())
	{
		m_viewGroup->m_pDocument->g_selectedSymbol = CComQIPtr<ILSVGElement>((ILDOMElement*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element);
	}
	else
	{
		m_viewGroup->m_pDocument->g_selectedSymbol = NULL;
	}

	return 0;
}

#if 0
LRESULT CSVGSymbolsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	ButtonDown(nFlags, point);

	return 0;
}

LRESULT CSVGSymbolsDlg::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_selectedItemIndex >= 0)
	{
		CComPtr<IWebXMLViewGroup> viewGroup;
		m_document->GetActiveViewGroup(&viewGroup);
		if (viewGroup)
		{
			CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(viewGroup.p);

//			CElementImpl* pElement = ((CEXMLDocument*)m_document.p)->m_pTree->FindDOMElement(m_items[m_selectedItemIndex]);
			CComPtr<IEElement> pElement;
			m_document->GetEElementFromDOMElement(m_items[m_selectedItemIndex], &pElement);

			pViewGroup->ActivateElement(pElement, 0, NULL);
		}
	}

	return 0;
}
#endif

/*
void CSVGSymbolsDlg::BuildItems()
{
	m_items.RemoveAll();

	CComPtr<ILDOMDocument> document;
	m_document->get_DOMDocument(&document);

	CComPtr<ILDOMNodeList> nodeList;
	document->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"symbol", &nodeList);
	if (nodeList)
	{
		long length;
		nodeList->get_length(&length);

		for (int i = 0; i < length; i++)
		{
			CComPtr<ILSVGSymbolElement> symbol;
			nodeList->item(i, (ILDOMNode**)&symbol);

			m_items.Add(symbol);
		}
	}
}
*/

STDMETHODIMP CSVGSymbolsDlg::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	return S_OK;
}

STDMETHODIMP CSVGSymbolsDlg::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CSVGSymbolsDlg::DragLeave()
{
	return S_OK;
}

STDMETHODIMP CSVGSymbolsDlg::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	ASSERT(0);
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
	if (hData = dataObject.GetGlobalData(CF_UNICODETEXT))
	{
		WCHAR* text = (WCHAR*)GlobalLock(hData);
		int len = GlobalSize(hData);

		CComPtr<ILSVGDocument> svgdocument;
		svgdocument.CoCreateInstance(CLSID_LSVGDocument);

		VARIANT_BOOL bsuccess;
		svgdocument->loadXML(_bstr_t(text), &bsuccess);

		if (bsuccess)
		{
			CComQIPtr<IEDocument> eDocument = m_viewGroup->m_pDocument;

			CComPtr<IOleUndoManager> undoManager;
			eDocument->get_undoManager(&undoManager);

			CComObject<CUndoParent>* pParentUndo;
			CComObject<CUndoParent>::CreateInstance(&pParentUndo);
			if (pParentUndo)
			{
				pParentUndo->AddRef();	// ???
				undoManager->Open(pParentUndo);

				CComPtr<ILSVGElement> svgDefsElement;
				m_viewGroup->m_pDocument->FindOrCreateSVGDefs(&svgDefsElement);

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

						CComQIPtr<ILSVGSymbolElement> svgSymbolElement = node;
						if (svgSymbolElement)
						{
							m_listView.m_xmlDocument->adoptNode(svgSymbolElement, NULL);

							CComObject<CWEUndoNewElement>* pUndo;
							CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
							if (pUndo)
							{
							//	pUndo->AddRef();
								pUndo->m_pDocument = m_viewGroup->m_pDocument;

								pUndo->DoInitial(undoManager, svgSymbolElement, svgDefsElement, NULL);
							}
						}

						node = nextSibling;
					}
				}

				undoManager->Close(pParentUndo, TRUE/*commit*/);
			}
		}

		GlobalUnlock(hData);
		//return TRUE;
	}
#endif

	return S_OK;
}

HRESULT __stdcall CSVGSymbolsDlg::OnDOMEvent(ILDOMEvent* evt)
{
	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}

#if 0
// IUIEventHandler
STDMETHODIMP CSVGSymbolsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLDocument> document = object;
	if (document)
	{
		if (m_document != NULL)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
			eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

			IDispEventImpl<2, CSVGSymbolsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}

		m_document = document;

		m_listView.m_xmlDocument.Release();
		m_document->get_DOMDocument(&m_listView.m_xmlDocument);

		IDispEventImpl<2, CSVGSymbolsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();

		if (m_hWnd)
		{
			Invalidate();
		}

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSVGSymbolsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(IsUnknownEqualUnknown(m_document, object));

	IDispEventImpl<2, CSVGSymbolsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
	eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

	m_listView.RemoveItems();

	m_listView.m_xmlDocument.Release();
	m_document.Release();

	g_selectedSymbol = NULL;

	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}
#endif

// ILDOMEventListener
STDMETHODIMP CSVGSymbolsDlg::handleEvent(ILDOMEvent* evt)
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

void CSVGSymbolsDlg::BuildItems()
{
	m_listView.RemoveItems();

//	m_listView.AddItem(NULL, L"[none]");
	AddItems();
}

void CSVGSymbolsDlg::AddEventListeners()
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

void CSVGSymbolsDlg::RemoveEventListeners()
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

BOOL IsSymbolUsed(ILDOMElement* element, BSTR symbolId)
{
	CComQIPtr<ILSVGUseElement> useElement = element;
	if (useElement)
	{
		CComQIPtr<ILSVGURIReference> uriReference = useElement;

		CComPtr<ILSVGAnimatedString> a;
		uriReference->get_href(&a);

		CComBSTR uri;
		a->get_baseVal(&uri);

		if (((BSTR)uri)[0] == L'#')
		{
			_bstr_t uriid = ((BSTR)uri)+1;

			if (!wcscmp(uriid, symbolId))
				return TRUE;
		}
	}

	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> childElement = node;
		if (childElement)
		{
			BOOL bUsed = IsSymbolUsed(childElement, symbolId);
			if (bUsed)
				return bUsed;
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return FALSE;
}

////////////////

BEGIN_CMD_MAP(CSVGSymbolsDlg)
	CMD_HANDLER(ID_SYMBOLS_DEFINESYMBOL, OnSymbolDefineSymbol)
	CMD_HANDLER(ID_SYMBOLS_NEWSYMBOL, OnSymbolsNewSymbol)
	CMD_HANDLER(ID_SYMBOLS_PLACESYMBOL, OnSymbolsPlaceSymbol)
	CMD_HANDLER(ID_SYMBOLS_BREAKLINKTOSYMBOL, OnBreakLinkToSymbol)
	CMD_UPDATE(ID_SYMBOLS_BREAKLINKTOSYMBOL, OnBreakLinkToSymbolUpdate)
	CMD_HANDLER(ID_SYMBOLS_SELECTALLUNUSED, OnSymbolSelectAllUnused)

	CMD_HANDLER(ID_SVGLIST_SMALLTHUMBNAILS, OnListSmallThumbnails)
	CMD_HANDLER(ID_SVGLIST_LARGETHUMBNAILS, OnListLargeThumbnails)
	CMD_HANDLER(ID_SVGLIST_SMALLLISTVIEW, OnListSmallListView)
	CMD_HANDLER(ID_SVGLIST_LARGELISTVIEW, OnListLargeListView)
	CMD_UPDATE(ID_SVGLIST_SMALLTHUMBNAILS, OnListSmallThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGETHUMBNAILS, OnListLargeThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_SMALLLISTVIEW, OnListSmallListViewUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGELISTVIEW, OnListLargeListViewUpdate)
END_CMD_MAP()

#include "SVGFilterOptionsDlg.h"

LRESULT CSVGSymbolsDlg::OnSymbolDefineSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
				CComPtr<ILSVGSymbolElement> svgFilterElement;
				document->createElementNS(L"http://www.w3.org/2000/svg", L"symbol", (ILDOMElement**)&svgFilterElement);

				if (svgFilterElement)
				{
					svgFilterElement->setAttribute(L"id", dlg.m_id);

					{
						double minx = 99999999;
						double miny = 99999999;
						double maxx = -99999999;
						double maxy = -99999999;

						for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
						{
							CComPtr<IEElement> eElement;
							m_viewGroup->m_targetElements[i]->get_eElement(&eElement);

							CComPtr<ILDOMElement> element;
							eElement->get_domElement(&element);

							CComQIPtr<ILSVGLocatable> locatable = element;
							if (locatable)
							{
								CComPtr<ILSVGRect> svgrect;
								locatable->getBBox(&svgrect);
								SVGRect rect = svgrect;

								minx = min(minx, rect.X);
								miny = min(miny, rect.Y);
								maxx = max(maxx, rect.X+rect.Width);
								maxy = max(maxy, rect.Y+rect.Height);

								CComPtr<ILDOMNode> clone;
								element->cloneNode(VARIANT_TRUE/*bDeep*/, &clone);

								svgFilterElement->appendChild(clone, NULL);
							}
						}
						WCHAR viewBox[256];
						swprintf(viewBox, L"%g %g %g %g", minx, miny, maxx-minx, maxy-miny);
						svgFilterElement->setAttribute(L"viewBox", viewBox);
					}

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

	return 0;
}

LRESULT CSVGSymbolsDlg::OnSymbolsNewSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CSVGSymbolsDlg::OnSymbolsPlaceSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_listView.m_selectedItemIndex >= 0)
	{
		CComQIPtr<ILDOMElement> symbol = (ILDOMElement*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element;

		CComPtr<ILDOMElement> documentElement;
		m_listView.m_xmlDocument->get_documentElement(&documentElement);

		CComBSTR id;
		symbol->getAttribute(L"id", &id);

		_bstr_t uri = _bstr_t(L"#") + (BSTR)id;

		CComPtr<ILSVGUseElement> useElement;
		m_listView.m_xmlDocument->createElementNS(L"http://www.w3.org/2000/svg", L"use", (ILDOMElement**)&useElement);
		if (useElement)
		{
			{
				CComQIPtr<ILSVGURIReference> uriReference = useElement;
				CComPtr<ILSVGAnimatedString> a;
				uriReference->get_href(&a);
				a->put_baseVal(uri);
			}

			{
				CComQIPtr<ILSVGFitToViewBox> viewBox = symbol;
				CComPtr<ILSVGAnimatedRect> asvgrect;
				viewBox->get_viewBox(&asvgrect);
				CComPtr<ILSVGRect> svgrect;
				asvgrect->get_baseVal(&svgrect);
				SVGRect rect = svgrect;

				// width
				{
					CComQIPtr<ILSVGAnimatedLength> alength;
					useElement->get_width(&alength);
					CComPtr<ILSVGLength> length;
					alength->get_baseVal(&length);
					
					length->put_value(rect.Width);
				}

				// height
				{
					CComQIPtr<ILSVGAnimatedLength> alength;
					useElement->get_height(&alength);
					CComPtr<ILSVGLength> length;
					alength->get_baseVal(&length);
					
					length->put_value(rect.Height);
				}
			}

			documentElement->appendChild(useElement, NULL);
		}
	}

	return 0;
}

LRESULT CSVGSymbolsDlg::OnBreakLinkToSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup->m_pActiveElement)
	{
		CComPtr<IEElement> eElement;
		m_viewGroup->m_pActiveElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILSVGUseElement> useElement = domElement;

		if (useElement)
		{
			CComPtr<ILDOMDocument> document;
			m_viewGroup->m_pDocument->get_DOMDocument(&document);

			CComQIPtr<ILSVGURIReference> uriReference = useElement;
			CComPtr<ILSVGAnimatedString> a;
			uriReference->get_href(&a);

			CComBSTR uri;
			a->get_baseVal(&uri);

			BSTR id = &((BSTR)uri)[1];

			CComPtr<ILDOMElement> refElement;
			document->getElementById(id, &refElement);

			CComQIPtr<ILSVGSymbolElement> symbolElement = refElement;
			if (symbolElement)
			{
				CComPtr<ILDOMElement> gElement;
				document->createElementNS(L"http://www.w3.org/2000/svg", L"g", &gElement);
				if (gElement)
				{
					CComPtr<ILDOMElement> svgElement;
					document->createElementNS(L"http://www.w3.org/2000/svg", L"svg", &svgElement);
					if (svgElement)
					{
						CComBSTR viewBox;
						symbolElement->getAttribute(L"viewBox", &viewBox);
						svgElement->setAttribute(L"viewBox", viewBox);

						//symbolElement->getAttribute(L"style", &viewBox);

						CComBSTR width;
						CComBSTR height;
						useElement->getAttribute(L"width", &width);
						useElement->getAttribute(L"height", &height);

						if (width != NULL)
							svgElement->setAttribute(L"width", width);
						else
							svgElement->setAttribute(L"width", L"100%");

						if (height != NULL)
							svgElement->setAttribute(L"height", height);
						else
							svgElement->setAttribute(L"height", L"100%");

						CComPtr<ILDOMNode> node;
						symbolElement->get_firstChild(&node);
						while (node)
						{
							CComQIPtr<ILDOMElement> element = node;
							if (element)
							{
								CComPtr<ILDOMNode> clone;
								element->cloneNode(VARIANT_TRUE/*bDeep*/, &clone);

								svgElement->appendChild(clone, NULL);
							}
							CComPtr<ILDOMNode> nextSibling;
							node->get_nextSibling(&nextSibling);
							node = nextSibling;
						}

						gElement->appendChild(svgElement, NULL);
					}

					CComPtr<ILDOMNode> parentNode;
					useElement->get_parentNode(&parentNode);

					CComPtr<ILDOMNode> p;
					parentNode->replaceChild(gElement, useElement, &p);
				}
			}
		}
	}

	return 0;
}

void CSVGSymbolsDlg::OnBreakLinkToSymbolUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_viewGroup->m_pActiveElement)
	{
		CComPtr<IEElement> eElement;
		m_viewGroup->m_pActiveElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILSVGUseElement> useElement = domElement;

		if (useElement)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CSVGSymbolsDlg::OnSymbolSelectAllUnused(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
			BOOL bUsed = IsSymbolUsed(documentElement, id);

			if (!bUsed)
			{
				m_listView.SelectItem(i);
			}
		}
	}

	return 0;
}

#endif