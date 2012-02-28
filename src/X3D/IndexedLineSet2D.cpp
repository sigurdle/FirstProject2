#include "stdafx.h"
#include "X3D2.h"
#include "IndexedLineSet2D.h"

namespace System
{
namespace x3d
{

NodeType* IndexedLineSet2D::nodeType(GetNodeType());

NodeType* IndexedLineSet2D::GetNodeType()
{
	static X3DFieldDefinition colorPerVertex("colorPerVertex", FieldType_SFBool, SAIFieldAccess_initializeOnly, offsetof(IndexedLineSet2D, m_colorPerVertex));
	static X3DFieldDefinition coord("coord", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(IndexedLineSet2D, m_coord));
	static X3DFieldDefinition coordIndex("coordIndex", FieldType_MFInt32, SAIFieldAccess_initializeOnly, offsetof(IndexedLineSet2D, m_coordIndex));

	static X3DFieldDefinition* fields[] =
	{
//		&colorPerVertex,
		&coord,
		&coordIndex,
	/*
	eventIn MFInt32 set_colorIndex
	eventIn MFInt32 set_coordIndex
	exposedField SFNode color NULL
	exposedField SFNode coord NULL
	field MFInt32 colorIndex []
	field SFBool colorPerVertex TRUE
	field MFInt32 coordIndex []
	*/
	};

	static NodeType nodeType("IndexedLineSet2D", typeid(IndexedLineSet2D), fields, _countof(fields), X3DGeometryNode::GetNodeType());
	return &nodeType;
}

IndexedLineSet2D::IndexedLineSet2D() : X3DGeometryNode(GetNodeType())
{
}

IndexedLineSet2D::~IndexedLineSet2D()
{
}

void IndexedLineSet2D::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
	ASSERT(0);
#if 0
	/*
	if (pDC->m_pGraphics2D)
	{
		Coordinate2D* coordinate2D = dynamic_cast<Coordinate2D*>(m_coord->m_value);
		if (coordinate2D)
		{
			MFVec2f* point = coordinate2D->getPoint();

			if (m_coordIndex->get_size() == 0)
			{
				pDC->m_pGraphics2D->FillPolygon(pDC->m_pBrush, (LDraw::PointF*)point->m_items.begin(), point->m_items.size());
			}
			else
			{
			}
		}
	}
	else
	*/
	if (pDC->m_pGraphics3D)
	{
		Coordinate2D* coordinate2D = dynamic_cast<Coordinate2D*>(m_coord->m_value);
		if (coordinate2D)
		{
			MFVec2f* point = coordinate2D->getPoint();

			if (m_coordIndex->m_items.GetSize() == 0)
			{
				int count = point->m_items.size();

				pDC->m_pGraphics3D->glBegin(GL_LINE_STRIP);

				for (int i = 0; i < count; i++)
				{
					pDC->m_pGraphics3D->glVertex(point->m_items[i]);
				}

				pDC->m_pGraphics3D->glEnd();
			}
			else
			{
				int i = 0;
				while (i < m_coordIndex->m_items.GetSize())
				{
					int j = i;
					int count = 0;
					while (j < m_coordIndex->m_items.GetSize())
					{
						long index = m_coordIndex->m_items[j];
						if (index == -1)
						{
							j++;
							break;
						}

						count++;
						j++;
					}

					pDC->m_pGraphics3D->glBegin(GL_LINE_STRIP);

					for (int k = 0; k < count; k++)
					{
						LDraw::vector2f& v = point->m_items[m_coordIndex->m_items[i+k]];
						pDC->m_pGraphics3D->glVertex(v);
					}

					pDC->m_pGraphics3D->glEnd();

					i = j;
				}
			}
		}
	}
#endif
}

}	// x3d
}
