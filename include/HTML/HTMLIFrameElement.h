#ifndef Web_HTMLIFrameElement_h
#define Web_HTMLIFrameElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLIFrameElement : 

	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLIFrameElement>,
//	public CLElementEditASImpl<HTMLIFrameElement>,
	public ElementEditVALImpl<HTMLIFrameElement>,

	public IEmbeddingElement
	/*
	public IBindStatusCallback,
	public IBindHost,
	public IHttpNegotiate,
	*/

//	public IElementEditVAL,	// ILNodeEditVAL

// MSHTML interfaces
//	public IHTMLFrameBase,
//	public IHTMLFrameBase2,
//	public IHTMLFrameBase3,
//	public CProxy_ILHTMLFrameSiteEvents< HTMLIFrameElement >,
//	public IConnectionPointContainerImpl<HTMLIFrameElement>,

//
{
public:
	CTOR HTMLIFrameElement(NamedNodeMap* attributes);

//	int FinalConstruct();
//	void FinalRelease();

#if 0	// ???
	CLXUIFrameContent* m_pFrameContent;
#endif
//

	ErrorCode Load();


// IDispatch
#if 0
	ErrorCode GetTypeInfoCount( 
         /* [out] */ UINT *pctinfo)
	{
		return IDispatchImpl<DispILHTMLIFrameElement, &IID_DispILHTMLIFrameElement, &LIBID_LHTMLLib>::GetTypeInfoCount(pctinfo);
	}

	ErrorCode GetTypeInfo( 
         /* [in] */ UINT iTInfo,
         /* [in] */ LCID lcid,
         /* [out] */ ITypeInfo **ppTInfo)
	{
		return IDispatchImpl<DispILHTMLIFrameElement, &IID_DispILHTMLIFrameElement, &LIBID_LHTMLLib>::GetTypeInfo(iTInfo, lcid, ppTInfo);
	}

	ErrorCode GetIDsOfNames( 
         /* [in] */ REFIID riid,
         /* [size_is][in] */ LPOLESTR *rgszNames,
         /* [in] */ UINT cNames,
         /* [in] */ LCID lcid,
         /* [size_is][out] */ DISPID *rgDispId)
	{
		return IDispatchImpl<DispILHTMLIFrameElement, &IID_DispILHTMLIFrameElement, &LIBID_LHTMLLib>::GetIDsOfNames(riid, rgszNames, cNames, lcid, rgDispId);
	}
     
	ErrorCode Invoke( 
         /* [in] */ DISPID dispIdMember,
         /* [in] */ REFIID riid,
         /* [in] */ LCID lcid,
         /* [in] */ WORD wFlags,
         /* [out][in] */ DISPPARAMS *pDispParams,
         /* [out] */ VARIANT *pVarResult,
         /* [out] */ EXCEPINFO *pExcepInfo,
         /* [out] */ UINT *puArgErr)
	{
		return IDispatchImpl<DispILHTMLIFrameElement, &IID_DispILHTMLIFrameElement, &LIBID_LHTMLLib>::Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	}

// EventTarget
	virtual ErrorCode dispatchEvent2(/*[in]*/ ILDOMEvent * evt, /*[in]*/ bool bCapture, /*[out,retval]*/ bool * doDefault);
#endif

	/*
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/

	virtual void OnAttrValueChanged(StringIn /*nodeName*/, Attr* attr);

	void goForward();
	void goBack();

	String get_src();
	void set_src(StringIn newVal);

	Document* get_contentDocument();
	IWindow* get_contentWindow();

	Attr* get_srcAttr()
	{
		return m_srcAttr;
	}

#if 0
	STDMETHOD(get_frameSpacing)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(set_frameSpacing)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_border)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(set_border)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_scrolling)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_scrolling)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_noResize)(/*[out, retval]*/ bool *pVal);
	STDMETHOD(set_noResize)(/*[in]*/ bool newVal);
	STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_marginHeight)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(set_marginHeight)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_marginWidth)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(set_marginWidth)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_longDesc)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_longDesc)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_frameBorder)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_frameBorder)(/*[in]*/ BSTR newVal);
#endif

#if 0
// Extensions
	STDMETHOD(get_contentWindow)(/*[out, retval]*/ ILHTMLWindow* *pVal);
#endif

// IHTMLFrameBase2
#if 0
        virtual /* [id][propget] */ ErrorCode STDMETHODCALLTYPE get_contentWindow( 
            /* [out][retval] */ IHTMLWindow2 **p)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [bindable][displaybind][id][propput] */ ErrorCode STDMETHODCALLTYPE set_onload( 
            /* [in] */ VARIANT v)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [bindable][displaybind][id][propget] */ ErrorCode STDMETHODCALLTYPE get_onload( 
            /* [out][retval] */ VARIANT *p)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [bindable][displaybind][id][propput] */ ErrorCode STDMETHODCALLTYPE set_onreadystatechange( 
            /* [in] */ VARIANT v)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [bindable][displaybind][id][propget] */ ErrorCode STDMETHODCALLTYPE get_onreadystatechange( 
            /* [out][retval] */ VARIANT *p)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [id][propget] */ ErrorCode STDMETHODCALLTYPE get_readyState( 
            /* [out][retval] */ BSTR *p)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [id][propput] */ ErrorCode STDMETHODCALLTYPE set_allowTransparency( 
            /* [in] */ bool v)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [id][propget] */ ErrorCode STDMETHODCALLTYPE get_allowTransparency( 
            /* [out][retval] */ bool *p)
		  {
			  return E_NOTIMPL;
		  }

// IBindStatusCallback
	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding __RPC_FAR *pib);
	STDMETHOD(GetPriority)(LONG __RPC_FAR *pnPriority);
	STDMETHOD(OnLowResource)(DWORD reserved);
	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText);
	STDMETHOD(OnStopBinding)(ErrorCode hresult, LPCWSTR szError);
	STDMETHOD(GetBindInfo)(DWORD __RPC_FAR *grfBINDF, BINDINFO __RPC_FAR *pbindinfo);
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR *pformatetc, STGMEDIUM __RPC_FAR *pstgmed);
	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown __RPC_FAR *punk);

// IBindHost
	virtual ErrorCode STDMETHODCALLTYPE CreateMoniker( 
      /* [in] */ LPOLESTR szName,
      /* [in] */ IBindCtx *pBC,
      /* [out] */ IMoniker **ppmk,
      /* [in] */ DWORD dwReserved)
	{
		return S_OK;
	}
		
		virtual /* [local] */ ErrorCode STDMETHODCALLTYPE MonikerBindToStorage( 
      /* [in] */ IMoniker *pMk,
      /* [in] */ IBindCtx *pBC,
      /* [in] */ IBindStatusCallback *pBSC,
      /* [in] */ REFIID riid,
      /* [out] */ void **ppvObj)
	{
		return S_OK;
	}

		virtual /* [local] */ ErrorCode STDMETHODCALLTYPE MonikerBindToObject( 
      /* [in] */ IMoniker *pMk,
      /* [in] */ IBindCtx *pBC,
      /* [in] */ IBindStatusCallback *pBSC,
      /* [in] */ REFIID riid,
      /* [out] */ void **ppvObj)
	{
		return S_OK;
	}

	// IHttpNegotiate
     virtual ErrorCode STDMETHODCALLTYPE BeginningTransaction( 
         /* [in] */ LPCWSTR szURL,
         /* [unique][in] */ LPCWSTR szHeaders,
         /* [in] */ DWORD dwReserved,
         /* [out] */ LPWSTR *pszAdditionalHeaders)
	{
		return S_OK;
	}
     
     virtual ErrorCode STDMETHODCALLTYPE OnResponse( 
         /* [in] */ DWORD dwResponseCode,
         /* [unique][in] */ LPCWSTR szResponseHeaders,
         /* [unique][in] */ LPCWSTR szRequestHeaders,
         /* [out] */ LPWSTR *pszAdditionalRequestHeaders)
	{
		return S_OK;
	}
#endif

protected:

	Attr* m_srcAttr;
};

}	// Web
}

#endif // Web_HTMLIFrameElement_h
