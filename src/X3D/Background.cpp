#include "stdafx.h"
#include "X3D2.h"
#include "Background.h"

namespace System
{
namespace x3d
{

Graphics::Bitmap* GenTex(X3DDrawContext* pDC, MFString* url)
{
	for (uint i = 0; i < url->get_size(); ++i)
	{
//		FilePath filepath(m_scene->getWorldURL());

//		filepath.set_Filename(url->get1Value(i));
		FilePath filepath(url->get1Value(i));

		//Imaging::BitmapLoader loader;
	//	loader.Load(filepath.get_FullPath());
		Graphics::Bitmap* bitmap = Graphics::Bitmap::FromFile(filepath.get_FullPath());

		if (bitmap != NULL)//pBitmap->GetLastStatus() == LDraw::Ok)
		{
			return bitmap;
#if 0
		//	m_status = -1;

			pG->GenTextures(1, &m_texName[index]);

	//							ASSERT(glError == GL_NO_ERROR);

			pG->BindTexture(GL_TEXTURE_2D, m_texName[index]);

			// Use default envMode GL_REPLACE

			// Set the bitmap data
			pG->TexImage2D(GL_TEXTURE_2D, bitmap);
#endif
		}
	}

	return NULL;
}

IMP_X3DFIELD0(Background, MFString, frontUrl, inputOutput)
IMP_X3DFIELD0(Background, MFString, backUrl, inputOutput)
IMP_X3DFIELD0(Background, MFString, leftUrl, inputOutput)
IMP_X3DFIELD0(Background, MFString, rightUrl, inputOutput)
IMP_X3DFIELD0(Background, MFString, topUrl, inputOutput)
IMP_X3DFIELD0(Background, MFString, bottomUrl, inputOutput)

NodeType* Background::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_backUrlFieldDef(),
		get_bottomUrlFieldDef(),
		get_frontUrlFieldDef(),
		get_leftUrlFieldDef(),
		get_rightUrlFieldDef(),
		get_topUrlFieldDef(),
	};

	static NodeType nodeType(WSTR("Background"), typeid(Background), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* Background::nodeType(GetNodeType());

Background::Background() : X3DBackgroundNode(GetNodeType()),
	m_frontUrl(new MFString(get_frontUrlFieldDef(), this)),
	m_backUrl(new MFString(get_backUrlFieldDef(), this)),
	m_leftUrl(new MFString(get_leftUrlFieldDef(), this)),
	m_rightUrl(new MFString(get_rightUrlFieldDef(), this)),
	m_topUrl(new MFString(get_topUrlFieldDef(), this)),
	m_bottomUrl(new MFString(get_bottomUrlFieldDef(), this))
{
}

void Background::Draw2(X3DDrawContext* pDC)
{

#if 0
	for (n = 0; n < radians.GetSize()-1; n++)
	{
		float radian1 = radians[n];
		float radian2 = radians[n+1];

		LDraw::vector3f color1 = colors[n];
		LDraw::vector3f color2 = colors[n+1];

		pG->glBegin(GL_QUAD_STRIP);

		float cos_rho = cos(radian1);
		float sin_rho = sin(radian1);

		float cos_rho2 = cos(radian2);
		float sin_rho2 = sin(radian2);

		float rho = radian1;

		int nsign = 1;

		for (int m = 0; m <= around_y; m++)
		{
			float theta = (m == around_y)? 0 : ((float)m / around_y) * M_PI*2;

			float x, y, z;

			z = -sin(theta) * sin_rho;
			x = cos(theta) * sin_rho;
			y = nsign * cos_rho;
			pG->glColorf(color1[0], color1[1], color1[2]);
			pG->glVertexf( x*radius, y*radius, z*radius );

			z = -sin(theta) * sin_rho2;
			x = cos(theta) * sin_rho2;
			y = nsign * cos_rho2;
			pG->glColorf(color2[0], color2[1], color2[2]);
			pG->glVertexf( x*radius, y*radius, z*radius );
		}

		pG->glEnd();
	}
#endif

#if 0
	if (m_groundColor->get_size())
	{
		LDraw::vector3f color = m_groundColor->m_items[0];

		pG->glColorf(color[0], color[1], color[2]);
		{
			pG->glBegin(GL_TRIANGLE_FAN);

			pG->glVertexf(0, -5, 0);

			for (int i = 0; i <= around_y; i++)
			{
				float rad = (i == around_y)? 0: ((float)i / around_y) * M_PI*2;
				float x = cos(rad);
				float z = sin(rad);

				pG->glVertexf(x*(radius-8), -5, 0 + z*(radius-8));
			}

			pG->glEnd();
		}
	}
#endif

	float radius = pDC->m_zFar-5;

	Graphics::RenderTarget* rt = pDC->m_renderContext->GetRT();

	rt->m_d3d10->m_device1->IASetInputLayout(Graphics::Direct10::s.m_vertexLayout0);
	rt->m_d3d10->m_device1->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	{
	//	pG->Enable(GL_BLEND);
	//	pG->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float size = cosf(gmRadians(45.0f))*radius;

		if (m_frontUrl->get_size())
		{
			if (m_bitmap[0] == nullptr)
			{
				m_bitmap[0] = GenTex(pDC, m_frontUrl);
			}

			if (m_bitmap[0])
			{
				if (m_vertexBuffer[0] == nullptr)
				{
					// left-handed
					Graphics::VERTEX_XYZ_T2 _vertices[4] =
					{
						{Vec3f(-size/2, -size/2, size/2), Vec2f(0, 1)},
						{Vec3f(size/2, -size/2, size/2), Vec2f(1, 1)},
						{Vec3f(-size/2, size/2, size/2), Vec2f(0, 0)},
						{Vec3f(size/2, size/2, size/2), Vec2f(1, 0)},
					};


					Graphics::VERTEX_XYZ_T2 vertices[4] =
					{
						{Vec3f(-size/2, -size/2, -size/2), Vec2f(0, 1)},
						{Vec3f(size/2, -size/2, -size/2), Vec2f(1, 1)},
						{Vec3f(-size/2, size/2, -size/2), Vec2f(0, 0)},
						{Vec3f(size/2, size/2, -size/2), Vec2f(1, 0)},
					};

					{
						D3D10_BUFFER_DESC bd;
						bd.Usage = D3D10_USAGE_DEFAULT;
						bd.ByteWidth = sizeof(vertices);
						bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
						bd.CPUAccessFlags = 0;
						bd.MiscFlags = 0;
						D3D10_SUBRESOURCE_DATA InitData;
						InitData.pSysMem = vertices;
						rt->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_vertexBuffer[0]);
					}
				}

				UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
				UINT offset = 0;
				rt->m_d3d10->m_device1->IASetVertexBuffers(0, 1, &m_vertexBuffer[0], &stride, &offset);

				D3DXMATRIX modelViewProjection = pDC->m_renderContext->modelViewProjectionMatrix();
				Graphics::Direct10::s.m_modelViewProjectionVariable->SetMatrix(modelViewProjection);

				gm::matrix4f textureMatrix = gm::matrix4f::getIdentity();
				Graphics::Direct10::s.m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

				Graphics::Direct10::s.m_texture0Variable->SetResource(m_bitmap[0]->m_d3d10_shaderResourceView);

				Vec4f colorMultiply(1,1,1,1);
				Vec4f colorTranslate(0,0,0,0);
				Graphics::Direct10::s.m_colorMultiplyVariable->SetFloatVector(colorMultiply);
				Graphics::Direct10::s.m_colorTranslateVariable->SetFloatVector(colorTranslate);

				D3DX10_TECHNIQUE_DESC techDesc;
				Graphics::Direct10::s.m_RenderTextureTechnique->GetDesc(&techDesc);

				Graphics::Direct10::s.m_RenderTextureTechnique->GetPassByIndex(0)->Apply(0);

				rt->m_d3d10->m_device1->Draw(4, 0);
			}

#if 0
		if (m_backUrl->get_size())
		{
			if (m_texName[1] == 0)
			{
				GenTex(pG, m_backUrl, 1);
			}

			if (m_texName[1])
			{
				pG->BindTexture(GL_TEXTURE_2D, m_texName[1]);
				pG->Enable(GL_TEXTURE_2D);

				pG->glBegin(GL_QUADS);

				pG->glTexCoordf(0, 0);
				pG->glVertexf(size/2, -size/2, size/2);

				pG->glTexCoordf(1, 0);
				pG->glVertexf(-size/2, -size/2, size/2);

				pG->glTexCoordf(1, 1);
				pG->glVertexf(-size/2, size/2, size/2);

				pG->glTexCoordf(0, 1);
				pG->glVertexf(size/2, size/2, size/2);

				pG->glEnd();
			}
		}
#endif

		if (m_leftUrl->get_size())
		{
			if (m_bitmap[2] == nullptr)
			{
				m_bitmap[2] = GenTex(pDC, m_leftUrl);
			}

			if (m_bitmap[2])
			{
				if (m_vertexBuffer[2] == nullptr)
				{
					Graphics::VERTEX_XYZ_T2 _vertices[4] =
					{
						{Vec3f(-size/2, -size/2, -size/2), Vec2f(0, 1)},
						{Vec3f(-size/2, -size/2, size/2), Vec2f(1, 1)},
						{Vec3f(-size/2, size/2, -size/2), Vec2f(0, 0)},
						{Vec3f(-size/2, size/2, size/2), Vec2f(1, 0)},
					};

					Graphics::VERTEX_XYZ_T2 vertices[4] =
					{
						{Vec3f(-size/2, -size/2, size/2), Vec2f(0, 1)},
						{Vec3f(-size/2, -size/2, -size/2), Vec2f(1, 1)},
						{Vec3f(-size/2, size/2, size/2), Vec2f(0, 0)},
						{Vec3f(-size/2, size/2, -size/2), Vec2f(1, 0)},
					};

					{
						D3D10_BUFFER_DESC bd;
						bd.Usage = D3D10_USAGE_DEFAULT;
						bd.ByteWidth = sizeof(vertices);
						bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
						bd.CPUAccessFlags = 0;
						bd.MiscFlags = 0;
						D3D10_SUBRESOURCE_DATA InitData;
						InitData.pSysMem = vertices;
						rt->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_vertexBuffer[2]);
					}
				}

				UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
				UINT offset = 0;
				rt->m_d3d10->m_device1->IASetVertexBuffers(0, 1, &m_vertexBuffer[2], &stride, &offset);

				D3DXMATRIX modelViewProjection = pDC->m_renderContext->modelViewProjectionMatrix();
				Graphics::Direct10::s.m_modelViewProjectionVariable->SetMatrix(modelViewProjection);

				gm::matrix4f textureMatrix = gm::matrix4f::getIdentity();
				Graphics::Direct10::s.m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

				Graphics::Direct10::s.m_texture0Variable->SetResource(m_bitmap[2]->m_d3d10_shaderResourceView);

				Vec4f colorMultiply(1,1,1,1);
				Vec4f colorTranslate(0,0,0,0);
				Graphics::Direct10::s.m_colorMultiplyVariable->SetFloatVector(colorMultiply);
				Graphics::Direct10::s.m_colorTranslateVariable->SetFloatVector(colorTranslate);

				D3DX10_TECHNIQUE_DESC techDesc;
				Graphics::Direct10::s.m_RenderTextureTechnique->GetDesc(&techDesc);

				Graphics::Direct10::s.m_RenderTextureTechnique->GetPassByIndex(0)->Apply(0);

				rt->m_d3d10->m_deviceContext->Draw(4, 0);
			}

		}

		if (m_rightUrl->get_size())
		{
			if (m_bitmap[3] == nullptr)
			{
				m_bitmap[3] = GenTex(pDC, m_rightUrl);
			}

			if (m_bitmap[3])
			{
				if (m_vertexBuffer[3] == nullptr)
				{
					Graphics::VERTEX_XYZ_T2 _vertices[4] =
					{
						{Vec3f(size/2, -size/2, size/2), Vec2f(0, 1)},
						{Vec3f(size/2, -size/2, -size/2), Vec2f(1, 1)},
						{Vec3f(size/2, size/2, size/2), Vec2f(0, 0)},
						{Vec3f(size/2, size/2, -size/2), Vec2f(1, 0)},
					};

					Graphics::VERTEX_XYZ_T2 vertices[4] =
					{
						{Vec3f(size/2, -size/2, -size/2), Vec2f(0, 1)},
						{Vec3f(size/2, -size/2, size/2), Vec2f(1, 1)},
						{Vec3f(size/2, size/2, -size/2), Vec2f(0, 0)},
						{Vec3f(size/2, size/2, size/2), Vec2f(1, 0)},
					};

					{
						D3D10_BUFFER_DESC bd;
						bd.Usage = D3D10_USAGE_DEFAULT;
						bd.ByteWidth = sizeof(vertices);
						bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
						bd.CPUAccessFlags = 0;
						bd.MiscFlags = 0;
						D3D10_SUBRESOURCE_DATA InitData;
						InitData.pSysMem = vertices;
						rt->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_vertexBuffer[3]);
					}
				}

				UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
				UINT offset = 0;
				rt->m_d3d10->m_device1->IASetVertexBuffers(0, 1, &m_vertexBuffer[3], &stride, &offset);

				D3DXMATRIX modelViewProjection = pDC->m_renderContext->modelViewProjectionMatrix();
				Graphics::Direct10::s.m_modelViewProjectionVariable->SetMatrix(modelViewProjection);

				gm::matrix4f textureMatrix = gm::matrix4f::getIdentity();
				Graphics::Direct10::s.m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

				Graphics::Direct10::s.m_texture0Variable->SetResource(m_bitmap[3]->m_d3d10_shaderResourceView);

				Vec4f colorMultiply(1,1,1,1);
				Vec4f colorTranslate(0,0,0,0);
				Graphics::Direct10::s.m_colorMultiplyVariable->SetFloatVector(colorMultiply);
				Graphics::Direct10::s.m_colorTranslateVariable->SetFloatVector(colorTranslate);

				D3DX10_TECHNIQUE_DESC techDesc;
				Graphics::Direct10::s.m_RenderTextureTechnique->GetDesc(&techDesc);

				Graphics::Direct10::s.m_RenderTextureTechnique->GetPassByIndex(0)->Apply(0);

				rt->m_d3d10->m_deviceContext->Draw(4, 0);
			}
		}

		if (m_backUrl->get_size())
		{
			if (m_bitmap[4] == NULL)
			{
				m_bitmap[4] = GenTex(pDC, m_backUrl);
			}

			if (m_bitmap[4])
			{
				if (m_vertexBuffer[4] == nullptr)
				{
					Graphics::VERTEX_XYZ_T2 _vertices[4] =
					{
						{Vec3f(size/2, -size/2, -size/2), Vec2f(0, 1)},
						{Vec3f(-size/2, -size/2, -size/2), Vec2f(1, 1)},
						{Vec3f(size/2, size/2, -size/2), Vec2f(0, 0)},
						{Vec3f(-size/2, size/2, -size/2), Vec2f(1, 0)},
					};

					Graphics::VERTEX_XYZ_T2 vertices[4] =
					{
						{Vec3f(size/2, -size/2, size/2), Vec2f(0, 1)},
						{Vec3f(-size/2, -size/2, size/2), Vec2f(1, 1)},
						{Vec3f(size/2, size/2, size/2), Vec2f(0, 0)},
						{Vec3f(-size/2, size/2, size/2), Vec2f(1, 0)},
					};

					{
						D3D10_BUFFER_DESC bd;
						bd.Usage = D3D10_USAGE_DEFAULT;
						bd.ByteWidth = sizeof(vertices);
						bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
						bd.CPUAccessFlags = 0;
						bd.MiscFlags = 0;
						D3D10_SUBRESOURCE_DATA InitData;
						InitData.pSysMem = vertices;
						rt->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_vertexBuffer[4]);
					}
				}

				UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
				UINT offset = 0;
				rt->m_d3d10->m_device1->IASetVertexBuffers(0, 1, &m_vertexBuffer[4], &stride, &offset);

				D3DXMATRIX modelViewProjection = pDC->m_renderContext->modelViewProjectionMatrix();
				Graphics::Direct10::s.m_modelViewProjectionVariable->SetMatrix(modelViewProjection);

				gm::matrix4f textureMatrix = gm::matrix4f::getIdentity();
				Graphics::Direct10::s.m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

				Graphics::Direct10::s.m_texture0Variable->SetResource(m_bitmap[4]->m_d3d10_shaderResourceView);

				Vec4f colorMultiply(1,1,1,1);
				Vec4f colorTranslate(0,0,0,0);
				Graphics::Direct10::s.m_colorMultiplyVariable->SetFloatVector(colorMultiply);
				Graphics::Direct10::s.m_colorTranslateVariable->SetFloatVector(colorTranslate);

				D3DX10_TECHNIQUE_DESC techDesc;
				Graphics::Direct10::s.m_RenderTextureTechnique->GetDesc(&techDesc);

				Graphics::Direct10::s.m_RenderTextureTechnique->GetPassByIndex(0)->Apply(0);

				rt->m_d3d10->m_deviceContext->Draw(4, 0);
			}
		}

		if (m_topUrl->get_size())
		{
			if (m_bitmap[5] == nullptr)
			{
				m_bitmap[5] = GenTex(pDC, m_topUrl);
			}

			if (m_bitmap[5])
			{
				if (m_vertexBuffer[5] == nullptr)
				{
					Graphics::VERTEX_XYZ_T2 _vertices[4] =
					{
						{Vec3f(-size/2, size/2, size/2), Vec2f(0, 1)},
						{Vec3f(size/2, size/2, size/2), Vec2f(1, 1)},
						{Vec3f(-size/2, size/2, -size/2), Vec2f(0, 0)},
						{Vec3f(size/2, size/2, -size/2), Vec2f(1, 0)},
					};

					Graphics::VERTEX_XYZ_T2 vertices[4] =
					{
						{Vec3f(-size/2, size/2, -size/2), Vec2f(0, 1)},
						{Vec3f(size/2, size/2, -size/2), Vec2f(1, 1)},
						{Vec3f(-size/2, size/2, size/2), Vec2f(0, 0)},
						{Vec3f(size/2, size/2, size/2), Vec2f(1, 0)},
					};

					{
						D3D10_BUFFER_DESC bd;
						bd.Usage = D3D10_USAGE_DEFAULT;
						bd.ByteWidth = sizeof(vertices);
						bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
						bd.CPUAccessFlags = 0;
						bd.MiscFlags = 0;
						D3D10_SUBRESOURCE_DATA InitData;
						InitData.pSysMem = vertices;
						rt->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_vertexBuffer[5]);
					}
				}

				UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
				UINT offset = 0;
				rt->m_d3d10->m_device1->IASetVertexBuffers(0, 1, &m_vertexBuffer[5], &stride, &offset);

				D3DXMATRIX modelViewProjection = pDC->m_renderContext->modelViewProjectionMatrix();
				Graphics::Direct10::s.m_modelViewProjectionVariable->SetMatrix(modelViewProjection);

				gm::matrix4f textureMatrix = gm::matrix4f::getIdentity();
				Graphics::Direct10::s.m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

				Graphics::Direct10::s.m_texture0Variable->SetResource(m_bitmap[5]->m_d3d10_shaderResourceView);

				Vec4f colorMultiply(1,1,1,1);
				Vec4f colorTranslate(0,0,0,0);
				Graphics::Direct10::s.m_colorMultiplyVariable->SetFloatVector(colorMultiply);
				Graphics::Direct10::s.m_colorTranslateVariable->SetFloatVector(colorTranslate);

				D3DX10_TECHNIQUE_DESC techDesc;
				Graphics::Direct10::s.m_RenderTextureTechnique->GetDesc(&techDesc);

				Graphics::Direct10::s.m_RenderTextureTechnique->GetPassByIndex(0)->Apply(0);

				rt->m_d3d10->m_deviceContext->Draw(4, 0);
			}
		}

		if (m_bottomUrl->get_size())
		{
			if (m_bitmap[1] == nullptr)
			{
				m_bitmap[1] = GenTex(pDC, m_bottomUrl);
			}

			if (m_bitmap[1])
			{
				if (m_vertexBuffer[1] == nullptr)
				{
					Graphics::VERTEX_XYZ_T2 _vertices[4] =
					{
						{Vec3f(-size/2, -size/2, -size/2), Vec2f(0, 1)},
						{Vec3f(size/2, -size/2, -size/2), Vec2f(1, 1)},
						{Vec3f(-size/2, -size/2, size/2), Vec2f(0, 0)},
						{Vec3f(size/2, -size/2, size/2), Vec2f(1, 0)},
					};

					Graphics::VERTEX_XYZ_T2 vertices[4] =
					{
						{Vec3f(-size/2, -size/2, size/2), Vec2f(0, 1)},
						{Vec3f(size/2, -size/2, size/2), Vec2f(1, 1)},
						{Vec3f(-size/2, -size/2, -size/2), Vec2f(0, 0)},
						{Vec3f(size/2, -size/2, -size/2), Vec2f(1, 0)},
					};

					{
						D3D10_BUFFER_DESC bd;
						bd.Usage = D3D10_USAGE_DEFAULT;
						bd.ByteWidth = sizeof(vertices);
						bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
						bd.CPUAccessFlags = 0;
						bd.MiscFlags = 0;
						D3D10_SUBRESOURCE_DATA InitData;
						InitData.pSysMem = vertices;
						rt->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_vertexBuffer[1]);
					}
				}

				UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
				UINT offset = 0;
				rt->m_d3d10->m_device1->IASetVertexBuffers(0, 1, &m_vertexBuffer[1], &stride, &offset);

				D3DXMATRIX modelViewProjection = pDC->m_renderContext->modelViewProjectionMatrix();
				Graphics::Direct10::s.m_modelViewProjectionVariable->SetMatrix(modelViewProjection);

				gm::matrix4f textureMatrix = gm::matrix4f::getIdentity();
				Graphics::Direct10::s.m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

				Graphics::Direct10::s.m_texture0Variable->SetResource(m_bitmap[1]->m_d3d10_shaderResourceView);

				Vec4f colorMultiply(1,1,1,1);
				Vec4f colorTranslate(0,0,0,0);
				Graphics::Direct10::s.m_colorMultiplyVariable->SetFloatVector(colorMultiply);
				Graphics::Direct10::s.m_colorTranslateVariable->SetFloatVector(colorTranslate);

				D3DX10_TECHNIQUE_DESC techDesc;
				Graphics::Direct10::s.m_RenderTextureTechnique->GetDesc(&techDesc);

				Graphics::Direct10::s.m_RenderTextureTechnique->GetPassByIndex(0)->Apply(0);

				rt->m_d3d10->m_deviceContext->Draw(4, 0);
			}
		}

#if 0
		if (m_topUrl->get_size())
		{
			if (m_texName[4] == 0)
			{
				GenTex(pG, m_topUrl, 4);
			}

			if (m_texName[4])
			{
				pG->BindTexture(GL_TEXTURE_2D, m_texName[4]);
				pG->Enable(GL_TEXTURE_2D);

				pG->glBegin(GL_QUADS);

				pG->glTexCoordf(0, 0);
				pG->glVertexf(-size/2, size/2, -size/2);

				pG->glTexCoordf(1, 0);
				pG->glVertexf(size/2, size/2, -size/2);

				pG->glTexCoordf(1, 1);
				pG->glVertexf(size/2, size/2, size/2);

				pG->glTexCoordf(0, 1);
				pG->glVertexf(-size/2, size/2, size/2);

				pG->glEnd();
			}
		}

		if (m_bottomUrl->get_size())
		{
			if (m_texName[5] == 0)
			{
				GenTex(pG, m_bottomUrl, 5);
			}

			if (m_texName[5])
			{
				pG->BindTexture(GL_TEXTURE_2D, m_texName[5]);
				pG->Enable(GL_TEXTURE_2D);

				pG->glBegin(GL_QUADS);

				pG->glTexCoordf(0, 0);
				pG->glVertexf(-size/2, -size/2, size/2);

				pG->glTexCoordf(1, 0);
				pG->glVertexf(size/2, -size/2, size/2);

				pG->glTexCoordf(1, 1);
				pG->glVertexf(size/2, -size/2, -size/2);

				pG->glTexCoordf(0, 1);
				pG->glVertexf(-size/2, -size/2, -size/2);

				/*
				pG->glTexCoordf(0, 0);
				pG->glVertexf(-size/2, size/2, size/2);

				pG->glTexCoordf(1, 0);
				pG->glVertexf(size/2, size/2, size/2);

				pG->glTexCoordf(1, 1);
				pG->glVertexf(size/2, size/2, -size/2);

				pG->glTexCoordf(0, 1);
				pG->glVertexf(-size/2, size/2, -size/2);
				*/

				pG->glEnd();
			}
#endif
		}
	}
}

}	// x3d
}	// System
