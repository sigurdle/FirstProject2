#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESelectedSVGPathElement.h"

#include "SVGBehavior.h"

namespace System
{
namespace LXmlEdit
{

#if 0

#define MATCHPOINT(x1, y1, x2, y2) ((fabs((x2)-(x1)) <= 4) && \
												(fabs((y2)-(y1)) <= 4))

HRESULT SetProperty(IUnknown* unk, BSTR name, VARIANT var);
_variant_t GetProperty(IUnknown* unk, BSTR name);

LDraw::PointD GetPathSegP2(LSVG::CLSVGPathSegList* seglist, int index);
LDraw::PointD GetPathSegP3(LSVG::CLSVGPathSegList* seglist, int index);

void InsertAnchorPoint(ILSVGPathElement* path, ILSVGPathSegList* seglist, int segindex, double t);
void DeleteAnchorPoint(ILSVGPathSegList* seglist, int segindex);

//////////

STDMETHODIMP CESelectedSVGPathElement::HitTest(ISVGView* view, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* ctm, double ptx, double pty, long tool, _SVGHitData* hit)
{
	m_pElement->HitTest(view, svgsvgElement, ctm, ptx, pty, /*tool,*/ hit);

	SVGPoint pt(ptx, pty);

	//if (tool == 2/*ID_SVGTOOL_DIRECT*/)	// Direct selection tool
	{
		hit->anchor = FindPoint(ctm, pt.X, pt.Y, hit->ctl);
		if (hit->anchor >= 0)
		{
			//hit->path = this;//pFrame;//pdpath;
			hit->hit = -1;

			return S_OK;
		}
	}

	return CESelectedElementImpl<IESelectedSVGPathElement>::HitTest(view, svgsvgElement, ctm, ptx, pty, tool, hit);
}

void CESelectedSVGPathElement::MoveSelectedPoints(ILSVGPathSegList* seglist, _SVGHitData* hitdata, LDraw::PointD xnewpt2, LDraw::PointD xoldpt2 /*, LDraw::RectF& invalidBounds,*/)
{
	if (hitdata->ctl == 0)	// Clicked on anchor point
	{
		double dx = xnewpt2.X - xoldpt2.X;
		double dy = xnewpt2.Y - xoldpt2.Y;

		MovePoints(seglist, dx, dy, false);
	}
	else
	{
	}
}

void CESelectedSVGPathElement::MoveSelectedPoints(_SVGHitData* hitdata, SVGPoint xnewpt2, SVGPoint xoldpt2 /*, LDraw::RectF& invalidBounds,*/)
{
	if (hitdata->ctl == 0)	// Clicked on anchor point
	{
		double dx = xnewpt2.X - xoldpt2.X;
		double dy = xnewpt2.Y - xoldpt2.Y;

		MovePoints(dx, dy, false);
	}
	else
	{
	}
}

void CESelectedSVGPathElement::DrawSelection(ILSVGPathSegList* seglist, LDraw::Graphics* pGraphics, LDraw::Color& color, ILSVGMatrix* matrix)
{
	LDraw::Pen pen(color);
	LDraw::SolidBrush brush(color);
	LDraw::SolidBrush whitebrush(LDraw::Color(255, 255, 255));

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	int npathpt = 0;
	while (npathpt < numberOfItems)
	{
		int nAnchorsSelected = 0;	// number of anchors selected in subpath
		int i;
		for (i = npathpt+1; i < numberOfItems; i++)
		{
			CComPtr<ILSVGPathSeg> seg;
			seglist->getItem(i, &seg);

			LSVGPathSegType segType;
			seg->get_pathSegType(&segType);
	/*
	PATHSEG_CLOSEPATH	= 1,
	PATHSEG_MOVETO_ABS	= 2,
	PATHSEG_MOVETO_REL	= 3,
	*/
			if (segType == PATHSEG_MOVETO_ABS ||
				segType == PATHSEG_MOVETO_REL)
			{
				// Beginning of new subpath
				break;
			}
			else if (segType == PATHSEG_CLOSEPATH)
			{
				i++;
				break;
			}

			if (IsAnchorSelected(i))
			{
				nAnchorsSelected++;
			}
		}

		int subpathNumberOfItems = i-npathpt;	// number of segments in subpath

		for (int index = npathpt; index < i; index++)
		{
			CComPtr<ILSVGPathSeg> seg;
			seglist->getItem(index, &seg);

			SVGPoint P;
			P.X = GetProperty(seg, L"x");
			P.Y = GetProperty(seg, L"y");
			SVGPoint P2 = GetPathSegP2(seglist, index);
			SVGPoint P3 = GetPathSegP3(seglist, index);

			SVGPoint XP = P.matrixTransform(matrix);
			SVGPoint XP2 = P2.matrixTransform(matrix);
			SVGPoint XP3 = P3.matrixTransform(matrix);

			BOOL indexSelected = IsAnchorSelected(index);

			BOOL c1;
			BOOL c2;
			IsControlPointVisible(subpathNumberOfItems, nAnchorsSelected, npathpt, index-npathpt, &c1, &c2);

			if (c1)
			{
				pGraphics->DrawLine(&pen, (float)XP.X, (float)XP.Y, (float)XP2.X, (float)XP2.Y);
				pGraphics->FillEllipse(&brush, (int)(XP2.X-2), (int)(XP2.Y-2), (4), (4));
			}

			if (c2)
			{
				pGraphics->DrawLine(&pen, (float)XP.X, (float)XP.Y, (float)XP3.X, (float)XP3.Y);
				pGraphics->FillEllipse(&brush, (int)(XP3.X-2), (int)(XP3.Y-2), (4), (4));
			}

			if (indexSelected)
			{
				pGraphics->FillRectangle(&brush, (int)(XP.X-2), (int)(XP.Y-2), (4), (4));
			}
			else
			{
				pGraphics->DrawRectangle(&pen, (int)(XP.X-2), (int)(XP.Y-2), (4), (4));
				pGraphics->FillRectangle(&whitebrush, (int)(XP.X-1), (int)(XP.Y-1), (3), (3));
			}
		}

		npathpt += subpathNumberOfItems;
	}
}

// virtual
HRESULT CESelectedSVGPathElement::DrawSelection(LDraw::Graphics* pGraphics, LDraw::Color& color, ILSVGMatrix* matrix)
{
	CComQIPtr<ILSVGPathElement> path = GetPath()->m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_pathSegList(&seglist);

	DrawSelection(seglist, pGraphics, color, matrix);

	return S_OK;
}

///////////


CESVGPathElement* CESelectedSVGPathElement::GetPath()
{
	return (CESVGPathElement*)m_pElement;
}

void CESelectedSVGPathElement::DeleteAnchorPoint(int segindex)
{
	m_selectedPoints.RemoveAll();

	CComQIPtr<ILSVGPathElement> path = GetPath()->m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
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

void CESelectedSVGPathElement::InsertAnchorPoint(int segindex, double t)
{
	m_selectedPoints.RemoveAll();

	CComQIPtr<ILSVGPathElement> path = GetPath()->m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
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

BOOL CESelectedSVGPathElement::IsSegmentSelected(long index)
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
}

STDMETHODIMP CESelectedSVGPathElement::SelectSegment(long index)
{
//	ASSERT(!IsSegmentSelected(index));

	for (int i = 0; i < m_selectedSegments.GetSize(); i++)
	{
		if (index == m_selectedSegments[i]) return S_OK; 
		if (index < m_selectedSegments[i]) break;
	}
	m_selectedSegments.InsertAt(i, index);

	return S_OK;
}

STDMETHODIMP CESelectedSVGPathElement::DeselectSegment(long index)
{
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] == index)
		{
			m_selectedPoints.RemoveAt(i);
			return S_OK;
		}
	}

	return S_OK;
}

#if 0
HRESULT splitOnSegment(ILSVGPathSegList* seglist, long index, long* pRotateVal)
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
#endif

LSVGPathSegType GetPathSegType(ILSVGPathSegList* seglist, int index)
{
	CComPtr<ILSVGPathSeg> seg;
	seglist->getItem(index, &seg);

	LSVGPathSegType segType;
	seg->get_pathSegType(&segType);

	return segType;
}

HRESULT splitOnAnchor(ILSVGPathElement* pathElement, ILSVGPathSegList* seglist, long index, long* pRotateVal)
{
	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	// Find index of start of subpath
	int startSubPath;
	for (startSubPath = index; startSubPath >= 0; startSubPath--)
	{
		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(startSubPath, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);

		if (segType == PATHSEG_MOVETO_REL || segType == PATHSEG_MOVETO_ABS)
			break;
	}

	// Find number of segments in subpath
	int i;
	for (i = index+1; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);

		if (segType == PATHSEG_MOVETO_REL || segType == PATHSEG_MOVETO_ABS)
			break;
	}
	int nSubPathPoints = i-startSubPath;

	seglist->LockUpdate();

	if (GetPathSegType(seglist, startSubPath+nSubPathPoints-1) == PATHSEG_CLOSEPATH)
	{
		// Replace index+1 segment with a moveto
		{
			CComPtr<ILSVGPathSeg> nextseg;
			seglist->getItem(index+1, &nextseg);
			double x = GetProperty(nextseg, L"x");
			double y = GetProperty(nextseg, L"y");
			double x2 = GetProperty(nextseg, L"x2");
			double y2 = GetProperty(nextseg, L"y2");

			CComPtr<ILSVGPathSegMovetoAbs> moveseg;
			pathElement->createSVGPathSegMovetoAbs(x, y, &moveseg);

			seglist->replaceItem(moveseg, index+1, NULL);
			SetProperty(moveseg, L"x2", _variant_t(x2));
			SetProperty(moveseg, L"y2", _variant_t(y2));
		}

		// remove the first moveto of the subpath
		seglist->removeItem(startSubPath, NULL);
		numberOfItems--;
		nSubPathPoints--;
		//if (index > startSubPath)
			index--;

	// remove the last closepath 'z' of the subpath
		seglist->removeItem(startSubPath+nSubPathPoints-1, NULL);
		numberOfItems--;
		nSubPathPoints--;

	// remove the actual point
		if (index >= 0)
		{
			seglist->removeItem(index, NULL);
			numberOfItems--;
			nSubPathPoints--;
		}
		else
		{
			index = nSubPathPoints;
			seglist->removeItem(startSubPath+nSubPathPoints-1, NULL);
		}

		for (int npt = index; npt < nSubPathPoints; npt++)
		{
			CComPtr<ILSVGPathSeg> seg;
			seglist->removeItem(startSubPath+nSubPathPoints-1, &seg);	// Remove from end
			seglist->insertItemBefore(seg, startSubPath, NULL);	// Reinsert at beginning
		}
	}
	else	// open
	{
		seglist->removeItem(index, NULL);
		numberOfItems--;
		nSubPathPoints--;

		// replace the next segment in the subpath with moveto
		if (index < startSubPath+nSubPathPoints)
		{
			CComPtr<ILSVGPathSeg> nextseg;
			seglist->getItem(index, &nextseg);
			double x = GetProperty(nextseg, L"x");
			double y = GetProperty(nextseg, L"y");
			double x2 = GetProperty(nextseg, L"x2");
			double y2 = GetProperty(nextseg, L"y2");

			CComPtr<ILSVGPathSegMovetoAbs> moveseg;
			pathElement->createSVGPathSegMovetoAbs(x, y, &moveseg);

			seglist->replaceItem(moveseg, index, NULL);
			SetProperty(moveseg, L"x2", _variant_t(x2));
			SetProperty(moveseg, L"y2", _variant_t(y2));
		}
	}

	seglist->UnlockUpdate();

#if 0
	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	BOOL bClosed = FALSE;

	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);

		if (segType > PATHSEG_MOVETO_REL)	// We're still in same subpath
		{
			if (segType == PATHSEG_CLOSE_PATH)
			{
				bClose = TRUE;
			}
		}
	}

	long npoints;
	for (int nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
	{
		npoints = m_subPaths[nsubpath]->m_points.GetSize();
		if (index-npoints < 0) break;

		index -= npoints;
	}

	if (bClosed)
	{
#if 0
		seglist->removeItem(index, NULL);
		//m_subPaths[nsubpath]->m_points.RemoveAt(index);
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
#endif
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
					/*
					CBezierPoint bpt = m_subPaths[nsubpath]->m_points[npt];
					pSubPath->m_points.Add(bpt);
					*/
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
#endif

	return S_OK;
}

void CESelectedSVGPathElement::DeleteSelection(ILSVGPathSegList* seglist)
{
	CComQIPtr<ILSVGPathElement> path = GetPath()->m_domElement;

	int i;

#if 0
	for (i = m_selectedSegments.GetSize()-1; i >= 0; i--)
	{
		long rotate;
		m_path->splitOnSegment(m_selectedSegments[i], &rotate);
		RotateSelectedPointIndexes(rotate);

		m_selectedSegments.RemoveAt(i);
	}
#endif

	int size = m_selectedPoints.GetSize();

	for (i = size-1; i >= 0; i--)
	{
		long rotate;
		splitOnAnchor(path, seglist, m_selectedPoints[i], &rotate);
#if 0
		RotateSelectedPointIndexes(rotate);
#endif

		m_selectedPoints.RemoveAt(i);
	}
}

STDMETHODIMP CESelectedSVGPathElement::DeleteSelection()
{
	CComQIPtr<ILSVGPathElement> path = GetPath()->m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_pathSegList(&seglist);

	DeleteSelection(seglist);

	return S_OK;
}

void CESelectedSVGPathElement::MovePoints(ILSVGPathSegList* seglist, double dx, double dy, /*LDraw::RectF& invalidBounds,*/ bool bAll /* = true */)
{
	seglist->LockUpdate();

	/*
	double minx = 999999;
	double miny = 999999;
	double maxx = -999999;
	double maxy = -999999;
	*/

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		if (bAll || IsAnchorSelected(i))
		{
			double x = GetProperty(seg, L"x");
			double y = GetProperty(seg, L"y");
			double x2 = GetProperty(seg, L"x2");
			double y2 = GetProperty(seg, L"y2");
			double x3 = GetProperty(seg, L"x3");
			double y3 = GetProperty(seg, L"y3");

			SetProperty(seg, L"x", CComVariant(x+dx));
			SetProperty(seg, L"y", CComVariant(y+dy));
			SetProperty(seg, L"x2", CComVariant(x2+dx));
			SetProperty(seg, L"y2", CComVariant(y2+dy));
			SetProperty(seg, L"x3", CComVariant(x3+dx));
			SetProperty(seg, L"y3", CComVariant(y3+dy));

			if (i < numberOfItems-1)
			{
				CComPtr<ILSVGPathSeg> seg;
				seglist->getItem(i+1, &seg);
	
				LSVGPathSegType segType;
				seg->get_pathSegType(&segType);

				if (segType > PATHSEG_MOVETO_REL)	// We're still in same subpath
				{
					double x1 = GetProperty(seg, L"x1");
					double y1 = GetProperty(seg, L"y1");
					SetProperty(seg, L"x1", CComVariant(x1+dx));
					SetProperty(seg, L"y1", CComVariant(y1+dy));
				}
			}
		}
	}

	/*
	invalidBounds.X = minx;
	invalidBounds.Y = miny;
	invalidBounds.Width = maxx-minx;
	invalidBounds.Height = maxy-miny;
	*/

	seglist->UnlockUpdate();
}

void CESelectedSVGPathElement::MovePoints(double dx, double dy, /*LDraw::RectF& invalidBounds,*/ bool bAll /* = true */)
{
	CComQIPtr<ILSVGPathElement> path = GetPath()->m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_pathSegList(&seglist);

	MovePoints(seglist, dx, dy, bAll);
}

BOOL CESelectedSVGPathElement::IsAnchorSelected(long index)
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

STDMETHODIMP CESelectedSVGPathElement::SelectAnchor(long index)
{
//	ASSERT(!IsAnchorSelected(index));

	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (index == m_selectedPoints[i]) return S_OK;
		if (index < m_selectedPoints[i]) break;
	}
	m_selectedPoints.InsertAt(i, index);

	return S_OK;
}

STDMETHODIMP CESelectedSVGPathElement::DeselectAnchor(long index)
{
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] == index)
		{
			m_selectedPoints.RemoveAt(i);
			return S_OK;
		}
	}

	return S_OK;
}

void CESelectedSVGPathElement::IsControlPointVisible(long nsubpathpoints, int nAnchorsSelected, int ntotalpoints, int npt, BOOL* c1, BOOL* c2)
{
//	long npoints;
//	subpath->get_pointCount(&npoints);

	int index = ntotalpoints + npt;
	int nextIndex = (npt < nsubpathpoints-1)? index+1: ntotalpoints;
	int prevIndex = (npt > 0)? index-1: ntotalpoints+nsubpathpoints-1;

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

int CESelectedSVGPathElement::FindPoint(ILSVGPathSegList* seglist, ILSVGMatrix* matrix, double mousex, double mousey, long& ctl)
{
	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	int npathpt = 0;
	while (npathpt < numberOfItems)
	{
		int nAnchorsSelected = 0;	// number of anchors selected in subpath
		int i;
		for (i = npathpt+1; i < numberOfItems; i++)
		{
			CComPtr<ILSVGPathSeg> seg;
			seglist->getItem(i, &seg);

			LSVGPathSegType segType;
			seg->get_pathSegType(&segType);
	/*
	PATHSEG_CLOSEPATH	= 1,
	PATHSEG_MOVETO_ABS	= 2,
	PATHSEG_MOVETO_REL	= 3,
	*/
			if (segType == PATHSEG_MOVETO_ABS ||
				segType == PATHSEG_MOVETO_REL)
			{
				// Beginning of new subpath
				break;
			}
			else if (segType == PATHSEG_CLOSEPATH)
			{
				i++;
				break;
			}

			if (IsAnchorSelected(i))
			{
				nAnchorsSelected++;
			}
		}

		int subpathNumberOfItems = i-npathpt;	// number of segments in subpath

		for (int index = npathpt; index < i; index++)
		{
			CComPtr<ILSVGPathSeg> seg;
			seglist->getItem(index, &seg);

			SVGPoint P;
			P.X = GetProperty(seg, L"x");
			P.Y = GetProperty(seg, L"y");
			SVGPoint P2 = GetPathSegP2(seglist, index);
			SVGPoint P3 = GetPathSegP3(seglist, index);

			SVGPoint XP = P.matrixTransform(matrix);
			SVGPoint XP2 = P2.matrixTransform(matrix);
			SVGPoint XP3 = P3.matrixTransform(matrix);

			if (fabs(XP.X-mousex) < 4 && fabs(XP.Y-mousey) < 4)
			{
				ctl = 0;
				return index;
			}

			BOOL c1;
			BOOL c2;
			IsControlPointVisible(subpathNumberOfItems, nAnchorsSelected, npathpt, index-npathpt, &c1, &c2);

			if (c1)
			{
				if (fabs(XP2.X-mousex) < 4 && fabs(XP2.Y-mousey) < 4)
				{
					ctl = -1;
					return index;
				}
			}

			if (c2)
			{
				if (fabs(XP3.X-mousex) < 4 && fabs(XP3.Y-mousey) < 4)
				{
					ctl = 1;
					return index;
				}
			}
		}

		npathpt += subpathNumberOfItems;
	}

	return -1;
}

int CESelectedSVGPathElement::FindPoint(ILSVGMatrix* matrix, double mousex, double mousey, long& ctl)
{
	CComQIPtr<ILSVGPathElement> path = GetPath()->m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_pathSegList(&seglist);

	return FindPoint(seglist, matrix, mousex, mousey, ctl);
}

void CESelectedSVGPathElement::InsertPointBefore(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] >= index)
		{
			m_selectedPoints[i]++;
		}
	}

	CComQIPtr<ILSVGPathElement> path = GetPath()->m_domElement;
	CComQIPtr<ILSVGAnimatedPathData> pathData = path;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_normalizedPathSegList(&seglist);

	ASSERT(0);
	{
	}
	//m_path->insertPointBefore(index, x, y, x1, y1, x2, y2);
#endif
}

void CESelectedSVGPathElement::InsertPointAfter(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
{
#if 0
	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		if (m_selectedPoints[i] > index)
		{
			m_selectedPoints[i]++;
		}
	}

	CComPtr<IESVGPath> path;
	GetPath()->GetPath(&path);

	static_cast<CESVGPath*>(path.p)->InsertPointAfter(index, x, y, x1, y1, x2, y2);
#endif
}

#endif

}	// LXmlEdit
}
