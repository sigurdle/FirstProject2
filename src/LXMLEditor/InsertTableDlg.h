// InsertTableDlg.h : Declaration of the CInsertTableDlg

#ifndef __INSERTTABLEDLG_H_
#define __INSERTTABLEDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CInsertTableDlg : 
	public CAxDialogImpl<CInsertTableDlg>
{
public:
	CInsertTableDlg()
	{
	// Set default values
		m_rows = 4;
		m_columns = 4;
	}

	~CInsertTableDlg()
	{
	}

	int m_rows;
	int m_columns;

	enum { IDD = IDD_INSERTTABLEDLG };

	/*
BEGIN_MSG_MAP(CInsertTableDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(int wNotifyCode, int wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog(bool& bHandled)
	{
		SetDlgItemInt(IDC_TABLE_ROWS, m_rows);
		SetDlgItemInt(IDC_TABLE_COLUMNS, m_columns);

		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		long rows = GetDlgItemInt(IDC_TABLE_ROWS);
		if (rows < 1 || rows > 99)
		{
			MessageBoxA(NULL, "Enter a number between 1 and 99", "WebEditor", MB_OK);
#if 0
			SendDlgItemMessage(IDC_TABLE_ROWS, EM_SETSEL, 0, -1);
			::SetFocus(GetDlgItem(IDC_TABLE_ROWS));
#endif
		}

		long columns = GetDlgItemInt(IDC_TABLE_COLUMNS);
		if (columns < 1 || columns > 99)
		{
			MessageBoxA(NULL, "Enter a number between 1 and 99", "WebEditor", MB_OK);
#if 0
			SendDlgItemMessage(IDC_TABLE_COLUMNS, EM_SETSEL, 0, -1);
			::SetFocus(GetDlgItem(IDC_TABLE_COLUMNS));
#endif
		}

		m_rows = rows;
		m_columns = columns;

		EndDialog(wID);
		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

}
}

#endif //__INSERTTABLEDLG_H_
