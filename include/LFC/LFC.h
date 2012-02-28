/**
@file LFC include
@defgroup LFC
*/

#ifndef __LERSTAD__
#define RPC_USE_NATIVE_WCHAR
#define NOMINMAX
#include <windows.h>
#endif

//#include <atlbase.h>
//ATL::CComPtrBase<IUnknown>
//ATL::CComBSTR::ArrayToBSTR
//ATL::CComVariant h;

#ifndef LFC_h
#define LFC_h

#define EXTERN_C extern "C"
#define IN
#define OUT

#if defined(_MSC_VER) || defined(__LERSTAD__)
#define DECLSPEC_IMPORT	__declspec(dllimport)
#elif __GNUC__
#define DECLSPEC_IMPORT
#endif

#define RPC_USE_NATIVE_WCHAR

#ifdef _WIN32

#ifdef __LERSTAD__

#define WINVER			0x0600
#define _WIN32_WINNT		0x0601

#include "windows_header.h"

#define _I8_MIN     (-128)    /* minimum signed 8 bit value */
#define _I8_MAX       127         /* maximum signed 8 bit value */
#define _UI8_MAX      0xff       /* maximum unsigned 8 bit value */

#define _I16_MIN    (-32767 - 1) /* minimum signed 16 bit value */
#define _I16_MAX      32767      /* maximum signed 16 bit value */
#define _UI16_MAX     0xffff    /* maximum unsigned 16 bit value */

#define _I32_MIN    (-2147483647 - 1) /* minimum signed 32 bit value */
#define _I32_MAX      2147483647 /* maximum signed 32 bit value */
#define _UI32_MAX     0xffffffff /* maximum unsigned 32 bit value */

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647    /* maximum (signed) int value */
#define UINT_MAX      0xffffffff    /* maximum unsigned int value */
#define LONG_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#define LONG_MAX      2147483647L   /* maximum (signed) long value */
#define ULONG_MAX     0xffffffffUL  /* maximum unsigned long value */

#if 0
#define _I8_MIN     (-127i8 - 1)    /* minimum signed 8 bit value */
#define _I8_MAX       127i8         /* maximum signed 8 bit value */
#define _UI8_MAX      0xffui8       /* maximum unsigned 8 bit value */

#define _I16_MIN    (-32767i16 - 1) /* minimum signed 16 bit value */
#define _I16_MAX      32767i16      /* maximum signed 16 bit value */
#define _UI16_MAX     0xffffui16    /* maximum unsigned 16 bit value */

#define _I32_MIN    (-2147483647i32 - 1) /* minimum signed 32 bit value */
#define _I32_MAX      2147483647i32 /* maximum signed 32 bit value */
#define _UI32_MAX     0xffffffffui32 /* maximum unsigned 32 bit value */

#endif

#define DBL_DIG         15                      /* # of decimal digits of precision */
#define DBL_EPSILON     2.2204460492503131e-016 /* smallest such that 1.0+DBL_EPSILON != 1.0 */
#define DBL_MANT_DIG    53                      /* # of bits in mantissa */
#define DBL_MAX         1.7976931348623158e+308 /* max value */
#define DBL_MAX_10_EXP  308                     /* max decimal exponent */
#define DBL_MAX_EXP     1024                    /* max binary exponent */
#define DBL_MIN         2.2250738585072014e-308 /* min positive value */
#define DBL_MIN_10_EXP  (-307)                  /* min decimal exponent */
#define DBL_MIN_EXP     (-1021)                 /* min binary exponent */
#define _DBL_RADIX      2                       /* exponent radix */
#define _DBL_ROUNDS     1                       /* addition rounding: near */

#define FLT_DIG         6                       /* # of decimal digits of precision */
#define FLT_EPSILON     1.192092896e-07F        /* smallest such that 1.0+FLT_EPSILON != 1.0 */
#define FLT_GUARD       0
#define FLT_MANT_DIG    24                      /* # of bits in mantissa */
#define FLT_MAX         3.402823466e+38F        /* max value */
#define FLT_MAX_10_EXP  38                      /* max decimal exponent */
#define FLT_MAX_EXP     128                     /* max binary exponent */
#define FLT_MIN         1.175494351e-38F        /* min positive value */
#define FLT_MIN_10_EXP  (-37)                   /* min decimal exponent */
#define FLT_MIN_EXP     (-125)                  /* min binary exponent */
#define FLT_NORMALIZE   0
#define FLT_RADIX       2                       /* exponent radix */
#define FLT_ROUNDS      1                       /* addition rounding: near */

#ifndef _HAS_CHAR16_T_LANGUAGE_SUPPORT
 #define _HAS_CHAR16_T_LANGUAGE_SUPPORT 0
#endif /* _HAS_CHAR16_T_LANGUAGE_SUPPORT */

/* uchar PROPERTIES */ 
#if _HAS_CHAR16_T_LANGUAGE_SUPPORT 
#else /* _HAS_CHAR16_T_LANGUAGE_SUPPORT */ 
#if !defined(_CHAR16T) 
   #define _CHAR16T 
typedef unsigned short char16_t; 
typedef unsigned int char32_t; 
#endif /* !defined(_CHAR16T) */ 

#endif /* _HAS_CHAR16_T_LANGUAGE_SUPPORT */ 

#else

#define NOMINMAX
#include <windows.h>

#undef GetObject
#undef GetWindowLong
#undef SetWindowLong
#undef DefWindowProc
#undef LoadCursor
#undef SendMessage
#undef PostMessage
#undef DrawText
#undef GetGlyphIndices
#undef RegisterClass
#undef UnregisterClass

#endif
#elif __GNUC__

#include <stdlib.h>
#include <string.h>

typedef wchar_t WCHAR;

typedef short SHORT;
typedef unsigned int UINT;

typedef unsigned int DWORD;
typedef unsigned long ULONG;
typedef int HANDLE;

typedef unsigned int UINT_PTR;	// TODO
typedef unsigned long ULONG_PTR;	// TODO

#define INVALID_HANDLE_VALUE	-1

#define __cdecl __attribute__((cdecl))
#define __stdcall __attribute__((stdcall))
#define __fastcall __attribute__((fastcall))

char* strncpy_s(char* dst, const char* src, int len);

#endif

/*
#ifdef __GNUC__
typedef long nullvalue_t;
#else
typedef int nullvalue_t;
#endif
*/

#ifdef __LERSTAD__

#define __attrib__(x) [ x ]

#endif

#ifdef __LERSTAD__
// TODO, support this in __LERSTAD__
#define override
#define abstract =0
#endif

#ifdef __GNUC__
#define override
#define abstract =0
#endif

#ifdef __GNUC__

	#define DECLSPEC_RESTRICT //restrict

#elif __LERSTAD__

	#define DECLSPEC_RESTRICT

#else

	#define DECLSPEC_RESTRICT __declspec(restrict)

#endif

#ifndef __LERSTAD__

#define __STRUCT__ struct
#define interface __STRUCT__

#define __attrib__(x)

#endif

#ifndef __LERSTAD__
#define CTOR
#else
#define CTOR <
#endif

#ifdef __LERSTAD__

#define _inline inline
#define __inline inline

#endif

#ifndef LFCEXT
#define LFCEXT DECLSPEC_DLLIMPORT
#endif

#pragma warning(disable : 4200) // zero-sized array in struct/union

//disable warnings on extern before template instantiation
#pragma warning(disable : 4231)

// to have dll-interface
#pragma warning(disable : 4251)

// base class to have dll-interface
#pragma warning(disable : 4275)

#if _MSC_VER //&& !__LERSTAD__
#pragma warning(disable: 4201) // nameless unions are part of C++

#pragma warning(disable: 4127) // constant expression

#pragma warning(disable: 4505) // unreferenced local function has been removed

#pragma warning(disable: 4512) // can't generate assignment operator (so what?)

#pragma warning(disable: 4514) // unreferenced inlines are common

#pragma warning(disable: 4103) // pragma pack

#pragma warning(disable: 4702) // unreachable code

#pragma warning(disable: 4237) // bool

#pragma warning(disable: 4710) // function couldn't be inlined

#pragma warning(disable: 4355) // 'this' : used in base member initializer list

#pragma warning(disable: 4097) // typedef name used as synonym for class-name

#pragma warning(disable: 4786) // identifier was truncated in the debug information

#pragma warning(disable: 4268) // const static/global data initialized to zeros

#pragma warning(disable: 4291) // allow placement new

#pragma warning(disable : 4290 )	// C++ exception specification ignored except to indicate a function is not __declspec(nothrow)

// warning C4700: uninitialized local variable used
#pragma warning(error : 4700)

#endif

#define INT_MAX 2147483647

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

#ifdef _M_X64
typedef unsigned __int64 size_t;
typedef __int64 ptrdiff_t;
#elif defined(_WIN32)
typedef unsigned int size_t;
typedef int ptrdiff_t;
#else
typedef unsigned long size_t;
typedef long ptrdiff_t;
#endif

#ifdef _M_X64
typedef signed __int64 count_t;
typedef unsigned __int64 ucount_t;
#else
typedef signed int count_t;
typedef unsigned int ucount_t;
#endif

#ifdef _WIN32
#define DECLSPEC_DLLIMPORT __declspec(dllimport)
#define DECLSPEC_DLLEXPORT __declspec(dllexport)
#else
#define DECLSPEC_DLLIMPORT
#define DECLSPEC_DLLEXPORT
#endif

#include <new>

#include <float.h>

#ifndef __LERSTAD__
#include <xutility>
#endif

namespace System
{
	class Type;
	class ClassType;
	class Module;

	extern Module _Module;
}

#ifdef __LERSTAD__

namespace std
{

typedef const char *__exString;

class exception
{
public:
	CTOR exception();
	CTOR exception(const __exString&);
	CTOR exception(const exception&);
	virtual ~exception();
	virtual __exString what() const;

private:
    __exString _m_what;
    int _m_doFree;
};

}

#endif

#if defined(_WIN32) && (defined(_MSC_VER) || defined(__LERSTAD__))

// This is basically a copy of typeinfo.h, with an added GetType method in type_info
#ifndef _INC_TYPEINFO
#define _INC_TYPEINFO

 #if !defined(_WIN32) && !defined(_MAC)
  #error ERROR: Only Mac or Win32 targets supported!
 #endif


/* Define _CRTIMP */

#ifndef _CRTIMP
#ifdef	_NTSDK
/* definition compatible with NT SDK */
#define _CRTIMP
#else	/* ndef _NTSDK */
/* current definition */
#ifdef	_DLL
#define _CRTIMP __declspec(dllimport)
#else	/* ndef _DLL */
#define _CRTIMP
#endif	/* _DLL */
#endif	/* _NTSDK */
#endif	/* _CRTIMP */

//#include <xstddef>

//#ifdef  _MSC_VER
//#pragma pack(push,8)

//#endif  /* _MSC_VER */

#define _TYPEINFO_

class type_info
{
public:

 #if _HAS_CPP0X
	size_t hash_code() const _THROW0()
		{	// hash name() to size_t value by pseudorandomizing transform
		const char *_Keyval = name();
		size_t _Val = 2166136261U;
		size_t _First = 0;
		size_t _Last = _CSTD strlen(_Keyval);
		size_t _Stride = 1 + _Last / 10;

		for(; _First < _Last; _First += _Stride)
			_Val = 16777619U * _Val ^ (size_t)_Keyval[_First];
		return (_Val);
		}
 #endif /* _HAS_CPP0X */

	_CRTIMP virtual ~type_info();

	_CRTIMP bool operator==(const type_info& rhs) const;
	_CRTIMP bool operator!=(const type_info& rhs) const;

	_CRTIMP bool before(const type_info& rhs) const;
	_CRTIMP const char* name() const;
	_CRTIMP const char* raw_name() const;

	_CRTIMP bool operator < (const type_info& other) const
	{
		return this->before(other);
	}

	_CRTIMP bool operator <= (const type_info& other) const
	{
		return *this == other || this->before(other);
	}

	_CRTIMP bool operator > (const type_info& other) const
	{
		return other.before(*this);
	}

	inline System::Type* GetType() const;

	inline operator System::Type* () const
	{
		return GetType();
	}

	inline System::Type* operator -> () const
	{
		return GetType();
	}

private:

//	friend void Build_rtti(System::ClassType* pType);

	void* _m_data;
	char _m_d_name[1];

	CTOR type_info(const type_info& rhs);
	type_info& operator=(const type_info& rhs);
};

#ifndef __LERSTAD__
// This include must occur below the definition of class type_info
#include <typeinfo>
#include <stdexcpt.h>

namespace std
{

class _CRTIMP bad_cast : public exception {
public:
	bad_cast(const char* what_arg = "bad cast") : exception (what_arg) {}
	bad_cast(const bad_cast &_That) : exception(_That) {}
};

class _CRTIMP bad_typeid : public exception {
public:
    bad_typeid(const char * what_arg) : exception (what_arg) {}
};

class _CRTIMP __non_rtti_object : public bad_typeid {
public:
    __non_rtti_object(const char * what_arg) : bad_typeid(what_arg) {}
};

}

#endif


//#ifdef  _MSC_VER
//#pragma pack(pop)

//#endif  /* _MSC_VER */

#endif // _INC_TYPEINFO

#else

/*
#include <typeinfo>
*/

// RTTI support for -*- C++ -*-
// Copyright (C) 1994, 1995, 1996, 1997, 1998, 2000, 2001, 2002
// Free Software Foundation
//
// This file is part of GCC.
//
// GCC is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// GCC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GCC; see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

/** @file typeinfo
 *  This header provides RTTI support.
 */

#ifndef _TYPEINFO
#define _TYPEINFO

#include <exception>

extern "C++" {

namespace __cxxabiv1
{
  class __class_type_info;
} // namespace __cxxabiv1

#if !__GXX_WEAK__
  // If weak symbols are not supported, typeinfo names are not merged.
  #define __GXX_MERGED_TYPEINFO_NAMES 0
#else
  // On platforms that support weak symbols, typeinfo names are merged.
  #define __GXX_MERGED_TYPEINFO_NAMES 1
#endif

namespace std 
{
  /**
   *  @brief  Part of RTTI.
   *
   *  The @c type_info class describes type information generated by
   *  an implementation.
  */
  class type_info 
  {
  public:
    /** Destructor. Being the first non-inline virtual function, this
     *  controls in which translation unit the vtable is emitted. The
     *  compiler makes use of that information to know where to emit
     *  the runtime-mandated type_info structures in the new-abi.  */
    virtual ~type_info();

  private:
    /// Assigning type_info is not supported.  Made private.
    type_info& operator=(const type_info&);
    CTOR type_info(const type_info&);
    
  protected:
    const char *__name;
    
  protected:
    explicit CTOR type_info(const char *__n): __name(__n) { }
    
  public:
    // the public interface
    /** Returns an @e implementation-defined byte string; this is not
     *  portable between compilers!  */
    const char* name() const
    { return __name; }

	 System::Type* GetType() const;

#if !__GXX_MERGED_TYPEINFO_NAMES
    bool before(const type_info& __arg) const;
    // In old abi, or when weak symbols are not supported, there can
    // be multiple instances of a type_info object for one
    // type. Uniqueness must use the _name value, not object address.
    bool operator==(const type_info& __arg) const;
#else
    /** Returns true if @c *this precedes @c __arg in the implementation's
     *  collation order.  */
    // In new abi we can rely on type_info's NTBS being unique,
    // and therefore address comparisons are sufficient.
    bool before(const type_info& __arg) const
    { return __name < __arg.__name; }
    bool operator==(const type_info& __arg) const
    { return __name == __arg.__name; }
#endif
    bool operator!=(const type_info& __arg) const
    { return !operator==(__arg); }
    
    // the internal interface
  public:
    // return true if this is a pointer type of some kind
    virtual bool __is_pointer_p() const;
    // return true if this is a function type
    virtual bool __is_function_p() const;

    // Try and catch a thrown type. Store an adjusted pointer to the
    // caught type in THR_OBJ. If THR_TYPE is not a pointer type, then
    // THR_OBJ points to the thrown object. If THR_TYPE is a pointer
    // type, then THR_OBJ is the pointer itself. OUTER indicates the
    // number of outer pointers, and whether they were const
    // qualified.
    virtual bool __do_catch(const type_info *__thr_type, void **__thr_obj,
			    unsigned __outer) const;

    // internally used during catch matching
    virtual bool __do_upcast(const __cxxabiv1::__class_type_info *__target,
			     void **__obj_ptr) const;
  };

  /**
   *  @brief  Thrown during incorrect typecasting.
   *
   *  If you attempt an invalid @c dynamic_cast expression, an instance of
   *  this class (or something derived from this class) is thrown.  */
  class bad_cast : public exception 
  {
  public:
    CTOR bad_cast() throw() { }
    // This declaration is not useless:
    // http://gcc.gnu.org/onlinedocs/gcc-3.0.2/gcc_6.html#SEC118
    virtual ~bad_cast() throw();
  };
  
  /** If you use a NULL pointer in a @c typeid expression, this is thrown.  */
  class bad_typeid : public exception 
  {
  public:
    CTOR bad_typeid () throw() { }
    // This declaration is not useless:
    // http://gcc.gnu.org/onlinedocs/gcc-3.0.2/gcc_6.html#SEC118
    virtual ~bad_typeid() throw();
  };
} // namespace std

} // extern "C++"
#endif

#endif


#if defined(_WIN32) && (defined(_MSC_VER) || defined(__LERSTAD__))
typedef type_info Type_Info;
#else
typedef std::type_info Type_Info;
#endif

#ifndef __LERSTAD__
#include <boost/intrusive/avl_set.hpp>
#endif

namespace System
{
class Object;
class Module;
class Declarator;

LFCEXT DECLSPEC_RESTRICT Object* allocate_object(size_t size);
LFCEXT DECLSPEC_RESTRICT Object* allocate_object(size_t size, const char* filename, int line);
LFCEXT DECLSPEC_RESTRICT void* allocate_buffer(size_t size);
LFCEXT DECLSPEC_RESTRICT void* allocate_buffer(size_t size, const char* filename, int line);
LFCEXT void* try_resize_buffer(void* pv, size_t newsize);
LFCEXT void* reallocate_buffer(void* buffer, size_t newsize);
LFCEXT size_t get_buffer_size(const void* pv);
LFCEXT void free_object(Object* pv);
LFCEXT void free_buffer(void* pv);

}

#if _WIN32
#define TRY try
#define CATCH(x) catch(x)
#define THROW(x)	throw x
#else
#define TRY if (true)
#define CATCH(x) else
#define THROW(x)	ASSERT(0)
#endif

// replaceable signatures
inline void *operator new (size_t size)
{
	return System::allocate_buffer(size);
}

inline void *operator new[] (size_t size)
{
	return System::allocate_buffer(size);
}

/*
// replaceable signatures
inline void *operator new (size_t size, System::Module* pModule)
{
	return System::allocate_buffer(size, pModule);
}

inline void *operator new[] (size_t size, System::Module* pModule)
{
	return System::allocate_buffer(size, pModule);
}
*/

inline void *operator new (size_t size, const char* filename, int line)
{
	return System::allocate_buffer(size, filename, line);
}

inline void *operator new[] (size_t size, const char* filename, int line)
{
	return System::allocate_buffer(size, filename, line);
}

inline void operator delete (void *pv)
{
	System::free_buffer(pv);
}

inline void operator delete[] (void *pv)
{
	System::free_buffer(pv);
}

#ifndef ASSERT
#define ASSERT(expr) _ASSERTE(expr)
#endif

#define ASSUME(expr) do { ASSERT(expr); __analysis_assume(!!(expr)); } while(0)

extern "C"
{
	LFCEXT void _Break(const char* filename, int line);
}

#ifndef VERIFY
	#ifdef _DEBUG
		#define VERIFY(x) ASSERT(x)
	#else
		#define VERIFY(x) do{ if (!(x)) _Break(__FILE__, __LINE__); } while(0)
	#endif
#endif

namespace System
{

typedef unsigned char byte;	// A little controversial, breaking compatibility with a lot of source code
typedef signed char sbyte;
typedef unsigned char ubyte;

// TODO on PPC, bool is 4 bytes ?
typedef bool bool8;

typedef signed char tiny_int;
typedef unsigned char tiny_uint;

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef unsigned int uint;
typedef unsigned char uint8;
typedef uint8* puint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef int ErrorCode;
typedef int ErrorCode_Bool;

enum
{
	Success_False = 1,
	Success_True = 0,
	Success = 0,
	Error = -1,
	Error_Failed = -1,
	Error_NoInterface,
	Error_NotImplemented,
	Error_NullPointerArgument,
	Error_InvalidArgument,
};

}

#ifdef _MSC_VER

typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

typedef __int64 int64;
typedef unsigned __int64 uint64;

#else

/*
// gcc on Amiga give linking errors when using wchar_t
#if 0
	typedef wchar_t WCHAR;
#else
	typedef unsigned short WCHAR;
#endif
*/

/*
#ifdef __LERSTAD__

typedef wchar_t WCHAR;
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#else
  */

typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;

typedef long long int64;
typedef unsigned long long uint64;

//#endif

#endif

#ifdef __GNUC__
#include <assert.h>
#define _ASSERTE(x) assert(x)

#endif

#include <malloc.h>

#if _WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#ifdef __LERSTAD__

#ifndef _FILE_DEFINED
typedef struct _iobuf FILE;
#endif

namespace std
{
extern "C"
{
void *memcpy( void *dest, const void *src, size_t count);
int memcmp(const void*, const void*, int len);
int strcmp(const char*, const char*);
int wcscmp(const WCHAR*, const WCHAR*);
}
}

#endif

#define _VA_LIST_DEFINED
typedef char* va_list;

#ifndef __LERSTAD__

#ifdef _MSC_VER
#include <crtdbg.h>

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <cwchar>

#else

extern "C"
{

namespace std
{
void *memcpy( void *dest, const void *src, size_t count);
int memcmp(const void*, const void*, int len);
int strcmp(const char*, const char*);
int wcscmp(const WCHAR*, const WCHAR*);
}

void _DebugBreak(const char* file, int line);

}

#define _ASSERTE(x) do{ if (!(x)) _DebugBreak(__FILE__, __LINE__); } while(0)

#endif

#endif

namespace System
{

#define LittleEndian16(x) (x)
#define LittleEndian32(x) (x)

inline uint16 BigEndian16(uint16 x)
{
	return ((uint16)((((uint16)(x)/* & 0x00ff*/)<<8) |
		(((uint16)(x)/* & 0xff00*/)>>8)));
}

inline uint32 BigEndian32(uint32 x)
{
	return ((((uint32)(x)/* & 0x000000ff*/)<<24) |
								 (((uint32)(x) & 0x0000ff00)<<8) |
								 (((uint32)(x) & 0x00ff0000)>>8) |
								 (((uint32)(x)/* & 0xff000000*/)>>24));
}

inline ULONGLONG BigEndian64(ULONGLONG x)
{
	ULONGLONG val = (x>>56);
	val |= ((x>>48) & 0xff)<<8;
	val |= ((x>>40) & 0xff)<<16;
	val |= ((x>>32) & 0xff)<<24;
	val |= ((x>>24) & 0xff)<<32;
	val |= ((x>>16) & 0xff)<<40;
	val |= ((x>>8) & 0xff)<<48;
	val |= ((x))<<56;

	return val;
#if 0
	return ((((uint32)(x)/* & 0x000000ff*/)<<24) |
								 (((uint32)(x) & 0x0000ff00)<<8) |
								 (((uint32)(x) & 0x00ff0000)>>8) |
								 (((uint32)(x)/* & 0xff000000*/)>>24));
#endif
}

}

#elif __GNUC__

#define __builtin_bswap32 _byteswap_ulong
#define __builtin_bswap64 _byteswap_uint64

#define BigEndian16(x) (x)
#define BigEndian32(x) (x)
#define BigEndian64(x) (x)

namespace System
{

inline uint16 LittleEndian16(uint16 x)
{
	return ((uint16)((((uint16)(x)/* & 0x00ff*/)<<8) |
		(((uint16)(x)/* & 0xff00*/)>>8)));
}

inline uint32 LittleEndian32(uint32 x)
{
	return ((((uint32)(x)/* & 0x000000ff*/)<<24) |
								 (((uint32)(x) & 0x0000ff00)<<8) |
								 (((uint32)(x) & 0x00ff0000)>>8) |
								 (((uint32)(x)/* & 0xff000000*/)>>24));
}

}

#elif AMIGA

#include <memory.h>
#include <malloc.h>

extern "C" int sprintf(char*, const char*, ...);

/*
extern "C" int memcmp( const void *buf1, const void *buf2, int count);
extern "C" void *memcpy( void *dest, const void *src, int count );
extern "C" void *memset( void *dest, int c, int count );
*/

template <class T> inline T abs(T value)
{
	return (value >= 0)? value: -value;
}

#define BigEndian16(x) (x)
#define BigEndian32(x) (x)
#define BigEndian64(x) (x)

inline uint16 LittleEndian16(uint16 x)
{
	return ((uint16)((((uint16)(x)/* & 0x00ff*/)<<8) |
		(((uint16)(x)/* & 0xff00*/)>>8)));
}

inline uint32 LittleEndian32(uint32 x)
{
	return ((((uint32)(x)/* & 0x000000ff*/)<<24) |
								 (((uint32)(x) & 0x0000ff00)<<8) |
								 (((uint32)(x) & 0x00ff0000)>>8) |
								 (((uint32)(x)/* & 0xff000000*/)>>24));
}

EXTERN_C int printf(const char *, ...);

//#define OLE2ANSI

//#define __int64 long long

typedef char TCHAR;

//typedef int BOOL;
typedef const TCHAR* LPCTSTR;

typedef void* HANDLE;

typedef char OLECHAR;
typedef char syschar;

typedef const OLECHAR* LPCOLESTR;

//#define DECLSPEC_IMPORT
#define WINBASEAPI	DECLSPEC_DLLIMPORT
#define WINUSERAPI	DECLSPEC_DLLIMPORT
#define WINAPI

#define IN
#define OUT

#define _cdecl
#define __cdecl
#define __stdcall
#define __fastcall

inline void TRACE(const char* ,...) {}

void _DebugBreak(const char* file, int line);

#define _ASSERTE(x) do{ if (!(x)) _DebugBreak(__FILE__, __LINE__); } while(0)

/*  32-Bit Absolute Memory Pointer.  C pointer math will not       */
#ifndef APTR_TYPEDEF
#define APTR_TYPEDEF
typedef void	       *APTR;	    /* 32-bit untyped pointer */
#endif

// Forward declaration of some often used amiga structures
struct Task;
struct MsgPort;
struct IntuiMessage;

long InterlockedIncrement(long* plong);
long InterlockedDecrement(long* plong);

bool ReadProcessMemory(Task* task, const void* lpBaseAddress, void* lpBuffer, unsigned long nSize, unsigned long* lpNumberOfBytesRead);
bool WriteProcessMemory(Task* task, void* lpBaseAddress, const void* lpBuffer, unsigned long nSize, unsigned long* lpNumberOfBytesWritten);

//#define MIDL_INTERFACE(x)   struct //DECLSPEC_UUID(x) DECLSPEC_NOVTABLE

// TODO, have this somewhere else

// File commands
#define ID_FILE_NEW                     0xE100
#define ID_FILE_OPEN                    0xE101
#define ID_FILE_CLOSE                   0xE102
#define ID_FILE_SAVE                    0xE103
#define ID_FILE_SAVE_AS                 0xE104
#define ID_FILE_PAGE_SETUP              0xE105
#define ID_FILE_PRINT_SETUP             0xE106
#define ID_FILE_PRINT                   0xE107
#define ID_FILE_PRINT_DIRECT            0xE108
#define ID_FILE_PRINT_PREVIEW           0xE109
#define ID_FILE_UPDATE                  0xE10A
#define ID_FILE_SAVE_COPY_AS            0xE10B
#define ID_FILE_SEND_MAIL               0xE10C

#define ID_FILE_MRU_FIRST               0xE110
#define ID_FILE_MRU_FILE1               0xE110          // range - 16 max
#define ID_FILE_MRU_FILE2               0xE111
#define ID_FILE_MRU_FILE3               0xE112
#define ID_FILE_MRU_FILE4               0xE113
#define ID_FILE_MRU_FILE5               0xE114
#define ID_FILE_MRU_FILE6               0xE115
#define ID_FILE_MRU_FILE7               0xE116
#define ID_FILE_MRU_FILE8               0xE117
#define ID_FILE_MRU_FILE9               0xE118
#define ID_FILE_MRU_FILE10              0xE119
#define ID_FILE_MRU_FILE11              0xE11A
#define ID_FILE_MRU_FILE12              0xE11B
#define ID_FILE_MRU_FILE13              0xE11C
#define ID_FILE_MRU_FILE14              0xE11D
#define ID_FILE_MRU_FILE15              0xE11E
#define ID_FILE_MRU_FILE16              0xE11F
#define ID_FILE_MRU_LAST                0xE11F

// Edit commands
#define ID_EDIT_CLEAR                   0xE120
#define ID_EDIT_CLEAR_ALL               0xE121
#define ID_EDIT_COPY                    0xE122
#define ID_EDIT_CUT                     0xE123
#define ID_EDIT_FIND                    0xE124
#define ID_EDIT_PASTE                   0xE125
#define ID_EDIT_PASTE_LINK              0xE126
#define ID_EDIT_PASTE_SPECIAL           0xE127
#define ID_EDIT_REPEAT                  0xE128
#define ID_EDIT_REPLACE                 0xE129
#define ID_EDIT_SELECT_ALL              0xE12A
#define ID_EDIT_UNDO                    0xE12B
#define ID_EDIT_REDO                    0xE12C

// Help and App commands
#define ID_APP_ABOUT                    0xE140
#define ID_APP_EXIT                     0xE141
#define ID_HELP_INDEX                   0xE142
#define ID_HELP_FINDER                  0xE143
#define ID_HELP_USING                   0xE144
#define ID_CONTEXT_HELP                 0xE145      // shift-F1
// special commands for processing help
#define ID_HELP                         0xE146      // first attempt for F1
#define ID_DEFAULT_HELP                 0xE147      // last attempt

#elif __APPLE__

//#include <ApplicationServices/ApplicationServices.h>

#if __BIG_ENDIAN__

#define BigEndian16(x) (x)
#define BigEndian32(x) (x)

inline uint16 LittleEndian16(uint16 x)
{
	return ((uint16)((((uint16)(x)/* & 0x00ff*/)<<8) |
		(((uint16)(x)/* & 0xff00*/)>>8)));
}

inline uint32 LittleEndian32(uint32 x)
{
	return ((((ULONG)(x)/* & 0x000000ff*/)<<24) |
								 (((ULONG)(x) & 0x0000ff00)<<8) |
								 (((ULONG)(x) & 0x00ff0000)>>8) |
								 (((ULONG)(x)/* & 0xff000000*/)>>24));
}

#else

#define LittleEndian16(x) (x)
#define LittleEndian32(x) (x)

#define BigEndian16(x)	((uint16)((((uint16)(x) & 0x00ff)<<8) |      (((uint16)(x) & 0xff00)>>8)))
#define BigEndian32(x)	((((ULONG)(x) & 0x000000ff)<<24) |   (((ULONG)(x) & 0x0000ff00)<<8) |     (((ULONG)(x) & 0x00ff0000)>>8) |     (((ULONG)(x) & 0xff000000)>>24))

#endif

//#include <mach-o/dyld.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
typedef int BOOL;
typedef wchar_t WCHAR;
typedef const char* LPCSTR;
typedef const wchar_t* LPCWSTR;

#define SUCCEEDED(x) ((LONG)x >= 0)
#define FAILED(x) ((LONG)x < 0)

#define EXTERN_C	extern "C"

//#define interface struct
#define DECLSPEC_NOVTABLE
#define DECLSPEC_UUID(x)
#define MIDL_INTERFACE(x)	interface DECLSPEC_UUID(x) DECLSPEC_NOVTABLE

namespace System
{
extern const GUID GUID_NULL;
}

inline void TRACE(const char* ,...) {}
inline BOOL MessageBeep(uint uType) { return TRUE; }

inline void _DebugBreak(const char* file, int line)
{
	printf("assertion at %s(%d)\n", file, line);
	fflush(stdout);
	THROW(-1);
}

#define _ASSERTE(x) do{ if (!(x)) _DebugBreak(__FILE__, __LINE__); } while(0)

#define _cdecl
#define __cdecl
#define __stdcall
#define __fastcall

#define STDMETHODCALLTYPE
#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHOD(method)       virtual HRESULT STDMETHODCALLTYPE method

#define OLE2ANSI	// TODO remove

#ifdef OLE2ANSI
	typedef char TCHAR;
	typedef char OLECHAR;
	typedef char syschar;
#else
	typedef wchar_t TCHAR;
	typedef wchar_t OLECHAR;
	typedef wchar_t syschar;
#endif

typedef const TCHAR* LPCTSTR;	// TODO remove

extern "C"
{
int stricmp(const char*, const char*);
int strnicmp(const char*, const char*, int);
}

#else

#error "Unknown OS"

#endif

namespace System
{

inline void BigEndian(uint16 * data)
{
	*data = BigEndian16(*data);
}

inline void BigEndian(uint32 * data)
{
	*data = BigEndian32(*data);
}

inline void BigEndian(ULONGLONG * data)
{
	*data = BigEndian64(*data);
}

}

//#ifndef GUID_DEFINED
//#define GUID_DEFINED
#ifdef __LERSTAD__

typedef struct _GUID
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];

	 /*
	 bool Equals(const _GUID& other) const
	 {
		 return memcmp(this, &other, 16) == 0;
	 }
	 */
}
GUID;

typedef GUID IID;

#endif

#if AMIGA

extern "C"
{

int isalpha(int);
int isdigit(int);
int isxdigit(int);
int isalnum(int);
int isspace(int);
int tolower(int);
int toupper(int);

int wcscmp(const WCHAR*, const WCHAR*);
int wcsncmp(const WCHAR*, const WCHAR*, int);
int wcsicmp(const WCHAR*, const WCHAR*);
int wcsnicmp(const WCHAR*, const WCHAR*, int);

WCHAR* wcscpy(WCHAR* dest, const WCHAR* src);
WCHAR* wcsncpy(WCHAR* dest, const WCHAR* src, int len);

WCHAR* wcschr(const WCHAR*, WCHAR);
WCHAR* wcsstr(const WCHAR*, const WCHAR*);

int wcslen(const WCHAR* str);

int swprintf(WCHAR* dst, const WCHAR* format, ...);

}

inline WCHAR* wcschr(WCHAR* x, WCHAR y)
{
	return (WCHAR*)wcschr((const WCHAR*)x, y);
}

inline WCHAR* wcsstr(WCHAR* x, const WCHAR* y)
{
	return (WCHAR*)wcsstr((const WCHAR*)x, y);
}

// ?
#define iswalpha isalpha
#define iswdigit isdigit
#define iswalnum isalnum
#define iswspace isspace
#define iswxdigit isxdigit
#define towlower tolower
#define towupper toupper

#endif

#define ASTR(x) x
#define WSTR(x) L##x

#ifndef MAX
#define MAX(a,b) ((a)>(b)? (a): (b))
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)? (a): (b))
#endif

namespace std
{
#include <ctype.h>
}

#ifdef _M_IX86
PVOID RtlPcToFileHeader_(PVOID PcValue, PVOID* BaseOfImage);
#else
#define RtlPcToFileHeader_ RtlPcToFileHeader
#endif

namespace System
{
class Object;
class Variant;
class Type;
class ClassType;
//class Heap;
class Exception;
class SystemException;

typedef char char8;
typedef wchar_t char16;			// NOTE: wchar_t isn't necessarily 16-bit by default on all compilers
//typedef uint32 char32;

class std_allocator
{
public:
	DECLSPEC_RESTRICT inline char* _Charalloc(size_t size)
	{
		return (char*)malloc(size);
	}

	DECLSPEC_RESTRICT inline void* allocate_buffer(size_t size)
	{
		return malloc(size);
	}

	inline void* try_resize_buffer(void* pv, size_t newsize)
	{
		return NULL;
	}

	inline void* reallocate_buffer(void* pv, size_t newsize)
	{
		return realloc(pv, newsize);
	}

	inline void free_buffer(void* pv)
	{
		free(pv);
	}

	DECLSPEC_RESTRICT inline System::Object* allocate_object(size_t size, Module* pModule = NULL, const char* filename = NULL, int line = -1)
	{
		return (System::Object*)malloc(size);
	}

	inline void free_object(System::Object* object)
	{
		free(object);
	}
};

class LFCEXT grow_allocator
{
public:
	inline CTOR grow_allocator()
	{
		ASSERT(0);
	}

	inline CTOR grow_allocator(void* buffer, size_t size)
	{
		m_buffer = (byte*)buffer;
		m_size = size;
		m_next = 0;
	}

	DECLSPEC_RESTRICT inline Object* allocate_object(size_t size, Module* pModule = NULL, const char* filename = NULL, int line = -1)
	{
		return (Object*)allocate_buffer(size);
	}

	inline void* try_resize_buffer(void* pv, size_t newsize)
	{
		return NULL;
	}

	DECLSPEC_RESTRICT void* allocate_buffer(size_t size);
	void* reallocate_buffer(void* pv, size_t size);

	void free_buffer(void* p)
	{
		if (p == NULL) return;

		ASSERT(p == m_buffer);
		m_next = 0;
	}

	inline void free_object(Object* object)
	{
		free_buffer(object);
	}

	byte* m_buffer;
	size_t m_size;
	ULONG m_next;
};

class LFCEXT __gc_allocator
{
public:
	DECLSPEC_RESTRICT inline void* allocate_buffer(size_t size)
	{
		return System::allocate_buffer(size);
	}

	DECLSPEC_RESTRICT inline void* allocate_buffer_size(size_t size)
	{
		return System::allocate_buffer(size);
	}

	inline void* try_resize_buffer(void* pv, size_t newsize)
	{
		return System::try_resize_buffer(pv, newsize);
	}

	inline void* reallocate_buffer(void* pv, size_t size)
	{
		return System::reallocate_buffer(pv, size);
	}

	inline void free_buffer(void* pv)
	{
		return System::free_buffer(pv);
	}

/*
	inline size_t get_buffer_size(const void* buffer) const
	{
		return *((ULONG*)buffer - 1);
		//return System::get_buffer_size(buffer);
	}
*/

	DECLSPEC_RESTRICT inline Object* allocate_object(size_t size)
	{
		return System::allocate_object(size);
	}

	DECLSPEC_RESTRICT inline Object* allocate_object(size_t size, const char* filename, int line)
	{
		return System::allocate_object(size, filename, line);
	}

	inline void free_object(Object* object)
	{
		return System::free_buffer(object);
	}
};

template<class T> class string_data
{
public:
	CTOR string_data(const T* _data, size_t _len) : data(_data), len(_len)
	{
	}

	CTOR string_data(const T* _data) : data(_data)
	{
		len = cstrlen(_data);
	}

	int Compare(const string_data& other) const
	{
		if (this == &other) return 0;

		size_t i;
		for (i = 0; i < len; ++i)
		{
			T c = data[i];

			if (i == other.len) return 1;	// return > 0

			T c2 = other.data[i];

			int diff = c - c2;
			if (diff)
				return diff;
		}
	
		if (len == other.len)
			return 0;
		else
			return -1;
	}

	bool operator == (const string_data& other) const
	{
		return Compare(other) == 0;
	}

	bool operator != (const string_data& other) const
	{
		return Compare(other) != 0;
	}

	bool operator < (const string_data& other) const
	{
		return Compare(other) < 0;
	}

	bool operator > (const string_data& other) const
	{
		return Compare(other) > 0;
	}

	const T* data;
	size_t len;
};

template<class T, class A = __gc_allocator> class string_alloc
{
public:
	CTOR string_alloc(size_t len, A& a = A()) : m_strdata((T*)a.allocate_buffer((len+1)*sizeof(T)), len)
	{
	//	m_strdata.data[len] = 0;	// TODO remove
	}

	operator string_data<T> ()
	{
		return m_strdata;
	}

	string_data<T> m_strdata;
};

template<class T> string_data<T> StringData(const T* cstr, size_t len)
{
	return string_data<T>(cstr, len);
}

template<class T> string_data<T> string_copy(const T* cstr)
{
	__gc_allocator a;

	size_t len = cstrlen(cstr);
	T* data = (T*)a.allocate_buffer((len)*sizeof(T));
	memcpy(data, cstr, len*sizeof(T));
//	data[len] = 0;
	return string_data<T>(data, len);
}

template<class T> string_data<T> string_copy(const T* cstr, size_t len)
{
	__gc_allocator a;

	T* data = (T*)a.allocate_buffer((len)*sizeof(T));
	memcpy(data, cstr, len*sizeof(T));
//	data[len] = 0;
	return string_data<T>(data, len);
}

template<class T> string_data<char> string_copya(const T* cstr, size_t len)
{
	__gc_allocator a;

	char* data = (char*)a.allocate_buffer((len+1));
	for (size_t i = 0; i < len; i++)
	{
		data[i] = char(cstr[i]);
	}
	data[len] = 0;
	return string_data<char>(data, len);
}

template<class T> string_data<wchar_t> string_copyw(const T* cstr, size_t len)
{
	__gc_allocator a;

	wchar_t* data = (wchar_t*)a.allocate_buffer((len+1)*sizeof(wchar_t));
	for (size_t i = 0; i < len; i++)
	{
		data[i] = wchar_t(cstr[i]);
	}
	data[len] = 0;
	return string_data<wchar_t>(data, len);
}

/*
template<class T, class A> string_data<T> string_copy(const T* cstr, const A& a)
{
	unsigned int len = cstrlen(cstr);
	T* data = (T*)a.allocate_buffer((len+1)*sizeof(T));
	memcpy(data, cstr, len*sizeof(T));
	data[len] = 0;
	return string_data<T>(data, len);
}
*/

#ifndef __LERSTAD__
template<class T, class A> string_data<T> string_copy(const T* cstr, unsigned int len, const A& a)
{
	if (len == -1) len = cstrlen(cstr);

	T* data = (T*)a.allocate_buffer((len+1)*sizeof(T));
	memcpy(data, cstr, len*sizeof(T));
	data[len] = 0;
	return string_data<T>(data, len);
}
#endif

}

#if 0
#ifndef __LERSTAD__

template<class T, class arg_t> inline T _dynamic_cast_(arg_t* obj)
{
	struct rtti_object_locator
	{
		int signature;
		int offset_to_top;
		DWORD cdOffset;	//constructor displacement offset
	};
	
	void* vtable = *(void**)obj;
	rtti_object_locator* locator = ((rtti_object_locator**)vtable)[-1];
	DWORD oldcdOffset = locator->cdOffset;
	locator->cdOffset = 0;
	T r = dynamic_cast<T>(obj);
	locator->cdOffset = oldcdOffset;
	return r;
}

#define dynamic_cast _dynamic_cast_

#endif	// __LERSTAD__
#endif

#define _new new (__FILE__, __LINE__)

#define new _new

#ifdef _DEBUG

#ifndef TRACE_LEVEL
#define TRACE_LEVEL 0
#endif

namespace System
{

inline void _cdecl Trace(LPCSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	char szBuffer[2048];

	nBuf = _vsnprintf_s(szBuffer, sizeof(szBuffer), _countof(szBuffer)-1, lpszFormat, args);
	ASSERT(nBuf < sizeof(szBuffer)); //Output truncated as it was > sizeof(szBuffer)

	OutputDebugStringA(szBuffer);
	va_end(args);
}

}

namespace System
{

inline void _cdecl Trace(LPCWSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	WCHAR szBuffer[512];

	nBuf = _vsnwprintf_s(szBuffer, sizeof(szBuffer), _countof(szBuffer)-1, lpszFormat, args);
	ASSERT(nBuf < sizeof(szBuffer));//Output truncated as it was > sizeof(szBuffer)

	OutputDebugStringW(szBuffer);
	va_end(args);
}
}

#if 0
#ifndef TRACE
#define TRACE            Trace
//#define ATLTRACE2           AtlTrace2
#endif
//#define ATLTRACENOTIMPL(funcname)   ATLTRACE2(atlTraceNotImpl, 2, _T("ATL: %s not implemented.\n"), funcname); return E_NOTIMPL
#else // !DEBUG
inline void Trace(const char* , ...){}
//inline void _cdecl AtlTrace2(ULONG, UINT, LPCSTR , ...){}
#ifndef OLE2ANSI
inline void Trace(const WCHAR* , ...){}
//inline void _cdecl AtlTrace2(ULONG, UINT, LPCWSTR , ...){}
#endif //OLE2ANSI
#ifndef TRACE
#define TRACE            1 ? (void)0 : Trace
//#define ATLTRACE2           1 ? (void)0 : AtlTrace2
#endif //ATLTRACE
//#define ATLTRACENOTIMPL(funcname)   return E_NOTIMPL
#endif //_DEBUG
#endif

#ifdef _DEBUG
#define DebugTrace(x)	IO::DebugStream::get_Out() << x
#define DebugTraceLn(x)	IO::DebugStream::get_Out() << x << '\n'
#else
#define DebugTrace(x)
#define DebugTraceLn(x)
#endif

#if _WIN32

inline System::Type* type_info::GetType() const
{
	//ASSERT(_m_data);
	return (System::Type*)_m_data;
}

#endif

namespace System
{

interface IFunction
{
	virtual size_t get_NumArgs() abstract;
};

#if _WIN32

class LFCEXT CriticalSection
{
public:
	inline CTOR CriticalSection()
	{
		InitializeCriticalSection(&m_sec);
	}

	inline ~CriticalSection()
	{
		DeleteCriticalSection(&m_sec);
	}

	/*
	inline void Lock()
	{
		EnterCriticalSection(&m_sec);
	}

	inline void Unlock()
	{
		LeaveCriticalSection(&m_sec);
	}

	inline bool Try()
	{
		return TryEnterCriticalSection(&m_sec)? true: false;
	}
	*/

	operator CRITICAL_SECTION* ()
	{
		return &m_sec;
	}

private:

	CRITICAL_SECTION m_sec;
};

class LFCEXT CriticalSectionLock
{
public:

	inline CTOR CriticalSectionLock(CRITICAL_SECTION* pCritSection) : m_pCritSection(pCritSection)
	{
		ASSERT(pCritSection);
		EnterCriticalSection(pCritSection);
	}

	inline CTOR CriticalSectionLock(CriticalSectionLock&& other) : m_pCritSection(other.m_pCritSection)
	{
		other.m_pCritSection = nullptr;
	}

	inline ~CriticalSectionLock()
	{
		ASSERT(m_pCritSection);
		LeaveCriticalSection(m_pCritSection);
	}

	operator CRITICAL_SECTION*()
	{
		return m_pCritSection;
	}

	CRITICAL_SECTION* m_pCritSection;

private:
	CTOR CriticalSectionLock(const CriticalSectionLock&);
	CriticalSectionLock& operator=(const CriticalSectionLock&);
};

class LFCEXT TryCriticalSectionLock
{
public:

	inline CTOR TryCriticalSectionLock(CRITICAL_SECTION* pCritSection) : m_pCritSection(NULL)
	{
		ASSERT(pCritSection);
		if (TryEnterCriticalSection(pCritSection))
		{
			m_pCritSection = pCritSection;
		}
	}

	inline ~TryCriticalSectionLock()
	{
		if (m_pCritSection) LeaveCriticalSection(m_pCritSection);
	}

	operator bool () const
	{
		return m_pCritSection != NULL;
	}

	CRITICAL_SECTION* m_pCritSection;
};

#ifdef __LERSTAD__
typedef PVOID SRWLOCK;
#endif

class LFCEXT SRWLock
{
public:

	inline CTOR SRWLock()
	{
		ASSERT(0);
#if 0
		InitializeSRWLock(&m_SRWLock);
#endif
	}

	operator SRWLOCK* ()
	{
		return &m_SRWLock;
	}

	SRWLOCK m_SRWLock;
};

class LFCEXT ReadLock
{
public:

	inline CTOR ReadLock(SRWLOCK* pSRWLock) : m_pSRWLock(pSRWLock)
	{
		ASSERT(pSRWLock);
		ASSERT(0);
#if 0
		AcquireSRWLockShared(pSRWLock);
#endif
	}

	inline ~ReadLock()
	{
#if 0
		ReleaseSRWLockShared(m_pSRWLock);
#endif
	}

	SRWLOCK* m_pSRWLock;
};

class LFCEXT WriteLock
{
public:

	inline CTOR WriteLock(SRWLOCK* pSRWLock) : m_pSRWLock(pSRWLock)
	{
		ASSERT(pSRWLock);
#if 0
		AcquireSRWLockExclusive(pSRWLock);
#endif
	}

	inline ~WriteLock()
	{
#if 0
		ReleaseSRWLockExclusive(m_pSRWLock);
#endif
	}

	SRWLOCK* m_pSRWLock;
};

#if 0	// Windows 7

class LFCEXT TryReadLock
{
public:

	inline CTOR TryReadLock(SRWLOCK* pSRWLock) : m_pSRWLock(NULL)
	{
		ASSERT(pSRWLock);
		if (TryAcquireSRWLockShared(pSRWLock))
		{
			m_pSRWLock = pSRWLock;
		}
	}

	inline ~TryReadLock()
	{
		if (m_pSRWLock) ReleaseSRWLockShared(m_pSRWLock);
	}

	operator bool () const
	{
		return m_pSRWLock != NULL;
	}

	SRWLOCK* m_pSRWLock;
};

#endif

#elif AMIGA

class CriticalSection
{
public:
	CTOR CriticalSection();
	~CriticalSection();

	void Lock();
	void Unlock();
	bool Try();

protected:

//	uint8 m_private[46];	// sizeof SignalSemaphore

//	uint16 m_private[23];	// sizeof SignalSemaphore
//	uint16 reserved;	// align on 4 bytes

	uint32 m_private[12];	// sizeof SignalSemaphore+2
};

#elif __APPLE__

// TODO

class CriticalSection
{
public:
	void Lock()
	{
//		EnterCriticalSection(&m_sec);
	}
	
	void Unlock()
	{
//		LeaveCriticalSection(&m_sec);
	}
	
	void Init()
	{
//		InitializeCriticalSection(&m_sec);
	}
	
	void Term()
	{
//		DeleteCriticalSection(&m_sec);
	}

	bool Try()
	{
		return true;
//		return TryEnterCriticalSection(&m_sec)? true: false;
	}

//	CRITICAL_SECTION m_sec;
};

#else


// TODO

class CriticalSection
{
public:
	void Lock()
	{
//		EnterCriticalSection(&m_sec);
	}

	void Unlock()
	{
//		LeaveCriticalSection(&m_sec);
	}

	void Init()
	{
//		InitializeCriticalSection(&m_sec);
	}

	void Term()
	{
//		DeleteCriticalSection(&m_sec);
	}

	bool Try()
	{
		return true;
//		return TryEnterCriticalSection(&m_sec)? true: false;
	}

//	CRITICAL_SECTION m_sec;
};

#endif

class String;

}	// System

#include "Object.h"

namespace System
{

inline bool operator < (const FILETIME& x, const FILETIME& y)
{
	return CompareFileTime(&x, &y) < 0;
}

inline bool operator > (const FILETIME& x, const FILETIME& y)
{
	return CompareFileTime(&x, &y) > 0;
}

inline bool operator <= (const FILETIME& x, const FILETIME& y)
{
	return CompareFileTime(&x, &y) <= 0;
}

inline bool operator >= (const FILETIME& x, const FILETIME& y)
{
	return  CompareFileTime(&x, &y) >= 0;
}

inline bool operator == (const FILETIME& x, const FILETIME& y)
{
	return CompareFileTime(&x, &y) == 0;
}

inline bool operator != (const FILETIME& x, const FILETIME& y)
{
	return CompareFileTime(&x, &y) != 0;
}

class LFCEXT ValueType : public Object
{
public:
};

class LFCEXT MarshalByRefObject : public Object
{
public:
	void* m_serverObject;
	Object* m_serverInfo;
};

template<class T> interface IEquatable
{
	virtual bool Equals(T other) const = 0;
};

// base class for unary functions
template<class arg_t, class result_t>
class unary_function
{
public:
	typedef arg_t argument_type;
	typedef result_t result_type;
};

// base class for binary functions
template <class arg1_t, class arg2_t, class result_t>
class binary_function
{
public:
	typedef arg1_t first_argument_type;
	typedef arg2_t second_argument_type;
	typedef result_t result_type;
};

template<class T> struct hash : public unary_function<T, size_t>
{
	size_t operator() (const T& arg) const
	{
		return hash_value(arg);
	}
};

}

#include "Heap.h"	// TODO remove

#include "vector.h"
#include "list.h"
#include "map.h"
#include "unordered_map.h"

namespace System
{

template<class key_t, class value_t>
class key_value_pair
{
public:
	CTOR key_value_pair(const key_t& key_, const value_t& value_) :
	  key(key_), value(value_)
	{
	}

	key_t key;
	value_t value;
};

template<class key_t, class value_t>
class avl_tree
{
public:

	CTOR avl_tree() : _size(0)
	{
		avl_algo::init_header(&_header);
	}

	class node : public Object
	{
	public:

		node* parent_;
		node* left_;
		node* right_;
		int balance_;

		key_value_pair<key_t, value_t> item;
	};

	typedef node* node_ptr;
	typedef const node* const_node_ptr;

	//Define our own avltree_node_traits
	struct avltree_node_traits
	{
		typedef node* node_ptr;
		typedef const node* const_node_ptr;
		typedef int balance;

		static node_ptr get_parent(const_node_ptr n)       {  return n->parent_;   }
		static void set_parent(node_ptr n, node_ptr parent){  n->parent_ = parent; }
		static node_ptr get_left(const_node_ptr n)         {  return n->left_;     }
		static void set_left(node_ptr n, node_ptr left)    {  n->left_ = left;     }
		static node_ptr get_right(const_node_ptr n)        {  return n->right_;    }
		static void set_right(node_ptr n, node_ptr right)  {  n->right_ = right;   }
		static balance get_balance(const_node_ptr n)       {  return n->balance_;  }
		static void set_balance(node_ptr n, balance b)     {  n->balance_ = b;     }
		static balance negative()                          {  return -1; }
		static balance zero()                              {  return 0;  }
		static balance positive()                          {  return 1;  }
	};

#ifndef __LERSTAD__
	typedef boost::intrusive::avltree_algorithms<avltree_node_traits> avl_algo;
#endif

	template<class KeyType, class KeyNodePtrCompare>
		node_ptr find(const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
	{
		return avl_algo::find(&_header, key, comp);
	}

	/*
	void insert_lower_bound()
	{
		return avl_algo::insert_lower_bound(&header, key, comp);
	}
	*/

	template<class Disposer>
	static void clear_and_dispose(Disposer disposer)
	{
		avl_algo::clear_and_dispose(&_header, disposer);
		_size = 0;
	}

	void clear() throw()
	{
		avl_algo::init_header(&_header);
		_size = 0;
	}

	size_t size() const throw()
	{
		return _size;
	}

	bool empty() const throw()
	{
		return size == 0;
	}

private:

	node* _header;
	size_t _size;
};

template<class value_t>
class avl_set
{
public:

	CTOR avl_set() : _size(0)
	{
		avl_algo::init_header(&_header);
	}

	class node : public Object
	{
	public:

		node* parent_;
		node* left_;
		node* right_;
		int balance_;

		value_t item;
	};

	//Define our own avltree_node_traits
	struct avltree_node_traits
	{
	   typedef node* node_ptr;
	   typedef const node* const_node_ptr;
	   typedef int balance;

	   static node_ptr get_parent(const_node_ptr n)       {  return n->parent_;   }
	   static void set_parent(node_ptr n, node_ptr parent){  n->parent_ = parent; }
	   static node_ptr get_left(const_node_ptr n)         {  return n->left_;     }
	   static void set_left(node_ptr n, node_ptr left)    {  n->left_ = left;     }
	   static node_ptr get_right(const_node_ptr n)        {  return n->right_;    }
	   static void set_right(node_ptr n, node_ptr right)  {  n->right_ = right;   }
	   static balance get_balance(const_node_ptr n)       {  return n->balance_;  }
	   static void set_balance(node_ptr n, balance b)     {  n->balance_ = b;     }
	   static balance negative()                          {  return -1; }
	   static balance zero()                              {  return 0;  }
	   static balance positive()                          {  return 1;  }
	};

#ifndef __LERSTAD__
	typedef boost::intrusive::avltree_algorithms<avltree_node_traits> avl_algo;
#endif

	template<class Disposer>
	static void clear_and_dispose(Disposer disposer)
	{
		avl_algo::clear_and_dispose(&_header, disposer);
		_size = 0;
	}

	void clear() throw()
	{
		avl_algo::init_header(&_header);
		_size = 0;
	}

	size_t size() const throw()
	{
		return _size;
	}

	bool empty() const throw()
	{
		return size == 0;
	}

private:

	node* _header;
	size_t _size;
};

}

namespace System
{

//#include <queue>

template<class Ty, class Cont = list<Ty> > class queue
{
public:

	typedef Ty value_type;

	int size() const
	{
		return cont.size();
	}

	inline bool empty() const
	{
		return size() == 0;
	}

	value_type& front()
	{
		return cont.front();
	}

	value_type& back()
	{
		return cont.back();
	}

	void push(const value_type & value)
	{
		cont.push_back(value);
	}

	void pop()
	{
		cont.pop_front();
	}

	Cont cont;
};

inline size_t hash_value(Object* object)
{
	return object->GetHashCode();
}

/*
inline bool operator == (const Object& x, const Object& y)
{
	return x.Equals(&y);
}
*/

template<class T> class EnumFlags
{
public:

	typedef T enum_type;

	CTOR EnumFlags(T flags)
	{
		m_flags = flags;
	}

	/*
	EnumFlags(UINT flags)
	{
		m_flags = flags;
	}
	*/

	operator UINT () const
	{
		return m_flags;
	}

	/*
	operator T () const
	{
		return (T)m_flags;
	}
	*/

	bool operator == (EnumFlags<T> flags) const
	{
		return m_flags == flags.m_flags;
	}

	bool operator != (EnumFlags<T> flags) const
	{
		return m_flags != flags.m_flags;
	}

	bool operator ! () const
	{
		return m_flags == 0;
	}

	EnumFlags<T> operator | (T flag) const
	{
		return (T)(m_flags | flag);
	}

	EnumFlags<T>& operator |= (T flag)
	{
		m_flags |= flag;
		return *this;
	}

	EnumFlags<T> operator & (T flag) const
	{
		return (T)(m_flags & flag);
	}

	EnumFlags<T>& operator &= (T flag)
	{
		m_flags &= flag;
		return *this;
	}

	EnumFlags<T> operator ^ (T flag) const
	{
		return (T)(m_flags ^ flag);
	}

	EnumFlags<T>& operator ^= (T flag)
	{
		m_flags ^= flag;
		return *this;
	}

	UINT m_flags;
};

#define DECLARE_ENUM_OPERATORS(enum_type)	inline EnumFlags<enum_type> operator | (enum_type x, enum_type y)	\
														{	\
															EnumFlags<enum_type> z = x;	\
															z |= y;	\
															return z;	\
														}
}

namespace System
{

enum AttributeTarget
{
	AttributeTarget_Assembly = 0x1,
	AttributeTarget_Module = 0x2,
	AttributeTarget_Class = 0x4,
	AttributeTarget_Struct = 0x8,
	AttributeTarget_Interface = 0x10,
	AttributeTarget_Enum = 0x20,
	AttributeTarget_Method = 0x40,
	AttributeTarget_Constructor = 0x80,
	AttributeTarget_Parameter = 0x100,
};

DECLARE_ENUM_OPERATORS(AttributeTarget)

typedef EnumFlags<AttributeTarget> AttributeTargets;

class LFCEXT Attribute : public Object
{
public:
	CTOR Attribute();
};

__attrib__(AttributeUsageAttribute(AttributeTarget_Class))
class LFCEXT AttributeUsageAttribute : public Attribute
{
public:
	CTOR AttributeUsageAttribute(AttributeTargets validOn);

	AttributeTargets get_ValidOn() const
	{
		return m_validOn;
	}

private:

	AttributeTargets m_validOn;
};

}	// System

	/*
namespace System
{

LFCEXT void _AddRoots(void* pvobject, ClassType* pMostDerivedClass);

class StaticRootObject
{
public:
	CTOR StaticRootObject(void* address, ClassType* pType) : m_address(address), m_pType(pType)
	{
	}

	void* m_address;
	ClassType* m_pType;
};

template<class T> int addroot(T* p)
{
	_AddRoots(p, typeof(T)->GetClass());
	return 1;
}

template<class T> class __root
{
public:
	CTOR __root()
	{
		_AddRoots(&m_v, typeof(T)->GetClass());
	}

	CTOR __root(const T& init) : m_v(init)
	{
		_AddRoots(&m_v, typeof(T)->GetClass());
	}

	operator T& ()
	{
		return m_v;
	}

	T* operator -> ()
	{
		return &m_v;
	}

	T m_v;
};
}	// System
*/

namespace System
{

LFCEXT String toString(bool value);
LFCEXT String toString(char value);
LFCEXT String toString(wchar_t value);
LFCEXT String toString(signed char value);
LFCEXT String toString(unsigned char value);
LFCEXT String toString(short value);
LFCEXT String toString(unsigned short value);
LFCEXT String toString(int value);
LFCEXT String toString(unsigned int value);
LFCEXT String toString(int64 value);
LFCEXT String toString(uint64 value);
LFCEXT String toString(float value);
LFCEXT String toString(double value);
LFCEXT String toString(long double value);
LFCEXT String toString(Object* obj);
LFCEXT String toString(const String& str);
//LFCEXT String toString(const StringVariant& str);

LFCEXT int toInt(float value);
LFCEXT int toInt(double value);

LFCEXT float toFloat(int value);
LFCEXT float toFloat(double value);
LFCEXT float toFloat(String value);

LFCEXT double toDouble(int value);
LFCEXT double toDouble(float value);

LFCEXT bool ToBool(Object* obj);
LFCEXT int ToInt(Object* obj);
LFCEXT unsigned int ToUInt(Object* obj);
LFCEXT float ToFloat(Object* obj);
LFCEXT double ToDouble(Object* obj);

}

namespace System
{

union FloatBits
{
	uint32 bits;
	float value;
};

const FloatBits float_NegativeZero = {0x80000000};
const FloatBits float_One = {0x3f800000};
const FloatBits float_NegativeInfinity = {0xff800000};
const FloatBits float_PositiveInfinity = {0x7f800000};
const FloatBits float_NaN = {0x7fc00000};

union DoubleBits
{
	uint64 bits;
	double value;
};

const DoubleBits double_NegativeZero = {0x8000000000000000};
const DoubleBits double_One = {0x3ff0000000000000};
const DoubleBits double_NegativeInfinity = {0xfff0000000000000};
const DoubleBits double_PositiveInfinity = {0x7ff0000000000000};
const DoubleBits double_NaN = {0x7ff8000000000000};

}	// System

// TODO
#define constexpr	inline

#include "BoolObject.h"
#include "SByteObject.h"
#include "UByteObject.h"
#include "ShortObject.h"
#include "UShortObject.h"
#include "IntObject.h"
#include "UIntObject.h"
#include "Int64Object.h"
#include "UInt64Object.h"
#include "FloatObject.h"
#include "DoubleObject.h"

namespace System
{

template<class T> struct box_t
{
	typedef T type;
};

#ifndef __LERSTAD__

template<> class box_t<bool>
{
	typedef BoolObject type;
};

template<> class box_t<signed char>
{
	typedef SByteObject type;
};

template<> class box_t<unsigned char>
{
	typedef UByteObject type;
};

template<> class box_t<short>
{
	typedef ShortObject type;
};

template<> class box_t<unsigned short>
{
	typedef UShortObject type;
};

template<> class box_t<int>
{
	typedef IntObject type;
};

template<> class box_t<unsigned int>
{
	typedef UIntObject type;
};

template<> class box_t<long long>
{
	typedef Int64Object type;
};

template<> class box_t<unsigned long long>
{
	typedef UInt64Object type;
};

template<> class box_t<float>
{
	typedef FloatObject type;
};

template<> class box_t<double>
{
	typedef DoubleObject type;
};

template<> class box_t<long double>
{
	typedef DoubleObject type;
};

#endif

template<class T> size_t cstrlen(const T* cstr);

#ifndef __LERSTAD__

template<> inline size_t cstrlen(const char* cstr)
{
	return strlen(cstr);
}

template<> inline size_t cstrlen(const wchar_t* cstr)
{
	return wcslen(cstr);
}

template<> inline size_t cstrlen(const char32_t* cstr)
{
	size_t count = 0;
	while (cstr[count])
	{
		++count;
	}

	return count;
}

#endif

template<class T> class inner_ptr
{
public:
	T* ptr;	// NOTE: This must be the first declarator in the class

	CTOR inner_ptr() : ptr(nullptr), baseptr(nullptr)
	{
	}

	CTOR inner_ptr(T* const _ptr)
	{
		ptr = const_cast<T*>(ptr);
		baseptr = const_cast<T*>(ptr);
	}

	CTOR inner_ptr(void* const _baseptr, T* _ptr)
	{
		ptr = _ptr;
		baseptr = const_cast<void*>(_baseptr);
	}

	void set(void* const _baseptr, T* _ptr)
	{
		ptr = _ptr;
		baseptr = const_cast<void*>(_baseptr);
	}

	inner_ptr& operator = (const inner_ptr& other)
	{
		ptr = other.ptr;
		baseptr = other.baseptr;
		return *this;
	}

	operator T* const () const
	{
		return ptr;
	}

	void* const getbaseptr() const
	{
		return baseptr;
	}

private:

	void* baseptr;
};

// TODO

/*
Schema BMPFile(
			   _read2(0xBF),
				_read_int(width),
				_read_int(height),
				_read_int(biCompression),
				_if(biCompression == 0)

			   );
*/

class TypeLib;
class StringVariant;
template<class char_type> class CStringT;

class StringBuilderBase;
class StringBuilderTwo;

namespace IO
{
class Stream;
class TextWriter;
class TextReader;
class StreamWriter;
}

}	// System

#ifndef __LERSTAD__

	#undef new
	#include <string>
	#define new _new

#else

	namespace std
	{
		template<class T> class basic_string;

		typedef basic_string<char/*, char_traits<wchar_t>,	allocator<wchar_t>*/ > string;
		typedef basic_string<wchar_t/*, char_traits<wchar_t>,	allocator<wchar_t>*/ > wstring;
	}

#endif	// __LERSTAD__

#include "SystemString.h"
#include "StringVariant.h"

namespace System
{

class LFCEXT StringBuilder : public StringBuilderBase
{
private:

	friend class String;
	friend class StringVariant;
	friend class StringStream;
	friend class StringBuilderTwo;

	CTOR StringBuilder(StringIn str, const StringBuilderBase* prev) : m_str(str), m_prev(prev)
	{
		ASSERT(prev);
		m_wide = (str.GetCharSize() == 2) || prev->m_wide;
		m_totalLen = str.GetLength() + prev->GetLength();
	}

public:

	/*
	StringBuilder operator + (const String& other) const
	{
		return StringBuilder(other, this);
	}
	*/

	StringBuilder operator + (StringVariant other) const
	{
		return StringBuilder(other, this);
	}

#ifndef __LERSTAD__
	template<size_t size>
	StringBuilder operator + (const char other[size]) const
	{
		return StringBuilder(other, this);
	}

	template<size_t size> 
	StringBuilder operator + (const wchar_t other[size]) const
	{
		return StringBuilder(other, this);
	}
#endif

	virtual char* BuildString(char* pw) const override;
	virtual WCHAR* BuildString(WCHAR* pw) const override;

private:

	StringVariant m_str;
	const StringBuilderBase* m_prev;
};

inline StringBuilderBase::operator String () const
{
	return BuildString();
}

	/*
// Hack: should have been const char*
template<ULONG_PTR str> class _StringObject
{
public:

	operator StringObject* () const
	{
		static ImmutableString s_str((const char*)str);
		return &s_str;
	}
};

// Hack: should have been const wchar_t*
template<ULONG_PTR str> class _StringObjectW
{
public:

	static StringObject* get()
	{
		static ImmutableString s_str((const wchar_t*)str);
		return &s_str;
	}
};
*/

}	// System

#include "Exception.h"
#include "SystemException.h"

namespace System
{

class LFCEXT OverflowException : public SystemException
{
public:

	CTOR OverflowException(StringIn reason, Exception* innerException = nullptr) : SystemException(reason, innerException)
	{
	}

private:

	CTOR OverflowException(const OverflowException&);
	OverflowException& operator = (const OverflowException&);
};

class LFCEXT ApplicationException : public SystemException
{
public:

	CTOR ApplicationException(StringIn reason, Exception* innerException = nullptr) : SystemException(reason, innerException)
	{
	}

private:

	CTOR ApplicationException(const ApplicationException&);
	ApplicationException& operator = (const ApplicationException&);
};

class LFCEXT OutOfMemoryException : public SystemException
{
public:

	CTOR OutOfMemoryException(Exception* innerException = nullptr) : SystemException(L"Out of memory", innerException, E_OUTOFMEMORY)
	{
	}

	CTOR OutOfMemoryException(StringIn reason, Exception* innerException = nullptr) : SystemException(reason, innerException, E_OUTOFMEMORY)
	{
	}

private:

	CTOR OutOfMemoryException(const OutOfMemoryException&);
	OutOfMemoryException& operator = (const OutOfMemoryException&);
};

class LFCEXT NotImplementedException : public SystemException
{
public:

	CTOR NotImplementedException(Exception* innerException = nullptr) : SystemException(L"Not implemented", innerException, E_NOTIMPL)
	{
	}

	CTOR NotImplementedException(StringIn reason, Exception* innerException = nullptr) : SystemException(reason, innerException, E_NOTIMPL)
	{
	}
};

class LFCEXT ArgumentException : public SystemException
{
public:

	CTOR ArgumentException(Exception* innerException = nullptr) : SystemException(L"Argument invalid", innerException, E_INVALIDARG)
	{
	}

	CTOR ArgumentException(StringIn reason, Exception* innerException = nullptr, HRESULT hr = E_INVALIDARG) : SystemException(reason, innerException, hr)
	{
	}

private:

	CTOR ArgumentException(const ArgumentException&);
	ArgumentException& operator = (const ArgumentException&);
};

class LFCEXT ArgumentOutOfRangeException : public ArgumentException
{
public:
	CTOR ArgumentOutOfRangeException(Exception* innerException = nullptr) : ArgumentException(L"Argument out of range", innerException)
	{
	}

	CTOR ArgumentOutOfRangeException(StringIn reason, Exception* innerException = nullptr) : ArgumentException(reason, innerException)
	{
	}
};

class LFCEXT ArgumentNullException : public ArgumentException
{
public:
	CTOR ArgumentNullException(Exception* innerException = nullptr) : ArgumentException(L"Argument is null", innerException, E_POINTER)
	{
	}

	CTOR ArgumentNullException(StringIn reason, Exception* innerException = nullptr) : ArgumentException(reason, innerException, E_POINTER)
	{
	}
};

#ifndef __LERSTAD__

#define Stringify(x) #x
#define ArgumentNullException_(x) ArgumentNullException("Formal argument '" Stringify(x) "' is NULL in " __FUNCSIG__ )
#define VerifyArgumentNotNull(x)	do { if (x == nullptr) { raise(ArgumentNullException_(x)); } } while(0)

#else

#define VerifyArgumentNotNull(x)

#endif

namespace IO
{

class LFCEXT IOException : public SystemException
{
public:

	CTOR IOException(HRESULT hr = E_FAIL) : SystemException(L"IO Error", nullptr, hr)
	{
	}

	CTOR IOException(StringIn reason, HRESULT hr = E_FAIL) : SystemException(reason, nullptr, hr)
	{
	}
};

class LFCEXT FileNotFoundException : public IOException
{
public:

	CTOR FileNotFoundException() : IOException(L"File not found")
	{
	}

	CTOR FileNotFoundException(StringIn reason, HRESULT hr = E_FAIL) : IOException(reason, hr)
	{
	}

	String m_pathname;
};

class LFCEXT EndOfStreamException : public IOException
{
public:

	CTOR EndOfStreamException() : IOException(L"End of stream")
	{
	}
};

}	// IO

class LFCEXT SecurityException : public SystemException
{
public:

	CTOR SecurityException() : SystemException(L"Securiry exception")
	{
	}
};

template<class char_type>
char_type String::const_iterator<char_type>::operator * () const
{
	if (m_p == nullptr) raise(SystemException(L"referencing null pointer"));

	if ((unsigned int)m_offset >= m_p->GetLength()) raise(SystemException(L"offset < 0 or >= length"));

	switch (m_p->GetCharSize())
	{
	case 1: return (char_type)((char8*)m_p->GetData())[m_offset];
	case 2: return (char_type)((char16*)m_p->GetData())[m_offset];
	default: return (char_type)((char32_t*)m_p->GetData())[m_offset];
	}
}

template<class char_type>
char_type String::const_iterator<char_type>::operator [] (ptrdiff_t index) const
{
	if (m_p == nullptr)
	{
		raise(SystemException(L"referencing null pointer"));
	}

	ptrdiff_t offset = m_offset + index;

	if ((size_t)offset >= m_p->GetLength())
	{
		raise(SystemException(L"offset < 0 or >= length"));
	}

	switch (m_p->GetCharSize())
	{
	case 1: return (char_type)((char8*)m_p->GetData())[offset];
	case 2: return (char_type)((char16*)m_p->GetData())[offset];
	default: return (char_type)((char32_t*)m_p->GetData())[offset];
	}
}

class LFCEXT StringBuilderTwo : public StringBuilderBase
{
//private:
public:

//	friend class String;
//	friend class StringVariant;
//	friend class StringStream;
//	friend template<class char_type> class CStringT;

	CTOR StringBuilderTwo(StringIn str2, StringIn str1) : m_str2(str2), m_str1(str1)
	{
		m_wide = (str1.GetCharSize() == 2) || (str2.GetCharSize() == 2);
		m_totalLen = str1.GetLength() + str2.GetLength();
	}

public:

	StringBuilder operator + (const String& other) const
	{
		return StringBuilder(other, this);
	}

	StringBuilder operator + (const StringVariant& other) const
	{
		return StringBuilder(other, this);
	}

	StringBuilder operator + (const char* other) const
	{
		return StringBuilder(other, this);
	}

	StringBuilder operator + (const wchar_t* other) const
	{
		return StringBuilder(other, this);
	}

	StringBuilder operator + (char ch) const;
	StringBuilder operator + (wchar_t ch) const;

	virtual char* BuildString(char* pw) const override;
	virtual WCHAR* BuildString(WCHAR* pw) const override;

	friend StringBuilderTwo operator + (const char* cstr, const String& str);
	friend StringBuilderTwo operator + (const wchar_t* cstr, const String& str);
	friend StringBuilderTwo operator + (const char* cstr, const StringIn& str);
	friend StringBuilderTwo operator + (const wchar_t* cstr, const StringIn& str);

private:

	StringIn m_str1;
	StringIn m_str2;
};

inline StringBuilderTwo operator + (const char* cstr, const String& str)
{
	return StringBuilderTwo(str.m_stringObject, cstr);
}

inline StringBuilderTwo operator + (const wchar_t* cstr, const String& str)
{
	return StringBuilderTwo(str.m_stringObject, cstr);
}

inline StringBuilderTwo operator + (const char* cstr, const StringIn& str)
{
	return StringBuilderTwo(str, cstr);
}

inline StringBuilderTwo operator + (const wchar_t* cstr, const StringIn& str)
{
	return StringBuilderTwo(str, cstr);
}

template<class char_type>
inline StringBuilderTwo operator + (const char* cstr, const CStringT<char_type>& cstr2)
{
	return StringBuilderTwo(cstr2.c_str(), cstr);
}

template<class char_type>
inline StringBuilderTwo operator + (const wchar_t* cstr, const CStringT<char_type>& cstr2)
{
	return StringBuilderTwo(cstr2.c_str(), cstr);
}

template<class char_type>
inline StringBuilderTwo CStringT<char_type>::operator + (const char* cstr) const
{
	return StringBuilderTwo(cstr, c_str());
}

template<class char_type>
inline StringBuilderTwo CStringT<char_type>::operator + (const wchar_t* cstr) const
{
	return StringBuilderTwo(cstr, c_str());
}

/*
class LFCEXT StringBuilderTwoCh : public StringBuilderBase
{
private:

	friend class String;
	friend class StringVariant;
	friend class StringStream;

	CTOR StringBuilderTwoCh(char ch2, StringIn str1) : m_ch2(ch2), m_str1(str1)
	{
		m_wide = str1.GetCharSize() == 2;
		m_totalLen = str1.GetLength() + 1;
	}

	CTOR StringBuilderTwoCh(wchar_t ch2, StringIn str1) : m_ch2(ch2), m_str1(str1)
	{
		m_wide = true;
		m_totalLen = str1.GetLength() + 1;
	}

public:

	StringBuilder operator + (const String& other) const
	{
		return StringBuilder(other, this);
	}

	StringBuilder operator + (const StringVariant& other) const
	{
		return StringBuilder(other, this);
	}

	StringBuilder operator + (const char* other) const
	{
		return StringBuilder(other, this);
	}

	StringBuilder operator + (const wchar_t* other) const
	{
		return StringBuilder(other, this);
	}

	StringBuilder operator + (char ch) const;
	StringBuilder operator + (wchar_t ch) const;

	virtual char* BuildString(char* pw) const override;
	virtual WCHAR* BuildString(WCHAR* pw) const override;

	friend StringBuilderTwo operator + (const char* cstr, const String& str);
	friend StringBuilderTwo operator + (const wchar_t* cstr, const String& str);

private:

	StringIn m_str1;
	StringIn m_str2;
};
*/

inline bool operator == (const char* x, const String& y)
{
	return y == x;
}

inline bool operator != (const char* x, const String& y)
{
	return y != x;
}

inline bool operator == (const wchar_t* cstr, const String& str)
{
	return str == cstr;
}

inline bool operator == (const wchar_t* cstr, const StringVariant& str)
{
	return str == cstr;
}

inline bool operator == (const String& str, const String::_SubString& substr)
{
	return substr == str;
}

inline bool operator < (const char* x, const String& y)
{
	return y > x;
}

inline bool operator > (const char* x, const String& y)
{
	return y < x;
}

inline bool operator < (const wchar_t* x, const String& y)
{
	return y > x;
}

inline bool operator > (const wchar_t* x, const String& y)
{
	return y < x;
}

#ifndef __LERSTAD__
// specialization
template<>
class less<String> : public binary_function<String, String, bool>
{
public:
	bool operator () (const String& x, const String& y) const
	{
		return x < y;
	}

	bool operator () (const char* x, const String& y) const
	{
		return x < y;
	}

	bool operator () (const String& x, const char* y) const
	{
		return x < y;
	}

	bool operator () (const wchar_t* x, const String& y) const
	{
		return x < y;
	}

	bool operator () (const String& x, const wchar_t* y) const
	{
		return x < y;
	}
};
#endif

}

#include "Guid.h"

namespace System
{

template<class return_type>
interface IFunction0 : public IFunction
{
	virtual return_type Call() = 0;
};

template<class return_type, class arg0_type>
interface IFunction1 : public IFunction
{
	virtual return_type Call(arg0_type arg0) = 0;
};

template<class return_type, class arg0_type, class arg1_type>
interface IFunction2 : public IFunction
{
	virtual return_type Call(arg0_type arg0, arg1_type arg1) = 0;
};

template<class return_type, class arg0_type, class arg1_type, class arg2_type>
interface IFunction3 : public IFunction
{
	virtual return_type Call(arg0_type arg0, arg1_type arg1, arg2_type arg2) = 0;
};

class LFCEXT Event : public Object
{
public:

//	virtual const Type_Info& get_HandlerType() const = 0;
	virtual uint get_NumArgs() = 0;
	//virtual void InvokeHandler(const EventHandler& handler) = 0;

	virtual void Handle(const Variant& varg0, const Variant& varg1)
	{
		raise(Exception("not implemented"));
	}

	/*
	void Connect(const EventHandler& handler)
	{
		m_handlers.push_back(handler);
	}

	void Disconnect(const EventHandler& handler)
	{
		list<EventHandler>::iterator it = m_handlers.find(handler);
		ASSERT(it != m_handlers.end());
		m_handlers.erase(it);
	}

	list<EventHandler> m_handlers;
	*/
};

/*
class Function0
{
public:

	typedef void (*fun_type)();

	static void CallFun(IFunction* f)
	{
		static_cast<fun_type>(f)->Call(arg0);
	};
};
*/

template<class class_type, class arg0_type> class MemberFunction1 : public Object, public IFunction1<void, arg0_type>
{
public:

	typedef void (class_type::*memfun_type)(arg0_type);

#ifndef __LERSTAD__

	CTOR MemberFunction1(class_type* object, memfun_type memfun) :
		m_pObject(object),
		m_memfun(memfun)
	{
	}

		/*
	template<class h_arg0_type>	IFunction1<void, h_arg0_type>* Cv()
	{
		return new MemberFunction1<class_type, h_arg0_type>(m_pObject, memfun_type);
	}
	*/

	virtual uint get_NumArgs() override
	{
		return 1;
	}

	virtual void Call(arg0_type arg0) override
	{
		(m_pObject->*m_memfun)(arg0);
	}

	template<class h_arg0_type> static void CallFun(IFunction* f, h_arg0_type arg0)
	{
		static_cast<MemberFunction1*>(f)->Call(arg0);
	};

#endif

	class_type* m_pObject;
	memfun_type m_memfun;
};

template<class class_type, class arg0_type, class arg1_type> class MemberFunction2 : public Object, public IFunction2<void, arg0_type, arg1_type>
{
public:

	typedef void (class_type::*memfun_type)(arg0_type, arg1_type);

#ifndef __LERSTAD__

	CTOR MemberFunction2(class_type* object, memfun_type memfun) :
		m_pObject(object),
		m_memfun(memfun)
	{
	}

		/*
	template<class h_arg0_type>	IFunction1<void, h_arg0_type>* Cv()
	{
		return new MemberFunction1<class_type, h_arg0_type>(m_pObject, memfun_type);
	}
	*/

	virtual uint get_NumArgs() override
	{
		return 2;
	}

	virtual void Call(arg0_type arg0, arg1_type arg1) override
	{
		(m_pObject->*m_memfun)(arg0, arg1);
	}

	template<class h_arg0_type, class h_arg1_type> static void CallFun(IFunction* f, h_arg0_type arg0, h_arg1_type arg1)
	{
		static_cast<MemberFunction2*>(f)->Call(arg0, arg1);
	};

#endif

	class_type* m_pObject;
	memfun_type m_memfun;
};

template<class class_type, class arg0_type, class arg1_type, class arg2_type> class MemberFunction3 : public Object, public IFunction3<void, arg0_type, arg1_type, arg2_type>
{
public:

	typedef void (class_type::*memfun_type)(arg0_type, arg1_type, arg2_type);

#ifndef __LERSTAD__

	CTOR MemberFunction3(class_type* object, memfun_type memfun) :
		m_pObject(object),
		m_memfun(memfun)
	{
	}

		/*
	template<class h_arg0_type>	IFunction1<void, h_arg0_type>* Cv()
	{
		return new MemberFunction1<class_type, h_arg0_type>(m_pObject, memfun_type);
	}
	*/

	virtual uint get_NumArgs() override
	{
		return 3;
	}

	virtual void Call(arg0_type arg0, arg1_type arg1, arg2_type arg2) override
	{
		(m_pObject->*m_memfun)(arg0, arg1, arg2);
	}

	template<class h_arg0_type, class h_arg1_type> static void CallFun(IFunction* f, h_arg0_type arg0, h_arg1_type arg1, arg2_type arg2)
	{
		static_cast<MemberFunction3*>(f)->Call(arg0, arg1, arg2);
	};

#endif

	class_type* m_pObject;
	memfun_type m_memfun;
};

#ifndef __LERSTAD__

template<class class_type, class arg0_type> MemberFunction1<class_type, arg0_type>* EventHandler(class_type* p, void (class_type::*memfun)(arg0_type))
{
	return new MemberFunction1<class_type, arg0_type>(p, memfun);
}

template<class class_type, class arg0_type, class arg1_type> MemberFunction2<class_type, arg0_type, arg1_type>* EventHandler(class_type* p, void (class_type::*memfun)(arg0_type, arg1_type))
{
	return new MemberFunction2<class_type, arg0_type, arg1_type>(p, memfun);
}

template<class class_type, class arg0_type, class arg1_type, class arg2_type> MemberFunction2<class_type, arg0_type, arg1_type>* EventHandler(class_type* p, void (class_type::*memfun)(arg0_type, arg1_type, arg2_type))
{
	return new MemberFunction3<class_type, arg0_type, arg1_type, arg2_type>(p, memfun);
}

#endif

/*
class Fun
{
public:
	static void CallFun(IFunction* f)
	{
		static_cast<Function0*>(f)->Call(arg0, arg1, arg2);
	};
};
*/

class LFCEXT Event0 : public Event
{
public:

	typedef void (*fun_type)(IFunction* f);
	typedef void (*fun_type2)();

	class Handler
	{
	public:

		CTOR Handler(IFunction* f, fun_type fun) : m_f(f), m_fun(fun)
		{
		}

		CTOR Handler(fun_type2 fun2) : m_f(nullptr), m_fun2(fun2)
		{
		}

		void operator () ()
		{
			if (m_f)
				m_fun(m_f);
			else
				m_fun2();
		}

		IFunction* m_f;
		union
		{
			fun_type m_fun;
			fun_type2 m_fun2;
		};
	};

	void operator () ()
	{
#ifndef __LERSTAD__
		for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
		{
			Handler handler = *it;
			handler();
		}
#endif
	}

	static const uint numArgs = 0;

	virtual uint get_NumArgs() override
	{
		return 0;
	}

#ifndef __LERSTAD__
	template<class x>
	void Connect(typename x handler)
	{
		m_handlers.push_back(Handler(handler, &(handler->CallFun)));
	}
#endif

	void Add(void (*funptr)())
	{
		m_handlers.push_back(Handler(funptr));
	}

	void RemoveHandlers()
	{
		m_handlers.clear();
	}

	list<Handler>& get_Handlers()
	{
		return m_handlers;
	}

	list<Handler> m_handlers;
};

template<class arg0_type> class Event1 : public Event
{
public:

	typedef void (*fun_type)(IFunction* f, arg0_type);
	typedef void (*fun_type2)(arg0_type);

	class Handler
	{
	public:

		CTOR Handler(IFunction* f, fun_type fun) : m_f(f), m_fun(fun)
		{
		}

		CTOR Handler(fun_type2 fun2) : m_f(NULL), m_fun2(fun2)
		{
		}

		void operator () (arg0_type arg0)
		{
			if (m_f)
				m_fun(m_f, arg0);
			else
				m_fun2(arg0);
		}

		IFunction* m_f;
		union
		{
			fun_type m_fun;
			fun_type2 m_fun2;
		};
	};

	void operator () (arg0_type arg0)
	{
#ifndef __LERSTAD__
		for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
		{
			Handler& handler = *it;
			handler(arg0);
		}
#endif
	}

	static const uint numArgs = 1;

	virtual uint get_NumArgs() override
	{
		return 1;
	}

#ifndef __LERSTAD__

	template<class x>
	void Connect(typename x handler)
	{
		m_handlers.push_back(Handler(handler, &(handler->CallFun<arg0_type>)));
	}
#endif

	/*
	template<class arg0_type> static CallFun(IFunction* f, arg0_type arg0)
	{
		IFunction1
	}
	*/

	void Add(void (*funptr)(arg0_type))
	{
		m_handlers.push_back(Handler(funptr));
	}

	void RemoveHandlers()
	{
		m_handlers.clear();
	}

	list<Handler>& get_Handlers()
	{
		return m_handlers;
	}

	list<Handler> m_handlers;
};

template<class arg0_type, class arg1_type> class Event2 : public Event
{
public:

	CTOR Event2()
	{
	}

	typedef void (*fun_type)(IFunction* f, arg0_type, arg1_type);
	typedef void (*fun_type2)(arg0_type, arg1_type);

	class Handler
	{
	public:

		CTOR Handler(IFunction* f, fun_type fun) : m_f(f), m_fun(fun)
		{
		}

		CTOR Handler(fun_type2 fun2) : m_f(NULL), m_fun2(fun2)
		{
		}

		void operator () (arg0_type arg0, arg1_type arg1)
		{
			if (m_f)
				m_fun(m_f, arg0, arg1);
			else
				m_fun2(arg0, arg1);
		}

		IFunction* m_f;
		union
		{
			fun_type m_fun;
			fun_type2 m_fun2;
		};
	};

	void operator () (arg0_type arg0, arg1_type arg1)
	{
#ifndef __LERSTAD__
		for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
		{
			Handler& handler = *it;
			handler(arg0, arg1);
		}
#endif
	}

	virtual void Handle(const Variant& varg0, const Variant& varg1)
	{
		arg0_type arg0 = varg0;
		arg1_type arg1 = varg1;

		this->operator () (arg0, arg1);
	}

	static const uint numArgs = 2;

	virtual uint get_NumArgs() override
	{
		return 2;
	}

#ifndef __LERSTAD__
	template<class x>
	void Connect(typename x handler)
	{
		m_handlers.push_back(Handler(handler, &(handler->CallFun<arg0_type, arg1_type>)));
	}
#endif

	void Add(void (*funptr)(arg0_type, arg1_type))
	{
		m_handlers.push_back(Handler(funptr));
	}

	void RemoveHandlers()
	{
		m_handlers.clear();
	}

	list<Handler>& get_Handlers()
	{
		return m_handlers;
	}

	list<Handler> m_handlers;
};

template<class arg0_type, class arg1_type, class arg2_type> class Event3 : public Event
{
public:

	typedef void (*fun_type)(IFunction* f, arg0_type, arg1_type, arg2_type);

	class Handler
	{
	public:

		CTOR Handler(IFunction* f, fun_type fun) : m_f(f), m_fun(fun)
		{
		}

		IFunction* m_f;
		fun_type m_fun;
	};

#ifndef __LERSTAD__

	void operator () (arg0_type arg0, arg1_type arg1, arg2_type arg2)
	{
		for (auto it = m_handlers.cbegin(); it != m_handlers.cend(); ++it)
		{
			const Handler& handler = *it;
			handler.m_fun(handler.m_f, arg0, arg1, arg2);
		}
	}

	virtual uint get_NumArgs() override
	{
		return 3;
	}

	template<class x>
	void Connect(typename x handler)
	{
		m_handlers.push_back(Handler(handler, &(handler->CallFun<arg0_type, arg1_type, arg2_type>)));
	}

	/*
	void Connect(fun_type* handler)
	{
		m_handlers.push_back(handler);
	}
*/

#endif

	list<Handler> m_handlers;
};

template<class arg0_type, class arg1_type, class arg2_type, class arg3_type> class Event4 : public Event
{
public:

	typedef void (*fun_type)(IFunction* f, arg0_type, arg1_type, arg2_type, arg3_type);

	class Handler
	{
	public:

		CTOR Handler(IFunction* f, fun_type fun) : m_f(f), m_fun(fun)
		{
		}

		IFunction* m_f;
		fun_type m_fun;
	};

#ifndef __LERSTAD__

	void operator () (arg0_type arg0, arg1_type arg1, arg2_type arg2, arg3_type arg3)
	{
		for (auto it = m_handlers.cbegin(); it != m_handlers.cend(); ++it)
		{
			const Handler& handler = *it;
			handler.m_fun(handler.m_f, arg0, arg1, arg2, arg3);
		}
	}

	virtual uint get_NumArgs() override
	{
		return 4;
	}

	template<class x>
	void Connect(typename x handler)
	{
		m_handlers.push_back(Handler(handler, &(handler->CallFun<arg0_type, arg1_type, arg2_type, arg3_type>)));
	}

	/*
	void Connect(fun_type* handler)
	{
		m_handlers.push_back(handler);
	}
*/

#endif

	list<Handler> m_handlers;
};

template<class arg0_type, class arg1_type, class arg2_type, class arg3_type, class arg4_type> class Event5 : public Event
{
public:

	typedef void (*fun_type)(IFunction* f, arg0_type, arg1_type, arg2_type, arg3_type, arg4_type);

	class Handler
	{
	public:

		CTOR Handler(IFunction* f, fun_type fun) : m_f(f), m_fun(fun)
		{
		}

		IFunction* m_f;
		fun_type m_fun;
	};

#ifndef __LERSTAD__

	void operator () (arg0_type arg0, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4)
	{
		for (auto it = m_handlers.cbegin(); it != m_handlers.cend(); ++it)
		{
			const Handler& handler = *it;
			handler.m_fun(handler.m_f, arg0, arg1, arg2, arg3, arg4);
		}
	}

	virtual uint get_NumArgs() override
	{
		return 5;
	}

	template<class x>
	void Connect(typename x handler)
	{
		m_handlers.push_back(Handler(handler, &(handler->CallFun<arg0_type, arg1_type, arg2_type, arg3_type, arg4_type>)));
	}

	/*
	void Connect(fun_type* handler)
	{
		m_handlers.push_back(handler);
	}
*/

#endif

	list<Handler> m_handlers;
};

template<class T> class _Ptr
{
public:

	typedef T ptrtype;

	inline CTOR _Ptr() : m_p(nullptr)
	{
	}

	inline CTOR _Ptr(T* p) : m_p(p)
	{
		if (p) IncRef(p);
	}

	template<class T2>
	inline CTOR _Ptr(const _Ptr<T2>& other) : m_p(other.m_p)
	{
		if (m_p) IncRef(m_p);
	}

	inline CTOR _Ptr(const _Ptr& other) : m_p(other.m_p)
	{
		if (m_p) IncRef(m_p);
	}

#ifndef __LERSTAD__
	template<class T2>
	inline CTOR _Ptr(_Ptr<T2>&& other) : m_p(other.m_p)
	{
		other.m_p = nullptr;
	}

	inline CTOR _Ptr(_Ptr&& other) : m_p(other.m_p)
	{
		other.m_p = nullptr;
	}
#endif

	inline ~_Ptr()
	{
		if (m_p)
		{
			DecRef(m_p);
			m_p = nullptr;
		}
	}

	inline T* operator -> ()
	{
		if (m_p == nullptr)
		{
			raise(SystemException("nullptr"));
		}
		return m_p;
	}

	inline const T* operator -> () const
	{
		if (m_p == nullptr)
		{
			raise(SystemException("nullptr"));
		}
		return m_p;
	}

	template<class T2>
	_Ptr& operator = (const _Ptr<T2>& other)
	{
		if (other.m_p) IncRef(other.m_p);
		if (m_p) DecRef(m_p);
		m_p = other.m_p;

		return *this;
	}

#ifndef __LERSTAD__
	template<class T2>
	_Ptr& operator = (_Ptr<T2>&& other)
	{
		if (m_p) DecRef(m_p);
		m_p = other.m_p;
		other.m_p = nullptr;

		return *this;
	}

#endif

	_Ptr& operator = (T* p)
	{
		if (p) IncRef(p);
		if (m_p) DecRef(m_p);
		m_p = p;

		return *this;
	}

	template<class T2>
	inline bool operator == (const _Ptr<T2>& other) const
	{
		return m_p == other.m_p;
	}

	template<class T2>
	inline bool operator != (const _Ptr<T2>& other) const
	{
		return m_p != other.m_p;
	}

	inline bool operator ! () const throw()
	{
		return m_p == nullptr;
	}

	inline T* ptr() const throw()
	{
		return m_p;
	}

	inline operator T& ()
	{
		return *m_p;
	}

	inline operator T* () throw()
	{
		return m_p;
	}

	T* m_p;
};

interface IObjectCollection
{
	virtual const Type_Info& GetItemType() const = 0;
	virtual size_t GetCount() = 0;
	virtual void Clear() = 0;
	virtual void AddObject(Object* element) = 0;
	virtual Object* get_ObjectItem(size_t index) = 0;
};

template<class TYPE> interface ICollection : public IObjectCollection
{
	virtual void Add(TYPE element) = 0;
};

/*
#ifndef __LERSTAD__
interface ICollection<Object*> : public IObjectCollection
{
	virtual void Add(Object* element) = 0;
};
#endif
*/

template<class TYPE> interface IVector : public ICollection<TYPE>
{
public:
	virtual TYPE get_Item(size_t index) = 0;
	virtual void set_Item(size_t index, TYPE element) = 0;
};

template<class TYPE> interface IEnumerator
{
public:
	virtual bool MoveNext() = 0;
	virtual TYPE get_Current() = 0;
};

template<class TYPE> interface IEnumerable
{
public:
	virtual IEnumerator<TYPE>* GetEnumerator() = 0;
};

template<class TYPE, class ARRAY_TYPE = vector<TYPE> > class Vector : public Object, public IVector<TYPE>
{
public:
	CTOR Vector()
	{
	}

	/*
	explicit CTOR Vector(ARRAY_TYPE& items) : m_items(items)
	{
	}
	*/

	// when ARRAY_TYPE is reference
	explicit CTOR Vector(ARRAY_TYPE items) : m_items(items)
	{
	}

	virtual const Type_Info& GetItemType() const
	{
		return typeid(TYPE);
	}

	virtual size_t GetCount()
	{
		return m_items.size();
	}

	virtual void Clear()
	{
		m_items.clear();
	}

	virtual TYPE get_Item(size_t index)
	{
		if (index < m_items.size())
			return m_items[index];
		else
			raise(ArgumentOutOfRangeException());
	}

	virtual void set_Item(size_t index, TYPE element)
	{
		if (index < m_items.size())
			m_items[index] = element;
		else
			raise(ArgumentOutOfRangeException());
	}

	virtual Object* get_ObjectItem(size_t index)
	{
		if (index < m_items.size())
			return m_items[index];
		else
			raise(ArgumentOutOfRangeException());
	}

	virtual void Add(TYPE element)
	{
		m_items.push_back(element);
	}

	virtual void AddObject(Object* object)
	{
#ifndef __LERSTAD__
		Add(unbox_cast<TYPE>(object));
#endif
	}

	ARRAY_TYPE m_items;
};

template<class TYPE, class LIST_TYPE = list<TYPE> > class List : public Object, public IEnumerable<TYPE>
{
public:

	class Enumerator : public Object, public IEnumerator<TYPE>
	{
	public:

#ifndef __LERSTAD__
		CTOR Enumerator(List* pList) : m_pList(pList)
		{
			m_it = pList->m_list.end();
		}
#endif

		virtual bool MoveNext() override
		{
			++m_it;
			return m_it != m_pList->m_list.end(); 
		}

		virtual TYPE get_Current() override
		{
			if (m_it == m_pList->m_list.end())
			{
				raise(Exception("Not at valid position"));
			}
			return *m_it;
		}

		/*
		virtual bool Any()
		{
			return m_it != m_pList->m_list.end(); 
		}
		*/

		/*
		virtual TYPE MoveNext()
		{
			return *m_it++;
		}
		*/

#ifndef __LERSTAD__
		typename LIST_TYPE::iterator m_it;
		List* m_pList;
#else
		Object* m_it;
		Object* m_pList;
#endif
	};

	CTOR List()
	{
	}

	CTOR List(IEnumerator<TYPE>* enumerator)
	{
		VerifyArgumentNotNull(enumerator);

		while (enumerator->MoveNext())
		{
			Add(enumerator->get_Current());
		}

		/*
		for (; enumerator->Any(); enumerator->Next())
		{
			Add(enumerator->get_Current());
		}
		*/
	}

	virtual void Add(TYPE newItem)
	{
		m_list.push_back(newItem);
	}

	virtual size_t GetCount()
	{
		return m_list.size();
	}

	virtual uint64 GetCount64() //override
	{
		return m_list.size();
	}

	virtual String ToString() override
	{
		String str;
		for (typename LIST_TYPE::iterator it = m_list.begin(); it != m_list.end(); ++it)
		{
			if (it != m_list.begin()) str += "\n";
			str += toString(*it);
		}

		return str;
	}

	virtual IEnumerator<TYPE>* GetEnumerator()
	{
		return new Enumerator(this);
	}

	virtual TYPE Find(size_t index)
	{
#ifndef __LERSTAD__
		for (LIST_TYPE::iterator it = m_list.begin(); it != m_list.end(); ++it)
		{
			if (index == 0)
			{
				return *it;
			}
			--index;
		}
#endif
		raise(ArgumentOutOfRangeException());
	}

	LIST_TYPE m_list;
};

enum Endianess
{
	Endianess_Little,
	Endianess_Big
};

template<class T> inline void IncRef(T* p)
{
	p->IncRef();
}

template<class T> inline void DecRef(T* p)
{
	p->DecRef();
}

class Formatter : public Object
{
public:
};

class bitfield
{
public:
	CTOR bitfield(uint value, uint nbits) : m_value(value), m_nbits(nbits)
	{
	}

	uint m_value;
	uint m_nbits;
};

class bitfield64
{
public:
	CTOR bitfield64(uint64 value, uint nbits) : m_value(value), m_nbits(nbits)
	{
	}

	uint64 m_value;
	uint m_nbits;
};

template<class T>
class TypedFormatter : public Formatter
{
public:
	virtual void Write(IO::TextWriter& stream, const T& obj) abstract;
};

#ifndef __LERSTAD__
template<class T>
class TypedArrayFormatter : public Formatter
{
public:
	virtual void Write(IO::TextWriter& stream, const T* obj, size_t count) abstract;
};
#endif

LFCEXT IO::TextWriter& PrintValue(IO::TextWriter& stream, Type* pType, byte* p, StringIn sep);
LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& stream, const FILETIME& filetime);
LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& stream, const SYSTEMTIME& filetime);

namespace IO
{

enum SeekOrigin
{
	STREAM_SEEK_SET	= 0,
	STREAM_SEEK_CUR	= 1,
	STREAM_SEEK_END	= 2,

	SeekOrigin_Set	= 0,
	SeekOrigin_Start = 0,
	SeekOrigin_Current = 1,
	SeekOrigin_End	= 2
};

union value8_t
{
	bool8 boolVal;
	char charVal;
	sbyte sbyteVal;
	ubyte byteVal;
	ubyte ubyteVal;
};

union value16_t
{
	int16 intVal;
	uint16 uintVal;
	char16_t charVal;
};

union value32_t
{
	int32 intVal;
	uint32 uintVal;
	float floatVal;
	char32_t charVal;
};

union value64_t
{
	int64 intVal;
	uint64 uintVal;
	double doubleVal;
};

class LFCEXT Fmt
{
public:

	CTOR Fmt(StringIn fmt) : m_fmt(fmt)
	{
	}

	Fmt& operator << (bool value);

	Fmt& operator << (char value);
	Fmt& operator << (signed char value);
	Fmt& operator << (unsigned char value);

	Fmt& operator << (wchar_t value);

	Fmt& operator << (short value);
	Fmt& operator << (unsigned short value);

	Fmt& operator << (int value)
	{
		m_types.push_back(8);
		value32_t val;
		val.intVal = value;
		m_values32.push_back(val);
		return *this;
	}

	Fmt& operator << (unsigned int value)
	{
		m_types.push_back(9);

		value32_t val;
		val.intVal = value;
		m_values32.push_back(val);
		return *this;
	}

	Fmt& operator << (long value);
	Fmt& operator << (unsigned long value);

	Fmt& operator << (long long value);
	Fmt& operator << (unsigned long long value);

	Fmt& operator << (float value);
	Fmt& operator << (double value);
	Fmt& operator << (long double value);

#if 0
	Fmt& operator << (__int128 value);
#endif

	Fmt& operator << (String value)
	{
		m_types.push_back(16);
		m_strvalues.push_back(value);
		return *this;
	}

	String get_fmt() const
	{
		return m_fmt;
	}

	void set_fmt(StringIn fmt)
	{
		m_fmt = fmt;
	}

	LFCEXT friend IO::TextWriter& operator << (IO::TextWriter& stream, const Fmt& fmt);

protected:

	String m_fmt;

	vector<ubyte> m_types;
//	vector<value8_t> m_values8;
//	vector<value16_t> m_values16;
	vector<value32_t> m_values32;
	vector<value64_t> m_values64;
	vector<const char*> m_cstrvalues;
	vector<const wchar_t*> m_cstrwvalues;
	vector<String> m_strvalues;
};

/*
template<class T> class ClassFormatter : public TypedFormatter<T>
{
public:

	CTOR ClassFormatter(

	virtual void Write(Stream& stream, const T& obj)
	{
		stream->Write(&obj, sizeof(T));
	}
};
*/

namespace BinaryFormatters
{

template<class T> class BinaryFormatter : public TypedFormatter<T>
{
public:
	virtual void Write(Stream& stream, const T& obj)
	{
		ASSERT(0);
		//stream->Write(&obj, sizeof(T));
	}

	virtual void Write(Stream& stream, const char* cstr)
	{
		//stream->Write(&obj, sizeof(T));
	}
};

}

namespace TextFormatters
{
}

class BitSet
{
public:

	/*
	BitSet& operator << (bool bit)
	{
		return *this;
	}
	*/

};

/*
class IntegerNumberBase
{
};

template<int bits> class IntegerNumber : public IntegerNumberBase
{
public:
	int m_value;
};

template<int bits> class LargeIntegerNumber
{
public:
	__int64 m_value;
};
*/

/*
template<class T>
class SingleListNode
{
public:

#ifndef __LERSTAD__
	unsigned int Length() const
	{
		unsigned int length = 0;
		SingleListNode* p = this;
		while (p)
		{
			++length;
			p = p->m_next;
		}

		return length;
	}

	SingleListNode* & Next()
	{
		return m_next;
	}

private:

	SingleListNode* m_next;
	T m_item;
#endif
};
*/

/*
template<class T>
class SingleList
{
public:
	SingleListNode<T>* m_head;

	SingleList* Prepend(SingleListNode<T>* node)
	{
		
	}
};
*/

//template<class T> inline Stream& write(Stream& stream, T item)

#if 0
template<class T> inline Stream& WriteToStream(Stream& stream, const T& item)
{
	Type* pType = typeid(item).GetType();

#if 0
	switch (pType->get_Kind())
	{
		case type_class:
		{
			ClassType* pClassType = pType->AsClass();

			stream << pClassType->get_QName() << "\n";
			stream << "{\n";

			for (size_t i = 0; i < pClassType->m_pScope->m_orderedDecls.size(); i++)
			{
				CDeclarator* decl = pClassType->m_pScope->m_orderedDecls[i];

				stream << /*decl->get_Type()->get_QName() <<*/  decl->get_Name();
				stream << " = ";

				int offset = decl->m_offset;
				const void* p = (const byte*)&item + offset;

				switch (decl->get_Type()->get_Kind())
				{
				case type_bool:
				case type_char:
				case type_wchar:
				case type_signed_char:
				case type_unsigned_char:
				case type_short_int:
				case type_unsigned_short_int:
				case type_int:
				case type_unsigned_int:
				case type_long_int:
				case type_unsigned_long_int:
				case type_float:
				case type_double:
					{
#ifndef __LERSTAD__
						PrimitiveType* pPrimType = static_cast<PrimitiveType*>(decl->get_Type());
#endif
						switch (decl->get_Type()->get_Kind())
						{
							case type_bool:
								stream << *(bool*)p;
								break;

							case type_char:
								stream << *(char*)p;
								break;

							case type_wchar:
								stream << *(wchar_t*)p;
								break;

							case type_signed_char:
								stream << *(signed char*)p;
								break;

							case type_unsigned_char:
								stream << *(unsigned char*)p;
								break;

							case type_short_int:
								stream << *(short*)p;
								break;

							case type_unsigned_short_int:
								stream << *(unsigned short*)p;
								break;

							case type_int:
								stream << *(int*)p;
								break;

							case type_unsigned_int:
								stream << *(unsigned int*)p;
								break;

							case type_long_int:
								stream << *(long*)p;
								break;

							case type_unsigned_long_int:
								stream << *(unsigned long*)p;
								break;

							case type_float:
								stream << *(float*)p;
								break;

							case type_double:
								stream << *(double*)p;
								break;
						}
					}
					break;

				case type_pointer:
					{
					}
					break;

				case type_class:
					break;
				}

				stream << ";\n";
			}
			stream << "};\n";
		}
		break;

	case type_enum:
		{
		}
		break;
	}
#endif
	return stream;

	/*
	const Type_Info& typ = typeid(T);
	if (typ.GetType() && typ.GetType()->GetClass())
	{
		stream << "<write(" << typ.GetType()->AsClass()->get_QName() << ")>";
	}
	else
	{
		stream << "<write(" << typ.raw_name() << ")>";
	}
	*/
	return stream;
}
#endif

class LFCEXT FileTime
{
public:

	FILETIME m_ft;

	operator FILETIME () const
	{
		return m_ft;
	}

	static FILETIME Now();
};

class LFCEXT File
{
public:

	typedef uint64 filesize_t;

	static bool Exists(StringIn filename);
	static FILETIME GetCreationTime(StringIn filename);
	static FILETIME GetLastAccessTime(StringIn filename);
	static FILETIME GetLastModifiedTime(StringIn filename);
	static filesize_t GetSize(StringIn filename);
	static filesize_t GetCompressedSize(StringIn filename);

	static void Touch(StringIn filename, FILETIME fileTime);

private:
	CTOR File();
};

class LFCEXT Path
{
public:

	static String Combine(StringIn path1, StringIn path2);
	static String Combine(StringIn path1, StringIn path2, StringIn path3);
	static String Combine(StringIn path1, StringIn path2, StringIn path3, StringIn path4);
	static String Combine(const vector<String>& paths);
	static String GetFullPath(StringIn path);
	static String GetDirectoryName(StringIn path);
	static String GetPathNameWithoutExtension(StringIn path);
	static String GetFileName(StringIn path);
	static String GetFileNameWithoutExtension(StringIn path);
	static String GetExtension(StringIn path);
	static bool HasExtension(StringIn path);
	static String ChangeExtension(StringIn path, StringIn extension);
	static String GetPathRoot(StringIn path);
	static bool IsPathRooted(StringIn path);

	static char get_DirectorySeparatorChar()
	{
#if _WIN32
		return '\\';
#else
		return '/';
#endif
	}

private:
	CTOR Path();
};

class LFCEXT Stream : public Object
{
public:

	CTOR Stream();
	virtual ~Stream();

	virtual uint64 Seek(int64 move, SeekOrigin origin) abstract;
	virtual size_t Read(void* pv, size_t len) abstract;
	virtual size_t Write(const void* pv, size_t len) abstract;

	virtual uint64 GetSize();
	virtual size_t ReadChars(char* p, size_t len);
	virtual size_t ReadChars(wchar_t* p, size_t len);
	virtual size_t WriteChars(const char* p, size_t len);
	virtual size_t WriteChars(const wchar_t* p, size_t len);
	virtual size_t _WriteChars(const char* p, size_t len);
	virtual size_t _WriteChars(const wchar_t* p, size_t len);
	virtual void Flush()
	{
	}

	virtual uint64 GetPosition()
	{
		return Seek(0, SeekOrigin_Current);
	}

	virtual Stream* Clone()
	{
		raise(Exception("Clone not implemented"));
		return NULL;
	}

	virtual bool CanSeek()
	{
		return false;
	}

	virtual bool CanRead()
	{
		return false;
	}

	virtual bool CanWrite()
	{
		return false;
	}

	virtual String GetFilename()
	{
		return nullptr;
	}

	virtual uint32 GetSize32() throw (SystemException*);

	virtual bool Close()
	{
		return true;
	}

	uint state() const
	{
		return m_state;
	}

	uint m_state;

	// Write

	Stream& operator << (sbyte ch);
	Stream& operator << (ubyte ch);

	Stream& operator << (const array<sbyte>& data);
	Stream& operator << (const array<ubyte>& data);

	Stream& operator << (const vector<sbyte>& data);
	Stream& operator << (const vector<ubyte>& data);

	// Read

	Stream& operator >> (sbyte& ch);
	Stream& operator >> (ubyte& ch);

	/*
	vector<ubyte> Read(size_t nbytes)
	{
		vector<ubyte> v;
		v.resize(nbytes);
		Read(v.GetData(), nbytes);
		return v;
	}
	*/

#ifndef __LERSTAD__
	template<class T, int size> Stream& operator << (const T (&items)[size])
	{
#ifndef __LERSTAD__
//		Stream stream2(*this);
#endif

		ASSERT(0);

#if 0
		const Type_Info& type = typeid(T[]);
		const char* raw_name = type.raw_name();

		TypedArrayFormatter<T>* pFormatter = dynamic_cast<TypedArrayFormatter<T>*>(m_streamObject->m_formatters.find(raw_name)->second);
		if (pFormatter)
		{
			pFormatter->Write(stream2, items, size);
		}
		else
		{
		}
#endif
		return *this;
	}
#endif

	template<class T> Stream& operator << (const T& item)
	{
#ifndef __LERSTAD__
		Stream stream2(*this);
#endif

		const Type_Info& type = typeid(T);
		const char* raw_name = type.raw_name();

		/*
		TypedFormatter<T>* pFormatter = dynamic_cast<TypedFormatter<T>*>(m_streamObject->m_formatters.find(raw_name)->second);
		if (pFormatter)
		{
			pFormatter->Write(stream2, item);
		}
		else
		*/
		{
		//	WriteToStream(stream2, const_cast<T&>(item));
			WriteToStream(stream2, item);
		}

		return *this;
	}

	template<class T> Stream& operator >> (T& item)
	{
#ifndef __LERSTAD__
		Stream stream2(*this);
#endif

		/*
		const Type_Info& type = typeid(T);
		const char* raw_name = type.raw_name();

		TypedFormatter<T>* pFormatter = dynamic_cast<TypedFormatter<T>*>(m_streamObject->m_formatters.find(raw_name)->second);
		if (pFormatter)
		{
			pFormatter->Read(stream2, item);
		}
		else
		*/
		{
			ReadFromStream(stream2, item);
		}

		return *this;
	}

	inline size_t IncRef()
	{
		return InterlockedIncrement(&m_refcount);
	}

	size_t DecRef();

	class Position
	{
	private:

		CTOR Position(Stream& stream) : m_stream(stream)
		{
		}

	public:

		friend class Stream;

		Position& operator = (int64 offset)
		{
			if (offset < 0)
			{
				raise(IOException("Negative seek"));
			}

			m_stream.Seek(offset, SeekOrigin_Set);
			return *this;
		}

		Position& operator ++ ()	// prefix
		{
			m_stream.Seek(1, SeekOrigin_Current);
			return *this;
		}

		Position& operator -- ()	// prefix
		{
			m_stream.Seek(-1, SeekOrigin_Current);
			return *this;
		}

		uint64 operator ++ (int)	// postfix
		{
			return m_stream.Seek(1, SeekOrigin_Current)-1;
		}

		uint64 operator -- (int)	// postfix
		{
			return m_stream.Seek(-1, SeekOrigin_Current)+1;
		}

		Position& operator += (int64 offset)
		{
			m_stream.Seek(offset, SeekOrigin_Current);
			return *this;
		}

		Position& operator -= (int64 offset)
		{
			m_stream.Seek(-offset, SeekOrigin_Current);
			return *this;
		}

		int64 operator + (int64 offset) const
		{
			return m_stream.GetPosition() + offset;
		}

		int64 operator - (int64 offset) const
		{
			return m_stream.GetPosition() - offset;
		}

		operator uint64 () const
		{
			return m_stream.GetPosition();
		}

		Stream& m_stream;

	private:

		CTOR Position(const Position&);
	};

	Position position;
	size_t m_refcount;

private:

	CTOR Stream(const Stream&);
};

}	// IO
}	// System

#include "CStdFile.h"

namespace System
{
namespace IO
{

LFCEXT Stream& operator << (Stream& stream, Fmt& fmt);

class LFCEXT Writer : public Object
{
public:
	CTOR Writer() : m_refcount(0)
	{
	}

	virtual ~Writer()
	{
		VERIFY(m_refcount == 0);
	}

	inline size_t IncRef()
	{
		return InterlockedIncrement(&m_refcount);
	}

	size_t DecRef()
	{
		ASSERT(m_refcount > 0);
		size_t refcount = InterlockedDecrement(&m_refcount);
		if (refcount == 0)
		{
			this->~Writer();
		}
		return refcount;
	}

	virtual bool IsNull() const
	{
		return false;
	}

	virtual void Write(bool bit) = 0;
	virtual void Write(char ch) = 0;
	virtual void Write(wchar_t ch) = 0;
#if _HAS_CHAR16_T_LANGUAGE_SUPPORT
	virtual void Write(char16_t ch) = 0;
	virtual void Write(char32_t ch) = 0;
#endif
	virtual void Write(signed char value) = 0;
	virtual void Write(unsigned char value) = 0;
	virtual void Write(short value) = 0;
	virtual void Write(unsigned short value) = 0;
	virtual void Write(int value) = 0;
	virtual void Write(unsigned int value) = 0;
	virtual void Write(long value) = 0;
	virtual void Write(unsigned long value) = 0;
	virtual void Write(long long value) = 0;
	virtual void Write(unsigned long long value) = 0;
	virtual void Write(float value) = 0;
	virtual void Write(double value) = 0;
	virtual void Write(long double value)
	{
		return Write((double)value);
	}

private:

	size_t m_refcount;
};

LFCEXT inline Writer& operator << (Writer& writer, bool bit)
{
	writer.Write(bit);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, char ch)
{
	writer.Write(ch);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, wchar_t ch)
{
	writer.Write(ch);
	return writer;
}

#if _HAS_CHAR16_T_LANGUAGE_SUPPORT

LFCEXT inline Writer& operator << (Writer& writer, char16_t ch)
{
	writer.Write(ch);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, char32_t ch)
{
	writer.Write(ch);
	return writer;
}

#endif

LFCEXT inline Writer& operator << (Writer& writer, signed char number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, unsigned char number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, short number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, unsigned short number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, int number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, unsigned int number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, long number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, unsigned long number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, int64 number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, uint64 number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, float number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, double number)
{
	writer.Write(number);
	return writer;
}

LFCEXT inline Writer& operator << (Writer& writer, long double number)
{
	writer.Write(number);
	return writer;
}

class LFCEXT TextWriter : public Writer
{
public:

	CTOR TextWriter();

	virtual uint64 GetPosition()
	{
		return 0;
	}

	virtual size_t WriteCStr(const char* str)
	{
		return WriteChars(str, strlen(str));
	}

	virtual size_t WriteCStr(const wchar_t* str)
	{
		return WriteChars(str, wcslen(str));
	}

	virtual void Write(bool bit) override;
	virtual void Write(char ch) override;
	virtual void Write(wchar_t ch) override;
	virtual void Write(signed char value) override;
	virtual void Write(unsigned char value) override;
	virtual void Write(short value) override;
	virtual void Write(unsigned short value) override;
	virtual void Write(int value) override;
	virtual void Write(unsigned int value) override;
	virtual void Write(long value) override;
	virtual void Write(unsigned long value) override;
	virtual void Write(int64 value) override;
	virtual void Write(uint64 value) override;
	virtual void Write(float value) override;
	virtual void Write(double value) override;
//	virtual void Write(long double value) override;

	virtual size_t WriteChars(const char8* p, size_t len) abstract;
	virtual size_t WriteChars(const char16* p, size_t len) abstract;
	virtual size_t WriteChars(const char32_t* p, size_t len);

	virtual void OnWritten(size_t len)
	{
	}

	void setbase(int base);
	int getbase() const
	{
		return m_base;
	}

	String m_true;
	String m_false;
	int m_base;
};

inline TextWriter& operator << (TextWriter& writer, TextWriter& (*pfn)(TextWriter& writer))
{
	return pfn(writer);
}

#ifndef __LERSTAD__

template<class arg0_type>
TextWriter& operator << (TextWriter& writer, TextWriter& (*pfn)(TextWriter& writer, arg0_type arg0))
{
	return pfn(writer, arg0);
}

template<class arg0_type, class arg1_type>
TextWriter& operator << (TextWriter& writer, TextWriter& (*pfn)(TextWriter& writer, arg0_type arg0, arg1_type arg1))
{
	return pfn(writer, arg0, arg1);
}

template<class arg0_type, class arg1_type, class arg2_type>
TextWriter& operator << (TextWriter& writer, TextWriter& (*pfn)(TextWriter& writer, arg0_type arg0, arg1_type arg1, arg2_type arg2))
{
	return pfn(writer, arg0, arg1, arg2);
}

template<class data_type>
TextWriter& WriteToStream(TextWriter& writer, const data_type& item)
{
	Type* pType = typeid(data_type);
	if (pType)
	{
		switch (pType->get_Kind())
		{
		case type_enum:
			{
				EnumType* pEnumType = static_cast<EnumType*>(pType);
			//	EnumDef* p = pEnumType->GetItem((std::remove_reference<data_type&>::type)item);
				EnumDef* p = pEnumType->GetItem(*(int*)(&item));
				if (p)
				{
					writer << p->m_name;
				}
				else
					ASSERT(0);
			}
			break;

		default:
			ASSERT(0);
		}
	}
	else
	{
		ASSERT(0);
	}

	return writer;
}

template<class data_type>
TextWriter& operator << (TextWriter& writer, const data_type& item)
{
	/*
	Type* pType = typeof(data_type);
	if (pType)
	{
		ClassType* pClassType = pType->AsClass();
		if (pClassType)
		{
		}
	}
	else
	{
	}
	*/
	WriteToStream(writer, item);

	return writer;
}

#endif	// __LERSTAD__

#ifndef __LERSTAD__
inline TextWriter& WriteToStream(TextWriter& writer, Object* item)
{
#if 0
	Type* pType = typeid(item).GetType();
	ASSERT(pType->get_Kind() == type_pointer);

	stream << "ptr(" << *item << ")";
#endif
	return writer;
}
#endif

LFCEXT TextWriter& operator << (TextWriter& writer, bool bit);
LFCEXT TextWriter& operator << (TextWriter& writer, char ch);
LFCEXT TextWriter& operator << (TextWriter& writer, wchar_t ch);
LFCEXT TextWriter& operator << (TextWriter& writer, signed char number);
LFCEXT TextWriter& operator << (TextWriter& writer, unsigned char number);
LFCEXT TextWriter& operator << (TextWriter& writer, short number);
LFCEXT TextWriter& operator << (TextWriter& writer, unsigned short number);
LFCEXT TextWriter& operator << (TextWriter& writer, int number);
LFCEXT TextWriter& operator << (TextWriter& writer, unsigned int number);
LFCEXT TextWriter& operator << (TextWriter& writer, long number);
LFCEXT TextWriter& operator << (TextWriter& writer, unsigned long number);
LFCEXT TextWriter& operator << (TextWriter& writer, int64 number);
LFCEXT TextWriter& operator << (TextWriter& writer, uint64 number);
LFCEXT TextWriter& operator << (TextWriter& writer, float number);
LFCEXT TextWriter& operator << (TextWriter& writer, double number);
LFCEXT TextWriter& operator << (TextWriter& writer, long double number);
LFCEXT TextWriter& operator << (TextWriter& writer, char* cstr);
LFCEXT TextWriter& operator << (TextWriter& writer, const char* cstr);
LFCEXT TextWriter& operator << (TextWriter& writer, wchar_t* cstr);
LFCEXT TextWriter& operator << (TextWriter& writer, const wchar_t* cstr);
LFCEXT TextWriter& operator << (TextWriter& writer, void* p);
LFCEXT TextWriter& operator << (TextWriter& writer, const void* p);

}

inline IO::TextWriter& endl(IO::TextWriter& writer)
{
	writer << "\n";
	return writer;
}

namespace IO
{

inline TextWriter& base(TextWriter& writer, int base)
{
	writer.setbase(base);
	return writer;
}

class LFCEXT Reader : public Object
{
public:

	CTOR Reader() : m_refcount(0), m_state(0)
	{
	}

	virtual ~Reader()
	{
		VERIFY(m_refcount == 0);
	}

	inline size_t IncRef()
	{
		return InterlockedIncrement(&m_refcount);
	}

	size_t DecRef()
	{
		ASSERT(m_refcount > 0);
		size_t refcount = InterlockedDecrement(&m_refcount);
		if (refcount == 0)
		{
			this->~Reader();
		}
		return refcount;
	}

	virtual bool ReadBool() abstract;
	virtual char ReadChar() abstract;
	virtual wchar_t ReadWChar() abstract;
	virtual signed char ReadSByte() abstract;
	virtual unsigned char ReadUByte() abstract;
	virtual short ReadShort() abstract;
	virtual unsigned short ReadUShort() abstract;
	virtual int ReadInt() abstract;
	virtual unsigned int ReadUInt() abstract;
	virtual long ReadLong() abstract;
	virtual unsigned long ReadULong() abstract;
	virtual int64 ReadInt64() abstract;
	virtual uint64 ReadUInt64() abstract;
	virtual float ReadFloat() abstract;
	virtual double ReadDouble() abstract;

	virtual long double ReadLongDouble()
	{
		return ReadDouble();
	}

	virtual uint64 GetPosition() abstract;

	uint state() const
	{
		return m_state;
	}

#ifndef __LERSTAD__

	template<class T> T Read();

	template<> inline bool Read()
	{
		return ReadBool();
	}

	template<> inline char Read()
	{
		return ReadChar();
	}

	template<> inline wchar_t Read()
	{
		return ReadWChar();
	}

	template<> inline signed char Read()
	{
		return ReadSByte();
	}

	template<> inline unsigned char Read()
	{
		return ReadUByte();
	}

	template<> inline short Read()
	{
		return ReadInt();
	}

	template<> inline unsigned short Read()
	{
		return ReadUInt();
	}

	template<> inline int Read()
	{
		return ReadInt();
	}

	template<> inline unsigned int Read()
	{
		return ReadUInt();
	}

	template<> inline long Read()
	{
		return ReadLong();
	}

	template<> inline unsigned long Read()
	{
		return ReadULong();
	}

	template<> inline int64 Read()
	{
		return ReadInt64();
	}

	template<> inline uint64 Read()
	{
		return ReadUInt64();
	}

	template<> inline float Read()
	{
		return ReadFloat();
	}

	template<> inline double Read()
	{
		return ReadDouble();
	}

	template<> inline long double Read()
	{
		return ReadLongDouble();
	}

#endif

protected:

	uint m_state;

private:

	size_t m_refcount;
};

LFCEXT inline Reader& operator >> (Reader& reader, bool& bit)
{
	bit = reader.ReadBool();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, char& ch)
{
	ch = reader.ReadChar();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, wchar_t& ch)
{
	ch = reader.ReadWChar();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, signed char& number)
{
	number = reader.ReadSByte();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, unsigned char& number)
{
	number = reader.ReadUByte();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, short& number)
{
	number = reader.ReadShort();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, unsigned short& number)
{
	number = reader.ReadUShort();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, int& number)
{
	number = reader.ReadInt();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, unsigned int& number)
{
	number = reader.ReadUInt();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, long& number)
{
	number = reader.ReadLong();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, unsigned long& number)
{
	number = reader.ReadULong();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, int64& number)
{
	number = reader.ReadInt64();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, uint64& number)
{
	number = reader.ReadUInt64();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, float& number)
{
	number = reader.ReadFloat();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, double& number)
{
	number = reader.ReadDouble();
	return reader;
}

LFCEXT inline Reader& operator >> (Reader& reader, long double& number)
{
	number = reader.ReadLongDouble();
	return reader;
}

class LFCEXT TextReader : public Reader
{
public:

	virtual int ReadCharacter()
	{
		char ch;

		if (ReadChars(&ch, 1) != 1)
		{
			m_state |= 1;
			return -1;

		}

		return ch;
	}

	virtual size_t ReadChars(char* p, size_t len) = 0;
	virtual size_t ReadChars(wchar_t* p, size_t len) = 0;

	uint ReadChars32(char* p, uint len)
	{
		return (uint)ReadChars(p, len);
	}

	uint ReadChars32(wchar_t* p, uint len)
	{
		return (uint)ReadChars(p, len);
	}

	virtual bool ReadBool() override;
	virtual char ReadChar() override;
	virtual wchar_t ReadWChar() override;
	virtual signed char ReadSByte() override;
	virtual unsigned char ReadUByte() override;
	virtual short ReadShort() override;
	virtual unsigned short ReadUShort() override;
	virtual int ReadInt() override;
	virtual unsigned int ReadUInt() override;
	virtual long ReadLong() override;
	virtual unsigned long ReadULong() override;
	virtual int64 ReadInt64() override;
	virtual uint64 ReadUInt64() override;
	virtual float ReadFloat() override;
	virtual double ReadDouble() override;
//	virtual long double ReadLongDouble() override;

	String ReadLine();
	String ReadToEol();
	String ReadToEof();

protected:

	CTOR TextReader();
};

LFCEXT TextReader& operator >> (TextReader& reader, Utf32Char& ch);

struct FileError
{
	operator int () const
	{
		return code;
	}

	int code;
};

LFCEXT TextWriter& WriteToStream(TextWriter& writer, const FileError& err);

enum FileMode
{
	FileMode_Create,
// Creates a new file, always.
//If a file exists, the function overwrites the file, clears the existing attributes, combines the specified file attributes, and flags with FILE_ATTRIBUTE_ARCHIVE, but does not set the security descriptor that the SECURITY_ATTRIBUTES structure specifies.

	FileMode_CreateNew,
// Creates a new file.
// The function fails if a specified file exists.

	FileMode_OpenOrCreate,
// Opens a file, always.
// If a file does not exist, the function creates a file as if dwCreationDisposition is CREATE_NEW.

	FileMode_Open,
// Opens a file.
// The function fails if the file does not exist.
// For more information, see the Remarks section of this topic.

	FileMode_TruncateExisting,
// Opens a file and truncates it so that its size is zero (0) bytes.
// The function fails if the file does not exist.
// The calling process must open the file with the GENERIC_WRITE access right.
};

enum FileAccess
{
	FileAccess_None = 0,
	FileAccess_Read = 1,
	FileAccess_Write = 2,
	FileAccess_ReadWrite = 3
};

enum FileShare
{
	FileShare_None = 0,
	FileShare_Read,
	FileShare_Write,
	FileShare_ReadWrite
};

class LFCEXT FileSystem : public Object
{
public:
	// TODO
};

class LFCEXT FileStream : public Stream
{
public:

	CTOR FileStream(Stream* sync);
	CTOR FileStream(StringIn filename, FileMode mode, FileAccess access);
	CTOR FileStream(StringIn filename, FileMode mode, FileAccess access, FileShare share);
//	CTOR FileStream(File file, bool closeFile = false);
	CTOR FileStream(HANDLE hFile, bool closeFile = false);

	virtual ~FileStream();

	static _Ptr<FileStream> Open(StringIn filename, FileMode mode, FileAccess access);
	static _Ptr<FileStream> Open(StringIn filename, FileMode mode, FileAccess access, FileShare share);
	static _Ptr<FileStream> Open(File file, bool closeFile = false);
	static _Ptr<FileStream> Open(HANDLE hFile, bool closeFile = false);

	/*
	virtual bool IsNTFS() override	// TODO
	{
		return true;
	}
	*/

	virtual bool Close() override;

	virtual size_t Read(void* pv, size_t len) override;
	virtual size_t Write(const void* pv, size_t len) override;

	uint32 Read(void* pv, uint64 offset, uint32 len);
	uint32 Write(const void* pv, uint64 offset, uint32 len);

	virtual size_t ReadChars(char* p, size_t len) override;
	virtual size_t ReadChars(wchar_t* p, size_t len) override;

	virtual uint64 Seek(int64 move, IO::SeekOrigin origin) override;
	virtual uint64 GetSize() override;
	virtual uint64 GetFilePos();

	virtual void SetFileHandle(HANDLE hFile, bool closeFile = false);

	int Peek();

	virtual HANDLE GetFileHandle() const
	{
		return m_hFile;
	}

	virtual String GetFilename() override
	{
		return m_filename;
	}

	virtual bool IsHandleValid() const
	{
		return m_hFile != INVALID_HANDLE_VALUE;
	}

	virtual int state();

	virtual bool CanSeek() override;
	virtual bool CanRead() override;
	virtual bool CanWrite() override;

	bool Reopen(FileAccess access, FileShare share);

//	void SetMode(FileMode mode);
//	void SetEndianess(Endianess endianess);

	static FileError GetLastError();

protected:

	virtual size_t _WriteChars(const char* p, size_t len) override;
	virtual size_t _WriteChars(const wchar_t* p, size_t len) override;

	virtual uint64 GetPosition() override;

public:

	uint64 m_position;

	HANDLE m_hFile;
	String m_filename;
	int m_state;
//	FileMode m_mode;
//	Endianess m_endianess;
	DWORD m_consoleMode;
	bool m_closeFile : 1;
	bool m_isConsole : 1;

	ubyte* m_buffer;
	size_t m_buffersize;
	size_t m_bufferpos;

private:

	CTOR FileStream(const FileStream&);	// private copy constructor
	FileStream& operator = (const FileStream&);	// private copy
};

class LFCEXT StringWriter : public TextWriter
{
public:

	CTOR StringWriter();
	CTOR StringWriter(const StringWriter& other);
	CTOR StringWriter(StringIn str);

	virtual size_t WriteChars(const char8* p, size_t len) override;
	virtual size_t WriteChars(const char16* p, size_t len) override;
	virtual size_t WriteChars(const char32_t* p, size_t len) override;

	StringWriter& operator = (const StringWriter& other);
	StringWriter& operator << (const StringBuilder& strbuilder);

	String str() const
	{
		return m_str;
	}

	virtual String ToString() override
	{
		return str();
	}

	operator String () const
	{
		return str();
	}

	operator StringIn () const
	{
		return str();
	}

	String Detach()
	{
		String str = m_str;
		m_str = nullptr;
		return str;
	}

protected:

	String m_str;
};

class LFCEXT StringReader : public TextReader
{
public:

	CTOR StringReader() : m_position(0)
	{
	}

	CTOR StringReader(StringIn str) : m_str(str), m_position(0)
	{
	}

	virtual size_t ReadChars(char* p, size_t len) override
	{
		len = m_str.CopyTo(p, len, m_position);
		m_position += len;
		return len;
	}

	virtual size_t ReadChars(wchar_t* p, size_t len) override
	{
		len = m_str.CopyTo(p, len, m_position);
		m_position += len;
		return len;
	}

	virtual uint64 GetPosition() override
	{
		return m_position;
	}

	int Peek()
	{
		if (m_position >= m_str.GetLength())
			return -1;

		wchar_t ch;
		m_str.CopyTo(&ch, 1, m_position);
		return ch;
	}

	virtual String ToString() override
	{
		return m_str;
	}

	void set_Data(StringIn str)
	{
		m_str = str;
		m_position = 0;
	}

private:

	String m_str;
	size_t m_position;
};

class LFCEXT DebugStream : public TextWriter
{
public:

	virtual bool IsNull() const override;

	virtual size_t WriteCStr(const char* str) override;
	virtual size_t WriteCStr(const wchar_t* str) override;

	virtual uint64 GetPosition() override
	{
		return m_position;
	}

	virtual size_t WriteChars(const char* p, size_t len) override;
	virtual size_t WriteChars(const wchar_t* p, size_t len) override;

	static DebugStream& get_Out()
	{
		return _out;
	}

private:

	CTOR DebugStream() : m_position(0)
	{
	}

	uint64 m_position;

	static DebugStream _out;
};

class LFCEXT StreamReader : public TextReader
{
public:
	CTOR StreamReader();
	CTOR StreamReader(Stream* baseStream);

	virtual size_t ReadChars(char8* p, size_t len) override;
	virtual size_t ReadChars(char16* p, size_t len) override;
	virtual uint64 GetPosition() override;

	_Ptr<Stream> get_BaseStream()
	{
		return m_baseStream;
	}

	void set_BaseStream(Stream* baseStream)
	{
		m_baseStream = baseStream;
	}

protected:

	_Ptr<Stream> m_baseStream;

private:

	CTOR StreamReader(const StreamReader&);
	StreamReader& operator = (const StreamReader&);
};

class LFCEXT StreamWriter : public TextWriter
{
public:
	CTOR StreamWriter();
	CTOR StreamWriter(Stream* baseStream);

	virtual size_t WriteChars(const char8* p, size_t len) override;
	virtual size_t WriteChars(const char16* p, size_t len) override;

	_Ptr<Stream> get_BaseStream()
	{
		return m_baseStream;
	}

	void set_BaseStream(Stream* baseStream)
	{
		m_baseStream = baseStream;
	}

protected:

	_Ptr<Stream> m_baseStream;

private:

	CTOR StreamWriter(const StreamWriter&);
	StreamWriter& operator = (const StreamWriter&);
};

class LFCEXT NullTextWriter : public TextWriter
{
public:
	CTOR NullTextWriter()
	{
	}

	virtual bool IsNull() const
	{
		return true;
	}

	virtual size_t WriteChars(const char8* p, size_t len) override
	{
		return len;
	}

	virtual size_t WriteChars(const char16* p, size_t len) override
	{
		return len;
	}

	static NullTextWriter writer;
};

class LFCEXT BinaryReader : public Reader
{
public:

	CTOR BinaryReader();
	CTOR BinaryReader(Stream* baseStream);

	virtual bool ReadBool() override;
	virtual char ReadChar() override;
	virtual wchar_t ReadWChar() override;
	virtual signed char ReadSByte() override;
	virtual unsigned char ReadUByte() override;
	virtual short ReadShort() override;
	virtual unsigned short ReadUShort() override;
	virtual int ReadInt() override;
	virtual unsigned int ReadUInt() override;
	virtual long ReadLong() override;
	virtual unsigned long ReadULong() override;
	virtual int64 ReadInt64() override;
	virtual uint64 ReadUInt64() override;
	virtual float ReadFloat() override;
	virtual double ReadDouble() override;
//	virtual long double ReadLongDouble() override;

	virtual uint64 GetPosition() override;

	BinaryReader& operator << (bool bit);

	BinaryReader& operator << (char ch);
	BinaryReader& operator << (wchar_t ch);
	BinaryReader& operator << (Utf32Char ch);

	BinaryReader& operator << (signed char number);
	BinaryReader& operator << (unsigned char number);

	BinaryReader& operator << (short number);
	BinaryReader& operator << (unsigned short number);

	BinaryReader& operator << (int number);
	BinaryReader& operator << (unsigned int number);

	BinaryReader& operator << (long number);
	BinaryReader& operator << (unsigned long number);

	BinaryReader& operator << (int64 number);
	BinaryReader& operator << (uint64 number);

	BinaryReader& operator << (float number);
	BinaryReader& operator << (double number);
	BinaryReader& operator << (long double number);

	size_t Read(void* pv, size_t len);

public:

	_Ptr<Stream> m_baseStream;
	Endianess m_endianess;

	ubyte* m_buffer;
	size_t m_bufferlen;
	size_t m_bufferpos;

private:

	BinaryReader& operator = (const BinaryReader&);
};

class LFCEXT BinaryWriter : public Writer
{
public:

	CTOR BinaryWriter();
	CTOR BinaryWriter(Stream* baseStream);

	virtual void Write(bool bit) override;
	virtual void Write(char ch) override;
	virtual void Write(wchar_t ch) override;
	virtual void Write(signed char value) override;
	virtual void Write(unsigned char value) override;
	virtual void Write(short value) override;
	virtual void Write(unsigned short value) override;
	virtual void Write(int value) override;
	virtual void Write(unsigned int value) override;
	virtual void Write(long value) override;
	virtual void Write(unsigned long value) override;
	virtual void Write(int64 value) override;
	virtual void Write(uint64 value) override;
	virtual void Write(float value) override;
	virtual void Write(double value) override;
//	virtual void Write(long double value) override;

	size_t Write(const void* pv, size_t len);

	void Flush();

public:

	_Ptr<Stream> m_baseStream;
	Endianess m_endianess;

	ubyte* m_buffer;
	size_t m_buffersize;
	size_t m_bufferpos;

protected:

	inline void putbyte(ubyte v);

private:

	BinaryWriter& operator = (const BinaryWriter&);
};

/*
template<class data_type>
BinaryWriter& WriteToStream(BinaryWriter& writer, const data_type& value)
{
	Type* pType = typeof(data_type);
	if (pType)
	{
		ClassType* pClassType = pType->AsClass();
		if (pClassType)
		{
			const ubyte* p = (const ubyte*)&value;
			for (size_t i = 0; i < pClassType->m_pScope->m_orderedDecls.size(); ++i)
			{
				const Declarator* decl = pClassType->m_pScope->m_orderedDecls[i];

				switch (decl->GetType()->get_Kind())
				{
				case type_bool:
					writer.Write(*(bool*)p, sizeof(bool));
					p += sizeof(bool);
					break;

				case type_char:
					writer.Write(*(char*)p, sizeof(char));
					p += sizeof(char);
					break;

				case type_wchar_t:
					writer.Write(*(wchar_t*)p, sizeof(wchar_t));
					p += sizeof(wchar_t);
					break;

				case type_signed_char:
				case type_unsigned_char:
					writer.Write(*(char*)p, sizeof(char));
					p += sizeof(char);
					break;

				case type_short:
				case type_unsigned_short:
					writer.Write(*(short*)p, sizeof(short));
					p += sizeof(short);
					break;

				case type_int:
				case type_unsigned_int:
					writer.Write(*(int*)p, sizeof(int));
					p += sizeof(int);
					break;

				case type_long:
				case type_unsigned_long:
					writer.Write(*(long*)p, sizeof(long));
					p += sizeof(long);
					break;

				default:
					ASSERT(0);
				}
			}
		}
	}
	else
	{
		raise(Exception());
	}
}

template<class data_type>
BinaryWriter& operator << (BinaryWriter& writer, const data_type& value)
{
	return WriteToStream(writer, item);
}
*/

/*
template<class T> class WriterT : public T
{
public:

	Writer& operator << (bool bit);
	Writer& operator << (bitfield bits);
	Writer& operator << (bitfield64 bits);
};

class Writer : public Object
{
public:

	virtual Writer& operator << (bool bit);
	virtual Writer& operator << (bitfield bits);
	virtual Writer& operator << (bitfield64 bits);
};

Reader<CBitStream32>
Reader<BinaryReader>
*/

/*
template<class char_type>
class StringBufferStream : public EmbeddedStream<StringBufferStreamObject<char_type> >
{
public:

	CTOR StringBufferStream(char_type* buffer, size_t size) :
	  EmbeddedStream<StringBufferStreamObject<char_type> >(buffer, size)
	{
	}
};

typedef StringStream StringBuilder;	// TODO remove
*/

/*
#ifndef __LERSTAD__

template<int size>
inline StringBufferStream<char> StringBuffer(char buffer[size])
{
	return StringBufferStream<char>(buffer, size);
}

template<int size>
inline StringBufferStream<wchar_t> StringBuffer(wchar_t buffer[size])
{
	return StringBufferStream<wchar_t>(buffer, size);
}

#endif

inline StringBufferStream<char> StringBuffer(char* buffer, size_t size)
{
	return StringBufferStream<char>(buffer, size);
}

inline StringBufferStream<wchar_t> StringBuffer(wchar_t* buffer, size_t size)
{
	return StringBufferStream<wchar_t>(buffer, size);
}
*/

}	// IO

LFCEXT IO::TextReader& ReadFromStream(IO::TextReader& reader, CString& cbuffer);
LFCEXT IO::TextReader& ReadFromStream(IO::TextReader& reader, String& str);
LFCEXT IO::TextReader& ReadFromStream(IO::TextReader& reader, char& ch);
LFCEXT IO::TextReader& ReadFromStream(IO::TextReader& reader, int& number);

template<class T> IO::TextWriter& WriteToStream(IO::TextWriter& writer, const vector<T>& v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		writer << v[i];
	}

	return writer;
}

class LFCEXT newline
{
public:
	CTOR newline()
	{
	}
};

inline IO::TextWriter& operator << (IO::TextWriter& writer, const newline& nl)
{
	writer << "\n";
	return writer;
}

template<class T>
class Quote
{
public:

	CTOR Quote(const T& content, char _open, char _close) : m_open(_open), m_close(_close), m_content(content)
	{
	}

	const T m_content;
	char m_open;
	char m_close;
};

template<class T>
inline IO::TextWriter& operator << (IO::TextWriter& writer, const Quote<T>& q)
{
	writer << q.m_open << q.m_content << q.m_close;
	return writer;
}

template<class T>
inline Quote<T> quote(const T& content)
{
	return Quote<T>(content, '\'', '\'');
}

template<class T>
inline Quote<T> doublequote(const T& content)
{
	return Quote<T>(content, '\"', '\"');
}

template<class T>
inline Quote<T> paren(const T& content)
{
	return Quote<T>(content, '(', ')');
}

template<class T>
inline Quote<T> bracket(const T& content)
{
	return Quote<T>(content, '[', ']');
}

}

#include "Console.h"

namespace System
{

typedef Console Std;

/*
class LFCEXT Std
{
public:


private:

	CTOR Std();
	Std& operator = (const Std& other);
};
*/

template<class Ty, class ContType = vector<Ty> > class stack
{
public:
	typedef Ty value_type;

	bool empty() const
	{
		return cont.size() == 0;
	}

	unsigned int size() const
	{
		return cont.size();
	}

	void push(const value_type& x)
	{
		cont.push_back(x);
	}

	void pop()
	{
		cont.RemoveAt(cont.GetSize()-1);
	}

	value_type& top()
	{
		return cont[cont.GetSize()-1];
	}

	const value_type& top() const
	{
		return cont[cont.GetSize()-1];
	}

	ContType cont;
};

}

namespace System
{

class cstr_less : public binary_function<const char*, const char*, bool>
{
public:
	bool operator () (const char* str1, const char* str2)
	{
		return strcmp(str1, str2) < 0;
	}
};

template<class T> class Ref_Less : public binary_function<T, T, bool>
{
public:
	bool operator () (const T* x, const T* y) const
	{
		return *x < *y;
	}
};

class StringObject_Less
{
public:
	bool operator () (StringObject* x, StringObject* y)
	{
		return *x < *y;
	}

	bool operator () (StringObject* x, const char* y)
	{
		return *x < y;
	}

	bool operator () (const char* x, StringObject* y)
	{
		return *y > x;
	}
};

template<class T> class Ref_Equal : public binary_function<T, T, bool>
{
public:

	bool operator () (const T* x, const T* y) const
	{
		/*
		if (x == y) return true;
		if (x == NULL) return false;
		if (y == NULL) return false;
		*/
		return *x == *y;
	}
};

}

#include "Module.h"

namespace System
{

LFCEXT String MakeFilePath(Module& module, WCHAR* relpath);

namespace IO
{

#if 0

interface ISequentialByteStream
{
//	virtual ULONG AddRef() = 0;
//	virtual ULONG Release() = 0;
	virtual ULONG Read(void* pv, ULONG cb) = 0;
	virtual ULONG Write(const void* pv, ULONG cb) = 0;
	virtual LONGLONG Seek(LONGLONG move, SeekOrigin origin) = 0;
	virtual LONGLONG GetSize() = 0;
//	virtual LONGLONG GetSize() const = 0;
	virtual ISequentialByteStream* Clone() const = 0;
};
#endif

class LFCEXT MemoryStream : public Stream
{
public:
	CTOR MemoryStream(void* buffer, size_t size);
	CTOR MemoryStream(const void* buffer, size_t size);

	virtual size_t Read(void* pv, size_t cb) override;
	virtual size_t Write(const void* pv, size_t cb) override;
	virtual uint64 Seek(int64 offset, SeekOrigin origin) override;
	virtual uint64 GetSize() override;
	virtual uint64 GetPosition() override
	{
		return m_pos;
	}

	virtual bool CanWrite() override
	{
		return m_CanWrite;
	}

protected:

	ubyte* m_buffer;
	size_t m_size;
	size_t m_pos;
	bool m_CanWrite;
};

#if 0
class LFCEXT BufferedByteStream : public Object, public ISequentialByteStream
{
public:
	CTOR BufferedByteStream(ISequentialByteStream* stream, ULONG buffersize = 4096);

	ULONG AddRef();
	ULONG Release();

	virtual ULONG Read(void* pv, ULONG cb);
	virtual LONGLONG Seek(LONGLONG offset, SeekOrigin origin);
	virtual LONGLONG GetSize();
	virtual LONGLONG GetSize() const;
	virtual ISequentialByteStream* Clone() const;
	virtual ULONG Write(const void* pv, ULONG cb);

protected:

	~BufferedByteStream();

	ISequentialByteStream* m_stream;
//	uint8* m_buffer;

	map<uint32, uint8*> m_buffers;

	ULONG m_buffersize;
	//ULONGLONG m_bufferpos;
	ULONGLONG m_pos;
};

// TODO, remove this class
class LFCEXT ByteStreamWriter : public ISequentialByteStream
{
public:
	CTOR ByteStreamWriter(StringIn filename);
	~ByteStreamWriter();

	ULONG AddRef();
	ULONG Release();

	ULONG Read(void* pv, ULONG cb);
	ULONG Write(const void* pv, ULONG cb);
	virtual LONGLONG Seek(LONGLONG offset, SeekOrigin origin);
	virtual LONGLONG GetSize();
	ISequentialByteStream* Clone() const;

	ULONG m_refcount;
#if WIN32
	HANDLE m_hFile;
#endif

	void Close();
};
#endif

	}	// IO
}	// System

namespace System
{
namespace IO
{

class LFCEXT BitStreamO
{
public:
	CTOR BitStreamO(Stream* bytestream);
	~BitStreamO();

	void putbit(bool bit);
	void putnbits(int nbits, int value);
	void byte_align();

	_Ptr<Stream> m_bytestream;

protected:

	uint8 m_bitcnt;
	uint8 m_curbyte;
};

}	// IO
}	// System

#include "md5.h"
#include "parsenumber.h"
#include "parsestring.h"

#if 0
template <class T> class LFCEXT CManaged
{
public:
	CManaged()
	{
		m_Data = NULL;
	}

	~CManaged()
	{
		_Free();
	}

	/*
	CManaged(T* pT)
	{
		m_refcount = 1;
		m_pT = pT;
	}

	operator T* ()
	{
		return m_pT;
	}
	*/

// Copy constructor
//
	CManaged(const CManaged<T>& s) throw()
		: m_Data(s.m_Data)
	{
		_AddRef();
	}

	void _AddRef()
	{
		if (m_Data != NULL)
			m_Data->AddRef();
	}

	void _Free()
	{
		if (m_Data != NULL)
		{
			m_Data->Release();
			m_Data = NULL;
		}
	}

	operator T* ()
	{
		if (m_Data)
			return m_Data->m_pT;
		return NULL;
	}

	CManaged<T>& operator = (T* pT)
	{
		_Free();
		if (pT)
			m_Data = new CData(pT);

		return *this;
	}

	bool operator == (T* pT) const
	{
		if (m_Data == NULL && pT == NULL) return true;
		if (m_Data == NULL) return false;
		return m_Data->m_pT == pT;
	}

	bool operator != (T* pT) const
	{
		return !(*this == pT);
	}

	// Referencecounted data
	class CData
	{
	private: // // Prevent deletes from outside. Release() must be used.
		~CData()
		{
			ASSERT(m_refcount == 0);
			delete m_pT;
			m_pT = NULL;
		}

		int m_refcount;

	public:
		/*
		CData()
		{
			m_pT = NULL;
			m_refcount = 0;
		}
		*/

		CData(T* pT)
		{
			ASSERT(pT != NULL);
			m_refcount = 1;
			m_pT = pT;
		}

		T* m_pT;

		int AddRef()
		{
			m_refcount++;
			return m_refcount;
		}

		int Release()
		{
			m_refcount--;
			ASSERT(m_refcount >= 0);

			if (m_refcount == 0)
			{
				delete this;
				return 0;
			}

			return m_refcount;
		}

		/*
		operator T* ()
		{
			return m_pT;
		}
		*/
	};
	
	CData* m_Data;
};
#endif

const double M_PI = 3.14159265358979323846;
const double M_SQRT2 = 1.4142135623730950488016887242097;

const float M_PI_f = 3.141592653f;
const float M_SQRT2_f = 1.4142135623f;

#if WIN32

	typedef HANDLE PlatformProcess;

#elif AMIGA

	typedef struct Task* PlatformProcess;

#elif __APPLE__

	typedef unsigned int __darwin_natural_t;
	typedef __darwin_natural_t natural_t;
	typedef natural_t mach_port_name_t;
	typedef mach_port_name_t mach_port_t;
	typedef mach_port_t io_object_t;

	typedef mach_port_t PlatformProcess;

#else	// LINUX

	typedef int PlatformProcess;

//#error "Unknown OS"

#endif

namespace System
{

#ifndef __GNUC__

typedef ULONG (WINAPI *THREADSTARTPROC)(void* lpArgument);
LFCEXT void* CreateThread(THREADSTARTPROC startproc, void* args);

#endif

}

#if 0
class bytestream;

LFCEXT long getnumber(bytestream& s);
LFCEXT StringA ReadLine(bytestream& s);

class bytestream
{
public:
	bytestream(ISequentialByteStream* pStream)
	{
		buf = new char[pStream->GetSize()];
		pStream->Read(buf, pStream->GetSize());
		p = buf;
	}

	~bytestream()
	{
		//m_pStream->Release();
	}

//	ISequentialByteStream* m_pStream;

//	LONGLONG m_pos;
//	char m_c;

	/*
	char& operator * ()
	{
		LONGLONG pos = m_pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (m_pos != pos)
		{
			if (m_pStream->Read(&m_c, 1) != 1)
				THROW(-1);

			m_pos = pos;
		}

		return m_c;
	}

	const bytestream& operator ++ ()	// prefix
	{
		m_pStream->Seek(1, System::IO::STREAM_SEEK_CUR);
		return *this;
	}

	bytestream operator ++ (int)	// postfix
	{
		LONGLONG pos = m_pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		bytestream clone(m_pStream);
		clone.m_c = m_c;

		clone.m_pStream->Seek(pos+1, System::IO::STREAM_SEEK_SET);

		return clone;
	}

	int operator - (const bytestream& other) const
	{
		return m_pStream->Seek(0, System::IO::STREAM_SEEK_CUR) - other.m_pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
	}

	bool operator == (const bytestream& other) const
	{
		if (m_pStream != other.m_pStream) return false;
		return m_pStream->Seek(0, System::IO::STREAM_SEEK_CUR) == other.m_pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
	}
	*/

	char* buf;
	char* p;

	bytestream& operator >> (char &n)
	{
		return *p++;
	}

	bytestream& operator >> (int &n)
	{
		n = getnumber(*this);
		return *this;
	}
};
#endif

/*
IntObject::operator Object* ()
{
	return IntObject::GetIntObject(m_value);
}
*/

/*
interface IObjectCollection : public IUnknownCollection
{
	virtual System::Object* GetObjectItem(unsigned int index) = 0;
};

template<class TYPE> interface ITypedCollection
{
	virtual TYPE GetItem(unsigned int index) = 0;
};

template<class TYPE> interface ITypedObjectCollection
{
	virtual TYPE GetItem(unsigned int index) = 0;
};
*/

namespace System
{

class LFCEXT Bool
{
public:
	CTOR Bool(bool value) : m_value(value)
	{
	}

	explicit CTOR Bool(BOOL value)
	{
		m_value = !!value;
	}

	operator bool () const throw()
	{
		return m_value;
	}

	Bool& operator = (bool rhs) throw()
	{
		m_value = rhs;
		return *this;
	}

	bool operator ! () const throw()
	{
		return !m_value;
	}

	bool operator == (bool rhs) const throw()
	{
		return m_value == rhs;
	}

	bool operator != (bool rhs) const throw()
	{
		return m_value != rhs;
	}

	Bool& operator ++() throw()
	{
		++m_value;	// = true
		return *this;
	}

	Bool operator ++(int) throw()
	{
		return m_value++;
	}

#ifndef __LERSTAD__
	friend IO::TextWriter& operator << (IO::TextWriter& stream, const Bool& v)
	{
		stream << v.m_value;
		return stream;
	}
#endif

	typedef bool value_t;

	static const bool MinValue = 0;
	static const bool MaxValue = 1;

	bool m_value;
};

class LFCEXT Int
{
public:
	CTOR Int(int value) : m_value(value)
	{
	}

	operator int () const throw()
	{
		return m_value;
	}

	Int& operator = (int rhs) throw()
	{
		m_value = rhs;
		return *this;
	}

	bool operator ! () const throw()
	{
		return !m_value;
	}

	int operator ~ () const throw()
	{
		return ~m_value;
	}

	bool operator == (int rhs) const throw()
	{
		return m_value == rhs;
	}

	bool operator != (int rhs) const throw()
	{
		return m_value != rhs;
	}

	bool operator < (int rhs) const throw()
	{
		return m_value < rhs;
	}

	bool operator > (int rhs) const throw()
	{
		return m_value > rhs;
	}

	bool operator <= (int rhs) const throw()
	{
		return m_value <= rhs;
	}

	bool operator >= (int rhs) const throw()
	{
		return m_value >= rhs;
	}

	Int& operator ++() throw()
	{
		++m_value;
		return *this;
	}

	Int& operator --() throw()
	{
		--m_value;
		return *this;
	}

	Int operator ++(int) throw()
	{
		return m_value++;
	}

	Int operator --(int) throw()
	{
		return m_value--;
	}

	Int& operator += (int rhs) throw()
	{
		m_value += rhs;
		return *this;
	}

	Int& operator -= (int rhs) throw()
	{
		m_value -= rhs;
		return *this;
	}

	Int& operator *= (int rhs) throw()
	{
		m_value *= rhs;
		return *this;
	}

	Int& operator /= (int rhs)
	{
		m_value /= rhs;
		return *this;
	}

	Int& operator %= (int rhs)
	{
		m_value %= rhs;
		return *this;
	}

	String ToString() const
	{
		return String::FromNumber(m_value);
	}

#ifndef __LERSTAD__
	friend IO::TextWriter& operator << (IO::TextWriter& stream, const Int& v)
	{
		stream << v.m_value;
		return stream;
	}
#endif

	typedef int value_t;

	static const int MinValue = _I32_MIN;
	static const int MaxValue = _I32_MAX;

	int m_value;
};

class LFCEXT Float
{
public:
	CTOR Float(float value) : m_value(value)
	{
	}

	operator float () const throw()
	{
		return m_value;
	}

	Float& operator = (float rhs) throw()
	{
		m_value = rhs;
		return *this;
	}

	bool operator == (float rhs) const throw()
	{
		return m_value == rhs;
	}

	bool operator != (float rhs) const throw()
	{
		return m_value != rhs;
	}

	float m_value;
};

class LFCEXT Double
{
public:
	CTOR Double(double value) : m_value(value)
	{
	}

	operator double () const throw()
	{
		return m_value;
	}

	Double& operator = (double rhs) throw()
	{
		m_value = rhs;
		return *this;
	}

	bool operator == (double rhs) const throw()
	{
		return m_value == rhs;
	}

	bool operator != (double rhs) const throw()
	{
		return m_value != rhs;
	}

	Double& operator += (double rhs)
	{
		m_value += rhs;
		return *this;
	}

	Double& operator -= (double rhs)
	{
		m_value -= rhs;
		return *this;
	}

	Double& operator *= (double rhs)
	{
		m_value *= rhs;
		return *this;
	}

	Double& operator /= (double rhs)
	{
		m_value /= rhs;
		return *this;
	}

	String ToString() const
	{
		return String::FromNumber(m_value);
	}

#ifndef __LERSTAD__
	friend IO::TextWriter& operator << (IO::TextWriter& stream, const Double& v)
	{
		stream << v.m_value;
		return stream;
	}
#endif

	static bool IsNaN(double value)
	{
		return !!_isnan(value);
	}

	typedef double value_t;

	static constexpr double get_MinValue() { return DBL_MIN; }
#ifndef __LERSTAD__
	static constexpr double get_MaxValue() { return DBL_MAX; }
	static constexpr double get_Epsilon() { return DBL_EPSILON; }
#endif
	static constexpr double get_NegativeInfinity() { return double_NegativeInfinity.value; }
	static constexpr double get_PositiveInfinity() { return double_PositiveInfinity.value; }
	static constexpr double get_NAN() { return double_NaN.value; }

	double m_value;
};

class LFCEXT Decimal
{
public:
	union
	{
		int32 data[4];
	};
};

template<class T> struct AliasClass
{
};

#ifndef __LERSTAD__
template<> struct AliasClass<bool>
{
	typedef Bool type;
};

template<> struct AliasClass<int>
{
	typedef Int type;
};

template<> struct AliasClass<double>
{
	typedef Double type;
};
#endif

template<class T> class Nullable
{
public:

	CTOR Nullable() : m_hasvalue(false)
	{
	}

	/*
	CTOR Nullable(const Nullable& other)
	{
	}
	*/

	CTOR Nullable(T value) : m_value(value), m_hasvalue(true)
	{
	}

//	Nullable& operator = (const Nullable& other)

	bool operator == (const Nullable<T>& other) const
	{
		if (!m_hasvalue && !other.m_hasvalue)
			return true;
		else if (!m_hasvalue)
			return false;
		else if (!other.m_hasvalue)
			return false;
		else
			return m_value == other.m_value;
	}

	inline bool operator != (const Nullable<T>& other) const
	{
		return !(*this == other);
	}

	inline Nullable<T>& operator = (const T& otherValue)
	{
		m_hasvalue = true;
		m_value = otherValue;
		return *this;
	}

	/*
	inline Nullable<T>& operator = (const Nullable<T>& other)
	{
		m_hasvalue = other.m_hasvalue;
		m_value = other.m_value;
		return *this;
	}
	*/

	/*
	inline T operator + (const T& otherValue) const
	{
		if (!m_hasvalue) throw exception("null value");
		return m_value + otherValue;
	}

	inline T operator - (const T& otherValue) const
	{
		if (!m_hasvalue) throw exception("null value");
		return m_value - otherValue;
	}
	*/

	const Type_Info& GetUnderlyingType() const
	{
		return typeid(T);
	}

	inline bool HasValue() const
	{
		return m_hasvalue;
	}

	T Value() const
	{
		if (!m_hasvalue)
		{
			raise(Exception("null value"));
		}

		return m_value;
	}

	/*
	const T& Value() const
	{
		if (!m_hasvalue) throw exception("null value");
		return m_value;
	}
*/

	operator T () const
	{
		return Value();
	}

	/*
	operator const T& () const
	{
		return Value();
	}
	*/
	
	T m_value;
	bool m_hasvalue;
};

#ifndef __LERSTAD__
template<> class Nullable<bool>
{
public:

	typedef bool T;

	CTOR Nullable() : m_hasvalue(false)
	{
	}

	/*
	CTOR Nullable(const Nullable& other)
	{
	}
	*/

	CTOR Nullable(T value) : m_value(value), m_hasvalue(true)
	{
	}

//	Nullable& operator = (const Nullable& other)

	bool operator == (const Nullable<T>& other) const
	{
		if (!m_hasvalue && !other.m_hasvalue)
			return true;
		else if (!m_hasvalue)
			return false;
		else if (!other.m_hasvalue)
			return false;
		else
			return m_value == other.m_value;
	}

	inline bool operator != (const Nullable<T>& other) const
	{
		return !(*this == other);
	}

	inline Nullable<T>& operator = (const T& otherValue)
	{
		m_hasvalue = true;
		m_value = otherValue;
		return *this;
	}

	/*
	inline Nullable<T>& operator = (const Nullable<T>& other)
	{
		m_hasvalue = other.m_hasvalue;
		m_value = other.m_value;
		return *this;
	}
	*/

	/*
	inline T operator + (const T& otherValue) const
	{
		if (!m_hasvalue) throw exception("null value");
		return m_value + otherValue;
	}

	inline T operator - (const T& otherValue) const
	{
		if (!m_hasvalue) throw exception("null value");
		return m_value - otherValue;
	}
	*/

	const Type_Info& GetUnderlyingType() const
	{
		return typeid(T);
	}

	inline bool HasValue() const
	{
		return m_hasvalue;
	}

	T Value() const
	{
		if (!m_hasvalue)
		{
			raise(Exception("null value"));
		}

		return m_value;
	}

	/*
	const T& Value() const
	{
		if (!m_hasvalue) throw exception("null value");
		return m_value;
	}
*/

	operator T () const
	{
		return Value();
	}

	bool m_value : 1;
	bool m_hasvalue : 1;
};
#endif

// Boxing

inline BoolObject* box_cast(bool value)
{
	return BoolObject::GetObject(value);
}

inline SByteObject* box_cast(signed char value)
{
	return SByteObject::GetObject(value);
}

inline UByteObject* box_cast(unsigned char value)
{
	return UByteObject::GetObject(value);
}

inline ShortObject* box_cast(short value)
{
	return ShortObject::GetObject(value);
}

inline UShortObject* box_cast(unsigned short value)
{
	return UShortObject::GetObject(value);
}

inline IntObject* box_cast(int value)
{
	return IntObject::GetObject(value);
}

inline UIntObject* box_cast(unsigned int value)
{
	return UIntObject::GetObject(value);
}

inline Int64Object* box_cast(long long value)
{
	return Int64Object::GetObject(value);
}

inline UInt64Object* box_cast(unsigned long long value)
{
	return UInt64Object::GetObject(value);
}

inline FloatObject* box_cast(float value)
{
	return FloatObject::GetObject(value);
}

inline DoubleObject* box_cast(double value)
{
	return DoubleObject::GetObject(value);
}

template<class T> inline Object* box_cast(T* value)
{
	return dynamic_cast<Object*>(value);
}

inline Object* box_cast(Object* value)
{
	return value;
}

template<class TYPE> inline TYPE unbox_cast(Object* object)
{
	if (object == nullptr)
	{
		return TYPE();
	}
	else
	{
		TYPE value = dynamic_cast<TYPE>(object);
		if (value == nullptr)
		{
			raise(Exception(L"Not of correct type"));
		}
		return value;
	}
}

#ifndef __LERSTAD__

template<> inline bool unbox_cast<bool>(Object* object)
{
	if (object == BoolObject::get_False())
	{
		return false;
	}
	else if (object == BoolObject::get_True())
	{
		return true;
	}
	else
	{
		raise(SystemException(L"Not BoolObject"));
	}
}

template<> inline signed char unbox_cast<signed char>(Object* object)
{
	int value = SByteObject::GetValueFrom(object);
	if (value == 0xffff)
	{
		raise(SystemException(L"Not SByteObject"));
	}
	return (signed char)value;
}

template<> inline unsigned char unbox_cast<unsigned char>(Object* object)
{
	int value = UByteObject::GetValueFrom(object);
	if (value == 0xffff)
	{
		raise(SystemException(L"Not UByteObject"));
	}
	return (unsigned char)value;
}

template<> inline int unbox_cast<int>(Object* object)
{
	IntObject* value = dynamic_cast<IntObject*>(object);
	if (value == nullptr)
	{
		raise(SystemException(L"Not IntObject"));
	}
	return value->GetValue();
}

template<> inline unsigned int unbox_cast<unsigned int>(Object* object)
{
	UIntObject* value = dynamic_cast<UIntObject*>(object);
	if (value == nullptr)
	{
		raise(SystemException(L"Not UIntObject"));
	}
	return value->GetValue();
}

template<> inline long long unbox_cast<long long>(Object* object)
{
	Int64Object* value = dynamic_cast<Int64Object*>(object);
	if (value == nullptr)
	{
		raise(SystemException(L"Not Int64Object"));
	}
	return value->GetValue();
}

template<> inline unsigned long long unbox_cast<unsigned long long>(Object* object)
{
	UInt64Object* value = dynamic_cast<UInt64Object*>(object);
	if (value == nullptr)
	{
		raise(SystemException(L"Not UInt64Object"));
	}
	return value->GetValue();
}

template<> inline float unbox_cast<float>(Object* object)
{
	FloatObject* value = dynamic_cast<FloatObject*>(object);
	if (value == nullptr)
	{
		raise(SystemException(L"Not FloatObject"));
	}
	return value->GetValue();
}

template<> inline double unbox_cast<double>(Object* object)
{
	DoubleObject* value = dynamic_cast<DoubleObject*>(object);
	if (value == nullptr)
	{
		raise(SystemException(L"Not DoubleObject"));
	}
	return value->GetValue();
}

template<> inline String unbox_cast<String>(Object* object)
{
	if (object == nullptr)
	{
		return nullptr;
	}
	else
	{
		StringObject* value = dynamic_cast<StringObject*>(object);
		if (value == nullptr)
		{
			raise(SystemException(L"Not StringObject"));
		}
		return value;
	}
}

#endif

class ComBSTR;
class ComVariant;

class Dispatch;
class Property;

class LFCEXT Locale
{
public:

	static bool IsValidName(StringIn name);
	static String get_UserDefault();
	static String get_SystemDefault();
	static List<String>& get_Locales();
	static List<GEOID>& get_GeoIDs();

private:

	friend BOOL CALLBACK myEnumGeoInfoProc(GEOID GeoId);
	friend BOOL CALLBACK myEnumLocalesProcEx(LPWSTR lpLocaleString, DWORD dwFlags, LPARAM lParam);

	static List<String> s_localesAll;
	static List<GEOID> s_geoIDs;
};

union VariantValue
{
	bool bool_val;

	char char_val;
	wchar_t wchar_t_val;
	char16_t char16_t_val;
	char32_t char32_t_val;

	signed char schar_val;
	unsigned char uchar_val;
	short short_val;
	unsigned short ushort_val;
	int int_val;
	unsigned int uint_val;
	long long_val;
	unsigned long ulong_val;
	long long longlong_val;
	unsigned long long ulonglong_val;

	int8 int8_val;
	uint8 uint8_val;
	int16 int16_val;
	uint16 uint16_val;
	int32 int32_val;
	uint32 uint32_val;
	int64 int64_val;
	uint64 uint64_val;

	float float_val;
	double double_val;
	long double longdouble_val;
	float float32_val;
	double float64_val;

	size_t size_t_val;
	ptrdiff_t ptrdiff_t_val;
	ULONG_PTR ulongptr_val;

// pointers
	bool* pbool_val;
	char* pchar_val;
	wchar_t* pwchar_t_val;
	char16_t* pchar16_t_val;
	char32_t* pchar32_t_val;

	signed char* pschar_val;
	unsigned char* puchar_val;
	short* pshort_val;
	unsigned short* pushort_val;
	int* pint_val;
	unsigned int* puint_val;
	long* plong_val;
	unsigned long* pulong_val;
	long long* plonglong_val;
	unsigned long long* pulonglong_val;

	int8* pint8_val;
	uint8* puint8_val;
	int16* pint16_val;
	uint16* puint16_val;
	int32* pint32_val;
	uint32* puint32_val;
	int64* pint64_val;
	uint64* puint64_val;

	float* pfloat_val;
	double* pdouble_val;
	long double* plongdouble_val;
	float* pfloat32_val;
	double* pfloat64_val;

	size_t* psize_t_val;
	ptrdiff_t* pptrdiff_t_val;
	ULONG_PTR* pulongptr_val;

	Object* pObject;
	void* ptr_val;

	HANDLE whandle;	// not garbage collected
	IUnknown* punk_val;
	IDispatch* pdisp_val;
	BSTR bstr_val;
	FILETIME filetime_val;
};

template<class T> class _VarTypeInfo
{
};

#ifndef __LERSTAD__
template<> class _VarTypeInfo<bool>
{
public:
	static bool VariantValue::* const pmField;
};
__declspec(selectany) bool VariantValue::* const _VarTypeInfo<bool>::pmField = &VariantValue::bool_val;

template<> class _VarTypeInfo<char>
{
public:
	static char VariantValue::* const pmField;
};
__declspec(selectany) char VariantValue::* const _VarTypeInfo<char>::pmField = &VariantValue::char_val;

template<> class _VarTypeInfo<signed char>
{
public:
	static signed char VariantValue::* const pmField;
};
__declspec(selectany) signed char VariantValue::* const _VarTypeInfo<signed char>::pmField = &VariantValue::schar_val;

template<> class _VarTypeInfo<unsigned char>
{
public:
	static unsigned char VariantValue::* const pmField;
};
__declspec(selectany) unsigned char VariantValue::* const _VarTypeInfo<unsigned char>::pmField = &VariantValue::uchar_val;

template<> class _VarTypeInfo<FILETIME>
{
public:
	static FILETIME VariantValue::* const pmField;
};
__declspec(selectany) FILETIME VariantValue::* const _VarTypeInfo<FILETIME>::pmField = &VariantValue::filetime_val;
#endif

////////////////////////////////////

template<class T> class _ComVarTypeInfo
{
};

#if 0
template<> class _ComVarTypeInfo<char>
{
public:
	static const VARTYPE VT = VT_I1;
	static char VARIANT::* const pmField;
};
__declspec(selectany) char VARIANT::* const _ComVarTypeInfo<char>::pmField = &VARIANT::cVal;
#endif

}	// System

#include "FilePath.h"
#include "TypeArchive.h"
#include "Type.h"
#include "Variant.h"
#include "Debug.h"
#include "CodeViewDebugInfo.h"	// TODO, remove from here ??

/** The System namespace is the root namespace for many common classes
*/
namespace System
{

union UntypedVariant
{
	bool bool_val;
	char char_val;
	wchar_t wchar_val;

	signed char schar_val;
	unsigned char uchar_val;
	short short_val;
	unsigned short ushort_val;
	int int_val;
	unsigned int uint_val;
	long long_val;
	unsigned long ulong_val;
	long long longlong_val;
	unsigned long long ulonglong_val;

	int8 int8_val;
	uint8 uint8_val;
	int16 int16_val;
	uint16 uint16_val;
	int32 int32_val;
	uint32 uint32_val;
	int64 int64_val;
	uint64 uint64_val;

	float float_val;
	double double_val;
	float float32_val;
	double float64_val;

	HANDLE whandle;	// not garbage collected
	Object* obj_val;
	void* ptr_val;
};

class LFCEXT UndefinedValue
{
public:

	operator Variant () const
	{
		return Variant();
	}

	operator Object* () const
	{
		return &undefinedObject;
	}

private:

	static Object undefinedObject;
};

extern LFCEXT UndefinedValue undefined;

template<class Key_t, class Value_t, class MAP_TYPE = multimap<Key_t, Value_t> > class TypedMultiMapCollection : public Object, public IEnumerable<Value_t>
{
public:

	typedef Key_t key_t;
	typedef Value_t value_t;
	typedef MAP_TYPE Map_t;

	class Enumerator : public Object, public IEnumerator<Value_t>
	{
	public:

#ifndef __LERSTAD__
		CTOR Enumerator(TypedMultiMapCollection* pList) : m_pList(pList)
		{
		}
#endif

		virtual bool MoveNext() override
		{
			if (m_it == m_pList->m_map.end() || m_it->first != m_pList->m_key)
				return false;

			if (m_it.m_p == NULL)
			{
				m_it = m_pList->m_begin;
			}
			else
			{
				++m_it;
			}

			return true;
		}

		virtual value_t get_Current() override
		{
			if (m_it.m_p == NULL || m_it == m_pList->m_map.end() || m_it->first != m_pList->m_key)
			{
				raise(Exception("not at valid position"));
			}

			return m_it->second;
		}

#ifndef __LERSTAD__
		typename multimap<Key_t, Value_t>::iterator m_it;
		TypedMultiMapCollection* m_pList;
#else
		Object* m_it;
		Object* m_pList;
#endif
	};

	CTOR TypedMultiMapCollection(MAP_TYPE m = MAP_TYPE()) : m_map(m)
	{
		m_begin = m_map.begin();
	//	m_it.m_p = NULL;
	}

	IEnumerator<Value_t>* GetEnumerator() override
	{
		return new Enumerator(this);
	}

	virtual size_t GetCount()
	{
		size_t count = 0;

		multimap<key_t, value_t>::iterator it = m_begin;
		while (it != m_map.end() && it->first == m_key)
		{
			++count;
			++it;
		}

		return count;
	}

	virtual String ToString() override
	{
		String str;

		for (multimap<key_t, value_t>::iterator it = m_begin; it != m_map.end() && it->first == m_key; ++it)
		{
#ifndef __LERSTAD__
			value_t value = it->second;
#endif

			str += value->ToString();
			str += "\n";
		}

		return str;
	}

	MAP_TYPE m_map;
#ifndef __LERSTAD__
	typename multimap<key_t, value_t>::iterator m_begin;
#else
	Object* m_begin;
#endif

	key_t m_key;
};

template<class Key_t, class Value_t, class MAP_TYPE = map<Key_t, Value_t> > class Map : public Object, public IEnumerable<Value_t>
{
public:

	typedef Key_t key_t;
	typedef Value_t value_t;
	typedef MAP_TYPE Map_t;

	/*
	CTOR Map()
	{
		m_begin = m_map.begin();
	}
	*/

	class Enumerator : public Object, public IEnumerator<Value_t>
	{
	public:

#ifndef __LERSTAD__
		CTOR Enumerator(Map* pList) : m_pList(pList)
		{
		}
#endif

		virtual bool MoveNext() override
		{
			if (m_it == m_pList->m_map.end())
				return false;

			if (m_it.m_p == NULL)
			{
				m_it = m_pList->m_map.begin();
			}
			else
			{
				++m_it;
			}

			return true;
		}

		virtual value_t get_Current() override
		{
			if (m_it.m_p == NULL || m_it == m_pList->m_map.end())
			{
				raise(Exception("not at valid position"));
			}

			return m_it->second;
		}

#ifndef __LERSTAD__
		typename map<Key_t, Value_t>::iterator m_it;
		Map* m_pList;
#else
		Object* m_it;
		Object* m_pList;
#endif
	};

	CTOR Map(MAP_TYPE m = map<Key_t, Value_t>()) : m_map(m)
	{
		m_begin = m_map.begin();
	//	m_it.m_p = NULL;
	}

	/*
	CTOR Map(IEnumerator<TYPE>* enumerator)
	{
		while (enumerator->MoveNext())
		{
			Add(enumerator->get_Current());
		}
	}
	*/

	IEnumerator<Value_t>* GetEnumerator() override
	{
		return new Enumerator(this);
	}

	virtual size_t GetCount()
	{
		size_t count = 0;

		map<key_t, value_t>::iterator it = m_begin;
		while (it != m_map.end())
		{
			++count;
			++it;
		}

		return count;
	}

	virtual String ToString() override
	{
		String str;

		for (map<key_t, value_t>::iterator it = m_begin; it != m_map.end(); ++it)
		{
#ifndef __LERSTAD__
			value_t value = it->second;
#endif

			str += value->ToString();
			str += "\n";
		}

		return str;
	}

	/*
	void Add(const value_t& value)
	{
		m_map.push_back(value);
	}
	*/

	MAP_TYPE m_map;
#ifndef __LERSTAD__
	typename map<key_t, value_t>::iterator m_begin;
#else
	Object* m_begin;
#endif
};

}

#include "FunctionObject.h"

namespace System
{

class LFCEXT TypeAddress
{
public:
	
	CTOR TypeAddress() : m_pType(nullptr), m_address(0)
	{
	}
	
	CTOR TypeAddress(Type* pType, ULONG_PTR address) : m_pType(pType), m_address(address)
	{
	}

	bool operator < (const TypeAddress& other) const
	{
		return m_address < other.m_address;
	}

	Type* m_pType;
	ULONG_PTR m_address;
};

class LFCEXT CVR : public Object, public IDebugInfoReceiver
{
public:

	ULONG_PTR LookupSymbol(StringIn name);

	virtual NamedType* LookupNamedType(StringIn name);
	virtual Type* CreatePointerType(Type_type type, Type* pPointerTo);
	virtual void OnSymbol(StringIn name, ULONG_PTR address, ULONG_PTR dwData);
	virtual void OnType(StringIn name, NamedType* type, ULONG_PTR dwData);
	virtual Scope* OnProc(Scope* pScope, StringIn name, Type* type, ULONG_PTR startAddress, ULONG_PTR endAddress, ULONG_PTR dwData);
	virtual Scope* End(Scope* pScope);
	virtual void OnData(StringIn name, Type* type, ULONG_PTR address, ULONG_PTR dwData);
	virtual String CreateString(const char* str);

	map<String, ULONG_PTR> m_procs;
	multimap<String, TypeAddress> m_procs2;
	multimap<String, ULONG_PTR> m_symbols;

public://protected:

	map<String, NamedType*> m_namedTypes;
	typedef map<String, String> stringmap_t;
	stringmap_t m_strings;

protected:

	typedef map<System::Type*, System::PointerType*, less<System::Type*> > PointerTypes;
	typedef map<System::Type*, System::ReferenceType*, less<System::Type*> > ReferenceTypes;

	PointerTypes m_pointer_Types;
	ReferenceTypes m_reference_Types;
};

LFCEXT IEnumerable<CppSourceFile*>* GetSourceFiles();
LFCEXT IEnumerable<FilePart*>* GetFiles(StringIn part);

typedef TypedMultiMapCollection<String, NamedType*, multimap<String, NamedType*>&> NamedTypeMultiMapCollection;
typedef TypedMultiMapCollection<String, FunctionObject*, multimap<String, FunctionObject*>&> FunctionObjectMultiMapCollection;
typedef TypedMultiMapCollection<String, FilePart*, multimap<String, FilePart*>&> FilePartMap;

class LFCEXT TypeDatabase : public Object
{
public:
	CTOR TypeDatabase();

	NamedType* LookupNamedType(StringIn name);

public:

	TypeStuff* m_typestuff;
	Namespace* m_globalNamespace;
	CVR* m_debugInfo;

	map<String, NamedType*> m_namedTypes;
	multimap<String, NamedType*> m_namedTypesM;
	multimap<String, FunctionObject*> m_procs;
	vector<Module*, std_allocator> m_hmodules;

	static Type** m_types[1024];

	static TypeDatabase* pD;
};

LFCEXT void AddPersistentLiveRoot(void** pp);

class LFCEXT GC
{
public:

	static void Collect();

private:

	CTOR GC();
};

}	// System

#include "Dispatch.h"

namespace System
{

typedef int (*ThreadStarterProc)(Object* param);

/**
The Thread class represents a thread of execution
*/
class LFCEXT Thread : public Object
{
public:

	CTOR Thread()
	{
	}

	~Thread()
	{
		if (m_hThread)
		{
			CloseHandle(m_hThread);
		}
	}

	CTOR Thread(HANDLE hThread, DWORD threadId);

//	virtual int Run(Object* param);

	void RunProc(ThreadStarterProc proc, Object* param);

	class ThreadProcParameter
	{
	public:
		Thread* m_thisThread;
		ThreadStarterProc m_proc;
		Object* m_param;
		HANDLE m_hEvent;
	};

	uint GetExitCode();

	static Thread* CurrentThread();
	static void Sleep(DWORD milliseconds);

private:

	static DWORD WINAPI ThreadProc(LPVOID lpParameter);

//	static __declspec(thread) Thread* s_currentThread;

	HANDLE m_hThread;
	DWORD m_threadId;
};

LFCEXT Dispatch* GetDispatch(NamespaceType* pClass);

//LFCEXT Conv* Convert(const cpp::Type* pType, const cpp::Type* ArgType, int level);

LFCEXT ClassType* GetType(const void* object, bool nothrow = false);
LFCEXT void* DynamicCast(void* obj, ClassType* type, ClassType* totype);
LFCEXT void* LeftMost(void* obj, ClassType** ppClass);

template<class T> T __dynamic_cast(void* obj)
{
#ifndef __LERSTAD__
	return (T)DynamicCast(obj, nullptr, typeid(std::remove_pointer<T>::type)->AsClass());
#endif
}

template<class T> T __dynamic_cast(const Variant& v)
{
#ifndef __LERSTAD__
	bool ok;
	return v.try_cast<T>(&ok);
#endif
}

struct MemoryManagerStatus
{
	uint32 Total;
	uint32 Free;
	uint32 Used;
	uint32 InternalFragmentation;	// Wasted

	size_t m_gccount;

	uint32 AllocSizes[24];
};

LFCEXT const MemoryManagerStatus& GetMemoryManagerStatus();

#if 1

class LFCEXT RefCountedObject : public Object
{
public:

	CTOR RefCountedObject()
	{
		m_refcount = 0;
	}

	ULONG AddRef();
	ULONG Release();

	ULONG m_refcount;
};

template<class T> class __release
{
public:

	CTOR __release()
	{
		m_p = NULL;
	}

	CTOR __release(T* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}

	inline CTOR __release(const __release<T>& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	template<class T2> inline CTOR __release(__release<T2>& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	~__release()
	{
		if (m_p) m_p->Release();
	}

	operator T* () const
	{
		return m_p;
	}

	/*
	operator const T* () const
	{
		return m_p;
	}
	*/

	T& operator * ()
	{
		return *m_p;
	}

	T* operator -> ()
	{
		return m_p;
	}

	const T* operator -> () const
	{
		return m_p;
	}

	__release& operator = (const __release& other)
	{
		T* old = m_p;
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
		if (old) old->Release();

		return *this;
	}

	T* m_p;
};

#endif

}

#include <math.h>
#include "gm/vector2.h"
#include "gm/vector3.h"
#include "gm/vector4.h"

namespace System
{
namespace gm
{

template<class TYPE> class Point
{
public:
	inline CTOR Point()
	{
		X = 0;
		Y = 0;
	}

	inline CTOR Point(TYPE x, TYPE y)
	{
		X = x;
		Y = y;
	}

#if WIN32
	inline CTOR Point(POINT pt)
	{
		X = pt.x;
		Y = pt.y;
	}
#endif

	inline CTOR Point(vector2<TYPE> src)
	{
		X = src[0];
		Y = src[1];
	}

	operator vector2<TYPE> () const
	{
		return vector2<TYPE>(X, Y);
	}

	inline Point<TYPE>& operator += (const Point<TYPE>& other)
	{
		X += other.X;
		Y += other.Y;
		return *this;
	}

	inline Point<TYPE>& operator -= (const Point<TYPE>& other)
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}

	inline Point<TYPE> operator + (const Point<TYPE>& other) const
	{
		return Point<TYPE>(X + other.X, Y + other.Y);
	}

	inline Point<TYPE> operator - (const Point<TYPE>& other) const
	{
		return Point<TYPE>(X - other.X, Y - other.Y);
	}

	inline Point<TYPE> operator - () const
	{
		return Point<TYPE>(-X, -Y);
	}

	inline Point<TYPE> operator * (int magnitude) const
	{
		return Point<TYPE>(TYPE(X * magnitude), TYPE(Y * magnitude));
	}

	inline Point<TYPE> operator * (float magnitude) const
	{
		return Point<TYPE>(TYPE(X * magnitude), TYPE(Y * magnitude));
	}

	inline Point<TYPE> operator * (double magnitude) const
	{
		return Point<TYPE>(TYPE(X * magnitude), TYPE(Y * magnitude));
	}

	inline Point<TYPE> operator / (int f) const
	{
		ASSERT(f != 0);
		return Point<TYPE>((TYPE)(X / f), (TYPE)(Y / f));
	}

	inline Point<TYPE> operator / (float f) const
	{
		ASSERT(f != 0);
		return Point<TYPE>((TYPE)(X / f), (TYPE)(Y / f));
	}

	inline Point<TYPE> operator / (double f) const
	{
		ASSERT(f != 0);
		return Point<TYPE>((TYPE)(X / f), (TYPE)(Y / f));
	}

	template<class TYPE2> inline Point<TYPE> operator / (Point<TYPE2> div) const
	{
		ASSERT(div.X != 0);
		ASSERT(div.Y != 0);
		return Point<TYPE>((TYPE)(X / div.X), (TYPE)(Y / div.X));
	}

	inline bool Equals(const Point<TYPE>& other) const
	{
		return (X == other.X && Y == other.Y);
	}

	bool Equals(const Point<TYPE>& other, TYPE tolerance) const
	{
		return abs(X - other.X) <= tolerance && abs(Y - other.Y) <= tolerance;
	}

	bool FuzzyEquals(const Point<TYPE>& other, TYPE tolerance) const
	{
		return abs(X - other.X) <= tolerance && abs(Y - other.Y) <= tolerance;
	}

	inline bool operator == (const Point<TYPE>& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Point<TYPE>& other) const
	{
		return !Equals(other);
	}

	inline TYPE& operator [] (int index)
	{
		ASSERT(index == 0 || index == 1);
		return (&X)[index];
	}

	inline TYPE operator [] (int index) const
	{
		ASSERT(index == 0 || index == 1);
		return (&X)[index];
	}

	inline Point<int> toInt() const
	{
		return Point<int>((int)X, (int)Y);
	}

	inline Point<float> toFloat() const
	{
		return Point<float>((float)X, (float)Y);
	}

	inline Point<double> toDouble() const
	{
		return Point<double>((double)X, (double)Y);
	}

	TYPE get_X() const
	{
		return X;
	}

	TYPE get_Y() const
	{
		return Y;
	}

	TYPE X;
	TYPE Y;
};

template<class TYPE> class Size
{
public:
	inline CTOR Size() : Width(0), Height(0)
	{
	}

	inline CTOR Size(TYPE _Width, TYPE _Height)
	{
		Width = _Width;
		Height = _Height;
	}

	inline CTOR Size(vector2<TYPE> src)
	{
		Width = src[0];
		Height = src[1];
	}

	operator vector2<TYPE> () const
	{
		return vector2<TYPE>(Width, Height);
	}

	inline Size<TYPE> operator + (const Size<TYPE>& other) const
	{
		return Size<TYPE>(Width + other.Width, Height + other.Height);
	}

	inline Size<TYPE> operator - (const Size<TYPE>& other) const
	{
		return Size<TYPE>(Width - other.Width, Height - other.Height);
	}

	inline Size<TYPE> operator * (int magnitude) const
	{
		return Size<TYPE>((TYPE)(Width * magnitude), (TYPE)(Height * magnitude));
	}

	inline Size<TYPE> operator * (float magnitude) const
	{
		return Size<TYPE>((TYPE)(Width * magnitude), (TYPE)(Height * magnitude));
	}

	inline Size<TYPE> operator * (double magnitude) const
	{
		return Size<TYPE>((TYPE)(Width * magnitude), (TYPE)(Height * magnitude));
	}

	inline Size<TYPE> operator * (const Size<TYPE>& m) const
	{
		return Size<TYPE>((TYPE)(Width * m.Width), (TYPE)(Height * m.Height));
	}

	inline Size<TYPE> operator / (int f) const
	{
		ASSERT(f != 0);
		return Size<TYPE>((TYPE)(Width / f), (TYPE)(Height / f));
	}

	inline Size<TYPE> operator / (float f) const
	{
		ASSERT(f != 0);
		return Size<TYPE>((TYPE)(Width / f), (TYPE)(Height / f));
	}

	inline Size<TYPE> operator / (double f) const
	{
		ASSERT(f != 0);
		return Size<TYPE>((TYPE)(Width / f), (TYPE)(Height / f));
	}

	inline bool Equals(const Size<TYPE>& other) const
	{
		return (Width == other.Width) && (Height == other.Height);
	}

	inline bool operator == (const Size<TYPE>& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Size<TYPE>& other) const
	{
		return !Equals(other);
	}

	TYPE get_Width() const
	{
		return Width;
	}

	TYPE get_Height() const
	{
		return Height;
	}

	TYPE Width;
	TYPE Height;
};

#ifndef __LERSTAD__

template<> class Size<double>
{
public:

	typedef double TYPE;

	inline CTOR Size() : Width(0), Height(0)
	{
	}

	inline CTOR Size(TYPE _Width, TYPE _Height)
	{
		Width = _Width;
		Height = _Height;
	}

	inline CTOR Size(vector2<TYPE> src)
	{
		Width = src[0];
		Height = src[1];
	}

	operator vector2<TYPE> () const
	{
		return vector2<TYPE>(Width, Height);
	}

	inline Size operator + (const Size<TYPE>& other) const
	{
		return Size(Width + other.Width, Height + other.Height);
	}

	inline Size operator - (const Size<TYPE>& other) const throw()
	{
		return Size(Width - other.Width, Height - other.Height);
	}

	inline Size operator * (double magnitude) const throw()
	{
		return Size(Width * magnitude, Height * magnitude);
	}

	template<class T2>
	inline Size operator * (const Size<T2>& m) const throw()
	{
		return Size(Width * m.Width, Height * m.Height);
	}

	inline Size<TYPE> operator / (double f) const
	{
		ASSERT(f != 0);
		return Size(Width / f, Height / f);
	}

	inline bool Equals(const Size& other) const
	{
		return (Width == other.Width) && (Height == other.Height);
	}

	inline bool operator == (const Size& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Size<TYPE>& other) const
	{
		return !Equals(other);
	}

	TYPE get_Width() const throw()
	{
		return Width;
	}

	TYPE get_Height() const throw()
	{
		return Height;
	}

	TYPE Width;
	TYPE Height;
};

template<> class Size<float>
{
public:

	typedef float TYPE;

	inline CTOR Size() throw() : Width(0), Height(0)
	{
	}

	inline CTOR Size(TYPE _Width, TYPE _Height) throw()
	{
		Width = _Width;
		Height = _Height;
	}

	inline CTOR Size(vector2<TYPE> src) throw()
	{
		Width = src[0];
		Height = src[1];
	}

	operator vector2<TYPE> () const
	{
		return vector2<TYPE>(Width, Height);
	}

	inline Size<TYPE> operator + (const Size<TYPE>& other) const
	{
		return Size<TYPE>(Width + other.Width, Height + other.Height);
	}

	inline Size<TYPE> operator - (const Size<TYPE>& other) const
	{
		return Size<TYPE>(Width - other.Width, Height - other.Height);
	}

	inline Size<float> operator * (int magnitude) const
	{
		return Size<float>(Width * magnitude, Height * magnitude);
	}

	inline Size<float> operator * (float magnitude) const
	{
		return Size<float>(Width * magnitude, Height * magnitude);
	}

	inline Size<double> operator * (double magnitude) const
	{
		return Size<double>(Width * magnitude, Height * magnitude);
	}

	inline Size<TYPE> operator * (const Size<TYPE>& m) const
	{
		return Size<TYPE>((TYPE)(Width * m.Width), (TYPE)(Height * m.Height));
	}

	inline Size<float> operator / (int f) const
	{
		ASSERT(f != 0);
		return Size<float>(Width / f, Height / f);
	}

	inline Size<float> operator / (float f) const
	{
		ASSERT(f != 0);
		return Size<float>(Width / f, Height / f);
	}

	inline Size<double> operator / (double f) const
	{
		ASSERT(f != 0);
		return Size<double>(Width / f, Height / f);
	}

	inline bool Equals(const Size& other) const
	{
		return (Width == other.Width) && (Height == other.Height);
	}

	inline bool operator == (const Size& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Size<TYPE>& other) const
	{
		return !Equals(other);
	}

	TYPE get_Width() const
	{
		return Width;
	}

	TYPE get_Height() const
	{
		return Height;
	}

	TYPE Width;
	TYPE Height;
};

template<> class Size<int>
{
public:

	typedef int TYPE;

	inline CTOR Size() : Width(0), Height(0)
	{
	}

	inline CTOR Size(TYPE _Width, TYPE _Height)
	{
		Width = _Width;
		Height = _Height;
	}

	inline CTOR Size(vector2<TYPE> src)
	{
		Width = src[0];
		Height = src[1];
	}

	operator vector2<TYPE> () const
	{
		return vector2<TYPE>(Width, Height);
	}

	inline Size<TYPE> operator + (const Size<TYPE>& other) const
	{
		return Size<TYPE>(Width + other.Width, Height + other.Height);
	}

	inline Size<TYPE> operator - (const Size<TYPE>& other) const
	{
		return Size<TYPE>(Width - other.Width, Height - other.Height);
	}

	inline Size<int> operator * (int magnitude) const
	{
		return Size<int>(Width * magnitude, Height * magnitude);
	}

	inline Size<float> operator * (float magnitude) const
	{
		return Size<float>(Width * magnitude, Height * magnitude);
	}

	inline Size<double> operator * (double magnitude) const
	{
		return Size<double>(Width * magnitude, Height * magnitude);
	}

	inline Size<TYPE> operator * (const Size<TYPE>& m) const
	{
		return Size<TYPE>((TYPE)(Width * m.Width), (TYPE)(Height * m.Height));
	}

	inline Size<int> operator / (int f) const
	{
		ASSERT(f != 0);
		return Size<int>(Width / f, Height / f);
	}

	inline Size<float> operator / (float f) const
	{
		ASSERT(f != 0);
		return Size<float>(Width / f, Height / f);
	}

	inline Size<double> operator / (double f) const
	{
		ASSERT(f != 0);
		return Size<double>(Width / f, Height / f);
	}

	inline bool Equals(const Size<TYPE>& other) const
	{
		return (Width == other.Width) && (Height == other.Height);
	}

	inline bool operator == (const Size<TYPE>& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Size<TYPE>& other) const
	{
		return !Equals(other);
	}

	TYPE get_Width() const throw()
	{
		return Width;
	}

	TYPE get_Height() const throw()
	{
		return Height;
	}

	TYPE Width;
	TYPE Height;
};
#endif


typedef Point<int> PointI;
typedef Point<float> PointF;
typedef Point<double> PointD;

typedef Size<int> Sizei;
typedef Size<int> SizeI;
typedef Size<float> SizeF;
typedef Size<double> SizeD;

template<class TYPE> class Rect
{
public:

	inline CTOR Rect() : X(0), Y(0), Width(0), Height(0)
	{
	}

	inline CTOR Rect(const Rect<TYPE>& rect)
	{
		X = rect.X;
		Y = rect.Y;
		Width = rect.Width;
		Height = rect.Height;
	}

	inline CTOR Rect(TYPE x, TYPE y, TYPE _Width, TYPE _Height)  throw()
	{
		X = x;
		Y = y;
		Width = _Width;
		Height = _Height;
	}

	inline CTOR Rect(const Point<TYPE>& topleft, const Size<TYPE>& size)  throw()
	{
		X = topleft.X;
		Y = topleft.Y;
		Width = size.Width;
		Height = size.Height;
	}

	inline CTOR Rect(const Point<TYPE>& topleft, const Point<TYPE>& bottomright)  throw()
	{
		X = topleft.X;
		Y = topleft.Y;
		Width = bottomright.X - topleft.X;
		Height = bottomright.Y - topleft.Y;
	}

	inline CTOR Rect(const vector4<TYPE>& src)
	{
		X = src[0];
		Y = src[1];
		Width = src[2];
		Height = src[3];
	}

	operator vector4<TYPE> () const
	{
		return vector4<TYPE>(X, Y, Width, Height);
	}

	inline TYPE GetLeft() const throw()
	{
		return X;
	}

	inline TYPE GetTop() const throw()
	{
		return Y;
	}

	inline TYPE GetRight() const throw()
	{
		return X+Width;
	}

	inline TYPE GetBottom() const throw()
	{
		return Y+Height;
	}

	inline Point<TYPE> GetTopLeft() const throw()
	{
		return Point<TYPE>(X, Y);
	}

	inline Point<TYPE> GetBottomRight() const throw()
	{
		return Point<TYPE>(X+Width, Y+Height);
	}

	inline Size<TYPE> GetSize() const throw()
	{
		return Size<TYPE>(Width, Height);
	}

	void Normalize() throw()
	{
		if (Width < 0)
		{
			X += Width;
			Width = -Width;
		}

		if (Height < 0)
		{
			Y += Height;
			Height = -Height;
		}
	}

	bool Contains(TYPE x, TYPE y) const throw()
	{
		return (x >= X) && (y >= Y) && (x < X+Width) && (y < Y+Height);
	}

	bool Contains(Point<TYPE>& pt) const throw()
	{
		return (pt.X >= X) && (pt.Y >= Y) && (pt.X < X+Width) && (pt.Y < Y+Height);
	}

	inline void Translate(TYPE dx, TYPE dy) throw()
	{
		X += dx;
		Y += dy;
	}

	inline void Translate(const Point<TYPE>& pt) throw()
	{
		X += pt.X;
		Y += pt.Y;
	}

	template<class T> inline Rect& operator *= (T scale)
	{
		X *= scale;
		Y *= scale;
		Width *= scale;
		Height *= scale;
		return *this;
	}

	inline void Inflate(TYPE dx, TYPE dy)
	{
		X -= dx;
		Y -= dy;
		Width += dx*2;
		Height += dy*2;
	}

	inline void Inflate(TYPE l, TYPE t, TYPE r, TYPE b)
	{
		X -= l;
		Y -= t;
		Width += l+r;
		Height += t+b;
	}

	inline bool IsEmpty() const throw()
	{
		return (Width <= 0) || (Height <= 0);
	}

	inline bool IsEmptyArea() const throw()
	{
		return (Width <= 0) || (Height <= 0);
	}

	TYPE Area() const
	{
		return Width*Height;
	}

	/*
	TYPE DiagonalLength() const
	{
		TYPE dx =
		return sqrt(;
	}
	*/

	bool Equals(const Rect& other) const
	{
		return (	X == other.X &&
					Y == other.Y &&
					Width == other.Width &&
					Height == other.Height);
	}

	static bool Intersect(/*OUT*/ Rect& c,
		/*IN*/ const Rect& a,
		/*IN*/ const Rect& b)
	{
		TYPE right = MIN(a.GetRight(), b.GetRight());
		TYPE bottom = MIN(a.GetBottom(), b.GetBottom());
		TYPE left = MAX(a.GetLeft(), b.GetLeft());
		TYPE top = MAX(a.GetTop(), b.GetTop());

		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	static bool Union(Rect& c, const Rect& a, const Rect& b)
	{
		TYPE right = MAX(a.GetRight(), b.GetRight());
		TYPE bottom = MAX(a.GetBottom(), b.GetBottom());
		TYPE left = MIN(a.GetLeft(), b.GetLeft());
		TYPE top = MIN(a.GetTop(), b.GetTop());
		
		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	template<class TYPE2> inline bool IntersectsWith(const Rect<TYPE2>& rect) const
	{
		return (GetLeft() < rect.GetRight() &&
			GetTop() < rect.GetBottom() &&
			GetRight() > rect.GetLeft() &&
			GetBottom() > rect.GetTop());
	}

	inline Rect<int> ToRectI() const
	{
		return Rect<int>(X, Y, Width, Height);
	}

	inline Rect<float> ToRectF() const
	{
		return Rect<float>(X, Y, Width, Height);
	}

	inline Rect<double> ToRectD() const
	{
		return Rect<double>(X, Y, Width, Height);
	}

	inline bool operator == (const Rect<TYPE>& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Rect<TYPE>& other) const
	{
		return !Equals(other);
	}

	TYPE X;
	TYPE Y;
	TYPE Width;
	TYPE Height;
};

#ifndef __LERSTAD__
template<> class Rect<int>;
template<> class Rect<float>;
template<> class Rect<double>;

template<> class Rect<double>
{
public:
	typedef double TYPE;

	inline CTOR Rect() : X(0), Y(0), Width(0), Height(0)
	{
	}

	inline CTOR Rect(const Rect<TYPE>& rect)
	{
		X = rect.X;
		Y = rect.Y;
		Width = rect.Width;
		Height = rect.Height;
	}

	inline CTOR Rect(TYPE x, TYPE y, TYPE _Width, TYPE _Height)  throw()
	{
		X = x;
		Y = y;
		Width = _Width;
		Height = _Height;
	}

	inline CTOR Rect(const Point<TYPE>& topleft, const Size<TYPE>& size)  throw()
	{
		X = topleft.X;
		Y = topleft.Y;
		Width = size.Width;
		Height = size.Height;
	}

	inline CTOR Rect(const Point<TYPE>& topleft, const Point<TYPE>& bottomright)  throw()
	{
		X = topleft.X;
		Y = topleft.Y;
		Width = bottomright.X - topleft.X;
		Height = bottomright.Y - topleft.Y;
	}

	inline CTOR Rect(const vector4<TYPE>& src)
	{
		X = src[0];
		Y = src[1];
		Width = src[2];
		Height = src[3];
	}

	operator vector4<TYPE> () const
	{
		return vector4<TYPE>(X, Y, Width, Height);
	}

	inline TYPE GetLeft() const throw()
	{
		return X;
	}

	inline TYPE GetTop() const throw()
	{
		return Y;
	}

	inline TYPE GetRight() const throw()
	{
		return X+Width;
	}

	inline TYPE GetBottom() const throw()
	{
		return Y+Height;
	}

	inline Point<TYPE> GetTopLeft() const throw()
	{
		return Point<TYPE>(X, Y);
	}

	inline Point<TYPE> GetBottomRight() const throw()
	{
		return Point<TYPE>(X+Width, Y+Height);
	}

	inline Size<TYPE> GetSize() const throw()
	{
		return Size<TYPE>(Width, Height);
	}

	void Normalize() throw()
	{
		if (Width < 0)
		{
			X += Width;
			Width = -Width;
		}

		if (Height < 0)
		{
			Y += Height;
			Height = -Height;
		}
	}

	bool Contains(TYPE x, TYPE y) const throw()
	{
		return (x >= X) && (y >= Y) && (x < X+Width) && (y < Y+Height);
	}

	bool Contains(Point<TYPE>& pt) const throw()
	{
		return (pt.X >= X) && (pt.Y >= Y) && (pt.X < X+Width) && (pt.Y < Y+Height);
	}

	inline void Translate(TYPE dx, TYPE dy) throw()
	{
		X += dx;
		Y += dy;
	}

	inline void Translate(const Point<TYPE>& pt) throw()
	{
		X += pt.X;
		Y += pt.Y;
	}

	template<class _T, class T> inline Rect<_T> operator * (T scale) const;
	/*
	{
		return Rect<TYPE>(X*scale, Y*scale, Width*scale, Height*scale);
	}
	*/

	template<class T> inline Rect& operator *= (T scale)
	{
		X *= scale;
		Y *= scale;
		Width *= scale;
		Height *= scale;
		return *this;
	}

	inline void Inflate(double dx, double dy)
	{
		X -= dx;
		Y -= dy;
		Width += dx*2;
		Height += dy*2;
	}

	inline void Inflate(double l, double t, double r, double b)
	{
		X -= l;
		Y -= t;
		Width += l+r;
		Height += t+b;
	}

	inline bool IsEmpty() const throw()
	{
		return (Width <= 0) || (Height <= 0);
	}

	inline bool IsEmptyArea() const throw()
	{
		return (Width <= 0) || (Height <= 0);
	}

	bool Equals(const Rect& other) const
	{
		return (	X == other.X &&
					Y == other.Y &&
					Width == other.Width &&
					Height == other.Height);
	}

	static bool Intersect(/*OUT*/ Rect& c,
		/*IN*/ const Rect& a,
		/*IN*/ const Rect& b)
	{
		TYPE right = MIN(a.GetRight(), b.GetRight());
		TYPE bottom = MIN(a.GetBottom(), b.GetBottom());
		TYPE left = MAX(a.GetLeft(), b.GetLeft());
		TYPE top = MAX(a.GetTop(), b.GetTop());

		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	static bool Union(Rect& c, const Rect& a, const Rect& b)
	{
		TYPE right = MAX(a.GetRight(), b.GetRight());
		TYPE bottom = MAX(a.GetBottom(), b.GetBottom());
		TYPE left = MIN(a.GetLeft(), b.GetLeft());
		TYPE top = MIN(a.GetTop(), b.GetTop());
		
		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	template<class TYPE2> inline bool IntersectsWith(const Rect<TYPE2>& rect) const
	{
		return (GetLeft() < rect.GetRight() &&
			GetTop() < rect.GetBottom() &&
			GetRight() > rect.GetLeft() &&
			GetBottom() > rect.GetTop());
	}

	template<class T>
	inline Rect<T> ToRect() const
	{
		return Rect<T>(X, Y, Width, Height);
	}

	inline bool operator == (const Rect& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Rect& other) const
	{
		return !Equals(other);
	}

	TYPE X;
	TYPE Y;
	TYPE Width;
	TYPE Height;
};

template<> class Rect<float>
{
public:
	typedef float TYPE;

	inline CTOR Rect() : X(0), Y(0), Width(0), Height(0)
	{
	}

	inline CTOR Rect(const Rect<TYPE>& rect)
	{
		X = rect.X;
		Y = rect.Y;
		Width = rect.Width;
		Height = rect.Height;
	}

#if WIN32
	CTOR Rect(const RECT& rect)  throw();
	operator RECT () const throw();
#endif

	inline CTOR Rect(TYPE x, TYPE y, TYPE _Width, TYPE _Height)  throw()
	{
		X = x;
		Y = y;
		Width = _Width;
		Height = _Height;
	}

	inline CTOR Rect(const Point<TYPE>& topleft, const Size<TYPE>& size)  throw()
	{
		X = topleft.X;
		Y = topleft.Y;
		Width = size.Width;
		Height = size.Height;
	}

	inline CTOR Rect(const Point<TYPE>& topleft, const Point<TYPE>& bottomright)  throw()
	{
		X = topleft.X;
		Y = topleft.Y;
		Width = bottomright.X - topleft.X;
		Height = bottomright.Y - topleft.Y;
	}

	inline CTOR Rect(const vector4<TYPE>& src)
	{
		X = src[0];
		Y = src[1];
		Width = src[2];
		Height = src[3];
	}

	operator vector4<TYPE> () const
	{
		return vector4<TYPE>(X, Y, Width, Height);
	}

	inline TYPE GetLeft() const throw()
	{
		return X;
	}

	inline TYPE GetTop() const throw()
	{
		return Y;
	}

	inline TYPE GetRight() const throw()
	{
		return X+Width;
	}

	inline TYPE GetBottom() const throw()
	{
		return Y+Height;
	}

	inline Point<TYPE> GetTopLeft() const throw()
	{
		return Point<TYPE>(X, Y);
	}

	inline Point<TYPE> GetBottomRight() const throw()
	{
		return Point<TYPE>(X+Width, Y+Height);
	}

	inline Size<TYPE> GetSize() const throw()
	{
		return Size<TYPE>(Width, Height);
	}

	void Normalize() throw()
	{
		if (Width < 0)
		{
			X += Width;
			Width = -Width;
		}

		if (Height < 0)
		{
			Y += Height;
			Height = -Height;
		}
	}

	bool Contains(TYPE x, TYPE y) const throw()
	{
		return (x >= X) && (y >= Y) && (x < X+Width) && (y < Y+Height);
	}

	bool Contains(Point<TYPE>& pt) const throw()
	{
		return (pt.X >= X) && (pt.Y >= Y) && (pt.X < X+Width) && (pt.Y < Y+Height);
	}

	inline void Translate(TYPE dx, TYPE dy) throw()
	{
		X += dx;
		Y += dy;
	}

	inline void Translate(const Point<TYPE>& pt) throw()
	{
		X += pt.X;
		Y += pt.Y;
	}

	inline Rect<float> operator * (float scale) const throw();
	inline Rect<double> operator * (double scale) const throw();
	inline Rect<float> operator / (float scale) const;
	inline Rect<double> operator / (double scale) const;

	inline void Inflate(TYPE dx, TYPE dy)
	{
		X -= dx;
		Y -= dy;
		Width += dx*2;
		Height += dy*2;
	}

	inline void Inflate(TYPE l, TYPE t, TYPE r, TYPE b)
	{
		X -= l;
		Y -= t;
		Width += l+r;
		Height += t+b;
	}

	inline bool IsEmpty() const throw()
	{
		return (Width <= 0) || (Height <= 0);
	}

	inline bool IsEmptyArea() const throw()
	{
		return (Width <= 0) || (Height <= 0);
	}

	bool Equals(const Rect& other) const
	{
		return (	X == other.X &&
					Y == other.Y &&
					Width == other.Width &&
					Height == other.Height);
	}

	static bool Intersect(/*OUT*/ Rect& c,
		/*IN*/ const Rect& a,
		/*IN*/ const Rect& b)
	{
		TYPE right = MIN(a.GetRight(), b.GetRight());
		TYPE bottom = MIN(a.GetBottom(), b.GetBottom());
		TYPE left = MAX(a.GetLeft(), b.GetLeft());
		TYPE top = MAX(a.GetTop(), b.GetTop());

		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	static bool Union(Rect& c, const Rect& a, const Rect& b)
	{
		TYPE right = MAX(a.GetRight(), b.GetRight());
		TYPE bottom = MAX(a.GetBottom(), b.GetBottom());
		TYPE left = MIN(a.GetLeft(), b.GetLeft());
		TYPE top = MIN(a.GetTop(), b.GetTop());
		
		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	template<class TYPE2> inline bool IntersectsWith(const Rect<TYPE2>& rect) const
	{
		return (GetLeft() < rect.GetRight() &&
			GetTop() < rect.GetBottom() &&
			GetRight() > rect.GetLeft() &&
			GetBottom() > rect.GetTop());
	}

	template<class T>
	inline Rect<T> ToRect() const
	{
		return Rect<T>(X, Y, Width, Height);
	}

	inline bool operator == (const Rect<TYPE>& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Rect<TYPE>& other) const
	{
		return !Equals(other);
	}

	TYPE X;
	TYPE Y;
	TYPE Width;
	TYPE Height;
};

template<> class Rect<int>
{
public:
	typedef int TYPE;

	inline CTOR Rect() : X(0), Y(0), Width(0), Height(0)
	{
	}

	inline CTOR Rect(const Rect<TYPE>& rect)
	{
		X = rect.X;
		Y = rect.Y;
		Width = rect.Width;
		Height = rect.Height;
	}

#if WIN32
	inline CTOR Rect(const RECT& rect)
	{
		X = rect.left;
		Y = rect.top;
		Width = rect.right - rect.left;
		Height = rect.bottom - rect.top;
	}

	inline operator RECT () const
	{
		RECT rect;
		rect.left = X;
		rect.top = Y;
		rect.right = GetRight();
		rect.bottom = GetBottom();

		return rect;
	}
#endif

	inline CTOR Rect(int x, int y, int _Width, int _Height)  throw()
	{
		X = x;
		Y = y;
		Width = _Width;
		Height = _Height;
	}

	inline CTOR Rect(const Point<TYPE>& topleft, const Size<TYPE>& size)  throw()
	{
		X = topleft.X;
		Y = topleft.Y;
		Width = size.Width;
		Height = size.Height;
	}

	inline CTOR Rect(const Point<TYPE>& topleft, const Point<TYPE>& bottomright)  throw()
	{
		X = topleft.X;
		Y = topleft.Y;
		Width = bottomright.X - topleft.X;
		Height = bottomright.Y - topleft.Y;
	}

	inline CTOR Rect(const vector4<TYPE>& src)
	{
		X = src[0];
		Y = src[1];
		Width = src[2];
		Height = src[3];
	}

	operator vector4<TYPE> () const
	{
		return vector4<TYPE>(X, Y, Width, Height);
	}

	inline TYPE GetLeft() const throw()
	{
		return X;
	}

	inline TYPE GetTop() const throw()
	{
		return Y;
	}

	inline TYPE GetRight() const throw()
	{
		return X+Width;
	}

	inline TYPE GetBottom() const throw()
	{
		return Y+Height;
	}

	inline Point<TYPE> GetTopLeft() const throw()
	{
		return Point<TYPE>(X, Y);
	}

	inline Point<TYPE> GetBottomRight() const throw()
	{
		return Point<TYPE>(X+Width, Y+Height);
	}

	inline Size<TYPE> GetSize() const throw()
	{
		return Size<TYPE>(Width, Height);
	}

	void Normalize() throw()
	{
		if (Width < 0)
		{
			X += Width;
			Width = -Width;
		}

		if (Height < 0)
		{
			Y += Height;
			Height = -Height;
		}
	}

	template<class arg_t>
	bool Contains(arg_t x, arg_t y) const throw()
	{
		return (x >= X) && (y >= Y) && (x < X+Width) && (y < Y+Height);
	}

	template<class arg_t>
	bool Contains(Point<arg_t>& pt) const throw()
	{
		return (pt.X >= X) && (pt.Y >= Y) && (pt.X < X+Width) && (pt.Y < Y+Height);
	}

	inline void Translate(TYPE dx, TYPE dy) throw()
	{
		X += dx;
		Y += dy;
	}

	inline void Translate(const Point<TYPE>& pt) throw()
	{
		X += pt.X;
		Y += pt.Y;
	}

	inline Rect<int> operator * (int scale) const throw()
	{
		return Rect<int>(X*scale, Y*scale, Width*scale, Height*scale);
	}

	inline Rect<float> operator * (float scale) const throw();
	inline Rect<double> operator * (double scale) const throw();

	inline Rect<int> operator / (int scale) const
	{
		return Rect<int>(X/scale, Y/scale, Width/scale, Height/scale);
	}

	inline Rect<float> operator / (float scale) const;
	inline Rect<double> operator / (double scale) const;

	template<class T> inline Rect& operator *= (T scale) throw()
	{
		X *= scale;
		Y *= scale;
		Width *= scale;
		Height *= scale;
		return *this;
	}

	template<class T> inline Rect& operator /= (T scale) throw()
	{
		X *= scale;
		Y *= scale;
		Width *= scale;
		Height *= scale;
		return *this;
	}

	inline void Inflate(TYPE dx, TYPE dy)
	{
		X -= dx;
		Y -= dy;
		Width += dx*2;
		Height += dy*2;
	}

	inline void Inflate(TYPE l, TYPE t, TYPE r, TYPE b)
	{
		X -= l;
		Y -= t;
		Width += l+r;
		Height += t+b;
	}

	inline bool IsEmpty() const throw()
	{
		return (Width <= 0) || (Height <= 0);
	}

	inline bool IsEmptyArea() const throw()
	{
		return (Width <= 0) || (Height <= 0);
	}

	bool Equals(const Rect& other) const
	{
		return (	X == other.X &&
					Y == other.Y &&
					Width == other.Width &&
					Height == other.Height);
	}

	static bool Intersect(/*OUT*/ Rect& c,
		/*IN*/ const Rect& a,
		/*IN*/ const Rect& b)
	{
		TYPE right = MIN(a.GetRight(), b.GetRight());
		TYPE bottom = MIN(a.GetBottom(), b.GetBottom());
		TYPE left = MAX(a.GetLeft(), b.GetLeft());
		TYPE top = MAX(a.GetTop(), b.GetTop());

		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	static bool Union(Rect& c, const Rect& a, const Rect& b)
	{
		TYPE right = MAX(a.GetRight(), b.GetRight());
		TYPE bottom = MAX(a.GetBottom(), b.GetBottom());
		TYPE left = MIN(a.GetLeft(), b.GetLeft());
		TYPE top = MIN(a.GetTop(), b.GetTop());
		
		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	template<class TYPE2> inline bool IntersectsWith(const Rect<TYPE2>& rect) const
	{
		return (GetLeft() < rect.GetRight() &&
			GetTop() < rect.GetBottom() &&
			GetRight() > rect.GetLeft() &&
			GetBottom() > rect.GetTop());
	}

	template<class T>
	inline Rect<T> ToRect() const
	{
		return Rect<T>(X, Y, Width, Height);
	}

	inline bool operator == (const Rect& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Rect& other) const
	{
		return !Equals(other);
	}

	TYPE X;
	TYPE Y;
	TYPE Width;
	TYPE Height;
};

// Rect<int>

inline Rect<float> Rect<int>::operator * (float scale) const throw()
{
	return Rect<float>(X*scale, Y*scale, Width*scale, Height*scale);
}

inline Rect<double> Rect<int>::operator * (double scale) const throw()
{
	return Rect<double>(X*scale, Y*scale, Width*scale, Height*scale);
}

inline Rect<float> Rect<int>::operator / (float scale) const
{
	float r = 1.0f/scale;
	return Rect<float>(X*r, Y*r, Width*r, Height*r);
}

inline Rect<double> Rect<int>::operator / (double scale) const
{
	double r = 1.0/scale;
	return Rect<double>(X*r, Y*r, Width*r, Height*r);
}

// Rect<float>

inline Rect<float> Rect<float>::operator * (float scale) const throw()
{
	return Rect<float>(X*scale, Y*scale, Width*scale, Height*scale);
}

inline Rect<double> Rect<float>::operator * (double scale) const throw()
{
	return Rect<double>(X*scale, Y*scale, Width*scale, Height*scale);
}

inline Rect<float> Rect<float>::operator / (float scale) const
{
	float r = 1.0f/scale;
	return Rect<float>(X*r, Y*r, Width*r, Height*r);
}

inline Rect<double> Rect<float>::operator / (double scale) const
{
	double r = 1.0/scale;
	return Rect<double>(X*r, Y*r, Width*r, Height*r);
}

#endif

/*
typedef decltype(1 * .0f)   int_mul_float_t;		// float
typedef decltype(1 * .0)	    int_mul_double_t;	// double
*/

typedef Rect<int> Recti;
typedef Rect<int> RectI;

typedef Rect<float> Rectf;
typedef Rect<float> RectF;

typedef Rect<double> Rectd;
typedef Rect<double> RectD;

//template bool Rect<float>::IntersectsWith(const Rect<double>&);

}	// gm
}

//#ifdef _MSC_VER
#if WIN32
#define __DECLSPEC_ALIGN_16__ __declspec(align(16))
#else
#define __DECLSPEC_ALIGN_16__
#endif

#include "gm/Matrix3f.h"
#include "gm/Matrix3d.h"
#include "gm/Matrix4f.h"

#include "Archive.h"
#include "BitStream.h"

namespace System
{

class LFCEXT DispatchMsg
{
public:

	CTOR DispatchMsg() :
		m_object(nullptr),
		m_dispatch(nullptr),
		m_method(nullptr),
		m_args(nullptr),
		m_exception(nullptr),
		retval_struct(nullptr)
	{
		caller.m_hWaitEvent = nullptr;
		caller.m_hThread = nullptr;
	}

	// method call
	void* m_object;
	Dispatch* m_dispatch;
	union
	{
		Declarator* m_method;

	// function call
		Declarator* m_func;
	};

	ubyte* m_args;
	Exception* m_exception;
	void* retval_struct;
	VariantValue retval;

	struct
	{
		HANDLE m_hWaitEvent;
		HANDLE m_hThread;
		DWORD m_threadId;
	}
	caller;

	int m_kind;
	uint m_args_nbytes;
};

class LFCEXT DispatcherObject : public Object
{
public:

	CTOR DispatcherObject();

#ifndef __LERSTAD__

	template<class class_type, class arg0_type>
	inline void DispatchCall(void (class_type::*memfun)(arg0_type), arg0_type arg0)
	{
		if (GetCurrentThreadId() != m_threadId)
		{
		}
	}

	template<class class_type, class arg0_type>
	inline int DispatchCall(int (class_type::*memfun)(arg0_type), arg0_type arg0)
	{
		if (GetCurrentThreadId() != m_threadId)
		{
		}
	}

	template<class class_type, class arg0_type>
	inline float DispatchCall(float (class_type::*memfun)(arg0_type), arg0_type arg0)
	{
		if (GetCurrentThreadId() != m_threadId)
		{
		}
	}

#endif

	// TODO, not like this
	HANDLE m_hThread;
	DWORD m_threadId;
};

enum CharacterEncoding
{
	Latin,
	Utf8,
	Utf16,
	Utf32,
};

class LFCEXT CharacterStream
{
public:
	CTOR CharacterStream(CharacterEncoding encoding, const void* data, unsigned int length)
	{
		m_encoding = encoding;
		m_data = data;
		m_p = (const uint8*)m_data;

		switch (m_encoding)
		{
		case Latin:
			m_bytelength = length;
			break;

		case Utf16:
			m_bytelength = length*2;
			break;

		case Utf32:
			m_bytelength = length*4;
			break;
		}
	}

	const void* m_data;
	const unsigned char* m_p;
	CharacterEncoding m_encoding;
	unsigned int m_bytelength;

	bool AtEnd() const
	{
		return !(m_p < (uint8*)m_data + m_bytelength);
	}

	uint32 GetChar();
};

interface IFrameContext
{
	virtual Variant GetVariable(StringIn name) = 0;
};

LFCEXT Type* ToType(Type* p);

/*
struct ProcessorFeatures
{
	bool _3DNOW_INSTRUCTIONS_AVAILABLE : 1;
	bool _CHANNELS_ENABLED : 1;
	bool _PF_COMPARE_EXCHANGE_DOUBLE : 1;
	bool _PF_COMPARE_EXCHANGE128 : 1;
	bool _PF_COMPARE64_EXCHANGE128 : 1;
	bool _COMPARE64_EXCHANGE128 : 1;
	bool _FLOATING_POINT_EMULATED : 1;
};
*/

}

#include "Environment.h"

namespace System
{

LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& stream, Type* pType);
LFCEXT IO::TextWriter& printArg(IO::TextWriter& stream, TemplatedClassArg* p, NamespaceType* pNamespaceType);
LFCEXT IO::TextWriter& print(IO::TextWriter& fp, _TemplateArgType* pType);
LFCEXT IO::TextWriter& print(IO::TextWriter& fp, Declarator* pDeclarator, FunctionType* pType, NamespaceType* pNamespaceType);
LFCEXT IO::TextWriter& printClass(IO::TextWriter& fp, ClassType* pClass, int levels, NamespaceType* pNamespaceType = NULL);

LFCEXT void print(Namespace* pNamespace);
LFCEXT void print(ClassType* pClass);
LFCEXT void print(EnumType* pEnum);
LFCEXT void printProperties(ClassType* pClass);
LFCEXT void printProperties(Object* pObj);

class LFCEXT Real
{
public:

	static int floor(float value);
	static int ceil(float value);
};

template<class list_type> size_t Count(list_type* listp)
{
	size_t count = 0;
	while (listp)
	{
		++count;
		listp = listp->tail;
	}

	return count;
}

template<class list_type> list_type* Reverse(list_type* listp, list_type* prev = NULL)
{
	while (listp)
	{
		list_type* next = listp->tail;

		listp->tail = prev;
		prev = listp;
		listp = next;
	}

	return prev;
}

template<class list_type> list_type* Join(list_type* a, list_type* b)
{
	if (a == nullptr) return b;

	list_type* _a = a;
	while (_a->tail)
	{
		_a = _a->tail;
	}
	_a->tail = b;
	return a;
}

}	// System

#include "MSWindows.h"
#include "crc32.h"

namespace System
{

class LFCEXT ThrowHr
{
public:
	CTOR ThrowHr() throw() : m_hr(0)
	{
	}

	CTOR ThrowHr(HRESULT hr) : m_hr(hr)
	{
		if (FAILED(hr))
		{
			raise_(Exception::FromHResult(hr));
		}
	}

	ThrowHr& operator = (HRESULT hr)
	{
		m_hr = hr;

		if (FAILED(hr))
		{
			raise_(Exception::FromHResult(hr));
		}
		return *this;
	}

	bool Succeeded() const throw()
	{
		return SUCCEEDED(m_hr);
	}

	bool Failed() const throw()
	{
		return FAILED(m_hr);
	}

	bool operator == (HRESULT hr) const throw()
	{
		return m_hr == hr;
	}

	bool operator != (HRESULT hr) const throw()
	{
		return m_hr != hr;
	}

	operator bool () const throw()
	{
		return m_hr == S_OK;
	}

	bool operator ! () const throw()
	{
		return (m_hr == S_FALSE)? true: false;
	}

	operator HRESULT () const throw()
	{
		return m_hr;
	}

	HRESULT m_hr;
};

}

#include "ComBSTR.h"
#include "ComPtr.h"
#include "ComVariant.h"

namespace System
{

interface IDictionary
{
	virtual void SetKeyValue(Object* key, Object* value) abstract;
	virtual Object* GetValue(Object* key) abstract;
//	virtual bool HasValue(Object* key) abstract;
};

class LFCEXT Dictionary : public Object, public IDictionary
{
public:
	virtual void SetKeyValue(Object* key, Object* value) override;
	virtual Object* GetValue(Object* key) override;
//	virtual bool HasValue(Object* key) override;

	unordered_map<Object*, Object*> m_dict;
};

interface IHasMimetype
{
	virtual String get_Mimetype() abstract;
	virtual void set_Mimetype(StringIn mimetype) abstract;
};

interface IHasUserData
{
	virtual Object* GetUserData(Object* key) abstract;
	virtual void SetUserData(Object* key, Object* value) abstract;
};

class LFCEXT ConstantPool : public Object
{
public:
	vector<Variant> m_constantPool;
};

LFCEXT Object* GetUserData(Object* obj, Object* key);
LFCEXT void SetUserData(Object* obj, Object* key, Object* value);

LFCEXT void PrintOffsets(IO::TextWriter& stream, ClassType* pClass);

LFCEXT String CurrentDir();
LFCEXT bool ChangeDir(StringIn path);

LFCEXT uint GetAppLockCount();
LFCEXT uint IncAppLockCount();
LFCEXT uint DecAppLockCount();

/*
class FileInfo : public Object
{
public:
	PathName pathname;
};
*/

LFCEXT Type* DemangleNameVC(Namespace* pGlobalNamespace, bool x64, const char* str);

LFCEXT List<String>* FindFiles(StringIn filename);

LFCEXT void WriteNumberAndNull(char* dst, signed char num, uint base = 10);
LFCEXT void WriteNumberAndNull(char* dst, unsigned char num, uint base = 10);
LFCEXT void WriteNumberAndNull(char* dst, int num, uint base = 10);
LFCEXT void WriteNumberAndNull(char* dst, unsigned int num, uint base = 10);
LFCEXT void WriteNumberAndNull(char* dst, long num, uint base = 10);
LFCEXT void WriteNumberAndNull(char* dst, unsigned long num, uint base = 10);
LFCEXT void WriteNumberAndNull(char* dst, int64 num, uint base = 10);
LFCEXT void WriteNumberAndNull(char* dst, uint64 num, uint base = 10);

class LFCEXT HWindow : public Object
{
public:

	CTOR HWindow() : m_hWnd(NULL)
	{
	}

	virtual ~HWindow()
	{
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = NULL;
		}
	}

	/*
	HWND Create(LPCWSTR lpWindowName, DWORD dwStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT, HWND hWndParent = NULL, HMENU hMenu = NULL, LPVOID lParam = NULL)
	{
		RegisterClass();

		m_hWnd = CreateWindowEx(0, m_class, lpWindowName, dwStyle, x, y, width, height, hWndParent, hMenu, _Module.GetHandle(), lParam);
		if (m_hWnd == NULL)
		{
			raise(Exception("Failed to create window"));
		}
		return m_hWnd;
	}
	*/

	/*
	HWND CreateEx(DWORD dwExStyle, LPCWSTR lpWindowName, DWORD dwStyle, int nID = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT, HWND hWndParent = NULL, LPVOID lParam = NULL)
	{
		RegisterClass();

		m_hWnd = CreateWindowEx(0, m_class, lpWindowName, dwStyle, x, y, width, height, hWndParent, hMenu, _Module.GetHandle(), lParam);
		if (m_hWnd == NULL)
		{
			raise(Exception("Failed to create window"));
		}
		return m_hWnd;
	}
	*/

//	HWND Create(LPCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, const gm::RectI& rect, HWND hWndParent = NULL, HMENU hMenu = NULL, LPVOID lParam = NULL);
	HWND CreateOverlapped(LPCWSTR lpWindowName, DWORD dwStyle = WS_OVERLAPPEDWINDOW, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT, HWND hWndParent = NULL, HMENU hMenu = NULL, LPVOID lParam = NULL)
	{
		RegisterClass();

		m_hWnd = CreateWindowExW(0, (LPCWSTR)m_class, lpWindowName, WS_OVERLAPPEDWINDOW | dwStyle, x, y, width, height, NULL, NULL, _Module.GetHandle(), this);
		if (m_hWnd == NULL)
		{
			raise(Exception("Failed to create window"));
		}
		return m_hWnd;
	}

	HWND CreateHidden()
	{
		RegisterClass();

		m_hWnd = CreateWindowExW(0, (LPCWSTR)m_class, NULL, WS_POPUP, 0, 0, 0, 0, NULL, NULL, _Module.GetHandle(), this);
		if (m_hWnd == NULL)
		{
			raise(Exception("Failed to create window"));
		}
		return m_hWnd;
	}

	HWND get_Hwnd() const
	{
		return m_hWnd;
	}

	void Attach(HWND hWnd)
	{
		// TODO
		ASSERT(0);
		m_hWnd = hWnd;
	}

	HWND Detach()
	{
		HWND hWnd = m_hWnd;
		m_hWnd = NULL;
		return hWnd;
	}

	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProcW(m_hWnd, uMsg, wParam, lParam);
	}

private:

	static void RegisterClass();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static ATOM m_class;

	HWND m_hWnd;
};

class LFCEXT Handle
{
public:
	CTOR Handle() : m_h(INVALID_HANDLE_VALUE)
	{
	}

	CTOR Handle(decltype(nullptr)) : m_h(INVALID_HANDLE_VALUE)
	{
	}

	CTOR Handle(HANDLE h) : m_h(h)
	{
	}

	CTOR Handle(Handle&& other)
	{
		m_h = other.m_h;
		other.m_h = INVALID_HANDLE_VALUE;
	}

	~Handle()
	{
		if (m_h != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_h);
		}
	}

	bool operator ! () const throw()
	{
		return m_h == INVALID_HANDLE_VALUE;
	}

	bool operator == (decltype(nullptr)) const throw()
	{
		return m_h == INVALID_HANDLE_VALUE;
	}

	Handle& operator = (Handle&& other) throw()
	{
		m_h = other.m_h;
		other.m_h = INVALID_HANDLE_VALUE;
		return *this;
	}

	operator HANDLE () const throw()
	{
		return m_h;
	}

	HANDLE m_h;
};

class LFCEXT ProcessThread
{
public:
	DWORD get_Id() const
	{
		return m_id;
	}

	DWORD get_ExitCode() const
	{
		DWORD exitCode;
		GetExitCodeThread(m_h, &exitCode);
		return exitCode;
	}

	FILETIME get_StartTime()
	{
		FILETIME startTime;
		GetThreadTimes(m_h, &startTime, nullptr, nullptr, nullptr);
		return startTime;
	}

	FILETIME get_EndTime()
	{
		FILETIME endTime;
		GetThreadTimes(m_h, nullptr, &endTime, nullptr, nullptr);
		return endTime;
	}

	int get_Priority()
	{
		return GetThreadPriority(m_h);
	}

	bool get_PriorityBoost()
	{
		BOOL disablePriorityBoost;
		GetThreadPriorityBoost(m_h, &disablePriorityBoost);
		return !!disablePriorityBoost;
	}

	ULONG_PTR get_StartAddress();

#if _WIN32_WINNT >= 0x0600
	bool get_IOPending()
	{
		BOOL IOIsPending;
		GetThreadIOPendingFlag(m_h, &IOIsPending);
		return !!IOIsPending;
	}
#endif

#if _WIN32_WINNT >= 0x0601
	int get_IdealProcessor()
	{
		PROCESSOR_NUMBER pn;
		GetThreadIdealProcessorEx(m_h, &pn);
		return pn.Number | pn.Group*64;
	}
#endif

	Handle m_h;
	DWORD m_id;
};

class LFCEXT ProcessInformation
{
public:

	CTOR ProcessInformation(const PROCESS_INFORMATION& pi) :
		processHandle(pi.hProcess),
		threadHandle(pi.hThread),
		processId(pi.dwProcessId),
		threadId(pi.dwThreadId)
	{
	}

	CTOR ProcessInformation(ProcessInformation&& other) :
		processHandle(other.processHandle),
		threadHandle(other.threadHandle),
		processId(other.processId),
		threadId(other.threadId)
	{
	}

	Handle processHandle;
	Handle threadHandle;
	DWORD processId;
	DWORD threadId;
};

LFCEXT ProcessInformation Execute(StringIn commandLine);
LFCEXT ProcessInformation Execute(StringIn applicationName, StringIn commandLine);

enum WaitResult { WaitResult_Ok, WaitResult_Timeout};

LFCEXT void WaitFor(const ProcessInformation& process);
LFCEXT WaitResult WaitFor(const ProcessInformation& process, DWORD milliseconds);

}	// System

namespace MS
{
namespace Win32
{

#ifdef __LERSTAD__
#define _Out_opt_z_cap_post_count_(x,y)
#endif

class LFCEXT RegistryKey
{
private:
	CTOR RegistryKey(const RegistryKey& other);	// non-copyable
	RegistryKey& operator = (const RegistryKey& other);	// non-copyable

public:
	CTOR RegistryKey(HKEY hKey) : m_hKey(hKey)
	{
	}

	CTOR RegistryKey(RegistryKey&& other)	// moveable
	{
		m_hKey = other.m_hKey;
		other.m_hKey = nullptr;
	}

	~RegistryKey()
	{
		if (m_hKey)
		{
			RegCloseKey(m_hKey);
		}
	}

	void Close()
	{
		if (m_hKey)
		{
			RegCloseKey(m_hKey);
			m_hKey = nullptr;
		}
	}

	LONG Flush()
	{
		return RegFlushKey(m_hKey);
	}

	LONG QueryValue(System::StringIn valueName, DWORD* pdwType, void* pData, DWORD* pnBytes) throw()
	{
		ASSUME(m_hKey != nullptr);
		return RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, pdwType, (BYTE*)pData, pnBytes);
	}

	DWORD QueryDWORDValue(System::StringIn valueName)
	{
		DWORD dwType;
		DWORD dwData;
		DWORD nBytes = sizeof(DWORD);
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &dwType, (BYTE*)&dwData, &nBytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");

		if (dwType == REG_DWORD_BIG_ENDIAN)
		{
			return _byteswap_ulong(dwData);
		}

		if (dwType != REG_DWORD)
		{
			throw new System::SystemException("Not DWORD");
		}

		return dwData;
	}

	ULONGLONG QueryQWORDValue(System::StringIn valueName)
	{
		DWORD dwType;
		DWORD qwData;
		DWORD nBytes = sizeof(ULONGLONG);

		ASSUME(m_hKey != nullptr);
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &dwType, (BYTE*)&qwData, &nBytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");

/*
NOTE: REG_QWORD_BIG_ENDIAN doesn't exist
		if (dwType == REG_QWORD_BIG_ENDIAN)
		{
			return _byteswap_uint64(qwData);
		}
*/

		if (dwType != REG_QWORD)
		{
			throw new System::SystemException("Not QWORD");
		}

		return qwData;
	}

	System::String QueryStringValue(System::StringIn valueName)
	{
		DWORD dwType;
		DWORD nBytes = 0;
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &dwType, nullptr, &nBytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");
		if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
		{
			throw new System::SystemException("Not String");
		}

#ifndef __LERSTAD__
		WCHAR* data = new WCHAR[nBytes/2];

		ASSUME(m_hKey != nullptr);
		lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &dwType, (BYTE*)data, &nBytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");

		return System::String(System::string_data<wchar_t>(data, nBytes/2));
#endif
	}

	LONG QueryStringValue(System::StringIn valueName,
	_Out_opt_z_cap_post_count_(*pnChars, *pnChars) LPWSTR sz, ULONG* pnChars) throw()
	{
		ASSERT(sz);
		ASSERT(pnChars);

		DWORD dwType;
		DWORD nBytes = (*pnChars)*2;

		ASSUME(m_hKey);
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &dwType, (BYTE*)sz, &nBytes);
		if (lRes != ERROR_SUCCESS) return lRes;

		if(dwType != REG_SZ && dwType != REG_EXPAND_SZ)
		{
			return ERROR_INVALID_DATA;
		}

		*pnChars = nBytes/2;

		return lRes;
	}

	System::vector<System::String> QueryMultiStringValue(System::StringIn valueName)
	{
		DWORD type;
		DWORD nbytes = 0;

		ASSUME(m_hKey != nullptr);
		RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, nullptr, &nbytes);
		if (type != REG_MULTI_SZ)
		{
			throw new System::Exception("Not multistring");
		}

		WCHAR* data = (WCHAR*)_alloca(nbytes);
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, (BYTE*)data, &nbytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");

		System::vector<System::String> arr;
		WCHAR* p = data;
		while (*p)
		{
			arr.push_back(p);
			p += wcslen(p);
		}

		return arr;
	}

	template<class container_t>
	void QueryMultiStringValue(System::StringIn valueName, container_t arr)
	{
		DWORD type;
		DWORD nbytes = 0;
		RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, nullptr, &nbytes);
		if (type != REG_MULTI_SZ)
		{
			throw new System::Exception("Not multistring");
		}

		WCHAR* data = (WCHAR*)_alloca(nbytes);
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, (BYTE*)data, &nbytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");

		WCHAR* p = data;
		while (*p)
		{
			arr.push_back(p);
			p += wcslen(p);
		}
	}

	System::array<BYTE> QueryBinaryValue(System::StringIn valueName)
	{
		DWORD type;
		DWORD nbytes = 0;
		RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, nullptr, &nbytes);
		if (type != REG_BINARY)
		{
			throw new System::Exception("Not binary" /*ERROR_INVALID_DATA*/);
		}

#ifndef __LERSTAD__
		BYTE* data = new BYTE[nbytes];
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, (BYTE*)data, &nbytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");
		return System::array<BYTE>(data, nbytes);
#endif
	}

	DWORD QueryBinaryValue(System::StringIn valueName, BYTE* data, DWORD nbytes)
	{
		DWORD type;
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, (BYTE*)data, &nbytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");
		return nbytes;
	}

	GUID QueryGUIDValue(System::StringIn pszValueName)
	{
		ASSUME(m_hKey != nullptr);

		WCHAR szGUID[64];
		ULONG nCount;

		nCount = 64;
		LONG lRes = QueryStringValue(pszValueName, szGUID, &nCount);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");

		GUID guidValue;
		HRESULT hr = ::CLSIDFromString(szGUID, &guidValue);
		if (FAILED(hr)) throw new System::SystemException("Not a guid");

		return guidValue;
	}

	System::Variant QueryValue(System::StringIn valueName)
	{
		DWORD type;
		DWORD nbytes = 0;
		RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, nullptr, &nbytes);

		BYTE* data = (BYTE*)_alloca(nbytes);
		LONG lRes = RegQueryValueExW(m_hKey, valueName.c_strw(), nullptr, &type, data, &nbytes);
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");
		switch (type)
		{
			case REG_DWORD:
			{
				return *(DWORD*)data;
			}
			break;

			case REG_QWORD:
			{
				return *(uint64*)data;
			}
			break;

			case REG_MULTI_SZ:
				break;

			case REG_SZ:
				return System::String(System::string_copy((wchar_t*)data, nbytes/2));
				break;

			case REG_BINARY:
				break;

		}

		throw new System::SystemException("");
	}

	void SetDWORDValue(System::StringIn valueName, DWORD dwValue)
	{
		ASSUME(m_hKey != nullptr);
		LONG lRes = ::RegSetValueExW(m_hKey, valueName.c_strw(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&dwValue), sizeof(DWORD));
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");
	}

	void SetQWORDValue(System::StringIn valueName, ULONGLONG dwValue)
	{
		ASSUME(m_hKey != nullptr);
		LONG lRes = ::RegSetValueExW(m_hKey, valueName.c_strw(), 0, REG_QWORD, reinterpret_cast<const BYTE*>(&dwValue), sizeof(ULONGLONG));
		if (lRes != ERROR_SUCCESS) throw new System::SystemException("RegKey");
	}

	void SetStringValue(System::StringIn valueName, System::StringIn value)
	{
	}

	operator HKEY () const throw()
	{
		return m_hKey;
	}

	RegistryKey& operator = (RegistryKey&& other)	// moveable
	{
		if (m_hKey)
		{
			RegCloseKey(m_hKey);
		}
		m_hKey = other.m_hKey;
		other.m_hKey = nullptr;	// clear other

		return *this;
	}

	void Attach(HKEY hKey)
	{
		ASSERT(hKey);
		if (m_hKey)
		{
			RegCloseKey(m_hKey);
		}
		m_hKey = hKey;
	}

	HKEY Detach()
	{
		HKEY hKey = m_hKey;
		m_hKey = nullptr;
		return hKey;
	}

	LONG DeleteValue(System::StringIn valueName)
	{
		return RegDeleteKeyW(m_hKey, valueName.c_strw());
	}

	HKEY m_hKey;
//	TransactionManager
};

class LFCEXT Registry
{
public:
	static RegistryKey OpenKey(HKEY hKeyParent, System::StringIn keyName)
	{
		HKEY hKey;
		RegOpenKeyExW(hKeyParent, keyName.c_strw(), 0, KEY_READ | KEY_WRITE, &hKey);
		return hKey;
	}

	static RegistryKey OpenKey(HKEY hKeyParent, System::StringIn keyName, DWORD samDesired)
	{
		HKEY hKey;
		RegOpenKeyExW(hKeyParent, keyName.c_strw(), 0, samDesired, &hKey);
		return hKey;
	}

	/*
	static RegistryKey Create(
	   HKEY hKeyParent,
	   StringIn keyName,
	   LPTSTR lpszClass = REG_NONE,
	   DWORD dwOptions = REG_OPTION_NON_VOLATILE,
	   REGSAM samDesired = KEY_READ | KEY_WRITE,
	   LPSECURITY_ATTRIBUTES lpSecAttr = nullptr,
	   LPDWORD lpdwDisposition = nullptr);
	   */

#if _WIN32_WINNT >= 0x0600

	static DWORD get_SystemQuotaAllowed()
	{
		DWORD allowed;
		GetSystemRegistryQuota(&allowed, nullptr);
		return allowed;
	}

	static DWORD get_SystemQuotaUsed()
	{
		DWORD used;
		GetSystemRegistryQuota(nullptr, &used);
		return used;
	}

	static void GetSystemQuota(DWORD* pAllowed, DWORD* pUsed)
	{
		GetSystemRegistryQuota(pAllowed, pUsed);
	}
#endif

	static HKEY get_ClassesRoot()
	{
		return HKEY_CLASSES_ROOT;
	}

	static HKEY get_CurrentConfig()
	{
		return HKEY_CURRENT_CONFIG;
	}

	static HKEY get_CurrentUser()
	{
		return HKEY_CURRENT_USER;
	}

	static HKEY get_LocalMachine()
	{
		return HKEY_LOCAL_MACHINE;
	}

	static HKEY get_PerformanceData()
	{
		return HKEY_PERFORMANCE_DATA;
	}

	static HKEY get_PerformanceNLSText()
	{
		return HKEY_PERFORMANCE_NLSTEXT;
	}

	static HKEY get_PerformanceText()
	{
		return HKEY_PERFORMANCE_TEXT;
	}

	static HKEY get_Users()
	{
		return HKEY_USERS;
	}

private:

	CTOR Registry();		// non-creatable
};

}	// Win32
}	// MS

namespace System
{

extern LFCEXT DWORD gui_threadId;

}	// System

#endif // LFC_h
