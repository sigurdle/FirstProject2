#include <new.h>

#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/intuition.h>

#if 0
void *operator new (size_t size)// throw (std::bad_alloc)
{
return AllocVec(size, MEMF_CLEAR|MEMF_ANY);
}

void *operator new[] (size_t size)// throw (std::bad_alloc)
{
return AllocVec(size, MEMF_CLEAR|MEMF_ANY);
}

void operator delete (void *mem)// throw()
{
	FreeVec(mem);
}

void operator delete[] (void *mem)// throw()
{
	FreeVec(mem);
}
#endif

/*
extern "C" void exit(int)
{
}
*/

class ctest
{
public:
	int j, k;

	virtual int test()
	{
		return 24;
	}
};

#if 0
extern "C" LONG CreateXAMLDocument(void** pVal)
{
	CComObject<CLXUIDocument>* p;
	CComObject<CLXUIDocument>::CreateInstance(&p);
	/*
	p->AddRef();
	
	*pVal = (void*)static_cast<ILXUIDocument*>(p);
	*/

	return 0;
}
#endif