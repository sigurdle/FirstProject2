#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

int globalPropertyCount = 0;

DependencyClass::Map_t* DependencyClass::s_classes;
map<String, DependencyProperty*>* DependencyClass::s_properties;

DependencyClass* DependencyClass::GetClass(ClassType* pClassType)
{
	DependencyClass* depClass = (DependencyClass*)pClassType->GetUserData(L"System::Gui::DependencyClass");
	/*
	if (depClass == NULL)
	{
		if (pClassType == typeid(DependencyObject).GetType())
		{
			depClass = new DependencyClass(pClassType, NULL);
			pClassType->SetUserData(L"System::Gui::DependencyClass", depClass);

			return depClass;
		}
		else
		{
			ASSERT(pClassType->m_bases.size() > 0);
			depClass = new DependencyClass(pClassType, GetClass(pClassType->m_bases[0]->m_pClass->GetClass()));
			pClassType->SetUserData(L"System::Gui::DependencyClass", depClass);
		}
	}
	*/

	return depClass;
}

DependencyClass::DependencyClass(const Type_Info& classType, DependencyClass* baseClass) :
	m_classType(classType),
	m_localPropertyStart(0),
	m_localPropertyCount(0)
{
	ClassType* pClassType = classType.GetType()->AsClass();
	ASSERT(pClassType);

	if (baseClass)
	{
		m_localPropertyStart = baseClass->GetLocalPropertiesCount();
		m_localPropertyCount = baseClass->GetLocalPropertiesCount();
	}

	ASSERT(pClassType->GetUserData(L"System::Gui::DependencyClass") == nullptr);
	pClassType->SetUserData(L"System::Gui::DependencyClass", this);

	m_registered = Register();
}

DependencyClass::~DependencyClass()
{
	Unregister(m_registered);
}

DependencyClass::Map_t::iterator DependencyClass::Register()
{
	if (s_classes == nullptr)
	{
		s_classes = new map<String, DependencyClass*>;
	}
	return (*s_classes).insert(Map_t::value_type(m_classType.GetType()->AsClass()->get_Name(), this)).first;
//	return (*s_classes).insert(Map_t::value_type(get_Name(), this)).first;
}

void DependencyClass::Unregister(Map_t::iterator it)
{
	// TODO
}

/*
unsigned int DependencyClass::GetComputedPropertiesCount() const
{
	return m_computedCount;
}
*/

DependencyProperty* DependencyClass::GetLocalProperty(unsigned int index)
{
	if (index < m_localProperties.size())
	{
		return m_localProperties[index];
	}
	else
	{
		ASSERT(0);
		throw new ArgumentOutOfRangeException();
	}
}

DependencyProperty* DependencyClass::GetLocalProperty(StringIn name)
{
	for (size_t i = 0; i < m_localProperties.size(); ++i)
	{
		if (m_localProperties[i]->get_Name() == name)
		{
			return m_localProperties[i];
		}
	}

	DependencyClass* baseClass = GetBaseClass();
	if (baseClass)
	{
		return baseClass->GetLocalProperty(name);
	}

	return nullptr;
}

ClassType* DependencyClass::GetClassType() const throw()
{
	return m_classType.GetType()->AsClass();
}

DependencyClass* DependencyClass::GetBaseClass() const throw()
{
	return (DependencyClass*)GetClassType()->m_bases[0]->m_pClass->AsClass()->GetUserData(L"System::Gui::DependencyClass");
}

void DependencyClass::RegisterProperty(DependencyProperty* dp)
{
	if (dp == nullptr) throw new ArgumentNullException();

	dp->m_localIndex = m_localPropertyCount++;
	dp->m_globalUid = globalPropertyCount++;

	m_localProperties.push_back(dp);

	if (s_properties == nullptr)
	{
		s_properties = new map<String, DependencyProperty*>;
	}

	(*s_properties)[dp->get_Name()] = dp;

//	dp->m_localIndex = index;
//	return dp->m_localIndex;
}

// static
DependencyClass* DependencyClass::FindClass(StringIn name) throw()
{
	return (*s_classes).find(name)->second;
}

//static
DependencyProperty* DependencyClass::FindGlobalProperty(StringIn name) throw()
{
	return (*s_properties).find(name)->second;
}

}	// Gui
}	// System
