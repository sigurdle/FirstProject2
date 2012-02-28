#include "stdafx.h"
#include "HTML2.h"
#include "HTMLTableElement.h"

namespace System
{
namespace Web
{

HTMLTableElement::HTMLTableElement(NamedNodeMap* attributes) : HTMLElement(new PHTMLElement(this), attributes)
{
	m_cellSpacingAttr = NULL;
	m_cellPaddingAttr = NULL;
	m_borderAttr = NULL;

	m_pcellspacing = NULL;

	ASSERT(0);
//	AddXMLAttribute(NewXMLAttr(&m_pcellspacing, NULL, WSTR("cellspacing")));

	SetAllValues(this);	// ???
}

HTMLTableElement::~HTMLTableElement()
{
}

long HTMLTableElement::get_border()
{
	VERIFY(0);

	return 0;
}

void HTMLTableElement::set_border(long newVal)
{
	VERIFY(0);
}

long HTMLTableElement::get_cellPadding()
{
	/*
	sysstring bstr = getAttribute(L"cellpadding");
	_variant_t var(bstr.c_str(), false));
	*pVal = var.Detach();
	*/
	VERIFY(0);

	return 0;
}

void HTMLTableElement::set_cellPadding(long newVal)
{
	//setAttribute(L"cellpadding", _bstr_t(newVal));
}

long HTMLTableElement::get_cellSpacing()
{
	VERIFY(0);
	return 0;
}

void HTMLTableElement::set_cellSpacing(long newVal)
{
	VERIFY(0);
}

}	// Web
}
