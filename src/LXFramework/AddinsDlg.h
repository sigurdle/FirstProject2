// AddinsDlg.h : Declaration of the CAddinsDlg

#ifndef __ADDINSDLG_H_
#define __ADDINSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class CLXFrameworkFrame;

/////////////////////////////////////////////////////////////////////////////
// CAddinsDlg
class CAddinsDlg : 
	public CAxDialogImpl<CAddinsDlg>
{
public:
	CAddinsDlg()
	{
	}

	~CAddinsDlg()
	{
	}

	CListViewCtrl m_list;

	CLXFrameworkFrame* m_pFrame;

	void FillList();

	enum { IDD = IDD_ADDINSDLG };

BEGIN_MSG_MAP(CAddinsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_ADDIN_CUSTOMIZE, OnAddinCustomize)
	COMMAND_ID_HANDLER(IDC_ADDINS_ADD, OnAddinAdd)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnAddinCustomize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAddinAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

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

#endif //__ADDINSDLG_H_
