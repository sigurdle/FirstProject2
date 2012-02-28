#include "stdafx.h"
#include "HTML2.h"
#include "SMILTransitionElement.h"

namespace System
{
namespace Web
{

double ParseClockValue(StringIn s);

SMILTransitionElement::SMILTransitionElement(NamedNodeMap* attributes) : SMILElement(new PElementBase(this), attributes)
{
	m_horzRepeat = 1;
	m_vertRepeat = 1;
	m_borderWidth = 0;

	/*
	AddXMLAttribute(NewNXMLAttr(&m_horzRepeat, NULL, WSTR("horzRepeat"), WSTR("1")));
	AddXMLAttribute(NewNXMLAttr(&m_vertRepeat, NULL, WSTR("vertRepeat"), WSTR("1")));
	AddXMLAttribute(NewNXMLAttr(&m_borderWidth, NULL, WSTR("borderWidth"), WSTR("0")));
	AddXMLAttribute(NewNXMLAttr(&m_direction, NULL, WSTR("direction"), WSTR("forward")));

	SetAllValues(this);	// ???
	*/
}

double SMILTransitionElement::get_dur()
{
// TODO
	String s = getAttribute(WSTR("dur"));
	if (s == NULL)
		s = WSTR("1");

	return ParseClockValue(s);
}

TransitionDirection SMILTransitionElement::get_direction()
{
	return m_direction;
}

int SMILTransitionElement::get_horzRepeat()
{
	return m_horzRepeat;
}

int SMILTransitionElement::get_vertRepeat()
{
	return m_vertRepeat;
}

int SMILTransitionElement::get_borderWidth()
{
	return m_borderWidth;
}

}	// Web
}
