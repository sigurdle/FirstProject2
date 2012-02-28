// RasterizeDlg.h : Declaration of the CRasterizeDlg

#ifndef __RASTERIZEDLG_H_
#define __RASTERIZEDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CRasterizeDlg
class CRasterizeDlg : 
	public CAxDialogImpl<CRasterizeDlg>
{
public:
	CRasterizeDlg()
	{
	}

	~CRasterizeDlg()
	{
	}

	long m_ppi;
	long m_documentppi;
	Gdiplus::Color	m_bgColor;

	enum { IDD = IDD_RASTERIZEDLG };

BEGIN_MSG_MAP(CRasterizeDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(IDC_RASTERIZE_RES72, OnRes)
	COMMAND_ID_HANDLER(IDC_RASTERIZE_RES150, OnRes)
	COMMAND_ID_HANDLER(IDC_RASTERIZE_RES300, OnRes)
	COMMAND_ID_HANDLER(IDC_RASTERIZE_RES_OTHER, OnRes)
	COMMAND_ID_HANDLER(IDC_RASTERIZE_RES_DODUMENT, OnRes)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnRes(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		::EnableWindow(GetDlgItem(IDC_RASTERIZE_RES_OTHERVALUE), (wID == IDC_RASTERIZE_RES_OTHER));
		if (wID == IDC_RASTERIZE_RES_OTHER)
		{
			::SetFocus(GetDlgItem(IDC_RASTERIZE_RES_OTHERVALUE));
			::SendMessage(GetDlgItem(IDC_RASTERIZE_RES_OTHERVALUE), EM_SETSEL, 0, -1);
		}
		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::EnableWindow(GetDlgItem(IDC_RASTERIZE_RES_OTHERVALUE), FALSE);

		if (m_ppi == 72)
			CheckDlgButton(IDC_RASTERIZE_RES72, TRUE);
		else if (m_ppi == 150)
			CheckDlgButton(IDC_RASTERIZE_RES150, TRUE);
		else if (m_ppi == 300)
			CheckDlgButton(IDC_RASTERIZE_RES300, TRUE);
		else
		{
			CheckDlgButton(IDC_RASTERIZE_RES_OTHER, TRUE);
			::EnableWindow(GetDlgItem(IDC_RASTERIZE_RES_OTHERVALUE), TRUE);
		}

		SetDlgItemInt(IDC_RASTERIZE_RES_OTHERVALUE, m_ppi);

		if (m_bgColor.GetAlpha() == 0)
			CheckDlgButton(IDC_RASTERIZE_BG1, TRUE);
		else
			CheckDlgButton(IDC_RASTERIZE_BG0, TRUE);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (IsDlgButtonChecked(IDC_RASTERIZE_RES72))
		{
			m_ppi = 72;
		}
		else if (IsDlgButtonChecked(IDC_RASTERIZE_RES150))
		{
			m_ppi = 150;
		}
		else if (IsDlgButtonChecked(IDC_RASTERIZE_RES300))
		{
			m_ppi = 300;
		}
		else if (IsDlgButtonChecked(IDC_RASTERIZE_RES_OTHER))
		{
			BOOL bTrans;
			m_ppi = GetDlgItemInt(IDC_RASTERIZE_RES_OTHERVALUE, &bTrans, FALSE);
			if (!bTrans)
			{
				MessageBox("Invalid numeric value", "PageDesigner", MB_OK);
				SendMessage(GetDlgItem(IDC_RASTERIZE_RES_OTHERVALUE), EM_SETSEL, 0, -1);
				return 0;
			}
		}
		else if (IsDlgButtonChecked(IDC_RASTERIZE_RES_DODUMENT))
		{
			m_ppi = m_documentppi;
		}
		else
			ATLASSERT(0);

		if (IsDlgButtonChecked(IDC_RASTERIZE_BG0))
		{
			m_bgColor = Gdiplus::Color(255, 255, 255, 255);
		}
		else
		{
			m_bgColor = Gdiplus::Color(0, 0, 0, 0);
		}

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__RASTERIZEDLG_H_
