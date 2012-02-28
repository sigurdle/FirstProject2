#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

unsigned int ResourceDictionary::get_Count()
{
	return m_items.size();
}

bool ResourceDictionary::get_IsReadOnly()
{
	return false;
}

ResourceDictionary::ResourceDictionary()
{
	m_MergedDictionaries = new Vector<ResourceDictionary*>;
}

Vector<ResourceDictionary*>* ResourceDictionary::get_MergedDictionaries()
{
	return m_MergedDictionaries;
}

void ResourceDictionary::set_MergedDictionaries(Vector<ResourceDictionary*>* mergedDictionaries)
{
	m_MergedDictionaries = mergedDictionaries;
}

void ResourceDictionary::set_Source(Uri* source)
{
	if (m_Source != source)
	{
		Clear();

		m_Source = source;
		/*
		UrlBinding binding;
		IO::ISequentialByteStream* stream = binding.BindToObject(m_Source->m_absolute, NULL);
		*/

		Application::LoadComponent(this, m_Source);
	}
}

#if 0
virtual const Type_Info& ResourceDictionary::GetItemType() const
{
	return typeid(Object*);
}

virtual unsigned int ResourceDictionary::GetCount()
{
}
/*
virtual void ResourceDictionary::Clear()
{
}
*/
virtual void ResourceDictionary::AddObject(Object* element)
{
	Add
}
#endif

// IDictionary

Object* ResourceDictionary::get_Item(Object* key)
{
	if (m_recurse)
	{
		throw new Exception(WSTR("Recursive call"));
		return NULL;
	}

	++m_recurse;

	Object* value = m_items.find(key)->second;
	if (value)
	{
		--m_recurse;
		return value;
	}

	// Do this here ??
	unsigned int count = m_MergedDictionaries->GetCount();
	for (unsigned int i = 0; i < count; i++)
	{
		ResourceDictionary* dict = m_MergedDictionaries->get_Item(i);
		
		value = dict->get_Item(key);
		if (value)
		{
			--m_recurse;
			return value;
		}
	}

	--m_recurse;
	return NULL;
}

void ResourceDictionary::set_Item(Object* key, Object* value)
{
	m_items[key] = value;
}

void ResourceDictionary::Clear()
{
	m_items.clear();
}

bool ResourceDictionary::Contains(Object* key)
{
	return m_items.find(key) != m_items.end();
}

void ResourceDictionary::Add(Object* key, Object* value)
{
	m_items[key] = value;

//	m_items.insert(items_t::value_type(key, value));

//	RegisterName(dynamic_cast<StringW*>(key), value);
}

void ResourceDictionary::Remove(Object* key)
{
	ASSERT(0);
}

// INameScope
Object* ResourceDictionary::FindName(StringW* name)
{
//	return m_items.find(name)->second;

	// Not implemented for ResourceDictionary
	throw new Exception(WSTR("not implemented"));
	return NULL;
}

void ResourceDictionary::RegisterName(StringW* name, Object* scopedElement)
{
	// Not implemented for ResourceDictionary
	throw new Exception(WSTR("not implemented"));

//	m_items.insert(items_t::value_type(name, scopedElement));
}

void ResourceDictionary::UnregisterName(StringW* name)
{
	throw new Exception(WSTR("not implemented"));
	ASSERT(0);
}

}
}
