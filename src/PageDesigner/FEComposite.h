// FEComposite.h : Declaration of the CFEComposite

#ifndef __FECOMPOSITE_H_
#define __FECOMPOSITE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFEComposite
class ATL_NO_VTABLE CFEComposite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFEComposite, &CLSID_FEComposite>,
	public IDispatchImpl<IFEComposite, &IID_IFEComposite, &LIBID_PAGEDESIGNERLib>,
	public IPluginFilter,
	public IObjectSerializable
{
public:
	CFEComposite()
	{
		m_op = 0;	// Over
	}

	long m_op;
	
	CComPtr<IPluginFilterClass> m_pluginFilterClass;

DECLARE_REGISTRY_RESOURCEID(IDR_FECOMPOSITE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFEComposite)
	COM_INTERFACE_ENTRY(IFEComposite)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IPluginFilter)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

public:
	STDMETHOD(get_op)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_op)(/*[in]*/ long newVal);
	STDMETHOD(GetPluginFilterClass)(/*[out,retval]*/ IPluginFilterClass* *pVal);
	STDMETHOD(SetPluginFilterClass)(/*[in]*/ IPluginFilterClass* newVal);
// IFEComposite
// IPluginFilter
	STDMETHOD(ShowOptions)(/*[in]*/ HWND hParent);
	STDMETHOD(GetInPinCount)(long* pVal);
	STDMETHOD(GetInPinType)(long n, long* pVal);
	STDMETHOD(GetResultType)(long* pVal);
	STDMETHOD(GetName)(BSTR* pVal);
	STDMETHOD(FrameSetup)(DWORD filterRecord);
	STDMETHOD(FrameSetdown)(DWORD filterRecord);
	STDMETHOD(Filter)(DWORD filterRecord);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_FEComposite;
		return S_OK;
	}
};

#endif //__FECOMPOSITE_H_
