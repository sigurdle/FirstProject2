// KeyboardDlg.h : Declaration of the CKeyboardDlg

#ifndef __KEYBOARDDLG_H_
#define __KEYBOARDDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg
class CKeyboardDlg : 
	public CAxPropertyPageImpl<CKeyboardDlg>
{
public:
	CKeyboardDlg()
	{
	}

	~CKeyboardDlg()
	{
	}

	CComPtr<IUIManager> m_uiManager;

	enum { IDD = IDD_KEYBOARDDLG };

BEGIN_MSG_MAP(CKeyboardDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_KEYBOARD_CATEGORIES, LBN_SELCHANGE, OnChangeCategory)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnChangeCategory(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

/*
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	*/
};

#endif //__KEYBOARDDLG_H_
