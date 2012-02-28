// FTPView.cpp : Implementation of CFTPView
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "FTPView.h"

/////////////////////////////////////////////////////////////////////////////
// CFTPView

int CFTPView::FinalConstruct()
{
	HRESULT hr;

	hr = m_ftpBrowser.CoCreateInstance(CLSID_FTPBrowser);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CFTPView::FinalRelease()
{
/*
	if (m_document)
		IDispEventImpl<3, CSiteLinksView, &DIID__IWebSiteEvents, &LIBID_LXFrameworkLib, 1, 0>::DispEventUnadvise(m_document);
*/
}

LRESULT CFTPView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axftpBrowser.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axftpBrowser.AttachControl(m_ftpBrowser, &p);

	m_ftpBrowser->put_ServerName(L"ftp.bredband.no");
	m_ftpBrowser->put_UserName(L"sigler");
	m_ftpBrowser->put_Password(L"9pmbi238");

	VARIANT_BOOL success;
	m_ftpBrowser->Connect(&success);

	return 0;
}

LRESULT CFTPView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CFTPView::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int top = 0;//m_thumbHeight;

	int cx = client.Width();
	int cy = client.Height();

	m_axftpBrowser.MoveWindow(0, top, cx, cy-top, TRUE);
}

BEGIN_CMD_MAP(CFTPView)
	//CMD_HANDLER(&ID_SITE_RESCAN, OnRescan)
END_CMD_MAP()

/*
STDMETHODIMP CFTPView::get_document(IWebSite **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFTPView::put_document(IWebSite *newVal)
{
	m_document = newVal;
	return S_OK;
}
*/