// ProgressDlg.cpp : Implementation of CProgressDlg
#include "stdafx.h"
#include "ProgressDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg

LRESULT CProgressDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	CRect rc(10, 10, client.right-10, 20);

	dc.Draw3dRect(&rc, RGB(100, 100, 100), RGB(180, 180, 180));
	rc.InflateRect(2, 2);

	if (m_max != m_min)
	{
		dc.FillSolidRect(rc.left, rc.top, rc.Width() * (m_pos-m_min) / (m_max-m_min), rc.Height(), RGB(80, 80, 120));
	}

	return 0;
}
