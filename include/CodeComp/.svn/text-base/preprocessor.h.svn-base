#ifndef Preprocessor_h
#define Preprocessor_h

#undef new
#include <cstdio>
#include <map>
#define new _new

namespace System
{

//class CCompiler;

namespace cpp
{
class Options;
}

namespace PP
{

class MacroInvocation : public Object
{
public:
	MacroInvocation(CDefine* pMacro)
	{
		ASSERT(pMacro);
		m_pMacro = pMacro;

		m_pPrev = NULL;
		m_cur = 0;
	}

	int GetArg(StringIn name)
	{
		for (uint i = 0; i < m_pMacro->m_argNames.GetSize(); ++i)
		{
			if (String(m_pMacro->m_argNames[i]) == name)
			{
				return i;
			}
		}

		return -1;
	}

	bool _eof()
	{
#if 1
		return !(m_cur < m_string.GetLength());
#else
		return !(m_cur < m_tokenList.size());
#endif
	}

#if 1
	int _getc()
	{
		int c = m_string.GetData8()[m_cur];
		++m_cur;
		return c;
	}

	void _ungetc()
	{
		ASSERT(m_cur > 0);
		--m_cur;
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
		ASSERT(m_cur >= 0);
		m_cur--;
	}
#endif

	int SubstituteArguments(vector<vector<CToken*> >& argTokenList);

	bool IsInside(StringIn name)
	{
		ASSERT(m_pMacro);

		//if (!std::strcmp(m_pMacro->m_name->c_str(), name->c_str()))
		if (m_pMacro->m_name == name)
		{
			return true;
		}
		if (m_pPrev)
		{
			return m_pPrev->IsInside(name);
		}
		return false;
	}

	MacroInvocation* m_pPrev;
	CDefine* m_pMacro;

	String m_string;
	uint m_cur;
};

/*
class CCharacterStream
{
public:
	virtual int _getc() = 0;
	virtual void _ungetc(int c) = 0;
	virtual bool _eof() = 0;
};
*/

class CFile : public Object
{
public:
	CTOR CFile();
	~CFile();

	bool open(StringIn filepath);

	int _getc2();

	virtual int _getc();
	virtual void _ungetc(int c);
	virtual bool _eof()
	{
#if 0
		if (!m_tokens.empty())
			return FALSE;
		else
#endif
		//	if (true)
			{
				return !(m_fpos < m_size);
			}
			/*
			else
			{
				return feof(m_fp) != 0;
			}
			*/
	}

public:

//	IO::StreamReader m_fp;
	FILETIME m_filetime;

public:
	String m_filepath;
	CFile* m_pPrev;

	int m_lastc;
#if 0
	std::stack<CToken> m_tokens;
	void UngetToken(CToken* ptok);
#endif

	int m_line;
	int m_column;

	char* m_data;
	int m_size;
	int m_fpos;
};

class CIf : public Object
{
public:
	CIf()
	{
		m_pPrev = NULL;
		m_bCondition = false;
	}

	CIf* m_pPrev;
	bool m_bCondition;
};

typedef std::map<String, CDefine*> macromap;

template<class T> class std_Ref_Less //: public binary_function<T, T, bool>
{
public:

	bool operator () (const T * x, const T * y) const
	{
	//	if (x == y) return false;	// they're equal
	//	if (x == NULL) return true;	// x < y
	//	if (y == NULL) return false;	// y < x
		return *x < *y;
	}
};

typedef std::map<String, CDefine*> std_macromap;

class IncludeFile : public Object
{
public:

	CTOR IncludeFile(String filename, FILETIME filetime) :
		m_filename(filename),
		m_filetime(filetime)
	{
	}

	String m_filename;
	FILETIME m_filetime;
};

class PPException : public Exception
{
public:

	CTOR PPException(StringIn msg) : Exception(msg)
	{
	}
};

class CPreprocessor : public Object
{
public:
	CPreprocessor(CFile* pFile, cpp::Options* options);

	CToken* _GetToken();
	CToken* __GetToken();

	void GetString(bool bWide/*, CToken& token*/);
	void GetCharacter(bool bWide/*, CToken& token*/);

	CToken* TryMacro(MacroInvocation* pParentMacro, macromap::iterator pDefine);

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
	bool _eof();

//	std::string rest_of_line();

	int directive();
	void newline();
	void newline_or_eof();
	void skipline();
	System::StringA* identifier();
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
	long literal_expression();
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

	macromap::iterator Find(StringIn name)
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

	CDefine* Define(StringIn name);
	CDefine* Define(StringIn name, long int32);

	void Define(CDefine* pDefine);
	void Undef(StringIn name);
	bool IfDef(StringIn name);

	void printlocation(const char* type)
	{
		CFile* pPrevFile = m_pFile->m_pPrev;
		while (pPrevFile)
		{
			smsg() << pPrevFile->m_filepath << paren(pPrevFile->m_line+1) << "..." << '\n';
			pPrevFile = pPrevFile->m_pPrev;
		}

		smsg() << m_pFile->m_filepath << paren(m_pFile->m_line+1) << ":" << type << " : ";
	}

	void jwarn(const char* msg, ...)
	{
		printlocation("warn");
		std::printf(msg);
		std::printf("\n");

		++m_warnings;
	}

	IO::TextWriter& smsg()
	{
		return m_msgStream;
	}

	IO::TextWriter& swarn()
	{
		printlocation("warn");
		return smsg();
	}

	IO::TextWriter& serror()
	{
		printlocation("error");
		return smsg();
	}

	IO::TextWriter& sfatalerror()
	{
		printlocation("error");
		return smsg();
	}

	void jwarn(IO::TextWriter& stream)
	{
		++m_warnings;
		stream << endl;
	}

	void jerror(IO::TextWriter& stream)
	{
		++m_errors;
		stream << endl;
	}

	void jfatalerror(IO::TextWriter& stream)
	{
		stream << endl;
		raise(PPException(L"Fatal error"));
	}

	void jerror(const char* msg, ...)
	{
		if (m_try == 0)
		{
			printlocation("error");
			smsg() << msg << endl;
			++m_errors;

			uint maxErrors = 50;
			if (m_errors > maxErrors)
			{
				smsg() << maxErrors << " errors reached, stopping compilation\n";
				raise(PPException("Too many errors"));
			}
		}
		else
		{
			raise(PPException("Too many errors"));
		}
	}

	void jfatalerror(const char* msg, ...)
	{
		if (m_try == 0)
		{
			printlocation("fatal error");
			smsg() << msg << endl;
			raise(PPException("Fatal Error"));
		}
		else
		{
			raise(PPException("Too many errors"));
		}
	}

public:

//	CCompiler* m_pCompiler;
	int m_try;
	bool m_bNewLine;
	CFile* m_pFile;
	CIf* m_pIf;
	CToken* curtokpp;
	stack<CToken*> m_stack;
	MacroInvocation* m_pMacroInvocation;
#if 0
	macromap m_defines;
#endif
	macromap m_defines;

	vector<IncludeFile> m_includeFiles;

	_Ptr<IO::StreamWriter> m_msgStream;

	vector<String> m_includeDirs;

	cpp::Options* m_options;

	uint m_errors;
	uint m_warnings;
};

}	// PP
}	// System

#endif // Preprocessor_h
