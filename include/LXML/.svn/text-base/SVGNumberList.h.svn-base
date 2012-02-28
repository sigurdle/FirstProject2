#ifndef __Web_SVGNumberList_h__
#define __Web_SVGNumberList_h__

//#include "resource.h"       // main symbols

#include "SVGNumber.h"

namespace System
{
namespace Web
{

class SVGNumberList;

/*
class SVGNumberListListener
{
public:
	virtual void OnNumberListChange(SVGNumberList* pSegList) = 0;
};
*/

class WEBEXT SVGNumberList : 
	public Object,
	public ISVGNumberList
{
public:
	CTOR SVGNumberList()
	{
	}

	~SVGNumberList();

	virtual String ToString() override;

	unsigned int get_numberOfItems() const;
	void clear();
	ISVGNumber* appendItem(ISVGNumber* newItem);
	ISVGNumber* removeItem(unsigned int index);
	ISVGNumber* replaceItem(ISVGNumber* newItem, unsigned int index);
	ISVGNumber* insertItemBefore(ISVGNumber* newItem, unsigned int index);
	ISVGNumber* getItem(unsigned int index);
	ISVGNumber* initialize(ISVGNumber* newItem);

	void setStringValue(StringIn str);
//	void operator = (const SVGNumberList& value);
//	void operator += (const SVGNumberList& value);
	void InterpolateValue(const SVGNumberList& a, const SVGNumberList& b, double t);
	void RemoveAll();

public:

	vector<SVGNumber*> m_items;
};

}	// Web
}

#endif // __Web_SVGNumberList_h__
