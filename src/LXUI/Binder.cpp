#include "stdafx.h"
#include "LXUI2.h"
#include "Binder.h"

extern DECLSPEC_DLLIMPORT long g_locked;
extern DECLSPEC_DLLIMPORT long g_locked2;

namespace System
{
using namespace std;
using namespace IO;

int filecount = 0;

DownloadDocument::DownloadDocument()
{
#if WIN32
	m_hFile = MSWindows::Invalid_Handle_Value;
#else
	m_hFile = NULL;
#endif
	m_pos = 0;

#if WIN32
	m_size = 0xFFFFFFFFFFFFFFFF;	// Unknown size
#else
	m_size = 0xFFFFFFFFFFFFFFFFLL;	// Unknown size
#endif

	m_stream = NULL;

	m_bEOF = false;
}

ULONG DownloadDocument::Read(void* pv, ULONG cb)
{
	uint8* pb = (uint8*)pv;
	ULONG total = 0;

#if WIN32
	while (total < cb)
	{
		ULONG len = cb - total;

		ULONG n;
		try
		{
			n = Read2(pb, len);
		}
		catch(int e)
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
			if (MSWindows::WaitForSingleObject(m_hEvent, 10 * 60 * 1000) != MSWindows::Wait_Object_0)
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

	m_crit.Lock();

	if (m_hFile == MSWindows::Invalid_Handle_Value)
	{
		m_crit.Unlock();
		THROW(-2);	// E_PENDING
	}

	LONGLONG filesize = GetFileSize();

	if (m_pos + cb > filesize)
	{
		cb = filesize - m_pos;
	}
	LONG low = (MSWindows::DWORD)(m_pos);
	LONG high = (MSWindows::DWORD)(m_pos>>32);
	MSWindows::SetFilePointer(m_hFile, low, &high, FILE_BEGIN);
	if (MSWindows::GetLastError() != NO_ERROR)
	{
		m_crit.Unlock();
		return 0;
	}

	ULONG nRead;
	MSWindows::ReadFile(m_hFile, pv, cb, &nRead, NULL);
	m_pos += nRead;

	m_crit.Unlock();

	return nRead;
#endif
	return 0;
}

LONGLONG DownloadDocument::Seek(LONGLONG move, IO::SeekOrigin origin)
{
	m_crit.Lock();

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

	m_crit.Unlock();

	return abspos;
}

LONGLONG DownloadDocument::GetFileSize()
{
#if WIN32
	MSWindows::DWORD high;
	MSWindows::DWORD low = MSWindows::GetFileSize(m_hFile, &high);
	return low | ((LONGLONG)high<<32);
#endif
	return 0;
}

int DownloadDocument::OnProgress(HttpRequest* request)
{
#if WIN32
	m_request = request;

	StringA* contentType = request->m_headers.GetHeaderValue(ASTR("Content-Type"));

//	Control* control;

	m_crit.Lock();

	m_size = request->GetContentStream()->GetSize();
	ASSERT(m_size != 0);

	m_crit.Unlock();

	/*
	if (true)
	{
		m_object = new LXML::CHTMLWindow;
	}

	dynamic_cast<IPersistControl*>(m_object)->Load(ConvertA2S(request->m_objectName));
	dynamic_cast<IDownloadCallback*>(m_object)->OnProgress(request);
	*/

	if (m_callback)
		m_callback->OnObjectAvailable(NULL, m_url->ToStringW());
//	MessageBeep(-1);

#if 0
	m_targetFrame->m_pElement->put_VisualTree(m_targetFrame->m_pFrameContent);
	m_targetFrame->m_pElement->InvalidateArrange();
	m_targetFrame->m_pElement->Arrange(LDraw::SizeD(m_targetFrame->m_pElement->m_computedSize.Width, m_targetFrame->m_pElement->m_computedSize.Height));
#endif

#endif

	return 0;
}

int DownloadDocument::OnDataAvailable(ULONG cbSize, ISequentialByteStream* stream)
{
	// Write the data to disk first

#if WIN32

	m_crit.Lock();

	ASSERT(!m_bEOF);

	MSWindows::DWORD pos = MSWindows::SetFilePointer(m_hFile, 0, NULL, FILE_END);

	uint8 buffer[1024];

	ULONG n = 0;
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
		MSWindows::WriteFile(m_hFile, buffer, nRead, &nWritten, NULL);
		if (nWritten != nRead)
		{
			m_crit.Unlock();
			return -1;
		}

		if (nRead < 1024)
			break;
	}

	m_crit.Unlock();

	MSWindows::SetEvent(m_hEvent);

	//dynamic_cast<IDownloadCallback*>(m_object)->OnDataAvailable(n, this);
	if (m_callback)
		m_callback->OnDataAvailable(n, this);
#endif

	return 0;
}

int DownloadDocument::OnDone()
{
	m_crit.Lock();
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

	m_crit.Unlock();

#if WIN32
	MSWindows::SetEvent(m_hEvent);
#else
	ASSERT(0);
#endif
	if (m_callback)
		return m_callback->OnDone();
	else
		return 0;
}

LONGLONG DownloadDocument::GetSize()
{
	return m_size;
}

//	virtual LONGLONG GetSize() const = 0;
ISequentialByteStream* DownloadDocument::Clone() const
{
	THROW(-1);
	return NULL;
}

ULONG DownloadDocument::Write(const void* pv, ULONG cb)
{
	ASSERT(0);
	THROW(-1);
	return 0;
}

MSWindows::DWORD DownloadDocument_Run(__live_object_ptr<DownloadDocument> download)
{
#if WIN32

	download->m_crit.Lock();

	char localfilename[512];
	sprintf_s(localfilename, "C:/%d", filecount++);
	download->m_hFile = MSWindows::CreateFileA(localfilename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	download->m_crit.Unlock();

	if (download->m_hFile == MSWindows::Invalid_Handle_Value)
	{
		int err = MSWindows::GetLastError();

		if (err == ERROR_SHARING_VIOLATION)
			THROW((int)ERROR_SHARING_VIOLATION);
		else
			THROW(-1);
	}

	try
	{
		HttpConnection* connection = new HttpConnection(download->m_server);
		HttpRequest* request = connection->OpenRequest(ASTR("GET"), download->m_url);
//		request->AddHeaders("Accept: application/xhtml+xml\r\n");
//		request->AddHeaders("Accept: application/xhtml+xml\r\n");

		request->m_downloadCallback = download;
		request->Send();

		MSWindows::MSG msg;
		while (MSWindows::GetMessageA(&msg, NULL, 0, 0))
		{
			MSWindows::TranslateMessage(&msg);

			MSWindows::InterlockedIncrement(&g_locked);
			while (g_locked2) MSWindows::Sleep(1);
			MSWindows::DispatchMessageA(&msg);
			MSWindows::InterlockedDecrement(&g_locked);
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

ISequentialByteStream* UrlBinding::BindToObject(StringW* uri, IBindCallback* callback)
{
	StringA* url = uri->ToStringA();

	printf("Bind: %s\n", url->c_str());

//	Delay(50*5);

	if (strncmp(url->c_str(), "http://", 7) == 0)
	{
		DownloadDocument* downloader = new DownloadDocument;
		downloader->AddRef();
		downloader->m_callback = callback;

		downloader->m_url = url;

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
		downloader->m_hEvent = MSWindows::CreateEventA(NULL, false, false, NULL);

		MSWindows::DWORD threadId;
		MSWindows::CreateThread(NULL, 0, DownloadDocument::DownloadDocumentThread, (LPVOID)downloader, 0, &threadId);
#else
		ASSERT(0);
#endif

		return downloader;
	}
	// TODO
	else if (strncmp(url->c_str(), "inline://", 9) == 0)
	{
		VERIFY(callback == NULL);	// TODO

		return new MemoryByteStream(url->begin() + 9, url->Length()-9);
	}
	else
	{
		const char* p;
		if (strncmp(url->c_str(), "file://", 7) == 0)
		{
			p = url->c_str() + 7;
		}
		else
		{
			p = url->c_str();
		}

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

		if (callback) callback->OnObjectAvailable(NULL, uri);
		FileByteStream* file = new FileByteStream(localfilename);
#if 0
		file->AddRef();
#endif
		if (callback) callback->OnDataAvailable(file->GetSize(), file);
		if (callback) callback->OnDone();

		return file;
	}

	return NULL;
}

}	// System
