#pragma once

//#include "Java.h"

namespace System
{
namespace CLI
{

class DataType
{
	union
	{
		char byte_dt;
		short short_dt;
		long int_dt;
		long bool_dt;
		LONGLONG long_dt;
		float float_dt;
		double double_dt;
	}
	u;
};

/*
class Operand
{
public:
	Operand* prev;
	long value;
};
*/

typedef long Operand;

class CodeCompExt MethodState	// Another term for Method invocation frame
{
public:
	MethodState()
	{
		m_pCaller = NULL;
		m_returnAddress = 0;
		m_localVariables = new long[512];	// TODO
	}

// m_ip;

	MethodState* m_pCaller;
	uint8* m_returnAddress;

	long* m_localVariables;
	vector<Operand> m_operands;

//	Operand* top;

//	CJavaClassFile* m_pJavaClass;

	void push(Operand value);
	Operand pop();
};

class CodeCompExt Thread
{
public:
	MethodState* m_pFrame;
	uint8* pc;

	void CreateThread()
	{
		m_pFrame = new MethodState;
	}

	int next_instruction();

	inline uint16 getword()
	{
		// Big endian
		uint8 byte1 = *pc++;
		uint8 byte2 = *pc++;
		return (byte1 << 8) | byte2;
	}

	typedef int (Thread::*tyfunc)(Thread* c);

	static tyfunc funcs[256];

/*
	int jop_notimpl(Thread* c);
	int jop_nop(Thread* c);
	int jop_aconst_null(Thread* c);
	int jop_iconst_m1(Thread* c);	// minus 1
	int jop_iconst_0(Thread* c);
	int jop_iconst_1(Thread* c);
	int jop_iconst_2(Thread* c);
	int jop_iconst_3(Thread* c);
	int jop_iconst_4(Thread* c);
	int jop_iconst_5(Thread* c);
	int jop_istore(Thread* c);
	int jop_istore_0(Thread* c);
	int jop_istore_1(Thread* c);
	int jop_istore_2(Thread* c);
	int jop_istore_3(Thread* c);
	int jop_iload(Thread* c);
	int jop_iload0(Thread* c);
	int jop_iload1(Thread* c);
	int jop_iload2(Thread* c);
	int jop_iload3(Thread* c);
	int jop_dup(Thread* c);
	int jop_return(Thread* c);
	int jop_aload_0(Thread* c);
	int jop_aload_1(Thread* c);
	int jop_aload_2(Thread* c);
	int jop_aload_3(Thread* c);
	int jop_iadd(Thread* c);
	int jop_invokevirtual(Thread* c);
	int jop_invokespecial(Thread* c);
	int jop_getstatic(Thread* c);
	int jop_getfield(Thread* c);
	int jop_putfield(Thread* c);
	int jop_ldc(Thread* c);
	int jop_ret(Thread* c);
	int jop_new(Thread* c);
	int jop_if_icmp(Thread* c);
	int jop_bipush(Thread* c);
	int jop_sipush(Thread* c);
	*/
};

class CodeCompExt Process
{
public:
//	LoadClass(StringA className);
//	LinkClass();

	vector<Thread*> m_threads;
};

}	// CLI
}
