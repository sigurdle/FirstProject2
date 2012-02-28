// NewDocumentDlg.h : Declaration of the CNewDocumentDlg

#ifndef __NEWDOCUMENTDLG_H_
#define __NEWDOCUMENTDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "DocumentDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CNewDocumentDlg
class CNewDocumentDlg : 
	public CDocumentDlg<CNewDocumentDlg>
{
public:
	CNewDocumentDlg()
	{
		m_marginTop = 0;
		m_marginBottom = 0;
		m_marginLeft = 0;
		m_marginRight = 0;

		m_columnNumber = 1;
		m_columnGutter = 0;
	}

	~CNewDocumentDlg()
	{
	}

	double m_marginTop;
	double m_marginBottom;
	double m_marginLeft;
	double m_marginRight;

	int m_columnNumber;
	double m_columnGutter;

	/*
	CComPtr<IUIEditUnitValue> m_numPagesCtl;
	CComPtr<IUIEditUnitValue> m_pageWidthCtl;
	CComPtr<IUIEditUnitValue> m_pageHeightCtl;
	*/

	enum { IDD = IDD_NEWDOCUMENTDLG };

	void SetMarginsText()
	{
		if (IsDlgButtonChecked(IDC_NEWDOC_FACINGPAGES))
		{
			SetDlgItemText(IDC_NEWDOC_MARGINS_LEFTTEXT, "&Inside:");
			SetDlgItemText(IDC_NEWDOC_MARGINS_RIGHTTEXT, "&Outside:");
		}
		else
		{
			SetDlgItemText(IDC_NEWDOC_MARGINS_LEFTTEXT, "&Left:");
			SetDlgItemText(IDC_NEWDOC_MARGINS_RIGHTTEXT, "&Right:");
		}
	}

BEGIN_MSG_MAP(CNewDocumentDlg)
	CHAIN_MSG_MAP(CDocumentDlg<CNewDocumentDlg>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_NEWDOC_FACINGPAGES, BN_CLICKED, OnFacingPages)
//	COMMAND_HANDLER(IDC_NEWDOC_PAGESIZE_PRESETS, CBN_SELCHANGE, OnPageSizePreset)
//	COMMAND_HANDLER(IDC_NEWDOC_PAGEWIDTH, EN_KILLFOCUS, OnChangeSize)
//	COMMAND_HANDLER(IDC_NEWDOC_PAGEHEIGHT, EN_KILLFOCUS, OnChangeSize)
//	COMMAND_HANDLER(IDC_NEWDOC_ORIENTATION_PORTRAIT, BN_CLICKED, OnOrientation)
//	COMMAND_HANDLER(IDC_NEWDOC_ORIENTATION_LANDSCAPE, BN_CLICKED, OnOrientation)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);


	LRESULT OnFacingPages(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetMarginsText();
		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CDocumentDlg<CNewDocumentDlg>::OnInitDialog();

/*
		GetDlgControl(IDC_NEWDOC_NUMBEROFPAGES, IID_IUIEditUnitValue, (void**)&m_numPagesCtl);
		GetDlgControl(IDC_NEWDOC_PAGEWIDTH, IID_IUIEditUnitValue, (void**)&m_pageWidthCtl);
		GetDlgControl(IDC_NEWDOC_PAGEHEIGHT, IID_IUIEditUnitValue, (void**)&m_pageHeightCtl);

		m_numPagesCtl->put_value(m_numPages);
		m_pageWidthCtl->put_value(m_pageWidth);
		m_pageHeightCtl->put_value(m_pageHeight);
*/


	// Margins
		SetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_TOP, m_marginTop, UNIT_IN);
		SetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_BOTTOM, m_marginBottom, UNIT_IN);
		SetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_LEFT, m_marginLeft, UNIT_IN);
		SetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_RIGHT, m_marginRight, UNIT_IN);

	// Columns
		SetDlgItemInt(IDC_NEWDOC_COLUMNS_NUMBER, m_columnNumber);
		SetDlgItemValue(m_hWnd, IDC_NEWDOC_COLUMNS_GUTTER, m_columnGutter, UNIT_IN);

		SetMarginsText();

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (!CDocumentDlg<CNewDocumentDlg>::OnOK())
			return 0;

	// Margins
		m_marginTop = GetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_TOP);
		m_marginBottom = GetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_BOTTOM);
		m_marginLeft = GetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_LEFT);
		m_marginRight = GetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_RIGHT);

	// Columns

		m_columnNumber = GetDlgItemInt(IDC_NEWDOC_COLUMNS_NUMBER);
		m_columnGutter = GetDlgItemValue(m_hWnd, IDC_NEWDOC_COLUMNS_GUTTER);

	//
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__NEWDOCUMENTDLG_H_
