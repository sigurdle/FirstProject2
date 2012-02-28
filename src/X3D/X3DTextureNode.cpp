#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

NodeType* X3DTextureNode::GetNodeType()
{
#if 0
	static X3DFieldDefinition fields[] =
	{
		X3DFieldDefinition(WSTR("addChildren"), FieldType_MFNode, SAIFieldAccess_inputOnly,-1),
		X3DFieldDefinition(WSTR("removeChildren"), FieldType_MFNode, SAIFieldAccess_inputOnly,-1),
		X3DFieldDefinition(WSTR("bboxCenter"), FieldType_SFVec3f, SAIFieldAccess_initializeOnly,-1),
		X3DFieldDefinition(WSTR("bboxSize"), FieldType_SFVec3f, SAIFieldAccess_initializeOnly,-1),
		X3DFieldDefinition(WSTR("children"), FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
		/*
		MFNode  [in]     addChildren             [X3DChildNode]
		MFNode  [in]     removeChildren          [X3DChildNode]
		MFNode  [in,out] children       []       [X3DChildNode]
		SFVec3f []       bboxCenter     0 0 0    (-8,8)
		SFVec3f []       bboxSize       -1 -1 -1 (0,8) or -1 -1 -1
		*/
	};

	static NodeType nodeType(nullptr, typeid(X3DTexture2DNode), fields, _countof(fields), &X3DTexture2DNode::GetNodeType());
#endif

	static NodeType nodeType(nullptr, typeid(X3DTextureNode), nullptr, 0, X3DAppearanceChildNode::GetNodeType());
	return &nodeType;
}

}	// x3d
}	// System
