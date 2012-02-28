#ifndef __Binder_h_
#define __Binder_h_

#include "http.h"

namespace System
{
namespace Net
{

interface IBindCallback
{
	virtual int OnObjectAvailable(Object* object, StringIn url) = 0;
	virtual int OnDataAvailable(size_t cbSize, IO::Stream* stream) = 0;
	virtual int OnDone() = 0;
};

class NETEXT DownloadDocument : public IO::Stream, public IDownloadCallback//, public System::IO::ISequentialByteStream
{
public:
	CTOR DownloadDocument();

	int OnProgress(HttpRequest* request);
	int OnDataAvailable(size_t cbSize, IO::Stream* stream);
	int OnDone();

//	DWORD Run();

	ULONG Read2(void* pv, ULONG cb);	// non-blocking

	virtual size_t Read(void* pv, size_t cb) override;	// blocking
	virtual uint64 Seek(int64 move, IO::SeekOrigin origin) override;
	virtual uint64 GetSize() override;
	virtual size_t Write(const void* pv, size_t cb) override;

	/*
	bool IsDone()
	{
		m_crit.Lock();
		bool bEOF = m_bEOF;
		m_crit.Unlock();
		return bEOF;
	}
	*/

#if _WIN32
	static ULONG WINAPI DownloadDocumentThread(void* lpData);
#endif

//	Object* m_object;

	CriticalSection m_crit;

	HANDLE m_hEvent;

	String m_url;
	String m_server;
//	LXML::Document* m_document;
	IBindCallback* m_callback;

	HttpRequest* m_request;

	bool m_bEOF;

//	LXML::CHTMLWindow* pBrowser;
	_Ptr<IO::Stream> m_stream;

#if defined(_WIN32)
	HANDLE m_hFile;
#elif defined(AMIGA)
	BPTR m_hFile;
#else
	int m_hFile;
#endif

	ULONGLONG m_size;
	LONGLONG m_pos;

//	HRESULT BindToObject(const sysstring& uri, IBindCallback* callback);

protected:

	uint64 GetFileSize();
};

class NETEXT UrlBinding : public Object
{
public:
	_Ptr<IO::Stream> BindToObject(StringIn uri, IBindCallback* callback);
};

}	// Net
}	// System

#endif // __Binder_h_
