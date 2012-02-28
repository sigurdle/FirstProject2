#include "stdafx.h"
#include "X3D2.h"
#include "MultiTextureCoordinate.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* MultiTextureCoordinateFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("texCoord", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	/*
	MFNode [in,out] texCoord NULL [X3DTextureCoordinateNode]
	*/
};

NodeType MultiTextureCoordinate::s_nodeType("MultiTextureCoordinate", typeid(MultiTextureCoordinate), MultiTextureCoordinateFields, _countof(MultiTextureCoordinateFields));

MultiTextureCoordinate::MultiTextureCoordinate() : X3DTextureCoordinateNode(&s_nodeType)
{
}

MultiTextureCoordinate::~MultiTextureCoordinate()
{
}

}	// x3d
}
