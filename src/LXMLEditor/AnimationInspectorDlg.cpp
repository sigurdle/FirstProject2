// AnimationInspectorDlg.cpp : Implementation of CAnimationInspectorDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "AnimationInspectorDlg.h"

#include "ControlsWindow.h"
#include "XMLControlsHandler.h"

#if 0

LRESULT CAnimationInspectorDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->AddEventHandler(this);

	return 0;
}

LRESULT CAnimationInspectorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->RemoveEventHandler(this);

	return 0;
}

LRESULT CAnimationInspectorDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	if (m_pControlWindow)
	{
		HWND hwnd;
		m_pControlWindow->get_hwnd(&hwnd);
		::MoveWindow(hwnd, 0, 0, client.right, client.bottom, TRUE);
	}

	return 0;
}

void AddAnimationTypeControls(CXMLControlsHandler* handler)
{
	handler->m_controlWindow->AddControl(new CXMLControlPopup("animValues", L"values|from-to|from-by|to|by"));

	CComBSTR values;
	handler->/*m_controlWindow->*/GetPathNodeValue(L"@values", &values);

	CComBSTR from;
	handler->/*m_controlWindow->*/GetPathNodeValue(L"@from", &from);

	CComBSTR to;
	handler->/*m_controlWindow->*/GetPathNodeValue(L"@to", &to);

	CComBSTR by;
	handler->/*m_controlWindow->*/GetPathNodeValue(L"@by", &by);

	if (values != NULL)
	{
		handler->m_controlWindow->GetControl("animValues")->SetProperty(NULL, _bstr_t(L"values"));
	}
	else if (from != NULL)
	{
		if (to != NULL)
		{
			handler->m_controlWindow->GetControl("animValues")->SetProperty(NULL, _bstr_t(L"from-to"));
		}
		else if (by != NULL)
		{
			handler->m_controlWindow->GetControl("animValues")->SetProperty(NULL, _bstr_t(L"from-by"));
		}
	}
	else if (to != NULL)
	{
		handler->m_controlWindow->GetControl("animValues")->SetProperty(NULL, _bstr_t(L"to"));
	}
	else if (by != NULL)
	{
		handler->m_controlWindow->GetControl("animValues")->SetProperty(NULL, _bstr_t(L"by"));
	}

//
	handler->m_controlWindow->AddData(new CXMLStringData(L"@additive", L"replace"));
	handler->m_controlWindow->AddControl(new CXMLControlPopup("additive", L"replace|sum"));
	handler->m_controlWindow->GetControl("additive")->ConnectData(handler->m_controlWindow->GetData(L"@additive"));

	handler->m_controlWindow->AddData(new CXMLStringData(L"@accumulate", L"none"));
	handler->m_controlWindow->AddControl(new CXMLControlPopup("accumulate", L"none|sum"));
	handler->m_controlWindow->GetControl("accumulate")->ConnectData(handler->m_controlWindow->GetData(L"@accumulate"));
}

void HandleAnimationType(CXMLControlsHandler* handler, CControl* pControl)
{
	if (pControl->GetName() == "animValues")
	{
		_bstr_t type = handler->m_controlWindow->GetControl("animValues")->GetProperty(NULL);

		int index;
				if (!wcscmp(type, L"values"))		index = 0;
		else	if (!wcscmp(type, L"from-to"))	index = 1;
		else	if (!wcscmp(type, L"from-by"))	index = 2;
		else	if (!wcscmp(type, L"to"))			index = 3;
		else	if (!wcscmp(type, L"by"))			index = 4;
		else
			ASSERT(0);

		if (index == 0)	// values
		{
			CComBSTR from;
			handler->GetPathNodeValue(L"@from", &from);

			CComBSTR to;
			handler->GetPathNodeValue(L"@to", &to);

			handler->SetPathNodeValue(L"@from", NULL);
			handler->SetPathNodeValue(L"@to", NULL);
			handler->SetPathNodeValue(L"@by", NULL);

			if (from != NULL && to != NULL)
			{
				CComBSTR attvalue;
				attvalue = from;
				attvalue += L";";
				attvalue += to;
				handler->SetPathNodeValueIfNotExists(L"@values", attvalue);
				handler->SetPathNodeValueIfNotExists(L"@keyTimes", L"0;1");
			}
			else
			{
				handler->SetPathNodeValueIfNotExists(L"@values", L"");
			}
		}
		else if (index == 1)	// from-to
		{
			handler->SetPathNodeValue(L"@values", NULL);
			handler->SetPathNodeValue(L"@keyTimes", NULL);
			handler->SetPathNodeValue(L"@by", NULL);

			handler->SetPathNodeValueIfNotExists(L"@from", L"");
			handler->SetPathNodeValueIfNotExists(L"@to", L"");
		}
		else if (index == 2)	// from-by
		{
			handler->SetPathNodeValue(L"@values", NULL);
			handler->SetPathNodeValue(L"@keyTimes", NULL);
			handler->SetPathNodeValue(L"@to", NULL);

			handler->SetPathNodeValueIfNotExists(L"@from", L"");
			handler->SetPathNodeValueIfNotExists(L"@by", L"");
		}
		else if (index == 3)	// to
		{
			handler->SetPathNodeValue(L"@values", NULL);
			handler->SetPathNodeValue(L"@keyTimes", NULL);
			handler->SetPathNodeValue(L"@from", NULL);
			handler->SetPathNodeValue(L"@by", NULL);

			handler->SetPathNodeValueIfNotExists(L"@to", L"");
		}
		else if (index == 4)	// by
		{
			handler->SetPathNodeValue(L"@values", NULL);
			handler->SetPathNodeValue(L"@keyTimes", NULL);
			handler->SetPathNodeValue(L"@from", NULL);
			handler->SetPathNodeValue(L"@to", NULL);

			handler->SetPathNodeValueIfNotExists(L"@by", L"");
		}
	}
}

class CAnimateHandler :
	public CXMLControlsHandler
{
public:
	CAnimateHandler()
	{
	}

	virtual void Setup()
	{
		AddAnimationTypeControls(this);

		m_controlWindow->AddData(new CXMLStringData(L"@calcMode", L"linear"));

		m_controlWindow->AddControl(new CXMLControlPopup("calcMode", L"discrete|linear|paced"));
		m_controlWindow->GetControl("calcMode")->ConnectData(m_controlWindow->GetData(L"@calcMode"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		HandleAnimationType(this, pControl);
	}
};

class CSVGAnimateTransformHandler :
	public CXMLControlsHandler
{
public:
	CSVGAnimateTransformHandler()
	{
	}

	virtual void Setup()
	{
		AddAnimationTypeControls(this);

		m_controlWindow->AddData(new CXMLStringData(L"@calcMode", L"linear"));

		m_controlWindow->AddControl(new CXMLControlPopup("calcMode", L"discrete|linear|paced"));
		m_controlWindow->GetControl("calcMode")->ConnectData(m_controlWindow->GetData(L"@calcMode"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		HandleAnimationType(this, pControl);
	}
};

class CSVGAnimateMotionHandler :
	public CXMLControlsHandler
{
public:
	CSVGAnimateMotionHandler()
	{
	}

	virtual void Setup()
	{
		//AddAnimationTypeControls(this);

		m_controlWindow->AddData(new CXMLStringData(L"@rotate", L"auto"));

		m_controlWindow->AddControl(new CControlAnimateMotionRotate("rotate"));
		m_controlWindow->GetControl("rotate")->ConnectData(m_controlWindow->GetData(L"@rotate"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		HandleAnimationType(this, pControl);
	}
};

void __stdcall CAnimationInspectorDlg::OnViewGroupSelectionChanging()
{
	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		// Remove event listeners on element
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = domElement;

		// Non-Capture
			eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_FALSE);

		// Capture
			eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
		}
	}
}

void __stdcall CAnimationInspectorDlg::OnViewGroupSelectionChanged()
{
	ASSERT(m_viewGroup);

	if (m_pControlWindow)
	{
		m_pControlWindow->DestroyWindow();
		m_pControlWindow.Release();
		//m_pControlWindow = NULL;
	}

	{
		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		CComBSTR tagName;
		CComBSTR namespaceURI;

		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			// Add event listeners on element
			{
				CComQIPtr<ILDOMEventTarget> eventTarget = domElement;

			// Non-Capture
				eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_FALSE);

			// Capture
				eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
			}

			CComBSTR tagName2;
			domElement->get_localName(&tagName2);
			if (tagName2.Length() == 0)
			{
				tagName2.Empty();
				domElement->get_tagName(&tagName2);
			}

			CComBSTR namespaceURI2;
			domElement->get_namespaceURI(&namespaceURI2);

			if (i == 0)
			{
				tagName = tagName2;
				namespaceURI = namespaceURI2;
			}
			else if (
				!((namespaceURI.Length() == 0 && namespaceURI2.Length() == 0) || !wcscmp(namespaceURI, namespaceURI2))
				||
				wcscmp(tagName, tagName2))
			{
				tagName.Empty();
				namespaceURI.Empty();
				break;
			}
		}

		if (tagName.Length())
		{
			//if (m_dlg == NULL)
			{
				CComObject<CControlsContainer>* p;
				CComObject<CControlsContainer>::CreateInstance(&p);
				if (p)
				{
					p->AddRef();

					CXMLControlsHandler* handler = NULL;

					if (!wcscmp(namespaceURI, L"http://www.w3.org/1999/xhtml"))
					{
					}
					else if (!wcscmp(namespaceURI, L"http://www.w3.org/2000/svg"))
					{
						if (!wcscmp(tagName, L"animate"))
						{
							
							handler = new CAnimateHandler();
							handler->m_viewGroup = m_viewGroup;
						}
						else if (!wcscmp(tagName, L"animateTransform"))
						{
							handler = new CSVGAnimateTransformHandler();
							handler->m_viewGroup = m_viewGroup;
						}
						else if (!wcscmp(tagName, L"animateMotion"))
						{
							handler = new CSVGAnimateMotionHandler();
							handler->m_viewGroup = m_viewGroup;
						}
					}
					else if (!wcscmp(namespaceURI, L"http://www.w3.org/2001/SMIL20/Language") ||
								!wcscmp(namespaceURI, L"http://www.w3.org/2000/SMIL20/CR/Language"))
					{
					}

					p->m_pControlsHandler = handler;

					if (p->m_pControlsHandler)
					{
						p->m_pControlsHandler->Setup();

						for (int nattr = 0; nattr < p->m_attributes.GetSize(); nattr++)
						{
							CXMLData* pData = p->m_attributes[nattr];

							handler->UpdateData(pData);
						}
					}

					m_pControlWindow = p;
				}
			}

			if (m_pControlWindow)
			{
				BOOL success;
				m_pControlWindow->Create(m_hWnd);
				m_pControlWindow->ShowWindow(SW_SHOW);

				CRect client;
				GetClientRect(&client);

				HWND hwnd;
				m_pControlWindow->get_hwnd(&hwnd);
				::MoveWindow(hwnd, 0, 0, client.right, client.bottom, TRUE);
			}
		}
		else
		{
		}
	}
}

// ILDOMEventListener
STDMETHODIMP CAnimationInspectorDlg::handleEvent(ILDOMEvent* evt)
{
	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, L"DOMAttrModified"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		LDOMAttrChangeType attrChangeType;
		mut->get_attrChange(&attrChangeType);

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComPtr<ILDOMNode> attrNode;
		mut->get_relatedNode(&attrNode);
		CComQIPtr<ILDOMAttr> attr = attrNode;

		CComBSTR name;
		attr->get_name(&name);

		//_bstr_path = GetNodePath(domElement

		//CXMLAttributesDlg* dlg = static_cast<CXMLAttributesDlg*>(m_dlg.p);
		//if (dlg)
		if (m_pControlWindow)
		{
			for (int nattr = 0; nattr < m_pControlWindow->m_attributes.GetSize(); nattr++)
			{
				CXMLData* pData = m_pControlWindow->m_attributes[nattr];

				_bstr_t path = L"@" + _bstr_t(name);

				if (!wcscmp(pData->m_name, path))
				{
#if 0	// TODO have this
					m_pControlWindow->UpdateData(pData);
#endif
				}
			}
		}
	}

	return S_OK;
}

// IUIEventHandler
STDMETHODIMP CAnimationInspectorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;

//	CComQIPtr<IEElement> element = object;

	if (viewGroup/*element*/)
	{
		ASSERT(m_viewGroup == NULL);
		m_viewGroup = viewGroup;
		IDispEventImpl<1, CAnimationInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);


		OnViewGroupSelectionChanged();


		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CAnimationInspectorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(m_viewGroup != NULL);

	if (m_pControlWindow)
	{
		m_pControlWindow->DestroyWindow();
		m_pControlWindow.Release();
	}

	OnViewGroupSelectionChanging();

	IDispEventImpl<1, CAnimationInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();

#if 0
	if (m_dlg)
	{
		CComQIPtr<IInspectWebElementDlg> idlg = m_dlg;
		idlg->SetElement(NULL);

		m_dlg->DestroyWindow();
		m_dlg.Release();
	}

	m_element = NULL;
#endif

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CAnimationInspectorDlg

#if 0
LRESULT CAnimationInspectorDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	m_dlgs.RemoveAll();

#if 0
	CWebElementDlg* pDlg;

// SMIL
	pDlg = new CWebElementDlg;
	pDlg->m_clsid = CLSID_SMILAnimateColorDlg;
	pDlg->m_namespaceURI = L"http://www.w3.org/2001/SMIL20/Language";
	pDlg->m_tagName = L"animateColor";
	m_dlgs.Add(pDlg);

	pDlg = new CWebElementDlg;
	pDlg->m_clsid = CLSID_SMILSetDlg;
	pDlg->m_namespaceURI = L"http://www.w3.org/2001/SMIL20/Language";
	pDlg->m_tagName = L"set";
	m_dlgs.Add(pDlg);

	pDlg = new CWebElementDlg;
	pDlg->m_clsid = CLSID_SMILAnimateDlg;
	pDlg->m_namespaceURI = L"http://www.w3.org/2001/SMIL20/Language";
	pDlg->m_tagName = L"animate";
	m_dlgs.Add(pDlg);

// SVG
	pDlg = new CWebElementDlg;
	pDlg->m_clsid = CLSID_SMILAnimateDlg;
	pDlg->m_namespaceURI = L"http://www.w3.org/2000/svg";
	pDlg->m_tagName = L"animate";
	m_dlgs.Add(pDlg);

	pDlg = new CWebElementDlg;
	pDlg->m_clsid = CLSID_SMILSetDlg;
	pDlg->m_namespaceURI = L"http://www.w3.org/2000/svg";
	pDlg->m_tagName = L"set";
	m_dlgs.Add(pDlg);

	pDlg = new CWebElementDlg;
	pDlg->m_clsid = CLSID_SMILAnimateColorDlg;
	pDlg->m_namespaceURI = L"http://www.w3.org/2000/svg";
	pDlg->m_tagName = L"animateColor";
	m_dlgs.Add(pDlg);

	pDlg = new CWebElementDlg;
	pDlg->m_clsid = CLSID_SVGAnimateMotionDlg;
	pDlg->m_namespaceURI = L"http://www.w3.org/2000/svg";
	pDlg->m_tagName = L"animateMotion";
	m_dlgs.Add(pDlg);

	pDlg = new CWebElementDlg;
	pDlg->m_clsid = CLSID_SVGAnimateTransformDlg;
	pDlg->m_namespaceURI = L"http://www.w3.org/2000/svg";
	pDlg->m_tagName = L"animateTransform";
	m_dlgs.Add(pDlg);

//
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);
#endif

	return 0;
}

LRESULT CAnimationInspectorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);
#endif

	return 0;
}

STDMETHODIMP CAnimationInspectorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEElement> element = object;

#if 0
	if (element)
	{
		CRect client;
		GetClientRect(&client);

		if (element != m_element)
		{
			m_element = element;

			CComPtr<IEXMLDocument> edocument;
			m_element->get_ownerDocument(&edocument);

			CComPtr<ILDOMElement> domelement;
			m_element->get_domElement(&domelement);

			BSTR bnamespaceURI;
			domelement->get_namespaceURI(&bnamespaceURI);
			_bstr_t namespaceURI = _bstr_t(bnamespaceURI, false);

			BSTR btagName;
			domelement->get_localName(&btagName);
			if (SysStringLen(btagName) == 0)
			{
				domelement->get_tagName(&btagName);
			}
			_bstr_t tagName = _bstr_t(btagName, false);

			CWebElementDlg* pDlg = NULL;

			for (int i = 0; i < m_dlgs.GetSize(); i++)
			{
				if (!wcscmp(namespaceURI, m_dlgs[i]->m_namespaceURI) &&
					!wcscmp(tagName, m_dlgs[i]->m_tagName))
				{
					pDlg = m_dlgs[i];
					break;
				}
			}

			if (pDlg)
			{
				m_dlg.CoCreateInstance(pDlg->m_clsid);
				if (m_dlg)
				{
					BOOL success;
					m_dlg->Create(m_hWnd, &success);
					m_dlg->ShowWindow(SW_SHOW);

					CComQIPtr<IInspectWebElementDlg> idlg = m_dlg;
					idlg->SetElement(m_element);

					HWND hwnd;
					m_dlg->get_hwnd(&hwnd);
					::MoveWindow(hwnd, 0, 0, client.right, client.bottom, TRUE);
				}

				/*
				CComQIPtr<ILSVGAnimationElement> animationElement = domelement;
				if (animationElement)
				{
					CComPtr<ILSVGElement> targetElement;
					animationElement->get_targetElement(&targetElement);
					if (targetElement)
					{
						CComPtr<IEElement> etargetElement;
						edocument->GetEElementFromDOMElement(targetElement, &etargetElement);

						CComQIPtr<IUIManager> uiManager = gIFrame;
						uiManager->ActivateObject(m_element, etargetElement);
#if 0
						IUIRegisteredDlg* pDlgclass = NULL;
						for (int i = 0; i < pFrame->m_dialogs.GetSize(); i++)
						{
							if (pFrame->m_dialogs[i]->m_clsid == CLSID_InspectorDlg)
							{
								pDlgclass = pFrame->m_dialogs[i];
							}
						}

						if (pDlgclass)
						{
							CComPtr<IUIDlg> dlg;

							long n;
							pDlgclass->GetDialogsCount(&n);
							if (n > 0)
							{
								dlg = static_cast<CRegisteredDialog*>(pDlgclass)->m_dialogs[0];
							}
							else
							{
								pDlgclass->CreateDlg(&dlg);
							}

							if (dlg)
							{
								CComQIPtr<IWEColorDlg> colorDlg = dlg;
								colorDlg->SetColor(color);
							}
						}
#endif
					}
				}
				*/
			}
		}

		*cookie = 1;
	}
#endif
	return S_OK;
}

STDMETHODIMP CAnimationInspectorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
#if 0
	if (m_dlg)
	{
		CComQIPtr<IInspectWebElementDlg> idlg = m_dlg;
		idlg->SetElement(NULL);

		m_dlg->DestroyWindow();
		m_dlg.Release();
	}

	m_element = NULL;

#if 0
	CComQIPtr<IWebElement> element = object;

	if (element)
	{
		if (element == m_pElement)
		{
			EndEdit();

			m_attributes.RemoveAll();

		// Don't listen to this document events anymore
			CComQIPtr<IESvgDocument> webDocument;
			m_pElement->m_pDocument->QueryInterface(IID_IESvgDocument, (void**)&webDocument);
			IDispEventImpl<2, CElementAttrsDlg, &DIID__IESvgDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(webDocument);

			m_pElement = NULL;

			OnSize();
			InvalidateRect(NULL, TRUE);
		}
	}
#endif
#endif
	return S_OK;
}

#endif

#endif