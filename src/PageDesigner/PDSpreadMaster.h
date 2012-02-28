#include "resource.h"

class CObjectMap;
class CPDDocument;

#include "PDSpreadImpl.h"

class ATL_NO_VTABLE CPDSpreadMaster : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDSpreadMaster, &CLSID_PDSpreadMaster>,
	public CPDSpreadImpl<IPDSpreadMaster>
{
public:
	CPDSpreadMaster()
	{
	}
	
	HRESULT FinalConstruct();
	void FinalRelease();

	_bstr_t m_prefix;
	_bstr_t m_name;

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDSPREADMASTER)

BEGIN_COM_MAP(CPDSpreadMaster)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSpread)
	COM_INTERFACE_ENTRY(IPDSpreadMaster)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IPDSpreadMaster
public:
//	STDMETHOD(removeLayerGroup)(/*[in]*/ IPDObjectLayerGroup* object);
	STDMETHOD(get_prefix)(BSTR *pVal);
	STDMETHOD(put_prefix)(BSTR newVal);
	STDMETHOD(get_name)(BSTR *pVal);
	STDMETHOD(put_name)(BSTR newVal);
// IObjectSerializable
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDSpreadMaster;
		return S_OK;
	}
};
