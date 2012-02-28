#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFlowTextElement.h"
#include "SVGFlowTextElement.h"

#include "PSVGMaskElement.h"
#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{
//void DrawPathSegList(ILSVGPathSegList* seglist, LDraw::GraphicsPath* path, ILSVGMatrix* matrix);
//void GetPathSegListBBox(ILSVGPathSegList* seglist, const gmMatrix3& matrix, FlowTextD* bbox);

//virtual
gm::Matrix3d* PSVGFlowTextElement::GetLocalAnimatedMatrix()
{
	SVGFlowTextElement* psvgElement = static_cast<SVGFlowTextElement*>(m_pNode);

	gm::Matrix3d* matrix = psvgElement->m_transform->m_animVal->consolidateToMatrix();
	matrix = *matrix * *m_animateMotionMatrix;

	return matrix;
}

//virtual
gm::RectD PSVGFlowTextElement::GetScreenBBox()
{
	SVGFlowTextElement* psvgElement = static_cast<SVGFlowTextElement*>(m_pNode);

	gm::RectD bbox;

	ASSERT(0);
#if 0

	gmMatrix3 matrix = m_pWindow->svgGetScreenCTM(this);	// TODO?: Should be GetScreenCTM2() ?
#if 0
	bbox = CalcRoundFlowTextBBox(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy, matrix);
#endif
#endif
		//PSVGElement::GetScreenBBox(seglist, &bbox);

	return bbox;
}

//virtual
void PSVGFlowTextElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	SVGFlowTextElement* psvgElement = static_cast<SVGFlowTextElement*>(m_pNode);

	gm::Matrix3d* matrix = GetLocalAnimatedMatrix();

	m_bounds = CalculateRenderableChildrenBoundingBox();
	gm::GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	gm::RectD viewBox = pViewportElement->GetViewBox();

// Text layout is performed as normal, on one infinitely long line

	TextLayoutContext tlc;	// curpos,initialpos are set to 0,0

	LayoutText(&tlc, true, true);

	tlc.AlignChunk(this);

	PSVGElement* pFlowRegion = (PSVGElement*)GetElementByTagNameNS(WSTR("http://www.w3.org/2000/svg"), WSTR("flowRegion"));

	double linetop = 0;
	double linebottom = 0;

#if 0
	TransformGlyphs();
#endif
}

//virtual
void PSVGFlowTextElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
//	CLSVGFlowTextElement* psvgElement = static_cast<CLSVGFlowTextElement*>(m_pNode);

	RenderTextChildren(pC, pBitmap, renderContext, scaleX, scaleY, bOffscreen);

	RenderChildren(pC, renderContext, scaleX, scaleY);
}

//virtual
bool PSVGFlowTextElement::HitTest(double x, double y, int pointerEvents)
{
	bool bOver = false;

	return bOver;
}

}	// Web
}	// System
