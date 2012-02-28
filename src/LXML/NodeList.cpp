#include "stdafx.h"
#include "LXML.h"
#include "NodeList.h"

namespace System
{
namespace Web
{

NodeList::NodeList()
{
}

NodeList::~NodeList()
{
}

unsigned int NodeList::get_length() const
{
	return m_items.size();
}

ChildNode* NodeList::item(unsigned int index) const
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
		return NULL;
}

}	// w3c
}
