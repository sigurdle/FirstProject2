#include "resource.h"

#include "PDSwatchImpl.h"

class CPDColor;

class ATL_NO_VTABLE CPDSwatchColor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDSwatchColor, &CLSID_PDSwatchColor>,
	public CPDSwatchImpl<CPDSwatchColor, IPDSwatchColor>,
	public IObjectSerializable,
	public CNotifyGetImpl<CPDSwatchColor>
{
public:
	CPDSwatchColor()
	{
		m_color = NULL;
		m_nameWithColorValue = VARIANT_TRUE;
		m_colorType = COLORTYPE_PROCESS;
	}

	int FinalConstruct();
	void FinalRelease();

	PDColorType m_colorType;
	VARIANT_BOOL m_nameWithColorValue;
	CComObject<CPDColor>* m_color;

DECLARE_REGISTRY_RESOURCEID(IDR_PDSWATCHCOLOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSwatchColor)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSwatch)
	COM_INTERFACE_ENTRY(IPDSwatchColor)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// IPDSwatchColor
public:
	STDMETHOD(get_colorType)(/*[out, retval]*/ PDColorType *pVal);
	STDMETHOD(put_colorType)(/*[in]*/ PDColorType newVal);
	STDMETHOD(get_swatchType)(PDSwatchType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = SWATCH_COLOR;
		return S_OK;
	}

	STDMETHOD(get_nameWithColorValue)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_nameWithColorValue)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_name)(BSTR *pVal);
//	STDMETHOD(put_name)(BSTR newVal);
	STDMETHOD(clone)(/*[out,retval]*/ IPDSwatch* *pVal);
	STDMETHOD(get_color)(IPDColor* *pVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
