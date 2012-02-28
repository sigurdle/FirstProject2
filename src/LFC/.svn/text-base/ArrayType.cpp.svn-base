#include "stdafx.h"
#include "LFC.h"

namespace System
{

ArrayType::ArrayType() :
	m_pElemType(NULL),
	m_nElemCount(0)
{
}

ArrayType::ArrayType(Type* elemType, unsigned int elemCount) :
	m_pElemType(elemType),
	m_nElemCount(elemCount)
{
}

uint ArrayType::get_sizeof(uint sizeofptr) const
{
	VERIFY(m_pElemType != NULL);
	return m_pElemType->get_sizeof(sizeofptr) * m_nElemCount;
}

bool ArrayType::IsConst() const
{
	return false;
}

bool ArrayType::IsVolatile() const
{
	return false;
}

void ArrayType::Load(TypeArchive& ar)
{
	ar >> m_nElemCount;
	ar >> m_pElemType;
}

void ArrayType::Store(TypeArchive& ar) const
{
	ar << m_nElemCount;
	ar << m_pElemType;
}

TypeSerializable::Class_Type ArrayType::GetSerializableType() const
{
	return Class_ArrayType;
}

Type* ArrayType::Clone() const
{
	ASSERT(0);
	return NULL;
}

String ArrayType::ToString()
{
	IO::StringWriter strbuilder;
	Write(strbuilder);
	return strbuilder.str();
}

IO::TextWriter& ArrayType::Write(IO::TextWriter& stream) const
{
	if (m_pElemType != NULL)
	{
		m_pElemType->Write(stream);
	}
//	if (m_bConst) str += "const ";
//	if (m_bVolatile) str += "volatile ";

//	char buf[64];
//	sprintf_s(buf, "[%d]", m_nElemCount);
	stream << '[' << m_nElemCount << ']';

	/*
	for (int i = 0; i < m_arrayDims.GetSize(); i++)
	{
		char buf[64];
		sprintf(buf, "[%d]", m_arrayDims[i]);
		str += buf;
	}
	*/

	return stream;
}

}	// System
