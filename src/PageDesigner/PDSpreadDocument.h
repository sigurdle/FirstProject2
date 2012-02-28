#pragma once

#include "resource.h"

class CObjectMap;
class CPDDocument;

#include "PDSpreadImpl.h"

class ATL_NO_VTABLE CPDSpreadDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDSpreadDocument, &CLSID_PDSpreadDocument>,
	public CPDSpreadImpl<IPDSpreadDocument>
{
public:
	CPDSpreadDocument()
	{
		m_keepSpreadTogether = VARIANT_FALSE;

		m_previousSpread = NULL;
		m_nextSpread = NULL;
	}

	HRESULT FinalConstruct();
	void FinalRelease();

	VARIANT_BOOL m_keepSpreadTogether;

	CComObject<CPDSpreadDocument>* m_previousSpread;
	CComObject<CPDSpreadDocument>* m_nextSpread;

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDSPREADDOCUMENT)

BEGIN_COM_MAP(CPDSpreadDocument)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSpread)
	COM_INTERFACE_ENTRY(IPDSpreadDocument)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IPDSpreadDocument
public:
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
//	STDMETHOD(get_lastLayerGroup)(/*[out, retval]*/ IPDObjectUnknown* *pVal);
//	STDMETHOD(get_firstLayerGroup)(/*[out, retval]*/ IPDObjectUnknown* *pVal);
//	STDMETHOD(removeLayerGroup)(/*[in]*/ IPDObjectLayerGroup* object);
	STDMETHOD(get_keepSpreadTogether)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_keepSpreadTogether)(/*[in]*/ VARIANT_BOOL newVal);
};
