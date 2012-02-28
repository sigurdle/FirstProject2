#include "stdafx.h"

#include "CodeComp/ir.h"
#include "ecmascript_ast.h"

/*
#undef min
#undef max

#include "../../Win32/LXUI/ecmascript_parse.tab.hh"
*/

namespace System
{
namespace ecma
{
using namespace std;

#undef __GNUC_MINOR__	// hm..
#include "ecmascript_parse.tab.c"
}
}
