#pragma once

class ATL_NO_VTABLE CObjectMap : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IObjectMap,
	public IObjectSerializable
{
public:
	CObjectMap()
	{
	}
	
	void FinalRelease();

	CArray<IUnknown*,IUnknown*> m_items;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CObjectMap)
	COM_INTERFACE_ENTRY(IObjectMap)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IObjectMap
public:
	STDMETHOD(get_length)(long *pVal);
	STDMETHOD(item)(long index, IUnknown** pVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_NULL;//IID_IObjectMap;
		return 0;
	}
};
