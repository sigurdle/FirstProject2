#include "stdafx.h"

#include <stdarg.h>

#include "../CodeComp/cpp_ast.h"

namespace cpp
{

#include "cpp_exp_parse.tab.h"

#include "cpp_exp_parse.tab.c"

void cpp_exp_error (char const *s)
{
/*
	PP::macromap::iterator macro = pPP2->m_defines.find("__RPC_USER");	// RPC_ENTRY
	if (macro != pPP2->m_defines.end())
	{
		PP::CDefine* p = (*macro).second;
		p;
	}	
*/

//	fprintf(stderr, "%s(%d): ", pPP2->m_pFile->m_filepath.c_str(), pPP2->m_pFile->m_line+1);
	TRACE ("%s\n", s);
}

}