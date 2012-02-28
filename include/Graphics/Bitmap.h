#ifndef __dxgiformat_h__
#define __dxgiformat_h__

#define DXGI_FORMAT_DEFINED 1

typedef enum DXGI_FORMAT
{
    DXGI_FORMAT_UNKNOWN	                    = 0,
    DXGI_FORMAT_R32G32B32A32_TYPELESS       = 1,
    DXGI_FORMAT_R32G32B32A32_FLOAT          = 2,
    DXGI_FORMAT_R32G32B32A32_UINT           = 3,
    DXGI_FORMAT_R32G32B32A32_SINT           = 4,
    DXGI_FORMAT_R32G32B32_TYPELESS          = 5,
    DXGI_FORMAT_R32G32B32_FLOAT             = 6,
    DXGI_FORMAT_R32G32B32_UINT              = 7,
    DXGI_FORMAT_R32G32B32_SINT              = 8,
    DXGI_FORMAT_R16G16B16A16_TYPELESS       = 9,
    DXGI_FORMAT_R16G16B16A16_FLOAT          = 10,
    DXGI_FORMAT_R16G16B16A16_UNORM          = 11,
    DXGI_FORMAT_R16G16B16A16_UINT           = 12,
    DXGI_FORMAT_R16G16B16A16_SNORM          = 13,
    DXGI_FORMAT_R16G16B16A16_SINT           = 14,
    DXGI_FORMAT_R32G32_TYPELESS             = 15,
    DXGI_FORMAT_R32G32_FLOAT                = 16,
    DXGI_FORMAT_R32G32_UINT                 = 17,
    DXGI_FORMAT_R32G32_SINT                 = 18,
    DXGI_FORMAT_R32G8X24_TYPELESS           = 19,
    DXGI_FORMAT_D32_FLOAT_S8X24_UINT        = 20,
    DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS    = 21,
    DXGI_FORMAT_X32_TYPELESS_G8X24_UINT     = 22,
    DXGI_FORMAT_R10G10B10A2_TYPELESS        = 23,
    DXGI_FORMAT_R10G10B10A2_UNORM           = 24,
    DXGI_FORMAT_R10G10B10A2_UINT            = 25,
    DXGI_FORMAT_R11G11B10_FLOAT             = 26,
    DXGI_FORMAT_R8G8B8A8_TYPELESS           = 27,
    DXGI_FORMAT_R8G8B8A8_UNORM              = 28,
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB         = 29,
    DXGI_FORMAT_R8G8B8A8_UINT               = 30,
    DXGI_FORMAT_R8G8B8A8_SNORM              = 31,
    DXGI_FORMAT_R8G8B8A8_SINT               = 32,
    DXGI_FORMAT_R16G16_TYPELESS             = 33,
    DXGI_FORMAT_R16G16_FLOAT                = 34,
    DXGI_FORMAT_R16G16_UNORM                = 35,
    DXGI_FORMAT_R16G16_UINT                 = 36,
    DXGI_FORMAT_R16G16_SNORM                = 37,
    DXGI_FORMAT_R16G16_SINT                 = 38,
    DXGI_FORMAT_R32_TYPELESS                = 39,
    DXGI_FORMAT_D32_FLOAT                   = 40,
    DXGI_FORMAT_R32_FLOAT                   = 41,
    DXGI_FORMAT_R32_UINT                    = 42,
    DXGI_FORMAT_R32_SINT                    = 43,
    DXGI_FORMAT_R24G8_TYPELESS              = 44,
    DXGI_FORMAT_D24_UNORM_S8_UINT           = 45,
    DXGI_FORMAT_R24_UNORM_X8_TYPELESS       = 46,
    DXGI_FORMAT_X24_TYPELESS_G8_UINT        = 47,
    DXGI_FORMAT_R8G8_TYPELESS               = 48,
    DXGI_FORMAT_R8G8_UNORM                  = 49,
    DXGI_FORMAT_R8G8_UINT                   = 50,
    DXGI_FORMAT_R8G8_SNORM                  = 51,
    DXGI_FORMAT_R8G8_SINT                   = 52,
    DXGI_FORMAT_R16_TYPELESS                = 53,
    DXGI_FORMAT_R16_FLOAT                   = 54,
    DXGI_FORMAT_D16_UNORM                   = 55,
    DXGI_FORMAT_R16_UNORM                   = 56,
    DXGI_FORMAT_R16_UINT                    = 57,
    DXGI_FORMAT_R16_SNORM                   = 58,
    DXGI_FORMAT_R16_SINT                    = 59,
    DXGI_FORMAT_R8_TYPELESS                 = 60,
    DXGI_FORMAT_R8_UNORM                    = 61,
    DXGI_FORMAT_R8_UINT                     = 62,
    DXGI_FORMAT_R8_SNORM                    = 63,
    DXGI_FORMAT_R8_SINT                     = 64,
    DXGI_FORMAT_A8_UNORM                    = 65,
    DXGI_FORMAT_R1_UNORM                    = 66,
    DXGI_FORMAT_R9G9B9E5_SHAREDEXP          = 67,
    DXGI_FORMAT_R8G8_B8G8_UNORM             = 68,
    DXGI_FORMAT_G8R8_G8B8_UNORM             = 69,
    DXGI_FORMAT_BC1_TYPELESS                = 70,
    DXGI_FORMAT_BC1_UNORM                   = 71,
    DXGI_FORMAT_BC1_UNORM_SRGB              = 72,
    DXGI_FORMAT_BC2_TYPELESS                = 73,
    DXGI_FORMAT_BC2_UNORM                   = 74,
    DXGI_FORMAT_BC2_UNORM_SRGB              = 75,
    DXGI_FORMAT_BC3_TYPELESS                = 76,
    DXGI_FORMAT_BC3_UNORM                   = 77,
    DXGI_FORMAT_BC3_UNORM_SRGB              = 78,
    DXGI_FORMAT_BC4_TYPELESS                = 79,
    DXGI_FORMAT_BC4_UNORM                   = 80,
    DXGI_FORMAT_BC4_SNORM                   = 81,
    DXGI_FORMAT_BC5_TYPELESS                = 82,
    DXGI_FORMAT_BC5_UNORM                   = 83,
    DXGI_FORMAT_BC5_SNORM                   = 84,
    DXGI_FORMAT_B5G6R5_UNORM                = 85,
    DXGI_FORMAT_B5G5R5A1_UNORM              = 86,
    DXGI_FORMAT_B8G8R8A8_UNORM              = 87,
    DXGI_FORMAT_B8G8R8X8_UNORM              = 88,
    DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM  = 89,
    DXGI_FORMAT_B8G8R8A8_TYPELESS           = 90,
    DXGI_FORMAT_B8G8R8A8_UNORM_SRGB         = 91,
    DXGI_FORMAT_B8G8R8X8_TYPELESS           = 92,
    DXGI_FORMAT_B8G8R8X8_UNORM_SRGB         = 93,
    DXGI_FORMAT_BC6H_TYPELESS               = 94,
    DXGI_FORMAT_BC6H_UF16                   = 95,
    DXGI_FORMAT_BC6H_SF16                   = 96,
    DXGI_FORMAT_BC7_TYPELESS                = 97,
    DXGI_FORMAT_BC7_UNORM                   = 98,
    DXGI_FORMAT_BC7_UNORM_SRGB              = 99,
    DXGI_FORMAT_FORCE_UINT                  = 0xffffffff
} DXGI_FORMAT;

#endif // __dxgiformat_h__

typedef struct HPALETTE__ * HPALETTE;

struct _DDSURFACEDESC;
struct tagBITMAPINFO;

struct tagRGBQUAD;

#if AMIGA

/*
struct tagRGBQUAD
{
	uint8 rgbBlue;
	uint8 rgbGreen;
	uint8 rgbRed;
	uint8 rgbReserved;
};
*/

#endif

//#endif

//#if __APPLE__

typedef struct PixMap PixMap;
typedef PixMap * PixMapPtr;
typedef PixMapPtr * PixMapHandle;

//#endif

//#if AMIGA

struct BitMap;

//#endif

#ifdef __LERSTAD__

typedef struct D3D10_MAPPED_TEXTURE2D
    {
    void *pData;
    UINT RowPitch;
    } 	D3D10_MAPPED_TEXTURE2D;

#endif

namespace System
{
namespace Graphics
{

struct RGB
{
	uint8 r;
	uint8 g;
	uint8 b;
	uint8 pen;
};

class RGBTriple
{
public:
	inline CTOR RGBTriple()
	{
		r = g = b = 0;
	}

	inline CTOR RGBTriple(uint8 _r, uint8 _g, uint8 _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}

	uint8 r;
	uint8 g;
	uint8 b;

	bool operator == (const RGBTriple& other) const
	{
		return (r == other.r) && (g == other.g) && (b == other.b);
	}

	bool operator != (const RGBTriple& other) const
	{
		return !(*this == other);
	}

	uint8& operator [] (size_t index)
	{
		switch (index)
		{
		case 0: return r;
		case 1: return g;
		case 2: return b;
		default:
			ASSERT(0);
		}
	}

	uint8 operator [] (size_t index) const
	{
		switch (index)
		{
		case 0: return r;
		case 1: return g;
		case 2: return b;
		default:
			ASSERT(0);
		}
		return 0;
	}
};

//kdtree<RGBTriple, uint8>::node* maketree(RGB* rgb, int count, int depth);

class GfxExt ColorMatrixF
{
public:
	CTOR ColorMatrixF();

	CTOR ColorMatrixF(
		float m00, float m01, float m02, float m03, float m04,
		float m10, float m11, float m12, float m13, float m14,
		float m20, float m21, float m22, float m23, float m24,
		float m30, float m31, float m32, float m33, float m34);

	CTOR ColorMatrixF(
		float m00, float m01, float m02, float m03, float m04,
		float m10, float m11, float m12, float m13, float m14,
		float m20, float m21, float m22, float m23, float m24,
		float m30, float m31, float m32, float m33, float m34,
		float m40, float m41, float m42, float m43, float m44);

	ColorMatrixF operator *(const ColorMatrixF& M) const;

	float m[5][5];

	static ColorMatrixF colorMatrixIdentity;
};

class GfxExt PixelFormat_t
{
public:
	inline CTOR PixelFormat_t()
	{
		m_value = 0;
	}

	inline CTOR PixelFormat_t(uint32 _value)
	{
		m_value = _value;
	}

	inline uint8 GetBitCount() const
	{
		return (uint8)m_value;	// lower 8 bits
	}

	inline operator uint32 () const
	{
		return m_value;
	}

	enum
	{
		INDEXED_RGB_24	=	((1<<8) | 8),
		INDEXED_RGBA_32 =	((2<<8) | 8),
		GRAY_8 =				((10<<8) | 8),
		GRAY_16 =			((11<<8) | 16),
		HDR_32 =				((15<<8) | 32),
		RGB_24 =				((20<<8) | 24),
		RGB_32 =				((21<<8) | 32),
		RGBAP_32	=			((22<<8) | 32),
		RGBAP_4444	=		((23<<8) | 16),
		DEPTH_32	=			((24<<8) | 32),
	};

protected:

	uint32 m_value;
};

#if 0
////////////////////////////////
class PixelLum
{
public:
	inline CTOR PixelLum()
	{
	}

	inline CTOR PixelLum(uint8 _v)
	{
		v = _v;
	}

	typedef PixelLumAP alpha_t;

	uint8 v;
};

class PixelLumAP
{
public:
	inline CTOR PixelLumAP()
	{
	}

	inline CTOR PixelLumAP(uint8 _v, uint8 _a)
	{
		v = _v;
		a = _a;
	}

	inline CTOR PixelLumAP(const PixelLum other)
	{
		v = other.v;
		a = 255;
	}

	inline PixelLumAP& operator = (const PixelLum other)
	{
		v = other.v;
		a = 255;
		return *this;
	}

	/*
	inline PixelLumAP& operator = (const PixelRGB_24 other);
	inline PixelLumAP& operator = (const PixelRGB_32 other);
	inline PixelLumAP& operator = (const PixelRGBAP_32 other);
	*/

	uint8 v;
	uint8 a;

	inline void clear()
	{
		v = 0;
		a = 0;
	}

	typedef PixelLumAP alpha_t;
};

class PixelLum_HDR
{
public:
	inline CTOR PixelLum_HDR()
	{
	}

	inline CTOR PixelLum_HDR(float _v)
	{
		v = _v;
	}

	float v;
};

class PixelRGB_24
{
public:

	inline CTOR PixelRGB_24()
	{
	}

	inline CTOR PixelRGB_24(const PixelRGB_32 other);

#if WIN32

	uint8 b;
	uint8 g;
	uint8 r;

#elif AMIGA || __APPLE__

	uint8 r;
	uint8 g;
	uint8 b;

#endif

	inline CTOR PixelRGB_24(const PixelLum other)
	{
		r = g = b = other.v;
	}

	typedef PixelRGBAP_32 alpha_t;
};

class PixelRGB_32
{
public:

#if WIN32

	uint8 b;
	uint8 g;
	uint8 r;
	uint8 pad;

#elif AMIGA

	uint8 r;
	uint8 g;
	uint8 b;
	uint8 pad;

#elif __APPLE__

	uint8 pad;
	uint8 r;
	uint8 g;
	uint8 b;

#endif

	inline CTOR PixelRGB_32()
	{
	}

	inline CTOR PixelRGB_32(uint8 _r, uint8 _g, uint8 _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}

	inline CTOR PixelRGB_32(const PixelLum other)
	{
		r = g = b = other.v;
	}

	inline CTOR PixelRGB_32(const PixelRGB_24 other);
	inline CTOR PixelRGB_32(const PixelRGBAP_32 other);

	inline PixelRGB_32& operator = (const PixelRGB_24 src)
	{
		r = src.r;
		g = src.g;
		b = src.b;
		return *this;
	}

	typedef PixelRGBAP_32 alpha_t;
};

class PixelRGBAP_32
{
public:

#if WIN32

	uint8 b;
	uint8 g;
	uint8 r;
	uint8 a;

	inline CTOR PixelRGBAP_32(uint8 _a, uint8 _r, uint8 _g, uint8 _b)
	{
		b = _b;
		g = _g;
		r = _r;
		a = _a;
	}

#define PixelRGBA_Args(r, g, b, a) a, r, g, b

#elif AMIGA

	uint8 r;
	uint8 g;
	uint8 b;
	uint8 a;

	inline CTOR PixelRGBAP_32(uint8 _a, uint8 _b, uint8 _g, uint8 _r)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

#define PixelRGBA_Args(r, g, b, a) a, b, g, r

#elif __APPLE__

	uint8 a;
	uint8 r;
	uint8 g;
	uint8 b;

	inline CTOR PixelRGBAP_32(uint8 _b, uint8 _g, uint8 _r, uint8 _a)
	{
		a = _a;
		r = _r;
		g = _g;
		b = _b;
	}

#define PixelRGBA_Args(r, g, b, a) b, g, r, a

#endif

	inline CTOR PixelRGBAP_32()
	{
	}

	inline CTOR PixelRGBAP_32(const PixelLum src);
	inline CTOR PixelRGBAP_32(const PixelLumAP src);
	inline CTOR PixelRGBAP_32(const PixelRGB_24 src);
	inline CTOR PixelRGBAP_32(const PixelRGB_32 src);
	inline CTOR PixelRGBAP_32(const PixelRGBAP_4444 src);
	inline PixelRGBAP_32& operator = (const PixelLum src);
	inline PixelRGBAP_32& operator = (const PixelLumAP src);
	inline PixelRGBAP_32& operator = (const PixelRGB_24 src);
	inline PixelRGBAP_32& operator = (const PixelRGB_32 src);
	inline PixelRGBAP_32& operator = (const PixelRGBAP_4444 src);

	inline PixelRGBAP_32 operator + (const PixelRGBAP_32 other) const
	{
		return PixelRGBAP_32(r + other.r, g + other.g, b + other.b, a + other.a);
	}

	inline void clear()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	typedef PixelRGBAP_32 alpha_t;
};

class PixelRGBA_32
{
public:

#if WIN32

	uint8 b;
	uint8 g;
	uint8 r;
	uint8 a;

	inline CTOR PixelRGBA_32(uint8 _a, uint8 _r, uint8 _g, uint8 _b)
	{
		b = _b;
		g = _g;
		r = _r;
		a = _a;
	}

#elif AMIGA

	uint8 r;
	uint8 g;
	uint8 b;
	uint8 a;

	inline CTOR PixelRGBA_32(uint8 _a, uint8 _b, uint8 _g, uint8 _r)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

#elif __APPLE__

	uint8 a;
	uint8 r;
	uint8 g;
	uint8 b;

	inline CTOR PixelRGBA_32(uint8 _b, uint8 _g, uint8 _r, uint8 _a)
	{
		a = _a;
		r = _r;
		g = _g;
		b = _b;
	}

#endif

	inline CTOR PixelRGBA_32()
	{
	}

	/*
	inline PixelRGBAP_32(const PixelLum src);
	inline PixelRGBAP_32(const PixelLumAP src);
	inline PixelRGBAP_32(const PixelRGB_24 src);
	inline PixelRGBAP_32(const PixelRGB_32 src);
	inline PixelRGBAP_32(const PixelRGBAP_4444 src);
	inline PixelRGBAP_32& operator = (const PixelLum src);
	inline PixelRGBAP_32& operator = (const PixelLumAP src);
	inline PixelRGBAP_32& operator = (const PixelRGB_24 src);
	inline PixelRGBAP_32& operator = (const PixelRGB_32 src);
	inline PixelRGBAP_32& operator = (const PixelRGBAP_4444 src);

	inline PixelRGBAP_32 operator + (const PixelRGBAP_32 other) const
	{
		return PixelRGBAP_32(r + other.r, g + other.g, b + other.b, a + other.a);
	}

	inline void clear()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	typedef PixelRGBAP_32 alpha_t;
	*/
};

class PixelRGBAP_4444
{
public:
	uint8 b : 4;
	uint8 g : 4;
	uint8 r : 4;
	uint8 a : 4;

	inline CTOR PixelRGBAP_4444()
	{
	}

	inline CTOR PixelRGBAP_4444(uint8 _r, uint8 _g, uint8 _b, uint8 _a)
	{
		b = _b;
		g = _g;
		r = _r;
		a = _a;
	}

	inline CTOR PixelRGBAP_4444(const PixelLum src)
	{
		b = g = r = src.v>>4;
		a = 15;
	}

	inline CTOR PixelRGBAP_4444(const PixelLumAP src)
	{
		b = g = r = src.v>>4;
		a = src.a>>4;
	}

	inline CTOR PixelRGBAP_4444(const PixelRGB_24 src)
	{
		b = src.b>>4;
		g = src.g>>4;
		r = src.r>>4;
		a = 15;
	}

	inline CTOR PixelRGBAP_4444(const PixelRGB_32 src)
	{
		b = src.b>>4;
		g = src.g>>4;
		r = src.r>>4;
		a = 15;
	}

	inline CTOR PixelRGBAP_4444(const PixelRGBAP_32 src)
	{
		b = src.b>>4;
		g = src.g>>4;
		r = src.r>>4;
		a = src.a>>4;
	}

	inline void clear()
	{
		b = 0;
		g = 0;
		r = 0;
		a = 0;
	}

	inline PixelRGBAP_4444& operator = (const PixelLum src)
	{
		b = g = r = src.v>>4;
		a = 15;
		return *this;
	}

	inline PixelRGBAP_4444& operator = (const PixelLumAP src)
	{
		b = g = r = src.v>>4;
		a = src.a>>4;
		return *this;
	}

	inline PixelRGBAP_4444& operator = (const PixelRGB_24 src)
	{
		b = src.b>>4;
		g = src.g>>4;
		r = src.r>>4;
		a = 15;
		return *this;
	}

	inline PixelRGBAP_4444& operator = (const PixelRGB_32 src)
	{
		b = src.b>>4;
		g = src.g>>4;
		r = src.r>>4;
		a = 15;
		return *this;
	}

	inline PixelRGBAP_4444& operator = (const PixelRGBAP_32 src)
	{
		b = src.b>>4;
		g = src.g>>4;
		r = src.r>>4;
		a = src.a>>4;
		return *this;
	}

	typedef PixelRGBAP_4444 alpha_t;
};

inline PixelRGB_32::PixelRGB_32(const PixelRGBAP_32 other)
{
	*(uint32*)this = *(const uint32*)&other;
}

inline PixelRGB_24::PixelRGB_24(const PixelRGB_32 other)
{
	r = other.r;
	g = other.g;
	b = other.b;
}

inline PixelRGB_32::PixelRGB_32(const PixelRGB_24 other)
{
	r = other.r;
	g = other.g;
	b = other.b;
}

inline PixelRGBAP_32::PixelRGBAP_32(const PixelLum src)
{
	r = g = b = src.v;
	a = 255;
}

inline PixelRGBAP_32::PixelRGBAP_32(const PixelLumAP src)
{
	r = g = b = src.v;
	a = src.a;
}

inline PixelRGBAP_32::PixelRGBAP_32(const PixelRGB_24 src)
{
	r = src.r;
	g = src.g;
	b = src.b;
	a = 255;
}

inline PixelRGBAP_32::PixelRGBAP_32(const PixelRGB_32 src)
{
	r = src.r;
	g = src.g;
	b = src.b;
	a = 255;
}

inline PixelRGBAP_32::PixelRGBAP_32(const PixelRGBAP_4444 src)
{
	r = (src.r<<4) | src.r;
	g = (src.g<<4) | src.g;
	b = (src.b<<4) | src.b;
	a = (src.a<<4) | src.a;
}

inline PixelRGBAP_32& PixelRGBAP_32::operator = (const PixelLum src)
{
	r = g = b = src.v;
	a = 255;
	return *this;
}

inline PixelRGBAP_32& PixelRGBAP_32::operator = (const PixelLumAP src)
{
	r = g = b = src.v;
	a = src.a;
	return *this;
}

inline PixelRGBAP_32& PixelRGBAP_32::operator = (const PixelRGB_24 src)
{
	r = src.r;
	g = src.g;
	b = src.b;
	a = 255;
	return *this;
}

inline PixelRGBAP_32& PixelRGBAP_32::operator = (const PixelRGB_32 src)
{
	r = src.r;
	g = src.g;
	b = src.b;
	a = 255;
	return *this;
}

inline PixelRGBAP_32& PixelRGBAP_32::operator = (const PixelRGBAP_4444 src)
{
	r = (src.r<<4) | src.r;
	g = (src.g<<4) | src.g;
	b = (src.b<<4) | src.b;
	a = (src.a<<4) | src.a;
	return *this;
}

/*
inline PixelLumAP& PixelLumAP::operator = (const PixelRGB_24 other)
{
	v = (other.r + other.g + other.b)/3;
	a = 255;
	return *this;
}

inline PixelLumAP& PixelLumAP::operator = (const PixelRGB_32 other)
{
	v = (other.r + other.g + other.b)/3;
	a = 255;
	return *this;
}

inline PixelLumAP& PixelLumAP::operator = (const PixelRGBAP_32 other)
{
	v = (other.r + other.g + other.b)/3;
	a = other.a;
	return *this;
}
*/
#endif

class BitmapData
{
public:

	CTOR BitmapData()
	{
		Scan0 = NULL;
		Reserved = NULL;
	}

	int Width;
	int Height;
	int Stride;
	PixelFormat_t PFormat;
	uint8* Scan0;
	void* Reserved;
};

class _Graphics;
class GraphicsO;

enum ImageLockMode
{
	ImageLockModeRead = 1,
	ImageLockModeWrite = 2,
};

typedef D3D10_MAPPED_TEXTURE2D MAPPED_TEXTURE2D;
/*
struct MAPPED_TEXTURE2D
{
	void* pData;
	UINT RowPitch;
};
*/

class GfxExt D3D10Texture2D
{
public:
	CTOR D3D10Texture2D();

	CTOR D3D10Texture2D(ID3D10Texture2D* p) : m_d3d10_texture(p)
	{
		if (m_d3d10_texture) m_d3d10_texture->AddRef();
	}

	~D3D10Texture2D()
	{
		if (m_d3d10_texture) m_d3d10_texture->Release();
	}

//	CTOR D3D10Texture2D(ID3D10Device* device, int width, int height, DXGI_FORMAT pixelFormat);
	CTOR D3D10Texture2D(ID3D10Device* device, int width, int height, DXGI_FORMAT pixelFormat, void* initialSysMem, int sysMemPitch);
#ifndef __LERSTAD__
	CTOR D3D10Texture2D(ID3D10Device* device, int width, int height, DXGI_FORMAT pixelFormat, D3D10_USAGE usage = D3D10_USAGE_DEFAULT);
#endif
//	void Create(ID3D10Device* device, int width, int height, DXGI_FORMAT pixelFormat);
	void Create(ID3D10Device* pD3DDevice, int width, int height, DXGI_FORMAT pixelFormat, void* initialSysMem, int sysMemPitch);
#ifndef __LERSTAD__
	void Create(ID3D10Device* pD3DDevice, int width, int height, DXGI_FORMAT pixelFormat, D3D10_USAGE usage = D3D10_USAGE_DEFAULT);
#endif

#if 0
#ifndef __LERSTAD__	// Because of Map
	int Map(D3D10_MAP mapType, MAPPED_TEXTURE2D* pMapped)
	{
		return m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), mapType, 0, (D3D10_MAPPED_TEXTURE2D*)pMapped);

//	D3DLOCKED_RECT locked_rect;
//	m_bitmap->m_d3dTexture->LockRect(0, &locked_rect, NULL/*&rect*/, 0);
	}

	int Map(D3D10_MAP mapType, UINT mapFlags, MAPPED_TEXTURE2D* pMapped)
	{
		return m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), mapType, mapFlags, (D3D10_MAPPED_TEXTURE2D*)pMapped);

//	D3DLOCKED_RECT locked_rect;
//	m_bitmap->m_d3dTexture->LockRect(0, &locked_rect, NULL/*&rect*/, 0);
	}
#endif

	void Unmap()
	{
		m_d3d10_texture->Unmap(D3D10CalcSubresource(0,0,0));
	//	m_bitmap->m_d3dTexture->UnlockRect(0);
	}
#endif

	ID3D10Texture2D* m_d3d10_texture;
};

class GfxExt Image : public Object
{
public:

	float get_HorizontalResolution() const
	{
		return m_xdpi;
	}

	float get_VerticalResolution() const
	{
		return m_ydpi;
	}

	float m_xdpi;
	float m_ydpi;
};

class GfxExt Bitmap : public Image
{
public:

	CTOR Bitmap(int width, int height, PixelFormat_t pixelFormat);
	CTOR Bitmap(int width, int height, int rowBytes, PixelFormat_t pixelFormat, void* data);
	//Bitmap(const BitmapData & bitmapdata);

//#ifdef WIN32

	CTOR Bitmap(ID3D10Device* device, const D3D10Texture2D& texture2D);
	CTOR Bitmap(HBITMAP hbm, HPALETTE hpal = NULL);
	CTOR Bitmap(const BITMAPINFO* gdiBitmapInfo, void* gdiBitmapData);
	CTOR Bitmap(StringIn filename);
	CTOR Bitmap(HINSTANCE hInstance, StringIn name);

	// TODO remove??
	CTOR Bitmap(const _DDSURFACEDESC* surfDesc);

//#elif AMIGA

	CTOR Bitmap(struct BitMap* p96BitMap);

//#elif __APPLE__

	CTOR Bitmap(PixMapHandle pixMap);

//#endif

	~Bitmap();

	void Set(ID3D10Device* device, const D3D10Texture2D& texture2D);

//	virtual int LockBits(const RectI* rect, uint nFlags, BitmapData* lockedBitmapData);
//	virtual void UnlockBits(BitmapData* lockedBitmapData);

	bool Equals(const Bitmap& other) const;

	int get_Width() const
	{
		return m_width;
	}

	int get_Height() const
	{
		return m_height;
	}

	inline int GetWidth() const
	{
		return m_width;
	}

	inline int GetHeight() const
	{
		return m_height;
	}

	inline PixelFormat_t GetPixelFormat() const
	{
		return m_pixelFormat;
	}

	inline int GetRowBytes() const
	{
		return m_rowBytes;
	}

	virtual void SetPixelFormat(PixelFormat_t pixelFormat);

	/*
	inline uint GetBitCount() const
	{
		return m_bitcount;
	}
	*/

	void SetResolution(float xdpi, float ydpi);

	ARGB GetPixelARGB(unsigned int x, unsigned int y);
	ARGB GetPixelARGB(float x, float y);	// Linear interpolation

	Bitmap* Clone();
	Bitmap* Clone(PixelFormat_t pixelFormat);
	Bitmap* Clone(const gm::RectI& rect);
	Bitmap* Clone(const gm::RectI& rect, uint32 pixelFormat);
	int CopyBitmapData(int dstX, int dstY, Bitmap* srcBitmap, int srcX, int srcY, int width, int height);

	static Bitmap* CreateSharedRenderTarget(unsigned int width, unsigned int height, bool alpha = false);
	static Bitmap* CreateSharedDepthStencil(unsigned int width, unsigned int height);
	static Bitmap* CreateSharedDepth(unsigned int width, unsigned int height, uint depthbits = 0);

	static Bitmap* FromFile(StringIn filename);
	static Bitmap* FromHICON(HICON hIcon);
	static Bitmap* FromHBITMAP(HBITMAP hBitmap, HPALETTE hPalette = NULL);

//	HBITMAP ToHBITMAP();
	//HCURSOR ToHCURSOR(int hotspotX, int hotspotY);

	virtual bool HasData()
	{
		return m_bitmapData != NULL;
	}

	void* GetPointer()
	{
		return m_bitmapData;
	}

	class Data : public MAPPED_TEXTURE2D
	{
	public:
		CTOR Data(Bitmap* pBitmap) : m_pBitmap(pBitmap)
		{
			this->pData = NULL;
			this->RowPitch = 0;
		}

		CTOR Data(Bitmap* pBitmap, const MAPPED_TEXTURE2D& m) : m_pBitmap(pBitmap)
		{
			this->pData = m.pData;
			this->RowPitch = m.RowPitch;
		}

		/*
		CTOR Data(const Data& other) : m_pBitmap(other.m_pBitmap)
		{
			this->pData = other.pData;
			this->RowPitch = other.RowPitch;
		}
		*/
#ifndef __LERSTAD__
		CTOR Data(Data&& other) : m_pBitmap(other.m_pBitmap)
		{
			this->pData = other.pData;
			this->RowPitch = other.RowPitch;

			other.m_pBitmap = NULL;
		}
#endif

		Data& operator = (const Data& other);
#ifndef __LERSTAD__
		Data& operator = (Data&& other);
#endif

		~Data()
		{
			Unmap();
		}

		void Unmap()
		{
			ASSERT(0);
#if 0
			if (m_pBitmap)
			{
			//	--m_pBitmap->m_mapCount;
				m_pBitmap->Unmap();
				m_pBitmap = NULL;
			}
			this->pData = NULL;
			this->RowPitch = 0;
#endif
		}

		Bitmap* m_pBitmap;

	private:

		CTOR Data();
	};

#if 0
#ifndef __LERSTAD__
	Data MapRead()
	{
		MAPPED_TEXTURE2D mapped;
		ThrowHr hr = m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), D3D10_MAP_READ, 0, &mapped);
		return Data(this, mapped);
//	D3DLOCKED_RECT locked_rect;
//	m_bitmap->m_d3dTexture->LockRect(0, &locked_rect, NULL/*&rect*/, 0);
	}

	Data MapWrite()
	{
		MAPPED_TEXTURE2D mapped;
		ThrowHr hr = m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), D3D10_MAP_WRITE, 0, &mapped);
		return Data(this, mapped);
	}

	Data MapReadWrite()
	{
		MAPPED_TEXTURE2D mapped;
		ThrowHr hr = m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), D3D10_MAP_READ_WRITE, 0, &mapped);
		return Data(this, mapped);
	}

	Data MapWriteDiscard()
	{
		MAPPED_TEXTURE2D mapped;
		ThrowHr hr = m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), D3D10_MAP_WRITE_DISCARD, 0, &mapped);
		return Data(this, mapped);
	}
#endif

#ifndef __LERSTAD__	// Because of Map
	int Map(D3D10_MAP mapType, MAPPED_TEXTURE2D* pMapped)
	{
		return m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), mapType, 0, (D3D10_MAPPED_TEXTURE2D*)pMapped);

//	D3DLOCKED_RECT locked_rect;
//	m_bitmap->m_d3dTexture->LockRect(0, &locked_rect, NULL/*&rect*/, 0);
	}

	int Map(D3D10_MAP mapType, UINT mapFlags, MAPPED_TEXTURE2D* pMapped)
	{
		return m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), mapType, mapFlags, (D3D10_MAPPED_TEXTURE2D*)pMapped);

//	D3DLOCKED_RECT locked_rect;
//	m_bitmap->m_d3dTexture->LockRect(0, &locked_rect, NULL/*&rect*/, 0);
	}
#endif

	void Unmap()
	{
		m_d3d10_texture->Unmap(D3D10CalcSubresource(0,0,0));
	//	m_bitmap->m_d3dTexture->UnlockRect(0);
	}
#endif

	ID3D10ShaderResourceView* GetD3D10ShaderResourceView();
	ID3D10RenderTargetView* GetD3D10RenderTargetView();

	ID3D11ShaderResourceView* GetD3D11ShaderResourceView();
	ID3D11RenderTargetView* GetD3D11RenderTargetView();

	ID2D1Bitmap* GetD2D1Bitmap(RenderTarget* rt);

public:

	tagRGBQUAD* m_colors;

//	kdtree<RGBTriple, uint8/*pen*/> m_palette;

#ifdef _WIN32

	IDirect3DTexture9* m_d3d9_texture;
	HANDLE m_shared;

	GraphicsI* m_device10;

	ID3D10Texture2D* m_d3d10_texture;
	ID3D10ShaderResourceView* m_d3d10_shaderResourceView;
	ID3D10RenderTargetView* m_d3d10_renderTargetView;

	ID3D11Texture2D* m_d3d11_texture;
	ID3D11ShaderResourceView* m_d3d11_shaderResourceView;
	ID3D11RenderTargetView* m_d3d11_renderTargetView;

	ComPtr<ID2D1Bitmap> m_d2d1bitmap;
	ComPtr<ID2D1RenderTarget> m_d2d1renderTarget;

#endif

	uint m_gl_fbo;

	ubyte* m_bitmapData;

protected:

	void CreateD3D10ShaderResourceView(ID3D10Device* pD3DDevice);
	void CreateD3D10RenderTargetView(ID3D10Device* pD3DDevice);
	void CopyFromMemory(const void* data, int rowbytes);

	bool m_bFreeData;
	bool m_locked;

	HICON m_hIcon;
	HBITMAP m_hBitmap;
	HPALETTE m_hPalette;

	PixelFormat_t m_pixelFormat;

	int m_width;
	int m_height;

	int m_rowBytes;
};

class GfxExt Metafile : public Image
{
public:
};

}	// Graphics
}	// System
