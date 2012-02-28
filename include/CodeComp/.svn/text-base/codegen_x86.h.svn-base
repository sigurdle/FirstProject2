#ifndef __codegen_x86_h_
#define __codegen_x86_h_

#include "codegen.h"

#if 0
//namespace cpp
//{

class CodeCompExt CCodeGenx86 : public CCodeGenerator
{
public:
	CCodeGenx86()
	{
		m_processor_id = CPU_IX86;
		m_line = 0;
	}

//	void amode(int r32, int RM, long displacement = 0);
	void amode(AS_instr* instr, int r32, int Mod, int RM, uint8 SIB = -1, long displacement = -1);
//	void mov_r32_imm32(int rd, long value);
//	void mov_r32_rm32(AS_instr* instr, int r32, int Mod, int RM, long displacement = 0);
//	void mov_rm32_imm32(AS_instr* instr, int Mod, int RM, long displacement, long imm32);
//	void lea_r32_rm32_disp(AS_instr* instr, int r32, int RM, long displacement = 0);
//	void push_imm(long value);
//	void or_imm(int reg, long value);

	Temp_temp** munchExpression(CFunctionCode* pFun, T_Exp* e);
	void munchStatement(CFunctionCode* pFun, T_Stm* s);

	virtual void Function_Prologue(CFunctionCode* pFunc);
	virtual void Function_Epilogue(CFunctionCode* pFunc);
	virtual void WriteStatement(CFunctionCode* pFunc, T_Stm* pstmt);

	int m_line;
};
#endif

//}	// cpp

#endif // __codegen_x86_h_
