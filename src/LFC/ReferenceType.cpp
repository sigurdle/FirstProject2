#include "stdafx.h"
#include "LFC.h"

namespace System
{

//using namespace IO;

ReferenceType::ReferenceType() : m_pPointerTo(nullptr)
{
}

ReferenceType::ReferenceType(Type* pPointerTo) : m_pPointerTo(pPointerTo)
{
}

bool ReferenceType::IsConst() const
{
	return false;
}

bool ReferenceType::IsVolatile() const
{
	return false;
}

uint ReferenceType::get_sizeof(uint sizeofptr) const
{
	if (sizeofptr == 0)
		return PointerType::default_sizeofptr;
	else
		return sizeofptr;
}

IO::TextWriter& ReferenceType::Write(IO::TextWriter& stream) const
{
	return m_pPointerTo->Write(stream) << " &";
}

String ReferenceType::ToString()
{
	IO::StringWriter stream;
	Write(stream);
	return stream.str();
}

bool ReferenceType::Equals(const ReferenceType& other) const
{
	return GetPointerTo()->Equals(*(Type*)other.GetPointerTo());
}

void ReferenceType::Load(TypeArchive& ar)
{
	ar >> m_pPointerTo;
}

void ReferenceType::Store(TypeArchive& ar) const
{
	ar << (Type*)m_pPointerTo;
}

Type* ReferenceType::Clone() const
{
	ReferenceType* pType = new ReferenceType(m_pPointerTo);
	return pType;
}

TypeSerializable::Class_Type ReferenceType::GetSerializableType() const
{
	return Class_ReferenceType;
}

}	// System
