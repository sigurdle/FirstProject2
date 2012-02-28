#include "stdafx.h"
#include "Expressive.h"

/*
#include "CodeComp/ir.h"

#pragma comment(lib, "CodeComp")
*/

namespace System
{
namespace Expressive
{

IO::TextWriter& WriteToStream(IO::TextWriter& stream, const Token& token)
{
	switch (token)
	{
	case TOKEN_INT:
	case TOKEN_UINT:
	case TOKEN_FLOAT:
		stream << "number";
		break;

	case TOKEN_KEYWORD:
		stream << "keyword";
		break;

	case TOKEN_STRING:
		stream << "string";
		break;

	case TOKEN_SYMBOL:
		stream << "symbol";
		break;
	}

	return stream;
}

Lexer::Lexer(StringIn filepath, IO::TextReader* stream) : m_filepath(filepath), m_stream(stream)
{
	m_buffer = new char[64];
	m_fpos = 0;
	m_nstacked = 0;

	m_loc.m_filepath = filepath;
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
		buffer[0] = m_c;
		size_t i = 1;
		adv();

		while (m_c != EOF)
		{
			if (!(isalnum(m_c) || m_c == '_'/* || m_c == '-')*/))
				break;

			if (i > 128)
			{
				raise(Exception("id too long"));
			}

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
		else if (wcscmp(buffer, L"val") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_val;
		}
		else if (wcscmp(buffer, L"div") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_div;
		}
		else if (wcscmp(buffer, L"mod") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_mod;
		}
		else if (wcscmp(buffer, L"expof") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_expof;
		}
		else if (wcscmp(buffer, L"DEF") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_DEF;
		}
		/*
		else if (wcscmp(buffer, L"USE") == 0)
		{
			m_token = TOKEN_KEYWORD;
			m_val.keyword = Keyword_USE;
		}
		*/
		else
		{
			m_val.string = string_copy(buffer);

			m_token = TOKEN_ID;
		}
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
		long integer = (long)_getnumber();

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

		IO::StringWriter str;

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

		m_val.string = str.str();

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
		if (m_c == '\n')
		{
			m_loc.m_column = 0;
			++m_loc.m_line;
		}
		return;
	}

	uint count = MIN(32, 64 - (m_fpos & 63));
	uint nRead = m_stream->ReadChars(m_buffer + (m_fpos & 63), count);
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
	if (m_fpos > 0)
	{
		if (m_c == '\n')
		{
			m_loc.m_column = 99999;	// TODO
			--m_loc.m_line;
		}

		++m_nstacked;
		--m_fpos;
		--m_loc.m_column;
		m_c = m_buffer[(m_fpos-1) & 63];
	}
	else
		ASSERT(0);
}

///////////////////////////////////////////////////////////
// Parser

Parser::Parser(Lexer* lexer) : m_lexer(lexer)
{
	m_out = Std::get_Out();

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
		FatalError(L"Parser: expected number");
}

String Parser::readidentifier()
{
	if (m_token != TOKEN_ID)
	{
		IO::StringWriter str;
		str << L"Expected identifier instead of " << m_token;
		/*
		switch (m_token)
		{
			case 
		}
		*/
		FatalError(str.str());
	}

	String id = m_val.string;
	lex();
	return id;
}

String Parser::readstring()
{
	if (m_token != TOKEN_STRING)
	{
		FatalError(L"Expected string");
	}

	String id = m_val.string;
	lex();
	return id;
}

void Parser::Warning(StringIn str)
{
	m_out << m_lexer->m_loc.m_filepath << "(" << (m_lexer->m_loc.m_line+1) << "," << (m_lexer->m_loc.m_column+1) << ")" << " warning : " << str << endl;
	++m_warnings;
}

void Parser::Error(StringIn str)
{
	m_out << m_lexer->m_loc.m_filepath << "(" << (m_lexer->m_loc.m_line+1) << "," << (m_lexer->m_loc.m_column+1) << ")" << " error : " << str << endl;
	++m_errors;
}

__declspec(noreturn) void Parser::FatalError(StringIn str)
{
	m_out << m_lexer->m_loc.m_filepath << "(" << (m_lexer->m_loc.m_line+1) << "," << (m_lexer->m_loc.m_column+1) << ")" << " fatal error : " << str << endl;
	++m_errors;
	raise(Exception("stopping"));
}

void Parser::EatChar(int c)
{
	if (m_token != TOKEN_SYMBOL || m_val.symbol != c)
	{
		IO::StringWriter str;
		str << "Expected " << c;
		FatalError(str.str());
	}

	lex();
}

AExpression* Parser::ParsePrimaryExpression()
{
	if (m_token == TOKEN_INT)
	{
		AExpression* exp = new AConstExpression<int>(m_loc, m_val.intval);
		lex();
		return exp;
	}
	else if (m_token == TOKEN_UINT)
	{
		AExpression* exp = new AConstExpression<unsigned int>(m_loc, m_val.uintval);
		lex();
		return exp;
	}
	else if (m_token == TOKEN_FLOAT)
	{
		AExpression* exp = new AConstExpression<float>(m_loc, m_val.floatval);
		lex();
		return exp;
	}
	else if (m_token == TOKEN_STRING)
	{
		AExpression* exp = new AStringExpression(m_loc, m_val.string);
		lex();
		return exp;
	}
	else if (m_token == TOKEN_ID)
	{
		AIdExpression* exp = new AIdExpression(m_loc, m_val.string);
		lex();
		return exp;
	}
	else if (IsSymbol('('))
	{
		lex();

		AExpression* exp = ParseExpression();
		EatChar(')');

		return exp;
	}
	else if (m_token == TOKEN_KEYWORD)
	{
		if (IsKeyword(Keyword_DEF))
		{
			lex();
			String name = readidentifier();
			AExpression* exp = ParseExpression();

		//	m_defs[name] = exp;

			return new ADEFExpression(m_loc, name, exp);
		//	return exp;//new DEFExpression(name, exp);
		}
		/*
		else if (IsKeyword(Keyword_USE))
		{
			ASSERT(0);
			lex();
			String name = readidentifier();

			//return new AUSEExpression(name);
		}
		*/
		else if (m_val.keyword == Keyword_true)
		{
			lex();
			return new AConstExpression<bool>(m_loc, true);
		}
		else if (m_val.keyword == Keyword_false)
		{
			lex();
			return new AConstExpression<bool>(m_loc, false);
		}
		else if (m_val.keyword == Keyword_null)
		{
			lex();
			return new ANullExpression(m_loc);
		}
		else if (m_val.keyword == Keyword_this)
		{
			lex();
			return new AThisExpression(m_loc);
		}

		FatalError("parse error");
		return NULL;
	}

	FatalError("missing Primary expression");
	return NULL;
}

AExpression* Parser::ParseMemberExpression()
{
	AExpression* left = ParsePrimaryExpression();
	ASSERT(left);

	while (IsSymbol('.'))
	{
		lex();

		left = new AMemberExpression(m_loc, left, readidentifier());
	}

	if (IsSymbol('{'))
	{
		lex();

		ANewObjProperties* pexp = new ANewObjProperties(m_loc, left);

		while (m_token != TOKEN_EOF)
		{
			if (IsSymbol('}'))
			{
				break;
			}

		//	ParseFieldValue();
			AExpression* exp = ParseExpression();

			//if (dynamic_cast<NewObjProperties*>(exp))
			if (IsSymbol(':'))
			{
				EatChar(':');
				AExpression* exp2 = ParseExpression();
				pexp->m_properties.push_back(pair<AExpression*,AExpression*>(exp, exp2));
			}
			else
			{
				pexp->m_properties.push_back(pair<AExpression*,AExpression*>(NULL, exp));
			}
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
		return pexp;
	}

	return left;
}

AExpression* Parser::ParseCallExpression()
{
	AExpression* exp = ParseMemberExpression();
	while (IsSymbol('('))
	{
		lex();
		ACallExpression* callexp = new ACallExpression(m_loc, exp);

	//	vector<Expression*> args;
		while (!IsSymbol(')'))
		{
			callexp->m_args.push_back(ParseExpression());
			if (IsSymbol(')'))
			{
				break;
			}
			EatChar(',');
		}
		EatChar(')');

		exp = callexp;
	}

	return exp;
}

AExpression* Parser::ParseUnaryExpression()
{
	// TODO while ?

	if (IsKeyword(Keyword_typeof))
	{
		lex();
		return new ATypeofExpression(m_loc, ParseUnaryExpression());
	}
	else if (IsKeyword(Keyword_expof))
	{
		lex();
		return new AExpressionExpression(m_loc, ParseUnaryExpression());
	}
	else if (IsSymbol('-'))
	{
		lex();
		return new AMinusUnaryExpression(m_loc, ParseUnaryExpression());
	}
	else if (IsSymbol('!'))
	{
		lex();
		return new ANotUnaryExpression(m_loc, ParseUnaryExpression());
	}
	else if (IsSymbol('+'))
	{
		lex();
		return ParseUnaryExpression();
	}
	else
	{
		return ParseCallExpression();
	}
}

AExpression* Parser::ParseMultiplicativeExpression()
{
	AExpression* left = ParseUnaryExpression();

	while (IsSymbol('*') || IsSymbol('/') || IsKeyword(Keyword_mod) || IsKeyword(Keyword_div))
	{
		int symbol = m_val.symbol;

		lex();
		AExpression* right = ParseUnaryExpression();

		if (symbol == '*')
		{
			left = new AMultiplyBinaryExpression(m_loc, left, right);
		}
		else if (symbol == '/')
		{
			left = new ADivideBinaryExpression(m_loc, left, right);
		}
		else
		{
			left = new AModulusBinaryExpression(m_loc, left, right);
		}
	}

	return left;
}

AExpression* Parser::ParseAdditiveExpression()
{
	AExpression* left = ParseMultiplicativeExpression();

	while (IsSymbol('+') || IsSymbol('-'))
	{
		int symbol = m_val.symbol;

		lex();
		AExpression* right = ParseMultiplicativeExpression();

		if (symbol == '+')
		{
			left = new APlusBinaryExpression(m_loc, left, right);
		}
		else
		{
			left = new AMinusBinaryExpression(m_loc, left, right);
		}
	}

	return left;
}

AExpression* Parser::ParseRelationalExpression()
{
	AExpression* left = ParseAdditiveExpression();

	while (
		IsSymbol('<') ||
		IsSymbol('>') ||
		IsSymbol('<=') ||
		IsSymbol('<=') ||
		IsSymbol('=') ||
		IsSymbol('!='))
	{
		int symbol = m_val.symbol;

		lex();
		AExpression* right = ParseAdditiveExpression();

		if (symbol == '<')
		{
			left = new ALTRelationalExpression(m_loc, left, right);
		}
		else if (symbol == '>')
		{
			left = new AGTRelationalExpression(m_loc, left, right);
		}
		else if (symbol == '>=')
		{
			left = new ALTEQRelationalExpression(m_loc, left, right);
		}
		else if (symbol == '>=')
		{
			left = new AGTEQRelationalExpression(m_loc, left, right);
		}
		else if (symbol == '=')
		{
			left = new AEQRelationalExpression(m_loc, left, right);
		}
		else if (symbol == '!=')
		{
			left = new ANEQRelationalExpression(m_loc, left, right);
		}
	}

	return left;
}

AExpression* Parser::ParseLogicalANDExpression()
{
	AExpression* left = ParseRelationalExpression();

	while (IsKeyword(Keyword_and))
	{
		lex();
		left = new ALogicalAndExpression(m_loc, left, ParseRelationalExpression());
	}

	return left;
}

AExpression* Parser::ParseLogicalORExpression()
{
	AExpression* left = ParseLogicalANDExpression();

	while (IsKeyword(Keyword_or))
	{
		lex();
		left = new ALogicalOrExpression(m_loc, left, ParseLogicalANDExpression());
	}

	return left;
}

AExpression* Parser::ParseConditionalExpression()
{
	if (IsKeyword(Keyword_if))
	{
		lex();

		AExpression* testExp = ParseExpression();
		if (IsKeyword(Keyword_then))
		{
			lex();

			AExpression* trueExp = ParseExpression();

			if (IsKeyword(Keyword_else))
			{
				lex();
				AExpression* falseExp = ParseExpression();
				return new AConditionalExpression(m_loc, testExp, trueExp, falseExp);
			}
			else
			{
				FatalError(L"Expected else keyword");
				return NULL;
			}
		}
		else
		{
			FatalError(L"Expected then keyword");
			return NULL;
		}
	}
	else
	{
		return ParseLogicalORExpression();
	}
}

AExpression* Parser::ParseExpression()
{
	return ParseConditionalExpression();
}

ADeclaration* Parser::ParseTopLevelDeclaration()
{
	if (IsKeyword(Keyword_val))
	{
		lex();

		String id = readidentifier();
		EatChar(':');
		AExpression* typeexp = ParseUnaryExpression();

		return new AValDeclaration(m_loc, id, typeexp);
	}
	else
	{
		return new AExpressionDeclaration(m_loc, ParseConditionalExpression());
	}
}

ADeclarationList* Parser::ParseProgram()
{
	ADeclarationList* dlist = new ADeclarationList;
	while (!eof())
	{
		ADeclaration* decl = ParseTopLevelDeclaration();

		dlist->m_items.push_back(decl);
		/*
		if (IsSymbol(';'))
		{
		}
		*/
	}

	return dlist;
}

// static
ADeclarationList* Parser::ProgramFromFile(StringIn filename)
{
	IO::FileStream file(filename, IO::FileMode_Open, IO::FileAccess_Read);
	return ParseProgram(&file);
}

// static
ADeclarationList* Parser::ParseProgram(IO::Stream* stream)
{
	IO::StreamReader reader(stream);
	Lexer lexer(stream->GetFilename(), &reader);
	Parser parser(&lexer);

	ADeclarationList* dlist = parser.ParseProgram();

	return dlist;
}

// static
AExpression* Parser::ParseExpression(StringIn filename, IO::TextReader* reader)
{
	Lexer lexer(filename, reader);
	Parser parser(&lexer);

	AExpression* exp = parser.ParseExpression();
	if (parser.m_token != TOKEN_EOF)
	{
		parser.FatalError("Syntax error");
	}

	return exp;
}

// static
AExpression* Parser::ExpressionFromString(StringIn str)
{
	IO::StringReader reader(str);
	return ParseExpression(nullptr, &reader);
}

// static
AExpression* Parser::ExpressionFromFile(StringIn filename)
{
	IO::FileStream file(filename, IO::FileMode_Open, IO::FileAccess_Read);
	IO::StreamReader reader(&file);
	return ParseExpression(filename, &reader);
}

}	// Gui
}	// System
