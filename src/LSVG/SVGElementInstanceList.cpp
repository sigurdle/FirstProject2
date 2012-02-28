#include "stdafx.h"
#include "LSVG2.h"
#include "SVGElementInstanceList.h"

namespace System
{
namespace Web
{

unsigned int SVGElementInstanceList::get_length() const
{
	return static_cast<unsigned int>(m_items.size());
}

SVGElementInstance* SVGElementInstanceList::item(unsigned int index)
{
	if (index < m_items.size())
		return m_items[index];
	else
		return nullptr;
}

}	// Web
}	// System
