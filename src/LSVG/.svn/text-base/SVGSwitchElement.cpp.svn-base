#include "stdafx.h"
#include "LSVG2.h"

#include "SVGSwitchElement.h"
#include "PSVGSwitchElement.h"

namespace System
{
namespace Web
{

SVGSwitchElement::SVGSwitchElement(NamedNodeMap* attributes) : SVGTransformableElement(new PSVGSwitchElement(this), attributes)
{
	m_selectedElement = NULL;
}

bool MatchesRequiredExtensions(ISVGTests* tests, SVGStringList* stringlist)
{
	unsigned int numberOfItems = stringlist->get_numberOfItems();
	for (unsigned int i = 0; i < numberOfItems; i++)
	{
		String value = stringlist->getItem(i);

		bool bValue = tests->hasExtension(value);
		if (!bValue)
			return false;
	}

	return true;
}

bool MatchesLanguage(ISVGTests* tests, SVGStringList* stringlist)
{
	unsigned int numberOfItems = stringlist->get_numberOfItems();
	if (numberOfItems == 0)
		return true;	// Matches any language

	ASSERT(0);
	String systemLanguage = NULL;// = g_preferences.m_systemLanguage;

	for (unsigned int i = 0; i < numberOfItems; i++)
	{
		String value = stringlist->getItem(i);

		if (value.CompareNoCase(systemLanguage) == 0)
		{
			return true;
		}
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
// SVGSwitchElement

Element* SVGSwitchElement::SelectElement()
{
	ASSERT(0);
#if 0
//	ILDOMElement* selectedElement;

	for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
	{
		CComQIPtr<ILDOMElement> element = m_childNodes->m_items[i];

		CComQIPtr<ILSVGTests> tests = element;
		if (tests)
		{
			ASSERT(element);

			/*
			CComPtr<ILSVGStringList> requiredFeatures;
			tests->get_requiredFeatures(&requiredEFeatures);
			*/

			CComPtr<ILSVGStringList> systemLanguage;
			tests->get_systemLanguage(&systemLanguage);
			if (!MatchesLanguage(tests, systemLanguage))
				continue;

			CComPtr<ILSVGStringList> requiredExtensions;
			tests->get_requiredExtensions(&requiredExtensions);
			if (!MatchesRequiredExtensions(tests, requiredExtensions))
				continue;

			long systemBitrate;
			tests->get_systemBitrate(&systemBitrate);
			if (g_preferences.m_systemBitrate < systemBitrate)
				continue;

			// Found an element that passed all tests, stop searching
			return element;
		}
	}
#endif
	// Went through all the children without finding any that passed all tests
	return NULL;
}

void SVGSwitchElement::UpdateSelectedElement()
{
	ASSERT(0);
#if 0
	ILDOMElement* selectedElement = SelectElement();

	if (m_selectedElement != selectedElement)
	{
		// Invalidate display of previously selected element
		if (m_selectedElement)
		{
			for (int i = 0; i < CComQIPtr<CLDOMNodeImplImpl>(m_selectedElement)->m_pNodes.GetSize(); i++)
			{
				CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(m_selectedElement)->m_pNodes[i];

				gmMatrix3 ctm = ((PSVGElement*)pPElement)->GetScreenCTM();

				RectD xrect;
				GetTransformRectBoundingBox(ctm, ((PSVGElement*)pPElement)->m_expandedBBox, &xrect);

				CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));

				pPElement->m_pWindow->InvalidateRect(&rect);
			}
		}

		m_selectedElement = selectedElement;

		// Invalidate display of newly selected element
		if (m_selectedElement)
		{
			for (int i = 0; i < CComQIPtr<CLDOMNodeImplImpl>(m_selectedElement)->m_pNodes.GetSize(); i++)
			{
				CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(m_selectedElement)->m_pNodes[i];

				gmMatrix3 ctm = ((PSVGElement*)pPElement)->GetScreenCTM();

				RectD xrect;
				GetTransformRectBoundingBox(ctm, ((PSVGElement*)pPElement)->m_expandedBBox, &xrect);

				CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));

				pPElement->m_pWindow->InvalidateRect(&rect);
			}
		}
	}
#endif
}

Element* SVGSwitchElement::getSelectedElement()
{
	return m_selectedElement;
}

}	// Web
}
