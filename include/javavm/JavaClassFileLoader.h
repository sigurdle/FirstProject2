#ifndef __JavaClassFileLoader_h__
#define __JavaClassFileLoader_h__

namespace System
{
namespace javavm
{

class JavaObject;
class Thread;
class JProcess;
class JavaClass;
class JavaMethod;
class JavaField;

//extern uint32 objcount;

class ObjectRef
{
public:
	CTOR ObjectRef()
	{
		m_object = NULL;
	}

	CTOR ObjectRef(JavaObject* object)
	{
		m_object = object;
	//	m_id = objcount++;
	}

	/*
	CTOR ObjectRef(jobject object)
	{
		m_object = (JavaObject*)object;
	//	m_id = objcount++;
	}
	*/

	/*
	ObjectRef& operator = (JavaObject* object)
	{
		m_object = object;
		m_id = objcount++;
		return *this;
	}
	*/

	bool operator == (const JavaObject* object) const
	{
		return m_object == object;
	}

	bool operator != (const JavaObject* object) const
	{
		return m_object != object;
	}

	operator JavaObject* () const
	{
		return m_object;
	}

	operator jobject () const
	{
		return (jobject)m_object;
	}

	JavaObject* operator -> ()
	{
		return m_object;
	}

	JavaObject* m_object;
//	uint32 m_id;
};

struct ArrayFields
{
	uint m_length;
	uint8* m_data;
};

class JavaObject : public Object
{
public:
	CTOR JavaObject()
	{
		m_pClass = NULL;
		m_data = NULL;
		m_private0 = NULL;
	}

	JavaClass* m_pClass;
	uint8* m_data;
	void* m_private0;
};

typedef JavaObject ArrayRef;

inline JavaClass* GetClass(JavaObject* obj)
{
	return obj->m_pClass;
}

inline uint8* GetData(JavaObject* obj)
{
	return obj->m_data;
}

struct UTF8
{
	System::StringA* str;
	System::StringW* wstr;
	JavaObject* ref;
};

class CPoolItem
{
public:
	CTOR CPoolItem()
	{
		tag = 0;
		utf8.str = NULL;
		utf8.ref = NULL;
	}

	~CPoolItem()
	{
		if (tag == CONSTANT_Utf8)
		{
		//	str->Release();
			//str = NULL;
		}
	}

	JavaObject* GetString(Thread* c);

	uint8 tag;
	union
	{
		short int_16;
		long int_32;
		float float_32;
		LONGLONG long_64;
		double double_64;
		uint16 string_index;
		UTF8 utf8;

		struct //_methodRef
		{
			JavaMethod* m_pMethod;
			uint16 class_index;
			uint16 name_and_type_index;
		}
		methodRef;

		struct //_fieldRef
		{
			JavaField* m_pField;
			uint16 class_index;
			uint16 name_and_type_index;
		}
		fieldRef;

		struct //_classData
		{
			JavaClass* m_pClass;
			uint16 name_index;
		}
		classData;

		struct //_nameAndType
		{
			uint16 name_index;
			uint16 descriptor_index;
		}
		nameAndType;
	};
};

String Utf8ToW(StringA* str);
String GetString(JavaObject* pString);

//class CJavaClassFile;

class javavmext Attribute : public Object
{
public:
	uint8* m_data;
	ULONG m_length;
};

class javavmext WithAttributes
{
public:
	map<String, Attribute*> m_attributes;

	Attribute* GetAttribute(StringIn str);
};

class LineNumber
{
public:

	inline CTOR LineNumber(uint16 _start_pc, uint16 _line_number)
	{
		start_pc = _start_pc;
		line_number = _line_number;
	}

	uint16 start_pc;
	uint16 line_number;
};

class javavmext CodeAttribute : public WithAttributes
{
public:
	virtual ~CodeAttribute()
	{
	}

	int GetLineNumbers(vector<LineNumber>& lines);

	uint16 max_stack;
	uint16 max_locals;
	uint32 code_length;
	uint8* code;
};

class Type : public Object
{
public:

	CTOR Type() : className(NULL), m_pClass(NULL)
	{
	}

	enum TypeKind : char
	{
		BaseType_byte = 'B',//  byte  signed byte  
		BaseType_wchar = 'C',//  Unicode character  
		BaseType_double = 'D',//  double-precision floating-point value  
		BaseType_float = 'F',//  single-precision floating-point value  
		BaseType_int = 'I',//  integer  
		BaseType_long = 'J',// long integer  
		Type_ref = 'L',// reference  an instance of class <classname>  
		BaseType_short = 'S',//signed short  
		BaseType_bool = 'Z',//  true or false  
		Type_array = '[',
		ReturnType_void = 'V',
	}
	kind;

	union
	{
		Type* arrayof;
	}
	u;

	String className;
	JavaClass* m_pClass;
};

class javavmext JavaField : public Object, public WithAttributes
{
public:
	CTOR JavaField(JavaClass* pOwnerClass)
	{
		m_pOwnerClass = pOwnerClass;
		m_p = NULL;

		m_access_flags = 0;
	}

	String GetName();

	JavaClass* m_pOwnerClass;

	uint16 m_access_flags;
	uint16 m_name_index;
	uint16 m_descriptor_index;
//	uint8* m_code;
//	ULONG m_codelength;

	Type* m_pType;
	uint32 m_offset;

	ObjectRef m_p;	// As seen by VM (java/lang/reflect/Field)
};

class MethodException
{
public:
	uint16 start_pc;
	uint16 end_pc;
	uint16 handler_pc;
	uint16 catch_type;
};

class javavmext JavaMethod : public Object, public WithAttributes
{
public:
	CTOR JavaMethod(JavaClass* pOwnerClass)
	{
		m_pOwnerClass = pOwnerClass;
		m_nativeFunc = NULL;
		m_p = NULL;
		m_exceptions = NULL;
		m_pReturnType = NULL;

		m_userdata = NULL;
	}

	String GetName();
	String GetSignature();
	String GetDescriptor();
	CodeAttribute* GetCode();

public:

	ObjectRef m_p;
	String m_name;
	JavaClass* m_pOwnerClass;
	Type* m_pReturnType;
	vector<Type*> m_argumentTypes;
	MethodException* m_exceptions;
	void* m_nativeFunc;

	Object* m_userdata;

	uint16 m_access_flags;
	uint16 m_name_index;
	uint16 m_descriptor_index;
	uint16 m_exception_count;
};

class javavmext JavaClass : public Object, public WithAttributes
{
public:

	CTOR JavaClass(int baseTypeSize = 4);
	virtual ~JavaClass();

	inline ObjectRef GetObject()
	{
	//	return this;
	// TODO, maybe change this to
		return m_p;
	}

	int Parse(IO::Stream* stream);

	String GetSourceFile();
	String GetName();
	JavaMethod* GetMethodByName(StringIn name);
	JavaMethod* GetMethodShallow(StringIn name);
	JavaField* GetFieldByName(StringIn name);
	JavaField* GetField(StringIn name);
	JavaClass* GetSuperClass();

	void Initialize(Thread* vm);
	void InitializeStatics(Thread* vm);
	JavaObject* CreateInstance();

	void ReadAttributes(IO::Stream* stream, WithAttributes* pAttributes);

public:

	CPoolItem* m_pool_array;

	uint32 m_staticFieldSize;
	uint32 m_instanceFieldSize;

	uint8* m_staticData;

	JavaClass* m_pSuperClass;
	JavaClass** m_pInterfaces;

	int m_state;

	String m_name;

//	map<const char*, void*, cstr_less> m_nativeFuncs;

	int m_baseTypeSize;

	uint32 m_magic;
	uint16 m_minor_version;
	uint16 m_major_version;
	uint16 m_constant_pool_count;

	uint16 m_access_flags;
	uint16 m_this_class;	// Index to the class that this .class file defines
	uint16 m_super_class;	// extends
	uint16 m_interfaces_count;	// implements
	uint16* m_interface_index;

	uint16 m_fields_count;
	JavaField** m_fields;

	uint16 m_methods_count;
	JavaMethod** m_methods;

	JavaClass* m_pArrayOf;	// If this class is an array class

	ObjectRef m_p;	// As seen by the VM (java/lang/reflect/Class)

	map<String, JavaMethod*> m_methodByName;
	map<String, JavaField*> m_fieldByName;
};

inline JavaClass* GetJavaClass(JavaObject* obj)
{
//	return static_cast<JavaClass*>(obj);
// TODO, maybe change this to
	ASSERT(dynamic_cast<JavaClass*>((Object*)obj->m_private0));
	return (JavaClass*)obj->m_private0;
}

inline ArrayFields* GetArrayFields(ArrayRef* obj)
{
	ASSERT(GetClass(obj)->m_pArrayOf);
	return (ArrayFields*)GetData(obj);
}

inline int GetArrayLength(ArrayRef* obj)
{
	ASSERT(GetClass(obj)->m_pArrayOf);
	return GetArrayFields(obj)->m_length;
}

inline uint8* GetArrayData(ArrayRef* obj)
{
	ASSERT(GetClass(obj)->m_pArrayOf);
	return GetArrayFields(obj)->m_data;
}

inline JavaClass* GetArrayComponentType(ArrayRef* obj)
{
	ASSERT(GetClass(obj)->m_pArrayOf);
	return GetClass(obj)->m_pArrayOf;
}

}	// javavm
}	// System

#endif // __JavaClassFileLoader_h__
