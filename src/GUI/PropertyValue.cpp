#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

PropertyValue::PropertyValue(DependencyObject* owner, DependencyProperty* dp) :
	m_owner(owner),
	m_dp(dp)//,
//	m_localValue(&UnsetValue),
//	m_computedValue(&UnsetValue)
{
}

Type* PropertyValue::GetOutputType()
{
	return m_dp->get_Type().GetType();
}

void PropertyValue::OnObjectChanged(Object* object)
{
	OnComputedValueChanged();
}

void PropertyValue::OnComputedValueChanged()
{
	if (m_valueChanged == false)
	{
		m_valueChanged = true;
		m_owner->OnComputedPropertyValueChanged(this, false);
		m_valueChanged = false;
	}
}

void PropertyValue::OnComputedValueChanging(const Variant& oldValue, const Variant& newValue)
{
	if (m_valueChanged == false)
	{
		m_valueChanged = true;
		m_owner->OnComputedPropertyValueChanging(this, oldValue, newValue, false);
		m_valueChanged = false;
	}
}

inline bool IsUndefined(const Variant& v)
{
	return v.IsUndefined();
}

Variant PropertyValue::GetComputedValue()
{
	if (IsUndefined(m_computedValue))
	{
		Variant localValue = m_owner->GetLocalPropertyValue(this);
		if (!localValue.IsUndefined())
		{
			m_computedValue = localValue;
		}
		else if (m_inBinding)
		{
			try
			{
				m_computedValue = m_inBinding->GetOutput(this);
			}
			catch (Exception* e)
			{
			//	ASSERT(0);
				// TODO
				m_computedValue = m_dp->get_DefaultValue();//Variant(m_dp->GetPropertyType());
			}

			// TODO... 

			PropertyMetadata* metadata = m_dp->get_Metadata();
			if (metadata && metadata->m_notifyOnValueChange)
			{
				// Setup to listen for changes to the object
				DependencyObject* depObject = __dynamic_cast<DependencyObject*>(m_computedValue);
				if (depObject)
				{
					depObject->AddNotify(this);
				}
			}
		}
		else if (m_owner->HasComputedPropertyValue(m_dp))
		{
			m_computedValue = m_owner->GetComputedPropertyObjectValue2(m_dp);
		}
		else
		{
			m_computedValue = GetPropertyDefinition()->get_DefaultValue();
		}
	}

	return m_computedValue;
}

Variant PropertyValue::GetLocalValue()
{
	return m_owner->GetLocalPropertyValue(this);
}

void PropertyValue::SetLocalValue(const Variant& localValue)
{
	// TODO
	//m_owner->SetLocalPropertyValue(this);
	m_localValue = localValue;

	PropertyMetadata* metadata = m_dp->get_Metadata();
	if (metadata && metadata->m_notifyOnValueChange)
	{
		// Setup to listen for changes to the object
		DependencyObject* depObject = __dynamic_cast<DependencyObject*>(m_localValue);
		if (depObject)
		{
			depObject->AddNotify(this);
		}
	}

	// TODO, don't update here if in init phase

// TODO, if there are times that computed value isn't set to localValue, then don't need to update anything either

	Variant oldValue = m_computedValue;

	m_computedValue = Variant();
	Variant newValue = GetComputedValue();
	m_computedValue = oldValue;

	OnComputedValueChanging(oldValue, newValue);

	m_computedValue = newValue;
	OnComputedValueChanged();

	SendComputedValueDownStream();
}

/*

The difference between UpdateObjectValue and SetOutput is that UpdateObjectValue is called from us, while
SetOutput comes from one of our outbindings
*/

void PropertyValue::UpdateValue(const Variant& value)
{
//	SetOutput(NULL, value);

	// If we have our local value alreay set, we replace it with the new value
	// Also, if we have no incoming, we set the localValue

	Variant localValue = m_owner->GetLocalPropertyValue(this);
	if (!localValue.IsUndefined() || m_inBinding == nullptr)
	{
		m_localValue = value;	// TODO

	// TODO, if there are times that computed value isn't set to localValue, then don't need to update anything either
		m_computedValue = Variant();//&UnsetValue;
		m_computedValue = GetComputedValue();
		OnComputedValueChanged();

		SendComputedValueDownStream();
	}
	else
	{
		m_inBinding->SetOutput(this, value);
	}
}

int PropertyValue::SetOutput(IBinding* caller, const Variant& value)
{

//	ASSERT(m_outBindings.find(caller) != m_outBindings.end());

	// If we have our local value alreay set, we replace it with the new value
	// Also, if we have no incoming, we set the localValue

	Variant localValue = m_owner->GetLocalPropertyValue(this);

	if (!localValue.IsUndefined() || m_inBinding == nullptr)
	{
		m_localValue = value;	// TODO
	// TODO, if there are times that computed value isn't set to localValue, then don't need to update anything either
		m_computedValue = Variant();
		m_computedValue = GetComputedValue();
		OnComputedValueChanged();

		SendComputedValueDownStreamExcept(caller);
	}
	else
	{
		m_inBinding->SetOutput(this, value);
	}

	return 0;
}

Variant PropertyValue::GetOutput(IBinding* caller)
{
	return GetComputedValue();
}

int PropertyValue::SetInput(IBinding* caller, const Variant& value)
{

	// TODO
#if 0
	if (GetPropertyDefinition()->get_Type().GetType()->get_Kind() == type_class)
	{
		ASSERT(value.GetType()->IsDerivedFrom(GetPropertyDefinition()->get_Type().GetType()->GetClass()));
	}
#endif

	ASSERT(caller == m_inBinding);

//	Object* localValue = m_owner->GetLocalPropertyValue(this);
//	if (localValue == &UnsetValue)
	if (!m_owner->HasLocalPropertyValue(this))
	{
		m_computedValue = value;
		OnComputedValueChanged();
		//m_computedValue = &UnsetValue;
		//m_computedValue = GetComputedObjectValue();
	}

	SendComputedValueDownStream();

	return 0;
}

int PropertyValue::SendComputedValueDownStreamExcept(IBinding* exceptThis)
{
	int result = 0;

	for (auto it = m_outBindings.begin(); it != m_outBindings.end(); ++it)
	{
		IInputBinding* binding = *it;

	//	if (binding != exceptThis)
		{
			int result2 = binding->SetInput(this, m_computedValue);
			if (result2)
			{
				++result;
			}
		}
	}

	return result;
}

void* PropertyValue::Connect(IInputBinding* binding)
{
	/*
	if (!binding->GetOutputType()->IsOfType(GetOutputType()))
	{
		ASSERT(0);
		return NULL;
	}
	*/
	ASSERT(m_outBindings.find(binding) == m_outBindings.end());
	return m_outBindings.insert(m_outBindings.end(), binding).m_ptr;
}

void PropertyValue::SetInputBinding(IBinding* inBinding)
{
	ASSERT(m_inBinding == nullptr);

	if (inBinding == nullptr) raise(ArgumentNullException());

	m_inBinding = inBinding;
	m_inBindingPtr = m_inBinding->Connect(this);

//	Object* localValue = m_owner->GetLocalPropertyValue(this);
//	if (localValue == &UnsetValue)
	if (!m_owner->HasLocalPropertyValue(this))
	{
		m_computedValue = Variant();
		OnComputedValueChanged();

		// TODO, update here, unless in init phase
	}
}

}	// Gui
}	// System
