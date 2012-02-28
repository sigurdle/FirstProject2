#include "StdAfx.h"
#include "javavm.h"

namespace System
{
using namespace std;
using namespace IO;

namespace javavm
{

char fget8(IO::Stream* stream)
{
	char v;
	stream->Read(&v, 1);
	return v;
}

short fget16(IO::Stream* stream)
{
	short v;
	stream->Read(&v, 2);
	return BigEndian16(v);
}

long fget32(IO::Stream* stream)
{
	long v;
	stream->Read(&v, 4);
	return BigEndian32(v);
}

javavmext char* JavaOpcodeNames[256] =
{
	"nop",
	"aconst_null",
	"iconst_m1",
	"iconst_0",
	"iconst_1",
	"iconst_2",
	"iconst_3",
	"iconst_4",
	"iconst_5",
	"lconst_0",
	"lconst_1",
	"fconst_0",
	"fconst_1",
	"fconst_2",
	"dconst_0",
	"dconst_1",
	"bipush",
	"sipush",
	"ldc",
	"ldc_w",
	"ldc2_w",
	"iload",
	"lload",
	"fload",
	"dload",
	"aload",
	"iload_0",
	"iload_1",
	"iload_2",
	"iload_3",
	"lload_0",
	"lload_1",
	"lload_2",
	"lload_3",
	"fload_0",
	"fload_1",
	"fload_2",
	"fload_3",
	"dload_0",
	"dload_1",
	"dload_2",
	"dload_3",
	"aload_0",
	"aload_1",
	"aload_2",
	"aload_3",
	"iaload",
	"laload",
	"faload",
	"daload",
	"aaload",
	"baload",
	"caload",
	"saload",
	"istore",
	"lstore",
	"fstore",
	"dstore",
	"astore",
	"istore_0",
	"istore_1",
	"istore_2",
	"istore_3",
	"lstore_0",
	"lstore_1",
	"lstore_2",
	"lstore_3",
	"fstore_0",
	"fstore_1",
	"fstore_2",
	"fstore_3",
	"dstore_0",
	"dstore_1",
	"dstore_2",
	"dstore_3",
	"astore_0",
	"astore_1",
	"astore_2",
	"astore_3",
	"iastore",
	"lastore",
	"fastore",
	"dastore",
	"aastore",
	"bastore",
	"castore",
	"sastore",
	"pop",
	"pop2",
	"dup",
	"dup_x1",
	"dup_x2",
	"dup2",
	"dup2_x1",
	"dup2_x2",
	"swap",
	"iadd",
	"ladd",
	"fadd",
	"dadd",
	"isub",
	"lsub",
	"fsub",
	"dsub",
	"imul",
	"lmul",
	"fmul",
	"dmul",
	"idiv",
	"ldiv",
	"fdiv",
	"ddiv",
	"irem",
	"lrem",
	"frem",
	"drem",
	"ineg",
	"lneg",
	"fneg",
	"dneg",
	"ishl",
	"lshl",
	"ishr",
	"lshr",
	"iushr",
	"lushr",
	"iand",
	"land",
	"ior",
	"lor",
	"ixor",
	"lxor",
	"iinc",
	"i2l",
	"i2f",
	"i2d",
	"l2i",
	"l2f",
	"l2d",
	"f2i",
	"f2l",
	"f2d",
	"d2i",
	"d2l",
	"d2f",
	"i2b",
	"i2c",
	"i2s",
	"lcmp",
	"fcmpl",
	"fcmpg",
	"dcmpl",
	"dcmpg",
	"ifeq",
	"ifne",
	"iflt",
	"ifge",
	"ifgt",
	"ifle",
	"if_icmpeq",
	"if_icmpne",
	"if_icmplt",
	"if_icmpge",
	"if_icmpgt",
	"if_icmple",
	"if_acmpeq",
	"if_acmpne",
	"goto",
	"jsr",
	"ret",
	"tableswitch",
	"lookupswitch",
	"ireturn",
	"lreturn",
	"freturn",
	"dreturn",
	"areturn",
	"return",
	"getstatic",
	"putstatic",
	"getfield",
	"putfield",
	"invokevirtual",
	"invokespecial",
	"invokestatic",
	"invokeinterface",
	NULL,//"xxxunusedxxx1",
	"new",
	"newarray",
	"anewarray",
	"arraylength",
	"athrow",
	"checkcast",
	"instanceof",
	"monitorenter",
	"monitorexit",
	"wide",
	"multianewarray",
	"ifnull",
	"ifnonnull",
	"goto_w",
	"jsr_w",
/*
Reserved opcodes:

202 (0xca) breakpoint

254 (0xfe) impdep1

255 (0xff) impdep2
*/
};

class CJILContext
{
public:

	JavaClass* m_pJavaClass;

	uint8* code;
	uint8* p;

	inline uint16 getword()
	{
		// Big endian
		uint8 byte1 = *p++;
		uint8 byte2 = *p++;
		return (byte1 << 8) | byte2;
	}

	typedef int (CJILContext::*tyfunc)(CJILContext* c);

	static tyfunc funcs[256];

	int jop_notimpl(CJILContext* c);
	int jop_nop(CJILContext* c);
	int jop_aconst_null(CJILContext* c);
	int jop_dup(CJILContext* c);
	int jop_return(CJILContext* c);
	int jop_aload_0(CJILContext* c);
	int jop_aload_1(CJILContext* c);
	int jop_aload_2(CJILContext* c);
	int jop_aload_3(CJILContext* c);
	int jop_invokevirtual(CJILContext* c);
	int jop_invokespecial(CJILContext* c);
	int jop_getstatic(CJILContext* c);
	int jop_getfield(CJILContext* c);
	int jop_putfield(CJILContext* c);
	int jop_ldc(CJILContext* c);
	int jop_ret(CJILContext* c);
	int jop_new(CJILContext* c);
	int jop_if_icmp(CJILContext* c);
	int jop_bipush(CJILContext* c);
	int jop_sipush(CJILContext* c);
	int jop_iushr(CJILContext* c);
};


//typedef int (*jop_func)(CJILContext* c);


int CJILContext::jop_notimpl(CJILContext* c)
{
	printf("\top not implemented");
	c->p++;
	return 0;
}

int CJILContext::jop_nop(CJILContext* c)
{
	c->p++;
	return 0;
}

int CJILContext::jop_aconst_null(CJILContext* c)
{
	c->p++;
	return 0;
}

int CJILContext::jop_dup(CJILContext* c)
{
	c->p++;
	return 0;
}

int CJILContext::jop_return(CJILContext* c)
{
	c->p++;
	return 0;
}

int CJILContext::jop_aload_0(CJILContext* c)
{
	c->p++;
	return 0;
}

int CJILContext::jop_aload_1(CJILContext* c)
{
	c->p++;
	return 0;
}

int CJILContext::jop_aload_2(CJILContext* c)
{
	c->p++;
	return 0;
}

int CJILContext::jop_aload_3(CJILContext* c)
{
	c->p++;
	return 0;
}

int CJILContext::jop_invokevirtual(CJILContext* c)
{
	c->p++;
	uint16 methodIndex = c->getword();

	uint16 classIndex = c->m_pJavaClass->m_pool_array[methodIndex-1].methodRef.class_index;
	uint16 classNameIndex = c->m_pJavaClass->m_pool_array[classIndex-1].classData.name_index;
	String className = c->m_pJavaClass->m_pool_array[classNameIndex-1].utf8.str;

	uint16 nameAndTypeIndex = c->m_pJavaClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
	uint16 methodNameIndex = c->m_pJavaClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	String methodName = c->m_pJavaClass->m_pool_array[methodNameIndex-1].utf8.str;

	//printf("%s::%s", className->c_str(), methodName->c_str());

	return 0;
}

int CJILContext::jop_invokespecial(CJILContext* c)
{
	c->p++;
	uint16 methodIndex = c->getword();

	uint16 classIndex = c->m_pJavaClass->m_pool_array[methodIndex-1].methodRef.class_index;
	uint16 classNameIndex = c->m_pJavaClass->m_pool_array[classIndex-1].classData.name_index;
	String className = c->m_pJavaClass->m_pool_array[classNameIndex-1].utf8.str;

	uint16 nameAndTypeIndex = c->m_pJavaClass->m_pool_array[methodIndex-1].methodRef.name_and_type_index;
	uint16 methodNameIndex = c->m_pJavaClass->m_pool_array[nameAndTypeIndex-1].nameAndType.name_index;
	String methodName = c->m_pJavaClass->m_pool_array[methodNameIndex-1].utf8.str;

//	printf("%s::%s", className->c_str(), methodName->c_str());

	return 0;
}

int CJILContext::jop_getstatic(CJILContext* c)
{
	c->p++;
	uint16 index = c->getword();
	return 0;
}

int CJILContext::jop_getfield(CJILContext* c)
{
	c->p++;
	uint16 index = c->getword();
	return 0;
}

int CJILContext::jop_putfield(CJILContext* c)
{
	c->p++;
	uint16 index = c->getword();
	return 0;
}

int CJILContext::jop_ldc(CJILContext* c)
{
	c->p++;
	uint8 index = *c->p++;
	return 0;
}

int CJILContext::jop_ret(CJILContext* c)
{
	c->p++;
	uint8 index = *c->p++;
	return 0;
}

int CJILContext::jop_new(CJILContext* c)
{
	c->p++;
	uint16 index = c->getword();
	return 0;
}

int CJILContext::jop_if_icmp(CJILContext* c)
{
	c->p++;
	short offset = c->getword();

//	printf("%4.4x", c->p - c->code + offset);

	return 0;
}

int CJILContext::jop_bipush(CJILContext* c)
{
	c->p++;
	int int8 = *c->p++;

	printf("%d", int8);

	return 0;
}

int CJILContext::jop_sipush(CJILContext* c)
{
	c->p++;
	short int16 = c->getword();

	printf("%d", int16);

	return 0;
}

int CJILContext::jop_iushr(CJILContext* c)
{
	ASSERT(0);
	return 0;
}

CJILContext::tyfunc funcs[256] =
{
	&CJILContext::jop_nop,
	&CJILContext::jop_aconst_null,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_bipush,
	&CJILContext::jop_sipush,
	&CJILContext::jop_ldc,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_aload_0,
	&CJILContext::jop_aload_1,
	&CJILContext::jop_aload_2,
	&CJILContext::jop_aload_3,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_dup,		// 89
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_iushr,	// 124
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_if_icmp,
	&CJILContext::jop_if_icmp,
	&CJILContext::jop_if_icmp,
	&CJILContext::jop_if_icmp,
	&CJILContext::jop_if_icmp,
	&CJILContext::jop_if_icmp,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_ret,		// 169
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_return,
	&CJILContext::jop_getstatic,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_getfield,
	&CJILContext::jop_putfield,
	&CJILContext::jop_invokevirtual,
	&CJILContext::jop_invokespecial,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_new,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
	&CJILContext::jop_notimpl,
/*
Reserved opcodes:

202 (0xca) breakpoint

254 (0xfe) impdep1

255 (0xff) impdep2
*/
};

Attribute* WithAttributes::GetAttribute(StringIn str)
{
	map<String, Attribute*>::iterator it = m_attributes.find(str);
	if (it != m_attributes.end())
		return it->second;
	else
		return NULL;
}

Type* _ParseFieldType(const char*& p)
{
	Type* type = new Type;

	switch (*p)
	{
	case 'B':
	case 'C':
	case 'D':
	case 'F':
	case 'I':
	case 'J':
	case 'S':
	case 'Z':
		type->kind = (Type::TypeKind)*p;
		p++;
		break;
		
	case 'L':	// classname
		{
			type->kind = (Type::TypeKind)*p;

			p++;
			const char* start = p;
			while (*p != ';')
			{
			//	type->className += *p;
				p++;
			}
			type->className = string_copy(start, p-start);

			ASSERT(*p == ';');
			p++;
		}
		break;
		
	case '[':	// array
		{
			type->kind = (Type::TypeKind)*p;

			const char* start = p;
			p++;
			type->kind = Type::Type_array;
			type->u.arrayof = _ParseFieldType(p);

			type->className = string_copy(start, p-start);
		}
		break;
		
	default:
		ASSERT(0);
	}

	return type;
}

Type* ParseFieldType(const char* p)
{
	return _ParseFieldType(p);
}

void ParseMethodType(JavaMethod* pMethod, const char* p)
{
	ASSERT(*p == '('); p++;

	while (*p != ')')
	{
		Type* type = _ParseFieldType(p);
		pMethod->m_argumentTypes.Add(type);
	}

	ASSERT(*p == ')'); p++;

	if (*p == 'V')
	{
		p++;
		ASSERT(*p == '\0');

		Type* type = new Type;
		type->kind = Type::ReturnType_void;
		pMethod->m_pReturnType = type;
	}
	else
	{
		Type* type = _ParseFieldType(p);
		pMethod->m_pReturnType = type;
	}
}

void JavaClass::ReadAttributes(IO::Stream* stream, WithAttributes* pAttributes)
{
	uint16 attributes_count = fget16(stream);
	for (int a = 0; a < attributes_count; a++)
	{
		uint16 attribute_name_index = fget16(stream);
		uint32 attribute_length = fget32(stream);

		String name = m_pool_array[attribute_name_index-1].utf8.str;

		size_t pos = stream->GetPosition();

		if (m_pool_array[attribute_name_index-1].tag != CONSTANT_Utf8)
		{
			printf("Error\n");
			VERIFY(0);//exit(1);
		}

		Attribute* pAttribute = new Attribute;

		pAttribute->m_length = attribute_length;
		pAttribute->m_data = new uint8[pAttribute->m_length];
		stream->Read(pAttribute->m_data, pAttribute->m_length);

		/*
		if (!wcscmp(m_pool_array[attribute_name_index-1].bstr->c_str(), L"Code"))
		{
			ParseCode(attribute_length);
		}
		*/

		pAttributes->m_attributes[name] = pAttribute;

	//	long curpos = ftell(fp);
		size_t curpos = stream->GetPosition();
		if (curpos > pos+attribute_length)
		{
			printf("Read overflow\n");
			VERIFY(0);//exit(1);
		}
		stream->Seek(pos+attribute_length, IO::SeekOrigin_Start);
	}
}

int CodeAttribute::GetLineNumbers(vector<LineNumber>& lines)
{
	Attribute* pAttribute = GetAttribute(L"LineNumberTable");
	if (pAttribute == NULL)
		return 0;

	if (pAttribute->m_length < 2)
		return 0;

	uint16 count = BigEndian16(*(uint16*)pAttribute->m_data);

	uint8* p = (pAttribute->m_data + 2);
	for (uint i = 0; i < count; i++)
	{
		uint16 start_pc = BigEndian16(*(uint16*)p); p += 2;
		uint16 line_num = BigEndian16(*(uint16*)p); p += 2;

		lines.Add(LineNumber(start_pc, line_num));
	}

	return count;
}

String JavaField::GetName()
{
	return m_pOwnerClass->m_pool_array[m_name_index-1].utf8.str;
}

String JavaMethod::GetName()
{
	return m_pOwnerClass->m_pool_array[m_name_index-1].utf8.str;
}

String JavaMethod::GetSignature()
{
//	StringW name = m_pClass->m_pool_array[m_name_index-1].str;
	StringA* descriptor = m_pOwnerClass->m_pool_array[m_descriptor_index-1].utf8.str;

	return descriptor;
}

CodeAttribute* JavaMethod::GetCode()
{
	Attribute* pAttribute = GetAttribute(L"Code");
	if (pAttribute == NULL)
		return NULL;

	if (pAttribute->m_length < 12)
		raise(Exception("corrupted file"));

	ASSERT(0);
	IO::Stream* stream = NULL;//new MemoryByteStream(pAttribute->m_data, pAttribute->m_length);

	CodeAttribute* p = new CodeAttribute;
	p->max_stack = fget16(stream);
	p->max_locals = fget16(stream);
	p->code_length = fget32(stream);
	p->code = pAttribute->m_data + 8;
	stream->Seek(p->code_length, System::IO::STREAM_SEEK_CUR);

	m_exception_count = fget16(stream);

	m_exceptions = new MethodException[m_exception_count];
	stream->Read(m_exceptions, m_exception_count * sizeof MethodException);

	m_pOwnerClass->ReadAttributes(stream, p);

	return p;
}

String Utf8ToW(StringA* str)
{
	//StringW* wstr = new StringW();

	int len = str->GetLength();
	WCHAR* buffer = new WCHAR[len];
	int di = 0;

	const char* const p = (const char*)str->GetData();
	for (int i = 0; i < len; i++)
	{
		if (p[i] & 0x80)
		{
			ASSERT(p[i] & (1<<6));
			if (p[i] & (1<<5))
			{
				uint8 x = p[i++];
				uint8 y = p[i++];
				uint8 z = p[i];

				uint16 value = ((x & 0xf) << 12) + ((y & 0x3f) << 6) + (z & 0x3f);

				buffer[di++] = value;
			}
			else
			{
				uint8 x = p[i++];
				uint8 y = p[i];

				uint16 value = ((x & 0x1f) << 6) + (y & 0x3f);

				buffer[di++] = value;
			}
		}
		else
		{
			buffer[di++] = p[i];
		}
	}

	return new ImmutableString<WCHAR>(buffer, di);
}

JavaClass::JavaClass(int baseTypeSize/* = 4*/)
{
	m_baseTypeSize = baseTypeSize;

//	m_pClass = NULL;//(JavaClass*)1;
	m_interface_index = NULL;
	m_state = 0;
	m_pSuperClass = NULL;

	m_fields_count = 0;
	m_methods_count = 0;

	m_instanceFieldSize = 0;
	m_staticFieldSize = 0;

	m_pArrayOf = NULL;
}

JavaClass::~JavaClass()
{
	delete m_interface_index;
}

String JavaClass::GetSourceFile()
{
	Attribute* pAttribute = GetAttribute(L"SourceFile");

	if (pAttribute == NULL)
		return NULL;

	if (pAttribute->m_length != 2)
		THROW(exception("corrupt file"));

	uint16 index = pAttribute->m_data[0]<<8;
	index |= pAttribute->m_data[1];

	if (m_pool_array[index-1].tag != CONSTANT_Utf8)
		THROW(-1);

	return Utf8ToW(m_pool_array[index-1].utf8.str);
	//return ConvertA2S(m_pool_array[index-1].str);
}

int JavaClass::Parse(IO::Stream* stream)
{
	m_magic = fget32(stream);
	m_minor_version = fget16(stream);
	m_major_version = fget16(stream);

	if (m_major_version < 45 || m_major_version > 50/*48*//*46*/)
	{
		printf("Unsupported major minor version %d.%d\n", m_major_version, m_minor_version);
		return -1;//exit(1);
	}

// The value of the constant_pool_count item is equal to the number of entries in the constant_pool table plus one
	m_constant_pool_count = fget16(stream);

	int i;

	int nitems = m_constant_pool_count-1;

	m_pool_array = new CPoolItem[nitems];

	for (i = 0; i < nitems; i++)
	{
		printf("%d\t", i+1);

		m_pool_array[i].tag = fget8(stream);

		switch (m_pool_array[i].tag)
		{
		case CONSTANT_Utf8:
			{
				uint16 length = fget16(stream);

				char* data = new char[length];

				for (int n = 0; n < length; n++)
				{
					uint8 x = fget8(stream);
					ASSERT(x != 0);	// Never embedded nulls

					data[n] = x;
				}

			//	String string(data);
				m_pool_array[i].utf8.str = new ImmutableString<char>(data, length);//.GetString();

				//printf("%S", string.c_str());
			}
			break;
			
		case CONSTANT_Integer:
		case CONSTANT_Float:
			{
				m_pool_array[i].int_32 = fget32(stream);
				//printf("string_index=%d", string_index);
			}
			break;

			/*
			{
				printf("Float:\t");
				DWORD v = fget32(stream);
				m_pool_array[i].float_32 = *(float*)&v;
				//printf("string_index=%d", string_index);
			}
			break;
			*/

		case CONSTANT_Long:
		case CONSTANT_Double:
			{
				m_pool_array[i].long_64 = (int64)fget8(stream)<<56;
				m_pool_array[i].long_64 |= (int64)fget8(stream)<<48;
				m_pool_array[i].long_64 |= (int64)fget8(stream)<<40;
				m_pool_array[i].long_64 |= (int64)fget8(stream)<<32;
				m_pool_array[i].long_64 |= (int64)fget8(stream)<<24;
				m_pool_array[i].long_64 |= (int64)fget8(stream)<<16;
				m_pool_array[i].long_64 |= (int64)fget8(stream)<<8;
				m_pool_array[i].long_64 |= (int64)fget8(stream);
				i++;	// for long and double
			}
			break;

		case CONSTANT_String:
			{
				printf("String:\t");
				m_pool_array[i].string_index = fget16(stream);
				//printf("string_index=%d", string_index);
			}
			break;
			
		case CONSTANT_Class:
			{
				m_pool_array[i].classData.name_index = fget16(stream);
			}
			break;
			
		case CONSTANT_Fieldref:
			{
				m_pool_array[i].fieldRef.class_index = fget16(stream);
				m_pool_array[i].fieldRef.name_and_type_index = fget16(stream);
			}
			break;

		case CONSTANT_Methodref:
		case CONSTANT_InterfaceMethodref:
			{
				m_pool_array[i].methodRef.class_index = fget16(stream);
				m_pool_array[i].methodRef.name_and_type_index = fget16(stream);
			}
			break;
			
		case CONSTANT_NameAndType:
			{
				m_pool_array[i].nameAndType.name_index = fget16(stream);
				m_pool_array[i].nameAndType.descriptor_index = fget16(stream);
			}
			break;
			
		default:
			{
				printf("Unknown tag %d\n", m_pool_array[i].tag);
				LOG("Unknown tag %d\n", m_pool_array[i].tag);
				ASSERT(0);
				return -1;
			}
		}

		printf("\n");
	}

	m_access_flags = fget16(stream);
	m_this_class = fget16(stream);
	m_super_class = fget16(stream);
	m_interfaces_count = fget16(stream);

	m_name = m_pool_array[m_pool_array[m_this_class-1].classData.name_index-1].utf8.str;

	m_interface_index = new uint16[m_interfaces_count];

	for (i = 0; i < m_interfaces_count; ++i)
	{
		m_interface_index[i] = fget16(stream);
		if (m_interface_index[i] == 0)
		{
			ASSERT(0);
			return -1;
		}

		ASSERT(m_pool_array[m_interface_index[i]-1].tag == CONSTANT_Class);
	}

	m_fields_count = fget16(stream);
	m_fields = new JavaField*[m_fields_count];

	for (int f = 0; f < m_fields_count; ++f)
	{
		JavaField* pField = new JavaField(this);

		pField->m_access_flags = fget16(stream);
		pField->m_name_index = fget16(stream);
		pField->m_descriptor_index = fget16(stream);

		if (pField->m_name_index == 0)
		{
			ASSERT(0);
			return -1;
		}

		StringA* name = m_pool_array[pField->m_name_index-1].utf8.str;
		m_fieldByName[name] = pField;

		StringA* descriptor = m_pool_array[pField->m_descriptor_index-1].utf8.str;
		pField->m_pType = ParseFieldType(CString(descriptor).c_str());

		ReadAttributes(stream, pField);

		m_fields[f] = pField;
	}

	m_methods_count = fget16(stream);
	m_methods = new JavaMethod*[m_methods_count];

	for (int m = 0; m < m_methods_count; ++m)
	{
		JavaMethod* pMethod = new JavaMethod(this);

		pMethod->m_access_flags = fget16(stream);

		/*
		if (pMethod->m_access_flags & ACC_NATIVE)
		{
			printf("Native method\n");
		}
		*/

		pMethod->m_name_index = fget16(stream);
		pMethod->m_descriptor_index = fget16(stream);

		if (pMethod->m_name_index == 0)
		{
			ASSERT(0);
			return -1;
		}

		/*
		{
			for (int i = 0; i < constant_pool_count; i++)
			{
				if (m_pool_array[i].tag == CONSTANT_Methodref)
				{
					if (m_pool_array[i].methodRef.class_index
				}
			}
		}
		*/

		String name = m_pool_array[pMethod->m_name_index-1].utf8.str;
		String descriptor = m_pool_array[pMethod->m_descriptor_index-1].utf8.str;
		ParseMethodType(pMethod, CString(descriptor).c_str());

		pMethod->m_name = name;

		char buffer[1024];
		sprintf_s(buffer, "%s%s", CString(name).c_str(), CString(descriptor).c_str());

		m_methodByName[string_copy(buffer)] = pMethod;
	//	LOG("%S\n", name->c_str());

		ReadAttributes(stream, pMethod);

		m_methods[m] = pMethod;
	}

	ReadAttributes(stream, this);

	return 0;
}

String JavaClass::GetName()
{
	return m_name;
	//return m_pool_array[m_pool_array[m_this_class-1].classData.name_index-1].str;
}

JavaMethod* JavaClass::GetMethodByName(StringIn name)
{
	JavaClass* pClass = this;
	do
	{
		map<String, JavaMethod*>::iterator it = pClass->m_methodByName.find(name);

		if (it != pClass->m_methodByName.end())
			return (*it).second;

		pClass = pClass->GetSuperClass();
	}
	while (pClass);

	return NULL;
}

JavaMethod* JavaClass::GetMethodShallow(StringIn name)
{
	map<String, JavaMethod*>::iterator it = m_methodByName.find(name);
	if (it != m_methodByName.end())
		return (*it).second;
	else
		return NULL;
}

JavaField* JavaClass::GetFieldByName(StringIn name)
{
	map<String, JavaField*>::iterator it = m_fieldByName.find(name);
	if (it != m_fieldByName.end())
		return (*it).second;
	else
		return NULL;
}

JavaField* JavaClass::GetField(StringIn name)
{
	JavaClass* pClass = this;
	do
	{
		map<String, JavaField*>::iterator it = pClass->m_fieldByName.find(name);

		if (it != pClass->m_fieldByName.end())
			return (*it).second;

		pClass = pClass->GetSuperClass();
	}
	while (pClass);

	return NULL;
}

JavaClass* JavaClass::GetSuperClass()
{
	return m_pSuperClass;
}

void JavaClass::Initialize(Thread* vm)
{
	LOG(" Initializing class %s {\n", CString(GetName()).c_str());

	m_state = 1;	// Initializing
	/*
	if (m_super_class)
	{
	}
	*/

	if (m_super_class > 0)
	{
		ASSERT(m_pSuperClass == NULL);

		if (m_pool_array[m_super_class-1].classData.m_pClass == NULL)
		{
			String className = m_pool_array[m_pool_array[m_super_class-1].classData.name_index-1].utf8.str;
			m_pool_array[m_super_class-1].classData.m_pClass = vm->LoadClass(className);
		}
		m_pSuperClass = m_pool_array[m_super_class-1].classData.m_pClass;
		VERIFY(m_pSuperClass);
	}

	{
		m_pInterfaces = new JavaClass*[m_interfaces_count];

		for (int i = 0; i < m_interfaces_count; i++)
		{
			if (m_pool_array[m_interface_index[i]-1].classData.m_pClass == NULL)
			{
				String className = m_pool_array[m_pool_array[m_interface_index[i]-1].classData.name_index-1].utf8.str;
				m_pool_array[m_interface_index[i]-1].classData.m_pClass = vm->LoadClass(className);
			}

			m_pInterfaces[i] = m_pool_array[m_interface_index[i]-1].classData.m_pClass;
			VERIFY(m_pInterfaces[i]);
		}
	}

	int f;

	m_staticFieldSize = 0;
	m_instanceFieldSize = 0;

	if (m_pSuperClass)
	{
		m_instanceFieldSize += m_pSuperClass->m_instanceFieldSize;
	}

	for (f = 0; f < m_fields_count; ++f)
	{
		JavaField* pField = m_fields[f];

		uint32 fieldSize;
		if (pField->m_pType->kind == Type::BaseType_double || pField->m_pType->kind == Type::BaseType_long)
		{
			fieldSize = 8;
		}
		else if (pField->m_pType->kind == Type::Type_ref || pField->m_pType->kind == Type::Type_array)
		{
			fieldSize = sizeof(ObjectRef);
		}
		else
		{
			fieldSize = 4;
		}

		if (pField->m_access_flags & ACC_STATIC)
		{
			pField->m_offset = m_staticFieldSize;
			m_staticFieldSize += fieldSize;
		}
		else
		{
			pField->m_offset = m_instanceFieldSize;
			m_instanceFieldSize += fieldSize;
		}
	}

	m_staticData = new uint8[m_staticFieldSize];
	memset(m_staticData, 0, m_staticFieldSize);

	for (f = 0; f < m_fields_count; f++)
	{
		JavaField* pField = m_fields[f];
		if (pField->m_access_flags & ACC_STATIC)
		{
			Attribute* pAttribute = pField->GetAttribute("ConstantValue");
			if (pAttribute)
			{
				ASSERT(pAttribute->m_length == 2);
				uint16 index = BigEndian16(*(uint16*)pAttribute->m_data);
				CPoolItem& item = m_pool_array[index-1];

				if (item.tag == CONSTANT_Integer)
				{
					jint* p = (jint*)(m_staticData + pField->m_offset);
					*p = item.int_32;
				}
				else if (item.tag == CONSTANT_Float)
				{
					jfloat* p = (jfloat*)(m_staticData + pField->m_offset);
					*p = item.float_32;
				}
				else if (item.tag == CONSTANT_Long)
				{
					jlong* p = (jlong*)(m_staticData + pField->m_offset);
					*p = item.long_64;
				}
				else if (item.tag == CONSTANT_Double)
				{
					jdouble* p = (jdouble*)(m_staticData + pField->m_offset);
					*p = item.double_64;
				}
				else if (item.tag == CONSTANT_String)
				{
					JavaObject** p = (JavaObject**)(m_staticData + pField->m_offset);
					*p = m_pool_array[item.string_index-1].GetString(vm);//vm->NewString(stringW->c_str(), stringW->Length());

					/*
					StringW* stringW = Utf8ToW(m_pool_array[item.string_index-1].str);

					JavaObject** p = (JavaObject**)(m_staticData + pField->m_offset);
					*p = vm->NewString(stringW->c_str(), stringW->Length());
					*/
				}
				else
				{
					ASSERT(0);
				}
			}
		}
	}
}

void JavaClass::InitializeStatics(Thread* thread)
{
	map<String, JavaMethod*>::iterator it = m_methodByName.find("<clinit>()V");
	if (it != m_methodByName.end())
	{
		JavaMethod* pMethod = (*it).second;

		if (pMethod->m_access_flags & ACC_NATIVE)
		{
			ASSERT(0);
			LOG("\n");
		}
		else
		{
			CodeAttribute* pCode = pMethod->GetCode();

		//	Thread* thread = new Thread;
		//	thread->m_vm = vm;
		//	Frame* oldframe = thread->m_pFrame;
		//	uint8* oldpc = thread->m_pc;

			Frame* pCaller = thread->m_pFrame;
			Frame* pFrame = new Frame(pMethod, pCode, pCaller, thread->m_pc);
			thread->m_pFrame = pFrame;
			thread->m_pc = pCode->code;

			/*
			if (*GetName() == "java/io/BufferedInputStream")
			{
				MessageBeep(-1);
			}
			*/

			LOG("%s.<clinit>() { ", CString(GetName()).c_str());

			ULONG ninstrs = 0;
			do
			{
				thread->next_instruction();
				ninstrs++;
			}
			while (thread->m_pFrame != pCaller);

		//	thread->m_pc = oldpc;
		//	thread->m_pFrame = oldframe;
		}
	}

	m_state = 2;
	LOG("}\n");
}

JavaObject* JavaClass::CreateInstance()
{
	JavaObject* pObjectRef = new JavaObject;
	pObjectRef->m_pClass = this;
	pObjectRef->m_data = new uint8[m_instanceFieldSize];
	memset(pObjectRef->m_data, 0, m_instanceFieldSize);

	/*
	if (m_name == "java/lang/reflect/Field")
	{
		MessageBeep(-1);
	}
	*/

	/*
	if (*m_name == "java/lang/Thread")
	{
		JavaVM::Thread* thread = new JavaVM::Thread;
		thread->m_vm = m_pJavaVMHost->m_pJavaVM;

		m_pJavaVMHost->m_pJavaVM->m_threads.Add(thread);
	}
	*/

	return pObjectRef;
}

}	// JavaVM
}
