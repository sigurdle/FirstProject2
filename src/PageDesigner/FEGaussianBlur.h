// FEGaussianBlur.h : Declaration of the CFEGaussianBlur

#ifndef __FEGAUSSIANBLUR_H_
#define __FEGAUSSIANBLUR_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFEGaussianBlur
class ATL_NO_VTABLE CFEGaussianBlur : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFEGaussianBlur, &CLSID_FEGaussianBlur>,
	public IDispatchImpl<IFEGaussianBlur, &IID_IFEGaussianBlur, &LIBID_PAGEDESIGNERLib>,
	public IPluginFilter,
	public IObjectSerializable
{
public:
	CFEGaussianBlur()
	{
		m_blurx = 5;
		m_blury = 5;
	}

	double m_blurx;
	double m_blury;

	CComPtr<IPluginFilterClass> m_pluginFilterClass;

DECLARE_REGISTRY_RESOURCEID(IDR_FEGAUSSIANBLUR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFEGaussianBlur)
	COM_INTERFACE_ENTRY(IFEGaussianBlur)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IPluginFilter)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IFEGaussianBlur
public:
	STDMETHOD(setStdDeviation)(/*[in]*/ double stdDeviationX, /*[in]*/ double stdDeviationY);
	STDMETHOD(get_stdDeviationY)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_stdDeviationX)(/*[out, retval]*/ double *pVal);
	STDMETHOD(GetPluginFilterClass)(/*[out,retval]*/ IPluginFilterClass* *pVal);
	STDMETHOD(SetPluginFilterClass)(/*[in]*/ IPluginFilterClass* newVal);
// IPluginFilter
	STDMETHOD(ShowOptions)(/*[in]*/ HWND hParent);
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
		*pClassID = CLSID_FEGaussianBlur;
		return S_OK;
	}
};

#endif //__FEGAUSSIANBLUR_H_
