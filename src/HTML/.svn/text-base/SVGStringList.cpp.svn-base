#include "stdafx.h"
#include "HTML2.h"
#include "SVGStringList.h"

namespace System
{
namespace Web
{

SVGStringList::SVGStringList()
{
//		m_bLockUpdate = 0;
//		m_nChanges = 0;
//		m_pListener = NULL;
}

SVGStringList::~SVGStringList()
{
	RemoveAll();
//		ASSERT(m_pListener == NULL);
}

void SVGStringList::RemoveAll()
{
	m_items.RemoveAll();
}

unsigned int SVGStringList::get_numberOfItems() const
{
	return m_items.GetSize();
}

void SVGStringList::clear()
{
	if (m_items.GetSize() > 0)
	{
		RemoveAll();

		if (m_pListener)
			m_pListener->OnChanged(this);
	}
}

String SVGStringList::appendItem(StringIn newItem)
{
	m_items.Add((newItem));

	if (m_pListener)
		m_pListener->OnChanged(this);

	return newItem;
}

String SVGStringList::removeItem(unsigned int index)
{
	if (index < m_items.GetSize())
	{
		String oldvalue = m_items[index];

		m_items.RemoveAt(index);

		if (m_pListener)
			m_pListener->OnChanged(this);

		return oldvalue;
	}

	return NULL;
}

String SVGStringList::replaceItem(StringIn newItem, unsigned int index)
{
	ASSERT(0);
	return NULL;
}

String SVGStringList::insertItemBefore(StringIn newItem, unsigned int index)
{
	ASSERT(0);
	return newItem;
}

String SVGStringList::getItem(unsigned int index)
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
	{
		return NULL;
	}
}

String SVGStringList::initialize(StringIn newItem)
{
	ASSERT(0);
	return newItem;
}

void SVGStringList::CopyFrom(SVGStringList* value)
{
	ASSERT(0);
}

void SVGStringList::Add(SVGStringList* value)
{
	ASSERT(0);
}

void SVGStringList::InterpolateValue(SVGStringList* a, SVGStringList* b, double t)
{
	ASSERT(0);
}

String SVGStringListCommaSeparated::getStringValue()
{
	String str = WSTR("");

	for (size_t i = 0; i < m_items.GetSize(); ++i)
	{
		ASSERT(0);
#if 0
		if (i > 0) str += ',';
		str += m_items[i];
#endif
	}

	return str;
}

void SVGStringListCommaSeparated::setStringValue(StringIn str)
{
	GetCommaSepStringArray(str, m_items);
}

String SVGStringListSemicolonSeparated::getStringValue()
{
	String str = NULL;

	for (size_t i = 0; i < m_items.GetSize(); ++i)
	{
		ASSERT(0);
#if 0

		if (i > 0) str += ';';
		str += m_items[i];
#endif
	}

	return str;
}

void SVGStringListSemicolonSeparated::setStringValue(StringIn str)
{
	GetSemicolonSepStringArray(str, m_items);
}

String SVGStringListSpaceSeparated::getStringValue()
{
	String str = NULL;//OLESTR("");

	for (size_t i = 0; i < m_items.GetSize(); ++i)
	{
		ASSERT(0);
#if 0
		if (i > 0) str += ' ';
		str += m_items[i];
#endif
	}

	return str;
}

void SVGStringListSpaceSeparated::setStringValue(StringIn str)
{
	GetSpaceSepStringArray(str, m_items);
}

}	// Web
}
