// SiteFTPView.cpp : Implementation of CSiteFTPView
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "SiteFTPView.h"

#include "WebSite.h"

#include "LXWebSiteApp.h"	// TODO remove

/////////////////////////////////////////////////////////////////////////////
// CSiteFTPView

int CSiteFTPView::FinalConstruct()
{
	HRESULT hr;

	hr = m_ftpBrowser.CoCreateInstance(CLSID_FTPBrowser);
	if (FAILED(hr)) return E_NOINTERFACE;

	return S_OK;
}

void CSiteFTPView::FinalRelease()
{
/*
	if (m_document)
		IDispEventImpl<3, CSiteLinksView, &DIID__IWebSiteEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
*/
}

LRESULT CSiteFTPView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axftpBrowser.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axftpBrowser.AttachControl(m_ftpBrowser, &p);

	IDispEventImpl<1, CSiteFTPView, &DIID__IFTPBrowserEvents, &LIBID_FTPMODLib, 1, 0>::DispEventAdvise(m_ftpBrowser);
	/*
	m_ftpBrowser->put_ServerName(L"ftp.bredband.no");
	m_ftpBrowser->put_UserName(L"sigler");
	m_ftpBrowser->put_Password(L"9pmbi238");

	VARIANT_BOOL success;
	m_ftpBrowser->Connect(&success);
	*/

	return 0;
}

LRESULT CSiteFTPView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CSiteFTPView, &DIID__IFTPBrowserEvents, &LIBID_FTPMODLib, 1, 0>::DispEventUnadvise(m_ftpBrowser);
	return 0;
}

LRESULT CSiteFTPView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CSiteFTPView::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int top = 0;//m_thumbHeight;

	int cx = client.Width();
	int cy = client.Height();

	m_axftpBrowser.MoveWindow(0, top, cx, cy-top, TRUE);
}

STDMETHODIMP CSiteFTPView::get_document(IWebSite **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

void __stdcall CSiteFTPView::OnDblClick(/*[in]*/ BSTR url)
{
	CWebSite* pWebSite = ((CWebSite*)m_document);

	CComQIPtr<ILXAddin> addin = m_document->m_app;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	CComPtr<IMoniker> moniker;
	CreateURLMoniker(NULL, url, &moniker);
	if (moniker)
	{
//	CComPtr<IBindCtx> ctx;
//	CreateAsyncBindCtx(0, this, NULL, &ctx);

//	CComPtr<IStream> stream;
	//if (SUCCEEDED(moniker->BindToStorage(ctx, NULL, IID_IStream, (void**)&stream)))
		CComQIPtr<ILXAddin> addin = pWebSite->m_app;
		CComPtr<ILXAddinSite> addinSite;
		addin->GetSite(&addinSite);

		CComPtr<ILXFrameworkFrame> lxframe;
		addinSite->GetFrame(&lxframe);

		if (FAILED(lxframe->OpenDocument(moniker)))
		{
			CString msg;
			msg.Format("Failed to open document:\n%S", url);
			MessageBox(msg, "LXFramework", MB_OK);
		}
	}
	else
	{
		CString msg;
		msg.Format("Failed to create moniker for:\n%S", url);
		MessageBox(msg, "LXFramework", MB_OK);
	}

	/*
	HRESULT hr = lxframe->OpenDocument(moniker);
	if (FAILED(hr))
	{
		CString msg;
		msg.Format("Failed to open document\n%S", url);
		MessageBox(msg, "LXFramework", MB_OK);
	}
	*/
}

// ICommandTarget

BEGIN_CMD_MAP(CSiteFTPView)
	CMD_HANDLER(ID_FTPSERVER_CONNECT, OnFTPConnect)
	//CMD_HANDLER(&ID_SITE_RESCAN, OnRescan)
END_CMD_MAP()

STDMETHODIMP CSiteFTPView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	CComQIPtr<ICommandTarget> target;
	
// Try document
	target = m_document;
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	return S_OK;
}

LRESULT CSiteFTPView::OnFTPConnect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CServer* pServer = static_cast<CLXWebSiteApp*>(m_document->m_app.p)->GetServerByName(m_document->m_ftpServerName);

	if (pServer)
	{
		m_ftpBrowser->put_ServerName(pServer->m_serverName);
		m_ftpBrowser->put_UserName(pServer->m_userName);
		m_ftpBrowser->put_Password(pServer->m_password);

		VARIANT_BOOL success;
		m_ftpBrowser->Connect(&success);
		if (!success)
		{
			MessageBox("Failed to connect", "LXWebSite", MB_OK);
		}
	}

	return 0;
}

//////////////////////////
/// IBindStatusCallback

STDMETHODIMP CSiteFTPView::OnStartBinding( 
													/* [in] */ DWORD dwReserved,
													/* [in] */ IBinding __RPC_FAR *pib)
{
	m_spBinding = pib;
	return S_OK;
}

STDMETHODIMP CSiteFTPView::GetPriority(/* [out] */ LONG __RPC_FAR *pnPriority)
{
	return S_OK;
}

STDMETHODIMP CSiteFTPView::OnLowResource(/* [in] */ DWORD reserved)
{
	return S_OK;
}

STDMETHODIMP CSiteFTPView::OnProgress( 
											  /* [in] */ ULONG ulProgress,
											  /* [in] */ ULONG ulProgressMax,
											  /* [in] */ ULONG ulStatusCode,
											  /* [in] */ LPCWSTR szStatusText)
{
	return S_OK;
}

STDMETHODIMP CSiteFTPView::OnStopBinding( 
												  /* [in] */ HRESULT hresult,
												  /* [unique][in] */ LPCWSTR szError)
{
	m_spBinding.Release();
	return S_OK;
}

STDMETHODIMP CSiteFTPView::GetBindInfo( 
												/* [out] */ DWORD __RPC_FAR *grfBINDF,
												/* [unique][out][in] */ BINDINFO __RPC_FAR *pbindinfo)
{
	DWORD cbSize = pbindinfo->cbSize;        
	memset(pbindinfo,0,cbSize);
	pbindinfo->cbSize = cbSize;

//	*grfBINDF = 0;
	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

//	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

	pbindinfo->dwBindVerb = BINDVERB_GET;	// set verb

	return S_OK;
}

STDMETHODIMP CSiteFTPView::OnDataAvailable( 
													 /* [in] */ DWORD grfBSCF,
													 /* [in] */ DWORD dwSize,
													 /* [in] */ FORMATETC __RPC_FAR *pformatetc,
													 /* [in] */ STGMEDIUM __RPC_FAR *pstgmed)
{
#if 0
	m_bufferdata = (BYTE*)realloc(m_bufferdata, m_bufferlen + dwSize);
	if (m_bufferdata)
	{
		ULONG dwRead;
		pstgmed->pstm->Read(m_bufferdata+m_bufferlen, dwSize, &dwRead);

		//ATLASSERT(dwRead == dwSize);

		m_bufferlen += dwRead;

		return S_OK;
	}
	else
	{
		return E_OUTOFMEMORY;
	}
#endif
	return S_OK;
}

STDMETHODIMP CSiteFTPView::OnObjectAvailable( 
														/* [in] */ REFIID riid,
														/* [iid_is][in] */ IUnknown __RPC_FAR *punk)
{
#if 0
	HRESULT hr;

	m_spUnknown = punk;

	m_spOleObject = m_spUnknown;
	m_spOleDocument = m_spUnknown;

	hr = m_spOleObject->SetClientSite(this);
	hr = m_spOleObject->Advise(this, &m_dwAdvise);

//	hr = OleRun(m_spUnknown);

	CRect rc(0,0,300,300);
	//GetClientRect(&rc);
	hr = m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, this, 0, m_pUI->m_hWnd, &rc);
#endif

	return S_OK;
}
