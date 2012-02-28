#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGPathElement.h"
#include "EXMLDocument.h"

#if 0

/////////////////////////////////////////////////////////////////
// CSubPath

void CSubPath::appendPoint(double x, double y, double x1, double y1, double x2, double y2, long* curveCp)
{
// TODO, not really an append point
	m_firstx = x1;
	m_firsty = y1;

	CComPtr<ILSVGPathSegMovetoAbs> moveto;
	m_pPath->m_pathElement->createSVGPathSegMovetoAbs(x, y, &moveto);

	m_pPath->m_segList->appendItem(moveto, NULL);

	m_lastx = x2;
	m_lasty = y2;

	m_nsegs++;

	*curveCp = 0;
}

STDMETHODIMP CSubPath::get_pointCount(long* pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_nsegs;
	return S_OK;
}

void CSubPath::GetPathSeg(int segindex, CBezierPoint* _seg)
{
	CComQIPtr<ILSVGPathSeg> seg;
	m_pPath->m_segList->getItem(m_segIndex+segindex, &seg);

	LSVGPathSegType segtype;
	seg->get_pathSegType(&segtype);

	if (segtype == PATHSEG_CURVETO_CUBIC_ABS)
	{
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubic = seg;

		cubic->get_x2(&_seg->x1);
		cubic->get_y2(&_seg->y1);
		cubic->get_x(&_seg->x);
		cubic->get_y(&_seg->y);
	}
	else if (segtype == PATHSEG_MOVETO_ABS)
	{
		CComQIPtr<ILSVGPathSegMovetoAbs> move = seg;

		_seg->x1 = m_firstx;
		_seg->y1 = m_firsty;
		move->get_x(&_seg->x);
		move->get_y(&_seg->y);
	}
	else if (segtype == PATHSEG_LINETO_ABS)
	{
		CComQIPtr<ILSVGPathSegLinetoAbs> line = seg;

		line->get_x(&_seg->x);
		line->get_y(&_seg->y);
		_seg->x1 = _seg->x;
		_seg->y1 = _seg->y;
	}
	/*
	else if (segtype == PATHSEG_CLOSEPATH)
	{
		CComQIPtr<ILSVGPathSegMovetoAbs> move = seg;
		ASSERT(move);

		_seg->x2 = m_firstx;
		_seg->y2 = m_firsty;
	}
	*/
	else
	{
		ASSERT(0);
	}

	if (segindex < m_nsegs-1)
	{
		CComQIPtr<ILSVGPathSeg> seg1;
		m_pPath->m_segList->getItem(m_segIndex+segindex+1, &seg1);

		LSVGPathSegType segtype1;
		seg1->get_pathSegType(&segtype1);

		if (segtype1 == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubic1 = seg1;

			cubic1->get_x1(&_seg->x2);
			cubic1->get_y1(&_seg->y2);
		}
		else if (segtype1 == PATHSEG_LINETO_ABS)
		{
		// Not sure
			CComQIPtr<ILSVGPathSegLinetoAbs> line1 = seg1;

		//	line1->get_x(&_seg->x2);
		//	line1->get_y(&_seg->y2);

			_seg->x2 = _seg->x;
			_seg->y2 = _seg->y;
		}
		/*
		else if (segtype1 == PATHSEG_CLOSEPATH)
		{
			_seg->x2 = m_firstx;
			_seg->y2 = m_firsty;
		}
		*/
		else
		{
			ASSERT(0);
		}
	}
	else
	{
		_seg->x2 = m_lastx;
		_seg->y2 = m_lasty;
	}
}

void CSubPath::PutPathSeg(int segindex, CBezierPoint* _seg)
{
	CComQIPtr<ILSVGPathSeg> seg;
	m_pPath->m_segList->getItem(m_segIndex+segindex, &seg);

	LSVGPathSegType segtype;
	seg->get_pathSegType(&segtype);

	if (segtype == PATHSEG_CURVETO_CUBIC_ABS)
	{
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubic = seg;

		cubic->put_x2(_seg->x1);
		cubic->put_y2(_seg->y1);
		cubic->put_x(_seg->x);
		cubic->put_y(_seg->y);
	}
	else if (segtype == PATHSEG_MOVETO_ABS)
	{
		CComQIPtr<ILSVGPathSegMovetoAbs> move = seg;

		m_firstx = _seg->x1;
		m_firsty = _seg->y1;
		move->put_x(_seg->x);
		move->put_y(_seg->y);

	// Also alter the end

		ASSERT(segindex == 0);

		if (m_bClosed)
		{
			if (m_nsegs >= 2)
			{
				CComQIPtr<ILSVGPathSeg> seg1;
				m_pPath->m_segList->getItem(m_segIndex+m_nsegs-1, &seg1);

				LSVGPathSegType segtype1;
				seg1->get_pathSegType(&segtype1);

				if (segtype1 == PATHSEG_CURVETO_CUBIC_ABS)
				{
					CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubic1 = seg1;

					cubic1->put_x(_seg->x);
					cubic1->put_y(_seg->y);
					cubic1->put_x2(_seg->x1);
					cubic1->put_y2(_seg->y1);
				}
			}
		}
	}
	else if (segtype == PATHSEG_LINETO_ABS)
	{
		CComQIPtr<ILSVGPathSegLinetoAbs> line = seg;

		line->put_x(_seg->x);
		line->put_y(_seg->y);
	}
	else
	{
		ASSERT(0);
	}

	if (segindex < m_nsegs-1)
	{
		CComQIPtr<ILSVGPathSeg> seg1;
		m_pPath->m_segList->getItem(m_segIndex+segindex+1, &seg1);

		LSVGPathSegType segtype1;
		seg1->get_pathSegType(&segtype1);

		if (segtype1 == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubic1 = seg1;

			cubic1->put_x1(_seg->x2);
			cubic1->put_y1(_seg->y2);
		}
		else if (segtype1 == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> line1 = seg1;

			//line1->put_x(_seg->x2);
			//line1->put_y(_seg->y2);
		}
		else
		{
			// TODO, could be z, could be m
			ASSERT(0);
		}
	}
	else
	{
		m_lastx = _seg->x2;
		m_lasty = _seg->y2;
	}
}

#endif