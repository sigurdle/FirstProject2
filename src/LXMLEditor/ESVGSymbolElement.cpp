#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EXMLDocument.h"

#include "ESVGSymbolElement.h"

#if 0

// IESVGDrawOutline
STDMETHODIMP CESVGSymbolElement::DrawOutline(LDraw::Graphics* pGraphics, LDraw::Color color, LSVG::SVGMatrix* matrix)
{
	CComPtr<ILDOMNode> node;
	m_domElement->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComPtr<IEElement> eelement;
			m_pDocument->GetEElementFromDOMElement(element, &eelement);
			
			CComQIPtr<IESVGDrawOutline> drawOutline = eelement;
			if (drawOutline)
			{
				drawOutline->DrawOutline(pGraphics, color, matrix);
#if 0
				CComPtr<ILSVGMatrix> matrix;
				transformable->getCTM(&matrix);

				CComPtr<ILSVGMatrix> imatrix;
				matrix->inverse(&imatrix);

				/*
				CPointD pt0;
				pt0.x = 0;
				pt0.y = 0;

				PointD pt1;
				pt1.x = dx;
				pt1.y = dy;
				*/

				SVGPoint pt0(0,0);
				SVGPoint xpt0 = pt0.matrixTransform(imatrix);

				SVGPoint pt1(dx,dy);
				SVGPoint xpt1 = pt1.matrixTransform(imatrix);

				/*
				CComPtr<ILSVGPoint> svgPoint0;
				svgsvgElement->createSVGPoint(&svgPoint0);
				svgPoint0->put_x(0);
				svgPoint0->put_y(0);
				CComPtr<ILSVGPoint> xsvgPoint0;
				svgPoint0->matrixTransform(imatrix, &xsvgPoint0);

				CComPtr<ILSVGPoint> svgPoint1;
				svgsvgElement->createSVGPoint(&svgPoint1);
				svgPoint1->put_x(dx);
				svgPoint1->put_y(dy);
				CComPtr<ILSVGPoint> xsvgPoint1;
				svgPoint1->matrixTransform(imatrix, &xsvgPoint1);

				//imatrix->transformPoint(&pt0, &pt0);
				//imatrix->transformPoint(&pt1, &pt1);

				SVGPoint xpt0 = svgPoint0;
				SVGPoint xpt1 = svgPoint1;
				*/

				esvgelement->Move(xpt1.X-xpt0.X, xpt1.Y-xpt0.Y);
			//	objectTransformable->Move(pt1.x-pt0.x, pt1.y-pt0.y);
#endif
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return S_OK;
}

#endif