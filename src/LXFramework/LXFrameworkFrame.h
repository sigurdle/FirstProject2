// LXFrameworkFrame.h : Declaration of the CLXFrameworkFrame

#if 0

#ifndef __LXFRAMEWORKFRAME_H_
#define __LXFRAMEWORKFRAME_H_

#include "resource.h"       // main symbols
#include "LXFrameworkCP.h"
//#include "UICP.h"
//#include "UICP.h"

//#include "LXFrameworkCP.h"

//#include "..\UIT\UITImpl.h"

#include "UIManagerImpl.h"

class CLXFrameworkAddinSite;

class ATL_NO_VTABLE CLXFrameworkAddinUIManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
	//public IUnknown
	public CUIManagerImpl//<CLXFrameworkAddinSite>
{
public:
	CLXFrameworkAddinUIManager()
	{
		m_pAddinSite = NULL;
	}

	int FinalConstruct()
	{
		/*
		CComObject<CUISheetDlgClass>* p;
		CComObject<CUISheetDlgClass>::CreateInstance(&p);
		p->AddRef();

		m_dialogs.Add(p);
		*/

		return 0;
	}

	CLXFrameworkAddinSite* m_pAddinSite;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXFrameworkAddinUIManager)
//	COM_INTERFACE_ENTRY(IUnknown)
	COM_INTERFACE_ENTRY(IUIManager)
END_COM_MAP()

   STDMETHODIMP CreateMenuDlg(IUIMenuDlg* *pVal);
	STDMETHODIMP CreateDlgSheet(LPWSTR name, IMenuItem* menu, /*[out,retval]*/ IUIDlgSheet* *pVal);
	STDMETHODIMP RegisterBar(IUIDlgClass* dlgClass, BSTR name, IUIDlgSite* *pVal);
	STDMETHODIMP CreateDlgSite(LPWSTR name, IMenuItem* menu, IUIDlg* dlg, IUIDlgSite* *pVal);
};

class CLXFrameworkFrame;

class ATL_NO_VTABLE CLXFrameworkAddinSite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILXAddinSite
{
public:
	CLXFrameworkAddinSite()
	{
		m_frame = NULL;
		m_clsid = GUID_NULL;
	}

	int FinalConstruct()
	{
		CComObject<CLXFrameworkAddinUIManager>::CreateInstance(&m_uiManager);
		m_uiManager->AddRef();
		m_uiManager->m_pAddinSite = this;

		return 0;
	}

	CComBSTR m_name;
	CLSID m_clsid;
	CComPtr<ILXAddin> m_p;

	CLXFrameworkFrame* m_frame;

	CComObject<CLXFrameworkAddinUIManager>* m_uiManager;

	void SetFrame(CLXFrameworkFrame* frame)
	{
		m_frame = frame;

		ATLASSERT(m_p);

		m_uiManager->m_pSite = CComQIPtr<IUIManagerSite>(m_p);
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXFrameworkAddinSite)
	COM_INTERFACE_ENTRY(ILXAddinSite)
END_COM_MAP()

	STDMETHOD(GetFrame)(/*[out,retval]*/ ILXFrameworkFrame* *pVal);
	STDMETHOD(GetUIManager)(/*[out,retval]*/ IUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_uiManager;
		(*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(GetName)(/*[out,retval]*/ BSTR* pVal)
	{
		return m_name.CopyTo(pVal);
	}
};

class CLXFrameworkApp;

/////////////////////////////////////////////////////////////////////////////
// CLXFrameworkFrame
class ATL_NO_VTABLE CLXFrameworkFrame : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CLXFrameworkFrame, &CLSID_LXFrameworkFrame>,
	public IConnectionPointContainerImpl<CLXFrameworkFrame>,

//	public IDispatchImpl<DispILXFrameworkFrame, &IID_DispILXFrameworkFrame, &LIBID_LXFrameworkLib>,

	public ILXFrameworkFrame,

	public IPersist,
//	public IDispatchImpl<ICustomDraw, &IID_ICustomDraw, &LIBID_UILib>,

	public ProcessTargetCommands,

#if 0
	public IOleInPlaceFrame,
	public IOleCommandTarget,
#endif

	public IBindStatusCallback,	// ??

//	public ILDOMEventListener,

#if 0
	public CUIMDIFrameImpl<CLXFrameworkFrame, IUIMDIFrame>,
#endif
#if 0
	public CWindowImpl<CLXFrameworkFrame>,
#endif

	public CMessageFilter
{
public:
//	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CLXFrameworkFrame()
	{
	}

	~CLXFrameworkFrame()
	{
//		ATLASSERT(m_documents.GetSize() == 0);
	}

	int FinalConstruct();
	void FinalRelease();

//	CArray<IActiveCntDocument*,IActiveCntDocument*> m_documents;

	CComPtr<ILXUIMDIFrameElement> m_element;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
#if 0
		if(CUIMDIFrameImpl<CLXFrameworkFrame, IUIMDIFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		HWND hWnd = MDIGetActive();
		if(hWnd != NULL)
			return (BOOL)::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg);	// ??
#endif

		return FALSE;
	}

	CArray<CComObject<CLXFrameworkAddinSite>*,CComObject<CLXFrameworkAddinSite>*> m_addins;

	CLXFrameworkApp* m_app;

	CComPtr<IOleInPlaceActiveObject> m_pIOleIPActiveObject;

	HRESULT OpenFramework(LPCTSTR filename);
	HRESULT SaveFramework(LPCTSTR filename);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXFrameworkFrame)
	COM_INTERFACE_ENTRY(ILXFrameworkFrame)
//	COM_INTERFACE_ENTRY2(IDispatch, DispILXFrameworkFrame)
//	COM_INTERFACE_ENTRY(IDispatch)

	COM_INTERFACE_ENTRY(IPersist)

	COM_INTERFACE_ENTRY(ILDOMEventListener)

	COM_INTERFACE_ENTRY(IBindStatusCallback)	// ??

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLXFrameworkFrame)
//CONNECTION_POINT_ENTRY(DIID__IUIManagerEvents)
END_CONNECTION_POINT_MAP()

#if 0
	typedef CUIMDIFrameImpl<CLXFrameworkFrame, IUIMDIFrame> baseClass;
#endif

#if 0
BEGIN_MSG_MAP(CLXFrameworkFrame)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_NCACTIVATE, OnNcActivate)

	MESSAGE_HANDLER(WM_NCCALCSIZE, OnNcCalcSize)
//	MESSAGE_HANDLER(WM_NCACTIVATE, OnNcActivate)
//	MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNcLButtonDown)
//	MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
	MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)

#if 0
	// message handling for standard DDE commands
	MESSAGE_HANDLER(WM_DDE_INITIATE, OnDDEInitiate)
	MESSAGE_HANDLER(WM_DDE_EXECUTE, OnDDEExecute)
	MESSAGE_HANDLER(WM_DDE_TERMINATE, OnDDETerminate)
#endif

END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
#endif

	/*
	LRESULT OnDDEInitiate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDDEExecute(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDDETerminate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	*/

DECLARE_CMD_MAP(CLXFrameworkFrame)

	LRESULT OnAddSnapin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAppExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	/*
	LRESULT OnNavigateBack(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnNavigateForward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnNavigateBackUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnNavigateForwardUpdate(long iid, IUICmdUpdate* pCmdUI);
	*/

	STDMETHOD(OpenDocument)(/*[in]*/ BSTR pathName, /*[out,retval]*/ VARIANT_BOOL* success);

	STDMETHOD(OpenDocument)(/*[in]*/ IMoniker *pmk);

// ILXFrameworkFrame
public:
	STDMETHOD(get_Element)(/*[in]*/ ILXUIMDIFrameElement* *pVal);
	STDMETHOD(GetApp)(ILXFrameworkApp* *pVal);
	STDMETHOD(GetWindow)(HWND* phwnd);

// IBindStatusCallback
	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding __RPC_FAR *pib);
	STDMETHOD(GetPriority)(LONG __RPC_FAR *pnPriority);
	STDMETHOD(OnLowResource)(DWORD reserved);
	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText);
	STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError);
	STDMETHOD(GetBindInfo)(DWORD __RPC_FAR *grfBINDF, BINDINFO __RPC_FAR *pbindinfo);
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR *pformatetc, STGMEDIUM __RPC_FAR *pstgmed);
	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown __RPC_FAR *punk);

// IOleInPlaceFrame

	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetMenu( 
	/* [in] */ HMENU hMenu,
	/* [in] */ HOLEMENU hOLEMenu,
	/* [in] */ HWND hWndObj)
	{
	/*
	if (NULL!=hMenu)
	::SetMenu(hwnd, hMenu);
	
	  ::DrawMenuBar(hwnd);
		*/
		
		HRESULT hr;

		ATLASSERT(0);
#if 0
		if (m_menu)
		{
			m_menuBar->put_menuItem(NULL);
			m_menu.Release();
		}
		
		if (hMenu)
		{
			CComObject<CMenuItem>* pMenu;
			CComObject<CMenuItem>::CreateInstance(&pMenu);
			m_menu = pMenu;
			BOOL success;
			m_menu->BuildFromHMenu(hMenu, &success);

			m_menuBar->put_menuItem(m_menu);
		}

		hr=OleSetMenuDescriptor(hOLEMenu, m_hWnd, hWndObj, NULL, NULL);
#endif

		return hr;
	}
	

// IOleCommandTarget
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE QueryStatus( 
         /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
         /* [in] */ ULONG cCmds,
         /* [out][in][size_is] */ OLECMD __RPC_FAR prgCmds[  ],
         /* [unique][out][in] */ OLECMDTEXT __RPC_FAR *pCmdText)
	  {
		  return OLECMDERR_E_UNKNOWNGROUP;
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE Exec( 
         /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
         /* [in] */ DWORD nCmdID,
         /* [in] */ DWORD nCmdexecopt,
         /* [unique][in] */ VARIANT __RPC_FAR *pvaIn,
         /* [unique][out][in] */ VARIANT __RPC_FAR *pvaOut)
	  {
		  return OLECMDERR_E_UNKNOWNGROUP;
		  return S_OK;
	  }

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		//*pClassID = CLSID_LXFrameworkFrame;
		return S_OK;
	}

	// ILDOMEventListener
//	STDMETHOD(handleEvent)(ILDOMEvent* evt);
};

#endif //__LXFRAMEWORKFRAME_H_

#endif