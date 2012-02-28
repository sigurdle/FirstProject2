// NewSiteSingleWorkgroupDlg.h : Declaration of the CNewSiteSingleWorkgroupDlg

#ifndef __NEWSITESINGLEWORKGROUPDLG_H_
#define __NEWSITESINGLEWORKGROUPDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "NewSiteData.h"

/////////////////////////////////////////////////////////////////////////////
// CNewSiteSingleWorkgroupDlg
class CNewSiteSingleWorkgroupDlg : 
	public CPropertyPageImpl<CNewSiteSingleWorkgroupDlg>
{
public:
	CNewSiteSingleWorkgroupDlg()
	{
		m_nWorkgroup = -1;
	}

	~CNewSiteSingleWorkgroupDlg()
	{
	}

	CNewSiteData* m_data;
	int m_previousIDD;

	int m_nWorkgroup;

	enum { IDD = IDD_NEWSITESINGLEWORKGROUPDLG };

BEGIN_MSG_MAP(CNewSiteSingleWorkgroupDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CPropertyPageImpl<CNewSiteSingleWorkgroupDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 1;  // Let the system set the focus
	}

	BOOL OnSetActive()
	{
		SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

		m_previousIDD = m_data->m_previousIDD;

		CheckRadioButton(IDC_NEWSITE_SINGLE, IDC_NEWSITE_WORKGROUP, IDC_NEWSITE_SINGLE + m_nWorkgroup);

		return TRUE;
	}

	int OnWizardBack()
	{
		// 0  = goto next page
		// -1 = prevent page change
		// >0 = jump to page by dlg ID
		return m_previousIDD;
	}

	int OnWizardNext()
	{
		// 0  = goto next page
		// -1 = prevent page change
		// >0 = jump to page by dlg ID

		m_data->m_previousIDD = IDD;

		if (IsDlgButtonChecked(IDC_NEWSITE_SINGLE))
			m_nWorkgroup = 0;
		else if (IsDlgButtonChecked(IDC_NEWSITE_WORKGROUP))
			m_nWorkgroup = 1;

		if (m_nWorkgroup == 0)
			return IDD_NEWSITELOCALSITEOPTIONSDLG;
		else if (m_nWorkgroup == 1)
			return IDD_NEWSITEWORKGROUPOPTIONSDLG;
		return -1;
	}
};

#endif //__NEWSITESINGLEWORKGROUPDLG_H_
