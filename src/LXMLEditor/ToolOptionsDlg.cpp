// ToolOptionsDlg.cpp : Implementation of CToolOptionsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ToolOptionsDlg.h"

namespace System
{
namespace LXmlEdit
{
/////////////////////////////////////////////////////////////////////////////
// CToolOptionsDlg

long CToolOptionsDlg::OnCreate()
{
	ASSERT(0);
#if 0
	m_presetsPopup->Create(m_hWnd);
	m_presetsPopup->ShowWindow(SW_SHOW);

	m_sheet->Create(m_hWnd);
	m_sheet->ShowWindow(SW_SHOW);
#endif

	return 0;
}

long CToolOptionsDlg::OnDestroy()
{
	return 0;
}

long CToolOptionsDlg::OnSize()
{
	ASSERT(0);
#if 0
	CRect client;
	GetClientRect(&client);

	{
		HWND hwnd;
		m_presetsPopup->get_hwnd(&hwnd);
		::MoveWindow(hwnd, 0, 0, 32, client.bottom, TRUE);
	}

	{
		HWND hwnd;
		m_sheet->get_hwnd(&hwnd);
		::MoveWindow(hwnd, 32, 0, client.right-32, client.bottom, TRUE);
	}
#endif

	return 0;
}

}	// LXmlEdit
}
