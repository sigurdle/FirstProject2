#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFlowRegionElement.h"
//#include "LSVGFlowRegionElement.h"
#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{

//virtual
gm::Matrix3d* CPSVGFlowRegionElement::GetLocalAnimatedMatrix()
{
#if 0
	/*
	CComQIPtr<ILSVGFlowRegionElement> g = m_pNode;
	if (g)
	{
		CLSVGFlowRegionElement* pElement = static_cast<CLSVGFlowRegionElement*>(m_pNode);
		return pElement->m_transform->m_animated->m_animVal->m_value->consolidate();
	}
	else	// seq or par ?
	{
		/*
		CComObject<CLSVGMatrix>* p;
		CComObject<CLSVGMatrix>::CreateInstance(&p);
		p->AddRef();
	// identity matrix

		return p;
		*/
#endif
	return gm::Matrix3d::GetIdentity();
	//}
}

// virtual
bool CPSVGFlowRegionElement::NeedOffscreenBitmap()
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
gm::RectD CPSVGFlowRegionElement::GetScreenBBox()
{
//	CLSVGFlowRegionElement* psvgElement = static_cast<CLSVGFlowRegionElement*>(m_pNode);

//	CComPtr<ILSVGMatrix> m;
//	psvgElement->getScreenCTM(&m);

	gm::RectD bbox;
	PSVGElement::GetScreenBBoxFromBounds(m_bounds, &bbox);

//	GetTransformRectBoundingBox(static_cast<CLSVGMatrix*>(m.p)->m_matrix, &m_bounds, &bbox);

	return bbox;
}

//virtual
void CPSVGFlowRegionElement::CalculateBounds()
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
void CPSVGFlowRegionElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

	RenderChildren(pC, renderContext, scaleX, scaleY);

	PSVGElement::Render4(pC, pBitmap, renderContext, scaleX, scaleY, bOffscreen, bDrawBehaviors);
}

}	// Web
}	// System
