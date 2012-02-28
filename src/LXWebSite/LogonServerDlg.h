// LogonServerDlg.h : Declaration of the CLogonServerDlg

#ifndef __LOGONSERVERDLG_H_
#define __LOGONSERVERDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CLogonServerDlg
class CLogonServerDlg : 
	public CAxDialogImpl<CLogonServerDlg>
{
public:
	CLogonServerDlg()
	{
	}

	~CLogonServerDlg()
	{
	}

	_bstr_t m_server;
	_bstr_t m_username;
	_bstr_t m_password;

	enum { IDD = IDD_LOGONSERVERDLG };

BEGIN_MSG_MAP(CLogonServerDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		SetDlgItemText(IDC_LOGON_SERVER, m_server);
		SetDlgItemText(IDC_LOGON_USERNAME, m_username);
		SetDlgItemText(IDC_LOGON_PASSWORD, m_password);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		TCHAR buf[1024];
	
		GetDlgItemText(IDC_LOGON_SERVER, buf, sizeof(buf));
		m_server = buf;

		GetDlgItemText(IDC_LOGON_USERNAME, buf, sizeof(buf));
		m_username = buf;

		GetDlgItemText(IDC_LOGON_PASSWORD, buf, sizeof(buf));
		m_password = buf;

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__LOGONSERVERDLG_H_
