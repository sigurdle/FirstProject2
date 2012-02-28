// PDObjectSymbolInstanceSet.h : Declaration of the CPDObjectSymbolInstanceSet

#ifndef __PDOBJECTSYMBOLINSTANCESET_H_
#define __PDOBJECTSYMBOLINSTANCESET_H_

#include "resource.h"       // main symbols

#include "PDObjectImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CPDObjectSymbolInstanceSet
class ATL_NO_VTABLE CPDObjectSymbolInstanceSet : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDObjectSymbolInstanceSet, &CLSID_PDObjectSymbolInstanceSet>,
	public CPDObjectImpl<IPDObjectSymbolInstanceSet>,
	public CNotifySendImpl<CPDObjectSymbolInstanceSet>
{
public:
	CPDObjectSymbolInstanceSet()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	virtual void CalculateBounds();
	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* graphics, double scaleX, double scaleY);

DECLARE_REGISTRY_RESOURCEID(IDR_PDOBJECTSYMBOLINSTANCESET)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDObjectSymbolInstanceSet)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectSymbolInstanceSet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IPDObjectSymbolInstanceSet
public:
	STDMETHOD(getExpandedBBox)(/*[out,retval]*/ RectD* pVal);
	STDMETHOD(get_document)(/*[out, retval]*/ IPDDocument* *pVal);
	STDMETHOD(put_document)(/*[in]*/ IPDDocument* newVal);
// IPDObject
//	STDMETHOD(getScreenBBox)(/*[out,retval]*/ RectD* pVal);
//	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy);

	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = OBJECT_SYMBOLINSTANCESET;
		return S_OK;
	}
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDObjectSymbolInstanceSet;
		return S_OK;
	}
};

#endif //__PDOBJECTSYMBOLINSTANCESET_H_
