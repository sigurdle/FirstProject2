// NewSiteBeginDlg.h : Declaration of the CNewSiteBeginDlg

#ifndef __NEWSITEBEGINDLG_H_
#define __NEWSITEBEGINDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CNewSiteBeginDlg
class CNewSiteBeginDlg : 
	public CPropertyPageImpl<CNewSiteBeginDlg>
{
public:
	CNewSiteBeginDlg()
	{
		m_hTitleFont = NULL;
	}

	~CNewSiteBeginDlg()
	{
	}

	enum { IDD = IDD_NEWSITEBEGINDLG };

BEGIN_MSG_MAP(CNewSiteBeginDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	CHAIN_MSG_MAP(CPropertyPageImpl<CNewSiteBeginDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	HFONT m_hTitleFont;

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		NONCLIENTMETRICS ncm = {0};
		ncm.cbSize = sizeof(ncm);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);
	
	//Create the intro/end title font
		LOGFONT TitleLogFont = ncm.lfMessageFont;
		TitleLogFont.lfWeight = FW_BOLD;
		lstrcpy(TitleLogFont.lfFaceName, TEXT("Verdana Bold"));
		 
		HDC hdc = ::GetDC(NULL); //gets the screen DC
		INT FontSize = 12;
		TitleLogFont.lfHeight = 0 - GetDeviceCaps(hdc, LOGPIXELSY) * FontSize / 72;
		m_hTitleFont = CreateFontIndirect(&TitleLogFont);
		::ReleaseDC(NULL, hdc);

		::SendMessage(GetDlgItem(IDC_TITLE), WM_SETFONT, (WPARAM)m_hTitleFont, TRUE);

		return 1;  // Let the system set the focus
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DeleteObject(m_hTitleFont);
		return 0;
	}

	BOOL OnSetActive()
	{
		SetWizardButtons(PSWIZB_NEXT);

		return TRUE;
	}
};

#endif //__NEWSITEBEGINDLG_H_
