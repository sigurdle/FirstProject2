#pragma once

#include "EElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CECSSDocument;

class CEStyleElement :
	public Element
{
public:
	CEStyleElement()
	{
		m_pCSSDocument = NULL;
	}

	CECSSDocument* m_pCSSDocument;
};

}	// LXmlEdit
}
