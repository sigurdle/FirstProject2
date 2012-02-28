// TDDDLoader.h : Declaration of the CTDDDLoader

#ifndef __TDDDLOADER_H_
#define __TDDDLOADER_H_

#include "resource.h"       // main symbols

#include "..\iffparse.h"

/////////////////////////////////////////////////////////////////////////////
// CTDDDLoader
class ATL_NO_VTABLE CTDDDLoader : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTDDDLoader, &CLSID_TDDDLoader>,
	public ITDDDLoader,
	public CLBaseFilterImpl	// ILMediaFilter
{
public:
	class ATL_NO_VTABLE CInputPin : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLBasePinImpl
		//public ILMemInputPin
	{
	public:
		CInputPin() : CLBasePinImpl(LPINDIR_INPUT)
		{
			m_pFilter = NULL;
		}

		CTDDDLoader* m_pFilter;

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

		virtual HRESULT CheckMediaType(const CLMediaType& mt)
		{
			if (mt->majortype != LMEDIATYPE_Stream)
				return E_FAIL;

			return S_OK;
		}

		virtual HRESULT CompleteConnect(ILPin* pConnector);
	};

	CTDDDLoader()
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

	CComObject<CInputPin>* m_pInputPin;

	CComPtr<ILX3DScene> m_scene;

	ILX3DNode* ParseDESC(IStream* pStream, ILMFNode* parentChildren);
	HRESULT ParseOBJ(IStream* pStream, ILMFNode* parentChildren);
	HRESULT ParseTDDD(IStream* pStream, ILMFNode* parentChildren);

DECLARE_REGISTRY_RESOURCEID(IDR_TDDDLOADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTDDDLoader)
	COM_INTERFACE_ENTRY(ITDDDLoader)
//	COM_INTERFACE_ENTRY(ILX3DLoader)

	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()

// ITDDDLoader
public:
	/*
	CI3DLayer* ParseDESC(CIStream* pStream, CI3DLayer* parentLayer);
	long ParseOBJ(CIStream* pStream, CI3DLayer* parentRef);
	long ParseTDDD(CIStream* pStream, CI3DLayer* parentRef);
	*/

// ILX3DLoader
//	STDMETHOD(Load)(/*[in]*/ IStream* stream, /*[in]*/ ILX3DScene* scene, /*[in]*/ ILMFNode* children);

// ILBaseFilter
	STDMETHOD(Run)(double tStart);
};

#endif //__TDDDLOADER_H_
