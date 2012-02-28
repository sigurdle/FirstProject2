#include "stdafx.h"
#include "LXML.h"

#include "ASDTDModel.h"
#include "ASDTDAttribute.h"

namespace System
{
namespace Web
{

ASDataType CASDTDAttribute::get_dataType() const
{
	ASSERT(0);
	return OTHER_SIMPLE_DATATYPE;
}

void CASDTDAttribute::set_dataType(ASDataType newVal)
{
}

String CASDTDAttribute::get_dataValue()
{
	return m_value;
}

void CASDTDAttribute::set_dataValue(StringIn newVal)
{
	m_value = newVal;
}

String CASDTDAttribute::get_enumAttr()
{
	ASSERT(0);
	return nullptr;
#if 0

	sysstring str = OLESTR("");

	for (int i = 0; i < m_enums.GetSize(); i++)
	{
		if (i > 0) str += OLESTR("|");
		str += m_enums[i];
	}

	return str;
#endif
}

void CASDTDAttribute::set_enumAttr(StringIn newVal)
{
	ASSERT(0);
}

ASValueConstraint CASDTDAttribute::get_defaultType() const
{
	return m_defaultType;
}

void CASDTDAttribute::set_defaultType(ASValueConstraint newVal)
{
	m_defaultType = newVal;
}

}	// Web
}
