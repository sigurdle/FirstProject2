#ifndef __SMILTIMEGRAPHOPTIONSDLG_H_
#define __SMILTIMEGRAPHOPTIONSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CSMILTimeGraphOptionsDlg : 
	public CAxDialogImpl<CSMILTimeGraphOptionsDlg>
{
public:
	CSMILTimeGraphOptionsDlg()
	{
		m_iconSize = -1;
		m_trackFormat = -1;
	}

	~CSMILTimeGraphOptionsDlg()
	{
	}
	
	int m_iconSize;
	int m_trackFormat;

	enum { IDD = IDD_SMILTIMEGRAPHOPTIONSDLG };

	/*
BEGIN_MSG_MAP(CSMILTimeGraphOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog()
	{
		ASSERT(0);
#if 0
		::SendMessage(GetDlgItem(IDC_TIMEGRAPH_SIZE0), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TIMEGRAPH_SIZE0)));
		::SendMessage(GetDlgItem(IDC_TIMEGRAPH_SIZE1), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TIMEGRAPH_SIZE1)));
		::SendMessage(GetDlgItem(IDC_TIMEGRAPH_SIZE2), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TIMEGRAPH_SIZE2)));

		::SendMessage(GetDlgItem(IDC_TIMEGRAPH_FORMAT0), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TIMEGRAPH_FORMAT0)));
		::SendMessage(GetDlgItem(IDC_TIMEGRAPH_FORMAT1), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TIMEGRAPH_FORMAT1)));
		::SendMessage(GetDlgItem(IDC_TIMEGRAPH_FORMAT2), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TIMEGRAPH_FORMAT2)));
		::SendMessage(GetDlgItem(IDC_TIMEGRAPH_FORMAT3), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TIMEGRAPH_FORMAT3)));
#endif
		CheckRadioButton(IDC_TIMEGRAPH_SIZE0, IDC_TIMEGRAPH_SIZE2, IDC_TIMEGRAPH_SIZE0+m_iconSize);
		CheckRadioButton(IDC_TIMEGRAPH_FORMAT0, IDC_TIMEGRAPH_FORMAT3, IDC_TIMEGRAPH_FORMAT0+m_trackFormat);

		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		if (IsDlgButtonChecked(IDC_TIMEGRAPH_SIZE0))
			m_iconSize = 0;
		else if (IsDlgButtonChecked(IDC_TIMEGRAPH_SIZE1))
			m_iconSize = 1;
		else if (IsDlgButtonChecked(IDC_TIMEGRAPH_SIZE2))
			m_iconSize = 2;

		if (IsDlgButtonChecked(IDC_TIMEGRAPH_FORMAT0))
			m_trackFormat = 0;
		else if (IsDlgButtonChecked(IDC_TIMEGRAPH_FORMAT1))
			m_trackFormat = 1;
		else if (IsDlgButtonChecked(IDC_TIMEGRAPH_FORMAT2))
			m_trackFormat = 2;
		else if (IsDlgButtonChecked(IDC_TIMEGRAPH_FORMAT3))
			m_trackFormat = 3;

		EndDialog(wID);
		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

}
}

#endif //__SMILTIMEGRAPHOPTIONSDLG_H_
