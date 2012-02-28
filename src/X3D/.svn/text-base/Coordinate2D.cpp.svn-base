#include "stdafx.h"
#include "X3D2.h"
#include "Coordinate2D.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* Coordinate2DFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("point", FieldType_MFVec2f, SAIFieldAccess_inputOutput,-1),
	/*
		MFVec2f [in,out] point [NULL] (-8,8)
	*/
};

NodeType Coordinate2D::s_nodeType("Coordinate2D", typeid(Coordinate2D), Coordinate2DFields, _countof(Coordinate2DFields));

Coordinate2D::Coordinate2D() : X3DCoordinateNode(&s_nodeType)
{
// Cache pointers to relevant fields
	m_point = static_cast<MFVec2f*>(getField("point"));
}

Coordinate2D::~Coordinate2D()
{
}

MFVec2f* Coordinate2D::getPoint()
{
	return m_point;
}

}	// x3d
}	// System
