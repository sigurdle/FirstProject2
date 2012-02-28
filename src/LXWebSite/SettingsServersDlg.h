// SettingsServersDlg.h : Declaration of the CSettingsServersDlg

#ifndef __SETTINGSSERVERSDLG_H_
#define __SETTINGSSERVERSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class CLXWebSiteApp;

/////////////////////////////////////////////////////////////////////////////
// CSettingsServersDlg
class CSettingsServersDlg : 
	public CAxPropertyPageImpl<CSettingsServersDlg>
{
public:
	CSettingsServersDlg()
	{
	}

	~CSettingsServersDlg()
	{
	}

	CComboBox m_ftpServer;


	CLXWebSiteApp* m_pApp;

	CComBSTR m_ftpServerName;

	enum { IDD = IDD_SETTINGSSERVERSDLG };

BEGIN_MSG_MAP(CSettingsServersDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CSettingsServersDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	BOOL OnApply()
	{
		USES_CONVERSION;

		TCHAR buf[512];
		m_ftpServer.GetWindowText(buf, _countof(buf));
		m_ftpServerName = A2W(buf);

		return TRUE;
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

#endif //__SETTINGSSERVERSDLG_H_
