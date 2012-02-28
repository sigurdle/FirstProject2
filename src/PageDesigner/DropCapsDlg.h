// DropCapsDlg.h : Declaration of the CDropCapsDlg

#ifndef __DROPCAPSDLG_H_
#define __DROPCAPSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CDropCapsDlg
class CDropCapsDlg : 
	public CAxPropertyPageImpl<CDropCapsDlg>
{
public:
	CDropCapsDlg()
	{
	}

	~CDropCapsDlg()
	{
	}

	CComPtr<IPDTextPara> m_para;
//	CArray<IDOMElement*,IDOMElement*> m_targetObjects;

	enum { IDD = IDD_DROPCAPSDLG };

BEGIN_MSG_MAP(CDropCapsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_DROPCAPS_LINES, EN_CHANGE, OnEditChanged)
	COMMAND_HANDLER(IDC_DROPCAPS_CHARACTERS, EN_CHANGE, OnEditChanged)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CDropCapsDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	BOOL OnApply()
	{
		BOOL bTrans;

		int lines = GetDlgItemInt(IDC_DROPCAPS_LINES, &bTrans);
		if (bTrans)
		{
			m_para->put_dropCapLines(lines);
		}

		int characters = GetDlgItemInt(IDC_DROPCAPS_CHARACTERS, &bTrans);
		if (bTrans)
		{
			m_para->put_dropCapChars(characters);
		}

		return TRUE;
	}

	LRESULT OnEditChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetModified(TRUE);
		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	// Lines
		long lines;
		m_para->get_dropCapLines(&lines);
		if (lines != tomUndefined) SetDlgItemInt(IDC_DROPCAPS_LINES, lines);

	// Characters
		long characters;
		m_para->get_dropCapChars(&characters);
		if (characters != tomUndefined) SetDlgItemInt(IDC_DROPCAPS_CHARACTERS, characters);

		return 1;  // Let the system set the focus
	}
};

#endif //__DROPCAPSDLG_H_
