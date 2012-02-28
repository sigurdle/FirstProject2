#include "stdafx.h"
#include "codegen_ppc.h"
#include "ppcassem.h"

namespace System
{
using namespace std;

void fput8(FILE* fp, uint8 v);
void fput16(FILE* fp, uint16 v);
void fput32(FILE* fp, uint32 v);

//namespace cpp
//{

void CCodeGenPPC::blr()
{
//	fput32(fileout, 0x4E800020);	// blr // TODO, this is a shortcut for something
}

void CCodeGenPPC::trap()
{
//	fput32(fileout, 0x7FE00008);	// trap	// TODO, this is a shortcut for something
}

void CCodeGenPPC::li(int RT, int RA, int SI)
{
	addi(RT, 0, SI);
}

void CCodeGenPPC::addi(int RT, int RA, int SI)
{
	uint32 dword;
	dword |= 14<<26;
	dword |= RT<<21;
	dword |= RA<<16;
	dword |= SI;

//	fput32(fileout, dword);
}

// virtual
void CCodeGenPPC::Function_Prologue(CFunctionCode* pFun)
{
	/*
	mflr        r0,                     # extract return address 
   stw         r0,8(SP)                # save the return address
   stwu        SP, -spaceToSave(SP)    # skip over caller save
	*/
}

// virtual
void CCodeGenPPC::Function_Epilogue(CFunctionCode* pFun)
{
	/*
	lwz         r0,spaceToSave(SP)+8    # get the return address
   mtlr        R0                      #   into the Link Register
   addic       SP,SP,spaceToSave       # restore stack pointer
   blr                                 # and branch to the return address
	*/
	blr();
}

// virtual
void CCodeGenPPC::WriteStatement(CFunctionCode* pFun, T_Stm* s)
{
//	munchStatement(pFun, s);
}

//}	// cpp

}
