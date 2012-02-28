#include "stdafx.h"

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
