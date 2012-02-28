// NewToolbarDlg.h : Declaration of the CNewToolbarDlg

#ifndef __NEWTOOLBARDLG_H_
#define __NEWTOOLBARDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CNewToolbarDlg
class CNewToolbarDlg : 
	public CAxDialogImpl<CNewToolbarDlg>
{
public:
	CNewToolbarDlg()
	{
	}

	~CNewToolbarDlg()
	{
	}

	_bstr_t m_name;

	enum { IDD = IDD_NEWTOOLBARDLG };

BEGIN_MSG_MAP(CNewToolbarDlg)
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
		SetDlgItemText(IDC_TOOLBARNAME, m_name);
		::SendMessage(GetDlgItem(IDC_TOOLBARNAME), EM_SETSEL, 0, -1);
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		TCHAR buf[256];
		GetDlgItemText(IDC_TOOLBARNAME, buf, sizeof(buf));
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

#endif //__NEWTOOLBARDLG_H_
