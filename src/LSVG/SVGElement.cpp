#include "stdafx.h"
#include "LSVG2.h"
#include "SVGElement.h"

namespace System
{
namespace Web
{

SVGElement::SVGElement(PElementBase* pPElement) :
	Element(pPElement),
	m_presentationAttributes(new CSSStyleDeclaration),
	AttributeT<SVGElement, CSSStyleDeclaration, 0>(NULL, WSTR("style")),
	PresentationAttributeT<SVGElement, CSSValue, 0>(NULL, WSTR("filter")),
	PresentationAttributeT<SVGElement, SVGPaint, 1>(NULL, WSTR("fill")),
	PresentationAttributeT<SVGElement, SVGPaint, 2>(NULL, WSTR("stroke")),
	PresentationAttributeT<SVGElement, CSSValue, 3>(NULL, WSTR("stroke-width")),
	PresentationAttributeT<SVGElement, CSSValue, 4>(NULL, WSTR("font-family")),
	PresentationAttributeT<SVGElement, CSSValue, 5>(NULL, WSTR("font-size")),
	PresentationAttributeT<SVGElement, CSSValue, 6>(NULL, WSTR("text-anchor"))
{
}

SVGElement::SVGElement(PElementBase* pPElement, NamedNodeMap* attributes) :
	Element(pPElement, attributes),
	AttributeT<SVGElement, CSSStyleDeclaration, 0>(NULL, WSTR("style")),
	PresentationAttributeT<SVGElement, CSSValue, 0>(NULL, WSTR("filter")),
	PresentationAttributeT<SVGElement, SVGPaint, 1>(NULL, WSTR("fill")),
	PresentationAttributeT<SVGElement, SVGPaint, 2>(NULL, WSTR("stroke")),
	PresentationAttributeT<SVGElement, CSSValue, 3>(NULL, WSTR("stroke-width")),
	PresentationAttributeT<SVGElement, CSSValue, 4>(NULL, WSTR("font-family")),
	PresentationAttributeT<SVGElement, CSSValue, 5>(NULL, WSTR("font-size")),
	PresentationAttributeT<SVGElement, CSSValue, 6>(NULL, WSTR("text-anchor"))
{
	AddAttributeContentEventHandler(WSTR("mousedown"), WSTR("onmousedown"), false);
	AddAttributeContentEventHandler(WSTR("mouseup"), WSTR("onmouseup"), false);
	AddAttributeContentEventHandler(WSTR("mousemove"), WSTR("onmousemove"), false);
	AddAttributeContentEventHandler(WSTR("mouseover"), WSTR("onmouseover"), false);
	AddAttributeContentEventHandler(WSTR("mouseout"), WSTR("onmouseout"), false);
	AddAttributeContentEventHandler(WSTR("click"), WSTR("onclick"), false);
}

SVGElement::~SVGElement()
{
	delete m_presentationAttributes;
}

String GetAsString(CSSStyleDeclaration* cssDecl)
{
	return cssDecl->get_cssText();
}

void SetAsString(CSSStyleDeclaration* cssDecl, StringIn str)
{
	ASSERT(cssDecl);
	cssDecl->set_cssText(str);
}

SVGSVGElement* SVGElement::get_ownerSVGElement()
{
	return m_ownerSVGElement;
//	ASSERT(0);
//	return NULL;
#if 0
	CComQIPtr<ILDOMElement> parent;
	thisNode->get_parentNode((ILDOMNode**)&parent);

	while (parent != NULL)
	{
		CComQIPtr<ILSVGSVGElement> svgsvgElement = parent;

		if (svgsvgElement != NULL)
		{
			*pVal = svgsvgElement;
			(*pVal)->AddRef();
			return S_OK;
		}

		CComQIPtr<ILDOMNode> parentNode;
		parent->get_parentNode(&parentNode);
		parent = parentNode;
	}

	*pVal = NULL;

	return S_OK;
#endif
}

SVGElement* SVGElement::get_viewportElement()
{
	ASSERT(0);
	return NULL;
#if 0
	CComPtr<ILDOMNode> parent;
	thisNode->get_parentNode(&parent);

	while (parent != NULL)
	{
		CComQIPtr<ILSVGElement> svgelement = parent;
		if (svgelement)
		{
		// TODO
			CComQIPtr<ILSVGSVGElement> svgsvgElement = svgelement;
			if (svgsvgElement)
			{
				*pVal = svgelement;
				(*pVal)->AddRef();
				return S_OK;
			}

		//	ASSERT(0);
#if 0
			CComQIPtr<ISVGFitToViewBox> viewbox = svgelement;

			if (viewbox != NULL)
			{
				*pVal = svgelement;
				(*pVal)->AddRef();
				return S_OK;
			}
#endif
		}

		CComPtr<ILDOMNode> parentNode;
		parent->get_parentNode(&parentNode);
		parent = parentNode;
	}

	*pVal = NULL;
	return S_OK;
#endif
}

void SVGElement::set_attributes(NamedNodeMap* newVal)
{
	Element::set_attributes(newVal);

	for (uint i = 0; i < m_attributes->m_items.size(); i++)
	{
		Attr* attr = dynamic_cast<Attr*>(m_attributes->m_items[i]);

		String nodeName = attr->get_nodeName();
		ASSERT(nodeName);

	//	if (nodeName)	// hm.. prefix xmlns seems to not have nodeName, that's wrong
		{
			int propertyIndex = GetCSSPropertyIndex(nodeName);

			if (propertyIndex >= 0 && CSSProperties::csspropertyList[propertyIndex]->m_cssType != NULL)
			{
				String value = attr->get_value();

				m_presentationAttributes->setProperty(nodeName, value, NULL);
			}
		}
	}
}

void SVGElement::OnAttrValueChanged(StringIn /*nodeName*/, Attr* attr)
{
	String nodeName = attr->get_nodeName();

// Handle svg presentation attributes
	int propertyIndex = GetCSSPropertyIndex(nodeName);

	if (propertyIndex >= 0 && CSSProperties::csspropertyList[propertyIndex]->m_cssType != 0)
	{
		String value = attr->get_value();

		m_presentationAttributes->setProperty(nodeName, value, NULL);

	//	Node* thisNode = static_cast<T*>(this);

		;//ATLASSERT(0);
#if 0	// TODO, had this
		for (int i = 0; i < m_pNodes.GetSize(); i++)
		{
			((CPElementBase*)m_pNodes[i])->GetCSSPropertiesAndChildren();

			// ????
#if 0	// I had this
			if (m_pNodes[i]->m_pView)
			{
				m_pNodes[i]->m_pView->CalcDims((CPElement*)m_pNodes[i]);
			}
#endif
		}
#endif
	}

	Element::OnAttrValueChanged(nodeName, attr);
}

SVGLocatableElement::SVGLocatableElement(PElementBase* pPElement) : SVGElement(pPElement)
{
}

SVGLocatableElement::SVGLocatableElement(PElementBase* pPElement, NamedNodeMap* attributes) : SVGElement(pPElement, attributes)
{
}

ISVGRect* SVGLocatableElement::getBBox()
{
	ASSERT(0);
	return NULL;//SVGLocatableImplImpl::getBBox(static_cast<T*>(this), pVal);
}

SVGElement* SVGLocatableElement::get_farthestViewportElement()
{
	ASSERT(0);
	return NULL;
}

SVGElement* SVGLocatableElement::get_nearestViewportElement()
{
	ASSERT(0);
	return 0;
	//return ((ILSVGElement*)static_cast<T*>(this))->get_viewportElement(pVal);
}

SVGPoint* SVGLocatableElement::convertClientXY(/*[in]*/ int clientXArg, /*[in]*/ int clientYArg)
{
	VERIFY(0);
	return NULL;
}

//AttrCallbacksImpl(SVGTransformableElement, transform)

Object* SVGTransformValueHandler::Create() const
{
	return new SVGTransformMutable;
}

void SVGTransformValueHandler::ParseString(Object* _value, StringIn str) const
{
	SVGTransformMutable* value = static_cast<SVGTransformMutable*>(_value);

	ASSERT(0);
	//value->setStringValue(str);
}

void SVGTransformValueHandler::InterpolateValue(Object* _dest, Object* _a, Object* _b, double t)
{
	ASSERT(0);
}

SVGTransformValueHandler SVGTransformValueHandler::s_transformValueHandler;

/*
attr_vtable SVGTransformableElement::s_transformCallbacks =
{
	(GetBaseValString_t)&SVGTransformableElement::transformGetBaseValString,
	(SetBaseValString_t)&SVGTransformableElement::transformSetBaseValString,
	(GetBaseValObject_t)&SVGTransformableElement::transformGetBaseValObject,
	(SetAnimValObject_t)&SVGTransformableElement::transformSetAnimValObject,
	SVGTransformValueHandler::GetSVGTransformValueHandler
};
*/

ImmutableString<WCHAR> transform_str(L"transform");

SVGTransformableElement::SVGTransformableElement(PElementBase* pPElement) :
	SVGLocatableElement(pPElement),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedTransformList>(this, NULL, &transform_str)
{
}

SVGTransformableElement::SVGTransformableElement(PElementBase* pPElement, NamedNodeMap* attributes) :
	SVGLocatableElement(pPElement, attributes),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedTransformList>(this, NULL, &transform_str)
{
}

/*
void transformBaseValChanged(Object* obj)
{
	SVGTransformableElement* e = static_cast<SVGTransformableElement*>(obj);
	e->m_transformAttr->m_valueIsValid = false;
	e->GetPElement()->InvalidateBounds();
	// TODO AttrModifiedEvent
}

StringW* SVGTransformableElement::transformGetBaseValString()
{
	return m_transform->m_baseVal->getStringValue();
}

void SVGTransformableElement::transformSetBaseValString()
{
	m_transform->m_baseVal->setStringValue(m_transformAttr->get_value());
	GetPElement()->InvalidateBounds();
	// TODO AttrModifiedEvent
}

Object* SVGTransformableElement::transformGetBaseValObject()
{
	return m_transform;
}

void SVGTransformableElement::transformSetAnimValObject(Object* value)
{
	ASSERT(0);
	//m_transform->m_baseVal->setStringValue(m_transformAttr->get_value());
	GetPElement()->InvalidateBounds();
	// TODO AttrModifiedEvent
}
*/

}	// Web
}
