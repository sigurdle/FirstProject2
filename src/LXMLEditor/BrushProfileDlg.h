// BrushProfileDlg.h : Declaration of the CBrushProfileDlg

#ifndef __BRUSHPROFILEDLG_H_
#define __BRUSHPROFILEDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CBrushProfileDlg : 
	public CAxDialogImpl<CBrushProfileDlg>
{
public:
	CBrushProfileDlg()
	{
	}

	~CBrushProfileDlg()
	{
	}

	enum { IDD = IDD_BRUSHPROFILEDLG };

	/*
BEGIN_MSG_MAP(CBrushProfileDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog(bool& bHandled)
	{
		return 1;  // Let the system set the focus
	}

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

#endif //__BRUSHPROFILEDLG_H_
