#ifndef __SQL_h__
#define __SQL_h__

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LFC.typeinfo"
#else
#include "LFC/LFC.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/XPath.typeinfo"
#else
#include "XPath/XPath.h"
#endif

#ifndef SQLEXT
#define SQLEXT DECLSPEC_DLLIMPORT
#endif

#include "db.h"

#endif // __SQL_h__
