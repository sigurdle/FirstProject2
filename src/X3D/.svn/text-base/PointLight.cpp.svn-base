#include "stdafx.h"
#include "X3D2.h"
#include "PointLight.h"

namespace System
{
namespace x3d
{

void DrawAxis(X3DDrawContext* pDC)
{
	Gui::Media3D::Lines2 lines;

	float scale = 1.0f;

	Vec3f vertices[] =
	{
		Vec3f(0,0,0), Vec3f(scale, 0, 0),
		Vec3f(0,0,0), Vec3f(0, scale, 0),
		Vec3f(0,0,0), Vec3f(0, 0, scale),
	};

	Vec3f colors[] =
	{
		Vec3f(1, 0, 0),
		Vec3f(0, 1, 0),
		Vec3f(0, 0, 1),
	};

	lines.Create(pDC->m_renderContext, vertices, _countof(vertices), colors, false);

//	Gui::Media3D::CylinderShape cylinder;
//	cylinder.Create(pDC->m_renderContext, 1, 0, 2);

//	ID3D10DepthStencilState* depthStencilState; UINT stencilRef;
//	pDC->m_renderContext->GetRT()->m_d3d10->m_device->OMGetDepthStencilState(&depthStencilState, &stencilRef);

//	pDC->m_renderContext->GetRT()->m_d3d10->m_device->OMSetDepthStencilState(GL::Direct10::s.m_pDepthStencilState[false], 0/*stencilRef*/);
	
	lines.Draw(pDC->m_renderContext);
//	cylinder.Draw(pDC->m_renderContext);
}

IMP_X3DFIELD1(PointLight, SFVec3f, attenuation, inputOutput, Vec3f(1,0,0))
IMP_X3DFIELD1(PointLight, SFVec3f, location, inputOutput, Vec3f(0,0,0))
IMP_X3DFIELD3(PointLight, SFFloat, radius, inputOutput, 100.0f, 0.0f, FLT_MAX)

NodeType* PointLight::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_attenuationFieldDef(),
		get_locationFieldDef(),
		get_radiusFieldDef(),
	};

	static NodeType nodeType(WSTR("PointLight"), typeid(PointLight), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* PointLight::nodeType(GetNodeType());

PointLight::PointLight() : X3DLightNode(GetNodeType(), true),
	m_attenuation(new SFVec3f(get_attenuationFieldDef(), this)),
	m_location(new SFVec3f(get_locationFieldDef(), this)),
	m_radius(new SFFloat(get_radiusFieldDef(), this))
{
}

void PointLight::DrawOverlay(X3DDrawContext* pDC)
{
	// TODO: not here
	if (m_selected)
	{
		pDC->m_renderContext->PushModelView(pDC->m_renderContext->modelViewMatrix() * MatrixTranslation(getLocation()));

		DrawAxis(pDC);

		pDC->m_renderContext->PopMatrix();
	//	pDC->m_renderContext->GetRT()->m_d3d10->m_device->OMSetDepthStencilState(depthStencilState, stencilRef);
	}
}

int PointLight::HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest)
{
	D3DXVECTOR3 location(m_location->getValue());
//	D3DXVECTOR4 v;

//	D3DXVec3Transform(&v, &location, &modelView);

	D3DXVECTOR3 out;
	D3DXVec3Project(&out, &location, &vp, &projection, &view, &model);

	if (fabs(mousepos[0]-out.x) < 3 &&
		fabs(mousepos[1]-out.y) < 3)
	{
		hitTest->OnHit(this, type, *(Vec3f*)&out);
		return 1;
	}

	return 0;
}

void PointLight::SetLight(X3DDrawContext* pDC)
{
//	m_radius->m_value;

	D3DXMATRIX modelView = pDC->m_renderContext->modelViewMatrix();

	D3DXVECTOR3 location(m_location->getValue());
	D3DXVECTOR4 v;

	D3DXVec3Transform(&v, &location, &modelView);

	float ambientIntensity = getAmbientIntensity();
	float intensity = getIntensity();
	Vec3f color = getColor();
	Vec3f attenuation = getAttenuation();

	Graphics::Light light;
	light.m_type = 2;
	light.m_ambient = Vec4f(ambientIntensity, ambientIntensity, ambientIntensity, 1.0f);
	light.m_diffuse = Vec4f(color[0]*intensity, color[1]*intensity, color[2]*intensity, 1.0f);
	light.m_position = Vec4f(v.x, v.y, v.z, 1/*positional*/);
	light.m_constant_attenuation = attenuation[0];
	light.m_linear_attenuation = attenuation[1];
	light.m_quadratic_attenuation = attenuation[2];

	pDC->m_renderContext->m_lights.push_back(light);

	++pDC->m_renderContext->m_nLight;

#if 0
	pDC->m_pGraphics3D->PushMatrix();
//	glTranslated(0, 0, 100);

	float light_position[4];
	m_location->getValue(light_position);
	light_position[3] = 1;	// positional
	float ambient[4] = {m_ambientIntensity->m_value, m_ambientIntensity->m_value, m_ambientIntensity->m_value, 1.0};
	float diffuse_specular[4] = {m_color->m_value[0], m_color->m_value[1], m_color->m_value[2], m_intensity->m_value};

	pDC->m_pGraphics3D->Enable(GL_LIGHT0+pDC->m_nLight);
	pDC->m_pGraphics3D->Lightfv(GL_LIGHT0+pDC->m_nLight, GL_POSITION, light_position);
	pDC->m_pGraphics3D->Lightfv(GL_LIGHT0+pDC->m_nLight, GL_AMBIENT, ambient);
	pDC->m_pGraphics3D->Lightfv(GL_LIGHT0+pDC->m_nLight, GL_DIFFUSE, diffuse_specular);
//	pDC->m_pGraphics3D->glLightfv(GL_LIGHT0+pDC->m_nLight, GL_SPECULAR , diffuse_specular);

	pDC->m_pGraphics3D->Lightf(GL_LIGHT0+pDC->m_nLight, GL_CONSTANT_ATTENUATION, m_attenuation->m_value[0]);
	pDC->m_pGraphics3D->Lightf(GL_LIGHT0+pDC->m_nLight, GL_LINEAR_ATTENUATION, m_attenuation->m_value[1]);
	pDC->m_pGraphics3D->Lightf(GL_LIGHT0+pDC->m_nLight, GL_QUADRATIC_ATTENUATION, m_attenuation->m_value[2]);

	pDC->m_pGraphics3D->PopMatrix();
#endif
}

void PointLight::DrawGlobalLights(X3DDrawContext* pDC)
{
	if (getGlobal() && getOn())
	{
		SetLight(pDC);
	}
}

void PointLight::PreDraw(X3DDrawContext* pDC)
{
	if (!getGlobal() && getOn())
	{
		SetLight(pDC);
	}
}

}	// x3d
}
