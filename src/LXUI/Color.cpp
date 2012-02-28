#include "stdafx.h"
#include "LXUI.h"

#include "Color.h"

namespace System
{
namespace UI
{

Color::Color()
{
	m_A = 0;
	m_R = 0;
	m_G = 0;
	m_B = 0;

	m_ScA = 0.0f;
	m_ScR = 0.0f;
	m_ScG = 0.0f;
	m_ScB = 0.0f;

	m_ColorContext = NULL;
}

Color::Color(uint8 R, uint8 G, uint8 B)
{
	m_A = 255;
	m_R = R;
	m_G = G;
	m_B = B;

	m_ScA = 1.0f;
	m_ScR = R/255.0f;
	m_ScG = G/255.0f;
	m_ScB = B/255.0f;

	m_ColorContext = NULL;
}

Color::Color(uint8 A, uint8 R, uint8 G, uint8 B)
{
	m_A = A;
	m_R = R;
	m_G = G;
	m_B = B;

	m_ScA = A/255.0f;
	m_ScR = R/255.0f;
	m_ScG = G/255.0f;
	m_ScB = B/255.0f;

	m_ColorContext = NULL;
}

Color::Color(float ScR, float ScG, float ScB)
{
	m_ScA = 1.0f;
	m_ScR = ScR;
	m_ScG = ScG;
	m_ScB = ScB;

	SyncARGB();

	m_ColorContext = NULL;
}

Color::Color(float ScA, float ScR, float ScG, float ScB)
{
	m_ScA = ScA;
	m_ScR = ScR;
	m_ScG = ScG;
	m_ScB = ScB;

	SyncARGB();

	m_ColorContext = NULL;
}

Color::Color(LDraw::Color color)
{
	m_A = color.GetA();
	m_R = color.GetR();
	m_G = color.GetG();
	m_B = color.GetB();

	m_ScA = m_A/255.0f;
	m_ScR = m_R/255.0f;
	m_ScG = m_G/255.0f;
	m_ScB = m_B/255.0f;

	m_ColorContext = NULL;
}

void Color::SyncARGB()
{
	if (m_ScA <= 0)
		m_A = 0;
	else if (m_ScA >= 1)
		m_A = 255;
	else
		m_A = (uint8)(m_ScA*255);

	if (m_ScR <= 0)
		m_R = 0;
	else if (m_ScR >= 1)
		m_R = 255;
	else
		m_R = (uint8)(m_ScR*255);

	if (m_ScG <= 0)
		m_G = 0;
	else if (m_ScG >= 1)
		m_G = 255;
	else
		m_G = (uint8)(m_ScG*255);

	if (m_ScB <= 0)
		m_B = 0;
	else if (m_ScB >= 1)
		m_B = 255;
	else
		m_B = (uint8)(m_ScB*255);
}

/*
uint8 Color::get_R() const
{
	return m_R;
}

uint8 Color::get_G() const
{
	return m_G;
}

uint8 Color::get_B() const
{
	return m_B;
}

uint8 Color::get_A() const
{
	return m_A;
}
*/

/*
Color* Color::Clone() const
{
	return new Color(m_R, m_G, m_B, m_A);
}
*/

void Color::Clamp()
{
	if (m_ScA < 0) m_ScA = 0;
	else if (m_ScA > 1) m_ScA = 1;

	if (m_ScR < 0) m_ScR = 0;
	else if (m_ScR > 1) m_ScR = 1;

	if (m_ScG < 0) m_ScG = 0;
	else if (m_ScG > 1) m_ScG = 1;

	if (m_ScB < 0) m_ScB = 0;
	else if (m_ScB > 1) m_ScB = 1;
}

bool Color::AreClose(Color color1, Color color2)
{
	ASSERT(0);
	//if (gmFuzEq
	return false;
}

bool Color::Equals(Object* other)
{
	if (this == NULL && other == NULL) return true;
	if (this == NULL) return false;
	if (other == NULL) return false;

	if (other->GetType() != GetType()) return false;
	return Equals(*static_cast<Color*>(other));
}

bool Color::operator == (const Color& other) const
{
	if (m_ScR != other.m_ScR) return false;
	if (m_ScG != other.m_ScG) return false;
	if (m_ScB != other.m_ScB) return false;
	if (m_ScA != other.m_ScA) return false;

	return true;
}

bool Color::Equals(Color other) const
{
	if (m_ScR != other.m_ScR) return false;
	if (m_ScG != other.m_ScG) return false;
	if (m_ScB != other.m_ScB) return false;
	if (m_ScA != other.m_ScA) return false;

	/*
	if (m_R != other.m_R) return false;
	if (m_G != other.m_G) return false;
	if (m_B != other.m_B) return false;
	if (m_A != other.m_A) return false;
	*/

	return true;
}

uint32 Color::GetHashCode()
{
	return (((uint32)m_R)<<24) | (((uint32)m_G)<<16) | (((uint32)m_B)<<8) | m_A;
}

// static
Color Color::FromRgb(uint8 R, uint8 G, uint8 B)
{
	return Color(R, G, B);
}

// static
Color Color::FromArgb(uint8 A, uint8 R, uint8 G, uint8 B)
{
	return Color(A, R, G, B);
}

// static
Color Color::FromScRgb(float ScR, float ScG, float ScB)
{
	return Color(ScR, ScG, ScB);
}

// static
Color Color::FromScArgb(float ScA, float ScR, float ScG, float ScB)
{
	return Color(ScA, ScR, ScG, ScB);
}

Color Color::operator + (const Color& other) const
{
	return FromScArgb(
		m_ScA + other.m_ScA,
		m_ScR + other.m_ScR,
		m_ScG + other.m_ScG,
		m_ScB + other.m_ScB);
}

Color& Color::operator += (const Color& other)
{
	m_ScA += other.m_ScA;
	m_ScR += other.m_ScR;
	m_ScG += other.m_ScG;
	m_ScB += other.m_ScB;

	SyncARGB();

	return *this;
}

/*
Color operator - (const Color& other) const;
Color& operator -= (const Color& other);

Color operator * (const Color& other) const;
Color& operator *= (const Color& other);
*/

#if 0
Color::Color()
{
	m_p = NULL;
}

Color::Color(_Color* p)
{
	m_p = p;
	if (m_p)
	{
		m_p->addref();
	}
}

Color::Color(const Color& other)
{
	m_p = other.m_p;
	if (m_p)
	{
		m_p->addref();
	}
}

Color::Color(uint8 R, uint8 G, uint8 B)
{
	m_p = new _Color(R, G, B);
	m_p->addref();
}

Color::Color(uint8 R, uint8 G, uint8 B, uint8 A)
{
	m_p = new _Color(R, G, B, A);
	m_p->addref();
}

Color::Color(LDraw::Color color)
{
	m_p = new _Color(color);
	m_p->addref();
}

Color::~Color()
{
	if (m_p)
	{
		m_p->Release();
	}
}

Color::operator Object() const
{
	return m_p;
}

uint8 Color::get_R() const
{
	ASSERT(m_p);
	if (m_p == NULL)
	{
		THROW(-1);
	}
	return m_p->m_R;
}

void Color::set_R(uint8 newVal)
{
	ASSERT(m_p);
	if (m_p == NULL)
	{
		THROW(-1);
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();

		m_p = new _Color(m_p->m_A, newVal, m_p->m_G, m_p->m_B);
		m_p->addref();
	}
	else
	{
		m_p->m_R = newVal;
	}
}

uint8 Color::get_G() const
{
	ASSERT(m_p);
	if (m_p == NULL)
	{
		THROW(-1);
	}
	return m_p->m_G;
}

void Color::set_G(uint8 newVal)
{
	ASSERT(m_p);
	if (m_p == NULL)
	{
		THROW(-1);
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();

		m_p = new _Color(m_p->m_A, m_p->m_R, newVal, m_p->m_G);
		m_p->addref();
	}
	else
	{
		m_p->m_G = newVal;
	}
}

uint8 Color::get_B() const
{
	ASSERT(m_p);
	if (m_p == NULL)
	{
		THROW(-1);
	}
	return m_p->m_B;
}

void Color::set_B(uint8 newVal)
{
	ASSERT(m_p);
	if (m_p == NULL)
	{
		THROW(-1);
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();

		m_p = new _Color(m_p->m_A, m_p->m_R, m_p->m_G, newVal);
		m_p->addref();
	}
	else
	{
		m_p->m_B = newVal;
	}
}

uint8 Color::get_A() const
{
	ASSERT(m_p);
	if (m_p == NULL)
	{
		THROW(-1);
	}
	return m_p->m_A;
}

void Color::set_A(uint8 newVal)
{
	ASSERT(m_p);
	if (m_p == NULL)
	{
		THROW(-1);
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();

		m_p = new _Color(newVal, m_p->m_R, m_p->m_G, m_p->m_B);
		m_p->addref();
	}
	else
	{
		m_p->m_A = newVal;
	}
}

Color& Color::operator = (const Color& other)
{
	_Color* old = m_p;
	m_p = other.m_p;
	if (m_p) m_p->addref();
	if (old) old->Release();

	return *this;
}

bool Color::ReferenceEquals(const Color& other) const
{
	return m_p == other.m_p;
}

bool Color::Equals(const Color& other) const
{
	if (m_p == other.m_p) return true;
	if (m_p == NULL) return false;
	if (other.m_p == NULL) return false;
	return m_p->Equals(*other.m_p);
}
#endif

}	// UI
}
