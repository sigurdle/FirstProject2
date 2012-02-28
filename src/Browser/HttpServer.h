#pragma once

#include "../LFC/Socket.h"
#include "../LXUI/HttpHeaders.h"

#if 0
#include <sstream>
#endif

namespace System
{

class HTTPClientSocket : public AsyncSocket
{
public:

	HTTPClientSocket()
	{
		m_state = 0;
		m_fp = NULL;
	}

	System::StringA m_request;
	System::StringA m_requestline;
	HttpHeaders	m_headers;

	System::StringA m_objectName;
	System::StringA m_filepart;
	map<System::StringA, System::StringA> m_querymap;

	std::FILE* m_fp;

	int m_state;

	virtual void OnConnect()
	{
		TRACE("OnConnect\n");
	}

	virtual void OnClose()
	{
		TRACE("OnClose\n");
	}

	void ParseRequest()
	{
		ASSERT(0);
#if 0

		const char* p = m_request->c_str();
		while (*p)
		{
			if (p[0] == '\r' && p[1] == '\n')
			{
				break;
			}
			m_requestline = m_requestline->Append(*p++);
		}
		if (p[0] != '\r' || p[1] != '\n')
		{
			Close();
			return;
		}
		p += 2;
		/*
		try
		{
			m_request = ReadLine();
		}
		catch(int)
		{
			return;
		}*/

		System::StringA verb;
		System::StringA httpVer;

		{
			const char* p = m_requestline.c_str();

			while (*p && *p != ' ') verb += *p++;
			while (*p == ' ') p++;

			while (*p && *p != ' ') m_objectName += *p++;
			while (*p == ' ') p++;

			while (*p && *p != ' ') httpVer += *p++;

			{
				int i = m_objectName.Find('?');
				if (i)
				{
					const char* p = m_objectName.c_str() + i;
					while (*p)
					{
						System::StringA key;

						while (*p)
						{
							if (*p == '=') break;
							key += *p++;
						}
						p++;

						System::StringA value;
						while (*p)
						{
							if (*p == '&') break;
							key += *p++;
						}
						p++;

						m_querymap[key] = value;
					}
				}
			}
		}

		while (1)
		{
			System::StringA line;
			while (*p)
			{
				if (p[0] == '\r' && p[1] == '\n')
				{
					break;
				}
				line += *p++;
			}

			p += 2;

			if (line == "")
			{
				break;
			}

			m_headers.AddHeaders(line += "\r\n");

		//	headers += line;
		//	headers += "\r\n";
		}

		/*
		std::string contentLengthStr;
		if (m_headers.GetHeaderValue("Content-Length", contentLengthStr))
		{
			long contentLength;
			sscanf(contentLengthStr.c_str(), "%d", &contentLength);

			m_pContentStream->m_contentLength = contentLength;
		}
		*/
		//m_pContentStream->m_chunkBytesLeft = m_pContentStream->m_contentLength;

//		m_headers.GetHeaderValue("Transfer-Encoding", m_pContentStream->m_transferEncoding);
//		m_downloadCallback->OnProgress(this);
#endif
	}

	virtual void OnReceive(int nErrorCode)
	{
		ASSERT(0);
#if 0
		//ReadRequest();
		TRACE("OnRead\n");

		if (m_state == 0)
		{
			char buf[512];
			while (1)
			{
				int nRead = Receive(buf, 512);

				for (int i = 0; i < nRead; i++)
				{
					TRACE("%c", buf[i]);
				}

				m_request += buf;
				if (m_request.length() >= 3)
				{
					if (strncmp(m_request.c_str(), "GET", 3))
					{
						Close();
						return;
					}
				}

				if (nRead < 512)
					break;
			}

			if (m_request.Find("\r\n\r\n") != -1)
			{
				ParseRequest();

				SendResponse();
			}
		}
		else
		{
			Close();
		}
#endif
	}

	void SendResponse()
	{
		ASSERT(0);
#if 0
		System::StringA filename = "C:/VirtualDir";
		filename += m_objectName;

		m_fp = fopen(filename.c_str(), "r");
		if (m_fp)
		{
			fseek(m_fp, 0, SEEK_END);
			long size = ftell(m_fp);
			rewind(m_fp);

			ASSERT(0);

#if 0

			std::stringstream response;
			response	<< "HTTP/1.1 200 OK\r\n"
						<< "Content-Type: text/html\r\n"
						<< "Content-Length: " << size << "\r\n"
						<< "\r\n";

			std::string responsestr = response.str();

			int nSent = Send(responsestr.c_str(), responsestr.length());

#endif

			WriteFileContent();

			fclose(m_fp);
			m_fp = NULL;

	//		m_state = 2;
			m_state = -1;
			Close();
		}
		else
		{
			ASSERT(0);
#if 0
			std::stringstream response;
			response	<< "HTTP/1.1 404 Not Found\r\n"
						<< "Content-Type: text/html\r\n"
						<< "Content-Length: " << 9 << "\r\n"
						<< "\r\n"
						<<	"Not found";

			std::string responsestr = response.str();

			int nSent = Send(responsestr.c_str(), responsestr.length());
#endif
			m_state = -1;
			Close();
		}
#endif
	}

	void WriteFileContent()
	{
		char buf[512];
		while (1)
		{
			int nRead = std::fread(buf, 1, 512, m_fp);
			Send(buf, nRead);
			if (nRead < 512)
				break;
		}

		/*
		if (m_headers.GetHeaderValue("Connection") == "Keep-Alive")
		{
			m_state = 0;	// Ready for new requests
		}
		else
		*/
		{
		}
	}

	virtual void OnWrite()
	{
		TRACE("OnWrite\n");

		if (m_state == 2)
		{
		}
		else
		{
		//	Close();
		}
	}
};

class HTTPListenerSocket : public AsyncSocket
{
public:
	virtual void OnAccept(int nErrorCode)
	{
		HTTPClientSocket* pSocket = new HTTPClientSocket;
		Accept(pSocket);
		if (pSocket->m_socket != INVALID_SOCKET)
		{
		}
		else
			delete pSocket;

		TRACE("OnAccept %d\n", (int)pSocket->m_socket);
	}

	virtual void OnConnect(int nErrorCode)
	{
		TRACE("OnConnect\n");
	}

	virtual void OnClose(int nErrorCode)
	{
		TRACE("OnClose\n");
	}

	virtual void OnReceive(int nErrorCode)
	{
		TRACE("OnReceive\n");

		char buf[512];
		int nRead = Receive(buf, 512);

	//	::MessageBox(NULL, buf, NULL, MB_OK);
	}

	virtual void OnSend(int nErrorCode)
	{
		TRACE("OnSend\n");
	}
};

}
