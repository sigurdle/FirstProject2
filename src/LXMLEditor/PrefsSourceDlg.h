#ifndef __PREFSSOURCEDLG_H_
#define __PREFSSOURCEDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CPrefsSourceDlg : 
	public CAxPropertyPageImpl<CPrefsSourceDlg>
{
public:
	CPrefsSourceDlg()
	{
		m_colorFormat = -1;
	}

	~CPrefsSourceDlg()
	{
	}

	int m_colorFormat;

	enum { IDD = IDD_PREFSSOURCEDLG };

	/*
BEGIN_MSG_MAP(CPrefsSourceDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CPrefsSourceDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
*/
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog()
	{
		CheckRadioButton(IDC_SOURCE_COLOR_HEX3, IDC_SOURCE_RGBPERCENT, IDC_SOURCE_COLOR_HEX3+m_colorFormat);
		return 1;  // Let the system set the focus
	}

	bool OnApply()
	{
		if (IsDlgButtonChecked(IDC_SOURCE_COLOR_HEX3))
			m_colorFormat = 0;
		else if (IsDlgButtonChecked(IDC_SOURCE_COLOR_HEX3+1))
			m_colorFormat = 1;
		else if (IsDlgButtonChecked(IDC_SOURCE_COLOR_HEX3+2))
			m_colorFormat = 2;
		else if (IsDlgButtonChecked(IDC_SOURCE_COLOR_HEX3+3))
			m_colorFormat = 3;

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

#endif //__PREFSSOURCEDLG_H_
