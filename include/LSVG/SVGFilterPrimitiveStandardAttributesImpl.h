#ifndef Web_SVGFilterPrimitiveStandardAttributesImplImpl_h
#define Web_SVGFilterPrimitiveStandardAttributesImplImpl_h

namespace System
{
namespace Web
{

#if 0
class SVGFilterPrimitiveStandardAttributesImplImpl
{
public:
	CTOR SVGFilterPrimitiveStandardAttributesImplImpl()
	{
		m_x = NULL;
		m_y = NULL;
		m_width = NULL;
		m_height = NULL;
	}

	virtual SVGAnimatedLength* get_x()
	{
		return m_x;
	}

	virtual SVGAnimatedLength* get_y()
	{
		return m_y;
	}

	virtual SVGAnimatedLength* get_width()
	{
		return m_width;
	}

	virtual SVGAnimatedLength* get_height()
	{
		return m_height;
	}

	virtual SVGAnimatedString* get_result()
	{
		return m_result;
	}

public:

	Attr* m_xAttr;
	Attr* m_yAttr;
	Attr* m_widthAttr;
	Attr* m_heightAttr;
	Attr* m_resultAttr;

	SVGAnimatedLength* m_x;
	SVGAnimatedLength* m_y;
	SVGAnimatedLength* m_width;
	SVGAnimatedLength* m_height;
	SVGAnimatedString* m_result;
};
#endif

/*
interface ISVGFilterPrimitveStandardAttributes
{
	virtual ISVGAnimatedLength* get_x() = 0;
	virtual ISVGAnimatedLength* get_y() = 0;
	virtual ISVGAnimatedLength* get_width() = 0;
	virtual ISVGAnimatedLength* get_height() = 0;
	virtual ISVGAnimatedString* get_result() = 0;
};
*/

template <class T> class SVGFilterPrimitiveStandardAttributesImpl : 
	public SVGStylableImpl<T>,
	public ISVGFilterPrimitiveStandardAttributes,
//	public SVGFilterPrimitiveStandardAttributesImplImpl,
	protected AnimatedAttributeT<SVGAnimatedLength, 0>,
	protected AnimatedAttributeT<SVGAnimatedLength, 1>,
	protected AnimatedAttributeT<SVGAnimatedLength, 2>,
	protected AnimatedAttributeT<SVGAnimatedLength, 3>,
	protected AnimatedAttributeT<SVGAnimatedString, 4>
{
public:
	CTOR SVGFilterPrimitiveStandardAttributesImpl() :
		AnimatedAttributeT<SVGAnimatedLength, 0>(static_cast<T*>(this), NULL, WSTR("x")),
		AnimatedAttributeT<SVGAnimatedLength, 1>(static_cast<T*>(this), NULL, WSTR("y")),
		AnimatedAttributeT<SVGAnimatedLength, 2>(static_cast<T*>(this), NULL, WSTR("width")),
		AnimatedAttributeT<SVGAnimatedLength, 3>(static_cast<T*>(this), NULL, WSTR("height")),
		AnimatedAttributeT<SVGAnimatedString, 4>(static_cast<T*>(this), NULL, WSTR("result"))
	{
		/*
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));

		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_result, NULL, WSTR("result")));
		*/
	}

	AnimatedAttributeT<SVGAnimatedLength, 0>& x_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedLength, 0>*>(this);
	}
	AnimatedAttributeT<SVGAnimatedLength, 1>& y_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedLength, 1>*>(this);
	}
	AnimatedAttributeT<SVGAnimatedLength, 2>& width_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedLength, 2>*>(this);
	}
	AnimatedAttributeT<SVGAnimatedLength, 3>& height_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedLength, 3>*>(this);
	}
	AnimatedAttributeT<SVGAnimatedString, 4>& result_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedString, 4>*>(this);
	}

	virtual ISVGAnimatedLength* get_x()
	{
		return x_attr();
	}

	virtual ISVGAnimatedLength* get_y()
	{
		return y_attr();
	}

	virtual ISVGAnimatedLength* get_width()
	{
		return width_attr();
	}

	virtual ISVGAnimatedLength* get_height()
	{
		return height_attr();
	}

	virtual ISVGAnimatedString* get_result()
	{
		return result_attr();
	}

	virtual Attr* get_xAttr()
	{
		return x_attr();
	}
	virtual Attr* get_yAttr()
	{
		return y_attr();
	}

	virtual Attr* get_widthAttr()
	{
		return width_attr();
	}
	virtual Attr* get_heightAttr()
	{
		return height_attr();
	}
	virtual Attr* get_resultAttr()
	{
		return result_attr();
	}

	virtual ISVGAnimatedString* get_className()
	{
		return SVGStylableImpl<T>::get_className();
	}

	virtual Web::CSSValue* getPresentationAttribute(StringIn name)
	{
		return SVGStylableImpl<T>::getPresentationAttribute(name);
	}

	virtual ICSSStyleDeclaration* get_style()
	{
		return SVGStylableImpl<T>::get_style();
	}

};

}	// Web
}	// System

#endif // Web_SVGFilterPrimitiveStandardAttributesImplImpl_h
