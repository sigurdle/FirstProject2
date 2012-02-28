// LXUISheetElement.cpp : Implementation of CLXUISheetElement
#include "stdafx.h"

#if 0

#include "LXUI.h"
#include "LHTML2.h"
#include "LXUISheetElement.h"

//////////////////////////////////////////////////////////////////////
// CLXUISheetElement

STDMETHODIMP CLXUISheetElement::createPage(/*[out,retval]*/ ILXUIPage* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CLXUIPage>* pPage;
	CComObject<CLXUIPage>::CreateInstance(&pPage);
	if (pPage)
	{
		pPage->AddRef();

		m_ownerDocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"caption", &pPage->m_captionElement);
		m_ownerDocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"content", &pPage->m_contentElement);

		*pVal = pPage;
	}

	return S_OK;
}

STDMETHODIMP CLXUISheetElement::insertPage(/*[in]*/ long index, /*[in]*/ ILXUIPage* page)
{
	CLXUIPage* pPage = static_cast<CLXUIPage*>(page);

	CComPtr<ILDOMElement> element;
	m_ownerDocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", &element);

	element->appendChild(pPage->m_captionElement, NULL);
	element->appendChild(pPage->m_contentElement, NULL);

	appendChild(element, NULL);

	return S_OK;
}

STDMETHODIMP CLXUISheetElement::removePage(/*[in]*/ long index, /*[out,retval]*/ ILXUIPage* *pVal)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CLXUISheetElement::setActivePage(/*[in]*/ VARIANT vpage)
{
	if (vpage.vt == VT_NULL || vpage.vt == VT_EMPTY)
	{
		return removeAttribute(L"selectedIndex");
	}
	else if (vpage.vt == VT_UNKNOWN || vpage.vt == VT_DISPATCH)
	{
		CComQIPtr<ILXUIPageElement> page = vpage.punkVal;
		if (page == NULL)
			return E_INVALIDARG;

		for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
		{
			if (m_childNodes->m_items[i] == page)
			{
				WCHAR buf[64];
				swprintf(buf, L"%d", i);
				return setAttribute(L"selectedIndex", buf);
			}
		}
	}

	return E_INVALIDARG;
}

#endif