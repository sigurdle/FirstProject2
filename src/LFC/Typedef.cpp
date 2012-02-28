#include "stdafx.h"
#include "LFC.h"
#include "Type.h"

namespace System
{

Typedef::Typedef() : m_pType(nullptr)
{
}

Typedef::Typedef(StringIn name, Type* pType) : NamedType(name), m_pType(pType)
{
}

bool Typedef::IsConst() const
{
	return m_pType->IsConst();
}

bool Typedef::IsVolatile() const
{
	return m_pType->IsVolatile();
}

TypeSerializable::Class_Type Typedef::GetSerializableType() const
{
	return Class_Typedef;
}

Type* Typedef::GetStripped()
{
	ASSERT(this);

	if (m_pType == nullptr) return nullptr;
	return m_pType->GetStripped();
}

Type* Typedef::GetPointerTo() const
{
	if (m_pType == nullptr) return nullptr;
	return m_pType->GetPointerTo();
}

ClassType* Typedef::AsClass()
{
	if (m_pType == nullptr) return nullptr;
	return m_pType->AsClass();
}

bool Typedef::IsOfType(Type* pType) const
{
	return m_pType->IsOfType(pType);
}

Type* Typedef::Clone() const
{
	Typedef* p = new Typedef(m_name, m_pType);
//	p->m_pType = m_pType;
	return p;
}

uint Typedef::get_sizeof(uint sizeofptr) const
{
	return m_pType->get_sizeof(sizeofptr);
}

String Typedef::ToString()
{
	IO::StringWriter strbuilder;
	Write(strbuilder);
	return strbuilder;
}

IO::TextWriter& Typedef::Write(IO::TextWriter& strbuilder) const
{
	if (m_ownerScope && m_ownerScope->m_pNamespace->m_name)
	{
		GetQualifiedName(m_ownerScope, strbuilder);
		strbuilder << "::";
	}

	strbuilder << m_name;

	return strbuilder;
}

// static
Typedef* Typedef::CreateFromArchive(TypeArchive& ar, uint32 id)
{
	Typedef* p = new Typedef;
	if (ar.m_typeLoad.size() <= id) ar.m_typeLoad.resize(id+1);
	ar.m_typeLoad[id] = p;
	p->Load(ar);
	return p;

	String qname;

	bool hasqname;
	ar >> hasqname;

	if (hasqname)
	{
		ar >> qname;
	}

	TypeLib* typelib;
	ar >> typelib;
	ASSERT(typelib);

	if (typelib != ar.m_typelib)
	{
		return (Typedef*)NamedType::CreateFromArchive(ar, id, typelib, qname);
	}
	else
	{
		Typedef* pobj = new Typedef;
#if 0
		ar.m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pobj));
#endif
		ar.m_typeLoad.push_back(pobj);
		ASSERT(ar.m_typeLoad.size() == id);

		pobj->m_qname = qname;
		pobj->Load(ar);

		return pobj;
	}
}

void Typedef::Load(TypeArchive& ar)
{
	NamedType::Load(ar);

	/*
	bool hasqname;
	ar >> hasqname;
	if (hasqname)
	{
		m_qname = new StringA;
		ar >> *m_qname;
	}
	*/

	ar >> m_pType;

	/*
	{
		BufferImp<char> buffer;
		StringBuilderA strbuilder = StringBuilderA(&buffer);
		Write(strbuilder);
		m_qname = buffer.DetachToString();
	}
	*/
}

void Typedef::Store(TypeArchive& ar) const
{
	ASSERT(m_typelib);

	NamedType::Store(ar);

	ar << m_pType;
}

}	// System
