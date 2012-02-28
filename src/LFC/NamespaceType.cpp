#include "stdafx.h"
#include "LFC.h"
#include "Type.h"

namespace System
{

NamespaceType::NamespaceType() :
	m_pDispatch(NULL)
{
	m_pScope = new Scope;
	m_pScope->m_pNamespace = this;

	m_members = NULL;	// TODO, maybe not in use
}

NamespaceType::~NamespaceType()
{
	if (m_pScope)
	{
		delete m_pScope;
		m_pScope = NULL;
	}
}

NamespaceType::MembersCollection* NamespaceType::get_Members()
{
	return new MembersCollection/*CollectionObject<vector<CDeclarator*, __gc_allocator>, CDeclarator*>*/(m_pScope->m_orderedDecls);
}

void NamespaceType::Load(TypeArchive& ar)
{
	NamedType::Load(ar);

	m_pScope->m_pParentScope = m_ownerScope;
//	m_pScope->m_name = m_name;
}

void NamespaceType::Store(TypeArchive& ar) const
{
	NamedType::Store(ar);

}

IO::TextWriter& NamespaceType::Write(IO::TextWriter& stream) const
{
	if (m_ownerScope && m_ownerScope->m_pNamespace->m_name)
	{
		ASSERT(m_ownerScope->m_pNamespace);
		m_ownerScope->m_pNamespace->Write(stream);
		stream << "::";
	}

	stream << m_name;

	return stream;
}

}	// System
