#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegList.h"

#include "SVGPathSegMovetoAbs.h"
#include "SVGPathSegMovetoRel.h"
#include "SVGPathSegLinetoRel.h"
#include "SVGPathSegLinetoAbs.h"
#include "SVGPathSegCurvetoCubicAbs.h"
#include "SVGPathSegCurvetoCubicRel.h"
#include "SVGPathSegCurvetoQuadraticAbs.h"
#include "SVGPathSegCurvetoQuadraticRel.h"
#include "SVGPathSegCurvetoCubicSmoothAbs.h"
#include "SVGPathSegCurvetoCubicSmoothRel.h"
#include "SVGPathSegCurvetoQuadraticSmoothAbs.h"
#include "SVGPathSegCurvetoQuadraticSmoothRel.h"
#include "SVGPathSegLinetoHorizontalAbs.h"
#include "SVGPathSegLinetoHorizontalRel.h"
#include "SVGPathSegLinetoVerticalAbs.h"
#include "SVGPathSegLinetoVerticalRel.h"
#include "SVGPathSegArcAbs.h"
#include "SVGPathSegArcRel.h"
#include "SVGPathSegClosePath.h"

namespace System
{

//namespace Math
//{
double GetLineAngle(double x1, double y1, double x2, double y2);

/* take binary sign of a, either -1, or 1 if >= 0 */
#define SGN(a)		(((a)<0) ? -1 : 1)

double GetCurveT(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double length, double* pt)
{
	if (length == 0)
	{
		*pt = 0;
		return 0;
	}

	double length2 = 0;

	double ax, ay, bx, by, cx, cy;

	cx = 3 * (x1 - x0);
	cy = 3 * (y1 - y0);
	bx = 3 * (x2 - x1) - cx;
	by = 3 * (y2 - y1) - cy;
	ax = x3 - x0 - cx - bx;
	ay = y3 - y0 - cy - by;

//	double tinc = 1/500.0;
	double tinc = 1/500.0;

	double oldx, oldy;

	for (double t = 0.0; t <= 1.0; t += tinc)
	{
		double xt = ax * t*t*t + bx * t*t + cx * t + x0;
		double yt = ay * t*t*t + by * t*t + cy * t + y0;

		if (t > 0)
		{
			double dx = xt-oldx;
			double dy = yt-oldy;

			double l = sqrt(dx*dx + dy*dy);
			length2 += l;

			if (length2 >= length)
			{
				*pt = t;
				return 0;
			}
		}

		oldx = xt;
		oldy = yt;
	}

	return length2;
}

static double GetAngle(double dx, double dy)
{
	double distance = sqrt(dx*dx + dy*dy);
	double distance2 = distance;

	if (distance2 == 0.0) distance2 = 0.00001;
	if (dy < 0) distance2 =-distance2;
	double angle = acos(dx/distance2);
	if (dy < 0) angle += M_PI;

	return angle;// * 180/M_PI;
}
//}

namespace gm
{

//*** TODO *** This needs to be improved

double CalcCurveLength(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
	double length = 0;

	double ax, ay, bx, by, cx, cy;

	cx = 3 * (x1 - x0);
	cy = 3 * (y1 - y0);
	bx = 3 * (x2 - x1) - cx;
	by = 3 * (y2 - y1) - cy;
	ax = x3 - x0 - cx - bx;
	ay = y3 - y0 - cy - by;

	double tinc = 1/500.0;

	double oldx, oldy;

	for (double t = 0.0; t <= 1.0; t += tinc)
	{
		double xt = ax * t*t*t + bx * t*t + cx * t + x0;
		double yt = ay * t*t*t + by * t*t + cy * t + y0;

		if (t > 0)
		{
			double dx = xt-oldx;
			double dy = yt-oldy;

			double l = sqrt(dx*dx + dy*dy);
			length += l;
		}

		oldx = xt;
		oldy = yt;
	}

	return length;
}

}

namespace Web
{

double SVGPathSegList::getLength() const
{
	double length = 0;

	double last_movex = 0;
	double last_movey = 0;

	double oldx;
	double oldy;

	long numberOfItems = m_items.GetSize();

	for (int i = 0; i < numberOfItems; i++)
	{
		SVGPathSeg* seg = m_items[i];

		SVGPathSegType segType = seg->get_pathSegType();
		if (segType == PATHSEG_MOVETO_ABS)
		{
			SVGPathSegMovetoAbs* movetoabs = dynamic_cast<SVGPathSegMovetoAbs*>(seg);

			double x, y;
			x = movetoabs->get_x();
			y = movetoabs->get_y();

			last_movex = x;
			last_movey = y;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			SVGPathSegLinetoAbs* linetoabs = dynamic_cast<SVGPathSegLinetoAbs*>(seg);

			double x = linetoabs->get_x();
			double y = linetoabs->get_y();

			double dx = x-oldx;
			double dy = y-oldy;

			double l = sqrt(dx*dx + dy*dy);
			length += l;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			SVGPathSegCurvetoCubicAbs* cubictoabs = dynamic_cast<SVGPathSegCurvetoCubicAbs*>(seg);

			double x, y, x1, y1, x2, y2;
			x = cubictoabs->get_x();
			y = cubictoabs->get_y();
			x1 = cubictoabs->get_x1();
			y1 = cubictoabs->get_y1();
			x2 = cubictoabs->get_x2();
			y2 = cubictoabs->get_y2();

			double l = gm::CalcCurveLength(oldx, oldy, x1, y1, x2, y2, x, y);
			length += l;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CLOSEPATH)
		{
		//	int ix = last_movex;
		//	int iy = last_movey;
		}
	}

	return length;
}

// pangle is in degrees
bool SVGPathSegList::getPointOnLength(double onlength, double *pxt, double *pyt, double *pangle)
{
	if (pxt == NULL) THROW(-1);
	if (pyt == NULL) THROW(-1);
//	if (pangle == NULL) return E_POINTER;	// Allowed to be NULL

	double length = 0;

	double x0, y0;

	for (uint i = 0; i < m_items.GetSize(); i++)
	{
		SVGPathSeg* seg = m_items[i];
		SVGPathSegType segType = seg->get_pathSegType();

		if (segType == PATHSEG_MOVETO_ABS)
		{
			SVGPathSegMovetoAbs* move = dynamic_cast<SVGPathSegMovetoAbs*>(seg);

			x0 = move->get_x();
			y0 = move->get_y();
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			SVGPathSegLinetoAbs* line = dynamic_cast<SVGPathSegLinetoAbs*>(seg);

			double x1 = line->get_x();
			double y1 = line->get_y();

			double dx = x1-x0;
			double dy = y1-y0;

			double l = sqrt(dx*dx + dy*dy);

			if (length+l >= onlength)
			{
				double k = (onlength-length)/l;
				*pxt = x0 + dx*k;
				*pyt = y0 + dy*k;

				if (pangle)
				{
					*pangle = gmDegrees(GetLineAngle(x0, y0, x1, y1));
				}

				return Success;
			}

			x0 = x1;
			y0 = y1;

			length += l;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			SVGPathSegCurvetoCubicAbs* cubic = dynamic_cast<SVGPathSegCurvetoCubicAbs*>(seg);

			double x1, y1, x2, y2, x3, y3;
			x1 = cubic->get_x1();
			y1 = cubic->get_y1();
			x2 = cubic->get_x2();
			y2 = cubic->get_y2();
			x3 = cubic->get_x();
			y3 = cubic->get_y();

			double t = -1;

			double l = GetCurveT(x0, y0, x1, y1, x2, y2, x3, y3, onlength-length, &t);

			if (t >= 0)
			{
				double cx = 3 * (x1 - x0);
				double cy = 3 * (y1 - y0);
				double bx = 3 * (x2 - x1) - cx;
				double by = 3 * (y2 - y1) - cy;
				double ax = x3 - x0 - cx - bx;
				double ay = y3 - y0 - cy - by;

				*pxt = ax * t*t*t + bx * t*t + cx * t + x0;
				*pyt = ay * t*t*t + by * t*t + cy * t + y0;

				// Calculate angle
				double dx = ax * 3*t*t + bx * 2*t + cx;
				double dy = ay * 3*t*t + by * 2*t + cy;

				if (pangle)
				{
					*pangle = gmDegrees(GetAngle(dx, dy));
				}

				return true;
			}

			x0 = x3;
			y0 = y3;
			length += l;
		}
		else
			ASSERT(0);
	}

	return false;
}

/*
void SVGPathSegList::FinalRelease()
{
	RemoveAll();
}
*/

void SVGPathSegList::RemoveAll()
{
	for (uint i = 0; i < m_items.GetSize(); i++)
	{
		delete m_items[i];
	}

	m_items.RemoveAll();
}

unsigned int SVGPathSegList::get_numberOfItems() const
{
	return m_items.GetSize();
}

void SVGPathSegList::clear()
{
	if (m_items.GetSize() > 0)
	{
		RemoveAll();
		ChangedSeg();
	}
}

SVGPathSeg* SVGPathSegList::initialize(SVGPathSeg *newItem)
{
// Untested

	ASSERT(newItem != NULL);
	if (newItem == NULL) THROW(-1);

	RemoveAll();

	m_items.Add(newItem);

	(newItem)->m_pSegList = this;

	ChangedSeg();

	return newItem;
}

SVGPathSeg* SVGPathSegList::getItem(unsigned int index) const
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
	{
		ASSERT(0);
		return NULL;
	}
}

SVGPathSeg* SVGPathSegList::insertItemBefore(SVGPathSeg* newItem, unsigned int index)
{
	ASSERT(newItem != NULL);
	if (newItem == NULL) THROW(-1);

	if (newItem->m_pSegList)
	{
		newItem->m_pSegList->RemoveItem(newItem);
	}

	m_items.InsertAt(index, newItem);
	newItem->m_pSegList = this;

	ChangedSeg();

	return newItem;
}

SVGPathSeg* SVGPathSegList::replaceItem(SVGPathSeg *newItem, unsigned int index)
{
	if (index >= 0 && index < m_items.GetSize())
	{
		ASSERT(newItem != NULL);
		if (newItem == NULL) THROW(-1);

		if (newItem->m_pSegList)
		{
			newItem->m_pSegList->RemoveItem(newItem);
		}

		SVGPathSeg* pOldSeg = m_items[index];
		pOldSeg->m_pSegList = NULL;
	//	m_items[index]->Release();

		m_items[index] = newItem;

		ChangedSeg();

		return pOldSeg;
	}
	else
	{
		ASSERT(0);
	}
	return NULL;
}

SVGPathSeg* SVGPathSegList::removeItem(unsigned int index)
{
	if (index < m_items.GetSize())
	{
		SVGPathSeg* pSeg = m_items[index];

		pSeg->m_pSegList = NULL;
		/*
		if (pVal)
		{
			*pVal = m_items[index];
			(*pVal)->AddRef();
		}
		*/
	//	m_items[index]->Release();
		m_items.RemoveAt(index);

		ChangedSeg();

		return pSeg;
	}
	else
	{
		ASSERT(0);
	}

	return NULL;
}

void SVGPathSegList::RemoveItem(SVGPathSeg* seg)
{
	for (size_t i = 0; i < m_items.GetSize(); i++)
	{
		if (m_items[i] == seg)
		{
			SVGPathSeg* pSeg = m_items[i];

			pSeg->m_pSegList = NULL;
			//m_items[i]->Release();
			m_items.RemoveAt(i);

			if (m_pListener)
			{
				m_pListener->OnPathSegListChange(this);
			}

			return;
		}
	}

	ASSERT(0);
}

SVGPathSeg* SVGPathSegList::appendItem(SVGPathSeg *newItem)
{
	ASSERT(newItem != NULL);
	if (newItem == NULL) THROW(-1);

	if (newItem->m_pSegList)
	{
		newItem->m_pSegList->RemoveItem(newItem);
	}

	m_items.Add(newItem);
	newItem->m_pSegList = this;

	ChangedSeg();

	return newItem;
}

// Extensions
void SVGPathSegList::AddEllipse(/*[in]*/ double cx, /*[in]*/ double cy, /*[in]*/ double rx, /*[in]*/ double ry)
{
	ErrorCode hr = 0;

	ASSERT(0);
#if 0

	double left = cx-rx;
	double top = cy-ry;
	double right = cx+rx;
	double bottom = cy+ry;
	double width = rx*2;
	double height = ry*2;
	
	// MAGICAL CONSTANT to map ellipse to beziers
   //  			2/3*(sqrt(2)-1) 
	const double EToBConst =	0.2761423749154; 
	PointD offset;
	offset.X = width * EToBConst;
	offset.Y = height * EToBConst;

	{
		CComObject<CLSVGPathSegMovetoAbs>* seg;
		hr = CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&seg);
		if (seg)
		{
			seg->m_x = left;	seg->m_y = cy;

			seg->AddRef();
			seg->m_pSegList = this;
			m_items.Add(seg);
		}
		else
			return hr;
	}

	{
		CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
		hr = CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);
		if (seg)
		{
			seg->m_x = cx;	seg->m_y = top;
			seg->m_x1 = left;		seg->m_y1 = cy-offset.Y;
			seg->m_x2 = cx-offset.X;		seg->m_y2 = top;

			seg->AddRef();
			seg->m_pSegList = this;
			m_items.Add(seg);
		}
		else
			return hr;
	}

	{
		CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
		hr = CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);
		if (seg)
		{
			seg->m_x = right;						seg->m_y = cy;
			seg->m_x1 = cx + offset.X;	seg->m_y1 = top;
			seg->m_x2 = right;						seg->m_y2 = cy - offset.Y;

			seg->AddRef();
			seg->m_pSegList = this;
			m_items.Add(seg);
		}
		else
			return hr;
	}

	{
		CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
		hr = CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);
		if (seg)
		{
			seg->m_x = cx;				seg->m_y = bottom;
			seg->m_x1 = right;				seg->m_y1 = cy+offset.Y;
			seg->m_x2 = cx+offset.X;	seg->m_y2 = bottom;

			seg->AddRef();
			seg->m_pSegList = this;
			m_items.Add(seg);
		}
		else
			return hr;
	}

	{
		CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
		hr = CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);
		if (seg)
		{
			seg->m_x = left;				seg->m_y = cy;
			seg->m_x1 = cx-offset.X;	seg->m_y1 = bottom;
			seg->m_x2 = left;					seg->m_y2 = cy + offset.Y;

			seg->AddRef();
			seg->m_pSegList = this;
			m_items.Add(seg);
		}
		else
			return hr;
	}

// ?? add a closepath ??
	{
		CComObject<CLSVGPathSegClosePath>* seg;
		hr = CComObject<CLSVGPathSegClosePath>::CreateInstance(&seg);
		if (seg)
		{
			seg->AddRef();
			seg->m_pSegList = this;
			m_items.Add(seg);
		}
		else
			return hr;
	}

	ChangedSeg();
#endif
}

void SVGPathSegList::AddRoundRect(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height, /*[in]*/ double rx, /*[in]*/ double ry)
{
	ErrorCode hr = 0;

	ASSERT(0);
#if 0

//	double width = right-left;
//	double height = bottom-top;

	double left = x;
	double top = y;
	double right = x+width;
	double bottom = y+height;

	if (rx > width/2) rx = width/2;
	if (ry > height/2) ry = height/2;

    // MAGICAL CONSTANT to map ellipse to beziers
   //  			2/3*(sqrt(2)-1) 
    const double EToBConst =	0.2761423749154; 
    PointD offset;
	 offset.X = rx*2 * EToBConst;
	 offset.Y = ry*2 * EToBConst;
/*
    CDblPoint centre;
	 centre.x = (left + right) / 2;
	 centre.y = (top + bottom) / 2;
*/
	// top line
	{
		CLSVGPathSegMovetoAbs* seg = new CLSVGPathSegMovetoAbs;

		seg->m_x = left+rx;	seg->m_y = top;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

	{
		CLSVGPathSegLinetoAbs>* seg = new CLSVGPathSegLinetoAbs;

		seg->m_x = right-rx;	seg->m_y = top;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

	{
		CLSVGPathSegCurvetoCubicAbs* seg = new CLSVGPathSegCurvetoCubicAbs;

		seg->m_x1 = right-rx+offset.X;		seg->m_y1 = top;
		seg->m_x2 = right;						seg->m_y2 = top+ry-offset.Y;
		seg->m_x = right;						seg->m_y = top+ry;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

// right line
	{
		CLSVGPathSegLinetoAbs* seg = new CLSVGPathSegLinetoAbs;

		seg->m_x = right;	seg->m_y = bottom-ry;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

	{
		CLSVGPathSegCurvetoCubicAbs* seg = new CLSVGPathSegCurvetoCubicAbs;

		seg->m_x1 = right;						seg->m_y1 = bottom-ry+offset.Y;
		seg->m_x2 = right-rx+offset.X;		seg->m_y2 = bottom;
		seg->m_x = right-rx;					seg->m_y = bottom;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

// bottom line
	{
		CLSVGPathSegLinetoAbs* seg = new CLSVGPathSegLinetoAbs;

		seg->m_x = left+rx;	seg->m_y = bottom;
		seg->m_pSegList = this;

		seg->AddRef();
		m_items.Add(seg);
	}

	{
		CLSVGPathSegCurvetoCubicAbs* seg = new CLSVGPathSegCurvetoCubicAbs;

		seg->m_x1 = left+rx-offset.X;	seg->m_y1 = bottom;
		seg->m_x2 = left;					seg->m_y2 = bottom-ry+offset.Y;
		seg->m_x = left;						seg->m_y = bottom-ry;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

// left line
	{
		CLSVGPathSegLinetoAbs* seg = new CLSVGPathSegLinetoAbs;

		seg->m_x = left;	seg->m_y = top+ry;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

	{
		CLSVGPathSegCurvetoCubicAbs* seg = new CLSVGPathSegCurvetoCubicAbs;

		seg->m_x1 = left;					seg->m_y1 = top+ry-offset.Y;
		seg->m_x2 = left+rx-offset.X;	seg->m_y2 = top;
		seg->m_x = left+rx;					seg->m_y = top;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

// ?? add a closepath ??
	{
		CLSVGPathSegClosePath* seg = new CLSVGPathSegClosePath;
		if (seg)
		{
			seg->AddRef();
			seg->m_pSegList = this;
			m_items.Add(seg);
		}
		else
			return hr;
	}

	ChangedSeg();
#endif
}

void SVGPathSegList::AddRect(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height)
{
	ASSERT(0);
}

void SVGPathSegList::AddLine(/*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
{
	ASSERT(0);
#if 0
	{
		CComObject<CLSVGPathSegMovetoAbs>* seg;
		CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&seg);

		seg->m_x = x1;
		seg->m_y = y1;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

	{
		CComObject<CLSVGPathSegLinetoAbs>* seg;
		CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg);

		seg->m_x = x2;
		seg->m_y = y2;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

	ChangedSeg();
#endif
}

void SVGPathSegList::AddMoveTo(/*[in]*/ double x, /*[in]*/ double y)
{
	VERIFY(0);
}

void SVGPathSegList::AddLineTo(/*[in]*/ double x, /*[in]*/ double y)
{
	VERIFY(0);
}

void SVGPathSegList::AddCloseFigure()
{
	VERIFY(0);
}

void SVGPathSegList::ChangedSeg()
{
	if (m_bLockUpdate == 0)
	{
		if (m_pListener)
		{
			m_pListener->OnPathSegListChange(this);
		}
	}
	else
	{
		m_nChanges++;
	}
}

void SVGPathSegList::LockUpdate()
{
	m_bLockUpdate++;
}

void SVGPathSegList::UnlockUpdate()
{
	m_bLockUpdate--;
	ASSERT(m_bLockUpdate >= 0);
	if (m_bLockUpdate == 0)
	{
		if (m_nChanges > 0)
		{
			if (m_pListener)
			{
				m_pListener->OnPathSegListChange(this);
			}
			m_nChanges = 0;
		}
	}
}

#include <math.h>

double fxDiv2(double v1, double v2)
{
	return (v1+v2)/2;
}

/****************************************************************************
 *  FUNCTION   : AppendQuadBSplineToBezier
 *
 *  PURPOSE    : Converts Quadratic spline segments into their Bezier point 
 *               representation and appends them to a list of Bezier points. 
 *
 *               WARNING - The array must have at least one valid
 *               start point prior to the address of the element passed.
 *
 *  RETURNS    : number of Bezier points added to the POINT array.
 ****************************************************************************/ 
UINT SVGPathSegList::AppendQuadBSplineToBezier(gm::PointD start, gm::PointD* lpCurve, int count)
{
	ASSERT(0);
	return 0;
#if 0
	WORD		i;
	UINT		cTotal = 0;
	PointD	spline[3];  // a Quadratic is defined by 3 points
	PointD	bezier[4];  // a Cubic by 4

	// The initial A point is on the curve.
	spline[0].X = start.X;
	spline[0].Y = start.Y;
	
	for (i = 0; i < count; )
	{
		// The B point.
		spline[1].X = lpCurve[i].X;
		spline[1].Y = lpCurve[i].Y;

		i++;
		
		// Calculate the C point.
		if (i == (count - 1))
		{
			// The last C point is described explicitly
			// i.e. it is on the curve.
			spline[2].X = lpCurve[i].X;
			spline[2].Y = lpCurve[i].Y;

			i++;
		}     
		else
		{
			// C is midpoint between B and next B point
			// because that is the on curve point of 
			// a Quadratic B-Spline.
			spline[2].X = fxDiv2(
				lpCurve[i-1].X,
				lpCurve[i].X);

			spline[2].Y = fxDiv2(
				lpCurve[i-1].Y,
				lpCurve[i].Y);
		}
		
		// convert the Q Spline to a Bezier
		MakeBezierFromQBSpline( bezier, spline );
		
	// append the Bezier to the existing ones

		CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
		CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
		outcubicabs->m_x = bezier[3].X; outcubicabs->m_y = bezier[3].Y;
		outcubicabs->m_x1 = bezier[1].X; outcubicabs->m_y1 = bezier[1].Y;
		outcubicabs->m_x2 = bezier[2].X; outcubicabs->m_y2 = bezier[2].Y;
//		/*pt->*/appendItem(outcubicabs, NULL);
		outcubicabs->m_pSegList = this;
		outcubicabs->AddRef();
		m_items.Add(outcubicabs);

		// New A point for next slice of spline is the 
		// on curve C point of this B-Spline
		spline[0] = spline[2];
	}
	
	return cTotal;
#endif
}

		/*
			s and S

			Draws a cubic Bézier curve from the current point to (x,y). The first
			control point is assumed to be the reflection of the second control
			point on the previous command relative to the current point.
			(If there is no previous command or if the previous command was not
			an C, c, S or s, assume the first control point is coincident with
			the current point.) (x2,y2) is the second control point
			(i.e., the control point at the end of the curve). S (uppercase)
			indicates that absolute coordinates will follow; s (lowercase)
			indicates that relative coordinates will follow. Multiple sets of
			coordinates may be specified to draw a polybezier. At the end of
			the command, the new current point becomes the final (x,y) coordinate
			pair used in the polybezier.
		*/
#if 0
void SVGPathSegList::CubicSmooth(double x, double y, double x2, double y2, double& oldx, double& oldy, double& oldx2, double& oldy2, LSVGPathSegType oldsegType)
{
#if 0
	double apt_x = oldx2;
	double apt_y = oldy2;

	double ppt_x = oldx;
	double ppt_y = oldy;

	double dx = apt_x-ppt_x;
	double dy = apt_y-ppt_y;
	double distance = sqrt(dx*dx+dy*dy);
	double distance2 = distance;

	if (distance2 == 0.0) distance2 = 0.0001;
	if (dy < 0) distance2 =-distance2;
	double angle = acos(dx/distance2);
	if (dy < 0) angle += M_PI;

	angle += M_PI;	// Add 180 degrees (Reflection)

	PointD	pt3;
	pt3.X = cos(angle)*distance+ppt_x;
	pt3.Y = sin(angle)*distance+ppt_y;

	CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
	CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
	outcubicabs->m_x1 = pt3.X;			outcubicabs->m_y1 = pt3.Y;
	outcubicabs->m_x2 = x2;				outcubicabs->m_y2 = y2;
	outcubicabs->m_x = x;					outcubicabs->m_y = y;

	outcubicabs->m_pSegList = this;
	outcubicabs->AddRef();
	m_items.Add(outcubicabs);

	oldx = x;
	oldy = y;
	oldx2 = pt3.X;
	oldy2 = pt3.Y;
#endif

	CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
	CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
	outcubicabs->m_x1 = oldx + (oldx-oldx2);	outcubicabs->m_y1 = oldy + (oldy-oldy2);
	outcubicabs->m_x2 = x2;				outcubicabs->m_y2 = y2;
	outcubicabs->m_x = x;					outcubicabs->m_y = y;

	outcubicabs->m_pSegList = this;
	outcubicabs->AddRef();
	m_items.Add(outcubicabs);

	oldx = x;
	oldy = y;
	oldx2 = x2;
	oldy2 = y2;
}
#endif

/*
Draws a quadratic Bézier curve from the current point to (x,y). The control
point is assumed to be the reflection of the control point on the previous
command relative to the current point. (If there is no previous command or
if the previous command was not a Q, q, T or t, assume the control point is
coincident with the current point.) T (uppercase) indicates that absolute
coordinates will follow; t (lowercase) indicates that relative coordinates
will follow. At the end of the command, the new current point becomes the
final (x,y) coordinate pair used in the polybezier.
*/
void SVGPathSegList::QuadraticSmooth(double x, double y, double& oldx, double& oldy, double& oldx2, double& oldy2, SVGPathSegType oldsegType)
{
	double apt_x = oldx2;
	double apt_y = oldy2;

	double ppt_x = oldx;
	double ppt_y = oldy;

	double dx = apt_x-ppt_x;
	double dy = apt_y-ppt_y;
	double distance = sqrt(dx*dx+dy*dy);
	double distance2 = distance;

	if (distance2 == 0.0) distance2 = 0.0001;
	if (dy < 0) distance2 =-distance2;
	double angle = acos(dx/distance2);
	if (dy < 0) angle += M_PI;

	angle += M_PI;	// Add 180 degrees (Reflection)

	gm::PointD	pt3;
	pt3.X = (cos(angle)*distance)+ppt_x;
	pt3.Y = (sin(angle)*distance)+ppt_y;

	gm::PointD start = gm::PointD(oldx, oldy);
	gm::PointD points[2] =
	{
		gm::PointD(pt3.X, pt3.Y),
		gm::PointD(x, y),
	};

	AppendQuadBSplineToBezier(start, points, 2);

	oldx = x;
	oldy = y;
	oldx2 = pt3.X;
	oldy2 = pt3.Y;
}

double vangle(gm::vector2d& u, gm::vector2d& v)
{
	int sgn = SGN(u[0]*v[1] - u[1]*v[0]);

	double d1 = gm::dot(u, v);

	double d2 = sqrt(u.lengthSquared() * v.lengthSquared());
	ASSERT(d2 != 0);

	double a = d1 / d2;
	ASSERT(a >= -1 && a <= 1);

	return acos(a) * sgn * (180 / M_PI);
}

/////////////////////////////////////////////////////////////////////////////
// SVGPathSegList

void SVGPathSegList::NormalizePathSegList(SVGPathSegList* inseglist/*, ILSVGPathSegList* outseglist*/)
{
	ASSERT(0);
#if 0
	long numberOfItems = inseglist->get_numberOfItems();

	double oldx = 0, oldy = 0;
	double oldx2 = 0, oldy2 = 0;
	double last_movex = 0, last_movey = 0;
	LSVGPathSegType oldsegType;

	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ILSVGPathSeg> inseg;
		inseglist->getItem(i, &inseg);

		LSVGPathSegType segType;
		inseg->get_pathSegType(&segType);

		switch (segType)
		{
		case PATHSEG_MOVETO_ABS:
			{
				CComQIPtr<ILSVGPathSegMovetoAbs> inmovetoabs = inseg;

				double x, y;
				inmovetoabs->get_x(&x);
				inmovetoabs->get_y(&y);

				CComObject<CLSVGPathSegMovetoAbs>* outmovetoabs;
				CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&outmovetoabs);
				outmovetoabs->m_x = x;
				outmovetoabs->m_y = y;
				outmovetoabs->m_pSegList = this;
				outmovetoabs->AddRef();
				m_items.Add(outmovetoabs);

				last_movex = oldx = oldx2 = x;
				last_movey = oldy = oldy2 = y;
			}
			break;

		case PATHSEG_MOVETO_REL:
			{
				CComQIPtr<ILSVGPathSegMovetoRel> inmovetorel = inseg;
				
				double x, y;
				inmovetorel->get_x(&x);
				inmovetorel->get_y(&y);
				
				x += oldx;
				y += oldy;

				CComObject<CLSVGPathSegMovetoAbs>* outmovetoabs;
				CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&outmovetoabs);
				outmovetoabs->m_x = x;
				outmovetoabs->m_y = y;
				outmovetoabs->m_pSegList = this;
				outmovetoabs->AddRef();
				m_items.Add(outmovetoabs);

				last_movex = oldx = oldx2 = x;
				last_movey = oldy = oldy2 = y;
			}
			break;
			
		case PATHSEG_LINETO_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoAbs> inlinetoabs = inseg;
				
				double x, y;
				inlinetoabs->get_x(&x);
				inlinetoabs->get_y(&y);
				
				CComObject<CLSVGPathSegLinetoAbs>* outlinetoabs;
				CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&outlinetoabs);
				outlinetoabs->m_x = x;
				outlinetoabs->m_y = y;
				outlinetoabs->m_pSegList = this;
				outlinetoabs->AddRef();
				m_items.Add(outlinetoabs);

				oldx = oldx2 = x;
				oldy = oldy2 = y;
			}
			break;
			
		case PATHSEG_LINETO_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoRel> inlinetorel = inseg;
				
				double x, y;
				inlinetorel->get_x(&x);
				inlinetorel->get_y(&y);
				
				x += oldx;
				y += oldy;

				CComObject<CLSVGPathSegLinetoAbs>* outlinetoabs;
				CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&outlinetoabs);
				outlinetoabs->m_x = x;
				outlinetoabs->m_y = y;
//				/*outseglist->*/appendItem(outlinetoabs, NULL);
				outlinetoabs->m_pSegList = this;
				outlinetoabs->AddRef();
				m_items.Add(outlinetoabs);

				oldx = oldx2 = x;
				oldy = oldy2 = y;
			}
			break;

		case PATHSEG_CURVETO_CUBIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> incubictoabs = inseg;
				
				double x, y, x1, y1, x2, y2;
				incubictoabs->get_x(&x);
				incubictoabs->get_y(&y);
				incubictoabs->get_x1(&x1);
				incubictoabs->get_y1(&y1);
				incubictoabs->get_x2(&x2);
				incubictoabs->get_y2(&y2);
				
				CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
				CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
				outcubicabs->m_x = x;
				outcubicabs->m_y = y;
				outcubicabs->m_x1 = x1;
				outcubicabs->m_y1 = y1;
				outcubicabs->m_x2 = x2;
				outcubicabs->m_y2 = y2;
				outcubicabs->m_pSegList = this;
			//	/*outseglist->*/appendItem(outcubicabs, NULL);
				outcubicabs->AddRef();
				m_items.Add(outcubicabs);

				oldx = x;
				oldy = y;
				oldx2 = x2;
				oldy2 = y2;
			}
			break;
			
		case PATHSEG_CURVETO_CUBIC_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicRel> incubictorel = inseg;

				double x, y, x1, y1, x2, y2;
				incubictorel->get_x(&x);
				incubictorel->get_y(&y);
				incubictorel->get_x1(&x1);
				incubictorel->get_y1(&y1);
				incubictorel->get_x2(&x2);
				incubictorel->get_y2(&y2);

				x += oldx;
				y += oldy;
				x1 += oldx;
				y1 += oldy;
				x2 += oldx;
				y2 += oldy;

				CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
				CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
				outcubicabs->set_x(x);
				outcubicabs->set_y(y);
				outcubicabs->set_x1(x1);
				outcubicabs->set_y1(y1);
				outcubicabs->set_x2(x2);
				outcubicabs->set_y2(y2);
				outcubicabs->m_pSegList = this;
				outcubicabs->AddRef();
				m_items.Add(outcubicabs);

				oldx = x;
				oldy = y;
				oldx2 = x2;
				oldy2 = y2;
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticAbs> inquadseg = inseg;
				
				double x, y, x1, y1;
				inquadseg->get_x(&x);
				inquadseg->get_y(&y);
				inquadseg->get_x1(&x1);
				inquadseg->get_y1(&y1);

#if 0
				PointD points[2] =
				{
					PointD(x1, y1),
					PointD(x, y),
				};

				PointD start = PointD(oldx, oldy);

				AppendQuadBSplineToBezier(/*outseglist,*/ start, points, 2);
#endif

				PointD	spline[3];  // a Quadratic is defined by 3 points
				PointD	bezier[4];  // a Cubic by 4

				// The initial A point is on the curve.
				spline[0].X = oldx;
				spline[0].Y = oldy;
				
				// The B point.
				spline[1].X = x1;
				spline[1].Y = y1;
				
				// The last C point is described explicitly
				// i.e. it is on the curve.
				spline[2].X = x;
				spline[2].Y = y;
				
				// convert the Q Spline to a Bezier
				MakeBezierFromQBSpline( bezier, spline );
				
			// append the Bezier to the existing ones

				CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
				CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
				outcubicabs->m_x = bezier[3].X; outcubicabs->m_y = bezier[3].Y;
				outcubicabs->m_x1 = bezier[1].X; outcubicabs->m_y1 = bezier[1].Y;
				outcubicabs->m_x2 = bezier[2].X; outcubicabs->m_y2 = bezier[2].Y;
		//		/*pt->*/appendItem(outcubicabs, NULL);
				outcubicabs->m_pSegList = this;
				outcubicabs->AddRef();
				m_items.Add(outcubicabs);

				oldx = x;
				oldy = y;
				oldx2 = x1;//bezier[2].X;
				oldy2 = y1;//bezier[2].Y;
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticRel> inquadseg = inseg;

				double x, y, x1, y1;
				inquadseg->get_x(&x);
				inquadseg->get_y(&y);
				inquadseg->get_x1(&x1);
				inquadseg->get_y1(&y1);

				x += oldx;
				y += oldy;
				x1 += oldx;
				y1 += oldy;

#if 0
				PointD points[2] =
				{
					PointD(x1, y1),
					PointD(x, y),
				};

				PointD start = PointD(oldx, oldy);

				AppendQuadBSplineToBezier(start, points, 2);

				oldx = x;
				oldy = y;
				oldx2 = x1;
				oldy2 = y1;
#endif

				PointD	spline[3];  // a Quadratic is defined by 3 points
				PointD	bezier[4];  // a Cubic by 4

				// The initial A point is on the curve.
				spline[0].X = oldx;
				spline[0].Y = oldy;
				
				// The B point.
				spline[1].X = x1;
				spline[1].Y = y1;
				
				// The last C point is described explicitly
				// i.e. it is on the curve.
				spline[2].X = x;
				spline[2].Y = y;
				
				// convert the Q Spline to a Bezier
				MakeBezierFromQBSpline( bezier, spline );
				
			// append the Bezier to the existing ones

				CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
				CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
				outcubicabs->m_x = bezier[3].X; outcubicabs->m_y = bezier[3].Y;
				outcubicabs->m_x1 = bezier[1].X; outcubicabs->m_y1 = bezier[1].Y;
				outcubicabs->m_x2 = bezier[2].X; outcubicabs->m_y2 = bezier[2].Y;
		//		/*pt->*/appendItem(outcubicabs, NULL);
				outcubicabs->m_pSegList = this;
				outcubicabs->AddRef();
				m_items.Add(outcubicabs);

				oldx = x;
				oldy = y;
				oldx2 = x1;//bezier[2].X;
				oldy2 = y1;//bezier[2].Y;
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticSmoothAbs> insmoothseg = inseg;

				double x, y;
				insmoothseg->get_x(&x);
				insmoothseg->get_y(&y);

				QuadraticSmooth(x, y, oldx, oldy, oldx2, oldy2, oldsegType);
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticSmoothRel> insmoothseg = inseg;

				double x, y;
				insmoothseg->get_x(&x);
				insmoothseg->get_y(&y);
				x += oldx;
				y += oldy;

				QuadraticSmooth(x, y, oldx, oldy, oldx2, oldy2, oldsegType);
			}
			break;

		case PATHSEG_LINETO_HORIZONTAL_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoHorizontalAbs> inlinetohabs = inseg;

				double x;
				inlinetohabs->get_x(&x);

				CComObject<CLSVGPathSegLinetoAbs>* outlinetoabs;
				CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&outlinetoabs);
				outlinetoabs->set_x(x);
				outlinetoabs->set_y(oldy);
				outlinetoabs->m_pSegList = this;
				outlinetoabs->AddRef();
				m_items.Add(outlinetoabs);

				oldx = x;
				oldx2 = x;
			}
			break;

		case PATHSEG_LINETO_HORIZONTAL_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoHorizontalRel> inlinetohrel = inseg;
				
				double x;
				inlinetohrel->get_x(&x);
				
				x += oldx;

				CComObject<CLSVGPathSegLinetoAbs>* outlinetoabs;
				CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&outlinetoabs);
				outlinetoabs->set_x(x);
				outlinetoabs->set_y(oldy);
				outlinetoabs->m_pSegList = this;
				outlinetoabs->AddRef();
				m_items.Add(outlinetoabs);

				oldx = x;
				oldx2 = x;
			}
			break;

		case PATHSEG_LINETO_VERTICAL_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoVerticalAbs> inlinetovabs = inseg;
				
				double y;
				inlinetovabs->get_y(&y);
				
				CComObject<CLSVGPathSegLinetoAbs>* outlinetoabs;
				CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&outlinetoabs);
				outlinetoabs->put_x(oldx);
				outlinetoabs->put_y(y);
				outlinetoabs->m_pSegList = this;
				outlinetoabs->AddRef();
				m_items.Add(outlinetoabs);

				oldy = y;
				oldy2 = y;
			}
			break;

		case PATHSEG_LINETO_VERTICAL_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoVerticalRel> inlinetovrel = inseg;

				double y;
				inlinetovrel->get_y(&y);

				y += oldy;

				CComObject<CLSVGPathSegLinetoAbs>* outlinetoabs;
				CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&outlinetoabs);
				outlinetoabs->set_x(oldx);
				outlinetoabs->set_y(y);
				outlinetoabs->m_pSegList = this;
				outlinetoabs->AddRef();
				m_items.Add(outlinetoabs);

				oldy = y;
				oldy2 = y;
			}
			break;

		case PATHSEG_CURVETO_CUBIC_SMOOTH_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicSmoothAbs> insmoothseg = inseg;

				double x, y;
				double x2, y2;
				insmoothseg->get_x(&x);
				insmoothseg->get_y(&y);
				insmoothseg->get_x2(&x2);
				insmoothseg->get_y2(&y2);

			//	CubicSmooth(x, y, x2, y2, oldx, oldy, oldx2, oldy2, oldsegType);

				CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
				CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
				outcubicabs->m_x1 = oldx + (oldx-oldx2);	outcubicabs->m_y1 = oldy + (oldy-oldy2);
				outcubicabs->m_x2 = x2;				outcubicabs->m_y2 = y2;
				outcubicabs->m_x = x;					outcubicabs->m_y = y;

				outcubicabs->m_pSegList = this;
				outcubicabs->AddRef();
				m_items.Add(outcubicabs);

				oldx = x;
				oldy = y;
				oldx2 = x2;
				oldy2 = y2;
			}
			break;

		case PATHSEG_CURVETO_CUBIC_SMOOTH_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicSmoothRel> insmoothseg = inseg;

				double x, y;
				double x2, y2;
				insmoothseg->get_x(&x);
				insmoothseg->get_y(&y);
				insmoothseg->get_x2(&x2);
				insmoothseg->get_y2(&y2);

				x += oldx;
				y += oldy;
				x2 += oldx;
				y2 += oldy;

				CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
				CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
				outcubicabs->m_x1 = oldx + (oldx-oldx2);	outcubicabs->m_y1 = oldy + (oldy-oldy2);
				outcubicabs->m_x2 = x2;				outcubicabs->m_y2 = y2;
				outcubicabs->m_x = x;					outcubicabs->m_y = y;

				outcubicabs->m_pSegList = this;
				outcubicabs->AddRef();
				m_items.Add(outcubicabs);

				oldx = x;
				oldy = y;
				oldx2 = x2;
				oldy2 = y2;

		//		CubicSmooth(x, y, x2, y2, oldx, oldy, oldx2, oldy2, oldsegType);
			}
			break;

		case PATHSEG_ARC_ABS:
		case PATHSEG_ARC_REL:
			{
				// I think I've copied the algorithm from somewhere, but can't remember
				// where...Sorry about missing credits

				double x1 = oldx;
				double y1 = oldy;

				double x2, y2;
				double rx, ry;
				double angle;
				bool largeArcFlag;
				bool sweepFlag;

				if (segType == PATHSEG_ARC_REL)
				{
					CComQIPtr<ILSVGPathSegArcRel> inarcseg = inseg;

					inarcseg->get_x(&x2);
					inarcseg->get_y(&y2);
					inarcseg->get_r1(&rx);
					inarcseg->get_r2(&ry);
					inarcseg->get_angle(&angle);
					inarcseg->get_largeArcFlag(&largeArcFlag);
					inarcseg->get_sweepFlag(&sweepFlag);

					x2 += oldx;
					y2 += oldy;
				}
				else
				{
					CComQIPtr<ILSVGPathSegArcAbs> inarcseg = inseg;

					inarcseg->get_x(&x2);
					inarcseg->get_y(&y2);
					inarcseg->get_r1(&rx);
					inarcseg->get_r2(&ry);
					inarcseg->get_angle(&angle);
					inarcseg->get_largeArcFlag(&largeArcFlag);
					inarcseg->get_sweepFlag(&sweepFlag);
				}

			// If rX = 0 or rY = 0, then treat this as a straight line from (x1, y1) to (x2, y2) and stop

				if (rx == 0 || ry == 0)
				{
					CComObject<CLSVGPathSegLinetoAbs>* linetoabs;
					CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&linetoabs);
					linetoabs->AddRef();
					linetoabs->m_x = x2;
					linetoabs->m_y = y2;
					linetoabs->m_pSegList = this;
					m_items.Add(linetoabs);
				}
				else
				{
					gmVector2 xy_ = gmMatrix3::rotate(angle).inverse().transform(gmVector2((x1-x2)/2, (y1-y2)/2));
					double x1_ = xy_[0];
					double y1_ = xy_[1];

				// Adjust rx, ry
					rx = fabs(rx);
					ry = fabs(ry);

					double t = (x1_*x1_)/(rx*rx) + (y1_*y1_)/(ry*ry);
					if (t > 1)
					{
						rx = sqrt(t)*rx;
						ry = sqrt(t)*ry;
					}

					gmVector2 cxy_ = (largeArcFlag != sweepFlag? 1: -1) *
						sqrt(	((rx*rx * ry*ry) - (rx*rx * y1_*y1_) - (ry*ry * x1_*x1_)) /
								((rx*rx * y1_*y1_) + (ry*ry * x1_*x1_))
								) *
								gmVector2(rx*y1_ / ry, - (ry*x1_ / rx));

					double cx_ = cxy_[0];
					double cy_ = cxy_[1];

					double startAngle = vangle(gmVector2(1, 0), gmVector2((x1_-cx_)/rx, (y1_-cy_)/ry));

					double sweepAngle = vangle(
						gmVector2((x1_-cx_)/rx, (y1_-cy_)/ry),
						gmVector2((-x1_-cx_)/rx, (-y1_-cy_)/ry));

					/*
					while (sweepAngle <= -360) sweepAngle += 360;
					while (sweepAngle >= 360)sweepAngle -= 360;
					*/

					if (sweepFlag == 0 && sweepAngle > 0)
						sweepAngle -= 360;
					else if (sweepFlag == 1 && sweepAngle < 0)
						sweepAngle += 360;

					{
						double startAng = startAngle;
						double extent = sweepAngle;
						{
							int Nfrag;

							double fragAngle;

							if (fabs(extent) <= 90)
							{
								fragAngle = extent;
								Nfrag = 1;
							}
							else
							{
								Nfrag = int(ceil(fabs(extent)/90.));
								fragAngle = extent / Nfrag;
							}

							double halfAng = fragAngle * M_PI / 360;
							double kappa = 4. / 3. * (1. - cos(halfAng)) / sin(halfAng);

							gmMatrix3 mat = gmMatrix3::rotate(angle) * gmMatrix3::translate((x1+x2)/2, (y1+y2)/2);

							for (int i = 0; i < Nfrag; i++)
							{
								double theta0 = (startAng + i*fragAngle) * M_PI / 180;
								double theta1 = (startAng + (i+1)*fragAngle) * M_PI / 180;

								double bx1 = cx_ + rx * (cos(theta0) - kappa * sin(theta0));
								double by1 = cy_ + ry * (sin(theta0) + kappa * cos(theta0));
								double bx2 = cx_ + rx * (cos(theta1) + kappa * sin(theta1));
								double by2 = cy_ + ry * (sin(theta1) - kappa * cos(theta1));
								double bx3 = cx_ + rx * cos(theta1);
								double by3 = cy_ + ry * sin(theta1);

								gmVector2 v1 = mat.transform(gmVector2(bx1, by1));
								gmVector2 v2 = mat.transform(gmVector2(bx2, by2));
								gmVector2 v3 = mat.transform(gmVector2(bx3, by3));

								CComObject<CLSVGPathSegCurvetoCubicAbs>* outcubicabs;
								CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&outcubicabs);
								outcubicabs->m_x1 = v1[0];
								outcubicabs->m_y1 = v1[1];
								outcubicabs->m_x2 = v2[0];
								outcubicabs->m_y2 = v2[1];
								outcubicabs->m_x = v3[0];
								outcubicabs->m_y = v3[1];

								outcubicabs->AddRef();
								outcubicabs->m_pSegList = this;
								m_items.Add(outcubicabs);
								
								oldx = v3[0];
								oldy = v3[1];
								oldx2 = v2[0];
								oldy2 = v2[1];
							}
						}
					}
				}
			}
			break;

		case PATHSEG_CLOSEPATH:
			{
				CComObject<CLSVGPathSegClosePath>* outclose;
				CComObject<CLSVGPathSegClosePath>::CreateInstance(&outclose);
				outclose->AddRef();
				outclose->m_pSegList = this;
				m_items.Add(outclose);

				oldx = last_movex;
				oldy = last_movey;
				oldx2 = last_movex;
				oldy2 = last_movey;
			}
			break;

		default:
			ASSERT(0);
		}

		oldsegType = segType;
	}
#endif
}

/////////////////////////////////

bool SVGPathSegList::ParsePathData(StringIn str_pathdata)
{
	ASSERT(0);
	bool success = false;	// Assume error
#if 0
	const WCHAR* ptext = str_pathdata->c_str();



	/*segList->*/clear();	// ??

	const OLECHAR* p = ptext;
	while (*p)	// Process entire string
	{
		while (*p && iswspace(*p)) p++;
		if (*p == 0) break;

		OLECHAR op = *p++;	// Get operation
		if (!iswalpha(op))
		{
			MessageBox(NULL, "illegal path data op", "SVG", MB_OK);
			goto Exit;	// Illegal operation
		}

	// Get values
		CArray<double,double> dbl_values;

		while (iswspace(*p)) p++;

		while (*p)
		{
			if (!*p || iswalpha(*p)) break;

			const OLECHAR* p2 = p;
			double fval = getfnumber(&p2);
			if (p2 == NULL)
			{
			//	ASSERT(0);
				goto Exit;
			}

			p = p2;

			dbl_values.Add(fval);

			while (iswspace(*p)) p++;
			if (*p == L',') p++;
			while (iswspace(*p)) p++;

		//	if (!*p || iswalpha(*p)) break;
		}

		switch (op)
		{
		case 'm':	// relative moveto
		case 'M':	// absolute moveto
		case 'l':	// relative lineto
		case 'L':	// absolute lineto
		case 'c':	// Relative Cubic bezier
		case 'C':	// Absolute Cubic bezier
		case 'q':	// Relative quadratic bezier
		case 'Q':	// Absolute quadratic bezier
		case 's':	// Relative shorthand/smooth curveto
		case 'S':	// Absolute shorthand/smooth curveto
		case 't':	// Relative smooth quadratic
		case 'T':	// Absolute smooth quadratic
			{
				if ((dbl_values.GetSize() % 2) != 0)
				{
					ASSERT(0);
					goto Exit;
				}

				CArray <PointD,PointD&> points;
				int npoints = dbl_values.GetSize()/2;
				points.SetSize(npoints);

				for (int n = 0; n < npoints; n++)
				{
					points[n].X = dbl_values[n*2+0];
					points[n].Y = dbl_values[n*2+1];
				}

				switch (op)
				{
/*
If a moveto is followed by multiple pairs of coordinates, the subsequent
pairs are treated as implicit lineto commands.
*/

				case 'm':	// Relative moveto
					{
						// TODO
				/* If a relative moveto (m) appears as the first element of the
 				  path, then it is treated as a pair of absolute coordinates
				  */

						CComObject<CLSVGPathSegMovetoRel>* seg_movetorel;
						CComObject<CLSVGPathSegMovetoRel>::CreateInstance(&seg_movetorel);
						//pathElement->createSVGPathSegMovetoRel(points[0].x, points[0].y, &seg_movetorel);
						seg_movetorel->AddRef();
						seg_movetorel->m_x = points[0].X;
						seg_movetorel->m_y = points[0].Y;

						seg_movetorel->m_pSegList = this;
						m_items.Add(seg_movetorel);//segList->appendItem(seg_movetorel, NULL);

						for (int i = 1; i < npoints; i++)
						{
							CComObject<CLSVGPathSegLinetoAbs>* seg_linetoabs;
							CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg_linetoabs);
							seg_linetoabs->AddRef();
							seg_linetoabs->m_x = points[i].X;
							seg_linetoabs->m_y = points[i].Y;
							//pathElement->createSVGPathSegLinetoAbs(points[i].x, points[i].y, &seg_linetoabs);
							//segList->appendItem(seg_linetoabs, NULL);
							seg_linetoabs->m_pSegList = this;
							m_items.Add(seg_linetoabs);//segList->appendItem(seg_movetorel, NULL);
						}
					}
					break;

				case 'M':	// Absolute moveto
					{
						CComObject<CLSVGPathSegMovetoAbs>* seg_movetoabs;
						CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&seg_movetoabs);
						seg_movetoabs->AddRef();
						seg_movetoabs->m_x = points[0].X;
						seg_movetoabs->m_y = points[0].Y;
						seg_movetoabs->m_pSegList = this;
						m_items.Add(seg_movetoabs);

						for (int i = 1; i < npoints; i++)
						{
							CComObject<CLSVGPathSegLinetoAbs>* seg_linetoabs;
							CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg_linetoabs);
							seg_linetoabs->AddRef();
							seg_linetoabs->m_x = points[i].X;
							seg_linetoabs->m_y = points[i].Y;

							seg_movetoabs->m_pSegList = this;
							m_items.Add(seg_linetoabs);//segList->appendItem(seg_movetorel, NULL);

							//pathElement->createSVGPathSegLinetoAbs(points[i].x, points[i].y, &seg_linetoabs);
							//segList->appendItem(seg_linetoabs, NULL);
						}
					}
					break;

				case 'l':	// Relative lineto
					{
						for (int i = 0; i < npoints; i++)
						{
							CComObject<CLSVGPathSegLinetoRel>* seg_linetorel;
							CComObject<CLSVGPathSegLinetoRel>::CreateInstance(&seg_linetorel);
							seg_linetorel->AddRef();
							seg_linetorel->m_x = points[i].X;
							seg_linetorel->m_y = points[i].Y;

							seg_linetorel->m_pSegList = this;
							m_items.Add(seg_linetorel);
						}
					}
					break;

				case 'L':	// Absolute lineto
					{
						for (int i = 0; i < npoints; i++)
						{
							CComObject<CLSVGPathSegLinetoAbs>* seg_linetoabs;
							CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg_linetoabs);
							seg_linetoabs->AddRef();
							seg_linetoabs->m_x = points[i].X;
							seg_linetoabs->m_y = points[i].Y;
							seg_linetoabs->m_pSegList = this;
							m_items.Add(seg_linetoabs);//segList->appendItem(seg_movetorel, NULL);
						}
					}
					break;

				case 'c':	// relative Cubic bezier
					{
						if ((npoints % 3) != 0)
						{
							ASSERT(0);
							goto Exit;
						}

						for (int i = 0; i < npoints; i += 3)
						{
							CComObject<CLSVGPathSegCurvetoCubicRel>* seg;
							CComObject<CLSVGPathSegCurvetoCubicRel>::CreateInstance(&seg);
							seg->AddRef();
							seg->m_x = points[i+2].X;
							seg->m_y = points[i+2].Y;
							seg->m_x1 = points[i].X;
							seg->m_y1 = points[i].Y;
							seg->m_x2 = points[i+1].X;
							seg->m_y2 = points[i+1].Y;
							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;

				case 'C':	// absolute Cubic bezier
					{
						if ((npoints % 3) != 0)
						{
							ASSERT(0);
							goto Exit;
						}

						for (int i = 0; i < npoints; i += 3)
						{
							CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
							CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);
							seg->AddRef();
							seg->m_x = points[i+2].X;
							seg->m_y = points[i+2].Y;
							seg->m_x1 = points[i].X;
							seg->m_y1 = points[i].Y;
							seg->m_x2 = points[i+1].X;
							seg->m_y2 = points[i+1].Y;

							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;

				case 'q':
					{
						if ((npoints % 2) != 0)
						{
							ASSERT(0);
							goto Exit;
						}

						for (int i = 0; i < npoints; i += 2)
						{
							CComObject<CLSVGPathSegCurvetoQuadraticRel>* seg;
							CComObject<CLSVGPathSegCurvetoQuadraticRel>::CreateInstance(&seg);
							seg->AddRef();
							seg->m_x = points[i+1].X;
							seg->m_y = points[i+1].Y;
							seg->m_x1 = points[i].X;
							seg->m_y1 = points[i].Y;

							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;

				case 'Q':
					{
						if ((npoints % 2) != 0)
						{
							ASSERT(0);
							goto Exit;
						}

						for (int i = 0; i < npoints; i += 2)
						{
							CComObject<CLSVGPathSegCurvetoQuadraticAbs>* seg;
							CComObject<CLSVGPathSegCurvetoQuadraticAbs>::CreateInstance(&seg);
							seg->AddRef();

							seg->m_x = points[i+1].X;
							seg->m_y = points[i+1].Y;
							seg->m_x1 = points[i].X;
							seg->m_y1 = points[i].Y;
							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;


		/*
			s and S

			Draws a cubic Bézier curve from the current point to (x,y). The first
			control point is assumed to be the reflection of the second control
			point on the previous command relative to the current point.
			(If there is no previous command or if the previous command was not
			an C, c, S or s, assume the first control point is coincident with
			the current point.) (x2,y2) is the second control point
			(i.e., the control point at the end of the curve). S (uppercase)
			indicates that absolute coordinates will follow; s (lowercase)
			indicates that relative coordinates will follow. Multiple sets of
			coordinates may be specified to draw a polybezier. At the end of
			the command, the new current point becomes the final (x,y) coordinate
			pair used in the polybezier.
		*/

				case 's':
					{
						if ((npoints % 2) != 0)
						{
							ASSERT(0);
							goto Exit;
						}

						for (int i = 0; i < npoints; i += 2)
						{
							CComObject<CLSVGPathSegCurvetoCubicSmoothRel>* seg;
							CComObject<CLSVGPathSegCurvetoCubicSmoothRel>::CreateInstance(&seg);
							seg->AddRef();
							//pathElement->createSVGPathSegCurvetoCubicSmoothRel(points[i+1].x, points[i+1].y, points[i].x, points[i].y, &seg);
							seg->m_x = points[i+1].X;
							seg->m_y = points[i+1].Y;
							seg->m_x2 = points[i].X;
							seg->m_y2 = points[i].Y;
							seg->m_pSegList = this;
							m_items.Add(seg);
//							segList->appendItem(seg, NULL);
						}
					}
					break;

				case 'S':
					{
						if ((npoints % 2) != 0)
						{
							ASSERT(0);
							goto Exit;
						}

						for (int i = 0; i < npoints; i += 2)
						{
							CComObject<CLSVGPathSegCurvetoCubicSmoothAbs>* seg;
							CComObject<CLSVGPathSegCurvetoCubicSmoothAbs>::CreateInstance(&seg);
							seg->AddRef();

							seg->m_x = points[i+1].X;
							seg->m_y = points[i+1].Y;
							seg->m_x2 = points[i].X;
							seg->m_y2 = points[i].Y;

							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;

				case 't':
					{
						if ((npoints % 1) != 0)
						{
							ASSERT(0);
							goto Exit;
						}

						for (int i = 0; i < npoints; i += 1)
						{
							CComObject<CLSVGPathSegCurvetoQuadraticSmoothRel>* seg;
							CComObject<CLSVGPathSegCurvetoQuadraticSmoothRel>::CreateInstance(&seg);
							seg->AddRef();
							seg->m_x = points[i].X;
							seg->m_y = points[i].Y;

							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;

				case 'T':
					{
						if ((npoints % 1) != 0)
						{
							ASSERT(0);
							goto Exit;
						}

						for (int i = 0; i < npoints; i += 1)
						{
							CComObject<CLSVGPathSegCurvetoQuadraticSmoothAbs>* seg;
							CComObject<CLSVGPathSegCurvetoQuadraticSmoothAbs>::CreateInstance(&seg);
							seg->AddRef();

							seg->m_x = points[i].X;
							seg->m_y = points[i].Y;

							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;
				}
			}
			break;

		case 'h':	// Relative Horizontal line
		case 'H':	// Absolute Horizontal line
		case 'v':	// Relative Vertical line
		case 'V':	// Absolute Vertical line
			{
				int npoints = dbl_values.GetSize();

				switch (op)
				{
				case 'h':
					{
						for (int i = 0; i < npoints; i++)
						{
							CComObject<CLSVGPathSegLinetoHorizontalRel>* seg;
							CComObject<CLSVGPathSegLinetoHorizontalRel>::CreateInstance(&seg);
							seg->AddRef();
							seg->m_x = dbl_values[i];
							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;

				case 'v':
					{
						for (int i = 0; i < npoints; i++)
						{
							CComObject<CLSVGPathSegLinetoVerticalRel>* seg;
							CComObject<CLSVGPathSegLinetoVerticalRel>::CreateInstance(&seg);
							seg->AddRef();
							
							seg->m_y = dbl_values[i];
							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;

				case 'H':
					{
						for (int i = 0; i < npoints; i++)
						{
							CComObject<CLSVGPathSegLinetoHorizontalAbs>* seg;
							CComObject<CLSVGPathSegLinetoHorizontalAbs>::CreateInstance(&seg);
							seg->AddRef();

							seg->m_x = dbl_values[i];
							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;

				case 'V':
					{
						for (int i = 0; i < npoints; i++)
						{
							CComObject<CLSVGPathSegLinetoVerticalAbs>* seg;
							CComObject<CLSVGPathSegLinetoVerticalAbs>::CreateInstance(&seg);
							seg->AddRef();

							seg->m_y = dbl_values[i];

							seg->m_pSegList = this;
							m_items.Add(seg);
						}
					}
					break;
				}
			}
			break;

		case 'a':
		case 'A':
			{
				int npoints = dbl_values.GetSize();

				if ((npoints % 7) != 0)
				{
					//ASSERT(0);
					goto Exit;
				}

				for (int i = 0; i < npoints; i += 7)
				{
					if (op == 'a')	// Relative
					{
						CComObject<CLSVGPathSegArcRel>* seg;
						CComObject<CLSVGPathSegArcRel>::CreateInstance(&seg);

						seg->m_r1 = dbl_values[i+0];
						seg->m_r2 = dbl_values[i+1];
						seg->m_angle = dbl_values[i+2];
						seg->m_largeArcFlag = dbl_values[i+3] != 0? VARIANT_TRUE: VARIANT_FALSE;
						seg->m_sweepFlag = dbl_values[i+4] != 0? VARIANT_TRUE: VARIANT_FALSE;
						seg->m_x = dbl_values[i+5];
						seg->m_y = dbl_values[i+6];

						seg->AddRef();
						seg->m_pSegList = this;
						m_items.Add(seg);
					}
					else	// Absolute
					{
						CComObject<CLSVGPathSegArcAbs>* seg;
						CComObject<CLSVGPathSegArcAbs>::CreateInstance(&seg);

						seg->m_r1 = dbl_values[i+0];
						seg->m_r2 = dbl_values[i+1];
						seg->m_angle = dbl_values[i+2];
						seg->m_largeArcFlag = dbl_values[i+3] != 0? VARIANT_TRUE: VARIANT_FALSE;
						seg->m_sweepFlag = dbl_values[i+4] != 0? VARIANT_TRUE: VARIANT_FALSE;
						seg->m_x = dbl_values[i+5];
						seg->m_y = dbl_values[i+6];

						seg->AddRef();
						seg->m_pSegList = this;
						m_items.Add(seg);
					}
				}
			}
			break;

		case 'z':
		case 'Z':	// Close current sub-path (no difference between z/Z)
			{
				if (dbl_values.GetSize() != 0)
				{
					ASSERT(0);
					goto Exit;
				}

				CComObject<CLSVGPathSegClosePath>* seg_closepath;
				CComObject<CLSVGPathSegClosePath>::CreateInstance(&seg_closepath);
				seg_closepath->AddRef();
				seg_closepath->m_pSegList = this;
				m_items.Add(seg_closepath);
			}
			break;

		default:
			{
				/*
				char msg[256];
				sprintf(msg, "Unsupported operation (yet) '%c'\nReport to author", op);
				MessageBox(NULL, msg, "SVG", MB_OK);
				*/
				goto Exit;
			}
			break;
		}
	}

	success = TRUE;

Exit:

	if (!success)
	{
		CUString msg;
		msg.Format("Error parsing path data\n\n%S", str_pathdata);
		MessageBox(NULL, msg, "SVG", MB_OK);
	}
#endif
	return success;
}

///////////////////////////////////

bool SVGPathSegList::InterpolateValue(SVGPathSegList* a, SVGPathSegList* b, double t)
{
	long numberOfItems = a->get_numberOfItems();

	long b_numberOfItems = b->get_numberOfItems();

	ASSERT(0);
#if 0

// Both lists must contain equal number of items
	if (numberOfItems != b_numberOfItems)
		return FALSE;

	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> aseg; a->getItem(i, &aseg);
		CComPtr<ILSVGPathSeg> bseg; b->getItem(i, &bseg);

		LSVGPathSegType segType;
		aseg->get_pathSegType(&segType);

		LSVGPathSegType b_segType;
		bseg->get_pathSegType(&b_segType);

		if (segType != b_segType)
			break;

		switch (segType)
		{
		case PATHSEG_MOVETO_ABS:
			{
				CComQIPtr<ILSVGPathSegMovetoAbs> amovetoabs = aseg;
				CComQIPtr<ILSVGPathSegMovetoAbs> bmovetoabs = bseg;
				
				double ax; amovetoabs->get_x(&ax);
				double ay; amovetoabs->get_y(&ay);
				
				double bx; amovetoabs->get_x(&bx);
				double by; amovetoabs->get_y(&by);
				
				double cx = ax + (bx-ax)*t;
				double cy = ay + (by-ay)*t;
				
				CComObject<CLSVGPathSegMovetoAbs>* cseg;
				CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_x = cx;
				cseg->m_y = cy;

				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;

		case PATHSEG_MOVETO_REL:
			{
				CComQIPtr<ILSVGPathSegMovetoRel> amovetorel = aseg;
				CComQIPtr<ILSVGPathSegMovetoRel> bmovetorel = bseg;
				
				double ax; amovetorel->get_x(&ax);
				double ay; amovetorel->get_y(&ay);
				
				double bx; amovetorel->get_x(&bx);
				double by; amovetorel->get_y(&by);
				
				double cx = ax + (bx-ax)*t;
				double cy = ay + (by-ay)*t;
				
				CComObject<CLSVGPathSegMovetoRel>* cseg;
				CComObject<CLSVGPathSegMovetoRel>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_x = cx;
				cseg->m_y = cy;

				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;
			
		case PATHSEG_LINETO_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoAbs> alinetoabs = aseg;
				CComQIPtr<ILSVGPathSegLinetoAbs> blinetoabs = bseg;
				
				double ax; alinetoabs->get_x(&ax);
				double ay; alinetoabs->get_y(&ay);
				
				double bx; alinetoabs->get_x(&bx);
				double by; alinetoabs->get_y(&by);
				
				double cx = ax + (bx-ax)*t;
				double cy = ay + (by-ay)*t;
				
				CComObject<CLSVGPathSegLinetoAbs>* cseg;
				CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_x = cx;
				cseg->m_y = cy;

				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;

		case PATHSEG_LINETO_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoRel> alinetorel = aseg;
				CComQIPtr<ILSVGPathSegLinetoRel> blinetorel = bseg;
				
				double ax; alinetorel->get_x(&ax);
				double ay; alinetorel->get_y(&ay);
				
				double bx; alinetorel->get_x(&bx);
				double by; alinetorel->get_y(&by);
				
				double cx = ax + (bx-ax)*t;
				double cy = ay + (by-ay)*t;
				
				CComObject<CLSVGPathSegLinetoRel>* cseg;
				CComObject<CLSVGPathSegLinetoRel>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_x = cx;
				cseg->m_y = cy;

				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;
		
		case PATHSEG_CURVETO_CUBIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> acubictoabs = aseg;
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> bcubictoabs = bseg;
				
				double ax; acubictoabs->get_x(&ax);
				double ay; acubictoabs->get_y(&ay);
				double ax1; acubictoabs->get_x1(&ax1);
				double ay1; acubictoabs->get_y1(&ay1);
				double ax2; acubictoabs->get_x2(&ax2);
				double ay2; acubictoabs->get_y2(&ay2);
				
				double bx; bcubictoabs->get_x(&bx);
				double by; bcubictoabs->get_y(&by);
				double bx1; bcubictoabs->get_x1(&bx1);
				double by1; bcubictoabs->get_y1(&by1);
				double bx2; bcubictoabs->get_x2(&bx2);
				double by2; bcubictoabs->get_y2(&by2);
				
				double cx = ax + (bx-ax)*t;
				double cy = ay + (by-ay)*t;
				double cx1 = ax1 + (bx1-ax1)*t;
				double cy1 = ay1 + (by1-ay1)*t;
				double cx2 = ax2 + (bx2-ax2)*t;
				double cy2 = ay2 + (by2-ay2)*t;
				
				CComObject<CLSVGPathSegCurvetoCubicAbs>* cseg;
				CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_x = cx;
				cseg->m_y = cy;
				cseg->m_x1 = cx1;
				cseg->m_y1 = cy1;
				cseg->m_x2 = cx2;
				cseg->m_y2 = cy2;
				
				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;
			
		case PATHSEG_CURVETO_CUBIC_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> acubictorel = aseg;
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> bcubictorel = bseg;
				
				double ax; acubictorel->get_x(&ax);
				double ay; acubictorel->get_y(&ay);
				double ax1; acubictorel->get_x1(&ax1);
				double ay1; acubictorel->get_y1(&ay1);
				double ax2; acubictorel->get_x2(&ax2);
				double ay2; acubictorel->get_y2(&ay2);
				
				double bx; bcubictorel->get_x(&bx);
				double by; bcubictorel->get_y(&by);
				double bx1; bcubictorel->get_x1(&bx1);
				double by1; bcubictorel->get_y1(&by1);
				double bx2; bcubictorel->get_x2(&bx2);
				double by2; bcubictorel->get_y2(&by2);
				
				double cx = ax + (bx-ax)*t;
				double cy = ay + (by-ay)*t;
				double cx1 = ax1 + (bx1-ax1)*t;
				double cy1 = ay1 + (by1-ay1)*t;
				double cx2 = ax2 + (bx2-ax2)*t;
				double cy2 = ay2 + (by2-ay2)*t;
				
				CComObject<CLSVGPathSegCurvetoCubicRel>* cseg;
				CComObject<CLSVGPathSegCurvetoCubicRel>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_x = cx;
				cseg->m_y = cy;
				cseg->m_x1 = cx1;
				cseg->m_y1 = cy1;
				cseg->m_x2 = cx2;
				cseg->m_y2 = cy2;
				
				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticAbs> aquadtoabs = aseg;
				CComQIPtr<ILSVGPathSegCurvetoQuadraticAbs> bquadtoabs = bseg;

				double ax; aquadtoabs->get_x(&ax);
				double ay; aquadtoabs->get_y(&ay);
				double ax1; aquadtoabs->get_x1(&ax1);
				double ay1; aquadtoabs->get_y1(&ay1);

				double bx; bquadtoabs->get_x(&bx);
				double by; bquadtoabs->get_y(&by);
				double bx1; bquadtoabs->get_x1(&bx1);
				double by1; bquadtoabs->get_y1(&by1);

				double cx = ax + (bx-ax)*t;
				double cy = ay + (by-ay)*t;
				double cx1 = ax1 + (bx1-ax1)*t;
				double cy1 = ay1 + (by1-ay1)*t;

				CComObject<CLSVGPathSegCurvetoQuadraticAbs>* cseg;
				CComObject<CLSVGPathSegCurvetoQuadraticAbs>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_x = cx;
				cseg->m_y = cy;
				cseg->m_x1 = cx1;
				cseg->m_y1 = cy1;

				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticRel> aquadtorel = aseg;
				CComQIPtr<ILSVGPathSegCurvetoQuadraticRel> bquadtorel = bseg;
				
				double ax; aquadtorel->get_x(&ax);
				double ay; aquadtorel->get_y(&ay);
				double ax1; aquadtorel->get_x1(&ax1);
				double ay1; aquadtorel->get_y1(&ay1);

				double bx; bquadtorel->get_x(&bx);
				double by; bquadtorel->get_y(&by);
				double bx1; bquadtorel->get_x1(&bx1);
				double by1; bquadtorel->get_y1(&by1);

				double cx = ax + (bx-ax)*t;
				double cy = ay + (by-ay)*t;
				double cx1 = ax1 + (bx1-ax1)*t;
				double cy1 = ay1 + (by1-ay1)*t;

				CComObject<CLSVGPathSegCurvetoQuadraticRel>* cseg;
				CComObject<CLSVGPathSegCurvetoQuadraticRel>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_x = cx;
				cseg->m_y = cy;
				cseg->m_x1 = cx1;
				cseg->m_y1 = cy1;

				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;

		case PATHSEG_CLOSEPATH:
			{
				CComObject<CLSVGPathSegClosePath>* cseg;
				CComObject<CLSVGPathSegClosePath>::CreateInstance(&cseg);
				cseg->AddRef();

				cseg->m_pSegList = this;
				m_items.Add(cseg);
			}
			break;

		default:
			{
				ASSERT(0);
			}
		}
	}
#endif
	return true;
}

///////////////////////////////////

String SVGPathSegList::StringFromPathSegList()
{
	WCHAR str2[256];	// Enough for one segment

	String str = WSTR("");

	ASSERT(0);
#if 0

//	_bstr_t str = L"";
	long numberOfItems = m_items.GetSize();

	for (long i = 0; i < numberOfItems; i++)
	{
		ILSVGPathSeg* seg = m_items[i];

	//	if (i > 0) str += L" ";

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);

		switch (segType)
		{
		case PATHSEG_MOVETO_ABS:
			{
				CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

				double x, y;
				movetoabs->get_x(&x);
				movetoabs->get_y(&y);

				swprintf(str2, L"M%g %g", x, y);
				str += str2;
			}
			break;

		case PATHSEG_MOVETO_REL:
			{
				CComQIPtr<ILSVGPathSegMovetoRel> movetorel = seg;

				double x, y;
				movetorel->get_x(&x);
				movetorel->get_y(&y);

				swprintf(str2, L"m%g %g", x, y);
				str += str2;
			}
			break;

		case PATHSEG_LINETO_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

				double x, y;
				linetoabs->get_x(&x);
				linetoabs->get_y(&y);

				swprintf(str2, L"L%g %g", x, y);
				str += str2;
			}
			break;

		case PATHSEG_LINETO_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoRel> linetorel = seg;

				double x, y;
				linetorel->get_x(&x);
				linetorel->get_y(&y);

				swprintf(str2, L"l%g %g", x, y);
				str += str2;
			}
			break;

		case PATHSEG_CURVETO_CUBIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;

				double x, y, x1, y1, x2, y2;
				cubictoabs->get_x(&x);
				cubictoabs->get_y(&y);
				cubictoabs->get_x1(&x1);
				cubictoabs->get_y1(&y1);
				cubictoabs->get_x2(&x2);
				cubictoabs->get_y2(&y2);

				swprintf(str2, L"C%g %g %g %g %g %g", x1, y1, x2, y2, x, y);
				str += str2;
			}
			break;

		case PATHSEG_CURVETO_CUBIC_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicRel> cubictorel = seg;

				double x, y, x1, y1, x2, y2;
				cubictorel->get_x(&x);
				cubictorel->get_y(&y);
				cubictorel->get_x1(&x1);
				cubictorel->get_y1(&y1);
				cubictorel->get_x2(&x2);
				cubictorel->get_y2(&y2);

				swprintf(str2, L"c%g %g %g %g %g %g", x1, y1, x2, y2, x, y);
				str += str2;
			}
			break;

		case PATHSEG_CURVETO_CUBIC_SMOOTH_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicSmoothAbs> cubictosmoothabs = seg;

				double x, y, x2, y2;
				cubictosmoothabs->get_x(&x);
				cubictosmoothabs->get_y(&y);
				cubictosmoothabs->get_x2(&x2);
				cubictosmoothabs->get_y2(&y2);

				swprintf(str2, L"S%g %g %g %g", x2, y2, x, y);
				str += str2;
			}
			break;

		case PATHSEG_CURVETO_CUBIC_SMOOTH_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicSmoothRel> cubictosmoothrel = seg;

				double x, y, x2, y2;
				cubictosmoothrel->get_x(&x);
				cubictosmoothrel->get_y(&y);
				cubictosmoothrel->get_x2(&x2);
				cubictosmoothrel->get_y2(&y2);

				swprintf(str2, L"s%g %g %g %g", x2, y2, x, y);
				str += str2;
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticAbs> _seg = seg;

				double x, y, x1, y1;
				_seg->get_x(&x);
				_seg->get_y(&y);
				_seg->get_x1(&x1);
				_seg->get_y1(&y1);

				swprintf(str2, L"Q%g %g %g %g", x1, y1, x, y);
				str += str2;
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticRel> _seg = seg;

				double x, y, x1, y1;
				_seg->get_x(&x);
				_seg->get_y(&y);
				_seg->get_x1(&x1);
				_seg->get_y1(&y1);

				swprintf(str2, L"q%g %g %g %g", x1, y1, x, y);
				str += str2;
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS:
			{
				ASSERT(0);
#if 0
				CComQIPtr<ILSVGPathSegCurvetoQuadraticSmoothAbs> cubictosmoothabs = seg;

				double x, y, x2, y2;
				cubictosmoothabs->get_x(&x);
				cubictosmoothabs->get_y(&y);
				cubictosmoothabs->get_x2(&x2);
				cubictosmoothabs->get_y2(&y2);

				swprintf(str2, L"T%g %g %g %g", x2, y2, x, y);
				str += str2;
#endif
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL:
			{
				ASSERT(0);
#if 0
				CComQIPtr<ILSVGPathSegCurvetoQuadraticSmoothRel> cubictosmoothrel = seg;

				double x, y, x2, y2;
				cubictosmoothrel->get_x(&x);
				cubictosmoothrel->get_y(&y);
				cubictosmoothrel->get_x2(&x2);
				cubictosmoothrel->get_y2(&y2);

				swprintf(str2, L"t%g %g %g %g", x2, y2, x, y);
				str += str2;
#endif
			}
			break;

		case PATHSEG_LINETO_HORIZONTAL_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoHorizontalAbs> linetohabs = seg;

				double x;
				linetohabs->get_x(&x);

				swprintf(str2, L"H%g", x);
				str += str2;
			}
			break;

		case PATHSEG_LINETO_HORIZONTAL_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoHorizontalRel> linetohrel = seg;

				double x;
				linetohrel->get_x(&x);

				swprintf(str2, L"h%g", x);
				str += str2;
			}
			break;

		case PATHSEG_LINETO_VERTICAL_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoVerticalAbs> linetovabs = seg;

				double y;
				linetovabs->get_y(&y);

				swprintf(str2, L"V%g", y);
				str += str2;
			}
			break;

		case PATHSEG_LINETO_VERTICAL_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoVerticalRel> linetovrel = seg;

				double y;
				linetovrel->get_y(&y);

				swprintf(str2, L"v%g", y);
				str += str2;
			}
			break;

		case PATHSEG_CLOSEPATH:
			{
				str += L"z";
			}
			break;

		default:
			ASSERT(0);
		}
	}
#endif
	return str;
}

//////////

// Convert degrees to radians for math functions.
/*
#define RAD(x) ((x) * 3.1415927 / 180)

typedef struct _FIXED {
#ifndef _MAC
    uint16    fract;
    short   value;
#else
    short   value;
    WORD    fract;
#endif
} FIXED;
*/

/*
typedef struct _MAT2 {
     FIXED  eM11;
     FIXED  eM12;
     FIXED  eM21;
     FIXED  eM22;
} MAT2,  *LPMAT2;
*/

/****************************************************************************
 *  FUNCTION   : FixedFromDouble
 *  RETURNS    : FIXED value representing the given double.
 ****************************************************************************/

/*
FIXED FixedFromDouble(double d)
{
    long l;

    l = (long) (d * 65536L);
    return *(FIXED *)&l;
}
*/
/****************************************************************************
 *  FUNCTION   : IntFromFixed
 *  RETURNS    : int value approximating the FIXED value.
 ****************************************************************************/
/*
int IntFromFixed(FIXED f)
{
    if (f.fract >= 0x8000)
	return(f.value + 1);
    else
	return(f.value);
}
*/

/****************************************************************************
 *  FUNCTION   : fxDiv2
 *  RETURNS    : (val1 + val2)/2 for FIXED values
 ****************************************************************************/

/*
FIXED fxDiv2(FIXED fxVal1, FIXED fxVal2)
{
    long l;

    l = (*((long *)&(fxVal1)) + *((long *)&(fxVal2)))/2;
    return(*(FIXED *)&l);
}
*/
#if 0

/****************************************************************************
 *  FUNCTION   : MakeRotationMat
 *  PURPOSE    : Fill in a rotation matrix based on the given angle.
 *  RETURNS    : none.
 ****************************************************************************/
/*
void MakeRotationMat(LPMAT2 lpMat, double dAngle)
{
    lpMat->eM11 = FixedFromDouble(cos(RAD(dAngle)));
    lpMat->eM12 = FixedFromDouble(sin(RAD(dAngle)));
    lpMat->eM21 = FixedFromDouble(-sin(RAD(dAngle)));
    lpMat->eM22 = FixedFromDouble(cos(RAD(dAngle)));
}
*/
/****************************************************************************
 *  FUNCTION   : ShearMat
 *  PURPOSE    : Fill in a 0.25 horizontal shear matrix.
 *  RETURNS    : none.
 ****************************************************************************/
/*
void ShearMat(LPMAT2 lpMat)
{
    lpMat->eM11 = FixedFromDouble(1);
    lpMat->eM12 = FixedFromDouble(0);
    lpMat->eM21 = FixedFromDouble(0.25);
    lpMat->eM22 = FixedFromDouble(1);
}
*/
#endif

/****************************************************************************
 *  FUNCTION   : IdentityMat
 *  PURPOSE    : Fill in matrix to be the identity matrix.
 *  RETURNS    : none.
 ****************************************************************************/
/*
void IdentityMat(LPMAT2 lpMat)
{
    lpMat->eM11 = FixedFromDouble(1);
    lpMat->eM12 = FixedFromDouble(0);
    lpMat->eM21 = FixedFromDouble(0);
    lpMat->eM22 = FixedFromDouble(1);
}
*/

#if 0
LDraw::PointD FixedPt2FIX(POINT fx)
{
	LDraw::PointD apt;
	apt.X = *(long*)&fx.x / 65536.0;// (long)(fx.x.fract/65536.0 + fx.x.value)*65536;
	apt.Y = *(long*)&fx.y / 65536.0;//(long)(fx.y.fract/65536.0 + fx.y.value)*65536;

	/*
	apt.X = ((double)fx.x.fract/65536.0 + (double)fx.x.value);
	apt.Y = ((double)fx.y.fract/65536.0 + (double)fx.y.value);
	*/
	return apt;
}

#if 0
/****************************************************************************
 *  FUNCTION   : MakeBezierFromQBSpline
 *
 *  PURPOSE    : Converts a quadratic spline in pSline to a four point Bezier
 *               spline in pPts.
 *
 *
 *  RETURNS    : number of Bezier points placed into the pPts POINT array.
 ****************************************************************************/ 
UINT MakeBezierFromQBSpline( LDraw::PointD* pPts, POINT *pSpline )
{
    LDraw::PointD P0,         // Quadratic on curve start point
            P1,         // Quadratic control point
            P2;         // Quadratic on curve end point
//    UINT    cTotal = 0;

    // Convert the Quadratic points to integer
	/*
    P0.x = IntFromFixed( pSpline[0].x );
    P0.y = IntFromFixed( pSpline[0].y );
    P1.x = IntFromFixed( pSpline[1].x );
    P1.y = IntFromFixed( pSpline[1].y );
    P2.x = IntFromFixed( pSpline[2].x );
    P2.y = IntFromFixed( pSpline[2].y );
*/

	 P0 = FixedPt2FIX(pSpline[0]);
	 P1 = FixedPt2FIX(pSpline[1]);
	 P2 = FixedPt2FIX(pSpline[2]);

    // conversion of a quadratic to a cubic

    // Cubic P0 is the on curve start point
    pPts[0] = P0; // Don't add the first point, already added
    
    // Cubic P1 in terms of Quadratic P0 and P1
    pPts[1] = LDraw::PointD(
		P0.X + 2*(P1.X - P0.X)/3,
		P0.Y + 2*(P1.Y - P0.Y)/3);

    // Cubic P2 in terms of Qudartic P1 and P2
    pPts[2] = LDraw::PointD(
		P1.X + 1*(P2.X - P1.X)/3,
		P1.Y + 1*(P2.Y - P1.Y)/3);

    // Cubic P3 is the on curve end point
    pPts[3] = P2;

    return 4;
}
#endif

/****************************************************************************
 *  FUNCTION   : AppendQuadBSplineToBezier
 *
 *  PURPOSE    : Converts Quadratic spline segments into their Bezier point 
 *               representation and appends them to a list of Bezier points. 
 *
 *               WARNING - The array must have at least one valid
 *               start point prior to the address of the element passed.
 *
 *  RETURNS    : number of Bezier points added to the POINT array.
 ****************************************************************************/ 

UINT SVGPathSegList::AppendQuadBSplineToBezier(POINTFX start, LPTTPOLYCURVE lpCurve, double offsetx, double offsety)
{
	ASSERT(0);
	return 0;
#if 0
    WORD                i;
    UINT                cTotal = 0;
    POINTFX             spline[3];  // a Quadratic is defined by 3 points
    LDraw::PointD           bezier[4];  // a Cubic by 4

    // The initial A point is on the curve.
    spline[0] = start;

    for (i = 0; i < lpCurve->cpfx;)
    {
        // The B point.
        spline[1] = lpCurve->apfx[i++];

        // Calculate the C point.
        if (i == (lpCurve->cpfx - 1))
        {
            // The last C point is described explicitly
            // i.e. it is on the curve.
            spline[2] = lpCurve->apfx[i++];
        }     
        else
        {
            // C is midpoint between B and next B point
            // because that is the on curve point of 
            // a Quadratic B-Spline.
            spline[2].x = fxDiv2(
                lpCurve->apfx[i-1].x,
                lpCurve->apfx[i].x
                );
            spline[2].y = fxDiv2(
                lpCurve->apfx[i-1].y,
                lpCurve->apfx[i].y
                );
        }

        // convert the Q Spline to a Bezier
        MakeBezierFromQBSpline( bezier, spline );
        
        // append the Bezier to the existing ones
                                    // Point 0 is Point 3 of previous.
       // pt[cTotal++] = bezier[1];   // Point 1
       // pt[cTotal++] = bezier[2];   // Point 2
       // pt[cTotal++] = bezier[3];   // Point 3
/*
        pt.Add(bezier[1]);   // Point 1
        pt.Add(bezier[2]);   // Point 2
        pt.Add(bezier[3]);   // Point 3
*/

		  CComObject<CLSVGPathSegCurvetoCubicAbs>* cubic;
		  CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&cubic);
		  cubic->m_x1 = bezier[1].X + offsetx; cubic->m_y1 = /*-*/bezier[1].Y + offsety;
		  cubic->m_x2 = bezier[2].X + offsetx; cubic->m_y2 = /*-*/bezier[2].Y + offsety;
		  cubic->m_x = bezier[3].X + offsetx; cubic->m_y = /*-*/bezier[3].Y + offsety;
		  cubic->m_pSegList = this;
		  cubic->AddRef();
		  m_items.Add(cubic);

        // New A point for next slice of spline is the 
        // on curve C point of this B-Spline
        spline[0] = spline[2];
    }

    return cTotal;
#endif
}
#endif

#if 0
ErrorCode SVGPathSegList::AddCharToSegList(HDC hdc, UINT ch, double offsetx, double offsety)
{
	ASSERT(0);
#if 0
	DWORD cbBuffer = 0;
	LPBYTE lpBuffer = NULL;

	GLYPHMETRICS	gm;

	MAT2 mat2;// = {{1,0},{0,0},{0,0},{1,0}};
	IdentityMat(&mat2);

// Get required size
	cbBuffer = GetGlyphOutline(hdc, ch, GGO_GLYPH_INDEX | /*GGO_UNHINTED |*/ /*GGO_BEZIER*/GGO_NATIVE, &gm, 0, NULL, &mat2);
	if (cbBuffer == -1)
	{
	//	TCHAR buf[256];
	//	wsprintf(buf, "GetGlyphOutline() = %d", GetLastError());
	//	MessageBox(NULL, buf, "", MB_OK);

		return FALSE;
	}

	lpBuffer = (LPBYTE)GlobalAlloc(0, cbBuffer);
	if (GetGlyphOutline(hdc, ch, GGO_GLYPH_INDEX | /*GGO_UNHINTED |*/ /*GGO_BEZIER*/GGO_NATIVE, &gm, cbBuffer, lpBuffer, &mat2) == -1)
	{
		GlobalFree(lpBuffer);
	//	MessageBox(NULL, "Error GetGlyphOutline()", "", MB_OK);
		return FALSE;
	}

	POINTFX	ptStart;

	LPTTPOLYGONHEADER hdr = (LPTTPOLYGONHEADER)lpBuffer;

	int charsubcurves = 0;

	while ((DWORD)hdr < (DWORD)(((LPSTR)lpBuffer) + cbBuffer))
	{
		if (hdr->dwType == TT_POLYGON_TYPE)
		{
			LDraw::PointD  apt;

			POINTFX	pfx[3];

			pfx[0] = hdr->pfxStart;

			apt = FixedPt2FIX(hdr->pfxStart);

			POINTFX pfxOld = hdr->pfxStart;

			CComObject<CLSVGPathSegMovetoAbs>* moveto;
			CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&moveto);

			moveto->m_x = apt.X + offsetx;
			moveto->m_y = /*-*/apt.Y + offsety;
			moveto->m_pSegList = this;
			moveto->AddRef();
			m_items.Add(moveto);

			LPBYTE p = ((LPBYTE)hdr) + sizeof(TTPOLYGONHEADER);

			while ((DWORD)p < (DWORD)(((LPSTR)hdr) + hdr->cb))
			{
				LPTTPOLYCURVE curve = (LPTTPOLYCURVE)p;
				int size = 4 + curve->cpfx*sizeof(POINTFX);
//**********************************************
             // Format assumption:
             //   The bytes immediately preceding a POLYCURVE
             //   structure contain a valid POINTFX.
             // 
             //   If this is first curve, this points to the 
             //      pfxStart of the POLYGONHEADER.
             //   Otherwise, this points to the last point of
             //      the previous POLYCURVE.
             // 
             //   In either case, this is representative of the
             //      previous curve's last point.
             //**********************************************

         //    ptStart = *(LPPOINTFX)((LPSTR)curve - sizeof(POINTFX));

				if (curve->wType == TT_PRIM_LINE)
				{
					for (int i = 0; i < curve->cpfx; i++)
					{
						apt = FixedPt2FIX(curve->apfx[i]);

						CComObject<CLSVGPathSegLinetoAbs>* lineto;
						CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&lineto);
						lineto->m_x = apt.X + offsetx;
						lineto->m_y = /*-*/apt.Y + offsety;
						lineto->m_pSegList = this;
						lineto->AddRef();
						m_items.Add(lineto);

						pfxOld = curve->apfx[i];
					}
				}
				else if (curve->wType == TT_PRIM_QSPLINE)
				{
          //   ptStart = *(LPPOINTFX)((LPSTR)curve - sizeof(POINTFX));

					ptStart = pfxOld;
					AppendQuadBSplineToBezier(ptStart, curve, offsetx, offsety);

					pfxOld = curve->apfx[curve->cpfx-1];
				}
				else if (curve->wType == TT_PRIM_CSPLINE)
				{
					ASSERT((curve->cpfx % 3) == 0);

					for (int i = 0; i < curve->cpfx; i += 3)
					{
						PointD apt0 = FixedPt2FIX(curve->apfx[i]);
						PointD apt1 = FixedPt2FIX(curve->apfx[i+1]);
						PointD apt2 = FixedPt2FIX(curve->apfx[i+2]);

						CComObject<CLSVGPathSegCurvetoCubicAbs>* curveto;
						CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&curveto);
						curveto->m_x1 = apt0.X + offsetx;
						curveto->m_y1 = /*-*/apt0.Y + offsety;
						curveto->m_x2 = apt1.X + offsetx;
						curveto->m_y2 = /*-*/apt1.Y + offsety;
						curveto->m_x = apt2.X + offsetx;
						curveto->m_y = /*-*/apt2.Y + offsety;

						curveto->m_pSegList = this;
						curveto->AddRef();
						m_items.Add(curveto);

						pfxOld = curve->apfx[i+2];
					}
				}
				else
					ASSERT(0);

				p += size;
			}

#if 0
			pBez->m_pointArray.Add(pBez->m_pointArray[pBez->m_pointArray.GetSize()-1]);

			ASSERT((pBez->m_pointArray.GetSize() % 3) == 0);

			for (int i = 0; i < pBez->m_pointArray.GetSize(); i++)
			{
				pBez->m_pointArray[i].y = 0 - pBez->m_pointArray[i].y;
			}

			pBez->MovePoints(TRUE, x, y);

			charsubcurves++;
			pBezList->AddTail(pBez);
#endif
			// Close path
			{
				CComObject<CLSVGPathSegClosePath>* p;
				CComObject<CLSVGPathSegClosePath>::CreateInstance(&p);
				p->AddRef();
				
				p->m_pSegList = this;
				m_items.Add(p);
			}
		}
		else
			ASSERT(0);

		hdr = (LPTTPOLYGONHEADER)(((LPSTR)hdr) + hdr->cb);
	}

	GlobalFree(lpBuffer);
#endif
	return true;
}
#endif

// TODO, optimize this

void SVGPathSegList::matrixTransform(const gm::matrix3d& mat)
{
	long numberOfItems = m_items.GetSize();

	ASSERT(0);
#if 0

	for (int i = 0; i < numberOfItems; i++)
	{
		ILSVGPathSeg* seg = m_items[i];

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);
		if (segType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

			double x, y;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

			gmVector2 pt(x, y);
			gmVector2 xpt = mat.transform(pt);

			movetoabs->set_x(xpt[0]);
			movetoabs->set_y(xpt[1]);
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

			double x, y;
			linetoabs->get_x(&x);
			linetoabs->get_y(&y);

			gmVector2 pt(x, y);
			gmVector2 xpt = mat.transform(pt);

			linetoabs->set_x(xpt[0]);
			linetoabs->set_y(xpt[1]);
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;

			double x, y, x1, y1, x2, y2;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
			cubictoabs->get_x1(&x1);
			cubictoabs->get_y1(&y1);
			cubictoabs->get_x2(&x2);
			cubictoabs->get_y2(&y2);

			{
				gmVector2 pt(x, y);
				gmVector2 xpt = mat.transform(pt);

				x = xpt[0];
				y = xpt[1];
			}
			{
				gmVector2 pt(x1, y1);
				gmVector2 xpt = mat.transform(pt);

				x1 = xpt[0];
				y1 = xpt[1];
			}
			{
				gmVector2 pt(x2, y2);
				gmVector2 xpt = mat.transform(pt);

				x2 = xpt[0];
				y2 = xpt[1];
			}

			cubictoabs->set_x(x);
			cubictoabs->set_y(y);
			cubictoabs->set_x1(x1);
			cubictoabs->set_y1(y1);
			cubictoabs->set_x2(x2);
			cubictoabs->set_y2(y2);
		}
	}
#endif
}

void SVGPathSegList::matrixTransform(SVGMatrix *matrix)
{
	if (matrix == NULL) throw new Exception(WSTR("null pointer"));
	LockUpdate();

	matrixTransform(matrix->GetM());

	UnlockUpdate();
}

void SVGPathSegList::AddSegList(const SVGPathSegList* seglist)
{
	long numberOfItems = seglist->get_numberOfItems();
	if (numberOfItems > 0)
	{
		AddSegListNoUpdate(seglist);
		ChangedSeg();
	}
}

void SVGPathSegList::AddSegListNoUpdate(const SVGPathSegList* seglist)
{
	ASSERT(0);
#if 0
	long numberOfItems = seglist->get_numberOfItems();
	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);

		switch (segType)
		{
		case PATHSEG_MOVETO_ABS:
			{
				CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;
				
				CComObject<CLSVGPathSegMovetoAbs>* p;
				CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&p);
				p->AddRef();
				
				movetoabs->get_x(&p->m_x);
				movetoabs->get_y(&p->m_y);
				
				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;
			
		case PATHSEG_MOVETO_REL:
			{
				CComQIPtr<ILSVGPathSegMovetoRel> movetorel = seg;
				
				CComObject<CLSVGPathSegMovetoRel>* p;
				CComObject<CLSVGPathSegMovetoRel>::CreateInstance(&p);
				p->AddRef();
				
				movetorel->get_x(&p->m_x);
				movetorel->get_y(&p->m_y);
				
				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;
			
		case PATHSEG_LINETO_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;
				
				CComObject<CLSVGPathSegLinetoAbs>* p;
				CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&p);
				p->AddRef();
				
				linetoabs->get_x(&p->m_x);
				linetoabs->get_y(&p->m_y);
				
				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;
			
		case PATHSEG_LINETO_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoRel> linetorel = seg;
				
				CComObject<CLSVGPathSegLinetoRel>* p;
				CComObject<CLSVGPathSegLinetoRel>::CreateInstance(&p);
				p->AddRef();
				
				linetorel->get_x(&p->m_x);
				linetorel->get_y(&p->m_y);
				
				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_LINETO_HORIZONTAL_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoHorizontalAbs> _seg = seg;
				
				CComObject<CLSVGPathSegLinetoHorizontalAbs>* p;
				CComObject<CLSVGPathSegLinetoHorizontalAbs>::CreateInstance(&p);
				p->AddRef();
				
				_seg->get_x(&p->m_x);
				
				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_LINETO_HORIZONTAL_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoHorizontalRel> _seg = seg;

				CComObject<CLSVGPathSegLinetoHorizontalRel>* p;
				CComObject<CLSVGPathSegLinetoHorizontalRel>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_LINETO_VERTICAL_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoVerticalAbs> _seg = seg;

				CComObject<CLSVGPathSegLinetoVerticalAbs>* p;
				CComObject<CLSVGPathSegLinetoVerticalAbs>::CreateInstance(&p);
				p->AddRef();

				_seg->get_y(&p->m_y);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_LINETO_VERTICAL_REL:
			{
				CComQIPtr<ILSVGPathSegLinetoVerticalRel> _seg = seg;

				CComObject<CLSVGPathSegLinetoVerticalRel>* p;
				CComObject<CLSVGPathSegLinetoVerticalRel>::CreateInstance(&p);
				p->AddRef();

				_seg->get_y(&p->m_y);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CURVETO_CUBIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;

				CComObject<CLSVGPathSegCurvetoCubicAbs>* p;
				CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&p);
				p->AddRef();

				cubictoabs->get_x(&p->m_x);
				cubictoabs->get_y(&p->m_y);
				cubictoabs->get_x1(&p->m_x1);
				cubictoabs->get_y1(&p->m_y1);
				cubictoabs->get_x2(&p->m_x2);
				cubictoabs->get_y2(&p->m_y2);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CURVETO_CUBIC_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicRel> cubictorel = seg;
				
				CComObject<CLSVGPathSegCurvetoCubicRel>* p;
				CComObject<CLSVGPathSegCurvetoCubicRel>::CreateInstance(&p);
				p->AddRef();
				
				cubictorel->get_x(&p->m_x);
				cubictorel->get_y(&p->m_y);
				cubictorel->get_x1(&p->m_x1);
				cubictorel->get_y1(&p->m_y1);
				cubictorel->get_x2(&p->m_x2);
				cubictorel->get_y2(&p->m_y2);
				
				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CURVETO_CUBIC_SMOOTH_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicSmoothAbs> _seg = seg;
				
				CComObject<CLSVGPathSegCurvetoCubicSmoothAbs>* p;
				CComObject<CLSVGPathSegCurvetoCubicSmoothAbs>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);
				_seg->get_y(&p->m_y);
				_seg->get_x2(&p->m_x2);
				_seg->get_y2(&p->m_y2);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CURVETO_CUBIC_SMOOTH_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicSmoothRel> _seg = seg;

				CComObject<CLSVGPathSegCurvetoCubicSmoothRel>* p;
				CComObject<CLSVGPathSegCurvetoCubicSmoothRel>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);
				_seg->get_y(&p->m_y);
				_seg->get_x2(&p->m_x2);
				_seg->get_y2(&p->m_y2);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticAbs> _seg = seg;

				CComObject<CLSVGPathSegCurvetoQuadraticAbs>* p;
				CComObject<CLSVGPathSegCurvetoQuadraticAbs>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);
				_seg->get_y(&p->m_y);
				_seg->get_x1(&p->m_x1);
				_seg->get_y1(&p->m_y1);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticRel> _seg = seg;

				CComObject<CLSVGPathSegCurvetoQuadraticRel>* p;
				CComObject<CLSVGPathSegCurvetoQuadraticRel>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);
				_seg->get_y(&p->m_y);
				_seg->get_x1(&p->m_x1);
				_seg->get_y1(&p->m_y1);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticSmoothAbs> _seg = seg;

				CComObject<CLSVGPathSegCurvetoQuadraticSmoothAbs>* p;
				CComObject<CLSVGPathSegCurvetoQuadraticSmoothAbs>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);
				_seg->get_y(&p->m_y);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL:
			{
				CComQIPtr<ILSVGPathSegCurvetoQuadraticSmoothRel> _seg = seg;

				CComObject<CLSVGPathSegCurvetoQuadraticSmoothRel>* p;
				CComObject<CLSVGPathSegCurvetoQuadraticSmoothRel>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);
				_seg->get_y(&p->m_y);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_ARC_ABS:
			{
				CComQIPtr<ILSVGPathSegArcAbs> _seg = seg;

				CComObject<CLSVGPathSegArcAbs>* p;
				CComObject<CLSVGPathSegArcAbs>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);
				_seg->get_y(&p->m_y);
				_seg->get_r1(&p->m_r1);
				_seg->get_r2(&p->m_r2);
				_seg->get_angle(&p->m_angle);
				_seg->get_largeArcFlag(&p->m_largeArcFlag);
				_seg->get_sweepFlag(&p->m_sweepFlag);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_ARC_REL:
			{
				CComQIPtr<ILSVGPathSegArcRel> _seg = seg;

				CComObject<CLSVGPathSegArcRel>* p;
				CComObject<CLSVGPathSegArcRel>::CreateInstance(&p);
				p->AddRef();

				_seg->get_x(&p->m_x);
				_seg->get_y(&p->m_y);
				_seg->get_r1(&p->m_r1);
				_seg->get_r2(&p->m_r2);
				_seg->get_angle(&p->m_angle);
				_seg->get_largeArcFlag(&p->m_largeArcFlag);
				_seg->get_sweepFlag(&p->m_sweepFlag);

				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		case PATHSEG_CLOSEPATH:
			{
				CComObject<CLSVGPathSegClosePath>* p;
				CComObject<CLSVGPathSegClosePath>::CreateInstance(&p);
				p->AddRef();
				
				p->m_pSegList = this;
				m_items.Add(p);
			}
			break;

		default:
			ASSERT(0);
		}
	}

	return S_OK;
#endif
}

void SVGPathSegList::Offset(double dx, double dy)
{
	ASSERT(0);
#if 0
	long numberOfItems = m_items.GetSize();

	if (((dx != 0) || (dy != 0)) && (numberOfItems > 0))
	{
		for (int i = 0; i < numberOfItems; i++)
		{
			ILSVGPathSeg* seg = m_items[i];

			LSVGPathSegType segType;
			seg->get_pathSegType(&segType);

			switch (segType)
			{
			case PATHSEG_MOVETO_ABS:
				{
					static_cast<CLSVGPathSegMovetoAbs*>(seg)->m_x += dx;
					static_cast<CLSVGPathSegMovetoAbs*>(seg)->m_y += dy;
				}
				break;

			case PATHSEG_MOVETO_REL:
				{
					static_cast<CLSVGPathSegMovetoRel*>(seg)->m_x += dx;
					static_cast<CLSVGPathSegMovetoRel*>(seg)->m_y += dy;
				}
				break;

			case PATHSEG_LINETO_ABS:
				{
					static_cast<CLSVGPathSegLinetoAbs*>(seg)->m_x += dx;
					static_cast<CLSVGPathSegLinetoAbs*>(seg)->m_y += dy;
				}
				break;

			case PATHSEG_LINETO_REL:
				{
					static_cast<CLSVGPathSegLinetoRel*>(seg)->m_x += dx;
					static_cast<CLSVGPathSegLinetoRel*>(seg)->m_y += dy;
				}
				break;

			case PATHSEG_LINETO_HORIZONTAL_ABS:
				{
					static_cast<CLSVGPathSegLinetoHorizontalAbs*>(seg)->m_x += dx;
				}
				break;

			case PATHSEG_LINETO_HORIZONTAL_REL:
				{
					static_cast<CLSVGPathSegLinetoHorizontalRel*>(seg)->m_x += dx;
				}
				break;

			case PATHSEG_LINETO_VERTICAL_ABS:
				{
					static_cast<CLSVGPathSegLinetoVerticalAbs*>(seg)->m_y += dy;
				}
				break;

			case PATHSEG_LINETO_VERTICAL_REL:
				{
					static_cast<CLSVGPathSegLinetoVerticalRel*>(seg)->m_y += dy;
				}
				break;

			case PATHSEG_CURVETO_CUBIC_ABS:
				{
					static_cast<CLSVGPathSegCurvetoCubicAbs*>(seg)->m_x += dx;
					static_cast<CLSVGPathSegCurvetoCubicAbs*>(seg)->m_y += dy;
					static_cast<CLSVGPathSegCurvetoCubicAbs*>(seg)->m_x1 += dx;
					static_cast<CLSVGPathSegCurvetoCubicAbs*>(seg)->m_y1 += dy;
					static_cast<CLSVGPathSegCurvetoCubicAbs*>(seg)->m_x2 += dx;
					static_cast<CLSVGPathSegCurvetoCubicAbs*>(seg)->m_y2 += dy;
				}
				break;

			case PATHSEG_CURVETO_CUBIC_REL:
				{
					static_cast<CLSVGPathSegCurvetoCubicRel*>(seg)->m_x += dx;
					static_cast<CLSVGPathSegCurvetoCubicRel*>(seg)->m_y += dy;
					static_cast<CLSVGPathSegCurvetoCubicRel*>(seg)->m_x1 += dx;
					static_cast<CLSVGPathSegCurvetoCubicRel*>(seg)->m_y1 += dy;
					static_cast<CLSVGPathSegCurvetoCubicRel*>(seg)->m_x2 += dx;
					static_cast<CLSVGPathSegCurvetoCubicRel*>(seg)->m_y2 += dy;
				}
				break;

			case PATHSEG_CURVETO_QUADRATIC_ABS:
				{
					static_cast<CLSVGPathSegCurvetoQuadraticAbs*>(seg)->m_x += dx;
					static_cast<CLSVGPathSegCurvetoQuadraticAbs*>(seg)->m_y += dy;
					static_cast<CLSVGPathSegCurvetoQuadraticAbs*>(seg)->m_x1 += dx;
					static_cast<CLSVGPathSegCurvetoQuadraticAbs*>(seg)->m_y1 += dy;
				}
				break;

			case PATHSEG_CURVETO_QUADRATIC_REL:
				{
					static_cast<CLSVGPathSegCurvetoQuadraticRel*>(seg)->m_x += dx;
					static_cast<CLSVGPathSegCurvetoQuadraticRel*>(seg)->m_y += dy;
					static_cast<CLSVGPathSegCurvetoQuadraticRel*>(seg)->m_x1 += dx;
					static_cast<CLSVGPathSegCurvetoQuadraticRel*>(seg)->m_y1 += dy;
				}
				break;

			case PATHSEG_CLOSEPATH:
				{
				}
				break;

			default:
				ASSERT(0);
			}
		}

		ChangedSeg();
	}
#endif
}

}	// Web
}
