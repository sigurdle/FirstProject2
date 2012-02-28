#ifndef Web_SVGAnimatedString_h
#define Web_SVGAnimatedString_h

namespace System
{
namespace Web
{

HTMLEXT String GetAsString(StringIn str);

class HTMLEXT SVGStringValueHandler : public IValueHandler
{
public:
	virtual Object* Create() const;
	virtual void ParseString(Object* value, StringIn str) const;
	virtual void InterpolateValue(Object* dest, Object* a, Object* b, double t);

	static SVGStringValueHandler s_SVGStringValueHandler;

	static IValueHandler* GetValueHandler()
	{
		return &s_SVGStringValueHandler;
	}
};

class HTMLEXT SVGAnimatedString : public Object, public ISVGAnimatedString
{
public:
	CTOR SVGAnimatedString();

//	typedef String t_baseType;
	typedef StringObject t_baseType;
	typedef SVGStringValueHandler t_valueHandler;

	String get_animVal();
	String get_baseVal();
	void set_baseVal(StringIn newVal);

//	friend SVGEXT StringW* GetStringValue(SVGAnimatedString* p);
//	friend SVGEXT void SetStringValue(SVGAnimatedString* p, StringW* str);

	void SetAnimVal(StringIn value)
	{
		m_animVal = value;
	}

	void SetBaseValAsString(StringIn str);

public:

	String m_baseVal;
	String m_animVal;

	IAnimatedOwner<SVGAnimatedString>* m_owner;

//	void (*m_baseValChanged)(Object* arg0);
//	Object* m_arg0;

	/*
	CreateInstanceT<CValueTypeWrapper<CreateInstanceT<CStringValue> > > m_baseVal;
	CreateInstanceT<CValueTypeWrapper<CreateInstanceT<CStringValue> > > m_animVal;

	CATXMLAttr* m_pAttr;
	*/
};

}	// Web
}

#endif // Web_SVGAnimatedString_h
