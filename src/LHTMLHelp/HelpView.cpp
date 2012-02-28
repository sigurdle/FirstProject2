// HelpView.cpp : Implementation of CHelpView
#include "stdafx.h"
#include "LHTMLHelp.h"
#include "HelpView.h"

#include "HelpContentsWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CHelpView

long CHelpView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_contents = new CHelpContentsWnd;
	m_contents->m_view = this;
	m_contents->Create(m_hWnd, CRect(0,0,0,0), NULL, WS_VISIBLE | WS_CHILD);

	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_html.CoCreateInstance(CLSID_LHTMLControl);

	m_axhtml.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhtml.AttachControl(m_html, &p);

	return 0;
}

long CHelpView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	BeginPaint(&ps);
	HDC hDC = ps.hdc;

	RECT client;
	GetClientRect(&client);

	FillSolidRect(hDC, m_splitx-3, 0, 6, client.bottom, GetSysColor(COLOR_BTNFACE));
	Draw3DRect(hDC, m_splitx-3, 0, 6, client.bottom, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

	EndPaint(&ps);
	return 0;
}

long CHelpView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_dragging)
	{
		SetCapture();
		m_dragging = 1;
	}

	return 0;
}

long CHelpView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}

	return 0;
}

long CHelpView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	if (m_dragging)
	{
		RECT client;
		GetClientRect(&client);

		m_splitx = point.x;

		if (m_splitx < 10) m_splitx = 10;
		else if (m_splitx > client.right-40) m_splitx = client.right-40;

		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return 0;
}

long CHelpView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CHelpView::OnSize()
{
	RECT client;
	GetClientRect(&client);
	int cx = client.right;
	int cy = client.bottom;

	m_contents->MoveWindow(0, 0, m_splitx-3, cy, TRUE);
	m_axhtml.MoveWindow(m_splitx+3, 0, cx-(m_splitx+3), cy, TRUE);
}

#if 0
STDMETHODIMP CHelpView::get_contents(IHelpContentsWnd **pVal)
{
	*pVal = m_contents;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CHelpView::put_contents(IHelpContentsWnd *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CHelpView::get_html(IHTMLControl **pVal)
{
	*pVal = m_html;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CHelpView::put_html(IHTMLControl *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
#endif