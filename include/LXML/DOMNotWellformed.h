#ifndef __LDOMNOTWELLFORMED_H_
#define __LDOMNOTWELLFORMED_H_

//#include "resource.h"       // main symbols

//#include "DOMCharacterData.h"

namespace System
{
namespace Web
{

class WEBEXT NotWellformed : 
	public CharacterData,
	protected CNotifySendImpl<NotWellformed>
{
public:
	CTOR NotWellformed() : CharacterData(NULL)
	{
	}

	Node* cloneNode(bool deep) const
	{
		ASSERT(0);
		return NULL;
	}

	NodeType get_nodeType() const
	{
		return NODE_NOT_WELLFORMED;
	}

	String get_nodeName() const
	{
		return WSTR("#not-wellformed");
	}
};

}	// w3c
}

#endif //__LDOMNOTWELLFORMED_H_
