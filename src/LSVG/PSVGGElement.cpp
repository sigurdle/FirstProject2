#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGGElement.h"
#include "SVGGElement.h"

namespace System
{
namespace Web
{

PSVGGElement::PSVGGElement(SVGGElement* element) : PSVGTransformableElement(element)
{
}

#if 0
//virtual
LDraw::Matrix3d* PSVGGElement::GetLocalAnimatedMatrix()
{
	ASSERT(0);
	return LDraw::Matrix3d::GetIdentity();
#if 0
	CComQIPtr<ILSVGGElement> g = m_pNode;
	if (g)
	{
		SVGGElement* pElement = static_cast<SVGGElement*>(m_pNode);
		return pElement->m_transform->m_animated->m_animVal->m_value->consolidate();
	}
	else	// seq or par ?
	{
		/*
		CComObject<SVGMatrix>* p;
		CComObject<SVGMatrix>::CreateInstance(&p);
		p->AddRef();
	// identity matrix

		return p;
		*/
		return gmMatrix3::identity();
	}
#endif
}
#endif

// virtual
bool PSVGGElement::NeedOffscreenBitmap()
{
//	return FALSE;

	if (PSVGElement::NeedOffscreenBitmap())
		return true;

	if (m_computedOpacity < 1)
		return true;

	/*
// If any of the children have partial opacity, this group must
// create an offscreen bitmap
// unless this groups opacity is 1
	UPOSITION pos = m_childListRender.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)m_childListRender.GetNext(pos);

		if (pElement->m_computedOpacity > 0 && pElement->m_computedOpacity < 1)
			return TRUE;
	}
	*/

	return false;
}

//virtual
gm::RectD PSVGGElement::GetScreenBBox()
{
	SVGGElement* psvgElement = static_cast<SVGGElement*>(m_pNode);

//	CComPtr<ILSVGMatrix> m;
//	psvgElement->getScreenCTM(&m);

	gm::RectD bbox;
	PSVGElement::GetScreenBBoxFromBounds(m_bounds, &bbox);

//	GetTransformRectBoundingBox(static_cast<SVGMatrix*>(m.p)->m_matrix, &m_bounds, &bbox);

	return bbox;
}

//virtual
void PSVGGElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	gm::Matrix3d* matrix = GetLocalAnimatedMatrix();

	m_bounds = CalculateRenderableChildrenBoundingBox();
	gm::GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

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
		m_filterRect = CalculateRenderableChildrenFilterRect();
	}

	m_expandedBBox = m_filterRect;

	CalculateScale(matrix);
}

//virtual
void PSVGGElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

	RenderChildren(pC, renderContext, scaleX, scaleY);

//	PSVGElement::Render4(pC, pBitmap, renderContext, scaleX, scaleY, bOffscreen, bDrawBehaviors);
}

}	// Web
}	// System
