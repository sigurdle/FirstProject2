#include "stdafx.h"
#include "XPath.h"

namespace System
{
namespace XPath
{

using namespace std;

#include "lex.xpath_.c"

void xpath_error(char const* msg)
{
//	TRACE("Error: %s\n", msg);
}

char* get_buf_p()
{
	*yy_c_buf_p = yy_hold_char;
	return yy_c_buf_p;
}

extern "C" int xpath_wrap()
{
	return 1;	// terminate lex scanner
}

}
}
