// FTPView.h : Declaration of the CFTPView

#ifndef __FTPVIEW_H_
#define __FTPVIEW_H_

#include "resource.h"       // main symbols

class CSiteItem;

#import "..\FTPMod\FTPMod.tlb" no_namespace, named_guids, raw_interfaces_only

/////////////////////////////////////////////////////////////////////////////
// CFTPView
class ATL_NO_VTABLE CFTPView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CFTPView, &CLSID_FTPView>,
	public IConnectionPointContainerImpl<CFTPView>,
//	public IDispatchImpl<IFTPView, &IID_IFTPView, &LIBID_WEBEDITORLib>,
	public ProcessTargetCommands,
	public CUIDialogImpl<CFTPView, CWindowImpl<CFTPView> >
{
public:

	CFTPView()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	CComboBox m_server;
	CButton m_connect;

//	CComQIPtr<IWebSite>	m_document;

	CAxWindow m_axftpBrowser;
	CComPtr<IFTPBrowser> m_ftpBrowser;

	void OnSize();

//DECLARE_REGISTRY_RESOURCEID(IDR_FTPView)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFTPView)
//	COM_INTERFACE_ENTRY(IFTPView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY2(IDispatch, IFTPView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CFTPView)
END_CONNECTION_POINT_MAP()

DECLARE_CMD_MAP(CFTPView)

BEGIN_MSG_MAP(CFTPView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
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
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

/*
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// IFTPView
public:
//	STDMETHOD(get_document)(/*[out, retval]*/ IWebSite* *pVal);
//	STDMETHOD(put_document)(/*[in]*/ IWebSite* newVal);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"FTP");
		return S_OK;
	}
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
	{
		/*
		CComQIPtr<ICommandTarget> target;
		
	// Try document first
	//	target = m_document;
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
		*/

	// Then try us
		return ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	}
};

#endif //__FTPVIEW_H_
