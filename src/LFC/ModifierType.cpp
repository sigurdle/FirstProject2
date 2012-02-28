#include "stdafx.h"
#include "LFC.h"
#include "Type.h"

namespace System
{

ModifierType::ModifierType() : m_pPointerTo(NULL)
{
}

ModifierType::ModifierType(Type* pPointerTo, bool bConst, bool bVolatile) : _CVType(bConst, bVolatile), m_pPointerTo(pPointerTo)
{
}

TypeSerializable::Class_Type ModifierType::GetSerializableType() const
{
	return TypeSerializable::Class_ModifierType;
}

uint ModifierType::get_sizeof(uint sizeofptr) const
{
	return m_pPointerTo->get_sizeof(sizeofptr);
}

Type* ModifierType::GetStripped()
{
	ASSERT(this);
	return m_pPointerTo->GetStripped();
}

Type* ModifierType::Normalized()
{
	if (!m_bConst && !m_bVolatile)
		return m_pPointerTo->Normalized();

	return this;
}

bool ModifierType::IsConst() const
{
	if (m_bConst) return true;
	return m_pPointerTo->IsConst();
}

bool ModifierType::IsVolatile() const
{
	if (m_bVolatile) return true;
	return m_pPointerTo->IsConst();
}

Type* ModifierType::Clone() const
{
	ModifierType* p = new ModifierType;
	p->m_pPointerTo = m_pPointerTo;
	p->m_bConst = m_bConst;
	p->m_bVolatile = m_bVolatile;

	return p;
}

void ModifierType::Load(TypeArchive& ar)
{
	_CVType::Load(ar);
	ar >> m_pPointerTo;
}

void ModifierType::Store(TypeArchive& ar) const
{
	_CVType::Store(ar);
	ar << (Type*)m_pPointerTo;
}

String ModifierType::ToString()
{
	IO::StringWriter strbuilder;
	Write(strbuilder);
	return strbuilder.str();
}

IO::TextWriter& ModifierType::Write(IO::TextWriter& stream) const
{
	Type* pType = m_pPointerTo;
	while (pType && pType->get_Kind() == type_typedef)
	{
		pType = ((Typedef*)pType)->m_pType;
	}

	if (pType != NULL)
	{
		m_pPointerTo->Write(stream);
	}
	else
	{
		stream << "(null)";
	}

	if (m_bConst) stream << " const";
	if (m_bVolatile) stream << " volatile";

	return stream;
}

}	// System
