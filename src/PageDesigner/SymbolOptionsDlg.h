// SymbolOptionsDlg.h : Declaration of the CSymbolOptionsDlg

#ifndef __SYMBOLOPTIONSDLG_H_
#define __SYMBOLOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CSymbolOptionsDlg
class CSymbolOptionsDlg : 
	public CAxDialogImpl<CSymbolOptionsDlg>
{
public:
	CSymbolOptionsDlg()
	{
	}

	~CSymbolOptionsDlg()
	{
	}

	CArray<IPDSymbol*,IPDSymbol*> m_targetObjects;

	enum { IDD = IDD_SYMBOLOPTIONSDLG };

BEGIN_MSG_MAP(CSymbolOptionsDlg)
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
		CenterWindow();

	// Symbol name
		if (m_targetObjects.GetSize() == 1)
		{
			BSTR bname;
			m_targetObjects[0]->get_name(&bname);
			SetDlgItemText(IDC_SYMBOL_NAME, _bstr_t(bname, false));
		}
		else
		{
			::EnableWindow(GetDlgItem(IDC_SYMBOL_NAME), FALSE);
		}

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
	// Symbol Name
		if (m_targetObjects.GetSize() == 1)
		{
			TCHAR buf[256];
			GetDlgItemText(IDC_SYMBOL_NAME, buf, sizeof(buf));
			m_targetObjects[0]->put_name(_bstr_t(buf));
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

#endif //__SYMBOLOPTIONSDLG_H_
