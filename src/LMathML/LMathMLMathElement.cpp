// LMathMLMathElement.cpp : Implementation of CLMathMLMathElement
#include "stdafx.h"
#include "LHTML.h"
#include "LHTML2.h"

#include "LMathMLMathElement.h"

/////////////////////////////////////////////////////////////////////////////
// CLMathMLMathElement

STDMETHODIMP CLMathMLMathElement::get_macros(/*[out, retval]*/ BSTR *pVal)
{
	return S_OK;
}

STDMETHODIMP CLMathMLMathElement::put_macros(/*[in]*/ BSTR newVal)
{
	return S_OK;
}

STDMETHODIMP CLMathMLMathElement::get_display(/*[out, retval]*/ BSTR *pVal)
{
	return S_OK;
}

STDMETHODIMP CLMathMLMathElement::put_display(/*[in]*/ BSTR newVal)
{
	return S_OK;
}
