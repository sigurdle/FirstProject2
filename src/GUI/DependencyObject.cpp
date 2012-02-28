#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

// static
DependencyClass* DependencyObject::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), nullptr);
	return &depclass;
}

DependencyObject::DependencyObject(DependencyClass* depClass)
{
	unsigned int localPropertiesCount = depClass->GetLocalPropertiesCount();
	m_localProperties.assign(new PropertyValue*[localPropertiesCount], localPropertiesCount);

	CreateProperties(depClass);
}

void DependencyObject::CreateProperties(DependencyClass* depClass)
{
	if (DependencyClass* baseClass = depClass->GetBaseClass())
	{
		CreateProperties(baseClass);
	}

	for (size_t i = 0; i < depClass->m_localProperties.size(); ++i)
	{
		DependencyProperty* dp = depClass->m_localProperties[i];
		
		ASSERT(m_localProperties[dp->m_localIndex] == nullptr);
		m_localProperties[dp->m_localIndex] = new PropertyValue(this, dp);

		if (Expressive::Expression* dpExp = dp->get_Expression())
		{
			ExpressionBinding* expBinding = new ExpressionBinding(this, dpExp);
			m_localProperties[dp->m_localIndex]->SetInputBinding(expBinding);
		}
	}
}

void DependencyObject::AddNotify(IObjectChangedNotify* callback)
{
	ASSERT(m_notifyList.find(callback) == m_notifyList.end());
	m_notifyList.insert(m_notifyList.end(), callback);
}

DependencyClass* DependencyObject::GetClass()
{
	return DependencyClass::GetClass(GetType());
}

PropertyValue* DependencyObject::GetExistingProperty(DependencyProperty* dp)
{
	VerifyArgumentNotNull(dp);

	if (dp->m_localIndex < m_localProperties.size() &&
		m_localProperties[dp->m_localIndex]->m_dp == dp)
	{
		return m_localProperties[dp->m_localIndex];
	}
	else
	{
		auto it = m_attachedProperties.find(dp->m_globalUid);
		if (it != m_attachedProperties.end())
		{
			return it->second;
		}
	}

	return nullptr;
}

PropertyValue* DependencyObject::GetProperty(DependencyProperty* dp)
{
	VerifyArgumentNotNull(dp);

	if (dp->m_localIndex < m_localProperties.size() &&
		m_localProperties[dp->m_localIndex]->m_dp == dp)
	{
		return m_localProperties[dp->m_localIndex];
	}
	else
	{
		PropertyValue*& p = m_attachedProperties[dp->m_globalUid];
		if (p == nullptr)
		{
			p = new PropertyValue(this, dp);
		}

		return p;
	}
}

void DependencyObject::UpdatePropertyObjectValue(DependencyProperty* dp, const Variant& value)
{
	GetProperty(dp)->UpdateValue(value);
}

bool DependencyObject::HasComputedPropertyValue(DependencyProperty* dp)
{
	return false;
}

Variant DependencyObject::GetComputedPropertyObjectValue2(DependencyProperty* dp)
{
	return nullptr;
}

Variant DependencyObject::GetComputedValue(DependencyProperty* dp)
{
	if (this == nullptr)
	{
		raise(Exception(S("Accessing null object")));
	}

	PropertyValue* p = GetExistingProperty(dp);
	if (p)
		return p->GetComputedValue();
	else
		return dp->get_DefaultValue();
}

Variant DependencyObject::GetPropertyValue(DependencyProperty* dp)
{
	return GetComputedValue(dp);
}

void DependencyObject::SetPropertyValue(DependencyProperty* dp, const Variant& value)
{
	if (this == nullptr) raise(SystemException(S("null object")));
	if (dp == nullptr) raise(ArgumentNullException());

	PropertyValue* p = GetProperty(dp);

	if (p->m_inBinding != nullptr && p->m_localValue.IsUndefined())
	{
		p->UpdateValue(value);
	}
	else
	{
		p->SetLocalValue(value);
	}
}

void DependencyObject::SetPropertyValue(DependencyProperty* dp, String value)
{
	SetPropertyValue(dp, Variant(value));
}

void DependencyObject::ClearPropertyValue(DependencyProperty* dp)
{
	PropertyValue* p = GetExistingProperty(dp);
	if (p)
	{
		if (!p->m_localValue.IsUndefined())
		{
			p->m_localValue = Variant();
			ASSERT(0);
			// TODO
		}
	}
}

bool DependencyObject::HasLocalPropertyValue(PropertyValue* pPropertyVal)
{
	if (pPropertyVal == nullptr) raise(ArgumentNullException());

	// TODO, some other place
	return !pPropertyVal->m_localValue.IsUndefined();
}

Variant DependencyObject::GetLocalPropertyValue(PropertyValue* pPropertyVal)
{
	if (pPropertyVal == nullptr) raise(ArgumentNullException());

	// TODO, some other place
	return pPropertyVal->m_localValue;
}

void DependencyObject::ClearLocalPropertyValue(PropertyValue* pPropertyVal)
{
	if (pPropertyVal == nullptr) raise(ArgumentNullException());
	pPropertyVal->m_localValue = Variant();
}

String DependencyObject::ToString()
{
	IO::StringWriter stream;
	stream << GetType()->m_name;
	return stream.str();
}

String DependencyObject::ToMLString()
{
	map<Object*,int> defs;

	IO::StringWriter stream;
	WriteMLString(stream, defs);

	return stream.str();
}

IO::TextWriter& DependencyObject::WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs)
{
	pair<map<Object*,int>::iterator,bool> it = defs.insert(map<Object*,int>::value_type(this, defs.size()+1));
	if (!it.second)
	{
		stream << "use(" << it.first->second << ")";
		return stream;
	}

	stream << GetType()->m_name;
	stream << "\n{\n";

	for (size_t i = 0; i < m_localProperties.size(); ++i)
	{
		PropertyValue* pProperty = m_localProperties[i];

		if (!pProperty->m_localValue.IsUndefined())
		{
			stream << "\t";
			stream << pProperty->m_dp->get_Name();
			stream << " ";

			if (DependencyObject* depobj = __dynamic_cast<DependencyObject*>(pProperty->m_localValue))
			{
				depobj->WriteMLString(stream, defs);
			}
			else if (VisualCollection* vc = __dynamic_cast<VisualCollection*>(pProperty->m_localValue))
			{
				for (auto it = vc->m_items.begin(); it != vc->m_items.end(); ++it)
				{
					Visual* item = *it;
					item->WriteMLString(stream, defs);
				}
			}
			else if (!pProperty->m_localValue.IsUndefined())
			{
				stream << pProperty->m_localValue.ToString();
			}
			else
			{
				stream << "nil";
			}
			stream << "\n";
		}
		else if (pProperty->m_inBinding != nullptr)
		{
			stream << "\t";
			stream << pProperty->m_dp->get_Name();
			stream << " ";

			if (ExpressionBinding* exp = dynamic_cast<ExpressionBinding*>(pProperty->m_inBinding))
			{
				exp->m_exp->WriteMLString(stream, defs);
			}
			stream << "\n";
		}
	}

	stream << "}";

	return stream;
}

void DependencyObject::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	// Notify listeners that this object has changed

	for (auto it = m_notifyList.begin(); it != m_notifyList.end(); ++it)
	{
		IObjectChangedNotify* callback = *it;
		callback->OnObjectChanged(this);	// TODO?? OnContentChanged
	}
}

void DependencyObject::OnComputedPropertyValueChanging(PropertyValue* pPropertyVal, const Variant& oldValue, const Variant& newValue, bool handled)
{
}

//////////////////////////////////

DependencyObject* GetTemplatedOwner(DependencyObject* depObject)
{
	UIElement* uielement = dynamic_cast<UIElement*>(depObject);
	if (uielement)
	{
		return uielement->get_TemplatedOwner();
	}

	return nullptr;
}

}	// Gui
}	// System
