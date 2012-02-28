// LinksOptionsDlg.h : Declaration of the CLinksOptionsDlg

#ifndef __LINKSOPTIONSDLG_H_
#define __LINKSOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CLinksOptionsDlg
class CLinksOptionsDlg : 
	public CAxDialogImpl<CLinksOptionsDlg>
{
public:
	CLinksOptionsDlg()
	{
		m_thumbSize = 0;
	}

	~CLinksOptionsDlg()
	{
	}

	int m_thumbSize;

	enum { IDD = IDD_LINKSOPTIONSDLG };

BEGIN_MSG_MAP(CLinksOptionsDlg)
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
		CheckRadioButton(IDC_LINKSOPTIONS_THUMB_NONE, IDC_LINKSOPTIONS_THUMB_LARGE, IDC_LINKSOPTIONS_THUMB_NONE+m_thumbSize);
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (IsDlgButtonChecked(IDC_LINKSOPTIONS_THUMB_NONE)) m_thumbSize = 0;
		else if (IsDlgButtonChecked(IDC_LINKSOPTIONS_THUMB_SMALL)) m_thumbSize = 1;
		else if (IsDlgButtonChecked(IDC_LINKSOPTIONS_THUMB_MEDIUM)) m_thumbSize = 2;
		else if (IsDlgButtonChecked(IDC_LINKSOPTIONS_THUMB_LARGE)) m_thumbSize = 3;

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__LINKSOPTIONSDLG_H_
