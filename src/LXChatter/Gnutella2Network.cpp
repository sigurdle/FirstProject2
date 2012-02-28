#include "stdafx.h"
#include "LXChatter.h"
#include "LXChatter2.h"
#include "Gnutella2Network.h"
/*
#include <sstream>
#include <algorithm>
#include <time.h>
*/

#include "../LXUI/http.h"
#include "../LFC/ZLIBDecoder.h"

#include "../LXUI/Socket.h"
//#pragma comment(lib, "ws2_32.lib")	// TODO, should not be necessary

namespace System
{

class UDPListener;

char* ParseHost(const char* addr, std::string& server, uint16& port)
{
	char strserver[512];
	strcpy(strserver, addr);

	char* strport = strchr(strserver, ':');
	if (strport)
	{
		*strport = 0;
		strport++;

		server = strserver;

		char* p;
		port = strtol(strport, &p, 10);
		return p;
	}
	else
	{
		port = 0;
	}

	return NULL;
}

char* ParseHost(const char* addr, DWORD& IPAddress, WORD& port)
{
	std::string strserver;
	char* p = ParseHost(addr, strserver, port);
	IPAddress = ntohl(inet_addr(strserver.c_str()));
	return p;
}

class PacketHeader
{
public:
	PacketHeader()
	{
		length = 0;
	}

	uint8 nTypeLen;
	bool bBigEndian;
	bool bIsCompound;
	ULONG length;
};

class PacketPart
{
public:
	uint8 nPart;
	uint8* data;
	ULONG length;
};

typedef map<uint16, PacketPart*> typart;

class PacketEntry
{
public:
	PacketEntry()
	{
		m_bDone = false;
	}

	uint16 m_nSequence;
	bool m_bDone;
	uint8 PartCount;

	typart m_parts;
};

typedef std::map<WORD, PacketEntry*> tyentry;

class G2Node
{
public:
	G2Node(Gnutella2Network* pNetwork)
	{
		m_pNetwork = pNetwork;

		m_tcpConnection = NULL;
		m_nSequence = 0;
		m_queryKey = 0;
		m_queryKeyValid = false;
		m_RetryAfter = 0;

		m_bandwidth[0] = 0;
		m_bandwidth[1] = 0;
	}

	ULONGLONG m_bandwidth[2];

	Gnutella2Network* m_pNetwork;

	G2TCPConnection* m_tcpConnection;

	std::list<G2Query*> m_searchQueue;

	bool m_queryKeyValid;
	DWORD m_queryKey;

	uint16 m_nSequence;

	tyentry m_packets;

	time_t m_TimeLastSeen;
	DWORD m_IPAddress;
	uint16 m_Port;

	time_t m_RetryAfter;

	int ConnectTCP();

	void ProcessPacket(Packet* packet, bool bTCP);

	void QueryAcknowledge(Packet* packet);
	void QueryKeyAnswer(Packet* packet);

	void SendSearch(G2Query* pSearch);

	void SendPacket(Packet* packet);
};

class UDPSocket : public AsyncSocket
{
public:
};

#pragma pack(push, 1)

struct GND_HEADER
{
	char szTag3[3];
	uint8 nFlags;
	uint16 nSequence;
	uint8 nPart;
	uint8 nCount;
};

#pragma pack(pop)

class UDPListener : public AsyncSocket
{
public:
	Gnutella2Network* m_pNetwork;

	virtual void OnRead();

	virtual void OnWrite()
	{
		MessageBeep(-1);
	}
};

class TCPListener : public AsyncSocket
{
public:
	void OnConnect(int nErrorCode)
	{
		if (nErrorCode == 0)
		{
		}
		MessageBeep(-1);
	}
};

class Packet
{
public:

	Packet()
	{
		nTypeLen = 0;
		m_type[0] = 0;

		m_payloadData = NULL;
		m_payloadLength = 0;
	}

	Packet(const char* type)
	{
		nTypeLen = strlen(type);
		ASSERT(nTypeLen >= 1 && nTypeLen <= 8);
		strcpy(m_type, type);

		m_payloadData = NULL;
		m_payloadLength = 0;
	}

	const char* get_Type() const
	{
		return m_type;
	}

	void AddChild(Packet* packet)
	{
		m_children.push_back(packet);
	}

	Packet* GetChildByType(const char* type) const
	{
		for (int i = 0; i < m_children.size(); i++)
		{
			Packet* child = m_children[i];
			if (!strcmp(child->m_type, type))
			{
				return child;
			}
		}

		return NULL;
	}

	inline uint8* get_payloadData() const
	{
		return m_payloadData;
	}

	inline ULONG get_payloadLength() const
	{
		return m_payloadLength;
	}

	ULONG Serialize(uint8* p);
	ULONG ReadPacket(uint8* p);
	void ReadPacketLoad(uint8* p, PacketHeader* hdr);

	CArray<Packet*, Packet*> m_children;

	uint8 nTypeLen;
	char m_type[9];

	uint8* m_payloadData;
	ULONG m_payloadLength;
};

class G2TCPConnection : public IConnection,
	public AsyncSocket
{
public:

	G2TCPConnection()
	{
		m_code = 0;

		m_state = 0;

		m_nbufbytes = 0;
	
//		m_bTryMore = false;

	}

	G2Node* m_node;

	std::string m_strHandshake;
//	std::vector<std::string> m_headers;
	HttpHeaders m_headers;

	virtual IPv4 get_Address() const
	{
		IPv4 v;
		v.IPAddress = m_peerIP;
		v.Port = m_peerPort;
		return v;
	}

	DWORD m_peerIP;
	uint16 m_peerPort;

	DWORD m_listenIP;
	uint16 m_listenIPPort;

	int m_state;

//	time_t m_timer0;

	Gnutella2Network* m_pNetwork;

	uint8 m_packetbuf[32768];
	int m_nbufbytes;

	sysstring m_name;

	virtual sysstring get_Name() const
	{
		return m_name;
	}

	std::string ReadLine()
	{
		std::string str;

		while (1)
		{
			char c;
			if (Read(&c, 1) != 1)
				break;
			if (c == '\r')
			{
				char c2;
				if (Read(&c2, 1) != 1)
					break;
				if (c2 == '\n')
				{
					break;
				}
				else
				{
					/*
					if (str.length() == 512)
						throw -1;
						*/
					str += c;

					/*
					if (str.length() == 512)
						throw -1;
						*/
					str += c2;
				}
			}
			else
			{
				/*
				if (str.length() == 4096)
					throw -1;
					*/
				str += c;
			}
		}

		TRACE("%s\n", str.c_str());
		return str;
	}

	int m_code;

	int ParseHandshake();

	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(/*int nErrorCode*/);
	virtual void OnWrite(/*int nErrorCode*/);
	virtual void OnRead(/*int nErrorCode*/);
};

void G2Node::QueryKeyAnswer(Packet* packet)
{
	Packet* pQueryKey = packet->GetChildByType("QK");
	if (pQueryKey)
	{
		if (pQueryKey->m_payloadLength < 4)
			throw -1;
		m_queryKeyValid = true;
		m_queryKey = *(DWORD*)pQueryKey->m_payloadData;

		// Send qeued searches

		while (!m_searchQueue.empty())
		{
			G2Query* pSearch = *m_searchQueue.begin();
			m_searchQueue.erase(m_searchQueue.begin());

			SendSearch(pSearch);
		}
	}
}

void G2Node::QueryAcknowledge(Packet* packet)
{
	if (packet->get_payloadLength() < 16)
		throw -1;

	const GUID& guid = *(const GUID*)packet->get_payloadData();

	time_t ts;

	Packet* pChildTS = packet->GetChildByType("TS");	// Time stamp
	if (pChildTS)
	{
		if (pChildTS->m_payloadLength >= 4)
			ts = *(long*)pChildTS->get_payloadData();
	}
	else
	{
		ts = time(NULL);
	}

	Packet* pChildRA = packet->GetChildByType("RA");	// Retry-After
	if (pChildRA)
	{
		if (pChildRA->get_payloadLength() >= 4)
		{
			time_t RetryAfter = *(long*)pChildRA->get_payloadData();

			m_RetryAfter = ts + RetryAfter;
		}
	}

	std::list<G2Query*>::const_iterator it;
	for (it = m_pNetwork->m_searchList.begin(); it != m_pNetwork->m_searchList.end(); it++)
	{
		G2Query* pSearch = *it;
		if (pSearch->get_ID() == guid)
		{
			pSearch->QueryAcknowledge(packet);
			break;
		}
	}
}

void G2Query::Init(ISearchHitHandler* pSearchHitHandler, const StringA& criteria)
{
	if (m_pSearchHitHandler) throw -1;

	m_pSearchHitHandler = pSearchHitHandler;
	m_criteria = criteria;
	CoCreateGuid(&m_queryGuid);
}

void G2Query::QueryAcknowledge(const Packet* packet)
{
	for (int i = 0; i < packet->m_children.size(); i++)
	{
		Packet* pChild = packet->m_children[i];
		if (!strcmp(pChild->m_type, "D"))	// Done hub
		{
			if (pChild->get_payloadLength() >= 8)
			{
				DWORD IPAddress = *(DWORD*)(pChild->get_payloadData());
				WORD Port = *(WORD*)(pChild->get_payloadData()+4);
				WORD LeafCount = *(WORD*)(pChild->get_payloadData()+6);

				G2Node* node = m_pNetwork->AddServer(IPAddress, Port);

				for (int i = 0; i < m_searchedNodes.size(); i++)
				{
					if (m_searchedNodes[i] == node)
						break;
				}

				if (i == m_searchedNodes.size())
					m_searchedNodes.push_back(node);
			}
		}
		else if (!strcmp(pChild->m_type, "S"))	// Search hub
		{
			if (pChild->get_payloadLength() >= 6)
			{
				DWORD IPAddress = *(DWORD*)(pChild->get_payloadData());
				WORD Port = *(WORD*)(pChild->get_payloadData()+4);
				if (pChild->get_payloadLength() >= 8)
				{
					DWORD TimeStamp = *(DWORD*)(pChild->get_payloadData()+6);
				}

				G2Node* node = m_pNetwork->AddServer(IPAddress, Port);

				for (int i = 0; i < m_unsearchedNodes.size(); i++)
				{
					if (m_unsearchedNodes[i] == node)
						break;
				}

				if (i == m_unsearchedNodes.size())
					m_unsearchedNodes.push_back(node);
			}
		}
	}
}

void G2Query::QueryHit(const Packet* packet)
{
	for (int i = 0; i < packet->m_children.size(); i++)
	{
		Packet* pChild = packet->m_children[i];
		if (!strcmp(pChild->m_type, "H"))
		{
			G2SearchHit* pHit = new G2SearchHit;

			for (int i = 0; i < pChild->m_children.size(); i++)
			{
				Packet* pURN = pChild->m_children[i];
				if (!strcmp(pURN->m_type, "URN"))
				{
					ULONG length = pURN->get_payloadLength();
					BYTE* payload = pURN->get_payloadData();

					if (length == 47 && !strcmp((char*)payload, "bp"))
					{
						memcpy(pHit->m_sha1, payload+3, 20);
					}
					else if (length == 53 && !strcmp((char*)payload, "bitprint"))
					{
						memcpy(pHit->m_sha1, payload+9, 20);
					}
					else if (length == 25 && !strcmp((char*)payload, "sha1"))
					{
						memcpy(pHit->m_sha1, payload+5, 20);
					}
				}
			}

			Packet* pChildSZ = pChild->GetChildByType("SZ");
			Packet* pChildDN = pChild->GetChildByType("DN");

			if (pChildSZ)
			{
				if (pChildSZ->m_payloadLength <= 8)
				{
					memcpy(&pHit->m_FileSize, pChildSZ->m_payloadData, pChildSZ->m_payloadLength);
				}

				if (pChildDN)
				{
					ULONG filenameOffset;
					if (pChildDN->get_payloadLength() >= 4 && *(DWORD*)pChildDN->get_payloadData() == 0x00000000)
						filenameOffset = 4;
					else
						filenameOffset = 0;

					int len = min(1023, pChildDN->get_payloadLength()-filenameOffset);

					char filename[1024];
					strncpy(filename, (char*)pChildDN->get_payloadData()+filenameOffset, len);
					filename[len] = 0;

					pHit->m_FileName = filename;

					if (filename[0] == 0)
					{
						MessageBeep(-1);
					}
				}
			}
			else
			{
				if (pChildDN)
				{
					if (pChildDN->m_payloadLength >= 4)
					{
						pHit->m_FileSize = *(DWORD*)pChildDN->m_payloadData;
					}

					int len = min(1023, pChildDN->m_payloadLength-4);

					char filename[1024];
					strncpy(filename, (char*)pChildDN->m_payloadData+4, len);
					filename[len] = 0;

					pHit->m_FileName = filename;

					if (filename[0] == 0)
					{
						MessageBeep(-1);
					}
				}
			}

			m_pSearchHitHandler->OnHit(pHit);
		}
	}
}

/////////////////////////////////////////////////////////////////
// G2TCPConnection

void G2TCPConnection::OnConnect(int nErrorCode)
{
	if (nErrorCode)
	{
		const char* str;
		switch (nErrorCode)
		{
		case WSAETIMEDOUT:
			str = "Connection timed out";
			break;

		case WSAECONNREFUSED:
			str = "Connection was refused";
			break;

		default:
			str = "Unknown";//TRACE("Connect error code %d\n", nErrorCode);
		}

		TRACE("%s - %d\n", str, nErrorCode);

		for (int i = 0; i < m_pNetwork->m_connections.size(); i++)
		{
			if (m_pNetwork->m_connections[i] == this)
			{
				m_pNetwork->m_connections.erase(m_pNetwork->m_connections.begin() + i);
				return;
			}
		}
		ASSERT(0);
	}

	{
		StringA name;
		UINT rPort;
		((AsyncSocket*)this)->GetPeerName(name, rPort);
		m_name = ConvertA2S(name);
	}

	PostMessage(m_pNetwork->m_hWnd, WM_USER+100, (LPARAM)(IConnection*)this, 0);
}

void G2TCPConnection::OnClose(/*int nErrorCode*/)
{
	TRACE("OnClose\n");

	for (int i = 0; i < m_pNetwork->m_connections.size(); i++)
	{
		if (m_pNetwork->m_connections[i] == this)
		{
			m_pNetwork->m_connections.erase(m_pNetwork->m_connections.begin() + i);
			PostMessage(m_pNetwork->m_hWnd, WM_USER+101, (LPARAM)(IConnection*)this, 0);
			return;
		}
	}
	ASSERT(0);
}

void G2TCPConnection::OnWrite(/*int nErrorCode*/)
{
	TRACE("OnWrite (%d)\n", m_state);

	if (m_state == 0)
	{
		// Handshake

		char hostname[256];
		gethostname(hostname, 256);
		hostent* host = gethostbyname(hostname);
		DWORD ip = *((DWORD*)host->h_addr_list[0]);
		std::string listenip = inet_ntoa(*(in_addr*)&ip);

		DWORD ip2 = htonl(m_peerIP);
		std::string peerIP = inet_ntoa(*(in_addr*)&ip2);

		std::stringstream initstr;
		initstr
			<< "GNUTELLA CONNECT/0.6\r\n"
			<< "User-Agent: LX 1.0.0.0\r\n"
			<< "X-Ultrapeer: False\r\n"
			<< "X-Ultrapeer-Needed: True\r\n"
		//	<< "X-Query-Routing: 0.1\r\n"
			<< "Accept: application/x-gnutella2\r\n"
		//	<< "Accept-Encoding: deflate\r\n"
			<< "Remote-IP:" << peerIP << "\r\n"
			<< "Listen-IP:" << listenip << ":" << 20000 << "\r\n"
		//	<< "Bye-Packet: 0.1\r\n"
			<< "\r\n";

		std::string str = initstr.str();
		/*
			"GNUTELLA CONNECT/0.6\r\n"
			"User-Agent: LX/1.0\r\n"
			"X-Ultrapeer: False\r\n"
			"X-Query-Routing: 0.1\r\n"
			"Accept: application/x-gnutella2\r\n"
			"Bye-Packet: 0.1\r\n"
			"\r\n";
			*/

	//char* str = "Gnutella2 CONNECT/0.4\n\n";

		int nWritten = Send(str.c_str(), str.length());
		if (nWritten != str.length())
		{
			//ASSERT(0);
		}
		if (nWritten == SOCKET_ERROR)
		{
			int nError = GetLastError();

			const char* str = NULL;
			switch (nError)
			{
			case WSAENETDOWN: str = "The Windows Sockets implementation detected that the network subsystem failed.";
				break;

			default:
				str = "Unknown";
			}

			TRACE("Socket Error: %s\n", str);
		}
	}
	else
	{
		//ASSERT(0);
		TRACE("OnWrite() in state=3 ???");
	}
	/*
	else if (m_state == 3)
	{
		char* str =
			"Gnutella2/0.6 200 OK\r\n"
			"\r\n";
	//	char* str = "Gnutella2 OK\n\n";
		int nWritten = Send(str, strlen(str));

		if (nWritten != strlen(str))
		{
			ASSERT(0);
		}
	}
	*/
}

int G2TCPConnection::ParseHandshake()
{
	const char* p = m_strHandshake.c_str();
	const char* pend = p+m_strHandshake.length();

	if (!strncmp(p, "GNUTELLA/0.6", 12))
	{
		p += 12;
		p++;
		long code = strtol(p, (char**)&p, 10);
		p++;

		std::string codemsg;
		while (p < pend)
		{
			if (p[0] == '\r' && p[1] == '\n')
			{
				break;
			}

			codemsg += *p;
			p++;
		}

		if (*p++ != '\r') ASSERT(0);
		if (*p++ != '\n') ASSERT(0);

	//	HttpHeaders headers;
		m_headers.AddHeaders(p);

		/*
		while (p < pend)
		{
			std::string header;
			while (p < pend)
			{
				if (p[0] == '\r' && p[1] == '\n')
				{
					break;
				}

				header += *p;
				p++;
			}

			if (*p++ != '\r') ASSERT(0);
			if (*p++ != '\n') ASSERT(0);

			m_headers.push_back(header);
		}
		ASSERT(*p == 0);
		*/

		return code;
	}
	else
	{
		ASSERT(0);
		return 0;
	}
}

void G2TCPConnection::OnRead(/*int nErrorCode*/)
{
//	TRACE("OnRead\n");
	/*
	if (nErrorCode)
	{
		ASSERT(0);
		return;
	}
	*/

	if (m_state == 0 || m_state == 1)
	{
		/*
		time_t timer1;
		time(&timer1);

		double diff = difftime(timer1, m_timer0);

		m_timer0 = timer1;

		ATLTRACE("", diff);
		*/

		ULONG n;
		ioctlsocket(m_socket, FIONREAD, &n);

		char buf[256+1];
		while (n)
		{
			int len = 256;
			if (len > n)
				len = n;

			int nread = Receive(buf, len);
			m_node->m_bandwidth[0] += nread;
			//if (nread == SOCKET_ERROR)
			if (nread < len)
			{
				m_state = -1;
				Close();
				return;
			}

			n -= nread;

			buf[nread] = 0;
			m_strHandshake += buf;
		}

		if (m_strHandshake.length() > 4096)
		{
			// Handshake overflow
			ASSERT(0);
			m_state = -1;
			Close();
			return;//break;
		}

		if (m_state == 0)
		{
			if (m_strHandshake.length() >= 12)
			{
				if (strncmp(m_strHandshake.c_str(), "GNUTELLA/0.6", 12))
				{
					// Not a Gnutella2 peer (disconnect)
					m_state = -1;
					Close();
					return;//break;
				}

				m_state = 1;	// Now we know it's a Gnutella2 peer (keep receiving handshake)
			}
		}

		if (m_state == 1)
		{
			if (strstr(m_strHandshake.c_str(), "\r\n\r\n"))
			{
				m_state = 2;	// Have read entire handshake string
			}
		}

		if (m_state == 2)
		{
			m_code = ParseHandshake();

			TRACE("%s", m_strHandshake.c_str());

			m_pNetwork->ProcessHeaders(this);

			if (m_code == 200)	// OK
			{
				m_state = 3;

				StringA listenIP;
				m_headers.GetHeaderValue("Listen-IP", listenIP);
				ParseHost(listenIP.c_str(), m_listenIP, m_listenIPPort);
				ASSERT(m_listenIPPort == m_node->m_Port);

				char* str =
					"GNUTELLA/0.6 200 OK\r\n"
					"Content-Type: application/x-gnutella2\r\n"
				//	"Content-Encoding: deflate\r\n"
					"X-Ultrapeer: False\r\n"
					"\r\n";
			//	char* str = "Gnutella2 OK\n\n";
				int nWritten = Send(str, strlen(str));

				if (nWritten != strlen(str))
				{
					ASSERT(0);
				}

				{
					Packet* lni = new Packet("LNI");
					{
						char hostname[256];
						gethostname(hostname, 256);
						hostent* host = gethostbyname(hostname);
						DWORD ip = *((DWORD*)host->h_addr_list[0]);

						Packet* na = new Packet("NA");
						na->m_payloadLength = 6;
						na->m_payloadData = new BYTE[6];
						*(DWORD*)(na->m_payloadData) = ip;
						*(WORD*)(na->m_payloadData+4) = 20000;
						lni->AddChild(na);
					}
					{
						Packet* gu = new Packet("GU");
						gu->m_payloadLength = 16;
						gu->m_payloadData = new BYTE[16];
						*(GUID*)(gu->m_payloadData) = m_pNetwork->m_guid;
						lni->AddChild(gu);
					}

					BYTE* p = new BYTE[65536];
					ULONG length = lni->Serialize(p);

					int n = Send(p, length);

					delete p;
				}

				/*
				{
					Packet* packet = new Packet("PI");
					BYTE* p = new BYTE[65536];
					ULONG length = packet->Serialize(p);

					{
						Packet* p2 = new Packet;
						ULONG l2 = p2->ReadPacket(p);
						ASSERT(l2 = length);
					}


					int n = Send(p, length);
					ASSERT(n == length);
					TRACE("Sent Ping\n");

					delete p;
				}
				*/
			}
			else
			{
				Close();
			}
		}
	}
	else if (m_state == 3)
	{
		int nread = Receive(m_packetbuf+m_nbufbytes, 32768-m_nbufbytes);
		if (nread == 0)	// Connection closed
		{
			m_state = -1;
			Close();
			return;
		}

		m_node->m_bandwidth[0] += nread;

		if (nread == -1)
		{
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)
				return;
			m_state = -1;
			Close();
			return;
		}

		int nbufbytes = m_nbufbytes + nread;

		// Process all complete packets
		bool bContinue;

		int offset = 0;
		int bytesleft;
		do
		{
			bytesleft = nbufbytes - offset;

			if (bytesleft < 2)
			{
				// Incomplete packet
				bContinue = false;
			}
			else
			{
				BYTE* p = (BYTE*)(m_packetbuf+offset);
				BYTE nInput = *p++;

				if (nInput == 0)
					return;

				PacketHeader hdr;

				BYTE nLenLen = (nInput >> 6);
				hdr.nTypeLen = ((nInput>>3) & 0x07) + 1;
				BYTE nFlags = (nInput & 0x07);

				hdr.bBigEndian = (nFlags>>1) & 1;
				hdr.bIsCompound = (nFlags>>2) & 1;

			//	ASSERT(!bBigEndian);

				if (bytesleft < (1 + nLenLen))
				{
					// Incomplete packet
					bContinue = false;
				}
				else
				{
					hdr.length = 0;
					if (nLenLen > 0)
					{
						hdr.length = *p++;

						if (nLenLen > 1)
						{
							hdr.length |= (*p++)<<8;

							if (nLenLen > 2)
							{
								hdr.length |= (*p++)<<16;
							}
						}
					}

					ULONG nCompletePacketLen = 1 + (nLenLen) + (hdr.nTypeLen) + (hdr.length);

				//	TRACE("packet length: %d\n", nCompletePacketLen);

					if (bytesleft < nCompletePacketLen)
					{
						// Incomplete packet
						bContinue = false;
					}
					else
					{
						if (hdr.bBigEndian)
						{
							MessageBeep(-1);
						}

						Packet* packet = new Packet;

						try
						{
							packet->ReadPacketLoad(p, &hdr);

							m_node->ProcessPacket(packet, true);
						}
						catch(int)
						{
						}

						delete packet;

						offset += nCompletePacketLen;
					//	nbufbytes = 0;

						bContinue = true;
					}
				}
			}
		}
		while (bContinue);

		// Move the leftover bytes to the beginning of the buffer
		if (bytesleft)
		{
			memmove(m_packetbuf, m_packetbuf+offset, bytesleft);
		}
		m_nbufbytes = bytesleft;

		/*
		Gnutella2Header hdr;
		int nread = Receive(&hdr, sizeof(hdr));
		if (nread != sizeof(hdr))
		{
			ASSERT(0);
		}

		if (hdr.PayloadLength)
		{
			char* buf = new char[hdr.PayloadLength];
			if (buf)
			{
				int ntotalread = 0;
				while (ntotalread < hdr.PayloadLength)
				{
					int nread = Receive(buf, hdr.PayloadLength);
					if (nread != hdr.PayloadLength)
					{
						ASSERT(0);
					}
				}


				delete [] buf;
			}
		}
		*/
	}
}

void Packet::ReadPacketLoad(BYTE* p, PacketHeader* hdr)
{
	nTypeLen = hdr->nTypeLen;
	memcpy(m_type, p, nTypeLen);
	m_type[nTypeLen] = 0;
	p += nTypeLen;

	ULONG offset = 0;

	if (hdr->bIsCompound)
	{
		while (offset < hdr->length)
		{
			if (*p)
			{
				Packet* subpacket = new Packet;
				ULONG childlength = subpacket->ReadPacket(p);
				p += childlength;
				offset += childlength;
				AddChild(subpacket);
			}
			else
			{
				p++;
				offset++;
				break;
			}
		}
	}

	ASSERT(hdr->length >= offset);

	m_payloadData = p;
	m_payloadLength = hdr->length - offset;
}

ULONG Packet::ReadPacket(BYTE* p)
{
	BYTE nInput = *p++;
	if ( nInput == 0 ) return 1;

	Packet* packet = new Packet;
	PacketHeader hdr;

	BYTE nLenLen = (nInput >> 6) & 0x03;
	hdr.nTypeLen = ((nInput>>3) & 0x07) + 1;
	BYTE nFlags = ( nInput & 0x07 );

	hdr.bBigEndian = (nFlags>>1) & 1;
	hdr.bIsCompound = (nFlags>>2) & 1;

	if (hdr.bBigEndian )
		throw -1;

	hdr.length = 0;
	if (nLenLen > 0)
	{
		hdr.length = *p++;

		if (nLenLen > 1)
		{
			hdr.length |= (*p++)<<8;

			if (nLenLen > 2)
			{
				hdr.length |= (*p++)<<16;
			}
		}
	}

	if (hdr.length > 64000)
	{
		MessageBeep(-1);
	}

	ULONG nCompletePacketLen = 1 + nLenLen + hdr.nTypeLen + hdr.length;

	ReadPacketLoad(p, &hdr);

	return nCompletePacketLen;
}

ULONG Packet::Serialize(BYTE* p0)
{
	BYTE* p = p0;

	BYTE Control = 0;
	if (m_children.size())
	{
		Control |= 4;	// bIsCompound
	}
	Control |= ((nTypeLen-1)<<3);
	p++;

	// We insert Length here later (by moving memory)
//	p += 2;

	memcpy(p, m_type, nTypeLen);
	p += nTypeLen;

	ULONG length = 0;

	for (int i = 0; i < m_children.size(); i++)
	{
		Packet* subpacket = m_children[i];

		ULONG sublength = subpacket->Serialize(p);
		p += sublength;
		length += sublength;
	}

	if (m_payloadLength)
	{
		if (m_children.size())
		{
			*p++ = 0;	// End children
			length++;
		}

		memcpy(p, m_payloadData, m_payloadLength);
		p += m_payloadLength;
		length += m_payloadLength;
	}

	BYTE nbytes;

	// We only use a 0 length when the control byte isn't zero
	if (Control != 0 && length == 0)
		nbytes = 0;
	else if (length < 256)
		nbytes = 1;
	else if (length < 65536)
		nbytes = 2;
	else
		nbytes = 3;

	Control |= nbytes<<6;
	*p0 = Control;

//	*(WORD*)(p0+1) = length;

	if (nbytes)
	{
		memmove(p0+1+nbytes, p0+1, length+nTypeLen);
		memcpy(p0+1, &length, nbytes);
		p += nbytes;
	}

	return p - p0;
}

void G2Node::ProcessPacket(Packet* packet, bool bTCP)
{
	if (!strcmp(packet->m_type, "PI"))	// PING
	{
		TRACE("Ping..");

		Packet* udp = packet->GetChildByType("UDP");
		if (udp == NULL)
		{
		//	TRACE("Didn't contain any UDP child\n");
		//	return;
		}
		else if (udp->get_payloadLength() != 6)
		{
			TRACE("Payload Length != 6\n");
			return;
		}

		Packet* relay = packet->GetChildByType("RELAY");
		if (relay)
		{
			// Respond with a pong to the original sender via UDP

			DWORD IPAddress = *(DWORD*)(udp->get_payloadData());
			WORD Port = *(WORD*)(udp->get_payloadData()+4);

		//	UDPSocket* pSocket = new UDPSocket;
		//	pSocket->Create(SOCK_DGRAM, IPPROTO_UDP);

		//	if (pSocket->Connect(IPAddress, Port))
			{
				Packet* pong = new Packet("PO");
				{
					pong->AddChild(new Packet("RELAY"));
				}

				if (udp)
				{
#if 0
					BYTE* p = new BYTE[256];
					GND_HEADER* gnd = (GND_HEADER*)p;
					gnd->szTag3[0] = 'G';
					gnd->szTag3[1] = 'N';
					gnd->szTag3[2] = 'D';
					gnd->nFlags = 0;
					gnd->nSequence = ++m_nSequence;
					gnd->nCount = 1;
					gnd->nPart = 1;

					ULONG length = pong->Serialize(p+8);

					sockaddr_in sa;
					sa.sin_family = AF_INET;
					sa.sin_port = htons(Port/*m_listenIPPort*/);
					sa.sin_addr.s_addr = /*htonl*/(IPAddress/*m_listenIP*/);

					int nSent = sendto(/*m_pNetwork->m_udpListener->*/m_socket, (const char*)p, length+8, 0, (SOCKADDR*)&sa, sizeof(sa));
					if (nSent != -1)
					{
						//MessageBeep(-1);
					}
					else
					{
						int err = WSAGetLastError();
						TRACE("sendto() returned %d\n", err);
					}
					delete p;
#endif
				}
				else
				{
					BYTE* p = new BYTE[256];
					ULONG length = pong->Serialize(p);
					int nSent = m_tcpConnection->Send(p, length);
					if (nSent != -1)
					{
						//MessageBeep(-1);
					}
					else
					{
						int err = WSAGetLastError();
						TRACE("sendto() returned %d\n", err);
					}
					delete p;
				}

				/*
				int nSent = pSocket->Send(p, 8+length);
				if (nSent == -1)
				{
					int err = WSAGetLastError();
				}
				*/
			}

		//	pSocket->Close();
		//	delete pSocket;
		}
		else
		{
			// add a relay and forward to all neighbours
			Packet* relay = new Packet("RELAY");
			packet->AddChild(relay);

			for (int i = 0; i < m_pNetwork->m_nodes.size(); i++)
			{
				G2Node* node = m_pNetwork->m_nodes[i];

				if (node != this)
				{
					node->SendPacket(packet);
#if 0
					BYTE* p = new BYTE[256];
					GND_HEADER* gnd = (GND_HEADER*)p;
					gnd->szTag3[0] = 'G';
					gnd->szTag3[1] = 'N';
					gnd->szTag3[2] = 'D';
					gnd->nFlags = 0;
					gnd->nSequence = ++m_nSequence;
					gnd->nCount = 1;
					gnd->nPart = 1;

					ULONG length = packet->Serialize(p+8);

					sockaddr_in sa;
					sa.sin_family = AF_INET;
					sa.sin_addr.s_addr = htonl(node->m_IPAddress);
					sa.sin_port = htons(node->m_Port);

					int nSent = sendto(m_pNetwork->m_udpListener->m_socket, (const char*)p, length+8, 0, (SOCKADDR*)&sa, sizeof(sa));
					if (nSent != -1)
					{
						//MessageBeep(-1);
					}
					else
					{
						int err = WSAGetLastError();
						TRACE("sendto() returned %d\n", err);
					}
					/*
					int nSent = pN->Send(p, length+8);
					if (nSent != -1)
					{
						MessageBeep(-1);
					}
					else
					{
						int err = WSAGetLastError();
						TRACE("sendto() returned %d\n", err);
					}
*/
					delete p;
#endif
				}
			}
		}
		TRACE("\n");
	}
	else if (!strcmp(packet->m_type, "UPROC"))	// USER PROFILE CHALLENGE
	{
		TRACE("User Profile Challenge\n");
		// Respond with a user profile (if available)
	}
	else if (!strcmp(packet->m_type, "LNI"))	// LOCAL NODE INFORMATION
	{
		TRACE("Local Node Information\n");
		// Store for later
	}
	else if (!strcmp(packet->m_type, "QKA"))	// QUERY KEY ANSWER
	{
		TRACE("Query Key Answer\n");

		QueryKeyAnswer(packet);

	}
	else if (!strcmp(packet->m_type, "Q2"))	// QUERY
	{
		if (packet->get_payloadLength() != 16)
			throw -1;
		GUID guid = *(GUID*)packet->get_payloadData();

		Packet* udp = packet->GetChildByType("UDP");
		if (udp)
		{
			if (udp->get_payloadLength() < 10)
				throw -1;
			
			DWORD IPAddress = *(DWORD*)(udp->get_payloadData());
			WORD Port = *(WORD*)(udp->get_payloadData()+4);
			DWORD QueryKey = *(DWORD*)(udp->get_payloadData()+6);
		}
	}
	else if (!strcmp(packet->m_type, "QA"))	// QUERY ACKNOWLEDGEMENT
	{
		TRACE("Query Acknowledgement\n");

		QueryAcknowledge(packet);
	}
	else if (!strcmp(packet->m_type, "QH2"))	// QUERY HIT
	{
		TRACE("Query Hit\n");
		if (packet->m_payloadLength < 17)
			throw -1;

		BYTE HopCount = *packet->m_payloadData;
		GUID guid;
		memcpy(&guid, packet->m_payloadData+1, 16);

		std::list<G2Query*>::const_iterator it;
		for (it = m_pNetwork->m_searchList.begin(); it != m_pNetwork->m_searchList.end(); it++)
		{
			G2Query* pSearch = *it;
			if (pSearch->get_ID() == guid)
			{
				pSearch->QueryHit(packet);
				break;
			}
		}
	}
	else
		TRACE("Unknown packet: %s\n", packet->m_type);
#if 0
	switch (hdr->PayloadType)
	{
	case Gnutella2Ping:
		{
		}
		break;
		
	case Gnutella2Pong:
		{
		/*
		if (hdr->PayloadLength < sizeof(Gnutella2PongMessage))
		{
		ASSERT(0);
		}
			*/
			
			Gnutella2PongMessage* pong = (Gnutella2PongMessage*)hdr;
			
			NETWORKINFO* info = new NETWORKINFO;
			info->NumberOfSharedFiles = pong->NumberOfSharedFiles;
			info->NumberOfKilobytesShared = pong->NumberOfKilobytesShared;
			
			PostMessage(m_pComm->m_hWnd, WM_USER+103, (WPARAM)info, 0);
		}
		break;
		
	case Gnutella2Query:
		{
			if (hdr->PayloadLength >= 3)
			{
				char* buf = (char*)(hdr+1);
				WORD minimumSpeed = *(WORD*)buf;
				int n = 2;
				
				std::string searchCriteria;
				
				char* p = buf+2;
				while (*p && n < hdr->PayloadLength)
				{
					searchCriteria += *p;
					p++;
					n++;
				}
			}
		}
		break;
		
	case Gnutella2QueryHit:
		{
		/*
		if (hdr.PayloadLength < sizeof(Gnutella2QueryHitMessage))
		{
		ASSERT(0);
		}
			*/
			
			Gnutella2QueryHitMessage* queryhit = (Gnutella2QueryHitMessage*)hdr;
			
			
			for (int i = 0; i < m_pComm->m_searchList.size(); i++)
			{
				if (queryhit->hdr.Guid == m_pComm->m_searchList[i]->m_queryGuid)
				{
					m_pComm->m_searchList[i]->QueryHit(queryhit);
				}
			}
		}
		break;
		
	default:
		{
			MessageBeep(-1);
		}
		break;
	}
#endif
}

G2Node* Gnutella2Network::AddServer(DWORD server, WORD port)
{
	// Add server/port if it doesn't already exist
	for (int i = 0; i < m_nodes.size(); i++)
	{
		G2Node* node = m_nodes[i];
		if (node->m_IPAddress == server && node->m_Port == port)
		{
			return node;
		}
	}
	G2Node* node = new G2Node(this);
	node->m_TimeLastSeen = time(NULL);
	node->m_IPAddress = server;
	node->m_Port = port;
	m_nodes.push_back(node);

	return node;
}

void Gnutella2Network::AddServers(const StringA& servers)
{
	const char* p = servers.c_str();
	const char* pend = p+servers.length();

	while (isspace(*p)) p++;

	while (p < pend)
	{
		std::string addr;

		while (p < pend)
		{
			if (*p == ',')
			{
				break;
			}

			addr += *p;
			p++;
		}

		if (p < pend)
		{

			if (*p != ',') ASSERT(0);
			p++;
		}

		DWORD server;
		WORD port;
		ParseHost(addr.c_str(), server, port);

		AddServer(server, port);
	}
}

void Gnutella2Network::ProcessHeaders(G2TCPConnection* node)
{
	StringA XTryUltraPeers;
	if (node->m_headers.GetHeaderValue("X-Try-Ultrapeers", XTryUltraPeers))
	{
		AddServers(XTryUltraPeers);
	}

	StringA XTry;
	if (node->m_headers.GetHeaderValue("X-Try", XTry))
	{
		AddServers(XTry);
	}

	/*
	for (int i = 0; i < node->m_headers.size(); i++)
	{
		int len = 0;

		if (!strncmp(node->m_headers[i].c_str(), "X-Try:", 6))
		{
			len = 6;
		}
		else if (!strncmp(node->m_headers[i].c_str(), "X-Try-Ultrapeers:", 17))
		{
			len = 17;
		}

		if (len > 0)
		{

			break;
		}
	}
	*/
}

int G2Node::ConnectTCP()
{
	G2TCPConnection* tcp = new G2TCPConnection;
	tcp->m_pNetwork = m_pNetwork;
	tcp->m_node = this;
//	tcp->m_peerIP = server;
//	tcp->m_peerPort = port;

	if (!tcp->Create())
	{
		return 0;
	}

	m_tcpConnection = tcp;

	m_pNetwork->m_connections.push_back(tcp);
	if (tcp->Connect(m_IPAddress, m_Port))
	{
		return 0;
	}

	return 1;
}

class FileDownload;

class HTTPSocket : public AsyncSocket
{
public:
	HTTPSocket(FileDownload* pFileDownload)
	{
		m_pFileDownload = pFileDownload;
		m_state = 0;
		m_startpos = 0;
	}

	FileDownload* m_pFileDownload;

	//SearchHit* m_queryhitdata;
	DWORD m_startpos;

	int m_state;

	StringA m_server;

	void OnConnect(int nErrorCode);
	void OnRead();

	StringA ReadLine()
	{
		StringA str;

		while (1)
		{
			char c;
			Read(&c, 1);
			if (c == '\r')
			{
				char c2;
				Read(&c2, 1);
				if (c2 == '\n')
				{
					break;
				}
				else
				{
				//	if (str.length() == 512)
				//		throw -1;
					str += c;

				//	if (str.length() == 512)
				//		throw -1;
					str += c2;
				}
			}
			else
			{
			//	if (str.length() == 512)
			//		throw -1;
				str += c;
			}
		}

	//	TRACE("%s\n", str.c_str());
		return str;
	}
};


/*	struct greater : binary_function<_Ty, _Ty, bool> {
	bool operator()(const _Ty& _X, const _Ty& _Y) const
		{return (_X > _Y); }
	};
*/

/*
struct greaterSpeed : public std::greater<const SearchHit*&, const SearchHit*&, bool>
{
	bool operator()(const SearchHit*& _X, const SearchHit*& _Y) const
	{
		return _X->m_Speed > _Y->m_Speed;
	}
};
*/

#if 0

class FileDownload :
//	public MSWindows::WindowImpl<Gnutella2Network>
	public IFileDownload
{
public:
	FileDownload(Gnutella2Network* pComm)
	{
		m_pComm = pComm;
/*
		RECT rect;
		SetRectEmpty(&rect);
		Create(NULL, rect, NULL, WS_POPUP);
		*/
		m_hThread = INVALID_HANDLE_VALUE;
	}

	Gnutella2Network* m_pComm;

	HANDLE m_hThread;

	IDownloadHandler* m_handler;

//	std::list<SearchHit*> m_matches;
	std::vector<HTTPSocket*> m_sockets;

	ByteStreamWriter* m_stream;

	void OnIdle();

	DWORD OnDownloadThread();

	static DWORD WINAPI OnDownloadThreadFunc(LPVOID lpData)
	{
		return ((FileDownload*)lpData)->OnDownloadThread();
	}

	void Pause()
	{
	}

	void Resume()
	{
		std::list<SearchHit*>::iterator it = m_matches.begin();
		while (it != m_matches.end())
		{
			SearchHit* hit = *it++;

			HTTPSocket* pSocket = new HTTPSocket(this);
			pSocket->m_queryhitdata = hit;

			in_addr addr;
			addr.s_addr = pSocket->m_queryhitdata->m_IPAddress;
			pSocket->m_server = inet_ntoa(addr);

			pSocket->Create();
			pSocket->Connect(pSocket->m_server.c_str(), pSocket->m_queryhitdata->m_Port);

			break;
		}
	}

	void Cancel()
	{
	}
};

void HTTPSocket::OnConnect(int nErrorCode)
{
	if (nErrorCode != 0)
	{
		return;
	}

	std::stringstream request;
	request	<< "GET " << "/get/" << m_queryhitdata->m_FileIndex << '/' << m_queryhitdata->m_FileName << " HTTP/1.1\r\n"
				<< "Host: " << m_server << "\r\n"
				<< "Range: bytes=" << m_startpos << "-" << m_queryhitdata->m_FileSize-1 << "\r\n"
				<< "\r\n";

	std::string requeststr = request.str();
	int nsent = Write((void*)requeststr.c_str(), requeststr.length());

	m_state = 1;
}

void HTTPSocket::OnRead()
{
	if (m_state == 1)
	{
		std::string status = ReadLine();

		const char* p = status.c_str();
		while (*p)
		{
			if (*p == ' ')
				break;
			p++;
		}
		while (*p == ' ') p++;

		long code = strtol(p, (char**)&p, 10);

		if (code != 200)
		{
			m_state = -1;
			Close();
			return;
		}

		typedef std::map<std::string,std::string> tyheadermap;
		tyheadermap headerlines;
		std::string headers;
		while (1)
		{
			std::string line = ReadLine();
			if (!strcmp(line.c_str(), ""))
			{
				break;
			}

			std::string name;
			const char* p = line.c_str();
			while (*p)
			{
				if (*p == ':' || *p == ' ')
					break;
				name += *p;
				p++;
			}
			while (*p == ' ') p++;
			if (*p != ':')
				throw -1;
			p++;

			while (*p == ' ') p++;
			std::string value = p;

			headerlines.insert(tyheadermap::value_type(name, value));

			headers += line;
			headers += "\r\n";
		}

		TRACE("%s", headers.c_str());

		m_state = 2;
	}
	else
	{
		ULONG n;
		ioctlsocket(m_socket, FIONREAD, &n);

		char buf[512];
		while (n)
		{
			int len = 512;
			if (len > n)
				len = n;

			int nread = Receive(buf, len);

			m_pFileDownload->m_stream->Seek(m_startpos, STREAM_SEEK_SET);
			m_pFileDownload->m_stream->Write(buf, nread);
			m_startpos += nread;

			//PostMessage(m_pComm->m_hWnd, WM_USER+3, 

			//if (nread == SOCKET_ERROR)
			if (nread < len)
			{
				m_state = -1;
				Close();
				return;
			}

			n -= nread;

		//	m_strHandshake += buf;
		}
	}
}

void FileDownload::OnIdle()
{
}

DWORD FileDownload::OnDownloadThread()
{
	Resume();

	// Main thread message loop, TODO, eventually, I will have this in a a system class of its own (only more powerful than below)
	while (1)
	{
		MSG msg;
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			OnIdle();
		}

		if (GetMessage(&msg, NULL, 0, 0) <= 0)
			break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
#endif

IFileDownload* Gnutella2Network::Download(LONGLONG FileSize, const BYTE sha1digest[20], IDownloadHandler* handler, ByteStreamWriter* stream)
{
#if 0
	FileDownload* pFileDownload = new FileDownload(this);

	pFileDownload->m_handler = handler;
	pFileDownload->m_stream = stream;

	for (int i = 0; i < m_queryhits.size(); i++)
	{
		SearchHit* hit2 = m_queryhits[i];

		if ((FileSize == hit2->m_FileSize) &&
			memcmp(sha1digest, hit2->m_digest, 20) == 0)
		{
			pFileDownload->m_matches.push_back(hit2);

			handler->OnHit(hit2);
		}
	}

	/*
	greaterSpeed k;
//	bool h = k((SearchHit*)NULL, (SearchHit*)NULL);

	// Sort by speed
	matches.sort(k);
//	std::sort(matches.begin(), matches.end(), k);
*/
	//int count = pFileDownload->m_matches.size();

	DWORD threadId;
	pFileDownload->m_hThread = CreateThread(NULL, 0, FileDownload::OnDownloadThreadFunc, pFileDownload, 0, &threadId);

	return pFileDownload;
#endif
	return NULL;
}

void UDPListener::OnReceive(int nErrorCode)
{
	ULONG n;
	ioctlsocket(m_socket, FIONREAD, &n);

	BYTE* data = new BYTE[n];
	sockaddr_in addr;
	int len = sizeof(addr);
	int nRead = ReceiveFrom(data, n, (SOCKADDR*)&addr, &len);
	if (nRead == -1)
	{
		int err = WSAGetLastError();
		if (err == WSAEWOULDBLOCK)
			return;
		//Close();
		return;
	}

	DWORD ip = (addr.sin_addr.s_addr);
	WORD port = ntohs(addr.sin_port);

	G2Node* node = m_pNetwork->AddServer(ntohl(ip), port);

	node->m_bandwidth[0] += nRead;

#if 0
	for (int i = 0; i < m_pNetwork->m_nodes.size(); i++)
	{
		G2Node* node2 = m_pNetwork->m_nodes[i];

		if (node2->m_IPAddress == ntohl(ip)/* && pSocket2->m_peerPort == port*/)
		{
			TRACE("%s\n", inet_ntoa(addr.sin_addr));
			node = node2;
			break;
		}

		/*
		if (pSocket2->m_listenIP == ip)
		{
			pSocket = pSocket2;
			break;
		}
		*/
	}

	if (node == NULL)
	{
		// Node has not been seen before

		node = new G2Node(m_pNetwork);
		node->m_IPAddress = ntohl(ip);
		node->m_Port = port;
		m_pNetwork->m_nodes.push_back(node);
	}
#endif

	if (node)
	{
		node->m_TimeLastSeen = time(NULL);

		if (nRead >= sizeof(GND_HEADER))
		{
			GND_HEADER* gnd = (GND_HEADER*)data;

			if (gnd->szTag3[0] == 'G' &&
				gnd->szTag3[1] == 'N' &&
				gnd->szTag3[2] == 'D')
			{
				if (gnd->nCount == 0)
				{
					TRACE("UDP Acknowledge received\n");
					return;
				}

				PacketEntry* pPacketEntry;

				tyentry::iterator it = node->m_packets.find(gnd->nSequence);
				if (it == node->m_packets.end())
				{
					pPacketEntry = new PacketEntry;
					pPacketEntry->m_nSequence = gnd->nSequence;
					node->m_packets.insert(tyentry::value_type(gnd->nSequence, pPacketEntry));
				}
				else
				{
					pPacketEntry = (*it).second;
				}

				if (gnd->nFlags & 2)
				{
					// Acknowledge
					sockaddr_in sa;
					sa.sin_family = AF_INET;
					sa.sin_addr.s_addr = /*htonl*/(ip/*pSocket->m_listenIP*/);
					sa.sin_port = htons(port/*pSocket->m_listenIPPort*/);
					
					GND_HEADER ack;
					ack.szTag3[0] = 'G';
					ack.szTag3[1] = 'N';
					ack.szTag3[2] = 'D';
					ack.nFlags = 0;
					ack.nSequence = gnd->nSequence;
					ack.nPart = gnd->nPart;
					ack.nCount = 0;

					int UdpSent = sendto(m_socket, (const char*)&ack, sizeof(GND_HEADER), 0, (SOCKADDR*) &sa, sizeof(sa) );
				}

				/*
				if (gnd->nFlags & 1)	// ZLIB Compressed
				{
					ASSERT(0);
				}
				*/

				typart::iterator itpart = pPacketEntry->m_parts.find(gnd->nPart);
				if (itpart == pPacketEntry->m_parts.end())	// New part for this packet
				{
					PacketPart* pPart = new PacketPart;
					pPart->nPart = gnd->nPart;
					pPart->length = nRead;// - sizeof(gnd);
					pPart->data = data;//new BYTE[pPart->length];
					//int nRead = Receive(pPart->data, pPart->length);

					/*
					if (nRead > -1)
					{
						MessageBeep(-1);
					}
					*/

					pPacketEntry->m_parts.insert(typart::value_type(gnd->nPart, pPart));

					/*
					if (gnd->nCount > 1)
					{
						MessageBeep(-1);
					}
					*/

					if (pPacketEntry->m_parts.size() == gnd->nCount)
					{
						// Assemble fragments into one continuous buffer

						pPacketEntry->m_bDone = true;

						typart::const_iterator it;
						ULONG size = 0;
						for (it = pPacketEntry->m_parts.begin(); it != pPacketEntry->m_parts.end(); it++)
						{
							PacketPart* part = it->second;
							size += part->length-8;
						}

						BYTE* packetdata0 = new BYTE[size];
						ULONG offset = 0;

						for (it = pPacketEntry->m_parts.begin(); it != pPacketEntry->m_parts.end(); it++)
						{
							PacketPart* part = it->second;

							memcpy(packetdata0+offset, part->data+8, part->length-8);
							offset += part->length-8;
						}

						BYTE code;
						BYTE* packetdata;
						BYTE* p;
						PacketHeader hdr;

						if (gnd->nFlags & 1)	// ZLIB Compressed
						{
							try
							{
								ZLIBDecoder* zlibDecoder = new ZLIBDecoder(new MemoryByteStream(packetdata0, size));
								zlibDecoder->start();
								zlibDecoder->start_block();

								if (zlibDecoder->Read(&code, 1) != 1)
								{
									ASSERT(0);
								//	Close();
									return;
								}

								BYTE nLenLen = code>>6;
								hdr.nTypeLen = ((code>>3) & 0x07) + 1;

								zlibDecoder->Read(&hdr.length, nLenLen);

								ULONG len = hdr.nTypeLen + hdr.length;
								packetdata = new BYTE[len];

								if (zlibDecoder->Read(packetdata, len) != len)
								{
									ASSERT(0);
								//	Close();
									return;
								}

								delete packetdata0;
							}
							catch(int)
							{
								delete packetdata0;
								return;
							}

							p = packetdata;
						}
						else
						{
							packetdata = packetdata0;
							p = packetdata;

							code = *p++;
							BYTE nLenLen = code>>6;
							hdr.nTypeLen = ((code>>3) & 0x07) + 1;
							memcpy(&hdr.length, p, nLenLen);
							p += nLenLen;
						}

						BYTE nFlags = (code & 0x07);

						hdr.bBigEndian = (nFlags>>1) & 1;
						hdr.bIsCompound = (nFlags>>2) & 1;

						Packet* pPacket = new Packet;
						try
						{
							pPacket->ReadPacketLoad(p, &hdr);
						//	TRACE("packet length: %d\n", length);

							/*
							if (offset != length)
							{
								Close();
								return;
							}
							*/

							node->ProcessPacket(pPacket, false);
						}
						catch(int)
						{
						}

						delete pPacket;

						delete packetdata;
					}
				}
			}
		}
	}
	else
	{
		delete data;
	}
}

void G2Node::SendPacket(Packet* packet)
{
	BYTE* p = new BYTE[65536];
	GND_HEADER* gnd = (GND_HEADER*)p;
	gnd->szTag3[0] = 'G';
	gnd->szTag3[1] = 'N';
	gnd->szTag3[2] = 'D';
	gnd->nFlags = 2;	// Require acknowledge
	gnd->nSequence = ++m_nSequence;
	gnd->nCount = 1;
	gnd->nPart = 1;

	ULONG length = packet->Serialize(p+8);

	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(m_IPAddress);
	sa.sin_port = htons(m_Port);

	int nSent = sendto(m_pNetwork->m_udpListener->m_socket, (const char*)p, length+8, 0, (SOCKADDR*)&sa, sizeof(sa));
	if (nSent != -1)
	{
	//	MessageBeep(-1);
	}
	else
	{
		int err = WSAGetLastError();
		TRACE("sendto() returned %d\n", err);
	}

	delete p;
}

void G2Node::SendSearch(G2Query* pSearch)
{
	if (!m_queryKeyValid)
	{
		Packet* qkr = new Packet("QKR");	// Query Key Request
		{
			char hostname[256];
			gethostname(hostname, 256);
			hostent* host = gethostbyname(hostname);
			DWORD ip = *((DWORD*)host->h_addr_list[0]);

			Packet* rna = new Packet("RNA");	// Requesting Node Address 
			rna->m_payloadData = new BYTE[6];
			rna->m_payloadLength = 6;
			*(DWORD*)(rna->m_payloadData) = ip;
			*(WORD*)(rna->m_payloadData+4) = 20000;

			qkr->AddChild(rna);
		}
		SendPacket(qkr);

		// Queue the query so it can be sent when the query key arrives
		for (std::list<G2Query*>::const_iterator it = m_searchQueue.begin(); it != m_searchQueue.end(); it++)
		{
			if (*it == pSearch)
				return;
		}
		m_searchQueue.push_back(pSearch);
	}
	else
	{
		Packet* q2 = pSearch->MakeQueryPacket(m_queryKey);
		SendPacket(q2);
	}
}

void G2Query::More()
{
	time_t currentTime = time(NULL);

	for (int i = 0; i < m_unsearchedNodes.size(); i++)
	{
		G2Node* node = m_unsearchedNodes[i];

		if (currentTime > node->m_RetryAfter)
		{
			node->SendSearch(this);
		}
		else
		{
			MessageBeep(-1);
		}
	}
}

Packet* G2Query::MakeQueryPacket(DWORD queryKey) const
{
	Packet* q2 = new Packet("Q2");
	q2->m_payloadLength = 16;
	q2->m_payloadData = new BYTE[16];
	memcpy(q2->m_payloadData, &m_queryGuid, 16);

	{
		char hostname[256];
		gethostname(hostname, 256);
		hostent* host = gethostbyname(hostname);
		DWORD ip = *((DWORD*)host->h_addr_list[0]);

		Packet* udp = new Packet("UDP");
		udp->m_payloadData = new BYTE[10];
		udp->m_payloadLength = 10;
		*(DWORD*)(udp->m_payloadData) = ip;
		*(WORD*)(udp->m_payloadData+4) = 20000;
		*(DWORD*)(udp->m_payloadData+6) = queryKey;

		q2->AddChild(udp);
	}
	{
		Packet* dn = new Packet("DN");
		dn->m_payloadData = new BYTE[m_criteria.length()+1];
		strcpy((char*)dn->m_payloadData, m_criteria.c_str());
		dn->m_payloadLength = m_criteria.length()+1;

		q2->AddChild(dn);
	}

	return q2;
}

IQuery* Gnutella2Network::Search(const sysstring& wcriteria, ISearchHitHandler* pSearchHitHandler)
{
	G2Query* pSearch = NULL;

	StringA criteria = ConvertS2A(wcriteria);

	/*
	for (std::list<G2Query*>::const_iterator it = m_searchList.begin(); it != m_searchList.end(); it++)
	{
		G2Query* pSearch2 = *it;
		if (pSearch2->get_Criteria() == criteria)
		{
			pSearch = pSearch2;
			break;
		}
	}

  */
	//if (pSearch == NULL)
	{
		pSearch = new G2Query(this);
		pSearch->Init(pSearchHitHandler, criteria);

		m_searchList.push_back(pSearch);
	}

	time_t currentTime = time(NULL);

	for (int i = 0; i < m_nodes.size(); i++)
	{
		G2Node* node = m_nodes[i];

		if (currentTime > node->m_RetryAfter)
		{
			node->SendSearch(pSearch);
		}
	}

	return pSearch;
}

void Gnutella2Network::OnIdle()
{
	while (m_connections.size() < 16 && m_naddr < m_nodes.size())
	{
		G2Node* node = m_nodes[m_naddr];
		m_naddr++;

//		DWORD server = host->m_server;
//		int port = host->m_port;

		node->ConnectTCP();
	}
}

DWORD Gnutella2Network::OnP2PThread()
{
	TCPListener* m_tcpListener = new TCPListener;
	m_tcpListener->Create();
	m_tcpListener->Listen(20000);

	m_udpListener = new UDPListener;
	m_udpListener->m_pNetwork = this;
	m_udpListener->Create(SOCK_DGRAM, IPPROTO_UDP);
	m_udpListener->Bind(20000);

	// Main thread message loop, TODO, eventually, I will have this in a a system class of its own (only more powerful than below)
	while (1)
	{
		MSG msg;
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			OnIdle();
		}

		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

void Gnutella2Network::Connect()
{
	if (false)
	{
		std::string url = "http://glad04.no-ip.com/g2/bazooka.php?client=TESTBAZK031&net=gnutella2&get=1";

		HttpConnection* pConnection = new HttpConnection("glad04.no-ip.com");
		HttpRequest* pRequest = pConnection->OpenRequest("GET", url.c_str());
		pRequest->Send();

		StdStream stream(pRequest->GetContentStream());

		FILE* fp = fopen("C:/gwebcache.dat", "wb");

		while (1)
		{
			std::string line = stream.GetLine();
			if (line.length() == 0)
				break;

			const char* p = line.c_str();
			if (*p == 'h' || *p == 'H')
			{
				p++;

				if (*p != '|') throw -1;
				p++;
				std::string strserver;
				std::string strport;

				while (*p)
				{
					if (*p == ':')
						break;
					strserver += *p;
					p++;
				}
				if (*p != ':') throw -1;
				p++;

				while (*p)
				{
					if (*p == '|')
						break;
					strport += *p;
					p++;
				}

				DWORD IPAddress = inet_addr(strserver.c_str());
				char* p;
				WORD Port = (WORD)strtol(strport.c_str(), &p, 10);

				fwrite(&IPAddress, 1, 4, fp);
				fwrite(&Port, 1, 2, fp);
			}
			else if (*p == 'u' || *p == 'U')
			{
				break;
			}
			else
				break;
		}

		delete pConnection;

		fclose(fp);
	}

	{
		FILE* fp = fopen("C:/gwebcache.dat", "rb");
		while (!feof(fp))
		{
			DWORD IPAddress;
			WORD Port;
			fread(&IPAddress, 1, 4, fp);
			fread(&Port, 1, 2, fp);

			G2Node* node = new G2Node(this);
			node->m_IPAddress = ntohl(IPAddress);
			node->m_Port = Port;
			m_nodes.push_back(node);
		}
	}


//		m_servers.push_back(new Host("83.227.110.78", 6346));

	/*
	while (1)
	{
		int c = stream.GetChar();
		if (c == -1) break;

		fwrite(
	}
	*/

	/*
	m_servers.push_back(new Host("172.211.38.82", 6346));
	m_servers.push_back(new Host("172.183.177.144", 6346));
	m_servers.push_back(new Host("12.218.106.173:", 6346));
	*/

	/*
	m_servers.push_back(new Host("68.46.4.4", 6346));
	m_servers.push_back(new Host("68.232.1.229", 6346));
	m_servers.push_back(new Host("67.85.198.176", 6346));
	m_servers.push_back(new Host("24.166.109.116", 6346));
	m_servers.push_back(new Host("24.116.149.104", 6346));
	*/

	DWORD threadId;
	CreateThread(NULL, 0, OnP2PThreadFunc, this, 0, &threadId);
}

}
