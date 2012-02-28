#include "stdafx.h"
//#include "Movie.h"
#include "ActionScript.h"

namespace System
{
namespace ActionScripting
{

ActionScriptFunction::ActionScriptFunction()
{
	m_codeData = NULL;
	m_pContext = NULL;
}

void ActionScriptFunction::dispatch(VM* vm, StackFrame* pFrame, int numargs)
{
	if (pFrame->m_variables.find(ASTR("this")) == pFrame->m_variables.end())	// TODO, not
		pFrame->m_variables[ASTR("this")] = (Object*)this;//object.m_variant.u.m_pObject;

	//std::vector<
	TRACE("(");

	for (int i = 0; i < numargs; i++)
	{
		StkElt elt = vm->pop();

		pFrame->m_variables[m_args[i]] = elt;

		if (i > 0) TRACE(", ");

		TRACE("%s", elt.toString()->c_str());
	}

	TRACE(")");

	pFrame->m_pContext = m_pContext;
//	ctx->m_pCaller = m_ctx;
	pFrame->m_return_pc = vm->m_pc;
	pFrame->m_instructionsData = m_codeData;
	pFrame->m_instructionsLength = m_codeLength;
//	ctx->m_constantPool = m_ctx->m_constantPool;	// inherited ?
	vm->m_pc = pFrame->m_instructionsData;
	vm->m_pFrame = pFrame;

	while (vm->next())
		;

//	PrintActions(pc, f->m_codeLength);

	/*
	// Check for empty function ?
	if (vm->pc - vm->m_ctx->m_instructionsData >= vm->ctx->m_instructionsLength)
	{
		vm->pc = vm->m_ctx->m_return_pc;
		vm->m_ctx = vm->m_ctx->m_pCaller;
	}
	*/
}

}	// ActionScripting
}
