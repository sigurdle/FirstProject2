// PrefsConnectionDlg.h : Declaration of the CPrefsConnectionDlg

#ifndef __PREFSCONNECTIONDLG_H_
#define __PREFSCONNECTIONDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class CPreferences;

/////////////////////////////////////////////////////////////////////////////
// CPrefsConnectionDlg
class CPrefsConnectionDlg : 
	public CAxPropertyPageImpl<CPrefsConnectionDlg>
{
public:
	CPrefsConnectionDlg()
	{
	}

	~CPrefsConnectionDlg()
	{
	}

	CPreferences* m_pPrefs;

	enum { IDD = IDD_PREFSCONNECTIONDLG };

BEGIN_MSG_MAP(CPrefsConnectionDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CPrefsConnectionDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	BOOL OnApply();

/*
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
	*/
};

#endif //__PREFSCONNECTIONDLG_H_
