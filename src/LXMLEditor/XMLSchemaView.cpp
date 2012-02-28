// XMLSchemaView.cpp : Implementation of CXMLSchemaView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "XMLSchemaView.h"

#include "XMLSchema.h"

#if 0

#include "XMLSchemaGlobalsCtl.h"
#include "XMLSchemaDesignCtl.h"
#include "XMLSchemaAttributesView.h"

/////////////////////////////////////////////////////////////////////////////
// CXMLSchemaView

int CXMLSchemaView::FinalConstruct()
{
//	HRESULT hr;

//	hr = CoCreateInstance (CLSID_UIView, GetControllingUnknown(), CLSCTX_INPROC_SERVER, IID_IUnknown, (void **) &m_puiwnd);
//	if (FAILED (hr)) return E_NOINTERFACE;

	CComObject<CXMLSchemaGlobalsCtl>::CreateInstance(&m_globalsCtl);
	CComObject<CXMLSchemaDesignCtl>::CreateInstance(&m_designCtl);
	CComObject<CXMLSchemaAttributesView>::CreateInstance(&m_attributesCtl);

	CComPtr<IUnknown> p;
	m_globalsCtl->QueryInterface(IID_IUnknown, (void**)&p);
	IDispEventImpl<1, CXMLSchemaView, &DIID__IXMLSchemaGlobalsCtlEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(p);

	return S_OK;
}

long CXMLSchemaView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	if (HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam) != 0)
//		return -1;

	CComQIPtr<IUIWnd> thiswnd;
	QueryInterface(IID_IUIWnd, (void**)&thiswnd);

	HWND hwnd = m_hWnd;
//	get_hwnd(&hwnd);

//	CComQIPtr<IUIContextManager> uiManager;
//	gApp->get_uiManager(&uiManager);

//	m_editControl->put_uiManager(uiManager);
//	m_editControl->put_ESvgDocument(m_pDocument);

	CRect rc(0,0,0,0);
	m_globalsCtl->Create(hwnd, rc, "", WS_CHILD | WS_VISIBLE);
	m_designCtl->Create(hwnd, rc, "", WS_CHILD | WS_VISIBLE);
	m_attributesCtl->Create(hwnd, rc, "", WS_CHILD | WS_VISIBLE);

	CComQIPtr<IDOMDocument> domdocument;
	m_document->get_DOMDocument(&domdocument);

	CComQIPtr<IDOMElement> documentElement;
	domdocument->get_documentElement(&documentElement);

	m_pSchema = new CSchema;
	m_pSchema->IncludeSchema(documentElement);

	m_designCtl->m_pSchema = m_pSchema;
	m_globalsCtl->m_pSchema = m_pSchema;

	return 0;
}

long CXMLSchemaView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);

	CRect client;
	GetClientRect(&client);

	int h = client.Height()/2;

	m_globalsCtl->MoveWindow(0, h*0, client.Width(), h, TRUE);
	m_designCtl->MoveWindow(0, h*1, client.Width(), h, TRUE);
	m_attributesCtl->MoveWindow(0, 0, client.Width(), 0, TRUE);

	return 0;
}

STDMETHODIMP CXMLSchemaView::get_document(IESvgDocument **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CXMLSchemaView::put_document(IESvgDocument *newVal)
{
	m_document = newVal;
	return S_OK;
}

HRESULT __stdcall CXMLSchemaView::OnDesignNode(IDOMNode* node)
{
	m_designCtl->put_rootNode(node);
	return S_OK;
}
#endif