#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#if 0
#include "LHTMLElement.h"
#include "LHTMLFrameElement.h"
#include "LHTMLIFrameElement.h"
#include "LHTMLFrameSetElement.h"
#include "LHTMLBodyElement.h"
#include "LHTMLStyleElement.h"
#include "LHTMLLinkElement.h"
#include "LHTMLImageElement.h"
#include "LHTMLTableElement.h"
#include "LHTMLFormElement.h"
#include "LHTMLSelectElement.h"
#include "LHTMLAnchorElement.h"
#include "LHTMLParagraphElement.h"
#include "LHTMLObjectElement.h"
#include "LHTMLParamElement.h"

HRESULT CLDOMDocumentImplImpl::createHTMLElement(BSTR localName, ILDOMElement **ppElement)
{
	CComPtr<ILDOMElement> newElement;

	if (!wcscmp(localName, L"frameset"))
	{
		CComObject<CLHTMLFrameSetElement>* pElement;
		CComObject<CLHTMLFrameSetElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"frame"))
	{
		CComObject<CLHTMLFrameElement>* pElement;
		CComObject<CLHTMLFrameElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"iframe"))
	{
		CComObject<CLHTMLIFrameElement>* pElement;
		CComObject<CLHTMLIFrameElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"body"))
	{
		CComObject<CLHTMLBodyElement>* pElement;
		CComObject<CLHTMLBodyElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"link"))
	{
		CComObject<CLHTMLLinkElement>* pElement;
		CComObject<CLHTMLLinkElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"style"))
	{
		CComObject<CLHTMLStyleElement>* pElement;
		CComObject<CLHTMLStyleElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"img"))
	{
		CComObject<CLHTMLImageElement>* pElement;
		CComObject<CLHTMLImageElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"table"))
	{
		CComObject<CLHTMLTableElement>* pElement;
		CComObject<CLHTMLTableElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	// Form
	else if (!wcscmp(localName, L"form"))
	{
		CComObject<CLHTMLFormElement>* pElement;
		CComObject<CLHTMLFormElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"select"))
	{
		CComObject<CLHTMLSelectElement>* pElement;
		CComObject<CLHTMLSelectElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"p"))
	{
		CComObject<CLHTMLParagraphElement>* pElement;
		CComObject<CLHTMLParagraphElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"a"))
	{
		CComObject<CLHTMLAnchorElement>* pElement;
		CComObject<CLHTMLAnchorElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"object"))
	{
		CComObject<CLHTMLObjectElement>* pElement;
		CComObject<CLHTMLObjectElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"param"))
	{
		CComObject<CLHTMLParamElement>* pElement;
		CComObject<CLHTMLParamElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	// Generic/Unknown HTML element
	else
	{
		CComObject<CLHTMLElement>* pElement;
		CComObject<CLHTMLElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}

/*
		if (errorHandler)
		{
			CUString str;
			str.Format("Unknown tag \"%S\"", (BSTR)localName);

			CComQIPtr<IDOMLocator> locator;
			m_documentContainer->getCurrentLocation(&locator);
			errorHandler->warn(locator, NULL, _bstr_t(str));
		}

*/
	}

	*ppElement = newElement;
	if (*ppElement) (*ppElement)->AddRef();

	return S_OK;
}

#endif