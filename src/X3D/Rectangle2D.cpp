#include "stdafx.h"
#include "X3D2.h"
#include "Rectangle2D.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(Rectangle2D, SFVec2f, size, inputOutput, Vec2f(2,2))

//	static TypedX3DFieldDefinition<type>(L#fieldname, SAIFieldAccess_inputOutput, offsetof(Rectangle2D, m_size)),

NodeType* Rectangle2D::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_sizeFieldDef()
//		X3DFieldDefinition(WSTR("solid"), SAIFieldAccess_inputOutput, offsetof(Rectangle2D, m_solid)),
		/*
			SFVec2f []       size     2 2  (0,8)
			SFBool  []       solid    FALSE
		 */
	};

	static NodeType nodeType(WSTR("Rectangle2D"), typeid(Rectangle2D), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* Rectangle2D::nodeType(GetNodeType());

Rectangle2D::Rectangle2D() : X3DGeometryNode(GetNodeType()),
	m_size(new SFVec2f(get_sizeFieldDef(), this))
{
}

void Rectangle2D::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* textureNode)
{
	if (!m_shape.IsValid(pDC->m_renderContext))
	{
		m_shape.Create(pDC->m_renderContext, getSize());
	}

	m_shape.Draw(pDC->m_renderContext);

#if 0
	pDC->m_pGraphics3D->glBegin(GL_TRIANGLES);

	{
		pDC->m_pGraphics3D->glTexCoordf(0, 0);
		pDC->m_pGraphics3D->glVertexf(-m_size->m_value[0]/2, m_size->m_value[1]/2, 0);

		pDC->m_pGraphics3D->glTexCoordf(1, 0);
		pDC->m_pGraphics3D->glVertexf(m_size->m_value[0]/2, m_size->m_value[1]/2, 0);

		pDC->m_pGraphics3D->glTexCoordf(1, 1);
		pDC->m_pGraphics3D->glVertexf(m_size->m_value[0]/2, -m_size->m_value[1]/2, 0);
	}

	{
		pDC->m_pGraphics3D->glTexCoordf(1, 1);
		pDC->m_pGraphics3D->glVertexf(m_size->m_value[0]/2, -m_size->m_value[1]/2, 0);

		pDC->m_pGraphics3D->glTexCoordf(0, 1);
		pDC->m_pGraphics3D->glVertexf(-m_size->m_value[0]/2, -m_size->m_value[1]/2, 0);

		pDC->m_pGraphics3D->glTexCoordf(0, 0);
		pDC->m_pGraphics3D->glVertexf(-m_size->m_value[0]/2, m_size->m_value[1]/2, 0);
	}

	pDC->m_pGraphics3D->glEnd();

#if 0
	pDC->m_pGraphics3D->glBegin(GL_QUADS);

	pDC->m_pGraphics3D->glTexCoord(0, 0);
	pDC->m_pGraphics3D->glVertex(-m_size->m_value[0]/2, m_size->m_value[1]/2, 0);

	pDC->m_pGraphics3D->glTexCoord(1, 0);
	pDC->m_pGraphics3D->glVertex(m_size->m_value[0]/2, m_size->m_value[1]/2, 0);

	pDC->m_pGraphics3D->glTexCoord(1, 1);
	pDC->m_pGraphics3D->glVertex(m_size->m_value[0]/2, -m_size->m_value[1]/2, 0);

	pDC->m_pGraphics3D->glTexCoord(0, 1);
	pDC->m_pGraphics3D->glVertex(-m_size->m_value[0]/2, -m_size->m_value[1]/2, 0);

	pDC->m_pGraphics3D->glEnd();

#endif

	/*

	Rectf(pDC,
		-m_size->m_value[0]/2, -m_size->m_value[1]/2,
		m_size->m_value[0]/2, m_size->m_value[1]/2);
*/
#if 0
	glBegin(GL_QUADS);

	SFVec3f* size = static_cast<SFVec3f*>(m_size->m_value);
	gmVector3 s = size->m_v;

	// front (cw)
	/*
	glVertex3d(-m_boxSize[0]/2, -m_boxSize[1]/2, m_boxSize[2]/2);
	glVertex3d(m_boxSize[0]/2, -m_boxSize[1]/2, m_boxSize[2]/2);
	glVertex3d(m_boxSize[0]/2, m_boxSize[1]/2, m_boxSize[2]/2);
	glVertex3d(-m_boxSize[0]/2, m_boxSize[1]/2, m_boxSize[2]/2);
	*/

	// front (ccw)
	lglNormal(	gmVector3(-s[0]/2, -s[1]/2, s[2]/2),
					gmVector3(-s[0]/2, s[1]/2, s[2]/2),
					gmVector3(s[0]/2, s[1]/2, s[2]/2));

	glVertex3d(-s[0]/2, -s[1]/2, s[2]/2);
	glVertex3d(-s[0]/2, s[1]/2, s[2]/2);
	glVertex3d(s[0]/2, s[1]/2, s[2]/2);
	glVertex3d(s[0]/2, -s[1]/2, s[2]/2);

	// left side
	lglNormal(	gmVector3(-s[0]/2, -s[1]/2, s[2]/2),
					gmVector3(-s[0]/2, -s[1]/2, -s[2]/2),
					gmVector3(-s[0]/2, s[1]/2, -s[2]/2));

	glVertex3d(-s[0]/2, -s[1]/2, s[2]/2);
	glVertex3d(-s[0]/2, -s[1]/2, -s[2]/2);
	glVertex3d(-s[0]/2, s[1]/2, -s[2]/2);
	glVertex3d(-s[0]/2, s[1]/2, s[2]/2);

	glEnd();
#endif
#endif
}

}	// x3d
}
