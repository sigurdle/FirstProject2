#include "stdafx.h"
#include "LXChatter.h"
#include "LXChatter2.h"
#include "GnutellaNetwork.h"
//#include <sstream>
//#include <algorithm>

#include "../LXUI/http.h"

#include "../LXUI/Socket.h"
//#pragma comment(lib, "ws2_32.lib")	// TODO, should not be necessary

/////////////////////////////////////////////////////////////////////////////
// GnutellaNetwork

class CGnutellaSocket : public IConnection,
	public AsyncSocket
{
public:

	CGnutellaSocket()
	{
		m_code = 0;

		m_state = 0;

		m_nbufbytes = 0;
	
//		m_bTryMore = false;
	}

//	bool m_bTryMore;

	virtual IPv4 get_Address() const
	{
		return m_address;
	}

	IPv4 m_address;

	StringA m_strHandshake;
//	std::vector<std::string> m_headers;
	HttpHeaders m_headers;

	int m_state;

//	time_t m_timer0;

	GnutellaNetwork* m_pComm;

	uint8 m_packetbuf[32768];
	int m_nbufbytes;

	sysstring m_name;

	virtual sysstring get_Name() const
	{
		return m_name;
	}

	StringA ReadLine()
	{
		StringA str;

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

	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(/*int nErrorCode*/);
	virtual void OnWrite(/*int nErrorCode*/);
	int ParseHandshake();
	virtual void OnRead(/*int nErrorCode*/);

	/*
	int ConnectP2P(const char* server, int port, int levels, std::vector<CString>& visited)
	{
		if (Connect(server, port))
		{
		}
	}
	*/

	void ProcessPacket(GnutellaHeader* hdr);
};

#pragma pack(push,1)

struct GnutellaPongMessage
{
	GnutellaHeader hdr;

	uint16 PortNumber;	/* Port number. The port number on which the responding
            host can accept incoming connections. */

	DWORD IPAddress; /* The IP address of the responding host.
            Note: This field is in big-endian format.
				*/
	DWORD NumberOfSharedFiles;	/*The number of files that the
            servent with the given IP address and port is sharing
            on the network.*/
	DWORD NumberOfKilobytesShared;	/* The number of kilobytes
            of data that the servent with the given IP address and
            port is sharing on the network. */
	/*
    OPTIONAL GGEP extension block. (see Section 2.3)
	 */
};

struct GnutellaQueryHitMessage
{
	GnutellaHeader hdr;

	uint8 nHits;
	uint16 PortNumber;	/* Port number. The port number on which the responding
            host can accept incoming connections. */
	DWORD IPAddress; /* The IP address of the responding host.
            Note: This field is in big-endian format.
				*/
	DWORD Speed;
// ... Result Set

};

#pragma pack(pop)

#if 0
int send(SOCKET socket, const char* buf, long len)
{
	for (int i = 0; i < 3; i++)
	{
		fd_set ws,es;
		
		FD_ZERO(&ws);
		FD_ZERO(&es);

		FD_SET(socket, &ws);
		FD_SET(socket, &es);

		timeval tv;
		tv.tv_sec = 1;		// s
		tv.tv_usec = 0;	// ms
		int selRet = select(0/*ignored*/, NULL, &ws, &es, &tv); 

		if(selRet && FD_ISSET(socket, &ws))
		{
			return send(socket, buf, len, 0);
		}
		else if (selRet && FD_ISSET(socket, &es)) // error on the socket
		{
			return -1;
		}
	}

	return -1;
}
#endif

#if 0
int receive(SOCKET socket, char* buf, long len)
{
	for (int i = 0; i < 3; i++)
	{
		fd_set rs,es;
	
		FD_ZERO(&rs);
		FD_ZERO(&es);

		FD_SET(socket, &rs);
		FD_SET(socket, &es);

		timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;	// ms

		int selRet = select(0, &rs, 0, &es, &tv); 

		if(selRet && FD_ISSET(socket, &es)) // error
		{
			//state = ERRORSTATE;
			return -1;
		}

		if (selRet && FD_ISSET(socket, &rs))
		{
			return recv(socket, buf, len, 0);
		}
	}

	return -1;
}
#endif

/////////////////////////////////////////////////////////////////
// CGnutellaSocket

void CGnutellaSocket::OnConnect(int nErrorCode)
{
	TRACE("OnConnect %d\n", nErrorCode);

	if (nErrorCode)
	{
		for (int i = 0; i < m_pComm->m_connections.size(); i++)
		{
			if (m_pComm->m_connections[i] == this)
			{
				m_pComm->m_connections.RemoveAt(/*m_pComm->m_connections.begin() +*/ i);
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

	m_pComm->PostMessage(WM_USER+100, (LPARAM)(IConnection*)this, 0);
}

void CGnutellaSocket::OnClose(/*int nErrorCode*/)
{
	TRACE("OnClose\n");

	for (int i = 0; i < m_pComm->m_connections.size(); i++)
	{
		if (m_pComm->m_connections[i] == this)
		{
			m_pComm->m_connections.RemoveAt(/*m_pComm->m_connections.begin() +*/ i);
			m_pComm->PostMessage(WM_USER+101, (LPARAM)(IConnection*)this, 0);
			return;
		}
	}
	ASSERT(0);
}

void CGnutellaSocket::OnWrite(/*int nErrorCode*/)
{
	TRACE("OnWrite\n");

	if (m_state == 0)
	{
		// Handshake
		char* str =
			"GNUTELLA CONNECT/0.6\r\n"
			"User-Agent: LX/1.0\r\n"
			"X-Ultrapeer: False\r\n"
			"X-Query-Routing: 0.1\r\n"
			"Accept: application/x-gnutella2\r\n"
			"Bye-Packet: 0.1\r\n"
			"\r\n";

	//char* str = "GNUTELLA CONNECT/0.4\n\n";

		int nWritten = Send(str, strlen(str));
		if (nWritten != strlen(str))
		{
			//ASSERT(0);
		}
		if (nWritten == SOCKET_ERROR)
		{
#if 0	// TODO, have this
			int nError = GetLastError();

			const char* str = NULL;
			switch (nError)
			{
			case WSAENETDOWN: str = "The Windows Sockets implementation detected that the network subsystem failed.";
				break;

			default:
				str = "Unknown";
			}
#endif

			TRACE("Socket Error: %s\n", str);
		}
		//TRACE("%d", nWritten);
	}
	/*
	else if (m_state == 3)
	{
		char* str =
			"GNUTELLA/0.6 200 OK\r\n"
			"\r\n";
	//	char* str = "GNUTELLA OK\n\n";
		int nWritten = Send(str, strlen(str));

		if (nWritten != strlen(str))
		{
			ASSERT(0);
		}
	}
	*/
	else
	{
	//	ASSERT(0);
	}
}

int CGnutellaSocket::ParseHandshake()
{
	const char* p = m_strHandshake.c_str();
	const char* pend = p+m_strHandshake.length();

	if (!strncmp(p, "GNUTELLA/0.6", 12))
	{
		p += 12;
		p++;
		long code = strtol(p, (char**)&p, 10);
		p++;

		StringA codemsg;
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

void CGnutellaSocket::OnReceive(int nErrorCode)
{
	TRACE("OnRead\n");
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

		/*
		std::string line;
		while (1)
		{
			line = ReadLine();
			m_strHandshake += line + "\r\n";
			if (line.length() == 0)
				break;
		}
		*/

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
					// Not a gnutella peer (disconnect)
					m_state = -1;
					Close();
					return;//break;
				}

				m_state = 1;	// Now we know it's a gnutella peer (keep receiving handshake)
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
			int m_code = ParseHandshake();

			m_pComm->ProcessHeaders(this);

			if (m_code == 200)	// OK
			{
				m_state = 3;

				char* str =
					"GNUTELLA/0.6 200 OK\r\n"
					"\r\n";
			//	char* str = "GNUTELLA OK\n\n";
				int nWritten = Send(str, strlen(str));

				if (nWritten != strlen(str))
				{
					ASSERT(0);
				}

			//	PostMessage(m_pComm->m_hWnd, WM_USER+102, (LPARAM)(IConnection*)this, m_code);
			//	m_pComm->m_client->OnConnection(this);

				// Ping
				{
					GnutellaHeader ping;

					CoCreateGuid(&ping.Guid);	// ???
					ping.PayloadType = GnutellaPing;
					ping.TTL = 7;
					ping.Hops = 0;
					ping.PayloadLength = 0;

					int wrote = Send((const char*)&ping, sizeof(ping));
				}

			}
			else
			{
				Close();


				/*
				char* str =
					"GNUTELLA/0.6 503 FAIL\r\n"
					"\r\n";
				int nWritten = Send(str, strlen(str));

				if (nWritten != strlen(str))
				{
					ASSERT(0);
				}
*/
			}
		}
	}
	else if (m_state == 3)
	{
		int nread = Receive(m_packetbuf+m_nbufbytes, 32768-m_nbufbytes);
		if (nread == -1)
		{
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

			if (bytesleft < sizeof(GnutellaHeader))
			{
				// Incomplete packet
				bContinue = false;
			}
			else
			{
				GnutellaHeader* hdr = (GnutellaHeader*)(m_packetbuf+offset);

				if((hdr->PayloadType == 0x00 && hdr->PayloadLength < 32768)					  ||
					(hdr->PayloadType == 0x01 && hdr->PayloadLength >= 14 && hdr->PayloadLength < 32768)  ||
					(hdr->PayloadType == 0x02 && hdr->PayloadLength > 0 && hdr->PayloadLength < 32768)	||
					(hdr->PayloadType == 0x30 && hdr->PayloadLength > 2 && hdr->PayloadLength < 32768)   ||
					(hdr->PayloadType == 0x31 && hdr->PayloadLength < 32768)   ||
					(hdr->PayloadType == 0x32 && hdr->PayloadLength < 32768)   ||
					(hdr->PayloadType == 0x40 && hdr->PayloadLength >= 26 && hdr->PayloadLength < 32768)  ||
					(hdr->PayloadType == 0x80 && hdr->PayloadLength >  2 && hdr->PayloadLength <= 230)   ||
					(hdr->PayloadType == 0x81 && hdr->PayloadLength > 26 && hdr->PayloadLength <= 32768))
				{
					DWORD packetlen = sizeof(GnutellaHeader) + hdr->PayloadLength;

					if (bytesleft < packetlen)
					{
						// Incomplete packet
						bContinue = false;
					}
					else
					{
						ProcessPacket(hdr);

						offset += packetlen;

						bContinue = true;
					}
				}
				else
				{
					bContinue = false;

					m_state = -1;
					Close();
					return;
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
	}
}

void CGnutellaSocket::ProcessPacket(GnutellaHeader* hdr)
{
	switch (hdr->PayloadType)
	{
	case GnutellaPing:
		{
		}
		break;
		
	case GnutellaPong:
		{
		/*
		if (hdr->PayloadLength < sizeof(GnutellaPongMessage))
		{
		ASSERT(0);
		}
			*/
			
			GnutellaPongMessage* pong = (GnutellaPongMessage*)hdr;
			
			NETWORKINFO* info = new NETWORKINFO;
			info->NumberOfSharedFiles = pong->NumberOfSharedFiles;
			info->NumberOfKilobytesShared = pong->NumberOfKilobytesShared;
			
			m_pComm->PostMessage(WM_USER+103, (WPARAM)info, 0);
		}
		break;
		
	case GnutellaQuery:
		{
			if (hdr->PayloadLength >= 3)
			{
				char* buf = (char*)(hdr+1);
				uint16 minimumSpeed = *(uint16*)buf;
				int n = 2;
				
				StringA searchCriteria;
				
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
		
	case GnutellaQueryHit:
		{
		/*
		if (hdr.PayloadLength < sizeof(GnutellaQueryHitMessage))
		{
		ASSERT(0);
		}
			*/
			
			GnutellaQueryHitMessage* queryhit = (GnutellaQueryHitMessage*)hdr;
			
			
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
}

/////////////////////////////////////////////////////////////////
// CGnutellaSearch

void CGnutellaSearch::Search(const char* criteria)
{
	int criteria_len = strlen(criteria);

	GnutellaHeader* hdr = (GnutellaHeader*)new uint8[sizeof(GnutellaHeader) + 2 + criteria_len+1];
	uint8* data = (uint8*)(hdr+1);

	hdr->Guid = m_queryGuid;
	hdr->Hops = 0;
	hdr->TTL = 7;
	hdr->PayloadType = GnutellaQuery;
	hdr->PayloadLength = 2 + criteria_len+1;

	*(uint16*)data = 0;
	strcpy((char*)(data+2), criteria);

	CGnutellaSocket ** it = m_pComm->m_connections.begin();
	while (it != m_pComm->m_connections.end())
	//for (int i = 0; min(10, m_pComm->m_connections.size()); i++)
	{
		CGnutellaSocket* pSocket = *it++;//m_pComm->m_connections[i];
		int nWritten = pSocket->Send(hdr, sizeof(GnutellaHeader) + hdr->PayloadLength);

		if (nWritten == 0)
		{
			int nError = GetLastError();
			TRACE("Socket error: %d\n", nError);

			//WSAENETDOWN
		}
	}

	delete hdr;
}

void SearchHit::urn(char* & p)
{
	if (*p++ == 's' && *p++ == 'h' && *p++ == 'a' && *p++ == '1' && *p++ == ':')
	{
		int n = 0;
		// base32 digest
		while (*p != 0 && *p != 0x1C)
		{
			int nbyte = 0;
			int nbit = 0;
			uint8 out[5] = {0};
			for (int i = 0; i < 8; i++)
			{
				char c = *p++;

				ASSERT(c != '=');
				int value = Base32Char(c);

				out[nbyte] |= value<<nbit;
				nbit += 5;
				if (nbit >= 8)
				{
					nbit -= 8;
					value >>= nbit;
					nbyte++;
					out[nbyte] = value;
				}
			}
			ASSERT(nbyte == 5);

			for (i = 0; i < 5; i++)
			{
				m_digest[n++] = out[i];
			}
		}
	}
	else
	{
		p--;
	}
}

void SearchHit::ggep(char* & p)
{
	while (*p)
	{
		p++;
	}
}

void SearchHit::plain(char* & p)
{
	while (*p && *p != 0x1C)
	{
		p++;
	}
}

void CGnutellaSearch::QueryHit(const GnutellaQueryHitMessage * queryhit)
{
	char* p = (char*)(queryhit + 1);
	char* end = p + queryhit->hdr.PayloadLength;

	for (int i = 0; i < queryhit->nHits; i++)
	{
		SearchHit* pHit = new SearchHit;

		m_pComm->m_queryhits.Add(pHit);

		pHit->m_Speed = queryhit->Speed;
		pHit->m_IPAddress = queryhit->IPAddress;
		pHit->m_Port = queryhit->PortNumber;

		if (end-p < 8) return;

		pHit->m_FileIndex = *(DWORD*)p; p += 4;
		pHit->m_FileSize = *(DWORD*)p; p += 4;

		char* filename = p;
		int filenamelen = 0;
		while (1)
		{
			if (!(p < end)) return;

			if (*p == 0)
			{
				p++;
				break;
			}

			filenamelen++;
			p++;
		}

		pHit->m_FileName = filename;

		while (1)
		{
			if (!(p < end)) return;
			if (*p == 0)	// end of extension block
			{
				p++;
				break;
			}

			if (end-p > 4 && p[0] == 'u' && p[1] == 'r' && p[2] == 'n' && p[3] == ':')
			{
				p += 4;
				pHit->urn(p);
			}
			else if (*p == 0xC3)
			{
				p++;
				pHit->ggep(p);
			}
			else
			{
				pHit->plain(p);
			}

			if (*p == 0x1C)	// separator
			{
				p++;
			}
		}

		/*
		if (0xC3)	// GGEP (Gnutella Generic Extension Protocol)
		{
		}

		if (!strncmp(resultData.c_str(), "urn:", 4))
		{
			//MessageBeep(-1);
		}
		*/

		m_pSearchHitHandler->OnHit(pHit);
	}
}

void CGnutellaSearch::More()
{
	// TODO
	ASSERT(0);
}

void GnutellaNetwork::AddServer(DWORD server, WORD port)
{
	// Add server/port if it doesn't already exist
	for (int i = 0; i < m_servers.size(); i++)
	{
		Host* host = m_servers[i];
		if (host->m_server == server && host->m_port == port)
		{
			return;
		}
	}
	m_servers.push_back(new Host(server, port));
}

void GnutellaNetwork::AddServers(const StringA& servers)
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

		char strserver[256];
		strcpy(strserver, addr.c_str());

		char* strport = strchr(strserver, ':');
		if (strport)
		{
			*strport = 0;
			strport++;

			DWORD server = ntohl(inet_addr(strserver));
			
			char* p;
			long port = strtol(strport, &p, 10);

			AddServer(server, port);
		}
	}
}

void GnutellaNetwork::ProcessHeaders(CGnutellaSocket* node)
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

int GnutellaNetwork::ConnectP2P(DWORD server, int port)
{
	CGnutellaSocket* node = new CGnutellaSocket;
	node->m_pComm = this;

	if (!node->Create())
	{
		return 0;
	}

	m_connections.Add(node);
	if (node->Connect(server, port))
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

	SearchHit* m_queryhitdata;
	DWORD m_startpos;

	int m_state;

	std::string m_server;

	void OnConnect(int nErrorCode);
	void OnReceive(int nErrorCode);

	std::string ReadLine()
	{
		std::string str;

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

class FileDownload :
//	public MSWindows::WindowImpl<GnutellaNetwork>
	public IFileDownload
{
public:
	FileDownload(GnutellaNetwork* pComm)
	{
		m_pComm = pComm;
/*
		RECT rect;
		SetRectEmpty(&rect);
		Create(NULL, rect, NULL, WS_POPUP);
		*/
		m_hThread = INVALID_HANDLE_VALUE;
	}

	GnutellaNetwork* m_pComm;

	HANDLE m_hThread;

	IDownloadHandler* m_handler;

	list<SearchHit*> m_matches;
	CArray<HTTPSocket*, HTTPSocket*> m_sockets;

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

	ASSERT(0);
#if 0	// TODO
	std::stringstream request;
	request	<< "GET " << "/get/" << m_queryhitdata->m_FileIndex << '/' << m_queryhitdata->m_FileName << " HTTP/1.1\r\n"
				<< "Host: " << m_server << "\r\n"
				<< "Range: bytes=" << m_startpos << "-" << m_queryhitdata->m_FileSize-1 << "\r\n"
				<< "\r\n";

	std::string requeststr = request.str();
	int nsent = Write((void*)requeststr.c_str(), requeststr.length());
#endif

	m_state = 1;
}

void HTTPSocket::OnRead()
{
	if (m_state == 1)
	{
		StringA status = ReadLine();

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

		typedef map<StringA, StringA> tyheadermap;
		tyheadermap headerlines;
		std::string headers;
		while (1)
		{
			StringA line = ReadLine();
			if (!strcmp(line.c_str(), ""))
			{
				break;
			}

			StringA name;
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
			StringA value = p;

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

			m_pFileDownload->m_stream->Seek(m_startpos, System::IO::STREAM_SEEK_SET);
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

IFileDownload* GnutellaNetwork::Download(LONGLONG FileSize, const uint8 sha1digest[20], IDownloadHandler* handler, ByteStreamWriter* stream)
{
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
}

IQuery* GnutellaNetwork::Search(const sysstring& criteria, ISearchHitHandler* pSearchHitHandler)
{
	if (m_connections.size() > 0)
	{
		CGnutellaSearch* pSearch = new CGnutellaSearch;

		pSearch->m_pSearchHitHandler = pSearchHitHandler;

		pSearch->m_pComm = this;
		CoCreateGuid(&pSearch->m_queryGuid);	// ??
		m_searchList.Add(pSearch);

		pSearch->Search(ConvertS2A(criteria).c_str());

		return pSearch;
	}

	return NULL;
}

void GnutellaNetwork::OnIdle()
{
	while (m_connections.size() < 80 && m_naddr < m_servers.size())
	{
		Host* host = m_servers[m_naddr];
		m_naddr++;

		DWORD server = host->m_server;
		int port = host->m_port;

		ConnectP2P(server, port);
	}
}

DWORD GnutellaNetwork::OnP2PThread()
{
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

void GnutellaNetwork::Connect()
{
#if 0
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
#endif

#if 0
	FILE* fp = fopen("C:/gwebcache.dat", "rb");
	while (!feof(fp))
	{
		DWORD IPAddress;
		WORD Port;
		fread(&IPAddress, 1, 4, fp);
		fread(&Port, 1, 2, fp);

		m_servers.push_back(new Host(ntohl(IPAddress), Port));
	}
#endif

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
	m_servers.Add(new Host("68.46.4.4", 6346));
	m_servers.Add(new Host("68.232.1.229", 6346));
	m_servers.Add(new Host("67.85.198.176", 6346));
	m_servers.Add(new Host("24.166.109.116", 6346));
	m_servers.Add(new Host("24.116.149.104", 6346));

	DWORD threadId;
	CreateThread(NULL, 0, OnP2PThreadFunc, this, 0, &threadId);
}
