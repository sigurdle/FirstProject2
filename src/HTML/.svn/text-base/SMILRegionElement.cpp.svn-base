#include "stdafx.h"
#include "HTML2.h"

#include "SMILRegionElement.h"

namespace System
{
namespace Web
{

SMILRegionElement::SMILRegionElement(NamedNodeMap* attributes) : SMILElement(new PElementBase(this), attributes)
{
	m_backgroundColor = NULL;
	m_left = NULL;
	m_top = NULL;
	m_right = NULL;
	m_bottom = NULL;
	m_width = NULL;
	m_height = NULL;
	m_fit = NULL;
	m_showBackground = NULL;

#if 0
	AddXMLAttribute(NewXMLAttr(&m_backgroundColor, NULL, WSTR("backgroundColor")));
	AddXMLAttribute(NewXMLAttr(&m_left, NULL, WSTR("left")));
	AddXMLAttribute(NewXMLAttr(&m_top, NULL, WSTR("top")));
	AddXMLAttribute(NewXMLAttr(&m_right, NULL, WSTR("right")));
	AddXMLAttribute(NewXMLAttr(&m_bottom, NULL, WSTR("bottom")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));
	AddXMLAttribute(NewXMLAttr(&m_fit, NULL, WSTR("fit"), WSTR("hidden")));
	AddXMLAttribute(NewXMLAttr(&m_showBackground, NULL, WSTR("showBackground"), WSTR("always")));
#endif
	SetAllValues(this);	// ???
}

// A region is activated when a media starts playing within it

void SMILRegionElement::Deactivate(double atTime, SMILMediaElement* mediaElement)
{
	for (uint i = 0; i < m_mediaElements.GetSize(); i++)
	{
		if (m_mediaElements[i] == mediaElement)
		{
			m_mediaElements.RemoveAt(i);
			return;
		}
	}

	ASSERT(0);
}

void SMILRegionElement::Activate(double atTime, SMILMediaElement* mediaElement)
{
	if (mediaElement)
	{
#ifdef _DEBUG
		for (uint i = 0; i < m_mediaElements.GetSize(); i++)
		{
			if (m_mediaElements[i] == mediaElement)
			{
				ASSERT(0);
			}
		}
#endif

		m_mediaElements.Add(mediaElement);
	}

	// Activate parent also
	SMILRegionElement* parentRegion = dynamic_cast<SMILRegionElement*>(m_parentNode);
	if (parentRegion)
	{
		parentRegion->Activate(atTime, NULL);
	}
}

/*
STDMETHODIMP SMILRegionElement::get_width(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP SMILRegionElement::put_width(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP SMILRegionElement::get_height(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP SMILRegionElement::put_height(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
*/

}	// Web
}
