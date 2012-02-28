// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__BADED4B3_0EFC_4F4B_BBEA_BF16E6BCC077__INCLUDED_)
#define AFX_STDAFX_H__BADED4B3_0EFC_4F4B_BBEA_BF16E6BCC077__INCLUDED_

#define STRICT

#define WINVER		0x0500
#define _WIN32_IE	0x0500

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#define HTMLEXT DECLSPEC_DLLEXPORT

#include "LFC/LFC.h"

namespace System
{
class HTMLModule : public Module
{
public:
	HTMLModule();

	static HTMLModule _Module;
};
}

//#include <simpdata.h>	// OLEDB
//#include <Shlobj.h>
//#include <docobj.h>

/*
// Calculates fixed point from floating point.
#define __FXPTMANTISSA(d, f)  ( (DWORD)d << f )
#define __FXPTFRACTION(d, f)  ( (DWORD)ldexp((d - (DWORD)d), f) )
#define __FXPT32(d, f)      ( __FXPTMANTISSA(d, f) | __FXPTFRACTION(d, f) )

#define __FXPT2DOT30(d)   __FXPT32(d, 30)
#define __FXPT16DOT16(d)  __FXPT32(d, 16)
*/

#include "LXML/LXML.h"

#endif // !defined(AFX_STDAFX_H__BADED4B3_0EFC_4F4B_BBEA_BF16E6BCC077__INCLUDED)
