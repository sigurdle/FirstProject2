// AboutDlg.cpp : Implementation of CAboutDlg
#include "stdafx.h"
#include "AboutDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg

static WCHAR* text =
L"Programming and Design:\n"
L"Sigurd Lerstad\n"
L"\n"
L"Thanks to:\n"
L"My family (in alphabetical order): Anders, Håkon, Sissel, Vidar\n"
L"\n"
L"And a special thanks to:\n"
L"Iris Brandsegg"
;

LRESULT CAboutDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC	dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	{
		Gdiplus::Graphics graphics(dc);
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
		graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

		{
			WCHAR* title = L"PageDesigner";

			Gdiplus::Font font(L"Arial", 30);

			Gdiplus::RectF layoutrect(0, 0, client.right, 70);

			Gdiplus::StringFormat stringFormat(0);
			stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);

			Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0));

			graphics.DrawString(title, wcslen(title), &font, layoutrect, &stringFormat, &brush);
		}

		graphics.DrawLine(&Gdiplus::Pen(Gdiplus::Color(0,0,0)), 10, 70-1, client.right-10, 70-1);
		graphics.DrawLine(&Gdiplus::Pen(Gdiplus::Color(0,0,0)), 10, client.bottom-40+1, client.right-10, client.bottom-40+1);

		{
			Gdiplus::Font font(L"Arial", 7);

			Gdiplus::RectF layoutrect(10, 70, client.right-20, client.bottom-40-70);

			Gdiplus::StringFormat stringFormat(0);
			stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);

			Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));

			graphics.DrawString(text, wcslen(text), &font, layoutrect, &stringFormat, &brush);
		}

	}

	return 0;
}

LRESULT CAboutDlg::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HDC hDC = (HDC)wParam;

	CRect client;
	GetClientRect(&client);

	FillSolidRect(hDC, &client, RGB(255, 255, 255));

	return TRUE;
}

LRESULT CAboutDlg::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO : Add Code for message handler. Call DefWindowProc if necessary.
	return 0;
}
