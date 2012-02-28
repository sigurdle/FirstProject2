// MasterOptionsDlg.h : Declaration of the CMasterOptionsDlg

#ifndef __MASTEROPTIONSDLG_H_
#define __MASTEROPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CMasterOptionsDlg
class CMasterOptionsDlg : 
	public CAxDialogImpl<CMasterOptionsDlg>
{
public:
	CMasterOptionsDlg()
	{
		m_numPages = 0;
	}

	~CMasterOptionsDlg()
	{
	}

	int m_numPages;
	_bstr_t m_prefix;
	_bstr_t m_name;

	enum { IDD = IDD_MASTEROPTIONSDLG };

BEGIN_MSG_MAP(CMasterOptionsDlg)
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
		SetDlgItemInt(IDC_MASTER_NUMPAGES, m_numPages);
		SetDlgItemText(IDC_MASTER_PREFIX, m_prefix);
		SetDlgItemText(IDC_MASTER_NAME, m_name);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_numPages = GetDlgItemInt(IDC_MASTER_NUMPAGES);
		if (m_numPages < 1 || m_numPages > 10)
		{
			MessageBox("Number of pages must be between 1..10", "PageDesigner", MB_OK);

			::SetFocus(GetDlgItem(IDC_MASTER_NUMPAGES));
			::SendMessage(GetDlgItem(IDC_MASTER_NUMPAGES), EM_SETSEL, 0, -1);
			return 0;
		}

		TCHAR buf[256];

		GetDlgItemText(IDC_MASTER_PREFIX, buf, sizeof(buf));
		m_prefix = buf;

		GetDlgItemText(IDC_MASTER_NAME, buf, sizeof(buf));
		m_name = buf;

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__MASTEROPTIONSDLG_H_
