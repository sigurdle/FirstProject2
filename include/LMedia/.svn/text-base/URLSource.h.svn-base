#ifndef __URLSOURCE_H_
#define __URLSOURCE_H_

//#include "resource.h"       // main symbols

//#include "LMediaImpl.h"

namespace System
{
namespace MediaShow
{

#if 0
class CLByteStream : 
//	public CComObjectRootEx<CComMultiThreadModel>,
	public ILByteStream
{
public:
	CComPtr<IStream> m_stream;

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLByteStream)
	COM_INTERFACE_ENTRY(ILByteStream)
END_COM_MAP()
*/

public:
// ILByteStream
	virtual ErrorCode Read(void *pv, ULONG cb, ULONG *pcbRead)
	{
		return m_stream->Read(pv, cb, pcbRead);
	}
	
	virtual ErrorCode Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
	{
		return m_stream->Seek(dlibMove, dwOrigin, plibNewPosition);
	}

	virtual ErrorCode Clone(ILByteStream* *ppstm)
	{
		CLByteStream* p = new CLByteStream;//>::CreateInstance(&p);

		m_stream->Clone(&p->m_stream);

		*ppstm = p;
//		(*ppstm)->AddRef();

		return S_OK;
	}
};
#endif

class CURLSource : 
	public BaseFilterImpl
{
public:

	class COutputPin : 
		public BasePinImpl,
		public IByteData
	{
	public:
		CTOR COutputPin() : BasePinImpl(PINDIR_OUTPUT)
		{
		}

		inline CURLSource* GetFilter() const
		{
			return (CURLSource*)m_pFilter;
		}

		//CComObject<CVideoSample>* m_pOutSample;

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Stream)
				return Error;

			return 0;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType **pMediaType)
		{
			if (iPosition == 0)
			{
				//ErrorCode hr;

				MediaType* mediaType = new MediaType(LMEDIATYPE_Stream);
				//hr = mediaType.Create();
				//if (FAILED(hr)) return hr;

				//mediaType.SetMajorType(LMEDIATYPE_Stream);

				*pMediaType = mediaType;

				return 0;
			}
			else
			{
				*pMediaType = NULL;
				return 1;
			}
		}

		virtual ULONG Read(void *pv, LONGLONG bytepos, ULONG cb);

		virtual LONGLONG GetSize()
		{
#if 0
			DWORD high;
			DWORD low = GetFileSize(m_pFilter->m_hFile, &high);
			return (LONGLONG)low | ((LONGLONG)high << 32);
#endif
			return GetFilter()->m_FileSize;
		}

		CriticalSection m_lock;
	};

	CTOR CURLSource();

	COutputPin* m_pOutputPin;

#if WIN32

	HANDLE m_hFile;

#elif AMIGA

	long m_hFile;

#elif __APPLE__

	short m_forkRefNum;

#endif

	LONGLONG m_FileSize;

//	ErrorCode LoadFromStream(IStream* stream);

	void SetURL(System::StringW* url);
#if 0
// ILBaseFilter
	STDMETHOD(GetPinCount)(long *pVal)
	{
		*pVal = 1;
		return S_OK;
	}
	STDMETHOD(GetPin)(long index, ILPin* *pVal)
	{
		if (index == 0)
		{
			*pVal = m_pOutputPin;
//			(*pVal)->AddRef();
			return S_OK;
		}
		return E_FAIL;
	}
#endif
};

}	// MediaShow
}

#endif //__URLSOURCE_H_
