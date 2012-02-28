// CommandsDlg.h : Declaration of the CCommandsDlg

#ifndef __COMMANDSDLG_H_
#define __COMMANDSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CCommandsDlg
class CCommandsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public CAxPropertyPageImpl<CCommandsDlg>
//	public IUnknown,
//	public IDispEventImpl<1, CCommandsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<2, CCommandsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>
{
public:
	CCommandsDlg() : m_commands(NULL/*"LISTBOX"*/, this, 1)
	{
	}

	~CCommandsDlg()
	{
	}

	CComPtr<IUIManager> m_uiManager;

//	IUIListControlPtr c_categories;
//	IUIListControlPtr c_commands;

	CContainedWindow m_commands;

	enum { IDD = IDD_COMMANDSDLG };

	/*
BEGIN_COM_MAP(CCommandsDlg)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()
*/

#if 0
BEGIN_SINK_MAP(CCommandsDlg)
	SINK_ENTRY_EX(1, DIID__IUIListControlEvents, /*dispid*/1, OnCategory)
	SINK_ENTRY_EX(2, DIID__IUIListControlEvents, /*dispid*/1, OnCommand)
END_SINK_MAP()

	void __stdcall OnCategory();
	void __stdcall OnCommand();
#endif

BEGIN_MSG_MAP(CCommandsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	COMMAND_HANDLER(IDC_COMMANDS_CATEGORIES, LBN_SELCHANGE, OnChangeCategory)
//	COMMAND_HANDLER(IDC_COMMANDS_COMMANDS, LBN_SELCHANGE, OnChangeCommand)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
ALT_MSG_MAP(1)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnCommandsLButtonDown)

END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnChangeCategory(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCommandsLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

#endif //__COMMANDSDLG_H_
