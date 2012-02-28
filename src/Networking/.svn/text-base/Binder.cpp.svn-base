#include "stdafx.h"
#include "LFC/LFC.h"
#include "Binder.h"

//extern DECLSPEC_DLLIMPORT long g_locked;
//extern DECLSPEC_DLLIMPORT long g_locked2;

namespace System
{
namespace Net
{

using namespace std;
using namespace IO;

int filecount = 0;

DownloadDocument::DownloadDocument()
{
#if WIN32
	m_hFile = INVALID_HANDLE_VALUE;
#else
	m_hFile = NULL;
#endif
	m_pos = 0;
	m_size = ~0;	// Unknown size

	m_stream = NULL;

	m_bEOF = false;
}

size_t DownloadDocument::Read(void* pv, size_t cb)
{
	uint8* pb = (uint8*)pv;
	size_t total = 0;

#if WIN32
	while (total < cb)
	{
		size_t len = cb - total;

		size_t n;
		try
		{
			n = Read2(pb, len);
		}
		catch (int e)
		{
			if (e != -2)
				THROW(e);
			n = 0;
		}

		pb += n;
		total += n;

		if (n < len)
		{
			if (m_pos == m_size)
				return total;

#if WIN32
			if (WaitForSingleObject(m_hEvent, 10 * 60 * 1000) != WAIT_OBJECT_0)
				return 0;
#else
			ASSERT(0);
#endif
		}
	}
#else
	ASSERT(0);
#endif

	return total;
}

ULONG DownloadDocument::Read2(void* pv, ULONG cb)
{
#if WIN32

	CriticalSectionLock lock(m_crit);

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
	//	m_crit.Unlock();
		THROW(-2);	// E_PENDING
	}

	LONGLONG filesize = GetFileSize();

	if (m_pos + cb > filesize)
	{
		cb = filesize - m_pos;
	}
	LONG low = (DWORD)(m_pos);
	LONG high = (DWORD)(m_pos>>32);
	SetFilePointer(m_hFile, low, &high, FILE_BEGIN);
	if (GetLastError() != NO_ERROR)
	{
	//	m_crit.Unlock();
		return 0;
	}

	ULONG nRead;
	ReadFile(m_hFile, pv, cb, &nRead, NULL);
	m_pos += nRead;

//	m_crit.Unlock();

	return nRead;
#endif
	return 0;
}

uint64 DownloadDocument::Seek(int64 move, IO::SeekOrigin origin)
{
	CriticalSectionLock lock(m_crit);

	LONGLONG abspos;
	if (origin == System::IO::STREAM_SEEK_SET)
	{
		abspos = move;
	}
	else if (origin == System::IO::STREAM_SEEK_CUR)
	{
		abspos = m_pos + move;
	}
	/*
	else if (origin == System::IO::STREAM_SEEK_END)
	{
		abspos = m_size + move;
	}
	*/
	else
		THROW(-1);

	/*
	LONGLONG filesize = GetFileSize();
	if (abspos > filesize)
	{
		ASSERT(0);
		THROW(-1);
		// TODO, wait for an event
	}
	*/

//	LONG low = (LONG)abspos;
//	LONG high = (LONG)(abspos>>32);

//	low = SetFilePointer(m_hFile, low, &high, FILE_BEGIN);

	m_pos = abspos;//low | ((LONGLONG)high<<32);

//	m_crit.Unlock();

	return abspos;
}

uint64 DownloadDocument::GetFileSize()
{
#if WIN32
	DWORD high;
	DWORD low = ::GetFileSize(m_hFile, &high);
	return low | ((int64)high<<32);
#endif
	return 0;
}

int DownloadDocument::OnProgress(HttpRequest* request)
{
#if WIN32
	m_request = request;

	String contentType = request->m_responseHeaders.GetHeaderValue("Content-Type");

//	Control* control;

	{
		CriticalSectionLock lock(m_crit);

		m_size = request->GetContentStream()->GetSize();
		ASSERT(m_size != 0);
	}

	/*
	if (true)
	{
		m_object = new LXML::CHTMLWindow;
	}

	dynamic_cast<IPersistControl*>(m_object)->Load(ConvertA2S(request->m_objectName));
	dynamic_cast<IDownloadCallback*>(m_object)->OnProgress(request);
	*/

	if (m_callback)
		m_callback->OnObjectAvailable(NULL, m_url);
//	MessageBeep(-1);

#if 0
	m_targetFrame->m_pElement->put_VisualTree(m_targetFrame->m_pFrameContent);
	m_targetFrame->m_pElement->InvalidateArrange();
	m_targetFrame->m_pElement->Arrange(LDraw::SizeD(m_targetFrame->m_pElement->m_computedSize.Width, m_targetFrame->m_pElement->m_computedSize.Height));
#endif

#endif

	return 0;
}

int DownloadDocument::OnDataAvailable(size_t cbSize, IO::Stream* stream)
{
	// Write the data to disk first

#if WIN32

	ULONG n = 0;
	{
		CriticalSectionLock lock(m_crit);

		ASSERT(!m_bEOF);

		DWORD pos = SetFilePointer(m_hFile, 0, NULL, FILE_END);

		uint8 buffer[1024];

		while (1)//n < cbSize)
		{
			ULONG nRead;
			
			try
			{
				nRead = stream->Read(buffer, 1024);
			}
			catch(int)
			{
				nRead = 0;
			}

			n += nRead;

			ULONG nWritten;
			WriteFile(m_hFile, buffer, nRead, &nWritten, NULL);
			if (nWritten != nRead)
			{
			//	m_crit.Unlock();
				return -1;
			}

			if (nRead < 1024)
				break;
		}

//	m_crit.Unlock();
	}

	SetEvent(m_hEvent);

	//dynamic_cast<IDownloadCallback*>(m_object)->OnDataAvailable(n, this);
	if (m_callback)
		m_callback->OnDataAvailable(n, this);
#endif

	return 0;
}

int DownloadDocument::OnDone()
{
	{
		CriticalSectionLock lock(m_crit);
		ASSERT(!m_bEOF);
		m_bEOF = true;

	//	LONGLONG size = m_request->GetContentStream()->GetSize();

		m_size = GetFileSize();

		/*
		try
		{
			char buf[64];
			ULONG n = m_request->GetContentStream()->Read(buf, 64);
			ASSERT(n == 0);
		}
		catch(int)
		{
		}
		*/

		//ASSERT(m_size != 0);

	}

#if WIN32
	SetEvent(m_hEvent);
#else
	ASSERT(0);
#endif
	if (m_callback)
		return m_callback->OnDone();
	else
		return 0;
}

uint64 DownloadDocument::GetSize()
{
	return m_size;
}

/*
//	virtual LONGLONG GetSize() const = 0;
ISequentialByteStream* DownloadDocument::Clone() const
{
	THROW(-1);
	return NULL;
}
*/

size_t DownloadDocument::Write(const void* pv, size_t cb)
{
	ASSERT(0);
	raise(Exception());
	return 0;
}

DWORD DownloadDocument_Run(DownloadDocument* download)
{
#if WIN32

	{
		CriticalSectionLock lock(download->m_crit);

		char localfilename[512];
		sprintf_s(localfilename, "C:/%d", filecount++);
		download->m_hFile = CreateFileA(localfilename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	if (download->m_hFile == INVALID_HANDLE_VALUE)
	{
		int err = GetLastError();

		if (err == ERROR_SHARING_VIOLATION)
			THROW((int)ERROR_SHARING_VIOLATION);
		else
			THROW(-1);
	}

	try
	{
		HttpConnection* connection = new HttpConnection(download->m_server);
		HttpRequest* request = connection->OpenRequest("GET", download->m_url);
//		request->AddHeaders("Accept: application/xhtml+xml\r\n");
//		request->AddHeaders("Accept: application/xhtml+xml\r\n");

		request->m_downloadCallback = download;
		request->Send();

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);

		//	MSWindows::InterlockedIncrement(&g_locked);
		//	while (g_locked2) MSWindows::Sleep(1);
			DispatchMessage(&msg);
		//	MSWindows::InterlockedDecrement(&g_locked);
		}

#if 0
	//	if (content

		m_stream = request->GetContentStream();

		m_document->m_uri = ConvertA2S(m_url);
		m_document->m_pWindow = pBrowser;
		dynamic_cast<LHTML::CLHTMLDocument*>(m_document)->loadDefaultStylesheet();
		bool success = m_document->load(m_stream);
#endif
	}
	catch(int)
	{
		return -1;
	}

#if 0
	m_targetFrame->OnDocumentReady(this);
#endif
#endif
	return 0;
}

#if WIN32

ULONG WINAPI DownloadDocument::DownloadDocumentThread(LPVOID lpData)
{
	return DownloadDocument_Run((DownloadDocument*)lpData);
}

#endif

_Ptr<IO::Stream> UrlBinding::BindToObject(StringIn uri, IBindCallback* callback)
{
//	String url = uri;//->ToStringA();

//	printf("Bind: %s\n", url->c_str());

//	Delay(50*5);

	if (uri.LeftOf(7) == "http://")
	{
		ASSERT(0);
		return NULL;
#if 0
		DownloadDocument* downloader = new DownloadDocument;
		downloader->AddRef();
		downloader->m_callback = callback;

		downloader->m_url = uri;

		const char* p = url->c_str() + 7;
		const char* p2 = strchr(p, '/');
		if (p2 == NULL)
		{
			downloader->m_server = new StringA(string_copy(p));
		}
		else
		{
			downloader->m_server = new StringA(string_copy(p, p2-p));
		}

#if WIN32
		downloader->m_hEvent = CreateEvent(NULL, false, false, NULL);

		DWORD threadId;
		::CreateThread(NULL, 0, DownloadDocument::DownloadDocumentThread, (LPVOID)downloader, 0, &threadId);
#else
		ASSERT(0);
#endif

		return downloader;
#endif
	}
	// TODO
	else if (uri.LeftOf(9) == "inline://")
	{
		VERIFY(callback == NULL);	// TODO

		ASSERT(0);
		return NULL;
	//	return new IO::StringReader(String(uri.RightOf(9)));
		//return new MemoryByteStream(String(uri.RightOf(9)).GetData8(), uri.GetLength()-9);
	}
	else
	{
		String localfilename;

	//	const char* p;
		if (uri.LeftOf(7) == "file://")
		{
			localfilename = uri.RightOf(7);
		}
		else
		{
			localfilename = uri;
		}

#if 0
		BufferImp<char> buffer;
		StringBuilderA strbuilder(&buffer);
		while (*p)
		{
			if (*p == '%')
			{
				// TODO improve
				p += 3;
				// 20 is space
				strbuilder << ' ';
			}
			else
			{
				strbuilder << *p++;
			}
		}
		StringA* localfilename = buffer.DetachToString();
#endif

		if (callback) callback->OnObjectAvailable(NULL, uri);
		IO::FileStream* file = new IO::FileStream(localfilename, IO::FileMode_Open, IO::FileAccess_Read);

		if (callback) callback->OnDataAvailable(file->GetSize(), file);
		if (callback) callback->OnDone();

		return file;
	}

	return NULL;
}

}	// Net
}	// System
