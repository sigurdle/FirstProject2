// LXWebSiteApp.h : Declaration of the CLXWebSiteApp

#ifndef __LXWEBSITEAPP_H_
#define __LXWEBSITEAPP_H_

#include "resource.h"       // main symbols

#include "Server.h"

/////////////////////////////////////////////////////////////////////////////
// CLXWebSiteApp
class ATL_NO_VTABLE CLXWebSiteApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXWebSiteApp, &CLSID_LXWebSiteApp>,
	public IDispatchImpl<ILXWebSiteApp, &IID_ILXWebSiteApp, &LIBID_LXWEBSITELib>,

	public ILXAddin,
	public IUIManagerSite,
	public ProcessTargetCommands
{
public:
	CLXWebSiteApp()
	{
	}

	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
		for (int i = 0; i < m_servers.GetSize(); i++)
		{
			m_servers[i]->Release();
		}
		m_servers.RemoveAll();
	}

	CComPtr<ILXAddinSite> m_spAddinSite;

	CArray<CComObject<CServer>*,CComObject<CServer>*> m_servers;

	CServer* GetServerByName(BSTR serverName)
	{
		for (int i = 0; i < m_servers.GetSize(); i++)
		{
			if (!wcscmp(serverName, m_servers[i]->m_name))
			{
				return m_servers[i];
			}
		}

		return NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LXWEBSITEAPP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXWebSiteApp)
	COM_INTERFACE_ENTRY(ILXWebSiteApp)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILXAddin)
	COM_INTERFACE_ENTRY(IUIManagerSite)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

DECLARE_CMD_MAP(CLXWebSiteApp)

	LRESULT OnFileNewSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileOpenSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileMountWorkgroupSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnFileFTPBrowser(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileWebDAVBrowser(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnFileServers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// ILXWebSiteApp
public:
// ILXAddin
	STDMETHOD(GetSite)(ILXAddinSite* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_spAddinSite;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(SetSite)(ILXAddinSite* pSite);
	STDMETHOD(BindToObjectMoniker)(IMoniker* mk, IBindCtx* ctx, IUnknown* *pVal)
	{
		return E_FAIL;
	}
//	STDMETHOD(CreateDlg)(UINT nID, IUIDlg* *pVal);
};

#endif //__LXWEBSITEAPP_H_
