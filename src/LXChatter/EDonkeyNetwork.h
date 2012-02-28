#pragma once

#include "FileNetwork.h"
#include "../LFC/MSWindows.h"

namespace System
{

class EDonkeyServerSocket;

class LP2PEXT EDonkeyNetwork :
	public INetwork,
	public MSWindows::WindowImpl//<EDonkeyNetwork>
{
public:
	EDonkeyNetwork(INetworkClient* client)
	{
		m_client = client;

		m_naddr = 0;

		ASSERT(0);
#if 0
	//	RECT rect;
	//	SetRectEmpty(&rect);
		Create(NULL, MSWindows::Rect(), NULL, WS_POPUP);
#endif
	}

	void AddServer(DWORD IPAddress, uint16 Port)
	{
		for (int i = 0; i < m_servers.GetSize(); i++)
		{
			if (m_servers[i]->m_server == IPAddress &&
				m_servers[i]->m_port == Port)
			{
				return;
			}
		}
		m_servers.Add(new Host(IPAddress, Port));
	}

	void OnIdle();

	virtual bool ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::LRESULT& lResult/*, DWORD dwMsgMapID*/ )
	{
		ASSERT(0);
#if 0
		if (uMsg == WM_USER+100)
		{
			m_client->OnConnection((IConnection*)wParam);
			return true;
		}
		else if (uMsg == WM_USER+101)
		{
			m_client->OnCloseConnection((IConnection*)wParam);
			return true;
		}
/*		else if (uMsg == WM_USER+102)
		{
			m_client->OnConnectionStatus((IConnection*)wParam, lParam);
			return true;
		}
		else if (uMsg == WM_USER+103)
		{
			NETWORKINFO* info = (NETWORKINFO*)wParam;

			m_NetworkInfo.NumberOfClients++;
			m_NetworkInfo.NumberOfSharedFiles += info->NumberOfSharedFiles;
			m_NetworkInfo.NumberOfKilobytesShared += info->NumberOfKilobytesShared;

			delete info;

			m_client->OnNetworkInfo(&m_NetworkInfo);
			return true;
		}
		*/

		if (uMsg == WM_USER+104)
		{
			((ISearchHitHandler*)wParam)->OnHit((ISearchHit*)lParam);
		}
#endif
		return false;
	}

	static DWORD WINAPI OnP2PThreadFunc(LPVOID lpdata)
	{
		return ((EDonkeyNetwork*)lpdata)->OnP2PThread();
	}

	DWORD OnP2PThread();

	virtual void Connect();
	virtual IQuery* Search(StringIn criteria, ISearchHitHandler* pSearchHitHandler);
	virtual IFileDownload* Download(int64 FileSize, const uint8 sha1digest[20], IDownloadHandler* handler, System::IO::ByteStreamWriter* stream)
	{
		return NULL;
	}

	Array<Host*> m_servers;
	Array<EDonkeyServerSocket*> m_ServerConnections;

	int m_naddr;

	INetworkClient* m_client;
};

}
