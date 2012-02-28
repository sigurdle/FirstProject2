// Read EMF/WMF files

#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "SVGReadEMF.h"

#if 0

/////////////////////
// Gdiplus utils

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

//////////////

// The Base64 Alphabet 

char Base64Chars[64] =
{
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
	'G',
	'H',
	'I',
	'J',
	'K',
	'L',
	'M',
	'N',
	'O',
	'P',
	'Q',
	'R',
	'S',
	'T',
	'U',
	'V',
	'W',
	'X',
	'Y',
	'Z',

	'a',
	'b',
	'c',
	'd',
	'e',
	'f',
	'g',
	'h',
	'i',
	'j',
	'k',
	'l',
	'm',
	'n',
	'o',
	'p',
	'q',
	'r',
	's',
	't',
	'u',
	'v',
	'w',
	'x',
	'y',
	'z',

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	'+',
	'/',
};

#include "..\Utils\WCharString.h"

HRESULT EncodeBase64(BYTE* pData, int totalSize, BSTR* pVal)
{
	int triplets = (int)(totalSize/3);

	BYTE* p = pData;

	CWCharString buf;

	for (int i = 0; i < triplets; i++)
	{
		if ((i % 18) == 0) buf += L"\n";

		DWORD bits24;
		bits24 = ((DWORD)p[0]<<16) | ((DWORD)p[1]<<8) | ((DWORD)p[2]<<0);

		WCHAR buf2[5];

		buf2[0] = Base64Chars[(bits24 >> 18) & 0x3f];
		buf2[1] = Base64Chars[(bits24 >> 12) & 0x3f];
		buf2[2] = Base64Chars[(bits24 >> 6) & 0x3f];
		buf2[3] = Base64Chars[(bits24 >> 0) & 0x3f];
		buf2[4] = 0;

		buf += buf2;

		p += 3;
	}

	int size = triplets*3;

	if (totalSize > size)
	{
		WCHAR buf2[5];

		DWORD bits24 = 0;

		bits24 |= (DWORD)p[0]<<16;

		if (totalSize > size+1)
		{
			bits24 |= (DWORD)p[1]<<8;

			buf2[0] = Base64Chars[(bits24 >> 18) & 0x3f];
			buf2[1] = Base64Chars[(bits24 >> 12) & 0x3f];
			buf2[2] = Base64Chars[(bits24 >> 6) & 0x3f];
			buf2[3] = L'=';
		}
		else
		{
			buf2[0] = Base64Chars[(bits24 >> 18) & 0x3f];
			buf2[1] = Base64Chars[(bits24 >> 12) & 0x3f];
			buf2[2] = L'=';
			buf2[3] = L'=';
		}

		buf2[4] = 0;

		buf += buf2;
	}

	*pVal = buf.copyBSTR();

	return S_OK;
}

///////////

#pragma pack(push,1)

typedef struct tagOLDRECT
{
    short left;
    short top;
    short right;
    short bottom;
} OLDRECT;

// Placeable metafile header 
typedef struct
{
	DWORD		key;
	WORD		hmf;
	OLDRECT	bbox;
	WORD		inch;
	DWORD		reserved;
	WORD		checksum;
}
ALDUSMFHEADER;

#define METAFILE_VERSION	1
#define ALDUSKEY				0x9AC6CDD7
#define ALDUSMFHEADERSIZE	22	// Avoid sizeof is struct alignment >1

#pragma pack(pop)

static HENHMETAFILE GetMyEnhMetaFile(FILE* fp)
{
	HENHMETAFILE hemf = NULL;

	DWORD   		dwIsAldus;
	METAHEADER		mfHeader;
  	DWORD    		dwSize;
	DWORD			seekpos;
	ALDUSMFHEADER	m_aldusMFHeader;

	if (fread(&dwIsAldus, sizeof(dwIsAldus), 1, fp) != 1)
		return FALSE;
	
	if (dwIsAldus != ALDUSKEY) {
		// A windows metafile, not a placeable wmf 
		seekpos = 0;
		::ZeroMemory(&m_aldusMFHeader, sizeof(m_aldusMFHeader));
	}
	else
	{  
		// This is a placeable metafile 
	        // Convert the placeable format into something that can
	        // be used with GDI metafile functions 
		fseek(fp, 0, SEEK_SET);
		if (fread(&m_aldusMFHeader, ALDUSMFHEADERSIZE, 1, fp) != 1)
			return FALSE;
		seekpos = ALDUSMFHEADERSIZE;
	}
	fseek(fp, seekpos, SEEK_SET);
	// Read the metafile header 
	if (fread(&mfHeader, sizeof(mfHeader), 1, fp) != 1)
		return FALSE;
	// At this point we have a metafile header regardless of whether
	// the metafile was a windows metafile or a placeable metafile
	// so check to see if it is valid.  There is really no good
	// way to do this so just make sure that the mtType is either
	// 1 or 2 (memory or disk file) 
	if ((mfHeader.mtType != 1) && (mfHeader.mtType != 2)) 
		return FALSE;
	// Allocate memory for the metafile bits 
	dwSize = mfHeader.mtSize * 2;
	BYTE* lpMFBits = new BYTE [dwSize];
	if (lpMFBits == NULL)
		return FALSE;
	// Seek to the metafile bits 
	fseek(fp, seekpos, SEEK_SET);
	// Read metafile bits and create
	// the enhanced metafile
	if (fread(lpMFBits, dwSize, 1, fp) == 1)
		hemf = ::SetWinMetaFileBits(dwSize, lpMFBits, NULL, NULL);
	// Done with the bit data	
	delete [] lpMFBits;

	return hemf;
}

static HENHMETAFILE GetMyEnhMetaFile(LPCTSTR lpszPathName)
{
	// Open the file
	FILE* fp = fopen(lpszPathName, "rb");
	if (fp)
	{
		HENHMETAFILE hemf = GetMyEnhMetaFile(fp);
		fclose(fp);
		return hemf;
	}

	return NULL;
}

void LPToDP(HDC hDC, int Lx, int Ly, double*px, double*py)
{
/*
	POINT WO;
	GetWindowOrgEx(hDC, &WO);

	SIZE WE;
	GetWindowExtEx(hDC, &WE);

	POINT VO;
	GetViewportOrgEx(hDC, &VO);

	SIZE VE;
	GetViewportExtEx(hDC, &VE);

	*px = ((double)(Lx - WO.x) * (double)VE.cx / (double)WE.cx) + VO.x;
	*py = ((double)(Ly - WO.y) * (double)VE.cy / (double)WE.cy) + VO.y;
*/

	POINT pt;
	pt.x = Lx;
	pt.y = Ly;
	LPtoDP(hDC, &pt, 1);

	*px = pt.x;
	*py = pt.y;
}

static int CALLBACK EnhMetaFileProc(
  HDC hhDC,                    // handle to device context
  HANDLETABLE FAR *lpHTable,  // pointer to metafile handle table
  ENHMETARECORD FAR *lpEMFR,  // pointer to metafile record
  int nObj,                   // count of objects
  LPVOID lpData               // pointer to optional data
)
{
	CSVGReadEMF* emf = (CSVGReadEMF*)lpData;
	return emf->EnhMetaFileProc(hhDC, lpHTable, lpEMFR, nObj);
}

void CSVGReadEMF::SetShapeStroke(ILSVGElement* frame, LPLOGPEN lp)
{
#if 0
	if (!lp || lp->lopnStyle == PS_NULL)
	{
		//stylable->style->setProperty(L"stroke", L"none", L"");
	}
	else if ((lp->lopnStyle == PS_SOLID) || ((lp->lopnStyle == PS_INSIDEFRAME) && (lp->lopnWidth.x <= 1)))
	{
		CComPtr<IPDObjectStroke> stroke;
		stroke.CoCreateInstance(CLSID_PDObjectStroke);
		CComQIPtr<IPDStrokeSettings> stroke2 = stroke;

		stroke2->put_strokeWeight(lp->lopnWidth.x);

		CComPtr<IPDBrush> brush;
		stroke->get_brush(&brush);

		CComPtr<IPDColor> color;
		brush->setColor(&color);
		color->setRGB(GetRValue(lp->lopnColor), GetGValue(lp->lopnColor), GetBValue(lp->lopnColor));

		frame->appendSubObject(stroke);
	}
	else if (lp->lopnStyle == PS_DASH)
	{
		TRACE("PS_DASH\n");
	}
	else if (lp->lopnStyle == PS_DOT)
	{
		TRACE("PS_DOT\n");
	}
	else if (lp->lopnStyle == PS_DASHDOT)
	{
		TRACE("PS_DASHDOT\n");
	}
	else if (lp->lopnStyle == PS_DASHDOTDOT)
	{
		TRACE("PS_DASHDOTDOT\n");
	}
	else if (lp->lopnStyle == PS_INSIDEFRAME)
	{
		TRACE("PS_INSIDEFRAME\n");
	}
	else
	{
		TRACE("Unknown pen style: %d\n", lp->lopnStyle);

	// TODO
//		m_strokeColor = lp->lopnColor;
//		m_strokeWidth = lp->lopnWidth.x;
	}
#endif
}

void CSVGReadEMF::SetShapeStroke(ILSVGElement* frame, LPEXTLOGPEN elp)
{
	CComQIPtr<ILSVGStylable> stylable = frame;
	if (stylable)
	{
		CComPtr<ILCSSStyleDeclaration> style;
		stylable->get_style(&style);

		if (!elp || elp->elpPenStyle == PS_NULL)
		{
			style->setProperty(L"stroke", L"none", L"");
		}
		else// if ((elp->elpPenStyle/*PS_SOLID*/)/* || ((lp->lopnStyle == PS_INSIDEFRAME) && (lp->lopnWidth.x <= 1))*/)
		{
			WCHAR buf[64];

			swprintf(buf, L"#%2.2X%2.2X%2.2X", GetRValue(elp->elpColor), GetGValue(elp->elpColor), GetBValue(elp->elpColor));
			style->setProperty(L"stroke", buf, L"");

			swprintf(buf, L"%d", elp->elpWidth);
			style->setProperty(L"stroke-width", buf, L"");
		}
		/*
		else if (lp->lopnStyle == PS_DASH)
		{
			TRACE("PS_DASH\n");
		}
		else if (lp->lopnStyle == PS_DOT)
		{
			TRACE("PS_DOT\n");
		}
		else if (lp->lopnStyle == PS_DASHDOT)
		{
			TRACE("PS_DASHDOT\n");
		}
		else if (lp->lopnStyle == PS_DASHDOTDOT)
		{
			TRACE("PS_DASHDOTDOT\n");
		}
		else if (lp->lopnStyle == PS_INSIDEFRAME)
		{
			TRACE("PS_INSIDEFRAME\n");
		}
		else
		{
			TRACE("Unknown pen style: %d\n", lp->lopnStyle);

		// TODO
	//		m_strokeColor = lp->lopnColor;
	//		m_strokeWidth = lp->lopnWidth.x;
		}
		*/
	}
}

void CSVGReadEMF::SetShapeFill(ILSVGElement* frame, LPLOGBRUSH32 lb)
{
	CComQIPtr<ILSVGStylable> stylable = frame;
	if (stylable)
	{
		CComPtr<ILCSSStyleDeclaration> style;
		stylable->get_style(&style);

		if (!lb || lb->lbStyle == BS_NULL)
		{
			style->setProperty(L"fill", L"none", L"");
		}
		else if (lb->lbStyle == BS_SOLID)
		{
			WCHAR buf[64];
			swprintf(buf, L"#%2.2X%2.2X%2.2X", GetRValue(lb->lbColor), GetGValue(lb->lbColor), GetBValue(lb->lbColor));

			style->setProperty(L"fill", buf, L"");
		}
		else if (lb->lbStyle == BS_DIBPATTERN)
		{
			WCHAR buf[64];
			swprintf(buf, L"url(#pat%d)", lb->lbHatch);

			style->setProperty(L"fill", buf, L"");
		}
		else
		{
			ATLTRACE("Unknown brush style: %d\n", lb->lbStyle);
		//	m_fill = TRUE;
	//		m_fillColor = lb->lbColor;
		}
	}
}

int CSVGReadEMF::EnhMetaFileProc(
	  HDC hhDC,                    // handle to device context
	  HANDLETABLE FAR *lpHTable,  // pointer to metafile handle table
	  ENHMETARECORD FAR *lpEMFR,  // pointer to metafile record
	  int nObj                   // count of objects
	)
{
	CComPtr<ILDOMDocument> pddoc;
	m_group->get_ownerDocument(&pddoc);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	pddoc->get_documentElement((ILDOMElement**)&svgsvgElement);	// TODO

	switch (lpEMFR->iType)
	{
// Do nothing for these records
	case EMR_HEADER:
		break;
		
	case EMR_GDICOMMENT:
		break;
		
		// Palette Stuff / Do nothing
	case EMR_CREATEPALETTE:
		{
			//	PEMRCREATEPALETTE pEMR = (PEMRCREATEPALETTE)lpEMFR;
			TRACE("EMR_CREATEPALETTE (unhandled)\n");
		}
		break;
		
	case EMR_SELECTPALETTE:
		{
			//	PEMRSELECTPALETTE pEMR = (PEMRSELECTPALETTE)lpEMFR;
			TRACE("EMR_SELECTPALETTE (unhandled)\n");
		}
		break;
		
	case EMR_REALIZEPALETTE:
		{
			//	PEMRREALIZEPALETTE pEMR = (PEMRREALIZEPALETTE)lpEMFR;
				TRACE("EMR_REALIZEPALETTE (unhandled)\n");
		}
		break;
		
		// Mapping mode and coordinate translations
	case EMR_SETMAPMODE:
		{
			TRACE("EMR_SETMAPMODE:\n");

			PEMRSETMAPMODE	pEMR = (PEMRSETMAPMODE)lpEMFR;
			
			::SetMapMode(hDC, pEMR->iMode);
		}
		break;
		
	case EMR_SETVIEWPORTEXTEX:
		{
			TRACE("EMR_SETVIEWPORTEXTEX:\n");

			PEMRSETVIEWPORTEXTEX pEMR = (PEMRSETVIEWPORTEXTEX)lpEMFR;
			::SetViewportExtEx(hDC, pEMR->szlExtent.cx, pEMR->szlExtent.cy, NULL);
		}
		break;
		
	case EMR_SETWINDOWEXTEX:
		{
			TRACE("EMR_SETWINDOWEXTEX:\n");

			PEMRSETWINDOWEXTEX pEMR = (PEMRSETWINDOWEXTEX)lpEMFR;
			::SetWindowExtEx(hDC, pEMR->szlExtent.cx, pEMR->szlExtent.cy, NULL);
		}
		break;
		
	case EMR_SETVIEWPORTORGEX:
		{
			TRACE("EMR_SETVIEWPORTORGEX:\n");

			PEMRSETVIEWPORTORGEX pEMR = (PEMRSETVIEWPORTORGEX)lpEMFR;
			::SetViewportOrgEx(hDC, pEMR->ptlOrigin.x, pEMR->ptlOrigin.y, NULL);
		}
		break;
		
	case EMR_SETWINDOWORGEX:
		{
			TRACE("EMR_SETWINDOWORGEX:\n");
			PEMRSETWINDOWORGEX pEMR = (PEMRSETWINDOWORGEX)lpEMFR;
			::SetWindowOrgEx(hDC, pEMR->ptlOrigin.x, pEMR->ptlOrigin.y, NULL);
		}
		break;
		
	case EMR_SCALEVIEWPORTEXTEX:
		{
			TRACE("EMR_SCALEVIEWPORTEXTEX:\n");
			PEMRSCALEVIEWPORTEXTEX pEMR = (PEMRSCALEVIEWPORTEXTEX)lpEMFR;
			::ScaleViewportExtEx(hDC, pEMR->xNum, pEMR->xDenom, pEMR->yNum, pEMR->yDenom, NULL);
		}
		break;
		
	case EMR_SCALEWINDOWEXTEX:
		{
			TRACE("EMR_SCALEWINDOWEXTEX:\n");
			PEMRSCALEWINDOWEXTEX pEMR = (PEMRSCALEWINDOWEXTEX)lpEMFR;
			::ScaleWindowExtEx(hDC, pEMR->xNum, pEMR->xDenom, pEMR->yNum, pEMR->yDenom, NULL);
		}
		break;
		
		// GDI Objects
	case EMR_SELECTOBJECT:
		{
			TRACE("EMR_SELECTOBJECT ");
			PEMRSELECTOBJECT pEMR = (PEMRSELECTOBJECT)lpEMFR;
			
			CGdiObj* pObj = NULL;
			if (pEMR->ihObject & ENHMETA_STOCK_OBJECT)
			{
				int n = pEMR->ihObject & ~ENHMETA_STOCK_OBJECT;
				if (n >= 0 && n <= STOCK_LAST)
				{
					pObj = m_stockObjects[n];
				}
				//::SelectObject(hDC, ::GetStockObject(pEMR->ihObject & ~ENHMETA_STOCK_OBJECT));
			}
			else if (hTable[pEMR->ihObject])
			{
				ATLTRACE("ihObject: %d", pEMR->ihObject);
				pObj = hTable[pEMR->ihObject];
				//::SelectObject(hDC, hTable[pEMR->ihObject]);
			}

			if (pObj)
			{
				if (pObj->m_type == OBJ_BRUSH)
					m_pCurrentBrush = (CGdiBrush*)pObj;
				else if (pObj->m_type == OBJ_PEN)
					m_pCurrentPen = (CGdiPen*)pObj;
			}

			ATLTRACE("\n");
		}
		break;
		
	case EMR_DELETEOBJECT:
		{
			PEMRDELETEOBJECT pEMR = (PEMRDELETEOBJECT)lpEMFR;

			ATLTRACE("EMR_DELETEOBJECT ihObject:\n", pEMR->ihObject);
			
			if (hTable[pEMR->ihObject])
			{
				delete hTable[pEMR->ihObject];
				//::DeleteObject(hTable[pEMR->ihObject]);
				hTable[pEMR->ihObject] = NULL;
			}
		}
		break;
		
	case EMR_CREATEPEN:
		{
			TRACE("EMR_CREATEPEN\n");

			PEMRCREATEPEN pEMR = (PEMRCREATEPEN)lpEMFR;
			/*
			
			HPEN hPen = ::CreatePenIndirect(&pEMR->lopn);
			hTable[pEMR->ihPen] = hPen;
			*/

			CGdiPen* pPen = new CGdiPen;
			pPen->m_elp.elpColor = pEMR->lopn.lopnColor;
			pPen->m_elp.elpWidth = pEMR->lopn.lopnWidth.x;
			pPen->m_elp.elpPenStyle = pEMR->lopn.lopnStyle;
			hTable[pEMR->ihPen] = pPen;
		}
		break;

	case EMR_EXTCREATEPEN:
		{
			TRACE("EMR_EXTCREATEPEN\n");

			PEMREXTCREATEPEN pEMR = (PEMREXTCREATEPEN)lpEMFR;
			
			//PS_USERSTYLE
#if 0
			LOGBRUSH lb;
			lb.lbColor = pEMR->elp.elpColor;
			lb.lbHatch = 0;
			lb.lbStyle = BS_SOLID;
			HPEN hPen = ::ExtCreatePen(/*PS_SOLID | PS_GEOMETRIC*/pEMR->elp.elpPenStyle, pEMR->elp.elpWidth, &lb, pEMR->elp.elpNumEntries, NULL/*pEMR->elp.elpStyleEntry*/);
			ASSERT(hPen);
			hTable[pEMR->ihPen] = hPen;
#endif
			CGdiPen* pPen = new CGdiPen;
			pPen->m_elp = pEMR->elp;
			hTable[pEMR->ihPen] = pPen;
		}
		break;
		
	case EMR_CREATEBRUSHINDIRECT:
		{
			ATLTRACE("EMR_CREATEBRUSHINDIRECT\n");

			PEMRCREATEBRUSHINDIRECT pEMR = (PEMRCREATEBRUSHINDIRECT)lpEMFR;
			
			//HBRUSH hBrush = ::CreateBrushIndirect((LOGBRUSH*)&pEMR->lb);
			//hTable[pEMR->ihBrush] = hBrush;
			CGdiBrush* pBrush = new CGdiBrush;
			pBrush->m_lb = pEMR->lb;

			hTable[pEMR->ihBrush] = pBrush;
		}
		break;

	case EMR_CREATEDIBPATTERNBRUSHPT:
		{
			ATLTRACE("EMR_CREATEDIBPATTERNBRUSHPT\n");

			PEMRCREATEDIBPATTERNBRUSHPT pEMR = (PEMRCREATEDIBPATTERNBRUSHPT)lpEMFR;

			LPBITMAPINFO pbmi = (LPBITMAPINFO)((BYTE*)pEMR + pEMR->offBmi);
			BYTE* bits = ((BYTE*)pEMR + pEMR->offBits);

			CComPtr<ILSVGImageElement> imageElement;
			pddoc->createElement(L"image", (ILDOMElement**)&imageElement);
			if (imageElement)
			{
				{
					CComPtr<ILSVGAnimatedLength> a;
					imageElement->get_x(&a);

					CComPtr<ILSVGLength> x;
					a->get_baseVal(&x);

					x->put_value(0);
				}

				{
					CComPtr<ILSVGAnimatedLength> a;
					imageElement->get_y(&a);

					CComPtr<ILSVGLength> y;
					a->get_baseVal(&y);

					y->put_value(0);
				}

				{
					CComPtr<ILSVGAnimatedLength> a;
					imageElement->get_width(&a);

					CComPtr<ILSVGLength> width;
					a->get_baseVal(&width);

					width->put_value(pbmi->bmiHeader.biWidth);
				}

				{
					CComPtr<ILSVGAnimatedLength> a;
					imageElement->get_height(&a);

					CComPtr<ILSVGLength> height;
					a->get_baseVal(&height);

					height->put_value(pbmi->bmiHeader.biHeight);
				}

			// xlink:href

				_bstr_t mimeType = L"image/png";	// Should be able to set this in preferences

				_bstr_t buf;
				buf = L"data:" + mimeType + L";base64,";

				Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(pbmi, bits);

				if (pBitmap->GetLastStatus() == Gdiplus::Ok)
				{
					HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, 0);

					CComPtr<IStream> pstm;
					if (SUCCEEDED(CreateStreamOnHGlobal(hData, FALSE, &pstm)))
					{
						CLSID imgClsid;
						GetEncoderClsid(mimeType, &imgClsid);

						if (pBitmap->Save(pstm, &imgClsid) == Gdiplus::Ok)
						{
							BYTE* pData = (BYTE*)GlobalLock(hData);
							if (pData)
							{
								// Get size of stream
								LARGE_INTEGER li0;
								li0.QuadPart = 0;

								ULARGE_INTEGER lipos;
								pstm->Seek(li0, STREAM_SEEK_END, &lipos);

								CComBSTR encodedString;
								EncodeBase64(pData, (int)lipos.QuadPart, &encodedString);

								buf += (BSTR)encodedString;

								GlobalUnlock(pData);
							}
						}
					}

					GlobalFree(hData);
				}

				delete pBitmap;

				imageElement->setAttributeNS(L"http://www.w3.org/1999/xlink", L"href", buf);

				CComPtr<ILSVGPatternElement> patternElement;
				pddoc->createElement(L"pattern", (ILDOMElement**)&patternElement);
				if (patternElement)
				{
					WCHAR patternId[16];
					swprintf(patternId, L"pat%d", pEMR->ihBrush);
					patternElement->setAttribute(L"id", patternId);

					patternElement->appendChild(imageElement, NULL);

					m_group->appendChild(patternElement, NULL);
				}
			}

			CGdiBrush* pBrush = new CGdiBrush;
			pBrush->m_lb.lbStyle = BS_DIBPATTERN;
			pBrush->m_lb.lbHatch = pEMR->ihBrush;

			hTable[pEMR->ihBrush] = pBrush;
		}
		break;

	case EMR_EXTCREATEFONTINDIRECTW:
		{
			TRACE("EMR_EXTCREATEFONTINDIRECTW\n");

		/*
			PEMREXTCREATEFONTINDIRECTW pEMR = (PEMREXTCREATEFONTINDIRECTW)lpEMFR;
			
			HFONT hFont = ::CreateFontIndirect((LPLOGFONT)&pEMR->elfw);
			hTable[pEMR->ihFont] = hFont;
			*/
		}
		break;
		
		// Transformations
	case EMR_SETWORLDTRANSFORM:	// TODO
		{
			TRACE("EMR_SETWORLDTRANSFORM (unhandled)\n");
		}
		break;
		
	case EMR_MODIFYWORLDTRANSFORM:	// TODO
		{
			TRACE("EMR_MODIFYWORLDTRANSFORM (unhandled)\n");
		}
		break;
		
		// Regions
	case EMR_INTERSECTCLIPRECT:
		{
			TRACE("EMR_INTERSECTCLIPRECT (unhandled)\n");
		}
		break;
		
	case EMR_EXTSELECTCLIPRGN:
		{
			PEMREXTSELECTCLIPRGN pEMR = (PEMREXTSELECTCLIPRGN)lpEMFR;
			TRACE("EMR_EXTSELECTCLIPRGN (unhandled)\n");
		}
		break;
		
		// DC State
	case EMR_SAVEDC:
		{
			TRACE("EMR_SAVEDC\n");

			PEMRSAVEDC pEMR = (PEMRSAVEDC)lpEMFR;
			::SaveDC(hDC);
		}
		break;
		
	case EMR_RESTOREDC:
		{
			TRACE("EMR_RESTOREDC\n");

			PEMRRESTOREDC pEMR = (PEMRRESTOREDC)lpEMFR;
			
			if (pEMR->iRelative > 0)
			{
				//	AfxMessageBox("restoredc is positive!!");
				pEMR->iRelative = -pEMR->iRelative;
			}
			
			::RestoreDC(hDC, pEMR->iRelative);
		}
		break;
		
		// GDI Modes
	case EMR_SETTEXTCOLOR:
		{
			TRACE("EMR_SETTEXTCOLOR\n");

			PEMRSETTEXTCOLOR pEMR = (PEMRSETTEXTCOLOR)lpEMFR;
			::SetTextColor(hDC, pEMR->crColor);
		}
		break;
		
	case EMR_SETBKCOLOR:
		{
			TRACE("EMR_SETBKCOLOR\n");

			PEMRSETBKCOLOR pEMR = (PEMRSETBKCOLOR)lpEMFR;
			::SetBkColor(hDC, pEMR->crColor);
		}
		break;
		
	case EMR_SETBKMODE:
		{
			TRACE("EMR_SETBKMODE\n");

			PEMRSETBKMODE pEMR = (PEMRSETBKMODE)lpEMFR;
			::SetBkMode(hDC, pEMR->iMode);
		}
		break;
		
	case EMR_SETPOLYFILLMODE:
		{
			TRACE("EMR_SETPOLYFILLMODE\n");

			PEMRSETPOLYFILLMODE pEMR = (PEMRSETPOLYFILLMODE)lpEMFR;
			::SetPolyFillMode(hDC, pEMR->iMode);
		}
		break;
		
	case EMR_SETROP2:
		{
			TRACE("EMR_SETROP2\n");

			PEMRSETROP2	pEMR = (PEMRSETROP2)lpEMFR;
			::SetROP2(hDC, pEMR->iMode);
		}
		break;
		
	case EMR_SETMAPPERFLAGS:
		{
			TRACE("EMR_SETMAPPERFLAGS\n");

			PEMRSETMAPPERFLAGS pEMR = (PEMRSETMAPPERFLAGS)lpEMFR;
			::SetMapperFlags(hDC, pEMR->dwFlags);
		}
		break;
		
	case EMR_MOVETOEX:
		{
			ATLTRACE("EMR_MOVETOEX\n");

			PEMRMOVETOEX pEMR = (PEMRMOVETOEX)lpEMFR;

			::MoveToEx(hDC, pEMR->ptl.x, pEMR->ptl.y, NULL);

			/*
			m_startPt.x = pEMR->ptl.x;
			m_startPt.y = pEMR->ptl.y;
			*/

			PointD pt;
			LPToDP(hDC, pEMR->ptl.x, pEMR->ptl.y, &pt.X, &pt.Y);
			ConvertPt(&pt.X, &pt.Y);

			if (m_curFrame)
			{
				CComPtr<ILSVGPathSegMovetoAbs> seg;
				m_curFrame->createSVGPathSegMovetoAbs(pt.X, pt.Y, &seg);

				m_curPath->appendItem(seg, NULL);
			}
			else
			{
			}

			/*
			SVGLib::ISVGPathSegMovetoAbsPtr moveto = path->createSVGPathSegMovetoAbs(pt.x, pt.y);
			pathData->pathSegList->appendItem(moveto);
			*/

			/*
			if (m_curPath)
			{
				CComQIPtr<ILSVGPathSegMovetoAbs> seg;

			}
			*/

		}
		break;
		
	case EMR_SETMITERLIMIT:
		{
			TRACE("EMR_SETMITERLIMIT\n");

			PEMRSETMITERLIMIT pEMR = (PEMRSETMITERLIMIT)lpEMFR;
			::SetMiterLimit(hDC, pEMR->eMiterLimit, NULL);
		}
		break;

		case EMR_BEGINPATH:
			{
				ATLTRACE("EMR_BEGINPATH\n");

				if (m_curFrame == NULL)
				{
					pddoc->createElement(L"path", (ILDOMElement**)&m_curFrame);
					CComQIPtr<ILSVGAnimatedPathData> pathData = m_curFrame;

					pathData->get_normalizedPathSegList(&m_curPath);

					//m_group->appendChild(m_curFrame, NULL);
				}
			}
			break;

		case EMR_STROKEPATH:
			{
				TRACE("EMR_STROKEPATH\n");

				if (m_curFrame)
				{
					SetShapeStroke(m_curFrame, &m_pCurrentPen->m_elp);

					m_group->appendChild(m_curFrame, NULL);

					//m_curSubPath.Release();
					m_curPath.Release();
					m_curFrame.Release();
				}
			}
			break;

//#define EMR_ENDPATH                     60

		case EMR_FILLPATH:
			{
				ATLTRACE("EMR_FILLPATH\n");

				if (m_curFrame)
				{
					SetShapeFill(m_curFrame, &m_pCurrentBrush->m_lb);
					SetShapeStroke(m_curFrame, (LPEXTLOGPEN)NULL);

					m_group->appendChild(m_curFrame, NULL);

					//m_curSubPath.Release();
					m_curPath.Release();
					m_curFrame.Release();
				}
			}
			break;

		case EMR_STROKEANDFILLPATH:
			{
				ATLTRACE("EMR_STROKEANDFILLPATH\n");

				if (m_curFrame)
				{
					SetShapeFill(m_curFrame, &m_pCurrentBrush->m_lb);
					SetShapeStroke(m_curFrame, &m_pCurrentPen->m_elp);

					m_group->appendChild(m_curFrame, NULL);

					//m_curSubPath.Release();
					m_curPath.Release();
					m_curFrame.Release();
				}
			}
			break;

// Geometric shapes
		case EMR_LINETO:
		{
			ATLTRACE("EMR_LINETO\n");

			PEMRLINETO pEMR = (PEMRLINETO)lpEMFR;

			PointD pt;
			LPToDP(hDC, pEMR->ptl.x, pEMR->ptl.y, &pt.X, &pt.Y);
			ConvertPt(&pt.X, &pt.Y);

			if (m_curFrame)
			{
				CComPtr<ILSVGPathSegLinetoAbs> seg;
				m_curFrame->createSVGPathSegLinetoAbs(pt.X, pt.Y, &seg);

				m_curPath->appendItem(seg, NULL);
			}
			else
			{
			}

#if 0
			if (m_curSubPath)
			{
				BezierPoint bpt;

				LPToDP(hDC, pEMR->ptl.x, pEMR->ptl.y, &bpt.x, &bpt.y);
				ConvertPt(&bpt.x, &bpt.y);
				bpt.x1 = bpt.x;
				bpt.y1 = bpt.y;
				bpt.x2 = bpt.x;
				bpt.y2 = bpt.y;

				long index;
				m_curSubPath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);
			}
#endif

			MoveToEx(hDC, pEMR->ptl.x, pEMR->ptl.y, NULL);
		}
		break;

		case EMR_POLYGON16:
		case EMR_POLYLINE16:
			{
				PEMRPOLYGON16	pEMR = (PEMRPOLYGON16)lpEMFR;

				CComQIPtr<ILSVGElement> element;

				if (lpEMFR->iType == EMR_POLYGON16)
					ATLTRACE("POLYGON16\n");
				else
					ATLTRACE("POLYLINE16\n");

			// TODO, maybe it's inside a path ?
				if (lpEMFR->iType == EMR_POLYGON16)
				{
					pddoc->createElement(L"polygon", (ILDOMElement**)&element);
				}
				else
				{
					pddoc->createElement(L"polyline", (ILDOMElement**)&element);
				}

				CComQIPtr<ILSVGAnimatedPoints> a = element;

				CComQIPtr<ILSVGPointList> points;
				a->get_points(&points);

				for (int i = 0; i < pEMR->cpts; i++)
				{
					POINT	pt;
					pt.x = pEMR->apts[i].x;
					pt.y = pEMR->apts[i].y;

					PointD bpt;
					LPToDP(hDC, pt.x, pt.y, &bpt.X, &bpt.Y);
					ConvertPt(&bpt.X, &bpt.Y);

					CComPtr<ILSVGPoint> svgPoint;
					svgsvgElement->createSVGPoint(&svgPoint);
					svgPoint->put_x(bpt.X);
					svgPoint->put_y(bpt.Y);

					points->appendItem(svgPoint, NULL);
				}

				if (lpEMFR->iType == EMR_POLYGON16)
				{
					SetShapeFill(element, &m_pCurrentBrush->m_lb);
					SetShapeStroke(element, &m_pCurrentPen->m_elp);
				}
				else
				{
					SetShapeStroke(element, &m_pCurrentPen->m_elp);
				}

				m_group->appendChild(element, NULL);

#if 0
				BOOL bInPath;

				if (m_curFrame == NULL)
				{
					bInPath = FALSE;

					pddoc->createElement(L"path", &m_curFrame);

					CComQIPtr<ILSVGAnimatedPathData> pathData = m_curFrame;
					pathData->get_normalizedPathSegList(&m_curPath);

					/*
					m_curPath->createSubPath(&m_curSubPath);
					m_curPath->insertSubPath(-1, m_curSubPath);
					*/

					if (lpEMFR->iType == EMR_POLYGON16)
					{
						/*
						if (fillMode == WINDING)
							;//pLayer->m_fillType = 0;
						else if (fillMode == ALTERNATE)
							;//pLayer->m_fillType = 1;
						else
							ASSERT(0);
							*/

#if 0
						m_curSubPath->put_closed(VARIANT_TRUE);
#endif

						SetShapeFill(m_curFrame, &m_pCurrentBrush->m_lb);
						SetShapeStroke(m_curFrame, &m_pCurrentPen->m_elp);
					}
					else
					{
						SetShapeStroke(m_curFrame, &m_pCurrentPen->m_elp);
					}
				}
				else
					bInPath = TRUE;

				for (int i = 0; i < pEMR->cpts; i++)
				{
					POINT	pt;
					pt.x = pEMR->apts[i].x;
					pt.y = pEMR->apts[i].y;

					BezierPoint bpt;
					LPToDP(hDC, pt.x, pt.y, &bpt.x, &bpt.y);
					ConvertPt(&bpt.x, &bpt.y);

					bpt.x1 = bpt.x;
					bpt.y1 = bpt.y;
					bpt.x2 = bpt.x;
					bpt.y2 = bpt.y;

					CComPtr<ILSVGPathSegLinetoAbs> seg;
					m_curFrame->createSVGPathSegLinetoAbs(&seg);
					long index;
					m_curSubPath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);
				}

				if (!bInPath)
				{
					m_group->appendChild(m_curFrame, NULL);

					//m_curSubPath.Release();
					m_curPath.Release();
					m_curFrame.Release();
				}
#endif
			}
			break;

		case EMR_POLYPOLYGON16:
		case EMR_POLYPOLYLINE16:
			{
				TRACE("POLYPOLYGON16/POLYPOLYLINE16 (unhandled)\n");
			}
			break;
			
		case EMR_RECTANGLE:
		case EMR_ELLIPSE:
			{
				TRACE("RECTANGLE/ELLIPSE\n");

				PEMRRECTANGLE	pEMR = (PEMRRECTANGLE)lpEMFR;

				RectD r;
				LPToDP(hDC, pEMR->rclBox.left, pEMR->rclBox.top, &r.X, &r.Y);
				LPToDP(hDC, pEMR->rclBox.right, pEMR->rclBox.bottom, &r.Width, &r.Height);
				r.Width -= r.X;
				r.Height -= r.Y;

				CComPtr<ILSVGElement> element;

				if (lpEMFR->iType == EMR_RECTANGLE)
				{
					/*
					SVGLib::ISVGRectElementPtr rect = pDoc->GetDOMDocument()->createElement(L"rect");
					rect->x->baseVal->value = r.left;
					rect->y->baseVal->value = r.top;
					rect->width->baseVal->value = r.Width();
					rect->height->baseVal->value = r.Height();

					element = rect;
					*/
				}
				else if (lpEMFR->iType == EMR_ELLIPSE)
				{
					CComPtr<ILSVGEllipseElement> ellipse;
					pddoc->createElement(L"ellipse", (ILDOMElement**)&ellipse);

					{
						CComPtr<ILSVGAnimatedLength> a;
						ellipse->get_cx(&a);
						CComPtr<ILSVGLength> cx;
						a->get_baseVal(&cx);
						cx->put_value(r.X + r.Width/2);
					}

					{
						CComPtr<ILSVGAnimatedLength> a;
						ellipse->get_cy(&a);
						CComPtr<ILSVGLength> cy;
						a->get_baseVal(&cy);
						cy->put_value(r.Y + r.Height/2);
					}

					{
						CComPtr<ILSVGAnimatedLength> a;
						ellipse->get_rx(&a);
						CComPtr<ILSVGLength> rx;
						a->get_baseVal(&rx);
						rx->put_value(r.Width/2);
					}

					{
						CComPtr<ILSVGAnimatedLength> a;
						ellipse->get_ry(&a);
						CComPtr<ILSVGLength> ry;
						a->get_baseVal(&ry);
						ry->put_value(r.Height/2);
					}

					element = ellipse;
				}

				m_group->appendChild(element, NULL);
				//SetShapeStrokeFill(element, &lp, &lb);
			}
			break;

#if 0
		{
			CComPtr<IPDObjectFrame> element;

			HPEN hPen = (HPEN)::GetCurrentObject(hDC, OBJ_PEN);
			HBRUSH hBrush = (HBRUSH)::GetCurrentObject(hDC, OBJ_BRUSH);

			LOGPEN	lp;
			::GetObject(hPen, sizeof(lp), &lp);

			LOGBRUSH	lb;
			::GetObject(hBrush, sizeof(lb), &lb);

			int fillMode = ::GetPolyFillMode(hDC);

			switch (lpEMFR->iType)
			{
				case EMR_POLYGON16:
				case EMR_POLYLINE16:
				{
					TRACE("POLYGON16/POLYLINE16\n");

					/*
					PEMRPOLYGON16	pEMR = (PEMRPOLYGON16)lpEMFR;

					pddoc->createObjectFrame(&element);

					CComPtr<IPDPath> pathData;
					element->get_path(&pathData);

					if (lpEMFR->iType == EMR_POLYGON16)
					{
					//	pLayer->m_name.Format("Polygon");

						if (fillMode == WINDING)
							;//pLayer->m_fillType = 0;
						else if (fillMode == ALTERNATE)
							;//pLayer->m_fillType = 1;
						else
							ASSERT(0);
					}
					else
					{
					//	pLayer->m_name.Format("Polyline");
					}

					SetShapeStrokeFill(path, &lp, (EMR_POLYGON16)? &lb: NULL);

					int j = 0;
					for (DWORD i = 0; i < pEMR->cpts; i++)
					{
						POINT	pt;
						pt.x = pEMR->apts[i].x;
						pt.y = pEMR->apts[i].y;

						::LPtoDP(hDC, &pt, 1);

						if (i == 0)
						{
							SVGLib::ISVGPathSegMovetoAbsPtr moveto = path->createSVGPathSegMovetoAbs(pt.x, pt.y);
							pathData->pathSegList->appendItem(moveto);
						}
						else
						{
							SVGLib::ISVGPathSegLinetoAbsPtr lineto = path->createSVGPathSegLinetoAbs(pt.x, pt.y);
							pathData->pathSegList->appendItem(lineto);
						}
					}

					element = path;
					*/
				}
				break;

				case EMR_POLYPOLYGON16:
				case EMR_POLYPOLYLINE16:
				{
					TRACE("POLYPOLYGON16/POLYPOLYLINE16 (unhandled)\n");

					/*
					PEMRPOLYPOLYGON16 pEMR = (PEMRPOLYPOLYGON16)lpEMFR;

					POINTS* apts = (POINTS*)(((LPBYTE)pEMR->apts) + (pEMR->nPolys-1)*4);

					SVGLib::ISVGPathElementPtr path = pDoc->GetDOMDocument()->createElement(L"path");
					SVGLib::ISVGAnimatedPathDataPtr pathData = path;

					for (DWORD nPoly = 0; nPoly < pEMR->nPolys; nPoly++)
					{
					//	pLayer->SetShapeStrokeFill(&lp, (lpEMFR->iType == EMR_POLYPOLYGON16) ? &lb: NULL);

						if (lpEMFR->iType == EMR_POLYPOLYGON16)
						{
							if (fillMode == WINDING)
								;//pLayer->m_fillType = 0;
							else// if (fillMode == ALTERNATE)
								;//pLayer->m_fillType = 1;
						}
						else
						{
						}

						int j = 0;

						for (DWORD i = 0; i < pEMR->aPolyCounts[nPoly]; i++)
						{
							POINT	pt;
							pt.x = apts->x;
							pt.y = apts->y;
							apts++;

							::LPtoDP(hDC, &pt, 1);

							if (i == 0)
							{
								SVGLib::ISVGPathSegMovetoAbsPtr moveto = path->createSVGPathSegMovetoAbs(pt.x, pt.y);
								pathData->pathSegList->appendItem(moveto);
							}
							else
							{
								SVGLib::ISVGPathSegLinetoAbsPtr lineto = path->createSVGPathSegLinetoAbs(pt.x, pt.y);
								pathData->pathSegList->appendItem(lineto);
							}
						}
					}

					element = path;
					*/
				}
				break;

			}

			if (element)
			{
				m_group->appendObject(element);
			}
		}
		break;
#endif

		case EMR_POLYBEZIER16:
			{
				TRACE("EMR_POLYBEZIER16: (unhandled)\n");
			}
			break;

		case EMR_POLYBEZIERTO16:
			{
				ATLTRACE("EMR_POLYBEZIERTO16:\n");
				
				PEMRPOLYBEZIERTO16 pEMR = (PEMRPOLYBEZIERTO16)lpEMFR;
				
				POINT pt;
				GetCurrentPositionEx(hDC, &pt);
				
				//BezierPoint bpt;
				
				/*
				if (m_curSubPath == NULL)
				{
					m_curPath->createSubPath(&m_curSubPath);
					m_curPath->insertSubPath(-1, m_curSubPath);
				}
				*/

				/*
				LPToDP(hDC, pt.x, pt.y, &bpt.x, &bpt.y);
				ConvertPt(&bpt.x, &bpt.y);

				bpt.x1 = bpt.x;
				bpt.y1 = bpt.y;
				*/
				
				ASSERT((pEMR->cpts % 3) == 0);
				
				for (int i = 0; i < pEMR->cpts; i += 3)
				{
					PointD pts[3];

					LPToDP(hDC, pEMR->apts[i].x, pEMR->apts[i].y, &pts[0].X, &pts[0].Y);
					ConvertPt(&pts[0].X, &pts[0].Y);

					LPToDP(hDC, pEMR->apts[i+1].x, pEMR->apts[i+1].y, &pts[1].X, &pts[1].Y);
					ConvertPt(&pts[1].X, &pts[1].Y);

					LPToDP(hDC, pEMR->apts[i+2].x, pEMR->apts[i+2].y, &pts[2].X, &pts[2].Y);
					ConvertPt(&pts[2].X, &pts[2].Y);
					
					//CComQIPtr<ILSVGAnimatedPathData> pathData = m_curFrame;
					CComPtr<ILSVGPathSegCurvetoCubicAbs> seg;
					m_curFrame->createSVGPathSegCurvetoCubicAbs(pts[2].X, pts[2].Y, pts[0].X, pts[0].Y, pts[1].X, pts[1].Y, &seg);

					m_curPath->appendItem(seg, NULL);
				}

				/*
				bpt.x2 = bpt.x;
				bpt.y2 = bpt.y;
				
				long index;
				m_curSubPath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);
				*/
				
				MoveToEx(hDC, pEMR->apts[i-1].x, pEMR->apts[i-1].y, NULL);
			}
			break;

		case EMR_CLOSEFIGURE:
			{
				ATLTRACE("EMR_CLOSEFIGURE:\n");

				if (m_curPath)
				{
					CComPtr<ILSVGPathSegClosePath> seg;
					m_curFrame->createSVGPathSegClosePath(&seg);

					m_curPath->appendItem(seg, NULL);
				}
#if 0
				if (m_curSubPath)
				{
					m_curSubPath->put_closed(VARIANT_TRUE);
					m_curSubPath.Release();

					/*	Have this ?????
					BezierPoint bpt;

					LPToDP(hDC, m_startPt.x, m_startPt.y, &bpt.x, &bpt.y);
					ConvertPt(&bpt.x, &bpt.y);
					bpt.x1 = bpt.x;
					bpt.y1 = bpt.y;
					bpt.x2 = bpt.x;
					bpt.y2 = bpt.y;

					long index;
					m_curSubPath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);
					*/
				}
#endif
			}
			break;

		case EMR_ROUNDRECT:	// TODO
			{
				TRACE("EMR_ROUNDRECT: (unhandled)\n");
			}
			break;
			
		case EMR_ARC:	// TODO
			{
				TRACE("EMR_ARC: (unhandled)\n");
			}
			break;
			
		case EMR_PIE:	// TODO
			{
				TRACE("EMR_PIE: (unhandled)\n");
			}
			break;
			
		case EMR_CHORD:	// TODO
			{
				TRACE("EMR_CHORD: (unhandled)\n");
			}
			break;
			
		case EMR_ANGLEARC:	// TODO
			{
				TRACE("EMR_ANGLEARC: (unhandled)\n");
			}
			break;
			
		case EMR_ARCTO:
			{
				TRACE("EMR_ARCTO: (unhandled)\n");
			}
			break;

		///////////////////////////////////////////////////////
		// Bitmap Stuff

		case EMR_STRETCHDIBITS:
			{
				ATLTRACE("EMR_STRETCHDIBITS\n");

				PEMRSTRETCHDIBITS pEMR = (PEMRSTRETCHDIBITS)lpEMFR;

				LPBITMAPINFO pbmi = (LPBITMAPINFO)((BYTE*)pEMR + pEMR->offBmiSrc);
				BYTE* bits = ((BYTE*)pEMR + pEMR->offBitsSrc);

				CComPtr<ILSVGImageElement> element;
				pddoc->createElement(L"image", (ILDOMElement**)&element);
				if (element)
				{
					{
						CComPtr<ILSVGAnimatedLength> a;
						element->get_x(&a);

						CComPtr<ILSVGLength> x;
						a->get_baseVal(&x);

						x->put_value(pEMR->xDest);
					}

					{
						CComPtr<ILSVGAnimatedLength> a;
						element->get_y(&a);

						CComPtr<ILSVGLength> y;
						a->get_baseVal(&y);

						y->put_value(pEMR->yDest);
					}

					{
						CComPtr<ILSVGAnimatedLength> a;
						element->get_width(&a);

						CComPtr<ILSVGLength> width;
						a->get_baseVal(&width);

						width->put_value(pEMR->cxDest);
					}

					{
						CComPtr<ILSVGAnimatedLength> a;
						element->get_height(&a);

						CComPtr<ILSVGLength> height;
						a->get_baseVal(&height);

						height->put_value(pEMR->cyDest);
					}

				// xlink:href

					_bstr_t mimeType = L"image/png";	// Should be able to set this in preferences

					_bstr_t buf;
					buf = L"data:" + mimeType + L";base64,";

					Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(pbmi, bits);

					if (pBitmap->GetLastStatus() == Gdiplus::Ok)
					{
						HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, 0);

						CComPtr<IStream> pstm;
						if (SUCCEEDED(CreateStreamOnHGlobal(hData, FALSE, &pstm)))
						{
							CLSID imgClsid;
							GetEncoderClsid(mimeType, &imgClsid);

							if (pBitmap->Save(pstm, &imgClsid) == Gdiplus::Ok)
							{
								BYTE* pData = (BYTE*)GlobalLock(hData);
								if (pData)
								{
									// Get size of stream
									LARGE_INTEGER li0;
									li0.QuadPart = 0;

									ULARGE_INTEGER lipos;
									pstm->Seek(li0, STREAM_SEEK_END, &lipos);

									CComBSTR encodedString;
									EncodeBase64(pData, (int)lipos.QuadPart, &encodedString);

									buf += (BSTR)encodedString;

									GlobalUnlock(pData);
								}
							}
						}

						GlobalFree(hData);
					}

					delete pBitmap;

					element->setAttributeNS(L"http://www.w3.org/1999/xlink", L"href", buf);

					m_group->appendChild(element, NULL);
				}
			}
			break;

		case EMR_BITBLT:	// TODO
			{
				PEMRBITBLT pEMR = (PEMRBITBLT)lpEMFR;
				
				//	pEMR->
				TRACE("EMR_BITBLT: (unhandled)\n");
			}
			break;
			
		
		case EMR_STRETCHBLT:	// TODO
			{
				TRACE("EMR_STRETCHBLT: (unhandled)\n");
			}
			break;
			
		case EMR_SETDIBITSTODEVICE:	// TODO
			{
				TRACE("EMR_SETDIBITSTODEVICE: (unhandled)\n");
			}
			break;
			
		case EMR_MASKBLT:
			{
				TRACE("EMR_MASKBLT: (unhandled)\n");
			}
			break;
			
		case EMR_PLGBLT:
			{
				TRACE("EMR_PLGBLT: (unhandled)\n");
			}
			break;
			
		case EMR_ALPHABLEND:	// TODO
			{
				TRACE("EMR_ALPHABLEND: (unhandled)\n");
			}
			break;
			
		case 115: //EMR_ALPHADIBBLEND:	// TODO
			{
				TRACE("EMR_ALPHADIBBLEND: (unhandled)\n");
			}
			break;
			
		case EMR_TRANSPARENTBLT:
			{
				TRACE("EMR_TRANSPARENTBLT: (unhandled)\n");
			}
			break;
			
		case 117: //EMR_TRANSPARENTDIB:
			{
				TRACE("EMR_TRANSPARENTDIB: (unhandled)\n");
			}
			break;
			
		case 118: //EMR_GRADIENTFILL:
			{
				TRACE("EMR_GRADIENTFILL: (unhandled)\n");
			}
			break;

		case EMR_SETPIXELV:
			{
				TRACE("EMR_SETPIXELV: (unhandled)\n");
			}
			break;

			// Text Stuff
		case EMR_EXTTEXTOUTA:	// TODO
		case EMR_EXTTEXTOUTW:
			{
				TRACE("EMR_EXTTEXTOUT: (unhandled)\n");
			}
			break;
			
		case EMR_POLYTEXTOUTA:	// TODO
		case EMR_POLYTEXTOUTW:
			{
				TRACE("EMR_POLYTEXTOUT: (unhandled)\n");
			}
			break;
			
			// End of file
		case EMR_EOF:
			{
				PEMREOF pEMR = (PEMREOF)lpEMFR;
				return 0;
			}
			break;
			
		default:	// Unknown record type
			{
				ATLTRACE("Unknown iType: %d\n", lpEMFR->iType);
			}
			break;
	}
	
	return 1;
}

void CSVGReadEMF::ConvertPt(double *px, double *py)
{
	int width = m_hdr.rclBounds.right - m_hdr.rclBounds.left;
	int height = m_hdr.rclBounds.bottom - m_hdr.rclBounds.top;

	double magnifyX = (double)m_sizePix.cx/width;
	double magnifyY = (double)m_sizePix.cy/height;

	*px = (*px - m_hdr.rclBounds.left)*magnifyX + m_hdr.rclBounds.left;
	*py = (*py - m_hdr.rclBounds.top)*magnifyY + m_hdr.rclBounds.top;
}

HRESULT CSVGReadEMF::ReadEMF(HENHMETAFILE hemf, SIZEL* sizePix, ILDOMDocument* pddoc, ILSVGGElement* *group)
{
	GetEnhMetaFileHeader(
		hemf,      // handle to enhanced metafile
		sizeof(m_hdr),
		&m_hdr);

	int width = m_hdr.rclBounds.right - m_hdr.rclBounds.left;
	int height = m_hdr.rclBounds.bottom - m_hdr.rclBounds.top;

	if (sizePix)
	{
		m_sizePix = *sizePix;
	}
	else
	{
		m_sizePix.cx = width;
		m_sizePix.cy = height;
	}

//	pddoc->createObjectGroup(GUID_NULL, &m_group);
	pddoc->createElement(L"g", (ILDOMElement**)&m_group);

	ZeroMemory(hTable, sizeof(hTable));
	hDC = CreateCompatibleDC(NULL);

	BOOL b = EnumEnhMetaFile(NULL,//hDC,
		hemf,
		(ENHMFENUMPROC)::EnhMetaFileProc,
		(LPVOID)this,
		NULL);//&hdr.rclBounds/*NULL*/);

	DeleteDC(hDC);

	*group = m_group;
	(*group)->AddRef();

	return S_OK;
}

#if 0
LONG CESvgDocument::OpenEnhancedMetaFile(LPCTSTR lpszPathName)
{
	// To identify enhanced metafile ENHMETA_SIGNATURE

	HENHMETAFILE hemf;

	if (hemf = GetMyEnhMetaFile(lpszPathName))
	{
		ENHMETAHEADER	hdr;

		GetEnhMetaFileHeader(
			hemf,      // handle to enhanced metafile
			sizeof(hdr),
			&hdr);

		int width = hdr.rclBounds.right - hdr.rclBounds.left +1;
		int height = hdr.rclBounds.bottom - hdr.rclBounds.top +1;

		BOOL success;
		m_xmldoc->loadXML(L"<svg/>", &success);

		CComQIPtr<ISVGSVGElement> svg;
		m_xmldoc->get_documentElement((IDOMElement**)&svg);

		{
			CComQIPtr<ISVGAnimatedLength> alength;
			svg->get_width(&alength);
			
			CComQIPtr<ISVGLength> length;
			alength->get_baseVal(&length);

			length->set_value(width);
		}

		{
			CComQIPtr<ISVGAnimatedLength> alength;
			svg->get_height(&alength);
			
			CComQIPtr<ISVGLength> length;
			alength->get_baseVal(&length);

			length->set_value(height);
		}

		ZeroMemory(hTable, sizeof(hTable));
		hDC = CreateCompatibleDC(NULL);

		EnumEnhMetaFile(NULL,
			hemf,
			(ENHMFENUMPROC)EnhMetaFileProc,
			(LPVOID)this,
			NULL);

		DeleteDC(hDC);

		DeleteEnhMetaFile(hemf);

		return S_OK;
	}

	return -1;
}
#endif

#endif