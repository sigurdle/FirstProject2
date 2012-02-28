#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGUseElement.h"
#include "SVGUseElement.h"

//#include "PSVGSymbolElement.h"
//#include "SVGSymbolElement.h"

//#include "PSVGFilterElement.h"
//#include "LSVGMatrix.h"

namespace System
{
namespace Web
{
//RectD GetViewBoxRect(CSVGRectViewBox* _viewBox, CLSVGPreserveAspectRatio* preserveAspectRatio, RectD viewPort);
gm::RectD GetViewBoxRect(gm::RectD viewBox, SVGPreserveAspectRatio* preserveAspectRatio, gm::RectD viewPort);
gm::matrix3d GetViewBoxMatrix(gm::RectD rect, gm::RectD viewPort);

PSVGUseElement::PSVGUseElement(SVGUseElement* element) : PSVGElement(element)
{
	m_pInstanceRoot = NULL;
}

#if 0
PSVGElement* CloneRenderTree(PSVGElement* pParent, PSVGElement* pElement)
{
	CComQIPtr<ILSVGElement> element = pElement->m_pNode;
	if (element)
	{
		PSVGElement* pClone = (PSVGElement*)pParent->m_pView->CreateElement(element);

		pClone->m_parent = pParent;
		pClone->GetCSSProperties();

		UPOSITION pos = pElement->m_childListRender.GetHeadPosition();
		while (pos)
		{
			PSVGElement* pElement2 = (PSVGElement*)pElement->m_childListRender.GetNext(pos);

			PSVGElement* pClone2 = CloneRenderTree(pClone, pElement2);
			if (pClone2)
			{
				pClone->m_childList.AddTail(pClone2);

				// TODO, not always
				pClone->m_childListRender.AddTail(pClone2);
			}
		}

		pClone->CalculateBoundsAndChildren();	// This calculates children first

		return pClone;
	}

	return NULL;
}
#endif

PSVGElement* CloneInstanceTree(PSVGElement* pParent, SVGElementInstance* parentInstance)
{
	ASSERT(0);
	return NULL;
#if 0

	CComPtr<ILSVGElement> svgElement;
	parentInstance->get_correspondingElement(&svgElement);

	CComQIPtr<ILDOMEventTarget> eventTarget = parentInstance;

	PSVGElement* pClone = (PSVGElement*)pParent->m_pView->CreateElement(svgElement);

	pClone->m_eventTarget = eventTarget;
	pClone->m_parent = pParent;
	ASSERT(0);
#if 0
	pClone->GetCSSProperties();
#endif

	CComPtr<ILSVGElementInstance> elementInstance;
	parentInstance->get_firstChild(&elementInstance);

	while (elementInstance != NULL)
	{
		PSVGElement* pClone2 = CloneInstanceTree(pClone, elementInstance);
		if (pClone2)
		{
			pClone->m_childList.AddTail(pClone2);
			pClone->m_childListRender.AddTail(pClone2);
		}

		CComPtr<ILSVGElementInstance> nextSibling;
		elementInstance->get_nextSibling(&nextSibling);
		elementInstance = nextSibling;
	}

	pClone->CalculateBoundsAndChildren();	// This calculates children first

	return pClone;
#endif
}

/////////////////////////////////////////////////////////////////////
// CPSVGUseElement

/*
void CPSVGUseElement::FinalRelease()
{
	if (m_pInstanceRoot)
	{
		((ILViewNode*)m_pInstanceRoot)->Release();
		m_pInstanceRoot = NULL;
	}
}
*/

//virtual
gm::Matrix3d* PSVGUseElement::GetLocalAnimatedMatrix()
{
	SVGUseElement* psvgElement = static_cast<SVGUseElement*>(m_pNode);
	gm::Matrix3d* matrix = psvgElement->transform_attr()->m_animVal->consolidateToMatrix();

//	pMatrix->m_matrix = /*gmMatrix3::translate(m_computedX, m_computedY) **/ pMatrix->m_matrix;

	matrix = *matrix * *m_animateMotionMatrix;

	return matrix;
}

// virtual
gm::RectD PSVGUseElement::GetScreenBBox()
{
	gm::RectD bbox;
	PSVGElement::GetScreenBBoxFromBounds(m_bounds, &bbox);

	return bbox;
}

//virtual
void PSVGUseElement::CalculateBounds()
{
	ASSERT(0);
#if 0
	PSVGElement::FreeCachedBitmap();

	SVGUseElement* psvgElement = static_cast<SVGUseElement*>(m_pNode);

	gmMatrix3 matrix = psvgElement->m_transform->m_animated->m_animVal->m_value->consolidate();//GetLocalAnimatedMatrix();

	m_bounds.X = m_bounds.Y = m_bounds.Width = m_bounds.Height = 0;
	m_filterRect.X = m_filterRect.Y = m_filterRect.Width = m_filterRect.Height = 0;
	m_expandedBBox.X = m_expandedBBox.Y = m_expandedBBox.Width = m_expandedBBox.Height = 0;

	if (m_pInstanceRoot == NULL)
	{
		/*
		_bstr_t href = psvgElement->m_href->m_animated->m_animVal->m_value;
		if (href.length())
		{
			BSTR id = &((BSTR)href)[1];

			PSVGElement* pReferencedElement = (PSVGElement*)m_pWindow->m_htmTree->GetElementById(id);

			if (pReferencedElement)
			{
				m_pInstanceRoot = CloneRenderTree(this, pReferencedElement);
			}
		}
		*/

		CComPtr<ILSVGElementInstance> instance;
		psvgElement->get_animatedInstanceRoot(&instance);

		m_pInstanceRoot = CloneInstanceTree(this, instance);
	}

	if (m_pInstanceRoot)
	{
		PSVGElement* pViewportElement = GetViewportElement();
		ASSERT(pViewportElement);

		LDraw::RectD viewBox = pViewportElement->GetViewBox();

		CLSVGLength* xLength = psvgElement->m_x->m_animated->m_animVal->m_value;
		CLSVGLength* yLength = psvgElement->m_y->m_animated->m_animVal->m_value;
		CLSVGLength* widthLength = psvgElement->m_width->m_animated->m_animVal->m_value;
		CLSVGLength* heightLength = psvgElement->m_height->m_animated->m_animVal->m_value;

		if (xLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
			m_computedX = (xLength->m_valueInSpecifiedUnits * viewBox.Width)/100;
		else
			m_computedX = xLength->m_value;

		if (yLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
			m_computedY = (yLength->m_valueInSpecifiedUnits * viewBox.Height)/100;
		else
			m_computedY = yLength->m_value;

		CComQIPtr<ILSVGSymbolElement> symbolElement = m_pInstanceRoot->m_pNode;
		if (symbolElement)
		{
			if (psvgElement->m_width->m_specified)
			{
				if (widthLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
					m_computedWidth = (widthLength->m_valueInSpecifiedUnits * viewBox.Width)/100;
				else
					m_computedWidth = widthLength->m_value;
			}
			else	// 100%
			{
				m_computedWidth = viewBox.Width;
			}

			if (psvgElement->m_height->m_specified)
			{
				if (heightLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
					m_computedHeight = (heightLength->m_valueInSpecifiedUnits * viewBox.Height)/100;
				else
					m_computedHeight = heightLength->m_value;
			}
			else	// 100%
			{
				m_computedHeight = viewBox.Height;
			}

		//	CLSVGSymbolElement* psymbolElement = static_cast<CLSVGSymbolElement*>(symbolElement.p);

		//	RectD viewPort = RectD(m_computedX, m_computedY, m_computedWidth, m_computedHeight);
		//	gmMatrix3 mat = GetViewBoxMatrix(psymbolElement->m_viewBox->m_animated->m_animVal, psymbolElement->m_preserveAspectRatio->m_animated->m_animVal, viewPort);

		}
	// TODO referencing svg element
		else
		{
			// width/height on <use> is ignored (as far as I can tell from the spec)
			m_computedWidth = m_pInstanceRoot->m_xbounds.Width;
			m_computedHeight = m_pInstanceRoot->m_xbounds.Height;
		}

		m_bounds.X = m_computedX;
		m_bounds.Y = m_computedY;
		m_bounds.Width = m_computedWidth;
		m_bounds.Height = m_computedHeight;

		// TODO? Can this be improved?
		GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

		GetFillUriElement();
		GetStrokeUriElement();
		GetFilterElement();
		GetMaskElement();
		GetClipPathElement();

		if (m_pFilterElement)
		{
			m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
		}
		else
		{
			m_filterRect.X = m_bounds.X;
			m_filterRect.Y = m_bounds.Y;
			m_filterRect.Width = m_bounds.Width;
			m_filterRect.Height = m_bounds.Height;
		}

		m_expandedBBox = m_filterRect;

		CalculateScale(matrix);
	}
#endif
}

//virtual
void PSVGUseElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	ASSERT(0);
#if 0
	SVGUseElement* pElement = static_cast<SVGUseElement*>(m_pNode);

//	LDraw::Matrix oldmat;
//	pGraphics->GetTransform(&oldmat);

	if (m_pInstanceRoot)
	{
		LDraw::GraphicsState state = pGraphics->Save();

		Matrix mat;

		CComQIPtr<ILSVGSymbolElement> symbolElement = m_pInstanceRoot->m_pNode;
		if (symbolElement)
		{
			CLSVGSymbolElement* psymbolElement = static_cast<CLSVGSymbolElement*>(symbolElement.p);

			RectD viewBox(m_computedX, m_computedY, m_computedWidth, m_computedHeight);

			RectD viewPort = RectD(
				psymbolElement->m_viewBox->m_animated->m_animVal->m_value->m_x,
				psymbolElement->m_viewBox->m_animated->m_animVal->m_value->m_y,
				psymbolElement->m_viewBox->m_animated->m_animVal->m_value->m_width,
				psymbolElement->m_viewBox->m_animated->m_animVal->m_value->m_height);

			//RectD viewPort = RectD(m_computedX, m_computedY, m_computedWidth, m_computedHeight);

			RectD rect = GetViewBoxRect(
				viewBox,
				psymbolElement->m_preserveAspectRatio->m_animated->m_animVal->m_value,
				viewPort);

			//mat = gmMatrix3::identity();
			mat = gmMatrix3::translate(-viewPort.X, -viewPort.Y);
			mat *= gmMatrix3::scale(rect.Width/viewPort.Width, rect.Height/viewPort.Height);
			mat *= gmMatrix3::translate(rect.X, rect.Y);

		//	mat = ::GetViewBoxMatrix(rect, viewPort);
		}
		else
		{
			mat = gmMatrix3::identity();
		}

	//	mat = mat * gmMatrix3::translate(m_computedX, m_computedY);

		/*
		LDraw::Matrix matrix(
			(float)mat[0][0], (float)mat[0][1],
			(float)mat[1][0], (float)mat[1][1],
			(float)mat[2][0], (float)mat[2][1]);

		pGraphics->MultiplyTransform(&matrix);
		*/
		LDraw::Matrix gdipMatrix;
		mat.GetGdipMatrix(gdipMatrix);

		pGraphics->MultiplyTransform(&gdipMatrix);

		gmMatrix3 oldMatrixToView = pC->m_matrixToView;
		pC->m_matrixToView = mat * pC->m_matrixToView;

		if (m_pInstanceRoot)
		{
	//		pGraphics->TranslateTransform(-m_pInstanceRoot->m_bounds.X, -m_pInstanceRoot->m_bounds.Y);

			if (symbolElement)
				m_pInstanceRoot->RenderChildren(pC, pGraphics, scaleX, scaleY);
			else
				m_pInstanceRoot->Render(pC, pGraphics, scaleX, scaleY);
		}

		pC->m_matrixToView = oldMatrixToView;
		pGraphics->Restore(state);
	}

//	pGraphics->SetTransform(&oldmat);
#endif
}

// virtual
PSVGElement* PSVGUseElement::HitTestElement(gm::Matrix3d* matrix, gm::PointD pt)
{
	if (m_pInstanceRoot)
	{
		return m_pInstanceRoot->HitTestElement(matrix, pt);
	}

	return NULL;
}

}	// w3c
}
