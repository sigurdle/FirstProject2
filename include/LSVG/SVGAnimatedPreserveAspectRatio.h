#ifndef w3c_SVGAnimatedPreserveAspectRatio_h
#define w3c_SVGAnimatedPreserveAspectRatio_h

#include "SVGPreserveAspectRatio.h"

namespace System
{
namespace Web
{

class SVGPreserveAspectRatioValueHandler : public IValueHandler
{
public:
	virtual Object* Create() const;
	virtual void ParseString(Object* value, StringIn str) const;
	virtual void InterpolateValue(Object* dest, Object* a, Object* b, double t);

	static SVGPreserveAspectRatioValueHandler s_SVGPreserveAspectRatioValueHandler;

	static IValueHandler* GetValueHandler()
	{
		return &s_SVGPreserveAspectRatioValueHandler;
	}
};

class SVGEXT SVGAnimatedPreserveAspectRatio :
	public Object,
	public ISVGAnimatedPreserveAspectRatio
{
public:
	CTOR SVGAnimatedPreserveAspectRatio();

	typedef SVGPreserveAspectRatio t_baseType;
	typedef SVGPreserveAspectRatioValueHandler t_valueHandler;

	ISVGPreserveAspectRatio* get_baseVal()
	{
		return m_baseVal;
	}

	ISVGPreserveAspectRatio* get_animVal()
	{
		return m_animVal;
	}

	void SetAnimVal(SVGPreserveAspectRatio* value)
	{
		m_animVal = value;
	}

	void SetBaseValAsString(StringIn str)
	{
		m_baseVal->SetAsString(str);
	}

	SVGPreserveAspectRatio* m_baseVal;
	SVGPreserveAspectRatio* m_animVal;
	IAnimatedOwner<SVGAnimatedPreserveAspectRatio>* m_owner;
};

}	// w3c
}

#endif // w3c_SVGAnimatedPreserveAspectRatio_h
