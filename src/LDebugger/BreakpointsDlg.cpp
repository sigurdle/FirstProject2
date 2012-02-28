#include "stdafx.h"
#include "BreakpointsDlg.h"
#include "DebuggerFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CBreakpointsDlg

LRESULT CBreakpointsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CListBox list(GetDlgItem(IDC_BREAKPOINTLIST));

	for (int i = 0; i < m_pFrame->m_breakpoints.size(); i++)
	{
		DebugBreakpoint* pBreakpoint = m_pFrame->m_breakpoints[i];

		char str[512];
		sprintf(str, "%s @%d", pBreakpoint->m_filename.c_str(), pBreakpoint->m_line+1);

		int index = list.AddString(str);
		list.SetItemDataPtr(index, pBreakpoint);
	}

	return 1;  // Let the system set the focus
}

LRESULT CBreakpointsDlg::OnRemoveAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_pFrame->RemoveAllBreakpoints();
	CListBox list(GetDlgItem(IDC_BREAKPOINTLIST));
	list.ResetContent();
	return 0;
}
