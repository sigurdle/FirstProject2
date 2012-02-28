//#include "LHTMLCP.h"

#pragma once

#if 0
class CHTMFrame;

class CHTMLScriptSiteBase :
	public IActiveScriptSite,
	public IActiveScriptSiteWindow,
	public ILHTMLWindow,
	public IDispatchEx
{
public:
	CHTMLScriptSiteBase()
	{
		m_pFrame = NULL;
	}

	CHTMFrame* m_pFrame;

	STDMETHODIMP SVGHitTest(/*[in]*/ ILSVGElement* element, /*[in]*/ long pointerEvents, /*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ bool* pVal)
	{
		return E_FAIL;
	}
	STDMETHOD(get_magnify)(/*[out, retval]*/ double *pVal)
	{
		return E_FAIL;
	}
	STDMETHOD(set_magnify)(/*[in]*/ double newVal)
	{
		return E_FAIL;
	}

/*
BEGIN_COM_MAP(CHTMLScriptSite)
	COM_INTERFACE_ENTRY(IActiveScriptSite)
	COM_INTERFACE_ENTRY(IActiveScriptSiteWindow)
	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(IDispatchEx)
	COM_INTERFACE_ENTRY(IMMSXHTMLWindow)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CHTMLScriptSite)
CONNECTION_POINT_ENTRY(DIID_HTMLWindowEvents)
END_CONNECTION_POINT_MAP()
*/

// IActiveScriptSite
	STDMETHOD(GetLCID)(/* [out] */ LCID __RPC_FAR *plcid);
	STDMETHOD(GetItemInfo)(/* [in] */ LPCOLESTR pstrName, /* [in] */ DWORD dwReturnMask,/* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiunkItem,/* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppti);
	STDMETHOD(GetDocVersionString)(/* [out] */ BSTR __RPC_FAR *pbstrVersion);
	STDMETHOD(OnScriptTerminate)(/* [in] */ const VARIANT __RPC_FAR *pvarResult,/* [in] */ const EXCEPINFO __RPC_FAR *pexcepinfo);
	STDMETHOD(OnStateChange)(/* [in] */ SCRIPTSTATE ssScriptState);
	STDMETHOD(OnScriptError)(/* [in] */ IActiveScriptError __RPC_FAR *pscripterror);
	STDMETHOD(OnEnterScript)( void);
	STDMETHOD(OnLeaveScript)( void);

// IActiveScriptSiteWindow
	STDMETHOD(GetWindow)(/* [out] */ HWND __RPC_FAR *phwnd);
	STDMETHOD(EnableModeless)(/* [in] */ BOOL fEnable);

// IDispatchImpl
	STDMETHOD(GetTypeInfoCount)(unsigned int FAR *iTInfo);
	STDMETHOD(GetTypeInfo)(unsigned int iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo);

	STDMETHOD(GetIDsOfNames)(
		REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid
	) = 0;

	STDMETHOD(Invoke)(
	  DISPID dispIdMember,
	  REFIID riid,
	  LCID lcid,
	  WORD wFlags,
	  DISPPARAMS FAR* pDispParams,
	  VARIANT FAR* pVarResult,
	  EXCEPINFO FAR* pExcepInfo,
	  unsigned int FAR* puArgErr
	) = 0;

	// IDispatchEx
     virtual HRESULT STDMETHODCALLTYPE GetDispID( 
         /* [in] */ BSTR bstrName,
         /* [in] */ DWORD grfdex,
         /* [out] */ DISPID __RPC_FAR *pid)
	  {
		  /*
		  ATLTRACE(L"IDispatchEx::GetDispID(%s)", bstrName);
		  HRESULT hr = m_pScriptDisp->GetDispID(bstrName,grfdex,pid);
		  ATLTRACE(L"=%ld\n", hr);

		  return hr;
		  */
		  return S_OK;
	  }
     
     virtual /* [local] */ HRESULT STDMETHODCALLTYPE InvokeEx( 
         /* [in] */ DISPID id,
         /* [in] */ LCID lcid,
         /* [in] */ WORD wFlags,
         /* [in] */ DISPPARAMS __RPC_FAR *pdp,
         /* [out] */ VARIANT __RPC_FAR *pvarRes,
         /* [out] */ EXCEPINFO __RPC_FAR *pei,
         /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller)
	  {
			//return m_pScriptDisp->InvokeEx(id,lcid,wFlags,pdp,pvarRes,pei,pspCaller);
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE DeleteMemberByName( 
         /* [in] */ BSTR bstr,
         /* [in] */ DWORD grfdex)
     	  {
		  return S_OK;
//		return m_pScriptDisp->DeleteMemberByName(bstr,grfdex);
	  }

     virtual HRESULT STDMETHODCALLTYPE DeleteMemberByDispID( 
         /* [in] */ DISPID id)
 	  {
		  return S_OK;
//		return m_pScriptDisp->DeleteMemberByDispID(id);
	  }

     virtual HRESULT STDMETHODCALLTYPE GetMemberProperties( 
         /* [in] */ DISPID id,
         /* [in] */ DWORD grfdexFetch,
         /* [out] */ DWORD __RPC_FAR *pgrfdex)
	  {
		  return S_OK;
//			return m_pScriptDisp->GetMemberProperties(id,grfdexFetch,pgrfdex);
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetMemberName( 
         /* [in] */ DISPID id,
         /* [out] */ BSTR __RPC_FAR *pbstrName)
	  {
		  return S_OK;
//		return m_pScriptDisp->GetMemberName( id,pbstrName);
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetNextDispID( 
         /* [in] */ DWORD grfdex,
         /* [in] */ DISPID id,
         /* [out] */ DISPID __RPC_FAR *pid)
	  {
		  return S_OK;
//		return m_pScriptDisp->GetNextDispID(grfdex,id,pid);
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetNameSpaceParent( 
         /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk)
	  {
		  return S_OK;
//			return m_pScriptDisp->GetNameSpaceParent(ppunk);
	  }

// ILHTMLWindow
	STDMETHOD(get_frames)(/*[out, retval]*/ ILHTMLFramesCollection **pVal);
	STDMETHOD(get_event)(/*[out, retval]*/ ILDOMEvent* *pVal)
	{
		return S_OK;
	}
	STDMETHOD(set_event)(/*[in]*/ ILDOMEvent* newVal)
	{
		return S_OK;
	}
	STDMETHOD(get_document)(ILDOMDocument* * p)
	{
		return S_OK;
	}
	STDMETHOD(set_document)(ILDOMDocument * p)
	{
		return S_OK;
	}
	STDMETHOD(setTimeout)(BSTR expression, LONG msec, VARIANT * language, LONG * timerID)
	{
		return S_OK;
	}
	STDMETHOD(clearTimeout)(LONG timerID)
	{
		return S_OK;
	}
	STDMETHOD(alert)(BSTR message)
	{
		return S_OK;
	}
	STDMETHOD(confirm)(BSTR message, bool * confirmed)
	{
		return S_OK;
	}
	STDMETHOD(prompt)(BSTR message, BSTR defstr, VARIANT * textdata)
	{
		return S_OK;
	}
	STDMETHOD(get_parent)(/*[out, retval]*/ ILHTMLWindow* *pVal)
	{
		return S_OK;
	}
	STDMETHOD(showModalDialog)(/*[in]*/ BSTR dialog, /*[in]*/ VARIANT *varArgIn, /*[in]*/ VARIANT *varOptions, /*[out,retval]*/ VARIANT *varArgOut)
	{
		return S_OK;
	}

	STDMETHOD(get_length)(/*[out, retval]*/ long *pVal)
	{
		return S_OK;
	}
	STDMETHOD(item)(/*[in]*/ VARIANT* pvarIndex, /*[out,retval]*/ VARIANT* pvarResult)
	{
		return S_OK;
	}

	// IHTMLWindow2
	
	STDMETHOD(get_frames)(IHTMLFramesCollection2 * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_defaultStatus)(BSTR p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_defaultStatus)(BSTR * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_status)(BSTR p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_status)(BSTR * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_Image)(IHTMLImageElementFactory * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_location)(IHTMLLocation * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_history)(IOmHistory * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(close)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(put_opener)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_opener)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_navigator)(IOmNavigator * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_name)(BSTR p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_name)(BSTR * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_parent)(IHTMLWindow2 * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(open)(BSTR url, BSTR name, BSTR features, bool replace, IHTMLWindow2 * * pomWindowResult)
	{
		if (pomWindowResult == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_self)(IHTMLWindow2 * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_top)(IHTMLWindow2 * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_window)(IHTMLWindow2 * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(navigate)(BSTR url)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(put_onfocus)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onfocus)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_onblur)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onblur)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_onload)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onload)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_onbeforeunload)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onbeforeunload)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_onunload)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onunload)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_onhelp)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onhelp)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_onerror)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onerror)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_onresize)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onresize)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(put_onscroll)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_onscroll)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_document)(IHTMLDocument2 * * p)
	{
		if (p == NULL) return E_POINTER;

		*p = NULL;

		/*
		CComQIPtr<IDOMDocument> domdocument;
		m_documentContainer->get_document(&domdocument);
		if (domdocument)
		{
			domdocument->QueryInterface(IID_IHTMLDocument2, (void**)p);
			ATLASSERT(*p);
		}
		*/

		return S_OK;
	}
	STDMETHOD(get_event)(IHTMLEventObj * * p)
	{
		ATLASSERT(0);
		/*
		CComQIPtr<IHTMLEventObj> e = m_pFrame->m_eventObj;
		*p = e;
		if (*p) (*p)->AddRef();
		*/

		return S_OK;
	}
	STDMETHOD(get__newEnum)(IUnknown * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
/*
	STDMETHOD(showModalDialog)(BSTR dialog, VARIANT * varArgIn, VARIANT * varOptions, VARIANT * varArgOut)
	{
		if (varArgOut == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
*/
	STDMETHOD(showHelp)(BSTR helpURL, VARIANT helpArg, BSTR features)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_screen)(IHTMLScreen * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_Option)(IHTMLOptionElementFactory * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(focus)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_closed)(bool * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(blur)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(scroll)(LONG x, LONG y)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_clientInformation)(IOmNavigator * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(setInterval)(BSTR expression, LONG msec, VARIANT * language, LONG * timerID)
	{
		if (timerID == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(clearInterval)(LONG timerID)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(put_offscreenBuffering)(VARIANT p)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_offscreenBuffering)(VARIANT * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(execScript)(BSTR code, BSTR language, VARIANT * pvarRet)
	{
		if (pvarRet == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(toString)(BSTR * String)
	{
		if (String == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(scrollBy)(LONG x, LONG y)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(scrollTo)(LONG x, LONG y)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(moveTo)(LONG x, LONG y)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(moveBy)(LONG x, LONG y)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(resizeTo)(LONG x, LONG y)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(resizeBy)(LONG x, LONG y)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_external)(IDispatch * * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
// IHTMLFramesCollection2
/*
	STDMETHOD(item)(VARIANT * pvarIndex, VARIANT * pvarResult)
	{
		if (pvarResult == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_length)(LONG * p)
	{
		if (p == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
*/
};

class CHTMLScriptSite :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CHTMLScriptSiteBase,
	public IConnectionPointContainerImpl<CHTMLScriptSite>
//	public CProxyHTMLWindowEvents< CHTMLScriptSite >
{
public:
	STDMETHOD(svgGetScreenBBox)(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGRect* *pVal);
	STDMETHOD(get_screen)(/*[out, retval]*/ IHTMLScreen* *pVal);
	STDMETHOD(setActiveElement)(/*[in]*/ ILDOMElement* element);
	STDMETHOD(GetIDsOfNames)(
		REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid);
	
	STDMETHOD(Invoke)(
		DISPID dispIdMember,
		REFIID riid,
		LCID lcid,
		WORD wFlags,
		DISPPARAMS FAR* pDispParams,
		VARIANT FAR* pVarResult,
		EXCEPINFO FAR* pExcepInfo,
		unsigned int FAR* puArgErr);

BEGIN_COM_MAP(CHTMLScriptSite)
	COM_INTERFACE_ENTRY(IActiveScriptSite)
	COM_INTERFACE_ENTRY(IActiveScriptSiteWindow)
	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(IDispatchEx)
	COM_INTERFACE_ENTRY(ILHTMLWindow)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CHTMLScriptSite)
//CONNECTION_POINT_ENTRY(DIID_HTMLWindowEvents)
END_CONNECTION_POINT_MAP()
};
#endif