// KeyboardDlg.cpp : Implementation of CKeyboardDlg
#include "stdafx.h"
#include "KeyboardDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg

LRESULT CKeyboardDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	long ngroups;
	m_uiManager->get_CommandGroupsCount(&ngroups);

	for (int i = 0; i < ngroups; i++)
	{
		CComPtr<IUICommandGroup> cmdGroup;
		m_uiManager->GetCommandGroup(i, &cmdGroup);

		CComBSTR name;
		cmdGroup->get_name(&name);

		long index = ::SendMessage(GetDlgItem(IDC_KEYBOARD_CATEGORIES), LB_ADDSTRING, 0, (LPARAM)(TCHAR*)_bstr_t(name));
		::SendMessage(GetDlgItem(IDC_KEYBOARD_CATEGORIES), LB_SETITEMDATA, index, (LPARAM)cmdGroup.p);
	}

	return 1;  // Let the system set the focus
}

LRESULT CKeyboardDlg::OnChangeCategory(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long index = ::SendMessage(GetDlgItem(IDC_KEYBOARD_CATEGORIES), LB_GETCURSEL, 0, 0);

	if (index >= 0)
	{
		IUICommandGroup* cmdGroup = (IUICommandGroup*)::SendMessage(GetDlgItem(IDC_KEYBOARD_CATEGORIES), LB_GETITEMDATA, index, 0);

		long ncommands;
		cmdGroup->get_length(&ncommands);

		::SendMessage(GetDlgItem(IDC_KEYBOARD_COMMANDS), LB_RESETCONTENT, 0, 0);

		for (int i = 0; i < ncommands; i++)
		{
			CComPtr<IUICommand> cmd;
			cmdGroup->item(i, &cmd);

			CComBSTR name;
			cmd->get_name(&name);

			long index = ::SendMessage(GetDlgItem(IDC_KEYBOARD_COMMANDS), LB_ADDSTRING, 0, (LPARAM)(TCHAR*)_bstr_t(name));
			::SendMessage(GetDlgItem(IDC_KEYBOARD_COMMANDS), LB_SETITEMDATA, index, (LPARAM)cmd.p);
		}
	}

	return 0;
}
