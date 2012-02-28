// TextFrameOptionsDlg.h : Declaration of the CTextFrameOptionsDlg

#ifndef __TEXTFRAMEOPTIONSDLG_H_
#define __TEXTFRAMEOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CTextFrameOptionsDlg
class CTextFrameOptionsDlg : 
	public CAxDialogImpl<CTextFrameOptionsDlg>
{
public:
	CTextFrameOptionsDlg()
	{
	}

	~CTextFrameOptionsDlg()
	{
	}

	CArray<IPDTextFrameOptions*,IPDTextFrameOptions*> m_targetObjects;

	double m_textFrameWidth;

	enum { IDD = IDD_TEXTFRAMEOPTIONSDLG };

BEGIN_MSG_MAP(CTextFrameOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_TEXTFRAME_COLUMNS_NUMBER, EN_KILLFOCUS, OnChangedColumnsNumber)
	COMMAND_HANDLER(IDC_TEXTFRAME_COLUMNS_GUTTER, EN_KILLFOCUS, OnChangedColumnsGutter)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	void SetColumnWidthValue()
	{
		BOOL bTrans;

		int columns = GetDlgItemInt(IDC_TEXTFRAME_COLUMNS_NUMBER, &bTrans, FALSE);
		double gutter = GetDlgItemValue(m_hWnd, IDC_TEXTFRAME_COLUMNS_GUTTER, &bTrans);

		UINT bcolumnsFixedWidth = IsDlgButtonChecked(IDC_TEXTFRAME_COLUMNS_FIXEDWIDTH);
		if (bcolumnsFixedWidth == BST_UNCHECKED)
		{
			double frameWidth;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				long columnsNumber2;
				double columnsWidth2;
				double columnsGutter2;

				m_targetObjects[i]->get_columnsNumber(&columnsNumber2);
				m_targetObjects[i]->get_columnsWidth(&columnsWidth2);
				m_targetObjects[i]->get_columnsGutter(&columnsGutter2);

				double frameWidth2 = (columnsNumber2 * columnsWidth2) + (columnsNumber2-1)*columnsGutter2;

				if (i == 0)
				{
					frameWidth = frameWidth2;
				}
				else if (frameWidth != frameWidth2)
				{
					frameWidth = tomUndefined;
					break;
				}
			}

			if (frameWidth != tomUndefined)
			{
				double columnsWidth = (frameWidth-(columns-1)*gutter)/columns;

				SetDlgItemValue(m_hWnd, IDC_TEXTFRAME_COLUMNS_WIDTH, columnsWidth, UNIT_PT);
			}
			else
			{
				SetDlgItemText(IDC_TEXTFRAME_COLUMNS_WIDTH, "");
			}
		}
	}

	LRESULT OnChangedColumnsNumber(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetColumnWidthValue();
		return 0;
	}

	LRESULT OnChangedColumnsGutter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetColumnWidthValue();
		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	// Columns Number
		{
			long columnsNumber;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				long columnsNumber2;
				m_targetObjects[i]->get_columnsNumber(&columnsNumber2);

				if (i == 0)
				{
					columnsNumber = columnsNumber2;
				}
				else if (columnsNumber != columnsNumber2)
				{
					columnsNumber = -1;
					break;
				}
			}

			if (columnsNumber >= 0)
			{
				SetDlgItemInt(IDC_TEXTFRAME_COLUMNS_NUMBER, columnsNumber);
			}
		}

	// Columns Gutter
		{
			double columnsGutter;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double columnsGutter2;
				m_targetObjects[i]->get_columnsGutter(&columnsGutter2);

				if (i == 0)
				{
					columnsGutter = columnsGutter2;
				}
				else if (columnsGutter != columnsGutter2)
				{
					columnsGutter = -1;
					break;
				}
			}

			if (columnsGutter >= 0)
			{
				SetDlgItemValue(m_hWnd, IDC_TEXTFRAME_COLUMNS_GUTTER, columnsGutter, UNIT_PT);
			}
		}

	// Columns Width
		{
			double columnsWidth;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double columnsWidth2;
				m_targetObjects[i]->get_columnsWidth(&columnsWidth2);

				if (i == 0)
				{
					columnsWidth = columnsWidth2;
				}
				else if (columnsWidth != columnsWidth2)
				{
					columnsWidth = tomUndefined;
					break;
				}
			}

			if (columnsWidth != tomUndefined)
			{
				SetDlgItemValue(m_hWnd, IDC_TEXTFRAME_COLUMNS_WIDTH, columnsWidth, UNIT_PT);
			}
		}

	// Columns Fixed Width
		{
			VARIANT_BOOL columnsFixedWidth;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				VARIANT_BOOL columnsFixedWidth2;
				m_targetObjects[i]->get_columnsFixedWidth(&columnsFixedWidth2);

				if (i == 0)
				{
					columnsFixedWidth = columnsFixedWidth2;
				}
				else if (columnsFixedWidth != columnsFixedWidth2)
				{
					columnsFixedWidth = 2;
					break;
				}
			}

			if (columnsFixedWidth == 2)
				::SetWindowLong(GetDlgItem(IDC_TEXTFRAME_COLUMNS_FIXEDWIDTH), GWL_STYLE, ::GetWindowLong(GetDlgItem(IDC_TEXTFRAME_COLUMNS_FIXEDWIDTH), GWL_STYLE) & ~BST_MASK | BS_AUTO3STATE);

			CheckDlgButton(IDC_TEXTFRAME_COLUMNS_FIXEDWIDTH, (columnsFixedWidth == VARIANT_TRUE)? BST_CHECKED: (columnsFixedWidth == VARIANT_FALSE)? BST_UNCHECKED: BST_INDETERMINATE);
		}

	// For Inset boxes to be enabled, either all or none of the target objects be rectangular or not
		{
			int isRectangular = -1;	// VARIANT_TRUE

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CComQIPtr<IPDObject> object = m_targetObjects[i];
				if (object)
				{
					CComPtr<IPDObjectFrame> parentFrame;
					object->get_parent((IPDObjectUnknown**)&parentFrame);

					CComPtr<IPDPath> path;
					parentFrame->get_path(&path);

					VARIANT_BOOL isRectangular2;
					path->IsRectangular(&isRectangular2);

					if (i == 0)
					{
						isRectangular = isRectangular2;
					}
					else if (isRectangular != isRectangular2)
					{
						isRectangular = 2;
						break;
					}
				}
			}

			::EnableWindow(GetDlgItem(IDC_TEXTFRAME_INSET_TOP), isRectangular != 2);
			::EnableWindow(GetDlgItem(IDC_TEXTFRAME_INSET_BOTTOM), isRectangular == -1);
			::EnableWindow(GetDlgItem(IDC_TEXTFRAME_INSET_LEFT), isRectangular == -1);
			::EnableWindow(GetDlgItem(IDC_TEXTFRAME_INSET_RIGHT), isRectangular == -1);
		}

	// Inset values

		{
			double insetTop;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double insetTop2;
				m_targetObjects[i]->get_insetTop(&insetTop2);

				if (i == 0)
				{
					insetTop = insetTop2;
				}
				else if (insetTop != insetTop2)
				{
					insetTop = tomUndefined;
					break;
				}
			}

			if (insetTop != tomUndefined)
			{
				SetDlgItemValue(m_hWnd, IDC_TEXTFRAME_INSET_TOP, insetTop, UNIT_PT);
			}
		}

		{
			double insetBottom;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double insetBottom2;
				m_targetObjects[i]->get_insetBottom(&insetBottom2);

				if (i == 0)
				{
					insetBottom = insetBottom2;
				}
				else if (insetBottom != insetBottom2)
				{
					insetBottom = tomUndefined;
					break;
				}
			}

			if (insetBottom != tomUndefined)
			{
				SetDlgItemValue(m_hWnd, IDC_TEXTFRAME_INSET_BOTTOM, insetBottom, UNIT_PT);
			}
		}

		{
			double insetLeft;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double insetLeft2;
				m_targetObjects[i]->get_insetLeft(&insetLeft2);

				if (i == 0)
				{
					insetLeft = insetLeft2;
				}
				else if (insetLeft != insetLeft2)
				{
					insetLeft = tomUndefined;
					break;
				}
			}

			if (insetLeft != tomUndefined)
			{
				SetDlgItemValue(m_hWnd, IDC_TEXTFRAME_INSET_LEFT, insetLeft, UNIT_PT);
			}
		}

		{
			double insetRight;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				double insetRight2;
				m_targetObjects[i]->get_insetRight(&insetRight2);

				if (i == 0)
				{
					insetRight = insetRight2;
				}
				else if (insetRight != insetRight2)
				{
					insetRight = tomUndefined;
					break;
				}
			}

			if (insetRight != tomUndefined)
			{
				SetDlgItemValue(m_hWnd, IDC_TEXTFRAME_INSET_RIGHT, insetRight, UNIT_PT);
			}
		}

	// Ignore Text Wrap
		{
			VARIANT_BOOL ignoreTextWrap;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				VARIANT_BOOL ignoreTextWrap2;
				m_targetObjects[i]->get_ignoreTextWrap(&ignoreTextWrap2);

				if (i == 0)
				{
					ignoreTextWrap = ignoreTextWrap2;
				}
				else if (ignoreTextWrap != ignoreTextWrap2)
				{
					ignoreTextWrap = 2;
					break;
				}
			}

			if (ignoreTextWrap == 2)
				::SetWindowLong(GetDlgItem(IDC_TEXTFRAME_IGNOREWRAP), GWL_STYLE, ::GetWindowLong(GetDlgItem(IDC_TEXTFRAME_IGNOREWRAP), GWL_STYLE) & ~BST_MASK | BS_AUTO3STATE);

			CheckDlgButton(IDC_TEXTFRAME_IGNOREWRAP, (ignoreTextWrap == VARIANT_TRUE)? BST_CHECKED: (ignoreTextWrap == VARIANT_FALSE)? BST_UNCHECKED: BST_INDETERMINATE);
		}

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		BOOL bTrans;

	// Columns Number
		long columnsNumber = tomUndefined;
		if (::GetWindowTextLength(GetDlgItem(IDC_TEXTFRAME_COLUMNS_NUMBER)) > 0)
		{
			columnsNumber = GetDlgItemInt(IDC_TEXTFRAME_COLUMNS_NUMBER, &bTrans);
			if (!bTrans || columnsNumber < 1 || columnsNumber > 40)
			{
				MessageBox("Columns Number must be between 1..40", "PageDesigner", MB_OK);
				::SetFocus(GetDlgItem(IDC_TEXTFRAME_COLUMNS_NUMBER));
				::SendMessage(GetDlgItem(IDC_TEXTFRAME_COLUMNS_NUMBER), EM_SETSEL, 0, -1);
				return 0;
			}
		}

	// Columns Gutter
		double columnsGutter = tomUndefined;
		if (::GetWindowTextLength(GetDlgItem(IDC_TEXTFRAME_COLUMNS_GUTTER)) > 0)
		{
			columnsGutter = GetDlgItemValue(m_hWnd, IDC_TEXTFRAME_COLUMNS_GUTTER, &bTrans);
			if (!bTrans)
			{
				MessageBox("Invalid columns gutter", "PageDesigner", MB_OK);
				::SetFocus(GetDlgItem(IDC_TEXTFRAME_COLUMNS_GUTTER));
				::SendMessage(GetDlgItem(IDC_TEXTFRAME_COLUMNS_GUTTER), EM_SETSEL, 0, -1);
				return 0;
			}
		}

	// ColumnsWidth
		double columnsWidth = tomUndefined;
		if (::GetWindowTextLength(GetDlgItem(IDC_TEXTFRAME_COLUMNS_WIDTH)) > 0)
		{
			columnsWidth = GetDlgItemValue(m_hWnd, IDC_TEXTFRAME_COLUMNS_WIDTH, &bTrans);
			if (!bTrans || columnsWidth <= 0)
			{
				MessageBox("Invalid Columns Width", "PageDesigner", MB_OK);
				::SetFocus(GetDlgItem(IDC_TEXTFRAME_COLUMNS_WIDTH));
				::SendMessage(GetDlgItem(IDC_TEXTFRAME_COLUMNS_WIDTH), EM_SETSEL, 0, -1);
				return 0;
			}
		}

	// ColumnsFixedWidth
		VARIANT_BOOL columnsFixedWidth = 2;
		UINT bcolumnsFixedWidth = IsDlgButtonChecked(IDC_TEXTFRAME_COLUMNS_FIXEDWIDTH);
		if (bcolumnsFixedWidth == BST_CHECKED || bcolumnsFixedWidth == BST_UNCHECKED)
		{
			columnsFixedWidth = bcolumnsFixedWidth == BST_CHECKED? VARIANT_TRUE: VARIANT_FALSE;
		}

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			m_targetObjects[i]->setColumns(columnsNumber, columnsGutter, columnsWidth, columnsFixedWidth);
		}

	// Ignore Text Wrap
		UINT ignoreWrap = IsDlgButtonChecked(IDC_TEXTFRAME_IGNOREWRAP);
		if (ignoreWrap == BST_CHECKED || ignoreWrap == BST_UNCHECKED)
		{
			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				m_targetObjects[i]->put_ignoreTextWrap((ignoreWrap == BST_CHECKED)? VARIANT_TRUE: VARIANT_FALSE);
			}
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

#endif //__TEXTFRAMEOPTIONSDLG_H_
