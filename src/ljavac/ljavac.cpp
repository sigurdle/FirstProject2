// ljavac.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include "../LFC/disasm.h"

#include "../CodeComp/cpp_ast.h"
#include "../CodeComp/cpp_translate.h"
#include "../CodeComp/codegen.h"
//#include "preprocessor.h"

#include "../CodeComp/link.h"

#ifdef _DEBUG
#pragma comment(lib, "../LFC/Debug/LFC.lib")
#else
#pragma comment(lib, "../LFC/Release/LFC.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../CodeComp/Debug/CodeComp.lib")
#else
#pragma comment(lib, "../CodeComp/Release/CodeComp.lib")
#endif

//void cpp_translation_unit(cpp::CGlobal* pGlobal, PP::CPreprocessor*);
//void WriteFileOBJ(FILE* fp, cpp::CGlobal* pGlobal, CCodeGenerator* pGenCode);
//void preprocessing_file();

//extern int m_warnings;
//extern int m_errors;

#include <direct.h>

/*
class CDefine
{
};

class CConfiguration
{
public:
	std::vector<
};
*/

// TODO, remove, not used
namespace cpp
{
class A_Exp * g_exp;
}

#if 0
#include "pp_parse.tab.h"

std::string PP_Token::toString()
{
	if (kind == PP_Token::PP_IDENTIFIER)
		return id;
	else if (kind == PP_CHAR)
	{
		char c2[2] = {c, 0};
		return c2;
	}

	ATLASSERT(0);
	return "";
}
#endif

#if 0

PP_Group* pp_file;
PP_TokenList* tlist;

PP_TokenList* tail;

PP_TokenList* Reverse(PP_TokenList* p)
{
	if (p->tail)
	{
		PP_TokenList* p2 = Reverse(p->tail);
		p->tail->tail = p;
		p->tail = NULL;
		p = p2;
	}
	return p;
}

long PP_evaluate(A_Exp* exp)
{
	switch (exp->kind)
	{
	case A_Exp::A_INT32:
		{
			return exp->int32;
		}
		break;

	case A_Exp::A_BINOP:
		{
			long v1 = PP_evaluate(exp->binop.left);
			long v2 = PP_evaluate(exp->binop.right);

			switch (exp->binop.op)
			{
			case '+':	return v1 + v2;
			case '-':	return v1 - v2;
			case '*':	return v1 * v2;
			case '/':	return v1 / v2;
			case '%':	return v1 % v2;
			case '&':	return v1 & v2;
			case '|':	return v1 | v2;
			case '^':	return v1 ^ v2;
			case '<':	return v1 < v2;
			case '>':	return v1 > v2;

			default:
				ATLASSERT(0);
			}
		}
		break;

		default:
			ATLASSERT(0);
	}

	ATLASSERT(0);
	return 0;
}

macromap m_defines;

CDefine* Define(int line_pos, PP_GroupPart* groupPart)
{
	macromap::iterator pDefine2 = m_defines.find(groupPart->DEFINE.id);
	if (pDefine2 != m_defines.end())
	{
		char msg[512];
		sprintf(msg, "Redefinition of macro '%s' : first seen :(%d)",
			groupPart->DEFINE.id, /*(*pDefine2).second->m_location.m_filepath.c_str(),*/ (*pDefine2).second->m_line_pos);

		printf(msg);
	//	pDefine->m_replacementList.clear();

		return NULL;
	}
	else
	{
		CDefine* pDefine;
		pDefine = new CDefine;
		pDefine->m_name = groupPart->DEFINE.id;
		pDefine->m_bFunctionLike = groupPart->DEFINE.bFunctionLike;

	//	pDefine->m_location.m_filepath = m_pFile->m_filepath;
		pDefine->m_line_pos = line_pos;///*m_pFile->*/m_line;
	//	m_defines.push_back(pDefine);
		m_defines.insert(macromap::value_type(pDefine->m_name, pDefine));

		PP_TokenList* token = groupPart->DEFINE.replacementList;
		while (token)
		{
			pDefine->m_replacementList.push_back(token->head);
			token = token->tail;
		}

		//printf("#define %s\n", name);

		return pDefine;
	}
}

void Undef(const char* name)
{
	//printf("#undef %s\n", name);
	m_defines.erase(name);
}

inline bool PP_IsChar(PP_Token& tok, char c)
{
	return (((tok).kind == PP_Token::PP_CHAR) && ((tok).c == (c)));
}

PP_TokenList* ttail = NULL;

class CMacroInvocation
{
public:
	CMacroInvocation(CDefine* pMacro)
	{
		m_pMacro = pMacro;
		m_pPrev = NULL;

		yybufstate = NULL;
	}

	CMacroInvocation* m_pPrev;
	CDefine* m_pMacro;

	std::string m_string;

	int SubstituteArguments(std::vector<std::vector<PP_Token> >& argTokenList);

	int GetArg(const char* name)
	{
		for (int i = 0; i < m_pMacro->m_argNames.size(); i++)
		{
			if (!strcmp(m_pMacro->m_argNames[i].c_str(), name))
			{
				return i;
			}
		}

		return -1;
	}

	yy_buffer_state* yybufstate;
};

CMacroInvocation * m_pMacroInvocation;

// Argument substitution
int CMacroInvocation::SubstituteArguments(std::vector<std::vector<PP_Token> >& argTokenList)
{
#if 0
	m_string = "";//" ";

	//CToken* pprevtok = NULL;

	for (int i = 0; i < m_pMacro->m_replacementList.size(); i++)
	{
		PP_Token* ptok = &m_pMacro->m_replacementList[i];

		PP_Token* pnexttok;
		if (i < m_pMacro->m_replacementList.size()-1)
			pnexttok = &m_pMacro->m_replacementList[i+1];
		else
			pnexttok = NULL;

		if (PP_IsChar(*ptok, '##'))
		{
		//	m_string.erase(m_string.end()-1);
			if (i == 0)
				return -1;
			else if (pnexttok == NULL)
				return -2;

			std::string str;

			int arg = GetArg(pnexttok->id);
			if (arg >= 0)
			{
				if (argTokenList.size() > arg)
				{
					std::vector<PP_Token>& tokenlist = argTokenList[arg];
					for (int j = 0; j < tokenlist.size(); j++)
					{
						PP_Token* ptok = &tokenlist[j];
						str += ptok->toString();
					}
				}
			}
			else
			{
				str = pnexttok->toString();
			}

			//str += pnexttok->toString();

			m_string += str;
			i++;
			continue;
		}

		if (ptok->kind == PP_Token::PP_IDENTIFIER)
		{
			int arg = GetArg(ptok->id);
			if (arg >= 0)
			{
				if (argTokenList.size() > arg)
				{
					std::vector<PP_Token>& tokenlist = argTokenList[arg];
					for (int j = 0; j < tokenlist.size(); j++)
					{
						PP_Token* ptok = &tokenlist[j];
						m_string += ptok->toString();
					}
				}
			}
			else
			{
				m_string += ptok->toString();
			}
		}
		else if (PP_IsChar(*ptok, '#'))
		{
			return 1;
			i++;
		}
		else
		{
			m_string += ptok->toString();
		}

	//	pprevtok = ptok;
	}

#if 0
	if (strstr(m_string.c_str(), "//"))
	{
		printf("");
	}
#endif

	/*
	if (pprevtok)
	{
		m_string += pprevtok->toString();
	}
	*/

	{/*
		for (int i = 0; i < m_tokenList.size(); i++)
		{
			printf("'%s'-", m_tokenList[i].ident);
		}
		printf("\n");
		*/
	}
#endif
	return 0;	// success
}

int PP_ProcessTokens(PP_TokenList*);

#if 0
// Expand macros and Include files
int PP_process2(PP_TokenList* head)
{
	PP_TokenList* p = head;
	while (p)
	{
		BOOL bMacro = FALSE;

		if (p->head.kind == PP_Token::PP_IDENTIFIER)
		{
			macromap::iterator pDefine = m_defines.find(p->head.id);
			if (pDefine != m_defines.end())
			{
				if ((*pDefine).second->m_bFunctionLike)
				{
					if (p->tail && PP_IsChar(p->tail->head, '('))
					{
						p = p->tail->tail;
						bMacro = TRUE;
					}
				}
				else
				{
					bMacro = TRUE;
				}

				if (bMacro)
				{
					std::vector<std::vector<PP_Token> > argTokenList;

					if ((*pDefine).second->m_bFunctionLike)
					{
						int argNamesSize = (*pDefine).second->m_argNames.size();

						/*
						if (argNamesSize == 12)
						{
							printf("");
						}
						*/

						int paren = 1;

						if (p && !PP_IsChar(p->head, ')'))
						{
							while (p)
							{
								ATLASSERT(paren == 1);

								std::vector<PP_Token> tokens;

								while (p)
								{
									if (PP_IsChar(p->head, '('))
									{
										paren++;
									}
									else if (PP_IsChar(p->head, ')'))
									{
										paren--;
										if (paren < 1)
										{
											//GetToken4();
											break;
										}
									}
									else if (PP_IsChar(p->head, ','))
									{
										if (paren == 1)
											break;
									}

									tokens.push_back(p->head);
								//	GetToken4();
									p = p->tail;
								}
								if (PP_IsChar(p->head, ','))
									p = p->tail;//GetToken3();

								argTokenList.push_back(tokens);

								if (argTokenList.size() > argNamesSize+10)	// Break at some sensible overflow
								{
									break;
								}

								if (paren == 0)
									break;
							}
						}

						int argTokenListSize = argTokenList.size();

						const char* mname = (*pDefine).second->m_name.c_str();

						if (argTokenListSize < argNamesSize)
						{
							char msg[512];
							sprintf(msg, "too few parameters in macro invocation of '%s'", mname);
							printf(msg);
						}
						else if (argTokenListSize > argNamesSize)
						{
							char msg[512];
							sprintf(msg, "too many parameters in macro invocation of '%s'", mname);
							printf(msg);
						}

						if (p == NULL || !PP_IsChar(p->head, ')'))
						{
						//	Expect(')');
						//	GetToken3();
							printf("Error");
						}
						else
						{
							p = p->tail;
							continue;
						}
					}

					CMacroInvocation* pMacroInvocation = new CMacroInvocation((*pDefine).second);
					int err = pMacroInvocation->SubstituteArguments(argTokenList);
					if (err != 0)
					{
						if (err == -1)
							printf("## cannot be the first token in a macro");
						else if (err == -2)
							printf("## cannot be the last token in a macro");
						else
							printf("failed to substitute macro arguments");
					}

					pMacroInvocation->m_pPrev = m_pMacroInvocation;
					m_pMacroInvocation = pMacroInvocation;

					pMacroInvocation->yybufstate = pp2__scan_string(pMacroInvocation->m_string.c_str());
				//	pp2__switch_to_buffer(pMacroInvocation->yybufstate);

					PP_TokenList* tl = NULL;
				//	pp_file = NULL;

					int c;
					while (c = pp2_lex())
					{
						PP_Token tok = PP_Identifier(YYLTYPE(), pp_lval.id);

						tl = new PP_TokenList(tok, tl);
					}

				//	pp_parse();

					PP_ProcessTokens(tl);

					m_pMacroInvocation = m_pMacroInvocation->m_pPrev;
				}
			}
		}

		if (!bMacro)
		{
			if (tail)
			{
				tail->tail = new PP_TokenList(p->head, NULL);
				tail = tail->tail;
			}
			else
			{
				tlist = tail = new PP_TokenList(p->head, NULL);
			}
		}

		p = p->tail;
	}

	return 0;
}

int PP_ProcessTokens(PP_TokenList* tokens)
{
//	while (part->kind == PP_GroupPart::PP_TOKENS)
	PP_TokenList* p = tokens;//part->tokenList;
	if (p)
	{
		PP_TokenList* last = p;

		//p->ta
		PP_TokenList* head = Reverse(p);
		
/*
		if (ttail)
		{
			ttail->tail = head;
		}
		else
		{
			tlist = head;
		}

		ttail = last;
*/
		PP_process2(head);
		/*
		while (p)
		{
			tlist = new PP_TokenList(p->head, tlist);
			p = p->tail;
		}
		*/
		
		//tlist = p;
		/*
		if (tlist)
		{
		while (p)
		{
		PP_TokenList* tail = p = p->tail;
		
		  if (p->tail)
		  p->tail->tail = p;
		  
			 p = tail;
			 }
			 tlist = group-
			 }
			 else
			 {
			 }
		*/
	}

	return 0;
}

typedef int (__stdcall * uu)();

void  * __stdcall  memcpy2(void *, const void *, size_t);

int PP_process(PP_Group* group)
{
	while (group)
	{
		PP_GroupPart* part = group->part;
		ATLASSERT(part);

		switch (part->kind)
		{
		case PP_GroupPart::PP_IF_SECTION:
			{
				long v;
				
				if (part->IF_SECTION.ifGroup->kind == PP_IfGroup::PP_IF)
				{
					v = PP_evaluate(part->IF_SECTION.ifGroup->exp);
				}
				else
				{
					ATLASSERT(0);
				}
				
				if (v)
				{
					PP_process(part->IF_SECTION.ifGroup->group);
				}
				else
				{
					PP_ElifGroups* elifGroups = part->IF_SECTION.elifGroups;
					while (elifGroups)
					{
						v = PP_evaluate(elifGroups->head->ELIF.exp);
						
						if (v)
						{
							PP_process(elifGroups->head->ELIF.group);
							break;
						}
						
						elifGroups = elifGroups->tail;
					}
					
					if (!v && part->IF_SECTION.elseGroup)
					{
						PP_process(part->IF_SECTION.elseGroup);
					}
				}
			}
			break;
			
		case PP_GroupPart::PP_DEFINE:
			{
				Define(0, part);
			}
			break;
			
		case PP_GroupPart::PP_UNDEF:
			{
				Undef(part->UNDEF.id);
			}
			break;

		case PP_GroupPart::PP_TOKENS:
			{
				PP_ProcessTokens(part->tokenList);
			}
			break;
			
		default:
			ATLASSERT(0);
		}

		group = group->tail;
	}

	return 0;
}
#endif

#endif

int cpp_compile(const char* filepath, char* fileoutpath, int m_exeType);
int compile_java(const char* filepath, const char* fileoutpath);

int CConfiguration::CompileFile(const char* filepath, char* fileoutpath)
{
	char dir[16];
	char path[256];
	char filename[256];
	char ext[256];
	_splitpath(filepath, dir, path, filename, ext);

	if (stricmp(ext, ".java") == 0)
	{
		_makepath(fileoutpath, dir, path, filename, "class");
	}
	else if (stricmp(ext, ".cpp") == 0)
	{
		char outdir[260];
		_makepath(outdir, dir, path, m_name.c_str(), NULL);
		_mkdir(outdir);

		_makepath(fileoutpath, NULL, outdir, filename, "obj");

		printf("Compiling %s...\n", filename);

		int errors = cpp_compile(filepath, fileoutpath, m_exeType);

		m_errors += errors;
	}
	else if (stricmp(ext, ".c") == 0)
	{
		printf("Currently doesn't support c files, only cpp\n");
	}
	else if (stricmp(ext, ".lib") == 0)
	{
		//// Do nothing
		_makepath(fileoutpath, dir, path, filename, "lib");
	}
	else
	{
		printf("Unrecognized file extension, supported file extensions are:\n");

		printf("java\n");
		printf("cpp\n");
	}

	if (0)
	{
		printf("Couldn't open file %s\n", filepath);
		return -1;
	}

	return 0;
}

///////////////////////////
// Here, based on file extension, we determine which compiler to invoke

//#define offsetof(s,m)   (int)&(((s *)0))

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("You must specify a filename");
		return 0;
	}

	filevectortype files;
	char* outname = NULL;
	BOOL bCompile = FALSE;
	BOOL bLink = FALSE;

	for (int i = 1; i < argc; i++)
	{
		char* p = argv[i];

		if (p[0] == '-')
		{
			p++;
			if (!strcmp(p, "compile"))
			{
				bCompile = TRUE;
			}
			else if (!strcmp(p, "link"))
			{
				bLink = TRUE;
				i++;

				if (i < argc)
				{
					outname = argv[i];
				}
				else
				{
					printf("expected output filename after -link\n");
					return -1;
				}
			}
		}
		else
		{
			files.Add(StringA(p));
//			files.push_back("C:\\mmstudio\\extras\\lxui\\cssunits.cpp");
		}
	}

	if (!bCompile && !bLink)
	{
		printf("(-compile | -link) file1 file2 ...\n");
	}
	else
	{
		if (bCompile)
		{
			Array<CConfiguration*> configs;

			/*
			{
				CConfiguration* p = new CConfiguration;
				p->m_name = "Amiga68k";
				p->m_exeType = 1;
				p->m_outputFileName = "test.exe";
				configs.push_back(p);
			}
			*/

			{
				CConfiguration* p = new CConfiguration;
				p->m_name = "Win32";
				p->m_exeType = 2;
				p->m_outputFileName = "test.exe";
				configs.Add(p);
			}

			/*
			{
				CConfiguration* p = new CConfiguration;
				p->m_name = "OSX";
				p->m_exeType = 3;
				p->m_outputFileName = "test2";
				configs.push_back(p);
			}
			*/

			for (int i = 0; i < configs.GetSize(); i++)
			{
				CConfiguration* config = configs[i];

				printf("------------ Configuration: %s ------------\n", config->m_name.c_str());

				for (int i = 0; i < files.size(); i++)
				{
					char fileoutpath[512];
					config->CompileFile(files[i].c_str(), fileoutpath);

					config->objectfiles.Add(StringA(fileoutpath));
				}

				if (false && bLink)
				{
					if (outname)
					{
						char outdir[260];
						_makepath(outdir, NULL, "C:\\testdev\\", config->m_name.c_str(), NULL);
						config->m_outputPathName = outdir;

						char exepathname[260];
						_makepath(exepathname, NULL, outdir, config->m_outputFileName.c_str(), NULL);

						FILE* fileout = fopen(exepathname, "wb");
						if (fileout)
						{
							config->Link(fileout);
							fclose(fileout);
						}
					}
					else
					{
						printf("linking requires you to specify an output filename with -o");
					}
				}

				printf("%s - ", config->m_outputFileName.c_str());
				printf("%d error(s), %d warning(s)\n", config->m_errors, config->m_warnings);
			}
		}
	}

	return 0;
}
