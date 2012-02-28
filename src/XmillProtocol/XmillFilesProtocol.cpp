// XmillFilesProtocol.cpp : Implementation of CXmillFilesProtocol
#include "stdafx.h"
#include "XmillProtocol.h"
#include "XmillFilesProtocol.h"

#import "..\XMillWeb\XMillWeb.tlb" named_guids

#include "shlwapi.h" // For PathIsUrl function
#include <atlconv.h>  // String Conversion Macros

/////////////////////////////////////////////////////////////////////////////
// CXmillFilesProtocol

enum ProtocolStates {PreStartState};

// IInternetProtocolRoot
STDMETHODIMP CXmillFilesProtocol::Start( 
            /* [in] */ LPCWSTR szUrl,
            /* [in] */ IInternetProtocolSink *pOIProtSink,
            /* [in] */ IInternetBindInfo *pOIBindInfo,
            /* [in] */ DWORD grfPI,
            /* [in] */ HANDLE_PTR dwReserved)
{
	HRESULT hr = E_FAIL;

	m_pProtSink = pOIProtSink;
	m_pIBindInfo = pOIBindInfo;
	
	m_bindinfo.cbSize = sizeof(BINDINFO);
	if (pOIBindInfo)
		hr = pOIBindInfo->GetBindInfo(&m_bindf, &m_bindinfo);

	// TODO: Honor all documented PI_ flags

	// We'll parse completely now and bind later if PI_FORCE_ASYNC
	
	// Parse URL and store results inside
	/*
	hr = DoParse(szUrl);
	if (FAILED(hr))
		goto Cleanup;
		*/

	// Should we do the following or always fail? How can we continue if parsing failed?
	if (grfPI & PI_PARSE_URL)
	{
		if (FAILED(hr))
			return S_FALSE;
		else
			return S_OK;
	}

	if (FAILED(hr))
		;//goto Cleanup;

	if (!(grfPI & PI_FORCE_ASYNC))
	{
		_bstr_t server = L"213.115.5.45";
		_bstr_t username = L"Sigurd";
		_bstr_t password = L"testing";

		/*
		COAUTHIDENTITY cauthid;
		cauthid.User = dlg.m_username;
		cauthid.UserLength = dlg.m_username.length();
		cauthid.Domain = L"WORKGROUP";
		cauthid.DomainLength = wcslen(cauthid.Domain);
		cauthid.Password = dlg.m_password;
		cauthid.PasswordLength = dlg.m_password.length();
		cauthid.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

		COAUTHINFO cauthi;
		cauthi.dwAuthnSvc = RPC_C_AUTHN_WINNT;
		cauthi.dwAuthzSvc = RPC_C_AUTHZ_NONE;
		cauthi.pwszServerPrincName = NULL;
		cauthi.dwAuthnLevel = RPC_C_AUTHN_LEVEL_CONNECT;
		cauthi.dwImpersonationLevel = RPC_C_IMP_LEVEL_IMPERSONATE;
		cauthi.pAuthIdentityData = &cauthid;
		cauthi.dwCapabilities = EOAC_NONE;
		*/

		COSERVERINFO csi;
		csi.dwReserved1 = 0;
		csi.pwszName = server;
		csi.pAuthInfo = NULL;//&cauthi;
		csi.dwReserved2 = 0;

		MULTI_QI qi[2];
		qi[0].pIID = &XMILLWEBLib::IID_IXmillWorkgroup;
		qi[0].pItf = NULL;
		qi[0].hr = 0;

		qi[1].pIID = &XMILLWEBLib::IID_ILFileSystem;
		qi[1].pItf = NULL;
		qi[1].hr = 0;

		HRESULT hr = CoCreateInstanceEx(XMILLWEBLib::CLSID_XmillWorkgroup, NULL, CLSCTX_SERVER/*CLSCTX_ALL*/, &csi, 2, qi);

		if (SUCCEEDED(qi[0].hr) && SUCCEEDED(qi[1].hr))
		{
			XMILLWEBLib::ILFileSystemPtr filesystem = qi[1].pItf;

			_bstr_t filePath = L"UserFolders/id_test3.svg";
			m_dataArray = filesystem->OpenFileAsArray(filePath);

			SafeArrayAccessData(m_dataArray, (void**)&m_data);
			m_dataLength = m_dataArray->rgsabound[0].cElements;

			qi[0].pItf->Release();
			qi[1].pItf->Release();
		}

		if (m_pProtSink)
			m_pProtSink->ReportProgress(BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE,
				 L"text/xml");

		TCHAR m_strCacheFile[_MAX_PATH];
		BOOL bSuccess = CreateUrlCacheEntry(_bstr_t(szUrl), m_dataLength, "svg", m_strCacheFile, 0);
		if (bSuccess)
		{
			FILE* m_fileCache = _tfopen(m_strCacheFile, _T("wb"));
			// Make sure to open using "b" so that UNICODE endlines aren't
			// botched by fwrite!
			if (m_fileCache != NULL)
			{
				fwrite(m_data, 1, m_dataLength, m_fileCache);
				fclose(m_fileCache);

				// *** As I said above, this is very important! *** //
				if (m_pProtSink)
					m_pProtSink->ReportProgress(BINDSTATUS_CACHEFILENAMEAVAILABLE,
					_bstr_t/*T2W*/(m_strCacheFile));
			}
			else
			{
				// Close cache entry and null out cache file name
				DeleteUrlCacheEntry(_bstr_t(szUrl));
				m_strCacheFile[0] = 0;
			}
		}
		else
		{
			m_strCacheFile[0] = 0;
		}

		m_nReadSoFar = 0;
		m_pProtSink->ReportData(BSCF_LASTDATANOTIFICATION | BSCF_DATAFULLYAVAILABLE, 0, m_dataLength);

	//		hr = DoBind();
	//		if (FAILED(hr))
	//			;//goto Cleanup;
	}
	else  // Wait for Continue to DoBind()
	{
		PROTOCOLDATA protdata;
		hr = E_PENDING;
		protdata.grfFlags = PI_FORCE_ASYNC;
		protdata.dwState = PreStartState;
		protdata.pData = NULL;
		protdata.cbData = 0;

		if (m_pProtSink)
		{
			m_pProtSink->Switch(&protdata);
		}
		else
		{
			hr = E_INVALIDARG;
			;//goto Cleanup;
		}
	}

	return hr;
}

STDMETHODIMP CXmillFilesProtocol::Continue( 
            /* [in] */ PROTOCOLDATA *pProtocolData)
{
//	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CXmillFilesProtocol::Abort( 
            /* [in] */ HRESULT hrReason,
            /* [in] */ DWORD dwOptions)
{
//	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CXmillFilesProtocol::Terminate( 
            /* [in] */ DWORD dwOptions)
{
	if (m_dataArray)
	{
		SafeArrayUnaccessData(m_dataArray);
	}

	if (m_pIBindInfo)
		m_pIBindInfo.Release();

	if (m_pProtSink)
		m_pProtSink.Release();

	return S_OK;
}
        
STDMETHODIMP CXmillFilesProtocol::Suspend( void)
{
//	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}
        
STDMETHODIMP CXmillFilesProtocol::Resume( void)
{
//	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}

// IInternetProtocol

STDMETHODIMP CXmillFilesProtocol::Read( 
	/* [length_is][size_is][out][in] */ void *pv,
	/* [in] */ ULONG cb,
	/* [out] */ ULONG *pcbRead)
{
	if (m_nReadSoFar >= m_dataLength)
	{
		return S_FALSE;
	}
	else
	{
		DWORD nRead;
		if (m_nReadSoFar+cb > m_dataLength)
		{
			nRead = m_dataLength-m_nReadSoFar;
		}
		else
			nRead = cb;

		memcpy(pv, ((LPCSTR)m_data)+m_nReadSoFar, nRead);

		m_nReadSoFar += nRead;
		*pcbRead = nRead;

		if (m_nReadSoFar >= m_dataLength)
		{
			m_pProtSink->ReportResult(S_OK, 0, NULL);
			return S_FALSE;	// All data downloaded
		}
		else
		{
			return S_OK;	// There's more data
		}
	}
}
	
STDMETHODIMP CXmillFilesProtocol::Seek( 
	/* [in] */ LARGE_INTEGER dlibMove,
	/* [in] */ DWORD dwOrigin,
	/* [out] */ ULARGE_INTEGER *plibNewPosition)
{
//	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}
	
STDMETHODIMP CXmillFilesProtocol::LockRequest( 
	/* [in] */ DWORD dwOptions)
{
//	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}
	
STDMETHODIMP CXmillFilesProtocol::UnlockRequest( void)
{
//	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}

//

STDMETHODIMP CXmillFilesProtocol::CombineUrl(LPCWSTR pwzBaseUrl, LPCWSTR pwzRelativeUrl, DWORD dwCombineFlags,
	LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved)
{
	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CXmillFilesProtocol::CompareUrl(LPCWSTR pwzUrl1, LPCWSTR pwzUrl2, DWORD dwCompareFlags)
{
	MessageBox(NULL, "Start", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CXmillFilesProtocol::ParseUrl(LPCWSTR pwzUrl, PARSEACTION ParseAction, DWORD dwParseFlags,
	LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved)
{
	HRESULT hr = E_FAIL;

	DWORD dwUrlLen = wcslen(pwzUrl);
	LPWSTR pwstrSecurityURL = NULL;

	if (PARSE_SECURITY_URL == ParseAction || PARSE_SECURITY_DOMAIN == ParseAction)
	{
		PSUACTION PSUFlag = (PARSE_SECURITY_URL == ParseAction) ? PSU_SECURITY_URL_ONLY : PSU_DEFAULT;
		hr = CoInternetGetSecurityUrl(_bstr_t(pwzUrl)/*m_url*/, &pwstrSecurityURL, PSUFlag, 0);
		// Need to copy security url to original buffer passed to us
		DWORD dwNewUrlLen = wcslen(pwstrSecurityURL);
		if (cchResult < dwNewUrlLen + 1)
		{
			hr = S_FALSE;
		}
		else
		{
			wcscpy(pwzResult, pwstrSecurityURL);
		}
		*pcchResult = dwNewUrlLen;
	}
	else
	{
	//	hr = CoInternetParseUrl(_bstr_t(pwzUrl), ParseAction, dwParseFlags, pwzResult, dwUrlLen, pcchResult, dwReserved);
		//wcscpy(pwzResult, L"test.svg");

		hr = CoInternetParseUrl(_bstr_t(pwzUrl+2), ParseAction, dwParseFlags, pwzResult, dwUrlLen, pcchResult, dwReserved);

		//*pcchResult = wcslen(pwzResult);
		//hr = S_OK;
	}

	return hr;
}

STDMETHODIMP CXmillFilesProtocol::QueryInfo( LPCWSTR pwzUrl, QUERYOPTION QueryOption, DWORD dwQueryFlags,
	LPVOID pBuffer, DWORD cbBuffer, DWORD *pcbBuf, DWORD dwReserved)
{
	return INET_E_DEFAULT_ACTION;
	return S_OK;
}
