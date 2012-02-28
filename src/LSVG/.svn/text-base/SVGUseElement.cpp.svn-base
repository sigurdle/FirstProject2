#include "stdafx.h"
#include "LSVG2.h"
#include "SVGUseElement.h"
#include "SVGElementInstance.h"
#include "PSVGUseElement.h"

namespace System
{
namespace Web
{

SVGUseElement::SVGUseElement(NamedNodeMap* attributes) : SVGTransformableElement(new PSVGUseElement(this), attributes)
{
	m_instanceRoot = NULL;
	m_animatedInstanceRoot = NULL;

	m_x = NULL;
	m_y = NULL;
	m_width = NULL;
	m_height = NULL;

	/*
	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));

	SetAllValues(this);	// ???
	*/
}

SVGUseElement::~SVGUseElement()
{
	if (m_instanceRoot)
	{
//		m_instanceRoot->Release();
		m_instanceRoot = NULL;
	}

	if (m_animatedInstanceRoot)
	{
//		m_animatedInstanceRoot->Release();
		m_animatedInstanceRoot = NULL;
	}
}

SVGElementInstance* SVGUseElement::GetInstanceRoot()
{
	ASSERT(0);
#if 0
	if (m_instanceRoot == NULL)
	{
		sysstring href = m_href->m_animated->m_baseVal->m_value;
		if (href.Length() && ((BSTR)href)[0] == L'#')
		{
			BSTR id = &((BSTR)href)[1];

			Element* element;
			m_ownerDocument->getElementById(id, &element);

			CComQIPtr<ILSVGElement> svgElement = element;
			if (svgElement)
			{
				CComObject<SVGElementInstance>::CreateInstance(&m_instanceRoot);
				m_instanceRoot->AddRef();

				m_instanceRoot->BuildTree(this, svgElement);
			}
		}
	}
#endif
	return m_instanceRoot;
}

SVGElementInstance* SVGUseElement::GetAnimatedInstanceRoot()
{
	return NULL;
}

SVGAnimatedLength* SVGUseElement::get_x()
{
	return m_x;
}

SVGAnimatedLength* SVGUseElement::get_y()
{
	return m_y;
}

SVGAnimatedLength* SVGUseElement::get_width()
{
	return m_width;
}

SVGAnimatedLength* SVGUseElement::get_height()
{
	return m_height;
}

SVGElementInstance* SVGUseElement::get_instanceRoot()
{
	SVGElementInstance* pInstance = GetInstanceRoot();
	return pInstance;
}

SVGElementInstance* SVGUseElement::get_animatedInstanceRoot()
{
// TODO, not nessecerily the same
	SVGElementInstance* pInstance = GetInstanceRoot();
	return  pInstance;
}

}	// w3c
}
