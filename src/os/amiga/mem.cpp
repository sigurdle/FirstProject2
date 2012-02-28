#include <ole2.h>
#include <stdlib.h>

extern "C"
{

void* CoTaskMemAlloc(SIZE_T cb)
{
	return malloc(cb);
}

void* CoTaskMemReAlloc(void* p, SIZE_T cb)
{
	return realloc(p, cb);
}

void CoTaskMemFree(void* p)
{
	return free(p);
}

}
