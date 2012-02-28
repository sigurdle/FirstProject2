// SVGClipPathsDlg.cpp : Implementation of CSVGClipPathsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGClipPathsDlg.h"

#include "EXMLDocument.h"	// TODO, remove
#include "EXMLViewGroup.h"	// TODO, remove

#include "WEUndoNewElement.h"
#include "UndoParent.h"

#if 0
bool SelectionCanHavePaint(IEXMLViewGroup* viewGroup);

/////////////////////////////////////////////////////////////////////////////
// CSVGClipPathsDlg

LRESULT CSVGClipPathsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (CSVGDefinitionsDlgT<CSVGClipPathsDlg>::OnCreate(uMsg, wParam, lParam, bHandled) != 0)
		return -1;

	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		m_listView.m_xmlDocument.Release();
		edocument->get_DOMDocument(&m_listView.m_xmlDocument);

#if 0
		IDispEventImpl<1, CSVGFiltersDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);
#endif
	//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(edocument);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();

#if 0
		OnSelectionStyleChanged();
#endif
	}

	return 0;
}

LRESULT CSVGClipPathsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CSVGDefinitionsDlgT<CSVGClipPathsDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);
	return 0;
}

LRESULT CSVGClipPathsDlg::OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup)
	{
		//CComPtr<IWebXMLViewGroup> viewGroup;
		//m_document->GetActiveViewGroup(&viewGroup);
		//if (viewGroup)
		{
			if (SelectionCanHavePaint(m_viewGroup))
			{
				//_bstr_t propertyName = (static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_strokeOrFill==0)? L"stroke": L"fill";

				if (m_listView.m_selectedItemIndex >= 0 && m_listView.m_selectedItemIndex < m_listView.m_items.GetSize())
				{
					CComPtr<ILCSSStyleDeclaration> style;
					m_viewGroup->GetCurrentSelectionCSSStyle(&style);

					if (m_listView.m_items[m_listView.m_selectedItemIndex]->m_element ||
						wcscmp(m_listView.m_items[m_listView.m_selectedItemIndex]->m_name, L"[inherit]"))
					{
						if (SelectionCanHavePaint(m_viewGroup))
						{
							CComBSTR paint;

							if (m_listView.m_items[m_listView.m_selectedItemIndex]->m_element)
							{
								sysstring id = ((LXML::Element*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element)->getAttribute(L"id");

								paint = L"url(#";
								paint += id;
								paint += L")";
							}
							else
							{
								paint = L"none";
							}

							style->setProperty(L"clip-path", paint, NULL);
						}
					}
					else
					{
						style->removeProperty(L"clip-path", NULL);
					}

					m_viewGroup->ApplyCurrentSelectionCSSStyle();

					/*
					((CEXMLDocument*)m_document.p)->m_defaultGradient = paint;
					((CEXMLDocument*)m_document.p)->m_defaultStyle->setProperty(propertyName, paint, NULL);
					*/
				}
				else
				{
				}
			}
		}
	}

	return 0;
}

LRESULT CSVGClipPathsDlg::OnDblClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_listView.m_selectedItemIndex >= 0)
	{
	//	CComPtr<IWebXMLViewGroup> viewGroup;
	//	m_document->GetActiveViewGroup(&viewGroup);
		if (m_viewGroup)
		{
			CComPtr<IEXMLDocument> edocument;
			m_viewGroup->get_eXMLDocument(&edocument);

			CEXMLViewGroup* pViewGroup = m_viewGroup;

			CComPtr<IEElement> eElement;
			edocument->GetEElementFromDOMElement((ILDOMElement*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element, &eElement);

			pViewGroup->m_activeReferencedElement = eElement;	// ??? reference element is still NULL
			m_viewGroup->ActivateElement(eElement, 0, NULL);
		}
	}

	return 0;
}

void CSVGClipPathsDlg::BuildItems()
{
	m_listView.RemoveItems();
	AddItems();
}

void CSVGClipPathsDlg::AddEventListeners()
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

void CSVGClipPathsDlg::RemoveEventListeners()
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

#if 0
// IUIEventHandler
STDMETHODIMP CSVGClipPathsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLDocument> document = object;
	if (document)
	{
		if (m_document != NULL)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
			eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

//			IDispEventImpl<2, CSVGClipPathsDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}

		m_document = document;

		m_listView.m_xmlDocument.Release();
		m_document->get_DOMDocument(&m_listView.m_xmlDocument);

//		IDispEventImpl<2, CSVGFiltersDlg, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSVGClipPathsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(IsUnknownEqualUnknown(m_document, object));

//	IDispEventImpl<2, CSVGClipPathsDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
	eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
	RemoveEventListeners();

	m_listView.RemoveItems();

	m_listView.m_xmlDocument.Release();
	m_document.Release();

	return S_OK;
}
#endif

// ILDOMEventListener
STDMETHODIMP CSVGClipPathsDlg::handleEvent(ILDOMEvent* evt)
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

BEGIN_CMD_MAP(CSVGClipPathsDlg)
//	CMD_HANDLER(ID_SVGSWATCHES_NEWSOLIDCOLOR, OnSwatchesNewSolidColor)
//	CMD_HANDLER(ID_SVGSWATCHES_NEWLINEARGRADIENT, OnSwatchesNewLinearGradient)
	CMD_HANDLER(ID_SVGCLIPPATHS_DEFINECLIPPATH, OnClipPathsDefinePattern)
//	CMD_HANDLER(ID_SVGSWATCHES_DELETESWATCH, OnSwatchesDeleteSwatch)
//	CMD_HANDLER(ID_FILTERS_SELECTALLUNUSED, OnSelectAllUnused)

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

LRESULT CSVGClipPathsDlg::OnClipPathsDefinePattern(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
				CComPtr<ILSVGClipPathElement> svgFilterElement;
				document->createElementNS(L"http://www.w3.org/2000/svg", L"clipPath", (ILDOMElement**)&svgFilterElement);

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

						/*
						WCHAR buf[256];

						swprintf(buf, L"%g", maxx-minx);
						svgFilterElement->setAttribute(L"width", buf);

						swprintf(buf, L"%g", maxy-miny);
						svgFilterElement->setAttribute(L"height", buf);

						swprintf(buf, L"%g %g %g %g", minx, miny, maxx-minx, maxy-miny);
						svgFilterElement->setAttribute(L"viewBox", buf);
						*/
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

#endif