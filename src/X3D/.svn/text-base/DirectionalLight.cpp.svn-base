#include "stdafx.h"
#include "X3D2.h"
#include "DirectionalLight.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(DirectionalLight, SFVec3f, direction, inputOutput, Vec3f(0.0f, 0.0f ,-1.0f))

NodeType* DirectionalLight::GetNodeType()
{
	static X3DFieldDefinition* DirectionalLightFields[] =
	{
		get_directionFieldDef(),
		/*
		SFFloat [in,out] ambientIntensity 0      [0,1]
		SFColor [in,out] color            1 1 1  [0,1]
		SFVec3f [in,out] direction        0 0 -1 (-8,8)
		SFBool  [in,out] global           FALSE
		SFFloat [in,out] intensity        1      [0,1]
		SFBool  [in,out] on               TRUE
		*/
	};

	static NodeType nodeType(WSTR("DirectionalLight"), typeid(DirectionalLight), DirectionalLightFields, _countof(DirectionalLightFields), X3DLightNode::GetNodeType());
	return &nodeType;
}

NodeType* DirectionalLight::nodeType(GetNodeType());

DirectionalLight::DirectionalLight() : X3DLightNode(GetNodeType(), false),
	m_direction(new SFVec3f(get_directionFieldDef(), this))
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetLight(X3DDrawContext* pDC)
{
#if 0
	float light_position[4];
	light_position[0] = -m_direction->m_value[0];
	light_position[1] = -m_direction->m_value[1];
	light_position[2] = -m_direction->m_value[2];
	light_position[3] = 0;	// directional

	float ambient[4] = {m_ambientIntensity->m_value, m_ambientIntensity->m_value, m_ambientIntensity->m_value, 1.0};
	float diffuse[4] = {m_color->m_value[0], m_color->m_value[1], m_color->m_value[2], m_intensity->m_value};
	float specular[4] = {1,1,1,1};

	pDC->m_pGraphics3D->Enable(GL_LIGHT0+pDC->m_nLight);
	pDC->m_pGraphics3D->Lightfv(GL_LIGHT0+pDC->m_nLight, GL_POSITION, light_position);
	pDC->m_pGraphics3D->Lightfv(GL_LIGHT0+pDC->m_nLight, GL_AMBIENT, ambient);
	pDC->m_pGraphics3D->Lightfv(GL_LIGHT0+pDC->m_nLight, GL_DIFFUSE, diffuse);
	pDC->m_pGraphics3D->Lightfv(GL_LIGHT0+pDC->m_nLight, GL_SPECULAR, specular);
#endif

	float ambientIntensity = getAmbientIntensity();
	float intensity = getIntensity();
	Vec3f color = getColor();

	Graphics::Light light;
	light.m_ambient = gm::vector4f(ambientIntensity, ambientIntensity, ambientIntensity, 1.0f);
	light.m_diffuse = gm::vector4f(color[0]*intensity, color[1]*intensity, color[2]*intensity, 1.0f);
	light.m_type = 1;
//	light.
//	light.m_position = LDraw::vector4f(m_location->getValue(), 1/*positional*/);

	pDC->m_renderContext->m_lights.push_back(light);

//	pDC->m_pGraphics3D->glPopMatrix();

	pDC->m_renderContext->m_nLight++;
}

void DirectionalLight::DrawGlobalLights(X3DDrawContext* pDC)
{
	if (getGlobal() && getOn())
	{
		SetLight(pDC);
	}
}

void DirectionalLight::PreDraw(X3DDrawContext* pDC)
{
	if (!getGlobal() && getOn())
	{
		SetLight(pDC);
	}
}

}	// x3d
}	// System
