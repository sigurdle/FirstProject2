#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEOffsetElement.h"
#include "SVGFEOffsetElement.h"

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

namespace System
{
namespace Web
{

PSVGFEOffsetElement::PSVGFEOffsetElement(SVGFEOffsetElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEOffsetElement::GetInCount()
{
	return 1;
}

//virtual
Gui::CEffect* PSVGFEOffsetElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inEffect[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	SVGFEOffsetElement* psvgElement = static_cast<SVGFEOffsetElement*>(m_pNode);

//	LDraw::Bitmap* inImage = inImage[0]->m_outImage;

	double dx = psvgElement->get_dx()->get_animVal();
	double dy = psvgElement->get_dy()->get_animVal();

	SVGOffsetEffect* pEffect = new SVGOffsetEffect;

	pEffect->m_inEffect = inEffect[0];
	pEffect->m_dx = (float)dx;
	pEffect->m_dy = (float)dy;
#if 0
	pEffect->m_technique = pO->m_res->m_d3d9_effect->GetTechniqueByName("RenderLinearGradient");
	ASSERT(pEffect->m_technique);
#endif

	m_effect = pEffect;
	return pEffect;
#if 0
	UI::Graphics out(new LDraw::GraphicsO(outImage));

	out.DrawImage(inImage, (float)(dx*scaleX), (float)(dy*scaleY));
#endif

	return 0;
}

}	// w3c
}
