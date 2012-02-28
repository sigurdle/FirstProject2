// RectangleOptionsDlg.h : Declaration of the CRectangleOptionsDlg

#ifndef __RECTANGLEOPTIONSDLG_H_
#define __RECTANGLEOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CRectangleOptionsDlg
class CRectangleOptionsDlg : 
	public CAxDialogImpl<CRectangleOptionsDlg>
{
public:
	CRectangleOptionsDlg()
	{
		m_width = 0;
		m_height = 0;
	}

	~CRectangleOptionsDlg()
	{
	}

	double m_width;
	double m_height;

	enum { IDD = IDD_RECTANGLEOPTIONSDLG };

BEGIN_MSG_MAP(CRectangleOptionsDlg)
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
		TCHAR buf[256];

		sprintf(buf, "%g", m_width);
		SetDlgItemText(IDC_OBJECT_WIDTH, buf);

		sprintf(buf, "%g", m_height);
		SetDlgItemText(IDC_OBJECT_HEIGHT, buf);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		TCHAR buf[256];

		GetDlgItemText(IDC_OBJECT_WIDTH, buf, sizeof(buf));
		m_width = atof(buf);

		GetDlgItemText(IDC_OBJECT_HEIGHT, buf, sizeof(buf));
		m_height = atof(buf);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__RECTANGLEOPTIONSDLG_H_
