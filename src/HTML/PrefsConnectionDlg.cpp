// PrefsConnectionDlg.cpp : Implementation of CPrefsConnectionDlg
#include "stdafx.h"
#include "LHTML.h"
#include "LHTML2.h"
#include "PrefsConnectionDlg.h"

static DWORD BitRates[] =
{
	28800,
	33600,
	56600,
	64000,
	128000,
	256000,
	384000,
	512000,
	768000,
	1000000,
	1500000,
	10000000,
};

#define NUMBITRATES (sizeof(BitRates)/sizeof(DWORD))

/////////////////////////////////////////////////////////////////////////////
// CPrefsConnectionDlg

LRESULT CPrefsConnectionDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComboBox speed = GetDlgItem(IDC_CONNECTION_SPEED);

	speed.AddString("28.8 Kbps");
	speed.AddString("33.6 Kbps");
	speed.AddString("56.6 Kbps");
	speed.AddString("Single ISDN (64 Kbps)");
	speed.AddString("Dual ISDN (128 Kbps)");
	speed.AddString("DSL/Cable (256 Kbps)");
	speed.AddString("DSL/Cable (384 Kbps)");
	speed.AddString("DSL/Cable (512 Kbps)");
	speed.AddString("DSL/Cable (768 Kbps)");
	speed.AddString("1 Mbps Cable");
	speed.AddString("T1 (1.5 Mbps)");
	speed.AddString("Office LAN (10 Mbps and above)");

	for (int i = 0; i < NUMBITRATES; i++)
	{
		if (m_pPrefs->m_systemBitrate <= BitRates[i])
		{
			speed.SetCurSel(i);
			break;
		}
	}

	return 1;  // Let the system set the focus
}

BOOL CPrefsConnectionDlg::OnApply()
{
	CComboBox speed = GetDlgItem(IDC_CONNECTION_SPEED);

	if (speed.GetCurSel() >= 0)
	{
		m_pPrefs->m_systemBitrate = BitRates[speed.GetCurSel()];
	}

	return TRUE;
}
