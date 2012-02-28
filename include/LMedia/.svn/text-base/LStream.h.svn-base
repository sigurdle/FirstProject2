#ifndef __LSTREAM_H_
#define __LSTREAM_H_

#include "resource.h"       // main symbols

#if 0

/////////////////////////////////////////////////////////////////////////////
// CLStream
class ATL_NO_VTABLE CLStream : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ILMediaStream, &IID_DispILMediaStream, &LIBID_LMEDIALib>
{
public:
	CLStream()
	{
	}

	void FinalRelease()
	{
	}

	ILPin* m_pin;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLStream)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(DispILMediaStream)
	COM_INTERFACE_ENTRY(ILMediaStream)
END_COM_MAP()

// ILStream
public:
	STDMETHOD(GetStreamType)(/*[out,retval]*/ LStreamType* pVal);
	STDMETHOD(GetDuration)(/*[out,retval]*/ double* pVal);
	STDMETHOD(GetPin)(ILPin* *pVal);
};

#endif

#endif //__LSTREAM_H_
