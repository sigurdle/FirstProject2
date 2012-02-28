#ifndef __BYTEARRAY_H_
#define __BYTEARRAY_H_

//#include "resource.h"       // main symbols

#include "LMediaImpl.h"

namespace LMedia
{

#if 0
/////////////////////////////////////////////////////////////////////////////
// CByteArray
class CByteArray : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CByteArray, &CLSID_ByteArray>,
	public IByteArray,//, &IID_IByteArray, &LIBID_LMEDIALib>,
	public CLBaseFilterImpl
{
public:
	class CInputPin : 
	//	public CComObjectRootEx<CComSingleThreadModel>,
		public CLBasePinImpl
	//	public ISequentialStream
	{
	public:
		CInputPin() : CLBasePinImpl(LPINDIR_INPUT)
		{
			m_pFilter = NULL;
		}

		/*
		int FinalConstruct()
		{
			return 0;
		}

		void FinalRelease()
		{
		}
		*/

		CByteArray* m_pFilter;

		virtual HRESULT CheckMediaType(const CLMediaType &mt)
		{
			return S_OK;
		}

		/*
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputPin)
		COM_INTERFACE_ENTRY(ILPin)
		COM_INTERFACE_ENTRY(ISequentialStream)
	END_COM_MAP()
	*/

	public:
		ILBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

		HRESULT ReceiveConnection(ILPin* pConnector, LMediaType* pMediaType)
		{
			CLBasePinImpl::ReceiveConnection(pConnector, pMediaType);

			CreateStreamOnHGlobal(NULL, TRUE, &m_pFilter->m_stream);

			return S_OK;
		}

		virtual /* [local] */ HRESULT STDMETHODCALLTYPE Read( 
			/* [length_is][size_is][out] */ void *pv,
			/* [in] */ ULONG cb,
			/* [out] */ ULONG *pcbRead)
		{
			return E_NOTIMPL;
		}
		
		virtual /* [local] */ HRESULT STDMETHODCALLTYPE Write( 
			/* [size_is][in] */ const void *pv,
			/* [in] */ ULONG cb,
			/* [out] */ ULONG *pcbWritten)
		{
			return m_pFilter->m_stream->Write(pv, cb, pcbWritten);
		}
	};

	CByteArray()
	{
		m_pInput = new CInputPin;
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);
	}

	/*
	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLBaseFilterImpl::FinalConstruct();
		if (FAILED(hr)) return hr;

		CComObject<CInputPin>::CreateInstance(&m_pInput);
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);

		return 0;
	}

	void FinalRelease()
	{
		CLBaseFilterImpl::FinalRelease();
	}
	*/

	CInputPin* m_pInput;

	CComPtr<IStream> m_stream;
/*
DECLARE_REGISTRY_RESOURCEID(IDR_BYTEARRAY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CByteArray)
	COM_INTERFACE_ENTRY(IByteArray)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()
*/

// IByteArray
public:
	STDMETHOD(GetArray)(/*[out,retval]*/ VARIANT *pVal);
};

#endif

}	// LMedia

#endif //__BYTEARRAY_H_
