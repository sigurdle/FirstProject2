#include "stdafx.h"
#include "LFC.h"
#include "Archive.h"

namespace System
{

Archive& Archive::operator >> (String &value)
{
	ASSERT(0);
	/*
	int len;
	*this >> len;
	value = new StringA(string_alloc<char>(len));
	Read(value->begin(), len);
	*/
	return *this;
}

Archive& Archive::operator << (String value)
{
	ASSERT(0);
	/*
	*this << value->Length();
	Write(value->c_str(), value->Length());
	*/
	return *this;
}

/*
Archive& Archive::operator << (StringW* value)
{
	*this << value->Length();
	Write(value->c_str(), value->Length()*2);
	return *this;
}
*/

ClassType* Archive::ReadClass()
{
	uint16 id;
	*this >> id;

	if (id == 0)
	{
		return NULL;
	}

	map<uint16, ClassType *>::iterator it = m_classmapLoad.find(id);
	if (it != m_classmapLoad.end())
	{
		return (*it).second;
	}
	else
	{
		ASSERT(0);
#if 0
		if (true)
		{
			/*
			Class* pClass;
			*this >> pClass;
			*/
			Class* pClass = new Class;
			m_classmapLoad.insert(map<uint16, Class *>::value_type(id, pClass));
			pClass->Load(*this);
			return pClass;
		}
		else
		{
			StringA qname;
			*this >> qname;
			Class * pClass = pD->LookupNamedType(qname)->GetClass();

			m_classmapLoad.insert(map<uint16, Class *>::value_type(id, pClass));

			return pClass;
		}
#endif
		return NULL;
	}
}

void Archive::WriteClass(ClassType* pClass)
{
	map<ClassType *, uint16>::iterator it = m_classmapSave.find(pClass);
	if (it != m_classmapSave.end())
	{
		*this << (*it).second;
	}
	else
	{
		uint16 id = m_classmapSave.size()+1;
		m_classmapSave.insert(map<ClassType *, uint16>::value_type(pClass, id));

		*this << id;
		/*
		if (true)
		{
			pClass->Store(*this);
			//*this << pClass;
		}
		else
		*/
		{
			*this << pClass->m_qname;
		}
	}
}

Archive& Archive::operator >> (Object* & object)
{
	uint32 id;
	*this >> id;

	if (id == 0)
	{
		object = NULL;
		return *this;
	}

	map<uint32,void*>::iterator it = m_objectmapLoad.find(id);
	if (it != m_objectmapLoad.end())
	{
		object = (Object*)(*it).second;
	}
	else
	{
	//	StringA classname;
	//	*this >> classname;

		ClassType* pClass = ReadClass();

#if WIN32
	//	Class* pClass = pD->LookupNamedType(classname)->GetClass();
		Object* pobj = newobj(pClass);
		if (pobj)
		{
		//	object = (Object*)DynamicCast(pobj, pClass, pD->LookupNamedType("System::Object")->GetClass());
			object = pobj;

			m_objectmapLoad.insert(map<uint32, void*>::value_type(id, object));

			dynamic_cast<ISerializable*>(object)->Load(*this);
		}
		else
			THROW(-1);
#else

	//	_ObjectImpl* object;

		ASSERT(0);

		StringA classname;

		if (classname == "Class")
		{
			Class* pobj = new Class;
			object = dynamic_cast<_ObjectImpl*>(pobj);
		}
		else if (classname == "PrimitiveType")
		{
			PrimitiveType* pobj = new PrimitiveType;
			object = dynamic_cast<_ObjectImpl*>(pobj);
		}
		else if (classname == "CFunction")
		{
			CFunction* pobj = new CFunction;
			object = dynamic_cast<_ObjectImpl*>(pobj);
		}
		else if (classname == "Namespace")
		{
			Namespace* pobj = new Namespace;
			object = dynamic_cast<_ObjectImpl*>(pobj);
		}
		else
		{
			printf("Unknown %s\n", classname.c_str());
			ASSERT(0);
		}

		m_objectmapLoad.insert(map<uint32, void*>::value_type(id, object));

		dynamic_cast<ISerializable*>(object)->Load(*this);

#endif
	}

	return *this;
}

Archive& Archive::operator << (const Object* object)
{
	if (object == NULL)
	{
		uint32 id = 0;
		*this << id;
		return *this;
	}

	map<const void*,uint32>::iterator it = m_objectmapSave.find((const void*)object);
	if (it != m_objectmapSave.end())
	{
		*this << (*it).second;
	}
	else
	{
		uint32 id = m_objectmapSave.size()+1;
		m_objectmapSave.insert(map<const void*,uint32>::value_type((void*)object, id));

		*this << id;

		ClassType* pType = GetType(object);
		//*this << pType->GetName();
		WriteClass(pType);
		dynamic_cast<const ISerializable*>(object)->Store(*this);
	}

	return *this;
}

void Archive::MapObject(const Object* object)
{
	if (m_bIsStoring)
	{
		map<const void*, uint32>::iterator it = m_objectmapSave.find((void*)object);
		if (it == m_objectmapSave.end())
		{
			m_objectmapSave.insert(map<const void*, uint32>::value_type(object, m_objectmapSave.size()+1));
		}
	}
}

void Archive::MapClass(ClassType* pClass)
{
	if (m_bIsStoring)
	{
		map<ClassType *, uint16>::iterator it = m_classmapSave.find(pClass);
		if (it == m_classmapSave.end())
		{
			m_classmapSave.insert(map<ClassType *, uint16>::value_type(pClass, m_classmapSave.size()+1));
		}
		else
			ASSERT(0);
	}
	else
	{
		m_classmapLoad.insert(map<uint16, ClassType *>::value_type(m_classmapLoad.size()+1, pClass));
	}
}

}
