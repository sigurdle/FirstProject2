#include "stdafx.h"
#include "LDebugger.h"
#include "javadisasm.h"

namespace System
{

namespace javavm
{
javavmext extern char* JavaOpcodeNames[256];
}

namespace java
{
using namespace javavm;

uint16 javavmContext::getword()
{
	// Big endian
	uint8 byte1 = *pc++;
	uint8 byte2 = *pc++;
	return (byte1 << 8) | byte2;
}

//typedef int (*jop_func)(javavmContext* c);


javainstr* javavmContext::jop_notimpl(const JavaClass* pJavaClass)
{
//	TRACE("\top not implemented");
	javainstr* p = new javainstr(*pc++);
//	ASSERT(0);
	return p;
}

javainstr* javavmContext::jop_nop(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_iconst_5(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_istore(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	uint8 index = *pc++;
	return p;
}

javainstr* javavmContext::jop_istore_1(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_aconst_null(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_dup(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_return(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_iload(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	uint8 index = *pc++;
	return p;
}

javainstr* javavmContext::jop_lload(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	uint8 index = *pc++;
	return p;
}

javainstr* javavmContext::jop_dload_0(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_dload_1(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_dload_2(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_dload_3(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_aload_0(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_aload_1(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_aload_2(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_aload_3(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_iaload(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_aaload(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_aastore(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	return p;
}

javainstr* javavmContext::jop_invokevirtual(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	p->u.methodIndex = getword();

	/*
	WORD classIndex = pJavaClass->m_pool_array[methodIndex-1].methodRef.class_index;
	WORD classNameIndex = pJavaClass->m_pool_array[classIndex-1].classData.name_index;
	_String* className = pJavaClass->m_pool_array[classNameIndex-1].str;

	WORD nameAndTypeIndex = pJavaClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
	WORD methodNameIndex = pJavaClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	_String* methodName = pJavaClass->m_pool_array[methodNameIndex-1].str;

	printf("%S::%S", className->c_str(), methodName->c_str());
	*/

	return p;
}

javainstr* javavmContext::jop_invokespecial(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	p->u.methodIndex = getword();

	/*
	WORD classIndex = pJavaClass->m_pool_array[methodIndex-1].methodRef.class_index;
	WORD classNameIndex = pJavaClass->m_pool_array[classIndex-1].classData.name_index;
	_String* className = pJavaClass->m_pool_array[classNameIndex-1].str;

	WORD nameAndTypeIndex = pJavaClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
	WORD methodNameIndex = pJavaClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	_String* methodName = pJavaClass->m_pool_array[methodNameIndex-1].str;

	printf("%S::%S", className->c_str(), methodName->c_str());
	*/

	return p;
}

javainstr* javavmContext::jop_invokestatic(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	p->u.methodIndex = getword();

	return p;
}

javainstr* javavmContext::jop_invokeinterface(const JavaClass* pJavaClass)
{
	javainstr* p = new javainstr(*pc++);
	p->u.methodIndex = getword();

	return p;
}

javainstr* javavmContext::jop_getstatic(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	p->u.fieldIndex = getword();
	return p;
}

javainstr* javavmContext::jop_putstatic(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	p->u.fieldIndex = getword();
	return p;
}

javainstr* javavmContext::jop_getfield(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	p->u.fieldIndex = getword();
	return p;
}

javainstr* javavmContext::jop_putfield(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	p->u.fieldIndex = getword();
	return p;
}

javainstr* javavmContext::jop_ldc(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	uint8 index = *pc++;
	return p;
}

javainstr* javavmContext::jop_ldc_w(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	uint16 index = getword();
	return p;
}

javainstr* javavmContext::jop_ldc2_w(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	uint16 index = getword();
	return p;
}

javainstr* javavmContext::jop_ret(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	uint8 index = *pc++;
	return p;
}

javainstr* javavmContext::jop_goto(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	short offset = getword();
	return p;
}

javainstr* javavmContext::jop_jsr(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	short offset = getword();
	return p;
}

javainstr* javavmContext::jop_new(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	p->u.classIndex = getword();
	return p;
}

javainstr* javavmContext::jop_newarray(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	uint8 atype = *pc++;
	return p;
}

javainstr* javavmContext::jop_anewarray(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	uint16 index = getword();
	return p;
}

javainstr* javavmContext::jop_if_icmp(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	short offset = getword();

#if 0
	printf("%4.4x", c->pc - c->code + offset);
#endif

	return p;
}

javainstr* javavmContext::jop_ifnull(const javavm::JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	short offset = getword();
	return p;
}

javainstr* javavmContext::jop_ifnonnull(const javavm::JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	short offset = getword();
	return p;
}

javainstr* javavmContext::jop_checkcast(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	uint16 index = getword();

	return p;
}

javainstr* javavmContext::jop_instanceof(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	uint16 index = getword();

	return p;
}

javainstr* javavmContext::jop_bipush(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);
	int int8 = *pc++;

	return p;
}

javainstr* javavmContext::jop_sipush(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);

	short int16 = getword();

	return p;
}

javainstr* javavmContext::jop_iinc(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);

	uint8 index = *pc++;
	signed char v = *pc++;

	return p;
}

javainstr* javavmContext::jop_tableswitch(const JavaClass* c)
{
	javainstr* p = new javainstr(*pc++);

//	pad bytes (align on 4 bytes)
	pc = (uint8*)(((long)pc+3) & ~3);

	long _default = getlong();
	long _low = getlong();
	long _high = getlong();

	pc += (_high-_low+1)<<2;

	return p;
}

javavmContext::tyfunc funcs[256] =
{
	&javavmContext::jop_nop,
	&javavmContext::jop_aconst_null,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_iconst_5,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_bipush,
	&javavmContext::jop_sipush,
	&javavmContext::jop_ldc,
	&javavmContext::jop_ldc_w,
	&javavmContext::jop_ldc2_w,	// 20
	&javavmContext::jop_iload,
	&javavmContext::jop_lload,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_dload_2,	// 40
	&javavmContext::jop_dload_3,
	&javavmContext::jop_aload_0,
	&javavmContext::jop_aload_1,
	&javavmContext::jop_aload_2,
	&javavmContext::jop_aload_3,
	&javavmContext::jop_iaload,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_aaload,	// 50
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_istore,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_istore_1,	// 60
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,	// 70
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,	// 80
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_aastore,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_dup,
	&javavmContext::jop_notimpl,	// 90
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,	// 100
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,	// 110
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,	// 120
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,	// 130
	&javavmContext::jop_notimpl,
	&javavmContext::jop_iinc,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,	// 140
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_if_icmp,
	&javavmContext::jop_if_icmp,
	&javavmContext::jop_if_icmp,
	&javavmContext::jop_if_icmp,
	&javavmContext::jop_if_icmp,
	&javavmContext::jop_if_icmp,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_goto,
	&javavmContext::jop_jsr,
	&javavmContext::jop_ret,
	&javavmContext::jop_tableswitch,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_return,
	&javavmContext::jop_getstatic,
	&javavmContext::jop_putstatic,
	&javavmContext::jop_getfield,
	&javavmContext::jop_putfield,
	&javavmContext::jop_invokevirtual,	// 182
	&javavmContext::jop_invokespecial,
	&javavmContext::jop_invokestatic,
	&javavmContext::jop_invokeinterface,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_new,
	&javavmContext::jop_newarray,
	&javavmContext::jop_anewarray,
	&javavmContext::jop_notimpl,	// 190
	&javavmContext::jop_notimpl,
	&javavmContext::jop_checkcast,
	&javavmContext::jop_instanceof,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_ifnull,
	&javavmContext::jop_ifnonnull,
	&javavmContext::jop_notimpl,	// 200
	&javavmContext::jop_notimpl,
/*
Reserved opcodes:

202 (0xca) breakpoint

254 (0xfe) impdep1

255 (0xff) impdep2
*/
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
	&javavmContext::jop_notimpl,
};

DebuggingExt javainstr* disasm_java(javavmContext* c, const JavaClass* pJavaClass)
{
	return (c->*funcs[*c->pc])(pJavaClass);
}

DebuggingExt StringA* toString(const JavaClass* pJavaClass, const javainstr* instr)
{
	BufferImp<char> buffer;
	StringBuilderA stream(&buffer);

	if (JavaOpcodeNames[instr->m_op])
		stream << JavaOpcodeNames[instr->m_op];
	else
		return NULL;

	stream << " ";

//	uint8* p = instr->m_p;
//	++p;

	switch (instr->m_op)
	{
	case JOP_new:
		{
			uint16 index = instr->u.classIndex;
			const CPoolItem& item = pJavaClass->m_pool_array[index-1];
			if (item.tag == CONSTANT_Class)
			{
				StringA* className = pJavaClass->m_pool_array[item.classData.name_index-1].utf8.str;

				stream << *className;
			}
		}
		break;

	case JOP_putfield:
	case JOP_getfield:
	case JOP_putstatic:
	case JOP_getstatic:
		{
			uint16 fieldIndex = instr->u.fieldIndex;

			uint16 classIndex = pJavaClass->m_pool_array[fieldIndex-1].fieldRef.class_index;
			uint16 classNameIndex = pJavaClass->m_pool_array[classIndex-1].classData.name_index;
			StringA* className = pJavaClass->m_pool_array[classNameIndex-1].utf8.str;

			uint16 nameAndTypeIndex = pJavaClass->m_pool_array[fieldIndex-1].fieldRef.name_and_type_index;
			uint16 fieldNameIndex = pJavaClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
			StringA* fieldName = pJavaClass->m_pool_array[fieldNameIndex-1].utf8.str;

			stream << *className << "::" << *fieldName;
		}
		break;

	case JOP_invokevirtual:
	case JOP_invokespecial:
	case JOP_invokestatic:
		{
			uint16 methodIndex = instr->u.methodIndex;

			uint16 classIndex = pJavaClass->m_pool_array[methodIndex-1].methodRef.class_index;
			uint16 classNameIndex = pJavaClass->m_pool_array[classIndex-1].classData.name_index;
			StringA* className = pJavaClass->m_pool_array[classNameIndex-1].utf8.str;

			uint16 nameAndTypeIndex = pJavaClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
			uint16 methodNameIndex = pJavaClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
			uint16 descriptorIndex = pJavaClass->m_pool_array[nameAndTypeIndex-1].nameAndType.descriptor_index;
			StringA* methodName = pJavaClass->m_pool_array[methodNameIndex-1].utf8.str;
			StringA* descriptor = pJavaClass->m_pool_array[descriptorIndex-1].utf8.str;

			stream << *className << "::" << *methodName << "::" << *descriptor;
		}
		break;

	default:
		;
	}

	return buffer.DetachToString();
}

}	// java
}	// System
