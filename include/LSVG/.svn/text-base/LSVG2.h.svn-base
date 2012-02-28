#ifdef __LERSTAD__
#import "LXML/LXML.h"
#else
#include "LXML/LXML.h"
#endif

/*
#ifdef __LERSTAD__
#import "HTML/HTML.h"
#else
#include "HTML/HTML.h"
#endif
*/

#ifndef SVGEXT
#define SVGEXT DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace Web
{

class SVGElement;
class SVGLocatableElement;
class SVGTransformableElement;
class SVGSVGElement;
class SVGFilterElement;
class SVGMaskElement;
class SVGUseElement;
class SVGGElement;
class SVGPathElement;
class SVGClipPathElement;
class SVGMarkerElement;
class SVGRectElement;
class SVGCircleElement;
class SVGEllipseElement;
class SVGFontElement;
class SVGColorProfileElement;
class SVGVideoElement;
class SVGLineElement;
class SVGForeignObjectElement;
class SVGImageElement;
class SVGLinearGradientElement;
class SVGRadialGradientElement;
class SVGPatternElement;
class SVGPolylineElement;
class SVGPolygonElement;
class SVGAElement;
class SVGSolidColorElement;
class SVGTextPathElement;
class SVGTextElement;
class SVGGlyphElement;
class SVGAltGlyphElement;
class SVGTSpanElement;
class SVGTRefElement;
class SVGSwitchElement;
class SVGElementInstance;

class SVGFEColorMatrixElement;
class SVGFEComponentTransferElement;
class SVGFEConvolveMatrixElement;
class SVGFEDisplacementMapElement;
class SVGFEImageElement;
class SVGFEMorphologyElement;
class SVGFEOffsetElement;
class SVGFEGaussianBlurElement;
class SVGFETurbulenceElement;
class SVGFEBlendElement;
class SVGFEFloodElement;
class SVGFEMergeElement;
class SVGFEDiffuseLightingElement;
class SVGFESpecularLightingElement;
class SVGFECompositeElement;
class SVGFEPointLightElement;

class SVGGradientElement;
class SVGStopElement;

class PSVGElement;
class PSVGShapeElement;
class PSVGFEElement;
class PSVGSVGElement;
class PSVGFilterElement;
class PSVGMaskElement;
class PSVGUseElement;
class PSVGGElement;
class PSVGClipPathElement;
class PSVGMarkerElement;
class PSVGRectElement;
class PSVGCircleElement;
class PSVGEllipseElement;
class PSVGPolygonElement;
class PSVGPolylineElement;
class PSVGFontElement;
class PSVGGlyphElement;
class PSVGLinearGradientElement;

class PSVGFEGaussianBlurElement;
class PSVGFEMergeElement;
class PSVGFEPointLightElement;

//class CEffect;

class SVGAngle;
class SVGAnimatedLength;
//class SVGAnimatedLengthTest;	// TODO

class SVGAnimatedLengthList;
class SVGTransform;
class SVGTransformList;
class SVGAnimatedTransformList;
class SVGPathSegList;
class CAttributeTransformType;

class CGlyphGroup;

String GetAsString(CSSStyleDeclaration* cssDecl);
void SetAsString(CSSStyleDeclaration* cssDecl, StringIn str);

template<class ContainerClass, class Type, int unique = 0> class AttributeT : public IAttrOwner
{
public:

	typedef AttributeT<ContainerClass, Type, unique> thisClass;

	CTOR AttributeT(StringIn namespaceURI, StringIn localName)
	{
		static_cast<ContainerClass*>(this)->UnspecifiedAttr(inner_ptr<Attr*>(static_cast<ContainerClass*>(this), &m_attr), namespaceURI, localName);

		ASSERT(m_attr);
		m_attr->m_owner = this;

		m_value = new Type;
		SetAsString(m_value, m_attr->get_value());
	}

	virtual Element* GetElement()
	{
		return static_cast<ContainerClass*>(this);
	}

	operator Type* ()
	{
		return m_value;
	}

	operator Attr* ()
	{
		return m_attr;
	}

	Type* operator->()
	{
		return m_value;
	}

	virtual String GetBaseValAsString()
	{
		return GetAsString(m_value);
	}
	
	virtual Object* GetBaseValAsObject()
	{
		return m_value;
	}
	virtual void SetAnimValAsObject(Object* value)
	{
		ASSERT(0);
	//	typename AnimatedType::t_baseType* length = static_cast<typename AnimatedType::t_baseType*>(value);
	//	SetAnimVal(length);
	}

	virtual IValueHandler* GetValueHandler()
	{
		return NULL;
#ifndef __LERSTAD__	// TODO
	//	return AnimatedType::t_valueHandler::GetValueHandler();
#endif
	}

	virtual void UpdateBaseValString()
	{
		SetAsString(m_value, m_attr->get_value());

	//	SetStringValue(m_animated->m_baseVal, m_attr->get_value());
	//	m_animated->SetBaseValAsString(m_attr->get_value());
		// static_cast<ContainerClass*>(this)->OnSetBaseValString(m_animated, value);
	}

	virtual void SetAnimVal(Type* value)
	{
		ASSERT(NULL);
		// ??
	//	m_value = value;
		//m_animated->SetAnimVal(value);
		// static_cast<ContainerClass*>(this)->OnSetAnimVal(m_animated, value);
	}

	virtual void BaseValChanged()
	{
		m_attr->m_valueIsValid = false;
		// static_cast<ContainerClass*>(this)->OnBaseValChanged(m_attr);
	}

	Attr* m_attr;
	Type* m_value;
};

/*
class AnimatedCSSValue
{
public:
	CSSValue* m_baseVal;
	CSSValue* m_animVal;
};
*/

template<class ContainerClass, class AnimatedType, int unique = 0> class PresentationAttributeT : public IAttrOwner//, public IAnimatedOwner<typename AnimatedType::t_baseType*>
{
public:

	typedef PresentationAttributeT<ContainerClass, AnimatedType, unique> thisClass;

	CTOR PresentationAttributeT(StringIn namespaceURI, StringIn localName)
	{
		static_cast<ContainerClass*>(this)->UnspecifiedAttr(inner_ptr<Attr*>(static_cast<ContainerClass*>(this), &m_attr), namespaceURI, localName);

		ASSERT(m_attr);
		m_attr->m_owner = this;

		if (static_cast<ContainerClass*>(this)->m_presentationAttributes == NULL)
		{
			static_cast<ContainerClass*>(this)->m_presentationAttributes = new CSSStyleDeclaration;
		}

		String attrValue = m_attr->get_value();
		if (attrValue)
		{
			static_cast<ContainerClass*>(this)->m_presentationAttributes->setProperty(localName, attrValue, NULL);
		}

	//	m_animated.m_baseVal = new CSSValue;
	//	m_animated.m_baseVal->set_cssText(m_attr->get_value());
	//	m_animated.m_animVal = m_animated.m_baseVal;

	//	m_animated = new AnimatedType;
	//	m_animated->SetBaseValAsString(m_attr->get_value());
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
		return static_cast<ContainerClass*>(this)->m_presentationAttributes->getPropertyValue(m_attr->get_name());
	//	return m_animated.m_baseVal->get_cssText();
	}

	virtual Object* GetBaseValAsObject()
	{
		return static_cast<ContainerClass*>(this)->m_presentationAttributes->getPropertyCSSValue(m_attr->get_name());
	}

	virtual void SetAnimValAsObject(Object* value)
	{
		ASSERT(0);
	//	typename AnimatedType::t_baseType* length = static_cast<typename AnimatedType::t_baseType*>(value);
	//	SetAnimVal(length);
	}

	virtual IValueHandler* GetValueHandler()
	{
		return NULL;
#ifndef __LERSTAD__	// TODO
		//return AnimatedType::t_valueHandler::GetValueHandler();
#endif
	}

	virtual void UpdateBaseValString()
	{
		String attrValue = m_attr->get_value();
		if (attrValue)
		{
			static_cast<ContainerClass*>(this)->m_presentationAttributes->setProperty(m_attr->get_name(), attrValue, NULL);
		}
		else
		{
			static_cast<ContainerClass*>(this)->m_presentationAttributes->removeProperty(m_attr->get_name());
		}

	//	SetStringValue(m_animated->m_baseVal, m_attr->get_value());
//		m_animated.m_baseVal->set_cssText(m_attr->get_value());
		// static_cast<ContainerClass*>(this)->OnSetBaseValString(m_animated, value);
	}

	virtual void SetAnimVal(CSSValue* value)
	{
	//	m_animated->SetAnimVal(value);
		// static_cast<ContainerClass*>(this)->OnSetAnimVal(m_animated, value);
	}

	virtual void BaseValChanged()
	{
		m_attr->m_valueIsValid = false;
		// static_cast<ContainerClass*>(this)->OnBaseValChanged(m_attr);
	}

	Attr* m_attr;
//	AnimatedCSSValue m_animated;
};

interface ISVGLocatable
{
	virtual SVGElement* get_nearestViewportElement() = 0;
	virtual SVGElement* get_farthestViewportElement() = 0;
	virtual ISVGRect* getBBox() = 0;
	virtual SVGMatrix* getCTM() = 0;
	virtual SVGMatrix* getScreenCTM() = 0;
	virtual SVGMatrix* getTransformToElement(SVGElement* element) = 0;
	virtual ISVGPoint* convertClientXY(int clientXArg, int clientYArg) = 0;
	virtual SVGMatrix* getTransformMatrix() = 0;
};

interface ISVGTransformable : public ISVGLocatable
{
	virtual SVGAnimatedTransformList* get_transform() = 0;
};

enum SVGZoomAndPanType
{
	SVG_ZOOMANDPAN_UNKNOWN = 0,
	SVG_ZOOMANDPAN_DISABLE = 1,
	SVG_ZOOMANDPAN_MAGNIFY = 2
};

interface ISVGZoomAndPan
{
	virtual SVGZoomAndPanType get_zoomAndPan() = 0;
	virtual void set_zoomAndPan(SVGZoomAndPanType zoomAndPanType) = 0;	
};

interface ISVGViewSpec : public ISVGZoomAndPan
{
	virtual SVGTransformList* get_transform() = 0;
	virtual SVGElement* get_viewTarget() = 0;
	virtual String get_viewBoxString() = 0;
	virtual String get_preserveAspectRatioString() = 0;
	virtual String get_transformString() = 0;
	virtual String get_viewTargetString() = 0;
};

interface ISVGFilterPrimitiveStandardAttributes : public ISVGStylable
{
	virtual ISVGAnimatedLength* get_x() = 0;
	virtual ISVGAnimatedLength* get_y() = 0;
	virtual ISVGAnimatedLength* get_width() = 0;
	virtual ISVGAnimatedLength* get_height() = 0;
	virtual ISVGAnimatedString* get_result() = 0;

	virtual Attr* get_xAttr() = 0;
	virtual Attr* get_yAttr() = 0;
	virtual Attr* get_widthAttr() = 0;
	virtual Attr* get_heightAttr() = 0;
	virtual Attr* get_resultAttr() = 0;
};

interface ISVGTransformList : public ISVGList
{
	virtual SVGTransform* appendItem(SVGTransform* newItem) = 0;
	virtual SVGTransform* removeItem(unsigned int index) = 0;
	virtual SVGTransform* replaceItem(SVGTransform* newItem, unsigned int index) = 0;
	virtual SVGTransform* insertItemBefore(SVGTransform* newItem, unsigned int index) = 0;
	virtual SVGTransform* getItem(unsigned int index) const = 0;
	virtual SVGTransform* initialize(SVGTransform* newItem) = 0;
	virtual SVGTransform* createSVGTransformFromMatrix(const SVGMatrix* matrix) = 0;
	virtual SVGTransform* consolidate() = 0;
};

interface ISVGAnimatedTransformList
{
	virtual SVGTransformList* get_baseVal() = 0;
	virtual SVGTransformList* get_animVal() = 0;
};

enum SVGCompositeOperatorType
{
	SVG_FECOMPOSITE_OPERATOR_UNKNOWN = 0,
	SVG_FECOMPOSITE_OPERATOR_OVER = 1,
	SVG_FECOMPOSITE_OPERATOR_IN = 2,
	SVG_FECOMPOSITE_OPERATOR_OUT = 3,
	SVG_FECOMPOSITE_OPERATOR_ATOP = 4,
	SVG_FECOMPOSITE_OPERATOR_XOR = 5,
	SVG_FECOMPOSITE_OPERATOR_ARITHMETIC = 6
};

enum SVGTurbulenceType
{
	SVG_TURBULENCE_TYPE_UNKNOWN = 0,
	SVG_TURBULENCE_TYPE_FRACTALNOISE = 1,
	SVG_TURBULENCE_TYPE_TURBULENCE = 2
};

enum SVGStitchOptions
{
	SVG_STITCHTYPE_UNKNOWN = 0,
	SVG_STITCHTYPE_STITCH = 1,
	SVG_STITCHTYPE_NOSTITCH = 2
};

enum SVGEdgeModeValue
{
	SVG_EDGEMODE_UNKNOWN = 0,
	SVG_EDGEMODE_DUPLICATE = 1,
	SVG_EDGEMODE_WRAP = 2,
	SVG_EDGEMODE_NONE = 3
};

enum SVGBlendModeType
{
	SVG_FEBLEND_MODE_UNKNOWN = 0,
	SVG_FEBLEND_MODE_NORMAL = 1,
	SVG_FEBLEND_MODE_MULTIPLY = 2,
	SVG_FEBLEND_MODE_SCREEN = 3,
	SVG_FEBLEND_MODE_DARKEN = 4,
	SVG_FEBLEND_MODE_LIGHTEN = 5
};

enum SVGChannelSelector
{
	SVG_CHANNEL_UNKNOWN = 0,
	SVG_CHANNEL_R = 1,
	SVG_CHANNEL_G = 2,
	SVG_CHANNEL_B = 3,
	SVG_CHANNEL_A = 4
};

enum SVGMorphologyOperator
{
	SVG_MORPHOLOGY_OPERATOR_UNKNOWN = 0,
	SVG_MORPHOLOGY_OPERATOR_ERODE = 1,
	SVG_MORPHOLOGY_OPERATOR_DILATE = 2
};

enum SVGColorMatrixType
{
	SVG_FECOLORMATRIX_TYPE_UNKNOWN = 0,
	SVG_FECOLORMATRIX_TYPE_MATRIX = 1,
	SVG_FECOLORMATRIX_TYPE_SATURATE = 2,
	SVG_FECOLORMATRIX_TYPE_HUEROTATE = 3,
	SVG_FECOLORMATRIX_TYPE_LUMINANCETOALPHA = 4
};

enum SVGComponentTransferType
{
	SVG_FECOMPONENTTRANSFER_TYPE_UNKNOWN = 0,
	SVG_FECOMPONENTTRANSFER_TYPE_IDENTITY = 1,
	SVG_FECOMPONENTTRANSFER_TYPE_TABLE = 2,
	SVG_FECOMPONENTTRANSFER_TYPE_DISCRETE = 3,
	SVG_FECOMPONENTTRANSFER_TYPE_LINEAR = 4,
	SVG_FECOMPONENTTRANSFER_TYPE_GAMMA = 5
};

enum SVGLengthAdjustType
{
	LENGTHADJUST_UNKNOWN	= 0,
	LENGTHADJUST_SPACING	= 1,
	LENGTHADJUST_SPACINGANDGLYPHS	= 2
};

enum SVGTextPathMethodType
{
	TEXTPATH_METHODTYPE_UNKNOWN = 0,
	TEXTPATH_METHODTYPE_ALIGN = 1,
	TEXTPATH_METHODTYPE_STRETCH = 2
};

enum SVGTextPathSpacingType
{
	TEXTPATH_SPACINGTYPE_UNKNOWN = 0,
	TEXTPATH_SPACINGTYPE_AUTO = 1,
	TEXTPATH_SPACINGTYPE_EXACT = 2
};

}	// Web
}	// System

#include "SVGImplementation.h"
#include "SVGPreserveAspectRatio.h"
#include "SVGAnimatedPreserveAspectRatio.h"
#include "SVGLengthList.h"
#include "SVGAnimatedLength.h"
#include "SVGAnimatedPathDataImpl.h"
#include "SVGTransformableImpl.h"
#include "SVGLangSpaceImpl.h"
#include "SVGExternalResourcesRequiredImpl.h"
#include "SVGRenderElementImpl.h"

#include "SVGURIReferenceImpl.h"
#include "SVGFilterPrimitiveStandardAttributesImpl.h"
#include "SVGAnimatedNumber.h"
#include "SVGTransformList.h"
#include "SVGAnimatedTransformList.h"
#include "SVGTransform.h"
#include "SVGAnimatedInteger.h"
#include "SVGAnimatedBoolean.h"
#include "SVGAngle.h"
#include "SVGAnimatedAngle.h"
#include "SVGAnimatedLength.h"
#include "SVGAnimatedPointsImpl.h"

#include "SVGElement.h"
#include "SVGDocument.h"
#include "SVGTextPositioningElementImpl.h"

#include "SVGAnimationElement.h"

#include "PSVGFEElement.h"
//#include "PSVGPolygonElement.h"
//#include "PSVGCircleElement.h"
//#include "PSVGEllipseElement.h"
#include "PSVGRectElement.h"
#include "PSVGLineElement.h"
#include "PSVGPathElement.h"
#include "PSVGUseElement.h"

#include "SVGSVGElement.h"
#include "SVGGElement.h"
#include "SVGFontElement.h"
#include "SVGFilterElement.h"
#include "SVGFEMergeElement.h"
#include "SVGFEMergeNodeElement.h"
#include "SVGFEPointLightElement.h"

#include "PSVGSVGElement.h"
#include "PSVGGElement.h"
#include "PSVGFilterElement.h"
#include "PSVGFontElement.h"
#include "PSVGMaskElement.h"
#include "PSVGLinearGradientElement.h"
#include "PSVGPatternElement.h"
#include "PSVGGlyphElement.h"
#include "PSVGFESpecularLightingElement.h"
#include "PSVGFEPointLightElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGVisual : public Gui::FrameworkElement
{
public:

	CTOR SVGVisual();

	void Load(StringIn url);
	void SetDocument(Web::SVGDocument* svgdocument);

	virtual void Render(Gui::ManagedRenderContext renderContext) override;
	virtual void OnLeftMouseButtonDown(Gui::MouseButtonEventArgs* args) override;

	virtual void DoLayout() override;
	virtual void DoLayoutSize(gm::SizeF size) override;

	static Gui::DependencyClass* get_Class();
	static Gui::DependencyClass* pClass;

	virtual SVGDocument* get_Document()
	{
		return m_document;
	}

	CHTMLWindow* m_window;
	SVGDocument* m_document;
	SVGSVGElement* m_svgelement;
	PSVGSVGElement* m_psvgelement;
};

}	// Web
}	// System
