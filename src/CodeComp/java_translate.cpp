#include "stdafx.h"
#include "java_translate.h"

namespace System
{
namespace java
{
using namespace std;

	/*
CodeCompExt void * TransStatement(A_Stm* stm)
{
	switch (stm->kind)
	{
	case A_Stm::A_EXP:
		{
			TransExpression(
		}
		break;
	}

	return NULL;
}
*/

	/*
T_Exp* T_Variable(const char* identifier)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_VARIABLE;
	p->identifier = strdup(identifier);
	return p;
}
*/

T_Exp* T_Member(T_Exp* left, const char* right)
{
	ASSERT(0);
	return NULL;
#if 0
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_MEMBER;
	p->member.left = left;
	p->member.right = strdup(right);
	return p;
#endif
}

Tr_Exp* TransExpression(A_Exp* exp)
{
	/*
	if (exp->kind == A_Exp::A_THIS)
	{
		Tr_Exp* pTExpr = Tr_Ex(T_Const(exp->int32));
	//	pTExpr->m_pType = new PrimitiveType(type_int);
		return pTExpr;
	}
	else
	*/
	if (exp->kind == A_Exp::A_IDLIST)
	{
		//return Tr_Ex(T_Mem(T_Variable(exp->idlist->head), -1));
		ASSERT(0);
	}
	else if (exp->kind == A_Exp::A_ID)
	{
		ASSERT(0);
		//return Tr_Ex(T_Mem(T_Variable(exp->id), -1));
	}
	else if (exp->kind == A_Exp::A_INT32)
	{
		Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(exp->int32));
	//	pTExpr->m_pType = new PrimitiveType(type_int);
		return pTExpr;
	}
	else if (exp->kind == A_Exp::A_BOOL)
	{
		Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(exp->boolValue));
	//	pTExpr->m_pType = new PrimitiveType(type_bool);
		return pTExpr;
	}
	else if (exp->kind == A_Exp::A_MEMBER)
	{
		Tr_Exp* tleft = TransExpression(exp->member.left);
		if (tleft == NULL)
			return NULL;

		T_Exp* left = unEx(tleft);
		
//		ASSERT(left->kind == T_Exp::T_MEM);
//		left = left->mem.mem;

	//	T_Exp* setMember = new T_Exp;
	//	setMember->kind ) 
		Tr_Exp* tr;

		/*
		tr = Tr_Ex(
			T_Mem(
			T_Binop('+', left, T_Const(pRightDeclarator->m_offset)), pRightDeclarator->m_pType->GetType()->get_sizeof()));
			*/
//		ASSERT(0);
		return Tr_Ex(T_Mem(T_Member(left, exp->member.right), -1));

		return tr;
	}
	else if (exp->kind == A_Exp::A_BINOP)
	{
		switch (exp->binop.op)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '|':
		case '&':
		case '^':
		case '==':
		case '>':
		case '>=':
		case '<':
		case '<=':
			{
				Tr_Exp* left = TransExpression(/*frame, */exp->binop.left/*, pGlobal, pScope*/);
				Tr_Exp* right = TransExpression(/*frame, */exp->binop.right/*, pGlobal, pScope*/);

				if (true)
				{
					T_Stm* s1 = /*T_Seq(*/T_CJumpStm(exp->binop.op, unEx(left), unEx(right), NULL, NULL);/*,
											T_Label(z));*/
					
					Tr_Exp* tr = Tr_Cx(new PatchList(s1/*->cjump.t*/, NULL), new PatchList(s1/*->cjump.f*/, NULL), s1);

					return tr;
				}
				else

			//	if (left->m_pType && right->m_pType)
				{
					Tr_Exp* tr = Tr_Ex(T_BinopExp(exp->binop.op, unEx(left), unEx(right)));

					return tr;
				}
			}
			break;

		case '=':
			{
				Tr_Exp* left = TransExpression(/*frame,*/ exp->binop.left);//, pGlobal, pScope);
				if (left == NULL)
				{
					return NULL;
				}
				else
				{
					Tr_Exp* right = TransExpression(/*frame,*/ exp->binop.right);//, pGlobal, pScope);

					if (right == NULL)
					{
						return NULL;
					}
					else
					{
						Tr_Exp* p = Tr_Nx(T_MoveStm(left->ex, unEx(right)));
					//	p->m_pType = left->m_pType;
						return p;
					}
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
	else
		ASSERT(0);

	return NULL;
}

CodeCompExt T_Stm* TransStatement(A_Stm* stm)
{
	switch (stm->GetKind())
	{
	case A_Stm::A_EXP:
		{
			A_ExpStm* expstm = (A_ExpStm*)stm;

			Tr_Exp* tr = TransExpression(/*frame,*/ expstm->m_exp/*, pGlobal, pScope*/);
			
			if (tr == NULL)
				return NULL;
			
			T_Stm* t = unNx(tr);
			//	t->m_line_pos = stm->exp->line_pos;
			
			return t;
		}
		break;
		
#if 0
	case A_Stm::A_IF:
		{
			Tr_Exp* tr = TransExpression(/*frame,*/ stm->IF.cond/*, pGlobal, pScope*/);

			if (tr == NULL)
				return NULL;

			ASSERT(0);
			return NULL;
		}
		break;
#endif

	default:
		ASSERT(0);
	}

	return NULL;
}

}
}
