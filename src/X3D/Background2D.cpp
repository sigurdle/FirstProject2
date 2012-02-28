#include "stdafx.h"
#include "X3D2.h"
#include "Background2D.h"

namespace System
{
namespace x3d
{

NodeType* Background2D::GetNodeType()
{
	// BIFS MPEG4
	static X3DFieldDefinition* fields[] =
	{
		&X3DFieldDefinition("backColor", FieldType_SFColor, SAIFieldAccess_inputOutput, offsetof(Background2D, m_backColor)),
	/*
		eventIn SFBool set_bind
		exposedField SFColor backColor 0 0 0
		exposedField MFString url []
		eventOut SFBool isBound
	*/
	};

	static NodeType nodeType("Background2D", typeid(Background2D), fields, _countof(fields), X3DBackgroundNode::GetNodeType());
	return &nodeType;
}

Background2D::Background2D() : X3DBackgroundNode(GetNodeType())
{
}

}	// x3d
}
