// MediaSearchDlg.h : Declaration of the CMediaSearchDlg

#ifndef __MEDIASEARCHDLG_H_
#define __MEDIASEARCHDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class CLXDocumentViewerApp;

/////////////////////////////////////////////////////////////////////////////
// CMediaSearchDlg
class CMediaSearchDlg : 
	public CAxDialogImpl<CMediaSearchDlg>
{
public:
	CMediaSearchDlg()
	{
	}

	~CMediaSearchDlg()
	{
	}

	CLXDocumentViewerApp* m_app;

	enum { IDD = IDD_MEDIASEARCHDLG };

BEGIN_MSG_MAP(CMediaSearchDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_SEARCH, OnSearch)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 1;  // Let the system set the focus
	}

	LRESULT OnSearch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

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

#endif //__MEDIASEARCHDLG_H_
