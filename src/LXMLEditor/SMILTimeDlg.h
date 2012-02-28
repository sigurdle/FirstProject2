// SMILTimeDlg.h : Declaration of the CSMILTimeDlg

#ifndef __SMILTIMEDLG_H_
#define __SMILTIMEDLG_H_

#include "resource.h"       // main symbols

double ParseClockValue(const WCHAR * s);

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CSMILTimeDlg
class CSMILTimeDlg : 
	public CAxDialogImpl<CSMILTimeDlg>
{
public:
	CSMILTimeDlg()
	{
		m_type = -1;
	}

	~CSMILTimeDlg()
	{
	}

	int m_type;
	double m_offset;

	enum { IDD = IDD_SMILTIMEDLG };

	long OnInitDialog()
	{
#if 0
		if (m_offset != 999999999)
		{
			CString str;
			str.Format("%g", m_offset);
			SetDlgItemText(IDC_TIME_OFFSET, str);
		}

	//	CheckRadioButton(IDC_TIME_TYPE_INDEFINITE, IDC_TIME_TYPE_EVENTBASED, IDC_TIME_TYPE_INDEFINITE+m_type);
		if (m_type == 0)
			CheckDlgButton(IDC_TIME_TYPE_INDEFINITE, BST_CHECKED);
		else if (m_type == 1)
			CheckDlgButton(IDC_TIME_TYPE_OFFSET, BST_CHECKED);
		else if (m_type == 2)
			CheckDlgButton(IDC_TIME_TYPE_SYNCBASED, BST_CHECKED);
		else if (m_type == 3)
			CheckDlgButton(IDC_TIME_TYPE_EVENTBASED, BST_CHECKED);

		SendDlgItemMessage(IDC_TIME_BASE, CB_ADDSTRING, 0, (LPARAM)_T("begin"));
		SendDlgItemMessage(IDC_TIME_BASE, CB_ADDSTRING, 0, (LPARAM)_T("end"));
#endif
		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
#if 0
		USES_CONVERSION;

		if (IsDlgButtonChecked(IDC_TIME_TYPE_INDEFINITE))
			m_type = 0;
		else if (IsDlgButtonChecked(IDC_TIME_TYPE_OFFSET))
			m_type = 1;
		else if (IsDlgButtonChecked(IDC_TIME_TYPE_SYNCBASED))
			m_type = 2;
		else if (IsDlgButtonChecked(IDC_TIME_TYPE_EVENTBASED))
			m_type = 3;

		CString str;
		GetDlgItemText(IDC_TIME_OFFSET, str.GetBuffer(256), 256);
		str.ReleaseBuffer();
		m_offset = ParseClockValue(A2W(str));
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

#endif //__SMILTIMEDLG_H_
