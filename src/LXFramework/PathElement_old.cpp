#include "stdafx.h"
#include "resource.h"
#include "WebEditor.h"
#include "SvgEditor2.h"

#include "Element.h"
#include "ESvgDocument.h"
//#include "SvgLayoutView.h"

BOOL ParsePathData(ISVGPathElement* pathElement, ISVGPathSegList* segList, CUString str_pathdata);
_bstr_t StringFromPathSegList(ISVGPathSegList* seglist);

void DrawPathSegList(ISVGPathSegList* seglist, HDC iDC, ISVGMatrix* xform);

CComQIPtr<ISVGPathSegList> GetPathSegList(CElement* pElement);
void PutPathSegList(CElement* pElement, CComQIPtr<ISVGPathSegList> seglist);

/*
Given a bezier and a point close to the bezier but not necessarily on it,
I want to find the value of t for the nearest point on the bezier.

Right now I am using a brute force approach as shown below. Are there
any better ways to do this?

//
// Given a bezier and a point near the bezier, find value of 't'
// for the point.
// 0 <= t <= 1
//
// Return false if point is too far from the bezier.
//
*/
static
bool bezier_find_t_for_point(
   double x0, double y0, double x1, double y1, // bezier coordinates
   double x2, double y2, double x3, double y3, // bezier coordinates
   double split_x, double split_y, // point close to the bezier but not on it
   double tolerance, // above point is atmost this far from the bezier
   double *pt, // result should be stored here
   double *pDistanceSquared // square of distance from point to bezier
   )
{
/*
   if (!in_bezier_bbox(x0, y0, x1, y1, x2, y2, x3, y3,
                       fabs(tolerance), split_x, split_y))
      return false;
*/

   double ax, ay, bx, by, cx, cy;
   double t;
   double xt, yt;
   bool  found = false;
   double dsquared;
   double t_;

   cx = 3 * (x1 - x0);
   cy = 3 * (y1 - y0);
   bx = 3 * (x2 - x1) - cx;
   by = 3 * (y2 - y1) - cy;
   ax = x3 - x0 - cx - bx;
   ay = y3 - y0 - cy - by;
   for (t = 0.0; t <= 1.0; t += 0.001)
   {
      xt = ax * t*t*t + bx * t*t + cx * t + x0;
      yt = ay * t*t*t + by * t*t + cy * t + y0;
      if (fabs(split_x - xt) <= tolerance &&
          fabs(split_y - yt) <= tolerance)
      {
         double temp = (xt - split_x)*(xt - split_x) +
                      (yt - split_y)*(yt - split_y);
         if (found)
         {
            if (temp > dsquared)
               break;
         }
         found = true;
         dsquared = temp;
         t_ = t;
      }
   }

   if (found)
   {
      if (pt) *pt = (1 - t_);
      if (pDistanceSquared) *pDistanceSquared = dsquared;
      return true;
   }

   return false;
}

BOOL GetPointOnSegList(ISVGPathSegList* seglist, double mousex, double mousey, double tolerance, long* segindex, double* pt)
{
	float oldx = 0;
	float oldy = 0;

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	for (unsigned long i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ISVGPathSeg> seg;
		seglist->getItem(i, &seg);

		_tagSVGPathSegType segType;
		seg->get_pathSegType(&segType);

		if (segType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ISVGPathSegMovetoAbs> movetoabs = seg;

			movetoabs->get_x(&oldx);
			movetoabs->get_y(&oldy);
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg;

			float x, y, x1, y1, x2, y2;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
			cubictoabs->get_x1(&x1);
			cubictoabs->get_y1(&y1);
			cubictoabs->get_x2(&x2);
			cubictoabs->get_y2(&y2);

			bool bOnCurve = bezier_find_t_for_point(
				oldx, oldy, x1, y1, // bezier coordinates
				x2, y2, x, y, // bezier coordinates
				mousex, mousey, // point close to the bezier but not on it
				tolerance, // above point is atmost this far from the bezier
				pt, // result should be stored here
				NULL//double *pDistanceSquared // square of distance from point to bezier
			);

			if (bOnCurve)
			{
				*segindex = i;
				return TRUE;
			}

			oldx = x;
			oldy = y;
		}
	}

	return FALSE;
}

void CPathElement::SelectSegment(int index)
{
	ATLASSERT(!IsSegmentSelected(index));

// TODO, have it sorted ??
	m_selectedPoints.Add(index);
}

BOOL CPathElement::IsSegmentSelected(int index)
{
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] == index) return TRUE;
	}

	return FALSE;
}

void CPathElement::DeselectSegment(int index)
{
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] == index)
		{
			m_selectedPoints.RemoveAt(i);
			return;
		}
	}
}

#define MATCHPOINT(x1, y1, x2, y2) ((fabs((x2)-(x1)) <= 4) && \
												(fabs((y2)-(y1)) <= 4))

void CPathElement::AddFlatCurve(int, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double& oldxt, double& oldyt, int& count)
{
	double ax, ay, bx, by, cx, cy;
	double t;
	double xt, yt;

	cx = 3 * (x1 - x0);
	cy = 3 * (y1 - y0);
	bx = 3 * (x2 - x1) - cx;
	by = 3 * (y2 - y1) - cy;
	ax = x3 - x0 - cx - bx;
	ay = y3 - y0 - cy - by;

	double tinc = 1/120.0;

	for (t = 0.0; t <= 1.0; t += tinc)
	{
		xt = ax * t*t*t + bx * t*t + cx * t + x0;
		yt = ay * t*t*t + by * t*t + cy * t + y0;

		if ((xt != oldxt || yt != oldyt))
		{
			m_flatPoints.Add(CDblPoint(xt, yt));
			count++;

			oldxt = xt;
			oldyt = yt;
		}
	}
}

void CPathElement::SetPolyPointsFromSegList()
{
	CComQIPtr<ISVGAnimatedPathData> pathData = m_domElement;

	CComQIPtr<ISVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	m_subPoints.RemoveAll();
	m_flatPoints.RemoveAll();

	float lastmovex = 0;
	float lastmovey = 0;
	float oldx = 0;
	float oldy = 0;

	int count = 0;

	double oldxt = -99999;
	double oldyt = -99999;

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ISVGPathSeg> seg;
		seglist->getItem(i, &seg);

		_tagSVGPathSegType pathSegType;
		seg->get_pathSegType(&pathSegType);

		if (pathSegType == PATHSEG_MOVETO_ABS)
		{
			if (i > 0)
			{
				m_subPoints.Add(count);
				oldxt = -99999;
				oldyt = -99999;
				count = 0;
			}

			CComQIPtr<ISVGPathSegMovetoAbs> movetoabs = seg;
			float x; movetoabs->get_x(&x);
			float y; movetoabs->get_y(&y);

			lastmovex = x;
			lastmovey = y;
			oldx = x;
			oldy = y;
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg;
			double x0 = oldx;
			double y0 = oldy;
			float x1; cubictoabs->get_x1(&x1);
			float y1; cubictoabs->get_y1(&y1);
			float x2; cubictoabs->get_x2(&x2);
			float y2; cubictoabs->get_y2(&y2);
			float x3; cubictoabs->get_x(&x3);
			float y3; cubictoabs->get_y(&y3);

			AddFlatCurve(i, x0, y0, x1, y1, x2, y2, x3, y3, oldxt, oldyt, count);

			oldx = x3;
			oldy = y3;
		}
	}

	if (count > 0)
	{
		m_subPoints.Add(count);
	}

	TRACE("subs: %d - points: %d\n", m_subPoints.GetSize(), m_flatPoints.GetSize());

/*
	UPOSITION pos = GetBezList()->GetHeadPosition();
	while (pos)
	{
		CBezier* pBez = (CBezier*)GetBezList()->GetNext(pos);
		int numpoints = pBez->m_pointArray.GetSize();

		if (numpoints > 3)
		{
			CAPoint* points = pBez->m_pointArray.GetData();

			int count = 0;

			double oldxt = -99999;
			double oldyt = -99999;

			double dx = 0;
			double dy = 0;

			CAPoint* pts = &points[1];

			for (int i = 1; i < numpoints-4; i += 3, pts += 3)
			{
				double x0 = pts[0].x;
				double y0 = pts[0].y;

				double x1 = pts[1].x;
				double y1 = pts[1].y;

				double x2 = pts[2].x;
				double y2 = pts[2].y;

				double x3 = pts[3].x;
				double y3 = pts[3].y;

				AddFlatCurve(i, x0, y0, x1, y1, x2, y2, x3, y3, oldxt, oldyt, count);
			}

			if (pBez->m_bClosed)
			{
				double x0 = points[numpoints-2].x;
				double y0 = points[numpoints-2].y;

				double x1 = points[numpoints-1].x;
				double y1 = points[numpoints-1].y;

				double x2 = points[0].x;
				double y2 = points[0].y;

				double x3 = points[1].x;
				double y3 = points[1].y;

				AddFlatCurve(i, x0, y0, x1, y1, x2, y2, x3, y3, oldxt, oldyt, count);
			}

			m_subPoints.Add(count);
		}
	}
*/
}

#include "..\Animator2D\GraphicsGems.h"

typedef Point2 *BezierCurve;
void FitCurve(Point2	*d, int nPts, double error);

CComQIPtr<ISVGPathElement> g_pathElement;
ISVGPathSegList* g_pathSegList;
int g_pathSize;

void DrawBezierCurve(int n, BezierCurve curve)
{
	if (g_pathSize == 0)
	{
		CComQIPtr<ISVGPathSegMovetoAbs> seg;
		g_pathElement->createSVGPathSegMovetoAbs(curve[0].x, curve[0].y,
			&seg);

		g_pathSegList->appendItem(seg, NULL);

		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg2;
		g_pathElement->createSVGPathSegCurvetoCubicAbs(
			curve[3].x, curve[3].y,
			curve[1].x, curve[1].y,
			curve[2].x, curve[2].y,
			&seg2);

		g_pathSegList->appendItem(seg2, NULL);

		g_pathSize += 2;
	}
	else
	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		g_pathElement->createSVGPathSegCurvetoCubicAbs(
			curve[3].x, curve[3].y,
			curve[1].x, curve[1].y,
			curve[2].x, curve[2].y,
			&seg);

		g_pathSegList->appendItem(seg, NULL);

		g_pathSize++;
	}
}

void CPathElement::ConvertFlatToCurves(ISVGPathSegList* seglist)
{
	CComQIPtr<ISVGAnimatedPathData> pathData = m_domElement;

	g_pathElement = m_domElement;
	g_pathSegList = seglist;

	int count = 0;
	for (int sub = 0; sub < m_subPoints.GetSize(); sub++)
	{
		int size = m_subPoints[sub];
		CDblPoint* points = m_flatPoints.GetData() + count;
		count += size;

		g_pathSize = 0;
		double	error = 25.0;		//  Squared error

		FitCurve((Point2*)points, size, error);		//  Fit the Bezier curves
	}
}

void CPathElement::DrawPolyPoints(HDC hDC)
{
	int ipt = 0;
	CDblPoint* points = m_flatPoints.GetData();

	for (int sub = 0; sub < m_subPoints.GetSize(); sub++)
	{
		int count = m_subPoints[sub];

		MoveToEx(hDC, points[ipt].x, points[ipt].y, NULL);
		ipt++;
		
		for (int i = 1; i < count; i++)
		{
			LineTo(hDC, points[ipt].x, points[ipt].y);
			ipt++;
		}
	}
}

int CPathElement::FindPoint(ISVGPathSegList* seglist, ISVGMatrix* matrix, double mousex, double mousey, int& ctl)
{
	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ISVGPathSeg> seg;
		seglist->getItem(i, &seg);

		float x, y;

		_tagSVGPathSegType pathSegType;
		seg->get_pathSegType(&pathSegType);

		if (pathSegType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ISVGPathSegMovetoAbs> movetoabs = seg;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
		}

		CComQIPtr<ISVGPoint> pt;
		pt.CoCreateInstance(CLSID_SVGPoint);
		pt->put_x(x);
		pt->put_y(y);

		CComQIPtr<ISVGPoint> xpt;
		pt->matrixTransform(matrix, &xpt);
		xpt->get_x(&x);
		xpt->get_y(&y);

		if (MATCHPOINT(mousex, mousey, x, y))
		{
			ctl = 0;
			return i;
		}

		if (IsSegmentSelected(i))
		{
			if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
			{
				CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg;
				float x2; cubictoabs->get_x2(&x2);
				float y2; cubictoabs->get_y2(&y2);

				if (MATCHPOINT(x2, y2, mousex, mousey))
				{
					ctl = -1;
					return i;
				}
			}

			if (i < numberOfItems-1)
			{
				CComQIPtr<ISVGPathSeg> seg1;
				seglist->getItem(i+1, &seg1);

				CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubicseg1 = seg1;
				if (cubicseg1)
				{
					float x1; cubicseg1->get_x1(&x1);
					float y1; cubicseg1->get_y1(&y1);

					if (MATCHPOINT(x1, y1, mousex, mousey))
					{
						ctl = 1;
						return i;
					}
				}
			}
		}
	}

	return -1;
}

double GetLineDistance(float x1, float y1, float x2, float y2)
{
	double dx = x2-x1;
	double dy = y2-y1;
	double distance = sqrt(dx*dx + dy*dy);

	return distance;
}

double GetLineAngle(double distance, float x1, float y1, float x2, float y2)
{
	double dx = x2-x1;
	double dy = y2-y1;

	double distance2 = distance;

	if (distance2 == 0.0) distance2 = 0.00001;
	if (dy < 0) distance2 =-distance2;
	double angle = acos(dx/distance2);
	if (dy < 0) angle += M_PI;

	return angle;
}

// Sets the control points, the control points are opposite and same length
void CPathElement::SetPathSegControlPointsSameLength(ISVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly)
{
	seglist->LockUpdate();

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	CComQIPtr<ISVGPathSeg> seg;
	seglist->getItem(segindex, &seg);

	CComQIPtr<ISVGPathSegCurvetoCubicAbs> curveto = seg;

	if (ctlindex == -1)
	{
		curveto->put_x2(ctlx);
		curveto->put_y2(ctly);

		float x; curveto->get_x(&x);
		float y; curveto->get_y(&y);

		double distance = GetLineDistance(x, y, ctlx, ctly);
		double angle = GetLineAngle(distance, x, y, ctlx, ctly);

		angle += M_PI;

		float x1 = cos(angle)*distance + x;
		float y1 = sin(angle)*distance + y;

		if (segindex < numberOfItems-1)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> curveto2;
			seglist->getItem(segindex+1, (ISVGPathSeg**)&curveto2);

			curveto2->put_x1(x1);
			curveto2->put_y1(y1);
		}
		else
		{
			m_lastx = x1;
			m_lasty = y1;
		}
	}
	else if (ctlindex == 1)
	{
		if (segindex < numberOfItems-1)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> curveto2;
			seglist->getItem(segindex+1, (ISVGPathSeg**)&curveto2);

			curveto2->put_x1(ctlx);
			curveto2->put_y1(ctly);
		}
		else
		{
			m_lastx = ctlx;
			m_lasty = ctly;
		}

		if (curveto)
		{
			float x; curveto->get_x(&x);
			float y; curveto->get_y(&y);

			double distance = GetLineDistance(x, y, ctlx, ctly);
			double angle = GetLineAngle(distance, x, y, ctlx, ctly);

			angle += M_PI;

			float x2 = cos(angle)*distance + x;
			float y2 = sin(angle)*distance + y;

			curveto->put_x2(x2);
			curveto->put_y2(y2);
		}
	}
	else
		ATLASSERT(0);

	seglist->UnlockUpdate();
}

class CPathSeg
{
public:
	float x0, y0;
	float x1, y1;
	float x2, y2;
};

CPathSeg CPathElement::GetPathSeg(ISVGPathSegList* seglist, int segindex)
{
	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	if (segindex > 0)
	{
	}
}

void CPathElement::PutPathSeg(ISVGPathSegList* seglist, int segindex. CPathSeg& seg)
{
	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

}

void CPathElement::SetPathSegControlPoints(ISVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly)
{
	seglist->LockUpdate();

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	CComQIPtr<ISVGPathSeg> seg;
	seglist->getItem(segindex, &seg);

	CComQIPtr<ISVGPathSegCurvetoCubicAbs> curveto = seg;

	if (ctlindex == -1)
	{
		curveto->put_x2(ctlx);
		curveto->put_y2(ctly);

		if (segindex < numberOfItems-1)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> curveto2;
			seglist->getItem(segindex+1, (ISVGPathSeg**)&curveto2);

			float x; curveto2->get_x(&x);
			float y; curveto2->get_y(&y);
			float 
			double dx = ctlx-x;
			double dy = ctly-y;
		}

		double distance = sqrt(dx*dx + dy*dy);
		double distance2 = distance;

		if (distance2 == 0.0) distance2 = 0.00001;
		if (dy < 0) distance2 =-distance2;
		double angle = acos(dx/distance2);
		if (dy < 0) angle += M_PI;

		angle += M_PI;

		float x1 = cos(angle)*distance + x;
		float y1 = sin(angle)*distance + y;


			curveto2->put_x1(x1);
			curveto2->put_y1(y1);
		}
		else
		{
			m_lastx = x1;
			m_lasty = y1;
		}
	}
	else if (ctlindex == 1)
	{
		if (segindex < numberOfItems-1)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> curveto2;
			seglist->getItem(segindex+1, (ISVGPathSeg**)&curveto2);

			curveto2->put_x1(ctlx);
			curveto2->put_y1(ctly);
		}
		else
		{
			m_lastx = ctlx;
			m_lasty = ctly;
		}

		if (curveto)
		{
			float x; curveto->get_x(&x);
			float y; curveto->get_y(&y);

			double dx = ctlx-x;
			double dy = ctly-y;

			double distance = sqrt(dx*dx + dy*dy);
			double distance2 = distance;

			if (distance2 == 0.0) distance2 = 0.00001;
			if (dy < 0) distance2 =-distance2;
			double angle = acos(dx/distance2);
			if (dy < 0) angle += M_PI;

			angle += M_PI;

			float x2 = cos(angle)*distance + x;
			float y2 = sin(angle)*distance + y;

			curveto->put_x2(x2);
			curveto->put_y2(y2);
		}
	}
	else
		ATLASSERT(0);

	seglist->UnlockUpdate();
}

void CPathElement::SetPathSegControlPoint(ISVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly)
{
}

#if 0
void GetAnimationList(CComQIPtr<ISVGElement> parent, CComQIPtr<ISVGElement> target, CArray<ISVGAnimationElement*, ISVGAnimationElement*>& list)
{
	CComQIPtr<IDOMNode> node;
	parent->get_firstChild(&node);

	while (node != NULL)
	{
		_tagDOMNodeType nodeType;
		node->get_nodeType(&nodeType);

		if (nodeType == NODE_ELEMENT)
		{
			CComQIPtr<ISVGAnimationElement> animation = node;
			if (animation)
			{
				CComQIPtr<
				if (animation->targetElement == target)
					list.Add(animation);
			}
			else
			{
			// Recurse
				GetAnimationList(node, target, list);
			}
		}

		node = node->nextSibling;
	}
}
#endif

void DeleteAnchorPoint(ISVGPathSegList* seglist, int segindex)
{
	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubic;
	seglist->getItem(segindex, (ISVGPathSeg**)&cubic);

	CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubic2;
	if (segindex < numberOfItems-1)
		seglist->getItem(segindex+1, (ISVGPathSeg**)&cubic2);

	seglist->LockUpdate();

	if (cubic2 != NULL)
	{
		float x1;
		float y1;

		cubic->get_x1(&x1);
		cubic->get_y1(&y1);

		cubic2->put_x1(x1);
		cubic2->put_y1(y1);
	}

	seglist->removeItem(segindex, NULL);

	seglist->UnlockUpdate();
}

typedef struct _FPoint
{
	float x, y;
}
CFPoint;

void InsertAnchorPoint(ISVGPathElement* path, ISVGPathSegList* seglist, int segindex, double t)
{
	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	ATLASSERT(segindex > 0);

	double ratio = 1.0 - t;
	ATLASSERT((ratio >= 0.0) && (ratio <= 1.0));

	seglist->LockUpdate();

	CFPoint P00, P01, P02, P03;
	CFPoint P10, P11, P12;
	CFPoint P20, P21;
	CFPoint P30;

	ATLASSERT(segindex > 0);

	CComQIPtr<ISVGPathSeg> segprev;
	seglist->getItem(segindex-1, &segprev);

	_tagSVGPathSegType seg0Type;
	segprev->get_pathSegType(&seg0Type);

	if (seg0Type == PATHSEG_MOVETO_ABS)
	{
		CComQIPtr<ISVGPathSegMovetoAbs> seg0 = segprev;
		seg0->get_x(&P00.x);
		seg0->get_y(&P00.y);
	}
	else if (seg0Type == PATHSEG_CURVETO_CUBIC_ABS)
	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg0 = segprev;
		seg0->get_x(&P00.x);
		seg0->get_y(&P00.y);
	}

	CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg1;
	seglist->getItem(segindex, (ISVGPathSeg**)&seg1);

	seg1->get_x1(&P01.x);
	seg1->get_y1(&P01.y);

	seg1->get_x2(&P02.x);
	seg1->get_y2(&P02.y);

	seg1->get_x(&P03.x);
	seg1->get_y(&P03.y);

//	P00 = &m_pointArray[n+0];
//	P01 = &m_pointArray[n+1];
//	P02 = &m_pointArray[n+2];
//	P03 = &m_pointArray[n+3];
	
	/* De Casteljau algorithme 
	[Advanced Animation & Randering Technics / Alan & Mark WATT]
	[ADDISON WESLEY ref 54412]
	Iteratif way of drawing a Bezier curve by geometrical approch 
	
	  P0x represent the four controls points ( anchor / control /control /anchor ) 
	  P30 represent the new anchor point to add on the curve 
	  P2x represent the new control points of P30
	  P1x represent the new values of the control points P01 and P02
	  
		 so if we moves ratio from 0 to 1 we draw the all curve between P00 and P03
	*/
	
	P10.x = ((1-ratio)*P00.x + ratio * P01.x);
	P10.y = ((1-ratio)*P00.y + ratio * P01.y);
	
	P11.x = (1-ratio)*P01.x + ratio * P02.x;
	P11.y = (1-ratio)*P01.y + ratio * P02.y;
	
	P12.x = (1-ratio)*P02.x + ratio * P03.x;
	P12.y = (1-ratio)*P02.y + ratio * P03.y;
	
	P20.x = (1-ratio)*P10.x + ratio * P11.x;
	P20.y = (1-ratio)*P10.y + ratio * P11.y;
	
	P21.x = (1-ratio)*P11.x + ratio * P12.x;
	P21.y = (1-ratio)*P11.y + ratio * P12.y;
	
	P30.x = (1-ratio)*P20.x + ratio * P21.x;
	P30.y = (1-ratio)*P20.y + ratio * P21.y;
	
//
//	P01.x = P10.x;
//	P01.y = P10.y;
//	P02.x = P12.x;
//	P02.y = P12.y;

	seg1->put_x1(P21.x);
	seg1->put_y1(P21.y);
	seg1->put_x2(P12.x);
	seg1->put_y2(P12.y);
	
	/* All the computes are done, let's insert the new point on the curve */
	
	CComQIPtr<ISVGPathSegCurvetoCubicAbs> curveto;
	path->createSVGPathSegCurvetoCubicAbs(
		P30.x, P30.y,
		P10.x, P10.y,	// x1,y1
		P20.x, P20.y,
		&curveto
		);

	seglist->insertItemBefore(curveto, segindex, NULL);

//	CDblPoint	apt1;
//	apt1.x = P20.x; apt1.y = P20.y;
	
//	CAPoint	apt2;
//	apt2.x = P30.x; apt2.y = P30.y;
	
//	CAPoint	apt3;
//	apt3.x = P21.x; apt3.y = P21.y;
/*	
	m_pointArray.InsertAt(n+2, apt1);
	m_pointArray.InsertAt(n+3, apt2);
	m_pointArray.InsertAt(n+4, apt3);
*/
	seglist->UnlockUpdate();
}

void CPathElement::DeleteAnchorPoint(int segindex)
{
	m_selectedPoints.RemoveAll();

	CComQIPtr<ISVGPathElement> path = m_domElement;
	CComQIPtr<ISVGAnimatedPathData> pathData = path;

	CComQIPtr<ISVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	::DeleteAnchorPoint(seglist, segindex);

#if 0
	CArray<SVGLib::ISVGAnimationElement*, SVGLib::ISVGAnimationElement*> list;
	GetAnimationList(m_pDocument->GetDOMDocument()->documentElement, m_domElement, list);

	// Do it for all animations as well
	for (int i = 0; i < list.GetSize(); i++)
	{
		SVGLib::ISVGAnimationElementPtr animation = list[i];

		_bstr_t attributeName = animation->getAttribute(L"attributeName");

		if (attributeName.length() > 0 && !wcscmp(attributeName, L"d"))
		{
			// from
			{
				SVGLib::ISVGPathSegListPtr seglist;
				seglist.CreateInstance("SVG.SVGPathSegList");

				_bstr_t pathstr = animation->getAttribute(L"from");
				ParsePathData(path, seglist, CUString((BSTR)pathstr));

				::DeleteAnchorPoint(seglist, segindex);

				pathstr = StringFromPathSegList(seglist);
				animation->setAttribute(L"from", pathstr);
			}

			// to
			{
				SVGLib::ISVGPathSegListPtr seglist;
				seglist.CreateInstance("SVG.SVGPathSegList");

				_bstr_t pathstr = animation->getAttribute(L"to");
				ParsePathData(path, seglist, CUString((BSTR)pathstr));

				::DeleteAnchorPoint(seglist, segindex);

				pathstr = StringFromPathSegList(seglist);
				animation->setAttribute(L"to", pathstr);
			}
		}
	}
#endif
}

void CPathElement::InsertAnchorPoint(int segindex, double t)
{
	m_selectedPoints.RemoveAll();

	CComQIPtr<ISVGPathElement> path = m_domElement;
	CComQIPtr<ISVGAnimatedPathData> pathData = path;

	CComQIPtr<ISVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	::InsertAnchorPoint(path, seglist, segindex, t);

// Do it for all animations as well
#if 0
	CArray<ISVGAnimationElement*, ISVGAnimationElement*> list;

	CComQIPtr<IDOMElement> documentElement;
	m_pDocument->GetDOMDocument()->get_documentElement(&documentElement);

	GetAnimationList(documentElement, m_domElement, list);

	for (int i = 0; i < list.GetSize(); i++)
	{
		CComQIPtr<ISVGAnimationElement> animation = list[i];

		BSTR battributeName;
		animation->getAttribute(L"attributeName", &battributeName);
		_bstr_t attributeName = _bstr_t(battributeName, false);

		if (attributeName.length() > 0 && !wcscmp(attributeName, L"d"))
		{
			// from
			{
				SVGLib::ISVGPathSegListPtr seglist;
				seglist.CreateInstance("SVG.SVGPathSegList");

				_bstr_t pathstr = animation->getAttribute(L"from");
				ParsePathData(path, seglist, CUString((BSTR)pathstr));

				::InsertAnchorPoint(path, seglist, segindex, t);

				pathstr = StringFromPathSegList(seglist);
				animation->setAttribute(L"from", pathstr);
			}

			// to
			{
				SVGLib::ISVGPathSegListPtr seglist;
				seglist.CreateInstance("SVG.SVGPathSegList");

				_bstr_t pathstr = animation->getAttribute(L"to");
				ParsePathData(path, seglist, CUString((BSTR)pathstr));

				::InsertAnchorPoint(path, seglist, segindex, t);

				pathstr = StringFromPathSegList(seglist);
				animation->setAttribute(L"to", pathstr);
			}
		}
	}
#endif
}

void CPathElement::ReleaseCompound()
{
#if 0
	CElement* pParent = (CElement*)m_parent;

	m_selectedPoints.RemoveAll();

	SVGLib::IDOMNodePtr beforeNode = m_domElement->nextSibling;

	SVGLib::ISVGAnimatedPathDataPtr pathData = m_domElement;
	SVGLib::ISVGPathSegListPtr segList = pathData->normalizedPathSegList;

	unsigned long numberOfItems = segList->numberOfItems;

	SVGLib::ISVGPathElementPtr destPath;
	SVGLib::ISVGAnimatedPathDataPtr destPathData;
	SVGLib::ISVGPathSegListPtr destSegList;

	for (unsigned long i = 0; i < numberOfItems; i++)
	{
		SVGLib::ISVGPathSegPtr seg = segList->getItem(i);
		SVGLib::_tagSVGPathSegType segType = seg->pathSegType;

		if ((segType == SVGLib::PATHSEG_MOVETO_ABS) ||
			(segType == SVGLib::PATHSEG_MOVETO_REL) ||
			(segType == SVGLib::PATHSEG_CLOSEPATH))
		{
			if (destSegList != NULL)
			{
				destSegList->UnlockUpdate();
			}

			destPath = m_pDocument->GetDOMDocument()->createElement(L"path");
			destPathData = destPath;
			destSegList = destPathData->normalizedPathSegList;

			destSegList->LockUpdate();

			destPath->setAttribute(L"style", m_domElement->getAttribute(L"style"));

			if (beforeNode)
				pParent->m_domElement->insertBefore(destPath, beforeNode);
			else
				pParent->m_domElement->appendChild(destPath);
		}

		ATLASSERT(destPath != NULL);

		seg->AddRef();
		destSegList->appendItem(seg);
	}

	if (destSegList != NULL)
	{
		destSegList->UnlockUpdate();
	}

	pParent->m_domElement->removeChild(m_domElement);
#endif
}

void CPathElement::MovePoints(ISVGPathSegList* seglist, double dx, double dy, BOOL bAll /* = TRUE */)
{
	seglist->LockUpdate();

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	for (int index = 0; index < numberOfItems; index++)
	{
		if (bAll || IsSegmentSelected(index))
		{
			CComQIPtr<ISVGPathSeg> seg;
			seglist->getItem(index, &seg);

			CComQIPtr<ISVGPathSeg> seg2;

			if (index < numberOfItems-1) seglist->getItem(index+1, &seg2);

			_tagSVGPathSegType pathSegType;
			seg->get_pathSegType(&pathSegType);

			if (pathSegType == PATHSEG_MOVETO_ABS)
			{
				CComQIPtr<ISVGPathSegMovetoAbs> movetoabs = seg;
				float x; movetoabs->get_x(&x);
				float y; movetoabs->get_y(&y);

				movetoabs->put_x(x + dx);
				movetoabs->put_y(y + dy);
			}
			else if (pathSegType == PATHSEG_LINETO_ABS)
			{
				CComQIPtr<ISVGPathSegLinetoAbs> linetoabs = seg;
				float x; linetoabs->get_x(&x);
				float y; linetoabs->get_y(&y);
				linetoabs->put_x(x + dx);
				linetoabs->put_y(y + dy);
			}
			else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
			{
				CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg;
				float x; cubictoabs->get_x(&x);
				float y; cubictoabs->get_y(&y);
			//	float x1; cubictoabs->get_x1(&x1);
			//	float y1; cubictoabs->get_y1(&y1);
				float x2; cubictoabs->get_x2(&x2);
				float y2; cubictoabs->get_y2(&y2);

				cubictoabs->put_x(x + dx);
				cubictoabs->put_y(y + dy);
			//	cubictoabs->put_x1(x1 + dx);
			//	cubictoabs->put_y1(y1 + dy);
				cubictoabs->put_x2(x2 + dx);
				cubictoabs->put_y2(y2 + dy);
			}

			if (seg2)
			{
				_tagSVGPathSegType pathSegType2;
				seg2->get_pathSegType(&pathSegType2);

				if (pathSegType2 == PATHSEG_CURVETO_CUBIC_ABS)
				{
					CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg2;

			//		float x; cubictoabs->get_x(&x);
			//		float y; cubictoabs->get_y(&y);
					float x1; cubictoabs->get_x1(&x1);
					float y1; cubictoabs->get_y1(&y1);
			//		float x2; cubictoabs->get_x2(&x2);
			//		float y2; cubictoabs->get_y2(&y2);

			//		cubictoabs->put_x(x + dx);
			//		cubictoabs->put_y(y + dy);
					cubictoabs->put_x1(x1 + dx);
					cubictoabs->put_y1(y1 + dy);
			//		cubictoabs->put_x2(x2 + dx);
			//		cubictoabs->put_y2(y2 + dy);
				}
			}
			else
			{
				m_lastx += dx;
				m_lasty += dy;
			}
		}
	}

	seglist->UnlockUpdate();
}

//#include "DrawSession.h"

void CPathElement::DrawPathCurve(ISVGPathSegList* seglist, ISVGMatrix* addmatrix, HDC hDC)
{
	CComQIPtr<ISVGTransformable> transformable = m_domElement;

	CComQIPtr<ISVGMatrix> matrix0;
	transformable->getScreenCTM(&matrix0);

	CComQIPtr<ISVGMatrix> matrix;
	matrix0->multiply(addmatrix, &matrix);

	COLORREF m_shapeOutlineColor = RGB(96, 96, 255);
	COLORREF m_shapeWingColor = RGB(96, 96, 255);
	COLORREF m_shapeSelectedColor = RGB(255, 0, 0);
	int m_knobSize = 2;

//	HPEN	outlinepen = CreatePen(PS_SOLID, 1, m_shapeOutlineColor);
//	HPEN	wingpen = CreatePen(PS_SOLID, 1, m_shapeWingColor);
//	HBRUSH wingbrush = CreateSolidBrush(m_shapeWingColor);
	HBRUSH selectedbrush = CreateSolidBrush(m_shapeSelectedColor);
	
	HPEN hOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);
	HBRUSH hOldBrush = (HBRUSH)GetCurrentObject(hDC, OBJ_BRUSH);

	::DrawPathSegList(seglist, hDC, matrix);

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	int i;

	SelectObject(hDC, GetStockObject(NULL_BRUSH));

	for (i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ISVGPathSeg> seg;
		seglist->getItem(i, &seg);

		_tagSVGPathSegType pathSegType;
		seg->get_pathSegType(&pathSegType);

		float x, y;

		if (pathSegType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ISVGPathSegMovetoAbs> movetoabs = seg;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

			if (matrix)
			{
				CComQIPtr<ISVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);
				pt->put_x(x);
				pt->put_y(y);

				CComQIPtr<ISVGPoint> xpt;
				pt->matrixTransform(matrix, &xpt);
				xpt->get_x(&x);
				xpt->get_y(&y);
			}
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);

			if (matrix)
			{
				CComQIPtr<ISVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);
				pt->put_x(x);
				pt->put_y(y);

				CComQIPtr<ISVGPoint> xpt;
				pt->matrixTransform(matrix, &xpt);
				xpt->get_x(&x);
				xpt->get_y(&y);
			}
		}

		int ix = x;
		int iy = y;

		Rectangle(hDC, ix-3, iy-3, ix+4, iy+4);
	}

	for (i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		int index = m_selectedPoints[i];
		ATLASSERT(index >= 0 && index < numberOfItems);

		CComQIPtr<ISVGPathSeg> seg;
		seglist->getItem(index, &seg);

		CComQIPtr<ISVGPathSeg> seg1;
		CComQIPtr<ISVGPathSeg> seg2;

		if (index > 0) seglist->getItem(index-1, &seg1);
		if (index < numberOfItems-1) seglist->getItem(index+1, &seg2);

		float x = 0, y = 0;
		float x1 = 0, y1 = 0;
		float x2 = 0, y2 = 0;

		BOOL b1 = FALSE;
		BOOL b2 = FALSE;

		_tagSVGPathSegType pathSegType;
		seg->get_pathSegType(&pathSegType);

		if (pathSegType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ISVGPathSegMovetoAbs> movetoabs = seg;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubicto = seg;
			cubicto->get_x(&x);
			cubicto->get_y(&y);
			cubicto->get_x2(&x1);
			cubicto->get_y2(&y1);
			b1 = TRUE;
		}

		if (seg2)
		{
			_tagSVGPathSegType pathSegType2;
			seg2->get_pathSegType(&pathSegType2);

			if (pathSegType2 == PATHSEG_CURVETO_CUBIC_ABS)
			{
				CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg2;
				cubictoabs->get_x1(&x2);
				cubictoabs->get_y1(&y2);
				b2 = TRUE;
			}
		}
		else
		{
			x2 = m_lastx;
			y2 = m_lasty;
			b2 = TRUE;
		}

		if (matrix)
		{
			CComQIPtr<ISVGPoint> pt;
			pt.CoCreateInstance(CLSID_SVGPoint);

			{
				pt->put_x(x);
				pt->put_y(y);

				CComQIPtr<ISVGPoint> xpt;
				pt->matrixTransform(matrix, &xpt);
				xpt->get_x(&x);
				xpt->get_y(&y);
			}

			if (b1)
			{
				pt->put_x(x1);
				pt->put_y(y1);

				CComQIPtr<ISVGPoint> xpt;
				pt->matrixTransform(matrix, &xpt);
				xpt->get_x(&x1);
				xpt->get_y(&y1);
			}

			if (b2)
			{
				pt->put_x(x2);
				pt->put_y(y2);

				CComQIPtr<ISVGPoint> xpt;
				pt->matrixTransform(matrix, &xpt);
				xpt->get_x(&x2);
				xpt->get_y(&y2);
			}
		}

	// Draw selected anchor point
		SelectObject(hDC, GetStockObject(BLACK_BRUSH));
		Rectangle(hDC, x-3, y-3, x+4, y+4);

//		SelectObject(hDC, outlinepen);

		if (b1)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x1, y1);
		//	ds->DrawLine(hDC, x, y, x1, y1);
		//	ds->Ellipse(hDC, x1-2, y1-2, x1+3, y1+3);
		}

		if (b2)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x2, y2);
		//	ds->DrawLine(hDC, x, y, x2, y2);
		//	ds->Ellipse(hDC, x2-2, y2-2, x2+3, y2+3);
		}
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

//	DeleteObject(outlinepen);
//	DeleteObject(wingpen);
//	DeleteObject(wingbrush);
	DeleteObject(selectedbrush);
}

void CPathElement::SelectPointsInRect(double x1, double y1, double x2, double y2)
{
	CComQIPtr<ISVGAnimatedPathData> pathData = m_domElement;

	CComQIPtr<ISVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	int npoints = 0;

	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ISVGPathSeg> seg;
		seglist->getItem(i, (ISVGPathSeg**)&seg);

		float x, y;

		_tagSVGPathSegType pathSegType;
		seg->get_pathSegType(&pathSegType);

		if (pathSegType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ISVGPathSegMovetoAbs> movetoabs = seg;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubictoabs = seg;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
		}

		if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
		{
			m_selectedPoints.Add(i);
			npoints++;
		}
	}

	if (npoints > 0)
	{
		m_pDocument->SetTargetElement(this, MK_SHIFT);
	}
}

void CPathElement::ReverseSelectedSubPaths()
{
#if 0
	CBezier* pOldBez = NULL;

	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		int npoint;
		CBezier* pBez = pTarget->GetLocalPoint(pTarget->m_selectedPoints[i], npoint);

		if (pBez != pOldBez)	// Only reverse path once
		{
			CAPoint* points = m_pointArray.GetData();
			int size = m_pointArray.GetSize();

			for (int i = 0; i < size/2; i++)
			{
				CAPoint t = points[i];
				points[i] = points[size-i-1];
				points[size-i-1] = t;
			}

			pBez->Reverse();
			pOldBez = pBez;
		}
	}
#endif
}

void CPathElement::DrawPathCurve(HDC hDC, ISVGMatrix* addmatrix)
{
	CComQIPtr<ISVGAnimatedPathData> pathData = m_domElement;

	CComQIPtr<ISVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	DrawPathCurve(seglist, addmatrix, hDC);
}

void CPathElement::Move(float dx, float dy)
{
//	CPathElement* pathElement = (CPathElement*)pTargetElement;
	
	CComQIPtr<ISVGPathSegList> seglist = GetPathSegList(this);
	MovePoints(seglist, dx, dy, TRUE);
	PutPathSegList(this, seglist);
}

void CPathElement::Scale(float cx, float cy, float sx, float sy)
{
//	CPathElement* pathElement = (CPathElement*)pTargetElement;
	/*
	SVGLib::ISVGPathSegListPtr seglist = GetPathSegList(pActiveElement);//pathData->normalizedPathSegList;
	pathElement->MovePoints(seglist, dx, dy, TRUE);
	PutPathSegList(pActiveElement, seglist);
	*/
}
