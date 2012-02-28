// LXDatabaseApp.h : Declaration of the CLXDatabaseApp

#ifndef __LXDATABASEAPP_H_
#define __LXDATABASEAPP_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLXDatabaseApp
class ATL_NO_VTABLE CLXDatabaseApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXDatabaseApp, &CLSID_LXDatabaseApp>,
	public IDispatchImpl<ILXDatabaseApp, &IID_ILXDatabaseApp, &LIBID_LXDATABASELib>
{
public:
	CLXDatabaseApp()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LXDATABASEAPP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXDatabaseApp)
	COM_INTERFACE_ENTRY(ILXDatabaseApp)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ILXDatabaseApp
public:
};

#endif //__LXDATABASEAPP_H_
