// ThreadsDlg.h : Declaration of the CThreadsDlg

#ifndef __THREADSDLG_H_
#define __THREADSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class DebugProcess;

/////////////////////////////////////////////////////////////////////////////
// CThreadsDlg
class CThreadsDlg : 
	public CAxDialogImpl<CThreadsDlg>
{
public:
	CThreadsDlg()
	{
		m_pDebugProcess = NULL;
	}

	~CThreadsDlg()
	{
	}

	enum { IDD = IDD_THREADSDLG };

	DebugProcess* m_pDebugProcess;

BEGIN_MSG_MAP(CThreadsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

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

#endif //__THREADSDLG_H_
