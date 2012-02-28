#ifndef __PREPOROCESSOR_H_
#define __PREPOROCESSOR_H_

class CCompiler;

namespace PP
{
class CToken
{
public:
	CToken()
	{
		type = tok_empty;
		ident = NULL;
	}

	~CToken()
	{
		/*
		if (type == tok_ident || type == tok_string || type == tok_ltstring)
		{
			if (ident)
			{
				free(ident);
				ident = NULL;
			}
		}
		*/
	}

	CToken& operator = (const CToken& other)
	{
		/*
		if (type == tok_ident || type == tok_string || type == tok_ltstring)
		{
			if (ident)
			{
				free(ident);
				ident = NULL;
			}
		}
		*/

		type = other.type;
		if (type == tok_ident || type == tok_string || type == tok_ltstring)
		{
			identlen = other.identlen;
			ident = strdup(other.ident);
		}
		else
		{
			symbol = other.symbol;
		}

		return *this;
	}

	enum
	{
		tok_empty,
		tok_space,
		tok_ident,
		tok_symbol,
		tok_string,
		tok_ltstring,
		tok_integer,
		tok_double,
		tok_char,
	}
	type;

	std::string toString()
	{
		if (type == tok_space)
		{
			return " ";
		}
		else if (type == tok_string || type == tok_ident)
		{
			return string;
		}
		else if (type == tok_integer)
		{
			char buf[64];
			sprintf(buf, "%d", int32);
			return buf;
		}
		else if (type == tok_symbol)
		{
			if (symbol > 255)
			{
				if (symbol > 65535)
				{
					ATLASSERT(0);
				}
				else
				{
					std::string str;
					{
						char c2[2] = {(symbol>>8)&0xff, 0};
						str += c2;
					}

					{
						char c2[2] = {(symbol)&0xff, 0};
						str += c2;
					}

					return str;
				}
			}
			else
			{
				char c2[2] = {(char)symbol, 0};
				return std::string(c2);
			}
		}
		else if (type == tok_char)
		{
			char c2[2] = {(char)symbol, 0};
			return std::string(c2);
		}
		else
		{
			ATLASSERT(0);
		}
		return NULL;
	}

	union
	{
		long int32;
		double double64;
		int kw;
		DWORD symbol;

		struct
		{
			int identlen;
			char* ident;
		};

		struct
		{
			int stringlen;
			char* string;
		};

		struct
		{
			int stringlen;
			WCHAR* wstring;
		};
	};
};

class CFileLocation
{
public:
	std::string m_filepath;
	int m_line;
	int m_column;
};

class CDefine
{
public:
	CDefine()
	{
		m_bFunctionLike = false;
	}

	std::string m_name;

	BOOL m_bFunctionLike;	// Even if m_params is empty, the macro could require empty parentheses
	std::vector<std::string> m_argNames;

//	std::string m_replacementString;

	std::vector<CToken> m_replacementList;

	CFileLocation m_location;

	BOOL IsEqual(CDefine* pOther);
};

class CMacroInvocation
{
public:
	CMacroInvocation(CDefine* pMacro)
	{
		ATLASSERT(pMacro);
		m_pMacro = pMacro;

		m_cur = 0;
	}

	CMacroInvocation* m_pPrev;
	CDefine* m_pMacro;

#if 1
	std::string m_string;
#else
	std::vector<CToken> m_tokenList;
#endif

	int m_cur;

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

	BOOL _eof()
	{
#if 1
		return !(m_cur < m_string.length());
#else
		return !(m_cur < m_tokenList.size());
#endif
	}

#if 1
	int _getc()
	{
		int c = m_string[m_cur];
		m_cur++;
		return c;
	}

	void _ungetc()
	{
		ATLASSERT(m_cur >= 0);
		m_cur--;
	}

#if 0
	std::stack<CToken> m_tokens;

	void UngetToken(CToken* ptok)
	{
		m_tokens.push(*ptok);
	}
#endif

#else
	CToken* GetToken()
	{
		return &m_tokenList[m_cur++];
	}

	void UngetToken()
	{
		ATLASSERT(m_cur >= 0);
		m_cur--;
	}
#endif

	BOOL SubstituteArguments(std::vector<std::vector<CToken> >& argTokenList);

	BOOL IsInside(const char* name)
	{
		if (!strcmp(m_pMacro->m_name.c_str(), name))
		{
			return TRUE;
		}
		if (m_pPrev)
		{
			return m_pPrev->IsInside(name);
		}
		return FALSE;
	}
};

class CCharacterStream
{
public:
	virtual ~CCharacterStream()
	{
	}

	virtual int _getc() = 0;
	virtual void _ungetc(int c) = 0;
	virtual BOOL _eof() = 0;
};

class CFile : public CCharacterStream
{
public:
	CFile()
	{
		m_pPrev = NULL;
		m_fp = NULL;

		m_lastc = -1;
		m_line = 0;
	}

	~CFile()
	{
		if (m_fp)
		{
			fclose(m_fp);
			m_fp =  NULL;
		}
	}

public:	//protected:
	FILE* m_fp;

public:
	std::string m_filepath;
	CFile* m_pPrev;

	int m_lastc;
#if 0
	std::stack<CToken> m_tokens;
	void UngetToken(CToken* ptok);
#endif

	int m_line;

	FILE* open(const char* filepath)
	{
		m_filepath = filepath;
		m_fp = fopen(filepath, "rb");
		return m_fp;
	}

	int _getc2();

public:

	virtual int _getc();
	virtual void _ungetc(int c);
	virtual BOOL _eof()
	{
#if 0
		if (!m_tokens.empty())
			return FALSE;
		else
#endif
			return feof(m_fp);
	}
};

class CIf
{
public:
	CIf()
	{
		m_pPrev = NULL;
		m_bCondition = FALSE;
	}

	CIf* m_pPrev;
	BOOL m_bCondition;
};

	typedef std::map<std::string, CDefine*> macromap;

class CPreprocessor
{
public:
	CPreprocessor(CFile* pFile)
	{
		m_pIf = NULL;

		m_pFile = pFile;
		m_pMacroInvocation = NULL;

		//m_level = 0;

		curtokpp = &gtoken;

		m_errors = 0;
		m_warnings = 0;

		m_try = 0;

		m_bNewLine = TRUE;

		m_pCompiler = NULL;
	}

	CCompiler* m_pCompiler;

	int m_try;

	BOOL m_bNewLine;

	CFile* m_pFile;

	CIf* m_pIf;

	CToken gtoken;
	CToken* curtokpp;

	CToken* TryMacro(macromap::iterator pDefine);

	int getNextNonSpace(int c);
	//void SkipSpacesAndComments();

	CToken* GetToken4();
	CToken* GetToken3();
	CToken* GetToken2();	// Calls GetToken3()
	CToken* GetToken();	// Calls GetToken2() and expands macros
	void GetHeaderName();
	void EatSymbol(int c);
	void Expect(int c);
	void skipspaces();

	int _getc();
	void _ungetc(int c);
	BOOL _eof();

//	std::string rest_of_line();

	int directive();
	void newline();
	void newline_or_eof();
	void skipline();
	std::string identifier();
	void identifier_list(CDefine* pMacro);

	void replacement_list(CDefine* pDefine);
	void if_section(int directive);
	void endif();

	void skip_if_section(int directive);
	int group_part();
	int skip_group_part();
	void group();
	void skip_group();

// #if expressions
	long literal();
	long primary_expression();
	long postfix_expression();
	long unary_expression();
	long pm_expression();
	long multiplicative_expression();
	long additive_expression();
	long shift_expression();
	long relational_expression();
	long equality_expression();
	long and_expression();
	long exclusive_or_expression();
	long inclusive_or_expression();
	long logical_and_expression();
	long logical_or_expression();
	long constant_expression();
//

	CMacroInvocation* m_pMacroInvocation;

//	std::vector<CDefine*> m_defines;
	macromap m_defines;

	int m_errors;
	int m_warnings;

	macromap::iterator Find(const char* name)
	{
		return m_defines.find(name);
		//return *i;//CDefine* p = 
		//return &i;

		//return p;
#if 0
		for (int i = 0; i < m_defines.size(); i++)
		{
			if (!strcmp(m_defines[i]->m_name.c_str(), name))
			{
				return m_defines[i];
			}
		}
		return NULL;
#endif
	}

	CDefine* Define(const char* name);
	CDefine* Define(const char* name, long int32);

	void Define(CDefine* pDefine);
	void Undef(const char* name);
	BOOL IfDef(const char* name);

	void printlocation(const char* type)
	{
		CFile* pPrevFile = m_pFile->m_pPrev;
		while (pPrevFile)
		{
			printf("%s(%d)...\n", pPrevFile->m_filepath.c_str(), pPrevFile->m_line+1);
			pPrevFile = pPrevFile->m_pPrev;
		}

		printf("%s(%d) : %s : ", m_pFile->m_filepath.c_str(), m_pFile->m_line+1, type);
	}

	void __cdecl jwarn(const char* msg, ...)
	{
		printlocation("warn");
		printf(msg);
		printf("\n");

		m_warnings++;
	}

	void __cdecl jerror(const char* msg, ...)
	{
		if (m_try == 0)
		{
			printlocation("error");
			printf(msg);
			printf("\n");
			m_errors++;

			if (m_errors > 50)
			{
				printf("50 errors reached, stopping compilation\n");
				exit(1);
			}

		//	exit(1);
		}
		else
		{
		//	throw -1;
		}
	}

	void __cdecl jfatalerror(const char* msg, ...)
	{
		if (m_try == 0)
		{
			printlocation("fatal error");
			printf(msg);
			printf("\n");
			exit(1);
		}
		else
		{
			throw -1;
		}
	}
};

};

#endif // __PREPOROCESSOR_H_
