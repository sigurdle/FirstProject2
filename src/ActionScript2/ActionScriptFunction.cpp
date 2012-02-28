#include "stdafx.h"
#include "ActionScript2.h"
//#include "Movie.h"
#include "ActionScript.h"

namespace System
{
namespace ActionScripting
{

ImmutableString<char> ActionNames[256] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	"ActionNextFrame",
	"ActionPrevFrame",
	"ActionPlay",
	"ActionStop",
	"ActionToggleQuality",
	"ActionStopSounds",
	"ActionAdd",
	"ActionSubtract",
	"ActionMultiply",
	"ActionDivide",
	"ActionEquals",
	"ActionLess",
	"ActionAnd",
	"ActionOr",
	"ActionNot",
	"ActionStringEquals",
	"ActionStringLength",
	"ActionStringExtract",
	NULL,
	"ActionPop",
	"ActionToInteger",
	NULL,
	NULL,
	NULL,
	"ActionGetVariable",
	"ActionSetVariable",
	NULL,
	NULL,
	"ActionSetTarget2",
	"ActionStringAdd",
	"ActionGetProperty",
	"ActionSetProperty",
	"ActionCloneSprite",
	"ActionRemoveSprite",
	"ActionTrace",
	"ActionStartDrag",
	"ActionEndDrag",
	"ActionStringLess",
	"ActionThrow",
	"ActionCastOp",
	"ActionImplementsOp",
	NULL,
	NULL,
	NULL,
	"ActionRandomNumber",
	"ActionMBStringLength",
	"ActionCharToAscii",
	"ActionAsciiToChar",
	"ActionGetTime",
	"ActionMBStringExtract",
	"ActionMBCharToAscii",
	"ActionMBAsciiToChar",
	NULL,
	NULL,
	"ActionDelete",
	"ActionDelete2",
	"ActionDefineLocal",
	"ActionCallFunction",
	"ActionReturn",
	"ActionModulo",
	"ActionNewObject",
	"ActionDefineLocal2",
	"ActionInitArray",
	"ActionInitObject",
	"ActionTypeOf",
	"ActionTargetPath",
	"ActionEnumerate",
	"ActionAdd2",
	"ActionLess2",
	"ActionEquals2",
	"ActionToNumber",
	"ActionToString",
	"ActionPushDuplicate",
	"ActionStackSwap",
	"ActionGetMember",
	"ActionSetMember",
	"ActionIncrement",
	"ActionDecrement",
	"ActionCallMethod",
	"ActionNewMethod",
	"ActionInstanceOf",
	"ActionEnumerate2",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"ActionBitAnd",
	"ActionBitOr",
	"ActionBitXor",
	"ActionBitLShift",
	"ActionBitRShift",
	"ActionBitURShift",
	"ActionStrictEquals",
	"ActionGreater",
	"ActionStringGreater",
	"ActionExtends",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"ActionGotoFrame",
	NULL,
	"ActionGetURL",
	NULL,
	NULL,
	NULL,
	"ActionStoreRegister",
	"ActionConstantPool",
	NULL,
	"ActionWaitForFrame",
	"ActionSetTarget",
	"ActionGoToLabel",
	"ActionWaitForFrame2",
	"ActionDefineFunction2",
	"ActionTry",
	NULL,
	NULL,
	NULL,
	NULL,
	"ActionWith",
	NULL,
	"ActionPush",
	NULL,
	NULL,
	"ActionJump",
	"ActionGetURL2",
	"ActionDefineFunction",
	NULL,
	"ActionIf",
	"ActionCall",
	"ActionGotoFrame2",
};

ActionScriptFunction::ActionScriptFunction()
{
	m_codeData = NULL;
	m_pContext = NULL;
}

/*
ActionScriptFunction::ActionScriptFunction(ecma::Script* scriptcode)
{
	m_codeData = scriptcode_code.begin();
	m_codeLength = scriptcode->m_code.size();
	m_pContext = scriptcode->m_as_context;
}
*/

size_t ActionScriptFunction::get_NumArgs()
{
	return m_args.size();
}

String ActionScriptFunction::ToString()
{
	IO::StringWriter stream;
	stream << "unknown_name" << "(";
	for (uint i = 0; i < m_args.size(); ++i)
	{
		if (i > 0) stream << ",";
		stream << m_args[i];
	}
	stream << ")";
	return stream.str();
}

void ActionScriptFunction::dispatch(VM* vm, StackFrame* pFrame, uint numargs)
{
#if 0
	if (pFrame->m_variables.find("this") == pFrame->m_variables.end())	// TODO, not
		pFrame->m_variables["this"] = (Object*)this;//object.m_variant.u.m_pObject;
#endif

	//std::vector<
//	DebugTrace("(");

	for (uint i = 0; i < numargs; i++)
	{
		StkElt elt = vm->pop();

		pFrame->m_variables[m_args[i]] = elt;

//		if (i > 0) DebugTrace(", ");
	//	DebugTrace(elt.ToString());
	}

	DebugTrace(")");

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

class Instruction// : public MInstruction
{
public:
	uint8 op;
};

class DasmContext
{
public:
	virtual ~DasmContext()
	{
	}

	uint8* pc;
};

Instruction* disasm(DasmContext* context, void* reserved)
{
	Instruction* instr = new Instruction;
	instr->op = *context->pc++;

	uint16 length;
	if (instr->op >= 0x80)
	{
		length = *context->pc++;
		length |= (*context->pc++)<<8;
	}
	else
	{
		length = 0;
	}

	context->pc += length;

	return instr;
}

ActionScript2Ext void Disasm(ActionScriptFunction* function)
{
	DasmContext context;
	context.pc = function->m_codeData;
	byte* end = function->m_codeData + function->m_codeLength;

	while (context.pc < end)
	{
		Instruction* instr = disasm(&context, NULL);

		Std::get_Out() << context.pc - function->m_codeData << "\t";

		String strdasm = &ActionNames[instr->op];

		Std::Out << strdasm << endl;
	}
}

}	// ActionScripting
}	// System
