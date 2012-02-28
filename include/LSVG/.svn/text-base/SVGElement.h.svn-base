#ifndef Web_SVGElement_h
#define Web_SVGElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGElement :
	public Element,
	public IElementCSSInlineStyle,
	protected AttributeT<SVGElement, CSSStyleDeclaration, 0>,
	private PresentationAttributeT<SVGElement, CSSValue, 0>,
	private PresentationAttributeT<SVGElement, SVGPaint, 1>,
	private PresentationAttributeT<SVGElement, SVGPaint, 2>,
	private PresentationAttributeT<SVGElement, CSSValue, 3>,
	private PresentationAttributeT<SVGElement, CSSValue, 4>,
	private PresentationAttributeT<SVGElement, CSSValue, 5>,
	private PresentationAttributeT<SVGElement, CSSValue, 6>
{
public:
	CTOR SVGElement(PElementBase* pPElement);
	CTOR SVGElement(PElementBase* pPElement, NamedNodeMap* attributes);
	~SVGElement();

	CSSStyleDeclaration* get_style() override
	{
		return style_attr();
	//	return static_cast<const T*>(this)->m_styleDeclaration;
	}

	AttributeT<SVGElement, CSSStyleDeclaration, 0>& style_attr()
	{
		return *static_cast<AttributeT<SVGElement, CSSStyleDeclaration, 0>*>(this);
	}

	PresentationAttributeT<SVGElement, CSSValue, 0>& filter_attr()
	{
		return *static_cast<PresentationAttributeT<SVGElement, CSSValue, 0>*>(this);
	}

#if 0
	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLDOMElementImpl<T, IBase>::FinalConstruct();
		if (FAILED(hr)) return hr;

		hr = CComObject<CSSStyleDeclaration>::CreateInstance(&m_presentationAttributes);
		if (FAILED(hr)) return hr;
		m_presentationAttributes->AddRef();
	// TODO listen to property changes ?

		return 0;
	}

	void FinalRelease()
	{
		if (m_presentationAttributes)
		{
			m_presentationAttributes->m_pListener = NULL;
			m_presentationAttributes->Release();
			m_presentationAttributes = NULL;
		}

		CLDOMElementImpl<T, IBase>::FinalRelease();
	}
#endif

	virtual SVGElement* get_viewportElement();
	virtual SVGSVGElement* get_ownerSVGElement();

	virtual void OnAttrValueChanged(StringIn /*nodeName*/, Attr* attr);

	virtual void set_attributes(NamedNodeMap* newVal);

public:

	SVGSVGElement* m_ownerSVGElement;
	CSSStyleDeclaration* m_presentationAttributes;
};

class SVGEXT SVGLocatableElement : public SVGElement
{
public:
	CTOR SVGLocatableElement(PElementBase* pPElement);
	CTOR SVGLocatableElement(PElementBase* pPElement, NamedNodeMap* attributes);

	virtual ISVGRect* getBBox();
	virtual SVGElement* get_farthestViewportElement();
	virtual SVGElement* get_nearestViewportElement();
	virtual SVGPoint* convertClientXY(/*[in]*/ int clientXArg, /*[in]*/ int clientYArg);
};

class SVGEXT SVGTransformableElement : public SVGLocatableElement,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedTransformList>

{
public:
	CTOR SVGTransformableElement(PElementBase* pPElement);
	CTOR SVGTransformableElement(PElementBase* pPElement, NamedNodeMap* attributes);

	AnimatedAttributeAffectsBoundsT<SVGAnimatedTransformList>& transform_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedTransformList>*>(this);
	}

	SVGAnimatedTransformList* get_transform()
	{
		return transform_attr();
	}

	Attr* get_transformAttr()
	{
		return transform_attr();
	}

	PSVGElement* GetPElement() const
	{
		return (PSVGElement*)m_pNode;
	}

protected:

	friend class PSVGTransformableElement;
};

class SVGEXT SVGShapeElement : public SVGTransformableElement
{
public:
	CTOR SVGShapeElement(PSVGShapeElement* pPElement);
	CTOR SVGShapeElement(PSVGShapeElement* pPElement, NamedNodeMap* attributes);

	virtual Gui::Geometry* get_animatedGeometry()
	{
		ASSERT(0);
		return NULL;
	}
};

class AnimatedPoints
{
public:

	CTOR AnimatedPoints()
	{
		m_baseVal = new SVGPointListMutable(new SVGPointListData());
		m_animVal = new SVGPointList(m_baseVal->m_p);
	}

	typedef SVGPointList t_baseType;

	SVGPointListMutable* m_baseVal;
	SVGPointList* m_animVal;

	void SetBaseValAsString(StringIn value);
	void SetAnimVal(SVGPointList* value);

	AnimatedPoints* operator -> ()
	{
		return this;
	}
};

template<class ContainerClass>
class PolygonalPointsAttributeT : public IAttrOwner, public IAnimatedOwner<AnimatedPoints>
{
public:

	typedef AnimatedPoints AnimatedType;

	CTOR PolygonalPointsAttributeT(StringIn namespaceURI, StringIn localName, StringIn defaultValueAsString = NULL)
	{
		static_cast<ContainerClass*>(this)->UnspecifiedAttr(inner_ptr<Attr*>(static_cast<ContainerClass*>(this), &m_attr), namespaceURI, localName);

		ASSERT(m_attr);
		m_attr->m_owner = this;

	//	m_animated = new AnimatedType;
	//	m_animated->m_owner = this;
		if (m_attr->get_specified())
			m_animated->SetBaseValAsString(m_attr->get_value());
		else
			m_animated->SetBaseValAsString(defaultValueAsString);
	}

	virtual Element* GetElement()
	{
		return static_cast<ContainerClass*>(this);
	}

	/*
	operator AnimatedType* ()
	{
		return m_animated;
	}
	*/

	operator Attr* ()
	{
		return m_attr;
	}

	/*
	AnimatedType* operator->()
	{
		return m_animated;
	}
*/

	virtual String GetBaseValAsString()
	{
		return GetAsString(m_animated->m_baseVal);
	}
	
	virtual Object* GetBaseValAsObject()
	{
		return GetAsObject(m_animated->m_baseVal);
	}
	virtual void SetAnimValAsObject(Object* value)
	{
		ASSERT(0);
		// TODO, have this
#if 0
		typename AnimatedType::t_baseType* length = static_cast<typename AnimatedType::t_baseType*>(value);
		SetAnimVal(length);
#endif
	}

	virtual IValueHandler* GetValueHandler()
	{
		ASSERT(0);
#if 0
#ifndef __LERSTAD__	// TODO
		return AnimatedType::t_valueHandler::GetValueHandler();
#endif
#endif
		return NULL;
	}

	virtual void UpdateBaseValString()
	{
	//	SetStringValue(m_animated->m_baseVal, m_attr->get_value());
		m_animated->SetBaseValAsString(m_attr->get_value());
		// static_cast<ContainerClass*>(this)->OnSetBaseValString(m_animated, value);
	}

	virtual void SetAnimVal(typename AnimatedType::t_baseType* value)
	{
		m_animated->SetAnimVal(value);
		// static_cast<ContainerClass*>(this)->OnSetAnimVal(m_animated, value);
	}

	virtual void BaseValChanged()
	{
		m_attr->m_valueIsValid = false;
		// static_cast<ContainerClass*>(this)->OnBaseValChanged(m_attr);
	}

	Attr* m_attr;
	AnimatedPoints m_animated;
};

class SVGEXT SVGPolygonalShapeElement : public SVGShapeElement,
	public PolygonalPointsAttributeT<SVGPolygonalShapeElement>
{
public:
	CTOR SVGPolygonalShapeElement(PSVGShapeElement* pPElement);
	CTOR SVGPolygonalShapeElement(PSVGShapeElement* pPElement, NamedNodeMap* attributes);

	PolygonalPointsAttributeT<SVGPolygonalShapeElement>& points_attr()
	{
		return *static_cast<PolygonalPointsAttributeT<SVGPolygonalShapeElement>*>(this);
	}

	virtual Gui::Geometry* get_animatedGeometry() override;

	ISVGPointList* get_points()
	{
		return points_attr().m_animated.m_baseVal;
		//return m_points->m_animated->m_baseVal->m_value;
	}

	ISVGPointList* get_animatedPoints()
	{
		return points_attr().m_animated.m_animVal;//m_animatedPoints;
		//return m_points->m_animated->m_animVal->m_value;
	}

	Attr* get_pointsAttr();

protected:

//	SVGPointListMutable* m_points;
//	SVGPointList* m_animatedPoints;
};

class SVGEXT SVGEllipticalShapeElement :
	public SVGShapeElement,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>
{
public:

	CTOR SVGEllipticalShapeElement(PSVGShapeElement* pPElement);
	CTOR SVGEllipticalShapeElement(PSVGShapeElement* pPElement, NamedNodeMap* attributes);

	PSVGShapeElement* GetPElement() const
	{
		return (PSVGShapeElement*)m_pNode;
	}

	XMLANIMATEDATTR(SVGEllipticalShapeElement, SVGAnimatedLength, ISVGAnimatedLength*, cx, 0)
	XMLANIMATEDATTR(SVGEllipticalShapeElement, SVGAnimatedLength, ISVGAnimatedLength*, cy, 1)
};

}	// Web
}	// System

#endif // Web_SVGElement_h
