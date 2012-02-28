#include <rpc.h>
#include <oaidl.h>

void _com_issue_error(HRESULT hr)
{
}

EXTERN_C void VariantInit(VARIANTARG*)
{
}

EXTERN_C HRESULT VariantClear(VARIANTARG*)
{
	return S_OK;
}

EXTERN_C HRESULT VariantCopy(VARIANTARG *  pvargDest, VARIANTARG *  pvargSrc)
{
	return S_OK;
}

EXTERN_C HRESULT VariantChangeType(VARIANTARG *  pvargDest, VARIANTARG *  pvargSrc, unsigned short wFlags, VARTYPE vt)
{
	return S_OK;
}
