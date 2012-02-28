#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

TypedX3DFieldDefinition<MFFloat>* X3DInterpolatorNode::get_keyFieldDef()
{
	static TypedX3DFieldDefinition<MFFloat> key("key", SAIFieldAccess_inputOutput, offsetof(X3DInterpolatorNode, m_key));
	return &key;
}

TypedX3DFieldDefinition<SFFloat>* X3DInterpolatorNode::get_setFractionFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> set_fraction("set_fraction", SAIFieldAccess_inputOnly, offsetof(X3DInterpolatorNode, m_setFraction), 0, 0, 1);
	return &set_fraction;
}

NodeType* X3DInterpolatorNode::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_keyFieldDef(),
		get_setFractionFieldDef(),
	};

	static NodeType nodeType(nullptr, typeid(X3DInterpolatorNode), fields, _countof(fields), X3DChildNode::GetNodeType());
	return &nodeType;
}

X3DInterpolatorNode::X3DInterpolatorNode(NodeType* nodeType) : X3DChildNode(nodeType)
{
}

}	// x3d
}
