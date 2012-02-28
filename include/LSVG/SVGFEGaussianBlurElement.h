#ifndef Web_SVGFEGaussianBlurElement_h
#define Web_SVGFEGaussianBlurElement_h

namespace System
{
namespace Web
{

template</*class ContainerClass,*/ class AnimatedType, int unique = 0> class AnimatedAttribute2T : public IAttrOwner, public IAnimatedOwner<AnimatedType>
{
public:

	typedef AnimatedAttribute2T</*ContainerClass,*/ AnimatedType, unique> thisClass;

	CTOR AnimatedAttribute2T(Element* element, StringIn namespaceURI, StringIn localName, StringIn defaultValueAsString = NULL)
	{
	//	static_cast<ContainerClass*>(this)->UnspecifiedAttr(inner_ptr<Attr*>(static_cast<ContainerClass*>(this), &m_attr), namespaceURI, localName);
		element->UnspecifiedAttr(inner_ptr<Attr*>(element, &m_attr), namespaceURI, localName);

		ASSERT(m_attr);
		m_attr->m_owner = this;

		m_animated[0] = new AnimatedType;
		m_animated[1] = new AnimatedType;

		if (m_attr->get_specified())
			SetBaseValAsString(m_attr->get_value());
		else
			SetBaseValAsString(defaultValueAsString);
	}

	void SetBaseValAsString(StringIn str)
	{
		vector<double> values;
		GetCommaOrSpaceSepNumberArray(str, values);
		if (values.GetSize() > 0)
		{
			double m_values[2];
			if (values.GetSize() == 1)
			{
				m_values[0] = values[0];
				m_values[1] = values[0];
			}
			else
			{
				m_values[0] = values[0];
				m_values[1] = values[1];
			}

			m_animated[0]->m_baseVal = m_values[0];
			m_animated[0]->m_animVal = m_values[0];

			m_animated[1]->m_baseVal = m_values[1];
			m_animated[1]->m_animVal = m_values[1];
		}
	}

	virtual Element* GetElement()
	{
		return m_attr->get_ownerElement();
//		return static_cast<ContainerClass*>(this);
	}

	operator Attr* ()
	{
		return m_attr;
	}

	virtual String GetBaseValAsString()
	{
		ASSERT(0);
		return NULL;
		//return GetAsString(m_animated->m_baseVal);
	}
	
	virtual Object* GetBaseValAsObject()
	{
		ASSERT(0);
		return NULL;
		//return m_animated->m_baseVal;
	}
	virtual void SetAnimValAsObject(Object* value)
	{
		ASSERT(0);
	//	typename AnimatedType::t_baseType* length = static_cast<typename AnimatedType::t_baseType*>(value);
	//	SetAnimVal(length);
	}

	virtual IValueHandler* GetValueHandler()
	{
		ASSERT(0);
		return NULL;
#ifndef __LERSTAD__	// TODO
//		return AnimatedType::t_valueHandler::GetValueHandler();
#endif
	}

	virtual void UpdateBaseValString()
	{
		ASSERT(0);
	//	m_animated->SetBaseValAsString(m_attr->get_value());
	}

	virtual void SetAnimVal(typename AnimatedType::t_baseType* value)
	{
		ASSERT(0);
	//	m_animated->SetAnimVal(value);
	}

	virtual void BaseValChanged()
	{
		m_attr->m_valueIsValid = false;
	}

	Attr* m_attr;
	AnimatedType* m_animated[2];
};

class SVGEXT SVGFEGaussianBlurElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEGaussianBlurElement>,
//	public ElementEditASImpl<SVGFEGaussianBlurElement>,
	public ElementEditVALImpl<SVGFEGaussianBlurElement>,
	public SMILAnimationTargetImpl<SVGFEGaussianBlurElement>,
//	public SVGFEElementImpl<SVGFEGaussianBlurElement>,

//	public IElementEditVAL,	// ILNodeEditVAL

	protected AnimatedAttributeT<SVGAnimatedString, 0>,
	protected AnimatedAttribute2T<SVGAnimatedNumber, 1>
{
public:

	CTOR SVGFEGaussianBlurElement(NamedNodeMap* attributes);

	AnimatedAttributeT<SVGAnimatedString, 0>& in1_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedString, 0>*>(this);
	}

	AnimatedAttribute2T<SVGAnimatedNumber, 1>& stdDeviation_attr()
	{
		return *static_cast<AnimatedAttribute2T<SVGAnimatedNumber, 1>*>(this);
	}

	void setStdDeviation(double stdDeviationX, double stdDeviationY);
	ISVGAnimatedNumber* get_stdDeviationY();
	ISVGAnimatedNumber* get_stdDeviationX();
	ISVGAnimatedString* get_in1();

public:

	inline PSVGFEGaussianBlurElement* GetPElement() const
	{
		return (PSVGFEGaussianBlurElement*)m_pNode;
	}

//	SVGAnimatedNumber* m_stdDeviationX;
//	SVGAnimatedNumber* m_stdDeviationY;
//	Attr* m_stdDeviationAttr;
};

}	// Web
}	// System

#endif // Web_SVGFEGaussianBlurElement_h
