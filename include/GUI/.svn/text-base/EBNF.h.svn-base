namespace System
{
namespace Expressive
{

enum Token
{
	TOKEN_EOF = -1,
	TOKEN_INT,
	TOKEN_FLOAT,
	TOKEN_ID,
	TOKEN_KEYWORD,
	TOKEN_STRING,
	TOKEN_SYMBOL,
};

enum Keyword
{
	Keyword_true,
	Keyword_false,
	Keyword_null,
	Keyword_if,
	Keyword_then,
	Keyword_else,
	Keyword_this,
	Keyword_and,
	Keyword_or,
	Keyword_bitand,
	Keyword_bitor,
	Keyword_bitxor,
	Keyword_switch,
	Keyword_case,
	Keyword_DEF,
	Keyword_USE,
};

struct lex_val
{
	union
	{
		int intval;
		int64 int64val;
		double floatval;
		char symbol;
		Keyword keyword;
	};

	String string;
};

class GUIEXT Lexer : public Object
{
public:
	CTOR Lexer(Stream& stream);
	virtual ~Lexer();

	Token lex();

	void adv();
	int Getc();

	long parsenumber();

	Token m_token;
	lex_val m_val;

	Stream m_stream;
	char* m_buffer;
	ULONG m_fpos;
	int m_nstacked;

	ULONG m_line;

//private:
protected:

	bool ceof();
	void unGetc();

	long _getnumber();
	double getfrac();
	int lookexp();

	int m_c;
};

class GUIEXT Parser : public Object
{
public:

	CTOR Parser(Lexer* lexer);

	Expression* ParseExpression();
	Expression* ParseConditionalExpression();
	Expression* ParseLogicalORExpression();
	Expression* ParseLogicalANDExpression();
	Expression* ParseRelationalExpression();
	Expression* ParseAdditiveExpression();
	Expression* ParseMultiplicativeExpression();
	Expression* ParseUnaryExpression();
	Expression* ParseLeftHandSideExpression();
	Expression* ParseMemberExpression();
	Expression* ParsePrimaryExpression();


	bool ReadBool();
	int32 ReadInt32();
	float ReadFloat();
	double ReadDouble();

	void lex()
	{
		m_lexer->lex();
		m_token = m_lexer->m_token;
		m_val = m_lexer->m_val;
	//	return m_token;
	}

	void EatChar(int c);

	void read(char* buffer, int count);

	String readidentifier();
	String readstring();
	long getnumber();
	double getfnumber();

	bool IsSymbol(int c);
	bool IsKeyword(Keyword keyword);

	Lexer* m_lexer;

	Token m_token;
	lex_val m_val;

protected:

	inline bool eof()
	{
		return m_token == TOKEN_EOF;
	}
};

}
}
