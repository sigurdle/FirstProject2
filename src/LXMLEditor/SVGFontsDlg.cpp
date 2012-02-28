// SVGFontsDlg.cpp : Implementation of CSVGFontsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGFontsDlg.h"

#include "EXMLDocument.h"	// TODO, remove
#include "EXMLViewGroup.h"	// TODO, remove

#include "WEUndoNewElement.h"
#include "UndoParent.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CSVGFontsDlg

int CSVGFontsDlg::FinalConstruct()
{
	HRESULT hr;

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->FindMenu(IDR_SVGFONTSDLG, &m_menu);

	/*
	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);
	*/

	return 0;
}

LRESULT CSVGFontsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	if (CSVGFiltersDlgT<CSVGFiltersDlg>::OnCreate(uMsg, wParam, lParam, bHandled) != 0)
		return -1;
*/
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

//	::RegisterDragDrop(m_hWnd, this);

	return 0;
}

LRESULT CSVGFontsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	::RevokeDragDrop(m_hWnd);

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

//	CSVGFiltersDlgT<CSVGFiltersDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);

	return 0;
}

// IUIEventHandler
STDMETHODIMP CSVGFontsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLDocument> document = object;
	if (document)
	{
		if (m_document != NULL)
		{
			/*
			CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
			eventTarget->removeEventListener(L"DOMNodeInserted", this, VARIANT_TRUE);
			*/

//			IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}

		m_document = document;

		/*
		m_listView.m_xmlDocument.Release();
		m_document->get_DOMDocument(&m_listView.m_xmlDocument);
		*/

//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);

		/*
		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();
		*/
	}

	return S_OK;
}

STDMETHODIMP CSVGFontsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(IsUnknownEqualUnknown(m_document, object));

//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	/*
	CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
	eventTarget->removeEventListener(L"DOMNodeInserted", this, VARIANT_TRUE);
	RemoveEventListeners();

	m_listView.RemoveItems();

	m_listView.m_xmlDocument.Release();
	*/
	m_document.Release();

	return S_OK;
}

BEGIN_CMD_MAP(CSVGFontsDlg)
	CMD_HANDLER(ID_SVGFONTS_NEWFONT, OnFontNewFont)
END_CMD_MAP()

#include "SVGFilterOptionsDlg.h"

LRESULT CSVGFontsDlg::OnFontNewFont(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_document)
	{
		CComQIPtr<IEDocument> eDocument = m_document;

		CComPtr<ILDOMDocument> document;
		m_document->get_DOMDocument(&document);

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
				m_document->FindOrCreateSVGDefs(&svgDefsElement);

				if (svgDefsElement)
				{
					CComPtr<ILSVGFilterElement> svgElement;
					document->createElementNS(L"http://www.w3.org/2000/svg", L"font", (ILDOMElement**)&svgElement);

					if (svgElement)
					{
						svgElement->setAttribute(L"id", dlg.m_id);

						CComObject<CWEUndoNewElement>* pUndo;
						CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
						if (pUndo)
						{
						//	pUndo->AddRef();
							pUndo->m_pDocument = static_cast<CEXMLDocument*>(m_document.p);

							pUndo->DoInitial(undoManager, svgElement, svgDefsElement, NULL);

							// TODO: do this here?
							CComPtr<IEXMLViewGroup> viewGroup;
							m_document->GetActiveViewGroup(&viewGroup);
							if (viewGroup)
							{
								CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(viewGroup.p);

	//							CElementImpl* pElement = ((CEXMLDocument*)m_document.p)->m_pTree->FindDOMElement(svgFilterElement);
								CComPtr<IEElement> pElement;
								m_document->GetEElementFromDOMElement(svgElement, &pElement);

								pViewGroup->ActivateElement(pElement, 0, NULL);
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