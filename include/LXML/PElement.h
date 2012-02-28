#ifndef __PELEMENT_H
#define __PELEMENT_H

#include "PElementBase.h"

namespace System
{
namespace Web
{

class WEBEXT PGenericElement : public PElementBase
{
public:
	CTOR PGenericElement(Element* element) : PElementBase(element)
	{
	}
};

}	// Web
}

#endif	// __PELEMENT_H
