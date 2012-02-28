// BrushDimensionsDlg.h : Declaration of the CBrushDimensionsDlg

#ifndef __BRUSHDIMENSIONSDLG_H_
#define __BRUSHDIMENSIONSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

#include "BrushProfileDlg.h"

namespace System
{
namespace LXmlEdit
{

	class CPDBrushSettingsImpl;

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

	CPDBrushSettingsImpl* m_brushSettings;

	enum { IDD = IDD_BRUSHDIMENSIONSDLG };

	/*
BEGIN_MSG_MAP(CBrushDimensionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
	COMMAND_HANDLER(IDC_BRUSH_ANGLE, CBN_SELCHANGE, OnAngleChanged)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(IDC_BRUSH_EDITPROFILE, OnEditBrushProfile)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CBrushDimensionsDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnEditBrushProfile(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		CBrushProfileDlg dlg;
		dlg.DoModal();

		return 0;
	}

	long OnAngleChanged(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		static long prevcursel = -1;

		ASSERT(0);
#if 0
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
#endif
		return 0;
	}

	long OnInitDialog(bool& bHandled)
	{
		ASSERT(0);
#if 0
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

		double brushWidth = m_brushSettings->get_brushWidth();
		SetDlgItemValue(m_hWnd, IDC_BRUSH_WIDTH, brushWidth, LCSS::CSS_PT);

		double brushHeight = m_brushSettings->get_brushHeight();
		SetDlgItemValue(m_hWnd, IDC_BRUSH_HEIGHT, brushHeight, LCSS::CSS_PT);

		double brushAngle = m_brushSettings->get_brushAngle();
		SetDlgItemAngle(m_hWnd, IDC_BRUSH_ANGLE, brushAngle);

		bool showBrush = m_brushSettings->get_showBrushSize();
		CheckDlgButton(IDC_BRUSH_SHOW, showBrush? BST_CHECKED: BST_UNCHECKED);
#endif
		return 1;  // Let the system set the focus
	}

	bool OnApply()
	{
		bool bTrans;

		ASSERT(0);
#if 0
		double brushWidth = GetDlgItemValue(m_hWnd, IDC_BRUSH_WIDTH, &bTrans);
		if (!bTrans)
		{
			MessageBox("Invalid width", "WebEditor", MB_OK);
			return FALSE;
		}
		m_brushSettings->put_brushWidth(brushWidth);

		double brushHeight = GetDlgItemValue(m_hWnd, IDC_BRUSH_HEIGHT, &bTrans);
		if (!bTrans)
		{
			MessageBox("Invalid height", "WebEditor", MB_OK);
			return FALSE;
		}
		m_brushSettings->put_brushHeight(brushHeight);

		double brushAngle = GetDlgItemAngle(m_hWnd, IDC_BRUSH_ANGLE, &bTrans);
		if (!bTrans)
		{
			MessageBox("Invalid angle", "WebEditor", MB_OK);
			return FALSE;
		}
		m_brushSettings->put_brushAngle(brushAngle);

		int showBrush = IsDlgButtonChecked(IDC_BRUSH_SHOW);
		m_brushSettings->put_showBrushSize(showBrush? true: false);
#endif
		return true;
	}

	long OnDrawItem(bool& bHandled)
	{
		ASSERT(0);
#if 0
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
#endif
		return 0;
	}
};

}	// LXmlEdit
}

#endif //__BRUSHDIMENSIONSDLG_H_
