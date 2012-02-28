// XmillFilesProtocol.h : Declaration of the CXmillFilesProtocol

#ifndef __XMILLFILESPROTOCOL_H_
#define __XMILLFILESPROTOCOL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXmillFilesProtocol
class ATL_NO_VTABLE CXmillFilesProtocol : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXmillFilesProtocol, &CLSID_XmillFilesProtocol>,
//	public IXmillFilesProtocol,
	public IInternetProtocolInfo,
	public IInternetProtocol//IInternetProtocolRoot
{
public:
	CXmillFilesProtocol()
	{
		m_bindf = 0;
		m_dataArray = NULL;
		m_data = NULL;
		m_dataLength = 0L;
	}

	DWORD m_bindf;							// From m_pIBindInfo
	BINDINFO m_bindinfo;

	CComPtr<IInternetProtocolSink> m_pProtSink;
	CComPtr<IInternetBindInfo> m_pIBindInfo;

	SAFEARRAY* m_dataArray;
	DWORD m_dataLength;
	BYTE* m_data;
	DWORD m_nReadSoFar;

DECLARE_REGISTRY_RESOURCEID(IDR_XMILLFILESPROTOCOL)
//DECLARE_NOT_AGGREGATABLE(CXmillFilesProtocol)
//DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXmillFilesProtocol)
//	COM_INTERFACE_ENTRY(IXmillFilesProtocol)
//	COM_INTERFACE_ENTRY(IInternetProtocolRoot)
//	COM_INTERFACE_ENTRY(IInternetProtocol)
//	COM_INTERFACE_ENTRY(IInternetProtocolInfo)

	COM_INTERFACE_ENTRY_IID(IID_IInternetProtocol, IInternetProtocol)
	COM_INTERFACE_ENTRY_IID(IID_IInternetProtocolRoot, IInternetProtocol)
//	COM_INTERFACE_ENTRY_IID(IID_IInternetProtocolInfo, IInternetProtocolInfo)

END_COM_MAP()

// IXmillFilesProtocol
public:

// IInternet
	// No methods

//	IInternetProtocolRoot
	virtual HRESULT STDMETHODCALLTYPE Start( 
		/* [in] */ LPCWSTR szUrl,
		/* [in] */ IInternetProtocolSink *pOIProtSink,
		/* [in] */ IInternetBindInfo *pOIBindInfo,
		/* [in] */ DWORD grfPI,
		/* [in] */ HANDLE_PTR dwReserved);
		
	virtual HRESULT STDMETHODCALLTYPE Continue( 
		/* [in] */ PROTOCOLDATA *pProtocolData);
		
	virtual HRESULT STDMETHODCALLTYPE Abort( 
		/* [in] */ HRESULT hrReason,
		/* [in] */ DWORD dwOptions);
		
	virtual HRESULT STDMETHODCALLTYPE Terminate( 
		/* [in] */ DWORD dwOptions);
		
	virtual HRESULT STDMETHODCALLTYPE Suspend( void);
	
	virtual HRESULT STDMETHODCALLTYPE Resume( void);

// IInternetProtocol
	virtual HRESULT STDMETHODCALLTYPE Read( 
		/* [length_is][size_is][out][in] */ void *pv,
		/* [in] */ ULONG cb,
		/* [out] */ ULONG *pcbRead);
		
		virtual HRESULT STDMETHODCALLTYPE Seek( 
		/* [in] */ LARGE_INTEGER dlibMove,
		/* [in] */ DWORD dwOrigin,
		/* [out] */ ULARGE_INTEGER *plibNewPosition);
		
		virtual HRESULT STDMETHODCALLTYPE LockRequest( 
		/* [in] */ DWORD dwOptions);
		
		virtual HRESULT STDMETHODCALLTYPE UnlockRequest( void);

// IInternetProtocolInfo interface
public:
	STDMETHOD(CombineUrl)(LPCWSTR pwzBaseUrl, LPCWSTR pwzRelativeUrl, DWORD dwCombineFlags,
		LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved);
	STDMETHOD(CompareUrl)(LPCWSTR pwzUrl1, LPCWSTR pwzUrl2, DWORD dwCompareFlags);
	STDMETHOD(ParseUrl)(LPCWSTR pwzUrl, PARSEACTION ParseAction, DWORD dwParseFlags,
		LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved);
	STDMETHOD(QueryInfo)( LPCWSTR pwzUrl, QUERYOPTION QueryOption, DWORD dwQueryFlags,
		LPVOID pBuffer, DWORD cbBuffer, DWORD *pcbBuf, DWORD dwReserved);
};

#endif //__XMILLFILESPROTOCOL_H_
