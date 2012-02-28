#include "stdafx.h"
#include "LSVG2.h"
#include "SVGCursorElement.h"
//#include "PSVGCursorElement.h"

/* TODO, Maybe I can use this code..

Hi,

You may want to make sure you are setting up your CreateIconIndirect 
correctly.  In my article (ID = 318876), I create an empty mask bitmap:



HCURSOR CreateAlphaCursor(void)
{
    HDC hMemDC;
    DWORD dwWidth, dwHeight;
    BITMAPV5HEADER bi;
    HBITMAP hBitmap, hOldBitmap;
    void *lpBits;
    DWORD x,y;
    HCURSOR hAlphaCursor = NULL;

    dwWidth  = 32;  // width of cursor
    dwHeight = 32;  // height of cursor

    ZeroMemory(&bi,sizeof(BITMAPV5HEADER));
    bi.bV5Size           = sizeof(BITMAPV5HEADER);
    bi.bV5Width           = dwWidth;
    bi.bV5Height          = dwHeight;
    bi.bV5Planes = 1;
    bi.bV5BitCount = 32;
    bi.bV5Compression = BI_BITFIELDS;
    // The following mask specification specifies a supported 32 BPP
    // alpha format for Windows XP.
    bi.bV5RedMask   =  0x00FF0000;
    bi.bV5GreenMask =  0x0000FF00;
    bi.bV5BlueMask  =  0x000000FF;
    bi.bV5AlphaMask =  0xFF000000; 

    HDC hdc;
    hdc = GetDC(NULL);

    // Create the DIB section with an alpha channel.
    hBitmap = CreateDIBSection(hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, 
        (void **)&lpBits, NULL, (DWORD)0);

    hMemDC = CreateCompatibleDC(hdc);
    ReleaseDC(NULL,hdc);

    // Draw something on the DIB section.
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
    PatBlt(hMemDC,0,0,dwWidth,dwHeight,WHITENESS);
    SetTextColor(hMemDC,RGB(0,0,0));
    SetBkMode(hMemDC,TRANSPARENT);
    TextOut(hMemDC,0,9,"rgba",4);
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    // Create an empty mask bitmap.
    HBITMAP hMonoBitmap = CreateBitmap(dwWidth,dwHeight,1,1,NULL);

    // Set the alpha values for each pixel in the cursor so that
    // the complete cursor is semi-transparent.
    DWORD *lpdwPixel;
    lpdwPixel = (DWORD *)lpBits;
    for (x=0;x<dwWidth;x++)
       for (y=0;y<dwHeight;y++)
       {
           // Clear the alpha bits
           *lpdwPixel &= 0x00FFFFFF;
           // Set the alpha bits to 0x9F (semi-transparent)
           *lpdwPixel |= 0x9F000000;
           lpdwPixel++;
       }

    ICONINFO ii;
    ii.fIcon = FALSE;  // Change fIcon to TRUE to create an alpha icon
    ii.xHotspot = 0;
    ii.yHotspot = 0;
    ii.hbmMask = hMonoBitmap;
    ii.hbmColor = hBitmap;

    // Create the alpha cursor with the alpha DIB section.
    hAlphaCursor = CreateIconIndirect(&ii);

    DeleteObject(hBitmap);          
    DeleteObject(hMonoBitmap); 

    return hAlphaCursor;
}







Thanks,
-Greg
Microsoft Developer Support



This posting is provided "AS IS" with no warranties, and confers no rights.
Visit http://www.microsoft.com/security for current information on security.



*/

namespace System
{
namespace Web
{

SVGCursorElement::SVGCursorElement() : SVGElement(new PSVGElement(this))
{
	m_x = nullptr;
	m_y = nullptr;

	m_bTriedLoaded = false;

	m_pImage = nullptr;
	m_hCursor = nullptr;

//	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x")));
//	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y")));

	SetAllValues(this);
}

ISVGAnimatedLength* SVGCursorElement::get_x()
{
	return m_x;
}

ISVGAnimatedLength* SVGCursorElement::get_y()
{
	return m_y;
}

ErrorCode SVGCursorElement::Load()
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	if (!m_bTriedLoaded)
	{
		m_bTriedLoaded = true;

//		ATLASSERT(m_document == NULL);
//		ATLASSERT(m_pSVGDocumentView == NULL);
		ASSERT(m_pImage == NULL);

		sysstring src = m_href->m_animated->m_animVal->m_value;
		if (src.length())
		{
			TCHAR result[2048];
			{
				sysstring documentUrl = m_ownerDocument->get_url();

				sysstring baseUrl = documentUrl;

				DWORD resultLen = sizeof(result);
				InternetCombineUrl(baseUrl, W2A(src), result, &resultLen, 0);
			}

			/*
			m_document.CoCreateInstance(CLSID_LSVGDocument);
			bool bSVGDocument;
			m_document->load(_bstr_t(result), &bSVGDocument);
			if (!bSVGDocument)
			*/
			{
				// Try to load it as raster bitmap
			//	m_document.Release();
				m_pImage = g_Images.OpenImage(result);
			}

			return S_OK;
		}
	}
#endif
	return Error;
}

HCURSOR SVGCursorElement::GetCursor()
{
	Load();

	if (m_hCursor == NULL)
	{
		if (m_pImage)
		{
			/*
			ICONINFO iconinfo;
			iconinfo.fIcon = FALSE;
			iconinfo.xHotspot = 0;
			iconinfo.yHotspot = 0;
			iconinfo.hbmMask = NULL;
			iconinfo.hbmColor = 

			CreateIconIndirect(&iconinfo);
			*/

			ASSERT(0);
#if 0
			m_pImage->m_gdipImage->GetHICON((HICON*)&m_hCursor);
#endif
		}
	}

	return m_hCursor;
}

CImage* SVGCursorElement::GetImage()
{
	Load();
	return m_pImage;
}

// TODO, not here

SVGAnimatedPreserveAspectRatio::SVGAnimatedPreserveAspectRatio()
{
//		m_pAttr = NULL;

	m_baseVal = new SVGPreserveAspectRatio;
	m_animVal = m_baseVal;//new SVGPreserveAspectRatio;
}

}	// Web
}	// System
