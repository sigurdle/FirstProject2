namespace System
{
typedef DWORD rva_t;


class TypeDescriptor		// type_info
{
public:
	void* vtable;	//virtual ~TypeDescriptor()
	void *_m_data;
	char rawname[1];	// variable length

	const char* raw_name() const
	{
		return rawname;
	}
};

struct BaseClassDescriptor
{
#ifndef _M_X64
	TypeDescriptor* typedesc;
#else
	rva_t typedesc;
#endif
	uint32 nbases;
	int base_offset;

	//uint32 flags;
	uint32 notvisible : 1;
	uint32 ambiguous : 1;
	uint32 privcomp : 1;
	uint32 privbase : 1;
	uint32 vbofcontobj : 1;
	uint32 nonpolymorphic : 1;
};

struct ClassHierarchyDescriptor
{
	uint32 signature;	// = 0
	uint32 attributes;	// bit 0 set = multiple inheritance, bit 1 set = virtual inheritance
	uint32 count;		//number of classes in pBaseClassArray
#ifndef _M_X64
	BaseClassDescriptor** pBaseClassArray;
#else
	rva_t pBaseClassArray;
#endif
};

class LFCEXT ObjectLocator
{
public:
	uint32 signature;
	int32 offset_to_top;
	int32 cdOffset;
#ifndef _M_X64
	TypeDescriptor* typeinfo;
	ClassHierarchyDescriptor* hierarchy;
#else
	rva_t typeinfo;
	rva_t hierarchy;
	rva_t selfRelativeOffset;	// when signature=1
#endif

	static inline const ObjectLocator& From(const void* obj)
	{
		void* vtable = *(void**)obj;
		return *reinterpret_cast<const ObjectLocator*>(((void**)vtable)[-1]);
	}

	/**
	Gets the typeinfo of the superclass that this object is derived from
	*/
	const TypeDescriptor& TypeInfo() const
	{
#if _WIN64

		ASSERT(signature == 1);
		ubyte* imageBase = (ubyte*)this - selfRelativeOffset;

		DWORD* table = (DWORD*)(imageBase + ((ClassHierarchyDescriptor*)(imageBase + locator->m_classHierarchyDescriptor))->pBaseClassArray);

		TypeDescriptor* typedesc = (TypeDescriptor*)(imageBase + ((BaseClassDescriptor*)(imageBase + table[0]))->typedesc);
		return *typedesc;
#else
		ASSERT(signature == 0);

		TypeDescriptor* typedesc = hierarchy->pBaseClassArray[0]->typedesc;
		return *typedesc;
#endif
	}
};

}	// System
