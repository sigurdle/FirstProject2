// NewSiteLocalSiteOptionsDlg.h : Declaration of the CNewSiteLocalSiteOptionsDlg

#ifndef __NEWSITELOCALSITEOPTIONSDLG_H_
#define __NEWSITELOCALSITEOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "NewSiteData.h"

/////////////////////////////////////////////////////////////////////////////
// CNewSiteLocalSiteOptionsDlg
class CNewSiteLocalSiteOptionsDlg : 
	public CPropertyPageImpl<CNewSiteLocalSiteOptionsDlg>
{
public:
	CNewSiteLocalSiteOptionsDlg()
	{
		m_nLocalSite = -1;
	}

	~CNewSiteLocalSiteOptionsDlg()
	{
	}

	int m_nLocalSite;

	CNewSiteData* m_data;
	int m_previousIDD;

	enum { IDD = IDD_NEWSITELOCALSITEOPTIONSDLG };

BEGIN_MSG_MAP(CNewSiteLocalSiteOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CPropertyPageImpl<CNewSiteLocalSiteOptionsDlg>)
//	DEFAULT_REFLECTION_HANDLER()
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

		CheckRadioButton(IDC_LOCALSITE_BLANKSITE, IDC_LOCALSITE_FROMSERVER, IDC_LOCALSITE_BLANKSITE + m_nLocalSite);

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

		if (IsDlgButtonChecked(IDC_LOCALSITE_BLANKSITE))
			m_nLocalSite = 0;
		else if (IsDlgButtonChecked(IDC_LOCALSITE_FROMSERVER))
			m_nLocalSite = 1;

		if (m_nLocalSite == 0)
			return IDD_NEWSITELOCALNAMEDLG;
		else if (m_nLocalSite == 1)
			return IDD_NEWSITEFTPDLG;
		return -1;
	}
};

#endif //__NEWSITELOCALSITEOPTIONSDLG_H_
