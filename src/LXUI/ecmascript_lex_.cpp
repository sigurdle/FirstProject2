#include "stdafx.h"
//#include <istream>
//#include <ostream>
#include <iostream>

#undef max
#undef min

using namespace std;

#include "../../Win32/LXUI/ecmascript_parse.tab.hh"

#include "ecmascript_lex.cc"

#if 0

#include "ecmascript_ast.h"

namespace System
{
namespace ecma
{
using namespace std;

#include "ecmascript_parse.tab.h"
#include "ecmascript_lex.c"


void ecmascripterror(char const * err)
{
	TRACE(err);
}

int ecmascriptwrap()
{
	return 1;	// terminate lex scanner
}

}

}

#endif
