// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9C21E6CA_04C2_4428_8EF9_0C9E0E5C1861__INCLUDED_)
#define AFX_STDAFX_H__9C21E6CA_04C2_4428_8EF9_0C9E0E5C1861__INCLUDED_

// Change these values to use different versions

#define WINVER		0x0500
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#define _WIN32_WINNT 0x0500
#define _ATL_APARTMENT_THREADED

/*
#define STRICT
#define WINVER 0x0500

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#define _ATL_APARTMENT_THREADED
*/

#include <atlbase.h>
#include <atlapp.h>

extern CServerAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>

// My additions
#include <atlframe.h>

#include <AtlDlgs.h>
#include <AtlCtrls.h>
#include <AtlMisc.h>

#include <comdef.h>

#include <math.h>

#include <docobj.h>

#include <oledlg.h>
#pragma comment(lib, "oledlg.lib")

#pragma comment(lib, "atl.lib")

#include <icm.h>
#pragma comment(lib, "mscms.lib")

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ASSERT(x)	ATLASSERT(x)
#define TRACE	ATLTRACE
#define VERIFY(x)	(x)

extern bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);
extern double ConvertUserUnitToSpecifiedValue(double value, short unitType);
extern double ConvertSpecifiedValueToUserUnit(short unitType, double specifiedValue);

extern double GetWindowTextValue(HWND hWnd, BOOL* bTrans = NULL);
extern double GetDlgItemValue(HWND hWnd, UINT nID, BOOL* bTrans = NULL);
extern void SetWindowTextValue(HWND hWnd, double value, short unit);
extern void SetWindowTextValueCheckForSame(HWND hWnd, double value, short unit);
extern void SetDlgItemValue(HWND hWnd, UINT nID, double value, short unit);

extern double GetDlgItemAngle(HWND hWnd, UINT nID, BOOL* bTrans = NULL);
extern void SetDlgItemAngle(HWND hWnd, UINT nID, double value);

/// GDI Plus
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

typedef struct _ARGBPixel
{
	BYTE blue, green, red, alpha;
}
ARGBPixel;

//

#include "Tom.h"

#include "..\..\Utils\UPtrList.h"
#include "..\..\Utils\UPtrArray.h"
#include "..\..\Utils\UString.h"
#include "..\..\Utils\UArray.h"
#include "..\..\Utils\Draw.h"
#include "..\..\Utils\DblPoint.h"
//#include "..\..\Utils\Rect.h"
#include "..\..\Utils\IEnumfe.h"

#include "olemisc.h"

typedef struct _CDblRect
{
	_CDblRect()
	{
	}

	_CDblRect(double l, double t, double r, double b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	double left, top, right, bottom;
	double Width() { return right-left;}
	double Height() { return bottom-top;}
}
CDblRect;

#ifdef _DEBUG
#pragma comment(lib, "..\\..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\..\\Utils\\Release\\Utils.lib")
#endif

#define BST_MASK	(BS_CHECKBOX|BS_AUTOCHECKBOX|BS_RADIOBUTTON|BS_3STATE|BS_AUTO3STATE|BS_AUTORADIOBUTTON)

typedef HRESULT (*HTMLModalDialogProc)(HWND hParent, BSTR url, VARIANT* pvarArgIn, BSTR pchOptions, VARIANT* pvarArgOut);
typedef HRESULT (*HTMLModelessDialogProc)(HWND hParent, BSTR url, VARIANT* pvarArgIn, BSTR pchOptions);

//#import "..\DOMCOREMOD\DOMCOREMOD.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9C21E6CA_04C2_4428_8EF9_0C9E0E5C1861__INCLUDED_)
