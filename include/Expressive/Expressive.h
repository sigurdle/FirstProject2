#ifndef System_Expressive_h
#define System_Expressive_h

#ifndef EXPEXT
#define EXPEXT DECLSPEC_DLLIMPORT
#endif

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

/*
#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/CodeComp.typeinfo"
#else
#include "CodeComp/CodeComp.h"
#endif
*/

namespace System
{
namespace Expressive
{

enum Kind
{
	Kind_Unk,
	Kind_NEWOBJ,
	Kind_CONST,
	Kind_String,
	Kind_ID,
	Kind_This,
	Kind_Relational,
	Kind_Conditional,
	Kind_Member,
	Kind_Typeof,
	Kind_Expof,
	Kind_Null,
};

struct lex_loc
{
	String m_filepath;
	uint m_line;
	uint m_column;
};

class EXPEXT AExpression : public Object
{
protected:
	CTOR AExpression(const lex_loc& loc) : m_loc(loc)
	{
	}

public:

	virtual Kind GetKind()
	{
		return Kind_Unk;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs)
	{
		return stream;
	}

	AExpression* m_parent;
	lex_loc m_loc;
};

class EXPEXT ADeclaration : public Object
{
public:
	CTOR ADeclaration(const lex_loc& loc) : m_loc(loc)
	{
	}

	lex_loc m_loc;
};

class EXPEXT AExpressionDeclaration : public ADeclaration
{
public:
	CTOR AExpressionDeclaration(const lex_loc& loc, AExpression* exp) : ADeclaration(loc), m_exp(exp)
	{
	}

	AExpression* m_exp;
};

class EXPEXT AValDeclaration : public ADeclaration
{
public:
	CTOR AValDeclaration(const lex_loc& loc, StringIn id, AExpression* typeexp) : ADeclaration(loc), m_id(id), m_typeexp(typeexp)
	{
	}

	String m_id;
	AExpression* m_typeexp;
};

class EXPEXT ADeclarationList : public Object
{
public:
	vector<ADeclaration*> m_items;
};

template<class T>
class AConstExpression : public AExpression
{
public:

	CTOR AConstExpression(const lex_loc& loc, T value) : AExpression(loc), m_value(value)
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_CONST;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << m_value;
		return stream;
	}

	T m_value;

//	static AConstExpression<bool> True;
//	static AConstExpression<bool> False;
};

class EXPEXT ANullExpression : public AExpression
{
public:

	CTOR ANullExpression(const lex_loc& loc) : AExpression(loc)
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_Null;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "nil";
		return stream;
	}
};

class EXPEXT AStringExpression : public AExpression
{
public:

	CTOR AStringExpression(const lex_loc& loc, StringIn str) : AExpression(loc), m_str(str)
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_String;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "\"" << m_str << "\"";
		return stream;
	}

	String m_str;
};

class EXPEXT AConditionalExpression : public AExpression
{
public:
	CTOR AConditionalExpression(const lex_loc& loc, AExpression* testExp, AExpression* trueExp, AExpression* falseExp) :
		AExpression(loc), 
		m_testExp(testExp),
		m_trueExp(trueExp),
		m_falseExp(falseExp)
	{
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "if ";
		m_testExp->WriteMLString(stream, defs);
		stream << " then ";
		m_trueExp->WriteMLString(stream, defs);
		stream << " else ";
		m_falseExp->WriteMLString(stream, defs);
		return stream;
	}

	virtual Kind GetKind() override
	{
		return Kind_Conditional;
	}

	AExpression* m_testExp;
	AExpression* m_trueExp;
	AExpression* m_falseExp;
};

class EXPEXT ADEFExpression : public AExpression
{
public:
	CTOR ADEFExpression(const lex_loc& loc, StringIn name, AExpression* exp) : AExpression(loc), m_name(name), m_exp(exp)
	{
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "DEF " << m_name;
		m_exp->WriteMLString(stream, defs);
		return stream;
	}

	String m_name;
	AExpression* m_exp;
};

class EXPEXT ATypeofExpression : public AExpression
{
public:
	CTOR ATypeofExpression(const lex_loc& loc, AExpression* exp) : AExpression(loc), m_exp(exp)
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_Typeof;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "typeof ";
		m_exp->WriteMLString(stream, defs);
		return stream;
	}

	AExpression* m_exp;
};

class EXPEXT AExpressionExpression : public AExpression
{
public:
	CTOR AExpressionExpression(const lex_loc& loc, AExpression* exp) : AExpression(loc), m_exp(exp)
	{
	}

	/*
	virtual Kind GetKind() override
	{
		return Kind_Typeof;
	}
	*/

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "expof ";
		m_exp->WriteMLString(stream, defs);
		return stream;
	}

	AExpression* m_exp;
};

class EXPEXT AUnaryExpression : public AExpression
{
public:
	CTOR AUnaryExpression(const lex_loc& loc, AExpression* exp) : AExpression(loc), m_exp(exp)
	{
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		PrintOp(stream);
		m_exp->WriteMLString(stream, defs);
		return stream;
	}

	virtual void PrintOp(IO::TextWriter& stream) abstract;

	AExpression* m_exp;
};

class EXPEXT ABinaryExpression : public AExpression
{
public:
	CTOR ABinaryExpression(const lex_loc& loc, AExpression* left, AExpression* right) : AExpression(loc), m_left(left), m_right(right)
	{
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs)
	{
		m_left->WriteMLString(stream, defs);
		PrintOp(stream);
		m_right->WriteMLString(stream, defs);
		return stream;
	}

	virtual int GetOperator() abstract;

	virtual void PrintOp(IO::TextWriter& stream) abstract;

	AExpression* m_left;
	AExpression* m_right;
};

class EXPEXT AMinusUnaryExpression : public AUnaryExpression
{
public:
	CTOR AMinusUnaryExpression(lex_loc& loc, AExpression* exp) : AUnaryExpression(loc, exp)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "-";
	}
};

class EXPEXT ANotUnaryExpression : public AUnaryExpression
{
public:
	CTOR ANotUnaryExpression(lex_loc& loc, AExpression* exp) : AUnaryExpression(loc, exp)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "!";
	}
};

class EXPEXT AMinusBinaryExpression : public ABinaryExpression
{
public:
	CTOR AMinusBinaryExpression(lex_loc& loc, AExpression* left, AExpression* right) : ABinaryExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "-";
	}

	virtual int GetOperator() override
	{
		return '-';
	}
};

class EXPEXT APlusBinaryExpression : public ABinaryExpression
{
public:
	CTOR APlusBinaryExpression(lex_loc& loc, AExpression* left, AExpression* right) : ABinaryExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "+";
	}

	virtual int GetOperator() override
	{
		return '+';
	}
};

class EXPEXT AMultiplyBinaryExpression : public ABinaryExpression
{
public:
	CTOR AMultiplyBinaryExpression(lex_loc& loc, AExpression* left, AExpression* right) : ABinaryExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "*";
	}

	virtual int GetOperator() override
	{
		return '*';
	}
};

class EXPEXT ADivideBinaryExpression : public ABinaryExpression
{
public:
	CTOR ADivideBinaryExpression(lex_loc& loc, AExpression* left, AExpression* right) : ABinaryExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "/";
	}

	virtual int GetOperator() override
	{
		return '/';
	}
};

class EXPEXT AModulusBinaryExpression : public ABinaryExpression
{
public:
	CTOR AModulusBinaryExpression(lex_loc& loc, AExpression* left, AExpression* right) : ABinaryExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "%";
	}

	virtual int GetOperator() override
	{
		return '%';
	}
};

class EXPEXT ARelationalExpression : public ABinaryExpression
{
public:
	CTOR ARelationalExpression(lex_loc& loc, AExpression* left, AExpression* right) : ABinaryExpression(loc, left, right)
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_Relational;
	}
};

class EXPEXT ALogicalExpression : public ABinaryExpression
{
public:
	CTOR ALogicalExpression(lex_loc& loc, AExpression* left, AExpression* right) : ABinaryExpression(loc, left, right)
	{
	}
};

class EXPEXT AEQRelationalExpression : public ARelationalExpression
{
public:
	CTOR AEQRelationalExpression(lex_loc& loc, AExpression* left, AExpression* right) : ARelationalExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "=";
	}

	virtual int GetOperator() override
	{
		return '=';
	}
};

class EXPEXT ANEQRelationalExpression : public ARelationalExpression
{
public:
	CTOR ANEQRelationalExpression(lex_loc& loc, AExpression* left, AExpression* right) : ARelationalExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "!=";
	}

	virtual int GetOperator() override
	{
		return '!=';
	}
};

class EXPEXT ALTRelationalExpression : public ARelationalExpression
{
public:
	CTOR ALTRelationalExpression(lex_loc& loc, AExpression* left, AExpression* right) : ARelationalExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "<";
	}

	virtual int GetOperator() override
	{
		return '<';
	}
};

class EXPEXT ALTEQRelationalExpression : public ARelationalExpression
{
public:
	CTOR ALTEQRelationalExpression(lex_loc& loc, AExpression* left, AExpression* right) : ARelationalExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "<=";
	}

	virtual int GetOperator() override
	{
		return '<=';
	}
};

class EXPEXT AGTRelationalExpression : public ARelationalExpression
{
public:
	CTOR AGTRelationalExpression(lex_loc& loc, AExpression* left, AExpression* right) : ARelationalExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << ">";
	}

	virtual int GetOperator() override
	{
		return '>';
	}
};

class EXPEXT AGTEQRelationalExpression : public ARelationalExpression
{
public:
	CTOR AGTEQRelationalExpression(lex_loc& loc, AExpression* left, AExpression* right) : ARelationalExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << ">=";
	}

	virtual int GetOperator() override
	{
		return '>=';
	}
};

class EXPEXT ALogicalOrExpression : public ALogicalExpression
{
public:
	CTOR ALogicalOrExpression(lex_loc& loc, AExpression* left, AExpression* right) : ALogicalExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "or";
	}

	virtual int GetOperator() override
	{
		return '||';
	}
};

class EXPEXT ALogicalAndExpression : public ALogicalExpression
{
public:
	CTOR ALogicalAndExpression(lex_loc& loc, AExpression* left, AExpression* right) : ALogicalExpression(loc, left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "and";
	}

	virtual int GetOperator() override
	{
		return '&&';
	}
};

class EXPEXT AObjectExpression : public AExpression
{
public:
	CTOR AObjectExpression(const lex_loc& loc) : AExpression(loc)
	{
	}
};

class EXPEXT AThisExpression : public AObjectExpression
{
public:
	CTOR AThisExpression(lex_loc& loc) : AObjectExpression(loc)
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_This;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "this";
		return stream;
	}

//	static AThisExpression s_thisExp;
};

class EXPEXT AMemberExpression : public AExpression
{
public:

	CTOR AMemberExpression(const lex_loc& loc, AExpression* object, StringIn id) : AExpression(loc), m_object(object), m_id(id)
	{
		ASSERT(object);
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		m_object->WriteMLString(stream, defs);
		stream << ".";
		stream << m_id;
		return stream;
	}

	virtual Kind GetKind() override
	{
		return Kind_Member;
	}

	AExpression* m_object;
	String m_id;
};

class EXPEXT AIdExpression : public AExpression
{
public:

	CTOR AIdExpression(lex_loc& loc, StringIn id) : AExpression(loc), m_id(id)
	{
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << m_id;
		return stream;
	}

	virtual Kind GetKind()
	{
		return Kind_ID;
	}

	String m_id;
};

class EXPEXT ANewObjProperties : public AExpression
{
public:

	CTOR ANewObjProperties(lex_loc& loc, AExpression* obj) : AExpression(loc), m_obj(obj)
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_NEWOBJ;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
	//	m_object->WriteMLString(stream, defs);
	//	stream << ".";
	//	stream << m_id;
		ASSERT(0);
		return stream;
	}

	AExpression* m_obj;

	vector<pair<AExpression*, AExpression*> > m_properties;
};

class EXPEXT ACallExpression : public AExpression
{
public:

	CTOR ACallExpression(lex_loc& loc, AExpression* name) : AExpression(loc), m_name(name)
	{
	}

	/*
	virtual Kind GetKind() override
	{
		return Kind_NEWOBJ;
	}
	*/

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		m_name->WriteMLString(stream, defs);
		stream << "(";

		for (uint i = 0; i < m_args.size(); ++i)
		{
			if (i > 0) stream << ", ";
			m_args[i]->WriteMLString(stream, defs);
		}

		stream << ")";
		return stream;
	}

	AExpression* m_name;
	vector<AExpression*> m_args;
};

}	// Expressive
}	// System

#include "Parser.h"

#endif	// System_Expressive_h
