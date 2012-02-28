#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

class Effects
{
public:
	CTOR Effects();
	~Effects();

	void Init();

	ID3DX10Effect* m_effect;
	ID3DX10EffectMatrixVariable* m_modelViewVariable;
	ID3DX10EffectMatrixVariable* m_projectionVariable;
	ID3DX10EffectMatrixVariable* m_modelViewProjectionVariable;
	ID3DX10EffectShaderResourceVariable* m_textureVariable;
	ID3DX10EffectMatrixVariable* m_textureMatrixVariable;

	ID3DX10EffectVectorVariable* m_texelKernel;
	ID3DX10EffectScalarVariable* m_kernelSize;
	ID3DX10EffectScalarVariable* m_blurWeights;
	ID3DX10EffectMatrixVariable* m_colorTransformVariable;
	ID3DX10EffectVectorVariable* m_colorTranslateVariable;

	ID3DX10EffectTechnique* m_techniqueH;
	ID3DX10EffectTechnique* m_techniqueV;
};

Effects::Effects()
{
}

Effects::~Effects()
{
}

void Effects::Init()
{
	if (m_effect == NULL)
	{
		HRESULT hr;

		ID3D10Blob* errors = NULL;

		UINT hlslFlags = 0;
		hlslFlags |= D3D10_SHADER_ENABLE_STRICTNESS;
		hlslFlags |= D3D10_SHADER_DEBUG;
		hlslFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;

		hr = D3DX10CreateEffectFromFileW(L"../../../Shaders/GaussianBlur.fx", NULL, NULL, "fx_4_1", hlslFlags, 0, Graphics::Direct10::get_D3DDevice(), NULL, NULL, &m_effect, &errors, NULL);
		if (FAILED(hr))
		{
			switch (hr)
			{
			case D3D10_ERROR_FILE_NOT_FOUND:
				DebugTrace("fx file not found\n");
				break;
			}

			SIZE_T size = errors->GetBufferSize();
			char* errormsg = (char*)errors->GetBufferPointer();
			ASSERT(0);
			errors->Release();

			return;
		}

		/*
		m_d3d10_modelViewVariable = m_d3d10_effect->GetVariableByName("modelView")->AsMatrix();
		m_d3d10_projectionVariable = m_d3d10_effect->GetVariableByName("projection")->AsMatrix();
		m_d3d10_modelViewProjectionVariable = m_d3d10_effect->GetVariableByName("modelViewProjection")->AsMatrix();
		m_d3d10_modelViewITVariable = m_d3d10_effect->GetVariableByName("modelViewIT")->AsMatrix();
		m_d3d10_modelViewProjectionITVariable = m_d3d10_effect->GetVariableByName("modelViewProjectionIT")->AsMatrix();
		m_d3d10_nlightsVariable = m_d3d10_effect->GetVariableByName("nlights")->AsScalar();
		m_d3d10_lightsVariable = m_d3d10_effect->GetVariableByName("lights");
		*/

		m_techniqueH = m_effect->GetTechniqueByName("RenderFilterGaussianBlurH");
		m_techniqueV = m_effect->GetTechniqueByName("RenderFilterGaussianBlurV");
		//	m_res->m_d3d9_technique1 = m_res->m_d3d9_effect->GetTechniqueByName("RenderLinearGradient");
		//	m_res->m_d3d9_technique4 = m_res->m_d3d9_effect->GetTechniqueByName("RenderTextSolidColor");

		m_modelViewProjectionVariable = m_effect->GetVariableByName("modelViewProjection")->AsMatrix();
		m_textureVariable = m_effect->GetVariableByName("texture0")->AsShaderResource();
		m_textureMatrixVariable = m_effect->GetVariableByName("textureMatrix0")->AsMatrix();

		/*
		{
			// Define the input layout
			D3D10_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },  
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },  
			};
			UINT numElements = sizeof(layout)/sizeof(layout[0]);
			// Create the input layout
			D3D10_PASS_DESC PassDesc;
			m_RenderTextureTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
			hr = GL::Direct10::get_D3DDevice()->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature, 
				PassDesc.IAInputSignatureSize, &m_vertexLayout0);
		}
		*/

		m_texelKernel = m_effect->GetVariableByName("TexelKernel")->AsVector();
		ASSERT(m_texelKernel->IsValid());
		m_kernelSize = m_effect->GetVariableByName("KernelSize")->AsScalar();
		m_blurWeights = m_effect->GetVariableByName("BlurWeights")->AsScalar();
		m_colorTransformVariable = m_effect->GetVariableByName("colorTransform")->AsMatrix();
		m_colorTranslateVariable = m_effect->GetVariableByName("colorTranslate")->AsVector();
	}
}

//static Effects* s_peff;
static Effects s_eff;// = *s_peff;

float float4x4_identity[4*4] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1,
};

GaussianBlurEffect::GaussianBlurEffect()
{
}

GaussianBlurEffect::GaussianBlurEffect(IEffect* input, float stdDeviationX, float stdDeviationY)
{
	m_inEffect = input;
	m_stdDeviationX = stdDeviationX;
	m_stdDeviationY = stdDeviationY;
}

unsigned int GaussianBlurEffect::GetInputCount()
{
	return 1;
}

IEffect* GaussianBlurEffect::GetInput(unsigned int index)
{
	if (index != 0)
	{
		raise(Exception("Index out of bounds"));
	}

	return m_inEffect;
}

void GaussianBlurEffect::SetInput(unsigned int index, IEffect* input)
{
	if (index != 0)
	{
		raise(Exception("Index out of bounds"));
	}

	m_inEffect = input;
}

void GaussianBlurEffect::Render(RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection)
{
	if (s_eff.m_effect == NULL)
	{
	//	s_peff = new Effects;
		s_eff.Init();
	}

	if (m_inEffect->GetOutputBitmap() == NULL)
	{
		m_inEffect->RenderOutput(rt);
	}

//	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_vertexDeclaration1);

	/*
	m_stdDeviationX = 6;
	m_stdDeviationY = 6;
	*/

	unsigned int cKernelX = m_stdDeviationX*2+1;
	unsigned int cKernelY = m_stdDeviationY*2+1;

	float2* TexelKernel = (float2*)alloca(sizeof(float2) * __max(cKernelX, cKernelY)+16);	// hmm
	float* BlurWeights = (float*)alloca(sizeof(float) * __max(cKernelX, cKernelY));

//	pGraphics->m_device->SetPrimitiveTopology(GL_TRIANGLE_STRIP);

//	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device);

	ID3D10RenderTargetView* pOldRenderTarget;
	rt->GetRT()->m_d3d10->m_device->OMGetRenderTargets(1, &pOldRenderTarget, NULL);

	UINT numOldViewports = 8;
	D3D10_VIEWPORT pOldViewports[8];
	rt->GetRT()->m_d3d10->m_device->RSGetViewports(&numOldViewports, pOldViewports);

	// Common for both Horizontal and Vertical
	rt->GetRT()->m_d3d10->m_device->IASetInputLayout(Graphics::Direct10::s.m_vertexLayout0);

	UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
	UINT offset = 0;
	rt->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 1, &Graphics::Direct10::s.m_DrawImageVertexBuffer, &stride, &offset);
	rt->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	ID3D10Texture2D* tempTexture = NULL;
	ID3D10ShaderResourceView* tempShaderResourceView = NULL;
	ID3D10RenderTargetView* tempRenderTargetView = NULL;

	// Create the render target texture and view
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = m_scaledWidth;
	desc.Height = m_scaledHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
	rt->GetRT()->m_d3d10->m_device->CreateTexture2D(&desc, NULL, &tempTexture);

	D3D10_RENDER_TARGET_VIEW_DESC rtDesc;
	rtDesc.Format = desc.Format;
	rtDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	rtDesc.Texture2D.MipSlice = 0;
	rt->GetRT()->m_d3d10->m_device->CreateRenderTargetView(tempTexture, &rtDesc, &tempRenderTargetView);

	D3D10_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = desc.Format;
	srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;
	rt->GetRT()->m_d3d10->m_device->CreateShaderResourceView(tempTexture, &srDesc, &tempShaderResourceView);

	rt->GetRT()->m_d3d10->m_device->OMSetRenderTargets(1, &tempRenderTargetView, NULL);

	D3D10_VIEWPORT vp;
	vp.Width = m_scaledWidth;
	vp.Height = m_scaledHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	rt->GetRT()->m_d3d10->m_device->RSSetViewports(1, &vp);

	// GaussianBlur Horizontal
	{
		s_eff.m_colorTransformVariable->SetMatrix(gm::matrix4f::getIdentity());
		s_eff.m_colorTranslateVariable->SetFloatVector(gm::vector4f(0,0,0,0));

		gm::matrix3f textureMatrix =
			gm::matrix3f::getScale(m_scaledWidth / m_subRegion.Width, m_scaledHeight / m_subRegion.Height) *
			gm::matrix3f::getTranslate(-m_subRegion.X / m_scaledWidth, -m_subRegion.Y / m_scaledHeight);

		s_eff.m_textureMatrixVariable->SetMatrix(float4x4(textureMatrix));

		gm::matrix4f modelView =
			gm::matrix4f::getTranslate(0, 0, 0) *
			gm::matrix4f::getScale(m_scaledWidth, m_scaledHeight, 1);

		gm::matrix4f projection = gm::matrix4f::getOrtho2D(0, m_scaledWidth, m_scaledHeight, 0);
		s_eff.m_modelViewProjectionVariable->SetMatrix(projection * modelView);

		float sum = 0;

		for (int i = 0; i < cKernelX; i++)
		{
			int pixelX = i - cKernelX/2;

			TexelKernel[i].x = (float)pixelX / m_inEffect->GetOutputBitmap()->GetWidth();
			TexelKernel[i].y = 0;

		//	BlurWeights[i] = exp(-(pixelX*pixelX) / (2*m_stdDeviationX*m_stdDeviationX)) / sqrt(2 * M_PI * m_stdDeviationX*m_stdDeviationX);

			BlurWeights[i] = 1;

			sum += BlurWeights[i];
		}

		for (uint i = 0; i < cKernelX; i++)
		{
			BlurWeights[i] /= sum;
		}

		HRESULT hr;

		s_eff.m_kernelSize->SetInt(cKernelX);
		hr = s_eff.m_texelKernel->SetFloatVectorArray((float*)TexelKernel, 0, (cKernelX+1)/2);
		ASSERT(SUCCEEDED(hr));

		hr = s_eff.m_blurWeights->SetFloatArray(BlurWeights, 0, cKernelX);
		ASSERT(SUCCEEDED(hr));

		s_eff.m_textureVariable->SetResource(m_inEffect->GetOutputBitmap()->m_d3d10_shaderResourceView);
	//	m_effect->SetTechnique(m_techniqueH);
		//DrawBitmap(rt, RectF(0, 0, m_scaledWidth, m_scaledHeight));

		D3DX10_TECHNIQUE_DESC techDesc;
		s_eff.m_techniqueH->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			s_eff.m_techniqueH->GetPassByIndex(p)->Apply(0);

			rt->GetRT()->m_d3d10->m_deviceContext->Draw(
				4, // VertexCount
				0 // StartVertexLocation
				);
		}
	}

	rt->GetRT()->m_d3d10->m_device->OMSetRenderTargets(1, &pOldRenderTarget, NULL);
	if (pOldRenderTarget) pOldRenderTarget->Release();

	rt->GetRT()->m_d3d10->m_device->RSSetViewports(numOldViewports, pOldViewports);

	// GaussianBlur Vertical
	{

		s_eff.m_colorTransformVariable->SetMatrix((float*)rt->m_colorTransform);
		s_eff.m_colorTranslateVariable->SetFloatVector(rt->m_colorTranslate);

		/*
		matrix4f modelView;
		pGraphics->m_device->GetFloatv(GL_MODELVIEW_MATRIX, (float*)modelView);

		matrix4f projection;
		pGraphics->m_device->GetFloatv(GL_PROJECTION_MATRIX, (float*)projection);
		*/

	//	destRect.X += m_subRegion.X;
	//	destRect.Y += m_subRegion.Y;

		gm::matrix4f modelView =
			gm::matrix4f::getTranslate(destRect.X, destRect.Y, 0) *
			gm::matrix4f::getScale(destRect.Width, destRect.Height, 1);

		s_eff.m_modelViewProjectionVariable->SetMatrix((float*)(rt->GetRT()->m_modelViewProjection * modelView));
	//	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	//	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));

		s_eff.m_textureMatrixVariable->SetMatrix(float4x4_identity);

		float sum = 0;

		for (int i = 0; i < cKernelY; i++)
		{
			int pixelY = i - cKernelY/2;

			TexelKernel[i].x = 0;
			TexelKernel[i].y = (float)pixelY / m_inEffect->GetOutputBitmap()->GetHeight();

		//	BlurWeights[i] = exp(-(pixelY*pixelY) / (2*m_stdDeviationY*m_stdDeviationY)) / sqrt(2 * M_PI * m_stdDeviationY*m_stdDeviationY);

			BlurWeights[i] = 1;

			sum += BlurWeights[i];
		}

		for (unsigned int i = 0; i < cKernelY; i++)
		{
			BlurWeights[i] /= sum;
		}

		/*
		for (unsigned int i = 0; i < cKernelY/2; i++)
		{
			BlurWeights[i] = exp(-pixelY/ (cKernelY)) / sqrt(2* M_PI*cKernelY)
		}
		*/

		s_eff.m_kernelSize->SetInt(cKernelY);
		s_eff.m_texelKernel->SetFloatVectorArray((float*)TexelKernel, 0, (cKernelY+1)*2);
		s_eff.m_blurWeights->SetFloatArray(BlurWeights, 0, cKernelY);

		s_eff.m_textureVariable->SetResource(tempShaderResourceView);
	//	pGraphics->m_res->m_d3d9_effect->SetTechnique(m_techniqueV);
	//	destRect.X += m_subRegion.X;
	//	destRect.Y += m_subRegion.Y;
//		GL::Direct10::s.Render(rt, destRect);

		D3DX10_TECHNIQUE_DESC techDesc;
		s_eff.m_techniqueV->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			s_eff.m_techniqueV->GetPassByIndex(p)->Apply(0);

			rt->GetRT()->m_d3d10->m_deviceContext->Draw(
				4, // VertexCount
				0 // StartVertexLocation
				);
		}
	}

	s_eff.m_textureVariable->SetResource(NULL);

	tempTexture->Release();
	tempShaderResourceView->Release();
	tempRenderTargetView->Release();
}

}	// Gui
}	// System
