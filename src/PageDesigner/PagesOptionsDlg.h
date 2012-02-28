// PagesOptionsDlg.h : Declaration of the CPagesOptionsDlg

#ifndef __PAGESOPTIONSDLG_H_
#define __PAGESOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CPagesOptionsDlg
class CPagesOptionsDlg : 
	public CAxDialogImpl<CPagesOptionsDlg>
{
public:
	CPagesOptionsDlg()
	{
		m_pagesIconSize = 1;
		m_mastersIconSize = 1;
		m_resize = 2;
		m_windowOnTop = 1;
	}

	~CPagesOptionsDlg()
	{
	}

	int m_pagesIconSize;
	int m_mastersIconSize;
	int m_resize;
	int m_windowOnTop;

	enum { IDD = IDD_PAGESOPTIONSDLG };

BEGIN_MSG_MAP(CPagesOptionsDlg)
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
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_PAGESSIZE), CB_ADDSTRING, 0, (LPARAM)"Small");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_PAGESSIZE), CB_ADDSTRING, 0, (LPARAM)"Medium");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_PAGESSIZE), CB_ADDSTRING, 0, (LPARAM)"Large");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_PAGESSIZE), CB_ADDSTRING, 0, (LPARAM)"Extra Large");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_PAGESSIZE), CB_SETCURSEL, m_pagesIconSize, 0);

		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_MASTERSSIZE), CB_ADDSTRING, 0, (LPARAM)"Small");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_MASTERSSIZE), CB_ADDSTRING, 0, (LPARAM)"Medium");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_MASTERSSIZE), CB_ADDSTRING, 0, (LPARAM)"Large");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_MASTERSSIZE), CB_ADDSTRING, 0, (LPARAM)"Extra Large");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_MASTERSSIZE), CB_SETCURSEL, m_mastersIconSize, 0);

		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_RESIZE), CB_ADDSTRING, 0, (LPARAM)"Proportional");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_RESIZE), CB_ADDSTRING, 0, (LPARAM)"Pages Fixed");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_RESIZE), CB_ADDSTRING, 0, (LPARAM)"Masters Fixed");
		::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_RESIZE), CB_SETCURSEL, m_resize, 0);

		CheckRadioButton(IDC_PAGESOPTIONS_LAYOUT_ONTOP, IDC_PAGESOPTIONS_LAYOUT_ONTOP2, IDC_PAGESOPTIONS_LAYOUT_ONTOP+m_windowOnTop);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_pagesIconSize = ::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_PAGESSIZE), CB_GETCURSEL, 0, 0);
		m_mastersIconSize = ::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_MASTERSSIZE), CB_GETCURSEL, 0, 0);
		m_resize = ::SendMessage(GetDlgItem(IDC_PAGESOPTIONS_RESIZE), CB_GETCURSEL, 0, 0);

		if (IsDlgButtonChecked(IDC_PAGESOPTIONS_LAYOUT_ONTOP))
			m_windowOnTop = 0;
		else if (IsDlgButtonChecked(IDC_PAGESOPTIONS_LAYOUT_ONTOP+1))
			m_windowOnTop = 1;

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__PAGESOPTIONSDLG_H_
