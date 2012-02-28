#ifndef __SVGELEMENTINSTANCELIST_H_
#define __SVGELEMENTINSTANCELIST_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class SVGElementInstance;

class SVGEXT SVGElementInstanceList : public System::Object
{
public:
	SVGElementInstanceList()
	{
	}

	unsigned int get_length() const;
	SVGElementInstance* item(unsigned int index);

public:

	vector<SVGElementInstance*> m_items;
};

}	// w3c
}

#endif // __SVGELEMENTINSTANCELIST_H_
