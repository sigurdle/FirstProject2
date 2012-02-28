// DropShadowDlg.h : Declaration of the CDropShadowDlg

#ifndef __DROPSHADOWDLG_H_
#define __DROPSHADOWDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CDropShadowDlg
class CDropShadowDlg : 
	public CAxDialogImpl<CDropShadowDlg>
{
public:
	CDropShadowDlg()
	{
	}

	~CDropShadowDlg()
	{
	}

	int m_angle;
	int m_distance;
	int m_size;

	enum { IDD = IDD_DROPSHADOWDLG };

BEGIN_MSG_MAP(CDropShadowDlg)
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
		SetDlgItemInt(IDC_DROPSHADOW_ANGLE, m_angle);
		SetDlgItemInt(IDC_DROPSHADOW_DISTANCE, m_distance);
		SetDlgItemInt(IDC_DROPSHADOW_SIZE, m_size);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_angle = GetDlgItemInt(IDC_DROPSHADOW_ANGLE);
		m_distance = GetDlgItemInt(IDC_DROPSHADOW_DISTANCE);
		m_size = GetDlgItemInt(IDC_DROPSHADOW_SIZE);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__DROPSHADOWDLG_H_
