#include "stdafx.h"
#include "LXUI2.h"
#include "Thickness.h"

namespace System
{
namespace UI
{

Thickness::Thickness()
{
	m_Left = 0.0;
	m_Top = 0.0;
	m_Right = 0.0;
	m_Bottom = 0.0;
}

Thickness::Thickness(double Left, double Top, double Right, double Bottom)
{
	m_Left = Left;
	m_Top = Top;
	m_Right = Right;
	m_Bottom = Bottom;
}

Thickness::Thickness(double len)
{
	m_Left = len;
	m_Top = len;
	m_Right = len;
	m_Bottom =  len;
}

bool Thickness::Equals(const Thickness& other) const
{
	return	m_Left == other.m_Left &&
				m_Top == other.m_Top &&
				m_Right == other.m_Right &&
				m_Bottom == other.m_Bottom;
}

double Thickness::get_Left() const
{
	return m_Left;
}

/*
void Thickness::put_Left(Length* newVal)
{
	m_Left = newVal;
}
*/

double Thickness::get_Top() const
{
	return m_Top;
}

/*
void Thickness::put_Top(Length* newVal)
{
	m_Top = newVal;
}
*/

double Thickness::get_Right() const
{
	return m_Right;
}

/*
void Thickness::put_Right(Length* newVal)
{
	m_Right = newVal;
}
*/

double Thickness::get_Bottom() const
{
	return m_Bottom;
}

/*
void Thickness::put_Bottom(Length* newVal)
{
	m_Bottom = newVal;
}
*/

#if 0

Thickness::Thickness(const Thickness& other)
{
	printf("UI::Thickness::Thickness:other(%p)\n", other.m_p);

	m_p = other.m_p;
	if (m_p)
	{
		long refcount = m_p->AddRef();
		printf("refcount: %d\n", refcount);
	}
	printf("done\n");
}

Thickness::Thickness(_Thickness* p)
{
	printf("UI::Thickness::Thickness(%p)\n", p);

	m_p = p;
	if (m_p)
	{
		long refcount = m_p->AddRef();
		printf("refcount: %d\n", refcount);
	}
	printf("done\n");
}

/*
Thickness::Thickness(const Object2& other)
{
	m_p = dynamic_cast<_Thickness*>(other.m_p);
	if (m_p)
	{
		m_p->AddRef();
	}
}
*/

Thickness::Thickness(Length Left, Length Top, Length Right, Length Bottom)
{
	m_p = new _Thickness(Left, Top, Right, Bottom);
	m_p->AddRef();
}

Thickness::Thickness(Length len)
{
	m_p = new _Thickness(len);
	m_p->AddRef();
}

Thickness::~Thickness()
{
	printf("Thickness::~Thickness\n");

	if (m_p)
		m_p->Release();
}

/*
Thickness::operator Object2 () const
{
	return m_p;
}
*/

/*
Thickness::operator _Thickness* () const
{
	printf("Thickness::operator _Thickness*\n");
	return m_p;
}
*/

Thickness& Thickness::operator = (const Thickness& other)
{
	printf("UI::Thickness::operator =\n");
	printf("other(%p)\n", other.m_p);

	_Thickness* old = m_p;

	printf("%p\n", old);

	m_p = other.m_p;
	if (m_p)
	{
		long refcount = m_p->AddRef();
		printf("refcount %d\n", refcount);
	}
	if (old) old->Release();

	printf("done\n");

	return *this;
}

void Thickness::BeforeChange()
{
	if (m_p == NULL)
	{
		m_p = new _Thickness;
	}
	else if (m_p->m_refcount > 1)
	{
		_Thickness* old = m_p;
		m_p = new _Thickness(m_p->m_Left, m_p->m_Top, m_p->m_Right, m_p->m_Bottom);
		m_p->AddRef();
		old->Release();
	}
}

Length Thickness::get_Left() const
{
	return m_p->m_Left;
}

void Thickness::put_Left(Length newVal)
{
	BeforeChange();
	m_p->m_Left = newVal;
}

Length Thickness::get_Top() const
{
	return m_p->m_Top;
}

void Thickness::put_Top(Length newVal)
{
	BeforeChange();
	m_p->m_Top = newVal;
}

Length Thickness::get_Right() const
{
	return m_p->m_Right;
}

void Thickness::put_Right(Length newVal)
{
	BeforeChange();
	m_p->m_Right = newVal;
}

Length Thickness::get_Bottom() const
{
	return m_p->m_Bottom;
}

void Thickness::put_Bottom(Length newVal)
{
	BeforeChange();
	m_p->m_Bottom = newVal;
}

bool Thickness::ReferenceEquals(const Thickness& other) const
{
	return m_p == other.m_p;
}

bool Thickness::Equals(const Thickness& other) const
{
	if (m_p == other.m_p) return true;
	if (m_p == NULL) return false;
	if (other.m_p == NULL) return false;
	return m_p->Equals(*other.m_p);
}

#endif

}	// UI
}
