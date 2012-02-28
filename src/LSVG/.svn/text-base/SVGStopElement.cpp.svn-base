#include "stdafx.h"
#include "LSVG2.h"
#include "SVGStopElement.h"

namespace System
{
namespace Web
{

double ParseNumberOrPercentageValue(StringIn str)
{
//	System::StringW* str = bstr;//stripspaces(bstr);
	if (str.GetLength() > 0)
	{
		ASSERT(0);
#if 0
		if ((str->c_str())[str->Length()-1] == L'%')
			return getfnumber(str->c_str())/100.0;
		else
			return getfnumber(str->c_str());
#endif
	}

	return 0;
}

/*
void offsetBaseValChanged(Object* obj)
{
	SVGStopElement* e = static_cast<SVGStopElement*>(obj);

	e->m_offsetAttr->m_valueIsValid = false;
}
*/

SVGStopElement::SVGStopElement(NamedNodeMap* attributes) : SVGElement(new PSVGStopElement(this), attributes)
{
	ASSERT(0);
	/*
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_offsetAttr), NULL, WSTR("offset"));

	m_offset = new SVGAnimatedNumber;

	m_offset->m_baseVal = ParseNumberOrPercentageValue(m_offsetAttr->get_value());
*/
//	m_offset->m_arg0 = this;
//	m_offset->m_baseValChanged = offsetBaseValChanged;

	//AddXMLAttribute(NewXMLAttr(&m_offset, NULL, WSTR("offset")));

	//SetAllValues(this);	// ???
}

Attr* SVGStopElement::get_offsetAttr()
{
	return NULL;
	//return m_offsetAttr;
}

ISVGAnimatedNumber* SVGStopElement::get_offset()
{
	return NULL;
	//return m_offset;
}

}	// Web
}	// System
