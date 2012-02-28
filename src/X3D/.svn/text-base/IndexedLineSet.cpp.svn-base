#include "stdafx.h"
#include "X3D2.h"
#include "IndexedLineSet.h"

namespace System
{
namespace x3d
{

NodeType* IndexedLineSet::nodeType(GetNodeType());

X3DFieldDefinition* IndexedLineSet::get_coordFieldDef()
{
	static X3DFieldDefinition coord("coord", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(IndexedLineSet, m_coord));
	return &coord;
}

X3DFieldDefinition* IndexedLineSet::get_coordIndexFieldDef()
{
	static X3DFieldDefinition coordIndex("coordIndex", FieldType_MFInt32, SAIFieldAccess_initializeOnly, offsetof(IndexedLineSet, m_coordIndex));
	return &coordIndex;
}

X3DFieldDefinition* IndexedLineSet::get_colorIndexFieldDef()
{
	static X3DFieldDefinition colorIndex("colorIndex", FieldType_MFInt32, SAIFieldAccess_initializeOnly, offsetof(IndexedLineSet, m_colorIndex));
	return &colorIndex;
}

X3DFieldDefinition* IndexedLineSet::get_colorPerVertexFieldDef()
{
	static X3DFieldDefinition colorPerVertex("colorPerVertex", FieldType_SFBool, SAIFieldAccess_initializeOnly, offsetof(IndexedLineSet, m_colorPerVertex));
	return &colorPerVertex;
}

X3DFieldDefinition* IndexedLineSet::get_colorFieldDef()
{
	static X3DFieldDefinition color("color", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(IndexedLineSet, m_color));
	return &color;
}

NodeType* IndexedLineSet::GetNodeType()
{
	static X3DFieldDefinition* IndexedLineSetFields[] =
	{
		get_coordFieldDef(),
		get_coordIndexFieldDef(),
		get_colorIndexFieldDef(),
		get_colorPerVertexFieldDef(),
		get_colorFieldDef(),
		/*
		MFInt32 [in]     set_colorIndex
		MFInt32 [in]     set_coordIndex	// This must be a typo, should it be get??
		SFNode  [in,out] color          NULL [X3DColorNode]
		SFNode  [in,out] coord          NULL [X3DCoordinateNode]
		SFNode  [in,out] metadata       NULL [X3DMetadataObject]
		MFInt32 []       colorIndex     []   [0,8) or -1
		SFBool  []       colorPerVertex TRUE
		MFInt32 []       coordIndex     []   [0,8) or -1
		*/
	};

	static NodeType nodeType("IndexedLineSet", typeid(IndexedLineSet), IndexedLineSetFields, _countof(IndexedLineSetFields), X3DGeometryNode::GetNodeType());
	return &nodeType;
}

IndexedLineSet::IndexedLineSet() : X3DGeometryNode(GetNodeType())
{
}

IndexedLineSet::~IndexedLineSet()
{
}

void IndexedLineSet::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
#if 0
// Lines are not lit, are not texture-mapped, and do not participate in collision detection
	Coordinate* coord = getCoord();//m_coord->m_value;
	if (coordinate)
	{
		MFVec3f* point = coord->getPointField();
		MFInt32* point = coord->getPointField();

		CArray<polyline,polyline&> polylines;

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
				polylines.Add(polyline(i, count));

				i = j;
			}
		}

		for (int npoly = 0; npoly < polylines.GetSize(); ++npoly)
		{
			int npt = polylines[npoly].index;
			int count = polylines[npoly].count;

			if (getColorPerVertex() == false)
			{
				Color* pColor = static_cast<CLColor*>(m_color->m_value.p);

				rt->m_d3d10->m_device->IASetInputLayout(GL::Direct10::s.m_vertexLayout0);
				rt->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

			//	glBegin(GL_LINE_STRIP);

				if (m_colorIndex->m_items.GetSize() == 0)
				{
					if (pColor)
					{
						if (npoly < pColor->m_color->m_items.GetSize())
						{
							glColor3(pColor->m_color->m_items[npoly]);
						}
					}
				}
				else
				{
					if (pColor)
					{
						int colorIndex = m_colorIndex->m_items[npoly];
						if (colorIndex >= 0 && colorIndex < pColor->m_color->m_items.GetSize())
						{
							glColor3(pColor->m_color->m_items[colorIndex]);
						}
					}
				}

				int* pindex = &m_coordIndex->m_items[npt];
				for (int k = 0; k < count; k++)
				{
					LDraw::gmVector3f& v = point->m_items[*pindex];
					glVertex3(v);

					pindex++;
				}
				glEnd();
			}
			else
			{
				CLColor* pColor = static_cast<CLColor*>(m_color->m_value.p);

				glBegin(GL_LINE_STRIP);

			// If the colorIndex field is empty, the coordIndex field is used to choose colours from the Color node
				if (m_colorIndex->m_items.GetSize() == 0)
				{
					long *pindex = &m_coordIndex->m_items[npt];
					for (int k = 0; k < count; k++)
					{
						LDraw::gmVector3f& v = point->m_items[*pindex];

						if (pColor)
							glColor3(pColor->m_color->m_items[*pindex]);

						glVertex3(v);

						pindex++;
					}
				}
				else
				{
					MessageBeep(-1);
				}
				glEnd();
			}
		}
	}

	glPopAttrib();
#endif
}

}	// x3d
}
