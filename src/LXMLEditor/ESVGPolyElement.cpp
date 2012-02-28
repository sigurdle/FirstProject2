#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EXMLDocument.h"

#include "ESVGPolyElement.h"

#include "ESelectedSVGPolyElement.h"

#if 0

//virtual
STDMETHODIMP CESVGPolyElement::CreateSelectedElement(IEXMLViewGroup* viewGroup, IESelectedElement* *pVal)
{
	ATLASSERT(0);
#if 0
	CComObject<CESelectedSVGPolyElement>* pSelectedElement;
	CComObject<CESelectedSVGPolyElement>::CreateInstance(&pSelectedElement);
	pSelectedElement->AddRef();
	pSelectedElement->m_pElement = this;//put_eElement(this);
	pSelectedElement->m_viewGroup = viewGroup;

	*pVal = pSelectedElement;
#endif
	return S_OK;
}

STDMETHODIMP CESVGPolyElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGAnimatedPoints> apoints = m_domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);

	points->LockUpdate();

	long numberOfItems;
	points->get_numberOfItems(&numberOfItems);
	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPoint> point;
		points->getItem(i, &point);

		double x, y;
		point->get_x(&x);
		point->get_y(&y);

		point->set_x(x+dx);
		point->set_y(y+dy);
	}

	points->UnlockUpdate();

	return S_OK;
}

STDMETHODIMP CESVGPolyElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	CComQIPtr<ILSVGTransformable> transformable = m_domElement;

	ATLASSERT(0);

#if 0
	CComPtr<ILSVGRect> svgbounds;
	transformable->getRBBox(&svgbounds);
	SVGRect bounds = svgbounds;

	double ox = bounds.X;
	double oy = bounds.Y;
	double ox2 = x;
	double oy2 = y;
	double sx = width/bounds.Width;
	double sy = height/bounds.Height;

	if (fabs(sx) < 0.001) sx = 0.001;
	if (fabs(sy) < 0.001) sy = 0.001;

	CComQIPtr<ILSVGAnimatedPoints> apoints = m_domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);

	points->LockUpdate();

	long numberOfItems;
	points->get_numberOfItems(&numberOfItems);
	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGPoint> point;
		points->getItem(i, &point);

		double x, y;
		point->get_x(&x);
		point->get_y(&y);

		point->put_x((x-ox)*sx+ox2);
		point->put_y((y-oy)*sy+oy2);
	}

	points->UnlockUpdate();
#endif

	return S_OK;
}

STDMETHODIMP CESVGPolyElement::get_pointCount(/*[out,retval]*/ long *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComQIPtr<ILSVGAnimatedPoints> apoints = m_domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);

	long numberOfItems;
	points->get_numberOfItems(&numberOfItems);

	*pVal = numberOfItems;

	return S_OK;
}

STDMETHODIMP CESVGPolyElement::IsClosed(/*[out,retval]*/ VARIANT_BOOL* pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComQIPtr<ILSVGPolygonElement> polygon = m_domElement;
	if (polygon)
	{
		*pVal = VARIANT_TRUE;
	}
	else
	{
		*pVal = VARIANT_FALSE;
	}

	return S_OK;
}

STDMETHODIMP CESVGPolyElement::SetClosed(/*[in]*/ VARIANT_BOOL bClosed, IEElement* *pVal)
{
	VARIANT_BOOL bOldClosed;
	IsClosed(&bOldClosed);

	if ((bOldClosed == 0) != (bClosed == 0))
	{
		CComPtr<ILDOMDocument> document;
		m_domElement->get_ownerDocument(&document);

		CComPtr<ILDOMElement> newElement;
		if (bClosed)
			document->renameNode(m_domElement, L"http://www.w3.org/2000/svg", L"polygon", (ILDOMNode**)&newElement);
		else
			document->renameNode(m_domElement, L"http://www.w3.org/2000/svg", L"polyline", (ILDOMNode**)&newElement);

		CComPtr<IEElement> newEElement;
		m_pDocument->GetEElementFromDOMElement(newElement, &newEElement);
		ATLASSERT(newEElement);

		if (pVal)
		{
			*pVal = newEElement;
			(*pVal)->AddRef();
		}
	}
	else
	{
		if (pVal)
		{
			*pVal = this;
			(*pVal)->AddRef();
		}
	}

	return S_OK;
}

STDMETHODIMP CESVGPolyElement::HitTest(ISVGView* view, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit)
{
	CComQIPtr<ILSVGAnimatedPoints> apoints = m_domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);

	return HitTest(points, view, svgsvgElement, ctm, ptx, pty, hit);
}

STDMETHODIMP CESVGPolyElement::HitTest(ILSVGPointList* points, ISVGView* view, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* ctm, double ptx, double pty, _SVGHitData* hit)
{
	long numberOfItems;
	points->get_numberOfItems(&numberOfItems);

	for (int i = numberOfItems-1; i >= 0; i--)
	{
		CComPtr<ILSVGPoint> point;
		points->getItem(i, &point);

		SVGPoint pt = point;
		SVGPoint xpt = pt.matrixTransform(ctm);

		if (abs(ptx-xpt.X) < 4 && abs(pty-xpt.Y) < 4)
		{
			hit->element = this;
			hit->anchor = i;
			hit->ctl = 0;

			return S_OK;
		}
	}

	if (numberOfItems > 0)
	{
		gmVector2 P(ptx,pty);

		CComPtr<ILSVGPoint> point;
		points->getItem(0, &point);
		gmVector2 A = SVGPoint(point).matrixTransform(ctm);

		for (i = 1; i < numberOfItems; i++)
		{
			CComPtr<ILSVGPoint> point;
			points->getItem(i, &point);

			gmVector2 B = SVGPoint(point).matrixTransform(ctm);

			double bboxX1 = min(A[0], B[0])-2;
			double bboxY1 = min(A[1], B[1])-2;
			double bboxX2 = max(A[0], B[0])+2;
			double bboxY2 = max(A[1], B[1])+2;

			if (P[0] >= bboxX1 && P[1] >= bboxY1 && P[0] <= bboxX2 && P[1] <= bboxY2)
			{
				double a2 = (P[1]-A[1])*(B[0]-A[0]) - (P[0]-A[0])*(B[1]-A[1]);

				double d1 = (a2*a2)/((B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]));

				if (d1 < 3*3)
				{
					hit->element = this;
					hit->segment = i-1;

					double L2 = (B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]);
					hit->t = ((P[0]-A[0])*(B[0]-A[0]) + (P[1]-A[1])*(B[1]-A[1]))/L2;

#if 0
				//	hit->t = dot(A, P);
					hit->t = (P[0]-A[0])*(B[0]-A[0]) + (P[1]-A[1])*(B[1]-A[1]);
				//	hit->t = (B[0]-P[0])*(B[0]-A[0]) + (B[1]-P[1])*(B[1]-A[1]);

					hit->t /= distance(A,B);
#endif

					return S_OK;
				}
			}

			A = B;
		}
	}

	return CESVGElementImpl<IESVGPolyElement>::HitTest(view, svgsvgElement, ctm, ptx, pty, hit);
}

// IESVGDrawOutline
STDMETHODIMP CESVGPolyElement::DrawOutline(ILSVGPointList* points, LDraw::Graphics* pGraphics, LDraw::Color color, LSVG::SVGMatrix* matrix)
{
	ATLASSERT(0);
#if 0
	LDraw::Pen pen(color);

	long numberOfItems = points->get_numberOfItems();

	if (numberOfItems > 0)
	{
		LSVG::CLSVGPoint* point = points->getItem(0);

		SVGPoint pt = point;
		SVGPoint xpt0 = pt.matrixTransform(matrix);

		for (int i = 1; i < numberOfItems; i++)
		{
			CComPtr<ILSVGPoint> point;
			points->getItem(i, &point);

			SVGPoint pt = point;

			SVGPoint xpt = pt.matrixTransform(matrix);

			pGraphics->DrawLine(&pen, (int)(xpt0.X), (int)(xpt0.Y), (int)(xpt.X), (int)(xpt.Y));

			xpt0 = xpt;
		}
	}
#endif
	return S_OK;
}

STDMETHODIMP CESVGPolyElement::DrawOutline(LDraw::Graphics* pGraphics, LDraw::Color& color, ILSVGMatrix* matrix)
{
	CComQIPtr<ILSVGAnimatedPoints> apoints = m_domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);

	DrawOutline(points, pGraphics, color, matrix);

	return S_OK;
}

// IESVGSimpleShapeElement
STDMETHODIMP CESVGPolyElement::DrawPathSegList(/*[in]*/ ILSVGPathElement* pathElement, /*[in]*/ ILSVGPathSegList* seglist)
{
	CComQIPtr<ILSVGAnimatedPoints> apoints = m_domElement;

	CComPtr<ILSVGPointList> points;
	apoints->get_points(&points);

	long numberOfItems;
	points->get_numberOfItems(&numberOfItems);

	if (numberOfItems > 0)
	{
		CComPtr<ILSVGPoint> point;
		points->getItem(0, &point);
		double x, y;
		point->get_x(&x);
		point->get_y(&y);

		CComPtr<ILSVGPathSegMovetoAbs> moveto;
		pathElement->createSVGPathSegMovetoAbs(x, y, &moveto);
		seglist->appendItem(moveto, NULL);

		for (int i = 0; i < numberOfItems; i++)
		{
			CComPtr<ILSVGPoint> point;
			points->getItem(i, &point);

			point->get_x(&x);
			point->get_y(&y);

			CComPtr<ILSVGPathSegLinetoAbs> lineto;
			pathElement->createSVGPathSegLinetoAbs(x, y, &lineto);
			seglist->appendItem(lineto, NULL);
		}

		CComQIPtr<ILSVGPolygonElement> polygon = m_domElement;
		if (polygon)
		{
			CComPtr<ILSVGPathSegClosePath> closepath;
			pathElement->createSVGPathSegClosePath(&closepath);
			seglist->appendItem(closepath, NULL);
		}
	}

	return S_OK;
}

#endif