#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFESpecularLightingElement.h"
#include "SVGFESpecularLightingElement.h"

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

/*
#define SPECULAR
#define NAME PSVGFESpecularLightingElement
#include "PSVGFELightingElementImpl.h"
*/

namespace System
{
namespace Web
{

unsigned int SVGSpecularLightingEffect::GetInputCount()
{
	return 1;
}

Gui::IEffect* SVGSpecularLightingEffect::GetInput(unsigned int index)
{
	if (index != 0)
	{
		throw new ArgumentOutOfRangeException();
	}
	return m_input;
}

void SVGSpecularLightingEffect::SetInput(unsigned int index, Gui::IEffect* input)
{
	if (index != 0)
	{
		throw new ArgumentOutOfRangeException();
	}
	m_input = input;
}

void SVGSpecularLightingEffect::Render(Gui::RenderContext* renderContext, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection)
{
	if (m_input->GetOutputNormalMap() == NULL)
	{
		ASSERT(0);
//		m_input->RenderOutputNormalMap(pGraphics);
	}

	Graphics::Bitmap* normalMap = m_input->GetOutputNormalMap();

#if 0
	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device);

	D3DXHANDLE technique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("RenderSpecularLighting");

	D3DXHANDLE surfaceScaleVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "surfaceScale");
	D3DXHANDLE specularConstantVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "specularConstant");
	D3DXHANDLE specularExponentVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "specularExponent");
	D3DXHANDLE lightPositionVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "lightPosition");
	D3DXHANDLE lightColorVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "lightColor");

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));

	pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, normalMap->m_texture.u.d3d);

	pGraphics->m_res->m_d3d9_effect->SetFloat(surfaceScaleVariable, m_surfaceScale);
	pGraphics->m_res->m_d3d9_effect->SetFloat(specularConstantVariable, m_specularConstant);
	pGraphics->m_res->m_d3d9_effect->SetFloat(specularExponentVariable, m_specularExponent);
	pGraphics->m_res->m_d3d9_effect->SetVector(lightPositionVariable, (D3DXVECTOR4*)&m_lightPosition);
	pGraphics->m_res->m_d3d9_effect->SetVector(lightColorVariable, (D3DXVECTOR4*)&m_lightColor);

	pGraphics->m_res->m_d3d9_effect->SetTechnique(technique);

	DrawBitmap(pGraphics, destRect);
#endif
}

////////

PSVGFESpecularLightingElement::PSVGFESpecularLightingElement(SVGFESpecularLightingElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFESpecularLightingElement::GetInCount()
{
	return 1;
}

Gui::CEffect* PSVGFESpecularLightingElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* input[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	SVGFESpecularLightingElement* psvgElement = static_cast<SVGFESpecularLightingElement*>(m_pNode);

	/*
	double specularConstant = psvgElement->m_specularConstant->m_animated->m_animVal->m_value->m_value;
	double specularExponent = psvgElement->m_specularExponent->m_animated->m_animVal->m_value->m_value;
	double surfaceScale = psvgElement->m_surfaceScale->m_animated->m_animVal->m_value->m_value;
*/
	double specularConstant = psvgElement->get_specularConstant()->get_animVal();
	double specularExponent = psvgElement->get_specularExponent()->get_animVal();
	double surfaceScale = psvgElement->get_surfaceScale()->get_animVal();

	int lighttype;	// 0=distance,1=point,2=spot

	PSVGFEPointLightElement* pfePoint = (PSVGFEPointLightElement*)GetElementByTagNameNS(WSTR("http://www.w3.org/2000/svg"), WSTR("fePointLight"), false);
	PSVGElement* pfeDistant = (PSVGElement*)GetElementByTagNameNS(WSTR("http://www.w3.org/2000/svg"), WSTR("feDistantLight"), false);
	PSVGElement* pfeSpot = (PSVGElement*)GetElementByTagNameNS(WSTR("http://www.w3.org/2000/svg"), WSTR("feSpotLight"), false);
	if (pfeDistant)
	{
		lighttype = 0;
	}
	else if (pfePoint)
	{
		lighttype = 1;
	}
	else if (pfeSpot)
	{
		lighttype = 2;
	}
	else
		return NULL;

	gm::vector3f lightColor;
	lightColor[0] = MAX(0, MIN(255, m_computedLightingColor.m_rgbColor[0]))/255.0;
	lightColor[1] = MAX(0, MIN(255, m_computedLightingColor.m_rgbColor[1]))/255.0;
	lightColor[2] = MAX(0, MIN(255, m_computedLightingColor.m_rgbColor[2]))/255.0;

	gm::vector3f S;	// Spot light

	gm::vector3f lightLocation;
	if (lighttype == 1)	// Point
	{
		SVGFEPointLightElement* psvgfePoint = static_cast<SVGFEPointLightElement*>(pfePoint->m_pNode);
/*
		lightLocation[0] = psvgfePoint->m_x->m_animated->m_animVal->m_value->m_value;
		lightLocation[1] = psvgfePoint->m_y->m_animated->m_animVal->m_value->m_value;
		lightLocation[2] = psvgfePoint->m_z->m_animated->m_animVal->m_value->m_value;
*/
		lightLocation[0] = psvgfePoint->get_x()->get_animVal();
		lightLocation[1] = psvgfePoint->get_y()->get_animVal();
		lightLocation[2] = psvgfePoint->get_z()->get_animVal();
	}
	else
		ASSERT(0);

	if (m_effect == NULL)
	{
		m_effect = new SVGSpecularLightingEffect;
	}

	SVGSpecularLightingEffect* pEffect = static_cast<SVGSpecularLightingEffect*>(m_effect);
	pEffect->m_outImage = NULL;
	pEffect->m_outNormalMap = NULL;

	pEffect->m_input = input[0];
	pEffect->m_lightPosition = gm::vector4f(lightLocation, 0);
	pEffect->m_lightColor = gm::vector4f(lightColor, 1);
	pEffect->m_specularConstant = specularConstant;
	pEffect->m_specularExponent = specularExponent;
	pEffect->m_surfaceScale = surfaceScale;

	return pEffect;
}

}	// w3c
}
