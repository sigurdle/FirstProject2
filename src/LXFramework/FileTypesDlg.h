// FileTypesDlg.h : Declaration of the CFileTypesDlg

#ifndef __FILETYPESDLG_H_
#define __FILETYPESDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "FileType.h"

//class CMyFileType

/////////////////////////////////////////////////////////////////////////////
// CFileTypesDlg
class CFileTypesDlg : 
	public CAxPropertyPageImpl<CFileTypesDlg>
{
public:
	CFileTypesDlg()
	{
	}

	~CFileTypesDlg()
	{
	}

	CFileTypes* m_fileTypes;

	enum { IDD = IDD_FILETYPESDLG };

BEGIN_MSG_MAP(CFileTypesDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
//	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
	COMMAND_HANDLER(IDC_FILETYPES, LBN_SELCHANGE, OnFileTypeChange)
	COMMAND_HANDLER(IDC_FILETYPE_REGISTERED, BN_CLICKED, OnFileTypeRegister)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CFileTypesDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnFileTypeChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileTypeRegister(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

//	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	BOOL OnApply()
	{
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

#endif //__FILETYPESDLG_H_
