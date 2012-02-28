#include "stdafx.h"
#include "cpp_ast.h"

namespace System
{
namespace cpp
{
namespace ast
{
using namespace std;

#define YY_NEVER_INTERACTIVE 0


#include "cpp_exp_parse.tab.h"

#include "lex.cpp2_.c"

extern "C" int cpp2_wrap()
{
	return 1;	// terminate lex scanner
}

}
}
}
