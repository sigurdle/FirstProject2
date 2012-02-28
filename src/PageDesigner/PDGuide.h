#pragma once

class CPDGuides;
//class CPDLayer;

#include "PDObjectUnknownImpl.h"

class ATL_NO_VTABLE CPDGuide : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDObjectUnknownImpl<IPDGuide>
//	public CPDObjectChildImpl<CPDGuide>
{
public:
	CPDGuide()
	{
		m_position = 0;
		m_direction = 0;
		m_pageIndex = 0;

	//	m_parent = NULL;
	//	m_previousSibling = NULL;
	//	m_nextSibling = NULL;
	}

	int FinalConstruct()
	{
		CoCreateGuid(&m_uniqId);
		return S_OK;
	}

	void FinalRelease()
	{
	}

	double m_position;
	long m_direction;
	long m_pageIndex;

//	CPDGuides* m_parent;
//	CPDGuide* m_previousSibling;
//	CPDGuide* m_nextSibling;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDGuide)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDGuide)
END_COM_MAP()

public:
// IPDObjectUnknown
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = OBJECT_GUIDE;
		return S_OK;
	}
// IPDGuide
	STDMETHOD(offsetPosition)(/*[in]*/ double delta);
	STDMETHOD(get_ownerSpread)(/*[out, retval]*/ IPDSpread* *pVal);
	STDMETHOD(get_direction)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_direction)(/*[in]*/ long newVal);
	STDMETHOD(get_position)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_position)(/*[in]*/ double newVal);
	STDMETHOD(get_pageIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_pageIndex)(/*[in]*/ long newVal);
};
