// WebSite.cpp : Implementation of CWebSite
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "WebSite.h"

#include "SiteFilesView.h"
#include "SiteLinksView.h"
#include "SiteFTPView.h"

void WinError(DWORD lastError)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		lastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}

/*
void CSiteItem::DeselectAll()
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
		pItem->m_selected = FALSE;
	}
}
*/


/////////////////////////////////////////////////////////////////////////////
// CWebSite

void CWebSite::FinalRelease()
{
	m_webSite.Release();
}

STDMETHODIMP CWebSite::LoadDocument(BSTR pathName)
{
#if 0

	COSERVERINFO csi;
	csi.dwReserved1 = 0;
//	csi.pwszName = L"Mmstudio-proj";
	csi.pwszName = L"localhost";
	csi.pAuthInfo = NULL;
	csi.dwReserved2 = 0;

	MULTI_QI qi;
	qi.pIID = &IID_IWSSrv;
	qi.pItf = NULL;
	qi.hr = 0;
#endif

	CComPtr<ILXLocalWebSite> webSite;
	HRESULT hr = webSite.CoCreateInstance(CLSID_LXLocalWebSite);
//	HRESULT hr = CoCreateInstanceEx(CLSID_LXLocalWebSite, NULL, /*CLSCTX_SERVER*/CLSCTX_ALL, &csi, 1, &qi);

	if (SUCCEEDED(hr))
	{
		//HRESULT hr = m_webSite.CreateInstance(L"WSSrvMod.WSSrv");

		//if (SUCCEEDED(qi.hr))
		{
			/*
			m_webSite = qi.pItf;
			qi.pItf->Release();
			*/
			m_webSite = webSite;

			VARIANT_BOOL success;
			hr = m_webSite->LoadDocument(pathName, &success);
			if (SUCCEEDED(hr))
			{
				return hr;
			}

			m_webSite = NULL;
		}
	}
	else
	{
		//MessageBox(NULL, "Couldn't create website object", "WebEditor", MB_OK);
		//WinError(hr);
	}

	return hr;
}

void CWebSite::NewWindow()
{
	//CComQIPtr<IUIContextManager> uiManager = gApp->m_uiManager;

#if 0
	{
		CComObject<CUIMDIChild>* child;
		CComObject<CUIMDIChild>::CreateInstance(&child);
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		// Files
		{
			CComObject<CSiteFilesView>* filesView;
			CComObject<CSiteFilesView>::CreateInstance(&filesView);
			if (filesView)
			{
				gApp->m_frame->FindMenu(IDR_FILESVIEW, &filesView->m_menu);
				filesView->m_document = this;
				child->AddPage(filesView, NULL);
			}
		}

		// Links
		{
			CComObject<CSiteLinksView>* linksView;
			CComObject<CSiteLinksView>::CreateInstance(&linksView);
		//	linksView->Create(uiManager, L"Links", (IID*)&CLSID_SiteFilesView, NULL);
			linksView->m_document = this;
			child->AddPage(linksView, NULL);
		}

		// FTP
		{
			CComObject<CSiteFTPView>* ftpView;
			CComObject<CSiteFTPView>::CreateInstance(&ftpView);
			//ftpView.CoCreateInstance(CLSID_SiteFTPView);
			//ftpView->Create(uiManager, L"FTP", (IID*)&CLSID_SiteFilesView, NULL);
			ftpView->m_document = this;
			child->AddPage(ftpView, NULL);
		}

		child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
//		child->CreateMDIChild(frame, NULL);
//		child.Detach();	// Keep it open
	}
#endif
}

STDMETHODIMP CWebSite::ShowViews(IEFrame* pFrame)
{
	ATLASSERT(0);
#if 0
	CComQIPtr<ILXAddin> addin = m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<IUIManager> uiManager;
	addinSite->GetUIManager((IUnknown**)&uiManager);

	/*
	CComObject<CWebXMLViewGroup>* viewGroup;
	CComObject<CWebXMLViewGroup>::CreateInstance(&viewGroup);
	if (viewGroup)
	{
		viewGroup->AddRef();

		viewGroup->SetDocument(this);
		*/

		CComPtr<IEViewGroupSite> spViewGroupSite;
		pFrame->CreateViewGroupSite(NULL/*viewGroup*/, &spViewGroupSite);

		{
		// Files
			CComObject<CSiteFilesView>* filesView;
			CComObject<CSiteFilesView>::CreateInstance(&filesView);
			if (filesView)
			{
				uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SITEFILESVIEW, &filesView->m_menu);
				filesView->m_document = this;

			//	layoutView->m_viewGroup = viewGroup;
			//	viewGroup->m_views.Add(layoutView);

			//	viewGroup->m_layoutView = layoutView;

				/*viewGroup->m_*/spViewGroupSite->AddPage(filesView, NULL);
			}

		// Links
			CComObject<CSiteLinksView>* linksView;
			CComObject<CSiteLinksView>::CreateInstance(&linksView);
			if (linksView)
			{
				uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SITELINKSVIEW, &linksView->m_menu);
				linksView->m_document = this;

				//sourceView->m_viewGroup = viewGroup;
				//viewGroup->m_views.Add(sourceView);

				/*viewGroup->m_*/spViewGroupSite->AddPage(linksView, NULL);
			}

		// FTP
			CComObject<CSiteFTPView>* ftpView;
			CComObject<CSiteFTPView>::CreateInstance(&ftpView);
			if (ftpView)
			{
				uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SITEFTPVIEW, &ftpView->m_menu);
				ftpView->m_document = this;

				//sourceView->m_viewGroup = viewGroup;
				//viewGroup->m_views.Add(sourceView);

				/*viewGroup->m_*/spViewGroupSite->AddPage(ftpView, NULL);
			}
		}

		CComQIPtr<IUIMDIFrame> mdiframe = pFrame;

		CComPtr<IUIMDIChild> childFrame;
		mdiframe->CreateChildFrame(spViewGroupSite, &childFrame);
	//}
#endif

	return S_OK;
}

/*
STDMETHODIMP CWebSite::get_ftpServerName(BSTR *pVal)
{
	*pVal = SysAllocString(m_ftpServerName);
	return S_OK;
}

STDMETHODIMP CWebSite::put_ftpServerName(BSTR newVal)
{
	m_ftpServerName = newVal;
	return S_OK;
}

STDMETHODIMP CWebSite::get_ftpDirectory(BSTR *pVal)
{
	*pVal = SysAllocString(m_ftpDirectory);
	return S_OK;
}

STDMETHODIMP CWebSite::put_ftpDirectory(BSTR newVal)
{
	m_ftpDirectory = newVal;
	return S_OK;
}

STDMETHODIMP CWebSite::get_ftpUsername(BSTR *pVal)
{
	*pVal = SysAllocString(m_ftpUsername);
	return S_OK;
}

STDMETHODIMP CWebSite::put_ftpUsername(BSTR newVal)
{
	m_ftpUsername = newVal;
	return S_OK;
}

STDMETHODIMP CWebSite::get_ftpPassword(BSTR *pVal)
{
	*pVal = SysAllocString(m_ftpPassword);
	return S_OK;
}

STDMETHODIMP CWebSite::put_ftpPassword(BSTR newVal)
{
	m_ftpPassword = newVal;
	return S_OK;
}
*/

#if 0
STDMETHODIMP CWebSite::OpenDocument(DWORD file_id, VARIANT_BOOL *pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;

	*pSuccess = VARIANT_FALSE;

	CComQIPtr<IEDocument> pDocument;

	/*
	TCHAR ext[512];
	_splitpath(_bstr_t(pathName), NULL, NULL, NULL, ext);


	if (!stricmp(ext, ".htm") ||
		!stricmp(ext, ".html") ||
		!stricmp(ext, ".shtml") ||
		!stricmp(ext, ".asp") ||

		!stricmp(ext, ".svg") ||

		!stricmp(ext, ".smil") ||
		!stricmp(ext, ".smi") ||

		!stricmp(ext, ".xml") ||
		!stricmp(ext, ".xsd") ||

		!stricmp(ext, ".wmf") ||
		!stricmp(ext, ".emf"))
	*/
	{
#if 0
		pDocument.CoCreateInstance(CLSID_EXMLDocument);
#endif
	}
/*
	else if (!stricmp(ext, ".css"))
	{
	//	pDocument = new CCSSDocument;
	}
	else
	{
	//	pDocument = new CTextDocument;
	}
*/
	if (pDocument != NULL)
	{
		SAFEARRAY* dataArray = NULL;

		VARIANT_BOOL success;
		dataArray;
		m_webSite->OpenFileAsArray(file_id, &dataArray);

		if (dataArray)
		{
#if 0
			pDocument->LoadDocumentByteArray(dataArray, &success);
			if (success)
			{
#if 0
				pDocument->ShowViews();
#endif

				//CComQIPtr<IUIContextManager> uiManager = gApp->m_uiManager;

				CComQIPtr<IUIManager> uiManager = gApp->m_frame;
				uiManager->ActivateObject(NULL, pDocument);

				*pSuccess = VARIANT_TRUE;
			}
#endif
		}

		if (dataArray)
			SafeArrayDestroy(dataArray);
	}

	return S_OK;
}
#endif

__int64 GetTotalSizeOfFiles(LPTSTR filepath)
{
	__int64 nSize = 0;

	DWORD attributes = GetFileAttributes(filepath);
	TCHAR* filepart = PathFindFileName(filepath);

	if (attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		HANDLE hFindFile;
		WIN32_FIND_DATA	wfd;

		char	search[MAX_PATH];
		wsprintf(search, "%s\\*.*", filepath);

		if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (wfd.cFileName[0] != '.')
				{
					if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						char pathName[_MAX_PATH];
						_makepath(pathName, NULL, filepath, wfd.cFileName, NULL);

						nSize += GetTotalSizeOfFiles(pathName);
					}
					else
					{
						nSize += wfd.nFileSizeLow;
					}
				}
			}
			while (FindNextFile(hFindFile, &wfd));

			FindClose(hFindFile);
		}
	}
	else
	{
		nSize += GetFileSize(filepath, NULL);
	}

	return nSize;
}

#include "ProgressDlg.h"

long CWebSite::CopyMoveFile(DWORD folder_id, _bstr_t filepath, VARIANT_BOOL bSilent, CProgressDlg* dlg)
{
	USES_CONVERSION;

	long nFilesCopied = 0;

	DWORD attributes = GetFileAttributes(filepath);
	TCHAR* filepart = PathFindFileName(filepath);

	if (attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		// Does A2BSTR require SysFreeString afterwards?
		folder_id;
		m_webSite->FindOrCreateFolder(folder_id, A2BSTR(filepart), L"", &folder_id);

		if (folder_id)
		{
			HANDLE hFindFile;
			WIN32_FIND_DATA	wfd;

			char	search[MAX_PATH];
			wsprintf(search, "%S\\*.*", (BSTR)filepath);

			if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (wfd.cFileName[0] != '.')
					{
						char pathName[_MAX_PATH];
						_makepath(pathName, NULL, filepath, wfd.cFileName, NULL);

						nFilesCopied += CopyMoveFile(folder_id, pathName, bSilent, dlg);

						if (dlg)
						{
							if (dlg->m_bCancel) break;
						}
					}
				}
				while (FindNextFile(hFindFile, &wfd));

				FindClose(hFindFile);
			}
		}
		else
		{
			if (!bSilent)
			{
				CUString str;
				str.Format("Couldn't create folder %S", (BSTR)filepath);
				MessageBox(NULL, str, "WebEditor", MB_OK);
			}
		}
	}
	else
	{
		SAFEARRAY* dataArray = NULL;
		long dataSize = 0;

		FILE* fp = fopen(filepath, "rb");
		if (fp)
		{
			fseek(fp, 0, SEEK_END);
			dataSize = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			dataArray = SafeArrayCreateVector(VT_UI1, 0, dataSize);
			if (dataArray)
			{
				fread((dataArray)->pvData, 1, dataSize, fp);
			}

			fclose(fp);
		}
		else
		{
			if (!bSilent)
			{
				CUString str;
				str.Format("Couldn't open %S", (BSTR)filepath);
				MessageBox(NULL, str, "WebEditor", MB_OK);
			}
		}

		if (dataArray)
		{
			DWORD file_id;

			VARIANT_BOOL success;
			m_webSite->SaveArrayAsFile(folder_id, _bstr_t(filepart), dataArray, L"", &file_id, &success);

			SafeArrayDestroy(dataArray);

			if (success)
			{
				nFilesCopied++;
			}
			else
			{
				if (!bSilent)
				{
					CUString str;
					str.Format("Failed to copy %s", filepart);
					MessageBox(NULL, str, "WebEditor", MB_OK);
				}
			}
		}

		if (dlg)
		{
			dlg->m_pos += dataSize/10;
			dlg->Invalidate();

			MSG msg;
			while (PeekMessage(&msg, dlg->m_hWnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return nFilesCopied;
}

STDMETHODIMP CWebSite::CopyMoveFile(DWORD folder_id, BSTR filepath, VARIANT_BOOL bSilent, long *nFilesCopied)
{
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = 1;
   SAFEARRAY* sa = SafeArrayCreate(VT_BSTR, 1, rgsabound);
	if (sa)
	{
		long ix[1];
		ix[0] = 0;
		SafeArrayPutElement(sa, ix, filepath);

		CopyMoveFiles(folder_id, sa, bSilent, nFilesCopied);

		SafeArrayDestroy(sa);
	}

	return S_OK;
}

STDMETHODIMP CWebSite::CopyMoveFiles(/*[in]*/ DWORD folder_id, /*[in]*/ SAFEARRAY* sa, /*[in]*/ VARIANT_BOOL bSilent, /*[out,retval]*/ long* nFilesCopied)
{
	if (nFilesCopied == NULL) return E_POINTER;

//	CProgressDlg dlg;
//	dlg.Create(NULL/*GetMainHwnd()*/, NULL);

	int i;

	__int64 nSize = 0;
	for (i = 0; i < sa->rgsabound[0].cElements; i++)
	{
		long ix[1];
		ix[0] = i;

		BSTR bstr;
		SafeArrayGetElement(sa, ix, (void**)&bstr);

		nSize += GetTotalSizeOfFiles(_bstr_t(bstr));
	}

//	dlg.m_min = 0;
//	dlg.m_max = nSize/10;
//	dlg.m_pos = 0;

	for (i = 0; i < sa->rgsabound[0].cElements; i++)
	{
		long ix[1];
		ix[0] = i;

		BSTR bstr;
		SafeArrayGetElement(sa, ix, (void**)&bstr);

		(*nFilesCopied) += CopyMoveFile(folder_id, _bstr_t(bstr), bSilent, NULL/*&dlg*/);
	}

//	dlg.DestroyWindow();

	return S_OK;
}

BEGIN_CMD_MAP(CWebSite)
	CMD_HANDLER(ID_FILE_SITESETTINGS, OnSiteSettings)

//	CMD_HANDLER(&ID_SITE_RESCAN, OnRescan)
	CMD_HANDLER(ID_WINDOW_NEW, OnWindowNew)
/*
	CMD_HANDLER(&ID_SITE_FTP_CONNECT, OnFTPConnect)
	CMD_HANDLER(&ID_SITE_FTP_DISCONNECT, OnFTPDisconnect)
*/
END_CMD_MAP()

#include "LXWebSiteApp.h"

#include "SettingsFilenameConstraintsDlg.h"
#include "SettingsServersDlg.h"

LRESULT CWebSite::OnSiteSettings(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComQIPtr<ILXAddin> app = m_app;

	CComPtr<ILXAddinSite> addinSite;
	app->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	HWND hWnd;
	frame->get_hwnd(&hWnd);

	CPropertySheet sheet("WebSite Settings", 0, hWnd);
	sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	CSettingsFilenameConstraintsDlg filenameconstraints;

	CSettingsServersDlg servers;
	servers.m_pApp = static_cast<CLXWebSiteApp*>(m_app.p);
	servers.m_ftpServerName = m_ftpServerName;

	sheet.AddPage(filenameconstraints);
	sheet.AddPage(servers);

	if (sheet.DoModal() == IDOK)
	{
		m_ftpServerName = servers.m_ftpServerName;
	}

	return 0;
}

LRESULT CWebSite::OnWindowNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	NewWindow();
	return 0;
}

LRESULT CWebSite::OnFTPConnect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CWebSite::OnFTPDisconnect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

/*
void CWebSite::OnRescan(GUID* iid)
{
}
*/
