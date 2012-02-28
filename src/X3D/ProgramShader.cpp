#include "stdafx.h"
#include "X3D2.h"
#include "ProgramShader.h"
#include "ShaderProgram.h"

//#include <d3d11shader.h>

namespace System
{
namespace x3d
{

NodeType* ProgramShader::nodeType(GetNodeType());

NodeType* ProgramShader::GetNodeType()
{
	static X3DFieldDefinition programs("programs", FieldType_MFNode, SAIFieldAccess_inputOutput, offsetof(ProgramShader, m_programs));

	static X3DFieldDefinition* fields[] =
	{
		&programs,
	};

	static NodeType nodeType("ProgramShader", typeid(ProgramShader), fields, _countof(fields), X3DShaderNode::GetNodeType());
	return &nodeType;
}

ProgramShader::ProgramShader() : X3DShaderNode(GetNodeType())
{
}

bool ProgramShader::CreateShader(Graphics::RenderTarget* p3D)
{
	String language = getLanguage();

	/*
	if (wcsncmp(language->c_str(), "CG-", 3) == 0)
	{
	}
	else
		*/
	{
		for (unsigned int i = 0; i < m_programs->get_size(); ++i)
		{
			X3DNode* node = m_programs->get1Value(i);
			ShaderProgram* program = dynamic_cast<ShaderProgram*>(node);
			if (program)
			{
				bool created = program->CreateShader(getLanguage(), p3D);

				if (created)
				{
					if (program->m_shaderType == ShaderType_Vertex)
					{
						m_vertexShader = program;

						ASSERT(0);
#if 0
						ID3D10Blob* pInputSignature;
						HRESULT hr = D3D10GetInputSignatureBlob(m_vertexShader->m_shaderBlob->GetBufferPointer(), m_vertexShader->m_shaderBlob->GetBufferSize(), &pInputSignature);
						if (SUCCEEDED(hr))
						{
							D3D11_INPUT_ELEMENT_DESC layout[] =
							{
								{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
								{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
								{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
							};

							hr = p3D->m_d3d10->m_device->CreateInputLayout(layout, _countof(layout), pInputSignature->GetBufferPointer(), pInputSignature->GetBufferSize(), &m_inputLayout);

						//	hr = p3D->m_d3d10->m_device->CreateInputLayout(inputDesc, shaderDesc.InputParameters, pShader->GetBufferPointer(), pShader->GetBufferSize(), &m_inputLayout); 
							ASSERT(SUCCEEDED(hr));
						}
#endif
					}
					else if (program->m_shaderType == ShaderType_Fragment)
					{
						m_fragmentShader = program;
					}
					else if (program->m_shaderType == ShaderType_Geometry)
					{
						m_geometryShader = program;
					}
					else
						ASSERT(0);
				}

			//	return true;
			}
				/*
				if (created)
				{
					// isSelected=true
				//	program->Change
					i++;
					for (; i < m_programs->get_size(); i++)
					{
						X3DNode* node = m_programs->get1Value(i);
						ShaderProgram* program = dynamic_cast<ShaderProgram*>(node);
						if (program)
						{
					// isSelected=false
						}
					}

					return true;
				}
				else
				{
					// isSelected=false
				}
				*/
		}

		return true;
	}
}

void ProgramShader::Begin(X3DDrawContext* p3DX, UINT* nPasses)
{
	*nPasses = 1;
}

void ProgramShader::SetModelMatrix(const float* v)
{
	if (m_vertexShader->m_model.m_nbuffer != -1)
		*(D3DXMATRIX*)(m_vertexShader->m_buffers[m_vertexShader->m_model.m_nbuffer] + m_vertexShader->m_model.m_offset) = *(D3DXMATRIX*)v;
}

void ProgramShader::SetViewMatrix(const float* v)
{
	if (m_vertexShader->m_view.m_nbuffer != -1)
		*(D3DXMATRIX*)(m_vertexShader->m_buffers[m_vertexShader->m_view.m_nbuffer] + m_vertexShader->m_view.m_offset) = *(D3DXMATRIX*)v;
}

void ProgramShader::SetProjectionMatrix(const float* v)
{
	if (m_vertexShader->m_projection.m_nbuffer != -1)
		*(D3DXMATRIX*)(m_vertexShader->m_buffers[m_vertexShader->m_projection.m_nbuffer] + m_vertexShader->m_projection.m_offset) = *(D3DXMATRIX*)v;
}

void ProgramShader::SetModelViewMatrix(const float* v)
{
	if (m_vertexShader->m_modelView.m_nbuffer != -1)
		*(D3DXMATRIX*)(m_vertexShader->m_buffers[m_vertexShader->m_modelView.m_nbuffer] + m_vertexShader->m_modelView.m_offset) = *(D3DXMATRIX*)v;
}

void ProgramShader::SetModelViewProjectionMatrix(const float* v)
{
	if (m_vertexShader->m_modelViewProjection.m_nbuffer != -1)
		*(D3DXMATRIX*)(m_vertexShader->m_bufferData[m_vertexShader->m_modelViewProjection.m_nbuffer] + m_vertexShader->m_modelViewProjection.m_offset) = *(D3DXMATRIX*)v;
}

void ProgramShader::End(X3DDrawContext* p3DX)
{
}

void ProgramShader::BeginPass(X3DDrawContext* p3DX, UINT nPass)
{
	if (nPass != 0)
	{
		raise(Exception("Invalid pass"));
	}

	Graphics::Direct3D10_I* pD10 = p3DX->m_renderContext->GetRT()->m_d3d10;

	pD10->m_device1->VSSetConstantBuffers(0, m_vertexShader->m_buffers.size(), m_vertexShader->m_buffers.GetData());
	pD10->m_device1->VSSetShader(m_vertexShader->m_hlsl_10_Shader.vertex);

	pD10->m_device1->GSSetShader(nullptr);//pshader->m_geometryShader->m_hlsl_10_Shader.vertex);

	pD10->m_device1->PSSetConstantBuffers(0, m_fragmentShader->m_buffers.size(), m_fragmentShader->m_buffers.GetData());
	pD10->m_device1->PSSetShader(m_fragmentShader->m_hlsl_10_Shader.pixel);

	D3D10_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D10_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	samplerDesc.AddressU = D3D10_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D10_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D10_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.ComparisonFunc = D3D10_COMPARISON_NEVER;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = FLT_MAX;
	samplerDesc.MipLODBias = 0.0f;

	ID3D10SamplerState* samplerState;
	pD10->m_device->CreateSamplerState(&samplerDesc, &samplerState);

	pD10->m_device1->PSSetSamplers(0, 1, &samplerState);


//	pD10->m_device->IASetInputLayout(m_inputLayout);
	/*
	for (unsigned int i = 0; i < m_programs->get_size(); ++i)
	{
		X3DNode* node = m_programs->get1Value(i);
		ShaderProgram* program = dynamic_cast<ShaderProgram*>(node);
		if (program)
		{
			program->Apply(p3DX);
		}
	}
	*/
}

void ProgramShader::EndPass(X3DDrawContext* p3DX)
{
	for (unsigned int i = 0; i < m_programs->get_size(); ++i)
	{
		X3DNode* node = m_programs->get1Value(i);
		ShaderProgram* program = dynamic_cast<ShaderProgram*>(node);
		if (program)
		{
			program->End(p3DX);
		}
	}
}

}	// x3d
}	// System
