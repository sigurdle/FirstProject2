// ToolbarsDlg.h : Declaration of the CToolbarsDlg

#ifndef __TOOLBARSDLG_H_
#define __TOOLBARSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CToolsbarsDlg
class CToolbarsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public CAxPropertyPageImpl<CToolbarsDlg>
//	public IUnknown,
//	public IDispEventImpl<1, CToolbarsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>
{
public:
	CToolbarsDlg() : m_list(NULL, this, 1)
	{
	}

	~CToolbarsDlg()
	{
	}

	CComPtr<IUIManager> m_uiManager;

//	IUIListControlPtr m_list;

	CContainedWindow m_list;

	enum { IDD = IDD_TOOLBARSDLG };

	void InitListBox();

	/*
BEGIN_COM_MAP(CToolbarsDlg)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()
*/

#if 0
BEGIN_SINK_MAP(CToolbarsDlg)
	SINK_ENTRY_EX(1, DIID__IUIListControlEvents, /*dispid*/2, OnCheckToolBar)
  // SINK_ENTRY_EX(2, DIID__IUIButtonEvents, /*dispid*/1, OnNewBar)
END_SINK_MAP()

	void __stdcall OnCheckToolBar();
	HRESULT __stdcall OnNewBar();
#endif

BEGIN_MSG_MAP(CToolbarsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
	COMMAND_ID_HANDLER(IDC_NEWTOOLBAR, OnNewToolbar)
ALT_MSG_MAP(1)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnToolbarsLButtonDown)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnNewToolbar(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnToolbarsLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

#endif //__TOOLBARSDLG_H_
