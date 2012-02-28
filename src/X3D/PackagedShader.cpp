#include "stdafx.h"
#include "X3D2.h"
#include "PackagedShader.h"

#include "PointLight.h"
#include "DirectionalLight.h"

#include <d3d9.h>
#include <D3dx9math.h>

#pragma comment(lib, "D3dx9.lib")

namespace System
{
namespace x3d
{

NodeType* PackagedShader::nodeType(GetNodeType());

NodeType* PackagedShader::GetNodeType()
{
	static X3DFieldDefinition url("url", FieldType_MFURL, SAIFieldAccess_inputOutput, offsetof(PackagedShader, m_url));

	static X3DFieldDefinition* PackagedShaderFields[] =
	{
		&url,

		/*
		SFBool    [in]     activate
		SFNode    [in,out] metadata   NULL [X3DMetadataObject]
		MFString  [in,out] url        []   [URI]
		SFBool    [out]    isSelected
		SFBool    [out]    isValid
		SFString  []       language   ""

		# And any number of:
		fieldType [in]     fieldName
		fieldType [in,out] fieldName initialValue
		fieldType [out]    fieldName
		fieldType []       fieldName initialValue
		*/
	};

	static NodeType nodeType(WSTR("PackagedShader"), typeid(PackagedShader), PackagedShaderFields, _countof(PackagedShaderFields));
	return &nodeType;
}

PackagedShader::PackagedShader() : X3DShaderNode(GetNodeType())
{
}

bool PackagedShader::CreateShader(Graphics::RenderTarget* p3D)
{
	if (m_language->getValue() == L"HLSL")
	{
		ASSERT(0);
#if 0
		IDirect3DDevice9* d3dDevice = p3D->m_pGraphics->m_device->GetD3D9Device();
		if (d3dDevice == NULL)
			return false;

		if (m_effect == NULL)
		{
			CStringw filename(m_url->m_items[0].string);

	//		ID3DXEffectCompiler* effectCompiler = NULL;
			ID3DXBuffer* parseErrors = NULL;

			HRESULT hr;
		//	hr = D3DXCreateEffectCompilerFromFileW(filename, NULL, NULL, 0, &effectCompiler, &parseErrors);
			ID3DXEffectPool* pool = NULL;
			hr = D3DXCreateEffectFromFileW(d3dDevice, filename.c_str(), NULL, NULL, 0, pool, &m_effect, &parseErrors);
			if (FAILED(hr))
			{
				if (parseErrors)
				{
					char* str = (char*)parseErrors->GetBufferPointer();

					parseErrors->Release();
				}

				return false;
			}
		}
#endif
		return true;
	}
	else if (m_language->getValue() == L"HLSL_10")
	{
		if (m_effect == NULL)
		{
			CStringw filename(m_url->get1Value(0)/*.string*/);

			UINT dwShaderFlags = 0;
			ComPtr<ID3D10Blob> errors;
			HRESULT hr = D3DX10CreateEffectFromFileW(filename.c_str(), nullptr, nullptr, "fx_5_0", dwShaderFlags, 0, p3D->m_d3d10->m_device, nullptr,
																	 nullptr, &m_d3d10_effect, &errors, nullptr);
			if (FAILED(hr))
			{
				if (errors)
				{
					const char* str = (const char*)errors->GetBufferPointer();

					return false;
				}
			}

			m_model = m_d3d10_effect->GetVariableByName("model")->AsMatrix();
			m_view = m_d3d10_effect->GetVariableByName("view")->AsMatrix();
			m_projection = m_d3d10_effect->GetVariableByName("projection")->AsMatrix();
			m_modelView = m_d3d10_effect->GetVariableByName("modelView")->AsMatrix();
			m_modelViewProjection = m_d3d10_effect->GetVariableByName("modelViewProjection")->AsMatrix();

			m_modelI = m_d3d10_effect->GetVariableByName("modelI")->AsMatrix();
			m_viewI = m_d3d10_effect->GetVariableByName("viewI")->AsMatrix();
			m_projectionI = m_d3d10_effect->GetVariableByName("projectionI")->AsMatrix();
			m_modelViewI = m_d3d10_effect->GetVariableByName("modelViewI")->AsMatrix();
			m_modelViewProjectionI = m_d3d10_effect->GetVariableByName("modelViewProjectionI")->AsMatrix();

			m_modelT = m_d3d10_effect->GetVariableByName("modelT")->AsMatrix();
			m_viewT = m_d3d10_effect->GetVariableByName("viewT")->AsMatrix();
			m_projectionT = m_d3d10_effect->GetVariableByName("projectionT")->AsMatrix();
			m_modelViewT = m_d3d10_effect->GetVariableByName("modelViewT")->AsMatrix();
			m_modelViewProjectionT = m_d3d10_effect->GetVariableByName("modelViewProjectionT")->AsMatrix();
		}

		return true;
	}

	return false;
}

void PackagedShader::Begin(X3DDrawContext* p3DX, UINT* nPasses)
{
	if (m_effect)
	{
	//	IDirect3DDevice9* d3dDevice = p3D->GetDirect3DDevice9();
	//	VERIFY(d3dDevice);

		HRESULT hr;

		//hr = m_effect->SetTechnique("RenderScene");

		hr = m_effect->SetMatrix("model", (D3DXMATRIX*)(float*)p3DX->m_model);
		hr = m_effect->SetMatrix("view", (D3DXMATRIX*)(float*)p3DX->m_view);
		hr = m_effect->SetMatrix("projection", (D3DXMATRIX*)(float*)p3DX->m_projection);
		hr = m_effect->SetMatrix("modelView", (D3DXMATRIX*)(float*)p3DX->m_modelView);
		hr = m_effect->SetMatrix("modelViewProjection", (D3DXMATRIX*)(float*)p3DX->m_modelViewProjection);

		hr = m_effect->SetMatrix("modelI", (D3DXMATRIX*)(float*)p3DX->m_modelI);
		hr = m_effect->SetMatrix("viewI", (D3DXMATRIX*)(float*)p3DX->m_viewI);
		hr = m_effect->SetMatrix("projectionI", (D3DXMATRIX*)(float*)p3DX->m_projectionI);
		hr = m_effect->SetMatrix("modelViewI", (D3DXMATRIX*)(float*)p3DX->m_modelViewI);
		hr = m_effect->SetMatrix("modelViewProjectionI", (D3DXMATRIX*)(float*)p3DX->m_modelViewProjectionI);

		hr = m_effect->SetMatrix("modelT", (D3DXMATRIX*)(float*)p3DX->m_modelT);
		hr = m_effect->SetMatrix("viewT", (D3DXMATRIX*)(float*)p3DX->m_viewT);
		hr = m_effect->SetMatrix("projectionT", (D3DXMATRIX*)(float*)p3DX->m_projectionT);
		hr = m_effect->SetMatrix("modelViewT", (D3DXMATRIX*)(float*)p3DX->m_modelViewT);
		hr = m_effect->SetMatrix("modelViewProjectionT", (D3DXMATRIX*)(float*)p3DX->m_modelViewProjectionT);

		hr = m_effect->SetMatrix("modelIT", (D3DXMATRIX*)(float*)p3DX->m_modelIT);
		hr = m_effect->SetMatrix("viewIT", (D3DXMATRIX*)(float*)p3DX->m_viewIT);
		hr = m_effect->SetMatrix("projectionIT", (D3DXMATRIX*)(float*)p3DX->m_projectionIT);
		hr = m_effect->SetMatrix("modelViewIT", (D3DXMATRIX*)(float*)p3DX->m_modelViewIT);
		hr = m_effect->SetMatrix("modelViewProjectionIT", (D3DXMATRIX*)(float*)p3DX->m_modelViewProjectionIT);

		for (uint i = 0; i < m_addfields.size(); ++i)
		{
			X3DField* field = m_addfields[i];

			CString param(field->getFieldName());

			switch (field->getFieldType())
			{
				case FieldType_SFBool:
				{
					SFBool* sf = static_cast<SFBool*>(field);

					hr = m_effect->SetBool(param, sf->getValue());
				}
				break;

				case FieldType_SFFloat:
				{
					SFFloat* sf = static_cast<SFFloat*>(field);

					hr = m_effect->SetFloat(param, sf->getValue());
				}
				break;

				case FieldType_SFVec2f:
				{
					SFVec2f* sfvec2f = static_cast<SFVec2f*>(field);

					hr = m_effect->SetFloatArray(param, sfvec2f->getValue(), 2);
				}
				break;

				case FieldType_SFVec3f:
				{
					SFVec3f* sfvec3f = static_cast<SFVec3f*>(field);

					hr = m_effect->SetFloatArray(param, sfvec3f->getValue(), 3);
				}
				break;

				case FieldType_SFColor:
				{
					SFColor* sfcolor = static_cast<SFColor*>(field);

					hr = m_effect->SetFloatArray(param, sfcolor->getValue(), 3);
				}
				break;

				case FieldType_SFColorRGBA:
				{
					SFColorRGBA* sfcolor = static_cast<SFColorRGBA*>(field);

					hr = m_effect->SetFloatArray(param, sfcolor->getValue(), 4);
				}
				break;

				case FieldType_MFFloat:
				{
					MFFloat* mf = static_cast<MFFloat*>(field);

					hr = m_effect->SetFloatArray(param, mf->m_items.begin(), mf->m_items.size());
				}
				break;

				case FieldType_SFNode:
				{
					SFNode* sf = static_cast<SFNode*>(field);

					X3DNode* node = sf->getValue();

					if (X3DLightNode* lightNode = dynamic_cast<X3DLightNode*>(node))
					{
						float3 color = lightNode->getColor();
						float intensity = lightNode->getIntensity();
						float ambientIntensity = lightNode->getAmbientIntensity();

						X3DLight light;
						light.diffuseColor = float4(color[0]*intensity, color[1]*intensity, color[2]*intensity, 1);
						light.specularColor = float4(0,0,0,1);
						light.ambientColor = float4(ambientIntensity, ambientIntensity, ambientIntensity, 1);

						if (PointLight* pointLight = dynamic_cast<PointLight*>(lightNode))
						{
							light.type = 1;
							light.position = pointLight->getLocation();
						}
						else if (DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(lightNode))
						{
							light.type = 3;
							light.direction = directionalLight->getDirection();
						}
						else
							VERIFY(0);

						light.on = lightNode->getOn();

						hr = m_effect->SetValue(param, &light, sizeof(X3DLight));
					}
					else if (X3DMaterialNode* materialNode = dynamic_cast<X3DMaterialNode*>(node))
					{
					}

					//	hr = m_effect->SetFloatArray(param, mf->m_items.begin(), mf->m_items.size());
				}
				break;

				case FieldType_MFNode:
				{
					MFNode* mf = static_cast<MFNode*>(field);

					for (unsigned int i = 0; i < mf->get_size(); i++)
					{
						X3DNode* node = mf->get1Value(i);

#if 0
						if (X3DLightNode* lightNode = dynamic_cast<X3DLightNode*>(node))
						{
							float3 color = lightNode->getColor();
							float intensity = lightNode->getIntensity();
							float ambientIntensity = lightNode->getAmbientIntensity();

							X3DLight light;
							light.diffuseColor = float4(color[0]*intensity, color[1]*intensity, color[2]*intensity, 1);
							light.specularColor = float4(0,0,0,1);
							light.ambientColor = float4(ambientIntensity, ambientIntensity, ambientIntensity, 1);

							if (PointLight* pointLight = dynamic_cast<PointLight*>(lightNode))
							{
								light.type = 1;
								light.position = pointLight->getLocation();
							}
							else if (DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(lightNode))
							{
								light.type = 3;
								light.direction = directionalLight->getDirection();
							}
							else
								VERIFY(0);

							light.on = lightNode->getOn();

							hr = m_effect->SetValue(param, &light, sizeof(X3DLight));
						}
						else if (X3DMaterialNode* materialNode = dynamic_cast<X3DMaterialNode*>(node))
						{
						}
#endif
					}

					//	hr = m_effect->SetFloatArray(param, mf->m_items.begin(), mf->m_items.size());
				}
				break;

			default:
				ASSERT(0);
			}
		}
	
		hr = m_effect->Begin(nPasses, 0);
		ASSERT(SUCCEEDED(hr));
	}
	else if (m_d3d10_effect)
	{
		HRESULT hr;

		hr = m_model->SetMatrix((float*)p3DX->m_model);
		hr = m_view->SetMatrix((float*)p3DX->m_view);
		hr = m_projection->SetMatrix((float*)p3DX->m_projection);
		hr = m_modelView->SetMatrix((float*)p3DX->m_modelView);
		hr = m_modelViewProjection->SetMatrix((float*)p3DX->m_modelViewProjection);

		hr = m_modelI->SetMatrix((float*)p3DX->m_modelI);
		hr = m_viewI->SetMatrix((float*)p3DX->m_viewI);
		hr = m_projectionI->SetMatrix((float*)p3DX->m_projectionI);
		hr = m_modelViewI->SetMatrix((float*)p3DX->m_modelViewI);
		hr = m_modelViewProjectionI->SetMatrix((float*)p3DX->m_modelViewProjectionI);
	}
}

void PackagedShader::End(X3DDrawContext* p3DX)
{
	if (m_effect)
	{
		HRESULT hr = m_effect->End();
		ASSERT(SUCCEEDED(hr));
	}
	else
	{
	}
}

void PackagedShader::BeginPass(X3DDrawContext* p3DX, UINT nPass)
{
	if (m_effect)
	{
		HRESULT hr = m_effect->BeginPass(nPass);
		ASSERT(SUCCEEDED(hr));
	}
}

void PackagedShader::EndPass(X3DDrawContext* p3DX)
{
	if (m_effect)
	{
		HRESULT hr = m_effect->EndPass();
		ASSERT(SUCCEEDED(hr));
	}
}

}	// x3d
}
