// ServersDlg.cpp : Implementation of CServersDlg
#include "stdafx.h"
#include "LXWebSite.h"
#include "ServersDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CServersDlg

LRESULT CServersDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	USES_CONVERSION;

	m_list = GetDlgItem(IDC_SERVERS_LIST);

//	m_list.SetUnicodeFormat(TRUE);

	::EnableWindow(GetDlgItem(IDC_SERVERS_DELETE), FALSE);

	::EnableWindow(GetDlgItem(IDC_SERVERS_NAME), FALSE);
	::EnableWindow(GetDlgItem(IDC_SERVERS_SERVERNAME), FALSE);
	::EnableWindow(GetDlgItem(IDC_SERVERS_DIRECTORY), FALSE);
	::EnableWindow(GetDlgItem(IDC_SERVERS_USERNAME), FALSE);
	::EnableWindow(GetDlgItem(IDC_SERVERS_PASSWORD), FALSE);

#if 0
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;// | LVCF_SUBITEM;//nMask;
	lvc.fmt = LVCFMT_LEFT;//nFmt;
	lvc.pszText = (LPTSTR)_T("Name");
	lvc.cx = 140;//GetStringWidth(lvc.pszText) + 15;
	//if(nMask & LVCF_SUBITEM)
	lvc.iSubItem = 0;//(nSubItem != -1) ? nSubItem : nItem;
	m_list.InsertColumn(0/*nItem*/, &lvc);
#endif

	for (int i = 0; i < m_servers.GetSize(); i++)
	{
		CServer* pServer = m_servers[i];

		LVITEM item;
		item.mask = LVIF_TEXT | LVIF_PARAM;
		item.iItem = i;//nItem;
		item.iSubItem = 0;
		item.pszText = LPSTR_TEXTCALLBACK;//(LPTSTR)W2A(pServer->m_name);
		//item.state = nState;
		//item.stateMask = nStateMask;
		//item.iImage = nImage;
		item.lParam = (LPARAM)pServer;
		m_list.InsertItem(&item);
	}

	return 1;  // Let the system set the focus
}

LRESULT CServersDlg::OnServersNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	CComObject<CServer>* pServer;
	CComObject<CServer>::CreateInstance(&pServer);
	pServer->AddRef();

	pServer->m_name = L"Server_0";

	m_servers.Add(pServer);

	LVITEM item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = m_list.GetItemCount();//0;//0;//nItem;
	item.iSubItem = 0;
	item.pszText = LPSTR_TEXTCALLBACK;//W2A(pServer->m_name);
	item.cchTextMax = 0;
	//item.state = nState;
	//item.stateMask = nStateMask;
	//item.iImage = nImage;
	item.lParam = (LPARAM)pServer;
	int index = m_list.InsertItem(&item);

	m_list.SelectItem(index);

	::SetFocus(GetDlgItem(IDC_SERVERS_NAME));
	SendDlgItemMessage(IDC_SERVERS_NAME, EM_SETSEL, 0, -1);

	return 0;
}

#if 0
LRESULT CServersDlg::OnListDeleteItem(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	LPNMLISTVIEW pnmv = (LPNMLISTVIEW)pnmh;

	for (int i = 0; i < m_servers.GetSize(); i++)
	{
		if (m_servers[i] == (CServer*)pnmv->lParam)
		{
			m_servers.RemoveAt(i);
			break;
		}
	}

	return 0;
}
#endif

LRESULT CServersDlg::OnServersDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = m_list.GetSelectedIndex();
	if (index >= 0)
	{
		CServer* pServer = (CServer*)m_list.GetItemData(index);

		for (int i = 0; i < m_servers.GetSize(); i++)
		{
			if (m_servers[i] == pServer)
			{
				pServer->Release();
				m_servers.RemoveAt(i);
				break;
			}
		}

		m_list.DeleteItem(index);
//		CServer* pServer = (CServer*)m_list.GetItemData(index);
	}

	return 0;
}

LRESULT CServersDlg::OnServerName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	int index = m_list.GetSelectedIndex();

	CServer* pServer = (CServer*)m_list.GetItemData(index);

	TCHAR buf[1024];
	GetDlgItemText(IDC_SERVERS_NAME, buf, _countof(buf));
	pServer->m_name = A2W(buf);

	m_list.Update(index);

	return 0;
}

#if 0
LRESULT CServersDlg::OnListClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	USES_CONVERSION;


	/*int oldindex = m_list.GetSelectedIndex();
	if (oldindex >= 0)
	{
		CServer* pServer = (CServer*)m_list.GetItemData(oldindex);

		TCHAR buf[1024];
		GetDlgItemText(IDC_SERVERS_NAME, buf, _countof(buf));
		pServer->m_name = A2W(buf);

		GetDlgItemText(IDC_SERVERS_SERVERNAME, buf, _countof(buf));
		pServer->m_serverName = A2W(buf);

		GetDlgItemText(IDC_SERVERS_DIRECTORY, buf, _countof(buf));;
		pServer->m_directory = A2W(buf);

		GetDlgItemText(IDC_SERVERS_USERNAME, buf, _countof(buf));
		pServer->m_userName = A2W(buf);

		GetDlgItemText(IDC_SERVERS_PASSWORD, buf, _countof(buf));
		pServer->m_password = A2W(buf);
	}
	*/

	LPNMLISTVIEW lpnmia = (LPNMLISTVIEW)pnmh;

//	CServer* pServer = (CServer*)lpnmia->lParam;

	if (lpnmia->iItem >= 0)
	{
		CServer* pServer = (CServer*)m_list.GetItemData(lpnmia->iItem);

		::EnableWindow(GetDlgItem(IDC_SERVERS_DELETE), TRUE);

		::EnableWindow(GetDlgItem(IDC_SERVERS_NAME), TRUE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_SERVERNAME), TRUE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_DIRECTORY), TRUE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_USERNAME), TRUE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_PASSWORD), TRUE);

		SetDlgItemText(IDC_SERVERS_NAME, W2A(pServer->m_name));
		SetDlgItemText(IDC_SERVERS_SERVERNAME, W2A(pServer->m_serverName));
		SetDlgItemText(IDC_SERVERS_DIRECTORY, W2A(pServer->m_directory));
		SetDlgItemText(IDC_SERVERS_USERNAME, W2A(pServer->m_userName));
		SetDlgItemText(IDC_SERVERS_PASSWORD, W2A(pServer->m_password));
	}
	else
	{
		::EnableWindow(GetDlgItem(IDC_SERVERS_DELETE), FALSE);

		::EnableWindow(GetDlgItem(IDC_SERVERS_NAME), FALSE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_SERVERNAME), FALSE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_DIRECTORY), FALSE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_USERNAME), FALSE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_PASSWORD), FALSE);

		SetDlgItemText(IDC_SERVERS_NAME, NULL);
		SetDlgItemText(IDC_SERVERS_SERVERNAME, NULL);
		SetDlgItemText(IDC_SERVERS_DIRECTORY, NULL);
		SetDlgItemText(IDC_SERVERS_USERNAME, NULL);
		SetDlgItemText(IDC_SERVERS_PASSWORD, NULL);
	}

	return 0;
}
#endif

LRESULT CServersDlg::OnListChanging(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	USES_CONVERSION;

	LPNMLISTVIEW lpnmia = (LPNMLISTVIEW)pnmh;

// Deselecting
	if ((lpnmia->uOldState & LVIS_SELECTED) && !(lpnmia->uNewState & LVIS_SELECTED))
	{
		CServer* pServer = (CServer*)lpnmia->lParam;//m_list.GetItemData(lpnmia->iItem);

		UpdateServer(pServer);

		::EnableWindow(GetDlgItem(IDC_SERVERS_DELETE), FALSE);

		::EnableWindow(GetDlgItem(IDC_SERVERS_NAME), FALSE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_SERVERNAME), FALSE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_DIRECTORY), FALSE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_USERNAME), FALSE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_PASSWORD), FALSE);

		SetDlgItemText(IDC_SERVERS_NAME, NULL);
		SetDlgItemText(IDC_SERVERS_SERVERNAME, NULL);
		SetDlgItemText(IDC_SERVERS_DIRECTORY, NULL);
		SetDlgItemText(IDC_SERVERS_USERNAME, NULL);
		SetDlgItemText(IDC_SERVERS_PASSWORD, NULL);
	}
// Selecting
	else if (!(lpnmia->uOldState & LVIS_SELECTED) && (lpnmia->uNewState & LVIS_SELECTED))
	{
		CServer* pServer = (CServer*)lpnmia->lParam;//m_list.GetItemData(lpnmia->iItem);

		::EnableWindow(GetDlgItem(IDC_SERVERS_DELETE), TRUE);

		::EnableWindow(GetDlgItem(IDC_SERVERS_NAME), TRUE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_SERVERNAME), TRUE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_DIRECTORY), TRUE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_USERNAME), TRUE);
		::EnableWindow(GetDlgItem(IDC_SERVERS_PASSWORD), TRUE);

		SetDlgItemText(IDC_SERVERS_NAME, W2A(pServer->m_name));
		SetDlgItemText(IDC_SERVERS_SERVERNAME, W2A(pServer->m_serverName));
		SetDlgItemText(IDC_SERVERS_DIRECTORY, W2A(pServer->m_directory));
		SetDlgItemText(IDC_SERVERS_USERNAME, W2A(pServer->m_userName));
		SetDlgItemText(IDC_SERVERS_PASSWORD, W2A(pServer->m_password));
	}

	return 0;
}

void CServersDlg::UpdateServer(CServer* pServer)
{
	USES_CONVERSION;

	TCHAR buf[1024];
	GetDlgItemText(IDC_SERVERS_NAME, buf, _countof(buf));
	pServer->m_name = A2W(buf);

	GetDlgItemText(IDC_SERVERS_SERVERNAME, buf, _countof(buf));
	pServer->m_serverName = A2W(buf);

	GetDlgItemText(IDC_SERVERS_DIRECTORY, buf, _countof(buf));;
	pServer->m_directory = A2W(buf);

	GetDlgItemText(IDC_SERVERS_USERNAME, buf, _countof(buf));
	pServer->m_userName = A2W(buf);

	GetDlgItemText(IDC_SERVERS_PASSWORD, buf, _countof(buf));
	pServer->m_password = A2W(buf);
}

LRESULT CServersDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = m_list.GetSelectedIndex();
	if (index >= 0)
	{
		CServer* pServer = (CServer*)m_list.GetItemData(index);

		UpdateServer(pServer);
	}

	EndDialog(wID);
	return 0;
}

/*
LRESULT CServersDlg::OnListActivate(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	USES_CONVERSION;

	LPNMITEMACTIVATE lpnmia = (LPNMITEMACTIVATE)pnmh;

	CServer* pServer = (CServer*)lpnmia->lParam;

	::EnableWindow(GetDlgItem(IDC_SERVERS_DELETE), TRUE);

	::EnableWindow(GetDlgItem(IDC_SERVERS_NAME), TRUE);
	::EnableWindow(GetDlgItem(IDC_SERVERS_SERVERNAME), TRUE);
	::EnableWindow(GetDlgItem(IDC_SERVERS_DIRECTORY), TRUE);
	::EnableWindow(GetDlgItem(IDC_SERVERS_USERNAME), TRUE);
	::EnableWindow(GetDlgItem(IDC_SERVERS_PASSWORD), TRUE);

	SetDlgItemText(IDC_SERVERS_NAME, W2A(pServer->m_name));
	SetDlgItemText(IDC_SERVERS_SERVERNAME, W2A(pServer->m_serverName));
	SetDlgItemText(IDC_SERVERS_DIRECTORY, W2A(pServer->m_directory));
	SetDlgItemText(IDC_SERVERS_USERNAME, W2A(pServer->m_userName));
	SetDlgItemText(IDC_SERVERS_PASSWORD, W2A(pServer->m_password));

	return 0;
}
*/
LRESULT CServersDlg::OnListGetDispInfo(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	USES_CONVERSION;

	NMLVDISPINFO* pnmv = (NMLVDISPINFO*)pnmh;

	CServer* pServer = (CServer*)pnmv->item.lParam;

	if (pnmv->item.mask & LVIF_TEXT)
	{
		lstrcpyn(pnmv->item.pszText, W2A(pServer->m_name), pnmv->item.cchTextMax);
	}

	return 0;
}
