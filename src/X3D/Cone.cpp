#include "stdafx.h"
#include "X3D2.h"
#include "Cone.h"

namespace System
{
	/*
namespace LDraw
{
void X3DEXT gluCylinder(LDraw::Graphics3D* pG, double baseRadius, double topRadius, double height, int slices, int stacks);
}
*/

namespace x3d
{

IMP_X3DFIELD3(Cone, SFFloat, bottomRadius, initializeOnly, 1.0f, 0, FLT_MAX)
IMP_X3DFIELD3(Cone, SFFloat, height, initializeOnly, 2.0f, 0, FLT_MAX)

NodeType* Cone::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_bottomRadiusFieldDef(),
		get_heightFieldDef(),
		/*
		SFBool  [] bottom       TRUE
		SFFloat [] bottomRadius 1    (0,8)
		SFFloat [] height       2    (0,8)
		SFBool  [] side         TRUE
		*/
	};

	static NodeType nodeType(WSTR("Cone"), typeid(Cone), fields, _countof(fields), X3DGeometryNode::GetNodeType());
	return &nodeType;
}

NodeType* Cone::nodeType(GetNodeType());

Cone::Cone() : X3DGeometryNode(GetNodeType()),

	m_bottomRadius(new SFFloat(this, 1.0f)),
	m_height(new SFFloat(this, 2.0f))
{
}

void Cone::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
	if (!m_shape.IsValid(pDC->m_renderContext))
	{
		float height = getHeight();
		float bottomRadius = getBottomRadius();

		m_shape.Create(pDC->m_renderContext, bottomRadius, 0, height);
	}

	m_shape.Draw(pDC->m_renderContext);

#if 0
	GLUquadricObj* q = gluNewQuadric();
	gluCylinder(q, m_bottomRadius->m_value, 0/*topRadius*/, m_height->m_value, 20, 20);
	gluDeleteQuadric(q);
#endif
//	LDraw::gluCylinder(pDC->m_pGraphics3D, m_bottomRadius->m_value, 0/*topRadius*/, m_height->m_value, 20, 20);
}

}	// x3d
}
