#ifndef __codegen_ppc_h_
#define __codegen_ppc_h_

#include "codegen.h"

namespace System
{
//namespace cpp
//{

class CodeCompExt CCodeGenPPC : public CCodeGenerator
{
public:
	CCodeGenPPC()
	{
		m_processor_id = CPU_PPC;
	}

	Temp_temp* munchExpression(CFunctionCode* pFun, T_Exp* e);
	void munchStatement(CFunctionCode* pFun, T_Stm* s);

	void blr();
	void trap();
	void li(int RT, int RA, int SI);
	void addi(int RT, int RA, int SI);

	virtual void Function_Prologue(CFunctionCode* pFunc);
	virtual void Function_Epilogue(CFunctionCode* pFunc);
	virtual void WriteStatement(CFunctionCode* pFunc, T_Stm* pstmt);
};

//}	// cpp
}

#endif // __codegen_ppc_h_
