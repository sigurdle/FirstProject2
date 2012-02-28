#include "stdafx.h"
#include "HTML2.h"
#include "HTMLBodyElement.h"

namespace System
{
namespace Web
{

HTMLBodyElement::HTMLBodyElement(NamedNodeMap* attributes) : HTMLElement(new PElementBase(this), attributes)
{
	SetAllValues(this);
}

}	// w3c
}
