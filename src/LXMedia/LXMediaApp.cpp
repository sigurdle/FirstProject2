// LXMediaApp.cpp : Implementation of CLXMediaApp
#include "stdafx.h"
#include "LXMedia.h"
#include "LXMedia2.h"
#include "LXMediaApp.h"

/////////////////////////////////////////////////////////////////////////////
// CLXMediaApp

STDMETHODIMP CLXMediaApp::CreateDlg(UINT nID, IUIDlg* *pVal)
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
	}

	return S_OK;
}

STDMETHODIMP CLXMediaApp::SetSite(ILXAddinSite* pSite)
{
	m_spAddinSite = pSite;

	if (m_spAddinSite)
	{
		CComPtr<ILXFrameworkFrame> lxframe;
		m_spAddinSite->GetFrame(&lxframe);

		CComQIPtr<IUIFrame> frame = lxframe;

		CComPtr<IUIManager> uiManager;
		m_spAddinSite->GetUIManager((IUnknown**)&uiManager);

		{
			CComPtr<IUIRegisteredDlg> rdlg;
			uiManager->RegisterDlg(70/*TODO?IDR_MAINFRAME*/, L"Menubar", 0, &rdlg);

			CComPtr<IUIDlg> dlg;
			rdlg->CreateDlg(&dlg);

			CComPtr<IUIDlgSite> dlgsite;
			uiManager->CreateDlgSite(dlg, &dlgsite);

			frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
		}
	}

	return S_OK;
}

BEGIN_CMD_MAP(CLXMediaApp)
// File
//	CMD_HANDLER(ID_FILE_NEW, OnFileNew)
	CMD_HANDLER(ID_FILE_OPEN, OnFileOpen)
END_CMD_MAP()

LRESULT CLXMediaApp::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	HWND hWnd;
	frame->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"MPEG (*.mpg,*.mpe,*.mpeg)\0*.mpg;*.mpe;*.mpeg\0"
												"IFF (*.iff)\0*.iff\0"
												"JPEG (*.jpg,*.jpeg)\0*.jpg;*.jpeg\0"
												"GIF (*.gif)\0*.gif\0"
												"TIFF (*.tif,*.tiff)\0*.tif;*.tiff\0"
												"PCX (*.pcx)\0*.pcx\0"
												"AIFF (*.aif,*.aiff)\0*.aif;*.aiff\0"
												"VOC (*.voc)\0*.voc\0"
												"Sun AU (*.au)\0*.au\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;//sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	
	if (GetOpenFileName(&ofn))
	{
		CComQIPtr<IEFrame> eframe = lxframe;

		CComPtr<IEDocument> document;
		HRESULT hr = document.CoCreateInstance(CLSID_EMediaClipDocument);
		if (SUCCEEDED(hr))
		{
			document->SetApp(this);

			CComQIPtr<IPersistFile> persistFile = document;
			persistFile->Load(A2W(sbuffer), STGM_READ);

			document->ShowViews(eframe);
		}

		document.Detach();	// TODO, add in a list

		/*
		VARIANT_BOOL success;
		OpenDocument(_bstr_t(sbuffer), &success);
		*/
	}

	return 0;
}
