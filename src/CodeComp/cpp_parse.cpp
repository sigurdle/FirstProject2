#include "StdAfx.h"
#include "preprocessor.h"
#include "cpp_ast.h"

namespace System
{
extern PP::CPreprocessor* pPP2;
extern kwmap kwm;

using namespace std;

namespace cpp
{
	namespace ast
	{
#include "cpp_parse.tab.h"

#include "cpp_parse.tab.c"
	}
}
}
