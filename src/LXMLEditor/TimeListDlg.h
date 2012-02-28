#ifndef __TIMELISTDLG_H_
#define __TIMELISTDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CTimeListDlg : 
	public CAxDialogImpl<CTimeListDlg>
{
public:
	CTimeListDlg()
	{
	}

	~CTimeListDlg()
	{
	}

	System::StringW* m_title;

	Web::SMILTimeList* m_timeList;

	enum { IDD = IDD_TIMELISTDLG };

	/*
BEGIN_MSG_MAP(CTimeListDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog();

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
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

#endif //__TIMELISTDLG_H_
