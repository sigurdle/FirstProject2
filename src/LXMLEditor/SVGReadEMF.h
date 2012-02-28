#pragma once

#if 0

class CGdiObj
{
public:
	int m_type;
};

class CGdiPen : public CGdiObj
{
public:
	CGdiPen()
	{
		m_type = OBJ_PEN;
	}

	EXTLOGPEN m_elp;
};

class CGdiBrush : public CGdiObj
{
public:
	CGdiBrush()
	{
		m_type = OBJ_BRUSH;
	}

	LOGBRUSH32 m_lb;
};

/*
class CGdiDibBrush : public CGdiObj
{
};
*/

class CSVGReadEMF
{
public:
	HDC	hDC;
//	HGDIOBJ	hTable[512];
	CGdiObj*	hTable[512];

	ENHMETAHEADER	m_hdr;
	SIZEL m_sizePix;

	CGdiObj* m_stockObjects[STOCK_LAST+1];

	CSVGReadEMF()
	{
		memset(m_stockObjects, 0, sizeof(CGdiObj*)*(STOCK_LAST+1));

		{
			CGdiPen* pPen = new CGdiPen;
			m_stockObjects[NULL_PEN] = pPen;
			pPen->m_elp.elpPenStyle = PS_NULL;
		}

		m_pCurrentPen = new CGdiPen;

		m_pCurrentPen->m_elp.elpPenStyle = PS_SOLID | PS_GEOMETRIC;
		m_pCurrentPen->m_elp.elpWidth = 1;

		m_pCurrentBrush = new CGdiBrush;
		m_pCurrentBrush->m_lb.lbStyle = BS_SOLID;
		m_pCurrentBrush->m_lb.lbColor = RGB(255, 255, 255);
		m_pCurrentBrush->m_lb.lbHatch = 0;
	}

	CGdiPen* m_pCurrentPen;
	CGdiBrush* m_pCurrentBrush;

	POINT m_startPt;

	/*
	CComPtr<IPDObjectFrame> m_curFrame;
	CComPtr<IPDPath> m_curPath;
	CComPtr<IPDSubPath> m_curSubPath;
	*/
	LSVG::SVGPathElement* m_curFrame;
	LSVG::SVGPathSegList* m_curPath;

	//CComPtr<IPDObjectGroup> m_group;
	LSVG::SVGGElement* m_group;

	int EnhMetaFileProc(
	  HDC hhDC,                    // handle to device context
	  HANDLETABLE FAR *lpHTable,  // pointer to metafile handle table
	  ENHMETARECORD FAR *lpEMFR,  // pointer to metafile record
	  int nObj                   // count of objects
	);

/*

The following formula shows the math involved in converting a
point from page space to device space.

Dx = ((Lx - WOx) * VEx / WEx) + VOx 
 
The following variables are involved.

Dx     x value in device units 
Lx     x value in logical units (also known as page space units) 
WOx     window x origin 
VOx     viewport x origin 
WEx     window x-extent 
VEx     viewport x-extent 
 
*/

	void ConvertPt(double *px, double *py);

	void SetShapeStroke(LSVG::SVGElement* frame, LPLOGPEN lp);
	void SetShapeStroke(LSVG::SVGElement* frame, LPEXTLOGPEN lp);
	void SetShapeFill(LSVG::SVGElement* frame, LPLOGBRUSH32 lb);

	HRESULT ReadEMF(HENHMETAFILE hemf, SIZEL* sizePix, LXML::Document* pddoc, LSVG::SVGGElement* *group);
};

#endif