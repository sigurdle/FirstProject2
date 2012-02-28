#if !defined(AFX_STDAFX_H__53F9331D_E982_42B4_8ABA_6CAD7D23BE06__INCLUDED_)
#define AFX_STDAFX_H__53F9331D_E982_42B4_8ABA_6CAD7D23BE06__INCLUDED_

#if WIN32

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#elif AMIGA

#endif // AMIGA

#include "../LFC/LFC.h"
extern Module _Module;

#include "../../include/Draw/Draw.h"

#define UIEXT DECLSPEC_DLLEXPORT

#endif // !defined(AFX_STDAFX_H__53F9331D_E982_42B4_8ABA_6CAD7D23BE06__INCLUDED)
