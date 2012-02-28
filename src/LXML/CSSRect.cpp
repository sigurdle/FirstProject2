#include "stdafx.h"
#include "LXML.h"
#include "CSSRect.h"

#include "CSSPrimitiveValue.h"

namespace System
{
namespace Web
{

CSSRect::CSSRect()
{
	m_pListener = NULL;

	m_top = new CSSPrimitiveValue;
	m_right = new CSSPrimitiveValue;
	m_bottom = new CSSPrimitiveValue;
	m_left = new CSSPrimitiveValue;

// Get notification of changes

	m_top->m_pListener = this;
	m_right->m_pListener = this;
	m_bottom->m_pListener = this;
	m_left->m_pListener = this;
}

CSSRect::~CSSRect()
{
	ASSERT(m_pListener == NULL);

	if (m_top)
	{
		m_top->m_pListener = NULL;
//		m_top->Release();
		m_top = NULL;
	}

	if (m_right)
	{
		m_right->m_pListener = NULL;
//		m_right->Release();
		m_right = NULL;
	}

	if (m_bottom)
	{
		m_bottom->m_pListener = NULL;
//		m_bottom->Release();
		m_bottom = NULL;
	}

	if (m_left)
	{
		m_left->m_pListener = NULL;
//		m_left->Release();
		m_left = NULL;
	}
}

CSSPrimitiveValue* CSSRect::get_top()
{
	return m_top;
}

CSSPrimitiveValue* CSSRect::get_right()
{
	return m_right;
}

CSSPrimitiveValue* CSSRect::get_bottom()
{
	return m_bottom;
}

CSSPrimitiveValue* CSSRect::get_left()
{
	return m_left;
}

}	// Web
}
