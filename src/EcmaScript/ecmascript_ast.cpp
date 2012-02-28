#include "stdafx.h"
#include "EcmaScript.h"
#include "ecmascript_ast.h"

namespace System
{
namespace ecma
{
using namespace std;

/*
A_Exp* A_MemberExp(A_Exp* left, StringIn right)
{
	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_MEMBER;
	p->member.left = left;
	p->member.right = right;

	return p;
}
*/

A_Exp* A_BinopExp(/*YYLTYPE& pos,*/ int op, A_Exp* left, A_Exp* right)
{
	ASSERT(left != NULL);
	ASSERT(right != NULL);

	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_BINOP;
//	p->line_pos = pos.first_line;

	p->binop.op = op;
	p->binop.left = left;
	p->binop.right = right;

	return p;
}

A_Exp* A_UnopExp(/*YYLTYPE& pos,*/ int op, A_Exp* exp)
{
#if 0	// TODO, have this
	ASSERT(exp != NULL);
#endif

	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_UNOP;
//	p->line_pos = pos.first_line;
	p->unop.op = op;
	p->unop.exp = exp;

	return p;
}

A_Exp* A_Int32Exp(long num)
{
	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_INT32;
	p->int32 = num;

	return p;
}

A_Exp* A_BoolExp(bool boolValue)
{
	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_BOOL;
	p->boolValue = boolValue;

	return p;
}

A_Exp* A_NullExp()
{
	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_NULL;

	return p;
}

A_Exp* A_IdExp(const char* id)
{
	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_ID;
	p->id = _strdup(id);
	p->line_pos = -1;

	return p;
}

/*
A_Stm* A_ExpStm(A_Exp* exp)
{
	A_ExpStm* p = new A_Stm;
	p->kind = A_Stm::A_EXP;
	p->exp = exp;
	return p;
}
*/

/*
A_Stm* A_IfStm(A_Exp* cond, A_Stm* stm, A_Stm* elseStm)
{
	A_Stm* p = new A_Stm;
	p->kind = A_Stm::A_IF;
	p->IF.cond = cond;
	p->IF.stm = stm;
	p->IF.elseStm = elseStm;
	return p;
}

A_Stm* A_ReturnStm(A_Exp* exp)
{
	A_Stm* p = new A_Stm;
	p->kind = A_Stm::A_RETURN;
	p->exp = exp;
	return p;
}

A_Stm* A_CompoundStm(A_StmList* stmList)
{
	A_Stm* p = new A_Stm;
	p->kind = A_Stm::A_COMPOUND;
	p->compound = stmList;
	return p;
}
*/


/*A_Fun* A_Function(const char* id, A_ElemList* body)
{
	A_Fun* p = new A_Fun;
	p->id = id;
	p->body = body;

	return p;
}
*/

A_Elem* A_FunctionElem(A_Function* fun)
{
	A_Elem* p = new A_Elem;
	p->kind = A_Elem::A_FUNCTION;
	p->fun = fun;
	return p;
}

A_Elem* A_StatementElem(A_Stm* stm)
{
	A_Elem* p = new A_Elem;
	p->kind = A_Elem::A_STATEMENT;
	p->stm = stm;
	return p;
}

}	// ecma
}
