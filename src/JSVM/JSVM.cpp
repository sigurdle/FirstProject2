#include "stdafx.h"
#include "JSVM.h"

#pragma comment(lib, "LFC")

namespace System
{

DECLSPEC_DLLEXPORT JSVM::StackFrame* g_frame;

#if 0
template<class T>
void disasm_x86(ubyte* pc, T tab[256])
{
	c->operand_size = 4;

	int group1 = 0;
	int group2 = 0;
	int group3 = 0;
	int group4 = 0;

	while (1)
	{
		bool bDone = false;

		uint8 byte = *pc;
		switch (byte)
		{
		case 0xF0:
		case 0xF2:
		case 0xF3:
		{
			ASSERT(group1 == 0);
			group1 = byte;
		}
		break;

		case 0x2E:
		case 0x36:
		case 0x3E:
		case 0x26:
		case 0x64:
		case 0x65:
			{
				ASSERT(group2 == 0);
				group2 = byte;
			}
			break;

		case 0x66:
			{
				ASSERT(group3 == 0);
				group3 = byte;
				c->operand_size = 2;	// word
			}
			break;

		case 0x67:
			{
				ASSERT(group4 == 0);
				group4 = byte;
			}
			break;

		default:
			bDone = true;
		}

		if (bDone)
			break;

		++pc;
	}

//	x86instr* instr = x86_ops[*c->pc].func(c);
	tab[*pc](pc);

	if (group1 == 0xF3)
	{
		return x86_REP(instr);
	}
	else
		return instr;
}
#endif

namespace JSVM
{

ImmutableString<char> empty_str("");
ImmutableString<char> true_str("true");
ImmutableString<char> false_str("false");
ImmutableString<char> null_str("null");
ImmutableString<char> undefined_str("undefined");

ImmutableString<wchar_t> empty_str_w(L"");
ImmutableString<wchar_t> true_str_w(L"true");
ImmutableString<wchar_t> false_str_w(L"false");
ImmutableString<wchar_t> null_str_w(L"null");
ImmutableString<wchar_t> undefined_str_w(L"undefined");
ImmutableString<wchar_t> boolean_str_w(L"boolean");
ImmutableString<wchar_t> number_str_w(L"number");
ImmutableString<wchar_t> string_str_w(L"string");
ImmutableString<wchar_t> object_str_w(L"object");
ImmutableString<wchar_t> function_str_w(L"function");

struct FData
{
	FunctionType* pFunType;
	ScriptFunction* pFun;
};

void x86func2_cdecl(volatile FData* fdata, void* vargs)
{
	VM vm;
	vm.m_gui_threadId = gui_threadId;

	StackFrame frame;
//	frame.m_pContext = m_pFrame->m_pContext;
	frame.m_pCaller = g_frame;
	frame.m_return_pc = NULL;

	uint numargs = fdata->pFunType->m_parameters.m_parameters.size();

	ubyte* args = (ubyte*)vargs;

	Variant arr[64];
//	array<Variant> arr(data);

	for (uint n = 0; n < numargs; ++n)
	{
		Type* pArgType = fdata->pFunType->m_parameters[n].m_pType;

		Variant v;

		switch (pArgType->GetBaseType()->get_Kind())
		{
		case type_int:
		case type_unsigned_int:
			v = *(int*)args;
			args += sizeof(int);
			break;

		case type_float:
			v = *(float*)args;
			args += sizeof(float);
			break;

		case type_double:
		case type_long_double:
			v = *(double*)args;
			args += sizeof(double);
			break;

		case type_pointer:
//		case type_reference:
			{
				// TODO

				void* obj = *(void**)args;
				args += sizeof(void*);
				v = Variant(true, obj, System::GetType(obj, true)->get_pointerToThis());
			}
			break;

		default:
			ASSERT(0);
		}

		arr[numargs-n-1] = v;
	}

	for (size_t i = 0; i < numargs; ++i)
	{
		vm.push(arr[i]);
	}

	fdata->pFun->dispatch(&vm, &frame, numargs);

	if (vm.m_stack.size())
	{
		vm.pop();
	}
}

FData* g_pData;

static void x86func_cdecl(int arg0)
{
	// placeholder
//	volatile FData* fdata = (FData*)0xABCDABCD;
	volatile FData* fdata = (FData*)g_pData;

	x86func2_cdecl(fdata, &arg0);
}

static void __end()
{
}

// TODO, make more general
void RelocateCode(byte* code, size_t codesize, ptrdiff_t diff)
{
	ubyte* end = code + codesize;
	for (ubyte* p = code; p < end; ++p)
	{
		if (p[0] == 0xE8)	// call rel32
		{
			*((int32*)&p[1]) -= diff;
			p += 4;
		}
	}
}

// TODO, make use of all 4096 bytes in page

//ubyte* code;
void* makefunc(FunctionType* pFunType, ScriptFunction* pFun)
{
	const size_t nbytes = (byte*)__end - (byte*)x86func_cdecl;

//	ubyte* code = (ubyte*)VirtualAlloc(NULL, nbytes, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	//memcpy(code, x86func_cdecl, nbytes);

	ubyte* code = (ubyte*)x86func_cdecl;

	FData* fdata = new FData;
	fdata->pFun = pFun;
	fdata->pFunType = pFunType;

	g_pData = fdata;
/*
	for (ubyte* p = code; p < code + nbytes; ++p)
	{
		if (p[0] == 0xCD && p[1] == 0xAB && p[2] == 0xCD && p[3] == 0xAB)
		{
			*(FData**)p = fdata;
			break;
		}
	}
	*/
	ptrdiff_t diff = (char*)code - (char*)x86func_cdecl;

//	RelocateCode(code, nbytes, diff);

#ifdef _AMD64_
	pFun->m_runTimeFunction.BeginAddress = 0;
	pFun->m_runTimeFunction.EndAddress = nbytes;
	
	BOOL success = RtlAddFunctionTable(&pFun->m_runTimeFunction, 1/*entrycount*/, (ULONG_PTR)code);
	if (!success)
	{
		raise(Exception("RtlAddFunctionTable failed"));
	}
#elif _IA64_
	BOOL success = RtlAddFunctionTable(&pFun->m_runTimeFunction, 1/*entrycount*/, (ULONG_PTR)code, TargetGp);
	if (!success)
	{
		raise(Exception("RtlAddFunctionTable failed"));
	}
#endif

	return (void*)code;
}

String Identifier(const Variant& v)
{
	if (v.GetType() == typeid(String))
	{
		return String((StringObject*)v.u.pObject);
	}
	else
	{
		raise(Exception("not an identifier"));
	}
	/*
	switch (v.kind)
	{
	case VARKIND_STRINGA:
	case VARKIND_STRINGW:
		{
			return String((StringObject*)v.m_pObject);
		}
		break;

	default:
		raise(Exception("not an identifier"));
	}
	return NULL;
	*/
}

String toString(const Variant& v)
{
	if (v.GetType() == typeid(String))
	{
		return "\"" + String((StringObject*)v.u.pObject) + "\"";
	}
	else
	{
		return v.ToString();
	}
	/*
	switch (v.kind)
	{
	case VARKIND_STRINGA:
	case VARKIND_STRINGW:
		{
		return "\"" + String((StringObject*)v.m_pObject) + "\"";
		}
		break;

	default:
		return v.ToString();
	}
	*/
}


IO::TextWriter& PrintFields(IO::TextWriter& stream, Type* pType, byte* p, String sep)
{
	pType = pType->GetStripped();

	switch (pType->get_Kind())
	{
	case type_class:
		{
			ClassType* pClassType = static_cast<ClassType*>(pType);

			bool bAny = false;

			for (uint i = 0; i < pClassType->m_pScope->m_orderedDecls.size(); ++i)
			{
				Declarator* decl = pClassType->m_pScope->m_orderedDecls[i];

				if (decl->m_pType && decl->m_pType->get_Kind() != type_function &&
					!decl->get_IsStatic())
				{
					if (bAny) stream << sep;
					bAny = true;

					PrintFields(stream, decl->m_pType, p + decl->m_offset, sep);
				}
			}
		}
		break;

	case type_array:
		{
			ArrayType* pArrayType = static_cast<ArrayType*>(pType);
			size_t elemcount = pArrayType->get_ElemCount();
			Type* pElemType = pArrayType->get_ElemType();

			stream << "[";

			for (size_t i = 0; i < elemcount; ++i)
			{
				if (i > 0) stream << sep;
				PrintFields(stream, pElemType, p + pElemType->get_sizeof()*i, sep); 
			}

			stream << "]";
		}
		break;

	case type_bool:
		{
			stream << *(bool*)p;
		}
		break;

	case type_char:
		{
			stream << *(char*)p;
		}
		break;

	case type_wchar:
		{
			stream << *(wchar_t*)p;
		}
		break;

	case type_signed_char:
		{
			stream << *(signed char*)p;
		}
		break;

	case type_unsigned_char:
		{
			stream << *(unsigned char*)p;
		}
		break;

	case type_short:
		{
			stream << *(short*)p;
		}
		break;

	case type_unsigned_short:
		{
			stream << *(unsigned short*)p;
		}
		break;

	case type_int:
		{
			stream << *(int*)p;
		}
		break;

	case type_unsigned_int:
		{
			stream << *(unsigned int*)p;
		}
		break;

	case type_long:
		{
			stream << *(long*)p;
		}
		break;

	case type_unsigned_long:
		{
			stream << *(unsigned long*)p;
		}
		break;

	case type_int64:
		{
			stream << *(int64*)p;
		}
		break;

	case type_unsigned_int64:
		{
			stream << *(uint64*)p;
		}
		break;

	case type_float:
		{
			stream << *(float*)p;
		}
		break;

	case type_double:
		{
			stream << *(double*)p;
		}
		break;

	default:
		// TODO
		ASSERT(0);
	}

	return stream;
}

Variant MembersMap::GetMember(StringIn name)
{
	return m_members[name];
}

void MembersMap::SetMember(StringIn name, Variant value)
{
	m_members[name] = value;
}

//////////////////////////////

StackFrame::StackFrame() :
	m_instructionsData(nullptr),
	m_instructionsLength(0),
	m_pCaller(nullptr),
	m_return_pc(nullptr),
	m_pContext(nullptr)
{
}

Variant StackFrame::GetVariable(StringIn name)
{
	auto it = m_variables.find(name);
	if (it != m_variables.end())
	{
		return it->second;
	}
	else
		return Variant();
}

/////////////////////////

VM::VM()
{
	m_flags = 0;
	m_breakpoint = nullptr;
	m_userobject = nullptr;

	m_global = nullptr;
	m_pc = nullptr;
	m_pFrame = nullptr;

	OnSetVariable = nullptr;
}

void VM::push(const Variant& value)
{
	m_stack.push_back(value);
}

void VM::push(Variant&& value)
{
	m_stack.push_back(std::move(value));
}

Variant VM::pop()
{
	size_t size = m_stack.size();
	if (size == 0)
	{
		raise(Exception(S("Couldn't pop from empty stack")));
	}

	// NOTE: std::move since we're going to remove it from vector anyway
	Variant elt = std::move(m_stack[size-1]);
	m_stack.RemoveAt(size-1);
	return elt;
}

void VM::op_notimpl(unsigned int length)
{
	raise(Exception(L"JSVM: op not implemented"));
	ASSERT(0);
}

bool IsCompatible(const Variant& arg, Type* argType)
{
	argType = argType->GetStripped();

	if (arg.IsBool())
	{
		if (argType->get_Kind() == type_bool)
		{
			return true;
		}
	}
	else if (arg.IsInt())
	{
		if (
			/*
			argType->get_Kind() == type_signed_char ||
			argType->get_Kind() == type_unsigned_char ||
			argType->get_Kind() == type_short ||
			argType->get_Kind() == type_unsigned_short ||
			*/
			argType->get_Kind() == type_int ||
			argType->get_Kind() == type_unsigned_int ||
			argType->get_Kind() == type_float ||
			argType->get_Kind() == type_double/* ||

			argType->get_Kind() == type_enum*/)

		{
			return true;
		}
	}
	else if (arg.IsFloat())
	{
		if (
			/*
			argType->get_Kind() == type_signed_char ||
			argType->get_Kind() == type_unsigned_char ||
			argType->get_Kind() == type_short ||
			argType->get_Kind() == type_unsigned_short ||
			argType->get_Kind() == type_int ||
			argType->get_Kind() == type_unsigned_int ||
			*/
			argType->get_Kind() == type_float ||
			argType->get_Kind() == type_double)
		{
			return true;
		}
	}
	else if (arg.IsDouble())
	{
		if (
			/*
			argType->get_Kind() == type_signed_char ||
			argType->get_Kind() == type_unsigned_char ||
			argType->get_Kind() == type_short ||
			argType->get_Kind() == type_unsigned_short ||
			argType->get_Kind() == type_int ||
			argType->get_Kind() == type_unsigned_int ||
			*/
			argType->get_Kind() == type_float ||
			argType->get_Kind() == type_double)
		{
			return true;
		}
	}
	else if (arg.IsString())	// TODO, not like this
	{
		if (argType == typeid(String) || argType == typeid(StringIn) ||
			argType == typeid(const String&))
		{
			return true;
		}
	}
#if 0
	else if (arg.kind == VARKIND_STRUCT)
	{
		ClassType* pStructType = arg.m_pType->GetClass();

		if (argType->get_Kind() == type_class)
		{
			if (pStructType == argType->GetClass())
			{
				return true;	// match, ok, continue
			}
		}
		else if (argType->get_Kind() == type_reference)
		{
			Type* refType = argType->GetPointerTo()->GetStripped();

			if (refType->get_Kind() == type_class)
			{
				if (pStructType->IsDerivedFrom(refType->GetClass()))
				{
					return true;	// Derived from, ok, continue
				}
			}
		}
	}
#endif
	else if (argType->get_Kind() == type_pointer &&
			argType->GetPointerTo()->get_Kind() == type_function)
	{
		if (arg.GetObjectType() == typeid(ScriptFunction))
		{
			return true;
		}
		else
			return false;
	}
	else if (arg.IsObject())
	{
		ClassType* pObjectType = arg.GetObjectType();

		if (argType->get_Kind() == type_pointer)
		{
			Type* pPointerTo = argType->GetPointerTo()->GetStripped();
			if (pPointerTo->get_Kind() == type_class)
			{
				if (pObjectType->IsDerivedFrom(pPointerTo->AsClass()))
				{
					return true;	// Derived from, ok, continue
				}
			}
		}
		else if (argType->get_Kind() == type_reference)	// Treat like pointer
		{
			Type* pPointerTo = argType->GetPointerTo()->GetStripped();
			if (pPointerTo->get_Kind() == type_class)
			{
				if (pObjectType->IsDerivedFrom(pPointerTo->AsClass()))
				{
					return true;	// Derived from, ok, continue
				}
			}
		}
	}
	else if (arg.IsNull())
	{
		if (argType->get_Kind() == type_pointer)
		{
			// by commenting this, we can call a function like
			// func(int* iptr) with a null iptr
			// don't know if a function like above is useful from ecmascript though?

		//	if (pType->GetPointerTo()->get_Kind() == type_class)
			{
				return true;	// ok, continue
			}
		}
	}
	else
	{
		raise(Exception("TODO: conversion not implemented"));
	}

	return false;
}

byte* DoArg(Type* ArgType, const Variant& elt, byte* p)
{
	ArgType = ArgType->GetStripped();

	switch (ArgType->get_Kind())
	{
	case type_bool:
		{
			*(bool*)p = elt.ToBool();
			p += 4;//sizeof(bool);
		}
		break;

	case type_signed_char:
		{
			*(signed char*)p = elt.ToInt();
			p += sizeof(signed char);
		}
		break;

	case type_unsigned_char:
		{
			*(unsigned char*)p = elt.ToInt();
			p += sizeof(unsigned char);
		}
		break;

	case type_int:
		{
			*(int*)p = elt.ToInt();
			p += sizeof(int);
		}
		break;

	case type_unsigned_int:
		{
			*(int*)p = elt.ToInt();
			p += sizeof(unsigned int);
		}
		break;

	case type_enum:
		{
		//	EnumType* pEnumType = static_cast<EnumType*>(
			// TODO: Not 100% sure about size

			*(int*)p = elt.ToInt();
			p += sizeof(int);
		}
		break;

	case type_float:
		{
			*(float*)p = elt.ToFloat();
			p += sizeof(float);
		}
		break;

	case type_double:
	case type_long_double:
		{
			*(double*)p = elt.ToDouble();
			p += sizeof(double);
		}
		break;

	default:
		{
			//ASSERT(elt.kind

			//Type* ArgType = method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType->GetStripped();
			if (ArgType->get_Kind() == type_class)
			{
				ClassType* pClassType = ArgType->AsClass();

				if (pClassType == typeid(StringVariant))
				{
				//	*(StringVariant*)p = StringVariant(elt.ToString());
#undef new
					::new ((StringVariant*)p) StringVariant(Identifier(elt));
#define new _new
					p += sizeof(StringVariant);
				}
				else if (pClassType == typeid(String))
				{
#undef new
					::new ((String*)p) String(Identifier(elt));
#define new _new
					p += sizeof(String);
				}
				else
				{
					Dispatch* pDispatch = GetDispatch(pClassType);

					Declarator* pMethod = nullptr;

					auto it = pDispatch->m_methodnames.find(pClassType->m_name);
					if (it != pDispatch->m_methodnames.end())
					{
						do
						{
							Declarator* pMethod2 = it->second;
							if (pMethod2->m_pType->AsFunction()->m_parameters.size() == 1)
							{
								if (/*elt.kind == VARKIND_OBJECT &&*/ pMethod2->m_pType->AsFunction()->m_parameters[0].m_pType->get_Kind() == type_pointer &&
									pMethod2->m_pType->AsFunction()->m_parameters[0].m_pType->GetPointerTo() == elt.GetType())
								{
									// Exact arg type match, just stop searching
									pMethod = pMethod2;
									break;
								}

								if (IsCompatible(elt, pMethod2->m_pType->AsFunction()->m_parameters.m_parameters[0].m_pType))
								{
									if (pMethod)
									{
										raise(Exception("ambiguous: " + pMethod->ToString() + " " + pMethod2->ToString()));
									}
									pMethod = pMethod2;
								}
							}

							++it;
						}
						while (it->first == pClassType->m_name);

						if (pMethod)
						{
							// TODO, TODO

							if (elt.IsObject())
							{
								Type* ArgType = pMethod->m_pType->AsFunction()->m_parameters[0].m_pType;
								if (ArgType->get_Kind() == type_reference ||
									ArgType->get_Kind() == type_pointer)
								{
									void_invoke_method32(pMethod->GetAddress(), p, &elt.u.ptr_val, sizeof(void*));
								}
								else
								{
							//	byte args[256];
							//	byte* endargs = DoArg(pMethod->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[].m_pType, elt, args);
							//	void_invoke_method(pMethod->m_decl->m_offset, p, args, endargs-args);
									void_invoke_method32(pMethod->GetAddress(), p, elt.u.ptr_val, elt.GetType()->get_sizeof());
								}
							}
							/*
							else if (elt.kind == VARKIND_OBJECT)
							{
								pDispatch->void_Invoke(p, pMethod, &elt.m_pObject, sizeof(Object*));
							}
							*/
							else if (elt.IsInt())
							{
								ASSERT(pMethod->m_pType->AsFunction()->m_parameters[0].m_pType->get_Kind() == type_float);
								float val = elt.u.int32_val;

								pDispatch->void_Invoke(p, pMethod, &val, sizeof(float));
							}
							else if (elt.IsDouble())
							{
								// ??
								ASSERT(pMethod->m_pType->AsFunction()->m_parameters[0].m_pType->get_Kind() == type_float);
								float val = elt.ToFloat();
								pDispatch->void_Invoke(p, pMethod, &val, sizeof(float));
							}
							else
							{
								// TODO
								ASSERT(0);
							}
						}
						else
						{
							if (pClassType == elt.GetType()->GetStripped())
							{
								// TODO, sub ??

								// just copy
								memcpy(p, elt.u.ptr_val, elt.GetType()->get_sizeof());
							}
							else
							{
								raise(Exception(L"no matching copy constructor found"));
							}
						}

						p += pClassType->get_sizeof();
					}
					else
					{
						ASSERT(0);
					}

					/*
					// TODO
					// typed
					*(Object**)p = NULL;
					p += sizeof(Object*);
					*(Object**)p = NULL;
					p += sizeof(Object*);
					*(Object**)p = elt.m_pObject;	// TODO IncRef
					p += sizeof(Object*);
					*/
				}
			}
			else if (ArgType->get_Kind() == type_reference)
			{
				Type* ArgType2 = ArgType->GetPointerTo()->GetStripped();
				if (ArgType2->get_Kind() == type_class)
				{
					if (ArgType2 == elt.GetType())
					{
						*(void**)p = elt.GetPtr();
						p += sizeof(void*);
					}
					else if (elt.IsObject())
					{
						if (elt.u.pObject && elt.u.pObject->GetType()->IsDerivedFrom(ArgType2->AsClass()))
						{
							*(void**)p = elt.GetPtr();
							p += sizeof(void*);
						}
						else
						{
							Dispatch* pDispatch = GetDispatch(ArgType2->AsClass());

						//	Convert(ArgType2, m_variant.m_pObject->GetType());

							// Try all constructors, if more than one constructor matches, there's an ambiguity
							auto it = pDispatch->m_methodnames.find(pDispatch->GetClass()->get_Name());
							if (it != pDispatch->m_methodnames.end())
							{
								String cname;
								Declarator* pMethod = NULL;
								do
								{
									Declarator* pMethod = it->second;
									if (pMethod->m_pType->AsFunction()->m_parameters.size() == 1)
									{
										Type* ArgType3 = pMethod->m_pType->AsFunction()->m_parameters[0].m_pType->GetStripped();
										if (ArgType3->get_Kind() == type_pointer)
										{
											ArgType3 = ArgType3->GetPointerTo()->GetStripped();

											if (ArgType3->get_Kind() == type_class)
											{
												if (elt.u.pObject->GetType()->IsDerivedFrom(ArgType3->AsClass()))
												{
													// temp object
													byte* temp = (byte*)_alloca(ArgType3->get_sizeof());

													void_invoke_method32(pMethod->GetAddress(), temp, &elt.u.pObject, sizeof(Object*));

													*(void**)p = temp;
													p += sizeof(void*);

													break;
												}
											}
											else
											{
												raise(Exception(L"not derived from.."));
											}
										}
									}

									++it;
								}
								while (it->first == pDispatch->GetClass()->get_Name());
							}
							else
							{
								raise(Exception(L"not derived from.."));
							}
						}
					}
					else
					{
						if (elt.IsNull())
						{
							raise(Exception(ArgType->ToString() + " cannot be set to null value"));
						}
						else
						{
							raise(Exception(L"Unsupported arg type"));
						}
					}
				}
				else
				{
					raise(Exception(L"ecmacript cannot call function with non-class reference as parameter"));
				}

				//	p += ArgType->get_sizeof();
			}
			else if (ArgType->get_Kind() == type_pointer)
			{
				ArgType = ArgType->GetPointerTo()->GetStripped();

				if (ArgType->get_Kind() == type_function)
				{
					FunctionType* fun = ArgType->AsFunction();
				//	if (fun->m_jsDispatch == NULL)
					{
						ScriptFunction* scriptfun = dynamic_cast<ScriptFunction*>(elt.GetObject());
						void* jsDispatch = makefunc(fun, scriptfun);

						*(void**)p = jsDispatch;
						p += sizeof(void*);
					}
				}

				//		ASSERT(pSourceType->m_type == type_pointer);
				else if (ArgType->get_Kind() == type_char)
				{
					*(char**)p = CString(elt.ToString()).Detach();
					p += sizeof(char*);
				}
				else if (ArgType->get_Kind() == type_wchar)
				{
					*(wchar_t**)p = CStringw(elt.ToString()).Detach();
					p += sizeof(wchar_t*);
				}
				else if (ArgType->get_Kind() == type_class)
				{
					void* properType;

					if (ArgType == typeid(System::StringA).GetType())	// TODO, remove ?
					{
						Object* pObject = elt.ToString();
						properType = pObject;
					}
					else if (ArgType == typeid(System::StringW).GetType())	// TODO, remove ?
					{
						Object* pObject = elt.ToString();
						properType = pObject;
					}
					else if (ArgType->AsClass()->IsPolymorphic())
					{
						if (elt.IsNull())
						{
							properType = nullptr;
						}
						else if (elt.IsObject())
						//if (elt.GetObjectType()->IsDerivedFrom(ArgType->GetClass()))
						{
							properType = DynamicCast(elt.u.ptr_val, nullptr, ArgType->AsClass());
							if (properType == nullptr)
							{
								raise(Exception(ArgType->AsClass()->get_QName() + " is not derived from " + elt.GetObjectType()->get_QName()));
							}
						}
						else
						{
							raise(Exception("object required"));
#if 0
							// Try to cast

							Object* pObject = elt.kind == VARKIND_NULL? NULL: elt.m_pObject;
							ClassType* pSourceType = pObject? pObject->GetType(): NULL;

							if (pObject)
							{
								properType = DynamicCast(pObject, NULL, ArgType->GetClass());
								if (properType == NULL)
								{
									raise(Exception(ArgType->GetClass()->get_QName() + " is not derived from " + pSourceType->GetClass()->get_QName()));
								}
							}
							else
#endif
								properType = nullptr;
						}
					}
					else
					{
						if (elt.GetType()->get_Kind() == type_pointer &&
							elt.GetType()->GetPointerTo()->IsOfType(ArgType))
						{
							properType = elt.GetPtr();//u.ptr_val;
						}
						else
						{
							raise(Exception(ArgType->AsClass()->get_QName() + " is not derived from " + elt.GetType()->AsClass()->get_QName()));
						}
					}

					*(void**)p = properType;
					p += sizeof(void*);
				}
				else
				{
					raise(Exception(L"Unsupported arg type"));
				}
			}
			else
			{
				raise(Exception(L"Unsupported arg type"));
			}
		}
	}

	return p;
}

void VM::op_GetTypeMember(unsigned int length)
{
	Variant member = pop();
	Variant object = pop();

	if (!object.IsObject())
	{
		raise(Exception(S(L"Expected object")));
	}

	String typeName = Identifier(member);

	ClassType* pType = object.GetObjectType();
	if (NamespaceType* pName = dynamic_cast<NamespaceType*>(object.GetObject()))
	{
		Declarator* decl = pName->m_pScope->m_decls.find(typeName)->second;
		if (decl == nullptr)
		{
			raise(Exception(decl->m_name + " is not a member of " + pName->get_QName()));
		}

		NamedType* pType = dynamic_cast<NamedType*>(decl->m_pType);
		if (pType == nullptr)
		{
			raise(Exception(decl->m_name + " is not a typemember of " + pName->get_QName()));
		}

		push(pType);
	}
	else
	{
		raise(Exception(object.ToString() + " is not a type object"));
	}
}

void VM::op_GetMember(unsigned int length)
{
	Variant member = pop();
	Variant object = pop();

	if (!object.IsObject())
	{
		raise(Exception(S(L"Expected object")));
	}

	if (true)
	{
		String propertyName = Identifier(member);

		if (auto pName = __dynamic_cast<NamespaceType*>(object))
		{
			// static const ... = constval;
			Declarator* pDeclarator = pName->m_pScope->GetDeclarator(propertyName);
			if (pDeclarator && pDeclarator->get_IsStatic() && pDeclarator->m_pType->AsFunction() == nullptr && pDeclarator->m_initVal)
			{
				Type* pReturnType = pDeclarator->m_pType;

				switch (pReturnType->GetBaseType()->get_Kind())
				{
				case type_bool:
					{
						bool result = static_cast<SValExp*>(pDeclarator->m_initVal)->m_val & 1;
						push(Variant(result, pReturnType));
					}
					break;

				case type_short:
					{
						short result = static_cast<SValExp*>(pDeclarator->m_initVal)->m_val;
						push(Variant(result, pReturnType));
					}
					break;

				case type_unsigned_short:
					{
						unsigned short result = static_cast<SValExp*>(pDeclarator->m_initVal)->m_val;
						push(Variant(result, pReturnType));
					}
					break;

				case type_int:
					{
						int result = static_cast<SValExp*>(pDeclarator->m_initVal)->m_val;
						push(Variant(result, pReturnType));
					}
					break;

				case type_unsigned_int:
					{
						unsigned int result = static_cast<SValExp*>(pDeclarator->m_initVal)->m_val;
						push(Variant(result, pReturnType));
					}
					break;

				default:
					{
						raise(Exception());
					}
					break;
				}
			}
			else
			{
				Dispatch* pDispatch = GetDispatch(pName);

				Property* pProperty = pDispatch->GetProperties().find(propertyName)->second;
				if (pProperty == NULL)
				{
					raise(Exception(L"property " + pName->get_QName() + "." + propertyName + " not found"));
				}

				if (!pProperty->get_GetMethod()->get_IsStatic())
				{
					raise(Exception(L"property is not a static property"));
				}

				Type* pReturnType = pProperty->get_GetMethod()->get_ReturnType();

				switch (pReturnType->GetBaseType()->get_Kind())
				{
				case type_bool:
					{
						bool result = pProperty->get_GetMethod()->invoke_functionA<bool>(nullptr, 0);
						push(Variant(result, pReturnType));
					}
					break;

				case type_short:
					{
						short result = pProperty->get_GetMethod()->invoke_functionA<short>(nullptr, 0);
						push(Variant(result, pReturnType));
					}
					break;

				case type_unsigned_short:
					{
						unsigned short result = pProperty->get_GetMethod()->invoke_functionA<unsigned short>(nullptr, 0);
						push(Variant(result, pReturnType));
					}
					break;

				case type_int:
					{
						int result = pProperty->get_GetMethod()->invoke_functionA<int>(nullptr, 0);
						push(Variant(result, pReturnType));
					}
					break;

				case type_unsigned_int:
					{
						unsigned int result = pProperty->get_GetMethod()->invoke_functionA<unsigned int>(nullptr, 0);
						push(Variant(result, pReturnType));
					}
					break;

				case type_float:
					{
						float result = pProperty->get_GetMethod()->invoke_functionA<float>(nullptr, 0);
						push(Variant(result, pReturnType));
					}
					break;

				case type_double:
					{
						double result = pProperty->get_GetMethod()->invoke_functionA<double>(nullptr, 0);
						push(Variant(result, pReturnType));
					}
					break;

					/*
				case type_enum:
					{
						// TODO
						int result = pProperty->get_GetMethod()->m_decl->invoke_function<int>(NULL, 0);
						push(Variant(pReturnType, result));
					}
					break;
					*/

				case type_class:
					{
						byte* retval = new byte[pReturnType->get_sizeof()];

						pProperty->get_GetMethod()->struct_invoke_function(nullptr, 0, retval);
						if (pReturnType == typeid(String))
						{
							push(*(String*)retval);
						}
						else
						{
							push(Variant(retval, pReturnType));
						}
					}
					break;

				default:
					{
						// TODO
						Object* result = pProperty->get_GetMethod()->invoke_functionA<Object*>(NULL, 0);
						if (Module::WithinManaged((ULONG_PTR)result))
						{
							push(result);
						}
						else
						{
							push(Variant(true, result,  pReturnType));
						}
					}
				}
			}
		}
		else if (auto pEnum = __dynamic_cast<EnumType*>(object))
		{
			EnumDef* pDef = pEnum->GetItem(propertyName);
			if (pDef)
			{
				push(Variant(pDef->m_value, pEnum));
			}
			else
			{
				raise(Exception(L"enum '" + propertyName + L"' not found"));
			}
		}
		else
		{
			ClassType* pType = object.GetObjectType();

			Dispatch* pDispatch = GetDispatch(pType);
			Property* pProperty = pDispatch->GetProperty(propertyName);
			if (pProperty)
			{
				if (pProperty->get_GetMethod() == nullptr)
				{
					raise(Exception(L"property '" + propertyName + L"' cannot be read"));
				}

				CallMethod(pDispatch, object.u.pObject, pProperty->get_GetMethod(), 0, true);
			}
			else
			{
				raise(Exception(L"property " + pType->get_QName() + "." + propertyName + L" not found"));
				/*
				Gui::UIElement* expandable = dynamic_cast<Gui::UIElement*>(object.m_pObject);
				Object* value = expandable->m_userdata[member.ToString()];

				push(Variant(value));
				*/
			}
		}
	}
	else
	{
		IMembersMap* pob = dynamic_cast<IMembersMap*>(object.u.pObject);

		Variant value = pob->GetMember(Identifier(member));

		push(std::move(value));
	}
}

void VM::op_SetMember(unsigned int length)
{
	Variant value = pop();
	Variant member = pop();
	Variant object = pop();

	if (!object.IsObject())
	{
		raise(Exception(L"Expected object instead of " + object.GetType()->ToString()));
	}

	if (true)
	{
		/*
		if (object.m_pObject == nullptr)
		{
			ASSERT(0);
		}
		*/

//		if (NamespaceType* pName = dynamic_cast<NamespaceType*>(object.m_pObject))
		if (NamespaceType* pName = __dynamic_cast<NamespaceType*>(object))
		{
			NamespaceType* pType = pName;

			Dispatch* pDispatch = GetDispatch(pType);
			Property* pProperty = pDispatch->GetProperty(Identifier(member));
			if (pProperty == NULL)
			{
				raise(Exception(pType->get_QName() + L"." + member.ToString() + " does not not exist"));
			}

			if (pProperty->get_SetMethod() == nullptr)
			{
				raise(Exception(pType->get_QName() + L"." + member.ToString() + " is read only"));
			}

			byte args[256];
			byte* p = DoArg(pProperty->get_SetMethod()->m_pType->AsFunction()->m_parameters.m_parameters[0].m_pType, value, args);
			pProperty->get_SetMethod()->invoke_functionA<void>(args, p-args);
		}
		else
		{
			ClassType* pType = object.GetObjectType();
			Dispatch* pDispatch = GetDispatch(pType);
			Property* pProperty = pDispatch->GetProperty(Identifier(member));
			if (pProperty == NULL)
			{
				raise(Exception(pType->get_QName() + L"." + Identifier(member) + " does not not exist"));
			}

			if (pProperty->get_SetMethod() == nullptr)
			{
				raise(Exception(pType->get_QName() + L"." + Identifier(member) + " is read only"));
			}

			if (pProperty->get_SetMethod()->m_access != AccessSpec_Public)
			{
				raise(Exception(pType->get_QName() + L"." + member.ToString() + " is not a public member"));
			}

			push(value);

			CallMethod(pDispatch, object.u.pObject, pProperty->get_SetMethod(), 1, false);
		}
	}
	else
	{
		IMembersMap* pob = dynamic_cast<IMembersMap*>(object.u.pObject);

		pob->SetMember(Identifier(member), value);
	}
}

void VM::op_With(unsigned int length)
{
	Variant object = pop();

//	DebugTrace(object.ToString());

	if (!object.IsObject())
	{
		throw new Exception(L"Expected object");
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

	pFrame->m_variables[String("this")] = object.u.pObject;

//	TRACE(" %s - %s", object.ToStringA().c_str(), str.c_str());
}

void VM::op_DefineFunction(unsigned int length)
{
	uint8* start = m_pc;

	while (*m_pc)
	{
		++m_pc;
	}
	String funName = nullptr;
	if (start[0])
	{
		funName = String(string_copy((const char*)start, m_pc - start));
	}

	auto it = TypeDatabase::pD->m_namedTypesM.find(funName);
	if (it != TypeDatabase::pD->m_namedTypesM.end())
	{
		raise(Exception("'" + funName + "' already defined"));
	}

	++m_pc;

	uint16 numParams = *m_pc++;
	numParams |= (*m_pc++)<<8;

	ScriptFunction* pFunction = new ScriptFunction(funName);

	/*
	if (funName)
	{
		pFunction->m_name = funName;
	}
	*/

	for (uint i = 0; i < numParams; ++i)
	{
		const char* paramName = (const char*)m_pc;
		while (*m_pc)
		{
			m_pc++;
		}

		pFunction->m_args.push_back(String(string_copy(paramName, (const char*)m_pc - paramName)));

		++m_pc;
	}

	uint16 codeSize = *m_pc++;
	codeSize |= (*m_pc++)<<8;

	pFunction->m_pContext = m_pFrame->m_pContext;
	pFunction->m_codeData = m_pc;
	pFunction->m_codeLength = codeSize;

	m_pc += codeSize;

	if (funName == nullptr)	// anonymous
	{
		push(Variant(pFunction));
	}
	else
	{
		m_pFrame->m_variables[funName] = pFunction;
	}
}

// Create a new constant pool, erase the old one
void VM::op_ConstantPool(unsigned int length)
{
	uint16 count = *m_pc++;
	count |= (*m_pc++)<<8;

	m_pFrame->m_pContext->m_constantPool.clear();

//	m_constantPool.resize(MAX(m_constantPool.size(), count));

	m_pFrame->m_pContext->m_constantPool.reserve(count);

	for (size_t i = 0; i < count; ++i)
	{
		uint8* start = m_pc;

		while (*m_pc)
		{
		//	str = str->Append(*pc++);
			m_pc++;
		}
		String str = String(string_copy((const char*)start, m_pc - start));

		m_pc++;
	//	TRACE("%s, ", str->c_str());

	//	m_constantPool[i] = (str);
		m_pFrame->m_pContext->m_constantPool.Add(Variant(str));
	}
}

void VM::op_Push(unsigned int length)
{
	ubyte* start = m_pc;

	while (m_pc < start+length)
	{
		ubyte type = *m_pc++;
		switch (type)
		{
		case 1:	// 32 bit float
			{
				uint32 value = *m_pc++;
				value |= (*m_pc++)<<8;
				value |= (*m_pc++)<<16;
				value |= (*m_pc++)<<24;

				push(*(float*)&value);
			}
			break;

		case 2:	// null
			{
				push(Variant(nullptr));
			}
			break;

		case 3:	// undefined
			{
				push(Variant());
			}
			break;

		case 5:	// boolean
			{
				ubyte value = *m_pc++;

				push((bool)(value & 1));
			}
			break;

		case 6:	// 64 bit float
			{
				uint64 value = *m_pc++;
				value |= (uint64(*m_pc++))<<8U;
				value |= (uint64(*m_pc++))<<16U;
				value |= (uint64(*m_pc++))<<24U;
				value |= (uint64(*m_pc++))<<32U;
				value |= (uint64(*m_pc++))<<40U;
				value |= (uint64(*m_pc++))<<48U;
				value |= (uint64(*m_pc++))<<56U;

				push(*(double*)&value);
			}
			break;

		case 7:	// 32 bit integer
			{
				int32 value = *m_pc++;
				value |= (*m_pc++)<<8;
				value |= (*m_pc++)<<16;
				value |= (*m_pc++)<<24;

				push(value);
			}
			break;

		case 8:	// 8-bit index into pool
			{
				ubyte index = *m_pc++;

				if (index < m_pFrame->m_pContext->m_constantPool.GetSize())
				{
					push(m_pFrame->m_pContext->m_constantPool[index]);
				}
				else
				{
					DebugTrace(" out of bounds");
				//	push(Variant());
				}
			}
			break;

		case 9:	// 16-bit index into pool
			{
				uint16 index = *m_pc++;
				index |= (*m_pc++)<<8;

				if (index < m_pFrame->m_pContext->m_constantPool.GetSize())
				{
					push(m_pFrame->m_pContext->m_constantPool[index]);
				}
				else
				{
					DebugTrace(" out of bounds");
				//	push(Variant());
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
}

void VM::op_Pop(unsigned int length)
{
	pop();
}

void VM::op_Less2(unsigned int length)
{
	Variant arg2 = pop();
	Variant arg1 = pop();

// TODO

	bool result = arg1.ToInt() < arg2.ToInt();

	push(Variant(result));
}

void VM::op_Greater(unsigned int length)
{
	Variant arg2 = pop();
	Variant arg1 = pop();

// TODO

	bool result = arg1.ToInt() > arg2.ToInt();

	push(Variant(result));
}

void VM::op_Add2(unsigned int length)
{
	Variant arg2 = pop();
	Variant arg1 = pop();

	if ((arg1.IsString() || arg1.IsNull()) || (arg2.IsString() || arg2.IsNull()))
	{
		String value = arg1.ToString() + arg2.ToString();

		push(Variant(value));
	}
	else
	{
		if (arg1.IsDouble() || arg2.IsDouble())
		{
			double value = arg1.ToDouble() + arg2.ToDouble();
			push(Variant(value));
		}
		else if (arg1.IsFloat() || arg2.IsFloat())
		{
			float value = arg1.ToFloat() + arg2.ToFloat();
			push(Variant(value));
		}
		else
		{
			int value = arg1.ToInt() + arg2.ToInt();
			push(Variant(value));
		}
	}
}

void VM::op_Multiply(unsigned int length)
{
	Variant arg2 = pop();
	Variant arg1 = pop();

	if (arg1.IsDouble() || arg2.IsDouble())
	{
		double value = arg1.ToDouble() * arg2.ToDouble();
		push(Variant(value));
	}
	else if (arg1.IsFloat() || arg2.IsFloat())
	{
		float value = arg1.ToFloat() * arg2.ToFloat();
		push(Variant(value));
	}
	else
	{
		int32 value = arg1.ToInt() * arg2.ToInt();
		push(Variant(value));
	}
}

void VM::op_Divide(unsigned int length)
{
	Variant arg2 = pop();
	Variant arg1 = pop();

	if (arg1.IsDouble() || arg2.IsDouble())
	{
		double denom = arg2.ToDouble();
		if (denom == 0)
		{
			raise(Exception("Divide by zero"));
		}
		double value = arg1.ToDouble() / denom;
		push(Variant(value));
	}
	else if (arg1.IsFloat() || arg2.IsFloat())
	{
		float denom = arg2.ToFloat();
		if (denom == 0)
		{
			raise(Exception("Divide by zero"));
		}

		float value = arg1.ToFloat() / denom;
		push(Variant(value));
	}
	else if (arg1.IsLongInteger() || arg2.IsLongInteger())
	{
		long long denom = arg2.ToInt64();
		if (denom == 0)
		{
			raise(Exception("Divide by zero"));
		}

		int64 value = arg1.ToInt64() / denom;
		push(Variant(value));
	}
	else
	{
		int denom = arg2.ToInt();
		if (denom == 0)
		{
			raise(Exception("Divide by zero"));
		}

		int32 value = arg1.ToInt() / denom;
		push(Variant(value));
	}
}

void VM::op_Negate(unsigned int length)
{
	Variant arg = pop();

	if (arg.IsDouble())
	{
		double value = -arg.ToDouble();
		push(Variant(value));
	}
	else if (arg.IsFloat())
	{
		float value = -arg.ToFloat();
		push(Variant(value));
	}
	else
	{
		int32 value = -arg.ToInt();
		push(Variant(value));
	}
}

void VM::op_Subtract(unsigned int length)
{
	Variant arg2 = pop();
	Variant arg1 = pop();

	if (arg1.IsDouble() || arg2.IsDouble())
	{
		double value = arg1.ToDouble() - arg2.ToDouble();
		push(Variant(value));
	}
	else if (arg1.IsFloat() || arg2.IsFloat())
	{
		float value = arg1.ToFloat() - arg2.ToFloat();
		push(Variant(value));
	}
	else
	{
		int32 value = arg1.ToInt() - arg2.ToInt();
		push(Variant(value));
	}
}

void VM::op_StringAdd(unsigned int length)
{
	Variant arg2 = pop();
	Variant arg1 = pop();

	push((arg1.ToString() + arg2.ToString()).ToString());
}

void VM::op_If(unsigned int length)
{
	Variant cond = pop();

	short offset = (*m_pc++);
	offset |= (*m_pc++)<<8;

	if (cond.ToBool())
	{
		m_pc += offset;
	}
}

void VM::op_DefineLocal2(unsigned int length)
{
	Variant name = pop();

	m_pFrame->m_variables.insert(map<String, Variant>::value_type(Identifier(name), Variant()));
}

//			void SetValue(Dispatch* dispatch, void* _this, Method* method, Object* pObject, Type* pSourceType);

byte* VM::GetArgs(FunctionType* pFun, byte* args, Variant* v, unsigned int numargs)
{
	byte* p = args;
	for (size_t i = 0; i < numargs; ++i)
	{
		Type* argType = pFun->m_parameters.m_parameters[i].m_pType->GetStripped();

		Variant& elt = v[i];//pop();

		p = DoArg(argType, elt, p);

		/*
		switch (elt.kind)
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


		// TODO, convert to appropriate type

	//	*(void**)p = elt.m_pStringA;
		//*(int*)p = elt.toInt();

		//switch (elt
	}

	return p;
}

void VM::CallMethod(Dispatch* pDispatch, void* object, Declarator* pMethod, unsigned int numargs, bool bReturnValue)
{
	ubyte args[512];
	ubyte* p = args;

	if (pMethod->m_pType->AsFunction()->m_parameters.m_parameters.size() != numargs)
	{
		raise(Exception(L"Wrong number of arguments"));
	}

	FunctionType* pFunction = pMethod->m_pType->AsFunction();

	Type* pReturnType = pFunction->get_ReturnType()->GetStripped();
	Type* pStrippedReturnType = pReturnType->GetStripped();

	vector<Variant> v;
	for (size_t i = 0; i < numargs; ++i)
	{
		v.push_back(pop());
	}

	p = GetArgs(pFunction, args, v.begin(), numargs);
	uint argssize = (uint)(p - args);
	argssize = (argssize + 3) & ~3;

	DispatcherObject* dispatcherObject = NULL;
	if (pMethod->GetClass()->AsClass()->m_bVT)
	{
		dispatcherObject = dynamic_cast<DispatcherObject*>((Object*)object);
	}

	DWORD threadId;

	if (dispatcherObject)
		threadId = dispatcherObject->m_threadId;
	else 
		threadId = m_gui_threadId;

	if (threadId != GetCurrentThreadId())
	{
		DispatchMsg dmsg;
		dmsg.caller.m_hWaitEvent = CreateEventW(NULL, false, false, nullptr);	// TODO, create once

		dmsg.m_dispatch = pDispatch;
		dmsg.m_object = object;
		dmsg.m_func = pMethod;
		dmsg.m_args = args;
		dmsg.m_args_nbytes = argssize;

	//	String str;
		Variant struct_retval;

		if (bReturnValue)
		{
			if (pReturnType->AsClass())
			{
				// Variant will call destructor on data

				struct_retval.m_pType = pReturnType;
				if (pReturnType->get_sizeof() <= sizeof(VariantValue))
				{
					dmsg.retval_struct = &struct_retval.u.ptr_val;
				}
				else
				{
					struct_retval.u.ptr_val = new byte[pReturnType->get_sizeof()];
					dmsg.retval_struct = struct_retval.u.ptr_val;
				}
			}

			/*
			if (pReturnType->get_Kind() == type_class)
			{
				if (pReturnType->
			// TODO, check that String

				dmsg.retval_struct = &str;
			}
			*/
		}

		if (dispatcherObject)
		{
			PostThreadMessageW(dispatcherObject->m_threadId, WM_USER+1, (WPARAM)2, (LPARAM)&dmsg);
		}
		else if (object)
		{
			PostThreadMessageW(m_gui_threadId, WM_USER+1, (WPARAM)2, (LPARAM)&dmsg);
		}
		else
		{
			PostThreadMessageW(m_gui_threadId, WM_USER+1, (WPARAM)3, (LPARAM)&dmsg);
		}

		WaitForSingleObject(dmsg.caller.m_hWaitEvent, INFINITE);
		CloseHandle(dmsg.caller.m_hWaitEvent);

		if (dmsg.m_exception)
		{
			dmsg.m_exception->raiseme();
		}

		if (bReturnValue)
		{
			switch (pReturnType->GetBaseType()->get_Kind())
			{
			case type_void:
				{
					push(Variant());	// undefined
				}
				break;

			case type_bool:
				{
					push(Variant(dmsg.retval.bool_val, pReturnType));
				}
				break;

			case type_char:
				{
					push(Variant(dmsg.retval.char_val, pReturnType));
				}
				break;

			case type_wchar_t:
				{
					push(Variant(dmsg.retval.wchar_t_val, pReturnType));
				}
				break;

			case type_signed_char:
				{
					push(Variant(dmsg.retval.schar_val, pReturnType));
				}
				break;

			case type_unsigned_char:
				{
					push(Variant(dmsg.retval.uchar_val, pReturnType));
				}
				break;

			case type_short:
				{
					push(Variant(dmsg.retval.short_val, pReturnType));
				}
				break;

			case type_unsigned_short:
				{
					push(Variant(dmsg.retval.ushort_val, pReturnType));
				}
				break;

			case type_int:
				{
					push(Variant(dmsg.retval.int_val, pReturnType));
				}
				break;

			case type_unsigned_int:
				{
					push(Variant(dmsg.retval.uint_val, pReturnType));
				}
				break;

			case type_long:
				{
					push(Variant(dmsg.retval.long_val, pReturnType));
				}
				break;

			case type_unsigned_long:
				{
					push(Variant(dmsg.retval.ulong_val, pReturnType));
				}
				break;

			case type_long_long:
				{
					push(Variant(dmsg.retval.longlong_val, pReturnType));
				}
				break;

			case type_unsigned_long_long:
				{
					push(Variant(dmsg.retval.ulonglong_val, pReturnType));
				}
				break;

			case type_float:
				{
					push(Variant(dmsg.retval.float_val, pReturnType));
				}
				break;

			case type_double:
				{
					push(Variant(dmsg.retval.double_val, pReturnType));
				}
				break;

			case type_class:
				{
					push(std::move(struct_retval));
					// struct_retval is now invalid

#if 0
					if (pReturnType->GetClass() == typeof(String))
					{
					//	push(Variant(*(String*)struct_retval));
						push(Variant(struct_retval, pReturnType->GetClass()));
					}
					else
					{
						// TODO ??

						if (pReturnType->GetClass()->IsPolymorphic())
						{
							push(Variant(struct_retval, pReturnType->GetClass()));
						}
						else
						{
							// TODO: move

							push(Variant(struct_retval, pReturnType->get_sizeof()));

						}
					}
#endif
				}
				break;

		case type_pointer:
		case type_reference:	// Treat like pointer
			{
				if (bReturnValue)
				{
					Type* pReturnType2 = pReturnType->GetPointerTo()->GetStripped();
					if (pReturnType2->get_Kind() == type_class)
					{
						if (dmsg.retval_struct)
						{
							if (pReturnType2->AsClass()->IsPolymorphic())
							{
								ClassType* pClass;
								void* p = LeftMost(dmsg.retval_struct, &pClass);
								push(Variant(true, p, pClass->get_pointerToThis()));

							//	// TODO??
								//Object* obj = dynamic_cast<Object*>((Object*)dmsg.retval_struct);

							//	push(Variant(obj));
							}
							else
							{
								push(Variant(true, dmsg.retval_struct, pReturnType));
							}
						}
						else
						{
							push(Variant((Object*)NULL));
						}
					}
					else
					{
						push(Variant());	// undefined
					}
				}
			}
			break;

			default:
				raise(SystemException("Invalid return type"));
			}
		}
	}
	else
	{
		switch (pReturnType->GetBaseType()->get_Kind())
		{
		case type_void:
			{
				if (object)
					pDispatch->void_Invoke(object, pMethod, args, argssize);
				else
					pMethod->invoke_functionA<void>(args, argssize);

				if (bReturnValue)
				{
					push(Variant());	// undefined
				}
			}
			break;

		case type_bool:
			{
				bool result = pDispatch->bool_Invoke(object, pMethod, args, argssize);
				if (bReturnValue)
				{
					push(Variant(result, pReturnType));
				}
			}
			break;

		case type_int:
		case type_unsigned_int:
			{
				int32 result;

				if (object)
					result = pDispatch->int32_Invoke(object, pMethod, args, argssize);
				else
					result = pMethod->invoke_functionA<int>(args, argssize);

				if (bReturnValue)
				{
					push(Variant(result, pReturnType));
				}
			}
			break;

		case type_long:
		case type_unsigned_long:
			{
				long result;

				if (object)	// TODO, long
					result = pDispatch->Invoke<long>(object, pMethod, args, argssize);
				else
					result = pMethod->invoke_functionA<long>(args, argssize);

				if (bReturnValue)
				{
					push(Variant(result, pReturnType));
				}
			}
			break;

		case type_float:
			{
				float result = pDispatch->Invoke<float>(object, pMethod, args, argssize);
				if (bReturnValue)
				{
					push(Variant(result, pReturnType));
				}
			}
			break;

		case type_double:
			{
				double result = pDispatch->Invoke<double>(object, pMethod, args, argssize);
				if (bReturnValue)
				{
					push(Variant(result, pReturnType));
				}
			}
			break;

		case type_pointer:
		case type_reference:	// Treat like pointer
			{
				void* result;
				if (object)
					result = pDispatch->pointer_Invoke(object, pMethod, args, argssize);
				else
					result = pMethod->pointer_invoke_function(args, argssize);

				if (bReturnValue)
				{
					Type* pReturnType2 = pReturnType->GetPointerTo()->GetStripped();

					if (pReturnType2 == typeid(StringA).GetType())
						push(Variant(static_cast<StringA*>(result)));
					else if (pReturnType2 == typeid(StringW).GetType())
						push(Variant(static_cast<StringW*>(result)));
					else
						push(Variant((Object*)result));
				}
			}
			break;

		case type_class:
			{
				ClassType* pClassType = pReturnType->AsClass();
				if (pClassType == typeid(String))
				{
					String result = pDispatch->String_Invoke(object, pMethod, args, argssize);

					if (bReturnValue)
					{
						push(Variant(result));
					}
				}
				else
				{
					// Variant will call destructor on data

					Variant struct_retval;
				//	struct_retval.kind = VARKIND_STRUCT;
					struct_retval.m_pType = pReturnType;
					void* retval;
					if (pReturnType->get_sizeof() <= sizeof(VariantValue))
					{
						retval = &struct_retval.u.ptr_val;
					}
					else
					{
						struct_retval.u.ptr_val = new byte[pReturnType->get_sizeof()];
						retval = struct_retval.u.ptr_val;
					}

					/*
					size_t size = pClassType->get_sizeof();
					byte* retval = new byte[size];
					*/
					pDispatch->struct_Invoke(object, pMethod, args, argssize, retval);

					if (bReturnValue)
					{
						push(std::move(struct_retval));
						// struct_retval is now invalid

					//	push(Variant(retval, pClassType));
					}
				}
			}
			break;

			/*
		case type_enum:
			{
				int32 result;

				if (object)
					result = pDispatch->int32_Invoke(object, pMethod, args, argssize);
				else
					result = pMethod->m_decl->invoke_function<int>(args, argssize);

				if (bReturnValue)
				{
					push(Variant(result));
				}
			}
			break;
			*/

		default:
			{
				raise(Exception(L"Unsupported return type"));
			}
		}
	}
}

void VM::CallMethod(Dispatch* pDispatch, void* object, Declarator* pMethod, vector<Variant>& argsarr, bool bReturnValue)
{
	uint8 args[512];
	uint8* p = args;

	VERIFY(pMethod->m_pType->AsFunction()->m_parameters.size() == argsarr.size());
	Type* pReturnType = pMethod->m_pType->AsFunction()->m_pReturnType;

	for (unsigned int i = 0; i < argsarr.size(); ++i)
	{
		Type* argType = pMethod->m_pType->AsFunction()->m_parameters[i].m_pType->GetStripped();

		const Variant& elt = argsarr[i];

		p = DoArg(argType, elt, p);
#if 0
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
			//ASSERT(elt.kind

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
						Object* pObject = elt.ToString();
						properType = pObject;
					}
					else if (ArgType == typeid(System::StringW).GetType())
					{
						Object* pObject = elt.ToString();
						properType = pObject;
					}
					else
					{
						Object* pObject = elt.kind == VARKIND_NULL? NULL: elt.m_pObject;
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
#endif
		// TODO, convert to appropriate type

	//	*(void**)p = elt.m_pStringA;
		//*(int*)p = elt.toInt();

		//switch (elt
	}

	/*
	if (pMethod->m_offset == ~0)
	{
		raise(Exception("address of method '" + pDispatch->GetClass()->get_QName() + "::" + pMethod->ToString() + "' was not found"));
		ASSERT(0);
	}
	*/

	uint size = (uint)(p - args);
	size = (size+3) & ~3;

	//long result = pDispatch->Invoke(object, pMethod, args, p - args);

	if (true)
	{
		DispatchMsg dmsg;
		dmsg.caller.m_hWaitEvent = CreateEventW(NULL, FALSE, FALSE, nullptr);	// TODO, create once

		dmsg.m_dispatch = pDispatch;
		dmsg.m_object = object;
		dmsg.m_method = pMethod;
		dmsg.m_args = args;
		dmsg.m_args_nbytes = size;

		PostThreadMessageW(m_gui_threadId, WM_USER+1, (WPARAM)1, (LPARAM)&dmsg);
		WaitForSingleObject(dmsg.caller.m_hWaitEvent, INFINITE);
		CloseHandle(dmsg.caller.m_hWaitEvent);

		if (dmsg.m_exception)
		{
			throw dmsg.m_exception;
		}
	}
	else
	{
		void_invoke_method32(pMethod->m_offset, object, args, size);
	}

	/*
	if (bReturnValue)
	{
		if (pReturnType->GetKind() == type_void)
		{
			push(Variant());	// undefined
		}
		else if (pReturnType->GetKind() == type_int)
		{
			push(Variant(result));
		}
		else if (pReturnType->GetKind() == type_pointer)
		{
			if (pReturnType->GetPointerTo() == typeid(StringA).GetType())
				push(Variant((StringA*)result));
			else
				push(Variant((Object*)result));
		}
		else
		{
			ASSERT(0);
		}
	}
	*/
}

void VM::op_NewObject(unsigned int length)
{
	Variant name0 = pop();
	int numargs = pop().ToInt();
	if (numargs < 0) raise(Exception(L"numargs < 0"));

	if (Type* pType = __dynamic_cast<Type*>(name0))
	{
		pType = pType->GetStripped();

		if (pType->get_Kind() != type_class)
		{
			raise(Exception(L"Not a class type"));
		}
		ClassType* pClass = static_cast<ClassType*>(pType);

		vector<Variant> args;
		args.reserve(numargs);
		for (int i = 0; i < numargs; ++i)
		{
			args.push_back(pop());
		}

		Dispatch* pDispatch = GetDispatch(pClass);

		String className = pClass->m_name;

	//	void* _this = object;

		// Try all constructors, if more than one constructor matches, there's an ambiguity
		auto it = pDispatch->m_methodnames.find(className);
		if (it != pDispatch->m_methodnames.end())
		{
			String cname;
			Declarator* pMethod = nullptr;
			do
			{
				ASSERT(it->second->m_pType != nullptr);

				FunctionType* pFunctionType = it->second->m_pType->AsFunction();
				ASSERT(pFunctionType != nullptr);

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
					uint i;

					for (i = 0; i < args.size(); ++i)
					{
						if (i == pFunctionType->m_parameters.size())
							break;	// Too many arguments given, so doesn't match

						Type* argType = pFunctionType->m_parameters[i].m_pType->GetStripped();

						if (argType == args[i].GetType())
							continue;
					}

					if (i < args.size())
					{
						for (i = 0; i < args.size(); ++i)
						{
							if (i == pFunctionType->m_parameters.size())
								break;	// Too many arguments given, so doesn't match

							Type* argType = pFunctionType->m_parameters[i].m_pType->GetStripped();

							if (IsCompatible(args[i], argType))
								continue;

							break;	// Argument wasn't compatible
						}

						if (i == args.size())
						{
							if (pMethod)
							{
								raise(Exception(L"ambiguity"));
							}

							pMethod = it->second;
						}
					}
					else
					{
						pMethod = it->second;
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
				cname = it->first;
			}
			while (cname == className);

			if (pMethod)
			{
				if (!pMethod->IsImplemented())
				{
					raise(Exception("Implementation of " + pMethod->get_QName() + "not found"));
				}

			//	Object* object = allocate_object(pClass->get_sizeof(), Module::FromAddress((const void*)pMethod->m_decl->m_offset));
				Object* object = allocate_object(pClass->get_sizeof());

				try
				{
					CallMethod(pDispatch, object, pMethod, args, false);
					push(Variant(object));
				}
				catch (Exception* e)
				{
					free_object(object);
					e->raiseme();
				}
				catch (std::exception& e)
				{
					free_object(object);
					throw e;
				}
			}
			else
			{
				raise(Exception(L"method not found"));
			}
		}
	}
	else
	{
		raise(Exception("not a named type"));
	}
}

/*
int some(int j);

int (*(*x))(int j);
*/

IO::TextWriter& WriteSignature(IO::TextWriter& stream, Type* pType, Declarator* decl)
{
	if (pType->get_Kind() == type_pointer ||
		pType->get_Kind() == type_reference)
	{
		if (pType->get_Kind() == type_pointer)
			stream << "*";
		else
			stream << "&";

		IO::StringWriter str2;
		WriteSignature(str2, pType->GetPointerTo(), decl);
	}
	else if (pType->get_Kind() == type_function)
	{
		pType->AsFunction()->m_pReturnType->Write(stream);
		stream << decl->m_name;
		pType->AsFunction()->m_parameters.Write(stream);
	}

	return stream;
}

String GetSignature(Declarator* decl)
{
	IO::StringWriter stream;

	WriteSignature(stream, decl->m_pType, decl);

	return stream.str();

	/*
	FunctionType* pFunType = decl->m_pType->GetFunction();

	if (pFunType->m_pReturnType)
	{
		pFunType->m_pReturnType->Write(stream);
	}

	stream << decl->m_name;

	stream << "";
	*/
}

void VM::op_CallFunction(unsigned int length)
{
	String name = Identifier(pop());
	int numargs = pop().ToInt();
	if (numargs < 0)
	{
		raise(Exception("CallFunction: Invalid number of arguments"));
	}

	Variant obj = m_pFrame->GetVariable(name);
	if (obj.IsPtrObject())
	{
		Function* fun = dynamic_cast<Function*>(obj.u.pObject);
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
		auto it = TypeDatabase::pD->m_procs.find(name);
		if (it != TypeDatabase::pD->m_procs.end())
		{
			auto it2 = it;

			bool found = false;

			do
			{
				FunctionType* pFunctionType = it2->second->m_decl->m_pType->AsFunction();

				if (numargs == pFunctionType->m_parameters.m_parameters.size())
				{
					int i;

					for (i = 0; i < numargs; ++i)
					{
						if (i == pFunctionType->m_parameters.size())
							break;	// Too many arguments given, so doesn't match

						const Variant& arg = *(m_stack.end()-1-i);
						Type* argType = pFunctionType->m_parameters[i].m_pType->GetStripped();

						if (IsCompatible(arg, argType))
							continue;

						break;	// Argument wasn't compatible
					}

					if (i == numargs)
					{
						found = true;
						// TODO ambiguity
						break;
					}
				}

				++it2;
			}
			while (it2 != TypeDatabase::pD->m_procs.end() && it2->first == name);

			if (found)
			{
				FunctionType* pFunctionType = it2->second->m_decl->m_pType->AsFunction();

				vector<Variant> v;
				for (size_t i = 0; i < numargs; ++i)
				{
					v.push_back(pop());
				}

				ubyte args[512];
				ubyte* p = GetArgs(pFunctionType, args, v.begin(), numargs);

			//	int funcspec = pFunctionType->m_funcspec;

				Type* pReturnType = pFunctionType->get_ReturnType();

				switch (pReturnType->GetBaseType()->get_Kind())
				{
				case type_void:
					{
						if (false)
						{
							DispatchMsg dmsg;
							dmsg.caller.m_hWaitEvent = CreateEventW(NULL, false, false, nullptr);	// TODO, create once

							dmsg.m_func = it2->second->m_decl;
							dmsg.m_args = args;
							dmsg.m_args_nbytes = (uint)(p - args);

							PostThreadMessageW(m_gui_threadId, WM_USER+1, (WPARAM)3, (LPARAM)&dmsg);
							WaitForSingleObject(dmsg.caller.m_hWaitEvent, INFINITE);
							CloseHandle(dmsg.caller.m_hWaitEvent);

							if (dmsg.m_exception)
							{
								dmsg.m_exception->raiseme();
							}
						}
						else
						{
							it2->second->m_decl->invoke_functionA<void>(args, p - args);
						}
					}
					break;

				case type_bool:
					{
						if (true)
						{
							DispatchMsg dmsg;
							dmsg.caller.m_hWaitEvent = CreateEventW(NULL, false, false, nullptr);	// TODO, create once

							dmsg.m_func = it2->second->m_decl;
							dmsg.m_args = args;
							dmsg.m_args_nbytes = (uint)(p - args);

							PostThreadMessageW(m_gui_threadId, WM_USER+1, (WPARAM)3, (LPARAM)&dmsg);
							WaitForSingleObject(dmsg.caller.m_hWaitEvent, INFINITE);
							CloseHandle(dmsg.caller.m_hWaitEvent);

							if (dmsg.m_exception)
							{
								dmsg.m_exception->raiseme();
							}

							push(Variant(dmsg.retval.bool_val, pReturnType));
						}
						else
						{
							bool result = it2->second->m_decl->invoke_functionA<bool>(args, p - args) & 1;
							push(Variant(result, pReturnType));
						}
					}
					break;

				case type_char:
				case type_wchar_t:

				case type_signed_char:
				case type_unsigned_char:

				case type_short:
				case type_unsigned_short:

				case type_int:
				case type_unsigned_int:
					{
						int result = it2->second->m_decl->invoke_functionA<int>(args, p - args);
						push(Variant(result, pReturnType));
					}
					break;

				case type_long:
					{
						long result = it2->second->m_decl->invoke_functionA<long>(args, p - args);
						push(Variant(result, pReturnType));
					}
					break;

				case type_unsigned_long:
					{
						unsigned long result = it2->second->m_decl->invoke_functionA<unsigned long>(args, p - args);
						push(Variant(result, pReturnType));
					}
					break;

				case type_float:
					{
						float result = it2->second->m_decl->invoke_functionA<float>(args, p - args);
						push(Variant(result, pReturnType));
					}
					break;

				case type_double:
					{
						double result = it2->second->m_decl->invoke_functionA<double>(args, p - args);
						push(Variant(result, pReturnType));
					}
					break;

				case type_long_double:
					{
						double result = it2->second->m_decl->invoke_functionA<long double>(args, p - args);
						push(Variant(result, pReturnType));
					}
					break;

				case type_class:
					{
						// TODO
						if (pReturnType->AsClass()->m_name == "String")
						{
							String result;
							result = it2->second->m_decl->invoke_functionA<String>(args, p - args);
							push(Variant(std::move(result)));
						}
						else
						{
							byte* ret = new byte[pReturnType->get_sizeof()];
							it2->second->m_decl->struct_invoke_function(args, p - args, ret);
							push(Variant(ret, pReturnType));
						}
					}
					break;

				case type_pointer:
				case type_reference:
					{
						Type* pPointerTo = pReturnType->GetPointerTo()->GetStripped();
						if (pPointerTo->get_Kind() == type_class)
						{
							ClassType* pClass = pPointerTo->AsClass();

							void* result;

							if (true)
							{
								DispatchMsg dmsg;
								dmsg.caller.m_hWaitEvent = CreateEventW(NULL, false, false, NULL);	// TODO, create once

								dmsg.m_func = it2->second->m_decl;
								dmsg.m_args = args;
								dmsg.m_args_nbytes = (uint)(p - args);

								PostThreadMessageW(m_gui_threadId, WM_USER+1, (WPARAM)3, (LPARAM)&dmsg);
								WaitForSingleObject(dmsg.caller.m_hWaitEvent, INFINITE);
								CloseHandle(dmsg.caller.m_hWaitEvent);

								if (dmsg.m_exception)
								{
									throw dmsg.m_exception;
								}

								result = dmsg.retval_struct;
							}
							else
							{
								result = it2->second->m_decl->pointer_invoke_function(args, p - args);
							}

							if (pClass->HasVirtualTable())
							{
							// TODO, check address to know if it's one of our objects

								Object* obj = reinterpret_cast<Object*>(DynamicCast(result, System::GetType(result), typeid(Object)->AsClass()));

								if (obj)
								{
									push(obj);
								}
								else
								{
									// TODO
									ASSERT(0);
								//	push((byte*)result, pClass);
								//	push((byte*)result, pClass);
								}
							}
							else	// struct (no vtable)
							{
								push(Variant((byte*)result, pClass));
							}
						}
						else
						{
							raise(Exception("pointer to != class or interface"));
						}
					}
					break;

				default:
					raise(Exception("Unknown return type"));
				}
			}
			else
			{
				auto it2 = it;

				IO::StringWriter str;

				bool found = false;

				do
				{
					String sig = GetSignature(it2->second->m_decl);

					str << sig << endl;

					++it2;
				}
				while (it2 != TypeDatabase::pD->m_procs.end() && it2->first == name);

				raise(Exception(str.str()));
			}
		}
		else
		{
			auto typit = TypeDatabase::pD->m_namedTypesM.find(name);
			if (typit != TypeDatabase::pD->m_namedTypesM.end())
			{
				vector<Variant> args;
				args.reserve(numargs);
				for (int i = 0; i < numargs; ++i)
				{
					args.push_back(pop());
				}

				ClassType* pClassType = dynamic_cast<ClassType*>(typit->second->GetStripped());
				if (pClassType == NULL)
				{
					raise(Exception("'" + name + L"' not a function or class"));
				}

				String className = pClassType->m_name;

				Dispatch* pDispatch = GetDispatch(pClassType);

				// Try all constructors, if more than one constructor matches, there's an ambiguity
				auto it = pDispatch->m_methodnames.find(className);
				if (it != pDispatch->m_methodnames.end())
				{
					String cname;
					Declarator* pMethod = nullptr;
					do
					{
						ASSERT((*it).second->m_pType != nullptr);
						ASSERT((*it).second->m_pType->AsFunction() != nullptr);

						FunctionType* pFunctionType = it->second->m_pType->AsFunction();

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

							for (i = 0; i < args.size(); ++i)
							{
								if (i == pFunctionType->m_parameters.size())
									break;	// Too many arguments given, so doesn't match

								Type* argType = pFunctionType->m_parameters[i].m_pType->GetStripped();

								if (IsCompatible(args[i], argType))
									continue;

								break;	// Argument wasn't compatible
							}

							if (i == args.size())
							{
								if (pMethod)
								{
									raise(Exception(L"ambiguity"));
									ASSERT(0);
								}

								pMethod = it->second;
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
						cname = it->first;
					}
					while (cname == className);

					if (pMethod)
					{
						if (!pMethod->IsImplemented())
						{
							raise(Exception(pMethod->get_QName() + " not method not implemented"));
						}

						uint8* block = (uint8*)allocate_object(pClassType->get_sizeof());

						CallMethod(pDispatch, block, pMethod, args, false);

						push(Variant(block, pClassType));
					}
					else
					{
						raise(Exception(L"TODO: message"));
						ASSERT(0);
					}
				}
			}
			else
			{
				raise(Exception(L"Function '" + name + "' not found"));
			}
		}

#if 0
		ClassType* pType = m_global->GetType();
		Dispatch* pDispatch = GetDispatch(pType);//->m_pDispatch;

		Method* pMethod = pDispatch->GetMethod(methodName);
		VERIFY(pMethod);

		CallMethod(pDispatch, m_global, pMethod, numargs, true);
#endif
	}

	/*
	ActionScriptFunction* fun = m_ctx->m_pContext->m_funmap[name.ToString()];

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

	//push(Variant(0L));
}

void VM::op_CallMethod(unsigned int length)
{
	Variant methodName = pop();
	Variant object = pop();
	int numargs = pop().ToInt();
	if (numargs < 0)
	{
		raise(Exception(L"Negative number of arguments"));
	}

	if (object.IsUndefined())
	{
		raise(Exception(L"Cannot call method on 'undefined'"));
	}

	if (object.IsNull())
	{
		raise(Exception(L"Cannot call method on null object"));
	}

	if (!object.IsObject())
	{
		raise(Exception(L"Expected object instead of " + object.GetType()->ToString()));
	}

	if (true)
	{
		if (NamespaceType* pName = __dynamic_cast<NamespaceType*>(object))
		{
			Dispatch* pDispatch = GetDispatch(pName);

			String methodNameStr = Identifier(methodName);
			Declarator* pMethod = pDispatch->GetMethod(methodNameStr);
			if (pMethod == NULL)
			{
				Declarator* pMethod = pDispatch->GetMethod(methodNameStr);
				raise(Exception(L"method " + methodNameStr + " not found"));
			}

			CallMethod(pDispatch, NULL, pMethod, numargs, true);
		}
		else
		{
			NamespaceType* pType = dynamic_cast<NamespaceType*>(object.GetObjectType());

			Dispatch* pDispatch = GetDispatch(pType);

			String methodNameStr = Identifier(methodName);

			if (methodNameStr.BeginsWith("op_"))
			{
				if (methodNameStr == "op_Add") methodNameStr = "operator+";
				else if (methodNameStr == "op_Sub") methodNameStr = "operator-";
				else if (methodNameStr == "op_Mul") methodNameStr = "operator*";
				else if (methodNameStr == "op_Div") methodNameStr = "operator/";
				else if (methodNameStr == "op_Mod") methodNameStr = "operator%";
				else if (methodNameStr == "op_And") methodNameStr = "operator&";
				else if (methodNameStr == "op_Or") methodNameStr = "operator|";
				else if (methodNameStr == "op_Xor") methodNameStr = "operator^";
				else if (methodNameStr == "op_LShift") methodNameStr = "operator<<";
				else if (methodNameStr == "op_RShift") methodNameStr = "operator>>";

				else if (methodNameStr == "op_Comma") methodNameStr = "operator,";
				else if (methodNameStr == "op_Arrow") methodNameStr = "operator->";
				else if (methodNameStr == "op_Not") methodNameStr = "operator!";
				else if (methodNameStr == "op_Complement") methodNameStr = "operator~";
				else if (methodNameStr == "op_Subscript") methodNameStr = "operator[]";
				else if (methodNameStr == "op_Paren") methodNameStr = "operator()";

				else if (methodNameStr == "op_Assign") methodNameStr = "operator=";
				else if (methodNameStr == "op_AssignAdd") methodNameStr = "operator+=";
				else if (methodNameStr == "op_AssignSub") methodNameStr = "operator-=";
				else if (methodNameStr == "op_AssignMul") methodNameStr = "operator*=";
				else if (methodNameStr == "op_AssignDiv") methodNameStr = "operator/=";
				else if (methodNameStr == "op_AssignMod") methodNameStr = "operator%=";
				else if (methodNameStr == "op_AssignAnd") methodNameStr = "operator&=";
				else if (methodNameStr == "op_AssignOr") methodNameStr = "operator|=";
				else if (methodNameStr == "op_AssignXor") methodNameStr = "operator^=";
				else if (methodNameStr == "op_AssignLShift") methodNameStr = "operator<<=";
				else if (methodNameStr == "op_AssignRShift") methodNameStr = "operator>>=";

				else if (methodNameStr == "op_Eq") methodNameStr = "operator==";
				else if (methodNameStr == "op_NotEq") methodNameStr = "operator!=";
				else if (methodNameStr == "op_Lt") methodNameStr = "operator<";
				else if (methodNameStr == "op_Gt") methodNameStr = "operator>";
				else if (methodNameStr == "op_LtEq") methodNameStr = "operator<=";
				else if (methodNameStr == "op_GtEq") methodNameStr = "operator>=";
			}

			auto begin_it = pDispatch->m_methodnames.find(methodNameStr);
			auto it = begin_it;
			if (it == pDispatch->m_methodnames.end())
			{
				Declarator* pMethod = pDispatch->GetMethod(methodNameStr);
				raise(Exception(L"method '" + pDispatch->GetClass()->get_QName() + "." + methodNameStr + "' not found"));
			}

			Declarator* pMethod = nullptr;

			do
			{
				Declarator* decl = it->second;
				FunctionType* pFunctionType = decl->m_pType->AsFunction();

				if (pFunctionType->m_parameters.m_parameters.size() == numargs)
				{
					int i;

					for (i = 0; i < numargs; ++i)
					{
						if (i == pFunctionType->m_parameters.m_parameters.size())
							break;	// Too many arguments given, so doesn't match

						Variant& arg = *(m_stack.end()-1-i);

						Type* argType = pFunctionType->m_parameters.m_parameters[i].m_pType->GetStripped();

						if (IsCompatible(arg, argType))
							continue;

						break;	// Argument wasn't compatible
					}

					if (i == numargs)	// All the args were compatible
					{
						// TODO, have
						/*
						if (pMethod)
						{
							raise(Exception(L"ambiguity"));
							ASSERT(0);
						}
						*/

						pMethod = it->second;
					}
				}

				++it;
			}
			while (it->first == methodNameStr);

			if (pMethod)
			{
				if (pMethod->m_static)
				{
					CallMethod(pDispatch, NULL, pMethod, numargs, true);
				}
				else
				{
				//	pMethod->m_decl->m_offset = 236;
					CallMethod(pDispatch, object.GetPtr(), pMethod, numargs, true);
				}
			}
			else
			{
				IO::StringWriter str;
				str << L"no method " << methodNameStr << " found with correct arguments, alternatives: \n";

				for (auto it = begin_it; it->first == methodNameStr; ++it)
				{
					FunctionType* pFunctionType = it->second->m_pType->AsFunction();
					str << "\t" << pFunctionType->ToString() << "\n";
				}

				raise(Exception(str.str()));
			}
		}
	}
	else
	{
		IMembersMap* pob = dynamic_cast<IMembersMap*>(object.u.pObject);

		Variant method = pob->GetMember(Identifier(methodName));

		if (!method.IsObject())
		{
			raise(Exception("Expected object"));
		}

		Function* f = dynamic_cast<Function*>(method.u.pObject);

		int numargs = pop().ToInt();

		StackFrame* pFrame = new StackFrame;

	#if 0
		ctx->m_variables["this"] = object.u.m_pObject;

		//std::vector<

		for (int i = 0; i < numargs; i++)
		{
			ctx->m_variables[f->m_args[i]] = pop();
			/*
			Variant elt = pop();
			if (i > 0) TRACE(", ");

			TRACE("%s", elt.ToString().c_str());
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

void VM::op_GetVariable(unsigned int length)
{
	String name = Identifier(pop());
	Variant value;

//	DebugTrace("GetVariable " << name << "\n");

	// TODO, improve.. I'm just winging
	StackFrame* frame = m_pFrame;
	do
	{
		auto it = frame->m_variables.find(name);
		if (it != frame->m_variables.end())
		{
			value = it->second;
			break;
		}
		frame = frame->m_pCaller;
	}
	while (frame);

	if (frame == nullptr)	// At root
	{
		auto it = TypeDatabase::pD->m_namedTypesM.find(name);
		if (it != TypeDatabase::pD->m_namedTypesM.end())
		{
			auto it2 = it;
			++it2;

			if (it2 != TypeDatabase::pD->m_namedTypesM.end() && it2->first == name)
			{
				NamedTypeMultiMapCollection* coll = new NamedTypeMultiMapCollection(TypeDatabase::pD->m_namedTypesM);
				coll->m_key = name;
				coll->m_begin = it;

				value = coll;
			}
			else
			{
				value = it->second;
			}
		}
		else
		{
			auto it = TypeDatabase::pD->m_procs.find(name);
			if (it != TypeDatabase::pD->m_procs.end())
			{
				auto it2 = it;
				++it2;

				if (it2 != TypeDatabase::pD->m_procs.end() && it2->first == name)
				{
					FunctionObjectMultiMapCollection* coll = new FunctionObjectMultiMapCollection(TypeDatabase::pD->m_procs);
					coll->m_key = name;
				//	coll->m_map = pD->m_procs;
					coll->m_begin = it;
				//	coll->m_it = it;

					value = coll;
				}
				else
				{
					value = it->second;
				}
			}
			else
			{
				raise(Exception("'" + name + "' not found"));
			}
		}
	}

	push(value);

//	DebugTrace(name << "=>" << value.ToString());
}

void VM::op_SetVariable(unsigned int length)
{
	Variant value = pop();
	String name = Identifier(pop());

	// TODO, improve.. I'm just winging
	StackFrame* frame = m_pFrame;
	do
	{
		auto it = frame->m_variables.find(name);
		if (it != frame->m_variables.end())
		{
			if (OnSetVariable)
			{
				OnSetVariable(frame, name, value);
			}

			it->second = value;
			break;
		}
		frame = frame->m_pCaller;
	}
	while (frame);

	if (frame == nullptr)
	{
		// TODO, set global variable
	//	m_pFrame->m_variables[name.ToStringA()] = value;
	}

//	TRACE(" %s <= %s", CString(name.ToStringA()).c_str(), CString(value.ToStringA()).c_str());
//	DebugTrace(name << "<=" << value.ToString());
}

void VM::op_Typeof(unsigned int length)
{
	Variant value = pop();
	if (value.IsNull())
	{
		push(Variant(&null_str_w));
	}
	else if (value.IsUndefined())
	{
		push(Variant(&undefined_str_w));
	}
	else if (value.IsBool())
	{
		push(Variant(&boolean_str_w));
	}
	else if (value.IsObject())
	{
		// TODO: Check if function

		push(Variant(&object_str_w));
	}
	else if (value.IsFunction())
	{
		push(Variant(&function_str_w));
	}
	else if (value.IsNumberOrEnum())
	{
		push(Variant(&number_str_w));
	}
	else if (value.IsString())
	{
		push(Variant(&string_str_w));
	}
	else
	{
		raise(Exception("unknown type"));
	}
}

VM::tyasfunc VM::asfuncs[256] =
{
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionNextFrame = 0x04",
	&VM::op_notimpl,//"ActionPrevFrame = 0x05",
	&VM::op_GetTypeMember,//"GetTypeMember = 0x06",
	&VM::op_notimpl,//"ActionStop = 0x07",
	&VM::op_notimpl,//"ActionToggleQuality = 0x08",
	&VM::op_Negate,
	&VM::op_notimpl,//"ActionAdd = 0x0A",
	&VM::op_Subtract,//"ActionSubtract = 0x0B",
	&VM::op_Multiply,//"ActionMultiply = 0x0C",
	&VM::op_Divide,//"ActionDivide = 0x0D",
	&VM::op_notimpl,//"ActionEquals = 0x0E",
	&VM::op_notimpl,//"ActionLess = 0x0F",
	&VM::op_notimpl,//"ActionAnd = 0x10",
	&VM::op_notimpl,//"ActionOr = 0x11",
	&VM::op_notimpl,//"ActionNot = 0x12",
	&VM::op_notimpl,//"ActionStringEquals = 0x13",
	&VM::op_notimpl,//"ActionStringLength = 0x14",
	&VM::op_notimpl,//"ActionStringExtract = 0x15",
	&VM::op_notimpl,//NULL,
	&VM::op_Pop,//"ActionPop = 0x17",
	&VM::op_notimpl,//"ActionToInteger = 0x18",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_GetVariable,//"ActionGetVariable = 0x1C",
	&VM::op_SetVariable,//"ActionSetVariable = 0x1D",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionSetTarget2 = 0x20",
	&VM::op_StringAdd,//"ActionStringAdd = 0x21",
	&VM::op_notimpl,//"ActionGetProperty = 0x22",
	&VM::op_notimpl,//"ActionSetProperty = 0x23",
	&VM::op_notimpl,//"ActionCloneSprite = 0x24",
	&VM::op_notimpl,//"ActionRemoveSprite = 0x25",
	&VM::op_notimpl,//"ActionTrace = 0x26",
	&VM::op_notimpl,//"ActionStartDrag = 0x27",
	&VM::op_notimpl,//"ActionEndDrag = 0x28",
	&VM::op_notimpl,//"ActionStringLess = 0x29",
	&VM::op_notimpl,//"ActionThrow = 0x2A",
	&VM::op_notimpl,//"ActionCastOp = 0x2B",
	&VM::op_notimpl,//"ActionImplementsOp = 0x2C",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionRandomNumber = 0x30",
	&VM::op_notimpl,//"ActionMBStringLength = 0x31",
	&VM::op_notimpl,//"ActionCharToAscii = 0x32",
	&VM::op_notimpl,//"ActionAsciiToChar = 0x33",
	&VM::op_notimpl,//"ActionGetTime = 0x34",
	&VM::op_notimpl,//"ActionMBStringExtract = 0x35",
	&VM::op_notimpl,//"ActionMBCharToAscii = 0x36",
	&VM::op_notimpl,//"ActionMBAsciiToChar = 0x37",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionDelete = 0x3A",
	&VM::op_notimpl,//"ActionDelete2 = 0x3B",
	&VM::op_notimpl,//"ActionDefineLocal = 0x3C",
	&VM::op_CallFunction,//"ActionCallFunction = 0x3D",
	&VM::op_notimpl,//"ActionReturn = 0x3E",
	&VM::op_notimpl,//"ActionModulo = 0x3F",
	&VM::op_NewObject,//"ActionNewObject = 0x40",
	&VM::op_DefineLocal2,//"ActionDefineLocal2 = 0x41",
	&VM::op_notimpl,//"ActionInitArray = 0x42",
	&VM::op_notimpl,//"ActionInitObject = 0x43",
	&VM::op_Typeof,//"ActionTypeOf = 0x44",
	&VM::op_notimpl,//"ActionTargetPath = 0x45",
	&VM::op_notimpl,//"ActionEnumerate = 0x46",
	&VM::op_Add2,//"ActionAdd2 = 0x47",
	&VM::op_Less2,//"ActionLess2 = 0x48",
	&VM::op_notimpl,//"ActionEquals2 = 0x49",
	&VM::op_notimpl,//"ActionToNumber = 0x4A",
	&VM::op_notimpl,//"ActionToString = 0x4B",
	&VM::op_notimpl,//"ActionPushDuplicate = 0x4C",
	&VM::op_notimpl,//"ActionStackSwap = 0x4D",
	&VM::op_GetMember,//"ActionGetMember = 0x4E",
	&VM::op_SetMember,//"ActionSetMember = 0x4F",
	&VM::op_notimpl,//"ActionIncrement = 0x50",
	&VM::op_notimpl,//"ActionDecrement = 0x51",
	&VM::op_CallMethod,//"ActionCallMethod = 0x52",
	&VM::op_notimpl,//"ActionNewMethod = 0x53",
	&VM::op_notimpl,//"ActionInstanceOf = 0x54",
	&VM::op_notimpl,//"ActionEnumerate2 = 0x55",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionBitAnd = 0x60",
	&VM::op_notimpl,//"ActionBitOr = 0x61",
	&VM::op_notimpl,//"ActionBitXor = 0x62",
	&VM::op_notimpl,//"ActionBitLShift = 0x63",
	&VM::op_notimpl,//"ActionBitRShift = 0x64",
	&VM::op_notimpl,//"ActionBitURShift = 0x65",
	&VM::op_notimpl,//"ActionStrictEquals = 0x66",
	&VM::op_Greater,//"ActionGreater = 0x67",
	&VM::op_notimpl,//"ActionStringGreater = 0x68",
	&VM::op_notimpl,//"ActionExtends = 0x69",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionGotoFrame = 0x81",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionGetURL = 0x83",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionStoreRegister = 0x87",
	&VM::op_ConstantPool,//"ActionConstantPool = 0x88",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionWaitForFrame = 0x8A",
	&VM::op_notimpl,//"ActionSetTarget = 0x8B",
	&VM::op_notimpl,//"ActionGoToLabel = 0x8C",
	&VM::op_notimpl,//"ActionWaitForFrame2 = 0x8D",
	&VM::op_notimpl,//"ActionDefineFunction2 = 0x8E",
	&VM::op_notimpl,//"ActionTry = 0x8F",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_With,//"ActionWith = 0x94",
	&VM::op_notimpl,//NULL,
	&VM::op_Push,//"ActionPush = 0x96",
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//NULL,
	&VM::op_notimpl,//"ActionJump = 0x99",
	&VM::op_notimpl,//"ActionGetURL2 = 0x9A",
	&VM::op_DefineFunction,//"ActionDefineFunction = 0x9B",
	&VM::op_notimpl,//NULL,
	&VM::op_If,//"ActionIf = 0x9D",
	&VM::op_notimpl,//"ActionCall = 0x9E",
	&VM::op_notimpl,//"ActionGotoFrame2 = 0x9F",

	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl,
	&VM::op_notimpl
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

#if 0
		// ????
		// push function/method result onto stack
		push(0L);
#endif

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

	uint Length = 0;
	if (ActionCode >= 0x80)
	{
		Length = *p++;
		Length |= (int)(*p++)<<8;
	}
	m_pc = p;
	(this->*asfuncs[ActionCode])(Length);

#ifdef _DEBUG
	if (ActionCode != 0x9B)
	{
	;//	ASSERT(pc == p+Length);
	}

//	pc = p + Length;
#endif

//	DebugTrace("\n");

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

ImmutableString<char> ActionNames[256] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"Negate",
	"Add",
	"Subtract",
	"Multiply",
	"Divide",
	"Equals",
	"Less",
	"And",
	"Or",
	"Not",
	"StringEquals",
	"StringLength",
	"StringExtract",
	NULL,
	"Pop",
	"ToInteger",
	NULL,
	NULL,
	NULL,
	"GetVariable",
	"SetVariable",
	NULL,
	NULL,
	NULL,
	"StringAdd",
	"GetProperty",
	"SetProperty",
	NULL,
	NULL,
	"Trace",
	NULL,
	NULL,
	"StringLess",
	"Throw",
	"CastOp",
	"ImplementsOp",
	NULL,
	NULL,
	NULL,
	"RandomNumber",
	"MBStringLength",
	"CharToAscii",
	"AsciiToChar",
	"GetTime",
	"MBStringExtract",
	"MBCharToAscii",
	"MBAsciiToChar",
	NULL,
	NULL,
	"Delete",
	"Delete2",
	"DefineLocal",
	"CallFunction",
	"Return",
	"Modulo",
	"NewObject",
	"DefineLocal2",
	"InitArray",
	"InitObject",
	"TypeOf",
	NULL,
	"Enumerate",
	"Add2",
	"Less2",
	"Equals2",
	"ToNumber",
	"ToString",
	"PushDuplicate",
	"StackSwap",
	"GetMember",
	"SetMember",
	"Increment",
	"Decrement",
	"CallMethod",
	"NewMethod",
	"InstanceOf",
	"Enumerate2",
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
	"BitAnd",
	"BitOr",
	"BitXor",
	"BitLShift",
	"BitRShift",
	"BitURShift",
	"StrictEquals",
	"Greater",
	"StringGreater",
	"Extends",
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
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"StoreRegister",
	"ConstantPool",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"DefineFunction2",
	"Try",
	NULL,
	NULL,
	NULL,
	NULL,
	"With",
	NULL,
	"Push",
	NULL,
	NULL,
	"Jump",
	NULL,
	"DefineFunction",
	NULL,
	"If",
	"Call",
	NULL,
};

ScriptFunction::ScriptFunction() :
	m_codeData(nullptr),
	m_pContext(nullptr)
{
#ifdef _WIN64
	m_runTimeFunction.BeginAddress = 0;
	m_runTimeFunction.EndAddress = 0;
#endif
}

ScriptFunction::ScriptFunction(StringIn name) : m_name(name),
	m_codeData(nullptr),
	m_pContext(nullptr)
{
#ifdef _WIN64
	m_runTimeFunction.BeginAddress = 0;
	m_runTimeFunction.EndAddress = 0;
#endif
}

ScriptFunction::~ScriptFunction()
{
#ifdef _WIN64
	if (m_runTimeFunction.BeginAddress)
	{
		BOOL success = RtlDeleteFunctionTable(&m_runTimeFunction);
		ASSERT(success);
	}
#endif
}

size_t ScriptFunction::get_NumArgs()
{
	return m_args.size();
}

String ScriptFunction::ToString()
{
	IO::StringWriter stream;
	stream << m_name << "(";
	for (size_t i = 0; i < m_args.size(); ++i)
	{
		if (i > 0) stream << ",";
		stream << m_args[i];
	}
	stream << ")";
	return stream.str();
}

void ScriptFunction::dispatch(VM* vm, StackFrame* pFrame, uint numargs)
{
#if 0
	if (pFrame->m_variables.find("this") == pFrame->m_variables.end())	// TODO, not
		pFrame->m_variables["this"] = (Object*)this;//object.u.m_pObject;
#endif

	for (uint i = 0; i < numargs; ++i)
	{
		Variant elt = vm->pop();

		if (m_args.size() > i)
		{
			pFrame->m_variables[m_args[i]] = elt;
		}
	}

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

JSVMEXT void Disasm(ScriptFunction* function)
{
	DasmContext context;
	context.pc = function->m_codeData;
	byte* end = function->m_codeData + function->m_codeLength;

	while (context.pc < end)
	{
		Instruction* instr = disasm(&context, NULL);

		Std::Out << context.pc - function->m_codeData << "\t";

		String strdasm = &ActionNames[instr->op];

		Std::Out << strdasm << endl;
	}
}

}	// JSVM

JSVMEXT void test_callme(void (*f)(Object*), Object* p)
{
	f(p);
}

}	// System
