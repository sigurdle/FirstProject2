// DocumentSetupDlg.h : Declaration of the CDocumentSetupDlg

#ifndef __DOCUMENTSETUPDLG_H_
#define __DOCUMENTSETUPDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "DocumentDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDocumentSetupDlg
class CDocumentSetupDlg : 
	public CDocumentDlg<CDocumentSetupDlg>
{
public:
	CDocumentSetupDlg()
	{
	}

	~CDocumentSetupDlg()
	{
	}

	enum { IDD = IDD_DOCUMENTSETUPDLG };

BEGIN_MSG_MAP(CDocumentSetupDlg)
	CHAIN_MSG_MAP(CDocumentDlg<CDocumentSetupDlg>)
	DEFAULT_REFLECTION_HANDLER()
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
		CDocumentDlg<CDocumentSetupDlg>::OnInitDialog();

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (!CDocumentDlg<CDocumentSetupDlg>::OnOK())
			return 0;

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__DOCUMENTSETUPDLG_H_
