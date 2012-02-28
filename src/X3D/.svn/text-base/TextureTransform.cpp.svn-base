#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* TextureTransformFields[] =
{
	&X3DFieldDefinition("center", FieldType_SFVec2f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("rotation", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("scale", FieldType_SFVec2f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("translation", FieldType_SFVec2f, SAIFieldAccess_inputOutput,-1),
	/*
	SFVec2f [in,out] center      0 0 (-8,8)
	SFFloat [in,out] rotation    0   (-8,8)
	SFVec2f [in,out] scale       1 1 (-8,8)
	SFVec2f [in,out] translation 0 0 (-8,8)
	*/
};

NodeType TextureTransform::s_nodeType(WSTR("TextureTransform"), typeid(TextureTransform), TextureTransformFields, _countof(TextureTransformFields));

TextureTransform::TextureTransform() : X3DTextureTransform2DNode(&s_nodeType)
{
}

}	// x3d
}
