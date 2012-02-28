#ifndef ecmascript_ast_h
#define ecmascript_ast_h

namespace System
{
class A_IdentifierList;

namespace ecma
{

class A_ExpList;
class A_StmList;
class A_ElemList;
class A_Function;

class ECMAEXT A_Exp : public Object
{
public:

	enum Kind : unsigned char
	{
		A_BINOP,
		A_UNOP,
		A_ID,
		A_MEMBER,
		A_BOOL,
		A_NULL,
		A_STRING,
		A_STRINGW,
		A_INT32,
		A_INT64,
		A_FLOAT64,
		A_CALL,
		A_NEW,
		A_FUNCTION,
	};

	Kind kind;

	virtual Kind get_Kind() const { return kind; }

	struct
	{
		struct
		{
			int op;
			A_Exp* left;
			A_Exp* right;
		}
		binop;

		struct
		{
			int op;
			A_Exp* exp;
		}
		unop;

		/*
		struct
		{
			A_TypeId* typeId;
			A_Exp* exp;
		}
		cast;
		*/

		bool boolValue;

		char* id;
	//	String stringw;
		long int32;
		LONGLONG int64;
//		double float64;
	};

	int line_pos;
};

class ECMAEXT A_MemberExp : public A_Exp
{
public:
	CTOR A_MemberExp(A_Exp* left, StringIn right)
	{
		kind = A_Exp::A_MEMBER;
		m_left = left;
		m_right = right;
	}

	virtual Kind get_Kind() const override
	{
		return A_MEMBER;
	}

	A_Exp* m_left;
	String m_right;
};

class A_CallExp : public A_Exp
{
public:
	CTOR A_CallExp(A_Exp* left, A_ExpList* args)
	{
		kind = A_CALL;
		m_left = left;
		m_args = args;
	}

	virtual Kind get_Kind() const override
	{
		return A_CALL;
	}

	A_Exp* m_left;
	A_ExpList* m_args;
};

class A_NewExp : public A_CallExp
{
public:
	CTOR A_NewExp(A_Exp* left, A_ExpList* args) : A_CallExp(left, args)
	{
		kind = A_NEW;
	}

	virtual Kind get_Kind() const override
	{
		return A_NEW;
	}
};

class Float64Exp : public A_Exp
{
public:
	CTOR Float64Exp(double number)
	{
		kind = A_FLOAT64;
		m_number = number;
	}

	double m_number;
};

class FunctionExp : public A_Exp
{
public:
	CTOR FunctionExp(A_Function* fun) : m_fun(fun)
	{
		kind = A_FUNCTION;
	}

	virtual Kind get_Kind() const override
	{
		return A_FUNCTION;
	}

	A_Function* m_fun;
};

class A_StringExp : public A_Exp
{
public:
	CTOR A_StringExp(StringIn str)
	{
		kind = A_STRING;
		m_string = str;
	}

	String m_string;
};

class A_StringWExp : public A_Exp
{
public:
	CTOR A_StringWExp(StringIn str)
	{
		kind = A_STRINGW;
		m_string = str;
	}

	String m_string;
};

class A_ExpList
{
public:

	CTOR A_ExpList(A_Exp* _head, A_ExpList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_Exp* head;
	A_ExpList* tail;
};

class A_Stm : public Object
{
public:

	enum Kind : unsigned char
	{
//		A_INVALID = -1,
		A_IF,
		A_VAR,
		A_FOR,
	//	A_SWITCH,
	//	A_WHILE,
	//	A_DOWHILE,
		A_RETURN,
		A_EXP,
	//	A_DECLARATION,
	//	A_EXP_OR_DECLARATION,
		A_COMPOUND,
	};

	virtual Kind GetKind() const = 0;

//	int m_line;

protected:

	CTOR A_Stm()
	{
	}
};

class A_ExpStm : public A_Stm
{
public:
	CTOR A_ExpStm(A_Exp* exp)
	{
		m_exp = exp;
	}

	virtual Kind GetKind() const override
	{
		return A_EXP;
	}

	A_Exp* m_exp;
};

class ECMAEXT A_CompoundStm : public A_Stm
{
public:
	CTOR A_CompoundStm(A_StmList* stmList)
	{
		m_stmList = stmList;
	}

	virtual Kind GetKind() const override
	{
		return A_COMPOUND;
	}

	A_StmList* m_stmList;
};

class ECMAEXT A_ReturnStm : public A_Stm
{
public:
	CTOR A_ReturnStm(A_Exp* exp)
	{
		m_exp = exp;
	}

	virtual Kind GetKind() const override
	{
		return A_RETURN;
	}

	A_Exp* m_exp;
};

class ECMAEXT A_IfStm : public A_Stm
{
public:
	CTOR A_IfStm(A_Exp* cond, A_Stm* stm, A_Stm* elseStm)
	{
		m_cond = cond;
		m_stm = stm;
		m_elseStm = elseStm;
	}

	virtual Kind GetKind() const override
	{
		return A_IF;
	}

	A_Exp* m_cond;
	A_Stm* m_stm;
	A_Stm* m_elseStm;
};

class A_ForStm : public A_Stm
{
public:
	CTOR A_ForStm(A_Exp* init, A_Exp* cond, A_Exp* exp, A_Stm* stm)
	{
		m_init = init;
		m_cond = cond;
		m_exp = exp;
		m_stm = stm;
	}

	virtual Kind GetKind() const override
	{
		return A_FOR;
	}

	int m_last_line;

	A_Exp* m_init;
	A_Exp* m_cond;
	A_Exp* m_exp;
	A_Stm* m_stm;
};

class A_VarDecl
{
public:
	CTOR A_VarDecl(StringIn identifier, A_Exp* initializer = NULL) :
		m_identifier(identifier),
		m_initializer(initializer)
	{
	}

	String m_identifier;
	A_Exp* m_initializer;
};

class A_VarDeclList
{
public:
	CTOR A_VarDeclList(A_VarDecl* _head, A_VarDeclList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_VarDecl* head;
	A_VarDeclList* tail;
};

class ECMAEXT A_VarStm : public A_Stm
{
public:
	CTOR A_VarStm(A_VarDeclList* vardecls)
	{
		m_vardecls = vardecls;
	}

	virtual Kind GetKind() const override
	{
		return A_VAR;
	}

	A_VarDeclList* m_vardecls;
};

class ECMAEXT A_StmList
{
public:
	CTOR A_StmList(A_Stm* stm, A_StmList* stmList)
	{
		head = stm;
		tail = stmList;
	}

	A_Stm* head;
	A_StmList* tail;
};

class ECMAEXT A_Function : public Object
{
public:
	CTOR A_Function(StringIn id, A_IdentifierList* formals, A_ElemList* body)
	{
		m_id = id;
		m_formals = formals;
		m_body = body;
	}

	String m_id;
	A_IdentifierList* m_formals;
	A_ElemList* m_body;
};

class ECMAEXT A_Elem
{
public:
	enum
	{
		A_FUNCTION,
		A_STATEMENT
	}
	kind;

	union
	{
		A_Function* fun;
		A_Stm* stm;
	};
};

class ECMAEXT A_ElemList
{
public:

	CTOR A_ElemList(A_Elem* elem, A_ElemList* elemList)
	{
		head = elem;
		tail = elemList;
	}

	A_Elem* head;
	A_ElemList* tail;
};

A_Exp* A_BinopExp(/*YYLTYPE& pos,*/ int op, A_Exp* e1, A_Exp* e2);
A_Exp* A_UnopExp(/*YYLTYPE& pos,*/ int op, A_Exp* e);
A_Exp* A_IdExp(const char* id);
A_Exp* A_Int32Exp(long num);
A_Exp* A_BoolExp(bool boolValue);
A_Exp* A_NullExp();

A_Elem* A_FunctionElem(A_Function* fun);
A_Elem* A_StatementElem(A_Stm* stm);

}	// ecma
}	// System

#endif // ecmascript_ast_h
