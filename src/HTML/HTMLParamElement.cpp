#include "stdafx.h"
#include "HTML2.h"
#include "HTMLParamElement.h"

namespace System
{
namespace Web
{

	// TODO, not here
HTMLParagraphElement::HTMLParagraphElement(NamedNodeMap* attributes) : HTMLElement(new PElementBase(this), attributes)
{
//	SetAllValues(this);	// ??
}

HTMLParagraphElement::~HTMLParagraphElement()
{
}

///

HTMLParamElement::HTMLParamElement(NamedNodeMap* attributes) : HTMLElement(new PElementBase(this), attributes)
{
//	SetAllValues(this);	// ???
}

HTMLParamElement::~HTMLParamElement()
{
}

String HTMLParamElement::get_name()
{
	return getAttribute(WSTR("name"));
}

void HTMLParamElement::set_name(StringIn newVal)
{
	setAttribute(WSTR("name"), newVal);
}

String HTMLParamElement::get_type()
{
	THROW(-1);
	return NULL;
}

void HTMLParamElement::set_type(StringIn newVal)
{
	THROW(-1);
}

String HTMLParamElement::get_value()
{
	return getAttribute(WSTR("value"));
}

void HTMLParamElement::set_value(StringIn newVal)
{
	setAttribute(WSTR("name"), newVal);
}

String HTMLParamElement::get_valueType()
{
	return getAttribute(WSTR("valuetype"));
}

void HTMLParamElement::set_valueType(StringIn newVal)
{
	setAttribute(WSTR("valuetype"), newVal);
}

}	// Web
}
