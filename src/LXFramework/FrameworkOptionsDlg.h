// FrameworkOptionsDlg.h : Declaration of the CFrameworkOptionsDlg

#ifndef __FRAMEWORKOPTIONSDLG_H_
#define __FRAMEWORKOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CFrameworkOptionsDlg
class CFrameworkOptionsDlg : 
	public CAxPropertyPageImpl<CFrameworkOptionsDlg>
{
public:
	CFrameworkOptionsDlg()
	{
	}

	~CFrameworkOptionsDlg()
	{
	}

	enum { IDD = IDD_FRAMEWORKOPTIONSDLG };

BEGIN_MSG_MAP(CFrameworkOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(IDC_CHANGE_ICON, OnChangeIcon)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CFrameworkOptionsDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 1;  // Let the system set the focus
	}

	BOOL OnApply()
	{
		return TRUE;
	}

	LRESULT OnChangeIcon(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

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

#endif //__FRAMEWORKOPTIONSDLG_H_
