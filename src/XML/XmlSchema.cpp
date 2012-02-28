#include "stdafx.h"
#include "XML.h"

namespace System
{
namespace XS
{

static String xsd_namespaceURI(L"http://www.w3.org/2001/XMLSchema");

void GetNSID(StringIn qname, String& prefix, String& localName)
{
	size_t ncolon = qname.find(':');
	if (ncolon != String::npos)
	{
		prefix = qname.LeftOf(ncolon);
		localName = qname.RightOf(ncolon + 1);
	}
	else
	{
		prefix = nullptr;
		localName = qname;
	}
}

Type Type::s_anyType(L"anyType", xsd_namespaceURI);

////////////

String Type::get_name()
{
	return m_name;
}

String Type::get_targetNamespace()
{
	return m_targetNamespace;
}

///

SimpleType::SimpleType()
{
}

SimpleType::SimpleType(SimpleTypeKind kind, StringIn name, StringIn targetNamespace, Type* derivedFrom, DerivationMethod derivationMethod)
{
	m_kind = kind;
	m_name = name;
	m_targetNamespace = targetNamespace;
	m_derivedFrom = derivedFrom;
	m_derivationMethod = derivationMethod;
}

String anySimpleType_str(L"anySimpleType");
String date_str(L"date");
String decimal_str(L"decimal");
String integer_str(L"integer");
String nonNegativeInteger_str(L"nonNegativeInteger");
String normalizedString_str(L"normalizedString");
String positiveInteger_str(L"positiveInteger");
String string_str(L"string");
String token_str(L"token");
String unsignedLong_str(L"unsignedLong");
String NMTOKEN_str(L"NMTOKEN");

// Keep these sorted
SimpleType SimpleType::s_builtin_types[] =
{
	SimpleType(anySimpleType_Idx, anySimpleType_str, xsd_namespaceURI, &s_anyType, Derivation_restriction),
	SimpleType(date_Idx, date_str, xsd_namespaceURI, &s_builtin_types[anySimpleType_Idx], Derivation_restriction),
	SimpleType(decimal_Idx, decimal_str, xsd_namespaceURI, &s_builtin_types[anySimpleType_Idx], Derivation_restriction),
	SimpleType(integer_Idx, integer_str, xsd_namespaceURI, &s_builtin_types[decimal_Idx], Derivation_restriction),
	SimpleType(nonNegativeInteger_Idx, nonNegativeInteger_str, xsd_namespaceURI, &s_builtin_types[integer_Idx], Derivation_restriction),
	SimpleType(normalizedString_Idx, normalizedString_str, xsd_namespaceURI, &s_builtin_types[string_Idx], Derivation_restriction),
	SimpleType(positiveInteger_Idx, positiveInteger_str, xsd_namespaceURI, &s_builtin_types[nonNegativeInteger_Idx], Derivation_restriction),
	SimpleType(string_Idx, string_str, xsd_namespaceURI, &s_builtin_types[anySimpleType_Idx], Derivation_restriction),
	SimpleType(token_Idx, token_str, xsd_namespaceURI, &s_builtin_types[normalizedString_Idx], Derivation_restriction),
	SimpleType(unsignedLong_Idx, unsignedLong_str, xsd_namespaceURI, &s_builtin_types[nonNegativeInteger_Idx], Derivation_restriction),
	SimpleType(NMTOKEN_Idx, NMTOKEN_str, xsd_namespaceURI, &s_builtin_types[token_Idx], Derivation_restriction),
};

SimpleType* BuiltinSimpleType(StringIn name)
{
	if (name == L"anySimpleType")
	{
		return &SimpleType::s_builtin_types[anySimpleType_Idx];
	}
	else if (name == L"string")
	{
		return &SimpleType::s_builtin_types[string_Idx];
	}
	else if (name == L"normalizedString")
	{
		return &SimpleType::s_builtin_types[normalizedString_Idx];
	}
	else if (name == L"decimal")
	{
		return &SimpleType::s_builtin_types[decimal_Idx];
	}
	else if (name == L"date")
	{
		return &SimpleType::s_builtin_types[date_Idx];
	}
	else if (name == L"positiveInteger")
	{
		return &SimpleType::s_builtin_types[positiveInteger_Idx];
	}
	else if (name == L"token")
	{
		return &SimpleType::s_builtin_types[token_Idx];
	}
	else if (name == L"unsignedLong")
	{
		return &SimpleType::s_builtin_types[unsignedLong_Idx];
	}
	else if (name == L"NMTOKEN")
	{
		return &SimpleType::s_builtin_types[NMTOKEN_Idx];
	}
	else
		raise(Exception(L"Unrecognized simple type " + name));

	return NULL;
}

//

Attribute::Attribute()
{
}

Attribute::Attribute(ComplexType* scope)
{
	m_scope = scope;
}

String Attribute::get_name()
{
	return m_name;
}

String Attribute::get_targetNamespace()
{
	return m_targetNamespace;
}

SimpleType* Attribute::get_typeDefinition()
{
	return m_typeDefinition;
}

Annotation* Attribute::get_annotation()
{
	return m_annotation;
}

ComplexType* Attribute::get_scope()	// if NULL, it is global
{
	return m_scope;
}

void Attribute::FromXML(Schema* schema, XmlData::Element* element)
{
	m_name = element->getAttributeNS(StringIn(), L"name");

	XmlData::Element* simpleTypeElement = element->getElementByTagNameNS(xsd_namespaceURI, L"simpleType");

	if (simpleTypeElement)
	{
	}
	else
	{
		String type_str = element->getAttribute(L"type");
		if (type_str == nullptr)
		{
			throw new Exception(L"No type attribute");
			ASSERT(0);
		}

		String prefix;
		String localName;
		GetNSID(type_str, prefix, localName);

		if (prefix == nullptr)
		{
			// TODO: ?

			Type* pType = schema->FindType(localName);
		//	map<StringW*, Type*, Ref_Less<StringW> >::iterator it = schema->m_globalTypes.find(localName);
		//	VERIFY(it != schema->m_globalTypes.end());
			if (pType == NULL)
			{
				pType = BuiltinSimpleType(localName);
			}

			SimpleType* pSimpleType = dynamic_cast<SimpleType*>(pType);

			if (pSimpleType == NULL)
			{
				raise(Exception(L"attribute type must be a simpleType"));
				ASSERT(0);
			}

			m_typeDefinition = pSimpleType;
		}
		else
		{
			if (prefix == L"xsd")	// TODO, lookup
			{
				m_typeDefinition = BuiltinSimpleType(localName);
			}
			else
			{
				raise(Exception(L"prefix != xsd"));
			}
		}
	}
}

////////////

Element::Element()
{
}

Element::Element(ComplexType* scope)
{
	m_scope = scope;
}

String Element::get_name()
{
	return m_name;
}

String Element::get_targetNamespace()
{
	return m_targetNamespace;
}

Type* Element::get_typeDefinition()
{
	return m_typeDefinition;
}

ComplexType* Element::get_scope()	// if NULL, it is global
{
	return m_scope;
}

bool Element::get_nillable()
{
	return m_nillable;
}

void Element::FromXML(Schema* schema, XmlData::Element* element)
{
#ifdef _DEBUG
	String ref_str = element->getAttributeNS(nullptr, L"ref");
	VERIFY(ref_str == nullptr);
#endif

	m_name = element->getAttributeNS(nullptr, L"name");
	if (m_name == nullptr)
	{
		raise(Exception(L"no name attribute"));
	}

	String nillable_str = element->getAttributeNS(nullptr, L"nillable");
	if (nillable_str == nullptr)
		m_nillable = false;
	else
		m_nillable = nillable_str == L"true";

	XmlData::Element* simpleTypeElement = element->getElementByTagNameNS(xsd_namespaceURI, L"simpleType");
	XmlData::Element* complexTypeElement = element->getElementByTagNameNS(xsd_namespaceURI, L"complexType");

	if (simpleTypeElement != nullptr && complexTypeElement != nullptr)
	{
		raise(Exception(L"Can only have either simpleType or complexType"));
		ASSERT(0);
	}
	else if (simpleTypeElement)
	{
		SimpleType* pType = new SimpleType;
		pType->FromXML(schema, simpleTypeElement);

		m_typeDefinition = pType;
	}
	else if (complexTypeElement)
	{
		ComplexType* pType = new ComplexType;
		pType->FromXML(schema, complexTypeElement);

		m_typeDefinition = pType;
	}
	else
	{
		String type_str = element->getAttribute(L"type");
		if (type_str == nullptr)
		{
			raise(Exception(L"No type"));
			ASSERT(0);
		}

		String prefix;
		String localName;
		GetNSID(type_str, prefix, localName);

		if (prefix != nullptr)
		{
			m_typeDefinition = schema->FindType(localName);
			if (m_typeDefinition == nullptr)
			{
				raise(Exception(L"Couldn't find type " + localName));
			}
		}
		else
		{
			m_typeDefinition = BuiltinSimpleType(localName);
		}
	}
}

////////////

void SimpleType::FromXML(Schema* schema, XmlData::Element* element)
{
	m_name = element->getAttributeNS(nullptr, L"name");
}

///////////////

ComplexType::ComplexType()
{
}

/*
StringW* ComplexType::get_name()
{
	return m_name;
}

StringW* ComplexType::get_targetNamespace()
{
	return m_targetNamespace;
}
*/

bool ComplexType::get_abstract()
{
	return m_abstract;
}

DerivationMethod ComplexType::get_derivationMethod()
{
	return m_derivationMethod;
}

Particles* ParticlesFromXML(Schema* schema, XmlData::Element* element);

ModelGroup* ModelGroupFromXML(Schema* schema, XmlData::Element* element)
{
	if (element->get_localName() == L"all")
	{
		return new ModelGroup(C_ALL, ParticlesFromXML(schema, element));
	}
	else if (element->get_localName() == L"choice")
	{
		return new ModelGroup(C_CHOICE, ParticlesFromXML(schema, element));
	}
	else if (element->get_localName() == L"sequence")
	{
		return new ModelGroup(C_SEQUENCE, ParticlesFromXML(schema, element));
	}
	else
	{
		VERIFY(0);
		return nullptr;
	}
}

Particle* ParticleFromXML(Schema* schema, XmlData::Element* element)
{
	String minOccurs_str = element->getAttributeNS(nullptr, L"minOccurs");
	String maxOccurs_str = element->getAttributeNS(nullptr, L"maxOccurs");

	unsigned long minOccurs = minOccurs_str != nullptr? str2int(CString(minOccurs_str).c_str()): 1;
	unsigned long maxOccurs;

	if (maxOccurs_str == L"unbounded")
		maxOccurs = unbounded;
	else
		maxOccurs = maxOccurs_str != nullptr? str2int(CString(maxOccurs_str).c_str()): 1;

	if (element->get_localName() == L"element")
	{
		String ref_str = element->getAttributeNS(nullptr, L"ref");

		if (ref_str != nullptr)
		{
			String name_str = element->getAttributeNS(nullptr, L"name");
			String nillable_str = element->getAttributeNS(nullptr, L"nillable");
			XmlData::Element* simpleTypeElement = element->getElementByTagNameNS(xsd_namespaceURI, L"simpleType");
			XmlData::Element* complexTypeElement = element->getElementByTagNameNS(xsd_namespaceURI, L"complexType");

			if (nillable_str) throw new Exception(L"nillable must not be present when ref is present");
			if (name_str) throw new Exception(L"name must not be present when ref is present");
			if (simpleTypeElement) throw new Exception(L"simpleType must not be present when ref is present");
			if (complexTypeElement) throw new Exception(L"complexType must not be present when ref is present");

			Element* xselement = schema->FindElement(ref_str);
			VERIFY(xselement);

			return new Particle(minOccurs, maxOccurs, xselement);
		}
		else
		{
			Element* xselement = new Element;
			xselement->FromXML(schema, element);
			return new Particle(minOccurs, maxOccurs, xselement);
		}
	}
	else
	{
		return new Particle(minOccurs, maxOccurs, ModelGroupFromXML(schema, element));
	}
}

Particles* ParticlesFromXML(Schema* schema, XmlData::Element* element)
{
	Particles* particles = new Particles;

	for (unsigned int i = 0; i < element->get_childNodes()->get_length(); i++)
	{
		XmlData::Node* childNode = element->get_childNodes()->item(i);

		if (childNode->get_nodeType() == XmlData::NODE_ELEMENT)
		{
			XmlData::Element* childElement = static_cast<XmlData::Element*>(childNode);

			if (childElement->get_namespaceURI() == xsd_namespaceURI)
			{
				String localName = childElement->get_localName();

				// Model group / Element
				if (localName == L"all" || localName == L"choice" || localName == L"sequence" || localName == L"element")
				{
					particles->m_items.Add(ParticleFromXML(schema, childElement));
				}
				// Wildcard
				else if (localName == L"any")
				{
				//	Particle* particle = new Particle;
				}
				else if (localName == L"anyAttribute")
				{
				//	Particle* particle = new Particle;
				}
			}
		}
	}

	return particles;
}

void ComplexType::FromXML(Schema* schema, XmlData::Element* element)
{
	m_name = element->getAttributeNS(nullptr, L"name");

	String abstract_str = element->getAttributeNS(nullptr, L"abstract");
	if (abstract_str == nullptr)
		m_abstract = false;
	else
		m_abstract = abstract_str == L"true";

	for (unsigned int i = 0; i < element->get_childNodes()->get_length(); i++)
	{
		XmlData::Node* childNode = element->get_childNodes()->item(i);

		if (childNode->get_nodeType() == XmlData::NODE_ELEMENT)
		{
			XmlData::Element* childElement = static_cast<XmlData::Element*>(childNode);

			if (childElement->get_namespaceURI() == xsd_namespaceURI)
			{
				// Attribute
				if (childElement->get_localName() == L"attribute")
				{
					AttributeUse* attributeUse = new AttributeUse;
				//	use = (optional | prohibited | required) : optional
					String use = childElement->getAttributeNS(nullptr, L"use");
					if (use == L"required")
						attributeUse->m_required = true;
					else
						attributeUse->m_required = false;

					String ref_str = childElement->getAttributeNS(nullptr, L"ref");
					if (ref_str != nullptr)
					{
						// TODO
						raise(Exception(L"TODO: ref_str != null"));
					}
					else
					{
						Attribute* attribute = new Attribute(this);
						attribute->FromXML(schema, childElement);
						attributeUse->m_attribute = attribute;
					}

					m_attributeUses.Add(attributeUse);
				}
			}
		}
	}

	m_particles = ParticlesFromXML(schema, element);
}

//

unsigned long Particle::get_minOccurs()
{
	return m_minOccurs;
}

unsigned long Particle::get_maxOccurs()
{
	return m_maxOccurs;
}

Element* Schema::FindElement(StringIn ref)
{
	map<String, Element*>::iterator it = m_globalElementsByName.find(ref);
	if (it != m_globalElementsByName.end())
	{
		return (*it).second;
	}

	for (unsigned int i = 0; i < m_documentElement->get_childNodes()->get_length(); i++)
	{
		XmlData::Node* childNode = m_documentElement->get_childNodes()->item(i);

		if (childNode->get_nodeType() == XmlData::NODE_ELEMENT)
		{
			XmlData::Element* childElement = static_cast<XmlData::Element*>(childNode);

			if (childElement->get_namespaceURI() == xsd_namespaceURI)
			{
				if (childElement->get_localName() == L"element")	// global element
				{
					String name = childElement->getAttribute(L"name");
					if (name == ref)
					{
						Element* xselement = new Element(NULL/*global*/);
						m_globalDefs.Add(xselement);
						m_globalElementsByName.insert(map<String, Element*>::value_type(ref, xselement));

						xselement->FromXML(this, childElement);

						return xselement;
					}
				}
			}
		}
	}

	return nullptr;
}

Type* Schema::FindType(StringIn localName)
{
	map<String, Type*>::iterator it = m_globalTypes.find(localName);
	if (it != m_globalTypes.end())
	{
		return it->second;
	}

	for (unsigned int i = 0; i < m_documentElement->get_childNodes()->get_length(); i++)
	{
		XmlData::Node* childNode = m_documentElement->get_childNodes()->item(i);

		if (childNode->get_nodeType() == XmlData::NODE_ELEMENT)
		{
			XmlData::Element* childElement = static_cast<XmlData::Element*>(childNode);

			if (childElement->get_namespaceURI() == xsd_namespaceURI)
			{
				if (childElement->get_localName() == L"complexType")	// global type definition
				{
					String name = childElement->getAttribute(L"name");
					if (name == localName)
					{
						ComplexType* type = new ComplexType;
						m_globalTypes.insert(map<String, Type*>::value_type(name, type));
						m_globalDefs.Add(type);
						type->FromXML(this, childElement);

						return type;
					}
				}
				else if (childElement->get_localName() == L"simpleType")	// global type definition
				{
					String name = childElement->getAttribute(L"name");
					if (name == localName)
					{
						SimpleType* type = new SimpleType;
						m_globalTypes.insert(map<String, Type*>::value_type(name, type));
						m_globalDefs.Add(type);
						type->FromXML(this, childElement);

						return type;
					}
				}
			}
		}
	}

	return NULL;
}

Schema::Schema(XmlData::Document* document)
{
	FromXML(document->get_documentElement());
}

Schema::Schema(StringIn url)
{
	XmlData::Document* document = new XmlData::Document;
	document->load(url);
	FromXML(document->get_documentElement());
}

Schema::Schema(IO::Stream* stream)
{
	XmlData::Document* document = new XmlData::Document;
	document->load(stream);
	FromXML(document->get_documentElement());
}

void Schema::FromXML(XmlData::Element* element)
{

	m_documentElement = element;

	// ??
	// First global types

	for (size_t i = 0; i < element->get_childNodes()->get_length(); ++i)
	{
		XmlData::Node* childNode = element->get_childNodes()->item(i);

		if (childNode->get_nodeType() == XmlData::NODE_ELEMENT)
		{
			XmlData::Element* childElement = static_cast<XmlData::Element*>(childNode);

			if (childElement->get_namespaceURI() == xsd_namespaceURI)
			{
				if (childElement->get_localName() == L"complexType")	// global type definition
				{
					String name = childElement->getAttribute(L"name");

					if (m_globalTypes.find(name) == m_globalTypes.end())
					{
						ComplexType* type = new ComplexType;
						type->FromXML(this, childElement);

						m_globalTypes.insert(map<String, Type*>::value_type(type->get_name(), type));

						m_globalDefs.Add(type);
					}
				}
				else if (childElement->get_localName() == L"simpleType")	// global type definition
				{
					String name = childElement->getAttribute(L"name");

					if (m_globalTypes.find(name) == m_globalTypes.end())
					{
						SimpleType* type = new SimpleType;
						type->FromXML(this, childElement);

						m_globalTypes.insert(map<String, Type*>::value_type(type->get_name(), type));

						m_globalDefs.Add(type);
					}
				}
				else if (childElement->get_localName() == L"element")	// global element
				{
					String name = childElement->getAttribute(L"name");

					if (m_globalElementsByName.find(name) == m_globalElementsByName.end())
					{
						Element* xselement = new Element(nullptr/*global*/);

						xselement->FromXML(this, childElement);

						m_globalDefs.Add(xselement);

						m_globalElementsByName.insert(map<String, Element*>::value_type(xselement->get_name(), xselement));
					}
				}
			}
		}
	}

#if 0
	// global elements
	for (int i = 0; i < element->get_childNodes()->get_length(); i++)
	{
		XmlData::Node* childNode = element->get_childNodes()->item(i);

		if (childNode->get_nodeType() == XmlData::NODE_ELEMENT)
		{
			XmlData::Element* childElement = static_cast<XmlData::Element*>(childNode);

			if (*childElement->get_namespaceURI() == xsd_namespaceURI)
			{
				if (*childElement->get_localName() == L"element")	// global element
				{
					Element* xselement = new Element(NULL/*global*/);

					xselement->FromXML(this, childElement);

					m_globalDefs.Add(xselement);

					m_globalElementsByName.insert(map<StringW*, Element*, Ref_Less<StringW> >::value_type(xselement->get_name(), xselement));
				}
				/*
				else if (*childElement->get_localName() == L"complexType")	// global type definition
				{
					ComplexType* type = new ComplexType;
					type->FromXML(childElement);

					m_globalDefs.Add(type);
				}
				else if (*childElement->get_localName() == L"simpleType")	// global type definition
				{
					SimpleType* type = new SimpleType;
					type->FromXML(childElement);

					m_globalDefs.Add(type);
				}
				*/
			}
		}
	}
#endif
}

}	// XS
}	// System
