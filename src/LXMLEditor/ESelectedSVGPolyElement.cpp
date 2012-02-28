#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESelectedSVGPolyElement.h"
#include "ESVGPolyElement.h"

#if 0

BOOL CESelectedSVGPolyElement::IsSegmentSelected(long index)
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

STDMETHODIMP CESelectedSVGPolyElement::SelectSegment(long index)
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

STDMETHODIMP CESelectedSVGPolyElement::DeselectSegment(long index)
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

BOOL CESelectedSVGPolyElement::IsAnchorSelected(long index)
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

STDMETHODIMP CESelectedSVGPolyElement::SelectAnchor(long index)
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

STDMETHODIMP CESelectedSVGPolyElement::DeselectAnchor(long index)
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

STDMETHODIMP CESelectedSVGPolyElement::DeselectAllPoints()
{
	m_selectedPoints.RemoveAll();
	m_selectedSegments.RemoveAll();

	return S_OK;
}

STDMETHODIMP CESelectedSVGPolyElement::DeleteSelection()
{
	return S_OK;
}

STDMETHODIMP CESelectedSVGPolyElement::HitTest(ISVGView* view, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* ctm, double ptx, double pty, long tool, _SVGHitData* hit)
{
	return m_pElement->HitTest(view, svgsvgElement, ctm, ptx, pty, /*tool,*/ hit);
}

void CESelectedSVGPolyElement::MoveSelectedPoints(ILSVGPointList* points, _SVGHitData* hitdata, SVGPoint xnewpt2, SVGPoint xoldpt2)
{
	double dx = xnewpt2.X - xoldpt2.X;
	double dy = xnewpt2.Y - xoldpt2.Y;

	points->LockUpdate();

	for (int i = 0; i < m_selectedPoints.GetSize(); i++)
	{
		CComPtr<ILSVGPoint> point;
		points->getItem(m_selectedPoints[i], &point);

		double x, y;
		point->get_x(&x);
		point->get_y(&y);

		point->put_x(x+dx);
		point->put_y(y+dy);
	}

	points->UnlockUpdate();
}

void CESelectedSVGPolyElement::MoveSelectedPoints(_SVGHitData* hitdata, SVGPoint xnewpt2, SVGPoint xoldpt2/*, LDraw::RectF& invalidBounds,*/)
{
	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

	CComQIPtr<ILSVGAnimatedPoints> apoints = domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);

	MoveSelectedPoints(points, hitdata, xnewpt2, xoldpt2);
}

// IESVGDrawOutline
STDMETHODIMP CESelectedSVGPolyElement::DrawOutline(LDraw::Graphics* pGraphics, LDraw::Color& color, ILSVGMatrix* matrix)
{
	return ((CESVGPolyElement*)m_pElement)->DrawOutline(pGraphics, color, matrix);
}

// IESVGDrawSelection
HRESULT CESelectedSVGPolyElement::DrawSelection(LDraw::Graphics* pGraphics, LDraw::Color& color, ILSVGMatrix* matrix)
{
	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

	CComQIPtr<ILSVGAnimatedPoints> apoints = domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);

	DrawSelection(points, pGraphics, color, matrix);

	return S_OK;
}

HRESULT CESelectedSVGPolyElement::DrawSelection(ILSVGPointList* points, LDraw::Graphics* pGraphics, LDraw::Color color, LSVG::SVGMatrix* matrix)
{
	LDraw::Pen pen(color);
	LDraw::SolidBrush brush(color);
	LDraw::SolidBrush whitebrush(LDraw::Color(255, 255, 255));

	/*
	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

	CComQIPtr<ILSVGAnimatedPoints> apoints = domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);
	*/

	long numberOfItems;
	points->get_numberOfItems(&numberOfItems);
	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPoint> point;
		points->getItem(i, &point);

		SVGPoint pt = point;

		SVGPoint xpt = pt.matrixTransform(matrix);

		if (IsAnchorSelected(i))
		{
			pGraphics->FillRectangle(&brush, (int)(xpt.X-2), (int)(xpt.Y-2), (4), (4));
		}
		else
		{
			pGraphics->DrawRectangle(&pen, (int)(xpt.X-2), (int)(xpt.Y-2), (4), (4));
			pGraphics->FillRectangle(&whitebrush, (int)(xpt.X-1), (int)(xpt.Y-1), (3), (3));
		}
	}

	return S_OK;
}

#endif