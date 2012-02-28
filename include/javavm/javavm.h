#ifndef javavm_h
#define javavm_h

#ifndef javavmext
#define javavmext DECLSPEC_DLLIMPORT
#endif

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

//#include <stdio.h>
//#include <stdarg.h>

#include "jni.h"
#include "JavaClassFile.h"
#include "JavaClassFileLoader.h"
#include "JavaVirtualMachine.h"

#endif // javavm_h
