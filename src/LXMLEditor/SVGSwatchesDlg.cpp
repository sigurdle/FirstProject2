// SVGSwatchesDlg.cpp : Implementation of CSVGSwatchesDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGSwatchesDlg.h"

#include "EXMLDocument.h"	// TODO, remove
#include "EXMLViewGroup.h"	// TODO, remove

#include "LXMLEditorApp.h"	// TODO, remove
//#include "WebEditorFrame.h"	// TODO, remove

#include "WEUndoNewElement.h"
#include "UndoParent.h"

#if 0

BOOL ElementCanHavePaint(ILDOMElement* element)
{
	{
		CComQIPtr<ILSVGStopElement> e = element;
		if (e) return FALSE;
	}

	{
		CComQIPtr<ILSVGGradientElement> e = element;
		if (e) return FALSE;
	}

	{
		CComQIPtr<ILSVGFilterElement> e = element;
		if (e) return FALSE;
	}

	{
		CComQIPtr<ILSVGFilterPrimitiveStandardAttributes> e = element;
		if (e) return FALSE;
	}

	/*
	{
		CComQIPtr<ILSVGAnimation> e = element;
		if (e) return FALSE;
	}
	*/

	return TRUE;
}

BOOL SelectionCanHavePaint(IEXMLViewGroup* viewGroup)
{
	long nselected;
	viewGroup->GetSelectedCount(&nselected);

	for (int i = 0; i < nselected; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> element;
		eElement->get_domElement(&element);


		BOOL bCan = ElementCanHavePaint(element);
		if (!bCan) return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSVGSwatchesDlg

int CSVGSwatchesDlg::FinalConstruct()
{
	return 0;
}

LRESULT CSVGSwatchesDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (CSVGDefinitionsDlgT<CSVGSwatchesDlg>::OnCreate(uMsg, wParam, lParam, bHandled) != 0)
		return -1;

	::RegisterDragDrop(m_hWnd, this);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);
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

		OnSelectionStyleChanged();
	}

	return 0;
}

LRESULT CSVGSwatchesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
	eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
	RemoveEventListeners();

	m_listView.RemoveItems();

	m_listView.m_xmlDocument.Release();

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

	::RevokeDragDrop(m_hWnd);

	CSVGDefinitionsDlgT<CSVGSwatchesDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);

	return 0;
}

LRESULT CSVGSwatchesDlg::OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup)
	{
		//CComPtr<IWebXMLViewGroup> viewGroup;
		//m_document->GetActiveViewGroup(&viewGroup);
		//if (viewGroup)
		{
			if (SelectionCanHavePaint(m_viewGroup))
			{
				_bstr_t propertyName = (static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_strokeOrFill==0)? L"stroke": L"fill";

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
								CComBSTR id;
								((ILDOMElement*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element)->getAttribute(L"id", &id);

								paint = L"url(#";
								paint += id;
								paint += L")";
							}
							else
							{
								paint = L"none";
							}

							style->setProperty(propertyName, paint, NULL);
						}
					}
					else
					{
						style->removeProperty(propertyName, NULL);
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

LRESULT CSVGSwatchesDlg::OnDblClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

			ASSERT(0);
#if 0
			{
				CComPtr<IUIDlgSite> dlgsite;
				m_viewGroup->m_views[14]->GetDlgSite(&dlgsite);
				dlgsite->Show(TRUE);

				// Activate the dialogs frame
				HWND hwnd;
				m_viewGroup->m_views[14]->get_hwnd(&hwnd);
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

	return 0;
}

void __stdcall CSVGSwatchesDlg::OnSelectionStyleChanged()
{
	ASSERT(m_viewGroup);

	m_listView.DeselectAll();

#if 0
	ASSERT(0);
#endif

#if 0
	CComPtr<ILCSSStyleDeclaration> style;
	m_viewGroup->GetCurrentSelectionCSSStyle(&style);

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
#endif
}

// IDropTarget
STDMETHODIMP CSVGSwatchesDlg::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	return S_OK;
}

STDMETHODIMP CSVGSwatchesDlg::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CSVGSwatchesDlg::DragLeave()
{
	return S_OK;
}

STDMETHODIMP CSVGSwatchesDlg::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
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

	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> eXMLDocument;
		m_viewGroup->get_eXMLDocument(&eXMLDocument);

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
				CComQIPtr<IEDocument> eDocument = eXMLDocument;

				IUndoManager* undoManager;
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
						CComPtr<ILDOMElement> documentElement;
						svgdocument->get_documentElement(&documentElement);

						CComPtr<ILDOMNode> node;
						documentElement->get_firstChild(&node);
						while (node)
						{
							CComPtr<ILDOMNode> nextSibling;
							node->get_nextSibling(&nextSibling);

							CComQIPtr<ILSVGGradientElement> svgGradientElement = node;
							if (svgGradientElement)
							{
								m_listView.m_xmlDocument->adoptNode(svgGradientElement, NULL);

								CComObject<CWEUndoNewElement>* pUndo;
								CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
								if (pUndo)
								{
								//	pUndo->AddRef();
									pUndo->m_pDocument = static_cast<CEXMLDocument*>(eXMLDocument.p);

									pUndo->DoInitial(undoManager, svgGradientElement, svgDefsElement, NULL);
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
	}
#endif

	return S_OK;
}

#if 0
// IUIEventHandler
STDMETHODIMP CSVGSwatchesDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
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

//			IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}
		*/

		m_viewGroup = viewGroup;

		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		m_listView.m_xmlDocument.Release();
		edocument->get_DOMDocument(&m_listView.m_xmlDocument);

//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_document);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();

		OnSelectionStyleChanged();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSVGSwatchesDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(IsUnknownEqualUnknown(m_viewGroup, object));

//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);

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
STDMETHODIMP CSVGSwatchesDlg::handleEvent(ILDOMEvent* evt)
{
	BSTR btype;
	evt->get_type(&btype);
	_bstr_t type = _bstr_t(btype, false);

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
	else// if (!wcscmp(type, L"DOMAttrModified") ||
			//	!wcscmp(type, L"DOMCharacterDataModified"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		for (int i = 0; i < m_listView.m_items.GetSize(); i++)
		{
			if ((ILDOMElement*)m_listView.m_items[i]->m_element == node)
			{
				if (m_listView.m_items[i]->m_thumbnailBitmap)
				{
					DeleteObject(m_listView.m_items[i]->m_thumbnailBitmap);
					m_listView.m_items[i]->m_thumbnailBitmap = NULL;
					m_listView.m_items[i]->m_thumbnailBits = NULL;
				}

				if (m_listView.m_hWnd)
				{
					m_listView.Invalidate();
				}

				break;
			}
		}
	}

	return S_OK;
}

void CSVGSwatchesDlg::BuildItems()
{
	m_listView.RemoveItems();

	m_listView.AddItem(NULL, L"[none]");
	m_listView.AddItem(NULL, L"[inherit]");
	AddItems();
}

void CSVGSwatchesDlg::AddEventListeners()
{
	for (int i = 0; i < m_listView.m_items.GetSize(); i++)
	{
		if (m_listView.m_items[i]->m_element)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = (ILDOMElement*)m_listView.m_items[i]->m_element;

			eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);

		//
			eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_FALSE);
		// Capture as well
			eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
		}
	}
}

void CSVGSwatchesDlg::RemoveEventListeners()
{
	for (int i = 0; i < m_listView.m_items.GetSize(); i++)
	{
		if (m_listView.m_items[i]->m_element)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = (ILDOMElement*)m_listView.m_items[i]->m_element;

			eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);

		//
			eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_FALSE);
		// Capture as well
			eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
		}
	}
}

//////////////////////////////////

BOOL IsPaintUsed(ILDOMElement* element, BSTR paintId)
{
	CComQIPtr<ILElementCSSInlineStyle> stylable = element;
	if (stylable)
	{
		CComPtr<ILCSSStyleDeclaration> style;
		stylable->get_style(&style);

		CComPtr<ILSVGPaint> stroke;
		style->getPropertyCSSValue(L"stroke", (ILCSSValue**)&stroke);

		if (stroke)
		{
			LSVGPaintType paintType;
			stroke->get_paintType(&paintType);

			if (paintType == SVG_PAINTTYPE_URI_NONE ||
				paintType == SVG_PAINTTYPE_URI_CURRENTCOLOR ||
				paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||
				paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
			{
				BSTR burl;
				stroke->get_uri(&burl);
				_bstr_t url = _bstr_t(burl, false);

				if (((BSTR)url)[0] == L'#')
				{
					BSTR uri = ((BSTR)url)+1;

					if (!wcscmp(uri, paintId))
						return TRUE;
				}
			}
		}

		CComPtr<ILSVGPaint> fill;
		style->getPropertyCSSValue(L"fill", (ILCSSValue**)&fill);

		if (fill)
		{
			LSVGPaintType paintType;
			fill->get_paintType(&paintType);

			if (paintType == SVG_PAINTTYPE_URI_NONE ||
				paintType == SVG_PAINTTYPE_URI_CURRENTCOLOR ||
				paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||
				paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
			{
				BSTR burl;
				fill->get_uri(&burl);
				_bstr_t url = _bstr_t(burl, false);

				if (((BSTR)url)[0] == L'#')
				{
					BSTR uri = ((BSTR)url)+1;

					if (!wcscmp(uri, paintId))
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
			BOOL bUsed = IsPaintUsed(childElement, paintId);
			if (bUsed)
				return bUsed;
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return FALSE;
}

BEGIN_CMD_MAP(CSVGSwatchesDlg)
	CMD_HANDLER(ID_SVGSWATCHES_NEWSOLIDCOLOR, OnSwatchesNewSolidColor)
	CMD_HANDLER(ID_SVGSWATCHES_NEWLINEARGRADIENT, OnSwatchesNewLinearGradient)
	CMD_HANDLER(ID_SVGSWATCHES_DEFINEPATTERN, OnSwatchesDefinePattern)
	CMD_HANDLER(ID_SVGSWATCHES_DELETESWATCH, OnSwatchesDeleteSwatch)
	CMD_HANDLER(ID_FILTERS_SELECTALLUNUSED, OnSelectAllUnused)

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

LRESULT CSVGSwatchesDlg::OnSwatchesNewSolidColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup)
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
					CComPtr<ILSVGElement> svgElement;
					document->createElementNS(L"http://www.w3.org/2000/svg", L"solidColor", (ILDOMElement**)&svgElement);

					if (svgElement)
					{
						svgElement->setAttribute(L"id", dlg.m_id);

					//	CComPtr<IOleUndoManager> undoManager;
					//	m_document->get_undoManager(&undoManager);

						CComBSTR styleValue;
						styleValue += L"solid-color:";
						styleValue += static_cast<CEXMLDocument*>(eXMLDocument.p)->m_lastColor;
						styleValue += L";";

						svgElement->setAttribute(L"style", styleValue);

						CComObject<CWEUndoNewElement>* pUndo;
						CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
						if (pUndo)
						{
						//	pUndo->AddRef();
							pUndo->m_pDocument = static_cast<CEXMLDocument*>(eXMLDocument.p);

							pUndo->DoInitial(undoManager, svgElement, svgDefsElement, NULL);

							// TODO: do this here?
							//CComPtr<IWebXMLViewGroup> viewGroup;
							//m_document->GetActiveViewGroup(&viewGroup);
							//if (viewGroup)
							{
								CEXMLViewGroup* pViewGroup = m_viewGroup;

	//							CElementImpl* pElement = ((CEXMLDocument*)m_document.p)->m_pTree->FindDOMElement(svgFilterElement);
								CComPtr<IEElement> eElement;
								eXMLDocument->GetEElementFromDOMElement(svgElement, &eElement);

								{
									pViewGroup->m_colorEditing = L"solid-color";

									pViewGroup->SetCurrentSelectionColor();
									pViewGroup->Fire_ColorChanged();
								}

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

LRESULT CSVGSwatchesDlg::OnSwatchesNewLinearGradient(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup)
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
					CComPtr<ILSVGElement> svgElement;
					document->createElementNS(L"http://www.w3.org/2000/svg", L"linearGradient", (ILDOMElement**)&svgElement);

					if (svgElement)
					{
						svgElement->setAttribute(L"id", dlg.m_id);
						svgElement->setAttribute(L"gradientUnits", L"userSpaceOnUse");

						// black
						{
							CComPtr<ILDOMElement> stop;
							document->createElementNS(L"http://www.w3.org/2000/svg", L"stop", &stop);
							stop->setAttribute(L"offset", L"0");
							stop->setAttribute(L"style", L"stop-color:#ff0000");

							svgElement->appendChild(stop, NULL);
						}

						// white
						{
							CComPtr<ILDOMElement> stop;
							document->createElementNS(L"http://www.w3.org/2000/svg", L"stop", &stop);
							stop->setAttribute(L"offset", L"1");
							stop->setAttribute(L"style", L"stop-color:#ffff00");

							svgElement->appendChild(stop, NULL);
						}

					//	CComPtr<IOleUndoManager> undoManager;
					//	m_document->get_undoManager(&undoManager);

						CComObject<CWEUndoNewElement>* pUndo;
						CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
						if (pUndo)
						{
						//	pUndo->AddRef();
							pUndo->m_pDocument = static_cast<CEXMLDocument*>(eXMLDocument.p);

							pUndo->DoInitial(undoManager, svgElement, svgDefsElement, NULL);

							// TODO: do this here?
						//	CComPtr<IWebXMLViewGroup> viewGroup;
						//	m_document->GetActiveViewGroup(&viewGroup);
						//	if (viewGroup)
							{
								CEXMLViewGroup* pViewGroup = m_viewGroup;

	//							CElementImpl* pElement = ((CEXMLDocument*)m_document.p)->m_pTree->FindDOMElement(svgFilterElement);
								CComPtr<IEElement> eElement;
								eXMLDocument->GetEElementFromDOMElement(svgElement, &eElement);

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

LRESULT CSVGSwatchesDlg::OnSwatchesDefinePattern(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
				document->createElementNS(L"http://www.w3.org/2000/svg", L"pattern", (ILDOMElement**)&svgFilterElement);

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

						WCHAR buf[256];

						swprintf(buf, L"%g", maxx-minx);
						svgFilterElement->setAttribute(L"width", buf);

						swprintf(buf, L"%g", maxy-miny);
						svgFilterElement->setAttribute(L"height", buf);

						swprintf(buf, L"%g %g %g %g", minx, miny, maxx-minx, maxy-miny);
						svgFilterElement->setAttribute(L"viewBox", buf);
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

LRESULT CSVGSwatchesDlg::OnSwatchesDeleteSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

				BOOL bUsed = IsPaintUsed(documentElement, id);
				if (bUsed)
				{
					UINT nID = MessageBox("Some of the swatches are in use, Delete anyway?", "WebEditor", MB_YESNO);
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

LRESULT CSVGSwatchesDlg::OnSelectAllUnused(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
			BOOL bUsed = IsPaintUsed(documentElement, id);

			if (!bUsed)
			{
				m_listView.SelectItem(i);
			}
		}
	}

	return 0;
}

#endif