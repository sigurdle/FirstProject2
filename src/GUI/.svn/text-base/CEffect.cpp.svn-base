#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

CEffect::CEffect()
{
	m_outImage = NULL;
}

CEffect::~CEffect()
{
	if (m_outImage)
	{
	//	delete m_outImage;
		m_outImage = NULL;
	}
}

void CEffect::RenderOutput(Gui::RenderContext *renderContext)
{
	ASSERT(0);
}

#if 0
void CEffect::DrawBitmap(RenderTarget* rt, ID3D10TextureView* textureView, RectF destRect)
{
	rt->m_device->IASetInputLayout(GL::Direct10::s.m_vertexLayout0);

	UINT stride = sizeof(GL::VERTEX_XYZ_T2);
	UINT offset = 0;
	rt->m_device->IASetVertexBuffers(0, 1, &GL::Direct10::s.m_DrawImageVertexBuffer, &stride, &offset);
	rt->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	LDraw::matrix4f xform =
		LDraw::matrix4f::getTranslate(destRect.X, destRect.Y, 0) *
		LDraw::matrix4f::getScale(destRect.Width, destRect.Height, 1);

	m_modelViewProjectionVariable->SetMatrix((float*)(rt->m_modelViewProjection * xform));

	LDraw::matrix4f textureMatrix = LDraw::matrix4f::getIdentity();

//	m_texture0Variable->SetResource(bitmap->m_d3d10_textureView);
//	m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

	D3D10_TECHNIQUE_DESC techDesc;
	m_RenderTextureTechnique->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_RenderTextureTechnique->GetPassByIndex(p)->Apply(0);

		rt->m_device->Draw(
			4, // VertexCount
			0 // StartVertexLocation
			);
	}
#if 0
	float x = destRect.X;
	float y = destRect.Y;
	float width = destRect.Width;
	float height = destRect.Height;

	VERTEX_XYZ_T2 vertices[4] =
	{
		{vector3f(x, y, 0), vector2f(0, 0)},
		{vector3f(x+width, y, 0), vector2f(1, 0)},
		{vector3f(x, y+height, 0), vector2f(0, 1)},
		{vector3f(x+width, y+height, 0), vector2f(1, 1)},
	};

	HRESULT hr;

	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_res->m_vertexDeclaration1);
	pGraphics->m_device->SetPrimitiveTopology(GL_TRIANGLE_STRIP);

	UINT nPasses;
	hr = pGraphics->m_res->m_d3d9_effect->Begin(&nPasses, 0);
	ASSERT(SUCCEEDED(hr));
	for (UINT nPass = 0; nPass < nPasses; ++nPass)
	{
		hr = pGraphics->m_res->m_d3d9_effect->BeginPass(nPass);
		ASSERT(SUCCEEDED(hr));

		pGraphics->m_device->DrawUP(4, vertices, sizeof(VERTEX_XYZ_T2));

#if 0
		if (indexBuffer != NULL)
			m_device->DrawIndexed(0, count-1, count/*, GL_UNSIGNED_SHORT, m_indexOffset*/);
		else
			m_device->Draw(0, count);
#endif
		hr = pGraphics->m_res->m_d3d9_effect->EndPass();
		ASSERT(SUCCEEDED(hr));
	}
	hr = pGraphics->m_res->m_d3d9_effect->End();
	ASSERT(SUCCEEDED(hr));
#endif
}
#endif

void VisualEffect::RenderOutput(RenderContext* renderContext)
{
	ASSERT(0);
#if 0
	m_outImage = m_visual->GetBitmap(ManagedRenderContext(renderContext), m_subRegion.Width, m_subRegion.Height, 1, 1);
	ASSERT(m_outImage->m_d3d10_shaderResourceView);
#endif

	/*
	if (m_outImage->m_texture == NULL)
	{
		m_outImage->m_texture = rt->m_device->CreateTexture2D(0, GL_RGBA, m_outImage->GetWidth(), m_outImage->GetHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, m_outImage->GetPointer());
	}
	*/
}

}
}
