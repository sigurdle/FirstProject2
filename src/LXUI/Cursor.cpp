#include "stdafx.h"
#include "LXUI2.h"
#include "Cursor.h"

namespace System
{
namespace MSWindows
{

typedef struct _ICONINFO {
    BOOL    fIcon;
    DWORD   xHotspot;
    DWORD   yHotspot;
    HBITMAP hbmMask;
    HBITMAP hbmColor;
} ICONINFO;
typedef ICONINFO *PICONINFO;

extern "C"
{

WINUSERAPI
BOOL
WINAPI
GetIconInfo(
    IN HICON hIcon,
    OUT PICONINFO piconinfo);

WINUSERAPI
BOOL
WINAPI
DestroyIcon(
    IN HICON hIcon);

WINUSERAPI
HICON
WINAPI
CreateIconIndirect(
    IN PICONINFO piconinfo);

}	// extern "C"
}	// MSWindows
}	// System

namespace System
{
	LFCEXT extern Heap* heap;
}

namespace System
{
using namespace MSWindows;

namespace UI
{

Cursor::Cursor()
{
	m_parent = NULL;
	m_Visual = NULL;
	m_HotspotX = 0;
	m_HotspotY = 0;
	m_hCursor = NULL;
}

#if WIN32

Cursor::Cursor(HCURSOR hCursor)
{
	if ((uint8*)hCursor >= heap->m_data && (uint8*)hCursor < heap->m_data + heap->m_size*2)
	{
		ASSERT(0);
		MessageBoxA(NULL, "", "cursor oops", MB_OK);
	}

	m_parent = NULL;
	ICONINFO ii;
	GetIconInfo(hCursor, &ii);

	m_HotspotX = ii.xHotspot;
	m_HotspotY = ii.yHotspot;

	m_Visual = NULL;
	//m_Visual = new Image(new MemoryImageSource(LDraw::Bitmap(ii.hbmMask)));
	m_hCursor = hCursor;
}
#endif

Cursor::~Cursor()
{
	if (m_hCursor)
	{
#if WIN32
		::DestroyIcon(m_hCursor);
#endif
	}
}

DependencyObject* Cursor::GetDependencyParent()
{
	return m_rparent;
}

double Cursor::get_HotspotX()
{
	return m_HotspotX;
}

void Cursor::set_HotspotX(double x)
{
	m_HotspotX = x;
}

double Cursor::get_HotspotY()
{
	return m_HotspotY;
}

void Cursor::set_HotspotY(double y)
{
	m_HotspotY = y;
}

void Cursor::set_Visual(Visual* pVisual)
{
	m_Visual = pVisual;
}

#if WIN32
HCURSOR Cursor::GetHCursor()
{
	if (m_hCursor == NULL)
	{
		m_hCursor = CreateAlphaCursor();
	}

	return m_hCursor;
}

HCURSOR Cursor::CreateAlphaCursor()
{
	MSWindows::BITMAPV5HEADER bi;
	HBITMAP hBitmap;
	void *lpBits;

	HCURSOR hAlphaCursor = NULL;
	
	ASSERT(0);
#if 0
	m_Visual->Measure(LDraw::SizeD(0, 0));
	m_Visual->Arrange(LDraw::RectD(LDraw::PointD(0, 0), m_Visual->get_DesiredSize()));
#endif

	int dwWidth  = m_Visual->m_expandedBBox.Width;
	int dwHeight = m_Visual->m_expandedBBox.Height;
	
	std::memset(&bi, 0, sizeof(MSWindows::BITMAPV5HEADER));
	bi.bV5Size = sizeof(MSWindows::BITMAPV5HEADER);
	bi.bV5Width = dwWidth;
	bi.bV5Height = dwHeight;
	bi.bV5Planes = 1;
	bi.bV5BitCount = 32;
	bi.bV5Compression = BI_BITFIELDS;
	// The following mask specification specifies a supported 32 BPP
	// alpha format for Windows XP.
	bi.bV5RedMask   =  0x00FF0000;
	bi.bV5GreenMask =  0x0000FF00;
	bi.bV5BlueMask  =  0x000000FF;
	bi.bV5AlphaMask =  0xFF000000;
	
	// Create the DIB section with an alpha channel.
	hBitmap = MSWindows::CreateDIBSection(NULL, (MSWindows::BITMAPINFO*)&bi, DIB_RGB_COLORS, 
		(void **)&lpBits, NULL, (DWORD)0);
	
	{
		LDraw::Bitmap* bitmap = new LDraw::Bitmap(hBitmap);
		{
			/*
			Graphics* graphics = new Graphics(new LDraw::GraphicsO(bitmap));
			graphics->TranslateTransform(-m_Visual->m_expandedBBox.X, -m_Visual->m_expandedBBox.Y);
			m_Visual->Render(graphics);
			*/
		}
	}
	
	// Create an empty mask bitmap.
	HBITMAP hMonoBitmap = MSWindows::CreateBitmap(dwWidth,dwHeight,1,1,NULL);
	
	ICONINFO ii;
	ii.fIcon = false;
	ii.xHotspot = get_HotspotX() - m_Visual->m_expandedBBox.X;
	ii.yHotspot = get_HotspotY() - m_Visual->m_expandedBBox.Y;
	ii.hbmMask = hMonoBitmap;
	ii.hbmColor = hBitmap;
	
	// Create the alpha cursor with the alpha DIB section.
	hAlphaCursor = CreateIconIndirect(&ii);
	
	MSWindows::DeleteObject((void*)hBitmap);          
	MSWindows::DeleteObject((void*)hMonoBitmap); 
	
	return hAlphaCursor;
}
#endif

}	// UI
}
