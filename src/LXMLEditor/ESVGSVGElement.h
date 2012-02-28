#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGSVGElement :
	public CESVGElementImpl
{
public:
	CTOR CESVGSVGElement()
	{
	}


	ErrorCode SetShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height);

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability(/*[out,retval]*/ long* pVal)
	{
		return 1;
	}
};

}	// LXmlEdit
}
