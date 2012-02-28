#pragma once

#include "LDOMElementImpl.h"

template <class T, class IBase = CLDOMElementImplImpl> class ATL_NO_VTABLE CLMathMLElementImpl :
	public CLDOMElementImpl<T, IBase>
//	public CLSVGElementImplImpl
{
public:
	CLMathMLElementImpl()
	{
	}

	int FinalConstruct()
	{
		return CLDOMElementImpl<T, IBase>::FinalConstruct();
	}

	void FinalRelease()
	{
		CLDOMElementImpl<T, IBase>::FinalRelease();
	}

// ILMathMLElementImpl
	STDMETHODIMP put_className(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHODIMP get_className(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHODIMP put_mathElementStyle(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHODIMP get_mathElementStyle(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHODIMP put__id(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHODIMP get__id(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHODIMP put_xref(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHODIMP get_xref(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHODIMP put_href(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHODIMP get_href(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHODIMP get_ownerMathElement(/*[out, retval]*/ ILMathMLMathElement* *pVal)
	{
		return S_OK;
	}
};
