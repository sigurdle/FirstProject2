#include "stdafx.h"
#include "LFC.h"

namespace System
{

PrimitiveType::PrimitiveType(Type_type type) : m_type(type), m_sizeof(GetSizeof(type))
{
}

uint PrimitiveType::get_sizeof(uint sizeofptr) const
{
	return m_sizeof;
}

TypeSerializable::Class_Type PrimitiveType::GetSerializableType() const
{
	return Class_PrimitiveType;
}

bool PrimitiveType::IsOfType(Type* pType) const
{
	Type_type othertype = pType->get_Kind();

	switch (get_Kind())
	{
	case type_bool:
		{
			return othertype == type_bool;
		}
		break;

	case type_char:
		{
			return othertype == type_char;
		}
		break;

	case type_wchar_t:
		{
			switch (othertype)
			{
			case type_char:	return true;
			case type_wchar_t:	return true;
			}
		}
		break;

	case type_uchar16:
		{
			switch (othertype)
			{
			case type_uchar16:	return true;
			}
		}
		break;

	case type_uchar32:
		{
			switch (othertype)
			{
			case type_uchar16:	return true;
			case type_uchar32:	return true;
			}
		}
		break;

	case type_short:
		{
			switch (othertype)
			{
			case type_short:	return true;
			case type_signed_char:	return true;
			case type_unsigned_char:	return true;
			}
		}
		break;

	case type_int:
		{
			switch (othertype)
			{
			case type_int:	return true;
			case type_short:	return true;
			case type_unsigned_short:	return true;
			case type_signed_char:	return true;
			case type_unsigned_char:	return true;
			}
		}
		break;

	case type_unsigned_int:
		{
			switch (othertype)
			{
			case type_unsigned_int:	return true;
			case type_unsigned_short:	return true;
			case type_unsigned_char:	return true;
			}
		}
		break;

	case type_long_long:
		{
			switch (othertype)
			{
			case type_long_long:	return true;
			case type_long:		return true;
			case type_int:	return true;
			case type_unsigned_int:	return true;
			case type_short:	return true;
			case type_unsigned_short:	return true;
			case type_signed_char:	return true;
			case type_unsigned_char:	return true;
			}
		}
		break;

	case type_unsigned_long_long:
		{
			switch (othertype)
			{
			case type_unsigned_char:	return true;
			case type_unsigned_short:	return true;
			case type_unsigned_int:		return true;
			case type_unsigned_long:	return true;
			case type_unsigned_long_long:	return true;
			}
		}
		break;

	case type_float:
		{
			return othertype == type_float;
		}
		break;

	case type_double:
		{
			return othertype == type_double ||
				othertype == type_float;
		}
		break;

	case type_long_double:
		{
			return othertype == type_long_double ||
				othertype == type_double ||
				othertype == type_float;
		}
		break;

	case type_float80:
		{
			return othertype == type_float80 ||
				othertype == type_long_double ||
				othertype == type_double ||
				othertype == type_float;
		}
		break;

	default:
		ASSERT(0);
	}

	return false;
}

void PrimitiveType::Load(TypeArchive& ar)
{
	ASSERT(0);
	/*
	//CVType::Load(ar);
	uint8 type;
	ar >> type;
	SetType((Type_type)type);
	*/
}

void PrimitiveType::Store(TypeArchive& ar) const
{
	//CVType::Store(ar);

	ASSERT(0);

	//ar << (uint8)m_type;
}

bool PrimitiveType::IsConst() const
{
	return false;
}

bool PrimitiveType::IsVolatile() const
{
	return false;
}

Type* PrimitiveType::Clone() const
{
	PrimitiveType* p = new PrimitiveType(m_type);
//	p->m_bConst = m_bConst;
//	p->m_bVolatile = m_bVolatile;
	return p;
}

String type_void_str("void");
String type_bool_str("bool");
String type_char_str("char");
String type_wchar_t_str("wchar_t");
String type_signed_char_str("signed char");
String type_unsigned_char_str("unsigned char");
String type_short_str("short");
String type_unsigned_short_str("unsigned short");
String type_int_str("int");
String type_unsigned_int_str("unsigned int");
String type_long_str("long");
String type_unsigned_long_str("unsigned long");
String type_long_long_str("long long");
String type_unsigned_long_long_str("unsigned long long");
String type_float_str("float");
String type_double_str("double");
String type_long_double_str("long double");
String type_float128_str("__float128");

String PrimitiveType::ToString()
{
	String str;

	switch (m_type)
	{
	case type_void:						str = type_void_str;					break;
	case type_bool:						str = type_bool_str;					break;
	case type_char:						str = type_char_str;					break;
	case type_wchar:					str = type_wchar_t_str;					break;
	case type_signed_char:				str = type_signed_char_str;				break;
	case type_unsigned_char:			str = type_unsigned_char_str;			break;
	case type_short:					str = type_short_str;					break;
	case type_unsigned_short:			str = type_unsigned_short_str;			break;
	case type_int:						str = type_int_str;						break;
	case type_unsigned_int:				str = type_unsigned_int_str;			break;
	case type_long:						str = type_long_str;					break;
	case type_unsigned_long:			str = type_unsigned_long_str;			break;
	case type_long_long:				str = type_long_long_str;				break;
	case type_unsigned_long_long:		str = type_unsigned_long_long_str;		break;
	case type_float:					str = type_float_str;					break;
	case type_double:					str = type_double_str;					break;
	case type_long_double:				str = type_long_double_str;				break;
	case type_float128:					str = type_float128_str;				break;

	default:
		ASSERT(0);
	}

	return str;
}

IO::TextWriter& PrimitiveType::Write(IO::TextWriter& stream) const
{
	switch (m_type)
	{
	case type_null:							stream << "null";					break;

	case type_void:							stream << "void";					break;
	case type_bool:							stream << "bool";					break;

	case type_char:							stream << "char";					break;
	case type_wchar:						stream << "wchar_t";				break;

	case type_signed_char:					stream << "signed char";			break;
	case type_unsigned_char:				stream << "unsigned char";			break;
	case type_short:						stream << "short";					break;
	case type_unsigned_short:				stream << "unsigned short";			break;
	case type_int:							stream << "int";					break;
	case type_unsigned_int:					stream << "unsigned int";			break;
	case type_long:							stream << "long";					break;
	case type_unsigned_long:				stream << "unsigned long";			break;
	case type_long_long:					stream << "long long";				break;
	case type_unsigned_long_long:			stream << "unsigned long long";		break;
	case type_float:						stream << "float";					break;
	case type_double:						stream << "double";					break;
	case type_long_double:					stream << "long double";			break;
	case type_float128:						stream << "float128";				break;

	default:
		ASSERT(0);
	}

	return stream;
}

// static
unsigned int PrimitiveType::GetSizeof(Type_type type)
{
	switch (type)
	{
	case type_bool:
		ASSERT(sizeof(bool) == 1);
		// TODO, 4 on ppc
		// return sizeof(bool);
		return 1;

	case type_char:
	case type_signed_char:
	case type_unsigned_char:
		return 1;

	case type_wchar_t:
		{
			ASSERT(sizeof(wchar_t) == 2);
			return 2;
		//return 4;	// default in GCC (but it has a compiler switch)
		}
		break;

	case type_short:
	case type_unsigned_short:
		return 2;

	case type_int:
	case type_unsigned_int:
	case type_float:
		return 4;

	case type_long:
	case type_unsigned_long:
		return sizeof(long);

	case type_long_long:
	case type_unsigned_long_long:
	case type_double:
		return 8;

	case type_long_double:
		ASSERT(sizeof(long double) == 8);
		return 8;

	case type_int128:
	case type_float128:
		return 16;

	case type_void:
		return ~0;

	default:
		return ~0;
	}
}

}	// System
