#include "stdafx.h"
#include "X3D2.h"
#include "LineProperties.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* LinePropertiesFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("applied", FieldType_SFBool, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("linetype", FieldType_SFInt32, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("linewidthScaleFactor", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	/*
	SFBool  [in,out] applied              TRUE
	SFInt32 [in,out] linetype             1    [1,8)
	SFFloat [in,out] linewidthScaleFactor 0    [-8,8)
	SFNode  [in,out] metadata             NULL [X3DMetadataObject]
	*/
};

NodeType LineProperties::s_nodeType("LineProperties", typeid(LineProperties), LinePropertiesFields, _countof(LinePropertiesFields));

LineProperties::LineProperties() : X3DAppearanceChildNode(&s_nodeType)
{
}

}	// x3d
}	// System
