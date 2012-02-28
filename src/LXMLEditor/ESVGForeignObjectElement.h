#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGForeignObjectElement : public CESVGElementImpl
{
public:
	CTOR CESVGForeignObjectElement()
	{
	}

	ErrorCode SetShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height);

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability()
	{
		return 1;
	}
};

}	// LXmlEdit
}
