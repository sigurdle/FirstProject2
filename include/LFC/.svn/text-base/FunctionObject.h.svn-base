namespace System
{

class LFCEXT FunctionObject : public Object, public IFunction
{
public:

	CTOR FunctionObject(Declarator* decl);

	virtual size_t get_NumArgs() override;
	virtual String ToString() override;

	Module* GetModule()
	{
		return m_decl->m_pModule;
	}

	ULONG_PTR GetAddress()
	{
		return m_decl->GetAddress();
	}

	Declarator* m_decl;
};

}	// System
