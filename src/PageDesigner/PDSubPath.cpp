#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDSubPath.h"

#include "PDDocument.h"

#include "gmVec2.h"

/////////////////////////
// CPDSubPath

_bstr_t CPDSubPath::saveString()
{
	_bstr_t str;

	if (m_closed)
		str = L"c";
	else
		str = L"o";

	WCHAR str2[512];

	for (int i = 0; i < m_points.GetSize(); i++)
	{
		CBezierPoint& pt = m_points[i];

		if (i > 0)
			str += L",";

		if (pt.x == pt.x1 && pt.x == pt.x2 &&
			pt.y == pt.y1 && pt.y == pt.y2)	// Moveto/Lineto
		{
			swprintf(str2, L"%g %g", pt.x, pt.y);
			str += str2;
		}
		else	// Cubic bezier
		{
			swprintf(str2, L"%g %g %g %g %g %g", pt.x, pt.y, pt.x1, pt.y1, pt.x2, pt.y2);
			str += str2;
		}
	}

	return str;
}

BSTR CPDSubPath::parseString(BSTR s)
{
	WCHAR* p = s;

	if (*p == 0) return NULL;

	if (*p == L'c')
		m_closed = VARIANT_TRUE;
	else if (*p == L'o')
		m_closed = VARIANT_FALSE;
	else
		return NULL;

	p++;

	while (*p && !iswalpha(*p))
	{
		while (iswspace(*p)) p++;

		CArray<double,double> numbers;

	// Collect numbers upto comma
		while ((*p) && (*p != L','))
		{
		// Collect one number
			int n = 0;
			WCHAR nstr[256];
			while ((*p) && (*p != ',') && !iswspace(*p) && !iswalpha(*p))
			{
				nstr[n++] = *p++;
			}

			nstr[n] = 0;
			numbers.Add(atof(_bstr_t(nstr)));

			while (iswspace(*p)) p++;
		}

		if (*p == L',') p++;

		if (numbers.GetSize() == 2)
		{
			CBezierPoint pt(numbers[0], numbers[1], numbers[0], numbers[1], numbers[0], numbers[1]);
			m_points.Add(pt);
		}
		else if (numbers.GetSize() == 6)
		{
			CBezierPoint pt(numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]);
			m_points.Add(pt);
		}
		else
			return NULL;
	}

	return p;
}

STDMETHODIMP CPDSubPath::get_closed(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_closed;
	return S_OK;
}

STDMETHODIMP CPDSubPath::put_closed(VARIANT_BOOL newVal)
{
	if ((m_closed == 0) != (newVal == 0))
	{
		m_closed = newVal? VARIANT_TRUE: VARIANT_FALSE;
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	}

	return S_OK;
}

STDMETHODIMP CPDSubPath::reverse()
{
	int npoints = m_points.GetSize();

	for (int i = 0; i < (npoints+1)/2; i++)
	{
		CBezierPoint bpt = m_points[npoints-i-1];

		m_points[npoints-i-1].x1 = m_points[i].x2;
		m_points[npoints-i-1].y1 = m_points[i].y2;
		m_points[npoints-i-1].x = m_points[i].x;
		m_points[npoints-i-1].y = m_points[i].y;
		m_points[npoints-i-1].x2 = m_points[i].x1;
		m_points[npoints-i-1].y2 = m_points[i].y1;

		m_points[i].x1 = bpt.x2;
		m_points[i].y1 = bpt.y2;
		m_points[i].x = bpt.x;
		m_points[i].y = bpt.y;
		m_points[i].x2 = bpt.x1;
		m_points[i].y2 = bpt.y1;
	}

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDSubPath::get_pointCount(long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_points.GetSize();
	return S_OK;
}

STDMETHODIMP CPDSubPath::getPoint(long index, BezierPoint *pVal)
{
	*pVal = m_points[index];
	return S_OK;
}

STDMETHODIMP CPDSubPath::setPoint(long index, BezierPoint *point)
{
	m_points[index] = *point;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

void SetEllipseBezier(BezierPoint* cCtlPt, double left, double top, double right, double bottom)
{
	double width = right-left;
	double height = bottom-top;

    // MAGICAL CONSTANT to map ellipse to beziers
   //  			2/3*(sqrt(2)-1) 
    const double EToBConst =	0.2761423749154; 
    CDblPoint offset;
	 offset.x = width * EToBConst;
	 offset.y = height * EToBConst;
//  Use the following line instead for mapping systems where +ve Y is upwards
//  CSize offset((int)(r.Width() * EToBConst), -(int)(r.Height() * EToBConst));

    CDblPoint centre;
	 centre.x = (left + right) / 2;
	 centre.y = (top + bottom) / 2;

	cCtlPt[0].x1 =
	cCtlPt[0].x = 
	cCtlPt[0].x2 = left;

	cCtlPt[1].x1 = centre.x-offset.x;
	cCtlPt[1].x = centre.x;
	cCtlPt[1].x2 = centre.x + offset.x;

	cCtlPt[2].x1 =
	cCtlPt[2].x = 
	cCtlPt[2].x2 = right;

	cCtlPt[3].x1 = centre.x+offset.x;
	cCtlPt[3].x = centre.x;
	cCtlPt[3].x2 = centre.x - offset.x;

	cCtlPt[0].y1 = centre.y+offset.y;
	cCtlPt[0].y = centre.y;
	cCtlPt[0].y2 = centre.y-offset.y;

	cCtlPt[1].y1 =
	cCtlPt[1].y = 
	cCtlPt[1].y2 = top;

	cCtlPt[2].y1 = centre.y-offset.y;
	cCtlPt[2].y = centre.y;
	cCtlPt[2].y2 = centre.y+offset.y;

	cCtlPt[3].y1 =
	cCtlPt[3].y = 
	cCtlPt[3].y2 = bottom;
}

STDMETHODIMP CPDSubPath::setEllipse(double left, double top, double right, double bottom)
{
	m_points.RemoveAll();	// Just in case there's something there before
	m_points.SetSize(4);
	m_closed = VARIANT_TRUE;

	SetEllipseBezier(m_points.GetData(), left, top, right, bottom);

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDSubPath::setRectangle(double left, double top, double right, double bottom)
{
	m_points.RemoveAll();
	m_points.SetSize(4);
	m_closed = VARIANT_TRUE;

	m_points[0].x = left;
	m_points[0].x1 = left;
	m_points[0].x2 = left;
	m_points[0].y = top;
	m_points[0].y1 = top;
	m_points[0].y2 = top;

	m_points[1].x = right;
	m_points[1].x1 = right;
	m_points[1].x2 = right;
	m_points[1].y = top;
	m_points[1].y1 = top;
	m_points[1].y2 = top;

	m_points[2].x = right;
	m_points[2].x1 = right;
	m_points[2].x2 = right;
	m_points[2].y = bottom;
	m_points[2].y1 = bottom;
	m_points[2].y2 = bottom;

	m_points[3].x = left;
	m_points[3].x1 = left;
	m_points[3].x2 = left;
	m_points[3].y = bottom;
	m_points[3].y1 = bottom;
	m_points[3].y2 = bottom;

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDSubPath::setLine(double x1, double y1, double x2, double y2)
{
	m_points.RemoveAll();
	m_points.SetSize(2);
	m_closed = VARIANT_FALSE;

	m_points[0].x1 = x1;
	m_points[0].y1 = y1;
	m_points[0].x = x1;
	m_points[0].y = y1;
	m_points[0].x2 = x1;
	m_points[0].y2 = y1;

	m_points[1].x1 = x2;
	m_points[1].y1 = y2;
	m_points[1].x = x2;
	m_points[1].y = y2;
	m_points[1].x2 = x2;
	m_points[1].y2 = y2;

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

void CPDSubPath::RenderToGraphicsPath(Gdiplus::GraphicsPath* path)
{
	int npoints = m_points.GetSize();

	if (npoints > 0)
	{
		path->StartFigure();

		for (int i = 1; i < npoints; i++)
		{
			path->AddBezier(
				(float)m_points[i-1].x, (float)m_points[i-1].y,
				(float)m_points[i-1].x2, (float)m_points[i-1].y2,
				(float)m_points[i].x1, (float)m_points[i].y1,
				(float)m_points[i].x, (float)m_points[i].y
				);
		}

		if (m_closed)
		{
			path->AddBezier(
				(float)m_points[i-1].x, (float)m_points[i-1].y,
				(float)m_points[i-1].x2, (float)m_points[i-1].y2,
				(float)m_points[0].x1, (float)m_points[0].y1,
				(float)m_points[0].x, (float)m_points[0].y
				);

			path->CloseFigure();
		}
	}
}

STDMETHODIMP CPDSubPath::Move(double dx, double dy)
{
	for (int i = 0; i < m_points.GetSize(); i++)
	{
		m_points[i].Move(dx, dy);
	}

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDSubPath::appendPoint(double x, double y, double x1, double y1, double x2, double y2, long *pVal)
{
	if (pVal == NULL) return E_POINTER;

	CBezierPoint pt(x, y, x1, y1, x2, y2);
	*pVal = m_points.Add(pt);

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDSubPath::insertPoint(long index, double x, double y, double x1, double y1, double x2, double y2)
{
	// TODO: Add your implementation code here

	return S_OK;
}

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

double GetCurveT(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double length, double* pt)
{
	double length2 = 0;

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

STDMETHODIMP CPDSubPath::getLength(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	double length = 0;

	if (m_points.GetSize() > 0)
	{
		BezierPoint point0 = m_points[0];

		for (int i = 1; i < m_points.GetSize(); i++)
		{
			BezierPoint point = m_points[i];

			double l = CalcCurveLength(
				point0.x, point0.y,
				point0.x2, point0.y2,
				point.x1, point.y1,
				point.x, point.y);

			point0 = point;

			length += l;
		}

		if (m_closed)
		{
			BezierPoint point = m_points[0];

			double l = CalcCurveLength(
				point0.x, point0.y,
				point0.x2, point0.y2,
				point.x1, point.y1,
				point.x, point.y);

			length += l;
		}
	}

	*pVal = length;

	return S_OK;
}

static double GetAngle(double dx, double dy)
{
	double distance = sqrt(dx*dx + dy*dy);
	double distance2 = distance;

	if (distance2 == 0.0) distance2 = 0.00001;
	if (dy < 0) distance2 =-distance2;
	double angle = acos(dx/distance2);
	if (dy < 0) angle += M_PI;

	return angle * 180/M_PI;
}

STDMETHODIMP CPDSubPath::getPointOnLength(double onlength, double *pxt, double *pyt, double *pangle)
{
	if (pxt == NULL) return E_POINTER;
	if (pyt == NULL) return E_POINTER;
	if (pangle == NULL) return E_POINTER;

	double length = 0;

	if (m_points.GetSize() > 0)
	{
		BezierPoint point0 = m_points[0];

		for (int i = 1; i < m_points.GetSize(); i++)
		{
			BezierPoint point = m_points[i];

			double x0 = point0.x;
			double y0 = point0.y;
			double x1 = point0.x2;
			double y1 = point0.y2;
			double x2 = point.x1;
			double y2 = point.y1;
			double x3 = point.x;
			double y3 = point.y;

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

				*pangle = GetAngle(dx, dy);

				return S_OK;
			}

			length += l;

			point0 = point;
		}

		if (m_closed)
		{
			BezierPoint point = m_points[0];

			double x0 = point0.x;
			double y0 = point0.y;
			double x1 = point0.x2;
			double y1 = point0.y2;
			double x2 = point.x1;
			double y2 = point.y1;
			double x3 = point.x;
			double y3 = point.y;

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

				*pangle = GetAngle(dx, dy);

				return S_OK;
			}

			length += l;
		}
	}

	return E_FAIL;
}

void SplitBezier(
	const gmVector2& P00, const gmVector2& P01, const gmVector2& P02, const gmVector2& P03,
	double t, gmVector2& P10, gmVector2& P11, gmVector2& P12, gmVector2& P20, gmVector2& P21, gmVector2& P30);

STDMETHODIMP CPDSubPath::insertAnchorPointAt(long segment, double t)
{
	gmVector2 P10, P11, P12;
	gmVector2 P20, P21;
	gmVector2 P30;

	CBezierPoint& segmentpt0 = m_points[segment];
	CBezierPoint& segmentpt1 = (segment < m_points.GetSize()-1)? m_points[segment+1]: m_points[0];

	SplitBezier(
		gmVector2(segmentpt0.x, segmentpt0.y),
		gmVector2(segmentpt0.x2, segmentpt0.y2),
		gmVector2(segmentpt1.x1, segmentpt1.y1),
		gmVector2(segmentpt1.x, segmentpt1.y),
		t,
		P10, P11, P12, P20, P21, P30);

	CBezierPoint bezpt;
	bezpt.x1 = P20[0];
	bezpt.y1 = P20[1];
	bezpt.x = P30[0];
	bezpt.y = P30[1];
	bezpt.x2 = P21[0];
	bezpt.y2 = P21[1];

	segmentpt0.x2 = P10[0];
	segmentpt0.y2 = P10[1];

	segmentpt1.x1 = P12[0];
	segmentpt1.y1 = P12[1];

	m_points.InsertAt(segment+1, bezpt);

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDSubPath::deleteAnchorPoint(long index)
{
	if (index >= 0 && index < m_points.GetSize())
	{
		m_points.RemoveAt(index);
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

		return S_OK;
	}
	else
	{
		ATLASSERT(0);
		return E_FAIL;
	}
}

STDMETHODIMP CPDSubPath::appendSubPathPoints(IPDSubPath *subpath)
{
	if (subpath == NULL) return E_INVALIDARG;

	long npoints;
	subpath->get_pointCount(&npoints);
	for (long i = 0; i < npoints; i++)
	{
		CBezierPoint bpt;
		subpath->getPoint(i, &bpt);

		m_points.Add(bpt);
	}

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDSubPath::removeAllPoints()
{
	m_points.RemoveAll();
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}
