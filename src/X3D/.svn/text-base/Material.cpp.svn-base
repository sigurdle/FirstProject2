#include "stdafx.h"
#include "X3D2.h"
#include "Material.h"

namespace System
{
namespace x3d
{

//extern ID3D10EffectVariable* m_d3d10_materialVariable;

NodeType* Material::nodeType(GetNodeType());

TypedX3DFieldDefinition<SFFloat>* Material::get_ambientIntensityFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> ambientIntensity("ambientIntensity", SAIFieldAccess_inputOutput, offsetof(Material, m_ambientIntensity), 0.2f, 0, 1);
	return &ambientIntensity;
}

TypedX3DFieldDefinition<SFColor>* Material::get_diffuseColorFieldDef()
{
	static TypedX3DFieldDefinition<SFColor> diffuseColor("diffuseColor", SAIFieldAccess_inputOutput, offsetof(Material, m_diffuseColor), Vec3f(0.8f, 0.8f, 0.8f));
	return &diffuseColor;
}

TypedX3DFieldDefinition<SFColor>* Material::get_emissiveColorFieldDef()
{
	static TypedX3DFieldDefinition<SFColor> emissiveColor("emissiveColor", SAIFieldAccess_inputOutput, offsetof(Material, m_emissiveColor), Vec3f(0, 0, 0));
	return &emissiveColor;
}

TypedX3DFieldDefinition<SFFloat>* Material::get_shininessFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> shininess("shininess", SAIFieldAccess_inputOutput, offsetof(Material, m_shininess), 0.2f, 0, 1);
	return &shininess;
}

TypedX3DFieldDefinition<SFColor>* Material::get_specularColorFieldDef()
{
	static TypedX3DFieldDefinition<SFColor> specularColor("specularColor", SAIFieldAccess_inputOutput, offsetof(Material, m_specularColor), Vec3f(0,0,0));
	return &specularColor;
}

TypedX3DFieldDefinition<SFFloat>* Material::get_transparencyFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> transparency("transparency", SAIFieldAccess_inputOutput, offsetof(Material, m_transparency), 0, 0, 1);
	return &transparency;
}

NodeType* Material::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_ambientIntensityFieldDef(),
		get_diffuseColorFieldDef(),
		get_emissiveColorFieldDef(),
		get_shininessFieldDef(),
		get_specularColorFieldDef(),
		get_transparencyFieldDef(),
		/*
		SFFloat [in,out] ambientIntensity 0.2         [0,1]
		SFColor [in,out] diffuseColor     0.8 0.8 0.8 [0,1]
		SFColor [in,out] emissiveColor    0 0 0       [0,1]
		SFFloat [in,out] shininess        0.2         [0,1]
		SFColor [in,out] specularColor    0 0 0       [0,1]
		SFFloat [in,out] transparency     0           [0,1]
		 */
	};

	static NodeType nodeType("Material", typeid(Material), fields, _countof(fields), X3DMaterialNode::GetNodeType());
	return &nodeType;
}

Material::Material() : X3DMaterialNode(GetNodeType()),

	m_ambientIntensity(new SFFloat(get_ambientIntensityFieldDef(), this)),
	m_diffuseColor(new SFColor(get_diffuseColorFieldDef(), this)),
	m_emissiveColor(new SFColor(get_emissiveColorFieldDef(), this)),
	m_shininess(new SFFloat(get_shininessFieldDef(), this)),
	m_specularColor(new SFColor(get_specularColorFieldDef(), this)),
	m_transparency(new SFFloat(get_transparencyFieldDef(), this))
{
}

Vec3f Material::getDiffuseColor()
{
	return m_diffuseColor->getValue();
}

void Material::setDiffuseColor(Vec3f value)
{
	m_diffuseColor->setValue(value);
}

Vec3f Material::getSpecularColor()
{
	return m_specularColor->m_value;
}

void Material::setSpecularColor(Vec3f value)
{
	m_specularColor->setValue(value);
}

Vec3f Material::getEmissiveColor()
{
	return m_emissiveColor->m_value;
}

float Material::getShininess()
{
	return m_shininess->m_value;
}

float Material::getTransparency()
{
	return m_transparency->m_value;
}

float Material::getAmbientIntensity()
{
	return m_ambientIntensity->m_value;
}

int Material::ApplyMaterial(X3DDrawContext* pDC)
{
	Graphics::Direct3D10_I* pD10 = pDC->m_renderContext->GetRT()->m_d3d10;
	Graphics::OpenGL_I* pGL = pDC->m_renderContext->GetRT()->m_opengl;

	if (pD10)
	{
		X3DMaterial material;
		memset(&material, 0, sizeof(material));
		material.diffuseColor = Vec4f(getDiffuseColor(), 1);
	//	material.ambientColor = Vec4f(getDiffuseColor(), 1);
		HRESULT hr = pD10->m_d3d10_materialVariable->SetRawValue(&material, 0, sizeof(X3DMaterial));
		ASSERT(SUCCEEDED(hr));
	}
	else
	{
		ASSERT(0);
	}

#if 0
	/*
	SFFloat* ambientIntensity = static_cast<SFFloat*>(m_ambientIntensity);
	SFColor* diffuseColor = static_cast<SFColor*>(m_diffuseColor);
	SFColor* emissiveColor = static_cast<SFColor*>(m_emissiveColor);
	SFFloat* shininess = static_cast<SFFloat*>(m_shininess);
	SFColor* specularColor = static_cast<SFColor*>(m_specularColor);
	SFFloat* transparency = static_cast<SFFloat*>(m_transparency);
	*/

	float MatEmiss[4] = { m_emissiveColor->m_value[0], m_emissiveColor->m_value[1], m_emissiveColor->m_value[2], 0};
	float MatAmb[4] = { m_diffuseColor->m_value[0] * m_ambientIntensity->m_value, m_diffuseColor->m_value[1] * m_ambientIntensity->m_value, m_diffuseColor->m_value[2] * m_ambientIntensity->m_value, 0};	// ??
	float MatDiff[4] = { m_diffuseColor->m_value[0], m_diffuseColor->m_value[1], m_diffuseColor->m_value[2], 1-m_transparency->m_value};
	float MatSpec[4] = { m_specularColor->m_value[0], m_specularColor->m_value[1], m_specularColor->m_value[2], 0};

	pDC->m_pGraphics3D->Materialfv(GL_FRONT_AND_BACK, GL_EMISSION, MatEmiss);
	pDC->m_pGraphics3D->Materialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmb);
	pDC->m_pGraphics3D->Materialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiff);
	pDC->m_pGraphics3D->Materialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);

	pDC->m_pGraphics3D->Materialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess->m_value*128);

	if (m_transparency->m_value > 0)
	{
		pDC->m_pGraphics3D->Disable(GL_DEPTH_TEST);
		pDC->m_pGraphics3D->Enable(GL_BLEND);
		pDC->m_pGraphics3D->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
#endif

	return 1;
}

}	// x3d
}	// System
