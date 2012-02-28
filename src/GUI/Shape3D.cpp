#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

IMP_DEPENDENCY_PROPERTY1(Geometry3D*, Shape3D, Geometry, nullptr, new PropertyMetadata(true));
IMP_DEPENDENCY_PROPERTY1(Material*, Shape3D, Material, nullptr, new PropertyMetadata(true));

DependencyClass* Shape3D::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_GeometryProperty(),
		get_MaterialProperty(),
	};

	return &depclass;
}

DependencyClass* Shape3D::pClass(get_Class());

Shape3D::Shape3D() : Visual3D(get_Class())
{
}

struct X3DLight
{
	__declspec(align(16)) int type;
	__declspec(align(16)) float4 diffuseColor;
	__declspec(align(16)) float4 specularColor;
	__declspec(align(16)) float4 ambientColor;
	__declspec(align(16)) float3 position;
	__declspec(align(16)) float3 direction;
	float range;
	float falloff;
	float attenuation0;
	float attenuation1;
	float attenuation2;
	float theta;
	float phi;
	bool on;
};

void Shape3D::Render(ManagedRenderContext renderContext)
{
	ImmediateRenderContext* imm = dynamic_cast<ImmediateRenderContext*>(renderContext.m_p);

	Graphics::Direct3D10_I* d3d10 = renderContext.m_p->GetRT()->m_d3d10;
	if (d3d10)
	{
		d3d10->Load2();
	}

	d3d10->m_d3d10_modelViewVariable->SetMatrix(imm->modelViewMatrix());
	d3d10->m_d3d10_projectionVariable->SetMatrix(imm->projectionMatrix());
	d3d10->m_d3d10_modelViewProjectionVariable->SetMatrix(imm->modelViewProjectionMatrix());
	d3d10->m_d3d10_modelViewITVariable->SetMatrix(imm->modelViewITMatrix());

	if (true)
	{
		uint nlights = imm->m_lights.size();
		nlights = __min(nlights, 256);
		X3DLight lights[256];

		d3d10->m_d3d10_nlightsVariable->SetInt(nlights);

		for (uint i = 0; i < nlights; ++i)
		{
		//	char name[256];
		//	sprintf_s(name, "lights[%d]", i);

			lights[i].type = (int)imm->m_lights[i].m_position[3];

			lights[i].position[0] = imm->m_lights[i].m_position[0];
			lights[i].position[1] = imm->m_lights[i].m_position[1];
			lights[i].position[2] = imm->m_lights[i].m_position[2];

			lights[i].direction[0] = imm->m_lights[i].m_position[0];
			lights[i].direction[1] = imm->m_lights[i].m_position[1];
			lights[i].direction[2] = imm->m_lights[i].m_position[2];

			lights[i].diffuseColor = imm->m_lights[i].m_diffuse;
			lights[i].ambientColor = imm->m_lights[i].m_ambient;

			lights[i].attenuation0 = imm->m_lights[i].m_constant_attenuation;
			lights[i].attenuation1 = imm->m_lights[i].m_linear_attenuation;
			lights[i].attenuation2 = imm->m_lights[i].m_quadratic_attenuation;
		}

		d3d10->m_d3d10_lightsVariable->SetRawValue(lights, 0, sizeof(X3DLight)*nlights);
	}

//	ID3D10EffectTechnique* tech = d3d10->m_d3d10_effect->GetTechniqueByName("HeightMapTechnique");

	ID3DX10EffectTechnique* tech = d3d10->m_phongLightTechnique;

	d3d10->m_device->IASetInputLayout(d3d10->m_phongLightInputLayout);

	D3DX10_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);

	Material* pMaterial = get_Material();
	if (pMaterial)
	{
		pMaterial->Apply(renderContext.m_p);
	}

	Geometry3D* pGeometry = get_Geometry();
	if (pGeometry)
	{
		if (false)
		{
			HeightMap* p = dynamic_cast<HeightMap*>(pGeometry);
			d3d10->m_d3d10_HeightMapTexture->SetResource(p->m_bitmap->m_d3d10_shaderResourceView);
		}

		for (uint nPass = 0; nPass < techDesc.Passes; ++nPass)
		{
			tech->GetPassByIndex(nPass)->Apply(0);
			pGeometry->Render(renderContext);
		}
	}
}

}	// Media3D
}	// Gui
}	// System
