// WebSite.h : Declaration of the CWebSite

#ifndef __WEBSITE_H_
#define __WEBSITE_H_

#include "resource.h"       // main symbols

#include "..\LXFramework\WebDocumentImpl.h"

#include "LXWebSiteCP.h"

class CProgressDlg;
class CServer;

/////////////////////////////////////////////////////////////////////////////
// CWebSite
class ATL_NO_VTABLE CWebSite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWebSite, &CLSID_WebSite>,
	public IConnectionPointContainerImpl<CWebSite>,
	public IDispatchImpl<IWebSite, &IID_IWebSite, &LIBID_LXWEBSITELib>,

	public CEDocumentImpl<CWebSite>,
	public IOleObject,
	public IOleDocument,
	public ProcessTargetCommands,

	public CProxy_IWebSiteEvents< CWebSite >
{
public:
	CWebSite()
	{
//		m_pFTPRootDir = NULL;
		//m_hInternet = NULL;
		//m_hInternetFtp = NULL;

		m_pFtpServer = NULL;
	}

	void FinalRelease();

	CComQIPtr<ILXWebSiteApp> m_app;

	CComPtr<IOleClientSite> m_spClientSite;

// File system
// FTP files

	//CSiteDir* m_pFTPRootDir;
//	HINTERNET m_hInternet;
//	HINTERNET m_hInternetFtp;

	//IWSSrvPtr m_webSite;
	CComPtr<ILXLocalWebSite> m_webSite;
//

	CComBSTR m_ftpServerName;
	CServer* m_pFtpServer;

	/*
	_bstr_t m_ftpServerName;
	_bstr_t m_ftpDirectory;
	_bstr_t m_ftpUsername;
	_bstr_t m_ftpPassword;
	*/

	void NewWindow();
	void ScanFiles();
	long CopyMoveFile(DWORD folder_id, _bstr_t filepath, VARIANT_BOOL bSilent, CProgressDlg* dlg);

DECLARE_REGISTRY_RESOURCEID(IDR_WEBSITE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWebSite)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IWebSite)
	COM_INTERFACE_ENTRY(IEDocument)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IOleDocument)
	COM_INTERFACE_ENTRY(ICommandTarget)

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CWebSite)
	//CONNECTION_POINT_ENTRY(DIID__ILXLocalWebSiteEvents)
	CONNECTION_POINT_ENTRY(DIID__IWebSiteEvents)
END_CONNECTION_POINT_MAP()

DECLARE_CMD_MAP(CWebSite)

	LRESULT OnSiteSettings(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnWindowNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnFTPConnect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFTPDisconnect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IWebSite
public:
	STDMETHOD(CopyMoveFile)(/*[in]*/ DWORD folder_id, /*[in]*/ BSTR filepath, /*[in]*/ VARIANT_BOOL bSilent, /*[out,retval]*/ long* nFilesCopied);
	STDMETHOD(CopyMoveFiles)(/*[in]*/ DWORD folder_id, /*[in]*/ SAFEARRAY* filepaths, /*[in]*/ VARIANT_BOOL bSilent, /*[out,retval]*/ long* nFilesCopied);
//	STDMETHOD(OpenDocument)(/*[in]*/ DWORD file_id, /*[out,retval]*/ VARIANT_BOOL* pSuccess);
#if 0
	STDMETHOD(get_ftpPassword)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ftpPassword)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ftpUsername)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ftpUsername)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ftpDirectory)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ftpDirectory)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ftpServerName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ftpServerName)(/*[in]*/ BSTR newVal);
#endif
	STDMETHOD(LoadDocument)(/*[in]*/ BSTR pathName);

// IEDocument
	STDMETHOD(Activate)()
	{
		return S_OK;
	}
//	STDMETHOD(get_undoManager)(/*[out, retval]*/ IOleUndoManager* *pVal);
//	STDMETHOD(NewDocument)();
	STDMETHOD(CloseDocument)()
	{
		return S_OK;
	}
//	STDMETHOD(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);

	STDMETHOD(ShowViews)(IEFrame* pFrame);

   STDMETHOD(SetApp)(ILXAddin* pApp)
	{
		m_app = pApp;
		return S_OK;
	}

// IOleObject
     virtual HRESULT STDMETHODCALLTYPE SetClientSite( 
         /* [unique][in] */ IOleClientSite __RPC_FAR *pClientSite)
	  {
		  m_spClientSite = pClientSite;

		//  CComQIPtr<IOleObject> spOleObject = m_document;
		  //return spOleObject->SetClientSite(pClientSite);
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetClientSite( 
         /* [out] */ IOleClientSite __RPC_FAR *__RPC_FAR *ppClientSite)
	  {
		  *ppClientSite = m_spClientSite;
		  if (*ppClientSite) (*ppClientSite)->AddRef();
		  return S_OK;

		  //CComQIPtr<IOleObject> spOleObject = m_document;
		  //return spOleObject->GetClientSite(ppClientSite);
	  }

     virtual HRESULT STDMETHODCALLTYPE SetHostNames( 
         /* [in] */ LPCOLESTR szContainerApp,
         /* [unique][in] */ LPCOLESTR szContainerObj)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE Close( 
         /* [in] */ DWORD dwSaveOption)
	  {
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE SetMoniker( 
         /* [in] */ DWORD dwWhichMoniker,
         /* [unique][in] */ IMoniker __RPC_FAR *pmk)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetMoniker( 
         /* [in] */ DWORD dwAssign,
         /* [in] */ DWORD dwWhichMoniker,
         /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE InitFromData( 
         /* [unique][in] */ IDataObject __RPC_FAR *pDataObject,
         /* [in] */ BOOL fCreation,
         /* [in] */ DWORD dwReserved)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetClipboardData( 
         /* [in] */ DWORD dwReserved,
         /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDataObject)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE DoVerb( 
         /* [in] */ LONG iVerb,
         /* [unique][in] */ LPMSG lpmsg,
         /* [unique][in] */ IOleClientSite __RPC_FAR *pActiveSite,
         /* [in] */ LONG lindex,
         /* [in] */ HWND hwndParent,
         /* [unique][in] */ LPCRECT lprcPosRect)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE EnumVerbs( 
         /* [out] */ IEnumOLEVERB __RPC_FAR *__RPC_FAR *ppEnumOleVerb)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE Update( void)
  	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE IsUpToDate( void)
	  {
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetUserClassID( 
         /* [out] */ CLSID __RPC_FAR *pClsid)
 	  {
		  //CComQIPtr<IOleObject> spOleObject = m_document;
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetUserType( 
         /* [in] */ DWORD dwFormOfType,
         /* [out] */ LPOLESTR __RPC_FAR *pszUserType)
	  {
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE SetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ SIZEL __RPC_FAR *psizel)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [out] */ SIZEL __RPC_FAR *psizel)
	  {
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE Advise( 
         /* [unique][in] */ IAdviseSink __RPC_FAR *pAdvSink,
         /* [out] */ DWORD __RPC_FAR *pdwConnection)
	  {
		  return S_OK;
	  }

		virtual HRESULT STDMETHODCALLTYPE Unadvise( 
         /* [in] */ DWORD dwConnection)
	  {
		  return S_OK;
	  }

		virtual HRESULT STDMETHODCALLTYPE EnumAdvise( 
         /* [out] */ IEnumSTATDATA __RPC_FAR *__RPC_FAR *ppenumAdvise)
	  {
	  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetMiscStatus( 
         /* [in] */ DWORD dwAspect,
         /* [out] */ DWORD __RPC_FAR *pdwStatus)
	  {
	  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE SetColorScheme( 
         /* [in] */ LOGPALETTE __RPC_FAR *pLogpal)
	  {
	  return S_OK;
	  }

// IOleDocument
	STDMETHOD(CreateView)(IOleInPlaceSite __RPC_FAR *pIPSite, IStream __RPC_FAR *pstm, DWORD dwReserved, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
	{
	  return S_OK;
	}
	STDMETHOD(GetDocMiscStatus)(DWORD __RPC_FAR *pdwStatus)
	{
	  return S_OK;
	}
	STDMETHOD(EnumViews)(IEnumOleDocumentViews __RPC_FAR *__RPC_FAR *ppEnum, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
	{
	  return S_OK;
	}
};

#endif //__WEBSITE_H_
