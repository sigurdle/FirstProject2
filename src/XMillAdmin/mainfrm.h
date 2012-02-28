// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E3F65D93_4835_40A9_B579_A7AC4329C1FC__INCLUDED_)
#define AFX_MAINFRM_H__E3F65D93_4835_40A9_B579_A7AC4329C1FC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\UIT\UIT.h"

class ATL_NO_VTABLE CMainFrame :
	public CComObjectRootEx<CComSingleThreadModel>,

//	public CMDIFrameWindowImpl<CMainFrame>,
//	public CUpdateUI<CMainFrame>,

	public CUIManagerImpl<CMainFrame>,
	public CUIMDIFrameImpl<CMainFrame, IUIFrame>,

	public ProcessTargetCommands,

	public CMessageFilter//, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CMDIFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		HWND hWnd = MDIGetActive();
		if(hWnd != NULL)
			return (BOOL)::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg);

		return FALSE;
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

BEGIN_COM_MAP(CMainFrame)
//	COM_INTERFACE_ENTRY(IWebEditorFrame)
//	COM_INTERFACE_ENTRY2(IDispatch, DispIWebEditorFrame)
//	COM_INTERFACE_ENTRY(IDispatch)

//	COM_INTERFACE_ENTRY(IPersist)

	COM_INTERFACE_ENTRY(ICommandTarget)
//	COM_INTERFACE_ENTRY(ICustomDraw)

/*
	COM_INTERFACE_ENTRY(IOleWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceUIWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceFrame)
	COM_INTERFACE_ENTRY(IOleCommandTarget)
*/
	COM_INTERFACE_ENTRY(IUIManager)

	COM_INTERFACE_ENTRY(IUIFrame)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

	typedef CUIMDIFrameImpl<CMainFrame, IUIFrame> baseClass;

BEGIN_MSG_MAP(CMainFrame)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
	COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
	COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
	COMMAND_ID_HANDLER(ID_WINDOW_CASCADE, OnWindowCascade)
	COMMAND_ID_HANDLER(ID_WINDOW_TILE_HORZ, OnWindowTile)
	COMMAND_ID_HANDLER(ID_WINDOW_ARRANGE, OnWindowArrangeIcons)
//	CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
	CHAIN_MSG_MAP(baseClass)
END_MSG_MAP()

DECLARE_CMD_MAP(CMainFrame)

/*
BEGIN_UPDATE_UI_MAP(CMainFrame)
END_UPDATE_UI_MAP()
*/

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
//		pLoop->RemoveIdleHandler(this);
		// if UI is the last thread, no need to wait
		if(_Module.GetLockCount() == 1)
		{
			_Module.m_dwTimeOut = 0L;
			_Module.m_dwPause = 0L;
		}
		_Module.Unlock();

		return baseClass::OnDestroy(uMsg, wParam, lParam, bHandled);
	}

	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_CLOSE);
		return 0;
	}

	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		/*
		CChildFrame* pChild = new CChildFrame;
		pChild->CreateEx(m_hWndClient);

		// TODO: add code to initialize document
		*/

		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		/*
		CAboutDlg dlg;
		dlg.DoModal();
		*/
		return 0;
	}

	LRESULT OnWindowCascade(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		MDICascade();
		return 0;
	}

	LRESULT OnWindowTile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		MDITile();
		return 0;
	}

	LRESULT OnWindowArrangeIcons(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		MDIIconArrange();
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E3F65D93_4835_40A9_B579_A7AC4329C1FC__INCLUDED_)
