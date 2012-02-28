#ifndef __VIDEODECODER_H__
#define __VIDEODECODER_H__

//#include "resource.h"       // main symbols

//#include "../LFC/BitStream.h"

//#include "VideoDec.h"

namespace System
{
namespace MediaShow
{

class CVideoDecoder : public BaseFilterImpl
{
public:
	class CInputPin : public BasePinImpl
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

		inline CVideoDecoder* GetFilter() const
		{
			return (CVideoDecoder*)m_pFilter;
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

	class CVideoSequence :
		public BaseOutputPinImpl,
		public IMediaSeeking
	{
	public:
		CTOR CVideoSequence();

	//	CComObject<CVideoMediaType>* m_pMediaType;
	//	CComPtr<ILMemAllocator> m_allocator;

		/*
		CBitStream* m_file;

		WORD m_horizontal_size;
		WORD m_vertical_size;

		int m_mb_width;

		BYTE m_intra_quantiser_matrix[64];
		BYTE m_non_intra_quantiser_matrix[64];

		BYTE	m_chroma_format : 2,
				m_aspect_ratio_information : 4,
				m_frame_rate_code : 4,
				m_progressive_sequence : 1;
				//m_quantiser_scale_code : 5;

		DWORD m_bitrate;

		BYTE	m_profile_and_level_indication;

		long m_currentFrame;
		CUPtrList m_pictures;
		*/

	//	CComPtr<ILVideoSample> m_sample;

	//
	//	ErrorCode video_sequence();
	//	void sequence_header();
	//	ErrorCode sequence_extension();
	//	void extension_and_user_data(int i);
	//	void extension_data(int i);
	//	void group_of_pictures_header();
	//	void user_data();

	//	void seek(int frame);
		void SetSampleRGBData(IMediaSample* sample, Mpeg4::VideoObjectPlane* vob);

		virtual ErrorCode CheckMediaType(MediaType* mt);

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);

		inline CVideoDecoder* GetFilter() const
		{
			return (CVideoDecoder*)m_pFilter;
		}

	#if 0
		STDMETHOD(Connect)(ILPin* pReceivePin, LMediaType* mediaType)
		{
			if (pReceivePin == NULL) return E_POINTER;
			if (m_connectedTo != NULL) return E_UNEXPECTED;	// Already connected

			//CComPtr<ILMediaType> mediaType;
			//GetMediaType(&mediaType);

			/*
			{ // TODO, maybe not do this here
			// Create video media type
				ASSERT(m_pMediaType == NULL);

				CComObject<CVideoMediaType>::CreateInstance(&m_pMediaType);
				m_pMediaType->AddRef();
				m_pMediaType->m_pVideoOut = this;
			}
			*/

			CComQIPtr<ILMemInputPin> memInput = pReceivePin;
			if (memInput)
			{
				memInput->GetAllocator(&m_allocator);
			}

			ErrorCode hr = pReceivePin->ReceiveConnection(this, m_pMediaType);
			if (SUCCEEDED(hr))
			{
				m_connectedTo = pReceivePin;
			}

			/*
			if (memInput)
			{
				m_allocator->GetBuffer(0, (ILMediaSample**)&m_sample);
	#if 0
				m_pFilter->ReadImage();
	#endif

				memInput->Receive(m_sample);
			}
			*/

			return hr;
		}
	#endif

	// IMediaSeeking
		ErrorCode Seek(TimeUnit unit, LONGLONG t);
		ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal);
		ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal);
	};

	CTOR CVideoDecoder();

//	ISequentialByteStream* m_stream;
	Mpeg4::Track* m_pTrack;	// Kind of input pin.. ??

	/*
	CMP4VConfig* m_config;

	CMP4VSampleDescription* m_pSampleDescription;
	*/

	CInputPin* m_pInputPin;
	CVideoSequence* m_pVideo;

	DWORD m_threadId;
	HANDLE m_hThread;

	ErrorCode Read();

//	CVideoObjectPlane* pPrevVOP;

	Mpeg4::VideoDec* m_decoder;
	Mpeg4::VideoObjectPlane* m_pCurrentVOP;

	LONGLONG m_currentTime;
	long m_currentFrame;
	int32 m_start_code;

	void SeekFrame(ULONG frame);

	/*
	CBitStream* m_pBitStream;
	ULONG m_sampleSize;
	BOOL eof()
	{
	}
	*/

	/*
	void VisualObjectSequence(CBitStream* pBitStream, int start_code);
	int VisualObject(CBitStream* pBitStream, int start_code);
	int Group_of_VideoObjectPlane(CBitStream* pBitStream);
*/
//	void VideoObjectPlane(CBitStream* pBitStream);

	virtual ErrorCode Run(LONGLONG tStart);
};

}	// Media
}

#endif //__VIDEODECODER_H_
