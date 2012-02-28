// CommandsDlg.cpp : Implementation of CCommandsDlg
#include "stdafx.h"
#include "CommandsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CCommandsDlg

LRESULT CCommandsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_commands.SubclassWindow(GetDlgItem(IDC_COMMANDS_COMMANDS));

	long ngroups;
	m_uiManager->get_CommandGroupsCount(&ngroups);

	for (int i = 0; i < ngroups; i++)
	{
		CComPtr<IUICommandGroup> cmdGroup;
		m_uiManager->GetCommandGroup(i, &cmdGroup);

		CComBSTR name;
		cmdGroup->get_name(&name);

		long index = ::SendMessage(GetDlgItem(IDC_COMMANDS_CATEGORIES), LB_ADDSTRING, 0, (LPARAM)(TCHAR*)_bstr_t(name));
		::SendMessage(GetDlgItem(IDC_COMMANDS_CATEGORIES), LB_SETITEMDATA, index, (LPARAM)cmdGroup.p);
	}

	::SendMessage(GetDlgItem(IDC_COMMANDS_COMMANDS), LB_SETITEMHEIGHT, 0, MAKELPARAM(20, 0));

/*
	GetDlgControl(IDC_CATEGORIES, __uuidof(c_categories), (void**)&c_categories);
	GetDlgControl(IDC_COMMANDS, __uuidof(c_commands), (void**)&c_commands);

	unsigned long ngroups = m_uiManager->CommandGroupsCount;

	for (int i = 0; i < ngroups; i++)
	{
		ICommandGroupPtr cmdGroup = m_uiManager->GetCommandGroup(i);

		_bstr_t name = cmdGroup->name;

		long index = c_categories->AddString(name);
		c_categories->SetItemData(index, (DWORD)cmdGroup.GetInterfacePtr());
	}

	HRESULT hr;
	
	hr = IDispEventImpl<1, CCommandsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(c_categories);
	ATLASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<2, CCommandsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(c_commands);
	ATLASSERT(SUCCEEDED(hr));
*/
	return 1;  // Let the system set the focus
}

LRESULT CCommandsDlg::OnChangeCategory(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long index = ::SendMessage(GetDlgItem(IDC_COMMANDS_CATEGORIES), LB_GETCURSEL, 0, 0);

	if (index >= 0)
	{
		IUICommandGroup* cmdGroup = (IUICommandGroup*)::SendMessage(GetDlgItem(IDC_COMMANDS_CATEGORIES), LB_GETITEMDATA, index, 0);

		long ncommands;
		cmdGroup->get_length(&ncommands);

		::SendMessage(GetDlgItem(IDC_COMMANDS_COMMANDS), LB_RESETCONTENT, 0, 0);

		for (int i = 0; i < ncommands; i++)
		{
			CComPtr<IUICommand> cmd;
			cmdGroup->item(i, &cmd);

			CComBSTR name;
			cmd->get_name(&name);

			long index = ::SendMessage(GetDlgItem(IDC_COMMANDS_COMMANDS), LB_ADDSTRING, 0, (LPARAM)(TCHAR*)_bstr_t(name));
			::SendMessage(GetDlgItem(IDC_COMMANDS_COMMANDS), LB_SETITEMDATA, index, (LPARAM)cmd.p);
		}
	}

	return 0;
}

LRESULT CCommandsDlg::OnCommandsLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_commands.DefWindowProc(uMsg, wParam, lParam);

	long index = ::SendMessage(GetDlgItem(IDC_COMMANDS_COMMANDS), LB_GETCURSEL, 0, 0);

	if (index >= 0)
	{
		IUICommand* cmd = (IUICommand*)::SendMessage(GetDlgItem(IDC_COMMANDS_COMMANDS), LB_GETITEMDATA, index, 0);

		HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, sizeof(long));
		if (hData)
		{
			long* pid = (long*)GlobalLock(hData);
			if (pid)
			{
				cmd->get_ID(pid);
				GlobalUnlock(hData);

				CMyDropSource*  dropSource = new CMyDropSource;
				CMyDataObject* dataObject = new CMyDataObject;	// TODO, use COleDataObject

				STGMEDIUM	stg = {0};
				stg.tymed = TYMED_HGLOBAL;
				stg.hGlobal = hData;
				stg.pUnkForRelease = NULL;

				FORMATETC	etc = {0};
				etc.cfFormat = RegisterClipboardFormat("MMStudio-Command");
				etc.tymed = TYMED_HGLOBAL;
				etc.ptd = NULL;
				etc.dwAspect = DVASPECT_CONTENT;
				etc.lindex = -1;

				dataObject->SetData(&etc, &stg, TRUE);

				DWORD dropEffect = 0;
				HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_COPY, &dropEffect);

				if (hr == DRAGDROP_S_DROP)
				{
					if (dropEffect/* & DROPEFFECT_MOVE*/)
					{
					}
				}
			}

			GlobalFree(hData);
		}
	}

	return 0;
}

LRESULT CCommandsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT hr;
/*	
	hr = IDispEventImpl<1, CCommandsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(c_categories);
	ATLASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<2, CCommandsDlg, &DIID__IUIListControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(c_commands);
	ATLASSERT(SUCCEEDED(hr));
*/
	return 0;
}

LRESULT CCommandsDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT idCtl = (UINT) wParam;             // control identifier 
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; // item-drawing information 

	if (lpdis->itemID >= 0)
	{
		TCHAR text[256];
		::SendMessage(lpdis->hwndItem, LB_GETTEXT, lpdis->itemID, (LPARAM)text);
		IUICommand* pCmd = (IUICommand*)::SendMessage(lpdis->hwndItem, LB_GETITEMDATA, lpdis->itemID, 0);

		HIMAGELIST hImageList;
		(HIMAGELIST)pCmd->get_bitmap((unsigned long*)&hImageList);

		long imageIndex;
		pCmd->get_bitmapIndex(&imageIndex);

		CRect& rcItem = *(CRect*)&lpdis->rcItem;

		DWORD cmdType;
		pCmd->get_type(&cmdType);

		int oldBk = SetBkMode(lpdis->hDC, TRANSPARENT);

		FillSolidRect(lpdis->hDC, &rcItem, GetSysColor(COLOR_BTNFACE));

		CRect selectedRect = rcItem;

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

		FillSolidRect(lpdis->hDC, &selectedRect, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHT): GetSysColor(COLOR_BTNFACE));

		CRect trect = rcItem;
		trect.left += 22;
		SetTextColor(lpdis->hDC, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHTTEXT): GetSysColor(COLOR_WINDOWTEXT));
		DrawText(lpdis->hDC, text, lstrlen(text), &trect, DT_SINGLELINE | DT_VCENTER);

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

		SetBkMode(lpdis->hDC, oldBk);
	}

	return 0;
}

#if 0
void __stdcall CCommandsDlg::OnCategory()
{
	long index = c_categories->cursel;

	if (index >= 0)
	{
		c_commands->ResetContent();

		ICommandGroup* cmdGroup = (ICommandGroup*)c_categories->GetItemData(index);

		unsigned long ncommands = cmdGroup->length;

		for (int i = 0; i < ncommands; i++)
		{
			ICommandPtr cmd = cmdGroup->item(i);

			_bstr_t name = cmd->name;

			long index = c_commands->AddString(name);
			c_commands->SetItemData(index, (DWORD)cmd.GetInterfacePtr());
		}
	}
}

void __stdcall CCommandsDlg::OnCommand()
{
}
#endif