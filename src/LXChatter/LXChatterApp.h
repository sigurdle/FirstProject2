// LXChatterApp.h : Declaration of the CLXChatterApp

#ifndef __LXCHATTERAPP_H_
#define __LXCHATTERAPP_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLXChatterApp
class ATL_NO_VTABLE CLXChatterAddinApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXChatterApp, &CLSID_LXChatterApp>,
	public IDispatchImpl<ILXChatterApp, &IID_ILXChatterApp, &LIBID_LXCHATTERLib>
{
public:
	CLXChatterAddinApp()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LXCHATTERADDINAPP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXChatterAddinApp)
	COM_INTERFACE_ENTRY(ILXChatterAddinApp)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ILXChatterApp
public:
};

#endif //__LXCHATTERAPP_H_
