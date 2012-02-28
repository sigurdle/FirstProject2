#include "stdafx.h"
#include "X3D2.h"
#include "Rectangle.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(Rectangle, SFVec2f, size, inputOutput, Vec2f(2,2))

NodeType* Rectangle::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_sizeFieldDef(),
	};

	static NodeType nodeType(WSTR("Rectangle"), typeid(Rectangle), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

Rectangle::Rectangle() : X3DGeometryNode(GetNodeType())
{
}

void Rectangle::Rectf(X3DDrawContext* pDC, float x1, float y1, float x2, float y2)
{
	ASSERT(0);
#if 0
	if (false)
	{
		pDC->m_pGraphics3D->FillRectangle(pDC->m_pBrush, x1, y1, x2-x1, y2-y1);
	}
	else
	{
		if (true)
		{
			LDraw::GraphicsO_3D* p = ((LDraw::Graphics3DImmediate*)pDC->m_pGraphics3D)->m_pG;

			if (true)
			{
				/*
				pDC->GenFace(LDraw::vector3f(x1, y1, 0),
					LDraw::vector3f(x2, y1, 0)
					LDraw::vector3f(x2, y2, 0));

				pDC->GenFace(LDraw::vector3f(x1, y1, 0),
					LDraw::vector3f(x2, y2, 0)
					LDraw::vector3f(x1, y2, 0));
*/

				int index = pDC->m_vertices.size();

				pDC->Vertex(LDraw::vector3f(x1, y1, 0));
				pDC->Vertex(LDraw::vector3f(x2, y1, 0));
				pDC->Vertex(LDraw::vector3f(x2, y2, 0));
				pDC->Vertex(LDraw::vector3f(x1, y2, 0));

				Face face0(index, index+1, index+2);
				Face face1(index, index+2, index+3);

				pDC->m_faces.push_back(face0);
				pDC->m_faces.push_back(face1);
			}
			else
			{
#if 0
				LDraw::Vertex v0;
				p->processVertex(LDraw::vector4f(x1, y1, 0, 1), LDraw::vector3f(0, 0, 1), NULL, v0);

				LDraw::Vertex v1;
				p->processVertex(LDraw::vector4f(x2, y1, 0, 1), LDraw::vector3f(0, 0, 1), NULL, v1);

				LDraw::Vertex v2;
				p->processVertex(LDraw::vector4f(x2, y2, 0, 1), LDraw::vector3f(0, 0, 1), NULL, v2);

				LDraw::Vertex v3;
				p->processVertex(LDraw::vector4f(x1, y2, 0, 1), LDraw::vector3f(0, 0, 1), NULL, v3);

				int index = pDC->m_vertices.size();
				pDC->m_vertices.push_back(v0);
				pDC->m_vertices.push_back(v1);
				pDC->m_vertices.push_back(v2);
				pDC->m_vertices.push_back(v3);

				Face face0(index, index+1, index+2);
				Face face1(index, index+2, index+3);
				face0.CalcMinZ(pDC->m_vertices.begin());
				face1.CalcMinZ(pDC->m_vertices.begin());

				pDC->m_indices.push_back(pDC->m_faces.size());
				pDC->m_indices.push_back(pDC->m_faces.size()+1);

				pDC->m_faces.push_back(face0);
				pDC->m_faces.push_back(face1);
#endif
			}

/*
			int index = pDC->m_indices.size();

			pDC->m_faces.push_back(index);

			pDC->m_vertexArray.push_back(v0);

			pDC->m_colorArray.push_back(pDC->m_currentColor);
			pDC->m_colorArray.push_back(pDC->m_currentColor);
			pDC->m_colorArray.push_back(pDC->m_currentColor);
			pDC->m_colorArray.push_back(pDC->m_currentColor);

			// triangle
			pDC->m_indices.push_back(index);
			pDC->m_indices.push_back(index+1);
			pDC->m_indices.push_back(index+2);

			// triangle
			pDC->m_indices.push_back(index);
			pDC->m_indices.push_back(index+2);
			pDC->m_indices.push_back(index+3);
			*/
		}
		else
		{
			pDC->m_pGraphics3D->glBegin(GL_POLYGON);

			pDC->m_pGraphics3D->glNormalf(0, 0, 1);

			pDC->m_pGraphics3D->glTexCoordf(0, 0);
			pDC->m_pGraphics3D->glVertexf(x1, y1);

			pDC->m_pGraphics3D->glTexCoordf(1, 0);
			pDC->m_pGraphics3D->glVertexf(x2, y1);

			pDC->m_pGraphics3D->glTexCoordf(1, 1);
			pDC->m_pGraphics3D->glVertexf(x2, y2);

			pDC->m_pGraphics3D->glTexCoordf(0, 1);
			pDC->m_pGraphics3D->glVertexf(x1, y2);

			pDC->m_pGraphics3D->glEnd();
		}
	}
#endif
}

void Rectangle::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* textureNode)
{


	Rectf(pDC,
		-m_size->m_value[0]/2, -m_size->m_value[1]/2,
		m_size->m_value[0]/2, m_size->m_value[1]/2);

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
}

}	// x3d
}
