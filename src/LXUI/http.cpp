#include "stdafx.h"
#include "LXUI2.h"
#include "LFC/Socket.h"

#include <direct.h>
#include <stdlib.h>

//#include <sstream>

#include "http.h"

namespace System
{
using namespace std;
using namespace IO;

const char* GetFilenameExtension(const char* str)
{
	int len = strlen(str);
	const char* p = str + len-1;
	while (p >= str)
	{
		if (*p == '.')
			return p;

		p--;
	}
	return NULL;
}

StringA* GetTempFilename(const char* dir, const char* url)
{
	const char* ext = GetFilenameExtension(url);

	_mkdir(dir);

	int n = 0;
	while (1)
	{
		char filename[64];
		sprintf_s(filename, "temp%d", n);

		char fullpath[512];
		_makepath_s(fullpath, NULL, dir, filename, ext);

		FILE* fp = fopen(fullpath, "rb");
		if (fp == NULL)	// File doesn't exist, so we return the filename
			return new StringA(string_copy(fullpath));

		fclose(fp);	// Close the file and try another filename
		n++;
	}

	return NULL;
}

namespace Net
{

////////////////////////////////////////////////////////
// HttpContentStream

HttpContentStream::HttpContentStream(HttpRequest* pRequest)// : m_refcount(0)
{
	m_transferEncoding = NULL;

	m_pRequest = pRequest;

	m_pos = 0;
	m_chunkBytesLeft = 0;
	m_contentLength = (ULONGLONG)-1;
}

HttpContentStream::~HttpContentStream()
{
	m_contentLength = -1;
}

LONGLONG HttpContentStream::GetSize()
{
	return m_contentLength;
}

LONGLONG HttpContentStream::GetSize() const
{
	return m_contentLength;
}

ISequentialByteStream* HttpContentStream::Clone() const
{
	THROW(-1);
	return NULL;
}

ULONG HttpContentStream::Read(void* pv, ULONG cb)
{
	uint8* pb = (uint8*)pv;

	if (m_transferEncoding && *m_transferEncoding != "identity")	// chunked
	{
		ULONG bytesLeft = cb;

		/*

  TODO, something like this here

		if (m_chunkSize == 0)
			return 0;
			*/

		while (bytesLeft)
		{
			if (m_chunkBytesLeft == 0)	// Begin next chunk
			{
				BufferImp<char> buffer;
				StringBuilder<char> stream(&buffer);

				m_pRequest->m_connection->m_pSocket->ReadLine(stream);
				StringA* str = buffer.DetachToString();

				long size;
				if (sscanf(str->c_str(), "%x", &size) != 1)
					THROW(-1);

				m_chunkBytesLeft = size;

				if (size == 0)
				{
					m_pRequest->m_connection->m_pSocket->ReadLine(stream);
					StringA* crlf = buffer.DetachToString();
					ASSERT(crlf->Length() == 0);
					m_pRequest->m_connection->m_pSocket->m_bDone = true;
					break;
				}

			//	m_chunkSize = size;

			}

			ULONG len = bytesLeft;
			if (len > m_chunkBytesLeft)	// Don't cross chunks
				len = m_chunkBytesLeft;

			int nRead = m_pRequest->m_connection->m_pSocket->Read(pb, len);

			m_pos += nRead;
			pb += nRead;
			m_chunkBytesLeft -= nRead;
			bytesLeft -= nRead;

			if (nRead < len)
				break;

			if (m_chunkBytesLeft == 0)	// End chunk
			{
				BufferImp<char> buffer;
				StringBuilder<char> stream(&buffer);

				m_pRequest->m_connection->m_pSocket->ReadLine(stream);
				StringA* crlf = buffer.DetachToString();
				ASSERT(crlf->Length() == 0);
			}
		}

		return cb - bytesLeft;
	}
	else
	{
#if 0
		std::string contentLengthStr;
		if (headers.GetHeaderValue("Content-Length", contentLengthStr))
		{
			long contentLength;
			sscanf(contentLengthStr.c_str(), "%d", &contentLength);
#endif

		ULONG len = cb;
		if (m_pos+len > m_contentLength)
			len = m_contentLength-m_pos;

		ULONG nRead = m_pRequest->m_connection->m_pSocket->Read(pb, len);

		m_pos += nRead;
		//m_chunkBytesLeft -= nRead;

	//	if (nRead < len)
	//		m_chunkBytesLeft = 0;

		return nRead;
	}
}

LONGLONG HttpContentStream::Seek(LONGLONG offset, IO::SeekOrigin origin)
{
	uint8 buffer[256];

	if (origin == System::IO::STREAM_SEEK_SET)
	{
		if (offset < m_pos)	// Can't seek backward
		{
			raise(Exception(L"Can't seek backward"));
		}

		for (int i = m_pos; i < offset; i++)
		{
			int n = 256;
			if (i+n > offset)
				n = offset-i;

			Read(buffer, n);
		}
	}
	else if (origin == System::IO::STREAM_SEEK_CUR)
	{
		if (offset < 0)	// Can't seek backward
		{
			raise(Exception(L"Can't seek backward"));
		}

		for (int i = 0; i < offset; i++)
		{
			int n = 256;
			if (i+n > offset)
				n = offset-i;

			Read(buffer, n);
		}
	}
	else
	{
		raise(ArgumentException());
	}

	return m_pos;
}

ULONG HttpContentStream::Write(const void* pv, ULONG cb)
{
	THROW(-1);
	return -1;
}

/*
ULONG HttpContentStream::AddRef()
{
	return _Object::AddRef();
	//m_refcount++;
	//return m_refcount;
}

ULONG HttpContentStream::Release()
{
	return _Object::Release();
}
*/

//////////////////////////////////////////////////////////////////
// HttpRequest

HttpRequest::HttpRequest(HttpConnection* connection, StringA* verb, StringA* objectName)
{
	m_connection = connection;
	m_verb = verb;
	m_objectName = objectName;
	m_additionalHeaders = NULL;
	m_pContentStream = new HttpContentStream(this);
}

void HttpRequest::AddHeaders(StringA* str)
{
	ASSERT(0);
#if 0
	m_additionalHeaders = *m_additionalHeaders + *str;
#endif
}

HttpContentStream* HttpRequest::GetContentStream()
{
	return m_pContentStream;
}

void HttpConnection::HttpSocket::OnSend(int nErrorCode)
{
	TRACE("OnSend %p\n", this);

	/*
	char* msg = "GET http://www.lerstad.com/index.html HTTP/1.1\r\n"
					"Host: www.lerstad.com\r\n"
				//	"Content-Length: 0\r\n"
					"\r\n";

	int n = Write(msg, strlen(msg));
	*/
//	select(0, NULL, &fd, NULL, NULL);
//	int nSent = send(m_socket, msg, strlen(msg), 0);
}

void HttpConnection::HttpSocket::OnReceive(int nErrorCode)
{
	if (m_state == 0)
	{
		m_pConnection->m_pRequest->ReadResponse();
		m_state = 1;
	}
	else
	{
		ULONG n;
		IOCtl(FIONREAD, &n);

		TRACE("OnRead %p count %d\n", this, n);

	//	if (n > 0)
		{
			m_pConnection->m_pRequest->m_downloadCallback->OnDataAvailable(n, m_pConnection->m_pRequest->GetContentStream());

			/*
			if (m_bDone)
			{
				m_pConnection->m_pRequest->m_downloadCallback->OnDone();
			}
			*/

			/*
			m_sofar += n;

			if (m_sofar >= m_pConnection->m_pRequest->m_pContentStream->m_contentLength)
			{
				m_pConnection->m_pRequest->m_downloadCallback->OnDone();
			}
			*/
		}
		//else
		;//	ASSERT(0);
	}
}

HttpConnection::HttpSocket::HttpSocket()
{
	m_bDone = false;
//	m_hEvent = INVALID_HANDLE_VALUE;
	m_state = 0;
	m_sofar = 0;
}

void HttpConnection::HttpSocket::ReadLine(StringBuilder<char>& stream)
{
	while (1)
	{
		char c;
		if (Read(&c, 1) != 1)
			THROW(-1);
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
			//		THROW(-1);
				stream << c;

			//	if (str.length() == 512)
			//		THROW(-1);
				stream << c2;
			}
		}
		else
		{
		//	if (str.length() == 512)
		//		THROW(-1);
			stream << c;
		}
	}

//	TRACE("%s\n", str.c_str());
//	return buffer.DetachToString();
}

void HttpConnection::HttpSocket::OnConnect(int nErrorCode)
{
	TRACE("OnConnect\n");
//			SetEvent(m_hEvent);
}

void HttpConnection::HttpSocket::OnClose(int nErrorCode)
{
	TRACE("OnClose %p, %d\n", this, nErrorCode);

	// Check if there's more data to read also in OnClose()
	ULONG n;
	IOCtl(FIONREAD, &n);
	if (n > 0)
	{
		m_pConnection->m_pRequest->m_downloadCallback->OnDataAvailable(n, m_pConnection->m_pRequest->GetContentStream());
	}

	m_pConnection->m_pRequest->m_downloadCallback->OnDone();
}

void HttpRequest::ReadResponse()
{
	// Read Response
	StringA* status;
	try
	{
		BufferImp<char> buffer;
		StringBuilder<char> stream(&buffer);
		m_connection->m_pSocket->ReadLine(stream);
		status = buffer.DetachToString();

		// TODO
		if (*status != "HTTP/1.1 200 OK")
		{
			THROW(-1);
		}
	}
	catch(int)
	{
		return;
	}

	while (1)
	{
		BufferImp<char> buffer;
		StringBuilder<char> stream(&buffer);

		m_connection->m_pSocket->ReadLine(stream);
		//if (!strcmp(line.c_str(), ""))
		if (buffer.m_len == 0)
		{
			break;
		}

		//line += "\r\n";
		stream << "\r\n";
		m_headers.AddHeaders(buffer.DetachToString());

	//	headers += line;
	//	headers += "\r\n";
	}

	StringA* contentLengthStr;
	if (contentLengthStr = m_headers.GetHeaderValue(ASTR("Content-Length")))
	{
		long contentLength;
		sscanf(contentLengthStr->c_str(), "%d", &contentLength);

		m_pContentStream->m_contentLength = contentLength;
	}
	//m_pContentStream->m_chunkBytesLeft = m_pContentStream->m_contentLength;

	m_pContentStream->m_transferEncoding = m_headers.GetHeaderValue(ASTR("Transfer-Encoding"));

	m_downloadCallback->OnProgress(this);
}

void HttpRequest::Send()
{
	BufferImp<char> buffer;
	StringBuilder<char> request(&buffer);

	//std::basic_stringstream<char, std::char_traits<char>, myallocator<char> > request;

	request	<< *m_verb << " " << *m_objectName << " HTTP/1.1\r\n"
				<< "Host: " << *m_connection->m_server << "\r\n";

	if (m_additionalHeaders)
		request << *m_additionalHeaders;
	request << "\r\n";

	//std::basic_string<char, std::char_traits<char>, myallocator<char> > requeststr = request.str();

	/*
	DWORD ret = WaitForSingleObject(m_connection->m_pSocket->m_hEvent, 60*1000);
	if (ret == WAIT_TIMEOUT)
		THROW(-1);
		*/

	int nsent = m_connection->m_pSocket->Write((void*)buffer.m_str, buffer.m_len);

#if 0
	//std::stringstream request;

	std::basic_stringstream<char, std::char_traits<char>, myallocator<char> > request;

	request	<< m_verb.c_str() << " " << m_objectName.c_str() << " HTTP/1.1\r\n"
				<< "Host: " << m_connection->m_server.c_str() << "\r\n";

	if (m_additionalHeaders)
		request << m_additionalHeaders.c_str();
	request << "\r\n";

	std::basic_string<char, std::char_traits<char>, myallocator<char> > requeststr = request.str();

	/*
	DWORD ret = WaitForSingleObject(m_connection->m_pSocket->m_hEvent, 60*1000);
	if (ret == WAIT_TIMEOUT)
		THROW(-1);
		*/

	int nsent = m_connection->m_pSocket->Write((void*)requeststr.c_str(), requeststr.length());
#endif

}

/////////////////////////////////////////////////////////////////////////////
// HttpConnection

HttpConnection::HttpConnection(StringA* server, int port)
{
	m_server = server;
	m_port = port;

	m_pSocket = new HttpSocket;
	m_pSocket->m_pConnection = this;

//	m_pSocket->m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_pSocket->Create();
	m_pSocket->Connect(server->c_str(), port);
}

HttpConnection::~HttpConnection()
{
	m_pSocket->Close();
	delete m_pSocket;
}

HttpRequest* HttpConnection::OpenRequest(StringA* verb, StringA* objectName)
{
	HttpRequest* pRequest = new HttpRequest(this, verb, objectName);
	m_pRequest = pRequest;
	return pRequest;
}

/*
class CacheStream : public ISequentialByteStream
{
	ReadFile(m_hFile, 
};

class BlockingStream : public ISequentialByteStream
{
};

ISequentialByteStream* GetBlockingStream(const StringA& url)
{
	StringA scheme;
	StringA server;
	StringA path;

	const char* p = url.c_str();
	StringA str;
	while (*p)
	{
		if (*p == ':')
			break;
		str += *p;
		p++;
	}

	scheme = str;
	p++;	// colon

	if (scheme == "file")
	{
		if (*p != '/') THROW(-1);
		p++;

		if (*p != '/') THROW(-1);
		p++;

		return p;
	}
	else if (scheme == "http")
	{
		if (*p != '/') THROW(-1);
		p++;

		if (*p != '/') THROW(-1);
		p++;

		while (*p)
		{
			if (*p == '/')
				break;
			server += *p;
			p++;
		}

		if (*p != '/') THROW(-1);
		p++;

		path = p;

		StringA tempname = GetTempFilename("C:\\Cache", path.c_str());
	
		FILE* tempfile = fopen(tempname.c_str(), "wb");
		if (tempfile == NULL)
			THROW(-1);

		HttpConnection* pConnection = new HttpConnection(server);
		HttpRequest* pRequest = pConnection->OpenRequest("GET", url.c_str());
		pRequest->Send();

		BYTE buf[512];
		while (1)
		{
			ULONG nRead = pRequest->GetContentStream()->Read(buf, 512);
			if (nRead > 0)
			{
				fwrite(buf, 1, nRead, tempfile);
			}
			if (nRead < 512)
				break;
		}

		delete pConnection;
}
*/

UIEXT StringA* DownloadFile(StringA* url)
{
	ASSERT(0);

#if 0
	StringA scheme;
	StringA server;
	StringA path;

	const char* p = url.c_str();
	StringA str;
	while (*p)
	{
		if (*p == ':')
			break;
		str += *p;
		p++;
	}

	scheme = str;
	p++;	// colon

	if (scheme == "file")
	{
		if (*p != '/') THROW(-1);
		p++;

		if (*p != '/') THROW(-1);
		p++;

		return p;
	}
	else if (scheme == "http")
	{
		if (*p != '/') THROW(-1);
		p++;

		if (*p != '/') THROW(-1);
		p++;

		while (*p)
		{
			if (*p == '/')
				break;
			server += *p;
			p++;
		}

		if (*p != '/') THROW(-1);
		p++;

		path = p;

		StringA tempname = GetTempFilename("C:\\Cache", path.c_str());
	
		FILE* tempfile = fopen(tempname.c_str(), "wb");
		if (tempfile == NULL)
			THROW(-1);

		HttpConnection* pConnection = new HttpConnection(server);
		HttpRequest* pRequest = pConnection->OpenRequest("GET", url.c_str());
		pRequest->Send();

		uint8 buf[512];
		while (1)
		{
			ULONG nRead = pRequest->GetContentStream()->Read(buf, 512);
			if (nRead > 0)
			{
				fwrite(buf, 1, nRead, tempfile);
			}
			if (nRead < 512)
				break;
		}

		delete pConnection;

#if 0
	//	TRACE("%s", headers.c_str());
		//::MessageBox(NULL, headers.c_str(), "", MB_OK);

		std::string transferEncodingStr;
		if (headers.GetHeaderValue("Transfer-Encoding", transferEncodingStr) &&
			strcmp(transferEncodingStr.c_str(), "identity"))
		{
			// chunked

			int size;
			do
			{
				std::string str = pSocket->ReadLine();

				if (sscanf(str.c_str(), "%x", &size) != 1)
					THROW(-1);

				char* buf = new char[size];
				if (size > 0)
				{
					int nRead = pSocket->Read(buf, size);
					//int nRead = recv(m_socket, buf, 256, 0);
					if (nRead > 0)
					{
						fwrite(buf, 1, nRead, tempfile);
					}
				}

				std::string crlf = pSocket->ReadLine();
				ASSERT(!strcmp(crlf.c_str(), ""));
			}
			while (size > 0);
		}
		else
		{
			std::string contentLengthStr;
			if (headers.GetHeaderValue("Content-Length", contentLengthStr))
			{
				long contentLength;
				sscanf(contentLengthStr.c_str(), "%d", &contentLength);

				char* buf = new char[1024];
				long sofar = 0;
				while (sofar < contentLength)
				{
					int len = 1024;
					if (sofar+len > contentLength)
						len = contentLength - sofar;

					int nRead = pSocket->Read(buf, len);

					if (nRead > 0)
					{
						fwrite(buf, 1, nRead, tempfile);
					}

					sofar += nRead;
				}

				delete [] buf;
			}
		}
#endif

		fclose(tempfile);
		tempfile = NULL;

		return tempname;
	}
	else
	{
		return url;
	}
#endif
	return NULL;
}

}
