#ifndef __Media_MPEGVIDEODECODER_H__
#define __Media_MPEGVIDEODECODER_H__

namespace System
{
namespace MediaShow
{

class CVideoSequence;

class MPEGVideoDecoder : 
	public BaseFilterImpl
{
public:
	class InputPin : 
		public BasePinImpl
	{
	public:
		CTOR InputPin();

		inline MPEGVideoDecoder* GetFilter() const
		{
			return (MPEGVideoDecoder*)m_pFilter;
		}

	//	STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType);

		virtual ErrorCode CheckConnect(IPin* pPin);

		virtual void BreakConnect();

		virtual ErrorCode CheckMediaType(MediaType* mt);

		virtual ErrorCode CompleteConnect(IPin* pPin);
	};

	class OutputPin : 
		public BaseOutputPinImpl,
		public IMediaSeeking
	//	public CVideoSequence
	{
	public:

		CTOR OutputPin()
		{
			m_p = new CVideoSequence;
		}

		CVideoSequence* m_p;

		ErrorCode video_sequence_frames();

		virtual ErrorCode CheckMediaType(MediaType* mt);

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);

		inline MPEGVideoDecoder* GetFilter() const
		{
			return (MPEGVideoDecoder*)m_pFilter;
		}

	#if 0
		STDMETHOD(Connect)(IPin* pReceivePin, ILMediaType* mediaType)
		{
			if (pReceivePin == NULL) return E_POINTER;
			if (m_connectedTo != NULL) return E_UNEXPECTED;	// Already connected

			//CComPtr<ILMediaType> mediaType;
			//GetMediaType(&mediaType);

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

			if (memInput)
			{
				m_allocator->GetBuffer(0, (ILMediaSample**)&m_sample);
	#if 0
				m_pFilter->ReadImage();
	#endif

				memInput->Receive(m_sample);
			}

			return hr;
		}
	#endif

	// IMediaSeeking
		/*
		ErrorCode Seek(LONGLONG seconds)
		{
			return Seek(0, seconds);
		}
		*/
		ErrorCode Seek(TimeUnit unit, LONGLONG t);
		ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal);
		ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal);

	#if 0
	// ILMediaStream
		STDMETHODIMP GetStreamType(LStreamType* pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = LStreamType_Video;
			return S_OK;
		}

		/*
	// ILVideo
		STDMETHOD(GetWidth)(long *pVal);
		STDMETHOD(GetHeight)(long *pVal);
		STDMETHOD(GetSample)(ILVideoSample* *pVal);
		STDMETHOD(SetSample)(ILVideoSample* newVal);
		*/

	//	ILStreamInfo
		STDMETHOD(GetBitRate)(long* pVal);
		STDMETHOD(GetCodec)(BSTR *pVal);

	// ILVideoStreamInfo
		STDMETHOD(GetFrameRate)(double* pVal);
	#endif
		};

	CTOR MPEGVideoDecoder();

	System::IO::CByteStream* m_stream;

	InputPin* m_pInputPin;

	OutputPin* m_pVideo;

	virtual ErrorCode Run(LONGLONG tStart);
};

}	// MediaShow
}

#endif // __Media_MPEGVIDEODECODER_H__
