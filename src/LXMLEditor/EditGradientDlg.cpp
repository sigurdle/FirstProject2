// EditGradientDlg.cpp : Implementation of CEditGradientDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EditGradientDlg.h"

#include "EElement.h"
#include "EXMLDocument.h"
#include "EXMLViewGroup.h"	// TODO, remove

#if 0

/////////////////////////////////////////////////////////////////////////////
// CEditGradientDlg

LRESULT CEditGradientDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	GetDlgControl(IDC_SVGGRADIENT, IID_ISVGGradientEditCtl, (void**)&m_GradCtl);
	/*
	m_axGradCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axGradCtl.AttachControl(m_GradCtl, &p);
	*/

	m_GradCtl->put_BackColor(GetSysColor(COLOR_BTNFACE));

	SendDlgItemMessage(IDC_GRADIENT_TYPE, CB_ADDSTRING, 0, (LPARAM)_T("Linear"));
	SendDlgItemMessage(IDC_GRADIENT_TYPE, CB_ADDSTRING, 0, (LPARAM)_T("Radial"));

	IDispEventImpl<3, CEditGradientDlg, &DIID__ISVGGradientEditCtlEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_GradCtl);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);

	IDispEventImpl<1, CEditGradientDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());

	OnViewGroupSelectionChanged();

	return 0;
}

LRESULT CEditGradientDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

	IDispEventImpl<1, CEditGradientDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());

	IDispEventImpl<3, CEditGradientDlg, &DIID__ISVGGradientEditCtlEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_GradCtl);

	return 0;
}

LRESULT CEditGradientDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

//	m_axGradCtl.MoveWindow(0, 20, client.right, client.bottom-20);

	InvalidateRect(NULL, TRUE);

	return 0;
}

LRESULT CEditGradientDlg::OnGradientType(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = SendDlgItemMessage(IDC_GRADIENT_TYPE, CB_GETCURSEL, 0, 0);

	CComPtr<ILDOMDocument> ownerDocument;
	m_gradient->get_ownerDocument(&ownerDocument);

	CComPtr<ILDOMNode> node;

	if (index == 0)
	{
		ownerDocument->renameNode(m_gradient, L"http://www.w3.org/2000/svg", L"linearGradient", &node);
	}
	else if (index == 1)
	{
		ownerDocument->renameNode(m_gradient, L"http://www.w3.org/2000/svg", L"radialGradient", &node);
	}

//	m_pDocument->ActivateElement(
//	m_gradient

	return 0;
}

#include "WEUndoNewElement.h"
#include "UndoParent.h"

BOOL SelectionCanHavePaint(IEXMLViewGroup* viewGroup);

LRESULT CEditGradientDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
// Create default gradient
	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> eXMLDocument;
		m_viewGroup->get_eXMLDocument(&eXMLDocument);

		CComQIPtr<IEDocument> eDocument = eXMLDocument;

		CComPtr<ILDOMDocument> document;
		eXMLDocument->get_DOMDocument(&document);

//		CSVGFilterOptionsDlg dlg;
//		dlg.m_document = document;

//		if (dlg.DoModal(GetMainHwnd()) == IDOK)
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
					CComPtr<ILSVGElement> svgElement;
					document->createElementNS(L"http://www.w3.org/2000/svg", L"linearGradient", (ILDOMElement**)&svgElement);

					if (svgElement)
					{
						// TODO, create unique ID

						CComBSTR id = L"gradient";

						svgElement->setAttribute(L"id", id);
						svgElement->setAttribute(L"gradientUnits", L"userSpaceOnUse");
						svgElement->setAttribute(L"x1", L"0%");
						svgElement->setAttribute(L"y1", L"0%");
						svgElement->setAttribute(L"x2", L"100%");
						svgElement->setAttribute(L"y2", L"0%");

						// black
						{
							CComPtr<ILDOMElement> stop;
							document->createElementNS(L"http://www.w3.org/2000/svg", L"stop", &stop);
							stop->setAttribute(L"offset", L"0");
							stop->setAttribute(L"style", L"stop-color:#000000");

							svgElement->appendChild(stop, NULL);
						}

						// white
						{
							CComPtr<ILDOMElement> stop;
							document->createElementNS(L"http://www.w3.org/2000/svg", L"stop", &stop);
							stop->setAttribute(L"offset", L"1");
							stop->setAttribute(L"style", L"stop-color:#ffffff");

							svgElement->appendChild(stop, NULL);
						}

						CComObject<CWEUndoNewElement>* pUndo;
						CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
						if (pUndo)
						{
						//	pUndo->AddRef();
							pUndo->m_pDocument = static_cast<CEXMLDocument*>(eXMLDocument.p);

							pUndo->DoInitial(undoManager, svgElement, svgDefsElement, NULL);

							// TODO: do this here?
							CComPtr<IEXMLViewGroup> viewGroup;
							eXMLDocument->GetActiveViewGroup(&viewGroup);
							if (viewGroup)
							{
								//CWebXMLViewGroup* pViewGroup = static_cast<CWebXMLViewGroup*>(viewGroup.p);

								CComPtr<IEElement> pElement;
								eXMLDocument->GetEElementFromDOMElement(svgElement, &pElement);

								CComBSTR gradient;
								gradient = L"url(#";
								gradient += id;
								gradient += L")";

								if (SelectionCanHavePaint(viewGroup))
								{
#if 0
									CComPtr<ILCSSStyleDeclaration> style;
									viewGroup->GetCurrentSelectionCSSStyle(&style);
#endif

									ATLASSERT(0);
#if 0
									style->setProperty(gApp->m_strokeOrFill == 0? L"stroke": L"fill", gradient, NULL);
#endif

#if 0
									viewGroup->ApplyCurrentSelectionCSSStyle();
#endif
								}

							//
								static_cast<CEXMLDocument*>(eXMLDocument.p)->m_lastGradient = gradient;
							//

								viewGroup->ActivateElement(pElement, 0, NULL);
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

void __stdcall CEditGradientDlg::OnViewGroupSelectionChanged()
{
	/*
	CComPtr<IWebXMLDocument> eDocument;
	m_viewGroup->get_document(&eDocument);

	_bstr_t defaultGradient = static_cast<CEXMLDocument*>(eDocument.p)->m_defaultGradient;
	if (defaultGradient.length() && wcscmp(defaultGradient, L"none"))
	{
		_bstr_t url = ExtractUrl(defaultGradient);

		BSTR uri = &((BSTR)url)[1];

		CComPtr<ILDOMDocument> xmldocument;
		eDocument->get_DOMDocument(&xmldocument);

		CComPtr<ILDOMElement> uriElement;
		xmldocument->getElementById(uri, &uriElement);
		if (uriElement)
		{
			// TODO check if linearGradient or radialGradient

			m_GradCtl->SetSVGElement(uriElement);

			{
				CComPtr<ILCSSStyleDeclaration> style;
				m_viewGroup->GetCurrentSelectionCSSStyle(&style);

				CComPtr<ILSVGPaint> paint;
				style->getPropertyCSSValue((gApp->m_strokeOrFill==0)? L"stroke": L"fill", (ILCSSValue**)&paint);

				if (paint)
				{
					CComBSTR cssTextPaint;
					paint->get_cssText(&cssTextPaint);

					if (!wcscmp(defaultGradient, cssTextPaint))
					{
						m_GradCtl->put_canEditStops(VARIANT_TRUE);
					}
					else
					{
						m_GradCtl->put_canEditStops(VARIANT_FALSE);
					}
				}
				else
				{
					m_GradCtl->put_canEditStops(VARIANT_FALSE);
				}
			}
		}
		else
		{
			m_GradCtl->SetSVGElement(NULL);
		}
	}
	*/

	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);
	if (selectedElement)
	{
		CComPtr<IEElement> element;
		selectedElement->get_eElement(&element);

		CComPtr<ILDOMElement> domElement;
		element->get_domElement(&domElement);

		m_GradCtl->SetSVGElement(domElement);
	}
}

void __stdcall CEditGradientDlg::OnEndDragStopElement(ILSVGStopElement* stopElement)
{
	CComPtr<IEXMLDocument> eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<IEElement> eElement;
	eDocument->GetEElementFromDOMElement(stopElement, &eElement);

	m_viewGroup->m_colorEditing = L"stop-color";

	m_viewGroup->ActivateElement(eElement, 0, NULL);
}

#if 0
// IUIEventHandler
STDMETHODIMP CEditGradientDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		ATLASSERT(m_viewGroup == NULL);
		m_viewGroup = viewGroup;

		IDispEventImpl<1, CEditGradientDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		OnViewGroupSelectionChanged();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CEditGradientDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(m_viewGroup != NULL);

	IDispEventImpl<1, CEditGradientDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();

	m_GradCtl->SetSVGElement(NULL);

	return S_OK;
}
#endif

HRESULT __stdcall CEditGradientDlg::OnDOMEvent(ILDOMEvent* evt)
{
	if (m_pElement)
	{
		/*
		PrepareRange();

		HWND hwnd;
		get_hwnd(&hwnd);
		if (hwnd)
		{
			InvalidateRect(NULL, TRUE);
		}
		*/
	}

	return S_OK;
}

#endif
