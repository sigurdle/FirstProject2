#ifndef Web_SVGAnimatedTransformList_h
#define Web_SVGAnimatedTransformList_h

namespace System
{
namespace Web
{

class SVGTransformValueHandler : public IValueHandler
{
public:

	virtual Object* Create() const;
	virtual void ParseString(Object* value, StringIn str) const;
	virtual void InterpolateValue(Object* _dest, Object* _a, Object* _b, double t);

	static SVGTransformValueHandler s_transformValueHandler;

	static IValueHandler* GetValueHandler()
	{
		return &s_transformValueHandler;
	}
};

class SVGEXT SVGAnimatedTransformList : public Object
{
public:
	CTOR SVGAnimatedTransformList();

	typedef SVGTransformList t_baseType;
	typedef SVGTransformValueHandler t_valueHandler;

	SVGTransformList* get_animVal();
	SVGTransformList* get_baseVal();

	void SetAnimVal(SVGTransformList* val);

	void SetBaseValAsString(StringIn str)
	{
		m_baseVal->setStringValue(str);
	}

public:

	SVGTransformList* m_baseVal;
	SVGTransformList* m_animVal;

	IAnimatedOwner<SVGAnimatedTransformList>* m_owner;

//	Object* m_arg0;
//	void (*m_baseValChanged)(Object* arg0);
};

}	// Web
}

#endif // Web_SVGAnimatedTransformList_h
