// RDF.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RDF.h"

namespace System
{
namespace rdf
{

String rdfURI = "http://www.w3.org/1999/02/22-rd-syntax-ns#";
String rdfsURI = "http://www.w3.org/1999/02/22-rdfs-ns#";	// TODO
String owlURI = "http://www.w3.org/1999/02/22-owl-ns#";	// TODO



map<String, String> m_mapping;	// prefix to uri

Resource* RDF::get_type()
{
	static Resource* p = GetSubject("rdf", "type");
	return p;
}

Resource* RDFS::get_Class()
{
	static Resource* p = GetSubject("rdfs", "Class");
	return p;
}

Resource* RDFS::get_subClassOf()
{
	static Resource* p = GetSubject("rdfs", "subClassOf");
	return p;
}

Resource* RDFS::get_subPropertyOf()
{
	static Resource* p = GetSubject("rdfs", "subPropertyOf");
	return p;
}

Resource* RDFS::get_domain()
{
	static Resource* domain = GetSubject("rdfs", "domain");
	return domain;
}

Resource* RDFS::get_range()
{
	static Resource* range = GetSubject("rdfs", "range");
	return range;
}

Resource* OWL::get_DataTypeProperty()
{
	static Resource* p = GetSubject("owl", "DataTypeProperty");
	return p;
}

Resource* OWL::get_ObjectProperty()
{
	static Resource* p = GetSubject("owl", "ObjectProperty");
	return p;
}

Resource* Model::GetSubject(StringIn prefix, StringIn localName)
{
	String uri = m_mapping[prefix];
	String fulluri = uri + localName;

	pair<map<String, Resource*>::iterator, bool> r = m_subjects.insert(map<String, Resource*>::value_type(fulluri, NULL));
	if (r.second == true)
	{
		r.first->second = new Resource(fulluri);
	}

	return r.first->second;
}

Resource* Model::GetSubject(StringIn subjectUri)
{
	pair<map<String, Resource*>::iterator, bool> r = m_subjects.insert(map<String, Resource*>::value_type(String(subjectUri), NULL));
	if (r.second == true)
	{
		r.first->second = new Resource(subjectUri);
	}

	return r.first->second;
}

Resource** Model::NewSubject(StringIn subjectUri)
{
	pair<map<String, Resource*>::iterator, bool> r = m_subjects.insert(map<String, Resource*>::value_type(String(subjectUri), NULL));
	/*
	if (r.second == true)
	{
		r.first->second = new Subject(subject);
	}
	*/

	return &r.first->second;
}

/*
RDFEXT Subject* FindSubject(StringIn subject)
{
	return m_subjects.find(subject)->second;
}
*/

//Predicate* Predicate::type = new Predicate("type");

void Model::AddTriple(StringIn subjectstr, StringIn predicatestr, StringIn objectstr)
{
	Resource* subject = GetSubject(subjectstr);
	Resource* pred = GetSubject(predicatestr);
	Resource* obj = GetSubject(objectstr);

	subject->m_properties.insert(multimap<predicate, Resource*>::value_type(pred, obj));
}

/*
RDFEXT void AddTriple(Subject* subject, Subject* predicatestr, StringIn objectstr)
{
	Subject* subject = GetSubject(subjectstr);
	Subject* pred = GetSubject(predicatestr);
	Subject* obj = GetSubject(objectstr);

	subject->m_properties.insert(multimap<predicate, Subject*>::value_type(pred, obj));
}
*/

String Resource::ToString()
{
	return get_URI();
}

void Resource::SetProperty(Resource* pred, Resource* obj)
{
	m_properties.insert(multimap<predicate, ObjectVariant>::value_type(pred, obj));
}

void Resource::SetProperty(Resource* pred, ObjectVariant obj)
{
	m_properties.insert(multimap<predicate, ObjectVariant>::value_type(pred, obj));
}

RDFEXT Resource* GetClass(ClassType* pClass)
{
	String uri = pClass->get_QName();

	Resource** subject = NewSubject(uri);
	if (*subject == NULL)	// If it doesn't previously exist
	{
		*subject = new Resource(uri);
		GenClass(pClass, *subject);
	}

	return *subject;
}

RDFEXT void GenClass(ClassType* pClass, Resource* pClassSubject)
{
	pClassSubject->SetProperty(RDF::get_type(), RDFS::get_Class());

	for (uint i = 0; i < pClass->m_bases.size(); ++i)
	{
		BaseClass* pBase = pClass->m_bases[i];
		Resource* pSuperClass = GetClass(pBase->get_Class());

		pClassSubject->SetProperty(RDFS::get_subClassOf(), pSuperClass);
	}

	for (uint i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* decl = pClass->m_pScope->m_orderedDecls[i];

		if (decl->m_pType)
		{
			Type* pType = decl->m_pType->GetStripped();

			if (!decl->m_static && pType->get_Kind() != type_function)
			{
				Resource* pred = GetSubject(pClass->m_qname + decl->m_name);

				pred->SetProperty(RDFS::get_domain(), pClassSubject);

				switch (pType->get_Kind())
				{
					/*
				case type_bool:
					{
						Variant value = *(bool*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_short_int:
					{
						Variant value = *(short*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_unsigned_short_int:
					{
						Variant value = *(unsigned short*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_int:
					{
						Variant value = *(int*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_unsigned_int:
					{
						Variant value = *(unsigned int*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_float:
					{
						Variant value = *(float*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_double:
					{
						Variant value = *(double*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;
					*/

				case type_pointer:
					{
						if (pType->GetPointerTo()->GetStripped()->get_Kind() == type_class)
						{
							ClassType* pClassPtr = pType->GetPointerTo()->GetClass();
							Resource* pRange = GetClass(pClassPtr);

							// Or should this always be inferred ?

							pred->SetProperty(RDFS::get_range(), pRange);
						}
					}
					break;

					/*
				case type_class:
					{
						if (pType->GetClass() == typeid(String).GetType())
						{
							Variant value = *(String*)(((byte*)pObject) + decl->m_offset);

							obj = GetSubject(value.ToString());
						}
						else if (pType->GetClass() == typeid(StringVariant).GetType())
						{
							Variant value = *(StringVariant*)(((byte*)pObject) + decl->m_offset);

							obj = GetSubject(value.ToString());
						}
						else if (pType->GetClass() == typeid(Variant).GetType())
						{
							Variant value = *(Variant*)(((byte*)pObject) + decl->m_offset);

							obj = GetSubject(value.ToString());
						}
					}
					break;
					*/
				}
			}
		}
	}
}

RDFEXT Resource* GetInstance(Object* pObject)
{
	String uri = pObject->GetType()->get_QName() + "_1";

	Resource** ppSubject = NewSubject(uri);
	if (*ppSubject)	// If it previously exists
	{
		return *ppSubject;
	}

	*ppSubject = new Resource(uri);
	Resource* pSubject = *ppSubject;

	pSubject->SetProperty(RDF::get_type(), GetClass(pObject->GetType()));

	GenInstanceFields(pObject->GetType(), pObject, pSubject);

	return pSubject;
}

RDFEXT void GenInstanceFields(ClassType* pClass, Object* pObject, Resource* pSubject)
{
	for (size_t i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* decl = pClass->m_pScope->m_orderedDecls[i];

		Resource* pred = GetSubject(decl->m_name);

		if (decl->m_pType)
		{
			Type* pType = decl->m_pType->GetStripped();

			Resource* obj = NULL;

			if (!decl->m_static && pType->get_Kind() != type_function)
			{
				switch (pType->get_Kind())
				{
				case type_bool:
					{
						Variant value = *(bool*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_short:
					{
						Variant value = *(short*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_unsigned_short:
					{
						Variant value = *(unsigned short*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_int:
					{
						Variant value = *(int*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_unsigned_int:
					{
						Variant value = *(unsigned int*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_float:
					{
						Variant value = *(float*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_double:
				case type_long_double:
					{
						Variant value = *(double*)(((byte*)pObject) + decl->m_offset);
						obj = GetSubject(value.ToString());
					}
					break;

				case type_pointer:
					{
						if (pType->GetPointerTo()->GetStripped()->get_Kind() == type_class)
						{
							ClassType* pClass2 = pType->GetPointerTo()->GetClass();
							if (pClass2->IsLeftMostDerivedFrom(typeof(Object)->GetClass()))
							{
								Object* value = *(Object**)(((byte*)pObject) + decl->m_offset);
								if (value)
								{
									obj = GetInstance(value);
								}
							}
						}
					}
					break;

				case type_class:
					{
						if (pType->GetClass() == typeid(String).GetType())
						{
							Variant value = *(String*)(((byte*)pObject) + decl->m_offset);

							obj = GetSubject(value.ToString());
						}
						else if (pType->GetClass() == typeid(StringVariant).GetType())
						{
							Variant value = *(StringVariant*)(((byte*)pObject) + decl->m_offset);

							obj = GetSubject(value.ToString());
						}
						else if (pType->GetClass() == typeid(Variant).GetType())
						{
							Variant value = *(Variant*)(((byte*)pObject) + decl->m_offset);

							// TODO, object

							obj = GetSubject(value.ToString());
						}
					}
					break;
				}

				if (obj)
				{
					pSubject->SetProperty(pred, obj);
				}
			}
		}
	}
}

String ObjectVariant::ToString()
{
	if (m_resource)
		return m_resource->ToString();
	else
		return m_literal.ToString();
}

RDFEXT void NT(IO::TextWriter& stream, Resource* subject)
{
	multimap<predicate, ObjectVariant>::iterator it = subject->m_properties.begin();
	while (it != subject->m_properties.end())
	{
		Resource* pred = it->first;
		ObjectVariant obj = it->second;

		stream << "<" << subject->get_URI() << "> ";
		stream << "<" << pred->get_URI() << "> ";
		stream << "<" << obj.ToString();//->get_URI() << ">.";
		stream << "\n";

		++it;
	}
}

RDFEXT void MapNS(StringIn uri, StringIn prefix)
{
	m_mapping[uri] = prefix;
}

RDFEXT void N3(Stream& stream, Resource* subject)
{
	ASSERT(0);
#if 0
	for (map<String, String>::iterator it = m_mapping.begin(); it != m_mapping.end(); ++it)
	{
		stream << "@prefix " << it->second << ":" << "<" << it->first << ">";
		stream << "\n";
	}

	stream << subject->m_value << " ";

	multimap<predicate, Resource*>::iterator it = subject->m_properties.begin();
	while (it != subject->m_properties.end())
	{
		if (it != subject->m_properties.begin()) stream << ";\n";

		Subject* pred = it->first;
//		Subject* obj = it->second;

		if (pred->get_URI() == rdfURI && pred->m_value == "type")
		{
			stream << "a ";	// shorthand
		}
		else
		{
			stream << pred->m_value << " ";
		}

		multimap<predicate, Subject*>::iterator it2 = it;
		do
		{
			if (it != it2) stream << ",";

			stream << it2->second->m_value;
			++it2;
		}
		while (it2 != subject->m_properties.end() && it2->first == it->first);

		++it;
	}

	stream << ".\n";
#endif
}

/*
ParseN3()
{
}
*/

/*
ShowTimeline()
{
}
*/

}

Person::Person(StringIn fname, StringIn lname, int age) :
 m_firstname(fname),
 m_lastname(lname),
 m_age(age)
{
}

}
