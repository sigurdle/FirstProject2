#include "stdafx.h"
#include "LXML2.h"
#include "NameList.h"

namespace System
{
namespace Web
{

NameList::NameList()
{
}

unsigned int NameList::get_length() const
{
	return m_items.GetSize();
}

String NameList::getName(unsigned int index)
{
	if (index < m_items.GetSize())
	{
		return m_items[index].m_name;
	}
	else
		return nullptr;
}

String NameList::getNamespaceURI(unsigned int index)
{
	if (index < m_items.GetSize())
	{
		return m_items[index].m_namespaceURI;
	}
	else
		return nullptr;
}

}	// Web
}	// System
