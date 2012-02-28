// TintSwatchOptionsDlg.h : Declaration of the CTintSwatchOptionsDlg

#ifndef __TINTSWATCHOPTIONSDLG_H_
#define __TINTSWATCHOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CTintSwatchOptionsDlg
class CTintSwatchOptionsDlg : 
	public CAxDialogImpl<CTintSwatchOptionsDlg>
{
public:
	CTintSwatchOptionsDlg()
	{
	}

	~CTintSwatchOptionsDlg()
	{
	}

	enum { IDD = IDD_TINTSWATCHOPTIONSDLG };

BEGIN_MSG_MAP(CTintSwatchOptionsDlg)
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

#endif //__TINTSWATCHOPTIONSDLG_H_
