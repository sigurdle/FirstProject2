#include "stdafx.h"
#include "codegen_m68k.h"
#include "m68kassem.h"

namespace System
{
using namespace std;

void fput8(FILE* fp, uint8 v);
void fput16(FILE* fp, uint16 v);
void fput32(FILE* fp, uint32 v);

extern Temp_temp* d0;
extern Temp_temp* d1;
extern Temp_temp* d2;
extern Temp_temp* d3;

extern Temp_temp* a0;
extern Temp_temp* a1;
extern Temp_temp* a2;
extern Temp_temp* a3;
extern Temp_temp* a4;
extern Temp_temp* a5;
extern Temp_temp* a6;
extern Temp_temp* a7;

//namespace cpp
//{

void CCodeGen68k::link(int areg, long displacement)
{
	if (displacement >= -32768 && displacement <= 32767)
	{
		fput16(fileout, 0x4E50 | areg);
		fput16(fileout, displacement);
	}
	else
	{
		ASSERT(0);
	}
}

void CCodeGen68k::unlk(int areg)
{
	fput16(fileout, 0x4E58 | areg);
}

void CCodeGen68k::jsr(uint8 mode, uint8 reg)
{
	uint16 word = 0x4E80;
	word |= (mode<<3);
	word |= reg;

	fput16(fileout, word);
}

void CCodeGen68k::rts()
{
	fput16(fileout, 0x4E75);
}

void CCodeGen68k::move(int size, int src_mode, int src_reg, int dst_mode, int dst_reg)
{
	uint16 word = size<<12;

	ASSERT(src_reg >= 0 && src_reg < 8);
	ASSERT(dst_reg >= 0 && dst_reg < 8);

	word |= dst_reg<<9;
	word |= dst_mode<<6;
	word |= src_mode<<3;
	word |= src_reg<<0;

	fput16(fileout, word);
}

void CCodeGen68k::movem(int dir, int size, int mode, int reg)
{
	uint16 word = 0x4880;//size<<12;
	word |= dir<<10;
	word |= size<<6;

	word |= mode<<3;
	word |= reg<<0;

	fput16(fileout, word);
}

void CCodeGen68k::lea(int an, int mode, int reg)
{
	uint16 word = 0x41C0;
	word |= reg;
	word |= mode<<3;
	word |= an<<9;

	fput16(fileout, word);
}

void CCodeGen68k::cmp(int reg, int cmpop, int eamode, int eareg)
{
	uint16 word = 0xB000;
	word |= eareg;
	word |= eamode<<3;
	word |= cmpop<<6;
	word |= reg<<9;

	fput16(fileout, word);
}

void CCodeGen68k::cmpi(long data, int size, int eamode, int eareg)
{
	uint16 word = 0x0C00;
	word |= eareg;
	word |= eamode<<3;
	word |= size<<6;

	fput16(fileout, word);

	if (size == 2)	// long
	{
		fput32(fileout, data);
	}
	else	// byte / word
	{
		fput16(fileout, data);
	}
}

void CCodeGen68k::bcc(int cond)
{
	uint16 word = 0x6000;
	word |= cond<<8;
	word |= 0;	// Always use 16-bit displacement

	fput16(fileout, word);
}

void CCodeGen68k::addi(int data, int size, int eamode, int eareg)
{
	uint16 word = 0x600;

	word |= size<<6;
	word |= eamode<<3;
	word |= eareg;

	fput16(fileout, word);

	if (size == 2)	// long
	{
		fput32(fileout, data);
	}
	else	// word/byte
	{
		fput16(fileout, data);
	}
}

void CCodeGen68k::add(int opmode, int dn, int eamode, int eareg)
{
	uint16 word = 0xD000;

	word |= dn<<9;
	word |= opmode<<6;
	word |= eamode<<3;
	word |= eareg;

	fput16(fileout, word);
}

void CCodeGen68k::adda(int opmode, int an, int eamode, int eareg)
{
	uint16 word = 0xD000;

	word |= an<<9;
	word |= opmode<<6;
	word |= eamode<<3;
	word |= eareg;

	fput16(fileout, word);
}

void CCodeGen68k::sub(int opmode, int dn, int eamode, int eareg)
{
	uint16 word = 0x9000;

	word |= dn<<9;
	word |= opmode<<6;
	word |= eamode<<3;
	word |= eareg;

	fput16(fileout, word);
}

// 16 x 16 -> 32
void CCodeGen68k::muls(int dn, int eamode, int eareg)
{
	uint16 word = 0xC1C0;

	word |= dn<<9;
//	word |= opmode<<6;
	word |= eamode<<3;
	word |= eareg;

	fput16(fileout, word);
}

void CCodeGen68k::divu(int dn, int eamode, int eareg)
{
	uint16 word = 0x80C0;

	word |= dn<<9;
//	word |= opmode<<6;
	word |= eamode<<3;
	word |= eareg;

	fput16(fileout, word);
}

#define SHIFT_RIGHT 0
#define SHIFT_LEFT 1

void CCodeGen68k::logic_shift(int dr, int size, int ir, int cr, int reg)
{
	uint16 word = 0xE008;

//	int ir = 0;
//	int size = 2;	// long
//	int dr = 0;	// right
	word |= reg;
	word |= ir<<5;	// 0=immediate, 1=register
	word |= size<<6;
	word |= dr<<8;
	word |= cr<<9;
	fput16(fileout, word);
}

void CCodeGen68k::clr(int size, int eamode, int eareg)
{
	uint16 word = 0x4200;

	word |= size<<6;
	word |= eamode<<3;
	word |= eareg;

	fput16(fileout, word);
}

void CCodeGen68k::moveq(char data, int dn)
{
	uint16 word = 0x7000;
	word |= dn<<9;
	word |= (uint8)data;
	fput16(fileout, word);
}

void CCodeGen68k::addq(int data, int size, int eamode, int eareg)
{
	ASSERT(data >= 1 && data <= 8);
	if (data == 8)
		data = 0;

	uint16 word = 0x5000;
	word |= eareg;
	word |= eamode<<3;
	word |= size<<6;
	word |= data<<9;

	fput16(fileout, word);
}

void CCodeGen68k::subq(int data, int size, int eamode, int eareg)
{
	ASSERT(data >= 1 && data <= 8);
	if (data == 8)
		data = 0;

	uint16 word = 0x5100;
	word |= eareg;
	word |= eamode<<3;
	word |= size<<6;
	word |= data<<9;

	fput16(fileout, word);
}

void CCodeGen68k::ext(int dn, int opmode)
{
	uint16 word = 0x4800;
	word |= dn;
	word |= opmode<<6;

	fput16(fileout, word);
}

void CCodeGen68k::jmp(int eamode, int eareg)
{
	uint16 word = 0x4EC0;
	word |= eareg;
	word |= eamode<<3;

	fput16(fileout, word);
}

void CCodeGen68k::Function_Prologue(CFunctionCode* pFun)
{
//	Temp_temp* a5 = new Temp_temp;
//	link(areg_5, -(pFun->m_pBody->m_pScope->m_stackSize));

	pFun->emit(AS_Oper(m68k_LINK(m68k_DATAREG(&a5), -32), NULL, NULL));
#if 0
//	link(areg_5, -0/*(pFun->m_pBody->m_pScope->m_stackSize)*/);
	
	AllocAddrRegister(a5, 15);
#endif

#if 0
	if (pFun->m_pBody->m_pScope->m_pParentScope->m_pParentScope)	// TODO, better way to determine
	{
		move(SIZE_L, 5,5, 1,0);	// 8(a5),a0
		fput16(fileout, 8);
	}
#endif

//	movem(0, 1/*long*/, 4,7);	// register to memory
//	fput16(fileout, 0xfffe);	// except a7
//	fput16(fileout, 0x7ffe);	// except d0/a7
//	fput16(fileout, 0);
}

void CCodeGen68k::Function_Epilogue(CFunctionCode* pFun)
{
//	movem(1, 1/*long*/, 3,7);	// memory to register
//	fput16(fileout, 0x7fff);	// except a7
//	fput16(fileout, 0x7ffe);	// except d0/a7
//	fput16(fileout, 0);
//	FreeRegister(15);
//	unlk(areg_5);
//	rts();
	pFun->emit(AS_Oper(m68k_UNLK(m68k_DATAREG(&a5)), NULL, new Temp_tempList(&a5, NULL)));
	pFun->emit(AS_Oper(m68k_RTS(), NULL, NULL));
}

void CCodeGen68k::de(Temp_temp* temp)
{
//	temp->m_refcount--;

//	if (m_refcount == 0)
	{
		if (temp->m_dn != -1)
		{
			if (m_regsinuse[temp->m_dn] == temp)
				FreeRegister(temp->m_dn);
		}

		if (temp->m_an != -1)
		{
			if (m_regsinuse[temp->m_an] == temp)
				FreeRegister(temp->m_an);
		}
	}
}

Temp_temp** CCodeGen68k::munchExpression(CFunctionCode* pFun, T_Exp* e)
{
	switch (e->kind)
	{
	case T_Exp::T_MEM:
	{
		Temp_temp** r = new Temp_temp*;
		*r = new Temp_temp;

		e->m_result = r;
		(*r)->m_size = e->mem.size;

		/*
		r->m_dn = AllocDataRegister(r);

		Temp_temp* t = new Temp_temp;
		t->m_an = AllocAddrRegister(t);
		*/

		/*if (true &&
			e->mem.mem->kind == T_Exp::T_MEM &&
			e->mem.mem->mem.mem->kind == T_Exp::T_BINOP &&
			e->mem.mem->mem.mem->binop.op == '+' &&
			e->mem.mem->mem.mem->binop.right->kind == T_Exp::T_CONST)
		{
			ASSERT(0);
		}
		else*/ if (e->mem.mem->kind == T_Exp::T_BINOP &&
			e->mem.mem->binop.op == '+' &&
			e->mem.mem->binop.right->kind == T_Exp::T_CONST)
		{
			Temp_temp** r1 = munchExpression(pFun, e->mem.mem->binop.left);

			if (!(*r1)->m_precolored)
			{
				(*r1)->m_an++;
			}

			if (e->mem.size <= 4)
			{
				pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e->mem.mem->binop.right->const_int.int32Val), m68k_DATAREG(r), e->mem.size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
			}
			else
			{
				(*r)->m_second = new Temp_temp*;

				(*r)->m_size = 4;
				(*(*r)->m_second)->m_size = 4;

			//	r->m_size = 8;

				pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e->mem.mem->binop.right->const_int.int32Val+4), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e->mem.mem->binop.right->const_int.int32Val), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList(r1, NULL)));
			}
		}
		else if (e->mem.mem->kind == T_Exp::T_CONST)
		{
			pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT(m68k_IMM(e->mem.mem->const_int.int32Val)), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), NULL));
		}
		else
		{
			Temp_temp** r1 = munchExpression(pFun, e->mem.mem);
			if (!(*r1)->m_precolored)
			{
				(*r1)->m_an++;	// address register
		//	move(SIZE_L, 0,r1->m_dn, 1,t->m_an-8);
			}

			pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT(r1), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
		}

		/*
		if (e->mem_size == 1)
		{
			move(SIZE_B, 2,t->m_an-8, 0,r->m_dn);
			ext(r->m_dn, 2);	// TODO, not here
			ext(r->m_dn, 3);	// TODO, not here
		}
		else if (e->mem_size == 2)
		{
			move(SIZE_W, 2,t->m_an-8, 0,r->m_dn);
			ext(r->m_dn, 3);	// TODO, not here
		else
		}
		*/
		/*
		if (e->mem.size == 4)
		{
			//move(SIZE_L, 2,t->m_an-8, 0,r->m_dn);
		}
		else
			ASSERT(0);
			*/

	//	de(r1);
	//	de(t);

		return r;
	}
	break;
#if 0
	/*
	else if (e->kind == cpp::T_Exp::T_ADDR)
	{
	}
	*/
#endif
	case T_Exp::T_TEMP:
	{
		e->m_result = e->temp;

		return e->temp;
	}
	break;
	/*
	else if (e->kind == cpp::T_Exp::T_CONST)
	{
	//	printf("temp");
		Temp_temp* r = new Temp_temp;
		emit(SD_Oper("MOVE", NULL, new Temp_tempList(e
		return r;
	}
	*/
	case T_Exp::T_UNOP:
	{
		switch (e->unop.op)
		{
		case '-':
			{
				Temp_temp** r = new Temp_temp*;
				*r = new Temp_temp;

				e->m_result = r;

				Temp_temp** r2 = munchExpression(pFun, e->unop.exp);

				if ((*r2)->m_second)
				{
					(*r)->m_second = new Temp_temp*;
					*(*r)->m_second = new Temp_temp;

					(*r)->m_dn++;
					(*(*r)->m_second)->m_dn++;

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r2)->m_second, NULL)));

					pFun->emit(AS_Oper(m68k_NEG(m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
					pFun->emit(AS_Oper(m68k_NEGX(m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r)->m_second, NULL)));
				}
				else
				{
					ASSERT(0);
				}

				return r;
			}
			break;

		case 'se':
			{
				Temp_temp** r = new Temp_temp*;
				e->m_result = r;
				(*r)->m_size = e->m_size;

				Temp_temp** r2 = munchExpression(pFun, e->unop.exp);

				if (e->m_size == 8)
				{
					(*r)->m_second = new Temp_temp*;
					(*r)->m_size = 4;
					(*(*r)->m_second)->m_size = 4;

					if ((*r2)->m_size == 4)	// int32->int64
					{
						if (!(*r)->m_precolored)
						{
							(*r)->m_dn++;
						}

						if (!(*(*r)->m_second)->m_precolored)
						{
							(*(*r)->m_second)->m_dn++;
						}

						pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
						pFun->emit(AS_Oper(m68k_TST(m68k_DATAREG(r)), NULL, new Temp_tempList(r, NULL)));
						pFun->emit(AS_Oper(m68k_SET(11/*mi*/, m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList(r, NULL)));
						pFun->emit(AS_Oper(m68k_EXT((*r)->m_second, 7), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r)->m_second, NULL)));
					}
					else
						ASSERT(0);
				}
				else if (e->m_size == 4)
				{
					if ((*r2)->m_size == 2)	// word->long
					{
						if (!(*r)->m_precolored)
						{
							(*r)->m_an++;
						}

						// movea.w r2,an
						// sign extends

						pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 2), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
					//	pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
					}
					else if ((*r2)->m_size == 1)	// byte->long
					{
						//r->m_dn = r2->m_dn;
						//r->m_an = r2->m_an;
						if (!(*r)->m_precolored)
						{
							(*r)->m_dn++;
						}

						pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), (*r2)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
						pFun->emit(AS_Oper(m68k_EXT(r, 7), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
					}
					else
						ASSERT(0);
				}
				else if (e->m_size == 2)
				{
					ASSERT(0);	// TODO
				}
				else
					ASSERT(0);

				return r;
			}
			break;

		case 'trun':
			{
				if (e->unop.exp->kind == T_Exp::T_BINOP &&
					e->unop.exp->binop.op == 'sdiv' &&

					e->unop.exp->binop.left->m_size == 8/*T_Exp::T_TEMP &&
					e->unop.exp->binop.left->temp->m_second != NULL*/ &&	// 64bit

					e->unop.exp->binop.right->kind == T_Exp::T_UNOP &&
					e->unop.exp->binop.right->unop.op == 'se')	// 32bit originally
				{
					Temp_temp** q = new Temp_temp*;
					*q = new Temp_temp;

					e->m_result = q;

					// cpu 68020
					// 64/32 -> 32r:32q

				//	Temp_temp* left = e->unop.exp->binop.left->temp;
					Temp_temp** left = munchExpression(pFun, e->unop.exp->binop.left);

					Temp_temp** r = new Temp_temp*;
					*r = new Temp_temp;

					(*q)->m_aux = r;

					(*q)->m_dn++;
					(*r)->m_dn++;

					// dst/src -> dst

					Temp_temp** r2 = munchExpression(pFun, e->unop.exp->binop.right->unop.exp);

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(left), m68k_DATAREG(q), 4), new Temp_tempList(q, NULL), new Temp_tempList(left, NULL)));
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*left)->m_second), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList((*left)->m_second, NULL)));
					pFun->emit(AS_Oper(m68k_DIVS(m68k_DATAREG(r2), q, r), new Temp_tempList(q, new Temp_tempList(r, NULL)), new Temp_tempList(q, new Temp_tempList(r, new Temp_tempList(r2, NULL)))));

					return q;	// return quotient
				}
				else
				{
					Temp_temp** r = new Temp_temp*;
					*r = new Temp_temp;

					e->m_result = r;
					(*r)->m_size = 4;

					Temp_temp** r2 = munchExpression(pFun, e->unop.exp);
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), (*r2)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));

					return r;
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
	break;

	case T_Exp::T_BINOP:
	{
		Temp_temp** r = new Temp_temp*;
		*r = new Temp_temp;

		e->m_result = r;

		if (e->binop.op == '+')
		{
			if (e->binop.left->kind == T_Exp::T_TEMP && e->binop.right->kind == T_Exp::T_CONST &&
					(__int64)e->binop.right->const_int.int32Val >= -32768 &&
					(__int64)e->binop.right->const_int.int32Val <= 32767)
			{
				Temp_temp** r1 = munchExpression(pFun, e->binop.left);
				if (!(*r1)->m_precolored)
				{
					(*r1)->m_an++;
				}

				(*r)->m_an++;

				//	Temp_temp* r2 = munchExpression(pFun, src->binop.left);
				pFun->emit(AS_Oper(m68k_LEA(m68k_INDIRECT_DISPLACEMENT(r1, e->binop.right->const_int.int32Val), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
			}
			else if (e->binop.right->kind == T_Exp::T_CONST)
			{
				Temp_temp** r1 = munchExpression(pFun, e->binop.left);

				(*r)->m_dn = (*r1)->m_dn;// + (*r2)->m_dn;
				(*r)->m_an = (*r1)->m_an;// + (*r2)->m_an;

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), (*r1)->m_size), new Temp_tempList(r, NULL), /*e->m_src[1] =*/ new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Oper(m68k_ADD(m68k_IMM(e->binop.right->const_int.int32Val), m68k_DATAREG(r)), /*e->m_dst =*/ new Temp_tempList(r, NULL), NULL));
			}
			else
			{
				Temp_temp** r1 = munchExpression(pFun, e->binop.left);
				Temp_temp** r2 = munchExpression(pFun, e->binop.right);

				if ((*r1)->m_second)
				{
					ASSERT((*r2)->m_second);

					*(*r)->m_second = new Temp_temp;

					(*r)->m_dn++;
					(*(*r)->m_second)->m_dn++;

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r2)->m_second, NULL)));

					pFun->emit(AS_Oper(m68k_ADD(m68k_DATAREG(r1), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(m68k_ADDX(m68k_DATAREG((*r1)->m_second), m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r1)->m_second, NULL)));
				}
				else
				{
					(*r)->m_dn = (*r1)->m_dn + (*r2)->m_dn;
					(*r)->m_an = (*r1)->m_an + (*r2)->m_an;

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), (*r1)->m_size), new Temp_tempList(r, NULL), /*e->m_src[1] =*/ new Temp_tempList(r2, NULL)));
					pFun->emit(AS_Oper(m68k_ADD(m68k_DATAREG(r1), m68k_DATAREG(r)), /*e->m_dst =*/ new Temp_tempList(r, NULL), /*e->m_src[0] =*/ new Temp_tempList(r1, NULL)));//new Temp_tempList(r, NULL))));
				}
			}
		}
		else if (e->binop.op == '-')
		{
			if (e->binop.right->kind == T_Exp::T_CONST)
			{
				Temp_temp** r1 = munchExpression(pFun, e->binop.left);

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), (*r1)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				if (e->binop.right->const_int.int32Val >= 1 && e->binop.right->const_int.int32Val <= 8)
				{
					pFun->emit(AS_Oper(m68k_SUBQ(e->binop.right->const_int.int32Val, m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
				}
				else
				{
					(*r)->m_dn++;

					// dst = dst - src
					// r = r2 - r
					pFun->emit(AS_Oper(m68k_SUBI(e->binop.right->const_int.int32Val, m68k_DATAREG(r), (*r1)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
				}
			}
			else if (e->binop.left->kind == T_Exp::T_CONST)
			{
				ASSERT(0);
			}
			else
			{
				Temp_temp** r1 = munchExpression(pFun, e->binop.left);
				Temp_temp** r2 = munchExpression(pFun, e->binop.right);

				if ((*r1)->m_second)
				{
					ASSERT((*r2)->m_second);

					(*r)->m_second = new Temp_temp*;

					(*r)->m_dn++;
					(*(*r)->m_second)->m_dn++;

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r1)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r1)->m_second, NULL)));

					pFun->emit(AS_Oper(m68k_SUB(m68k_DATAREG(r2), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
					pFun->emit(AS_Oper(m68k_SUBX(m68k_DATAREG((*r2)->m_second), m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r2)->m_second, NULL)));
				}
				else
				{
					(*r)->m_dn = (*r1)->m_dn + (*r2)->m_dn;
					(*r)->m_an = (*r1)->m_an + (*r2)->m_an;

					// r = r1 - r2

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), (*r1)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					// dst = dst - src
					// r = r2 - r
					pFun->emit(AS_Oper(m68k_SUB(m68k_DATAREG(r2), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				}
			}
		}
		else if (e->binop.op == '/')
		{
			/*
			if (e->binop.left->kind == T_Exp::T_UNOP && e->binop.left->unop.op == 'se' && e->binop.left->unop.size == 8 &&
				e->binop.right->kind == T_Exp::T_UNOP && e->binop.right->unop.op == 'se' && e->binop.right->unop.size == 8)
			{
			}
			else
			*/
			{
				Temp_temp** r1 = munchExpression(pFun, e->binop.left);
				Temp_temp** r2 = munchExpression(pFun, e->binop.right);

				// TODO
				(*r)->m_size = 4;
				(*r)->m_second = new Temp_temp*;
				(*(*r)->m_second)->m_size = 4;

				(*r1)->m_dn++;
				(*r2)->m_dn++;

				(*r)->m_dn = (*r1)->m_dn + (*r2)->m_dn;
				(*r)->m_an = (*r1)->m_an + (*r2)->m_an;

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r1)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r1)->m_second, NULL)));
				ASSERT(0);
				//pFun->emit(AS_Oper(m68k_DIVS(m68k_DATAREG(r2), r, r->m_second), new Temp_tempList(r, new Temp_tempList(r->m_second, NULL)), new Temp_tempList(r2, NULL)));
			}
		}
		else if (e->binop.op == '*')
		{
			if (e->binop.left->kind == T_Exp::T_UNOP && e->binop.left->unop.op == 'se' && e->binop.left->m_size == 8 &&
				e->binop.right->kind == T_Exp::T_UNOP && e->binop.right->unop.op == 'se' && e->binop.right->m_size == 8)
			{
				Temp_temp** r1 = munchExpression(pFun, e->binop.left->unop.exp);
				Temp_temp** r2 = munchExpression(pFun, e->binop.right->unop.exp);

				(*r)->m_size = 4;
				(*r)->m_second = new Temp_temp*;

				(*r1)->m_dn++;
				(*r2)->m_dn++;

				(*r)->m_dn = (*r1)->m_dn + (*r2)->m_dn;
				(*r)->m_an = (*r1)->m_an + (*r2)->m_an;

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				pFun->emit(AS_Oper(m68k_MULS(m68k_DATAREG(r1), r, (*r)->m_second), new Temp_tempList(r, new Temp_tempList((*r)->m_second, NULL)), new Temp_tempList(r, new Temp_tempList(r1, NULL))));
			}
			else
			{
				Temp_temp** r1 = munchExpression(pFun, e->binop.left);
				Temp_temp** r2 = munchExpression(pFun, e->binop.right);

				(*r)->m_dn++;
				(*r1)->m_dn++;
				(*r2)->m_dn++;

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				pFun->emit(AS_Oper(m68k_MULS(m68k_DATAREG(r1), r, NULL), new Temp_tempList(r, NULL), new Temp_tempList(r, new Temp_tempList(r1, NULL))));
			}

#if 0
			r->m_dn = AllocDataRegister(r);

			if (e->binop.left->kind == T_Exp::T_CONST)
			{
				Temp_temp* r2 = munchExpression(pFun, e->binop.right);

				if (r2->m_dn != -1)
					move(SIZE_L, 0, r2->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r2->m_an-8, 0, r->m_dn);

				muls(r->m_dn, 7, 4);
				fput16(fileout, e->binop.left->const_int.int32Val);

				de(r2);
			}
			else if (e->binop.right->kind == T_Exp::T_CONST)
			{
				Temp_temp* r1 = munchExpression(pFun, e->binop.left);

				if (r1->m_dn != -1)
					move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

				muls(r->m_dn, 7, 4);
				fput16(fileout, e->binop.right->const_int.int32Val);

				de(r1);
			}
#endif
			{
		//		ASSERT(0);
			//	Temp_temp* r1 = munchExpression(pFun, e->binop.left);
			//	Temp_temp* r2 = munchExpression(pFun, e->binop.right);

			//	pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
			//	emit(AS_Oper(m68k_MUL(), new Temp_tempList(r, NULL), new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

#if 0
				if (r1->m_dn != -1)
					move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

				muls(r->m_dn, 0, r2->m_dn);
			//	ext(r->m_dn, 3/*word -> long*/);

				de(r1);
				de(r2);
#endif
			}
		}
		else if (e->binop.op == '<<')
		{
			Temp_temp** r1 = munchExpression(pFun, e->binop.left);
			Temp_temp** r2 = munchExpression(pFun, e->binop.right);

			pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
			pFun->emit(AS_Oper(m68k_LSHIFT(1, m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
		}
		else if (e->binop.op == 'sar')
		{
			Temp_temp** r1 = munchExpression(pFun, e->binop.left);
			Temp_temp** r2 = munchExpression(pFun, e->binop.right);

			if ((*r1)->m_second)
			{
				//Temp_label* label = new Temp_label;

				(*r)->m_second = new Temp_temp*;

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r1)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r1)->m_second, NULL)));

				//pFun->emit(AS_Label(label));
				pFun->emit(AS_Oper(m68k_ANDI(63, m68k_DATAREG(r2), 4), new Temp_tempList(r2, NULL), new Temp_tempList(r2, NULL)));
				pFun->emit(AS_Oper(m68k_SUBQ(1, m68k_DATAREG(r2)), new Temp_tempList(r2, NULL), new Temp_tempList(r2, NULL)));
			//	pFun->emit(AS_Oper(m68k_Bcc(11/*minus*/, NULL), NULL, NULL));
				pFun->emit(AS_Oper(m68k_ASR(m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r)->m_second, NULL)));
				pFun->emit(AS_Oper(m68k_ROXR(m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
				pFun->emit(AS_Oper(NULL/*m68k_DBcc(1, r2, NULL)*/, new Temp_tempList(r2, NULL), new Temp_tempList(r2, NULL)));
			}
			else
				ASSERT(0);

		}
#if 0
		else if (e->binop.op == '/')
		{
			r->m_dn = AllocDataRegister(r);

			Temp_temp* r1 = munchExpression(pFun, e->binop.left);
			Temp_temp* r2 = munchExpression(pFun, e->binop.right);

			emit(AS_Oper("DIVU", new Temp_tempList(r, NULL), new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

			if (r1->m_dn != -1)
				move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
			else
				move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

			divu(r->m_dn, 0, r2->m_dn);
			ext(r->m_dn, 3/*word -> long*/);

			de(r1);
			de(r2);
		}
		else if (e->binop.op == '%')
		{
			r->m_dn = AllocDataRegister(r);

			Temp_temp* r1 = munchExpression(pFun, e->binop.left);
			Temp_temp* r2 = munchExpression(pFun, e->binop.right);

			emit(AS_Oper("SUB", new Temp_tempList(r, NULL), new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

			if (r1->m_dn != -1)
				move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
			else
				move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

			divu(r->m_dn, 0, r2->m_dn);

			// shift right
			{
				uint16 word = 0xE008;

				int ir = 0;
				int size = 2;	// long
				int dr = 0;	// right
				word |= r->m_dn;
				word |= ir<<5;
				word |= size<<6;
				word |= dr<<8;
				word |= 0<<9;	// 8
				fput16(fileout, word);

				fput16(fileout, word);	// Do it twice
			}

			de(r1);
			de(r2);
		}
		else if (e->binop.op == '<<' || e->binop.op == '>>')
		{
			r->m_dn = AllocDataRegister(r);

			int dr = (e->binop.op=='<<')? SHIFT_LEFT: SHIFT_RIGHT;

			if (e->binop.left->kind == T_Exp::T_CONST)
			{
				Temp_temp* r2 = munchExpression(pFun, e->binop.right);

				move(SIZE_L, 7,4, 0,r->m_dn);
				fput32(fileout, e->binop.left->const_int.int32Val);

				logic_shift(dr, 2/*long*/, 1/*reg*/,r2->m_dn, r->m_dn);

				de(r2);
			}
			else if (e->binop.right->kind == T_Exp::T_CONST)
			{
				ASSERT(0);	// TODO
			}
			else
			{
				ASSERT(0);
#if 0
				r->m_dn = AllocDataRegister(r);

				Temp_temp* r1 = munchExpression(pFun, e->binop.left);
				Temp_temp* r2 = munchExpression(pFun, e->binop.right);

				emit(AS_Oper("SUB", new Temp_tempList(r, NULL), new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

				if (r1->m_dn != -1)
					move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

				//divu(r->m_dn, 0, r2->m_dn);

				logic_shift(dr, 2/*long*/, 1/*reg*/,r->m_dn);

				de(r1);
				de(r2);
#endif
			}
		}
#endif
		else
			ASSERT(0);

		return r;
	}
	break;

	case T_Exp::T_CONST:
	{
		Temp_temp** r = new Temp_temp*;
		*r = new Temp_temp;
	//	r->m_size = e->m_size;
		e->m_result = r;

		if (e->m_size <= 4)
		{
			if (e->const_int.int32Val == 0)
			{
				pFun->emit(AS_Oper(m68k_CLR(m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), NULL));
			}
			else if (e->const_int.int32Val >= -128 && e->const_int.int32Val < 127)
			{
				(*r)->m_dn++;
				pFun->emit(AS_Oper(m68k_MOVEQ(e->const_int.int32Val, r), new Temp_tempList(r, NULL), NULL));
			}
			else
			{
			//	r->m_dn = AllocDataRegister(r);
				pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(e->const_int.int32Val), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), NULL));
			}
		}
		else if (e->m_size == 8)
		{
			(*r)->m_second = new Temp_temp*;

			pFun->emit(AS_Oper(NULL, new Temp_tempList(r, NULL), NULL));
			pFun->emit(AS_Oper(NULL, new Temp_tempList((*r)->m_second, NULL), NULL));
		}
		else
			ASSERT(0);

		return r;

#if 0
	//	char assem[64];
	//	sprintf(assem, "MOVEI #%d", e->tok.int32);
	//	emit(AS_Oper(assem, new Temp_tempList(r, NULL), NULL));

		move(SIZE_L, 7,4, 0,r->m_dn);
		ASSERT(0);
#if 0
		if (e->const_int.reloc)
		{
			e->const_int.reloc->VirtualAddress = ftell(fileout);
			pFun->AddRelocation(e->const_int.reloc);
		}
#endif

		fput32(fileout, e->const_int.int32Val);
		//fwrite_const32(fileout, e->tok.int32);

		return r;
#endif
	}
	break;

	case T_Exp::T_CALL:
	{
		Temp_temp** r = new Temp_temp*;
		*r = new Temp_temp;
		//e->m_result = r;
		(*r)->m_size = 4;

		T_Exp* f;
		if (e->call.f->kind == T_Exp::T_MEM)
			f = e->call.f->mem.mem;
		else
			f = e->call.f;

		ArgList* pArgList;

		// evaluate those that go on stack since they don't occupy registers
		pArgList = e->call.args;
		while (pArgList)
		{
			T_Exp* e2 = pArgList->head;

			if (pArgList->reg == NULL)
			{
				if (e2->kind == T_Exp::T_NAME)
				{
					pFun->emit(AS_Oper(m68k_MOVE(m68k_NAME(e2->name.label), m68k_INDIRECT_PREDEC(&a7), 4), NULL, NULL));
				}
				else if (e2->kind == T_Exp::T_CONST)
				{
					pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(e2->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), 4), NULL, NULL));
				}
				else if (e2->kind == T_Exp::T_BINOP && e2->binop.op == '+' &&
							e2->binop.left->kind == T_Exp::T_TEMP && e2->binop.right->kind == T_Exp::T_CONST &&
							e2->binop.right->const_int.int32Val >= -32768 &&
							e2->binop.right->const_int.int32Val <= 32767)
				{
					Temp_temp** r1 = munchExpression(pFun, e2->binop.left);

					if (!(*r1)->m_precolored)
					{
						(*r1)->m_an++;
					}

					pFun->emit(AS_Oper(m68k_PEA(m68k_INDIRECT_DISPLACEMENT(r1, e2->binop.right->const_int.int32Val)), NULL, new Temp_tempList(r1, NULL)));
				}
				/*
				else if (e2->kind == T_Exp::T_MEM &&
							e2->mem.mem->kind == T_Exp::T_BINOP &&
							e2->mem.mem->binop.left->kind == T_Exp::T_MEM &&
							e2->mem.mem->binop.op == '+')
				{
					ASSERT(0);
				}
				else
				*/
				else if (e2->kind == T_Exp::T_MEM &&
							e2->mem.mem->kind == T_Exp::T_BINOP &&
							e2->mem.mem->binop.op == '+' &&
							e2->mem.mem->binop.right->kind == T_Exp::T_CONST)
				{
					if (e2->mem.mem->binop.left->kind == T_Exp::T_MEM &&
						e2->mem.mem->binop.left->mem.mem->kind == T_Exp::T_TEMP)
					{
						// mem(binop('+', mem(r), const))

						ASSERT(0);//pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, NULL)));
					}
					else
					{
						Temp_temp** r1 = munchExpression(pFun, e2->mem.mem->binop.left);

						if (!(*r1)->m_precolored)
						{
							(*r1)->m_an++;
						}

						if (e2->mem.size <= 4)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, NULL)));
						}
						else
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val+4), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r1, NULL)));
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r1, NULL)));
						}
					}
				}
				else if (e2->kind == T_Exp::T_MEM &&
							e2->mem.mem->kind == T_Exp::T_BINOP &&
							e2->mem.mem->binop.op == '+')
				{
					Temp_temp** r1 = munchExpression(pFun, e2->mem.mem->binop.left);

					if (e2->mem.mem->binop.right->kind == T_Exp::T_BINOP &&
						e2->mem.mem->binop.right->binop.op == '<<' &&
						e2->mem.mem->binop.right->binop.right->kind == T_Exp::T_CONST &&
						(e2->mem.mem->binop.right->binop.right->const_int.int32Val == 0 ||
						e2->mem.mem->binop.right->binop.right->const_int.int32Val == 1 ||
						e2->mem.mem->binop.right->binop.right->const_int.int32Val == 2 ||
						e2->mem.mem->binop.right->binop.right->const_int.int32Val == 3))
					{
						int scalefactor = e2->mem.mem->binop.right->binop.right->const_int.int32Val;

						if (e2->mem.mem->binop.right->binop.left->kind == T_Exp::T_BINOP &&
							e2->mem.mem->binop.right->binop.left->binop.op == '-' &&
							e2->mem.mem->binop.right->binop.left->binop.right->kind == T_Exp::T_CONST &&
							((__int64)e2->mem.mem->binop.right->binop.left->binop.right->const_int.int32Val<<scalefactor) >= -128 &&
							((__int64)e2->mem.mem->binop.right->binop.left->binop.right->const_int.int32Val<<scalefactor) <= 127)
						{
							Temp_temp** r2 = munchExpression(pFun, e2->mem.mem->binop.right->binop.left->binop.left);

							if (!(*r1)->m_precolored)
							{
								(*r1)->m_an++;
							}

							if (!(*r2)->m_precolored)	// TODO, can also do an
							{
								(*r2)->m_dn++;
							}

							int8 disp8 = -(int)(e2->mem.mem->binop.right->binop.left->binop.right->const_int.int32Val << scalefactor);

							if (e2->mem.size <= 4)
							{
								pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_INDEX(disp8, r1, r2, scalefactor), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
							}
							else
								ASSERT(0);
						}
						else
						{
							Temp_temp** r2 = munchExpression(pFun, e2->mem.mem->binop.right->binop.left);

							if (!(*r1)->m_precolored)
							{
								(*r1)->m_an++;
							}

							if (!(*r2)->m_precolored)
							{
								(*r2)->m_dn++;
							}

							if (e2->mem.size <= 4)
							{
								pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_INDEX(0/*disp8*/, r1, r2, scalefactor), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
							}
							else
								ASSERT(0);
						}
					}
					else
					{
						Temp_temp** r2 = munchExpression(pFun, e2->mem.mem->binop.right);

						if (!(*r1)->m_precolored)
						{
							(*r1)->m_an++;
						}

						if (!(*r2)->m_precolored)
						{
							(*r2)->m_dn++;
						}

						if (e2->mem.size <= 4)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_INDEX(0/*disp8*/, r1, r2, 0/*scalefactor*/), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
						}
						/*
						else
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_INDEXACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val+4), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r1, NULL)));
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r1, NULL)));
						}
						*/
					}
				}
				else
				{
					Temp_temp** r2 = munchExpression(pFun, e2);

					pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT_PREDEC(&a7), 4), NULL, /*e->m_src[0] =*/ new Temp_tempList(r2, NULL)));

					if ((*r2)->m_second)
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList((*r2)->m_second, NULL)));
					}
				}
			}

			pArgList = pArgList->tail;
		}

		// evaluate those that go in registers
		vector<Temp_temp**> args;
		pArgList = e->call.args;
		while (pArgList)
		{
			if (pArgList->reg)
			{
				Temp_temp** r2 = munchExpression(pFun, pArgList->head);
				args.push_back(r2);
			}

			pArgList = pArgList->tail;
		}

		// put them in correct registers
		Temp_tempList* templist = NULL;
		int i = 0;
		pArgList = e->call.args;
		while (pArgList)
		{
			T_Exp* e = pArgList->head;

			if (pArgList->reg)
			{
				Temp_temp** r2 = args[i];

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(pArgList->reg), (*pArgList->reg)->m_size), new Temp_tempList(pArgList->reg, NULL), new Temp_tempList(r2, NULL)));

				templist = new Temp_tempList(pArgList->reg, templist);
				i++;
			}

			pArgList = pArgList->tail;
		}

		if (f->kind == T_Exp::T_BINOP &&
			f->binop.op == '+' &&
			f->binop.right->kind == T_Exp::T_CONST)
		{
			Temp_temp** r1 = munchExpression(pFun, f->binop.left);

			if (!(*r1)->m_precolored)
			{
				(*r1)->m_an++;
			}

			templist = new Temp_tempList(r1, templist);

			pFun->emit(AS_Oper(m68k_JSR(m68k_INDIRECT_DISPLACEMENT(r1, f->binop.right->const_int.int32Val)),
				new Temp_tempList(&d0, new Temp_tempList(&d1, new Temp_tempList(&a0, new Temp_tempList(&a1, NULL)))),
				templist));

			pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(&d0), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(&d0, NULL)));
		}
		else if (f->kind == T_Exp::T_NAME)
		{
			pFun->emit(AS_Oper(m68k_JSR(m68k_NAME(f->name.label)),
				NULL,//new Temp_tempList(&d0, new Temp_tempList(&d1, new Temp_tempList(&a0, new Temp_tempList(&a1, NULL)))),
				templist));

#if 0
			pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(&d0), m68k_DATAREG(r), (*r)->m_size), e->m_dst = new Temp_tempList(r, NULL), new Temp_tempList(&d0, NULL)));
#endif
		}
		else
			ASSERT(0);

		return r;

#if 0
		// push parameters in reverse order
		
		ExpList* pExprR = e->call.args;
		
		int stackSize = 0;

		Temp_tempList* templist = NULL;

		while (pExprR)
		{
		//	cpp::CExpression* pArgExpr = pExprR->expr;
			T_Exp* pTExpr = pExprR->head;

			{
			//	int destreg = -1;
				int destreg = pExprR->reg;

//				if (pArgExpr->m_pDeclaratorRef)
//					destreg = pArgExpr->m_pDeclaratorRef->m_pDeclarator->m_libcall.m_reg;
				
				if (destreg >= 0)	// place argument in a register
				{
					if (m_regsinuse[destreg])
					{
					}

					Temp_temp* t = new Temp_temp;
					if (destreg < 8)
						t->m_dn = AllocAnyRegister(t, destreg);
					else
						t->m_an = AllocAnyRegister(t, destreg);

					Temp_temp* r1 = munchExpression(pFun, pTExpr);

					if (destreg < 8)
					{
						move(SIZE_L, 0, r1->m_dn, 0,destreg);
					}
					else
					{
						move(SIZE_L, 0, r1->m_dn, 1,destreg-8);
					}

					de(r1);

					templist = new Temp_tempList(t, templist);
				}
				else if (destreg < -1)
				{
					destreg = -(destreg+1);

					Temp_temp* t = new Temp_temp;
					if (destreg < 8)
						t->m_dn = AllocAnyRegister(t, destreg);
					else
						t->m_an = AllocAnyRegister(t, destreg);

					move(SIZE_L, 1,15-8, 1,t->m_an-8);

					templist = new Temp_tempList(t, templist);
				}
				else	// push argument on stack
				{
					stackSize += 4;
				//	ea _destea(4,7);

					Temp_temp* r1 = munchExpression(pFun, pTExpr);
					//if (emit_expr(pFunc, pArgExpr, &_destea) != 1)
					//	printf("Error in expression\n");
					move(SIZE_L, 0, r1->m_dn, 4,7);		// -(a7)

					de(r1);
				}
			}

			pExprR = pExprR->tail;
		}

		Temp_temp* r = new Temp_temp;

		T_Exp* f;
		if (e->call.f->kind == T_Exp::T_MEM)
			f = e->call.f->mem;
		else
			f = e->call.f;

		if (f->kind == T_Exp::T_BINOP &&
			f->binop.op == '+' &&
			f->binop.right->kind == T_Exp::T_CONST)
		{
			r->m_dn = 0;//AllocDataRegister(0);	// result is in d0

			Temp_temp* r1 = munchExpression(pFun, f->binop.left);

			// save scratch registers (d1,a0,a1)
			if (m_regsinuse[1]) move(SIZE_L, 0,1, 4,7);
			if (m_regsinuse[8]) move(SIZE_L, 1,0, 4,7);
			if (m_regsinuse[9]) move(SIZE_L, 1,1, 4,7);

			ASSERT(r1->m_an >= 8);
			jsr(5, r1->m_an-8);
			fput16(fileout, f->binop.right->const_int.int32Val);

			// restore scratch registers (d1,a0,a1)
			if (m_regsinuse[9]) move(SIZE_L, 3,7, 1,1);
			if (m_regsinuse[8]) move(SIZE_L, 3,7, 1,0);
			if (m_regsinuse[1]) move(SIZE_L, 3,7, 0,1);

			de(r1);
		}
		else if (/*e->call.f->kind == T_Exp::T_MEM &&*/
					f->kind == T_Exp::T_CONST)
		{
			r->m_dn = 0;//AllocDataRegister(0);	// result is in d0

			jsr(7, 1);	// (xxx).L

			ASSERT(0);
#if 0
			if (f->const_int.reloc)
			{
				f->const_int.reloc->VirtualAddress = ftell(fileout);
				pFun->AddRelocation(f->const_int.reloc);
			}
#endif
			fput32(fileout, f->const_int.int32Val);
		}
		else
		{
			ASSERT(0);
#if 0
			r = new Temp_temp;
			r->m_dn = 0;//AllocDataRegister(0);	// result is in d0

			Temp_temp* r1 = munchExpression(pFun, e->call.f);

			jsr(5, r1->m_an-8);

			de(r1);
#endif
		}

		if (stackSize > 0)	// adjust stack pointer
		{
			if (stackSize <= 8)
			{
				addq(stackSize, 2/*size*/,1,7);	// addq #stackSize,a7
			}
			else
			{
				add(3/*word*/, 7/*a7*/, 7,4);	// adda #stackSize,a7
				fput16(fileout, stackSize);
			}
		}

		while (templist)
		{
			de(templist->temp);
			templist = templist->tail;
		}

		return r;
#endif
	}
	break;

	case T_Exp::T_NAME:
		{
			Temp_temp** r = new Temp_temp*;
			*r = new Temp_temp;
			e->m_result = r;
			(*r)->m_size = 4;

			pFun->emit(AS_Oper(m68k_MOVE(m68k_NAME(e->name.label), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), NULL));

			return r;
		}
		break;

	default:
		ASSERT(0);
	}

	return NULL;
}

Temp_temp** CCodeGen68k::munchExpression2(CFunctionCode* pFun, T_Exp* e)
{
	switch (e->kind)
	{
	case T_Exp::T_MEM:
	{
		Temp_temp** r = e->m_result;
		ASSERT(r);
		/*
		r->m_dn = AllocDataRegister(r);

		Temp_temp* t = new Temp_temp;
		t->m_an = AllocAddrRegister(t);
		*/

		if (e->mem.mem->kind == T_Exp::T_BINOP &&
			e->mem.mem->binop.op == '+' &&
			e->mem.mem->binop.right->kind == T_Exp::T_CONST)
		{
			Temp_temp** r1 = munchExpression(pFun, e->mem.mem->binop.left);

			/*
			if (!r1->m_precolored)
			{
				r1->m_an++;
			}
			*/

			if (e->mem.size <= 4)
			{
				pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e->mem.mem->binop.right->const_int.int32Val), m68k_DATAREG(r), e->mem.size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
			}
			else
			{
				pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e->mem.mem->binop.right->const_int.int32Val+4), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e->mem.mem->binop.right->const_int.int32Val), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList(r1, NULL)));
			}
		}
		else if (e->mem.mem->kind == T_Exp::T_CONST)
		{
			pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT(m68k_IMM(e->mem.mem->const_int.int32Val)), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), NULL));
		}
		else
		{
			Temp_temp** r1 = munchExpression2(pFun, e->mem.mem);

			ASSERT((*r1)->getn() >= 8);
		//r1->m_a = 8;	// address register
	//	move(SIZE_L, 0,r1->m_dn, 1,t->m_an-8);

			pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT(r1), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
		}

		/*
		if (e->mem_size == 1)
		{
			move(SIZE_B, 2,t->m_an-8, 0,r->m_dn);
			ext(r->m_dn, 2);	// TODO, not here
			ext(r->m_dn, 3);	// TODO, not here
		}
		else if (e->mem_size == 2)
		{
			move(SIZE_W, 2,t->m_an-8, 0,r->m_dn);
			ext(r->m_dn, 3);	// TODO, not here
		else
		}
		*/
		/*
		if (e->mem.size == 4)
		{
			//move(SIZE_L, 2,t->m_an-8, 0,r->m_dn);
		}
		else
			ASSERT(0);
*/
	//	de(r1);
	//	de(t);

		return r;
	}
	break;
#if 0
	/*
	else if (e->kind == cpp::T_Exp::T_ADDR)
	{
	}
	*/
#endif
	case T_Exp::T_TEMP:
	{
		return e->m_result;
	}
	break;

	/*
	else if (e->kind == cpp::T_Exp::T_CONST)
	{
	//	printf("temp");
		Temp_temp* r = new Temp_temp;
		emit(SD_Oper("MOVE", NULL, new Temp_tempList(e
		return r;
	}
	*/
	case T_Exp::T_UNOP:
	{
		switch (e->unop.op)
		{
		case '-':
			{
				Temp_temp** r = e->m_result;

				Temp_temp** r2 = munchExpression2(pFun, e->unop.exp);

				if ((*r2)->m_second)
				{
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r2)->m_second, NULL)));

					pFun->emit(AS_Oper(m68k_NEG(m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
					pFun->emit(AS_Oper(m68k_NEGX(m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r)->m_second, NULL)));
				}
				else
				{
					ASSERT(0);
				}

				return r;
			}
			break;

		case 'se':
			{
				Temp_temp** r = e->m_result;
			//	e->m_result = r;
			//	r->m_size = 4;

				Temp_temp** r2 = munchExpression2(pFun, e->unop.exp);

				if (e->m_size == 8)
				{
					if ((*r2)->m_size == 4)	// int32->int64
					{
						ASSERT((*r)->getn() < 8);

					//	r->m_dn++;

						pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
						pFun->emit(AS_Oper(m68k_TST(m68k_DATAREG(r)), NULL, new Temp_tempList(r, NULL)));
						pFun->emit(AS_Oper(m68k_SET(11/*mi*/, m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList(r, NULL)));
						pFun->emit(AS_Oper(m68k_EXT((*r)->m_second, 7), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r)->m_second, NULL)));
					}
					else
						ASSERT(0);
				}
				else if (e->m_size == 4)
				{
					if ((*r2)->m_size == 2)	// word->long
					{
						if ((*r)->getn() < 8)
						{
						//	r->m_dn = r2->m_dn;
						//	r->m_an = r2->m_an;

							pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), (*r2)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
							pFun->emit(AS_Oper(m68k_EXT(r, 3), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
						}
						else
						{
							// MOVEA
							pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 2/*r2->m_size*/), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
						}
					}
					else if ((*r2)->m_size == 1)	// byte->long
					{
						ASSERT((*r)->getn() < 8);

						//r->m_dn = r2->m_dn;
						//r->m_an = r2->m_an;
					//	r->m_dn++;

						pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), (*r2)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
						pFun->emit(AS_Oper(m68k_EXT(r, 7), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
					}
					else
						ASSERT(0);
				}

				return r;
			}
			break;

		case 'trun':
			{
				if (e->unop.exp->kind == T_Exp::T_BINOP &&
					e->unop.exp->binop.op == 'sdiv' &&

					e->unop.exp->binop.left->m_size == 8/*kind == T_Exp::T_TEMP &&
					e->unop.exp->binop.left->temp->m_second != NULL*/ &&	// 64bit

					e->unop.exp->binop.right->kind == T_Exp::T_UNOP &&
					e->unop.exp->binop.right->unop.op == 'se')	// 32bit originally
				{
					Temp_temp** q = e->m_result;

					// cpu 68020
					// 64/32 -> 32r:32q

					//Temp_temp* left = e->unop.exp->binop.left->temp;
					Temp_temp** left = munchExpression2(pFun, e->unop.exp->binop.left);

					Temp_temp** r = (*q)->m_aux;

					// dst/src -> dst

					Temp_temp** r2 = munchExpression2(pFun, e->unop.exp->binop.right->unop.exp);

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(left), m68k_DATAREG(q), 4), new Temp_tempList(q, NULL), new Temp_tempList(left, NULL)));
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*left)->m_second), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList((*left)->m_second, NULL)));
					pFun->emit(AS_Oper(m68k_DIVS(m68k_DATAREG(r2), q, r), new Temp_tempList(q, new Temp_tempList(r, NULL)), new Temp_tempList(q, new Temp_tempList(r, new Temp_tempList(r2, NULL)))));

					return q;	// return quotient
				}
				else
				{
					Temp_temp** r = e->m_result;
				//	e->m_result = r;
				//	r->m_size = 4;

					Temp_temp** r2 = munchExpression2(pFun, e->unop.exp);
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), (*r2)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));

					return r;
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
	break;

	case T_Exp::T_BINOP:
	{
		Temp_temp** r = e->m_result;//new Temp_temp;
	//	Temp_temp** r = e->m_dst->temp;//munchExpression2(pFun, e->binop.left);

		if (e->binop.op == '+')
		{
			//r->m_dn = AllocDataRegister(r);

#if 0
			if (e->binop.left->kind == T_Exp::T_CONST)
			{
				Temp_temp* r2 = munchExpression(pFun, e->binop.right);

				if (r2->m_dn != -1)
					move(SIZE_L, 0, r2->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r2->m_an-8, 0, r->m_dn);

				addi(e->binop.left->const_int.int32Val, 2/*long*/, 0, r->m_dn);

				de(r2);
			}
			else if (e->binop.right->kind == T_Exp::T_CONST)
			{
				Temp_temp* r1 = munchExpression(pFun, e->binop.left);

				if (r1->m_dn != -1)
					move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

				addi(e->binop.right->const_int.int32Val, 2/*long*/, 0, r->m_dn);

				de(r1);
			}
			else
#endif
			if ((*r)->getn() >= 8 && e->binop.left->kind == T_Exp::T_TEMP && (*e->binop.left->temp)->getn() >= 8 && e->binop.right->kind == T_Exp::T_CONST &&
					(__int64)e->binop.right->const_int.int32Val >= -32768 &&
					(__int64)e->binop.right->const_int.int32Val <= 32767)
			{
				Temp_temp** r1 = munchExpression2(pFun, e->binop.left);
				/*
				if (!r1->m_precolored)
				{
					r1->m_an++;
				}
				*/

				//	Temp_temp* r2 = munchExpression(pFun, src->binop.left);
				pFun->emit(AS_Oper(m68k_LEA(m68k_INDIRECT_DISPLACEMENT(r1, e->binop.right->const_int.int32Val), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
			}
			else if (e->binop.right->kind == T_Exp::T_CONST)
			{
				Temp_temp** r1 = munchExpression2(pFun, e->binop.left);

			//	(*r)->m_dn = (*r1)->m_dn;// + (*r2)->m_dn;
			//	(*r)->m_an = (*r1)->m_an;// + (*r2)->m_an;

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), (*r1)->m_size), new Temp_tempList(r, NULL), /*e->m_src[1] =*/ new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Oper(m68k_ADD(m68k_IMM(e->binop.right->const_int.int32Val), m68k_DATAREG(r)), /*e->m_dst =*/ new Temp_tempList(r, NULL), NULL));
			}
			else
			{
				Temp_temp** r1 = munchExpression2(pFun, e->binop.left);
				Temp_temp** r2 = munchExpression2(pFun, e->binop.right);

			//	Temp_temp** r1 = e->m_src[0]->temp;//munchExpression2(pFun, e->binop.right);
			//	Temp_temp** r2 = e->m_src[1]->temp;//munchExpression2(pFun, e->binop.right);

				if ((*r1)->m_second)
				{
					ASSERT((*r2)->m_second);

				//	r->m_second = new Temp_temp;

				//	r->m_dn++;
				//	r->m_second->m_dn++;

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r2)->m_second, NULL)));

					pFun->emit(AS_Oper(m68k_ADD(m68k_DATAREG(r1), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(m68k_ADDX(m68k_DATAREG((*r1)->m_second), m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r1)->m_second, NULL)));
				}
				else
				{
				//	r->m_dn = r1->m_dn + r2->m_dn;
				//	r->m_an = r1->m_an + r2->m_an;

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
					pFun->emit(AS_Oper(m68k_ADD(m68k_DATAREG(r1), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				}
				/*
				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Oper(m68k_ADD(m68k_DATAREG(r2), m68k_DATAREG(r)), NULL, new Temp_tempList(r2, NULL)));
*/

				/*
				if (r1->m_dn != -1)
					move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

				add(2, r->m_dn, 0,r2->m_dn);

				de(r1);
				de(r2);
				*/
			}
		}
		else if (e->binop.op == '-')
		{
			if (e->binop.right->kind == T_Exp::T_CONST)
			{
				Temp_temp** r1 = munchExpression2(pFun, e->binop.left);

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), (*r1)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				if (e->binop.right->const_int.int32Val >= 1 && e->binop.right->const_int.int32Val <= 8)
				{
					pFun->emit(AS_Oper(m68k_SUBQ(e->binop.right->const_int.int32Val, m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
				}
				else
				{
					(*r)->m_dn++;
					// dst = dst - src
					// r = r2 - r
					pFun->emit(AS_Oper(m68k_SUBI(e->binop.right->const_int.int32Val, m68k_DATAREG(r), (*r1)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
				}
			}
			else if (e->binop.left->kind == T_Exp::T_CONST)
			{
				ASSERT(0);
			}
			else
			{
				Temp_temp** r1 = munchExpression2(pFun, e->binop.left);
				Temp_temp** r2 = munchExpression2(pFun, e->binop.right);

				if ((*r1)->m_second)
				{
					ASSERT((*r2)->m_second);

				//	r->m_second = new Temp_temp;

				//	r->m_dn++;
				//	r->m_second->m_dn++;

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r1)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r1)->m_second, NULL)));

					pFun->emit(AS_Oper(m68k_SUB(m68k_DATAREG(r2), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
					pFun->emit(AS_Oper(m68k_SUBX(m68k_DATAREG((*r2)->m_second), m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r2)->m_second, NULL)));
				}
				else
				{
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(m68k_SUB(m68k_DATAREG(r2), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				}
			}
		}
		else if (e->binop.op == '*')
		{
			if (e->binop.left->kind == T_Exp::T_UNOP && e->binop.left->unop.op == 'se' && e->binop.left->m_size == 8 &&
				e->binop.right->kind == T_Exp::T_UNOP && e->binop.right->unop.op == 'se' && e->binop.right->m_size == 8)
			{
				Temp_temp** r1 = munchExpression2(pFun, e->binop.left->unop.exp);
				Temp_temp** r2 = munchExpression2(pFun, e->binop.right->unop.exp);

				if ((*r1)->getn() >= 8)
				{
					ASSERT(0);
				}

				if ((*r2)->getn() >= 8)
				{
					ASSERT(0);
				}

				/*
				r1->m_dn++;
				r2->m_dn++;

				r->m_dn = r1->m_dn + r2->m_dn;
				r->m_an = r1->m_an + r2->m_an;
				*/

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				pFun->emit(AS_Oper(m68k_MULS(m68k_DATAREG(r1), r, (*r)->m_second), new Temp_tempList(r, new Temp_tempList((*r)->m_second, NULL)), new Temp_tempList(r, new Temp_tempList(r1, NULL))));
			}
			else
			{
				Temp_temp** r1 = munchExpression2(pFun, e->binop.left);
				Temp_temp** r2 = munchExpression2(pFun, e->binop.right);

			//	(*r1)->m_dn++;
			//	(*r2)->m_dn++;

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				pFun->emit(AS_Oper(m68k_MULS(m68k_DATAREG(r1), r, NULL), new Temp_tempList(r, NULL), new Temp_tempList(r, new Temp_tempList(r1, NULL))));
			}
#if 0
			r->m_dn = AllocDataRegister(r);

			if (e->binop.left->kind == T_Exp::T_CONST)
			{
				Temp_temp* r2 = munchExpression(pFun, e->binop.right);

				if (r2->m_dn != -1)
					move(SIZE_L, 0, r2->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r2->m_an-8, 0, r->m_dn);

				muls(r->m_dn, 7, 4);
				fput16(fileout, e->binop.left->const_int.int32Val);

				de(r2);
			}
			else if (e->binop.right->kind == T_Exp::T_CONST)
			{
				Temp_temp* r1 = munchExpression(pFun, e->binop.left);

				if (r1->m_dn != -1)
					move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

				muls(r->m_dn, 7, 4);
				fput16(fileout, e->binop.right->const_int.int32Val);

				de(r1);
			}
#endif
			{
		//		ASSERT(0);
			//	Temp_temp* r1 = munchExpression(pFun, e->binop.left);
			//	Temp_temp* r2 = munchExpression(pFun, e->binop.right);

			//	pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
			//	emit(AS_Oper(m68k_MUL(), new Temp_tempList(r, NULL), new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

#if 0
				if (r1->m_dn != -1)
					move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

				muls(r->m_dn, 0, r2->m_dn);
			//	ext(r->m_dn, 3/*word -> long*/);

				de(r1);
				de(r2);
#endif
			}
		}
		else if (e->binop.op == '<<')
		{
			Temp_temp** r1 = munchExpression2(pFun, e->binop.left);
			Temp_temp** r2 = munchExpression2(pFun, e->binop.right);

			pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
			pFun->emit(AS_Oper(m68k_LSHIFT(1, m68k_DATAREG(r2), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
		}
		else if (e->binop.op == 'sar')
		{
			Temp_temp** r1 = munchExpression2(pFun, e->binop.left);
			Temp_temp** r2 = munchExpression2(pFun, e->binop.right);

			if ((*r1)->m_second)
			{
				Temp_label* label = new Temp_label;
				Temp_label* done_label = new Temp_label;

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r1)->m_second), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r1)->m_second, NULL)));
				//pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r1->m_second), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));

				pFun->emit(AS_Oper(m68k_ANDI(63, m68k_DATAREG(r2), 4), new Temp_tempList(r2, NULL), new Temp_tempList(r2, NULL)));
				pFun->emit(AS_Oper(m68k_SUBQ(1, m68k_DATAREG(r2)), new Temp_tempList(r2, NULL), new Temp_tempList(r2, NULL)));
				pFun->emit(AS_Oper(m68k_Bcc(11/*minus*/, done_label), NULL, NULL));
				pFun->emit(AS_Label(label));
				pFun->emit(AS_Oper(m68k_ASR(m68k_DATAREG((*r)->m_second)), new Temp_tempList((*r)->m_second, NULL), new Temp_tempList((*r)->m_second, NULL)));
				pFun->emit(AS_Oper(m68k_ROXR(m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
			//	pFun->emit(AS_Oper(m68k_ASR(m68k_DATAREG(r->m_second)), new Temp_tempList(r->m_second, NULL), new Temp_tempList(r->m_second, NULL)));
			//	pFun->emit(AS_Oper(m68k_ROXR(m68k_DATAREG(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));
				pFun->emit(AS_Oper(m68k_DBcc(1/*never true*/, r2, label), new Temp_tempList(r2, NULL), new Temp_tempList(r2, NULL)));
				pFun->emit(AS_Label(done_label));
			}
			else
				ASSERT(0);

		}
#if 0
		else if (e->binop.op == '/')
		{
			r->m_dn = AllocDataRegister(r);

			Temp_temp* r1 = munchExpression(pFun, e->binop.left);
			Temp_temp* r2 = munchExpression(pFun, e->binop.right);

			emit(AS_Oper("DIVU", new Temp_tempList(r, NULL), new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

			if (r1->m_dn != -1)
				move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
			else
				move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

			divu(r->m_dn, 0, r2->m_dn);
			ext(r->m_dn, 3/*word -> long*/);

			de(r1);
			de(r2);
		}
		else if (e->binop.op == '%')
		{
			r->m_dn = AllocDataRegister(r);

			Temp_temp* r1 = munchExpression(pFun, e->binop.left);
			Temp_temp* r2 = munchExpression(pFun, e->binop.right);

			emit(AS_Oper("SUB", new Temp_tempList(r, NULL), new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

			if (r1->m_dn != -1)
				move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
			else
				move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

			divu(r->m_dn, 0, r2->m_dn);

			// shift right
			{
				uint16 word = 0xE008;

				int ir = 0;
				int size = 2;	// long
				int dr = 0;	// right
				word |= r->m_dn;
				word |= ir<<5;
				word |= size<<6;
				word |= dr<<8;
				word |= 0<<9;	// 8
				fput16(fileout, word);

				fput16(fileout, word);	// Do it twice
			}

			de(r1);
			de(r2);
		}
		else if (e->binop.op == '<<' || e->binop.op == '>>')
		{
			r->m_dn = AllocDataRegister(r);

			int dr = (e->binop.op=='<<')? SHIFT_LEFT: SHIFT_RIGHT;

			if (e->binop.left->kind == T_Exp::T_CONST)
			{
				Temp_temp* r2 = munchExpression(pFun, e->binop.right);

				move(SIZE_L, 7,4, 0,r->m_dn);
				fput32(fileout, e->binop.left->const_int.int32Val);

				logic_shift(dr, 2/*long*/, 1/*reg*/,r2->m_dn, r->m_dn);

				de(r2);
			}
			else if (e->binop.right->kind == T_Exp::T_CONST)
			{
				ASSERT(0);	// TODO
			}
			else
			{
				ASSERT(0);
#if 0
				r->m_dn = AllocDataRegister(r);

				Temp_temp* r1 = munchExpression(pFun, e->binop.left);
				Temp_temp* r2 = munchExpression(pFun, e->binop.right);

				emit(AS_Oper("SUB", new Temp_tempList(r, NULL), new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

				if (r1->m_dn != -1)
					move(SIZE_L, 0, r1->m_dn, 0, r->m_dn);
				else
					move(SIZE_L, 1, r1->m_an-8, 0, r->m_dn);

				//divu(r->m_dn, 0, r2->m_dn);

				logic_shift(dr, 2/*long*/, 1/*reg*/,r->m_dn);

				de(r1);
				de(r2);
#endif
			}
		}
#endif
		else
			ASSERT(0);

		return r;
	}
	break;

	case T_Exp::T_CONST:
	{
		Temp_temp** r = e->m_result;//new Temp_temp;
	//	r->m_dn = AllocDataRegister(r);

		if (e->m_size <= 4)
		{
			if (e->const_int.int32Val == 0)
			{
				pFun->emit(AS_Oper(m68k_CLR(m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), NULL));
			}
			else if ((*r)->getn() < 8 && e->const_int.int32Val >= -128 && e->const_int.int32Val < 127)
			{
				pFun->emit(AS_Oper(m68k_MOVEQ(e->const_int.int32Val, r), new Temp_tempList(r, NULL), NULL));
			}
			else
			{
				pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(e->const_int.int32Val), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), NULL));//new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
			}
		}
		else if (e->m_size == 8)
		{
		//	r->m_second = new Temp_temp;

			pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(e->const_int.int64Val&0xFFFFFFFF), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), NULL));
			pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(e->const_int.int64Val>>32), m68k_DATAREG((*r)->m_second), 4), new Temp_tempList((*r)->m_second, NULL), NULL));
		}
		else
			ASSERT(0);

		return r;

#if 0
	//	char assem[64];
	//	sprintf(assem, "MOVEI #%d", e->tok.int32);
	//	emit(AS_Oper(assem, new Temp_tempList(r, NULL), NULL));

		move(SIZE_L, 7,4, 0,r->m_dn);
		ASSERT(0);
#if 0
		if (e->const_int.reloc)
		{
			e->const_int.reloc->VirtualAddress = ftell(fileout);
			pFun->AddRelocation(e->const_int.reloc);
		}
#endif

		fput32(fileout, e->const_int.int32Val);
		//fwrite_const32(fileout, e->tok.int32);

		return r;
#endif
	}
	break;

	case T_Exp::T_CALL:
	{
	//	Temp_temp** r = e->m_result;
		Temp_temp** r = NULL;//e->m_dst->temp;

		T_Exp* f;
		if (e->call.f->kind == T_Exp::T_MEM)
			f = e->call.f->mem.mem;
		else
			f = e->call.f;

		ArgList* pArgList;

		// evaluate those that go on stack since they don't occupy registers
		int stacksize = 0;

		pArgList = e->call.args;
		while (pArgList)
		{
			T_Exp* e2 = pArgList->head;

			if (pArgList->reg == NULL)
/*			{
				Temp_temp* r2 = args[i];

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(pArgList->reg), pArgList->reg->m_size), new Temp_tempList(pArgList->reg, NULL), new Temp_tempList(r2, NULL)));
				
				templist = new Temp_tempList(pArgList->reg, templist);
				i++;
			}
			else
*/			{
				if (e2->kind == T_Exp::T_NAME)
				{
					pFun->emit(AS_Oper(m68k_MOVE(m68k_NAME(e2->name.label), m68k_INDIRECT_PREDEC(&a7), 4), NULL, NULL));
					stacksize += 4;
				}
				else if (e2->kind == T_Exp::T_CONST)
				{
					pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(e2->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), 4), NULL, NULL));
					stacksize += 4;
				}
				else if (e2->kind == T_Exp::T_BINOP && e2->binop.op == '+' &&
							e2->binop.left->kind == T_Exp::T_TEMP && e2->binop.right->kind == T_Exp::T_CONST &&
							e2->binop.right->const_int.int32Val >= -32768 &&
							e2->binop.right->const_int.int32Val <= 32767)
				{
					Temp_temp** r1 = munchExpression(pFun, e2->binop.left);

					pFun->emit(AS_Oper(m68k_PEA(m68k_INDIRECT_DISPLACEMENT(r1, e2->binop.right->const_int.int32Val)), NULL, new Temp_tempList(r1, NULL)));

					stacksize += 4;
				}
				else if (e2->kind == T_Exp::T_MEM &&
							e2->mem.mem->kind == T_Exp::T_BINOP &&
							e2->mem.mem->binop.op == '+' &&
							e2->mem.mem->binop.right->kind == T_Exp::T_CONST)
				{
					Temp_temp** r1 = munchExpression2(pFun, e2->mem.mem->binop.left);

					if (e2->mem.size <= 4)
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, NULL)));
						stacksize += 4;
					}
					else if (e2->mem.size == 8)
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val+4), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r1, NULL)));
						pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r1, NULL)));
						stacksize += 8;
					}
					else
						ASSERT(0);
				}
				else if (e2->kind == T_Exp::T_MEM &&
							e2->mem.mem->kind == T_Exp::T_BINOP &&
							e2->mem.mem->binop.op == '+')
				{
					Temp_temp** r1 = munchExpression2(pFun, e2->mem.mem->binop.left);

					if (e2->mem.mem->binop.right->kind == T_Exp::T_BINOP &&
						e2->mem.mem->binop.right->binop.op == '<<' &&
						e2->mem.mem->binop.right->binop.right->kind == T_Exp::T_CONST &&
						(e2->mem.mem->binop.right->binop.right->const_int.int32Val == 0 ||
						e2->mem.mem->binop.right->binop.right->const_int.int32Val == 1 ||
						e2->mem.mem->binop.right->binop.right->const_int.int32Val == 2 ||
						e2->mem.mem->binop.right->binop.right->const_int.int32Val == 3))
					{
						int scalefactor = e2->mem.mem->binop.right->binop.right->const_int.int32Val;

						if (e2->mem.mem->binop.right->binop.left->kind == T_Exp::T_BINOP &&
							e2->mem.mem->binop.right->binop.left->binop.op == '-' &&
							e2->mem.mem->binop.right->binop.left->binop.right->kind == T_Exp::T_CONST &&
							((__int64)e2->mem.mem->binop.right->binop.left->binop.right->const_int.int32Val<<scalefactor) >= -128 &&
							((__int64)e2->mem.mem->binop.right->binop.left->binop.right->const_int.int32Val<<scalefactor) <= 127)
						{
							Temp_temp** r2 = munchExpression2(pFun, e2->mem.mem->binop.right->binop.left->binop.left);

							int8 disp8 = -(int)(e2->mem.mem->binop.right->binop.left->binop.right->const_int.int32Val << scalefactor);

							if (e2->mem.size <= 4)
							{
								pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_INDEX(disp8, r1, r2, scalefactor), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
							}
							else
								ASSERT(0);
						}
						else
						{
							Temp_temp** r2 = munchExpression2(pFun, e2->mem.mem->binop.right->binop.left);


							/*
							if (!(*r1)->m_precolored)
							{
								(*r1)->m_an++;
							}

							if (!(*r2)->m_precolored)
							{
								(*r2)->m_dn++;
							}
							*/

							if (e2->mem.size <= 4)
							{
								pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_INDEX(0/*disp8*/, r1, r2, scalefactor), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
								stacksize += 4;
							}
							else
								ASSERT(0);
						}
					}
					else
					{
						Temp_temp** r2 = munchExpression2(pFun, e2->mem.mem->binop.right);

						/*
						if (!(*r1)->m_precolored)
						{
							(*r1)->m_an++;
						}

						if (!(*r2)->m_precolored)
						{
							(*r2)->m_dn++;
						}
						*/

						if (e2->mem.size <= 4)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_INDEX(0/*disp8*/, r1, r2, 0/*scalefactor*/), m68k_INDIRECT_PREDEC(&a7), e->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
							stacksize += 4;
						}
						/*
						else
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_INDEXACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val+4), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r1, NULL)));
							pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT_DISPLACEMENT(r1, e2->mem.mem->binop.right->const_int.int32Val), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r1, NULL)));
						}
						*/
					}
				}
				else
				{
					Temp_temp** r2 = munchExpression2(pFun, e2);

				//	Temp_temp** r2 = e->m_src[0]->temp;

					pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList(r2, NULL)));
					stacksize += 4;

					if ((*r2)->m_second)
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_INDIRECT_PREDEC(&a7), 4), NULL, new Temp_tempList((*r2)->m_second, NULL)));
						stacksize += 4;
					}
				}
			}

			pArgList = pArgList->tail;
		}

		// evaluate those that go in registers
		vector<Temp_temp**> args;
		pArgList = e->call.args;
		while (pArgList)
		{
			if (pArgList->reg)
			{
				Temp_temp** r2 = munchExpression2(pFun, pArgList->head);
				args.push_back(r2);
			}

			pArgList = pArgList->tail;
		}

		// put them in correct registers
		Temp_tempList* templist = NULL;
		int i = 0;
		pArgList = e->call.args;
		while (pArgList)
		{
			T_Exp* e = pArgList->head;

			if (pArgList->reg)
			{
				Temp_temp** r2 = args[i];

				pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(pArgList->reg), (*pArgList->reg)->m_size), new Temp_tempList(pArgList->reg, NULL), new Temp_tempList(r2, NULL)));

				templist = new Temp_tempList(pArgList->reg, templist);
				i++;
			}

			pArgList = pArgList->tail;
		}

		if (f->kind == T_Exp::T_BINOP &&
			f->binop.op == '+' &&
			f->binop.right->kind == T_Exp::T_CONST)
		{
			Temp_temp** r1 = munchExpression2(pFun, f->binop.left);

			/*
			if (!r1->m_precolored)
			{
				r1->m_an++;
			}
			*/

			templist = new Temp_tempList(r1, templist);

			pFun->emit(AS_Oper(m68k_JSR(m68k_INDIRECT_DISPLACEMENT(r1, f->binop.right->const_int.int32Val)),
				new Temp_tempList(&d0, new Temp_tempList(&d1, new Temp_tempList(&a0, new Temp_tempList(&a1, NULL)))),
				templist));

			pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(&d0), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(&d0, NULL)));
		}
		else if (f->kind == T_Exp::T_NAME)
		{
			pFun->emit(AS_Oper(m68k_JSR(m68k_NAME(f->name.label)),
				NULL,//new Temp_tempList(&d0, new Temp_tempList(&d1, new Temp_tempList(&a0, new Temp_tempList(&a1, NULL)))),
				templist));

#if 0
			pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(&d0), m68k_DATAREG(r), (*r)->m_size), new Temp_tempList(r, NULL), new Temp_tempList(&d0, NULL)));
#endif
		}
		else
			ASSERT(0);

		if (stacksize > 0)
		{
			pFun->emit(AS_Oper(m68k_ADD(m68k_IMM(stacksize), m68k_DATAREG(&a7)), NULL, NULL));
		
		}

		return r;
	}
	break;

	case T_Exp::T_NAME:
		{
			Temp_temp** r = e->m_result;

			pFun->emit(AS_Oper(m68k_MOVE(m68k_NAME(e->name.label), m68k_DATAREG(r), 4), new Temp_tempList(r, NULL), NULL));

			return r;
		}
		break;

	default:
		ASSERT(0);
	}
	return NULL;
}

void CCodeGen68k::munchStatement(CFunctionCode* pFun, T_Stm* s)
{
	switch (s->kind)
	{
	case T_Stm::T_LABEL:
		{
			printf("label %d\n", s->label->m_n);
			pFun->emit(AS_Label(s->label));

#if 0
			ASSERT(s->label->m_pos == -1);
			s->label->m_pos = ftell(fileout);
			FlushLabel(s->label);
#endif
		}
		break;

	case T_Stm::T_MOVE:
		{
			printf("move\n");

			T_Exp* dst = s->move.left;
			T_Exp* src = s->move.right;
			if (dst->kind == T_Exp::T_MEM)
			{
				if (dst->mem.mem->kind == T_Exp::T_CONST)
				{
					if (src->kind == T_Exp::T_MEM && src->mem.mem->kind == T_Exp::T_CONST)
					{
						move(SIZE_L, 7,1, 7,1);

						ASSERT(0);
#if 0
						if (src->mem->const_int.reloc)
						{
							src->mem->const_int.reloc->VirtualAddress = ftell(fileout);
							pFun->AddRelocation(src->mem->const_int.reloc);
						}
#endif
						fput32(fileout, src->mem.mem->const_int.int32Val);

						ASSERT(0);
#if 0
						if (dst->mem->const_int.reloc)
						{
							dst->mem->const_int.reloc->VirtualAddress = ftell(fileout);
							pFun->AddRelocation(dst->mem->const_int.reloc);
						}
#endif
						fput32(fileout, dst->mem.mem->const_int.int32Val);
					}
					else
					{
						ASSERT(0);
						Temp_temp** r2 = munchExpression(pFun, src);
					}
				}
				else if (dst->mem.mem->kind == T_Exp::T_BINOP &&
							dst->mem.mem->binop.op == '+' &&
							dst->mem.mem->binop.right->kind == T_Exp::T_CONST)
				{
					//T_Exp* e1 = ;
				//	T_Exp* e2 = src;

					Temp_temp** r1 = munchExpression(pFun, dst->mem.mem->binop.left);
					//Temp_temp* r2 = munchExpression(pFun, e2);

					if (!(*r1)->m_precolored)
					{
						(*r1)->m_an++;
					}

					/*
					if (src->kind == T_Exp::T_CONST_DOUBLE)
					{
						ASSERT(dst->mem.size == 8);
						pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM((long)(src->const_int.int32Val & 0xffffffff)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), 4), NULL, new Temp_tempList(r1, NULL)));
						pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM((long)(src->const_int.int32Val >> 32)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val+4), 4), NULL, new Temp_tempList(r1, NULL)));
					}
					else
						*/
						if (src->kind == T_Exp::T_CONST || src->kind == T_Exp::T_CONST_DOUBLE)
					{
						if (dst->mem.size <= 4)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(src->const_int.int32Val), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), src->m_size), NULL, new Temp_tempList(r1, NULL)));
						}
						else if (dst->mem.size == 8)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM((src->const_int.int32Val)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val+4), 4), NULL, new Temp_tempList(r1, NULL)));

							if ((src->const_int.int64Val >> 32) != 0)
								pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM((src->const_int.int64Val >> 32)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), 4), NULL, new Temp_tempList(r1, NULL)));
							else
								pFun->emit(AS_Oper(m68k_CLR(m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), 4), NULL, new Temp_tempList(r1, NULL)));
						}
						else
							ASSERT(0);

#if 0
						if (r1->m_an != -1)
						{
							if (dst->mem.size == 1)
							{
								move(SIZE_B, 7,4, 5,r1->m_an-8);
								ASSERT(0);
#if 0
								ASSERT(src->const_int.reloc == NULL);
#endif
								fput16(fileout, src->const_int.int32Val);
							}
							else if (dst->mem.size == 2)
							{
								move(SIZE_W, 7,4, 5,r1->m_an-8);
								ASSERT(0);
#if 0
								ASSERT(src->const_int.reloc == NULL);
#endif
								fput16(fileout, src->const_int.int32Val);
							}
							else if (dst->mem.size == 4)
							{
							//	move(SIZE_L, 7,4, 5,r1->m_an-8);
								move(SIZE_L, 7,4, 5,r1->m_n);
							//	ASSERT(0);
#if 0
								if (src->const_int.reloc)
								{
									src->const_int.reloc->VirtualAddress = ftell(fileout);
									pFun->AddRelocation(src->const_int.reloc);
								}
#endif
								fput32(fileout, src->const_int.int32Val);
							}
							else
								ASSERT(0);
						}
						else
						{
							Temp_temp* t = new Temp_temp;
							t->m_an = AllocAddrRegister(t);

							move(SIZE_L, 0,r1->m_dn, 1,t->m_an-8);

							if (dst->mem.size == 1)
							{
								ASSERT(0);
#if 0
								ASSERT(src->const_int.reloc == NULL);
#endif
								move(SIZE_B, 7,4, 5,t->m_an-8);
								fput16(fileout, src->const_int.int32Val);
							}
							else if (dst->mem.size == 2)
							{
								ASSERT(0);
#if 0
								ASSERT(src->const_int.reloc == NULL);
#endif
								move(SIZE_W, 7,4, 5,t->m_an-8);
								fput16(fileout, src->const_int.int32Val);
							}
							else if (dst->mem.size == 4)
							{
								move(SIZE_L, 7,4, 5,t->m_an-8);

								ASSERT(0);
#if 0
								if (src->const_int.reloc)
								{
									src->const_int.reloc->VirtualAddress = ftell(fileout);
									pFun->AddRelocation(src->const_int.reloc);
								}
#endif
								fput32(fileout, src->const_int.int32Val);
							}
							else
								ASSERT(0);

							de(t);

							/*
							Temp_temp* t = new Temp_temp;
							t->m_an = AllocAddrRegister(t);

							move(2, 0,r1->m_dn, 1,t->m_an-8);

							if (dst->mem_size == 1)
								move(SIZE_B, 0,r2->m_dn, 5,t->m_an-8);
							else if (dst->mem_size == 2)
								move(SIZE_W, 0,r2->m_dn, 5,t->m_an-8);
							else if (dst->mem_size == 4)
								move(SIZE_L, 0,r2->m_dn, 5,t->m_an-8);
							else
								ASSERT(0);

							de(t);
							*/
						}
#endif
					}
					else if (src->kind == T_Exp::T_MEM && src->mem.mem->kind == T_Exp::T_CONST)
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT(m68k_IMM(src->mem.mem->const_int.int32Val)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), src->mem.size), NULL, new Temp_tempList(r1, NULL)));
					}
					else
					{
						Temp_temp** r2 = munchExpression(pFun, src);

						if (dst->mem.size <= 4)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), dst->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
						}
						else if (dst->mem.size == 8)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val+4), 4), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
							pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), 4), NULL, new Temp_tempList(r1, new Temp_tempList((*r2)->m_second, NULL))));
						}

						//pFun->emit(AS_Oper(new m68kinstr, NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

#if 0
						if (r1->m_an != -1)
						{
							if (dst->mem.size == 1)
								move(SIZE_B, 0,r2->m_dn, 5,r1->m_an-8);
							else if (dst->mem.size == 2)
								move(SIZE_W, 0,r2->m_dn, 5,r1->m_an-8);
							else if (dst->mem.size == 4)
								move(SIZE_L, 0,r2->m_dn, 5,r1->m_an-8);
							else
								ASSERT(0);
						}
						else
						{
							Temp_temp* t = new Temp_temp;
							t->m_an = AllocAddrRegister(t);

							move(2, 0,r1->m_dn, 1,t->m_an-8);

							if (dst->mem.size == 1)
								move(SIZE_B, 0,r2->m_dn, 5,t->m_an-8);
							else if (dst->mem.size == 2)
								move(SIZE_W, 0,r2->m_dn, 5,t->m_an-8);
							else if (dst->mem.size == 4)
								move(SIZE_L, 0,r2->m_dn, 5,t->m_an-8);
							else
								ASSERT(0);

							de(t);
						}

						de(r2);
#endif
					}

#if 0
					fput16(fileout, dst->mem.mem->binop.right->const_int.int32Val);

					de(r1);
#endif
				}
				else if (dst->mem.mem->kind == T_Exp::T_BINOP &&
					dst->mem.mem->binop.op == '+' &&
					dst->mem.mem->binop.left->kind == T_Exp::T_CONST)
				{
					ASSERT(0);
					/*
					munchExpression(pFun, dst->mem->binop.right);
					printf("MOVE +%d", dst->mem->binop.left->tok.int32);
					*/
				}
				else //if (dst->mem.mem->kind == T_Exp::T_TEMP)
				{
					Temp_temp** r1 = munchExpression(pFun, dst->mem.mem);

					(*r1)->m_an++;

					// NOTE: r1 is set as a source, not a destination

					if (src->kind == T_Exp::T_CONST)
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(src->const_int.int32Val), m68k_INDIRECT(r1), dst->mem.size), NULL, new Temp_tempList(r1, NULL)));
					}
					else
					{
						Temp_temp** r2 = munchExpression(pFun, src);

						pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT(r1), dst->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
					}
				}
				/*
				else if (dst->kind == T_Exp::T_CONST)
				{
					ASSERT(0);
				}
				else
				{
					Temp_temp** r1 = munchExpression(pFun, dst->mem.mem);
					Temp_temp** r2 = munchExpression(pFun, src);

					(*r1)->m_an++;

					pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT(r1), dst->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
				}
				*/
			}
			else if (dst->kind == T_Exp::T_TEMP)
			{
			//	T_Exp* e1 = dst;
			//	T_Exp* e2 = src;

				Temp_temp** r1 = munchExpression(pFun, dst);

				if (src->kind == T_Exp::T_CONST)
				{
					if (src->const_int.int32Val >= -128 && src->const_int.int32Val <= 127)
					{
						(*r1)->m_dn++;

						pFun->emit(AS_Oper(m68k_MOVEQ(src->const_int.int32Val, r1), /*s->m_dst =*/ new Temp_tempList(r1, NULL), NULL));
					}
					else
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(src->const_int.int32Val), m68k_DATAREG(r1), (*r1)->m_size), /*s->m_dst =*/ new Temp_tempList(r1, NULL), NULL));
					}

					if ((*r1)->m_second)
					{
						(*(*r1)->m_second)->m_dn++;

						LONG high = src->const_int.int64Val >> 32;

						if (high == 0)
							pFun->emit(AS_Oper(m68k_CLR(m68k_DATAREG((*r1)->m_second), 4), new Temp_tempList((*r1)->m_second, NULL), NULL));
						else if (high == -1)
							pFun->emit(AS_Oper(m68k_MOVEQ(-1, (*r1)->m_second), new Temp_tempList((*r1)->m_second, NULL), NULL));
						else
							pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(high), m68k_DATAREG((*r1)->m_second), 4), new Temp_tempList((*r1)->m_second, NULL), NULL));
					}

					/*
					if (r1->m_dn != -1)
					{
						move(SIZE_L, 7,4, 0,r1->m_dn);
					}
					else
					{
						move(SIZE_L, 7,4, 1,r1->m_an-8);
					}

					ASSERT(0);
					*/
#if 0
					if (src->const_int.reloc)
					{
						src->const_int.reloc->VirtualAddress = ftell(fileout);
						pFun->AddRelocation(src->const_int.reloc);
					}
					fput32(fileout, src->const_int.int32Val);
#endif
				}
				/*
				else if (src->kind == T_Exp::T_BINOP && src->binop.op == '+' && src->binop.right->kind == T_Exp::T_CONST)
				{
					(*r1)->m_an++;

					Temp_temp** r2 = munchExpression(pFun, src->binop.left);
					pFun->emit(AS_Oper(m68k_LEA(m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), m68k_DATAREG(r1)), new Temp_tempList(r1, NULL), new Temp_tempList(r2, NULL)));

					ASSERT(0);
				}
				*/
				else if (src->kind == T_Exp::T_MEM &&
					src->mem.mem->kind == T_Exp::T_CONST)
				{
					pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT(m68k_IMM(src->mem.mem->const_int.int32Val)), m68k_DATAREG(r1), (*r1)->m_size), new Temp_tempList(r1, NULL), NULL));

					/*
					if (r1->m_dn != -1)
					{
						move(SIZE_L, 7,1, 0,r1->m_dn);
					}
					else
					{
						move(SIZE_L, 7,1, 1,r1->m_an-8);
					}

					ASSERT(0);
					*/
#if 0
					if (src->mem->const_int.reloc)
					{
						src->mem->const_int.reloc->VirtualAddress = ftell(fileout);
						pFun->AddRelocation(src->mem->const_int.reloc);
					}
#endif
					//fput32(fileout, src->mem.mem->const_int.int32Val);
				}
				else
				{
					Temp_temp** r2 = munchExpression(pFun, src);

					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r1), (*r1)->m_size), /*s->m_dst =*/ new Temp_tempList(r1, NULL), /*s->m_src[0] =*/ new Temp_tempList(r2, NULL)));
					if ((*r2)->m_second)
					{
						pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_DATAREG((*r1)->m_second), (*(*r1)->m_second)->m_size), new Temp_tempList((*r1)->m_second, NULL), new Temp_tempList((*r2)->m_second, NULL)));
					}

					/*
					if (r1->m_dn != -1)
					{
						move(SIZE_L, 0,r2->m_dn, 0,r1->m_dn);
					}
					else
					{
						if (r2->m_dn != -1)
							move(SIZE_L, 0,r2->m_dn, 1,r1->m_an-8);
						else
							move(SIZE_L, 1,r2->m_an-8, 1,r1->m_an-8);
					}

					de(r2);
					*/
				}

				//de(r1);
			}
			else
				ASSERT(0);	// destination of move must be MEM or TEMP
		}
		break;

	case T_Stm::T_EXP:
		{
			printf("expr\n");
			munchExpression(pFun, s->exp);
		}
		break;

	case T_Stm::T_JUMP:
		{
			printf("jump");
			if (s->jump.exp->kind == T_Exp::T_NAME)
			{
				pFun->emit(AS_Oper(m68k_Bcc(0, s->jump.exp->name.label), NULL, NULL, new AS_Targets(s->jump.labels)));

					/*
				s->jump.exp->name.label->m_branches.push_back(ftell(fileout));
				printf(" %d", s->jump.exp->name.label->m_n);

				short offset = 0;
				if (s->jump.exp->name.label->m_pos != -1)
				{
					offset = s->jump.exp->name.label->m_pos - ftell(fileout);
				}

				fput16(fileout, offset);
				*/
			}
			else
			{
				ASSERT(0);
				/*
				Temp_temp* r1 = munchExpression(pFun, s->jump.exp);

				jmp(2,0);	// TODO

				de(r1);
				*/
			}

			printf("\n");
		}
		break;

	case T_Stm::T_CJUMP:
		{
			printf("cjump");
			Temp_temp** r1 = munchExpression(pFun, s->cjump.left);

			/*
			if (s->cjump.right->kind == T_Exp::T_CONST && r1->m_dn != -1)
			{
				cmpi(s->cjump.right->const_int.int32Val, 2, 0,r1->m_dn);
			}
			else if (s->cjump.left->kind == T_Exp::T_CONST)
			{
				ASSERT(0);	// TODO
			}
			else
			*/
			{
				Temp_temp** r2 = munchExpression(pFun, s->cjump.right);

				pFun->emit(AS_Oper(m68k_CMP(m68k_DATAREG(r1), m68k_DATAREG(r2)), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
				//emit(AS_Oper("BCC", NULL, NULL));

			/*
				if ((pExpr->left->m_pType->get_sizeof() == 2) ||
					(pExpr->right->m_pType->get_sizeof() == 2))
				{
					((CCodeGen68*)this)->cmp(dreg0, CMPOP_DN_WORD, 0,dreg1);
				}
				else
					*/
				/*
				{
					ASSERT(r2->m_dn != -1);
					if (r1->m_dn != -1)
						cmp(r1->m_dn, CMPOP_DN_LONG, 0,r2->m_dn);
					else
						cmp(r1->m_an-8, CMPOP_AN_LONG, 0,r2->m_dn);
				}

				de(r2);
				*/
			}

			// Note, we emit the opposite op codes
			switch (s->cjump.relop)
			{
			case '==':
				{
				//bcc(COND_NE);//JOP_if_icmpne);
					pFun->emit(AS_Oper(m68k_Bcc(7, s->cjump.t), NULL, NULL,
						new AS_Targets(new Temp_labelList(s->cjump.t, new Temp_labelList(s->cjump.f, NULL)))));
				}
				break;
					/*
			case '!=':
				bcc(COND_EQ);//emit_op(JOP_if_icmpeq);
				break;
					
			case '<':
				bcc(COND_GE);
			//	emit_op(JOP_if_icmpgt);
				break;
					
			case '>':
				bcc(COND_LE);
			//	emit_op(JOP_if_icmplt);
				break;
					
			case '<=':
				bcc(COND_GT);	//emit_op(JOP_if_icmpge);
				break;
					
			case '>=':
				bcc(COND_LT);	//emit_op(JOP_if_icmple);
				break;
				*/

			default:
				ASSERT(0);
			}

			/*
			s->cjump.f->m_branches.push_back(ftell(fileout));
			printf(" t=%d, f=%d", s->cjump.t->m_n, s->cjump.f->m_n);

			short offset = 0;
			fput16(fileout, offset);

			de(r1);
			printf("\n");
			*/
		}
		break;

#if 0
	case T_Stm::T_ZERO:
		{
			Temp_temp* a = new Temp_temp;

#if 0
			int dreg = AllocDataRegister();
			a->m_an = AllocAddrRegister(a);
			moveq(s->zero.m_spOffset, dreg);
			add(2/*L ea+dn -> dn*/, dreg, 1,5);	// a5,dn
			move(SIZE_L, 0,dreg, 1,areg);
			FreeRegister(dreg);
#endif
			a->m_an = AllocAddrRegister(a);

			move(SIZE_W, 7,4, 1, a->m_an-8);
			fput16(fileout, s->zero.m_spOffset);

			adda(7, a->m_an-8, 1,5/*a5*/);

			int offset = s->zero.m_spOffset;
			int to = s->zero.m_spOffset + s->zero.m_length;

			if (offset & 1)
			{
				clr(0, 3, a->m_an-8);
				offset += 1;
			}

			if (offset < to)
			{
				if (offset & 2)
				{
					clr(1, 3, a->m_an-8);
					offset += 2;
				}

				while (offset < to)
				{
					if (to - offset == 1)
					{
						clr(0, 3, a->m_an-8);
						offset += 1;
					}
					else if (to - offset < 4)
					{
						clr(1, 3, a->m_an-8);
						offset += 2;
					}
					else
					{
						clr(2, 3, a->m_an-8);
						offset += 4;
					}
				}
			}
			de(a);
		}
		break;
#endif

	case T_Stm::T_LBRAC:
		{
			pFun->emit(AS_LBrac());
		}
		break;

	case T_Stm::T_RBRAC:
		{
			pFun->emit(AS_RBrac());
		}
		break;

	case T_Stm::T_LSYM:
		{
			pFun->emit(AS_LSym(s->declarator));
		}
		break;

	case T_Stm::T_NULL:
		break;

	default:
		ASSERT(0);
	}
}

void CCodeGen68k::munchStatement2(CFunctionCode* pFun, T_Stm* s)
{
	switch (s->kind)
	{
	case T_Stm::T_LABEL:
		{
			printf("label %d\n", s->label->m_n);
			pFun->emit(AS_Label(s->label));

#if 0
			ASSERT(s->label->m_pos == -1);
			s->label->m_pos = ftell(fileout);
			FlushLabel(s->label);
#endif
		}
		break;

	case T_Stm::T_MOVE:
		{
			printf("move\n");

			T_Exp* dst = s->move.left;
			T_Exp* src = s->move.right;
			if (dst->kind == T_Exp::T_MEM)
			{
				if (dst->mem.mem->kind == T_Exp::T_CONST)
				{
					if (src->kind == T_Exp::T_MEM && src->mem.mem->kind == T_Exp::T_CONST)
					{
						move(SIZE_L, 7,1, 7,1);

						ASSERT(0);
#if 0
						if (src->mem->const_int.reloc)
						{
							src->mem->const_int.reloc->VirtualAddress = ftell(fileout);
							pFun->AddRelocation(src->mem->const_int.reloc);
						}
#endif
						fput32(fileout, src->mem.mem->const_int.int32Val);

						ASSERT(0);
#if 0
						if (dst->mem->const_int.reloc)
						{
							dst->mem->const_int.reloc->VirtualAddress = ftell(fileout);
							pFun->AddRelocation(dst->mem->const_int.reloc);
						}
#endif
						fput32(fileout, dst->mem.mem->const_int.int32Val);
					}
					else
					{
						Temp_temp** r2 = munchExpression(pFun, src);

						ASSERT(0);
#if 0
						if (dst->mem->const_int.reloc)
						{
							dst->mem->const_int.reloc->VirtualAddress = ftell(fileout);
							pFun->AddRelocation(dst->mem->const_int.reloc);
						}
#endif
					}
				}
				else if (dst->mem.mem->kind == T_Exp::T_BINOP &&
							(*dst->mem.mem->binop.left->m_result)->getn() >= 8 &&
							dst->mem.mem->binop.op == '+' &&
							dst->mem.mem->binop.right->kind == T_Exp::T_CONST)
				{
					//T_Exp* e1 = ;
					//T_Exp* e2 = src;

					Temp_temp** r1 = munchExpression2(pFun, dst->mem.mem->binop.left);
					//Temp_temp* r2 = munchExpression(pFun, e2);

					/*
					if ()
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM((long)(src->const_int.int32Val & 0xffffffff)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), 4), NULL, new Temp_tempList(r1, NULL)));
						pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM((long)(src->const_int.int32Val >> 32)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val+4), 4), NULL, new Temp_tempList(r1, NULL)));
					}
					else
						*/
					if (src->kind == T_Exp::T_CONST || src->kind == T_Exp::T_CONST_DOUBLE)
					{
						if (dst->mem.size <= 4)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(src->const_int.int32Val), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), src->m_size), NULL, new Temp_tempList(r1, NULL)));
						}
						else if (dst->mem.size == 8)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM((long)(src->const_int.int32Val)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val+4), 4), NULL, new Temp_tempList(r1, NULL)));

							if ((src->const_int.int64Val >> 32) != 0)
								pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM((int32)(src->const_int.int64Val >> 32)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), 4), NULL, new Temp_tempList(r1, NULL)));
							else
								pFun->emit(AS_Oper(m68k_CLR(m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), 4), NULL, new Temp_tempList(r1, NULL)));
						}
						else
							ASSERT(0);

#if 0
						if (r1->m_an != -1)
						{
							if (dst->mem.size == 1)
							{
								move(SIZE_B, 7,4, 5,r1->m_an-8);
								ASSERT(0);
#if 0
								ASSERT(src->const_int.reloc == NULL);
#endif
								fput16(fileout, src->const_int.int32Val);
							}
							else if (dst->mem.size == 2)
							{
								move(SIZE_W, 7,4, 5,r1->m_an-8);
								ASSERT(0);
#if 0
								ASSERT(src->const_int.reloc == NULL);
#endif
								fput16(fileout, src->const_int.int32Val);
							}
							else if (dst->mem.size == 4)
							{
							//	move(SIZE_L, 7,4, 5,r1->m_an-8);
								move(SIZE_L, 7,4, 5,r1->m_n);
							//	ASSERT(0);
#if 0
								if (src->const_int.reloc)
								{
									src->const_int.reloc->VirtualAddress = ftell(fileout);
									pFun->AddRelocation(src->const_int.reloc);
								}
#endif
								fput32(fileout, src->const_int.int32Val);
							}
							else
								ASSERT(0);
						}
						else
						{
							Temp_temp* t = new Temp_temp;
							t->m_an = AllocAddrRegister(t);

							move(SIZE_L, 0,r1->m_dn, 1,t->m_an-8);

							if (dst->mem.size == 1)
							{
								ASSERT(0);
#if 0
								ASSERT(src->const_int.reloc == NULL);
#endif
								move(SIZE_B, 7,4, 5,t->m_an-8);
								fput16(fileout, src->const_int.int32Val);
							}
							else if (dst->mem.size == 2)
							{
								ASSERT(0);
#if 0
								ASSERT(src->const_int.reloc == NULL);
#endif
								move(SIZE_W, 7,4, 5,t->m_an-8);
								fput16(fileout, src->const_int.int32Val);
							}
							else if (dst->mem.size == 4)
							{
								move(SIZE_L, 7,4, 5,t->m_an-8);

								ASSERT(0);
#if 0
								if (src->const_int.reloc)
								{
									src->const_int.reloc->VirtualAddress = ftell(fileout);
									pFun->AddRelocation(src->const_int.reloc);
								}
#endif
								fput32(fileout, src->const_int.int32Val);
							}
							else
								ASSERT(0);

							de(t);

							/*
							Temp_temp* t = new Temp_temp;
							t->m_an = AllocAddrRegister(t);

							move(2, 0,r1->m_dn, 1,t->m_an-8);

							if (dst->mem_size == 1)
								move(SIZE_B, 0,r2->m_dn, 5,t->m_an-8);
							else if (dst->mem_size == 2)
								move(SIZE_W, 0,r2->m_dn, 5,t->m_an-8);
							else if (dst->mem_size == 4)
								move(SIZE_L, 0,r2->m_dn, 5,t->m_an-8);
							else
								ASSERT(0);

							de(t);
							*/
						}
#endif
					}
					else if (src->kind == T_Exp::T_MEM && src->mem.mem->kind == T_Exp::T_CONST)
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT(m68k_IMM(src->mem.mem->const_int.int32Val)), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), src->mem.size), NULL, new Temp_tempList(r1, NULL)));
					}
					else
					{
						Temp_temp** r2 = munchExpression2(pFun, src);

						if (dst->mem.size <= 4)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), dst->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
						}
						else if (dst->mem.size == 8)
						{
							pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val+4), 4), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
							pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), 4), NULL, new Temp_tempList(r1, new Temp_tempList((*r2)->m_second, NULL))));
						}

					//	pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT_DISPLACEMENT(r1, dst->mem.mem->binop.right->const_int.int32Val), r2->m_size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
					//	pFun->emit(AS_Oper(new m68kinstr, NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

#if 0
						if (r1->m_an != -1)
						{
							if (dst->mem.size == 1)
								move(SIZE_B, 0,r2->m_dn, 5,r1->m_an-8);
							else if (dst->mem.size == 2)
								move(SIZE_W, 0,r2->m_dn, 5,r1->m_an-8);
							else if (dst->mem.size == 4)
								move(SIZE_L, 0,r2->m_dn, 5,r1->m_an-8);
							else
								ASSERT(0);
						}
						else
						{
							Temp_temp* t = new Temp_temp;
							t->m_an = AllocAddrRegister(t);

							move(2, 0,r1->m_dn, 1,t->m_an-8);

							if (dst->mem.size == 1)
								move(SIZE_B, 0,r2->m_dn, 5,t->m_an-8);
							else if (dst->mem.size == 2)
								move(SIZE_W, 0,r2->m_dn, 5,t->m_an-8);
							else if (dst->mem.size == 4)
								move(SIZE_L, 0,r2->m_dn, 5,t->m_an-8);
							else
								ASSERT(0);

							de(t);
						}

						de(r2);
#endif
					}

#if 0
					fput16(fileout, dst->mem.mem->binop.right->const_int.int32Val);

					de(r1);
#endif
				}
				else if (dst->mem.mem->kind == T_Exp::T_BINOP &&
					dst->mem.mem->binop.op == '+' &&
					dst->mem.mem->binop.left->kind == T_Exp::T_CONST)
				{
					ASSERT(0);
					/*
					munchExpression(pFun, dst->mem->binop.right);
					printf("MOVE +%d", dst->mem->binop.left->tok.int32);
					*/
				}
				else //if (dst->mem.mem->kind == T_Exp::T_TEMP)
				{
					Temp_temp** r1 = munchExpression2(pFun, dst->mem.mem);

					//	(*r1)->m_an++;

					if (src->kind == T_Exp::T_CONST)
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(src->const_int.int32Val), m68k_INDIRECT(r1), dst->mem.size), NULL, new Temp_tempList(r1, NULL)));
					}
					else
					{
						Temp_temp** r2 = munchExpression2(pFun, src);

						pFun->emit(AS_Oper(m68k_MOVE(m68k_DATAREG(r2), m68k_INDIRECT(r1), dst->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
					}
				}
			}
			else if (dst->kind == T_Exp::T_TEMP)
			{
			//	T_Exp* e1 = dst;
			//	T_Exp* e2 = src;

				Temp_temp** r1 = munchExpression2(pFun, dst);
			//	Temp_temp** r1 = s->m_dst->temp;//munchExpression2(pFun, dst);

				if (src->kind == T_Exp::T_CONST)
				{
					if ((*r1)->getn() < 8 && src->const_int.int32Val >= -128 && src->const_int.int32Val <= 127)
					{
						pFun->emit(AS_Oper(m68k_MOVEQ(src->const_int.int32Val, r1), NULL, NULL));
					}
					else
					{
						pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(src->const_int.int32Val), m68k_DATAREG(r1), (*r1)->m_size), NULL, NULL));
					}

					if ((*r1)->m_second)
					{
						//r1->m_second->m_dn++;

						int32 high = src->const_int.int64Val >> 32;

						if (high == 0)
							pFun->emit(AS_Oper(m68k_CLR(m68k_DATAREG((*r1)->m_second), 4), new Temp_tempList((*r1)->m_second, NULL), NULL));
						else if (high == -1)
							pFun->emit(AS_Oper(m68k_MOVEQ(-1, (*r1)->m_second), new Temp_tempList((*r1)->m_second, NULL), NULL));
						else
							pFun->emit(AS_Oper(m68k_MOVE(m68k_IMM(high), m68k_DATAREG((*r1)->m_second), 4), new Temp_tempList((*r1)->m_second, NULL), NULL));

						/*
						if (src->const_int.int32Val < 0)
							pFun->emit(AS_Oper(m68k_MOVEQ(-1, r1->m_second), new Temp_tempList(r1->m_second, NULL), NULL));
						else
							pFun->emit(AS_Oper(m68k_CLR(m68k_DATAREG(r1->m_second), 4), new Temp_tempList(r1->m_second, NULL), NULL));
							*/
					}

					/*
					if (r1->m_dn != -1)
					{
						move(SIZE_L, 7,4, 0,r1->m_dn);
					}
					else
					{
						move(SIZE_L, 7,4, 1,r1->m_an-8);
					}

					ASSERT(0);
					*/
#if 0
					if (src->const_int.reloc)
					{
						src->const_int.reloc->VirtualAddress = ftell(fileout);
						pFun->AddRelocation(src->const_int.reloc);
					}
					fput32(fileout, src->const_int.int32Val);
#endif
				}
				else if (src->kind == T_Exp::T_MEM &&
					src->mem.mem->kind == T_Exp::T_CONST)
				{
					pFun->emit(AS_Oper(m68k_MOVE(m68k_INDIRECT(m68k_IMM(src->mem.mem->const_int.int32Val)), m68k_DATAREG(r1), (*r1)->m_size), new Temp_tempList(r1, NULL), NULL));

					/*
					if (r1->m_dn != -1)
					{
						move(SIZE_L, 7,1, 0,r1->m_dn);
					}
					else
					{
						move(SIZE_L, 7,1, 1,r1->m_an-8);
					}

					ASSERT(0);
					*/
#if 0
					if (src->mem->const_int.reloc)
					{
						src->mem->const_int.reloc->VirtualAddress = ftell(fileout);
						pFun->AddRelocation(src->mem->const_int.reloc);
					}
#endif
					//fput32(fileout, src->mem.mem->const_int.int32Val);
				}
				else
				{
					Temp_temp** r2 = munchExpression2(pFun, src);
					pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG(r2), m68k_DATAREG(r1), (*r1)->m_size), new Temp_tempList(r1, NULL), new Temp_tempList(r2, NULL)));
					if ((*r2)->m_second)
					{
						pFun->emit(AS_Move(m68k_MOVE(m68k_DATAREG((*r2)->m_second), m68k_DATAREG((*r1)->m_second), (*(*r1)->m_second)->m_size), new Temp_tempList((*r1)->m_second, NULL), new Temp_tempList((*r2)->m_second, NULL)));
					}

					/*
					if (r1->m_dn != -1)
					{
						move(SIZE_L, 0,r2->m_dn, 0,r1->m_dn);
					}
					else
					{
						if (r2->m_dn != -1)
							move(SIZE_L, 0,r2->m_dn, 1,r1->m_an-8);
						else
							move(SIZE_L, 1,r2->m_an-8, 1,r1->m_an-8);
					}

					de(r2);
					*/
				}

			//	de(r1);
			}
			else
				ASSERT(0);	// destination of move must be MEM or TEMP
		}
		break;

	case T_Stm::T_EXP:
		{
			printf("expr\n");
			munchExpression2(pFun, s->exp);
		}
		break;

	case T_Stm::T_JUMP:
		{
			printf("jump");
			if (s->jump.exp->kind == T_Exp::T_NAME)
			{
				pFun->emit(AS_Oper(m68k_Bcc(0, s->jump.exp->name.label), NULL, NULL, new AS_Targets(s->jump.labels)));
			}
			else
			{
				/*
				Temp_temp* r1 = munchExpression(pFun, s->jump.exp);

				jmp(2,0);	// TODO

				de(r1);
				*/
				ASSERT(0);
			}

			printf("\n");
		}
		break;

	case T_Stm::T_CJUMP:
		{
			printf("cjump");
			Temp_temp** r1 = munchExpression(pFun, s->cjump.left);

			/*
			if (s->cjump.right->kind == T_Exp::T_CONST && r1->m_dn != -1)
			{
				cmpi(s->cjump.right->const_int.int32Val, 2, 0,r1->m_dn);
			}
			else if (s->cjump.left->kind == T_Exp::T_CONST)
			{
				ASSERT(0);	// TODO
			}
			else
				*/
			{
				Temp_temp** r2 = munchExpression2(pFun, s->cjump.right);

				pFun->emit(AS_Oper(m68k_CMP(m68k_DATAREG(r1), m68k_DATAREG(r2)), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));

			/*
				if ((pExpr->left->m_pType->get_sizeof() == 2) ||
					(pExpr->right->m_pType->get_sizeof() == 2))
				{
					((CCodeGen68*)this)->cmp(dreg0, CMPOP_DN_WORD, 0,dreg1);
				}
				else
					*/
				/*
				{
					ASSERT(r2->m_dn != -1);
					if (r1->m_dn != -1)
						cmp(r1->m_dn, CMPOP_DN_LONG, 0,r2->m_dn);
					else
						cmp(r1->m_an-8, CMPOP_AN_LONG, 0,r2->m_dn);
				}

				de(r2);
				*/
			}

			// Note, we emit the opposite op codes
			switch (s->cjump.relop)
			{
			case '==':
				{
				//bcc(COND_NE);//JOP_if_icmpne);
					pFun->emit(AS_Oper(m68k_Bcc(7, s->cjump.t), NULL, NULL,
						new AS_Targets(new Temp_labelList(s->cjump.t, new Temp_labelList(s->cjump.f, NULL)))));
				}
				break;
			
				/*
			case '!=':
				bcc(COND_EQ);//emit_op(JOP_if_icmpeq);
				break;
					
			case '<':
				bcc(COND_GE);
			//	emit_op(JOP_if_icmpgt);
				break;
					
			case '>':
				bcc(COND_LE);
			//	emit_op(JOP_if_icmplt);
				break;
					
			case '<=':
				bcc(COND_GT);	//emit_op(JOP_if_icmpge);
				break;
					
			case '>=':
				bcc(COND_LT);	//emit_op(JOP_if_icmple);
				break;
				*/

			default:
				ASSERT(0);
			}

			/*
			s->cjump.f->m_branches.push_back(ftell(fileout));
			printf(" t=%d, f=%d", s->cjump.t->m_n, s->cjump.f->m_n);

			short offset = 0;
			fput16(fileout, offset);

			de(r1);
			printf("\n");
			*/
		}
		break;

#if 0
	case T_Stm::T_ZERO:
		{
			Temp_temp* a = new Temp_temp;

#if 0
			int dreg = AllocDataRegister();
			a->m_an = AllocAddrRegister(a);
			moveq(s->zero.m_spOffset, dreg);
			add(2/*L ea+dn -> dn*/, dreg, 1,5);	// a5,dn
			move(SIZE_L, 0,dreg, 1,areg);
			FreeRegister(dreg);
#endif
			a->m_an = AllocAddrRegister(a);

			move(SIZE_W, 7,4, 1, a->m_an-8);
			fput16(fileout, s->zero.m_spOffset);

			adda(7, a->m_an-8, 1,5/*a5*/);

			int offset = s->zero.m_spOffset;
			int to = s->zero.m_spOffset + s->zero.m_length;

			if (offset & 1)
			{
				clr(0, 3, a->m_an-8);
				offset += 1;
			}

			if (offset < to)
			{
				if (offset & 2)
				{
					clr(1, 3, a->m_an-8);
					offset += 2;
				}

				while (offset < to)
				{
					if (to - offset == 1)
					{
						clr(0, 3, a->m_an-8);
						offset += 1;
					}
					else if (to - offset < 4)
					{
						clr(1, 3, a->m_an-8);
						offset += 2;
					}
					else
					{
						clr(2, 3, a->m_an-8);
						offset += 4;
					}
				}
			}
			de(a);
		}
		break;
#endif

	case T_Stm::T_LBRAC:
		{
			pFun->emit(AS_LBrac());
		}
		break;

	case T_Stm::T_RBRAC:
		{
			pFun->emit(AS_RBrac());
		}
		break;

	case T_Stm::T_LSYM:
		{
			pFun->emit(AS_LSym(s->declarator));
		}
		break;

	case T_Stm::T_NULL:
		break;

	default:
		ASSERT(0);
	}
}

// virtual
void CCodeGen68k::WriteStatement(CFunctionCode* pFun, T_Stm* s)
{
	munchStatement(pFun, s);
}

// virtual
void CCodeGen68k::WriteStatement2(CFunctionCode* pFun, T_Stm* s)
{
	munchStatement2(pFun, s);
}

//}	// cpp
}
