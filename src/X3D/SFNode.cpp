#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFNode::SFNode(X3DNode* ownerNode) : X3DField(ownerNode)
{
}

SFNode::SFNode(X3DFieldDefinition* def, X3DNode* ownerNode) : X3DField(def, ownerNode)
{
}

// virtual
void SFNode::CopyFrom(X3DField* pFrom)
{
	// ??
	//m_v = static_cast<SFNode*>(pFrom)->m_v;
	// clone

	X3DNode* node = static_cast<SFNode*>(pFrom)->getValue();
	if (node)	// ???
	{
		X3DNode* clone = node->m_scene->CreateNodeOfType(node->getType());

		ASSERT(0);
#if 0
		// clone fields
		for (int i = 0; i < node->m_fields.GetSize(); i++)
		{
			clone->getField(i)->CopyFrom(node->getField(i));
		}
#endif

		setX3DNode(clone);
	}
}

}	// x3d
}
