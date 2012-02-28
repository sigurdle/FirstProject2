#ifndef __SCRIPTSITE_H
#define __SCRIPTSITE_H

#if 0
class Document;


#ifdef _WINDOWS
#include <activdbg.h>

//MIDL_INTERFACE("DB40EA2D-969A-4262-A5FE-B04887B2E35D") CLDOMDocumentImplImpl;
/////////////////////////////////////////////////////////////////
// Scripting

///////////////////////////////////////////////////////////////////////////////
// Events
/*
<listener> element
*/

class CEventListener :
	public ILDOMEventListener
{
public:
	CTOR CEventListener()
	{
		m_listenerElement = NULL;
		m_handlerElement = NULL;
	}

	ILDOMElement* m_listenerElement;
	ILDOMElement* m_handlerElement;

	CComPtr<IDispatch> m_disp;	// The parsed code to execute

	/*
BEGIN_COM_MAP(CEventListener)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/

	void handleEvent(ILDOMEvent* evt)
	{
	// Set up the evt argument
		DISPPARAMS dispparams;
		VARIANTARG varargs[1];
		dispparams.cArgs = 1;
		dispparams.cNamedArgs = 0;
		dispparams.rgvarg = varargs;

#if 0
		V_VT(&dispparams.rgvarg[0]) = VT_DISPATCH;
		V_DISPATCH(&dispparams.rgvarg[0]) = evt;

		// Call the code
		DISPID dispid = 0;
		HRESULT hr = m_disp->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD,
			&dispparams, 0, 0, 0);
#endif
	}
};

class CScriptSite :
//	public CComObjectRootEx<CComSingleThreadModel>,
	public IActiveScriptSite,
	public IActiveScriptSiteWindow,

	public IActiveScriptSiteDebug,
	public IApplicationDebugger,
	public IDebugSessionProvider
{
public:
	CScriptSite()
	{
		m_pDocument = NULL;	// ??

		m_hWnd = NULL;
		m_pGlobalObject = NULL;
	}

	void FinalRelease();

	HWND m_hWnd;
	IUnknown* m_pGlobalObject;

	Document* m_pDocument;		// ??

	CComQIPtr<IActiveScript> m_activeScript;
	CComQIPtr<IDispatchEx> m_pScriptDisp;

	CComPtr<IProcessDebugManager> m_debugManager;
	CComPtr<IDebugApplication> m_debugApp;
	CComPtr<IDebugDocumentHelper> m_debugDocumentHelper;

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CScriptSite)
	COM_INTERFACE_ENTRY(IActiveScriptSite)
	COM_INTERFACE_ENTRY(IActiveScriptSiteWindow)

	COM_INTERFACE_ENTRY(IActiveScriptSiteDebug)
	COM_INTERFACE_ENTRY(IApplicationDebugger)
	COM_INTERFACE_ENTRY(IDebugSessionProvider)
END_COM_MAP()
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

// IActiveScriptSiteDebug
	STDMETHODIMP GetDocumentContextFromPosition(/*[in]*/ DWORD dwSourceContext,/*[in]*/
		ULONG uCharacterOffset,/*[in]*/ ULONG uNumChars,/*[out]*/ IDebugDocumentContext
		**ppsc);
	STDMETHODIMP GetApplication(/*[out]*/ IDebugApplication **ppda) ;
	STDMETHODIMP GetRootApplicationNode(/*[out]*/ IDebugApplicationNode
		**ppdanRoot);
	STDMETHODIMP OnScriptErrorDebug(/*[in]*/ IActiveScriptErrorDebug
		*pErrorDebug,/*[out]*/ BOOL *pfEnterDebugger,/*[out]*/ BOOL
		*pfCallOnScriptErrorWhenContinuing);

/////////////////////////////////////////////////////////////////////////////
// IApplicationDebugger
	STDMETHOD(QueryAlive)(void);
	STDMETHOD(CreateInstanceAtDebugger)(/*[in]*/ REFCLSID rclsid,/*[in]*/ IUnknown *pUnkOuter,/*[in]*/ DWORD
																	dwClsContext,/*[in]*/ REFIID riid,/*[out,iid_is(riid)]*/ IUnknown **ppvObject);
	STDMETHOD(onDebugOutput)(/*[in]*/ LPCOLESTR pstr );
	STDMETHOD(onHandleBreakPoint)(/*[in]*/ IRemoteDebugApplicationThread *prpt,/*[in]*/ BREAKREASON br,/*[in]*/
															IActiveScriptErrorDebug *pError);
	STDMETHOD(onClose)();
	STDMETHOD(onDebuggerEvent)(/* [in] */ REFIID riid, /* [in] */ IUnknown __RPC_FAR *punk);

/////////////////////////////////////////////////////////////////////////////
// IDebugSessionProvider
	STDMETHOD(StartDebugSession)(/*[in]*/ IRemoteDebugApplication* pApp);
};

#endif
#endif	// _WINDOWS

#endif
