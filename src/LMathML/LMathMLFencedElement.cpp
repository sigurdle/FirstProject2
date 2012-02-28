// LMathMLFencedElement.cpp : Implementation of CLMathMLFencedElement
#include "stdafx.h"
#include "LHTML.h"
#include "LHTML2.h"

#include "LMathMLFencedElement.h"

/////////////////////////////////////////////////////////////////////////////
// CLMathMLFencedElement

STDMETHODIMP CLMathMLFencedElement::get_open(/*[out, retval]*/ BSTR *pVal)
{
	return getAttribute(L"open", pVal);
}

STDMETHODIMP CLMathMLFencedElement::put_open(/*[in]*/ BSTR newVal)
{
	return S_OK;
}

STDMETHODIMP CLMathMLFencedElement::get_close(/*[out, retval]*/ BSTR *pVal)
{
	return getAttribute(L"close", pVal);
}

STDMETHODIMP CLMathMLFencedElement::put_close(/*[in]*/ BSTR newVal)
{
	return S_OK;
}

STDMETHODIMP CLMathMLFencedElement::get_separators(/*[out, retval]*/ BSTR *pVal)
{
	return getAttribute(L"separators", pVal);
}

STDMETHODIMP CLMathMLFencedElement::put_separators(/*[in]*/ BSTR newVal)
{
	return S_OK;
}
