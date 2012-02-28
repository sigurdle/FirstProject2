#include "stdafx.h"
//#include <stdio.h>
//#include <string>
//#include <sstream>

#include "m68kassem.h"
#include "ir.h"
#include "codegen.h"

namespace System
{
using namespace std;

void fput8(FILE* fp, uint8 v);
void fput16(FILE* fp, uint16 v);
void fput32(FILE* fp, uint32 v);

Temp_temp* eax = new Temp_temp("eax", 0);
Temp_temp* ecx = new Temp_temp("ecx", 1);
Temp_temp* edx = new Temp_temp("edx", 2);
Temp_temp* ebx = new Temp_temp("ebx", 3);
Temp_temp* esp = new Temp_temp("esp", 4);
Temp_temp* ebp = new Temp_temp("ebp", 5);

Temp_temp* d0 = new Temp_temp("d0", 0);
Temp_temp* d1 = new Temp_temp("d1", 1);
Temp_temp* d2 = new Temp_temp("d2", 2);
Temp_temp* d3 = new Temp_temp("d3", 3);
Temp_temp* d4 = new Temp_temp("d4", 4);
Temp_temp* d5 = new Temp_temp("d5", 5);
Temp_temp* d6 = new Temp_temp("d6", 6);
Temp_temp* d7 = new Temp_temp("d7", 7);
Temp_temp* a0 = new Temp_temp("a0", 8+0);
Temp_temp* a1 = new Temp_temp("a1", 8+1);
Temp_temp* a2 = new Temp_temp("a2", 8+2);
Temp_temp* a3 = new Temp_temp("a3", 8+3);
Temp_temp* a4 = new Temp_temp("a4", 8+4);
Temp_temp* a5 = new Temp_temp("a5", 8+5);
Temp_temp* a6 = new Temp_temp("a6", 8+6);
Temp_temp* a7 = new Temp_temp("a7", 8+7);

Temp_temp* regs[16] =
{
	d0,
	d1,
	d2,
	d3,
	d4,
	d5,
	d6,
	d7,
	a0,
	a1,
	a2,
	a3,
	a4,
	a5,
	a6,
	a7,
};

Temp_temp** dregs = regs;/*[8] =
{
	d0,
	d1,
	d2,
	d3,
	d4,
	d5,
	d6,
	d7,
};
*/
Temp_temp** aregs = regs + 8;/*[8] =
{
	a0,
	a1,
	a2,
	a3,
	a4,
	a5,
	a6,
	a7,
};
*/

//namespace cpp
//{

m68kinstr* m68k_MOVE(m68koperand* src, m68koperand* dst, int size)
{
	ASSERT(dst->kind != m68koperand::K_IMM);

	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_MOVE;
	p->two.src = src;
	p->two.dst = dst;
	p->two.size = size;
	return p;
}

m68kinstr* m68k_MOVEM()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_MOVEM;
	return p;
}

m68kinstr* m68k_MOVEQ(int8 data, Temp_temp** dreg)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_MOVEQ;
	p->moveq.data = data;
	p->moveq.dreg = dreg;
	return p;
}

CodeCompExt m68kinstr* m68k_SUBQ(int8 data, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_SUBQ;
	p->subq.data = data;
	p->subq.dst = dst;
	return p;
}

m68kinstr* m68k_DBcc(uint8 condition, Temp_temp** dn, Temp_label* displacement)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_DBcc;
	p->dbcc.condition = condition;
	p->dbcc.dn = dn;
	p->dbcc.displacement = displacement;
	return p;
}

m68kinstr* m68k_LEA(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_LEA;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_PEA(m68koperand* src)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_PEA;
	p->op = src;
	return p;
}

m68kinstr* m68k_CHK(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_CHK;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_EXG()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_EXG;
	return p;
}

m68kinstr* m68k_EXT(Temp_temp** dn, uint8 opmode)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_EXT;
	p->ext.dn = dn;
	p->ext.opmode = opmode;
	return p;
}

m68kinstr* m68k_SWAP()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_SWAP;
	return p;
}

m68kinstr* m68k_NEG(m68koperand* op)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_NEG;
	p->op = op;
	return p;
}

m68kinstr* m68k_NEGX(m68koperand* op)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_NEGX;
	p->op = op;
	return p;
}

m68kinstr* m68k_CLR(m68koperand* op, int size)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_CLR;
	p->clr.operand = op;
	p->clr.size = size;
	return p;
}

m68kinstr* m68k_TRAP(uint8 trap)
{
	ASSERT(trap < 16);

	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_TRAP;
	p->trap = trap;
	return p;
}

m68kinstr* m68k_LINK(m68koperand* reg, long offset)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_LINK;
	p->link.reg = reg;
	p->link.offset = offset;
	return p;
}

m68kinstr* m68k_UNLK(m68koperand* reg)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_UNLK;
	p->op = reg;
	return p;
}

m68kinstr* m68k_ASR(m68koperand* reg)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_ASR;
	p->op = reg;
	return p;
}

CodeCompExt m68kinstr* m68k_LSHIFT(bool dr, m68koperand* src, m68koperand* dst, int size)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_LSHIFT;
	p->lshift.src = src;
	p->lshift.dst = dst;
	p->lshift.dr = dr;
	return p;
}

m68kinstr* m68k_ROXR(m68koperand* reg)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_ROXR;
	p->op = reg;
	return p;
}

m68kinstr* m68k_ADD(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_ADD;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_SUBI(long src, m68koperand* dst, int size)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_SUBI;
	p->subi.src = src;
	p->subi.dst = dst;
	return p;
}

m68kinstr* m68k_ADDX(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_ADDX;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_SUB(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_SUB;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_SUBX(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_SUBX;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_MULS(m68koperand* src, Temp_temp** dl_reg, Temp_temp** dh_reg)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_MULS;
	p->muls.src = src;
	p->muls.dl_reg = dl_reg;
	p->muls.dh_reg = dh_reg;
	return p;
}

CodeCompExt m68kinstr* m68k_DIVS(m68koperand* src, Temp_temp** q_reg, Temp_temp** r_reg)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_DIVS;
	p->divs.src = src;
	p->divs.q_reg = q_reg;
	p->divs.r_reg = r_reg;
	return p;
}

m68kinstr* m68k_MULU(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_MULU;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_RTS()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_RTS;
	return p;
}

m68kinstr* m68k_RTR()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_RTR;
	return p;
}

m68kinstr* m68k_RTE()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_RTE;
	return p;
}

m68kinstr* m68k_OR(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_OR;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_EOR(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_EOR;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_AND(m68koperand* src, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_AND;
	p->two.src = src;
	p->two.dst = dst;
	return p;
}

m68kinstr* m68k_ANDI(long src, m68koperand* dst, int size)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_ANDI;
	p->andi.src = src;
	p->andi.dst = dst;
	p->andi.size = size;
	return p;
}

m68kinstr* m68k_CMP(m68koperand* src0, m68koperand* src1)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_CMP;
	p->two.dst = src0;
	p->two.src = src1;
	return p;
}

/*
m68kinstr* m68k_TEST(m68koperand* reg)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_TEST;
	p->op = reg;
	return p;
}
*/

m68kinstr* m68k_JSR(m68koperand* op)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_JSR;
	p->op = op;
	return p;
}

m68kinstr* m68k_BSR(short offset)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_BSR;
	p->uint_16 = offset;
	return p;
}

m68kinstr* m68k_JMP(m68koperand* op)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_JMP;
	p->op = op;
	return p;
}

m68kinstr* m68k_TST(m68koperand* op)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_TST;
	p->op = op;
	return p;
}

m68kinstr* m68k_BTST()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_BTST;
	return p;
}

m68kinstr* m68k_BCHG()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_BCHG;
	return p;
}

m68kinstr* m68k_BCLR()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_BCLR;
	return p;
}

m68kinstr* m68k_BSET()
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_BSET;
	return p;
}

m68kinstr* m68k_Bcc(uint8 condition, Temp_label* displacement)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_Bcc;
	p->bcc.condition = condition;
	p->bcc.displacement = displacement;
	return p;
}

m68kinstr* m68k_SET(uint8 condition, m68koperand* dst)
{
	m68kinstr* p = new m68kinstr;
	p->kind = m68kinstr::K_SET;
	p->set.condition = condition;
	p->set.dst = dst;
	return p;
}

m68koperand* m68k_IMM(long imm32)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_IMM;
	p->imm32 = imm32;
	return p;
}

m68koperand* m68k_NAME(Temp_label* name)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_NAME;
	p->name = name;
	return p;
}

m68koperand* m68k_DATAREG(uint8 reg)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_DATAREG;
	p->reg = reg;
	return p;
}

m68koperand* m68k_DATAREG(Temp_temp** temp)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_DATAREG_TEMP;
	p->temp = temp;
	return p;
}

m68koperand* m68k_INDIRECT(Temp_temp** temp)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_INDIRECT_TEMP;
	p->temp = temp;
	return p;
}

m68koperand* m68k_ADDRREG(uint8 reg)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_ADDRREG;
	p->reg = reg;
	return p;
}

m68koperand* m68k_INDIRECT(m68koperand* op)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_INDIRECT;
	p->indirect= op;
	return p;
}

m68koperand* m68k_INDIRECT_REG(uint8 reg)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_INDIRECT_REG;
	p->reg = reg;
	return p;
}

m68koperand* m68k_INDIRECT_POSTINC(uint8 areg)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_INDIRECT_POSTINC;
	p->reg = areg;
	return p;
}

m68koperand* m68k_INDIRECT_PREDEC(Temp_temp** areg)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_INDIRECT_PREDEC;
	p->temp = areg;
	return p;
}

m68koperand* m68k_INDIRECT_DISPLACEMENT(Temp_temp** areg, short disp16)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_INDIRECT_DISPLACEMENT;
	p->displacement.areg = areg;
	p->displacement.disp16 = disp16;
	return p;
}

m68koperand* m68k_INDIRECT_INDEX(uint8 disp, Temp_temp** reg, Temp_temp** ext_reg, uint8 ext_factor)
{
	m68koperand* p = new m68koperand;
	p->kind = m68koperand::K_INDIRECT_INDEX;
	p->index.disp = disp;
	p->index.reg = reg;
	p->index.ext_reg = ext_reg;
	p->index.ext_factor = ext_factor;
	return p;
}

m68kinstr* unknown_opcode(void)
{
//	msptr += sprintf(msptr, "dc.w\t%4X\t;\"%.4s\"", opcode, &opcode);

	return NULL;
}

char SizeChar[] =
{
	'B', 'W', 'L'
};

const char *CondTest[] =
{
	"T",	// True
	"F",	// False
	"HI",	// High
	"LS",	// Low or Same
	"CC",	// Carry Clear
	"CS",	// Carry Set
	"NE",	// Not Equal
	"EQ",	// Equal
	"VC",	// Overflow Clear
	"VS",	// Overflow Set
	"PL",	// Plus
	"MI",	// Minus
	"GE",	// Greater or Equal
	"LT",	// Less Than
	"GT",	// Greater Than
	"LE"	// Less or Equal
};

const char *BitStr[] =
{
	"TST",
	"CHG",
	"CLR",
	"SET"
};

/*************************************************************************************

 Fetch a word from the code stream

*************************************************************************************/

uint16 fetch_w(m68kContext* c)
{
	uint16 d = (*c->pc++) << 8;
	d |= (*c->pc++);
	return d;
}

/*************************************************************************************

 Fetch a long word from the code stream

*************************************************************************************/

uint32 fetch_l(m68kContext* c)
{
	uint32 d = (*c->pc++) << 24;
	d |= (*c->pc++) << 16;
	d |= (*c->pc++) << 8;
	d |= (*c->pc++);
	return d;
}

// Do immediate
m68koperand* do_imm(m68kContext* c, uint8 size)
{
	if (size == 2)	// long
	{
		//msptr += sprintf(msptr, "#$%lX", fetch_l());
	//	msptr += sprintf(msptr, "#%ld", );
		return m68k_IMM(fetch_l(c));
	}
	else	// byte/word
	{
		//msptr += sprintf(msptr, "#$%X", fetch_w());
	//	msptr += sprintf(msptr, "#%d", fetch_w(c));
		return m68k_IMM(fetch_w(c));
	}
}

// Do effective address (six bits of ea) size is optional
// 5  4  3 | 2  1  0
//   Mode  | Register
m68koperand* do_ea(m68kContext* c, uint8 mode, uint8 reg, uint8 size)
{
	LONG	disp;

	switch (mode)
	{
	case 0:	// Data Register Direct
		//msptr += sprintf(msptr, "D%d", reg);
		return m68k_DATAREG(reg);

		/************************************************************************************/
	case 1:	// Address Register Direct
		//msptr += sprintf(msptr, "A%d", reg);
		return m68k_ADDRREG(reg);
	
		/************************************************************************************/
	case 2:	// Address Register Indirect
//		msptr += sprintf(msptr, "(A%d)", reg);
		return m68k_INDIRECT_REG(reg);
		break;
		
	case 3:	// Address Register Indirect with Postincrement
	//	msptr += sprintf(msptr, "(A%d)+", reg);
		return m68k_INDIRECT_POSTINC(reg);
		break;
		
	case 4:	// Address Register Indirect with Predecrement
		//msptr += sprintf(msptr, "-(A%d)", reg);
		{
	//	Temp_temp** t = new Temp_temp*;
	//	*t = regs[8+reg];
		return m68k_INDIRECT_PREDEC(&regs[8+reg]);
		}
		break;
		
	case 5:	// Address Register Indirect with Displacement
		//msptr += sprintf(msptr, "%d(A%d)", (short)fetch_w(c), reg);
		{
	//	Temp_temp** t = new Temp_temp*;
	//	*t = ;
		return m68k_INDIRECT_DISPLACEMENT(&aregs[reg], (short)fetch_w(c));
		}
		/************************************************************************************/
	case 6:	// Address Register Indirect with Index
		{
			uint16	extw = fetch_w(c);
			
			if (!(extw & 0x0100))	// no 8bit? Brief format
			{
				//struct {unsigned	type:1, reg:3, isize:1, factor:2, pad:1, disp:8;}	ext;
				//*(uint16 *)(&ext) = extw;
				uint8 ext_disp = extw & 0xFF;
				uint8 ext_factor = (extw >> 9) & 0x3;
				uint8 ext_isize = (extw >> 11) & 0x1;
				uint8 ext_reg = (extw >> 12) & 0x7;
				uint8 ext_type = (extw >> 15) & 0x1;
				
			//	if (ext_factor == 0)
			//	Temp_temp** t = new Temp_temp*;
			//	*t = 
					m68k_INDIRECT_INDEX(ext_disp, &aregs[reg], &dregs[ext_reg], ext_factor);//msptr += sprintf(msptr, "$%02X(A%d,D%d.%c)", ext_disp, reg, ext_reg, SizeChar[ext_isize+1]);
			//	else
			//		m68k_INDIRECT_INDEX(ext_disp, reg, ext_reg);;//msptr += sprintf(msptr, "$%02X(A%d,D%d.%c*%d)", ext_disp, reg, ext_reg, SizeChar[ext_isize+1], 1<<ext_factor);
			}
			else	// Full format (68020)
			{
				uint32	disp0 = 0L;
				uint32	disp1 = 0L;
				uint16	index_type;		// Post/Pre Index
			
			//	ATLASSERT(0);
			//	struct {unsigned	type:1, reg:3, isize:1, factor:2, pad:1, bsup:1, isup:1, bsize:2, pad1:1, isel:3;}	ext;
			//	*(uint16 *)(&ext) = extw;
				uint8 extisel = extw & 0x7;
				uint8 extbsize = (extw>>4) & 0x3;
				uint8 extisup = (extw>>6) & 0x1;
				uint8 extbsup = (extw>>7) & 0x1;
				uint8 extfactor = (extw>>9) & 0x3;
				uint8 extisize = (extw>>11) & 0x1;
				uint8 extreg = (extw>>12) & 0x7;
				uint8 exttype = (extw>>15) & 0x1;
				
				// Get base displacement
				if (extbsize == 2)	// Word base displacement
					disp0 = fetch_w(c);
				else if (extbsize == 3)	// Long base displacement
					disp0 = fetch_l(c);
				
				// Get outer displacement
				if ((extisel == 2) || ((extisel == 6) && !extisup))	// Word displacement
					disp1 = fetch_w(c);
				else if ((extisel == 3) || ((extisel == 7) && !extisup))	// Long displacement
					disp1 = fetch_l(c);
				
				// Get Index type (Post/Pre)
				if (extisel & 0x4)
					index_type = 0;	// Pre-index
				else
					index_type = 1;	// Post-index
				
				if (index_type)	// Post-index
				{
				;//	msptr += sprintf(msptr, "([$%lX,A%d,D%d.%c*%d],$%lX)", disp0, reg, extreg, SizeChar[extisize+1], 1<<extfactor, disp1);
				}
				else	// Pre-index
				{
				;//	msptr += sprintf(msptr, "([$%lX,A%d],D%d.%c*%d,$%lX)", disp0, reg, extreg, SizeChar[extisize+1], 1<<extfactor, disp1);
				}

				// TODO
				return m68k_INDIRECT_REG(reg);
		//		ASSERT(0);
			}
		}
		break;
		/************************************************************************************/
	case 7:
		switch (reg)
		{
		case 0:	// Absolute Short
		//	msptr += sprintf(msptr, "$%d.W", fetch_w(c));
			return m68k_INDIRECT(m68k_IMM(fetch_w(c)));
			break;
			
		case 1:	// Absolute Long
		//	msptr += sprintf(msptr, "$%ld.L", fetch_l(c));
			return m68k_INDIRECT(m68k_IMM(fetch_l(c)));
			break;
			/************************************************************************************/
		case 2:	// Program Counter Indirect with Displacement
			disp = fetch_w(c);
			
#if 0
			symnode = FindSymbol(counter+disp-2);
			
			if (symnode)
			{
				msptr += sprintf(msptr, "%.*s(PC)", (*symnode->SymPtr)<<2, symnode->SymPtr+1);
			}
			else
#endif
			{
			;//	msptr += sprintf(msptr, "$%X(PC)", disp);
			// TODO
			ASSERT(0);
			}
			break;
			/************************************************************************************/
		case 3:	// Program Counter Indirect with Index
#if 0
			msptr += sprintf(msptr, "$%X(PC,D%d.W)", stream[0], stream[1]);
#endif
			fetch_w(c);
			
			/*
			{
			struct {unsigned	type:1, reg:3, size:1, factor:2, pad:1, disp:8;}	ext;
			*(uint16 *)(&ext) = fetch_w();
			
			 if (ext.factor == 0)
			 msptr += sprintf(msptr, "$%02X(PC,D%d.%c)", ext.disp, reg, ext.reg, SizeChar[ext.size+1]);
			 else
			 msptr += sprintf(msptr, "$%02X(PC,D%d.%c*%d)", ext.disp, reg, ext.reg, SizeChar[ext.size+1], 1<<ext.factor);
			 }
			*/
			break;
			/************************************************************************************/
		case 4:	// Immediate
			if (size == 2)	// Long
			{
				return m68k_IMM((long)fetch_l(c));
			//	msptr += sprintf(msptr, "#%ld", (long)fetch_l(c));
			}
			else	// Byte/Word
			{
				return m68k_IMM((short)fetch_w(c));
			//	msptr += sprintf(msptr, "#%d", (short)fetch_w(c));
			}
			break;
		}
		break;
	}

	return NULL;
}

#define ADM_0		(1<<0)
#define ADM_1		(1<<1)
#define ADM_2		(1<<2)
#define ADM_3		(1<<3)
#define ADM_4		(1<<4)
#define ADM_5		(1<<5)
#define ADM_6		(1<<6)
#define ADM_7		(1<<7)
#define ADM_8		(1<<8)
#define ADM_9		(1<<9)
#define ADM_10		(1<<10)
#define ADM_11		(1<<11)

#define ADM_ALL	0x0FFF

bool sup_ea(uint8 mode, uint8 reg, short adrmodes)
{
	if (mode < 7)
	{
		if (adrmodes & (1<<mode)) return true;
	}
	else
	{
		if (adrmodes & (1<<(7+reg))) return true;
	}

	return false;
}

// Bit Manipulation/MOVEP/Immediate
m68kinstr* codemap00(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	if (opcode == 0x003C)	// ORI ,CCR	(done)
	{
	//	msptr += sprintf(msptr, "ORI.B\t");
		do_imm(c, 0);
	//	msptr += sprintf(msptr, ",CCR");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x007C)	// ORI ,SR	(done)
	{
	//	msptr += sprintf(msptr, "ORI.W\t");
		do_imm(c, 1);
	//	msptr += sprintf(msptr, ",SR");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x023C)	// ANDI ,CCR	(done)
	{
	//	msptr += sprintf(msptr, "ANDI.B\t");
		do_imm(c, 0);
	//	msptr += sprintf(msptr, ",CCR");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x027C)	// ANDI ,SR	(done)
	{
	//	msptr += sprintf(msptr, "ANDI.W\t");
		do_imm(c, 1);
	//	msptr += sprintf(msptr, ",SR");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x0A3E)	// EORI ,CCR	(done)
	{
	//	msptr += sprintf(msptr, "EORI.B\t");
		do_imm(c, 0);
	//	msptr += sprintf(msptr, ",CCR");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x0A7C)	// EORI ,SR	(done)
	{
	//	msptr += sprintf(msptr, "EORI.W\t");
		do_imm(c, 1);
	//	msptr += sprintf(msptr, ",SR");
		ASSERT(0);
		return NULL;
	}

	if ((opcode & 0xFF00) == 0x0000)	// ORI	(done)
	{
	//			ATLASSERT(0);
	//	struct {unsigned	pad:8, size:2, mode: 3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 opreg = opcode & 0x7;
		uint8 opmode = (opcode>>3) & 0x7;
		uint8 opsize = (opcode>>6) & 0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "ORI.%c\t", SizeChar[opsize]);
			m68koperand* src = do_imm(c, opsize);
		//	msptr += sprintf(msptr, ",");
			m68koperand* dst = do_ea(c, opmode, opreg, opsize);
			return m68k_OR(src, dst);
		}
	}

	if ((opcode & 0xFF00) == 0x0200)	// ANDI	(done)
	{
	//			ATLASSERT(0);
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode&0x7;
		uint8 op_mode = (opcode>>3)&0x7;
		uint8 op_size = (opcode>>6)&0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "ANDI.%c\t", SizeChar[op.size]);
			m68koperand* src = do_imm(c, op_size);
		//	msptr += sprintf(msptr, ",");
			m68koperand* dst = do_ea(c, op_mode, op_reg, op_size);
			return m68k_AND(src, dst);
		}
	}

	if ((opcode & 0xFF00) == 0x0400)	// SUBI	(done)
	{
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 opreg = opcode & 0x7;
		uint8 opmode = (opcode>>3) & 0x7;
		uint8 opsize = (opcode>>6) & 0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "SUBI.%c\t", SizeChar[opsize]);
			m68koperand* src = do_imm(c, opsize);
		//	msptr += sprintf(msptr, ",");
			m68koperand* dst = do_ea(c, opmode, opreg, opsize);
			return m68k_SUB(src, dst);
		}
	}

	if ((opcode & 0xFF00) == 0x0600)	// ADDI	(done)
	{
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_size = (opcode>>6) & 0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "ADDI.%c\t", SizeChar[op_size]);
			m68koperand* src = do_imm(c, op_size);
		//	msptr += sprintf(msptr, ",");
			m68koperand* dst = do_ea(c, op_mode, op_reg, op_size);
			return m68k_ADD(src, dst);
		}
	}

	if ((opcode & 0xFF00) == 0x0A00)	// EORI	(done)
	{
		//		ATLASSERT(0);
		//struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		//*(uint16 *)(&op) = opcode;
		uint8 opreg = opcode & 0x7;
		uint8 opmode = (opcode>>3) & 0x7;
		uint8 opsize = (opcode>>6) & 0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "EORI.%c\t", SizeChar[opsize]);
			do_imm(c, opsize);
		//	msptr += sprintf(msptr, ",");
			do_ea(c, opmode, opreg, opsize);
			ASSERT(0);
			return NULL;
		}
	}

	if ((opcode & 0xFF00) == 0x0C00)	// CMPI	(done)
	{
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_size = (opcode>>6) & 0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "CMPI.%c\t", SizeChar[op_size]);
			m68koperand* src0 = do_imm(c, op_size);
		//	msptr += sprintf(msptr, ",");
			m68koperand* src1 = do_ea(c, op_mode, op_reg, op_size);
			return m68k_CMP(src0, src1);
		}
	}

	if ((opcode & 0xF038) == 0x0008)	// MOVEP
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, dreg:3, t:1, opmode:2, pad1:3, areg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 opareg = opcode & 0x7;
		uint8 opmode = (opcode>>6) & 0x3;
		uint8 opt = (opcode>>8) & 0x1;
		uint8 opdreg = (opcode>>9) & 0x7;

		if (opt == 1)
		{
			uint16	size = (opmode & 1)? 2: 1;
			uint16	disp;

		//	msptr += sprintf(msptr, "MOVEP.%c\t", SizeChar[size]);

			disp = fetch_w(c);

			if (opmode & 2)	// From register to memory
			{
			;//	msptr += sprintf(msptr, "D%d,($%X,A%d)", opdreg, disp, opareg);
			}
			else	// From memory to register
			{
			;//	msptr += sprintf(msptr, "($%X,A%d),D%d", disp, opareg, opdreg);
			}

			ASSERT(0);
			return NULL;
		}
	}

	if ((opcode & 0xFF00) == 0x0800)	// Static Bit
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad:8, type:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode&0x7;
		uint8 op_mode = (opcode>>3)&0x7;
		uint8 op_type = (opcode>>6)&0x3;

	//	msptr += sprintf(msptr, "B%s\t", BitStr[op_type]);
#if 0
		msptr += sprintf(msptr, "#%d,", *(uint16 *)stream);
#endif
		fetch_l(c);
		do_ea(c, op_mode, op_reg, 1);
		switch (op_type)
		{
		case 0: return m68k_BTST();
		case 1: return m68k_BCHG();
		case 2: return m68k_BCLR();
		case 3: return m68k_BSET();
		}
		return NULL;
	}

	if ((opcode & 0xF100) == 0x0100)	// Dynamic Bit
	{
	//	struct {unsigned	pad0:4, dreg:3, pad1:1, type:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_type = (opcode>>6) & 0x3;
		uint8 op_dreg = (opcode>>9) & 0x7;

	//	msptr += sprintf(msptr, "B%s\t", BitStr[op_type]);
	//	msptr += sprintf(msptr, "D%d,", op_dreg);
		;

		m68kinstr* p = new m68kinstr;
		p->kind = m68kinstr::K_BSET;	// TODO
		p->op = do_ea(c, op_mode, op_reg,-1);
		return p;

	//	return m68k_(src0, src1);
	//	ASSERT(0);
	//	return NULL;
	}

	return unknown_opcode();
}

// Move Byte
m68kinstr* codemap01(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

//	ATLASSERT(0);
//	struct {unsigned	pad:4, destreg:3, destmode:3, srcmode:3, srcreg:3;}	op;
//	*(uint16 *)(&op) = opcode;
	int size = (opcode>>12) & 3;
	uint8 opsrcreg = opcode & 0x7;
	uint8 opsrcmode = (opcode>>3) & 0x7;
	uint8 opdestmode = (opcode>>6) & 0x7;
	uint8 opdestreg = (opcode>>9) & 0x7;

// All addressing modes are allowed for source

	if (sup_ea(opdestmode, opdestreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
	{
	//	msptr += sprintf(msptr, "MOVE.B\t");
		m68koperand* src = do_ea(c, opsrcmode, opsrcreg, 0);
	//	msptr += sprintf(msptr, ",");
		m68koperand* dst = do_ea(c, opdestmode, opdestreg, 0);
		return m68k_MOVE(src, dst, size==1? 1: size==3? 2: 4);
	}

	return unknown_opcode();
}

// Move Long
m68kinstr* codemap02(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

//	struct {unsigned	pad:4, destreg:3, destmode:3, srcmode:3, srcreg:3;}	op;
//	*(uint16 *)(&op) = opcode;
	int size = (opcode>>12) & 3;
	uint8 srcreg = opcode & 0x7;
	uint8 srcmode = (opcode >> 3) & 0x7;
	uint8 destmode = (opcode >> 6) & 0x7;
	uint8 destreg = (opcode >> 9) & 0x7;

// All addressing modes are allowed for source

	if (destmode == 1)	// If Address Register Direct - MOVEA
	{
	//	msptr += sprintf(msptr, "MOVEA.L\t");
		m68koperand* src = do_ea(c, srcmode, srcreg, 2);
	//	msptr += sprintf(msptr, ",");
		m68koperand* dst = do_ea(c, destmode, destreg, 2);
		return m68k_MOVE(src, dst, size == 3? 2: 4);
	}
	else
	{
		if (sup_ea(destmode, destreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "MOVE.L\t");
			m68koperand* src = do_ea(c, srcmode, srcreg, 2);
		//	msptr += sprintf(msptr, ",");
			m68koperand* dst = do_ea(c, destmode, destreg, 2);
			return m68k_MOVE(src, dst, size == 1? 1: size==3? 2: 4);
		}
	}

	return unknown_opcode();
}

// Move Word
m68kinstr* codemap03(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	ASSERT(0);
#if 0

//	struct {unsigned	pad:4, destreg:3, destmode:3, srcmode:3, srcreg:3;}	op;
//	*(uint16 *)(&op) = opcode;
	uint8 srcreg = opcode & 0x7;
	uint8 srcmode = (opcode >> 3) & 0x7;
	uint8 destmode = (opcode >> 6) & 0x7;
	uint8 destreg = (opcode >> 9) & 0x7;

// All addressing modes are allowed for source

	if (destmode == 1)	// If Address Register Direct - MOVEA
	{
	//	msptr += sprintf(msptr, "MOVEA.W\t");
		m68koperand* src = do_ea(c, srcmode, srcreg, 3);
	//	msptr += sprintf(msptr, ",");
		m68koperand* dst = do_ea(c, destmode, destreg, 3);
		return m68k_MOVE(src, dst);
	}
	else
	{
		if (sup_ea(destmode, destreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "MOVE.W\t");
			m68koperand* src = do_ea(c, srcmode, srcreg, 3);
		//	msptr += sprintf(msptr, ",");
			m68koperand* dst = do_ea(c, destmode, destreg, 3);
			return m68k_MOVE(src, dst);
		}
	}

#endif
	return unknown_opcode();
}

// Miscellaneous
// + 68020 (MULS/MULU Long)
m68kinstr* codemap04(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	if (opcode == 0x4E75)	// RTS
	{
	//	msptr += sprintf(msptr, "RTS");
		return m68k_RTS();
	}

	if (opcode == 0x4E77)	// RTR
	{
	//	msptr += sprintf(msptr, "RTR");
		return m68k_RTR();
	}

	if (opcode == 0x4E73)	// RTE
	{
	//	msptr += sprintf(msptr, "RTE");
		return m68k_RTE();
	}

	if (opcode == 0x4E74)	// RTD	(MC68010/MC68012)
	{
	//	msptr += sprintf(msptr, "RTD");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x4E71)	// NOP
	{
	//	msptr += sprintf(msptr, "NOP");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x4E72)	// STOP
	{
	//	msptr += sprintf(msptr, "STOP");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x4E70)	// RESET
	{
	//	msptr += sprintf(msptr, "RESET");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x4E76)	// TRAPV
	{
//		msptr += sprintf(msptr, "TRAPV");
		ASSERT(0);
		return NULL;
	}

	if (opcode == 0x4AFC)	// ILLEGAL
	{
//		msptr += sprintf(msptr, "ILLEGAL");
		ASSERT(0);
		return NULL;
	}

	if ((opcode & 0xFFF8) == 0x4840)	// SWAP	(done)
	{
		/*
		ATLASSERT(0);
		struct {unsigned	pad:13, dreg:3;}	op;
		*(uint16 *)(&op) = opcode;
		*/
		uint8 op_dreg = (opcode)&0x7;

//		msptr += sprintf(msptr, "SWAP\tD%d", op_dreg);
		return m68k_SWAP();
	}

	if ((opcode & 0xFFF8) == 0x4848)	// BKPT (MC68010/MC68012) (done)
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad:13, bkpt:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_bkpt = (opcode)&0x7;

	//	msptr += sprintf(msptr, "BKPT\t#%d", op_bkpt);
		ASSERT(0);
		return NULL;
	}

	if ((opcode & 0xFFF8) == 0x4E50)	// LINK (done)
	{
		//struct {unsigned	pad:13, areg:3;}	op;
		//*(uint16 *)(&op) = opcode;
		uint8 areg = opcode & 0x7;

	//	msptr += sprintf(msptr, "LINK\tA%d,%d", areg, (short)fetch_w(c));
		return m68k_LINK(m68k_ADDRREG(areg), (short)fetch_w(c));
	}

	if ((opcode & 0xFFF8) == 0x4E58)	// UNLK (done)
	{
	//	struct {unsigned	pad:13, areg:3;}	op;
//		*(uint16 *)(&op) = opcode;
		uint8 areg = opcode & 0x7;

	//	msptr += sprintf(msptr, "UNLK\tA%d", areg);
		return m68k_UNLK(m68k_ADDRREG(areg));
	}

	if ((opcode & 0xFFC0) == 0x4E80)	// JSR	(done)
	{
	//	struct {unsigned	pad:10, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 reg = opcode & 0x7;
		uint8 mode = (opcode >> 3) & 0x7;

		if (sup_ea(mode, reg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_4|ADM_11)))
		{
		//	msptr += sprintf(msptr, "JSR\t");
			return m68k_JSR(do_ea(c, mode, reg,-1));
		}
	}

	if ((opcode & 0xFFC0) == 0x4EC0)	// JMP	(done)
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad:10, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_4|ADM_11)))
		{
		//	msptr += sprintf(msptr, "JMP\t");
			return m68k_JMP(do_ea(c, op_mode, op_reg,-1));
		}
	}

	if ((opcode & 0xFFC0) == 0x4AC0)	// TAS	(done)
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad:10, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "TAS\t");
			do_ea(c, op_mode, op_reg, 0);
			ASSERT(0);
			return NULL;
		}
	}

	if ((opcode & 0xFFC0) == 0x4840)	// PEA	(done)
	{
	//	struct {unsigned	pad:10, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_4|ADM_11)))
		{
		//	msptr += sprintf(msptr, "PEA\t");
			do_ea(c, op_mode, op_reg, 2);
			return m68k_PEA(NULL);
		}
	}

	if ((opcode & 0xFFC0) == 0x4800)	// NBCD	(done)
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad:10, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "NBCD\t");
			do_ea(c, op_mode, op_reg, 0);
			ASSERT(0);
			return NULL;
		}
	}

	if ((opcode & 0xFFC0) == 0x4800)	// MOVE to SR	(done)
	{
	//	struct {unsigned	pad:10, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~ADM_1))
		{
		//	msptr += sprintf(msptr, "MOVE\t");
			do_ea(c, op_mode, op_reg, 1);
		//	msptr += sprintf(msptr, ",SR");
			ASSERT(0);
			return NULL;
		}
	}

	if ((opcode & 0xFE38) == 0x4800)	// EXT (done)
	{
	//	struct {unsigned	pad0:7, type:3, pad1:3, dreg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_dreg = opcode & 0x7;
		uint8 op_type = (opcode>>6) & 0x7;

	//	msptr += sprintf(msptr, "EXT.%c\t", SizeChar[op_type-1]);
	//	msptr += sprintf(msptr, "D%d", op_dreg);
		return m68k_EXT(NULL, op_type);
	}

	if ((opcode & 0xFB80) == 0x4880)	// MOVEM (done)
	{
	//	struct {unsigned	pad0:5, dir:1, pad1:3, size:1, mode:3, reg:3;}	op;
	//	struct {unsigned	pad0:5, dir:1, pad1:3, size:1, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = ENDIANWORD(opcode);
		uint8 opreg = opcode & 0x7;
		uint8 opmode = (opcode>>3)&0x7;
		uint8 opsize = (opcode>>6)&0x1;
		uint8 opdir = (opcode>>10)&0x1;

		if (((opdir == 0) && (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_9|ADM_10|ADM_11)))) ||
			((opdir == 1) && (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_0|ADM_1|ADM_4|ADM_11)))))
		{
			uint16	regmask = fetch_w(c);

		//	msptr += sprintf(msptr, "MOVEM.%c\t", SizeChar[opsize+1]);

			if (opdir == 1)	// Memory to Register
			{
				do_ea(c, opmode, opreg, opsize);
			//	msptr += sprintf(msptr, ",");

				bool bPrev = false;

				for (int n = 0; n < 16; n++)
				{
					int i = n;

					if (i < 8)
					{
						if (regmask & (1<<i))
						{
						//	if (bPrev) msptr += sprintf(msptr, ",");
						//	msptr += sprintf(msptr, "D%d", i);
							bPrev = true;
						}
					}
					else
					{
						if (regmask & (1<<i))
						{
						//	if (bPrev) msptr += sprintf(msptr, ",");
						//	msptr += sprintf(msptr, "A%d", i-8);
							bPrev = true;
						}
					}
				}
			}
			else	// Register to Memory
			{
				bool bPrev = false;

				for (int n = 0; n < 16; n++)
				{
					int i = n;

					if (i < 8)
					{
						if (regmask & (1<<(15-i)))
						{
						//	if (bPrev) msptr += sprintf(msptr, ",");
						//	msptr += sprintf(msptr, "D%d", i);
							bPrev = true;
						}
					}
					else
					{
						if (regmask & (1<<(15-i)))
						{
						//	if (bPrev) msptr += sprintf(msptr, ",");
						//	msptr += sprintf(msptr, "A%d", i-8);
							bPrev = true;
						}
					}
				}

			//	msptr += sprintf(msptr, ",");
				do_ea(c, opmode, opreg, opsize);
			}

/*
			if (op.mode == 4);	// Predecrement

			if (op.dir == 0)	// Register to Memory
			{
				WORD	i;
				WORD	last = 0xffff;

				for (i = 0; i < 16; i++)
				{
					if (1<<i & regmask)
					{
						BOOL	printreg = TRUE;

#if 0
						if (last = 0xffff)	// First bit that is set
						{
						}
						else if (last == i-1)	// The previous bit was also set
						{
						}
						else
						{
							msptr += sprintf(msptr, "-");
						}
#endif

						if (printreg)
						{
							if (i < 8)
								msptr += sprintf(msptr, "D%d", i);
							else
								msptr += sprintf(msptr, "A%d", i-8);
						}

						last = i;
					}
				}
			}
			else	// Memory to Register
			{
			}
*/
			return m68k_MOVEM();
		}
	}

	if ((opcode & 0xFF00) == 0x4A00)	// TST	(done)
	{
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_size = (opcode>>6) & 0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "TST.%c\t",SizeChar[op_size]);
			return m68k_TST(do_ea(c, op_mode, op_reg, op_size));
		}
	}

	if ((opcode & 0xFF00) == 0x4600)	// NOT (done)
	{
			//	ATLASSERT(0);
		//struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		//*(uint16 *)(&op) = opcode;
		uint8 opreg = opcode & 0x7;
		uint8 opmode = (opcode>>3) & 0x7;
		uint8 opsize = (opcode>>6) & 0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "NOT.%c\t", SizeChar[opsize]);
			do_ea(c, opmode, opreg, opsize);
			return NULL;
		}
	}

	if ((opcode & 0xFF00) == 0x4400)	// NEG	(done)
	{
//		struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
//		*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_size = (opcode>>6) & 0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "NEG.%c\t", SizeChar[op_size]);
			do_ea(c, op_mode, op_reg, op_size);
			return m68k_NEG(NULL);
		}
	}

	if ((opcode & 0x41C0) == 0x41C0)	// LEA	(done)
	{
	//			ATLASSERT(0);
	//	struct {unsigned	pad0:4, areg:3, pad1:3, mode:3, reg:3;}	op;
		//*(uint16 *)(&op) = opcode;
		uint8 opreg = opcode&0x7;
		uint8 opmode = (opcode>>3)&0x7;
		uint8 opareg = (opcode>>9)&0x7;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_4|ADM_9)))
		{
		//	msptr += sprintf(msptr, "LEA\t");
		//	;
		//	msptr += sprintf(msptr, ",A%d", opareg);
			return m68k_LEA(do_ea(c, opmode, opreg, 2), m68k_ADDRREG(opareg));
		}
	}

	if ((opcode & 0xFF00) == 0x4200)	// CLR	(done)
	{
		//struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		//*(uint16 *)(&op) = opcode;
		uint8 opreg = opcode & 0x7;
		uint8 opmode = (opcode>>3)&0x7;
		uint8 opsize = (opcode>>6)&0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "CLR.%c\t", SizeChar[opsize]);
			return m68k_CLR(do_ea(c, opmode, opreg, opsize), 1<<opsize);
		}
	}

	if ((opcode & 0xFF00) == 0x4000)	// NEGX	(done)
	{
		/*
				ATLASSERT(0);
		struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		*(uint16 *)(&op) = opcode;
		*/
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;
		uint8 op_size = (opcode>>6)&0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "NEGX.%c\t", SizeChar[op_size]);
			do_ea(c, op_mode, op_reg, op_size);
			return m68k_NEGX(NULL);
		}
	}

	if ((opcode & 0xF040) == 0x4000)	// CHK	(done)
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, dreg:3, size:2, pad1:1, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;
		uint8 op_size = (opcode>>7)&0x3;
		uint8 op_dreg = (opcode>>9)&0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ADM_1))
		{
			uint16	size = (op_size == 3)? 1: 2;

		//	msptr += sprintf(msptr, "CHK.%c\t", SizeChar[size]);
		//	;
		//	msptr += sprintf(msptr, ",D%d", op_dreg);
			return m68k_CHK(do_ea(c, op_mode, op_reg, size), m68k_DATAREG(op_dreg));
		}
	}

	if ((opcode & 0xFFF0) == 0x4E40)	// TRAP
	{
		return m68k_TRAP(opcode & 0xF);
	}

	return unknown_opcode();
}

// ADDQ/SUBQ/Scc/DBcc
m68kinstr* codemap05(m68kContext* c)
{
	ASSERT(0);

#if 0
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	if ((opcode & 0xF0F8) == 0x50C8)	// DBcc	(done)
	{
	//	struct {unsigned	pad0:4, condition:4, pad1:5, dreg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_dreg = (opcode)&0x7;
		uint8 op_condition = (opcode>>8)&0x15;

	//	msptr += sprintf(msptr, "DB%s\t", CondTest[op_condition]);
	//	msptr += sprintf(msptr, "D%d,", op_dreg);

	//	msptr += sprintf(msptr, "%d", (uint16)fetch_w(c));

		return m68k_DBcc(op_condition, dregs[op_dreg], NULL);
	}

	if ((opcode & 0xFFC0) == 0x50C0)	// Scc	(done)
	{
	//	struct {unsigned	pad0:4, condition:4, pad1:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;
		uint8 op_condition = (opcode>>8)&0x15;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
		//	msptr += sprintf(msptr, "S%s\t", CondTest[op_condition]);
			do_ea(c, op_mode, op_reg,-1);
			return NULL;
		}
	}

	if ((opcode & 0xF100) == 0x5000)	// ADDQ	(done)
	{
		//struct {unsigned	pad0:4, data:3, pad1:1, size:2, mode: 3, reg:3;}	op;
		//*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_size = (opcode>>6) & 0x3;
		uint8 op_data = (opcode>>9) & 0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_9|ADM_10|ADM_11)))
		{
			uint16	data = (op_data)? op_data: 8;

		//	msptr += sprintf(msptr, "ADDQ.%c\t#%d,", SizeChar[op_size], data);
			m68koperand* dst = do_ea(c, op_mode, op_reg, op_size);
			return m68k_ADD(m68k_IMM(data), dst);
		}
	}

	if ((opcode & 0xF100) == 0x5100)	// SUBQ	(done)
	{
	//	struct {unsigned	pad0:4, data:3, pad1:1, size:2, mode: 3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_size = (opcode>>6) & 0x3;
		uint8 op_data = (opcode>>9) & 0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_9|ADM_10|ADM_11)))
		{
			uint16	data = (op_data)? op_data: 8;

		//	msptr += sprintf(msptr, "SUBQ.%c\t#%d,", SizeChar[op_size], data);
			m68koperand* dst = do_ea(c, op_mode, op_reg, op_size);
			return m68k_SUB(m68k_IMM(data), dst);
		}
	}
#endif

	return unknown_opcode();
}

// Bcc/BSR
m68kinstr* codemap06(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	if ((opcode & 0xFF00) == 0x6100)	// BSR	(done)
	{
//		struct {unsigned	pad:8, disp8:8;}	op;
//		*(uint16 *)(&op) = opcode;
		char op_disp8 = opcode & 0xFF;

		;//msptr += sprintf(msptr, "BSR.%c\t", SizeChar[(op_disp8)? 0: 1]);

		short offset;
		if (op_disp8 == 0)	// Allows for 16bit displacement in extension word
		{
			offset = fetch_w(c);

			;//msptr += sprintf(msptr, "%d", disp16);
		}
		else
		{
			offset = op_disp8;
			;//msptr += sprintf(msptr, "%d", op_disp8);
		}

		return m68k_BSR(offset);
	}

	if ((opcode & 0xF000) == 0x6000)	// Bcc/BRA	(done)
	{
		//struct {unsigned	pad0:4, condition:4; signed disp8:8;}	op;
		//*(uint16 *)(&op) = opcode;
		char op_disp8 = opcode & 0xFF;
		uint8 op_condition = (opcode >> 8) & 0xF;

		if (op_condition != 1)	// Always False (not available for this instruction)
		{
			if (op_condition == 0)	// Always True
				;//msptr += sprintf(msptr, "BRA.%c\t", SizeChar[(op_disp8)? 0: 1]);
			else
				;//msptr += sprintf(msptr, "B%s.%c\t", CondTest[op_condition], SizeChar[(op_disp8)? 0: 1]);

			if (op_disp8 == 0)	// Allows for 16bit displacement in extension word
			{
				short	disp16 = fetch_w(c);

#if 0
				msptr += sprintf(msptr, "%d", counter-2 + disp16);
#endif
			}
			else
			{
#if 0
				msptr += sprintf(msptr, "%d", counter + op_disp8);
#endif
			}

			return m68k_Bcc(op_condition, NULL);
		}
	}

	return unknown_opcode();
}

// MOVEQ
m68kinstr* codemap07(m68kContext* c)	// (done)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	//struct {unsigned	pad0:4, dreg:3, pad1:1, data:8;}	op;
	int8 data = opcode&0xFF;
	uint8 dreg = (opcode>>9)&0x7;

//	msptr += sprintf(msptr, "MOVEQ\t#%d,D%d", data, dreg);

	return m68k_MOVEQ(data, &regs[dreg]);
}

// OR/DIV/SBCD
m68kinstr* codemap08(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	if ((opcode & 0xF1F0) == 0x8100)	// SBCD
	{
	}

	if ((opcode & 0xF0C0) == 0x80C0)	// DIVU/DIVS Word
	{
		//struct {unsigned	pad0:4, dreg:3, type:1, pad1:2, mode:3, reg:3;}	op;
		//*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_type = (opcode>>8) & 0x1;
		uint8 op_dreg = (opcode>>9) & 0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~ADM_1))
		{
			if (op_type)
				;//msptr += sprintf(msptr, "DIVS.W\t");
			else
				;//msptr += sprintf(msptr, "DIVU.W\t");

			do_ea(c, op_mode, op_reg, 1);
			;//msptr += sprintf(msptr, ",D%d", op_dreg);
			return NULL;
		}
	}

	if	(1) // OR	(done)
	{
	//	struct {unsigned	pad:4, dreg:3, t:1, size:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 opreg = opcode & 0x7;
		uint8 opmode = (opcode>>3) & 0x7;
		uint8 opsize = (opcode>>6) & 0x3;
		uint8 opt = (opcode>>8) & 0x1;
		uint8 opdreg = (opcode>>9) & 0x7;

		if (((opt == 0) && (sup_ea(opmode, opreg, ADM_ALL & ~ADM_1))) ||
			((opt == 1) && (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_0|ADM_1|ADM_9|ADM_10|ADM_11)))))
		{
		//	msptr += sprintf(msptr, "OR.%c\t", SizeChar[opsize]);

			m68koperand* src;
			m68koperand* dst;

			if (opt)	// Dn,<ea>
			{
			//	msptr += sprintf(msptr, "D%d,", opdreg);
				src = m68k_DATAREG(opdreg);
				dst = do_ea(c, opmode, opreg, opsize);
			}
			else	// <ea>,Dn
			{
				src = do_ea(c, opmode, opreg, opsize);
				dst = m68k_DATAREG(opdreg);
				//msptr += sprintf(msptr, ",D%d", opdreg);
			}

			return m68k_OR(src, dst);
		}
	}

	return unknown_opcode();
}

// SUB/SUBX
m68kinstr* codemap09(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

//	struct {unsigned	pad0:4, rx:3, pad1:1, size:2, pad2:2, rm:1, ry:3;}	op;
//	*(uint16 *)(&op) = opcode;

	uint8 op_size = (opcode>>6) & 0x3;
	if (((opcode & 0xF130) == 0x9100) && (op_size < 3))	// SUBX
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, rx:3, pad1:1, size:2, pad2:2, rm:1, ry:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_rx = opcode & 0x7;
		uint8 op_rm = (opcode>>3) & 0x1;
		uint8 op_ry = (opcode>>9) & 0x7;

		;//msptr += sprintf(msptr, "SUBX.%c\t", SizeChar[op_size]);

		if (op_rm)
			;//msptr += sprintf(msptr, "-(A%d),-(A%d)", op_ry, op_rx);
		else
			;//msptr += sprintf(msptr, "D%d,D%d", op_ry, op_rx);

		return NULL;
	}

	if (1)	// SUB/SUBA
	{
	//	struct {unsigned	pad:4, dareg:3, opmode:3, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_opmode = (opcode>>6) & 0x7;
		uint8 op_dareg = (opcode>>9) & 0x7;

		m68koperand* src;
		m68koperand* dst;

		if ((op_opmode == 3) || (op_opmode == 7))	// SUBA
		{
			uint16	size = ((op_opmode == 3)? 1: 2);

		//	msptr += sprintf(msptr, "SUBA.%c\t", SizeChar[size]);
			src = do_ea(c, op_mode, op_reg, size);
		//	msptr += sprintf(msptr, ",A%d", op_dareg);
			dst = m68k_ADDRREG(op_reg);
		}
		else	// SUB
		{
		//	struct {unsigned	pad:4, dreg:3, t:1, size:2, mode:3, reg:3;}	op;
		//	*(uint16 *)(&op) = opcode;
			uint8 op_size = (opcode>>6) & 0x3;
			uint8 op_t = (opcode>>8) & 0x1;

		//	msptr += sprintf(msptr, "SUB.%c\t", SizeChar[op_size]);

			if (op_t)	// <Dn>,<ea>
			{
			//	msptr += sprintf(msptr, "D%d,", op_dareg);
				src = m68k_DATAREG(op_dareg);
				dst = do_ea(c, op_mode, op_reg, op_size);
			}
			else	// <ea>,<Dn>
			{
				src = do_ea(c, op_mode, op_reg, op_size);
				dst = m68k_DATAREG(op_dareg);
			//	msptr += sprintf(msptr, ",D%d", op_dareg);
			}
		}

		return m68k_SUB(src, dst);
	}

	unknown_opcode();
}

// (Unnassigned, Reserved)
m68kinstr* codemap10(m68kContext* c)
{
	return unknown_opcode();
}

// CMP/EOR
m68kinstr* codemap11(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	if ((opcode & 0xF138) == 0xB108)	// CMPM
	{
	//	struct {unsigned	pad0:4, ax:3, pad1:1, size:2, pad2:3, ay:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_ay = (opcode)&0x7;
		uint8 op_size = (opcode>>6)&0x3;
		uint8 op_ax = (opcode>>9)&0x7;

	//	msptr += sprintf(msptr, "CMPM.%c\t(A%d)+,(A%d)+", SizeChar[op_size], op_ay, op_ax);
		return NULL;
	}

	if ((opcode & 0xF000) == 0xB000)	// CMP/CMPA/EOR
	{
	//	struct {unsigned	pad:4, adreg:3, opmode:3, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 oreg = opcode & 0x7;
		uint8 omode = (opcode>>3) & 0x7;
		uint8 oopmode = (opcode>>6) & 0x7;
		uint8 oadreg = (opcode>>9) & 0x7;

		if ((oopmode >= 4) && (oopmode <= 6))	// EOR
		{
			uint16	size = oopmode-4;

		//	msptr += sprintf(msptr, "EOR.%c\t", SizeChar[size]);
		//	msptr += sprintf(msptr, "D%d,", oadreg);
			m68koperand* dst = do_ea(c, omode, oreg, size);

			return m68k_EOR(m68k_DATAREG(oadreg), dst);
		}
		else
		{
			if (oopmode < 3)	// CMP
			{
			//	msptr += sprintf(msptr, "CMP.%c\t", SizeChar[oopmode]);
				m68koperand* dst = do_ea(c, omode, oreg, oopmode);
			//	msptr += sprintf(msptr, ",D%d", oadreg);
				return m68k_CMP(m68k_DATAREG(oadreg), dst);
			}
			else	// CMPA
			{
				uint16	size = (oopmode == 3)? 1: 2;

			//	msptr += sprintf(msptr, "CMPA.%c\t", SizeChar[size]);
				m68koperand* dst = do_ea(c, omode, oreg, size);
			//	msptr += sprintf(msptr, ",A%d", oadreg);
				return m68k_CMP(m68k_ADDRREG(oadreg), dst);
			}
		}

		return NULL;
	}

	return unknown_opcode();
}

// AND/MUL/ABCD/EXG
m68kinstr* codemap12(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	if ((opcode & 0xF1F0) == 0xC100)	// ABCD
	{
	//	struct {unsigned	pad0:4, rx:3, pad1:5, rm:1, ry:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_ry = (opcode)&0x7;
		uint8 op_rm = (opcode>>3)&0x1;
		uint8 op_rx = (opcode>>9)&0x7;

	//	msptr += sprintf(msptr, "ABCD\t");

		if (op_rm)	// -(Ay),-(Ax)
		;//	msptr += sprintf(msptr, "-(A%d),-(A%d)", op_ry, op_rx);
		else	// Dy,Dx
		;//	msptr += sprintf(msptr, "D%d,D%d", op_ry, op_rx);

		return NULL;
	}

	if ((opcode & 0xF100) == 0xC100)	// EXG
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, rx:3, pad1:1, opmode:5, ry:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_ry = opcode & 0x7;
		uint8 op_opmode = (opcode>>3) & 0x1f;
		uint8 op_rx = (opcode>>9) & 0x7;

		if (op_opmode == 0x8)	// exg data registers
		{
		//	msptr += sprintf(msptr, "EXG\t");
		//	msptr += sprintf(msptr, "D%d,D%d", op_rx, op_ry);
			return m68k_EXG();
		}
		else if (op_opmode == 0x9)	// exg address registers
		{
		//	msptr += sprintf(msptr, "EXG\t");
		//	msptr += sprintf(msptr, "A%d,A%d", op_rx, op_ry);
			return m68k_EXG();
		}
		else if (op_opmode == 0x11)	// exg data register and address register
		{
		//	msptr += sprintf(msptr, "EXG\t");
		//	msptr += sprintf(msptr, "D%d,A%d", op_rx, op_ry);
			return m68k_EXG();
		}
	}

	if ((opcode & 0xF0C0) == 0xC0C0)	// MULU/MULS Word
	{
//		ATLASSERT(0);
//		struct {unsigned	pad0:4, dreg:3, type:1, pad1:2, mode:3, reg:3;}	op;
//		*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_type = (opcode>>8) & 0x1;
		uint8 op_dreg = (opcode>>9) & 0x7;

		if (op_type)
			;//msptr += sprintf(msptr, "MULS\t");	else msptr += sprintf(msptr, "MULU\t");
		do_ea(c, op_mode, op_reg, 1);	// Word
	//	msptr += sprintf(msptr, ",D%d", op_dreg);

		return NULL;
	}

	if ((opcode & 0xF000) == 0xC000)	// AND
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad:4, dreg:3, t:1, size:2, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;
		uint8 op_size = (opcode>>6)&0x3;
		uint8 op_t = (opcode>>8)&0x1;
		uint8 op_dreg = (opcode>>9)&0x7;

	//	msptr += sprintf(msptr, "AND.%c\t", SizeChar[op_size]);

		m68koperand* src;
		m68koperand* dst;

		if (op_t)	// Dn,<ea>
		{
			//msptr += sprintf(msptr, "D%d,", op.dreg);
			src = m68k_DATAREG(op_dreg);
			dst = do_ea(c, op_mode, op_reg, op_size);
		}
		else	// <ea>,Dn
		{
			src = do_ea(c, op_mode, op_reg, op_size);
			//msptr += sprintf(msptr, ",D%d", op.dreg);
			dst = m68k_DATAREG(op_dreg);
		}
		return m68k_AND(src, dst);
	}

	return unknown_opcode();
}

// ADD/ADDX
m68kinstr* codemap13(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	//	struct {unsigned	pad0:4, rx:3, pad1:1, size:2, pad2:2, rm:1, ry:3;}	op;
//	*(uint16 *)(&op) = opcode;
	uint8 op_size = (opcode>>6) & 0x3;

	if (((opcode & 0xF130) == 0xD100) && (op_size < 3))	// ADDX
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, rx:3, pad1:1, size:2, pad2:2, rm:1, ry:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_ry = opcode & 0x7;
		uint8 op_rm = (opcode>>3) & 0x1;
		uint8 op_size = (opcode>>6) & 0x3;
		uint8 op_rx = (opcode>>9) & 0x7;

	//	msptr += sprintf(msptr, "ADDX.%c\t", SizeChar[op_size]);

		if (op_rm)
		;//	msptr += sprintf(msptr, "-(A%d),-(A%d)", op_ry, op_rx);
		else
		;//	msptr += sprintf(msptr, "D%d,D%d", op_ry, op_rx);

		return NULL;
	}
	else	// ADD/ADDA
	{
	//	struct {unsigned	pad:4, dareg:3, opmode:3, mode:3, reg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_reg = opcode & 0x7;
		uint8 op_mode = (opcode>>3) & 0x7;
		uint8 op_opmode = (opcode>>6) & 0x7;
		uint8 op_dareg = (opcode>>9) & 0x7;

		m68koperand* src;
		m68koperand* dst;

		if ((op_opmode == 3) || (op_opmode == 7))	// ADDA
		{
			uint16	size = ((op_opmode == 3)? 1: 2);

		//	msptr += sprintf(msptr, "ADDA.%c\t", SizeChar[size]);
			src = do_ea(c, op_mode, op_reg, size);
		//	msptr += sprintf(msptr, ",A%d", op_dareg);
			dst = m68k_ADDRREG(op_dareg);
		}
		else	// ADD
		{
			//struct {unsigned	pad:4, dreg:3, t:1, size:2, mode:3, reg:3;}	op;
			uint8 reg = opcode & 0x7;
			uint8 mode = (opcode >> 3) & 0x7;
			uint8 size = (opcode >> 6) & 0x3;
			uint8 t = (opcode >> 8) & 0x1;
			uint8 dreg = (opcode >> 9) & 0x7;

		//	msptr += sprintf(msptr, "ADD.%c\t", SizeChar[size]);

			if (t)	// <Dn>,<ea>
			{
			//	msptr += sprintf(msptr, "D%d,", dreg);
				src = m68k_DATAREG(dreg);
				dst = do_ea(c, mode, reg, size);
			}
			else	// <ea>,<Dn>
			{
				src = do_ea(c, mode, reg, size);
				dst = m68k_DATAREG(dreg);
			//	msptr += sprintf(msptr, ",D%d", dreg);
			}

			return m68k_ADD(src, dst);
		}
	}

	return unknown_opcode();
}

char *ShiftRot[] =
{
	"AS",
	"LS",
	"ROX",
	"RO"
};

char ShRoDir[] = {'R', 'L'};

// Shift/Rotate
m68kinstr* codemap14(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream

	if ((opcode & 0xF8C0) == 0xE0C0)	// SHIFT/ROTATE - Memory
	{
		/*
		ATLASSERT(0);
		struct {unsigned	pad0:5, type:2, dir:1, pad1:2, mode:3, reg:3;}	op;
		*(uint16 *)(&op) = opcode;
		*/
		uint8 op_reg = (opcode)&0x7;
		uint8 op_mode = (opcode>>3)&0x7;
		uint8 op_dir = (opcode>>8)&0x1;
		uint8 op_type = (opcode>>10)&0x3;

	//	msptr += sprintf(msptr, "%s%c", ShiftRot[op_type], ShRoDir[op_dir]);

	//	msptr += sprintf(msptr, "\t");
		do_ea(c, op_mode, op_reg, 2);
	}
	else if ((opcode & 0xF000) == 0xE000)	// SHIFT/ROTATE - Register
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad:4, cr:3, dir:1, size:2, ir:1, type:2, dreg:3;}	op;
	//	*(uint16 *)(&op) = opcode;
		uint8 op_dreg = opcode & 0x7;
		uint8 op_type = (opcode>>3) & 0x3;
		uint8 op_ir = (opcode>>5) & 0x1;
		uint8 op_size = (opcode>>6) & 0x3;
		uint8 op_dir = (opcode>>8) & 0x1;
		uint8 op_cr = (opcode>>9) & 0x7;

	//	msptr += sprintf(msptr, "%s%c", ShiftRot[op_type], ShRoDir[op_dir]);
	//	msptr += sprintf(msptr, ".%c\t", SizeChar[op_size]);
		if (op_ir)
		;//	msptr += sprintf(msptr, "D%d,", op_cr);
		else
		;//	msptr += sprintf(msptr, "#%d,", (op_cr==0)?8:op_cr);
		//msptr += sprintf(msptr, "D%d", op_dreg);
	}
	else
	{
		return unknown_opcode();
	}

	return NULL;
}

// Coprocessor interface (MC68020)
m68kinstr* codemap15(m68kContext* c)
{
	uint16 opcode = fetch_w(c);		// Get the next opcode from the stream
	return NULL;

	uint8 coid = (opcode>>9) & 0x7;

	if (coid == 1)
	{
		int eareg = opcode & 0x7;
		int eamode = (opcode>>3) & 0x7;

		uint16 word = fetch_w(c);

		uint8 RM = (word>>14) & 0x1;
		uint8 reg = (word>>7) & 0x7;
		uint8 src_specifier = (word>>10) & 0x7;

		if (RM == 0)
		{
			ASSERT(eareg == 0);
			ASSERT(eamode == 0);
		}

		if ((word & 0x7F) == 0x0)
		{
			/*
0000000 FMOVE Rounding precision specified by the floating-point
control register.
1000000 FSMOVE Single-precision rounding specified.
1000100 FDMOVE Double-precision rounding specified.
*/
		;//	msptr += sprintf(msptr, "FMOVE\t");

			if (word & (1<<13))	// register -> EA
			{
			;//	msptr += sprintf(msptr, "F%d,", reg);
				if (RM == 1)
				{
					do_ea(c, eamode, eareg, 1);
				}
				else
				{
				}
			}
			else	// EA -> register
			{
				if (RM == 1)
				{
					do_ea(c, eamode, eareg, 1);
				}
				else
				{
				}
			;//	msptr += sprintf(msptr, ",F%d", reg);
			}

		}
		else if ((word & 0x7F) == 0x1)
		{
		//	msptr += sprintf(msptr, "FINT\t");

			if (RM == 1)
			{
				do_ea(c, eamode, eareg, 1);
			}
		}
		else if ((word & 0x7F) == 0x3)
		{
		//	msptr += sprintf(msptr, "FINTRZ\t");

			if (RM == 1)
			{
				do_ea(c, eamode, eareg, 1);
			}

		//	msptr += sprintf(msptr, ",F%d", reg);
		}
		else if ((word & 0x7F) == 0x1F)
		{
		//	msptr += sprintf(msptr, "FGETMAN\t");

			if (RM == 1)
			{
				do_ea(c, eamode, eareg, 1);
			}
		}
		else
		{
		//	msptr += sprintf(msptr, "fop\t");

			if (RM == 1)
			{
				do_ea(c, eamode, eareg, 1);
			}
		}
	}
	else
		return unknown_opcode();

	return NULL;
}

typedef m68kinstr* (*TyCodeMapFunc)(m68kContext* c);

TyCodeMapFunc CodeMapFunc[] =
{
	codemap00,
	codemap01,
	codemap02,
	codemap03,
	codemap04,
	codemap05,
	codemap06,
	codemap07,
	codemap08,
	codemap09,
	codemap10,
	codemap11,
	codemap12,
	codemap13,
	codemap14,
	codemap15,
};

m68kinstr* disasm_m68k(m68kContext* c)
{
	/*
	uint16 opcode = (uint16)c->pc[0]<<8;
	opcode |= c->pc[1];
	*/

	return (CodeMapFunc[c->pc[0]>>4])(c);
}

IO::TextWriter& operator << (IO::TextWriter& stream, m68koperand* operand)
{
	switch (operand->kind)
	{
	case m68koperand::K_INDIRECT:
		{
			if (operand->indirect->kind == m68koperand::K_IMM)
			{
				stream << "$";
				stream << (int)operand->indirect->imm32;
			}
			else
			{
				ASSERT(0);
			}
		}
		break;

	case m68koperand::K_IMM:
		{
			stream << "#";
			stream << (int)operand->imm32;
		}
		break;

	case m68koperand::K_DATAREG:
		{
			stream << "D" << (int)operand->reg;
		}
		break;

	case m68koperand::K_ADDRREG:
		{
			stream << "A" << (int)operand->reg;
		}
		break;

	case m68koperand::K_INDIRECT_REG:
		{
			stream << "(";
			stream << "A" << (int)operand->reg;
			stream << ")";
		}
		break;

	case m68koperand::K_INDIRECT_POSTINC:
		{
			stream << "(";
			stream << "A" << (int)operand->reg;
			stream << ")+";
		}
		break;

	case m68koperand::K_INDIRECT_PREDEC:
		{
			stream << "-(";
			stream << "A" << (int)operand->reg;
			stream << ")";
		}
		break;

	case m68koperand::K_INDIRECT_DISPLACEMENT:
		{
			stream << (int)operand->displacement.disp16;
			stream << "(";
			stream << "A" << (int)operand->displacement.areg;
			stream << ")";
		}
		break;

	case m68koperand::K_INDIRECT_INDEX:
		{
			stream << (int)operand->index.disp;
			stream << "(";

			if (operand->index.ext_factor == 0)
			{
				stream << "A" << (int)operand->index.reg;
				stream << ",";
				stream << "D" << (int)operand->index.ext_reg;
			}
			else
			{
				stream << "A" << (int)operand->index.reg;
				stream << ",";
				stream << "D" << (int)operand->index.ext_reg;
				stream << "*" << (int)(1<<operand->index.ext_factor);
			}

			stream << ")";
		}
		break;

	default:
		ASSERT(0);
	}

	return stream;
}

CodeCompExt IO::TextWriter& operator << (IO::TextWriter& stream, const m68kinstr* instr)
{
	switch (instr->kind)
	{
	case m68kinstr::K_MOVE:
		{
			stream << "move";
			stream << "\t";
			if (instr->two.src && instr->two.dst)
			{
				stream << instr->two.src;
				stream << ",";
				stream << instr->two.dst;
			}
		}
		break;

	case m68kinstr::K_MOVEM:
		{
			stream << "movem";
		}
		break;

	case m68kinstr::K_MOVEQ:
		{
			stream << "moveq";
			stream << "#" << (int)instr->moveq.data;
			stream << ",";
			stream << "D" << (int)(*instr->moveq.dreg)->getn();
		}
		break;

	case m68kinstr::K_ADD:
		{
			stream << "add";
			stream << "\t";
			if (instr->two.src && instr->two.dst)
			{
				stream << instr->two.src;
				stream << ",";
				stream << instr->two.dst;
			}
		}
		break;

	case m68kinstr::K_SUB:
		{
			stream << "sub";
			stream << "\t";
			if (instr->two.src && instr->two.dst)
			{
				stream << instr->two.src;
				stream << ",";
				stream << instr->two.dst;
			}
		}
		break;

	case m68kinstr::K_OR:
		{
			stream << "or";
			stream << "\t";
			if (instr->two.src && instr->two.dst)
			{
				stream << instr->two.src;
				stream << ",";
				stream << instr->two.dst;
			}
		}
		break;

	case m68kinstr::K_EOR:
		{
			stream << "eor";
			stream << "\t";
			if (instr->two.src && instr->two.dst)
			{
				stream << instr->two.src;
				stream << ",";
				stream << instr->two.dst;
			}
		}
		break;

	case m68kinstr::K_AND:
		{
			stream << "and";
			stream << "\t";
			if (instr->two.src && instr->two.dst)
			{
				stream << instr->two.src;
				stream << ",";
				stream << instr->two.dst;
			}
		}
		break;

	case m68kinstr::K_JSR:
		{
			stream << "jsr";
		}
		break;

	case m68kinstr::K_BSR:
		{
			stream << "bsr";
			stream << " ";
			stream << instr->uint_16;
		}
		break;

	case m68kinstr::K_JMP:
		{
			stream << "jmp";
		}
		break;

	case m68kinstr::K_LINK:
		{
			stream << "link";
			stream << " ";
			stream << instr->link.reg;
			stream << ",";
			stream << instr->link.offset;
		}
		break;

	case m68kinstr::K_UNLK:
		{
			stream << "unlk";
			stream << " ";
			stream << instr->op;
		}
		break;

	case m68kinstr::K_TST:
		{
			stream << "tst";
		}
		break;

	case m68kinstr::K_CMP:
		{
			stream << "cmp";
		}
		break;

	case m68kinstr::K_RTS:
		{
			stream << "rts";
		}
		break;

	case m68kinstr::K_RTR:
		{
			stream << "rtr";
		}
		break;

	case m68kinstr::K_RTE:
		{
			stream << "rte";
		}
		break;

	case m68kinstr::K_LEA:
		{
			stream << "lea";
			stream << "\t";
			if (instr->two.src && instr->two.dst)
			{
				stream << instr->two.src;
				stream << ",";
				stream << instr->two.dst;
			}
		}
		break;

	case m68kinstr::K_PEA:
		{
			stream << "pea";
		}
		break;

	case m68kinstr::K_EXT:
		{
			stream << "ext";
		}
		break;

	case m68kinstr::K_CLR:
		{
			stream << "clr";
			stream << "\t";
			if (instr->op)
			{
				stream << instr->op;
			}
		}
		break;

	case m68kinstr::K_NEG:
		{
			stream << "neg";
		}
		break;

	case m68kinstr::K_NEGX:
		{
			stream << "negx";
		}
		break;

	case m68kinstr::K_SWAP:
		{
			stream << "swap";
		}
		break;

	case m68kinstr::K_BTST:
		{
			stream << "btst";
		}
		break;

	case m68kinstr::K_BCHG:
		{
			stream << "bchg";
		}
		break;

	case m68kinstr::K_BCLR:
		{
			stream << "bclr";
		}
		break;

	case m68kinstr::K_BSET:
		{
			stream << "bset";
		}
		break;

	case m68kinstr::K_EXG:
		{
			stream << "exg";
		}
		break;

	case m68kinstr::K_CHK:
		{
			stream << "chk";
			stream << "\t";
			if (instr->two.src && instr->two.dst)
			{
				stream << instr->two.src;
				stream << ",";
				stream << instr->two.dst;
			}
		}
		break;

	case m68kinstr::K_TRAP:
		{
			stream << "trap";
			stream << " ";
			stream << "#" << (int)instr->trap;
		}
		break;

	case m68kinstr::K_DBcc:
		{
			stream << "DBcc";
		}
		break;

	case m68kinstr::K_Bcc:
		{
			/*
			if (instr->bcc.condition == 1)	// Always False
				stream << "BRA";//.%c\t", SizeChar[(op_disp8)? 0: 1]);
			else
			*/
				stream << "B" << CondTest[instr->bcc.condition];//, SizeChar[(op_disp8)? 0: 1]);
		}
		break;

	default:
		ASSERT(0);
	}

	return stream;
}

CodeCompExt String toString(const m68kinstr* instr)
{
	IO::StringWriter stream;
	stream << instr;
	return stream.str();
}

void assem(m68kinstr* assem, CFunctionCode* pFun, FILE* fileout)
{
	switch (assem->kind)
	{
	case m68kinstr::K_LSHIFT:	// logical shift
		{
			int size = 2;
			bool dr = assem->lshift.dr;
			int src_reg = (*assem->lshift.src->temp)->getn();
			int dst_reg = (*assem->lshift.dst->temp)->getn();

			int ir;

			ir = 1;

			int countreg = src_reg;

			uint16 word = 0xE008;
			word |= countreg<<9;
			word |= dr<<8;
			word |= size<<6;
			word |= ir<<5;
			word |= dst_reg;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_ASR:
		{
			int size = 2;
			int countreg = 1;
			int dr = 0;
			int reg = (*assem->op->temp)->getn();

			uint16 word = 0xE000;
			word |= countreg<<9;
			word |= dr<<8;
			word |= size<<6;
			word |= reg;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_ROXR:
		{
			int size = 2;
			int rotatereg = 1;
			int dr = 0;
			int reg = (*assem->op->temp)->getn();

			uint16 word = 0xE010;
			word |= rotatereg<<9;
			word |= dr<<8;
			word |= size<<6;
			word |= reg;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_SET:
		{
			int ea_reg;
			int ea_mode;

			if (assem->set.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				ea_reg = (*assem->set.dst->temp)->getn() & 7;

				if ((*assem->set.dst->temp)->getn() < 8)
					ea_mode = 0;
				else
					ea_mode = 1;
			}
			else
				ASSERT(0);

			uint16 word = 0x50C0;
			word |= assem->set.condition<<8;
			word |= ea_mode<<3;
			word |= ea_reg<<0;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_MOVEQ:
		{
			uint16 word = 0x7000;

			ASSERT((*assem->moveq.dreg)->getn() < 8);

			word |= (*assem->moveq.dreg)->getn()<<9;
			word |= (uint8)assem->moveq.data;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_SUBQ:
		{
			int size = 2;
			int ea_reg;
			int ea_mode;

			if (assem->subq.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				ea_reg = (*assem->subq.dst->temp)->getn() & 7;

				if ((*assem->subq.dst->temp)->getn() < 8)
					ea_mode = 0;
				else
					ea_mode = 1;
			}
			else
				ASSERT(0);

			uint16 word = 0x5100;
			word |= ((uint8)assem->subq.data == 8? 0: assem->subq.data)<<9;
			word |= size<<6;
			word |= ea_mode<<3;
			word |= ea_reg;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_TST:
		{
			int size = 2;
			int ea_reg;
			int ea_mode;

			if (assem->op->kind == m68koperand::K_DATAREG_TEMP)
			{
				ea_reg = (*assem->op->temp)->getn() & 7;

				if ((*assem->op->temp)->getn() < 8)
					ea_mode = 0;
				else
					ea_mode = 1;
			}
			else
				ASSERT(0);

			uint16 word = 0x4A00;
			word |= size<<6;
			word |= ea_mode<<3;
			word |= ea_reg<<0;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_MOVE:
		{
			int size;
			int src_reg = 0;
			int dst_reg = 0;
			int src_mode = 0;
			int dst_mode = 0;

			if (assem->two.size == 1)
				size = 1;
			else if (assem->two.size == 2)
				size = 3;
			else
				size = 2;

			if (assem->two.src->kind == m68koperand::K_INDIRECT_DISPLACEMENT)
			{
				ASSERT((*assem->two.src->displacement.areg)->getn() >= 8);
				src_reg = (*assem->two.src->displacement.areg)->getn() & 7;
				src_mode = 5;
			}
			else if (assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				src_reg = (*assem->two.src->temp)->getn() & 7;

				if ((*assem->two.src->temp)->getn() < 8)
					src_mode = 0;
				else
					src_mode = 1;
			}
			else if (assem->two.src->kind == m68koperand::K_IMM)
			{
				src_reg = 4;
				src_mode = 7;
			}
			else if (assem->two.src->kind == m68koperand::K_NAME)
			{
		//		ASSERT(assem->two.src->name->m_spOffset != -1);

				src_reg = 4;
				src_mode = 7;
			}
			else if (assem->two.src->kind == m68koperand::K_INDIRECT_TEMP)
			{
				ASSERT((*assem->two.src->temp)->getn() >= 8);

				src_reg = (*assem->two.src->temp)->getn() & 7;
				src_mode = 2;
			}
			else if (assem->two.src->kind == m68koperand::K_INDIRECT_INDEX)
			{
				ASSERT((*assem->two.src->index.reg)->getn() >= 8);

				src_reg = (*assem->two.src->index.reg)->getn() & 7;
				src_mode = 6;
			}
			else if (assem->two.src->kind == m68koperand::K_INDIRECT /*CONST*/)
			{
				src_reg = 1;//assem->two.src->indirect - 8;
				src_mode = 7;
			}
			else
				ASSERT(0);

			if (assem->two.dst->kind == m68koperand::K_INDIRECT_TEMP)
			{
				ASSERT((*assem->two.dst->temp)->getn() >= 8);
				dst_reg = (*assem->two.dst->temp)->getn() & 7;
				dst_mode = 2;
			}
			else if (assem->two.dst->kind == m68koperand::K_INDIRECT_DISPLACEMENT)
			{
				ASSERT((*assem->two.dst->displacement.areg)->getn() >= 8);
				dst_reg = (*assem->two.dst->displacement.areg)->getn() & 7;
				dst_mode = 5;
			}
			else if (assem->two.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				dst_reg = (*assem->two.dst->temp)->getn() & 7;
				if ((*assem->two.dst->temp)->getn() < 8)
					dst_mode = 0;
				else
					dst_mode = 1;
			}
			else if (assem->two.dst->kind == m68koperand::K_INDIRECT_PREDEC)
			{
				ASSERT((*assem->two.dst->temp)->getn() >= 8);

				dst_mode = 4;
				dst_reg = (*assem->two.dst->temp)->getn() & 7;
			}
			else
				ASSERT(0);

			uint16 word = size<<12;

			word |= dst_reg<<9;
			word |= dst_mode<<6;
			word |= src_mode<<3;
			word |= src_reg<<0;

			fput16(fileout, word);

			if (src_mode == 5)
			{
				fput16(fileout, assem->two.src->displacement.disp16);
			}
			else if (src_mode == 6)
			{
				uint16 extword = 0;

				int ext_reg = (*assem->two.src->index.ext_reg)->getn();

				extword |= ext_reg<<12;
				extword |= assem->two.src->index.ext_factor<<9;
				extword |= (uint8)assem->two.src->index.disp;

				fput16(fileout, extword);
			}
			else if (src_mode == 7)
			{
				if (src_reg == 4)
				{
					if (assem->two.src->kind == m68koperand::K_NAME)
					{
						FRelocation* reloc = new FRelocation;
						reloc->VirtualAddress = ftell(fileout);
						reloc->tempLabel = assem->two.src->name;
						pFun->AddRelocation(reloc);

						//pFun->m_labels.push_back(RelativeLabel(ftell(fileout), assem->two.src->name));

						long v = 0;
						if (size == 2)
							fput32(fileout, v);
						else
							fput16(fileout, v);
					}
					else
					{
						if (size == 2)
							fput32(fileout, assem->two.src->imm32);
						else
							fput16(fileout, assem->two.src->imm32);
					}
				}
				else
				{
					if (size == 2)
						fput32(fileout, assem->two.src->indirect->imm32);
					else
						fput16(fileout, assem->two.src->indirect->imm32);
				}
			}

			if (dst_mode == 5)
			{
				fput16(fileout, assem->two.dst->displacement.disp16);
			}
		}
		break;

	case m68kinstr::K_CLR:
		{
			int size;
			int reg;
			int mode;

			if (assem->clr.size == 1)
				size = 0;
			else if (assem->clr.size == 2)
				size = 1;
			else
				size = 2;

			if (assem->clr.operand->kind == m68koperand::K_INDIRECT_DISPLACEMENT)
			{
				ASSERT((*assem->clr.operand->displacement.areg)->getn() >= 8);
				reg = (*assem->clr.operand->displacement.areg)->getn() & 7;
				mode = 5;
			}
			else if (assem->clr.operand->kind == m68koperand::K_DATAREG_TEMP)
			{
				reg = (*assem->clr.operand->temp)->getn() & 7;

				if ((*assem->clr.operand->temp)->getn() < 8)
					mode = 0;
				else
					mode = 1;
			}
			else
				ASSERT(0);

			uint16 word = 0x4200;
			word |= size<<6;
			word |= mode<<3;
			word |= reg;

			fput16(fileout, word);

			if (mode == 5)
			{
				fput16(fileout, assem->clr.operand->displacement.disp16);
			}
		}
		break;

	case m68kinstr::K_NEG:
		{
			int size;
			int reg;
			int mode;

			size = 2;

			if (assem->op->kind == m68koperand::K_DATAREG_TEMP)
			{
				ASSERT((*assem->op->temp)->getn() < 8);
				reg = (*assem->op->temp)->getn() & 7;

				mode = 0;
			}
			else
				ASSERT(0);

			uint16 word = 0x4400;
			word |= size<<6;
			word |= mode<<3;
			word |= reg;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_NEGX:
		{
			int size;
			int reg;
			int mode;

			size = 2;

			if (assem->op->kind == m68koperand::K_DATAREG_TEMP)
			{
				ASSERT((*assem->op->temp)->getn() < 8);
				reg = (*assem->op->temp)->getn() & 7;

				mode = 0;
			}
			else
				ASSERT(0);

			uint16 word = 0x4000;
			word |= size<<6;
			word |= mode<<3;
			word |= reg;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_LEA:
		{
			int src_reg;
			int src_mode;
			int dst_reg;

			if (assem->two.src->kind == m68koperand::K_INDIRECT_DISPLACEMENT)
			{
				ASSERT((*assem->two.src->displacement.areg)->getn() >= 8);
				src_reg = (*assem->two.src->displacement.areg)->getn() & 7;
				src_mode = 5;
			}
			else
				ASSERT(0);

			if (assem->two.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				ASSERT((*assem->two.dst->temp)->getn() >= 8);
				dst_reg = (*assem->two.dst->temp)->getn() & 7;
			}
			else
				ASSERT(0);

			uint16 word = 0x41C0;

			word |= dst_reg<<9;
			word |= src_mode<<3;
			word |= src_reg;

			fput16(fileout, word);

			if (src_mode == 5)
			{
				fput16(fileout, assem->two.src->displacement.disp16);
			}
		}
		break;

	case m68kinstr::K_ADD:
		{
			int opmode;
			int ea_reg;
			int ea_mode;
			int dn;

			if (assem->two.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				dn = (*assem->two.dst->temp)->getn() & 7;

				if ((*assem->two.dst->temp)->getn() < 8)
				{
					opmode = 2;	// long
				}
				else
				{
					opmode = 7;	// long
				}

				if (assem->two.src->kind == m68koperand::K_IMM)
				{
					ea_mode = 7;
					ea_reg = 4;
				}
				else if (assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
				{
					ea_reg = (*assem->two.src->temp)->getn() & 7;
					if ((*assem->two.src->temp)->getn() < 8)
						ea_mode = 0;
					else
						ea_mode = 1;
				}
				else
					ASSERT(0);
			}
			else if (assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				opmode = 6;	// long
				dn = (*assem->two.src->temp)->getn();

				ASSERT(assem->two.dst->kind != m68koperand::K_DATAREG_TEMP);	// Not supported, it's catched by the if above

				// TODO
				ASSERT(0);
			}
			/*
			else if (assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				opmode = 6;	// long
				dn = assem->two.src->temp->m_n;

				//ASSERT(assem->two.dst->kind != m68koperand::K_DATAREG);	// Not supported, it's catched by the if above

				// TODO
				ASSERT(0);
			}
			*/
			else
				ASSERT(0);

			uint16 word = 0xD000;
			word |= ea_reg;
			word |= ea_mode<<3;
			word |= opmode<<6;
			word |= dn<<9;
			fput16(fileout, word);

			if (ea_mode == 7 && ea_reg == 4)
			{
				fput32(fileout, assem->two.src->imm32);
			}
		}
		break;

	case m68kinstr::K_SUB:
		{
			int opmode;
			int ea_reg;
			int ea_mode;
			int dn;

			if (assem->two.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				opmode = 2;	// long
				dn = (*assem->two.dst->temp)->getn();

				if (assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
				{
					ea_reg = (*assem->two.src->temp)->getn();
					ea_mode = 0;
				}
				else
					ASSERT(0);
			}
			else if (assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				opmode = 6;	// long
				dn = (*assem->two.src->temp)->getn();

				ASSERT(assem->two.dst->kind != m68koperand::K_DATAREG_TEMP);	// Not supported, it's catched by the if above

				// TODO
				ASSERT(0);
			}
			/*
			else if (assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				opmode = 6;	// long
				dn = assem->two.src->temp->m_n;

				//ASSERT(assem->two.dst->kind != m68koperand::K_DATAREG);	// Not supported, it's catched by the if above

				// TODO
				ASSERT(0);
			}
			*/
			else
				ASSERT(0);

			uint16 word = 0x9000;
			word |= ea_reg;
			word |= ea_mode<<3;
			word |= opmode<<6;
			word |= dn<<9;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_SUBI:
		{
			int ea_reg;
			int ea_mode;
			int size;

			size = 2;

			if (assem->subi.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				ea_reg = (*assem->subi.dst->temp)->getn();
				ea_mode = 0;
			}

			uint16 word = 0x0400;
			word |= size<<6;
			word |= ea_mode<<3;
			word |= ea_reg;

			fput16(fileout, word);

			fput32(fileout, assem->subi.src);
		}
		break;

	case m68kinstr::K_ANDI:
		{
			int ea_reg;
			int ea_mode;
			int size;

			size = assem->andi.size>>1;

			if (assem->andi.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				ASSERT((*assem->andi.dst->temp)->getn() < 8);

				ea_reg = (*assem->andi.dst->temp)->getn();
				ea_mode = 0;
			}
			else
				ASSERT(0);

			uint16 word = 0x0200;
			word |= size<<6;
			word |= ea_mode<<3;
			word |= ea_reg;

			fput16(fileout, word);

			if (size == 2)
				fput32(fileout, assem->andi.src);
			else
				fput16(fileout, assem->andi.src);
		}
		break;

	case m68kinstr::K_CMP:
		{
			int ea_mode;
			int ea_reg;
			int size;

			size = 2;

			int dn = (*assem->two.src->temp)->getn();

			if (assem->two.dst->kind == m68koperand::K_DATAREG_TEMP)
			{
				ASSERT((*assem->two.dst->temp)->getn() < 8);

				ea_reg = (*assem->two.dst->temp)->getn();
				ea_mode = 0;
			}
			else
				ASSERT(0);

			uint16 word = 0xB000;
			word |= dn<<9;
			word |= size<<6;
			word |= ea_mode<<3;
			word |= ea_reg;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_MULS:
		{
			int ea_reg;
			int ea_mode;

			if (assem->muls.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				ASSERT((*assem->muls.src->temp)->getn() < 8);
				ea_reg = (*assem->muls.src->temp)->getn();
				ea_mode = 0;
			}
			else if (assem->muls.src->kind == m68koperand::K_INDIRECT_DISPLACEMENT)
			{
				ASSERT((*assem->muls.src->displacement.areg)->getn() >= 8);
				ea_reg = (*assem->muls.src->displacement.areg)->getn() & 7;
				ea_mode = 5;
			}
			else
				ASSERT(0);

		//	uint16 word = 0xC1C0;	// word form

			uint16 word = 0x4C00;	// long form
			word |= ea_mode<<3;
			word |= ea_reg;
			fput16(fileout, word);

			ASSERT((*assem->muls.dl_reg)->getn() < 8);

			word = 0x0800;
			word |= (*assem->muls.dl_reg)->getn() << 12;
			if (assem->muls.dh_reg)
			{
				word |= 1<<10;	// 64-bit product
				word |= (*assem->muls.dh_reg)->getn();
			}
			else
			{
				//word |= 0<<10;	// 32-bit product
			}
			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_DIVS:
		{
			int ea_reg;
			int ea_mode;

			if (assem->divs.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				ASSERT((*assem->divs.src->temp)->getn() < 8);
				ea_reg = (*assem->divs.src->temp)->getn();
				ea_mode = 0;
			}
			else if (assem->divs.src->kind == m68koperand::K_INDIRECT_DISPLACEMENT)
			{
				ASSERT((*assem->divs.src->displacement.areg)->getn() >= 8);
				ea_reg = (*assem->divs.src->displacement.areg)->getn() & 7;
				ea_mode = 5;
			}
			else
				ASSERT(0);

			uint16 word = 0x4C40;	// long form
			word |= ea_mode<<3;
			word |= ea_reg;
			fput16(fileout, word);

			word = 0x0800;
			word |= (*assem->divs.q_reg)->getn() << 12;
			word |= 1<<10;	// 64-bit
			word |= (*assem->divs.r_reg)->getn();
			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_ADDX:
		{
			int rm;
			int size;
			int dst_reg;
			int src_reg;

			size = 2;	// long

			if (assem->two.dst->kind == m68koperand::K_DATAREG_TEMP && assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				rm = 0;

				ASSERT((*assem->two.src->temp)->getn() < 8);
				ASSERT((*assem->two.dst->temp)->getn() < 8);

				src_reg = (*assem->two.src->temp)->getn() & 7;
				dst_reg = (*assem->two.dst->temp)->getn() & 7;
			}
			else
				ASSERT(0);

			uint16 word = 0xD100;
			word |= dst_reg<<9;
			word |= size<<6;
			word |= rm<<3;
			word |= src_reg;
			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_SUBX:
		{
			int rm;
			int size;
			int dst_reg;
			int src_reg;

			size = 2;	// long

			if (assem->two.dst->kind == m68koperand::K_DATAREG_TEMP && assem->two.src->kind == m68koperand::K_DATAREG_TEMP)
			{
				rm = 0;

				ASSERT((*assem->two.src->temp)->getn() < 8);
				ASSERT((*assem->two.dst->temp)->getn() < 8);

				src_reg = (*assem->two.src->temp)->getn() & 7;
				dst_reg = (*assem->two.dst->temp)->getn() & 7;
			}
			else
				ASSERT(0);

			uint16 word = 0x9100;
			word |= dst_reg<<9;
			word |= size<<6;
			word |= rm<<3;
			word |= src_reg;
			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_EXT:
		{
			uint16 word = 0x4800;
			int dn = (*assem->ext.dn)->getn();
			int opmode = assem->ext.opmode;

			word |= opmode<<6;
			word |= dn;

			fput16(fileout, word);
		}
		break;

	case m68kinstr::K_Bcc:
		{
			uint16 word = 0x6000;
			word |= assem->bcc.condition<<8;
			fput16(fileout, word);

			FRelocation* reloc = new FRelocation;
			reloc->VirtualAddress = ftell(fileout);
			reloc->tempLabel = assem->bcc.displacement;

			reloc->Type = 1;	// relative
			pFun->AddRelocation(reloc);

			uint16 displacement = 0;
			fput16(fileout, displacement);
		}
		break;

	case m68kinstr::K_DBcc:
		{
			uint16 word = 0x50C8;
			word |= assem->dbcc.condition<<8;
			word |= (*assem->dbcc.dn)->getn();
			fput16(fileout, word);

			FRelocation* reloc = new FRelocation;
			reloc->VirtualAddress = ftell(fileout);
			reloc->tempLabel = assem->dbcc.displacement;
			reloc->Type = 1;	// relative
			pFun->AddRelocation(reloc);

			uint16 displacement = 0;
			fput16(fileout, displacement);
		}
		break;

	case m68kinstr::K_JSR:
		{
			int src_reg;
			int src_mode;

			if (assem->op->kind == m68koperand::K_INDIRECT_DISPLACEMENT)
			{
				ASSERT((*assem->op->displacement.areg)->getn() >= 8);

				src_reg = (*assem->op->displacement.areg)->getn() & 7;
				src_mode = 5;
			}
			else if (assem->op->kind == m68koperand::K_NAME)
			{
				src_reg = 1;
				src_mode = 7;
			}
			else
				ASSERT(0);

			uint16 word = 0x4E80;
			word |= src_mode<<3;
			word |= src_reg<<0;
			fput16(fileout, word);

			if (src_mode == 5)
			{
				fput16(fileout, assem->op->displacement.disp16);
			}
			else if (src_mode == 7)
			{
				if (src_reg == 0)	// (xxx).W
				{
					ASSERT(0);
				}
				else if (src_reg == 1)	// (xxx).L
				{
					FRelocation* reloc = new FRelocation;
					reloc->VirtualAddress = ftell(fileout);
					reloc->tempLabel = assem->two.src->name;
					pFun->AddRelocation(reloc);

					long v = 0;
					fput32(fileout, v);
				}
				else
					ASSERT(0);

				/*
				else
				{
					if (size == 2)
						fput32(fileout, assem->two.src->indirect->imm32);
					else
						fput16(fileout, assem->two.src->indirect->imm32);
				}
				*/
			}
		}
		break;

	case m68kinstr::K_PEA:
		{
			int src_reg;
			int src_mode;

			if (assem->op->kind == m68koperand::K_INDIRECT_DISPLACEMENT)
			{
				ASSERT((*assem->op->displacement.areg)->getn() >= 8);

				src_reg = (*assem->op->displacement.areg)->getn() & 7;
				src_mode = 5;
			}
			else if (assem->op->kind == m68koperand::K_NAME)
			{
				src_reg = 1;
				src_mode = 7;
			}
			else
				ASSERT(0);

			uint16 word = 0x4840;
			word |= src_mode<<3;
			word |= src_reg<<0;
			fput16(fileout, word);

			if (src_mode == 5)
			{
				fput16(fileout, assem->op->displacement.disp16);
			}
			else if (src_mode == 7)
			{
				if (src_reg == 0)	// (xxx).W
				{
					ASSERT(0);
				}
				else if (src_reg == 1)	// (xxx).L
				{
					FRelocation* reloc = new FRelocation;
					reloc->VirtualAddress = ftell(fileout);
					reloc->tempLabel = assem->two.src->name;
					pFun->AddRelocation(reloc);

					long v = 0;
					fput32(fileout, v);
				}
				else
					ASSERT(0);

				/*
				else
				{
					if (size == 2)
						fput32(fileout, assem->two.src->indirect->imm32);
					else
						fput16(fileout, assem->two.src->indirect->imm32);
				}
				*/
			}
		}
		break;

	case m68kinstr::K_LINK:
		{
			ASSERT(assem->link.reg->kind == m68koperand::K_DATAREG_TEMP);

			if (assem->link.offset >= -32768 && assem->link.offset <= 32767)
			{
				fput16(fileout, 0x4E50 | ((*assem->link.reg->temp)->getn() & 7));
				fput16(fileout, assem->link.offset);
			}
			else
				ASSERT(0);
		}
		break;

	case m68kinstr::K_UNLK:
		{
			ASSERT(assem->op->kind == m68koperand::K_DATAREG_TEMP);
			fput16(fileout, 0x4E58 | ((*assem->op->temp)->getn() & 7));
		}
		break;

	case m68kinstr::K_RTS:
		{
			fput16(fileout, 0x4E75);
		}
		break;

	default:
		ASSERT(0);
	}
}

//}	// cpp
}	// System
