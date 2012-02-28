// BrushDimensionsDlg.h : Declaration of the CBrushDimensionsDlg

#ifndef __BRUSHDIMENSIONSDLG_H_
#define __BRUSHDIMENSIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CBrushDimensionsDlg
class CBrushDimensionsDlg : 
	public CAxPropertyPageImpl<CBrushDimensionsDlg>
{
public:
	CBrushDimensionsDlg()
	{
	}

	~CBrushDimensionsDlg()
	{
	}

	CComPtr<IPDBrushSettings> m_brushSettings;

	enum { IDD = IDD_BRUSHDIMENSIONSDLG };

BEGIN_MSG_MAP(CBrushDimensionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
	COMMAND_HANDLER(IDC_BRUSH_ANGLE, CBN_SELCHANGE, OnAngleChanged)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CBrushDimensionsDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnAngleChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		static long prevcursel = -1;

		long index = ::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_GETCURSEL, 0, 0);
		if (index >= 0)
		{
			TCHAR buf[256];
			::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_GETLBTEXT, index, (LPARAM)buf);
			if (buf[0] == 0)
			{
				if (index > prevcursel)
					index++;
				else
					index--;

				::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_SETCURSEL, index, 0);
			}

			prevcursel = index;
		}
		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"5 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"10 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"20 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"30 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"40 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"50 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"60 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"70 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"80 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"90 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"100 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"150 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"200 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"250 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"300 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_WIDTH), CB_ADDSTRING, 0, (LPARAM)"400 pt");

		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"5 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"10 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"20 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"30 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"40 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"50 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"60 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"70 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"80 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"90 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"100 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"150 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"200 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"250 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"300 pt");
		::SendMessage(GetDlgItem(IDC_BRUSH_HEIGHT), CB_ADDSTRING, 0, (LPARAM)"400 pt");

		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"-180");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"-150");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"-120");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"-90");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"-60");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"-45");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"-30");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"0");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"30");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"45");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"60");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"90");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"120");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"150");
		::SendMessage(GetDlgItem(IDC_BRUSH_ANGLE), CB_ADDSTRING, 0, (LPARAM)"180");

		::SendMessage(GetDlgItem(IDC_BRUSH_TIP), STM_SETICON, (WPARAM)LoadIcon(NULL, IDI_INFORMATION), 0);

		double brushWidth;
		m_brushSettings->get_brushWidth(&brushWidth);
		SetDlgItemValue(m_hWnd, IDC_BRUSH_WIDTH, brushWidth, UNIT_PT);

		double brushHeight;
		m_brushSettings->get_brushHeight(&brushHeight);
		SetDlgItemValue(m_hWnd, IDC_BRUSH_HEIGHT, brushHeight, UNIT_PT);

		double brushAngle;
		m_brushSettings->get_brushAngle(&brushAngle);
		SetDlgItemAngle(m_hWnd, IDC_BRUSH_ANGLE, brushAngle);

		VARIANT_BOOL showBrush;
		m_brushSettings->get_showBrushSize(&showBrush);
		CheckDlgButton(IDC_BRUSH_SHOW, showBrush? BST_CHECKED: BST_UNCHECKED);

		return 1;  // Let the system set the focus
	}

	BOOL OnApply()
	{
		BOOL bTrans;

		double brushWidth = GetDlgItemValue(m_hWnd, IDC_BRUSH_WIDTH, &bTrans);
		if (!bTrans)
		{
			MessageBox("Invalid width", "PageDesigner", MB_OK);
			return FALSE;
		}
		m_brushSettings->put_brushWidth(brushWidth);

		double brushHeight = GetDlgItemValue(m_hWnd, IDC_BRUSH_HEIGHT, &bTrans);
		if (!bTrans)
		{
			MessageBox("Invalid height", "PageDesigner", MB_OK);
			return FALSE;
		}
		m_brushSettings->put_brushHeight(brushHeight);

		double brushAngle = GetDlgItemAngle(m_hWnd, IDC_BRUSH_ANGLE, &bTrans);
		if (!bTrans)
		{
			MessageBox("Invalid angle", "PageDesigner", MB_OK);
			return FALSE;
		}
		m_brushSettings->put_brushAngle(brushAngle);

		int showBrush = IsDlgButtonChecked(IDC_BRUSH_SHOW);
		m_brushSettings->put_showBrushSize(showBrush? VARIANT_TRUE: VARIANT_FALSE);

		return TRUE;
	}

	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		UINT idCtl = (UINT) wParam;             // control identifier 
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; // item-drawing information 

		if (lpdis->itemID >= 0)
		{
			TCHAR text[256];
			::SendMessage(lpdis->hwndItem, CB_GETLBTEXT, lpdis->itemID, (LPARAM)text);

			CRect& rcItem = *(CRect*)&lpdis->rcItem;

			if (text[0])
			{
				int oldBk = SetBkMode(lpdis->hDC, TRANSPARENT);

				FillSolidRect(lpdis->hDC, &rcItem, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHT): GetSysColor(COLOR_WINDOW));

				CRect trect = rcItem;
				trect.InflateRect(-1, -1);
				//trect.left += 22;
				SetTextColor(lpdis->hDC, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHTTEXT): GetSysColor(COLOR_WINDOWTEXT));
				DrawText(lpdis->hDC, text, lstrlen(text), &trect, DT_SINGLELINE | DT_VCENTER);

				SetBkMode(lpdis->hDC, oldBk);

				if (lpdis->itemState & ODS_FOCUS)
				{
					DrawFocusRect(lpdis->hDC, &rcItem);
				}
			}
			else
			{
				MoveToEx(lpdis->hDC, rcItem.left+1, rcItem.top + rcItem.Height()/2, NULL);
				LineTo(lpdis->hDC, rcItem.right, rcItem.top + rcItem.Height()/2);
			}
		}

		return 0;
	}
};

#endif //__BRUSHDIMENSIONSDLG_H_
