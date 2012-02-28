#ifndef __HTTP_H
#define __HTTP_H

#include "Socket.h"
#include "HttpHeaders.h"

namespace System
{
namespace Net
{

class HttpRequest;

interface IDownloadCallback
{
	virtual int OnProgress(HttpRequest* request) = 0;
	virtual int OnDataAvailable(ULONG cbSize, IO::Stream* stream) = 0;
	virtual int OnDone() = 0;
};

class HttpConnection;
class HttpRequest;

class NETEXT HttpContentStream : public IO::Stream
{
public:
	CTOR HttpContentStream(HttpRequest* pRequest);
	~HttpContentStream();

	virtual size_t Read(void* pv, size_t cb) override;
	virtual uint64 Seek(int64 offset, IO::SeekOrigin origin) override;
	virtual uint64 GetSize() override;
//	virtual LONGLONG GetSize() const;
//	virtual IO::ISequentialByteStream* Clone() const;

	virtual size_t Write(const void* pv, size_t cb) override;

	virtual uint64 GetPosition() override
	{
		return m_pos;
	}

	uint64 m_contentLength;
	String m_transferEncoding;

protected:

	friend class HttpRequest;

	HttpRequest* m_pRequest;
	uint64 m_pos;
	uint64 m_chunkBytesLeft;
};

class NETEXT HttpRequest : public Object
{
public:
	CTOR HttpRequest(HttpConnection* connection, StringIn verb, StringIn objectName);

	void AddHeader(StringIn field, StringIn value);
	void AddHeaders(StringIn str);
	void Send();

	HttpContentStream* GetContentStream();
	void ReadResponse();

	Event1<int> m_stateChanged;

public:

//	String m_additionalHeaders;
	String m_verb;
	String m_objectName;
	String m_status;
	HttpHeaders m_requestHeaders;
	HttpHeaders m_responseHeaders;

	IDownloadCallback* m_downloadCallback;
	HttpContentStream* m_pContentStream;

protected:

	friend class HttpContentStream;

	HttpConnection* m_connection;
};

class NETEXT HttpConnection : public Object
{
public:
	CTOR HttpConnection(StringIn server, int port = 80);
	~HttpConnection();

	/*
	enum
	{
		HTTP_VERB_POST = 0 ,
		HTTP_VERB_GET = 1 ,
		HTTP_VERB_HEAD = 2 ,
		HTTP_VERB_PUT = 3 ,
		HTTP_VERB_LINK = 4 ,
		HTTP_VERB_DELETE = 5 ,
		HTTP_VERB_UNLINK = 6,
	};
	*/

	HttpRequest* m_pRequest;

	HttpRequest* OpenRequest(StringIn verb, StringIn objectName);

protected:

	friend class HttpRequest;
	friend class HttpContentStream;

	class HttpSocket : public AsyncSocket
	{
	public:
		CTOR HttpSocket(HttpConnection* connection);

		virtual void OnConnect(int nErrorCode);
		virtual void OnClose(int nErrorCode);
		virtual void OnReceive(int nErrorCode);
		virtual void OnSend(int nErrorCode);

		IO::TextWriter& ReadLine(IO::TextWriter& stream);
		String ReadLine();

		HttpConnection* m_pConnection;
		//HANDLE m_hEvent;
		int64 m_sofar;
		int m_state;
		bool m_bDone;
	};

	HttpSocket* m_pSocket;
	String m_server;
	int m_port;
};

NETEXT String DownloadFile(String url);

}	// Net
}	// System

#endif // __HTTP_H
