// WebDAVView.cpp : Implementation of CWebDAVView
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "WebDAVView.h"

/////////////////////////////////////////////////////////////////////////////
// CWebDAVView

int CWebDAVView::FinalConstruct()
{
	HRESULT hr;

	hr = m_browser.CoCreateInstance(CLSID_WebDAVBrowser);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CWebDAVView::FinalRelease()
{
/*
	if (m_document)
		IDispEventImpl<3, CSiteLinksView, &DIID__IWebSiteEvents, &LIBID_LXFrameworkLib, 1, 0>::DispEventUnadvise(m_document);
*/
}

LRESULT CWebDAVView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	AtlAxWinInit();

	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axbrowser.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axbrowser.AttachControl(m_browser, &p);

#if 0
	m_browser->put_ServerName(L"ftp.bredband.no");
	m_browser->put_UserName(L"sigler");
	m_browser->put_Password(L"9pmbi238");
#endif

	VARIANT_BOOL success;
	m_browser->Connect(&success);

	return 0;
}

LRESULT CWebDAVView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CWebDAVView::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int top = 0;//m_thumbHeight;

	int cx = client.Width();
	int cy = client.Height();

	m_axbrowser.MoveWindow(0, top, cx, cy-top, TRUE);
}

BEGIN_CMD_MAP(CWebDAVView)
	//CMD_HANDLER(&ID_SITE_RESCAN, OnRescan)
END_CMD_MAP()

/*
STDMETHODIMP CWebDAVView::get_document(IWebSite **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CWebDAVView::put_document(IWebSite *newVal)
{
	m_document = newVal;
	return S_OK;
}
*/