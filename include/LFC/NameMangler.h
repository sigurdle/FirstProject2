namespace System
{

class LFCEXT Mangler
{
public:

	CTOR Mangler(bool bPreserveTypedefs = false);

	IO::TextWriter& MangleType(Type* pType, IO::TextWriter& strbuilder);
	void MangleEnumType(EnumType* pType, IO::TextWriter& strbuilder);
	void MangleClassType(ClassType* pType, IO::TextWriter& strbuilder);
	void MangleFunctionParameters(const FunctionParameters& parameters, IO::TextWriter& strbuilder);

	void MangleName(Scope* pScope, IO::TextWriter& strbuilder);

//	StringA* MangleName(Scope* pScope, __live_object_ptr<StringA> & refname);

protected:

	static void Base36(IO::TextWriter& strbuilder, int num);

	bool m_bPreserveTypedefs;

	uint8 m_buffer[2048];
//	template class LFCEXT ::map<Object*, int, ::less<Object*>, grow_allocator>;
	map<Object*, int, less<Object*>, grow_allocator> m_dict;
};

void MangleName(ClassType* pClass, Declarator* decl, StringStream& strbuilder);

}
