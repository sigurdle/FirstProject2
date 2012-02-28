#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGPathElement.h"
#include "EXMLDocument.h"

#if 0
void DrawPathSegList(LSVG::CLSVGPathSegList* seglist, LDraw::GraphicsPath* path, LSVG::SVGMatrix* matrix)
{
	gmMatrix3 mat;
	if (matrix)
	{
		double v;
		matrix->get_a(&v); mat[0][0] = v; matrix->get_b(&v); mat[0][1] = v;
		matrix->get_c(&v); mat[1][0] = v; matrix->get_d(&v); mat[1][1] = v;
		matrix->get_e(&v); mat[2][0] = v; matrix->get_f(&v); mat[2][1] = v;
		mat[0][2] = 0;
		mat[1][2] = 0;
		mat[2][2] = 1;
	}
	else
		mat = gmMatrix3::identity();

	double last_movex = 0;
	double last_movey = 0;

	double last_posx = 0;
	double last_posy = 0;

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);
	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

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
			x = xpt[0];
			y = xpt[1];

			last_posx = last_movex = x;
			last_posy = last_movey = y;
			path->StartFigure();
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

			double x, y;
			linetoabs->get_x(&x);
			linetoabs->get_y(&y);

			gmVector2 pt(x, y);
			gmVector2 xpt = mat.transform(pt);
			x = xpt[0];
			y = xpt[1];

			path->AddLine((float)last_posx, (float)last_posy, (float)x, (float)y);
			last_posx = x;
			last_posy = y;
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

			POINT pt[3] =
			{
				x1, y1,
				x2, y2,
				x, y,
			};

			path->AddBezier((float)last_posx, (float)last_posy, (float)x1, (float)y1, (float)x2, (float)y2, (float)x, (float)y);

			last_posx = x;
			last_posy = y;
		}
		else if (segType == PATHSEG_CLOSEPATH)
		{
			path->CloseFigure();
		//	path->AddLine((float)last_posx, (float)last_posy, (float)last_movex, (float)last_movey);
		}
	}
}

////////////////////////////////////////////////////////////////////
// CESVGPath

STDMETHODIMP CESVGPath::AppendPath(IESVGPath* path)
{
	m_segList->LockUpdate();

	{
		long nsubpaths;
		path->GetSubPathCount(&nsubpaths);

		long numberOfItems;
		m_segList->get_numberOfItems(&numberOfItems);

		for (int i = 0; i < nsubpaths; i++)
		{
			CComPtr<IESVGSubPath> subpath;
			path->GetSubPath(i, &subpath);
			CComObject<CSubPath>* pSubPath = static_cast<CComObject<CSubPath>*>(subpath.p);

			pSubPath->AddRef();
			pSubPath->m_pPath = this;
			m_subPaths.Add(pSubPath);
			pSubPath->m_segIndex += numberOfItems;
		}
	}

	{
		CComPtr<ILSVGPathSegList> seglist;
		path->GetPathSegList(&seglist);

		long numberOfItems;
		seglist->get_numberOfItems(&numberOfItems);
		for (int i = 0; i < numberOfItems; i++)
		{
			CComPtr<ILSVGPathSeg> seg;
			seglist->getItem(0, &seg); // 0 since it gets removed from seglist

			m_segList->appendItem(seg, NULL);
		}
	}

	m_segList->UnlockUpdate();

	return S_OK;
}

long CESVGPath::GetSubPathIndex(CComObject<CSubPath>* pSubPath)
{
	for (int i = 0; i < m_subPaths.GetSize(); i++)
	{
		if (m_subPaths[i] == pSubPath)
			return i;
	}

	ASSERT(0);
	return -1;
}

void CESVGPath::RemoveSubPath(CComObject<CSubPath>* pSubPath)
{
	long index = GetSubPathIndex(pSubPath);

	m_subPaths.RemoveAt(index);
	for (int i = index; i < m_subPaths.GetSize(); i++)
	{
		m_subPaths[i]->m_segIndex -= pSubPath->m_nsegs;
	}

	pSubPath->m_pPath = NULL;
	pSubPath->Release();
}

STDMETHODIMP CESVGPath::InsertSubPathBefore(/*[in]*/ IESVGSubPath* path, /*[in]*/ long index)
{
	m_segList->LockUpdate();

	CComObject<CSubPath>* pSubPath = static_cast<CComObject<CSubPath>*>(path);

	CESVGPath* pPrevPath = pSubPath->m_pPath;
	if (pPrevPath)
	{
		pSubPath->AddRef();

		pPrevPath->RemoveSubPath(pSubPath);

		pPrevPath->m_segList->LockUpdate();

		for (int i = 0; i < pSubPath->m_nsegs; i++)
		{
			CComPtr<ILSVGPathSeg> seg;
			pPrevPath->m_segList->removeItem(pSubPath->m_segIndex, &seg);

			m_segList->insertItemBefore(seg, i/*TODO*/, NULL);
		}

		pPrevPath->m_segList->UnlockUpdate();

		pSubPath->m_segIndex = 0;	// TODO
		pSubPath->m_pPath = this;
		m_subPaths.InsertAt(index, pSubPath);
	}
	else
		ASSERT(0);

	m_segList->UnlockUpdate();

	return S_OK;
}

HRESULT CESVGPath::InsertPointAfter(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
{
// Find subpath to insert into
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_nsegs;//points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	m_subPaths[nsubpath]->m_nsegs++;
	for (int i = nsubpath+1; i < m_subPaths.GetSize(); i++)
	{
		m_subPaths[i]->m_segIndex++;
	}

	CComPtr<ILSVGPathSegCurvetoCubicAbs> curveto;

	m_pathElement->createSVGPathSegCurvetoCubicAbs(x, y, m_subPaths[nsubpath]->m_lastx, m_subPaths[nsubpath]->m_lasty, x1, y1, &curveto);

	m_subPaths[nsubpath]->m_lastx = x2;
	m_subPaths[nsubpath]->m_lasty = y2;

	m_segList->appendItem(curveto, NULL);

	return S_OK;
}

HRESULT CESVGPath::InsertPointBefore(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
{
	ASSERT(0);
	return S_OK;
}

HRESULT CESVGPath::GetPathSeg(int index, CBezierPoint* _seg)
{
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_nsegs;
		if (index-npoints < 0) break;

		index -= npoints;
	}

	m_subPaths[nsubpath]->GetPathSeg(index, _seg);

	return S_OK;
}

HRESULT CESVGPath::PutPathSeg(int index, CBezierPoint* _seg)
{
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		long npoints = m_subPaths[nsubpath]->m_nsegs;
		if (index-npoints < 0) break;

		index -= npoints;
	}

	m_subPaths[nsubpath]->PutPathSeg(index, _seg);

	return S_OK;
}

HRESULT CESVGPath::SetPathSegList(ILSVGPathSegList* seglist)
{
	ASSERT(m_subPaths.GetSize() == 0);
	
	m_segList = seglist;

	double x, y;

// Build subpaths from seglist
	CComObject<CSubPath>* pSubPath = NULL;

	long nsegitems;
	seglist->get_numberOfItems(&nsegitems);
	for (int i = 0; i < nsegitems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);

		if (segType == PATHSEG_CLOSEPATH)
		{
		// Closing current subpath
			if (pSubPath)
			{
				//pSubPath->m_lastx
				pSubPath->m_nsegs = i - pSubPath->m_segIndex;//+1;
				pSubPath->m_bClosed = true;
				pSubPath = NULL;
			}
		}
		else if (segType == PATHSEG_MOVETO_ABS)
		{
			// First end current subpath
			if (pSubPath)
			{
				pSubPath->m_nsegs = i - pSubPath->m_segIndex;
				pSubPath = NULL;
			}

			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

		// Beginning new subpath
			CComObject<CSubPath>::CreateInstance(&pSubPath);
			if (pSubPath)
			{
				pSubPath->AddRef();
				pSubPath->m_pPath = this;

				pSubPath->m_segIndex = i;

				m_subPaths.Add(pSubPath);
			}
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubic = seg;

		// First cubic bezier on subpath, set firstxy to opposite
			if (i == pSubPath->m_segIndex+1)
			{
				double x1, y1;
				cubic->get_x1(&x1);
				cubic->get_y1(&y1);

				pSubPath->m_firstx = x + (x-x1);
				pSubPath->m_firsty = y + (y-y1);
			}
		}
	}

	if (pSubPath)
	{
		pSubPath->m_nsegs = i - pSubPath->m_segIndex;
	}

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

STDMETHODIMP CESVGPath::getPointNearPath(/*[in]*/ LSVG::SVGMatrix* matrix, /*[in]*/ double mousex, /*[in]*/ double mousey, /*[in]*/ double tolerance, /*[out]*/ long* segindex, /*[out]*/ double* pt, /*[out,retval]*/ VARIANT_BOOL* pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	double oldx = 0;
	double oldy = 0;

	long numberOfItems;
	m_segList->get_numberOfItems(&numberOfItems);

	for (unsigned long i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		m_segList->getItem(i, &seg);

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
				*pVal = VARIANT_TRUE;
				return S_OK;
			}

			oldx = x;
			oldy = y;
		}
	}

	*pVal = VARIANT_FALSE;

	return S_OK;
}

#if 0
void CPathElement::ReleaseCompound()
{
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

		ASSERT(destPath != NULL);

		seg->AddRef();
		destSegList->appendItem(seg);
	}

	if (destSegList != NULL)
	{
		destSegList->UnlockUpdate();
	}

	pParent->m_domElement->removeChild(m_domElement);
}
#endif

#endif