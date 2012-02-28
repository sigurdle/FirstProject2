// TextData.h : Declaration of the CTextData

#ifndef __TEXTDATA_H_
#define __TEXTDATA_H_

#include "resource.h"       // main symbols
#include "TextDataModCP.h"
//#include "DOMCoreModCP.h"

#include "..\zlib\zlib.h"

typedef struct gz_stream {
    z_stream stream;
    int      z_err;   /* error code for last stream operation */
    int      z_eof;   /* set if end of input file */
//    FILE     *file;   /* .gz file */
	 uLong bufsize;
    Byte     *inbuf;  /* input buffer */
//    Byte     *outbuf; /* output buffer */
	 IStream* file;
    uLong    crc;     /* crc32 of uncompressed data */
    char     *msg;    /* error message */
    char     *path;   /* path name for debugging only */
    int      transparent; /* 1 if input file is not a .gz file */
    char     mode;    /* 'w' or 'r' */
    long     startpos; /* start of compressed data in file (header skipped) */
} gz_stream;

#ifdef _DEBUG
#pragma comment(lib, "..\\zlib\\Debug\\zlib.lib")
#else
#pragma comment(lib, "..\\zlib\\Release\\zlib.lib")
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextData
class ATL_NO_VTABLE CTextData : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CTextData, &CLSID_TextData>,
	public IDispatchImpl<ITextData, &IID_ITextData, &LIBID_TEXTDATAMODLib>,

	public IPersistStream,
	public IPersistMoniker,

	public IBindStatusCallback,
	public IHttpSecurity,
	public IAuthenticate,

	public IServiceProviderImpl<CTextData>,

//	public CProxy_ITextDataEvents< CTextData >,
	public IConnectionPointContainerImpl<CTextData>,
	public CProxy_ITextDataEvents< CTextData >
{
public:
	CTextData()
	{
		m_textData = NULL;
		m_lockCount = 0;
		memset(&m_gz, 0, sizeof(m_gz));
	}

	long m_lockCount;
	BSTR	m_textData;

	_bstr_t m_url;

	int m_nReadInput;

	BYTE* m_bufferdata;
	long m_bufferlen;
	HANDLE m_hEvent;

	gz_stream m_gz;

//	void OnData(CBindStatusCallback<CTextData>* pbsc, BYTE* pBytes, DWORD dwSize);

	HRESULT ReadStream(IStream* stm, DWORD dwSize, ULONG* nRead);

	VARIANT_BOOL loadBuffer(BYTE* data, long size);

DECLARE_REGISTRY_RESOURCEID(IDR_TEXTDATA)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTextData)
	COM_INTERFACE_ENTRY(ITextData)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IBindStatusCallback)
	COM_INTERFACE_ENTRY(IAuthenticate)
	COM_INTERFACE_ENTRY(IHttpSecurity)

	COM_INTERFACE_ENTRY2(IPersistStream, IPersist)
	COM_INTERFACE_ENTRY(IPersistStream)
	COM_INTERFACE_ENTRY(IPersistMoniker)

	COM_INTERFACE_ENTRY(IServiceProvider)

	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_SERVICE_MAP(CTextData)
//	SERVICE_ENTRY(SID_SHlinkFrame)
	if (::InlineIsEqualGUID(guidService, IID_IAuthenticate))
			return QueryInterface(riid, ppvObject);

END_SERVICE_MAP()

BEGIN_CONNECTION_POINT_MAP(CTextData)
	CONNECTION_POINT_ENTRY(DIID__ITextDataEvents)
END_CONNECTION_POINT_MAP()

// ITextData
public:
	STDMETHOD(save)(/*[in]*/ BSTR pathName);
	STDMETHOD(setData)(/*[in]*/ BSTR data);
	STDMETHOD(replaceText)(/*[in]*/ long offset, /*[in]*/ long deletelen, /*[in]*/ BSTR data);
	STDMETHOD(deleteText)(/*[in]*/ long offset, /*[in]*/ long len);
	STDMETHOD(insertText)(/*[in]*/ long offset, /*[in]*/ BSTR data, /*[in]*/ long len);
	STDMETHOD(load)(/*[in]*/ BSTR pathName);
	STDMETHOD(loadByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);
	STDMETHOD(get_len)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_data)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_data)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_url)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_url)(/*[in]*/ BSTR newVal);
	STDMETHOD(unlockData)(/*[out,retval]*/ long* lockcount);
	STDMETHOD(lockData)(/*[out,retval]*/ long* lockcount);

// IPersist
     virtual HRESULT STDMETHODCALLTYPE GetClassID( 
         /* [out] */ CLSID *pClassID)
	  {
		  return S_OK;
	  }

// IPersistStream
	virtual HRESULT STDMETHODCALLTYPE IsDirty( void)
	{
		return S_OK;
	}
	
	virtual HRESULT STDMETHODCALLTYPE Load( 
		/* [unique][in] */ IStream *pStm);
		
		virtual HRESULT STDMETHODCALLTYPE Save( 
		/* [unique][in] */ IStream *pStm,
		/* [in] */ BOOL fClearDirty)
	{
		return S_OK;
	}
		
		virtual HRESULT STDMETHODCALLTYPE GetSizeMax( 
		/* [out] */ ULARGE_INTEGER *pcbSize)
	{
			return S_OK;
	}

// IPersistMoniker
  STDMETHODIMP Load( 
      /* [in] */ BOOL fFullyAvailable,
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc,
      /* [in] */ DWORD grfMode);
  
  STDMETHODIMP Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember);
  
  STDMETHODIMP SaveCompleted( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc);
  
  STDMETHODIMP GetCurMoniker( 
      /* [out] */ IMoniker **ppimkName);

// IBindStatusCallback
	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding __RPC_FAR *pib);
	STDMETHOD(GetPriority)(LONG __RPC_FAR *pnPriority);
	STDMETHOD(OnLowResource)(DWORD reserved);
	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText);
	STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError);
	STDMETHOD(GetBindInfo)(DWORD __RPC_FAR *grfBINDF, BINDINFO __RPC_FAR *pbindinfo);
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR *pformatetc, STGMEDIUM __RPC_FAR *pstgmed);
	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown __RPC_FAR *punk);

/////
   STDMETHOD(GetWindow)( 
            /* [in] */ REFGUID rguidReason,
            /* [out] */ HWND *phwnd)
	{
		*phwnd = NULL;
		return S_OK;
	}

// IAuthenticate
	STDMETHOD(Authenticate)( 
            /* [out] */ HWND *phwnd,
            /* [out] */ LPWSTR *pszUsername,
            /* [out] */ LPWSTR *pszPassword)
	{
		*phwnd = NULL;

		CComBSTR username = L"w00005125";
		CComBSTR password = L"A7h2GH";

		*pszUsername = (LPWSTR)CoTaskMemAlloc(username.Length()*2+2);
		wcscpy(*pszUsername, (BSTR)username);

		*pszPassword = (LPWSTR)CoTaskMemAlloc(password.Length()*2+2);
		wcscpy(*pszPassword, (BSTR)password);

		return S_OK;
	}

	STDMETHOD(OnSecurityProblem)(DWORD dwProblem)
	{
		return S_FALSE;
	}
};

#endif //__TEXTDATA_H_
