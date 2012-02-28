#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace EBNF
{

Lexer::Lexer(Stream& stream) : m_stream(stream)
{
	m_buffer = new char[64];
	m_fpos = 0;
	m_nstacked = 0;

	adv();
}

Lexer::~Lexer()
{
	delete[] m_buffer;
}

long Lexer::_getnumber()
{
	long number = 0;

	while (isdigit(m_c))
	{
		char c = m_c;
		adv();
		number = number*10 + (c - '0');
	}

	return number;
}

long Lexer::parsenumber()
{
	long fpos = m_fpos;

// get sign
	int sign = 1;

	if ((m_c == '-') || (m_c == '+'))
	{
		if (m_c == '-') sign = -1;
		adv();
	}

// get number
	long integer = _getnumber();

	if (m_fpos == fpos)
		throw std::exception("end of file");

	if (sign == -1) integer = -integer;

	return integer;
}

double Lexer::getfrac()
{
	double dig = 0.1;
	double val = 0;

	//const char* p = *s;

	while (isdigit(m_c))
	{
		char c = m_c;
		val += dig * (c - '0');

		dig = 0.1 * dig;

		adv();
	}

	return val;
}

int Lexer::lookexp()
{
	int c;
	int exp;

	int minus = 0;

	c = m_c;
	if (tolower(c) != 'e')
	{
		return 0;
	}
	adv();

	c = m_c;
	if (c == '-')
	{
		minus = 1;
		adv();
	}
	else if (c == '+')
	{
		adv();
	}
	else
		raise(Exception("expected -/+"));

	c = m_c;//*p++;
	if (c >= '0' && c <= '9')
	{
		exp = _getnumber();
	}
	else
	{
		return 0;
		//exp = 0;
		//p--;//myungetc(c);
	}

	if (minus)
		exp = -exp;

	//*s = p;

	return exp;
}

bool Lexer::ceof()
{
	return m_c == -1;
	// TODO
	ASSERT(0);
	return false;
	//return !(m_fpos < m_buflength);
}

int Lexer::Getc()
{
	int c = m_c;
	adv();
	return c;
}

Token Lexer::lex()
{
	while (m_c == ' ' || m_c == '\t' || m_c == '\n' || m_c == '\r')
	{
		adv();
	}

	while (m_c == '#')	// comment
	{
		adv();

		while (m_c != EOF && m_c != '\n')
		{
			adv();
		}

		while (m_c == ' ' || m_c == '\t' || m_c == '\n' || m_c == '\r')
		{
			adv();
		}
	}

	if (isalpha(m_c) || m_c == '_')
	{
		WCHAR buffer[256];
		int i = 0;
		buffer[i++] = m_c;
		adv();

		while (m_c != EOF)
		{
			if (!(isalnum(m_c) || m_c == '_' || m_c == '-'))
				break;

			buffer[i++] = m_c;
			adv();
		}
		buffer[i] = 0;

		if (wcscmp(buffer, L"true") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_true;
		}
		else if (wcscmp(buffer, L"false") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_false;
		}
		else if (wcscmp(buffer, L"null") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_null;
		}
		else if (wcscmp(buffer, L"if") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_if;
		}
		else if (wcscmp(buffer, L"then") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_then;
		}
		else if (wcscmp(buffer, L"else") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_else;
		}
		else if (wcscmp(buffer, L"this") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_this;
		}
		else if (wcscmp(buffer, L"and") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_and;
		}
		else if (wcscmp(buffer, L"or") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_or;
		}
		else if (wcscmp(buffer, L"bitand") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_bitand;
		}
		else if (wcscmp(buffer, L"bitor") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_bitor;
		}
		else if (wcscmp(buffer, L"bitxor") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_bitxor;
		}
		else
		{
			m_val.string = string_copy(buffer);

			m_token = TOKEN_ID;
		}
	}
	else if (isdigit(m_c)/* || m_c == '-' || m_c == '+'*/)
	{
//	long fpos = m_fpos;

		int sign = 1;

		if ((m_c == '-') || (m_c == '+'))
		{
			if (m_c == '-') sign = -1;
			adv();
		}

	// get number
		long integer = _getnumber();

		// get fraction
		double fraction;
		if (m_c == '.')
		{
			adv();
			fraction = getfrac();
			m_token = TOKEN_FLOAT;
		}
		else
		{
			/*
			if (sign == -1) integer = -integer;

			if (m_fpos == fpos)
				throw -1;
			return integer;
			*/
			fraction = 0;
			m_token = TOKEN_INT;
		}

		int exp = lookexp();

		if (exp != 0)
		{
			m_token = TOKEN_FLOAT;
		}

		double value = makeflt(integer, fraction, exp);

		if (m_token == TOKEN_INT)
		{
			if (sign == -1) integer = -integer;

			m_val.intval = integer;
		}
		else
		{
			if (sign == -1) value = -value;

			m_val.floatval = value;
		}
	}
	else if (m_c == '\"' || m_c == '\'')
	{
		int delimiter = m_c;

		StringStream str;

		adv();

		while (m_c != EOF)
		{
			if (m_c == delimiter)
				break;

			str << (WCHAR)m_c;
			adv();
		}

		if (m_c != delimiter)
		{
			raise(Exception("unexpected character"));
		}

		adv();

		m_val.string = str->str();

		m_token = TOKEN_STRING;
	}
	else if (m_c == '<' || m_c == '>')
	{
		m_token = TOKEN_SYMBOL;
		m_val.symbol = m_c;

		adv();

		if (m_c == '=')
		{
			m_val.symbol |= m_c<<8;
			adv();
		}
	}
	else
	{
		m_val.symbol = m_c;

		if (m_c == EOF)
			m_token = TOKEN_EOF;
		else
			m_token = TOKEN_SYMBOL;

		adv();
	}

	return m_token;
}

void Lexer::adv()
{
	// TODO, not buffered here
	if (m_nstacked > 0)
	{
		m_nstacked--;
		m_c = m_buffer[(m_fpos++) & 63];
		if (m_c == '\n') m_line++;
		return;
	}

	ULONG count = MIN(32, 64 - (m_fpos & 63));
	LONG nRead = m_stream.Read(m_buffer + (m_fpos & 63), count);
	m_nstacked = nRead - 1;
	if (m_nstacked > 0)
	{
		m_c = m_buffer[(m_fpos++) & 63];

		if (m_c == '\n') m_line++;
	}
	else
		m_c = -1;

#if 0
	if (m_fpos < m_buflength)
	{
		int c = m_buffer[m_fpos];

		if (c == '\n')
		{
			m_line++;
		}
		m_fpos++;

		return c;
	}
	else
		return -1;
#endif
	/*
	BYTE c;

	ULONG nRead;
	m_stream->Read(&c, 1, &nRead);
	if (nRead == 0)
	{
		m_eof = TRUE;
		return EOF;
	}

	return c;
	*/
}

void Lexer::unGetc()
{
	if (m_fpos > 1)
	{
		if (m_c == '\n') m_line--;

		m_nstacked++;
		m_fpos--;
		m_c = m_buffer[(m_fpos-1) & 63];

		/*
		int c = m_buffer[m_fpos];
		if (c == '\n')
		{
			m_line--;
		}
		*/
	}
	else
		ASSERT(0);

	/*
	LARGE_INTEGER li;
	li.QuadPart = -1;
	m_stream->Seek(li, STREAM_SEEK_CUR, NULL);
	m_eof = FALSE;
	*/
}

///////////////////////////////////////////////////////////
// Parser

Parser::Parser(Lexer* lexer) : m_lexer(lexer)
{
	lex();
}

bool Parser::IsSymbol(int c)
{
	if (m_token == TOKEN_SYMBOL && m_val.symbol == c)
		return true;
	else
		return false;
}

bool Parser::IsKeyword(Keyword keyword)
{
	if (m_token == TOKEN_KEYWORD && m_val.keyword == keyword)
		return true;
	else
		return false;
}

long Parser::getnumber()
{
	if (m_token != TOKEN_INT)
		raise(Exception("expected number"));

	int intval = m_val.intval;
	lex();

	return intval;
}

double Parser::getfnumber()
{
	if (m_token == TOKEN_FLOAT)
	{
		double floatval = m_val.floatval;
		lex();
		return floatval;
	}
	else if (m_token == TOKEN_INT)
	{
		double floatval = m_val.intval;
		lex();
		return floatval;
	}
	else
		raise(Exception("Parser: expected number"));
}

String Parser::readidentifier()
{
	if (m_token != TOKEN_ID)
	{
		raise(Exception(L"Expected identifier"));
	}

	String id = m_val.string;
	lex();
	return id;
}

String Parser::readstring()
{
	if (m_token != TOKEN_STRING)
	{
		raise(Exception(L"Expected string"));
	}

	String id = m_val.string;
	lex();
	return id;
}

void Parser::EatChar(int c)
{
	if (m_token != TOKEN_SYMBOL || m_val.symbol != c)
	{
		WCHAR msg[256];
		//swprintf_s(msg, L"Expected '%c'", c);
		ASSERT(0);
	//	fatalerror(msg);
	}

	lex();
}


Expression* Parser::ParsePrimaryExpression()
{
	if (m_token == TOKEN_INT)
	{
		Expression* exp = new ConstExpression<int>(getnumber());
		return exp;
	}
	else if (m_token == TOKEN_FLOAT)
	{
		Expression* exp = new ConstExpression<float>(getfnumber());
		return exp;
	}
	else if (m_token == TOKEN_KEYWORD)
	{
		if (m_val.keyword == Keyword_true)
		{
			return &ConstExpression<bool>::True;
		}
		else if (m_val.keyword == Keyword_false)
		{
			return &ConstExpression<bool>::False;
		}
		else if (m_val.keyword == Keyword_this)
		{
			return &ThisExpression::s_thisExp;
		}

		/*
		if (m_val.keyword == Keyword_if)
		{
			return IfExpression();
		}
		*/

		return NULL;
	}
	else if (m_token == TOKEN_ID)
	{
		String id = readidentifier();
		return new IdExpression(id);
	}

	return NULL;
}

Expression* Parser::ParseMemberExpression()
{
	Expression* left = ParsePrimaryExpression();

	while (IsSymbol('.'))
	{
		lex();

		left = new MemberExpression(left, readidentifier());
	}

	if (IsSymbol('{'))
	{
		lex();

		NewObjProperties* pexp = new NewObjProperties(left);

		while (!IsSymbol('}'))
		{
			Expression* exp = ParseExpression();
			//String name = readidentifier();

			Expression* exp2 = ParseExpression();

			pexp->m_properties.push_back(pair<Expression*,Expression*>(exp, exp2));
		}

		EatChar('}');

		/*
		multimap<String, NamedType*>::iterator it = pD->m_namedTypesM.find(id);
		if (it == pD->m_namedTypesM.end())
		{
			return NULL;
		}
		NamedType* pType = it->second;

		Object* obj = LoadObjectContent(pType);
		return new Expressive::StaticObjectExpression(obj);
		*/
		return NULL;
	}
	else
	{
	}

	return left;
}

Expression* Parser::ParseUnaryExpression()
{
	if (IsSymbol('-'))
	{
		lex();
		return new MinusUnaryExpression(ParseUnaryExpression());
	}
	else if (IsSymbol('!'))
	{
		lex();
		return new NotUnaryExpression(ParseUnaryExpression());
	}
	else if (IsSymbol('+'))
	{
		lex();
		return ParseUnaryExpression();
	}
	else
	{
		return ParseMemberExpression();
	}
}

Expression* Parser::ParseMultiplicativeExpression()
{
	Expression* left = ParseUnaryExpression();

	while (IsSymbol('*') || IsSymbol('/') || IsSymbol('%'))
	{
		Expression* right = ParseUnaryExpression();

		if (IsSymbol('*'))
		{
			lex();
			left = new MultiplyBinaryExpression(left, right);
		}
		else if (IsSymbol('/'))
		{
			lex();
			left = new DivideBinaryExpression(left, right);
		}
		else
		{
			lex();
			left = new ModulusBinaryExpression(left, right);
		}
	}

	return left;
}

Expression* Parser::ParseAdditiveExpression()
{
	Expression* left = ParseMultiplicativeExpression();

	while (IsSymbol('+') || IsSymbol('-'))
	{
		Expression* right = ParseMultiplicativeExpression();

		if (IsSymbol('+'))
		{
			lex();
			left = new PlusBinaryExpression(left, right);
		}
		else
		{
			lex();
			left = new MinusBinaryExpression(left, right);
		}
	}

	return left;
}

Expression* Parser::ParseRelationalExpression()
{
	Expression* left = ParseAdditiveExpression();

	while (
		IsSymbol('<') ||
		IsSymbol('>') ||
		IsSymbol('<=') ||
		IsSymbol('<=') ||
		IsSymbol('=') ||
		IsSymbol('!='))
	{
		Expression* right = ParseAdditiveExpression();

		if (IsSymbol('<'))
		{
			lex();
			left = new LTRelationalExpression(left, right);
		}
		else if (IsSymbol('>'))
		{
			lex();
			left = new GTRelationalExpression(left, right);
		}
		else if (IsSymbol('>='))
		{
			lex();
			left = new LTEQRelationalExpression(left, right);
		}
		else if (IsSymbol('>='))
		{
			lex();
			left = new GTEQRelationalExpression(left, right);
		}
		else if (IsSymbol('='))
		{
			lex();
			left = new EQRelationalExpression(left, right);
		}
		else if (IsSymbol('!='))
		{
			lex();
			left = new NEQRelationalExpression(left, right);
		}
	}

	return left;
}

Expression* Parser::ParseLogicalANDExpression()
{
	Expression* left = ParseRelationalExpression();

	while (IsKeyword(Keyword_and))
	{
		lex();
		left = new LogicalAndExpression(left, ParseRelationalExpression());
	}

	return left;
}

Expression* Parser::ParseLogicalORExpression()
{
	Expression* left = ParseLogicalANDExpression();

	while (IsKeyword(Keyword_or))
	{
		lex();
		left = new LogicalOrExpression(left, ParseLogicalANDExpression());
	}

	return left;
}

Expression* Parser::ParseConditionalExpression()
{
	if (IsKeyword(Keyword_if))
	{
		Expression* testExp = ParseExpression();
		if (IsKeyword(Keyword_then))
		{
			Expression* trueExp = ParseExpression();

			if (IsKeyword(Keyword_else))
			{
				Expression* falseExp = ParseExpression();
				return new ConditionalExpression(testExp, trueExp, falseExp);
			}
			else
			{
				raise(Exception("Expected else keyword"));
			}
		}
		else
		{
			raise(Exception("Expected then keyword"));
		}
	}
	else
	{
		return ParseLogicalORExpression();
	}
}

Rule* Parser::ParseRight()
{
}

Rule* Parser::ParseRule()
{
	String rulename = readidentifier();

	EatChar(':');

	while (!IsSymbol(';'))
	{
		ParseRight();
	}

	return ParseConditionalExpression();
}

}
}
