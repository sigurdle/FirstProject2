#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDPath.h"
#include "PDSubPath.h"

#include "ObjectMap.h"
#include "PDObjectImpl.h"
#include "PDObjectGroup.h"
#include "PDObjectShape.h"
#include "PDLayer.h"
#include "PDDocument.h"


void CalcCurveBBox(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double mx[4])
{
	double ax, ay, bx, by, cx, cy;

	cx = 3 * (x1 - x0);
	cy = 3 * (y1 - y0);
	bx = 3 * (x2 - x1) - cx;
	by = 3 * (y2 - y1) - cy;
	ax = x3 - x0 - cx - bx;
	ay = y3 - y0 - cy - by;

	double tinc = 1/50.0;

	for (double t = 0.0; t <= 1.0; t += tinc)
	{
		double xt = ax * t*t*t + bx * t*t + cx * t + x0;
		double yt = ay * t*t*t + by * t*t + cy * t + y0;

		if (xt < mx[0]) mx[0] = xt;
		if (yt < mx[1]) mx[1] = yt;
		if (xt > mx[2]) mx[2] = xt;
		if (yt > mx[3]) mx[3] = yt;
	}
}

/////////////////////////
// CPDPath

void CPDPath::RenderToGraphicsPath(Gdiplus::GraphicsPath* pPath)
{
	for (int i = 0; i < m_subPaths.GetSize(); i++)
	{
		CPDSubPath* pSubPath = m_subPaths[i];
		pSubPath->RenderToGraphicsPath(pPath);
	}
}

_bstr_t CPDPath::saveString()
{
	_bstr_t str = L"";

	for (int i = 0; i < m_subPaths.GetSize(); i++)
	{
		str += m_subPaths[i]->saveString();
	}

	return str;
}

void CPDPath::FinalRelease()
{
	for (int i = 0; i < m_subPaths.GetSize(); i++)
	{
		m_subPaths[i]->Unadvise(this);
		m_subPaths[i]->Release();
	}
	m_subPaths.RemoveAll();
}

HRESULT CPDPath::parseString(BSTR s)
{
	WCHAR* p = s;

	while (*p)
	{
		CComObject<CPDSubPath>* pSubPath;
		CComObject<CPDSubPath>::CreateInstance(&pSubPath);
		if (pSubPath)
		{
			pSubPath->AddRef();

			p = pSubPath->parseString(p);
			if (p)
			{
				pSubPath->AddRef();
				pSubPath->m_pOwnerPath = this;

				DWORD cookie;
				pSubPath->Advise(this, &cookie);

				m_subPaths.Add(pSubPath);
			}

			pSubPath->Release();

			if (p == NULL)
			{
				MessageBox(NULL, "Failed to parse path", "", MB_OK);
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CPDPath::get_subPathCount(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_subPaths.GetSize();
	return S_OK;
}

STDMETHODIMP CPDPath::get_pointCount(long *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = 0;
	for (int i = 0; i < m_subPaths.GetSize(); i++)
	{
		*pVal += m_subPaths[i]->m_points.GetSize();
	}

	return S_OK;
}

STDMETHODIMP CPDPath::setRectangle(double left, double top, double right, double bottom)
{
	removeSubPaths();

	CComObject<CPDSubPath>* pSubPath;
	CComObject<CPDSubPath>::CreateInstance(&pSubPath);
	if (pSubPath)
	{
		pSubPath->setRectangle(left, top, right, bottom);
	
		insertSubPath(-1, pSubPath);

		return S_OK;
	}

	return E_OUTOFMEMORY;
}

STDMETHODIMP CPDPath::insertPointBefore(long index, double x, double y, double x1, double y1, double x2, double y2)
{
// TODO not tested on multiple subpaths
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	m_subPaths[nsubpath]->m_points.InsertAt(index, CBezierPoint(x, y, x1, y1, x2, y2));

	FireOnChanged(NOTIFY_MODIFY, m_subPaths[nsubpath]->GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDPath::insertPointAfter(long index, double x, double y, double x1, double y1, double x2, double y2)
{
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	m_subPaths[nsubpath]->m_points.InsertAt(index+1, CBezierPoint(x, y, x1, y1, x2, y2));

	FireOnChanged(NOTIFY_MODIFY, m_subPaths[nsubpath]->GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDPath::getSubPath(long index, IPDSubPath **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (index >= 0 && index < m_subPaths.GetSize())
	{
		*pVal = m_subPaths[index];
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDPath::insertSubPath(long index, IPDSubPath *subPath)
{
	if (subPath == NULL) return E_INVALIDARG;

	CComObject<CPDSubPath>* pSubPath = (CComObject<CPDSubPath>*)subPath;

	pSubPath->AddRef();

// Remove first from previous path
	if (pSubPath->m_pOwnerPath != NULL)
	{
		pSubPath->m_pOwnerPath->removeSubPath(pSubPath);
	}

	pSubPath->m_pOwnerPath = this;

	DWORD cookie;
	pSubPath->Advise(this, &cookie);

	if (index < 0)
		m_subPaths.Add(pSubPath);
	else
		m_subPaths.InsertAt(index, pSubPath);

	FireOnChanged(NOTIFY_ADD, pSubPath->GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDPath::removeSubPathByIndex(long index, IPDSubPath **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (index >= 0 && index < m_subPaths.GetSize())
	{
		m_subPaths[index]->Unadvise(this);

		*pVal = m_subPaths[index];
		m_subPaths[index]->m_pOwnerPath = NULL;
		m_subPaths.RemoveAt(index);

		FireOnChanged(NOTIFY_REMOVE, *pVal, DISPID_UNKNOWN);
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDPath::removeSubPath(IPDSubPath *subpath)
{
	if (subpath == NULL) return E_INVALIDARG;

	int index;
	for (index = 0; index < m_subPaths.GetSize(); index++)
	{
		if (IsUnknownEqualUnknown(m_subPaths[index]->GetUnknown(), subpath))
		{
			break;
		}
	}

	if (index >= 0 && index < m_subPaths.GetSize())
	{
		m_subPaths[index]->Unadvise(this);
		m_subPaths[index]->m_pOwnerPath = NULL;
		m_subPaths.RemoveAt(index);

		FireOnChanged(NOTIFY_REMOVE, subpath, DISPID_UNKNOWN);

		subpath->Release();

		return S_OK;
	}

	ATLASSERT(0);
	return E_FAIL;
}

STDMETHODIMP CPDPath::getPoint(long index, BezierPoint *pVal)
{
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	*pVal = m_subPaths[nsubpath]->m_points[index];

	return S_OK;
}

STDMETHODIMP CPDPath::setPoint(long index, BezierPoint *point)
{
	if (point == NULL) return E_POINTER;

	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	m_subPaths[nsubpath]->m_points[index] = *point;

	FireOnChanged(NOTIFY_MODIFY, m_subPaths[nsubpath]->GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDPath::createSubPath(IPDSubPath **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDSubPath>* pSubPath;
	CComObject<CPDSubPath>::CreateInstance(&pSubPath);
	if (pSubPath)
	{
		*pVal = pSubPath;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDPath::Move(double dx, double dy)
{
	for (int i = 0; i < m_subPaths.GetSize(); i++)
	{
		m_subPaths[i]->Move(dx, dy);
	}

	return S_OK;
}

/*
offset (Bezier(p1,p2,p3,p4),distance) {
    
    normal1 = cross (p2 - p1); // crossing means x=y y=-x
    normal2 = cross (p3 - p2);
    normal3 = cross (p4 - p3);

    line1 = line(p1,p2) translated over (normal1*distance);
    line2 = line(p2,p3) translated over (normal2*distance);
    line3 = line(p3,p4) translated over (normal3*distance);

    new_p1 = p1 translated over (normal1*distance);
    new_p2 = intersection(line1,line2);
    new_p3 = intersection(line2,line3);
    new_p4 = p4 translated over (normal3*distance);
}
*/

	/*
				(Ay-Cy)(Dx-Cx)-(Ax-Cx)(Dy-Cy)
         r = -----------------------------  (eqn 1)
             (Bx-Ax)(Dy-Cy)-(By-Ay)(Dx-Cx)
 
             (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
         s = -----------------------------  (eqn 2)
             (Bx-Ax)(Dy-Cy)-(By-Ay)(Dx-Cx)
 
     Let P be the position vector of the intersection point, then
 
         P=A+r(B-A) or
 
         Px=Ax+r(Bx-Ax)
         Py=Ay+r(By-Ay)
			*/

gmVector2 intersection(const gmVector2& A, const gmVector2& B, const gmVector2& C, const gmVector2& D)
{
	gmVector2 P;

	double r = ((A[1]-C[1])*(D[0]-C[0])-(A[0]-C[0])*(D[1]-C[1])) /
					((B[0]-A[0])*(D[1]-C[1])-(B[1]-A[1])*(D[0]-C[0]));

	P[0] = A[0]+r*(B[0]-A[0]);
	P[1] = A[1]+r*(B[1]-A[1]);

	return P;
}

void OffsetBezier(
	gmVector2 p1, gmVector2 p2, gmVector2 p3, gmVector2 p4,
	double distance,
	gmVector2& new_p1, gmVector2& new_p2, gmVector2& new_p3, gmVector2& new_p4)
{
	gmVector2 normal1 = gmVector2(p2[1] - p1[1], -(p2[0] - p1[0]));
	gmVector2 normal2 = gmVector2(p3[1] - p2[1], -(p3[0] - p2[0]));
	gmVector2 normal3 = gmVector2(p4[1] - p3[1], -(p4[0] - p3[0]));

	normal1.normalize();
	normal2.normalize();
	normal3.normalize();

	gmVector2 sline1 = p1 + normal1*distance;
	gmVector2 eline1 = p2 + normal1*distance;

	gmVector2 sline2 = p2 + normal2*distance;
	gmVector2 eline2 = p3 + normal2*distance;

	gmVector2 sline3 = p3 + normal3*distance;
	gmVector2 eline3 = p4 + normal3*distance;

	new_p1 = p1 + normal1*distance;
	new_p2 = intersection(sline1, eline1, sline2, eline2);
	new_p3 = intersection(sline2, eline2, sline3, eline3);
	new_p4 = p4 + normal3*distance;
}

typedef struct _FPoint
{
	double x, y;
}
CFPoint;

void SplitBezier(
	const gmVector2& P00, const gmVector2& P01, const gmVector2& P02, const gmVector2& P03,
	double t, gmVector2& P10, gmVector2& P11, gmVector2& P12, gmVector2& P20, gmVector2& P21, gmVector2& P30)
{
	double ratio = 1.0 - t;
	ATLASSERT((ratio >= 0.0) && (ratio <= 1.0));

//	CFPoint P00, P01, P02, P03;
	/*
	CFPoint P10, P11, P12;
	CFPoint P20, P21;
	CFPoint P30;
	*/
/*

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
	
	P10[0] = ((1-ratio)*P00[0] + ratio * P01[0]);
	P10[1] = ((1-ratio)*P00[1] + ratio * P01[1]);
	
	P11[0] = (1-ratio)*P01[0] + ratio * P02[0];
	P11[1] = (1-ratio)*P01[1] + ratio * P02[1];
	
	P12[0] = (1-ratio)*P02[0] + ratio * P03[0];
	P12[1] = (1-ratio)*P02[1] + ratio * P03[1];
	
	P20[0] = (1-ratio)*P10[0] + ratio * P11[0];
	P20[1] = (1-ratio)*P10[1] + ratio * P11[1];
	
	P21[0] = (1-ratio)*P11[0] + ratio * P12[0];
	P21[1] = (1-ratio)*P11[1] + ratio * P12[1];
	
	P30[0] = (1-ratio)*P20[0] + ratio * P21[0];
	P30[1] = (1-ratio)*P20[1] + ratio * P21[1];
	
//
//	P01.x = P10.x;
//	P01.y = P10.y;
//	P02.x = P12.x;
//	P02.y = P12.y;

	/*
	seg1->put_x1(P21.x);
	seg1->put_y1(P21.y);
	seg1->put_x2(P12.x);
	seg1->put_y2(P12.y);
	*/
	
	/* All the computes are done, let's insert the new point on the curve */
/*	
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

	seglist->UnlockUpdate();
*/
}

class CBezier
{
public:
	CBezier* m_prev;
	CBezier* m_next;

	CBezier()
	{
		m_prev = NULL;
		m_next = NULL;
	}

	gmVector2 p1;
	gmVector2 p2;
	gmVector2 p3;
	gmVector2 p4;
};

CBezier* OffsetBezier(CBezier* bez, double distance, double tolerance)
{
	CBezier* new_bez = new CBezier;

	OffsetBezier(bez->p1, bez->p2, bez->p3, bez->p4, distance, new_bez->p1, new_bez->p2, new_bez->p3, new_bez->p4);

	double ax, ay, bx, by, cx, cy;
	cx = 3 * (bez->p2[0] - bez->p1[0]);
	cy = 3 * (bez->p2[1] - bez->p1[1]);
	bx = 3 * (bez->p3[0] - bez->p2[0]) - cx;
	by = 3 * (bez->p3[1] - bez->p2[1]) - cy;
	ax = bez->p4[0] - bez->p1[0] - cx - bx;
	ay = bez->p4[1] - bez->p1[1] - cy - by;

	double new_ax, new_ay, new_bx, new_by, new_cx, new_cy;
	new_cx = 3 * (new_bez->p2[0] - new_bez->p1[0]);
	new_cy = 3 * (new_bez->p2[1] - new_bez->p1[1]);
	new_bx = 3 * (new_bez->p3[0] - new_bez->p2[0]) - new_cx;
	new_by = 3 * (new_bez->p3[1] - new_bez->p2[1]) - new_cy;
	new_ax = new_bez->p4[0] - new_bez->p1[0] - new_cx - new_bx;
	new_ay = new_bez->p4[1] - new_bez->p1[1] - new_cy - new_by;

	double tinc = 1/50.0;

	double maxdistance_t;
	double maxdistance = 0;

	for (double t = 0.0; t <= 1.0; t += tinc)
	{
		double xt = ax * t*t*t + bx * t*t + cx * t + bez->p1[0];
		double yt = ay * t*t*t + by * t*t + cy * t + bez->p1[1];

		double new_xt = new_ax * t*t*t + new_bx * t*t + new_cx * t + new_bez->p1[0];
		double new_yt = new_ay * t*t*t + new_by * t*t + new_cy * t + new_bez->p1[1];

		double distance = (xt-new_xt)*(xt-new_xt) + (yt-new_yt)*(yt-new_yt);
		if (distance > maxdistance)
		{
			maxdistance = distance;
			maxdistance_t = t;
		}
	}

	double sqrtmaxdistance = sqrt(maxdistance);
	if (fabs(sqrtmaxdistance - distance) > tolerance)
	{
/*	  P0x represent the four controls points ( anchor / control /control /anchor ) 
	  P30 represent the new anchor point to add on the curve 
	  P2x represent the new control points of P30
	  P1x represent the new values of the control points P01 and P02
*/
		gmVector2 P10, P11, P12;
		gmVector2 P20, P21;
		gmVector2 P30;

		SplitBezier(bez->p1, bez->p2, bez->p3, bez->p4, maxdistance_t, P10, P11, P12, P20, P21, P30);

		CBezier* pBezLeft = new CBezier;
		pBezLeft->p1 = bez->p1;
		pBezLeft->p2 = P10;
		pBezLeft->p3 = P20;
		pBezLeft->p4 = P30;

		CBezier* pBezRight = new CBezier;
		pBezRight->p1 = P30;
		pBezRight->p2 = P21;
		pBezRight->p3 = P12;
		pBezRight->p4 = bez->p4;

		pBezLeft->m_next = pBezRight;
		pBezRight->m_prev = pBezLeft;

		CBezier* pBezLeft2 = OffsetBezier(pBezLeft, distance, tolerance);
		CBezier* pBezRight2 = OffsetBezier(pBezRight, distance, tolerance);

		pBezLeft2->m_next = pBezRight2;
		pBezRight2->m_prev = pBezLeft2;

		return pBezLeft2;
	}
	else
	{
		return new_bez;
	}
};

STDMETHODIMP CPDPath::offset(double distance, double tolerance, IPDPath *other)
{
	removeSubPaths();

//	if (pVal == NULL) return E_POINTER;

	//CComObject<CPDPath>* pNewPath = static_cast<CComObject<CPDPath>*>(this);
	CComObject<CPDPath>* pOtherPath = static_cast<CComObject<CPDPath>*>(other);
	//CComObject<CPDPath>::CreateInstance(&pNewPath);

	for (int nsubpath = 0; nsubpath < pOtherPath->m_subPaths.GetSize(); nsubpath++)
	{
		CPDSubPath* pSubPath = pOtherPath->m_subPaths[nsubpath];

		CComObject<CPDSubPath>* pNewSubPath;
		CComObject<CPDSubPath>::CreateInstance(&pNewSubPath);
		//pNewSubPath->AddRef();
		pNewSubPath->m_closed = pSubPath->m_closed;
		//pNewSubPath->m_pOwnerPath = pNewPath;
		//pNewPath->m_subPaths.Add(pNewSubPath);
		insertSubPath(-1, pNewSubPath);

		int npoints = pSubPath->m_points.GetSize();

	// First point
		gmVector2 p0 = gmVector2(pSubPath->m_points[0].x1, pSubPath->m_points[0].y1);
		gmVector2 p1 = gmVector2(pSubPath->m_points[0].x, pSubPath->m_points[0].y);
		gmVector2 normal0 = gmVector2(p1[1] - p0[1], -(p1[0] - p0[0]));
		normal0.normalize();

		gmVector2 new_p0 = p0 + normal0*distance;
		gmVector2 new_p1;

		for (int i = 1; i < npoints; i++)
		{
			gmVector2 p2 = gmVector2(pSubPath->m_points[i-1].x2, pSubPath->m_points[i-1].y2);
			gmVector2 p3 = gmVector2(pSubPath->m_points[i].x1, pSubPath->m_points[i].y1);
			gmVector2 p4 = gmVector2(pSubPath->m_points[i].x, pSubPath->m_points[i].y);

			gmVector2 new_p2;
			gmVector2 new_p3;
			gmVector2 new_p4;

			CBezier bez;
			bez.p1 = p1;
			bez.p2 = p2;
			bez.p3 = p3;
			bez.p4 = p4;

			CBezier* pNewBez = OffsetBezier(&bez, distance, tolerance);
			
			while (pNewBez)
			{
				CBezier* next = pNewBez->m_next;

				CBezierPoint point;
				point.x1 = new_p0[0];
				point.y1 = new_p0[1];
				point.x = pNewBez->p1[0];
				point.y = pNewBez->p1[1];
				point.x2 = pNewBez->p2[0];
				point.y2 = pNewBez->p2[1];
				pNewSubPath->m_points.Add(point);

				new_p1 = pNewBez->p1;
				new_p2 = pNewBez->p2;
				new_p3 = pNewBez->p3;
				new_p4 = pNewBez->p4;

				new_p0 = new_p3;
				new_p1 = new_p4;
				p1 = p4;

				delete pNewBez;
				pNewBez = next;
			}
		}

	// Last point
		CBezierPoint point;
		point.x1 = new_p0[0];
		point.y1 = new_p0[1];
		point.x = new_p1[0];
		point.y = new_p1[1];

		gmVector2 p2 = gmVector2(pSubPath->m_points[i-1].x2, pSubPath->m_points[i-1].y2);
		gmVector2 normal2 = gmVector2(p2[1] - p1[1], -(p2[0] - p1[0]));
		normal2.normalize();

		gmVector2 new_p2 = p2 + normal2*distance;
		point.x2 = new_p2[0];
		point.y2 = new_p2[1];

		pNewSubPath->m_points.Add(point);
	}

//	*pVal = pNewPath;
//	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPDPath::calculateBBox(IPDMatrix* matrix, RectD *bbox)
{
	double mx[4] =
	{
		99999, 99999,		// minx / miny
		-99999, -99999,		// maxx / maxy
	};

	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		CPDSubPath* pSubPath = m_subPaths[nsubpath];

		int npoints = pSubPath->m_points.GetSize();

		if (npoints > 1)
		{
			BezierPoint seg0 = pSubPath->m_points[0];

			BezierPoint xseg0;
			if (matrix)
				matrix->transformBezierPoint(&seg0, &xseg0);
			else
				xseg0 = seg0;

			BezierPoint _xseg0 = xseg0;

			for (int i = 1; i < npoints; i++)
			{
				BezierPoint seg = pSubPath->m_points[i];

				BezierPoint xseg;
				if (matrix)
					matrix->transformBezierPoint(&seg, &xseg);
				else
					xseg = seg;

				CalcCurveBBox(
					xseg0.x, xseg0.y,
					xseg0.x2, xseg0.y2,
					xseg.x1, xseg.y1,
					xseg.x, xseg.y,
					mx
					);

				xseg0 = xseg;
			}

			if (pSubPath->m_closed)
			{
				CalcCurveBBox(
					xseg0.x, xseg0.y,
					xseg0.x2, xseg0.y2,
					_xseg0.x1, _xseg0.y1,
					_xseg0.x, _xseg0.y,
					mx
					);
			}
		}
	}

	bbox->X = mx[0];
	bbox->Y = mx[1];
	bbox->Width = mx[2]-mx[0]+1;
	bbox->Height = mx[3]-mx[1]+1;

	return S_OK;
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

STDMETHODIMP CPDPath::getPointNearPath(IPDMatrix *matrix, double mousex, double mousey, double tolerance, long *segindex, double *pt, BOOL *pVal)
{
	long nsubpaths;
	get_subPathCount(&nsubpaths);

	long ntotalpoints = 0;

	for (int nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		getSubPath(nsubpath, &subpath);

		long npoints;
		subpath->get_pointCount(&npoints);

		if (npoints > 0)
		{
			BezierPoint seg0;
			subpath->getPoint(0, &seg0);

			BezierPoint xseg0;
			if (matrix)
				matrix->transformBezierPoint(&seg0, &xseg0);
			else
				xseg0 = seg0;

			for (long npoint = 1; npoint < npoints; npoint++)
			{
				BezierPoint seg;
				subpath->getPoint(npoint, &seg);

				BezierPoint xseg;
				if (matrix)
					matrix->transformBezierPoint(&seg, &xseg);
				else
					xseg = seg;

				bool bOnCurve = bezier_find_t_for_point(
					xseg0.x, xseg0.y,
					xseg0.x2, xseg0.y2,
					xseg.x1, xseg.y1,
					xseg.x, xseg.y,
					mousex, mousey, // point close to the bezier but not on it
					tolerance, // above point is atmost this far from the bezier
					pt, // result should be stored here
					NULL//double *pDistanceSquared // square of distance from point to bezier
				);

				if (bOnCurve)
				{
					*segindex = ntotalpoints + npoint-1;
					*pVal = TRUE;
					return S_OK;
				}

				xseg0 = xseg;
			}

			// TODO: closed
		}

		ntotalpoints += npoints;
	}

	*pVal = FALSE;

	return S_OK;
}

STDMETHODIMP CPDPath::getPointNearAnchorPoint(IPDMatrix *matrix, double mousex, double mousey, double tolerance, long *pIndex)
{
	if (pIndex == NULL) return E_POINTER;

	long nsubpaths;
	get_subPathCount(&nsubpaths);

	long ntotalpoints = 0;

	for (int nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		getSubPath(nsubpath, &subpath);

		long npoints;
		subpath->get_pointCount(&npoints);

		for (long npoint = 0; npoint < npoints; npoint++)
		{
			BezierPoint seg;
			subpath->getPoint(npoint, &seg);

			BezierPoint xseg;
			if (matrix)
				matrix->transformBezierPoint(&seg, &xseg);
			else
				xseg = seg;

			if ((fabs(xseg.x-mousex) <= tolerance) && (fabs(xseg.y-mousey) <= tolerance))
			{
				*pIndex = ntotalpoints + npoint;
				return S_OK;
			}
		}

		ntotalpoints += npoints;
	}

	*pIndex = -1;

	return S_OK;
}

STDMETHODIMP CPDPath::IsRectangular(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = VARIANT_FALSE;

	if (m_subPaths.GetSize() != 1) return S_OK;
	if (m_subPaths[0]->m_points.GetSize() != 4) return S_OK;

	double left = m_subPaths[0]->m_points[0].x;
	double right = m_subPaths[0]->m_points[1].x;
	double top = m_subPaths[0]->m_points[0].y;
	double bottom = m_subPaths[0]->m_points[2].y;

	if (m_subPaths[0]->m_points[0].x != left) return S_OK;
	if (m_subPaths[0]->m_points[0].x1 != left) return S_OK;
	if (m_subPaths[0]->m_points[0].x2 != left) return S_OK;
	if (m_subPaths[0]->m_points[0].y != top) return S_OK;
	if (m_subPaths[0]->m_points[0].y1 != top) return S_OK;
	if (m_subPaths[0]->m_points[0].y2 != top) return S_OK;

	if (m_subPaths[0]->m_points[1].x != right) return S_OK;
	if (m_subPaths[0]->m_points[1].x1 != right) return S_OK;
	if (m_subPaths[0]->m_points[1].x2 != right) return S_OK;
	if (m_subPaths[0]->m_points[1].y != top) return S_OK;
	if (m_subPaths[0]->m_points[1].y1 != top) return S_OK;
	if (m_subPaths[0]->m_points[1].y2 != top) return S_OK;

	if (m_subPaths[0]->m_points[2].x != right) return S_OK;
	if (m_subPaths[0]->m_points[2].x1 != right) return S_OK;
	if (m_subPaths[0]->m_points[2].x2 != right) return S_OK;
	if (m_subPaths[0]->m_points[2].y != bottom) return S_OK;
	if (m_subPaths[0]->m_points[2].y1 != bottom) return S_OK;
	if (m_subPaths[0]->m_points[2].y2 != bottom) return S_OK;

	if (m_subPaths[0]->m_points[3].x != left) return S_OK;
	if (m_subPaths[0]->m_points[3].x1 != left) return S_OK;
	if (m_subPaths[0]->m_points[3].x2 != left) return S_OK;
	if (m_subPaths[0]->m_points[3].y != bottom) return S_OK;
	if (m_subPaths[0]->m_points[3].y1 != bottom) return S_OK;
	if (m_subPaths[0]->m_points[3].y2 != bottom) return S_OK;

	*pVal = VARIANT_TRUE;

	return S_OK;
}

STDMETHODIMP CPDPath::insertAnchorPointAt(long segment, double t)
{
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (segment-npoints < 0) break;

		segment -= npoints;
	}

	m_subPaths[nsubpath]->insertAnchorPointAt(segment, t);
	return S_OK;
}

STDMETHODIMP CPDPath::getSubPathFromIndex(long index, long *pindex, IPDSubPath* *psubpath)
{
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	if (pindex) *pindex = index;
	if (psubpath) (*psubpath = m_subPaths[nsubpath])->AddRef();

	return S_OK;
}

STDMETHODIMP CPDPath::deleteAnchorPoint(long index)
{
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	m_subPaths[nsubpath]->deleteAnchorPoint(index);

	return S_OK;
}

STDMETHODIMP CPDPath::splitOnSegment(long index, long* pRotateVal)
{
	long npoints;
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	if (m_subPaths[nsubpath]->m_closed)
	{
		for (int npt = index+1; npt < npoints; npt++)
		{
			CBezierPoint bpt = m_subPaths[nsubpath]->m_points[npoints-1];
			m_subPaths[nsubpath]->m_points.InsertAt(0, bpt);
			m_subPaths[nsubpath]->m_points.RemoveAt(npoints);
		}

		m_subPaths[nsubpath]->m_closed = VARIANT_FALSE;

		if (pRotateVal)
			*pRotateVal = npoints-(index+1);
	}
	else
	{
		CComObject<CPDSubPath>* pSubPath;
		CComObject<CPDSubPath>::CreateInstance(&pSubPath);
		if (pSubPath)
		{
			for (int npt = index+1; npt < npoints; npt++)
			{
				CBezierPoint bpt = m_subPaths[nsubpath]->m_points[npt];
				pSubPath->m_points.Add(bpt);
			}

			m_subPaths[nsubpath]->m_points.SetSize(index+1);

			insertSubPath(nsubpath+1, pSubPath);

			if (pRotateVal)
				*pRotateVal = 0;
		}
		else
			return E_FAIL;
	}

	if (m_subPaths[nsubpath]->m_points.GetSize() > 0)
	{
		FireOnChanged(NOTIFY_MODIFY, m_subPaths[nsubpath]->GetUnknown(), DISPID_UNKNOWN);
	}
	else
	{
		CComPtr<IPDSubPath> p;
		removeSubPathByIndex(nsubpath, &p);
	}

	return S_OK;
}

STDMETHODIMP CPDPath::splitOnAnchor(long index, long* pRotateVal)
{
	long npoints;
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	if (m_subPaths[nsubpath]->m_closed)
	{
		m_subPaths[nsubpath]->m_points.RemoveAt(index);
		npoints--;

		for (int npt = index; npt < npoints; npt++)
		{
			CBezierPoint bpt = m_subPaths[nsubpath]->m_points[npoints-1];
			m_subPaths[nsubpath]->m_points.InsertAt(0, bpt);
			m_subPaths[nsubpath]->m_points.RemoveAt(npoints);
		}

		m_subPaths[nsubpath]->m_closed = VARIANT_FALSE;

		if (pRotateVal)
			*pRotateVal = npoints-index;
	}
	else
	{
		if (index+1 < npoints)
		{
			CComObject<CPDSubPath>* pSubPath;
			CComObject<CPDSubPath>::CreateInstance(&pSubPath);
			if (pSubPath)
			{
				for (int npt = index+1; npt < npoints; npt++)
				{
					CBezierPoint bpt = m_subPaths[nsubpath]->m_points[npt];
					pSubPath->m_points.Add(bpt);
				}

				insertSubPath(nsubpath+1, pSubPath);
			}
			else
				return E_FAIL;
		}

		m_subPaths[nsubpath]->m_points.SetSize(index);

		if (pRotateVal)
			*pRotateVal = 0;
	}

	if (m_subPaths[nsubpath]->m_points.GetSize() > 0)
	{
		FireOnChanged(NOTIFY_MODIFY, m_subPaths[nsubpath]->GetUnknown(), DISPID_UNKNOWN);
	}
	else
	{
		CComPtr<IPDSubPath> p;
		removeSubPathByIndex(nsubpath, &p);
	}

	return S_OK;
}

STDMETHODIMP CPDPath::removeSubPaths()
{
	for (int i = m_subPaths.GetSize()-1; i >= 0; i--)
	{
		m_subPaths[i]->Unadvise(this);
		m_subPaths[i]->Release();
		m_subPaths.RemoveAt(i);
	}

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDPath::transformPoints(IPDMatrix *matrix)
{
	if (matrix == NULL) return E_INVALIDARG;

	if (m_subPaths.GetSize() > 0)
	{
		for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
		{
			CPDSubPath* pSubPath = m_subPaths[nsubpath];
			int npoints = pSubPath->m_points.GetSize();

			for (int i = 0; i < npoints; i++)
			{
				matrix->transformBezierPoint(&pSubPath->m_points[i], &pSubPath->m_points[i]);
			}
		}

		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	}

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDPath::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	_bstr_t d = saveString();

	node->putData(_variant_t(d));

	return S_OK;
}

STDMETHODIMP CPDPath::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;
	node->getData(&v);

	parseString(_bstr_t(v));

	return S_OK;
}

STDMETHODIMP CPDPath::GetClassID(CLSID *pClassID)
{
	return S_OK;
}
