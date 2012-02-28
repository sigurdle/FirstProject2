#include "stdafx.h"
#include "LSVG.h"

#include "PSVGFEFloodElement.h"
#include "SVGFEFloodElement.h"

namespace System
{
namespace Web
{

SVGFloodEffect::SVGFloodEffect()
{
}

unsigned int SVGFloodEffect::GetInputCount()
{
	return 0;
}

Gui::IEffect* SVGFloodEffect::GetInput(unsigned int index)
{
	throw std::exception("Index out of bounds");
	return NULL;
}

void SVGFloodEffect::SetInput(unsigned int index, Gui::IEffect* input)
{
	throw std::exception("Index out of bounds");
}

void SVGFloodEffect::Render(Gui::RenderContext* renderContext, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection)
{
	//LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device);

//	D3DCOLOR color = D3DCOLOR_RGBA(m_color[0], m_color[1], m_color[2], m_color[3]);
//	pD3D9->m_d3dDevice->Fill(color);
}

gm::vector4f SVGFloodEffect::get_Color()
{
	return m_color;
}

void SVGFloodEffect::set_Color(gm::vector4f color)
{
	m_color = color;
}

///////////////////////////////////////

PSVGFEFloodElement::PSVGFEFloodElement(SVGFEFloodElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEFloodElement::GetInCount()
{
	return 0;
}

//virtual
Gui::CEffect* PSVGFEFloodElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	SVGFEFloodElement* psvgElement = static_cast<SVGFEFloodElement*>(m_pNode);

	SVGFloodEffect* pEffect = new SVGFloodEffect;

	/*
	float alpha = MAX(0, MIN(1, m_computedFloodOpacity));
	float red = MAX(0, MIN(1, m_computedFloodColor.m_rgbColor[0]/255.0));
	float green = MAX(0, MIN(1, m_computedFloodColor.m_rgbColor[1]/255.0));
	float blue = MAX(0, MIN(1, m_computedFloodColor.m_rgbColor[2]/255.0));
	*/

	float alpha = m_computedFloodOpacity;
	float red = m_computedFloodColor.m_rgbColor[0]/255.0;
	float green = m_computedFloodColor.m_rgbColor[1]/255.0;
	float blue = m_computedFloodColor.m_rgbColor[2]/255.0;

	pEffect->set_Color(gm::vector4f(red, green, blue, alpha));

	return pEffect;

#if 0
	UI::Graphics graphics(new LDraw::GraphicsO(outImage));

	uint8 alpha = (uint8)(MAX(0, MIN(1, m_computedFloodOpacity))*255);
	uint8 red = (uint8)MAX(0, MIN(255, m_computedFloodColor.m_rgbColor[0]));
	uint8 green = (uint8)MAX(0, MIN(255, m_computedFloodColor.m_rgbColor[1]));
	uint8 blue = (uint8)MAX(0, MIN(255, m_computedFloodColor.m_rgbColor[2]));

	LDraw::SolidBrush brush(LDraw::Color(alpha, red, green, blue));

//	graphics.SetCompositingMode(LDraw::CompositingModeSourceCopy);

	graphics.FillRectangle(&brush, uRect);
#endif
	return 0;
}

}	// Web
}
