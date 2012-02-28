#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGImageElement :
	public CESVGElementImpl
{
public:
	CTOR CESVGImageElement()
	{
	}


	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability()
	{
		return 1;
	}
};

}	// LXmlEdit
}
