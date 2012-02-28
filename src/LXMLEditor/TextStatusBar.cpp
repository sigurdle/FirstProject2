#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "TextStatusBar.h"


#if 0
LRESULT CTextStatusBar::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	CRect rect = client;
	//rect.top = rect.bottom-16-1;

// Draw white dividing line
//	dc.FillSolidRect(0, rect.top, client.right, 1, GetSysColor(COLOR_3DHILIGHT));
	/*
	rect.right++;
	rect.bottom++;
	dc.Draw3dRect(&rect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
	*/
//	rect.top += 1;
	//rect.InflateRect(-1,-1);
	dc.FillSolidRect(&rect, GetSysColor(COLOR_BTNFACE));

	HFONT hOldFont = dc.SelectStockFont(DEFAULT_GUI_FONT);

	dc.SetBkMode(TRANSPARENT);

	CRect rc(client.right-16-2-90, 2, client.right-16-2, 16);
	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

	rc.InflateRect(-1,-1);

	dc.DrawText(m_text, m_text.GetLength(), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	dc.SelectFont(hOldFont);
	return 0;
}

LRESULT CTextStatusBar::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_sizeGrip.Create(m_hWnd, CRect(0, 0, 0, 0), NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP);

	return 0;
}

LRESULT CTextStatusBar::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_sizeGrip.MoveWindow(client.right-16, 0, 16, 16);

	return 0;
}
#endif