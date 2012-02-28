namespace System
{

//class Method;
class Property;
class Dispatch;

class Conv
{
public:
	CTOR Conv();

	Conv* pConv;
	Type* ArgType;
	Declarator* pMethod;
};

class LFCEXT Property : public Object
{
public:
	CTOR Property();

	String get_PropertyName() const
	{
		return m_name;
	}

	Declarator* get_GetMethod() const
	{
		return get_method;
	}

	Declarator* get_SetMethod() const
	{
		return set_method;
	}

	Type* get_GetType() const
	{
		return get_method->get_ReturnType();
	}

	Type* get_SetType() const
	{
		return set_method->m_pType->AsFunction()->m_parameters[0].m_pType;
	}

	Declarator* get_method;
	Declarator* set_method;

protected:

	friend class Dispatch;

	String m_name;
};

class LFCEXT DispMember
{
public:
	CTOR DispMember(Declarator* method, UINT dispID)
	{
		m_method = method;
		m_property = NULL;
		m_dispID = dispID;
	}

	CTOR DispMember(Property* prop, UINT dispID)
	{
		m_property = prop;
		m_method = NULL;
		m_dispID = dispID;
	}

	Declarator* m_method;
	Property* m_property;
	UINT m_dispID;
};

class LFCEXT Dispatch : public Object
{
public:

	CTOR Dispatch(NamespaceType* pClass);
	~Dispatch();
	//Dispatch(void* object, StringA methodName); // TODO

	typedef map<String, Property*> propertymap_t;

	void void_Invoke(void* object, Declarator* method, const void* args, size_t sz) throw(SystemException*);
	void* pointer_Invoke(void* object, Declarator* method, const void* args, size_t sz) throw(SystemException*);
	Object* Object_Invoke(void* object, Declarator* method, const void* args, size_t sz) throw(SystemException*);
	bool bool_Invoke(void* m_this, Declarator* method, const void* args, size_t sz) throw(SystemException*);
	int32 int32_Invoke(void* object, Declarator* method, const void* args, size_t sz) throw(SystemException*);
	int64 int64_Invoke(void* object, Declarator* method, const void* args, size_t sz) throw(SystemException*);
	float float_Invoke(void* object, Declarator* method, const void* args, size_t sz) throw(SystemException*);
	double double_Invoke(void* object, Declarator* method, const void* args, size_t sz) throw(SystemException*);
	void struct_Invoke(void* m_this, Declarator* method, const void* args, size_t sz, void* retval_address) throw(SystemException*);

	template<class T> T Invoke(void* m_this, Declarator* method, const void* args, size_t sz)
	{
#ifndef __LERSTAD__
		T retval;
		struct_Invoke(m_this, method, args, sz, &retval);
		return retval;
#endif
	}

#ifndef __LERSTAD__

	template<> void Invoke<void>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		void_Invoke(m_this, method, args, sz);
	}

	template<> bool Invoke<bool>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return bool_Invoke(m_this, method, args, sz);
	}

	template<> signed char Invoke<signed char>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return (signed char)int32_Invoke(m_this, method, args, sz);
	}

	template<> unsigned char Invoke<unsigned char>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return (unsigned char)int32_Invoke(m_this, method, args, sz);
	}

	template<> short Invoke<short>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return (short)int32_Invoke(m_this, method, args, sz);
	}

	template<> unsigned short Invoke<unsigned short>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return (unsigned short)int32_Invoke(m_this, method, args, sz);
	}

	template<> int Invoke<int>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return int32_Invoke(m_this, method, args, sz);
	}

	template<> unsigned int Invoke<unsigned int>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return (unsigned int)int32_Invoke(m_this, method, args, sz);
	}

	template<> long Invoke<long>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
#if ULONG_MAX == 0xffffffffUL
		return int32_Invoke(m_this, method, args, sz);
#else
		return int64_Invoke(m_this, method, args, sz);
#endif
	}

	template<> unsigned long Invoke<unsigned long>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
#if ULONG_MAX == 0xffffffffUL
		return (unsigned long)int32_Invoke(m_this, method, args, sz);
#else
		return (unsigned long)int64_Invoke(m_this, method, args, sz);
#endif
	}

	template<> long long Invoke<long long>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return int64_Invoke(m_this, method, args, sz);
	}

	template<> unsigned long long Invoke<unsigned long long>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return (unsigned long long)int64_Invoke(m_this, method, args, sz);
	}

	template<> float Invoke<float>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return float_Invoke(m_this, method, args, sz);
	}

	template<> double Invoke<double>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return double_Invoke(m_this, method, args, sz);
	}

	template<> long double Invoke<long double>(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		return double_Invoke(m_this, method, args, sz);
	}
#endif

	String String_Invoke(void* m_this, Declarator* method, const void* args, size_t sz)
	{
		String str;
		struct_Invoke(m_this, method, args, sz, &str);
		return str;
	}

	int SetValue(void* _this, Declarator* method, Object* pObject, Type* pSourceType);

	//Variant Invoke2(const Method& method, Variant param0, Variant param1);

//	Method* GetMethod(Declarator* decl);
	Declarator* GetMethod(StringIn methodName);
	Property* GetProperty(StringIn name);
	propertymap_t& GetProperties();

	inline NamespaceType* GetClass() const
	{
		return m_pClass;
	}

	friend LFCEXT Conv* Convert(Type* pType, Type* ArgType, int level);

	friend LFCEXT Object* newobj(ClassType* pClass) throw(SystemException*);
	friend LFCEXT void* newvoidobj(ClassType* pClass) throw(SystemException*);

	multimap<String, Declarator*> m_methodnames;

	typedef map<String, DispMember> dispmembermap;

#ifdef __LERSTAD__
	vector<Object*> m_dispmembers;
#else
	vector<dispmembermap::iterator> m_dispmembers;
#endif
	dispmembermap m_dispmembersByName;

protected:

	void Build(NamespaceType* pClass);
	void BuildProperties();

	NamespaceType* m_pClass;

	map<String, Declarator*> m_methods;
	propertymap_t m_properties;
};

extern "C"
{
LFCEXT void struct_invoke_method32(ULONG_PTR func, void* _this, const void* args, size_t sz, void* retaddress);
LFCEXT void void_invoke_method32(ULONG_PTR func, void* _this, const void* args, size_t sz);
LFCEXT int32 int32_invoke_method32(ULONG_PTR func, void* _this, const void* args, size_t sz);
LFCEXT int64 int64_invoke_method32(ULONG_PTR func, void* _this, const void* args, size_t sz);
LFCEXT float float_invoke_method32(ULONG_PTR func, void* _this, const void* args, size_t sz);
LFCEXT double double_invoke_method32(ULONG_PTR func, void* _this, const void* args, size_t sz);

LFCEXT void void_invoke_method_stdcall(ULONG_PTR func, void* _this, const void* args, size_t sz);
LFCEXT int32 int32_invoke_method_stdcall(ULONG_PTR func, void* _this, const void* args, size_t sz);
LFCEXT int64 int64_invoke_method_stdcall(ULONG_PTR func, void* _this, const void* args, size_t sz);
LFCEXT float float_invoke_method_stdcall(ULONG_PTR func, void* _this, const void* args, size_t sz);
LFCEXT double double_invoke_method_stdcall(ULONG_PTR func, void* _this, const void* args, size_t sz);

LFCEXT void void_invoke_function_stdcall(ULONG_PTR func, const void* args, size_t sz);
LFCEXT void* pointer_invoke_function_stdcall(ULONG_PTR func, const void* args, size_t sz);
LFCEXT int32 int32_invoke_function_stdcall(ULONG_PTR func, const void* args, size_t sz);
LFCEXT int64 int64_invoke_function_stdcall(ULONG_PTR func, const void* args, size_t sz);
LFCEXT float float_invoke_function_stdcall(ULONG_PTR func, const void* args, size_t sz);
LFCEXT double double_invoke_function_stdcall(ULONG_PTR func, const void* args, size_t sz);
LFCEXT void struct_invoke_function_stdcall(ULONG_PTR func, const void* args, size_t sz, void* retaddress);

LFCEXT void void_invoke_function_cdecl(ULONG_PTR func, const void* args, size_t sz);
LFCEXT void* pointer_invoke_function_cdecl(ULONG_PTR func, const void* args, size_t sz);
LFCEXT int32 int32_invoke_function_cdecl(ULONG_PTR func, const void* args, size_t sz);
LFCEXT int64 int64_invoke_function_cdecl(ULONG_PTR func, const void* args, size_t sz);
LFCEXT float float_invoke_function_cdecl(ULONG_PTR func, const void* args, size_t sz);
LFCEXT double double_invoke_function_cdecl(ULONG_PTR func, const void* args, size_t sz);
LFCEXT void struct_invoke_function_cdecl(ULONG_PTR func, const void* args, size_t sz, void* retaddress);

}	// extern "C"

template<class T> T invoke_function_cdecl(ULONG_PTR func, const void* args, size_t sz)
{
	T value;
	struct_invoke_function_cdecl(func, args, sz, &value);
	return value;
}

template<class T> T invoke_function_stdcall(ULONG_PTR func, const void* args, size_t sz)
{
	T value;
	struct_invoke_function_stdcall(func, args, sz, &value);
	return value;
}

#ifndef __LERSTAD__

template<> inline bool invoke_function_stdcall<bool>(ULONG_PTR func, const void* args, size_t sz)
{
	return int32_invoke_function_stdcall(func, args, sz) & 1;
}

template<> inline bool invoke_function_cdecl<bool>(ULONG_PTR func, const void* args, size_t sz)
{
	return int32_invoke_function_cdecl(func, args, sz) & 1;
}

template<> inline char invoke_function_cdecl<char>(ULONG_PTR func, const void* args, size_t sz)
{
	return (char)int32_invoke_function_cdecl(func, args, sz);
}

template<> inline signed char invoke_function_cdecl<signed char>(ULONG_PTR func, const void* args, size_t sz)
{
	return (signed char)int32_invoke_function_cdecl(func, args, sz);
}

template<> inline unsigned char invoke_function_cdecl<unsigned char>(ULONG_PTR func, const void* args, size_t sz)
{
	return (unsigned char)int32_invoke_function_cdecl(func, args, sz);
}

template<> inline short invoke_function_cdecl<short>(ULONG_PTR func, const void* args, size_t sz)
{
	return (short)int32_invoke_function_cdecl(func, args, sz);
}

template<> inline unsigned short invoke_function_cdecl<unsigned short>(ULONG_PTR func, const void* args, size_t sz)
{
	return (unsigned short)int32_invoke_function_cdecl(func, args, sz);
}

template<> inline wchar_t invoke_function_cdecl<wchar_t>(ULONG_PTR func, const void* args, size_t sz)
{
	return (wchar_t)int32_invoke_function_cdecl(func, args, sz);
}

template<> inline int invoke_function_cdecl<int>(ULONG_PTR func, const void* args, size_t sz)
{
	return int32_invoke_function_cdecl(func, args, sz);
}

template<> inline unsigned int invoke_function_cdecl<unsigned int>(ULONG_PTR func, const void* args, size_t sz)
{
	return (unsigned int)int32_invoke_function_cdecl(func, args, sz);
}

template<> inline int64 invoke_function_cdecl<int64>(ULONG_PTR func, const void* args, size_t sz)
{
	return int64_invoke_function_cdecl(func, args, sz);
}

template<> inline uint64 invoke_function_cdecl<uint64>(ULONG_PTR func, const void* args, size_t sz)
{
	return (uint64)int64_invoke_function_cdecl(func, args, sz);
}

template<> inline float invoke_function_cdecl<float>(ULONG_PTR func, const void* args, size_t sz)
{
	return float_invoke_function_cdecl(func, args, sz);
}

template<> inline double invoke_function_cdecl<double>(ULONG_PTR func, const void* args, size_t sz)
{
	return double_invoke_function_cdecl(func, args, sz);
}

template<> inline Object* invoke_function_cdecl<Object*>(ULONG_PTR func, const void* args, size_t sz)
{
	// TODO: 64
	return (Object*)int32_invoke_function_cdecl(func, args, sz);
}

template<> inline Object* invoke_function_stdcall<Object*>(ULONG_PTR func, const void* args, size_t sz)
{
	// TODO: 64
	return (Object*)int32_invoke_function_stdcall(func, args, sz);
}

#endif

}	// System
