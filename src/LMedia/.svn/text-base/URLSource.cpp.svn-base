#include "stdafx.h"
#include "LMediaImpl.h"
#include "URLSource.h"

#if AMIGA
#include "../amiga_header.h"
#endif

namespace System
{
namespace MediaShow
{

CURLSource::CURLSource()
{
	m_pOutputPin = new COutputPin;
	m_pOutputPin->m_pFilter = this;
	m_pOutputPin->m_id = WSTR("Stream Output");
	AddPin(m_pOutputPin);
}

#if 0
int CURLSource::FinalConstruct()
{
	HRESULT hr;

	hr = CLBaseFilterImpl::FinalConstruct();
	if (FAILED(hr)) return hr;

	CComObject<COutputPin>::CreateInstance(&m_pOutputPin);
	m_pOutputPin->AddRef();
	m_pOutputPin->m_pFilter = this;
	m_pOutputPin->m_id = L"Stream Output";
	AddPin(m_pOutputPin);

	return 0;
}

void CURLSource::FinalRelease()
{
	if (m_pOutputPin)
	{
		m_pOutputPin->Release();
		m_pOutputPin = NULL;
	}

	CLBaseFilterImpl::FinalRelease();
}
#endif

void CURLSource::SetURL(StringW* url)
{
#if WIN32

	m_hFile = CreateFileW(CStringw(url).c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
		THROW(-1);

	DWORD high;
	DWORD low = GetFileSize(m_hFile, &high);
	m_FileSize = (LONGLONG)low | ((LONGLONG)high << 32);

#elif AMIGA

	StringA* urla = url->ToStringA();

	m_hFile = dosOpen(DOSBase, urla->c_str(), MODE_OLDFILE);
	if (m_hFile == NULL)
		THROW(-1);

//	__aligned FileInfoBlock fib;
	__attribute__((aligned(8))) FileInfoBlock fib;
	if (dosExamineFH(DOSBase, m_hFile, &fib))
	{
		m_FileSize = fib.fib_Size;
	}
	else
		THROW(-1);

#endif

	/*
	m_buffer = new uint8[m_FileSize];

	ULONG nRead;
	ReadFile(m_hFile, m_buffer, m_FileSize, &nRead, NULL);
	*/

#if 0
	USES_CONVERSION;

	if (m_pFilterGraph == NULL)
		return E_UNEXPECTED;

	HRESULT hr;

	CComPtr<IStream> stream;
	hr = URLOpenBlockingStream(0, W2A(url), &stream, 0, 0);
	if (SUCCEEDED(hr))
	{
		ATLASSERT(0);
	//;	LoadFromStream(stream);
	}
#endif
}

/*
//"75B22630-668E-11CF-A6D9-00AA0062CE6C"
static const GUID ASFHeaderUID = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };
*/

#if 0
HRESULT CURLSource::LoadFromStream(IStream* stream)
{
	//USES_CONVERSION;

	if (m_pFilterGraph == NULL)
		return E_UNEXPECTED;

//	HRESULT hr;

	m_stream = stream;

	return S_OK;

#if 0
	ULONG nRead;

	CComPtr<ILBaseFilter> parser;

	// Read 16 first bytes of file
	BYTE buf[16];
	hr = m_stream->Read(buf, 16, &nRead);
	if (nRead >= 4)
	{
		// Set back to beginning
		LARGE_INTEGER li;
		li.QuadPart = 0;
		m_stream->Seek(li, System::IO::STREAM_SEEK_SET, NULL);

		if (*(DWORD*)buf == 0x4d524f46/*'FORM'*/)	// IFF
		{
			hr = parser.CoCreateInstance(L"IFF.IFFDecoder");
		}
		else if (*(DWORD*)buf == 0x646e732e/*.snd*/)	// SunAU
		{
			hr = parser.CoCreateInstance(L"SunAU.AUDecoder");
		}
		else if (*(DWORD*)buf == 0x38464947/*'GIF8'*/)	// GIF
		{
			hr = parser.CoCreateInstance(L"GIF.GIFDecoder");
		}
		else if (*(DWORD*)buf == 0x002a4949 || *(DWORD*)buf == 0x2a004d4d)	// TIFF
		{
			hr = parser.CoCreateInstance(L"TIFF.TIFFDecoder");
		}
		else if (((*(DWORD*)buf>>0)&0xff) == 10 &&	// magic
					(((*(DWORD*)buf>>8)&0xff) == 0 || ((*(DWORD*)buf>>8)&0xff) == 2 || ((*(DWORD*)buf>>8)&0xff) == 3 || ((*(DWORD*)buf>>8)&0xff) == 4 || ((*(DWORD*)buf>>8)&0xff) == 5) &&	// version
					((*(DWORD*)buf>>16)&0xff) == 1)	// encoding
		{
			hr = parser.CoCreateInstance(L"PCX.PCXDecoder");
		}
		//else if (value == 0x61657243/*'Crea'*/) //tive Voice
		else if (!memcmp(buf, "Creative Voice", 14))
		{
			hr = parser.CoCreateInstance(L"VOC.VOCDecoder");
		}
		else if ((*(DWORD*)buf & 0xffff) == 0xd8ff) // JPEG
		{
			hr = parser.CoCreateInstance(L"JPEG.JPEGDecoder");
		}
		else if (((DWORD*)buf)[0] == 0x474e5089 && ((DWORD*)buf)[1] == 0x0a1a0a0d) // PNG
		{
			hr = parser.CoCreateInstance(L"PNG.PNGDecoder");
		}
		else if (*(DWORD*)buf == 0xba010000)	// MPEG systems
		{
			hr = parser.CoCreateInstance(L"MPEG.MPEGDecoder");
		}
		else if (*(DWORD*)buf == 0xb3010000)	// MPEG video
		{
			hr = parser.CoCreateInstance(L"LMPEGVideo.LMPEGVideoDecoder");
		}
		else if (*(DWORD*)buf & 0xfff == 0xfff	/*TODO, check if this is correct*/)	// could be MPEG Audio
		{
			hr = parser.CoCreateInstance(L"LMPEGAudio.LMPEGAudioDecoder");
		}
		else if (*(DWORD*)buf == 0x00010000) // MPEG4 Video stream??
		{
			hr = parser.CoCreateInstance(L"LMPEG4.VideoDecoder");
		}
		else if (*(GUID*)buf == ASFHeaderUID)
		{
			hr = parser.CoCreateInstance(L"LASF.ASFLoader");
		}
		else if (((DWORD*)buf)[0] == 0x46464952/*RIFF*/ && ((DWORD*)buf)[2] == 0x20495641/*AVI */)
		{
			hr = parser.CoCreateInstance(L"LAVI.LAVIFile");
		}
		else if (((DWORD*)buf)[0] == 0x46464952/*RIFF*/ && ((DWORD*)buf)[2] == 0x45564157/*WAVE*/)
		{
			hr = parser.CoCreateInstance(L"LAVI.LAVIFile");
		}
		else// TODO ftyp??? moov.. ???
		{
			hr = parser.CoCreateInstance(L"LMPEG4.MP4File");
		}

		if (SUCCEEDED(hr))
		{
		// Add the parser to the movies filter graph
			m_pFilterGraph->AddFilter(parser);

		// Connect the parsers input pin to our output pin
			ILPin* pin;
			parser->GetPin(0, &pin);
			hr = m_pOutputPin->Connect(pin, NULL);
		}
	}

	return hr;
#endif
}
#endif

ULONG CURLSource::COutputPin::Read(void *pv, LONGLONG bytepos, ULONG cb)
{
#if WIN32
	LONG low = (LONG)bytepos;
	LONG high = (LONG)(bytepos >> 32);

	CriticalSectionLock lock(m_lock);

	HANDLE hFile = GetFilter()->m_hFile;

	SetFilePointer(hFile, low, &high, FILE_BEGIN);

	ULONG nRead;
	if (ReadFile(hFile, pv, cb, &nRead, NULL) == 0)
	{
		raise(IO::IOException());
	}

	return nRead;

#elif AMIGA

	LONG low = (LONG)bytepos;
	LONG high = (LONG)(bytepos >> 32);
	if (high != 0)
		THROW(-1);

	m_lock.Lock();

	dosSeek(DOSBase, GetFilter()->m_hFile, low, OFFSET_BEGINNING);
	ULONG nRead = dosRead(DOSBase, GetFilter()->m_hFile, pv, cb);

	m_lock.Unlock();

	return nRead;

#elif __APPLE__

	ASSERT(0);
	return 0;
#endif

	/*
	if (bytepos + cb > m_pFilter->m_FileSize)
		cb = m_pFilter->m_FileSize - bytepos;

	memcpy(pv, m_pFilter->m_buffer+bytepos, cb);
	return cb;
	*/
}

}	// MediaShow
}	// System
