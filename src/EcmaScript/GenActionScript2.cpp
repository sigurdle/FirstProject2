#include "stdafx.h"
#include "EcmaScript.h"
#include "CodeComp/ir.h"
#include "ActionScript2/ActionScript.h"
//#include "GenActionScript2.h"

namespace System
{
namespace ecma	// TODO ? ActionScript2
{

using namespace ActionScripting;

// munch

void push_string(StringIn str, vector<as_instr*>& instrs, ActionContext* as_context, map<String, uint16>& pool)
{
	map<String, uint16>::iterator it = pool.find(str);
	if (it == pool.end())
	{
		it = pool.insert(map<String, uint16>::value_type(str, (uint16)as_context->m_constantPool.size())).first;
		as_context->m_constantPool.push_back(ActionScripting::StkElt(str));
	}
	uint16 index = (*it).second;

	as_instr* p = new as_instr;
	p->data.push_back(0x96);	// push
	//if (ActionCode >= 0x80)
	{
		uint16 length = 1 + 2;
		p->data.push_back(length & 0xFF);
		p->data.push_back(length >> 8);
	}

	p->data.push_back(9);	// string
	p->data.push_back(index & 0xFF);
	p->data.push_back(index >> 8);
	instrs.push_back(p);
}

void push_int32(int32 value, vector<as_instr*>& instrs)
{
	as_instr* p = new as_instr;
	p->data.push_back(0x96);	// push
	//if (ActionCode >= 0x80)
	{
		uint16 length = 1 + 4;
		p->data.push_back(length & 0xFF);
		p->data.push_back(length >> 8);
	}

	p->data.push_back(7);	// int32
	p->data.push_back(value & 0xFF);
	p->data.push_back((value >> 8) & 0xFF);
	p->data.push_back((value >> 16) & 0xFF);
	p->data.push_back((value >> 24) & 0xFF);
	instrs.push_back(p);
}

void munchStm(T_Stm* s, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16> & pool);

void munchExp(T_Exp* e, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16> & pool)
{
	switch (e->kind)
	{
	case T_Exp::T_ESEQ:
		{
			munchStm(e->eseq.s, instrs, as_context, pool);
			munchExp(e->eseq.e, instrs, as_context, pool);
		}
		break;

	case T_Exp::T_NULL:
		{
			as_instr* p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}

			p->data.push_back(2);	// null

			instrs.push_back(p);
		}
		break;

	case T_Exp::T_CONST:
		{
			TRACE("Push %d\n", e->const_int.int32Val);

			push_int32(e->const_int.int32Val, instrs);
		}
		break;

	case T_Exp::T_CONST_DOUBLE:
		{
			TRACE("Push %f\n", e->const_double.float64);

			as_instr* p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1 + 8;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}

			p->data.push_back(6);	// float64
			p->data.push_back(e->const_double.intbits & 0xFF);
			p->data.push_back((e->const_double.intbits>>8) & 0xFF);
			p->data.push_back((e->const_double.intbits>>16) & 0xFF);
			p->data.push_back((e->const_double.intbits>>24) & 0xFF);
			p->data.push_back((e->const_double.intbits>>32) & 0xFF);
			p->data.push_back((e->const_double.intbits>>40) & 0xFF);
			p->data.push_back((e->const_double.intbits>>48) & 0xFF);
			p->data.push_back((e->const_double.intbits>>56) & 0xFF);

			instrs.push_back(p);
		}
		break;

	case T_Exp::T_STRING:
		{
			T_StringExp* te = static_cast<T_StringExp*>(e);

			push_string(te->m_string, instrs, as_context, pool);
		}
		break;

	case T_Exp::T_UNOP:
		{
			munchExp(e->unop.exp, instrs, as_context, pool);

			if (e->unop.op == 'type')
			{
				as_instr* p = new as_instr;
				p->data.push_back(0x44);	// ActionTypeof
				instrs.push_back(p);
			}
			else
				ASSERT(0);
		}
		break;

	case T_Exp::T_BINOP:
		{
			munchExp(e->binop.left, instrs, as_context, pool);
			munchExp(e->binop.right, instrs, as_context, pool);

			switch (e->binop.op)
			{
			case '<':
				{
					as_instr* p = new as_instr;
					p->data.push_back(0x48);	// ActionLess2
					instrs.push_back(p);
				}
				break;

			case '>':
				{
					as_instr* p = new as_instr;
					p->data.push_back(0x67);	// ActionGreater
					instrs.push_back(p);
				}
				break;

			case '+':
				{
					as_instr* p = new as_instr;
				//	p->data.push_back(0x0A);	// ActionAdd
					p->data.push_back(0x47);	// ActionAdd2
					instrs.push_back(p);

					p->data.push_back(0x21);	// ActionStringAdd
					instrs.push_back(p);

				}
				break;

			case '-':
				{
					as_instr* p = new as_instr;
					p->data.push_back(0x0B);	// ActionSubtract
					instrs.push_back(p);
				}
				break;

			case '*':
				{
					as_instr* p = new as_instr;
					p->data.push_back(0x0C);
					instrs.push_back(p);
				}
				break;

			case '/':
				{
					as_instr* p = new as_instr;
					p->data.push_back(0x0D);
					instrs.push_back(p);
				}
				break;

			case 's+':
				{
					as_instr* p = new as_instr;
					p->data.push_back(0x21);	// ActionStringAdd
					instrs.push_back(p);
				}
				break;

			default:
				ASSERT(0);
			}
		}
		break;

	case T_Exp::T_MEM:
		{
			if (e->mem.mem->kind == T_Exp::T_MEMBER)
			{
				T_MemberExp* member_exp = static_cast<T_MemberExp*>(e->mem.mem);

				TRACE("GetMember\n");

				munchExp(member_exp->m_left, instrs, as_context, pool);
				push_string(member_exp->m_right, instrs, as_context, pool);

				{
					as_instr* p = new as_instr;
					p->data.push_back(0x4E);	// GetMember
					instrs.push_back(p);
				}
			}
			else if (e->mem.mem->kind == T_Exp::T_VARIABLE)
			{
				T_VariableExp* varexp = static_cast<T_VariableExp*>(e->mem.mem);
			//	TRACE("Push '%s'\n", e->mem.mem->identifier);
			//	TRACE("GetVariable\n");
				as_instr* p;
				
				push_string(varexp->m_identifier, instrs, as_context, pool);

				{
					p = new as_instr;
					p->data.push_back(0x1C);	// GetVariable
					instrs.push_back(p);
				}
			}
			else
				ASSERT(0);
		}
		break;

	case T_Exp::T_CALL:
		{
		//	munchExp(e->call.left->mem.mem->var);

			as_instr* p;

			int numArgs = 0;
			ArgList* args = e->call.args;
			while (args)
			{
				munchExp(args->head, instrs, as_context, pool);

				numArgs++;
				args = args->tail;
			}

			push_int32(numArgs, instrs);

			if (e->call.f->mem.mem->kind == T_Exp::T_MEMBER)
			{
				T_MemberExp* member_exp = static_cast<T_MemberExp*>(e->call.f->mem.mem);

				// push object
				munchExp(member_exp->m_left, instrs, as_context, pool);

				// push method name
				push_string(member_exp->m_right, instrs, as_context, pool);

				p = new as_instr;
				p->data.push_back(0x52);	// ActionCallMethod
				instrs.push_back(p);
			}
			else
			{
				T_VariableExp* var_exp = static_cast<T_VariableExp*>(e->call.f->mem.mem);

				push_string(var_exp->m_identifier, instrs, as_context, pool);

				p = new as_instr;
				p->data.push_back(0x3D);	// ActionCallFunction
				instrs.push_back(p);
			}
		}
		break;

	case T_Exp::T_NEW:
		{
			as_instr* p;

			int numArgs = 0;
			ArgList* args = e->call.args;
			while (args)
			{
				munchExp(args->head, instrs, as_context, pool);

				numArgs++;
				args = args->tail;
			}

			push_int32(numArgs, instrs);

			if (e->call.f->mem.mem->kind != T_Exp::T_VARIABLE)
			{
				raise(Exception("syntax error : new identifier()"));
			}
			T_VariableExp* varexp = static_cast<T_VariableExp*>(e->call.f->mem.mem);

			push_string(varexp->m_identifier, instrs, as_context, pool);

			p = new as_instr;
			p->data.push_back(0x40);	// ActionNewObject
			instrs.push_back(p);

#if 0
			if (e->call.f->mem.mem->kind == T_Exp::T_MEMBER)
			{
				// push object
				munchExp(e->call.f->mem.mem->member.left, instrs, as_context);

				// push method name
				push_string(e->call.f->mem.mem->member.right, instrs, as_context);
				/*
				//
				StringA* str = e->call.f->mem.mem->member.right;
				map<StringA*, uint16, Ref_Less<StringA> >::iterator it = pool.find(str);
				if (it == pool.end())
				{
					it = pool.insert(map<StringA*, uint16, Ref_Less<StringA> >::value_type(str, as_context->m_constantPool.size())).first;
					as_context->m_constantPool.push_back(ActionScript::StkElt(*str));
				}

				uint16 name = (*it).second;

				//uint16 name = pool[e->call.f->mem.mem->member.right];
				p = new as_instr;
				p->data.push_back(0x96);	// push
				//if (ActionCode >= 0x80)
				{
					uint16 length = 1 + 2;
					p->data.push_back(length & 0xFF);
					p->data.push_back(length >> 8);
				}
				p->data.push_back(9);	// string
				p->data.push_back(name & 0xFF);
				p->data.push_back(name >> 8);
				instrs.push_back(p);
				*/

				p = new as_instr;
				p->data.push_back(0x52);	// ActionCallMethod
				instrs.push_back(p);
			}
			else
			{
				/*
				uint16 name = pool[e->call.f->mem.mem->string];
				p = new as_instr;
				p->data.push_back(0x96);	// push
				//if (ActionCode >= 0x80)
				{
					uint16 length = 1 + 2;
					p->data.push_back(length & 0xFF);
					p->data.push_back(length >> 8);
				}
				p->data.push_back(16);	// string
				p->data.push_back(name & 0xFF);
				p->data.push_back(name >> 8);
				instrs.push_back(p);
				*/
				push_string(e->call.f->mem.mem->string, instrs, as_context);

				p = new as_instr;
				p->data.push_back(0x3D);	// ActionCallFunction
				instrs.push_back(p);
			}
#endif
		}
		break;

	default:
		ASSERT(0);
	}
}

//ActionContext* as_context;

void munch(T_StmList* stms, vector<as_instr*>& instrs, ActionContext* as_context, map<String, uint16> & pool);

/*
template<class list_t> size_t Count(list_t* listp)
{
	size_t count = 0;

	while (listp)
	{
		count++;
		listp = listp->tail;
	}

	return count;
}
*/

void munchStm(T_Stm* s, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16>& pool)
{
	switch (s->kind)
	{
	case T_Stm::T_FUN:
		{
			as_instr* p;

			p = new as_instr;
			p->data.push_back(0x9B);	// DefineFunction
			//if (ActionCode >= 0x80)
			{
				p->data.push_back(0);
				p->data.push_back(0);
			}
			ULONG length = 0;

			CString cstr(s->fun.m_name);
			p->data.insert(p->data.end(), (ubyte*)cstr.c_str(), (ubyte*)cstr.c_str()+cstr.len()+1);

			/*
			{
				// TODO
				uint len = s->fun.m_name.GetLength();
				char data[256];
				s->fun.m_name.CopyBuffer(data, 0, len);
				p->data.insert(p->data.end(), (ubyte*)data, (ubyte*)data+len);
			}
			p->data.push_back(0);
			*/
			length += cstr.len()+1;//s->fun.m_name.GetLength() + 1;

			uint16 numParams = Count(s->fun.m_formals);
			p->data.push_back(numParams & 0xFF);
			p->data.push_back(numParams >> 8);
			length += 2;
			{
				A_IdentifierList* formals = s->fun.m_formals;
				while (formals)
				{
					CString cstr(formals->head);
					p->data.insert(p->data.end(), (ubyte*)cstr.c_str(), (ubyte*)cstr.c_str()+cstr.len()+1);

					length += cstr.len()+1;
					/*
				uint len = s->fun.m_name.GetLength();
				char data[256];
				s->fun.m_name.CopyBuffer(data, 0, len);
				p->data.insert(p->data.end(), (ubyte*)data, (ubyte*)data+len);
				*/

					/*
					for (int i = 0; i < formals->head.GetLength(); i++)
					{
						ASSERT(0);
						//p->data.push_back(formals->head.begin<char>()[i]);
					}
					*/
					//p->data.push_back(0);

					formals = formals->tail;
				}
			}

			vector<as_instr*> body;

			munch(s->fun.m_body, body, as_context, pool);

			uint codelength = 0;
			{
				for (size_t i = 0; i < body.size(); ++i)
				{
					codelength += (uint) body[i]->data.size();
				}
			}
			length += codelength;

			p->data.push_back(codelength & 0xFF);
			p->data.push_back(codelength >> 8);
			length += 2;

			if (length >= 65536)
			{
				raise(Exception("ActionScript: length >= 65536"));
			}

			{
				for (int i = 0; i < body.size(); i++)
				{
					for (int j = 0; j < body[i]->data.size(); j++)
						p->data.push_back(body[i]->data[j]);
				}
			}

			p->data[1] = length & 0xFF;
			p->data[2] = length>>8;

			instrs.push_back(p);
		}
		break;

	case T_Stm::T_VAR:
		{
			as_instr* p;

			p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1 + 2;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}
			p->data.push_back(9/*16*/);	// constant
			p->data.push_back(s->var.name & 0xFF);
			p->data.push_back(s->var.name >> 8);
			instrs.push_back(p);

			p = new as_instr;
			p->data.push_back(0x41);	// DefineLocal2
			instrs.push_back(p);
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
					T_VariableExp* varexp = static_cast<T_VariableExp*>(dst->mem.mem);

					as_instr* p;
					push_string(varexp->m_identifier, instrs, as_context, pool);

					munchExp(src, instrs, as_context, pool);

					p = new as_instr;
					p->data.push_back(0x1D);	// SetVariable
					instrs.push_back(p);

					DebugTrace("SetVariable\n");
				}
				else if (dst->mem.mem->kind == T_Exp::T_MEMBER)
				{
					T_MemberExp* member_exp = static_cast<T_MemberExp*>(dst->mem.mem);

					as_instr* p;

					// object
					munchExp(member_exp->m_left, instrs, as_context, pool);

					// property name
					push_string(member_exp->m_right, instrs, as_context, pool);

					// value
					munchExp(src, instrs, as_context, pool);

					p = new as_instr;
					p->data.push_back(0x4F);	// SetMember
					instrs.push_back(p);

					TRACE("SetMember\n");
				}
				else
					ASSERT(0);
			}
			else
				ASSERT(0);
		}
		break;

	case T_Stm::T_EXP:
		{
			munchExp(s->exp, instrs, as_context, pool);
		}
		break;

	default:
		ASSERT(0);
	}
}

void munch(T_StmList* stms, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16>& pool)
{
	T_StmList* tail = stms;
	while (tail)
	{
		munchStm(tail->head, instrs, as_context, pool);

		tail = tail->tail;
	}
}

}
}
