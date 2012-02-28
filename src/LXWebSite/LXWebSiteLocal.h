// LXWebSiteLocal.h : Declaration of the CLXWebSiteLocal

#ifndef __LXWEBSITELOCAL_H_
#define __LXWEBSITELOCAL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLXWebSiteLocal
class ATL_NO_VTABLE CLXWebSiteLocal : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXWebSiteLocal, &CLSID_LXWebSiteLocal>,
	public IConnectionPointContainerImpl<CLXWebSiteLocal>,
	public IDispatchImpl<ILXWebSiteLocal, &IID_ILXWebSiteLocal, &LIBID_LXWEBSITELib>
{
public:
	CLXWebSiteLocal()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LXWEBSITELOCAL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXWebSiteLocal)
	COM_INTERFACE_ENTRY(ILXWebSiteLocal)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CLXWebSiteLocal)
END_CONNECTION_POINT_MAP()


// ILXWebSiteLocal
public:
};

#endif //__LXWEBSITELOCAL_H_
