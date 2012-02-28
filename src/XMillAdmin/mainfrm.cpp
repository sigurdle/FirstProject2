#include "stdafx.h"
#include "XMillAdmin.h"
#include "mainfrm.h"

LRESULT CMainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	baseClass::OnCreate(uMsg, wParam, lParam, bHandled);

	EnableDocking(CBRS_ALIGN_ANY);

// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
//	pLoop->AddIdleHandler(this);
	pLoop->AddMessageFilter(this);

	return 0;
}

BEGIN_CMD_MAP(CMainFrame)
END_CMD_MAP()
