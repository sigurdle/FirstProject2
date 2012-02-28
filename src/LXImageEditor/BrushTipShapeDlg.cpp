// BrushTipShapeDlg.cpp : Implementation of CBrushTipShapeDlg
#include "stdafx.h"
#include "LXImageEditor.h"
#include "Image2.h"

#include "BrushTipShapeDlg.h"

/*
#include "WebEditorApp.h"	// TODO remove
#include "WebEditorFrame.h"	// TODO remove
extern CWebEditorApp* gApp;	// TODO remove
*/
#include "ImageApp.h"

/////////////////////////////////////////////////////////////////////////////
// CBrushTipShapeDlg

LRESULT CBrushTipShapeDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	SetDlgItemInt(IDC_BRUSH_SIZE, g_pImageApp->m_brushSize);
#endif

	return 0;
}

LRESULT CBrushTipShapeDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CBrushTipShapeDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	HMENU hMenu;
	hMenu = CreatePopupMenu();

#if 0
	for (int i = 0; i < g_pImageApp->m_paintMethods.GetSize(); i++)
	{
		UINT nFlags = MF_STRING;
		//if (value.Length() && !wcscmp(value, pProperty->m_enumStrings[i])) nFlags |= MF_CHECKED;
		AppendMenu(hMenu, nFlags, i+1, g_pImageApp->m_paintMethods[i]->m_name);
	}
#endif

	::ClientToScreen(m_hWnd, &point);

	UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

	DestroyMenu(hMenu);

	if (nID > 0)
	{
#if 0
		g_pImageApp->m_pActivePaintMethod = g_pImageApp->m_paintMethods[nID-1];
#endif
	}

	return 0;
}

LRESULT CBrushTipShapeDlg::OnBrushSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int value = GetDlgItemInt(wID);

#if 0
	g_pImageApp->m_brushSize = value;
#endif

	return 0;
}

// IUIEventHandler
STDMETHODIMP CBrushTipShapeDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	return S_OK;
}

STDMETHODIMP CBrushTipShapeDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	return S_OK;
}
