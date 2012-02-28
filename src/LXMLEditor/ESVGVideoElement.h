#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGVideoElement : public CESVGElementImpl
{
public:
	CTOR CESVGVideoElement()
	{
	}

	ErrorCode SetShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height);

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability()
	{
		return 1;
	}
//	virtual void Scale(double cx, double cy, double sx, double sy);
};

}	// LXmlEdit
}
