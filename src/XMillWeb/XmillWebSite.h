// XmillWebSite.h : Declaration of the CXmillWebSite

#ifndef __XMILLWEBSITE_H_
#define __XMILLWEBSITE_H_

#include "resource.h"       // main symbols
#include <mtx.h>

/////////////////////////////////////////////////////////////////////////////
// CXmillWebSite
class ATL_NO_VTABLE CXmillWebSite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXmillWebSite, &CLSID_XmillWebSite>,
	public IObjectControl,
	public IDispatchImpl<IXmillWebSite, &IID_IXmillWebSite, &LIBID_XMILLWEBLib>
{
public:
	CXmillWebSite()
	{
	}

	ADODB::_ConnectionPtr m_conn;

DECLARE_REGISTRY_RESOURCEID(IDR_XMILLWEBSITE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_NOT_AGGREGATABLE(CXmillWebSite)

BEGIN_COM_MAP(CXmillWebSite)
	COM_INTERFACE_ENTRY(IXmillWebSite)
	COM_INTERFACE_ENTRY(IObjectControl)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IObjectControl
public:
	STDMETHOD(Activate)();
	STDMETHOD_(BOOL, CanBePooled)();
	STDMETHOD_(void, Deactivate)();

	CComPtr<IObjectContext> m_spObjectContext;

// IXmillWebSite
public:
};

#endif //__XMILLWEBSITE_H_
