#include "stdafx.h"
#include "X3D2.h"
#include "TriangleStripSet.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* TriangleStripSetFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("attrib", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("ccw", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("colorPerVertex", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("coord", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("normal", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("normalPerVertex", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("solid", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("stripCount", FieldType_MFInt32, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("texCoord", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	/*
	MFNode [in,out] attrib          []   [X3DVertexAttributeNode]
	SFNode  [in,out] color           NULL [X3DColorNode]
	SFNode  [in,out] coord           NULL [X3DCoordinateNode]
	SFNode  [in,out] metadata        NULL [X3DMetadataObject]
	SFNode  [in,out] normal          NULL [X3DNormalNode]
	MFInt32 [in,out] stripCount      []   [3,8)
	SFNode  [in,out] texCoord        NULL [X3DTextureCoordinateNode]
	SFBool  []       ccw             TRUE
	SFBool  []       colorPerVertex  TRUE
	SFBool  []       normalPerVertex TRUE
	SFBool  []       solid           TRUE
	*/
};

NodeType TriangleStripSet::s_nodeType(WSTR("TriangleStripSet"), typeid(TriangleStripSet), TriangleStripSetFields, _countof(TriangleStripSetFields));

TriangleStripSet::TriangleStripSet() : X3DComposedGeometryNode(&s_nodeType)
{
}

TriangleStripSet::~TriangleStripSet()
{
}

void TriangleStripSet::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
	ASSERT(0);
#if 0
	<ILCoordinate> coordinate = m_coord->m_value;
	<ILNormal> normal = m_normal->m_value;
	if (coordinate)
	{
		int numberOfStrips = m_stripCount->m_items.GetSize();
		long* stripCountData = m_stripCount->m_items.GetData();

		MFVec3f* coordinatePoints = static_cast<CLCoordinate*>(coordinate.p)->m_point;
		int numberOfPoints = coordinatePoints->m_items.GetSize();
		LDraw::gmVector3f* coordinatePointData = coordinatePoints->m_items.GetData();

		glVertexPointer(3, GL_FLOAT, 0, coordinatePointData);

		LDraw::gmVector3f* normalVectorData = NULL;
		if (normal)
		{
			MFVec3f* normalVectors = static_cast<CLNormal*>(normal.p)->m_vector;
			if (normalVectors->m_items.GetSize() != numberOfPoints)
				return;	// Error

			normalVectorData = normalVectors->m_items.GetData();

			glNormalPointer(GL_FLOAT, 0, normalVectorData);
		}

		int pointIndex = 0;
		for (int i = 0; i < numberOfStrips; i++)
		{
			long pointCount = stripCountData[i];
			if (pointCount < 3)
				return;	// Error

			long pointIndex2 = pointIndex+pointCount;
			if (pointIndex2 >= numberOfPoints)
				return;	// Error

			if (TRUE)//normal)
			{
				//glBegin(GL_TRIANGLE_STRIP);
				glDrawArrays(GL_TRIANGLE_STRIP, pointIndex, pointCount);
				//glEnd();

				pointIndex += pointCount;
			}
			else
			{
				glBegin(GL_TRIANGLE_STRIP);

				while (pointIndex < pointIndex2)
				{
					if (normal)
						glNormal3(normalVectorData[pointIndex]);
					glVertex3(coordinatePointData[pointIndex]);

					pointIndex++;
				}

				glEnd();
			}
		}
	}

#if 0
	if (m_coord)
	{
		glPushAttrib(GL_ENABLE_BIT);

		if (m_color)
		{
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
		}

		CLCoordinate* pCoord = static_cast<CLCoordinate*>(m_coord.p);
		CLColor* pColor = static_cast<CLColor*>(m_color.p);

		for (int i = 0; i < pCoord->m_point.GetSize(); i += 3)
		{
			lglNormal(pCoord->m_point[i+0], pCoord->m_point[i+1], pCoord->m_point[i+2]);

			if (m_colorPerVertex && i+2 < pColor->m_color.GetSize())
			{
				glColor3f(pColor->m_color[i][0], pColor->m_color[i][1], pColor->m_color[i][2]);
				glVertex3f(pCoord->m_point[i][0], pCoord->m_point[i][1], pCoord->m_point[i][2]);

				glColor3f(pColor->m_color[i+1][0], pColor->m_color[i+1][1], pColor->m_color[i+1][2]);
				glVertex3f(pCoord->m_point[i+1][0], pCoord->m_point[i+1][1], pCoord->m_point[i+1][2]);

				glColor3f(pColor->m_color[i+2][0], pColor->m_color[i+2][1], pColor->m_color[i+2][2]);
				glVertex3f(pCoord->m_point[i+2][0], pCoord->m_point[i+2][1], pCoord->m_point[i+2][2]);
			}
			else
			{
				glVertex3f(pCoord->m_point[i][0], pCoord->m_point[i][1], pCoord->m_point[i][2]);
				glVertex3f(pCoord->m_point[i+1][0], pCoord->m_point[i+1][1], pCoord->m_point[i+1][2]);
				glVertex3f(pCoord->m_point[i+2][0], pCoord->m_point[i+2][1], pCoord->m_point[i+2][2]);
			}
		}

		glEnd();

		glPopAttrib();
	}
#endif
#endif
}

}	// x3d
}
