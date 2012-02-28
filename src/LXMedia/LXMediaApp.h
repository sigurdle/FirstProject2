// LXMediaApp.h : Declaration of the CLXMediaApp

#ifndef __LXMEDIAAPP_H_
#define __LXMEDIAAPP_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLXMediaApp
class ATL_NO_VTABLE CLXMediaApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXMediaApp, &CLSID_LXMediaApp>,
	public IDispatchImpl<ILXMediaApp, &IID_ILXMediaApp, &LIBID_LXMEDIALib>,

	public ILXAddin,
	public IUIManagerSite,

	public ProcessTargetCommands
{
public:
	CLXMediaApp()
	{
	}

	CComPtr<ILXAddinSite> m_spAddinSite;

DECLARE_REGISTRY_RESOURCEID(IDR_LXMEDIAAPP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXMediaApp)
	COM_INTERFACE_ENTRY(ILXMediaApp)
	COM_INTERFACE_ENTRY(ILXAddin)
	COM_INTERFACE_ENTRY(IUIManagerSite)

	COM_INTERFACE_ENTRY(ICommandTarget)

	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

DECLARE_CMD_MAP(CLXMediaApp)

	LRESULT OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// ILXMediaApp
public:

// ILXApp
	STDMETHOD(GetSite)(ILXAddinSite* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_spAddinSite;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(SetSite)(ILXAddinSite* pSite);

	STDMETHOD(CreateDlg)(UINT nID, IUIDlg* *pVal);

	STDMETHOD(BindToObjectMoniker)(IMoniker* mk, IBindCtx* ctx, IUnknown* *pVal)
	{
		return E_FAIL;
	}
};

#endif //__LXMEDIAAPP_H_
