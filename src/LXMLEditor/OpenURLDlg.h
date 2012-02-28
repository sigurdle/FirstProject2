// OpenURLDlg.h : Declaration of the COpenURLDlg

#ifndef __OPENURLDLG_H_
#define __OPENURLDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class COpenURLDlg : 
	public CAxDialogImpl<COpenURLDlg>
{
public:
	COpenURLDlg()
	{
	}

	~COpenURLDlg()
	{
	}

	System::StringW* m_url;

	enum { IDD = IDD_OPENURLDLG };

	/*
BEGIN_MSG_MAP(COpenURLDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog(bool& bHandled)
	{
		SetDlgItemText(IDC_OPEN_URL, m_url);

		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		WCHAR buf[1024];

		GetDlgItemText(IDC_OPEN_URL, buf, sizeof(buf));
		m_url = new System::StringW(string_copy(buf));

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

#endif //__OPENURLDLG_H_
