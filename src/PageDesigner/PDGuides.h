#pragma once

class CPDGuide;
//class CPDLayer;

#include "PDGuide.h"
#include "PDObjectUnknownImpl.h"
#include "PDObjectWithChildrenImpl.h"

class ATL_NO_VTABLE CPDGuides : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDObjectUnknownImpl<IPDGuides>,
	public CPDObjectWithChildrenImpl<CPDGuides>
{
public:
	CPDGuides()
	{
		m_children = NULL;
		m_firstChild = NULL;
		m_lastChild = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CComObject<CObjectMap>* m_children;
	IPDObjectUnknown* m_firstChild;
	IPDObjectUnknown* m_lastChild;

	HRESULT insertObject(IPDGuide* object, IPDGuide* before);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDGuides)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDGuides)
	COM_INTERFACE_ENTRY(IPDObjectWithChildren)
END_COM_MAP()

// IPDGuides
public:
	STDMETHOD(removeObject)(/*[in]*/ IPDObjectUnknown* object);
	STDMETHOD(deleteAllGuides)();
	STDMETHOD(getGuideUnderPoint)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double tolerance, /*[out,retval]*/ IPDGuide* *pVal);
	STDMETHOD(item)(/*[in]*/ long index, /*[out,retval]*/ IPDGuide* *pVal);
	STDMETHOD(get_length)(/*[out, retval]*/ long *pVal);
	STDMETHOD(appendGuide)(/*[in]*/ IPDGuide* guide);
	STDMETHOD(createGuide)(/*[in]*/ long direction, /*[out,retval]*/ IPDGuide* *pVal);
// IPDObjectUnknown
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = OBJECT_GUIDES;
		return S_OK;
	}
};
