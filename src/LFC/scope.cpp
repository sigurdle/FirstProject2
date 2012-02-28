#include "stdafx.h"
#include "LFC.h"
#include "Type.h"

namespace System
{

Scope::Scope()
{
	m_pParentScope = NULL;

	m_pType = NULL;
	m_pNamespace = NULL;
}

Scope::~Scope()
{
	if (m_pParentScope)
	{
		/*
		for (int i = 0; i < m_pIDExprs->m_v.size(); i++)
		{
			m_pParentScope->m_pIDExprs->m_v.Add(m_pIDExprs->m_v[i]);
		}
		*/
	}
}

// TODO, never gc while in here (use a critical section)

LFCEXT Type* GetType(ClassType* pClass, StringIn name)
{
	typemap::const_iterator it = pClass->m_pScope->m_types.find(name);
	if (it != pClass->m_pScope->m_types.end())
	{
		return (*it).second;
	}

	for (unsigned int i = 0; i < pClass->m_bases.GetSize(); ++i)
	{
		BaseClass* baseclass = pClass->m_bases[i];

		ClassType* pBaseClass;
		
		ASSERT(baseclass->m_pClass);
	//	ASSERT(baseclass->m_pClass->get_Kind() != type_typedef);

		if (baseclass->m_pClass->get_Kind() != type_templatearg)	// ??
		{
			/*
			if (baseclass->m_pClass->get_Kind() == type_forwardclass)
			{
				if (((ForwardClassType*)baseclass->m_pClass)->m_pClass->m_pInstantiatedFromClass)
				{
					pBaseClass = ((ForwardClassType*)baseclass->m_pClass)->m_pClass->m_pInstantiatedFromClass;
				}
				else
				{
					pBaseClass = ((ForwardClassType*)baseclass->m_pClass)->m_pClass->GetClass();
				}

				ASSERT(pBaseClass->m_pInstantiatedFromClass == NULL);

			}
			else
			*/
			ClassType* pClass = baseclass->m_pClass->AsClass();
			if (pClass)
			{
				// TODO, This is because CodeComp calls us here in the parse phase where classes haven't been truly instantiated
				// However, CodeComp should rather call its own version

				if (pClass->m_pInstantiatedFromClass)
				{
					pBaseClass = pClass->m_pInstantiatedFromClass;
				}
				else
				{
					pBaseClass = pClass;//->GetClass();
				}

				ASSERT(pBaseClass->m_pInstantiatedFromClass == NULL);
			}
#if 0
			else if (baseclass->m_pClass->get_Kind() == type_templateinst)
			{
				pBaseClass = baseclass->m_pClass->m_pInstantiatedFrom->m_pClass->GetClass();
				//ASSERT(0);	// ??
				//pBaseClass = baseclass->m_pClass;//->GetClass();//m_pInstantiatedFrom->m_pClass->GetClass();
			}
#endif
			else
			{
				raise(SystemException("baseClass is not a class type"));
			}

			Type* pType = GetType(pBaseClass, name);
			if (pType) return pType;
		}
	}

	return NULL;
}

Type* Scope::GetType(StringIn name) const
{
	ASSERT(name.GetLength() > 0);

	if (m_pNamespace && m_pNamespace->AsClass())
	{
		Type* pType = System::GetType(m_pNamespace->AsClass(), name);
		if (pType)
			return pType;
	}
	else
	{
		typemap::const_iterator it = m_types.find(name);
		if (it != m_types.end())
		{
			return (*it).second;
		}
	}

	if (m_pParentScope)
	{
		return m_pParentScope->GetType(name);
	}

	return NULL;
}

void Scope::AddDeclarator(Declarator* pDeclarator)
{
	ASSERT(pDeclarator);
//	ASSERT(pDeclarator->m_name.length());

	declsmap::iterator decli = m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
//	pDeclaratorRef->m_pDeclarator->m_referenced = 2;

//	pDeclaratorRef->m_pDeclarator->m_defined = true;

	m_orderedDecls.Add(pDeclarator);
}

//extern const char mystr[] ="Hello";

/*
template<class T> StringObject* S(T str)
{
	//static const char mystr[256];//strlen[str]] = str;
	return _StringObjectW<(ULONG_PTR)str>;
}
*/

//#define S(x)	_StringObjectW<(ULONG_PTR)x>::get();

Declarator* Scope::GetDeclarator(StringIn name)
{
	ASSERT(this);

	//StringObject* str =

//	S("Hello");

	{
		{
			declsmap::iterator it = m_decls.find(name);
			if (it != m_decls.end())
			{
				return (*it).second;
			}
		}

		{
			declsmap::iterator it = m_identdecls.find(name);
			if (it != m_identdecls.end())
			{
				return (*it).second;
			}
		}

		if (m_pNamespace && m_pNamespace->AsClass())
		{
			/*
			if (this != m_pClass->m_pScope)
			{
				CDeclarator* pDeclarator = m_pClass->m_pScope->GetDeclarator(name);
				if (pDeclarator)
				{
					return pDeclarator;
				}
			}
			*/

			for (unsigned int i = 0; i < m_pNamespace->AsClass()->m_bases.GetSize(); i++)
			{
				Declarator* pDeclarator = m_pNamespace->AsClass()->m_bases[i]->m_pClass->AsClass()->GetDeclarator(name);
				if (pDeclarator)
				{
					return pDeclarator;
				}
			}
		}

		if (m_pParentScope)
		{
			return m_pParentScope->GetDeclarator(name);
		}
	}

	return NULL;
}

}	// System
