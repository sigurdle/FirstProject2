// ExpandSelectionDlg.h : Declaration of the CExpandSelectionDlg

#ifndef __EXPANDSELECTIONDLG_H_
#define __EXPANDSELECTIONDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CExpandSelectionDlg
class CExpandSelectionDlg : 
	public CAxDialogImpl<CExpandSelectionDlg>
{
public:
	CExpandSelectionDlg()
	{
	}

	~CExpandSelectionDlg()
	{
	}

	int m_radius;

	enum { IDD = IDD_EXPANDSELECTIONDLG };

BEGIN_MSG_MAP(CExpandSelectionDlg)
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
		SetDlgItemInt(IDC_EXPAND_RADIUS, m_radius);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_radius = GetDlgItemInt(IDC_EXPAND_RADIUS);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__EXPANDSELECTIONDLG_H_
