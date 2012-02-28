#ifndef __codegen_m68k_h_
#define __codegen_m68k_h_

#include "codegen.h"

//namespace cpp
//{

namespace System
{

#define SIZE_B	1
#define SIZE_W	3
#define SIZE_L	2

enum
{
	dreg_0 = 0,
	dreg_1,
	dreg_2,
	dreg_3,
	dreg_4,
	dreg_5,
	dreg_6,
	dreg_7,
};

enum
{
	areg_0 = 0,
	areg_1,
	areg_2,
	areg_3,
	areg_4,
	areg_5,
	areg_6,
	areg_7,
};

enum
{
	reg_d0 = 0,
	reg_d1,
	reg_d2,
	reg_d3,
	reg_d4,
	reg_d5,
	reg_d6,
	reg_d7,

	reg_a0,
	reg_a1,
	reg_a2,
	reg_a3,
	reg_a4,
	reg_a5,
	reg_a6,
	reg_a7,
};

#define COND_CC	4
#define COND_CS	5
#define COND_NE	6
#define COND_EQ	7
#define COND_VC	8
#define COND_VS	9
#define COND_PL	10
#define COND_MI	11
#define COND_GE	12
#define COND_LT	13
#define COND_GT	14
#define COND_LE	15

#define CMPOP_DN_BYTE	0
#define CMPOP_DN_WORD	1
#define CMPOP_DN_LONG	2
#define CMPOP_AN_WORD	3
#define CMPOP_AN_LONG	7

class CodeCompExt CCodeGen68k : public CCodeGenerator
{
public:
	CCodeGen68k()
	{
		m_processor_id = CPU_M68K;

//		m_regsinuse = 0;

		for (int i = 0; i < 16; i++)
		{
			m_regsinuse[i] = NULL;
		}
	}

	std::FILE* fileout;

	void de(Temp_temp* temp);

	Temp_temp* m_regsinuse[16];
//	WORD m_regsinuse;

	int AllocAnyRegister(Temp_temp* temp, int n = -1)
	{
		if (n == -1)
		{
			for (int i = 0; i < 16; i++)
			{
				if (m_regsinuse[i] == NULL)
				{
					m_regsinuse[i] = temp;
					return i;
				}
			}

			std::printf("No free registers");
			ASSERT(0);
			return -1;
		}
		else
		{
			ASSERT(m_regsinuse[n] == NULL);
			m_regsinuse[n] = temp;
			return n;
		}
	}

	int AllocDataRegister(Temp_temp* temp, int n = -1)
	{
		if (n == -1)
		{
			// Hack, start to search from 1 since d0 is result of function calls
			for (int i = 1; i < 8; i++)
			{
				if (m_regsinuse[i] == NULL)
				{
					m_regsinuse[i] = temp;
					return i;
				}
			}

			std::printf("No free registers");
			ASSERT(0);
			return -1;
		}
		else
		{
			ASSERT(n < 8);
			ASSERT(m_regsinuse[n] == NULL);
			m_regsinuse[n] = temp;
			return n;
		}
	}

	int AllocAddrRegister(Temp_temp* temp, int n = -1)
	{
		if (n == -1)
		{
			for (int i = 8; i < 16; i++)
			{
				if (m_regsinuse[i] == NULL)
				{
					m_regsinuse[i] = temp;
					return i;
				}
			}

			std::printf("No free registers");
			ASSERT(0);
			return -1;
		}
		else
		{
			ASSERT(n >= 8);
			if (n != 13)	// a5
				ASSERT(m_regsinuse[n] == NULL);
			m_regsinuse[n] = temp;
			return n;
		}
	}

	void FreeRegister(int n)
	{
		ASSERT(m_regsinuse[n] != NULL);
		m_regsinuse[n] = NULL;
	}

	void link(int areg, long displacement);
	void unlk(int areg);
	void jsr(uint8 mode, uint8 reg);
	void rts();
	void move(int size, int src_mode, int src_reg, int dst_mode, int dst_reg);
	void lea(int an, int mode, int reg);
	void movem(int dir, int size, int mode, int reg);
	void bcc(int cond);
	void cmp(int reg, int cmpop, int eamode, int eareg);
	void cmpi(long data, int size, int eamode, int eareg);
	void moveq(char data, int dn);
	void addq(int data, int size, int eamode, int eareg);
	void addi(int data, int size, int eamode, int eareg);
	void subq(int data, int size, int eamode, int eareg);
	void add(int opmode, int dn, int eamode, int eareg);
	void adda(int opmode, int an, int eamode, int eareg);
	void sub(int opmode, int dn, int eamode, int eareg);
	void muls(int dn, int eamode, int eareg);
	void divu(int dn, int eamode, int eareg);
	void clr(int size, int eamode, int eareg);
	void ext(int dn, int opmode);
	void jmp(int eamode, int eareg);
	void logic_shift(int dr, int size, int ir, int cr, int reg);

	Temp_temp** munchExpression(CFunctionCode* pFun, T_Exp* e);
	void munchStatement(CFunctionCode* pFun, T_Stm* s);

public:
	virtual void WriteStatement(CFunctionCode* pFunc, T_Stm* pstmt);
	virtual void Function_Prologue(CFunctionCode* pFunc);
	virtual void Function_Epilogue(CFunctionCode* pFunc);

	void WriteStatement2(CFunctionCode* pFun, T_Stm* s);
	void CCodeGen68k::munchStatement2(CFunctionCode* pFun, T_Stm* s);
	Temp_temp** munchExpression2(CFunctionCode* pFun, T_Exp* e);
};

//}	// cpp
}

#endif // __codegen_m68k_h_
