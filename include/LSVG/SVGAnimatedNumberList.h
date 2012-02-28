#ifndef __SVGANIMATEDNUMBERLIST_H__
#define __SVGANIMATEDNUMBERLIST_H__

namespace System
{
namespace Web
{

class SVGNumberListValueHandler
{
public:
	static IValueHandler* GetValueHandler()
	{
		return NULL;
	}
};

class SVGEXT SVGNumberListPtr : public Object
{
public:

	CTOR SVGNumberListPtr() : m_p(NULL)
	{
	}

	CTOR SVGNumberListPtr(SVGNumberList* p) : m_p(p)
	{
	}

	friend String GetAsString(SVGNumberListPtr* p)
	{
		return p->m_p->ToString();
	}

	SVGNumberList* m_p;
};

class SVGEXT SVGAnimatedNumberList : public Object, public ISVGAnimatedNumberList
{
public:
	CTOR SVGAnimatedNumberList();

	ISVGNumberList* get_animVal();
	ISVGNumberList* get_baseVal();

	void SetAnimVal(SVGNumberList* val)
	{
		ASSERT(m_animVal);
		m_animVal->m_p = val;
	}
	void SetBaseValAsString(StringIn val);

	typedef SVGNumberList t_baseType;
	typedef SVGNumberListValueHandler t_valueHandler;

	SVGNumberListPtr* m_baseVal;
	SVGNumberListPtr* m_animVal;

	IAnimatedOwner<SVGAnimatedNumberList>* m_owner;
};

}	// Web
}

#endif // __SVGANIMATEDNUMBERLIST_H__
