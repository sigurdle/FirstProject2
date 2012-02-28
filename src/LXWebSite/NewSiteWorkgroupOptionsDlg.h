// NewSiteWorkgroupOptionsDlg.h : Declaration of the CNewSiteWorkgroupOptionsDlg

#ifndef __NEWSITEWORKGROUPOPTIONSDLG_H_
#define __NEWSITEWORKGROUPOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "NewSiteData.h"

/////////////////////////////////////////////////////////////////////////////
// CNewSiteWorkgroupOptionsDlg
class CNewSiteWorkgroupOptionsDlg : 
	public CPropertyPageImpl<CNewSiteWorkgroupOptionsDlg>
{
public:
	CNewSiteWorkgroupOptionsDlg()
	{
	}

	~CNewSiteWorkgroupOptionsDlg()
	{
	}

	CNewSiteData* m_data;
	int m_previousIDD;

	enum { IDD = IDD_NEWSITEWORKGROUPOPTIONSDLG };

BEGIN_MSG_MAP(CNewSiteWorkgroupOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CPropertyPageImpl<CNewSiteWorkgroupOptionsDlg>)
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

		return IDD_NEWSITEWORKGROUPLOGONDLG;
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

#endif //__NEWSITEWORKGROUPOPTIONSDLG_H_
