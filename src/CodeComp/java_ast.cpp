#include "stdafx.h"
#include "java_ast.h"

namespace System
{
namespace java
{
using namespace std;

A_Exp* A_MemberExp(A_Exp* left, const char* right)
{
	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_MEMBER;
	p->member.left = left;
	p->member.right = _strdup(right);

	return p;
}

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

A_Exp* A_BoolExp(int boolValue)
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

A_Exp* A_QualifiedIdExp(A_Ids* idlist)
{
	A_Exp* p = new A_Exp;
	p->kind = A_Exp::A_IDLIST;
	p->idlist = idlist;
	p->line_pos = -1;

	return p;
}

/*
A_Stm* A_ExpStm(A_Exp* exp)
{
	A_Stm* p = new A_Stm;
	p->kind = A_Stm::A_EXP;
	p->exp = exp;
	return p;
}

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

A_Stm* A_CompoundStm(A_Stms* stmList)
{
	A_Stm* p = new A_Stm;
	p->kind = A_Stm::A_COMPOUND;
	p->compound = stmList;
	return p;
}
*/

A_Class* A_ClassDecl(const char* name, A_ClassBodyDecls* bodydecls)
{
	A_Class* p = new A_Class;
	p->name = _strdup(name);
	p->bodydecls = bodydecls;
	return p;
}

A_Method* A_MethodDecl(const char* name, A_Stms* body)
{
	A_Method* p = new A_Method;
	p->name = _strdup(name);
	p->body = body;
	return p;
}

A_ClassBodyDecl* A_ClassBodyClass(A_Class* pClass)
{
	A_ClassBodyDecl * p = new A_ClassBodyDecl;
	p->kind = A_ClassBodyDecl::A_CLASS;
	p->pClass = pClass;
	return p;
}

A_ClassBodyDecl* A_ClassBodyMethod(A_Method* pMethod)
{
	A_ClassBodyDecl * p = new A_ClassBodyDecl;
	p->kind = A_ClassBodyDecl::A_METHOD;
	p->pMethod = pMethod;
	return p;
}

A_ClassBodyDecl* A_ClassBodyBlock(bool bStatic, A_Stms* stms)
{
	A_ClassBodyDecl * p = new A_ClassBodyDecl;
	p->kind = A_ClassBodyDecl::A_BLOCK;
	p->block.bStatic = bStatic;
	p->block.stms = stms;
	return p;
}

}	// java
}
