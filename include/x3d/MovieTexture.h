#ifndef x3d_MovieTexture_h
#define x3d_MovieTexture_h

//#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

namespace System
{
namespace x3d
{

#if 0
class MovieTexture;

// This is used by MovieTexture
class CVideoFilter : 
	public MediaShow::BaseFilterImpl,
	public MediaShow::IMediaSeeking
{
public:
#if 0
	class CVideoSample : 
		public Media::CLMediaSampleImpl<Media::IMediaSample>
	{
	public:
		CVideoSample()
		{
			m_hBitmap = NULL;
			m_lpBmi = NULL;
		}

//		LDraw::Bitmap* m_pBitmap;
//		LDraw::BitmapData m_bitmapData;

		BitmapInfoHeader* m_lpBmi;
#if 0
		HBITMAP m_hBitmap;
		LPBYTE m_bits;
		int m_rowbytes;
#endif

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

		ErrorCode LockBits(Media::LSampleData *pVal)
		{
			pVal->width = m_lpBmi->biWidth;
			pVal->height = m_lpBmi->biHeight;
			pVal->rowbytes = -m_rowbytes;	// Negative height
			pVal->bitcount = 24;
			pVal->idata = (LPBYTE)m_bits + m_rowbytes*(pVal->height-1);

		/*
			m_pBitmap->LockBits(
				&LDraw::Rect(0, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight()),
				LDraw::ImageLockModeWrite,
				PixelFormat24bppRGB, &m_bitmapData);

			pVal->width = m_bitmapData.Width;
			pVal->height = m_bitmapData.Height;
			pVal->rowbytes = m_bitmapData.Stride;
			pVal->bitcount = 24;
			pVal->idata = (LPBYTE)m_bitmapData.Scan0;
			*/

			return S_OK;
		}
		ErrorCode UnlockBits()
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
#if 0
				EnterCriticalSection(&m_pInputPin->m_pLock);

				ASSERT(0);
				CVideoSample* pSample = NULL;//new CVideoSample;

				int width = ((LMedia::LVIDEOINFOHEADER2*)m_pInputPin->m_mt.pbFormat)->bmiHeader.biWidth;
				int height = ((LMedia::LVIDEOINFOHEADER2*)m_pInputPin->m_mt.pbFormat)->bmiHeader.biHeight;

//				<ILVideoMediaType> videoType = m_pInputPin->m_mediaType;
//				long width;
//				long height;
//				videoType->GetWidth(&width);
//				videoType->GetHeight(&height);

				pSample->m_lpBmi = (BITMAPINFOHEADER*)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER));

				pSample->m_lpBmi->biSize = sizeof(BITMAPINFOHEADER);
				pSample->m_lpBmi->biWidth = width;
				pSample->m_lpBmi->biHeight = height;
				pSample->m_lpBmi->biBitCount = 24;
				pSample->m_lpBmi->biPlanes = 1;
				pSample->m_lpBmi->biCompression = BI_RGB;

				pSample->m_rowbytes = ROWBYTES(pSample->m_lpBmi->biWidth, pSample->m_lpBmi->biBitCount);

				pSample->m_hBitmap = CreateDIBSection(NULL, (BITMAPINFO*)pSample->m_lpBmi, DIB_RGB_COLORS, (void**)&pSample->m_bits, NULL, 0);

			//	pSample->m_pBitmap = new LDraw::Bitmap(width, height, PixelFormat24bppRGB);

				*pVal = pSample;

				LeaveCriticalSection(&m_pInputPin->m_pLock);
#endif
				return Success;
			}
			ErrorCode ReleaseBuffer(MediaShow::IMediaSample* pBuffer)
			{
			//	DeleteObject(static_cast<CVideoSample*>(pBuffer)->m_hBitmap);
				return Success;
			}
		};

		CTOR CInputPin() : BasePinImpl(MediaShow::PINDIR_INPUT)
		{

		//	m_mediaType = NULL;

	//		m_pSample = NULL;
			m_hReceivedEvent = NULL;

			m_pAllocator = new CMemAllocator;
			m_pAllocator->m_pInputPin = this;
		}

		~CInputPin()
		{
			delete m_pAllocator;
		}

		CriticalSection m_pLock;

	//	CVideoFilter* m_pFilter;

		//ILVideoMediaType* m_mediaType;

		CMemAllocator* m_pAllocator;

#if 0
		CVideoSample* m_pSample;
#endif
		HANDLE m_hReceivedEvent;

		virtual ErrorCode CheckMediaType(MediaShow::MediaType* mt)
		{
			ASSERT(0);
			/*
			if (mt->GetMajorType() != LMEDIATYPE_Video)
				return Error;
*/
			if (mt->GetSubType() != GUID_NULL)	// TODO
				return Error;

			return Success;
		}

	public:
		inline CVideoFilter* GetFilter() const
		{
			return (CVideoFilter*)m_pFilter;
		}

	// IMemInputPin
		MediaShow::IMemAllocator* GetAllocator()
		{
			return m_pAllocator;
		}
		ErrorCode Receive(MediaShow::IMediaSample *pSample);

		ErrorCode CompleteConnect(MediaShow::IPin* pConnector);

		ErrorCode EndOfStream();
	};

	CTOR CVideoFilter()
	{
		//m_pMovieTexture = NULL;
		m_pInput = new CInputPin;
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);
	}

	CInputPin* m_pInput;

	MovieTexture* m_pTexture;

// IMediaSeeking
	ErrorCode Seek(MediaShow::TimeUnit unit, LONGLONG t);
	ErrorCode GetCurrentPosition(MediaShow::TimeUnit unit, LONGLONG *pVal);
	ErrorCode GetDuration(MediaShow::TimeUnit unit, LONGLONG *pVal);
};
#endif

class X3DEXT MovieTexture : 
	public X3DTexture2DNode,
	public X3DTextureNodeImplImpl,
	protected DShow::IVideoPresenter
{
public:
	CTOR MovieTexture();
	virtual ~MovieTexture();

#if 0
	virtual void DoTime(double gt)
	{
#if 0
		USES_CONVERSION;

		if (m_filterGraph == NULL)
		{
			if (m_url->m_items.GetSize() > 0)
			{
				BSTR url0 = m_url->m_items[0];

				TCHAR fullurl[512];
				{
					DWORD resultLen = sizeof(fullurl);
					InternetCombineUrl(W2A(m_pScene->m_url), W2A(url0), fullurl, &resultLen, 0);
				}

				ErrorCode hr = LoadURL(A2W(fullurl));

				if (SUCCEEDED(hr))
				{
					m_filterGraph->Run();
				}
			}
		}
#endif
	}
#endif

// X3DTextureNodeImplImpl
	virtual int GetWidth()
	{
		return m_pVideo->get_Width();
	}

	virtual int GetHeight()
	{
		return m_pVideo->get_Height();
	}

	virtual void DoTime(double gt)
	{
		ASSERT(0);
#if 0
		if (m_pVideoFilter && m_pVideoFilter->m_pInput->m_pSample)
		{
			LMedia::LVIDEOINFOHEADER2* vih = (LMedia::LVIDEOINFOHEADER2*)m_pVideoFilter->m_pInput->m_mt.pbFormat;

			int width = vih->bmiHeader.biWidth;
			int height = vih->bmiHeader.biHeight;

			BYTE* p = new BYTE[m_texwidth*m_texheight*3];

			for (int y = 0; y < height; y++)
			{
				BYTE* dest = p + m_texwidth*3*y;
				BYTE* src = m_pVideoFilter->m_pInput->m_pSample->m_bits + ROWBYTES(width, 24)*y;

				for (int x = 0; x < width; x++)
				{
					*dest++ = *src++;
					*dest++ = *src++;
					*dest++ = *src++;
				}
			}

			pDC->m_pGraphics->glBindTexture(GL_TEXTURE_2D, m_texName);
			//ASSERT(glGetError() == GL_NO_ERROR);

			ASSERT(0);
#if 0

			pDC->m_pGraphics->glTexSubImage2D(GL_TEXTURE_2D,
				0,	// level (0=base image)
				0, // xoffset
				0,	// yoffset,
				m_texwidth,
				m_texheight,
				GL_RGB, GL_UNSIGNED_BYTE,
				p);
			if (glGetError() != GL_NO_ERROR)
			{
				TRACE("glTexSubImage2D() failed\n");
			}
#endif
			delete p;

			/*
			DeleteObject(m_pVideoFilter->m_pInput->m_pSample->m_hBitmap);
			m_pVideoFilter->m_pInput->m_pSample->Release();
			m_pVideoFilter->m_pInput->m_pSample = NULL;
			*/
#if WIN32
			SetEvent(m_pVideoFilter->m_pInput->m_hReceivedEvent);
#else
			ASSERT(0);
#endif
		}
#endif
	}

	void LoadURL(StringIn FileName);

	virtual void CreateTexture(Graphics::RenderTarget* pGraphics) override;
	virtual void ApplyTexture(Graphics::Graphics3D* pGraphics);

	X3DNODE(MovieTexture, X3DTexture2DNode)

	X3DMFIELD(MFString, url, Url)
	X3DSFIELD(SFBool, repeatS, RepeatS)
	X3DSFIELD(SFBool, repeatT, RepeatT)

//	static X3DFieldDefinition* get_UrlFieldDef();
//	static TypedX3DFieldDefinition<SFBool>* get_repeatSFieldDef();
//	static TypedX3DFieldDefinition<SFBool>* get_repeatTFieldDef();

protected:

	virtual HRESULT Init(IDirect3DDevice9* d3ddev, uint width, uint height, ID3D10Texture2D* texture) override;
	virtual HRESULT DrawScene(IDirect3DDevice9* d3ddev, IDirect3DTexture9* texture) override;

	DShow::IVideoPlayer* m_pVideo;
	Graphics::Bitmap* m_pBitmap;
//	CVideoFilter* m_pVideoFilter;	// TODO remove
//	MediaShow::FilterGraph* m_filterGraph;	// TODO remove
//	uint m_texName;	// TODO remove
	int m_status;

	//int m_texwidth;
//	int m_texheight;

private:

/*
	MFString [in,out] url     []   [urn]
	SFBool  []       repeatS TRUE
	SFBool  []       repeatT TRUE
*/

//	MFURL* m_url;
//	MFString* m_url;
//	SFBool* m_repeatS;
//	SFBool* m_repeatT;
};

}	// x3d
}	// System

#endif // x3d_MovieTexture_h
