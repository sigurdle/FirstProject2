#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

NodeType* X3DShapeNode::GetNodeType()
{
	/*
	static X3DFieldDefinition fields[] =
	{
		X3DFieldDefinition(WSTR("appearance"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Shape, m_appearance)),
		X3DFieldDefinition(WSTR("geometry"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Shape, m_geometry)),
	};
	*/

	static NodeType nodeType(nullptr, typeid(thisClass), nullptr, 0, baseClass::GetNodeType());
	return &nodeType;
}

}	// x3d
}	// System
