#include "stdafx.h"
#include "LFC.h"
#include "MSWindows.h"

//#include "../include/windows_header.h"

//extern System::MSWindows::HINSTANCE g_hModule;

namespace System
{
extern Module _Module;

namespace MSWindows
{

BOOL Hwnd::PostMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::PostMessageW(m_hWnd, Msg, wParam, lParam);
}

LRESULT Hwnd::SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessageW(m_hWnd, Msg, wParam, lParam);
}

UINT_PTR Hwnd::SetTimer(UINT_PTR nIDEvent, UINT uElapse)
{
	return ::SetTimer(m_hWnd, nIDEvent, uElapse, NULL);
}

UINT_PTR WindowImpl::SetTimer(UINT_PTR nIDEvent, UINT uElapse)
{
	return ::SetTimer(m_hWnd, nIDEvent, uElapse, NULL);
}

BOOL Hwnd::MoveWindow(int x, int y, int nWidth, int nHeight, bool bRepaint/* = true*/)
{
	return ::MoveWindow(m_hWnd, x, y, nWidth, nHeight, bRepaint);
}

LONG_PTR Hwnd::SetWindowLong(int nIndex, LONG_PTR dwNewLong )
{
	return ::SetWindowLongPtrW(m_hWnd, nIndex, dwNewLong);
}

LONG_PTR WindowImpl::SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong)
{
	return ::SetWindowLongPtrW(m_hWnd, nIndex, dwNewLong);
}

HWND Hwnd::SetParent(HWND hWndNewParent)
{
	return ::SetParent(m_hWnd, hWndNewParent);
}

LONG_PTR Hwnd::GetWindowLongPtr(int nIndex)
{
	return ::GetWindowLongPtrW(m_hWnd, nIndex);
}

LONG_PTR WindowImpl::GetWindowLongPtr(int nIndex)
{
	return ::GetWindowLongPtrW(m_hWnd, nIndex);
}

/*
LRESULT Hwnd::DefWindowProc(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcA(m_hWnd, Msg, wParam, lParam);
}
*/

BOOL Hwnd::SetProp(LPCWSTR lpString, HANDLE hData)
{
	return ::SetPropW(m_hWnd, lpString, hData);
}

BOOL WindowImpl::SetProp(LPCWSTR lpString, HANDLE hData)
{
	return ::SetPropW(m_hWnd, lpString, hData);
}

/////////////////////////////////////
// WindowImpl

WindowImpl::~WindowImpl()
{
	ASSERT(m_hWnd == NULL);	// Window must be destroyed before destructor is reached
}

// static
LRESULT CALLBACK WindowImpl::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return WndProc(Hwnd(hWnd), uMsg, wParam, lParam);
}

// static inline
LRESULT CALLBACK WindowImpl::WndProc(Hwnd hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
		{
			CREATESTRUCT* lpcs = (CREATESTRUCT*) lParam;
			WindowImpl* pWindow = ((Data*)lpcs->lpCreateParams)->m_window;
			pWindow->m_hWnd = hWnd;
			pWindow->SetWindowLongPtr(GWLP_USERDATA, (long)((Data*)lpcs->lpCreateParams));	// This is faster to retrieve if we know we own the HWND
			pWindow->SetProp(L"lxui_window", (HANDLE)((Data*)lpcs->lpCreateParams));	// This must be used if we don't know if we own the HWND
			return true;
		}
		break;

	default:
		{
			WindowImpl* pWindow = ((Data*)hWnd.GetWindowLongPtr(GWLP_USERDATA))->m_window;
			if (pWindow)
				return pWindow->WindowProc(uMsg, wParam, lParam);
			else
				return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);	// ??
		}
		break;
	}
	return 0;
}

Hwnd WindowImpl::Create(Hwnd hWndParent, const gm::RectI & rect, LPCWSTR title, DWORD dwStyle, DWORD dwExStyle, UINT nID)
{
	// TODO, maybe use class name as window class name ?
	{
		WNDCLASSEXW wc = {0};
		wc.cbSize = sizeof(wc);
		wc.hInstance = _Module.GetModuleInstance();
		wc.lpszClassName = L"gen_window_class";
		wc.lpfnWndProc = WndProc;
		wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
		RegisterClassExW(&wc);
	}

	Data* pdata = new Data;
	pdata->m_window = this;

	CreateWindowExW(dwExStyle, L"gen_window_class", NULL, dwStyle,
		rect.X, rect.Y, rect.Width, rect.Height,
		hWndParent, (HMENU)nID, _Module.GetModuleInstance(), pdata);
	return m_hWnd;
}

//	virtual
LRESULT WindowImpl::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lresult;
	BOOL bHandled = ProcessWindowMessage(m_hWnd, uMsg, wParam, lParam, lresult);
	if (!bHandled)
	{
		lresult = DefWindowProc(uMsg, wParam, lParam);
	}

	if (uMsg == WM_NCDESTROY)
	{
		m_hWnd = NULL;
	}
	return lresult;
}

LRESULT WindowImpl::DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(m_hWnd, uMsg, wParam, lParam);
}

}	// MSWindows
}
