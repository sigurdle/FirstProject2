// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__218D361E_5256_4D6D_BAB4_BC6BFB603406__INCLUDED_)
#define AFX_STDAFX_H__218D361E_5256_4D6D_BAB4_BC6BFB603406__INCLUDED_

// Change these values to use different versions
#define WINVER		0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100


#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>
#include <atlmisc.h>

#include <vector>

#define ASSERT(x) ATLASSERT(x)

#include "../gm/gmVec3.h"

#include <math.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__218D361E_5256_4D6D_BAB4_BC6BFB603406__INCLUDED_)
