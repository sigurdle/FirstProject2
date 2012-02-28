// MarginsAndColumnsDlg.h : Declaration of the CMarginsAndColumnsDlg

#ifndef __MARGINSANDCOLUMNSDLG_H_
#define __MARGINSANDCOLUMNSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CMarginsAndColumnsDlg
class CMarginsAndColumnsDlg : 
	public CAxDialogImpl<CMarginsAndColumnsDlg>
{
public:
	CMarginsAndColumnsDlg()
	{
	}

	~CMarginsAndColumnsDlg()
	{
	}

	CArray<IPDPage*,IPDPage*> m_targetObjects;

	enum { IDD = IDD_MARGINSANDCOLUMNSDLG };

BEGIN_MSG_MAP(CMarginsAndColumnsDlg)
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
		CenterWindow();

		/*
		if (IsDlgButtonChecked(IDC_NEWDOC_FACINGPAGES))
		*/
		{
			SetDlgItemText(IDC_NEWDOC_MARGINS_LEFTTEXT, "&Inside:");
			SetDlgItemText(IDC_NEWDOC_MARGINS_RIGHTTEXT, "&Outside:");
		}
		/*
		else
		{
			SetDlgItemText(IDC_NEWDOC_MARGINS_LEFTTEXT, "&Left:");
			SetDlgItemText(IDC_NEWDOC_MARGINS_RIGHTTEXT, "&Right:");
		}
		*/

		int i;

	// Top
		{
			double marginTop;

			for (i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double marginTop2;
				m_targetObjects[i]->get_marginTop(&marginTop2);

				if (i == 0)
				{
					marginTop = marginTop2;
				}
				else if (marginTop != marginTop2)
				{
					marginTop = -1;
					break;
				}
			}

			if (marginTop >= 0)
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_TOP, marginTop, UNIT_IN);
		}

	// Bottom
		{
			double marginBottom;

			for (i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double marginBottom2;
				m_targetObjects[i]->get_marginBottom(&marginBottom2);

				if (i == 0)
				{
					marginBottom = marginBottom2;
				}
				else if (marginBottom != marginBottom2)
				{
					marginBottom = -1;
					break;
				}
			}

			if (marginBottom >= 0)
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_BOTTOM, marginBottom, UNIT_IN);
		}

	// Inside
		{
			double marginInside;

			for (i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double marginInside2;
				m_targetObjects[i]->get_marginInside(&marginInside2);

				if (i == 0)
				{
					marginInside = marginInside2;
				}
				else if (marginInside != marginInside2)
				{
					marginInside = -1;
					break;
				}
			}

			if (marginInside >= 0)
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_LEFT, marginInside, UNIT_IN);
		}

	// Outside
		{
			double marginOutside;

			for (i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double marginOutside2;
				m_targetObjects[i]->get_marginOutside(&marginOutside2);

				if (i == 0)
				{
					marginOutside = marginOutside2;
				}
				else if (marginOutside != marginOutside2)
				{
					marginOutside = -1;
					break;
				}
			}

			if (marginOutside >= 0)
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_RIGHT, marginOutside, UNIT_IN);
		}

	// Outside
		{
			long columnNumber;

			for (i = 0; i < m_targetObjects.GetSize(); i++)
			{
				long columnNumber2;
				m_targetObjects[i]->get_columnNumber(&columnNumber2);

				if (i == 0)
				{
					columnNumber = columnNumber2;
				}
				else if (columnNumber != columnNumber2)
				{
					columnNumber = 0;
					break;
				}
			}

			if (columnNumber > 0)
				SetDlgItemInt(IDC_NEWDOC_COLUMNS_NUMBER, columnNumber);
		}

	// Gutter
		{
			double columnGutter;

			for (i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double columnGutter2;
				m_targetObjects[i]->get_columnGutter(&columnGutter2);

				if (i == 0)
				{
					columnGutter = columnGutter2;
				}
				else if (columnGutter != columnGutter2)
				{
					columnGutter = -1;
					break;
				}
			}

			if (columnGutter >= 0)
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_COLUMNS_GUTTER, columnGutter, UNIT_IN);
		}

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
	// Margins
		BOOL bTop;
		double marginTop = GetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_TOP, &bTop);

		BOOL bBottom;
		double marginBottom = GetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_BOTTOM, &bBottom);

		BOOL bInside;
		double marginInside = GetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_LEFT, &bInside);

		BOOL bOutside;
		double marginOutside = GetDlgItemValue(m_hWnd, IDC_NEWDOC_MARGINS_RIGHT, &bOutside);

	// Columns
		BOOL bColumns;
		long columnNumber = GetDlgItemInt(IDC_NEWDOC_COLUMNS_NUMBER, &bColumns);

		BOOL bGutter;
		double columnGutter = GetDlgItemValue(m_hWnd, IDC_NEWDOC_COLUMNS_GUTTER, &bGutter);

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
		// Margins
			double marginTop2;
			m_targetObjects[i]->get_marginTop(&marginTop2);

			double marginBottom2;
			m_targetObjects[i]->get_marginBottom(&marginBottom2);

			double marginInside2;
			m_targetObjects[i]->get_marginInside(&marginInside2);

			double marginOutside2;
			m_targetObjects[i]->get_marginOutside(&marginOutside2);

		// Columns
			long columnNumber2;
			m_targetObjects[i]->get_columnNumber(&columnNumber2);

			double columnGutter2;
			m_targetObjects[i]->get_columnGutter(&columnGutter2);

		// Margins
			double marginTop3 = (bTop)? marginTop: marginTop2;
			double marginBottom3 = (bBottom)? marginBottom: marginBottom2;
			double marginInside3 = (bInside)? marginInside: marginInside2;
			double marginOutside3 = (bOutside)? marginOutside: marginOutside2;

		// Columns
			long columnNumber3 = (bColumns)? columnNumber: columnNumber2;
			double columnGutter3 = (bGutter)? columnGutter: columnGutter2;

		//
			m_targetObjects[i]->setMarginsAndColumns(marginTop3, marginBottom3, marginInside3, marginOutside3, columnNumber3, columnGutter3);
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

#endif //__MARGINSANDCOLUMNSDLG_H_
