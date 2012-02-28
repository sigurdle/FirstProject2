#include "stdafx.h"
#include "X3D2.h"
#include "Normal.h"

namespace System
{
namespace x3d
{

NodeType* Normal::GetNodeType()
{
	static X3DFieldDefinition vector("vector", FieldType_MFVec3f, SAIFieldAccess_inputOutput, offsetof(Normal, m_vector));

	static X3DFieldDefinition* fields[] =
	{
		&vector,
		/*
	MFVec3f [in,out] vector [] (-8,8)
		*/
	};

	static NodeType nodeType("Normal", typeid(Normal), fields, _countof(fields), X3DNormalNode::GetNodeType());
	return &nodeType;
}

Normal::Normal() : X3DNormalNode(GetNodeType())
{
}

Normal::~Normal()
{
}

}	// x3d
}
