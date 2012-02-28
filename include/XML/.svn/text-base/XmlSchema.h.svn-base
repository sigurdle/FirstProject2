#ifndef XmlSchema_h
#define XmlSchema_h

namespace System
{
namespace XS
{

class XMLEXT date
{
public:

	uint64 m_value;
};

class XMLEXT PositiveInteger
{
public:

	CTOR PositiveInteger()
	{
	}

	CTOR PositiveInteger(unsigned long value)
	{
		if (value == 0)
		{
			ASSERT(0);
			raise(Exception(L"PositiveInteger out of range"));
		}

		m_value = value;
	}

	operator unsigned long () const
	{
		return m_value;
	}

	PositiveInteger& operator = (unsigned long value)
	{
		if (value == 0)
		{
			ASSERT(0);
			raise(Exception(L"PositiveInteger out of range"));
		}

		m_value = value;
		return *this;
	}

protected:

	unsigned long m_value;
};

class Schema;
class Element;
class Attribute;
class AttributeUse;
class Particles;

class XMLEXT Annotation : public Object
{
};

class XMLEXT Type : public Object
{
public:

	virtual String get_name();
	virtual String get_targetNamespace();

	bool m_global;

	static Type s_anyType;

protected:

	CTOR Type()
	{
		m_global = false;
	}

	CTOR Type(StringIn name, StringIn targetNamespace) : m_name(name), m_targetNamespace(targetNamespace)
	{
		m_global = false;
	}

protected:

	String m_name;
	String m_targetNamespace;
};

// Keep these sorted
enum SimpleTypeKind
{
	anySimpleType_Idx,
	date_Idx,
	decimal_Idx,
	integer_Idx,
	nonNegativeInteger_Idx,
	normalizedString_Idx,
	positiveInteger_Idx,
	string_Idx,
	token_Idx,
	unsignedLong_Idx,
	NMTOKEN_Idx,
};

enum DerivationMethod
{
	Derivation_none,
	Derivation_extension,
	Derivation_restriction,
	Derivation_list,
};

class XMLEXT SimpleType : public Type
{
public:
	CTOR SimpleType();

	void FromXML(Schema* schema, XmlData::Element* element);

	SimpleTypeKind m_kind;
	Type* m_derivedFrom;
	DerivationMethod m_derivationMethod;

	static SimpleType s_builtin_types[64];

protected:

	CTOR SimpleType(SimpleTypeKind kind, StringIn name, StringIn targetNamespace, Type* derivedFrom = NULL, DerivationMethod m_derivationMethod = Derivation_none);
};

/*
class LFCEXT StringSimpleType : public SimpleType
{
protected:
	CTOR StringSimpleType()
	{
	}
};

class LFCEXT DecimalSimpleType : public SimpleType
{
public:

protected:
	CTOR DecimalSimpleType()
	{
	}
};
*/

const unsigned long unbounded = 0xffffffff;

enum Compositor
{
	C_ALL,
	C_CHOICE,
	C_SEQUENCE,
};

class XMLEXT ModelGroup : public Object
{
public:
	CTOR ModelGroup(Compositor compositor, Particles* particles)
	{
		m_compositor = compositor;
		m_particles = particles;
	}

	Particles* m_particles;
	Compositor m_compositor;
};

enum TermKind
{
	Term_Element,
	Term_ModelGroup,
};

class XMLEXT Particle : public Object
{
public:

	CTOR Particle(unsigned long minOccurs, unsigned long maxOccurs, Element* element)
	{
		m_minOccurs = minOccurs;
		m_maxOccurs = maxOccurs;

		m_termKind = Term_Element;
		m_term.element = element;
	}

	CTOR Particle(unsigned long minOccurs, unsigned long maxOccurs, ModelGroup* modelGroup)
	{
		m_minOccurs = minOccurs;
		m_maxOccurs = maxOccurs;

		m_termKind = Term_ModelGroup;
		m_term.modelGroup = modelGroup;
	}

	unsigned long get_minOccurs();
	unsigned long get_maxOccurs();

	/*
	enum Term
	{
		model group, a wildcard, or an element declaration

	}
	*/

	TermKind m_termKind;
	union
	{
		Element* element;
		ModelGroup* modelGroup;
	}
	m_term;

protected:

	unsigned long m_minOccurs;
	unsigned long m_maxOccurs;
};

class XMLEXT Particles : public Object
{
public:
	vector<Particle*> m_items;
};

class XMLEXT ComplexType : public Type
{
public:
	CTOR ComplexType();

//	virtual StringW* get_name();
//	virtual StringW* get_targetNamespace();
	virtual bool get_abstract();

	virtual DerivationMethod get_derivationMethod();

	enum ContentType
	{
		EMPTY,
		SIMPLETYPE,
		CONTENTMODEL,
	};

	/*
	enum
	{
		Mixed,
		ElementOnly,
	}
	*/

	ContentType get_contentType();
	bool get_mixedContentModel();
	void FromXML(Schema* schema, XmlData::Element* element);

	Particles* m_particles;
	vector<AttributeUse*> m_attributeUses;

protected:

//	StringW* m_name;
//	StringW* m_targetNamespace;
	ContentType m_contentType;
	DerivationMethod m_derivationMethod;
	bool m_mixedContentModel;
	bool m_abstract;
};

class XMLEXT Attribute : public Object
{
public:
	CTOR Attribute();
	CTOR Attribute(ComplexType* scope);

	virtual String get_name();
	virtual String get_targetNamespace();
	virtual SimpleType* get_typeDefinition();
	virtual Annotation* get_annotation();
	virtual ComplexType* get_scope();	// if NULL, it is global

	// TODO
	// {value constraint} Optional. A pair consisting of a value and one of default, fixed. 

	void FromXML(Schema* schema, XmlData::Element* element);

protected:

	String m_name;
	String m_targetNamespace;
	SimpleType* m_typeDefinition;
	ComplexType* m_scope;
	Annotation* m_annotation;
};

class XMLEXT AttributeUse : public Object
{
public:
	Attribute* m_attribute;
	bool m_required;

	/* TODO
{value constraint}
Optional. A pair consisting of a value and one of default, fixed. 
	*/
};

class XMLEXT Element : public Object
{
public:
	CTOR Element();
	CTOR Element(ComplexType* scope);

	virtual String get_name();
	virtual String get_targetNamespace();
	virtual Type* get_typeDefinition();
	virtual ComplexType* get_scope();	// if NULL, it is global
	virtual bool get_nillable();

	void FromXML(Schema* schema, XmlData::Element* element);

protected:

	String m_name;
	String m_targetNamespace;
	Type* m_typeDefinition;
	ComplexType* m_scope;
	bool m_nillable;
};

class XMLEXT Schema : public Object
{
public:
	CTOR Schema(StringIn url);
	CTOR Schema(IO::Stream* stream);
	CTOR Schema(XmlData::Document* document);

	void FromXML(XmlData::Element* element);

	Type* FindType(StringIn localName);
	Element* FindElement(StringIn ref);
	Attribute* FindAttribute(StringIn ref);

	vector<Object*> m_globalDefs;

	map<String, Element*> m_globalElementsByName;
	map<String, Element*> m_globalAttributesByName;
	map<String, Type*> m_globalTypes;

protected:

	XmlData::Element* m_documentElement;
};

}	// XS
}	// System

#endif // XmlSchema_h
