#include "stdafx.h"
#include "LXML2.h"
#include "Entity.h"

namespace System
{
namespace Web
{

Entity::Entity(StringIn name, StringIn notationName) : m_name(name), m_notationName(notationName)
{
	m_pDTDEntity = nullptr;
}

String Entity::get_nodeName() const
{
	return m_name;
}

NodeType Entity::get_nodeType() const
{
	return NODE_ENTITY;
}

String Entity::get_publicId()
{
	VERIFY(0);
	return nullptr;
}

String Entity::get_systemId()
{
	VERIFY(0);
	return nullptr;
}

String Entity::get_notationName()
{
	return m_notationName;
}

/*
void Entity::set_notationName(StringIn notationName)
{
	m_notationName = notationName;
}
*/

Node* Entity::cloneNode(bool deep) const
{
	VERIFY(0);
	return nullptr;
}

}	// Web
}
