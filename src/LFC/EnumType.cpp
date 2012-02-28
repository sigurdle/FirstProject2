#include "stdafx.h"
#include "LFC.h"
#include "Type.h"

namespace System
{

EnumDef::EnumDef()
{
}

EnumDef::EnumDef(StringIn name, int value) :
	m_name(name),
	m_value(value)
{
}

bool EnumDef::Equals(const EnumDef& other) const
{
	return m_name == other.m_name && m_value == other.m_value;
}

//////////////////////////

EnumType::EnumType() : m_baseType(nullptr)
{
}

EnumType::EnumType(Type* baseType) : m_baseType(baseType)
{
}

EnumType::EnumType(StringIn name) : NamedType(name), m_baseType(nullptr)
{
}

EnumType::EnumType(StringIn name, Type* baseType) : NamedType(name), m_baseType(baseType)
{
}

uint EnumType::get_sizeof(uint sizeofptr) const
{
	if (m_baseType == nullptr) return sizeof(int);
	return m_baseType->get_sizeof(sizeofptr);
}

Type* EnumType::Clone() const
{
	EnumType* p = new EnumType(m_name, m_baseType);
	p->m_deflist = m_deflist;
	return p;
}

EnumDef* EnumType::GetItem(int value)
{
	for (size_t i = 0; i < m_deflist.size(); ++i)
	{
		if (m_deflist[i].m_value == value)
		{
			return &m_deflist[i];
		}
	}

	return nullptr;
}

EnumDef* EnumType::GetItemL(long long value)
{
	for (size_t i = 0; i < m_deflist.size(); ++i)
	{
		if (m_deflist[i].m_value == value)
		{
			return &m_deflist[i];
		}
	}

	return nullptr;
}

EnumDef* EnumType::GetItem(StringIn name)
{
	for (size_t i = 0; i < m_deflist.size(); ++i)
	{
		EnumDef* def = &m_deflist[i];

		if (def->m_name.BeginsWith(m_name))
		{
			// Skip '_'
			if (def->m_name.RightOf(m_name.GetLength()+1) == name)
			{
				return def;
			}
		}
		else
		{
			if (def->m_name == name)
			{
				return def;
			}
		}
	}

	return nullptr;
}

Type* EnumType::GetBaseType()
{
	if (m_baseType == nullptr) return typeid(int);
	return m_baseType->GetStripped();
}

bool EnumType::Equals(const EnumType* pOther) const
{
	if (m_deflist.GetSize() != pOther->m_deflist.GetSize())
		return false;

	for (uint i = 0; i < m_deflist.GetSize(); ++i)
	{
		const EnumDef& def1 = m_deflist[i];
		const EnumDef& def2 = pOther->m_deflist[i];
		if (!def1.Equals(def2))
		{
			return false;
		}
	}

	return true;
}

// static
EnumType* EnumType::CreateFromArchive(TypeArchive& ar, uint32 id)
{
	EnumType* p = new EnumType;
	if (ar.m_typeLoad.size() <= id) ar.m_typeLoad.resize(id+1);
	ar.m_typeLoad[id] = p;
	p->Load(ar);
	return p;

#if 0
	String qname;

	bool hasqname;
	ar >> hasqname;

	if (hasqname)
	{
		ar >> qname;
	}

	TypeLib* typelib;
	ar >> typelib;

	if (typelib != ar.m_typelib)
	{
		return (EnumType*)NamedType::CreateFromArchive(ar, id, typelib, qname);
	}
	else
	{
		EnumType* pobj = new EnumType;
#if 0
		ar.m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pobj));
#endif
		ar.m_typeLoad.push_back(pobj);
		ASSERT(ar.m_typeLoad.size() == id);

		pobj->m_qname = qname;
		pobj->Load(ar);

		return pobj;
	}
#endif
}

void EnumType::Load(TypeArchive& ar)
{
	NamedType::Load(ar);

	/*
	if (m_name == "Type_type")
	{
		__asm int 3
	}
	*/

	ar >> m_baseType;

	uint16 count;
	ar >> count;

	m_deflist.reserve(count);

	for (uint i = 0; i < count; ++i)
	{
		String name = ar.LoadIdentifier();
		int value;
		ar >> value;

		m_deflist.push_back(EnumDef(name, value));
	}
}

void EnumType::Store(TypeArchive& ar) const
{
	ASSERT(m_typelib);

	NamedType::Store(ar);

	/*
	if (m_name == "Type_type")
	{
		__asm int 3
	}
	*/

	ar << m_baseType;

	VERIFY(m_deflist.size() < 32767);
	ar << (uint16)m_deflist.size();

	for (size_t i = 0; i < m_deflist.size(); ++i)
	{
		ar.StoreIdentifier(m_deflist[i].m_name);

		ar << m_deflist[i].m_value;
	}
}

TypeSerializable::Class_Type EnumType::GetSerializableType() const
{
	return Class_EnumType;
}

String EnumType::ToString()
{
	IO::StringWriter strbuilder;
	Write(strbuilder);
	return strbuilder.str();
}

IO::TextWriter& EnumType::Write(IO::TextWriter& strbuilder) const
{
#if 0
	stream << "enum ";
#endif

	if (m_ownerScope && m_ownerScope->m_pNamespace->m_name)
	{
		GetQualifiedName(m_ownerScope, strbuilder);
		strbuilder << "::";
	}

	if (m_name == nullptr)
	{
		strbuilder << "(null)";
	}
	else
	{
		strbuilder << m_name;
	}

//	stream << m_name->c_str();

	return strbuilder;
}

}	// System
