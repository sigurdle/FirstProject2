#include "stdafx.h"
#include <stdio.h>
#include "x86assem.h"

#include "ir.h"

namespace System
{

//namespace cpp
//{

x86instr* x86_Jcc(int8 rel8)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_Jcc;
	p->data8 = rel8;
	return p;
}

x86instr* x86_Jcc(long rel32)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_Jcc;
	p->integer = rel32;
	return p;
}

x86instr* x86_Jcc(uint8 op, Temp_label* label)
{
	ASSERT(label);

	x86instr* p = new x86instr;
	p->kind = x86instr::K_Jcc;
	p->jcc.op = op;
	p->jcc.label = label;
	return p;
}

x86instr* x86_SETcc(int op, x86addr* dst)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_SETcc;
	p->setcc.op = op;
	p->setcc.dst = dst;
	return p;
}

x86instr* x86_PUSH(x86addr* push)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_PUSH;
	p->op0 = push;
	return p;
}

x86instr* x86_POP(x86addr* pop)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_POP;
	p->op0 = pop;
	return p;
}

x86instr* x86_MOV(x86addr* dst, x86addr* src, int w)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_MOV;
	p->mov.dst = dst;
	p->mov.src = src;
	p->mov.w = w > 1;
	p->size_prefix = w == 2;
	return p;
}

x86instr* x86_IMUL(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_IMUL;
	p->imul.dst = dst;
	p->imul.src = src;
	return p;
}

x86instr* x86_LEA(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_LEA;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_ADD(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_ADD;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_ADC(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_ADC;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_SBB(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_SBB;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_XCHG(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_XCHG;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_CMP(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_CMP;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_SUB(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_SUB;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_AND(x86addr* dst, x86addr* src, int w)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_AND;
	p->mov.dst = dst;
	p->mov.src = src;
	p->mov.w = w > 1;
	p->size_prefix = w == 2;
	return p;
}

x86instr* x86_OR(x86addr* dst, x86addr* src, int w)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_OR;
	p->mov.dst = dst;
	p->mov.src = src;
	p->mov.w = w > 1;
	p->size_prefix = w == 2;
	return p;
}

x86instr* x86_XOR(x86addr* dst, x86addr* src, int w)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_XOR;
	p->mov.dst = dst;
	p->mov.src = src;
	p->mov.w = w > 1;
	p->size_prefix = w == 2;
	return p;
}

x86instr* x86_ROR(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_ROR;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_DIV(x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_DIV;
	p->op0 = src;
	return p;
}

x86instr* x86_IDIV(x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_IDIV;
	p->op0 = src;
	return p;
}

x86instr* x86_SHL(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_SHL;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_SHR(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_SHR;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_TEST(x86addr* dst, x86addr* src, int w)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_TEST;
	p->mov.dst = dst;
	p->mov.src = src;
	p->mov.w = w > 1;
	p->size_prefix = w == 2;
	return p;
}

x86instr* x86_MOVZX(x86addr* dst, x86addr* src, int w)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_MOVZX;
	p->mov.dst = dst;
	p->mov.src = src;
	p->mov.w = w > 1;
	p->size_prefix = w == 2;
	return p;
}

x86instr* x86_MOVSX(x86addr* dst, x86addr* src, int w)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_MOVSX;
	p->mov.dst = dst;
	p->mov.src = src;
	p->mov.w = w > 1;
	p->size_prefix = w == 2;
	return p;
}

x86instr* x86_SAR(x86addr* dst, x86addr* src)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_SAR;
	p->mov.dst = dst;
	p->mov.src = src;
	return p;
}

x86instr* x86_NEG(x86addr* neg)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_NEG;
	p->op0 = neg;
	return p;
}

x86instr* x86_NOT(x86addr* not_)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_NOT;
	p->op0 = not_;
	return p;
}

x86instr* x86_CALL(x86addr* op0)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_CALL;
	p->op0 = op0;
	return p;
}

x86instr* x86_JMP(x86addr* op0)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_JMP;
	p->op0 = op0;
	return p;
}

x86instr* x86_INC(x86addr* addr)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_INC;
	p->op0 = addr;
	return p;
}

x86instr* x86_DEC(x86addr* addr)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_DEC;
	p->op0 = addr;
	return p;
}

x86instr* x86_LEAVE()
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_LEAVE;
	return p;
}

x86instr* x86_RET()
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_RET;
	return p;
}

x86instr* x86_RET_IMM16(short imm16)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_RET_IMM16;
	p->integer = imm16;
	return p;
}

x86instr* x86_REP(x86instr* instr)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_REP;
	p->instr = instr;
	return p;
}

x86addr* x86_NAME(Temp_label* label)
{
	x86addr* p = new x86addr;
	p->kind = x86addr::K_NAME;
	p->name = label;
	return p;
}

x86instr* x86_INT(int8 imm8)
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_INT;
	p->data8 = imm8;
	return p;
}

x86instr* x86_NOP()	// Really same as XCHG eax,eax, but this carries more semantics
{
	x86instr* p = new x86instr;
	p->kind = x86instr::K_NOP;
	return p;
}

x86addr* x86_IMM(T_Exp* pTExpr)
{
	if (pTExpr->kind == T_Exp::T_CONST)
	{
		x86addr* p = new x86addr;
		p->kind = x86addr::K_IMM;
		p->imm32 = (long)pTExpr->const_int.int32Val;
		return p;
	}
	else if (pTExpr->kind == T_Exp::T_NAME)
	{
		x86addr* p = new x86addr;
		p->kind = x86addr::K_NAME;
		p->name = pTExpr->name.label;
		return p;
	}

	ASSERT(0);
	return NULL;
}

x86addr* x86_IMM(long imm32)
{
	x86addr* p = new x86addr;
	p->kind = x86addr::K_IMM;
	p->imm32 = imm32;
	return p;
}

x86addr* x86_REG(uint8 reg)
{
	x86addr* p = new x86addr;
	p->kind = x86addr::K_REG;
	p->reg = reg;
	return p;
}

x86addr* x86_TEMP(Temp_temp* temp)
{
	x86addr* p = new x86addr;
	p->kind = x86addr::K_TEMP;
	p->temp = temp;
	return p;
}

x86addr* x86_RM(Temp_temp* temp, int displacement)
{
	x86addr* p = new x86addr;
	p->kind = x86addr::K_RM;
	p->rm.temp = temp;
	p->rm.displacement = displacement;
	return p;
}

x86addr* x86_BRACKET(x86addr* addr)
{
	x86addr* p = new x86addr;
	p->kind = x86addr::K_BRACKET;
	p->bracket = addr;
	return p;
}

x86addr* x86_BRACKET_DISPLACE(x86addr* addr, long displacement)
{
	x86addr* p = new x86addr;
	p->kind = x86addr::K_BRACKET_DISPLACE;
	p->bracket_displace.addr = addr;
	p->bracket_displace.displacement = displacement;
	return p;
}

//}	// cpp

}
