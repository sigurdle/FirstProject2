#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

Lines2::Lines2()
{
	m_d3d10_VertexBuffer = NULL;
}

Lines2::~Lines2()
{
	if (m_d3d10_VertexBuffer)
	{
//		m_d3d10_VertexBuffer->Release();
	}

	/*
	if (m_inputLayout)
	{
		m_inputLayout->Release();
	}
	*/
}

bool Lines2::IsValid(ImmediateRenderContext* renderContext)
{
	return m_d3d10_VertexBuffer != NULL;
}

void Lines2::Create(RenderContext* renderContext, gm::vector3f* points, uint nvertices, gm::vector4f color)
{
	m_nvertices = nvertices;

	VERTEX_XYZ_COLOR* vertices = (VERTEX_XYZ_COLOR*)_malloca(nvertices*sizeof(VERTEX_XYZ_COLOR));
	VERTEX_XYZ_COLOR* pvertex = vertices;

	gm::vector3f* ppoint = points;

	for (uint i = 0; i < nvertices; i += 1)
	{
		pvertex->position = *ppoint;
		pvertex->color = color;
		++pvertex;
		++ppoint;
	}

	ASSERT(m_d3d10_VertexBuffer == NULL);
	{
		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = nvertices*sizeof(VERTEX_XYZ_COLOR);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer);
	}

	/*
	if (m_inputLayout == NULL)
	{
		// Define the input layout
		D3D10_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },  
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },  
		};

		m_d3d10_technique = renderContext->GetRT()->m_d3d10->m_d3d10_effect->GetTechniqueByName("SolidColorTechnique");

		// Create the input layout
		D3D10_PASS_DESC PassDesc;
		m_d3d10_technique->GetPassByIndex(0)->GetDesc(&PassDesc);
		HRESULT hr = renderContext->GetRT()->m_d3d10->m_device->CreateInputLayout(layout, _countof(layout), PassDesc.pIAInputSignature, 
				PassDesc.IAInputSignatureSize, &m_inputLayout);
		ASSERT(SUCCEEDED(hr));
	}
	*/

	_freea(vertices);
}

void Lines2::Create(RenderContext* renderContext, gm::vector3f* points, uint nvertices, gm::vector3f* colors, bool colorPerVertex)
{
	m_nvertices = nvertices;

	VERTEX_XYZ_COLOR* vertices = (VERTEX_XYZ_COLOR*)_malloca(nvertices*sizeof(VERTEX_XYZ_COLOR));
	VERTEX_XYZ_COLOR* pvertex = vertices;

	gm::vector3f* ppoint = points;
	gm::vector3f* pcolor = colors;

	if (colorPerVertex)
	{
		for (uint i = 0; i < nvertices; i += 1)
		{
			pvertex->position = *ppoint;
			pvertex->color = *pcolor;
			++pvertex;
			++ppoint;

			++pcolor;
		}
	}
	else
	{
		for (uint i = 0; i < nvertices; i += 2)
		{
			pvertex->position = *ppoint;
			pvertex->color = *pcolor;
			++pvertex;
			++ppoint;

			pvertex->position = *ppoint;
			pvertex->color = *pcolor;
			++pvertex;
			++ppoint;

			++pcolor;
		}
	}

	ASSERT(m_d3d10_VertexBuffer == NULL);
	{
		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = nvertices*sizeof(VERTEX_XYZ_COLOR);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer);
	}

	/*
	if (m_inputLayout == NULL)
	{
		// Define the input layout
		D3D10_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },  
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },  
		};

		m_d3d10_technique = renderContext->GetRT()->m_d3d10->m_d3d10_effect->GetTechniqueByName("SolidColorTechnique");

		// Create the input layout
		D3D10_PASS_DESC PassDesc;
		m_d3d10_technique->GetPassByIndex(0)->GetDesc(&PassDesc);
		HRESULT hr = renderContext->GetRT()->m_d3d10->m_device->CreateInputLayout(layout, _countof(layout), PassDesc.pIAInputSignature, 
				PassDesc.IAInputSignatureSize, &m_inputLayout);
		ASSERT(SUCCEEDED(hr));
	}
	*/

	_freea(vertices);
}

void Lines2::Draw(ImmediateRenderContext* renderContext)
{
	UINT stride[1] = { sizeof(VERTEX_XYZ_COLOR)};
	UINT offset[1] = { 0 };
	renderContext->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 1, &m_d3d10_VertexBuffer, stride, offset);
	renderContext->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
	renderContext->GetRT()->m_d3d10->m_device->IASetInputLayout(renderContext->GetRT()->m_d3d10->m_solidColorInputLayout);

	renderContext->GetRT()->m_d3d10->m_d3d10_modelViewVariable->SetMatrix(renderContext->modelViewMatrix());
	renderContext->GetRT()->m_d3d10->m_d3d10_projectionVariable->SetMatrix(renderContext->projectionMatrix());
	renderContext->GetRT()->m_d3d10->m_d3d10_modelViewProjectionVariable->SetMatrix(renderContext->modelViewProjectionMatrix());

	renderContext->GetRT()->m_d3d10->m_solidColorTechnique->GetPassByIndex(0)->Apply(0);

	renderContext->GetRT()->m_d3d10->m_device->Draw(m_nvertices, 0);
}

}
}
}
