#ifndef __GNUTELLANETWORK_H_
#define __GNUTELLANETWORK_H_

#include "FileNetwork.h"
#include "../LFC/MSWindows.h"

namespace System
{

class CGnutellaSearch;
class CGnutellaSocket;
struct GnutellaQueryHitMessage;
class GnutellaNetwork;

class SearchHit : public ISearchHit
{
public:

	SearchHit()
	{
	}

	String get_FileName() const
	{
		return m_FileName;
	}

	int64 get_FileSize() const
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
		return m_digest;
	}

	void urn(char* & p);
	void ggep(char* & p);
	void plain(char* & p);

	String m_FileName;
	DWORD m_Speed;
	DWORD m_FileSize;
	DWORD m_FileIndex;
	DWORD m_IPAddress;
	uint16 m_Port;
	uint16 m_Pad;
	uint8 m_digest[20];
};

enum
{
	GnutellaPing = 0x00,
	GnutellaPong = 0x01,
	GnutellaBye = 0x02,
	GnutellaPush = 0x40,
	GnutellaQuery = 0x80,
	GnutellaQueryHit = 0x81,
};

#pragma pack(push,1)

struct GnutellaHeader
{
	GUID Guid;
	uint8 PayloadType;
	uint8 TTL;	// Time To Live
	uint8 Hops;
	DWORD PayloadLength;
	//BYTE PayloadData[0];
};

#pragma pack(pop)

class LP2PEXT CGnutellaSearch : public IQuery
{
public:
	CGnutellaSearch()
	{
//		m_pSocket = NULL;
		m_pSearchHitHandler = NULL;
	}

	void Search(StringIn criteria);
	void QueryHit(const GnutellaQueryHitMessage* queryhit);

	virtual void More();

	ISearchHitHandler* m_pSearchHitHandler;

	//CGnutellaSocket* m_pSocket;
	GnutellaNetwork* m_pComm;

	GUID m_queryGuid;

//	TreeControl* m_treeview;
//	TextString* m_nhitsElement;

//	std::vector<int> m_results;	// TODO
};

//typedef std::map<std::wstring, Object*> tyusermap;

class SearchHit;

class LP2PEXT GnutellaNetwork : public Object,
	public INetwork,
	public MSWindows::WindowImpl//<GnutellaNetwork>
{
public:
	GnutellaNetwork(INetworkClient* pclient)
	{
		ASSERT(0);
#if 0
		m_client = pclient;

	//	RECT rect;
	//	SetRectEmpty(&rect);
		Create(NULL, LDraw::Rect(), NULL, WS_POPUP);

		m_naddr = 0;

		m_NetworkInfo.NumberOfClients = 0;
		m_NetworkInfo.NumberOfSharedFiles = 0;
		m_NetworkInfo.NumberOfKilobytesShared = 0;
#endif
	}

	void OnIdle();

	virtual bool ProcessWindowMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ )
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

	void AddServer(DWORD server, uint16 port);
	void AddServers(StringIn servers);

	void ProcessHeaders(CGnutellaSocket* node);

	int ConnectP2P(DWORD, int port);

	virtual void Connect();
	virtual IQuery* Search(StringIn criteria, ISearchHitHandler* pSearchHitHandler);
	virtual IFileDownload* Download(int64 FileSize, const uint8 sha1digest[20], IDownloadHandler* handler, System::IO::ByteStreamWriter* stream);

	DWORD OnP2PThread();

	static DWORD WINAPI OnP2PThreadFunc(LPVOID lpdata)
	{
		return ((GnutellaNetwork*)lpdata)->OnP2PThread();
	}

public:

	NETWORKINFO m_NetworkInfo;

	INetworkClient* m_client;

	int m_naddr;
	Array<Host*> m_servers;
	Array<CGnutellaSocket*> m_connections;
	Array<CGnutellaSearch*> m_searchList;

	Array<SearchHit*> m_queryhits;
};

}

#endif //__GNUTELLANETWORK_H_
