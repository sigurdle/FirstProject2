#include "StdAfx.h"
#include "Graphics.h"

#include <d3d9.h>

//#include "Drawing.h"

namespace System
{
namespace MSWindows
{

/*
 * DDCOLORKEY
 */
typedef struct _DDCOLORKEY
{
    DWORD	dwColorSpaceLowValue;	// low boundary of color space that is to
					// be treated as Color Key, inclusive
    DWORD	dwColorSpaceHighValue;	// high boundary of color space that is
					// to be treated as Color Key, inclusive
} DDCOLORKEY;

/*
 * DDPIXELFORMAT
 */
typedef struct _DDPIXELFORMAT
{
    DWORD	dwSize;			// size of structure
    DWORD	dwFlags;		// pixel format flags
    DWORD	dwFourCC;		// (FOURCC code)
    union
    {
	DWORD	dwRGBBitCount;		// how many bits per pixel
	DWORD	dwYUVBitCount;		// how many bits per pixel
	DWORD	dwZBufferBitDepth;	// how many bits for z buffers
	DWORD	dwAlphaBitDepth;	// how many bits for alpha channels
    };
    union
    {
	DWORD	dwRBitMask;		// mask for red bit
	DWORD	dwYBitMask;		// mask for Y bits
    };
    union
    {
	DWORD	dwGBitMask;		// mask for green bits
	DWORD	dwUBitMask;		// mask for U bits
    };
    union
    {
	DWORD	dwBBitMask;		// mask for blue bits
	DWORD	dwVBitMask;		// mask for V bits
    };
    union
    {
	DWORD	dwRGBAlphaBitMask;	// mask for alpha channel
	DWORD	dwYUVAlphaBitMask;	// mask for alpha channel
	DWORD	dwRGBZBitMask;		// mask for Z channel
	DWORD	dwYUVZBitMask;		// mask for Z channel
    };
} DDPIXELFORMAT;

/*
 * DDSURFACEDESC
 */
typedef struct _DDSURFACEDESC
{
    DWORD		dwSize;			// size of the DDSURFACEDESC structure
    DWORD		dwFlags;		// determines what fields are valid
    DWORD		dwHeight;		// height of surface to be created
    DWORD		dwWidth;		// width of input surface
    union
    {
        LONG		lPitch;			// distance to start of next line (return value only)
        DWORD           dwLinearSize;           // Formless late-allocated optimized surface size
    };
    DWORD		dwBackBufferCount;	// number of back buffers requested
    union
    {
        DWORD           dwMipMapCount;          // number of mip-map levels requested
	DWORD		dwZBufferBitDepth;	// depth of Z buffer requested
	DWORD		dwRefreshRate;		// refresh rate (used when display mode is described)
    };
    DWORD		dwAlphaBitDepth;	// depth of alpha buffer requested
    DWORD		dwReserved;		// reserved
    LPVOID		lpSurface;		// pointer to the associated surface memory
    DDCOLORKEY		ddckCKDestOverlay;	// color key for destination overlay use
    DDCOLORKEY		ddckCKDestBlt;		// color key for destination blt use
    DDCOLORKEY		ddckCKSrcOverlay;	// color key for source overlay use
    DDCOLORKEY		ddckCKSrcBlt;		// color key for source blt use
    DDPIXELFORMAT	ddpfPixelFormat;	// pixel format description of the surface
//    DDSCAPS		ddsCaps;		// direct draw surface capabilities
} DDSURFACEDESC;

/* Bitmap Header Definition */
typedef struct tagBITMAP
  {
    LONG        bmType;
    LONG        bmWidth;
    LONG        bmHeight;
    LONG        bmWidthBytes;
    uint16        bmPlanes;
    uint16        bmBitsPixel;
    LPVOID      bmBits;
  } BITMAP, *PBITMAP, NEAR *NPBITMAP, FAR *LPBITMAP;

typedef struct tagDIBSECTION {
    BITMAP              dsBm;
    BITMAPINFOHEADER    dsBmih;
    DWORD               dsBitfields[3];
    HANDLE              dshSection;
    DWORD               dsOffset;
} DIBSECTION, FAR *LPDIBSECTION, *PDIBSECTION;

extern "C"
{

WINGDIAPI int   WINAPI GetDIBits( IN HDC, IN HBITMAP, IN UINT, IN UINT,  OUT LPVOID, IN OUT LPBITMAPINFO, IN UINT);
WINGDIAPI UINT WINAPI GetDIBColorTable( IN HDC, IN UINT, IN UINT, OUT RGBQUAD *);
WINGDIAPI int   WINAPI GetObjectA( IN HGDIOBJ, IN int, OUT LPVOID);
WINGDIAPI int   WINAPI GetObjectW( IN HGDIOBJ, IN int, OUT LPVOID);

}	// extern "C"

}	// MSWindows
}	// System

#if __APPLE__
#define LDraw carbonLDraw
#include <Carbon/Carbon.h>
#undef LDraw
#endif

#if AMIGA
#include "../amiga_header.h"
#endif

namespace System
{
namespace Graphics
{

#if 0

enum ColorSpace
{
	ColorSpaceMonochrome,
	ColorSpaceGray,
	ColorSpaceRGB,
	ColorSpaceCMYK,
	ColorSpaceLab,
	ColorSpaceXYZ,
	ColorSpaceCIE,
	ColorSpaceHSL,
};

Packing
{
	RGBA = 0,
	BGRA = 1,
	ARGB = 2,
	ABGR = 3,
	RGB = 0,
	BGR = 1,
	RGB_R5G5B5 = 0;
	RGB_R5G6B5 = 1,
};

	struct PixelFormat
	{
		unsigned bpp : 8;
		unsigned planes : 6;
		unsigned channels : 3;
		unsigned paletted : 1;
		unsigned alpha : 1;
		unsigned premultipled : 1;
		unsigned packing : 3;
		unsigned colorspace : 5;
		unsigned reserved : 3;
	};
#endif

#if 0
static int SubPrecX	= 0;
#define SubPrecY		0
static int SubRangeX	= 1<<SubPrecX;
#define SubRangeY		(1<<SubPrecY)

#define SubPixelsX	1
#define SubPixelsY	1

static int PREC	=	9;
/*
#define PRECRANGE	(1<<PREC)
#define PRECMASK	((1<<PREC)-1)
*/
static int PRECRANGE	= (1<<PREC);
static int PRECMASK = ((1<<PREC)-1);
#endif

//extern uint8 multab[256][256];

#if 0

class BitmapRenderFilter;

class BitmapSample : public LMedia::CLMediaSampleImpl<LMedia::IMediaSample>
{
public:
	BitmapSample()
	{
		//m_pBitmap = NULL;
		m_dwRef = 0;
	}

	~BitmapSample()
	{
		//delete m_pBitmap;
	}

	ULONG m_dwRef;
	LDraw::Bitmap mBitmap;
//	LDraw::BitmapData m_bitmapData;

	LDraw::BitmapData m_bitmapData;

	ULONG AddRef()
	{
		m_dwRef++;
		return m_dwRef;
	}

	ULONG Release()
	{
		m_dwRef--;

	// A refcount of 0 means it's free to use

		return m_dwRef;
	}

	HRESULT LockBits(LMedia::LSampleData* pVal)
	{
		mBitmap.LockBits(NULL, LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite, &m_bitmapData);

		pVal->width = m_bitmapData.Width;
		pVal->height = m_bitmapData.Height;
		pVal->bitcount = m_bitmapData.BitCount;
		pVal->rowbytes = m_bitmapData.Stride;
		pVal->idata = m_bitmapData.Scan0;
		return S_OK;
#if 0
		if (m_pBitmap->LockBits(
			&Gdiplus::RectI(0, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight()),
			Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite,
			PixelFormat24bppRGB, &m_bitmapData) == 0)
		{
			pVal->width = m_bitmapData.Width;
			pVal->height = m_bitmapData.Height;
			pVal->bitcount = 24;
			pVal->rowbytes = m_bitmapData.Stride;
			pVal->idata = (LPBYTE)m_bitmapData.Scan0;

			return S_OK;
		}
		else
#endif
			return E_FAIL;
	}

	HRESULT UnlockBits()
	{
		mBitmap.UnlockBits(&m_bitmapData);
		return S_OK;
	}
};

class CInputPin;

class CMemAllocator : public LMedia::IMemAllocator
{
public:
	CMemAllocator()
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

	~CMemAllocator()
	{
		for (int i = 0; i < 8; i++)
		{
			delete m_samples[i];
		}
	}

	CInputPin* m_pInputPin;

	BitmapSample* m_samples[8];

	HRESULT GetBuffer(DWORD /*dwBytes*/, LMedia::IMediaSample* *pVal);

	HRESULT ReleaseBuffer(LMedia::IMediaSample* pBuffer)
	{
		ASSERT(0);
		return S_OK;
	}
};

class CInputPin : 
	public LMedia::BasePinImpl,
	public LMedia::IMemInputPin
{
public:

	CInputPin() : BasePinImpl(LMedia::LPINDIR_INPUT)
	{
		m_pSample = NULL;

		m_pAllocator = new CMemAllocator;
		m_pAllocator->m_pInputPin = this;

		m_pLock.Init();
	}

	~CInputPin()
	{
		delete m_pAllocator;
	}

	CriticalSection m_pLock;

	CMemAllocator* m_pAllocator;
	BitmapSample* m_pSample;

	virtual HRESULT CheckMediaType(const LMedia::MediaType& mt)
	{
		if (mt.GetMajorType() != LMEDIATYPE_Video)
			return E_FAIL;

		return S_OK;
	}

	inline BitmapRenderFilter* GetFilter() const
	{
		return (BitmapRenderFilter*)m_pFilter;
	}
	HRESULT EndOfStream();

// ILMemInputPin
	LMedia::IMemAllocator* GetAllocator()
	{
		return m_pAllocator;
	}
	bool Receive(LMedia::IMediaSample *pSample);
};

class BitmapRenderFilter :
	public LMedia::BaseFilterImpl,
	public LMedia::IMediaSeeking
{
public:


	BitmapRenderFilter()
	{
		m_tStart = 0;

		m_pInput = new CInputPin;
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);
	}

	CInputPin* m_pInput;

	LDraw::Bitmap* m_pBitmap;

	HRESULT GetBitmap(LDraw::Bitmap** pVal);

public:
// IMediaSeeking
	HRESULT Seek(DWORD unit, LONGLONG t)
	{
		ASSERT(0);
		return 0;
#if 0
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;
		return peerSeeking->Seek(t);
#endif
	}

	HRESULT GetCurrentPosition(DWORD unit, LONGLONG *pVal)
	{
		/*
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->Seek(seconds);
		*/
		return S_OK;
	}

	HRESULT GetDuration(DWORD unit, LONGLONG *pVal)
	{
		ASSERT(0);
		return 0;
#if 0
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->GetDuration(pVal);
#endif
	}

	friend BitmapSample;
};

HRESULT CInputPin::EndOfStream()
{
	GetFilter()->m_pFilterGraph->Notify(m_pFilter, 0);
	return S_OK;
}

bool CInputPin::Receive(LMedia::IMediaSample *pSample)
{
	m_pLock.Lock();

	LONGLONG timeStart;
	LONGLONG timeEnd;
	pSample->GetTime(&timeStart, &timeEnd);

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	GetFilter()->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, timeStart/*streamTime*/, hEvent, NULL);

	WaitForSingleObject(hEvent, INFINITE);

	CloseHandle(hEvent);

	m_pSample = static_cast<BitmapSample*>(pSample);

//	m_pFilter->m_pMoviePlayer->m_cwnd.PostMessage(WM_USER+100, 0, 0);

	m_pLock.Unlock();

	return false;	// Stop sending samples
}

HRESULT CMemAllocator::GetBuffer(DWORD /*dwBytes*/, LMedia::IMediaSample* *pVal)
{
	m_pInputPin->m_pLock.Lock();

	for (int i = 0; i < 8; i++)
	{
		BitmapSample* pSample = m_samples[i];
		if (pSample == NULL)
		{
			pSample = new BitmapSample;
			//BitmapSample>::CreateInstance(&pSample);

			LMedia::MediaType mt;
			m_pInputPin->ConnectionMediaType(&mt);

			LMedia::VideoInfoHeader* vih = (LMedia::VideoInfoHeader*)mt.GetFormat();

			LDraw::Bitmap* pBitmap = m_pInputPin->GetFilter()->m_pBitmap;

			uint32 pixelFormat;

			if (vih->vih->bmiHeader.biBitCount == 24)
			{
				//pBitmap->m_p->m_bitcount = 24;
				pixelFormat = RGB_24;
			}
			else
			{
				//pBitmap->m_p->m_bitcount = 32;
				pixelFormat = RGBAP_32;
			}
			pBitmap->m_p = new Bitmap(vih->GetWidth(), vih->GetHeight(), pixelFormat);
			pBitmap->m_p->AddRef();
			/*
			pBitmap->m_p->m_width = vih->GetWidth();
			pBitmap->m_p->m_height = vih->GetHeight();
			pBitmap->m_p->m_rowBytes = ROWBYTES_DWORD(pBitmap->m_p->m_width, pBitmap->m_p->m_bitcount);
			pBitmap->m_p->m_bitmapData = new uint8[pBitmap->m_p->m_rowBytes * pBitmap->m_p->m_height];
			*/
			pSample->mBitmap = *pBitmap;

			m_samples[i] = pSample;
		}

		if (pSample->m_dwRef == 0)
		{
			*pVal = pSample;
			(*pVal)->AddRef();
			break;
		}
	}

	m_pInputPin->m_pLock.Unlock();

	return S_OK;
}

#endif	// WIN32

////////////////////////////////////////////////////////////////////
// Bitmap

#if 0
Bitmap::Bitmap()
{
	m_p = NULL;
}

Bitmap::Bitmap(const Bitmap& other)
{
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
}
#endif

/*
Bitmap::Bitmap()
{
	m_refcount = 0;
	m_locked = 0;
	m_bitmapData = NULL;
	m_width = 0;
	m_height = 0;
	m_rowBytes = 0;
	m_bFreeData = false;

	//m_depthBuffer = NULL;
}
*/

#if 0
Bitmap::Bitmap(const BitmapData& bitmapdata)
{
	m_p = new Bitmap(bitmapdata);
	m_p->AddRef();
}
#endif

#if 0
Bitmap::Bitmap(const BitmapData& bitmapdata)
{
	m_bFreeData = false;
	m_locked = 0;
	//m_depthBuffer = NULL;

	m_width = bitmapdata.Width;
	m_height = bitmapdata.Height;
	m_rowBytes = bitmapdata.Stride;
	m_pixelFormat = bitmapdata.PixelFormat;

	if (m_pixelFormat == PixelFormat_t::RGB_24)
	{
		ASSERT(m_pixelFormat.GetBitCount() == 24);
	}
	else if (m_pixelFormat == PixelFormat_t::RGB_32)
	{
		ASSERT(m_pixelFormat.GetBitCount() == 32);
	}
	else if (m_pixelFormat == PixelFormat_t::RGBAP_32)
	{
		ASSERT(m_pixelFormat.GetBitCount() == 32);
	}
	else if (m_pixelFormat == PixelFormat_t::GRAY_16)
	{
		ASSERT(m_pixelFormat.GetBitCount() == 16);
	}
	else
	{
		ASSERT(0);
		THROW(-1);
	}

	m_bitmapData = (uint8*)bitmapdata.Scan0;
}
#endif

#if WIN32

#if 0
Bitmap::Bitmap(HBITMAP hbm, HPALETTE hpal)
{
	m_p = new Bitmap(hbm, hpal);
	m_p->AddRef();
}
#endif

Bitmap::Bitmap(StringIn filename)
{
	Imaging::BitmapLoader bm;
	Imaging::BitmapFormat bitmapFormat;
#undef new
	void* data = bm.Load(filename, &bitmapFormat, ::operator new, ::operator delete);
#define new _new

	// TODO

	uint pixelbytes = 4;
	uint rowPitch = alignment4(bitmapFormat.width*pixelbytes);

	D3D10Texture2D texture(Direct10::get_D3DDevice(), bitmapFormat.width, bitmapFormat.height, DXGI_FORMAT_R8G8B8A8_UNORM, data, rowPitch);
	Set(Direct10::get_D3DDevice(), texture);

	delete data;
}

void Bitmap::Set(ID3D10Device* device, const D3D10Texture2D& texture2D)
{
	m_d3d10_texture = texture2D.m_d3d10_texture;
	m_d3d10_texture->AddRef();

	D3D10_TEXTURE2D_DESC desc;
	m_d3d10_texture->GetDesc(&desc);

	m_width = desc.Width;
	m_height = desc.Height;
	m_pixelFormat = PixelFormat_t::RGBAP_32;	// TODO

	if (desc.BindFlags & D3D10_BIND_SHADER_RESOURCE)
	{
		CreateD3D10ShaderResourceView(device);
	}

	if (desc.BindFlags & D3D10_BIND_RENDER_TARGET)
	{
		CreateD3D10RenderTargetView(device);
	}
}

Bitmap::Bitmap(ID3D10Device* device, const D3D10Texture2D& texture2D)
{
	Set(device, texture2D);
}

Bitmap::Bitmap(HBITMAP hbm, HPALETTE hpal)
{
//	m_refcount = 0;
	//m_depthBuffer  = NULL;
	m_locked = 0;

	m_colors = NULL;

	DIBSECTION dibsection;
	int size = GetObjectA((void*)hbm, sizeof(DIBSECTION), &dibsection);
	if (size == sizeof(DIBSECTION) || size == sizeof(BITMAP))
	{
		if (dibsection.dsBm.bmPlanes != 1)
		{
			raise(Exception());
		}

		if (dibsection.dsBm.bmBitsPixel != 8 && dibsection.dsBm.bmBitsPixel != 24 && dibsection.dsBm.bmBitsPixel != 32)
		{
			raise(Exception("Unsupported BitsPixel"));
		}

		m_width = dibsection.dsBm.bmWidth;
		m_height = abs(dibsection.dsBm.bmHeight);
		m_rowBytes = dibsection.dsBm.bmWidthBytes;

		int bitcount = dibsection.dsBm.bmBitsPixel;

		if (bitcount == 8)
		{
			m_pixelFormat = PixelFormat_t::INDEXED_RGB_24;
		}
		else if (bitcount == 24)
		{
			m_pixelFormat = PixelFormat_t::RGB_24;
		}
		else if (bitcount == 32)
		{
			if (dibsection.dsBmih.biCompression == BI_BITFIELDS)
			{
				// TODO, check
//	bi.bV5RedMask   =  0x00FF0000;
//	bi.bV5GreenMask =  0x0000FF00;
//	bi.bV5BlueMask  =  0x000000FF;
//	bi.bV5AlphaMask =  0xFF000000;
				m_pixelFormat = PixelFormat_t::RGBAP_32;
			}
			else
			{
				m_pixelFormat = PixelFormat_t::RGB_32;
			}
		}
		else
			raise(Exception());

		if (size == sizeof(DIBSECTION))
		{
			if (bitcount == 8)
			{
				HDC hdc = CreateCompatibleDC(NULL);
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, (void*)hbm);
				if (hOldBitmap)
				{
					m_colors = new RGBQUAD[256];
					GetDIBColorTable(hdc, 0, 256, m_colors);

					SelectObject(hdc, (void*)hOldBitmap);
				}
				DeleteDC(hdc);

				RGB rgb[256];
				for (int i = 0; i < 256; i++)
				{
					rgb[i].r = m_colors[i].rgbRed;
					rgb[i].g = m_colors[i].rgbGreen;
					rgb[i].b = m_colors[i].rgbBlue;
					rgb[i].pen = i;
				}

#if 0
				m_palette.m_root = maketree(rgb, 256, 0);
#endif
			}

		//	m_rowBytes = ROWBYTES_DWORD(m_width, m_bitcount);

			m_bitmapData = (uint8*)dibsection.dsBm.bmBits;
			m_bFreeData = false;
		}
		else
		{
			BITMAPINFO bmi;
			memset(&bmi, 0, sizeof(BITMAPINFOHEADER));
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = bitcount;
			bmi.bmiHeader.biWidth = m_width;
			bmi.bmiHeader.biHeight = m_height;
			bmi.bmiHeader.biCompression = BI_RGB;
			m_bitmapData = new uint8[m_rowBytes * m_height];
			m_bFreeData = true;

			HDC hdc = CreateCompatibleDC(NULL);

			int n = GetDIBits(hdc, hbm, 0, m_height, m_bitmapData, &bmi, DIB_RGB_COLORS);

			DeleteDC(hdc);

			if (n != m_height)
			{
				delete [] m_bitmapData;
				raise(Exception());
			}

			if (m_pixelFormat == PixelFormat_t::RGBAP_32)
			{
			// Premultiply

				for (int y = 0; y < m_height; y++)
				{
					uint8* dst = m_bitmapData + y * m_rowBytes;
					for (int x = 0; x < m_width; x++)
					{
						/*
						if (dst[3] == 0)
						{
							dst[0] = 0;
							dst[1] = 0;
							dst[2] = 0;
						}
						*/
#if 0
						dst[0] = (int)dst[0] * dst[3] / 255;
						dst[1] = (int)dst[1] * dst[3] / 255;
						dst[2] = (int)dst[2] * dst[3] / 255;
#endif
						dst += 4;
					}
				}
			}
		}

		if (dibsection.dsBm.bmHeight > 0)	// bottom-up
		{
			m_bitmapData = (uint8*)m_bitmapData + m_rowBytes * (m_height-1);
			m_rowBytes = -m_rowBytes;
		}
	}
	else
	{
		raise(Exception());
	}

	/*
	if (true)
	{
		m_depthBuffer = (uint8*)new float[m_width*m_height];
	}
	*/
}

#if 0
Bitmap::Bitmap(const BITMAPINFO *gdiBitmapInfo, VOID *gdiBitmapData)
{
	m_p = new Bitmap(gdiBitmapInfo, gdiBitmapData);
	m_p->AddRef();
}
#endif

Bitmap::Bitmap(const BITMAPINFO* gdiBitmapInfo, VOID* gdiBitmapData)
{
	ASSERT(0);
#if 0

	m_bFreeData = false;
	m_locked = 0;
	//m_depthBuffer = NULL;
	m_colors = NULL;

	ASSERT(gdiBitmapInfo != NULL);
	ASSERT(gdiBitmapData != NULL);
	if (gdiBitmapInfo == NULL) THROW(-1);
	if (gdiBitmapData == NULL) THROW(-1);

	int bitcount = gdiBitmapInfo->bmiHeader.biBitCount;

	m_width = gdiBitmapInfo->bmiHeader.biWidth;
	m_height = abs(gdiBitmapInfo->bmiHeader.biHeight);
	m_rowBytes = ROWBYTES_DWORD(m_width, bitcount);

	if (bitcount == 8)
	{
		m_pixelFormat = PixelFormat_t::INDEXED_RGB_24;
	}
	else if (bitcount == 24)
	{
		m_pixelFormat = PixelFormat_t::RGB_24;
	}
	else if (bitcount == 32)
	{
		m_pixelFormat = PixelFormat_t::RGB_32;
	}
	else
		THROW(-1);

	m_bitmapData = (uint8*)gdiBitmapData;
#endif
}

#if 0
Bitmap::Bitmap(const DDSURFACEDESC* surfDesc)
{
	m_p = new Bitmap(surfDesc);
	m_p->AddRef();
}
#endif

#if 1

Bitmap::Bitmap(const _DDSURFACEDESC* surfDesc)
{
//	m_refcount = 0;
	m_locked = 0;
	m_bFreeData = false;

	ASSERT(0);
#if 0

	m_pixelFormat = PixelFormat_t::RGB_32;	// TODO
//	m_bitcount = 32;
	m_width = surfDesc->dwWidth;
	m_height = surfDesc->dwHeight;
	m_rowBytes = surfDesc->lPitch;
	m_bitmapData = (uint8*)surfDesc->lpSurface;
	//m_depthBuffer  = NULL;
#endif
}

#endif

#if 0
Bitmap::Bitmap(HINSTANCE hInstance, LPCTSTR name)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(hInstance, name, IMAGEBitmap, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap == NULL)
	{
		m_p = NULL;
		THROW(-1);
	}

	m_p = new Bitmap(hBitmap, NULL);
	m_p->AddRef();
}
#endif

#elif AMIGA

#if 0
Bitmap::Bitmap(struct BitMap* p96BitMap)
{
	m_p = new Bitmap(p96BitMap);
	m_p->AddRef();
}
#endif

Bitmap::Bitmap(struct BitMap* pBitmap)
{
//	m_refcount = 0;
	m_locked = 0;
	m_bFreeData = false;
	//m_depthBuffer  = NULL;

//	m_bmLock = 0;
	m_colors = NULL;

	m_width = 0;
	m_height = 0;
//	mBitmap = NULL;

	if (pBitmap == NULL)
		THROW(-1);

	if (!p96GetBitMapAttr(pBitmap, P96BMA_ISP96))
	{
		printf("Not a P96 bitmap\n");
		THROW(-1);
	}

//	mBitmap = pBitmap;
//	if (mBitmap)
	{
		struct RenderInfo ri;
	//	m_bmLock = p96LockBitMap(mBitmap, (UBYTE*)&ri, sizeof(ri));
	//	if (m_bmLock)
		ri.RGBFormat = (RGBFTYPE)p96GetBitMapAttr(pBitmap, P96BMA_RGBFORMAT);


		{
			m_width = p96GetBitMapAttr(pBitmap, P96BMA_WIDTH);
			m_height = p96GetBitMapAttr(pBitmap, P96BMA_HEIGHT);

			int bitcount;

			switch (ri.RGBFormat)
			{
			case RGBFB_CLUT:				/* palette mode, set colors when opening screen using
									tags or use SetRGB32/LoadRGB32(...) */
				{
					bitcount = 8;
					m_pixelFormat = PixelFormat_t::INDEXED_RGB_24;
				}
				break;

			case RGBFB_R8G8B8:			/* TrueColor RGB (8 bit each) */
			case RGBFB_B8G8R8:			/* TrueColor BGR (8 bit each) */
				{
					bitcount = 24;
					m_pixelFormat = PixelFormat_t::RGB_24;
				}
				break;

			case RGBFB_A8R8G8B8:		/* 4 Byte TrueColor ARGB (A unused alpha channel) */
			case RGBFB_A8B8G8R8:		/* 4 Byte TrueColor ABGR (A unused alpha channel) */
			case RGBFB_R8G8B8A8:		/* 4 Byte TrueColor RGBA (A unused alpha channel) */
			case RGBFB_B8G8R8A8:		/* 4 Byte TrueColor BGRA (A unused alpha channel) */
				{
					bitcount = 32;
					m_pixelFormat = PixelFormat_t::RGB_32;
				}
				break;

			default:
				printf("Unsupported p96 Bitmap Format\n");
				THROW(-1);
			}

			/*
			struct RenderInfo ri;
			m_bmLock = p96LockBitMap(mBitmap, (UBYTE*)&ri, sizeof(ri));
			m_rowBytes = ri.BytesPerRow;
			m_bitmapData = (uint8*)ri.Memory;
			*/
			m_rowBytes = p96GetBitMapAttr(pBitmap, P96BMA_BYTESPERROW);
			m_bitmapData = (uint8*)p96GetBitMapAttr(pBitmap, P96BMA_MEMORY);

			/*
			if (true)	// Private, can unlock right away, and the above will still be valid
			{
				p96UnlockBitMap(mBitmap, m_bmLock);
				m_bmLock = 0;
			}
			*/
		}
	}

	/*
	if (true)
	{
		m_depthBuffer = (uint8*)new float[m_width*m_height];
	}
	*/
}

#elif __APPLE__

#if 0
Bitmap::Bitmap(PixMapHandle pixMap)
{
	m_p = new Bitmap(pixMap);
	m_p->AddRef();
}
#endif

Bitmap::Bitmap(PixMapHandle pixMap)
{
//	m_refcount = 0;
	m_locked = 0;
	m_bFreeData = false;
	m_bitmapData = NULL;
	//m_depthBuffer  = NULL;
	m_colors = NULL;

	if (pixMap == NULL)
		THROW(-1);

	m_rowBytes = GetPixRowBytes(pixMap);
	m_bitmapData = (uint8*)GetPixBaseAddr(pixMap);
	m_bitcount = GetPixDepth(pixMap);

	m_pixelFormat = RGB_32;	// TODO

	::RectI rect;
	GetPixBounds(pixMap, &rect);

	// Adjust bitmap data to topleft
	//m_bitmapData += rect.top*m_rowBytes + rect.left*(m_bitcount>>3);

	m_width = rect.right-rect.left;
	m_height = rect.bottom-rect.top;
}

#endif

#if 0
Bitmap::Bitmap(int width, int height, PixelFormat_t pixelFormat)
{
	m_p = new Bitmap(width, height, pixelFormat);
	m_p->AddRef();
}
#endif

/*
Bitmap::Bitmap(D3D10Texture2D& texture2D)
{
}
*/

Bitmap::Bitmap(int width, int height, PixelFormat_t pixelFormat)
{
//	m_refcount = 0;
	m_locked = 0;
	m_bFreeData = true;
	m_bitmapData = NULL;
	m_colors = NULL;
	//m_depthBuffer = NULL;
	m_pixelFormat = 0;

	if (width <= 0)
		THROW(std::exception("Width must be > 0"));

	if (height == 0)
		THROW(std::exception("Height must be != 0"));

	uint8 bitcount = pixelFormat.GetBitCount();

	if (	bitcount != 1 &&
			bitcount != 4 &&
			bitcount != 8 &&
			bitcount != 16 &&
			bitcount != 24 &&
			bitcount != 32)
	{
		raise(Exception("Unsupported bitcount"));
	}

	m_pixelFormat = pixelFormat;

	/*
	switch (pixelFormat)
	{
	case RGB_24:
		m_bitcount = 24;
		break;

	case RGB_32:
		m_bitcount = 32;
		break;

	case RGBAP_32:
		m_bitcount = 32;
		break;

	case DEPTH_32:
		m_bitcount = 32;
		break;
		
	case GRAY_8:
		m_bitcount = 8;
		break;

	case GRAY_16:
		m_bitcount = 16;
		break;

	case RGBAP_4444:
		m_bitcount = 16;
		break;

	default:
		THROW(-1);
	}
*/

	m_width = width;
	m_height = abs(height);
	m_rowBytes = ROWBYTES_DWORD(m_width, bitcount);

	m_bitmapData = new uint8[m_rowBytes * m_height];
	if (m_bitmapData == NULL)
		THROW(-1);

	std::memset(m_bitmapData, 0, m_rowBytes * m_height);

	if (height < 0)
	{
		m_bitmapData = (uint8*)m_bitmapData + m_rowBytes * (m_height-1);
		m_rowBytes = -m_rowBytes;
	}

	/*
	if (true)
	{
		m_depthBuffer = (uint8*)new float[m_width*m_height];
	}
	*/
}

Bitmap::Bitmap(int width, int height, int rowbytes, PixelFormat_t pixelFormat, void* data)
{
	// Allow zero width/height ??

	if (width < 0) throw std::exception("Invalid width");
	if (height < 0) throw std::exception("Invalid height");

	m_width = width;
	m_height = height;
	m_rowBytes = rowbytes;
	m_pixelFormat = pixelFormat;
	m_bitmapData = (uint8*)data;
}

Bitmap::~Bitmap()
{
//	ASSERT(m_refcount == 0);
	ASSERT(m_locked == 0);

#if 0
#if AMIGA
	if (mBitmap)
	{
		/*
		if (m_bmLock)
		{
			p96UnlockBitMap(mBitmap, m_bmLock);
			m_bmLock = 0;
		}
		*/
		mBitmap = NULL;
	}
#endif
#endif

	if (m_bFreeData)
	{
		delete m_bitmapData;
		m_bitmapData = NULL;
	}

//	delete m_depthBuffer;
}

bool Bitmap::Equals(const Bitmap& other) const
{
	if (m_width != other.m_width) return false;
	if (m_height != other.m_height) return false;
	if (m_pixelFormat != other.m_pixelFormat) return false;

	// TODO, compare bitmap data

	return true;
}

void Bitmap::SetPixelFormat(PixelFormat_t pixelFormat)
{
	// TODO, some checks

	m_pixelFormat = pixelFormat;
}

int Bitmap::CopyBitmapData(int dstX, int dstY, Bitmap* srcBitmap, int srcX, int srcY, int srcWidth, int srcHeight)
{
	ASSERT(0);
#if 0
	if (srcBitmap == NULL) return -1;

	if (dstX < 0)
	{
		srcWidth += dstX;
		srcX -= dstX;
		dstX = 0;
	}

	if (dstY < 0)
	{
		srcHeight += dstY;
		srcY -= dstY;
		dstY = 0;
	}

	if (dstX+srcWidth > GetWidth())
	{
		srcWidth -= (dstX+srcWidth) - GetWidth();
	}

	if (dstY+srcHeight > GetHeight())
	{
		srcHeight -= (dstY+srcHeight) - GetHeight();
	}

	if (srcX+srcWidth > srcBitmap->GetWidth())
	{
		srcWidth -= (srcX+srcWidth) - srcBitmap->GetWidth();
	}

	if (srcY+srcHeight > srcBitmap->GetHeight())
	{
		srcHeight -= (srcY+srcHeight) - srcBitmap->GetHeight();
	}

	BitmapData dstBitmapData;
	if (LockBits(&LDraw::RectI(dstX, dstY, srcWidth, srcHeight), ImageLockModeWrite, &dstBitmapData) != 0)
		return -1;

	BitmapData srcBitmapData;
	if (srcBitmap->LockBits(&LDraw::RectI(srcX, srcY, srcWidth, srcHeight), ImageLockModeRead, &srcBitmapData) != 0)
	{
		UnlockBits(&dstBitmapData);
		return -1;
	}
	
	switch (srcBitmapData.PFormat)
	{
	case PixelFormat_t::RGB_24:
		{
			switch (dstBitmapData.PFormat)
			{
			case PixelFormat_t::RGB_24:
				{
					for (int y = 0; y < srcHeight; y++)
					{
						PixelRGB_24* src = (PixelRGB_24*)(srcBitmapData.Scan0 + srcBitmapData.Stride*(y));
						PixelRGB_24* dst = (PixelRGB_24*)(dstBitmapData.Scan0 + dstBitmapData.Stride*(y));
						
						for (int x = 0; x < srcWidth; x++)
						{
							*dst++ = *src++;
						}
					}
					break;
				}
				break;

			case PixelFormat_t::RGB_32:
				{
					for (int y = 0; y < srcHeight; y++)
					{
						PixelRGB_24* src = (PixelRGB_24*)(srcBitmapData.Scan0 + srcBitmapData.Stride*(y));
						PixelRGB_32* dst = (PixelRGB_32*)(dstBitmapData.Scan0 + dstBitmapData.Stride*(y));
						
						for (int x = 0; x < srcWidth; x++)
						{
							*dst++ = *src++;
						}
					}
					break;
				}
				break;

			case PixelFormat_t::RGBAP_32:
				{
					for (int y = 0; y < srcHeight; y++)
					{
						PixelRGB_24* src = (PixelRGB_24*)(srcBitmapData.Scan0 + srcBitmapData.Stride*(y));
						PixelRGBAP_32* dst = (PixelRGBAP_32*)(dstBitmapData.Scan0 + dstBitmapData.Stride*(y));
						
						for (int x = 0; x < srcWidth; x++)
						{
							*dst++ = *src++;
						}
					}
					break;
				}
				break;

			default:
				ASSERT(0);
			}
		}
		break;
		
	case PixelFormat_t::RGB_32:
		{
			switch (dstBitmapData.PFormat)
			{
			case PixelFormat_t::RGB_24:
				{
					for (int y = 0; y < srcHeight; y++)
					{
						PixelRGB_32* src = (PixelRGB_32*)(srcBitmapData.Scan0 + srcBitmapData.Stride*(y));
						PixelRGB_24* dst = (PixelRGB_24*)(dstBitmapData.Scan0 + dstBitmapData.Stride*(y));
						
						for (int x = 0; x < srcWidth; x++)
						{
							*dst++ = *src++;
						}
					}
					break;
				}
				break;

			case PixelFormat_t::RGB_32:
				{
					for (int y = 0; y < srcHeight; y++)
					{
						PixelRGB_32* src = (PixelRGB_32*)(srcBitmapData.Scan0 + srcBitmapData.Stride*(y));
						PixelRGB_32* dst = (PixelRGB_32*)(dstBitmapData.Scan0 + dstBitmapData.Stride*(y));
						
						for (int x = 0; x < srcWidth; x++)
						{
							*dst++ = *src++;
						}
					}
					break;
				}
				break;
				
			case PixelFormat_t::RGBAP_32:
				{
					for (int y = 0; y < srcHeight; y++)
					{
						PixelRGB_32* src = (PixelRGB_32*)(srcBitmapData.Scan0 + srcBitmapData.Stride*(y));
						PixelRGBAP_32* dst = (PixelRGBAP_32*)(dstBitmapData.Scan0 + dstBitmapData.Stride*(y));

						for (int x = 0; x < srcWidth; x++)
						{
							*dst++ = *src++;
						}
					}
				}
				break;
			}
		}
		break;

	case PixelFormat_t::RGBAP_32:
		{
			switch (dstBitmapData.PFormat)
			{
			case PixelFormat_t::RGBAP_32:
				{
					for (int y = 0; y < srcHeight; y++)
					{
						PixelRGBAP_32* src = (PixelRGBAP_32*)(srcBitmapData.Scan0 + srcBitmapData.Stride*(y));
						PixelRGBAP_32* dst = (PixelRGBAP_32*)(dstBitmapData.Scan0 + dstBitmapData.Stride*(y));

						for (int x = 0; x < srcWidth; x++)
						{
							*dst++ = *src++;
						}
					}
				}
				break;
			}
		}
		break;

	default:
		ASSERT(0);
	}

	srcBitmap->UnlockBits(&srcBitmapData);
	UnlockBits(&dstBitmapData);
#endif
	return 0;
}

Bitmap* Bitmap::Clone()
{
	return Clone(gm::RectI(0, 0, GetWidth(), GetHeight()));
}

Bitmap* Bitmap::Clone(PixelFormat_t pixelFormat)
{
	return Clone(gm::RectI(0, 0, GetWidth(), GetHeight()), pixelFormat);
}

Bitmap* Bitmap::Clone(const gm::RectI& rect)
{
	Bitmap* bitmap = new Bitmap(rect.Width, rect.Height, GetPixelFormat());

	bitmap->CopyBitmapData(0, 0, this, rect.X, rect.Y, rect.Width, rect.Height);

	/*
	for (int y = 0; y < rect.Height; y++)
	{
		DWORD* dest = (DWORD*)(pBitmap->m_p->m_bitmapData + pBitmap->m_p->m_rowBytes*y);
		DWORD* src = (DWORD*)(m_p->m_bitmapData + m_p->m_rowBytes*(rect.Y+y) + rect.X*4);

		for (int x = 0; x < rect.Width; x++)
		{
			*dest++ = *src++;
		}
	}
	*/

	return bitmap;
}

Bitmap* Bitmap::Clone(const gm::RectI& rect, uint32 pixelFormat)
{
	if (pixelFormat == GetPixelFormat())
	{
		return Clone(rect);
	}

	Bitmap* bitmap = new Bitmap(rect.Width, rect.Height, pixelFormat);

	bitmap->CopyBitmapData(0, 0, this, rect.X, rect.Y, rect.Width, rect.Height);

	/*
	if (m_p->m_pixelFormat == RGB_24 && pixelFormat == RGBA_32)
	{
		for (int y = 0; y < rect.Height; y++)
		{
			PixelRGBAP_32* dst = (PixelRGBAP_32*)(pBitmap->m_p->m_bitmapData + pBitmap->m_p->m_rowBytes*y);
			PixelRGB_24* src = (PixelRGB_24*)(m_p->m_bitmapData + m_p->m_rowBytes*(rect.Y+y) + rect.X*3);

			for (int x = 0; x < rect.Width; x++)
			{
				dst->r = src->r;
				dst->g = src->g;
				dst->b = src->b;
				dst->a = 255;

				src++;
				dst++;
			}
		}
	}
	else if (m_p->m_pixelFormat == RGB_24 && pixelFormat == RGB_32)
	{
		for (int y = 0; y < rect.Height; y++)
		{
			PixelRGBAP_32* dst = (PixelRGBAP_32*)(pBitmap->m_p->m_bitmapData + pBitmap->m_p->m_rowBytes*y);
			PixelRGB_24* src = (PixelRGB_24*)(m_p->m_bitmapData + m_p->m_rowBytes*(rect.Y+y) + rect.X*3);

			for (int x = 0; x < rect.Width; x++)
			{
				dst->r = src->r;
				dst->g = src->g;
				dst->b = src->b;

				src++;
				dst++;
			}
		}
	}
	else if (m_p->m_pixelFormat == RGB_32 && pixelFormat == RGB_24)
	{
		for (int y = 0; y < rect.Height; y++)
		{
			PixelRGB_24* dst = (PixelRGB_24*)(pBitmap->m_p->m_bitmapData + pBitmap->m_p->m_rowBytes*y);
			PixelRGBAP_32* src = (PixelRGBAP_32*)(m_p->m_bitmapData + m_p->m_rowBytes*(rect.Y+y) + rect.X*4);

			for (int x = 0; x < rect.Width; x++)
			{
				dst->r = src->r;
				dst->g = src->g;
				dst->b = src->b;

				src++;
				dst++;
			}
		}
	}
	else
	{
		ASSERT(0);
	}
	*/

	return bitmap;
}

#if 0
// virtual
int Bitmap::LockBits(const gm::RectI* prect, uint nFlags, BitmapData* lockedBitmapData)
{
	if (lockedBitmapData == NULL) THROW(-1);

	ASSERT(m_bitmapData);
	if (m_bitmapData == NULL) THROW(-1);

	if (nFlags & ImageLockModeWrite)
	{
		if (m_locked != 0)
		{
			ASSERT(0);
			return -1;
		}

		m_locked = -1;
	}
	else
	{
		if (m_locked < 0)
		{
			ASSERT(0);
			return -1;
		}

		m_locked++;
	}

	if (prect)
	{
		lockedBitmapData->Width = prect->Width;
		lockedBitmapData->Height = prect->Height;
		lockedBitmapData->PFormat = m_pixelFormat;
//		lockedBitmapData->BitCount = m_bitcount;
		lockedBitmapData->Stride = m_rowBytes;
		lockedBitmapData->Scan0 = m_bitmapData + m_rowBytes*prect->Y + prect->X * (m_pixelFormat.GetBitCount() >> 3);
		lockedBitmapData->Reserved = NULL;
	}
	else
	{
		lockedBitmapData->Width = m_width;
		lockedBitmapData->Height = m_height;
		lockedBitmapData->PFormat = m_pixelFormat;
//		lockedBitmapData->BitCount = m_bitcount;
		lockedBitmapData->Stride = m_rowBytes;
		lockedBitmapData->Scan0 = m_bitmapData;
		lockedBitmapData->Reserved = NULL;
	}

	return 0;
}

// virtual
void Bitmap::UnlockBits(BitmapData* lockedBitmapData)
{
	if (m_locked == -1)
		m_locked = 0;
	else
		m_locked--;
}
#endif

#if 0
int Bitmap::LockBits(const RectI* prect, uint nFlags, BitmapData* lockedBitmapData)
{
	return m_p->LockBits(prect, nFlags, lockedBitmapData);
}

int Bitmap::LockBits(const RectI* prect, uint nFlags, BitmapData* lockedBitmapData) const
{
	if (nFlags & ImageLockModeWrite)
	{
		THROW(-1);
		return -1;
	}

	return m_p->LockBits(prect, nFlags, lockedBitmapData);
}

void Bitmap::UnlockBits(BitmapData* lockedBitmapData)
{
	m_p->UnlockBits(lockedBitmapData);
}

void Bitmap::UnlockBits(BitmapData* lockedBitmapData) const
{
	m_p->UnlockBits(lockedBitmapData);
}
#endif

ARGB Bitmap::GetPixelARGB(unsigned int x, unsigned int y)
{
#if 0
	if (x < (unsigned int)m_width && y < (unsigned int)m_height)
	{
		switch (m_pixelFormat)
		{
		case PixelFormat_t::RGB_24:
			{
				PixelRGB_24* pixel = (PixelRGB_24*)(m_bitmapData + m_rowBytes*y + x*sizeof(PixelRGB_24));
				return (255<<24) | (pixel->r<<16) | (pixel->g<<8) | (pixel->b);
			}

		case PixelFormat_t::RGB_32:
			{
				PixelRGB_32* pixel = (PixelRGB_32*)(m_bitmapData + m_rowBytes*y + x*sizeof(PixelRGB_32));
				return (255<<24) | (pixel->r<<16) | (pixel->g<<8) | (pixel->b);
			}

		case PixelFormat_t::RGBAP_32:
			{
				return *(ARGB*)(m_bitmapData + m_rowBytes*y + x*sizeof(ARGB));
			}

		default:
			ASSERT(0);
			return 0;
		}
	}
#endif

	ASSERT(0);

	return 0;
}

#if _WINDOWS

#if 0

LXUIEXT void DrawString(HDC hDC, const char* str, int len, Font* pFont, const PointF& point, const gmMatrix3& transform)
{
	int x = 0;

	gmMatrix3 mat = transform;

//	mat = gmMatrix3::scale(1.0, -1.0) * mat;
	mat = gmMatrix3::translate(point.X, point.Y) * mat;
	mat = gmMatrix3::scale(1.0/64.0, 1.0/64.0) * mat;

	for (int i = 0; i < len; i++)
	{
		int glyphIndex = pFont->GetFamily()->CharToGlyph(str[i]);

	//	printf("glyph: %d\n", glyphIndex);

		const Glyph* pGlyph = pFont->GetGlyph(glyphIndex);
		if (pGlyph)
		{
			/*
#if _WINDOWS
			LDraw::Matrix matrix;
		//	matrix.Translate(0, 1024);
			matrix.Scale(1.0, -1.0);
			pPath->Transform(&matrix);
#else
*/		
			//pPath->Transform(gmMatrix3::scale(1.0, -1.0));
//#endif
			DrawPath(hDC, pGlyph->pPath, mat);
		//	delete pPath;
		}

		//TranslateTransform(pFont->m_horMetrics[glyphIndex].advanceWidth, 0);
		mat = gmMatrix3::translate(pFont->GetFamily()->m_horMetrics[glyphIndex].advanceWidth, 0) * mat;
		x += pFont->GetFamily()->m_horMetrics[glyphIndex].advanceWidth;
	}
}

#endif

#endif

struct RGBPixel8
{
	uint8 b;
	uint8 g;
	uint8 r;
};

/*
Dca' = Sca.Da + Sca.(1 - Da) + Dca.(1 - Sa)
= Sca + Dca.(1 - Sa)

Da'  = Sa.Da + Sa.(1 - Da) + Da.(1 - Sa)
= Sa + Da - Sa.Da

*/

inline uint8* src_over_pixel32_slow(uint8* dst, int Sa, int Sr, int Sg, int Sb)
{
	/*
	uint8 Da = dst[3];
	uint8 Dr = dst[2];
	uint8 Dg = dst[1];
	uint8 Db = dst[0];

	ASSERT(dst[0] <= dst[3]);
	ASSERT(dst[1] <= dst[3]);
	ASSERT(dst[2] <= dst[3]);
	*/

	*dst++ = Sb + (*dst * (255 - Sa) / 255);
	*dst++ = Sg + (*dst * (255 - Sa) / 255);
	*dst++ = Sr + (*dst * (255 - Sa) / 255);
	*dst++ = Sa + *dst - ((Sa * *dst) / 255);

	/*
	ASSERT(dst[-2] <= dst[-1]);
	ASSERT(dst[-3] <= dst[-1]);
	ASSERT(dst[-4] <= dst[-1]);
	*/

	return dst;
}

inline uint8* src_over_pixel_rgb_32(uint8* dst, int Sa, int Sr, int Sg, int Sb)
{

	ASSERT(0);
#if 0

#if _WINDOWS
	*dst++ = Sb + (multab[*dst][(255 - Sa)]);
	*dst++ = Sg + (multab[*dst][(255 - Sa)]);
	*dst++ = Sr + (multab[*dst][(255 - Sa)]);
	//*dst++ = Sa + *dst - (multab[Sa][*dst]);
	dst++;
#else
	*dst++ = Sb + (multab[*dst][(255 - Sa)]);
	*dst++ = Sg + (multab[*dst][(255 - Sa)]);
	*dst++ = Sr + (multab[*dst][(255 - Sa)]);
	*dst++;
//	*dst++ = Sa + *dst - (multab[Sa][*dst]);
#endif
#endif
	return dst;
}

inline uint8* src_over_pixel_rgba_32(uint8* dst, int Sa, int Sr, int Sg, int Sb)
{
	ASSERT(0);
#if 0
#if _WINDOWS
	*dst++ = Sb + (multab[*dst][(255 - Sa)]);
	*dst++ = Sg + (multab[*dst][(255 - Sa)]);
	*dst++ = Sr + (multab[*dst][(255 - Sa)]);
	*dst++ = Sa + *dst - (multab[Sa][*dst]);
#else
	*dst++ = Sb + (multab[*dst][(255 - Sa)]);
	*dst++ = Sg + (multab[*dst][(255 - Sa)]);
	*dst++ = Sr + (multab[*dst][(255 - Sa)]);
	*dst++ = Sa + *dst - (multab[Sa][*dst]);
#endif
#endif
	return dst;
}

inline uint8* src_copy_pixel32(uint8* dst, uint8 Sa, uint8 Sr, uint8 Sg, uint8 Sb)
{
	*dst++ = Sb;
	*dst++ = Sg;
	*dst++ = Sr;
	*dst++ = Sa;
	
	return dst;
}

/*

  y - scanline
  xLeft, xRight - subpixels

*/

D3D10Texture2D::D3D10Texture2D()
{
	m_d3d10_texture = NULL;
}

/*
D3D10Texture2D::D3D10Texture2D(ID3D10Device* device, int width, int height, DXGI_FORMAT pixelFormat)
{
	if (width <= 0 || height <= 0)
	{
		raise(Exception("width/height < 0"));
	}
	Create(device, width, height, pixelFormat);
}
*/

D3D10Texture2D::D3D10Texture2D(ID3D10Device* device, int width, int height, DXGI_FORMAT pixelFormat, D3D10_USAGE usage)
{
	if (width <= 0 || height <= 0)
	{
		raise(Exception("width/height <= 0"));
	}

	Create(device, width, height, pixelFormat, usage);
}

D3D10Texture2D::D3D10Texture2D(ID3D10Device* device, int width, int height, DXGI_FORMAT pixelFormat, void* initialSysMem, int sysMemPitch)
{
	if (width <= 0 || height <= 0)
	{
		raise(Exception("width/height <= 0"));
	}

	Create(device, width, height, pixelFormat, initialSysMem, sysMemPitch);
}

#if 0
void D3D10Texture2D::Create(ID3D10Device* pD3DDevice, int width, int height, DXGI_FORMAT pixelFormat)
{
	if (width <= 0 || height <= 0)
	{
		raise(Exception("width/height < 0"));
	}

	// Create the render target texture
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = pixelFormat;
	desc.SampleDesc.Count = 1;
	if (true)
	{
		desc.Usage = D3D10_USAGE_DEFAULT;
		desc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
	}
	else
	{
		desc.Usage = D3D10_USAGE_STAGING;

		desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		desc.BindFlags = /*D3D10_BIND_RENDER_TARGET |*/ D3D10_BIND_SHADER_RESOURCE;
	}

	desc.MiscFlags = 0;//D3D10_RESOURCE_MISC_GDI_COMPATIBLE;

	//ID3D10Texture2D *pTexture = NULL;
	HRESULT hr = pD3DDevice->CreateTexture2D(&desc, NULL, &m_d3d10_texture);
}
#endif

void D3D10Texture2D::Create(ID3D10Device* pD3DDevice, int width, int height, DXGI_FORMAT pixelFormat, D3D10_USAGE usage)
{
	if (width <= 0 || height <= 0)
	{
		raise(Exception("width/height <= 0"));
	}

	// Create the render target texture
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = pixelFormat;
	desc.SampleDesc.Count = 1;
	desc.Usage = usage;

	if (usage == D3D10_USAGE_DEFAULT)	// GPU Read/Write
	{
		desc.CPUAccessFlags = 0;
		desc.BindFlags = D3D10_BIND_SHADER_RESOURCE | D3D10_BIND_RENDER_TARGET;
	}
	else if (usage == D3D10_USAGE_DYNAMIC)		// GPU Read, CPU Write
	{
		desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	}
	else if (usage == D3D10_USAGE_STAGING) // CPU Read/Write
	{
		desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ;
		desc.BindFlags = 0;
	}
	else	// Immutable
	{
		desc.CPUAccessFlags = 0;
		desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	}

	desc.MiscFlags = 0;//D3D10_RESOURCE_MISC_GDI_COMPATIBLE;

	ThrowHr hr = pD3DDevice->CreateTexture2D(&desc, NULL, &m_d3d10_texture);
}

void D3D10Texture2D::Create(ID3D10Device* pD3DDevice, int width, int height, DXGI_FORMAT pixelFormat, void* initialSysMem, int sysMemPitch)
{
	if (width <= 0 || height <= 0)
	{
		raise(Exception("width/height <= 0"));
	}

	// Create the render target texture
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = pixelFormat;
	desc.SampleDesc.Count = 1;
	if (true)
	{
		desc.Usage = D3D10_USAGE_DEFAULT;
		desc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
	}
	else
	{
		desc.Usage = D3D10_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		desc.BindFlags = /*D3D10_BIND_RENDER_TARGET |*/ D3D11_BIND_SHADER_RESOURCE;
	}

	D3D10_SUBRESOURCE_DATA initialData;
	initialData.pSysMem = initialSysMem;
	initialData.SysMemPitch = sysMemPitch;

	ThrowHr hr = pD3DDevice->CreateTexture2D(&desc, &initialData, &m_d3d10_texture);
}

void Bitmap::CreateD3D10ShaderResourceView(ID3D10Device* pD3DDevice)
{
	D3D10_TEXTURE2D_DESC desc;
	m_d3d10_texture->GetDesc(&desc);

	D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;

	HRESULT hr = pD3DDevice->CreateShaderResourceView(m_d3d10_texture, &srvDesc, &m_d3d10_shaderResourceView);
	if (FAILED(hr))
	{
		raise(Exception("Failed to CreateShaderResourceView"));
	}
}

void Bitmap::CreateD3D10RenderTargetView(ID3D10Device* pD3DDevice)
{
	D3D10_TEXTURE2D_DESC desc;
	m_d3d10_texture->GetDesc(&desc);

	D3D10_RENDER_TARGET_VIEW_DESC srvDesc;
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipSlice = 0;

	HRESULT hr = pD3DDevice->CreateRenderTargetView(m_d3d10_texture, &srvDesc, &m_d3d10_renderTargetView);
	if (FAILED(hr))
	{
		raise(Exception("Failed to CreateRenderTargetView"));
	}
}

void Bitmap::CopyFromMemory(const void* data, int rowbytes)
{
	ASSERT(m_d3d10_texture);

	ASSERT(0);
#if 0
	D3D10_MAPPED_TEXTURE2D mappedTex;
	m_d3d10_texture->Map(D3D10CalcSubresource(0, 0, 1), D3D10_MAP_WRITE_DISCARD, 0, &mappedTex);

	// TODO

	UCHAR* src = (UCHAR*)data;
	UCHAR* pTexels = (UCHAR*)mappedTex.pData;
	for (UINT row = 0; row < m_height; ++row)
	{
		uint32* srcrow = (uint32*)(src + row * rowbytes);
		uint32* dstrow = (uint32*)(pTexels + row * mappedTex.RowPitch);
		for (UINT col = 0; col < m_width; ++col)
		{
			*dstrow++ = *srcrow++;
		}
	}

	m_d3d10_texture->Unmap(D3D10CalcSubresource(0, 0, 1));
#endif
}

ID3D10ShaderResourceView* Bitmap::GetD3D10ShaderResourceView()
{
	if (m_d3d10_shaderResourceView == NULL)
	{
		CreateD3D10ShaderResourceView(Direct10::get_D3DDevice());
	}

	return m_d3d10_shaderResourceView;
}

ID3D10RenderTargetView* Bitmap::GetD3D10RenderTargetView()
{
	if (m_d3d10_renderTargetView == NULL)
	{
		CreateD3D10RenderTargetView(Direct10::get_D3DDevice());
	}

	return m_d3d10_renderTargetView;
}

ID2D1Bitmap* Bitmap::GetD2D1Bitmap(RenderTarget* rt)
{
	if (m_d2d1bitmap == NULL)
	{
		HRESULT hr;

		ComPtr<IDXGISurface> surface;
		hr = m_d3d10_texture->QueryInterface(__uuidof(IDXGISurface), reinterpret_cast<void**>(&surface));

		if (m_d2d1renderTarget == NULL)
		{
			hr = Direct10::get_D2DFactory()->CreateDxgiSurfaceRenderTarget(
				 surface,
				  D2D1::RenderTargetProperties(
						D2D1_RENDER_TARGET_TYPE_DEFAULT,
						D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
				  &m_d2d1renderTarget);
		}

		hr = rt->m_spRT->CreateSharedBitmap(__uuidof(IDXGISurface), surface,
			&D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
			&m_d2d1bitmap);

		/*
		switch (hr)
		{
		case D2DERR_INVALID_CALL:
			Std::get_Out() << "Invalid call";
			break;

		case D2DERR_INTERNAL_ERROR:
			Std::get_Out() << "Internal error";
			break;

		case D2DERR_TARGET_NOT_GDI_COMPATIBLE:
			Std::get_Out() << "Target not GDI compatible";
			break;
		}
		*/
	}

	return m_d2d1bitmap;
}

// static
Bitmap* Bitmap::FromFile(StringIn filename)
{
	return new Bitmap(filename);
}

// static
Bitmap* Bitmap::FromHICON(HICON hIcon)
{
	int width = 32;
	int height = 32;

	BITMAPV5HEADER bi;
	memset(&bi, 0, sizeof(BITMAPV5HEADER));
	bi.bV5Size = sizeof(BITMAPV5HEADER);
	bi.bV5Width = width;
	bi.bV5Height = height;
	bi.bV5Planes = 1;
	bi.bV5BitCount = 32;
	bi.bV5Compression = BI_BITFIELDS;
	// The following mask specification specifies a supported 32 BPP
	// alpha format for Windows XP.
	bi.bV5RedMask   =  0x00FF0000;
	bi.bV5GreenMask =  0x0000FF00;
	bi.bV5BlueMask  =  0x000000FF;
	bi.bV5AlphaMask =  0xFF000000;

	/*
	bi.biSize = sizeof(BITMAPV5HEADER);
	bi.biWidth = width;
	bi.biHeight = height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	*/
	void* bits = NULL;
	HBITMAP hBitmap = CreateDIBSection(NULL, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, NULL, 0);
	if (hBitmap)
	{
		HDC hDC = CreateCompatibleDC(NULL);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);

		UINT istepAniCur = 0;
		UINT diFlags = DI_NORMAL;
		DrawIconEx(hDC, 0, 0, hIcon, width, height, istepAniCur, NULL, diFlags);

		SelectObject(hDC, hOldBitmap);
		DeleteDC(hDC);
	}

	Bitmap* bitmap = new Bitmap(Direct10::get_D3DDevice1(),
		D3D10Texture2D(
			Direct10::get_D3DDevice1(),
			width, height, DXGI_FORMAT_R8G8B8A8_UNORM, bits, ROWBYTES_DWORD(width, 32)
			)
		);

	DeleteObject(hBitmap);

	return bitmap;
}

ComPtr<IDirect3D9>						m_D3D;
ComPtr<IDirect3D9Ex>					m_D3DEx;
ComPtr<IDirect3DDevice9>				m_D3DDev;
ComPtr<IDirect3DDevice9Ex>				m_D3DDevEx;

void CreateD9()
{
	if (m_D3D == NULL)
	{
		HRESULT hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_D3DEx);
		m_D3D = m_D3DEx;

		HWindow* win = new HWindow();
		win->CreateOverlapped(L"OpenGL");
		HWND m_hWnd = win->get_Hwnd();

		if (true)
		{
			m_D3DDev = nullptr;
			D3DDISPLAYMODE dm;
			hr = m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);

		//	D3DDISPLAYMODEEX dmex;
			//dmex.Size = sizeof(D3DDISPLAYMODEEX);

			D3DPRESENT_PARAMETERS pp;
			ZeroMemory(&pp, sizeof(pp));
			pp.BackBufferWidth = 8;
			pp.BackBufferHeight = 8;
			pp.Windowed = TRUE;
			pp.hDeviceWindow = m_hWnd;
			pp.SwapEffect = D3DSWAPEFFECT_COPY;

			if (m_D3DEx)
			{
			//	hr = m_D3DEx->GetAdapterDisplayModeEx(D3DADAPTER_DEFAULT, &dmex, NULL);
			//pp.BackBufferFormat = dmex.Format;

				hr = m_D3DEx->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
					D3DCREATE_MIXED_VERTEXPROCESSING |
					//D3DCREATE_SOFTWARE_VERTEXPROCESSING |
					D3DCREATE_MULTITHREADED,
					&pp,
					NULL,	// must be NULL for windowed mode
					&m_D3DDevEx);

				m_D3DDev = m_D3DDevEx;
			}

			if (m_D3DDev == NULL)
			{
				hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
					D3DCREATE_MIXED_VERTEXPROCESSING |
					//D3DCREATE_SOFTWARE_VERTEXPROCESSING |
					D3DCREATE_MULTITHREADED,
					&pp, &m_D3DDev);
			}

			if (FAILED(hr))
			{
				switch (hr)
				{
				case D3DERR_DEVICELOST:
					raise(Exception("D3D9: Device lost", NULL, hr));

				case D3DERR_INVALIDCALL:
					raise(Exception("D3D9: Invalid Call", NULL, hr));

				case D3DERR_NOTAVAILABLE:
					raise(Exception("D3D9: Not available", NULL, hr));

				case D3DERR_OUTOFVIDEOMEMORY:
					raise(Exception("D3D9: Out of video memory", NULL, hr));

				default:
					raise_(Exception::FromHResult(hr));
				}
			}
		}
	}
}

// static
Bitmap* Bitmap::CreateSharedRenderTarget(unsigned int width, unsigned int height, bool alpha)
{
	CreateD9();

	ComPtr<IDirect3DTexture9> texture = nullptr;
	HANDLE shared = NULL;

	HRESULT hr = m_D3DDevEx->CreateTexture(
			width, height, 1, D3DUSAGE_RENDERTARGET,
			alpha? D3DFMT_A8R8G8B8 : D3DFMT_X8R8G8B8,
		//	D3DFMT_X8B8G8R8,//lpAllocInfo->Format,
			D3DPOOL_DEFAULT,
			&texture,
			&shared
			);
	if (FAILED(hr)) return nullptr;

	ComPtr<ID3D10Texture2D> texture10 = nullptr;
	hr = Direct10::get_D3DDevice1()->OpenSharedResource(shared, __uuidof(ID3D11Texture2D), (void**)&texture10);
	if (FAILED(hr)) return nullptr;

	Bitmap* bitmap = new Bitmap(width, height, 0, PixelFormat_t::RGBAP_32, nullptr);
	bitmap->m_d3d9_texture = texture.Detach();
	bitmap->m_shared = shared;
	bitmap->m_d3d10_texture = texture10.Detach();

	return bitmap;
}

Bitmap* Bitmap::CreateSharedDepth(unsigned int width, unsigned int height, uint depthbits)
{
	if (!(depthbits == 0 ||
		depthbits == 16 ||
		depthbits == 24 ||
		depthbits == 32))
	{
		raise(ArgumentException());
	}
	
	CreateD9();

	ComPtr<IDirect3DTexture9> texture;
	HANDLE shared = NULL;

	HRESULT hr = m_D3DDevEx->CreateTexture(
			width, height, 1, D3DUSAGE_DEPTHSTENCIL,
			depthbits > 16? D3DFMT_D32 : D3DFMT_D16,
			D3DPOOL_DEFAULT,
			&texture,
			&shared
			);
	if (FAILED(hr)) return NULL;

	ComPtr<ID3D10Texture2D> texture10 = nullptr;
	hr = Direct10::get_D3DDevice1()->OpenSharedResource(shared, __uuidof(ID3D11Texture2D), (void**)&texture10);
	if (FAILED(hr)) return NULL;

	Bitmap* bitmap = new Bitmap(width, height, 0, PixelFormat_t::RGBAP_32, NULL);
	bitmap->m_shared = shared;
	bitmap->m_d3d9_texture = texture.Detach();
	bitmap->m_d3d10_texture = texture10.Detach();

	return bitmap;
}

Bitmap* Bitmap::CreateSharedDepthStencil(unsigned int width, unsigned int height)
{
	CreateD9();

	IDirect3DTexture9* texture = NULL;
	HANDLE shared = NULL;

	HRESULT hr = m_D3DDevEx->CreateTexture(
			width, height, 1, D3DUSAGE_DEPTHSTENCIL,
			D3DFMT_D24FS8,
			D3DPOOL_DEFAULT,
			&texture,
			&shared
			);
	if (FAILED(hr)) return nullptr;

	ComPtr<ID3D10Texture2D> texture10 = nullptr;
	hr = Direct10::get_D3DDevice1()->OpenSharedResource(shared, __uuidof(ID3D11Texture2D), (void**)&texture10);
	if (FAILED(hr)) return nullptr;

	Bitmap* bitmap = new Bitmap(width, height, 0, PixelFormat_t::RGBAP_32, nullptr);
	bitmap->m_d3d9_texture = texture;
	bitmap->m_shared = shared;
	bitmap->m_d3d10_texture = texture10.Detach();

	return bitmap;
}

}	// Graphics
}	// System
