#ifndef RDF_h
#define RDF_h

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LFC.typeinfo"
#else
#include "LFC/LFC.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/XML.typeinfo"
#else
#include "XML/XML.h"
#endif

#ifndef RDFEXT
#define RDFEXT DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace rdf
{

class RDFEXT RdfBase : public Object
{
public:

	/*
	CTOR RdfBase(StringIn name) : m_value(name)
	{
	}
	*/

	CTOR RdfBase(StringIn uri) : m_uri(uri)
	{
	}

	String m_uri;
};

/*
class RDFEXT Predicate : public RdfBase
{
public:
	CTOR Predicate(StringIn name) : RdfBase(name)
	{
	}

	static Predicate* type;
};
*/

class Resource;
typedef Resource Predicate;

class RDFEXT predicate
{
public:

	CTOR predicate(Predicate* p) : m_p(p)
	{
	}

	bool operator < (const predicate& other) const;
	bool operator == (const predicate& other) const;

	operator Predicate* () const
	{
		return m_p;
	}

	Predicate* m_p;
};

class RDFEXT Literal
{
public:

	CTOR Literal()
	{
	}

	CTOR Literal(int int32val)
	{
		u.int32val = int32val;
	}

	CTOR Literal(double float64val)
	{
		u.float64val = float64val;
	}

	CTOR Literal(String value) : m_datatype(NULL)
	{
		m_string = value;
	}

	CTOR Literal(String value, Resource* datatype) : m_datatype(datatype)
	{
		m_string = value;
	}

	CTOR Literal(const Literal& other) : m_string(other.m_string), m_datatype(other.m_datatype)
	{
		u.int64val = other.u.int64val;
	}

	String ToString()
	{
		// TODO
		return m_string;
	}

	union
	{
		int32 int32val;
		int64 int64val;
		double float64val;
	}
	u;

	String m_string;
	Resource* m_datatype;
};

class ObjectVariant
{
public:

	CTOR ObjectVariant(Literal lit) : m_literal(lit)
	{
	}

	CTOR ObjectVariant(Resource* resource) : m_resource(resource)
	{
	}

	String ToString();

	Literal m_literal;
	Resource* m_resource;
};

class RDFEXT Resource : public Object
{
public:
	CTOR Resource(StringIn uri) : m_uri(uri)
	{
	}

	/*
	CTOR Resource(StringIn value, Resource* datatype) : RdfBase(name), m_datatype(datatype)
	{
	}
	*/

	virtual String ToString() override;

	String get_URI()
	{
		return m_uri;
	}

	String m_uri;
	//Resource* m_datatype;

	void SetProperty(Resource* pred, Literal obj);
	void SetProperty(Resource* pred, Resource* obj);
	void SetProperty(Resource* pred, ObjectVariant obj);

	multimap<predicate, ObjectVariant> m_properties;
};

inline bool predicate::operator < (const predicate& other) const
{
	return m_p->m_uri < other.m_p->m_uri;
}

inline bool predicate::operator == (const predicate& other) const
{
	return m_p->m_uri == other.m_p->m_uri;
}

/*
class RDFEXT RdfObject : public Ptr
{
public:
};
*/

/*
class RDFEXT Triple
{
public:
	Subject* m_subject;
	Predicate* m_predicate;
	Subject* m_object;
};
*/

class RDFEXT Model
{
	Resource* GetSubject(StringIn prefix, StringIn local);
	Resource* GetSubject(StringIn uri);

	Resource* GetClass(ClassType* pClass);
	Resource* GetInstance(Object* pObject);

	void GenClass(ClassType* pClass, Resource* pSubject);
	void GenInstanceFields(ClassType* pClass, Object* pObject, Resource* pSubject);

	map<String, Resource*> m_subjects;
};

// Serializing
RDFEXT void NT(Stream& stream, Resource* subject);
RDFEXT void N3(Stream& stream, Resource* subject);
RDFEXT XmlData::Element* ToXML(XmlData::Document* document, Resource* subject);

//
RDFEXT void MapNS(StringIn uri, StringIn prefix);

extern String rdfURI;
extern String rdfsURI;

class RDFEXT RDF
{
public:
	static Resource* get_type();

private:
	CTOR RDF();
};

class RDFEXT RDFS : public RDF
{
public:
	static Resource* get_Class();
	static Resource* get_subClassOf();
	static Resource* get_subPropertyOf();
	static Resource* get_domain();
	static Resource* get_range();

private:
	CTOR RDFS();
};

class RDFEXT OWL : public RDFS
{
public:
	static Resource* get_DataTypeProperty();
	static Resource* get_ObjectProperty();

	static Resource* get_Inverse();
};

}

class RDFEXT Person : public Object
{
public:

	CTOR Person(StringIn fname, StringIn lname, int age);

	String m_firstname;
	String m_lastname;
	int m_age;
};

}	// System

#include "TurtleParser.h"

#endif // RDF_h
