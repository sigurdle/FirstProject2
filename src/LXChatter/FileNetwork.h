#ifndef __FILENETWORK_H_
#define __FILENETWORK_H_

			  /*
struct __in_addr {
        union {
                struct { u_char s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { u_short s_w1,s_w2; } S_un_w;
                uint32 S_addr;
        } S_un;
					 */

extern "C"
{

DECLSPEC_IMPORT HRESULT WINAPI CoCreateGuid(/*OUT*/ GUID *pguid);

uint32 __stdcall ntohl (/*IN*/ uint32 netlong);

uint16 __stdcall ntohs (/*IN*/ uint16 netshort);

unsigned long __stdcall inet_addr (/*IN*/ const char * cp);

//char * __stdcall inet_ntoa (/*IN*/ uint32/*struct _in_addr*/ in);

		  }

namespace System
{

uint8 Base32Char(int c);

class IPv4
{
public:
	DWORD IPAddress;
	uint16 Port;
};

class IConnection
{
public:

	virtual String get_Name() const = 0;
	virtual IPv4 get_Address() const = 0; 

//	tyusermap m_user;
	Object* m_userdata;
};

class StdStream
{
public:

	StdStream(IO::Stream* stream)
	{
		m_stream = stream;
	//	m_bufferOffset = 256;

		m_un = -1;
	}

	/*
	int m_bufferOffset;
	int m_bufferLength;
	BYTE m_buffer[256];
	*/

	ULONG Read(void* pv, ULONG cb)
	{
		return m_stream->Read(pv, cb);

		/*
		ULONG n = 0;
		while (n < cb)
		{
			if (m_bufferOffset == 256)
			{
				m_bufferLength = stream->Read(m_buffer, 256);
				if (m_bufferLength == 0)
					return -1;
				m_bufferOffset = 0;
			}

			m_bufferOffset++;
		}

		return c;
		*/
	}

	int m_un;

	void UngetChar(int c)
	{
		if (m_un != -1)
			throw -1;
		m_un = c;
	}

	int GetChar()
	{
		if (m_un != -1)
		{
			int c = m_un;
			m_un = -1;
			return c;
		}
		uint8 b;
		if (Read(&b, 1) == 0)
			return -1;
		return b;
	}

	String GetLine()
	{
		String line;

		while (1)
		{
			int c = GetChar();
			if (c == -1)
				break;
			if (c == '\r' || c == '\n')
			{
				int c2 = GetChar();
				if (c2 != '\r' && c2 != '\n')
					UngetChar(c2);
				break;
			}

			ASSERT(0);
#if 0
			line += (char)c;
#endif
		}

		return line;
	}

	_Ptr<IO::Stream> m_stream;
};

struct NETWORKINFO
{
	int64 NumberOfClients;
	int64 NumberOfSharedFiles;
	int64 NumberOfKilobytesShared;
};

interface ISearchHit
{
	virtual String get_FileName() const = 0;
	virtual int64 get_FileSize() const = 0;
	virtual const uint8* get_Sha1Digest() const = 0;
	virtual void GetHost(DWORD* IPAddress, uint16* Port) const = 0;
	virtual DWORD get_HostSpeed() const = 0;
};

interface IQuery
{
	virtual void More() = 0;
};

interface ISearchHitHandler
{
	virtual void OnHit(ISearchHit* pHit) = 0;
};

interface IDownloadHandler
{
	virtual void OnHit(ISearchHit* pHit) = 0;
};

interface IFileDownload
{
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Cancel() = 0;
};

interface INetwork
{
	virtual void Connect() = 0;
	virtual IQuery* Search(StringIn criteria, ISearchHitHandler* pSearchHitHandler) = 0;
	virtual IFileDownload* Download(LONGLONG FileSize, const uint8 sha1digest[20], IDownloadHandler* handler, System::IO::ByteStreamWriter* stream) = 0;
};

interface INetworkClient
{
	virtual void OnConnection(IConnection* pSocket) = 0;
	virtual void OnCloseConnection(IConnection* pSocket) = 0;
	virtual void OnConnectionStatus(IConnection* pSocket, int code) = 0;

	virtual void OnNetworkInfo(const NETWORKINFO* info) = 0;
};

class Host
{
public:
	Host(const char* server, uint16 port)
	{
		m_server = ntohl(inet_addr(server));
		m_port = port;
	}

	Host(DWORD server, uint16 port)
	{
		m_server = server;
		m_port = port;
	}

	DWORD m_server;
	uint16 m_port;
};

class GWebCache : public Object
{
public:
	GWebCache(StringIn url, uint16 port)
	{
		m_url = url;
		m_port = port;
	}

	void RetrieveHosts();

	String get_Url() const
	{
		return m_url;
	}

	uint16 get_Port() const
	{
		return m_port;
	}

	Array<Host*> m_hosts;

protected:

	String m_url;
	uint16 m_port;
};

}	// System

#endif //__FILENETWORK_H_
