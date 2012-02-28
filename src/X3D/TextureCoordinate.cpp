#include "stdafx.h"
#include "X3D2.h"
#include "TextureCoordinate.h"

namespace System
{
namespace x3d
{

NodeType* TextureCoordinate::GetNodeType()
{
	static X3DFieldDefinition point("point", FieldType_MFVec2f, SAIFieldAccess_inputOutput, offsetof(TextureCoordinate, m_point));

	static X3DFieldDefinition* TextureCoordinateFields[] =
	{
		&point,
		/*
		MFVec2f [in,out] point [] (-8,8)
		*/
	};

	static NodeType nodeType("TextureCoordinate", typeid(TextureCoordinate), TextureCoordinateFields, _countof(TextureCoordinateFields), X3DTextureCoordinateNode::GetNodeType());
	return &nodeType;
}

NodeType* TextureCoordinate::nodeType(GetNodeType());

TextureCoordinate::TextureCoordinate() : X3DTextureCoordinateNode(GetNodeType())
{
}

}	// x3d
}	// System
