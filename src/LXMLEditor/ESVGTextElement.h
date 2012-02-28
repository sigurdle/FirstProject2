#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{
class CESVGTextElement :
	public CESVGElementImpl
{
public:
	CTOR CESVGTextElement()
	{
	}


	ErrorCode Move(ISVGView* view, double dx, double dy);
};

}	// LXmlEdit
}
