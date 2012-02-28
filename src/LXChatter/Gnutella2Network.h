#ifndef __GNUTELLA2NETWORK_H_
#define __GNUTELLA2NETWORK_H_

#include "FileNetwork.h"
#include "../LFC/MSWindows.h"

namespace System
{

class G2Query;
class G2TCPConnection;
class Gnutella2Network;
class Packet;
class UDPListener;
class G2Node;

class G2SearchHit : public ISearchHit
{
public:

	G2SearchHit()
	{
	}

	System::StringA* get_FileName() const
	{
		return m_FileName;
	}

	LONGLONG get_FileSize() const
	{
		return m_FileSize;
	}

	void GetHost(DWORD* IPAddress, uint16* Port) const
	{
		*IPAddress = m_IPAddress;
		*Port = m_Port;
	}

	DWORD get_HostSpeed() const
	{
		return m_Speed;
	}

	const uint8* get_Sha1Digest() const
	{
		return m_sha1;
	}

//	void urn(char* & p);
//	void ggep(char* & p);
//	void plain(char* & p);

	System::StringA* m_FileName;
	DWORD m_Speed;
	DWORD m_FileSize;
	DWORD m_FileIndex;
	DWORD m_IPAddress;
	uint16 m_Port;
	uint16 m_Pad;
	uint8 m_sha1[20];
};

/*
struct guidless : std::binary_function<const GUID&, const GUID&, bool>
{
	bool operator()(const GUID& _X, const GUID& _Y) const
	{
		return memcmp(&_X, &_Y, 16);
	}
};
*/

class LP2PEXT G2Query : public IQuery
{
public:
	G2Query(Gnutella2Network* pNetwork)
	{
		m_pNetwork = pNetwork;
		m_pSearchHitHandler = NULL;
	}

	Gnutella2Network* m_pNetwork;

	Array<G2Node*> m_searchedNodes;
	Array<G2Node*> m_unsearchedNodes;

	void Init(ISearchHitHandler* pSearchHitHandler, System::StringA* criteria);
	void Search();
	void QueryAcknowledge(const Packet* packet);
	void QueryHit(const Packet* packet);
	Packet* MakeQueryPacket(DWORD queryKey) const;

	void More();

	System::StringA* get_Criteria() const
	{
		return m_criteria;
	}

	inline const GUID& get_ID() const
	{
		return m_queryGuid;
	}

protected:

	ISearchHitHandler* m_pSearchHitHandler;
	System::StringA* m_criteria;
	GUID m_queryGuid;
};

//typedef std::map<std::wstring, Object*> tyusermap;

//class SearchHit;

//typedef std::map<GUID,G2Query*, guidless> tysearchmap;

class LP2PEXT Gnutella2Network :
	public MSWindows::WindowImpl,//<Gnutella2Network>
	public INetwork
{
public:
	Gnutella2Network(INetworkClient* pclient)
	{
		ASSERT(0);
#if 0
		m_client = pclient;

	//	RECT rect;
	//	SetRectEmpty(&rect);
		Create(NULL, MSWindows::Rect(), NULL, WS_POPUP);

		m_naddr = 0;

//		m_nPort = 0;

		m_NetworkInfo.NumberOfClients = 0;
		m_NetworkInfo.NumberOfSharedFiles = 0;
		m_NetworkInfo.NumberOfKilobytesShared = 0;

		CoCreateGuid(&m_guid);
#endif
	}

	GUID m_guid;

	UDPListener* m_udpListener;

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
		else if (uMsg == WM_USER+102)
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
#endif
		return false;
	}

	NETWORKINFO m_NetworkInfo;

	INetworkClient* m_client;
//	WORD m_nPort;

	int m_naddr;
	//std::vector<Host*> m_servers;
	Array<G2Node*> m_nodes;
	Array<G2TCPConnection*> m_connections;

	list<G2Query*> m_searchList;

	//std::vector<SearchHit*> m_queryhits;

	G2Node* AddServer(DWORD server, uint16 port);
	void AddServers(System::StringA* servers);

	void ProcessHeaders(G2TCPConnection* node);

	static DWORD WINAPI OnP2PThreadFunc(LPVOID lpdata)
	{
		return ((Gnutella2Network*)lpdata)->OnP2PThread();
	}

	DWORD OnP2PThread();

	int ConnectP2P(DWORD, int port);

	virtual void Connect();
	virtual IQuery* Search(System::StringA* criteria, ISearchHitHandler* pSearchHitHandler);
	virtual IFileDownload* Download(LONGLONG FileSize, const uint8 sha1digest[20], IDownloadHandler* handler, System::IO::ByteStreamWriter* stream);
};

}

#endif //__GNUTELLA2NETWORK_H_
