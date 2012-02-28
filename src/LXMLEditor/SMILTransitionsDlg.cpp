// SMILTransitionsDlg.cpp : Implementation of CSMILTransitionsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SMILTransitionsDlg.h"

#include "EXMLDocument.h"	// TODO, remove
#include "EXMLViewGroup.h"	// TODO, remove
#include "SMILTimeGraphView.h"

#include "WEUndoNewElement.h"
#include "UndoParent.h"

#if 0

//IMPORTEXPORT ILDOMElement* GetElementByTagName(ILDOMNode* parentNode, BSTR tagName, BOOL bDeep = TRUE);
//IMPORTEXPORT ILDOMElement* GetElementByTagNameNS(ILDOMNode* parentNode, BSTR ns, BSTR tagName, BOOL bDeep = TRUE);

/////////////////////////////////////////////////////////////////////////////
// CSMILTransitionsDlg

int CSMILTransitionsDlg::FinalConstruct()
{
	return 0;
}

LRESULT CSMILTransitionsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (CSVGDefinitionsDlgT<CSMILTransitionsDlg>::OnCreate(uMsg, wParam, lParam, bHandled) != 0)
		return -1;

	::RegisterDragDrop(m_hWnd, this);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);

	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		m_listView.m_xmlDocument.Release();
		edocument->get_DOMDocument(&m_listView.m_xmlDocument);

		IDispEventImpl<1, CSMILTransitionsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());
	//	IDispEventImpl<2, CSMILTransitionsDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(edocument);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();

		OnSelectionStyleChanged();
	}

	return 0;
}

LRESULT CSMILTransitionsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}

	::RevokeDragDrop(m_hWnd);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

	{
		IDispEventImpl<1, CSMILTransitionsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
		RemoveEventListeners();

		m_listView.RemoveItems();

		m_listView.m_xmlDocument.Release();
	}

	CSVGDefinitionsDlgT<CSMILTransitionsDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);

	return 0;
}

LRESULT CSMILTransitionsDlg::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	for (int i = 0; i < m_listView.m_items.GetSize(); i++)
	{
		if (m_listView.m_items[i]->m_thumbnailBitmap)
		{
			DeleteObject(m_listView.m_items[i]->m_thumbnailBitmap);
			m_listView.m_items[i]->m_thumbnailBitmap = NULL;
			m_listView.m_items[i]->m_thumbnailBits = NULL;
		}
	}

	m_listView.InvalidateRect(&m_listView.m_areaRect, FALSE);

	double duration = 2;	// seconds
	m_progress += (200.0/1000.0) / duration;
	if (m_progress > 1) m_progress = 0;

	return 0;
}

LRESULT CSMILTransitionsDlg::OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

LRESULT CSMILTransitionsDlg::OnDblClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
				edocument->GetEElementFromDOMElement(((ILDOMElement*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element), &eElement);

				pViewGroup->m_activeReferencedElement = eElement;	// ??? reference element is still NULL
				m_viewGroup->ActivateElement(eElement, 0, NULL);
			}
		}
	}

	return 0;
}

void __stdcall CSMILTransitionsDlg::OnSelectionStyleChanged()
{
	ASSERT(m_viewGroup);

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
STDMETHODIMP CSMILTransitionsDlg::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	if (m_viewGroup)
	{
		*pdwEffect = DROPEFFECT_COPY;
	}

	return S_OK;
}

STDMETHODIMP CSMILTransitionsDlg::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CSMILTransitionsDlg::DragLeave()
{
	return S_OK;
}

#if 0
// TODO .. global function ??
HRESULT AddSVGElements(IEXMLDocument* m_document, HGLOBAL hData)
{
	CComPtr<ILDOMDocument> m_xmlDocument;
	m_document->get_DOMDocument(&m_xmlDocument);

	WCHAR* text = (WCHAR*)GlobalLock(hData);
	if (text)
	{
		int len = GlobalSize(hData);

		CComPtr<ILSVGDocument> svgdocument;
		svgdocument.CoCreateInstance(CLSID_LSVGDocument);

		VARIANT_BOOL bsuccess;
		svgdocument->loadXML(_bstr_t(text), &bsuccess);

		if (bsuccess)
		{
			CComQIPtr<IEDocument> eDocument = m_document;

			CComPtr<IOleUndoManager> undoManager;
			eDocument->get_undoManager(&undoManager);

			CComObject<CUndoParent>* pParentUndo;
			CComObject<CUndoParent>::CreateInstance(&pParentUndo);
			if (pParentUndo)
			{
				pParentUndo->AddRef();	// ???
				undoManager->Open(pParentUndo);

				CComPtr<ILSVGElement> svgDefsElement;
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

	return S_OK;
}
#endif

STDMETHODIMP CSMILTransitionsDlg::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
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
	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		if (hData = dataObject.GetGlobalData(CF_UNICODETEXT))
		{
//			AddSVGElements(edocument, hData);

			//return TRUE;
		}
	}
#endif

	return S_OK;
}

#if 0
// IUIEventHandler
STDMETHODIMP CSMILTransitionsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		ASSERT(m_viewGroup == NULL);
		/*
		if (m_document != NULL)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
			eventTarget->removeEventListener(L"DOMNodeInserted", this, VARIANT_TRUE);

			IDispEventImpl<2, CSMILTransitionsDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}
		*/

		m_viewGroup = viewGroup;

		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		m_listView.m_xmlDocument.Release();
		edocument->get_DOMDocument(&m_listView.m_xmlDocument);

		IDispEventImpl<1, CSMILTransitionsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);
	//	IDispEventImpl<2, CSMILTransitionsDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(edocument);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();

		OnSelectionStyleChanged();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSMILTransitionsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(IsUnknownEqualUnknown(m_viewGroup, object));

	IDispEventImpl<1, CSMILTransitionsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

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
STDMETHODIMP CSMILTransitionsDlg::handleEvent(ILDOMEvent* evt)
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

BOOL StringListContains(ILSVGStringList* list, BSTR value)
{
	long numberOfItems;
	list->get_numberOfItems(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		CComBSTR v;
		list->getItem(i, &v);

		if (!wcscmp(v, value))
			return TRUE;
	}

	return FALSE;
}

BOOL IsTransitionUsed(ILDOMElement* element, BSTR transitionId)
{
	CComQIPtr<ILSMILMediaElement> mediaElement = element;
	if (mediaElement)
	{
		{
			CComPtr<ILSVGStringList> transIn;
			mediaElement->get_transIn(&transIn);

			if (StringListContains(transIn, transitionId))
				return TRUE;
		}

		{
			CComPtr<ILSVGStringList> transOut;
			mediaElement->get_transOut(&transOut);

			if (StringListContains(transOut, transitionId))
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
			BOOL bUsed = IsTransitionUsed(childElement, transitionId);
			if (bUsed)
				return bUsed;
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return FALSE;
}

void CSMILTransitionsDlg::BuildItems()
{
	m_listView.RemoveItems();

//	m_listView.AddItem(NULL, L"[none]");
	AddItems();
}

void CSMILTransitionsDlg::AddEventListeners()
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

void CSMILTransitionsDlg::RemoveEventListeners()
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

BEGIN_CMD_MAP(CSMILTransitionsDlg)
	CMD_HANDLER(ID_TRANSITIONS_NEWTRANSITION, OnTransitionsNewTransition)
	CMD_HANDLER(ID_TRANSITIONS_DELETE, OnTransitionsDelete)
	CMD_HANDLER(ID_TRANSITIONS_PLACETRANSITION, OnTransitionsPlace)
	CMD_UPDATE(ID_TRANSITIONS_PLACETRANSITION, OnTransitionsPlaceUpdate)
	CMD_HANDLER(ID_TRANSITIONS_SELECTALLUNUSED, OnSelectAllUnused)
	CMD_HANDLER(ID_TRANSITIONS_ANIMATE, OnTransitionsAnimate)
	CMD_UPDATE(ID_TRANSITIONS_ANIMATE, OnTransitionsAnimateUpdate)

	CMD_HANDLER(ID_SVGLIST_SMALLTHUMBNAILS, OnSmallThumbnails)
	CMD_HANDLER(ID_SVGLIST_LARGETHUMBNAILS, OnLargeThumbnails)
	CMD_HANDLER(ID_SVGLIST_SMALLLISTVIEW, OnSmallListView)
	CMD_HANDLER(ID_SVGLIST_LARGELISTVIEW, OnLargeListView)
	CMD_UPDATE(ID_SVGLIST_SMALLTHUMBNAILS, OnSmallThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGETHUMBNAILS, OnLargeThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_SMALLLISTVIEW, OnSmallListViewUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGELISTVIEW, OnLargeListViewUpdate)
END_CMD_MAP()

LRESULT CSMILTransitionsDlg::OnTransitionsPlace(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_listView.m_selectedItems.GetSize() == 1/*m_listView.m_selectedItemIndex >= 0 && m_listView.m_selectedItemIndex < m_listView.m_items.GetSize()*/)
	{
		CComPtr<ILDOMElement> transition = (ILDOMElement*)m_listView.m_selectedItems[0]->m_element;

		// Ensure that the transition element has an ID
		CComBSTR transitionId;
		m_viewGroup->m_pDocument->SetElementID(transition, &transitionId);

		if (m_viewGroup->m_pActiveTimeGraphNode->m_type == -1)
		{
			CTransNode* pTransNode = (CTransNode*)m_viewGroup->m_pActiveTimeGraphNode;

			CComQIPtr<ILSMILMediaElement> mediaElement = pTransNode->m_parent->m_domElement;
			ASSERT(mediaElement);

			CComPtr<ILSVGStringList> transList;

			if (!wcscmp(pTransNode->m_name, L"transIn"))
			{
				transList = mediaElement->get_transIn();
			}
			else if (!wcscmp(pTransNode->m_name, L"transOut"))
			{
				transList = mediaElement->get_transOut();
			}
			else
				ASSERT(0);

			transList->appendItem(transitionId, NULL);
		}
		else
		{
			MessageBox("You must select a transIn or transOut node below a media element in the TimeGraphView", "LXMLEditor", MB_OK);
		}
	}

	return 0;
}

void CSMILTransitionsDlg::OnTransitionsPlaceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_listView.m_selectedItems.GetSize() == 1/*m_listView.m_selectedItemIndex >= 0 && m_listView.m_selectedItemIndex < m_listView.m_items.GetSize()*/)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CSMILTransitionsDlg::OnTransitionsDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

				BOOL bUsed = IsTransitionUsed(documentElement, id);
				if (bUsed)
				{
					UINT nID = MessageBox("Some of the transitions are in use, Delete anyway?", "WebEditor", MB_YESNO);
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

LRESULT CSMILTransitionsDlg::OnSelectAllUnused(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
			BOOL bUsed = IsTransitionUsed(documentElement, id);

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

LRESULT CSMILTransitionsDlg::OnTransitionsNewTransition(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> eXMLDocument;
		m_viewGroup->get_eXMLDocument(&eXMLDocument);

		CComQIPtr<IEDocument> eDocument = eXMLDocument;

		CComPtr<ILDOMDocument> document;
		eXMLDocument->get_DOMDocument(&document);

		CComPtr<ILDOMElement> documentElement;
		document->get_documentElement(&documentElement);

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

				//CComPtr<ILSVGElement> svgDefsElement;
				//eXMLDocument->FindOrCreateSVGDefs(&svgDefsElement);

				CComPtr<ILDOMElement> headElement = GetElementByTagNameNS(documentElement, L"http://www.w3.org/2001/SMIL20/Language", L"head");

				if (headElement)
				{
					CComPtr<ILSVGFilterElement> svgFilterElement;
					document->createElementNS(L"http://www.w3.org/2001/SMIL20/Language", L"transition", (ILDOMElement**)&svgFilterElement);

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

							pUndo->DoInitial(undoManager, svgFilterElement, headElement, NULL);

							// TODO: do this here?
							//CComPtr<IWebXMLViewGroup> viewGroup;
							//m_document->GetActiveViewGroup(&viewGroup);
							//if (viewGroup)
							{
								CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroup);

								CComPtr<IEElement> eElement;
								eXMLDocument->GetEElementFromDOMElement(svgFilterElement, &eElement);
#if 0	// ???
								pViewGroup->m_activeReferencedElement = eElement;	// ??? reference element is still NULL
#endif
								m_viewGroup->ActivateElement(eElement, 0, NULL);
							}
						}
					}
				}
				else
				{
					MessageBox("No head element", "LXMLEditor", MB_OK);
				}

				undoManager->Close(pParentUndo, TRUE/*commit*/);
			}
		}
	}

	return 0;
}

LRESULT CSMILTransitionsDlg::OnTransitionsAnimate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bAnimate = !m_bAnimate;

	if (m_bAnimate)
	{
		ASSERT(m_nTimer == 0);

		m_progress = 0;
		m_nTimer = SetTimer(1, 200);
	}
	else
	{
		if (m_nTimer)
		{
			KillTimer(m_nTimer);
			m_nTimer = 0;
		}

		if (m_progress != 0.5)
		{
			m_progress = 0.5;

			for (int i = 0; i < m_listView.m_items.GetSize(); i++)
			{
				if (m_listView.m_items[i]->m_thumbnailBitmap)
				{
					DeleteObject(m_listView.m_items[i]->m_thumbnailBitmap);
					m_listView.m_items[i]->m_thumbnailBitmap = NULL;
					m_listView.m_items[i]->m_thumbnailBits = NULL;
				}
			}

			m_listView.Invalidate();
		}
	}

	return 0;
}

void CSMILTransitionsDlg::OnTransitionsAnimateUpdate(long id, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_bAnimate);
}

#endif