namespace System
{

typedef map<String, Namespace*> namespacemap;
typedef map<String, NamedType*> typemap;
typedef multimap<String, Declarator*> declsmap;
typedef vector<Declarator*> declsvector;

class LFCEXT Scope : public Object
{
public:
	CTOR Scope();
	virtual ~Scope();

//	void AddType(CCPPCompiler* pCompiler, Type* pType);

	Type* GetType(StringIn name) const;
	void AddDeclarator(Declarator* pDeclarator);
	Declarator* GetDeclarator(StringIn name);

	Type* m_pType;
	Scope* m_pParentScope;
	NamespaceType* m_pNamespace;

	vector<Scope*> m_subScopes;
	vector<Namespace*> m_using_directives;

	typemap m_types;
	namespacemap m_namespaces;
	declsmap m_decls;
	declsvector m_orderedDecls;
	declsmap m_identdecls;

	ULONG_PTR m_startAddress;
	ULONG_PTR m_endAddress;

#if 0
	CExpression* GetIdentValue(const char* name, Scope* pScope)
	{
		identvaluemap::iterator enumi = m_identvalues.find(name);
		if (enumi != m_identvalues.end())
		{
			CExpression* pExpr = new CExpression;
			pExpr->tok.type = CToken::tok_integer;
			pExpr->tok.int32 = (*enumi).second;

			return pExpr;
		}
		else
		{
			if (m_pParentScope)
			{
				return m_pParentScope->GetIdentValue(name, pScope);
			}
			return NULL;
		}
	}
#endif

#if 0
	CTemplate* GetTemplate(const char* name)
	{
		ASSERT(name);
		ASSERT(name[0]);

		templatemap::iterator i = m_templates.find(name);
		if (i != m_templates.end())
		{
			return (*i).second;
		}
		else
		{
			if (m_pParentScope)
			{
				return m_pParentScope->GetTemplate(name);
			}
			return NULL;
		}
	}
#endif
};

}	// System
