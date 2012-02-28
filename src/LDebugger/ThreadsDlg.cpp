// ThreadsDlg.cpp : Implementation of CThreadsDlg
#include "stdafx.h"
#include "ThreadsDlg.h"

#include "Debug.h"

/////////////////////////////////////////////////////////////////////////////
// CThreadsDlg

LRESULT CThreadsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CListViewCtrl list(GetDlgItem(IDC_THREADLIST));

	list.InsertColumn(0, "Suspend Count", 0, 80, 0);
	list.InsertColumn(1, "Priority", 0, 80, 0);
	list.InsertColumn(2, "Location", 0, 100, 0);

	int n = 0;
	tyhthreadmap::iterator ti = m_pDebugProcess->m_threads.begin();
	while (ti != m_pDebugProcess->m_threads.end())
	{
		char suspcount[16];
		sprintf(suspcount, "%d", (*ti).second->m_dwSuspendCount);

		char pri[16];
		sprintf(pri, "%d", GetThreadPriority((*ti).second->m_hThread));

		CONTEXT context;
		GetThreadContext((*ti).second->m_hThread, &context);

		list.AddItem(n, 0, suspcount);
		list.AddItem(n, 1, pri);
		list.AddItem(n, 2, "(null)");

		n++;
		ti++;
	}

	return 1;  // Let the system set the focus
}
