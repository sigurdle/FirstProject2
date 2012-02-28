// BreakpointsDlg.h : Declaration of the CBreakpointsDlg

#ifndef __BREAKPOINTSDLG_H_
#define __BREAKPOINTSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class CMainFrame;

/////////////////////////////////////////////////////////////////////////////
// CBreakpointsDlg
class CBreakpointsDlg : 
	public CAxDialogImpl<CBreakpointsDlg>
{
public:
	CBreakpointsDlg()
	{
	}

	~CBreakpointsDlg()
	{
	}

	CMainFrame* m_pFrame;

	enum { IDD = IDD_BREAKPOINTSDLG };

BEGIN_MSG_MAP(CBreakpointsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_BREAKPOINT_REMOVEALL, OnRemoveAll)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnRemoveAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

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

#endif //__BREAKPOINTSDLG_H_
