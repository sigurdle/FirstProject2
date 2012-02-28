#ifndef __X86_H_
#define __X86_H_

#include "LFC/disasm.h"

namespace System
{

class x86instr;

class CodeCompExt X86Context : public MContext
{
public:
	uint8 operand_size;
};

CodeCompExt x86instr* disasm_x86(X86Context* c);
//void ReadCode_x86(DWORD base, BYTE* code, long size);

}	// System

#endif // __X86_H_
