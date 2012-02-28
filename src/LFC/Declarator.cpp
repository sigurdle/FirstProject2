#include "stdafx.h"
#include "LFC.h"
#include "Type.h"

namespace System
{

Declarator::Declarator() : m_pType(nullptr), m_access(AccessSpec_Private)
{
	m_static = false;
	m_typedef = false;
	m_referenced = false;
	m_defined = false;
	m_virtual = false;
	m_localVar = false;
	m_fwd = false;
	m_offset = ~0;
	m_address = ~0;
	m_alignment = 0;
	m_bitoffset = 0;
	m_bitlength = 0;
	m_pOwnerScope = nullptr;
}

Declarator::Declarator(Type* pType, StringIn name) : m_pType(pType), m_name(name), m_access(AccessSpec_Private)
{
	m_static = false;
	m_typedef = false;
	m_referenced = false;
	m_defined = false;
	m_virtual = false;
	m_localVar = false;
	m_fwd = false;
	m_offset = ~0;
	m_address = ~0;
	m_alignment = 0;
	m_bitoffset = 0;
	m_bitlength = 0;
	m_pOwnerScope = nullptr;
}

IO::TextWriter& Declarator::Write(IO::TextWriter& stream) const
{
	if (m_pType != nullptr)
	{
		ASSERT(m_pType != nullptr);
		m_pType->Write(stream);
	}
	else
	{
		stream << "(null)";
	}

	stream << ' ';
	if (m_name)
		stream << m_name;
	else
		stream << "(null)";

	return stream;
}

IO::TextWriter& Declarator::WriteFunctionIdentity(IO::TextWriter& stream) const
{
	if (m_name)
		stream << m_name;
	else
		stream << "(null)";

	stream << ' ';

	ASSERT(m_pType != nullptr);
	ASSERT(m_pType->AsFunction() != nullptr);
	m_pType->AsFunction()->m_parameters.Write(stream);

	return stream;
}

uint Declarator::get_bitSize() const
{
	if (m_bitlength)
		return m_bitlength;
	else
		return m_pType->get_sizeof()*8;
}

bool Declarator::Equals(const Declarator& other) const
{
	if (this == &other) return true;

	if (m_offset != other.m_offset)
		return false;

	if (*m_name != *other.m_name)
		return false;

	// Shallow
	if (true)
	{
		size_t t1_size = m_pType->get_sizeof();
		size_t t2_size = other.m_pType->get_sizeof();
		if (t1_size != t2_size)
			return false;

		Type* t1 = m_pType;
		ASSERT(t1);
		while (t1->get_Kind() == type_typedef)
		{
			t1 = ((Typedef*)t1)->m_pType;
		}

		Type* t2 = other.m_pType;
		ASSERT(t2);
		while (t2->get_Kind() == type_typedef)
		{
			t2 = ((Typedef*)t2)->m_pType;
		}

		// CodeView treats bool as unsigned char
	//	if (t1->get_Kind() != t2->get_Kind())
	//		return false;

		// hmm
		/*
		if (dynamic_cast<NamedType*>(t1))
		{
			if (dynamic_cast<NamedType*>(t2) == NULL) return false;

			if (*((NamedType*)t1)->m_qname != *((NamedType*)t2)->m_qname)
				return false;
		}
		*/
	}
	else
	{
		if (!m_pType->Equals(*(Type*)other.m_pType))
			return false;
	}

	return true;	// They're equal
}

String Declarator::ToString()
{
	IO::StringWriter strbuilder;
	Write(strbuilder);
	return strbuilder.str();
}

void Declarator::Load(bool bMember, TypeArchive& ar)
{
	m_name = ar.LoadIdentifier();

	uint8 flags;
	ar >> flags;
	m_static = flags & 1;
	m_virtual = (flags>>1) & 1;
	m_typedef = (flags>>2) & 1;
	m_access = (AccessSpec)((flags>>3) & 3);
	m_cpp_linkage = (flags>>5) & 1;
	m_abstract = (flags>>6) & 1;

	ASSERT(m_access != AccessSpec_Unspecified);

	ar >> m_pType;
	ar >> m_pOverrideClass;

	if (bMember)
	{
		ar >> m_offset;
		ar >> m_bitoffset;
		ar >> m_bitlength;
		m_initVal = SExp::FromArchive(ar);
	}
}

void Declarator::Store(bool bMember, TypeArchive& ar) const
{
	ar.StoreIdentifier(m_name);

	ASSERT(m_access != AccessSpec_Unspecified);

	uint8 flags = 0;
	flags |= (int)m_static;
	flags |= (int)m_virtual<<1;
	flags |= (int)m_typedef<<2;
	flags |= (int)m_access<<3;
	flags |= (int)m_cpp_linkage<<5;
	flags |= (int)m_abstract<<6;

	ar << flags;

	ar << m_pType;
	ar << m_pOverrideClass;

	if (bMember)
	{
		ar << m_offset;
		ar << m_bitoffset;
		ar << m_bitlength;
		if (m_initVal)
		{
			ar << (byte)m_initVal->GetKind();
			m_initVal->Store(ar);
		}
		else
		{
			ar << (byte)SExp::SEXP_NULL;
		}
	}
}

void Declarator::VerifyImplemented() const throw (SystemException*)
{
	if (m_pType->get_Kind() != type_function)
	{
		raise(SystemException(get_QName() + " is not a function"));
	}

	if (m_address == ~0 || m_address == 0)
	{
		IO::StringWriter str;
		str << "method '" << get_QName() << "' not implemented/found";
		raise(SystemException(str.str()));
	}
}

void Declarator::void_invoke_method(void* thisptr) const
{
	VerifyImplemented();

	FunctionType* pFunType = m_pType->AsFunction();

#ifdef _M_IX86

	void_invoke_method32(GetAddress(), thisptr, nullptr, 0);

#elif _M_X64

	int64 args_stack[4];
	int64* p = args_stack;
	*p++ = (ULONG_PTR)thisptr;
	size_t nargs = 4;	// always at least 4

	(void)int64_invoke_function_fastcall64(GetAddress(), args_stack, nargs);
#else
#error "Unknown OS"
#endif
}

void Declarator::void_invoke_method(void* thisptr, const void* args, size_t sz) const
{
	VerifyImplemented();

	FunctionType* pFunType = m_pType->AsFunction();

#ifdef _M_IX86

	void_invoke_method32(GetAddress(), thisptr, args, sz);

#elif _M_X64

	ASSERT(0);

	// TODO: args, sz

	int64 args_stack[4];
	int64* p = args_stack;
	*p++ = (ULONG_PTR)thisptr;
	size_t nargs = 4;	// always at least 4

	(void)int64_invoke_function_fastcall64(GetAddress(), args_stack, nargs);
#else
#error "Unknown OS"
#endif
}

int Declarator::int32_invoke_method(void* thisptr, const void* args, size_t sz) const
{
	VerifyImplemented();

	FunctionType* pFunType = m_pType->AsFunction();

#ifdef _M_IX86

	return int32_invoke_method32(GetAddress(), thisptr, args, sz);

#elif _M_X64

	ASSERT(0);
	return 0;

#else
#error "Unknown OS"
#endif
}

void Declarator::struct_invoke_method(void* thisptr, const void* args, size_t sz, void* retaddress) const
{
	VerifyImplemented();

	FunctionType* pFunType = m_pType->AsFunction();

#ifdef _M_IX86

	struct_invoke_method32(GetAddress(), thisptr, args, sz, retaddress);

#elif _M_X64

	ASSERT(0);
#else
#error "Unknown OS"
#endif
}

void Declarator::void_invoke_method(void* thisptr, const array<Variant>& args) const
{
	VerifyImplemented();

	FunctionType* pFunType = static_cast<FunctionType*>(m_pType);

#ifdef _M_IX86

	ubyte args_stack[512];
	ubyte* p =  args_stack;

	for (size_t i = 0; i < args.size(); ++i)
	{
		Variant arg = args[i];

		switch (arg.GetType()->GetStripped()->get_Kind())
		{
		case type_int:
		case type_unsigned_int:
			*(int*)p = arg.u.int32_val;
			p += 4;
			break;

		default:
			ASSERT(0);
		}
	}

	void_invoke_method32(GetAddress(), thisptr, args_stack, p - args_stack);

#elif _M_X64

	int64 args_stack[64];
	int64* p = args_stack;

	*p++ = (ULONG_PTR)thisptr;

	for (size_t i = 0; i < args.size(); ++i)
	{
		const Variant& v = args[i];

		switch (v.GetType()->GetStripped()->get_Kind())
		{
			/*
		case type_bool:
			*p = v.u.bool_val;
			break;

		case type_char:
		case type_signed_char:
		case type_unsigned_char:
			*p = v.u.int8_val;
			break;

		case type_short_int:
		case type_unsigned_short_int:
			*p = v.u.int16_val;
			break;
			*/

		case type_int:
		case type_unsigned_int:
			*p = v.u.int32_val;
			break;

		default:
			ASSERT(0);
		}

		++p;
	}

	size_t nargs = std::max(args.size(), (size_t)4);

	(void)int64_invoke_function_fastcall64(GetAddress(), args_stack, nargs);

#else
#error "Unknown OS"
#endif
	return;	// easier to debug in case there's a bug in int64_invoke_function_fastcall64
}

void Declarator::void_invoke_function(const void* args, size_t sz) const
{
	VerifyImplemented();
	FunctionType* pFunType = static_cast<FunctionType*>(m_pType);

#ifdef _M_IX86
	if (pFunType->m_funcspec == CallType_stdcall)
		void_invoke_function_stdcall(GetAddress(), args, sz);
	else if (pFunType->m_funcspec == CallType_cdecl)
		void_invoke_function_cdecl(GetAddress(), args, sz);
	else
		raise(SystemException("Unsupported calltype"));
#elif _WIN64
	(void)int64_invoke_function_fastcall64(GetAddress(), (int64*)args, sz>>3);
#else
#error "Unknown OS"
#endif
}

String Declarator::get_QName() const
{
	return m_pOwnerScope->m_pNamespace->get_QName() + "::" + m_name;
}

void* Declarator::pointer_invoke_function(const void* args, size_t sz) const
{
	FunctionType* pFunType = static_cast<FunctionType*>(m_pType);
	VerifyImplemented();

#ifdef _M_IX86
	if (pFunType->m_funcspec == CallType_stdcall) return pointer_invoke_function_stdcall(GetAddress(), args, sz);
	else if (pFunType->m_funcspec == CallType_cdecl) return pointer_invoke_function_cdecl(GetAddress(), args, sz);
	else raise(SystemException("Unsupported calltype"));
#elif _WIN64
	return (void*)int64_invoke_function_fastcall64(GetAddress(), (int64*)args, sz>>3);
#else
#error "Unknown OS"
#endif
}

int32 Declarator::int32_invoke_function(const void* args, size_t sz) const
{
	VerifyImplemented();
	FunctionType* pFunType = static_cast<FunctionType*>(m_pType);

#ifdef _M_IX86
	if (pFunType->m_funcspec == CallType_stdcall)
		return int32_invoke_function_stdcall(GetAddress(), args, sz);
	else if (pFunType->m_funcspec == CallType_cdecl)
		return int32_invoke_function_cdecl(GetAddress(), args, sz);
	else
		raise(SystemException("Unsupported calltype"));
#elif _WIN64

	int64 args_stack[64];
	int64* p = args_stack;

	size_t nargs = std::max(0ULL/*args.size()*/, (size_t)4);

	return (int32)int64_invoke_function_fastcall64(GetAddress(), (int64*)args_stack, nargs);
#else
#error "Unknown OS"
#endif
}

int64 Declarator::int64_invoke_function(const void* args, size_t sz) const
{
	VerifyImplemented();

	FunctionType* pFunType = m_pType->AsFunction();

#ifdef _M_IX86
	if (pFunType->m_funcspec == CallType_stdcall)
		return int64_invoke_function_stdcall(GetAddress(), args, sz);
	else if (pFunType->m_funcspec == CallType_cdecl)
		return int64_invoke_function_cdecl(GetAddress(), args, sz);
/*	else if (pFunType->m_funcspec == CallType_fastcall)
		VERIFY(0);//return int64_invoke_function_stdcall(m_offset, args, sz);
		*/
	else
		raise(SystemException("Unsupported calltype"));
#elif _WIN64
	return int64_invoke_function_fastcall64(GetAddress(), (int64*)args, sz>>3);
#else
#error "Unknown OS"
#endif
}

float Declarator::float_invoke_function(const void* args, size_t sz) const
{
	VerifyImplemented();

	FunctionType* pFunType = static_cast<FunctionType*>(m_pType);

#ifdef _M_IX86
	if (pFunType->m_funcspec == CallType_stdcall)
		return float_invoke_function_stdcall(GetAddress(), args, sz);
	else if (pFunType->m_funcspec == CallType_cdecl)
		return float_invoke_function_cdecl(GetAddress(), args, sz);
	else
		raise(SystemException("Unsupported calltype"));
	return 0;
#elif _WIN64
	return float_invoke_function_fastcall64(GetAddress(), (int64*)args, sz>>3);
#else
#error "Unknown OS"
#endif
}

double Declarator::double_invoke_function(const void* args, size_t sz) const
{
	FunctionType* pFunType = static_cast<FunctionType*>(m_pType);

	VerifyImplemented();

#ifdef _M_IX86
	if (pFunType->m_funcspec == CallType_stdcall)
		return double_invoke_function_stdcall(GetAddress(), args, sz);
	else if (pFunType->m_funcspec == CallType_cdecl)
		return double_invoke_function_cdecl(GetAddress(), args, sz);
	else
		raise(SystemException("Unsupported calltype"));
#elif _WIN64
	return double_invoke_function_fastcall64(GetAddress(), (int64*)args, sz>>3);
#else
#error "Unknown OS"
#endif
}

void Declarator::struct_invoke_function(const void* args, size_t sz, void* retaddress) const
{
	VerifyImplemented();

	FunctionType* pFunType = static_cast<FunctionType*>(m_pType);

#ifdef _M_IX86
	if (pFunType->m_funcspec == CallType_stdcall)
		struct_invoke_function_stdcall(GetAddress(), args, sz, retaddress);
	else if (pFunType->m_funcspec == CallType_cdecl)
		struct_invoke_function_cdecl(GetAddress(), args, sz, retaddress);
	else if (pFunType->m_funcspec == CallType_fastcall)
		raise(SystemException("Unsupported calltype"));
#elif _WIN64
	ASSERT(0);
	int64_invoke_function_fastcall64(GetAddress(), (int64*)args, sz>>3);
#else
#error "Unknown OS"
#endif
}

}	// System
