#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

Object DependencyProperty::s_UnsetValue;

DependencyProperty::DependencyProperty(const Type_Info& type, const Type_Info& ownerType, const PropertyMetaData& metadata) : m_type(type), m_ownerType(ownerType), m_metadata(metadata)
{
	m_name = NULL;
//	m_ownerClassName = NULL;
	m_defaultValue = NULL;
}

StringW* DependencyProperty::GetName() const
{
	return m_name;
}

}
}
