// SiteFTPView.h : Declaration of the CSiteFTPView

#ifndef __SITEFTPVIEW_H_
#define __SITEFTPVIEW_H_

//#include "resource.h"       // main symbols

class CWebSite;

#import "..\FTPMod\FTPMod.tlb" no_namespace, named_guids, raw_interfaces_only

/////////////////////////////////////////////////////////////////////////////
// CSiteFTPView
class ATL_NO_VTABLE CSiteFTPView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSiteFTPView, &CLSID_SiteFTPView>,
	public IConnectionPointContainerImpl<CSiteFTPView>,
	public IDispatchImpl<ISiteFTPView, &IID_ISiteFTPView, &LIBID_LXWEBSITELib>,
	public ProcessTargetCommands,
	public CUIDialogImpl<CSiteFTPView, CWindowImpl<CSiteFTPView> >,

	public IBindStatusCallback,
	public IAuthenticate,
	public IServiceProviderImpl<CSiteFTPView>,

	public IDispEventImpl<1, CSiteFTPView, &DIID__IFTPBrowserEvents, &LIBID_FTPMODLib, 1, 0>
{
public:

	CSiteFTPView()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	CWebSite*	m_document;

	CAxWindow m_axftpBrowser;
	CComQIPtr<IFTPBrowser> m_ftpBrowser;

	void OnSize();

//DECLARE_REGISTRY_RESOURCEID(IDR_SITEFTPVIEW)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSiteFTPView)
	COM_INTERFACE_ENTRY(ISiteFTPView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, ISiteFTPView)

	COM_INTERFACE_ENTRY(IBindStatusCallback)
	COM_INTERFACE_ENTRY(IAuthenticate)

	COM_INTERFACE_ENTRY(IServiceProvider)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_SERVICE_MAP(CSiteFTPView)
//	SERVICE_ENTRY(SID_SHlinkFrame)
	if (::InlineIsEqualGUID(guidService, IID_IAuthenticate))
			return QueryInterface(riid, ppvObject);

END_SERVICE_MAP()

BEGIN_CONNECTION_POINT_MAP(CSiteFTPView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CSiteFTPView)
   SINK_ENTRY_EX(1, DIID__IFTPBrowserEvents, /*dispid*/1, OnDblClick)
END_SINK_MAP()

	void __stdcall OnDblClick(/*[in]*/ BSTR url);

BEGIN_MSG_MAP(CSiteFTPView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
/*
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
*/
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CSiteFTPView)

	LRESULT OnFTPConnect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

/*
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// ISiteFTPView
public:
	STDMETHOD(get_document)(/*[out, retval]*/ IWebSite* *pVal);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"FTP");
		return S_OK;
	}
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);

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

	CComPtr<IBinding> m_spBinding;

// IBindStatusCallback
	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding __RPC_FAR *pib);
	STDMETHOD(GetPriority)(LONG __RPC_FAR *pnPriority);
	STDMETHOD(OnLowResource)(DWORD reserved);
	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText);
	STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError);
	STDMETHOD(GetBindInfo)(DWORD __RPC_FAR *grfBINDF, BINDINFO __RPC_FAR *pbindinfo);
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR *pformatetc, STGMEDIUM __RPC_FAR *pstgmed);
	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown __RPC_FAR *punk);
};

#endif //__SITEFTPVIEW_H_
