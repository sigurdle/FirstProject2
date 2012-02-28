#include "stdafx.h"
#include "X3D2.h"
#include "Cylinder.h"

namespace System
{
namespace LDraw
{
void gluDisk(Graphics::Graphics3D* pG, double innerRadius, double outerRadius, int slices, int loops);
void gluCylinder(Graphics::Graphics3D* pG, double baseRadius, double topRadius, double height, int slices, int stacks);
}

namespace x3d
{

IMP_X3DFIELD3(Cylinder, SFFloat, height, initializeOnly, 2.0f, 0, FLT_MAX)
IMP_X3DFIELD3(Cylinder, SFFloat, radius, initializeOnly, 1.0f, 0, FLT_MAX)
IMP_X3DFIELD1(Cylinder, SFBool, bottom, initializeOnly, true)
IMP_X3DFIELD1(Cylinder, SFBool, top, initializeOnly, true)
IMP_X3DFIELD1(Cylinder, SFBool, side, initializeOnly, true)

// static
NodeType* Cylinder::GetNodeType()
{
	static X3DFieldDefinition* CylinderFields[] =
	{
		get_bottomFieldDef(),
		get_heightFieldDef(),
		get_radiusFieldDef(),
		get_sideFieldDef(),
		get_topFieldDef(),
	/*
		SFBool  [] bottom TRUE
		SFFloat [] height 2    (0,8)
		SFFloat [] radius 1    (0,8)
		SFBool  [] side   TRUE
		SFBool  [] top    TRUE
	  */
	};

	static NodeType nodeType(WSTR("Cylinder"), typeid(Cylinder), CylinderFields, _countof(CylinderFields), baseClass::GetNodeType());
	return &nodeType;
}

Cylinder::Cylinder() : X3DGeometryNode(GetNodeType()),
	m_radius(new SFFloat(get_radiusFieldDef(), this)),
	m_height(new SFFloat(get_heightFieldDef(), this)),
	m_bottom(new SFBool(get_bottomFieldDef(), this)),
	m_top(new SFBool(get_topFieldDef(), this)),
	m_side(new SFBool(get_sideFieldDef(), this))
{
}

void Cylinder::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
#if 0
	if (m_d3d10_VertexBuffer == NULL)
	{
		float height = getHeight();
		float topRadius = getRadius();
		float bottomRadius = topRadius;

		int slices = 40;

		uint nvertices = slices*2;
		float stepradian = (M_PI/180)*(360.0f/nvertices);
		VERTEX_XYZ_NORMAL* vertices = (VERTEX_XYZ_NORMAL*)_alloca(sizeof(VERTEX_XYZ_NORMAL)*nvertices);
		uint nvertex = 0;

		for (uint i = 0; i < nvertices; i++)
		{
			float radian = stepradian * i;

			float normx = cos(radian);
			float normy = sin(radian);

			float x = normx * topRadius;
			float y = normy * topRadius;

			vertices[nvertex].position[0] = x;
			vertices[nvertex].position[2] = y;
			vertices[nvertex].normal[0] = normx;
			vertices[nvertex].normal[1] = 0;
			vertices[nvertex].normal[2] = normy;

			if (i & 1)
			{
				vertices[nvertex].position[1] = -height/2;
			}
			else
			{
				vertices[nvertex].position[1] = height/2;
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
		pDC->m_renderContext->GetRT()->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer);

		m_nvertices = nvertices;
	}

#if 0
	if (m_d3d10_IndexBuffer == NULL)
	{
		uint32 indices[] =
		{
			// front
			0, 2, 1,
			0, 3, 2,

			// back
			4, 6, 5,
			4, 7, 6,

			// left
			8+0, 8+2, 8+1,
			8+0, 8+3, 8+2,
		};

		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(uint32)*_countof(indices);
		bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = indices;
		pDC->m_renderContext->GetRT()->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_IndexBuffer);
	}
#endif
#endif

	if (!m_shape.IsValid(pDC->m_renderContext))
	{
		m_shape.Create(pDC->m_renderContext, getRadius(), getRadius(), getHeight());
	}

	m_shape.Draw(pDC->m_renderContext);

#if 0

//	SFFloat* radius = static_cast<SFFloat*>(m_radius);
//	SFFloat* height = static_cast<SFFloat*>(m_height);

	pDC->m_pGraphics3D->PushMatrix();

	pDC->m_pGraphics3D->glRotatef(90.0, 1.0, 0.0, 0.0);
	pDC->m_pGraphics3D->glTranslatef(0, 0, -m_height->m_value/2);

#if 0
	GLUquadricObj* q = gluNewQuadric();
#endif

	if (m_top->getValue())
	{
		LDraw::gluDisk(pDC->m_pGraphics3D, /*q,*/ 0, m_radius->m_value, 20, 1);
	}

	if (m_side->getValue())
	{
		LDraw::gluCylinder(pDC->m_pGraphics3D, /*q,*/ m_radius->m_value, m_radius->m_value, m_height->m_value, 20, 20);
	}

	if (m_bottom->getValue())
	{
		pDC->m_pGraphics3D->glTranslatef(0, 0, m_height->m_value);
		LDraw::gluDisk(pDC->m_pGraphics3D, /*q,*/ 0, m_radius->m_value, 20, 1);
	}

#if 0
	gluDeleteQuadric(q);
#endif

	pDC->m_pGraphics3D->PopMatrix();
#endif
}

/*
void Cylinder::CreateActor(NxScene* gScene, D3DXMATRIX modelView)
{
	ASSERT(0);
}
*/

}	// x3d
}	// System
