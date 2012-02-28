#include "stdafx.h"
#include "SQL.h"

#include "sql_a.h"

namespace System
{
namespace sql
{
namespace ast
{
#include "sql_parse.tab.h"

#include "lex.sql_.c"

yy_buffer_state* get_current_buffer()
{
	return yy_current_buffer;
}

char* get_buf_p()
{
	*yy_c_buf_p = yy_hold_char;
	return yy_c_buf_p;
}

int sql_wrap()
{
	return 1;	// terminate lex scanner
}

}
}
}
