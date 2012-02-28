#include "stdafx.h"
#include "../LXUI/Socket.h"
#include "EDonkeyNetwork.h"
#include "../LFC/ZLIBDecoder.h"

#include "../windows_header.h"

namespace System
{

/*
// {FF5BB720-59ED-4968-BE68-CE7E9F890C4E}
static GUID myguid = 
{ 0xff5bb720, 0x59ed, 0x4968, { 0xbe, 0x68, 0xce, 0x7e, 0x9f, 0x89, 0xc, 0x4e } };
*/

// {75F28AB2-5C34-4565-94FA-BC3CEEB38F45}
static GUID myguid = { 0x75f28ab2, 0x5c34, 0x4565, { 0x94, 0xfa, 0xbc, 0x3c, 0xee, 0xb3, 0x8f, 0x45 } };

class Msg
{
public:
	Msg(uint8 type)
	{
		m_p = m_buffer;

		putbyte(0xE3);
		putlong(0);	// Message Size, update later
		putbyte(type);
	}

	void putbyte(uint8 v)
	{
		*m_p++ = v;
	}

	void putshort(short v)
	{
		*m_p++ = v & 0xFF;
		*m_p++ = v >> 8;
	}

	void putlong(long v)
	{
		*m_p++ = v & 0xFF;
		*m_p++ = (v >> 8) & 0xFF;
		*m_p++ = (v >> 16) & 0xFF;
		*m_p++ = (v >> 24);
	}

	void put(const void *pv, DWORD cb)
	{
		memcpy(m_p, pv, cb);
		m_p += cb;
	}

	void putIntegerTag(uint8 name, long value)
	{
		putbyte(3);
		putshort(1);
		putbyte(name);
		putlong(value);
	}

	void putStringTag(uint8 name, const StringA & value)
	{
		putbyte(2);
		putshort(1);
		putbyte(name);

		putshort(value.Length());
		put(value.c_str(), value.Length());
	}

	void UpdateSize()
	{
		DWORD length = GetLength() - 5;
		m_buffer[1] = length & 0xFF;
		m_buffer[2] = (length>>8) & 0xFF;
		m_buffer[3] = (length>>16) & 0xFF;
		m_buffer[4] = length>>24;
	}

	const uint8* GetBuffer() const
	{
		return m_buffer;
	}

	DWORD GetLength() const
	{
		return m_p - m_buffer;
	}

	uint8 m_buffer[1024];

protected:

	uint8* m_p;

};

class EDonkeySocket : public AsyncSocket
{
public:
	CTOR EDonkeySocket()
	{
		m_nbufbytes = 0;
	}

	uint8 m_packetbuf[32768];
	int m_nbufbytes;

	void ReadPackets()
	{
//		ULONG n;
//		ioctlsocket(m_socket, FIONREAD, &n);
		int nread = Receive(m_packetbuf+m_nbufbytes, 32768-m_nbufbytes);
		if (nread == -1)
		{
//			m_state = -1;
			Close();
			return;
		}

		ULONG nbufbytes = m_nbufbytes + nread;

		// Process all complete packets
		bool bContinue;

		ULONG offset = 0;
		ULONG bytesleft;
		do
		{
			bytesleft = nbufbytes - offset;

			const int EDONKEY_HEADER_SIZE	= 5;

			if (bytesleft < EDONKEY_HEADER_SIZE)
			{
				// Incomplete packet
				bContinue = false;
			}
			else
			{
				uint8* msgstart = m_packetbuf+offset;

				uint8* p = msgstart;

			// Get Header
				uint8 protocol = *p++;
				DWORD size = *p++;
				size |= (*p++)<<8;
				size |= (*p++)<<16;
				size |= (*p++)<<24;

				if (size < 32768)	// Some sensible limit
				{
					DWORD packetlen = EDONKEY_HEADER_SIZE + size;

					if (bytesleft < packetlen)
					{
						// Incomplete packet
						bContinue = false;
					}
					else
					{
						if (protocol == 0xE3)	// Uncompressed packet
						{
							ProcessPacket(size, p);
						}
						else if (protocol == 0xD4)	// ZLIB compressed packet
						{
							ZLIBDecoder* zlibDecoder = new ZLIBDecoder(new IO::MemoryByteStream(p, size));
							/*
							zlibDecoder->start();
							zlibDecoder->start_block();
							*/

							uint8* p2 = new uint8[32000];
							ULONG len = 0;
							while (1)
							{
								int n = zlibDecoder->Read(p2+len, 512);
								len += n;
								if (n < 512)
									break;
							}

							ProcessPacket(size, p2);

							delete p2;
						}

						offset += packetlen;
					//	m_nbufbytes = 0;

						bContinue = true;
					}
				}
				else
				{
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

	virtual void ProcessPacket(DWORD size, uint8* p) = 0;
};

class EDonkeyClientSocket : public EDonkeySocket
{
public:

	EDonkeyClientSocket(EDonkeyNetwork* pNetwork)
	{
		m_pNetwork = pNetwork;
	}

	EDonkeyNetwork* m_pNetwork;

	uint8* hello;
	DWORD hellolen;

	virtual void ProcessPacket(DWORD size, uint8* p)
	{
		if (size < 1)
		{
			ASSERT(0);
			return;
		}

		uint8 type = *p++;
		if (type == 0x01)	// HELLO
		{
			uint8 UserHashSize = *p++;

#if 0
			hellolen = size + 5 - 1;
			hello = new BYTE[hellolen];

			DWORD length = hellolen - 5;
			hello[0] = 0xE3;
			hello[1] = length & 0xFF;
			hello[2] = (length>>8) & 0xFF;
			hello[3] = (length>>16) & 0xFF;
			hello[4] = length>>24;
			hello[5] = 0x4C;/*HELLO ANSWER*/

			memcpy(hello+6, msgstart+6+1, length-1);
#endif
		}
		/*
		else if (type == 0x05)	// REJECT
		{
		}
		*/
		else if (type == 0x38)	// MESSAGE
		{
			uint16 size = *p++;
			size |= (*p++)<<8;

			char* message = new char[size+1];
			message[size] = 0;
			memcpy(message, p, size);
			p += size;

			TRACE("%s\n", message);
		}
		else
		{
			TRACE("Unknown opcode 0x%x\n", type);
		}
	}

	virtual void OnClose()
	{
//		MessageBeep(-1);
//		Close();
	}

//	BYTE* m_pHelloMsg;

	virtual void OnWrite();

	virtual void OnRead()
	{
		ReadPackets();
	}

};

class EDonkeyListenerSocket : public AsyncSocket
{
public:
	EDonkeyListenerSocket(EDonkeyNetwork* pNetwork)
	{
		m_pNetwork = pNetwork;
	}

	EDonkeyNetwork* m_pNetwork;

	virtual void OnAccept()
	{
		TRACE("OnAccept\n");

	//	sockaddr addr;
	//	int addrlen;

		EDonkeyClientSocket* pSocket = new EDonkeyClientSocket(m_pNetwork);
		if (!Accept(pSocket))
		{
			delete pSocket;
		}

		/*
		pSocket->m_socket = accept(m_socket, NULL, NULL);
		if (pSocket->m_socket != INVALID_SOCKET)
		{
			pSocketWindow->m_sockets.insert(SocketWindow::tysocketmap::value_type(pSocket->m_socket, pSocket));
		}
		else
			delete pSocket;
			*/

#if 0
			Msg msg(0x15/*OFFERFILES*/);

			msg.putlong(10);	// FileCount

			char* filenames[10] =
			{
				"Test1",
				"Test2",
				"Test3",
				"Test4",
				"Test5",
				"Test6",
				"Test7",
				"Test8",
				"Test9",
				"Test10",
			};

			for (int i = 0; i < 10; i++)
			{
				BYTE md4[16];
				md4[i] = i;

				msg.put(md4, 16);
				msg.putlong(0);	// Client ID
				msg.putshort(0x15);	// TCP port
				msg.putlong(1);	// Tag count
				msg.putStringTag(0x1, filenames[i]);
			}

			msg.UpdateSize();
			int sent = pSocket->Send(msg.GetBuffer(), msg.GetLength());
#endif
	}

	virtual void OnClose()
	{
		MessageBeep(-1);
	}

	virtual void OnWrite()
	{
		MessageBeep(-1);
	}

	virtual void OnRead()
	{
#if 0
		ULONG n;
		ioctlsocket(m_socket, FIONREAD, &n);
#endif
	}
};

class EDonkeySearchHit : public ISearchHit
{
public:

	virtual StringA* get_FileName() const
	{
		return m_FileName;
	}

	virtual LONGLONG get_FileSize() const
	{
		return m_FileSize;
	}

	virtual const uint8* get_Sha1Digest() const
	{
		return m_digest;
	}

	virtual void GetHost(DWORD* IPAddress, uint16* Port) const
	{
		*IPAddress = m_IPAddress;
		*Port = m_Port;
		return;
	}

	virtual DWORD get_HostSpeed() const
	{
		return 0;
	}

	StringA* m_FileName;
	DWORD m_FileSize;
	uint8 m_digest[20];

	DWORD m_IPAddress;
	DWORD m_Port;
};

class EDonkeyServerSocket : public EDonkeySocket, public IConnection
{
public:

	virtual String get_Name() const
	{
		return WSTR("Unnamed");
	}

	virtual IPv4 get_Address() const
	{
		return m_address;
	}

	IPv4 m_address;

	EDonkeyServerSocket(EDonkeyNetwork* pNetwork)
	{
		m_pNetwork = pNetwork;
		m_state = -1;

		m_ClientID = 0;
		m_UserCount = 0;
		m_FileCount = 0;
	}

	ISearchHitHandler* m_pSearchHitHandler;

	EDonkeyNetwork* m_pNetwork;
	int m_state;

	DWORD m_ClientID;
	DWORD m_UserCount;
	DWORD m_FileCount;

	void OfferFiles()
	{
		Msg msg(0x15/*OFFERFILES*/);

		msg.putlong(0);

		msg.UpdateSize();
		int sent = Send(msg.GetBuffer(), msg.GetLength());
	}

	virtual void ProcessPacket(DWORD size, uint8* p)
	{
		if (size < 1)
		{
			ASSERT(0);
			return;
		}

		uint8 type = *p++;

		if (type == 0x32)	// List of servers
		{
			uint8 EntryCount = *p++;

			for (UINT i = 0; i < EntryCount; i++)
			{
				DWORD IPAddress = *p++;
				IPAddress |= (*p++)<<8;
				IPAddress |= (*p++)<<16;
				IPAddress |= (*p++)<<24;

				uint16 Port = *p++;
				Port |= (*p++)<<8;

				m_pNetwork->AddServer(ntohl(IPAddress), Port);
			}
		}
		else if (type == 0x33)	// SEARCH RESULTS
		{
			DWORD Count = *p++;
			Count |= (*p++)<<8;
			Count |= (*p++)<<16;
			Count |= (*p++)<<24;

			for (UINT i = 0; i < Count; i++)
			{
				EDonkeySearchHit* pHit = new EDonkeySearchHit;

				p += 16;	// File Hash

				pHit->m_IPAddress = *p++;
				pHit->m_IPAddress |= (*p++)<<8;
				pHit->m_IPAddress |= (*p++)<<16;
				pHit->m_IPAddress |= (*p++)<<24;

				pHit->m_Port = *p++;
				pHit->m_Port |= (*p++)<<8;

				DWORD TagCount = *p++;
				TagCount |= (*p++)<<8;
				TagCount |= (*p++)<<16;
				TagCount |= (*p++)<<24;

				for (UINT ti = 0; ti < TagCount; ti++)
				{
					uint8 Type = *p++;

					uint16 NameLen = *p++;
					NameLen |= (*p++)<<8;
					if (NameLen > 255)	// Sanity check
					{
						return;//ASSERT(0);
					}

					uint8* NameP = p;
					p += NameLen;

					if (Type == 1)	// Hash
					{
						p += 16;
					}
					else
					{
						if (Type == 2)	// String
						{
							uint16 StringLen = *p++;
							StringLen |= (*p++)<<8;

							char* StringVal = new char[StringLen+1];
							StringVal[StringLen] = 0;
							memcpy(StringVal, p, StringLen);
							p += StringLen;

							if (NameLen == 1 && *NameP == 0x01)
							{
								if (strncmp(StringVal, "Speed_Of_Sound", 14) == 0)
								{
									MessageBeep(-1);
								}
								pHit->m_FileName = new StringA(StringVal);
							}

							TRACE("%.510s\n", StringVal);
							delete StringVal;
						}
						else if (Type == 3)	// Integer
						{
							DWORD Value = *p++;
							Value |= (*p++)<<8;
							Value |= (*p++)<<16;
							Value |= (*p++)<<24;

							if (NameLen == 1 && *NameP == 0x02)
							{
								pHit->m_FileSize = Value;
							}
						}
						else if (Type == 4)	// float
						{
							uint32 iValue = *p++;
							iValue |= (*p++)<<8;
							iValue |= (*p++)<<16;
							iValue |= (*p++)<<24;
							float Value = *(float*)&iValue;
						}
						else
							ASSERT(0);
					}
				}

			//	PostMessage(m_pNetwork->m_hWnd, WM_USER+104, (WPARAM)m_pSearchHitHandler, (LPARAM)pHit);
				m_pSearchHitHandler->OnHit(pHit);
			}
		}
		else if (type == 0x34)	// SERVER STATUS
		{
			m_UserCount = *p++;
			m_UserCount |= (*p++)<<8;
			m_UserCount |= (*p++)<<16;
			m_UserCount |= (*p++)<<24;

			m_FileCount = *p++;
			m_FileCount |= (*p++)<<8;
			m_FileCount |= (*p++)<<16;
			m_FileCount |= (*p++)<<24;
		}
		else if (type == 0x38)	// MESSAGE
		{
			uint16 msgsize = *p++;
			msgsize |= (*p++)<<8;

			char* message = new char[msgsize+1];
			message[msgsize] = 0;
			memcpy(message, p, msgsize);
			p += msgsize;

			TRACE("%.510s\n", message);

			if (m_state == 1)
			{
#if 0
				{
					Msg msg(0x15/*OFFERFILES*/);

					msg.putlong(0);

					msg.UpdateSize();
					int sent = Send(msg.GetBuffer(), msg.GetLength());
				}

				{
					Msg msg(0x14/*SERVERSTATUS*/);
					msg.UpdateSize();
					int sent = Send(msg.GetBuffer(), msg.GetLength());
				}

				m_state = 2;
#endif
			}
		}
		else if (type == 0x40)	// IDCHANGE
		{
			m_ClientID = *p++;
			m_ClientID |= (*p++)<<8;
			m_ClientID |= (*p++)<<16;
			m_ClientID |= (*p++)<<24;

			DWORD Flags = *p++;
			Flags |= (*p++)<<8;
			Flags |= (*p++)<<16;
			Flags |= (*p++)<<24;

			if (Flags & 1)
			{
				TRACE("Server supports compression\n");
			}
		}
		else if (type == 0x41)	// SERVERIDENT
		{
			TRACE("Server Ident:\n");

			p += 16; // Hash
			p += 4;  // IP
			p += 2;	// Port

			DWORD TagCount = *p++;
			TagCount |= (*p++)<<8;
			TagCount |= (*p++)<<16;
			TagCount |= (*p++)<<24;

			for (int i = 0; i < TagCount; i++)
			{
				uint8 Type = *p++;
				if (Type == 2)
				{
					uint16 NameLen = *p++;
					NameLen |= (*p++)<<8;
					p += NameLen;

					uint16 StringLen = *p++;
					StringLen |= (*p++)<<8;

					char* StringVal = new char[StringLen+1];
					StringVal[StringLen] = 0;
					memcpy(StringVal, p, StringLen);
					p += StringLen;

					TRACE("%s\n", StringVal);
				}
				else
					break;
			}
		}
		else
		{
			TRACE("Unknown opcode 0x%x\n", type);
		}
	}

	virtual void OnConnect(int nErrorCode)
	{
		if (nErrorCode)
		{
			TRACE("Failed to connect to server\n");
			for (int i = 0; i < m_pNetwork->m_ServerConnections.size(); i++)
			{
				if (m_pNetwork->m_ServerConnections[i] == this)
				{
					m_pNetwork->m_ServerConnections.erase(m_pNetwork->m_ServerConnections.begin()+i);
					return;
				}
			}
			ASSERT(0);
			return;
		}

		MSWindows::PostMessageA(m_pNetwork->m_hWnd, WM_USER+100, (MSWindows::LPARAM)static_cast<IConnection*>(this), 0);
		TRACE("Connected\n");
		m_state = 0;
	}

	virtual void OnWrite()
	{
		if (m_state == 0)
		{
			Msg msg(0x01/*LOGIN*/);

		//	GUID guid;
		//	CoCreateGuid(&guid);

			/*
			char hostname[256];
			gethostname(hostname, 256);
			hostent* host = gethostbyname(hostname);
			DWORD ip = *((DWORD*)host->h_addr_list[0]);
			*/
			DWORD ip = 0;

		//	((BYTE*)&myguid)[6] = 14;
		//	((BYTE*)&myguid)[15] = 111;

			msg.put(&myguid, 16);	// User Hash
			msg.putlong(ip);		// Client ID (not known yet)
			msg.putshort(4662);	// TCP Port
			msg.putlong(4);	// Tag count

			StringA nickname = "sigler111";
			msg.putStringTag(0x1, nickname);
			msg.putIntegerTag(0x11, 0x3C);	// Version
			msg.putIntegerTag(0x0F, 4662);	// TCP Port
			msg.putIntegerTag(0x20, 0);	// Flags // Compression

			msg.UpdateSize();
			int sent = Send(msg.GetBuffer(), msg.GetLength());

			m_state = 1;

				{
					Msg msg(0x14/*SERVERSTATUS*/);
					msg.UpdateSize();
					int sent = Send(msg.GetBuffer(), msg.GetLength());
				}

			//	OfferFiles();
		}
		else if (m_state == 1)
		{
			Msg msg(0x15/*OFFERFILES*/);

			msg.putlong(10);	// FileCount

			char* filenames[10] =
			{
				"Test1",
				"Test2",
				"Test3",
				"Test4",
				"Test5",
				"Test6",
				"Test7",
				"Test8",
				"Test9",
				"Test10",
			};

			for (int i = 0; i < 10; i++)
			{
				uint8 md4[16];
				md4[i] = i;

				msg.put(md4, 16);
				msg.putlong(0);	// Client ID
				msg.putshort(0x15);	// TCP port
				msg.putlong(1);	// Tag count
				msg.putStringTag(0x1, filenames[i]);
			}

			msg.UpdateSize();
			int sent = Send(msg.GetBuffer(), msg.GetLength());

			m_state = 2;
		}
	}

	virtual void OnRead()
	{
		ReadPackets();
	}

	virtual void OnClose()
	{
		TRACE("Server Close\n");
	//	Close();
		for (int i = 0; i < m_pNetwork->m_ServerConnections.size(); i++)
		{
			if (m_pNetwork->m_ServerConnections[i] == this)
			{
				MSWindows::PostMessageA(m_pNetwork->m_hWnd, WM_USER+101, (MSWindows::LPARAM)static_cast<IConnection*>(this), 0);
				m_pNetwork->m_ServerConnections.erase(m_pNetwork->m_ServerConnections.begin()+i);
				return;
			}
		}
		ASSERT(0);
	}
};

void EDonkeyClientSocket::OnWrite()
{
//		MessageBeep(-1);
//		int nsent = Send(hello, hellolen);

	{
		Msg msg(0x4C/*HELLO ANSWER*/);

	//	GUID guid;
	//	CoCreateGuid(&guid);

		/*
		char hostname[256];
		gethostname(hostname, 256);
		hostent* host = gethostbyname(hostname);
		DWORD ip = *((DWORD*)host->h_addr_list[0]);
		*/
		DWORD ip = 0;

	//	((BYTE*)&myguid)[6] = 14;
	//	((BYTE*)&myguid)[15] = 111;

		EDonkeyServerSocket* pServerConnection = m_pNetwork->m_ServerConnections[0];

		msg.putbyte(16);	// User Hash Length
		msg.put(&myguid, 16);	// User Hash
		msg.putlong(pServerConnection->m_ClientID);		// Client ID
		msg.putshort(4662);	// TCP Port
		msg.putlong(3);	// Tag count

		StringA nickname = "sigler111";
		msg.putStringTag(0x1, nickname);
		msg.putIntegerTag(0x11, 0x3C);	// Version
		msg.putIntegerTag(0x0F, 4662);	// TCP Port
	//	msg.putIntegerTag(0x20, 1);	// Flags


		SOCKADDR_IN saddr;
		int len = sizeof(saddr);
		pServerConnection->GetPeerName((SOCKADDR*)&saddr, &len);

		DWORD IPAddress = /*ntohl*/(saddr.sin_addr.S_un.S_addr);
		uint16 port = ntohs(saddr.sin_port);

		msg.putlong(IPAddress);
		msg.putshort(port);

		msg.UpdateSize();
		int sent = Send(msg.GetBuffer(), msg.GetLength());
	}
}

IQuery* EDonkeyNetwork::Search(StringA* criteria, ISearchHitHandler* pSearchHitHandler)
{
	Msg msg(0x16);

	msg.putbyte(0x1);
	msg.putshort(criteria->Length());
	msg.put(criteria->c_str(), criteria->Length());

	msg.UpdateSize();
	for (int i = 0; i < m_ServerConnections.size(); i++)
	{
		m_ServerConnections[i]->m_pSearchHitHandler = pSearchHitHandler;
		int nsent = m_ServerConnections[i]->Send(msg.GetBuffer(), msg.GetLength());
		if (nsent > 0)
		{
			TRACE("Search Query Sent\n");
		}
	}
	return NULL;
}

void EDonkeyNetwork::OnIdle()
{
	if (m_ServerConnections.size() < 10 && m_naddr < m_servers.size())
	{
		Host* host = m_servers[m_naddr];
		m_naddr++;

		DWORD server = host->m_server;
		uint16 port = host->m_port;

		EDonkeyServerSocket* pServerConnection;
		pServerConnection = new EDonkeyServerSocket(this);
		pServerConnection->m_address.IPAddress = server;
		pServerConnection->m_address.Port = port;

		m_ServerConnections.push_back(pServerConnection);

		pServerConnection->Create();
		pServerConnection->Connect(server, port);
	}
}

DWORD EDonkeyNetwork::OnP2PThread()
{
	EDonkeyListenerSocket* listenersocket = new EDonkeyListenerSocket(this);
	listenersocket->Create();
	listenersocket->Listen(4662);

	// Main thread message loop, TODO, eventually, I will have this in a a system class of its own (only more powerful than below)
	while (1)
	{
		MSWindows::MSG msg;
		if (!MSWindows::PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			OnIdle();
		}

		MSWindows::GetMessageA(&msg, NULL, 0, 0);
		MSWindows::TranslateMessage(&msg);
		MSWindows::DispatchMessageA(&msg);
	}

	return 0;
}

void EDonkeyNetwork::Connect()
{

	m_servers.Add(new Host("195.245.244.243", 4661));
	m_servers.Add(new Host("66.250.47.36", 4661));
	m_servers.Add(new Host("62.241.53.16", 4242));
	m_servers.Add(new Host("62.241.53.2", 4242));
	m_servers.Add(new Host("64.34.161.180", 3921));
	m_servers.Add(new Host("62.241.53.17", 4242));
	m_servers.Add(new Host("80.239.200.103", 3000));
	m_servers.Add(new Host("213.251.161.69", 4661));
	m_servers.Add(new Host("81.169.154.125", 4661));
	m_servers.Add(new Host("84.183.148.183", 8661));

	DWORD threadId;
	MSWindows::CreateThread(NULL, 0, OnP2PThreadFunc, this, 0, &threadId);

	/*
	for (int i = 0; i < m_servers.size(); i++)
	{
		EDonkeyServerSocket* pServerConnection;
		pServerConnection = new EDonkeyServerSocket(this);

		m_ServerConnections.push_back(pServerConnection);

		pServerConnection->Create();
		pServerConnection->Connect(m_servers[i]->m_server, m_servers[i]->m_port);
	}
	*/

//	m_pServerSocket->Connect("80.239.200.103", 3000);
//	m_pServerSocket->Connect("213.251.161.69", 4661);
//	m_pServerSocket->Connect("81.169.154.125", 4661);
//	m_pServerSocket->Connect("195.245.244.244", 3000);
//	m_pServerSocket->Connect("84.183.148.183", 8661);
//	m_pServerSocket->Connect("64.132.210.162", 4661);
}

}
