#include "stdafx.h"
#include "X3D2.h"
#include "Material2D.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(Material2D, SFColor, emissiveColor, inputOutput, Vec3f(0.8f, 0.8f, 0.8f))
IMP_X3DFIELD1(Material2D, SFBool, filled, inputOutput, false)
//IMP_X3DFIELD0(Material2D, SFNode, lineProps, inputOutput)
IMP_X3DFIELD3(Material2D, SFFloat, transparency, inputOutput, 0, 0, 1)

// static
NodeType* Material2D::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_emissiveColorFieldDef(),
		get_filledFieldDef(),
//		get_linePropsFieldDef(),
		get_transparencyFieldDef(),
	};

	static NodeType nodeType(WSTR("Material2D"), typeid(Material2D), fields, _countof(fields), X3DMaterialNode::GetNodeType());
	return &nodeType;
}

Material2D::Material2D() : X3DMaterialNode(GetNodeType())
{
// Set default values
	m_emissiveColor->m_value[0] = 0.8f; m_emissiveColor->m_value[1] = 0.8f; m_emissiveColor->m_value[2] = 0.8f;
	m_transparency->m_value = 0.0f;
}

int Material2D::ApplyMaterial(X3DDrawContext* pDC)
{
	ASSERT(0);
#if 0
	//SFFloat* ambientIntensity = static_cast<SFFloat*>(m_ambientIntensity->m_value);
	//SFColor* diffuseColor = static_cast<SFColor*>(m_diffuseColor->m_value);
	//SFFloat* shininess = static_cast<SFFloat*>(m_shininess->m_value);
	//SFColor* specularColor = static_cast<SFColor*>(m_specularColor->m_value);
	//SFFloat* transparency = static_cast<SFFloat*>(m_transparency->m_value);

//		GLfloat MatAmb[] = { ambientIntensity->m_v, ambientIntensity->m_v, ambientIntensity->m_v, 1.0};	// ??
//		GLfloat MatDiff[] = { diffuseColor->m_v[0], diffuseColor->m_v[1], diffuseColor->m_v[2], 1.0};
	float MatEmiss[] =
	{ m_emissiveColor->m_value[0], m_emissiveColor->m_value[1], m_emissiveColor->m_value[2],
		1-m_transparency->getValue()};
//		GLfloat MatSpec[] = { specularColor->m_v[0], specularColor->m_v[1], specularColor->m_v[2], 1.0};

//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmb);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiff);

	if (pDC->m_pGraphics2D)
	{
		pDC->m_pBrush = new LDraw::SolidBrush(LDraw::Color(m_emissiveColor->m_value[0]*255, m_emissiveColor->m_value[1]*255, m_emissiveColor->m_value[2]*255));
		return 0;
	}

#if 0
	pDC->m_pGraphics3D->glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, MatEmiss);
#endif
	pDC->m_pGraphics3D->glColorf(m_emissiveColor->m_value[0], m_emissiveColor->m_value[1], m_emissiveColor->m_value[2], 1-m_transparency->getValue());
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);

//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess->m_v*128);	// ??

	pDC->Color(LDraw::vector4f(m_emissiveColor->m_value[0], m_emissiveColor->m_value[1], m_emissiveColor->m_value[2], 1-m_transparency->getValue()));

	/*
	if (m_transparency->m_value > 0)
	{
		pDC->m_pGraphics3D->glDepthMask(false);
	//	pDC->m_pGraphics3D->glDisable(GL_DEPTH_TEST);
		pDC->m_pGraphics3D->glEnable(GL_BLEND);
		pDC->m_pGraphics3D->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	*/
#endif
	return 0;
}

}	// x3d
}	// System
