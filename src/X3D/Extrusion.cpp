#include "stdafx.h"
#include "X3D2.h"
#include "Extrusion.h"

namespace System
{
namespace x3d
{

void lglNormal(Graphics::Graphics3D* p, const gm::vector3f& c, const gm::vector3f& b, const gm::vector3f& a);

X3DFieldDefinition* ExtrusionFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("convex", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("creaseAngle", FieldType_SFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("crossSection", FieldType_MFVec2f, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("orientation", FieldType_MFRotation, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("scale", FieldType_MFVec2f, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("solid", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("spine", FieldType_MFVec3f, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("endCap", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("beginCap", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	/*
	MFVec2f    [in]     set_crossSection
	MFRotation [in]     set_orientation
	MFVec2f    [in]     set_scale
	MFVec3f    [in]     set_spine
	SFNode     [in,out] metadata         NULL                      [X3DMetadataObject]
	SFBool     []       beginCap         TRUE
	SFBool     []       ccw              TRUE
	SFBool     []       convex           TRUE
	SFFloat    []       creaseAngle      0                         [0,8)
	MFVec2f    []       crossSection     [1 1 1 -1 -1 -1 -1 1 1 1] (-8,8)
	SFBool     []       endCap           TRUE
	MFRotation []       orientation      0 0 1 0                   [-1,1] or (-8,8)
	MFVec2f    []       scale            1 1                       (0,8)
	SFBool     []       solid            TRUE
	MFVec3f    []       spine            [0 0 0 0 1 0]             (-8,8)
	*/
};

NodeType Extrusion::s_nodeType(WSTR("Extrusion"), typeid(Extrusion), ExtrusionFields, _countof(ExtrusionFields));

Extrusion::Extrusion() : X3DGeometryNode(&s_nodeType)
{
// Set defaults
	//m_size->m_value[0] = m_size->m_value[1] = m_size->m_value[2] = 2;
}

void Extrusion::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
	ASSERT(0);
#if 0
	pDC->m_pGraphics3D->glBegin(GL_QUADS);

	for (int i = 1; i < m_spine->m_items.GetSize(); i++)
	{
		LDraw::vector2f scale1;

		if (m_scale->m_items.GetSize() == 1)
			scale1 = m_scale->m_items[0];
		else
			scale1 = m_scale->m_items[i];

		LDraw::vector2f scale0;
		if (m_scale->m_items.GetSize() == 1)
			scale0 = m_scale->m_items[0];
		else
			scale0 = m_scale->m_items[i-1];

		for (int j = 1; j < m_crossSection->m_items.GetSize(); j++)
		{
			/*
one quadrilateral has the points:

 spine[0](crossSection[0], crossSection[1])
 spine[1](crossSection[1], crossSection[0])
*/

			LDraw::vector3f v0 = LDraw::vector3f(m_crossSection->m_items[j-1][0], 0, m_crossSection->m_items[j-1][1]);
			v0[0] *= scale1[0];	// scale X
			v0[2] *= scale1[1];	// scale Z
			v0[0] += m_spine->m_items[i][0];	// translate X
			v0[1] += m_spine->m_items[i][1];	// translate Y
			v0[2] += m_spine->m_items[i][2];	// translate Z

			LDraw::vector3f v1 = LDraw::vector3f(m_crossSection->m_items[j][0], 0, m_crossSection->m_items[j][1]);
			v1[0] *= scale1[0];	// scale X
			v1[2] *= scale1[1];	// scale Z
			v1[0] += m_spine->m_items[i][0];	// translate X
			v1[1] += m_spine->m_items[i][1];	// translate Y
			v1[2] += m_spine->m_items[i][2];	// translate Z

			LDraw::vector3f v2 = LDraw::vector3f(m_crossSection->m_items[j][0], 0, m_crossSection->m_items[j][1]);
			v2[0] *= scale0[0];	// scale X
			v2[2] *= scale0[1];	// scale Z
			v2[0] += m_spine->m_items[i-1][0];	// translate X
			v2[1] += m_spine->m_items[i-1][1];	// translate Y
			v2[2] += m_spine->m_items[i-1][2];	// translate Z

			LDraw::vector3f v3 = LDraw::vector3f(m_crossSection->m_items[j-1][0], 0, m_crossSection->m_items[j-1][1]);
			v3[0] *= scale0[0];	// scale X
			v3[2] *= scale0[1];	// scale Z
			v3[0] += m_spine->m_items[i-1][0];	// translate X
			v3[1] += m_spine->m_items[i-1][1];	// translate Y
			v3[2] += m_spine->m_items[i-1][2];	// translate Z

			lglNormal(pDC->m_pGraphics3D, v0, v1, v2);
			pDC->m_pGraphics3D->glVertex(v0);
			pDC->m_pGraphics3D->glVertex(v1);
			pDC->m_pGraphics3D->glVertex(v2);
			pDC->m_pGraphics3D->glVertex(v3);
		}
	}

	pDC->m_pGraphics3D->glEnd();

	if (true)
	{
		pDC->m_pGraphics3D->glBegin(GL_POLYGON);

		int i = 0;
		LDraw::vector2f scale;

		if (m_scale->m_items.GetSize() == 1)
			scale = m_scale->m_items[0];
		else
			scale = m_scale->m_items[i];

		pDC->m_pGraphics3D->glNormalf(0, 1, 0);

		for (int j = 0; j < m_crossSection->m_items.GetSize(); j++)
		{
			LDraw::vector3f v = LDraw::vector3f(m_crossSection->m_items[j][0], 0, m_crossSection->m_items[j][1]);
			v[0] *= scale[0];	// scale X
			v[2] *= scale[1];	// scale Z
			v[0] += m_spine->m_items[i][0];	// translate X
			v[1] += m_spine->m_items[i][1];	// translate Y
			v[2] += m_spine->m_items[i][2];	// translate Z

			pDC->m_pGraphics3D->glVertex(v);
		}

		pDC->m_pGraphics3D->glEnd();
	}

	if (true)
	{
		pDC->m_pGraphics3D->glBegin(GL_POLYGON);

		int i = m_spine->m_items.GetSize()-1;
		LDraw::vector2f scale;

		if (m_scale->m_items.GetSize() == 1)
			scale = m_scale->m_items[0];
		else
			scale = m_scale->m_items[i];

		pDC->m_pGraphics3D->glNormalf(0, -1, 0);

		for (int j = 0; j < m_crossSection->m_items.GetSize(); j++)
		{
			LDraw::vector3f v = LDraw::vector3f(m_crossSection->m_items[j][0], 0, m_crossSection->m_items[j][1]);
			v[0] *= scale[0];	// scale X
			v[2] *= scale[1];	// scale Z
			v[0] += m_spine->m_items[i][0];	// translate X
			v[1] += m_spine->m_items[i][1];	// translate Y
			v[2] += m_spine->m_items[i][2];	// translate Z

			pDC->m_pGraphics3D->glVertex(v);
		}

		pDC->m_pGraphics3D->glEnd();
	}
#endif
}

}	// x3d
}	// System
