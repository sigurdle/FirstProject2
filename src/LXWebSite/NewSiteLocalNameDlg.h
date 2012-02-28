// NewSiteLocalNameDlg.h : Declaration of the CNewSiteLocalNameDlg

#ifndef __NEWSITELOCALNAMEDLG_H_
#define __NEWSITELOCALNAMEDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "..\SBDestination.h"

#include "NewSiteData.h"

/////////////////////////////////////////////////////////////////////////////
// CNewSiteLocalNameDlg
class CNewSiteLocalNameDlg : 
	public CPropertyPageImpl<CNewSiteLocalNameDlg>
{
public:
	CNewSiteLocalNameDlg()
	{
	}

	~CNewSiteLocalNameDlg()
	{
	}

	CUString m_localSitePath;
	CUString m_siteName;

	CNewSiteData* m_data;
	int m_previousIDD;

	enum { IDD = IDD_NEWSITELOCALNAMEDLG };

BEGIN_MSG_MAP(CNewSiteLocalNameDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_LOCALNAME_BROWSE, OnBrowse)
	COMMAND_HANDLER(IDC_LOCALNAME_NAME, EN_CHANGE, OnLocalNameChange)
	CHAIN_MSG_MAP(CPropertyPageImpl<CNewSiteLocalNameDlg>)
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

	void SetWizardButtons()
	{
		DWORD nFlags = PSWIZB_BACK;
		if (::GetWindowTextLength(GetDlgItem(IDC_LOCALNAME_NAME)) > 0 &&
			m_localSitePath.GetLength() > 0) nFlags |= PSWIZB_NEXT;

		CPropertyPageImpl<CNewSiteLocalNameDlg>::SetWizardButtons(nFlags);
	}

	LRESULT OnLocalNameChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetWizardButtons();
		return 0;
	}

	LRESULT OnBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CSBDestination dest;
		dest.SetInitialSelection(m_localSitePath);

		if (dest.SelectFolder())
		{
			TCHAR buf[512];
			dest.GetSelectedFolder(buf);

			m_localSitePath = buf;

			SetDlgItemText(IDC_LOCALNAME_LOCATION, m_localSitePath);

			SetWizardButtons();
		}
		return 0;
	}

	BOOL OnSetActive()
	{
		m_previousIDD = m_data->m_previousIDD;

		SetDlgItemText(IDC_LOCALNAME_NAME, m_siteName);
		SetDlgItemText(IDC_LOCALNAME_LOCATION, m_localSitePath);

		SetWizardButtons();

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

		TCHAR buf[512];
		GetDlgItemText(IDC_LOCALNAME_NAME, buf, sizeof(buf));
		m_siteName = buf;

		m_data->m_previousIDD = IDD;

		return IDD_NEWSITEFINISHDLG;
	}
};

#endif //__NEWSITELOCALNAMEDLG_H_
