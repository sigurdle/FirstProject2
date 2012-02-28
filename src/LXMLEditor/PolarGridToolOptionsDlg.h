// PolarGridToolOptionsDlg.h : Declaration of the CPolarGridToolOptionsDlg

#ifndef __POLARGRIDTOOLOPTIONSDLG_H_
#define __POLARGRIDTOOLOPTIONSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CPolarGridToolOptionsDlg
class CPolarGridToolOptionsDlg : 
	public CAxDialogImpl<CPolarGridToolOptionsDlg>
{
public:
	CPolarGridToolOptionsDlg()
	{
	}

	~CPolarGridToolOptionsDlg()
	{
	}

	int m_concentricDivs;
	int m_radialDivs;
	double m_concentricSkew;
	double m_radialSkew;

	enum { IDD = IDD_POLARGRIDTOOLOPTIONSDLG };

	/*
BEGIN_MSG_MAP(CPolarGridToolOptionsDlg)
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

		SetDlgItemInt(IDC_POLARGRID_CONCENTRICDIVS, m_concentricDivs);
		SetDlgItemInt(IDC_POLARGRID_RADIALDIVS, m_radialDivs);

		sprintf(buf, "%g", m_concentricSkew*100);
		SetDlgItemText(IDC_POLARGRID_CONCENTRICSKEW, buf);

		sprintf(buf, "%g", m_radialSkew*100);
		SetDlgItemText(IDC_POLARGRID_RADIALSKEW, buf);

		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		TCHAR buf[64];

		if (!GetDlgItemIntX(this, IDC_POLARGRID_CONCENTRICDIVS, 0, 1000, &m_concentricDivs))
			return 0;

		if (!GetDlgItemIntX(this, IDC_POLARGRID_RADIALDIVS, 0, 1000, &m_radialDivs))
			return 0;

		GetDlgItemText(IDC_POLARGRID_CONCENTRICSKEW, buf, sizeof(buf));
		m_concentricSkew = atof(buf)/100;

		GetDlgItemText(IDC_POLARGRID_RADIALSKEW, buf, sizeof(buf));
		m_radialSkew = atof(buf)/100;

		EndDialog(wID);
		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

}	// LXmlEdit
}

#endif //__POLARGRIDTOOLOPTIONSDLG_H_
