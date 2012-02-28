#ifndef ActionScript2_h
#define ActionScript2_h

/*
#ifdef __LERSTAD__
#define import2(x) #import x
#else
#define import2(x) ## include x
#endif

import2("LFC/LFC.h")
*/

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#ifndef ActionScript2Ext
#define ActionScript2Ext DECLSPEC_DLLIMPORT
#endif

#include "ActionScript.h"

namespace System
{
ActionScript2Ext void test_callme(void (*f)(Object*), Object* p);
}

#endif
