#include "stdafx.h"

// Compare two objects for equivalence
bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther)
{
	if (pThis == NULL && pOther == NULL)
		return true; // They are both NULL objects

	if (pThis == NULL || pOther == NULL)
		return false; // One is NULL the other is not

	CComPtr<IUnknown> punk1;
	CComPtr<IUnknown> punk2;
	pThis->QueryInterface(IID_IUnknown, (void**)&punk1);
	pOther->QueryInterface(IID_IUnknown, (void**)&punk2);
	return punk1 == punk2;
}
