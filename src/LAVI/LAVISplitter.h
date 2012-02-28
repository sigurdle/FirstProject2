// LAVISplitter.h : Declaration of the AVISplitter

#ifndef __LAVISPLITTER_H_
#define __LAVISPLITTER_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Media
{

#if 0
class CMemAllocator;

class CBuffer
{
public:
	CBuffer()
	{
		m_bFree = TRUE;
		m_pMemAllocator = NULL;

		m_pointer = NULL;
		m_dwBytes = 0;
		m_dwActualBytes = 0;
	}

	~CBuffer()
	{
		if (m_pointer)
		{
			GlobalFree(m_pointer);
			m_pointer = NULL;
		}
	}

	BOOL m_bFree;
	CMemAllocator* m_pMemAllocator;

	LPBYTE m_pointer;
	DWORD m_dwBytes;
	DWORD m_dwActualBytes;
};

class ATL_NO_VTABLE CSample : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CLMediaSampleImpl<ILMediaSample>
{
public:
	CSample()
	{
		m_mediaType = NULL;
		m_pBuffer = NULL;
	}

	void FinalRelease()
	{
		if (m_pBuffer)
		{
			m_pBuffer->m_pMemAllocator->ReleaseBuffer(this);
		}
	}

	CBuffer* m_pBuffer;

	//CInputPin* m_pInput;
	ILMediaType* m_mediaType;

public:
	STDMETHOD(LockBits)(LSampleData* pVal)
	{
		if (m_pBuffer)
		{
			pVal->idata = m_pBuffer->m_pointer;
			return S_OK;
		}
		else
		{
			ATLASSERT(0);
			return E_FAIL;
		}
	}

	STDMETHOD(UnlockBits)()
	{
		if (m_pBuffer)
		{
			return S_OK;
		}
		else
		{
			ATLASSERT(0);
			return E_FAIL;
		}
	}

	STDMETHOD(GetMediaType)(ILMediaType **pVal)
	{
		*pVal = m_mediaType;
		(*pVal)->AddRef();
		return S_OK;
	}

	virtual ULONG __stdcall GetActualDataLength()
	{
		if (m_pBuffer)
		{
			return m_pBuffer->m_dwBytes;
		}
		else
		{
			ATLASSERT(0);
			return 0;
		}
	}
	virtual ErrorCode __stdcall SetActualDataLength(ULONG length)
	{
		if (m_pBuffer)
		{
			if (length > m_pBuffer->m_dwBytes)
			{
				return VFW_E_BUFFER_OVERFLOW;
			}

			m_pBuffer->m_dwActualBytes = length;

			return S_OK;
		}
		else
		{
			ATLASSERT(0);
			return E_FAIL;
		}
	}
};

class ATL_NO_VTABLE CMemAllocator : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILMemAllocator
{
public:
	CMemAllocator()
	{
		m_pInputPin = NULL;
	}

//	CInputPin* m_pInputPin;

	CArray<CBuffer*,CBuffer*> m_buffers;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMemAllocator)
	COM_INTERFACE_ENTRY(ILMemAllocator)
END_COM_MAP()

public:
	STDMETHOD(GetBuffer)(DWORD dwBytes, ILMediaSample* *pVal)
	{
#if 0
		EnterCriticalSection(&m_pInputPin->m_pLock);
#endif

		CComObject<CSample>* pSample;
		CComObject<CSample>::CreateInstance(&pSample);
		pSample->AddRef();

		/*
		for (int i = 0; i < m_buffers.GetSize(); i++)
		{
			if (m_buffers[i]->m_bFree)
			{
				m_buffers[i]->m_bFree = FALSE;
				pSample->m_pBuffer = m_buffers[i];

				*pVal = pSample;

				LeaveCriticalSection(&m_pInputPin->m_pLock);

				return S_OK;
			}
		}
		*/

		CBuffer* pBuffer = new CBuffer;
		pBuffer->m_pMemAllocator = this;
		pBuffer->m_bFree = FALSE;
		m_buffers.Add(pBuffer);

		pBuffer->m_pointer = (LPBYTE)GlobalAlloc(0, dwBytes);
		pBuffer->m_dwBytes = dwBytes;

		pSample->m_pBuffer = pBuffer;

		*pVal = pSample;

#if 0
		LeaveCriticalSection(&m_pInputPin->m_pLock);
#endif

		return S_OK;
	}

	STDMETHOD(ReleaseBuffer)(ILMediaSample* pBuffer)
	{
		CSample* pSample = static_cast<CSample*>(pBuffer);
		ATLASSERT(pSample->m_pBuffer->m_bFree == FALSE);

		pSample->m_pBuffer->m_bFree = TRUE;
		pSample->m_pBuffer = NULL;

		return S_OK;
	}
};
#endif

class CChunkEntry
{
public:
	CChunkEntry()
	{
		m_chunkLength = 0;
	}

	~CChunkEntry()
	{
	}

	ULONGLONG m_chunkOffset;
	ULONG m_chunkLength;
	uint32 m_flags;
};

class AVISplitter;

class CBufferedSample
{
public:
	int m_nSample;
	IMediaSample* m_sample;
};

/*
struct IndexEntry
{
	ULONG offset;
	ULONG size;
	ULONG flags;
};
*/

class CAVIStream
{
public:
	CAVIStream()
	{
		m_pavifile = NULL;
		memset(&m_aviStreamHeader, 0, sizeof(m_aviStreamHeader));

		m_outputPin = NULL;
	}

	AVISplitter* m_pavifile;
	AVIStreamHeader m_aviStreamHeader;
	vector<CChunkEntry> m_sampleEntries;

	vector<CBufferedSample*> m_bufferedSamples;

//	std::vector<IndexEntry> m_entries;

//	DWORD m_threadId;
//	HANDLE m_hThread;

	//ILPin* m_outputPin;
	BaseOutputPinImpl* m_outputPin;

	//CComPtr<ILMemAllocator> m_allocator;

//	ErrorCode GetDataSize(long n, ULONG *pVal);
//	ULONG ReadData(long n, LPBYTE buffer, ULONG size);
	ErrorCode GetSample(long n, IMediaSample* *pVal);
};

class AVISplitter :
	public BaseFilterImpl	// IMediaFilter
{
public:
	class CInputPin : 
		public BasePinImpl
	{
	public:
		CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
		}

		virtual ErrorCode CheckConnect(IPin* pPin)
		{
			// Call base class first
			ErrorCode hr = BasePinImpl::CheckConnect(pPin);
			if (hr < 0) return hr;

			IByteData* stream = dynamic_cast<IByteData*>(pPin);
			if (stream == NULL) return E_NOINTERFACE;

			GetFilter()->m_stream = new ByteStreamWrapper(stream);

			return Success;
		}

		virtual void BreakConnect()
		{
			// Release what we obtained in CheckConnect
			GetFilter()->m_stream = NULL;
		}

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Stream)
				return E_FAIL;

			return Success;
		}

		virtual ErrorCode CompleteConnect(IPin *pPin);

		inline AVISplitter* GetFilter() const
		{
			return (AVISplitter*)m_pFilter;
		}
	};

	AVISplitter()
	{
		m_pInputPin = NULL;

		memset(&m_mainAVIHeader, 0, sizeof(m_mainAVIHeader));
		m_movieOffset = 0;

	//	m_fmtsize = 0;
	//	m_fmtbuffer = NULL;

		m_pInputPin = new CInputPin;
		m_pInputPin->m_pFilter = this;
		m_pInputPin->m_id = WSTR("Stream Input");
		AddPin(m_pInputPin);
	}

	~AVISplitter()
	{
		for (int i = 0; i < m_streams.GetSize(); i++)
		{
			delete m_streams[i];
		}
		m_streams.RemoveAll();

	}

	System::IO::ISequentialByteStream* m_stream;
	CInputPin* m_pInputPin;

	MainAVIHeader m_mainAVIHeader;
	ULONGLONG m_movieOffset;	// Offset of 'movi' chunk

	ErrorCode ReadAVI();

	vector<CAVIStream*> m_streams;

	ErrorCode ReadNext(CAVIStream* p, int n);
	ErrorCode ReadChunkData(IMediaSample* sample, ULONG size);

};

}	// Media
}

#endif //__LAVISPLITTER_H_
