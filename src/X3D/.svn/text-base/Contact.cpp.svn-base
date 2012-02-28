#include "stdafx.h"
#include "X3D2.h"
#include "RigidBody.h"
#include "Contact.h"
#include "GUI/physics.h"

namespace System
{
namespace x3d
{

NodeType* Contact::nodeType(GetNodeType());

NodeType* Contact::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		&TypedX3DFieldDefinition<SFNode>("body1", SAIFieldAccess_inputOutput, offsetof(Contact, m_body1)),
		&TypedX3DFieldDefinition<SFNode>("body2", SAIFieldAccess_inputOutput, offsetof(Contact, m_body2)),
	};

	static NodeType nodeType("Contact", typeid(Contact), fields, _countof(fields), X3DNode::GetNodeType());
	return &nodeType;
}

Contact::Contact() : X3DNode(GetNodeType()),
	m_body1(new TypedSFNode<RigidBody*>(this)),
	m_body2(new TypedSFNode<RigidBody*>(this))
{
}

}
}
