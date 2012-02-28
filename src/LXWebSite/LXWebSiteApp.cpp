// LXWebSiteApp.cpp : Implementation of CLXWebSiteApp
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "LXWebSiteApp.h"

void ComErrorMsg(HWND hWnd, _com_error &e)
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrMessage(e.ErrorMessage());
	_bstr_t bstrDescription(e.Description());

	CString msg;
	msg.Format("\n\tSource :  %s \n\tMessage : %s\n\tdescription : %s \n ", (LPCSTR)bstrSource, (LPCSTR)bstrMessage, (LPCSTR)bstrDescription);

	MessageBox(hWnd, msg, "LXWebSite", MB_OK);
}

/////////////////////////////////////////////////////////////////////////////
// CLXWebSiteApp

STDMETHODIMP CLXWebSiteApp::SetSite(ILXAddinSite* pSite)
{
	m_spAddinSite = pSite;

	{
		TCHAR appdata[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appdata);

		TCHAR pathname[MAX_PATH];
		_makepath(pathname, NULL, appdata, "LXFramework", NULL);

		TCHAR filename[MAX_PATH];
		_makepath(filename, NULL, pathname, "servers.xml", NULL);

		CComPtr<ILDOMDocument> xmldocument;
		if (SUCCEEDED(xmldocument.CoCreateInstance(CLSID_LDOMDocument)))
		{
			VARIANT_BOOL success;
			xmldocument->load(A2BSTR(filename), &success);

			CComPtr<ILDOMElement> documentElement;
			xmldocument->get_documentElement(&documentElement);
			if (documentElement)
			{
				CComPtr<ILDOMNode> node;
				documentElement->get_firstChild(&node);
				while (node)
				{
					CComQIPtr<ILDOMElement> element = node;
					if (element)
					{
						CComBSTR tagName;
						element->get_tagName(&tagName);
						if (!wcscmp(tagName, L"server"))
						{
							CComObject<CServer>* pServer;
							CComObject<CServer>::CreateInstance(&pServer);
							pServer->AddRef();

							element->getAttribute(L"name", &pServer->m_name);
							element->getAttribute(L"serverName", &pServer->m_serverName);
							element->getAttribute(L"directory", &pServer->m_directory);
							element->getAttribute(L"userName", &pServer->m_userName);
							element->getAttribute(L"password", &pServer->m_password);

							m_servers.Add(pServer);
						}
					}
					CComPtr<ILDOMNode> nextSibling;
					node->get_nextSibling(&nextSibling);
					node = nextSibling;
				}
			}
		}
	}

	if (m_spAddinSite)
	{
		CComPtr<ILXFrameworkFrame> lxframe;
		m_spAddinSite->GetFrame(&lxframe);

		CComQIPtr<IUIFrame> frame = lxframe;

		CComPtr<IUIManager> uiManager;
		m_spAddinSite->GetUIManager((IUnknown**)&uiManager);

		{
			CComPtr<IUIMenuDlg> menuDlg;
			uiManager->CreateMenuDlg(&menuDlg);

			CComPtr<IMenuItem> menuItem;
			uiManager->FindMenu(_Module.GetResourceInstance(), IDR_MAINFRAME, &menuItem);

			CComPtr<IMenuItem> menuItem0 = menuItem;
			//menuItem->GetSubMenu(0, &menuItem0);

			menuDlg->InitMenu(menuItem0, this/*CComQIPtr<ICommandTarget>(GetFrame())*/, -1);

			CComPtr<IUIDlgSite> dlgsite;
			uiManager->CreateDlgSite(L"MenuBar", NULL, menuDlg, &dlgsite);

			frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
		}
#if 0
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			uiManager->RegisterDlg(70/*TODO?IDR_MAINFRAME*/, L"Menubar", 0, &rdlg);

			CComPtr<IUIDlg> dlg;
			rdlg->CreateDlg(&dlg);

			CComPtr<IUIDlgSite> dlgsite;
			uiManager->CreateDlgSite(dlg, &dlgsite);

			frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
		}
#endif
	}

	return S_OK;
}

#if 0
#include "FileInspectorDlg.h"

STDMETHODIMP CLXWebSiteApp::CreateDlg(UINT nID, IUIDlg* *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComPtr<IUIManager> uiManager;
	m_spAddinSite->GetUIManager((IUnknown**)&uiManager);

	*pVal = NULL;

	switch (nID)
	{
	case 70:
		{
			CComPtr<IUIMenuDlg> menuDlg;
			uiManager->CreateMenuDlg(&menuDlg);

			CComPtr<IMenuItem> menuItem;
			uiManager->FindMenu(_Module.GetResourceInstance(), IDR_MAINFRAME, &menuItem);

			CComPtr<IMenuItem> menuItem0 = menuItem;
			//menuItem->GetSubMenu(0, &menuItem0);

			menuDlg->InitMenu(menuItem0, this/*CComQIPtr<ICommandTarget>(GetFrame())*/, -1);

			(*pVal = menuDlg)->AddRef();
		}
		break;

	case 71:
		{
			CComObject<CFileInspectorDlg>* p;
			CComObject<CFileInspectorDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
			p->m_app = this;
		}
		break;

	}

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CLXWebSiteApp)
// File
	CMD_HANDLER(ID_FILE_NEWSITE, OnFileNewSite)
	CMD_HANDLER(ID_FILE_OPENSITE, OnFileOpenSite)
	CMD_HANDLER(ID_FILE_MOUNTWORKGROUPSITE, OnFileMountWorkgroupSite)

	CMD_HANDLER(ID_FILE_FTPBROWSER, OnFileFTPBrowser)
	CMD_HANDLER(ID_FILE_WEBDAVBROWSER, OnFileWebDAVBrowser)

	CMD_HANDLER(ID_FILE_SERVERS, OnFileServers)

//	CMD_UPDATE(ID_IMAGETOOL_SELECT, OnToolUpdate)
END_CMD_MAP()

#include "NewSiteBeginDlg.h"
#include "NewSiteFinishDlg.h"
#include "NewSiteSingleWorkgroupDlg.h"
#include "NewSiteLocalSiteOptionsDlg.h"
#include "NewSiteLocalNameDlg.h"
#include "NewSiteFTPDlg.h"
#include "NewSiteWorkgroupOptionsDlg.h"
#include "NewSiteWorkgroupLogonDlg.h"

#include "WebSite.h"

LRESULT CLXWebSiteApp::OnFileNewSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
//	USES_CONVERSION;

	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIWnd> wnd = lxframe;
	HWND hWnd;
	wnd->get_hwnd(&hWnd);

	if (TRUE)
	{
		CPropertySheet* sheet = new CPropertySheet("New Site", 0, hWnd);
	//	sheet->SetWizardMode();
	//	sheet->m_psh.dwFlags |= PSH_WIZARD97;
		sheet->SetWatermark(MAKEINTRESOURCE(IDB_NEWSITE_WATERMARK));

		CNewSiteData data;

		CNewSiteBeginDlg begindlg;
		begindlg.m_psp.dwFlags |= PSP_HIDEHEADER;
		begindlg.SetHeaderTitle("LocalSite");

		CNewSiteFinishDlg finishdlg;
		finishdlg.m_psp.dwFlags |= PSP_HIDEHEADER;
		finishdlg.SetHeaderTitle("LocalSite");

		CNewSiteSingleWorkgroupDlg singleworkdlg;
		singleworkdlg.m_data = &data;
		singleworkdlg.m_nWorkgroup = 0;
		singleworkdlg.SetHeaderTitle("SingleWorkgroup");

		CNewSiteLocalSiteOptionsDlg localsitedlg;
		localsitedlg.m_data = &data;
		localsitedlg.m_nLocalSite = 0;
		localsitedlg.SetHeaderTitle("LocalSite");

		CNewSiteLocalNameDlg localnamedlg;
		localnamedlg.m_data = &data;
		localnamedlg.SetHeaderTitle("LocalName");

		CNewSiteFTPDlg ftpdlg;
		ftpdlg.m_data = &data;
		ftpdlg.SetHeaderTitle("FTP");

		CNewSiteWorkgroupOptionsDlg workoptionsdlg;
		workoptionsdlg.m_data = &data;
		workoptionsdlg.SetHeaderTitle("FTP");

		CNewSiteWorkgroupLogonDlg worklogondlg;
		worklogondlg.m_data = &data;
		worklogondlg.m_server = L"213.115.5.39";
		worklogondlg.m_username = L"Sigurd";
		worklogondlg.m_password = L"testing";
		worklogondlg.SetHeaderTitle("Workgroup Logon");

		sheet->AddPage(begindlg);
		sheet->AddPage(singleworkdlg);
		sheet->AddPage(localsitedlg);
		sheet->AddPage(localnamedlg);
		sheet->AddPage(ftpdlg);
		sheet->AddPage(finishdlg);
		sheet->AddPage(workoptionsdlg);
		sheet->AddPage(worklogondlg);

		sheet->DoModal();

		if (singleworkdlg.m_nWorkgroup == 0)
		{
			if (localnamedlg.m_localSitePath.GetLength() && localnamedlg.m_siteName.GetLength())
			{
				CComObject<CWebSite>* pWebSite;
				CComObject<CWebSite>::CreateInstance(&pWebSite);
				if (pWebSite)
				{
					pWebSite->AddRef();

					pWebSite->SetApp(this);

					HRESULT hr = pWebSite->m_webSite.CoCreateInstance(CLSID_LXLocalWebSite);
					if (SUCCEEDED(hr))
					{
						HRESULT hr = pWebSite->m_webSite->NewDocument(A2BSTR(localnamedlg.m_localSitePath), A2BSTR(localnamedlg.m_siteName));

						if (SUCCEEDED(hr))
						{
							CComQIPtr<IEFrame> eframe = lxframe;
							pWebSite->ShowViews(eframe);

							return 0;
						}
						else
						{
						// TODO, use IErrorInfo etc
							MessageBox(hWnd, "Failed to create Local WebSite", "LXWebSite", MB_OK);
						}
					}

					pWebSite->Release();
				}
			}
		}
		else if (singleworkdlg.m_nWorkgroup == 1)
		{
#if 0
			COAUTHIDENTITY cauthid;
			cauthid.User = worklogondlg.m_username;
			cauthid.UserLength = worklogondlg.m_username.length();
			cauthid.Domain = L"WORKGROUP";
			cauthid.DomainLength = wcslen(cauthid.Domain);
			cauthid.Password = worklogondlg.m_password;
			cauthid.PasswordLength = worklogondlg.m_password.length();
			cauthid.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

			COAUTHINFO cauthi;
			cauthi.dwAuthnSvc = RPC_C_AUTHN_WINNT;
			cauthi.dwAuthzSvc = RPC_C_AUTHZ_NONE;
			cauthi.pwszServerPrincName = NULL;
			cauthi.dwAuthnLevel = RPC_C_AUTHN_LEVEL_CONNECT;
			cauthi.dwImpersonationLevel = RPC_C_IMP_LEVEL_IMPERSONATE;
			cauthi.pAuthIdentityData = &cauthid;
			cauthi.dwCapabilities = EOAC_NONE;

			COSERVERINFO csi;
			csi.dwReserved1 = 0;
			csi.pwszName = worklogondlg.m_server;
			csi.pAuthInfo = &cauthi;
			csi.dwReserved2 = 0;

			MULTI_QI qi;
			qi.pIID = &XMILLWEBLib::IID_IXmillWebSite;
			qi.pItf = NULL;
			qi.hr = 0;

			HRESULT hr = CoCreateInstanceEx(XMILLWEBLib::CLSID_XmillWebSite, NULL, CLSCTX_SERVER/*CLSCTX_ALL*/, &csi, 1, &qi);

			if (SUCCEEDED(qi.hr))
			{
				XMILLWEBLib::IXmillWebSitePtr webSite;//(L"XMillWeb.WebSite");

				CComQIPtr<IClientSecurity> csec = qi.pItf;

				hr = CoSetProxyBlanket(qi.pItf, 
					cauthi.dwAuthnSvc,
					cauthi.dwAuthzSvc,
					cauthi.pwszServerPrincName,
					cauthi.dwAuthnLevel,
					cauthi.dwImpersonationLevel,
					cauthi.pAuthIdentityData,
					cauthi.dwCapabilities);

				webSite = qi.pItf;
				qi.pItf->Release();

				try
				{
					CComPtr<ILDOMDocument> document;
					document.CoCreateInstance(CLSID_LDOMDocument);
					VARIANT_BOOL bsuccess;
					document->loadXML(L"<website/>", &bsuccess);

					CComPtr<ILDOMElement> documentElement;
					document->get_documentElement(&documentElement);
					documentElement->setAttribute(L"name", L"TestSite1");

					BSTR bxml;
					document->saveXML(NULL, &bxml);
					_bstr_t xml = _bstr_t(bxml, false);

					long websiteID = webSite->NewWebSite(xml);
				}
				catch (_com_error &e)
				{
					ComError(e);
				}
			}
#endif
		}
	}
	return 0;
}

LRESULT CLXWebSiteApp::OnFileOpenSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIWnd> wnd = lxframe;
	HWND hWnd;
	wnd->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"Site (*.lxsite)\0*.lxsite\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	ofn.nFilterIndex = 2;
	
	if (GetOpenFileName(&ofn))
	{
		CComObject<CWebSite>* pWebSite;
		CComObject<CWebSite>::CreateInstance(&pWebSite);
		if (pWebSite)
		{
			pWebSite->AddRef();

			pWebSite->SetApp(this);

			HRESULT hr = pWebSite->LoadDocument(A2BSTR(sbuffer));
			if (SUCCEEDED(hr))
			{
				CComQIPtr<IEFrame> eframe = lxframe;
				pWebSite->ShowViews(eframe);

				return 0;
			}
			else
			{
				MessageBox(hWnd, "Failed to open website", "LXWebSite", MB_OK);
			}

			pWebSite->Release();
		}
		else
		{
			MessageBox(hWnd, "Failed to create website document", "LXWebSite", MB_OK);
		}
	}

	return 0;
}

#include "LogonServerDlg.h"

#include "WorkgroupDocument.h"

LRESULT CLXWebSiteApp::OnFileMountWorkgroupSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CLogonServerDlg dlg;
	dlg.m_server = L"213.115.5.45";
	dlg.m_username = L"Sigurd";
	dlg.m_password = L"testing";

	if (dlg.DoModal() == IDOK)
	{
#if 0
		COAUTHIDENTITY cauthid;
		cauthid.User = dlg.m_username;
		cauthid.UserLength = dlg.m_username.length();
		cauthid.Domain = L"WORKGROUP";
		cauthid.DomainLength = wcslen(cauthid.Domain);
		cauthid.Password = dlg.m_password;
		cauthid.PasswordLength = dlg.m_password.length();
		cauthid.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

		COAUTHINFO cauthi;
		cauthi.dwAuthnSvc = RPC_C_AUTHN_WINNT;
		cauthi.dwAuthzSvc = RPC_C_AUTHZ_NONE;
		cauthi.pwszServerPrincName = NULL;
		cauthi.dwAuthnLevel = RPC_C_AUTHN_LEVEL_CONNECT;
		cauthi.dwImpersonationLevel = RPC_C_IMP_LEVEL_IMPERSONATE;
		cauthi.pAuthIdentityData = &cauthid;
		cauthi.dwCapabilities = EOAC_NONE;

		COSERVERINFO csi;
		csi.dwReserved1 = 0;
		csi.pwszName = dlg.m_server;
		csi.pAuthInfo = &cauthi;
		csi.dwReserved2 = 0;

		MULTI_QI qi[2];
		qi[0].pIID = &XMILLWEBLib::IID_IXmillWorkgroup;
		qi[0].pItf = NULL;
		qi[0].hr = 0;

		qi[1].pIID = &XMILLWEBLib::IID_ILFileSystem;
		qi[1].pItf = NULL;
		qi[1].hr = 0;

		HRESULT hr = CoCreateInstanceEx(XMILLWEBLib::CLSID_XmillWorkgroup, NULL, CLSCTX_SERVER/*CLSCTX_ALL*/, &csi, 2, qi);

		if (SUCCEEDED(qi[0].hr) && SUCCEEDED(qi[1].hr))
		{
			//XMILLWEBLib::IXmillWorkgroupPtr workgroup;//(L"XMillWeb.WebSite");

			//CComQIPtr<IClientSecurity> csec = qi[0].pItf;

			hr = CoSetProxyBlanket(qi[0].pItf, 
				cauthi.dwAuthnSvc,
				cauthi.dwAuthzSvc,
				cauthi.pwszServerPrincName,
				cauthi.dwAuthnLevel,
				cauthi.dwImpersonationLevel,
				cauthi.pAuthIdentityData,
				cauthi.dwCapabilities);

			hr = CoSetProxyBlanket(qi[1].pItf, 
				cauthi.dwAuthnSvc,
				cauthi.dwAuthzSvc,
				cauthi.pwszServerPrincName,
				cauthi.dwAuthnLevel,
				cauthi.dwImpersonationLevel,
				cauthi.pAuthIdentityData,
				cauthi.dwCapabilities);

			//workgroup = qi.pItf;
			//qi.pItf->Release();

			CComObject<CWorkgroupDocument>* pWorkgroupDocument;
			CComObject<CWorkgroupDocument>::CreateInstance(&pWorkgroupDocument);
			if (pWorkgroupDocument)
			{
				pWorkgroupDocument->AddRef();

				pWorkgroupDocument->m_workgroup = qi[0].pItf;
				pWorkgroupDocument->m_filesystem = qi[1].pItf;

				pWorkgroupDocument->ShowView();
			}

			/*
			try
			{
				_bstr_t result = webSite->TestMethod("Test");
			}
			catch (_com_error &e)
			{
				ComError(e);
			}
			*/
		}
		else
		{
			MessageBox(hWnd, "Couldn't connect to Server", "", MB_OK);
		}
#endif
	}

	return 0;
}

#include "FTPView.h"

LRESULT CLXWebSiteApp::OnFileFTPBrowser(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<IUIManager> uiManager;
	m_spAddinSite->GetUIManager((IUnknown**)&uiManager);

	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIMDIFrame> mdiframe = lxframe;

	CComObject<CFTPView>* pView;
	CComObject<CFTPView>::CreateInstance(&pView);
	if (pView)
	{
		CComPtr<IMenuItem> menu;
		uiManager->FindMenu(_Module.GetResourceInstance(), IDR_FTPVIEW, &menu);

		CComPtr<IUIDlgSite> dlgsite;
		uiManager->CreateDlgSite(L"FTP", menu, pView, &dlgsite);

		CComPtr<IUIMDIChild> childFrame;
		mdiframe->CreateChildFrameDlgSite(dlgsite, &childFrame);
	}

	return 0;
}

#include "WebDAVView.h"

LRESULT CLXWebSiteApp::OnFileWebDAVBrowser(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<IUIManager> uiManager;
	m_spAddinSite->GetUIManager((IUnknown**)&uiManager);

	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIMDIFrame> mdiframe = lxframe;

	CComObject<CWebDAVView>* pView;
	CComObject<CWebDAVView>::CreateInstance(&pView);
	if (pView)
	{
		CComPtr<IMenuItem> menu;
		uiManager->FindMenu(_Module.GetResourceInstance(), IDR_WEBDAVVIEW, &menu);

		CComPtr<IUIDlgSite> dlgsite;
		uiManager->CreateDlgSite(L"WebDAV", menu, pView, &dlgsite);

		CComPtr<IUIMDIChild> childFrame;
		mdiframe->CreateChildFrameDlgSite(dlgsite, &childFrame);
	}

	return 0;
}

#include "ServersDlg.h"

LRESULT CLXWebSiteApp::OnFileServers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIWnd> wnd = lxframe;
	HWND hWnd;
	wnd->get_hwnd(&hWnd);

	CServersDlg dlg;

	for (int i = 0; i < m_servers.GetSize(); i++)
	{
		CComObject<CServer>* pServer;
		CComObject<CServer>::CreateInstance(&pServer);
		pServer->AddRef();

		*pServer = *m_servers[i];
		dlg.m_servers.Add(pServer);
	}

	if (dlg.DoModal() == IDOK)
	{
		int i;
		for (i = 0; i < m_servers.GetSize(); i++)
		{
			m_servers[i]->Release();
		}
		m_servers.RemoveAll();

		for (i = 0; i < dlg.m_servers.GetSize(); i++)
		{
			CComObject<CServer>* pServer;
			CComObject<CServer>::CreateInstance(&pServer);
			pServer->AddRef();

			*pServer = *dlg.m_servers[i];
			m_servers.Add(pServer);
		}

		TCHAR appdata[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appdata);

		TCHAR pathname[MAX_PATH];
		_makepath(pathname, NULL, appdata, "LXFramework", NULL);

		_mkdir(pathname);

		TCHAR filename[MAX_PATH];
		_makepath(filename, NULL, pathname, "servers.xml", NULL);

		CComPtr<ILDOMDocument> xmldocument;
		if (SUCCEEDED(xmldocument.CoCreateInstance(CLSID_LDOMDocument)))
		{
			VARIANT_BOOL success;
			xmldocument->loadXML(L"<servers/>", &success);
			if (success)
			{
				CComPtr<ILDOMElement> documentElement;
				xmldocument->get_documentElement(&documentElement);

				for (int i = 0; i < m_servers.GetSize(); i++)
				{
					CServer* pServer = m_servers[i];

					CComPtr<ILDOMElement> element;
					xmldocument->createElement(L"server", &element);
					if (element)
					{
						element->setAttribute(L"name", pServer->m_name);
						element->setAttribute(L"serverName", pServer->m_serverName);
						element->setAttribute(L"userName", pServer->m_userName);
						element->setAttribute(L"password", pServer->m_password);
						element->setAttribute(L"directory", pServer->m_directory);

						documentElement->appendChild(element, NULL);
					}
				}

				xmldocument->save(A2BSTR(filename), &success);
				if (success)
				{
					return 0;
				}
			}
		}

		MessageBox(hWnd, "Failed to save servers configuration", "LXWebSite", MB_OK);
	}

	return 0;
}
