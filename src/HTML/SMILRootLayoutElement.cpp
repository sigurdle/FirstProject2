#include "stdafx.h"
#include "HTML2.h"

#include "SMILRootLayoutElement.h"

namespace System
{
namespace Web
{

SMILRootLayoutElement::SMILRootLayoutElement(NamedNodeMap* attributes) : SMILElement(new PElementBase(this), attributes)
{
	m_backgroundColor = NULL;
	m_width = NULL;
	m_height = NULL;
	ASSERT(0);
/*
	AddXMLAttribute(NewXMLAttr(&m_backgroundColor, NULL, WSTR("backgroundColor")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));

	SetAllValues(this);	// ???
	*/
}

}
}
