// SectionOptionsDlg.h : Declaration of the CSectionOptionsDlg

#ifndef __SECTIONOPTIONSDLG_H_
#define __SECTIONOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CSectionOptionsDlg
class CSectionOptionsDlg : 
	public CAxDialogImpl<CSectionOptionsDlg>
{
public:
	CSectionOptionsDlg()
	{
		m_bSection = FALSE;
		m_pageNumbering = 0;
		m_pageNumberingStartAt = 0;
	}

	~CSectionOptionsDlg()
	{
	}

	enum { IDD = IDD_SECTIONOPTIONSDLG };

	BOOL m_bSection;
	long m_pageNumbering;
	long m_pageNumberingStartAt;

BEGIN_MSG_MAP(CSectionOptionsDlg)
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
		CheckDlgButton(IDC_SECTIONOPTIONS_STARTSECTION, m_bSection);

		CheckRadioButton(IDC_SECTIONOPTIONS_PAGENUMBERING0, IDC_SECTIONOPTIONS_PAGENUMBERING1, IDC_SECTIONOPTIONS_PAGENUMBERING0+m_pageNumbering);
		SetDlgItemInt(IDC_SECTIONOPTIONS_PAGENUMBERING_STARTAT, m_pageNumberingStartAt);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_bSection = IsDlgButtonChecked(IDC_SECTIONOPTIONS_STARTSECTION);

		if (IsDlgButtonChecked(IDC_SECTIONOPTIONS_PAGENUMBERING0))
			m_pageNumbering = 0;
		else if (IsDlgButtonChecked(IDC_SECTIONOPTIONS_PAGENUMBERING0+1))
			m_pageNumbering = 1;

		m_pageNumberingStartAt = GetDlgItemInt(IDC_SECTIONOPTIONS_PAGENUMBERING_STARTAT);


		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__SECTIONOPTIONSDLG_H_
