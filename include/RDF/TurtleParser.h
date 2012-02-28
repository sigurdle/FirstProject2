namespace System
{
namespace rdf
{

enum Token
{
	TOKEN_EOF = -1,
	TOKEN_INT,
	TOKEN_UINT,
	TOKEN_FLOAT,
	TOKEN_ID,
	TOKEN_AMPERSAND,
	TOKEN_KEYWORD,
	TOKEN_STRING,
	TOKEN_URI,
	TOKEN_SYMBOL,
};

enum Keyword
{
	Keyword_int,
	Keyword_word,
	Keyword_real,
	Keyword_true,
	Keyword_false,
	Keyword_null,
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

struct lex_loc
{
	uint m_line;
	uint m_column;
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

class RDFEXT Lexer : public Object
{
public:
	CTOR Lexer(Stream stream);
	virtual ~Lexer();

	Token lex();

	void adv();
	int Getc();
	void unGetc();

	int64 parsenumber();

	Token m_token;
	lex_val m_val;
	lex_loc m_loc;

	Stream m_stream;
	char* m_buffer;
	uint m_fpos;
	uint m_nstacked;

//	uint m_line;
//	uint m_column;

protected:

	bool ceof();
//	void unGetc();

	int64 _getnumber();
	double getfrac();
	int lookexp();

	int m_c;
};

class RDFEXT TurtleParser : public Object
{
public:

	CTOR TurtleParser(Lexer* lexer);

	void ParseDoc();
	void ParseStatement();

	bool IsDirective();
	void ParseDirective();

	void ParseTriples();
	Resource* ParseSubject();
	Predicate* ParseVerb();
	ObjectVariant ParseObject();
	void ParseObjectList(predicate verb, Resource* pSubject);
	void ParsePredicateObjectList(Resource* pSubject);

	bool IsResource();
	Predicate* ParseResource();

	bool IsSymbol(int c);
	bool IsKeyword(Keyword keyword);

	long getnumber();
	double getfnumber();
	String readidentifier();
	String readstring();

	void EatChar(int c);

	void lex()
	{
		m_lexer->lex();
		m_token = m_lexer->m_token;
		m_val = m_lexer->m_val;
		m_loc = m_lexer->m_loc;
	}

	void FatalError(StringIn str);

	static void Parse(StringIn filename);

	Lexer* m_lexer;

	String m_baseUri;

	Token m_token;
	lex_val m_val;
	lex_loc m_loc;
};

}	// RDF
}	// System
