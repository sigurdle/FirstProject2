// PrefsLanguageDlg.h : Declaration of the CPrefsLanguageDlg

#ifndef __PREFSLANGUAGEDLG_H_
#define __PREFSLANGUAGEDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class CPreferences;

/////////////////////////////////////////////////////////////////////////////
// CPrefsLanguageDlg
class CPrefsLanguageDlg : 
	public CAxPropertyPageImpl<CPrefsLanguageDlg>
{
public:
	CTOR CPrefsLanguageDlg()
	{
	}

	~CPrefsLanguageDlg()
	{
	}

	CPreferences* m_pPrefs;

	enum { IDD = IDD_PREFSLANGUAGEDLG };

BEGIN_MSG_MAP(CPrefsLanguageDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CPrefsLanguageDlg>)
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

#endif //__PREFSLANGUAGEDLG_H_
