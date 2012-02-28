#include "stdafx.h"
#include "LFC.h"
#include "Type.h"
#include "BitStream.h"

namespace System
{

ClassType::ClassType() :
	m_sizeof(~0),
	m_rsizeof(~0),
	m_alignment(0),
	m_force_alignment(0),
	m_packing(0),
	m_virtualSize(0),
 
	m_bVT(false),
	m_def(false),

	m_pInstantiatedFromClass(nullptr),
	m_pInstantiatedFromArgs(nullptr),
	m_pTemplateParams(nullptr),

	m_copyOperator((Declarator*)-1),
	m_copyConstructor((Declarator*)-1),

	m_notOperator((Declarator*)-1),
	m_notOperatorConst((Declarator*)-1),

	m_complementOperator((Declarator*)-1),
	m_complementOperatorConst((Declarator*)-1)
{
}

ClassType::~ClassType()
{
}

Vector<BaseClass*, vector<BaseClass*>&>* ClassType::get_BaseClasses()
{
	return new Vector<BaseClass*, vector<BaseClass*>&>(m_bases);
}

Vector<ClassType*, vector<ClassType*>&>* ClassType::get_DerivedClasses()
{
	return new Vector<ClassType*, vector<ClassType*>&>(m_derived);
}

Declarator* ClassType::FindEmptyConstructor()
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		if ((*it)->m_pType->get_Kind() == type_function && (*it)->m_name == m_name &&
			(*it)->m_pType->AsFunction()->m_parameters.size() == 0)
		{
			if ((*it)->get_Access() == AccessSpec_Private)
				return nullptr;

			return *it;
		}
	}

	return nullptr;
}

Declarator* ClassType::GetEmptyConstructor()
{
	if (m_emptyConstructor == (Declarator*)-1)
	{
		m_emptyConstructor = FindEmptyConstructor();
	}

	return m_emptyConstructor;
}

Declarator* ClassType::FindCopyConstructor()
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		if ((*it)->m_pType->get_Kind() == type_function && (*it)->m_name == m_name &&
			(*it)->m_pType->AsFunction()->m_parameters.size() == 1 &&
			(*it)->m_pType->AsFunction()->m_parameters[0].m_pType->get_Kind() == type_reference &&
			(*it)->m_pType->AsFunction()->m_parameters[0].m_pType->GetPointerTo()->GetStripped() == this)
		{
			if ((*it)->get_Access() == AccessSpec_Private)
				return nullptr;

			return *it;
		}
	}

	return nullptr;
}

Declarator* ClassType::GetCopyConstructor()
{
	if (m_copyConstructor == (Declarator*)-1)
	{
		m_copyConstructor = FindCopyConstructor();
	}

	return m_copyConstructor;
}

Declarator* ClassType::GetCopyConstructor(Type* fromType)
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		if ((*it)->m_pType->get_Kind() == type_function && (*it)->m_name == m_name &&
			(*it)->m_pType->AsFunction()->m_parameters.size() == 1)
		{
			Type* argType = (*it)->m_pType->AsFunction()->m_parameters[0].m_pType->GetStripped();

			if (argType->get_Kind() == type_reference &&
				argType->GetPointerTo()->GetStripped() == fromType)
			{
				if ((*it)->get_Access() == AccessSpec_Private)
					return nullptr;

				return *it;
			}
		}
	}

	return nullptr;
}

Declarator* ClassType::GetMoveConstructor()
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		if ((*it)->m_pType->get_Kind() == type_function && (*it)->m_name == m_name &&
			(*it)->m_pType->AsFunction()->m_parameters.size() == 1)
		{
			Type* argType = (*it)->m_pType->AsFunction()->m_parameters[0].m_pType->GetStripped();

			if (argType->get_Kind() == type_rvalue_reference &&
				argType->GetPointerTo()->GetStripped() == this)
			{
				if ((*it)->get_Access() == AccessSpec_Private)
					return nullptr;

				return *it;
			}
		}
	}

	return nullptr;
}

Declarator* ClassType::GetMoveConstructor(Type* fromType)
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		if ((*it)->m_pType->get_Kind() == type_function && (*it)->m_name == m_name &&
			(*it)->m_pType->AsFunction()->m_parameters.size() == 1)
		{
			Type* argType = (*it)->m_pType->AsFunction()->m_parameters[0].m_pType->GetStripped();

			if (argType->get_Kind() == type_rvalue_reference &&
				argType->GetPointerTo()->GetStripped() == fromType)
			{
				if ((*it)->get_Access() == AccessSpec_Private)
					return nullptr;

				return *it;
			}
		}
	}

	return nullptr;
}

Declarator* ClassType::GetDestructor(AccessSpec access)
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		if ((*it)->m_name.At(0) == '~')
		{
			if ((*it)->get_Access() < access)
				return nullptr;

			return *it;
		}
	}

	return nullptr;
}

Declarator* ClassType::GetOperatorNew()
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		if ((*it)->m_name == "operator new")
		{
			return *it;
		}
	}

	return nullptr;
}

Declarator* ClassType::GetOperatorDelete()
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		if ((*it)->m_name == "operator_delete")
		{
			return *it;
		}
	}

	return nullptr;
}

Declarator* ClassType::FindCopyOperator()
{
	for (auto it = m_pScope->m_orderedDecls.begin(); it != m_pScope->m_orderedDecls.end(); ++it)
	{
		FunctionType* pFun = (*it)->m_pType->AsFunction();
		if (pFun && (*it)->m_name == "operator=" &&
			pFun->m_parameters.size() == 1 &&
			pFun->m_parameters[0].m_pType->Normalized()->get_Kind() == type_reference &&
			pFun->m_parameters[0].m_pType->Normalized()->GetPointerTo()->GetStripped() == this)
		{
			if ((*it)->get_Access() != AccessSpec_Private)
				return nullptr;

			return *it;
		}
	}

	return nullptr;
}

Declarator* ClassType::GetCopyOperator()
{
	if (m_copyOperator == (Declarator*)-1)
	{
		m_copyOperator = FindCopyOperator();
	}

	return m_copyOperator;
}

Declarator* ClassType::GetConversionOperator(Type* toType)
{
	toType = toType->GetStripped();

	Dispatch* pDispatch = GetDispatch(this);
	auto it = pDispatch->m_methodnames.find("operator conversion");

	if (it != pDispatch->m_methodnames.end())
	{
		Declarator* method = nullptr;
		do
		{
			FunctionType* pFun = it->second->m_pType->AsFunction();
			if (pFun->m_pReturnType == toType)
			{
				// Exact match
				return it->second;
			}

			if (pFun->m_pReturnType->IsOfType(toType))
			{
				method = it->second;
			}

			++it;
		}
		while (it->first == "operator conversion");

		return method;
		/*
		if (it->first == "operator conversion")
		{
			break;
		}
		*/
	}

	return nullptr;
}

Declarator* ClassType::GetConversionOperatorConst(Type* toType)
{
	toType = toType->GetStripped();

	Dispatch* pDispatch = GetDispatch(this);
	auto it = pDispatch->m_methodnames.find("operator conversion");

	if (it != pDispatch->m_methodnames.end())
	{
		Declarator* method = nullptr;
		do
		{
			FunctionType* pFun = it->second->m_pType->AsFunction();
			if (pFun->m_bConst)
			{
				if (pFun->m_pReturnType == toType)
				{
					// Exact match
					return method;
				}

				if (pFun->m_pReturnType->IsOfType(toType))
				{
					method = it->second;
				}
			}
			++it;
		}
		while (it->first == "operator conversion");

		return method;
		/*
		if (it->first == "operator conversion")
		{
			break;
		}
		*/
	}

	return nullptr;
}

Declarator* ClassType::GetNotOperator()
{
	if (m_notOperator != (Declarator*)~0) return m_notOperator;

	Dispatch* pDispatch = GetDispatch(this);
	auto it = pDispatch->m_methodnames.find("operator!");

	if (it != pDispatch->m_methodnames.end())
	{
		Declarator* method = nullptr;
		do
		{
			FunctionType* pFun = it->second->m_pType->AsFunction();
			if (pFun->m_bConst)
			{
				m_notOperatorConst = it->second;
				return it->second;
			}
			++it;
		}
		while (it->first == "operator!");
	}

	m_notOperator = nullptr;
	return nullptr;
}

Declarator* ClassType::GetNotOperatorConst()
{
	if (m_notOperatorConst != (Declarator*)~0) return m_notOperatorConst;

	Dispatch* pDispatch = GetDispatch(this);
	auto it = pDispatch->m_methodnames.find("operator!");

	if (it != pDispatch->m_methodnames.end())
	{
		Declarator* method = nullptr;
		do
		{
			FunctionType* pFun = it->second->m_pType->AsFunction();
			if (pFun->m_bConst)
			{
				m_notOperatorConst = it->second;
				return it->second;
			}
			++it;
		}
		while (it->first == "operator!");
	}

	m_notOperatorConst = nullptr;
	return nullptr;
}

bool ClassType::Equals(const ClassType& other) const
{
	VERIFY(this);
	VERIFY(&other);

	if (this == &other) return true;

	if (m_qname == nullptr || other.m_qname == nullptr)
	{
		raise(SystemException(L"ClassType::qname nullptr"));
	}
	ASSERT(*m_qname == *other.m_qname);

	if (m_pTemplateParams)
	{
		if (other.m_pTemplateParams == nullptr)
		{
			ASSERT(0);
			return false;
		}

		m_pTemplateParams->Equals(*other.m_pTemplateParams);
	}
	else if (other.m_pTemplateParams)
	{
		ASSERT(0);
		return false;
	}

	if (!m_def) return true;

	// Special hacks for now
	/*
	if (*m_name == "COFFParser")
	{
		return true;
	}
	*/

	if (m_name == L"ExprResult")
	{
		return true;
	}

	if (m_sizeof != other.m_sizeof)
	{
		VERIFY(0);
	}

	if (m_name == L"CPoolItem")
	{
		return true;
	}

	if (m_name == L"x86addr")
	{
		return true;
	}

	if (m_name == L"x86instr")
	{
		return true;
	}

	/*
	if (*m_name == "ElementTimeImplImpl")
	{
		return true;
	}
	*/

	/*
	if (*m_name != *other.m_name)
		return false;
		*/

	/*
	// If one of them is a forward declaration just return true
	if (m_bVT == -1)	return true;
	if (other.m_bVT == -1) return true;
	*/

	if (m_bases.GetSize() != other.m_bases.GetSize())
		return false;

	{
		{
		// These are legal
			for (size_t i = 1; i < m_bases.GetSize(); ++i)
			{
				if (m_bases[i]->m_offset < m_bases[i-1]->m_offset)
				{
					MessageBeep(-1);
				}
			}
		}

		{
		// These are legal
			for (size_t i = 1; i < m_bases.GetSize(); ++i)
			{
				if (other.m_bases[i]->m_offset < other.m_bases[i-1]->m_offset)
				{
					MessageBeep(-1);
				}
			}
		}

		for (size_t i = 0; i < m_bases.GetSize(); ++i)
		{
			if (m_bases[i]->m_pClass->AsClass())
			{
				if (m_bases[i]->m_pClass->AsClass()->m_sizeof != other.m_bases[i]->m_pClass->AsClass()->m_sizeof)
				{
					MessageBeep(-1);
					//return false;
				}

				if (m_bases[i]->m_offset != other.m_bases[i]->m_offset)
				{
					MessageBeep(-1);
					//return false;
				}
				/*
				if (!m_bases[i].m_pClass->Equals(*other.m_bases[i].m_pClass))
					return false;
					*/
			}
		}
	}

	// Hack
	if (m_name == L"A_Exp")
	{
		return true;
	}

	if (m_name == L"T_Stm")
	{
		return true;
	}

	if (m_name == L"T_Exp")
	{
		return true;
	}

	if (m_name == L"Tr_Exp")
	{
		return true;
	}

	if (m_name == L"F_access")
	{
		return true;
	}

	if (m_name == L"NodeTest")
	{
		return true;
	}

	if (m_name == L"_IMAGE_RELOCATION")
	{
		return true;
	}

	if (m_name == L"OMFDirHeader")
	{
		return true;
	}

	if (m_name == L"OMFDirEntry")
	{
		return true;
	}

	if (m_name == L"OMFModule")
	{
		return true;
	}

	if (m_name == L"OMFSegMapDesc")
	{
		return true;
	}

	if (m_name == L"CV_PROCFLAGS")
	{
		return true;
	}

	size_t ndecls = m_pScope->m_orderedDecls.GetSize();
	size_t otherndecls = other.m_pScope->m_orderedDecls.GetSize();

	{
		size_t i = 0;
		size_t j = 0;

		while (i < ndecls && j < otherndecls)
		{
			while (m_pScope->m_orderedDecls[i]->m_pType->get_Kind() == type_function ||
					m_pScope->m_orderedDecls[i]->m_typedef ||
					m_pScope->m_orderedDecls[i]->m_static)
			{
				i++;
				if (i == ndecls) break;
			}

			while (other.m_pScope->m_orderedDecls[j]->m_pType->get_Kind() == type_function ||
					other.m_pScope->m_orderedDecls[j]->m_typedef ||
					other.m_pScope->m_orderedDecls[j]->m_static)
			{
				j++;
				if (j == otherndecls) break;
			}

			if ((i == ndecls) != (j == otherndecls))
			{
				return false;
			}

			if (i == ndecls)
				break;

			// Hack
			if (other.m_pScope->m_orderedDecls[j] == NULL)	// unnamed struct/union
				return true;

			if (!m_pScope->m_orderedDecls[i]->Equals(*other.m_pScope->m_orderedDecls[j]))
			{
				m_pScope->m_orderedDecls[i]->Equals(*other.m_pScope->m_orderedDecls[j]);
				return false;
			}

			i++;
			j++;
		}
	}

	// ? There seems to be a bug in codeview debug info, consecutive virtual functions with the same name get the same offset

	if (m_qname == L"System::LDraw::Graphics2D")
	{
		// Has lots of virtual methods with same name
		return true;
	}

	if (m_qname == L"System::LDraw::Graphics3D")
	{
		// Has lots of virtual methods with same name
		return true;
	}

	// ???
	/*
	if (*m_qname == L"System::Web::PSVGElement")
	{
	//	MessageBeep(-1);
		return true;
	}
	*/

	/*
	if (*m_name == "AOutParser")
	{
		MessageBeep(-1);
	}
	*/

#if 0
	{
		DebugTrace("-- %s --\n", m_name->c_str());
		for (int i = 0; i < ndecls; i++)
		{
			if (m_pScope->m_orderedDecls[i]->m_pType->get_Kind() == type_function/* &&
				m_pScope->m_orderedDecls[i]->m_virtual*/)
			{
				TRACE("%s - %d\n", m_pScope->m_orderedDecls[i]->m_name->c_str(), m_pScope->m_orderedDecls[i]->m_offset);
			}
		}
	}

	{
		for (int i = 0; i < otherndecls; i++)
		{
			if (other.m_pScope->m_orderedDecls[i]->m_pType->get_Kind() == type_function/* &&
				other.m_pScope->m_orderedDecls[i]->m_virtual*/)
			{
				TRACE("%s - %d\n", other.m_pScope->m_orderedDecls[i]->m_name->c_str(), other.m_pScope->m_orderedDecls[i]->m_offset);
			}
		}
	}
	TRACE("\n");
#endif

	{
		unsigned int i = 0;
		unsigned int j = 0;

		while (i < ndecls && j < otherndecls)
		{
			while (m_pScope->m_orderedDecls[i]->m_pType->get_Kind() != type_function ||
				//!m_pScope->m_orderedDecls[i]->m_virtual ||
				m_pScope->m_orderedDecls[i]->m_offset == -1 ||
				m_pScope->m_orderedDecls[i]->m_name == L"__vecDelDtor")
			{
				i++;
				if (i == ndecls) break;
			}

			while (other.m_pScope->m_orderedDecls[j]->m_pType->get_Kind() != type_function ||
				other.m_pScope->m_orderedDecls[j]->m_offset == -1
					/*!other.m_pScope->m_orderedDecls[j]->m_virtual*/)
			{
				j++;
				if (j == otherndecls) break;
			}

			if ((i == ndecls) != (j == otherndecls))
			{
				return true;//false;
			}

			if (i == ndecls)
				break;

			if (*m_pScope->m_orderedDecls[i]->m_name != *other.m_pScope->m_orderedDecls[j]->m_name)
				return true;//false;

			if (m_pScope->m_orderedDecls[i]->m_offset != other.m_pScope->m_orderedDecls[j]->m_offset)
				return true;//false;

			/*
			// Hack
			if (other.m_pScope->m_orderedDecls[j] == NULL)	// unnamed struct/union
				return true;

			if (!m_pScope->m_orderedDecls[i]->Equals(*other.m_pScope->m_orderedDecls[j]))
			{
				m_pScope->m_orderedDecls[i]->Equals(*other.m_pScope->m_orderedDecls[j]);
				return false;
			}
			*/

			i++;
			j++;
		}
	}

	/*
	if (ndecls != otherndecls)
	{
		for (int i = 0; i < m_pScope->m_orderedDecls.GetSize(); i++)
		{
			StringA str = m_pScope->m_orderedDecls[i]->m_pDeclarator->ToString();
			printf("%s\n", str.c_str());
		}

		printf("\n\n");

		for (i = 0; i < other.m_pScope->m_orderedDecls.GetSize(); i++)
		{
			StringA str = other.m_pScope->m_orderedDecls[i]->m_pDeclarator->ToString();
			printf("%s\n", str.c_str());
		}

		return false;
	}

	// Check individual members
	for (int i = 0; i < m_pScope->m_orderedDecls.GetSize(); i++)
	{
		if (!m_pScope->m_orderedDecls[i]->m_pDeclarator->Equals(*other.m_pScope->m_orderedDecls[i]->m_pDeclarator))
		{
			StringA str1 = m_pScope->m_orderedDecls[i]->m_pDeclarator->ToString();
			StringA str2 = other.m_pScope->m_orderedDecls[i]->m_pDeclarator->ToString();

			return false;
		}
	}
	*/

#if 0
	for (int i = 0; i < m_members.size(); i++)
	{
		if (!m_members[i]->IsEqual(pOther->m_members[i]))
			return FALSE;
	}
#endif


	return true;	// They're equal
}

#if 0
Scope* ClassType::GetScope(const char* name)
{
	Scope* pScope = m_pScope->GetScope2(name);
	if (pScope)
	{
		return pScope;
	}

	for (int i = 0; i < m_bases.GetSize(); i++)
	{
		Scope* pScope = m_bases[i]->m_pClass->GetClass()->GetScope(name);
		if (pScope)
		{
			return pScope;
		}
	}

	if (m_pScope->m_pParentScope)
	{
		return m_pScope->m_pParentScope->GetScope(name);
	}
	return NULL;
}
#endif

Object* ClassType::GetUserData(StringIn key) const
{
	if (key == L"System::Gui::DependencyClass")
	{
		return m_classUserData[0];
	}
	else if (key == L"System::x3d::NodeType")
	{
		return m_classUserData[1];
	}
	else
	{
		ASSERT(0);
		return NULL;
	}
}

void ClassType::SetUserData(StringIn key, Object* data)
{
	if (key == L"System::Gui::DependencyClass")
	{
		m_classUserData[0] = data;
	}
	else if (key == L"System::x3d::NodeType")
	{
		m_classUserData[1] = data;
	}
	else
	{
		ASSERT(0);
	}
}

int ClassType::GetOffset(const ClassType* pClass) const
{
	for (size_t i = 0; i < m_bases.GetSize(); ++i)
	{
		BaseClass* baseclass = m_bases[i];

		VERIFY(baseclass->m_pClass->AsClass() != nullptr);

		if (baseclass->m_pClass->AsClass() == pClass)
		{
			return baseclass->m_offset;
		}

		int offset = baseclass->m_pClass->AsClass()->GetOffset(pClass);
		if (offset != -1)
		{
			return baseclass->m_offset + offset;
		}
	}

	return -1;
}

bool ClassType::IsOfType(Type* pType) const
{
	if (pType->get_Kind() != type_class) return false;

	ClassType* pClass = pType->AsClass();

	return IsDerivedFrom(pClass);
}

bool ClassType::IsDerivedFrom(ClassType* pType) const
{
	ClassType* pClass = pType;
	if (this == pClass) return true;

	if (this == NULL) return false;
	VerifyArgumentNotNull(pType);

	for (size_t i = 0; i < m_bases.GetSize(); ++i)
	{
		BaseClass* baseclass = m_bases[i];

		ASSERT(baseclass->m_pClass);
		if (baseclass->m_pClass->AsClass()->IsDerivedFrom(pClass))
			return true;
	}

	return false;
}

bool ClassType::IsLeftMostDerivedFrom(ClassType* pType) const
{
	const ClassType* pThis = this;

	while (pThis != pType)
	{
		if (pThis->m_bases.size() == 0) return false;
		pThis = pThis->m_bases[0]->m_pClass->AsClass();
		ASSERT(pThis);
	}

	return true;
}

Declarator* ClassType::GetMemberByOffset(unsigned int offset)
{
	for (size_t i = 0; i < m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* decl = m_pScope->m_orderedDecls[i];
		Type* pType = decl->get_Type()->GetStripped();
		if (!decl->get_IsStatic() && pType->get_Kind() != type_function)
		{
			if (decl->m_offset == offset)
			{
				return decl;
			}
		}
	}

	for (size_t i = 0; i < m_bases.size(); ++i)
	{
		Declarator* decl = dynamic_cast<ClassType*>(m_bases[i]->m_pClass)->GetMemberByOffset(offset);
		if (decl) return decl;
	}

	return nullptr;
}

Type* ClassType::LookupType(StringIn name) const
{
	if (false)
	{
		typemap::iterator it = m_pScope->m_types.find(name);
		if (it != m_pScope->m_types.end())
		{
			return (*it).second;
		}
	}
	else
	{
		for (size_t i = 0; i < m_pScope->m_orderedDecls.GetSize(); ++i)
		{
			Declarator* pDeclarator = m_pScope->m_orderedDecls[i];

			if (pDeclarator->m_typedef)
			{
				if (pDeclarator->m_name == name)
				{
					return pDeclarator->m_pType;
				}
			}
		}
	}

	return nullptr;
#if 0
	typemap::iterator it = m_pScope->m_types.find(name);
	if (it != m_pScope->m_types.end())
	{
		return (*it).second;
	}

	for (i = 0; i < m_bases.GetSize(); i++)
	{
		Type* pType;
		if (m_bases[i].m_pClass->m_type == type_class)
		{
			pType = m_bases[i].m_pClass->AsClass()->LookupType(name);
		}

	}
	return nullptr;
#endif
}

Declarator* ClassType::GetDeclarator(StringIn name)
{
	// Search through the nameless member unions first
	for (size_t i = 0; i < m_pScope->m_orderedDecls.GetSize(); ++i)
	{
		Declarator* pDeclarator = m_pScope->m_orderedDecls[i];

		if (pDeclarator->m_name.GetLength() == 0)	// Recurse into unnamed class
		{
			if (pDeclarator->m_pType->GetStripped()->get_Kind() == type_class)
			{
				ASSERT(0);
#if 0
				CDeclaratorReference* pDeclarator2 = pDeclarator->m_pDeclarator->m_pType->GetType()->m_pClass->GetDeclarator(name);
				if (pDeclarator2)
				{
					return pDeclarator2;
				}
#endif
			}
		}
	}

	Declarator* pDeclarator = m_pScope->GetDeclarator(name);
	if (pDeclarator)
	{
		return pDeclarator;
	}

	for (uint i = 0; i < m_bases.GetSize(); ++i)
	{
		Declarator* pDeclarator = m_bases[i]->m_pClass->AsClass()->GetDeclarator(name);
		if (pDeclarator)
		{
			return pDeclarator;
		}
	}

	return nullptr;
}

Type* ClassType::Clone() const
{
	ClassType* pClass = new ClassType();

#if 0
	for (int i = 0; i < m_members.size(); i++)
	{
		CMember* pMember2 = new CMember;
		pMember2->m_offset = m_members[i]->m_offset;
		pMember2->m_pDeclarator = m_members[i]->m_pDeclarator;

		pClass->m_members.push_back(pMember2);
	}
#endif

	pClass->m_name = m_name;
	pClass->m_sizeof = m_sizeof;
	pClass->m_kwType = m_kwType;
	pClass->m_pScope = m_pScope;

	return pClass;
}

LFCEXT vector<BaseClass*>& bases(ClassType* pClass)
{
	return pClass->m_bases;
}

LFCEXT vector<ClassType*>& derived(ClassType* pClass)
{
	return pClass->m_derived;
}

LFCEXT void CalcGCMembers(ClassType* pTopClass, ClassType* pClass, size_t& count, size_t& innercount, size_t& arraycount)
{
	if (pClass->m_sizeof == ~0)	// TODO remove
		return;

	ASSERT(pClass->m_sizeof != ~0);
	ASSERT(pClass->m_def);

	size_t nsize = pClass->m_pScope->m_orderedDecls.size();
	Declarator** declrefs = pClass->m_pScope->m_orderedDecls.begin();

	for (size_t i = 0; i < nsize; ++i)
	{
		Declarator* decl = (*declrefs);

		Type *pType = decl->m_pType->GetStripped();

		if (pType->get_Kind() != type_function &&
			decl->m_offset != -1 &&
			!decl->get_IsStatic())
		{
			if (pType->get_Kind() == type_class)	// embedded class (process subfields)
			{
				ClassType* pClass = static_cast<ClassType*>(pType);

				ASSERT(pClass->m_kwType == ClassKey_class || pClass->m_kwType == ClassKey_struct || pClass->m_kwType == ClassKey_union || pClass->m_kwType == ClassKey_interface);

				if (pClass->m_kwType != ClassKey_union)
				{
					if (pClass->m_qname &&
						(pClass->m_qname.BeginsWith("System::vector<") ||	// special cases
						pClass->m_qname.BeginsWith("System::array<")))
					{
						Declarator* pdatadecl = pClass->m_pScope->m_orderedDecls[0];
						ASSERT(pdatadecl->m_name == "m_pData");

						Type* pElemType = pdatadecl->m_pType->GetStripped();

						ASSERT(pElemType->get_Kind() == type_pointer);

						//if (pElemType->m_type == type_pointer)
						{
							Type* pType = pElemType->GetPointerTo()->GetStripped();
							/*
							GCMember member;// = new GCMember;
							//member.m_bArray = true;
							member.m_offset = offset + decl->m_offset;
							member.m_pType = pType;
							pTopClass->m_gcArrayMembers.push_back(member);
							*/
							++arraycount;
						}
					}
					else if (pClass->m_qname && pClass->m_qname.BeginsWith("System::inner_ptr<"))	// special case for inner_ptr
					{
						/*
						pType = pType->GetPointerTo()->GetStripped();

						if (pType->get_Kind() == type_class && pType->GetClass()->HasVirtualTable())	// pointer to dynamic class
						{
							ClassType* pClass = (ClassType*)pType;
						}
						*/

						++innercount;
					}
					else
					{
						CalcGCMembers(pTopClass, pClass, count, innercount, arraycount);//offset + decl->m_offset);
					}
				}
				else	// Union
				{
					// gc if all members are polymorphic pointers
					bool nogo = false;

					ASSERT(pClass->m_pScope->m_orderedDecls.size());

				//	ASSERT(pClass->m_kwType == ClassKey_class || pClass->m_kwType == ClassKey_struct || pClass->m_kwType == ClassKey_union || pClass->m_kwType == ClassKey_interface);

					for (size_t i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
					{
						Declarator* decl = pClass->m_pScope->m_orderedDecls[i];
						Type *pType = decl->m_pType->GetStripped();

						if (pType->get_Kind() != type_pointer)
						{
							nogo = true;
							break;
						}

						if (pType->GetPointerTo()->GetStripped()->get_Kind() != type_class)
						{
							nogo = true;
							break;
						}

						if (!pType->GetPointerTo()->GetStripped()->AsClass()->HasVirtualTable())
						{
							nogo = true;
							break;
						}
					}

					if (!nogo)
					{
					//	ASSERT(pClass->m_kwType == ClassKey_class || pClass->m_kwType == ClassKey_struct || pClass->m_kwType == ClassKey_union || pClass->m_kwType == ClassKey_interface);

						ASSERT(pClass->get_sizeof() == sizeof(void*));
						count++;
					}
				}
			}
			else if (pType->get_Kind() == type_array)
			{
				ArrayType* pArrayType = static_cast<ArrayType*>(pType);

				Type* elemType = pArrayType->get_ElemType();

				if (elemType->get_Kind() == type_pointer &&
					elemType->GetPointerTo()->get_Kind() == type_class &&
					elemType->GetPointerTo()->AsClass()->HasVirtualTable())
				{
					size_t nelems = pArrayType->get_ElemCount();
					count += nelems;

#if 0
					for (int i = 0; i < nelems; i++)
					{
						count++;
						/*
						GCMember member;// = new GCMember;
					//	member.m_bArray = false;
						member.m_offset = offset + decl->m_offset + i*sizeof(void*);
						member.m_pType = pArrayType->m_pElemType->GetPointerTo();
						pTopClass->m_gcMembers.push_back(member);
						*/
					}
#endif
				}
				else if (elemType->get_Kind() == type_class)
				{
					ClassType* pClass = static_cast<ClassType*>(elemType);

					size_t nelems = pArrayType->get_ElemCount();

					size_t count_ = 0;
					size_t innercount_ = 0;
					size_t arraycount_ = 0;

					CalcGCMembers(pTopClass, pClass, count_, innercount_, arraycount_);

					count += count_ * nelems;
					innercount += innercount_ * nelems;
					arraycount += arraycount_ * nelems;

					/*
					for (int i = 0; i < nelems; i++)
					{
						//unsigned int offset2 = offset + decl->m_offset + i*pClass->get_sizeof();

					}
					*/
				}
			}
			else if (pType->get_Kind() == type_pointer)
			{
				pType = pType->GetPointerTo()->GetStripped();

				if (pType->get_Kind() == type_class && pType->AsClass()->HasVirtualTable())	// pointer to polymorphic/dynamic class
				{
					ClassType* pClass = static_cast<ClassType*>(pType);

					//if (pClass->m_kwType != CLASSKEY_UNION)
					{
						++count;
						/*
						GCMember member;// = new GCMember;
						//member.m_bArray = false;
						member.m_offset = offset + decl->m_offset;
						member.m_pType = pType;
						pTopClass->m_gcMembers.push_back(member);
						*/
					}
				}
				else //if (pType->GetKind() != type_class) || pType->GetClass()->m_bVT == 0)
				{
					count++;
					/*
					GCMember member;// = new GCMember;
					//member.m_bArray = false;
					member.m_offset = offset + decl->m_offset;
					member.m_pType = pType;
					pTopClass->m_gcMembers.push_back(member);
					*/
				}
			}
		}

		++declrefs;
	}

	for (size_t i = 0; i < pClass->m_bases.size(); ++i)
	{
		BaseClass * baseclass = pClass->m_bases[i];
		CalcGCMembers(pTopClass, baseclass->m_pClass->AsClass(), count, innercount, arraycount);
	}
}

LFCEXT void MakeGCMembers(ClassType* pTopClass, ClassType* pClass, ptrdiff_t offset, size_t& count, size_t& innercount, size_t& arraycount)
{
	if (pClass->m_sizeof == ~0)	// TODO remove
		return;

	/*
	if (pClass->m_qname.LeftOf(9) == "template ")
	{
		return;
	}
	*/

	ASSERT(pClass->m_sizeof != ~0);
	ASSERT(pClass->m_def);

	size_t nsize = pClass->m_pScope->m_orderedDecls.size();
	Declarator** declrefs = pClass->m_pScope->m_orderedDecls.begin();

	for (size_t i = 0; i < nsize; ++i)
	{
		Declarator* decl = (*declrefs);

		Type *pType = decl->m_pType->GetStripped();

		if (pType->get_Kind() != type_function &&
			decl->m_offset != ~0 &&
			!decl->get_IsStatic())
		{
			if (pType->get_Kind() == type_class)	// embedded class (process subfields)
			{
				ClassType* pClass = (ClassType*)pType;

				if (pClass->m_kwType != ClassKey_union)
				{
					if (pClass->m_qname &&
						(pClass->m_qname.BeginsWith("System::vector<") ||	// special case for Array
						pClass->m_qname.BeginsWith("System::array<")))
					{
						Declarator* pdatadecl = pClass->m_pScope->m_orderedDecls[0];//->m_pDeclarator;
						ASSERT(pdatadecl->m_name == "m_pData");

						Type* pElemType = pdatadecl->m_pType->GetStripped();

						ASSERT(pElemType->get_Kind() == type_pointer);

						//if (pElemType->m_type == type_pointer)
						{
							Type* pType = pElemType->GetPointerTo()->GetStripped();
							/*
							if (pType->m_type == type_pointer)	// pointer to pointer
							{
								pType = pType->GetPointerTo()->GetType();
								if (pType->m_type == type_class)	// pointer to pointer to class
								{
									ClassType* pClass = (ClassType*)pType;

									//if (pClass->m_bVT == 1)	// dynamic class
									{
									*/
										GCArrayMember member;// = new GCMember;
										//member.m_bArray = true;
										member.m_offset = offset + decl->m_offset;
										member.m_pType = pType;
										//pTopClass->m_gcArrayMembers.push_back(member);
										pTopClass->m_gcArrayMembers[arraycount++] = member;

										/*
										for (int i = 0; i < pArray->size(); i++)
										{
											void * childpointer = ((void**)pArray->m_pData)[i];
											if (childpointer)
											{
												ClassType* pMostDerivedClass = GetType(childpointer);

											//	if (pMostDerivedClass->IsDerivedFrom(m_pObjectClass))
												{
												//	TRACE("type of %s\n", pMostDerivedClass->m_qname->c_str());

												//	Object* childobject = (Object*)DynamicCast(childpointer, pType, m_pObjectClass);
#if WIN32
													Object* childobject = (Object*)__RTDynamicCast(childpointer, 0, (void*)&typeid(childpointer), (void*)&typeid(System::Object), 0);
#else
#endif
													if (childobject)
													{
														mark_dfs(childobject, pMostDerivedClass);
													}
												}
											}
										}
										*/
						//			}
						//		}
						//	}
						}
					}
					else if (pClass->m_qname && pClass->m_qname.BeginsWith("System::inner_ptr<")	)// special case for Array
					{
						Declarator* ptrdecl = pClass->m_pScope->m_orderedDecls[0];

						Type* pType = ptrdecl->m_pType->GetPointerTo()->GetStripped();

					//	ASSERT(pType->GetClass() == NULL || pType->get_sizeof() != -1);

						if (pType->get_Kind() == type_class && pType->AsClass()->HasVirtualTable())	// pointer to dynamic class
						{
							int kind = 0;

							GCMember member;
							member.m_offset_and_kind = ((offset + decl->m_offset)<<1) | kind;
						//	pTopClass->m_gcInnerMembers.push_back(member);
							pTopClass->m_gcInnerMembers[innercount++] = member;
						}
						else
						{
							int kind = 1;

							GCMember member;
							member.m_offset_and_kind = ((offset + decl->m_offset)<<1) | kind;
						//	pTopClass->m_gcInnerMembers.push_back(member);
							pTopClass->m_gcInnerMembers[innercount++] = member;
						}
					}
					else
					{
						MakeGCMembers(pTopClass, pClass, offset + decl->m_offset, count, innercount, arraycount);
					}
				}
				else
				{
					// gc if all members are polymorphic pointers
					bool nogo = false;

					ASSERT(pClass->m_pScope->m_orderedDecls.size());

					for (unsigned int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
					{
						Declarator* decl = pClass->m_pScope->m_orderedDecls[i];
						Type *pType = decl->m_pType->GetStripped();

						if (pType->get_Kind() != type_pointer)
						{
							nogo = true;
							break;
						}

						if (pType->GetPointerTo()->GetStripped()->get_Kind() != type_class)
						{
							nogo = true;
							break;
						}

						if (!pType->GetPointerTo()->GetStripped()->AsClass()->HasVirtualTable())
						{
							nogo = true;
							break;
						}
					}

					if (!nogo)
					{
						ASSERT(pClass->get_sizeof() == sizeof(void*));

						int kind = 0;

						GCMember member;// = new GCMember;
						//member.m_bArray = false;
						member.m_offset_and_kind = ((offset + decl->m_offset)<<1) | kind;
					//	member.m_pType = pType;
					//	pTopClass->m_gcMembers.push_back(member);
						pTopClass->m_gcMembers[count++] = member;
					}
				}
			}
			else if (pType->get_Kind() == type_array)
			{
				ArrayType* pArrayType = (ArrayType*)pType;

				if (pArrayType->m_pElemType->get_Kind() == type_pointer &&
					pArrayType->m_pElemType->GetPointerTo()->get_Kind() == type_class &&
					pArrayType->m_pElemType->GetPointerTo()->AsClass()->HasVirtualTable())
				{
					size_t nelems = pArrayType->get_ElemCount();
					for (uint i = 0; i < nelems; i++)
					{
						GCMember member;// = new GCMember;
						size_t offset2 = offset + decl->m_offset + i*sizeof(void*);
						int kind = 0;
					//	member.m_bArray = false;
						member.m_offset_and_kind = (offset2<<1) | kind;
					//	member.m_pType = pArrayType->m_pElemType->GetPointerTo();
					//	pTopClass->m_gcMembers.push_back(member);
						pTopClass->m_gcMembers[count++] = member;
					}
				}
				else if (pArrayType->m_pElemType->get_Kind() == type_class)
				{
					ClassType* pClass = (ClassType*)pArrayType->m_pElemType;

					size_t nelems = pArrayType->get_ElemCount();
					for (uint i = 0; i < nelems; i++)
					{
						size_t offset2 = offset + decl->m_offset + i*pClass->get_sizeof();

						MakeGCMembers(pTopClass, pClass, offset2, count, innercount, arraycount);
						/*
						GCMember member;// = new GCMember;
						int kind = 0;
					//	member.m_bArray = false;
						member.m_offset_and_kind = (offset2<<1) | kind;
					//	member.m_pType = pArrayType->m_pElemType->GetPointerTo();
						pTopClass->m_gcMembers.push_back(member);
						*/
					}
				}
			}
			else if (pType->get_Kind() == type_pointer)
			{
				pType = pType->GetPointerTo()->GetStripped();

			//	ASSERT(pType->GetClass() == NULL || pType->get_sizeof() != -1);

				if (pType->get_Kind() == type_class && pType->AsClass()->HasVirtualTable())	// pointer to dynamic class
				{
					ClassType* pClass = (ClassType*)pType;

					//if (pClass->m_kwType != CLASSKEY_UNION)
					{
						int kind = 0;

						GCMember member;// = new GCMember;
						//member.m_bArray = false;
						member.m_offset_and_kind = ((offset + decl->m_offset)<<1) | kind;
					//	member.m_pType = pType;
					//	pTopClass->m_gcMembers.push_back(member);
						pTopClass->m_gcMembers[count++] = member;
					}
				}
				else //if (pType->GetKind() != type_class) || pType->GetClass()->m_bVT == 0)
				{
					int kind = 1;

					GCMember member;// = new GCMember;
					//member.m_bArray = false;
					member.m_offset_and_kind = ((offset + decl->m_offset)<<1) | kind;
				//	member.m_pType = pType;
				//	pTopClass->m_gcMembers.push_back(member);
					pTopClass->m_gcMembers[count++] = member;
				}
			}
		}

		++declrefs;
	}

	for (size_t i = 0; i < pClass->m_bases.size(); ++i)
	{
		BaseClass* baseclass = pClass->m_bases[i];
		MakeGCMembers(pTopClass, baseclass->m_pClass->AsClass(), offset + baseclass->m_offset, count, innercount, arraycount);
	}
}

ClassType* ClassType::InstantiateTemplate(ActualTemplateArgs* args)
{
	ClassType* p = new ClassType;
	p->m_pInstantiatedFromClass = this;
	p->m_pInstantiatedFromArgs = args;
	p->m_pInstantiatedFromClass = this;
	p->m_bVT = m_bVT;
	p->m_def = true;
	p->m_kwType = m_kwType;
	p->m_name = m_name;
	p->m_qname = p->ToString();

	return p;
}

String ClassType::ToString()
{
	IO::StringWriter strbuilder;
	Write(strbuilder);
	return strbuilder.str();
}

IO::TextWriter& ClassType::Write(IO::TextWriter& stream) const
{
#if 0
	stream << ClassKeyName((ClassKey)m_kwType);
	stream << " ";
#endif

	if (m_pTemplateParams)
	{
	//	ASSERT(m_pInstantiatedFrom == NULL);
	//	ASSERT(m_pInstantiatedFromClass == NULL);

		stream << "template ";

		if (m_ownerScope && m_ownerScope->m_pNamespace->m_name)
		{
			ASSERT(m_ownerScope->m_pNamespace);
			GetQualifiedName(m_ownerScope, stream);
			stream << "::";
		}

		if (m_name)
			stream << m_name;
		else
			stream << "(null)";

		stream << "<";

		for (uint i = 0; i < m_pTemplateParams->m_items.size(); ++i)
		{
			TemplateParameter* param = m_pTemplateParams->m_items[i];

			if (i > 0)
			{
				stream << ",";
			}

			if (param->m_kind == TemplateParameter::Param_Type)
				stream << "class";
			else
				stream << "int";	// TODO
		}

		stream << ">";
	}
	else
	{
		if (m_ownerScope && m_ownerScope->m_pNamespace->m_name)
		{
			ASSERT(m_ownerScope->m_pNamespace);
			GetQualifiedName(m_ownerScope, stream);
			stream << "::";
		}

		if (m_name)
			stream << m_name;
		else
			stream << "(null)";
	}

	if (m_pInstantiatedFromArgs)
	{
#if 0
		ASSERT(m_pInstantiatedFromClass == m_pInstantiatedFrom->m_pClass);
#endif

		ASSERT(m_pInstantiatedFromClass->m_pTemplateParams);

		if (m_pInstantiatedFromClass->m_pTemplateParams)
		{
			stream << "<";

			ASSERT(m_pInstantiatedFromClass->m_pTemplateParams->m_items.size() >= m_pInstantiatedFromArgs->m_items.size()/* ||
				m_pClass->m_items.size() == 0*/);

			Type* pType = NULL;

			for (size_t i = 0; i < m_pInstantiatedFromArgs->m_items.size(); ++i)
			{
				if (i > 0) stream << ",";

				if (m_pInstantiatedFromClass->m_pTemplateParams->m_items[i]->m_kind == TemplateParameter::Param_Type)
				{
					pType = m_pInstantiatedFromArgs->m_items[i]->m_pType;
					if (pType)
					{
						VERIFY(pType);

						while (pType->get_Kind() == type_typedef)
						{
							pType = static_cast<Typedef*>(pType)->m_pType;
							VERIFY(pType);
						}

						pType->Write(stream);
					}
				}
				else
				{
					pType = NULL;
					stream << m_pInstantiatedFromArgs->m_items[i]->m_value;
				}
			}

			if (pType)
			{
				// TODO
				/*
				if (pType->get_Kind() == type_class && pType->GetClass()->m_pInstantiatedFrom)
					stream << " >";
				else
					*/
					stream << ">";
			}
			else
			{
				stream << ">";
			}
		}
	}

	return stream;
}

// static
ClassType* ClassType::CreateFromArchive(TypeArchive& ar, uint32 id)
{
	ClassType* p = new ClassType;
	if (ar.m_typeLoad.size() <= id) ar.m_typeLoad.resize(id+1);
	ar.m_typeLoad[id] = p;
	p->Load(ar);
	return p;

	String qname;

	bool hasqname;
	ar >> hasqname;

	if (hasqname)
	{
		ar >> qname;
	}

	/*
	if (*qname == "System::UI::Border")
	{
		MessageBeep(-1);
	}
	*/

	TypeLib* typelib;
	ar >> typelib;

	if (typelib != ar.m_typelib)
	{
		// Recursively load the typelibrary
		if (true)//ar.m_recurseLoadTypelibs)
		{
			return (ClassType*)NamedType::CreateFromArchive(ar, id, typelib, qname);
		}
		else
		{
			ClassType* pobj = new ClassType;
	//		ar.m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pobj));
			ar.m_typeLoad.push_back(pobj);
			ASSERT(ar.m_typeLoad.size() == id);

			pobj->m_typelib = typelib;
			pobj->m_qname = qname;
		//pobj->Load(ar);

			return pobj;
		}
	}
	else
	{
		ClassType* pobj = new ClassType;
//		ar.m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pobj));
		if (ar.m_typeLoad.size() < id+1) ar.m_typeLoad.resize(id+1);
		ar.m_typeLoad[id] = pobj;
	//	ASSERT(ar.m_typeLoad.size() == id);

		pobj->m_qname = qname;
		pobj->Load(ar);

		return pobj;
	}
}

void ClassType::Load(TypeArchive& ar)
{
	NamespaceType::Load(ar);

	if (m_qname == "System::Gui::Element" || m_qname == "System::Style::ICSSElementResolver")
	{
//		__asm int 3
	}

	/*
	bool hasqname;
	ar >> hasqname;
	if (hasqname)
	{
		m_qname = new StringA;
		ar >> *m_qname;
	}
	*/

	ar >> m_pInstantiatedFromClass;

	{
		bool bTemplated;
		ar >> bTemplated;

		if (bTemplated)
		{
			m_pInstantiatedFromArgs = new TemplatedClassArgs;
			m_pInstantiatedFromArgs->Load(ar);

#if 0
			m_pInstantiatedFromArgs->m_pClass = m_pInstantiatedFromClass;
#endif
		}
		else
		{
			m_pInstantiatedFromArgs = NULL;
		}
	}

	{
		bool bTemplatedArgs;
		ar >> bTemplatedArgs;

		if (bTemplatedArgs)
		{
			/*
			if (*m_name == "Vector")
			{
				MessageBeep(-1);
			}
			*/

			uint16 ntemplateargs;
			ar >> ntemplateargs;

			/*
			if (m_pInstantiatedFrom == NULL)
			{
				if (*m_name == "StringT")
				{
					ASSERT(ntemplateargs == 1);
				}
			}
			*/

			m_pTemplateParams = new FormalTemplateArgs;

			m_pTemplateParams->m_items.reserve(ntemplateargs);

			for (uint i = 0; i < ntemplateargs; ++i)
			{
				FormalTemplateArg* p = new FormalTemplateArg;
				//_TemplateArgType* pType;
				ar >> *(int*)&p->m_kind;
				if (p->m_kind == TemplateParameter::Param_Type)
				{
					ar >> p->u.m_pType;
				}
				//ar >> p->m_pDeclarator;
				m_pTemplateParams->m_items.push_back(p);
			}
		}
	}

	/*
	if (m_pTemplateParams == NULL)
	{
		BufferImp<char> buffer;
		StringBuilderA strbuilder = StringBuilderA(&buffer);
		Write(strbuilder);
		m_qname = buffer.DetachToString();
	}
	*/

	uint8 kwType;
	ar >> kwType;
	VERIFY(kwType == ClassKey_class || kwType == ClassKey_struct || kwType == ClassKey_union || kwType == ClassKey_interface);
	m_kwType = (ClassKey)kwType;

	ar >> m_sizeof;
	ar >> m_rsizeof;
	ar >> m_packing;
	ar >> m_alignment;
	ar >> m_force_alignment;
	ar >> m_virtualSize;

	uint8 flags;
	ar >> flags;
	m_bVT = flags & 1;
	m_def = (flags >> 1) & 1;

	{
		uint8 byteval;
		ar >> byteval;

		unsigned int nbases = byteval;

		m_bases.reserve(nbases);

		for (unsigned int i = 0; i < nbases; i++)
		{
			BaseClass* baseclass = new BaseClass;
			ar >> baseclass->m_offset;

			NamedType* pBaseType;
			ar >> pBaseType;

			m_bases.push_back(baseclass);

			baseclass->m_pClass = pBaseType;//dynamic_cast<ClassType*>(pBaseType);

			/*
			if (dynamic_cast<ClassType*>(pBaseType) == NULL)
			{
				MessageBeep(-1);
			}
			*/

			ASSERT(baseclass->m_pClass);

			if (baseclass->m_pClass->AsClass())
			{
				baseclass->m_pClass->AsClass()->m_derived.push_back(this);
			}
		}
	}

	{
		unsigned int ndecls;
		ar >> ndecls;

		m_pScope->m_orderedDecls.reserve(ndecls);

		bool bMember = get_Kind() == type_class;

		for (unsigned int i = 0; i < ndecls; ++i)
		{
			Declarator* decl = new Declarator;
			ar.MapObject(decl);
			decl->Load(bMember, ar);

			if (m_qname == "System::Gui::Element" && decl->m_name == "get_id")
			{
			//	__asm int 3
			}

			decl->m_pOwnerScope = m_pScope;
			m_pScope->m_decls.insert(declsmap::value_type(decl->m_name, decl));

			if (ar.m_bSortedDecls)
			{
				if (decl->m_typedef)
				{
					m_pScope->m_types.insert(typemap::value_type(decl->m_name, (NamedType*)decl->m_pType));
				}
			}

			m_pScope->m_orderedDecls.Add(decl);
		}
	}

	{
		unsigned short nattributes;
		ar >> nattributes;

		if (nattributes > 0)
		{
			m_attributeDefs = array<AttributeDef>(new AttributeDef[nattributes], nattributes);

			for (uint i = 0; i < m_attributeDefs.size(); ++i)
			{
				m_attributeDefs[i].Load(ar);
			}
		}
	}
}

void ClassType::Store(TypeArchive& ar) const
{
	ASSERT(m_typelib);

	/*
	if (*m_name == "__release")
	{
		MessageBeep(-1);
	}
	*/

	NamespaceType::Store(ar);

	/*
	if (m_qname)
	{
		ar << true;
		ar << *m_qname;
	}
	else
	{
		ar << false;
	}
	*/

	ar << m_pInstantiatedFromClass;

	if (m_pInstantiatedFromArgs)
	{
#if 0
		ASSERT(m_pInstantiatedFromArgs->m_pClass == m_pInstantiatedFromClass);
#endif

		ar << true;
		m_pInstantiatedFromArgs->Store(ar);
	}
	else
	{
		ar << false;
	}

	if (m_pTemplateParams)
	{
		ar << true;

		/*
		if (*m_name == "Vector")
		{
			MessageBeep(-1);
		}
		*/

		ar << (uint16)m_pTemplateParams->m_items.size();
		for (uint i = 0; i < m_pTemplateParams->m_items.size(); ++i)
		{
			TemplateParameter* param = m_pTemplateParams->m_items[i];
			ar << param->m_kind;
			if (param->m_kind == TemplateParameter::Param_Type)
			{
				ASSERT(dynamic_cast<_TemplateArgType*>(param->u.m_pType));
				ar << param->u.m_pType;
			}
		}
	}
	else
	{
		ar << false;
	}

	VERIFY(m_kwType == ClassKey_class ||
		m_kwType == ClassKey_struct ||
		m_kwType == ClassKey_union ||
		m_kwType == ClassKey_interface);

	ar << (uint8)m_kwType;
	ar << m_sizeof;
	ar << m_rsizeof;
	ar << m_packing;
	ar << m_alignment;
	ar << m_force_alignment;
	ar << m_virtualSize;

	uint8 flags;
	flags = m_bVT;
	flags |= m_def<<1;
	ar << flags;

	{
		size_t nbases = m_bases.GetSize();
		ASSERT(nbases < 128);
		ar << (uint8)nbases;

		for (size_t i = 0; i < nbases; ++i)
		{
			ar << m_bases[i]->m_offset;

			Type* pType = m_bases[i]->m_pClass;
			//ASSERT(dynamic_cast<ClassType*>(pType));	// TODO

			ar << m_bases[i]->m_pClass;
		}
	}

	ar << m_pScope->m_orderedDecls.GetSize();

	/*
	// constructors first
	{
		for (int i = 0; i < m_pScope->m_orderedDecls.GetSize(); i++)
		{
			if (m_pScope->m_orderedDecls[i]->m_pDeclarator->m_name == m_name)
			{
				m_pScope->m_orderedDecls[i]->m_pDeclarator->Store(ar);
			}
		}
	}
	*/

	{
		bool bMember = get_Kind() == type_class;

		for (size_t i = 0; i < m_pScope->m_orderedDecls.GetSize(); ++i)
		{
		//	if (m_pScope->m_orderedDecls[i]->m_pDeclarator->m_name != m_name)
			{
				ar.MapObject(m_pScope->m_orderedDecls[i]);
				m_pScope->m_orderedDecls[i]->Store(bMember, ar);
			}
		}
	}

	ar << (unsigned short)m_attributeDefs.size();

	for (size_t i = 0; i < m_attributeDefs.size(); ++i)
	{
		m_attributeDefs[i].Store(ar);
	}
}

LFCEXT void PrintOffsets(IO::TextWriter& stream, ClassType* pClass)
{
	size_t offset = 0;
	for (size_t i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* decl = pClass->m_pScope->m_orderedDecls[i];
		if (!decl->get_IsStatic() && decl->m_pType->GetStripped()->get_Kind() != type_function)
		{
			/*
			if (offset < decl->m_offset)
			{
				stream << (decl->m_offset - offset) << " padding bytes\n";
			}
			*/

			offset = decl->m_offset;
			stream << offset << "\t: " << decl->m_name << ", sizeof=" << decl->m_pType->get_sizeof() << "\n";
			offset += decl->m_pType->get_sizeof();
		}
	}
}

}	// System
