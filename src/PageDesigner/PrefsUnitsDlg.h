// PrefsUnitsDlg.h : Declaration of the CPrefsUnitsDlg

#ifndef __PREFSUNITSDLG_H_
#define __PREFSUNITSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CPrefsUnitsDlg
class CPrefsUnitsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CAxPropertyPageImpl<CPrefsUnitsDlg>
//	public IUnknown,
//	public IDispEventImpl<1, CPrefsUnitsDlg, &DIID__IUIComboBoxEvents, &LIBID_UILib, 1, 0>
{
public:
	CPrefsUnitsDlg()
	{
	//	m_origin = 0;
	}

	~CPrefsUnitsDlg()
	{
	}

	enum { IDD = IDD_PREFSUNITSDLG };

BEGIN_MSG_MAP(CPrefsUnitsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CPrefsUnitsDlg>)
	DEFAULT_REFLECTION_HANDLER()
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	BOOL OnApply()
	{
		MessageBox("", "", MB_OK);
		return TRUE;
	}
/*
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
//		IDispEventImpl<1, CPrefsUnitsDlg, &DIID__IUIComboBoxEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_originCtl);

		return 0;
	}
*/

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
//		GetDlgControl(IDC_RULERUNITS_ORIGIN, IID_IUIComboBox, (void**)&m_originCtl);
//		IDispEventImpl<1, CPrefsUnitsDlg, &DIID__IUIComboBoxEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_originCtl);

	//	long index;

		::SendMessage(GetDlgItem(IDC_RULERUNITS_ORIGIN), CB_ADDSTRING, 0, (LPARAM)"Spread");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_ORIGIN), CB_ADDSTRING, 0, (LPARAM)"Page");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_ORIGIN), CB_ADDSTRING, 0, (LPARAM)"Spine");

		::SendMessage(GetDlgItem(IDC_RULERUNITS_HORIZONTAL), CB_ADDSTRING, 0, (LPARAM)"Points");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_HORIZONTAL), CB_ADDSTRING, 0, (LPARAM)"Picas");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_HORIZONTAL), CB_ADDSTRING, 0, (LPARAM)"Inches");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_HORIZONTAL), CB_ADDSTRING, 0, (LPARAM)"Inches Decimal");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_HORIZONTAL), CB_ADDSTRING, 0, (LPARAM)"Millimeters");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_HORIZONTAL), CB_ADDSTRING, 0, (LPARAM)"Centimeters");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_HORIZONTAL), CB_ADDSTRING, 0, (LPARAM)"Ciceros");

		::SendMessage(GetDlgItem(IDC_RULERUNITS_VERTICAL), CB_ADDSTRING, 0, (LPARAM)"Points");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_VERTICAL), CB_ADDSTRING, 0, (LPARAM)"Picas");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_VERTICAL), CB_ADDSTRING, 0, (LPARAM)"Inches");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_VERTICAL), CB_ADDSTRING, 0, (LPARAM)"Inches Decimal");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_VERTICAL), CB_ADDSTRING, 0, (LPARAM)"Millimeters");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_VERTICAL), CB_ADDSTRING, 0, (LPARAM)"Centimeters");
		::SendMessage(GetDlgItem(IDC_RULERUNITS_VERTICAL), CB_ADDSTRING, 0, (LPARAM)"Ciceros");

	//	m_originCtl->put_cursel(m_origin);

		return 1;  // Let the system set the focus
	}
};

#endif //__PREFSUNITSDLG_H_
