#include "resource.h"

#include "PDSwatchImpl.h"

class ATL_NO_VTABLE CPDSwatchNone : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDSwatchNone, &CLSID_PDSwatchNone>,
	public CPDSwatchImpl<CPDSwatchNone, IPDSwatch>,
	public IObjectSerializable
{
public:
	CPDSwatchNone()
	{
		m_canEdit = VARIANT_FALSE;
		m_canDelete = VARIANT_FALSE;
	}

	int FinalConstruct()
	{
		m_name = SysAllocString(L"[None]");
		return S_OK;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PDSWATCHNONE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSwatchNone)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSwatch)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// IPDSwatch
public:
	STDMETHOD(clone)(/*[out,retval]*/ IPDSwatch* *pVal);
	STDMETHOD(get_swatchType)(PDSwatchType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = SWATCH_NONE;
		return S_OK;
	}
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node)
	{
		return S_OK;
	}
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		return S_OK;
	}
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDSwatchNone;
		return S_OK;
	}
};
