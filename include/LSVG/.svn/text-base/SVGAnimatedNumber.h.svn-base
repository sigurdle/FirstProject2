#ifndef __SVGANIMATEDNUMBER_H_
#define __SVGANIMATEDNUMBER_H_

//#include "SVGAnimatedNumberT.h"

namespace System
{
namespace Web
{

SVGEXT String GetAsString(double v);

inline Object* GetAsObject(double v)
{
	ASSERT(0);
	return NULL;
}

class SVGNumberValueHandler
{
public:
	static IValueHandler* GetValueHandler()
	{
		return NULL;
	}
};

class SVGAnimatedNumber : public Object, public ISVGAnimatedNumber
{
public:
	CTOR SVGAnimatedNumber()
	{
	}

	typedef double t_baseType;
	typedef SVGNumberValueHandler t_valueHandler;

	double get_baseVal() const
	{
		return m_baseVal;
	}

	void set_baseVal(double newVal)
	{
		m_baseVal = newVal;

		if (m_owner)
		{
			m_owner->BaseValChanged();
		}
	}

	double get_animVal() const
	{
		return m_animVal;
	}

	void SetBaseValAsString(StringIn value)
	{
		bool ok;
		m_baseVal = value.ToDouble(&ok);
	}

	void SetAnimVal(double* val)
	{
		m_animVal = *val;
	}

	double m_baseVal;
	double m_animVal;

	IAnimatedOwner<SVGAnimatedNumber>* m_owner;
};

}	// w3c
}

#endif // __SVGANIMATEDNUMBER_H_
