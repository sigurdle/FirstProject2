// ToolbarsDlg.cpp : Implementation of CToolbarsDlg
#include "stdafx.h"
//#include "UICustomizeMod.h"
#include "ToolbarsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CToolbarsDlg

void CToolbarsDlg::InitListBox()
{
	long nToolbars;
	m_uiManager->get_DlgCount(&nToolbars);

	for (long i = 0; i < nToolbars; i++)
	{
		CComPtr<IUIDlgSite> dlgclass;
		m_uiManager->GetDialogBar(i, &dlgclass);

		CComBSTR name;
		dlgclass->GetName(&name);

		int index = ::SendMessage(GetDlgItem(IDC_TOOLBARS), LB_ADDSTRING, 0, (LPARAM)(TCHAR*)_bstr_t(name));
		::SendMessage(GetDlgItem(IDC_TOOLBARS), LB_SETITEMDATA, index, (LPARAM)dlgclass.p);
	}
}

LRESULT CToolbarsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_list.SubclassWindow(GetDlgItem(IDC_TOOLBARS));

	InitListBox();

//	GetDlgControl(IDC_TOOLBARS, __uuidof(m_list), (void**)&m_list);

//	m_list->CheckStyle = 1;


//	IDispEventImpl<1, CToolbarsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_list);

	return 1;  // Let the system set the focus
}

LRESULT CToolbarsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	IDispEventImpl<1, CToolbarsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_list);

	return 0;
}

/*
void __stdcall CToolbarsDlg::OnCheckToolBar()
{
	if (m_list->cursel > -1)
	{
		IUIRegisteredDlg* dlgclass = (IUIRegisteredDlg*)m_list->GetItemData(m_list->cursel);

		dlgclass->CreateDlg();
	}
}
*/

LRESULT CToolbarsDlg::OnToolbarsLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	m_list.DefWindowProc(uMsg, wParam, lParam);

	int index = ::SendMessage(m_list.m_hWnd, LB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		CRect rcItem;
		::SendMessage(m_list.m_hWnd, LB_GETITEMRECT, index, (LPARAM)&rcItem);

		CRect cbrect = rcItem;
		cbrect.right = cbrect.left+18;
		cbrect.InflateRect(-1, -1);

		if (cbrect.PtInRect(point))
		{
			IUIDlgSite* dlgbar = (IUIDlgSite*)::SendMessage(m_list.m_hWnd, LB_GETITEMDATA, index, 0);

			BOOL bVisible;
			dlgbar->IsVisible(&bVisible);

#if 0
			if (bVisible)
			{
				dlgbar->SetVisible(FALSE);
			}
			else
			{
				dlgbar->SetVisible(TRUE);
			}
#endif

#if 0
			CComPtr<IUIDlg> dlg;
			dlgclass->CreateDlg(&dlg);
			if (dlg == NULL)
			{
				MessageBox("Couldn't create dialog", "Customize", MB_OK);
			}
#endif
		}
	}

	return 0;
}

LRESULT CToolbarsDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT idCtl = (UINT) wParam;             // control identifier 
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; // item-drawing information 

	if (lpdis->itemID >= 0)
	{
		TCHAR text[256];
		::SendMessage(lpdis->hwndItem, LB_GETTEXT, lpdis->itemID, (LPARAM)text);
		IUIDlgSite* dlgbar = (IUIDlgSite*)::SendMessage(lpdis->hwndItem, LB_GETITEMDATA, lpdis->itemID, 0);

		CRect& rcItem = *(CRect*)&lpdis->rcItem;

		int oldBk = SetBkMode(lpdis->hDC, TRANSPARENT);

		FillSolidRect(lpdis->hDC, &rcItem, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHT): GetSysColor(COLOR_WINDOW));

		CRect selectedRect = rcItem;

		BOOL bVisible = FALSE;
		dlgbar->IsVisible(&bVisible);

		CRect cbrect = rcItem;
		cbrect.right = cbrect.left+18;
		cbrect.InflateRect(-1, -1);
		DrawFrameControl(lpdis->hDC, &cbrect, DFC_BUTTON, DFCS_BUTTONCHECK | (bVisible? DFCS_CHECKED: 0));

		/*
		if (imageIndex >= 0)
		{
			selectedRect.left += 20;

			CRect iconrect = rcItem;
			iconrect.right = iconrect.left+20;

			int cx, cy;
			ImageList_GetIconSize(hImageList, &cx, &cy);

			ImageList_Draw(hImageList, imageIndex, lpdis->hDC, iconrect.left+(iconrect.Width()-cx)/2, iconrect.top+(iconrect.Height()-cy)/2, ILD_TRANSPARENT);

			if (lpdis->itemState & ODS_SELECTED)
			{
				Draw3DRect(lpdis->hDC, &iconrect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
			}
		}
		*/

//		FillSolidRect(lpdis->hDC, &selectedRect, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHT): GetSysColor(COLOR_BTNFACE));

		CRect trect = rcItem;
		trect.left += 22;
		SetTextColor(lpdis->hDC, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHTTEXT): GetSysColor(COLOR_WINDOWTEXT));
		DrawText(lpdis->hDC, text, lstrlen(text), &trect, DT_SINGLELINE | DT_VCENTER);

		/*
		if (cmdType == 1)
		{
			CRect textbnd(0,0,0,0);
			DrawText(lpdis->hDC, text, lstrlen(text), &textbnd, DT_SINGLELINE | DT_CALCRECT);

			int height = 18;
			int top = rcItem.top + (rcItem.Height()-height)/2;

			Rectangle(lpdis->hDC, trect.left + textbnd.Width()+2, top, rcItem.right-2, top+height);

			CRect arrowrect(rcItem.right-2-18+1, top+1, rcItem.right-2-1, top+height-1);
			DrawFrameControl(lpdis->hDC, &arrowrect, DFC_SCROLL, DFCS_SCROLLCOMBOBOX | DFCS_FLAT);
		}
		*/

		SetBkMode(lpdis->hDC, oldBk);
	}

	return 0;
}

#include "NewToolbarDlg.h"

LRESULT CToolbarsDlg::OnNewToolbar(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CNewToolbarDlg dlg;
	dlg.m_name = L"New Toolbar";

	if (dlg.DoModal() == IDOK)
	{
		ATLASSERT(0);
#if 0
		CComPtr<IUIRegisteredDlg> rdlg;
		m_uiManager->RegisterDlg(CLSID_NULL, dlg.m_name, 0, &rdlg);
		if (rdlg)
		{
			::SendMessage(GetDlgItem(IDC_TOOLBARS), LB_RESETCONTENT, 0, 0);
			InitListBox();

			//rdlg->CreateDlg();
		}
#endif
	}

	return 0;
}
