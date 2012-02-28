// SVGExportOptionsDlg.h : Declaration of the CSVGExportOptionsDlg

#ifndef __SVGEXPORTOPTIONSDLG_H_
#define __SVGEXPORTOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CSVGExportOptionsDlg
class CSVGExportOptionsDlg : 
	public CAxDialogImpl<CSVGExportOptionsDlg>
{
public:
	CSVGExportOptionsDlg()
	{
	}

	~CSVGExportOptionsDlg()
	{
	}

	enum { IDD = IDD_SVGEXPORTOPTIONSDLG };

BEGIN_MSG_MAP(CSVGExportOptionsDlg)
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

#endif //__SVGEXPORTOPTIONSDLG_H_
