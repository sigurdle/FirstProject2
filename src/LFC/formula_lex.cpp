#include "stdafx.h"
#include "LFC.h"

//#include "sql_a.h"

#if 0
#include "formula_parse.tab.h"

#include "lex.formula_.c"

#endif

namespace System
{

void formula_error(char const * err)
{
	Console::get_Out() << err << endl;
}

int formula_wrap()
{
	return 1;	// terminate lex scanner
}

}
