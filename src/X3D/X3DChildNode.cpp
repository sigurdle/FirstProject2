#include "StdAfx.h"
#include "X3D2.h"
#include "Transform.h"

namespace System
{
namespace x3d
{

NodeType* X3DChildNode::GetNodeType()
{
	/*
	static X3DFieldDefinition fields[] =
	{
	};

	static NodeType nodeType(NULL, typeid(X3DShapeNode), fields, _countof(fields), &X3DChildNode::GetNodeType());
	*/

	static NodeType nodeType(nullptr, typeid(X3DChildNode), nullptr, 0, X3DNode::GetNodeType());
	return &nodeType;
}

X3DChildNode::X3DChildNode(NodeType* nodeType) : X3DNode(nodeType)
{
}

X3DEXT void Translate(X3DChildNode* node, float x, float y, float z)
{
	X3DNode* parent = node->m_parents[0]->getOwnerNode();

	Transform* t = dynamic_cast<Transform*>(parent);
	if (t)
	{
		t->setTranslation(t->getTranslation() + Vec3f(x, y, z));
	}
	else
	{
		node->m_parents.clear();

		X3DGroupingNode* g = dynamic_cast<X3DGroupingNode*>(parent);
		ASSERT(g);

		g->getChildrenField()->m_items.erase(g->getChildrenField()->m_items.find(node));

		t = new Transform();
		t->setTranslation(Vec3f(x, y, z));
		t->getChildrenField()->append1Value(node);

		g->getChildrenField()->append1Value(t);
	}
}

X3DEXT void Rotate(X3DChildNode* node, float x, float y, float z, float angle)
{
	X3DNode* parent = node->m_parents[0]->getOwnerNode();

	Transform* t = dynamic_cast<Transform*>(parent);
	if (t)
	{
		t->setRotation(Rotation(x, y, z, angle));
	}
	else
	{
		node->m_parents.clear();

		X3DGroupingNode* g = dynamic_cast<X3DGroupingNode*>(parent);
		ASSERT(g);

		g->getChildrenField()->m_items.erase(g->getChildrenField()->m_items.find(node));

		t = new Transform();
		t->setRotation(Rotation(x, y, z, angle));
		t->getChildrenField()->append1Value(node);

		g->getChildrenField()->append1Value(t);
	}
}

}
}
