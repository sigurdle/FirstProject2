// RegisteredSnapinsDlg.h : Declaration of the CRegisteredSnapinsDlg

#ifndef __REGISTEREDSNAPINSDLG_H_
#define __REGISTEREDSNAPINSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class CAddinsDlg;

/////////////////////////////////////////////////////////////////////////////
// CRegisteredSnapinsDlg
class CRegisteredSnapinsDlg : 
	public CAxDialogImpl<CRegisteredSnapinsDlg>
{
public:
	CRegisteredSnapinsDlg()
	{
	}

	~CRegisteredSnapinsDlg()
	{
	}

	CListViewCtrl m_list;

	CAddinsDlg* m_pParent;

	enum { IDD = IDD_REGISTEREDSNAPINSDLG };

BEGIN_MSG_MAP(CRegisteredSnapinsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__REGISTEREDSNAPINSDLG_H_
