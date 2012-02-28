#ifndef Web_SVGAnimatedRect_h
#define Web_SVGAnimatedRect_h

namespace System
{
namespace Web
{

class SVGRectValueHandler
{
public:

	static IValueHandler* GetValueHandler()
	{
		ASSERT(0);
		return NULL;
	}
};

class SVGAnimatedRect : public Object, public ISVGAnimatedRect
{
public:
	CTOR SVGAnimatedRect();

	typedef SVGRect t_baseType;
	typedef SVGRectValueHandler t_valueHandler;

	ISVGRect* get_baseVal()
	{
		return m_baseVal;
	}

	ISVGRect* get_animVal()
	{
		return m_animVal;
	}

	void SetBaseValAsString(StringIn value);

	void SetAnimVal(SVGRect* rect)
	{
		m_animVal = rect;
	}

public:

	SVGRect* m_baseVal;
	SVGRect* m_animVal;

	IAnimatedOwner<SVGAnimatedRect>* m_owner;
//	Object* m_arg0;
//	void (*m_baseValChanged)(Object* arg0);

//	CATXMLAttr* m_pAttr;
};

}	// w3c
}

#endif // Web_SVGAnimatedRect_h
