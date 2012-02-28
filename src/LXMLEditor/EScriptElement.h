#pragma once

#include "EElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CEScriptDocument;

class CEScriptElement :
	public Element
{
public:
	CEScriptElement()
	{
		m_pScriptDocument = NULL;
	}

	CEScriptDocument* m_pScriptDocument;

};

}	// LXmlEdit
}
