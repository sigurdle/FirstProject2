// PDSymbol.h : Declaration of the CPDSymbol

#ifndef __PDSYMBOL_H_
#define __PDSYMBOL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPDSymbol
class ATL_NO_VTABLE CPDSymbol : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDSymbol, &CLSID_PDSymbol>,
	public IPDSymbol,
	public IObjectSerializable,
	public CNotifySendImpl<CPDSymbol>
{
public:
	CPDSymbol()
	{
	}

	_bstr_t m_name;
	CComPtr<IPDObject> m_symbolObject;

DECLARE_REGISTRY_RESOURCEID(IDR_PDSYMBOL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSymbol)
	COM_INTERFACE_ENTRY(IPDSymbol)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// IPDSymbol
public:
	STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_symbolObject)(/*[out, retval]*/ IPDObject* *pVal);
	STDMETHOD(put_symbolObject)(/*[in]*/ IPDObject* newVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDSymbol;
		return S_OK;
	}
};

#endif //__PDSYMBOL_H_
