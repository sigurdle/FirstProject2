#ifndef __BIFSDECODER_H_
#define __BIFSDECODER_H_

namespace System
{
namespace MediaShow
{

//	class BIFSDec;

/*
class CStatementBlock;
class CStatement;
class CIfStatement;
class CForStatement;
class CScriptItem;
class CLScriptEngine;

#include "Param.h"
#include "Nodes.h"
*/


class CBIFSDecoder : 
	//public IBIFSDecoder,
	public BaseFilterImpl	// ILMediaFilter
{
public:

	class CInputPin : 
		public BasePinImpl
	{
	public:
		CTOR CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
		}

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Stream)
				return Error;

			return Success;
		}

		inline CBIFSDecoder* GetFilter() const
		{
			return (CBIFSDecoder*)m_pFilter;
		}

	/*
	CheckConnect()
			CComQIPtr<ILByteStream> stream = m_connectedTo;
			if (stream == NULL) return E_NOINTERFACE;

			m_pFilter->m_stream = stream;
			*/

		ErrorCode CompleteConnect(IPin* pPin)
		{
			ErrorCode hr;
			hr = BasePinImpl::CompleteConnect(pPin);
			if (hr < 0) return hr;

			/*
			ATLASSERT(m_pFilter->m_pVideo == NULL);
			CComObject<CVideoSequence>::CreateInstance(&m_pFilter->m_pVideo);
			m_pFilter->m_pVideo->m_pFilter = m_pFilter;
			m_pFilter->AddPin(m_pFilter->m_pVideo);
			*/

		//	m_pFilter->m_pVideo->m_file = new CBitStream(stream);
		//	m_pFilter->m_pVideo->m_file->next_start_code();

#if 0
			// ??
			return m_pFilter->Read();
#endif
			return Success;
		}
	};

	class COutputPin : 
		public BaseOutputPinImpl,
		public IMediaSeeking,
		public IBIFSOutput
	{
	public:
		CTOR COutputPin()
		{
		}

		//CComPtr<ILByteStream> m_stream;

		//CComObject<CVideoSample>* m_pOutSample;

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Scene)
				return Error;

			return Success;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType)
		{
			if (iPosition == 0)
			{
				MediaType* mediaType;
		//		mediaType.Create();//sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

				//memcpy(mediaType->pbFormat, m_pWaveFormat, sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

				mediaType = new MediaType(LMEDIATYPE_Scene);
				//mediaType->subtype = FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

				*pMediaType = mediaType;

				return Success_True;
			}
			else
			{
				*pMediaType = NULL;
				return Success_False;
			}
		}

		inline CBIFSDecoder* GetFilter() const
		{
			return (CBIFSDecoder*)m_pFilter;
		}

	// IMediaSeeking
		ErrorCode Seek(TimeUnit unit, LONGLONG seconds);
		ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal);
		ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal);

	// ILBIFSOutput
		virtual ErrorCode FindODById(int ODid, Object* *pVal);
	};

	CTOR CBIFSDecoder();
	~CBIFSDecoder();

	ErrorCode ReadBIFSCommandFrame(Stream& stream);

	CInputPin* m_pInputPin;
	COutputPin* m_pOutputPin;

	DWORD m_threadId;
	HANDLE m_hThread;

	Mpeg4::BIFSDec* m_pDec;

	void SeekFrame(long frame);

	virtual ErrorCode Run(LONGLONG tStart);
};

}	// Media
}

#endif //__BIFSDECODER_H_
