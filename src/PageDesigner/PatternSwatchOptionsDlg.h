// PatternSwatchOptionsDlg.h : Declaration of the CPatternSwatchOptionsDlg

#ifndef __PATTERNSWATCHOPTIONSDLG_H_
#define __PATTERNSWATCHOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CPatternSwatchOptionsDlg
class CPatternSwatchOptionsDlg : 
	public CAxDialogImpl<CPatternSwatchOptionsDlg>
{
public:
	CPatternSwatchOptionsDlg()
	{
	}

	~CPatternSwatchOptionsDlg()
	{
	}

	CArray<IPDSwatchPattern*,IPDSwatchPattern*> m_targetObjects;

	enum { IDD = IDD_PATTERNSWATCHOPTIONSDLG };

BEGIN_MSG_MAP(CPatternSwatchOptionsDlg)
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
	// Swatch name
		if (m_targetObjects.GetSize() == 1)
		{
			BSTR bname;
			m_targetObjects[0]->get_name(&bname);
			SetDlgItemText(IDC_SWATCH_NAME, _bstr_t(bname, false));
		}
		else
		{
			::EnableWindow(GetDlgItem(IDC_SWATCH_NAME), FALSE);
		}

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
	// Swatch Name
		if (m_targetObjects.GetSize() == 1)
		{
			TCHAR buf[256];
			GetDlgItemText(IDC_SWATCH_NAME, buf, sizeof(buf));
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

#endif //__PATTERNSWATCHOPTIONSDLG_H_
