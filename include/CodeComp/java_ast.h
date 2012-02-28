#pragma once

namespace System
{
namespace java
{

class A_Stms;
class A_Ids;
class A_Class;
class A_ClassBodyDecls;

class A_Exp : public System::Object
{
public:
	enum
	{
		A_BINOP,
		A_UNOP,
		A_ID,
		A_IDLIST,
		A_MEMBER,
		A_BOOL,
		A_NULL,
		A_STRING,
		A_LSTRING,
		A_INT32,
		A_INT64,
	//	A_CAST,
		A_CALL,
	}
	kind;

	union
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

		struct
		{
			A_Exp* left;
		//	ecma_A_ExpList* args;
		}
		call;

		struct
		{
			A_Exp* left;
			char* right;
		}
		member;

		int boolValue;

		char* id;
		A_Ids* idlist;
		char* string;
		long int32;
		LONGLONG int64;
	};

	int line_pos;
};

class A_ExpList : public System::Object
{
public:
	A_ExpList(A_Exp* head, A_ExpList* tail)
	{
		m_head = head;
		m_tail = tail;
	}

	A_Exp* m_head;
	A_ExpList* m_tail;
};

class A_Stm : public System::Object
{
public:

	enum Kind
	{
		//A_INVALID = -1,
		A_IF,
	//	A_SWITCH,
	//	A_WHILE,
	//	A_DOWHILE,
		A_RETURN,
		A_EXP,
	//	A_DECLARATION,
	//	A_EXP_OR_DECLARATION,
		A_COMPOUND,
	};

	virtual Kind GetKind() = 0;

	A_Stm()
	{
		//kind = A_INVALID;
	}

//	int m_line;
};

class A_IfStm : public A_Stm
{
public:
	A_IfStm(A_Exp* cond, A_Stm* stm, A_Stm* elseStm)
	{
		m_cond = cond;
		m_stm = stm;
		m_elseStm = elseStm;
	}

	virtual Kind GetKind()
	{
		return A_IF;
	}

	A_Exp* m_cond;
	A_Stm* m_stm;
	A_Stm* m_elseStm;

};

class A_CompoundStm : public A_Stm
{
public:
	A_CompoundStm(A_Stms* compound)
	{
		m_compound = compound;
	}

	virtual Kind GetKind()
	{
		return A_COMPOUND;
	}

	A_Stms* m_compound;
};

class A_ReturnStm : public A_Stm
{
public:
	A_ReturnStm(A_Exp* exp)
	{
		m_exp = exp;
	}

	virtual Kind GetKind()
	{
		return A_RETURN;
	}

	A_Exp* m_exp;
};

class A_ExpStm : public A_Stm
{
public:
	A_ExpStm(A_Exp* exp)
	{
		m_exp = exp;
	}

	virtual Kind GetKind()
	{
		return A_EXP;
	}

	A_Exp* m_exp;
};

class A_Method
{
public:
	char* name;
	A_Stms* body;
};

class A_ClassBodyDecl
{
public:
	enum
	{
		A_METHOD,
		A_CLASS,
		A_BLOCK,
	}
	kind;

	union
	{
		A_Method* pMethod;
		A_Class* pClass;

		struct
		{
			A_Stms* stms;
			bool bStatic;
		}
		block;
	};
};

class A_Class
{
public:
	char* name;
	A_ClassBodyDecls* bodydecls;
};

class A_Stms
{
public:

	A_Stms(A_Stm* stm, A_Stms* stms)
	{
		head = stm;
		tail = stms;
	}

	A_Stm* head;
	A_Stms* tail;
};

class A_ClassBodyDecls
{
public:

	A_ClassBodyDecls(A_ClassBodyDecl * _head, A_ClassBodyDecls * _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_ClassBodyDecl* head;
	A_ClassBodyDecls* tail;
};

class A_Ids
{
public:

	A_Ids(const char* _head, A_Ids* _tail)
	{
		head = _strdup(_head);
		tail = _tail;
	}

	char* head;
	A_Ids* tail;
};

/*
class A_Fun
{
public:
	const char* id;
	A_ElemList* body;
};

class A_Elem
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
		A_Fun* fun;
		A_Stm* stm;
	};
};

class A_ElemList
{
public:

	A_ElemList(A_Elem* elem, A_ElemList* elemList)
	{
		head = elem;
		tail = elemList;
	}

	A_Elem* head;
	A_ElemList* tail;
};
*/

//A_Fun* A_Function(const char* id, A_ElemList* body);

A_Exp* A_BinopExp(/*YYLTYPE& pos,*/ int op, A_Exp* e1, A_Exp* e2);
A_Exp* A_UnopExp(/*YYLTYPE& pos,*/ int op, A_Exp* e);
A_Exp* A_IdExp(const char* id);
A_Exp* A_QualifiedIdExp(A_Ids* idlist);
A_Exp* A_MemberExp(A_Exp* left, const char* right);
/*
CodeCompExt A_Exp* A_IdExp(YYLTYPE& pos, const char* id);
CodeCompExt A_Exp* A_StringExp(const char* string);
CodeCompExt A_Exp* A_LStringExp(const char* string);
*/
A_Exp* A_Int32Exp(long num);
A_Exp* A_BoolExp(int boolValue);
A_Exp* A_NullExp();
/*
CodeCompExt A_Exp* A_CastExp(A_TypeId* typeId, A_Exp* exp);
CodeCompExt A_Exp* A_CallExp(YYLTYPE& pos, A_Exp* f, A_ExpList* args);
*/

/*
A_Stm* A_ExpStm(A_Exp* exp);
A_Stm* A_ReturnStm(A_Exp* exp);
A_Stm* A_IfStm(A_Exp* cond, A_Stm* stm, A_Stm* elseStm);
A_Stm* A_CompoundStm(A_Stms* stmList);
*/

A_Class* A_ClassDecl(const char* name, A_ClassBodyDecls* bodydecls);

A_Method* A_MethodDecl(const char* name, A_Stms* body);

A_ClassBodyDecl* A_ClassBodyClass(A_Class* pClass);
A_ClassBodyDecl* A_ClassBodyMethod(A_Method* pMethod);
A_ClassBodyDecl* A_ClassBodyBlock(bool bStatic, A_Stms* stms);

}	// java
}
