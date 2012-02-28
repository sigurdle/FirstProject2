// XML.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "XML.h"

namespace System
{

ClassType* DoComplexType(XS::ComplexType* xsType, NamespaceType* pOwnerClass);
void DoParticles(ClassType* pType, XS::Particles* particles, NamespaceType* pOwnerClass);

Type* FromXSType(XS::Type* xsType, NamespaceType* pOwnerClass)
{
	XS::SimpleType* simpleType = dynamic_cast<XS::SimpleType*>(xsType);
	if (simpleType)
	{
		if (simpleType->m_kind == XS::date_Idx)
		{
			return typeid(XS::date).GetType();
		}
		else if (simpleType->m_kind == XS::string_Idx)
		{
			return typeid(StringObject).GetType();
		}
		else if (simpleType->m_kind == XS::normalizedString_Idx)
		{
			return typeid(StringObject).GetType();
		}
		else if (simpleType->m_kind == XS::token_Idx)
		{
			return typeid(StringObject).GetType();
		}
		else if (simpleType->m_kind == XS::NMTOKEN_Idx)
		{
			return typeid(StringObject).GetType();
		}
		else if (simpleType->m_kind == XS::decimal_Idx)
		{
			return Types::get_long();
		}
		else if (simpleType->m_kind == XS::positiveInteger_Idx)
		{
			return typeid(XS::PositiveInteger).GetType();
		}
		else if (simpleType->m_kind == XS::unsignedLong_Idx)
		{
			return Types::get_unsigned_long_long();
		}
		else
		{
			// TODO
			return Types::get_void();
		}
	}
	else
	{
		XS::ComplexType* complexType = dynamic_cast<XS::ComplexType*>(xsType);
		return DoComplexType(complexType, pOwnerClass);
	}

	return NULL;
}

ClassType* DoComplexType(XS::ComplexType* complexType, NamespaceType* pOwnerClass)
{
	ClassType* pType = new ClassType;

	if (complexType->get_name())
		pType->m_name = complexType->get_name();
	else
		pType->m_name = L"unnamed";	// TODO

	if (pOwnerClass)// && complexType->mgget_scope())
	{
		Declarator* decl = new Declarator;
		decl->m_pType = pType;
		decl->m_typedef = true;
		decl->m_name = pType->m_name;
		pOwnerClass->m_pScope->m_orderedDecls.Add(decl);
	}

	for (unsigned int i = 0; i < complexType->m_attributeUses.size(); i++)
	{
		XS::AttributeUse* attributeUse = complexType->m_attributeUses[i];

		Declarator* decl = new Declarator;
		decl->m_name = attributeUse->m_attribute->get_name();
		decl->m_pType = FromXSType(attributeUse->m_attribute->get_typeDefinition(), pType);
		ASSERT(decl->m_pType);

		pType->m_pScope->m_orderedDecls.Add(decl);
	}

	DoParticles(pType, complexType->m_particles, pType);

	return pType;
}

void DoParticles(ClassType* pType, XS::Particles* particles, NamespaceType* pOwnerClass)
{
	for (unsigned int i = 0; i < particles->m_items.size(); i++)
	{
		XS::Particle* particle = particles->m_items[i];

		if (particle->m_termKind == XS::Term_ModelGroup)
		{
			XS::ModelGroup* modelGroup = particle->m_term.modelGroup;

			if (modelGroup->m_compositor == XS::C_CHOICE)
			{
				ClassType* pClass = new ClassType;
				pClass->m_kwType = ClassKey_union;
				// union
			}
			else
			{
				// sequence

				if (particle->get_maxOccurs() == XS::unbounded)
				{
					if (modelGroup->m_particles->m_items.size() == 1 && modelGroup->m_particles->m_items[0]->m_termKind == XS::Term_Element)
					{
						Declarator* decl = new Declarator;
					//	decl->m_name = element->get_name()->ToStringA();
					//	decl->m_pType = FromXSType(element->get_typeDefinition());
					}
					else
						VERIFY(0);
				}
				else
				{
					DoParticles(pType, modelGroup->m_particles, pOwnerClass);
				}
			}
		}
		else if (particle->m_termKind == XS::Term_Element)
		{
			XS::Element* element = particle->m_term.element;

			Type* pType2 = FromXSType(element->get_typeDefinition(), pOwnerClass);

			if (particle->get_maxOccurs() == XS::unbounded)
			{
				ClassType* pTemp = typeid(vector<double>)->AsClass();//(ClassType*)pD->LookupNamedType("vector<double,System::__gc_allocator>");
				VERIFY(pTemp);
				ClassType* pArrayTemplate = pTemp->m_pInstantiatedFromClass;

				ClassType* pArrayType = new ClassType;
				pArrayType->m_pInstantiatedFromClass = pArrayTemplate;
				pArrayType->m_pInstantiatedFromArgs = new TemplatedClassArgs;

				TemplatedClassArg* arg = new TemplatedClassArg;
				arg->m_pType = pType2;
				pArrayType->m_pInstantiatedFromArgs->m_items.Add(arg);

#if 0		// Defaults
				for (; i < pTemplateClass->AsClass()->m_pTemplateParams->m_templateParams.GetSize(); i++)
				{
					System::TemplateParameter* param = pTemplateClass->AsClass()->m_pTemplateParams->m_templateParams[i];
					if (param->m_kind == System::TemplateParameter::Param_Type)
					{
						//__live_object_ptr<Type> pTemplateArgType = 

					//	TemplatedClassArg* p = new TemplatedClassArg;
					//	p->m_pType = ;

					//	Type* pType = Evaluate(pGlobal, param->m_pType->m_defaultArg);

					//	Type* pType = param->m_pType->m_defaultArg;

						/*
						if (ContainsTemplateArg(param->m_pType->m_defaultArg->m_pType))
						{
							bWait = true;
						}
						*/

						/*pTType->m_*/pInstantiatedFrom->m_templateArgs.push_back(param->m_pType->m_defaultArg);
					}
					else
					{
						ASSERT(0);
					}
				}
#endif
				Declarator* decl = new Declarator;
				decl->m_name = element->get_name();
				decl->m_pType = pArrayType;//FromXSType(element->get_typeDefinition(), pOwnerClass);

				pType->m_pScope->m_orderedDecls.Add(decl);
			}
			else
			{
				Declarator* decl = new Declarator;
				decl->m_name = element->get_name();
				decl->m_pType = pType2;//FromXSType(element->get_typeDefinition(), pOwnerClass);

				pType->m_pScope->m_orderedDecls.Add(decl);
			}
		}
	}
}

void test()
{
	if (false)
	{
		XmlData::Document* document = new XmlData::Document;

		document->load(L"c:/delthis/po.xsd");

		VERIFY(document->get_documentElement() != NULL);

		XS::Schema* schema = new XS::Schema(document);

		{
			AllocConsole();
		//	MSWindows::GetStdHandle(STD_OUTPUT_HANDLE);

			FILE* fp;
			freopen_s(&fp, "CON:", "a", stdout);
		//	freopen("CON:", "a", stderr);

			for (auto it = schema->m_globalTypes.begin(); it != schema->m_globalTypes.end(); ++it)
			{
				XS::Type* xsType = it->second;

				XS::ComplexType* complexType = dynamic_cast<XS::ComplexType*>(xsType);
				if (complexType)
				{
					ClassType* pType = DoComplexType(complexType, NULL);
					ASSERT(0);
				//	printClass(stdout, pType, 0);
				}

				DebugTrace("\n");
			}

			DebugTrace("\n");
		}
	}

}
}