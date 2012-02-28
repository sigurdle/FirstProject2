#ifndef CodeComp_h
#define CodeComp_h

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#include "Comp2.h"
#include "cpp_ast.h"
#include "cpp_compile.h"
#include "ir.h"
#include "AOut.h"

#include "x86assem.h"
#include "m68kassem.h"
#include "ppcassem.h"
//#include "javadisasm.h"

namespace System
{
CodeCompExt int MakeTypes(StringIn headerfilename, StringIn outdirname);
CodeCompExt int ParseMap(StringIn mapfilename, StringIn typeinfofilename, StringIn adfilename);
}

#endif // CodeComp_h
