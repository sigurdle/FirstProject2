#include "stdafx.h"
#include "X3D2.h"
#include "TextureCoordinateGenerator.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* TextureCoordinateGeneratorFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("mode", FieldType_SFString, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("parameter", FieldType_MFFloat, SAIFieldAccess_inputOutput,-1),
	/*
	SFString [in,out] mode      "SPHERE" [see Table]
	MFFloat  [in,out] parameter []       [see Table]
	*/
};

NodeType TextureCoordinateGenerator::s_nodeType(WSTR("TextureCoordinateGenerator"), typeid(TextureCoordinateGenerator), TextureCoordinateGeneratorFields, _countof(TextureCoordinateGeneratorFields));

TextureCoordinateGenerator::TextureCoordinateGenerator() : X3DTextureCoordinateNode(&s_nodeType)
{
// Cache pointers to relevant fields
//	m_mode = static_cast<SFString*>(getField(WSTR("mode")));
//	m_parameter = static_cast<MFFloat*>(getField(WSTR("parameter")));

	m_mode->m_value = WSTR("SPHERE");
}

TextureCoordinateGenerator::~TextureCoordinateGenerator()
{
}

}
}
