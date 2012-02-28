// ASFLoader.h : Declaration of the CASFLoader

#ifndef __ASFLOADER_H_
#define __ASFLOADER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CASFLoader
class ATL_NO_VTABLE CASFLoader : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CASFLoader, &CLSID_ASFLoader>,
	public IASFLoader,
	public CLBaseFilterImpl	// ILMediaFilter
{
public:
	class ATL_NO_VTABLE CInputPin : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLPinImpl
		//public ILMemInputPin
	{
	public:
		CInputPin()
		{
			m_direction = LPINDIR_INPUT;
			m_pFilter = NULL;
		}

		CASFLoader* m_pFilter;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputPin)
		COM_INTERFACE_ENTRY(ILPin)
	END_COM_MAP()

		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}

		STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType);
	};

	CASFLoader()
	{
		m_pInputPin = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLBaseFilterImpl::FinalConstruct();
		if (FAILED(hr)) return hr;

		hr = CComObject<CInputPin>::CreateInstance(&m_pInputPin);
		if (FAILED(hr)) return hr;

		m_pInputPin->m_pFilter = this;
		AddPin(m_pInputPin);

		return 0;
	}

	void FinalRelease()
	{
		CLBaseFilterImpl::FinalRelease();
	}

	CComPtr<ILByteStream> m_stream;
	CComObject<CInputPin>* m_pInputPin;

DECLARE_REGISTRY_RESOURCEID(IDR_ASFLOADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CASFLoader)
	COM_INTERFACE_ENTRY(IASFLoader)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()

// IASFLoader
public:
};

#endif //__ASFLOADER_H_
