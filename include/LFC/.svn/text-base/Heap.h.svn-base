#if AMIGA

class __type_info2
{
public:
	virtual ~__type_info2();

public://	private:
	 const char *__type_name;
};

#endif

namespace System
{

#define MAX_ALLOCSIZE	0x1000000

class HeapRecord
{
public:

	inline CTOR HeapRecord(ULONG f, int kind)
	{
		v = f | kind;
	}

	inline ULONG get_f() const
	{
		return v & ~7;
		//return f;
	}

	inline void set_f(ULONG f_)
	{
		v = (v & 7) | f_;
		//f = f_;
	}

	inline int get_kind() const
	{
		return v & 1;
		//return kind;
	}

	inline void set_kind(int kind_)
	{
		v = (v & ~1) | kind_;
		//kind = kind_;
	}

	inline ULONG get_size() const
	{
		return v2 & 0xffffff;
	}

	inline void set_size(ULONG size)
	{
		ASSERT((size & ~0xffffff) == 0);
		v2 = size;
	}

protected:

	//HeapRecord* f;

	ULONG v;

		/*
	ULONG f : 31,
			kind : 1;
			*/

			//marked : 1;

	ULONG v2;
};

/*
class HeapRecordMem : public HeapRecord
{
public:
	ULONG m_size;
};
*/

class LFCEXT Heap
{
public:

	CTOR Heap();
	CTOR Heap(ULONG size);

	virtual ~Heap();

	uint8* m_data;
	uint8* m_next;
	ULONG m_size;

	//DWORD m_threadId;

	int m_toggle;

	void ClearGarbage();

//	void* allocate(int size);

//	void sweep();

	void Copy();

	//void maybe_gc();

	Object* allocate_object(ULONG size);
	void* allocate_buffer(ULONG size);
	void* reallocate_buffer(void* buffer, ULONG size);
	ULONG get_buffer_size(const void* pv);

	void deallocate_buffer(void* p);

#if WIN32
	CriticalSection m_crit;
#endif

protected:

	//HANDLE m_hEvent_gc;
//	void WaitFor_gc();

	inline HeapRecord* Forward(HeapRecord* p, ClassType* pDebugType, int debugOffset);

	HeapRecord* Forward(HeapRecord* p, ClassType* pMostDerivedClass);
	inline HeapRecord* ForwardNoRecurse(HeapRecord* p, ClassType* pMostDerivedClass);

	void ForwardFields(uint8* object, ClassType* pMostDerivedClass);
	void ForwardFieldsNoRecurse(uint8* object, ClassType* pMostDerivedClass);

	void ForwardField(void ** ppchildpointer, Type* pType);
//	void ForwardFieldNoRecurse(void ** ppchildpointer, int kind, ClassType* pDebugType, int debugOffset);
	void ForwardFieldNoRecurse_Kind(void ** ppchildpointer, int kind, ClassType* pDebugType, int debugOffset);
};

}	// System
