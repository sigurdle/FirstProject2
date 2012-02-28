// LStreams.h : Declaration of the CLStreams

#ifndef __LSTREAMS_H_
#define __LSTREAMS_H_

#include "resource.h"       // main symbols

#if 0

/////////////////////////////////////////////////////////////////////////////
// CLStreams
class ATL_NO_VTABLE CLStreams : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<DispILStreams, &IID_DispILStreams, &LIBID_LMEDIALib>
{
public:
	CLStreams()
	{
	}

	void FinalRelease()
	{
		RemoveAll();
	}

	void RemoveAll()
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			m_items[i]->Release();
		}
		m_items.RemoveAll();
	}

	CArray<DispILMediaStream*,DispILMediaStream*> m_items;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLStreams)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(DispILStreams)
END_COM_MAP()

// ILStreams
public:
	STDMETHOD(get_Count)(/*[out,retval]*/ long *pVal);
	STDMETHOD(Item)(long index, DispILMediaStream* *pVal);
	STDMETHOD(get__newEnum)(/*out,retval*/ IUnknown* *pVal);
};

#endif

#endif //__LSTREAMS_H_
