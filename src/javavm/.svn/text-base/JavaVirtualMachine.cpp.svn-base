#include "stdafx.h"
#include "javavm.h"

#include "ZIP/ZIP.h"

namespace System
{
using namespace std;
using namespace IO;

FILE* fplog;

void flog(const char* str, ...)
{
	/*
#if _WINDOWS
	va_list va;
	va_start(va, str);

	if (fplog)
	{
		vfprintf(fplog, str, va);
		fflush(fplog);
	}
#endif
	*/
}

namespace javavm
{

	uint32 objcount;

JavaClass* pCharClass = new JavaClass(2);
JavaClass* pBooleanClass = new JavaClass(1);
JavaClass* pByteClass = new JavaClass(1);
JavaClass* pShortClass = new JavaClass(2);
JavaClass* pIntClass = new JavaClass(4);
JavaClass* pLongClass = new JavaClass(8);
JavaClass* pFloatClass = new JavaClass(4);
JavaClass* pDoubleClass = new JavaClass(8);

JavaClass* pCharArrayClass;
JavaClass* pBooleanArrayClass;
JavaClass* pByteArrayClass;
JavaClass* pShortArrayClass;
JavaClass* pIntArrayClass;
JavaClass* pLongArrayClass;
JavaClass* pFloatArrayClass;
JavaClass* pDoubleArrayClass;

Type* _ParseFieldType(const char*& p);

JavaClass* GetArrayClass(StringIn className, JavaClass* pArrayOf, JProcess* c)
{
	JavaClass* pClass = c->m_classes[className];
	if (pClass == NULL)
	{
		pClass = new JavaClass;
		pClass->m_p = c->m_pClassClass->CreateInstance();
		pClass->m_p->m_pClass = c->m_pClassClass;
		pClass->m_pSuperClass = c->m_pObjectClass;
		pClass->m_name = className;
		pClass->m_pArrayOf = pArrayOf;
		pClass->m_instanceFieldSize = sizeof(ArrayFields);

#if 0
		// TODO ?? BaseClass vector that have this field ?
		{
			JavaField* pField = new JavaField(pClass);
			pField->m_access_flag

			pClass->m_fields_count = 1;
			pClass->m_fields = new JavaMethod*[1];
			pClass->m_fields[0] = pField;

			pClass->m_fieldsByName[
		}
#endif

		c->m_classes[className] = pClass;
	}

	return pClass;
}

JavaClass* GetClass(Type* pType, Thread* c)
{
	if (pType->m_pClass == NULL)
	{
		switch (pType->kind)
		{
		case Type::BaseType_bool:
			pType->m_pClass = pBooleanClass;
			break;

		case Type::BaseType_wchar:
			pType->m_pClass = pCharClass;
			break;

		case Type::BaseType_byte:
			pType->m_pClass = pByteClass;
			break;

		case Type::BaseType_short:
			pType->m_pClass = pShortClass;
			break;

		case Type::BaseType_int:
			pType->m_pClass = pIntClass;
			break;

		case Type::BaseType_long:
			pType->m_pClass = pLongClass;
			break;

		case Type::BaseType_float:
			pType->m_pClass = pFloatClass;
			break;

		case Type::BaseType_double:
			pType->m_pClass = pDoubleClass;
			break;

		case Type::Type_array:
			{
				if (pType->className == NULL)
				{
				}

				pType->m_pClass = GetArrayClass(pType->className, GetClass(pType->u.arrayof, c), c->m_vm);

				/*
				pType->m_pClass = c->LoadClass(pType->className);
				if (pType->m_pClass == NULL)
				{
					JavaClass* pClass = GetClass(pType->u.arrayof, c);
					ASSERT(pClass);

					pType->m_pClass = new JavaClass;
					pType->m_pClass->m_pClass = c->m_vm->m_pClassClass;
					pType->m_pClass->m_name = pType->className;
					pType->m_pClass->m_pSuperClass = c->LoadClass(&StringA(true, "java/lang/Object"));
					pType->m_pClass->m_pArrayOf = pClass;
					pType->m_pClass->m_instanceFieldSize = sizeof(ArrayFields);

					c->m_vm->m_classes[pType->className] = pType->m_pClass;
				}
				*/
			}
			break;

		default:
			pType->m_pClass = c->LoadClass(pType->className);
		}
	}

	ASSERT(pType->m_pClass);

	return pType->m_pClass;
}

void TraceObject(JavaObject* ref)
{
	if (ref == NULL)
	{
		LOG("null");
	}
	else if (ref && (int)ref->m_pClass > 10 && ref->m_pClass->GetName() == "java/lang/String")
	{
		JavaField* pField = ref->m_pClass->GetFieldByName("value");
		JavaObject* pValue = *(ObjectRef*)(ref->m_data + pField->m_offset);
		if (pValue)
		{
			LOG("\"%*.*S\"", GetArrayLength(pValue), GetArrayLength(pValue), GetArrayData(pValue));
		}
		else
		{
			LOG("nullstr");
		}
	}
	else
	{
		LOG("%p", ref);
	}
}

/*
Operand::Operand(ObjectRef& r)
{
}
*/

/*
Operand::Operand(JavaObject* r)
{
	ASSERT(r == NULL || dynamic_cast<JavaObject*>(r));
	kind = 4;
	u.ref = r;
}
*/

///////////////////////////
// Frame

void Frame::push(Operand value)
{
//	LOG("%X - push(%d 0x%X)\n", this, (long)value._longlong, (long)value._longlong);
	m_operands.Add(value);
}

Operand Frame::pop()
{
	int size = m_operands.GetSize();
	if (size <= 0) THROW(-1);
	Operand elt = m_operands[m_operands.GetSize()-1];
	m_operands.RemoveAt(m_operands.GetSize()-1);
//	LOG("%X - pop(%d 0x%X)\n", this, (long)elt._longlong, (long)elt._longlong);
	return elt;
}

//typedef int (*jop_func)(Thread* c);

///////////////////////////
// Thread

uint8* Frame::jop_notimpl(Thread* c, uint8* pc)
{
	LOG("\top not implemented %d", *pc);
	VERIFY(0);
	pc++;
	return pc;
}

uint8* Frame::jop_nop(Thread* c, uint8* pc)
{
	pc++;
	LOG("nop");
	return pc;
}

uint8* Frame::jop_if_icmpeq(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	jint value2 = pop();
	jint value1 = pop();

	LOG("if_icmpeq %d == %d", value1, value2);

	if (value1 == value2)
	{
		pc = start + offset;
	}

	return pc;
}

uint8* Frame::jop_if_icmpne(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	jint value2 = pop();
	jint value1 = pop();

	LOG("if_icmpne");

	if (value1 != value2)
	{
		pc = start + offset;
	}

	return pc;
}

uint8* Frame::jop_if_icmplt(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	jint value2 = pop();
	jint value1 = pop();

	LOG("if %d < %d", value1, value2);

	if (value1 < value2)
	{
		pc = start + offset;
	}

	return pc;
}

uint8* Frame::jop_if_icmpge(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	jint value2 = pop();
	jint value1 = pop();

	LOG("if %d >= %d", value1, value2);

	if (value1 >= value2)
	{
		pc = start + offset;
	}

	return pc;
}

uint8* Frame::jop_if_icmpgt(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	jint value2 = pop();
	jint value1 = pop();

	LOG("if %d > %d", value1, value2);

	if (value1 > value2)
	{
		pc = start + offset;
	}

	return pc;
}

uint8* Frame::jop_if_icmple(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	jint value2 = pop();
	jint value1 = pop();

	LOG("if %d <= %d", value1, value2);

	if (value1 <= value2)
	{
		pc = start + offset;
	}

	return pc;
}

uint8* Frame::jop_if_acmpeq(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	JavaObject* value2 = pop();
	JavaObject* value1 = pop();

	LOG("if %p == %p", value1, value2);

	if (value1 == value2)
	{
		pc = start + offset;
	}

	return pc;
}

uint8* Frame::jop_if_acmpne(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	JavaObject* value2 = pop();
	JavaObject* value1 = pop();

	LOG("if %p != %p", value1, value2);

	if (value1 != value2)
	{
		pc = start + offset;
	}

	return pc;
}

uint8* Frame::jop_lcmp(Thread* c, uint8* pc)
{
	pc++;

	LOG("lcmp - ");

	LONGLONG value2 = pop();
	LONGLONG value1 = pop();

	if (value1 > value2)
		push(1L);
	else if (value1 < value2)
		push(-1L);
	else
		push(0L);

	return pc;
}

// TODO NAN
uint8* Frame::jop_fcmpl(Thread* c, uint8* pc)
{
	pc++;

	LOG("fcmpg - ");

	float value2 = pop();
	float value1 = pop();

	if (value1 > value2)
		push(1L);
	else if (value1 < value2)
		push(-1L);
	else
		push(0L);

	return pc;
}

// TODO NAN
uint8* Frame::jop_fcmpg(Thread* c, uint8* pc)
{
	pc++;

	LOG("fcmpg - ");

	float value2 = pop();
	float value1 = pop();

	if (value1 > value2)
		push(1L);
	else if (value1 < value2)
		push(-1L);
	else
		push(0L);

	return pc;
}

// TODO NAN
uint8* Frame::jop_dcmpl(Thread* c, uint8* pc)
{
	pc++;

	LOG("dcmpg - ");

	double value2 = pop();
	double value1 = pop();

	if (value1 > value2)
		push(1L);
	else if (value1 < value2)
		push(-1L);
	else
		push(0L);

	return pc;
}

// TODO NAN
uint8* Frame::jop_dcmpg(Thread* c, uint8* pc)
{
	pc++;

	LOG("dcmpg - ");

	double value2 = pop();
	double value1 = pop();

	if (value1 > value2)
		push(1L);
	else if (value1 < value2)
		push(-1L);
	else
		push(0L);

	return pc;
}

uint8* Frame::jop_ifnull(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	LOG("ifnull - ");

	JavaObject* ref = pop();
	if (ref == 0) pc = start + offset;

	return pc;
}

uint8* Frame::jop_ifnonnull(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	LOG("ifnonnull - ");

	JavaObject* ref = pop();
	if (ref != 0) pc = start + offset;

	return pc;
}

uint8* Frame::jop_ifeq(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);
	jint value = pop();

	LOG("ifeq - %d == 0", value);

	if (value == 0) pc = start + offset;

	return pc;
}

uint8* Frame::jop_ifne(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);
	jint value = pop();

	LOG("ifne - %d != 0", value);

	if (value != 0) pc = start + offset;

	return pc;
}

uint8* Frame::jop_iflt(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	LOG("iflt - ");

	jint value = pop();
	if (value < 0) pc = start + offset;

	return pc;
}

uint8* Frame::jop_ifge(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	LOG("ifge - ");

	jint value = pop();
	if (value >= 0) pc = start + offset;

	return pc;
}

uint8* Frame::jop_ifgt(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	LOG("ifgt - ");

	jint value = pop();
	if (value > 0) pc = start + offset;

	return pc;
}

uint8* Frame::jop_ifle(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);

	LOG("ifle - ");

	jint value = pop();
	if (value <= 0) pc = start + offset;

	return pc;
}

uint8* Frame::jop_lconst_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("lconst_0");
	push((jlong)0);
	return pc;
}

uint8* Frame::jop_lconst_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("lconst - ");
	push((jlong)1);
	return pc;
}

uint8* Frame::jop_aconst_null(Thread* c, uint8* pc)
{
	pc++;
	LOG("aconst null - ");
	push(ObjectRef(NULL));
	return pc;
}

uint8* Frame::jop_fconst_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("fconst 0 - ");
	push((float)0);
	return pc;
}

uint8* Frame::jop_fconst_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("fconst 1 - ");
	push((float)1);
	return pc;
}

uint8* Frame::jop_fconst_2(Thread* c, uint8* pc)
{
	pc++;
	LOG("fconst 2 - ");
	push((float)2);
	return pc;
}

uint8* Frame::jop_dconst_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("dconst 0 - ");
	push((double)0);
	return pc;
}

uint8* Frame::jop_dconst_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("dconst 1 - ");
	push((double)1);
	return pc;
}

uint8* Frame::jop_iconst_m1(Thread* c, uint8* pc)	// minus 1
{
	pc++;
	LOG("iconst m1 - ");
	push(-1L);
	return pc;
}

uint8* Frame::jop_iconst_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("iconst 0 - ");
	push(0L);
	return pc;
}

uint8* Frame::jop_iconst_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("iconst 1 - ");
	push(1L);
	return pc;
}

uint8* Frame::jop_iconst_2(Thread* c, uint8* pc)
{
	pc++;
	LOG("iconst 2 - ");
	push(2L);
	return pc;
}

uint8* Frame::jop_iconst_3(Thread* c, uint8* pc)
{
	pc++;
	LOG("iconst 3 - ");
	push(3L);
	return pc;
}

uint8* Frame::jop_iconst_4(Thread* c, uint8* pc)
{
	pc++;
	LOG("iconst 4 - ");
	push(4L);
	return pc;
}

uint8* Frame::jop_iconst_5(Thread* c, uint8* pc)
{
	pc++;
	LOG("iconst 5 - ");
	push(5L);
	return pc;
}

uint8* Frame::jop_astore(Thread* c, uint8* pc)
{
	pc++;
	uint8 index = *pc++;
	LOG("astore %d - ", index);
	astore(index);
	return pc;
}

uint8* Frame::jop_astore_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("astore 0 - ");
	astore(0);
	return pc;
}

uint8* Frame::jop_astore_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("astore 1 - ");
	astore(1);
	return pc;
}

uint8* Frame::jop_astore_2(Thread* c, uint8* pc)
{
	pc++;
	LOG("astore 2 - ");
	astore(2);
	return pc;
}

uint8* Frame::jop_astore_3(Thread* c, uint8* pc)
{
	pc++;
	LOG("astore 3 - ");
	astore(3);
	return pc;
}

uint8* Frame::jop_istore(Thread* c, uint8* pc)
{
	pc++;
	uint8 index = *pc++;
	m_localVariables[index] = pop();
	LOG("istore %d - %d", index, m_localVariables[index]);
	return pc;
}

uint8* Frame::jop_istore_0(Thread* c, uint8* pc)
{
	pc++;
	m_localVariables[0] = pop();
	LOG("istore 0 - %d", m_localVariables[0]);
	return pc;
}

uint8* Frame::jop_istore_1(Thread* c, uint8* pc)
{
	pc++;
	m_localVariables[1] = pop();
	LOG("istore 1 - %d", m_localVariables[0]);
	return pc;
}

uint8* Frame::jop_istore_2(Thread* c, uint8* pc)
{
	pc++;
	m_localVariables[2] = pop();
	LOG("istore 2 - %d", m_localVariables[0]);
	return pc;
}

uint8* Frame::jop_istore_3(Thread* c, uint8* pc)
{
	pc++;
	m_localVariables[3] = pop();
	LOG("istore 3 - %d", m_localVariables[0]);
	return pc;
}

uint8* Frame::jop_lstore(Thread* c, uint8* pc)
{
	pc++;
	uint8 index = *pc++;

	Operand op = pop();
	ASSERT(op.kind == (1 | 16));
	m_localVariables[index] = op.u._long & 0xFFFFFFFF;
	m_localVariables[index+1] = op.u._long >> 32;
	LOG("lstore - %lld", m_localVariables[index], m_localVariables[index+1]);
	return pc;
}

uint8* Frame::jop_lstore_0(Thread* c, uint8* pc)
{
	pc++;
	Operand op = pop();
	ASSERT(op.kind == (1 | 16));
	m_localVariables[0] = op.u._long & 0xFFFFFFFF;
	m_localVariables[1] = op.u._long >> 32;
	LOG("lstore 2 - %d.%d", m_localVariables[0], m_localVariables[1]);
	return pc;
}

uint8* Frame::jop_lstore_1(Thread* c, uint8* pc)
{
	pc++;
	Operand op = pop();
	ASSERT(op.kind == (1 | 16));
	m_localVariables[1] = op.u._long & 0xFFFFFFFF;
	m_localVariables[2] = op.u._long >> 32;
	LOG("lstore 2 - %d.%d", m_localVariables[1], m_localVariables[2]);
	return pc;
}

uint8* Frame::jop_lstore_2(Thread* c, uint8* pc)
{
	pc++;
	Operand op = pop();
	ASSERT(op.kind == (1 | 16));
	m_localVariables[2] = op.u._long & 0xFFFFFFFF;
	m_localVariables[3] = op.u._long >> 32;
	LOG("lstore 2 - %d.%d", m_localVariables[2], m_localVariables[3]);
	return pc;
}

uint8* Frame::jop_lstore_3(Thread* c, uint8* pc)
{
	pc++;
	Operand op = pop();
	ASSERT(op.kind == (1 | 16));
	m_localVariables[3] = op.u._long & 0xFFFFFFFF;
	m_localVariables[4] = op.u._long >> 32;
	LOG("lstore 2 - %d.%d", m_localVariables[3], m_localVariables[4]);
	return pc;
}

uint8* Frame::jop_pop(Thread* c, uint8* pc)
{
	pc++;

	LOG("pop - ");
	pop();

	return pc;
}

uint8* Frame::jop_pop2(Thread* c, uint8* pc)
{
	pc++;

	LOG("pop2 - ");
	Operand value = pop();
	if (!(value.kind & 16))
	{
		value = pop();
		ASSERT(!(value.kind & 16));
	}

	return pc;
}

uint8* Frame::jop_dup(Thread* c, uint8* pc)
{
	pc++;

	LOG("dup - ");
	Operand value = pop();
	ASSERT(!(value.kind & 16));

	push(value);
	push(value);

	return pc;
}

uint8* Frame::jop_dup2(Thread* c, uint8* pc)
{
	pc++;

	LOG("dup2 - ");
	Operand value2 = pop();
	if (value2.kind & 16)	// long or double
	{
		push(value2);
		push(value2);
	}
	else
	{
		Operand value1 = pop();
		push(value2);
		push(value1);
		push(value2);
		push(value1);
	}

	return pc;
}

uint8* Frame::jop_dup_x1(Thread* c, uint8* pc)
{
	pc++;

	LOG("dup_x1 - ");

	ASSERT(m_operands.GetSize() >= 2);
	Operand value = m_operands[m_operands.GetSize()-1];
	m_operands.InsertAt(m_operands.GetSize()-2, value);

	return pc;
}

uint8* Frame::jop_dup_x2(Thread* c, uint8* pc)
{
	pc++;

	LOG("dup_x2 - ");
	ASSERT(m_operands.GetSize() >= 3);
	Operand value = m_operands[m_operands.GetSize()-1];
//	Operand value = m_operands.back();
	m_operands.InsertAt(m_operands.GetSize()-3, value);

	return pc;
}

uint8* Frame::jop_return(Thread* c, uint8* pc)
{
	Frame* pFrame = c->m_pFrame;
	pc = c->m_pFrame->m_returnAddress;
	c->m_pFrame = pFrame->m_pCaller;
	delete pFrame;

	LOG("return }");

	return pc;
	//return c->m_pFrame == NULL;	// 0=continue, 1=stop
}

uint8* Frame::jop_ireturn(Thread* c, uint8* pc)
{
	jint i = pop();
	m_pCaller->push(i);
	pc = c->m_pFrame->m_returnAddress;
	c->m_pFrame = m_pCaller;
	delete this;
	LOG("ireturn %d }", i);

	return pc;
	//return c->m_pFrame == NULL;	// 0=continue, 1=stop
}

uint8* Frame::jop_lreturn(Thread* c, uint8* pc)
{
	int64 value = pop();
	m_pCaller->push(value);
	pc = c->m_pFrame->m_returnAddress;
	c->m_pFrame = m_pCaller;
	delete this;
	LOG("lreturn }"/*, i*/);

	return pc;
	//return c->m_pFrame == NULL;	// 0=continue, 1=stop
}

uint8* Frame::jop_freturn(Thread* c, uint8* pc)
{
	float retval = pop();
	m_pCaller->push(retval);
	pc = c->m_pFrame->m_returnAddress;
	c->m_pFrame = m_pCaller;
	delete this;
	LOG("freturn %f }", retval);

	return pc;
	//return c->m_pFrame == NULL;	// 0=continue, 1=stop
}

uint8* Frame::jop_areturn(Thread* c, uint8* pc)
{
	ObjectRef ref = pop();
	LOG("areturn ");
	TraceObject(ref);

	m_pCaller->push(ref);
	Frame* pFrame = c->m_pFrame;
	pc = c->m_pFrame->m_returnAddress;
	c->m_pFrame = c->m_pFrame->m_pCaller;
	delete pFrame;

	LOG("}");

	return pc;
	//return c->m_pFrame == NULL;	// 0=continue, 1=stop
}

uint8* Frame::jop_goto(Thread* c, uint8* pc)
{
	LOG("goto");
	uint8* start = pc++;
	short offset = getword(pc);
	pc = start + offset;
	return pc;
}

// Convert float to double
uint8* Frame::jop_f2d(Thread* c, uint8* pc)
{
	pc++;
	LOG("f2d");
	float f = pop();
	push((double)f);

	return pc;
}

// Convert int to char
uint8* Frame::jop_i2c(Thread* c, uint8* pc)
{
	pc++;
	LOG("i2c");
	jint i = pop();
	uint16 ch = i;
	push((jint)ch);

	return pc;
}

// Convert int to byte
uint8* Frame::jop_i2b(Thread* c, uint8* pc)
{
	pc++;
	LOG("i2b");
	jint i = pop();
	int8 b = i;
	push((jint)b);

	return pc;
}

// Convert int to long
uint8* Frame::jop_i2l(Thread* c, uint8* pc)
{
	pc++;
	LOG("i2l");
	jint i = pop();
	push((jlong)i);

	return pc;
}

// Convert int to float
uint8* Frame::jop_i2f(Thread* c, uint8* pc)
{
	pc++;
	LOG("i2f");
	jint i = pop();
	push((float)i);

	return pc;
}

// Convert float to int
uint8* Frame::jop_f2i(Thread* c, uint8* pc)
{
	pc++;
	LOG("f2i");
	float f = pop();
	push((jint)f);

	return pc;
}

uint8* Frame::jop_fload_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("fload 0 - ");
	push(*(float*)&m_localVariables[0]);
	return pc;
}

uint8* Frame::jop_fload_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("fload 1 - ");
	push(*(float*)&m_localVariables[1]);
	return pc;
}

uint8* Frame::jop_fload_2(Thread* c, uint8* pc)
{
	pc++;
	LOG("fload 2 - ");
	push(*(float*)&m_localVariables[2]);
	return pc;
}

uint8* Frame::jop_fload_3(Thread* c, uint8* pc)
{
	pc++;
	LOG("fload 3 - ");
	push(*(float*)&m_localVariables[3]);
	return pc;
}

uint8* Frame::jop_aload(Thread* c, uint8* pc)
{
	pc++;
	uint8 index = *pc++;
	LOG("aload %d - ", index);

	ObjectRef ref = m_localVariables[index];

	TraceObject(ref);

	push(ref);
	return pc;
}

uint8* Frame::jop_aload_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("aload 0 - ");

	ObjectRef ref = m_localVariables[0];
	TraceObject(ref);
	push(ref);

	return pc;
}

uint8* Frame::jop_aload_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("aload 1 - ");

	ObjectRef ref = m_localVariables[1];
	TraceObject(ref);
	push(ref);

	return pc;
}

uint8* Frame::jop_aload_2(Thread* c, uint8* pc)
{
	pc++;
	LOG("aload 2 - ");

	ObjectRef ref = m_localVariables[2];
	TraceObject(ref);
	push(ref);

	return pc;
}

uint8* Frame::jop_aload_3(Thread* c, uint8* pc)
{
	pc++;
	LOG("aload 3 - ");

	ObjectRef ref = m_localVariables[3];
	TraceObject(ref);
	push(ref);

	return pc;
}

uint8* Frame::jop_iload(Thread* c, uint8* pc)
{
	pc++;
	uint8 index = *pc++;
	LOG("iload %d - ", index);
	push((jint)m_localVariables[index]);
	return pc;
}

uint8* Frame::jop_lload(Thread* c, uint8* pc)
{
	pc++;
	uint8 index = *pc++;
	LOG("lload %d - ", index);

	uint32 l = m_localVariables[index];
	uint32 h = m_localVariables[index+1];

	push((jlong)(l | (LONGLONG)h<<32));

	return pc;
}

uint8* Frame::jop_iload_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("iload 0 - ");
	push((jint)m_localVariables[0]);
	return pc;
}

uint8* Frame::jop_iload_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("iload 1 - ");
	push((jint)m_localVariables[1]);
	return pc;
}

uint8* Frame::jop_iload_2(Thread* c, uint8* pc)
{
	pc++;
	LOG("iload 2 - ");
	push((jint)m_localVariables[2]);
	return pc;
}

uint8* Frame::jop_iload_3(Thread* c, uint8* pc)
{
	pc++;
	LOG("iload 3 - ");
	push((jint)m_localVariables[3]);
	return pc;
}

uint8* Frame::jop_lload_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("lload 0 - ");
	int64 v = m_localVariables[0] | (int64)m_localVariables[1]<<32;
	push(v);
	return pc;
}

uint8* Frame::jop_lload_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("lload 1 - ");
	int64 v = m_localVariables[1] | (int64)m_localVariables[2]<<32;
	push(v);
	return pc;
}

uint8* Frame::jop_lload_2(Thread* c, uint8* pc)
{
	pc++;
	LOG("lload 2 - ");
	int64 v = m_localVariables[2] | (int64)m_localVariables[3]<<32;
	push(v);
	return pc;
}

uint8* Frame::jop_lload_3(Thread* c, uint8* pc)
{
	pc++;
	LOG("lload 3 - ");
	int64 v = m_localVariables[3] | (int64)m_localVariables[4]<<32;
	push(v);
	return pc;
}

uint8* Frame::jop_dload_0(Thread* c, uint8* pc)
{
	pc++;
	LOG("dload_0 -");
	int64 v = m_localVariables[0] | (int64)m_localVariables[1]<<32;
	push(*(double*)&v);

	return pc;
}

uint8* Frame::jop_dload_1(Thread* c, uint8* pc)
{
	pc++;
	LOG("dload_1 -");
	int64 v = m_localVariables[1] | (int64)m_localVariables[2]<<32;
	push(*(double*)&v);

	return pc;
}

uint8* Frame::jop_dload_2(Thread* c, uint8* pc)
{
	pc++;
	LOG("dload_2 -");
	int64 v = m_localVariables[2] | (int64)m_localVariables[3]<<32;
	push(*(double*)&v);

	return pc;
}

uint8* Frame::jop_dload_3(Thread* c, uint8* pc)
{
	pc++;
	LOG("dload_3 -");
	int64 v = m_localVariables[3] | (int64)m_localVariables[4]<<32;
	push(*(double*)&v);

	return pc;
}

// Load char from array
uint8* Frame::jop_caload(Thread* c, uint8* pc)
{
	pc++;
	LOG("caload - ");

	jint index = pop();
	ArrayRef* ref = pop();

	if (ref == NULL)
		THROW(-1);	//  NullPointerException

	if (index < 0 || index >= GetArrayLength(ref))
		THROW(-1);	// ArrayIndexOutOfBoundsException

	push((jint)((jchar*)GetArrayData(ref))[index]);
	return pc;
}

// Load int from array
uint8* Frame::jop_iaload(Thread* c, uint8* pc)
{
	pc++;
	LOG("iaload - ");

	jint index = pop();
	ArrayRef* ref = pop();

	if (ref == NULL)
		THROW(-1);	//  NullPointerException

	if (index < 0 || index >= GetArrayLength(ref))
		THROW(-1);	// ArrayIndexOutOfBoundsException

	push(((jint*)GetArrayData(ref))[index]);
	return pc;
}

// Load reference from array
uint8* Frame::jop_aaload(Thread* c, uint8* pc)
{
	pc++;
	LOG("aaload - ");

	jint index = pop();
	ObjectRef arrayref = pop();

	if (arrayref == NULL)
		THROW(-1);	//  NullPointerException

	if (index < 0 || index >= GetArrayLength(arrayref))
		THROW(-1);	// ArrayIndexOutOfBoundsException

	ObjectRef item(((JavaObject**)GetArrayData(arrayref))[index]);
	TraceObject(item);

	push(item);
	return pc;
}

// Load byte or boolean from array
uint8* Frame::jop_baload(Thread* c, uint8* pc)
{
	pc++;
	LOG("baload - ");

	jint index = pop();
	ObjectRef arrayref = pop();

	if (arrayref == NULL)
		THROW(-1);	//  NullPointerException

	if (index < 0 || index >= GetArrayLength(arrayref))
		THROW(-1);	// ArrayIndexOutOfBoundsException

	int8 value = ((int8*)GetArrayData(arrayref))[index];

	push((jint)value);

	return pc;
}

// Store into char array
uint8* Frame::jop_castore(Thread* c, uint8* pc)
{
	pc++;

	LOG("castore");

	jchar value = (jint)pop();
	jint index = pop();
	ArrayRef* arrayref = pop();

	if (arrayref == NULL)
		THROW(-1);	//  NullPointerException

	if (index < 0 || index >= GetArrayLength(arrayref))
		THROW(-1);	// ArrayIndexOutOfBoundsException

	// TODO, check type etc

	((jchar*)GetArrayData(arrayref))[index] = value;

	return pc;
}

// Store into int array
uint8* Frame::jop_iastore(Thread* c, uint8* pc)
{
	pc++;

	LOG("iastore");

	jint value = pop();
	jint index = pop();
	ArrayRef* ref = pop();

	if (ref == NULL)
		THROW(-1);	//  NullPointerException

	if (index < 0 || index >= GetArrayLength(ref))
		THROW(-1);	// ArrayIndexOutOfBoundsException

	// TODO, check type etc

	((jint*)GetArrayData(ref))[index] = value;

	return pc;
}

// Store into byte or boolean array
uint8* Frame::jop_bastore(Thread* c, uint8* pc)
{
	pc++;

	jint value = pop();
	jint index = pop();
	ArrayRef* ref = pop();

	if (ref == NULL)
		THROW(-1);	//  NullPointerException

	if (index < 0 || index >= GetArrayLength(ref))
		THROW(-1);	// ArrayIndexOutOfBoundsException

	VERIFY(GetArrayComponentType(ref)->m_baseTypeSize == 1);

	((uint8*)GetArrayData(ref))[index] = value;

	return pc;
}

// Store into reference array
uint8* Frame::jop_aastore(Thread* c, uint8* pc)
{
	pc++;

	JavaObject* value = pop();
	jint index = pop();
	ArrayRef* ref = pop();

	LOG("aastore");

	if (ref == NULL)
		THROW(-1);	//  NullPointerException

	if (index < 0 || index >= GetArrayLength(ref))
		THROW(-1);	// ArrayIndexOutOfBoundsException

	// TODO, check type etc

	((JavaObject**)GetArrayData(ref))[index] = value;

	return pc;
}

String JavaMethod::GetDescriptor()
{
	return m_pOwnerClass->m_pool_array[m_descriptor_index-1].utf8.str;
}

JavaMethod* Frame::GetMethod(Thread* c, uint16 methodIndex)
{
	uint16 classIndex = m_pMethod->m_pOwnerClass->m_pool_array[methodIndex-1].methodRef.class_index;

	uint16 nameAndTypeIndex = m_pMethod->m_pOwnerClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
	uint16 methodNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	uint16 descriptorIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.descriptor_index;
	String methodName = m_pMethod->m_pOwnerClass->m_pool_array[methodNameIndex-1].utf8.str;
	String descriptor = m_pMethod->m_pOwnerClass->m_pool_array[descriptorIndex-1].utf8.str;

	char fullName[512];
	sprintf_s(fullName, "%s%s", CString(methodName).c_str(), CString(descriptor).c_str());

	if (m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass == NULL)
	{
		uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
		StringA* className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;
		m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass = c->LoadClass(className);
	}
	JavaClass* pJavaClass = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass;
	VERIFY(pJavaClass);

	JavaMethod* pMethod = pJavaClass->GetMethodByName(fullName);

	return pMethod;
}

typedef int (*nativefunc)();

uint8* Frame::jop_invokevirtual(Thread* c, uint8* pc)
{
	pc++;
	uint16 methodIndex = getword(pc);

	uint16 classIndex = m_pMethod->m_pOwnerClass->m_pool_array[methodIndex-1].methodRef.class_index;
//	StringA* className = m_pMethod->m_pClass->m_pool_array[classNameIndex-1].str;

	uint16 nameAndTypeIndex = m_pMethod->m_pOwnerClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
	uint16 methodNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	uint16 descriptorIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.descriptor_index;
	String methodName = m_pMethod->m_pOwnerClass->m_pool_array[methodNameIndex-1].utf8.str;
	String descriptor = m_pMethod->m_pOwnerClass->m_pool_array[descriptorIndex-1].utf8.str;

//	StringA* fullName = *methodName + *descriptor;

	if (m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass == NULL)
	{
		uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
		String className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;
		m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass = c->LoadClass(className);
	}
	JavaClass* pJavaClass = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass;
	VERIFY(pJavaClass);

//	JavaClass* pJavaClass = c->LoadClass(className);

	char fullName[512];
	sprintf_s(fullName, "%s%s", CString(methodName).c_str(), CString(descriptor).c_str());

	LOG("invokevirtual %s", fullName);

	JavaMethod* pMethod = pJavaClass->GetMethodByName(fullName);

	vector<Operand> args;
	args.reserve(pMethod->m_argumentTypes.GetSize()+1);

	int i;
	for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
	{
		args.Add(pop());
	}

	ObjectRef objectRef = pop();
	args.Add(objectRef);

	if (objectRef == NULL)
	{
		c->m_vm->Breakpoint(c, 3);
		ASSERT(0);
		THROW(-1);
	}

	// Find the virtual method on the actual object
	JavaClass* pClass = objectRef->m_pClass;
	pMethod = pClass->GetMethodByName(fullName);
		/*
	do
	{
		pMethod  = pClass->GetMethodByName(fullName);
		if (pMethod) break;
		pClass = pClass->GetSuperClass();
	}
	while (pClass);
	*/

	ASSERT(pMethod);

//	LOG("invokevirtual %s.%s", pMethod->m_pClass->GetName().c_str(), pMethod->GetName().c_str());
	LOG("resolved %s.%s", CString(pMethod->m_pOwnerClass->GetName()).c_str(), CString(pMethod->GetName()).c_str());

	if (pMethod->m_access_flags & ACC_NATIVE)
	{
		char buffer2[1024];
		sprintf_s(buffer2, "%s%s", /*pMethod->m_pClass->GetName()->c_str(),*/ CString(pMethod->GetName()).c_str(), CString(pMethod->GetSignature()).c_str());

	//	StringA* fullName = *(*pMethod->m_pClass->GetName() + *pMethod->GetName()) + *pMethod->GetSignature();
	//	LOG(" native");

		if (!strcmp(buffer2, "putLong(JJ)V"))
		{
			MessageBeep(-1);
		}

		nativefunc pfunc = (nativefunc)pMethod->m_nativeFunc;//m_pClass->m_nativeFuncs[buffer2];
	//	nativefunc pfunc = (nativefunc)c->m_vm->m_nativeFuncs[fullName];
		if (pfunc == NULL)
		{
			LOG("Native function not registered");
			THROW(-1);
		}

		LOG(" {");

		const Operand* _args = args.GetData();

		int nargs = pMethod->m_argumentTypes.GetSize();
		Type** types = pMethod->m_argumentTypes.GetData()+nargs;

		for (i = 0; i < nargs; i++)
		{
			Type* type = *(--types);

			if (type->kind == Type::BaseType_double || type->kind == Type::BaseType_long)
			{
				int64 longlong = _args->u._long;
				uint32 l = (uint32)longlong;
				uint32 h = longlong>>32;
				__asm {
					push h
					push l
				}
			}
			else if (type->kind == Type::Type_ref || type->kind == Type::Type_array)
			{
				JavaObject* object = _args->ref.m_object;
			//	int id = _args->ref.m_id;

				__asm {
			//		push id
					push object
				}
			}
			else
			{
				jint i = _args->u._int;
				__asm {
					push i
				}
			}

			++ _args;
		}

		{
			JavaObject* ref = _args->ref.m_object;
		//	int id = _args->ref.m_id;
			__asm {
		//		push id
				push ref
			}
		}

		{
			JNIEnv* jni = c->m_jni;
			__asm {
				push jni
			}
		}

		int ret_eax;
		int ret_edx;
		ObjectRef objresult;
		ObjectRef* pobjresult = &objresult;

		if (pMethod->m_pReturnType->kind == Type::Type_ref || pMethod->m_pReturnType->kind == Type::Type_array)
		{
			__asm
			{
				push pobjresult;
			}
		}

		__asm {
			call pfunc;
			mov ret_eax,eax
			mov ret_edx,edx
		}

		if (pMethod->m_pReturnType->kind != Type::ReturnType_void)
		{
			switch (pMethod->m_pReturnType->kind)
			{
			case Type::BaseType_long:
				{
					push((jlong)((LONGLONG)ret_eax | ((LONGLONG)ret_edx<<32)));
				}
				break;
				
			case Type::BaseType_int:
				{
					push((jint)ret_eax);
				}
				break;
				
			case Type::BaseType_byte:
				{
					push((jint)(int8)(ret_eax & 0xFF));
				}
				break;
				
			case Type::BaseType_short:
				{
					push((jint)(int16)(ret_eax & 0xFFFF));
				}
				break;
				
			case Type::BaseType_bool:
				{
					push((jint)(ret_eax & 1));
				}
				break;
				
			case Type::Type_ref:
				{
					push(objresult);
					
					//	push(ObjectRef((JavaObject*)ret_eax));
				}
				break;

			default:
				ASSERT(0);
			}
		}

		LOG("}");
	}
	else
	{
		CodeAttribute* pCode = pMethod->GetCode();

		Frame* pFrame = new Frame(pMethod, pCode, this, pc);
		//pFrame->m_pCaller = this;
		c->m_pFrame = pFrame;
		pc = pCode->code;

		/*
		std::stack<Operand> args;
		int i;
		for (i = 0; i < pMethod->m_argumentTypes.size(); i++)
		{
			args.push(pop()); 
		}
		args.push(pop());	// objectref
		*/

		int j = args.GetSize();
		pFrame->m_localVariables[0] = args[--j];	// objectref

//		LOG(", 0x%X, ", pFrame->m_localVariables[0]);
		LOG("(");

		int n = 1;
		for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
		{
			if (i > 0) LOG(", ");

			Type* type = pMethod->m_argumentTypes[i];

			switch (type->kind)
			{
			case Type::BaseType_bool:
			{
				jint value = args[--j];
				LOG("%d", value);

				pFrame->m_localVariables[n] = value;
				n++;
			}
			break;

			case Type::BaseType_wchar:
			{
				uint16 value = (jint)args[--j];
				LOG("%d", value);

				pFrame->m_localVariables[n] = (jint)value;
				n++;
			}
			break;

			case Type::BaseType_byte:
			{
				int8 value = args[--j];
				LOG("%d", value);

				pFrame->m_localVariables[n] = value;
				n++;
			}
			break;

			case Type::BaseType_short:
			{
				jint value = args[--j];
				LOG("%d", value);

				pFrame->m_localVariables[n] = value;
				n++;
			}
			break;

			case Type::BaseType_int:
			{
				jint value = args[--j];
				LOG("%d", value);

				pFrame->m_localVariables[n] = value;
				n++;
			}
			break;

			case Type::BaseType_double:
			case Type::BaseType_long:
			{
				ASSERT(0);
				/*
				pFrame->m_localVariables[n] = pop();
				pFrame->m_localVariables[n+1] = pop();
				n += 2;
				*/
			}
			break;

			case Type::Type_ref:
			case Type::Type_array:
			{
				ObjectRef ref = args[--j];
				/*
				if (ref->m_pClass && *ref->m_pClass->GetName() == "java/lang/String")
				{
					JavaField* pField = ref->m_pClass->GetFieldByName(&StringA(true, "value"));
					JavaObject* pValue = *(JavaObject**)(ref->m_data + pField->m_offset);
					LOG("\"%*.*S\"", GetpValue->m_count, pValue->m_count, pValue->m_data);
				}
				*/
				TraceObject(ref);

				pFrame->m_localVariables[n] = ref;
				n++;
			}
			break;

			/*
			else if (type->kind == Type::Type_array)
			{
				ObjectRef ref = args[--j];
				pFrame->m_localVariables[n] = ref;
				n++;
			}
			*/
			default:
				ASSERT(0);
			}
		}

		LOG(") {");
	}
	return pc;
}

uint8* Frame::jop_invokeinterface(Thread* c, uint8* pc)
{
	pc++;
	uint16 methodIndex = getword(pc);
	uint8 count = *pc++;
	uint8 zero = *pc++;

	uint16 classIndex = m_pMethod->m_pOwnerClass->m_pool_array[methodIndex-1].methodRef.class_index;

	if (m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass == NULL)
	{
		uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
		String className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;
		m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass = c->LoadClass(className);
	}
	JavaClass* pJavaClass = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass;

	uint16 nameAndTypeIndex = m_pMethod->m_pOwnerClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
	uint16 methodNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	uint16 descriptorIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.descriptor_index;
	StringA* methodName = m_pMethod->m_pOwnerClass->m_pool_array[methodNameIndex-1].utf8.str;
	StringA* descriptor = m_pMethod->m_pOwnerClass->m_pool_array[descriptorIndex-1].utf8.str;

	//	StringA* fullName = *methodName + *descriptor;
	char fullName[512];
	sprintf_s(fullName, "%s%s", CString(methodName).c_str(), CString(descriptor).c_str());

	LOG("invokeinterface %s {", fullName);

	JavaMethod* pMethod = pJavaClass->GetMethodByName(fullName);

	vector<Operand> args;
	int i;
	for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
	{
		args.Add(pop());
	}
	ObjectRef objectRef = pop();
	args.push_back(Operand(objectRef));

	if (objectRef == NULL)
	{
		ASSERT(0);
		THROW(-1);
	}

	JavaClass* pClass = objectRef->m_pClass;
	pMethod  = pClass->GetMethodByName(fullName);
	/*
	do
	{
		pMethod  = pClass->GetMethodByName(fullName);
		if (pMethod) break;
		pClass = pClass->GetSuperClass();
	}
	while (pClass);
	*/

	ASSERT(pMethod);

//	LOG("invokevirtual %s.%s", pMethod->m_pClass->GetName().c_str(), pMethod->GetName().c_str());
	LOG("resolved %s.%s", CString(pMethod->m_pOwnerClass->GetName()).c_str(), CString(pMethod->GetName()).c_str());

	if (pMethod->m_access_flags & ACC_NATIVE)
	{
	//	StringA* fullName = *(*pMethod->m_pClass->GetName() + *pMethod->GetName()) + *pMethod->GetSignature();
		char buffer2[1024];
		sprintf_s(buffer2, "%s%s", /*pMethod->m_pClass->GetName()->c_str(),*/ CString(pMethod->GetName()).c_str(), CString(pMethod->GetSignature()).c_str());

		LOG(" native");

		nativefunc pfunc = (nativefunc)pMethod->m_nativeFunc;//m_pClass->m_nativeFuncs[buffer2];
	//	nativefunc pfunc = (nativefunc)c->m_vm->m_nativeFuncs[fullName];
		if (pfunc == NULL)
		{
			LOG("Native function not registered");
			THROW(-1);
		}

		const Operand* _args = args.GetData();

		int nargs = pMethod->m_argumentTypes.GetSize();
		Type** types = pMethod->m_argumentTypes.GetData()+nargs;

		for (i = 0; i < nargs; i++)
		{
			Type* type = *(--types);

			if (type->kind == Type::BaseType_double || type->kind == Type::BaseType_long)
			{
				ASSERT(0);
				/*
				pFrame->m_localVariables[n] = pop();
				pFrame->m_localVariables[n+1] = pop();
				n += 2;
				*/
			}
			else if (type->kind == Type::Type_ref || type->kind == Type::Type_array)
			{
				JavaObject* ref = _args->ref.m_object;
			//	int id = _args->ref.m_id;
				__asm {
			//		push id
					push ref
				}
			}
			else
			{
				jint i = _args->u._int;
				__asm {
					push i
				}
			}

			_args++;
		}

		{
			JavaObject* ref = _args->ref.m_object;
		//	int id = _args->ref.m_id;
			__asm {
		//		push id
				push ref
			}
		}

		{
			JNIEnv* jni = c->m_jni;
			__asm {
				push jni
			}
		}

		int ret_eax;
		int ret_edx;

		__asm {
			call pfunc;
			mov ret_eax,eax
			mov ret_edx,edx
		}

		if (pMethod->m_pReturnType->kind != Type::ReturnType_void)
		{
			if (pMethod->m_pReturnType->kind == Type::BaseType_long)
			{
				push((jlong)((LONGLONG)ret_eax | ((LONGLONG)ret_edx<<32)));
			}
			else if (pMethod->m_pReturnType->kind == Type::BaseType_int)
			{
				push((jint)ret_eax);
			}
			else if (pMethod->m_pReturnType->kind == Type::BaseType_short)
			{
				push((jint)(ret_eax & 0xFFFF));
			}
			else if (pMethod->m_pReturnType->kind == Type::BaseType_bool)
			{
				push((jint)(ret_eax & 1));
			}
			else if (pMethod->m_pReturnType->kind == Type::Type_ref)
			{
				ASSERT(0);
				push(ObjectRef((JavaObject*)ret_eax));
			}
			else
				ASSERT(0);
		}
	}
	else
	{
		CodeAttribute* pCode = pMethod->GetCode();

		Frame* pFrame = new Frame(pMethod, pCode, this, pc);
	//	pFrame->m_pCaller = this;
		c->m_pFrame = pFrame;
		pc = pCode->code;

		/*
		std::stack<Operand> args;
		int i;
		for (i = 0; i < pMethod->m_argumentTypes.size(); i++)
		{
			args.push(pop()); 
		}
		args.push(pop());	// objectref
		*/

		int j = args.GetSize()-1;
		pFrame->m_localVariables[0] = args[j--];	// objectref

//		LOG(", 0x%X, ", pFrame->m_localVariables[0]);
		LOG("(");

		int n = 1;
		for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++, j--)
		{
			if (i > 0) LOG(", ");

			Type* type = pMethod->m_argumentTypes[i];

			if (type->kind == Type::BaseType_bool)
			{
				jint value = args[j];
				LOG("%d", value);

				pFrame->m_localVariables[n] = value;
				n++;
			}
			else if (type->kind == Type::BaseType_short)
			{
				jint value = args[j];
				LOG("%d", value);

				pFrame->m_localVariables[n] = value;
				n++;
			}
			else if (type->kind == Type::BaseType_int)
			{
				jint value = args[j];
				LOG("%d", value);

				pFrame->m_localVariables[n] = value;
				n++;
			}
			else if (type->kind == Type::BaseType_double || type->kind == Type::BaseType_long)
			{
				ASSERT(0);
				/*
				pFrame->m_localVariables[n] = pop();
				pFrame->m_localVariables[n+1] = pop();
				n += 2;
				*/
			}
			else if (type->kind == Type::Type_ref)
			{
				ObjectRef ref = args[j];
				TraceObject(ref);

				pFrame->m_localVariables[n] = ref;
				n++;
			}
			else if (type->kind == Type::Type_array)
			{
				ObjectRef ref = args[j];
				pFrame->m_localVariables[n] = ref;
				n++;
			}
			else
				ASSERT(0);
		}

		LOG(")");
	}
	return pc;
}

uint8* Frame::jop_invokespecial(Thread* c, uint8* pc)
{
	pc++;
	uint16 methodIndex = getword(pc);

	JavaMethod* pMethod = GetMethod(c, methodIndex);

	String name = pMethod->GetName();
	String descriptor = pMethod->GetDescriptor();

//	sysstring name = pMethod->GetName();
	LOG("invokespecial %s.%s ", CString(pMethod->m_pOwnerClass->GetName()).c_str(), CString(pMethod->GetName()).c_str());

	stack<Operand> args;
	int i;
	for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
	{
		args.push(pop()); 
	}
	ObjectRef objectRef = pop();
	args.push(objectRef);	// objectref

	if (objectRef == NULL)
	{
		ASSERT(0);
		THROW(-1);
	}

	/*
	if (false)
	{
		// Find the virtual method on the actual object
		JavaClass* pClass = objectRef->m_pClass;
	//	pMethod  = pClass->GetMethodByName(&StringA(true, fullName));
	}
	*/

	if (pMethod->m_access_flags & ACC_NATIVE)
	{
		LOG(" native");

		nativefunc pfunc = (nativefunc)pMethod->m_nativeFunc;//m_pClass->m_nativeFuncs[buffer2];
		if (pfunc == NULL)
		{
			LOG("Native function not registered");
			THROW(-1);
		}

		const Operand* _args = args.cont.GetData();

		int nargs = pMethod->m_argumentTypes.GetSize();
		Type** types = pMethod->m_argumentTypes.GetData()+nargs;

		for (i = 0; i < nargs; i++)
		{
			Type* type = *(--types);

			if (type->kind == Type::BaseType_double || type->kind == Type::BaseType_long)
			{
				ASSERT(0);
				/*
				pFrame->m_localVariables[n] = pop();
				pFrame->m_localVariables[n+1] = pop();
				n += 2;
				*/
			}
			else if (type->kind == Type::Type_ref || type->kind == Type::Type_array)
			{
				JavaObject* object = _args->ref.m_object;
			//	int id = _args->ref.m_id;

				__asm {
				//	push id
					push object
				}
			}
			else
			{
				jint i = _args->u._int;
				__asm {
					push i
				}
			}

			_args++;
		}

		{
			JavaObject* ref = _args->ref.m_object;
		//	int id = _args->ref.m_id;
			__asm {
		//		push id
				push ref
			}
		}

		{
			JNIEnv* jni = c->m_jni;
			__asm {
				push jni
			}
		}

		int ret_eax;
		ObjectRef objresult;
		ObjectRef* pobjresult = &objresult;

		if (pMethod->m_pReturnType->kind == Type::Type_ref || pMethod->m_pReturnType->kind == Type::Type_array)
		{
			__asm
			{
				push pobjresult;
			}
		}

		__asm {
			call pfunc;
			mov ret_eax,eax
		}

		if (pMethod->m_pReturnType->kind != Type::ReturnType_void)
		{
			if (pMethod->m_pReturnType->kind == Type::BaseType_int)
			{
				push((jint)ret_eax);
			}
			else if (pMethod->m_pReturnType->kind == Type::BaseType_short)
			{
				push((jint)(ret_eax & 0xFFFF));
			}
			else if (pMethod->m_pReturnType->kind == Type::BaseType_bool)
			{
				push((jint)(ret_eax & 1));
			}
			else if (pMethod->m_pReturnType->kind == Type::Type_ref || pMethod->m_pReturnType->kind == Type::Type_array)
			{
				push(objresult);
			//	push(ObjectRef((JavaObject*)ret_eax));
			}
			else
				ASSERT(0);
		}

#if 0
	//	StringA* name = pMethod->GetName();

		/*
		stack<Operand> args;
		int i;
		for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
		{
			args.push(pop()); 
		}
		JavaObject* objref = pop();	// objectref
		*/

		if (*name == "setInputStreamLocalised")
		{
			LOG("");
		}
		else if (*name == "setOutputStreamLocalised")
		{
			LOG("");
		}
		else if (*name == "isOutputStreamLocalised")
		{
			LOG("");
		}
		else if (*name == "setPriority0")
		{
			args.pop();

			LOG("(%d)", (jint)args.top());
		}
		else if (*name == "getDeclaredFields0")
		{
			MessageBeep(-1);
		//	JavaObject* obj = args.top();
		//	args.pop();

		//	obj->m_pClass->GetMethod(

			/*
			CJavaClassType* pClass = (CJavaClassType*)obj;

			bool param = args.top();
			args.pop();

			Class_getDeclaredFields0(env, pClass, objref, param);
*/
			// return value is array
		}
		else
			ASSERT(0);

		if (pMethod->pReturnType->kind != Type::ReturnType_void)
		{
			push((jint)0);
		}
		LOG("{}");
#endif
	}
	else
	{
		CodeAttribute* pCode = pMethod->GetCode();

		Frame* pFrame = new Frame(pMethod, pCode, this, pc);
	//	pFrame->m_pCaller = this;
		c->m_pFrame = pFrame;
		pc = pCode->code;

		pFrame->m_localVariables[0] = args.top();	// objectref
		args.pop();

		LOG("(");

		int n = 1;
		for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
		{
			Type* type = pMethod->m_argumentTypes[i];

			if (i > 0) LOG(", ");

			switch (type->kind)
			{
			case Type::BaseType_double:
			{
				ASSERT(0);
			}
			break;

			case Type::BaseType_long:
			{
				ULONGLONG v = (LONGLONG)args.top();
				args.pop();

				pFrame->m_localVariables[n] = v & 0xFFFFFFFF;
				pFrame->m_localVariables[n+1] = v>>32;
				n += 2;
			}
			break;

			case Type::Type_ref:
			case Type::Type_array:
			{
				ObjectRef ref = args.top();
				TraceObject(ref);

				pFrame->m_localVariables[n] = ref;
				args.pop();
				n++;
			}
			break;

			case Type::BaseType_float:
			{
				*(float*)&pFrame->m_localVariables[n] = (float)args.top();
				args.pop();
				n++;
			}
			break;

			case Type::BaseType_int:
			{
				jint value = args.top();

				pFrame->m_localVariables[n] = value;
				args.pop();
				n++;
			}
			break;

			case Type::BaseType_short:
			{
				jint value = args.top();

				pFrame->m_localVariables[n] = value;
				args.pop();
				n++;
			}
			break;

			case Type::BaseType_wchar:
			{
				uint16 value = args.top();

				pFrame->m_localVariables[n] = value;
				args.pop();
				n++;
			}
			break;

			case Type::BaseType_bool:
			case Type::BaseType_byte:
			{
				jint value = args.top();

				pFrame->m_localVariables[n] = (jint)value;
				args.pop();
				n++;
			}
			break;

			default:
				ASSERT(0);
			}
		}

		LOG(") {");
	}

	return pc;
}

uint8* Frame::jop_invokestatic(Thread* c, uint8* pc)
{
	pc++;
	uint16 methodIndex = getword(pc);

	uint16 classIndex = m_pMethod->m_pOwnerClass->m_pool_array[methodIndex-1].methodRef.class_index;
	VERIFY(classIndex < m_pMethod->m_pOwnerClass->m_constant_pool_count);

	if (m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass == NULL)
	{
		uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
		VERIFY(classNameIndex < m_pMethod->m_pOwnerClass->m_constant_pool_count);

		StringA* className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;
		m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass = c->LoadClass(className);
	}

	JavaClass* pJavaClass = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass;

	ASSERT(pJavaClass);

	uint16 nameAndTypeIndex = m_pMethod->m_pOwnerClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
	uint16 methodNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	uint16 descriptorIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.descriptor_index;
	StringA* methodName = m_pMethod->m_pOwnerClass->m_pool_array[methodNameIndex-1].utf8.str;
	StringA* descriptor = m_pMethod->m_pOwnerClass->m_pool_array[descriptorIndex-1].utf8.str;

	LOG("invokestatic %s.%s", CString(pJavaClass->GetName()).c_str(), CString(methodName).c_str());
	char buffer[512];
	sprintf_s(buffer, "%s%s", CString(methodName).c_str(), CString(descriptor).c_str());
	//StringA* fullName = *methodName + *descriptor;

	JavaMethod* pMethod = pJavaClass->GetMethodByName(buffer);

//	JavaMethod* pMethod = GetMethod(c, methodIndex);

//	sysstring name = pMethod->GetName();
//	LOG("invokestatic %S", name.c_str());

	//methodName = *(*pMethod->m_pClass->GetName() + *pMethod->GetName()) + *pMethod->GetSignature();
//	LOG("invokestatic %s.%s", pMethod->m_pClass->GetName().c_str(), pMethod->GetName().c_str());

	if (pMethod->m_access_flags & ACC_NATIVE)
	{
		char buffer2[1024];
		sprintf_s(buffer2, "%s%s", /*pMethod->m_pClass->GetName()->c_str(),*/ CString(pMethod->GetName()).c_str(), CString(pMethod->GetSignature()).c_str());

		if (!strcmp(buffer2, "newInstance0(Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;"))
		{
			MessageBeep(-1);
		}

		LOG(" native");

		nativefunc pfunc = (nativefunc)pMethod->m_nativeFunc;//m_pClass->m_nativeFuncs[buffer2];
	//	nativefunc pfunc = (nativefunc)c->m_vm->m_nativeFuncs[buffer2];
		if (pfunc == NULL)
			THROW(exception("Native method not found"));

		vector<Operand> args;
		args.reserve(pMethod->m_argumentTypes.GetSize());
		int i;
		for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
		{
			Operand operand = pop();
			args.Add(operand); 
		}

		LOG("{");

		const Operand* _args = args.GetData();

		int nargs = pMethod->m_argumentTypes.GetSize();
		Type** types = pMethod->m_argumentTypes.GetData()+nargs;

		for (i = 0; i < nargs; i++)
		{
			Type* type = *(--types);

			if (type->kind == Type::BaseType_double || type->kind == Type::BaseType_long)
			{
				int64 longlong = _args->u._long;
				uint32 l = (uint32)longlong;
				uint32 h = longlong>>32;
				__asm {
					push h
					push l
				}
			}
			else if (type->kind == Type::Type_ref || type->kind == Type::Type_array)
			{
				JavaObject* object = _args->ref.m_object;
			//	int id = _args->ref.m_id;
				__asm {
			//		push id
					push object
				}
			}
			else
			{
				jint i = _args->u._int;
				__asm {
					push i
				}
			}

			++ _args;
		}

		{
			JavaClass* cls = pMethod->m_pOwnerClass;
			__asm {
				push cls
			}
		}

		{
			JNIEnv* jni = c->m_jni;
			__asm {
				push jni
			}
		}

		uint32 ret_eax;
		uint32 ret_edx;
		ObjectRef objresult;
		ObjectRef* pobjresult = &objresult;

		if (pMethod->m_pReturnType->kind == Type::Type_ref || pMethod->m_pReturnType->kind == Type::Type_array)
		{
			__asm
			{
				push pobjresult;
			}
		}

		__asm {
			call pfunc
			mov ret_eax,eax
			mov ret_edx,edx
		}

		if (pMethod->m_pReturnType->kind != Type::ReturnType_void)
		{
			if (pMethod->m_pReturnType->kind == Type::BaseType_long)
			{
				push((jlong)((LONGLONG)ret_eax | ((LONGLONG)ret_edx<<32)));
			}
			else if (pMethod->m_pReturnType->kind == Type::BaseType_double)
			{
				LONGLONG longlong = (LONGLONG)ret_eax | ((LONGLONG)ret_edx<<32);
				push(*(double*)&longlong);
			}
			else if (pMethod->m_pReturnType->kind == Type::BaseType_int)
			{
				push((jint)ret_eax);
			}
			else if (pMethod->m_pReturnType->kind == Type::BaseType_bool)
			{
				push((jint)ret_eax);
			}
			else if (pMethod->m_pReturnType->kind == Type::Type_ref)
			{
				push(objresult);

				//push(ObjectRef((JavaObject*)ret_eax));
			}
			else
			{
				ASSERT(0);
				THROW(-1);
			}
		}
		LOG("}");
	}
	else
	{
		LOG("");

		CodeAttribute* pCode = pMethod->GetCode();

		Frame* pFrame = new Frame(pMethod, pCode, this, pc);
		//pFrame->m_pCaller = this;
		c->m_pFrame = pFrame;
		pc = pCode->code;

		stack<Operand> args;
		int i;
		for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
		{
			args.push(pop()); 
		}

		LOG("(");

		int n = 0;
		for (i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
		{
			if (i > 0) LOG(", ");

			Type* type = pMethod->m_argumentTypes[i];

			if (type->kind == Type::BaseType_double || type->kind == Type::BaseType_long)
			{
				LONGLONG v = args.top().u._long;
				pFrame->m_localVariables[n] = v & 0xFFFFFFFF;
				pFrame->m_localVariables[n+1] = v>>32;
				args.pop();
				n += 2;
			}
			else if (type->kind == Type::BaseType_float)
			{
				float value = args.top();
				LOG("%g", value);

				pFrame->m_localVariables[n] = *(jint*)&value;
				args.pop();
				n++;
			}
			else if (type->kind == Type::Type_ref || type->kind == Type::Type_array)
			{
				ObjectRef ref = args.top();

				TraceObject(ref);

				pFrame->m_localVariables[n] = ref;
				args.pop();
				n++;
			}
			else if (type->kind == Type::BaseType_int ||
						type->kind == Type::BaseType_wchar ||
						type->kind == Type::BaseType_short ||
						type->kind == Type::BaseType_bool)
			{
				jint value = args.top();
				LOG("%d", value);

				pFrame->m_localVariables[n] = value;
				args.pop();
				n++;
			}
			else
				ASSERT(0);
		}

		LOG(") {");
	}

	return pc;
}

Frame::Frame(JavaMethod* pMethod, CodeAttribute* pCode)
{
	m_pMethod = pMethod;
	m_pCode = pCode;

	m_pCaller = NULL;
	m_localVariables = new LocalVariable[m_pCode->max_locals];
	memset(m_localVariables, 0, 4 * m_pCode->max_locals);
//	pc = pCode->code;
}

Frame::Frame(JavaMethod* pMethod, CodeAttribute* pCode, Frame* pCaller, uint8* returnAddress)
{
	m_pMethod = pMethod;
	m_pCode = pCode;

	m_pCaller = pCaller;
	m_returnAddress = returnAddress;
	m_localVariables = new LocalVariable[m_pCode->max_locals];
	memset(m_localVariables, 0, 4 * m_pCode->max_locals);
//	pc = pCode->code;
}

// Get static field from class
uint8* Frame::jop_getstatic(Thread* c, uint8* pc)
{
	pc++;
	uint16 fieldIndex = getword(pc);

	uint16 classIndex = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.class_index;
//	uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
//	StringA* className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;

	uint16 nameAndTypeIndex = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.name_and_type_index;
	uint16 fieldNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	String fieldName = m_pMethod->m_pOwnerClass->m_pool_array[fieldNameIndex-1].utf8.str;

//	if (m_pMethod->m_pO
//	JavaClass* pJavaClass = c->LoadClass(className);
	if (m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass == NULL)
	{
		uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
		String className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;
		m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass = c->LoadClass(className);
	}
	JavaClass* pJavaClass = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass;

	JavaField* pField = pJavaClass->GetField(fieldName);
	VERIFY(pField);

	pJavaClass = pField->m_pOwnerClass;

	LOG("getstatic %s.%s = ", CString(pField->m_pOwnerClass->GetName()).c_str(), CString(fieldName).c_str());

	if (fieldName == "out")
	{
		LOG("");
	}

	if (fieldName == "reflectionFactory" && pJavaClass->m_name == "java/lang/reflect/Constructor")
	{
		MessageBeep(-1);
	}

	ASSERT(pField->m_access_flags & ACC_STATIC);

	switch (pField->m_pType->kind)
	{
		case Type::BaseType_bool:
		case Type::BaseType_byte:
		{
			int8* p = (int8*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
			LOG("%d", *p);
		}
		break;

		case Type::BaseType_wchar:
		{
			uint16* p = (uint16*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
			LOG("%d", *p);
		}
		break;

		case Type::BaseType_short:
		{
			int16* p = (int16*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
			LOG("%d", *p);
		}
		break;

		case Type::BaseType_int:
		{
			jint* p = (jint*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
			LOG("%d", *p);
		}
		break;

		case Type::BaseType_long:
		{
			jlong* p = (jlong*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
		}
		break;

		case Type::BaseType_float:
		{
			float* p = (float*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
			LOG("%f", *p);
		}
		break;

		case Type::BaseType_double:
		{
			double* p = (double*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
			LOG("%f", *p);
		}
		break;

		case Type::Type_ref:
		case Type::Type_array:
		{
			ObjectRef* p = (ObjectRef*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
			LOG("%p", *p);
		}
		break;
		/*
		else if (pField->m_pType->kind == Type::Type_array)
		{
			ObjectRef* p = (ObjectRef*)(pJavaClass->m_staticData + pField->m_offset);
			push(*p);
			LOG("%p", *p);
		}
		else
		*/
		default:
			ASSERT(0);
	}

	return pc;
}

uint8* Frame::jop_putstatic(Thread* c, uint8* pc)
{
	pc++;
	uint16 fieldIndex = getword(pc);

	uint16 classIndex = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.class_index;

	if (m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass == NULL)
	{
		uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
		StringA* className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;
		m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass = c->LoadClass(className);
	}

	JavaClass* pJavaClass = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass;
	VERIFY(pJavaClass);

	uint16 nameAndTypeIndex = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.name_and_type_index;
	uint16 fieldNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	StringA* fieldName = m_pMethod->m_pOwnerClass->m_pool_array[fieldNameIndex-1].utf8.str;

	JavaField* pField = pJavaClass->GetField(fieldName);
	VERIFY(pField);

	pJavaClass = pField->m_pOwnerClass;

	ASSERT(pField->m_access_flags & ACC_STATIC);

//	LOG("putstatic %s.%s = ", CString(pField->m_pOwnerClass->GetName()).c_str(), CString(fieldName)._str());

	Operand value = pop();

	/*
	if (fieldName == "reflectionFactory")
	{
		MessageBeep(-1);
	}
	*/

	switch (pField->m_pType->kind)
	{
		case Type::BaseType_bool:
		case Type::BaseType_byte:
		{
			// TODO ?
			int8* p = (int8*)(pJavaClass->m_staticData + pField->m_offset);
			*p = value;
			LOG("%d", value.u._int);
		}
		break;

		case Type::BaseType_wchar:
		case Type::BaseType_short:
		{
			int16* p = (int16*)(pJavaClass->m_staticData + pField->m_offset);
			*p = value;

			LOG("%d", value.u._int);
		}
		break;

		case Type::BaseType_int:
		{
			jint* p = (jint*)(pJavaClass->m_staticData + pField->m_offset);
			*p = value;

			LOG("%d", value.u._int);
		}
		break;

		case Type::BaseType_long:
		{
			jlong* p = (jlong*)(pJavaClass->m_staticData + pField->m_offset);
			*p = value;
			LOG("%d", (long)*p);
		}
		break;

		case Type::BaseType_float:
		{
			float* p = (float*)(pJavaClass->m_staticData + pField->m_offset);
			*p = value;
			LOG("%f", value.u._float);
		}
		break;

		case Type::BaseType_double:
		{
			double* p = (double*)(pJavaClass->m_staticData + pField->m_offset);
			*p = value;
			LOG("%d", value.u._double);
		}
		break;

		case Type::Type_ref:
		case Type::Type_array:
		{
			ObjectRef* p = (ObjectRef*)(pJavaClass->m_staticData + pField->m_offset);
			*p = value;

			TraceObject(*p);
			/*
			if (*p && *(*p)->m_pClass->GetName() == "java/lang/String")
			{
				LOG("\"%S\"", GetString(*p)->c_str());
			}
			else
			{
				LOG("%p", *p);
			}
			*/
		}
		break;

		/*
		else if (pField->m_pType->kind == Type::Type_array)
		{
			ObjectRef* p = (ObjectRef*)(pJavaClass->m_staticData + pField->m_offset);
			*p = value;

			LOG("%p", value.ref.m_object);
		}
		else
		*/
		default:
			ASSERT(0);
	}

	return pc;
}

uint8* Frame::jop_getfield(Thread* c, uint8* pc)
{
	pc++;
	uint16 fieldIndex = getword(pc);
	JavaObject* ref = pop();

	if (m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.m_pField == NULL)
	{
		uint16 classIndex = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.class_index;
		if (m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass == NULL)
		{
			uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
			StringA* className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;
			m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass = c->LoadClass(className);
		}
		JavaClass* pJavaClass = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass;

		uint16 nameAndTypeIndex = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.name_and_type_index;
		uint16 fieldNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
		StringA* fieldName = m_pMethod->m_pOwnerClass->m_pool_array[fieldNameIndex-1].utf8.str;

		JavaField* pField = pJavaClass->GetField(fieldName);
		VERIFY(pField);

		m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.m_pField = pField;
	}
	JavaField* pField = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.m_pField;

	//JavaClass* pJavaClass = c->LoadClass(className);

	ASSERT(!(pField->m_access_flags & ACC_STATIC));

	LOG("getfield %s.%s = ", CString(pField->m_pOwnerClass->GetName()).c_str(), CString(pField->GetName()).c_str());

	if (ref == NULL)
	{
		ASSERT(0);
		THROW(-1);
	}

	switch (pField->m_pType->kind)
	{
	case Type::BaseType_wchar:
		{
			uint16* p = (uint16*)(ref->m_data + pField->m_offset);
			LOG("%d", *p);
			push(*p);
		}
		break;
		
	case Type::BaseType_long:
		{
			jlong* p = (jlong*)(ref->m_data + pField->m_offset);
			LOG("%lld", *p);
			push(*p);
		}
		break;
		
	case Type::BaseType_double:
		{
			double* p = (double*)(ref->m_data + pField->m_offset);
			LOG("%f", *p);
			push(*p);
		}
		break;
		
	case Type::BaseType_float:
		{
			float* p = (float*)(ref->m_data + pField->m_offset);
			LOG("%f", *p);
			push(*p);
		}
		break;
		
	case Type::BaseType_int:
		{
			jint* p = (jint*)(ref->m_data + pField->m_offset);
			LOG("%d", *p);
			push(*p);
		}
		break;

	case Type::BaseType_short:
		{
			int16* p = (int16*)(ref->m_data + pField->m_offset);
			LOG("%d", *p);
			push(*p);
		}
		break;
		
	case Type::BaseType_bool:
		{
			int8* p = (int8*)(ref->m_data + pField->m_offset);
			LOG("%d", *p);
			push(*p);
		}
		break;
		
	case Type::Type_ref:
	case Type::Type_array:
		{
			ObjectRef* p = (ObjectRef*)(ref->m_data + pField->m_offset);
			push(*p);
			
			TraceObject(*p);
			/*
			if (*p && *(*p)->m_pClass->GetName() == "java/lang/String")
			{
			LOG("\"%S\"", GetString(*p)->c_str());
			}
			else
			{
			LOG("%p", *p);
			}
			*/
		}
		break;

	/*
	else if (pField->m_pType->kind == Type::Type_array)
	{
		ObjectRef* p = (ObjectRef*)(ref->m_data + pField->m_offset);
		LOG("%p", *p);
		push(*p);
	}
	else
	*/
		default:
			ASSERT(0);
	}

	return pc;
}

uint8* Frame::jop_putfield(Thread* c, uint8* pc)
{
	pc++;
	uint16 fieldIndex = getword(pc);

	Operand value = pop();
	JavaObject* ref = pop();

	if (m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.m_pField == NULL)
	{
		uint16 classIndex = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.class_index;
		if (m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass == NULL)
		{
			uint16 classNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.name_index;
			StringA* className = m_pMethod->m_pOwnerClass->m_pool_array[classNameIndex-1].utf8.str;
			m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass = c->LoadClass(className);
		}
		JavaClass* pJavaClass = m_pMethod->m_pOwnerClass->m_pool_array[classIndex-1].classData.m_pClass;

		uint16 nameAndTypeIndex = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.name_and_type_index;
		uint16 fieldNameIndex = m_pMethod->m_pOwnerClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
		StringA* fieldName = m_pMethod->m_pOwnerClass->m_pool_array[fieldNameIndex-1].utf8.str;

		JavaField* pField = pJavaClass->GetField(fieldName);
		VERIFY(pField);

		m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.m_pField = pField;
	}
	JavaField* pField = m_pMethod->m_pOwnerClass->m_pool_array[fieldIndex-1].fieldRef.m_pField;

	/*
	if (*fieldName == "reflectionFactory")
	{
		MessageBeep(-1);
	}
	*/

	LOG("putfield %s.%s = ", CString(pField->m_pOwnerClass->GetName()).c_str(), CString(pField->GetName()).c_str());

//	JavaClass* pJavaClass = c->LoadClass(className);

	ASSERT(!(pField->m_access_flags & ACC_STATIC));

	switch (pField->m_pType->kind)
	{
		case Type::BaseType_bool:
		case Type::BaseType_byte:
		{
			int8* p = (int8*)(ref->m_data + pField->m_offset);
			*p = value;
			LOG("%d", *p);
		}
		break;

		case Type::BaseType_wchar:
		case Type::BaseType_short:
		{
			int16* p = (int16*)(ref->m_data + pField->m_offset);
			*p = value;
			LOG("%d", *p);
		}
		break;

		case Type::BaseType_int:
		{
			jint* p = (jint*)(ref->m_data + pField->m_offset);
			*p = value;
			LOG("%d", *p);
		}
		break;

		case Type::BaseType_long:
		{
			jlong* p = (jlong*)(ref->m_data + pField->m_offset);
			LOG("%d", (long)*p);
			*p = value;
		}
		break;

		case Type::BaseType_double:
		{
			double* p = (double*)(ref->m_data + pField->m_offset);
			*p = value;
			LOG("%f", *p);
		}
		break;

		case Type::BaseType_float:
		{
			float* p = (float*)(ref->m_data + pField->m_offset);
			*p = value;
			LOG("%f", *p);
		}
		break;

		case Type::Type_ref:
		case Type::Type_array:
		{
			ObjectRef* p = (ObjectRef*)(ref->m_data + pField->m_offset);
			*p = value;

			TraceObject(*p);
			/*
			if (*p && (int)(*p)->m_pClass > 10 && *(*p)->m_pClass->GetName() == "java/lang/String")
			{
				LOG("\"%S\"", GetString(*p)->c_str());
			}
			else
			{
				LOG("%p", *p);
			}
			*/
		}
		break;
		/*
		else if (pField->m_pType->kind == Type::Type_array)
		{
			ObjectRef* p = (ObjectRef*)(ref->m_data + pField->m_offset);
			*p = value;
			LOG("%p", *p);
		}
		else
		*/
		default:
			ASSERT(0);
	}

	return pc;
}

uint8* Frame::jop_ldc(Thread* c, uint8* pc)
{
	pc++;
	uint8 index = *pc++;
	LOG("ldc ");

	const CPoolItem& item = m_pMethod->m_pOwnerClass->m_pool_array[index-1];
	if (item.tag == CONSTANT_Integer)
	{
		LOG("%d", item.int_32);
		push(item.int_32);
	}
	else if (item.tag == CONSTANT_Float)
	{
		LOG("%f", item.float_32);
		push(item.float_32);
	}
	else if (item.tag == CONSTANT_String)
	{
		JavaObject* pString = m_pMethod->m_pOwnerClass->m_pool_array[item.string_index-1].GetString(c);
//		LOG("%S", CString(m_pMethod->m_pOwnerClass->m_pool_array[item.string_index-1].utf8.wstr).c_str());
		/*
		StringW* stringW = Utf8ToW(m_pMethod->m_pClass->m_pool_array[item.string_index-1].str);
		LOG("%S", stringW->c_str());

		JavaObject* pString = c->NewString(stringW->c_str(), stringW->Length());
		VERIFY(pString);
		*/
		/*
		JavaClass* pClass = c->LoadClass("java/lang/String");

		JavaObject* pString = pClass->CreateInstance();
		{
			JavaField* pField = pString->m_pClass->GetFieldByName("value");
			JavaObject** pValue = (JavaObject**)(pString->m_data + pField->m_offset);
			(*pValue) = new JavaObject;
			(*pValue)->m_data = (uint8*)new jchar[string.Length()];
			(*pValue)->baseType = 5;	// char
			(*pValue)->m_count = string.Length();

			memcpy((*pValue)->m_data, string.c_str(), string.Length()*sizeof jchar);
		}
		{
			JavaField* pField = pString->m_pClass->GetFieldByName("count");
			jint* pcount = (jint*)(pString->m_data + pField->m_offset);
			*pcount = string.Length();
		}
		*/

		push(ObjectRef(pString));
	}
	else
	{
		THROW(-1);
		ASSERT(0);
	}
	return pc;
}

uint8* Frame::jop_ldc_w(Thread* c, uint8* pc)
{
	pc++;
	uint16 index = getword(pc);
	if (index == 0) throw exception("pool index out of range");

//	if (index > m_pMethod->m_pClass->constant_pool_size)
//		throw exception("pool index out of range");

	LOG("ldc_w");

	CPoolItem& item = m_pMethod->m_pOwnerClass->m_pool_array[index-1];
	if (item.tag == CONSTANT_Integer)
	{
		LOG("%d", item.int_32);
		push(item.int_32);
	}
	else if (item.tag == CONSTANT_Float)
	{
		LOG("%f", item.float_32);
		push(item.float_32);
	}
	else if (item.tag == CONSTANT_String)
	{
		ObjectRef pString = m_pMethod->m_pOwnerClass->m_pool_array[item.string_index-1].GetString(c);
		/*
		StringW* stringW = Utf8ToW(m_pMethod->m_pClass->m_pool_array[item.string_index-1].str);
		LOG("%S", stringW->c_str());

		JavaObject* pString = c->NewString(stringW->c_str(), stringW->Length());
		*/

		VERIFY(pString != NULL);

		push(pString);
	}
	// ??
	else if (item.tag == CONSTANT_Class)
	{
		if (true)
		{
			if (item.classData.m_pClass == NULL)
			{
				StringA* className = m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str;

				item.classData.m_pClass = c->LoadClass(className);
			}

			push(ObjectRef(item.classData.m_pClass->GetObject()));
		}
		else
		{
			JavaObject* pString = m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].GetString(c);
			/*
			StringW* stringW = Utf8ToW(m_pMethod->m_pClass->m_pool_array[item.string_index-1].str);
			LOG("%S", stringW->c_str());

			JavaObject* pString = c->NewString(stringW->c_str(), stringW->Length());
			*/

			VERIFY(pString);

			push(ObjectRef(pString));
		}
	}
	else
	{
	//	THROW(-1);
		ASSERT(0);
	}

	return pc;
}

uint8* Frame::jop_ldc2_w(Thread* c, uint8* pc)
{
	pc++;
	uint16 index = getword(pc);
	LOG("ldc2_w");

	const CPoolItem& item = m_pMethod->m_pOwnerClass->m_pool_array[index-1];
	if (item.tag == CONSTANT_Long)
	{
		push(item.long_64);
	}
	else if (item.tag == CONSTANT_Double)
	{
		push(item.double_64);
	}
	else
	{
		THROW(-1);
		ASSERT(0);
	}
	return pc;
}

uint8* Frame::jop_jsr(Thread* c, uint8* pc)
{
	uint8* start = pc++;
	short offset = getword(pc);
	push(pc);
	pc = start + offset;

	LOG("jsr - ");

	return pc;
}

uint8* Frame::jop_ret(Thread* c, uint8* pc)
{
	pc++;
	uint8 index = *pc++;
	pc = (uint8*)m_localVariables[index].m_value;

	LOG("ret - ");

	return pc;
}

uint8* Frame::jop_new(Thread* c, uint8* pc)
{
	pc++;
	uint16 index = getword(pc);

	const CPoolItem& item = m_pMethod->m_pOwnerClass->m_pool_array[index-1];
	LOG("new");

	if (item.tag == CONSTANT_Class)
	{
		String classname = m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str;
		if (classname == "java/lang/IllegalThreadStateException")
		{
			LOG("\n");
		}

		JavaClass* pClass = c->LoadClass(classname);

		LOG("new %s", CString(pClass->GetName()).c_str());

		JavaObject* pObjectRef = pClass->CreateInstance();

		push(ObjectRef(pObjectRef));
	}
	else
	{
		ASSERT(0);//methodRef.class_index;
		THROW(-1);
	}

	return pc;
}

uint8* Frame::jop_arraylength(Thread* c, uint8* pc)
{
	pc++;

	JavaObject* ref = pop();
	if (ref == NULL)
		THROW(-1);	// NullPointerException

	LOG("%d", GetArrayLength(ref));

	push(GetArrayLength(ref));

	return pc;
}

uint8* Frame::jop_newarray(Thread* c, uint8* pc)
{
	pc++;
	uint8 atype = *pc++;

	ASSERT(atype >= 4 && atype <= 11);

	LOG("newarray - ");

	String className = m_pMethod->m_pOwnerClass->GetName();
	String methodName = m_pMethod->GetName();

	int32 count = pop();
	if (count < 0)
		THROW(-1);

	JavaClass* pArrayClass;

	switch (atype)
	{
	case ArrayType_BOOLEAN:
		pArrayClass = pBooleanArrayClass;
		break;

	case ArrayType_BYTE:
		pArrayClass = pByteArrayClass;
		break;

	case ArrayType_CHAR:
		pArrayClass = pCharArrayClass;
		break;

	case ArrayType_SHORT:
		pArrayClass = pShortArrayClass;
		break;

	case ArrayType_INT:
		pArrayClass = pIntArrayClass;
		break;

	case ArrayType_FLOAT:
		pArrayClass = pFloatArrayClass;
		break;

	case ArrayType_LONG:
		pArrayClass = pLongArrayClass;
		break;

	case ArrayType_DOUBLE:
		pArrayClass = pDoubleArrayClass;
		break;

	default:
		ASSERT(0);
	}

	ArrayRef* ref = pArrayClass->CreateInstance();

	GetArrayFields(ref)->m_length = count;
	GetArrayFields(ref)->m_data = new uint8[pArrayClass->m_pArrayOf->m_baseTypeSize * count];

	memset(GetArrayData(ref), 0, pArrayClass->m_pArrayOf->m_baseTypeSize * count);

	LOG("[%d]", count);

	push(ObjectRef(ref));

	return pc;
}

uint8* Frame::jop_anewarray(Thread* c, uint8* pc)
{
	pc++;
	uint16 index = getword(pc);

	LOG("anewarray - ");

	int32 count = pop();
	if (count < 0)
		THROW(-1);

	const CPoolItem& item = m_pMethod->m_pOwnerClass->m_pool_array[index-1];

	if (item.tag == CONSTANT_Class)
	{
		String str = m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str;

		ArrayRef* ref;// = new ArrayRef;

		if (str.LeftOf(1) == "[")	// array
		{
			ASSERT(0);
		//	JavaClass* pClass = c->m_vm->LoadClass(str.c_str()+1);
		//	ref->m_TypeOfClass = pClass;
		}
		else
		{
			JavaClass* pClass = c->LoadClass(str);
			LOG("%s", CString(pClass->GetName()).c_str());

			char buf[512];
			sprintf_s(buf, "[L%s;", CString(str).c_str());
			String arraystr = string_copy(buf);

			JavaClass* pArrayClass = GetArrayClass(arraystr, pClass, c->m_vm);//c->m_vm->m_classes[arraystr];
			ASSERT(pArrayClass->m_pArrayOf == pClass);
			ref = pArrayClass->CreateInstance();
			/*
			if (pArrayClass == NULL)
			{
				pArrayClass = new JavaClass;
				pArrayClass->m_name = arraystr;
				pArrayClass->m_pSuperClass = c->LoadClass(&StringA(true, "java/lang/Object"));
				pArrayClass->m_pArrayOf = pClass;
				pArrayClass->m_instanceFieldSize = sizeof(ArrayFields);

				c->m_vm->m_classes[arraystr] = pArrayClass;
			}
			*/

			//ref->m_pClass = pArrayClass;//(JavaClass*)4;	// TODO

		//	ref->m_TypeOfClass = pClass;
		}

	//	ref->baseType = 0;
		GetArrayFields(ref)->m_length = count;
		GetArrayFields(ref)->m_data = new uint8[4 * count];
		memset(GetArrayData(ref), 0, 4 * count);
		push(ObjectRef(ref));
	}
	else
	{
		ASSERT(0);//methodRef.class_index;
		THROW(-1);
	}

	return pc;
}

bool CheckCast(JavaClass* pT, JavaClass* pClass)
{
	while (pClass)
	{
		if (pClass == pT)
			return true;

		pClass = pClass->GetSuperClass();
	}

	return false;
}

uint8* Frame::jop_checkcast(Thread* c, uint8* pc)
{
	pc++;
	uint16 index = getword(pc);

	JavaObject* objectRef = pop();
	push(ObjectRef(objectRef));

	LOG("checkcast ");
	TraceObject(objectRef);

	CPoolItem& item = m_pMethod->m_pOwnerClass->m_pool_array[index-1];

	if (item.tag == CONSTANT_Class)
	{
		if (item.classData.m_pClass == NULL)
		{
			if (m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str->data()[0] == '[')
			{
				JavaClass* pJavaClass = c->m_vm->m_classes[m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str];
				if (pJavaClass)
				{
					item.classData.m_pClass = pJavaClass;
				}
				else
				{
					//pJavaClass = GetArrayClass(m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str, 

					String str = m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str;
					CString cstr(str);
					const char* p = cstr.c_str();
					Type* pType = _ParseFieldType(p);
					pJavaClass = GetClass(pType, c);
					item.classData.m_pClass = pJavaClass;

					/*
					pType->u.arrayof->className;

					pJavaClass = new JavaClass;
					pJavaClass->m_name = m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str;
					item.classData.m_pClass = pJavaClass;

					c->m_vm->m_classes[m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str] = pJavaClass;
					*/
				}
			}
			else
			{
				item.classData.m_pClass = c->LoadClass(m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str);
			}
		}

		JavaClass* pT = item.classData.m_pClass;

		LOG("%s", CString(pT->GetName()).c_str());

		if (objectRef)
		{
			JavaClass* pClass = objectRef->m_pClass;

			if (!CheckCast(pT, pClass))
			{
				THROW(-1);	// ClassCastException
			}
		}
	}
	else
	{
		ASSERT(0);
	}

	return pc;
}

uint8* Frame::jop_instanceof(Thread* c, uint8* pc)
{
	pc++;
	uint16 index = getword(pc);

	JavaObject* objectRef = pop();

	const CPoolItem& item = m_pMethod->m_pOwnerClass->m_pool_array[index-1];

	LOG("instanceof ");
	TraceObject(objectRef);

	if (item.tag == CONSTANT_Class)
	{
		JavaClass* pT = c->LoadClass(m_pMethod->m_pOwnerClass->m_pool_array[item.classData.name_index-1].utf8.str);

		LOG("%s", CString(pT->GetName()).c_str());

		if (objectRef)
		{
			JavaClass* pClass = objectRef->m_pClass;

			if (CheckCast(pT, pClass))
			{
				push((jint)1);
			}
			else
			{
				push((jint)0);
			}
		}
		else
		{
			push((jint)0);
		}
	}
	else
	{
		ASSERT(0);
	}

	return pc;
}

uint8* Frame::jop_bipush(Thread* c, uint8* pc)
{
	pc++;
	char int8 = (char)*pc++;

	LOG("bipush");
	push((long)int8);

	return pc;
}

uint8* Frame::jop_sipush(Thread* c, uint8* pc)
{
	pc++;
	short int16 = (short)getword(pc);

	LOG("%d", int16);

	LOG("sipush");
	push((jint)int16);

	return pc;
}

uint8* Frame::jop_iadd(Thread* c, uint8* pc)
{
	pc++;

	LOG("iadd");
	jint value2 = pop();
	jint value1 = pop();

	push(value1 + value2);

	return pc;
}

uint8* Frame::jop_ladd(Thread* c, uint8* pc)
{
	pc++;

	LOG("ladd");
	int64 value2 = pop();
	int64 value1 = pop();

	push(value1 + value2);

	return pc;
}

uint8* Frame::jop_isub(Thread* c, uint8* pc)
{
	pc++;

	LOG("isub");
	jint value2 = pop();
	jint value1 = pop();

	push(value1 - value2);

	return pc;
}

uint8* Frame::jop_iand(Thread* c, uint8* pc)
{
	pc++;

	LOG("iand");
	jint value2 = pop();
	jint value1 = pop();

	push(value1 & value2);

	return pc;
}

uint8* Frame::jop_land(Thread* c, uint8* pc)
{
	pc++;

	LOG("land");
	jlong value2 = pop();
	jlong value1 = pop();

	push(value1 & value2);

	return pc;
}

uint8* Frame::jop_ior(Thread* c, uint8* pc)
{
	pc++;

	LOG("ior");
	jint value2 = pop();
	jint value1 = pop();

	push(value1 | value2);

	return pc;
}

uint8* Frame::jop_lor(Thread* c, uint8* pc)
{
	pc++;

	LOG("lor");
	jlong value2 = pop();
	jlong value1 = pop();

	push(value1 | value2);

	return pc;
}

uint8* Frame::jop_ishl(Thread* c, uint8* pc)
{
	pc++;

	LOG("ishl");
	jint value2 = pop();
	jint value1 = pop();

	push(value1 << value2);

	return pc;
}

// Arithmetic shift right int
uint8* Frame::jop_ishr(Thread* c, uint8* pc)
{
	pc++;

	LOG("ishr");
	jint value2 = pop();
	jint value1 = pop();

	push(value1 >> value2);

	return pc;
}

uint8* Frame::jop_iinc(Thread* c, uint8* pc)
{
	pc++;

	LOG("iinc");

	uint8 index = *pc++;
	signed char v = *pc++;

	m_localVariables[index].m_value += v;

	return pc;
}

uint8* Frame::jop_ineg(Thread* c, uint8* pc)
{
	pc++;

	LOG("ineg");
	jint value = pop();

	push(-value);

	return pc;
}

uint8* Frame::jop_imul(Thread* c, uint8* pc)
{
	pc++;
	LOG("imul");

	jint value2 = pop();
	jint value1 = pop();

	push(value1 * value2);

	return pc;
}

// int remainder
uint8* Frame::jop_irem(Thread* c, uint8* pc)
{
	pc++;
	LOG("irem");

	jint value2 = pop();
	jint value1 = pop();

	if (value2 == 0)
		THROW(-1);	// ArithmeticException
	
	jint result = value1 - (value1 / value2) * value2;

	push(result);

	return pc;
}

uint8* Frame::jop_fmul(Thread* c, uint8* pc)
{
	pc++;
	LOG("fmul");

	float value2 = pop();
	float value1 = pop();

	push(value1 * value2);

	return pc;
}

uint8* Frame::jop_idiv(Thread* c, uint8* pc)
{
	pc++;
	LOG("idiv");

	jint value2 = pop();
	jint value1 = pop();

	if (value2 == 0)
	{
		VERIFY(0);
		// throw ArithmeticException
	}

	push(value1 / value2);

	return pc;
}

uint8* Frame::jop_tableswitch(Thread* c, uint8* pc)
{
	uint8* start = pc;
	pc++;

//	pad bytes (align on 4 bytes)
	pc = (uint8*)(((unsigned int)pc+3) & ~3);

	long _default = getlong(pc);
	long _low = getlong(pc);
	long _high = getlong(pc);

	int32 index = pop();
	LOG("tableswitch");

	if (index < _low || index > _high)
	{
		pc = start + _default;
	}
	else
	{
		long n = index - _low;
		n <<= 2;
		long address = pc[n]<<24;
		address |= pc[n+1]<<16;
		address |= pc[n+2]<<8;
		address |= pc[n+3];

		pc = start + address;
	}

	return pc;
}

uint8* Frame::jop_lookupswitch(Thread* c, uint8* pc)
{
	uint8* start = pc;
	pc++;
//	pad bytes (align on 4 bytes)
	pc = (uint8*)(((unsigned int)pc+3) & ~3);

	int32 defaultoffset = (*pc++)<<24;
	defaultoffset |= (*pc++)<<16;
	defaultoffset |= (*pc++)<<8;
	defaultoffset |= (*pc++);

	int npairs = (*pc++)<<24;
	npairs |= (*pc++)<<16;
	npairs |= (*pc++)<<8;
	npairs |= (*pc++);

	VERIFY(npairs >= 0);

	uint8* pc2 = pc;
	pc += npairs*8;

	jint key = pop();

	for (int i = 0; i < npairs; i++)
	{
		jint match = (pc2[0])<<24;
		match |= (pc2[1])<<16;
		match |= (pc2[2])<<8;
		match |= (pc2[3]);
		pc2 += 4;

		int32 offset = (pc2[0])<<24;
		offset |= (pc2[1])<<16;
		offset |= (pc2[2])<<8;
		offset |= (pc2[3]);
		pc2 += 4;

		if (key == match)
		{
			pc = start + offset;
			return pc;
		}
	}

	pc = start + defaultoffset;

	return pc;
}

uint8* Frame::jop_monitorenter(Thread* c, uint8* pc)
{
	pc++;

	JavaObject* objectRef = pop();

	LOG("monitorenter");
	// TODO

	return pc;
}

uint8* Frame::jop_monitorexit(Thread* c, uint8* pc)
{
	pc++;

	LOG("monitorexit");
	JavaObject* objectRef = pop();

	// TODO

	return pc;
}

uint8* Frame::jop_athrow(Thread* c, uint8* pc)
{
//	pc++;
	LOG("athrow");

	ObjectRef objectRef = pop();
// check that its a subclass of Throwable

	if (!CheckCast(c->LoadClass("java/lang/Throwable"), objectRef->m_pClass))
	{
		ASSERT(0);
		THROW(-1);
	}

	do
	{
		int curpc = c->m_pc - c->m_pFrame->m_pCode->code;

		for (int i = 0; i < c->m_pFrame->m_pMethod->m_exception_count; i++)
		{
			if (curpc >= c->m_pFrame->m_pMethod->m_exceptions[i].start_pc && c->m_pFrame->m_pMethod->m_exceptions[i].end_pc < curpc)
			{
				if (c->m_pFrame->m_pMethod->m_exceptions[i].catch_type == 0)	// all exceptions
				{
					c->m_pFrame->m_operands.RemoveAll();
					push(objectRef);
					pc = c->m_pFrame->m_pCode->code + c->m_pFrame->m_pMethod->m_exceptions[i].handler_pc;
					return 0;
				}

				StringA* className = c->m_pFrame->m_pMethod->m_pOwnerClass->m_pool_array[c->m_pFrame->m_pMethod->m_exceptions[i].catch_type-1].utf8.str;
				JavaClass* pCatchType = c->LoadClass(className);

				if (CheckCast(pCatchType, objectRef->m_pClass))
				{
					c->m_pFrame->m_operands.RemoveAll();
					push(objectRef);
					pc = c->m_pFrame->m_pCode->code + c->m_pFrame->m_pMethod->m_exceptions[i].handler_pc;
					return 0;
				}
			}
		}

		c->m_pFrame = c->m_pFrame->m_pCaller;
	}
	while (c->m_pFrame);

	JavaField* pValueField = objectRef->m_pClass->GetField("detailMessage");
	if (pValueField == NULL) raise(Exception(L"detailMessage not found"));
	ObjectRef* pValue = (ObjectRef*)(objectRef->m_data + pValueField->m_offset);
	raise(Exception(GetString(*pValue)));

	// Exit thread

	return pc;
	//return 1;
}

// Logical shift right int
uint8* Frame::jop_iushr(Thread* c, uint8* pc)
{
	pc++;
	LOG("iushr");

	jint value2 = pop();
	jint value1 = pop();

	push((jint)((unsigned int)value1 >> value2));

	return pc;
}

uint8* Frame::jop_ixor(Thread* c, uint8* pc)
{
	pc++;
	LOG("ixor");

	jint value2 = pop();
	jint value1 = pop();

	push(value1 ^ value2);

	return pc;
}

uint8* Frame::jop_breakpoint(Thread* c, uint8* pc)
{
	pc++;
	LOG("breakpoint");
	c->m_vm->Breakpoint(c, 1);

	return pc;
}

Frame::tyfunc Frame::funcs[256] =
{
	&Frame::jop_nop,
	&Frame::jop_aconst_null,
	&Frame::jop_iconst_m1,	// minus 1
	&Frame::jop_iconst_0,
	&Frame::jop_iconst_1,
	&Frame::jop_iconst_2,
	&Frame::jop_iconst_3,
	&Frame::jop_iconst_4,
	&Frame::jop_iconst_5,
	&Frame::jop_lconst_0,
	&Frame::jop_lconst_1,
	&Frame::jop_fconst_0,
	&Frame::jop_fconst_1,
	&Frame::jop_fconst_2,
	&Frame::jop_dconst_0,
	&Frame::jop_dconst_1,
	&Frame::jop_bipush,
	&Frame::jop_sipush,
	&Frame::jop_ldc,
	&Frame::jop_ldc_w,
	&Frame::jop_ldc2_w,	// 20
	&Frame::jop_iload,
	&Frame::jop_lload,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_aload,
	&Frame::jop_iload_0,
	&Frame::jop_iload_1,
	&Frame::jop_iload_2,
	&Frame::jop_iload_3,
	&Frame::jop_lload_0,	// 30
	&Frame::jop_lload_1,
	&Frame::jop_lload_2,
	&Frame::jop_lload_3,
	&Frame::jop_fload_0,
	&Frame::jop_fload_1,
	&Frame::jop_fload_2,	// 36
	&Frame::jop_fload_3,
	&Frame::jop_dload_0,
	&Frame::jop_dload_1,
	&Frame::jop_dload_2,	// 40
	&Frame::jop_dload_3,
	&Frame::jop_aload_0,
	&Frame::jop_aload_1,
	&Frame::jop_aload_2,
	&Frame::jop_aload_3,
	&Frame::jop_iaload,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_aaload,	// 50
	&Frame::jop_baload,
	&Frame::jop_caload,
	&Frame::jop_notimpl,
	&Frame::jop_istore,
	&Frame::jop_lstore,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_astore,
	&Frame::jop_istore_0,
	&Frame::jop_istore_1,	// 60
	&Frame::jop_istore_2,
	&Frame::jop_istore_3,
	&Frame::jop_lstore_0,
	&Frame::jop_lstore_1,
	&Frame::jop_lstore_2,
	&Frame::jop_lstore_3,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,	// 70
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_astore_0,
	&Frame::jop_astore_1,
	&Frame::jop_astore_2,
	&Frame::jop_astore_3,
	&Frame::jop_iastore,
	&Frame::jop_notimpl,	// 80
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_aastore,
	&Frame::jop_bastore,
	&Frame::jop_castore,
	&Frame::jop_notimpl,
	&Frame::jop_pop,
	&Frame::jop_pop2,
	&Frame::jop_dup,
	&Frame::jop_dup_x1,
	&Frame::jop_dup_x2,
	&Frame::jop_dup2,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_iadd,	// 96
	&Frame::jop_ladd,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_isub,	// 100
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_imul,
	&Frame::jop_notimpl,
	&Frame::jop_fmul,
	&Frame::jop_notimpl,
	&Frame::jop_idiv,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_irem,	// 112
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_ineg,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_ishl,	// 120
	&Frame::jop_notimpl,
	&Frame::jop_ishr,
	&Frame::jop_notimpl,
	&Frame::jop_iushr,
	&Frame::jop_notimpl,
	&Frame::jop_iand,
	&Frame::jop_land,
	&Frame::jop_ior,
	&Frame::jop_lor,
	&Frame::jop_ixor,	// 130
	&Frame::jop_notimpl,
	&Frame::jop_iinc,
	&Frame::jop_i2l,
	&Frame::jop_i2f,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_f2i,
	&Frame::jop_notimpl,
	&Frame::jop_f2d,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_i2b,
	&Frame::jop_i2c,
	&Frame::jop_notimpl,
	&Frame::jop_lcmp,
	&Frame::jop_fcmpl,
	&Frame::jop_fcmpg,	// 150
	&Frame::jop_dcmpl,
	&Frame::jop_dcmpg,
	&Frame::jop_ifeq,
	&Frame::jop_ifne,
	&Frame::jop_iflt,
	&Frame::jop_ifge,
	&Frame::jop_ifgt,
	&Frame::jop_ifle,
	&Frame::jop_if_icmpeq,
	&Frame::jop_if_icmpne,
	&Frame::jop_if_icmplt,
	&Frame::jop_if_icmpge,
	&Frame::jop_if_icmpgt,
	&Frame::jop_if_icmple,
	&Frame::jop_if_acmpeq,
	&Frame::jop_if_acmpne,
	&Frame::jop_goto,
	&Frame::jop_jsr,
	&Frame::jop_ret,
	&Frame::jop_tableswitch,
	&Frame::jop_lookupswitch,
	&Frame::jop_ireturn,	// 172
	&Frame::jop_lreturn,
	&Frame::jop_freturn,
	&Frame::jop_notimpl,
	&Frame::jop_areturn,
	&Frame::jop_return,
	&Frame::jop_getstatic,
	&Frame::jop_putstatic,
	&Frame::jop_getfield,
	&Frame::jop_putfield,
	&Frame::jop_invokevirtual,	// 182
	&Frame::jop_invokespecial,
	&Frame::jop_invokestatic,
	&Frame::jop_invokeinterface,
	&Frame::jop_notimpl,
	&Frame::jop_new,
	&Frame::jop_newarray,
	&Frame::jop_anewarray,
	&Frame::jop_arraylength,	// 190
	&Frame::jop_athrow,
	&Frame::jop_checkcast,
	&Frame::jop_instanceof,
	&Frame::jop_monitorenter,	// 194
	&Frame::jop_monitorexit,
	&Frame::jop_notimpl,
	&Frame::jop_notimpl,
	&Frame::jop_ifnull,
	&Frame::jop_ifnonnull,
	&Frame::jop_notimpl,	// 200
	&Frame::jop_notimpl,
	&Frame::jop_breakpoint,
/*
Reserved opcodes:

202 (0xca) breakpoint

254 (0xfe) impdep1

255 (0xff) impdep2
*/
};

JavaObject* CPoolItem::GetString(Thread* c)
{
	if (utf8.ref) return utf8.ref;

	utf8.wstr = (StringW*)Utf8ToW(utf8.str).m_stringObject;
	utf8.ref = c->NewString((jchar*)utf8.wstr->GetData(), utf8.wstr->GetLength());
	return utf8.ref;
}

extern char* JavaOpcodeNames[256];

int Thread::next_instruction()
{
	if (*m_pc == 0xca)	// Breakpoint
	{
		m_vm->Breakpoint(this, 1);
	}
	else if (m_vm->m_flags & 1)	// Single-step
	{
		m_vm->Breakpoint(this, 2);
	}

	Frame* p = m_pFrame->m_pCaller;
	while (p)
	{
		LOG("\t");
		p = p->m_pCaller;
	}

//	LOG("%s - ", JavaOpcodeNames[*m_pFrame->pc]);

//	int r = (m_pFrame->*Frame::funcs[*m_pFrame->pc])(this);
	m_pc = (m_pFrame->*Frame::funcs[*m_pc])(this, m_pc);

	LOG("\n");

	return m_pFrame == NULL;
//	return r;
}

string_data<WCHAR> GetStringData(JavaObject* pString)
{
	JavaField* pCountField = pString->m_pClass->GetFieldByName("count");
	int count = *(jint*)(pString->m_data + pCountField->m_offset);

	JavaField* pValueField = pString->m_pClass->GetFieldByName("value");
	ObjectRef* pValue = (ObjectRef*)(pString->m_data + pValueField->m_offset);

	return string_data<WCHAR>((WCHAR*)(*pValue)->m_data, count);
}

String GetString(JavaObject* pString)
{
	int count;
	{
		JavaField* pField = pString->m_pClass->GetFieldByName("count");
		count = *(jint*)(pString->m_data + pField->m_offset);
	}

	JavaField* pField = pString->m_pClass->GetFieldByName("value");
	ObjectRef* pValue = (ObjectRef*)(pString->m_data + pField->m_offset);
	if (true)	// TODO
		return string_copy((WCHAR*)GetArrayData(*pValue), count);
//	else
//		return ringW(true, (WCHAR*)GetArrayData(*pValue), count);
}

// Returns java/lang/Throwable
ObjectRef __stdcall java_lang_Exception_fillInStackTrace(JNINativeInterface* env, ObjectRef self)
{
	return NULL;
}

// Returns java/lang/Throwable
ObjectRef __stdcall java_lang_Throwable_fillInStackTrace(JNINativeInterface* env, ObjectRef self)
{
	return NULL;
}

ObjectRef __stdcall java_io_FileSystem_getFileSystem(JNINativeInterface* env, JavaClass* cls)
{
	JavaClass* pClass = env->m_pThread->LoadClass("java/io/Win32FileSystem");

	ObjectRef obj = pClass->CreateInstance();

	JavaMethod* pMethod = pClass->GetMethodByName("<init>()V");
	env->CallVoidMethod(obj, (jmethodID)pMethod);

	return obj;
}

jlong __stdcall System_currentTimeMillis(JNINativeInterface* env, JavaClass* cls)
{
	SYSTEMTIME systime = {0};
	systime.wYear = 1970;
	systime.wMonth = 1;
	systime.wDay = 1;
	systime.wDayOfWeek = 1;
	LONGLONG filetime;
	SystemTimeToFileTime(&systime, (FILETIME*)&filetime);

	GetLocalTime(&systime);
	LONGLONG curtime;
	SystemTimeToFileTime(&systime, (FILETIME*)&curtime);
//	LONGLONG filetime;
//	GetSystemTimeAsFileTime((FILETIME*)&filetime);

	curtime -= filetime;

	curtime /= 100000;	// convert to milliseconds

	return curtime;
}

// Returns a string
ObjectRef __stdcall System_mapLibraryName(JNINativeInterface* env, JavaClass* cls, ObjectRef str)
{
	// TODO ??

	String str2 = GetString(str);

	WCHAR buffer[512];
	swprintf_s(buffer, L"d:\\users\\sigurd\\documents\\vsprojects\\mmstudio\\bin\\win32\\debug\\%s.dll", CStringw(str2).c_str());

	return (JavaObject*)env->NewString(buffer);
}

ObjectRef __stdcall System_initSystemFD(JNIEnv* env, JavaClass* cls, ObjectRef fd, int desc)
{
	// Is this used in the latest version ?
	// ???
	return fd;
}

void __stdcall java_io_Win32FileSystem_initIDs(JNINativeInterface* env, JavaClass* cls)
{
	// ??
	LOG("");
}

jint __stdcall java_io_Win32FileSystem_getBooleanAttributes(JNINativeInterface* env, ObjectRef self, ObjectRef file)
{
	// ??

	JavaField* pField = file->m_pClass->GetField("path");
	ObjectRef path = *(ObjectRef*)(file->m_data + pField->m_offset);
	String pathstr = GetString(path);

//	WCHAR* buffer = (WCHAR*)alloca((pathstr->Length()+1)*sizeof(WCHAR));
//	wcscpy_s(buffer, pathstr->Length()+1, pathstr->begin());

	DWORD fa = GetFileAttributesW(CStringw(pathstr).c_str());
	if (fa == 0xFFFFFFFF)
		return 0;

    /* Constants for simple boolean attributes */
	/*
    public static final int BA_EXISTS    = 0x01;
    public static final int BA_REGULAR   = 0x02;
    public static final int BA_DIRECTORY = 0x04;
    public static final int BA_HIDDEN    = 0x08;
*/
	jint ba = 0x01;

	if (fa & FILE_ATTRIBUTE_DIRECTORY)
		ba |= 0x04;
	else
		ba |= 0x02;	// ???

	if (fa & FILE_ATTRIBUTE_HIDDEN) ba |= 0x08;

	return ba;
}

// returns a string
ObjectRef __stdcall java_io_Win32FileSystem_canonicalize0(JNINativeInterface* env, ObjectRef self, ObjectRef path)
{
	String pathstr = GetString(path);

	return path;
}

void __stdcall FileDescriptor_initIDs(JNINativeInterface* env, JavaClass* cls)
{
	// ???
	LOG("");
}

void __stdcall FileDescriptor_set(JNINativeInterface* env, JavaClass* cls, int fd)
{
	LOG("");
}

/*
jobject __stdcall java_util_Properties_initProperties(JNIEnv* env, jclass cls, jobject props)
{
	return NULL;
}
*/

/*
void __stdcall System_init(JNIEnv* env, jclass cls, jobject in, jobject out, jobject err)
{
	JavaClass* pClass = (JavaClass*)((JavaObject*)cls)->m_private0;

//	env->m_p->LoadClass("java/lang/System
	*(jobject*)(pClass->m_staticData + pClass->GetFieldByName(ASTR("in"))->m_offset) = in;
	*(jobject*)(pClass->m_staticData + pClass->GetFieldByName(ASTR("out"))->m_offset) = out;
	*(jobject*)(pClass->m_staticData + pClass->GetFieldByName(ASTR("err"))->m_offset) = err;
}
*/

/**
* System properties. The following properties are guaranteed to be defined:
* <dl>
* <dt>java.version		<dd>Java version number
* <dt>java.vendor		<dd>Java vendor specific string
* <dt>java.vendor.url	<dd>Java vendor URL
* <dt>java.home		<dd>Java installation directory
* <dt>java.class.version	<dd>Java class version number
* <dt>java.class.path	<dd>Java classpath
* <dt>os.name		<dd>Operating System Name
* <dt>os.arch		<dd>Operating System Architecture
* <dt>os.version		<dd>Operating System Version
* <dt>file.separator	<dd>File separator ("/" on Unix)
* <dt>path.separator	<dd>Path separator (":" on Unix)
* <dt>line.separator	<dd>Line separator ("\n" on Unix)
* <dt>user.name		<dd>User account name
* <dt>user.home		<dd>User home directory
* <dt>user.dir		<dd>User's current working directory
* </dl>
*/

ObjectRef __stdcall System_initProperties(JNINativeInterface* env, jclass cls, ObjectRef props)
{
	jmethodID setPropertyID = env->GetMethodID(env->GetObjectClass(props), "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
//	jmethodID setPropertyID = env->GetMethodID(env->GetObjectClass(props), "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

	WCHAR username[512];
	DWORD nchars = 511;
	GetUserNameW(username, &nchars);

	WCHAR homedir[512];
	wcscpy_s(homedir, L"C:\\mmstudio\\users\\Sigurd Lerstad");

	env->CallObjectMethod(props, setPropertyID, env->NewString(L"java.version"), env->NewString(L"1.6.0"));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"java.vendor"), env->NewString(L"Sigurd Lerstad - Java virtual machine"));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"java.vendor.url"), env->NewString(L"http://www.lerstad.com"));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"os.name"), env->NewString(L"Windows"));
	//env->CallObjectMethod(props, setPropertyID, env->NewString(L"os.version"), env->NewString(L"Windows"));

	env->CallObjectMethod(props, setPropertyID, env->NewString(L"file.separator"), env->NewString(L"\\"));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"file.encoding"), env->NewString(L"Unicode"));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"path.separator"), env->NewString(L","));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"line.separator"), env->NewString(L"\r\n"));
//	env->CallObjectMethod(props, setPropertyID, env->NewString(L"file.encoding.pkg", 17), env->NewString(L"sun.io", 6));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"user.name"), env->NewString(username));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"user.home"), env->NewString(homedir));
	env->CallObjectMethod(props, setPropertyID, env->NewString(L"user.dir"), env->NewString(homedir));	// ??

	env->CallObjectMethod(props, setPropertyID, env->NewString(L"java.library.path"), env->NewString(L"C:\\mmstudio\\win32\\bin\\debug"));	// ??

//	

	/*
	jmethodID getPropertyID = env->GetMethodID(env->GetObjectClass(props), "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
	jobject ob = env->CallObjectMethod(props, getPropertyID, env->NewString(L"key", 3));
	*/

	return props;
}

ObjectRef __stdcall Class_forName(JNIEnv* env, jclass cls, ObjectRef rclassName)
{
	JNINativeInterface* penv = (JNINativeInterface*)env;

	String className = GetString(rclassName);

	JavaClass* pClass = penv->m_pThread->LoadClass(className);

	return pClass->GetObject();//->m_pClass;

	/*
	//penv->m_p->m_threads[0]->LoadClass();

	JavaClass* pClassClass = penv->m_p->LoadClass("java/lang/Class");

	JavaObject* pClassObj = pClassClass->CreateInstance();
	*/

	//return pClassObj;
}

ObjectRef __stdcall java_lang_Class_forName0(JNINativeInterface* env, JavaClass* pClass, ObjectRef rclassName, jboolean initialize, ObjectRef classloader)
{
	// TODO initalize, classloader

	String className = GetString(rclassName);

	JavaClass* pClass2 = env->m_pThread->LoadClass(className);

	if (pClass2)
		return pClass2->GetObject();
	else
		return NULL;
}

ObjectRef __stdcall java_lang_Class_getPrimitiveClass(JNIEnv* env, JavaClass* pClass, ObjectRef _name)
{
	VERIFY(_name != NULL);
	String name = GetString(_name);

	if (name == L"boolean")
	{
		return pBooleanClass->GetObject();
	}
	else if (name == L"int")
	{
		return pIntClass->GetObject();
	}
	else if (name == L"float")
	{
		return pFloatClass->GetObject();
	}
	else if (name == L"double")
	{
		return pDoubleClass->GetObject();
	}
	else
	{
		ASSERT(0);
		return NULL;
	}
}

ObjectRef __stdcall java_lang_Class_newInstance(JNIEnv* env, ObjectRef self)
{
	JNINativeInterface* penv = (JNINativeInterface*)env;

	JavaClass* pClass = GetJavaClass(self);
	return pClass->CreateInstance();
}

jint __stdcall java_lang_Object_hashCode(JNINativeInterface* env, ObjectRef self)
{
	return (jint)self.m_object;
}

ObjectRef __stdcall java_lang_Object_getClass(JNINativeInterface* env, ObjectRef self)
{
	return self->m_pClass->GetObject();
}

ObjectRef __stdcall java_lang_Object_clone(JNINativeInterface* env, ObjectRef self)
{
	// TODO, call interface Cloneable ??

	ObjectRef p = self->m_pClass->CreateInstance();

	if (self->m_pClass->m_pArrayOf)
	{
		int length = GetArrayLength(self);
		GetArrayFields(p)->m_length = length;
		GetArrayFields(p)->m_data = new uint8[self->m_pClass->m_pArrayOf->m_baseTypeSize*length];

		memcpy(GetArrayData(p), GetArrayData(self), self->m_pClass->m_pArrayOf->m_baseTypeSize*length);
	}
	else
	{
		memcpy(p->m_data, self->m_data, self->m_pClass->m_instanceFieldSize);
	}
	return p;
}

#if 0
jint __stdcall String_hashCode(JNIEnv* env, jobject self)
{
	ASSERT(*((JavaObject*)self)->m_pClass->GetName() == "java/lang/String");

	StringW* string = GetString((JavaObject*)self);

	jint hash = string->c_str()[0] +
					string->c_str()[1 % string->Length()]*64 +
					string->c_str()[2 % string->Length()]*64*64 +
					string->c_str()[3 % string->Length()]*64*64*64;

	return hash;
}

jboolean __stdcall String_equalsIgnoreCase(JNIEnv* env, jstring self, jstring other)
{
	StringW* str1 = GetString((JavaObject*)self);
	StringW* str2 = GetString((JavaObject*)other);

	return str1->CompareNoCase(str2) == 0;
}

jboolean __stdcall String_equalsObject(JNIEnv* env, ObjectRef self, ObjectRef other)
{
	if (*((JavaObject*)other)->m_pClass->GetName() == "java/lang/String")
	{
		StringW* str1 = GetString((JavaObject*)self);
		StringW* str2 = GetString((JavaObject*)other);

		return *str1 == *str2;
	}
	else
	{
		return self == other;
	}
}
#endif

jobject __stdcall StringBuffer_appendString(JNIEnv* env, jobject self, jobject rstring)
{
	ASSERT(0);
	return NULL;
#if 0

	JavaField* pField;
	
	pField = ((JavaObject*)self)->m_pClass->GetFieldByName(ASTR("count"));
	jint* pCount = (jint*)(((JavaObject*)self)->m_data + pField->m_offset);

	pField = ((JavaObject*)self)->m_pClass->GetFieldByName(ASTR("value"));
	ObjectRef pValue = *(ObjectRef*)(((JavaObject*)self)->m_data + pField->m_offset);

	if (rstring)
	{
		StringW* string = GetString((JavaObject*)rstring);

		jchar* newdata = new jchar[*pCount + string->Length()];
		memcpy(newdata, pValue->m_data, *pCount * sizeof jchar);
		memcpy(newdata + *pCount, string->c_str(), string->Length()*sizeof jchar);

		pValue->m_data = (uint8*)newdata;
		pValue->m_count += string->Length();

		*pCount = *pCount + string->Length();
	}

	return self;
#endif
}

jfloat __stdcall Float_intBitsToFloat(JNIEnv* env, jclass cls, jint bits)
{
	jfloat f = *(jfloat*)&bits;
	return f;
}

jint __stdcall Float_floatToIntBits(JNIEnv* env, jclass cls, jfloat f)
{
	jint bits = *(jint*)&f;
	return bits;
}

jdouble __stdcall Double_longBitsToDouble(JNIEnv* env, jclass cls, jlong bits)
{
	jdouble d = *(jdouble*)&bits;
	return d;
}

jlong __stdcall Double_doubleToLongBits(JNIEnv* env, jclass cls, jdouble d)
{
	jlong bits = *(jlong*)&d;
	return bits;
}

void __stdcall Object_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	pClass->GetMethodShallow("hashCode()I")->m_nativeFunc = java_lang_Object_hashCode;
	pClass->GetMethodShallow("getClass()Ljava/lang/Class;")->m_nativeFunc = java_lang_Object_getClass;
	pClass->GetMethodShallow("clone()Ljava/lang/Object;")->m_nativeFunc = java_lang_Object_clone;
}

JavaObject* JProcess::StringIntern(JavaObject* stringref)
{
	string_data<WCHAR> strdata = GetStringData(stringref);

	pair<map<string_data<WCHAR>, JavaObject*>::iterator, bool> result = m_strings.insert(map<string_data<WCHAR>, JavaObject*>::value_type(strdata, stringref));
	return result.first->second;
}

ObjectRef __stdcall java_lang_String_intern(JNINativeInterface* env, ObjectRef self)
{
	return env->m_pThread->m_vm->StringIntern(self);
}

#if 0
void __stdcall String_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	ASSERT(0);
	MessageBeep(-1);
	//pClass->m_nativeFuncs["hashCode()I"] = Object_hashCode;
}
#endif

void __stdcall ClassLoader_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	LOG("ClassLoader_registerNatives\n");
}

void __stdcall java_lang_ClassLoader_NativeLibrary_load(JNINativeInterface* env, ObjectRef self, ObjectRef str)
{
	JProcess* vm = env->m_pThread->m_vm;

	JavaField* pFromClassField = self->m_pClass->GetFieldByName("fromClass");
	ObjectRef fromClass = *(ObjectRef*)(self->m_data + pFromClassField->m_offset);

	String pathstr = GetString(str);

	HINSTANCE hInstance = LoadLibraryW(CStringw(pathstr));

	hInstance = (HINSTANCE)1000;	// TODO, remove

	*(jlong*)(self->m_data + self->m_pClass->GetField("handle")->m_offset) = (jlong)hInstance;

	if (false)
	{
		//JavaField* pSystemNativeLibrariesField = self->m_pClass->GetFieldByName(&StringA(true, "fromClass"));
		ObjectRef systemNativeLibraries = *(ObjectRef*)(vm->m_pClassLoaderClass->m_staticData + vm->m_pClassLoaderClass->GetField("systemNativeLibraries")->m_offset);

		JavaMethod* pAddMethod = systemNativeLibraries->m_pClass->GetMethodByName("add(Ljava/lang/Object;)Z");

		env->CallBooleanMethod(systemNativeLibraries, (jmethodID)pAddMethod, self);
	}
}

/*
void __stdcall Float_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	pClass->GetMethodShallow(&StringA(true, "intBitsToFloat(I)F"))->m_nativeFunc = Float_intBitsToFloat;
	pClass->GetMethodShallow(&StringA(true, "floatToIntBits(F)I"))->m_nativeFunc = Float_floatToIntBits;
}

void __stdcall Double_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	pClass->GetMethodShallow(&StringA(true, "longBitsToDouble(J)D"))->m_nativeFunc = Double_longBitsToDouble;
	pClass->GetMethodShallow(&StringA(true, "doubleToLongBits(D)J"))->m_nativeFunc = Double_doubleToLongBits;
}
*/

ObjectRef __stdcall Reflection_getCallerClass(JNINativeInterface* penv, JavaClass* cls, jint n)
{
	//JNINativeInterface* penv = (JNINativeInterface*)env;

	//LOG("Reflection_getCallerClass\n");
	if (n < 0)
	{
		THROW(-1);
		return NULL;
	}

	if (n == 0)
	{
		return cls->m_p;	// sun/reflect/Reflection
	}
	--n;

	Frame* pFrame = penv->m_pThread->m_pFrame;

	while (n--)
	{
		pFrame = pFrame->m_pCaller;

		if (pFrame == NULL)
		{
			throw(exception("Reflection.getCallerClass: Too far up the stack"));
		}
	}

	ASSERT(pFrame->m_pMethod);
	return pFrame->m_pMethod->m_pOwnerClass->m_p;
}

jint __stdcall Reflection_getClassAccessFlags(JNINativeInterface* env, jclass cls, ObjectRef clazz)
{
	return 0;
	// ??
//	return ((JavaClass*)clazz)->m_access_flags;
//	return 0;
}

bool __stdcall java_lang_Class_isInterface(JNINativeInterface* env, ObjectRef self)
{
	return (GetJavaClass(self)->m_access_flags >> ACC_INTERFACE_BIT) & 1;
}

int __stdcall java_lang_Class_getModifiers(JNINativeInterface* env, ObjectRef self)
{
// public, protected, private, final, static, abstract and interface

	return GetJavaClass(self)->m_access_flags & (ACC_PUBLIC | ACC_PROTECTED | ACC_PRIVATE | ACC_FINAL | ACC_STATIC | ACC_ABSTRACT | ACC_INTERFACE);
}

ObjectRef __stdcall java_lang_Class_getClassLoader0(JNIEnv* env, ObjectRef self)
{
	return NULL;
}

jboolean __stdcall java_lang_Class_desiredAssertionStatus0(JNIEnv* env, jclass cls, ObjectRef object)
{
	return 0;
}

// Return String
ObjectRef __stdcall java_lang_Class_getName0(JNINativeInterface* env, ObjectRef self)
{
	JavaClass* pClass = GetJavaClass(self);
	return pClass->m_pool_array[pClass->m_pool_array[pClass->m_this_class-1].classData.name_index-1].GetString(env->m_pThread);
}

ObjectRef __stdcall java_lang_Class_getSuperclass(JNINativeInterface* env, ObjectRef self)
{
	if (GetJavaClass(self)->m_pSuperClass)
		return GetJavaClass(self)->m_pSuperClass->m_p;
	else
		return NULL;
}

// Returns array of fields
ObjectRef __stdcall java_lang_Class_getDeclaredFields0(JNINativeInterface* env, ObjectRef self, bool recurse/*??*/)
{
	JavaClass* pClass = GetJavaClass(self);

	JavaClass* pFieldClassType = env->m_pThread->LoadClass("java/lang/reflect/Field");
//	ASSERT(pFieldClassType->m_pClass);

	//GetField

	JavaClass* pFieldArrayClass = GetArrayClass("[Ljava/lang/reflect/Field;", pFieldClassType, env->m_pThread->m_vm);

	JavaObject** arraydata = new JavaObject*[pClass->m_fields_count];

	ArrayRef* ref = pFieldArrayClass->CreateInstance();//new ArrayRef;
	//ref->m_pClass = pFieldArrayClass;
	GetArrayFields(ref)->m_length = 0;
	{
		JavaClass* p = pClass;
		do
		{
			GetArrayFields(ref)->m_length += p->m_fields_count;
			p = p->GetSuperClass();
		}
		while (p);
	}

	GetArrayFields(ref)->m_data = (uint8*)arraydata;//(uint8*)pClass->m_fields;
	//ref->baseType = -1;	// TODO

	if (true)	// TODO, shouldn't be done here
	{
		int n = 0;
		do
		{
			for (int i = 0; i < pClass->m_fields_count; i++)
			{
				JavaField* pField = pClass->m_fields[i];

				if (pField->m_p == NULL)
				{
					ObjectRef fieldref = pFieldClassType->CreateInstance();
					fieldref->m_private0 = pField;

					JavaField* pRootField = fieldref->m_pClass->GetFieldByName("root");
					*(ObjectRef*)(fieldref->m_data + pRootField->m_offset) = NULL;//fieldref;	// Points to itself

					JavaField* pNameField = fieldref->m_pClass->GetFieldByName("name");
					*(ObjectRef*)(fieldref->m_data + pNameField->m_offset) = pClass->m_pool_array[pField->m_name_index-1].GetString(env->m_pThread);

					JavaField* pClazzField = fieldref->m_pClass->GetFieldByName("clazz");
					*(ObjectRef*)(fieldref->m_data + pClazzField->m_offset) = pField->m_pOwnerClass->GetObject();

					JavaField* pSignatureField = fieldref->m_pClass->GetFieldByName("signature");	// String
					*(ObjectRef*)(fieldref->m_data + pSignatureField->m_offset) = pField->m_pOwnerClass->m_pool_array[pField->m_descriptor_index-1].GetString(env->m_pThread);

					JavaField* pTypeField = fieldref->m_pClass->GetFieldByName("type");
					*(ObjectRef*)(fieldref->m_data + pTypeField->m_offset) = GetClass(pField->m_pType, env->m_pThread)->GetObject();

					JavaField* pModifierField = fieldref->m_pClass->GetFieldByName("modifiers");
					*(int*)(fieldref->m_data + pModifierField->m_offset) = pField->m_access_flags;	// ??

					pField->m_p = fieldref;
				}
				arraydata[n++] = pField->m_p;

			//	pClass->m_fields[i]->m_pClass = pFieldClassType;
			}

			pClass = pClass->GetSuperClass();
		}
		while (pClass);
	}

	return ref;
}

// Return array of java/lang/reflect/Constructor
ObjectRef __stdcall java_lang_Class_getDeclaredConstructors0(JNINativeInterface* env, ObjectRef self,  bool publicOnly)
{
	JavaClass* pClass = GetJavaClass(self);

	JavaClass* pConstructorClassType = env->m_pThread->LoadClass("java/lang/reflect/Constructor");

	JavaClass* pConstructorClassArrayType = GetArrayClass("[Ljava/lang/reflect/Constructor;", pConstructorClassType, env->m_pThread->m_vm);

	int count = 0;
	{
		for (int i = 0; i < pClass->m_methods_count; i++)
		{
			JavaMethod* pMethod = pClass->m_methods[i];

			if (pMethod->GetName() == "<init>")
			{
				if (!publicOnly || pMethod->m_access_flags & ACC_PUBLIC)
				{
					count++;
				}
			}
		}
	}

	JavaObject** arraydata = new JavaObject*[count];

	ArrayRef* ref = pConstructorClassArrayType->CreateInstance();//new ArrayRef;
	//ref->m_pClass = pConstructorClassArrayType;
	GetArrayFields(ref)->m_length = count;
	GetArrayFields(ref)->m_data = (uint8*)arraydata;//(uint8*)pClass->m_fields;
	//ref->baseType = -1;	// TODO

	int n = 0;
	for (int i = 0; i < pClass->m_methods_count; i++)
	{
		JavaMethod* pMethod = pClass->m_methods[i];

		if (pMethod->GetName() == "<init>")
		{
			if (!publicOnly || pMethod->m_access_flags & ACC_PUBLIC)
			{
				if (pMethod->m_p == NULL)
				{
					JavaObject* ctor = pConstructorClassType->CreateInstance();

					/* TODO
		 private int			slot;
		 private Class[]		parameterTypes;
		 private Class[]		exceptionTypes;
		 */

					JavaField* pRootField = ctor->m_pClass->GetFieldByName("root");
					*(ObjectRef*)(ctor->m_data + pRootField->m_offset) = NULL;//ctor;	// Points to itself

					JavaField* pClazzField = ctor->m_pClass->GetFieldByName("clazz");
					*(ObjectRef*)(ctor->m_data + pClazzField->m_offset) = pMethod->m_pOwnerClass->GetObject();

					JavaField* pSignatureField = ctor->m_pClass->GetFieldByName("signature");	// String
					*(ObjectRef*)(ctor->m_data + pSignatureField->m_offset) = pMethod->m_pOwnerClass->m_pool_array[pMethod->m_descriptor_index-1].GetString(env->m_pThread);

					JavaField* pModifierField = ctor->m_pClass->GetFieldByName("modifiers");
					*(int*)(ctor->m_data + pModifierField->m_offset) = pMethod->m_access_flags;	// ??

					{
						String className = "[Ljava/lang/Class;";
						JavaClass* pArrayClass = GetArrayClass(className, env->m_pThread->m_vm->m_pClassClass, env->m_pThread->m_vm);//LoadClass(className);
						/*if (pArrayClass == NULL)
						{
							pArrayClass = new JavaClass;
							pArrayClass->m_name = className;
							pArrayClass->m_pSuperClass = env->m_pThread->LoadClass(&StringA(true, "java/lang/Object"));
							//pClassArray->m_pArrayOf = 
							pArrayClass->m_instanceFieldSize = sizeof(ArrayFields);
							env->m_pThread->m_vm->m_classes[className] = pArrayClass;
						}
						*/

						ObjectRef parameterTypes = pArrayClass->CreateInstance();
						GetArrayFields(parameterTypes)->m_length = pMethod->m_argumentTypes.size();
						GetArrayFields(parameterTypes)->m_data = (uint8*)new JavaObject*[GetArrayFields(parameterTypes)->m_length];
						for (int i = 0; i < GetArrayFields(parameterTypes)->m_length; i++)
						{
							((JavaObject**)parameterTypes->m_data)[i] = GetClass(pMethod->m_argumentTypes[i], env->m_pThread)->GetObject();
						}

						JavaField* pParameterTypesField = ctor->m_pClass->GetFieldByName("parameterTypes");
						*(ObjectRef*)(ctor->m_data + pParameterTypesField->m_offset) = parameterTypes;
					}

					pMethod->m_p = ctor;
					ctor->m_private0 = pMethod;
				}

				arraydata[n++] = pMethod->m_p;
			}
		}
	}

	return ref;
}

void __stdcall Class_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	LOG("Class_registerNatives\n");

	pClass->GetMethodShallow("getSuperclass()Ljava/lang/Class;")->m_nativeFunc = java_lang_Class_getSuperclass;
	pClass->GetMethodShallow("getClassLoader0()Ljava/lang/ClassLoader;")->m_nativeFunc = java_lang_Class_getClassLoader0;
	//pClass->GetMethodShallow("forName(Ljava/lang/String;)Ljava/lang/Class;"))->m_nativeFunc = Class_forName;
	pClass->GetMethodShallow("forName0(Ljava/lang/String;ZLjava/lang/ClassLoader;)Ljava/lang/Class;")->m_nativeFunc = java_lang_Class_forName0;
	pClass->GetMethodShallow("getPrimitiveClass(Ljava/lang/String;)Ljava/lang/Class;")->m_nativeFunc = java_lang_Class_getPrimitiveClass;
	pClass->GetMethodShallow("newInstance()Ljava/lang/Object;")->m_nativeFunc = java_lang_Class_newInstance;
	pClass->GetMethodShallow("desiredAssertionStatus0(Ljava/lang/Class;)Z")->m_nativeFunc = java_lang_Class_desiredAssertionStatus0;
	pClass->GetMethodShallow("getDeclaredFields0(Z)[Ljava/lang/reflect/Field;")->m_nativeFunc = java_lang_Class_getDeclaredFields0;
	pClass->GetMethodShallow("getDeclaredConstructors0(Z)[Ljava/lang/reflect/Constructor;")->m_nativeFunc = java_lang_Class_getDeclaredConstructors0;
	pClass->GetMethodShallow("getName0()Ljava/lang/String;")->m_nativeFunc = java_lang_Class_getName0;
	pClass->GetMethodShallow("isInterface()Z")->m_nativeFunc = java_lang_Class_isInterface;
	pClass->GetMethodShallow("getModifiers()I")->m_nativeFunc = java_lang_Class_getModifiers;
}

void __stdcall System_setIn0(JNIEnv* env, JavaClass* pClass, ObjectRef in)
{
//	JavaClass* pClass = GetJavaClass(cls);
	JavaField* pField = pClass->GetFieldByName("in");
	*(JavaObject**)(pClass->m_staticData + pField->m_offset) = in;
}

void __stdcall System_setOut0(JNIEnv* env, JavaClass* pClass, ObjectRef out)
{
//	JavaClass* pClass = GetJavaClass(cls);
	JavaField* pField = pClass->GetFieldByName("out");
	*(JavaObject**)(pClass->m_staticData + pField->m_offset) = out;
}

void __stdcall System_setErr0(JNIEnv* env, JavaClass* pClass, ObjectRef err)
{
//	JavaClass* pClass = GetJavaClass(cls);
	JavaField* pField = pClass->GetFieldByName("err");
	*(JavaObject**)(pClass->m_staticData + pField->m_offset) = err;
}

jlong __stdcall sun_io_Win32ErrorMode_setErrorMode(JNINativeInterface* env, JavaClass* cls, jlong mode)
{
	return 0;
}

ObjectRef __stdcall sun_reflect_NativeConstructorAccessorImpl_newInstance0(JNINativeInterface* env, JavaClass* cls, ObjectRef ctor, ObjectRef objectsArray)
{
	JavaClass* pConstructorClassType = ctor->m_pClass;
	ASSERT(pConstructorClassType->m_name == "java/lang/reflect/Constructor");

	JavaField* pRootField = ctor->m_pClass->GetFieldByName("root");
	while (*(ObjectRef*)(ctor->m_data + pRootField->m_offset) != NULL)
	{
		ctor = *(ObjectRef*)(ctor->m_data + pRootField->m_offset);
	}

	JavaMethod* pMethod = (JavaMethod*)ctor->m_private0;

	int count = (objectsArray == NULL)? 0: GetArrayLength(objectsArray);

	ObjectRef obj = pMethod->m_pOwnerClass->CreateInstance();

	CodeAttribute* pCode = pMethod->GetCode();

//	uint8 return_op = 177;
//	Frame* pCaller = new Frame;
//	pCaller->pc = &return_op;

	Frame* pCaller = env->m_pThread->m_pFrame;
	Frame* pFrame = new Frame(pMethod, pCode, pCaller, env->m_pThread->m_pc);
//	pFrame->m_pCaller = pCaller;

	int n = 1;
	pFrame->m_localVariables[0] = obj;
	for (int i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
	{
		JavaObject* objarg = ((JavaObject**)GetArrayData(objectsArray))[i];
		Type* type = pMethod->m_argumentTypes[i];
		if (type->kind == Type::Type_ref)
		{
			pFrame->m_localVariables[n] = ObjectRef(objarg);
			n++;
		}
		else if (type->kind == Type::BaseType_int)
		{
			ASSERT(0);
			pFrame->m_localVariables[n] = 0;//va_arg(args, jint);
			n++;
		}
		else if (type->kind == Type::BaseType_float)
		{
			ASSERT(0);
			*(float*)&pFrame->m_localVariables[n] = 0;//(float)va_arg(args, jfloat);
			n++;
		}
		else
			ASSERT(0);
	}

//	Frame* oldframe = m_pThread->m_pFrame;
	env->m_pThread->m_pFrame = pFrame;
	env->m_pThread->m_pc = pCode->code;
	//thread->m_vm = m_pThread->m_vm;
	LOG("{\n");

	do
	{
		env->m_pThread->next_instruction();
	}
	while (env->m_pThread->m_pFrame != pCaller);

	return obj;
}

ObjectRef __stdcall AccessController_doPrivileged(JNINativeInterface* env, JavaClass* cls, ObjectRef privilegedAction)
{
//	StringA classname = privilegedAction->m_pClass->GetName();
//	JavaObject* p

//	return NULL;
	jmethodID runID = env->GetMethodID(env->GetObjectClass(privilegedAction), "run", "()Ljava/lang/Object;");

	ObjectRef obj = (JavaObject*)env->CallObjectMethod(privilegedAction, runID);
	if (obj == NULL)
	{
		MessageBeep(-1);
	}
//	ASSERT(obj);
	return obj;
}

/*
void __stdcall ObjectStreamClass_initNative(JNIEnv* env, jclass cls)
{
	LOG("ObjectStreamClass_initNative\n");
}
*/

void __stdcall FileInputStream_initIDs(JNIEnv* env, jclass cls)
{
	LOG("FileInputStream_initIDs\n");
}

/*
void __stdcall FileInputStream_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	pClass->m_nativeFuncs["initIDs()V"] = FileInputStream_initIDs;
}
*/

void __stdcall java_io_FileOutputStream_initIDs(JNIEnv* env, jclass cls)
{
	LOG("FileInputStream_initIDs\n");
}

void __stdcall java_io_FileOutputStream_writeBytes(JNIEnv* env, ObjectRef self, ObjectRef bytesArray, jint offset, jint count)
{
	uint16* chars = (uint16*)GetArrayData(bytesArray);

#if 0
	MSWindows::DWORD nWritten;
//	MSWindows::WriteFile(MSWindows::GetStdHandle(STD_OUTPUT_HANDLE), bytes + offset, count, &nWritten, NULL);
	MSWindows::WriteConsoleW(MSWindows::GetStdHandle(STD_OUTPUT_HANDLE), bytes + offset, count, &nWritten, NULL);
#endif
}

/*
void __stdcall FileOutputStream_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	pClass->m_nativeFuncs["initIDs()V"] = FileOutputStream_initIDs;
}
*/

ObjectRef __stdcall Thread_currentThread(JNINativeInterface* env, jclass cls)
{
	return env->m_pThread->m_p;
}

jboolean __stdcall Thread_isAlive(JNIEnv* env, ObjectRef self)
{
	return 0;//((JNINativeInterface*)env)->m_pThread->m_p;
}

void __stdcall Thread_start(JNIEnv* env, ObjectRef self)
{
	// TODO ??

	// do something here

	// isalive = true
}

void __stdcall Thread_setPriority0(JNIEnv* env, ObjectRef self, int priority)
{
	MessageBeep(-1);
}

void __stdcall Thread_start0(JNIEnv* env, ObjectRef self)
{
	MessageBeep(-1);
}

void __stdcall Thread_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	LOG("Thread_registerNatives\n");

	for (int i = 0; i < pClass->m_fields_count; i++)
	{
		DebugTrace(pClass->m_fields[i]->GetName() << "\n");
	}

	pClass->GetMethodShallow("currentThread()Ljava/lang/Thread;")->m_nativeFunc = Thread_currentThread;
	pClass->GetMethodShallow("isAlive()Z")->m_nativeFunc = Thread_isAlive;
	pClass->GetMethodShallow("start()V")->m_nativeFunc = Thread_start;

	pClass->GetMethodShallow("setPriority0(I)V")->m_nativeFunc = Thread_setPriority0;
	pClass->GetMethodShallow("start0()V")->m_nativeFunc = Thread_start0;
}

jint __stdcall sun_misc_Signal_findSignal(JNINativeInterface* env, JavaClass* pClass, ObjectRef name)
{
	String namestr = GetString(name);

	return 0;
}

jlong __stdcall sun_misc_Signal_handle0(JNINativeInterface* env, JavaClass* pClass, jint signal, jlong value)
{
	return 0;
}

void __stdcall sun_misc_VM_initialize(JNINativeInterface* env, JavaClass* pClass)
{
	// ??
	MessageBeep(-1);
}

int64 __stdcall sun_misc_Unsafe_allocateMemory(JNINativeInterface* env, ObjectRef self, int64 size)
{
	if (size < 0)
	{
		VERIFY(0);
	}

	return (int64)new uint8[(size_t)size];
}

void __stdcall sun_misc_Unsafe_freeMemory(JNINativeInterface* env, ObjectRef self, int64 memory)
{
	delete [] (uint8*)memory;
}

void __stdcall sun_misc_Unsafe_putLong(JNINativeInterface* env, ObjectRef self, int64 address, int64 value)
{
	*(int64*)address = value;
}

int8 __stdcall sun_misc_Unsafe_getByte(JNINativeInterface* env, ObjectRef self, int64 address)
{
	return *(int8*)address;
}

int64 __stdcall sun_misc_Unsafe_objectFieldOffset(JNINativeInterface* env, ObjectRef self, ObjectRef fieldref)
{
	JavaField* pRootField = fieldref->m_pClass->GetFieldByName("root");

	ObjectRef root = *(ObjectRef*)(fieldref->m_data + pRootField->m_offset);
	return ((JavaField*)root->m_private0)->m_offset;
}

bool __stdcall sun_misc_Unsafe_compareAndSwapInt(JNINativeInterface* env, ObjectRef self, ObjectRef objectref, jlong offset, jint expect, jint update)
{
	jint* p = (jint*)(objectref->m_data + offset);

	// TODO, do this atomically with some asm code
	if (*p == expect)
	{
		*p = update;
		return true;
	}
	else
	{
		return false;
	}
}

void __stdcall sun_misc_Unsafe_ensureClassInitialized(JNINativeInterface* env, ObjectRef self, ObjectRef classref)
{
	LOG("");
}

void __stdcall sun_misc_Unsafe_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	LOG("sun_misc_Unsafe_registerNatives\n");

	pClass->GetMethodShallow("objectFieldOffset(Ljava/lang/reflect/Field;)J")->m_nativeFunc = sun_misc_Unsafe_objectFieldOffset;
	pClass->GetMethodShallow("compareAndSwapInt(Ljava/lang/Object;JII)Z")->m_nativeFunc = sun_misc_Unsafe_compareAndSwapInt;
	pClass->GetMethodShallow("allocateMemory(J)J")->m_nativeFunc = sun_misc_Unsafe_allocateMemory;
	pClass->GetMethodShallow("freeMemory(J)V")->m_nativeFunc = sun_misc_Unsafe_freeMemory;
	pClass->GetMethodShallow("putLong(JJ)V")->m_nativeFunc = sun_misc_Unsafe_putLong;
	pClass->GetMethodShallow("getByte(J)B")->m_nativeFunc = sun_misc_Unsafe_getByte;
	pClass->GetMethodShallow("ensureClassInitialized(Ljava/lang/Class;)V")->m_nativeFunc = sun_misc_Unsafe_ensureClassInitialized;
}

void __stdcall System_arraycopy(JNIEnv* env, JavaClass* cls, ObjectRef src, int srcPos, ObjectRef dest, int destPos, int length)
{
	ASSERT(GetClass(src) == GetClass(dest));

	int elemSize = GetClass(src)->m_pArrayOf->m_baseTypeSize;
	/*
	switch (src->baseType)
	{
	case ArrayType_BOOLEAN:
	case ArrayType_BYTE:
		elemSize = 1;
		break;

	case ArrayType_CHAR:
	case ArrayType_SHORT:
		elemSize = 2;
		break;

	case ArrayType_INT:
	case ArrayType_FLOAT:
		elemSize = 4;
		break;

	case ArrayType_LONG:
	case ArrayType_DOUBLE:
		elemSize = 8;
		break;

	default:
		elemSize = 4;
	}
	*/

	// memmove automatically handles dest and source overlapping arrays
	memmove(GetArrayData(dest) + destPos*elemSize, GetArrayData(src) + srcPos*elemSize, length*elemSize);
}

void __stdcall System_registerNatives(JNIEnv* env, JavaClass* pClass)
{
	pClass->GetMethodShallow("currentTimeMillis()J")->m_nativeFunc = System_currentTimeMillis;
//	pClass->GetMethodShallow("init(Ljava/io/InputStream;Ljava/io/PrintStream;Ljava/io/PrintStream;)V")->m_nativeFunc = System_init;
	pClass->GetMethodShallow("initProperties(Ljava/util/Properties;)Ljava/util/Properties;")->m_nativeFunc = System_initProperties;
	pClass->GetMethodShallow("setIn0(Ljava/io/InputStream;)V")->m_nativeFunc = System_setIn0;
	pClass->GetMethodShallow("setOut0(Ljava/io/PrintStream;)V")->m_nativeFunc = System_setOut0;
	pClass->GetMethodShallow("setErr0(Ljava/io/PrintStream;)V")->m_nativeFunc = System_setErr0;
	pClass->GetMethodShallow("arraycopy(Ljava/lang/Object;ILjava/lang/Object;II)V")->m_nativeFunc = System_arraycopy;
	pClass->GetMethodShallow("mapLibraryName(Ljava/lang/String;)Ljava/lang/String;")->m_nativeFunc = System_mapLibraryName;
}

// Returns a java/security/AccessControlContext object
ObjectRef __stdcall AccessController_getStackAccessControlContext(JNINativeInterface* env, JavaClass* pClass)
{
	//JavaClass* pClass = (JavaClass*)cls;

	JavaClass* pContextClass = env->m_pThread->LoadClass("java/security/AccessControlContext");

	return NULL;	// only privileged code
}

ObjectRef __stdcall Throwable_fillInStackTrace(JNIEnv* env, ObjectRef self)
{
	// TODO, maybe set "backtrace" field to something
	return self;
}

Thread::Thread()
{
	m_pFrame = NULL;
	m_p = NULL;
	m_pc = NULL;

	m_jni = new JNINativeInterface;
	m_jni->m_pThread = this;

}

JProcess::JProcess()
{
	m_flags = 0;
	m_pHost = NULL;

	m_registerNatives["java/lang/Object"] = Object_registerNatives;
	m_registerNatives["java/lang/System"] = System_registerNatives;
	m_registerNatives["java/lang/Class"] = Class_registerNatives;
	m_registerNatives["java/lang/ClassLoader"] = ClassLoader_registerNatives;
	m_registerNatives["java/lang/Thread"] = Thread_registerNatives;
	m_registerNatives["sun/misc/Unsafe"] = sun_misc_Unsafe_registerNatives;
	//m_registerNatives["java/lang/String"] = String_registerNatives;

//	m_registerNatives["java/lang/Float"] = Float_registerNatives;
//	m_registerNatives["java/lang/Double"] = Double_registerNatives;

//	m_registerNatives["java/security/AccessController"] = AccessController_registerNatives;
//	m_registerNatives["java/security/ObjectStreamClass"] = ObjectStreamClass_registerNatives;

//	m_registerNatives["java/io/FileInputStream"] = FileInputStream_registerNatives;
//	m_registerNatives["java/io/FileOutputStream"] = FileOutputStream_registerNatives;

#if 0
	m_nativeFuncs["java/lang/ObjectregisterNatives()V"] = Object_registerNatives;
	m_nativeFuncs["java/lang/ObjecthashCode()I"] = Object_hashCode;

	m_nativeFuncs["java/lang/SystemregisterNatives()V"] = System_registerNatives;
	m_nativeFuncs["java/lang/SystemcurrentTimeMillis()J"] = System_currentTimeMillis;
	m_nativeFuncs["java/lang/Systeminit(Ljava/io/InputStream;Ljava/io/PrintStream;Ljava/io/PrintStream;)V"] = System_init;
	m_nativeFuncs["java/lang/SysteminitProperties(Ljava/util/Properties;)Ljava/util/Properties;"] = System_initProperties;
	m_nativeFuncs["java/lang/SystemsetIn0(Ljava/io/InputStream;)V"] = System_setIn0;
	m_nativeFuncs["java/lang/SystemsetOut0(Ljava/io/OutputStream;)V"] = System_setOut0;
	m_nativeFuncs["java/lang/SystemsetErr0(Ljava/io/OutputStream;)V"] = System_setErr0;
	m_nativeFuncs["java/lang/Systemarraycopy(Ljava/lang/Object;ILjava/lang/Object;II)V"] = System_arraycopy;

	m_nativeFuncs["java/lang/ClassregisterNatives()V"] = Class_registerNatives;
	m_nativeFuncs["java/lang/ClassgetClassLoader0()Ljava/lang/ClassLoader;"] = Class_getClassLoader0;
	m_nativeFuncs["java/lang/ClassforName(Ljava/lang/String;)Ljava/lang/Class;"] = Class_forName;
	m_nativeFuncs["java/lang/ClassforName0(Ljava/lang/String;ZLjava/lang/ClassLoader;)Ljava/lang/Class;"] = Class_forName0;
	m_nativeFuncs["java/lang/ClassgetPrimitiveClass(Ljava/lang/String;)Ljava/lang/Class;"] = Class_getPrimitiveClass;
	m_nativeFuncs["java/lang/ClassnewInstance()Ljava/lang/Object;"] = Class_newInstance;
	m_nativeFuncs["java/lang/ClassdesiredAssertionStatus0(Ljava/lang/Class;)Z"] = java_lang_Class_desiredAssertionStatus0;

	m_nativeFuncs["java/lang/ClassLoaderregisterNatives()V"] = ClassLoader_registerNatives;

	m_nativeFuncs["java/lang/ThreadregisterNatives()V"] = Thread_registerNatives;
	m_nativeFuncs["java/lang/ThreadcurrentThread()Ljava/lang/Thread;"] = Thread_currentThread;
	m_nativeFuncs["java/lang/ThreadisAlive()Z"] = Thread_isAlive;
	m_nativeFuncs["java/lang/Threadstart()V"] = Thread_start;

	m_nativeFuncs["java/lang/StringhashCode()I"] = String_hashCode;
//	m_nativeFuncs["java/lang/Stringequals(Ljava/lang/Object;)Z"] = String_equalsObject;
//	m_nativeFuncs["java/lang/StringequalsIgnoreCase(Ljava/lang/String;)Z"] = String_equalsIgnoreCase;
//	m_nativeFuncs["java/lang/StringBufferappend(Ljava/lang/String;)Ljava/lang/StringBuffer;"] = StringBuffer_appendString;

	m_nativeFuncs["java/lang/FloatintBitsToFloat(I)F"] = Float_intBitsToFloat;
	m_nativeFuncs["java/lang/FloatfloatToIntBits(F)I"] = Float_floatToIntBits;
	m_nativeFuncs["java/lang/DoublelongBitsToDouble(J)D"] = Double_longBitsToDouble;
	m_nativeFuncs["java/lang/DoubledoubleToLongBits(D)J"] = Double_doubleToLongBits;

	m_nativeFuncs["java/security/AccessControllerdoPrivileged(Ljava/security/PrivilegedAction;)Ljava/lang/Object;"] = AccessController_doPrivileged;
	m_nativeFuncs["java/security/AccessControllergetStackAccessControlContext()Ljava/security/AccessControlContext;"] = AccessController_getStackAccessControlContext;

	m_nativeFuncs["java/io/ObjectStreamClassinitNative()V"] = ObjectStreamClass_initNative;
	m_nativeFuncs["java/io/FileInputStreaminitIDs()V"] = FileInputStream_initIDs;
	m_nativeFuncs["java/io/FileOutputStreaminitIDs()V"] = FileOutputStream_initIDs;

	m_nativeFuncs["java/io/FileDescriptorinitSystemFD(Ljava/io/FileDescriptor;I)Ljava/io/FileDescriptor;"] = System_initSystemFD;
	m_nativeFuncs["java/io/FileDescriptorinitIDs()V"] = FileDescriptor_initIDs;

	m_nativeFuncs["java/lang/ThrowablefillInStackTrace()Ljava/lang/Throwable;"] = Throwable_fillInStackTrace;

	m_nativeFuncs["sun/reflect/ReflectiongetCallerClass(I)Ljava/lang/Class;"] = Reflection_getCallerClass;
#endif
}

void JProcess::Init()
{
//	ASSERT(0);
	fplog = fopen("C:\\jvm_log.txt", "w");

	m_pClassClass = NULL;	// Must have this first

	m_pClassClass = m_threads[0]->LoadClass("java/lang/Class");
	VERIFY(m_pClassClass);

	m_pObjectClass = m_threads[0]->LoadClass("java/lang/Object");
	VERIFY(m_pObjectClass);

	m_pClassLoaderClass = m_threads[0]->LoadClass("java/lang/ClassLoader");
	VERIFY(m_pClassLoaderClass);

	m_pCloneableClass = m_threads[0]->LoadClass("java/lang/Cloneable");
	VERIFY(m_pCloneableClass);

	m_pStringClass = m_threads[0]->LoadClass("java/lang/String");
	VERIFY(m_pStringClass);

	pBooleanClass->m_p = m_pClassClass->CreateInstance();
	pCharClass->m_p = m_pClassClass->CreateInstance();
	pByteClass->m_p = m_pClassClass->CreateInstance();
	pShortClass->m_p = m_pClassClass->CreateInstance();
	pIntClass->m_p = m_pClassClass->CreateInstance();
	pLongClass->m_p = m_pClassClass->CreateInstance();
	pFloatClass->m_p = m_pClassClass->CreateInstance();
	pDoubleClass->m_p = m_pClassClass->CreateInstance();

	pBooleanArrayClass = GetArrayClass("[Z", pBooleanClass, this);
	pCharArrayClass = GetArrayClass("[C", pCharClass, this);
	pByteArrayClass = GetArrayClass("[B", pByteClass, this);
	pShortArrayClass = GetArrayClass("[S", pShortClass, this);
	pIntArrayClass = GetArrayClass("[I", pIntClass, this);
	pLongArrayClass = GetArrayClass("[J", pLongClass, this);
	pFloatArrayClass = GetArrayClass("[F", pFloatClass, this);
	pDoubleArrayClass = GetArrayClass("[D", pDoubleClass, this);

//	m_threads[0]->LoadClass("sun/nio/cs/ext/ExtendedCharsets");
}

ZIP::Archive* archive = NULL;

JavaClass* Thread::LoadClass(StringIn className2)
{
	char* cstr = CString(className2).Detach();
	char* p = cstr;
	while (*p)
	{
		if (*p == '.') *p = '/';
		++p;
	}

	String className(cstr);

//
	//className = className.ReplaceChar('.', '/');

	/*
	if (strstr(className->c_str(), "ClassLoader"))
	{
		MessageBeep(-1);
	}
	*/

	/*
	if (className == "java/lang/reflect/AccessibleObject")
	{
		MessageBeep(-1);
	}
	*/

	LOG("LoadClass: %s\n", CString(className).c_str());

	JavaClass* pJavaClass;
	pJavaClass = m_vm->m_classes[className];
	if (pJavaClass)
		return pJavaClass;

	if (className.LeftOf(1) == "[") // vector
	{
		ASSERT(0);
#if 0
		if (className->GetData()[1] == 'B')
		{
			JavaClass* pClass = new JavaClass;
			pClass->m_pClass = m_vm->m_pClassClass;
			pClass->m_name = className;
			pClass->m_pSuperClass = LoadClass(&StringA(true, "java/lang/Object"));
			pClass->m_instanceFieldSize = sizeof(ArrayFields);
			pClass->m_pArrayOf = pByteClass;
			m_vm->m_classes[className] = pClass;
			return pClass;
		}
		else
			ASSERT(0);
#endif
	}

	{
		pJavaClass = new JavaClass;

		try
		{
			/*
			StringBuilder str;
			str << *className << ".class";
			*/

			char buffer[1024];
			sprintf_s(buffer, "c:/mmstudio/%s.class", CString(className).c_str());
			IO::FileStream stream(buffer, IO::FileMode_Open, IO::FileAccess_Read);
			if (stream.IsHandleValid())
			{
				pJavaClass->Parse(&stream);
			}
			else
			{
				if (archive == NULL)
				{
					IO::FileStream* file = new IO::FileStream("C:\\Program Files (x86)\\Java\\jdk1.6.0_17\\jre\\lib\\rt.jar", IO::FileMode_Open, IO::FileAccess_Read);
					VERIFY(file->IsHandleValid());

					archive = new ZIP::Archive;
					//archive->Open(new FileByteStream("C:\\WINDOWS\\Java\\Packages\\MCL3RDBV.ZIP"));
				//	archive->Open(new FileByteStream(ASTR("C:\\Program Files\\Java\\j2re1.4.2_05\\lib\\rt.jar")));
				//	archive->Open(new FileByteStream(ASTR("C:\\Program Files\\Java\\jre1.6.0_06\\lib\\rt.jar")));
					archive->Open(file);
				}

				char buffer[1024];
				sprintf(buffer, "%s.class", CString(className).c_str());
				ZIP::File* pFile = archive->FindFile(buffer);
				if (pFile)
				{
					_Ptr<IO::Stream> stream = pFile->GetStream();

					int ret = pJavaClass->Parse(stream);
					ASSERT(ret == 0);

				//	pStream->Release();
				}
				else
				{
					return NULL;
				}
			}
		}
		catch (Exception* e)
		{
			ASSERT(0);
		}

		if (pJavaClass)
		{
			map<String, JProcess::RegisterNativesFunc>::iterator it = m_vm->m_registerNatives.find(pJavaClass->GetName());
			if (it != m_vm->m_registerNatives.end())
			{
				pJavaClass->GetMethodShallow("registerNatives()V")->m_nativeFunc = (*it).second;
			}
			else if (pJavaClass->GetName() == "java/lang/ClassLoader$NativeLibrary")
			{
				pJavaClass->GetMethodShallow("load(Ljava/lang/String;)V")->m_nativeFunc = java_lang_ClassLoader_NativeLibrary_load;
			}
			else if (pJavaClass->GetName() == "java/lang/String")
			{
				pJavaClass->GetMethodShallow("intern()Ljava/lang/String;")->m_nativeFunc = java_lang_String_intern;
			}
			else if (pJavaClass->GetName() == "sun/io/Win32ErrorMode")
			{
				pJavaClass->GetMethodShallow("setErrorMode(J)J")->m_nativeFunc = sun_io_Win32ErrorMode_setErrorMode;
			}
			else if (pJavaClass->GetName() == "java/io/FileInputStream")
			{
				pJavaClass->GetMethodShallow("initIDs()V")->m_nativeFunc = FileInputStream_initIDs;
			}
			else if (pJavaClass->GetName() == "java/io/FileOutputStream")
			{
				pJavaClass->GetMethodShallow("initIDs()V")->m_nativeFunc = java_io_FileOutputStream_initIDs;
				pJavaClass->GetMethodShallow("writeBytes([BII)V")->m_nativeFunc = java_io_FileOutputStream_writeBytes;
			}
			else if (pJavaClass->GetName() == "java/io/FileDescriptor")
			{
				pJavaClass->GetMethodShallow("initIDs()V")->m_nativeFunc = FileDescriptor_initIDs;
				pJavaClass->GetMethodShallow("set(I)J")->m_nativeFunc = FileDescriptor_set;
			}
			else if (pJavaClass->GetName() == "java/lang/Float")
			{
				pJavaClass->GetMethodShallow("intBitsToFloat(I)F")->m_nativeFunc = Float_intBitsToFloat;
				pJavaClass->GetMethodShallow("floatToIntBits(F)I")->m_nativeFunc = Float_floatToIntBits;
				pJavaClass->GetMethodShallow("floatToRawIntBits(F)I")->m_nativeFunc = Float_floatToIntBits;

		//		pJavaClass->GetMethodShallow(&StringA(true, "initIDs()V"))->m_nativeFunc = FileOutputStream_initIDs;
			}
			else if (pJavaClass->GetName() == "java/lang/Double")
			{
				pJavaClass->GetMethodShallow("longBitsToDouble(J)D")->m_nativeFunc = Double_longBitsToDouble;
				pJavaClass->GetMethodShallow("doubleToLongBits(D)J")->m_nativeFunc = Double_doubleToLongBits;
				pJavaClass->GetMethodShallow("doubleToRawLongBits(D)J")->m_nativeFunc = Double_doubleToLongBits;
			}
			else if (pJavaClass->GetName() == "java/io/FileSystem")
			{
				pJavaClass->GetMethodShallow("getFileSystem()Ljava/io/FileSystem;")->m_nativeFunc = java_io_FileSystem_getFileSystem;
			}
			else if (pJavaClass->GetName() == "java/io/Win32FileSystem")
			{
				pJavaClass->GetMethodShallow("initIDs()V")->m_nativeFunc = java_io_Win32FileSystem_initIDs;
				pJavaClass->GetMethodShallow("getBooleanAttributes(Ljava/io/File;)I")->m_nativeFunc = java_io_Win32FileSystem_getBooleanAttributes;
				pJavaClass->GetMethodShallow("canonicalize0(Ljava/lang/String;)Ljava/lang/String;")->m_nativeFunc = java_io_Win32FileSystem_canonicalize0;
			}
			else if (pJavaClass->GetName() == "sun/reflect/Reflection")
			{
				pJavaClass->GetMethodShallow("getCallerClass(I)Ljava/lang/Class;")->m_nativeFunc = Reflection_getCallerClass;
				pJavaClass->GetMethodShallow("getClassAccessFlags(Ljava/lang/Class;)I")->m_nativeFunc = Reflection_getClassAccessFlags;
			}
			else if (pJavaClass->GetName() == "java/lang/Throwable")
			{
				pJavaClass->GetMethodShallow("fillInStackTrace()Ljava/lang/Throwable;")->m_nativeFunc = java_lang_Throwable_fillInStackTrace;
			}
			else if (pJavaClass->GetName() == "java/lang/NoSuchFieldException")	// TODO just Exception
			{
				pJavaClass->GetMethodShallow("fillInStackTrace()Ljava/lang/Throwable;")->m_nativeFunc = java_lang_Exception_fillInStackTrace;
			}
			else if (pJavaClass->GetName() == "java/security/AccessController")
			{
				pJavaClass->GetMethodShallow("doPrivileged(Ljava/security/PrivilegedAction;)Ljava/lang/Object;")->m_nativeFunc = AccessController_doPrivileged;
				pJavaClass->GetMethodShallow("getStackAccessControlContext()Ljava/security/AccessControlContext;")->m_nativeFunc = AccessController_getStackAccessControlContext;
			}
			else if (pJavaClass->GetName() == "sun/reflect/NativeConstructorAccessorImpl")
			{
				//pJavaClass->GetMethodShallow(&StringA(true, "newInstance0(Ljava/lang/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;"))->m_nativeFunc = sun_reflect_NativeConstructorAccessorImpl_newInstance0;
				pJavaClass->GetMethodShallow("newInstance0(Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;")->m_nativeFunc = sun_reflect_NativeConstructorAccessorImpl_newInstance0;

			}
			else if (pJavaClass->GetName() == "sun/misc/VM")
			{
				pJavaClass->GetMethodShallow("initialize()V")->m_nativeFunc = sun_misc_VM_initialize;
			}
			else if (pJavaClass->GetName() == "sun/misc/Signal")
			{
				pJavaClass->GetMethodShallow("findSignal(Ljava/lang/String;)I")->m_nativeFunc = sun_misc_Signal_findSignal;
				pJavaClass->GetMethodShallow("handle0(IJ)J")->m_nativeFunc = sun_misc_Signal_handle0;
			}
			else if (pJavaClass->GetName() == "java/util/Properties")
			{
			//	pJavaClass->GetMethodShallow(&StringA(true, "initProperties(Ljava/util/Properties;)Ljava/util/Properties;"))->m_nativeFunc = java_util_Properties_initProperties;

				MessageBeep(-1);
			//	pJavaClass->GetMethodShallow(&StringA(true, "longBitsToDouble(J)D"))->m_nativeFunc = Double_longBitsToDouble;
			//	pJavaClass->GetMethodShallow(&StringA(true, "doubleToLongBits(D)J"))->m_nativeFunc = Double_doubleToLongBits;
			}

			m_vm->m_classes[className] = pJavaClass;

			if (m_vm->m_pClassClass)
			{
#if 0
				pJavaClass->m_pClass = m_vm->m_pClassClass;
#endif

				pJavaClass->m_p = m_vm->m_pClassClass->CreateInstance();
				pJavaClass->m_p->m_private0 = pJavaClass;
			/*
				//JavaField* pField = pJavaClass->m_pClass->m_pClass->GetFieldByName("internal");
				//StringA n = pJavaClass->m_pClass->m_pClass->GetName();
				//ASSERT(pField);

				//*(jint*)(pJavaClass->m_pClass->m_data + pField->m_offset) = (jint)pJavaClass;

				pJavaClass->m_pClass->m_private0 = pJavaClass;
			*/
			}

			if (m_vm->m_pClassClass == NULL)
			{
				ASSERT(pJavaClass->GetName() == "java/lang/Class");
				m_vm->m_pClassClass = pJavaClass;
				pJavaClass->m_p = m_vm->m_pClassClass->CreateInstance();//pJavaClass;
				pJavaClass->m_p->m_private0 = pJavaClass;

			//	JavaField* pField = pJavaClass->m_pClass->GetFieldByName(&StringA(true, "internal"));
			}

#if 0
			// Each class is also an instance of java/lang/Class
			pJavaClass->m_data = new uint8[256/*m_vm->m_pClassClass->m_instanceFieldSize*/];
			memset(pJavaClass->m_data, 0, 256/*m_vm->m_pClassClass->m_instanceFieldSize*/);
#endif

			pJavaClass->Initialize(this);

			/*
			if (*className == "java/io/BufferedInputStream")
			{
				MessageBeep(-1);
			}
			else
			*/
			{
				pJavaClass->InitializeStatics(this);
			}

			if (m_vm->m_pHost)
			{
				m_vm->m_pHost->OnLoadedClass(pJavaClass);
			}
		}
	}

	return pJavaClass;
}

jclass __stdcall JNINativeInterface::GetObjectClass(jobject obj)
{
	ASSERT(obj);
	return (jclass)((JavaObject*)obj)->m_pClass;//->m_pClass;
}

jmethodID __stdcall JNINativeInterface::GetMethodID(jclass cls, const char* name, const char* sig)
{
	JavaClass* pClass = (JavaClass*)cls;

	char buffer[512];
	sprintf(buffer, "%s%s", name, sig);

	return (jmethodID)pClass->GetMethodByName(buffer);

	// TODO, this is just a quick hack

#if 0

	JavaMethod* pMethod = ((JavaClass*)((JavaObject*)cls)->m_private0)->GetMethodByName(StringA(name) + StringA(sig));

	return (jmethodID)pMethod;
#endif
}

jfieldID __stdcall JNINativeInterface::GetFieldID(jclass cls, const char* name, const char* sig)
{
	JavaClass* pClass = (JavaClass*)cls;

	char buffer[512];
	sprintf(buffer, "%s%s", name, sig);

	return (jfieldID)pClass->GetFieldByName(buffer);

#if 0
	// TODO, this is just a quick hack

	JavaField* pField = ((JavaClass*)((JavaObject*)cls)->m_private0)->GetFieldByName(StringA(name) + StringA(sig));

	return (jfieldID)pField;
#endif
}

JavaObject* Thread::NewString(jchar* unicode, jsize len)
{
	string_data<WCHAR> strdata((WCHAR*)unicode, len);

	pair<map<string_data<WCHAR>, JavaObject*>::iterator, bool> result = m_vm->m_strings.insert(map<string_data<WCHAR>, JavaObject*>::value_type(strdata, NULL));
	if (!result.second)
	{
		ASSERT(result.first->second);
		return result.first->second;
	}
	else
	{
		ASSERT(result.first->second == NULL);

		JavaClass* pClass = m_vm->m_pStringClass;//LoadClass(ASTR("java/lang/String"));

		JavaObject* pString = pClass->CreateInstance();

		{
			JavaField* pField = pString->m_pClass->GetFieldByName("value");
			ObjectRef* pValue = (ObjectRef*)(pString->m_data + pField->m_offset);
			(*pValue) = pCharArrayClass->CreateInstance();
			GetArrayFields(*pValue)->m_data = (uint8*)new jchar[len];
			//(*pValue)->baseType = 5;	// char
			GetArrayFields(*pValue)->m_length = len;

			memcpy(GetArrayData(*pValue), unicode, len*sizeof jchar);
		}
		{
			JavaField* pField = pString->m_pClass->GetFieldByName("count");
			jint* pcount = (jint*)(pString->m_data + pField->m_offset);
			*pcount = len;
		}

		result.first->second = pString;

		return pString;
	}
}

jstring __stdcall JNINativeInterface::NewString(const jchar* unicode, jsize len)
{
	string_data<WCHAR> strdata(string_copy((WCHAR*)unicode, len));
	return NewString(strdata);
}

jstring JNINativeInterface::NewString(string_data<WCHAR> strdata)
{
	return (jstring)m_pThread->NewString((jchar*)strdata.data, strdata.len);
}

jstring JNINativeInterface::NewString(const WCHAR* cstr)
{
	return NewString(string_copy(cstr));
}

jsize __stdcall JNINativeInterface::GetStringLength(jstring str)
{
	return NULL;
}

const jchar* __stdcall JNINativeInterface::GetStringChars(jstring str, jboolean* isCopy)
{
	return NULL;
}

void __stdcall JNINativeInterface::ReleaseStringChars(jstring str, const jchar *chars)
{
}

void __stdcall JNINativeInterface::CallVoidMethod(jobject obj, jmethodID methodID, ...)
{
	va_list arg;
	va_start(arg, methodID);

	CallVoidMethodV(obj, methodID, arg);
}

void __stdcall JNINativeInterface::CallVoidMethodA(jobject obj, jmethodID methodID, const jvalue* args)
{
	CallVoidMethodV(obj, methodID, (char*)args);
}

jobject __stdcall JNINativeInterface::CallObjectMethod(jobject obj, jmethodID methodID, ...)
{
	va_list arg;
	va_start(arg, methodID);

	return CallObjectMethodV(obj, methodID, arg);
}

jobject __stdcall JNINativeInterface::CallObjectMethodA(jobject obj, jmethodID methodID, const jvalue* args)
{
	return CallObjectMethodV(obj, methodID, (char*)args);
}

jboolean __stdcall JNINativeInterface::CallBooleanMethod(jobject obj, jmethodID methodID, ...)
{
	va_list arg;
	va_start(arg, methodID);

	return CallBooleanMethodV(obj, methodID, arg);
}

jboolean __stdcall JNINativeInterface::CallBooleanMethodA(jobject obj, jmethodID methodID, const jvalue* args)
{
	VERIFY(0);
	return 0;
}

jint JNINativeInterface::CallStaticIntMethod(jclass cls, jmethodID methodID, ...)
{
	va_list arg;
	va_start(arg, methodID);
	return CallStaticIntMethodV(cls, methodID, arg);
}

jint JNINativeInterface::CallStaticIntMethodA(jclass cls, jmethodID methodID, const jvalue* args)
{
	ASSERT(0);
	return 0;
}

jint JNINativeInterface::CallStaticIntMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	JavaMethod* pMethod = (JavaMethod*)methodID;

	if (pMethod->m_pReturnType->kind != Type::BaseType_int)
	{
		raise(Exception());
	}

	CodeAttribute* pCode = pMethod->GetCode();

	JavaClass* pClass = (JavaClass*)clazz;

//	uint8 return_op = 177;
//	Frame* pCaller = new Frame;
//	pCaller->pc = &return_op;

	Frame* pCaller = m_pThread->m_pFrame;
	Frame* pFrame = new Frame(pMethod, pCode, pCaller, m_pThread->m_pc);
	//pFrame->m_pCaller = pCaller;

	int n = 0;
//	pFrame->m_localVariables[0] = (long)obj;
	for (size_t i = 0; i < pMethod->m_argumentTypes.GetSize(); ++i)
	{
		Type* type = pMethod->m_argumentTypes[i];
		if (type->kind == Type::Type_ref || type->kind == Type::Type_array)
		{
			pFrame->m_localVariables[n] = ObjectRef(va_arg(args, JavaObject*));
			n++;
		}
		else if (type->kind == Type::BaseType_int)
		{
			pFrame->m_localVariables[n] = va_arg(args, jint);
			n++;
		}
		else if (type->kind == Type::BaseType_float)
		{
			*(float*)&pFrame->m_localVariables[n] = (float)va_arg(args, jfloat);
			n++;
		}
		else
			ASSERT(0);
	}

//	Thread* thread = new Thread;
//	Frame* oldframe = m_pThread->m_pFrame;
	m_pThread->m_pFrame = pFrame;
	//thread->m_vm = m_pThread->m_vm;
	m_pThread->m_pc = pCode->code;

	LOG("{\n");

	do
	{
		m_pThread->next_instruction();
	}
	while (m_pThread->m_pFrame != pCaller);

	return pCaller->pop();
}

void JNINativeInterface::CallStaticVoidMethod(jclass cls, jmethodID methodID, ...)
{
	va_list arg;
	va_start(arg, methodID);
	CallStaticVoidMethodV(cls, methodID, arg);
}

void JNINativeInterface::CallStaticVoidMethodA(jclass cls, jmethodID methodID, const jvalue* args)
{
	ASSERT(0);
}

void JNINativeInterface::CallStaticVoidMethodV(jclass cls, jmethodID methodID, va_list args)
{
	JavaMethod* pMethod = (JavaMethod*)methodID;

	if (pMethod->m_pReturnType->kind != Type::ReturnType_void)
	{
		THROW(-1);
	}

	CodeAttribute* pCode = pMethod->GetCode();

	JavaClass* pClass = (JavaClass*)cls;

//	uint8 return_op = 177;
//	Frame* pCaller = new Frame;
//	pCaller->pc = &return_op;

	Frame* pCaller = m_pThread->m_pFrame;
	Frame* pFrame = new Frame(pMethod, pCode, pCaller, m_pThread->m_pc);
	//pFrame->m_pCaller = pCaller;

	int n = 0;
//	pFrame->m_localVariables[0] = (long)obj;
	for (int i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
	{
		Type* type = pMethod->m_argumentTypes[i];
		if (type->kind == Type::Type_ref)
		{
			pFrame->m_localVariables[n] = ObjectRef(va_arg(args, JavaObject*));
			n++;
		}
		else if (type->kind == Type::BaseType_int)
		{
			pFrame->m_localVariables[n] = va_arg(args, jint);
			n++;
		}
		else if (type->kind == Type::BaseType_float)
		{
			*(float*)&pFrame->m_localVariables[n] = (float)va_arg(args, jfloat);
			n++;
		}
		else
			ASSERT(0);
	}

//	Thread* thread = new Thread;
//	Frame* oldframe = m_pThread->m_pFrame;
	m_pThread->m_pFrame = pFrame;
	//thread->m_vm = m_pThread->m_vm;
	m_pThread->m_pc = pCode->code;

	LOG("{\n");

	do
	{
		m_pThread->next_instruction();
	}
	while (m_pThread->m_pFrame != pCaller);

//	m_pThread->m_pFrame = oldframe;
}

void __stdcall JNINativeInterface::CallVoidMethodV(jobject obj, jmethodID methodID, va_list args)
{
	JavaMethod* pMethod = (JavaMethod*)methodID;

	if (pMethod->m_pReturnType->kind != Type::ReturnType_void)
	{
		THROW(-1);
	}

	CodeAttribute* pCode = pMethod->GetCode();

//	uint8 return_op = 177;
//	Frame* pCaller = new Frame;
//	pCaller->pc = &return_op;

	Frame* pCaller = m_pThread->m_pFrame;
	Frame* pFrame = new Frame(pMethod, pCode, pCaller, m_pThread->m_pc);
//	pFrame->m_pCaller = pCaller;

	int n = 1;
	pFrame->m_localVariables[0] = ObjectRef((JavaObject*)obj);
	for (int i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
	{
		Type* type = pMethod->m_argumentTypes[i];
		if (type->kind == Type::Type_ref)
		{
			pFrame->m_localVariables[n] = ObjectRef(va_arg(args, JavaObject*));
			n++;
		}
		else if (type->kind == Type::BaseType_int)
		{
			pFrame->m_localVariables[n] = va_arg(args, jint);
			n++;
		}
		else if (type->kind == Type::BaseType_float)
		{
			*(float*)&pFrame->m_localVariables[n] = (float)va_arg(args, jfloat);
			n++;
		}
		else
			ASSERT(0);
	}

//	Frame* oldframe = m_pThread->m_pFrame;
	m_pThread->m_pFrame = pFrame;
	m_pThread->m_pc = pCode->code;
	//thread->m_vm = m_pThread->m_vm;
	LOG("{\n");

	do
	{
		m_pThread->next_instruction();
	}
	while (m_pThread->m_pFrame != pCaller);

//	m_pThread->m_pFrame = oldframe;
}

jboolean __stdcall JNINativeInterface::CallBooleanMethodV(jobject obj, jmethodID methodID, va_list args)
{
	JavaMethod* pMethod = (JavaMethod*)methodID;

	if (pMethod->m_pReturnType->kind != Type::BaseType_bool)
	{
		THROW(-1);
	}

	CodeAttribute* pCode = pMethod->GetCode();

	Frame* pCaller = new Frame;	// Make a fake Frame to support result
	pCaller->m_pCaller = m_pThread->m_pFrame;
	Frame* pFrame = new Frame(pMethod, pCode, pCaller, m_pThread->m_pc);
	//pFrame->m_pCaller = pCaller;

	int n = 1;
	pFrame->m_localVariables[0] = ObjectRef((JavaObject*)obj);
	for (int i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
	{
		Type* type = pMethod->m_argumentTypes[i];
		if (type->kind == Type::Type_ref)
		{
			pFrame->m_localVariables[n] = ObjectRef(va_arg(args, JavaObject*));
			n++;
		}
		else if (type->kind == Type::BaseType_int)
		{
			pFrame->m_localVariables[n] = va_arg(args, jint);
			n++;
		}
		else if (type->kind == Type::BaseType_float)
		{
			*(float*)&pFrame->m_localVariables[n] = (float)va_arg(args, jfloat);
			n++;
		}
		else
			ASSERT(0);
	}

//	Frame* oldframe = m_pThread->m_pFrame;
	m_pThread->m_pFrame = pFrame;
	m_pThread->m_pc = pCode->code;

	//thread->m_vm = m_pThread->m_vm;
	LOG("{\n");

	do
	{
		m_pThread->next_instruction();
	}
	while (m_pThread->m_pFrame != pCaller);

//	m_pThread->m_pFrame = oldframe;
	m_pThread->m_pFrame = pCaller->m_pCaller;

	bool result = pCaller->pop();

	return result;
}

jobject __stdcall JNINativeInterface::CallObjectMethodV(jobject obj, jmethodID methodID, va_list args)
{
	JavaMethod* pMethod = (JavaMethod*)methodID;

	if (pMethod->m_pReturnType->kind != Type::Type_ref)
	{
		THROW(-1);
	}

	CodeAttribute* pCode = pMethod->GetCode();

	Frame* pCaller = new Frame;	// Make a fake Frame to support result
	pCaller->m_pCaller = m_pThread->m_pFrame;
	Frame* pFrame = new Frame(pMethod, pCode, pCaller, m_pThread->m_pc);
	//pFrame->m_pCaller = pCaller;

	int n = 1;
	pFrame->m_localVariables[0] = ObjectRef((JavaObject*)obj);
	for (int i = 0; i < pMethod->m_argumentTypes.GetSize(); i++)
	{
		Type* type = pMethod->m_argumentTypes[i];
		if (type->kind == Type::Type_ref)
		{
			pFrame->m_localVariables[n] = ObjectRef(va_arg(args, JavaObject*));
			n++;
		}
		else if (type->kind == Type::BaseType_int)
		{
			pFrame->m_localVariables[n] = va_arg(args, jint);
			n++;
		}
		else if (type->kind == Type::BaseType_float)
		{
			*(float*)&pFrame->m_localVariables[n] = (float)va_arg(args, jfloat);
			n++;
		}
		else
			ASSERT(0);
	}

//	Frame* oldframe = m_pThread->m_pFrame;
	m_pThread->m_pFrame = pFrame;
	m_pThread->m_pc = pCode->code;

	//thread->m_vm = m_pThread->m_vm;
	LOG("{\n");

	do
	{
		m_pThread->next_instruction();
	}
	while (m_pThread->m_pFrame != pCaller);

//	m_pThread->m_pFrame = oldframe;
	m_pThread->m_pFrame = pCaller->m_pCaller;

	JavaObject* result = pCaller->pop();

	return (jobject)result;
}

jint JNICALL JNINativeInterface::GetVersion()
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jclass JNICALL JNINativeInterface::DefineClass(const char *name, jobject loader, const jbyte *buf, jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jclass JNICALL JNINativeInterface::FindClass(const char *name)
{
	JavaClass* pClass = m_pThread->LoadClass(name);

	return (jclass)(JavaObject*)pClass->GetObject();
}

// Converts a java.lang.reflect.Method or java.lang.reflect.Constructor object to a method ID.
jmethodID JNICALL JNINativeInterface::FromReflectedMethod(jobject method)
{
	// TODO, traverse root
	return (jmethodID)(JavaMethod*)((JavaObject*)method)->m_private0;
}

jfieldID JNICALL JNINativeInterface::FromReflectedField(jobject field)
{
	// TODO, traverse root
	return (jfieldID)(JavaField*)((JavaObject*)field)->m_private0;
}

jobject JNICALL JNINativeInterface::ToReflectedMethod(jclass cls, jmethodID methodID, jboolean isStatic)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jclass JNICALL JNINativeInterface::GetSuperclass(jclass sub)
{
	// Untested
	return (jclass)(jobject)((JavaClass*)sub)->GetSuperClass()->GetObject();
}

jboolean JNICALL JNINativeInterface::IsAssignableFrom(jclass sub, jclass sup)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::ToReflectedField(jclass cls, jfieldID fieldID, jboolean isStatic)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::Throw(jthrowable obj)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::ThrowNew(jclass clazz, const char *msg)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jthrowable JNICALL JNINativeInterface::ExceptionOccurred()
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::ExceptionDescribe()
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::ExceptionClear()
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::FatalError(const char *msg)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jint JNICALL JNINativeInterface::PushLocalFrame(jint capacity)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::PopLocalFrame(jobject result)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::NewGlobalRef(jobject lobj)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::DeleteGlobalRef(jobject gref)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::DeleteLocalRef(jobject obj)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jboolean JNICALL JNINativeInterface::IsSameObject(jobject obj1, jobject obj2)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::NewLocalRef(jobject ref)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::EnsureLocalCapacity(jint capacity)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

// Allocates a new Java object without invoking any of the constructors for the object. Returns a reference to the object. 
jobject JNICALL JNINativeInterface::AllocObject(jclass clazz)
{
	JavaClass* pClass = GetJavaClass((JavaObject*)clazz);

	return (jobject)pClass->CreateInstance();
}

jobject JNICALL JNINativeInterface::NewObject(jclass clazz, jmethodID method_ID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::NewObjectV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::NewObjectA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::IsInstanceOf(jobject obj, jclass clazz)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallByteMethod(jobject obj, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallByteMethodV(jobject obj, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallByteMethodA(jobject obj, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallCharMethod(jobject obj, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallCharMethodV(jobject obj, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallCharMethodA(jobject obj, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallShortMethod(jobject obj, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallShortMethodV(jobject obj, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallShortMethodA(jobject obj, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::CallIntMethod(jobject obj, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::CallIntMethodV(jobject obj, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::CallIntMethodA(jobject obj, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallLongMethod(jobject obj, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallLongMethodV(jobject obj, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallLongMethodA(jobject obj, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallFloatMethod(jobject obj, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallFloatMethodV(jobject obj, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallFloatMethodA(jobject obj, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallDoubleMethod(jobject obj, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallDoubleMethodV(jobject obj, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallDoubleMethodA(jobject obj, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::CallNonvirtualObjectMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::CallNonvirtualObjectMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::CallNonvirtualObjectMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue* args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::CallNonvirtualBooleanMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::CallNonvirtualBooleanMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::CallNonvirtualBooleanMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue * args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallNonvirtualByteMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallNonvirtualByteMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallNonvirtualByteMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallNonvirtualCharMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallNonvirtualCharMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallNonvirtualCharMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallNonvirtualShortMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallNonvirtualShortMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallNonvirtualShortMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::CallNonvirtualIntMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::CallNonvirtualIntMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::CallNonvirtualIntMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallNonvirtualLongMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallNonvirtualLongMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallNonvirtualLongMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallNonvirtualFloatMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallNonvirtualFloatMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallNonvirtualFloatMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallNonvirtualDoubleMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallNonvirtualDoubleMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallNonvirtualDoubleMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::CallNonvirtualVoidMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::CallNonvirtualVoidMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::CallNonvirtualVoidMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue * args)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jobject JNICALL JNINativeInterface::GetObjectField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::GetBooleanField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::GetByteField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::GetCharField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::GetShortField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::GetIntField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::GetLongField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::GetFloatField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::GetDoubleField(jobject obj, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::SetObjectField(jobject obj, jfieldID fieldID, jobject val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetBooleanField(jobject obj, jfieldID fieldID, jboolean val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetByteField(jobject obj, jfieldID fieldID, jbyte val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetCharField(jobject obj, jfieldID fieldID, jchar val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetShortField(jobject obj, jfieldID fieldID, jshort val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetIntField(jobject obj, jfieldID fieldID, jint val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetLongField(jobject obj, jfieldID fieldID, jlong val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetFloatField(jobject obj, jfieldID fieldID, jfloat val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetDoubleField(jobject obj, jfieldID fieldID, jdouble val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jmethodID JNICALL JNINativeInterface::GetStaticMethodID(jclass clazz, const char *name, const char *sig)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::CallStaticObjectMethod(jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::CallStaticObjectMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::CallStaticObjectMethodA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::CallStaticBooleanMethod(jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::CallStaticBooleanMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::CallStaticBooleanMethodA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallStaticByteMethod(jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallStaticByteMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::CallStaticByteMethodA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallStaticCharMethod(jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallStaticCharMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::CallStaticCharMethodA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallStaticShortMethod(jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallStaticShortMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::CallStaticShortMethodA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallStaticLongMethod(jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallStaticLongMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::CallStaticLongMethodA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallStaticFloatMethod(jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallStaticFloatMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::CallStaticFloatMethodA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallStaticDoubleMethod(jclass clazz, jmethodID methodID, ...)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallStaticDoubleMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::CallStaticDoubleMethodA(jclass clazz, jmethodID methodID, const jvalue *args)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfieldID JNICALL JNINativeInterface::GetStaticFieldID(jclass clazz, const char *name, const char *sig)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::GetStaticObjectField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean JNICALL JNINativeInterface::GetStaticBooleanField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte JNICALL JNINativeInterface::GetStaticByteField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar JNICALL JNINativeInterface::GetStaticCharField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort JNICALL JNINativeInterface::GetStaticShortField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::GetStaticIntField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::GetStaticLongField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat JNICALL JNINativeInterface::GetStaticFloatField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble JNICALL JNINativeInterface::GetStaticDoubleField(jclass clazz, jfieldID fieldID)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::SetStaticObjectField(jclass clazz, jfieldID fieldID, jobject value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetStaticBooleanField(jclass clazz, jfieldID fieldID, jboolean value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetStaticByteField(jclass clazz, jfieldID fieldID, jbyte value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetStaticCharField(jclass clazz, jfieldID fieldID, jchar value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetStaticShortField(jclass clazz, jfieldID fieldID, jshort value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetStaticIntField(jclass clazz, jfieldID fieldID, jint value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetStaticLongField(jclass clazz, jfieldID fieldID, jlong value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetStaticFloatField(jclass clazz, jfieldID fieldID, jfloat value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetStaticDoubleField(jclass clazz, jfieldID fieldID, jdouble value)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jstring JNICALL JNINativeInterface::NewStringUTF(const char *utf)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jsize JNICALL JNINativeInterface::GetStringUTFLength(jstring str)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

const char* JNICALL JNINativeInterface::GetStringUTFChars(jstring str, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::ReleaseStringUTFChars(jstring str, const char* chars)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jsize JNICALL JNINativeInterface::GetArrayLength(jarray _array)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobjectArray JNICALL JNINativeInterface::NewObjectArray(jsize len, jclass clazz, jobject init)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::GetObjectArrayElement(jobjectArray _array, jsize index)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::SetObjectArrayElement(jobjectArray _array, jsize index, jobject val)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jbooleanArray JNICALL JNINativeInterface::NewBooleanArray(jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyteArray JNICALL JNINativeInterface::NewByteArray(jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jcharArray JNICALL JNINativeInterface::NewCharArray(jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshortArray JNICALL JNINativeInterface::NewShortArray(jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jintArray JNICALL JNINativeInterface::NewIntArray(jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlongArray JNICALL JNINativeInterface::NewLongArray(jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloatArray JNICALL JNINativeInterface::NewFloatArray(jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdoubleArray JNICALL JNINativeInterface::NewDoubleArray(jsize len)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jboolean* JNICALL JNINativeInterface::GetBooleanArrayElements(jbooleanArray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jbyte* JNICALL JNINativeInterface::GetByteArrayElements(jbyteArray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jchar* JNICALL JNINativeInterface::GetCharArrayElements(jcharArray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jshort* JNICALL JNINativeInterface::GetShortArrayElements(jshortArray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint* JNICALL JNINativeInterface::GetIntArrayElements(jintArray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong* JNICALL JNINativeInterface::GetLongArrayElements(jlongArray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jfloat* JNICALL JNINativeInterface::GetFloatArrayElements(jfloatArray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jdouble* JNICALL JNINativeInterface::GetDoubleArrayElements(jdoubleArray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::ReleaseBooleanArrayElements(jbooleanArray _array, jboolean *elems, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::ReleaseByteArrayElements(jbyteArray _array, jbyte *elems, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::ReleaseCharArrayElements(jcharArray _array, jchar *elems, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::ReleaseShortArrayElements(jshortArray _array, jshort *elems, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::ReleaseIntArrayElements(jintArray _array, jint *elems, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::ReleaseLongArrayElements(jlongArray _array, jlong *elems, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::ReleaseFloatArrayElements(jfloatArray _array, jfloat *elems, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::ReleaseDoubleArrayElements(jdoubleArray _array, jdouble *elems, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetBooleanArrayRegion(jbooleanArray _array, jsize start, jsize l, jboolean *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetByteArrayRegion(jbyteArray _array, jsize start, jsize len, jbyte *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetCharArrayRegion(jcharArray _array, jsize start, jsize len, jchar *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetShortArrayRegion(jshortArray _array, jsize start, jsize len, jshort *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetIntArrayRegion(jintArray _array, jsize start, jsize len, jint *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetLongArrayRegion(jlongArray _array, jsize start, jsize len, jlong *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetFloatArrayRegion(jfloatArray _array, jsize start, jsize len, jfloat *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetDoubleArrayRegion(jdoubleArray _array, jsize start, jsize len, jdouble *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetBooleanArrayRegion(jbooleanArray _array, jsize start, jsize l, const jboolean *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetByteArrayRegion(jbyteArray _array, jsize start, jsize len, const jbyte *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetCharArrayRegion(jcharArray _array, jsize start, jsize len, const jchar *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetShortArrayRegion(jshortArray _array, jsize start, jsize len, const jshort *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetIntArrayRegion(jintArray _array, jsize start, jsize len, const jint *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetLongArrayRegion(jlongArray _array, jsize start, jsize len, const jlong *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetFloatArrayRegion(jfloatArray _array, jsize start, jsize len, const jfloat *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::SetDoubleArrayRegion(jdoubleArray _array, jsize start, jsize len, const jdouble *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jint JNICALL JNINativeInterface::RegisterNatives(jclass clazz, const JNINativeMethod *methods, jint nMethods)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::UnregisterNatives(jclass clazz)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::MonitorEnter(jobject obj)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::MonitorExit(jobject obj)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jint JNICALL JNINativeInterface::GetJavaVM(void/*JavaVM*/ **vm)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::GetStringRegion(jstring str, jsize start, jsize len, jchar *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void JNICALL JNINativeInterface::GetStringUTFRegion(jstring str, jsize start, jsize len, char *buf)
{
	TRACE("TODO\n");
	ASSERT(0);
}

void* JNICALL JNINativeInterface::GetPrimitiveArrayCritical(jarray _array, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::ReleasePrimitiveArrayCritical(jarray _array, void *carray, jint mode)
{
	TRACE("TODO\n");
	ASSERT(0);
}

const jchar* JNICALL JNINativeInterface::GetStringCritical(jstring string, jboolean *isCopy)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::ReleaseStringCritical(jstring string, const jchar *cstring)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jweak JNICALL JNINativeInterface::NewWeakGlobalRef(jobject obj)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void JNICALL JNINativeInterface::DeleteWeakGlobalRef(jweak ref)
{
	TRACE("TODO\n");
	ASSERT(0);
}

jboolean JNICALL JNINativeInterface::ExceptionCheck()
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jobject JNICALL JNINativeInterface::NewDirectByteBuffer(void* address, jlong capacity)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

void* JNICALL JNINativeInterface::GetDirectBufferAddress(jobject buf)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

jlong JNICALL JNINativeInterface::GetDirectBufferCapacity(jobject buf)
{
	TRACE("TODO\n");
	ASSERT(0);
	return 0;
}

}	// JavaVM
}	// System
