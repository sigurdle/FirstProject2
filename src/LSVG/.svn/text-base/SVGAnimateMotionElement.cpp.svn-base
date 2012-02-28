#include "stdafx.h"
#include "LSVG2.h"

#include "SVGAnimateMotionElement.h"

namespace System
{
namespace Web
{

class CLSVGCoordinateType : public CAttributeType
{
public:
	virtual CValueType* NewVal()
	{
		return new CValueTypeWrapper<CreateInstanceT<CLSVGCoordinate> >;
	}
};

// Note: default value for calcMode on animateMotion is paced

SVGAnimateMotionElement::SVGAnimateMotionElement(NamedNodeMap* attributes) :
	SVGAnimationElement(new PSVGElement(this), attributes, CALCMODE_PACED)
{
	m_path = NULL;
	m_rotateType = NULL;
	m_rotateAngle = NULL;


//	AddXMLAttribute(NewNXMLAttr(&m_animateImpl->m_calcMode, NULL, WSTR("calcMode"), WSTR("paced")));

	/*
	AddXMLAttribute(NewNXMLAttr(&m_rotateType, NULL, WSTR("rotate"), WSTR("0")));
	AddXMLAttribute(NewNXMLAttr(&m_rotateAngle, NULL, WSTR("rotate"), WSTR("0")));

	NewNXMLAttr(&m_path, NULL, WSTR("path"));
	AddXMLAttribute(m_path);
	*/

	m_path->m_value->m_value->m_seglist->m_pListener = this;
	m_path->m_value->m_value->m_normalizedseglist->m_pListener = this;

	SetAllValues(this);	// ???
}

SVGAnimateMotionElement::~SVGAnimateMotionElement()
{
	m_path->m_value->m_value->m_seglist->m_pListener = NULL;
	m_path->m_value->m_value->m_normalizedseglist->m_pListener = NULL;
}

// virtual
void SVGAnimateMotionElement::SetValuesFromAttributes()
{
	ASSERT(0);
#if 0
	m_pAttributeType = new CLSVGCoordinateType;

	BSTR fromstr;
	BSTR tostr;
	BSTR bystr;
	BSTR valuesstr;
	BSTR keySplinesstr;

	getAttribute(L"from", &fromstr);
	getAttribute(L"to", &tostr);
	getAttribute(L"by", &bystr);
	getAttribute(L"values", &valuesstr);
	getAttribute(L"keySplines", &keySplinesstr);

	m_bInError = FALSE;

	if (valuesstr)
	{
		CArray<sysstring,sysstring> values;
		GetSemicolonSepStringArray(valuesstr, values);

		sysstring keyTimesstr = getAttribute(L"keyTimes");
		if (keyTimesstr != NULL)
		{
			GetSemicolonOrSpaceSepNumberArray(keyTimesstr, m_keyTimes);
		}
		else
		{
		// if keyTimes is ommited, create an evenly spaced array

			for (int i = 0; i < values.GetSize(); i++)
			{
				m_keyTimes.Add((double)i / (values.GetSize()-1));
			}
		}

	// TODO check that there are the same number of values in the two arrays

		for (int i = 0; i < values.GetSize(); i++)
		{
			CValueType* value = m_pAttributeType->NewVal();
			*value = values[i];
			m_valuesValues.Add(value);

			value->m_pListener = this;
		}
	}

	if (keySplinesstr)
	{
		ParseKeySplines(keySplinesstr, m_keySplines);
	}

	if (fromstr)
	{
		m_fromValue = m_pAttributeType->NewVal();
		*m_fromValue = _bstr_t(fromstr);

		m_fromValue->m_pListener = this;
	}

	if (tostr)
	{
		m_toValue = m_pAttributeType->NewVal();
		*m_toValue = _bstr_t(tostr);

		m_toValue->m_pListener = this;
	}

	if (bystr)
	{
		m_byValue = m_pAttributeType->NewVal();
		*m_byValue = _bstr_t(bystr);

		m_byValue->m_pListener = this;
	}

	m_currentValue = m_pAttributeType->NewVal();

	SysFreeString(fromstr);
	SysFreeString(tostr);
	SysFreeString(bystr);
	SysFreeString(valuesstr);
	SysFreeString(keySplinesstr);
#endif
}

// virtual
void SVGAnimateMotionElement::DoAnimationForElement(Element* target)
{
	ASSERT(0);
#if 0
	BOOL bAdditive = m_additive->m_value->m_value == ADDITIVE_SUM;

	double t = m_tsf/m_simpleDur;//(newLocalTime)/dur;	// TODO

	CComQIPtr<ILSVGTransformable> transformable = target;
	if (transformable)
	{
		gmMatrix3 matrix = gmMatrix3::identity();

		ILDOMElement* mpathElement = GetElementByTagNameNS(this, L"http://www.w3.org/2000/svg", L"mpath", FALSE);
		if (mpathElement)
		{
			CComBSTR href;
			mpathElement->getAttributeNS(L"http://www.w3.org/1999/xlink", L"href", &href);

			if (href.Length())
			{
				if (((BSTR)href)[0] == L'#')
				{
					BSTR id = &((BSTR)href)[1];

					CComPtr<ILDOMElement> refElement;
					m_ownerDocument->getElementById(id, &refElement);

					CComQIPtr<ILSVGPathElement> pathElement = refElement;
					if (pathElement)
					{
						CComQIPtr<ILSVGAnimatedPathData> pathData = pathElement;

						CComPtr<ILSVGPathSegList> seglist;
						pathData->get_animatedNormalizedPathSegList(&seglist);

						double length;
						static_cast<SVGPathSegList*>(seglist.p)->getLength(&length);

						double onlength = 0;
						double xt;
						double yt;
						double angle;
						static_cast<SVGPathSegList*>(seglist.p)->getPointOnLength(t*length, &xt, &yt, &angle);

						if (m_rotateType->m_value->m_value == SVG_ROTATE_ANGLE)
							m_rotateAngle->m_value->m_value->get_value(&angle);
						else if (m_rotateType->m_value->m_value == SVG_ROTATE_AUTO_REVERSE)
							angle += 180;

						matrix = gmMatrix3::rotate(angle) * gmMatrix3::translate(xt, yt);
					}
				}
			}
		}
		else if (m_path->m_specified)
		{
			CComPtr<ILSVGPathSegList> seglist = m_path->m_value->m_value->m_normalizedseglist;

			double length;
			static_cast<SVGPathSegList*>(seglist.p)->getLength(&length);

			double onlength = 0;
			double xt;
			double yt;
			double angle;
			static_cast<SVGPathSegList*>(seglist.p)->getPointOnLength(t*length, &xt, &yt, &angle);

			if (m_rotateType->m_value->m_value == SVG_ROTATE_ANGLE)
				m_rotateAngle->m_value->m_value->get_value(&angle);
			else if (m_rotateType->m_value->m_value == SVG_ROTATE_AUTO_REVERSE)
				angle += 180;

			matrix = gmMatrix3::rotate(angle) * gmMatrix3::translate(xt, yt);
		}
		else
		{
#if 0
			CComBSTR fromstr;
			getAttribute(L"from", &fromstr);
			
			CComBSTR tostr;
			getAttribute(L"to", &tostr);

			if (fromstr.Length() && tostr.Length())
			{
				double from_x, from_y;
				double to_x, to_y;

				{
					CArray<double,double> from;
					GetCommaOrSpaceSepNumberArray(fromstr, from);
					from_x = from[0];
					from_y = from[1];
				}

				{
					CArray<double,double> to;
					GetCommaOrSpaceSepNumberArray(tostr, to);
					to_x = to[0];
					to_y = to[1];
				}

				double x = from_x + (to_x-from_x)*t;
				double y = from_y + (to_y-from_y)*t;

				matrix = gmMatrix3::translate(x, y);//transform->SetTranslate(x, y);
			}
#endif
		}

		ASSERT(0);
#if 0
		for (int i = 0; i < CComQIPtr<CLDOMElementImplImpl>(target)->m_pNodes.GetSize(); i++)
		{
			PSVGElement* pSVGElement = (PSVGElement*)CComQIPtr<CLDOMElementImplImpl>(target)->m_pNodes[i];

			if (bAdditive)
			{
				pSVGElement->m_animateMotionMatrix *= matrix;
			}
			else
			{
				pSVGElement->m_animateMotionMatrix = matrix;
			}
		}
#endif
	}
#endif
}

SVGPathSegList* SVGAnimateMotionElement::get_pathSegList()
{
	return m_path->m_value->m_value->m_seglist;
}

SVGPathSegList* SVGAnimateMotionElement::get_normalizedPathSegList()
{
	return m_path->m_value->m_value->m_normalizedseglist;
}

SVGAnimateMotionRotateType SVGAnimateMotionElement::get_rotateType()
{
	return m_rotateType->m_value->m_value;
}

SVGAngle* SVGAnimateMotionElement::get_rotateAngle()
{
	return m_rotateAngle->m_value->m_value;
}

void SVGAnimateMotionElement::setRotateToAngle(SVGAngle* angle)
{
	ASSERT(angle != NULL);
	if (angle == NULL) THROW(-1);

	String stringValue = angle->get_valueAsString();

	setAttribute(WSTR("rotate"), stringValue);
}

}	// Web
}
