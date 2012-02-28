#include "stdafx.h"
//#include "LXML.h"
#include "LXML2.h"
#include "ASXMLSchemaModel.h"
#include "ASXMLComplexTypeDeclaration.h"
#include "ASXMLSchemaModelGroup.h"

#if 0

#include "ASXMLSchemaModel.h"

#include "ASXMLAttributeDeclaration.h"
#endif

namespace System
{
namespace Web
{

void CComplexContentType::BuildDefs(Element* parent)
{
	ASSERT(0);
#if 0

	ASSERT(m_pModelGroup == NULL);
	ASSERT(m_pSchema);

	Node* child = parent->get_firstChild();
	while (child != NULL)
	{
		Element* element = dynamic_cast<Element*>(child);
		if (element)
		{
			StringW* tagName = element->get_tagName();

			if ((*tagName == L"sequence") ||
				(*tagName == L"choice"))
			{
				if (m_pModelGroup == NULL)
				{
					ASSERT(0);
					m_pModelGroup = NULL;//new CModelGroup;
				//	m_pModelGroup->AddRef();
					m_pModelGroup->m_pSchema = m_pSchema;
				//	m_pModelGroup->m_element = element;
					if (tagName == L"sequence")
						m_pModelGroup->m_listOperator = AS_SEQUENCE;
					else if (tagName == L"choice")
						m_pModelGroup->m_listOperator = AS_CHOICE;
					else
						m_pModelGroup->m_listOperator = AS_ALL;

					m_pModelGroup->BuildDefs(element);
				}
				else	// Only one allowed
				{
					WCHAR msg[256];
					swprintf(msg, L"Unexpected element <%s>", tagName.c_str());

					throw msg;
				}
			}
		}

		child = child->get_nextSibling();
	}
#endif
}

///////////////////////////////////////
// CComplexTypeDefinition

void CComplexTypeDefinition::BuildAttributes(Element* parent)
{
	Node* child = parent->get_firstChild();

	while (child != NULL)
	{
		Element* element = dynamic_cast<Element*>(child);
		if (element)
		{
			String tagName = element->get_tagName();

			if (tagName == L"attribute")
			{
#if 0
				CComObject<CASXMLAttributeDeclaration>* p;
				CComObject<CASXMLAttributeDeclaration>::CreateInstance(&p);
				if (p)
				{
					p->AddRef();
					p->m_pSchema = m_pSchema;
					p->m_element = element;

					m_attributeDecls->m_items.Add(p);
				}
#endif
			}
		}

		child = child->get_nextSibling();
	}
}

// virtual
void CComplexTypeDefinition::BuildDefs(Element* m_element)
{
	ASSERT(0);
#if 0

	ASSERT(m_pContent == NULL);

	m_name = m_element->getAttribute(L"name");

// Search for complexContent or simpleContent
	Node* child = m_element->get_firstChild();
	while (child != NULL)
	{
		Element* element = dynamic_cast<Element*>(child);
		if (element)
		{
			StringW* tagName = element->get_tagName();

			if ((*tagName == L"complexContent") ||
				(*tagName == L"simpleContent"))
			{
				if (m_pContent == NULL)
				{
					if (*tagName == L"complexContent")
					{
						m_pContent = new CComplexContentType;
					}
					else
					{
						m_pContent = new CSimpleContentType;
					}

//					m_pContent->m_pBaseType = this;
					m_pContent->m_pSchema = m_pSchema;
				//	m_pContent->m_element = element;

					Node* child = element->get_firstChild();

					if (child)
					{
						Element* element = dynamic_cast<Element*>(child);
						if (element)
						{
							StringW* tagName = element->get_tagName();

							if ((*tagName == L"extension") ||
								(*tagName == L"restriction"))
							{
								if (*tagName == L"extension")
								{
									m_pContent->m_derivationMethod = WSTR("extension");
								}
								else
								{
									m_pContent->m_derivationMethod = WSTR("restriction");

									StringW* base = element->getAttribute(WSTR("base"));
									m_pContent->m_base = base;
									if (m_pContent->m_base->Length() == 0)
									{
										WCHAR msg[256];
										swprintf(msg, L"restriction element is missing base attribute");
										THROW(-1);
									}
								}

							//	m_deepElement = element;
								m_pContent->BuildDefs(element);
								BuildAttributes(element);
							}
							else
							{
								WCHAR msg[256];
								swprintf(msg, L"Unexpected element");
								THROW(-1);
							}
						}
					}

					if (m_pContent->m_derivationMethod.length() == 0)
					{
						WCHAR msg[256];
						swprintf(msg, L"Expected either <restriction> or <extension> element");

						throw msg;
					}
				}
				else
				{
					WCHAR msg[256];
					swprintf(msg, L"Can only have one of complexContent/simpleContent");

					throw msg;
				}
			}
		}

		child = child->get_nextSibling();
	}

// If there is no complexContent or simpleContent then
// defaults to restricted complexContent
	if (m_pContent == NULL)
	{
		CComplexContentType* pComplexContent = new CComplexContentType;
		pComplexContent->m_derivationMethod = L"restriction";

		m_pContent = pComplexContent;
		m_pContent->m_pSchema = m_pSchema;
	//	m_pContent->m_element = NULL;
	//	m_deepElement = m_element;

		m_pContent->BuildDefs(m_element);
		BuildAttributes(m_element);
	}
#endif
}

IASContentModel* CComplexTypeDefinition::get_asCM()
{
	ASSERT(0);
	return NULL;
#if 0

// TODO
	return ((CComplexContentType*)m_pContent)->m_pModelGroup;
#endif
}

void CComplexTypeDefinition::addASAttributeDecl(/*[in]*/ IASAttributeDeclaration* attributeDecl)
{
	ASSERT(0);
#if 0
	if (attributeDecl == NULL) return E_INVALIDARG;

	attributeDecl->AddRef();

	CComPtr<ILDOMElement> element;
	attributeDecl->GetElement(&element);
	ASSERT(element);

	ASSERT(m_deepElement);
	m_deepElement->appendChild(element, NULL);

	m_attributeDecls->m_items.Add(attributeDecl);
#endif
}

IASAttributeDeclaration* CComplexTypeDefinition::removeASAttributeDecl(/*[in]*/ IASAttributeDeclaration* attributeDecl)
{
	return NULL;
}

}	// Web
}
