#include "stdafx.h"
#include "LFC.h"

namespace System
{

//using namespace IO;

RValueReferenceType::RValueReferenceType() : m_pPointerTo(nullptr)
{
}

RValueReferenceType::RValueReferenceType(Type* pPointerTo) : m_pPointerTo(pPointerTo)
{
}

bool RValueReferenceType::IsConst() const
{
	return false;
}

bool RValueReferenceType::IsVolatile() const
{
	return false;
}

uint RValueReferenceType::get_sizeof(uint sizeofptr) const
{
	if (sizeofptr == 0)
		return PointerType::default_sizeofptr;
	else
		return sizeofptr;
}

IO::TextWriter& RValueReferenceType::Write(IO::TextWriter& stream) const
{
	return m_pPointerTo->Write(stream) << " &&";
}

String RValueReferenceType::ToString()
{
	IO::StringWriter stream;
	Write(stream);
	return stream.str();
}

bool RValueReferenceType::Equals(const ReferenceType& other) const
{
	return GetPointerTo()->Equals(*(Type*)other.GetPointerTo());
}

void RValueReferenceType::Load(TypeArchive& ar)
{
	ar >> m_pPointerTo;
}

void RValueReferenceType::Store(TypeArchive& ar) const
{
	ar << (Type*)m_pPointerTo;
}

Type* RValueReferenceType::Clone() const
{
	RValueReferenceType* pType = new RValueReferenceType(m_pPointerTo);
	return pType;
}

TypeSerializable::Class_Type RValueReferenceType::GetSerializableType() const
{
	return Class_RValueReferenceType;
}

}	// System
