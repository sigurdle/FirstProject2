// SettingsServersDlg.cpp : Implementation of CSettingsServersDlg
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "SettingsServersDlg.h"

#include "LXWebSiteApp.h"

/////////////////////////////////////////////////////////////////////////////
// CSettingsServersDlg

LRESULT CSettingsServersDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_ftpServer = GetDlgItem(IDC_SITESERVERS_FTP);

	for (int i = 0; i < m_pApp->m_servers.GetSize(); i++)
	{
		if (!wcsncmp(m_pApp->m_servers[i]->m_serverName, L"ftp", 3))
		{
			int index = m_ftpServer.AddString(_bstr_t(m_pApp->m_servers[i]->m_name));
		}
	}

	m_ftpServer.SetWindowText(_bstr_t(m_ftpServerName));

	return 1;  // Let the system set the focus
}
