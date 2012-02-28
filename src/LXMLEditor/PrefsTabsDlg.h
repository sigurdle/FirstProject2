// PrefsTabsDlg.h : Declaration of the CPrefsTabsDlg

#ifndef __PREFSTABSDLG_H_
#define __PREFSTABSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CPrefsTabsDlg : 
	public CAxPropertyPageImpl<CPrefsTabsDlg>
{
public:
	CPrefsTabsDlg()
	{
		m_tabSize = 0;
	}

	~CPrefsTabsDlg()
	{
	}

	int m_tabSize;

	enum { IDD = IDD_PREFSTABSDLG };

	/*
BEGIN_MSG_MAP(CPrefsTabsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CPrefsTabsDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
*/
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog()
	{
		SetDlgItemInt(IDC_TABS_TABSIZE, m_tabSize);
		return 1;  // Let the system set the focus
	}

	bool OnApply()
	{
		m_tabSize = GetDlgItemInt(IDC_TABS_TABSIZE);

		return true;
	}

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

}
}

#endif //__PREFSTABSDLG_H_
