#include "stdafx.h"
#include "LXUI.h"

#include "Length.h"

namespace System
{
namespace UI
{

Length::Length()
{
	m_Value = 0;
	m_UnitType = LengthUnits::Auto;
}

Length::Length(double Value)
{
	m_Value = Value;
	m_UnitType = LengthUnits::Auto;
}

Length::Length(double Value, LengthUnits::LengthUnit unitType)
{
	m_Value = Value;
	m_UnitType = unitType;
}

Length::~Length()
{
}

bool Length::Equals(const Length& other) const
{
	return m_UnitType == other.m_UnitType && m_Value == other.m_Value;
}

#if 0
Length::Length()
{
	m_p = NULL;//new _Length(0, UnitAuto);
	//m_p->AddRef();
//	m_pListener = NULL;
}

Length::Length(_Length* p)
{
//	m_pListener = NULL;
	m_p = p;
	if (m_p) m_p->AddRef();
}

Length::Length(const Length& other)
{
//	m_pListener = NULL;
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
}

Length::Length(const Object& other)
{
//	m_pListener = NULL;
	m_p = dynamic_cast<_Length*>(other.m_p);
	if (m_p) m_p->AddRef();
}

Length::Length(double Value, LengthUnits::LengthUnit unitType)
{
	m_p = new _Length(Value, unitType);
	m_p->AddRef();

//	m_pListener = NULL;
}

Length::~Length()
{
	if (m_p) m_p->Release();
//	ASSERT(m_pListener == NULL);
}

Length& Length::operator = (const Length& other)
{
	_Length* old = m_p;
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
	if (old) old->Release();

	return *this;
}

bool Length::ReferenceEquals(const Length& other) const
{
	return m_p == other.m_p;
}

bool Length::Equals(const Length& other) const
{
	if (m_p == other.m_p)
		return true;
	else if (m_p == NULL)
		return false;
	else if (other.m_p == NULL)
		return false;
	else
		return *m_p == *other.m_p;
}

Length::operator Object () const
{
	return m_p;
}
#endif

double Length::get_Value() const
{
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/
	return m_Value;
}

#if 0
void Length::put_Value(double newVal)
{
	if (m_p->m_Value != newVal)
	{
		if (m_p->m_refcount > 1)
		{
			_Length* p = new _Length(newVal, m_p->m_UnitType);
			p->AddRef();

			m_p->Release();
			m_p = p;
		}
		else
		{
			m_p->m_Value = newVal;
		}

//		if (m_pListener)
//			m_pListener->OnChanged(this);
	}
}
#endif

LengthUnits::LengthUnit Length::get_UnitType() const
{
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/
	return m_UnitType;
}

}	// UI
}
