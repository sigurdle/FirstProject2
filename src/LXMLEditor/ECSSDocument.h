// ECSSDocument.h : Declaration of the CECSSDocument

#ifndef __ECSSDOCUMENT_H_
#define __ECSSDOCUMENT_H_

#if 0

#include "resource.h"       // main symbols

#include "..\LXFramework\WebDocumentImpl.h"
#include "WEUndoManager.h"

// TODO remove this class
class IOleObjectSimpleImpl :
	public IOleObject
{
public:
	CComPtr<IOleClientSite> m_spClientSite;

// IOleObject
     virtual HRESULT STDMETHODCALLTYPE SetClientSite( 
         /* [unique][in] */ IOleClientSite __RPC_FAR *pClientSite)
	  {
		  m_spClientSite = pClientSite;
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetClientSite( 
         /* [out] */ IOleClientSite __RPC_FAR *__RPC_FAR *ppClientSite)
	  {
		  *ppClientSite = m_spClientSite;
		  if (*ppClientSite) (*ppClientSite)->AddRef();
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE SetHostNames( 
         /* [in] */ LPCOLESTR szContainerApp,
         /* [unique][in] */ LPCOLESTR szContainerObj)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE Close( 
         /* [in] */ DWORD dwSaveOption)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE SetMoniker( 
         /* [in] */ DWORD dwWhichMoniker,
         /* [unique][in] */ IMoniker __RPC_FAR *pmk)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetMoniker( 
         /* [in] */ DWORD dwAssign,
         /* [in] */ DWORD dwWhichMoniker,
         /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE InitFromData( 
         /* [unique][in] */ IDataObject __RPC_FAR *pDataObject,
         /* [in] */ BOOL fCreation,
         /* [in] */ DWORD dwReserved)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetClipboardData( 
         /* [in] */ DWORD dwReserved,
         /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDataObject)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE DoVerb( 
         /* [in] */ LONG iVerb,
         /* [unique][in] */ LPMSG lpmsg,
         /* [unique][in] */ IOleClientSite __RPC_FAR *pActiveSite,
         /* [in] */ LONG lindex,
         /* [in] */ HWND hwndParent,
         /* [unique][in] */ LPCRECT lprcPosRect)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE EnumVerbs( 
         /* [out] */ IEnumOLEVERB __RPC_FAR *__RPC_FAR *ppEnumOleVerb)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE Update( void)
  	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE IsUpToDate( void)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetUserClassID( 
         /* [out] */ CLSID __RPC_FAR *pClsid)
 	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetUserType( 
         /* [in] */ DWORD dwFormOfType,
         /* [out] */ LPOLESTR __RPC_FAR *pszUserType)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE SetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ SIZEL __RPC_FAR *psizel)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [out] */ SIZEL __RPC_FAR *psizel)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE Advise( 
         /* [unique][in] */ IAdviseSink __RPC_FAR *pAdvSink,
         /* [out] */ DWORD __RPC_FAR *pdwConnection)
	  {
		  return E_NOTIMPL;
	  }

		virtual HRESULT STDMETHODCALLTYPE Unadvise( 
         /* [in] */ DWORD dwConnection)
	  {
		  return E_NOTIMPL;
	  }

		virtual HRESULT STDMETHODCALLTYPE EnumAdvise( 
         /* [out] */ IEnumSTATDATA __RPC_FAR *__RPC_FAR *ppenumAdvise)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetMiscStatus( 
         /* [in] */ DWORD dwAspect,
         /* [out] */ DWORD __RPC_FAR *pdwStatus)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE SetColorScheme( 
         /* [in] */ LOGPALETTE __RPC_FAR *pLogpal)
	  {
		  return E_NOTIMPL;
	  }
};

class CECSSViewGroup;

/////////////////////////////////////////////////////////////////////////////
// CECSSDocument
class ATL_NO_VTABLE CECSSDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CECSSDocument, &CLSID_ECSSDocument>,
	public IConnectionPointContainerImpl<CECSSDocument>,
	public IDispatchImpl<IECSSDocument, &IID_IECSSDocument>,
	public CEDocumentImpl<CECSSDocument>,
	public ProcessTargetCommands,	// ILDOMEventListener
	public ISupportErrorInfo,
//	public IPersistFile,
	public IPersistMoniker,

	public IOleObjectSimpleImpl,
	public IOleDocument,

	public ILCSSStyleSheetHandler,

	public IDispEventImpl<1, CECSSDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>
{
public:
	CECSSDocument()
	{
		m_curMoniker = NULL;
		m_undoManager = NULL;

		m_lockDOM = 0;
		m_lockSource = 0;
	}

	int FinalConstruct();
	void FinalRelease();

	CComQIPtr<ILXMLEditorApp> m_app;

	CComPtr<IMoniker> m_curMoniker;
	CComPtr<ITextData> m_textData;
	CComObject<CWEUndoManager>* m_undoManager;

	CComPtr<ILCSSStyleSheet> m_styleSheet;

	int m_lockDOM;
	int m_lockSource;

	void UpdateTitles();

	CArray<CECSSViewGroup*,CECSSViewGroup*> m_viewGroups;

DECLARE_REGISTRY_RESOURCEID(IDR_ECSSDOCUMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CECSSDocument)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEDocument)
	COM_INTERFACE_ENTRY(IECSSDocument)
	//COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(ILDOMEventListener)

	COM_INTERFACE_ENTRY(ILCSSStyleSheetHandler)

//	COM_INTERFACE_ENTRY(IPersist)
//	COM_INTERFACE_ENTRY2(IPersist, IPersistFile)
//	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IPersistMoniker)

	COM_INTERFACE_ENTRY(IOleObject)	// TODO remove
	COM_INTERFACE_ENTRY(IOleDocument)	// TODO remove

	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CECSSDocument)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CECSSDocument)
   SINK_ENTRY_EX(1, DIID__ITextDataEvents, /*dispid*/2, OnTextDocumentInsertedText)
   SINK_ENTRY_EX(1, DIID__ITextDataEvents, /*dispid*/3, OnTextDocumentDeletedText)
END_SINK_MAP()

	void __stdcall OnTextDocumentInsertedText(long offset, long len);
	void __stdcall OnTextDocumentDeletedText(long offset, long len);

DECLARE_CMD_MAP(CECSSDocument)

	LRESULT OnEditUndo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditRedo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditUndoUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnEditRedoUpdate(long iid, IUICmdUpdate* pCmdUI);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IECSSDocument
public:

	STDMETHOD(get_textData)(ITextData* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_textData;
		(*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(get_undoManager)(/*[out, retval]*/ IUndoManager* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_undoManager;
		(*pVal)->AddRef();
		return S_OK;
	}

// IEDocument
	STDMETHOD(ShowViews)(IEFrame* pFrame);
	STDMETHOD(Activate)();
	STDMETHOD(CloseDocument)();
   STDMETHOD(SetApp)(ILXAddin* pApp)
	{
		m_app = pApp;
		return S_OK;
	}

// ILCSSStyleSheetHandler
	STDMETHOD(handleCSSEvent)(/*[in]*/ LCSSObjectType objectType, /*[in]*/ LCSSEventType eventType, /*[in]*/ ILCSSStyleSheet* styleSheet, /*[in]*/ IUnknown* pObject);

// IPersist
	STDMETHOD(GetClassID)(CLSID __RPC_FAR *pClassID);
	STDMETHOD(IsDirty)();

	/*
// IPersistFile
	STDMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode);
	STDMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember);
	STDMETHOD(SaveCompleted)(LPCOLESTR pszFileName);
	STDMETHOD(GetCurFile)(LPOLESTR __RPC_FAR *ppszFileName);
	*/

// IPersistMoniker
	STDMETHOD(Load)(/* [in] */ BOOL fFullyAvailable, /* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc, /* [in] */ DWORD grfMode);
	STDMETHOD(Save)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pbc, /* [in] */ BOOL fRemember);  
	STDMETHOD(SaveCompleted)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc);
	STDMETHOD(GetCurMoniker)(/* [out] */ IMoniker **ppimkName);

// IOleDocument
	STDMETHOD(CreateView)(IOleInPlaceSite __RPC_FAR *pIPSite, IStream __RPC_FAR *pstm, DWORD dwReserved, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetDocMiscStatus)(DWORD __RPC_FAR *pdwStatus)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(EnumViews)(IEnumOleDocumentViews __RPC_FAR *__RPC_FAR *ppEnum, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
	{
		return E_NOTIMPL;
	}
};

#endif
#endif //__ECSSDOCUMENT_H_
