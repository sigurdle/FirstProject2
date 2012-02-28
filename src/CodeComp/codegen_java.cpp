#include "stdafx.h"
#include "codegen_java.h"

namespace System
{
namespace java
{

// munch

void munchExp(T_Exp* e)
{
	switch (e->kind)
	{
		/*
	case T_Exp::T_ESEQ:
		{
		//	TRACE("Push %d\n", e->const_int.int32);
			munch
		}
		break;
		*/

	case T_Exp::T_CONST:
		{
			TRACE("Push %d\n", e->const_int.int32Val);
		}
		break;

	case T_Exp::T_BINOP:
		{
			munchExp(e->binop.left);
			munchExp(e->binop.right);

			switch (e->binop.op)
			{
			case '+':
				{
					TRACE("Add\n");
				}
				break;

			case '-':
				{
					TRACE("Subtract\n");
				}
				break;

			case '*':
				{
					TRACE("Multiply\n");
				}
				break;

			case '/':
				{
					TRACE("Divide\n");
				}
				break;

			default:
				ASSERT(0);
			}
		}
		break;

	case T_Exp::T_VARIABLE:
		{
			ASSERT(0);
#if 0
			T_VariableExp* ve = static_cast<T_VariableExp*>(e);
		//	TRACE("Push '%s'\n", e->mem.mem->identifier);
			DebugTrace("GetVariable '" << ve->identifier << "'\n");
#endif
		}
		break;

	case T_Exp::T_MEM:
		{
			ASSERT(0);
#if 0
			if (e->mem.mem->kind == T_Exp::T_MEMBER)
			{
				TRACE("GetMember\n");
			}
			else if (e->mem.mem->kind == T_Exp::T_VARIABLE)
			{
				TRACE("Push '%s'\n", e->mem.mem->identifier);
				TRACE("GetVariable\n");
			}
			else
				ASSERT(0);
#endif
		}
		break;

	default:
		ASSERT(0);
	}
}

CodeCompExt void munchStm(T_Stm* s)
{
	switch (s->kind)
	{
	case T_Stm::T_LABEL:
		{
			TRACE("%X\n", s->label);
		}
		break;

	case T_Stm::T_MOVE:
		{
			T_Exp* dst = s->move.left;
			T_Exp* src = s->move.right;

			if (dst->kind == T_Exp::T_MEM)
			{
				if (dst->mem.mem->kind == T_Exp::T_VARIABLE)
				{
					ASSERT(0);
#if 0
					TRACE("Push '%s'\n", dst->mem.mem->identifier);
				//	TRACE("Push\n");
				//	TRACE("Push\n");
#endif
					munchExp(src);

					TRACE("SetVariable\n");
				}
				ASSERT(0);
#if 0
				else if (dst->mem.mem->kind == T_Exp::T_MEMBER)
				{
					munchExp(dst->mem.mem->member.left);

					TRACE("Push '%s'\n", dst->mem.mem->member.right);
				//	TRACE("Push\n");
				//	TRACE("Push\n");

					munchExp(src);

					TRACE("SetMember\n");
				}
				else if (dst->mem.mem->kind == T_Exp::T_TEMP)
				{
					munchExp(src);
				}
#endif
			}
			else if (dst->kind == T_Exp::T_TEMP)
			{
				// ??

				munchExp(src);
			}
			else
				ASSERT(0);
		}
		break;

	case T_Stm::T_CJUMP:
		{
			munchExp(s->cjump.left);
			munchExp(s->cjump.right);

			TRACE("jumpif %X, %X\n", s->cjump.t, s->cjump.f);
		}
		break;

	default:
		ASSERT(0);
	}
}

CodeCompExt void munch(T_StmList* stms)
{
	T_StmList* tail = stms;
	while (tail)
	{
		munchStm(tail->head);

		tail = tail->tail;
	}
}

}	// java
}
