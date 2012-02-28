#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

//#include "XMLAttr.h"
//#include "LDOMElementImpl.h"

namespace System
{
namespace Web
{

void CATXMLAttr::OnBaseValChanged()
{
	// TODO, check reentrance here ??
	Element* element = m_animationTarget;

	SetAttribute(element);	// Update the ILDOMAttr value
#if 0
	m_animationTarget->DoAnimation(/*0,*/0);	// TODO
#endif
}

// Set element attribute from baseVal
void CATXMLAttr::SetAttribute(Element* element)
{
	if (m_reentrance == 0)
	{
		m_reentrance++;

		String baseVal_str = GetBaseVal()->getStringValue();

	//	if (m_namespaceURI)
		{
			element->setAttributeNS(m_namespaceURI, m_attributeName, baseVal_str);
		}
		/*
		else
		{
			element->setAttribute(m_attributeName, baseVal_str);
		}
		*/

		m_specified = true;	// Am I sure about this ?

		m_reentrance--;
	}
}

// Set values of baseVal/animVal from attribute string
void CATXMLAttr::SetValues(Element* element)
{
	if (m_reentrance == 0)
	{
		m_reentrance++;

	//	if (m_namespaceURI->Length())
		String str = element->getAttributeNS(m_namespaceURI, m_attributeName);
	//	else
	//		bstr = element->getAttribute(m_attributeName);

		if (str == nullptr)
		{
			m_specified = false;
			str = m_defaultValue;

		//	if (bstr == NULL)	bstr = SysAllocString(OLESTR(""));	// ??
		}
		else
		{
			m_specified = true;
		}

		CValueType* baseVal = GetBaseVal();
		ASSERT(baseVal);
		if (baseVal == NULL)
		{
			baseVal = GetBaseVal();
		}
		baseVal->setStringValue(str);

		if (GetAnimVal()) GetAnimVal()->setStringValue(str);

	//	SysFreeString(bstr);

		m_reentrance--;
	}
}

}	// Web
}
