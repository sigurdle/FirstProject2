// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__176C97C8_9996_4263_B5CA_F966CA88FDCD__INCLUDED_)
#define AFX_STDAFX_H__176C97C8_9996_4263_B5CA_F966CA88FDCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
//#define _ATL_APARTMENT_THREADED
//#define _ATL_FREE_THREADED

#include "LFC/LFC.h"

#define LMEDIAEXT	DECLSPEC_DLLEXPORT

/*
namespace System
{
class LMediaModule : public Module
{
public:
	LMediaModule();
};

#if WIN32
extern LMediaModule _Module;
#endif
}
*/

#endif // !defined(AFX_STDAFX_H__176C97C8_9996_4263_B5CA_F966CA88FDCD__INCLUDED)
