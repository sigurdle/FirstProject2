#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

IMAGEEDITEXT void ReloadEffect()
{
	MaskOutlineVisual::m_effect = NULL;
}

Gui::DependencyClass* MaskOutlineVisual::get_Class()
{
	static Gui::DependencyClass Class(typeid(MaskOutlineVisual), Gui::Visual::get_Class());
	return &Class;
}

void MaskOutlineVisual::Render(Gui::ManagedRenderContext renderContext)
{
	// TODO: not like this
	renderContext.m_p->GetRT()->m_modelView = static_cast<Gui::ImmediateRenderContext*>(renderContext.m_p)->m_transform;
	renderContext.m_p->GetRT()->m_modelViewProjection = renderContext.m_p->GetRT()->m_projection * renderContext.m_p->GetRT()->m_modelView;

	Render(renderContext.m_p->GetRT());
}

void MaskOutlineVisual::Render(Graphics::RenderTarget* rt)
{
	HRESULT hr;

	if (rt->m_spRT)
	{
		rt->m_spRT->Flush();
	}

	if (m_effect == NULL)
	{
		HRESULT hr;

		ComPtr<ID3D10Blob> errors;

		UINT hlslFlags = 0;
		hlslFlags |= D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
		hlslFlags |= D3D10_SHADER_DEBUG;
		hlslFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

		hr = D3DX11CreateEffectFromFileW(IO::Path::Combine(IO::Path::GetDirectoryName(_Module.GetFullPath()), L"../../../Shaders/ImageEdit.fx").c_strw(), NULL, NULL, "fx_4_0", hlslFlags, 0, rt->m_d3d10->m_device, NULL, NULL, &m_effect, &errors, NULL);
		if (FAILED(hr))
		{
			switch (hr)
			{
			case D3D11_ERROR_FILE_NOT_FOUND:
				MessageBox(NULL, L"fx file not found\n", L"Draw", MB_OK);
				break;
			}

			String errormsg;

			if (errors)
			{
				int size = errors->GetBufferSize();
				errormsg = (char*)errors->GetBufferPointer();
			}

			raise(Exception("effect err: " + errormsg));
		}

		m_renderSelectionTechnique = m_effect->GetTechniqueByName("RenderSelection");

		m_modelViewProjectionVariable = m_effect->GetVariableByName("modelViewProjection")->AsMatrix();

		m_texture0Variable = m_effect->GetVariableByName("texture0")->AsShaderResource();
		m_texture1Variable = m_effect->GetVariableByName("texture1")->AsShaderResource();

		m_texture0MatrixVariable = m_effect->GetVariableByName("texture0Matrix")->AsMatrix();
		m_texture1TranslateVariable = m_effect->GetVariableByName("texture1Translate")->AsVector();

		m_texelsPerPixelVariable = m_effect->GetVariableByName("texelsPerPixel")->AsVector();

		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
			{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
		};
		UINT numElements = _countof(layout);
		// Create the input layout
		D3DX11_PASS_DESC PassDesc;
		m_renderSelectionTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
		hr = rt->m_d3d10->m_device->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature, 
			PassDesc.IAInputSignatureSize, &m_vertexLayout0);
	}

	m_modelViewProjectionVariable->SetMatrix(rt->m_modelViewProjection);

	if (m_mask->m_bitmap == NULL)
	{
	//	BitmapEditor* editor = dynamic_cast<BitmapEditor*>(GetRoot());

		m_mask->m_bitmap = static_cast<VisualMask*>(m_mask)->m_visual->GetBitmap(rt, m_srcWidth, m_srcHeight, 1, 1);
	}

	float texelsPerPixel[4] = {1.0f / m_mask->m_bitmap->GetWidth(), 1.0f / m_mask->m_bitmap->GetHeight()};
	m_texelsPerPixelVariable->SetFloatVector(texelsPerPixel);

	float patternTranslate[4] = {m_patternSrcX / m_pattern->GetWidth(), m_patternSrcY / m_pattern->GetHeight()};
	m_texture1TranslateVariable->SetFloatVector(patternTranslate);

//	pGraphics->m_d3d9_effect->SetMatrix(pGraphics->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)matrix4f::getIdentity());

	/*
	D3DXHANDLE vposScaleVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "vposScale");
	ASSERT(vposScaleVariable);

	if (m_frameBuffer)
	{
		float vposScale[4] = {1.0f / m_frameBuffer->GetWidth(), 1.0f / m_frameBuffer->GetHeight() };
		pGraphics->m_res->m_d3d9_effect->SetVector(vposScaleVariable, (D3DXVECTOR4*)vposScale);
	}

	D3DXHANDLE alphaMultiplyVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "alphaMultiply");
	ASSERT(alphaMultiplyVariable);

	D3DXHANDLE frameBufferTextureVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "frameBufferTexture");
	ASSERT(frameBufferTextureVariable);
	*/

//	pGraphics->m_res->m_d3d9_effect->SetFloat(alphaMultiplyVariable, m_opacity);
//	dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device)->m_d3dDevice->SetRenderTarget(0, m_renderTarget);
/*
	if (m_frameBuffer)
	{
		hr = pGraphics->m_res->m_d3d9_effect->SetTexture(frameBufferTextureVariable, m_frameBuffer->m_texture.u.d3d);
		ASSERT(SUCCEEDED(hr));
	}
*/

	if (m_mask->m_bitmap)
	{
		m_texture0Variable->SetResource(m_mask->m_bitmap->m_d3d10_shaderResourceView);
	}

	if (m_pattern)
	{
		m_texture1Variable->SetResource(m_pattern->m_d3d10_shaderResourceView);
	}

	float x = m_destRect.X;
	float y = m_destRect.Y;
	float width = m_destRect.Width;
	float height = m_destRect.Height;

	float texX = m_srcX / m_mask->m_bitmap->GetWidth();
	float texY = m_srcY / m_mask->m_bitmap->GetHeight();
	float texWidth = m_srcWidth / m_mask->m_bitmap->GetWidth();
	float texHeight = m_srcHeight / m_mask->m_bitmap->GetHeight();

	float tex1X = 0 / m_pattern->GetWidth();
	float tex1Y = 0 / m_pattern->GetHeight();
	float tex1Width = m_srcWidth / m_pattern->GetWidth();
	float tex1Height = m_srcHeight / m_pattern->GetHeight();
/*
	LDraw::VERTEX_XYZ_T2 vertices[4] =
	{
		{LDraw::vector3f(x, y, 0), LDraw::vector2f(texX, texY)},
		{LDraw::vector3f(x+width, y, 0), LDraw::vector2f(texX+texWidth, texY)},
		{LDraw::vector3f(x, y+height, 0), LDraw::vector2f(texX, texY+texHeight)},
		{LDraw::vector3f(x+width, y+height, 0), LDraw::vector2f(texX+texWidth, texY+texHeight)},
	};
*/
	if (m_vertexBuffer == NULL)
	{
		Graphics::VERTEX_XYZ_T2_T2 vertices[4] =
		{
			/*
			{gm::vector3f(x, y+height, 0), gm::vector2f(texX, texY), gm::vector2f(tex1X, tex1Y)},
			{gm::vector3f(x+width, y+height, 0), gm::vector2f(texX+texWidth, texY), gm::vector2f(tex1X+tex1Width, tex1Y)},
			{gm::vector3f(x, y, 0), gm::vector2f(texX, texY+texHeight), gm::vector2f(tex1X, tex1Y+tex1Height)},
			{gm::vector3f(x+width, y, 0), gm::vector2f(texX+texWidth, texY+texHeight), gm::vector2f(tex1X+tex1Width, tex1Y+tex1Height)},
*/			
			{gm::vector3f(x, y+height, 0),			gm::vector2f(texX, texY+texHeight), gm::vector2f(tex1X, tex1Y+tex1Height)},
			{gm::vector3f(x+width, y+height, 0),	gm::vector2f(texX+texWidth, texY+texHeight), gm::vector2f(tex1X+tex1Width, tex1Y+tex1Height)},
			{gm::vector3f(x, y, 0),					gm::vector2f(texX, texY), gm::vector2f(tex1X, tex1Y)},
			{gm::vector3f(x+width, y, 0),			gm::vector2f(texX+texWidth, texY), gm::vector2f(tex1X+tex1Width, tex1Y)},
		};

		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(vertices);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		rt->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
	}

//	rt->m_d3d10->m_device->OMSetDepthStencilState(GL::Direct10::s.m_pDepthStencilState[false], 0/*stencilRef*/);

	rt->m_d3d10->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	rt->m_d3d10->m_deviceContext->IASetInputLayout(m_vertexLayout0);

	UINT stride[1] = { sizeof(Graphics::VERTEX_XYZ_T2_T2) };
	UINT offset[1] = {0};
	rt->m_d3d10->m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, stride, offset);

	D3DX11_TECHNIQUE_DESC techDesc;
	m_renderSelectionTechnique->GetDesc(&techDesc);

	for (UINT nPass = 0; nPass < techDesc.Passes; ++nPass)
	{
		m_renderSelectionTechnique->GetPassByIndex(nPass)->Apply(0, rt->m_d3d10->m_deviceContext);
		rt->m_d3d10->m_deviceContext->Draw(4, 0);
	}
}

}	// ImageEdit
}	// System
