#ifndef x3d_SceneRenderFilter_h
#define x3d_SceneRenderFilter_h

namespace System
{
namespace x3d
{

class COGLSceneRenderer;

#if 0
class X3DEXT SceneRenderFilter :
	public MediaShow::BaseFilterImpl,
	public MediaShow::IMediaSeeking
{
public:

	class BIFSSample :
		public Object,
		public MediaShow::MediaSampleImpl<MediaShow::IMediaSample>
	{
	public:
		X3DScene* m_scene;

		/*
		STDMETHOD(GetScene)(IUnknown* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_scene;
			if (*pVal) (*pVal)->AddRef();
			return S_OK;
		}
		*/

		ULONG AddRef()
		{
			return 1;
		}

		ULONG Release()
		{
			return 1;
		}

		ErrorCode LockBits(MediaShow::LSampleData *pVal)
		{
#ifndef __LERSTAD__
			pVal->idata = reinterpret_cast<uint8*>(m_scene);
#endif
			return Success;
		}
		ErrorCode UnlockBits()
		{
			return Success;
		}
	};

#if 0
	class ATL_NO_VTABLE CVideoSample : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLMediaSampleImpl<ILVideoSample>
	{
	public:
		CVideoSample()
		{
			m_hBitmap = NULL;
			m_lpBmi = NULL;
		}

//		Gdiplus::Bitmap* m_pBitmap;
//		Gdiplus::BitmapData m_bitmapData;

		BITMAPINFOHEADER* m_lpBmi;
		HBITMAP m_hBitmap;
		LPBYTE m_bits;
		int m_rowbytes;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CVideoSample)
		COM_INTERFACE_ENTRY(ILMediaSample)
		COM_INTERFACE_ENTRY(ILVideoSample)
	END_COM_MAP()

	public:

		/*
		STDMETHOD(GetMediaType)(ILMediaType* *pVal)
		{
			return S_OK;
		}
		*/
	#if 0
		STDMETHOD(GetWidth)(long* pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = 0;//m_pBitmap->GetWidth();
			return S_OK;
		}

		STDMETHOD(GetHeight)(long* pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pBitmap->GetHeight();
			return S_OK;
		}
	#endif

		STDMETHOD(LockBits)(LSampleData *pVal)
		{
			pVal->width = m_lpBmi->biWidth;
			pVal->height = m_lpBmi->biHeight;
			pVal->rowbytes = -m_rowbytes;	// Negative height
			pVal->bitcount = 24;
			pVal->idata = (LPBYTE)m_bits + m_rowbytes*(pVal->height-1);

		/*
			m_pBitmap->LockBits(
				&Gdiplus::Rect(0, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight()),
				Gdiplus::ImageLockModeWrite,
				PixelFormat24bppRGB, &m_bitmapData);

			pVal->width = m_bitmapData.Width;
			pVal->height = m_bitmapData.Height;
			pVal->rowbytes = m_bitmapData.Stride;
			pVal->bitcount = 24;
			pVal->idata = (LPBYTE)m_bitmapData.Scan0;
			*/

			return S_OK;
		}
		STDMETHOD(UnlockBits)()
		{
			//m_pBitmap->UnlockBits(&m_bitmapData);

			return S_OK;
		}
	};
#endif

	class CInputPin :
		public MediaShow::BasePinImpl,
		public MediaShow::IMemInputPin
	{
	public:
		class CMemAllocator :
			public Object,
			public MediaShow::IMemAllocator
		{
		public:
			CTOR CMemAllocator()
			{
				m_pInputPin = NULL;
			}

			CInputPin* m_pInputPin;

		public:
			ErrorCode GetBuffer(ULONG /*dwBytes*/, MediaShow::IMediaSample* *pVal)
			{
			//	EnterCriticalSection(&m_pInputPin->m_pLock);

				BIFSSample* pSample = new BIFSSample;
				pSample->m_scene = new X3DScene;
				pSample->AddRef();

				//pSample->m_scene.CoCreateInstance(CLSID_LX3DScene);

				*pVal = pSample;

			//	LeaveCriticalSection(&m_pInputPin->m_pLock);

				return Success;
			}
			ErrorCode ReleaseBuffer(MediaShow::IMediaSample* pBuffer)
			{
				return Success;
			}
		};

		CTOR CInputPin() : MediaShow::BasePinImpl(MediaShow::PINDIR_INPUT)
		{
			m_pFilter = NULL;

		//	m_pSample = NULL;

			m_pAllocator = new CMemAllocator;
			m_pAllocator->m_pInputPin = this;

		//	InitializeCriticalSection(&m_pLock);
		}

	//	CriticalSection m_pLock;

	//	SceneRenderFilter* m_pFilter;

		CMemAllocator* m_pAllocator;

	//	CVideoSample* m_pSample;

		virtual ErrorCode CheckMediaType(MediaShow::MediaType* mt)
		{
			ASSERT(0);
		//	if (mt->GetMajorType() != LMEDIATYPE_Scene)
		//		return Error;

			return Success;
		}

	public:
		inline SceneRenderFilter* GetFilter() const
		{
			return (SceneRenderFilter*)m_pFilter;
		}

		virtual MediaShow::IMemAllocator* GetAllocator()
		{
			return m_pAllocator;
		}
		
		virtual ErrorCode_Bool Receive(MediaShow::IMediaSample *pSample);
	};

	CTOR SceneRenderFilter();

	COGLSceneRenderer* m_Control;

	CInputPin* m_pInput;

// IMediaSeeking
	ErrorCode Seek(MediaShow::TimeUnit unit, LONGLONG t)
	{
		MediaShow::IMediaSeeking* peerSeeking = dynamic_cast<MediaShow::IMediaSeeking*>(m_pInput->ConnectedTo());
		if (peerSeeking == NULL)
			return Error_NoInterface;

		return peerSeeking->Seek(unit, t);
	}

	ErrorCode GetCurrentPosition(MediaShow::TimeUnit unit, LONGLONG* pVal)
	{
		MediaShow::IMediaSeeking* peerSeeking = dynamic_cast<MediaShow::IMediaSeeking*>(m_pInput->ConnectedTo());
		if (peerSeeking == NULL)
			return Error_NoInterface;

		return peerSeeking->GetCurrentPosition(unit, pVal);
	}

	ErrorCode GetDuration(MediaShow::TimeUnit unit, LONGLONG* pVal)
	{
		MediaShow::IMediaSeeking* peerSeeking = dynamic_cast<MediaShow::IMediaSeeking*>(m_pInput->ConnectedTo());
		if (peerSeeking == NULL)
			return Error_NoInterface;

		return peerSeeking->GetDuration(unit, pVal);
	}
};

#endif

}	// x3d
}	// System

#endif // x3d_SceneRenderFilter_h
