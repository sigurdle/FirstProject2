// SVGMasksDlg.cpp : Implementation of CSVGMasksDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGMasksDlg.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CSVGMasksDlg

int CSVGMasksDlg::FinalConstruct()
{
	return 0;
}

LRESULT CSVGMasksDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (CSVGDefinitionsDlgT<CSVGMasksDlg>::OnCreate(uMsg, wParam, lParam, bHandled) != 0)
		return -1;

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

//	::RegisterDragDrop(m_hWnd, this);

	return 0;
}

LRESULT CSVGMasksDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	::RevokeDragDrop(m_hWnd);

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	CSVGDefinitionsDlgT<CSVGMasksDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);

	return 0;
}

LRESULT CSVGMasksDlg::OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_document)
	{
		if (m_listView.m_selectedItemIndex >= 0 && m_listView.m_selectedItemIndex < m_listView.m_items.GetSize())
		{
			_bstr_t mask;

			if (m_listView.m_items[m_listView.m_selectedItemIndex]->m_element)
			{
				sysstring id = ((LXML::Element*)m_listView.m_items[m_listView.m_selectedItemIndex]->m_element)->getAttribute(L"id");

				mask = L"url(#" + _bstr_t(id) + L")";
			}
			else
			{
				mask = L"none";
			}

			CComPtr<IEXMLViewGroup> viewGroup;
			m_document->GetActiveViewGroup(&viewGroup);
			if (viewGroup)
			{
				ASSERT(0);
#if 0
				CComPtr<ILCSSStyleDeclaration> style;
				viewGroup->GetCurrentSelectionCSSStyle(&style);

				style->setProperty(L"mask", mask, NULL);

				viewGroup->ApplyCurrentSelectionCSSStyle();
#endif
			}
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

void CSVGMasksDlg::BuildItems()
{
	m_listView.RemoveItems();

	m_listView.AddItem(NULL, L"[none]");
	AddItems();
}

void CSVGMasksDlg::AddEventListeners()
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

void CSVGMasksDlg::RemoveEventListeners()
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

// IUIEventHandler
STDMETHODIMP CSVGMasksDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLDocument> document = object;
	if (document)
	{
		if (m_document != NULL)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
			eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

//			IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}

		m_document = document;

		m_listView.m_xmlDocument.Release();
		m_document->get_DOMDocument(&m_listView.m_xmlDocument);

//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
		eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);

		BuildItems();
		AddEventListeners();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSVGMasksDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(IsUnknownEqualUnknown(m_document, object));

//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_xmlDocument;
	eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
	RemoveEventListeners();

	m_listView.RemoveItems();

	m_listView.m_xmlDocument.Release();
	m_document.Release();

	return S_OK;
}

// ILDOMEventListener
STDMETHODIMP CSVGMasksDlg::handleEvent(ILDOMEvent* evt)
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

BEGIN_CMD_MAP(CSVGMasksDlg)
/*
	CMD_HANDLER(ID_SVGSWATCHES_NEWSOLIDCOLOR, OnSwatchesNewSolidColor)
	CMD_HANDLER(ID_SVGSWATCHES_NEWLINEARGRADIENT, OnSwatchesNewLinearGradient)

	CMD_HANDLER(ID_SVGSWATCHES_DELETESWATCH, OnSwatchesDeleteSwatch)

	CMD_HANDLER(ID_FILTERS_SELECTALLUNUSED, OnSelectAllUnused)
*/
	CMD_HANDLER(ID_SVGLIST_SMALLTHUMBNAILS, OnListSmallThumbnails)
	CMD_HANDLER(ID_SVGLIST_LARGETHUMBNAILS, OnListLargeThumbnails)
	CMD_HANDLER(ID_SVGLIST_SMALLLISTVIEW, OnListSmallListView)
	CMD_HANDLER(ID_SVGLIST_LARGELISTVIEW, OnListLargeListView)
	CMD_UPDATE(ID_SVGLIST_SMALLTHUMBNAILS, OnListSmallThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGETHUMBNAILS, OnListLargeThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_SMALLLISTVIEW, OnListSmallListViewUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGELISTVIEW, OnListLargeListViewUpdate)
END_CMD_MAP()

#endif