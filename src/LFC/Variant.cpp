#include "stdafx.h"
#include "LFC.h"
#include "Variant.h"

namespace System
{

#if 0
// 1024*1024 possible types = 1 million
Type** typesRoot[1024];
size_t numTypes;

void AddType(Type* pType)
{
	pType->m_index = numTypes;
	++numTypes;

	size_t rootindex = pType->m_index >> 10;
	size_t subindex = pType->m_index & 1023;

	if (typesRoot[rootindex] == nullptr)
	{
		typesRoot[rootindex] = new Type*[1024];
	}

	typesRoot[rootindex][subindex] = pType;
}

inline Type* getType(uint index)
{
	size_t rootindex = index >> 10;
	size_t subindex = index & 1023;

	ASSERT(rootindex < 1024);
	ASSERT(typesRoot[rootindex] != nullptr);

	return typesRoot[rootindex][subindex];
}
#endif

Variant::Variant(const VARIANT& v)
{
	Init(v);
}

Variant::Variant(const PROPVARIANT& pv)
{
	switch (pv.vt)
	{
// VT_LPSTR     [T][P]     null terminated string
	case VT_LPSTR:
		{
			m_pType = typeid(String);
			u.pObject = new ImmutableString<char>(string_copy(pv.pszVal));
		}
		break;

// VT_LPWSTR    [T][P]     wide null terminated string
	case VT_LPWSTR:
		{
			m_pType = typeid(String);
			u.pObject = new ImmutableString<wchar_t>(string_copy(pv.pwszVal));
		}
		break;

// VT_FILETIME [P]     FILETIME
	case VT_FILETIME:
		{
			m_pType = typeid(FILETIME);
			u.filetime_val = pv.filetime;
		}
		break;

	default:
		Init(*(const VARIANT*)&pv);
	}
}

void Variant::Init(const VARIANT& v)
{
	switch (v.vt)
	{
	case VT_NULL:
		{
			u.pObject = nullptr;
			m_pType = Types::get_nullType();
		}
		break;

	case VT_EMPTY:
		{
			u.pObject = nullptr;
			m_pType = typeid(void);
		}
		break;

	case VT_BOOL:
		{
			u.bool_val = (v.boolVal != VARIANT_FALSE);
			m_pType = typeid(bool);
		}
		break;

	case VT_I1:
		{
			u.char_val = v.cVal;
			m_pType = typeid(signed char);
		}
		break;

	case VT_UI1:
		{
			u.uint8_val = v.bVal;
			m_pType = typeid(unsigned char);
		}
		break;

	case VT_I2:
		{
			u.int16_val = v.iVal;
			m_pType = typeid(int16);
		}
		break;

	case VT_UI2:
		{
			u.uint16_val = v.uiVal;
			m_pType = typeid(uint16);
		}
		break;

	case VT_I4:
		{
			u.int32_val = v.lVal;
			m_pType = typeid(int32);
		}
		break;

	case VT_UI4:
		{
			u.uint32_val = v.ulVal;
			m_pType = typeid(uint32);
		}
		break;

	case VT_I8:
		{
			u.longlong_val = v.llVal;
			m_pType = typeid(long long);
		}
		break;

	case VT_UI8:
		{
			u.ulonglong_val = v.ullVal;
			m_pType = typeid(unsigned long long);
		}
		break;

	case VT_INT:
		{
			u.int32_val = v.intVal;
			m_pType = typeid(int);
		}
		break;

	case VT_UINT:
		{
			u.uint32_val = v.uintVal;
			m_pType = typeid(unsigned int);
		}
		break;

	case VT_R4:
		{
			u.float32_val = v.fltVal;
			m_pType = typeid(float);
		}
		break;

	case VT_R8:
		{
			u.float64_val = v.dblVal;
			m_pType = typeid(double);
		}
		break;

	case VT_BSTR:
		{
			m_pType = typeid(String);
			UINT len = SysStringLen(v.bstrVal);
			u.pObject = new ImmutableString<wchar_t>(string_copy(v.bstrVal, len));
		}
		break;

	case VT_UNKNOWN:
		{
#undef new
			::new (&u.ptr_val) ComPtr<IUnknown>(v.punkVal);
#define new _new
			m_pType = typeid(ComPtr<IUnknown>);
		}
		break;

	case VT_DISPATCH:
		{
#undef new
			::new (&u.ptr_val) ComPtr<IDispatch>(v.pdispVal);
#define new _new
			m_pType = typeid(ComPtr<IDispatch>);
		}
		break;

	case VT_BYREF:
		{
			m_pType = typeid(void*);
		}
		break;

	default:
		raise(SystemException("VARIANT.vt unsupported"));
	}
}

Variant::Variant(ComVariant&& v)
{
	switch (v.vt)
	{
		case VT_UNKNOWN:
		{
			m_pType = typeid(ComPtr<IUnknown>);
			*(IUnknown**)&u.ptr_val = v.punkVal;
		}
		break;

		case VT_DISPATCH:
		{
			m_pType = typeid(ComPtr<IDispatch>);
			*(IDispatch**)&u.ptr_val = v.pdispVal;
		}
		break;

		case VT_BSTR:
		{
			m_pType = typeid(ComBSTR);
			*(BSTR*)&u.ptr_val = v.bstrVal;
		}
		break;

		/*
		case VT_BOOL:
			m_pType = typeid(bool);
			u.bool_val = (v.boolVal != VARIANT_FALSE);
			break;

		case VT_I2:
			m_pType = typeid(short);
			u.int_val = v.iVal;
			break;

		case VT_UI2:
			m_pType = typeid(unsigned short);
			u.uint_val = v.uiVal;
			break;

		case VT_I4:
			m_pType = typeid(int);
			u.int_val = v.lVal;
			break;

		case VT_UI4:
			m_pType = typeid(unsigned int);
			u.uint_val = v.ulVal;
			break;

		case VT_R4:
			m_pType = typeid(float);
			u.float_val = v.fltVal;
			break;

		case VT_R8:
			m_pType = typeid(double);
			u.double_val = v.dblVal;
			break;

		default:
			VERIFY(0);	// TODO
			*/

		default:
			Init(v);
	}

	v.vt = VT_EMPTY;
}

Variant::Variant(const Variant& other)
{
	m_pType = other.m_pType;

	if (!other.IsPointer() && other.IsObject())
	{
		void* dst;
		const void* src;
		if (m_pType->get_sizeof() > sizeof(u))
		{
			u.ptr_val = new byte[m_pType->get_sizeof()];
			dst = u.ptr_val;
			src = other.u.ptr_val;
		}
		else
		{
			dst = &u.ptr_val;
			src = &other.u.ptr_val;
		}

		Declarator* copy_ctor = m_pType->AsClass()->GetCopyConstructor();
		if (copy_ctor && copy_ctor->IsImplemented())
		{
			copy_ctor->void_invoke_method(dst, src);
		}
		else
		{
			memcpy(dst, src, m_pType->get_sizeof());
		}
	}
	else
	{
		u = other.u;
	}
}

Variant::Variant(String&& str)
{
	u.pObject = str.m_stringObject;
	m_pType = typeid(String);

	str.m_stringObject = nullptr;	// reset other
}

Variant::Variant(const String& str)
{
#undef new
	::new (&u.ptr_val) String(str);
#define new _new
	m_pType = typeid(String);
}

Variant::Variant(StringIn str)
{
#undef new
	::new (&u.ptr_val) String(str);
#define new _new
	m_pType = typeid(String);
}

Variant::Variant(const StringBuilderBase& builder)
{
	// TODO: improve, uneccessary IncRef/DecRef ?

	String str = builder.BuildString();

#undef new
	::new (&u.ptr_val) String(str);
#define new _new
	m_pType = typeid(String);
}

Variant::Variant(const char* str, size_t len)
{
	if (len == ~0) len = strlen(str);

#undef new
	::new (&u.ptr_val) String(string_data<char>(str, len));
#define new _new
	m_pType = typeid(String);
}

Variant::Variant(const wchar_t* str, size_t len)
{
	if (len == ~0) len = wcslen(str);

#undef new
	::new (&u.ptr_val) String(string_data<wchar_t>(str, len));
#define new _new
	m_pType = typeid(String);
}

Variant::Variant(const void* src, Type* pType) : m_pType(pType)
{
	ClassType* pClass = pType->AsClass();

	void* dst;
	if (m_pType->get_sizeof() > sizeof(u))
	{
		u.ptr_val = new byte[m_pType->get_sizeof()];
		dst = u.ptr_val;
	}
	else
	{
		dst = &u.ptr_val;
	}

	Declarator* copy_ctor = m_pType->AsClass()->GetCopyConstructor();
	if (copy_ctor)
	{
		copy_ctor->void_invoke_method(dst, src);
	}
	else
	{
		memcpy(dst, src, m_pType->get_sizeof());
	}
}

Variant::Variant(bool, void* src, Type* pType)
{
	ASSERT(pType->GetPointerTo());

	m_pType = pType;
	u.ptr_val = src;

	if (src)
	{
		if (pType->GetPointerTo())
		{
			if (pType->GetPointerTo()->AsClass()->IsPolymorphic())
			{
				ClassType* pClass;
				u.ptr_val = LeftMost(src, &pClass);
				m_pType = pClass->get_pointerToThis();
			}
		}
	}
}

Variant::~Variant()
{
	if (m_pType)
	{
		if (m_pType->GetPointerTo() == nullptr)
		{
			ClassType* pClass = m_pType->AsClass();
			if (pClass)
			{
				Declarator* dtor = pClass->GetDestructor();

				if (pClass->get_sizeof() <= sizeof(u))	// inline
				{
					if (dtor)
					{
						dtor->void_invoke_method(&u.ptr_val);
					}
				}
				else if (u.ptr_val)
				{
					// TODO operator delete

					if (dtor)
					{
						dtor->void_invoke_method(u.ptr_val);
					}
					delete[] u.ptr_val;
				}
			}
		}

		m_pType = nullptr;
	}

	u.ptr_val = nullptr;
}

Type* Variant::GetPtrType() const
{
	if (m_pType == nullptr) return nullptr;

	Type* pType = m_pType->GetStripped();

	if (Type* p2 = pType->GetPointerTo())
	{
		return p2;
	}
	else
	{
		return pType;
	}
}

bool Variant::IsObject() const throw ()
{
	// pointer/reference to struct/class or embedded struct/class

	ASSERT(m_pType);

	Type* pType = m_pType->GetStripped();
	if (pType->get_Kind() == type_class) return true;

	pType = pType->GetPointerTo();
	if (pType && pType->AsClass()) return true;

	return false;
}

ClassType* Variant::GetObjectType() const
{
	ASSERT(m_pType);

	Type* pType = m_pType->GetStripped();

	if (Type* p2 = pType->GetPointerTo())
	{
		return p2->AsClass();
	}
	else
	{
		return pType->AsClass();
	}
}

Object* Variant::GetObject() const
{
	if (Type* pPtr = m_pType->GetPointerTo())
	{
		if (ClassType* pClass = pPtr->AsClass())
		{
			if (pClass->IsLeftMostDerivedFrom((ClassType*)typeid(Object).GetType()))
			{
				return u.pObject;
			}
		}
	}
	else if (ClassType* pClass = m_pType->AsClass())
	{
		if (pClass->IsLeftMostDerivedFrom((ClassType*)typeid(Object).GetType()))
		{
			if (pClass->get_sizeof() <= sizeof(u))	// inline
			{
				return (Object*)&u;
			}
			else
			{
				return u.pObject;
			}
		}
	}

	return nullptr;
}

Declarator* GetClassConverter(Type* fromType, ClassType* toType)
{
	Dispatch* pDispatch = GetDispatch(toType);

	Declarator* pMethod = nullptr;

	auto it = pDispatch->m_methodnames.find(toType->m_name);
	if (it != pDispatch->m_methodnames.end())
	{
		do
		{
			Declarator* pMethod2 = it->second;
			if (pMethod2->m_pType->AsFunction()->m_parameters.size() == 1)
			{
				Type* argType = pMethod2->m_pType->AsFunction()->m_parameters[0].m_pType->GetStripped();

				if (argType == fromType)
				{
					// Exact arg type match, just stop searching
					pMethod = pMethod2;
					break;
				}

				if (argType->get_Kind() == type_reference &&
					argType->GetPointerTo()->GetStripped() == fromType)
				{
					pMethod = pMethod2;
					break;
				}

				/*
				if (toType->GetClass() && argType->get_Kind() == type_pointer &&
					argType->GetPointerTo() == toType)
				{
					// Exact arg type match, just stop searching
					pMethod = pMethod2;
					break;
				}
				*/

				if (fromType->GetStripped()->IsOfType(argType))
				{
					if (pMethod)
					{
						return false;
						//raise(Exception("ambiguous: " + pMethod->ToString() + " " + pMethod2->ToString()));
					}
					pMethod = pMethod2;
				}
			}

			++it;
		}
		while (it->first == toType->m_name);
	}

	return pMethod;
}

Variant::Variant(const Variant& other, Type* pType) : m_pType(pType)
{
	if (ClassType* pClassType = pType->AsClass())
	{
		Declarator* converter_method = GetClassConverter(other.GetType(), pClassType);
		if (converter_method)
		{
			if (pType->get_sizeof() > sizeof(u))
			{
				u.ptr_val = new byte[pType->get_sizeof()];
			}

			void* ref;
			void* pargs;
			if (converter_method->m_pType->AsFunction()->m_parameters[0].m_pType->GetStripped()->get_Kind() == type_reference)
			{
				ref = (void*)&other.u.ptr_val;
				pargs = (void*)&ref;
			}
			else
			{
				pargs = (void*)&other.u.ptr_val;
			}

			void_invoke_method32(converter_method->GetAddress(), this->GetPtr(), pargs, other.GetType()->get_sizeof());
		}
		else
		{
			raise(Exception("Couldn't convert " + other.GetType()->ToString() + " to " + pType->ToString()));
		}
	}
	else
	{
		if (ClassType* pClassType = other.GetType()->AsClass())
		{
			// TODO
			// conversion operator
			ASSERT(0);
		}
		else
		{
			u = other.u;
		}
	}
}

void Variant::op_new(Type* pType)
{
	pType = m_pType->GetStripped();

	if (ClassType* pClass = pType->AsClass())
	{
		if (pClass->get_sizeof() > sizeof(u))
		{
			Declarator* op_new = pClass->GetOperatorNew();
			if (op_new)
			{
			}

			// TODO: operator new
			u.ptr_val = new byte[pClass->get_sizeof()];
		}
	}
}

void Variant::op_delete()
{
}

void* Variant::GetPtr() const
{
	Type* pType = m_pType->GetStripped();

	if (Type* pPtr2 = pType->GetPointerTo())
	{
		if (ClassType* pClass = pPtr2->AsClass())
		{
			return u.ptr_val;
		}
	}
	else if (ClassType* pClass = pType->AsClass())
	{
		if (pClass->get_sizeof() <= sizeof(u))	// inline
		{
			return (void*)&u.ptr_val;
		}
		else
		{
			return u.ptr_val;
		}
	}

	return nullptr;
}

Variant& Variant::operator = (const Variant& other)
{
	if (!other.IsPointer() && other.IsObject())
	{
		if (m_pType == other.m_pType)	// if same type, call copy assign operator, else copy constructor
		{
			size_t size = other.GetType()->get_sizeof();
			Declarator* op_assign = other.GetType()->AsClass()->GetCopyOperator();
			if (op_assign)
			{
				if (size <= sizeof(u))
				{
					op_assign->void_invoke_method(&u.ptr_val, &other.u.ptr_val);
				}
				else
				{
					// TODO operator new
					u.ptr_val = new byte[size];
					op_assign->void_invoke_method(u.ptr_val, other.u.ptr_val);
				}
			}
			else
			{
				if (size <= sizeof(u))
				{
					u.ptr_val = other.u.ptr_val;
				}
				else
				{
					// TODO operator new
					u.ptr_val = new byte[size];
					memcpy(u.ptr_val, other.u.ptr_val, size);
				}
			}
		}
		else
		{
			this->~Variant();
			/*
			ClassType* oldClass = m_pType->GetClass();
			if (oldClass)
			{
				Declarator* dtor = oldClass->GetDestructor();
				if (dtor)
				{
					dtor->void_invoke_method(&u.ptr_val);
				}
			}
			*/

			m_pType = other.m_pType;

			size_t size = other.GetType()->get_sizeof();
			Declarator* copy_ctor = other.GetType()->AsClass()->GetCopyConstructor();
			if (copy_ctor)
			{
				if (size <= sizeof(u))
				{
					copy_ctor->void_invoke_method(&u.ptr_val, &other.u.ptr_val);
				}
				else
				{
					// TODO operator new
					u.ptr_val = new byte[size];
					copy_ctor->void_invoke_method(u.ptr_val, other.u.ptr_val);
				}
			}
			else
			{
				if (size <= sizeof(u))
				{
					u.ptr_val = other.u.ptr_val;
				}
				else
				{
					// TODO operator new
					u.ptr_val = new byte[size];
					memcpy(u.ptr_val, other.u.ptr_val, size);
				}
			}
		}

		return *this;
	}

//	kind = other.kind;
	u = other.u;	// copy the entire record
	m_pType = other.m_pType;

	return *this;
}

bool Variant::operator ! ()
{
	ASSERT(m_pType);

	Type* pType = m_pType->GetStripped();
	switch (pType->get_Kind())
	{
	case type_bool:				return !u.bool_val;
	case type_int:				return !u.int_val;
	case type_unsigned_int:		return !u.uint_val;
	case type_pointer:			return !u.ptr_val;
	case type_class:
		{
			ClassType* pClass = static_cast<ClassType*>(pType);
		
			Declarator* decl = pClass->GetNotOperator();
			if (decl)
			{
				return decl->invoke_method<bool>(This());
			}

			throw new Exception(S("class has no ! operator"));
		}
		break;

	default:
		__assume(0);
		ASSERT(0);
	}
}

bool Variant::operator ! () const
{
	ASSERT(m_pType);

	Type* pType = m_pType->GetStripped();
	switch (pType->get_Kind())
	{
	case type_bool:				return !u.bool_val;
	case type_int:				return !u.int_val;
	case type_unsigned_int:		return !u.uint_val;
	case type_pointer:			return !u.ptr_val;
	case type_class:
		{
			ClassType* pClass = static_cast<ClassType*>(pType);
		
			Declarator* decl = pClass->GetNotOperatorConst();
			if (decl)
			{
				return decl->invoke_method<bool>(This());
			}

			throw new Exception(S("class has no ! operator"));
		}
		break;

	default:
		__assume(0);
		ASSERT(0);
	}
}

Variant::operator VARIANT () const
{
	ASSERT(m_pType);

	VARIANT vt;

	Type* pType = m_pType->GetBaseType();

	switch (pType->get_Kind())
	{
	case type_null:	// nullptr
		vt.vt = VT_NULL;
		break;

	case type_void:	// undefined
		vt.vt = VT_EMPTY;
		break;

	case type_bool:
		vt.vt = VT_BOOL;
		vt.boolVal = u.bool_val? VARIANT_TRUE: VARIANT_FALSE;
		break;

	case type_char:
	case type_signed_char:
		vt.vt = VT_I1;
		vt.cVal = u.char_val;
		break;

	case type_unsigned_char:
		vt.vt = VT_UI1;
		vt.bVal = u.uchar_val;
		break;

	case type_short:
		vt.vt = VT_I2;
		vt.iVal = u.short_val;
		break;

	case type_unsigned_short:
		vt.vt = VT_UI2;
		vt.uiVal = u.ushort_val;
		break;

	case type_int:
		vt.vt = VT_I4;
		vt.intVal = u.int_val;
		break;

	case type_unsigned_int:
		vt.vt = VT_UI4;
		vt.uintVal = u.uint_val;
		break;

#if INT_MAX == LONG_MAX

	case type_long:
		vt.vt = VT_I4;
		vt.lVal = u.long_val;
		break;

	case type_unsigned_long:
		vt.vt = VT_UI4;
		vt.uintVal = u.ulong_val;
		break;

#else

	case type_long:
		vt.vt = VT_I8;
		vt.llVal = u.long_val;
		break;

	case type_unsigned_long:
		vt.vt = VT_UI8;
		vt.ullVal = u.ulong_val;
		break;

#endif

	case type_long_long:
		vt.vt = VT_I8;
		vt.llVal = u.longlong_val;
		break;

	case type_unsigned_long_long:
		vt.vt = VT_UI8;
		vt.ullVal = u.ulonglong_val;
		break;

	case type_float:
		vt.vt = VT_R4;
		vt.fltVal = u.float_val;
		break;

	case type_double:
	case type_long_double:
		vt.vt = VT_R8;
		vt.dblVal = u.double_val;
		break;

	case type_pointer:
		{
			switch (pType->GetPointerTo()->get_Kind())
			{
			case type_void:
				vt.vt = VT_BYREF;	// Generic ByRef
				break;

				/*
			case type_bool:
				vt.vt = VT_BYREF|VT_BOOL;
				vt.pboolVal = (VARIANT_BOOL*)u.ptr_val;
				break;
				*/

			case type_short:
				vt.vt = VT_BYREF|VT_I2;
				vt.piVal = u.pshort_val;
				break;

			case type_unsigned_short:
				vt.vt = VT_BYREF|VT_UI2;
				vt.puiVal = u.pushort_val;
				break;

			case type_int:
				vt.vt = VT_BYREF|VT_I4;
				vt.pintVal = u.pint_val;
				break;

			case type_unsigned_int:
				vt.vt = VT_BYREF|VT_UI4;
				vt.puintVal = u.puint_val;
				break;

			case type_long_long:
				vt.vt = VT_BYREF|VT_I8;
				vt.pllVal = u.plonglong_val;
				break;

			case type_unsigned_long_long:
				vt.vt = VT_BYREF|VT_UI8;
				vt.pullVal = u.pulonglong_val;
				break;

			case type_float:
				vt.vt = VT_BYREF|VT_R4;
				vt.pfltVal = u.pfloat_val;
				break;

			case type_double:
			case type_long_double:
				vt.vt = VT_BYREF|VT_R8;
				vt.pdblVal = u.pdouble_val;
				break;

			case type_class:
				{
					if (u.ptr_val == nullptr)
					{
						// null object
						vt.vt = VT_EMPTY;
					}
					else
					{
						ASSERT(0);
					}
				}
				break;

			default:
				raise(SystemException("Failed to convert System::Variant to VARIANT"));
			}
		}
		break;

	case type_class:
		{
			ClassType* pClassType = m_pType->AsClass();
			if (pClassType == typeid(String))
			{
				String& pString = *(String*)&u.ptr_val;

				vt.vt = VT_BSTR;
				vt.bstrVal = SysAllocStringLen(pString.c_strw(), pString.GetLength32());
			}
			else
			{
				raise(SystemException("Failed to convert System::Variant to VARIANT"));
			}
		}
		break;

	default:
		raise(SystemException("Failed to convert System::Variant to VARIANT"));
	}

	return vt;
}

Variant::operator String ()
{
	ASSERT(m_pType);

	Type* pType = m_pType->GetStripped();
	if (pType == Types::get_nullType()) return nullptr;

	if (pType == typeid(String))
	{
		if (u.pObject == nullptr) return nullptr;

		ASSERT(dynamic_cast<StringObject*>(u.pObject) != nullptr);
		return String(static_cast<StringObject*>(u.pObject));
	}
	else if (ClassType* pClass = pType->AsClass())
	{
		Declarator* decl = pClass->GetConversionOperator(typeid(String));
		if (decl)
		{
			return decl->invoke_method<String>(This());
		}
	}

	throw new Exception("Not a String");
}

Variant::operator String () const
{
	ASSERT(m_pType);

	Type* pType = m_pType->GetStripped();
	if (pType == Types::get_nullType()) return nullptr;

	if (pType == typeid(String))
	{
		if (u.pObject == nullptr) return nullptr;

		ASSERT(dynamic_cast<StringObject*>(u.pObject) != nullptr);
		return String(static_cast<StringObject*>(u.pObject));
	}
	else if (ClassType* pClass = pType->AsClass())
	{
		Declarator* decl = pClass->GetConversionOperatorConst(typeid(String));
		if (decl)
		{
			return decl->invoke_method<String>(This());
		}
	}

	throw new Exception("Not a String");
}

Variant::operator bool ()
{
	Type* pType = m_pType->GetStripped();
	if(pType == typeid(bool))
	{
		return u.bool_val;
	}
	else if (ClassType* pClass = pType->AsClass())
	{
		Declarator* decl = pClass->GetConversionOperator(typeid(bool));
		if (decl)
		{
			return decl->invoke_method<bool>(This());
		}
		throw new Exception("no operator bool()");
	}

	throw new Exception("Cannot convert to bool");
}

Variant::operator bool () const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	default:
		// TODO operator bool
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to bool"));
	}
}

template<> bool Variant::CanConvertTo<int>() const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
	case type_wchar_t:
	case type_signed_char:
	case type_unsigned_char:
	case type_short:
	case type_unsigned_short:
	case type_int:
#if LONG_MAX == INT_MAX
	case type_long:
#endif
		return true;

	default:
		return false;
	}
}

Variant::operator signed char ()
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_char:
		return u.char_val;

	case type_signed_char:
		return u.schar_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to signed char"));
	}
}

Variant::operator signed char () const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_char:
		return u.char_val;

	case type_signed_char:
		return u.schar_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to signed char"));
	}
}

Variant::operator unsigned char ()
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_unsigned_char:
		return u.uchar_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to unsigned char"));
	}
}

Variant::operator unsigned char () const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_unsigned_char:
		return u.uchar_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to unsigned char"));
	}
}

Variant::operator int ()
{
	ASSERT(m_pType);

	Type* pType = m_pType->GetBaseType();
	switch (pType->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_wchar_t:
		return u.wchar_t_val;

	case type_signed_char:
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		return u.int_val;

#if LONG_MAX == INT_MAX
	case type_long:
		return u.long_val;
#endif

	case type_class:
	{
		ClassType* pClass = static_cast<ClassType*>(pType);

		Declarator* decl = pClass->GetConversionOperator(typeid(int));
		if (decl)
		{
			return decl->invoke_method<int>(This());
		}
		throw new Exception("no operator int()");
	}
	break;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to int"));
	}
}

Variant::operator int () const
{
	ASSERT(m_pType);

	Type* pType = m_pType->GetBaseType();
	switch (pType->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_wchar_t:
		return u.wchar_t_val;

	case type_signed_char:
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		return u.int_val;

#if LONG_MAX == INT_MAX
	case type_long:
		return u.long_val;
#endif

	case type_class:
	{
		ClassType* pClass = static_cast<ClassType*>(pType);

		Declarator* decl = pClass->GetConversionOperatorConst(typeid(int));
		if (decl)
		{
			return decl->invoke_method<int>(This());
		}
		throw new Exception("no operator int()");
	}
	break;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to int"));
	}
}

Variant::operator unsigned int ()
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_wchar_t:
		return u.wchar_t_val;

	case type_unsigned_char:
		return u.uint8_val;

	case type_unsigned_short:
		return u.uint16_val;

	case type_unsigned_int:
		return u.uint32_val;

#if ULONG_MAX == UINT_MAX
	case type_unsigned_long:
		return u.ulong_val;
#endif

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to unsigned int"));
	}
}

Variant::operator unsigned int () const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_wchar_t:
		return u.wchar_t_val;

	case type_unsigned_char:
		return u.uint8_val;

	case type_unsigned_short:
		return u.uint16_val;

	case type_unsigned_int:
		return u.uint32_val;

#if ULONG_MAX == UINT_MAX
	case type_unsigned_long:
		return u.ulong_val;
#endif

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to unsigned int"));
	}
}

Variant::operator long () const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_wchar_t:
		return u.wchar_t_val;

	case type_signed_char:
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		return u.int_val;

	case type_long:
		return u.long_val;

#if LONG_MAX == I64_MAX

	case type_unsigned_int:
		return u.uint_val;

	case type_long_long:
		return u.longlong_val;

#endif

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to long"));
	}
}

Variant::operator unsigned long () const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_unsigned_long:
		return u.ulong_val;

#if ULONG_MAX == _UI64_MAX
	case type_unsigned_long_long:
		return u.ulonglong_val;
#endif

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to unsigned long"));
	}
}

Variant::operator long long ()
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_wchar_t:
		return u.wchar_t_val;

	case type_signed_char:
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		return u.int_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_long:
		return u.long_val;

#if ULONG_MAX <= _I64_MAX
	case type_unsigned_long:
		return u.ulong_val;
#endif

	case type_long_long:
		return u.longlong_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to long long"));
	}
}

Variant::operator long long () const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_wchar_t:
		return u.wchar_t_val;

	case type_signed_char:
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		return u.int_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_long:
		return u.long_val;

#if ULONG_MAX <= _I64_MAX
	case type_unsigned_long:
		return u.ulong_val;
#endif

	case type_long_long:
		return u.longlong_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to long long"));
	}
}

Variant::operator unsigned long long ()
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_unsigned_long:
		return u.ulong_val;

	case type_unsigned_long_long:
		return u.ulonglong_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to unsigned long long"));
	}
}

Variant::operator unsigned long long () const
{
	ASSERT(m_pType);

	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_unsigned_long:
		return u.ulong_val;

	case type_unsigned_long_long:
		return u.ulonglong_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to unsigned long long"));
	}
}

Variant::operator float ()
{
	ASSERT(m_pType);

	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_float:
		return u.float_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to float"));
	}
}

Variant::operator float () const
{
	ASSERT(m_pType);

	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_float:
		return u.float_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to float"));
	}
}

Variant::operator double ()
{
	ASSERT(m_pType);

	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_float:
		return u.float_val;

	case type_double:
	case type_long_double:
		return u.double_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to double"));
	}
}

Variant::operator double () const
{
	ASSERT(m_pType);

	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_float:
		return u.float_val;

	case type_double:
	case type_long_double:
		return u.double_val;

	default:
		raise(OverflowException(L"Cannot convert " + m_pType->ToString() + " to double"));
	}
}

bool Variant::ToBool() const
{
	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		if ((u.int8_val & ~1) == 0) return u.int8_val & 1;

	case type_unsigned_char:
		if ((u.uint8_val & ~1) == 0) return u.uint8_val & 1;

	case type_short:
		if ((u.int16_val & ~1) == 0) return u.int16_val & 1;

	case type_unsigned_short:
		if ((u.uint16_val & ~1) == 0) return u.uint16_val & 1;

	case type_int:
		if ((u.int32_val & ~1) == 0) return u.int32_val & 1;

	case type_unsigned_int:
		if ((u.uint32_val & ~1) == 0) return u.uint32_val & 1;

	case type_long:
		if ((u.long_val & ~1) == 0) return u.long_val & 1;

	case type_unsigned_long:
		if ((u.ulong_val & ~1) == 0) return u.ulong_val & 1;

	case type_long_long:
		if ((u.int64_val & ~1) == 0) return u.int64_val & 1;

	case type_unsigned_long_long:
		if ((u.uint64_val & ~1) == 0) return u.uint64_val & 1;
	}

	raise(OverflowException(L"Cannot convert to bool"));
}

int Variant::ToInt() const
{
	ASSERT(m_pType);
	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		return u.int_val;

	case type_unsigned_int:
		if (u.uint_val > INT_MAX) raise(OverflowException("value to large, cannot be converted to int"));
		return u.uint_val;

	case type_long:
#if LONG_MAX > INT_MAX
		if (u.long_val > INT_MAX) raise(OverflowException("value to large, cannot be converted to int"));
#endif
		return u.long_val;

	case type_unsigned_long:
		if (u.ulong_val > INT_MAX) raise(OverflowException("value to large, cannot be converted to int"));
		return u.ulong_val;

	case type_unsigned_long_long:
		if (u.ulonglong_val > INT_MAX) raise(OverflowException("value to large, cannot be converted to int"));
		return (int)u.ulonglong_val;

	default:
		raise(OverflowException(L"Cannot convert to int"));
	}
}

unsigned int Variant::ToUInt() const
{
	ASSERT(m_pType);
	switch (m_pType->GetBaseType()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		if (u.schar_val < 0) raise(OverflowException("negative value, cannot be converted to unsigned int"));
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		if (u.short_val < 0) raise(OverflowException("negative value, cannot be converted to unsigned int"));
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		if (u.int_val < 0) raise(OverflowException("negative value, cannot be converted to unsigned int"));
		return u.int_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_long:
		if (u.long_val < 0) raise(OverflowException("negative value, cannot be converted to unsigned int"));
#if LONG_MAX > INT_MAX
		if (u.long_val > INT_MAX) raise(OverflowException("value to large, cannot be converted to int"));
#endif
		return u.long_val;

	case type_unsigned_long:
#if ULONG_MAX > UINT_MAX
		if (u.ulong_val > UINT_MAX) raise(OverflowException("value to large, cannot be converted to unsigned int"));
#endif
		return u.ulong_val;

	case type_unsigned_long_long:
		if (u.ulonglong_val > UINT_MAX) raise(OverflowException("value to large, cannot be converted to unsigned int"));
		return (int)u.ulonglong_val;

	default:
		raise(OverflowException(L"Cannot convert to unsigned int"));
	}
}

long Variant::ToLong() const
{
	ASSERT(0);
#if 0
	switch (kind)
	{
	case VARKIND_BOOL:
		return u.bool_val;

	case VARKIND_INT8:
		return u.int8_val;

	case VARKIND_UINT8:
		return u.uint8_val;

	case VARKIND_INT16:
		return u.int16_val;

	case VARKIND_UINT16:
		return u.uint16_val;

	case VARKIND_INT32:
		return u.int32_val;

#if LONG_MAX == _I64_MAX

	case VARKIND_UINT32:
		return u.uint32_val;

	case VARKIND_INT64:
		return u.int64_val;
#endif

	default:
		raise(OverflowException(L"Cannot convert to long"));
	}
#endif
	return 0;
}

unsigned long Variant::ToULong() const
{
	ASSERT(m_pType);
	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		if (u.schar_val < 0) raise(OverflowException("negative value cannot be converted to unsigned long"));
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		if (u.short_val < 0) raise(OverflowException("negative value cannot be converted to unsigned long"));
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		if (u.int_val < 0) raise(OverflowException("negative value cannot be converted to unsigned long"));
		return u.int_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_long_long:
		if (u.longlong_val < 0) raise(OverflowException("negative value cannot be converted to unsigned long"));
#if ULONG_MAX < _I64_MAX
		if (u.longlong_val > ULONG_MAX) raise(OverflowException("value too large to be converted to unsigned long"));
#endif
		return (unsigned long)u.longlong_val;

	case type_unsigned_long_long:
#if ULONG_MAX < _UI64_MAX
		if (u.ulonglong_val > ULONG_MAX) raise(OverflowException("value too large to be converted to unsigned long"));
#endif
		return (unsigned long)u.ulonglong_val;

	default:
		raise(OverflowException(L"Cannot convert to unsigned long"));
	}
}

long long Variant::ToInt64() const
{
	ASSERT(m_pType);

	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		return u.int_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_long:
		return u.long_val;

	case type_unsigned_long:
#if ULONG_MAX > _I64_MAX
		if (u.ulong_val > _I64_MAX)
		{
			if (ok == nullptr) raise(OverflowException("value too large to be converted to int64"));
		}
#endif
		return u.ulong_val;

	case type_long_long:
		return u.longlong_val;

	case type_unsigned_long_long:
		if (u.ulonglong_val > _I64_MAX) raise(OverflowException("value too large to be converted to int64"));
		return (unsigned long)u.ulonglong_val;

	default:
		raise(OverflowException(L"Cannot convert to int64"));
	}
}

long long Variant::ToInt64(bool* ok) const
{
	ASSERT(m_pType);

	if (ok == nullptr) throw new ArgumentNullException();
	*ok = true;

	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		return u.schar_val;

	case type_unsigned_char:
		return u.uchar_val;

	case type_short:
		return u.short_val;

	case type_unsigned_short:
		return u.ushort_val;

	case type_int:
		return u.int_val;

	case type_unsigned_int:
		return u.uint_val;

	case type_long:
		return u.long_val;

	case type_unsigned_long:
#if ULONG_MAX > _I64_MAX
		if (u.ulong_val > _I64_MAX)
		{
			*ok = false;
		}
#endif
		return u.ulong_val;

	case type_long_long:
		return u.longlong_val;

	case type_unsigned_long_long:
		if (u.ulonglong_val > _I64_MAX) *ok = false;
		return (unsigned long)u.ulonglong_val;
	}

	*ok = false;
	return 0;
}

float Variant::ToFloat() const
{
	ASSERT(m_pType);
	switch (m_pType->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		return u.int8_val;

	case type_unsigned_char:
		return u.uint8_val;

	case type_short:
		return u.int16_val;

	case type_unsigned_short:
		return u.uint16_val;

	case type_int:
		return (float)u.int32_val;

	case type_unsigned_int:
		ASSERT(0);
		return (float)u.uint32_val;

	case type_long_long:
		ASSERT(0);
		return (float)u.int64_val;

	case type_unsigned_long_long:
		ASSERT(0);
		return (float)u.uint64_val;

	case type_float:
		return u.float32_val;
		
	case type_double:
		return (float)u.float64_val;

	default:
		raise(OverflowException(L"Cannot convert to float"));
	}
}

float Variant::ToFloat(bool* ok) const
{
	ASSERT(m_pType);

	if (ok == nullptr) throw new ArgumentNullException();
	*ok = true;

	switch (m_pType->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		return u.int8_val;

	case type_unsigned_char:
		return u.uint8_val;

	case type_short:
		return u.int16_val;

	case type_unsigned_short:
		return u.uint16_val;

	case type_int:
		return (float)u.int32_val;

	case type_unsigned_int:
		ASSERT(0);
		return (float)u.uint32_val;

	case type_long_long:
		ASSERT(0);
		return (float)u.int64_val;

	case type_unsigned_long_long:
		ASSERT(0);
		return (float)u.uint64_val;

	case type_float:
		return u.float32_val;
		
	case type_double:
		return (float)u.float64_val;
	}

	*ok = false;
	return 0;
}

double Variant::ToDouble() const
{
	ASSERT(m_pType);
	switch (m_pType->get_Kind())
	{
	case type_bool:
		return u.bool_val;

	case type_signed_char:
		return u.int8_val;

	case type_unsigned_char:
		return u.uint8_val;

	case type_short:
		return u.int16_val;

	case type_unsigned_short:
		return u.uint16_val;

	case type_int:
		return (double)u.int32_val;

	case type_unsigned_int:
		return (double)u.uint32_val;

	case type_long_long:
		return (double)u.int64_val;

	case type_unsigned_long_long:
		return (double)u.uint64_val;

	case type_float:
		return u.float32_val;
		
	case type_double:
		return u.float64_val;

	default:
		raise(OverflowException(L"Cannot convert to double"));
	}
}

bool Variant::operator == (bool value) const
{
	return operator bool() == value;
}

bool Variant::operator == (char value) const
{
	return operator int() == value;
}

bool Variant::operator == (wchar_t value) const
{
	return operator int() == value;
}

bool Variant::operator == (signed char value) const
{
	return operator int() == value;
}

bool Variant::operator == (unsigned char value) const
{
	return operator int() == value;
}

bool Variant::operator == (short value) const
{
	return operator int() == value;
}

bool Variant::operator == (unsigned short value) const
{
	return operator int() == value;
}

bool Variant::operator == (int value) const
{
	// Special handling of testing for NULL pointer
	// TODO: remove ???
	if (value == 0)
	{
		// operator == (nullptr);

		if (IsNull()) return true;
		if (IsPointer())
		{
			return u.ptr_val == nullptr;
		}
	}

	return operator int() == value;
}

bool Variant::operator == (decltype(nullptr)) const
{
	if (IsNull()) return true;
	if (IsPointer())
	{
		return u.ptr_val == nullptr;
	}

	// TODO, delegate to class

	raise(Exception("Incompatible types"));
}

bool Variant::operator == (unsigned int value) const
{
	return operator unsigned int() == value;
}

bool Variant::operator == (long value) const
{
	return operator long() == value;
}

bool Variant::operator == (unsigned long value) const
{
	return operator unsigned long() == value;
}

bool Variant::operator == (long long value) const
{
	return operator long long() == value;
}

bool Variant::operator == (unsigned long long value) const
{
	return operator unsigned long long() == value;
}

bool Variant::operator < (bool value) const
{
	return operator bool() < value;
}

bool Variant::operator < (char value) const
{
	return operator int() < value;
}

bool Variant::operator < (wchar_t value) const
{
	return operator int() < value;
}

bool Variant::operator < (signed char value) const
{
	return operator int() < value;
}

bool Variant::operator < (unsigned char value) const
{
	return operator int() < value;
}

bool Variant::operator < (short value) const
{
	return operator int() < value;
}

bool Variant::operator < (unsigned short value) const
{
	return operator int() < value;
}

bool Variant::operator < (int value) const
{
	return operator int() < value;
}

bool Variant::operator < (unsigned int value) const
{
	return operator unsigned int() < value;
}

bool Variant::operator < (long value) const
{
	return operator long() < value;
}

bool Variant::operator < (unsigned long value) const
{
	return operator unsigned long() < value;
}

bool Variant::operator < (long long value) const
{
	return operator long long() < value;
}

bool Variant::operator < (unsigned long long value) const
{
	return operator unsigned long long() < value;
}

bool Variant::operator == (const Variant& other) const
{
	if (m_pType->GetStripped() != other.m_pType->GetStripped()) return false;

	if (IsBool()) return u.bool_val == other.u.bool_val;

	if (IsInt()) return int(*this) == int(other);
	else if (IsFloat()) return float(*this) == float(other);
	else if (IsDouble()) return double(*this) == double(other);

	return false;
}

bool Variant::operator > (const Variant& other) const
{
	if (m_pType->GetStripped() != other.m_pType->GetStripped()) return false;

	if (IsInt()) return int(*this) > int(other);
	else if (IsFloat()) return float(*this) > float(other);
	else if (IsDouble()) return double(*this) > double(other);

	return false;
}

bool Variant::operator < (const Variant& other) const
{
	if (m_pType->GetStripped() != other.m_pType->GetStripped()) return false;

	if (IsInt()) return int(*this) < int(other);
	else if (IsFloat()) return float(*this) < float(other);
	else if (IsDouble()) return double(*this) < double(other);

	return false;
}

bool Variant::operator >= (const Variant& other) const
{
	if (m_pType->GetStripped() != other.m_pType->GetStripped()) return false;

	if (IsInt()) return int(*this) >= int(other);
	else if (IsFloat()) return float(*this) >= float(other);
	else if (IsDouble()) return double(*this) >= double(other);

	return false;
}

bool Variant::operator <= (const Variant& other) const
{
	if (m_pType->GetStripped() != other.m_pType->GetStripped()) return false;

	if (IsInt()) return int(*this) <= int(other);
	else if (IsFloat()) return float(*this) <= float(other);
	else if (IsDouble()) return double(*this) <= double(other);

	return false;
}

Variant& Variant::operator ++ ()
{
	if (m_pType)
	{
		switch (m_pType->get_Kind())
		{
		case type_bool:
			++u.bool_val;	// C++ sais: set to true
			break;

		case type_signed_char:
			++u.schar_val;
			break;

		case type_unsigned_char:
			++u.uchar_val;
			break;

		case type_short:
			++u.short_val;
			break;

		case type_unsigned_short:
			++u.ushort_val;
			break;

		case type_int:
			++u.int_val;
			break;

		case type_unsigned_int:
			++u.uint_val;
			break;

		case type_long:
			++u.long_val;
			break;

		case type_unsigned_long:
			++u.ulong_val;
			break;

		case type_long_long:
			++u.longlong_val;
			break;

		case type_unsigned_long_long:
			++u.ulonglong_val;
			break;

		case type_float:
			++u.float_val;
			break;

		case type_double:
		case type_long_double:
			++u.double_val;
			break;

		default:
			raise(SystemException("wrong type"));
		}
	}
	else
	{
		VERIFY(0);
	}

	return *this;
}

Variant& Variant::operator -- ()
{
	if (m_pType)
	{
		switch (m_pType->get_Kind())
		{
		case type_signed_char:
			--u.schar_val;
			break;

		case type_unsigned_char:
			--u.uchar_val;
			break;

		case type_short:
			--u.short_val;
			break;

		case type_unsigned_short:
			--u.ushort_val;
			break;

		case type_int:
			--u.int_val;
			break;

		case type_unsigned_int:
			--u.uint_val;
			break;

		case type_long:
			--u.long_val;
			break;

		case type_unsigned_long:
			--u.ulong_val;
			break;

		case type_long_long:
			--u.longlong_val;
			break;

		case type_unsigned_long_long:
			--u.ulonglong_val;
			break;

		case type_float:
			--u.float_val;
			break;

		case type_double:
		case type_long_double:
			--u.double_val;
			break;

		default:
			raise(SystemException("wrong type"));
		}
	}
	else
	{
		VERIFY(0);
	}

	return *this;
}

Variant Variant::operator ++ (int)
{
	Variant v(*this);
	this->operator++();
	return v;
}

Variant Variant::operator -- (int)
{
	Variant v(*this);
	this->operator--();
	return v;
}

String Variant::ToString() const
{
	ASSERT(m_pType);

	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_null:
		return S("null");

	case type_void:
		return S("undefined");

	case type_bool:
		return u.bool_val? S("true"): S("false");

		/*
	case type_char:
		return "'" + String::FromNumber(u.int8_val);
		*/

	case type_signed_char:
		return String::FromNumber(u.schar_val);

	case type_unsigned_char:
		return String::FromNumber(u.uchar_val);

	case type_short:
		return String::FromNumber(u.short_val);

	case type_unsigned_short:
		return String::FromNumber(u.ushort_val);

	case type_int:
		return String::FromNumber(u.int_val);

	case type_unsigned_int:
		return String::FromNumber(u.uint_val);

	case type_long:
		return String::FromNumber(u.long_val);

	case type_unsigned_long:
		return String::FromNumber(u.ulong_val);

	case type_long_long:
		return String::FromNumber(u.longlong_val);

	case type_unsigned_long_long:
		return String::FromNumber(u.ulonglong_val);

	case type_float:
		return String::FromNumber(u.float_val);

	case type_double:
	case type_long_double:
		return String::FromNumber(u.double_val);

	case type_enum:
		{
			long long value;
			EnumType* pEnum = static_cast<EnumType*>(m_pType);
			if (pEnum->m_baseType)
			{
				switch (pEnum->m_baseType->get_Kind())
				{
				case type_bool:
					value = u.bool_val;
					break;

				case type_char:
					value = u.char_val;
					break;

				case type_wchar_t:
					value = u.wchar_t_val;
					break;

				case type_signed_char:
					value = u.schar_val;
					break;

				case type_unsigned_char:
					value = u.uchar_val;
					break;

				case type_short:
					value = u.short_val;
					break;

				case type_unsigned_short:
					value = u.ushort_val;
					break;

				case type_int:
					value = u.int_val;
					break;

				case type_unsigned_int:
					value = u.uint_val;
					break;

				case type_long:
					value = u.long_val;
					break;

				case type_unsigned_long:
					value = u.ulong_val;
					break;

				case type_long_long:
					value = u.longlong_val;
					break;

				default:
					raise(SystemException(S("Unsupported enum baseType")));
				}
			}
			else
			{
				value = u.int_val;
			}

			return pEnum->GetItemL(value)->m_name;
		}
		break;

	case type_class:
		{
			ClassType* pClassType = m_pType->AsClass();

			if (pClassType->IsPolymorphic())
			{
				Object* obj = __dynamic_cast<Object*>(u.pObject);
				if (obj)
					return obj->ToString();
				else
					return S("TODO to string");
			}
			else if (pClassType == typeid(String))
			{
				return *(String*)&u.ptr_val;
			}
			else if (pClassType->m_qname.BeginsWith("System::vector<"))
			{
				ArrayBaseData* arraybase = ((ArrayBaseData*)this->GetPtr());
				Declarator* pElem = pClassType->GetMemberByOffset(offsetof(ArrayBaseData, m_pData));
				IO::StringWriter writer;

				Type* pType = pElem->get_Type()->GetPointerTo();

				byte* ptr = (byte*)arraybase->m_pData;
				size_t sizeofElem = pType->get_sizeof();

				for (size_t i = 0; i < arraybase->m_nSize; ++i)
				{
					if (i > 0) writer << ",";
					PrintValue(writer, pType, ptr, ",");

					ptr += sizeofElem;
				}

				return writer.str();
			}
			else
			{
				IO::StringWriter writer;
				if (u.ptr_val)
				{
					PrintValue(writer, pClassType, (byte*)u.ptr_val, ",");
				}
				return writer.str();
			}
		}
		break;

	case type_pointer:
	case type_reference:
		{
			return "0x" + String::FromNumber((ULONG_PTR)u.ptr_val, 16);
		}
		break;

	default:
		ASSERT(0);
	}

	return nullptr;
}

Variant Variant::operator () () const
{
	ASSERT(m_pType->get_Kind() == type_function);
		
//	Dispatch* dispatch;
	return Variant();
}

Variant Variant::Deref() const
{
	Type* pType = m_pType->GetBaseType();
	switch (pType->get_Kind())
	{
	case type_pointer:
		{
			Type* p2 = m_pType->GetPointerTo();

			switch (p2->get_Kind())
			{
			case type_bool: return Variant(*u.pbool_val, p2);
			case type_char: return Variant(*u.pchar_val, p2);
			case type_int: return Variant(*u.pint_val, p2);
			case type_unsigned_int: return Variant(*u.puint_val, p2);
			case type_long: return Variant(*u.plong_val, p2);
			case type_unsigned_long: return Variant(*u.pulong_val, p2);
			case type_float: return Variant(*u.pfloat_val, p2);
			case type_double: return Variant(*u.pdouble_val, p2);
			case type_long_double: return Variant(*u.plongdouble_val, p2);

			case type_class:
				{
					ASSERT(0);
				}
				break;

			default:
				raise(Exception("Cannot"));
			}
		}
		break;

	case type_class:
		{
			ASSERT(0);
		}
		break;
	}

	raise(Exception());
}

/*
Object* Variant::operator -> () const
{
	if (m_pType->get_Kind() != type_class)
	{
		raise(Exception("not an object"));
	}

	if (u.pObject == NULL)
	{
		raise(Exception("accessing null object"));
	}

	return u.pObject;
}
*/

LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& writer, const Variant& v)
{
	writer << v.ToString();
	return writer;
}

LFCEXT bool ToBool(const Variant& v)
{
	return v.ToBool();
}

LFCEXT int ToInt(const Variant& v)
{
	return v.ToInt();
}

LFCEXT unsigned int ToUInt(const Variant& v)
{
	return v.ToUInt();
}

LFCEXT float ToFloat(const Variant& v)
{
	return v.ToFloat();
}

LFCEXT double ToDouble(const Variant& v)
{
	return v.ToDouble();
}

LFCEXT bool ToBool(Object* obj)
{
		 if (obj->GetType() == typeid(BoolObject).GetType())		return static_cast<BoolObject*>(obj)->GetValue();
	// TODO ??
	else if (obj->GetType() == typeid(IntObject).GetType())		return static_cast<IntObject*>(obj)->GetValue() != 0;
	else if (obj->GetType() == typeid(UIntObject).GetType())		return static_cast<UIntObject*>(obj)->GetValue() != 0;
	else
	{
		ASSERT(0);
		raise(OverflowException("Wrong type"));
	}
}

LFCEXT int ToInt(Object* obj)
{
	// TODO ??

		 if (obj->GetType() == typeid(DoubleObject).GetType())		return static_cast<DoubleObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(FloatObject).GetType())		return static_cast<FloatObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(IntObject).GetType())		return static_cast<IntObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(BoolObject).GetType())		return static_cast<BoolObject*>(obj)->GetValue();
	else
	{
		ASSERT(0);
		raise(Exception(S("Wrong type")));
	}
}

LFCEXT float ToFloat(Object* obj)
{

		if (obj->GetType() == typeid(DoubleObject).GetType())		return static_cast<DoubleObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(FloatObject).GetType())		return static_cast<FloatObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(IntObject).GetType())			return static_cast<IntObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(BoolObject).GetType())		return static_cast<BoolObject*>(obj)->GetValue();
	else
	{
		ASSERT(0);
		raise(Exception(S("Wrong type")));
	}
}

LFCEXT double ToDouble(Object* obj)
{
		 if (obj->GetType() == typeid(DoubleObject).GetType())		return static_cast<DoubleObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(FloatObject).GetType())		return static_cast<FloatObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(IntObject).GetType())			return static_cast<IntObject*>(obj)->GetValue();
	else if (obj->GetType() == typeid(BoolObject).GetType())		return static_cast<BoolObject*>(obj)->GetValue();
	else
	{
		ASSERT(0);
		raise(Exception(S("Wrong type")));
	}
}

// TODO
typedef IntObject LongObject;
typedef UIntObject ULongObject;

Object* Variant::box_cast() const
{
	switch (m_pType->GetStripped()->get_Kind())
	{
	case type_bool:
		return BoolObject::GetObject(u.bool_val);

	case type_signed_char:
		return SByteObject::GetObject(u.schar_val);

	case type_unsigned_char:
		return UByteObject::GetObject(u.uchar_val);

	case type_short:
		return IntObject::GetObject(u.short_val);

	case type_unsigned_short:
		return UIntObject::GetObject(u.ushort_val);

	case type_int:
		return IntObject::GetObject(u.int_val);

	case type_unsigned_int:
		return UIntObject::GetObject(u.uint_val);

	case type_long:
		return LongObject::GetObject(u.long_val);

	case type_unsigned_long:
		return ULongObject::GetObject(u.ulong_val);

	case type_long_long:
		return Int64Object::GetObject(u.longlong_val);

	case type_unsigned_long_long:
		return UInt64Object::GetObject(u.ulonglong_val);

	case type_float:
		return FloatObject::GetObject(u.float_val);

	case type_double:
	case type_long_double:
		return DoubleObject::GetObject(u.double_val);
	}

	return (Object*)(this);
}

}	// System
