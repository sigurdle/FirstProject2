#include "stdafx.h"
#include "X3D2.h"
#include "Sound2D.h"

namespace System
{
namespace x3d
{

NodeType* Sound2D::GetNodeType()
{
	static X3DFieldDefinition intensity("intensity", FieldType_SFFloat, SAIFieldAccess_inputOutput, offsetof(Sound2D, m_intensity));
	static X3DFieldDefinition location("location", FieldType_SFVec2f, SAIFieldAccess_inputOutput, offsetof(Sound2D, m_location));
	static X3DFieldDefinition source("source", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Sound2D, m_source));
	static X3DFieldDefinition spatialize("spatialize", FieldType_SFBool, SAIFieldAccess_initializeOnly, offsetof(Sound2D, m_spatialize));

	static X3DFieldDefinition* Sound2DFields[] =
	{
		&intensity,
		&location,
		&source,
		&spatialize,
		/*
		exposedField SFFloat intensity 1.0
		exposedField SFVec2f location 0,0
		exposedField SFNode source NULL
		field SFBool spatialize TRUE
		*/
	};

	static NodeType nodeType(WSTR("Sound2D"), typeid(Sound2D), Sound2DFields, _countof(Sound2DFields), X3DSoundNode::GetNodeType());
	return &nodeType;
}

Sound2D::Sound2D() : X3DSoundNode(GetNodeType())
{
}

}	// x3d
}
