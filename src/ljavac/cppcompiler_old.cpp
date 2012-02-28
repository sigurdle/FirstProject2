#include "stdafx.h"
#include "cppcompiler.h"

//using namespace cpp;

/////////////////////////////////////////////////////
/// CPP tokens

#define kwfSimpleTypeSpecifier	1
#define kwfStorageClassSpecifier	2
#define kwfFunctionSpecifier		4
#define kwAccessSpecifier			8

#if 0
static Keyword Keywords[] =
{
	"void",					KW_VOID, kwfSimpleTypeSpecifier,
	"char",					KW_CHAR, kwfSimpleTypeSpecifier,
	"wchar_t",				KW_WCHAR_T, kwfSimpleTypeSpecifier,
	"bool",					KW_BOOL, kwfSimpleTypeSpecifier,
	"int",					KW_INT, kwfSimpleTypeSpecifier,
	"short",					KW_SHORT, kwfSimpleTypeSpecifier,
	"long",					KW_LONG, kwfSimpleTypeSpecifier,
	"signed",				KW_SIGNED, kwfSimpleTypeSpecifier,
	"unsigned",				KW_UNSIGNED, kwfSimpleTypeSpecifier,
	"float",					KW_FLOAT, kwfSimpleTypeSpecifier,
	"double",				KW_DOUBLE, kwfSimpleTypeSpecifier,
	"__int64",				KW___INT64, kwfSimpleTypeSpecifier,
	"return",				KW_RETURN, 0,
	"if",						KW_IF, 0,
	"else",					KW_ELSE, 0,
	"class",					KW_CLASS, 0,
	"struct",				KW_STRUCT, 0,
	"union",					KW_UNION, 0,
	"enum",					KW_ENUM, 0,
	"auto",					KW_AUTO, kwfStorageClassSpecifier,
	"register",				KW_REGISTER, kwfStorageClassSpecifier,
	"static",				KW_STATIC, kwfStorageClassSpecifier,
	"extern",				KW_EXTERN, kwfStorageClassSpecifier,
	"mutable",				KW_MUTABLE, kwfStorageClassSpecifier,
	"inline",				KW_INLINE, kwfFunctionSpecifier,
	"virtual",				KW_VIRTUAL, kwfFunctionSpecifier,
	"explicit",				KW_EXPLICIT, kwfFunctionSpecifier,
	"sizeof",				KW_SIZEOF, 0,
	"const",					KW_CONST, 0,
	"volatile",				KW_VOLATILE, 0,
	"dynamic_cast",		KW_DYNAMIC_CAST, 0,
	"static_cast",			KW_STATIC_CAST, 0,
	"reinterpret_cast",	KW_REINTERPRET_CAST, 0,
	"const_cast",			KW_CONST_CAST, 0,
	"typedef",				KW_TYPEDEF, 0,
	"asm",					KW_ASM, 0,
	"__asm",					KW___ASM, 0,
	"namespace",			KW_NAMESPACE, 0,
	"using",					KW_USING, 0,
	"try",					KW_TRY, 0,
	"export",				KW_EXPORT, 0,
	"template",				KW_TEMPLATE, 0,
	"operator",				KW_OPERATOR, 0,
	"friend",				KW_FRIEND, 0,
	"while",					KW_WHILE, 0,
	"do",						KW_DO, 0,
	"switch",				KW_SWITCH, 0,
	"case",					KW_CASE, 0,
	"default",				KW_DEFAULT, 0,
	"break",					KW_BREAK, 0,
	"continue",				KW_CONTINUE, 0,
	"goto",					KW_GOTO, 0,
	"private",				KW_PRIVATE, kwAccessSpecifier,
	"protected",			KW_PROTECTED, kwAccessSpecifier,
	"public",				KW_PUBLIC, kwAccessSpecifier,
	"for",					KW_FOR, 0,
	"this",					KW_THIS, 0,
	"typename",				KW_TYPENAME, 0,
	"new",					KW_NEW, 0,
	"delete",				KW_DELETE, 0,
	"true",					KW_TRUE, 0,
	"false",					KW_FALSE, 0,
	"__cdecl",				KW___CDECL, 0,
//	"__stdcall",			KW___STDCALL, 0,
	"__declspec",			KW___DECLSPEC, kwfStorageClassSpecifier,
};

int nkeywords = sizeof(Keywords) / sizeof(Keyword);

typedef std::map<std::string, Keyword*> keywordmap;

class CKeywords
{
public:

	CKeywords()
	{
		for (int i = 0; i < nkeywords; i++)
		{
			m_map.insert(keywordmap::value_type(Keywords[i].name, &Keywords[i]));
		}
	}

	keywordmap m_map;
};

CKeywords keywords;

static Keyword* IsKeyword(const char* name)
{
	keywordmap::iterator i = keywords.m_map.find(name);
	if (i != keywords.m_map.end())
		return (*i).second;
	else
		return NULL;

#if 0
	int i = 0;
	while (Keywords[i].name)
	{
		if (!strcmp(name, Keywords[i].name))
		{
			return &Keywords[i];
		}
		i++;
	}
#endif
	return NULL;
}

#define NTOKENS	100

static CToken tokens[NTOKENS];

static CToken* curtok = tokens;
static int ntoken = 0;
#endif

#if 0
static int savestack[100];
static int nsave = 0;


static void save()
{
	if (nsave > 100)
	{
		pPP->jfatalerror("INTERNAL ERROR: stack overflow\n");
	}
	savestack[nsave] = ntoken;
	nsave++;
}

static void restore()
{
	nsave--;
	int count = ntoken - savestack[nsave];
	ntoken -= count;
	curtok -= count;
	if (curtok < tokens)
		curtok += 9;
}
#endif

#if 0
static CToken* GetToken();

CToken* CCPPCompiler::GetCharacter(int delimiter, BOOL bWide, CToken& token)
{
	int line = pPP->m_pFile->m_line;

	DWORD int32 = 0;
	int c2;
	while (!pPP->_eof())
	{
		c2 = pPP->_getc();

		if (c2 == '\\')
		{
			int c3 = pPP->_getc();
			if (c3 == '\\')
			{
				c2 = '\\';
			}
			else if (c3 == 'n')
			{
				c2 = '\n';
			}
			else if (c3 == 'r')
			{
				c2 = '\r';
			}
			else if (c3 == 't')
			{
				c2 = '\t';
			}
			else if (c3 == '?')
			{
				c2 = '\?';
			}
			else if (c3 == '\'')
			{
				c2 = '\'';
			}
			else if (c3 == '0')
			{
				c2 = '\0';
			}
			else
			{
				pPP->jerror("Unrecocnized character sequence");
			}
		}
		else if (c2 == delimiter)
		{
		//	ungetc(c2, fpin);
			break;
		}

		int32 <<= 8;
		int32 |= c2;
	}

	if (c2 != delimiter)
	{
		char msg[256];
		sprintf(msg, "expected end of character constant, started on line(%d)", line);
		pPP->jerror(msg);
	}

	token.type = CToken::tok_integer;
	token.int32 = int32;

	*curtok = token;

	return curtok;
}

CToken* CCPPCompiler::GetString(int delimiter, BOOL bWide, CToken& token)
{
	int line = pPP->m_pFile->m_line;

	std::string str;

	int c2;
	while (!pPP->_eof())
	{
		//PP::CToken* ptok = pPP->GetToken4();
		c2 = pPP->_getc();

		if (c2 == '\\')
		{
			int c3 = pPP->_getc();
			if (c3 == '\\')
			{
				c2 = '\\';
			}
			else if (c3 == 'n')
			{
				c2 = '\n';
			}
			else if (c3 == 'r')
			{
				c2 = '\r';
			}
			else if (c3 == 't')
			{
				c2 = '\t';
			}
			else if (c3 == '?')
			{
				c2 = '\?';
			}
			else if (c3 == '\'')
			{
				c2 = '\'';
			}
			else if (c3 == '0')
			{
				c2 = '\0';
			}
			else
			{
				pPP->jerror("Unrecocnized string sequence");
			}
		}
		else if (c2 == delimiter)
		{
		//	ungetc(c2, fpin);
			break;
		}
		str += c2;
	}

	if (c2 != delimiter)
	{
		char msg[256];
		sprintf(msg, "expected end of string, started on line(%d)", line);
		pPP->jerror(msg);
	}

	if (bWide)
	{
		token.type = CToken::tok_wstring;
	}
	else
	{
		token.type = CToken::tok_string;
	}

	token.stringlen = str.length();
	token.string = strdup(str.c_str());

	*curtok = token;

	return curtok;
}

CToken* CCPPCompiler::ConvertToken(PP::CToken* tokpp)
{
	CToken token;

	if (tokpp->type == PP::CToken::tok_ident)
	{
		if (tokpp->identlen == 1 && tokpp->ident[0] == 'L')
		{
			int c2 = pPP->_getc();
			if (c2 == '"')
			{
				return GetString(c2, TRUE, token);
			}
			else if (c2 == '\'')
			{
				return GetCharacter(c2, TRUE, token);
			}
			else
			{
				pPP->_ungetc(c2);
			}
		}

		Keyword* pkw;
		if (pkw = IsKeyword(tokpp->ident))
		{
			token.type = CToken::tok_keyword;
			token.pkw = pkw;
		}
		else
		{
			token.type = CToken::tok_ident;
			token.identlen = tokpp->identlen;
			token.ident = strdup(tokpp->ident);
		}
	}
	else if (tokpp->type == PP::CToken::tok_integer)
	{
		token.type = CToken::tok_integer;
		token.int32 = tokpp->int32;
	}
	else if (tokpp->type == PP::CToken::tok_double)
	{
		token.type = CToken::tok_double;
		token.double64 = tokpp->double64;
	}
	else if (tokpp->type == PP::CToken::tok_string)
	{
		token.type = CToken::tok_string;
		token.stringlen = tokpp->stringlen;
		token.string = strdup(tokpp->string);
	}
	else if (tokpp->type == PP::CToken::tok_symbol)
	{
		token.type = CToken::tok_symbol;
		token.symbol = tokpp->symbol;
	}
	else if (tokpp->type == PP::CToken::tok_char)
	{
		int c = tokpp->symbol;

		int line = pPP->m_pFile->m_line;

		/*
		bool bWide = false;
		if (c == 'L')
		{
			int c2 = pPP->_getc();
			if (c2 == '"' || c2 == '\'')
			{
				c = c2;
				bWide = true;
			}
			else
			{
				pPP->_ungetc(c2);
			}
		}
		*/

		if (c == '\'')
		{
			return GetCharacter(c, FALSE, token);
		}
		else if (c == '\"')
		{
			return GetString(c, FALSE, token);
		}
		else if (c == '{' ||
					c == '}' ||
					c == '(' ||
					c == ')' ||
					c == '[' ||
					c == ']' ||

					c == '^' ||
					c == '~' ||
					c == ',' ||
					c == ';' ||

					c == '?' ||

					c == '*' ||
					c == '/' ||
					c == '%')
		{
			token.type = CToken::tok_symbol;
			token.symbol = c;
		}
		else if (c == '.')
		{
			int c2 = pPP->m_pFile->_getc();
			if (c2 == '*')
			{
				token.type = CToken::tok_symbol;
				token.symbol = '.*';
			}
			else if (c2 == '.')
			{
				int c3 = pPP->m_pFile->_getc();
				if (c3 == '.')
				{
					token.type = CToken::tok_symbol;
					token.symbol = '...';
				}
				else
				{
					pPP->jerror("'..' is not a valid token");
				}
			}
			else
			{
				pPP->m_pFile->_ungetc(c2);
				token.type = CToken::tok_symbol;
				token.symbol = c;
			}
		}
		else if (c == '!')
		{
			int c2 = pPP->m_pFile->_getc();
			if (c2 == '=')	// !=
			{
				token.type = CToken::tok_symbol;
				token.symbol = (c<<8) | c2;
			}
			else
			{
				pPP->m_pFile->_ungetc(c2);
				token.type = CToken::tok_symbol;
				token.symbol = c;
			}
		}
		else if (c == '+' ||
					c == '-' ||
					c == '=' ||
					c == '&' ||
					c == '|' ||
					c == ':')
		{
			int c2 = pPP->_getc();

			if (c == '-' && c2 == '>')	// ->
			{
				int c3 = pPP->_getc();
				if (c3 == '*')
				{
					token.type = CToken::tok_symbol;
					token.symbol = '->*';
				}
				else
				{
					pPP->_ungetc(c3);

					token.type = CToken::tok_symbol;
					token.symbol = (c<<8) | c2;
				}
			}
			else if (c2 == c)	// ++ , -- , ==, &&, ||, ::
			{
				if (c2 == ':')
				{
					printf("");
				}
				token.type = CToken::tok_symbol;
				token.symbol = (c<<8) | c2;
			}
			else
			{
				pPP->_ungetc(c2);
				token.type = CToken::tok_symbol;
				token.symbol = c;
			}
		}
	}
	else
	{
		ASSERT(0);
	}

	*curtok = token;

	return curtok;
}
#endif

namespace cpp
{
#include "cpp_parse.tab.h"
}

#if 0
PP_GroupPart* PP_IfSection(PP_IfGroup* ifGroup, PP_ElifGroups* elifGroups, PP_Group* elseGroup)
{
	PP_GroupPart* p = new PP_GroupPart;
	p->kind = PP_GroupPart::PP_IF_SECTION;
	p->IF_SECTION.ifGroup = ifGroup;
	p->IF_SECTION.elifGroups = elifGroups;
	p->IF_SECTION.elseGroup = elseGroup;

	return p;
}

PP_GroupPart* PP_Define(const char* id, bool bFunctionLike, PP_IdentifierList* argList, PP_TokenList* replacementList)
{
	PP_GroupPart* p = new PP_GroupPart;
	p->kind = PP_GroupPart::PP_DEFINE;
	p->DEFINE.argList = argList;
	p->DEFINE.id = strdup(id);
	p->DEFINE.replacementList = replacementList;
	p->DEFINE.bFunctionLike = bFunctionLike;

	return p;
}

PP_GroupPart* PP_Undef(const char* id)
{
	PP_GroupPart* p = new PP_GroupPart;
	p->kind = PP_GroupPart::PP_UNDEF;
	p->UNDEF.id = strdup(id);

	return p;
}

PP_IfGroup* PP_If_Group(A_Exp* exp, PP_Group* group)
{
	PP_IfGroup* p = new PP_IfGroup;
	p->kind = PP_IfGroup::PP_IF;
	p->exp = exp;
	p->group = group;
	return p;
}

PP_IfGroup* PP_IfDefGroup(const char* id, PP_Group* group)
{
	PP_IfGroup* p = new PP_IfGroup;
	p->kind = PP_IfGroup::PP_IFDEF;
	p->id = strdup(id);
	p->group = group;
	return p;
}

PP_IfGroup* PP_IfNDefGroup(const char* id, PP_Group* group)
{
	PP_IfGroup* p = new PP_IfGroup;
	p->kind = PP_IfGroup::PP_IFNDEF;
	p->id = strdup(id);
	p->group = group;
	return p;
}

PP_Directive* PP_ElifGroup(A_Exp* exp, PP_Group* group)
{
	ASSERT(0);
	return NULL;
}

PP_Directive* PP_Elif(A_Exp* exp, PP_Group* group)
{
	PP_Directive* p = new PP_Directive;
	p->kind = PP_Directive::PP_ELIF;
	p->ELIF.exp = exp;
	p->ELIF.group = group;
	return p;
}

PP_GroupPart* PP_Tokens(PP_TokenList* tokens)
{
	PP_GroupPart* p = new PP_GroupPart;

	p->kind = PP_GroupPart::PP_TOKENS;
	p->tokenList = tokens;

	return p;
}

PP_Token PP_Char(YYLTYPE& pos, char c)
{
	PP_Token token;
	token.kind = PP_Token::PP_CHAR;
	token.c = c;
	token.line_pos = pos.first_line;
	return token;
}

PP_Token PP_Int32(YYLTYPE& pos, long int32)
{
	PP_Token token;
	token.kind = PP_Token::PP_INT32;
	token.int32 = int32;
	token.line_pos = pos.first_line;
	return token;
}

PP_Token PP_Identifier(YYLTYPE& pos, const char* id)
{
	PP_Token token;
	token.kind = PP_Token::PP_IDENTIFIER;
	token.id = strdup(id);
	token.line_pos = pos.first_line;
	return token;
}

#endif


#if 0
CExpression* A_Binop(int op, CExpression* left, CExpression* right)
{
	ASSERT(left != NULL);
	ASSERT(right != NULL);

	CExpression* p = new CExpression;
	p->tok.type = CToken::tok_symbol;
	p->tok.symbol = op;
	p->left = left;
	p->right = right;

	return p;
}

CExpression* A_Unop(int op, CExpression* right)
{
	CExpression* p = new CExpression;
	p->tok.type = CToken::tok_symbol;
	p->tok.symbol = op|('U'<<8);
	p->right = right;
	p->left = NULL;

	return p;
}

CExpression* A_Const(int int32)
{
	CExpression* p = new CExpression;
	p->tok.type = CToken::tok_integer;
	p->tok.int32 = int32;
	p->left = NULL;
	p->right = NULL;

	return p;
}

CExpressionStatement* A_Expr(CExpression* expr)
{
	ASSERT(expr != NULL);

	CExpressionStatement* p = new CExpressionStatement;
	p->m_pExpr = expr;

	return p;
}

CExpression* A_Ident(const char* ident)
{
	CExpression* p = new CExpression;
	p->tok.type = CToken::tok_ident;
	p->tok.ident = strdup(ident);
	return p;
}
#endif
#if 0
void CCPPCompiler::Restore(int n)
{
	while (m_tokStack2.size() >= n)
	{
		CToken tok = m_tokStack2.top();
		m_tokStack.push(tok);
		m_tokStack2.pop();
	}
	GetToken();
}

/*
void CCPPCompiler::Restore(CSave* gSave2)
{
	while (!gSave2->m_tokStack.empty())
	{
		m_tokStack.push(gSave->m_tokStack.top());
		gSave->m_tokStack.pop();
	}
	gSave = NULL;
	GetToken();
}
*/

CToken* CCPPCompiler::GetToken()
{
	if (!m_tokStack.empty())
	{
		*curtok = m_tokStack.top();
		m_tokStack.pop();

		m_tokStack2.push(*curtok);

		/*
		if (gSave)
		{
			gSave->m_tokStack.push(*curtok);
		}
		*/

		return curtok;
	}

	pPP->GetToken();
	while (pPP->curtokpp->type == PP::CToken::tok_space ||
		(pPP->curtokpp->type == PP::CToken::tok_symbol && pPP->curtokpp->symbol == '\n'))
	{
		pPP->GetToken();
	}

	CToken* p = ConvertToken(pPP->curtokpp);

	m_tokStack2.push(*p);
	/*
	if (gSave)
	{
		gSave->m_tokStack.push(*p);
	}
*/

	return p;
}



/*
static void UngetToken()
{
	curtok--;
	if (curtok < tokens)
	{
		curtok = tokens+NTOKENS-1;
	}

	//	jfatalerror("INTERNAL ERROR: (Token overflow)\n");
	//}
}
*/

void CCPPCompiler::EatSymbol(int c)
{
	if (curtok->type != CToken::tok_symbol || curtok->symbol != c)
	{
		if (curtok->type == CToken::tok_keyword)
		{
			char msg[128];
			sprintf(msg, "'%s' expected character: '%c'", curtok->pkw->name, c);
			pPP->jerror(msg);
		}
		else if (curtok->type == CToken::tok_ident)
		{
			char msg[128];
			sprintf(msg, "'%s' expected character: '%c'", curtok->ident, c);
			pPP->jerror(msg);
		}
		else if (curtok->type == CToken::tok_symbol)
		{
			if (curtok->symbol > 255)
			{
				char msg[128];
				sprintf(msg, "'%2.2s' expected character: '%c'", (char*)&curtok->symbol, c);
				pPP->jerror(msg);
			}
			else
			{
				if (curtok->symbol == ',')
				{
					printf("");
				}
				char msg[128];
				sprintf(msg, "'%c' expected character: '%c'", (char)curtok->symbol, c);
				pPP->jerror(msg);
			}
		}
		else
		{
			char msg[128];
			sprintf(msg, "expected character: '%c'", c);
			pPP->jerror(msg);
		}
	}
	GetToken();
}
#endif

///////////////////////////////////////////////////////
// Forward declarations

#if 0
enum
{
	LINKAGE_EXTERN_C,
	LINKAGE_EXTERN_CPP,
};

Type* TypeSpecifiers::GetType(CCPPCompiler* pCompiler)
{
	if (m_pType)
	{
		ASSERT(m_typeKW == -1);
		ASSERT(m_size == 0);
		ASSERT(m_sign == 0);

		Type* pType = new Type(type_cv);
		pType->m_pPointerTo = m_pType;
		pType->m_bConst = m_bConst;
		pType->m_bVolatile = m_bVolatile;

		return pType;
	}
	else
	{
		if (m_typeKW == -1 && (m_size != 0 || m_sign != 0))	// If only size or sign is specified, default to int of that size or sign
		{
			m_typeKW = KW_INT;
		//	if (m_size == 0)	// if size isn't specified, default to long (1=short,2=long)
		//		m_size = 2;	// long
		}

		if (m_typeKW != -1)
		{
			Type* pType = new Type;

			pType->m_bConst = m_bConst;
			pType->m_bVolatile = m_bVolatile;

			switch (m_typeKW)
			{
			case KW_VOID:
				{
					if (m_size)
						pCompiler->pPP->jerror("short/long cannot be specified on void type");
					pType->m_type = type_void;
					pType->m_sizeof = -1;
				}
				break;

			case KW_BOOL:
				{
					if (m_size)
						pCompiler->pPP->jerror("short/long cannot be specified on bool type");
					pType->m_type = type_bool;
					pType->m_sizeof = 1;
				}
				break;

				case KW_CHAR:
				{
					if (m_size)
						pCompiler->pPP->jerror("short/long cannot be specified on char type");

					if (m_sign == 1)
						pType->m_type = type_signed_char;
					else if (m_sign == -1)
						pType->m_type = type_unsigned_char;
					else
						pType->m_type = type_char;

					pType->m_sizeof = 1;
				}
				break;

				case KW_WCHAR_T:
				{
					if (m_size)
						pCompiler->pPP->jerror("short/long cannot be specified on wchar_t type");
					pType->m_type = type_wchar;
					pType->m_sizeof = 2;
				}
				break;

				case KW_INT:
					{
						if (m_size == 1)
						{
							if (m_sign == -1)
								pType->m_type = type_unsigned_short_int;
							else
								pType->m_type = type_short_int;

							pType->m_sizeof = 2;
						}
						else if (m_size == 2)
						{
							if (m_sign == -1)
								pType->m_type = type_unsigned_long_int;
							else
								pType->m_type = type_long_int;

							pType->m_sizeof = 4;
						}
						else if (m_size == 3)
						{
							if (m_sign == -1)
								pType->m_type = type_unsigned_long_long;
							else
								pType->m_type = type_long_long;

							pType->m_sizeof = 8;
						}
						else
						{
							if (m_sign == -1)
								pType->m_type = type_unsigned_int;
							else
								pType->m_type = type_int;

							pType->m_sizeof = 4;
						}
					}
					break;

				case KW___INT64:
					{
						if (m_size)
							pCompiler->pPP->jerror("short/long cannot be specified on wchar_t type");

						if (m_sign == -1)
							pType->m_type = type_unsigned_long_long;
						else
							pType->m_type = type_long_long;

						pType->m_sizeof = 8;
					}
					break;

				case KW_FLOAT:
					{
						if (m_size)
							pCompiler->pPP->jerror("short/long cannot be specified on float type");
						pType->m_type = type_float;
						pType->m_sizeof = 4;
					}
					break;

				case KW_DOUBLE:
					{
						if (m_size == 1)
							pCompiler->pPP->jerror("short cannot be specified on double type");

						pType->m_type = type_double;
						// long specifier is currently just ignored
						pType->m_sizeof = 8;
					}
					break;

				default:
					ASSERT(0);
			}

			ASSERT(pType->m_type != -1);
			ASSERT(pType->m_sizeof != 0);
			return pType;
		}
		else
		{
			return NULL;
		}
	}
}
#endif


#if 0
CScope* CCPPCompiler::GetNestedScope(CScope* pScope, CExpression* pExpr)
{
	if (pExpr == NULL)
	{
		return pGlobal->m_pNamespace->m_pScope;
	}
	else if (pExpr->tok.type == CToken::tok_symbol && pExpr->tok.symbol == '::')
	{
		CScope* pScope2 = GetNestedScope(pScope, pExpr->left);
		if (pScope2 == NULL)
		{
			return NULL;
		}

		return GetNestedScope(pScope2, pExpr->right);
	}
	else if (pExpr->tok.type == CToken::tok_ident)
	{
		CScope* pScope2 = pScope->GetScope(pExpr->tok.ident);
		if (pScope2)
		{
			return pScope2;
		}

		char msg[512];
		sprintf(msg, "'%s' : type not found", pExpr->tok.ident);
		pPP->jerror(msg);

		return NULL;
	}
	return NULL;
}

CScope* CCPPCompiler::GetScope(CScope* pScope, CExpression* pExpr)
{
	ASSERT(0);
	return NULL;
#if 0
	if (pExpr == NULL)
	{
		return pScope;
	}
	else if (pExpr->tok.type == CToken::tok_symbol && pExpr->tok.symbol == '::')
	{
		CScope* pScope2 = GetScope(pScope, pExpr->left);
		if (pScope2 == NULL)
		{
			return NULL;
		}

		return GetScope(pScope2, pExpr->right);
	}
	else if (pExpr->tok.type == CToken::tok_ident)
	{
	//	printf("%s:", pExpr->tok.ident);

		namespacemap::iterator nsi = pScope->m_namespaces.find(pExpr->tok.ident);
		if (nsi != pScope->m_namespaces.end())
		{
			return (*nsi).second->m_pScope;
		}

		typemap::iterator typei = pScope->m_types.find(pExpr->tok.ident);
		if (typei != pScope->m_types.end())
		{
			if ((*typei).second->m_pClass)
			{
				return (*typei).second->m_pClass->m_pScope;
			}
		}

		templatemap::iterator templatei = pScope->m_templates.find(pExpr->tok.ident);
		if (templatei != pScope->m_templates.end())
		{
		//	if ((*templatei).second->m_pClass)
			{
				printf("");
//				return (*templatei).second->m_pClass->m_pScope;
			}
		}

		char msg[512];
		sprintf(msg, "'%s' : type not found", pExpr->tok.ident);
		pPP->jerror(msg);
		return NULL;
	}

	return NULL;
#endif
}

// virtual
void CCPPCompiler::OnPragma()
{
	if (pPP->curtokpp->type == CToken::tok_ident && (
			!strcmp(pPP->curtokpp->ident, "libcall") ||
			!strcmp(pPP->curtokpp->ident, "tagcall"))
		)
	{
		int tagcall = !strcmp(pPP->curtokpp->ident, "tagcall");

		pPP->GetToken3();

		if (pPP->curtokpp->type == PP::CToken::tok_ident)
		{
			std::string basename = pPP->curtokpp->ident;

			pPP->GetToken3();
			if (pPP->curtokpp->type == PP::CToken::tok_ident)
			{
				CDeclaratorReference* pDeclaratorRef = pGlobal->m_pNamespace->m_pScope->GetDeclarator(pPP->curtokpp->ident);
				if (pDeclaratorRef == NULL)
				{
					char msg[512];
					sprintf(msg, "'%s' : undeclared name", pPP->curtokpp->ident);
					pPP->jwarn(msg);
				}
				else if (pDeclaratorRef->m_pDeclarator->m_pType->m_type != type_function)
				{
					char msg[512];
					sprintf(msg, "'%s' : previously declared as not a function", pPP->curtokpp->ident);
					pPP->jerror(msg);
				}
				else
				{
					while (!pPP->_eof())
					{
						int c = pPP->_getc();
						if (c == '\n' || c != ' ')
						{
							pPP->_ungetc(c);
							break;
						}
					}

					int int32 = 0;

					while (!pPP->_eof())
					{
						int c = pPP->_getc();
						if (!((c >= '0' && c <= '9') ||
							(c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
						{
							pPP->_ungetc(c);
							break;
						}

						int32 *= 16;

						if (c <= '9')
						{
							int32 += c - '0';
						}
						else if (c <= 'F')
						{
							int32 += 10 + c - 'A';
						}
						else
						{
							int32 += 10 + c - 'a';
						}
					}

					while (!pPP->_eof())
					{
						int c = pPP->_getc();
						if (c == '\n' || c != ' ')
						{
							pPP->_ungetc(c);
							break;
						}
					}

					char buf[32];
					int len = 0;

					while (!pPP->_eof())
					{
						int c = pPP->_getc();

						if (!((c >= '0' && c <= '9') ||
							(c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
						{
							pPP->_ungetc(c);
							break;
						}
						buf[len] = c;
						len++;
					}

					int nparams = buf[len-1]-'0';
					int nparams2 = pDeclaratorRef->m_pDeclarator->m_pType->m_pFunction->m_parameters.size();

					if (nparams != nparams2)
					{
						char msg[256];
						sprintf(msg, "#pragma %s %s doesn't match number of parameters previously declared", tagcall? "tagcall": "libcall", pDeclaratorRef->m_pDeclarator->m_name.c_str());
						pPP->jwarn(msg);
					}
					else
					{
						pDeclaratorRef->m_pDeclarator->m_pType->m_pFunction->m_libcall.m_tagcall = tagcall;
						pDeclaratorRef->m_pDeclarator->m_pType->m_pFunction->m_libcall.m_basename = basename;
						pDeclaratorRef->m_pDeclarator->m_pType->m_pFunction->m_libcall.m_offset = -int32;

						for (int i = pDeclaratorRef->m_pDeclarator->m_pType->m_pFunction->m_parameters.size()-1; i >= 0; i--)
						{
							int n = pDeclaratorRef->m_pDeclarator->m_pType->m_pFunction->m_parameters.size()-i-1;
							int reg;

							int c = buf[n];

							if (c <= '9')
								reg = c-'0';
							else if (reg <= 'F')
								reg = 10 + c - 'A';
							else
								reg = 10 + c - 'a';

							pDeclaratorRef->m_pDeclarator->m_pType->GetType()->m_pFunction->m_parameters[i]->m_libcall.m_reg = reg;
						}
					}
				}
			}
			else
			{
				pPP->jerror("Expected functionname");
			}
		}
		else
		{
			pPP->jerror("Expected basename");
		}
	}
}
#endif

///////////////////////////////////////////////////////
// Expressions

/*
operator-function-id:
	operator operator
	operator operator < template-argument-listopt >

operator: one of
	new delete new[] delete[]
	+ - * / % ˆ & | ˜
	! = < > += -= *= /= %=
	ˆ= &= |= << >> >>= <<= == !=
	<= >= && || ++ -- , ->* ->
	() []
*/

/*
template-id:
	template-name < template-argument-listopt >
template-name:
	identifier
*/

/*
qualified-id:
	::opt nested-name-specifier templateopt unqualified-id
	:: identifier
	:: operator-function-id
	:: template-id
*/

/*
unqualified-id:
	identifier
	operator-function-id
		operator operator
		operator operator < template-argument-listopt >
	conversion-function-id
		operator conversion-type-id
	˜ class-name
	template-id
*/
#if 0
BOOL unqualified_id(CDeclarator* pDeclarator, CScope* pScope)
{
	if (curtok->type == CToken::tok_ident)	// identifier or template-name
	{
		pDeclarator->m_name = curtok->ident;
		GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '<')
		{
			ASSERT(0);
			GetToken();

			//while (!pPP->_eof())
			{
				Type* pType = type_specifier_seq(NULL, pScope);
			}

			EatSymbol('>');
		}

		return TRUE;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_OPERATOR)
	{
		GetToken();

		if (curtok->type == CToken::tok_symbol)
		{
			switch (curtok->symbol)
			{
	#if 0
			case '+':	// unary
				pDeclarator->m_name = "ps";
				break;

			case '-':	// unary
				pDeclarator->m_name = "ng";
				break;

			case '&':	// unary
				pDeclarator->m_name = "ad";
				break;

			case '*':	// unary
				pDeclarator->m_name = "de";
				break;
	#endif

			case '~':
				pDeclarator->m_name = "co";
				break;

			case '+':
				pDeclarator->m_name = "pl";
				break;

			case '-':
				pDeclarator->m_name = "mi";
				break;

			case '*':
				pDeclarator->m_name = "ml";
				break;

			case '/':
				pDeclarator->m_name = "dv";
				break;

			case '%':
				pDeclarator->m_name = "rm";
				break;

			case '==':
				pDeclarator->m_name = "eq";
				break;

			case '!=':
				pDeclarator->m_name = "ne";
				break;

			default:
				ASSERT(0);
			}
		}
		else if (curtok->type == CToken::tok_keyword)
		{
			if (curtok->pkw->n == KW_NEW || curtok->pkw->n == KW_DELETE)
			{
				printf("");
			}
			else
			{
				pPP->jerror("unrecognized operator");
			}
		}
		else
		{
			pPP->jerror("expected an operator after 'operator' keyword");
		}

		GetToken();
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '~')
	{
		GetToken();
		pPP->jfatalerror("can be a class destructor: not yet supported");
	}

	return FALSE;
}
#endif

#if 0
CExpression* CCPPCompiler::unqualified_id(CScope* pScope)
{
	if (curtok->type == CToken::tok_ident)	// identifier or template-name
	{
		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;

#if 0
		CIDExpression idexpr;
		idexpr.m_location.m_filepath = pPP->m_pFile->m_filepath;
		idexpr.m_location.m_line = pPP->m_pFile->m_line;
		idexpr.m_pExpr = pExpr;
		pScope->m_pIDExprs->m_v.push_back(idexpr);
#endif

		GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '<')
		{
			Type* pTemplateType = pScope->GetType(pExpr->tok.ident);
			if (pTemplateType && pTemplateType->GetType()->m_type == type_class)
			{
				CTemplate* pTemplate = pTemplateType->GetType()->m_pClass->m_pTemplate;//Scope->GetTemplate(pExpr->tok.ident);
				if (pTemplate)//templatei != pGlobal->m_templates.end())
				{
					GetToken();

				//	CTemplate* pTemplate = (*templatei).second;

					while (!pPP->_eof())
					{
						if (curtok->type == CToken::tok_symbol && curtok->symbol == '>')
						{
							break;
						}
						GetToken();
					}

					/*
					{
						Type* pType = type_specifier_seq(NULL, pScope);

					}
					*/
					EatSymbol('>');
				}
			}
		}

		return pExpr;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_OPERATOR)
	{
		CExpression* pExpr = new CExpression;

		GetToken();

		if (curtok->type == CToken::tok_symbol)
		{
			pExpr->tok = *curtok;

			switch (curtok->symbol)
			{
			case '[':
				{
					GetToken();
					EatSymbol(']');
				}
				break;

			case '(':
				{
					GetToken();
					EatSymbol(')');
				}
				break;

			default:
				GetToken();
			}
		}
		else if (curtok->type == CToken::tok_keyword &&
			(curtok->pkw->n == KW_NEW || curtok->pkw->n == KW_DELETE))
		{
			pExpr->tok = *curtok;
			GetToken();
		}
		else
		{
			pExpr->tok = *curtok;

		//	Type* pType = type_specifier_seq(NULL/*pInnermostClass*/, pScope);
			Type* pType = type_id(NULL/*pInnermostClass*/, pScope);
			if (pType == NULL)
			{
				pPP->jerror("unrecognized operator");
				GetToken();

			//	pExpr->tok.ident = strdup(pType->toString());
			}
			else
			{
				ASSERT(0);
#if 0
				pExpr->m_pType = pType;
#endif
			}
		}

//		GetToken();

		return pExpr;
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '~')
	{
		GetToken();
		CExpression* pExpr;

		if (curtok->type == CToken::tok_ident)
		{
			std::string ident = std::string("~") + curtok->ident;

			pExpr = new CExpression;
			pExpr->tok.type = CToken::tok_ident;
			pExpr->tok.ident = strdup(ident.c_str());
		}
		else
		{
			pExpr = NULL;
			pPP->jerror("Expected identifier");
		}

		GetToken();

		return pExpr;
	}

	return NULL;
}

/*
id-expression:
	unqualified-id
	qualified-id
*/
CExpression* CCPPCompiler::id_expression(CClass* pNamespace, CScope* pScope)
{
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '::')
	{
		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;
		GetToken();
		
		if (curtok->type == CToken::tok_ident)
		{
			pExpr->right = new CExpression;
			pExpr->right->tok = *curtok;
			GetToken();

			/*
			if (!strcmp(pExpr->right->tok.ident, "IntuitionBase"))
			{
				printf("");
			}
			*/
		}
		else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_OPERATOR)
		{
			GetToken();

			if (curtok->type == CToken::tok_keyword &&
				(curtok->pkw->n == KW_NEW || curtok->pkw->n == KW_DELETE))
			{
				pExpr->right = new CExpression;
				pExpr->right->tok = *curtok;

				GetToken();
			}
			else
			{
				pPP->jerror("unrecognized operator");
				GetToken();
			}
		}
		else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_TEMPLATE)
		{
			pPP->jfatalerror("INTERNAL error, template not yet implemented here");
		}

		return pExpr;
	}
	else
	{
		/*
		if (curtok->type == CToken::tok_ident && !strcmp(curtok->ident, "CRegKey"))
		{
			printf("");
		}
		*/

		CExpression* pExpr = unqualified_id(pScope);

		while (curtok->type == CToken::tok_symbol && curtok->symbol == '::')
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok = *curtok;
			GetToken();

			pExpr2->left = pExpr;
			pExpr2->right = unqualified_id(pScope);

			pExpr = pExpr2;
		}

		return pExpr;
	}
}

CExpression* CCPPCompiler::literal(CScope* pScope)
{
	if (curtok->type == CToken::tok_integer)
	{
		CExpression* pnode = new CExpression;
		pnode->tok = *curtok;
		GetToken();
		return pnode;
	}
	else if (curtok->type == CToken::tok_double)
	{
		CExpression* pnode = new CExpression;
		pnode->tok = *curtok;
		GetToken();
		return pnode;
	}
	else if (curtok->type == CToken::tok_string)
	{
		CExpression* pnode = new CExpression;
		pnode->tok = *curtok;
		GetToken();
		return pnode;
	}
	else if (curtok->type == CToken::tok_wstring)
	{
		CExpression* pnode = new CExpression;
		pnode->tok = *curtok;
		GetToken();
		return pnode;
	}

	return NULL;
}

/*
primary-expression:
	literal
	this
	( expression )
	id-expression
*/
CExpression* CCPPCompiler::primary_expression(CClass* pInnermostClass, CScope* pScope)
{
	if (	curtok->type == CToken::tok_integer ||
			curtok->type == CToken::tok_double ||
			curtok->type == CToken::tok_string ||
			curtok->type == CToken::tok_wstring)
	{
		return literal(pScope);
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_TRUE)
	{
		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;
		GetToken();
		return pExpr;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_FALSE)
	{
		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;
		GetToken();
		return pExpr;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_THIS)
	{
		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;
		GetToken();

		return pExpr;
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
	{
		GetToken();

#if 0
	// Having trouble with '(', which also can mean a cast
	// Is it correct to handle the cast expression here ??
		Type* pType = type_id(pInnermostClass, pScope);
		if (pType)
		{
			CExpression* pCastExpr = new CExpression(pScope);
			pCastExpr->m_pType = pType;
			pCastExpr->tok.type = CToken::tok_symbol;
			pCastExpr->tok.symbol = ((DWORD)'('|('U'<<8));

			EatSymbol(')');
			pCastExpr->right = cast_expression(pInnermostClass, pScope);

			return pCastExpr;
		}
		else
#endif
		{
			CExpression* pExpr = expression(pInnermostClass, pScope);
			ASSERT(pExpr);
			EatSymbol(')');

			return pExpr;
		}
	}
	else
	{
		return id_expression(pInnermostClass, pScope);
	}
}

/*
expression-list:
	assignment-expression
	expression-list , assignment-expression
*/
CExpression* CCPPCompiler::expression_list(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = NULL;

	while (!pPP->_eof())
	{
		CExpression* pArgExpr = assignment_expression(pInnermostClass, pScope);
		if (pArgExpr == NULL)
		{
			pPP->jerror("Error in expression");
		}

		CExpression* pExpr2 = new CExpression;
		pExpr2->left = pArgExpr;
		pExpr2->right = pExpr;
		pExpr = pExpr2;

		if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
		{
			GetToken();
			continue;
		}
		break;
	}

	return pExpr;
}

/*
postfix-expression:
	primary-expression
	postfix-expression [ expression ]
	postfix-expression ( expression-listopt )
	simple-type-specifier ( expression-listopt )
	typename ::opt nested-name-specifier identifier ( expression-listopt )
	typename ::opt nested-name-specifier templateopt template-id ( expression-listopt )
	postfix-expression . templateopt id-expression
	postfix-expression -> templateopt id-expression
	postfix-expression . pseudo-destructor-name
	postfix-expression -> pseudo-destructor-name
	postfix-expression ++
	postfix-expression --
	dynamic_cast < type-id > ( expression )
	static_cast < type-id > ( expression )
	reinterpret_cast < type-id > ( expression )
	const_cast < type-id > ( expression )
	typeid ( expression )
	typeid ( type-id )
*/

CExpression* CCPPCompiler::postfix_expression(CClass* pInnermostClass, CScope* pScope)
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_TYPENAME)
	{
		pPP->jerror("typename not yet supported here");
		ASSERT(0);
	}
	else if (curtok->type == CToken::tok_keyword &&
		(curtok->pkw->n == KW_DYNAMIC_CAST ||
		curtok->pkw->n == KW_STATIC_CAST ||
		curtok->pkw->n == KW_REINTERPRET_CAST ||
		curtok->pkw->n == KW_CONST_CAST))
	{
		if (curtok->pkw->n == KW_CONST_CAST)
		{
			printf("");
		}
		GetToken();
/*
	dynamic_cast < type-id > ( expression )
	static_cast < type-id > ( expression )
	reinterpret_cast < type-id > ( expression )
	const_cast < type-id > ( expression )
	*/
		EatSymbol('<');
		Type* pType = type_id(pInnermostClass, pScope);
		EatSymbol('>');

		EatSymbol('(');
		CExpression* pExpr2 = expression(pInnermostClass, pScope);
		if (pExpr2)
		{
			ASSERT(0);
#if 0
			pExpr2->m_pType = pType;	// TODO, don't override this later
#endif
		}
		EatSymbol(')');

		return pExpr2;
	}

	CExpression* pExpr = primary_expression(pInnermostClass, pScope);
	if (pExpr == NULL)
	{
		pPP->jerror("Error in expression");
		return NULL;
	}

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '++' || curtok->symbol == '--'))
	{
		GetToken();
	}


	while (	curtok->symbol == '[' ||
				curtok->symbol == '(' ||
				curtok->symbol == '.' ||
				curtok->symbol == '->')
	{
		if (curtok->symbol == '[')
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok = *curtok;
			GetToken();

			pExpr2->left = pExpr;
			pExpr2->right = expression(pInnermostClass, pScope);

			pExpr = pExpr2;

			EatSymbol(']');
		}
		else if (curtok->symbol == '(')
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok = *curtok;

			pExpr2->left = pExpr;

			GetToken();
			if (curtok->type != CToken::tok_symbol || curtok->symbol != ')')
			{
				pExpr2->right = expression_list(pInnermostClass, pScope);
			}

			EatSymbol(')');

			pExpr = pExpr2;
		}
		else if (curtok->symbol == '.' || curtok->symbol == '->')
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok = *curtok;
			GetToken();

			pExpr2->left = pExpr;
			//templateopt id-expression
			//pExpr2->right = expression(pScope);
			//pExpr2->right = id_expression(
			pExpr2->right = id_expression(pInnermostClass, pScope);
#if 0
			if (curtok->type != CToken::tok_ident)
			{
				pPP->jerror("Expected member name");
			}

			pExpr2->right = new CExpression(pScope);
			pExpr2->right->tok = *curtok;
			GetToken();
#endif

			pExpr = pExpr2;

			//pExpr->m_pType = ExpressionType(pExpr, pScope);

			// TODO, maybe resolve this later
			{
				/*
				*/

			//	pExpr->left->
			}

			if (pExpr->left == NULL || pExpr->right == NULL)
			{
				delete pExpr;
				pExpr = NULL;
			}
		}
	}

	return pExpr;
}

/*
new-expression:
	::opt new new-placementopt new-type-id new-initializeropt
	::opt new new-placementopt ( type-id ) new-initializeropt

new-placement:
	( expression-list )

new-type-id:
	type-specifier-seq new-declaratoropt

new-declarator:
	ptr-operator new-declaratoropt
	direct-new-declarator

direct-new-declarator:
	[ expression ]
	direct-new-declarator [ constant-expression ]

new-initializer:
	( expression-listopt )
*/

/*
delete-expression:
::opt delete cast-expression
::opt delete [ ] cast-expression
*/

/*
unary-expression:
	postfix-expression
	++ cast-expression
	-- cast-expression
	unary-operator cast-expression
	sizeof unary-expression
	sizeof ( type-id )
	new-expression
	delete-expression

unary-operator: one of
	* & + - ! ˜
*/
CExpression* CCPPCompiler::unary_expression(CClass* pInnermostClass, CScope* pScope)
{
	if (curtok->type == CToken::tok_symbol && (
		curtok->symbol == '*' ||
		curtok->symbol == '&' ||
		curtok->symbol == '+' ||
		curtok->symbol == '-' ||
		curtok->symbol == '!' ||
		curtok->symbol == '~'))
	{
		int sym = curtok->symbol;

		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;
		pExpr->tok.symbol |= 'U'<<8;	// Unary
		GetToken();

	//	int paren = curtok->type == CToken::tok_symbol && curtok->symbol == '(';
		pExpr->right = cast_expression(pInnermostClass, pScope);
	//	if (paren)
	//	{
	//		EatSymbol(')');
	//	}

		if (pExpr)
		{
			if (pExpr->right->tok.type == CToken::tok_integer)
			{
				CExpression* pConstantExpr = new CExpression;
				pConstantExpr->tok.type = CToken::tok_integer;

				switch (sym)
				{
				case '+':
					pConstantExpr->tok.int32 = pExpr->right->tok.int32;
					break;

				case '-':
					pConstantExpr->tok.int32 = -pExpr->right->tok.int32;
					break;

				case '!':
					pConstantExpr->tok.int32 = !pExpr->right->tok.int32;
					break;

				case '~':
					pConstantExpr->tok.int32 = ~pExpr->right->tok.int32;
					break;

				default:	// TODO '*', '&'
					ASSERT(0);
				}

				delete pExpr;
				pExpr = pConstantExpr;
			}
		}

		return pExpr;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_NEW)
	{
		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;
		GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
		{
			ASSERT(0);
		}
		Type* pType = type_specifier_seq(pInnermostClass, pScope);
		//new_type_id();
		pType = abstract_declarator(pType);
	//	pExpr->right = CExpression(pScope);
		ASSERT(0);
#if 0
		pExpr->m_pType = new Type(type_pointer, sizeof_pointer);
		pExpr->m_pType->m_pPointerTo = pType;
#endif

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '[')
		{
			GetToken();

			CExpression* pExpr = expression(pInnermostClass, pScope);
			EatSymbol(']');
		}

		// ( expression-listopt )
		if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
		{
			GetToken();

			CExpression* pExpr = expression_list(pInnermostClass, pScope);
			EatSymbol(')');
		}

		return pExpr;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_DELETE)
	{
		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;
		GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '[')
		{
			GetToken();
			EatSymbol(']');
		}

		pExpr->right = cast_expression(pInnermostClass, pScope);

		return pExpr;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_SIZEOF)
	{
		GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
		{
			GetToken();

			CExpression* pExpr = NULL;

			Type* pType = type_id(pInnermostClass, pScope);
			if (pType)
			{
				pExpr = new CExpression;
				pExpr->tok.type = CToken::tok_integer;
				pExpr->tok.int32 = pType->get_sizeof();
			}
			else
			{
				CExpression* pExpr2 = unary_expression(pInnermostClass, pScope);
				if (pExpr2 == NULL)
				{
					pPP->jerror("Unexpected");
				}
				else
				{
					pExpr = new CExpression;
					pExpr->tok.type = CToken::tok_symbol;
					pExpr->tok.symbol = 'szof';

					pExpr->right = pExpr2;
				//	pExpr = pExpr2;
					/*
					ASSERT(0);
#if 0
					pExpr2 = Reduce(pExpr2, pScope);
				//	pExpr = new CExpression(pScope);
				//	pExpr->tok.type = CToken::tok_integer;
					if (pExpr2->m_pType)
						pExpr->tok.int32 = pExpr2->m_pType->get_sizeof();
					else
						pExpr->tok.int32 = -1;
#endif

					delete pExpr2;
					*/
				}

			//	pPP->jerror("Expected type_id");
			}

			EatSymbol(')');

			ASSERT(pExpr);

			return pExpr;
		}
		else
		{
			CExpression* pExpr2 = unary_expression(pInnermostClass, pScope);
			if (pExpr2 == NULL)
			{
				pPP->jerror("Unexpected");
			}
			else
			{
#if 0
				ExpressionType(pExpr2, pScope);
#endif

				CExpression* pExpr = new CExpression;
				pExpr->tok.type = CToken::tok_integer;
				ASSERT(0);
#if 0
				pExpr->tok.int32 = pExpr2->m_pType->get_sizeof();
#endif

				delete pExpr2;

				ASSERT(pExpr);
				return pExpr;
			}
		}
	}
	else
	{
		return postfix_expression(pInnermostClass, pScope);
	}
	ASSERT(0);
	return NULL;
}

/*
cast-expression:
	unary-expression
	( type-id ) cast-expression
*/
CExpression* CCPPCompiler::cast_expression(CClass* pInnermostClass, CScope* pScope)
{
//	CToken tok0 = *curtok;
	int paren = curtok->type == CToken::tok_symbol && curtok->symbol == '(';
	if (paren)	// C
	{
		int save = m_tokStack2.size();
		/*
		ASSERT(gSave == NULL);
		gSave = new CSave;
		gSave->m_tokStack.push(*curtok);
		*/

		GetToken();
		//CToken tok1 = *curtok;

		if (curtok->type == CToken::tok_ident && !strcmp(curtok->ident, "CComDispatchDriver"))
		{
			printf("");
		}

		Type* pType = type_id(pInnermostClass, pScope);
		if (pType)
		{
			CExpression* pCastExpr = new CExpression;
			pCastExpr->cast.m_pType = pType;
			pCastExpr->tok.type = CToken::tok_symbol;
			pCastExpr->tok.symbol = (DWORD)'('|('U'<<8);

			if (curtok->type == CToken::tok_symbol && curtok->symbol == ')')
			{
			//	delete gSave;
			//	gSave = NULL;

				GetToken();

				pCastExpr->right = cast_expression(pInnermostClass, pScope);

				return pCastExpr;
			}
			else
			{
				printf("");
			//	m_tokStack.push(*curtok);
			}
		}
		/*
		m_tokStack.push(tok1);
		m_tokStack.push(tok0);
		GetToken();
		*/
		//Restore(gSave);
		Restore(save);
	}

	CExpression* pExpr = unary_expression(pInnermostClass, pScope);
	return pExpr;

#if 0
	{
		GetToken();

	//	pPP->jfatalerror("cast is currently not supported");
		Type* pType = type_id(pScope);
		if (pType)
		{
			EatSymbol(')');
			CExpression* pCastExpr = cast_expression(pScope);

			return pCastExpr;
		}
		else
		// Duplicated from primary expression
		{
			CExpression* pExpr = expression(pScope);
			ASSERT(pExpr);
			EatSymbol(')');

			return pExpr;
		}
	}
	else
	{
		return unary_expression(pNamespace, pScope);
	}
	ASSERT(0);
#endif
}

/*
pm-expression:
	cast-expression
	pm-expression .* cast-expression
	pm-expression ->* cast-expression
*/
CExpression* CCPPCompiler::pm_expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = cast_expression(pInnermostClass, pScope);

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '.*' || curtok->symbol == '->*'))
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = cast_expression(pInnermostClass, pScope);

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
multiplicative-expression:
	pm-expression
	multiplicative-expression * pm-expression
	multiplicative-expression / pm-expression
	multiplicative-expression % pm-expression
*/
CExpression* CCPPCompiler::multiplicative_expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = pm_expression(pInnermostClass, pScope);
	/*
	if (pExpr == NULL)
	{
		pPP->jfatalerror("Error parsing expression");
	}
	*/

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '*' || curtok->symbol == '/' || curtok->symbol == '%'))
	{
		int sym = curtok->symbol;

		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = pm_expression(pInnermostClass, pScope);

		if (pExpr2->left->tok.type == CToken::tok_integer &&
			pExpr2->right->tok.type == CToken::tok_integer)
		{
			CExpression* pConstantExpr = new CExpression;
			pConstantExpr->tok.type = CToken::tok_integer;

			if (sym == '*')
			{
				pConstantExpr->tok.int32 = pExpr2->left->tok.int32 * pExpr2->right->tok.int32;
			}
			else
			{
				if (pExpr2->right->tok.int32 != 0)
				{
					if (sym == '/')
					{
						pConstantExpr->tok.int32 = pExpr2->left->tok.int32 / pExpr2->right->tok.int32;
					}
					else
					{
						pConstantExpr->tok.int32 = pExpr2->left->tok.int32 % pExpr2->right->tok.int32;
					}
				}
				else
				{
					pPP->jerror("division by zero in constant expression");
				}
			}

			delete pExpr2;
			pExpr2 = pConstantExpr;
		}

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
additive-expression:
	multiplicative-expression
	additive-expression + multiplicative-expression
	additive-expression - multiplicative-expression
*/
CExpression* CCPPCompiler::additive_expression(CClass* pNamespace, CScope* pScope)
{
	CExpression* pExpr = multiplicative_expression(pNamespace, pScope);

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '+' || curtok->symbol == '-'))
	{
		int sym = curtok->symbol;

		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = multiplicative_expression(pNamespace, pScope);

		if (pExpr2->left && pExpr2->right)
		{
			if (pExpr2->left->tok.type == CToken::tok_integer &&
				pExpr2->right->tok.type == CToken::tok_integer)
			{
				CExpression* pConstantExpr = new CExpression;
				pConstantExpr->tok.type = CToken::tok_integer;

				if (sym == '+')
				{
					pConstantExpr->tok.int32 = pExpr2->left->tok.int32 + pExpr2->right->tok.int32;
				}
				else
				{
					pConstantExpr->tok.int32 = pExpr2->left->tok.int32 - pExpr2->right->tok.int32;
				}

				delete pExpr2;
				pExpr2 = pConstantExpr;
			}
		}

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
shift-expression:
	additive-expression
	shift-expression << additive-expression
	shift-expression >> additive-expression
*/
CExpression* CCPPCompiler::shift_expression(CClass* pNamespace, CScope* pScope)
{
	CExpression* pExpr = additive_expression(pNamespace, pScope);

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '<<' || curtok->symbol == '>>'))
	{
		int sym = curtok->symbol;

		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = additive_expression(pNamespace, pScope);

		if (pExpr2->left->tok.type == CToken::tok_integer &&
			pExpr2->right->tok.type == CToken::tok_integer)
		{
			CExpression* pConstantExpr = new CExpression;
			pConstantExpr->tok.type = CToken::tok_integer;

			if (sym == '<<')
			{
				pConstantExpr->tok.int32 = pExpr2->left->tok.int32 << pExpr2->right->tok.int32;
			}
			else
			{
				pConstantExpr->tok.int32 = pExpr2->left->tok.int32 >> pExpr2->right->tok.int32;
			}

			delete pExpr2;
			pExpr2 = pConstantExpr;
		}

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
relational-expression:
	shift-expression
	relational-expression < shift-expression
	relational-expression > shift-expression
	relational-expression <= shift-expression
	relational-expression >= shift-expression
*/

BOOL bInTemplateArg = FALSE;

CExpression* CCPPCompiler::relational_expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = shift_expression(pInnermostClass, pScope);
	if (pExpr == NULL)
	{
		pPP->jerror("error in expression");
		return NULL;
	}

	while (curtok->type == CToken::tok_symbol &&
		(	(curtok->symbol == '<') ||
			(curtok->symbol == '>' && !bInTemplateArg) ||
			(curtok->symbol == '<=' || curtok->symbol == '>=')))
	{
		int sym = curtok->symbol;

		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = shift_expression(pInnermostClass, pScope);

		if (pExpr2->right == NULL)
		{
			pPP->jerror("error in expression");
			return NULL;
		}
		else
		{
			if (pExpr2->left->tok.type == CToken::tok_integer &&
				pExpr2->right->tok.type == CToken::tok_integer)
			{
				CExpression* pConstantExpr = new CExpression;
				pConstantExpr->tok.type = CToken::tok_integer;

				if (sym == '<')
				{
					pConstantExpr->tok.int32 = pExpr2->left->tok.int32 < pExpr2->right->tok.int32;
				}
				else if (sym == '>')
				{
					pConstantExpr->tok.int32 = pExpr2->left->tok.int32 > pExpr2->right->tok.int32;
				}
				else if (sym == '<=')
				{
					pConstantExpr->tok.int32 = pExpr2->left->tok.int32 <= pExpr2->right->tok.int32;
				}
				else if (sym == '>=')
				{
					pConstantExpr->tok.int32 = pExpr2->left->tok.int32 >= pExpr2->right->tok.int32;
				}

				delete pExpr2;
				pExpr2 = pConstantExpr;
			}

			pExpr = pExpr2;
		}
	}

	return pExpr;
}

/*
equality-expression:
	relational-expression
	equality-expression == relational-expression
	equality-expression != relational-expression
*/
CExpression* CCPPCompiler::equality_expression(CClass* pNamespace, CScope* pScope)
{
	CExpression* pExpr = relational_expression(pNamespace, pScope);
	if (pExpr == NULL)
	{
		pPP->jerror("Error in expression");
		return NULL;
	}

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '==' || curtok->symbol == '!='))
	{
		int sym = curtok->symbol;

		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = relational_expression(pNamespace, pScope);

		if (pExpr2->left->tok.type == CToken::tok_integer &&
			pExpr2->right->tok.type == CToken::tok_integer)
		{
			CExpression* pConstantExpr = new CExpression;
			pConstantExpr->tok.type = CToken::tok_integer;

			if (sym == '==')
			{
				pConstantExpr->tok.int32 = pExpr2->left->tok.int32 == pExpr2->right->tok.int32;
			}
			else
			{
				pConstantExpr->tok.int32 = pExpr2->left->tok.int32 != pExpr2->right->tok.int32;
			}

			delete pExpr2;
			pExpr2 = pConstantExpr;
		}

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
and-expression:
	equality-expression
	and-expression & equality-expression
*/
CExpression* CCPPCompiler::and_expression(CClass* pNamespace, CScope* pScope)
{
	CExpression* pExpr = equality_expression(pNamespace, pScope);

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '&'))
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = equality_expression(pNamespace, pScope);

		if (pExpr2->left->tok.type == CToken::tok_integer &&
			pExpr2->right->tok.type == CToken::tok_integer)
		{
			CExpression* pConstantExpr = new CExpression;
			pConstantExpr->tok.type = CToken::tok_integer;

			pConstantExpr->tok.int32 = pExpr2->left->tok.int32 & pExpr2->right->tok.int32;

			delete pExpr2;
			pExpr2 = pConstantExpr;
		}

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
exclusive-or-expression:
	and-expression
	exclusive-or-expression ˆ and-expression
*/
CExpression* CCPPCompiler::exclusive_or_expression(CClass* pNamespace, CScope* pScope)
{
	CExpression* pExpr = and_expression(pNamespace, pScope);

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '^'))
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = and_expression(pNamespace, pScope);

		if (pExpr2->left->tok.type == CToken::tok_integer &&
			pExpr2->right->tok.type == CToken::tok_integer)
		{
			CExpression* pConstantExpr = new CExpression;
			pConstantExpr->tok.type = CToken::tok_integer;

			pConstantExpr->tok.int32 = pExpr2->left->tok.int32 ^ pExpr2->right->tok.int32;

			delete pExpr2;
			pExpr2 = pConstantExpr;
		}

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
inclusive-or-expression:
	exclusive-or-expression
	inclusive-or-expression | exclusive-or-expression
*/
CExpression* CCPPCompiler::inclusive_or_expression(CClass* pNamespace, CScope* pScope)
{
	CExpression* pExpr = exclusive_or_expression(pNamespace, pScope);

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '|'))
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = exclusive_or_expression(pNamespace, pScope);

		if (pExpr2->left->tok.type == CToken::tok_integer &&
			pExpr2->right->tok.type == CToken::tok_integer)
		{
			CExpression* pConstantExpr = new CExpression;
			pConstantExpr->tok.type = CToken::tok_integer;

			pConstantExpr->tok.int32 = pExpr2->left->tok.int32 | pExpr2->right->tok.int32;

			delete pExpr2;
			pExpr2 = pConstantExpr;
		}

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
logical-and-expression:
	inclusive-or-expression
	logical-and-expression && inclusive-or-expression
*/
CExpression* CCPPCompiler::logical_and_expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = inclusive_or_expression(pInnermostClass, pScope);
	if (pExpr == NULL)
		return NULL;

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '&&'))
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = inclusive_or_expression(pInnermostClass, pScope);
		if (pExpr2->right)
		{
			if (pExpr2->left->tok.type == CToken::tok_integer &&
				pExpr2->right->tok.type == CToken::tok_integer)
			{
				CExpression* pConstantExpr = new CExpression;
				pConstantExpr->tok.type = CToken::tok_integer;

				pConstantExpr->tok.int32 = pExpr2->left->tok.int32 && pExpr2->right->tok.int32;

				delete pExpr2;
				pExpr2 = pConstantExpr;
			}

			pExpr = pExpr2;
		}
	}

	return pExpr;
}

/*
logical-or-expression:
	logical-and-expression
	logical-or-expression || logical-and-expression
*/
CExpression* CCPPCompiler::logical_or_expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = logical_and_expression(pInnermostClass, pScope);
	if (pExpr == NULL)
		return NULL;

	while (curtok->type == CToken::tok_symbol &&
		(curtok->symbol == '||'))
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = logical_and_expression(pInnermostClass, pScope);
		if (pExpr2->right)
		{
			if (pExpr2->left->tok.type == CToken::tok_integer &&
				pExpr2->right->tok.type == CToken::tok_integer)
			{
				CExpression* pConstantExpr = new CExpression;
				pConstantExpr->tok.type = CToken::tok_integer;

				pConstantExpr->tok.int32 = pExpr2->left->tok.int32 || pExpr2->right->tok.int32;

				delete pExpr2;
				pExpr2 = pConstantExpr;
			}

			pExpr = pExpr2;
		}
	}

	return pExpr;
}

/*
conditional-expression:
	logical-or-expression
	logical-or-expression ? expression : assignment-expression
*/
#if 0
CExpression* CCPPCompiler::conditional_expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = logical_or_expression(pInnermostClass, pScope);

	if (curtok->type == CToken::tok_symbol && curtok->symbol == '?')
	{
		GetToken();

		CExpression* pExpr2 = expression(pInnermostClass, pScope);
		EatSymbol(':');
		CExpression* pExpr3 = assignment_expression(pInnermostClass, pScope);
	}

	return pExpr;
}
#endif

CExpression* CCPPCompiler::constant_expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = logical_or_expression(pInnermostClass, pScope);
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '?')
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;

		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = new CExpression;
		pExpr2->right->tok.type = CToken::tok_symbol;
		pExpr2->right->tok.symbol = ':';

		pExpr2->right->left = expression(pInnermostClass, pScope);
		EatSymbol(':');
		pExpr2->right->right = assignment_expression(pInnermostClass, pScope);

		pExpr = pExpr2;
	}
	else
	{
	}

	return pExpr;
}

/*
assignment-expression:
	conditional-expression
		logical-or-expression
		logical-or-expression ? expression : assignment-expression

   logical-or-expression assignment-operator assignment-expression
	throw-expression

assignment-operator: one of
	= *= /= %= += -= >>= <<= &= ˆ= |=
*/

CExpression* CCPPCompiler::assignment_expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = logical_or_expression(pInnermostClass, pScope);
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '?')
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;

		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = new CExpression;

		pExpr2->right->left = expression(pInnermostClass, pScope);
		EatSymbol(':');
		pExpr2->right->right = assignment_expression(pInnermostClass, pScope);

		pExpr = pExpr2;
	}
	else if (curtok->type == CToken::tok_symbol &&
		(	curtok->symbol == '=' ||
			curtok->symbol == '+=' ||
			curtok->symbol == '-=' ||
			curtok->symbol == '*=' ||
			curtok->symbol == '/=' ||
			curtok->symbol == '%=' ||
			curtok->symbol == '|=' ||
			curtok->symbol == '&=' ||
			curtok->symbol == '^=' ||
			curtok->symbol == '>>=' ||
			curtok->symbol == '<<='))
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = assignment_expression(pInnermostClass, pScope);

		pExpr = pExpr2;
	}

	return pExpr;

//	return conditional_expression(pScope);
}

/*
expression:
	assignment-expression
	expression , assignment-expression
*/
CExpression* CCPPCompiler::expression(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = assignment_expression(pInnermostClass, pScope);
	if (pExpr == NULL)
		return NULL;

	while (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = assignment_expression(pInnermostClass, pScope);

		pExpr = pExpr2;
	}

	return pExpr;
}

/////////////////////////////////////////////////////////////////////////////
// Classes

//CScope* GetScope(CScope* pScope, CExpression* pExpr);

/*
class-key:
	class
	struct
	union
*/
#if 0
BOOL class_key()
{
	if (curtok->type == CToken::tok_keyword && (
		curtok->pkw->n == KW_CLASS ||
		curtok->pkw->n == KW_STRUCT ||
		curtok->pkw->n == KW_UNION))
	{
		GetToken();
		return TRUE;
	}

	pPP->jfatalerror("Unexpected\n");
	return FALSE;
}
#endif

/*
class-or-namespace-name:
	class-name
	namespace-name
*/

/*
nested-name-specifier:
	class-or-namespace-name :: nested-name-specifieropt
	class-or-namespace-name :: template nested-name-specifier
*/
CExpression* CCPPCompiler::nested_name_specifier(CScope* pScope)
{
	CExpression* pExpr = new CExpression;

	if (curtok->type == CToken::tok_ident)
	{
		ASSERT(curtok->type == CToken::tok_ident);
		pExpr->tok = *curtok;
		GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '<')
		{
			GetToken();

			Type* pType2 = new Type(type_templateinst);
			pType2->m_pDeclarator = new CDeclarator;
			pType2->m_pDeclarator->m_name = pExpr->tok.ident;//pType->m_pNamedType->m_name;
			pType2->m_pDeclarator->m_name += "<>";
			//pType2->m_pDeclarator->m_pType = pType;

			ASSERT(0);
#if 0
			pExpr->m_pType = pType2;
#endif

			bInTemplateArg = TRUE;

			while (!pPP->_eof())
			{
				Type* pArgType = type_id(NULL, pScope);

			//	Type* pArgType = type_specifier_seq(NULL, pScope);
				if (pArgType == NULL)
				{
					CExpression* pExpr = assignment_expression(NULL, pScope);
					if (pExpr == NULL)
					{
						char msg[512];
						if (curtok->type == CToken::tok_ident)
						{
							sprintf(msg, "Expected type '%s'", curtok->ident);
						}
						else if (curtok->type == CToken::tok_symbol)
						{
							sprintf(msg, "Expected type '%c'", (char)curtok->symbol);
						}
						else
						{
							sprintf(msg, "Expected type");
						}

						pPP->jerror(msg);
					//	GetToken();
					}
				}

				if (pArgType)
				{
					pType2->m_ArgTypes.push_back(pArgType);
				}

				if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
				{
					GetToken();
					continue;
				}
				break;
			}

			EatSymbol('>');
			bInTemplateArg = FALSE;
		}

		while (curtok->type == CToken::tok_symbol && curtok->symbol == '::')
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok = *curtok;
			GetToken();

			pExpr2->left = pExpr;

			pExpr = pExpr2;

			if (curtok->type == CToken::tok_ident)
			{
				ASSERT(curtok->type == CToken::tok_ident);
				pExpr2->right = new CExpression;
				pExpr2->right->tok = *curtok;
				GetToken();

				if (curtok->type == CToken::tok_symbol && curtok->symbol == '<')
				{
					GetToken();
					while (!pPP->_eof())
					{
						if (curtok->type == CToken::tok_symbol && curtok->symbol == '>')
						{
							break;
						}
						GetToken();
					}
					EatSymbol('>');
				}
			}
		}
	}

	return pExpr;
}

/*
class-name:
	identifier
	template-id
*/

/*
member-declarator:
	declarator pure-specifieropt
	declarator constant-initializeropt
	identifieropt : constant-expression
*/
CDeclarator* CCPPCompiler::member_declarator(CClass* pClass, CDeclSpecifiers& declspecs, CClass* pInnermostClass, CScope* pScope)
{
	/*
	if (curtok->type == CToken::tok_symbol && curtok->symbol == ';')
	{
		GetToken();
		return;
	}
	*/

//	CScope* pDeclScope;
	Type* pType = declspecs.m_type.GetType(this);

//	ASSERT(pType);

	CDeclarator* pDeclarator = new CDeclarator;
	pDeclarator->m_pType = declarator(pDeclarator, pType, pInnermostClass, pScope);
	ASSERT(pDeclarator->m_pOwnerScope);

	if (pDeclarator->m_pType)
	{
		ASSERT(pDeclarator->m_pType);

		if (pDeclarator->m_pType->GetType()->m_type == type_function)//m_pFunction)
		{
			Type* pType = pDeclarator->m_pType->GetType();

			// 'this' as first (i.e. last pushed on stack) parameter
			{
				pType->m_pFunction->m_thiscall = TRUE;
				pType->m_pFunction->m_stackSize += sizeof_pointer;

				CDeclarator* pParamDeclarator = new CDeclarator;
				pParamDeclarator->m_pType = new Type(type_pointer, sizeof_pointer);
				pParamDeclarator->m_pType->m_pPointerTo = new Type(type_class);
				pParamDeclarator->m_pType->m_pPointerTo->m_pClass = pClass;
#if 0	// Had this
				pParamDeclarator->m_spOffset = -12;
			// Adjust the parameters' already specified stacks offset
				for (int i = 0; i < pType->m_pFunction->m_parameters.size(); i++)
				{
					pType->m_pFunction->m_parameters[i]->m_spOffset -= 4;
				}
#endif
				pType->m_pFunction->m_parameters.insert(pType->m_pFunction->m_parameters.begin(), pParamDeclarator);
			}

			pType->m_pFunction->m_funcspec = declspecs.functionSpecifierKW;

			if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
			{
				GetToken();

				if (curtok->type == CToken::tok_integer)
				{
					if (curtok->int32 != 0)
					{
						pPP->jerror("pure specifier? should be '= 0'");
					}
					GetToken();
				}
				else
				{
					pPP->jerror("Expected '0'");
				}

				if (pDeclarator->m_pType->GetType()->m_pFunction->m_funcspec != KW_VIRTUAL)
				{
					pPP->jerror("only virtual function can have pure specifier");
				}
			}
		}
		else
		{
			if (curtok->type == CToken::tok_symbol && curtok->symbol == ':')
			{
				GetToken();
				CExpression* pExpr = constant_expression(pInnermostClass, pScope);
			}
		}

		return pDeclarator;
	}
	else
	{
		delete pDeclarator;
		return NULL;
	}
}

/*
member-declarator-list:
	member-declarator
	member-declarator-list , member-declarator
*/
/*
void member_declarator_list(CClass* pClass, Type* pType, CClass* pNamespace, CScope* pScope)
{
}
*/

/*
member-declaration:
	decl-specifier-seqopt member-declarator-listopt ;
	function-definition ;opt
	::opt nested-name-specifier templateopt unqualified-id ;
	using-declaration
	template-declaration
*/
void CCPPCompiler::member_declaration(CClass* pClass, CClass* pInnermostClass, CScope* pScope)
{
	if (curtok->type == CToken::tok_keyword && (
				curtok->pkw->n == KW_EXPORT ||
				curtok->pkw->n == KW_TEMPLATE))
	{
		template_declaration(pInnermostClass, pScope);
	}
	else
	{
		bool bTypedef;
		CDeclSpecifiers declspecs;
		decl_specifier_seq(pInnermostClass, pScope, declspecs, bTypedef);

		Type* pType = declspecs.m_type.GetType(this);
	#if 0
		if (pType == NULL)
		{
			char msg[512];
			if (curtok->type == CToken::tok_ident)
			{
				sprintf(msg, "Undeclared type '%s'", curtok->ident);
			}
			else
			{
				sprintf(msg, "Expected type");
			}

			pPP->jerror(msg);
			GetToken();
		}
		else
		{
			if (pType->GetType()->m_type == type_class && pType->m_pClass == pClass)
			{
				pPP->jwarn("constructor");
			}
		}
	#endif

		//member_declarator_list(pClass, pType, bTypedef, pNamespace, pScope);

		if (curtok->type == CToken::tok_symbol && curtok->symbol == ';')
		{
			GetToken();

			if (pType)
			{
				Type* pType2 = pType->GetType();
				if (pType2->m_type == type_class)
				{
					if (FALSE)
					{
						pPP->jwarn("nameless class/struct/union");
					}

					CDeclarator* pDeclarator = new CDeclarator;
					pDeclarator->m_pType = pType;

					// TODO, m_sizeof, same as below

					pClass->m_pScope->AddDeclarator(new CDeclaratorReference(pDeclarator));
				}
			}
		}
		else
		{
			while (!pPP->_eof())
			{

			//	pScope->m_decls.insert(declsmap::value_type(pMember->m_pDeclarator->m_name, pMember->m_pDeclarator));
				if (bTypedef)
				{
					CDeclarator* pDeclarator = member_declarator(pClass, declspecs, pInnermostClass, pScope);
					if (pDeclarator)
					{
						//if (pDeclarator->m_name ==
						typedef_declarator(pDeclarator, pScope);
					}
				}
				else
				{
				//	CMember* pMember = new CMember;

				//	pMember->m_pDeclarator = new CDeclarator;
				//	pMember->m_pDeclarator->m_pType = pType;

					CDeclarator* pDeclarator = member_declarator(pClass, declspecs, pInnermostClass, pScope);

					if (pDeclarator)
					{
						pDeclarator->m_linkage = LINKAGE_EXTERN_CPP;

#if 0	// TODO, had this, do it later
						if (pClass->m_kwType == KW_UNION)
						{
							/*
							pMember->m_offset = 0;	// All members start at offset 0 in a union
							*/
							pDeclarator->m_spOffset = 0;

							if (/*pMember->m_*/pDeclarator->m_pType)
							{
								// The size of the union is the maximum size of its members
								long memberSize = /*pMember->m_*/pDeclarator->m_pType->get_sizeof();
								ASSERT(memberSize != -1);
								if (memberSize > pClass->/*m_pType->*/ m_sizeof)
								{
									pClass->/*m_pType->*/m_sizeof = memberSize;
								}
							}
						}
						else	// struct/class
						{
							pDeclarator->m_spOffset = pClass->m_sizeof;
							ASSERT(pDeclarator->m_spOffset != -1);

							if (pDeclarator->m_pType)
							{
								Type* pType = pDeclarator->m_pType->GetType();
								if (pType->m_type != type_function)
								{
									ULONG _sizeof = pDeclarator->m_pType->get_sizeof();
									ASSERT(_sizeof >= 0);
									// word-align
									if (_sizeof >= 2)
									{
										pDeclarator->m_spOffset = ((pDeclarator->m_spOffset+1)/2)*2;

										//pDeclarator->m_spOffset = (pDeclarator->m_spOffset + 1) ~ 1;
									}

									pClass->m_sizeof = pDeclarator->m_spOffset + _sizeof;
								}
							}
						}
#endif

						/*
						pClass->m_members.push_back(pMember);
						*/

						BOOL bFunctionBody = nontypedef_declarator(/*pMember->m_*/pDeclarator, pInnermostClass, pScope);

						if (bFunctionBody)
						{
							return;// TRUE;
						}
					}
					/*
					else
					{
						ASSERT(0);
					}
					*/
				}

			//	printf("member name: %s\n", pMember->m_pDeclarator->m_name.c_str());

				if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
				{
					GetToken();
					continue;
				}
				break;

			}

			EatSymbol(';');
		}
	}
}

/*
access-specifier:
	private
	protected
	public
*/

/*
member-specification:
	member-declaration member-specificationopt
	access-specifier : member-specificationopt
*/
void CCPPCompiler::member_specification(CClass* pClass, CClass* pInnermostClass, CScope* pScope)
{
#if 0
	ASSERT(pClass->/*m_pType->*/m_sizeof == -1);
	pClass->/*m_pType->*/m_sizeof = 0;
#endif

	while (!pPP->_eof())
	{
		// {
		if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
			break;

		if (curtok->type == CToken::tok_keyword && curtok->pkw->flags & kwAccessSpecifier)
		{
			ASSERT(curtok->pkw->n == KW_PRIVATE || curtok->pkw->n == KW_PROTECTED || curtok->pkw->n == KW_PUBLIC);
			GetToken();

			EatSymbol(':');
		}
		else if (curtok->type == CToken::tok_symbol && curtok->symbol == ';')
		{
			GetToken();
		}
		else
		{
			member_declaration(pClass, pInnermostClass, pScope);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// Statements

/*
condition:
	expression
	type-specifier-seq declarator = assignment-expression
*/

/*
jump-statement:
	break ;
	continue ;
	return expressionopt ;
	goto identifier ;
*/

/*
for-init-statement:
	expression-statement
	simple-declaration
*/

/*
iteration-statement:
	while ( condition ) statement
	do statement while ( expression ) ;
	for ( for-init-statement conditionopt ; expressionopt ) statement
*/

/*
statement:
	labeled-statement
	expression-statement
	compound-statement
	selection-statement
	iteration-statement
	jump-statement
	declaration-statement
		block-declaration
	try-block
*/


CExpression* CCPPCompiler::initialize(CExpression* dst, CExpression* pInitializerExpr, Type* pType, CCompoundStatement* pCompoundStmt)
{
	ASSERT(pType);
	pType = pType->GetType();

	if (pType->m_type == type_class)
	{
		CClass* pClass = pType->GetClass();

		BOOL bBrace = (pInitializerExpr->tok.type == CToken::tok_symbol && pInitializerExpr->tok.symbol == '{');	// }
		CExpression* p;
		if (bBrace)
		{
			p = pInitializerExpr->right;
		}
		else
		{
			p = pInitializerExpr;
		}

		int size = 0;
		int i = 0;
		while (p)
		{
			if (i >= pClass->m_pScope->m_orderedDecls.size())
			{
				if (bBrace)
					pPP->jerror("too many initializers");
				break;
			}

			CDeclarator* pMemberDecl = pClass->m_pScope->m_orderedDecls[i]->m_pDeclarator;
			if (pMemberDecl->m_storageClassKW != KW_STATIC)	// skip static members
			{
				initialize(
					A_Binop('.',
						dst,
						A_Ident(pMemberDecl->m_name.c_str())
					),
					p->left, pMemberDecl->m_pType, pCompoundStmt);

				size += pMemberDecl->m_pType->get_sizeof();

				p = p->right;
			}

			i++;
		}

		if (size < pClass->m_sizeof)//i < pClass->m_pScope->m_orderedDecls.size())
		{
#if 0
			// set rest to zero
			CZeroStatement* pStmt = new CZeroStatement;
			pStmt->m_spOffset = - pClass->m_sizeof - pDeclarator->m_spOffset + size;
			pStmt->m_length = pClass->m_sizeof - size;

			pCompoundStmt->m_pBlock->m_statements.push_back(pStmt);
#endif
		}

		return p;
	}
	else if (pType->m_type == type_array)
	{
		if (pInitializerExpr->tok.type == CToken::tok_symbol && pInitializerExpr->tok.symbol == '{')	// }
		{
			int i = 0;
			CExpression* p = pInitializerExpr->right;
			while (p)
			{
				if (pType->m_arrayDims.size() != 0)
				{
					if (i > pType->m_arrayDims.size())
					{
						pPP->jerror("Too many initializers");
					}
				}
				/*
				CExpressionStatement* pStmt = A_Expr(
					A_Binop('=',
						A_Binop('[',
							A_Ident(pDeclarator->m_name.c_str()),
							A_Const(i)
						),
						p->left
					)
				);
				*/
				if (p->left->tok.symbol == '{')
				{
					initialize(
						A_Binop('[',
							dst,
							A_Const(i)),
						p->left,
						pType->m_pPointerTo, pCompoundStmt);

					p = p->right;
				}
				else
				{
					p = initialize(
						A_Binop('[',
							dst,
							A_Const(i)),
						p,
						pType->m_pPointerTo, pCompoundStmt);
				}

			//	pCompoundStmt->m_pBlock->m_statements.push_back(pStmt);

				i++;
			}

			if (pType->m_arrayDims.size() == 0)
			{
				pType->m_arrayDims.push_back(i);

				pType->m_sizeof = i * pType->m_pPointerTo->get_sizeof();
			}

			return p;
		}
		else
		{
			ASSERT(0);
		//	pPP->jerror("Invalid initializer clause for non-aggregate type");
		}
	}
	else
	{
		CExpressionStatement* pStmt = A_Expr(
			A_Binop('=',
				dst,
				pInitializerExpr
			)
		);

		pCompoundStmt->m_pBlock->m_statements.push_back(pStmt);
	}
	return NULL;
}

CStatement* CCPPCompiler::statement(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CScope* pScope)
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_RETURN)
	{
		GetToken();

		CReturnStatement* pStmt = new CReturnStatement;

		if (curtok->type != CToken::tok_symbol || curtok->symbol != ';')
		{
			if (pFunctionDecl->m_pType->m_type == type_void)
			{
				pPP->jerror("void function shouldn't return anything");
			}

			pStmt->m_expr = expression(pInnermostClass, pScope);
		//	pStmt->m_expr = Reduce(pStmt->m_expr, pScope);

#if 0
			pStmt->Evaluate(this, pFunctionDecl);	// ??
#endif
			if (pStmt->m_expr)
			{

#if 0
				pInnermostClass->m_pIDExprs->m_v.push_back(pStmt->m_expr);
			//	ExpressionType(pStmt->m_expr, pScope);
#endif
			}
		}
		else
		{
			if (pFunctionDecl->m_pType->m_type != type_void)
			{
				pPP->jerror("You should return something");
			}
		}

		EatSymbol(';');

		return pStmt;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_IF)
	{
		GetToken();
		
		CIfStatement* pStmt = new CIfStatement;

		EatSymbol('(');

		pStmt->m_pIfScope = T_Scope();
		pStmt->m_pIfScope->m_pParentScope = pScope;
#if 0
		pStmt->m_pIfScope->m_spOffset += pScope->m_stackSize;
#endif

		// condition
		Type* pType = type_specifier_seq(pInnermostClass, pStmt->m_pIfScope);
		if (pType)
		{
			CDeclarator* pDeclarator = new CDeclarator;
			pDeclarator->m_pType = declarator(pDeclarator, pType, pInnermostClass, pStmt->m_pIfScope);
			if (pDeclarator->m_name.length() == 0)
			{
				pPP->jerror("Expected declarator");
			}
			EatSymbol('=');
			pStmt->m_testexpr = assignment_expression(pInnermostClass, pStmt->m_pIfScope);
#if 0
			pStmt->m_testexpr = Reduce(pStmt->m_testexpr, pStmt->m_pIfScope);
#endif
			pStmt->m_pIfScope->AddDeclarator(new CDeclaratorReference(pDeclarator));
		}
		else
		{
			pStmt->m_testexpr = expression(pInnermostClass, pStmt->m_pIfScope);
#if 0
			pStmt->m_testexpr = Reduce(pStmt->m_testexpr, pStmt->m_pIfScope);
#endif
		//	ExpressionType(pStmt->m_testexpr, pIfScope);
		}

		EatSymbol(')');

		//CScope* pSubScope = new CScope;
		//pSubScope->m_pParentScope = pStmt->m_pIfScope;
		//pSubScope->m_spOffset = pStmt->m_pIfScope->m_stackSize;

		pStmt->m_substmt = new CCompoundStatement;
		pStmt->m_substmt->m_pBlock = new CFunctionBody;
		pStmt->m_substmt->m_pBlock->m_pScope = T_Scope();
		pStmt->m_substmt->m_pBlock->m_pScope->m_pParentScope = pStmt->m_pIfScope;
#if 0
		pStmt->m_substmt->m_pBlock->m_pScope->m_spOffset = pStmt->m_pIfScope->m_spOffset;
#endif

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')	// }
		{
			compound_statement(pGlobal, pInnermostClass, pFunctionDecl, pStmt->m_substmt->m_pBlock, pStmt->m_substmt->m_pBlock->m_pScope);
		}
		else
		{
			CStatement* p = statement(pGlobal, pInnermostClass, pFunctionDecl, pStmt->m_substmt->m_pBlock->m_pScope);
			ASSERT(p);
			pStmt->m_substmt->m_pBlock->m_statements.push_back(p);
		}

#if 0
		int stackSize = pStmt->m_substmt->m_pBlock->m_pScope->m_stackSize;
#endif

		if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_ELSE)
		{
			GetToken();

			pStmt->m_elsestmt = new CCompoundStatement;
			pStmt->m_elsestmt->m_pBlock = new CFunctionBody;//
			pStmt->m_elsestmt->m_pBlock->m_pScope = T_Scope();
			pStmt->m_elsestmt->m_pBlock->m_pScope->m_pParentScope = pStmt->m_pIfScope;
#if 0
			pStmt->m_elsestmt->m_pBlock->m_pScope->m_spOffset = pStmt->m_pIfScope->m_spOffset;
#endif

			if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')	// }
			{
				compound_statement(pGlobal, pInnermostClass, pFunctionDecl, pStmt->m_elsestmt->m_pBlock, pStmt->m_elsestmt->m_pBlock->m_pScope);
			}
			else
			{
				CStatement* p = statement(pGlobal, pInnermostClass, pFunctionDecl, pStmt->m_elsestmt->m_pBlock->m_pScope);
				ASSERT(p);
				pStmt->m_elsestmt->m_pBlock->m_statements.push_back(p);
			}

#if 0
			if (pStmt->m_elsestmt->m_pBlock->m_pScope->m_stackSize > stackSize)
			{
				stackSize = pStmt->m_elsestmt->m_pBlock->m_pScope->m_stackSize;
			}
#endif
		}

#if 0
		ASSERT(stackSize != -1);
		pScope->m_stackSize += stackSize;
#endif

		return pStmt;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_WHILE)
	{
		GetToken();

		CWhileStatement* pStmt = new CWhileStatement;

		EatSymbol('(');
		// TODO, condition()
		pStmt->m_testexpr = expression(pInnermostClass, pScope);
		EatSymbol(')');
#if 0
		pStmt->m_testexpr = Reduce(pStmt->m_testexpr, pScope);
#endif
	//	ExpressionType(pStmt->m_testexpr, pScope);

		pStmt->m_substmt = statement(pGlobal, pInnermostClass, pFunctionDecl, pScope);

		return pStmt;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_DO)
	{
		GetToken();

		statement(pGlobal, pInnermostClass, pFunctionDecl, pScope);

		if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_WHILE)
		{
			GetToken();

			EatSymbol('(');
			// TODO, condition()
			CExpression* pExpr = expression(pInnermostClass, pScope);
			EatSymbol(')');

			EatSymbol(';');
		}
		else
		{
			pPP->jerror("expected 'while (condition);' after 'do' statement");
		}

		ASSERT(0);
		return new CStatement;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_FOR)
	{
#if 0
		CForStatement* pStmt = new CForStatement;
#endif

		CScope* pForScope = T_Scope();
		pForScope->m_pParentScope = pScope;

		GetToken();

		EatSymbol('(');

		if (curtok->type != CToken::tok_symbol || curtok->symbol != ';')
		{
			// condition
			Type* pType = type_specifier_seq(pInnermostClass, pForScope);
			if (pType)
			{
			//	CScope* pDeclScope;
				CDeclarator* pDeclarator = new CDeclarator;
				pDeclarator->m_pType = declarator(pDeclarator, pType, pInnermostClass, pForScope);
				if (pDeclarator->m_name.length() == 0)
				{
					pPP->jerror("Expected declarator");
				}
				EatSymbol('=');
				/*pStmt->m_testexpr = */assignment_expression(pInnermostClass, pForScope);
				//pStmt->m_testexpr = Reduce(pStmt->m_testexpr, pIfScope);

			//	pIfScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
				pForScope->AddDeclarator(new CDeclaratorReference(pDeclarator));
			}
			else
			{
				/*pStmt->m_pInitExpr =*/ expression(pInnermostClass, pScope);
				//if (pStmt->m_pInitExpr)
				{
#if 0
					ExpressionType(pStmt->m_pExpr, pScope);
#endif
				}
			}
		}
		EatSymbol(';');

		if (curtok->type != CToken::tok_symbol || curtok->symbol != ';')
		{
			CExpression* pConditionExpr = expression(pInnermostClass, pScope);
		}
		EatSymbol(';');
		if (curtok->type != CToken::tok_symbol || curtok->symbol != ')')
		{
			CExpression* pExpr = expression(pInnermostClass, pScope);
		}

		EatSymbol(')');

		statement(pGlobal, pInnermostClass, pFunctionDecl, pForScope);
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_SWITCH)
	{
		GetToken();

		CSwitchStatement* pStmt = new CSwitchStatement;

		EatSymbol('(');
		pStmt->m_testexpr = expression(pInnermostClass, pScope);
		EatSymbol(')');

		pStmt->m_statement = statement(pGlobal, pInnermostClass, pFunctionDecl, pScope);

		return pStmt;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_CASE)
	{
		GetToken();

		CCaseStatement* pStmt = new CCaseStatement;
		pStmt->m_type = CStatement::STMT_CASE;

		CExpression* pExpr = constant_expression(pInnermostClass, pScope);
		if (pExpr->tok.type != CToken::tok_integer)
		{
			pPP->jerror("Expected constant integer expression in case");
		}
		pStmt->m_value = pExpr->tok.int32;

		EatSymbol(':');
		pStmt->m_statement = statement(pGlobal, pInnermostClass, pFunctionDecl, pScope);

		return pStmt;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_DEFAULT)
	{
		GetToken();
		EatSymbol(':');

		CLabelStatement* pStmt = new CLabelStatement;
		pStmt->m_type = CStatement::STMT_DEFAULT;

		pStmt->m_statement = statement(pGlobal, pInnermostClass, pFunctionDecl, pScope);

		return pStmt;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_BREAK)
	{
		GetToken();
		EatSymbol(';');

		CStatement* s = new CStatement;
		s->m_type = CStatement::STMT_BREAK;

		return s;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_CONTINUE)
	{
		GetToken();
		EatSymbol(';');
		return new CStatement;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_GOTO)
	{
		GetToken();
		if (curtok->type != CToken::tok_ident)
		{
			pPP->jerror("Expected identifier");
		}
		GetToken();

		EatSymbol(';');
		return new CStatement;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW___ASM)
	{
		GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')	// } block
		{
			GetToken();

			// {
			if (curtok->type != CToken::tok_symbol || curtok->symbol != '}')
			{
				while (!pPP->_eof())
				{
					// {
					if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
					{
						break;
					}
					GetToken();
				}
			}

			// {
			EatSymbol('}');
		}
		else
		{
			while (!pPP->_eof())
			{
				if (curtok->type == CToken::tok_keyword)
				{
					break;
				}

				// {
				if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
				{
					break;
				}

				GetToken();
			}
		}
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')	// }
	{
		CCompoundStatement* pStmt = new CCompoundStatement;
		pStmt->m_pBlock = new CFunctionBody;
		pStmt->m_pBlock->m_pScope = new CScope;
		pStmt->m_pBlock->m_pScope->m_pParentScope = pScope;

		compound_statement(pGlobal, pInnermostClass, pFunctionDecl, pStmt->m_pBlock, pStmt->m_pBlock->m_pScope);

		return pStmt;
	}
	else
	{
		if (curtok->type == CToken::tok_ident)
		{
			CToken tok0 = *curtok;
			GetToken();
			if (curtok->type == CToken::tok_symbol && curtok->symbol == ':')
			{
				GetToken();

				CStatement* pStmt = statement(pGlobal, pInnermostClass, pFunctionDecl, pScope);
				return pStmt;
			}

			m_tokStack.push(*curtok);
			m_tokStack.push(tok0);
			GetToken();
		}

		bool bTypedef;
		CDeclSpecifiers declspecs;
		declspecs.storageClassKW = -1;//storageClassKW;
		if (decl_specifier_seq(pInnermostClass, pScope, declspecs, bTypedef))
		{
			Type* pType = declspecs.m_type.GetType(this);

			if (curtok->type == CToken::tok_symbol && curtok->symbol == ';')
			{
				GetToken();
				if (pType)
				{
					Type* pType2 = pType->GetType();

					if (pType2->m_type != type_class && pType2->m_type != type_enum)
					{
						pPP->jwarn("ignored when no variable is declared");
					}
				}
			}
			else
			{
				CCompoundStatement* pCompoundStmt = new CCompoundStatement;
				pCompoundStmt->m_pBlock = new CFunctionBody;
				pCompoundStmt->m_pBlock->m_pScope = pScope;

				while (!pPP->_eof())
				{
					CDeclarator* pDeclarator = new CDeclarator;
					pDeclarator->m_pType = declarator(pDeclarator, pType, pInnermostClass, pScope);
					if (pDeclarator->m_name.length() == 0)
					{
						pPP->jerror("expected declarator");
					}
					else if (pDeclarator->m_pType == NULL)
					{
						pPP->jerror("declarator must have a type");
					}
					else
					{
						if (pDeclarator->m_pType->GetType()->m_type == type_function)
						{
							pDeclarator->m_pType->GetType()->m_pFunction->m_funcspec = declspecs.functionSpecifierKW;

							/*
							if (curtok->type == CToken::tok_symbol && curtok->symbol == ':')	// ctor-initializer
							{
								GetToken();
								printf("");
							}
							*/
						}

						pDeclarator->m_linkage = -1;//linkage;
						pDeclarator->m_storageClassKW = declspecs.storageClassKW;

						if (bTypedef)
						{
							typedef_declarator(pDeclarator, pScope);
						}
						else
						{
							/*
							if (pTemplate)
							{
								//ASSERT(pTemplate == NULL);	// TODO
		#if 0	// ???
								pPP->jerror("Function template not yet supported");
		#endif
							}
							*/

							BOOL bFunctionBody = nontypedef_declarator(pDeclarator, pInnermostClass, pScope/*pDeclScope*/);

							if (bFunctionBody)
							{
								pPP->jerror("local functions not allowed");
								return NULL;//TRUE;
							}

							if (pDeclarator->m_pInitializerExpr != NULL)
							{
								initialize(A_Ident(pDeclarator->m_name.c_str()), pDeclarator->m_pInitializerExpr, pDeclarator->m_pType, pCompoundStmt);
							}
							else
							//if (pDeclarator->m_name == "c")
							{
								if (pDeclarator->m_pType->GetType()->m_type == type_class)
								{
									// call constructor
									CClass* pClass = pDeclarator->m_pType->GetType()->m_pClass;

									CDeclaratorReference* pRef = pClass->m_pScope->GetDeclarator(pClass->m_name.c_str());
									if (pRef)
									{
										CDeclarator* pCtor = pRef->m_pDeclarator;

										CExpressionStatement* pStmt = new CExpressionStatement;
										pStmt->m_pExpr = new CExpression;
										pStmt->m_pExpr->tok.type = CToken::tok_symbol;
										pStmt->m_pExpr->tok.symbol = '(';

										// classname::ctor()
										{
											pStmt->m_pExpr->left = new CExpression;
											pStmt->m_pExpr->left->tok.type = CToken::tok_symbol;
											pStmt->m_pExpr->left->tok.symbol = '::';

											pStmt->m_pExpr->left->left = new CExpression;
											pStmt->m_pExpr->left->left->tok.type = CToken::tok_ident;
											pStmt->m_pExpr->left->left->tok.ident = strdup(pClass->m_name.c_str());

											pStmt->m_pExpr->left->right = new CExpression;
											pStmt->m_pExpr->left->right->tok.type = CToken::tok_ident;
											pStmt->m_pExpr->left->right->tok.ident = strdup(pCtor->m_name.c_str());
										}

									// 'this' on stack
										{
											pStmt->m_pExpr->right = new CExpression;
											pStmt->m_pExpr->right->left = new CExpression;
											pStmt->m_pExpr->right->left->tok.type = CToken::tok_symbol;
											pStmt->m_pExpr->right->left->tok.symbol = (DWORD)'&'|('U'<<8);

											pStmt->m_pExpr->right->left->right = new CExpression;
											pStmt->m_pExpr->right->left->right = new CExpression;
											pStmt->m_pExpr->right->left->right->tok.type = CToken::tok_ident;
											pStmt->m_pExpr->right->left->right->tok.ident = strdup(pDeclarator->m_name.c_str());
										}
#if 0
										pStmt->m_pExpr = Reduce(pStmt->m_pExpr, pScope);
#endif
										//return pStmt;
										pCompoundStmt->m_pBlock->m_statements.push_back(pStmt);
									}
								}
							}

							if (	pDeclarator->m_storageClassKW != KW_EXTERN &&
									pDeclarator->m_pType->GetType()->m_type != type_function)
							{
#if 0
								pDeclarator->m_spOffset = pScope->m_stackSize;
								if (pDeclarator->m_pType)
								{
									ULONG _sizeof = pDeclarator->m_pType->get_sizeof();
									ASSERT(_sizeof >= 0);
									// word-align
									if (_sizeof >= 2)
									{
										pDeclarator->m_spOffset = ((pDeclarator->m_spOffset+1)/2)*2;
									//	pDeclarator->m_spOffset = (pDeclarator->m_spOffset+1)~1;
									}
									/*
									else if (_sizeof == 4)
									{
										pDeclarator->m_spOffset = ((pDeclarator->m_spOffset+3)/4)*4;
									}
									else// if (_sizeof == 8)
									{
										pDeclarator->m_spOffset = ((pDeclarator->m_spOffset+7)/8)*8;
									}
									*/

									pScope->m_stackSize = pDeclarator->m_spOffset + _sizeof;
								}
#endif
							}
						}
					}

					/*
					if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
					{
						GetToken();
						printf("");
						assignment_expression(pInnermostClass, pScope);
					}
					*/

					if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
					{
						GetToken();
						continue;
					}
					break;
				}
				EatSymbol(';');

				/*
				if (!declarator(pFunction->m_pDeclarator, pScope))
				{
				}

				else
				{
					pGlobal->m_declarations.push_back(pFunction);
				}
				*/

				return pCompoundStmt;
			}

			return NULL;
		}
		else
		{

#if 0
		// TODO function_definition isn't allowed here
		if (simple_declaration_or_function_definition(pGlobal, pInnermostClass, pScope, -1/*linkage*/, -1/*storageClassKW*/, NULL/*pTemplate*/))
		{
			return NULL;//new CStatement;
		}
		else
		{
#endif
			CExpressionStatement* pStmt = new CExpressionStatement;
			if (curtok->type != CToken::tok_symbol || curtok->symbol != ';')
			{
				pStmt->m_pExpr = expression(pInnermostClass, pScope);

				if (pStmt->m_pExpr)
				{
#if 0
					pStmt->m_pExpr = Reduce(pStmt->m_pExpr, pScope);
#endif
					if (pInnermostClass)
						pInnermostClass->m_pIDExprs->m_v.push_back(pStmt->m_pExpr);
					else
						;//ExpressionType(pStmt->m_pExpr, pScope);
				}
			}

			EatSymbol(';');

			return pStmt;
		}
	}

	return NULL;
}

/*
statement-seq:
	statement
	statement-seq statement
*/
void CCPPCompiler::statement_seq(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CFunctionBody* pFunctionBody, CScope* pScope)
{
	while (!pPP->_eof())
	{
		// {
		if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
		{
			break;
		}

		CStatement* pStmt = statement(pGlobal, pInnermostClass, pFunctionDecl, pScope);
	//	if (pStmt == NULL)
	//		break;

		if (pStmt)
			pFunctionBody->m_statements.push_back(pStmt);
	}
}

/*
compound-statement:
	{ statement-seqopt }
*/
void CCPPCompiler::compound_statement(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CFunctionBody* pFunctionBody, CScope* pScope)
{
	EatSymbol('{');
	statement_seq(pGlobal, pInnermostClass, pFunctionDecl, pFunctionBody, pScope);
	EatSymbol('}');
}

CCompoundStatement* CCPPCompiler::compound_statement(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CScope* pScope)
{
	CCompoundStatement* pStmt = new CCompoundStatement;
	pStmt->m_pBlock = new CFunctionBody;
	pStmt->m_pBlock->m_pScope = T_Scope();
	pStmt->m_pBlock->m_pScope->m_pParentScope = pScope;

	EatSymbol('{');
	statement_seq(pGlobal, pInnermostClass, pFunctionDecl, pStmt->m_pBlock, pStmt->m_pBlock->m_pScope->m_pParentScope);
	EatSymbol('}');

	return pStmt;
}

Type* CCPPCompiler::ReplaceType(std::vector<Type*>& ArgTypes, Type* pType)
{
	ASSERT(pType);

	if (pType->m_type == type_typedef)
		return ReplaceType(ArgTypes, pType->m_pDeclarator->m_pType);

	if (pType->m_type == type_cv)
	{
		return ReplaceType(ArgTypes, pType->m_pPointerTo);
		printf("");
	}

	if (pType->m_type == type_pointer)
	{
		Type* pType2 = new Type(type_pointer);
		pType2->m_sizeof = pType->m_sizeof;

		pType2->m_pPointerTo = ReplaceType(ArgTypes, pType->m_pPointerTo);

		return pType2;
	}
	else if (pType->m_type == type_function)
	{
		Type* pType2 = new Type(type_function);
		pType2->m_sizeof = pType->m_sizeof;

		pType2->m_pFunction = new CFunction;
		pType2->m_pFunction->m_pReturnType = ReplaceType(ArgTypes, pType->m_pFunction->m_pReturnType);

	// TODO, parameters

		return pType2;
	}
	else if (pType->m_type == type_templateinst)
	{
		return InstantiateTemplateType(ArgTypes, pType);
	}
	else
	{
		if (pType->m_type == type_class)
		{
			if (pType->m_pNamedType->m_name == "T")
			{
				return ArgTypes[0];
			}
		}

		return pType;
	}
}

/*
storage-class-specifier:
	auto
	register
	static
	extern
	mutable
*/


/*
function-specifier:
	inline
	virtual
	explicit
*/

/*
simple-type-specifier:
	::opt nested-name-specifieropt type-name
	::opt nested-name-specifier template template-id
	char
	wchar_t
	bool
	short
	int
	long
	signed
	unsigned
	float
	double
	void
*/

BOOL CCPPCompiler::simple_type_specifier(TypeSpecifiers& typespecs, CScope* pScope)
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->flags & kwfSimpleTypeSpecifier)
	{
		if (curtok->pkw->n == KW_SHORT)
		{
			if (typespecs.m_size == 1)
			{
				pPP->jerror("short already specified");
			}
			else if (typespecs.m_size != 0)
			{
				pPP->jerror("size previously specified as short");
			}
			else
			{
				typespecs.m_size = (curtok->pkw->n == KW_SHORT)? 1: 2;
				typespecs.m_bSimpleTypeSpecified = true;
			}
		}
		else if (curtok->pkw->n == KW_LONG)
		{
			if (typespecs.m_size == 1)
			{
				pPP->jerror("size previously specified as short");
			}
			else if (typespecs.m_size == 2)
			{
				typespecs.m_size = 3;	// long long
			}
			else if (typespecs.m_size == 3)
			{
				pPP->jerror("long long already specified");
			}
			else
			{
				typespecs.m_size = 2;
				typespecs.m_bSimpleTypeSpecified = true;
			}
		}
		else if (curtok->pkw->n == KW_SIGNED || curtok->pkw->n == KW_UNSIGNED)
		{
			if (curtok->pkw->n == KW_SIGNED)
			{
				if (typespecs.m_sign == 1)
					pPP->jerror("'signed' already specified");
				else if (typespecs.m_sign == -1)
					pPP->jerror("'signed' unsigned already specified");
				else
					typespecs.m_sign = 1;
			}
			else
			{
				if (typespecs.m_sign == -1)
					pPP->jerror("'unsigned' already specified");
				else if (typespecs.m_sign == 1)
					pPP->jerror("'unsigned' signed already specified");
				else
					typespecs.m_sign = -1;
			}

			typespecs.m_bSimpleTypeSpecified = true;
		}
		else
		{
			switch (curtok->pkw->n)
			{
			case KW_VOID:
			case KW_BOOL:
			case KW_CHAR:
			case KW_WCHAR_T:
			case KW_INT:
			case KW___INT64:
			case KW_FLOAT:
			case KW_DOUBLE:
				{
					if (typespecs.m_typeKW != -1)
					{
						pPP->jerror("Type already specified");
					}

					typespecs.m_typeKW = curtok->pkw->n;
					typespecs.m_bSimpleTypeSpecified = true;
				}
				break;

			default:
				ASSERT(0);
			}
		}

		GetToken();
		return 2;	// We recognized it and we may recognize more, so keep calling us
	}
	else if (curtok->type == CToken::tok_ident)
	{
		/*
		if (typespecs.pType)
		{
			return FALSE;
		}
		*/

		//ASSERT(gSave == NULL);
		//gSave = new CSave;
		//gSave->m_tokStack.push(*curtok);
		int save = m_tokStack2.size();

		CExpression* pNestedNameExpr = nested_name_specifier(pScope);

		if (pNestedNameExpr->tok.type == CToken::tok_symbol && pNestedNameExpr->tok.symbol == '::')
		{
			CScope* pScope2 = GetNestedScope(pScope, pNestedNameExpr->left);
			if (pScope2 == NULL)
			{
				// ??
				//Restore(save);
				return 0;
			}
			else
			{
			//	CScope* pScope2 = GetScope(pGlobal->m_pNamespace->m_pScope, pNestedNameExpr->left);
				if (pScope2->m_pClass && pNestedNameExpr->right && pScope2->m_pClass->m_name == pNestedNameExpr->right->tok.ident)
				{
					Restore(save);
					typespecs.m_pType = new Type();
					return 1;
				}
				else if (curtok->type == CToken::tok_symbol && curtok->symbol == '~')
				{
					Restore(save);
					typespecs.m_pType = new Type();
					return 1;
				}
			}
		}

		//if (typespecs.m_pType == NULL)
		if (!typespecs.m_bSimpleTypeSpecified)	// if a simple keyword specifier has
															// already been specified, such as short
															// signed etc. a complex type or a typedef
															// cannot also be specified
		{
			ASSERT(typespecs.m_pType == NULL);

			//ASSERT(0);
		//	MessageBeep(-1);
		//	std::string ident = curtok->ident;
#if 0
			if (pNestedNameExpr->m_pType)	// Had this
#endif
				if (0)
			{
#if 0
				pNestedNameExpr->m_pType->m_pClass->m_pTemplate;

				CTemplate* pTemplate = pNestedNameExpr->tok.type == CToken::tok_ident? pScope->GetTemplate(pNestedNameExpr->tok.ident) : NULL;
				//if (pTemplate)//templatei != pScope->m_templates.end())
				ASSERT(pTemplate);
				
				std::string ident = pNestedNameExpr->tok.ident;

				// TODO
				ASSERT(pNestedNameExpr->m_pType);
#endif

				ASSERT(0);
#if 0
				typespecs.m_pType = pNestedNameExpr->m_pType;
#endif

#if 0	// ???
				typespecs.m_pType->m_pDeclarator->m_pType = pTemplate->m_pType;
#endif
				return 1;	// We recognized this one, but don't call us again

#if 0
				//templatemap::iterator templatei;
				if (curtok->type == CToken::tok_symbol && curtok->symbol == '<')
				{
					Type* pType = pTemplate->m_pType;

					GetToken();
					bInTemplateArg = TRUE;

				//	std::vector<Type*> ArgTypes;

					Type* pType2 = new Type(type_templateinst);
					pType2->m_pDeclarator = new CDeclarator;
					pType2->m_pDeclarator->m_name = pType->m_pNamedType->m_name;
					pType2->m_pDeclarator->m_name += "<>";
					pType2->m_pDeclarator->m_pType = pType;

					while (!pPP->_eof())
					{
						Type* pArgType = type_id(NULL, pScope);

					//	Type* pArgType = type_specifier_seq(NULL, pScope);
						if (pArgType == NULL)
						{
							CExpression* pExpr = assignment_expression(NULL, pScope);
							if (pExpr == NULL)
							{
								char msg[512];
								if (curtok->type == CToken::tok_ident)
								{
									sprintf(msg, "Expected type '%s'", curtok->ident);
								}
								else if (curtok->type == CToken::tok_symbol)
								{
									sprintf(msg, "Expected type '%c'", (char)curtok->symbol);
								}
								else
								{
									sprintf(msg, "Expected type");
								}

								pPP->jerror(msg);
							//	GetToken();
							}
						}

						if (pArgType)
						{
							pType2->m_ArgTypes.push_back(pArgType);
						}

						if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
						{
							GetToken();
							continue;
						}
						break;
					}

					EatSymbol('>');
					bInTemplateArg = FALSE;

					typespecs.m_pType = pType2;
					return 1;	// We recognized this one, but don't call us again
				//	pType = pType2;
				}
				else
				{
				//	pPP->jerror("Expected '<'");
				//	ASSERT(0);
					Type* pType = pScope->GetType(ident.c_str());
					if (pType)
					{
					//	GetToken();
						typespecs.m_pType = pType;
						return 1;	// We recognized this one, but don't call us again
					}
					else
						ASSERT(0);
				}
#endif
			}
			else
			{
				CDeclaratorReference* pDeclaratorRef = pNestedNameExpr->tok.type == CToken::tok_ident? pScope->GetDeclarator(pNestedNameExpr->tok.ident): NULL;

				/*
				if (!strcmp(curtok->ident, "CComPtr"))
				{
					printf("");
				}
				*/

				if (pDeclaratorRef == NULL || pDeclaratorRef->m_pDeclarator->m_pType->GetType()->m_type == type_function/*m_pFunction != NULL*/)	// Rule out this one, TODO, could improve the order of things here ??
				{
					Type* pType = NULL;

					if (pNestedNameExpr && pNestedNameExpr->tok.type == CToken::tok_ident)
					{
						pType = pScope->GetType(pNestedNameExpr->tok.ident);
					}
					else
					{
						CScope* pScope2 = GetNestedScope(pScope, pNestedNameExpr->left);
						if (pScope2)
						{
							if (pNestedNameExpr->right)
							{
								pType = pScope2->GetType(pNestedNameExpr->right->tok.ident);
							}
						}
					}

					if (pType)
					{
#if 0
						CToken tok0 = *curtok;
						GetToken();
						if (curtok->type == CToken::tok_symbol && curtok->symbol == '::')
						{
							m_tokStack.push(*curtok);
							m_tokStack.push(tok0);
							GetToken();
#if 0	// ??hm
							typespecs.m_pType = new Type(999);	// constructor
							return 1;
#endif
							return 0;
						}
#endif
					//	delete gSave;
					//	gSave = NULL;

						typespecs.m_pType = pType;
						return 1;	// We recognized this one, but don't call us again
					}
				}
				else
				{
					printf("");
				}

				Restore(save);
			}
		}
		else
		{
		//	delete gSave;
		//	gSave = NULL;
			Restore(save);
			printf("");
		}
	}

	return 0;	// we didn't recognize it
}

/*
class-head:
	class-key identifieropt base-clauseopt
	class-key nested-name-specifier identifier base-clauseopt
	class-key nested-name-specifieropt template-id base-clauseopt
*/

/*
class-specifier:
	class-head { member-specificationopt }
*/

/*
base-clause:
	: base-specifier-list

base-specifier-list:
	base-specifier
	base-specifier-list , base-specifier

base-specifier:
	::opt nested-name-specifieropt class-name
	virtual access-specifieropt ::opt nested-name-specifieropt class-name
	access-specifier virtualopt ::opt nested-name-specifieropt class-name
*/

void CCPPCompiler::base_specifier_list(CClass* pClass, CScope* pScope)
{
	while (!pPP->_eof())
	{
		bool bVirtualBase = false;

		if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_VIRTUAL)
		{
			GetToken();
			bVirtualBase = true;
		}

		if (curtok->type == CToken::tok_keyword && curtok->pkw->flags & kwAccessSpecifier)
		{
			GetToken();
		}

		if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_VIRTUAL)
		{
			GetToken();
			bVirtualBase = true;
		}

		if (curtok->type == CToken::tok_ident && !strcmp(curtok->ident, "CSimpleArray"))
		{
			printf("");
		}
		/*
		if (curtok->type != CToken::tok_ident)
		{
			pPP->jerror("expected base identifier");
		}
		*/

		CExpression* nested_name = nested_name_specifier(pScope);

		if (nested_name && nested_name->tok.type == CToken::tok_ident)// && !strcmp(nested_name->tok.ident, "CSimpleArray"))
		{
			Type* pType = pScope->GetType(nested_name->tok.ident);

			//CTemplate* pTemplate = pScope->GetTemplate(nested_name->tok.ident);

			if (pType)
			{
				if (pType->m_type == type_class)//m_pClass)
				{
					ASSERT(pType->m_pClass);
					CBaseClass baseclass;
					baseclass.m_pClass = pType->m_pClass;
					baseclass.m_offset = pClass->get_sizeof();
					pClass->m_sizeof += baseclass.m_pClass->m_sizeof;

					pClass->m_bases.push_back(baseclass);
				}
				else
				{
					pPP->jerror("cannot derive from non-class");
				}
			}
		}
		else
		{
			CScope* pScope2 = GetScope(pGlobal->m_pNamespace->m_pScope, nested_name);

			if (pScope2)
			{
				if (pScope2->m_pClass)
				{
					CBaseClass baseclass;
					baseclass.m_pClass = pScope->m_pClass;
					pClass->m_bases.push_back(baseclass);
				//	printf("\n");
				}
				else
				{
					char msg[256];
					sprintf(msg, "not a class");
					pPP->jerror(msg);
				}
			}
			else
			{
				printf("");
			}
		}

	//	typemap::iterator typei = pGlobal->m_types.find(curtok->ident);
	//	if (typei == 

	//	GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
		{
			GetToken();
			continue;
		}
		break;
	}
}

/*
enum-name:
	identifier

enum-specifier:
	enum identifieropt { enumerator-listopt }

enumerator-list:
	enumerator-definition
	enumerator-list , enumerator-definition

enumerator-definition:
	enumerator
	enumerator = constant-expression

enumerator:
	identifier
*/

CExpression* /*CCPPCompiler::*/ Reduce2(CExpression* pExpr, CScope* pScope)
{
	if (pExpr->tok.type == CToken::tok_ident)
	{
		CExpression* pExpr2 = pScope->GetIdentValue(pExpr->tok.ident, pScope/*pExpr->m_pScope*/);
		if (pExpr2)
		{
			delete pExpr;
			pExpr = pExpr2;
		}
	}
#if 0
	else if (pExpr->tok.symbol == (DWORD)'('|('U'<<8))	// cast
	{
		ASSERT(pExpr->left == NULL);
		ASSERT(pExpr->right != NULL);

		pExpr->right = Reduce2(pExpr->right);

		pExpr->
	}
#endif
	else if (pExpr->tok.symbol == ('-'|('U'<<8)) ||
				pExpr->tok.symbol == ('+'|('U'<<8)) ||
				pExpr->tok.symbol == ('~'|('U'<<8)))
	{
		if (pExpr->right->tok.type == CToken::tok_integer)
		{
			switch (pExpr->tok.symbol)
			{
			case ('-'|('U'<<8)):
				ASSERT(0);
				break;

			case ('+'|('U'<<8)):
				ASSERT(0);
				break;

			case ('~'|('U'<<8)):
				ASSERT(0);
				break;
			}
		}
	}
	/*
	else if (pExpr->tok.type == CToken::tok_symbol && pExpr->tok.symbol == ',')
	{
	}
	*/
	else if (pExpr->tok.type == CToken::tok_symbol && (
				pExpr->tok.symbol == '&&' ||
				pExpr->tok.symbol == '||' ||
				pExpr->tok.symbol == '==' ||
				pExpr->tok.symbol == '!=' ||
				pExpr->tok.symbol == '>' ||
				pExpr->tok.symbol == '<' ||
				pExpr->tok.symbol == '>=' ||
				pExpr->tok.symbol == '<=' ||
				pExpr->tok.symbol == '+' ||
				pExpr->tok.symbol == '-' ||
				pExpr->tok.symbol == '*' ||
				pExpr->tok.symbol == '/' ||
				pExpr->tok.symbol == '|' ||
				pExpr->tok.symbol == '&' ||
				pExpr->tok.symbol == '^' ||
				pExpr->tok.symbol == '>>' ||
				pExpr->tok.symbol == '<<')
				)
	{
		if (pExpr->left)
		{
			pExpr->left = Reduce2(pExpr->left, pScope);

			if (pExpr->right)
			{
				pExpr->right = Reduce2(pExpr->right, pScope);

				if (pExpr->left->tok.type == CToken::tok_integer &&
					pExpr->right->tok.type == CToken::tok_integer)
				{
					switch (pExpr->tok.symbol)
					{
					case '&&':
						pExpr->tok.int32 = pExpr->left->tok.int32 && pExpr->right->tok.int32;
						break;

					case '||':
						pExpr->tok.int32 = pExpr->left->tok.int32 || pExpr->right->tok.int32;
						break;

					case '==':
						pExpr->tok.int32 = pExpr->left->tok.int32 == pExpr->right->tok.int32;
						break;

					case '!=':
						pExpr->tok.int32 = pExpr->left->tok.int32 != pExpr->right->tok.int32;
						break;

					case '>':
						pExpr->tok.int32 = pExpr->left->tok.int32 > pExpr->right->tok.int32;
						break;

					case '<':
						pExpr->tok.int32 = pExpr->left->tok.int32 < pExpr->right->tok.int32;
						break;

					case '>=':
						pExpr->tok.int32 = pExpr->left->tok.int32 >= pExpr->right->tok.int32;
						break;

					case '<=':
						pExpr->tok.int32 = pExpr->left->tok.int32 <= pExpr->right->tok.int32;
						break;
					
					case '+':
						pExpr->tok.int32 = pExpr->left->tok.int32 + pExpr->right->tok.int32;
						break;

					case '-':
						pExpr->tok.int32 = pExpr->left->tok.int32 - pExpr->right->tok.int32;
						break;

					case '*':
						pExpr->tok.int32 = pExpr->left->tok.int32 * pExpr->right->tok.int32;
						break;

					case '/':
						pExpr->tok.int32 = pExpr->left->tok.int32 / pExpr->right->tok.int32;
						break;

					case '|':
						pExpr->tok.int32 = pExpr->left->tok.int32 | pExpr->right->tok.int32;
						break;

					case '&':
						pExpr->tok.int32 = pExpr->left->tok.int32 & pExpr->right->tok.int32;
						break;

					case '^':
						pExpr->tok.int32 = pExpr->left->tok.int32 ^ pExpr->right->tok.int32;
						break;

					case '>>':
						pExpr->tok.int32 = pExpr->left->tok.int32 >> pExpr->right->tok.int32;
						break;

					case '<<':
						pExpr->tok.int32 = pExpr->left->tok.int32 << pExpr->right->tok.int32;
						break;
					}

					pExpr->tok.type = CToken::tok_integer;
#if 0
					delete pExpr->left;
					delete pExpr->right;
#endif
				}
			}
		}
	}
	else
	{
		if (pExpr->left)
		{
			pExpr->left = Reduce2(pExpr->left, pScope);
		}

		if (pExpr->right)
		{
			pExpr->right = Reduce2(pExpr->right, pScope);
		}
	}

	return pExpr;
}

Type* CCPPCompiler::InstantiateTemplateType(std::vector<Type*>& ArgTypes, Type* pType)
{
	Type* pType2 = new Type(type_class);
	//pType2->m_name = pType->m_name;
	pType2->m_pClass = new CClass(/*pType2*/);
	pType2->m_pClass->m_name = pType->m_pNamedType->m_name;
	pType2->m_pClass->m_kwType = pType->m_pDeclarator->m_pType->m_pClass->m_kwType;
	{
		/*
		if (pType2->m_name == "_NoAddRefReleaseOnCComPtr")
		{
			printf("");
		}

		if (pType2->m_name == "CComPtr")
		{
			printf("");
		}
		*/

		{
			for (int i = 0; i < pType->m_pDeclarator->m_pType->m_pClass->m_bases.size(); i++)
			{
				CClass* pClass = pType->m_pDeclarator->m_pType->m_pClass->m_bases[i].m_pClass;
				//printf("");
				
				ASSERT(0);
				Type* pClassType = NULL;
#if 0
				pClassType = ReplaceType(ArgTypes, pClass->m_pType);
#endif
				ASSERT(pClassType->GetType()->m_type == type_class);

				CBaseClass baseclass;
				baseclass.m_pClass = pClassType->GetType()->m_pClass;
				pType2->m_pClass->m_bases.push_back(baseclass);
				//pDeclarator2->m_pType = 
			}
		}

		for (int i = 0; i < pType->m_pDeclarator->m_pType->m_pClass->m_pScope->m_orderedDecls.size(); i++)//m_members.size(); i++)
		{
			ASSERT(0);
#if 0
			CDeclaratorReference* pDeclaratorRef = pType->m_pDeclarator->m_pType->m_pClass->m_pScope->m_orderedDecls[i];

			CDeclarator* pDeclarator2 = new CDeclarator;
			pDeclarator2->m_name = pDeclarator->m_name;

			pDeclarator2->m_pType = ReplaceType(ArgTypes, pDeclarator->m_pType);

#if 0
			if (pDeclarator->m_pFunction)
			{
				pDeclarator2->m_pFunction = new CFunction;
			}
#endif

#if 0
			CMember* pMember = pType->m_pClass->m_members[i];

			CMember* pMember2 = new CMember;
			pMember2->m_pDeclarator = new CDeclarator;
			pMember2->m_pDeclarator->m_name = pMember->m_pDeclarator->m_name;

			pMember2->m_pDeclarator->m_pType = ReplaceType(ArgTypes, pMember->m_pDeclarator->m_pType);
#endif

			pType2->m_pClass->m_pScope->AddDeclarator(pDeclarator2);//m_members.push_back(pMember2);
#endif
		}
	}

	return pType2;
}


void CCPPCompiler::enumerator_definition(CClass* pInnermostClass, CScope* pScope, int& counter)
{
	if (curtok->type != CToken::tok_ident)
	{
		pPP->jerror("expected enumerator identifier");
	}
	std::string ident = curtok->ident;
	GetToken();

	if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
	{
		GetToken();

		CExpression* pExpr = constant_expression(pInnermostClass, pScope);
		if (pExpr)
		{
			pExpr = Reduce2(pExpr, pScope);

			if (pExpr->tok.type == CToken::tok_integer)
			{
				counter = pExpr->tok.int32;
				pScope->m_identvalues.insert(identvaluemap::value_type(ident, counter));

				counter++;
			}
			else
			{
				pPP->jerror("enumerator expression must be a constant integer expression");
			}
		}
		else
		{
			pPP->jerror("expected constant expression on right side of '='");
		}
	}
	else
	{
		pScope->m_identvalues.insert(identvaluemap::value_type(ident, counter));
		counter++;
	}
}

void CCPPCompiler::enumerator_list(CClass* pNamespace, CScope* pScope)
{
	int counter = 0;

	while (!pPP->_eof())
	{
		enumerator_definition(pNamespace, pScope, counter);

		if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
		{
			GetToken();
			if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
			{
				break;
			}

			continue;
		}
		break;
	}
}

/*
type-specifier:
	simple-type-specifier
	class-specifier
		class-head { member-specificationopt }
	enum-specifier
	elaborated-type-specifier
		class-key ::opt nested-name-specifieropt identifier
		class-key ::opt nested-name-specifieropt templateopt template-id
		enum ::opt nested-name-specifieropt identifier
		typename ::opt nested-name-specifier identifier
		typename ::opt nested-name-specifier templateopt template-id
	cv-qualifier
*/
BOOL CCPPCompiler::type_specifier(TypeSpecifiers& typespecs, CClass* pInnermostClass, CScope* pScope)
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_TYPENAME)
	{
		GetToken();

		typespecs.m_pType = new Type(type_typename);
		typespecs.m_pType->m_pNestedNameSpecifier = nested_name_specifier(pScope);

		return 1;
	}
	else if (curtok->type == CToken::tok_keyword && (
		curtok->pkw->n == KW_CLASS ||
		curtok->pkw->n == KW_STRUCT ||
		curtok->pkw->n == KW_UNION))
	{
		int kwType = curtok->pkw->n;

		// Either a class-specifier or elaborated-type-specifier
		GetToken();

		std::string name;
		if (curtok->type == CToken::tok_ident)
		{
			name = curtok->ident;
			GetToken();
		}

		//printf("class %s\n", name.c_str());

		Type* pClassType = NULL;

		if (name.length())
		{
			/*
			if (name == "Window")
			{
				MessageBeep(-1);
			}
			*/
#if 0
			CTemplate* pTemplate = pScope->GetTemplate(name.c_str());
			if (pTemplate)
			{
				// class template specialization
				EatSymbol('<');
				while (!pPP->_eof())
				{
					if (curtok->type == CToken::tok_symbol && curtok->symbol == '>')
					{
						break;
					}
					GetToken();
				}
				EatSymbol('>');

				// ???
				pClassType = new Type(type_class);

				pClassType->m_pClass = new CClass(pClassType);
				pClassType->m_pClass->m_pScope->m_pParentScope = pScope;

				for (int i = 0; i < pTemplate->m_parameters.size(); i++)
				{
					CTemplateParameter* pTemplateParameter = pTemplate->m_parameters[i];

					if (pTemplateParameter->m_type == CTemplateParameter::Type_type)
					{
						pClassType->m_pClass->m_pScope->AddType(this, pTemplateParameter->m_pType);
					}
				}

				pClassType->m_pClass->m_kwType = kwType;
				pClassType->m_pClass->m_name = name;
				pClassType->m_sizeof = -1;	// Not known yet
			}
			else
#endif
			{
				pClassType = pScope->GetType(name.c_str());
				if (pClassType)
				{
					/*
					if (name == "Window")
					{
						MessageBeep(-1);
					}
					*/

					if (pClassType->m_type != type_class ||	// Already defined as something else than struct/class/union
						pClassType->m_pClass->m_kwType != kwType)	// Already declared as a different type of struct/class/union
					{
						char msg[512];
						sprintf(msg, "'%s' already declared as a different type, first seen :\n%s(%d)", pClassType->m_pNamedType->m_name.c_str(), pClassType->m_pNamedType->m_location.m_filepath.c_str(), pClassType->m_pNamedType->m_location.m_line);
						pPP->jerror(msg);
					}
					else if (pClassType->m_pClass->m_pTemplate != NULL && pScope->m_pTemplate == NULL)
					{
						char msg[512];
						sprintf(msg, "'%s' previously declared as a template class:\n%s(%d)", pClassType->m_pNamedType->m_name.c_str(), pClassType->m_pNamedType->m_location.m_filepath.c_str(), pClassType->m_pNamedType->m_location.m_line);
						pPP->jerror(msg);
					}
					else if (pClassType->m_pClass->m_pTemplate == NULL && pScope->m_pTemplate != NULL)
					{
						char msg[512];
						sprintf(msg, "'%s' previously declared as a non-template class:\n%s(%d)", pClassType->m_pNamedType->m_name.c_str(), pClassType->m_pNamedType->m_location.m_filepath.c_str(), pClassType->m_pNamedType->m_location.m_line);
						pPP->jerror(msg);
					}
				}

				if (pClassType && pClassType->GetType()->m_type == type_class && pClassType->GetType()->m_pClass->m_pTemplate)
				{
					CTemplate* pTemplate = pClassType->GetType()->m_pClass->m_pTemplate;

					// class template specialization
					if (curtok->type == CToken::tok_symbol && curtok->symbol == '<')
					{
						GetToken();

						while (!pPP->_eof())
						{
							if (curtok->type == CToken::tok_symbol && curtok->symbol == '>')
							{
								break;
							}
							GetToken();
						}
						EatSymbol('>');

						// ???
						pClassType = new Type(type_class);

						pClassType->m_pClass = new CClass(/*pClassType*/);
						pClassType->m_pClass->m_pScope->m_pParentScope = pScope;

						for (int i = 0; i < pTemplate->m_parameters.size(); i++)
						{
							CTemplateParameter* pTemplateParameter = pTemplate->m_parameters[i];

							if (pTemplateParameter->m_type == CTemplateParameter::Type_type)
							{
								pClassType->m_pClass->m_pScope->AddType(this, pTemplateParameter->m_pType);
							}
						}

						ASSERT(0);
						//pClassType->m_pClass->m_kwType = kwType;
						pClassType->m_pClass->m_name = name;
						pClassType->m_sizeof = -1;	// Not known yet
					}
				}

				if (pClassType == NULL)
				{
					pClassType = new Type(type_class);
					pClassType->m_pClass = new CClass;

					if (curtok->type == CToken::tok_symbol && curtok->symbol == ';')
					{
						pClassType->m_pClass->m_pScope->m_pParentScope = pScope;
					}
					else	// scope is first non-class
					{
						CScope* p = pScope;
						while (p)
						{
							if (p->m_pClass == NULL)
								break;

							p = p->m_pParentScope;
						}

						ASSERT(p);
						pClassType->m_pClass->m_pScope->m_pParentScope = p;
					}

					ASSERT(0);
					//pClassType->m_pClass->m_kwType = kwType;
					pClassType->m_pClass->m_name = name;
					pClassType->m_sizeof = -1;	// Not known yet

					pClassType->m_pClass->m_pScope->m_pParentScope->AddType(this, pClassType);

					if (pScope->m_pTemplate)
					{
						pClassType->m_pClass->m_pTemplate = pScope->m_pTemplate;
						pScope->m_pTemplate->m_pClass = pClassType->m_pClass;
#if 0
						ASSERT(pScope->m_pTemplate->m_pType->m_pNamedType->m_name.length());
#endif
						pScope->m_pParentScope->AddType(this, pClassType);
#if 0
						pScope->m_pParentScope->m_templates.insert(templatemap::value_type(pScope->m_pTemplate->m_pType->m_pNamedType->m_name, pScope->m_pTemplate));
#endif
					}

				//	pScope->m_types.push_back(pClassType);
				//	pClassType->m_location.m_filepath = pPP->m_pFile->m_filepath;
				//	pClassType->m_location.m_line = pPP->m_pFile->m_line;
				}
			}
		}
		else	// anonymous struct/class/union
		{
			pClassType = new Type(type_class);

			pClassType->m_pClass = new CClass(/*pClassType*/);
			pClassType->m_pClass->m_pScope->m_pParentScope = pScope;
			ASSERT(0);
			//pClassType->m_pClass->m_kwType = kwType;
			pClassType->m_sizeof = -1;	// Not known yet
		}

		BOOL bBaseList = FALSE;

		if ((curtok->type == CToken::tok_symbol && curtok->symbol == ':') ||
			(curtok->type == CToken::tok_symbol && curtok->symbol == '{'))	// }
		{
			ASSERT(pClassType != NULL);

			if (pClassType->m_sizeof != -1)// Already fully declared, not just forward declared
			{
				char msg[512];
				sprintf(msg, "'%s' already declared with a body, first seen :\n%s(%d)", pClassType->m_pNamedType->m_name.c_str(), pClassType->m_pNamedType->m_location.m_filepath.c_str(), pClassType->m_pNamedType->m_location.m_line);
				pPP->jerror(msg);
			}

			pClassType->m_pClass->m_sizeof = 0;

			if (curtok->type == CToken::tok_symbol && curtok->symbol == ':')
			{
				//bBaseList = TRUE;

				GetToken();
				base_specifier_list(pClassType->m_pClass, pScope);

				if (curtok->type != CToken::tok_symbol || curtok->symbol != '{')	// '}'
				{
					pPP->jerror("Expected class body after base specifier list");
				}
			}

			if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')	// '}'
			{

#if 0
				if (/*!bBaseList &&*/ pClassType->m_sizeof != -1)// Already fully declared, not just forward declared
				{
					char msg[512];
					sprintf(msg, "'%s' already declared with a body, first seen :\n%s(%d)", pClassType->m_pNamedType->m_name.c_str(), pClassType->m_pNamedType->m_location.m_filepath.c_str(), pClassType->m_pNamedType->m_location.m_line);
					pPP->jerror(msg);
				}
#endif

				EatSymbol('{');
				member_specification(pClassType->m_pClass, pClassType->m_pClass/*pInnermostClass*/, pClassType->m_pClass->m_pScope);
				EatSymbol('}');

				if (pInnermostClass == NULL)
				{
					pClassType->m_pClass->Evaluate();
	#if 0
					for (int i = 0; i < pClassType->m_pClass->m_pIDExprs->m_v.size(); i++)
					{
						CExpression* pExpr = pClassType->m_pClass->m_pIDExprs->m_v[i];

						ExpressionType(pExpr, pClassType->m_pClass->m_pScope);

	#if 0
						CDeclarator* pDeclarator = pClassType->m_pClass->GetDeclarator(idexpr.m_pExpr->tok.ident);
						if (pDeclarator)
						{
							idexpr.m_pExpr->m_pDeclarator = pDeclarator;
							idexpr.m_pExpr->m_pType = idexpr.m_pExpr->m_pDeclarator->m_pType;
						}
						else
						{
							char msg[512];
							sprintf(msg, "'%s' : undeclared identifier", idexpr.m_pExpr->tok.ident);
							pPP->jerror(msg);
						}
	#endif
					}
	#endif
				}

				//pClassType->m_sizeof = pClassType->m_pClass->m_sizeof;

				bool bVirtualFunction = false;

				declsmap::iterator decli = pClassType->m_pClass->m_pScope->m_decls.begin();

				while (decli != pClassType->m_pClass->m_pScope->m_decls.end())//for (int i = 0; i < pClassType->m_pClass->m_pScope->m_orderedDecls.size(); i++)
				{
					CDeclaratorReference* pDeclaratorRef = (*decli).second;//pClassType->m_pClass->m_pScope->m_orderedDecls[i];

					Type* pType = pDeclaratorRef->m_pDeclarator->m_pType->GetType();
					if (pType->m_type == type_function && pType->m_pFunction->m_funcspec == KW_VIRTUAL)
					{
						bVirtualFunction = true;
						break;
					}

					decli++;
				}

				if (bVirtualFunction)
				{
					// Make virtual table

				}
			}
		}
		else
		{
			if (name.length())
			{
				ASSERT(pClassType != NULL);
			//	Type* pType = pScope->GetType(name.c_str());
			}
		}

		typespecs.m_pType = pClassType;
		return 1;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_ENUM)
	{
		GetToken();

		std::string name;
		if (curtok->type == CToken::tok_ident)
		{
			name = curtok->ident;
			GetToken();
		}

		Type* pType = NULL;

		if (name.length())
		{
			pType = pScope->GetType(name.c_str());
			if (pType)
			{
				pPP->jerror("enum already declared");
			}
		}
		
		pType = new Type(type_enum);
		//pType->m_type = 4;	// enum
		pType->m_sizeof = 4;

		pType->m_pNamedType = new CNamedType;

		if (name.length())
		{
			pType->m_pNamedType->m_name = name;
			//pType->m_name = name;
			pScope->AddType(this, pType);
		//	pScope->m_types.push_back(pType);
		}

		EatSymbol('{');
		enumerator_list(pInnermostClass, pScope);
		EatSymbol('}');

		typespecs.m_pType = pType;
		return 1;
	}
	else if (curtok->type == CToken::tok_keyword &&
		(curtok->pkw->n == KW_CONST))
	{
		GetToken();

		if (typespecs.m_bConst)
			pPP->jerror("const already specified");

		typespecs.m_bConst = true;
		return 2;
	}
	else if (curtok->type == CToken::tok_keyword &&
		(curtok->pkw->n == KW_VOLATILE))
	{
		GetToken();

		if (typespecs.m_bVolatile)
			pPP->jerror("volatile already specified");

		typespecs.m_bVolatile = true;

		return 2;
	}
	else
	{
		return simple_type_specifier(typespecs, pScope);
	}
//	return FALSE;
}

/*
storage-class-specifier:
	auto
	register
	static
	extern
	mutable

decl-specifier:
	storage-class-specifier
	type-specifier
	function-specifier
	friend
	typedef

decl-specifier-seq:
	decl-specifier-seqopt decl-specifier
*/

/*
static Type* decl_specifier_seq(CClass* pNamespace, CScope* pScope, bool& bTypedef)
{
}
*/

BOOL CCPPCompiler::decl_specifier_seq(CClass* pInnermostClass, CScope* pScope, CDeclSpecifiers& declspecs, bool& bTypedef)
{
	/*bool*/ bTypedef = false;

	BOOL bFoundOne = FALSE;
	int do_more_type_specifiers = 2;

	while (!pPP->_eof())
	{
		if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_TYPEDEF)
		{
			GetToken();
			bTypedef = true;
		}
		else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_FRIEND)
		{
			GetToken();
			pPP->jerror("friend specifier not yet supported");
		}
		else if (curtok->type == CToken::tok_keyword &&
				(curtok->pkw->n == KW_INLINE ||
				curtok->pkw->n == KW_VIRTUAL ||
				curtok->pkw->n == KW_EXPLICIT))	// function-specifier
		{
			declspecs.functionSpecifierKW = curtok->pkw->n;
			GetToken();
		}
		else if (curtok->type == CToken::tok_keyword && curtok->pkw->flags & kwfStorageClassSpecifier)
		{
			if (curtok->pkw->n == KW___DECLSPEC)
			{
				GetToken();

				EatSymbol('(');
				GetToken();
				EatSymbol(')');
			}
			else
			{
				// No more than one storage class specifier should be specified
				if (declspecs.storageClassKW != -1)
				{
					pPP->jerror("more than one storage class specified");
				}

				/*
				if (declspecs.storageClassKW == KW_EXTERN)
				{
					printf("");
				}
				*/

				declspecs.storageClassKW = curtok->pkw->n;
				GetToken();
			}
		}
		else
		{
			/*
			CToken tok0 = *curtok;
			GetToken();
			if (curtok->type == CToken::tok_symbol && curtok->symbol == '::')
			{
				printf("");
			}
			m_tokStack.push(tok0);
			GetToken();
			*/

			int save = m_tokStack2.size();

			bool bDestructor = false;
			bool bConstructor = false;
			if (curtok->type == CToken::tok_symbol && curtok->symbol == '~')
			{
				GetToken();
				bDestructor = true;
			}

			if (curtok->type == CToken::tok_ident)
			{
				if (pInnermostClass)
				{
					if (pInnermostClass->m_name == curtok->ident)
					{
					//	CToken tok0 = *curtok;
						GetToken();

						/*
						if (curtok->type == CToken::tok_symbol && curtok->symbol == '::')
						{
							printf("");
						}
						else
						*/
						if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
						{
							bConstructor = true;
						}
					//	m_tokStack.push(*curtok);
					//	m_tokStack.push(tok0);
					//	GetToken();
						Restore(save);

						if (bConstructor || bDestructor)
						{
							if (bDestructor)
								declspecs.m_type.m_pType = new Type();
							else
								declspecs.m_type.m_pType = new Type();

							return TRUE;//declspecs.m_type.m_pType;
						}
					}
					else
					{
						if (bDestructor)
						{
							pPP->jerror("looks like destructor, but function name is not same as class name");
						}
					}
				}
				else
				{
					if (bDestructor)
					{
						pPP->jerror("looks like destructor, but outside of class");
					}
				}
			}

			/*
			if (curtok->type == CToken::tok_symbol && curtok->symbol == '::')
			{
				printf("");
			}
			*/

			if (do_more_type_specifiers == 2)
			{
				do_more_type_specifiers = type_specifier(declspecs.m_type, pInnermostClass, pScope);

				if (do_more_type_specifiers == 0)
					break;
			}
			else
				break;
		}

		bFoundOne = TRUE;
	}
/*
		if (curtok->type == CToken::tok_ident)
		{
			char msg[512];
			sprintf(msg, "'%s' : undeclared identifier, expecting type", curtok->ident);
			pPP->jerror(msg);
		}
		else
		{
			char msg[512];
			sprintf(msg, "expecting type");
			pPP->jerror(msg);
		}
*/

	if (!bFoundOne)
	{
		return FALSE;//NULL;
	}
	else
	{
		return TRUE;//declspecs.m_type.GetType(this);
	}
}

/*
declarator-id:
	id-expression
	::opt nested-name-specifieropt type-name
*/
CExpression* CCPPCompiler::declarator_id(CClass* pInnermostClass, CScope* pScope)
{
	CExpression* pExpr = id_expression(pInnermostClass, pScope);

	return pExpr;

/*
	if (pExpr->tok.type == CToken::tok_ident)
	{
		pDeclarator->m_name = pExpr->tok.ident;
		return TRUE;
	}
	else
	{
		CScope* pScope2 = GetScope(pGlobal->m_pNamespace->m_pScope, pExpr->left);
		if (pScope2)
		{
			declsmap::iterator decli = pScope2->m_decls.find(pExpr->right->tok.ident);
			if (decli != pScope2->m_decls.end())
			{
				return TRUE;
			}
			else
			{
				char msg[512];
				sprintf(msg, "'%s' : not a member of '%s'", pExpr->right->tok.ident, pScope2->m_pClass->m_pType->m_name.c_str());
				pPP->jerror(msg);
			}
		}

		return FALSE;
	}
*/
}

/*
parameter-declaration:
	decl-specifier-seq declarator
	decl-specifier-seq declarator = assignment-expression
	decl-specifier-seq abstract-declaratoropt
	decl-specifier-seq abstract-declaratoropt = assignment-expression
*/
CDeclarator* CCPPCompiler::parameter_declaration(CClass* pInnermostClass, CScope* pScope)
{
	bool bTypedef;
	CDeclSpecifiers declspecs;
	if (!decl_specifier_seq(pInnermostClass, pScope, declspecs, bTypedef))
	{
		if (curtok->type == CToken::tok_ident)
		{
			char msg[512];
			sprintf(msg, "'%s' : Expected type", curtok->ident);
			pPP->jerror(msg);

			/*
			{
			Type* pType = pScope->GetType("CComBSTR");
			printf("");
			}

			{
			Type* pType = pGlobal->m_pNamespace->m_pScope->GetType("_AtlCreateWndData");
			printf("");
			}
			*/
		}
		else if (curtok->type == CToken::tok_symbol)
		{
			char msg[512];
			sprintf(msg, "'%c' : Expected type", (char)curtok->symbol);
			pPP->jerror(msg);
		}
		else
		{
			pPP->jerror("Expected type");
		}
		GetToken();
	}

	Type* pType = declspecs.m_type.GetType(this);

	CDeclarator* pDeclarator = new CDeclarator;
	pDeclarator->m_pType = declarator(pDeclarator, pType, pInnermostClass, pScope);

	if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
	{
		GetToken();

		CExpression* pExpr = assignment_expression(pInnermostClass, pScope);
		if (pExpr == NULL)
		{
			pPP->jerror("invalid expression");
		}
	}

	if (pScope->m_pClass)
	{
		printf("");
	}

	return pDeclarator;
}

/*
parameter-declaration-list:
	parameter-declaration
	parameter-declaration-list , parameter-declaration
*/
void CCPPCompiler::parameter_declaration_list(CFunction* pFunction, CClass* pInnermostClass, CScope* pScope)
{
	pFunction->m_stackSize = 0;

#if 0
	int spOffset = -8;	// stack pointer offset
#endif

	while (!pPP->_eof())
	{
		if (curtok->type == CToken::tok_symbol && curtok->symbol == '...')
		{
			break;
		}

		CDeclarator* pDeclarator = parameter_declaration(pInnermostClass, pScope);

#if 0
		spOffset -= 4;
#endif
		pFunction->m_stackSize += 4;

		if (pDeclarator)
		{
#if 0
			pDeclarator->m_spOffset = spOffset;
#endif

			pFunction->m_parameters.push_back(pDeclarator);
		}
		else
		{
			pPP->jerror("Expected declarator");
		}

		if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
		{
			GetToken();
			continue;
		}
		break;
	}

	// In C++, a single void argument is the same as an empty argument list
	if (pFunction->m_parameters.size() == 1)
	{
		if (pFunction->m_parameters[0]->m_pType)
		{
			if (pFunction->m_parameters[0]->m_pType->m_type == type_void)
			{
				pFunction->m_parameters.clear();
			}
		}
	}

	/*
	if (pScope->m_pClass)
	{
		CDeclarator* pDeclarator = new CDeclarator;
		pDeclarator->m_pType = new Type(type_pointer, sizeof_pointer);
		pDeclarator->m_pType->m_pPointerTo = new Type(type_class);
		pDeclarator->m_pType->m_pPointerTo->m_pClass = pScope->m_pClass;

		pFunction->m_parameters.insert(pFunction->m_parameters.begin(), pDeclarator);
	}*/
}

/*
parameter-declaration-clause:
	parameter-declaration-listopt ...opt
	parameter-declaration-list , ...
*/
void CCPPCompiler::parameter_declaration_clause(CFunction* pFunction, CClass* pNamespace, CScope* pScope)
{
	parameter_declaration_list(pFunction, pNamespace, pScope);
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '...')
	{
		GetToken();
		pFunction->m_bVarArg = TRUE;
	}
}


/**********************************************************************************
	Declarators

A declarator declares a single object, function, or type, within a declaration
Each declarator contains exactly one declarator-id; it names the identifier that is declared.
*/

/*
type-specifier-seq:
	type-specifier type-specifier-seqopt
*/
Type* CCPPCompiler::type_specifier_seq(CClass* pNamespace, CScope* pScope)
{
	TypeSpecifiers typespecs;
	while (!pPP->_eof())
	{
		int r = type_specifier(typespecs, pNamespace, pScope);
		if (r != 2)
			break;
	}

	return typespecs.GetType(this);
}

/*
direct-abstract-declarator:
	direct-abstract-declaratoropt
	( parameter-declaration-clause ) cv-qualifier-seqopt exception-specificationopt
	direct-abstract-declaratoropt [ constant-expressionopt ]
	( abstract-declarator )
*/

/*
abstract-declarator:
	ptr-operator abstract-declaratoropt
	direct-abstract-declarator
*/
Type* CCPPCompiler::abstract_declarator(Type* pType)
{
	ASSERT(pType);

	while (	(curtok->type == CToken::tok_symbol && (curtok->symbol == '*' || curtok->symbol == '&')) ||
				(curtok->type == CToken::tok_keyword && (curtok->pkw->n == KW_CONST || curtok->pkw->n == KW_VOLATILE))
			)
	{
		if (curtok->type == CToken::tok_symbol && (curtok->symbol == '*' || curtok->symbol == '&'))
		{
			Type* pType2 = new Type(type_pointer, sizeof_pointer);
			pType2->m_pPointerTo = pType;
			pType = pType2;
		}
		else if (curtok->pkw->n == KW_CONST)
		{
			if (pType->m_bConst)
			{
				pPP->jerror("const already specified");
			}

			pType->m_bConst = true;
		}
		else if (curtok->pkw->n == KW_VOLATILE)
		{
			if (pType->m_bVolatile)
			{
				pPP->jerror("volatile already specified");
			}

			pType->m_bVolatile = true;
		}

		GetToken();
	}

	return pType;
}

/*
type-id:
	type-specifier-seq abstract-declaratoropt
*/
Type* CCPPCompiler::type_id(CClass* pNamespace, CScope* pScope)
{
	Type* pType = type_specifier_seq(pNamespace, pScope);
	if (pType)
	{
		pType = abstract_declarator(pType);
	}
	return pType;
}

/*
direct-declarator:
	declarator-id
	direct-declarator ( parameter-declaration-clause ) cv-qualifier-seqopt exception-specificationopt
	direct-declarator [ constant-expressionopt ]
	( declarator )
*/

Type* CCPPCompiler::direct_declarator(CDeclarator* pDeclarator, Type* pType, CClass* pInnermostClass, CScope* pScope)
{
	//CDeclarator* pDeclarator = NULL;

	if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
	{
		GetToken();

		Type* pType2 = new Type(type_function);
		pType2->m_pFunction = new CFunction;
		pType2->m_pFunction->m_pReturnType = pType;
		if (pType == NULL)
		{
			pPP->jerror("no type for return type of function ?");
		}

		//pType2->m_pType = pType;

		if (pDeclarator->m_name.length() != 0)
		{
			pPP->jerror("hm..");
		}

		pType = declarator(pDeclarator, pType2, pInnermostClass, pScope);
		ASSERT(pDeclarator->m_pOwnerScope);
		/*
		if (pDeclarator->m_name.length() == 0)
		{
			pPP->jerror("Expected declarator\n");
		}
		*/
		EatSymbol(')');

		//pType = pType2;
	}
	else
	{
/*		pDeclarator = new CDeclarator;
		pDeclarator->m_location.m_filepath = pPP->m_pFile->m_filepath;
		pDeclarator->m_location.m_line = pPP->m_pFile->m_line;
		pDeclarator->m_pType = pType;
*/
		CExpression* pExpr = declarator_id(pInnermostClass, pScope);

#if 0
		*ppScope = pScope;
#endif

		if (pExpr && pExpr->tok.type != CToken::tok_empty)
		{
/*
			if (pExpr->tok.type == CToken::tok_ident)
			{
				pDeclarator->m_name = pExpr->tok.ident;
			}
			else if (pExpr->right->tok.type == CToken::tok_ident)
				*/
			{

#if 0
				if (pExpr->tok.symbol == '::')
				{
					if (pExpr->left)
					{
						Type* pLeft = pScope->GetType(pExpr->left->tok.ident);
						if (pLeft && pLeft->m_pClass)
						{
							/*
							if (!strcmp(pExpr->left->tok.ident, "CComVariant"))
							{
								printf("");
							}
							*/

						//	pDeclarator = new CDeclarator;
							pDeclarator->m_pOwnerScope = pLeft->m_pClass->m_pScope;
							ASSERT(pDeclarator->m_pOwnerScope);

							std::string str;

							if (pExpr->right->m_pType)
							{
							//	ASSERT(pType == NULL);

								str = "operator_";
								str += pExpr->right->m_pType->toString();
							}
							else if (pExpr->right->tok.type == CToken::tok_symbol)
							{
								char buf[5];
								sprintf(buf, "%.4s", (char*)&pExpr->right->tok.symbol);

								std::string str = "operator_";
								str += buf;

								if (str == "operator_>-")
								{
									printf("");
								}
							}
							else if (pExpr->right->tok.type == CToken::tok_ident)
							{
								str = pExpr->right->tok.ident;
							}
							else
								ASSERT(0);

							CDeclarator* pDeclarator2 = pLeft->m_pClass->GetDeclarator(str.c_str());
							ASSERT(pDeclarator2);
							pDeclarator->m_name = pDeclarator2->m_name;

							if (pExpr->right->m_pType)
							{
								//pDeclarator->m_pType = pExpr->right->m_pType;
								pType = pExpr->right->m_pType;
							}
							else
							{
								//pDeclarator->m_pType = pType;
							}

							//ASSERT(pDeclarator->m_pType);

							ASSERT(pType);

							pDeclarator->m_location.m_filepath = pPP->m_pFile->m_filepath;
							pDeclarator->m_location.m_line = pPP->m_pFile->m_line;
						}
						else
						{
							pPP->jerror("Error in ::");
							Type* pLeft = pScope->GetType(pExpr->left->tok.ident);
						}
					}
					else
					{
						pPP->jerror("Nothing left of ::");
					}
				}
				else
#endif
				if (pExpr->tok.symbol == '::')
				{
					pDeclarator->m_pOwnerScope = GetNestedScope(pScope, pExpr->left);
					ASSERT(pDeclarator->m_pOwnerScope);
					pExpr = pExpr->right;
				//	ASSERT(pExpr->tok.type == CToken::tok_ident);
				}
				else
				{
					pDeclarator->m_pOwnerScope = pScope;
				}

				{
				//	pDeclarator = pScope->GetDeclarator(pExpr->tok.ident);
				//	if (pDeclarator == NULL)
					{
						// hmm ???
					//	pDeclarator = new CDeclarator;
					//	pDeclarator->m_pOwnerScope = pScope;
#if 0
						ASSERT(pDeclarator->m_pOwnerScope);
#endif

						//ASSERT(0);
					//	MessageBeep(-1);
#if 0	// TODO, had this
						if (pExpr->m_pType)	// cast operator
						{
							if (pType != NULL)
							{
								pPP->jerror("cast operator: decl_specifier_seq should be NULL");
							}

							std::string str = "operator_";
							str += pExpr->m_pType->toString();
							pDeclarator->m_name = str;
							//pDeclarator->m_pType = pExpr->m_pType;
							pType = pExpr->m_pType;
						}
						else
#endif
							if (pExpr->tok.type == CToken::tok_symbol)	// operator
						{
							char buf[5];
							sprintf(buf, "%.4s", (char*)&pExpr->tok.symbol);

							std::string str = "operator_";
							str += buf;

							pDeclarator->m_name = str;

							ASSERT(pType != NULL);
							//pDeclarator->m_pType = pType;
						}
						else if (pExpr->tok.type == CToken::tok_keyword)	// new/delete operators
						{
							if (pExpr->tok.pkw->n == KW_NEW)
								pDeclarator->m_name = "operator_new";
							else if (pExpr->tok.pkw->n == KW_DELETE)
								pDeclarator->m_name = "operator_delete";

							//pDeclarator->m_pType = pType;
						}
						else if (pExpr->tok.type == CToken::tok_ident)
						{
							pDeclarator->m_name = pExpr->tok.ident;
							if (pType == NULL)
							{
								pPP->jerror("Expected type before identifier");
							}
							//pDeclarator->m_pType = pType;
						}
						else
						{
							ASSERT(0);
						}

					//	ASSERT(pType);

						pDeclarator->m_location.m_filepath = pPP->m_pFile->m_filepath;
						pDeclarator->m_location.m_line = pPP->m_pFile->m_line;
					}
				}
#if 0
				if (TRUE)
				{
				CScope* pScope2 = GetScope(pGlobal->m_pNamespace->m_pScope, pExpr->left);
				if (pScope2)
				{
					declsmap::iterator decli = pScope2->m_decls.find(pExpr->right->tok.ident);
					if (decli != pScope2->m_decls.end())
					{
						*ppScope = pScope2;
					}
					else
					{
						char msg[512];
						if (pScope2->m_pClass)
							sprintf(msg, "'%s' : not a member of '%s'", pExpr->right->tok.ident, pScope2->m_pClass->m_pType->m_name.c_str());
						else
							sprintf(msg, "'%s' : not a member of ..huh? not even a class?", pExpr->right->tok.ident);

						pPP->jerror(msg);
					}
				}
			}
#endif
			}
			/*
			else
			{
				*ppScope = pScope;	// Just set it to some valid scope, we're in error anyway
			}
			*/
		}
		else
		{
			pDeclarator->m_pOwnerScope = pScope;
		}
	}

	/*
	if (pDeclarator == NULL)
	{
		pDeclarator = new CDeclarator;
		pDeclarator->m_pOwnerScope = pScope;
		pDeclarator->m_location.m_filepath = pPP->m_pFile->m_filepath;
		pDeclarator->m_location.m_line = pPP->m_pFile->m_line;
		pDeclarator->m_pType = pType;
//		ASSERT(pDeclarator->m_pType);
	}
	*/

	if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
	{
		GetToken();

		Type* pType2 = pType;
		while (pType2)
		{
			if (pType2->m_type == type_function)
			{
				break;
			}
			else if (pType2->m_type == type_typedef)
			{
				;//pType2 = pType2->m_pDeclarator->m_pType;
				pType2 = NULL;
				break;
			}
			else if (pType2->m_type == type_pointer)
			{
				pType2 = pType2->m_pPointerTo;
			}
			else
			{
				pType2 = NULL;
				break;
			}
		}
		if (pType2 == NULL)
		{
			pType2 = new Type(type_function);
			pType2->m_pFunction = new CFunction;
			pType2->m_pFunction->m_pReturnType = pType;
#if 0
			ASSERT(pType);
#endif
			pType = pType2;
		}

		/*
		Type* pType2 = new Type(type_function);
		//pTyp2->
		//pType2->m_name = pDeclarator->m_name;
		pType2->m_pFunction = new CFunction;
		pType2->m_pFunction->m_pReturnType = pType;
		//pDeclarator->m_pType = pType2;
		*/

		//pDeclarator->m_pFunction->m_pScope = new CScope;

		if (curtok->type != CToken::tok_symbol || curtok->symbol != ')')
		{
			parameter_declaration_clause(pType2->m_pFunction, pInnermostClass, pScope);
		}

	//	delete pFunctionScope;

		EatSymbol(')');

		// cv-qualifier-seq
		while (!pPP->_eof())
		{
			if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_CONST)
			{
				int kw = KW_CONST;
			}
			else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_VOLATILE)
			{
				int kw = KW_VOLATILE;
			}
			else
			{
				break;
			}
			GetToken();
		}

	//	pType = pType2;
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '[')
	{
		Type* pType2 = new Type(type_array);
		pType2->m_pPointerTo = pType;
		pType2->m_sizeof = pType2->m_pPointerTo->GetType()->get_sizeof();
		ASSERT(pType2->m_sizeof != -1);

		while (curtok->type == CToken::tok_symbol && curtok->symbol == '[')
		{
			GetToken();

		// Array
			if (curtok->type != CToken::tok_symbol || curtok->symbol != ']')
			{
				CExpression* pExpr = constant_expression(pInnermostClass, pScope);
				if (pExpr)
				{
					if (pExpr->tok.type == CToken::tok_integer)
					{
						//if (pDeclarator->m_pType)
						{

						//	pDeclarator->m_pType = pDeclarator->m_pType->Clone();

							pType2->m_arrayDims.push_back(pExpr->tok.int32);
							pType2->m_sizeof *= pExpr->tok.int32;
							ASSERT(pType2->m_sizeof != 0);
						}
					}
					else
					{
						pPP->jerror("Array size must be a constant integer expression");
					}
				}
				else
				{
					pPP->jerror("Expected expression");
				}
			}
			else
			{
			//	MessageBeep(-1);
			}

			EatSymbol(']');
		}

		pType = pType2;
	}

//	return pDeclarator;

	return pType;
}

/*
cv-qualifier:
	const
	volatile

cv-qualifier-seq:
	cv-qualifier cv-qualifier-seqopt
*/
#if 0
void cv_qualifier_seq()
{
	while (curtok->type == CToken::tok_keyword && (curtok->pkw->n == KW_CONST || curtok->pkw->n == KW_VOLATILE))
	{
		GetToken();
		//pPP->jfatalerror("const and volatile not yet supported");
	}
}
#endif

///////////////////////////////////////////////////////////////////////
// Declarators

void CCPPCompiler::typedef_declarator(CDeclarator* pDeclarator, CScope* pScope)
{
	if (pDeclarator->m_pType)
	{
		Type* pType = pScope->GetType(pDeclarator->m_name.c_str());
		if (pType)
		{
		// If these are equal it means we typedefed and declared it with
		// the same name, like:
		//		typedef class a {} a;
		// which we permit without error
			if (pType != pDeclarator->m_pType)
			{
			//	Type* pType0 = pType;
			//	Type* pType1 = pDeclarator->m_pType;

				/*
				while (pType0->m_pPointerTo && pType1->m_pPointerTo)
				{
					pType0 = pType0->m_pPointerTo;
					pType1 = pType1->m_pPointerTo;
				}
				*/

				/*
				if (pType0->m_pPointerTo != NULL || pType1->m_pPointerTo != NULL)
				{
					pPP->jerror("redeclaration, differs in level of indirection");
				}
				else
				*/
				{
					if (pType->get_sizeof() == -1)	// partially declared
					{
						int classKey0 = pType->GetClassKey();
						int classKey1 = pDeclarator->m_pType->GetClassKey();

						if (classKey0 == -1 || classKey1 == -1)
						{
							pPP->jerror("INTERNAL ERROR:\n");
							pPP->jerror(pType->toString().c_str());
							pPP->jerror("\n");
							pPP->jerror(pDeclarator->m_pType->toString().c_str());
						}
						else if (!classKey1 != classKey0)//m_pClass->m_kwType != pType->m_pClass->m_kwType)	// Already declared as a different type of struct/class/union
						{
							char msg[256];
							sprintf(msg, "'%s %s' first seen as %s",
								Keywords[classKey1].name, pDeclarator->m_name.c_str(),
								Keywords[classKey0].name);
						}
						else
						// a previously partial declaration is now fully declared
						{
							ASSERT(pType->m_type == type_class);	// ??
							delete pType->m_pClass;

#if 0
							pType->m_name = pDeclarator->m_name;
#endif
							pType->m_sizeof = pDeclarator->m_pType->get_sizeof();
							pType->m_pClass = pDeclarator->m_pType->m_pClass;

							pDeclarator->m_pType->m_pClass = NULL;
	#if 0
							delete pDeclarator;
	#endif
						}
					}
					else
					{
						if (!pType->IsEqual(pDeclarator->m_pType))
						{
							std::string typ0 = pType->toString();
							std::string typ1 = pDeclarator->m_pType->toString();

							char msg[512];
							sprintf(msg, "'%s' already declared, first seen\n%s(%d) as:\n'%s'\nto:'%s'",

								pDeclarator->m_name.c_str(),
								pType->m_pNamedType->m_location.m_filepath.c_str(), pType->m_pNamedType->m_location.m_line,
								typ0.c_str(),
								typ1.c_str());

							pPP->jerror(msg);
						}
					}
				}
			}
		}
		else
		{
			if (pDeclarator->m_name.length())	// typedef requires a name
			{
				ASSERT(pDeclarator->m_name.length() != 0);

				Type* pType = new Type(type_typedef);
				pType->m_pDeclarator = pDeclarator;

#if 0
				Type* pType = pDeclarator->m_pType;//->Clone();
				pType->m_name = pDeclarator->m_name;
#endif

				pScope->AddType(this, pType);

			//	std::string str = pType->toString();

#if 0
				delete pDeclarator;
#endif
				pDeclarator = NULL;

			//ASSERT(pType->m_name.length() != 0);

		//	printf("typedef '%s'\n", pType->m_name.c_str());

			//	pScope->m_types.push_back(pType);
			//	pType->m_location.m_filepath = pPP->m_pFile->m_filepath;
			//	pType->m_location.m_line = pPP->m_pFile->m_line;
			}
			else
			{
				pPP->jerror("no names found for typedef declarator");
			}
		}
	}
	else
	{
		pPP->jerror("expected typedef type");
	}
}

BOOL CCPPCompiler::nontypedef_declarator(CDeclarator* pDeclarator, CClass* pInnermostClass, CScope* pScope)
{
	BOOL bFunctionTry = FALSE;
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_TRY)
	{
		GetToken();
		bFunctionTry = TRUE;
		pPP->jfatalerror("function-try-block not yet supported");
	}

	if (curtok->type == CToken::tok_symbol && curtok->symbol == ':')	//	ctor-initializer
	{
		GetToken();

		while (!pPP->_eof())
		{
			id_expression(pInnermostClass, pScope);

			EatSymbol('(');
			CExpression* pExpr = expression(pInnermostClass, pScope);
			EatSymbol(')');

			if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
			{
				GetToken();
				continue;
			}
			break;
		}
	}

#if 0
	std::string mname;
	if (linkage == LINKAGE_EXTERN_C)
	{
		mname = "_";
		//mname += pDeclarator->m_name;
	}
	else if (linkage == LINKAGE_EXTERN_CPP)
	{
		//mname = pDeclarator->MangleName();
	}
#endif

	declsmap::iterator decl;
	if (pDeclarator->m_pOwnerScope)
	{
		if (pDeclarator->m_name.length())
			decl = pDeclarator->m_pOwnerScope->m_decls.find(pDeclarator->m_name);
		else
			decl = pDeclarator->m_pOwnerScope->m_decls.end();

		if (decl != pDeclarator->m_pOwnerScope->m_decls.end())
		{
			/*
	#ifdef _DEBUG
			{
				for (int i = 0; i < pDeclarator->m_pOwnerScope->m_orderedDecls.size(); i++)
				{
					if (pDeclarator->m_pOwnerScope->m_orderedDecls[i] == (*decl).second)
					{
						//pDeclarator->m_pOwnerScope->m_orderedDecls[i] = pDeclarator;
						break;
					}
				}
				ASSERT(i < pDeclarator->m_pOwnerScope->m_orderedDecls.size());
			}
	#endif
			*/
			/*
			if (FALSE)
			{
				char msg[512];
				sprintf(msg, "'%s' : redefinition; first defined:\n %s(%d)",
					pDeclarator->m_name.c_str(),
					(*decl).second->m_location.m_filepath.c_str(), (*decl).second->m_location.m_line);
				pPP->jerror(msg);
			}
			*/

			CDeclaratorReference* pSecond = (*decl).second;

			if (pDeclarator->m_pType->GetType()->m_type == type_function)
			{
				if (pSecond->m_pDeclarator->m_pType->GetType()->m_type == type_function)
				{
					if (!pDeclarator->m_pType->m_pFunction->m_pReturnType->IsEqual(pSecond->m_pDeclarator->m_pType->GetType()->m_pFunction->m_pReturnType))
					{
						if (pDeclarator->m_pType->m_pFunction->IsEqual(pSecond->m_pDeclarator->m_pType->GetType()->m_pFunction))
						{
							std::string str0 = pDeclarator->toString();
							std::string str1 = pSecond->m_pDeclarator->toString();

							pDeclarator->m_pType->m_pFunction->IsEqual(pSecond->m_pDeclarator->m_pType->GetType()->m_pFunction);

							char msg[512];
							sprintf(msg, "'%s' : overloaded function differs only by return type from '%s'",
								str0.c_str(), str1.c_str());
							pPP->jerror(msg);
						}
						else
						{
							/*
							char msg[512];
							sprintf(msg, "%s' : is not a member", pDeclarator->m_name.c_str());
							pPP->jerror(msg);
							*/
							// It's a different function
							decl = pDeclarator->m_pOwnerScope->m_decls.end();
						}
					}
					else	// equal return type
					{
						if (pDeclarator->m_pType->m_pFunction->IsEqual(pSecond->m_pDeclarator->m_pType->m_pFunction))
						{
							if (pDeclarator->m_linkage != pSecond->m_pDeclarator->m_linkage)
							{
								char msg[512];
								sprintf(msg, "linkage specification contradicts earlier specification for '%s'",
									pDeclarator->m_name.c_str());
								pPP->jerror(msg);
							}
							else
							{
								if (pDeclarator->m_pType->m_pFunction->m_thiscall != pSecond->m_pDeclarator->m_pType->m_pFunction->m_thiscall)
								{
									char msg[512];
									sprintf(msg, "thiscall specification contradicts earlier specification for '%s'",
										pDeclarator->m_name.c_str());
									pPP->jerror(msg);
								}
							}
						}
						else
						{
							char msg[512];
							sprintf(msg, "%s' : is not a member", pDeclarator->m_name.c_str());
						//	pPP->jerror(msg);

							// It's a different function
							decl = pDeclarator->m_pOwnerScope->m_decls.end();
						}
					}
				}
				else
				{
					char msg[512];
					sprintf(msg, "'%s' : redefinition; first seen as non-function:\n %s(%d)",
						pDeclarator->m_name.c_str(),
						pSecond->m_pDeclarator->m_location.m_filepath.c_str(), pSecond->m_pDeclarator->m_location.m_line);
					pPP->jerror(msg);
				}
			}
			else	// != type_function
			{
				if (pSecond->m_pDeclarator->m_pType->GetType()->m_type == type_function)
				{
					char msg[512];
					sprintf(msg, "'%s' : redefinition; first seen as function:\n %s(%d)",
						pDeclarator->m_name.c_str(),
						pSecond->m_pDeclarator->m_location.m_filepath.c_str(), pSecond->m_pDeclarator->m_location.m_line);
					pPP->jerror(msg);
				}
				else
				{
					if (pDeclarator->m_storageClassKW == KW_EXTERN || pSecond->m_pDeclarator->m_storageClassKW == KW_EXTERN)
					{
						if (!pDeclarator->m_pType->IsEqual(pSecond->m_pDeclarator->m_pType))
						{
							char msg[512];
							sprintf(msg, "'%s' : redefinition; first seen:\n %s(%d)",
								pDeclarator->m_name.c_str(),
								pSecond->m_pDeclarator->m_location.m_filepath.c_str(), pSecond->m_pDeclarator->m_location.m_line);
							pPP->jerror(msg);
						}
					}
					else
					{
				//		if (FALSE)	// TODO, have this
						{
							char msg[512];
							sprintf(msg, "'%s' : redefinition; first seen:\n %s(%d)",
								pDeclarator->m_name.c_str(),
								pSecond->m_pDeclarator->m_location.m_filepath.c_str(), pSecond->m_pDeclarator->m_location.m_line);
							pPP->jerror(msg);
						}
					}
				}
			}
		}
	}

	/*
	if (pDeclarator->m_storageClassKW != KW_EXTERN)
	{
		pDeclarator->m_pOwnerScope->AddDeclarator(pDeclarator);
	}
	else
	{
		pDeclarator->m_pOwnerScope->AddReferenceDeclarator(pDeclarator);
	}
	*/

#if 0
	if (decl == pDeclarator->m_pOwnerScope->m_decls.end())	// not previously declared
	{
		if (pDeclarator->m_name.length())	// ???
		{
		//	declsmap::iterator newdecl = pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
			pDeclarator->m_pOwnerScope->AddReferenceDeclarator(pDeclarator);
		}
	}
	else
	{
		if (pDeclarator->m_pType->m_type != type_function)
		{
			pPP->jerror("redefinition");
		}
#if 0
		for (int i = 0; i < pDeclarator->m_pOwnerScope->m_orderedDecls.size(); i++)
		{
			if (pDeclarator->m_pOwnerScope->m_orderedDecls[i] == (*decl).second)
			{
				pDeclarator->m_pOwnerScope->m_orderedDecls[i] = pDeclarator;
				break;
			}
		}
		ASSERT(i < pDeclarator->m_pOwnerScope->m_orderedDecls.size());

		// ??
		delete (*decl).second;
		(*decl).second = pDeclarator;
#endif
	}
#endif

	BOOL bFunctionBody = FALSE;
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')	// }
	{
	//	pDeclarator->m_pOwnerScope->AddDeclarator(pDeclarator);
		bFunctionBody = TRUE;
	}

	/*
	if (pDeclarator->m_name == "mainloop")
	{
		printf("");
	}
	*/

	/*
	if (pDeclarator->m_pType->m_type == type_function && pDeclarator->m_pType->m_pFunction->m_thiscall)
	{
		MessageBeep(-1);
	}
	*/

	if (pDeclarator->m_storageClassKW != KW_EXTERN &&
		(pDeclarator->m_pType->GetType()->m_type != type_function || bFunctionBody))
	{
		/*
		if (pDeclarator->m_name == "test")
		{
			printf("");
		}
		*/

		CDeclaratorReference* pRef = NULL;
		if (decl == pDeclarator->m_pOwnerScope->m_decls.end())
		{
			//ASSERT(pDeclarator->m_pType->GetType()->m_type != type_function || pDeclarator->m_spOffset != -1);
		//	pDeclarator->m_pOwnerScope->AddDeclarator(pDeclarator);
	
			pRef = new CDeclaratorReference(pDeclarator);

			declsmap::iterator decli = pDeclarator->m_pOwnerScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pRef));
		}
		else
		{
			pRef = (*decl).second;
			delete pRef->m_pDeclarator;
			pRef->m_pDeclarator = pDeclarator;
		}

//		ASSERT(pDeclarator->m_spOffset != -1 || pDeclarator->m_pType->GetType()->m_type == type_function);
	//	pRef->m_pDeclarator->m_referenced = 2;
		pRef->m_pDeclarator->m_defined = true;
		pDeclarator->m_pOwnerScope->m_orderedDecls.push_back(pRef);

		pGlobal->m_globals.push_back(pRef);
	}
	else
	{
#if 0
		ASSERT(pDeclarator->m_spOffset == -1);
#endif
		if (pDeclarator->m_name == "get")
		{
			printf("");
		}
	//	pDeclarator->m_pOwnerScope->AddReferenceDeclarator(pDeclarator);
		if (decl == pDeclarator->m_pOwnerScope->m_decls.end())
		{
			declsmap::iterator decli = pDeclarator->m_pOwnerScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, new CDeclaratorReference(pDeclarator)));
		}
		else
		{
			delete (*decl).second->m_pDeclarator;
			(*decl).second->m_pDeclarator = pDeclarator;
		}
	}

	/*
	if (decl != pDeclarator->m_pOwnerScope->m_decls.end())
	{
	}
	*/

	if (bFunctionBody)
	{
		ASSERT(pDeclarator);

		if (pDeclarator->m_pOwnerScope)
		{
			if (decl != pDeclarator->m_pOwnerScope->m_decls.end())
			{
				if ((*decl).second->m_pDeclarator->m_pType->m_pFunction)
				{
					if ((*decl).second->m_pDeclarator->m_pBody)
					{
						if (FALSE)	// TODO, have something like this
						{
							std::string fstr = (*decl).second->m_pDeclarator->toString();

							char msg[512];
							sprintf(msg, "function '%s' already has a body", fstr.c_str());
							pPP->jerror(msg);
						}
					}
				}
				else
				{
					pPP->jerror("huh\n");
				}
			}
		}

		ASSERT(0);
#if 0
		pDeclarator->m_pBody = new CFunctionBody;

		pDeclarator->m_pBody->m_pScope = new CScope;
		pDeclarator->m_pBody->m_pScope->m_pParentScope = pDeclarator->m_pOwnerScope;

		for (int i = 0; i < pDeclarator->m_pType->GetType()->m_pFunction->m_parameters.size(); i++)
		{
			CDeclarator* pParamDeclarator = pDeclarator->m_pType->GetType()->m_pFunction->m_parameters[i];
		//	pFunctionScope->m_orderedDecls.push_back(pParamDeclarator);
			//pDeclarator->m_pFunction->m_pBody->m_pScope->m_decls.insert(declsmap::value_type(pParamDeclarator->m_name, pParamDeclarator));
			if (pParamDeclarator->m_name.length())
			{
				pDeclarator->m_pBody->m_pScope->AddDeclarator(new CDeclaratorReference(pParamDeclarator));
			}
#if 0
			pParamDeclarator->m_spOffset = -12;
#endif
		}
#endif

		if (/*TRUE ||*/ pInnermostClass)
		{
			GetToken();
			int brace = 1;
			while (!pPP->_eof())
			{
				if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')
				{
					brace++;
				}
				else if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
				{
					brace--;

					if (brace == 0)
					{
						GetToken();
						break;
					}
				}
				GetToken();
			}

			if (brace != 0)
			{
				pPP->jfatalerror("Unexpected end of file");
			}
		}
		else
		{
			ASSERT(0);
#if 0
			function_body(pGlobal, pInnermostClass, pDeclarator, pDeclarator->m_pBody, pDeclarator->m_pBody->m_pScope);
#endif
		}
	}
	else
	{
		if (bFunctionTry)
		{
			ASSERT(0);
			//handler_seq()
		}

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
		{
			GetToken();

			/*
			if (decl != pScope->m_decls.end())
			{
				if ((*decl).second->m_pInitializerExpr)
				{
					pPP->jerror("'%s' : redefinition; multiple initialization, first defined:\n %s(%d):\n",
						NULL,
						NULL, 0);
				}
			}
			*/

			pDeclarator->m_pInitializerExpr = initializer_clause(pInnermostClass, pScope);
		}
	}

	//ASSERT(pScope == pDeclarator->m_pOwnerScope);


	return bFunctionBody;
}

/*
initializer:
	= initializer-clause
	( expression-list )
*/

/*
init-declarator:
	declarator initializeropt
*/

/*
init-declarator-list:
	init-declarator
	init-declarator-list , init-declarator
*/
void CCPPCompiler::init_declarator_list(CScope* pScope)
{
	while (!pPP->_eof())
	{
		ASSERT(0);
		//init_declarator(pScope);

		if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
		{
			GetToken();
			continue;
		}
		break;
	}
}

/*
declarator:
	direct-declarator
	ptr-operator declarator

ptr-operator:
	* cv-qualifier-seqopt
	&
	::opt nested-name-specifier * cv-qualifier-seqopt
*/
Type* CCPPCompiler::declarator(CDeclarator* pDeclarator, Type* pType, CClass* pInnermostClass, CScope* pScope)
{
//	if (curtok->type == CToken::tok_symbol && curtok->symbol == '::')
	{
//	CExpression* pExpr = nested_name_specifier(pScope);
	}

	while (	(curtok->type == CToken::tok_symbol && (curtok->symbol == '*' || curtok->symbol == '&')) ||
				(curtok->type == CToken::tok_keyword && (curtok->pkw->n == KW_CONST || curtok->pkw->n == KW_VOLATILE))
			)
	{
		if (curtok->type == CToken::tok_symbol && (curtok->symbol == '*' || curtok->symbol == '&'))
		{
			Type* pType2 = new Type(type_pointer, sizeof_pointer);
			pType2->m_pPointerTo = pType;
			pType = pType2;
		}
		else if (curtok->pkw->n == KW_CONST)
		{
			if (pType->m_bConst)
			{
				pPP->jerror("const already specified");
			}

			pType->m_bConst = true;
		}
		else if (curtok->pkw->n == KW_VOLATILE)
		{
			if (pType->m_bVolatile)
			{
				pPP->jerror("volatile already specified");
			}

			pType->m_bVolatile = true;
		}

		GetToken();
	}

	pType = direct_declarator(pDeclarator, pType, pInnermostClass, pScope);
//	ASSERT(pDeclarator->m_pOwnerScope);

	//return pDeclarator;

	return pType;
}

////////////////////////////////////////////////////////////////////////////////////
// Templates

/*
template-parameter:
	type-parameter
	parameter-declaration

type-parameter:
	class identifieropt
	class identifieropt = type-id
	typename identifieropt
	typename identifieropt = type-id
	template < template-parameter-list > class identifieropt
	template < template-parameter-list > class identifieropt = id-expression
*/

CTemplateParameter* CCPPCompiler::template_parameter(CClass* pInnermostClass, CScope* pScope)
{
	if (curtok->type == CToken::tok_keyword &&
		(curtok->pkw->n == KW_CLASS || curtok->pkw->n == KW_TYPENAME))
	{
		GetToken();

		CTemplateParameter* pParam = new CTemplateParameter;

		pParam->m_type = CTemplateParameter::Type_type;

		pParam->m_pType = new Type(type_class);
		pParam->m_pType->m_pClass = new CClass(/*pParam->m_pType*/);

		if (curtok->type == CToken::tok_ident)
		{
			pParam->m_name = curtok->ident;
			pParam->m_pType->m_pClass->m_name = curtok->ident;
#if 0
			pParam->m_pType->m_name = curtok->ident;	// TODO remove
#endif
			GetToken();
		}

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
		{
			GetToken();
			//ASSERT(0);
			pPP->jwarn("INTERNAL ERROR: Unsupported template argument");

			Type* pType = type_id(pInnermostClass, pScope);
		}

		ASSERT(pParam->m_pType->m_sizeof != 0);
	//	ASSERT(pParam->m_pType->m_name.length());
		pScope->m_types.insert(typemap::value_type(pParam->m_name, pParam->m_pType));

		return pParam;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_TEMPLATE)
	{
		GetToken();
		EatSymbol('<');
		ASSERT(0);
		EatSymbol('>');
	}
	else
	{
		CTemplateParameter* pParam = new CTemplateParameter;
		pParam->m_type = CTemplateParameter::Type_declaration;
		pParam->m_pDeclarator = parameter_declaration(pInnermostClass, pScope);

		return pParam;
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////
// Declarations

/*
function-body:
	compound-statement
*/
void CCPPCompiler::function_body(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CFunctionBody* pFunctionBody, CScope* pScope)
{
	compound_statement(pGlobal, pInnermostClass, pFunctionDecl, pFunctionBody, pScope);
}

/*
ctor-initializer:
	: mem-initializer-list
*/
#if 0
BOOL CCPPCompiler::ctor_initializer()
{
	if (curtok->type == CToken::tok_symbol && curtok->symbol == ':')
	{
		GetToken();
		pPP->jfatalerror("ctor-initializer not yet supported\n");
		return FALSE;
	}
	else
		return FALSE;
}
#endif

#if 0
/*
block-declaration:
	simple-declaration
	asm-definition
	namespace-alias-definition
	using-declaration
	using-directive
*/

/*
simple-declaration:
	decl-specifier-seqopt init-declarator-listopt ;
*/
#endif

/*
function-definition:
	decl-specifier-seqopt declarator ctor-initializeropt function-body
	decl-specifier-seqopt declarator function-try-block
*/

/*
ctor-initializer:
	: mem-initializer-list
*/

/*
function-try-block:
	try ctor-initializeropt function-body handler-seq
*/

/*
using-declaration:
	using typenameopt ::opt nested-name-specifier unqualified-id ;
	using :: unqualified-id ;
*/

/*
using-directive:
	using namespace ::opt nested-name-specifieropt namespace-name ;
*/

/*
asm-definition:
	asm ( string-literal ) ;
*/
void CCPPCompiler::asm_definition()
{
	pPP->jfatalerror("asm not yet supported");
}

/*
linkage-specification:
	extern string-literal { declaration-seqopt }
	extern string-literal declaration

storage-class-specifier:
	extern
	...

*/
#if 0
void CCPPCompiler::linkage_specification(CGlobal* pGlobal, CClass* pNamespace, CScope* pScope)
{
	if (curtok->type != CToken::tok_keyword || curtok->pkw->n != KW_EXTERN)
	{
		pPP->jfatalerror("Expected extern");
	}
	GetToken();

	if (curtok->type == CToken::tok_string)	// linkage specification
	{
		std::string strlinkage = curtok->string;
		GetToken();

		int linkage;

		if (!strcmp(strlinkage.c_str(), "C"))
		{
			linkage = LINKAGE_EXTERN_C;
		}
		else if (!strcmp(strlinkage.c_str(), "C++"))
		{
			linkage = LINKAGE_EXTERN_CPP;
		}
		else
		{
			char msg[512];
			sprintf(msg, "'%s' : unknown linkage, should be \"C\" or \"C++\"", strlinkage.c_str());
			pPP->jerror(msg);
		}

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')	// }
		{
			GetToken();

			// {
			if (curtok->type != CToken::tok_symbol || curtok->symbol != '}')
			{
				declaration_seq(pGlobal, pNamespace, pScope, linkage);
			}

			// {
			EatSymbol('}');
		}
		else
		{
			declaration(pGlobal, pNamespace, pScope, linkage);
		}
	}
	else
	{
		// extern storage class
		printf("");
	}
}
#endif

/*
namespace-body:
declaration-seqopt
*/
void CCPPCompiler::namespace_body(CGlobal* pGlobal, CClass* pNamespace, CScope* pScope, int linkage)
{
	declaration_seq(pGlobal, pNamespace, pScope, linkage);
}

/*
initializer-list:
	initializer-clause
	initializer-list , initializer-clause
*/

/*
initializer-clause:
	assignment-expression
	{ initializer-list ,opt }
	{ }
*/
CExpression* CCPPCompiler::initializer_clause(/*CDeclarator* pDeclarator,*/ CClass* pInnermostClass, CScope* pScope)
{
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')
	{
		CExpression* pExpr = new CExpression;
		pExpr->tok = *curtok;
		GetToken();

		CExpression* p = pExpr;
		//int brace = 1;
		while (!pPP->_eof())
		{
			if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
			{
				break;
			}

			CExpression* pExpr2 = new CExpression;

			p->right = pExpr2;
			pExpr2->left = initializer_clause(pInnermostClass, pScope);

			p = pExpr2;

			if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
			{
				GetToken();
				continue;
			}
			break;

			/*
			if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')
			{
				brace++;
			}
			else if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
			{
				brace--;

				if (brace == 0)
				{
					GetToken();
					break;
				}
			}
			GetToken();
			*/
		}
		EatSymbol('}');

		/*
		if (brace != 0)
		{
			pPP->jfatalerror("Unexpected end of file");
		}
		*/

		return pExpr;
#if 0
		if (curtok->type != CToken::tok_symbol || curtok->symbol != '}')
		{
			pPP->jfatalerror("not yet supported : { initializer-list ,opt }");
		}

		// {
		EatSymbol('}');
#endif
	}
	else
	{
		//pDeclarator->m_pInitializerExpr = assignment_expression(pNamespace, pScope);
		return assignment_expression(pInnermostClass, pScope);
	}
}

/*
original-namespace-name
	identifier
*/

/*

declaration:
	block-declaration
		simple-declaration
				decl-specifier-seqopt init-declarator-listopt ;
					decl-specifier-seqopt declarator initializeropt

		asm-definition
			asm ( string-literal ) ;
		namespace-alias-definition
			namespace identifier = qualified-namespace-specifier ;
		using-declaration
			using typenameopt ::opt nested-name-specifier unqualified-id ;
			using :: unqualified-id ;
		using-directive
			using namespace ::opt nested-name-specifieropt namespace-name ;

	function-definition
		decl-specifier-seqopt declarator ctor-initializeropt function-body
		decl-specifier-seqopt declarator function-try-block

	template-declaration
		exportopt template < template-parameter-list > declaration
	explicit-instantiation
		template declaration
	explicit-specialization
		template < > declaration
	linkage-specification
		extern string-literal { declaration-seqopt }
		extern string-literal declaration
	namespace-definition
		named-namespace-definition
			original-namespace-definition
				namespace identifier { namespace-body }
			extension-namespace-definition
				namespace original-namespace-name { namespace-body }
		unnamed-namespace-definition
				namespace { namespace-body }
*/

BOOL CCPPCompiler::simple_declaration_or_function_definition(CGlobal* pGlobal, CClass* pInnermostClass, CScope* pScope, int linkage, int storageClassKW, CTemplate* pTemplate)
{
#ifdef _DEBUG
	CToken tok = *curtok;
#endif

	bool bTypedef;
	CDeclSpecifiers declspecs;
	declspecs.storageClassKW = storageClassKW;
	if (!decl_specifier_seq(pInnermostClass, pScope, declspecs, bTypedef))
	{
		return FALSE;
	}

	Type* pType = declspecs.m_type.GetType(this);

	/*
			if (curtok->type == CToken::tok_ident && !strcmp(curtok->ident, "RPC_IF_CALLBACK_FN"))
			{
				MessageBeep(-1);
			}
*/
	if (curtok->type == CToken::tok_symbol && curtok->symbol == ';')
	{
		GetToken();
		if (pType)
		{
			Type* pType2 = pType->GetType();

			if (pType2->m_type != type_class && pType2->m_type != type_enum)
			{
				pPP->jwarn("ignored when no variable is declared");
			}
		}
	}
	else
	{
		/*
			if (curtok->type == CToken::tok_ident && !strcmp(curtok->ident, "RPC_IF_CALLBACK_FN"))
			{
				MessageBeep(-1);
			}
			*/

		while (!pPP->_eof())
		{
			/*
			if (curtok->type == CToken::tok_ident && !strcmp(curtok->ident, "RPC_IF_CALLBACK_FN"))
			{
			}
			*/

			CDeclarator* pDeclarator = new CDeclarator;
			pDeclarator->m_pType = declarator(pDeclarator, pType, pInnermostClass, pScope);
/*
			if (curtok->type == CToken::tok_ident && !strcmp(curtok->ident, "RPC_IF_CALLBACK_FN"))
			{
			}
*/
			if (pDeclarator->m_name.length() == 0)
			{
				pPP->jerror("expected declarator");
			}
			else if (pDeclarator->m_pType == NULL)
			{
				pPP->jerror("declarator must have a type");
			}
			else
			{
				if (pDeclarator->m_pType->GetType()->m_type == type_function)//m_pFunction)
				{
					pDeclarator->m_pType->GetType()->m_pFunction->m_funcspec = declspecs.functionSpecifierKW;

					/*
					if (curtok->type == CToken::tok_symbol && curtok->symbol == ':')	// ctor-initializer
					{
						GetToken();
						printf("");
					}
					*/
				}

				pDeclarator->m_linkage = linkage;
				pDeclarator->m_storageClassKW = declspecs.storageClassKW;

				if (pDeclarator->m_name == "c")
				{
					if (pDeclarator->m_pType->GetType()->m_type == type_class)
					{
						// call constructor
					}
					printf("");
				}

				if (bTypedef)
				{
					typedef_declarator(pDeclarator, pScope);
				}
				else
				{
					if (	pDeclarator->m_storageClassKW != KW_EXTERN &&
							pDeclarator->m_pType->GetType()->m_type != type_function)
					{
#if 0
						pDeclarator->m_spOffset = pScope->m_stackSize;
						if (pDeclarator->m_pType)
						{
						//	ASSERT(pDeclarator->m_pType->get_sizeof() != -1);
							unsigned long _sizeof = pDeclarator->m_pType->get_sizeof();
							ASSERT(_sizeof != -1);
							pScope->m_stackSize += _sizeof;
						}
#endif
					}

					if (pTemplate)
					{
						//ASSERT(pTemplate == NULL);	// TODO
#if 0	// ???
						pPP->jerror("Function template not yet supported");
#endif
					}

					if (pDeclarator->m_pOwnerScope->m_pClass)
					{
						declsmap::iterator decl;
						decl = pDeclarator->m_pOwnerScope->m_decls.find(pDeclarator->m_name);
						if (decl == pDeclarator->m_pOwnerScope->m_decls.end())
						{
							char msg[512];
							sprintf(msg, "'%s' is not a member of '%s'", pDeclarator->m_name.c_str(), pDeclarator->m_pOwnerScope->m_pClass->m_name.c_str());
							pPP->jerror(msg);
						}
						else
						{
							Type* pType = pDeclarator->m_pType->GetType();

							if (pType->m_type == type_function)
							{
								pType->m_pFunction->m_thiscall = TRUE;
								pType->m_pFunction->m_stackSize += sizeof_pointer;

								CDeclarator* pParamDeclarator = new CDeclarator;
								pParamDeclarator->m_pType = new Type(type_pointer, sizeof_pointer);
								pParamDeclarator->m_pType->m_pPointerTo = new Type(type_class);
								pParamDeclarator->m_pType->m_pPointerTo->m_pClass = pDeclarator->m_pOwnerScope->m_pClass;
#if 0	// Had this
								pParamDeclarator->m_spOffset = -12;

								for (int i = 0; i < pType->m_pFunction->m_parameters.size(); i++)
								{
									pType->m_pFunction->m_parameters[i]->m_spOffset -= 4;
								}
#endif
								pType->m_pFunction->m_parameters.insert(pType->m_pFunction->m_parameters.begin(), pParamDeclarator);
							}
						}
					}

					BOOL bFunctionBody = nontypedef_declarator(pDeclarator, pInnermostClass, pScope);

					if (bFunctionBody)
					{
						return TRUE;
					}
				}
			}

			/*
			if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
			{
				GetToken();
				printf("");
				assignment_expression(pInnermostClass, pScope);
			}
			*/

			if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
			{
				GetToken();
				continue;
			}
			break;
		}
/*			if (curtok->type == CToken::tok_ident && !strcmp(curtok->ident, "RPC_IF_CALLBACK_FN"))
			{
				MessageBeep(-1);
			}
*/
		EatSymbol(';');

		/*
		if (!declarator(pFunction->m_pDeclarator, pScope))
		{
		}

		else
		{
			pGlobal->m_declarations.push_back(pFunction);
		}
		*/
	}

	return TRUE;
}

void CCPPCompiler::template_declaration(CClass* pInnermostClass, CScope* pScope)
{
	if (curtok->pkw->n == KW_EXPORT)
	{
		GetToken();
	}

	if (curtok->type != CToken::tok_keyword || curtok->pkw->n != KW_TEMPLATE)
	{
		pPP->jfatalerror("expected template after export");
	}
	GetToken();

//	CScope* pScope2 = new CScope;
//	pScope2->m_pParentScope = pScope;

	CTemplate* pTemplate = new CTemplate;

	CScope* pDeclarationScope = new CScope;
	pDeclarationScope->m_pParentScope = pScope;//2;

	EatSymbol('<');
	bInTemplateArg = TRUE;

	if (curtok->type != CToken::tok_symbol || curtok->symbol != '>')
	{
		while (!pPP->_eof())
		{
			CTemplateParameter* pTemplateParameter = template_parameter(pInnermostClass, pDeclarationScope);
			ASSERT(pTemplateParameter);

			pTemplate->m_parameters.push_back(pTemplateParameter);

			if (curtok->type == CToken::tok_symbol && curtok->symbol == ',')
			{
				GetToken();
				continue;
			}
			break;
		}
	}
	else
	{
		printf("");
	}

	EatSymbol('>');
	bInTemplateArg = FALSE;

	pDeclarationScope->m_pTemplate = pTemplate;

	declaration(pGlobal, pInnermostClass, pDeclarationScope, -1/*linkage*/, pTemplate);

#if 0
	typemap::iterator typei = pDeclarationScope->m_types.begin();

	Type* pType = (*typei).second;

	pTemplate->m_pType = pType;

	pGlobal->m_templates.insert(templatemap::value_type(pTemplate->m_pType->m_name, pTemplate));

	ASSERT(pType->m_sizeof != 0);
	pScope->m_types.insert(typemap::value_type(pType->m_name, pType));
#endif

//	delete pScope2;
}

BOOL CCPPCompiler::declaration(CGlobal* pGlobal, CClass* pInnermostClass, CScope* pScope, int linkage, CTemplate* pParentTemplate/*= NULL*/)
{
	// part of block-declaration
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_ASM)
	{
		pPP->jfatalerror("asm not yet supported");
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW___ASM)
	{
		EatSymbol('{');
		EatSymbol('}');
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_NAMESPACE)
	{
		GetToken();

		CNamespace* pNamespace = NULL;

		if (curtok->type == CToken::tok_ident)
		{
			std::string ident = curtok->ident;
			GetToken();

			namespacemap::iterator ni = pScope->m_namespaces.find(ident.c_str());
			if (ni != pScope->m_namespaces.end())
			{
				pNamespace = (*ni).second;
			}
			else
			{
				pNamespace = new CNamespace;
				pNamespace->m_pParentNamespace = pGlobal->m_pNamespace;
				pNamespace->m_pScope = T_Scope();
				pNamespace->m_pScope->m_pParentScope = pScope;
				pNamespace->m_name = ident;

				pScope->m_namespaces.insert(namespacemap::value_type(ident, pNamespace));
			}
		}

		EatSymbol('{');
		printf("%s{%d\n", pNamespace->m_name.c_str(), pPP->m_pFile->m_line);

		// {
		if (curtok->type != CToken::tok_symbol || curtok->symbol != '}')
		{
			namespace_body(pGlobal, pInnermostClass, pNamespace->m_pScope, linkage);
		}

		EatSymbol('}');
		printf("} // namespace %s\n", pNamespace->m_name.c_str());
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_USING)
	{
		GetToken();

		pPP->jerror("using not yet supported");

		if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_NAMESPACE)
		{
			GetToken();

			std::string _typename = curtok->ident;
			GetToken();
		}
		else
		{
			std::string _typename = curtok->ident;
			GetToken();
		}

		EatSymbol(';');
	}
	else if (curtok->type == CToken::tok_keyword && (
				curtok->pkw->n == KW_EXPORT ||
				curtok->pkw->n == KW_TEMPLATE))
	{
		template_declaration(pInnermostClass, pScope);
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == ';')
	{
		GetToken();
	}
	else
	{
		int storageClassKW = -1;

		if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_EXTERN)
		{
		//	linkage_specification(pGlobal, pInnermostClass, pScope);
			GetToken();

			if (curtok->type == CToken::tok_string)	// linkage specification
			{
				std::string strlinkage = curtok->string;
				GetToken();

				int linkage;

				if (!strcmp(strlinkage.c_str(), "C"))
				{
					linkage = LINKAGE_EXTERN_C;
				}
				else if (!strcmp(strlinkage.c_str(), "C++"))
				{
					linkage = LINKAGE_EXTERN_CPP;
				}
				else
				{
					char msg[512];
					sprintf(msg, "'%s' : unknown linkage, should be \"C\" or \"C++\"", strlinkage.c_str());
					pPP->jerror(msg);
				}

				if (curtok->type == CToken::tok_symbol && curtok->symbol == '{')	// }
				{
					GetToken();

					// {
					if (curtok->type != CToken::tok_symbol || curtok->symbol != '}')
					{
						declaration_seq(pGlobal, pInnermostClass, pScope, linkage);
					}

					// {
					EatSymbol('}');
				}
				else
				{
					declaration(pGlobal, pInnermostClass, pScope, linkage);
				}
				return FALSE;
			}
			else
			{
				// extern storage class
				storageClassKW = KW_EXTERN;
			}
		}

		if (simple_declaration_or_function_definition(pGlobal, pInnermostClass, pScope, linkage, storageClassKW, pParentTemplate))
		{
			return TRUE;
		}
		else
		{
			if (curtok->type == CToken::tok_ident)
			{
				char msg[512];
				sprintf(msg, "'%s' : Expected type", curtok->ident);
				pPP->jerror(msg);
			}
			else
			{
				pPP->jerror("Expected type");
			}
			GetToken();
		}
	}

	return FALSE;
}

/*
declaration-seq:
	declaration
	declaration-seq declaration
*/
void CCPPCompiler::declaration_seq(CGlobal* pGlobal, CClass* pInnermostClass, CScope* pScope, int linkage)
{
	while (!pPP->_eof())
	{
		declaration(pGlobal, pInnermostClass, pScope, linkage);
		//	return FALSE;

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
		{
			break;
		}

	//	GetToken();
	}
}

/*
translation-unit:
	declaration-seqopt
*/
void CCPPCompiler::translation_unit(CGlobal* _pGlobal, PP::CPreprocessor* argPP)
{
	pPP = argPP;
	pGlobal = _pGlobal;

	argPP->Define("__cplusplus", 199711L);
	argPP->Define("__STDC__", 1);
	argPP->Define("_WCHAR_T_DEFINED");
	argPP->Define("_INTEGRAL_MAX_BITS", 64);

	//CScope scope;
	pGlobal->m_pNamespace = new CNamespace;
	pGlobal->m_pNamespace->m_pScope = T_Scope();

/*
	void* operator new(std::size_t) throw(std::bad_alloc);
	void* operator new[](std::size_t) throw(std::bad_alloc);
	void operator delete(void*) throw();
	void operator delete[](void*) throw();
*/
	// void* operator new(std::size_t) throw(std::bad_alloc);
	{
		CDeclarator* pDeclarator = new CDeclarator;
		pDeclarator->m_name = "operator_new";
		pDeclarator->m_pType = new Type(type_function);
		pDeclarator->m_pType->m_pFunction = new CFunction;
		pDeclarator->m_pType->m_pFunction->m_pReturnType = new Type(type_pointer, sizeof_pointer);
		pDeclarator->m_pType->m_pFunction->m_pReturnType->m_pPointerTo = new Type(type_void);

		// parameters
		{
			CDeclarator* pArgument = new CDeclarator;
			pArgument->m_pType = new Type(type_unsigned_int, 4);
			pDeclarator->m_pType->m_pFunction->m_parameters.push_back(pArgument);
		}

		pGlobal->m_pNamespace->m_pScope->AddReferenceDeclarator(new CDeclaratorReference(pDeclarator));
	}

	// void operator delete(void*) throw();
	{
		CDeclarator* pDeclarator = new CDeclarator;
		pDeclarator->m_name = "operator_delete";
		pDeclarator->m_pType = new Type(type_function);
		pDeclarator->m_pType->m_pFunction = new CFunction;
		pDeclarator->m_pType->m_pFunction->m_pReturnType = new Type(type_void);

		// parameters
		{
			CDeclarator* pArgument = new CDeclarator;
			pArgument->m_pType = new Type(type_pointer, sizeof_pointer);
			pArgument->m_pType->m_pPointerTo = new Type(type_void);

			pDeclarator->m_pType->m_pFunction->m_parameters.push_back(pArgument);
		}
		pGlobal->m_pNamespace->m_pScope->AddReferenceDeclarator(new CDeclaratorReference(pDeclarator));
	}

	GetToken();
	declaration_seq(pGlobal, NULL, pGlobal->m_pNamespace->m_pScope, LINKAGE_EXTERN_CPP);
}

//////////////////////////////////////////////////////////////
// CDeclarator

// ABI

/*
<builtin-type> ::= v	# void
		 ::= w	# wchar_t
		 ::= b	# bool
		 ::= c	# char
		 ::= a	# signed char
		 ::= h	# unsigned char
		 ::= s	# short
		 ::= t	# unsigned short
		 ::= i	# int
		 ::= j	# unsigned int
		 ::= l	# long
		 ::= m	# unsigned long
		 ::= x	# long long, __int64
		 ::= y	# unsigned long long, __int64
		 ::= n	# __int128
		 ::= o	# unsigned __int128
		 ::= f	# float
		 ::= d	# double
		 ::= e	# long double, __float80
		 ::= g	# __float128
		 ::= z	# ellipsis
		 ::= u <source-name>	# vendor extended type

*/

void DemangleName(const char* mname)
{
	const char* p = NULL;

	if (*p == 'P')
	{
		Type* pType = new Type;
		pType->m_type = type_pointer;
	}
	else
	{
	}
}

/*
<operator-name> ::= nw	# new           
		  ::= na	# new[]
		  ::= dl	# delete        
		  ::= da	# delete[]      
		  ::= ps # + (unary)
		  ::= ng	# - (unary)     
		  ::= ad	# & (unary)     
		  ::= de	# * (unary)     
		  ::= co	# ~             
		  ::= pl	# +             
		  ::= mi	# -             
		  ::= ml	# *             
		  ::= dv	# /             
		  ::= rm	# %             
		  ::= an	# &             
		  ::= or	# |             
		  ::= eo	# ^             
		  ::= aS	# =             
		  ::= pL	# +=            
		  ::= mI	# -=            
		  ::= mL	# *=            
		  ::= dV	# /=            
		  ::= rM	# %=            
		  ::= aN	# &=            
		  ::= oR	# |=            
		  ::= eO	# ^=            
		  ::= ls	# <<            
		  ::= rs	# >>            
		  ::= lS	# <<=           
		  ::= rS	# >>=           
		  ::= eq	# ==            
		  ::= ne	# !=            
		  ::= lt	# <             
		  ::= gt	# >             
		  ::= le	# <=            
		  ::= ge	# >=            
		  ::= nt	# !             
		  ::= aa	# &&            
		  ::= oo	# ||            
		  ::= pp	# ++            
		  ::= mm	# --            
		  ::= cm	# ,             
		  ::= pm	# ->*           
		  ::= pt	# ->            
		  ::= cl	# ()            
		  ::= ix	# []            
		  ::= qu	# ?             
		  ::= st	# sizeof (a type)
		  ::= sz	# sizeof (an expression)
		  ::= cv <type>	# (cast)        
		  ::= v <digit> <source-name>	# vendor extended operator
*/

/*
<builtin-type> ::= v	# void
		 ::= w	# wchar_t
		 ::= b	# bool
		 ::= c	# char
		 ::= a	# signed char
		 ::= h	# unsigned char
		 ::= s	# short
		 ::= t	# unsigned short
		 ::= i	# int
		 ::= j	# unsigned int
		 ::= l	# long
		 ::= m	# unsigned long
		 ::= x	# long long, __int64
		 ::= y	# unsigned long long, __int64
		 ::= n	# __int128
		 ::= o	# unsigned __int128
		 ::= f	# float
		 ::= d	# double
		 ::= e	# long double, __float80
		 ::= g	# __float128
		 ::= z	# ellipsis
		 ::= u <source-name>	# vendor extended type
*/

std::string MangleName(Type* pType)
{
	std::string mname;

	if (pType->m_type == type_pointer)
	{
		mname = "P";
		mname += MangleName(pType->m_pPointerTo);
	}
	else
	{
		switch (pType->m_type)
		{
		case type_void:						mname += "v";	break;
		case type_wchar:						mname += "w";	break;
		case type_bool:						mname += "b";	break;
		case type_char:						mname += "c";	break;
		case type_signed_char:				mname += "a";	break;
		case type_unsigned_char:			mname += "h";	break;
		case type_int:							mname += "i";	break;
		case type_short_int:					mname += "s";	break;
		case type_long_int:					mname += "l";	break;
		case type_unsigned_int:				mname += "j";	break;
		case type_unsigned_short_int:		mname += "t";	break;
		case type_unsigned_long_int:		mname += "m";	break;

		default:
			ASSERT(0);
		}
	}

	return mname;
}
#endif

/*
<mangled-name> ::= _Z <encoding>
    <encoding> ::= <function name> <bare-function-type>
	       ::= <data name>
	       ::= <special-name>

*/
std::string cpp::CDeclarator::MangleName()
{
	std::string mname;

	char buf[512];
	sprintf(buf, "_Z%d%s", m_name.length(), m_name.c_str());
	mname = buf;

#if 0
	if (m_pFunction)
	{
		if (m_pFunction->m_parameters.size() == 0)
		{
			mname += "v";	// void
		}
		else
		{
			for (int i = 0; i < m_pFunction->m_parameters.size(); i++)
			{
				Type* pType = NULL;
			}
		}
	}
#endif

	return mname;
}

#if 0
//////////////////////////////////////////////////////////////
// CMember

BOOL CMember::IsEqual(CMember* pOther)
{
	if (m_offset != pOther->m_offset)
		return FALSE;

	if (!m_pDeclarator->IsEqual(pOther->m_pDeclarator))
		return FALSE;

	return TRUE;	// They're equal
}
#endif

//////////////////////////////////////////////////////////////
// CExpression

#if 0
BOOL CExpression::IsEqual(CExpression* pOther)
{
	if (tok.type != pOther->tok.type)
		return FALSE;

	if (m_pType)
	{
		if (pOther->m_pType == NULL)
			return FALSE;

		if (!m_pType->IsEqual(pOther->m_pType))
			return FALSE;
	}
	else if (pOther->m_pType)
	{
		return FALSE;
	}

	if (m_pDeclaratorRef != pOther->m_pDeclaratorRef)
		return FALSE;
	
	if (left)
	{
		if (pOther->left == NULL)
			return FALSE;

		if (!left->IsEqual(pOther->left))
			return FALSE;
	}
	else
	{
		if (pOther->left)
			return FALSE;
	}

	if (right)
	{
		if (pOther->right == NULL)
			return FALSE;

		if (!right->IsEqual(pOther->right))
			return FALSE;
	}
	else
	{
		if (pOther->right)
			return FALSE;
	}

	return TRUE;	// They're equal
}
#endif

//////////////////////////////////////////////////////////////////
// CScope

#if 0
void CScope::AddType(CCPPCompiler* pCompiler, Type* pType)
{
	pType->m_pNamedType->m_location.m_filepath = pCompiler->pPP->m_pFile->m_filepath;
	pType->m_pNamedType->m_location.m_line = pCompiler->pPP->m_pFile->m_line;
	ASSERT(pType->m_sizeof != 0);

	/*
	if (pType->m_name == "CComVariant")
	{
		printf("\nCComVariant\n\n");
	}
	*/
	if (pType->m_type == type_class || pType->m_type == type_enum)
	{

		m_types.insert(typemap::value_type(pType->m_pNamedType->m_name, pType));
	}
	else if (pType->m_type == type_typedef)
	{
		m_types.insert(typemap::value_type(pType->m_pNamedType->m_name, pType));
	}
	else
	{
		ASSERT(0);
	}
#if 0
	else
	{
		m_types.insert(typemap::value_type(pType->m_name, pType));
	}
#endif
}
#endif

///////////////////////////////////////////////////////////////////////
// CFunctionBody

#if 0
void CFunctionBody::Evaluate(CCPPCompiler* pCompiler, CDeclarator* pFunctionDecl)
{
	for (int i = 0; i < m_statements.size(); i++)
	{
		CStatement* pStmt = m_statements[i];

		pStmt->Evaluate(pCompiler, pFunctionDecl);
	}
}

//////////////////////////////////
// CReturnStatement

void CReturnStatement::Evaluate(CCPPCompiler* pCompiler, CDeclarator* pFunctionDecl)
{
	ASSERT(0);
#if 0
	if (m_expr)
	{
		//pCompiler->ExpressionType(m_expr, NULL);
		//m_expr = pCompiler->Reduce(m_expr, NULL);

		if (m_expr->m_pType)
		{
			ASSERT(pFunctionDecl->m_pType->m_type == type_function);

			pCompiler->ConvertExpressionType(m_expr, pFunctionDecl->m_pType->m_pFunction->m_pReturnType);

			if (!m_expr->m_pType->IsEqual(pFunctionDecl->m_pType->m_pFunction->m_pReturnType))
			{
				//if (pArgExpr->GetPointerLevel() >= 
				std::string str0 = m_expr->m_pType->toString();
				std::string str1 = pFunctionDecl->m_pType->m_pFunction->m_pReturnType->toString();

				std::string fstr = pFunctionDecl->toString();

				char msg[1024];
				sprintf(msg, "'%s' return type: incompatible types - from '%s' to '%s'",
					fstr.c_str(),//pExpr->left->tok.ident,
					//pDeclarator->m_pFunction->m_parameters.size()-i,
					str0.c_str(), str1.c_str());
				pCompiler->pPP->jerror(msg);
			}
		}
		else
		{
			pCompiler->pPP->jerror("return: expression had no type?");
		}
	}
#endif
}
/*
CClass* A_ClassTy()
{
}

CDeclaratorA_Name
*/
#endif