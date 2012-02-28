// NewSiteFinishDlg.h : Declaration of the CNewSiteFinishDlg

#ifndef __NEWSITEFINISHDLG_H_
#define __NEWSITEFINISHDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CNewSiteFinishDlg
class CNewSiteFinishDlg : 
	public CPropertyPageImpl<CNewSiteFinishDlg>
{
public:
	CNewSiteFinishDlg()
	{
	}

	~CNewSiteFinishDlg()
	{
	}

	enum { IDD = IDD_NEWSITEFINISHDLG };

BEGIN_MSG_MAP(CNewSiteFinishDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CPropertyPageImpl<CNewSiteFinishDlg>)
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
//		m_previousIDD = m_data->m_previousIDD;

		SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

		return TRUE;
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

#endif //__NEWSITEFINISHDLG_H_
