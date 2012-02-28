// SettingsFilenameConstraintsDlg.h : Declaration of the CSettingsFilenameConstraintsDlg

#ifndef __SETTINGSFILENAMECONSTRAINTSDLG_H_
#define __SETTINGSFILENAMECONSTRAINTSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CSettingsFilenameConstraintsDlg
class CSettingsFilenameConstraintsDlg : 
	public CAxPropertyPageImpl<CSettingsFilenameConstraintsDlg>
{
public:
	CSettingsFilenameConstraintsDlg()
	{
	}

	~CSettingsFilenameConstraintsDlg()
	{
	}

	enum { IDD = IDD_SETTINGSFILENAMECONSTRAINTSDLG };

BEGIN_MSG_MAP(CSettingsFilenameConstraintsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CSettingsFilenameConstraintsDlg>)
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

#if 0
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
#endif
};

#endif //__SETTINGSFILENAMECONSTRAINTSDLG_H_
