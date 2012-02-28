#ifndef __RECTANGULARGRIDTOOLOPTIONSDLG_H_
#define __RECTANGULARGRIDTOOLOPTIONSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CRectangularGridToolOptionsDlg : 
public CAxDialogImpl<CRectangularGridToolOptionsDlg>
{
public:
	CRectangularGridToolOptionsDlg()
	{
	}

	~CRectangularGridToolOptionsDlg()
	{
	}

	int m_horzDivs;
	int m_vertDivs;
	double m_horzSkew;
	double m_vertSkew;
	bool m_outsideAsRect;

	enum { IDD = IDD_RECTANGULARGRIDTOOLOPTIONSDLG };

	/*
BEGIN_MSG_MAP(CRectangularGridToolOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog(bool& bHandled)
	{
		TCHAR buf[64];

		SetDlgItemInt(IDC_RECTGRID_HORZDIVS, m_horzDivs);
		SetDlgItemInt(IDC_RECTGRID_VERTDIVS, m_vertDivs);

		sprintf(buf, "%g", m_horzSkew*100);
		SetDlgItemText(IDC_RECTGRID_HORZSKEW, buf);

		sprintf(buf, "%g", m_vertSkew*100);
		SetDlgItemText(IDC_RECTGRID_VERTSKEW, buf);

		CheckDlgButton(IDC_RECTGRID_OUTSIDEASRECT, m_outsideAsRect);

		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		TCHAR buf[64];

		if (!GetDlgItemIntX(this, IDC_RECTGRID_HORZDIVS, 0, 1000, &m_horzDivs))
			return 0;

		if (!GetDlgItemIntX(this, IDC_RECTGRID_VERTDIVS, 0, 1000, &m_vertDivs))
			return 0;

		GetDlgItemText(IDC_RECTGRID_HORZSKEW, buf, sizeof(buf));
		m_horzSkew = atof(buf)/100;

		GetDlgItemText(IDC_RECTGRID_VERTSKEW, buf, sizeof(buf));
		m_vertSkew = atof(buf)/100;

		m_outsideAsRect = IsDlgButtonChecked(IDC_RECTGRID_OUTSIDEASRECT);

		EndDialog(wID);
		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
	//	EndDialog(wID);
		return 0;
	}
};

}	// LXmlEdit
}

#endif //__RECTANGULARGRIDTOOLOPTIONSDLG_H_
