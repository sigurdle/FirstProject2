#include "stdafx.h"
#include "LXML2.h"
#include "RGBColor.h"

#include "CSSPrimitiveValue.h"

namespace System
{
namespace Web
{

RGBColor::RGBColor()
{
	m_pListener = NULL;

	m_red = new CSSPrimitiveValue;
	m_green = new CSSPrimitiveValue;
	m_blue = new CSSPrimitiveValue;
	m_alpha = 1.0;

// Get notification of changes
	m_red->m_pListener = this;
	m_green->m_pListener = this;
	m_blue->m_pListener = this;
}

RGBColor::~RGBColor()
{
	ASSERT(m_pListener == NULL);

	m_red->m_pListener = NULL;
	delete m_red;

	m_green->m_pListener = NULL;
	delete m_green;

	m_blue->m_pListener = NULL;
	delete m_blue;
}

#if 0
int RGBColor::FinalConstruct()
{
	HRESULT hr;

	ASSERT(0);
	/*
	hr = CComObject<CSSPrimitiveValue>::CreateInstance(&m_red);
	if (FAILED(hr)) return hr;
	m_red->AddRef();

	hr = CComObject<CSSPrimitiveValue>::CreateInstance(&m_green);
	if (FAILED(hr)) return hr;
	m_green->AddRef();

	hr = CComObject<CSSPrimitiveValue>::CreateInstance(&m_blue);
	if (FAILED(hr)) return hr;
	m_blue->AddRef();
*/
// Get notification of changes
	m_red->m_pListener = this;
	m_green->m_pListener = this;
	m_blue->m_pListener = this;

	return S_OK;
}

void RGBColor::FinalRelease()
{
	if (m_red)
	{
		m_red->m_pListener = NULL;
//		m_red->Release();
		m_red = NULL;
	}

	if (m_green)
	{
		m_green->m_pListener = NULL;
//		m_green->Release();
		m_green = NULL;
	}

	if (m_blue)
	{
		m_blue->m_pListener = NULL;
//		m_blue->Release();
		m_blue = NULL;
	}
}
#endif

CSSPrimitiveValue* RGBColor::get_red()
{
	return m_red;
}

CSSPrimitiveValue* RGBColor::get_green()
{
	return m_green;
}

CSSPrimitiveValue* RGBColor::get_blue()
{
	return m_blue;
}

double RGBColor::get_alpha()
{
	return m_alpha;
}

void RGBColor::set_alpha(double newVal)
{
	if (newVal != m_alpha)
	{
		m_alpha = newVal;

		if (m_pListener)
		{
			m_pListener->OnChangedRGBColor(this);
		}
	}
}

}	// Web
}
