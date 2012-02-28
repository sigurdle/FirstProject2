#pragma once

#include "preprocessor.h"
//#include "cpp_ast.h"
//#include "cpp_translate.h"

namespace System
{

// TODO, not in translate.h
class GlobalSymbol
{
public:
	char* importDLL;
	int ordinalHint;
	char* publicName;

	long Value;

//	nlist* refs;
	vector<uint32> refs;

	char defined;
};

// TODO, not in translate.h
class CCompileFile
{
public:
	CTOR CCompileFile()
	{
		m_warnings = 0;
		m_errors = 0;
	}

	int m_warnings;
	int m_errors;

#if 0
	void __cdecl jwarn(const char* msg, PP::CFileLocation& location)
	{
	//	printlocation("warn");
		printf(msg);
		printf("\n");

		m_warnings++;
	}

	void __cdecl jerror(const char* msg, PP::CFileLocation& location)
	{
		printf(msg);
		printf("\n");

		m_errors++;
	}
#endif

#if 0
//	CTStatement* TransStatement(T_Declarator* frame, cpp::CStatement* pstmt, cpp::Scope* pScope, cpp::CGlobal* pGlobal, CTSwitch* pInnermostSwitch, Temp_label* break_target);
//	Tr_Exp* TransExpression(T_Declarator* frame, cpp::CExpression* pExpr, cpp::CGlobal* pGlobal, cpp::Scope* pScope);
	Tr_Exp* ConvertExpressionType(Tr_Exp* pExpr, cpp::Type* p2Type, BOOL b2Const = FALSE);
#endif
};

typedef map<System::StringA, GlobalSymbol*> gsymmap;
typedef map<System::StringA, gsymmap> idmap;

class CConfiguration
{
public:
	CTOR CConfiguration()
	{
		m_errors = 0;
		m_warnings = 0;

		m_exeType = -1;
	}

	System::StringA m_name;
	System::StringA m_outputPathName;
	System::StringA m_outputFileName;

	int m_exeType;

	filevectortype objectfiles;

	gsymmap globsyms;

	int m_errors;
	int m_warnings;

	int Pass1();

	int COFF_Pass2(FILE* fileout);
	int MachO_Pass2(FILE* fileout);
	int AmigaHunk_Pass2(FILE* fileout);

	int Link(FILE* fileout);

	PP::CPreprocessor* pPP;

	int CompileFile(const char* filepath, char* fileoutpath);

};

}
