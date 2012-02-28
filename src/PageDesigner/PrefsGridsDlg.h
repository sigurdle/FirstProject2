// PrefsGridsDlg.h : Declaration of the CPrefsGridsDlg

#ifndef __PREFSGRIDSDLG_H_
#define __PREFSGRIDSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CPrefsGridsDlg
class CPrefsGridsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CAxPropertyPageImpl<CPrefsGridsDlg>
//	public IUnknown
{
public:
	CPrefsGridsDlg()
	{
		m_targetObject = NULL;
	}

	~CPrefsGridsDlg()
	{
	}

	IPDDocumentSettings* m_targetObject;

	enum { IDD = IDD_PREFSGRIDSDLG };

	/*
BEGIN_COM_MAP(CPrefsGridsDlg)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()
*/

BEGIN_MSG_MAP(CPrefsGridsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_DOCUMENTGRID_HOREVERY, EN_CHANGE, OnEditChanged)
	COMMAND_HANDLER(IDC_DOCUMENTGRID_VEREVERY, EN_CHANGE, OnEditChanged)
	COMMAND_HANDLER(IDC_DOCUMENTGRID_HORSUBDIVS, EN_CHANGE, OnEditChanged)
	COMMAND_HANDLER(IDC_DOCUMENTGRID_VERSUBDIVS, EN_CHANGE, OnEditChanged)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CPrefsGridsDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnEditChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetModified(TRUE);
		return 0;
	}

	BOOL OnApply()
	{
		int n;

		double verticalGridlineEvery = GetDlgItemValue(m_hWnd, IDC_DOCUMENTGRID_HOREVERY);
		m_targetObject->put_verticalGridlineEvery(verticalGridlineEvery);

		double horizontalGridlineEvery = GetDlgItemValue(m_hWnd, IDC_DOCUMENTGRID_VEREVERY);
		m_targetObject->put_horizontalGridlineEvery(horizontalGridlineEvery);

		n = GetDlgItemInt(IDC_DOCUMENTGRID_HORSUBDIVS);
		if (n <= 0)
		{
			return FALSE;
		}
		m_targetObject->put_horizontalGridSubdivisions(n);

		n = GetDlgItemInt(IDC_DOCUMENTGRID_VERSUBDIVS);
		if (n <= 0)
		{
			return FALSE;
		}
		m_targetObject->put_verticalGridSubdivisions(n);

		return TRUE;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
/*	VARIANT_BOOL m_gridsInBack;
	long ;
	long m_horizontalGridSubdivisions;
	double m_verticalGridlineEvery;
	double m_horizontalGridlineEvery;
*/
		double verticalGridlineEvery;
		m_targetObject->get_verticalGridlineEvery(&verticalGridlineEvery);
		SetDlgItemValue(m_hWnd, IDC_DOCUMENTGRID_HOREVERY, verticalGridlineEvery, UNIT_PT);

		double horizontalGridlineEvery;
		m_targetObject->get_horizontalGridlineEvery(&horizontalGridlineEvery);
		SetDlgItemValue(m_hWnd, IDC_DOCUMENTGRID_VEREVERY, horizontalGridlineEvery, UNIT_PT);

		long verticalGridSubdivisions;
		m_targetObject->get_verticalGridSubdivisions(&verticalGridSubdivisions);
		SetDlgItemInt(IDC_DOCUMENTGRID_HORSUBDIVS, verticalGridSubdivisions);

		long horizontalGridSubdivisions;
		m_targetObject->get_horizontalGridSubdivisions(&horizontalGridSubdivisions);
		SetDlgItemInt(IDC_DOCUMENTGRID_VERSUBDIVS, horizontalGridSubdivisions);

		return 1;  // Let the system set the focus
	}

/*
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
	*/
};

#endif //__PREFSGRIDSDLG_H_
