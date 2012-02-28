namespace System
{
namespace Grammar
{

enum Token
{
	TOKEN_EOF = -1,
	TOKEN_INT,
	TOKEN_UINT,
	TOKEN_FLOAT,
	TOKEN_ID,
	TOKEN_KEYWORD,
	TOKEN_STRING,
	TOKEN_SYMBOL,
};

IO::TextWriter& WriteToStream(IO::TextWriter& stream, const Token& token);

enum Keyword
{
	Keyword_int,
	Keyword_word,
	Keyword_real,
	Keyword_true,
	Keyword_false,
	Keyword_null,
	Keyword_val,
	Keyword_if,
	Keyword_then,
	Keyword_else,
	Keyword_this,
	Keyword_typeof,
	Keyword_raise,
	Keyword_and,
	Keyword_or,
	Keyword_bitand,
	Keyword_bitor,
	Keyword_bitxor,
	Keyword_div,
	Keyword_mod,
	Keyword_switch,
	Keyword_case,
	Keyword_expof,
	Keyword_DEF,
	//Keyword_USE,
};

struct lex_val
{
	union
	{
		int intval;
		unsigned int uintval;
		int64 int64val;
		double floatval;
		int symbol;
		Keyword keyword;
	};

	String string;
};

class EXPEXT Lexer : public Object
{
public:
	CTOR Lexer(StringIn filename, IO::TextReader* stream);
	virtual ~Lexer();

	Token lex();

	void adv();
	int Getc();
	void unGetc();

	int64 parsenumber();

	String GetFilePath()
	{
		return m_filepath;
	}

	Token m_token;
	lex_val m_val;
	lex_loc m_loc;

	_Ptr<IO::TextReader> m_stream;
	char* m_buffer;
	uint m_fpos;
	uint m_nstacked;

protected:

	bool ceof();
	int64 _getnumber();
	double getfrac();
	int lookexp();

	String m_filepath;
	int m_c;
};

class EXPEXT Parser : public Object
{
public:

	CTOR Parser(Lexer* lexer);

	static Object* FromStream(IO::Stream* stream);
	static Object* FromFile(StringIn filename);

	static ADeclarationList* ProgramFromFile(StringIn filename);
	static ADeclarationList* ParseProgram(IO::Stream* stream);

	static AExpression* ParseExpression(StringIn filename, IO::TextReader* reader);
	static AExpression* ExpressionFromString(StringIn str);
	static AExpression* ExpressionFromFile(StringIn filename);

	ADeclarationList* ParseProgram();
	ADeclaration* ParseTopLevelDeclaration();

	ADeclarationList* ParseRules();
	AExpression* ParseRule();
	AExpression* ParseTerminal();
	/*
	AExpression* ParseLogicalANDExpression();
	AExpression* ParseRelationalExpression();
	AExpression* ParseAdditiveExpression();
	AExpression* ParseMultiplicativeExpression();
	AExpression* ParseUnaryExpression();
	AExpression* ParseCallExpression();
//	Expression* ParseLeftHandSideExpression();
	AExpression* ParseMemberExpression();
	AExpression* ParsePrimaryExpression();
	*/

protected:

	void Warning(StringIn str);
	void Error(StringIn str);
	__declspec(noreturn) void FatalError(StringIn str);

	bool ReadBool();
//	int32 ReadInt32();
//	int64 ReadInt64();
	float ReadFloat();
	double ReadDouble();

	void lex()
	{
		m_lexer->lex();
		m_token = m_lexer->m_token;
		m_val = m_lexer->m_val;
		m_loc = m_lexer->m_loc;
	}

	void EatChar(int c);

	void read(char* buffer, int count);

	String readidentifier();
	String readstring();
	long getnumber();
	double getfnumber();

//	map<String, Expression*> m_defs;

	bool IsSymbol(int c);
	bool IsKeyword(Keyword keyword);

	Lexer* m_lexer;

	_Ptr<IO::TextWriter> m_out;

	Token m_token;
	lex_val m_val;
	lex_loc m_loc;

	uint m_warnings;
	uint m_errors;

protected:

//	Object* LoadObjectContent(NamedType* pType);

	inline bool eof()
	{
		return m_token == TOKEN_EOF;
	}
};

}	// Grammar
}	// System
