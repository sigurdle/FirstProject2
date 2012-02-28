// FrameworkOptionsDlg.cpp : Implementation of CFrameworkOptionsDlg
#include "stdafx.h"
//#include "LXFramework.h"
#include "FrameworkOptionsDlg.h"

#include "PickIconDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CFrameworkOptionsDlg

LRESULT CFrameworkOptionsDlg::OnChangeIcon(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	/*
	OLEUICHANGEICON ch = {0};
	ch.cbStruct = sizeof(ch);
	ch.dwFlags = 0;
	ch.hWndOwner = m_hWnd;

	if (OleUIChangeIcon(&ch) == OLEUI_OK)
	{
	}
	*/

	TCHAR m_pszCurrentFile[MAX_PATH] = {0};
	DWORD m_dwCurrentIndex = 0;

	if (::SelectIcon(m_hWnd, m_pszCurrentFile, MAX_PATH, &m_dwCurrentIndex))
	{
		HICON m_hIcon = ::ExtractIcon(_Module.m_hInst, m_pszCurrentFile, m_dwCurrentIndex);
		//SetIcon(m_hIcon, TRUE);
		//SetIcon(m_hIcon, FALSE);
	}

	return 0;
}
