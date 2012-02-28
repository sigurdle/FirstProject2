// EditFilterDlg.cpp : Implementation of CEditFilterDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "EditFilterDlg.h"

#if 0

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

//extern CWebEditorApp* gApp;

//#include "Element.h"
//#include "FilterElement.h"

/////////////////////////////////////////////////////////////////////////////
// CEditFilterDlg

int CEditFilterDlg::FinalConstruct()
{
	HRESULT hr;

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->FindMenu(IDR_EDITFILTERDLG, &m_menu);

	hr = m_editGraph.CoCreateInstance(CLSID_EditFilterGraph);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CEditFilterDlg::FinalRelease()
{
	m_editGraph.Release();
}

LRESULT CEditFilterDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IUnknown* p;

	CRect rc(0,0,0,0);

	m_axeditGraph.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axeditGraph.AttachControl(m_editGraph, &p);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);
	IDispEventImpl<1, CEditFilterDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

	OnViewGroupSelectionChanged();

	return 0;
}

LRESULT CEditFilterDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);
	IDispEventImpl<1, CEditFilterDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

	return 0;
}

long CEditFilterDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axeditGraph.MoveWindow(0, 0, client.right, client.bottom);

	return 0;
}

void __stdcall CEditFilterDlg::OnViewGroupSelectionChanged()
{
	m_pElement = NULL;
	IESVGFilterElement* pFilterElement = NULL;

	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);
	if (selectedElement)
	{
		CComPtr<IEElement> element;
		selectedElement->get_eElement(&element);

	// Check if there's a filter as parent
		CComPtr<IEElement> node = element;
		do
		{
			CComQIPtr<IESVGFilterElement> svgfilterElement = node;
			if (svgfilterElement)
			{
				pFilterElement = svgfilterElement;
				break;
			}

			CComPtr<IEElement> parentNode;
			node->get_parentNode(&parentNode);
			node = parentNode;
		}
		while (node != NULL);

		if (pFilterElement)
		{
			m_pElement = element;
		}
	}

	m_editGraph->put_activeElement(pFilterElement);
}

#if 0
STDMETHODIMP CEditFilterDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;

	if (viewGroup)
	{
		ASSERT(m_viewGroup == NULL);
		m_viewGroup = viewGroup;

		IDispEventImpl<1, CEditFilterDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		OnViewGroupSelectionChanged();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CEditFilterDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(m_viewGroup);
	IDispEventImpl<1, CEditFilterDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();
	m_pElement = NULL;

	m_editGraph->put_activeElement(NULL);

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CEditFilterDlg)
	CMD_HANDLER(ID_EDITFILTER_DELETEPRIMITIVE, OnFilterDeletePrimitive)

	CMD_HANDLER(ID_EDITFILTER_BLEND, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_COLORMATRIX, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_COMPONENTTRANSFER, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_COMPOSITE, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_CONVOLVEMATRIX, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_DIFFUSELIGHTING, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_DISPLACEMENTMAP, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_FLOOD, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_GAUSSIANBLUR, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_IMAGE, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_MERGE, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_MORPHOLOGY, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_OFFSET, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_SPECULARLIGHTING, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_TILE, OnFilterPrimitive)
	CMD_HANDLER(ID_EDITFILTER_TURBULENCE, OnFilterPrimitive)

	CMD_UPDATE(ID_EDITFILTER_BLEND, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_COLORMATRIX, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_COMPONENTTRANSFER, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_COMPOSITE, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_CONVOLVEMATRIX, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_DIFFUSELIGHTING, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_DISPLACEMENTMAP, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_FLOOD, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_GAUSSIANBLUR, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_IMAGE, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_MERGE, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_MORPHOLOGY, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_OFFSET, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_SPECULARLIGHTING, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_TILE, OnFilterPrimitiveUpdate)
	CMD_UPDATE(ID_EDITFILTER_TURBULENCE, OnFilterPrimitiveUpdate)
END_CMD_MAP()

LRESULT CEditFilterDlg::OnFilterDeletePrimitive(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_editGraph->DeleteSelectedPrimitive();

	return 0;
}

LRESULT CEditFilterDlg::OnFilterPrimitive(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pElement)
	{
		WCHAR* localName;

		switch (wID)
		{
		case ID_EDITFILTER_BLEND:					localName = L"feBlend"; break;
		case ID_EDITFILTER_COLORMATRIX:			localName = L"feColorMatrix"; break;
		case ID_EDITFILTER_COMPONENTTRANSFER:	localName = L"feComponentTransfer"; break;
		case ID_EDITFILTER_COMPOSITE:				localName = L"feComposite"; break;
		case ID_EDITFILTER_CONVOLVEMATRIX:		localName = L"feConvolveMatrix"; break;
		case ID_EDITFILTER_DIFFUSELIGHTING:		localName = L"feDiffuseLighting"; break;
		case ID_EDITFILTER_DISPLACEMENTMAP:		localName = L"feDisplacementMap"; break;
		case ID_EDITFILTER_FLOOD:					localName = L"feFlood"; break;
		case ID_EDITFILTER_GAUSSIANBLUR:			localName = L"feGaussianBlur"; break;
		case ID_EDITFILTER_IMAGE:					localName = L"feImage"; break;
		case ID_EDITFILTER_MERGE:					localName = L"feMerge"; break;
		case ID_EDITFILTER_MORPHOLOGY:			localName = L"feMorphology"; break;
		case ID_EDITFILTER_OFFSET:					localName = L"feOffset"; break;
		case ID_EDITFILTER_SPECULARLIGHTING:	localName = L"feSpecularLighting"; break;
		case ID_EDITFILTER_TILE:					localName = L"feTile"; break;
		case ID_EDITFILTER_TURBULENCE:			localName = L"feTurbulence"; break;

		default:
			ASSERT(0);
		}

		CComPtr<IEXMLDocument> eDocument;
		m_pElement->get_ownerDocument(&eDocument);

		CComPtr<IEElement> eElement;
		eDocument->createEElementNS(L"http://www.w3.org/2000/svg", localName, &eElement);
		if (eElement)
		{
			m_pElement->appendChild(eElement);
		}
	}

	return 0;
}

void CEditFilterDlg::OnFilterPrimitiveUpdate(long wID, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_pElement)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

#endif
