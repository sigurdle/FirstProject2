#include "stdafx.h"
#include "SQL.h"

#include "sql_a.h"

#include "XPath/XPath.h"

/*

namespace System
{
namespace XPath
{
//#include "../XPath/xpath_parse.tab.h"
	parse
}
}
*/

struct yy_buffer_state;

int XPathExt xpath_parse(yy_buffer_state* b);
int XPathExt xpath_parse(char* p, char **pp, int* ptoken);

namespace System
{
namespace sql
{
namespace ast
{
struct yy_buffer_state;

#include "sql_parse.tab.c"

void sql_error(char const * err)
{
	printf(err);
}

void sql__flush_buffer(yy_buffer_state*);
yy_buffer_state* sql__scan_string(const char *yy_str );

char* get_buf_p();

yy_buffer_state* get_current_buffer();

void parse_xpath()
{
//	sql__flush_buffer(get_current_buffer());

	char* p = get_buf_p();

//	int error = ::xpath_parse((::yy_buffer_state*)get_current_buffer());

	int token;
	int error = ::xpath_parse(p, &p, &token);
	if (error != 0)
	{
		;
	}

	/* TODO, must somehow synchronize token from xpath to sql, one solution would be
	 to have all tokens from xpath also in sql (not in the lexer, just inside parse.y)
*/

	/*System::XPath::yy_buffer_state* state =*/ sql__scan_string(p);
	sql_char = token;
}

}	// ast
}	// sql
}	// System
