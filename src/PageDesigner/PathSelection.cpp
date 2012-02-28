#include "stdafx.h"
#include "PageDesigner.h"
//#include "PDObjectSelected.h"
#include "PathSelection.h"

///////////////////////////////

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

double GetLineAngle(float x1, float y1, float x2, float y2)
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

////////////////////////////////////
// CPathSelection

bool CPathSelection::IsSubPathSelected(int nsubpath)
{
	long nsubpaths;
	m_path->get_subPathCount(&nsubpaths);

	long npoints = 0;
	long subpathNPoints;

	long j = 0;
	do
	{
		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(j, &subpath);
		subpath->get_pointCount(&subpathNPoints);

		if (j < nsubpath)
			npoints += subpathNPoints;
		else
			break;
	}
	while (1);

	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] >= npoints && m_selectedPoints[i] < npoints+subpathNPoints)
		{
			return true;
		}
	}

	return false;
}

void CPathSelection::AddAnchorPoints()
{
	long nsubpaths;
	m_path->get_subPathCount(&nsubpaths);

	long ntotalpoints = 0;

	for (int nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(nsubpath, &subpath);

		long npoints;
		subpath->get_pointCount(&npoints);

		if (IsSubPathSelected(nsubpath))
		{
			VARIANT_BOOL closed;
			subpath->get_closed(&closed);

			long count = npoints;
			if (!closed) count--;

			for (int i = count-1; i >= 0; i--)
			{
				subpath->insertAnchorPointAt(i, 0.5);

				int j;

				for (j = 0; j < m_selectedPoints.GetSize(); j++)
				{
					if (m_selectedPoints[j] > ntotalpoints+i)
						m_selectedPoints[j]++;
				}

				for (j = 0; j < m_selectedSegments.GetSize(); j++)
				{
					if (m_selectedSegments[j] > ntotalpoints+i)
						m_selectedSegments[j]++;
				}
			}
		}

		ntotalpoints += npoints;
	}
}

void CPathSelection::ReverseSelectedPath()
{
	long nsubpaths;
	m_path->get_subPathCount(&nsubpaths);

	for (int nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(nsubpath, &subpath);

		if (IsSubPathSelected(nsubpath))
		{
			subpath->reverse();
		}
	}
}

void CPathSelection::InsertPointBefore(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
{
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] >= index)
		{
			m_selectedPoints[i]++;
		}
	}

	m_path->insertPointBefore(index, x, y, x1, y1, x2, y2);
}

void CPathSelection::InsertPointAfter(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
{
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] > index)
		{
			m_selectedPoints[i]++;
		}
	}

	m_path->insertPointAfter(index, x, y, x1, y1, x2, y2);
}

void CPathSelection::DeleteAnchorPoint(int index)
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

void CPathSelection::RotateSelectedPointIndexes(long rotate)
{
	if (rotate != 0)
	{
		long npoints;
		m_path->get_pointCount(&npoints);

		int i;

		for (i = 0; i < m_selectedSegments.GetSize(); i++)
		{
			m_selectedSegments[i] += rotate;
			m_selectedSegments[i] %= npoints;
		}

		for (i = 0; i < m_selectedPoints.GetSize(); i++)
		{
			m_selectedPoints[i] += rotate;
			m_selectedPoints[i] %= npoints;
		}
	}
}

void CPathSelection::DeleteSelection()
{
	int i;

	for (i = m_selectedSegments.GetSize()-1; i >= 0; i--)
	{
		long rotate;
		m_path->splitOnSegment(m_selectedSegments[i], &rotate);
		RotateSelectedPointIndexes(rotate);

		m_selectedSegments.RemoveAt(i);
	}

	int size = m_selectedPoints.GetSize();

	for (i = size-1; i >= 0; i--)
	{
		long rotate;
		m_path->splitOnAnchor(m_selectedPoints[i], &rotate);
		RotateSelectedPointIndexes(rotate);

		m_selectedPoints.RemoveAt(i);
	}
}

void CPathSelection::SelectSegment(int index)
{
	ATLASSERT(!IsSegmentSelected(index));

	for (int i = 0; i < m_selectedSegments.GetSize(); i++)
	{
		if (index < m_selectedSegments[i]) break;
	}
	m_selectedSegments.InsertAt(i, index);
}

void CPathSelection::DeselectSegment(int index)
{
	for (int i = 0; i < m_selectedSegments.GetSize(); i++)
	{
		if (m_selectedSegments[i] == index)
		{
			m_selectedSegments.RemoveAt(i);
			return;
		}
	}
}

BOOL CPathSelection::IsSegmentSelected(int index)
{
	int min = 0;        // beginning of search range 
	int max = m_selectedSegments.GetSize();   // end of search range 
	
	int n = max / 2; 
	while (min < max) 
	{ 
		if (index < m_selectedSegments[n]) 
			max = n; 
		else if (index > m_selectedSegments[n])
			min = n + 1; 
		else
			return TRUE;

		n = (min + max) / 2; 
	} 

	return FALSE;

/*
	for (int i = 0; i < m_selectedSegments.GetSize(); i++)
	{
		if (m_selectedSegments[i] == index) return TRUE;
		else if (m_selectedSegments[i] > index) return FALSE;
	}

	ATLASSERT(0);
*/
}

void CPathSelection::SelectAnchor(int index)
{
	ATLASSERT(!IsAnchorSelected(index));

	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (index < m_selectedPoints[i]) break;
	}
	m_selectedPoints.InsertAt(i, index);
}

void CPathSelection::DeselectAnchor(int index)
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

BOOL CPathSelection::IsAnchorSelected(int index)
{
	int min = 0;        // beginning of search range 
	int max = m_selectedPoints.GetSize();   // end of search range 
	
	int n = max / 2; 
	while (min < max) 
	{ 
		if (index < m_selectedPoints[n]) 
			max = n; 
		else if (index > m_selectedPoints[n])
			min = n + 1; 
		else
			return TRUE;

		n = (min + max) / 2; 
	} 

	return FALSE;
}

void CPathSelection::SelectAllAnchors()
{
	m_selectedPoints.RemoveAll();

	long numberOfItems;
	m_path->get_pointCount(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		m_selectedPoints.Add(i);
	}
}

void CPathSelection::TransformSelectedPoint(IPDMatrix* pdmatrix)
{
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		BezierPoint bpt;
		m_path->getPoint(m_selectedPoints[i], &bpt);

		BezierPoint xbpt;
		pdmatrix->transformBezierPoint(&bpt, &xbpt);

		m_path->setPoint(m_selectedPoints[i], &xbpt);
	}
}

void CPathSelection::DrawPath(IPDMatrix* pdmatrix, IPDMatrix* pdmatrix2, Gdiplus::GraphicsPath* path)
{
	long nsubpaths;
	m_path->get_subPathCount(&nsubpaths);

	for (int i = 0; i < nsubpaths; i++)
	{
		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(i, &subpath);

		long npoints;
		subpath->get_pointCount(&npoints);

		if (npoints > 1)
		{
			path->StartFigure();

			BezierPoint point;
			subpath->getPoint(0, &point);

			BezierPoint xpoint[2];
			xpoint[0] = point;

			if (pdmatrix2 && IsAnchorSelected(0))
				pdmatrix2->transformBezierPoint(&xpoint[0], &xpoint[0]);
			else if (pdmatrix)
				pdmatrix->transformBezierPoint(&xpoint[0], &xpoint[0]);

			for (int npt = 1; npt < npoints; npt++)
			{
				subpath->getPoint(npt, &point);
				xpoint[1] = point;

				if (pdmatrix2 && IsAnchorSelected(npt))
					pdmatrix2->transformBezierPoint(&xpoint[1], &xpoint[1]);
				else if (pdmatrix)
					pdmatrix->transformBezierPoint(&xpoint[1], &xpoint[1]);

				path->AddBezier(
					(float)xpoint[0].x, (float)xpoint[0].y,
					(float)xpoint[0].x2, (float)xpoint[0].y2,
					(float)xpoint[1].x1, (float)xpoint[1].y1,
					(float)xpoint[1].x, (float)xpoint[1].y
					);

				xpoint[0] = xpoint[1];
			}

			VARIANT_BOOL closed;
			subpath->get_closed(&closed);

			if (closed)
			{
				subpath->getPoint(0, &point);
				xpoint[1] = point;

				if (pdmatrix2 && IsAnchorSelected(0))
					pdmatrix2->transformBezierPoint(&xpoint[1], &xpoint[1]);
				else if (pdmatrix)
					pdmatrix->transformBezierPoint(&xpoint[1], &xpoint[1]);

				path->AddBezier(
					(float)xpoint[0].x, (float)xpoint[0].y,
					(float)xpoint[0].x2, (float)xpoint[0].y2,
					(float)xpoint[1].x1, (float)xpoint[1].y1,
					(float)xpoint[1].x, (float)xpoint[1].y
					);

				path->CloseFigure();
			}
		}
	}
}

void CPathSelection::IsControlPointVisible(IPDSubPath* subpath, int nAnchorsSelected, int ntotalpoints, int npt, BOOL* c1, BOOL* c2)
{
	long npoints;
	subpath->get_pointCount(&npoints);

	int index = ntotalpoints + npt;
	int nextIndex = (npt < npoints-1)? index+1: ntotalpoints;
	int prevIndex = (npt > 0)? index-1: ntotalpoints+npoints-1;

	BOOL indexSelected = IsAnchorSelected(index);

	if (IsSegmentSelected(prevIndex) || (indexSelected && nAnchorsSelected < 2))
	{
		*c1 = true;
	}
	else
		*c1 = false;

	if (IsSegmentSelected(index) || (indexSelected && nAnchorsSelected < 2))
	{
		*c2 = true;
	}
	else
		*c2 = false;
}

void CPathSelection::DrawSelection(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, IPDMatrix* matrix)
{
	Gdiplus::Pen pen(color);
	Gdiplus::SolidBrush brush(color);

	long nsubpaths;
	m_path->get_subPathCount(&nsubpaths);

	long ntotalpoints = 0;

	for (long nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(nsubpath, &subpath);

		long npoints;
		subpath->get_pointCount(&npoints);

		int nAnchorsSelected = 0;
		for (long npt = ntotalpoints; npt < ntotalpoints+npoints; npt++)
		{
			if (IsAnchorSelected(npt))
			{
				nAnchorsSelected++;
				if (nAnchorsSelected >= 2) break;
			}
		}

		for (npt = 0; npt < npoints; npt++)
		{
			BezierPoint point;
			subpath->getPoint(npt, &point);

			int index = ntotalpoints + npt;

			BezierPoint xpoint;
			matrix->transformBezierPoint(&point, &xpoint);

			BOOL indexSelected = IsAnchorSelected(index);

			if (indexSelected)
				pGraphics->FillRectangle(&brush, (int)(xpoint.x-2), (int)(xpoint.y-2), (4), (4));
			else
				pGraphics->DrawRectangle(&pen, (int)(xpoint.x-2), (int)(xpoint.y-2), (4), (4));

			BOOL c1;
			BOOL c2;
			IsControlPointVisible(subpath, nAnchorsSelected, ntotalpoints, npt, &c1, &c2);

			if (c1)
			{
				pGraphics->DrawLine(&pen, (float)xpoint.x, (float)xpoint.y, (float)xpoint.x1, (float)xpoint.y1);
				pGraphics->FillEllipse(&brush, (int)(xpoint.x1-2), (int)(xpoint.y1-2), (4), (4));
			}

			if (c2)
			{
				pGraphics->DrawLine(&pen, (float)xpoint.x, (float)xpoint.y, (float)xpoint.x2, (float)xpoint.y2);
				pGraphics->FillEllipse(&brush, (int)(xpoint.x2-2), (int)(xpoint.y2-2), (4), (4));
			}

/*
			if (nptSelected || (npt > 0 && IsSegmentSelected(npt-1)))
			{
				pGraphics->DrawLine(&pen, (float)xpoint.x, (float)xpoint.y, (float)xpoint.x1, (float)xpoint.y1);
				pGraphics->FillEllipse(&brush, (float)(xpoint.x1-2), (float)(xpoint.y1-2), (float)(4), (float)(4));
			}

			if (nptSelected || (npt < npoints-1 && IsSegmentSelected(npt+1)))
			{
				pGraphics->DrawLine(&pen, (float)xpoint.x, (float)xpoint.y, (float)xpoint.x2, (float)xpoint.y2);
				pGraphics->FillEllipse(&brush, (float)(xpoint.x2-2), (float)(xpoint.y2-2), (float)(4), (float)(4));
			}
			*/
		}

		ntotalpoints += npoints;
	}
}

int CPathSelection::FindPoint(IPDMatrix* matrix, double mousex, double mousey, long& ctl)
{
	long nsubpaths;
	m_path->get_subPathCount(&nsubpaths);

	long ntotalpoints = 0;

	for (long nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(nsubpath, &subpath);

		long npoints;
		subpath->get_pointCount(&npoints);

		int nAnchorsSelected = 0;
		for (long npt = ntotalpoints; npt < ntotalpoints+npoints; npt++)
		{
			if (IsAnchorSelected(npt))
			{
				nAnchorsSelected++;
				if (nAnchorsSelected >= 2) break;
			}
		}

		for (npt = 0; npt < npoints; npt++)
		{
			BezierPoint point;
			subpath->getPoint(npt, &point);

			int index = ntotalpoints + npt;

			BezierPoint xpoint;
			matrix->transformBezierPoint(&point, &xpoint);

			if (fabs(xpoint.x-mousex) < 4 && fabs(xpoint.y-mousey) < 4)
			{
				ctl = 0;
				return index;
			}

			BOOL c1;
			BOOL c2;
			IsControlPointVisible(subpath, nAnchorsSelected, ntotalpoints, npt, &c1, &c2);

			if (c1)
			{
				if (fabs(xpoint.x1-mousex) < 4 && fabs(xpoint.y1-mousey) < 4)
				{
					ctl = -1;
					return index;
				}
			}

			if (c2)
			{
				if (fabs(xpoint.x2-mousex) < 4 && fabs(xpoint.y2-mousey) < 4)
				{
					ctl = 1;
					return index;
				}
			}

		}

		ntotalpoints += npoints;
	}

	return -1;
}

#if 0
	long numberOfItems;
	m_path->get_pointCount(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		BezierPoint seg;
		m_path->getPoint(i, &seg);

		BezierPoint xseg;
		matrix->transformBezierPoint(&seg, &xseg);

		if (MATCHPOINT(mousex, mousey, xseg.x, xseg.y))
		{
			ctl = 0;
			return i;
		}

		BOOL biselected = IsSegmentSelected(i);

		if (biselected || (i > 0 && IsSegmentSelected(i-1)))
		{
			if (MATCHPOINT(mousex, mousey, xseg.x1, xseg.y1))
			{
				ctl = -1;
				return i;
			}
		}

		if (biselected || (i < numberOfItems-1 && IsSegmentSelected(i+1)))
		{
			if (MATCHPOINT(mousex, mousey, xseg.x2, xseg.y2))
			{
				ctl = 1;
				return i;
			}
		}
	}

	return -1;
}
#endif

void CPathSelection::BezierBounds(long numberOfItems, long index, VARIANT_BOOL closed, BezierPoint seg, BezierPoint seg1, BezierPoint seg2, double& minx, double& miny, double& maxx, double& maxy)
{
	minx = min(minx, min(seg.x, min(seg.x1, seg.x2)));
	miny = min(miny, min(seg.y, min(seg.y1, seg.y2)));

	maxx = max(maxx, max(seg.x, max(seg.x1, seg.x2)));
	maxy = max(maxy, max(seg.y, max(seg.y1, seg.y2)));

	if (index > 0 || closed)
	{
		minx = min(minx, min(seg1.x, seg1.x2));
		miny = min(miny, min(seg1.y, seg1.y2));

		maxx = max(maxx, max(seg1.x, seg1.x2));
		maxy = max(maxy, max(seg1.y, seg1.y2));
	}

	if (index < numberOfItems-1 || closed)
	{
		minx = min(minx, min(seg2.x, seg2.x1));
		miny = min(miny, min(seg2.y, seg2.y1));

		maxx = max(maxx, max(seg2.x, seg2.x1));
		maxy = max(maxy, max(seg2.y, seg2.y1));
	}
}

void CPathSelection::MovePoints(double dx, double dy, Gdiplus::RectF& invalidBounds, bool bAll /* = true */)
{
	double minx = 999999;
	double miny = 999999;
	double maxx = -999999;
	double maxy = -999999;

	long nsubpaths;
	m_path->get_subPathCount(&nsubpaths);

	{
		CComQIPtr<INotifySend> cp = m_path;
		cp->LockSend();
	}
	
	long ntotalpoints = 0;

	for (long nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(nsubpath, &subpath);

		VARIANT_BOOL closed;
		subpath->get_closed(&closed);

		long numberOfItems;
		subpath->get_pointCount(&numberOfItems);

		{
			CComQIPtr<INotifySend> cp = subpath;
			cp->LockSend();
		}

		for (long index = 0; index < numberOfItems; index++)
		{
			if (bAll || IsAnchorSelected(ntotalpoints+index))
			{
				BezierPoint seg;
				subpath->getPoint(index, &seg);

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

				seg.x += dx;
				seg.y += dy;
				seg.x1 += dx;
				seg.y1 += dy;
				seg.x2 += dx;
				seg.y2 += dy;

				BezierBounds(numberOfItems, index, closed, seg, seg1, seg2, minx, miny, maxx, maxy);

				subpath->setPoint(index, &seg);
			}
		}

		{
			CComQIPtr<INotifySend> cp = subpath;
			cp->UnlockSend();
		}

		ntotalpoints += numberOfItems;
	}

	{
		CComQIPtr<INotifySend> cp = m_path;
		cp->UnlockSend();
	}

	invalidBounds.X = minx;
	invalidBounds.Y = miny;
	invalidBounds.Width = maxx-minx;
	invalidBounds.Height = maxy-miny;
}

// Sets the control points, the control points are opposite and same length
void CPathSelection::SetControlPointsSameLength(int segindex, int ctlindex, double ctlx, double ctly, Gdiplus::RectF& invalidBounds)
{
	double minx = 999999;
	double miny = 999999;
	double maxx = -999999;
	double maxy = -999999;

	CComPtr<IPDSubPath> subpath;
	long subpathIndex;
	m_path->getSubPathFromIndex(segindex, &subpathIndex, &subpath);
	long nsubpathPoints;
	subpath->get_pointCount(&nsubpathPoints);

	VARIANT_BOOL closed;
	subpath->get_closed(&closed);

	DblPOINT seg[3];
	m_path->getPoint(segindex, (BezierPoint*)seg);

	BezierPoint seg1;
	if (subpathIndex > 0)
		subpath->getPoint(subpathIndex-1, &seg1);
	else if (closed)
		subpath->getPoint(nsubpathPoints-1, &seg1);

	BezierPoint seg2;
	if (subpathIndex < nsubpathPoints-1)
		subpath->getPoint(subpathIndex+1, &seg2);
	else if (closed)
		subpath->getPoint(0, &seg2);

	BezierBounds(nsubpathPoints, subpathIndex, closed, (BezierPoint&)seg, seg1, seg2, minx, miny, maxx, maxy);

	seg[1+ctlindex].x = ctlx;
	seg[1+ctlindex].y = ctly;

	double distance = GetLineDistance(ctlx, ctly, seg[1].x, seg[1].y);
	double angle = GetLineAngle(distance, ctlx, ctly, seg[1].x, seg[1].y);

//	angle += M_PI;

	seg[1-ctlindex].x = cos(angle)*distance + seg[1].x;
	seg[1-ctlindex].y = sin(angle)*distance + seg[1].y;

	m_path->setPoint(segindex, (BezierPoint*)seg);

	BezierBounds(nsubpathPoints, subpathIndex, closed, (BezierPoint&)seg, seg1, seg2, minx, miny, maxx, maxy);

	invalidBounds.X = minx;
	invalidBounds.Y = miny;
	invalidBounds.Width = maxx-minx;
	invalidBounds.Height = maxy-miny;
}

void CPathSelection::SetPathSegControlPoints(int segindex, int ctlindex, double ctlx, double ctly, Gdiplus::RectF& invalidBounds)
{
	double minx = 999999;
	double miny = 999999;
	double maxx = -999999;
	double maxy = -999999;

	CComPtr<IPDSubPath> subpath;
	long subpathIndex;
	m_path->getSubPathFromIndex(segindex, &subpathIndex, &subpath);
	long nsubpathPoints;
	subpath->get_pointCount(&nsubpathPoints);

	VARIANT_BOOL closed;
	subpath->get_closed(&closed);

	DblPOINT seg[3];
	m_path->getPoint(segindex, (BezierPoint*)seg);

	BezierPoint seg1;
	if (subpathIndex > 0)
		subpath->getPoint(subpathIndex-1, &seg1);
	else if (closed)
		subpath->getPoint(nsubpathPoints-1, &seg1);

	BezierPoint seg2;
	if (subpathIndex < nsubpathPoints-1)
		subpath->getPoint(subpathIndex+1, &seg2);
	else if (closed)
		subpath->getPoint(0, &seg2);

	BezierBounds(nsubpathPoints, subpathIndex, closed, (BezierPoint&)seg, seg1, seg2, minx, miny, maxx, maxy);

	seg[1+ctlindex].x = ctlx;
	seg[1+ctlindex].y = ctly;

	double angle = GetLineAngle(ctlx, ctly, seg[1].x, seg[1].y);
	double distance = GetLineDistance(seg[1].x, seg[1].y, seg[1-ctlindex].x, seg[1-ctlindex].y);

//	angle += M_PI;

	seg[1-ctlindex].x = cos(angle)*distance + seg[1].x;
	seg[1-ctlindex].y = sin(angle)*distance + seg[1].y;

	m_path->setPoint(segindex, (BezierPoint*)seg);

	BezierBounds(nsubpathPoints, subpathIndex, closed, (BezierPoint&)seg, seg1, seg2, minx, miny, maxx, maxy);

	invalidBounds.X = minx;
	invalidBounds.Y = miny;
	invalidBounds.Width = maxx-minx;
	invalidBounds.Height = maxy-miny;
}

void CPathSelection::DrawPolyPoints(IPDMatrix* pdmatrix, Gdiplus::GraphicsPath* path)
{
#if 0
	ATLASSERT(pdmatrix != NULL);

	int ipt = 0;
	CDblPoint* points = m_flatPoints.GetData();

	for (int sub = 0; sub < m_subPoints.GetSize(); sub++)
	{
		int count = m_subPoints[sub];

		ipt++;

		path->StartFigure();

		PointD xpt0;
		pdmatrix->transformPoint((PointD*)&points[0], &xpt0);

		for (int i = 1; i < count; i++)
		{
			PointD xpt;
			pdmatrix->transformPoint((PointD*)&points[ipt], &xpt);

			path->AddLine((float)xpt0.x, (float)xpt0.y, (float)xpt.x, (float)xpt.y);

			xpt0 = xpt;
			ipt++;
		}

		path->CloseFigure();
	}
#endif
}

void CPathSelection::DrawPolyPoints(IPDMatrix* pdmatrix, Gdiplus::Graphics* pGraphics, Gdiplus::Pen* pPen)
{
	ATLASSERT(pdmatrix != NULL);

	for (int nsubpath = 0; nsubpath < m_flatSubPaths.GetSize(); nsubpath++)
	{
		CFlatSubPath* flatsubpath = m_flatSubPaths[nsubpath];
		int pointsIndex = 0;

		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(nsubpath, &subpath);

		VARIANT_BOOL closed;
		subpath->get_closed(&closed);

		long nsubpathpoints;
		subpath->get_pointCount(&nsubpathpoints);

		for (int nseg = 0; nseg < flatsubpath->m_flatSegments.GetSize(); nseg++)
		{
			CFlatSegment segment = flatsubpath->m_flatSegments[nseg];

			if (segment.m_pointCount > 0 && segment.m_bAltered)
			{
				int numpoints = segment.m_pointCount;
				DblPOINT* points = flatsubpath->m_flatPoints.GetData() + pointsIndex;

				PointD xpt0;
				pdmatrix->transformPoint((PointD*)&points[0], &xpt0);

				for (int i = 1; i < numpoints; i++)
				{
					PointD xpt;
					pdmatrix->transformPoint((PointD*)&points[i], &xpt);

					pGraphics->DrawLine(pPen, (float)xpt0.x, (float)xpt0.y, (float)xpt.x, (float)xpt.y);

					xpt0 = xpt;
				}
			}
			else	// Draw from original subpath data
			{
				BezierPoint bpt0;
				subpath->getPoint(nseg, &bpt0);

				BezierPoint bpt1;
				subpath->getPoint((nseg < nsubpathpoints-1)? nseg+1: 0, &bpt1);

				BezierPoint xpt0;
				pdmatrix->transformBezierPoint(&bpt0, &xpt0);

				BezierPoint xpt1;
				pdmatrix->transformBezierPoint(&bpt1, &xpt1);

				pGraphics->DrawBezier(pPen,
					(float)xpt0.x, (float)xpt0.y,
					(float)xpt0.x2, (float)xpt0.y2,
					(float)xpt1.x1, (float)xpt1.y1,
					(float)xpt1.x, (float)xpt1.y);
			}

			pointsIndex += segment.m_pointCount;
		}
	}
}

int AddFlatCurve(CArray<CDblPoint,CDblPoint>& pointsArr, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double& oldxt, double& oldyt)
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

	double tinc = 1/400.0;

	int count = 0;

	for (t = 0.0; t <= 1.0; t += tinc)
	{
		xt = ax * t*t*t + bx * t*t + cx * t + x0;
		yt = ay * t*t*t + by * t*t + cy * t + y0;

		if ((fabs(xt-oldxt) > 0.001) || (fabs(yt-oldyt) > 0.001))
		{
			pointsArr.Add(CDblPoint(xt, yt));
			count++;

			oldxt = xt;
			oldyt = yt;
		}
	}

	return count;
}

void CPathSelection::SetPolyPointsFromSegList()
{
	long nsubpaths;
	m_path->get_subPathCount(&nsubpaths);

	int ntotalpoints = 0;

	for (long nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(nsubpath, &subpath);

		VARIANT_BOOL closed;
		subpath->get_closed(&closed);

		long npoints;
		subpath->get_pointCount(&npoints);

		CFlatSubPath* flatSubPath = new CFlatSubPath;

		if (npoints > 0)
		{
			double oldxt = -99999;
			double oldyt = -99999;

			BezierPoint seg0;
			subpath->getPoint(0, &seg0);

			BezierPoint _seg0 = seg0;
			for (long i = 1; i < npoints; i++)
			{
				CFlatSegment segment;

				BezierPoint seg;
				subpath->getPoint(i, &seg);

				if (IsAnchorSelected(i-1) || IsAnchorSelected(i))
				{
					segment.m_pointCount = AddFlatCurve(
						flatSubPath->m_flatPoints,
						seg0.x, seg0.y,
						seg0.x2, seg0.y2,
						seg.x1, seg.y1,
						seg.x, seg.y,
						oldxt, oldyt);
				}

				seg0 = seg;

				flatSubPath->m_flatSegments.Add(segment);
			}

			if (closed)
			{
				CFlatSegment segment;

				if (IsAnchorSelected(0) || IsAnchorSelected(npoints-1))
				{
					segment.m_pointCount = AddFlatCurve(
						flatSubPath->m_flatPoints,
						seg0.x, seg0.y,
						seg0.x2, seg0.y2,
						_seg0.x1, _seg0.y1,
						_seg0.x, _seg0.y,
						oldxt, oldyt);
				}

				flatSubPath->m_flatSegments.Add(segment);
			}
		}

		m_flatSubPaths.Add(flatSubPath);
	}
}

void CPathSelection::MoreFlatDetail()
{
	for (int nsubpath = 0; nsubpath < m_flatSubPaths.GetSize(); nsubpath++)
	{
		CFlatSubPath* flatsubpath = m_flatSubPaths[nsubpath];

	//	CComPtr<IPDSubPath> subpath;
	//	m_path->getSubPath(nsubpath, &subpath);

	//	VARIANT_BOOL closed;
	//	subpath->get_closed(&closed);

	//	long nsubpathpoints;
	//	subpath->get_pointCount(&nsubpathpoints);

		CArray<CDblPoint,CDblPoint>& points = flatsubpath->m_flatPoints;
		int ipt = 0;

		for (int nseg = 0; nseg < flatsubpath->m_flatSegments.GetSize(); nseg++)
		{
			CFlatSegment& segment = flatsubpath->m_flatSegments[nseg];

			if (segment.m_pointCount > 0)
			{
				if (segment.m_bRecentAltered)
				{
					bool bAgain;
					do
					{
						bAgain = false;

						int count = segment.m_pointCount;

						for (int i = ipt+count-1; i > ipt; i--)
						{
							double dx = points[i].x-points[i-1].x;
							double dy = points[i].y-points[i-1].y;

							double dist = dx*dx + dy*dy;
							if (dist > 50)
							{
								points.InsertAt(i, CDblPoint(points[i-1].x+dx/2, points[i-1].y+dy/2));
								segment.m_pointCount++;

								bAgain = true;
							}
							else
							{
								/*
								m_flatPoints.RemoveAt(i);
								m_subPoints[sub]--;

								bAgain = true;
								*/
							}
						}
					}
					while (bAgain);

					segment.m_bRecentAltered = false;
				}
				else	// Draw from original subpath data
				{
				}
			}

			ipt += segment.m_pointCount;
		}
	}
}

#include "..\gm\GraphicsGems.h"

typedef Point2 *BezierCurve;
void FitCurve(Point2	*d, int nPts, double error);

//CComPtr<IPDPath> g_pathElement;
static IPDSubPath* g_pathSegList;
static int g_pathSize;

void DrawBezierCurve(int n, BezierCurve curve)
{
	static BezierPoint bpt1;

	if (g_pathSize == 0)
	{
		BezierPoint bpt;
		bpt.x1 = curve[0].x;
		bpt.y1 = curve[0].y;
		bpt.x = curve[0].x;
		bpt.y = curve[0].y;
		bpt.x2 = curve[1].x;
		bpt.y2 = curve[1].y;

		long index;
		g_pathSegList->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);

		g_pathSize += 1;
	}
	else
	{
		bpt1.x = curve[0].x;
		bpt1.y = curve[0].y;
		bpt1.x2 = curve[1].x;
		bpt1.y2 = curve[1].y;

		long index;
		g_pathSegList->appendPoint(bpt1.x, bpt1.y, bpt1.x1, bpt1.y1, bpt1.x2, bpt1.y2, &index);

		g_pathSize =+ 1;
	}

	bpt1.x1 = curve[2].x;
	bpt1.y1 = curve[2].y;
}

void CPathSelection::ConvertFlatToCurves()
{
	for (int nsubpath = 0; nsubpath < m_flatSubPaths.GetSize(); nsubpath++)
	{
		CFlatSubPath* flatsubpath = m_flatSubPaths[nsubpath];
		int pointsIndex = 0;

		CComPtr<IPDSubPath> subpath;
		m_path->getSubPath(nsubpath, &subpath);

		VARIANT_BOOL closed;
		long nsubpathpoints;
		subpath->get_closed(&closed);
		subpath->get_pointCount(&nsubpathpoints);

		CComPtr<IPDSubPath> newsubpath;
		m_path->createSubPath(&newsubpath);

		newsubpath->put_closed(closed);

		if (nsubpathpoints > 0)
		{
			for (int nseg = 0; nseg < flatsubpath->m_flatSegments.GetSize();/* nseg++*/)
			{
				CFlatSegment segment = flatsubpath->m_flatSegments[nseg];

				int ntotalpoints = 0;

			// Find adjacent segments
				int nadjsegs;
				for (nadjsegs = 0; nseg+nadjsegs < flatsubpath->m_flatSegments.GetSize(); nadjsegs++)
				{
					CFlatSegment segment = flatsubpath->m_flatSegments[nseg+nadjsegs];

					ntotalpoints += segment.m_pointCount;

					if (!(segment.m_pointCount > 0 && segment.m_bAltered))
						break;
				}

				if (nadjsegs > 0)
				{
					DblPOINT* points = flatsubpath->m_flatPoints.GetData() + pointsIndex;

					g_pathSegList = newsubpath;
					g_pathSize = 0;

					double	error = 2;		//  Squared error
					FitCurve((Point2*)points, ntotalpoints, error);		//  Fit the Bezier curves

					/*
					{	// Get last point
						long npoints;
						newsubpath->get_pointCount(&npoints);
						newsubpath->getPoint(npoints-1, &bpt0);
					}
					*/

					nseg += nadjsegs;
				}
				else	// Draw from original subpath data
				{
					BezierPoint bpt1;
					subpath->getPoint(nseg, &bpt1);

					long index;
					newsubpath->appendPoint(bpt1.x, bpt1.y, bpt1.x1, bpt1.y1, bpt1.x2, bpt1.y2, &index);

					nseg++;
				}

				pointsIndex += ntotalpoints;
			}
		}

		m_path->insertSubPath(nsubpath, newsubpath);
		m_path->removeSubPath(subpath);
	}

	DeleteFlatData();
}

void CPathSelection::DeleteFlatData()
{
	for (int nsubpath = 0; nsubpath < m_flatSubPaths.GetSize(); nsubpath++)
	{
		CFlatSubPath* flatsubpath = m_flatSubPaths[nsubpath];
		delete flatsubpath;
	}
	m_flatSubPaths.RemoveAll();
}
