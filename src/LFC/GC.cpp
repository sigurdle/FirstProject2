#include "stdafx.h"
#include "LFC.h"
#include "vc_typeinfo.h"

#if _WIN32
#include <Psapi.h>
System::CriticalSection m_live_crit;
#endif

/*

TODO: Comment on garbage collection and partially constructed objects:

If a garbage collection is initiated on a paritally constructed object, the type
of object is wrong, however:
The object itself is correctly found. (offset_to_top), and the 


TODO: For garbage collection

http://www.openrce.org/articles/full_view/23

Static and Global Initializers
Global and static objects need to be initialized before the main program starts. MSVC implements that by generating initializer funclets and putting their addresses in a table, which is processed during CRT startup by the _cinit function. The table usually resides in the beginning of .data section. A typical initializer looks like following: 


    _init_gA1:
        mov     ecx, offset _gA1
        call    A::A()
        push    offset _term_gA1
        call    _atexit
        pop     ecx
        retn
    _term_gA1:
        mov     ecx, offset _gA1
        call    A::~A()
        retn


Thus, from this table way we can find out: 
Global/static objects addresses 
Their constructors 
Their destructors 
See also MSVC _#pragma_ directive _init_seg_ [5]. 

*/

namespace System
{
///////////

extern list<void**, std_allocator>* live;

MemoryManagerStatus memstatus;

LFCEXT const MemoryManagerStatus& GetMemoryManagerStatus()
{
	return memstatus;
}

//#undef new

struct RegsX86
{
	DWORD Eax;
	DWORD Ecx;
	DWORD Edx;
	DWORD Ebx;
	DWORD Esi;
	DWORD Edi;
	DWORD Ebp;
	DWORD Esp;
};

struct RegsX64
{
	DWORD64 Rax;
	DWORD64 Rcx;
	DWORD64 Rdx;
	DWORD64 Rbx;
	DWORD64 Rsi;
	DWORD64 Rdi;
	DWORD64 Rbp;
	DWORD64 Rsp;

	DWORD64 R8;
	DWORD64 R9;
	DWORD64 R10;
	DWORD64 R11;
	DWORD64 R12;
	DWORD64 R13;
	DWORD64 R14;
	DWORD64 R15;
};

struct RegsPPC32
{
	uint32 grp[32];
};

struct RegsPPC64
{
	uint64 grp[32];
};

struct RegsM68K
{
	uint32 d0;
	uint32 d1;
	uint32 d2;
	uint32 d3;
	uint32 d4;
	uint32 d5;
	uint32 d6;
	uint32 d7;

	uint32 a0;
	uint32 a1;
	uint32 a2;
	uint32 a3;
	uint32 a4;
	uint32 a5;
	uint32 a6;
	uint32 a7;
};

#ifdef _M_IX86

typedef RegsX86 RegsNative;

#elif _M_X64

typedef RegsX64 RegsNative;

#elif AMIGA	// M68K

typedef RegsM68K RegsNative;

#elif _ARCH_PPC

typedef RegsPPC32 RegsNative;

#else
#error "Unknown OS"
#endif

extern "C"
{
	RegsNative regs;
}

list<HANDLE, std_allocator> g_threads;

byte* data;
byte* enddata;

// 28 bits = 256 MB
// 29 bits = 512 MB

struct Memblock
{
#if defined(_M_X64)
	unsigned int m_nextfree : 26;
	unsigned int m_kind : 1, m_allocated : 1, m_marked : 1;
	unsigned int m_magic : 3;

	unsigned int m_extra;

#else
	unsigned int m_nextfree : 26;
	unsigned int m_kind : 1, m_allocated : 1, m_marked : 1;
	unsigned int m_magic : 3;

	void* m_extra;

#endif

/*
#ifdef _DEBUG
	const char* m_filename;
	int m_line;
#endif
*/

	bool IsAllocated() const
	{
		return m_allocated;
	}

	uint getpage() const;

	void setnextfree(const Memblock* block);
	Memblock* getnextfree() const;

	ClassType* GetClassType() const;
};

inline void Memblock::setnextfree(const Memblock* block)
{
	ASSERT(this);

	if (block == nullptr)
	{
		m_nextfree = 0;
	}
	else
	{
		ptrdiff_t offset = (ubyte*)block - (ubyte*)data;
		ASSERT(offset < 0x1FFFFFFF);
	//	ASSERT(offset <= 0xFFFFFFF);

		m_nextfree = offset>>3;
	}
}

inline Memblock* Memblock::getnextfree() const
{
	if (m_nextfree == 0) return nullptr;
	return (Memblock*)((ubyte*)data + (m_nextfree<<3));
}

ClassType* Memblock::GetClassType() const
{
	if (m_kind == 1)
	{
		Type* pType = GetType((const void*)(this + 1), true);
		return pType->AsClass();
	}
	else
		return nullptr;
}

#define BLOCK_MAGIC 0x5

// max 28 bits address (256 MB)

#ifdef _M_IX86
//const uint g_maxpages = 0xF000;	// 61440
//const uint g_maxpages = 0xFFF0;	// 61440
const uint g_maxpages = 0x20000;	// 512
#elif _M_X64
const uint g_maxpages = 0x20000;	// 512 MB
#endif

#ifdef _M_X64
const size_t MaxAllocSize = 0x000000FFFFFFFFFF;
#else
const size_t MaxAllocSize = 0x07FFFFFF;
#endif

class GCPage
{
public:
	uint32 m_nextfree;
	uint16 m_allocsize;
	uint16 m_n;
};

GCPage pages[g_maxpages];
uint npages = 0;
uint first_freepage = 0;

const uint g_maxslots = 17;
Memblock* freelist[g_maxslots];

SYSTEM_INFO sysinfo;
int pagesize_bits;
int pagesize_mask;

CRITICAL_SECTION crit_section;

inline uint Memblock::getpage() const
{
	ASSERT(this);
	return ((byte*)this - data) >> pagesize_bits;
}

uint allocpage()
{
	if (first_freepage)
	{
		uint npage = first_freepage-1;

		if (pages[npage].m_allocsize)
		{
			ASSERT(0);
		}

		first_freepage = pages[npage].m_nextfree;
		return npage;
	}

	if (npages == g_maxpages)
	{
		GC::Collect();

		if (first_freepage == 0)
		{
			raise(Exception("oops - no more pages to allocate"));
		}

		return allocpage();
	}

	uint npage = npages;

	// new page
	void* p2 = VirtualAlloc(data + npages*sysinfo.dwPageSize, sysinfo.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
	ASSERT(p2 == (data + npages*sysinfo.dwPageSize));
	++npages;

	enddata += sysinfo.dwPageSize;

	return npage;
}

void makepage(uint npage, uint allocsize, uint allocslot)
{
	pages[npage].m_allocsize = allocsize;

	byte* p = data + npage*sysinfo.dwPageSize;
	freelist[allocslot] = (Memblock*)p;

	size_t count = sysinfo.dwPageSize / allocsize;

	Memblock* block;

	while (count--)
	{
		block = (Memblock*)p;
		block->setnextfree((Memblock*)(p + allocsize));
		block->m_allocated = false;
		block->m_marked = false;
		block->m_magic = BLOCK_MAGIC;

		p += allocsize;
	}
	block->m_nextfree = 0;
}

#ifdef _M_IX86

void __declspec(naked) saveregs()
{
	__asm
	{
		mov dword ptr[regs.Eax],eax
		mov dword ptr[regs.Ebx],ebx
		mov dword ptr[regs.Ecx],ecx
		mov dword ptr[regs.Edx],edx
		mov dword ptr[regs.Esi],esi
		mov dword ptr[regs.Edi],edi
		mov dword ptr[regs.Ebp],ebp
		mov dword ptr[regs.Esp],esp
		ret
	}
}

#elif _M_X64

extern "C" void saveregs();

#else

#error "Unknown OS"

#endif

void init_gc()
{
	InitializeCriticalSection(&crit_section);

	GetSystemInfo(&sysinfo);

	ULONG size = g_maxpages * sysinfo.dwPageSize;
	data = (byte*)VirtualAlloc(nullptr, size, MEM_RESERVE, PAGE_READWRITE);
	enddata = data;

	pagesize_mask = sysinfo.dwPageSize-1;
	pagesize_bits = -1;
	int pagesize = sysinfo.dwPageSize;
	while (pagesize > 0)
	{
		++pagesize_bits;
		pagesize >>= 1;
	}

	ASSERT((1<<pagesize_bits) == pagesize_mask+1);

	memstatus.Total = size;
	memstatus.Free = size;

#if defined(_M_X64) && defined(_MSC_VER)
	ASSERT(sizeof(Memblock) == 8);
#else
	ASSERT(sizeof(Memblock) == 8);
#endif
}

size_t getallocsize(size_t size)
{
	size_t allocsize;

	if (size <= 16) allocsize = 16;
	else if (size <= 24) allocsize = 24;
	else if (size <= 32) allocsize = 32;
	else if (size <= 40) allocsize = 40;
	else if (size <= 48) allocsize = 48;
	else if (size <= 56) allocsize = 56;
	else if (size <= 64) allocsize = 64;

	else if (size <= 96) allocsize = 96;
	else if (size <= 128) allocsize = 128;
	else if (size <= 192) allocsize = 192;
	else if (size <= 256) allocsize = 256;
	else if (size <= 384) allocsize = 384;
	else if (size <= 512) allocsize = 512;
	else if (size <= 1024) allocsize = 1024;
	else if (size <= 2048) allocsize = 2048;
	else if (size <= 4096) allocsize = 4096;
	else
	{
		allocsize = sysinfo.dwPageSize;
	}

	ASSERT(allocsize > sizeof(Memblock));

#ifdef _M_X64
	ASSERT((allocsize & 7) == 0);	// at least 8-byte aligned
#else
	ASSERT((allocsize & 7) == 0);	// at least 8-byte aligned
#endif

	return allocsize;
}

uint getallocslot(size_t size)
{
	uint allocslot;

	if (size <= 16) allocslot = 0;
	else if (size <= 24) allocslot = 1;
	else if (size <= 32) allocslot = 2;
	else if (size <= 40) allocslot = 3;
	else if (size <= 48) allocslot = 4;
	else if (size <= 56) allocslot = 5;
	else if (size <= 64) allocslot = 6;

	else if (size <= 96) allocslot = 7;
	else if (size <= 128) allocslot = 8;
	else if (size <= 192) allocslot = 9;
	else if (size <= 256) allocslot = 10;
	else if (size <= 384) allocslot = 11;
	else if (size <= 512) allocslot = 12;
	else if (size <= 1024) allocslot = 13;
	else if (size <= 2048) allocslot = 14;
	else if (size <= 4096) allocslot = 15;
	else
	{
		allocslot = 16;
	}

	ASSERT(allocslot < g_maxslots);

	return allocslot;
}

uint AllocSize(Memblock* block)
{
	ULONG_PTR offset = ((byte*)block - data);
	size_t npage = offset >> pagesize_bits;
	size_t pageoffset = offset & pagesize_mask;
	size_t allocsize = pages[npage].m_allocsize;
	size_t memblockoffset = pageoffset % allocsize;
	ASSERT(memblockoffset == 0);

	ASSERT(block->m_magic == BLOCK_MAGIC);

	return allocsize;
}

#ifdef _DEBUG

bool CheckAllocSize(Memblock* block, uint _allocsize)
{
	ULONG_PTR offset = ((byte*)block - data);
	size_t npage = offset >> pagesize_bits;
	size_t pageoffset = offset & pagesize_mask;
	size_t allocsize = pages[npage].m_allocsize;
	size_t memblockoffset = pageoffset % allocsize;
	ASSERT(memblockoffset == 0);

	ASSERT(block->m_magic == BLOCK_MAGIC);

	ASSERT(allocsize == _allocsize);
	return allocsize == _allocsize;
}

#endif

#define large_alloc	malloc

LFCEXT Object* _allocate_object(size_t _size, const char* filename, int line)
{
	if (_size > MaxAllocSize) return nullptr;

	size_t size = _size;
	size += sizeof(Memblock);

	if (size > sysinfo.dwPageSize)
	{
		return (Object*)large_alloc(_size);
	}

	size_t allocsize = getallocsize(size);
	uint allocslot = getallocslot(size);

	CriticalSectionLock lock(&crit_section);

	Memblock* block = freelist[allocslot];
	if (block)
	{
		if (block->m_magic != BLOCK_MAGIC)
		{
			raise(SystemException("not a valid memory block"));
		}

		if (block->m_allocated)
		{
			raise(SystemException("not a valid memory block"));
		}

		ASSERT(CheckAllocSize(block, allocsize));

		freelist[allocslot] = block->getnextfree();
		block->m_nextfree = 0;
		block->m_allocated = true;
		block->m_kind = 1;	// object (vtable)

#ifdef _DEBUG
	//	block->m_filename = filename;
	//	block->m_line = line;
#endif

		size_t npage = ((byte*)block - data) >> pagesize_bits;
		++pages[npage].m_n;

		memstatus.Free -= allocsize;
		memstatus.Used += allocsize;
		memstatus.InternalFragmentation += (allocsize-size);
		++memstatus.AllocSizes[allocslot];

		return (Object*)(block + 1);
	}

	uint npage = allocpage();
	makepage(npage, allocsize, allocslot);

	return _allocate_object(_size, filename, line);
}

LFCEXT void* _allocate_buffer(size_t _size)
{
	if (_size > MaxAllocSize) return nullptr;

	size_t size = _size;
	size += sizeof(Memblock);

	if (size > sysinfo.dwPageSize)
	{
		return large_alloc(_size);
	}

	size_t allocsize = getallocsize(size);
	uint allocslot = getallocslot(size);

	CriticalSectionLock lock(&crit_section);

	Memblock* block = freelist[allocslot];
	if (block)
	{
		if (block->m_magic != BLOCK_MAGIC)
		{
			raise(SystemException("not a valid memory block"));
		}

		if (block->m_allocated)
		{
			raise(SystemException("not a valid memory block"));
		}

		ASSERT(CheckAllocSize(block, allocsize));

		freelist[allocslot] = block->getnextfree();
		block->m_nextfree = 0;
		block->m_allocated = true;
		block->m_marked = false;
		block->m_kind = 0;	// buffer (not an object with vtable)

		size_t npage = ((byte*)block - data) >> pagesize_bits;
		++pages[npage].m_n;

		memstatus.Free -= allocsize;
		memstatus.Used += allocsize;
		memstatus.InternalFragmentation += (allocsize-size);
		++memstatus.AllocSizes[allocslot];

		return (block + 1);
	}

	uint npage = allocpage();
	makepage(npage, allocsize, allocslot);

	return _allocate_buffer(_size);
}

LFCEXT void* try_resize_buffer(void* pv, size_t newsize)
{
	if (pv == nullptr) return nullptr;

	if (newsize > sysinfo.dwPageSize)
	{
		return nullptr;
	}

	byte* pb = (byte*)pv;
	if (!(pb > data && pb < enddata))
	{
		return nullptr;
//#define new _new
//		raise(ArgumentException("pointer 0x" + String::FromNumber((ULONG_PTR)pv, 16) + " not in heap"));
//#undef new
	}

	Memblock* block = (Memblock*)pb - 1;
	if (block->m_magic != BLOCK_MAGIC)
	{
		raise(SystemException("not a valid memory block"));
	}

	ULONG_PTR offset = (pb - data);
	size_t npage = offset >> pagesize_bits;

	uint allocsize = pages[npage].m_allocsize;

	allocsize -= sizeof(Memblock);

	if (newsize <= allocsize)
	{
	//	memstatus.Used

		return pv;
	}

	return nullptr;
}

LFCEXT Object* allocate_object(size_t size)
{
	Object* p = _allocate_object(size, nullptr, -1);
	if (p)
	{
		ZeroMemory(p, size);
	}
	else
	{
		IO::StringWriter str;
		str << "Failed to allocate object of size " << size << " bytes";
		raise(OutOfMemoryException(str.str()));
	}
	return p;
}

LFCEXT Object* allocate_object(size_t size, const char* filename, int line)
{
	Object* p = _allocate_object(size, filename, line);
	if (p)
	{
		ZeroMemory(p, size);
	}
	else
	{
		IO::StringWriter str;
		str << "Failed to allocate object of size " << size << " bytes";
		raise(OutOfMemoryException(str.str()));
	}
	return p;
}

LFCEXT void* allocate_buffer(size_t size)
{
	void* p = _allocate_buffer(size);
	if (p)
	{
		ZeroMemory(p, size);
	}
	else
	{
		IO::StringWriter str;
		str << "Failed to allocate " << size << " bytes";
		raise(OutOfMemoryException(str.str()));
	}

	return p;
}

LFCEXT void* allocate_buffer(size_t size, const char* filename, int line)
{
	void* p = _allocate_buffer(size);
	if (p)
	{
		ZeroMemory(p, size);
	}
	else
	{
		IO::StringWriter str;
		str << "Failed to allocate " << size << " bytes";
		raise(OutOfMemoryException(str.str()));
	}

	return p;
}

namespace
{

void invalidate_mem(void* pv, size_t size)
{
	ASSERT((size & 3) == 0);

	DWORD* p = (DWORD*)pv;
	size >>= 2;
	while (size--)
	{
		*p++ = 0xCCCCCCCC;
	}
}

/*
Memblock* findFirstOnPage(Memblock* block, uint npage)
{
	while (block)
	{
		if (block->getpage() == npage) break;
		block = block->getnextfree();
	}
	return block;
}
*/

Memblock* skipOnPage(Memblock* block, uint npage)
{
	while (block)
	{
		if (block->getpage() != npage) break;
		block = block->getnextfree();
	}
	return block;
}

void gc_sweep()
{
	for (size_t i = 0; i < npages; ++i)
	{
		byte* start = data + i*sysinfo.dwPageSize;
		byte* end = start + sysinfo.dwPageSize;

		byte* p = start;

		uint allocsize = pages[i].m_allocsize;
		uint allocslot = getallocslot(allocsize);

		if (allocsize)
		{
			bool any_marked = false;

			// Scan page
			while (p+allocsize <= end)
			{
				Memblock* block = (Memblock*)p;
				ASSERT(block->m_magic == BLOCK_MAGIC);

				if (!block->m_marked)
				{
					// free it

					if (block->m_allocated)
					{
						
						/*
						if (block->GetClassType())
						{
							if (block->GetClassType()->m_name == "red_black_node")
							{
								ASSERT(0);
							}
						}
						*/

						--pages[i].m_n;
	#ifdef _DEBUG
						invalidate_mem(block+1, allocsize-sizeof(Memblock));
	#endif
						block->m_allocated = false;

						block->setnextfree(freelist[allocslot]);
						freelist[allocslot] = block;
					}
				}
				else
				{
					any_marked = true;

					ASSERT(block->m_allocated);
					ASSERT(block->m_nextfree == 0);
					block->m_marked = false;
				}

				p += allocsize;
			}

		//	if (pages[i].m_n == 0)
			if (!any_marked)
			{
				// Remove free block that are on this page

				// head
				Memblock* block = skipOnPage(freelist[allocslot], i);
				if (block != freelist[allocslot])
				{
					freelist[allocslot] = block;
				}
				while (block)
				{
					Memblock* block2 = skipOnPage(block->getnextfree(), i);
					block->setnextfree(block2);
					block = block2;
				}

				// The entire page was freed
				// put page on free pages list

				pages[i].m_nextfree = first_freepage;
				pages[i].m_allocsize = 0;

				first_freepage = i+1;
			}
		}
	}
}

void ForwardFieldsNoRecurse(uint8* object, ClassType* pMostDerivedClass);

void Forward(Memblock* block, ClassType* pContainerType, int debugOffset)
{
	if (block >= (Memblock*)data && block < (Memblock*)enddata)
	{
		ULONG_PTR value = (ULONG_PTR)block;
		byte* p = (byte*)block;

		ULONG_PTR pageaddr = value & ~pagesize_mask;
		ULONG_PTR offset = (p - data);
		size_t npage = offset >> pagesize_bits;
		uint pageoffset = offset & pagesize_mask;
		size_t allocsize = pages[npage].m_allocsize;
		uint memblockoffset = pageoffset % allocsize;
		Memblock* block = (Memblock*)(value - memblockoffset);

		ASSERT(block->m_magic == BLOCK_MAGIC);
		ASSERT(block->m_allocated);
		if (!block->m_marked)
		{
			ASSERT(block->m_allocated);
			block->m_marked = true;

			if (block->m_kind)
			{
				byte* object = (byte*)(block+1);
				ClassType* pType = GetType(object);

				ForwardFieldsNoRecurse(object, pType);
			}

			/*
			byte* object = (byte*)(block+1);
			ClassType* pType = GetType(object);

			ForwardFieldsNoRecurse(object, pType);
			*/
		}
	}
}

void ForwardNoRecurse(Memblock* block, ClassType* pType)
{
	ASSERT(pType);

	if (block >= (Memblock*)data && block < (Memblock*)enddata)
	{
		ASSERT(block->m_magic == BLOCK_MAGIC);
		ASSERT(block->m_allocated);
		if (!block->m_marked)
		{
			block->m_marked = true;

			ASSERT(block->m_kind);

			byte* object = (byte*)(block+1);
		//	ClassType* pType2 = GetType(object);
		//	ASSERT(pType == pType2);

			ForwardFieldsNoRecurse(object, pType);
		}
	}
}

void ForwardFieldNoRecurse_Kind(void** ppchildpointer, int kind, ClassType* pDebugType, int debugOffset)
{
	if (*ppchildpointer)
	{
		void* childpointer = *ppchildpointer;

		if (kind == 1)
		{
			childpointer = ((uint8*)childpointer/* - 4*/);

			Forward((Memblock*)childpointer-1, pDebugType, debugOffset);
		}
		else
		{
#if _WIN64
			const ObjectLocator& locator = ObjectLocator::From(childpointer);

			ubyte* imageBase = locator->signature == 1? (ubyte*)&locator - locator->selfRelativeOffset:
				nullptr;	// RtlPcToFileHeader

			DWORD* table = (DWORD*)(imageBase + ((ClassHierarchyDescriptor*)(imageBase + locator.m_classHierarchyDescriptor))->pBaseClassArray);

			TypeDescriptor* typedesc = (TypeDescriptor*)(imageBase + ((BaseClassDescriptor*)(imageBase + table[0]))->typedesc);
			ClassType* pMostDerivedClass = (ClassType*)(typedesc)->_m_data;

			void* childobject = (uint8*)childpointer - locator.offset_to_top;

#elif _WIN32

			const ObjectLocator& locator = ObjectLocator::From(childpointer);
			ClassType* pMostDerivedClass = (ClassType*)locator.hierarchy->pBaseClassArray[0]->typedesc->_m_data;
			if (pMostDerivedClass == nullptr)
			{
				MessageBoxA(nullptr, "pMostDerivedClass == nullptr", "", MB_OK);
				ASSERT(0);
			}

			void* childobject = (ubyte*)childpointer - locator.offset_to_top;

#else
			void *vtable = *(void**)childpointer;
			__type_info2* ti = (__type_info2*)((void**)vtable)[-1];
			ptrdiff_t offset_to_top = - ((ptrdiff_t*)vtable)[-2];
			//ASSERT(offset_to_top <= 0);
			if (offset_to_top < 0 || offset_to_top > 1000)
			{
				printf("offset_to_top is probably too large: %d\n", offset_to_top);
				printf("%s - %d\n", pDebugType->m_qname->c_str(), debugOffset);
				ASSERT(0);
			//	ASSERT(offset_to_top >= 0 && offset_to_top < 512);
			}

			ClassType* pMostDerivedClass = *(ClassType**)(ti->__type_name - 4);
			//ClassType* pMostDerivedClass = (ClassType*)ti->__type_name;

			void* childobject = (uint8*)childpointer - offset_to_top;
#endif
		//	if (childobject)
			{
				ForwardNoRecurse((Memblock*)childobject-1, pMostDerivedClass);
			}
		}
	}
}

void ForwardFieldsNoRecurse(ubyte* object, ClassType* pMostDerivedClass)
{
	/*
	if (pMostDerivedClass->m_name == "red_black_node")
	{
		MessageBeep(-1);
	}
	*/

	/*
	if (pMostDerivedClass->m_qname == "System::red_black_node<System::String,System::Declarator *>")
	{
		MessageBeep(-1);
	}
	*/

	{
		size_t ncount = pMostDerivedClass->m_gcMembers.size();
		GCMember* declrefs = pMostDerivedClass->m_gcMembers.begin();

		for (size_t i = 0; i < ncount; ++i)
		{
			const GCMember& decl = declrefs[i];

			uint offset = decl.m_offset_and_kind>>1;
			int kind = decl.m_offset_and_kind & 1;

			/*
#ifdef _DEBUG
			Declarator* pd = pMostDerivedClass->GetMemberByOffset(offset);
#endif
			*/

			void** ppchildpointer = (void**)(object + offset);

			ForwardFieldNoRecurse_Kind(ppchildpointer, kind, pMostDerivedClass, offset);
		}
	}

	{
		size_t ncount = pMostDerivedClass->m_gcArrayMembers.size();
		GCArrayMember* declrefs = pMostDerivedClass->m_gcArrayMembers.begin();

		if (declrefs == nullptr)
		{
			ASSERT(ncount == 0);
		}

		for (size_t i = 0; i < ncount; ++i)
		{
			const GCArrayMember& decl = declrefs[i];

			Type *pType = decl.m_pType;

			ArrayBaseData* pArray = (ArrayBaseData*)(object + decl.m_offset);

			Forward((Memblock*)((ubyte*)pArray->m_pData)-1, pMostDerivedClass, decl.m_offset);

			size_t arraysize = pArray->m_nSize;
			size_t elemsize = pType->get_sizeof();

			switch (pType->get_Kind())
			{
			case type_typedef:
				ASSERT(0);
				break;

			case type_class:
				{
					ubyte* object = (ubyte*)pArray->m_pData;

					for (size_t i = 0; i < arraysize; ++i)
					{
						ForwardFieldsNoRecurse(object, static_cast<ClassType*>(pType));

						object += elemsize;
					}
				}
				break;

			case type_pointer:
				{
					ASSERT(elemsize == sizeof(void*));

					Type* pPointerTo = pType->GetPointerTo()->GetStripped();

					int kind = !(pPointerTo->get_Kind() == type_class && pPointerTo->AsClass()->HasVirtualTable());

					ubyte* object = (ubyte*)pArray->m_pData;
					for (size_t i = 0; i < arraysize; ++i)
					{
						ForwardFieldNoRecurse_Kind((void**)object, kind, pMostDerivedClass, decl.m_offset);

						object += elemsize;
					}
				}
				break;
			}
		}
	}
}

void gc_address(ULONG_PTR value)
{
	--value;	// To accomodate for pointing at end of buffer
	byte* p = (byte*)value;

	if (p > data && p < enddata)
	{
		ULONG_PTR pageaddr = value & ~pagesize_mask;

		ULONG_PTR offset = (p - data);
		size_t npage = offset >> pagesize_bits;
		size_t pageoffset = offset & pagesize_mask;

		size_t allocsize = pages[npage].m_allocsize;

		size_t sizeofpage = (sysinfo.dwPageSize / allocsize) * allocsize;
		if (pageoffset < sizeofpage)
		{
			size_t memblockoffset = pageoffset % allocsize;

			Memblock* block = (Memblock*)(value - memblockoffset);

			ASSERT(block->m_magic == BLOCK_MAGIC);
			if (block->m_allocated)
			{
				if (!block->m_marked)
				{
					block->m_marked = true;

					if (block->m_kind)
					{
						byte* object = (byte*)(block+1);
						ClassType* pType = GetType(object);

						ForwardFieldsNoRecurse(object, pType);
					}
				}
			}
		}
	}
}

#define WITHIN_GC_HEAP(address) ((byte*)address > System::data && (byte*)address <= System::enddata)

void gc_address_top(ULONG_PTR value)
{
	--value;	// To accomodate for pointing at end of buffer
	byte* p = (byte*)value;

	//if (p > data && p < enddata)
	{
		ULONG_PTR pageaddr = value & ~pagesize_mask;

		ULONG_PTR offset = (p - data);
		size_t npage = offset >> pagesize_bits;
		size_t pageoffset = offset & pagesize_mask;

		size_t allocsize = pages[npage].m_allocsize;

		size_t sizeofpage = (sysinfo.dwPageSize / allocsize) * allocsize;
		if (pageoffset < sizeofpage)
		{
			size_t memblockoffset = pageoffset % allocsize;

			Memblock* block = (Memblock*)(value - memblockoffset);

			ASSERT(block->m_magic == BLOCK_MAGIC);
			if (block->m_allocated)
			{
				if (!block->m_marked)
				{
					block->m_marked = true;

					if (block->m_kind)
					{
						byte* object = (byte*)(block+1);
						ClassType* pType = GetType(object);

						/*
						if (pType == typeof(TypeDatabase))
						{
							ASSERT(0);
						}
						*/

						ForwardFieldsNoRecurse(object, pType);
					}
					else
					{
						// top level data array,

						byte* ptr = (byte*)(block+1);
						ULONG_PTR* p = (ULONG_PTR*)(ptr);
						ULONG_PTR* end = (ULONG_PTR*)(ptr + allocsize);

						while (p < end)
						{
							gc_address(*p);
							++p;
						}
					}
				}
			}
		}
	}
}

#if 0
list<StaticRootObject, std_allocator>* staticRoots;

LFCEXT void _AddRoots(void* pvobject, ClassType* pMostDerivedClass)
{
	if (staticRoots == nullptr)
	{
		staticRoots = new list<StaticRootObject, std_allocator>;
	}

	staticRoots->push_back(StaticRootObject(pvobject, pMostDerivedClass));

#if 0
	byte* object = (byte*)pvobject;
	{
		int ncount = pMostDerivedClass->m_gcMembers.size();
		GCMember* declrefs = pMostDerivedClass->m_gcMembers.begin();

		while (ncount--)
		{
			const GCMember* decl = declrefs;

			int offset = decl->m_offset_and_kind>>1;
			int kind = decl->m_offset_and_kind & 1;

			void** ppchildpointer = (void**)(object + offset);

			_AddPersistentLiveRoot(ppchildpointer);

			++declrefs;
		}
	}

	{
		int ncount = pMostDerivedClass->m_gcArrayMembers.size();
		GCArrayMember* declrefs = pMostDerivedClass->m_gcArrayMembers.begin();

		if (declrefs == nullptr)
		{
			ASSERT(ncount == 0);
		}

		while (ncount--)
		{
			const GCArrayMember* decl = declrefs;

			Type* pType = decl->m_pType;

			ArrayBaseData* pArray = (ArrayBaseData*)(object + decl->m_offset);

			arrays.push_back(pArray);

			_AddPersistentLiveRoot(&pArray->m_pData);

			uint arraysize = pArray->m_nSize;
			uint elemsize = pType->get_sizeof();

			switch (pType->get_Kind())
			{
			case type_typedef:
				ASSERT(0);
				break;

			case type_class:
				{
					ASSERT(0);
					/*
					for (uint i = 0; i < arraysize; ++i)
					{
						uint8* object = (uint8*)pArray->m_pData + i * elemsize;

						ForwardFieldsNoRecurse(object, (ClassType*)pType);
					}
					*/
				}
				break;

			case type_pointer:
				{
					Type* pPointerTo = pType->GetPointerTo()->GetStripped();

					int kind = !(pPointerTo->get_Kind() == type_class && pPointerTo->GetClass()->HasVirtualTable());

					for (uint i = 0; i < arraysize; ++i)
					{
						uint8* object = (uint8*)pArray->m_pData + i * elemsize;

						_AddPersistentLiveRoot((void**)object);
					}
				}
				break;
			}

			++declrefs;
		}
	}
#endif
}
#endif

void _gc()
{
#ifdef _DEBUG
	Console::get_Out() << "gc...";
#endif

	HANDLE hCurrentThread = GetCurrentThread();

	// stop all other threads
	for (auto it = g_threads.begin(); it != g_threads.end(); ++it)
	{
		HANDLE hThread = *it;
		if (hThread != hCurrentThread)
		{
			SuspendThread(hThread);
		}
	}

	++memstatus.m_gccount;

	// This thread

	// registers
	saveregs();

	// NOTE: Don't bother to do Eax, since the calling function would have
	// saved it on the stack
#ifdef _M_IX86
//	if (WITHIN_GC_HEAP(regs.Eax)) gc_address_top(regs.Eax);
	if (WITHIN_GC_HEAP(regs.Ebx)) gc_address_top(regs.Ebx);
	if (WITHIN_GC_HEAP(regs.Ecx)) gc_address_top(regs.Ecx);
	if (WITHIN_GC_HEAP(regs.Edx)) gc_address_top(regs.Edx);
	if (WITHIN_GC_HEAP(regs.Esi)) gc_address_top(regs.Esi);
	if (WITHIN_GC_HEAP(regs.Edi)) gc_address_top(regs.Edi);
	if (WITHIN_GC_HEAP(regs.Ebp)) gc_address_top(regs.Ebp);
#elif _M_X64
//	if (WITHIN_GC_HEAP(regs.Rax)) gc_address_top(regs.Rax);
	if (WITHIN_GC_HEAP(regs.Rbx)) gc_address_top(regs.Rbx);
	if (WITHIN_GC_HEAP(regs.Rcx)) gc_address_top(regs.Rcx);
	if (WITHIN_GC_HEAP(regs.Rdx)) gc_address_top(regs.Rdx);
	if (WITHIN_GC_HEAP(regs.Rsi)) gc_address_top(regs.Rsi);
	if (WITHIN_GC_HEAP(regs.Rdi)) gc_address_top(regs.Rdi);
	if (WITHIN_GC_HEAP(regs.Rbp)) gc_address_top(regs.Rbp);

	if (WITHIN_GC_HEAP(regs.R8)) gc_address_top(regs.R8);
	if (WITHIN_GC_HEAP(regs.R9)) gc_address_top(regs.R9);
	if (WITHIN_GC_HEAP(regs.R10)) gc_address_top(regs.R10);
	if (WITHIN_GC_HEAP(regs.R11)) gc_address_top(regs.R11);
	if (WITHIN_GC_HEAP(regs.R12)) gc_address_top(regs.R12);
	if (WITHIN_GC_HEAP(regs.R13)) gc_address_top(regs.R13);
	if (WITHIN_GC_HEAP(regs.R14)) gc_address_top(regs.R14);
	if (WITHIN_GC_HEAP(regs.R15)) gc_address_top(regs.R15);
#elif AMIGA
	if (WITHIN_GC_HEAP(regs.a0)) gc_address_top(regs.a0);
	if (WITHIN_GC_HEAP(regs.a1)) gc_address_top(regs.a1);
	if (WITHIN_GC_HEAP(regs.a2)) gc_address_top(regs.a2);
	if (WITHIN_GC_HEAP(regs.a3)) gc_address_top(regs.a3);
	if (WITHIN_GC_HEAP(regs.a4)) gc_address_top(regs.a4);
	if (WITHIN_GC_HEAP(regs.a5)) gc_address_top(regs.a5);
	if (WITHIN_GC_HEAP(regs.a6)) gc_address_top(regs.a6);

//	if (WITHIN_GC_HEAP(regs.d0)) gc_address_top(regs.d0);
	if (WITHIN_GC_HEAP(regs.d1)) gc_address_top(regs.d1);
	if (WITHIN_GC_HEAP(regs.d2)) gc_address_top(regs.d2);
	if (WITHIN_GC_HEAP(regs.d3)) gc_address_top(regs.d3);
	if (WITHIN_GC_HEAP(regs.d4)) gc_address_top(regs.d4);
	if (WITHIN_GC_HEAP(regs.d5)) gc_address_top(regs.d5);
	if (WITHIN_GC_HEAP(regs.d6)) gc_address_top(regs.d6);
	if (WITHIN_GC_HEAP(regs.d7)) gc_address_top(regs.d7);
#else
#error "Unknown OS"
#endif

	// stack
	void* myesp;
#ifdef _M_IX86
	myesp = (void*)regs.Esp;
#elif _M_X64
	myesp = (void*)regs.Rsp;
#elif AMIGA
	myesp = (void*)regs.a7;
#endif
			// TODO? esp+4
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(myesp, &mbi, sizeof(mbi));

	ULONG_PTR* pptr = (ULONG_PTR*)mbi.BaseAddress;
	ULONG_PTR* endstack = (ULONG_PTR*)((char*)mbi.BaseAddress + mbi.RegionSize);

	while (pptr < endstack)
	{
		ULONG_PTR value = *pptr;
		if (WITHIN_GC_HEAP(value)) gc_address_top(value);

		++pptr;
	}

	// other threads

	for (list<HANDLE, std_allocator>::iterator it = g_threads.begin(); it != g_threads.end(); ++it)
	{
		HANDLE hThread = *it;

		if (hThread != hCurrentThread)
		{
			CONTEXT context;
			context.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;
			GetThreadContext(hThread, &context);

		// registers
#ifdef _M_IX86
			if (WITHIN_GC_HEAP(context.Eax)) gc_address_top(context.Eax);
			if (WITHIN_GC_HEAP(context.Ebx)) gc_address_top(context.Ebx);
			if (WITHIN_GC_HEAP(context.Ecx)) gc_address_top(context.Ecx);
			if (WITHIN_GC_HEAP(context.Edx)) gc_address_top(context.Edx);
			if (WITHIN_GC_HEAP(context.Edi)) gc_address_top(context.Edi);
			if (WITHIN_GC_HEAP(context.Esi)) gc_address_top(context.Esi);
			if (WITHIN_GC_HEAP(context.Ebp)) gc_address_top(context.Ebp);
#elif _M_X64
			if (WITHIN_GC_HEAP(context.Rax)) gc_address_top(context.Rax);
			if (WITHIN_GC_HEAP(context.Rbx)) gc_address_top(context.Rbx);
			if (WITHIN_GC_HEAP(context.Rcx)) gc_address_top(context.Rcx);
			if (WITHIN_GC_HEAP(context.Rdx)) gc_address_top(context.Rdx);
			if (WITHIN_GC_HEAP(context.Rdi)) gc_address_top(context.Rdi);
			if (WITHIN_GC_HEAP(context.Rsi)) gc_address_top(context.Rsi);
			if (WITHIN_GC_HEAP(context.Rbp)) gc_address_top(context.Rbp);

			if (WITHIN_GC_HEAP(context.R8)) gc_address_top(context.R8);
			if (WITHIN_GC_HEAP(context.R9)) gc_address_top(context.R9);
			if (WITHIN_GC_HEAP(context.R10)) gc_address_top(context.R10);
			if (WITHIN_GC_HEAP(context.R11)) gc_address_top(context.R11);
			if (WITHIN_GC_HEAP(context.R12)) gc_address_top(context.R12);
			if (WITHIN_GC_HEAP(context.R13)) gc_address_top(context.R13);
			if (WITHIN_GC_HEAP(context.R14)) gc_address_top(context.R14);
			if (WITHIN_GC_HEAP(context.R15)) gc_address_top(context.R15);
#else
#error "Unknown OS"
#endif

		// stack
			MEMORY_BASIC_INFORMATION mbi;
#ifdef _M_IX86
			VirtualQuery((void*)context.Esp, &mbi, sizeof(mbi));
#elif _M_X64
			VirtualQuery((void*)context.Rsp, &mbi, sizeof(mbi));
#else
#error "Unknown OS"
#endif

			ULONG_PTR* pptr = (ULONG_PTR*)mbi.BaseAddress;
			ULONG_PTR* endstack = (ULONG_PTR*)((char*)mbi.BaseAddress + mbi.RegionSize);

			while (pptr < endstack)
			{
				ULONG_PTR value = *pptr;
				if (WITHIN_GC_HEAP(value)) gc_address_top(value);

				++pptr;
			}
		}
	}

	for (size_t n = 0; n < TypeDatabase::pD->m_hmodules.size(); ++n)
	{
		Module* pModule = TypeDatabase::pD->m_hmodules[n];

		byte* imageBase = (byte*)pModule->GetHandle();
		if (imageBase == nullptr) continue;	// TODO, remove
		ASSERT(imageBase);

		byte* p = imageBase;
		uint16 magic = *(uint16*)p;

		ASSERT(magic == IMAGE_DOS_SIGNATURE);
		if (magic == IMAGE_DOS_SIGNATURE)
		{
			uint32 PEOffset;
			PEOffset = *(uint32*)(p + 0x3c);

			p += PEOffset;
			uint32 signature = *(uint32*)(p); p += 4;

			if (signature == IMAGE_NT_SIGNATURE)
			{
				IMAGE_FILE_HEADER* header = (IMAGE_FILE_HEADER*)p;
				p += sizeof(IMAGE_FILE_HEADER);

				size_t sizeOfData = 0;
				ULONG_PTR baseOfData = 0;

			//	p += header->SizeOfOptionalHeader;
				if (header->SizeOfOptionalHeader > 0)
				{
					ASSERT(header->SizeOfOptionalHeader >= sizeof(OptionalStandardHeader));

					IMAGE_OPTIONAL_HEADER_X* h = (IMAGE_OPTIONAL_HEADER_X*)p;

#ifdef _M_IX86
					ASSERT(h->Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC);
#elif _M_X64
					ASSERT(h->Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC);
#else
					#error "Unknown OS"
#endif

					p += sizeof(IMAGE_OPTIONAL_HEADER_X) + sizeof(IMAGE_DATA_DIRECTORY) * h->NumberOfRvaAndSizes;

					IMAGE_SECTION_HEADER* sectionHeader = (IMAGE_SECTION_HEADER*)p;
					for (uint i = 0; i < header->NumberOfSections; ++i)
					{
						if (!strncmp((const char*)sectionHeader->Name, ".data", 8) ||
							!strncmp((const char*)sectionHeader->Name, ".idata", 8))
						{
							ULONG_PTR* dataAddress = (ULONG_PTR*)(imageBase + sectionHeader->VirtualAddress);
							ULONG_PTR* endAddress = (ULONG_PTR*)((char*)dataAddress + sectionHeader->Misc.VirtualSize);

							while (dataAddress < endAddress)
							{
								ULONG_PTR value = *dataAddress;
								if (WITHIN_GC_HEAP(value)) gc_address_top(value);

								++dataAddress;
							}
						}
						
						++sectionHeader;
					}

				//	p = (uint8*)m_optionalStandardHeader + header->SizeOfOptionalHeader;

					/*
					ULONG_PTR* dataAddress = (ULONG_PTR*)(imageBase + baseOfData);
					ULONG_PTR* endAddress = (ULONG_PTR*)((char*)dataAddress + sizeOfData);

					while (dataAddress < endAddress)
					{
						ULONG_PTR value = *dataAddress;
						gc_address(value);

						++dataAddress;
					}
					*/
				}
#if 0
				for (int i = 0; i < m_header->NumberOfSections; ++i)
				{
					if ((sectionHeader->Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA) ||
						(sectionHeader->Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA))
					{
						base + sectionHeader->PointerToRawData
						/*
						sectionHeader->Misc.VirtualSize = Endian32(m_SectionHeader[j].Misc.VirtualSize);
						sectionHeader->VirtualAddress = Endian32(m_SectionHeader[j].VirtualAddress);
						sectionHeader->SizeOfRawData = Endian32(m_SectionHeader[j].SizeOfRawData);
						sectionHeader->PointerToRawData = Endian32(m_SectionHeader[j].PointerToRawData);
						*/
					//	sectionHeader[j].PointerToRelocations = Endian32(m_SectionHeader[j].PointerToRelocations);
					//	sectionHeader[j].PointerToLinenumbers = Endian32(m_SectionHeader[j].PointerToLinenumbers);
					//	sectionHeader[j].NumberOfRelocations = Endian16(m_SectionHeader[j].NumberOfRelocations);
					}

					++sectionHeader;
				}
#endif
			}
		}
	}

#if 0
	// globals
	for (list<void**, std_allocator>::iterator it = live->begin(); it != live->end(); ++it)
	{
		void* object = *(*it);
		if (object)
		{
			gc_address((ULONG_PTR)object);
		}
	}

	if (staticRoots)
	{
		// global static root objects
		for (list<StaticRootObject, std_allocator>::iterator it = staticRoots->begin(); it != staticRoots->end(); ++it)
		{
			StaticRootObject pRoot = *it;
			ForwardFieldsNoRecurse((uint8*)pRoot.m_address, pRoot.m_pType);
		}
	}
#endif

	gc_sweep();

	// Resume other threads
	for (list<HANDLE, std_allocator>::iterator it = g_threads.begin(); it != g_threads.end(); ++it)
	{
		HANDLE hThread = *it;

		if (hThread != hCurrentThread)
		{
			ResumeThread(hThread);
		}
	}

#ifdef _DEBUG
	Console::get_Out() << "...gc done\n";
#endif
}

}	// unnamed

// static
void GC::Collect()
{
	CriticalSectionLock lock(&crit_section);

#ifdef _DEBUG
	ULONGLONG startTime = 0;//GetTickCount64();
#endif

	try
	{
		_gc();
	}
	catch (Exception* e)
	{
		DebugTraceLn(e->get_Reason());

		MessageBox(nullptr, CStringw(e->get_Reason()), L"LFC", MB_OK);
	}

#ifdef _DEBUG
	ULONGLONG endTime = 0;//GetTickCount64();

	DebugTraceLn("gc time: " << (ULONG)(endTime - startTime)/1000.0 << "s");
#endif
}

/*
LFCEXT void* allocate_buffer(ULONG size)
{
	VERIFY(heap);
	return heap->allocate_buffer(size);
}
*/

LFCEXT int EvalExcept(int code, _EXCEPTION_POINTERS* p)
{
	if (code == STATUS_ACCESS_VIOLATION)
	{
		ASSERT(p->ExceptionRecord->NumberParameters == 2);

		if (p->ExceptionRecord->ExceptionInformation[0] == 1)
		{
			ULONG_PTR access_address = p->ExceptionRecord->ExceptionInformation[1];

			// garbage collect

			// Allow write

			Module* fmodule = nullptr;
			for (uint i = 0; i < TypeDatabase::pD->m_hmodules.size(); ++i)
			{
				Module* module = TypeDatabase::pD->m_hmodules[i];
				if (module->Contains(access_address))
				{
					fmodule = module;
					break;
				}
			}

			if (fmodule)
			{
			//	pModule->m_pages[0] = true;

				DWORD oldProtect;
				VirtualProtect((void*)access_address, 1, PAGE_READWRITE, &oldProtect);

				return EXCEPTION_CONTINUE_EXECUTION;
			}
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

LFCEXT void gc_Protect()
{
	HMODULE thisModule = _Module.GetHandle();

	for (size_t n = 0; n < TypeDatabase::pD->m_hmodules.size(); ++n)
	{
		byte* imageBase = (byte*)TypeDatabase::pD->m_hmodules[n];

		if (imageBase == (byte*)thisModule)
		{
			continue;
		}

		byte* p = imageBase;
		uint16 magic = *(uint16*)p;

		ASSERT(magic == IMAGE_DOS_SIGNATURE);
		if (magic == IMAGE_DOS_SIGNATURE)
		{
			uint32 PEOffset;
			PEOffset = *(uint32*)(p + 0x3c);

			p += PEOffset;
			uint32 signature = *(uint32*)(p); p += 4;

			if (signature == IMAGE_NT_SIGNATURE)
			{
				IMAGE_FILE_HEADER* header = (IMAGE_FILE_HEADER*)p;
				p += sizeof(IMAGE_FILE_HEADER);

				size_t sizeOfData = 0;
				ULONG_PTR baseOfData = 0;

			//	p += header->SizeOfOptionalHeader;
				if (header->SizeOfOptionalHeader > 0)
				{
					ASSERT(header->SizeOfOptionalHeader >= sizeof(OptionalStandardHeader));

					OptionalStandardHeader* pOptionalStandardHeader = (OptionalStandardHeader*)p;
					p += sizeof(OptionalStandardHeader);

					sizeOfData = pOptionalStandardHeader->SizeOfInitializedData + pOptionalStandardHeader->SizeOfUninitializedData;

					if (pOptionalStandardHeader->Magic == 0x10b)//	PE32
					{
						baseOfData = *(uint32*)p; p += 4;//	Address, relative to image base, of beginning of data section, when loaded into memory.
						WindowsHeader* m_windowsHeader = (WindowsHeader*)p; p += sizeof(WindowsHeader);
						p += sizeof(IMAGE_DATA_DIRECTORY) * m_windowsHeader->NumberOfRvaAndSizes;
					}
					else if (pOptionalStandardHeader->Magic == 0x20b)//	PE32+
					{
						ASSERT(0);
						//printf("PE32+\n");
					}

					IMAGE_SECTION_HEADER* sectionHeader = (IMAGE_SECTION_HEADER*)p;
					for (uint i = 0; i < header->NumberOfSections; ++i)
					{
						if (!strncmp((const char*)sectionHeader->Name, ".data", 8) ||
							!strncmp((const char*)sectionHeader->Name, ".idata", 8))
						{
							DWORD oldProtect;
							VirtualProtect(imageBase + sectionHeader->VirtualAddress, sectionHeader->Misc.VirtualSize, PAGE_READONLY, &oldProtect);
						}
						
						++sectionHeader;
					}

				//	p = (uint8*)m_optionalStandardHeader + header->SizeOfOptionalHeader;

					/*
					ULONG_PTR* dataAddress = (ULONG_PTR*)(imageBase + baseOfData);
					ULONG_PTR* endAddress = (ULONG_PTR*)((char*)dataAddress + sizeOfData);

					while (dataAddress < endAddress)
					{
						ULONG_PTR value = *dataAddress;
						gc_address(value);

						++dataAddress;
					}
					*/
				}
			}
		}
	}
}

LFCEXT void* reallocate_buffer(void* buffer, size_t size)
{
	ASSERT(0);
	return nullptr;
	//return heap->reallocate_buffer(buffer, size);
}

LFCEXT size_t get_buffer_size(const void* buffer)
{
	ASSERT(0);
	return 0;
//	return heap->get_buffer_size(buffer);
}

LFCEXT void free_object(Object* pv)
{
	free_buffer(pv);
}

LFCEXT void free_buffer(void* pv)
{
	if (pv == nullptr) return;

	byte* p = (byte*)pv;
	ULONG_PTR value = (ULONG_PTR)pv;

	if (p >= data+sizeof(Memblock) && p < enddata)
	{
		ULONG_PTR pageaddr = value & ~pagesize_mask;

		ULONG_PTR offset = (p - data);
		size_t npage = offset >> pagesize_bits;
		size_t pageoffset = offset & pagesize_mask;
		size_t allocsize = pages[npage].m_allocsize;

		size_t memblockoffset = pageoffset % allocsize;

		if (memblockoffset != sizeof(Memblock))
		{
			raise(SystemException("not a valid memory block"));
		}

		Memblock* block = (Memblock*)pv - 1;

		if (block->m_magic != BLOCK_MAGIC)
		{
			raise(SystemException("not a valid memory block"));
		}

		if (!block->m_allocated)
		{
			raise(SystemException("memory block already freed"));
		}

		uint allocslot = getallocslot(allocsize);

		CriticalSectionLock lock(&crit_section);

		block->m_allocated = false;
		block->setnextfree(freelist[allocslot]);
		freelist[allocslot] = block;

		--pages[npage].m_n;

#ifdef _DEBUG
		invalidate_mem(block+1, allocsize-sizeof(Memblock));
#endif
	}
	else
	{
		free(pv);
	}
}

LFCEXT void _AddPersistentLiveRoot(void** pp)
{
	if (live == nullptr)
	{
		live = new list<void**, std_allocator>;
	}

	System::live->insert(System::live->end(), pp);
}

void AddPersistentLiveRoot(void** pp)
{
#if 0

#if WIN32
	if (false)
	{
		m_live_crit.Lock();
	}
#endif

	_AddPersistentLiveRoot(pp);

#if WIN32
	if (false)
	{
		m_live_crit.Unlock();
	}
#endif

#endif
}

}	// System

/*
template<class T> ref<T>::ref(T* p)
{
	m_p = p;

	if (m_p)
	{
		m_it = live.insert(live.end(), m_p);
	}
	else
	{
		m_it = live.end();
	}
}

template<class T> ref<T>::ref(const ref<T> & other)
{
	m_p = other.m_p;

	if (m_p)
	{
		m_it = live.insert(live.end(), m_p);
	}
	else
	{
		m_it = live.end();
	}
}

template<class T> ref<T>::~ref()
{
	live.erase(m_it);
}

template<class T>
ref<T> & ref<T>::operator = (const ref<T> & other)
{
	if (m_p != other.m_p)
	{
		if (other.m_p)
		{
			if (m_p == nullptr)
			{
				m_it = live.insert(live.end(), other.m_p);
			}
		}
		else
		{
			if (m_p != nullptr)
			{
				live.erase(m_it);
				m_it = live.end();
			}
		}

		m_p = other.m_p;
	}

	return *this;
}
*/

#if 0
__live_object_ptr_base::__live_object_ptr_base(void* p) : m_p(p)
{

#if WIN32
//	m_live_crit.Lock();
#endif

	if (System::live == nullptr)
	{
		System::live = new System::list<void**, System::std_allocator>;
	}

//	if (m_p)
	{
		/*m_it =*/ System::live->insert(System::live->end(), &m_p);
	}
	/*
	else
	{
		m_it = System::live->end();
	}
	*/

#if WIN32
//	m_live_crit.Unlock();
#endif
}

__live_object_ptr_base::~__live_object_ptr_base()
{
	if (m_p)
	{
#if WIN32
		if (false)
		{
			m_live_crit.Lock();
		}
#endif
	//	System::live->erase(m_it);
#if WIN32
		if (false)
		{
			m_live_crit.Unlock();
		}
#endif
	}
}
#endif

#if 0

__live_object_ptr_base& __live_object_ptr_base::operator = (const __live_object_ptr_base & other)
{
	m_p = other.m_p;

#if 0
#if WIN32
	if (false)
	{
		m_live_crit.Lock();
	}
#endif

	if (System::live == nullptr)
	{
		System::live = new System::list<void**, System::std_allocator>;
	}

	if (m_p != other.m_p)
	{
		if (other.m_p)
		{
			if (m_p == nullptr)
			{
				m_it = System::live->insert(System::live->end(), &m_p);
			}
		}
		else
		{
			if (m_p != nullptr)
			{
				System::live->erase(m_it);
				m_it = System::live->end();
			}
		}

		m_p = other.m_p;
	}

#if WIN32
	if (false)
	{
		m_live_crit.Unlock();
	}
#endif
#endif

	return *this;
}
#endif