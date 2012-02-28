#pragma once

bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

#include "..\UIT\UIT.h"
#include "..\LXFramework\edoc.h"

void ComErrorMsg(HWND hWnd, _com_error &e);
