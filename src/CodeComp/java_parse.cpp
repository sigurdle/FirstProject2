#include "stdafx.h"
#include "java_parse.h"

#include "java_ast.h"

namespace System
{
namespace java
{
using namespace std;

#include "java_parse.tab.c"

struct yy_buffer_state;
yy_buffer_state* java_scan_string(const char* str);
int javatparse();

extern A_Class* g_CompilationUnit;

CodeCompExt A_Class* Parse(StringA* str)
{
	yy_buffer_state* state = java_scan_string(str->c_str());
	javaparse();
	A_Class* p = g_CompilationUnit;//ecma::ecmascript_lval.elem_list;

	return p;
}

}
}
