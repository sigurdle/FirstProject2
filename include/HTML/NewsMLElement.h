#ifndef __NEWSMLELEMENT_H_
#define __NEWSMLELEMENT_H_

//#include "resource.h"       // main symbols

#include "NewsMLElementImpl.h"
//#include "LElementEditASImpl.h"

namespace System
{
namespace Web
{

class HTMLEXT GenericNewsMLElement : 
	public NewsMLElement
//	public CLElementEditASImpl<CLNewsMLElement>

//	public ILElementEditVAL	// ILNodeEditVAL
{
public:

	CTOR GenericNewsMLElement() : NewsMLElement(new PElementBase(this))
	{
	}
};

}
}

#endif //__NEWSMLELEMENT_H_
