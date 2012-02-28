// NewSiteWorkgroupLogonDlg.h : Declaration of the CNewSiteWorkgroupLogonDlg

#ifndef __NEWSITEWORKGROUPLOGONDLG_H_
#define __NEWSITEWORKGROUPLOGONDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "NewSiteData.h"

/////////////////////////////////////////////////////////////////////////////
// CNewSiteWorkgroupLogonDlg
class CNewSiteWorkgroupLogonDlg : 
	public CPropertyPageImpl<CNewSiteWorkgroupLogonDlg>
{
public:
	CNewSiteWorkgroupLogonDlg()
	{
	}

	~CNewSiteWorkgroupLogonDlg()
	{
	}

	CNewSiteData* m_data;
	int m_previousIDD;

	_bstr_t m_server;
	_bstr_t m_username;
	_bstr_t m_password;

	enum { IDD = IDD_NEWSITEWORKGROUPLOGONDLG };

BEGIN_MSG_MAP(CNewSiteWorkgroupLogonDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CPropertyPageImpl<CNewSiteWorkgroupLogonDlg>)
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

	BOOL OnSetActive()
	{
		m_previousIDD = m_data->m_previousIDD;

		SetDlgItemText(IDC_LOGON_SERVER, m_server);
		SetDlgItemText(IDC_LOGON_USERNAME, m_username);
		SetDlgItemText(IDC_LOGON_PASSWORD, m_password);

//		SetWizardButtons();

		return TRUE;
	}

	int OnWizardBack()
	{
		return m_previousIDD;
		// 0  = goto next page
		// -1 = prevent page change
		// >0 = jump to page by dlg ID
	}

	int OnWizardNext()
	{
		// 0  = goto next page
		// -1 = prevent page change
		// >0 = jump to page by dlg ID

		TCHAR buf[1024];
	
		GetDlgItemText(IDC_LOGON_SERVER, buf, sizeof(buf));
		m_server = buf;

		GetDlgItemText(IDC_LOGON_USERNAME, buf, sizeof(buf));
		m_username = buf;

		GetDlgItemText(IDC_LOGON_PASSWORD, buf, sizeof(buf));
		m_password = buf;

		m_data->m_previousIDD = IDD;

		return IDD_NEWSITEFINISHDLG;
	}

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

#endif //__NEWSITEWORKGROUPLOGONDLG_H_
