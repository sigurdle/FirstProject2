#include "stdafx.h"
#include "LXUI2.h"
#include <functional>

namespace System
{
namespace UI
{

Freezable::Freezable()
{
	m_isFrozen = false;
//	m_nonFreezableSubObjects = 0;
}

bool Freezable::get_CanFreeze()
{
#if 0
	// If any subobjects are non-freezable, then this is also non-freezable
	connections_type::iterator it = m_connections.begin();
	while (it != m_connections.end())
	{
		if (!it->first->get_CanFreeze())
			return false;

		++it;
	}
#endif
	return true;
	/*
	if (m_nonFreezableSubObjects > 0)
		return false;
	else
		return true;
		*/
}

void Freezable::Freeze()
{
	FreezeCore(false);
}

// virtual
bool Freezable::FreezeCore(bool isChecking)
{
	if (get_CanFreeze())
	{
		m_isFrozen = true;
		return true;
	}
	else
	{
		if (isChecking)
			return false;
		else
			throw std::exception("Cannot freeze");
	}
}

// virtual
void Freezable::OnChanged()
{
}

void Freezable::Changed()
{
	OnChanged();
	ChangedSignal(this);
}

void Freezable::OnPropertyChanged(DependencyPropertyChangedEventArgs args)
{
	DependencyObject::OnPropertyChanged(args);

	// hm..
//	ASSERT(newValue == NULL);
//	newValue = GetValue(pProperty);

	OnFreezablePropertyChanged(
		args.get_OldValue()? dynamic_cast<Freezable*>(args.get_OldValue()) : NULL,
		args.get_NewValue()? dynamic_cast<Freezable*>(args.get_NewValue()) : NULL,
		args.get_Property());
}

void Freezable::OnFreezablePropertyChanged(Freezable* oldValue, Freezable* newValue, DependencyProperty* dp)
{
	int dpindex = dp->gindex;

	if (oldValue != newValue)
	{
		if (oldValue)
		{
			//if (oldValue->get_CanFreeze())
			oldValue->ChangedSignal.disconnect(m_dp_connections[dpindex]);
		}

		if (newValue)
		{
//			m_connections.insert(connections_type::value_type(newValue, ChangedSignal.connect(newValue->ChangedSignal)));
		//	connections_type::iterator it = m_connections.find(p);
		//	if (p == m_connections.end())
			{
				m_dp_connections[dpindex] = newValue->ChangedSignal.connect(std::bind1st(std::mem_fun1(&DependencyObject::OnChanged), this));
			}
		}
	}

	Changed();
}

void Freezable::OnFreezablePropertyChanged(Freezable* oldValue, Freezable* newValue)
{
	ASSERT(0);
#if 0
	if (oldValue != newValue)
	{
		if (oldValue)
		{
			//if (oldValue->get_CanFreeze())
			oldValue->ChangedSignal.disconnect(m_connections.find(oldValue)->second);
		}

		if (newValue)
		{
//			m_connections.insert(connections_type::value_type(newValue, ChangedSignal.connect(newValue->ChangedSignal)));
		//	connections_type::iterator it = m_connections.find(p);
		//	if (p == m_connections.end())
			{
				m_connections.insert(connections_type::value_type(newValue, newValue->ChangedSignal.connect(std::bind1st(std::mem_fun1(&DependencyObject::OnChanged), this))));
			}
		}
	}

	Changed();
#endif
}

}
}
