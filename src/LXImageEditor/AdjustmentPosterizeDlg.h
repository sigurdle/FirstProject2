// AdjustmentPosterizeDlg.h : Declaration of the CAdjustmentPosterizeDlg

#ifndef __ADJUSTMENTPOSTERIZEDLG_H_
#define __ADJUSTMENTPOSTERIZEDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CAdjustmentPosterizeDlg
class CAdjustmentPosterizeDlg : 
	public CAxDialogImpl<CAdjustmentPosterizeDlg>
{
public:
	CAdjustmentPosterizeDlg()
	{
	}

	~CAdjustmentPosterizeDlg()
	{
	}

	enum { IDD = IDD_ADJUSTMENTPOSTERIZEDLG };

BEGIN_MSG_MAP(CAdjustmentPosterizeDlg)
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
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__ADJUSTMENTPOSTERIZEDLG_H_
