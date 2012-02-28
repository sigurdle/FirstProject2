#ifndef Java_Disasm_h
#define Java_Disasm_h

//#include "../LFC/disasm.h"
//#include "JavaClassFileLoader.h"

namespace System
{

namespace java
{

class DebuggingExt javainstr : public MInstruction
{
public:
	CTOR javainstr(uint8 op)
	{
		m_op = op;
	//	m_len = 0;
		//m_p = NULL;
	}
	uint8 m_op;
//	uint8 m_len;
//	uint8* m_p;
	union
	{
		uint16 classIndex;
		uint16 fieldIndex;
		uint16 methodIndex;
	}
	u;
};

class DebuggingExt javavmContext : public MContext
{
public:
	uint16 getword();

	inline long getlong()
	{
		long value = (*pc++)<<24;
		value |= (*pc++)<<16;
		value |= (*pc++)<<8;
		value |= (*pc++);
		return value;
	}

	typedef javainstr* (javavmContext::*tyfunc)(const javavm::JavaClass* c);

	static tyfunc funcs[256];

	javainstr* jop_notimpl(const javavm::JavaClass* c);
	javainstr* jop_iload(const javavm::JavaClass* pJavaClass);
	javainstr* jop_lload(const javavm::JavaClass* pJavaClass);
	javainstr* jop_iconst_5(const javavm::JavaClass* pJavaClass);
	javainstr* jop_istore(const javavm::JavaClass* pJavaClass);
	javainstr* jop_istore_1(const javavm::JavaClass* pJavaClass);
	javainstr* jop_nop(const javavm::JavaClass* c);
	javainstr* jop_aconst_null(const javavm::JavaClass* c);
	javainstr* jop_dup(const javavm::JavaClass* c);
	javainstr* jop_return(const javavm::JavaClass* c);
	javainstr* jop_dload_0(const javavm::JavaClass* c);
	javainstr* jop_dload_1(const javavm::JavaClass* c);
	javainstr* jop_dload_2(const javavm::JavaClass* c);
	javainstr* jop_dload_3(const javavm::JavaClass* c);
	javainstr* jop_aload_0(const javavm::JavaClass* c);
	javainstr* jop_aload_1(const javavm::JavaClass* c);
	javainstr* jop_aload_2(const javavm::JavaClass* c);
	javainstr* jop_aload_3(const javavm::JavaClass* c);
	javainstr* jop_iaload(const javavm::JavaClass* c);
	javainstr* jop_aaload(const javavm::JavaClass* c);
	javainstr* jop_aastore(const javavm::JavaClass* c);
	javainstr* jop_invokevirtual(const javavm::JavaClass* c);
	javainstr* jop_invokespecial(const javavm::JavaClass* c);
	javainstr* jop_invokestatic(const javavm::JavaClass* c);
	javainstr* jop_invokeinterface(const javavm::JavaClass* c);
	javainstr* jop_getstatic(const javavm::JavaClass* c);
	javainstr* jop_putstatic(const javavm::JavaClass* c);
	javainstr* jop_getfield(const javavm::JavaClass* c);
	javainstr* jop_putfield(const javavm::JavaClass* c);
	javainstr* jop_ldc(const javavm::JavaClass* c);
	javainstr* jop_ldc_w(const javavm::JavaClass* c);
	javainstr* jop_ldc2_w(const javavm::JavaClass* c);
	javainstr* jop_goto(const javavm::JavaClass* c);
	javainstr* jop_jsr(const javavm::JavaClass* c);
	javainstr* jop_ret(const javavm::JavaClass* c);
	javainstr* jop_new(const javavm::JavaClass* c);
	javainstr* jop_newarray(const javavm::JavaClass* c);
	javainstr* jop_anewarray(const javavm::JavaClass* c);
	javainstr* jop_checkcast(const javavm::JavaClass* c);
	javainstr* jop_instanceof(const javavm::JavaClass* c);
	javainstr* jop_if_icmp(const javavm::JavaClass* c);
	javainstr* jop_ifnull(const javavm::JavaClass* c);
	javainstr* jop_ifnonnull(const javavm::JavaClass* c);
	javainstr* jop_bipush(const javavm::JavaClass* c);
	javainstr* jop_sipush(const javavm::JavaClass* c);
	javainstr* jop_tableswitch(const javavm::JavaClass* c);
	javainstr* jop_iinc(const javavm::JavaClass* c);
};

/*
class CodeCompExt javadasmContext : public MContext
{
public:
	JavaClass* m_pJavaClass;
};
*/

DebuggingExt javainstr* disasm_java(javavmContext* c, const javavm::JavaClass* pdasm);

DebuggingExt System::StringA* toString(const javavm::JavaClass* pdasm, const javainstr* p);

}	// java
}

#endif // Java_Disasm_h
