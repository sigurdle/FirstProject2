// ParagraphIndentsDlg.h : Declaration of the CParagraphIndentsDlg

#ifndef __PARAGRAPHINDENTSDLG_H_
#define __PARAGRAPHINDENTSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CParagraphIndentsDlg
class CParagraphIndentsDlg : 
	public CAxPropertyPageImpl<CParagraphIndentsDlg>
{
public:
	CParagraphIndentsDlg()
	{
	}

	~CParagraphIndentsDlg()
	{
	}

	CComPtr<IPDTextPara> m_para;

	enum { IDD = IDD_PARAGRAPHINDENTSDLG };

BEGIN_MSG_MAP(CParagraphIndentsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::SendMessage(GetDlgItem(IDC_PARAGRAPHINDENTS_ALIGNMENT), CB_ADDSTRING, 0, (LPARAM)"Left");
		::SendMessage(GetDlgItem(IDC_PARAGRAPHINDENTS_ALIGNMENT), CB_ADDSTRING, 0, (LPARAM)"Center");
		::SendMessage(GetDlgItem(IDC_PARAGRAPHINDENTS_ALIGNMENT), CB_ADDSTRING, 0, (LPARAM)"Right");
		::SendMessage(GetDlgItem(IDC_PARAGRAPHINDENTS_ALIGNMENT), CB_ADDSTRING, 0, (LPARAM)"Left justify");
		::SendMessage(GetDlgItem(IDC_PARAGRAPHINDENTS_ALIGNMENT), CB_ADDSTRING, 0, (LPARAM)"Center justify");
		::SendMessage(GetDlgItem(IDC_PARAGRAPHINDENTS_ALIGNMENT), CB_ADDSTRING, 0, (LPARAM)"Right justify");
		::SendMessage(GetDlgItem(IDC_PARAGRAPHINDENTS_ALIGNMENT), CB_ADDSTRING, 0, (LPARAM)"Full justify");

	// Alignment
		long alignment;
		m_para->GetAlignment(&alignment);
		if (alignment != tomUndefined)
			::SendMessage(GetDlgItem(IDC_PARAGRAPHINDENTS_ALIGNMENT), CB_SETCURSEL, alignment, 0);

		return 1;  // Let the system set the focus
	}
};

#endif //__PARAGRAPHINDENTSDLG_H_
