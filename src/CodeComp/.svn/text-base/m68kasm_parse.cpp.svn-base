#include "stdafx.h"
//#include "m68kasm_parse.h"

//#include "m68kasm_ast.h"

namespace System
{
namespace m68kasm
{
using namespace std;

#include "m68kasm_parse.tab.c"

struct yy_buffer_state;
yy_buffer_state* m68kasm_scan_string(const char* str);
int m68kasmtparse();

/*
extern A_Class* g_CompilationUnit;
*/

CodeCompExt void /*A_Class* */ Parse(StringIn str)
{
	yy_buffer_state* state = m68kasm_scan_string(CString(str));
	int error = m68kasmparse();
	ASSERT(error == 0);
	//A_Class* p = g_CompilationUnit;//ecma::ecmascript_lval.elem_list;

//	return p;
}

}
}
