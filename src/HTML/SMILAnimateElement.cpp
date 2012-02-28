#include "stdafx.h"
#include "HTML2.h"

#include "SMILAnimateElement.h"

namespace System
{
namespace Web
{

SMILAnimateElement::SMILAnimateElement(NamedNodeMap* attributes) : SMILAnimationElement(new PElementBase(this), attributes)
{
	/*
	AddXMLAttribute(NewNXMLAttr(&m_animateImpl->m_calcMode, NULL, WSTR("calcMode"), WSTR("linear")));

	SetAllValues(this);	// ???
	*/
}

}	// w3c
}
