#ifndef Web_SVGAnimatedLength_h
#define Web_SVGAnimatedLength_h

namespace System
{
namespace Web
{

	/*
class SVGEXT SVGAnimatedLength : public System::Object,
	public ISVGAnimatedLength,
	public ISingleObjectListener
{
public:
	CTOR SVGAnimatedLength()
	{
		m_pAttr = NULL;
	}

	CreateInstanceT<CValueTypeWrapper<CreateInstanceT<SVGLengthMutable> > > m_baseVal;
	CreateInstanceT<CValueTypeWrapper<CreateInstanceT<SVGLengthMutable> > > m_animVal;

	CATXMLAttr* m_pAttr;

	virtual void OnChanged(CSingleObject* pSVGLength)
	{
		m_pAttr->OnBaseValChanged();
	}

	ISVGLength* get_animVal();
	ISVGLength* get_baseVal();
};
*/

class SVGEXT SVGAnimatedLength : public Object,
	public ISVGAnimatedLength,
	public ISVGLengthListener
{
public:
	CTOR SVGAnimatedLength();

	typedef SVGLength t_baseType;
	typedef SVGLengthValueHandler t_valueHandler;

	virtual ISVGLength* get_baseVal();
	virtual ISVGLength* get_animVal();

	virtual void OnChanged(SVGLength* pLength);
	virtual bool OnRemoveItem(SVGLength* pLength);

	void SetAnimVal(SVGLength* value)
	{
		m_animVal->m_p = value->m_p;
	}

	void SetBaseValAsString(StringIn str)
	{
		m_baseVal->set_valueAsString(str);
	}

// TODO protected

	IAnimatedOwner<SVGAnimatedLength>* m_owner;
	SVGLengthMutable* m_baseVal;
	SVGLength* m_animVal;
};

}	// Web
}	// System

#endif // Web_SVGAnimatedLength_h
