// FEOffset.h : Declaration of the CFEOffset

#ifndef __FEOFFSET_H_
#define __FEOFFSET_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFEOffset
class ATL_NO_VTABLE CFEOffset : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFEOffset, &CLSID_FEOffset>,
	public IDispatchImpl<IFEOffset, &IID_IFEOffset, &LIBID_PAGEDESIGNERLib>,
	public IPluginFilter,
	public IObjectSerializable
{
public:
	CFEOffset()
	{
		m_dx = 10;
		m_dy = 10;
	}

	double m_dx;
	double m_dy;

	CComPtr<IPluginFilterClass> m_pluginFilterClass;

DECLARE_REGISTRY_RESOURCEID(IDR_FEOFFSET)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFEOffset)
	COM_INTERFACE_ENTRY(IFEOffset)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IPluginFilter)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IFEOffset
public:
	STDMETHOD(get_dy)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_dx)(/*[out, retval]*/ double *pVal);
	STDMETHOD(GetPluginFilterClass)(/*[out,retval]*/ IPluginFilterClass* *pVal);
	STDMETHOD(SetPluginFilterClass)(/*[in]*/ IPluginFilterClass* newVal);
	STDMETHOD(ShowOptions)(/*[in]*/ HWND hParent);
// IPluginFilter
	STDMETHODIMP GetInPinCount(long* pVal);
	STDMETHODIMP GetInPinType(long n, long* pVal);
	STDMETHODIMP GetResultType(long* pVal);
	STDMETHODIMP GetName(BSTR* pVal);
	STDMETHODIMP FrameSetup(DWORD filterRecord);
	STDMETHODIMP FrameSetdown(DWORD filterRecord);
	STDMETHODIMP Filter(DWORD filterRecord);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_FEOffset;
		return S_OK;
	}
};

#endif //__FEOFFSET_H_
