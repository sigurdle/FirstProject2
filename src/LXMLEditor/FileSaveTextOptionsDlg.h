// FileSaveTextOptionsDlg.h : Declaration of the CFileSaveTextOptionsDlg

#ifndef __FILESAVETEXTOPTIONSDLG_H_
#define __FILESAVETEXTOPTIONSDLG_H_

#include "resource.h"       // main symbols

#if 0

/////////////////////////////////////////////////////////////////////////////
// CFileSaveTextOptionsDlg
class CFileSaveTextOptionsDlg : 
//	public CAxDialogImpl<CFileSaveTextOptionsDlg>
	public CFileDialogImpl<CFileDialog>
{
public:
	CFileSaveTextOptionsDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		HWND hWndParent = NULL)
		: CFileDialogImpl<CFileDialog>(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags | OFN_ENABLETEMPLATE, lpszFilter, hWndParent)
	{
		m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD);
	}

	~CFileSaveTextOptionsDlg()
	{
	}

	enum { IDD = IDD_FILESAVETEXTOPTIONSDLG };

BEGIN_MSG_MAP(CFileSaveTextOptionsDlg)
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
	// Align encoding text
		{
			HWND hWnd = GetFileDialogWindow().GetDlgItem(stc2);

			RECT rect;
			::GetWindowRect(hWnd, &rect);
			GetFileDialogWindow().ScreenToClient(&rect);

			RECT rect2;
			::GetWindowRect(GetDlgItem(IDC_FILESAVE_STENCODING), &rect2);
			ScreenToClient(&rect2);

			::SetWindowPos(GetDlgItem(IDC_FILESAVE_STENCODING), NULL, rect.left, rect2.top, rect.right-rect.left, rect.bottom-rect.top, SWP_NOZORDER | SWP_NOACTIVATE);
		}

	// Align encoding combobox
		{
			HWND hWnd = GetFileDialogWindow().GetDlgItem(cmb1);

			RECT rect;
			::GetWindowRect(hWnd, &rect);
			GetFileDialogWindow().ScreenToClient(&rect);

			RECT rect2;
			::GetWindowRect(GetDlgItem(IDC_FILESAVE_CBENCODING), &rect2);
			ScreenToClient(&rect2);

			::SetWindowPos(GetDlgItem(IDC_FILESAVE_CBENCODING), NULL, rect.left, rect2.top, rect.right-rect.left, rect.bottom-rect.top, SWP_NOZORDER | SWP_NOACTIVATE);
		}

		SendDlgItemMessage(IDC_FILESAVE_CBENCODING, CB_ADDSTRING, 0, (LPARAM)_T("ANSI"));
		SendDlgItemMessage(IDC_FILESAVE_CBENCODING, CB_ADDSTRING, 0, (LPARAM)_T("Unicode"));
		SendDlgItemMessage(IDC_FILESAVE_CBENCODING, CB_ADDSTRING, 0, (LPARAM)_T("Unicode big endian"));
		SendDlgItemMessage(IDC_FILESAVE_CBENCODING, CB_ADDSTRING, 0, (LPARAM)_T("UTF-8"));

		return 1;  // Let the system set the focus
	}

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
};

#endif

#endif //__FILESAVETEXTOPTIONSDLG_H_
