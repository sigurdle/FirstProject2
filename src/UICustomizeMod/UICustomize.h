// UICustomize.h : Declaration of the CUICustomize

#ifndef __UICUSTOMIZE_H_
#define __UICUSTOMIZE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUICustomize
class ATL_NO_VTABLE CUICustomize : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUICustomize, &CLSID_UICustomize>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CUICustomize>,
	public IDispatchImpl<IUICustomize, &IID_IUICustomize, &LIBID_UICUSTOMIZEMODLib>
{
public:
	CUICustomize()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_UICUSTOMIZE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUICustomize)
	COM_INTERFACE_ENTRY(IUICustomize)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CUICustomize)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUICustomize
public:
	STDMETHOD(Show)(/*[in]*/ IUnknown* uiManager, /*[in]*/ long hParent);
};

#endif //__UICUSTOMIZE_H_
