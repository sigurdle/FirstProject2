// NewSiteFTPDlg.h : Declaration of the CNewSiteFTPDlg

#ifndef __NEWSITEFTPDLG_H_
#define __NEWSITEFTPDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#import "..\FTPMod\FTPMod.tlb" no_namespace, named_guids, raw_interfaces_only

class CFTPBrowserDlg :
	public CAxDialogImpl<CFTPBrowserDlg>
{
public:
	CComPtr<IFTPBrowser> m_ftpBrowser;

	_bstr_t m_serverName;
	_bstr_t m_userName;

	enum { IDD = IDD_FTPBROWSERDLG };

BEGIN_MSG_MAP(CFTPBrowserDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		GetDlgControl(IDC_FTPBROWSER, IID_IFTPBrowser, (void**)&m_ftpBrowser);
		if (m_ftpBrowser)
		{
			m_ftpBrowser->put_ServerName(L"ftp.bredband.no");
			m_ftpBrowser->put_UserName(L"sigler");
			m_ftpBrowser->put_Password(L"9pmbi238");

			VARIANT_BOOL success;
			m_ftpBrowser->Connect(&success);
		}

		return 1;  // Let the system set the focus
	}

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
};

#include "NewSiteData.h"

/////////////////////////////////////////////////////////////////////////////
// CNewSiteFTPDlg
class CNewSiteFTPDlg : 
	public CPropertyPageImpl<CNewSiteFTPDlg>
{
public:
	CNewSiteFTPDlg()
	{
	}

	~CNewSiteFTPDlg()
	{
	}

	CNewSiteData* m_data;
	int m_previousIDD;

	enum { IDD = IDD_NEWSITEFTPDLG };

BEGIN_MSG_MAP(CNewSiteFTPDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_FTP_DIRBROWSE, OnDirBrowse)
	CHAIN_MSG_MAP(CPropertyPageImpl<CNewSiteFTPDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnDirBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CFTPBrowserDlg dlg;

		if (dlg.DoModal(m_hWnd) == IDOK)
		{
		}

		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 1;  // Let the system set the focus
	}

	BOOL OnSetActive()
	{
		SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

		m_previousIDD = m_data->m_previousIDD;
		return TRUE;
	}

	int OnWizardBack()
	{
		return m_previousIDD;
		// 0  = goto next page
		// -1 = prevent page change
		// >0 = jump to page by dlg ID
	}
};

#endif //__NEWSITEFTPDLG_H_
