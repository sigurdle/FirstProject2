#ifndef __UI_Video_h__
#define __UI_Video_h__

namespace System
{
namespace UI
{

class CVideoSample : public Object, public MediaShow::MediaSampleImpl<MediaShow::IMediaSample>
{
public:
	CTOR CVideoSample()
	{
		m_pBitmap = NULL;
		m_dwRef = 0;
	}

	ULONG m_dwRef;
	LDraw::Bitmap* m_pBitmap;
	LDraw::BitmapData m_bitmapData;

	ULONG AddRef()
	{
		m_dwRef++;
		return m_dwRef;
	}

	ULONG Release()
	{
		ASSERT(m_dwRef > 0);
		m_dwRef--;

	// A refcount of 0 means it's free to use

		return m_dwRef;
	}

	ErrorCode LockBits(MediaShow::LSampleData* pVal);
	ErrorCode UnlockBits();
};

class CVideoFilter :
	public MediaShow::BaseFilterImpl,
	public MediaShow::IMediaSeeking,
	public MediaShow::IQualProp
{
public:

	class CInputPin : 
		public MediaShow::BasePinImpl,
		public MediaShow::IMemInputPin
	{
	public:
		class CMemAllocator : public Object, public MediaShow::IMemAllocator
		{
		public:
			CTOR CMemAllocator()
			{
				m_pInputPin = NULL;

				m_samples[0] = NULL;
				m_samples[1] = NULL;
				m_samples[2] = NULL;
				m_samples[3] = NULL;
				m_samples[4] = NULL;
				m_samples[5] = NULL;
				m_samples[6] = NULL;
				m_samples[7] = NULL;
			}

			CInputPin* m_pInputPin;
			CVideoSample* m_samples[8];

			ErrorCode GetBuffer(ULONG /*dwBytes*/, MediaShow::IMediaSample* *pVal);
			ErrorCode ReleaseBuffer(MediaShow::IMediaSample* pBuffer);
		};

		CTOR CInputPin();

		~CInputPin()
		{
			delete m_pAllocator;
		}

		virtual ErrorCode CheckMediaType(MediaShow::MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Video)
				return Error;

			return Success;
		}

		virtual ErrorCode EndOfStream()
		{
			m_pFilter->m_pFilterGraph->Notify(m_pFilter, 0);
			return Success;
		}

	// IMemInputPin
		virtual MediaShow::IMemAllocator* GetAllocator()
		{
			return m_pAllocator;
		}

	//	HANDLE m_hEvent;

		virtual ErrorCode Pause()
		{
			m_pLock.Lock();
			/*
#if WIN32
			if (m_hEvent == NULL)
				m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
#else
#endif
				*/
			return Success;
		}

		virtual ErrorCode Run(LONGLONG tStart)
		{
			m_pLock.Unlock();
			/*
#if WIN32
			SetEvent(m_hEvent);
#else
#endif
			*/
			return Success;
		}

		virtual ErrorCode Receive(MediaShow::IMediaSample *pSample);

		inline CVideoFilter* GetFilter() const
		{
			return (CVideoFilter*)m_pFilter;
		}

	public:

		CriticalSection m_pLock;
		CriticalSection m_sampleLock;

		CMemAllocator* m_pAllocator;
		queue<CVideoSample*, vector<CVideoSample*> > m_samples;

		HANDLE m_hEvent;
	};

	CTOR CVideoFilter()
	{
		m_tStart = 0;

		m_pInput = new CInputPin;
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);
	}

	CInputPin* m_pInput;

//	LDraw::Bitmap* m_pBitmap;
	MediaElement* m_pControl;

	ErrorCode GetBitmap(LDraw::Bitmap** pVal);

public:

// IQualProp
	virtual ErrorCode get_AvgFrameRate(unsigned int* piAvgFrameRate)
	{
		*piAvgFrameRate = m_avgFrameRate;
		return Success;
	}

	virtual ErrorCode get_FramesDrawn(unsigned int* pcFramesDrawn)
	{
		*pcFramesDrawn = m_framesDrawn;
		return Success;
	}

	virtual ErrorCode get_FramesDroppedInRenderer(unsigned int* pcFramesDropped)
	{
		*pcFramesDropped = m_framesDropped;
		return Success;
	}

	virtual ErrorCode get_Jitter(unsigned int* piJitter)
	{
		*piJitter = m_jitter;
		return Success;
	}

	virtual ErrorCode get_AvgSyncOffset(int *piAvg)
	{
		return Success;
	}

	unsigned int m_avgFrameRate;
	unsigned int m_framesDrawn;
	unsigned int m_framesDropped;
	int m_jitter;

// IMediaSeeking
	virtual ErrorCode Seek(MediaShow::TimeUnit unit, LONGLONG t)
	{
		MediaShow::IMediaSeeking* peerSeeking = dynamic_cast<MediaShow::IMediaSeeking*>(m_pInput->ConnectedTo());
		if (peerSeeking == NULL)
			return Error_NoInterface;
		return peerSeeking->Seek(unit, t);
	}

	ErrorCode GetCurrentPosition(MediaShow::TimeUnit unit, LONGLONG *pVal)
	{
		MediaShow::IMediaSeeking* peerSeeking = dynamic_cast<MediaShow::IMediaSeeking*>(m_pInput->ConnectedTo());
		if (peerSeeking == NULL)
			return Error_NoInterface;

		return peerSeeking->GetCurrentPosition(unit, pVal);
	}

	ErrorCode GetDuration(MediaShow::TimeUnit unit, LONGLONG *pVal)
	{
		MediaShow::IMediaSeeking* peerSeeking = dynamic_cast<MediaShow::IMediaSeeking*>(m_pInput->ConnectedTo());
		if (peerSeeking == NULL)
			return Error_NoInterface;

		return peerSeeking->GetDuration(unit, pVal);
	}

	friend class CVideoSample;
};

class UIMediaExt MediaElement : public FrameworkElement, public IMediaControl
{
public:
	CTOR MediaElement();

//	bool m_playing;

//	CComPtr<IOGLSceneRenderer> m_sceneRenderer;

	System::StringW* get_Source() const;
	void set_Source(System::StringW* newVal);
//	void Play();

	virtual void Run();
	virtual void Stop();
	virtual void Pause();
	virtual MEDIACONTROL_STATE GetState();

//	static PropertyReference* CurrentTimeProperty;

	double get_CurrentTime();
	void set_CurrentTime(double timesecs);

	MediaShow::FilterGraph* get_FilterGraph()
	{
		return m_filterGraph;
	}

protected:

	void OnPresent(Object*);

	HANDLE m_hCEvent;

	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize);
	virtual LDraw::SizeD ArrangeOverride(LDraw::SizeD finalSize);
	virtual void OnRender(Graphics* pGraphics);

	friend class CVideoFilter;

	LDraw::DrawImageRectCommand* m_pDrawCommand;

	CVideoFilter* m_pFilter;

	System::StringW* m_Source;
	MediaShow::FilterGraph* m_filterGraph;
};

}	// UI
}

#endif // __UI_Video_h__
