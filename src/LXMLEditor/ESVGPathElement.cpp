#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGPathElement.h"
#include "EXMLDocument.h"

#if 0

void DrawPathSegList(ILSVGPathSegList* seglist, Gdiplus::GraphicsPath* path, ILSVGMatrix* matrix);

HRESULT SetProperty(IUnknown* unk, BSTR name, VARIANT var);
_variant_t GetProperty(IUnknown* unk, BSTR name);

static bool in_bezier_bbox(
   double x0, double y0, double x1, double y1, // bezier coordinates
   double x2, double y2, double x3, double y3, // bezier coordinates
   double split_x, double split_y, // point close to the bezier but not on it
   double tolerance) // above point is atmost this far from the bezier
{
	double minx = min(x0, min(x1, min(x2, x3))) - tolerance;
	double miny = min(y0, min(y1, min(y2, y3))) - tolerance;
	double maxx = max(x0, max(x1, max(x2, x3))) + tolerance;
	double maxy = max(y0, max(y1, max(y2, y3))) + tolerance;

	return (split_x > minx && split_y > miny && split_x < maxx && split_y < maxy);
}

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
   if (!in_bezier_bbox(x0, y0, x1, y1, x2, y2, x3, y3,
                       split_x, split_y, fabs(tolerance)))
      return false;

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

BOOL GetPointNearPath(ILSVGPathSegList* segList, /*[in]*/ ILSVGMatrix* matrix, /*[in]*/ double mousex, /*[in]*/ double mousey, /*[in]*/ double tolerance, /*[out]*/ long* segindex, /*[out]*/ double* pt)
{
	double oldx = 0;
	double oldy = 0;

	long numberOfItems;
	segList->get_numberOfItems(&numberOfItems);

	for (long i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		segList->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);

		if (segType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

			movetoabs->get_x(&oldx);
			movetoabs->get_y(&oldy);
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

		//	ASSERT(0);	// TODO
			linetoabs->get_x(&oldx);
			linetoabs->get_y(&oldy);
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

double GetLineDistance(double x1, double y1, double x2, double y2)
{
	double dx = x2-x1;
	double dy = y2-y1;
	double distance = sqrt(dx*dx + dy*dy);

	return distance;
}

double GetLineAngle(double distance, double x1, double y1, double x2, double y2)
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

double GetLineAngle(double x1, double y1, double x2, double y2)
{
	double dx = x2-x1;
	double dy = y2-y1;

	double distance2 = sqrt(dx*dx + dy*dy);

	if (distance2 == 0.0) distance2 = 0.00001;
	if (dy < 0) distance2 =-distance2;
	double angle = acos(dx/distance2);
	if (dy < 0) angle += M_PI;

	return angle;
}

#include "ESelectedSVGPathElement.h"

/////////////////////////////////////////////////////////////////
// CPathElement

STDMETHODIMP CESVGPathElement::put_domElement(/*[in]*/ ILDOMElement* newVal)
{
	CESVGElementImpl<IESVGPathElement>::put_domElement(newVal);
	return S_OK;
}

STDMETHODIMP CESVGPathElement::CreateSelectedElement(IEXMLViewGroup* viewGroup, IESelectedElement* *pVal)
{
	ASSERT(0);
#if 0
	CComObject<CESelectedSVGPathElement>* pSelectedElement;
	CComObject<CESelectedSVGPathElement>::CreateInstance(&pSelectedElement);
	pSelectedElement->AddRef();
	pSelectedElement->m_pElement = this;//SetElement(this);
	pSelectedElement->m_viewGroup = viewGroup;

	*pVal = pSelectedElement;
#endif
	return S_OK;
}

void CESVGPathElement::AddFlatCurve(int, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double& oldxt, double& oldyt, int& count)
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
			m_flatPoints.Add(PointD(xt, yt));
			count++;

			oldxt = xt;
			oldyt = yt;
		}
	}
}

void CESVGPathElement::SetPolyPointsFromSegList()
{
	CComQIPtr<ILSVGAnimatedPathData> pathData = m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
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

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType pathSegType;
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

			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;
			double x; movetoabs->get_x(&x);
			double y; movetoabs->get_y(&y);

			lastmovex = x;
			lastmovey = y;
			oldx = x;
			oldy = y;
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;
			double x0 = oldx;
			double y0 = oldy;
			double x1; cubictoabs->get_x1(&x1);
			double y1; cubictoabs->get_y1(&y1);
			double x2; cubictoabs->get_x2(&x2);
			double y2; cubictoabs->get_y2(&y2);
			double x3; cubictoabs->get_x(&x3);
			double y3; cubictoabs->get_y(&y3);

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

#endif

#include "..\gm\GraphicsGems.h"

typedef Point2 *BezierCurve;
void FitCurve(Point2	*d, int nPts, double error);

#if 0
CComQIPtr<ILSVGPathElement> g_pathElement;
ILSVGPathSegList* g_pathSegList;
int g_pathSize;
#endif

void DrawBezierCurve(int n, BezierCurve curve)
{
	ASSERT(0);
#if 0
	if (g_pathSize == 0)
	{
		CComQIPtr<ILSVGPathSegMovetoAbs> seg;
		g_pathElement->createSVGPathSegMovetoAbs(curve[0].x, curve[0].y,
			&seg);

		g_pathSegList->appendItem(seg, NULL);

		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg2;
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
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg;
		g_pathElement->createSVGPathSegCurvetoCubicAbs(
			curve[3].x, curve[3].y,
			curve[1].x, curve[1].y,
			curve[2].x, curve[2].y,
			&seg);

		g_pathSegList->appendItem(seg, NULL);

		g_pathSize++;
	}
#endif
}

#if 0
void CESVGPathElement::ConvertFlatToCurves(ILSVGPathSegList* seglist)
{
	CComQIPtr<ILSVGAnimatedPathData> pathData = m_domElement;

	g_pathElement = m_domElement;
	g_pathSegList = seglist;

	int count = 0;
	for (int sub = 0; sub < m_subPoints.GetSize(); sub++)
	{
		int size = m_subPoints[sub];
		PointD* points = m_flatPoints.GetData() + count;
		count += size;

		g_pathSize = 0;
		double	error = 25.0;		//  Squared error

		FitCurve((Point2*)points, size, error);		//  Fit the Bezier curves
	}
}

void CESVGPathElement::DrawPolyPoints(HDC hDC)
{
	int ipt = 0;
	PointD* points = m_flatPoints.GetData();

	for (int sub = 0; sub < m_subPoints.GetSize(); sub++)
	{
		int count = m_subPoints[sub];

		MoveToEx(hDC, points[ipt].X, points[ipt].Y, NULL);
		ipt++;

		for (int i = 1; i < count; i++)
		{
			LineTo(hDC, points[ipt].X, points[ipt].Y);
			ipt++;
		}
	}
}

void CESVGPathElement::SetPathSegControlPoints(int segindex, int ctlindex, double ctlx, double ctly)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGPathElement> path = m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	seglist->LockUpdate();

	PointD seg[3];
	m_pPath->GetPathSeg(segindex, (CBezierPoint*)seg);

	seg[1+ctlindex].X = ctlx;
	seg[1+ctlindex].Y = ctly;

	double angle = GetLineAngle(ctlx, ctly, seg[1].X, seg[1].Y);
	double distance = GetLineDistance(seg[1].X, seg[1].Y, seg[1-ctlindex].X, seg[1-ctlindex].Y);

//	angle += M_PI;

	seg[1-ctlindex].X = cos(angle)*distance + seg[1].X;
	seg[1-ctlindex].Y = sin(angle)*distance + seg[1].Y;

//	m_path->setPoint(segindex, (BezierPoint*)seg);
	m_pPath->PutPathSeg(segindex, (CBezierPoint*)seg);

	seglist->UnlockUpdate();
#endif
}

// Sets the control points, the control points are opposite and same length
void CESVGPathElement::SetControlPointsSameLength(int segindex, int ctlindex, double ctlx, double ctly)
{
#if 0
	CComQIPtr<ILSVGPathElement> path = m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	seglist->LockUpdate();

	PointD seg[3];
	m_pPath->GetPathSeg(segindex, (CBezierPoint*)seg);

	seg[1+ctlindex].X = ctlx;
	seg[1+ctlindex].Y = ctly;

	double distance = GetLineDistance(ctlx, ctly, seg[1].X, seg[1].Y);
	double angle = GetLineAngle(distance, ctlx, ctly, seg[1].X, seg[1].Y);

//	angle += M_PI;

	seg[1-ctlindex].X = cos(angle)*distance + seg[1].X;
	seg[1-ctlindex].Y = sin(angle)*distance + seg[1].Y;

	m_pPath->PutPathSeg(segindex, (CBezierPoint*)seg);

	seglist->UnlockUpdate();
#endif
}

#if 0
// Sets the control points, the control points are opposite and same length
void CPathElement::SetPathSegControlPointsSameLength(ILSVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly)
{
	seglist->LockUpdate();

	CPathSeg seg = GetPathSeg(seglist, segindex);

	seg.x[1+ctlindex] = ctlx;
	seg.y[1+ctlindex] = ctly;

	double distance = GetLineDistance(ctlx, ctly, seg.x[1], seg.y[1]);
	double angle = GetLineAngle(distance, ctlx, ctly, seg.x[1], seg.y[1]);

//	angle += M_PI;

	seg.x[1-ctlindex] = cos(angle)*distance + seg.x[1];
	seg.y[1-ctlindex] = sin(angle)*distance + seg.y[1];

	PutPathSeg(seglist, segindex, seg);

	seglist->UnlockUpdate();
}
#endif

void CESVGPathElement::SetPathSegControlPoints(ILSVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly)
{
#if 0
	seglist->LockUpdate();

	CPathSeg seg = GetPathSeg(seglist, segindex);

	seg.x[1+ctlindex] = ctlx;
	seg.y[1+ctlindex] = ctly;

	double angle = GetLineAngle(ctlx, ctly, seg.x[1], seg.y[1]);
	double distance = GetLineDistance(seg.x[1], seg.y[1], seg.x[1-ctlindex], seg.y[1-ctlindex]);

//	angle += M_PI;

	seg.x[1-ctlindex] = cos(angle)*distance + seg.x[1];
	seg.y[1-ctlindex] = sin(angle)*distance + seg.y[1];

	PutPathSeg(seglist, segindex, seg);

	seglist->UnlockUpdate();
#endif
}

// Set the coordinates of one control point
void CESVGPathElement::SetPathSegControlPoint(ILSVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly)
{
	ASSERT(0);
#if 0
	seglist->LockUpdate();

	CPathSeg seg = GetPathSeg(seglist, segindex);

	seg.x[1+ctlindex] = ctlx;
	seg.y[1+ctlindex] = ctly;

	PutPathSeg(seglist, segindex, seg);

	seglist->UnlockUpdate();
#endif
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

void DeleteAnchorPoint(ILSVGPathSegList* seglist, int segindex)
{
	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubic;
	seglist->getItem(segindex, (ILSVGPathSeg**)&cubic);

	CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubic2;
	if (segindex < numberOfItems-1)
		seglist->getItem(segindex+1, (ILSVGPathSeg**)&cubic2);

	seglist->LockUpdate();

	if (cubic2 != NULL)
	{
		double x1;
		double y1;

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
	double x, y;
}
CFPoint;

void InsertAnchorPoint(ILSVGPathElement* path, ILSVGPathSegList* seglist, int segindex, double t)
{
	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	ASSERT(segindex > 0);

	double ratio = 1.0 - t;
	ASSERT((ratio >= 0.0) && (ratio <= 1.0));

	seglist->LockUpdate();

	CFPoint P00, P01, P02, P03;
	CFPoint P10, P11, P12;
	CFPoint P20, P21;
	CFPoint P30;

	ASSERT(segindex > 0);

	CComQIPtr<ILSVGPathSeg> segprev;
	seglist->getItem(segindex-1, &segprev);

	LSVGPathSegType seg0Type;
	segprev->get_pathSegType(&seg0Type);

	if (seg0Type == PATHSEG_MOVETO_ABS)
	{
		CComQIPtr<ILSVGPathSegMovetoAbs> seg0 = segprev;
		seg0->get_x(&P00.x);
		seg0->get_y(&P00.y);
	}
	else if (seg0Type == PATHSEG_CURVETO_CUBIC_ABS)
	{
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg0 = segprev;
		seg0->get_x(&P00.x);
		seg0->get_y(&P00.y);
	}

	CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg1;
	seglist->getItem(segindex, (ILSVGPathSeg**)&seg1);

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
	
	CComQIPtr<ILSVGPathSegCurvetoCubicAbs> curveto;
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


#if 0
void CPathElement::MovePoints(ILSVGPathSegList* seglist, double dx, double dy, BOOL bAll /* = TRUE */)
{
	seglist->LockUpdate();

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	for (int index = 0; index < numberOfItems; index++)
	{
		if (bAll || IsSegmentSelected(index))
		{
			CComQIPtr<ILSVGPathSeg> seg;
			seglist->getItem(index, &seg);

			CComQIPtr<ILSVGPathSeg> seg2;

			if (index < numberOfItems-1) seglist->getItem(index+1, &seg2);

			LSVGPathSegType pathSegType;
			seg->get_pathSegType(&pathSegType);

			if (pathSegType == PATHSEG_MOVETO_ABS)
			{
				CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;
				double x; movetoabs->get_x(&x);
				double y; movetoabs->get_y(&y);

				movetoabs->put_x(x + dx);
				movetoabs->put_y(y + dy);
			}
			else if (pathSegType == PATHSEG_LINETO_ABS)
			{
				CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;
				double x; linetoabs->get_x(&x);
				double y; linetoabs->get_y(&y);
				linetoabs->put_x(x + dx);
				linetoabs->put_y(y + dy);
			}
			else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;
				double x; cubictoabs->get_x(&x);
				double y; cubictoabs->get_y(&y);
			//	float x1; cubictoabs->get_x1(&x1);
			//	float y1; cubictoabs->get_y1(&y1);
				double x2; cubictoabs->get_x2(&x2);
				double y2; cubictoabs->get_y2(&y2);

				cubictoabs->put_x(x + dx);
				cubictoabs->put_y(y + dy);
			//	cubictoabs->put_x1(x1 + dx);
			//	cubictoabs->put_y1(y1 + dy);
				cubictoabs->put_x2(x2 + dx);
				cubictoabs->put_y2(y2 + dy);
			}

			if (seg2)
			{
				LSVGPathSegType pathSegType2;
				seg2->get_pathSegType(&pathSegType2);

				if (pathSegType2 == PATHSEG_CURVETO_CUBIC_ABS)
				{
					CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg2;

			//		float x; cubictoabs->get_x(&x);
			//		float y; cubictoabs->get_y(&y);
					double x1; cubictoabs->get_x1(&x1);
					double y1; cubictoabs->get_y1(&y1);
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
#endif

//#include "DrawSession.h"

#if 0
void CPathElement::DrawPathCurve(ILSVGPathSegList* seglist, ILSVGMatrix* addmatrix, HDC hDC)
{
	ASSERT(0);

	CComQIPtr<ILSVGTransformable> transformable = m_domElement;

	CComQIPtr<ILSVGMatrix> matrix0;
	transformable->getScreenCTM(&matrix0);

	CComQIPtr<ILSVGMatrix> matrix;
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

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	int i;

	SelectObject(hDC, GetStockObject(NULL_BRUSH));

	for (i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType pathSegType;
		seg->get_pathSegType(&pathSegType);

		double x, y;

		if (pathSegType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

			if (matrix)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_LSVGPoint);
				pt->put_x(x);
				pt->put_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(matrix, &xpt);
				xpt->get_x(&x);
				xpt->get_y(&y);
			}
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);

			if (matrix)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_LSVGPoint);
				pt->put_x(x);
				pt->put_y(y);

				CComQIPtr<ILSVGPoint> xpt;
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
		ASSERT(index >= 0 && index < numberOfItems);

		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(index, &seg);

		CComQIPtr<ILSVGPathSeg> seg1;
		CComQIPtr<ILSVGPathSeg> seg2;

		if (index > 0) seglist->getItem(index-1, &seg1);
		if (index < numberOfItems-1) seglist->getItem(index+1, &seg2);

		double x = 0, y = 0;
		double x1 = 0, y1 = 0;
		double x2 = 0, y2 = 0;

		BOOL b1 = FALSE;
		BOOL b2 = FALSE;

		LSVGPathSegType pathSegType;
		seg->get_pathSegType(&pathSegType);

		if (pathSegType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubicto = seg;
			cubicto->get_x(&x);
			cubicto->get_y(&y);
			cubicto->get_x2(&x1);
			cubicto->get_y2(&y1);
			b1 = TRUE;
		}

		if (seg2)
		{
			LSVGPathSegType pathSegType2;
			seg2->get_pathSegType(&pathSegType2);

			if (pathSegType2 == PATHSEG_CURVETO_CUBIC_ABS)
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg2;
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
			CComQIPtr<ILSVGPoint> pt;
			pt.CoCreateInstance(CLSID_LSVGPoint);

			{
				pt->put_x(x);
				pt->put_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(matrix, &xpt);
				xpt->get_x(&x);
				xpt->get_y(&y);
			}

			if (b1)
			{
				pt->put_x(x1);
				pt->put_y(y1);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(matrix, &xpt);
				xpt->get_x(&x1);
				xpt->get_y(&y1);
			}

			if (b2)
			{
				pt->put_x(x2);
				pt->put_y(y2);

				CComQIPtr<ILSVGPoint> xpt;
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
#endif

void CESVGPathElement::SelectPointsInRect(double x1, double y1, double x2, double y2)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGAnimatedPathData> pathData = GetElement()->m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	int npoints = 0;

	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, (ILSVGPathSeg**)&seg);

		double x, y;

		LSVGPathSegType pathSegType;
		seg->get_pathSegType(&pathSegType);

		if (pathSegType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);
		}
		else if (pathSegType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;
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
		ASSERT(0);
		//m_pDocument->SetTargetElement(this, MK_SHIFT);
	}
#endif
}

void CESVGPathElement::ReverseSelectedSubPaths()
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

#if 0
void CESVGPathElement::DrawPathCurve(HDC hDC, ILSVGMatrix* addmatrix)
{
	CComQIPtr<ILSVGAnimatedPathData> pathData = m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	DrawPathCurve(seglist, addmatrix, hDC);
}
#endif

#if 0
void MovePathSegList(ILSVGPathSegList* seglist, double dx, double dy)
{
	seglist->LockUpdate();

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

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
				
				double x, y;
				movetoabs->get_x(&x);
				movetoabs->get_y(&y);
				
				movetoabs->put_x(x+dx);
				movetoabs->put_y(y+dy);
			}
			break;
			
		case PATHSEG_LINETO_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;
				
				double x, y;
				linetoabs->get_x(&x);
				linetoabs->get_y(&y);
				
				linetoabs->put_x(x+dx);
				linetoabs->put_y(y+dy);
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
				
				cubictoabs->put_x(x+dx);
				cubictoabs->put_y(y+dy);
				cubictoabs->put_x1(x1+dx);
				cubictoabs->put_y1(y1+dy);
				cubictoabs->put_x2(x2+dx);
				cubictoabs->put_y2(y2+dy);
			}
			break;
		}
	}

	seglist->UnlockUpdate();
}
#endif

void ScalePathSegList(ILSVGPathSegList* seglist, double ox, double oy, double ox2, double oy2, double sx, double sy)
{
	seglist->LockUpdate();

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

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
				
				double x, y;
				movetoabs->get_x(&x);
				movetoabs->get_y(&y);
				double x2 = GetProperty(seg, L"x2");
				double y2 = GetProperty(seg, L"y2");
				double x3 = GetProperty(seg, L"x3");
				double y3 = GetProperty(seg, L"y3");

				movetoabs->put_x((x-ox)*sx+ox2);
				movetoabs->put_y((y-oy)*sy+oy2);
				SetProperty(seg, L"x2", _variant_t((x2-ox)*sx+ox2));
				SetProperty(seg, L"y2", _variant_t((y2-oy)*sy+oy2));
				SetProperty(seg, L"x3", _variant_t((x3-ox)*sx+ox2));
				SetProperty(seg, L"y3", _variant_t((y3-oy)*sy+oy2));
			}
			break;
			
		case PATHSEG_LINETO_ABS:
			{
				CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;
				
				double x, y;
				linetoabs->get_x(&x);
				linetoabs->get_y(&y);
				
				linetoabs->put_x((x-ox)*sx+ox2);
				linetoabs->put_y((y-oy)*sy+oy2);
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
				double x3 = GetProperty(seg, L"x3");
				double y3 = GetProperty(seg, L"y3");
				
				cubictoabs->put_x((x-ox)*sx+ox2);
				cubictoabs->put_y((y-oy)*sy+oy2);
				cubictoabs->put_x1((x1-ox)*sx+ox2);
				cubictoabs->put_y1((y1-oy)*sy+oy2);
				cubictoabs->put_x2((x2-ox)*sx+ox2);
				cubictoabs->put_y2((y2-oy)*sy+oy2);
				SetProperty(seg, L"x3", _variant_t((x3-ox)*sx+ox2));
				SetProperty(seg, L"y3", _variant_t((y3-oy)*sy+oy2));
			}
			break;
		}
	}

	seglist->UnlockUpdate();
}

STDMETHODIMP CESVGPathElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGAnimatedPathData> pathData = m_domElement;

	CComPtr<ILSVGPathSegList> seglist;
	pathData->get_pathSegList(&seglist);

	seglist->Offset(dx, dy);

	return S_OK;
}

STDMETHODIMP CESVGPathElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGPathElement> path = m_domElement;

	CComQIPtr<ILSVGAnimatedPathData> pathData = m_domElement;
	CComPtr<ILSVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILSVGRect> svgbounds;
	window->svgGetRBBox(path, &svgbounds);
	SVGRect bounds = svgbounds;

	/*
// TODO, bring view/GetHTMLWindow into consideration?
//	CComQIPtr<ILSVGTransformable> transformable = m_domElement;

	CComPtr<ILSVGRect> svgbounds;
	transformable->getRBBox(&svgbounds);
	SVGRect bounds = svgbounds;
	*/

	double ox = bounds.X;
	double oy = bounds.Y;
	double ox2 = x;
	double oy2 = y;
	double sx = width/bounds.Width;
	double sy = height/bounds.Height;

	if (fabs(sx) < 0.001) sx = 0.001;
	if (fabs(sy) < 0.001) sy = 0.001;

	ScalePathSegList(seglist, ox, oy, ox2, oy2, sx, sy);	
#endif

	return S_OK;
}

HRESULT CESVGPathElement::DrawOutline(ILSVGPathSegList* seglist, Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	Gdiplus::Pen pen(color);

	Gdiplus::GraphicsPath graphicsPath;
	::DrawPathSegList(seglist, &graphicsPath, matrix);

	pGraphics->DrawPath(&pen, &graphicsPath);

	return S_OK;
}

STDMETHODIMP CESVGPathElement::DrawOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	CComQIPtr<ILSVGAnimatedPathData> pathData = m_domElement;

	CComPtr<ILSVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	DrawOutline(seglist, pGraphics, color, matrix);

	return S_OK;
}

#if 0
void CPathElement::Scale(double ox, double oy, double sx, double sy)
{
	ASSERT(0);

// TODO, this can be optimized, first scale all the seglists points,
// then, scale all the subpaths first/last points
// instead of going through Get/PutPathSeg

//	CPathElement* pathElement = (CPathElement*)pTargetElement;
	/*
	SVGLib::ISVGPathSegListPtr seglist = GetPathSegList(pActiveElement);//pathData->normalizedPathSegList;
	pathElement->MovePoints(seglist, dx, dy, TRUE);
	PutPathSegList(pActiveElement, seglist);
	*/

	CComQIPtr<ILSVGPathElement> path = m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	seglist->LockUpdate();

	long nsubpaths = m_subPaths.GetSize();

	long ntotalpoints = 0;

	for (long nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CSubPath* subpath = m_subPaths[nsubpath];
		//m_path->getSubPath(nsubpath, &subpath);

		//VARIANT_BOOL closed;
		//subpath->get_closed(&closed);

		long numberOfItems;
		subpath->get_pointCount(&numberOfItems);

		/*
		{
			CComQIPtr<INotifySend> cp = subpath;
			cp->LockSend();
		}
		*/

		for (long index = 0; index < numberOfItems; index++)
		{
			//if (bAll || IsAnchorSelected(ntotalpoints+index))
			{
				CBezierPoint seg;
				//subpath->getPoint(index, &seg);
				GetPathSeg(seglist, index, &seg);

				/*
				BezierPoint seg1;
				if (index > 0)
					subpath->getPoint(index-1, &seg1);
				else if (closed)
					subpath->getPoint(numberOfItems-1, &seg1);

				BezierPoint seg2;
				if (index < numberOfItems-1)
					subpath->getPoint(index+1, &seg2);
				else if (closed)
					subpath->getPoint(0, &seg2);

				BezierBounds(numberOfItems, index, closed, seg, seg1, seg2, minx, miny, maxx, maxy);
				*/

				seg.x = (seg.x-ox)*sx+ox;
				seg.y = (seg.y-oy)*sy+oy;
				seg.x1 = (seg.x1-ox)*sx+ox;
				seg.y1 = (seg.y1-oy)*sy+oy;
				seg.x2 = (seg.x2-ox)*sx+ox;
				seg.y2 = (seg.y2-oy)*sy+oy;

				//BezierBounds(numberOfItems, index, closed, seg, seg1, seg2, minx, miny, maxx, maxy);

			//	subpath->setPoint(index, &seg);
				PutPathSeg(seglist, index, &seg);
			}
		}

		/*
		{
			CComQIPtr<INotifySend> cp = subpath;
			cp->UnlockSend();
		}
		*/

		ntotalpoints += numberOfItems;
	}

	/*
	{
		CComQIPtr<INotifySend> cp = m_path;
		cp->UnlockSend();
	}*/

	/*
	invalidBounds.X = minx;
	invalidBounds.Y = miny;
	invalidBounds.Width = maxx-minx;
	invalidBounds.Height = maxy-miny;
	*/

	seglist->UnlockUpdate();
}
#endif

//////////////////////////

#if 0
void CPathElement::DeleteAnchorPoint(int index)
{
	for (int i = m_selectedPoints.GetSize()-1; i >= 0; i--)
	{
		if (m_selectedPoints[i] == index)
		{
			m_selectedPoints.RemoveAt(i);
		}
		else if (m_selectedPoints[i] > index)
		{
			m_selectedPoints[i]--;
		}
	}

	m_path->deleteAnchorPoint(index);
}
#endif

HRESULT CESVGPathElement::HitTest(ILSVGPathSegList* seglist, ISVGView* view, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit)
{
	if (GetPointNearPath(seglist, ctm, ptx, pty, 2, &hit->segment, &hit->t))
	{
		hit->element = this;
		return S_OK;
	}

	return S_FALSE;
}


STDMETHODIMP CESVGPathElement::HitTest(ISVGView* view, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit)
{
	CComQIPtr<ILSVGAnimatedPathData> pathData = m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_pathSegList(&seglist);

	if (HitTest(seglist, view, svgsvgElement, ctm, ptx, pty, hit) == S_OK)
	{
		return S_OK;
	}

	return CESVGElementImpl<IESVGPathElement>::HitTest(view, svgsvgElement, ctm, ptx, pty, hit);
}

#endif