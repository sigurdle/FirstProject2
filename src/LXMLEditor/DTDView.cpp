// DTDView.cpp : Implementation of CDTDView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "DTDView.h"

//#include "DTDDocument.h"

#include "EXMLDocument.h"
#include "EXMLViewGroup.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CDTDView

int CDTDView::FinalConstruct()
{
	HRESULT hr;

	hr = m_DTDGraph.CoCreateInstance(CLSID_ASGraphCtl);
	if (FAILED(hr)) return E_NOINTERFACE;

	return S_OK;
}

void CDTDView::FinalRelease()
{
	if (m_DTDGraph)
	{
		m_DTDGraph.Release();
	}
}

LRESULT CDTDView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> document;
	document = m_viewGroup->m_pDocument->m_document;//->GetDocument(&document);

	CComQIPtr<ILDTDDocument> dtdDocument = document;

	CComPtr<IASModel> asModel;
	ASSERT(0);
#if 0
	dtdDocument->get_asModel(&asModel);
#endif

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axDTDGraph.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axDTDGraph.AttachControl(m_DTDGraph, &p);

	CComQIPtr<IASNamedObjectMap> elementMap;
	asModel->get_elementDeclarations(&elementMap);

	CComQIPtr<IASElementDeclaration> rootElement;
	elementMap->item(0, (IASObject**)&rootElement);

	m_DTDGraph->put_asModel(asModel);
	m_DTDGraph->put_asRootObject(rootElement);

	HRESULT hr;

	hr = IDispEventImpl<3, CDTDView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(reinterpret_cast<IUnknown*>(m_viewGroup->m_pDocument));
	ASSERT(SUCCEEDED(hr));

	return 0;
}

LRESULT CDTDView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT hr;

	IDispEventImpl<3, CDTDView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(reinterpret_cast<IUnknown*>(m_viewGroup->m_pDocument));
	ASSERT(SUCCEEDED(hr));

	return 0;
}

LRESULT CDTDView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axDTDGraph.MoveWindow(0, 0, client.right, client.bottom, TRUE);
	return 0;
}

HRESULT __stdcall CDTDView::OnDoneParsing()
{
	// What's this for again??
	MessageBeep(-1);
#if 0
	CComQIPtr<IASNamedObjectMap> elementMap;
	m_document->m_dtdModel->get_elementDeclarations(&elementMap);

	CComQIPtr<IASElementDeclaration> rootElement;
	elementMap->item(0, (IASObject**)&rootElement);

	m_DTDGraph->put_asModel(m_document->m_dtdModel);
	m_DTDGraph->put_asRootObject(rootElement);
#endif

	return S_OK;
}

BEGIN_CMD_MAP(CDTDView)
// Schema
	CMD_HANDLER(ID_SCHEMA_CONTENTMODEL_OPTIONAL, OnContentModelOptional)
	CMD_HANDLER(ID_SCHEMA_CONTENTMODEL_UNBOUNDED, OnContentModelUnbounded)
	CMD_UPDATE(ID_SCHEMA_CONTENTMODEL_OPTIONAL, OnContentModelOptionalUpdate)
	CMD_UPDATE(ID_SCHEMA_CONTENTMODEL_UNBOUNDED, OnContentModelUnboundedUpdate)
END_CMD_MAP()

bool IsOptional(IASContentModel* asCM)
{
	if (asCM)
	{
		long minOccurs;
		asCM->get_minOccurs(&minOccurs);

		return (minOccurs == 0);
	}
	else
		return false;
}

bool IsUnbounded(IASContentModel* asCM)
{
	if (asCM)
	{
		long maxOccurs;
		asCM->get_maxOccurs(&maxOccurs);

		return (maxOccurs == 0xffffffff/*AS_UNBOUNDED*/);
	}
	else
		return false;
}

LRESULT CDTDView::OnContentModelOptional(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<IASDesignObject> item;
	m_DTDGraph->get_ActiveItem(&item);
	CComQIPtr<IASDesignContentModel> designCM = item;
	if (designCM)
	{
		CComPtr<IASContentModel> asCM;
		designCM->get_asCM((IUnknown**)&asCM);

		if (IsOptional(asCM))
			designCM->RemoveOptionalUnbounded(VARIANT_TRUE, VARIANT_FALSE);
		else
			designCM->SetOptionalUnbounded(VARIANT_TRUE, VARIANT_FALSE);
	}

	return 0;
}

LRESULT CDTDView::OnContentModelUnbounded(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<IASDesignObject> item;
	m_DTDGraph->get_ActiveItem(&item);
	CComQIPtr<IASDesignContentModel> designCM = item;
	if (designCM)
	{
		CComPtr<IASContentModel> asCM;
		designCM->get_asCM((IUnknown**)&asCM);

		if (IsUnbounded(asCM))
			designCM->RemoveOptionalUnbounded(VARIANT_FALSE, VARIANT_TRUE);
		else
			designCM->SetOptionalUnbounded(VARIANT_FALSE, VARIANT_TRUE);
	}

	return 0;
}

void CDTDView::OnContentModelOptionalUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	CComPtr<IASDesignObject> item;
	m_DTDGraph->get_ActiveItem(&item);
	CComQIPtr<IASDesignContentModel> designCM = item;
	if (designCM)
	{
		CComPtr<IASContentModel> asCM;
		designCM->get_asCM((IUnknown**)&asCM);

		pCmdUI->SetCheck(IsOptional(asCM));
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

void CDTDView::OnContentModelUnboundedUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	CComPtr<IASDesignObject> item;
	m_DTDGraph->get_ActiveItem(&item);
	CComQIPtr<IASDesignContentModel> designCM = item;
	if (designCM)
	{
		CComPtr<IASContentModel> asCM;
		designCM->get_asCM((IUnknown**)&asCM);

		pCmdUI->SetCheck(IsUnbounded(asCM));
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

#endif