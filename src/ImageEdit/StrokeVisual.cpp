#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace gm
{

GUIEXT gm::matrix4f mat4(const gm::matrix3f& transform);

}

namespace ImageEdit
{

Gui::DependencyClass* StrokeVisual::get_Class()
{
	static Gui::DependencyClass Class(typeid(StrokeVisual), baseClass::get_Class());
	return &Class;
}

StrokeVisual::StrokeVisual() : BElement(get_Class())
{
}

void StrokeVisual::ReloadEffect()
{
	if (m_effect)
	{
		m_RenderTextureTechnique = NULL;

		m_effect->Release();
		m_effect = NULL;
	}
}

void StrokeVisual::LoadEffect()
{
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

		hr = D3DX11CreateEffectFromFileW(IO::Path::Combine(IO::Path::GetDirectoryName(_Module.GetFullPath()), L"../../../Shaders/PaintBrush.fx").c_strw(), NULL, NULL, "fx_4_0", hlslFlags, 0, Graphics::Direct3D10_I::GetCurrent()->m_device, NULL, NULL, &m_effect, &errors, NULL);
		if (FAILED(hr))
		{
			switch (hr)
			{
			case D3D11_ERROR_FILE_NOT_FOUND:
				MessageBox(NULL, L"fx file not found\n", L"ImageEdit", MB_OK | MB_ICONERROR);
				break;
			}

			String errormsg;

			if (errors)
			{
				SIZE_T size = errors->GetBufferSize();
				errormsg = (char*)errors->GetBufferPointer();

				MessageBox(NULL, errormsg.c_strw(), L"ImageEdit", MB_OK | MB_ICONERROR);
			}

			return;
			//raise(Exception("effect err: " + errormsg));
		}

		m_RenderTextureTechnique = m_effect->GetTechniqueByName("RenderTexture");

		m_modelViewVariable = m_effect->GetVariableByName("modelView")->AsMatrix();
		m_projectionVariable = m_effect->GetVariableByName("projection")->AsMatrix();
		m_modelViewProjectionVariable = m_effect->GetVariableByName("modelViewProjection")->AsMatrix();

		m_texture0Variable = m_effect->GetVariableByName("texture0")->AsShaderResource();
		m_textureMatrix0Variable = m_effect->GetVariableByName("textureMatrix0")->AsMatrix();

		m_texture1Variable = m_effect->GetVariableByName("texture1")->AsShaderResource();
		m_textureMatrix1Variable = m_effect->GetVariableByName("textureMatrix1")->AsMatrix();

		//m_colorTransformVariable = m_effect->GetVariableByName("colorTransform")->AsMatrix();
		m_colorTranslateVariable = m_effect->GetVariableByName("colorTranslate")->AsVector();
		m_colorMultiplyVariable = m_effect->GetVariableByName("colorMultiply")->AsVector();

		{
			// Define the input layout
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
			//	{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 20, D3D10_INPUT_PER_VERTEX_DATA, 0 }, 
			};
			UINT numElements = _countof(layout);
			// Create the input layout
			D3DX11_PASS_DESC PassDesc;
			m_RenderTextureTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
			hr = Graphics::Direct3D10_I::GetCurrent()->m_device->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature, 
				PassDesc.IAInputSignatureSize, &m_vertexLayout0);
			ASSERT(SUCCEEDED(hr));
		}
	}
}

void StrokeVisual::CreateVertexBuffer()
{
	if (m_vertexBuffer == NULL)
	{
		// Create vertex buffer
		Graphics::VERTEX_XYZ_T2 vertices[] =
		{
			gm::vector3f( 0, 1, 0 ), gm::vector2f(0, 1),// gm::vector2f(0, 1),
			gm::vector3f( 1, 1, 0 ), gm::vector2f(1, 1),// gm::vector2f(1, 1),
			gm::vector3f( 0, 0, 0 ), gm::vector2f(0, 0),// gm::vector2f(0, 0),
			gm::vector3f( 1, 0, 0 ), gm::vector2f(1, 0),// gm::vector2f(1, 0),
		};

		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(vertices[0]) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		Graphics::Direct10::get_D3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
	}
}

void StrokeVisual::Render(Gui::ManagedRenderContext renderContext)
{
	Graphics::RenderTarget* rt = renderContext.m_p->GetRT();

	if (rt->m_spRT)
	{
		rt->m_spRT->Flush();
	}

	HRESULT hr;

	LoadEffect();

	if (m_mask)
	{
		CreateVertexBuffer();
	}
	else
	{
		ASSERT(0);
	}

	if (m_brush == NULL)
	{
		m_brush = new PaintBrush;
		m_brush->SetCircular();
	}

	if (true)
	{
		if (m_points.size() > 0)
		{
			MoveTo(m_points[0]);
			for (size_t i = 1; i < m_points.size(); ++i)
			{
				LineTo(rt, m_points[i]);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_points.size(); ++i)
		{
			gm::PointF pt = m_points[i];

			float brushSize = m_brushSize;

			Blt(rt, m_brush->m_bitmap, gm::RectF(pt.X-brushSize/2, pt.Y-brushSize/2, brushSize, brushSize), m_colorMultiply);
		}
	}
}

void StrokeVisual::Blt(Graphics::RenderTarget* rt, Graphics::Bitmap* bitmap, gm::RectF dstRect, gm::vector4f colorMultiply, gm::vector4f colorTranslate)
{
	HRESULT hr;

	ASSERT(bitmap->m_d3d10_shaderResourceView);

	// TODO
//	rt->m_d3d10->m_device->CopySubresourceRegion();
	
	rt->m_d3d10->m_deviceContext->IASetInputLayout(m_vertexLayout0);

	UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
	UINT offset = 0;
	rt->m_d3d10->m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	rt->m_d3d10->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	/*
	gm::matrix4f xform =
		gm::matrix4f::getTranslate(dstRect.X, dstRect.Y, 0) *
		gm::matrix4f::getScale(dstRect.Width, dstRect.Height, 1);

	m_modelViewProjectionVariable->SetMatrix((float*)(rt->m_projection * xform));
*/
	gm::matrix3f xform =
		gm::matrix3f::getScale(dstRect.Width, dstRect.Height) *
		gm::matrix3f::getTranslate(dstRect.X, dstRect.Y) *
		rt->m_transform3x3;

	m_modelViewProjectionVariable->SetMatrix((float*)(rt->m_projection * gm::mat4(xform)));

	gm::matrix4f textureMatrix = gm::matrix4f::getIdentity();

	m_texture0Variable->SetResource(bitmap->m_d3d10_shaderResourceView);
	m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

//	D3DXMATRIX texture1Matrix =
	//	gm::MatrixTranslation(gm::vector3f(-dstRect.X, -dstRect.Y, 0)) *
		//gm::MatrixScale(gm::vector3f(dstRect.Width / m_document->m_size.Width, dstRect.Height / m_document->m_size.Height, 1));

	if (m_mask->m_bitmap)
	{
		hr = m_texture1Variable->SetResource(m_mask->m_bitmap->m_d3d10_shaderResourceView);
		ASSERT(SUCCEEDED(hr));
	}
	gm::matrix3f texture1Matrix = 
		xform *
		/*
		gm::matrix3f::getScale(dstRect.Width, dstRect.Height) *
		gm::matrix3f::getTranslate(dstRect.X, dstRect.Y) * 
		*/
		gm::matrix3f::getScale(1.0f / m_document->m_size.Width, 1.0f / m_document->m_size.Height);

	m_textureMatrix1Variable->SetMatrix((float*)gm::matrix4f(texture1Matrix));

	m_colorMultiplyVariable->SetFloatVector(colorMultiply);
	m_colorTranslateVariable->SetFloatVector(colorTranslate);

	D3DX11_TECHNIQUE_DESC techDesc;
	m_RenderTextureTechnique->GetDesc(&techDesc);

	for (UINT nPass = 0; nPass < techDesc.Passes; ++nPass)
	{
		HRESULT hr = m_RenderTextureTechnique->GetPassByIndex(nPass)->Apply(0, rt->m_d3d10->m_deviceContext);
		ASSERT(SUCCEEDED(hr));

		rt->m_d3d10->m_deviceContext->Draw(
			4, // VertexCount
			0 // StartVertexLocation
			);
	}

	m_texture0Variable->SetResource(NULL);
}

void StrokeVisual::MoveTo(gm::PointF pos)
{
	m_oldpos = pos;
}

void StrokeVisual::LineTo(Graphics::RenderTarget* rt, gm::PointF pos)
{
	float dx = (pos.X - m_oldpos.X);
	float dy = (pos.Y - m_oldpos.Y);

	float length = sqrtf(dx*dx + dy*dy);

	float factor = m_brushSize * m_spacing;

	dx /= length;
	dy /= length;
	dx *= factor;
	dy *= factor;

	unsigned int nsteps = length / (factor);

	float x = m_oldpos.X;
	float y = m_oldpos.Y;

	float brushSize = m_brushSize;

	for (size_t n = 0; n < nsteps; ++n)
	{
		Blt(rt, m_brush->m_bitmap, gm::RectF(x-brushSize/2, y-brushSize/2, brushSize, brushSize), m_colorMultiply);

		x += dx;
		y += dy;
	}

	m_oldpos.X = x;
	m_oldpos.Y = y;
}

}	// ImageEdit
}	// System
