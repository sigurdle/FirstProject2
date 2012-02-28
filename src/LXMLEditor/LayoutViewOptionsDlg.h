// LayoutViewOptionsDlg.h : Declaration of the CLayoutViewOptionsDlg

#ifndef __LAYOUTVIEWOPTIONSDLG_H_
#define __LAYOUTVIEWOPTIONSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CLayoutViewOptionsDlg : 
	public CAxDialogImpl<CLayoutViewOptionsDlg>
{
public:
	CLayoutViewOptionsDlg()
	{
	}

	~CLayoutViewOptionsDlg()
	{
	}

	Web::CSSUnitType m_horRulerUnits;
	Web::CSSUnitType m_verRulerUnits;

	enum { IDD = IDD_LAYOUTVIEWOPTIONSDLG };

	long OnInitDialog(bool& bHandled)
	{
		ASSERT(0);
#if 0
		{
			HWND hWnd = GetDlgItem(IDC_RULER_HORIZONTAL_UNITS);

			AddCbString(hWnd, _T("Pixels"), Web::CSS_PX);
			AddCbString(hWnd, _T("Points"), Web::CSS_PT);
			AddCbString(hWnd, _T("mm"), Web::CSS_MM);
			AddCbString(hWnd, _T("cm"), Web::CSS_CM);
			AddCbString(hWnd, _T("Inches"), Web::CSS_IN);
			AddCbString(hWnd, _T("Pica"), Web::CSS_PC);
			AddCbString(hWnd, _T("%"), Web::CSS_PERCENTAGE);

			SetCbCurSel(GetDlgItem(IDC_RULER_HORIZONTAL_UNITS), m_horRulerUnits);
		}

		{
			HWND hWnd = GetDlgItem(IDC_RULER_VERTICAL_UNITS);

			AddCbString(hWnd, _T("Pixels"), Web::CSS_PX);
			AddCbString(hWnd, _T("Points"), Web::CSS_PT);
			AddCbString(hWnd, _T("mm"), Web::CSS_MM);
			AddCbString(hWnd, _T("cm"), Web::CSS_CM);
			AddCbString(hWnd, _T("Inches"), Web::CSS_IN);
			AddCbString(hWnd, _T("Pica"), Web::CSS_PC);
			AddCbString(hWnd, _T("%"), Web::CSS_PERCENTAGE);

			SetCbCurSel(GetDlgItem(IDC_RULER_VERTICAL_UNITS), m_verRulerUnits);
		}
#endif
		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
#if 0
		{
			int index = SendDlgItemMessage(IDC_RULER_HORIZONTAL_UNITS, CB_GETCURSEL);
			m_horRulerUnits = (Web::CSSUnitType)SendDlgItemMessage(IDC_RULER_HORIZONTAL_UNITS, CB_GETITEMDATA, index);
		}

		{
			int index = SendDlgItemMessage(IDC_RULER_VERTICAL_UNITS, CB_GETCURSEL);
			m_verRulerUnits = (Web::CSSUnitType)SendDlgItemMessage(IDC_RULER_VERTICAL_UNITS, CB_GETITEMDATA, index);
		}
#endif
		EndDialog(wID);
		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

}
}

#endif //__LAYOUTVIEWOPTIONSDLG_H_
