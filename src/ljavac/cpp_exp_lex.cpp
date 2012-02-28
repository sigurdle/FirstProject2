#include "stdafx.h"
#include "../CodeComp/cpp_ast.h"

namespace System
{
namespace cpp
{
#define YY_NEVER_INTERACTIVE 0


#include "cpp_exp_parse.tab.h"

#include "lex.cpp_exp_.c"

extern "C" int cpp_exp_wrap()
{
	return 1;	// terminate lex scanner
}
}
}
