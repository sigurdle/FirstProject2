#include "stdafx.h"
#include "X3D2.h"

// MPEG4
#ifdef X3D_COMPONENT_BIFS

#include "OrderedGroup.h"

namespace System
{
namespace x3d
{

NodeType* OrderedGroup::nodeType(GetNodeType());

NodeType* OrderedGroup::GetNodeType()
{
	static X3DFieldDefinition order("order", FieldType_MFFloat, SAIFieldAccess_inputOutput, offsetof(OrderedGroup, m_order));

	/* unfortunately c++ doesn't allow this (non-aggreate) virtual members or virtual base classes
	static X3DFieldDefinition order =
	{
		(WSTR("order"), FieldType_MFFloat, SAIFieldAccess_inputOutput, offsetof(OrderedGroup, m_order))
	};
	*/

	static X3DFieldDefinition* fields[] =
	{
		&order,
	};

	static NodeType nodeType(WSTR("OrderedGroup"), typeid(OrderedGroup), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

OrderedGroup::OrderedGroup() : X3DGroupingNode(GetNodeType())
{
}

// virtual
void OrderedGroup::Draw(X3DDrawContext* pDC)
{
	DrawChildren(pDC, getChildrenField());
}

}	// x3d
}	// System

#endif
