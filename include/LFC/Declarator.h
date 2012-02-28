/**
@file Declaration for the Declarator class
@author Sigurd Lerstad
*/
namespace System
{

#ifdef _M_X64

extern "C"
{
	LFCEXT int64 int64_invoke_function_fastcall64(ULONG_PTR func_address, int64* args, size_t nargs);
	LFCEXT float float_invoke_function_fastcall64(ULONG_PTR func_address, int64* args, size_t nargs);
	LFCEXT double double_invoke_function_fastcall64(ULONG_PTR func_address, int64* args, size_t nargs);
}

#endif

/**
Helper class Args to call a function
*/
template<unsigned int n>
class HelperArgs
{
public:
	CTOR HelperArgs() : m_p(nullptr)
	{
		m_p = m_fixed;
	}

	/*
	void pushVariant(const Variant& v)
	{
	}
	*/

	template<class arg_t> void push(arg_t arg)
	{
#ifdef _M_IX86
		ASSERT(0);
		//size_t s = (sizeof(arg)+3) ~3; 

#elif _M_X64
		// all args 64 bit
		if (sizeof(arg) < 8)
		{
		}
		m_fixed[m_count] = 
		++m_count;
#else
#error "Unknown OS"
#endif
	}

#ifdef _M_IX86
	void push(bool arg)
	{
		*p++ = arg;
	}

	void push(char arg)
	{
		*p++ = arg;
	}

	void push(signed char arg)
	{
		*p++ = arg;
	}

	void push(unsigned char arg)
	{
		*p++ = arg;
	}

	void push(int arg)
	{
		*(int*)p = arg;
		p += sizeof(int);
	}

	void push(unsigned int arg)
	{
		*(unsigned int*)p = arg;
		p += sizeof(unsigned int);
	}

#endif

	void* begin()
	{
		return m_fixed;
	}

	const void* begin() const
	{
		return m_fixed;
	}

	void* end()
	{
		return m_p;
	}

	const void* end() const
	{
		return m_p;
	}

	void clear()
	{
		m_p = m_fixed;
	}

#ifdef _M_X64
	ubyte m_fixed[n*4];
	ubyte* m_p;
#else
	ULONG_PTR m_fixed[n];
	ULONG_PTR* m_p;
#endif
};

/**
	This loosely represents a Declarator in c++ . A member of a class, a member function of a class, a global variable.

	<h1>Obtaining a Declarator</h1>
	To find a declarator by name in a class, use ...
	To find a declarator at a specific offset in a class, use FindOffset()

	<h1>Using a class data member Declarator</h1>

	<h1>Using a function Declarator</h1>

	@code
	Declarator* f;

	bool result = f->invoke_function<bool>();

	// This works for any return value
	MyCustomClass r = f->invoke_function<MyCustomClass>(args...);
	@endcode

*/
class LFCEXT Declarator : public Object
{
public:
	CTOR Declarator();
	CTOR Declarator(Type* pType, StringIn name);

	/** @return Offset in bits of this member in the containing class, if this declarator is such a member */
	uint get_bitOffset() const throw()
	{
		return m_offset*8 + m_bitoffset;
	}

	/** @return Size in bits of this member in the containing class, if this declarator is such a member */
	uint get_bitSize() const throw();

#if 0
	union
	{
	//	CExpression* m_pInitializerExpr;
	//	_FunctionBody* m_pBody;
		T_Declarator* m_pBody;
		//CToken* m_stringtok;
		struct
		{
			char* data;
			int len;
		}
		m_string;
	};
#endif
//	std::vector<CTStatement*> m_statementList;
//	T_stmList_ *m_statementList;

	String get_QName() const;

	String get_Name() const throw()
	{
		return m_name;
	}

	Type* get_Type() const throw()
	{
		return m_pType;
	}

	AccessSpec get_Access() const throw()
	{
		return m_access;
	}

	/** For internal use */
	void set_Access(AccessSpec access)
	{
		ASSERT(access != AccessSpec_Unspecified);
		m_access = access;
	}

	bool get_IsTypedef() const throw()
	{
		return m_typedef;
	}

	bool get_IsStatic() const throw()
	{
		return m_static;
	}

	NamespaceType* GetNamespace() const throw()
	{
		return m_pOwnerScope->m_pNamespace;
	}

	NamespaceType* GetOwnerNamespace() const throw()
	{
		return m_pOwnerScope->m_pNamespace;
	}

	ClassType* GetClass() const throw()
	{
		return m_pOwnerScope->m_pNamespace->AsClass();
	}

	ClassType* GetOwnerClass() const throw()
	{
		return m_pOwnerScope->m_pNamespace->AsClass();
	}

// 
	String MangleName();
	bool Equals(const Declarator& other) const;
	String ToString() override;

	IO::TextWriter& Write(IO::TextWriter& stream) const;
	IO::TextWriter& WriteFunctionIdentity(IO::TextWriter& stream) const;

	void Load(bool bMember, TypeArchive& ar);
	void Store(bool bMember, TypeArchive& ar) const;

	void void_invoke_function(const void* args, size_t sz) const;
	void* pointer_invoke_function(const void* args, size_t sz) const;
	int32 int32_invoke_function(const void* args, size_t sz) const;
	int64 int64_invoke_function(const void* args, size_t sz) const;
	float float_invoke_function(const void* args, size_t sz) const;
	double double_invoke_function(const void* args, size_t sz) const;
	void struct_invoke_function(const void* args, size_t sz, void* retaddress) const;

	void void_invoke_function(const array<Variant>& args) const;
	void void_invoke_method(void* thisptr, const array<Variant>& args) const;

	/** Invoke a method with no arguments
	@param thisptr pointer to 'this'
	*/
	void void_invoke_method(void* thisptr) const;
	void void_invoke_method(void* thisptr, const void* args, size_t sz) const;
	void struct_invoke_method(void* thisptr, const void* args, size_t sz, void* retaddress) const;
	int int32_invoke_method(void* thisptr, const void* args = nullptr, size_t sz = 0) const;

	/** Verifies that this is a function declarator and that the function is implemented and
	has a known address so that it can be called. If this function is only declared in a header file,
	but not implemented, causing a link error if one tries to call it from c++. There may be
	other reasons why, this may happen if the c++ compiler has chosen to inline a function or discarded
	it altogether since it's never been called in the c++ program.
	*/
	void VerifyImplemented() const throw (SystemException*);

	/** @return The Type of the return value if this is a function declarator, throws an exception
	if this is not a function
	*/
	Type* get_ReturnType() const throw (SystemException*)
	{
		FunctionType* pFunType = m_pType->AsFunction();
		if (pFunType == nullptr)
		{
			raise(SystemException("not a function"));
		}

		return pFunType->get_ReturnType();
	}

#ifndef __LERSTAD__

	template<class arg0_t>
	void void_invoke_method(void* thisptr, arg0_t arg0) const throw (SystemException*)
	{
		FunctionType* pFunType = m_pType->AsFunction();

		if (pFunType)
		{
			VerifyImplemented();

	#ifdef _M_IX86

			ULONG_PTR address = GetAddress();
			void_invoke_method32(address, thisptr, &arg0, sizeof(arg0));

	#elif _M_X64

			int64 args_stack[4];
			int64* p = args_stack;
			*p++ = (ULONG_PTR)thisptr;
			*p++ = (ULONG_PTR)arg0;
			size_t nargs = 4;	// always at least 4

			(void)int64_invoke_function_fastcall64(GetAddress(), args_stack, nargs);
	#else
		#error "Unknown OS"
	#endif
		}
		else
		{
			raise(SystemException("declarator not a function"));
		}
	}

	template<class arg0_t, class arg1_t>
	void void_invoke_method(void* thisptr, arg0_t arg0, arg1_t arg1) const throw (SystemException*)
	{
		FunctionType* pFunType = m_pType->GetFunction();

		if (pFunType)
		{
			VerifyImplemented();

	#ifdef _M_IX86

			// TODO
			ASSERT(0);

			void_invoke_method32(GetAddress(), thisptr, &arg0, sizeof(arg0));

	#elif _M_X64

			int64 args_stack[4];
			int64* p = args_stack;
			*p++ = (ULONG_PTR)thisptr;
			*p++ = (ULONG_PTR)arg0;
			*p++ = (ULONG_PTR)arg1;
			size_t nargs = 4;	// always at least 4

			(void)int64_invoke_function_fastcall64(GetAddress(), args_stack, nargs);
	#else
		#error "Unknown OS"
	#endif
		}
		else
		{
			raise(SystemException("declarator not a function"));
		}
	}

private:
	// helper class
	template<class T> class getter
	{
	public:
		static T get(const Declarator* decl, const void* args, size_t sz)
		{
			T value;
			decl->struct_invoke_function(args, sz, &value);
			return value;
		}
	};

	template<class T> class getter<T*>
	{
	public:
		static T* get(const Declarator* decl, const void* args, size_t sz)
		{
			return (T*)decl->pointer_invoke_function(args, sz);
		}
	};

	template<class T> class getter<T&>
	{
	public:
		static T& get(const Declarator* decl, const void* args, size_t sz)
		{
			return *(T*)decl->pointer_invoke_function(this, args, sz);
		}
	};

public:

	template<class T> T invoke_functionA(const void* args, size_t sz) const
	{
		return getter<T>::get(this, args, sz);
	}

	template<> inline void invoke_functionA<void>(const void* args, size_t sz) const
	{
		void_invoke_function(args, sz);
	}

	template<> inline bool invoke_functionA<bool>(const void* args, size_t sz) const
	{
		ubyte val = (ubyte)int32_invoke_function(args, sz);
		ASSERT((val & ~1) == 0);
		return val & 1;
	}

	template<> inline char invoke_functionA<char>(const void* args, size_t sz) const
	{
		return (char)int32_invoke_function(args, sz);
	}

	template<> inline wchar_t invoke_functionA<wchar_t>(const void* args, size_t sz) const
	{
		return (wchar_t)int32_invoke_function(args, sz);
	}

	template<> inline signed char invoke_functionA<signed char>(const void* args, size_t sz) const
	{
		return (signed char)int32_invoke_function(args, sz);
	}

	template<> inline unsigned char invoke_functionA<unsigned char>(const void* args, size_t sz) const
	{
		return (unsigned char)int32_invoke_function(args, sz);
	}

	template<> inline short invoke_functionA<short>(const void* args, size_t sz) const
	{
		return (short)int32_invoke_function(args, sz);
	}

	template<> inline unsigned short invoke_functionA<unsigned short>(const void* args, size_t sz) const
	{
		return (unsigned short)int32_invoke_function(args, sz);
	}

	template<> inline int invoke_functionA<int>(const void* args, size_t sz) const
	{
		return int32_invoke_function(args, sz);
	}

	template<> inline unsigned int invoke_functionA<unsigned int>(const void* args, size_t sz) const
	{
		return (unsigned int)int32_invoke_function(args, sz);
	}

#if ULONG_MAX == 0xffffffffUL

	template<> inline long invoke_functionA<long>(const void* args, size_t sz) const
	{
		return int32_invoke_function(args, sz);
	}

	template<> inline unsigned long invoke_functionA<unsigned long>(const void* args, size_t sz) const
	{
		return (unsigned long)int32_invoke_function(args, sz);
	}

#else

	template<> inline long invoke_functionA<long>(const void* args, size_t sz) const
	{
		return int64_invoke_function(args, sz);
	}

	template<> inline unsigned long invoke_functionA<unsigned long>(const void* args, size_t sz) const
	{
		return (unsigned long)int64_invoke_function(args, sz);
	}

#endif

	template<> inline long long invoke_functionA<long long>(const void* args, size_t sz) const
	{
		return int64_invoke_function(args, sz);
	}

	template<> inline unsigned long long invoke_functionA<unsigned long long>(const void* args, size_t sz) const
	{
		return (uint64)int64_invoke_function(args, sz);
	}

	template<> inline float invoke_functionA<float>(const void* args, size_t sz) const
	{
		return float_invoke_function(args, sz);
	}

	template<> inline double invoke_functionA<double>(const void* args, size_t sz) const
	{
		return double_invoke_function(args, sz);
	}

	template<> inline long double invoke_functionA<long double>(const void* args, size_t sz) const
	{
		return double_invoke_function(args, sz);
	}

	// method call

	// helper class
	template<class T> class gettermethod
	{
	public:
		static T get(const Declarator* decl, void* thisptr, const void* args, size_t sz)
		{
			T value;
			decl->struct_invoke_method(thisptr, args, sz, &value);
			return value;
		}
	};

	template<class T> class gettermethod<T*>
	{
	public:
		static T* get(const Declarator* decl, void* thisptr, const void* args, size_t sz)
		{
			return (T*)decl->pointer_invoke_method(thisptr, args, sz);
		}
	};

	template<class T> class gettermethod<T&>
	{
	public:
		static T& get(const Declarator* decl, void* thisptr, const void* args, size_t sz)
		{
			return *(T*)decl->pointer_invoke_method(thisptr, args, sz);
		}
	};

	/*
	template<> inline void invoke_method<void>(const void* args, uint32 sz)
	{
		void_invoke_function(args, sz);
	}

	template<> inline void* invoke_method<void*>(const void* args, uint32 sz)
	{
		return pointer_invoke_function(args, sz);
	}

	template<> inline bool invoke_method<bool>(const void* args, uint32 sz)
	{
		ubyte val = (ubyte)int32_invoke_function(args, sz);
		ASSERT((val & ~1) == 0);
		return val & 1;
	}
	*/

	template<class T> T invoke_method(void* thisptr, const void* args = nullptr, size_t sz = 0) const
	{
		return gettermethod<T>::get(this, thisptr, args, sz);
	}

	template<> inline void invoke_method<void>(void* thisptr, const void* args, size_t sz) const
	{
		void_invoke_method(thisptr, args, sz);
	}

	template<> inline bool invoke_method<bool>(void* thisptr, const void* args, size_t sz) const
	{
		ubyte val = (ubyte)int32_invoke_method(thisptr, args, sz);
		ASSERT((val & ~1) == 0);
		return val & 1;
	}

	template<> inline int invoke_method<int>(void* thisptr, const void* args, size_t sz) const
	{
		return int32_invoke_method(thisptr, args, sz);
	}

	template<> inline unsigned int invoke_method<unsigned int>(void* thisptr, const void* args, size_t sz) const
	{
		return (unsigned int)int32_invoke_method(thisptr, args, sz);
	}


///////////////

	/*
	template<class T, class arg0_t> T invoke_function(arg0_t arg0) const
	{
		//return getter<T>::get(this, args, sz);
	}

	template<class arg0_t> inline void invoke_function<void>(arg0_t arg0) const
	{
		convert(	AsFunction()->m_parameters[0].m_pType, arg0);

		HelperArgs args;
		args.push(arg0);

		void_invoke_function(args.begin(), args.size());
	}

	template<class arg0_t> inline int invoke_function<void>(arg0_t arg0) const
	{
		HelperArgs args;
		args.push(arg0);
		return int32_invoke_function(args.begin(), args.size());
	}

	template<class arg0_t> inline int invoke_function<void>(arg0_t arg0, arg1_t arg1) const
	{
		HelperArgs args;
		args.push(arg0);
		args.push(arg1);

		return int32_invoke_function(args.begin(), args.size());
	}
	*/

#endif

	/** @return The memory address of this declarator, if applicable (function, static class variable, global variable)
	*/
	ULONG_PTR GetAddress() const throw()
	{
		if (m_address == ~0) return ~0;
		ASSERT(m_pModule);
		return (ULONG_PTR)m_pModule->GetModuleInstance() + m_address;
	}

	void SetAddress(ULONG_PTR address) throw()
	{
		ASSERT(m_pModule);
		m_address = (uint32)(address - (ULONG_PTR)m_pModule->GetModuleInstance());
	}

	void SetAddress(const void* address) throw()
	{
		SetAddress((ULONG_PTR)address);
	}

	/** @return <code>true</code> if implemented
	*/
	bool IsImplemented() const throw()
	{
		if (m_address == ~0) return false;
		ASSERT(m_pModule);
		return true;
	}

public:

	CppSourceFile* m_sourcefile;
	list<Declarator*>::iterator m_sourcefile_it;
	int m_sourceline;
	int m_sourcecolumn;
	int m_charoffset_start;	// TODO ??
	int m_charoffset_end;	// TODO ??

	String m_name;
	Scope* m_pOwnerScope;	// pointer back to scope that owns this declaration
	Type* m_pType;
	Module* m_pModule;
	SExp* m_initVal;	// static const member
	ClassType* m_pOverrideClass;

	int m_alignment;	// member variable
	uint8 m_bitoffset;	// member variable
	uint8 m_bitlength;	// member variable

	uint32 m_offset;	// offset if this is a member of a struct/class
	uint32 m_address;	// relative to m_pModule

	AccessSpec m_access : 2;	// 0=private, 1=protected, 2=public
	uint8 m_localVar : 2;	// 0=false, 1=true, 2=enum
	uint8 m_kind : 2;	// 0=method,1=propertyget,2=propertyset // function
	uint8 m_pad : 2;

	bool m_referenced : 1;
	bool m_defined : 1;
	bool m_typedef : 1;
	bool m_static : 1;
	bool m_fwd : 1;
	bool m_virtual : 1;	// only-function
	bool m_cpp_linkage : 1;	// only-function
	bool m_abstract : 1;	// only-function

	//non-virtual=0
	//virtual-introduce=1
	//virtual-introduce-abstract=2
	//virtual-override=3

//	int m_reg;

#if 0
// libcall
	class libcall
	{
	public:
		inline libcall()
		{
			m_reg = -1;
		}
		int m_reg;
	}
	m_libcall;
#endif
};

inline bool decl_offset_less_than(Declarator* x, Declarator* y)
{
	return x->m_offset < y->m_offset;
}

}	// System
