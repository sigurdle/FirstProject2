#ifndef System_VCMangler_h
#define System_VCMangler_h

namespace System
{

class LFCEXT VCMangler
{
public:
	CTOR VCMangler();

	IO::TextWriter& WriteName(TypeSerializable* str, IO::TextWriter& strbuilder);

	IO::TextWriter& MangleNameName(Declarator* pDeclarator, IO::TextWriter& strbuilder);
	IO::TextWriter& MangleNameName(Scope* pScope, IO::TextWriter& strbuilder);
	IO::TextWriter& MangleType(Type* pType, IO::TextWriter& strbuilder);

	IO::TextWriter& MangleFunctionParameters(FunctionType* pFun, IO::TextWriter& strbuilder);

	static String MangleNameVC(ClassType* pClass, Declarator* decl, IO::TextWriter& strbuilder = IO::StringWriter());
	static String MangleNameVC(Scope* pScope, Declarator* decl, IO::TextWriter& strbuilder = IO::StringWriter());

public:

	int m_n;

	static int m_x64;

protected:

	uint8 m_buffer[512];

	map<TypeSerializable*, int, less<TypeSerializable*>, grow_allocator> m_names;

	map<Type*, int> argTypes;
};

}	// System

#endif // System_VCMangler_h
