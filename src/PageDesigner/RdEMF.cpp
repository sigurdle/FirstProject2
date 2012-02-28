// Read EMF/WMF files

#include "stdafx.h"
#include "PageDesigner.h"
//#include "SVGEditor2.h"

#include "RdEMF.h"

//#include "ESvgDocument.h"

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
	CReadEMF* emf = (CReadEMF*)lpData;
	return emf->EnhMetaFileProc(hhDC, lpHTable, lpEMFR, nObj);
}

void CReadEMF::SetShapeStroke(IPDObjectFrame* frame, LPLOGPEN lp)
{
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
}

void CReadEMF::SetShapeStroke(IPDObjectFrame* frame, LPEXTLOGPEN elp)
{
	if (!elp || elp->elpPenStyle == PS_NULL)
	{
		//stylable->style->setProperty(L"stroke", L"none", L"");
	}
	else// if ((elp->elpPenStyle/*PS_SOLID*/)/* || ((lp->lopnStyle == PS_INSIDEFRAME) && (lp->lopnWidth.x <= 1))*/)
	{
		CComPtr<IPDObjectStroke> stroke;
		stroke.CoCreateInstance(CLSID_PDObjectStroke);
		CComQIPtr<IPDStrokeSettings> stroke2 = stroke;

		stroke2->put_strokeWeight(elp->elpWidth);

		CComPtr<IPDBrush> brush;
		stroke->get_brush(&brush);

		CComPtr<IPDColor> color;
		brush->setColor(&color);
		color->setRGB(GetRValue(elp->elpColor), GetGValue(elp->elpColor), GetBValue(elp->elpColor));

		frame->appendSubObject(stroke);
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

void CReadEMF::SetShapeFill(IPDObjectFrame* frame, LPLOGBRUSH32 lb)
{
	if (!lb || lb->lbStyle == BS_NULL)
	{
//		stylable->style->setProperty(L"fill", L"none", L"");
	}
	else if (lb->lbStyle == BS_SOLID)
	{
		CComPtr<IPDObjectFill> fill;
		fill.CoCreateInstance(CLSID_PDObjectFill);

		CComPtr<IPDBrush> brush;
		fill->get_brush(&brush);

		CComPtr<IPDColor> color;
		brush->setColor(&color);
		color->setRGB(GetRValue(lb->lbColor), GetGValue(lb->lbColor), GetBValue(lb->lbColor));

		frame->appendSubObject(fill);
	}
	else
	{
		TRACE("Unknown brush style: %d\n", lb->lbStyle);
	//	m_fill = TRUE;
//		m_fillColor = lb->lbColor;
	}
}

int CReadEMF::EnhMetaFileProc(
	  HDC hhDC,                    // handle to device context
	  HANDLETABLE FAR *lpHTable,  // pointer to metafile handle table
	  ENHMETARECORD FAR *lpEMFR,  // pointer to metafile record
	  int nObj                   // count of objects
	)
{
	CComPtr<IPDDocument> pddoc;
	m_group->get_document(&pddoc);

	//	CESvgDocument* pDoc = (CESvgDocument*)lpData;
//	ASSERT(pDoc);

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
			TRACE("EMR_SELECTOBJECT\n");
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
		}
		break;
		
	case EMR_DELETEOBJECT:
		{
			TRACE("EMR_DELETEOBJECT\n");
			PEMRDELETEOBJECT pEMR = (PEMRDELETEOBJECT)lpEMFR;
			
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
			ATLASSERT(hPen);
			hTable[pEMR->ihPen] = hPen;
#endif
			CGdiPen* pPen = new CGdiPen;
			pPen->m_elp = pEMR->elp;
			hTable[pEMR->ihPen] = pPen;
		}
		break;
		
	case EMR_CREATEBRUSHINDIRECT:
		{
			TRACE("EMR_CREATEBRUSHINDIRECT\n");

			PEMRCREATEBRUSHINDIRECT pEMR = (PEMRCREATEBRUSHINDIRECT)lpEMFR;
			
			//HBRUSH hBrush = ::CreateBrushIndirect((LOGBRUSH*)&pEMR->lb);
			//hTable[pEMR->ihBrush] = hBrush;
			CGdiBrush* pBrush = new CGdiBrush;
			pBrush->m_lb = pEMR->lb;

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
			TRACE("EMR_MOVETOEX\n");

			PEMRMOVETOEX pEMR = (PEMRMOVETOEX)lpEMFR;

			::MoveToEx(hDC, pEMR->ptl.x, pEMR->ptl.y, NULL);

			m_startPt.x = pEMR->ptl.x;
			m_startPt.y = pEMR->ptl.y;

			if (m_curSubPath)	// Start new subpath
			{
				m_curSubPath.Release();
			}
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
				TRACE("EMR_BEGINPATH\n");

				if (m_curFrame == NULL)
				{
					pddoc->createObjectFrame(&m_curFrame);
					m_curFrame->get_path(&m_curPath);

					m_group->appendObject(m_curFrame);
				}
			}
			break;

		case EMR_STROKEPATH:
			{
				TRACE("EMR_STROKEPATH\n");

				if (m_curFrame)
				{
					SetShapeStroke(m_curFrame, &m_pCurrentPen->m_elp);

					m_group->appendObject(m_curFrame);

					m_curSubPath.Release();
					m_curPath.Release();
					m_curFrame.Release();
				}
			}
			break;

		case EMR_STROKEANDFILLPATH:
			{
				TRACE("EMR_STROKEANDFILLPATH\n");

				if (m_curFrame)
				{
					SetShapeFill(m_curFrame, &m_pCurrentBrush->m_lb);
					SetShapeStroke(m_curFrame, &m_pCurrentPen->m_elp);

					m_group->appendObject(m_curFrame);

					m_curSubPath.Release();
					m_curPath.Release();
					m_curFrame.Release();
				}
			}
			break;

// Geometric shapes
		case EMR_LINETO:
		{
			TRACE("EMR_LINETO\n");

			PEMRLINETO pEMR = (PEMRLINETO)lpEMFR;

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

			MoveToEx(hDC, pEMR->ptl.x, pEMR->ptl.y, NULL);
		}
		break;

		case EMR_POLYGON16:
		case EMR_POLYLINE16:
			{
				PEMRPOLYGON16	pEMR = (PEMRPOLYGON16)lpEMFR;

				if (lpEMFR->iType == EMR_POLYGON16)
					TRACE("POLYGON16\n");
				else
					TRACE("POLYLINE16\n");

				BOOL bInPath;

				if (m_curFrame == NULL)
				{
					bInPath = FALSE;

					pddoc->createObjectFrame(&m_curFrame);

					m_curFrame->get_path(&m_curPath);

					m_curPath->createSubPath(&m_curSubPath);
					m_curPath->insertSubPath(-1, m_curSubPath);

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

						m_curSubPath->put_closed(VARIANT_TRUE);

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

					long index;
					m_curSubPath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);
				}

				if (!bInPath)
				{
					m_group->appendObject(m_curFrame);

					m_curSubPath.Release();
					m_curPath.Release();
					m_curFrame.Release();
				}
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

				case EMR_RECTANGLE:
				case EMR_ELLIPSE:
				{
					/*
					PEMRRECTANGLE	pEMR = (PEMRRECTANGLE)lpEMFR;

					CRect	r;
					r.left = pEMR->rclBox.left;
					r.right = pEMR->rclBox.right;
					r.top = pEMR->rclBox.top;
					r.bottom = pEMR->rclBox.bottom;
					::LPtoDP(hDC, (LPPOINT)&r, 2);

					if (lpEMFR->iType == EMR_RECTANGLE)
					{
						SVGLib::ISVGRectElementPtr rect = pDoc->GetDOMDocument()->createElement(L"rect");
						rect->x->baseVal->value = r.left;
						rect->y->baseVal->value = r.top;
						rect->width->baseVal->value = r.Width();
						rect->height->baseVal->value = r.Height();

						element = rect;
					}
					else if (lpEMFR->iType == EMR_ELLIPSE)
					{
						SVGLib::ISVGEllipseElementPtr ellipse = pDoc->GetDOMDocument()->createElement(L"ellipse");
						ellipse->cx->baseVal->value = r.left + r.Width()/2;
						ellipse->cy->baseVal->value = r.top + r.Height()/2;
						ellipse->rx->baseVal->value = r.Width()/2;
						ellipse->ry->baseVal->value = r.Height()/2;

						element = ellipse;
					}

					SetShapeStrokeFill(element, &lp, &lb);
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
				TRACE("EMR_POLYBEZIERTO16:\n");
				
				PEMRPOLYBEZIERTO16 pEMR = (PEMRPOLYBEZIERTO16)lpEMFR;
				
				POINT pt;
				GetCurrentPositionEx(hDC, &pt);
				
				BezierPoint bpt;
				
				if (m_curSubPath == NULL)
				{
					m_curPath->createSubPath(&m_curSubPath);
					m_curPath->insertSubPath(-1, m_curSubPath);
				}

				LPToDP(hDC, pt.x, pt.y, &bpt.x, &bpt.y);
				ConvertPt(&bpt.x, &bpt.y);

				bpt.x1 = bpt.x;
				bpt.y1 = bpt.y;
				
				ATLASSERT((pEMR->cpts % 3) == 0);
				
				for (int i = 0; i < pEMR->cpts; i += 3)
				{
					LPToDP(hDC, pEMR->apts[i].x, pEMR->apts[i].y, &bpt.x2, &bpt.y2);
					ConvertPt(&bpt.x2, &bpt.y2);
					
					long index;
					m_curSubPath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);

					LPToDP(hDC, pEMR->apts[i+1].x, pEMR->apts[i+1].y, &bpt.x1, &bpt.y1);
					ConvertPt(&bpt.x1, &bpt.y1);

					LPToDP(hDC, pEMR->apts[i+2].x, pEMR->apts[i+2].y, &bpt.x, &bpt.y);
					ConvertPt(&bpt.x, &bpt.y);
				}
				
				bpt.x2 = bpt.x;
				bpt.y2 = bpt.y;
				
				long index;
				m_curSubPath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);
				
				MoveToEx(hDC, pEMR->apts[i-1].x, pEMR->apts[i-1].y, NULL);
			}
			break;

		case EMR_CLOSEFIGURE:
			{
				TRACE("EMR_CLOSEFIGURE:\n");

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
			
			// Bitmap Stuff (in order of importance)
		case EMR_BITBLT:	// TODO
			{
				PEMRBITBLT pEMR = (PEMRBITBLT)lpEMFR;
				
				//	pEMR->
				TRACE("EMR_BITBLT: (unhandled)\n");
			}
			break;
			
		case EMR_STRETCHDIBITS:	// TODO
			{
				TRACE("EMR_STRETCHDIBITS: (unhandled)\n");
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

void CReadEMF::ConvertPt(double *px, double *py)
{
	int width = m_hdr.rclBounds.right - m_hdr.rclBounds.left;
	int height = m_hdr.rclBounds.bottom - m_hdr.rclBounds.top;

	double magnifyX = (double)m_sizePix.cx/width;
	double magnifyY = (double)m_sizePix.cy/height;

	*px = (*px - m_hdr.rclBounds.left)*magnifyX + m_hdr.rclBounds.left;
	*py = (*py - m_hdr.rclBounds.top)*magnifyY + m_hdr.rclBounds.top;
}

HRESULT CReadEMF::ReadEMF(HENHMETAFILE hemf, SIZEL* sizePix, IPDDocument* pddoc, IPDObjectGroup* *group)
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


	pddoc->createObjectGroup(GUID_NULL, &m_group);

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

			length->put_value(width);
		}

		{
			CComQIPtr<ISVGAnimatedLength> alength;
			svg->get_height(&alength);
			
			CComQIPtr<ISVGLength> length;
			alength->get_baseVal(&length);

			length->put_value(height);
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
