// ServersDlg.h : Declaration of the CServersDlg

#ifndef __SERVERSDLG_H_
#define __SERVERSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "Server.h"

/////////////////////////////////////////////////////////////////////////////
// CServersDlg
class CServersDlg : 
	public CAxDialogImpl<CServersDlg>
{
public:
	CServersDlg()
	{
	}

	~CServersDlg()
	{
		for (int i = 0; i < m_servers.GetSize(); i++)
		{
			m_servers[i]->Release();
		}
		m_servers.RemoveAll();
	}

	CListViewCtrl m_list;

	CArray<CComObject<CServer>*,CComObject<CServer>*> m_servers;

	void UpdateServer(CServer* pServer);

	enum { IDD = IDD_SERVERSDLG };

BEGIN_MSG_MAP(CServersDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)

	COMMAND_ID_HANDLER(IDC_SERVERS_NEW, OnServersNew)
	COMMAND_ID_HANDLER(IDC_SERVERS_DELETE, OnServersDelete)

	COMMAND_HANDLER(IDC_SERVERS_NAME, EN_KILLFOCUS, OnServerName)

	//NOTIFY_HANDLER(IDC_SERVERS_LIST, LVN_ITEMACTIVATE, OnListActivate)
	//NOTIFY_HANDLER(IDC_SERVERS_LIST, NM_CLICK, OnListClick)
	NOTIFY_HANDLER(IDC_SERVERS_LIST, LVN_ITEMCHANGING, OnListChanging)
	NOTIFY_HANDLER(IDC_SERVERS_LIST, LVN_GETDISPINFO, OnListGetDispInfo)
//	NOTIFY_HANDLER(IDC_SERVERS_LIST, LVN_DELETEITEM, OnListDeleteItem)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

//	LRESULT OnListActivate(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
//	LRESULT OnListClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnListChanging(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
//	LRESULT OnListDeleteItem(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnListGetDispInfo(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnServersNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnServersDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnServerName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__SERVERSDLG_H_
