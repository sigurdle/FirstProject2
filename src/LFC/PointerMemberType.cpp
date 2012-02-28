#include "stdafx.h"
#include "LFC.h"

namespace System
{

TypeSerializable::Class_Type PointerMemberType::GetSerializableType() const
{
	return Class_PointerMemberType;
}

void PointerMemberType::Load(TypeArchive& stream)
{
	stream >> m_pPointerTo;
	stream >> m_pClass;
	stream >> m_sizeof;
}

void PointerMemberType::Store(TypeArchive& stream) const
{
	stream << m_pPointerTo;
	stream << m_pClass;
	stream << m_sizeof;
}

bool PointerMemberType::IsConst() const
{
	return false;
}

bool PointerMemberType::IsVolatile() const
{
	return false;
}

uint PointerMemberType::get_sizeof(uint sizeofptr) const
{
	return m_sizeof;
}

String PointerMemberType::ToString()
{
	ASSERT(0);
	return nullptr;
}

IO::TextWriter& PointerMemberType::Write(IO::TextWriter& stream) const
{
	// TODO
	//ASSERT(0);
	stream << "pm";

	return stream;
}

Type* PointerMemberType::Clone() const
{
	ASSERT(0);
	return NULL;
}

}	// System
