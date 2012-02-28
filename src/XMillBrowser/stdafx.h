// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BC351E19_E119_41EF_9096_02158F860966__INCLUDED_)
#define AFX_STDAFX_H__BC351E19_E119_41EF_9096_02158F860966__INCLUDED_

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_IE	0x0500
#define _RICHEDIT_VER	0x0100

#define _WIN32_WINNT 0x0500
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
#include <atlapp.h>

extern CServerAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>

#define ASSERT(x)	ATLASSERT(x)
#define TRACE	ATLTRACE

#include "..\..\Utils\UPtrList.h"
#include "..\..\Utils\UPtrArray.h"
#include "..\..\Utils\UString.h"
#include "..\..\Utils\UArray.h"
/*
#include "..\..\Utils\Draw.h"
#include "..\..\Utils\DblPoint.h"
//#include "..\..\Utils\Rect.h"
#include "..\..\Utils\IEnumfe.h"

typedef struct _CDblRect
{
	double left, top, right, bottom;
	double Width() { return right-left;}
	double Height() { return bottom-top;}
}
CDblRect;
*/
#ifdef _DEBUG
#pragma comment(lib, "..\\..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\..\\Utils\\Release\\Utils.lib")
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BC351E19_E119_41EF_9096_02158F860966__INCLUDED_)
