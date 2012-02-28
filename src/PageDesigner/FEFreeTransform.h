// FEFreeTransform.h : Declaration of the CFEFreeTransform

#ifndef __FEFREETRANSFORM_H_
#define __FEFREETRANSFORM_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFEFreeTransform
class ATL_NO_VTABLE CFEFreeTransform : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFEFreeTransform, &CLSID_FEFreeTransform>,
	public IDispatchImpl<IFEFreeTransform, &IID_IFEFreeTransform, &LIBID_PAGEDESIGNERLib>,
	public IPluginFilter
{
public:
	CFEFreeTransform()
	{
		m_left = 0;
		m_top = 0;
		m_right = 1;
		m_bottom = 1;
	}

	double m_left;
	double m_top;
	double m_right;
	double m_bottom;

DECLARE_REGISTRY_RESOURCEID(IDR_FEFREETRANSFORM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFEFreeTransform)
	COM_INTERFACE_ENTRY(IFEFreeTransform)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IPluginFilter)
END_COM_MAP()

// IFEFreeTransform
public:
	STDMETHOD(GetPluginFilterClass)(/*[out,retval]*/ IPluginFilterClass* *pVal);
	STDMETHOD(SetPluginFilterClass)(/*[in]*/ IPluginFilterClass* newVal);
// IPluginFilter
	STDMETHOD(ShowOptions)(/*[in]*/ HWND hParent);
	STDMETHOD(GetInPinCount)(long* pVal);
	STDMETHOD(GetInPinType)(long n, long* pVal);
	STDMETHOD(GetResultType)(long* pVal);
	STDMETHOD(GetName)(BSTR* pVal);
	STDMETHOD(FrameSetup)(DWORD filterRecord);
	STDMETHOD(FrameSetdown)(DWORD filterRecord);
	STDMETHOD(Filter)(DWORD filterRecord);
};

#endif //__FEFREETRANSFORM_H_
