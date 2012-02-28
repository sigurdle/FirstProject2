#include "StdAfx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

NodeType* X3DGeometryNode::GetNodeType()
{
	/*
	static X3DFieldDefinition fields[] =
	{
		X3DFieldDefinition(WSTR("size"), FieldType_SFVec3f, SAIFieldAccess_initializeOnly, offsetof(Box, m_size)),
	};

	static NodeType nodeType(NULL, typeid(X3DGeometryNode), fields, _countof(fields), &X3DChildNode::GetNodeType());
	*/
	static NodeType nodeType(nullptr, typeid(X3DGeometryNode), nullptr, 0, X3DChildNode::GetNodeType());
	return &nodeType;
}

}
}
