#ifndef Imaging_DecoderInterface_h
#define Imaging_DecoderInterface_h

namespace System
{
namespace Imaging
{

//#ifndef __dxgiformat_h__
//#define __dxgiformat_h__

//#define PixelFormat_DEFINED 1

enum PixelFormat
{
    PixelFormat_UNKNOWN	                    = 0,
    PixelFormat_R32G32B32A32_TYPELESS       = 1,
    PixelFormat_R32G32B32A32_FLOAT          = 2,
    PixelFormat_R32G32B32A32_UINT           = 3,
    PixelFormat_R32G32B32A32_SINT           = 4,
    PixelFormat_R32G32B32_TYPELESS          = 5,
    PixelFormat_R32G32B32_FLOAT             = 6,
    PixelFormat_R32G32B32_UINT              = 7,
    PixelFormat_R32G32B32_SINT              = 8,
    PixelFormat_R16G16B16A16_TYPELESS       = 9,
    PixelFormat_R16G16B16A16_FLOAT          = 10,
    PixelFormat_R16G16B16A16_UNORM          = 11,
    PixelFormat_R16G16B16A16_UINT           = 12,
    PixelFormat_R16G16B16A16_SNORM          = 13,
    PixelFormat_R16G16B16A16_SINT           = 14,
    PixelFormat_R32G32_TYPELESS             = 15,
    PixelFormat_R32G32_FLOAT                = 16,
    PixelFormat_R32G32_UINT                 = 17,
    PixelFormat_R32G32_SINT                 = 18,
    PixelFormat_R32G8X24_TYPELESS           = 19,
    PixelFormat_D32_FLOAT_S8X24_UINT        = 20,
    PixelFormat_R32_FLOAT_X8X24_TYPELESS    = 21,
    PixelFormat_X32_TYPELESS_G8X24_UINT     = 22,
    PixelFormat_R10G10B10A2_TYPELESS        = 23,
    PixelFormat_R10G10B10A2_UNORM           = 24,
    PixelFormat_R10G10B10A2_UINT            = 25,
    PixelFormat_R11G11B10_FLOAT             = 26,
    PixelFormat_R8G8B8A8_TYPELESS           = 27,
    PixelFormat_R8G8B8A8_UNORM              = 28,
    PixelFormat_R8G8B8A8_UNORM_SRGB         = 29,
    PixelFormat_R8G8B8A8_UINT               = 30,
    PixelFormat_R8G8B8A8_SNORM              = 31,
    PixelFormat_R8G8B8A8_SINT               = 32,
    PixelFormat_R16G16_TYPELESS             = 33,
    PixelFormat_R16G16_FLOAT                = 34,
    PixelFormat_R16G16_UNORM                = 35,
    PixelFormat_R16G16_UINT                 = 36,
    PixelFormat_R16G16_SNORM                = 37,
    PixelFormat_R16G16_SINT                 = 38,
    PixelFormat_R32_TYPELESS                = 39,
    PixelFormat_D32_FLOAT                   = 40,
    PixelFormat_R32_FLOAT                   = 41,
    PixelFormat_R32_UINT                    = 42,
    PixelFormat_R32_SINT                    = 43,
    PixelFormat_R24G8_TYPELESS              = 44,
    PixelFormat_D24_UNORM_S8_UINT           = 45,
    PixelFormat_R24_UNORM_X8_TYPELESS       = 46,
    PixelFormat_X24_TYPELESS_G8_UINT        = 47,
    PixelFormat_R8G8_TYPELESS               = 48,
    PixelFormat_R8G8_UNORM                  = 49,
    PixelFormat_R8G8_UINT                   = 50,
    PixelFormat_R8G8_SNORM                  = 51,
    PixelFormat_R8G8_SINT                   = 52,
    PixelFormat_R16_TYPELESS                = 53,
    PixelFormat_R16_FLOAT                   = 54,
    PixelFormat_D16_UNORM                   = 55,
    PixelFormat_R16_UNORM                   = 56,
    PixelFormat_R16_UINT                    = 57,
    PixelFormat_R16_SNORM                   = 58,
    PixelFormat_R16_SINT                    = 59,
    PixelFormat_R8_TYPELESS                 = 60,
    PixelFormat_R8_UNORM                    = 61,
    PixelFormat_R8_UINT                     = 62,
    PixelFormat_R8_SNORM                    = 63,
    PixelFormat_R8_SINT                     = 64,
    PixelFormat_A8_UNORM                    = 65,
    PixelFormat_R1_UNORM                    = 66,
    PixelFormat_R9G9B9E5_SHAREDEXP          = 67,
    PixelFormat_R8G8_B8G8_UNORM             = 68,
    PixelFormat_G8R8_G8B8_UNORM             = 69,
    PixelFormat_BC1_TYPELESS                = 70,
    PixelFormat_BC1_UNORM                   = 71,
    PixelFormat_BC1_UNORM_SRGB              = 72,
    PixelFormat_BC2_TYPELESS                = 73,
    PixelFormat_BC2_UNORM                   = 74,
    PixelFormat_BC2_UNORM_SRGB              = 75,
    PixelFormat_BC3_TYPELESS                = 76,
    PixelFormat_BC3_UNORM                   = 77,
    PixelFormat_BC3_UNORM_SRGB              = 78,
    PixelFormat_BC4_TYPELESS                = 79,
    PixelFormat_BC4_UNORM                   = 80,
    PixelFormat_BC4_SNORM                   = 81,
    PixelFormat_BC5_TYPELESS                = 82,
    PixelFormat_BC5_UNORM                   = 83,
    PixelFormat_BC5_SNORM                   = 84,
    PixelFormat_B5G6R5_UNORM                = 85,
    PixelFormat_B5G5R5A1_UNORM              = 86,
    PixelFormat_B8G8R8A8_UNORM              = 87,
    PixelFormat_B8G8R8X8_UNORM              = 88,
    PixelFormat_R10G10B10_XR_BIAS_A2_UNORM  = 89,
    PixelFormat_B8G8R8A8_TYPELESS           = 90,
    PixelFormat_B8G8R8A8_UNORM_SRGB         = 91,
    PixelFormat_B8G8R8X8_TYPELESS           = 92,
    PixelFormat_B8G8R8X8_UNORM_SRGB         = 93,
    PixelFormat_BC6H_TYPELESS               = 94,
    PixelFormat_BC6H_UF16                   = 95,
    PixelFormat_BC6H_SF16                   = 96,
    PixelFormat_BC7_TYPELESS                = 97,
    PixelFormat_BC7_UNORM                   = 98,
    PixelFormat_BC7_UNORM_SRGB              = 99,
    PixelFormat_FORCE_UINT                  = 0xffffffff
};

//#endif // __dxgiformat_h__

struct BitmapFormat
{
	int width;
	int height;
	PixelFormat pixelFormat;
};

interface IBitmapFormatDecoder
{
	virtual int ReadHeader(IO::Stream* stream, BitmapFormat* bitmapFormat) = 0;
	virtual int ReadBitmap(IO::Stream* stream, void* data, int rowbytes) = 0;
};

}	// Imaging
}	// System

#endif // Imaging_DecoderInterface_h
