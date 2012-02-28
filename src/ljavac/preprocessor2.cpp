#include "StdAfx.h"
#include "preprocessor.h"

double makeflt(long intpart, double frac, int exp)
{
	double val;
	double mod, mod10;//, mod100;

	val = intpart + frac;
	if (exp > 0)
	{
		mod = 1e1;
		mod10 = 1e10;
#if IEEE_FP
		mod100 = 1e100;
#endif
	}
	else if (exp < 0)
	{
		mod = 1e-1;
		mod10 = 1e-10;
#if IEEE_FP
		mod100 = 1e-100;
#endif
		exp = -exp;
	}
#if IEEE_FP
	while (exp >= 100)
	{
		val *= mod100;
		exp -= 100;
	}
#endif
	while (exp >= 10)
	{
		val *= mod10;
		exp -= 10;
	}

	while (exp--)
	{
		val *= mod;		/* slow and dirty */
	}

	return val;
}

namespace PP
{
enum
{
	PP_IF,
	PP_ELIF,
	PP_ELSE,
	PP_ENDIF,
	PP_IFDEF,
	PP_IFNDEF,
	PP_INCLUDE,
	PP_DEFINE,
	PP_UNDEF,
	PP_LINE,
	PP_ERROR,
	PP_PRAGMA,
	PP_MAX
};

char* pp_kws[] =
{
	"if",
	"elif",
	"else",
	"endif",
	"ifdef",
	"ifndef",
	"include",
	"define",
	"undef",
	"line",
	"error",
	"pragma",
};

int _getnumber(CPreprocessor* pPP)
{
	ATLASSERT(0);
	return 0;
}

double getfrac(CPreprocessor* pPP)
{
	double dig = 0.1;
	double val = 0;

	//OLECHAR* p = *s;

	while (!pPP->_eof())
	{
		int c = pPP->_getc();//WCHAR c = *p;
		if (!iswdigit(c))
		{
			pPP->_ungetc(c);
			break;
		}
		val += dig * (c - L'0');

		dig = 0.1 * dig;

		//p++;
	}

	//*s = p;

	return val;
}

int lookexp(CPreprocessor* pPP/*, long intpart, double frac*/)
{
	int c;
	int exp;

	//OLECHAR *p = *s;

	int minus = 0;

	c = pPP->_getc();//*p++;
	if (towlower(c) != 'e')
	{
		pPP->_ungetc(c);
		return 0;
	}

	c = pPP->_getc();//*p++;
	if (c == '-')
	{
		minus = 1;
		//c = mygetchar();
		c = pPP->_getc();
	}
	else if (c == '+')
	{
		//c = mygetchar();
	}

	//c = *p++;
	if (c >= '0' && c <= '9')
	{
		exp = _getnumber(pPP);
	}
	else
	{
		pPP->_ungetc(c);
		return 0;
		//exp = 0;
		//p--;//myungetc(c);
	}

	if (minus)
		exp = -exp;

//	*s = p;

	return exp;
}

int CFile::_getc2()
{
	int c = fgetc(m_fp);
	m_lastc = c;

	if (c == '\n')
	{
		m_line++;
	}
	return c;
}

int CFile::_getc()
{
	int c = _getc2();

	// Each instance of a new-line character and an immediately preceding backslash character is deleted,
	// splicing physical source lines to form logical source lines
	while (c == '\\')
	{
		int c2 = _getc2();
		if (c2 == '\r')
		{
			int c3 = _getc2();
			if (c3 == '\n')
			{
				c = _getc2();	// character on the next line
			}
		}
		else if (c2 == '\n')
		{
			c = _getc2();	// character on the next line
		}
		else
		{
			_ungetc(c2);
		//	c = c2;
			return c;
		}
	}
	return c;
}

void CFile::_ungetc(int c)
{
//	ATLASSERT(c == m_lastc);
	if (c == '\n')
	{
		m_line--;
	}
	ungetc(c, m_fp);
}

void CPreprocessor::Define(CDefine* pDefine)
{
	pDefine->m_location.m_filepath = m_pFile->m_filepath;
	pDefine->m_location.m_line = m_pFile->m_line;
//	m_defines.push_back(pDefine);
	m_defines.insert(macromap::value_type(pDefine->m_name, pDefine));
}

CDefine* CPreprocessor::Define(const char* name)
{
	macromap::iterator pDefine2 = Find(name);
	if (pDefine2 != m_defines.end())
	{
		char msg[512];
		sprintf(msg, "Redefinition of macro '%s' : first seen :\n%s(%d)",
			name, (*pDefine2).second->m_location.m_filepath.c_str(), (*pDefine2).second->m_location.m_line);

		jerror(msg);
	//	pDefine->m_replacementList.clear();

		return NULL;
	}
	else
	{
		CDefine* pDefine;
		pDefine = new CDefine;
		pDefine->m_name = name;

		pDefine->m_location.m_filepath = m_pFile->m_filepath;
		pDefine->m_location.m_line = m_pFile->m_line;
	//	m_defines.push_back(pDefine);
		m_defines.insert(macromap::value_type(pDefine->m_name, pDefine));

		return pDefine;
	}
}

CDefine* CPreprocessor::Define(const char* name, long int32)
{
	macromap::iterator pDefine2 = Find(name);
	if (pDefine2 != m_defines.end())
	{
		char msg[512];
		sprintf(msg, "Redefinition of macro '%s' : first seen :\n%s(%d)",
			name, (*pDefine2).second->m_location.m_filepath.c_str(), (*pDefine2).second->m_location.m_line);

		jerror(msg);
	//	pDefine->m_replacementList.clear();

		return NULL;
	}
	else
	{
		CDefine* pDefine;
		pDefine = new CDefine;
		pDefine->m_name = name;

		CToken tok;
		tok.type = CToken::tok_integer;
		tok.int32 = int32;

		pDefine->m_replacementList.push_back(tok);

		pDefine->m_location.m_filepath = m_pFile->m_filepath;
		pDefine->m_location.m_line = m_pFile->m_line;
	//	m_defines.push_back(pDefine);
		m_defines.insert(macromap::value_type(pDefine->m_name, pDefine));

		return pDefine;
	}
}

void CPreprocessor::Undef(const char* name)
{
	m_defines.erase(name);
	/*
	for (int i = 0; i < m_defines.size(); i++)
	{
		if (!strcmp(m_defines[i]->m_name.c_str(), name))
		{
			m_defines.erase(&m_defines[i]);
		}
	}
	*/
}

BOOL CPreprocessor::IfDef(const char* name)
{
	if (m_defines.find(name) != m_defines.end())
		return TRUE;
	else
		return FALSE;
}

BOOL CDefine::IsEqual(CDefine* pOther)
{
	ATLASSERT(m_name == pOther->m_name);	// Shouldn already have been checked against this

	if (m_bFunctionLike != pOther->m_bFunctionLike)
		return FALSE;

	if (m_argNames.size() != pOther->m_argNames.size())
		return FALSE;

	if (m_replacementList.size() != pOther->m_replacementList.size())
		return FALSE;

	for (int i = 0; i < m_replacementList.size(); i++)
	{
		if (m_replacementList[i].type != pOther->m_replacementList[i].type)
			return FALSE;

		if (m_replacementList[i].type == CToken::tok_ident || pOther->m_replacementList[i].type == CToken::tok_string)
		{
			if (strcmp(m_replacementList[i].ident, pOther->m_replacementList[i].ident))
				return FALSE;
		}
	}

	return TRUE;	// They're equal
}

// Argument substitution
int CMacroInvocation::SubstituteArguments(std::vector<std::vector<CToken> >& argTokenList)
{
	m_string = "";//" ";

	//CToken* pprevtok = NULL;

	for (int i = 0; i < m_pMacro->m_replacementList.size(); i++)
	{
		CToken* ptok = &m_pMacro->m_replacementList[i];

		CToken* pnexttok;
		if (i < m_pMacro->m_replacementList.size()-1)
			pnexttok = &m_pMacro->m_replacementList[i+1];
		else
			pnexttok = NULL;

		if (ptok->type == CToken::tok_symbol && ptok->symbol == '##')
		{
		//	m_string.erase(m_string.end()-1);
			if (i == 0)
				return -1;
			else if (pnexttok == NULL)
				return -2;

			std::string str;

			int arg = GetArg(pnexttok->ident);
			if (arg >= 0)
			{
				if (argTokenList.size() > arg)
				{
					std::vector<CToken>& tokenlist = argTokenList[arg];
					for (int j = 0; j < tokenlist.size(); j++)
					{
						CToken* ptok = &tokenlist[j];
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

		if (ptok->type == CToken::tok_ident)
		{
			int arg = GetArg(ptok->ident);
			if (arg >= 0)
			{
				if (argTokenList.size() > arg)
				{
					std::vector<CToken>& tokenlist = argTokenList[arg];
					for (int j = 0; j < tokenlist.size(); j++)
					{
						CToken* ptok = &tokenlist[j];
						m_string += ptok->toString();
					}
				}
			}
			else
			{
				m_string += ptok->toString();
			}
		}
		else if (ptok->type == CToken::tok_symbol && ptok->symbol == '#')
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

	return 0;	// success
}

#if 0
void CPreprocessor::skipspaces()
{
	while (!m_pFile->_eof())
	{
		int c = curtokpp->symbol;//m_pFile->_getc();
		if (!(curtokpp->type == CToken::tok_char && (c == ' ' || c == '\t')))
		{
			//m_pFile->_ungetc(c);
			break;
		}
		GetToken4();
	}

#if 0
// newlines are retained
	while (!m_pFile->_eof())
	{
		int c = m_pFile->_getc();
		if (!(c == ' ' || c == '\t'))
		{
			m_pFile->_ungetc(c);
			break;
		}
	}
#endif
}
#endif

int CPreprocessor::_getc()
{
	if (m_pMacroInvocation)
	{
	//	*curtokpp = m_pMacroInvocation->m_tokenList[m_pMacroInvocation->m_cur++];

		// Keep backing out of macro 
		while (m_pMacroInvocation->_eof())
		{
		//	printindent(m_pMacroInvocation);
		//	printf("%s)\n", m_pMacroInvocation->m_pMacro->m_name.c_str());

			CMacroInvocation* pPrev = m_pMacroInvocation->m_pPrev;
			delete m_pMacroInvocation;
			m_pMacroInvocation = pPrev;

			if (m_pMacroInvocation == NULL)
			{
				break;
			}

		//	*curtokpp = m_pMacroInvocation->m_tokenList[m_pMacroInvocation->m_cur++];
		}

#if 0
		if (m_pMacroInvocation)
		{
			*curtokpp = *m_pMacroInvocation->GetToken();//m_tokenList[m_pMacroInvocation->m_cur++];
		//	printf("\"%s\"\n", curtokpp->ident);
			return curtokpp;
		}
#endif
	}

	if (m_pMacroInvocation)
	{
		return m_pMacroInvocation->_getc();
	}
	else
	{
		return m_pFile->_getc();
	}
}

void CPreprocessor::_ungetc(int c)
{
	if (m_pMacroInvocation)
	{
		m_pMacroInvocation->_ungetc();
	}
	else
	{
		m_pFile->_ungetc(c);
	}
}

BOOL CPreprocessor::_eof()
{
	if (m_pMacroInvocation)
	{
		if (!m_pMacroInvocation->_eof())
			return FALSE;
	}

	return m_pFile->_eof();
}

int CPreprocessor::getNextNonSpace(int c)
{
// skip all spaces and comments

	while (/*c == ' ' || c == '\t' || c == '\v' || c == '\f' ||*/ c == '/')
	{
	//	int c = _getc();

		/*
		if (!(c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '/'))
		{
			break;
			//_ungetc();
		}
		*/

		if (c == '/')	// could be beginning of comment
		{
			int c2 = _getc();
			if (c2 == '*')	// multi-line comment
			{
				bool okay = false;
				while (!_eof())
				{
					c2 = _getc();
					if (c2 == '*')
					{
						int c3 = _getc();
						if (c3 == '/')
						{
							okay = true;
							break;
						}
						else
							_ungetc(c3);
					}
				}

				if (!okay)
				{
					jfatalerror("Unexpected end of file, unterminated comment");
				}

				c = _getc();
			}
			else if (c2 == '/')	// single-line comment
			{
				while (!_eof())
				{
					c2 = _getc();
				//	printf("%c", c2);
					if (c2 == '\r')
					{
						int c3 = _getc();
						ATLASSERT(c3 == '\n');
						_ungetc(c3);
						break;
					}
					else if (c2 == '\n')
					{
						_ungetc(c2);
						break;
					}
				}
				c = _getc();
				ATLASSERT(c == '\n' || c == -1);
			}
			else
			{
				_ungetc(c2);
				break;
			}
		}
		else	// white-space
		{
			c = _getc();
		}
	}

	return c;
}

CToken* CPreprocessor::GetToken4()
{

#if 0
	if (m_pMacroInvocation)
	{
		if (!m_pMacroInvocation->m_tokens.empty())
		{
			*curtokpp = m_pMacroInvocation->m_tokens.top();
			m_pMacroInvocation->m_tokens.pop();
			return curtokpp;
		}
	}
	else
	{
		if (!m_pFile->m_tokens.empty())
		{
			*curtokpp = m_pFile->m_tokens.top();
			m_pFile->m_tokens.pop();
			return curtokpp;
		}
	}
#endif

	{
		int c = _getc();
	//	printf("%c", c);

		CToken token;

		while (c == EOF)
		{
			if (m_pFile->m_pPrev == NULL)
			{
				break;
			}

			CFile* pPrev = m_pFile->m_pPrev;
			delete m_pFile;
			m_pFile = pPrev;

			c = m_pFile->_getc();
		}

	// trigraph sequences
		if (c == '?')
		{
			int c2 = _getc();
			if (c2 == '?')
			{
				int c3 = _getc();
				switch (c3)
				{
				case '=':	c = '#';		break;
				case '/':	c = '\\';	break;
				case '\'':	c = '^';		break;
				case '(':	c = '[';		break;
				case ')':	c = ']';		break;
				case '!':	c = '|';		break;
				case '<':	c = '{';		break;
				case '>':	c = '}';		break;
				case '-':	c = '~';		break;
				default:
					jfatalerror("Unrecognized trigraph sequence");
				}
			}
			else
			{
				_ungetc(c2);
			}
		}

		c = getNextNonSpace(c);

		if (c == ' ' || c == '\t' || c == '\v' || c == '\f')
		{
			token.type = CToken::tok_space;

			while  (!_eof())
			{
				c = _getc();
				if (!(c == ' ' || c == '\t' || c == '\v' || c == '\f'))
				{
					_ungetc(c);
					break;
				}
			}
		}
		else if (isalpha(c) || c == '_')
		{
			std::string ident;
			ident += c;
			while (!_eof())
			{
				c = _getc();
				if (!(isalnum(c) || c == '_'))
				{
					_ungetc(c);
					break;
				}

				ident += c;
			}

			token.type = CToken::tok_ident;
			token.identlen = ident.length();
			token.ident = strdup(ident.c_str());
		}
		else if (c >= '0' && c <= '9')
		{
			long int32;
			int c2 = -1;
			if (c == '0')
			{
				c2 = _getc();
				if (c2 == 'x')	// hex number
				{
					int32 = 0;

					while (!_eof())
					{
						c = _getc();
						if (!((c >= '0' && c <= '9') ||
							(c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
						{
							_ungetc(c);
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

					token.type = CToken::tok_integer;
					token.int32 = int32;
				}
				else
				{
					_ungetc(c2);
				}
			}

			if (c2 != 'x')
			{
				int32 = c - '0';
				while (!_eof())
				{
					c = _getc();
					if (!(c >= '0' && c <= '9'))
					{
					//	_ungetc(c);
						break;
					}

					int32 *= 10;
					int32 += c - '0';
				}

			// get fraction
				int exp = 0;
				double fraction;

				//int c = _getc();
				if (c == '.')
				{
					//p++;
					fraction = getfrac(this);

				// get exp
					exp = lookexp(this);

					double double64 = makeflt(int32, fraction, exp);

					token.type = CToken::tok_double;
					token.double64 = double64;
				}
				else
				{
					fraction = 0;
					_ungetc(c);

					{
						int c = _getc();
						if (c == 'l' || c == 'L')
						{
						}
						else
						{
							_ungetc(c);
						}
					}

					token.type = CToken::tok_integer;
					token.int32 = int32;
				}
			}
			
		}
		else if (c == '(' ||
			c == ')')
		{
			token.type = CToken::tok_symbol;
			token.symbol = c;
		}
		else if (c == '!')
		{
			int c2 = _getc();
			if (c2 == '=')	// !=
			{
				token.type = CToken::tok_symbol;
				token.symbol = (c<<8) | c2;
			}
			else
			{
				_ungetc(c2);
				token.type = CToken::tok_symbol;
				token.symbol = c;
			}
		}
		else if (c == '<' || c == '>')
		{
			int c2 = _getc();

			if (c2 == c)	// << , >>
			{
				token.type = CToken::tok_symbol;
				token.symbol = (c<<8) | c2;
			}
			else if (c2 == '=')	// <= , >=
			{
				token.type = CToken::tok_symbol;
				token.symbol = (c<<8) | c2;
			}
			else
			{
				_ungetc(c2);
				token.type = CToken::tok_symbol;
				token.symbol = c;
			}
		}
		else if (c == '+' ||
					c == '-' ||
					c == '=' ||
					c == '&' ||
					c == '|' ||
					c == '#')
		{
			int c2 = _getc();

			if (c == '-' && c2 == '>')	// ->
			{
				token.type = CToken::tok_symbol;
				token.symbol = (c<<8) | c2;
			}
			else if (c2 == c)	// ++ , -- , ==, '&&', '||'
			{
				token.type = CToken::tok_symbol;
				token.symbol = (c<<8) | c2;
			}
			else if ((c == '+' || c == '-' || c == '&' || c == '|')
						&& c2 == '=')	// +=, -=
			{
				token.type = CToken::tok_symbol;
				token.symbol = (c<<8) | c2;
			}
			else
			{
				_ungetc(c2);
				token.type = CToken::tok_symbol;
				token.symbol = c;
			}
		}
		else if (c == '\r')
		{
			int c2 = _getc();
			ATLASSERT(c2 ==  '\n');

			token.type = CToken::tok_symbol;
			token.symbol = c2;
		}
		else if (c == '\n')
		{
			token.type = CToken::tok_symbol;
			token.symbol = c;
		}
		else
		{
			token.type = CToken::tok_char;
			token.symbol = c;
		}

		*curtokpp = token;
	}

	return curtokpp;
}

// Get next token, without preprocessing or macro expansion
CToken* CPreprocessor::GetToken3()
{
	GetToken4();
	while (curtokpp->type == CToken::tok_space)
	{
		GetToken4();
	}

	return curtokpp;
}

// Get next token with preprocessing
CToken* CPreprocessor::GetToken2()
{
	GetToken3();

// If we've just gotten on a new line, check for preprocessor directive
	if (m_bNewLine)
	{
		while (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '#')
		{
			GetToken3();

			directive();
		}

		m_bNewLine = FALSE;
	}

	if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '\n')
	{
		m_bNewLine = TRUE;
	//	return GetToken();
	}

	return curtokpp;
}

#if 0
void CFile::UngetToken(CToken* ptok)
{
	m_tokens.push(*ptok);
}
#endif

CToken* CPreprocessor::TryMacro(macromap::iterator pDefine)
{
//	long pos = ftell(m_pFile->m_fp);

	CToken mname = *curtokpp;

	if (!strcmp(mname.ident, "_VARIANT_BOOL"))
	{
		printf("");
	}

	/*
	// Skip spaces
	int c;
	while (!_eof())
	{
		c = _getc();
		if (c == '\n')	// hm
			m_bNewLine = TRUE;

		if (!isspace(c))
		{
			_ungetc(c);
			break;
		}
	}
	*/
//	SkipSpacesAndComments();

//	GetToken3();

	BOOL bMacro = FALSE;

	if ((*pDefine).second->m_bFunctionLike)
	{
		GetToken();
		//int c = _getc();
		if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '(')
		//if (c == '(')//curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '(')
		{
			bMacro = TRUE;
		}
		else
		{
			printf("");
			return curtokpp;
			//ATLASSERT(0);
			//_ungetc(c);
		}
	}
	else
	{
		bMacro = TRUE;
	}

	if (bMacro)
	{
		/*
		if (m_pMacroInvocation)
			printindent(m_pMacroInvocation);
		printf("(%s\n", mname.ident);
		*/

		std::vector<std::vector<CToken> > argTokenList;

		if ((*pDefine).second->m_bFunctionLike)
		{
			/*
			if (!strcmp(mname.ident, "__declspec"))
			{
				printf("");
			}
			*/
			int argNamesSize = (*pDefine).second->m_argNames.size();

			/*
			if (argNamesSize == 12)
			{
				printf("");
			}
			*/

#if 0
			GetToken3();	// '('
#endif
			GetToken3();
			int paren = 1;

			if (curtokpp->symbol != ')')
			{
				while (!m_pFile->_eof())
				{
					ATLASSERT(paren == 1);

					std::vector<CToken> tokens;

					while (!m_pFile->_eof())
					{
						if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '(')
						{
							paren++;
						}
						else if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == ')')
						{
							paren--;
							if (paren < 1)
							{
								//GetToken4();
								break;
							}
						}
						else if (curtokpp->type == CToken::tok_char && curtokpp->symbol == ',')
						{
							if (paren == 1)
								break;
						}

						tokens.push_back(*curtokpp);
						GetToken4();//GetToken3();
					}
					if (curtokpp->symbol == ',')
						GetToken3();

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

			if (argTokenListSize < argNamesSize)
			{
				char msg[512];
				sprintf(msg, "too few parameters in macro invocation of '%s'", mname.ident);
				jerror(msg);
			}
			else if (argTokenListSize > argNamesSize)
			{
				char msg[512];
				sprintf(msg, "too many parameters in macro invocation of '%s'", mname.ident);
				jerror(msg);
			}

			Expect(')');
		//	GetToken3();
		}

		CMacroInvocation* pMacroInvocation = new CMacroInvocation((*pDefine).second);

		int err = pMacroInvocation->SubstituteArguments(argTokenList);
		if (err != 0)
		{
			if (err == -1)
				jfatalerror("## cannot be the first token in a macro");
			else if (err == -2)
				jfatalerror("## cannot be the last token in a macro");
			else
				jfatalerror("failed to substitute macro arguments");
		}

#if 0
		if (m_pMacroInvocation == NULL)
		{
		//	printf("pushing->'%s'\n", curtokpp->ident);
			m_pFile->UngetToken(curtokpp);
		}
		else
		{
			m_pMacroInvocation->UngetToken(curtokpp);
		}
#endif

		pMacroInvocation->m_pPrev = m_pMacroInvocation;
		m_pMacroInvocation = pMacroInvocation;

		return GetToken();	// Descend into macro
	}
	else
	{
	//	printf("pushing->'%s'\n", curtokpp->ident);
#if 0
		m_pFile->UngetToken(curtokpp);
#endif
		*curtokpp = mname;
	}

	return curtokpp;
}

// Get next token with preprocessing and macro expansion
CToken* CPreprocessor::GetToken()
{
	curtokpp = GetToken2();

	if (curtokpp->type == CToken::tok_ident)
	{
		if (m_pMacroInvocation == NULL || !m_pMacroInvocation->IsInside(curtokpp->ident))
		{
			macromap::iterator pDefine = m_defines.find(curtokpp->ident);
			if (pDefine != m_defines.end())
			{
				curtokpp = TryMacro(pDefine);
			}
		}
	}

	return curtokpp;
}

void CPreprocessor::GetHeaderName()
{
	//while (!m_pFile->_eof())
	{
		int c = curtokpp->symbol;

	// Special handling
		if (c == '"' || c == '<')
		{
			GetToken4();	// No special handling while in string

			CToken token;

			std::string str;

			int line = m_pFile->m_line;
			int eos = (c == '"')? '"': '>';	// end of string

			int c2;
			while (!m_pFile->_eof())
			{
				if (curtokpp->type == CToken::tok_char || curtokpp->type == CToken::tok_symbol)
				{
					c2 = curtokpp->symbol;//m_pFile->_getc();
					//c2 = m_pFile->_getc();
					if (c2 == eos)
					{
					//	ungetc(c2, fpin);
						break;
					}
					str += (char)c2;
				}
				else if (curtokpp->type == CToken::tok_ident)
				{
					str += curtokpp->ident;
				}

				GetToken4();	// No special handling while in string
			}

			if (c2 != eos)
			{
				char msg[256];
				sprintf(msg, "Expected end of string '%c', started(%d)", eos, line);
				jfatalerror(msg);
			}

			token.type = c == '"'? CToken::tok_string: CToken::tok_ltstring;
			token.stringlen = str.length();
			token.string = strdup(str.c_str());

			*curtokpp = token;

			//GetToken2();

		//	return str;
		}
		else
			jfatalerror("Expected string");
	}
	//return NULL;
}

void CPreprocessor::Expect(int c)
{
	if (
		(curtokpp->type != CToken::tok_symbol && curtokpp->type != CToken::tok_char)
		|| (curtokpp->symbol != c))
	{
		char cur[512];

		if (curtokpp->type == CToken::tok_ident)
		{
			sprintf(cur, "'%s'", curtokpp->ident);
		}
		else
		{
			sprintf(cur, "'%c'", curtokpp->symbol);
		}

		char msg[256];
		if (c == '\n')
			sprintf(msg, "%s expected newline", cur, c);
		else
			sprintf(msg, "%s expected '%c'", cur, c);
		jerror(msg);
	}
}

void CPreprocessor::EatSymbol(int c)
{
	Expect(c);
	GetToken3();
}

////////////////////////////////////////////////////////////////////////

void CPreprocessor::newline()
{
	EatSymbol('\n');
}

void CPreprocessor::newline_or_eof()
{
	if (!m_pFile->_eof())
	{
		EatSymbol('\n');
	}
}

void CPreprocessor::skipline()
{
	while (!m_pFile->_eof())
	{
		if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '\n')
		{
			GetToken3();
			break;
		}
		GetToken3();
	}
}

std::string CPreprocessor::identifier()
{
	if (curtokpp->type != CToken::tok_ident)
	{
		jfatalerror("Expected identifier");
	}
	std::string ident = curtokpp->ident;
	GetToken2();

	return ident;
}

void CPreprocessor::identifier_list(CDefine* pMacro)
{
	while (!m_pFile->_eof())
	{
		std::string ident = identifier();
		pMacro->m_argNames.push_back(ident);

		if (curtokpp->type == CToken::tok_char && curtokpp->symbol == ',')
		{
			GetToken2();
			continue;
		}
		break;
	}
}

long CPreprocessor::literal()
{
	if (curtokpp->type == CToken::tok_integer)
	{
		long int32 = curtokpp->int32;
		GetToken2();
		return int32;
	}
	else
	{
		jfatalerror("invalid integer constant expression");
		return 0;
	}
}

/*
primary-expression:
	literal
	this
	( expression )
	id-expression
*/
long CPreprocessor::primary_expression()
{
	if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '(')
	{
		GetToken2();

		long pExpr = constant_expression();
		EatSymbol(')');

		return pExpr;
	}
	else if (curtokpp->type == CToken::tok_ident)
	{
		/*
		CExpression* pexpr = new CExpression;
		pexpr->tok = *curtok;
		GetToken();

		return pexpr;
		*/

		std::string ident = curtokpp->ident;

//	GetToken2();

		macromap::iterator macro = m_defines.find(ident);
		if (macro != m_defines.end())
		{
			TryMacro(macro);

			/*
			m_pFile->UngetToken(curtokpp);
			GetToken();
			*/
			return primary_expression();

		}
		else
			GetToken2();

		return 0;
		//return IfDef(ident.c_str());
	}
	else
	{
		return literal();
	}
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

long CPreprocessor::postfix_expression()
{
	long pExpr = primary_expression();

#if 0
	if (curtok->type == CToken::tok_keyword &&
		(curtok->pkw->n == KW_DYNAMIC_CAST ||
		curtok->pkw->n == KW_STATIC_CAST ||
		curtok->pkw->n == KW_REINTERPRET_CAST ||
		curtok->pkw->n == KW_CONST_CAST))
	{
		pPP->jfatalerror("xxx_cast not yet supported");
/*
	dynamic_cast < type-id > ( expression )
	static_cast < type-id > ( expression )
	reinterpret_cast < type-id > ( expression )
	const_cast < type-id > ( expression )
	*/
	}
	else if (curtok->symbol == '[')
	{
		while (curtok->symbol == '[')
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok = *curtok;
			GetToken2();

			pExpr2->left = pExpr;
			pExpr2->right = expression(pScope);

			pExpr = pExpr2;

			EatSymbol(']');
		}

		return pExpr;
	}
	else if (curtok->symbol == '(')
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;

		pExpr2->left = pExpr;

		GetToken2();
		if (curtok->type != CToken::tok_symbol || curtok->symbol != ')')
		{
			expression_list(pScope);
		}

		EatSymbol(')');

		pExpr = pExpr2;

		return pExpr;
	}
	else if (curtok->symbol == '.')
	{
		while (curtok->symbol == '.')
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok = *curtok;
			GetToken2();

			pExpr2->left = pExpr;
			//templateopt id-expression
			//pExpr2->right = expression(pScope);
			//pExpr2->right = id_expression(
			if (curtok->type != CToken::tok_ident)
			{
				pPP->jerror("Expected member name");
			}

			pExpr2->right = new CExpression;
			pExpr2->right->tok = *curtok;
			GetToken2();

			pExpr = pExpr2;

			//pExpr->m_pType = ExpressionType(pExpr, pScope);

			// TODO, maybe resolve this later
			{
				/*
				*/

			//	pExpr->left->
			}
		}
	}
#endif

	return pExpr;
}

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
long CPreprocessor::unary_expression()
{
	if (curtokpp->type == CToken::tok_ident && !strcmp(curtokpp->ident, "defined"))
	{
		GetToken3();

		long bDefined;

		if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '(')
		{
			GetToken3();

			std::string ident = identifier();
			bDefined = IfDef(ident.c_str());

			EatSymbol(')');
		}
		else
		{
			std::string ident = identifier();
			bDefined = IfDef(ident.c_str());
		}

		return bDefined;
	}
	else if (curtokpp->type == CToken::tok_symbol && (
	//	curtok->symbol == '*' ||
	//	curtok->symbol == '&' ||
		curtokpp->symbol == '+' ||
		curtokpp->symbol == '-' ||
		curtokpp->symbol == '!' ||
		curtokpp->symbol == '~'))
	{
		int symbol = curtokpp->symbol;
		GetToken2();
		/*
		longCExpression* pnode = new CExpression;
		pnode->tok = *curtok;
		pnode->tok.symbol |= 'U'<<8;	// Unary
		GetToken();

		pnode->right = cast_expression(pScope);
		return pnode;
		*/
		long right = unary_expression();

		if (symbol == '+')
			return right;
		else if (symbol == '-')
			return -right;
		else if (symbol == '!')
			return !right;
		else// if (symbol == '~')
			return ~right;
	}
#if 0
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_SIZEOF)
	{
		ATLASSERT(0);
		GetToken();

		if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
		{
			GetToken();

			CExpression* pExpr = new CExpression;
			pExpr->tok.type = CToken::tok_integer;

			CType* pType = type_id(pScope);

			pExpr->tok.int32 = pType->get_sizeof();

			EatSymbol(')');

			return pExpr;
		}
		else
		{
			CExpression* pExpr2 = unary_expression(pScope);
			if (pExpr2 == NULL)
			{
				pPP->jerror("Unexpected");
			}
			else
			{
				ExpressionType(pExpr2, pScope);

				CExpression* pExpr = new CExpression;
				pExpr->tok.type = CToken::tok_integer;
				pExpr->tok.int32 = pExpr2->m_pType->get_sizeof();

				delete pExpr2;

				return pExpr;
			}
		}
	}
#endif
	else
	{
		return postfix_expression();
	}
}

#if 0
/*
cast-expression:
	unary-expression
	( type-id ) cast-expression
*/
CExpression* cast_expression(CScope* pScope)
{
#if 0	// TODO
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '(')
	{
		jfatalerror("cast is currently not supported");
		EatSymbol(')');
		cast_expression(pScope);

		return NULL;
	}
	else
#endif
	{
		return unary_expression(pScope);
	}
}
#endif

/*
pm-expression:
	cast-expression
	pm-expression .* cast-expression
	pm-expression ->* cast-expression
*/
long CPreprocessor::pm_expression()
{
	return unary_expression();
}

/*
multiplicative-expression:
	pm-expression
	multiplicative-expression * pm-expression
	multiplicative-expression / pm-expression
	multiplicative-expression % pm-expression
*/
long CPreprocessor::multiplicative_expression()
{
	long pExpr = pm_expression();
	while (curtokpp->type == CToken::tok_symbol &&
		(curtokpp->symbol == '*' || curtokpp->symbol == '/' || curtokpp->symbol == '%'))
	{
		GetToken2();

		long pExpr2left = pExpr;
		long pExpr2right = pm_expression();

		if (curtokpp->symbol == '*')
			pExpr = pExpr2left * pExpr2right;
		else if (curtokpp->symbol == '/')
			pExpr = pExpr2left / pExpr2right;
		else
			pExpr = pExpr2left % pExpr2right;
	}

	return pExpr;
}

/*
additive-expression:
	multiplicative-expression
	additive-expression + multiplicative-expression
	additive-expression - multiplicative-expression
*/
long CPreprocessor::additive_expression()
{
	long pExpr = multiplicative_expression();
	while (curtokpp->type == CToken::tok_symbol &&
		(curtokpp->symbol == '+' || curtokpp->symbol == '-'))
	{
		GetToken2();

		long pExpr2left = pExpr;
		long pExpr2right = multiplicative_expression();

		if (curtokpp->symbol == '+')
			pExpr = pExpr2left + pExpr2right;
		else
			pExpr = pExpr2left - pExpr2right;
	}

	return pExpr;
}

/*
shift-expression:
	additive-expression
	shift-expression << additive-expression
	shift-expression >> additive-expression
*/
long CPreprocessor::shift_expression()
{
	return additive_expression();
}

/*
relational-expression:
	shift-expression
	relational-expression < shift-expression
	relational-expression > shift-expression
	relational-expression <= shift-expression
	relational-expression >= shift-expression
*/
long CPreprocessor::relational_expression()
{
	long pExpr = shift_expression();
	while (curtokpp->type == CToken::tok_symbol &&
		(curtokpp->symbol == '<' || curtokpp->symbol == '>' || curtokpp->symbol == '<=' || curtokpp->symbol == '>='))
	{
		int sym = curtokpp->symbol;

		GetToken2();

		long pExpr2left = pExpr;
		long pExpr2right = shift_expression();

		if (sym == '<')
			pExpr = pExpr2left < pExpr2right;
		else if (sym == '>')
			pExpr = pExpr2left > pExpr2right;
		else if (sym == '<=')
			pExpr = pExpr2left <= pExpr2right;
		else
			pExpr = pExpr2left >= pExpr2right;
	}

	return pExpr;
}

/*
equality-expression:
	relational-expression
	equality-expression == relational-expression
	equality-expression != relational-expression
*/
long CPreprocessor::equality_expression()
{
	long pExpr = relational_expression();

	while (curtokpp->type == CToken::tok_symbol &&
		(curtokpp->symbol == '==' || curtokpp->symbol == '!='))
	{
		int sym = curtokpp->symbol;

		GetToken2();

		long pExpr2left = pExpr;
		long pExpr2right = relational_expression();

		if (sym == '==')
			pExpr = pExpr2left == pExpr2right;
		else
			pExpr = pExpr2left != pExpr2right;
	}

	return pExpr;

}

/*
and-expression:
	equality-expression
	and-expression & equality-expression
*/
long CPreprocessor::and_expression()
{
	long pExpr = equality_expression();

	while (curtokpp->type == CToken::tok_symbol &&
		(curtokpp->symbol == '&'))
	{
		GetToken2();

		long pExpr2left = pExpr;
		long pExpr2right = equality_expression();

		pExpr = pExpr2left & pExpr2right;
	}

	return pExpr;
}

/*
exclusive-or-expression:
	and-expression
	exclusive-or-expression ˆ and-expression
*/
long CPreprocessor::exclusive_or_expression()
{
	return and_expression();
}

/*
inclusive-or-expression:
	exclusive-or-expression
	inclusive-or-expression | exclusive-or-expression
*/
long CPreprocessor::inclusive_or_expression()
{
	long pExpr = exclusive_or_expression();

	while (curtokpp->type == CToken::tok_symbol &&
		(curtokpp->symbol == '|'))
	{
		GetToken2();

		long pExpr2left = pExpr;
		long pExpr2right = exclusive_or_expression();

		pExpr = pExpr2left | pExpr2right;
	}

	return pExpr;
}

/*
logical-and-expression:
	inclusive-or-expression
	logical-and-expression && inclusive-or-expression
*/
long CPreprocessor::logical_and_expression()
{
	long pExpr = inclusive_or_expression();

	while (curtokpp->type == CToken::tok_symbol &&
		(curtokpp->symbol == '&&'))
	{
		GetToken2();

		long pExpr2left = pExpr;
		long pExpr2right = inclusive_or_expression();

		pExpr = pExpr2left && pExpr2right;
	}

	return pExpr;
}

/*
logical-or-expression:
	logical-and-expression
	logical-or-expression || logical-and-expression
*/
long CPreprocessor::logical_or_expression()
{
	long pExpr = logical_and_expression();

	while (curtokpp->type == CToken::tok_symbol &&
		(curtokpp->symbol == '||'))
	{
		GetToken2();

		long pExpr2left = pExpr;
		long pExpr2right = logical_and_expression();

		pExpr = pExpr2left || pExpr2right;
	}

	return pExpr;
}

#if 0
/*
conditional-expression:
	logical-or-expression
	logical-or-expression ? expression : assignment-expression
*/
static CExpression* conditional_expression(CScope* pScope)
{
	return logical_or_expression(pScope);
}

/*
assignment-expression:
	conditional-expression
	logical-or-expression assignment-operator assignment-expression
	throw-expression

assignment-operator: one of
	= *= /= %= += -= >>= <<= &= ˆ= |=
*/

long CPreprocessor::assignment_expression()
{
	CExpression* pExpr = logical_or_expression(pScope);
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
	{
		CExpression* pExpr2 = new CExpression;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = assignment_expression(pScope);

		pExpr = pExpr2;
	}

	return pExpr;

//	return conditional_expression(pScope);
}
#endif

long CPreprocessor::constant_expression()
{
	return logical_or_expression();
}

void CPreprocessor::replacement_list(CDefine* pDefine)
{
	while (!m_pFile->_eof())
	{
		if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '\n')
		{
			break;
		}
		pDefine->m_replacementList.push_back(*curtokpp);
		GetToken4();	// or GetToken3()	// ??
	}
	if (pDefine->m_replacementList.size())
	{
		if (pDefine->m_replacementList[pDefine->m_replacementList.size()-1].type == CToken::tok_space)
		{
			pDefine->m_replacementList.erase(pDefine->m_replacementList.end()-1);
		}
	}
}

/*
elif-groups:
	elif-group
	elif-groups elif-group

elif-group:
	# elif constant-expression new-line groupopt

else-group:
	# else new-line groupopt

endif-line:
	# endif new-line
*/

/*
if-section:
	if-group elif-groupsopt else-groupopt endif-line
if-group:
	# if constant-expression new-line groupopt
	# ifdef identifier new-line groupopt
	# ifndef identifier new-line groupopt
*/

void CPreprocessor::if_section(int directive)
{
	CIf* pIf = new CIf;
	pIf->m_pPrev = m_pIf;
	m_pIf = pIf;

	BOOL bValue;

	if (directive == PP_IF)
	{
		bValue = constant_expression();
		newline();
	}
	else	// ifdef, ifndef
	{
		std::string ident = identifier();
		newline();

		bValue = IfDef(ident.c_str());

		if (directive == PP_IFNDEF)
		{
			bValue = !bValue;
		}
	}

//	printf("%s\n", bValue?"true":"false");

// We process if/ifdef/indef, elif and else groups, skipping them if necessary until we find the correct one to process

	if (bValue)
	{
		m_pIf->m_bCondition = TRUE;
		return;
	}
	skip_group();

// elif-groups opt
	while (!m_pFile->_eof())
	{
		if (strcmp(curtokpp->ident, "elif"))
		{
			break;
		}
		GetToken2();

		bValue = constant_expression();
		newline();

		if (bValue)
		{
			m_pIf->m_bCondition = TRUE;
			return;
		}

		skip_group();
	}

	if (!strcmp(curtokpp->ident, "else"))
	{
		GetToken2();

		newline();

		m_pIf->m_bCondition = TRUE;
		return;
	//	skip_group();
	}

	endif();
}

void CPreprocessor::endif()
{
	if (curtokpp->type != CToken::tok_ident || strcmp(curtokpp->ident, "endif"))
	{
		jfatalerror("Expected #endif");
	}
	GetToken();
	newline_or_eof();

	// Back up one level
	CIf* pPrevIf = m_pIf->m_pPrev;
	delete m_pIf;
	m_pIf = pPrevIf;
}

void CPreprocessor::skip_if_section(int directive)
{
	skipline();
	skip_group();

// elif-groups opt
	while (!m_pFile->_eof())
	{
		if (strcmp(curtokpp->ident, "elif"))
		{
			break;
		}

		skipline();
		skip_group();
	}

// else-group opt
	if (curtokpp->type == CToken::tok_ident && !strcmp(curtokpp->ident, "else"))
	{
		GetToken();

		newline();
		skip_group();
	}

	if (curtokpp->type != CToken::tok_ident || strcmp(curtokpp->ident, "endif"))
	{
		jfatalerror("Expected #endif");
	}
	GetToken();
}

/*
lparen:
	the left-parenthesis character without preceding white-space
*/

/*
control-line:
# include pp-tokens new-line
# define identifier replacement-list new-line
# define identifier lparen identifier-listopt ) replacement-list new-line
# undef identifier new-line
# line pp-tokens new-line
# error pp-tokensopt new-line
# pragma pp-tokensopt new-line
# new-line
*/

/*
group-part:
	pp-tokensopt new-line
	if-section
	control-line
*/

int CPreprocessor::directive()
{
	if (curtokpp->type == CToken::tok_ident)
	{
		for (int i = 0; i < PP_MAX; i++)
		{
			if (!strcmp(curtokpp->ident, pp_kws[i]))
			{
				break;
			}
		}

		if (i < PP_MAX)
		{
			int directive = i;

			switch (directive)
			{
			case PP_ENDIF:
				{
					//printf("#endif\n");
					if (m_pIf)
					{
						// Back up one level
						CIf* pPrevIf = m_pIf->m_pPrev;
						delete m_pIf;
						m_pIf = pPrevIf;
					}
					else
					{
						jfatalerror("Unexpected #endif");
					}

					GetToken2();
					newline_or_eof();

					return FALSE;
				}
				break;

			case PP_ELIF:
				{
					//printf("#elif\n");
					if (m_pIf == NULL)
					{
						jfatalerror("Unexpected #elif");
					}

					ATLASSERT(m_pIf->m_bCondition);

					while (!m_pFile->_eof())
					{
						if (strcmp(curtokpp->ident, "elif"))
						{
							break;
						}
						GetToken2();

						BOOL bValue = constant_expression();
						newline();

						skip_group();
					}

					if (!strcmp(curtokpp->ident, "else"))
					{
						GetToken2();

						newline();

						/*
						m_pIf->m_bCondition = TRUE;
						return;
						*/
						skip_group();
					}

					endif();

/*
					BOOL bValue = constant_expression();
					newline();

					skip_group();

					else_group_opt();
*/

					return FALSE;
				}
				break;

			case PP_ELSE:
				{
					//printf("#else\n");
					if (m_pIf == NULL)
					{
						jfatalerror("Unexpected #else");
					}

					GetToken3();
					newline();

					ATLASSERT(m_pIf->m_bCondition);
					skip_group();
					endif();

					return FALSE;
				}
				break;
			}

			switch (directive)
			{
			// if-section
			case PP_IF:
			case PP_IFDEF:
			case PP_IFNDEF:
				{
					GetToken3();

					//printf("#if ");
					if_section(directive);
				}
				break;

				/*
				control-line:
				# include pp-tokens new-line
				# define identifier replacement-list new-line
				# define identifier lparen identifier-listopt ) replacement-list new-line
				# undef identifier new-line
				# line pp-tokens new-line
				# error pp-tokensopt new-line
				# pragma pp-tokensopt new-line
				# new-line
				*/
			case PP_INCLUDE:
				{
					GetToken();	// Next token with macro expansion

					GetHeaderName();

					CToken tok = *curtokpp;
					GetToken2();
				//	newline_or_eof();

					BOOL bOk = FALSE;
					if (tok.type == CToken::tok_string)
					{
						CFile* pFile = new CFile;
						TCHAR dir[4];
						TCHAR path[260];
						_splitpath(m_pFile->m_filepath.c_str(), dir, path, NULL, NULL);

						TCHAR filepath[260];
						_makepath(filepath, dir, path, tok.string, NULL);

						if (pFile->open(filepath))
						{
							pFile->m_pPrev = m_pFile;
							m_pFile = pFile;

							GetToken();
							bOk = TRUE;
						}
						else
						{
							delete pFile;
						}
					}

					if (!bOk)
					{
						std::vector<std::string> include_paths;

					//	include_paths.push_back("C:\\PROGRAM FILES\\MICROSOFT SDK\\INCLUDE\\");
					//	include_paths.push_back("C:\\Program Files\\Microsoft Visual Studio\\VC98\\INCLUDE\\");
					//	include_paths.push_back("C:\\Program Files\\Microsoft Visual Studio\\VC98\\ATL\\INCLUDE\\");
					//	include_paths.push_back("C:\\WTL31\\INCLUDE\\");
						
						include_paths.push_back("C:\\Program Files\\Microsoft Visual Studio\\VC98\\Include\\");
					//	include_paths.push_back("C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\include\\");
						include_paths.push_back("C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\sdk\\classic\\ndk_39\\include\\include_h\\");

						for (int i = 0; i < include_paths.size(); i++)
						{
							CFile* pFile = new CFile;
							TCHAR dir[4];
							TCHAR path[260];
							_splitpath(include_paths[i].c_str(), dir, path, NULL, NULL);

							TCHAR filepath[260];
							_makepath(filepath, dir, path, tok.string, NULL);

							if (pFile->open(filepath))
							{
							//	printf("#include <%s>\n", filepath);
								pFile->m_pPrev = m_pFile;
								m_pFile = pFile;

								GetToken();
								bOk = TRUE;
								break;
							}
							else
							{
								delete pFile;
							}
						}
					}

					if (!bOk)
					{
						char msg[1024];
						sprintf(msg, "Cannot open include file '%s'", tok.string);
						jfatalerror(msg);
					}
				}
				break;
				
			case PP_DEFINE:
				{
					GetToken3();

					if (curtokpp->type != CToken::tok_ident)
					{
						jfatalerror("Expected identifier after #define");
					}

				//	printf("#define %s\n", ident.c_str());

					//CDefine* pDefine = Define(curtokpp->ident);
					CDefine* pDefine = new CDefine;
					pDefine->m_name = curtokpp->ident;

					int c = m_pFile->_getc();
					if (c == '(')	// No intervening spaces between identifer and left parenthesis
					{
						GetToken3();
						pDefine->m_bFunctionLike = true;

						if ((curtokpp->type != CToken::tok_symbol && curtokpp->type != CToken::tok_char) ||
							(curtokpp->symbol != ')'))
						{
							identifier_list(pDefine);
						}

						EatSymbol(')');
					}
					else
					{
						pDefine->m_bFunctionLike = false;
						m_pFile->_ungetc(c);
						GetToken3();
					}

#if 0
					skipspaces();
#endif
					replacement_list(pDefine);

					newline_or_eof();

					//CDefine* pDefine2 = Find(pDefine->m_name.c_str());
					macromap::iterator pDefine2 = m_defines.find(pDefine->m_name);
					if (pDefine2 != m_defines.end())
					{
						if (!pDefine->IsEqual((*pDefine2).second))
						{
							char msg[512];
							sprintf(msg, "Redefinition of macro '%s' : first seen :\n%s(%d)",
								pDefine->m_name.c_str(), (*pDefine2).second->m_location.m_filepath.c_str(), (*pDefine2).second->m_location.m_line);

							jerror(msg);
						}

						delete pDefine;
						pDefine = NULL;
					}

					if (pDefine)
					{
						Define(pDefine);
					}
				}
				break;
				
			case PP_UNDEF:
				{
					GetToken3();

					std::string ident = identifier();

					Undef(ident.c_str());

					newline_or_eof();
				}
				break;
				
			case PP_LINE:
				{
					GetToken3();
					jfatalerror("#line not supported yet");
				}
				break;
				
			case PP_ERROR:
				{
					std::string errorString = "#error";
					while (!m_pFile->_eof())
					{
						int c = m_pFile->_getc();
						if (c == '\r')
						{
							int c2 = m_pFile->_getc();
							ATLASSERT(c2 == '\n');
							break;
						}
						else if (c == '\n')
						{
							break;
						}
						errorString += c;
					}
					jerror(errorString.c_str());
					GetToken2();
				}
				break;
				
			case PP_PRAGMA:
				{
					GetToken3();
				//	jwarn("#pragma not supported yet");

					m_pCompiler->OnPragma();

					skipline();
				//	newline_or_eof();
				}
				break;
				
			default:
				ATLASSERT(0);
			}
		}
		else
		{
			char msg[1024];
			sprintf("invalid preprocessor command '%s'", curtokpp->ident);
			jfatalerror(msg);
		}
	}
	else if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '\n')
	{
		GetToken2();
	}
	else
	{
		jfatalerror("invalid preprocessor command");
	}
	return TRUE;
}

int CPreprocessor::group_part()
{
	GetToken();

	if (curtokpp->symbol == '#')
	{
		GetToken();
		return directive();
	}
	else
	{
		skipline();
	}

	return TRUE;
}

int CPreprocessor::skip_group_part()
{
//	GetToken();

	if (curtokpp->symbol == '#')
	{
		GetToken();

		if (curtokpp->type == CToken::tok_ident)
		{
			for (int i = 0; i < PP_MAX; i++)
			{
				if (!strcmp(curtokpp->ident, pp_kws[i]))
				{
					break;
				}
			}

			if (i < PP_MAX)
			{
				int directive = i;

				switch (directive)
				{
				case PP_ELIF:
					{
						return FALSE;
					}
					break;

				case PP_ELSE:
					{
						return FALSE;
					}
					break;

				case PP_ENDIF:
					{
						return FALSE;
					}
					break;
				}

				GetToken2();

				switch (directive)
				{
				// if-section
				case PP_IF:
				case PP_IFDEF:
				case PP_IFNDEF:
					{
						skip_if_section(directive);
					}
					break;
					
				default:
					skipline();
				}
			}
		}
		else if (curtokpp->type == CToken::tok_symbol && curtokpp->symbol == '\n')
		{
			GetToken();
		}
	}
	else
	{
		skipline();
	}

	return TRUE;
}

/*
group:
	group-part
	group group-part
*/
void CPreprocessor::group()
{
	ATLASSERT(0);
	while (!m_pFile->_eof())
	{
		if (!group_part())
			break;
	}
}

void CPreprocessor::skip_group()
{
	while (!m_pFile->_eof())
	{
		if (!skip_group_part())
			break;
	}
}

#if 0
void macro_replace(CDefines* pDefs, std::vector<CToken>& tokens)
{
	for (int i = 0; i < tokens.size(); i++)
	{
		CToken* tok = &tokens[i];

		if (tok->type == CToken::tok_ident)
		{
			CDefine* pDefine = pDefs->Find(tok->ident);
			if (pDefine)
			{
			}
		}
	}
}
#endif

};

/*
preprocessing-file:
	groupopt
*/
#if 0
void preprocessing_file()
{
	PP::CDefines defs;
	PP::group(&defs);
}
#endif