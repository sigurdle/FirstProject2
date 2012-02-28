// FileTypesDlg.cpp : Implementation of CFileTypesDlg
#include "stdafx.h"
#include "FileTypesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CFileTypesDlg

LRESULT CFileTypesDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	for (int i = 0; i < m_fileTypes->m_fileTypes.GetSize(); i++)
	{
		CFileType* pFileType = m_fileTypes->m_fileTypes[i];
		long index = SendDlgItemMessage(IDC_FILETYPES, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)pFileType->m_id);
		SendDlgItemMessage(IDC_FILETYPES, LB_SETITEMDATA, index, (LPARAM)pFileType);
	}

	::EnableWindow(GetDlgItem(IDC_FILETYPE_REGISTERED), FALSE);

	return 1;  // Let the system set the focus
}

LRESULT CFileTypesDlg::OnFileTypeChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = SendDlgItemMessage(IDC_FILETYPES, LB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		CFileType* pFileType = (CFileType*)SendDlgItemMessage(IDC_FILETYPES, LB_GETITEMDATA, index, 0);

		::EnableWindow(GetDlgItem(IDC_FILETYPE_REGISTERED), TRUE);

		int isRegistered = pFileType->IsFileTypeRegistered();

		UINT nCheck;
		if (isRegistered == 1)
			nCheck = BST_CHECKED;
		else if (isRegistered == 0)
			nCheck = BST_UNCHECKED;
		else
			nCheck = BST_INDETERMINATE;

		CheckDlgButton(IDC_FILETYPE_REGISTERED, nCheck);
	}

	return 0;
}

LRESULT CFileTypesDlg::OnFileTypeRegister(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = SendDlgItemMessage(IDC_FILETYPES, LB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		CFileType* pFileType = (CFileType*)SendDlgItemMessage(IDC_FILETYPES, LB_GETITEMDATA, index, 0);

		UINT nCheck = IsDlgButtonChecked(IDC_FILETYPE_REGISTERED);

		if (nCheck == BST_CHECKED)
		{
			pFileType->RegisterFileType();
		}
		else if (nCheck == BST_UNCHECKED)
		{
			pFileType->UnRegisterFileType();
		}
	}

	return 0;
}

#if 0
LRESULT CFileTypesDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT idCtl = (UINT) wParam;             // control identifier 
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; // item-drawing information 

	if (lpdis->itemID >= 0)
	{
		TCHAR text[256];
		::SendMessage(lpdis->hwndItem, LB_GETTEXT, lpdis->itemID, (LPARAM)text);
		CFileType* pFileType = (CFileType*)::SendMessage(lpdis->hwndItem, LB_GETITEMDATA, lpdis->itemID, 0);

		CRect& rcItem = *(CRect*)&lpdis->rcItem;

		int oldBk = SetBkMode(lpdis->hDC, TRANSPARENT);

		FillSolidRect(lpdis->hDC, &rcItem, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHT): GetSysColor(COLOR_WINDOW));

		CRect selectedRect = rcItem;

//		BOOL bVisible;
//		dlgclass->IsVisible(&bVisible);

		int isRegistered = pFileType->IsFileTypeRegistered();

		CRect cbrect = rcItem;
		cbrect.right = cbrect.left+18;
		cbrect.InflateRect(-1, -1);

		UINT uState;
		if (isRegistered == 1)
			 uState = DFCS_CHECKED;
		else if (isRegistered == 0)
			uState = 0;
		else
			uState = DFCS_INACTIVE | DFCS_CHECKED;

		DrawFrameControl(lpdis->hDC, &cbrect, DFC_BUTTON, DFCS_BUTTONCHECK | uState);

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
#endif