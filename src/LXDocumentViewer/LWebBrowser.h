// LWebBrowser.h : Declaration of the CLWebBrowser

#ifndef __LWEBBROWSER_H_
#define __LWEBBROWSER_H_

#include "resource.h"       // main symbols

#include "../CmdHandler.h"

class CLXDocumentViewerApp;

/////////////////////////////////////////////////////////////////////////////
// CLWebBrowser
class ATL_NO_VTABLE CLWebBrowser : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CLWebBrowser, &CLSID_LWebBrowser>,
//	public IDispatchImpl<ILWebBrowser, &IID_ILWebBrowser, &LIBID_LXDOCUMENTVIEWERLib>,

//	public ILXAddin,
//	public IUIManagerSite,
	public ProcessTargetCommands,

//	public ILCustomizable,

#if _WINDOWS
	public IDispatchImpl<IWebBrowser2, &IID_IWebBrowser2>,//IWebBrowserApp//IWebBrowser
#endif
	public IServiceProviderImpl<CLWebBrowser>
{
public:
	CLWebBrowser()
	{
		m_pApp = NULL;
	}

	CLXDocumentViewerApp* m_pApp;

	CComPtr<ILXUIWindowBase> m_windowElement;

	HRESULT Init(CLXDocumentViewerApp* pApp, CLWebBrowser* pOtherView);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLWebBrowser)
	COM_INTERFACE_ENTRY(ILDOMEventListener)

///////////////////////////////////////////
//	COM_INTERFACE_ENTRY(IDispatch)
#if _WINDOWS
	COM_INTERFACE_ENTRY(IWebBrowser)
	COM_INTERFACE_ENTRY(IWebBrowserApp)
	COM_INTERFACE_ENTRY(IWebBrowser2)
#endif
///////////////////////////////////////////

	COM_INTERFACE_ENTRY(IServiceProvider)
END_COM_MAP()

BEGIN_SERVICE_MAP(CLWebBrowser)
#if _WINDOWS
	if (::InlineIsEqualGUID(guidService, IID_IWebBrowserApp))
			return QueryInterface(riid, ppvObject);
#endif
END_SERVICE_MAP()

DECLARE_CMD_MAP(CLWebBrowser)

	LRESULT OnNewWindow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

public:
// ILDOMEventListener
	STDMETHOD(handleEvent)(ILDOMEvent* evt);

#if _WINDOWS
// IWebBrowser
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GoBack( void);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GoForward( void);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GoHome( void);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GoSearch( void);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Navigate(
            /* [in] */ BSTR URL,
            /* [optional][in] */ VARIANT *Flags,
            /* [optional][in] */ VARIANT *TargetFrameName,
            /* [optional][in] */ VARIANT *PostData,
            /* [optional][in] */ VARIANT *Headers);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh2( 
            /* [optional][in] */ VARIANT *Level);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch **ppDisp);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch **ppDisp);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Container( 
            /* [retval][out] */ IDispatch **ppDisp);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [retval][out] */ IDispatch **ppDisp);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TopLevelContainer( 
            /* [retval][out] */ VARIANT_BOOL *pBool);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR *Type);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long *pl);
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long Left);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long *pl);
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long Top);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long *pl);
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long Width);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long *pl);
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long Height);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LocationName( 
            /* [retval][out] */ BSTR *LocationName); 
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LocationURL( 
            /* [retval][out] */ BSTR *LocationURL);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Busy( 
            /* [retval][out] */ VARIANT_BOOL *pBool);

// IWebBrowserApp
	virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Quit( void);
	
	virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ClientToWindow( 
		/* [out][in] */ int *pcx,
		/* [out][in] */ int *pcy);
		
	virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE PutProperty( 
		/* [in] */ BSTR Property,
		/* [in] */ VARIANT vtValue);
		
	virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProperty( 
		/* [in] */ BSTR Property,
		/* [retval][out] */ VARIANT *pvtValue);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
		/* [retval][out] */ BSTR *Name);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HWND( 
		/* [retval][out] */ SHANDLE_PTR *pHWND);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FullName( 
		/* [retval][out] */ BSTR *FullName);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Path( 
		/* [retval][out] */ BSTR *Path);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
		/* [retval][out] */ VARIANT_BOOL *pBool);
		
	virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
		/* [in] */ VARIANT_BOOL Value);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_StatusBar( 
		/* [retval][out] */ VARIANT_BOOL *pBool);
		
	virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_StatusBar( 
		/* [in] */ VARIANT_BOOL Value);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
		/* [retval][out] */ BSTR *StatusText);
		
	virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_StatusText( 
		/* [in] */ BSTR StatusText);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ToolBar( 
		/* [retval][out] */ int *Value);
		
	virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ToolBar( 
		/* [in] */ int Value);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_MenuBar( 
		/* [retval][out] */ VARIANT_BOOL *Value);
		
	virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MenuBar( 
		/* [in] */ VARIANT_BOOL Value);
		
	virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FullScreen( 
		/* [retval][out] */ VARIANT_BOOL *pbFullScreen);
		
	virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_FullScreen( 
		/* [in] */ VARIANT_BOOL bFullScreen);

// IWebBrowser2
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Navigate2( 
            /* [in] */ VARIANT *URL,
            /* [optional][in] */ VARIANT *Flags,
            /* [optional][in] */ VARIANT *TargetFrameName,
            /* [optional][in] */ VARIANT *PostData,
            /* [optional][in] */ VARIANT *Headers);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryStatusWB( 
            /* [in] */ OLECMDID cmdID,
            /* [retval][out] */ OLECMDF *pcmdf);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecWB( 
            /* [in] */ OLECMDID cmdID,
            /* [in] */ OLECMDEXECOPT cmdexecopt,
            /* [optional][in] */ VARIANT *pvaIn,
            /* [optional][in][out] */ VARIANT *pvaOut);
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowBrowserBar( 
            /* [in] */ VARIANT *pvaClsid,
            /* [optional][in] */ VARIANT *pvarShow,
            /* [optional][in] */ VARIANT *pvarSize);
        
        virtual /* [bindable][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReadyState( 
            /* [out][retval] */ READYSTATE *plReadyState);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Offline( 
            /* [retval][out] */ VARIANT_BOOL *pbOffline);
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Offline( 
            /* [in] */ VARIANT_BOOL bOffline);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Silent( 
            /* [retval][out] */ VARIANT_BOOL *pbSilent);
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Silent( 
            /* [in] */ VARIANT_BOOL bSilent);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RegisterAsBrowser( 
            /* [retval][out] */ VARIANT_BOOL *pbRegister);
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_RegisterAsBrowser( 
            /* [in] */ VARIANT_BOOL bRegister);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RegisterAsDropTarget( 
            /* [retval][out] */ VARIANT_BOOL *pbRegister);
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_RegisterAsDropTarget( 
            /* [in] */ VARIANT_BOOL bRegister);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TheaterMode( 
            /* [retval][out] */ VARIANT_BOOL *pbRegister);
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_TheaterMode( 
            /* [in] */ VARIANT_BOOL bRegister);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AddressBar( 
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_AddressBar( 
            /* [in] */ VARIANT_BOOL Value);
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Resizable( 
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Resizable( 
            /* [in] */ VARIANT_BOOL Value);
#endif
};


#endif //__LWEBBROWSER_H_
