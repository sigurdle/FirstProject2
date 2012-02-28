#include "stdafx.h"
#include "LXUI2.h"

#include "ActionScript.h"
#include "ActionScriptFunction.h"

namespace System
{
namespace ActionScripting
{

StringA empty_str(true, "");
StringA true_str(true, "true");
StringA false_str(true, "false");
StringA null_str(true, "null");
StringA undefined_str(true, "undefined");

StringW empty_str_w(true, L"");
StringW true_str_w(true, L"true");
StringW false_str_w(true, L"false");
StringW null_str_w(true, L"null");
StringW undefined_str_w(true, L"undefined");

int32 StkElt::toInt() const
{
	switch (m_variant.kind)
	{
	case System::VARKIND_BOOL:
		return m_variant.u.bool_val;

	case System::VARKIND_INT32:
		return m_variant.u.int32_val;

	case System::VARKIND_FLOAT32:
		return (int32)m_variant.u.float32_val;

	case System::VARKIND_FLOAT64:
		return (int32)m_variant.u.float64_val;

	case System::VARKIND_STRINGA:
		return str2int(((System::StringA*)m_variant.m_pObject)->c_str());

	case System::VARKIND_STRINGW:
		return str2int(((System::StringW*)m_variant.m_pObject)->c_str());
	}
	return 0;
}

float StkElt::toFloat() const
{
	switch (m_variant.kind)
	{
	case System::VARKIND_BOOL:
		return (float)m_variant.u.bool_val;

	case System::VARKIND_INT32:
		return (float)m_variant.u.int32_val;

	case System::VARKIND_FLOAT32:
		return m_variant.u.float32_val;

	case System::VARKIND_FLOAT64:
		return (float)m_variant.u.float64_val;

	case System::VARKIND_STRINGA:
		return (float)getfnumber(((System::StringA*)m_variant.m_pObject)->c_str());

	case System::VARKIND_STRINGW:
		return (float)getfnumber(((System::StringW*)m_variant.m_pObject)->c_str());
	}
	return 0;
}

double StkElt::toDouble() const
{
	switch (m_variant.kind)
	{
	case System::VARKIND_BOOL:
		return (double)m_variant.u.bool_val;

	case System::VARKIND_INT32:
		return (double)m_variant.u.int32_val;

	case System::VARKIND_FLOAT32:
		return m_variant.u.float32_val;

	case System::VARKIND_FLOAT64:
		return m_variant.u.float64_val;

	case System::VARKIND_STRINGA:
		return getfnumber(((System::StringA*)m_variant.m_pObject)->c_str());

	case System::VARKIND_STRINGW:
		return getfnumber(((System::StringW*)m_variant.m_pObject)->c_str());
	}
	return 0;
}

VM::VM()
{
	m_flags = 0;
	m_breakpoint = NULL;
	m_userobject = NULL;

	m_global = NULL;
	m_pc = NULL;
	m_pFrame = NULL;
}

StackFrame::StackFrame()
{
	m_instructionsData = NULL;
	m_pCaller = NULL;
	m_return_pc = NULL;
	m_pContext = NULL;
}

System::StringA* StkElt::toStringA() const
{
	switch (m_variant.kind)
	{
	case VARKIND_NULL:
		{
			return &empty_str;
		//	return null_str;
		}
		break;

	case VARKIND_UNDEFINED:
		{
			return &undefined_str;
		}
		break;

	case VARKIND_BOOL:
		{
			return m_variant.u.bool_val? &true_str: &false_str;
		}
		break;

	case VARKIND_INT32:
		{
			char buf[32];
			sprintf_s(buf, "%d", m_variant.u.int32_val);
			return new System::StringA(string_copy(buf));
		}
		break;

	case VARKIND_FLOAT32:
		{
			char buf[32];
			sprintf_s(buf, "%f", m_variant.u.float32_val);
			return new System::StringA(string_copy(buf));
		}
		break;

	case VARKIND_FLOAT64:
		{
			char buf[32];
			sprintf_s(buf, "%f", m_variant.u.float64_val);
			return new System::StringA(string_copy(buf));
		}
		break;

	case VARKIND_STRINGA:
		{
			ASSERT(m_variant.m_pObject->GetType() == typeid(StringA).GetType());
			return (StringA*)m_variant.m_pObject;
		}

	case VARKIND_STRINGW:
		{
			ASSERT(m_variant.m_pObject->GetType() == typeid(StringW).GetType());
			return ((StringW*)m_variant.m_pObject)->ToStringA();
		}

	case VARKIND_OBJECT:
		{
			char buf[64];
			sprintf_s(buf, "(object=0x%x)", m_variant.m_pObject);
			return new System::StringA(string_copy(buf));
		}
		break;

	default:
		ASSERT(0);
		return NULL;
	}
}

System::StringW* StkElt::toString() const
{
	switch (m_variant.kind)
	{
	case VARKIND_NULL:
		{
		//	return &null_str_w;
			return &empty_str_w;
		}
		break;

	case VARKIND_UNDEFINED:
		{
			return &undefined_str_w;
		}
		break;

	case VARKIND_BOOL:
		{
			return m_variant.u.bool_val? &true_str_w: &false_str_w;
		}
		break;

	case VARKIND_INT32:
		{
			WCHAR buf[32];
			swprintf_s(buf, L"%d", m_variant.u.int32_val);
			return new System::StringW(string_copy(buf));
		}
		break;

	case VARKIND_FLOAT32:
		{
			WCHAR buf[32];
			swprintf_s(buf, L"%f", m_variant.u.float32_val);
			return new System::StringW(string_copy(buf));
		}
		break;

	case VARKIND_FLOAT64:
		{
			WCHAR buf[32];
			swprintf_s(buf, L"%f", m_variant.u.float64_val);
			return new System::StringW(string_copy(buf));
		}
		break;

	case VARKIND_STRINGA:
		return ((StringA*)m_variant.m_pObject)->ToStringW();

	case VARKIND_STRINGW:
		return (StringW*)m_variant.m_pObject;

	case VARKIND_OBJECT:
		{
			ClassType* pType = m_variant.m_pObject->GetType();
			WCHAR buf[64];
			swprintf_s(buf, L"([%S]=0x%x)", pType->m_qname->c_str(), m_variant.m_pObject);
			return new System::StringW(string_copy(buf));
		}
		break;

	default:
		ASSERT(0);
		return NULL;
	}
}

Variant MembersMap::GetMember(StringIn name)
{
	return m_members[name];
}

void MembersMap::SetMember(StringIn name, Variant value)
{
	m_members[name] = value;
}

void VM::push(StkElt value)
{
	m_stack.push_back(value);
}

StkElt VM::pop()
{
	unsigned int size = m_stack.GetSize();
	if (size == 0) throw std::exception("Couldn't pop from empty stack");
	StkElt elt = m_stack[m_stack.GetSize()-1];
	//ASSERT(elt == m_stack[size-1]);
	m_stack.RemoveAt(m_stack.GetSize()-1);
	return elt;
}

void VM::as_notimpl(unsigned int length)
{
	ASSERT(0);
	throw new Exception(WSTR("ActionScript: op not implemented"));
}

void VM::as_GetMember(unsigned int length)
{
	StkElt member = pop();
	StkElt object = pop();

	TRACE("%s.%s", object.toStringA()->c_str(), member.toStringA()->c_str());

	if (object.m_variant.kind != VARKIND_OBJECT)
	{
		ASSERT(0);
		throw new Exception(WSTR("Expected object"));
	}

	if (true)
	{
		ClassType* pType = object.m_variant.m_pObject->GetType();
		Dispatch* pDispatch = GetDispatch(pType);
		StringA* propertyName = member.toStringA();
		Property* pProperty = pDispatch->GetProperty(propertyName);
		if (pProperty)
		{
			CallMethod(pDispatch, object.m_variant.m_pObject, pProperty->get_GetMethod(), 0, true);
		}
		else
		{
			UI::UIElement* expandable = dynamic_cast<UI::UIElement*>(object.m_variant.m_pObject);
			Object* value = expandable->m_userdata[member.toString()];

			push(StkElt(value));
		}
	}
	else
	{
		IMembersMap* pob = dynamic_cast<IMembersMap*>(object.m_variant.m_pObject);

		StkElt value = pob->GetMember(member.toStringA());

		TRACE(" = %s", value.toStringA()->c_str());

		push(value);
	}
}

void VM::as_SetMember(unsigned int length)
{
	StkElt value = pop();
	StkElt member = pop();
	StkElt object = pop();

	TRACE("%s.%s = %s", object.toStringA()->c_str(), member.toStringA()->c_str(), value.toStringA()->c_str());

	if (object.m_variant.kind != VARKIND_OBJECT)
	{
		ASSERT(0);
		throw new Exception(WSTR("Expected object"));
	}

	if (true)
	{
		if (object.m_variant.m_pObject == NULL)
		{
			ASSERT(0);
		}

		ClassType* pType = object.m_variant.m_pObject->GetType();
		Dispatch* pDispatch = GetDispatch(pType);
		Property* pProperty = pDispatch->GetProperty(member.toStringA());

		if (pProperty->get_SetMethod() == NULL)
		{
			throw new Exception(WSTR("property is read only"));
		}

		push(value);

		CallMethod(pDispatch, object.m_variant.m_pObject, pProperty->get_SetMethod(), 1, false);
	}
	else
	{
		IMembersMap* pob = dynamic_cast<IMembersMap*>(object.m_variant.m_pObject);

		pob->SetMember(member.toStringA(), value);
	}
}

void VM::as_With(unsigned int length)
{
	StkElt object = pop();

	TRACE("%s", object.toStringA()->c_str());

	if (object.m_variant.kind != VARKIND_OBJECT)
	{
		ASSERT(0);
		throw new Exception(WSTR("Expected object"));
	}

	uint16 size = *m_pc++;
	size |= (*m_pc++)<<8;

//	StringA str = StringA((const char*)pc, length);
//	pc += length;

//	PrintActions(pc, length);

	StackFrame* pFrame = new StackFrame;
	pFrame->m_pContext = m_pFrame->m_pContext;
	pFrame->m_pCaller = m_pFrame;
	pFrame->m_return_pc = m_pc+size;
	pFrame->m_instructionsData = m_pc;
	pFrame->m_instructionsLength = size;
	m_pc = pFrame->m_instructionsData;
	m_pFrame = pFrame;

	pFrame->m_variables[ASTR("this")] = object.m_variant.m_pObject;

//	TRACE(" %s - %s", object.toStringA().c_str(), str.c_str());
}

void VM::as_DefineFunction(unsigned int length)
{
	//StringA* funName = new StringA();
	uint8* start = m_pc;

	//StkElt name = pop();

	while (*m_pc)
	{
		//funName = funName->Append(*pc++);
		m_pc++;
	}
	StringA* funName = NULL;
	if (start[0])
		funName = new StringA(string_copy((const char*)start, m_pc - start));

	m_pc++;

	TRACE(" %s(", (const char*)start);//->c_str());

	uint16 numParams = *m_pc++;
	numParams |= (*m_pc++)<<8;

	ActionScriptFunction* pFunction = new ActionScriptFunction;

//	m_ctx->m_pContext->m_funmap[new StringA(funName)] = pFunction;
	if (funName)
		m_pFrame->m_variables[funName] = pFunction;

	for (int i = 0; i < numParams; i++)
	{
		const char* paramName = (const char*)m_pc;
		while (*m_pc)
		{
			m_pc++;
		}

		pFunction->m_args.push_back(new StringA(string_copy(paramName, (const char*)m_pc - paramName)));

		m_pc++;

		if (i > 0) TRACE(",");
		TRACE("%s", paramName);//->c_str());
	}

	TRACE(")");

	uint16 codeSize = *m_pc++;
	codeSize |= (*m_pc++)<<8;

	pFunction->m_pContext = m_pFrame->m_pContext;
	pFunction->m_codeData = m_pc;
	pFunction->m_codeLength = codeSize;

	m_pc += codeSize;

	if (funName == 0)	// anonymous
	{
		StkElt elt;
		elt.m_variant = Variant(pFunction);

		push(elt);
	}
}

// Create a new constant pool, erase the old one
void VM::as_ConstantPool(unsigned int length)
{
	uint16 count = *m_pc++;
	count |= (*m_pc++)<<8;

	m_pFrame->m_pContext->m_constantPool.clear();

//	m_constantPool.resize(MAX(m_constantPool.size(), count));

	m_pFrame->m_pContext->m_constantPool.reserve(count);

	for (int i = 0; i < count; i++)
	{
		uint8* start = m_pc;

		while (*m_pc)
		{
		//	str = str->Append(*pc++);
			m_pc++;
		}
		StringA* str = new StringA(string_copy((const char*)start, m_pc - start));

		m_pc++;
	//	TRACE("%s, ", str->c_str());

	//	m_constantPool[i] = (str);
		m_pFrame->m_pContext->m_constantPool.Add(StkElt(str));
	}
}

void VM::as_Push(unsigned int length)
{
	uint8* start = m_pc;

	while (m_pc < start+length)
	{
		uint8 type = *m_pc++;
		switch (type)
		{
		case 2:	// null
			{
				push(StkElt(VARKIND_NULL));
			}
			break;

		case 3:	// undefined
			{
				push(StkElt(VARKIND_UNDEFINED));
			}
			break;

		case 7:	// 32 bit integer
			{
				int32 value = *m_pc++;
				value |= (*m_pc++)<<8;
				value |= (*m_pc++)<<16;
				value |= (*m_pc++)<<24;

				TRACE(" %d", value);
				push(value);
			}
			break;

		case 8:
			{
				uint8 index = *m_pc++;

				if (index < m_pFrame->m_pContext->m_constantPool.GetSize())
				{
					TRACE(" %s", m_pFrame->m_pContext->m_constantPool[index].toStringA()->c_str());

					push(m_pFrame->m_pContext->m_constantPool[index]);
				}
				else
				{
					TRACE(" out of bounds");
				//	push(StkElt());
				}
			}
			break;

		case 9:
			{
				uint16 index = *m_pc++;
				index |= (*m_pc++)<<8;

				if (index < m_pFrame->m_pContext->m_constantPool.GetSize())
				{
					TRACE(" %s", m_pFrame->m_pContext->m_constantPool[index].toStringA()->c_str());

					push(m_pFrame->m_pContext->m_constantPool[index]);
				}
				else
				{
					TRACE(" out of bounds");
				//	push(StkElt());
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
}

void VM::as_Pop(unsigned int length)
{
	pop();
}

void VM::as_Less2(unsigned int length)
{
	StkElt arg1 = pop();
	StkElt arg2 = pop();

// TODO

	bool result = arg2.toInt() < arg1.toInt();

	push(StkElt(result));
}

void VM::as_Greater(unsigned int length)
{
	StkElt arg1 = pop();
	StkElt arg2 = pop();

// TODO

	bool result = arg2.toInt() > arg1.toInt();

	push(StkElt(result));
}

void VM::as_Add2(unsigned int length)
{
	StkElt arg1 = pop();
	StkElt arg2 = pop();

	TRACE("%s + %s", arg2.toStringA()->c_str(), arg1.toStringA()->c_str());

	if ((arg1.m_variant.kind == VARKIND_STRINGW || arg1.m_variant.kind == VARKIND_NULL) ||
		(arg2.m_variant.kind == VARKIND_STRINGW || arg2.m_variant.kind == VARKIND_NULL))
	{
		StringPtr value = StringPtr(arg2.toString()) + StringPtr(arg1.toString());
		/*
		StringW* value = new StringW(arg2.toString()- + *arg1.toString();
		*/

		push(StkElt(value));
	}
	else if (arg1.m_variant.kind == VARKIND_STRINGA && arg2.m_variant.kind == VARKIND_STRINGA)
	{
		ASSERT(0);
#if 0
		StringA* value = *arg2.toString() + *arg1.toString();

		push(StkElt(value));
#endif
	}
	else
	{
		if (arg1.m_variant.kind == VARKIND_FLOAT64 ||
			arg2.m_variant.kind == VARKIND_FLOAT64)
		{
			double value = arg2.toDouble() + arg1.toDouble();
			push(StkElt(value));
		}
		else if (arg1.m_variant.kind == VARKIND_FLOAT32 ||
			arg2.m_variant.kind == VARKIND_FLOAT32)
		{
			float value = arg2.toFloat() + arg1.toFloat();
			push(StkElt(value));
		}
		else
		{
			int32 value = arg2.toInt() + arg1.toInt();
			push(StkElt(value));
		}
	}
}

void VM::as_If(unsigned int length)
{
	StkElt cond = pop();

	short offset = (*m_pc++);
	offset |= (*m_pc++)<<8;

	if (cond == true)
	{
		m_pc += offset;
	}
}

void VM::as_DefineLocal2(unsigned int length)
{
	StkElt name = pop();

	//pair<map<System::StringA*, StkElt, Ref_Less<System::StringA>, System::__gc_allocator>::iterator, bool> r;
	/*r =*/ m_pFrame->m_variables.insert(map<System::StringA*, StkElt, Ref_Less<System::StringA>, System::__gc_allocator>::value_type(name.toStringA(), StkElt()));

	TRACE("var %s;\n", name.toStringA()->c_str());
}

//			void SetValue(Dispatch* dispatch, void* _this, Method* method, Object* pObject, Type* pSourceType);

void VM::CallMethod(Dispatch* pDispatch, void* object, Method* pMethod, unsigned int numargs, bool bReturnValue)
{
	uint8 args[512];
	uint8* p = args;

	ASSERT(pMethod->m_decl->m_pType->GetFunction()->m_parameters.m_parameters.size() == numargs);
	Type* pReturnType = pMethod->m_decl->m_pType->GetFunction()->m_pReturnType;

	for (unsigned int i = 0; i < numargs; i++)
	{
		Type* ArgType = pMethod->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[i].m_pType->GetStripped();

		StkElt elt = pop();

		/*
		switch (elt.m_variant.kind)
		{
		case VARKIND_INT32:
			{
				*(int*)p = elt.toInt();
				p += 4;
			}
			break;

		case VARKIND_STRINGA:
		case VARKIND_STRINGW:
		case VARKIND_OBJECT:
			{
			*/

		if (ArgType->get_Kind() == type_int)
		{
			*(int*)p = elt.toInt();
			p += 4;
		}
		else if (ArgType->get_Kind() == type_unsigned_int)
		{
			*(int*)p = elt.toInt();
			p += 4;
		}
		else if (ArgType->get_Kind() == type_float)
		{
			*(float*)p = elt.toFloat();
			p += sizeof(float);
		}
		else if (ArgType->get_Kind() == type_double)
		{
			*(double*)p = elt.toDouble();
			p += sizeof(double);
		}
		else
		{
			//ASSERT(elt.m_variant.kind

			//Type* ArgType = method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType->GetStripped();
			if (ArgType->get_Kind() == type_class)
			{
				ASSERT(0);
			}
			else if (ArgType->get_Kind() == type_pointer)
			{
				ArgType = ArgType->GetPointerTo()->GetStripped();

		//		ASSERT(pSourceType->m_type == type_pointer);
				if (ArgType->get_Kind() == type_class)
				{
					void* properType;

					if (ArgType == typeid(System::StringA).GetType())
					{
						Object* pObject = elt.toString();
						properType = pObject;
					}
					else if (ArgType == typeid(System::StringW).GetType())
					{
						Object* pObject = elt.toString();
						properType = pObject;
					}
					else
					{
						Object* pObject = elt.m_variant.kind == VARKIND_NULL? NULL: elt.m_variant.m_pObject;
						ClassType* pSourceType = pObject? pObject->GetType(): NULL;

						if (pObject)
						{
						//	Class* psrc = GetType(pObject);	// debug
						//	ASSERT(psrc->m_qname == ((Class*)pSourceType)->m_qname);	// debug
							
							properType = DynamicCast(pObject, pSourceType->GetClass()/*->GetPointerTo()*/, ArgType->GetClass());
							ASSERT(properType);
						}
						else
							properType = NULL;
					}

					*(void**)p = properType;
					p += sizeof(void*);
					//dispatch->Invoke(_this, method, &properType, 4);
				}
				else
				{
					ASSERT(0);
					throw new Exception(WSTR("Unsupported arg type"));
				}
			}
			else
			{
				ASSERT(0);
				throw new Exception(WSTR("Unsupported arg type"));
			}
		}

		// TODO, convert to appropriate type

	//	*(void**)p = elt.m_variant.m_pStringA;
		//*(int*)p = elt.toInt();

		//switch (elt
	}

	switch (pReturnType->get_Kind())
	{
	case type_void:
		{
			pDispatch->void_Invoke(object, pMethod, args, p - args);
			if (bReturnValue)
			{
				push(StkElt());	// undefined
			}
		}
		break;

	case type_int:
	case type_unsigned_int:
		{
			int32 result = pDispatch->int32_Invoke(object, pMethod, args, p - args);
			if (bReturnValue)
			{
				push(StkElt(result));
			}
		}
		break;

	case type_double:
		{
			double result = pDispatch->double_Invoke(object, pMethod, args, p - args);
			if (bReturnValue)
			{
				push(StkElt(result));
			}
		}
		break;

	case type_pointer:
		{
			void* result = pDispatch->pointer_Invoke(object, pMethod, args, p - args);

			if (bReturnValue)
			{
				Type* pReturnType2 = pReturnType->GetPointerTo()->GetStripped();

				if (pReturnType2 == typeid(StringA).GetType())
					push(StkElt(static_cast<StringA*>(result)));
				else if (pReturnType2 == typeid(StringW).GetType())
					push(StkElt(static_cast<StringW*>(result)));
				else
					push(StkElt((Object*)result));
			}
		}
		break;

	default:
		{
			ASSERT(0);
			throw new Exception(WSTR("Unsupported return type"));
		}
	}
}

void VM::CallMethod(Dispatch* pDispatch, void* object, Method* pMethod, vector<StkElt>& argsarr, bool bReturnValue)
{
	uint8 args[512];
	uint8* p = args;

	VERIFY(pMethod->m_decl->m_pType->GetFunction()->m_parameters.m_parameters.size() == argsarr.size());
	Type* pReturnType = pMethod->m_decl->m_pType->GetFunction()->m_pReturnType;

	for (unsigned int i = 0; i < argsarr.size(); i++)
	{
		Type* ArgType = pMethod->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[i].m_pType->GetStripped();

		StkElt& elt = argsarr[i];

		if (ArgType->get_Kind() == type_int)
		{
			*(int*)p = elt.toInt();
			p += 4;
		}
		else if (ArgType->get_Kind() == type_unsigned_char)
		{
			*(int*)p = elt.toInt();
			p += 4;
		}
		else if (ArgType->get_Kind() == type_double)
		{
			*(double*)p = elt.toDouble();
			p += 8;
		}
		else
		{
			//ASSERT(elt.m_variant.kind

			//Type* ArgType = method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType->GetStripped();
			if (ArgType->get_Kind() == type_class)
			{
				ASSERT(0);
			}
			else if (ArgType->get_Kind() == type_pointer)
			{
				ArgType = ArgType->GetPointerTo()->GetStripped();

		//		ASSERT(pSourceType->m_type == type_pointer);
				if (ArgType->get_Kind() == type_class)
				{
					void* properType;

					if (ArgType == typeid(System::StringA).GetType())
					{
						Object* pObject = elt.toString();
						properType = pObject;
					}
					else if (ArgType == typeid(System::StringW).GetType())
					{
						Object* pObject = elt.toString();
						properType = pObject;
					}
					else
					{
						Object* pObject = elt.m_variant.kind == VARKIND_NULL? NULL: elt.m_variant.m_pObject;
						ClassType* pSourceType = pObject? pObject->GetType(): NULL;

						if (pObject)
						{
						//	Class* psrc = GetType(pObject);	// debug
						//	ASSERT(psrc->m_qname == ((Class*)pSourceType)->m_qname);	// debug
							
							properType = DynamicCast(pObject, pSourceType->GetClass()/*->GetPointerTo()*/, ArgType->GetClass());
						}
						else
							properType = NULL;
					}

					*(void**)p = properType;
					p += sizeof(void*);
					//dispatch->Invoke(_this, method, &properType, 4);
				}
				else
				{
					ASSERT(0);
				}
			}
			else
				ASSERT(0);
		}

		// TODO, convert to appropriate type

	//	*(void**)p = elt.m_variant.m_pStringA;
		//*(int*)p = elt.toInt();

		//switch (elt
	}

	if (pMethod->m_func == NULL)
		throw -1;

	unsigned int size = p - args;
	size = (size+3) & ~3;

	//long result = pDispatch->Invoke(object, pMethod, args, p - args);
	void_invoke_method(pMethod->m_func, object, args, size);

	/*
	if (bReturnValue)
	{
		if (pReturnType->GetKind() == type_void)
		{
			push(StkElt());	// undefined
		}
		else if (pReturnType->GetKind() == type_int)
		{
			push(StkElt(result));
		}
		else if (pReturnType->GetKind() == type_pointer)
		{
			if (pReturnType->GetPointerTo() == typeid(StringA).GetType())
				push(StkElt((StringA*)result));
			else
				push(StkElt((Object*)result));
		}
		else
		{
			ASSERT(0);
		}
	}
	*/
}

void VM::as_NewObject(unsigned int length)
{
	StkElt name0 = pop();
	int numargs = pop().toInt();
	if (numargs < 0)
		throw -1;

	StringA* name = name0.toStringA();

	char fullname[512];
	sprintf_s(fullname, "System::UI::%s", name->c_str());

	NamedType* pType = pD->LookupNamedType(new StringA(string_copy(fullname)));
	if (pType)
	{
		if (pType->get_Kind() != type_class)
		{
			throw new Exception(WSTR("Not a class type"));
		}
		ClassType* pClass = (ClassType*)pType;

		vector<StkElt> args;
		for (int i = 0; i < numargs; i++)
		{
			args.push_back(pop());
		}

		Dispatch* pDispatch = GetDispatch(pClass);

		StringA* className = pClass->m_name;

	//	void* _this = object;

		// Try all constructors, if more than one constructor matches, there's an ambiguity
		multimap<StringA*, Method*, Ref_Less<StringA>, __gc_allocator>::iterator it = pDispatch->m_methodnames.find(className);
		if (it != pDispatch->m_methodnames.end())
		{
			StringA* cname;
			Method* pMethod = NULL;
			do
			{
				ASSERT((*it).second->m_decl->m_pType != NULL);
				ASSERT((*it).second->m_decl->m_pType->GetFunction() != NULL);

				FunctionType* pFunctionType = (*it).second->m_decl->m_pType->GetFunction();

				/*
				if (pFunctionType->m_parameters.m_parameters.size() == args.size())
				{
					if (pMethod)
						throw -1;

					pMethod = (*it).second;//func = pMethod->m_func;
				}
				*/

				if (args.size() == pFunctionType->m_parameters.m_parameters.size())
				{
					unsigned int i;

					for (i = 0; i < args.size(); i++)
					{
						if (i == pFunctionType->m_parameters.m_parameters.size())
							break;

						Type* pType = pFunctionType->m_parameters.m_parameters[i].m_pType->GetStripped();

						if (args[i].m_variant.kind == VARKIND_INT32 ||
							args[i].m_variant.kind == VARKIND_FLOAT64)
						{
							if (pType->get_Kind() == type_unsigned_char ||
								pType->get_Kind() == type_int ||
								pType->get_Kind() == type_double)
							{
								continue;
							}
						}
						else if (args[i].m_variant.kind == VARKIND_OBJECT)
						{
							ClassType* pObjectType = args[i].m_variant.m_pObject->GetType();

							if (pType->get_Kind() == type_pointer)
							{
								if (pType->GetPointerTo()->get_Kind() == type_class)
								{
									if (pObjectType->IsDerivedFrom(pType->GetPointerTo()->GetClass()))
									{
										continue;
									}
								}
							}
						}
						else
							ASSERT(0);

						break;
					}

					if (i == args.size())
					{
						if (pMethod)
						{
							ASSERT(0);
							throw -1;
						}

						pMethod = (*it).second;
					}
				}
				/*
					//Method* pMethod = (*it).second;
					if (->m_parameters.m_parameters.size() == 0)
					{
						pMethod = (*it).second;//func = pMethod->m_func;
						break;
					}
				*/

				++it;
				cname = (*it).first;
			}
			while (*cname == *className);

			if (pMethod)
			{
				uint8* object = (uint8*)allocate_object(pClass->get_sizeof());
				if (object == NULL)
				{
					ASSERT(0);
					throw -1;
				}

				CallMethod(pDispatch, object, pMethod, args, false);
				//Object* p = newobj(pType);

				push(StkElt((Object*)object));
			}
			else
			{
				ASSERT(0);
				throw -1;
			}

		}
	}
	else
		ASSERT(0);
}

void VM::as_CallFunction(unsigned int length)
{
	StkElt name = pop();
	int numargs = pop().toInt();
	if (numargs < 0)
		throw std::exception("CallFunction: Invalid number of arguments");

	StringA* methodName = name.toStringA();

	StkElt obj = m_pFrame->m_variables.find(methodName)->second;
	if (obj.m_variant.m_pObject != NULL)
	{
		Function* fun = dynamic_cast<Function*>(obj.m_variant.m_pObject);
		ASSERT(fun);

		StackFrame* frame = new StackFrame;
		frame->m_pContext = m_pFrame->m_pContext;
		frame->m_pCaller = m_pFrame;
		frame->m_return_pc = m_pc;	// TODO, not this ??
	//	frame->m_instructionsData = fun->m_codeData;
	//	frame->m_instructionsLength = fun->m_codeLength;

		fun->dispatch(this, frame, numargs);

		m_pFrame = frame;
	}
	else
	{
		ClassType* pType = m_global->GetType();
		Dispatch* pDispatch = GetDispatch(pType);//->m_pDispatch;

		Method* pMethod = pDispatch->GetMethod(methodName);
		VERIFY(pMethod);

		CallMethod(pDispatch, m_global, pMethod, numargs, true);
	}

	/*
	ActionScriptFunction* fun = m_ctx->m_pContext->m_funmap[name.toString()];

	fun->dispatch(this, m_ctx, numargs);
	*/

	/*
	StackFrame* frame = new StackFrame;
	frame->m_pContext = m_ctx->m_pContext;
	frame->m_pCaller = m_ctx;
	frame->m_return_pc = pc;	// TODO, not this ??
	frame->m_instructionsData = fun->m_codeData;
	frame->m_instructionsLength = fun->m_codeLength;

	m_ctx = frame;
	pc = frame->m_instructionsData;
	*/

	//push(StkElt(0L));
}

void VM::as_CallMethod(unsigned int length)
{
	StkElt methodName = pop();
	StkElt object = pop();
	int numargs = pop().toInt();
	if (numargs < 0)
		throw std::exception("Invalid number of arguments");

	if (object.m_variant.kind != VARKIND_OBJECT)
	{
		throw std::exception("Expected object");
	}

	if (true)
	{
		NamedType* pType = object.m_variant.m_pObject->GetType();
		Dispatch* pDispatch = GetDispatch(pType->GetClass());//->m_pDispatch;

		StringA* methodNameStr = methodName.toStringA();
		Method* pMethod = pDispatch->GetMethod(methodNameStr);
		if (pMethod == NULL)
		{
			Method* pMethod = pDispatch->GetMethod(methodNameStr);
			throw std::exception("method not found");
		}

		CallMethod(pDispatch, object.m_variant.m_pObject, pMethod, numargs, true);
	}
	else
	{
		IMembersMap* pob = dynamic_cast<IMembersMap*>(object.m_variant.m_pObject);

		StkElt method = pob->GetMember(methodName.toStringA());

		if (method.m_variant.kind != VARKIND_OBJECT)
		{
			ASSERT(0);
			throw std::exception("Expected object");
		}

		Function* f = dynamic_cast<Function*>(method.m_variant.m_pObject);

		int numargs = pop().toInt();

		StackFrame* pFrame = new StackFrame;

	#if 0
		ctx->m_variables["this"] = object.m_variant.u.m_pObject;

		//std::vector<

		for (int i = 0; i < numargs; i++)
		{
			ctx->m_variables[f->m_args[i]] = pop();
			/*
			StkElt elt = pop();
			if (i > 0) TRACE(", ");

			TRACE("%s", elt.toString().c_str());
			*/
		}

		TRACE(")");
	#endif
		pFrame->m_pCaller = m_pFrame;
		f->dispatch(this, pFrame, numargs);
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
	}
}

void VM::as_GetVariable(unsigned int length)
{
	StkElt name = pop();
	StkElt value = m_pFrame->m_variables[name.toStringA()];
	push(value);

	TRACE(" %s => %s", name.toStringA()->c_str(), value.toStringA()->c_str());
}

void VM::as_SetVariable(unsigned int length)
{
	StkElt value = pop();
	StkElt name = pop();
	m_pFrame->m_variables[name.toStringA()] = value;

	TRACE(" %s <= %s", name.toStringA()->c_str(), value.toStringA()->c_str());
}

void VM::as_NextFrame(unsigned int length)
{
	StkElt elt = m_pFrame->m_variables[ASTR("this")];

	ASSERT(0);
#if 0
	PlacedCharacter* obj = dynamic_cast<PlacedCharacter*>(elt.m_variant.u.m_pObject);
	obj->m_gotoFrame++;
#endif
}

void VM::as_Play(unsigned int length)
{

}

void VM::as_SetTarget(unsigned int length)
{
	StringA target(string_copy((const char*)m_pc, length));

	TRACE("\"%s\"", target.c_str());
}

VM::tyasfunc VM::asfuncs[256] =
{
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_NextFrame,//"ActionNextFrame = 0x04",
	&VM::as_notimpl,//"ActionPrevFrame = 0x05",
	&VM::as_Play,//"ActionPlay = 0x06",
	&VM::as_notimpl,//"ActionStop = 0x07",
	&VM::as_notimpl,//"ActionToggleQuality = 0x08",
	&VM::as_notimpl,//"ActionStopSounds = 0x09",
	&VM::as_notimpl,//"ActionAdd = 0x0A",
	&VM::as_notimpl,//"ActionSubtract = 0x0B",
	&VM::as_notimpl,//"ActionMultiply = 0x0C",
	&VM::as_notimpl,//"ActionDivide = 0x0D",
	&VM::as_notimpl,//"ActionEquals = 0x0E",
	&VM::as_notimpl,//"ActionLess = 0x0F",
	&VM::as_notimpl,//"ActionAnd = 0x10",
	&VM::as_notimpl,//"ActionOr = 0x11",
	&VM::as_notimpl,//"ActionNot = 0x12",
	&VM::as_notimpl,//"ActionStringEquals = 0x13",
	&VM::as_notimpl,//"ActionStringLength = 0x14",
	&VM::as_notimpl,//"ActionStringExtract = 0x15",
	&VM::as_notimpl,//NULL,
	&VM::as_Pop,//"ActionPop = 0x17",
	&VM::as_notimpl,//"ActionToInteger = 0x18",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_GetVariable,//"ActionGetVariable = 0x1C",
	&VM::as_SetVariable,//"ActionSetVariable = 0x1D",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionSetTarget2 = 0x20",
	&VM::as_notimpl,//"ActionStringAdd = 0x21",
	&VM::as_notimpl,//"ActionGetProperty = 0x22",
	&VM::as_notimpl,//"ActionSetProperty = 0x23",
	&VM::as_notimpl,//"ActionCloneSprite = 0x24",
	&VM::as_notimpl,//"ActionRemoveSprite = 0x25",
	&VM::as_notimpl,//"ActionTrace = 0x26",
	&VM::as_notimpl,//"ActionStartDrag = 0x27",
	&VM::as_notimpl,//"ActionEndDrag = 0x28",
	&VM::as_notimpl,//"ActionStringLess = 0x29",
	&VM::as_notimpl,//"ActionThrow = 0x2A",
	&VM::as_notimpl,//"ActionCastOp = 0x2B",
	&VM::as_notimpl,//"ActionImplementsOp = 0x2C",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionRandomNumber = 0x30",
	&VM::as_notimpl,//"ActionMBStringLength = 0x31",
	&VM::as_notimpl,//"ActionCharToAscii = 0x32",
	&VM::as_notimpl,//"ActionAsciiToChar = 0x33",
	&VM::as_notimpl,//"ActionGetTime = 0x34",
	&VM::as_notimpl,//"ActionMBStringExtract = 0x35",
	&VM::as_notimpl,//"ActionMBCharToAscii = 0x36",
	&VM::as_notimpl,//"ActionMBAsciiToChar = 0x37",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionDelete = 0x3A",
	&VM::as_notimpl,//"ActionDelete2 = 0x3B",
	&VM::as_notimpl,//"ActionDefineLocal = 0x3C",
	&VM::as_CallFunction,//"ActionCallFunction = 0x3D",
	&VM::as_notimpl,//"ActionReturn = 0x3E",
	&VM::as_notimpl,//"ActionModulo = 0x3F",
	&VM::as_NewObject,//"ActionNewObject = 0x40",
	&VM::as_DefineLocal2,//"ActionDefineLocal2 = 0x41",
	&VM::as_notimpl,//"ActionInitArray = 0x42",
	&VM::as_notimpl,//"ActionInitObject = 0x43",
	&VM::as_notimpl,//"ActionTypeOf = 0x44",
	&VM::as_notimpl,//"ActionTargetPath = 0x45",
	&VM::as_notimpl,//"ActionEnumerate = 0x46",
	&VM::as_Add2,//"ActionAdd2 = 0x47",
	&VM::as_Less2,//"ActionLess2 = 0x48",
	&VM::as_notimpl,//"ActionEquals2 = 0x49",
	&VM::as_notimpl,//"ActionToNumber = 0x4A",
	&VM::as_notimpl,//"ActionToString = 0x4B",
	&VM::as_notimpl,//"ActionPushDuplicate = 0x4C",
	&VM::as_notimpl,//"ActionStackSwap = 0x4D",
	&VM::as_GetMember,//"ActionGetMember = 0x4E",
	&VM::as_SetMember,//"ActionSetMember = 0x4F",
	&VM::as_notimpl,//"ActionIncrement = 0x50",
	&VM::as_notimpl,//"ActionDecrement = 0x51",
	&VM::as_CallMethod,//"ActionCallMethod = 0x52",
	&VM::as_notimpl,//"ActionNewMethod = 0x53",
	&VM::as_notimpl,//"ActionInstanceOf = 0x54",
	&VM::as_notimpl,//"ActionEnumerate2 = 0x55",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionBitAnd = 0x60",
	&VM::as_notimpl,//"ActionBitOr = 0x61",
	&VM::as_notimpl,//"ActionBitXor = 0x62",
	&VM::as_notimpl,//"ActionBitLShift = 0x63",
	&VM::as_notimpl,//"ActionBitRShift = 0x64",
	&VM::as_notimpl,//"ActionBitURShift = 0x65",
	&VM::as_notimpl,//"ActionStrictEquals = 0x66",
	&VM::as_Greater,//"ActionGreater = 0x67",
	&VM::as_notimpl,//"ActionStringGreater = 0x68",
	&VM::as_notimpl,//"ActionExtends = 0x69",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionGotoFrame = 0x81",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionGetURL = 0x83",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionStoreRegister = 0x87",
	&VM::as_ConstantPool,//"ActionConstantPool = 0x88",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionWaitForFrame = 0x8A",
	&VM::as_SetTarget,//"ActionSetTarget = 0x8B",
	&VM::as_notimpl,//"ActionGoToLabel = 0x8C",
	&VM::as_notimpl,//"ActionWaitForFrame2 = 0x8D",
	&VM::as_notimpl,//"ActionDefineFunction2 = 0x8E",
	&VM::as_notimpl,//"ActionTry = 0x8F",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_With,//"ActionWith = 0x94",
	&VM::as_notimpl,//NULL,
	&VM::as_Push,//"ActionPush = 0x96",
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//NULL,
	&VM::as_notimpl,//"ActionJump = 0x99",
	&VM::as_notimpl,//"ActionGetURL2 = 0x9A",
	&VM::as_DefineFunction,//"ActionDefineFunction = 0x9B",
	&VM::as_notimpl,//NULL,
	&VM::as_If,//"ActionIf = 0x9D",
	&VM::as_notimpl,//"ActionCall = 0x9E",
	&VM::as_notimpl,//"ActionGotoFrame2 = 0x9F",
};

bool VM::next()
{
	if (m_pFrame == NULL)
	{
		return false;
	}

	if (m_flags & 1)	// single-step
	{
		m_breakpoint(this, m_userobject, 2);
	}

	if (m_pc - m_pFrame->m_instructionsData >= m_pFrame->m_instructionsLength)
	{
		m_pc = m_pFrame->m_return_pc;
		m_pFrame = m_pFrame->m_pCaller;

		// ????
		// push function/method result onto stack
		push(0L);

		m_level--;
		return true;
		/*
		if (m_ctx == NULL)
			return false;
			*/
	}

	uint8* p = m_pc;
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
	m_pc = p;
//	TRACE("%s - 0x%x ", ActionNames[ActionCode], ActionCode);
	(this->*asfuncs[ActionCode])(Length);

#ifdef _DEBUG
	if (ActionCode != 0x9B)
	{
	;//	ASSERT(pc == p+Length);
	}

//	pc = p + Length;
#endif

	TRACE("\n");

	return true;
}

/*
class Instructions
{
public:
	uint8* m_data;
	ULONG m_length;

//	std::vector<int> m_offset;
};
*/

/*
void PrintActions(uint8* p, ULONG length)
{
	uint8 ActionCode;
	while ((ActionCode = *p++) != 0)
	{
		TRACE("%s - 0x%x\n", ActionNames[ActionCode], ActionCode);
		uint16 Length = 0;
		if (ActionCode >= 0x80)
		{
			Length = *p++;
			Length |= (long)(*p++)<<8;
		}

		uint8* start = p;
		p = start+Length;
	}
}
*/

}
}
