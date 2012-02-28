#include "stdafx.h"
#include "RDF.h"

namespace System
{
namespace rdf
{

Lexer::Lexer(Stream stream) : m_stream(stream)
{
	m_buffer = new char[64];
	m_fpos = 0;
	m_nstacked = 0;

	m_loc.m_line = 0;
	m_loc.m_column = 0;

	adv();
}

Lexer::~Lexer()
{
	delete[] m_buffer;
}

int64 Lexer::_getnumber()
{
	int64 number = 0;

	while (isdigit(m_c))
	{
		char c = m_c;
		adv();
		number = number*10 + (c - '0');
	}

	return number;
}

int64 Lexer::parsenumber()
{
	uint fpos = m_fpos;

// get sign
	int sign = 1;

	if ((m_c == '-') || (m_c == '+'))
	{
		if (m_c == '-') sign = -1;
		adv();
	}

// get number
	int64 integer = _getnumber();

	if (m_fpos == fpos)
		raise(Exception("end of file"));

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
	bool more;

	do
	{
		while (m_c == ' ' || m_c == '\t' || m_c == '\n' || m_c == '\r')
		{
			adv();
		}

		more = false;

		if (m_c == '(')	// comment	?
		{
			adv();
			if (m_c == '*')	// comment
			{
				adv();

				while (m_c != EOF)
				{
					if (m_c == '*')
					{
						adv();
						if (m_c == ')')
						{
							adv();
							break;
						}
					}
					adv();
				}

				more = true;
			}
			else
			{
				unGetc();
			}
		}
	}
	while (more);

	if (isalpha(m_c) || m_c == '_')
	{
		WCHAR buffer[256];
		int i = 0;
		buffer[i++] = m_c;
		adv();

		while (m_c != EOF)
		{
			if (i > 250)
			{
				raise(Exception("ident too long"));
			}

			if (!(isalnum(m_c) || m_c == '_' || m_c == '-'))
				break;

			buffer[i++] = m_c;
			adv();
		}
		buffer[i] = 0;

		if (wcscmp(buffer, L"int") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_int;
		}
		else if (wcscmp(buffer, L"word") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_word;
		}
		else if (wcscmp(buffer, L"real") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_real;
		}
		else if (wcscmp(buffer, L"true") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_true;
		}
		else if (wcscmp(buffer, L"false") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_false;
		}
		else if (wcscmp(buffer, L"nil") == 0)
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
		else if (wcscmp(buffer, L"typeof") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_typeof;
		}
		else if (wcscmp(buffer, L"raise") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_raise;
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
		else
		{
			m_val.string = string_copy(buffer);

			m_token = TOKEN_ID;
		}
	}
	else if (m_c == '@')
	{
		adv();

		WCHAR buffer[64];
		int i = 0;
		buffer[i++] = m_c;

		while (m_c != EOF)
		{
			if (i > 60)
			{
				raise(Exception("@ident too long"));
			}
			if (!(isalnum(m_c) || m_c == '_' || m_c == '-'))
				break;

			buffer[i++] = m_c;
			adv();
		}
		buffer[i] = 0;

		m_val.string = string_copy(buffer);

		m_token = TOKEN_AMPERSAND;
	}
	else if (isdigit(m_c)/* || m_c == '-' || m_c == '+'*/)
	{
//	long fpos = m_fpos;

		if (m_c == '0')
		{
			adv();
			if (m_c == 'w')
			{
				adv();
				int64 integer = _getnumber();

				m_token = TOKEN_UINT;
				m_val.uintval = integer;

				return m_token;
			}
			else
				unGetc();

				/*
			if (m_c == 'x')
		{
			ASSERT(0);
		}
		*/
		}


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
	else if (m_c == '<')
	{
		int delimiter = '>';

		StringStream str;

		adv();

		while (m_c != EOF)
		{
			if (m_c == '\\')
			{
				ASSERT(0);
			}

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

		m_token = TOKEN_URI;
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
	else if (m_c == '^')
	{
		m_token = TOKEN_SYMBOL;
		m_val.symbol = m_c;

		adv();

		if (m_c == '^')
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
		if (m_c == '\n')
		{
			m_loc.m_column = 0;
			++m_loc.m_line;
		}
		return;
	}

	uint count = MIN(32, 64 - (m_fpos & 63));
	uint nRead = m_stream.ReadChars(m_buffer + (m_fpos & 63), count);
	if (nRead > 0)
	{
		m_nstacked = nRead - 1;

		m_c = m_buffer[(m_fpos++) & 63];

		if (m_c == '\n')
		{
			m_loc.m_column = 0;
			++m_loc.m_line;
		}
	}
	else
		m_c = -1;
}

void Lexer::unGetc()
{
	if (m_fpos > 1)
	{
		if (m_c == '\n')
		{
			--m_loc.m_line;
		}

		++m_nstacked;
		m_fpos--;
		m_c = m_buffer[(m_fpos-1) & 63];
	}
	else
		ASSERT(0);
}

TurtleParser::TurtleParser(Lexer* lexer) : m_lexer(lexer)
{
	lex();
}

bool TurtleParser::IsSymbol(int c)
{
	if (m_token == TOKEN_SYMBOL && m_val.symbol == c)
		return true;
	else
		return false;
}

bool TurtleParser::IsKeyword(Keyword keyword)
{
	if (m_token == TOKEN_KEYWORD && m_val.keyword == keyword)
		return true;
	else
		return false;
}

long TurtleParser::getnumber()
{
	if (m_token != TOKEN_INT)
		raise(Exception("expected number"));

	int intval = m_val.intval;
	lex();

	return intval;
}

double TurtleParser::getfnumber()
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

String TurtleParser::readidentifier()
{
	if (m_token != TOKEN_ID)
	{
		raise(Exception(L"Expected identifier"));
	}

	String id = m_val.string;
	lex();
	return id;
}

String TurtleParser::readstring()
{
	if (m_token != TOKEN_STRING)
	{
		raise(Exception(L"Expected string"));
	}

	String id = m_val.string;
	lex();
	return id;
}

// static
void TurtleParser::Parse(StringIn filename)
{
	Lexer lexer(FileStream(filename, 1, 1));
	TurtleParser parser(&lexer);

	parser.ParseDoc();
}

void TurtleParser::ParseDoc()
{
	while (m_token != TOKEN_EOF)
	{
		ParseStatement();
	}
}

void TurtleParser::ParseStatement()
{
	if (IsDirective())
	{
		ParseDirective();
	}
	else
	{
		ParseTriples();
		EatChar('.');
	}
}

bool TurtleParser::IsDirective()
{
	if (m_token == TOKEN_AMPERSAND)
	{
		return true;
	}
	return false;
}

void TurtleParser::ParseDirective()
{
	if (m_val.string == "prefix")
	{
		readidentifier();
		EatChar(':');
		if (m_token != TOKEN_URI)
		{
			raise(Exception("Expected uri"));
		}
		m_val.string;
	}
	else if (m_val.string == "base")
	{
		if (m_token != TOKEN_URI)
		{
			raise(Exception("Expected uri"));
		}

		m_baseUri = m_val.string;
	}
	else
		raise(Exception("unknown @"));
}

void TurtleParser::ParseTriples()
{
	Resource* pSubject = ParseSubject();
	ParsePredicateObjectList(pSubject);
}

Resource* TurtleParser::ParseSubject()
{
	if (m_token == TOKEN_URI)
	{
		lex();
		return GetSubject(m_val.string);
	}

	raise(Exception("Syntax error"));
	return NULL;
}

void TurtleParser::ParsePredicateObjectList(Resource* pSubject)
{
	while (1)
	{
		predicate verb = ParseVerb();
		ParseObjectList(verb, pSubject);

		if (IsSymbol(';'))
		{
			lex();
		}
		else
			break;
	}
}

void TurtleParser::ParseObjectList(predicate pred, Resource* pSubject)
{
	while (1)
	{
		ObjectVariant obj = ParseObject();

		pSubject->SetProperty(pred, obj);

		if (IsSymbol(','))
		{
			lex();
		}
		else
			break;
	}
}

ObjectVariant TurtleParser::ParseObject()
{
	if (IsResource())
	{
		return ParseResource();
	}
	else if (m_token == TOKEN_INT)
	{
		return Literal(getnumber());
	}
	else if (m_token == TOKEN_FLOAT)
	{
		return Literal(getfnumber());
	}
	else if (m_token == TOKEN_STRING)
	{
		String str = readstring();
		if (IsSymbol('^^'))
		{
			lex();
			Resource* datatype = ParseResource();
			return Literal(str, datatype);
		}
		else
		{
			return Literal(str);
		}
	}
	/*
	else if (IsSymbol('_:'))	// blank
	{
		lex();
		String id = readidentifier();
	}
	*/

	// resource | blank | literal
	raise(Exception("TODO"));
	return NULL;
}

bool TurtleParser::IsResource()
{
	if (m_token == TOKEN_URI)
	{
		return true;
	}
	else if (m_token == TOKEN_ID)
	{
		return true;
	}

	return false;
}

Predicate* TurtleParser::ParseVerb()
{
	if (m_token == TOKEN_ID && m_val.string == "a")
	{
		lex();
		return RDF::get_type();
	}
	else
	{
		Predicate* pred = ParseResource();
		return pred;
	}
}

Predicate* TurtleParser::ParseResource()
{
	if (m_token == TOKEN_URI)
	{
		lex();
		return GetSubject(m_val.string);
	}
	else if (m_token == TOKEN_ID)
	{
		ASSERT(0);
	}

	raise(Exception("Syntax error"));
	return NULL;
}

void TurtleParser::EatChar(int c)
{
	if (m_token != TOKEN_SYMBOL || m_val.symbol != c)
	{
		StringStream str;
		str << "Expected " << c;
		FatalError(str->str());
	}

	lex();
}

void TurtleParser::FatalError(StringIn str)
{
	raise(Exception(str));
}

}	// rdf
}	// System
