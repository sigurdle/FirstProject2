// LMathMLImplementation.cpp : Implementation of CLMathMLImplementation
#include "stdafx.h"
#include "LMathML.h"
#include "..\LHTML\LHTML2.h"
#include "LMathMLImplementation.h"

#include "LMathMLElement.h"
#include "LMathMLMathElement.h"
#include "LMathMLFencedElement.h"

/////////////////////////////////////////////////////////////////////////////
// CLMathMLImplementation

STDMETHODIMP CLMathMLImplementation::CreateElement(BSTR namespaceURI, BSTR localName, ILDOMElement* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComPtr<ILDOMElement> newElement;

	if (!cmpbstr(namespaceURI, L"http://www.w3.org/1998/Math/MathML"))
	{
		if (!wcscmp(localName, L"math"))
		{
			CComObject<CLMathMLMathElement>* pElement;
			CComObject<CLMathMLMathElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!wcscmp(localName, L"mfenced"))
		{
			CComObject<CLMathMLFencedElement>* pElement;
			CComObject<CLMathMLFencedElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else	// Generic/Unknown element
		{
			CComObject<CLMathMLElement>* pElement;
			CComObject<CLMathMLElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
	}

	*pVal = newElement;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLMathMLImplementation::CreateViewElement(ILDOMElement* element, CXMLDocumentView* pView, IUnknown* *pVal)
{
	// TODO
	*pVal = NULL;
	return S_OK;
}
