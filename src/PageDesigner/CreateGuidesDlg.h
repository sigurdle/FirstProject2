// CreateGuidesDlg.h : Declaration of the CCreateGuidesDlg

#ifndef __CREATEGUIDESDLG_H_
#define __CREATEGUIDESDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CCreateGuidesDlg
class CCreateGuidesDlg : 
	public CAxDialogImpl<CCreateGuidesDlg>
{
public:
	CCreateGuidesDlg()
	{
		m_rowsNumber = 0;
		m_rowsGutter = 0;

		m_colsNumber = 0;
		m_colsGutter = 0;

		m_fitGuidesTo = -1;
		m_removeExistingRulerGuides = FALSE;
	}

	~CCreateGuidesDlg()
	{
	}

	int m_rowsNumber;
	double m_rowsGutter;

	int m_colsNumber;
	double m_colsGutter;

	int m_fitGuidesTo;
	BOOL m_removeExistingRulerGuides;

	enum { IDD = IDD_CREATEGUIDESDLG };

BEGIN_MSG_MAP(CCreateGuidesDlg)
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
		SetDlgItemInt(IDC_CREATEGUIDES_ROWSNUM, m_rowsNumber);
		SetDlgItemValue(m_hWnd, IDC_CREATEGUIDES_ROWSGUTTER, m_rowsGutter, UNIT_IN);

		SetDlgItemInt(IDC_CREATEGUIDES_COLSNUM, m_colsNumber);
		SetDlgItemValue(m_hWnd, IDC_CREATEGUIDES_COLSGUTTER, m_colsGutter, UNIT_IN);

		CheckRadioButton(IDC_CREATEGUIDES_FIT0, IDC_CREATEGUIDES_FIT1, IDC_CREATEGUIDES_FIT0+m_fitGuidesTo);
		CheckDlgButton(IDC_CREATEGUIDES_REMOVEEXISTING, m_removeExistingRulerGuides);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_rowsNumber = GetDlgItemInt(IDC_CREATEGUIDES_ROWSNUM);
		if (m_rowsNumber < 0 || m_rowsNumber > 999)
		{
			MessageBox("Rows Number must be between 0..999", "PageDesigner", MB_OK);
			::SetFocus(GetDlgItem(IDC_CREATEGUIDES_ROWSNUM));
			::SendMessage(GetDlgItem(IDC_CREATEGUIDES_ROWSNUM), EM_SETSEL, 0, -1);
			return 0;
		}

		m_colsNumber = GetDlgItemInt(IDC_CREATEGUIDES_COLSNUM);
		if (m_colsNumber < 0 || m_colsNumber > 999)
		{
			MessageBox("Cols Number must be between 0..999", "PageDesigner", MB_OK);
			::SetFocus(GetDlgItem(IDC_CREATEGUIDES_COLSNUM));
			::SendMessage(GetDlgItem(IDC_CREATEGUIDES_COLSNUM), EM_SETSEL, 0, -1);
			return 0;
		}

		m_rowsGutter = GetDlgItemValue(m_hWnd, IDC_CREATEGUIDES_ROWSGUTTER);
		m_colsGutter = GetDlgItemValue(m_hWnd, IDC_CREATEGUIDES_COLSGUTTER);

		if (IsDlgButtonChecked(IDC_CREATEGUIDES_FIT0))
			m_fitGuidesTo = 0;
		else if (IsDlgButtonChecked(IDC_CREATEGUIDES_FIT1))
			m_fitGuidesTo = 1;

		m_removeExistingRulerGuides = IsDlgButtonChecked(IDC_CREATEGUIDES_REMOVEEXISTING);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__CREATEGUIDESDLG_H_
