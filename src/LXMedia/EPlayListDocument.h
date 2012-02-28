// EPlayListDocument.h : Declaration of the CEPlayListDocument

#ifndef __EPLAYLISTDOCUMENT_H_
#define __EPLAYLISTDOCUMENT_H_

#include "resource.h"       // main symbols

#include "WebDocumentImpl.h"

class CPlayListItem
{
public:
	CPlayListItem()
	{
		m_duration = 0;
		m_fileSize = 0;
		m_treeItem = NULL;
	}

	CComPtr<IUITreeItem> m_treeItem;
	CUString m_title;
	CUString m_filename;
	ULONGLONG m_fileSize;
	double m_duration;	// in seconds
	FILETIME m_lastModified;
};

/////////////////////////////////////////////////////////////////////////////
// CEPlayListDocument
class ATL_NO_VTABLE CEPlayListDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEPlayListDocument, &CLSID_EPlayListDocument>,
	public IDispatchImpl<IEPlayListDocument, &IID_IEPlayListDocument, &LIBID_LXMEDIALib>,

	public CEDocumentImpl<CEPlayListDocument>,

	public IOleObject,
	public IPersistFile,

	public ProcessTargetCommands
{
public:
	CEPlayListDocument()
	{
	}

	CComPtr<IOleClientSite> m_spClientSite;

	CUPtrList m_items;

DECLARE_REGISTRY_RESOURCEID(IDR_EPLAYLISTDOCUMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEPlayListDocument)
	COM_INTERFACE_ENTRY(IEPlayListDocument)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEDocument)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

DECLARE_CMD_MAP(CEPlayListDocument)

//	LRESULT OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IEPlayListDocument
public:
// IEDocument
//	STDMETHOD(GetDocumentsClass)(/*[out,retval]*/ IDocumentsClass* *pVal);
	STDMETHOD(Activate)();
//	STDMETHOD(get_undoManager)(/*[out, retval]*/ IOleUndoManager* *pVal);
	STDMETHOD(NewDocument)();
	STDMETHOD(CloseDocument)();
//	STDMETHOD(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);
	STDMETHOD(ShowViews)(IEFrame* pFrame);

   STDMETHOD(SetApp)(ILXAddin* pApp)
	{
		return S_OK;
	}

// IPersist
   STDMETHOD(GetClassID)(
            /* [out] */ CLSID *pClassID)
	{
		if (pClassID == NULL) return E_POINTER;
		*pClassID = GetObjectCLSID();
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

// IPersistFile
	STDMETHOD(IsDirty)( void)
	{
		return S_FALSE;
	}
	STDMETHOD(Load)(/*[in]*/ LPCOLESTR pszFileName, /*[in]*/ DWORD dwMode);
	STDMETHOD(Save)(/*[unique][in]*/ LPCOLESTR pszFileName, /*[in]*/ BOOL fRemember)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(SaveCompleted)(/*[unique][in]*/ LPCOLESTR pszFileName)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetCurFile)(/*[out]*/ LPOLESTR *ppszFileName)
	{
		return E_NOTIMPL;
	}
};

#endif //__EPLAYLISTDOCUMENT_H_
