#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGGElement.h"

#if 0

STDMETHODIMP CESVGGElement::Move(ISVGView* view, double dx, double dy)
{
//	CComQIPtr<ILSVGSVGElement> svgsvgElement = m_domElement;

	ATLASSERT(0);
#if 0

	CComQIPtr<ILSVGGElement> g = m_domElement;

	CComPtr<ILDOMNode> node;
	g->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILSVGLocatable> locatable = node;
		if (locatable)
		{
			CComQIPtr<ILDOMElement> element = node;

			CComPtr<IEElement> eelement;
			m_pDocument->GetEElementFromDOMElement(element, &eelement);
			
			CComQIPtr<IESVGElement> esvgelement = eelement;
			if (esvgelement)
			{
				//CComQIPtr<ILSVGTransformable> transformable = node;
				//if (transformable)
				CComPtr<ILSVGMatrix> matrix;
				locatable->getTransformMatrix(&matrix);

				CComPtr<ILSVGMatrix> imatrix;
				matrix->inverse(&imatrix);

				LDraw::PointD pt0(0,0);
				LDraw::PointD xpt0 = pt0.matrixTransform(imatrix);

				LDraw::PointD pt1(dx,dy);
				LDraw::PointD xpt1 = pt1.matrixTransform(imatrix);

				esvgelement->Move(view, xpt1.X-xpt0.X, xpt1.Y-xpt0.Y);
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
	return S_OK;
}

// IESVGDrawOutline
STDMETHODIMP CESVGGElement::DrawOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
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
				CComPtr<ILSVGMatrix> childMatrix;
				CComQIPtr<ILSVGLocatable> locatable = element;
				if (locatable)
				{
					CComPtr<ILSVGMatrix> ctm;
					locatable->getTransformMatrix(&ctm);

					ctm->multiply(matrix, &childMatrix);
				}
				else
					childMatrix = matrix;

				drawOutline->DrawOutline(pGraphics, color, childMatrix);
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return S_OK;
}

#endif