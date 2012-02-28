//#include "StdAfx.h"

//#include "headers.h"

#include <stdio.h>

typedef unsigned char BYTE;
typedef unsigned char UBYTE;
typedef unsigned short WORD;
typedef unsigned short UWORD;
typedef long LONG;
typedef unsigned long ULONG;
typedef int BOOL;

#define TRUE	1
#define FALSE	0
#define NULL	0

#define ENDIANWORD(x)	(x)
#define ENDIANLONG(x)	(x)

#define ATLASSERT(x)

void unknown_opcode(void);

char SizeChar[] =
{
	'B', 'W', 'L'
};

char *CondTest[] =
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

char *BitStr[] =
{
	"TST",
	"CHG",
	"CLR",
	"SET"
};

// Global variables for decoding code hunks
UWORD	opcode;
ULONG	counter;
BYTE	*stream;

BOOL	nopc;

char	xsbuf[128], *xsptr;
char	msbuf[128],	*msptr;

/*************************************************************************************

 Fetch a word from the code stream

*************************************************************************************/

WORD fetch_w(void)
{
	WORD	d = *(WORD *)stream;
	stream += sizeof(WORD);
	counter += sizeof(WORD);

	d = ENDIANWORD(d);

#if 0
	if (!args.nopc) xsptr += sprintf(xsptr, " %04X", d);
#endif

	return d;
}

/*************************************************************************************

 Fetch a long word from the code stream

*************************************************************************************/

ULONG fetch_l(void)
{
	ULONG	d = *(ULONG *)stream;
	stream += sizeof(ULONG);
	counter += sizeof(ULONG);

	d = ENDIANLONG(d);

#if 0
	if (!args.nopc) xsptr += sprintf(xsptr, " %04X_%04X", (d >> 16), (d & 0xffff));
#endif

	return d;
}

// Do immediate
void do_imm(BYTE size)
{
	if (size == 2)	// long
	{
		//msptr += sprintf(msptr, "#$%lX", fetch_l());
		msptr += sprintf(msptr, "#%ld", fetch_l());
	}
	else	// byte/word
	{
		//msptr += sprintf(msptr, "#$%X", fetch_w());
		msptr += sprintf(msptr, "#%d", fetch_w());
	}
}

// Do effective address (six bits of ea) size is optional
// 5  4  3 | 2  1  0
//   Mode  | Register
void do_ea(BYTE mode, BYTE reg, BYTE size)
{
#if 0
	extern struct SymbolNode *FindSymbol(ULONG counter);
	struct SymbolNode	*symnode;
#endif
	LONG	disp;

	switch (mode)
	{
	case 0:	// Data Register Direct
		msptr += sprintf(msptr, "D%d", reg);
		break;
		/************************************************************************************/
	case 1:	// Address Register Direct
		msptr += sprintf(msptr, "A%d", reg);
		break;
		/************************************************************************************/
	case 2:	// Address Register Indirect
		msptr += sprintf(msptr, "(A%d)", reg);
		break;
		
	case 3:	// Address Register Indirect with Postincrement
		msptr += sprintf(msptr, "(A%d)+", reg);
		break;
		
	case 4:	// Address Register Indirect with Predecrement
		msptr += sprintf(msptr, "-(A%d)", reg);
		break;
		
	case 5:	// Address Register Indirect with Displacement
		msptr += sprintf(msptr, "%d(A%d)", (short)fetch_w(), reg);
		break;
		/************************************************************************************/
	case 6:	// Address Register Indirect with Index
		{
			UWORD	extw = fetch_w();
			
			if (!(extw & 0x0100))	// no 8bit? Brief format
			{
				//struct {unsigned	type:1, reg:3, isize:1, factor:2, pad:1, disp:8;}	ext;
				//*(UWORD *)(&ext) = extw;
				BYTE ext_disp = extw & 0xFF;
				BYTE ext_factor = (extw >> 9) & 0x3;
				BYTE ext_isize = (extw >> 11) & 0x1;
				BYTE ext_reg = (extw >> 12) & 0x7;
				BYTE ext_type = (extw >> 15) & 0x1;
				
				if (ext_factor == 0)
					msptr += sprintf(msptr, "$%02X(A%d,D%d.%c)", ext_disp, reg, ext_reg, SizeChar[ext_isize+1]);
				else
					msptr += sprintf(msptr, "$%02X(A%d,D%d.%c*%d)", ext_disp, reg, ext_reg, SizeChar[ext_isize+1], 1<<ext_factor);
			}
			else	// Full format (68020)
			{
				ULONG	disp0 = 0L;
				ULONG	disp1 = 0L;
				UWORD	index_type;		// Post/Pre Index
			
			//	ATLASSERT(0);
			//	struct {unsigned	type:1, reg:3, isize:1, factor:2, pad:1, bsup:1, isup:1, bsize:2, pad1:1, isel:3;}	ext;
			//	*(UWORD *)(&ext) = extw;
				BYTE extisel = extw & 0x7;
				BYTE extbsize = (extw>>4) & 0x3;
				BYTE extisup = (extw>>6) & 0x1;
				BYTE extbsup = (extw>>7) & 0x1;
				BYTE extfactor = (extw>>9) & 0x3;
				BYTE extisize = (extw>>11) & 0x1;
				BYTE extreg = (extw>>12) & 0x7;
				BYTE exttype = (extw>>15) & 0x1;
				
				// Get base displacement
				if (extbsize == 2)	// Word base displacement
					disp0 = fetch_w();
				else if (extbsize == 3)	// Long base displacement
					disp0 = fetch_l();
				
				// Get outer displacement
				if ((extisel == 2) || ((extisel == 6) && !extisup))	// Word displacement
					disp1 = fetch_w();
				else if ((extisel == 3) || ((extisel == 7) && !extisup))	// Long displacement
					disp1 = fetch_l();
				
				// Get Index type (Post/Pre)
				if (extisel & 0x4)
					index_type = 0;	// Pre-index
				else
					index_type = 1;	// Post-index
				
				if (index_type)	// Post-index
				{
					msptr += sprintf(msptr, "([$%lX,A%d,D%d.%c*%d],$%lX)", disp0, reg, extreg, SizeChar[extisize+1], 1<<extfactor, disp1);
				}
				else	// Pre-index
				{
					msptr += sprintf(msptr, "([$%lX,A%d],D%d.%c*%d,$%lX)", disp0, reg, extreg, SizeChar[extisize+1], 1<<extfactor, disp1);
				}
			}
		}
		break;
		/************************************************************************************/
	case 7:
		switch (reg)
		{
		case 0:	// Absolute Short
			msptr += sprintf(msptr, "$%d.W", fetch_w());
			break;
			
		case 1:	// Absolute Long
			msptr += sprintf(msptr, "$%ld.L", fetch_l());
			break;
			/************************************************************************************/
		case 2:	// Program Counter Indirect with Displacement
			disp = fetch_w();
			
#if 0
			symnode = FindSymbol(counter+disp-2);
			
			if (symnode)
			{
				msptr += sprintf(msptr, "%.*s(PC)", (*symnode->SymPtr)<<2, symnode->SymPtr+1);
			}
			else
#endif
			{
				msptr += sprintf(msptr, "$%X(PC)", disp);
			}
			break;
			/************************************************************************************/
		case 3:	// Program Counter Indirect with Index
			msptr += sprintf(msptr, "$%X(PC,D%d.W)", stream[0], stream[1]);
			fetch_w();
			
			/*
			{
			struct {unsigned	type:1, reg:3, size:1, factor:2, pad:1, disp:8;}	ext;
			*(UWORD *)(&ext) = fetch_w();
			
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
				msptr += sprintf(msptr, "#%ld", (long)fetch_l());
			}
			else	// Byte/Word
			{
				msptr += sprintf(msptr, "#%d", (short)fetch_w());
			}
			break;
		}
		break;
	}
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

BOOL sup_ea(BYTE mode, BYTE reg, short adrmodes)
{
	if (mode < 7)
	{
		if (adrmodes & (1<<mode)) return TRUE;
	}
	else
	{
		if (adrmodes & (1<<(7+reg))) return TRUE;
	}

	return FALSE;
}

// Bit Manipulation/MOVEP/Immediate
void codemap00(void)
{
	if (opcode == 0x003C)	// ORI ,CCR	(done)
	{
		msptr += sprintf(msptr, "ORI.B\t");
		do_imm(0);
		msptr += sprintf(msptr, ",CCR");
		return;
	}

	if (opcode == 0x007C)	// ORI ,SR	(done)
	{
		msptr += sprintf(msptr, "ORI.W\t");
		do_imm(1);
		msptr += sprintf(msptr, ",SR");
		return;
	}

	if (opcode == 0x023C)	// ANDI ,CCR	(done)
	{
		msptr += sprintf(msptr, "ANDI.B\t");
		do_imm(0);
		msptr += sprintf(msptr, ",CCR");
		return;
	}

	if (opcode == 0x027C)	// ANDI ,SR	(done)
	{
		msptr += sprintf(msptr, "ANDI.W\t");
		do_imm(1);
		msptr += sprintf(msptr, ",SR");
		return;
	}

	if (opcode == 0x0A3E)	// EORI ,CCR	(done)
	{
		msptr += sprintf(msptr, "EORI.B\t");
		do_imm(0);
		msptr += sprintf(msptr, ",CCR");
		return;
	}

	if (opcode == 0x0A7C)	// EORI ,SR	(done)
	{
		msptr += sprintf(msptr, "EORI.W\t");
		do_imm(1);
		msptr += sprintf(msptr, ",SR");
		return;
	}

	if ((opcode & 0xFF00) == 0x0000)	// ORI	(done)
	{
	//			ATLASSERT(0);
	//	struct {unsigned	pad:8, size:2, mode: 3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE opreg = opcode & 0x7;
		BYTE opmode = (opcode>>3) & 0x7;
		BYTE opsize = (opcode>>6) & 0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "ORI.%c\t", SizeChar[opsize]);
			do_imm(opsize);
			msptr += sprintf(msptr, ",");
			do_ea(opmode, opreg, opsize);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x0200)	// ANDI	(done)
	{
				ATLASSERT(0);
		struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		if (sup_ea(op.mode, op.reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "ANDI.%c\t", SizeChar[op.size]);
			do_imm(op.size);
			msptr += sprintf(msptr, ",");
			do_ea(op.mode, op.reg, op.size);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x0400)	// SUBI	(done)
	{
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE opreg = opcode & 0x7;
		BYTE opmode = (opcode>>3) & 0x7;
		BYTE opsize = (opcode>>6) & 0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "SUBI.%c\t", SizeChar[opsize]);
			do_imm(opsize);
			msptr += sprintf(msptr, ",");
			do_ea(opmode, opreg, opsize);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x0600)	// ADDI	(done)
	{
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_size = (opcode>>6) & 0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "ADDI.%c\t", SizeChar[op_size]);
			do_imm(op_size);
			msptr += sprintf(msptr, ",");
			do_ea(op_mode, op_reg, op_size);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x0A00)	// EORI	(done)
	{
		//		ATLASSERT(0);
		//struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		//*(UWORD *)(&op) = opcode;
		BYTE opreg = opcode & 0x7;
		BYTE opmode = (opcode>>3) & 0x7;
		BYTE opsize = (opcode>>6) & 0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "EORI.%c\t", SizeChar[opsize]);
			do_imm(opsize);
			msptr += sprintf(msptr, ",");
			do_ea(opmode, opreg, opsize);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x0C00)	// CMPI	(done)
	{
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_size = (opcode>>6) & 0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "CMPI.%c\t", SizeChar[op_size]);
			do_imm(op_size);
			msptr += sprintf(msptr, ",");
			do_ea(op_mode, op_reg, op_size);
			return;
		}
	}

	if ((opcode & 0xF038) == 0x0008)	// MOVEP
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, dreg:3, t:1, opmode:2, pad1:3, areg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE opareg = opcode & 0x7;
		BYTE opmode = (opcode>>6) & 0x3;
		BYTE opt = (opcode>>8) & 0x1;
		BYTE opdreg = (opcode>>9) & 0x7;

		if (opt == 1)
		{
			UWORD	size = (opmode & 1)? 2: 1;
			UWORD	disp;

			msptr += sprintf(msptr, "MOVEP.%c\t", SizeChar[size]);

			disp = fetch_w();

			if (opmode & 2)	// From register to memory
			{
				msptr += sprintf(msptr, "D%d,($%X,A%d)", opdreg, disp, opareg);
			}
			else	// From memory to register
			{
				msptr += sprintf(msptr, "($%X,A%d),D%d", disp, opareg, opdreg);
			}

			return;
		}
	}

	if ((opcode & 0xFF00) == 0x0800)	// Static Bit
	{
		ATLASSERT(0);
		struct {unsigned	pad:8, type:2, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		msptr += sprintf(msptr, "B%s\t", BitStr[op.type]);
		msptr += sprintf(msptr, "#%d,", *(UWORD *)stream);
		fetch_l();
		do_ea(op.mode, op.reg, 1);
		return;
	}

	if ((opcode & 0xF100) == 0x0100)	// Dynamic Bit
	{
	//	struct {unsigned	pad0:4, dreg:3, pad1:1, type:2, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_type = (opcode>>6) & 0x3;
		BYTE op_dreg = (opcode>>9) & 0x7;

		msptr += sprintf(msptr, "B%s\t", BitStr[op_type]);
		msptr += sprintf(msptr, "D%d,", op_dreg);
		do_ea(op_mode, op_reg,-1);
		return;
	}

	unknown_opcode();
}

// Move Byte
void codemap01(void)
{
//	ATLASSERT(0);
//	struct {unsigned	pad:4, destreg:3, destmode:3, srcmode:3, srcreg:3;}	op;
//	*(UWORD *)(&op) = opcode;
	BYTE opsrcreg = opcode & 0x7;
	BYTE opsrcmode = (opcode>>3) & 0x7;
	BYTE opdestmode = (opcode>>6) & 0x7;
	BYTE opdestreg = (opcode>>9) & 0x7;

// All addressing modes are allowed for source

	if (sup_ea(opdestmode, opdestreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
	{
		msptr += sprintf(msptr, "MOVE.B\t");
		do_ea(opsrcmode, opsrcreg, 0);
		msptr += sprintf(msptr, ",");
		do_ea(opdestmode, opdestreg, 0);
		return;
	}

	unknown_opcode();
}

// Move Long
void codemap02(void)
{
//	struct {unsigned	pad:4, destreg:3, destmode:3, srcmode:3, srcreg:3;}	op;
//	*(UWORD *)(&op) = opcode;
	BYTE srcreg = opcode & 0x7;
	BYTE srcmode = (opcode >> 3) & 0x7;
	BYTE destmode = (opcode >> 6) & 0x7;
	BYTE destreg = (opcode >> 9) & 0x7;

// All addressing modes are allowed for source

	if (destmode == 1)	// If Address Register Direct - MOVEA
	{
		msptr += sprintf(msptr, "MOVEA.L\t");
		do_ea(srcmode, srcreg, 2);
		msptr += sprintf(msptr, ",");
		do_ea(destmode, destreg, 2);
		return;
	}
	else
	{
		if (sup_ea(destmode, destreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "MOVE.L\t");
			do_ea(srcmode, srcreg, 2);
			msptr += sprintf(msptr, ",");
			do_ea(destmode, destreg, 2);
			return;
		}
	}

	unknown_opcode();
}

// Move Word
void codemap03(void)
{
//	struct {unsigned	pad:4, destreg:3, destmode:3, srcmode:3, srcreg:3;}	op;
//	*(UWORD *)(&op) = opcode;
	BYTE srcreg = opcode & 0x7;
	BYTE srcmode = (opcode >> 3) & 0x7;
	BYTE destmode = (opcode >> 6) & 0x7;
	BYTE destreg = (opcode >> 9) & 0x7;

// All addressing modes are allowed for source

	if (destmode == 1)	// If Address Register Direct - MOVEA
	{
		msptr += sprintf(msptr, "MOVEA.W\t");
		do_ea(srcmode, srcreg, 3);
		msptr += sprintf(msptr, ",");
		do_ea(destmode, destreg, 3);
		return;
	}
	else
	{
		if (sup_ea(destmode, destreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "MOVE.W\t");
			do_ea(srcmode, srcreg, 3);
			msptr += sprintf(msptr, ",");
			do_ea(destmode, destreg, 3);
			return;
		}
	}

	unknown_opcode();
}

// Miscellaneous
// + 68020 (MULS/MULU Long)
void codemap04(void)
{
	if (opcode == 0x4E75)	// RTS
	{
		msptr += sprintf(msptr, "RTS");
		return;
	}

	if (opcode == 0x4E77)	// RTR
	{
		msptr += sprintf(msptr, "RTR");
		return;
	}

	if (opcode == 0x4E73)	// RTE
	{
		msptr += sprintf(msptr, "RTE");
		return;
	}

	if (opcode == 0x4E74)	// RTD	(MC68010/MC68012)
	{
		msptr += sprintf(msptr, "RTD");
		return;
	}

	if (opcode == 0x4E71)	// NOP
	{
		msptr += sprintf(msptr, "NOP");
		return;
	}

	if (opcode == 0x4E72)	// STOP
	{
		msptr += sprintf(msptr, "STOP");
		return;
	}

	if (opcode == 0x4E70)	// RESET
	{
		msptr += sprintf(msptr, "RESET");
		return;
	}

	if (opcode == 0x4E76)	// TRAPV
	{
		msptr += sprintf(msptr, "TRAPV");
		return;
	}

	if (opcode == 0x4AFC)	// ILLEGAL
	{
		msptr += sprintf(msptr, "ILLEGAL");
		return;
	}

	if ((opcode & 0xFFF8) == 0x4840)	// SWAP	(done)
	{
		struct {unsigned	pad:13, dreg:3;}	op;
		*(UWORD *)(&op) = opcode;

		msptr += sprintf(msptr, "SWAP\tD%d", op.dreg);
		return;
	}

	if ((opcode & 0xFFF8) == 0x4848)	// BKPT (MC68010/MC68012) (done)
	{
		ATLASSERT(0);
		struct {unsigned	pad:13, bkpt:3;}	op;
		*(UWORD *)(&op) = opcode;

		msptr += sprintf(msptr, "BKPT\t#%d", op.bkpt);
		return;
	}

	if ((opcode & 0xFFF8) == 0x4E50)	// LINK (done)
	{
		//struct {unsigned	pad:13, areg:3;}	op;
		//*(UWORD *)(&op) = opcode;
		BYTE areg = opcode & 0x7;

		msptr += sprintf(msptr, "LINK\tA%d,%d", areg, (short)fetch_w());
		return;
	}

	if ((opcode & 0xFFF8) == 0x4E58)	// UNLK (done)
	{
	//	struct {unsigned	pad:13, areg:3;}	op;
//		*(UWORD *)(&op) = opcode;
		BYTE areg = opcode & 0x7;

		msptr += sprintf(msptr, "UNLK\tA%d", areg);
		return;
	}

	if ((opcode & 0xFFC0) == 0x4E80)	// JSR	(done)
	{
	//	struct {unsigned	pad:10, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE reg = opcode & 0x7;
		BYTE mode = (opcode >> 3) & 0x7;

		if (sup_ea(mode, reg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_4|ADM_11)))
		{
			msptr += sprintf(msptr, "JSR\t");
			do_ea(mode, reg,-1);
			return;
		}
	}

	if ((opcode & 0xFFC0) == 0x4EC0)	// JMP	(done)
	{
		ATLASSERT(0);
		struct {unsigned	pad:10, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		if (sup_ea(op.mode, op.reg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_4|ADM_11)))
		{
			msptr += sprintf(msptr, "JMP\t");
			do_ea(op.mode, op.reg,-1);
			return;
		}
	}

	if ((opcode & 0xFFC0) == 0x4AC0)	// TAS	(done)
	{
		ATLASSERT(0);
		struct {unsigned	pad:10, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		if (sup_ea(op.mode, op.reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "TAS\t");
			do_ea(op.mode, op.reg, 0);
			return;
		}
	}

	if ((opcode & 0xFFC0) == 0x4840)	// PEA	(done)
	{
	//	struct {unsigned	pad:10, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_4|ADM_11)))
		{
			msptr += sprintf(msptr, "PEA\t");
			do_ea(op_mode, op_reg, 2);
			return;
		}
	}

	if ((opcode & 0xFFC0) == 0x4800)	// NBCD	(done)
	{
		ATLASSERT(0);
		struct {unsigned	pad:10, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		if (sup_ea(op.mode, op.reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "NBCD\t");
			do_ea(op.mode, op.reg, 0);
			return;
		}
	}

	if ((opcode & 0xFFC0) == 0x4800)	// MOVE to SR	(done)
	{
		ATLASSERT(0);
		struct {unsigned	pad:10, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		if (sup_ea(op.mode, op.reg, ADM_ALL & ~ADM_1))
		{
			msptr += sprintf(msptr, "MOVE\t");
			do_ea(op.mode, op.reg, 1);
			msptr += sprintf(msptr, ",SR");
			return;
		}
	}

	if ((opcode & 0xFE38) == 0x4800)	// EXT (done)
	{
	//	struct {unsigned	pad0:7, type:3, pad1:3, dreg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_dreg = opcode & 0x7;
		BYTE op_type = (opcode>>6) & 0x7;

		msptr += sprintf(msptr, "EXT.%c\t", SizeChar[op_type-1]);
		msptr += sprintf(msptr, "D%d", op_dreg);
		return;
	}

	if ((opcode & 0xFB80) == 0x4880)	// MOVEM (done)
	{
	//	struct {unsigned	pad0:5, dir:1, pad1:3, size:1, mode:3, reg:3;}	op;
	//	struct {unsigned	pad0:5, dir:1, pad1:3, size:1, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = ENDIANWORD(opcode);
		BYTE opreg = opcode & 0x7;
		BYTE opmode = (opcode>>3)&0x7;
		BYTE opsize = (opcode>>6)&0x1;
		BYTE opdir = (opcode>>10)&0x1;

		if (((opdir == 0) && (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_9|ADM_10|ADM_11)))) ||
			((opdir == 1) && (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_0|ADM_1|ADM_4|ADM_11)))))
		{
			UWORD	regmask = fetch_w();

			msptr += sprintf(msptr, "MOVEM.%c\t", SizeChar[opsize+1]);

			if (opdir == 1)	// Memory to Register
			{
				do_ea(opmode, opreg, opsize);
				msptr += sprintf(msptr, ",");

				bool bPrev = false;

				for (int n = 0; n < 16; n++)
				{
					int i = n;

					if (i < 8)
					{
						if (regmask & (1<<i))
						{
							if (bPrev) msptr += sprintf(msptr, ",");
							msptr += sprintf(msptr, "D%d", i);
							bPrev = true;
						}
					}
					else
					{
						if (regmask & (1<<i))
						{
							if (bPrev) msptr += sprintf(msptr, ",");
							msptr += sprintf(msptr, "A%d", i-8);
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
							if (bPrev) msptr += sprintf(msptr, ",");
							msptr += sprintf(msptr, "D%d", i);
							bPrev = true;
						}
					}
					else
					{
						if (regmask & (1<<(15-i)))
						{
							if (bPrev) msptr += sprintf(msptr, ",");
							msptr += sprintf(msptr, "A%d", i-8);
							bPrev = true;
						}
					}
				}

				msptr += sprintf(msptr, ",");
				do_ea(opmode, opreg, opsize);
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
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x4A00)	// TST	(done)
	{
	//	struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_size = (opcode>>6) & 0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "TST.%c\t",SizeChar[op_size]);
			do_ea(op_mode, op_reg, op_size);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x4600)	// NOT (done)
	{
			//	ATLASSERT(0);
		//struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		//*(UWORD *)(&op) = opcode;
		BYTE opreg = opcode & 0x7;
		BYTE opmode = (opcode>>3) & 0x7;
		BYTE opsize = (opcode>>6) & 0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "NOT.%c\t", SizeChar[opsize]);
			do_ea(opmode, opreg, opsize);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x4400)	// NEG	(done)
	{
//		struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
//		*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_size = (opcode>>6) & 0x3;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "NEG.%c\t", SizeChar[op_size]);
			do_ea(op_mode, op_reg, op_size);
			return;
		}
	}

	if ((opcode & 0x41C0) == 0x41C0)	// LEA	(done)
	{
	//			ATLASSERT(0);
	//	struct {unsigned	pad0:4, areg:3, pad1:3, mode:3, reg:3;}	op;
		//*(UWORD *)(&op) = opcode;
		BYTE opreg = opcode&0x7;
		BYTE opmode = (opcode>>3)&0x7;
		BYTE opareg = (opcode>>9)&0x7;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_0|ADM_1|ADM_3|ADM_4|ADM_9)))
		{
			msptr += sprintf(msptr, "LEA\t");
			do_ea(opmode, opreg, 2);
			msptr += sprintf(msptr, ",A%d", opareg);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x4200)	// CLR	(done)
	{
		//struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		//*(UWORD *)(&op) = opcode;
		BYTE opreg = opcode & 0x7;
		BYTE opmode = (opcode>>3)&0x7;
		BYTE opsize = (opcode>>6)&0x3;

		if (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "CLR.%c\t", SizeChar[opsize]);
			do_ea(opmode, opreg, opsize);
			return;
		}
	}

	if ((opcode & 0xFF00) == 0x4000)	// NEGX	(done)
	{
				ATLASSERT(0);
		struct {unsigned	pad:8, size:2, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		if (sup_ea(op.mode, op.reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "NEGX.%c\t", SizeChar[op.size]);
			do_ea(op.mode, op.reg, op.size);
			return;
		}
	}

	if ((opcode & 0xF040) == 0x4000)	// CHK	(done)
	{
		struct {unsigned	pad0:4, dreg:3, size:2, pad1:1, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		if (sup_ea(op.mode, op.reg, ADM_ALL & ADM_1))
		{
			UWORD	size = (op.size == 3)? 1: 2;

			msptr += sprintf(msptr, "CHK.%c\t", SizeChar[size]);
			do_ea(op.mode, op.reg, size);
			msptr += sprintf(msptr, ",D%d", op.dreg);
			return;
		}
	}

	unknown_opcode();
}

// ADDQ/SUBQ/Scc/DBcc
void codemap05(void)
{
	if ((opcode & 0xF0F8) == 0x50C8)	// DBcc	(done)
	{
		struct {unsigned	pad0:4, condition:4, pad1:5, dreg:3;}	op;
		*(UWORD *)(&op) = opcode;

		msptr += sprintf(msptr, "DB%s\t", CondTest[op.condition]);
		msptr += sprintf(msptr, "D%d,", op.dreg);

		msptr += sprintf(msptr, "%d", (WORD)fetch_w());

		return;
	}

	if ((opcode & 0xFFC0) == 0x50C0)	// Scc	(done)
	{
		struct {unsigned	pad0:4, condition:4, pad1:2, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		if (sup_ea(op.mode, op.reg, ADM_ALL & ~(ADM_1|ADM_9|ADM_10|ADM_11)))
		{
			msptr += sprintf(msptr, "S%s\t", CondTest[op.condition]);
			do_ea(op.mode, op.reg,-1);
			return;
		}
	}

	if ((opcode & 0xF100) == 0x5000)	// ADDQ	(done)
	{
		//struct {unsigned	pad0:4, data:3, pad1:1, size:2, mode: 3, reg:3;}	op;
		//*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_size = (opcode>>6) & 0x3;
		BYTE op_data = (opcode>>9) & 0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_9|ADM_10|ADM_11)))
		{
			UWORD	data = (op_data)? op_data: 8;

			msptr += sprintf(msptr, "ADDQ.%c\t#%d,", SizeChar[op_size], data);
			do_ea(op_mode, op_reg, op_size);
			return;
		}
	}

	if ((opcode & 0xF100) == 0x5100)	// SUBQ	(done)
	{
	//	struct {unsigned	pad0:4, data:3, pad1:1, size:2, mode: 3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_size = (opcode>>6) & 0x3;
		BYTE op_data = (opcode>>9) & 0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~(ADM_9|ADM_10|ADM_11)))
		{
			UWORD	data = (op_data)? op_data: 8;

			msptr += sprintf(msptr, "SUBQ.%c\t#%d,", SizeChar[op_size], data);
			do_ea(op_mode, op_reg, op_size);
			return;
		}
	}

	unknown_opcode();
}

// Bcc/BSR
void codemap06(void)
{
	if ((opcode & 0xFF00) == 0x6100)	// BSR	(done)
	{
//		struct {unsigned	pad:8, disp8:8;}	op;
//		*(UWORD *)(&op) = opcode;
		char op_disp8 = opcode & 0xFF;

		msptr += sprintf(msptr, "BSR.%c\t", SizeChar[(op_disp8)? 0: 1]);

		if (op_disp8 == 0)	// Allows for 16bit displacement in extension word
		{
			WORD	disp16 = fetch_w();

			msptr += sprintf(msptr, "%d", disp16);
		}
		else
		{
			msptr += sprintf(msptr, "%d", op_disp8);
		}

		return;
	}

	if ((opcode & 0xF000) == 0x6000)	// Bcc/BRA	(done)
	{
		//struct {unsigned	pad0:4, condition:4; signed disp8:8;}	op;
		//*(UWORD *)(&op) = opcode;
		char op_disp8 = opcode & 0xFF;
		BYTE op_condition = (opcode >> 8) & 0xF;

		if (op_condition != 1)	// Always False (not available for this instruction)
		{
			if (op_condition == 0)	// Always True
				msptr += sprintf(msptr, "BRA.%c\t", SizeChar[(op_disp8)? 0: 1]);
			else
				msptr += sprintf(msptr, "B%s.%c\t", CondTest[op_condition], SizeChar[(op_disp8)? 0: 1]);

			if (op_disp8 == 0)	// Allows for 16bit displacement in extension word
			{
				short	disp16 = fetch_w();

				msptr += sprintf(msptr, "%d", counter-2 + disp16);
			}
			else
			{
				msptr += sprintf(msptr, "%d", counter + op_disp8);
			}

			return;
		}
	}

	unknown_opcode();
}

// MOVEQ
void codemap07(void)	// (done)
{
	//struct {unsigned	pad0:4, dreg:3, pad1:1, data:8;}	op;
	char data = opcode&0xFF;
	char dreg = (opcode>>9)&0x7;

	msptr += sprintf(msptr, "MOVEQ\t#%d,D%d", data, dreg);

	return;
}

// OR/DIV/SBCD
void codemap08(void)
{
	if ((opcode & 0xF1F0) == 0x8100)	// SBCD
	{
	}

	if ((opcode & 0xF0C0) == 0x80C0)	// DIVU/DIVS Word
	{
		//struct {unsigned	pad0:4, dreg:3, type:1, pad1:2, mode:3, reg:3;}	op;
		//*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_type = (opcode>>8) & 0x1;
		BYTE op_dreg = (opcode>>9) & 0x7;

		if (sup_ea(op_mode, op_reg, ADM_ALL & ~ADM_1))
		{
			if (op_type)
				msptr += sprintf(msptr, "DIVS.W\t");
			else
				msptr += sprintf(msptr, "DIVU.W\t");

			do_ea(op_mode, op_reg, 1);
			msptr += sprintf(msptr, ",D%d", op_dreg);
			return;
		}
	}

	if	(1) // OR	(done)
	{
	//	struct {unsigned	pad:4, dreg:3, t:1, size:2, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE opreg = opcode & 0x7;
		BYTE opmode = (opcode>>3) & 0x7;
		BYTE opsize = (opcode>>6) & 0x3;
		BYTE opt = (opcode>>8) & 0x1;
		BYTE opdreg = (opcode>>9) & 0x7;

		if (((opt == 0) && (sup_ea(opmode, opreg, ADM_ALL & ~ADM_1))) ||
			((opt == 1) && (sup_ea(opmode, opreg, ADM_ALL & ~(ADM_0|ADM_1|ADM_9|ADM_10|ADM_11)))))
		{
			msptr += sprintf(msptr, "OR.%c\t", SizeChar[opsize]);

			if (opt)	// Dn,<ea>
			{
				msptr += sprintf(msptr, "D%d,", opdreg);
				do_ea(opmode, opreg, opsize);
			}
			else	// <ea>,Dn
			{
				do_ea(opmode, opreg, opsize);
				msptr += sprintf(msptr, ",D%d", opdreg);
			}

			return;
		}
	}

	unknown_opcode();
}

// SUB/SUBX
void codemap09(void)
{
//	struct {unsigned	pad0:4, rx:3, pad1:1, size:2, pad2:2, rm:1, ry:3;}	op;
//	*(UWORD *)(&op) = opcode;

	BYTE op_size = (opcode>>6) & 0x3;
	if (((opcode & 0xF130) == 0x9100) && (op_size < 3))	// SUBX
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, rx:3, pad1:1, size:2, pad2:2, rm:1, ry:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_rx = opcode & 0x7;
		BYTE op_rm = (opcode>>3) & 0x1;
		BYTE op_ry = (opcode>>9) & 0x7;

		msptr += sprintf(msptr, "SUBX.%c\t", SizeChar[op_size]);

		if (op_rm)
			msptr += sprintf(msptr, "-(A%d),-(A%d)", op_ry, op_rx);
		else
			msptr += sprintf(msptr, "D%d,D%d", op_ry, op_rx);

		return;
	}

	if (1)	// SUB/SUBA
	{
	//	struct {unsigned	pad:4, dareg:3, opmode:3, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_opmode = (opcode>>6) & 0x7;
		BYTE op_dareg = (opcode>>9) & 0x7;

		if ((op_opmode == 3) || (op_opmode == 7))	// SUBA
		{
			UWORD	size = ((op_opmode == 3)? 1: 2);

			msptr += sprintf(msptr, "SUBA.%c\t", SizeChar[size]);
			do_ea(op_mode, op_reg, size);
			msptr += sprintf(msptr, ",A%d", op_dareg);
		}
		else	// SUB
		{
		//	struct {unsigned	pad:4, dreg:3, t:1, size:2, mode:3, reg:3;}	op;
		//	*(UWORD *)(&op) = opcode;
			BYTE op_size = (opcode>>6) & 0x3;
			BYTE op_t = (opcode>>8) & 0x1;

			msptr += sprintf(msptr, "SUB.%c\t", SizeChar[op_size]);

			if (op_t)	// <Dn>,<ea>
			{
				msptr += sprintf(msptr, "D%d,", op_dareg);
				do_ea(op_mode, op_reg, op_size);
			}
			else	// <ea>,<Dn>
			{
				do_ea(op_mode, op_reg, op_size);
				msptr += sprintf(msptr, ",D%d", op_dareg);
			}
		}

		return;
	}

	unknown_opcode();
}

// (Unnassigned, Reserved)
void codemap10(void)
{
	unknown_opcode();
}

// CMP/EOR
void codemap11(void)
{
	if ((opcode & 0xF138) == 0xB108)	// CMPM
	{
		ATLASSERT(0);
		struct {unsigned	pad0:4, ax:3, pad1:1, size:2, pad2:3, ay:3;}	op;
		*(UWORD *)(&op) = opcode;

		msptr += sprintf(msptr, "CMPM.%c\t(A%d)+,(A%d)+", SizeChar[op.size], op.ay, op.ax);
		return;
	}

	if ((opcode & 0xF000) == 0xB000)	// CMP/CMPA/EOR
	{
	//	struct {unsigned	pad:4, adreg:3, opmode:3, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE oreg = opcode & 0x7;
		BYTE omode = (opcode>>3) & 0x7;
		BYTE oopmode = (opcode>>6) & 0x7;
		BYTE oadreg = (opcode>>9) & 0x7;

		if ((oopmode >= 4) && (oopmode <= 6))	// EOR
		{
			UWORD	size = oopmode-4;

			msptr += sprintf(msptr, "EOR.%c\t", SizeChar[size]);
			msptr += sprintf(msptr, "D%d,", oadreg);
			do_ea(omode, oreg, size);
		}
		else
		{
			if (oopmode < 3)	// CMP
			{
				msptr += sprintf(msptr, "CMP.%c\t", SizeChar[oopmode]);
				do_ea(omode, oreg, oopmode);
				msptr += sprintf(msptr, ",D%d", oadreg);
			}
			else	// CMPA
			{
				UWORD	size = (oopmode == 3)? 1: 2;

				msptr += sprintf(msptr, "CMPA.%c\t", SizeChar[size]);
				do_ea(omode, oreg, size);
				msptr += sprintf(msptr, ",A%d", oadreg);
			}
		}

		return;
	}

	unknown_opcode();
}

// AND/MUL/ABCD/EXG
void codemap12(void)
{
	if ((opcode & 0xF1F0) == 0xC100)	// ABCD
	{
		ATLASSERT(0);
		struct {unsigned	pad0:4, rx:3, pad1:5, rm:1, ry:3;}	op;
		*(UWORD *)(&op) = opcode;

		msptr += sprintf(msptr, "ABCD\t");

		if (op.rm)	// -(Ay),-(Ax)
			msptr += sprintf(msptr, "-(A%d),-(A%d)", op.ry, op.rx);
		else	// Dy,Dx
			msptr += sprintf(msptr, "D%d,D%d", op.ry, op.rx);

		return;
	}

	if ((opcode & 0xF100) == 0xC100)	// EXG
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, rx:3, pad1:1, opmode:5, ry:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_ry = opcode & 0x7;
		BYTE op_opmode = (opcode>>3) & 0x1f;
		BYTE op_rx = (opcode>>9) & 0x7;

		if (op_opmode == 0x8)	// exg data registers
		{
			msptr += sprintf(msptr, "EXG\t");
			msptr += sprintf(msptr, "D%d,D%d", op_rx, op_ry);
			return;
		}
		else if (op_opmode == 0x9)	// exg address registers
		{
			msptr += sprintf(msptr, "EXG\t");
			msptr += sprintf(msptr, "A%d,A%d", op_rx, op_ry);
			return;
		}
		else if (op_opmode == 0x11)	// exg data register and address register
		{
			msptr += sprintf(msptr, "EXG\t");
			msptr += sprintf(msptr, "D%d,A%d", op_rx, op_ry);
			return;
		}
	}

	if ((opcode & 0xF0C0) == 0xC0C0)	// MULU/MULS Word
	{
//		ATLASSERT(0);
//		struct {unsigned	pad0:4, dreg:3, type:1, pad1:2, mode:3, reg:3;}	op;
//		*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_type = (opcode>>8) & 0x1;
		BYTE op_dreg = (opcode>>9) & 0x7;

		if (op_type)	msptr += sprintf(msptr, "MULS\t");	else msptr += sprintf(msptr, "MULU\t");
		do_ea(op_mode, op_reg, 1);	// Word
		msptr += sprintf(msptr, ",D%d", op_dreg);

		return;
	}

	if ((opcode & 0xF000) == 0xC000)	// AND
	{
		ATLASSERT(0);
		struct {unsigned	pad:4, dreg:3, t:1, size:2, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		msptr += sprintf(msptr, "AND.%c\t", SizeChar[op.size]);

		if (op.t)	// Dn,<ea>
		{
			msptr += sprintf(msptr, "D%d,", op.dreg);
			do_ea(op.mode, op.reg, op.size);
		}
		else	// <ea>,Dn
		{
			do_ea(op.mode, op.reg, op.size);
			msptr += sprintf(msptr, ",D%d", op.dreg);
		}
		return;
	}

	unknown_opcode();
}

// ADD/ADDX
void codemap13(void)
{
//	struct {unsigned	pad0:4, rx:3, pad1:1, size:2, pad2:2, rm:1, ry:3;}	op;
//	*(UWORD *)(&op) = opcode;
	BYTE op_size = (opcode>>6) & 0x3;

	if (((opcode & 0xF130) == 0xD100) && (op_size < 3))	// ADDX
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad0:4, rx:3, pad1:1, size:2, pad2:2, rm:1, ry:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_ry = opcode & 0x7;
		BYTE op_rm = (opcode>>3) & 0x1;
		BYTE op_size = (opcode>>6) & 0x3;
		BYTE op_rx = (opcode>>9) & 0x7;

		msptr += sprintf(msptr, "ADDX.%c\t", SizeChar[op_size]);

		if (op_rm)
			msptr += sprintf(msptr, "-(A%d),-(A%d)", op_ry, op_rx);
		else
			msptr += sprintf(msptr, "D%d,D%d", op_ry, op_rx);

		return;
	}
	else	// ADD/ADDA
	{
	//	struct {unsigned	pad:4, dareg:3, opmode:3, mode:3, reg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_reg = opcode & 0x7;
		BYTE op_mode = (opcode>>3) & 0x7;
		BYTE op_opmode = (opcode>>6) & 0x7;
		BYTE op_dareg = (opcode>>9) & 0x7;

		if ((op_opmode == 3) || (op_opmode == 7))	// ADDA
		{
			UWORD	size = ((op_opmode == 3)? 1: 2);

			msptr += sprintf(msptr, "ADDA.%c\t", SizeChar[size]);
			do_ea(op_mode, op_reg, size);
			msptr += sprintf(msptr, ",A%d", op_dareg);

			return;
		}
		else	// ADD
		{
			//struct {unsigned	pad:4, dreg:3, t:1, size:2, mode:3, reg:3;}	op;
			BYTE reg = opcode & 0x7;
			BYTE mode = (opcode >> 3) & 0x7;
			BYTE size = (opcode >> 6) & 0x3;
			BYTE t = (opcode >> 8) & 0x1;
			BYTE dreg = (opcode >> 9) & 0x7;

			msptr += sprintf(msptr, "ADD.%c\t", SizeChar[size]);

			if (t)	// <Dn>,<ea>
			{
				msptr += sprintf(msptr, "D%d,", dreg);
				do_ea(mode, reg, size);
			}
			else	// <ea>,<Dn>
			{
				do_ea(mode, reg, size);
				msptr += sprintf(msptr, ",D%d", dreg);
			}

			return;
		}
	}

	unknown_opcode();
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
void codemap14(void)
{
	if ((opcode & 0xF8C0) == 0xE0C0)	// SHIFT/ROTATE - Memory
	{
		ATLASSERT(0);
		struct {unsigned	pad0:5, type:2, dir:1, pad1:2, mode:3, reg:3;}	op;
		*(UWORD *)(&op) = opcode;

		msptr += sprintf(msptr, "%s%c", ShiftRot[op.type], ShRoDir[op.dir]);

		msptr += sprintf(msptr, "\t");
		do_ea(op.mode, op.reg, 2);
	}
	else if ((opcode & 0xF000) == 0xE000)	// SHIFT/ROTATE - Register
	{
	//	ATLASSERT(0);
	//	struct {unsigned	pad:4, cr:3, dir:1, size:2, ir:1, type:2, dreg:3;}	op;
	//	*(UWORD *)(&op) = opcode;
		BYTE op_dreg = opcode & 0x7;
		BYTE op_type = (opcode>>3) & 0x3;
		BYTE op_ir = (opcode>>5) & 0x1;
		BYTE op_size = (opcode>>6) & 0x3;
		BYTE op_dir = (opcode>>8) & 0x1;
		BYTE op_cr = (opcode>>9) & 0x7;

		msptr += sprintf(msptr, "%s%c", ShiftRot[op_type], ShRoDir[op_dir]);
		msptr += sprintf(msptr, ".%c\t", SizeChar[op_size]);
		if (op_ir)
			msptr += sprintf(msptr, "D%d,", op_cr);
		else
			msptr += sprintf(msptr, "#%d,", (op_cr==0)?8:op_cr);
		msptr += sprintf(msptr, "D%d", op_dreg);
	}
	else
	{
		unknown_opcode();
	}
}

// Coprocessor interface (MC68020)
void codemap15(void)
{
	BYTE coid = (opcode>>9) & 0x7;

	if (coid == 1)
	{
		int eareg = opcode & 0x7;
		int eamode = (opcode>>3) & 0x7;

		UWORD word = fetch_w();

		BYTE RM = (word>>14) & 0x1;
		BYTE reg = (word>>7) & 0x7;
		BYTE src_specifier = (word>>10) & 0x7;

		if (RM == 0)
		{
			ATLASSERT(eareg == 0);
			ATLASSERT(eamode == 0);
		}

		if ((word & 0x7F) == 0x0)
		{
			/*
0000000 FMOVE Rounding precision specified by the floating-point
control register.
1000000 FSMOVE Single-precision rounding specified.
1000100 FDMOVE Double-precision rounding specified.
*/
			msptr += sprintf(msptr, "FMOVE\t");

			if (word & (1<<13))	// register -> EA
			{
				msptr += sprintf(msptr, "F%d,", reg);
				if (RM == 1)
				{
					do_ea(eamode, eareg, 1);
				}
				else
				{
				}
			}
			else	// EA -> register
			{
				if (RM == 1)
				{
					do_ea(eamode, eareg, 1);
				}
				else
				{
				}
				msptr += sprintf(msptr, ",F%d", reg);
			}

		}
		else if ((word & 0x7F) == 0x1)
		{
			msptr += sprintf(msptr, "FINT\t");

			if (RM == 1)
			{
				do_ea(eamode, eareg, 1);
			}
		}
		else if ((word & 0x7F) == 0x3)
		{
			msptr += sprintf(msptr, "FINTRZ\t");

			if (RM == 1)
			{
				do_ea(eamode, eareg, 1);
			}

			msptr += sprintf(msptr, ",F%d", reg);
		}
		else if ((word & 0x7F) == 0x1F)
		{
			msptr += sprintf(msptr, "FGETMAN\t");

			if (RM == 1)
			{
				do_ea(eamode, eareg, 1);
			}
		}
		else
		{
			msptr += sprintf(msptr, "fop\t");

			if (RM == 1)
			{
				do_ea(eamode, eareg, 1);
			}
		}
	}
	else
		unknown_opcode();
}

void unknown_opcode(void)
{
	msptr += sprintf(msptr, "dc.w\t%4X\t;\"%.4s\"", opcode, &opcode);
}

void (*CodeMapFunc[])() =
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
