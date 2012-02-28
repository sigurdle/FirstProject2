// FEGaussianBlurDlg.h : Declaration of the CFEGaussianBlurDlg

#ifndef __FEGAUSSIANBLURDLG_H_
#define __FEGAUSSIANBLURDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CFEGaussianBlurDlg
class CFEGaussianBlurDlg : 
	public CAxDialogImpl<CFEGaussianBlurDlg>
{
public:
	CFEGaussianBlurDlg()
	{
		m_blurx = 0;
		m_blury = 0;
	}

	~CFEGaussianBlurDlg()
	{
	}

	double m_blurx;
	double m_blury;

	CComPtr<IPluginFilterClass> m_pluginFilterClass;

	enum { IDD = IDD_FEGAUSSIANBLURDLG };

BEGIN_MSG_MAP(CFEGaussianBlurDlg)
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
		SetDlgItemValue(m_hWnd, IDC_FEGAUSSBLUR_DEVX, m_blurx, UNIT_PT);
		SetDlgItemValue(m_hWnd, IDC_FEGAUSSBLUR_DEVY, m_blury, UNIT_PT);
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		BOOL bTrans;

		m_blurx = GetDlgItemValue(m_hWnd, IDC_FEGAUSSBLUR_DEVX, &bTrans);
		if (!bTrans)
		{
			MessageBox("Dev X is invalid", "Gaussian Blur", MB_OK);
			return 0;
		}

		m_blury = GetDlgItemValue(m_hWnd, IDC_FEGAUSSBLUR_DEVY, &bTrans);
		if (!bTrans)
		{
			MessageBox("Dev Y is invalid", "Gaussian Blur", MB_OK);
			return 0;
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

#endif //__FEGAUSSIANBLURDLG_H_
