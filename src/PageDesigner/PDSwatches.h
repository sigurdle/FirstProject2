#pragma once

template <class IBase> class CPDSwatch;
template <class T, class IBase> class CPDSwatchImpl;

class CObjectMap;

class ATL_NO_VTABLE CPDSwatches : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDSwatches,
	public IObjectSerializable,
	public CNotifyGetImpl<CPDSwatches>,
	public CNotifySendImpl<CPDSwatches>
{
public:
	CPDSwatches()
	{
		m_firstChild = NULL;
		m_lastChild = NULL;
		m_swatches = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CComObject<CObjectMap>* m_swatches;
	//CArray<IPDSwatch*,IPDSwatch*> m_items;

	CPDSwatch<IPDSwatch>* m_firstChild;
	CPDSwatch<IPDSwatch>* m_lastChild;

	HRESULT insertSwatch(IPDSwatch* object, IPDSwatch* before);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSwatches)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSwatches)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// IPDSwatches
public:
	STDMETHOD(get_lastChild)(/*[out, retval]*/ IPDSwatch* *pVal);
	STDMETHOD(get_firstChild)(/*[out, retval]*/ IPDSwatch* *pVal);
	STDMETHOD(removeSwatch)(/*[in]*/ IPDSwatch* swatch);
	STDMETHOD(appendSwatch)(/*[in]*/ IPDSwatch* swatch);
	STDMETHOD(item)(/*[in]*/ long index, /*[out,retval]*/ IPDSwatch* *pVal);
	STDMETHOD(get_length)(/*[out, retval]*/ long *pVal);
	STDMETHOD(createSwatchTint)(/*[in]*/ IPDSwatchColor* swatchColor, /*[out,retval]*/ IPDSwatchTint* *pVal);
	STDMETHOD(createSwatchGradient)(/*[out,retval]*/ IPDSwatchGradient* *pVal);
	STDMETHOD(createSwatchColor)(/*[out,retval]*/ IPDSwatchColor* *pVal);
	STDMETHOD(createSwatchPattern)(/*[out,retval]*/ IPDSwatchPattern* *pVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
