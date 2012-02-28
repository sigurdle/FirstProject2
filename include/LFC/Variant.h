#ifndef System_Variant_h
#define System_Variant_h

namespace System
{

/**

The Variant class can hold a value of any type. This class consists of two datamembers:
The Type and the VariantValue. A Variant can also have the special value of typeid(void),
which is the same as 'undefined'.

Variant makes use of the type system to be a very versatile class.

@code
class someclass
{
public:
	operator bool () const;
	void* operator [] (int index) const;
};

someclass instance;
Variant var(instance);

bool boolVal = var;     // invokes someclass::operator bool () const
void* p = var[6];       // invokes someclass::operator [] (6) const

@endcode

<h2>How does Variant store its data?</h2>

Variant stores its data in a VariantValue, which is a union. Variant can store small objects
inline, if the object doesn't fit within sizeof(VariantValue), then memory is allocated. The memory is
allocated/freed with operator new/delete of the class if any are specified.

In a 32-bit application, sizeof(VariantValue) is 8. In a 64-bit application sizeof(VariantValue) is
16. The reason for making it 16 bytes is so that it is able to store arrays inline.
struct ArrayData
{
void* data;
size_t nSize;
};
This results in 8 bytes on 32bit, and 16 bytes on 64-bit

You can store a C-Array like this:

@code

int arr[4] = {10, 20, 30, 40, 50};
Variant var(arr);

// The array can be accessed
var[2];             // returns 30
var.ArrayLength();	// returns 4
@endcode

If the Variant stores a class instance. The destructor for the class will be called when
the Variant goes out of scope.

@code
IUnknown* p = ...;
ComPtr<IUnknown> ptr(p);		// Will call p->AddRef()
Variant var(ptr);	// Will call the copy constructor of ptr, which in return will call p->AddRef()

// ... going out of scope

~var() will call the destructor ~ComPtr, which in return will call Release()
~ptr() will call Release()

@endcode

*/

class LFCEXT Variant
{
public:
	CTOR Variant() : m_pType(typeid(void))
	{
	}

	CTOR Variant(decltype(nullptr)) : m_pType(Types::get_nullType())
	{
	}

	CTOR Variant(Type* pType, VariantValue value) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u = value;
	}

#ifndef __LERSTAD__

	template <class T> 
	CTOR Variant(const T& value, typename std::enable_if<std::is_class<T>::value>::type* dummy = 0) : m_pType(typeid(T))
	{
		T* dst;
		if (sizeof(T) > sizeof(u))
		{
			u.ptr_val = (T*)new byte[sizeof(T)];
			dst = (T*)u.ptr_val;
		}
		else
		{
			dst = (T*)&u.ptr_val;
		}

#undef new
		::new (dst) T(value);
#define new _new
		/*
		// TODO

		Declarator* copy_ctor = m_pType->GetClass()->GetCopyConstructor();
		if (copy_ctor)
		{
			copy_ctor->void_invoke_method(dst, src);
		}
		else
		{
			memcpy(dst, src, sizeof(value));
		}
		*/
	}

	template <class T>
	CTOR Variant(T value, typename std::enable_if<std::is_enum<T>::value>::type* dummy = 0) : m_pType(typeid(T))
	{
		u.int32_val = value;
	}
#endif

	CTOR Variant(const Variant& other);

	CTOR Variant(Variant&& other)
	{
		m_pType = other.m_pType;
		u = other.u;

		// reset other
		other.m_pType = typeid(void);
	}

	template<class T> CTOR Variant(T* value)
	{
		/*
		if (value == nullptr)
		{
			m_pType = Types::get_nullType();
			kind = VARKIND_NULL;
		}
		else
		*/
		{
			u.ptr_val = value;

#ifndef __LERSTAD__
			if (std::is_base_of<Object, T>::value)
			{
				if (value)
				{
					// Set Type to most-derived class type
					m_pType = u.pObject->GetType()->get_pointerToThis();
				}
				else
				{
#ifndef __LERSTAD__
					m_pType = typeid(T*);
#endif
				}
			}
			else
			{
		//	if (Module::WithinManaged(pObject))
#ifndef __LERSTAD__
				m_pType = typeid(T*);
#endif
			}
#endif
		}
	}

	CTOR Variant(bool value) : m_pType(typeid(value))
	{
		ASSERT(m_pType);
		u.bool_val = value;
	}

	CTOR Variant(bool value, Type* pType) : m_pType(pType)
	{
		ASSERT(pType);
		u.bool_val = value;
	}

	CTOR Variant(char value) : m_pType(typeid(value))
	{
		ASSERT(m_pType);
		u.char_val = value;
	}

	CTOR Variant(signed char lValue)
	{
		u.int8_val = lValue;
		m_pType = typeid(lValue);
		ASSERT(m_pType);
	}

	CTOR Variant(unsigned char lValue)
	{
		u.int8_val = lValue;
		m_pType = typeid(lValue);
		ASSERT(m_pType);
	}

	CTOR Variant(short lValue)
	{
		u.int16_val = lValue;
		m_pType = typeid(lValue);
		ASSERT(m_pType);
	}

	CTOR Variant(unsigned short lValue)
	{
		u.int16_val = lValue;
		m_pType = typeid(lValue);
		ASSERT(m_pType);
	}

	CTOR Variant(unsigned int lValue)
	{
//		kind = VARKIND_UINT32;
		u.int32_val = lValue;
		m_pType = typeid(lValue);
		ASSERT(m_pType);
	}

	CTOR Variant(long long value)
	{
		u.longlong_val = value;
		m_pType = typeid(value);
		ASSERT(m_pType);
	}

	CTOR Variant(unsigned long long value)
	{
		u.ulonglong_val = value;
		m_pType = typeid(value);
		ASSERT(m_pType);
	}

	CTOR Variant(float fValue)
	{
		u.float_val = fValue;
		m_pType = typeid(fValue);
		ASSERT(m_pType);
	}

	CTOR Variant(double fValue)
	{
		u.double_val = fValue;
		m_pType = typeid(fValue);
		ASSERT(m_pType);
	}

	CTOR Variant(long double fValue)
	{
		u.longdouble_val = fValue;
		m_pType = typeid(fValue);
		ASSERT(m_pType);
	}

	CTOR Variant(signed char value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.schar_val = value;
	}

	CTOR Variant(unsigned char value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.uchar_val = value;
	}

	CTOR Variant(short value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.short_val = value;
	}

	CTOR Variant(unsigned short value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.ushort_val = value;
	}

	CTOR Variant(int value) : m_pType(typeid(int))
	{
		ASSERT(m_pType);
		u.int_val = value;
	}

	CTOR Variant(int value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.int_val = value;
	}

	CTOR Variant(unsigned int value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.uint_val = value;
	}

	CTOR Variant(long value)
	{
		m_pType = typeid(value);
		u.long_val = value;
	}

	CTOR Variant(long value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.long_val = value;
	}

	CTOR Variant(unsigned long value)
	{
		m_pType = typeid(value);
		u.ulong_val = value;
	}

	CTOR Variant(unsigned long value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.ulong_val = value;
	}

	CTOR Variant(long long value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.longlong_val = value;
	}

	CTOR Variant(unsigned long long value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.ulonglong_val = value;
	}

	CTOR Variant(float value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.float_val = value;
	}

	CTOR Variant(double value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.double_val = value;
	}

	CTOR Variant(long double value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.longdouble_val = value;
	}

#if _HAS_CHAR16_T_LANGUAGE_SUPPORT

	CTOR Variant(char16_t value) : m_pType(typeid(value))
	{
		ASSERT(m_pType);
		u.char16_t_val = value;
	}

	CTOR Variant(char16_t value, Type* pType) : m_pType(pType)
	{
		if (pType == nullptr) throw new ArgumentNullException();
		u.char16_t_val = value;
	}

#endif

	CTOR Variant(const void* src, Type* pType);
	CTOR Variant(bool, void* src, Type* pType);

	CTOR Variant(const String& str);
	CTOR Variant(String&& str);
	CTOR Variant(ComBSTR&& str);
	CTOR Variant(ComVariant&& v);
	CTOR Variant(StringIn str);
	CTOR Variant(const StringBuilderBase& str);
	CTOR Variant(const char* str, size_t len = ~0);
	CTOR Variant(const wchar_t* str, size_t len = ~0);

	CTOR Variant(const VARIANT& v);
	CTOR Variant(const PROPVARIANT& v);

	CTOR Variant(const Variant& other, Type* pType);

	template<class T> CTOR Variant(const array<T>& v)
	{
		m_pType = typeid(array<T>);

		m_array.m_pData = v.begin();
		m_array.m_nSize = v.size();
	}

#ifndef __LERSTAD__
	template<class T, size_t size> CTOR Variant(T (&arr)[size])
	{
		m_pType = typeid(array<T>);

		m_array.m_pData = arr;
		m_array.m_nSize = size;
	}
#endif

	void op_new(Type* pType);
	void op_delete();

// destructor
	~Variant();

///

	Type* GetType() const throw ()
	{
		return m_pType;
	}

	Type* GetPtrType() const throw ();
	ClassType* GetObjectType() const throw ();

	bool IsNull() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == Types::get_nullType();
	}

	bool IsUndefined() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(void);
	}

	bool IsBool() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(bool);
	}

	bool IsInt() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(int);
	}

	bool IsUInt() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(unsigned int);
	}

	bool IsInt64() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(long long);
	}

	bool IsUInt64() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(unsigned long long);
	}

	bool IsLongInteger() const throw ()
	{
		ASSERT(m_pType);
		Type* pType = m_pType->GetStripped();
		return pType == typeid(long long) || pType == typeid(unsigned long long);
	}

	bool IsFloat() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(float);
	}

	bool IsDouble() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(double);
	}

	bool IsNumberOrEnum() const throw ()
	{
		ASSERT(m_pType);
		return System::IsNumberOrEnum(m_pType->GetStripped()->get_Kind());
	}

	bool IsString() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetStripped() == typeid(String);
	}

	bool IsPointer() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->GetPointerTo() != nullptr;
	}

	bool IsFunction() const throw ()
	{
		ASSERT(m_pType);
		return m_pType->AsFunction() != nullptr;
	}

	bool IsObject() const throw ();

	bool IsPtrObject() const throw ()
	{
		ASSERT(m_pType);

		Type* pType = m_pType->GetPointerTo();
		if (pType && pType->AsClass()) return true;
		return false;
	}

	void* GetPtr() const;
	Object* GetObject() const;

#ifndef __LERSTAD__

	template<class T, class Enable=void> class convert
	{
	};

	template<class T> class convert<T, typename std::enable_if<std::is_class<T>::value && std::is_convertible<decltype(nullptr), T>::value>::type>
	{
	public:
		static T get(const Variant& v, bool* ok)
		{
			if (v.IsNull())
			{
				*ok = true;
				return T(nullptr);
			}
			else if (v.m_pType->AsClass())
			{
				VariantValue d;
				const void* src;
				void* dst;

				Type* dstType = typeid(T);

				if (sizeof(T) <= sizeof(VariantValue))
				{
					src = &v.u.ptr_val;
					dst = &d;
				}
				else
				{
					src = v.u.ptr_val;
					dst = new byte[sizeof(T)];
				}

				Declarator* copy_ctor = dstType->AsClass()->GetCopyConstructor(v.GetType());
				if (copy_ctor && copy_ctor->IsImplemented())
				{
					copy_ctor->void_invoke_method(dst, src);
				}
				else
				{
					memcpy(dst, src, sizeof(T));
				}

				*ok = true;
				return std::move(*(T*)dst);
			}

			*ok = false;
			raise(Exception("cannot convert"));
		}
	};

	template<class T> class convert<T, typename std::enable_if<std::is_class<T>::value && !std::is_convertible<decltype(nullptr), T>::value>::type>
	{
	public:
		static T get(const Variant& v, bool* ok)
		{
			if (v.IsNull())
			{
				*ok = false;
				raise(Exception("cannot convert from nullptr"));
			}
			else if (v.m_pType->AsClass())
			{
				VariantValue d;
				const void* src;
				void* dst;

				Type* dstType = typeid(T);

				if (sizeof(T) <= sizeof(VariantValue))
				{
					src = &v.u.ptr_val;
					dst = &d;
				}
				else
				{
					src = v.u.ptr_val;
					dst = new byte[sizeof(T)];
				}

				Declarator* copy_ctor = dstType->AsClass()->GetCopyConstructor(v.GetType());
				if (copy_ctor && copy_ctor->IsImplemented())
				{
					copy_ctor->void_invoke_method(dst, src);
				}
				else
				{
					memcpy(dst, src, sizeof(T));
				}

				*ok = true;
				return std::move(*(T*)dst);
			}
			*ok = false;
			raise(Exception("cannot convert"));
		}
	};

	template<class T> class convert<T, typename std::enable_if<std::is_enum<T>::value >::type>
	{
	public:
		static T get(const Variant& v, bool* ok)
		{
			*ok = true;
			if (v.m_pType->get_Kind() == type_enum)
			{
				switch (v.m_pType->GetBaseType()->get_Kind())
				{
					case type_bool: return (T)v.u.bool_val;

					case type_char: return (T)v.u.char_val;
					case type_wchar_t: return (T)v.u.wchar_t_val;
					case type_uchar16: return (T)v.u.char16_t_val;
					case type_uchar32: return (T)v.u.char32_t_val;

					case type_signed_char: return (T)v.u.schar_val;
					case type_unsigned_char: return (T)v.u.uchar_val;

					case type_short: return (T)v.u.short_val;
					case type_unsigned_short: return (T)v.u.ushort_val;

					case type_int: return (T)v.u.int_val;
					case type_unsigned_int: return (T)v.u.uint_val;

					case type_long: return (T)v.u.long_val;
					case type_unsigned_long: return (T)v.u.ulong_val;

					case type_long_long: return (T)v.u.longlong_val;
					case type_unsigned_long_long: return (T)v.u.ulonglong_val;

					default: ASSERT(0);
				}
			}
			*ok = false;
			raise(Exception("cannot convert"));
		}
	};

	template<class T> class convert<T*>
	{
	public:
		static T* get(const Variant& v, bool* ok)
		{
			*ok = false;

			if (v.m_pType == Types::get_nullType())
			{
				*ok = true;
				return nullptr;
			}
			else if (Type* p = v.m_pType->GetPointerTo())
			{
				ClassType* pClass = p->AsClass();
				if (pClass)
				{
					if (pClass->IsPolymorphic())
					{
						*ok = true;
						return dynamic_cast<T*>(v.u.pObject);
					}
					else
					{
						return nullptr;
					}
				}
				else
				{
					return nullptr;
				}
			}

			return nullptr;
		}
	};

	template<class T> operator T () const
	{
		bool ok;
		T value = convert<T>::get(*this, &ok);
		if (!ok)
		{
			raise(Exception("cannot convert " + this->ToString() + " to " + typeid(T)->ToString()));
		}
		return value;
	}

	template<class T> T try_cast (bool* ok) const
	{
		return convert<T>::get(*this, ok);
	}

#endif

	bool operator == (decltype(nullptr)) const;
	bool operator != (decltype(nullptr)) const
	{
		return !operator==(nullptr);
	}

	bool operator == (bool value) const;
	bool operator == (char value) const;
	bool operator == (wchar_t value) const;
	bool operator == (signed char value) const;
	bool operator == (unsigned char value) const;
	bool operator == (short value) const;
	bool operator == (unsigned short value) const;
	bool operator == (int value) const;
	bool operator == (unsigned int value) const;
	bool operator == (long value) const;
	bool operator == (unsigned long value) const;
	bool operator == (long long value) const;
	bool operator == (unsigned long long value) const;
	bool operator == (StringIn str) const;

	bool operator != (bool value) const
	{
		return !operator==(value);
	}

	bool operator != (signed char value) const
	{
		return !operator==(value);
	}

	bool operator != (unsigned char value) const
	{
		return !operator==(value);
	}

	bool operator != (short value) const
	{
		return !operator==(value);
	}

	bool operator != (unsigned short value) const
	{
		return !operator==(value);
	}

	bool operator != (int value) const
	{
		return !operator==(value);
	}

	bool operator != (unsigned int value) const
	{
		return !operator==(value);
	}

	bool operator != (long value) const
	{
		return !operator==(value);
	}

	bool operator != (unsigned long value) const
	{
		return !operator==(value);
	}

	bool operator != (long long value) const
	{
		return !operator==(value);
	}

	bool operator != (unsigned long long value) const
	{
		return !operator==(value);
	}

	bool operator < (bool value) const;
	bool operator < (char value) const;
	bool operator < (wchar_t value) const;
	bool operator < (signed char value) const;
	bool operator < (unsigned char value) const;
	bool operator < (short value) const;
	bool operator < (unsigned short value) const;
	bool operator < (int value) const;
	bool operator < (unsigned int value) const;
	bool operator < (long value) const;
	bool operator < (unsigned long value) const;
	bool operator < (long long value) const;
	bool operator < (unsigned long long value) const;
	bool operator < (StringIn str) const;

	bool operator <= (bool value) const;
	bool operator <= (char value) const;
	bool operator <= (wchar_t value) const;
	bool operator <= (signed char value) const;
	bool operator <= (unsigned char value) const;
	bool operator <= (short value) const;
	bool operator <= (unsigned short value) const;
	bool operator <= (int value) const;
	bool operator <= (unsigned int value) const;
	bool operator <= (long value) const;
	bool operator <= (unsigned long value) const;
	bool operator <= (long long value) const;
	bool operator <= (unsigned long long value) const;

	bool operator == (const Variant& other) const;
	bool operator != (const Variant& other) const
	{
		return !operator==(other);
	}

	bool operator > (const Variant& other) const;
	bool operator <= (const Variant& other) const;
	bool operator < (const Variant& other) const;
	bool operator >= (const Variant& other) const;

	bool operator ! ();
	bool operator ! () const;
	Variant operator ~ ();
	Variant operator ~ () const;
	Variant operator + (const Variant& other) const;
	Variant operator - (const Variant& other) const;
	Variant operator * (const Variant& other) const;
	Variant operator / (const Variant& other) const;
	Variant operator % (const Variant& other) const;
	Variant operator | (const Variant& other) const;
	Variant operator & (const Variant& other) const;
	Variant operator ^ (const Variant& other) const;
	Variant operator << (const Variant& other) const;
	Variant operator >> (const Variant& other) const;

	Variant& Variant::operator = (Variant&& other)
	{
		m_pType = other.m_pType;
		u = other.u;
		other.m_pType = typeid(void);	// reset other

		return *this;
	}

	Variant& operator = (const Variant& other);
	Variant& operator += (const Variant& other);
	Variant& operator -= (const Variant& other);
	Variant& operator *= (const Variant& other);
	Variant& operator /= (const Variant& other);
	Variant& operator %= (const Variant& other);
	Variant& operator |= (const Variant& other);
	Variant& operator &= (const Variant& other);
	Variant& operator ^= (const Variant& other);
	Variant& operator <<= (const Variant& other);
	Variant& operator >>= (const Variant& other);
	Variant& operator ++ ();
	Variant& operator -- ();
	Variant operator ++ (int);
	Variant operator -- (int);

	template<class arg_t>
	Variant& operator [] (arg_t arg)
	{
		Declarator* decl = m_pType->GetClass()->GetBracketOperator(typeid(arg));
		if (decl == nullptr) throw new Exception("operator [] not found");

	//	decl->invoke_functionA<(&arg, sizeof(arg));
		return nullptr;
	}

	template<class arg_t>
	const Variant& operator [] (arg_t arg) const
	{
		Declarator* decl = m_pType->GetClass()->GetBracketOperatorConst(typeid(arg));
		if (decl == nullptr) throw new Exception("operator [] not found");
		return nullptr;
	}

	Variant operator () () const;

	template<class arg0_type>
	Variant operator () (arg0_type arg0)
	{
		ASSERT(m_pType->get_Kind() == type_function);
		return Variant();
	}

	//Variant operator & () const;
	Variant operator * () const;

	Variant Deref() const;

	// conversion operators

	operator bool ();
	operator bool () const;
	operator char ();
	operator char () const;
	operator wchar_t ();
	operator wchar_t () const;
#if _HAS_CHAR16_T_LANGUAGE_SUPPORT
	operator char16_t ();
	operator char16_t () const;
	operator char32_t ();
	operator char32_t () const;
#endif
	operator signed char ();
	operator signed char () const;
	operator unsigned char ();
	operator unsigned char () const;
	operator int ();
	operator int () const;
	operator unsigned int ();
	operator unsigned int () const;
	operator long ();
	operator long () const;
	operator unsigned long ();
	operator unsigned long () const;
	operator long long ();
	operator long long () const;
	operator unsigned long long ();
	operator unsigned long long () const;
	operator float ();
	operator float () const;
	operator double ();
	operator double () const;
	operator long double ();
	operator long double () const;
	operator String ();
	operator String () const;
	operator VARIANT () const;

	bool CanConvertTo(Type* pType) const throw ();

	template<class T> bool CanConvertTo() const throw ();
#ifndef __LERSTAD__
	template<> bool CanConvertTo<int>() const throw ();
#endif

	bool ToBool() const;
	int ToInt() const;
	unsigned int ToUInt() const;
	long ToLong() const;
	unsigned long ToULong() const;
	int64 ToInt64() const;
	uint64 ToUInt64() const;
	float ToFloat() const;
	double ToDouble() const;

	bool ToBool(bool* ok) const;
	int ToInt(bool* ok) const;
	unsigned int ToUInt(bool* ok) const;
	long ToLong(bool* ok) const;
	unsigned long ToULong(bool* ok) const;
	int64 ToInt64(bool* ok) const;
	uint64 ToUInt64(bool* ok) const;
	float ToFloat(bool* ok) const;
	double ToDouble(bool* ok) const;

	String ToString() const;

	Object* box_cast() const;

protected:

	void* This() const
	{
		return m_pType->get_sizeof() <= sizeof(u)? (void*)&u.ptr_val: u.ptr_val;
	}

	void Init(const VARIANT& v);

public:
// data members

	Type* m_pType;
//	uint typeIndex : 31;
//	uint isnull : 1;

	union
	{
		struct
		{
			void* m_pData;
			size_t m_nSize;
		}
		m_array;

		VariantValue u;
	};
};

// 32 bit: sizeof=16
// 64 bit: sizeof=24

LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& writer, const Variant& v);

LFCEXT bool ToBool(const Variant&);
LFCEXT int ToInt(const Variant&);
LFCEXT unsigned int ToUInt(const Variant&);
LFCEXT float ToFloat(const Variant&);
LFCEXT double ToDouble(const Variant&);

inline Object* box_cast(const Variant& value)
{
	return value.box_cast();
}

}	// System

#endif // System_Variant_h
