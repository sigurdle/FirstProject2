#include "stdafx.h"

#include "LXUI2.h"
#include "Screen.h"
#include "UIFrameImpl2.h"
#include "WindowBase.h"

//using namespace System::MSWindows;

#if 1

#if WIN32
#include "../include/windows_header.h"
#endif

#if WIN32
//#include <ddraw.h>
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "Dxguid.lib")
#endif

//#define INITGUID

namespace System
{

#define DECLSPEC_SELECTANY  __declspec(selectany)

extern "C" const DECLSPEC_SELECTANY FAR GUID IID_IDirectDraw2 = {                  0xB3A6F3E0,0x2B43,0x11CF,0xA2,0xDE,0x00,0xAA,0x00,0xB9,0x33,0x56 };

#define DECLSPEC_NOVTABLE __declspec(novtable)

#define DECLARE_INTERFACE(iface)    struct DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_(iface, baseiface)    struct DECLSPEC_NOVTABLE iface : public baseiface

struct IUnknown
{
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
	virtual ULONG __stdcall QueryInterface(System::GUID& guid, void**p) = 0;
};

#define THIS_
#define THIS
#define PURE = 0
typedef const GUID& REFIID;

typedef void * LPDIRECTDRAWCLIPPER;
typedef void * LPPALETTEENTRY;
typedef void * LPDIRECTDRAWPALETTE;

/*
 * DDCOLORKEY
 */
typedef struct _DDCOLORKEY
{
    DWORD       dwColorSpaceLowValue;   // low boundary of color space that is to
                                        // be treated as Color Key, inclusive
    DWORD       dwColorSpaceHighValue;  // high boundary of color space that is
                                        // to be treated as Color Key, inclusive
} DDCOLORKEY;

typedef DDCOLORKEY FAR* LPDDCOLORKEY;

/*
 * DDSCAPS
 */
typedef struct _DDSCAPS
{
    DWORD       dwCaps;         // capabilities of surface wanted
} DDSCAPS;

typedef DDSCAPS FAR* LPDDSCAPS;

/*
 * DDSCAPS2
 */
typedef struct _DDSCAPS2
{
    DWORD       dwCaps;         // capabilities of surface wanted
    DWORD       dwCaps2;
    DWORD       dwCaps3;
    union
    {
        DWORD       dwCaps4;
        DWORD       dwVolumeDepth;
    }; //DUMMYUNIONNAMEN(1);
} DDSCAPS2;

typedef DDSCAPS2 FAR* LPDDSCAPS2;

/*============================================================================
 *
 * Direct Draw Capability Flags
 *
 * These flags are used to describe the capabilities of a given Surface.
 * All flags are bit flags.
 *
 *==========================================================================*/

/****************************************************************************
 *
 * DIRECTDRAWSURFACE CAPABILITY FLAGS
 *
 ****************************************************************************/

/*
 * This bit is reserved. It should not be specified.
 */
#define DDSCAPS_RESERVED1                       0x00000001l

/*
 * Indicates that this surface contains alpha-only information.
 * (To determine if a surface is RGBA/YUVA, the pixel format must be
 * interrogated.)
 */
#define DDSCAPS_ALPHA                           0x00000002l

/*
 * Indicates that this surface is a backbuffer.  It is generally
 * set by CreateSurface when the DDSCAPS_FLIP capability bit is set.
 * It indicates that this surface is THE back buffer of a surface
 * flipping structure.  DirectDraw supports N surfaces in a
 * surface flipping structure.  Only the surface that immediately
 * precedeces the DDSCAPS_FRONTBUFFER has this capability bit set.
 * The other surfaces are identified as back buffers by the presence
 * of the DDSCAPS_FLIP capability, their attachment order, and the
 * absence of the DDSCAPS_FRONTBUFFER and DDSCAPS_BACKBUFFER
 * capabilities.  The bit is sent to CreateSurface when a standalone
 * back buffer is being created.  This surface could be attached to
 * a front buffer and/or back buffers to form a flipping surface
 * structure after the CreateSurface call.  See AddAttachments for
 * a detailed description of the behaviors in this case.
 */
#define DDSCAPS_BACKBUFFER                      0x00000004l

/*
 * Indicates a complex surface structure is being described.  A
 * complex surface structure results in the creation of more than
 * one surface.  The additional surfaces are attached to the root
 * surface.  The complex structure can only be destroyed by
 * destroying the root.
 */
#define DDSCAPS_COMPLEX                         0x00000008l

/*
 * Indicates that this surface is a part of a surface flipping structure.
 * When it is passed to CreateSurface the DDSCAPS_FRONTBUFFER and
 * DDSCAP_BACKBUFFER bits are not set.  They are set by CreateSurface
 * on the resulting creations.  The dwBackBufferCount field in the
 * DDSURFACEDESC structure must be set to at least 1 in order for
 * the CreateSurface call to succeed.  The DDSCAPS_COMPLEX capability
 * must always be set with creating multiple surfaces through CreateSurface.
 */
#define DDSCAPS_FLIP                            0x00000010l

/*
 * Indicates that this surface is THE front buffer of a surface flipping
 * structure.  It is generally set by CreateSurface when the DDSCAPS_FLIP
 * capability bit is set.
 * If this capability is sent to CreateSurface then a standalonw front buffer
 * is created.  This surface will not have the DDSCAPS_FLIP capability.
 * It can be attached to other back buffers to form a flipping structure.
 * See AddAttachments for a detailed description of the behaviors in this
 * case.
 */
#define DDSCAPS_FRONTBUFFER                     0x00000020l

/*
 * Indicates that this surface is any offscreen surface that is not an overlay,
 * texture, zbuffer, front buffer, back buffer, or alpha surface.  It is used
 * to identify plain vanilla surfaces.
 */
#define DDSCAPS_OFFSCREENPLAIN                  0x00000040l

/*
 * Indicates that this surface is an overlay.  It may or may not be directly visible
 * depending on whether or not it is currently being overlayed onto the primary
 * surface.  DDSCAPS_VISIBLE can be used to determine whether or not it is being
 * overlayed at the moment.
 */
#define DDSCAPS_OVERLAY                         0x00000080l

/*
 * Indicates that unique DirectDrawPalette objects can be created and
 * attached to this surface.
 */
#define DDSCAPS_PALETTE                         0x00000100l

/*
 * Indicates that this surface is the primary surface.  The primary
 * surface represents what the user is seeing at the moment.
 */
#define DDSCAPS_PRIMARYSURFACE                  0x00000200l

/*
 * This flag used to be DDSCAPS_PRIMARYSURFACELEFT, which is now
 * obsolete.
 */
#define DDSCAPS_RESERVED3               0x00000400l
#define DDSCAPS_PRIMARYSURFACELEFT              0x00000000l

/*
 * Indicates that this surface memory was allocated in system memory
 */
#define DDSCAPS_SYSTEMMEMORY                    0x00000800l

/*
 * Indicates that this surface can be used as a 3D texture.  It does not
 * indicate whether or not the surface is being used for that purpose.
 */
#define DDSCAPS_TEXTURE                         0x00001000l

/*
 * Indicates that a surface may be a destination for 3D rendering.  This
 * bit must be set in order to query for a Direct3D Device Interface
 * from this surface.
 */
#define DDSCAPS_3DDEVICE                        0x00002000l

/*
 * Indicates that this surface exists in video memory.
 */
#define DDSCAPS_VIDEOMEMORY                     0x00004000l

/*
 * Indicates that changes made to this surface are immediately visible.
 * It is always set for the primary surface and is set for overlays while
 * they are being overlayed and texture maps while they are being textured.
 */
#define DDSCAPS_VISIBLE                         0x00008000l

/*
 * Indicates that only writes are permitted to the surface.  Read accesses
 * from the surface may or may not generate a protection fault, but the
 * results of a read from this surface will not be meaningful.  READ ONLY.
 */
#define DDSCAPS_WRITEONLY                       0x00010000l

/*
 * Indicates that this surface is a z buffer. A z buffer does not contain
 * displayable information.  Instead it contains bit depth information that is
 * used to determine which pixels are visible and which are obscured.
 */
#define DDSCAPS_ZBUFFER                         0x00020000l

/*
 * Indicates surface will have a DC associated long term
 */
#define DDSCAPS_OWNDC                           0x00040000l

/*
 * Indicates surface should be able to receive live video
 */
#define DDSCAPS_LIVEVIDEO                       0x00080000l

/*
 * Indicates surface should be able to have a stream decompressed
 * to it by the hardware.
 */
#define DDSCAPS_HWCODEC                         0x00100000l

/*
 * Surface is a ModeX surface.
 *
 */
#define DDSCAPS_MODEX                           0x00200000l

/*
 * Indicates surface is one level of a mip-map. This surface will
 * be attached to other DDSCAPS_MIPMAP surfaces to form the mip-map.
 * This can be done explicitly, by creating a number of surfaces and
 * attaching them with AddAttachedSurface or by implicitly by CreateSurface.
 * If this bit is set then DDSCAPS_TEXTURE must also be set.
 */
#define DDSCAPS_MIPMAP                          0x00400000l

/*
 * This bit is reserved. It should not be specified.
 */
#define DDSCAPS_RESERVED2                       0x00800000l


/*
 * Indicates that memory for the surface is not allocated until the surface
 * is loaded (via the Direct3D texture Load() function).
 */
#define DDSCAPS_ALLOCONLOAD                     0x04000000l

/*
 * Indicates that the surface will recieve data from a video port.
 */
#define DDSCAPS_VIDEOPORT                       0x08000000l

/*
 * Indicates that a video memory surface is resident in true, local video
 * memory rather than non-local video memory. If this flag is specified then
 * so must DDSCAPS_VIDEOMEMORY. This flag is mutually exclusive with
 * DDSCAPS_NONLOCALVIDMEM.
 */
#define DDSCAPS_LOCALVIDMEM                     0x10000000l

/*
 * Indicates that a video memory surface is resident in non-local video
 * memory rather than true, local video memory. If this flag is specified
 * then so must DDSCAPS_VIDEOMEMORY. This flag is mutually exclusive with
 * DDSCAPS_LOCALVIDMEM.
 */
#define DDSCAPS_NONLOCALVIDMEM                  0x20000000l

/*
 * Indicates that this surface is a standard VGA mode surface, and not a
 * ModeX surface. (This flag will never be set in combination with the
 * DDSCAPS_MODEX flag).
 */
#define DDSCAPS_STANDARDVGAMODE                 0x40000000l

/*
 * Indicates that this surface will be an optimized surface. This flag is
 * currently only valid in conjunction with the DDSCAPS_TEXTURE flag. The surface
 * will be created without any underlying video memory until loaded.
 */
#define DDSCAPS_OPTIMIZED                       0x80000000l



/*
 * This bit is reserved
 */
#define DDSCAPS2_RESERVED4                      0x00000002L
#define DDSCAPS2_HARDWAREDEINTERLACE            0x00000000L

/*
 * Indicates to the driver that this surface will be locked very frequently
 * (for procedural textures, dynamic lightmaps, etc). Surfaces with this cap
 * set must also have DDSCAPS_TEXTURE. This cap cannot be used with
 * DDSCAPS2_HINTSTATIC and DDSCAPS2_OPAQUE.
 */
#define DDSCAPS2_HINTDYNAMIC                    0x00000004L

/*
 * Indicates to the driver that this surface can be re-ordered/retiled on
 * load. This operation will not change the size of the texture. It is
 * relatively fast and symmetrical, since the application may lock these
 * bits (although it will take a performance hit when doing so). Surfaces
 * with this cap set must also have DDSCAPS_TEXTURE. This cap cannot be
 * used with DDSCAPS2_HINTDYNAMIC and DDSCAPS2_OPAQUE.
 */
#define DDSCAPS2_HINTSTATIC                     0x00000008L

/*
 * Indicates that the client would like this texture surface to be managed by the
 * DirectDraw/Direct3D runtime. Surfaces with this cap set must also have
 * DDSCAPS_TEXTURE set.
 */
#define DDSCAPS2_TEXTUREMANAGE                  0x00000010L

/*
 * These bits are reserved for internal use */
#define DDSCAPS2_RESERVED1                      0x00000020L
#define DDSCAPS2_RESERVED2                      0x00000040L

/*
 * Indicates to the driver that this surface will never be locked again.
 * The driver is free to optimize this surface via retiling and actual compression.
 * All calls to Lock() or Blts from this surface will fail. Surfaces with this
 * cap set must also have DDSCAPS_TEXTURE. This cap cannot be used with
 * DDSCAPS2_HINTDYNAMIC and DDSCAPS2_HINTSTATIC.
 */
#define DDSCAPS2_OPAQUE                         0x00000080L

/*
 * Applications should set this bit at CreateSurface time to indicate that they
 * intend to use antialiasing. Only valid if DDSCAPS_3DDEVICE is also set.
 */
#define DDSCAPS2_HINTANTIALIASING               0x00000100L


/*
 * This flag is used at CreateSurface time to indicate that this set of
 * surfaces is a cubic environment map
 */
#define DDSCAPS2_CUBEMAP                        0x00000200L

/*
 * These flags preform two functions:
 * - At CreateSurface time, they define which of the six cube faces are
 *   required by the application.
 * - After creation, each face in the cubemap will have exactly one of these
 *   bits set.
 */
#define DDSCAPS2_CUBEMAP_POSITIVEX              0x00000400L
#define DDSCAPS2_CUBEMAP_NEGATIVEX              0x00000800L
#define DDSCAPS2_CUBEMAP_POSITIVEY              0x00001000L
#define DDSCAPS2_CUBEMAP_NEGATIVEY              0x00002000L
#define DDSCAPS2_CUBEMAP_POSITIVEZ              0x00004000L
#define DDSCAPS2_CUBEMAP_NEGATIVEZ              0x00008000L

/*
 * This macro may be used to specify all faces of a cube map at CreateSurface time
 */
#define DDSCAPS2_CUBEMAP_ALLFACES ( DDSCAPS2_CUBEMAP_POSITIVEX |\
                                    DDSCAPS2_CUBEMAP_NEGATIVEX |\
                                    DDSCAPS2_CUBEMAP_POSITIVEY |\
                                    DDSCAPS2_CUBEMAP_NEGATIVEY |\
                                    DDSCAPS2_CUBEMAP_POSITIVEZ |\
                                    DDSCAPS2_CUBEMAP_NEGATIVEZ )


/*
 * This flag is an additional flag which is present on mipmap sublevels from DX7 onwards
 * It enables easier use of GetAttachedSurface rather than EnumAttachedSurfaces for surface
 * constructs such as Cube Maps, wherein there are more than one mipmap surface attached
 * to the root surface.
 * This caps bit is ignored by CreateSurface
 */
#define DDSCAPS2_MIPMAPSUBLEVEL                 0x00010000L

/* This flag indicates that the texture should be managed by D3D only */
#define DDSCAPS2_D3DTEXTUREMANAGE               0x00020000L

/* This flag indicates that the managed surface can be safely lost */
#define DDSCAPS2_DONOTPERSIST                   0x00040000L

/* indicates that this surface is part of a stereo flipping chain */
#define DDSCAPS2_STEREOSURFACELEFT              0x00080000L


/*
 * Indicates that the surface is a volume.
 * Can be combined with DDSCAPS_MIPMAP to indicate a multi-level volume
 */
#define DDSCAPS2_VOLUME                         0x00200000L

/*
 * Indicates that the surface may be locked multiple times by the application.
 * This cap cannot be used with DDSCAPS2_OPAQUE.
 */
#define DDSCAPS2_NOTUSERLOCKABLE                0x00400000L

/*
 * Indicates that the vertex buffer data can be used to render points and
 * point sprites.
 */
#define DDSCAPS2_POINTS                         0x00800000L

/*
 * Indicates that the vertex buffer data can be used to render rt pactches.
 */
#define DDSCAPS2_RTPATCHES                      0x01000000L

/*
 * Indicates that the vertex buffer data can be used to render n patches.
 */
#define DDSCAPS2_NPATCHES                       0x02000000L

/*
 * This bit is reserved for internal use 
 */
#define DDSCAPS2_RESERVED3                      0x04000000L


/*
 * Indicates that the contents of the backbuffer do not have to be preserved
 * the contents of the backbuffer after they are presented.
 */
#define DDSCAPS2_DISCARDBACKBUFFER              0x10000000L

/*
 * Indicates that all surfaces in this creation chain should be given an alpha channel.
 * This flag will be set on primary surface chains that may have no explicit pixel format
 * (and thus take on the format of the current display mode).
 * The driver should infer that all these surfaces have a format having an alpha channel.
 * (e.g. assume D3DFMT_A8R8G8B8 if the display mode is x888.)
 */
#define DDSCAPS2_ENABLEALPHACHANNEL             0x20000000L

/*
 * Indicates that all surfaces in this creation chain is extended primary surface format.
 * This flag will be set on extended primary surface chains that always have explicit pixel
 * format and the pixel format is typically GDI (Graphics Device Interface) couldn't handle,
 * thus only used with fullscreen application. (e.g. D3DFMT_A2R10G10B10 format)
 */
#define DDSCAPS2_EXTENDEDFORMATPRIMARY          0x40000000L

/*
 * Indicates that all surfaces in this creation chain is additional primary surface.
 * This flag will be set on primary surface chains which must present on the adapter
 * id provided on dwCaps4. Typically this will be used to create secondary primary surface
 * on DualView display adapter.
 */
#define DDSCAPS2_ADDITIONALPRIMARY              0x80000000L

/*
 * This is a mask that indicates the set of bits that may be set
 * at createsurface time to indicate number of samples per pixel
 * when multisampling
 */
#define DDSCAPS3_MULTISAMPLE_MASK               0x0000001FL

/*
 * This is a mask that indicates the set of bits that may be set
 * at createsurface time to indicate the quality level of rendering
 * for the current number of samples per pixel
 */
#define DDSCAPS3_MULTISAMPLE_QUALITY_MASK       0x000000E0L
#define DDSCAPS3_MULTISAMPLE_QUALITY_SHIFT      5

/*
 * This bit is reserved for internal use 
 */
#define DDSCAPS3_RESERVED1                      0x00000100L

/*
 * This bit is reserved for internal use 
 */
#define DDSCAPS3_RESERVED2                      0x00000200L

/*
 * This indicates whether this surface has light-weight miplevels
 */
#define DDSCAPS3_LIGHTWEIGHTMIPMAP              0x00000400L

/*
 * This indicates that the mipsublevels for this surface are auto-generated
 */
#define DDSCAPS3_AUTOGENMIPMAP                  0x00000800L

/*
 * This indicates that the mipsublevels for this surface are auto-generated
 */
#define DDSCAPS3_DMAP                           0x00001000L

/*
 * DDPIXELFORMAT
 */
typedef struct _DDPIXELFORMAT
{
    DWORD       dwSize;                 // size of structure
    DWORD       dwFlags;                // pixel format flags
    DWORD       dwFourCC;               // (FOURCC code)
    union
    {
        DWORD   dwRGBBitCount;          // how many bits per pixel
        DWORD   dwYUVBitCount;          // how many bits per pixel
        DWORD   dwZBufferBitDepth;      // how many total bits/pixel in z buffer (including any stencil bits)
        DWORD   dwAlphaBitDepth;        // how many bits for alpha channels
        DWORD   dwLuminanceBitCount;    // how many bits per pixel
        DWORD   dwBumpBitCount;         // how many bits per "buxel", total
        DWORD   dwPrivateFormatBitCount;// Bits per pixel of private driver formats. Only valid in texture
                                        // format list and if DDPF_D3DFORMAT is set
    };// DUMMYUNIONNAMEN(1);
    union
    {
        DWORD   dwRBitMask;             // mask for red bit
        DWORD   dwYBitMask;             // mask for Y bits
        DWORD   dwStencilBitDepth;      // how many stencil bits (note: dwZBufferBitDepth-dwStencilBitDepth is total Z-only bits)
        DWORD   dwLuminanceBitMask;     // mask for luminance bits
        DWORD   dwBumpDuBitMask;        // mask for bump map U delta bits
        DWORD   dwOperations;           // DDPF_D3DFORMAT Operations
    };// DUMMYUNIONNAMEN(2);
    union
    {
        DWORD   dwGBitMask;             // mask for green bits
        DWORD   dwUBitMask;             // mask for U bits
        DWORD   dwZBitMask;             // mask for Z bits
        DWORD   dwBumpDvBitMask;        // mask for bump map V delta bits
        struct
        {
            uint16    wFlipMSTypes;       // Multisample methods supported via flip for this D3DFORMAT
            uint16    wBltMSTypes;        // Multisample methods supported via blt for this D3DFORMAT
        } MultiSampleCaps;

    };// DUMMYUNIONNAMEN(3);
    union
    {
        DWORD   dwBBitMask;             // mask for blue bits
        DWORD   dwVBitMask;             // mask for V bits
        DWORD   dwStencilBitMask;       // mask for stencil bits
        DWORD   dwBumpLuminanceBitMask; // mask for luminance in bump map
    };// DUMMYUNIONNAMEN(4);
    union
    {
        DWORD   dwRGBAlphaBitMask;      // mask for alpha channel
        DWORD   dwYUVAlphaBitMask;      // mask for alpha channel
        DWORD   dwLuminanceAlphaBitMask;// mask for alpha channel
        DWORD   dwRGBZBitMask;          // mask for Z channel
        DWORD   dwYUVZBitMask;          // mask for Z channel
    };// DUMMYUNIONNAMEN(5);
} DDPIXELFORMAT;

typedef DDPIXELFORMAT FAR* LPDDPIXELFORMAT;

/*
 * DDSURFACEDESC
 */
typedef struct _DDSURFACEDESC
{
    DWORD               dwSize;                 // size of the DDSURFACEDESC structure
    DWORD               dwFlags;                // determines what fields are valid
    DWORD               dwHeight;               // height of surface to be created
    DWORD               dwWidth;                // width of input surface
    union
    {
        LONG            lPitch;                 // distance to start of next line (return value only)
        DWORD           dwLinearSize;           // Formless late-allocated optimized surface size
    } ;//DUMMYUNIONNAMEN(1);
    DWORD               dwBackBufferCount;      // number of back buffers requested
    union
    {
        DWORD           dwMipMapCount;          // number of mip-map levels requested
        DWORD           dwZBufferBitDepth;      // depth of Z buffer requested
        DWORD           dwRefreshRate;          // refresh rate (used when display mode is described)
    } ;//DUMMYUNIONNAMEN(2);
    DWORD               dwAlphaBitDepth;        // depth of alpha buffer requested
    DWORD               dwReserved;             // reserved
    LPVOID              lpSurface;              // pointer to the associated surface memory
    DDCOLORKEY          ddckCKDestOverlay;      // color key for destination overlay use
    DDCOLORKEY          ddckCKDestBlt;          // color key for destination blt use
    DDCOLORKEY          ddckCKSrcOverlay;       // color key for source overlay use
    DDCOLORKEY          ddckCKSrcBlt;           // color key for source blt use
    DDPIXELFORMAT       ddpfPixelFormat;        // pixel format description of the surface
    DDSCAPS             ddsCaps;                // direct draw surface capabilities
} DDSURFACEDESC;

/*
 * DDSURFACEDESC2
 */
typedef struct _DDSURFACEDESC2
{
    DWORD               dwSize;                 // size of the DDSURFACEDESC structure
    DWORD               dwFlags;                // determines what fields are valid
    DWORD               dwHeight;               // height of surface to be created
    DWORD               dwWidth;                // width of input surface
    union
    {
        LONG            lPitch;                 // distance to start of next line (return value only)
        DWORD           dwLinearSize;           // Formless late-allocated optimized surface size
    };// DUMMYUNIONNAMEN(1);
    union
    {
        DWORD           dwBackBufferCount;      // number of back buffers requested
        DWORD           dwDepth;                // the depth if this is a volume texture 
    };// DUMMYUNIONNAMEN(5);
    union
    {
        DWORD           dwMipMapCount;          // number of mip-map levels requestde
                                                // dwZBufferBitDepth removed, use ddpfPixelFormat one instead
        DWORD           dwRefreshRate;          // refresh rate (used when display mode is described)
        DWORD           dwSrcVBHandle;          // The source used in VB::Optimize
    };// DUMMYUNIONNAMEN(2);
    DWORD               dwAlphaBitDepth;        // depth of alpha buffer requested
    DWORD               dwReserved;             // reserved
    LPVOID              lpSurface;              // pointer to the associated surface memory
    union
    {
        DDCOLORKEY      ddckCKDestOverlay;      // color key for destination overlay use
        DWORD           dwEmptyFaceColor;       // Physical color for empty cubemap faces
    };// DUMMYUNIONNAMEN(3);
    DDCOLORKEY          ddckCKDestBlt;          // color key for destination blt use
    DDCOLORKEY          ddckCKSrcOverlay;       // color key for source overlay use
    DDCOLORKEY          ddckCKSrcBlt;           // color key for source blt use
    union
    {
        DDPIXELFORMAT   ddpfPixelFormat;        // pixel format description of the surface
        DWORD           dwFVF;                  // vertex format description of vertex buffers
    };// DUMMYUNIONNAMEN(4);
    DDSCAPS2            ddsCaps;                // direct draw surface capabilities
    DWORD               dwTextureStage;         // stage in multitexture cascade
} DDSURFACEDESC2;

/*
 * ddsCaps field is valid.
 */
#define DDSD_CAPS               0x00000001l     // default

/*
 * dwHeight field is valid.
 */
#define DDSD_HEIGHT             0x00000002l

/*
 * dwWidth field is valid.
 */
#define DDSD_WIDTH              0x00000004l

/*
 * lPitch is valid.
 */
#define DDSD_PITCH              0x00000008l

/*
 * dwBackBufferCount is valid.
 */
#define DDSD_BACKBUFFERCOUNT    0x00000020l

/*
 * dwZBufferBitDepth is valid.  (shouldnt be used in DDSURFACEDESC2)
 */
#define DDSD_ZBUFFERBITDEPTH    0x00000040l

/*
 * dwAlphaBitDepth is valid.
 */
#define DDSD_ALPHABITDEPTH      0x00000080l


/*
 * lpSurface is valid.
 */
#define DDSD_LPSURFACE          0x00000800l

/*
 * ddpfPixelFormat is valid.
 */
#define DDSD_PIXELFORMAT        0x00001000l

/*
 * ddckCKDestOverlay is valid.
 */
#define DDSD_CKDESTOVERLAY      0x00002000l

/*
 * ddckCKDestBlt is valid.
 */
#define DDSD_CKDESTBLT          0x00004000l

/*
 * ddckCKSrcOverlay is valid.
 */
#define DDSD_CKSRCOVERLAY       0x00008000l

/*
 * ddckCKSrcBlt is valid.
 */
#define DDSD_CKSRCBLT           0x00010000l

/*
 * dwMipMapCount is valid.
 */
#define DDSD_MIPMAPCOUNT        0x00020000l

 /*
  * dwRefreshRate is valid
  */
#define DDSD_REFRESHRATE        0x00040000l

/*
 * dwLinearSize is valid
 */
#define DDSD_LINEARSIZE         0x00080000l

/*
 * dwTextureStage is valid
 */
#define DDSD_TEXTURESTAGE       0x00100000l
/*
 * dwFVF is valid
 */
#define DDSD_FVF                0x00200000l
/*
 * dwSrcVBHandle is valid
 */
#define DDSD_SRCVBHANDLE        0x00400000l

/*
 * dwDepth is valid
 */
#define DDSD_DEPTH              0x00800000l

/*
 * All input fields are valid.
 */
#define DDSD_ALL                0x00fff9eel

typedef DDSURFACEDESC* LPDDSURFACEDESC;

typedef struct IDirectDrawSurface       FAR *LPDIRECTDRAWSURFACE;

/*
 * IDirectDraw
 */
//#if defined( _WIN32 ) && !defined( _NO_COM )
#undef INTERFACE
#define INTERFACE IDirectDraw
DECLARE_INTERFACE_( IDirectDraw, IUnknown )
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj) PURE;
   // STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
   // STDMETHOD_(ULONG,Release) (THIS) PURE;
    /*** IDirectDraw methods ***/
    STDMETHOD(Compact)(THIS) PURE;
	 /*
    STDMETHOD(CreateClipper)(THIS_ DWORD, LPDIRECTDRAWCLIPPER FAR*, IUnknown FAR * ) PURE;
    STDMETHOD(CreatePalette)(THIS_ DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE FAR*, IUnknown FAR * ) PURE;
    STDMETHOD(CreateSurface)(THIS_  LPDDSURFACEDESC, LPDIRECTDRAWSURFACE FAR *, IUnknown FAR *) PURE;
    STDMETHOD(DuplicateSurface)( THIS_ LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE FAR * ) PURE;
    STDMETHOD(EnumDisplayModes)( THIS_ DWORD, LPDDSURFACEDESC, LPVOID, LPDDENUMMODESCALLBACK ) PURE;
    STDMETHOD(EnumSurfaces)(THIS_ DWORD, LPDDSURFACEDESC, LPVOID,LPDDENUMSURFACESCALLBACK ) PURE;
    STDMETHOD(FlipToGDISurface)(THIS) PURE;
    STDMETHOD(GetCaps)( THIS_ LPDDCAPS, LPDDCAPS) PURE;
    STDMETHOD(GetDisplayMode)( THIS_ LPDDSURFACEDESC) PURE;
    STDMETHOD(GetFourCCCodes)(THIS_  LPDWORD, LPDWORD ) PURE;
    STDMETHOD(GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE FAR *) PURE;
    STDMETHOD(GetMonitorFrequency)(THIS_ LPDWORD) PURE;
    STDMETHOD(GetScanLine)(THIS_ LPDWORD) PURE;
    STDMETHOD(GetVerticalBlankStatus)(THIS_ LPBOOL ) PURE;
    STDMETHOD(Initialize)(THIS_ GUID FAR *) PURE;
    STDMETHOD(RestoreDisplayMode)(THIS) PURE;
    STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD) PURE;
    STDMETHOD(SetDisplayMode)(THIS_ DWORD, DWORD,DWORD) PURE;
    STDMETHOD(WaitForVerticalBlank)(THIS_ DWORD, HANDLE ) PURE;
	 */
};

//#if defined( _WIN32 ) && !defined( _NO_COM )
#undef INTERFACE
#define INTERFACE IDirectDraw2
DECLARE_INTERFACE_( IDirectDraw2, IUnknown )
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj) PURE;
  //  STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
   // STDMETHOD_(ULONG,Release) (THIS) PURE;
    /*** IDirectDraw methods ***/
    STDMETHOD(Compact)(THIS) PURE;
    STDMETHOD(CreateClipper)(THIS_ DWORD, LPDIRECTDRAWCLIPPER FAR*, IUnknown FAR * ) PURE;
    STDMETHOD(CreatePalette)(THIS_ DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE FAR*, IUnknown FAR * ) PURE;
    STDMETHOD(CreateSurface)(THIS_  LPDDSURFACEDESC, LPDIRECTDRAWSURFACE FAR *, IUnknown FAR *) PURE;
    STDMETHOD(DuplicateSurface)( THIS_ LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE FAR * ) PURE;
	 /*
    STDMETHOD(EnumDisplayModes)( THIS_ DWORD, LPDDSURFACEDESC, LPVOID, LPDDENUMMODESCALLBACK ) PURE;
    STDMETHOD(EnumSurfaces)(THIS_ DWORD, LPDDSURFACEDESC, LPVOID,LPDDENUMSURFACESCALLBACK ) PURE;
    STDMETHOD(FlipToGDISurface)(THIS) PURE;
    STDMETHOD(GetCaps)( THIS_ LPDDCAPS, LPDDCAPS) PURE;
    STDMETHOD(GetDisplayMode)( THIS_ LPDDSURFACEDESC) PURE;
    STDMETHOD(GetFourCCCodes)(THIS_  LPDWORD, LPDWORD ) PURE;
    STDMETHOD(GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE FAR *) PURE;
    STDMETHOD(GetMonitorFrequency)(THIS_ LPDWORD) PURE;
    STDMETHOD(GetScanLine)(THIS_ LPDWORD) PURE;
    STDMETHOD(GetVerticalBlankStatus)(THIS_ LPBOOL ) PURE;
    STDMETHOD(Initialize)(THIS_ GUID FAR *) PURE;
    STDMETHOD(RestoreDisplayMode)(THIS) PURE;
	 */
    STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD) PURE;
    STDMETHOD(SetDisplayMode)(THIS_ DWORD, DWORD,DWORD, DWORD, DWORD) PURE;
    STDMETHOD(WaitForVerticalBlank)(THIS_ DWORD, HANDLE ) PURE;
    /*** Added in the v2 interface ***/
    STDMETHOD(GetAvailableVidMem)(THIS_ LPDDSCAPS, LPDWORD, LPDWORD) PURE;
};

/****************************************************************************
 *
 * DIRECTDRAW SETCOOPERATIVELEVEL FLAGS
 *
 ****************************************************************************/

/*
 * Exclusive mode owner will be responsible for the entire primary surface.
 * GDI can be ignored. used with DD
 */
#define DDSCL_FULLSCREEN                        0x00000001l

/*
 * allow CTRL_ALT_DEL to work while in fullscreen exclusive mode
 */
#define DDSCL_ALLOWREBOOT                       0x00000002l

/*
 * prevents DDRAW from modifying the application window.
 * prevents DDRAW from minimize/restore the application window on activation.
 */
#define DDSCL_NOWINDOWCHANGES                   0x00000004l

/*
 * app wants to work as a regular Windows application
 */
#define DDSCL_NORMAL                            0x00000008l

/*
 * app wants exclusive access
 */
#define DDSCL_EXCLUSIVE                         0x00000010l

/*
 * app can deal with non-windows display modes
 */
#define DDSCL_ALLOWMODEX                        0x00000040l

/*
 * this window will receive the focus messages
 */
#define DDSCL_SETFOCUSWINDOW                    0x00000080l

/*
 * this window is associated with the DDRAW object and will
 * cover the screen in fullscreen mode
 */
#define DDSCL_SETDEVICEWINDOW                   0x00000100l

/*
 * app wants DDRAW to create a window to be associated with the
 * DDRAW object
 */
#define DDSCL_CREATEDEVICEWINDOW                0x00000200l

/*
 * App explicitly asks DDRAW/D3D to be multithread safe. This makes D3D
 * take the global crtisec more frequently.
 */
#define DDSCL_MULTITHREADED                     0x00000400l

/*
 * App specifies that it would like to keep the FPU set up for optimal Direct3D
 * performance (single precision and exceptions disabled) so Direct3D
 * does not need to explicitly set the FPU each time. This is assumed by
 * default in DirectX 7. See also DDSCL_FPUPRESERVE
 */
#define DDSCL_FPUSETUP                          0x00000800l

/*
 * App specifies that it needs either double precision FPU or FPU exceptions
 * enabled. This makes Direct3D explicitly set the FPU state eah time it is
 * called. Setting the flag will reduce Direct3D performance. The flag is
 * assumed by default in DirectX 6 and earlier. See also DDSCL_FPUSETUP
 */
#define DDSCL_FPUPRESERVE                          0x00001000l

typedef struct IDirectDraw              FAR *LPDIRECTDRAW;

#define STDAPI __stdcall
#define STDAPICALLTYPE __stdcall

#ifdef _OLE32_
#define WINOLEAPI        STDAPI
#define WINOLEAPI_(type) STDAPI_(type)
#else

#define WINOLEAPI        EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define WINOLEAPI_(type) EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE

#define SUCCEEDED(x)	((x) >= 0)

#endif

}

extern "C"
{

	namespace System
	{
		namespace MSWindows
		{

WINOLEAPI  CoInitialize(void* pvReserved);
WINOLEAPI_(void)  CoUninitialize(void);

    extern HRESULT WINAPI DirectDrawCreate( GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter );
//    extern HRESULT WINAPI DirectDrawCreateEx( GUID FAR * lpGuid, LPVOID  *lplpDD, REFIID  iid,IUnknown FAR *pUnkOuter );
  //  extern HRESULT WINAPI DirectDrawCreateClipper( DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter );

		}
	}
}

namespace System
{
namespace UI
{

extern UIEXT __live_object_ptr<LayoutManager> pLayoutManager;

IDirectDraw2* dd2;

FullscreenWindow::FullscreenWindow()
{
	m_dds = NULL;
}

bool FullscreenWindow::CreateFull()
{
	LDraw::RectI rc(0, 0, GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	MSWindows::HWND hWnd = Create(NULL, rc, NULL, WS_POPUP | WS_VISIBLE/*, WS_EX_TOPMOST*/);
	if (hWnd == NULL)
		return false;

	CoInitialize(NULL);

	IDirectDraw* dd;
	HRESULT hr = DirectDrawCreate(NULL, &dd, NULL);

	hr = dd->QueryInterface(IID_IDirectDraw2, reinterpret_cast<void**>(&dd2));
	ASSERT(SUCCEEDED(hr));

	if (true)
	{
		hr = dd2->SetCooperativeLevel(hWnd, DDSCL_NORMAL/*DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN*/);
		ASSERT(SUCCEEDED(hr));

		DDSURFACEDESC ddsd;
		ddsd.dwSize = sizeof(ddsd); 

		// Tell DirectDraw which members are valid. 
		ddsd.dwFlags = DDSD_CAPS; 

		// Request a primary surface. 
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		hr = dd2->CreateSurface(&ddsd, &m_dds, NULL);
		ASSERT(SUCCEEDED(hr));
	}
	else
	{
		hr = dd2->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT);
		ASSERT(SUCCEEDED(hr));

		DDSURFACEDESC ddsd; 
		ddsd.dwSize = sizeof(ddsd); 

		// Tell DirectDraw which members are valid. 
		ddsd.dwFlags = DDSD_CAPS; 

		// Request a primary surface. 
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		hr = dd2->CreateSurface(&ddsd, &m_dds, NULL);
		ASSERT(SUCCEEDED(hr));
	}

	return true;
}

bool FullscreenWindow::ProcessWindowMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ )
{
	BOOL bHandled;
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		lResult = OnLButtonDown(uMsg, wParam, lParam, bHandled);
		break;

	case WM_LBUTTONUP:
		lResult = OnLButtonUp(uMsg, wParam, lParam, bHandled);
		break;

	case WM_MOUSEMOVE:
		lResult = OnMouseMove(uMsg, wParam, lParam, bHandled);
		break;

	default:
		return false;
	}
	return true;
}

LRESULT FullscreenWindow::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MSWindows::POINT point;
	point.x = (short)MSWindows::LoWORD(lParam);
	point.y = (short)MSWindows::HiWORD(lParam);
	UINT nFlags = wParam;

	MSWindows::POINT screenpt = point;
	MSWindows::ClientToScreen(m_hWnd, &screenpt);

	ASSERT(0);
#if 0
	Screen2* pScreen = *m_surfaceList.begin();

	pScreen->m_Visual->OnButtonDown(0, LDraw::PointD(screenpt.x, screenpt.y), LDraw::Point(point.x, point.y), 0, false);
#endif

	//m_pClient->OnButtonDown(nFlags, screenpt, point, 0, false);

	//Invalidate();	// TODO remove

	return 0;
}

LRESULT FullscreenWindow::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)MSWindows::LoWORD(lParam);
	point.y = (short)MSWindows::HiWORD(lParam);
	UINT nFlags = wParam;

	POINT screenpt = point;
	MSWindows::ClientToScreen(m_hWnd, &screenpt);

	ASSERT(0);
#if 0

	Screen2* pScreen = *m_surfaceList.begin();

	pScreen->m_Visual->OnButtonUp(0, LDraw::PointD(screenpt.x, screenpt.y), LDraw::Point(point.x, point.y), 0);

#endif
	//m_pClient->OnButtonUp(nFlags, screenpt, point, 0);

	/*
	if (m_hWnd)	// Maybe it's been closed by the above function
	{
		Invalidate();	// TODO remove
	}
	*/

	return 0;
}

LRESULT FullscreenWindow::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)MSWindows::LoWORD(lParam);
	point.y = (short)MSWindows::HiWORD(lParam);
	UINT nFlags = wParam;

	POINT screenpt = point;
	MSWindows::ClientToScreen(m_hWnd, &screenpt);

	ASSERT(0);
#if 0

	Screen2* pScreen = *m_surfaceList.begin();

	pScreen->m_Visual->m_bInsideWindow = true;
	pScreen->m_Visual->OnMouseMove(0, LDraw::PointD(screenpt.x, screenpt.y), LDraw::Point(point.x, point.y));
#endif

	return 0;
}

#if 0
///////////////////////////////////////////////////////////////////////////////////
// Screen2

Screen2::Screen2()
{
	m_pOwnerFullscreen = NULL;
	m_dds = NULL;
	m_y = 0;
	m_x = 0;

	m_bInvalidated = false;

	m_pCanvas = new Canvas;
	m_pCanvas->put_Width(new Length(1024));
	m_pCanvas->put_Height(new Length(768));
	{
		Rectangle* rect = new Rectangle;
		rect->put_Width(new Length(1024));
		rect->put_Height(new Length(768));
		rect->put_Fill(new SolidColorBrush(new Color(140, 160, 240)));

		m_pCanvas->AddRChild(rect);
	}

	m_Visual = new WindowBase;
	m_Visual->m_pSite = this;
	m_Visual->put_VisualTree(m_pCanvas);
}

WindowHost* Screen2::OpenWindow()
{
	CUIFrameImpl2* pSite = new CUIFrameImpl2;
	pSite->m_pOwnerScreen = this;
	return pSite;
#if 0
	pWindowClient->m_pWindowHost = pSite;
	pSite->m_pClient->put_VisualTree(dynamic_cast<UIElement*>(pWindowClient));

//	pSite->m_pClient->Measure(LDraw::SizeD(0, 0));
//	pSite->m_pClient->Arrange(pSite->m_pClient->m_desiredSize);

//	pSite->put_Width(new Length(pSite->m_pClient->m_computedSize.Width, Length::UnitAbsolute));
//	pSite->put_Height(new Length(pSite->m_pClient->m_computedSize.Height, Length::UnitAbsolute));

	m_pCanvas->AddRChild(pSite/*dynamic_cast<UIElement*>(pWindowClient)*/);
	m_pCanvas->InvalidateMeasure();
	pLayoutManager->MeasureAll();

#if 0
	CUIFrameImpl2* pWindowSite = new CUIFrameImpl2;
	pWindowSite->m_pClient = pWindowClient;
	pWindowSite->put_VisualTree(pWindowClient);

	pWindowSite->m_pOwnerScreen = this;

	m_pCanvas->AddRChild(pWindowSite);
//	m_pCanvas->AddRChild(pWindowClient);
	m_pCanvas->InvalidateMeasure();

	m_pActiveFrame = pWindowSite;

	pLayoutManager->MeasureAll();

	return pWindowSite;
#endif
#endif
}

void Screen2::Create()
{
//	m_pClient->Measure(LDraw::SizeD(0, 0));
//	m_pClient->Arrange(m_pClient->m_desiredSize);

	m_Visual->Measure(LDraw::SizeD(1024, 768));
	m_Visual->Arrange(LDraw::SizeD(1024, 768));

	DDSURFACEDESC ddsd;
	ddsd.dwSize = sizeof(ddsd); 

	// Tell DirectDraw which members are valid. 
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

	// (This assumes that the offscreen surface we are about
	// to create will match the pixel format of the 
	// primary surface.)
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN; 
	ddsd.dwWidth = 1024;
	ddsd.dwHeight = 768;

	HRESULT hr = dd2->CreateSurface(&ddsd, &m_dds, NULL);
	ASSERT(SUCCEEDED(hr));
}

void Screen2::Render()
{
	LDraw::RectI rect;
	m_invalidRegion->GetRegionRect(&rect);

	if (UpdateBitmap())
	{
		/*
		LDraw::RectI rect;
		rect.X = (int)floor(clip.X);
		rect.Y = (int)floor(clip.Y);
		rect.Width = (int)ceil(clip.GetRight()) - rect.X;
		rect.Height = (int)ceil(clip.GetBottom()) - rect.Y;
*/
		/*
		DDSURFACEDESC ddsd;
		m_dds->Lock(NULL, &ddsd, DDLOCK_WRITEONLY, NULL);
		m_dds->Unlock();
		*/

		RECT dstRect = {rect.X, rect.Y, rect.GetRight(), rect.GetBottom()};
		RECT srcRect = dstRect;

		HRESULT hr = m_pOwnerFullscreen->m_dds->Blt(&dstRect, m_dds, &srcRect, 0, NULL);
	//	HRESULT hr = m_pOwnerFullscreen->m_dds->BltFast(dstRect.left, dstRect.top, m_dds, &srcRect, DDBLTFAST_NOCOLORKEY);
	//	ASSERT(SUCCEEDED(hr));
	}

	m_invalidRegion->MakeEmpty();	// empty
	m_bInvalidated = false;
}

bool Screen2::UpdateBitmap()
{
	DDSURFACEDESC ddsd;
	ddsd.dwSize = sizeof(ddsd);
	HRESULT hr = m_dds->Lock(NULL, &ddsd, DDLOCK_NOSYSLOCK | DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	if (hr != DD_OK)
		return false;

	{
		LDraw::Bitmap* bitmap = new LDraw::Bitmap(&ddsd);
		{
			Graphics* graphics = new Graphics(new LDraw::GraphicsO(bitmap));

			LDraw::RectI bounds;
			m_invalidRegion->GetRegionRect(&bounds);

		//	LDraw::Region pOldRgn;
		//	graphics.GetClip(&m_clip);

			graphics->m_p->SetClip(m_invalidRegion);
		//	m_invalidRegion.MakeEmpty();

			if (true)
			{
				graphics->Clear(LDraw::Color(0, 0, 0, 0));
				/*
				graphics.SetCompositingMode(LDraw::CompositingModeSourceCopy);
				graphics.FillRectangle(LDraw::SolidBrush(LDraw::Color(0, 0, 0, 0)), bounds);
				graphics.SetCompositingMode(LDraw::CompositingModeSourceOver);
				*/
			}

			//graphics.TranslateTransform(-m_expandedBBox.X, -m_expandedBBox.Y);	// ???
			m_Visual->OnRender(graphics);

			//delete graphics.m_clip.m_pRgn;
		//	graphics.GetClip(&m_invalidRegion);
		//	graphics.m_clip = pOldRgn;
		}
	}
	hr = m_dds->Unlock(NULL);
	ASSERT(SUCCEEDED(hr));

	return true;
}

/*
void Screen2::InvalidateRect(const LDraw::RectD& rect)
{
//	MessageBeep(-1);
	if (rect.IsEmptyArea())
		return;

	LDraw::RectD xrect = rect;
	//xrect.Offset(-m_pClientVisual->m_expandedBBox.X, -m_pClientVisual->m_expandedBBox.Y);

	if (!m_bInvalidated)
	{
		m_bInvalidated = true;
		pLayoutManager->m_windowList.push_back(this);
	}

	m_invalidRegion.Union(rect);
}
*/
#endif

}	// UI
}

#endif