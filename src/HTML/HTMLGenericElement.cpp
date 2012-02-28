#include "stdafx.h"
#include "HTML2.h"
#include "HTMLGenericElement.h"

#include "PHTMLElement.h"

namespace System
{
namespace Web
{

HTMLGenericElement::HTMLGenericElement(StringIn qualifiedName) : HTMLElement(new PHTMLElement(this))
{
	m_nodeName = qualifiedName;
}

HTMLGenericElement::HTMLGenericElement(StringIn qualifiedName, NamedNodeMap* attributes) : HTMLElement(new PHTMLElement(this), attributes)
{
	m_nodeName = qualifiedName;
}

String HTMLGenericElement::get_timeContainer()
{
	String str = getAttribute(WSTR("timeContainer"));
	if (str == NULL)
		return WSTR("none");
	return str;
}

void HTMLGenericElement::set_timeContainer(StringIn newVal)
{
	setAttribute(WSTR("timeContainer"), newVal);
}

}	// Web
}
