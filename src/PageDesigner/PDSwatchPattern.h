// PDSwatchPattern.h : Declaration of the CPDSwatchPattern

#ifndef __PDSWATCHPATTERN_H_
#define __PDSWATCHPATTERN_H_

#include "resource.h"       // main symbols

#include "PDSwatchImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CPDSwatchPattern
class ATL_NO_VTABLE CPDSwatchPattern : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDSwatchPattern, &CLSID_PDSwatchPattern>,
	public CPDSwatchImpl<CPDSwatchPattern, IPDSwatchPattern>,
	public IObjectSerializable
{
public:
	CPDSwatchPattern()
	{
	}

	CComPtr<IPDObjectGroup> m_objectGroup;

DECLARE_REGISTRY_RESOURCEID(IDR_PDSWATCHPATTERN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSwatchPattern)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSwatch)
	COM_INTERFACE_ENTRY(IPDSwatchPattern)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// IPDSwatchPattern
public:
	STDMETHOD(get_objectGroup)(/*[out, retval]*/ IPDObjectGroup* *pVal);
	STDMETHOD(put_objectGroup)(/*[in]*/ IPDObjectGroup* newVal);
	STDMETHOD(clone)(/*[out,retval]*/ IPDSwatch* *pVal);
	STDMETHOD(get_swatchType)(PDSwatchType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = SWATCH_PATTERN;
		return S_OK;
	}
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDSwatchPattern;
		return S_OK;
	}
};

#endif //__PDSWATCHPATTERN_H_
