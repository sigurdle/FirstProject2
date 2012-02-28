// ContractSelectionDlg.h : Declaration of the CContractSelectionDlg

#ifndef __CONTRACTSELECTIONDLG_H_
#define __CONTRACTSELECTIONDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CContractSelectionDlg
class CContractSelectionDlg : 
	public CAxDialogImpl<CContractSelectionDlg>
{
public:
	CContractSelectionDlg()
	{
	}

	~CContractSelectionDlg()
	{
	}

	int m_radius;

	enum { IDD = IDD_CONTRACTSELECTIONDLG };

BEGIN_MSG_MAP(CContractSelectionDlg)
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
		SetDlgItemInt(IDC_CONTRACT_RADIUS, m_radius);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_radius = GetDlgItemInt(IDC_CONTRACT_RADIUS);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__CONTRACTSELECTIONDLG_H_
