#include "resource.h"

#include "PDSwatchImpl.h"

class CPDGradient;

class ATL_NO_VTABLE CPDSwatchGradient : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDSwatchGradient, &CLSID_PDSwatchGradient>,
	public CPDSwatchImpl<CPDSwatchGradient, IPDSwatchGradient>,
	public IObjectSerializable
{
public:
	CPDSwatchGradient()
	{
		m_gradient = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CComObject<CPDGradient>* m_gradient;

DECLARE_REGISTRY_RESOURCEID(IDR_PDSWATCHGRADIENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSwatchGradient)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSwatch)
	COM_INTERFACE_ENTRY(IPDSwatchGradient)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// IPDSwatchGradient
public:
	STDMETHOD(clone)(/*[out,retval]*/ IPDSwatch* *pVal);
	STDMETHOD(get_gradient)(/*[out, retval]*/ IPDGradient* *pVal);
	STDMETHOD(put_gradient)(/*[in]*/ IPDGradient* newVal);
	STDMETHOD(get_swatchType)(PDSwatchType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = SWATCH_GRADIENT;
		return S_OK;
	}
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
