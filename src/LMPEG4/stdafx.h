#if !defined(AFX_STDAFX_H__BBE2457F_5A9B_4D36_A964_0AE662A6F740__INCLUDED_)
#define AFX_STDAFX_H__BBE2457F_5A9B_4D36_A964_0AE662A6F740__INCLUDED_


#if WIN32

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#endif

#define MPEG4EXT DECLSPEC_DLLEXPORT

#include "../LFC/LFC.h"

#include <math.h>
#include <limits.h>
#include <float.h>

#include "../LMedia/LMedia.h"

namespace System
{

class HRESULT_throw
{
public:
	ErrorCode hr;

	HRESULT_throw(ErrorCode _hr)
	{
		hr = _hr;
	}

	ErrorCode operator = (ErrorCode _hr)
	{
		hr = _hr;
		if (hr < 0)
			throw hr;

		return hr;
	}
};

}

#endif // !defined(AFX_STDAFX_H__BBE2457F_5A9B_4D36_A964_0AE662A6F740__INCLUDED)
