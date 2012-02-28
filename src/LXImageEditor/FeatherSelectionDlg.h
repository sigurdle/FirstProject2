// FeatherSelectionDlg.h : Declaration of the CFeatherSelectionDlg

#ifndef __FEATHERSELECTIONDLG_H_
#define __FEATHERSELECTIONDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CFeatherSelectionDlg
class CFeatherSelectionDlg : 
	public CAxDialogImpl<CFeatherSelectionDlg>
{
public:
	CFeatherSelectionDlg()
	{
	}

	~CFeatherSelectionDlg()
	{
	}

	int m_radius;

	enum { IDD = IDD_FEATHERSELECTIONDLG };

BEGIN_MSG_MAP(CFeatherSelectionDlg)
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
		SetDlgItemInt(IDC_FEATHER_RADIUS, m_radius);
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_radius = GetDlgItemInt(IDC_FEATHER_RADIUS);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__FEATHERSELECTIONDLG_H_
