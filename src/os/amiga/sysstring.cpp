#include <oleauto.h>

extern "C"
{

BSTR SysAllocString(const OLECHAR* p)
{
	return NULL;
}

BSTR SysAllocStringLen(const OLECHAR* p, unsigned int len)
{
	return NULL;
}

BSTR SysAllocStringByteLen(const char FAR*  psz, unsigned int len)
{
	return NULL;
}

void SysFreeString(BSTR)
{
}

long SysStringLen(BSTR)
{
	return 0;
}

HRESULT SysStringByteLen(BSTR  bstr)
{
	return NULL;
}

}