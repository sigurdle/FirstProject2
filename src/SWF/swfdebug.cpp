#include "stdafx.h"
#include "swf.h"
#include "Movie.h"

#include "swfdebug.h"

namespace System
{
namespace SWF
{

using namespace ActionScripting;

/*
class StackFrame2
{
public:
};
*/

void VM2::push(StkElt value)
{
	m_stack.Add(value);
}

VM2::StkElt VM2::pop()
{
	int size = m_stack.GetSize();
	if (size <= 0) throw -1;
	StkElt elt = m_stack[m_stack.GetSize()-1];
	//ASSERT(elt == m_stack[size-1]);
	m_stack.RemoveAt(m_stack.GetSize()-1);
	return elt;
}

void VM2::as_notimpl(ULONG length)
{
	ASSERT(0);
}

void VM2::as_GetMember(ULONG length)
{
	std::string member = pop().str();
	std::string object = pop().str();

	/*TRACE("%s.%s", objectc_str(), member.c_str());

	if (object.m_variant.kind != VARKIND_OBJECT)
	{
		TRACE("Expected object");
		ASSERT(0);
	}
	*/

//	IMembersMap* pob = dynamic_cast<IMembersMap*>(object.m_variant.u.m_pObject);
//	StringA value = pob->GetMember(member.toString());
//	TRACE(" = %s", value.toString().c_str());

	push(object + "." + member);
}

void VM2::as_SetMember(ULONG length)
{
	std::string value = pop().str();
	std::string member = pop().str();
	std::string object = pop().str();

//	TRACE("%s.%s = %s", object.toString().c_str(), member.toString().c_str(), value.toString().c_str());
/*
	if (object.m_variant.kind != VARKIND_OBJECT)
	{
		TRACE("Expected object");
		ASSERT(0);
	}

	IMembersMap* pob = dynamic_cast<IMembersMap*>(object.m_variant.u.m_pObject);

	pob->SetMember(member.toString(), value);
	*/
	lines.push_back(LineNumber(m_startpc, m_nlines));

	m_str << object << "." << member << " = " << value;
	m_str << ";\n"; m_nlines++;

	//push(object + "." + member + " = " + value);
}

void VM2::as_With(ULONG length)
{
	std::string object = pop().str();

	/*TRACE("%s", object.toString().c_str());

	if (object.m_variant.kind != VARKIND_OBJECT)
	{
		TRACE("Expected object");
		ASSERT(0);
	}
	*/

	uint16 size = *pc++;
	size |= (*pc++)<<8;

//	StringA str = StringA((const char*)pc, length);
//	pc += length;

//	PrintActions(pc, length);

	/*
	StackFrame* ctx = new StackFrame;
	ctx->m_pContext = m_ctx->m_pContext;
	ctx->m_pCaller = m_ctx;
	ctx->m_return_pc = pc+size;
	ctx->m_instructionsData = pc;
	ctx->m_instructionsLength = size;
	pc = ctx->m_instructionsData;
	m_ctx = ctx;

	ctx->m_variables["this"] = object.m_variant.u.m_pObject;
	*/

	if (m_stack.GetSize())
	{
		m_str << pop().str() << ";\n";
	}

	ASSERT(m_stack.GetSize() == 0);

	lines.push_back(LineNumber(m_startpc, m_nlines));
	m_str << "with(" << object << ")\n" << "{\n";
	m_nlines++;

	uint8* end = pc + size;
//	uint8 ActionCode;
	while (pc < end)
	{
		uint8 ActionCode = *pc++;
		if (ActionCode == 0)
			break;

		ULONG Length = 0;
		if (ActionCode >= 0x80)
		{
			Length = *pc++;
			Length |= (long)(*pc++)<<8;
		}
		(this->*asfuncs[ActionCode])(Length);
	}

	m_str << "}\n";
	m_nlines++;

//	TRACE(" %s - %s", object.toString().c_str(), str.c_str());
}

void VM2::as_DefineFunction(ULONG length)
{
	std::string funName;

	//StringA name = pop();

	while (*pc)
	{
		funName += *pc++;
	}
	pc++;

	TRACE(" %s(", funName.c_str());

	uint16 numParams = *pc++;
	numParams |= (*pc++)<<8;

//	ActionScriptFunction* pFunction = new ActionScriptFunction;

	vector<std::string> args;

	for (int i = 0; i < numParams; i++)
	{
		std::string paramName;

		while (*pc)
		{
			paramName += *pc++;
		}
		pc++;

		/*pFunction->m_*/ args.Add(paramName);

		if (i > 0) TRACE(",");
		TRACE("%s", paramName.c_str());
	}

	TRACE(")");

	uint16 codeSize = *pc++;
	codeSize |= (*pc++)<<8;

	/*
	pFunction->m_pContext = m_ctx->m_pContext;
	pFunction->m_codeData = pc;
	pFunction->m_codeLength = codeSize;
	*/

	//pc += codeSize;

	VM2 vm2;
	vm2.pc = pc;
	vm2.m_pFrame = m_pFrame;

//	std::string str = m_str.str();
//	vector<StkElt> stack = m_stack;
//	m_stack.RemoveAll();
//	m_str = std::stringstream();

	//StringA result;

	if (funName.length() == 0)	// anonymous
	{
	//	StringA str;
		//elt.m_variant = Variant(pFunction);

		lines.push_back(LineNumber(m_startpc, m_nlines));

		vm2.m_str << "function (";
		vm2.m_nlines = m_nlines;

		for (unsigned int i = 0; i < args.size(); i++)
		{
			if (i > 0) vm2.m_str << ", ";
			vm2.m_str << args[i];
		}

		vm2.m_str << ")";

		vm2.m_str << "{\n";
		vm2.m_nlines++;

		uint8* end = vm2.pc + codeSize;
	//	uint8 ActionCode;
		while (vm2.pc < end)
		{
			vm2.m_startpc = vm2.pc - m_pFrame->m_instructionsData;
			uint8 ActionCode = *vm2.pc++;
			if (ActionCode == 0)
				break;

			ULONG Length = 0;
			if (ActionCode >= 0x80)
			{
				Length = *vm2.pc++;
				Length |= (long)(*vm2.pc++)<<8;
			}
			(vm2.*asfuncs[ActionCode])(Length);

		//	str += pop();
		}
		pc = vm2.pc;

		if (vm2.m_stack.GetSize())
		{
			vm2.m_str << pop().str();
			vm2.m_str << ";";
		}
		ASSERT(vm2.m_stack.GetSize() == 0);

		vm2.m_str << "}";

		std::string result = vm2.m_str.str();

		{
			for (unsigned int i = 0; i < vm2.lines.size(); i++)
			{
				lines.push_back(vm2.lines[i]);
			}
			m_nlines = vm2.m_nlines;
		}

		//m_str += str;

		push(result);
	}

/*	
	m_str = str;
	m_stack = stack;

	if (result != NULL)
	{
		push(result);
	}
	*/
}

void VM2::as_ConstantPool(ULONG length)
{
	uint16 count = *pc++;
	count |= (*pc++)<<8;

	//m_ctx->m_pContext->m_constantPool.clear();

//	m_constantPool.resize(MAX(m_constantPool.size(), count));

	for (int i = 0; i < count; i++)
	{
		std::string str;

		while (*pc)
		{
			str += *pc++;
		}
		pc++;
		TRACE("%s, ", str.c_str());

	//	m_constantPool[i] = (str);
		m_pFrame->m_pContext->m_constantPool.Add(StkElt(str));
	}
}

void VM2::as_Push(ULONG length)
{
	uint8* start = pc;

	while (pc < start+length)
	{
		uint8 type = *pc++;
		switch (type)
		{
		case 0:	// null-terminated string
			{
				std::string str;
				while (*pc)
				{
					str += *pc++;
				}
				pc++;

				push(str);
			}
			break;

		case 1:	// float
			{
				int32 value = *pc++;
				value |= (*pc++)<<8;
				value |= (*pc++)<<16;
				value |= (*pc++)<<24;

				push(*(float*)&value);
			}
			break;

		case 7:	// 32 bit integer
			{
				int32 value = *pc++;
				value |= (*pc++)<<8;
				value |= (*pc++)<<16;
				value |= (*pc++)<<24;

			//	char buf[32];
			//	sprintf(buf, "%d", value);
				push(value);
			}
			break;

		case 8:
			{
				uint8 index = *pc++;

				if (index < m_pFrame->m_pContext->m_constantPool.GetSize())
				{
					TRACE(" %s", m_pFrame->m_pContext->m_constantPool[index].str().c_str());

					push(m_pFrame->m_pContext->m_constantPool[index]);
				}
				else
				{
					TRACE(" out of bounds");
				//	push(StringA());
				}
			}
			break;

		case 16:
			{
				uint16 index = *pc++;
				index |= (*pc++)<<8;

				if (index < m_pFrame->m_pContext->m_constantPool.GetSize())
				{
					TRACE(" %s", m_pFrame->m_pContext->m_constantPool[index].str().c_str());

					push(m_pFrame->m_pContext->m_constantPool[index]);
				}
				else
				{
					TRACE(" out of bounds");
				//	push(StringA());
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
}

void VM2::as_Pop(ULONG length)
{
	lines.push_back(LineNumber(m_startpc, m_nlines));
	m_str << pop().str();
	m_str << ";\n";
	m_nlines++;
}

void VM2::as_Add2(ULONG length)
{
	std::string arg1 = pop().str();
	std::string arg2 = pop().str();

	push(arg2 + " + " + arg1);

	/*
	if (arg1.m_variant.kind == VARKIND_STRINGA && arg2.m_variant.kind == VARKIND_STRINGA)
	{
		StringA value = arg2.toString() + arg1.toString();

		push(StringA(value));
	}
	else
	{
		float value = arg2.toFloat() + arg1.toFloat();

		push(StringA(value));
	}
	*/

// TODO, more types
}

void VM2::as_If(ULONG length)
{
	std::string cond = pop().str();

	short offset = (*pc++);
	offset |= (*pc++)<<8;

	ASSERT(0);
	/*
	if (cond == true)
	{
		pc += offset;
	}
	*/
}

void VM2::as_CallFunction(ULONG length)
{
	ASSERT(0);
#if 0
	StringA name = pop();
	int numargs = pop().toInt();

	StringA str = name + "(";

	for (int i = 0; i < numargs; i++)
	{
		if (i > 0) str += ", ";

		str += pop();
	}

	str += ")";
	push(str);
#endif
}

void VM2::as_CallMethod(ULONG length)
{
	StkElt methodName = pop();
	std::string object = pop().str();

	std::string str = object + "." + methodName.str();

	str += "(";

	int numargs = pop().toInt();

	for (int i = 0; i < numargs; i++)
	{
		if (i > 0) str += ", ";

		std::string elt = pop().str();

		str += elt;
		/*
		StringA elt = pop();
		if (i > 0) TRACE(", ");

		TRACE("%s", elt.toString().c_str());
		*/
	}

	str += ")";

	push(str);

	/*
	if (m_stack.size() == 1)
	{
		m_str += pop();
		m_str += ";\n";
	}
	*/

#if 0
	if (object.m_variant.kind != VARKIND_OBJECT)
	{
		TRACE("Expected object");
		ASSERT(0);
	}

	IMembersMap* pob = dynamic_cast<IMembersMap*>(object.m_variant.u.m_pObject);

	StringA method = pob->GetMember(methodName.toString());

	if (method.m_variant.kind != VARKIND_OBJECT)
	{
		TRACE("Expected object");
		ASSERT(0);
	}

	Function* f = dynamic_cast<Function*>(method.m_variant.u.m_pObject);

	int numargs = pop().toInt();

	StackFrame* ctx = new StackFrame;

#if 0
	ctx->m_variables["this"] = object.m_variant.u.m_pObject;

	//std::vector<

	for (int i = 0; i < numargs; i++)
	{
		ctx->m_variables[f->m_args[i]] = pop();
		/*
		StringA elt = pop();
		if (i > 0) TRACE(", ");

		TRACE("%s", elt.toString().c_str());
		*/
	}

	TRACE(")");
#endif
	ctx->m_pCaller = m_ctx;
//	f->dispatch(this, ctx, numargs);
	/*
	ctx->m_pContext = f->m_pContext;
	ctx->m_pCaller = m_ctx;
	ctx->m_return_pc = pc;
	ctx->m_instructionsData = f->m_codeData;
	ctx->m_instructionsLength = f->m_codeLength;
//	ctx->m_constantPool = m_ctx->m_constantPool;	// inherited ?
	pc = ctx->m_instructionsData;
	m_ctx = ctx;

//	PrintActions(pc, f->m_codeLength);

	if (pc - m_ctx->m_instructionsData >= m_ctx->m_instructionsLength)
	{
		pc = m_ctx->m_return_pc;
		m_ctx = m_ctx->m_pCaller;
	}
	*/

	/*
	uint8* oldpc = pc;
	pc = pFunction->m_codeData;

	while (next())
		;

	pc = oldpc;
	*/
#endif
}

void VM2::as_GetVariable(ULONG length)
{
	std::string name = pop().str();
//	StringA value = m_ctx->m_variables[name.toString()];
//	push(value);

//	TRACE(" %s => %s", name.toString().c_str(), value.toString().c_str());
	push(name);
}

void VM2::as_SetVariable(ULONG length)
{
	std::string value = pop().str();
	std::string name = pop().str();

	lines.push_back(LineNumber(m_startpc, m_nlines));
	m_str << name << " = " << value;
	m_str << ";\n";
	m_nlines++;

//	push(name + " = " + value);
	/*
	m_ctx->m_variables[name.toString()] = value;

	TRACE(" %s <= %s", name.toString().c_str(), value.toString().c_str());
	*/

	/*
	if (m_stack.size() == 1)
	{
		m_str += pop();
		m_str += ";\n";
	}
	*/
}

void VM2::as_NextFrame(ULONG length)
{
	m_str << "nextFrame()";
	m_str << ";\n";
	/*
	StringA elt = m_ctx->m_variables["this"];
	
	PlacedCharacter* obj = dynamic_cast<PlacedCharacter*>(elt.m_variant.u.m_pObject);
	obj->m_gotoFrame++;
	*/
}

void VM2::as_Play(ULONG length)
{
	lines.push_back(LineNumber(m_startpc, m_nlines));
	m_str << "play()";
	m_str << ";\n";
}

void VM2::as_SetTarget(ULONG length)
{
	std::string target((const char*)pc, length);

	lines.push_back(LineNumber(m_startpc, m_nlines));
	m_str << "setTarget(" << target <<  ")";
	m_str << ";\n";
}

VM2::tyasfunc VM2::asfuncs[256] =
{
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_NextFrame,//"ActionNextFrame = 0x04",
	&VM2::as_notimpl,//"ActionPrevFrame = 0x05",
	&VM2::as_Play,//"ActionPlay = 0x06",
	&VM2::as_notimpl,//"ActionStop = 0x07",
	&VM2::as_notimpl,//"ActionToggleQuality = 0x08",
	&VM2::as_notimpl,//"ActionStopSounds = 0x09",
	&VM2::as_notimpl,//"ActionAdd = 0x0A",
	&VM2::as_notimpl,//"ActionSubtract = 0x0B",
	&VM2::as_notimpl,//"ActionMultiply = 0x0C",
	&VM2::as_notimpl,//"ActionDivide = 0x0D",
	&VM2::as_notimpl,//"ActionEquals = 0x0E",
	&VM2::as_notimpl,//"ActionLess = 0x0F",
	&VM2::as_notimpl,//"ActionAnd = 0x10",
	&VM2::as_notimpl,//"ActionOr = 0x11",
	&VM2::as_notimpl,//"ActionNot = 0x12",
	&VM2::as_notimpl,//"ActionStringEquals = 0x13",
	&VM2::as_notimpl,//"ActionStringLength = 0x14",
	&VM2::as_notimpl,//"ActionStringExtract = 0x15",
	&VM2::as_notimpl,//NULL,
	&VM2::as_Pop,//"ActionPop = 0x17",
	&VM2::as_notimpl,//"ActionToInteger = 0x18",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_GetVariable,//"ActionGetVariable = 0x1C",
	&VM2::as_SetVariable,//"ActionSetVariable = 0x1D",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionSetTarget2 = 0x20",
	&VM2::as_notimpl,//"ActionStringAdd = 0x21",
	&VM2::as_notimpl,//"ActionGetProperty = 0x22",
	&VM2::as_notimpl,//"ActionSetProperty = 0x23",
	&VM2::as_notimpl,//"ActionCloneSprite = 0x24",
	&VM2::as_notimpl,//"ActionRemoveSprite = 0x25",
	&VM2::as_notimpl,//"ActionTrace = 0x26",
	&VM2::as_notimpl,//"ActionStartDrag = 0x27",
	&VM2::as_notimpl,//"ActionEndDrag = 0x28",
	&VM2::as_notimpl,//"ActionStringLess = 0x29",
	&VM2::as_notimpl,//"ActionThrow = 0x2A",
	&VM2::as_notimpl,//"ActionCastOp = 0x2B",
	&VM2::as_notimpl,//"ActionImplementsOp = 0x2C",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionRandomNumber = 0x30",
	&VM2::as_notimpl,//"ActionMBStringLength = 0x31",
	&VM2::as_notimpl,//"ActionCharToAscii = 0x32",
	&VM2::as_notimpl,//"ActionAsciiToChar = 0x33",
	&VM2::as_notimpl,//"ActionGetTime = 0x34",
	&VM2::as_notimpl,//"ActionMBStringExtract = 0x35",
	&VM2::as_notimpl,//"ActionMBCharToAscii = 0x36",
	&VM2::as_notimpl,//"ActionMBAsciiToChar = 0x37",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionDelete = 0x3A",
	&VM2::as_notimpl,//"ActionDelete2 = 0x3B",
	&VM2::as_notimpl,//"ActionDefineLocal = 0x3C",
	&VM2::as_CallFunction,//"ActionCallFunction = 0x3D",
	&VM2::as_notimpl,//"ActionReturn = 0x3E",
	&VM2::as_notimpl,//"ActionModulo = 0x3F",
	&VM2::as_notimpl,//"ActionNewObject = 0x40",
	&VM2::as_notimpl,//"ActionDefineLocal2 = 0x41",
	&VM2::as_notimpl,//"ActionInitArray = 0x42",
	&VM2::as_notimpl,//"ActionInitObject = 0x43",
	&VM2::as_notimpl,//"ActionTypeOf = 0x44",
	&VM2::as_notimpl,//"ActionTargetPath = 0x45",
	&VM2::as_notimpl,//"ActionEnumerate = 0x46",
	&VM2::as_Add2,//"ActionAdd2 = 0x47",
	&VM2::as_notimpl,//"ActionLess2 = 0x48",
	&VM2::as_notimpl,//"ActionEquals2 = 0x49",
	&VM2::as_notimpl,//"ActionToNumber = 0x4A",
	&VM2::as_notimpl,//"ActionToString = 0x4B",
	&VM2::as_notimpl,//"ActionPushDuplicate = 0x4C",
	&VM2::as_notimpl,//"ActionStackSwap = 0x4D",
	&VM2::as_GetMember,//"ActionGetMember = 0x4E",
	&VM2::as_SetMember,//"ActionSetMember = 0x4F",
	&VM2::as_notimpl,//"ActionIncrement = 0x50",
	&VM2::as_notimpl,//"ActionDecrement = 0x51",
	&VM2::as_CallMethod,//"ActionCallMethod = 0x52",
	&VM2::as_notimpl,//"ActionNewMethod = 0x53",
	&VM2::as_notimpl,//"ActionInstanceOf = 0x54",
	&VM2::as_notimpl,//"ActionEnumerate2 = 0x55",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionBitAnd = 0x60",
	&VM2::as_notimpl,//"ActionBitOr = 0x61",
	&VM2::as_notimpl,//"ActionBitXor = 0x62",
	&VM2::as_notimpl,//"ActionBitLShift = 0x63",
	&VM2::as_notimpl,//"ActionBitRShift = 0x64",
	&VM2::as_notimpl,//"ActionBitURShift = 0x65",
	&VM2::as_notimpl,//"ActionStrictEquals = 0x66",
	&VM2::as_notimpl,//"ActionGreater = 0x67",
	&VM2::as_notimpl,//"ActionStringGreater = 0x68",
	&VM2::as_notimpl,//"ActionExtends = 0x69",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionGotoFrame = 0x81",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionGetURL = 0x83",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionStoreRegister = 0x87",
	&VM2::as_ConstantPool,//"ActionConstantPool = 0x88",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionWaitForFrame = 0x8A",
	&VM2::as_SetTarget,//"ActionSetTarget = 0x8B",
	&VM2::as_notimpl,//"ActionGoToLabel = 0x8C",
	&VM2::as_notimpl,//"ActionWaitForFrame2 = 0x8D",
	&VM2::as_notimpl,//"ActionDefineFunction2 = 0x8E",
	&VM2::as_notimpl,//"ActionTry = 0x8F",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_With,//"ActionWith = 0x94",
	&VM2::as_notimpl,//NULL,
	&VM2::as_Push,//"ActionPush = 0x96",
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//NULL,
	&VM2::as_notimpl,//"ActionJump = 0x99",
	&VM2::as_notimpl,//"ActionGetURL2 = 0x9A",
	&VM2::as_DefineFunction,//"ActionDefineFunction = 0x9B",
	&VM2::as_notimpl,//NULL,
	&VM2::as_If,//"ActionIf = 0x9D",
	&VM2::as_notimpl,//"ActionCall = 0x9E",
	&VM2::as_notimpl,//"ActionGotoFrame2 = 0x9F",
};

bool VM2::next()
{
#if 0
	if (m_ctx == NULL)
	{
		return false;
	}

	if (pc - m_ctx->m_instructionsData >= m_ctx->m_instructionsLength)
	{
		pc = m_ctx->m_return_pc;
		m_ctx = m_ctx->m_pCaller;

		// ????
		// push function/method result onto stack
		push(0L);

		level--;
		return true;
		/*
		if (m_ctx == NULL)
			return false;
			*/
	}
#endif

	uint8* end = pc + m_pFrame->m_instructionsLength;

	while (pc < end)
	{
		uint8* p = pc;
		m_startpc = pc - m_pFrame->m_instructionsData;
		uint8 ActionCode = *p++;

		if (ActionCode == 0)
			return false;

	#if 0
		if (instr_code == 0x1B)	// else
		{
			level--;
			printlevel();
			LOG("else\n");
			level++;
			pc++;

			while (1)
			{
				uint8 instr_code = *pc;
				if (instr_code == 0x59)	// eif
					break;

				skip_next(this);
			}

			ASSERT(*pc == 0x59);	// eif
			return true;//break;
		}

		if (instr_code == 0x59)	// eif
		{
		}

		printlevel();
	#endif

		ULONG Length = 0;
		if (ActionCode >= 0x80)
		{
			Length = *p++;
			Length |= (long)(*p++)<<8;
		}
		pc = p;
#ifdef _DEBUG
		TRACE("%s - 0x%x ", ActionNames[ActionCode], ActionCode);
#endif
		(this->*asfuncs[ActionCode])(Length);

		TRACE("\n");

#ifdef _DEBUG
	if (ActionCode != 0x9B)
	{
	;//	ASSERT(pc == p+Length);
	}

//	pc = p + Length;
#endif
	}

	return false;
}

}	// SWF
}
