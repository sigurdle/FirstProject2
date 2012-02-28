#include "stdafx.h"
#include "GUI2.h"

#include "physics.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

//ID3D10Effect* Mesh::g_pEffect;

ID3DX11Effect*                       g_pEffect10 = nullptr;
ID3D11InputLayout*                  g_pVertexLayout = nullptr;
ID3DX11EffectTechnique*              g_pNoSpecularTechnique = nullptr;
ID3DX11EffectShaderResourceVariable* g_ptxDiffuseVariable = nullptr;

ID3DX11EffectVectorVariable*         g_pAmbient = nullptr;
ID3DX11EffectVectorVariable*         g_pDiffuse = nullptr;
ID3DX11EffectVectorVariable*         g_pSpecular = nullptr;
ID3DX11EffectScalarVariable*         g_pOpacity = nullptr;
ID3DX11EffectScalarVariable*         g_pSpecularPower = nullptr;
ID3DX11EffectVectorVariable*         g_pLightColor = nullptr;
ID3DX11EffectVectorVariable*         g_pLightPosition = nullptr;
ID3DX11EffectVectorVariable*         g_pCameraPosition = nullptr;
ID3DX11EffectScalarVariable*         g_pTime = nullptr;
ID3DX11EffectMatrixVariable*         g_pWorld = nullptr;
ID3DX11EffectMatrixVariable*         g_pWorldViewProjection = nullptr;

#if 0
void Mesh::Init()
{
	if (g_pEffect10 == NULL)
	{
		ID3D10Device* pd3dDevice = GL::Direct10::get_D3DDevice();

		HRESULT hr;

		ID3D10Blob* errors = NULL;

		UINT hlslFlags = 0;
		hlslFlags |= D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
		hlslFlags |= D3D10_SHADER_DEBUG;
		hlslFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

		hr = D3DX10CreateEffectFromFile(L"../../../Shaders/MeshFromOBJ10.fx", NULL, NULL, "fx_4_0", hlslFlags, 0, pd3dDevice, NULL, NULL, &g_pEffect10, &errors, NULL);
		if (FAILED(hr))
		{
			/*
			switch (hr)
			{
			case D3D10_ERROR_FILE_NOT_FOUND:
				MessageBox(NULL, L"fx file not found\n", L"Draw", MB_OK);
				break;
			}
			*/

			String errormsg;

			if (errors)
			{
				int size = errors->GetBufferSize();
				errormsg = (WCHAR*)errors->GetBufferPointer();
				errors->Release();
			}

			raise(Exception("fx err: " + errormsg));
		}

		g_pNoSpecularTechnique = g_pEffect10->GetTechniqueByName("NoSpecular");

		g_pAmbient = g_pEffect10->GetVariableByName("g_vMaterialAmbient" )->AsVector();
		g_pDiffuse = g_pEffect10->GetVariableByName("g_vMaterialDiffuse" )->AsVector();
		g_pSpecular = g_pEffect10->GetVariableByName("g_vMaterialSpecular" )->AsVector();
		g_pOpacity = g_pEffect10->GetVariableByName("g_fMaterialAlpha" )->AsScalar();
		g_pSpecularPower = g_pEffect10->GetVariableByName("g_nMaterialShininess" )->AsScalar();
		g_pLightColor = g_pEffect10->GetVariableByName("g_vLightColor" )->AsVector();
		g_pLightPosition = g_pEffect10->GetVariableByName("g_vLightPosition" )->AsVector();
		g_pCameraPosition = g_pEffect10->GetVariableByName("g_vCameraPosition" )->AsVector();
		g_pTime = g_pEffect10->GetVariableByName("g_fTime")->AsScalar();
		g_pWorld = g_pEffect10->GetVariableByName("g_mWorld" )->AsMatrix();
		g_pWorldViewProjection = g_pEffect10->GetVariableByName("g_mWorldViewProjection" )->AsMatrix();

		// Define the input layout
		const D3D10_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		} ;
		UINT numElements = sizeof(layout) / sizeof(layout[0]);

		// Create the input layout
		D3D10_PASS_DESC PassDesc;
		g_pNoSpecularTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
		pd3dDevice->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature,
												 PassDesc.IAInputSignatureSize, &g_pVertexLayout);
	}
}
#endif

/*
DependencyClass* PerspectiveCamera::get_Class()
{
	static DependencyClass depclass(typeid(WindowVisual), ContentControl::get_Class());

	static DependencyProperty* properties[] =
	{
		get_EyeProperty(),
		get_AtProperty(),
		get_UpProperty(),
	};

	return &depclass;
}
*/

void Mesh::Render(ManagedRenderContext renderContext)
{
	ASSERT(0);
#if 0
	ASSERT(g_pEffect10);

	ID3D10Device* pd3dDevice = GL::Direct10::get_D3DDevice();

	m_subsetMaterial[0]->m_pTechnique = g_pEffect10->GetTechniqueByName("NoSpecular");

    pd3dDevice->IASetInputLayout(g_pVertexLayout);

	UINT nAttribTableEntries;
	m_pMesh->GetAttributeTable(NULL, &nAttribTableEntries);

	D3DX10_ATTRIBUTE_RANGE* pAttribTable = (D3DX10_ATTRIBUTE_RANGE*)_alloca(sizeof(D3DX10_ATTRIBUTE_RANGE)*nAttribTableEntries);
	m_pMesh->GetAttributeTable(pAttribTable, &nAttribTableEntries);

	for (UINT iAttr = 0; iAttr < nAttribTableEntries; ++iAttr)
	{
		// apply effect parameters for material pAttribTable[iAttr].AttribId

		Material* pMaterial = m_subsetMaterial[iAttr];

		pMaterial->m_pTechnique = g_pNoSpecularTechnique;

		LDraw::vector4f v(pMaterial->m_diffuseColor[0], pMaterial->m_diffuseColor[1], pMaterial->m_diffuseColor[2], 1);

		g_pDiffuse->SetFloatVector(v);
		g_pOpacity->SetFloat(pMaterial->m_alpha);

		D3D10_TECHNIQUE_DESC techDesc;
		pMaterial->m_pTechnique->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			pMaterial->m_pTechnique->GetPassByIndex(p)->Apply(0);

			HRESULT hr = m_pMesh->DrawSubset(iAttr);
			ASSERT(SUCCEEDED(hr));
		}
	}

//	renderContext.m_p->GetRT()->m_device->DrawIndexed(
#endif
}

void MeshContainer::Render(ManagedRenderContext renderContext)
{
}

void Document3D::AddAnimation(Animation* animation)
{
}

////////////

BoxShape::~BoxShape()
{
}

bool BoxShape::IsValid(ImmediateRenderContext* renderContext)
{
	if (renderContext->GetRT()->m_opengl)
	{
		return m_vertexBuffer != nullptr;
	}
	else
	{
		return m_d3d10_VertexBuffer[0] != nullptr;
	}
}

void BoxShape::Create(RenderContext* renderContext, gm::vector3f size)
{
	float rx = size[0]*0.5f;
	float ry = size[1]*0.5f;
	float rz = size[2]*0.5f;

	// Create vertex buffer
	VERTEX_XYZ_NORMAL vertices[24] =
	{
		// front
		gm::vector3f( -rx, -ry, rz), gm::vector3f(0, 0, 1),
		gm::vector3f( rx, -ry, rz), gm::vector3f(0, 0, 1),
		gm::vector3f( -rx, ry, rz), gm::vector3f(0, 0, 1),
		gm::vector3f( rx, ry, rz), gm::vector3f(0, 0, 1),

		// back
		gm::vector3f( rx, -ry, -rz), gm::vector3f(0, 0, -1),
		gm::vector3f( -rx, -ry, -rz), gm::vector3f(0, 0, -1),
		gm::vector3f( rx, ry, -rz), gm::vector3f(0, 0, -1),
		gm::vector3f( -rx, ry, -rz), gm::vector3f(0, 0, -1),

		// right
		gm::vector3f(rx, -ry, rz), gm::vector3f(1, 0, 0),
		gm::vector3f(rx, -ry, -rz), gm::vector3f(1, 0, 0),
		gm::vector3f(rx, ry, rz), gm::vector3f(1, 0, 0),
		gm::vector3f(rx, ry, -rz), gm::vector3f(1, 0, 0),

		// left
		gm::vector3f(-rx, -ry, -rz), gm::vector3f(-1, 0, 0),
		gm::vector3f(-rx, -ry, rz), gm::vector3f(-1, 0, 0),
		gm::vector3f(-rx, ry, -rz), gm::vector3f(-1, 0, 0),
		gm::vector3f(-rx, ry, rz), gm::vector3f(-1, 0, 0),

		// top
		gm::vector3f(-rx, ry, rz), gm::vector3f(0, 1, 0),
		gm::vector3f(rx, ry, rz), gm::vector3f(0, 1, 0),
		gm::vector3f(-rx, ry, -rz), gm::vector3f(0, 1, 0),
		gm::vector3f(rx, ry, -rz), gm::vector3f(0, 1, 0),

		// bottom
		gm::vector3f(rx, -ry, -rz), gm::vector3f(0, -1, 0),
		gm::vector3f(rx, -ry, rz), gm::vector3f(0, -1, 0),
		gm::vector3f(-rx, -ry, rz), gm::vector3f(0, -1, 0),
		gm::vector3f(-rx, -ry, -rz), gm::vector3f(0, -1, 0),
	};

	uint32 indices[36] =
	{
		// front
		0+0, 0+1, 0+2,
		0+1, 0+3, 0+2,

		// back
		4+0, 4+1, 4+2,
		4+1, 4+3, 4+2,

		// right
		8+0, 8+1, 8+2,
		8+1, 8+3, 8+2,

		// left
		12+0, 12+1, 12+2,
		12+1, 12+3, 12+2,

		// top
		16+0, 16+1, 16+2,
		16+1, 16+3, 16+2,

		// bottom
		20+0, 20+1, 20+2,
		20+1, 20+3, 20+2,
	};

	Graphics::OpenGL_I* pGL = renderContext->GetRT()->m_opengl;

	if (pGL)
	{
		ASSERT(m_vertexBuffer == nullptr);
		{
			/*
			VERTEX_XYZ_NORMAL vertices[4*4];

			vertices[0].position = LDraw::vector3f(-s[0]/2, -s[1]/2, s[2]/2);
			vertices[0].normal = LDraw::vector3f(0, 0, 1);
			vertices[1].position = LDraw::vector3f(s[0]/2, -s[1]/2, s[2]/2);
			vertices[1].normal = LDraw::vector3f(0, 0, 1);
			vertices[2].position = LDraw::vector3f(s[0]/2, s[1]/2, s[2]/2);
			vertices[2].normal = LDraw::vector3f(0, 0, 1);
			vertices[3].position = LDraw::vector3f(-s[0]/2, s[1]/2, s[2]/2);
			vertices[3].normal = LDraw::vector3f(0, 0, 1);
*/
			m_vertexBuffer = pGL->CreateVertexBuffer(sizeof(vertices), vertices, GL_STATIC_DRAW);

		//	pDC->m_pGraphics3D->BindBuffer(GL_ARRAY_BUFFER, m_buffer);
		//	pDC->m_pGraphics3D->BufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_XYZ_NORMAL)*4*4, vertices, 0);

			Graphics::VertexDeclElement elements[] =
			{
				{"POSITION", 0, 0, Graphics::DECLTYPE_FLOAT3, 0},
				{"NORMAL", 0, 12, Graphics::DECLTYPE_FLOAT3, 0},
			};

			m_vertexDeclaration = pGL->CreateVertexDeclaration(elements, 2, 0/*shader*/);

			m_indexBuffer = pGL->CreateIndexBuffer(GL_UNSIGNED_INT, sizeof(indices), indices);
		}
	}
	else
	{
		ASSERT(m_d3d10_VertexBuffer[0] == NULL);

		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(vertices);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[0]);

		// Texture coordinates
		if (true)
		{
			gm::vector2f vertices[] =
			{
				// front
				gm::vector2f( 0.0f, 0.0f),
				gm::vector2f( 1.0f, 0.0f),
				gm::vector2f( 0.0f, 1.0f),
				gm::vector2f( 1.0f, 1.0f),

				// back
				gm::vector2f( 0.0f, 0.0f),
				gm::vector2f( 1.0f, 0.0f),
				gm::vector2f( 0.0f, 1.0f),
				gm::vector2f( 1.0f, 1.0f),

				// right
				gm::vector2f( 0.0f, 0.0f),
				gm::vector2f( 1.0f, 0.0f),
				gm::vector2f( 0.0f, 1.0f),
				gm::vector2f( 1.0f, 1.0f),

				// left
				gm::vector2f( 0.0f, 0.0f),
				gm::vector2f( 1.0f, 0.0f),
				gm::vector2f( 0.0f, 1.0f),
				gm::vector2f( 1.0f, 1.0f),

				// top
				gm::vector2f( 0.0f, 0.0f),
				gm::vector2f( 1.0f, 0.0f),
				gm::vector2f( 0.0f, 1.0f),
				gm::vector2f( 1.0f, 1.0f),

				// bottom
				gm::vector2f( 0.0f, 0.0f),
				gm::vector2f( 1.0f, 0.0f),
				gm::vector2f( 0.0f, 1.0f),
				gm::vector2f( 1.0f, 1.0f),
			};

			D3D10_BUFFER_DESC bd;
			bd.Usage = D3D10_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(vertices);
			bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;
			D3D10_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = vertices;
			renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[1]);
		}

		if (m_d3d10_IndexBuffer == nullptr)
		{
			D3D10_BUFFER_DESC bd;
			bd.Usage = D3D10_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(indices);
			bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;
			D3D10_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = indices;
			renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_IndexBuffer);
		}
	}
}

void BoxShape::Draw(ImmediateRenderContext* renderContext)
{
	Graphics::OpenGL_I* pGL = renderContext->GetRT()->m_opengl;

	if (pGL)
	{
		pGL->SetVertexDeclaration(m_vertexDeclaration);

		pGL->SetIndexBuffer(m_indexBuffer, 0);
		pGL->SetVertexBuffer(0, m_vertexBuffer, 0, sizeof(VERTEX_XYZ_NORMAL));
	//	pDC->m_pGraphics3D->InterleavedArrays(GL_N3F_V3F, 0, NULL);
		pGL->SetPrimitiveTopology(GL_TRIANGLES);
		pGL->DrawIndexed(0, 23, 36);
	//	pDC->m_pGraphics3D->DrawArrays(GL_TRIANGLE_FAN, 4, 4);
	//	pDC->m_pGraphics3D->DrawArrays(GL_TRIANGLE_FAN, 8, 4);
	//	pDC->m_pGraphics3D->DrawArrays(GL_TRIANGLE_FAN, 12, 4);
	}
	else
	{
		{
			UINT stride[2] = { sizeof(VERTEX_XYZ_NORMAL), sizeof(gm::vector2f) };
			UINT offset[2] = {0,0};
			renderContext->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 2, m_d3d10_VertexBuffer, stride, offset);
		}
		/*
		{
			UINT stride = sizeof(LDraw::vector2f);
			UINT offset = 0;
			renderContext->GetRT()->m_device->IASetVertexBuffers(1, 1, &m_d3d10_TexCoordBuffer, &stride, &offset);
		}
		*/

		ASSERT(m_d3d10_IndexBuffer);
		renderContext->GetRT()->m_d3d10->m_device->IASetIndexBuffer(m_d3d10_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		renderContext->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	renderContext->GetRT()->m_d3d10->m_device->DrawIndexed(36, 0/*StartIndexLocation*/, 0/*BaseVertexLocation*/);
		renderContext->GetRT()->m_d3d10->m_device->DrawIndexed(6*5, 0/*StartIndexLocation*/, 0/*BaseVertexLocation*/);

//		renderContext->GetRT()->m_gi->SetPrimitiveTopology(GL_TRIANGLES);

//		renderContext->GetRT()->m_gi->DrawIndexed(36, 0/*StartIndexLocation*/, 0/*BaseVertexLocation*/);
	}
}

SphereShape::SphereShape()
{
	m_d3d10_VertexBuffer[0] = NULL;
}

SkySphereShape::SkySphereShape()
{
	m_d3d10_VertexBuffer[0] = NULL;
}

SkySphereShape::~SkySphereShape()
{
}

bool SkySphereShape::IsValid(ImmediateRenderContext* renderContext)
{
	return m_d3d10_VertexBuffer[0] != nullptr;
}

void SkySphereShape::Destroy()
{
	if (m_d3d10_VertexBuffer[0])
	{
		m_d3d10_VertexBuffer[0]->Release();
		m_d3d10_VertexBuffer[0] = nullptr;
	}
}

void SkySphereShape::Create(RenderContext* renderContext, double radius, int slices, vector<float>& radians, vector<gm::vector4f>& colors, int nsign)
{
	m_slices = slices;
	m_stacks = radians.GetSize()-1;

	__try
	{

#if 0
	   drho = M_PI / (GLfloat) stacks;
	   dtheta = 2.0 * M_PI / (GLfloat) slices;

		ds = 1.0 / slices;
		dt = 1.0 / stacks;
		t = 1.0;  /* because loop now runs from 0 */
	/*
		if (qobj->TextureFlag) {
			imin = 0;
			imax = stacks;
		}
		else
	*/	{
			imin = 1;
			imax = stacks-1;
		}
#endif
		VERTEX_XYZ_COLOR* vertices = (VERTEX_XYZ_COLOR*)_malloca((m_stacks)*(slices+1)*2*sizeof(VERTEX_XYZ_COLOR));
		VERTEX_XYZ_COLOR* vertex = vertices;

		for (size_t n = 0; n < radians.GetSize()-1; ++n)
		{
			float radian1 = radians[n];
			float radian2 = radians[n+1];

			gm::vector4f color1 = colors[n];
			gm::vector4f color2 = colors[n+1];

			float cos_rho = cos(radian1);
			float sin_rho = sin(radian1);

			float cos_rho2 = cos(radian2);
			float sin_rho2 = sin(radian2);

			float rho = radian1;

			for (int m = 0; m <= slices; ++m)
			{
				float theta = (m == slices)? 0 : ((float)m / slices) * M_PI*2;

				float x, y, z;

				z = -sin(theta) * sin_rho;
				x = cos(theta) * sin_rho;
				y = nsign * cos_rho;
			//	pG->glColorf(color1[0], color1[1], color1[2]);
			//	pG->glVertexf( x*radius, y*radius, z*radius );
				vertex->color = color1;
				vertex->position = gm::vector3f(x*radius, y*radius, z*radius);
				++vertex;

				z = -sin(theta) * sin_rho2;
				x = cos(theta) * sin_rho2;
				y = nsign * cos_rho2;
			//	pG->glColorf(color2[0], color2[1], color2[2]);
			//	pG->glVertexf( x*radius, y*radius, z*radius );
				vertex->color = color2;
				vertex->position = gm::vector3f(x*radius, y*radius, z*radius);
				++vertex;
			}
		}

		ASSERT(m_d3d10_VertexBuffer[0] == NULL);
		{
		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = (vertex - vertices)*sizeof(VERTEX_XYZ_COLOR);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[0]);
		}

		if (m_inputLayout == nullptr)
		{
			// Define the input layout
			D3D10_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }, 
			};

			m_d3d10_technique = renderContext->GetRT()->m_d3d10->m_d3d10_effect->GetTechniqueByName("SolidColorTechnique");

			// Create the input layout
			D3DX10_PASS_DESC PassDesc;
			m_d3d10_technique->GetPassByIndex(0)->GetDesc(&PassDesc);
			HRESULT hr = renderContext->GetRT()->m_d3d10->m_device->CreateInputLayout(layout, _countof(layout), PassDesc.pIAInputSignature, 
					PassDesc.IAInputSignatureSize, &m_inputLayout);
			ASSERT(SUCCEEDED(hr));
		}

		_freea(vertices);
	}
	__except (GetExceptionCode() == STATUS_STACK_OVERFLOW)
	{
		_resetstkoflw();
	}
}

void SkySphereShape::Draw(ImmediateRenderContext* renderContext)
{
	UINT stride[1] = { sizeof(VERTEX_XYZ_COLOR)};
	UINT offset[1] = { 0 };
	renderContext->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 1, m_d3d10_VertexBuffer, stride, offset);
	renderContext->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	renderContext->GetRT()->m_d3d10->m_device->IASetInputLayout(m_inputLayout);

	renderContext->GetRT()->m_d3d10->m_d3d10_modelViewVariable->SetMatrix(renderContext->modelViewMatrix());
	renderContext->GetRT()->m_d3d10->m_d3d10_projectionVariable->SetMatrix(renderContext->projectionMatrix());
	renderContext->GetRT()->m_d3d10->m_d3d10_modelViewProjectionVariable->SetMatrix(renderContext->modelViewProjectionMatrix());

	m_d3d10_technique->GetPassByIndex(0)->Apply(0);

	int count = (m_slices+1)*2;
	int start = 0;
	for (size_t i = 0; i < m_stacks; ++i)
	{
		renderContext->GetRT()->m_d3d10->m_device->Draw(count, start);
		start += count;
	}
}

//////////////////////////////

/*
void Lines::Create(RenderContext* renderContext, LDraw::vector3f* points, uint* indices, uint nindices, LDraw::vector3f color)
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
}
*/

///////////////////////////////

//////////////////////////////

CylinderShape::~CylinderShape()
{
}

void CylinderShape::Create(RenderContext* renderContext, float bottomRadius, float topRadius, float height)
{
	uint slices = 40;

	uint nvertices = slices*2;
	float stepradian = (M_PI/180)*(360.0f/nvertices);
	VERTEX_XYZ_NORMAL* vertices = (VERTEX_XYZ_NORMAL*)_alloca(sizeof(VERTEX_XYZ_NORMAL)*nvertices);
	uint nvertex = 0;

	float normy = (bottomRadius-topRadius)/height;

	for (size_t i = 0; i < nvertices; i++)
	{
		float radian = stepradian * i;

		float normx = cos(radian);
		float normz = sin(radian);

		if (i & 1)
		{
			float x = normx * topRadius;
			float z = normz * topRadius;

			vertices[nvertex].position[0] = x;
			vertices[nvertex].position[1] = height/2;
			vertices[nvertex].position[2] = z;
			vertices[nvertex].normal[0] = normx;
			vertices[nvertex].normal[1] = normz;
			vertices[nvertex].normal[2] = normz;
			vertices[nvertex].normal.normalize();
		}
		else
		{
			float x = normx * bottomRadius;
			float z = normz * bottomRadius;

			vertices[nvertex].position[0] = x;
			vertices[nvertex].position[1] = -height/2;
			vertices[nvertex].position[2] = z;
			vertices[nvertex].normal[0] = normx;
			vertices[nvertex].normal[1] = normz;
			vertices[nvertex].normal[2] = normy;
			vertices[nvertex].normal.normalize();
		}
		++nvertex;
	}

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_XYZ_NORMAL) * nvertices;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer);

	m_nvertices = nvertices;
}

bool CylinderShape::IsValid(ImmediateRenderContext* renderContext)
{
	return m_d3d10_VertexBuffer != nullptr;
}

void CylinderShape::Draw(ImmediateRenderContext* renderContext)
{
	UINT stride = sizeof(VERTEX_XYZ_NORMAL);
	UINT offset = 0;
	renderContext->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 1, &m_d3d10_VertexBuffer, &stride, &offset);
//	renderContext->GetRT()->m_device->IASetIndexBuffer(m_d3d10_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	renderContext->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	renderContext->GetRT()->m_d3d10->m_device->Draw(m_nvertices, 0/*StartVertexLocation*/);
}

DiskShape::DiskShape()
{
	m_d3d10_VertexBuffer = nullptr;
	m_d3d10_IndexBuffer = nullptr;
}

void DiskShape::Draw(ImmediateRenderContext* renderContext)
{
	ASSERT(0);
}

bool DiskShape::IsValid(ImmediateRenderContext* renderContext)
{
	ASSERT(0);
	return false;
}

Rectangle2DShape::Rectangle2DShape()
{
	m_d3d10_VertexBuffer[0] = nullptr;
	m_d3d10_VertexBuffer[1] = nullptr;
}

Rectangle2DShape::~Rectangle2DShape()
{
}

void Rectangle2DShape::Create(RenderContext* renderContext, gm::vector2f size)
{
	ASSERT(m_d3d10_VertexBuffer[0] == nullptr);

	float rx = size[0]*0.5f;
	float ry = size[1]*0.5f;

	// Create vertex buffer
	VERTEX_XYZ_NORMAL vertices[] =
	{
		gm::vector3f( rx, ry, 0), gm::vector3f(0, 0, 1),
		gm::vector3f( rx, -ry, 0), gm::vector3f(0, 0, 1),
		gm::vector3f( -rx, -ry, 0), gm::vector3f(0, 0, 1),
		gm::vector3f( -rx, ry, 0), gm::vector3f(0, 0, 1),
	};

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_XYZ_NORMAL) * _countof(vertices);
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[0]);

	// Texture coordinates
	if (true)
	{
		gm::vector2f vertices[] =
		{
			// front
			gm::vector2f( 0.0f, 0.0f),
			gm::vector2f( 1.0f, 0.0f),
			gm::vector2f( 1.0f, 1.0f),
			gm::vector2f( 0.0f, 1.0f),

			// back
			gm::vector2f( 0.0f, 0.0f),
			gm::vector2f( 1.0f, 0.0f),
			gm::vector2f( 1.0f, 1.0f),
			gm::vector2f( 0.0f, 1.0f),

			// left
			gm::vector2f( 0.0f, 0.0f),
			gm::vector2f( 1.0f, 0.0f),
			gm::vector2f( 1.0f, 1.0f),
			gm::vector2f( 0.0f, 1.0f),

			// right
			gm::vector2f( 0.0f, 0.0f),
			gm::vector2f( 1.0f, 0.0f),
			gm::vector2f( 1.0f, 1.0f),
			gm::vector2f( 0.0f, 1.0f),

			// top
			gm::vector2f( 0.0f, 0.0f),
			gm::vector2f( 1.0f, 0.0f),
			gm::vector2f( 1.0f, 1.0f),
			gm::vector2f( 0.0f, 1.0f),

			// bottom
			gm::vector2f( 0.0f, 0.0f),
			gm::vector2f( 1.0f, 0.0f),
			gm::vector2f( 1.0f, 1.0f),
			gm::vector2f( 0.0f, 1.0f),
		};

		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(gm::vector2f) * _countof(vertices);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[1]);
	}
}

bool Rectangle2DShape::IsValid(ImmediateRenderContext* renderContext)
{
	return m_d3d10_VertexBuffer[0] != NULL;
}

void Rectangle2DShape::Draw(ImmediateRenderContext* renderContext)
{
	UINT stride[2] = { sizeof(VERTEX_XYZ_NORMAL), sizeof(gm::vector2f) };
	UINT offset[2] = {0,0};
	renderContext->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 2, m_d3d10_VertexBuffer, stride, offset);

	renderContext->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	renderContext->GetRT()->m_d3d10->m_device->Draw(4/*VertexCount*/, 0/*StartVertexLocation*/);
}

IndexedLines::IndexedLines()
{
	m_d3d10_VertexBuffer = nullptr;
	m_d3d10_IndexBuffer = nullptr;
}

IndexedLines::~IndexedLines()
{
	if (m_d3d10_VertexBuffer)
	{
//		m_d3d10_VertexBuffer->Release();
	}
}

bool IndexedLines::IsValid(ImmediateRenderContext* renderContext)
{
	return m_d3d10_VertexBuffer != nullptr;
}

void IndexedLines::Create(RenderContext* renderContext, gm::vector3f* points, uint nvertices, uint* indices, uint nindices, gm::vector4f color)
{
	m_nvertices = nvertices;
	m_nindices = nindices;

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

	ASSERT(m_d3d10_VertexBuffer == nullptr);
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

	ASSERT(m_d3d10_IndexBuffer == nullptr);
	{
		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = nindices*sizeof(uint);
		bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = indices;
		renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_IndexBuffer);
	}

	_freea(vertices);
}

void IndexedLines::Draw(ImmediateRenderContext* renderContext)
{
	UINT stride[1] = { sizeof(VERTEX_XYZ_COLOR)};
	UINT offset[1] = { 0 };
	renderContext->GetRT()->m_d3d10->m_device->IASetIndexBuffer(m_d3d10_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	renderContext->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 1, &m_d3d10_VertexBuffer, stride, offset);
	renderContext->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
	renderContext->GetRT()->m_d3d10->m_device->IASetInputLayout(renderContext->GetRT()->m_d3d10->m_solidColorInputLayout);

	renderContext->GetRT()->m_d3d10->m_d3d10_modelViewVariable->SetMatrix(renderContext->modelViewMatrix());
	renderContext->GetRT()->m_d3d10->m_d3d10_projectionVariable->SetMatrix(renderContext->projectionMatrix());
	renderContext->GetRT()->m_d3d10->m_d3d10_modelViewProjectionVariable->SetMatrix(renderContext->modelViewProjectionMatrix());

	renderContext->GetRT()->m_d3d10->m_solidColorTechnique->GetPassByIndex(0)->Apply(0);

	renderContext->GetRT()->m_d3d10->m_device1->DrawIndexed(m_nindices, 0, 0);
}

}	// Media3D

BitmapShape::BitmapShape()
{
	m_d3d10_VertexBuffer = nullptr;
	m_bitmap = nullptr;
}

void BitmapShape::Create(Graphics::RenderTarget* rt, Graphics::Bitmap* bitmap, gm::RectF dstRect, gm::RectF srcRect)
{
	m_bitmap = bitmap;

	// Create vertex buffer
	Graphics::VERTEX_XYZ_T2 vertices[4] =
	{
		// front
		gm::vector3f(dstRect.GetLeft(), dstRect.GetTop(), 0), gm::vector2f(0, 0),
		gm::vector3f(dstRect.GetRight(), dstRect.GetTop(), 0), gm::vector2f(1, 0),
		gm::vector3f(dstRect.GetLeft(), dstRect.GetBottom(), 0), gm::vector2f(0, 1),
		gm::vector3f(dstRect.GetRight(), dstRect.GetBottom(), 0), gm::vector2f(1, 1),
	};

	ASSERT(m_d3d10_VertexBuffer == nullptr);

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(vertices);
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	rt->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer);
}

bool BitmapShape::IsValid(ImmediateRenderContext* renderContext)
{
	return m_d3d10_VertexBuffer != nullptr;
}

void BitmapShape::Draw(ImmediateRenderContext* renderContext)
{
	if (m_bitmap->m_d3d10_shaderResourceView == nullptr)
		return;

	ASSERT(m_bitmap->m_d3d10_shaderResourceView);

	renderContext->GetRT()->m_d3d10->m_device->IASetInputLayout(Graphics::Direct10::s.m_vertexLayout0);

	UINT stride = sizeof(Graphics::VERTEX_XYZ_T2);
	UINT offset = 0;
	renderContext->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 1, &m_d3d10_VertexBuffer, &stride, &offset);
	renderContext->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	/*
	LDraw::matrix4f xform =
		LDraw::matrix4f::getTranslate(dstRect.X, dstRect.Y, 0) *
		LDraw::matrix4f::getScale(dstRect.Width, dstRect.Height, 1);
*/
//	GL::Direct10::s.m_modelViewVariable->SetMatrix(renderContext->modelViewMatrix());
	Graphics::Direct10::s.m_modelViewProjectionVariable->SetMatrix(renderContext->modelViewProjectionMatrix());

//	LDraw::matrix4f textureMatrix = LDraw::matrix4f::getIdentity();
	/*
		LDraw::matrix4f::getTranslate(-srcRect.X, -srcRect.Y) *
		LDraw::matrix4f::getScale(srcRect.Width / bitmap->GetWidth(), srcRect.Height / bitmap->GetHeight());
*/

	Graphics::Direct10::s.m_texture0Variable->SetResource(m_bitmap->m_d3d10_shaderResourceView);

	Graphics::Direct10::s.m_textureMatrix0Variable->SetMatrix((float*)gm::matrix4f::getIdentity());

#if 0
	if (args)
	{
		m_colorTransformVariable->SetMatrix((float*)args->m_colorTransform.m_transform);
		m_colorTranslateVariable->SetFloatVector((float*)args->m_colorTransform.m_translate);

		D3D10_TECHNIQUE_DESC techDesc;
		HRESULT hr = m_RenderTextureColorMatrixTechnique->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			m_RenderTextureColorMatrixTechnique->GetPassByIndex(p)->Apply(0);

			rt->m_d3d10->m_device->Draw(
				4, // VertexCount
				0 // StartVertexLocation
				);
		}
	}
	else
#endif
	{
		D3DX10_TECHNIQUE_DESC techDesc;
		Graphics::Direct10::s.m_RenderTextureTechnique->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Graphics::Direct10::s.m_RenderTextureTechnique->GetPassByIndex(p)->Apply(0);

			renderContext->GetRT()->m_d3d10->m_device1->Draw(
				4, // VertexCount
				0 // StartVertexLocation
				);
		}
	}
}

/*
//--------------------------------------------------------------------------------------
// This function loads the mesh and ensures the mesh has normals; it also optimizes the 
// mesh for the graphics card's vertex cache, which improves performance by organizing 
// the internal triangle list for less cache misses.
//--------------------------------------------------------------------------------------
HRESULT LoadMesh( IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh )
{
    ID3DXMesh* pMesh = NULL;
    WCHAR str[MAX_PATH];
    HRESULT hr;

    // Load the mesh with D3DX and get back a ID3DXMesh*.  For this
    // sample we'll ignore the X file's embedded materials since we know 
    // exactly the model we're loading.  See the mesh samples such as
    // "OptimizedMesh" for a more generic mesh loading example.
    V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, strFileName ) );
    V_RETURN( D3DXLoadMeshFromX( str, D3DXMESH_MANAGED, pd3dDevice, NULL, NULL, NULL, NULL, &pMesh ) );

    DWORD* rgdwAdjacency = NULL;

    // Make sure there are normals which are required for lighting
    if( !( pMesh->GetFVF() & D3DFVF_NORMAL ) )
    {
        ID3DXMesh* pTempMesh;
        V( pMesh->CloneMeshFVF( pMesh->GetOptions(),
                                pMesh->GetFVF() | D3DFVF_NORMAL,
                                pd3dDevice, &pTempMesh ) );
        V( D3DXComputeNormals( pTempMesh, NULL ) );

        SAFE_RELEASE( pMesh );
        pMesh = pTempMesh;
    }

    // Optimize the mesh for this graphics card's vertex cache 
    // so when rendering the mesh's triangle list the vertices will 
    // cache hit more often so it won't have to re-execute the vertex shader 
    // on those vertices so it will improve perf.     
    rgdwAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
    if( rgdwAdjacency == NULL )
        return E_OUTOFMEMORY;
    V( pMesh->GenerateAdjacency( 1e-6f, rgdwAdjacency ) );
    V( pMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE, rgdwAdjacency, NULL, NULL, NULL ) );
    delete []rgdwAdjacency;

    *ppMesh = pMesh;

    return S_OK;
}
*/

}	// Gui
}	// System
