#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGSolidColorElement.h"
//#include "SVGSolidColorElement.h"

namespace System
{
namespace Web
{

PSVGSolidColorElement::PSVGSolidColorElement(SVGElement* element) : PSVGElement(element)
{
}

//virtual
LDraw::Brush* PSVGSolidColorElement::CreateBrush(PSVGElement* pReferencingElement, double scaleX, double scaleY)
{
// TODO, iccColors etc.
	LDraw::SolidBrush* pBrush = new LDraw::SolidBrush(LDraw::Color(
		(uint8)MAX(0, MIN(255, m_computedSolidOpacity*255)),
		m_computedSolidColor.m_rgbColor[0],
		m_computedSolidColor.m_rgbColor[1],
		m_computedSolidColor.m_rgbColor[2]));

	return pBrush;
}

}	// w3c
}
