#include "stdafx.h"
#include "HTML2.h"

#include "SMILAnimateMotionElement.h"

//#include "LSMILTransform.h"
//#include "LSMILTransformList.h"
//#include "LSMILAnimatedTransformList.h"
#include "SVGPathSegList.h"

#if 0
int GetCommaOrSpaceSepNumberArray(BSTR str, CArray<double,double>& values);

class CLSMILCoordinateType : public CAttributeType
{
public:
	virtual CValueType* NewVal()
	{
//		CComObject<CXMLAttr2T<CComObjectCreateInstance<CValueTypeWrapper<CComObjectCreateInstance<CLSMILCoordinate> > > > >* p;
//		CComObject<CXMLAttr2T<CComObjectCreateInstance<CValueTypeWrapper<CComObjectCreateInstance<CLSMILCoordinate> > > > >::CreateInstance(&p);

		CValueTypeWrapper<CComObjectCreateInstance<CLSMILCoordinate> >*p;
		CValueTypeWrapper<CComObjectCreateInstance<CLSMILCoordinate> >::CreateInstance(&p);

		p->AddRef();

		return p;
	}
};
#endif

namespace System
{
namespace Web
{

SMILAnimateMotionElement::SMILAnimateMotionElement(NamedNodeMap* attributes) : SMILAnimationElement(new PElementBase(this), attributes)
{
	m_path = NULL;

// Note: default value for calcMode on animateMotion is paced
	/*
	AddXMLAttribute(NewNXMLAttr(&m_animateImpl->m_calcMode, NULL, WSTR("calcMode"), WSTR("paced")));

	NewNXMLAttr(&m_path, NULL, WSTR("path"));
	AddXMLAttribute(m_path);
	*/

	m_path->m_value->m_value->m_seglist->m_pListener = this;
	m_path->m_value->m_value->m_normalizedseglist->m_pListener = this;
}

SMILAnimateMotionElement::~SMILAnimateMotionElement()
{
	m_path->m_value->m_value->m_seglist->m_pListener = NULL;
	m_path->m_value->m_value->m_normalizedseglist->m_pListener = NULL;
}

void SMILAnimateMotionElement::OnPathSegListChange(SVGPathSegList* pSegList)
{
	if (pSegList == m_path->m_value->m_value->m_seglist)
	{
		m_path->OnBaseValChanged();
	}
	else if (pSegList == m_path->m_value->m_value->m_normalizedseglist)
	{
	// Copy the normalized seglist to the the seglist
		m_path->m_value->m_value->m_seglist->RemoveAll();
		m_path->m_value->m_value->m_seglist->AddSegListNoUpdate(m_path->m_value->m_value->m_normalizedseglist);

		m_path->OnBaseValChanged();
	}
}

// virtual
void SMILAnimateMotionElement::SetValuesFromAttributes()
{
#if 0
	m_pAttributeType = new CLSMILCoordinateType;

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
		CArray<_bstr_t,_bstr_t> values;
		GetSemicolonSepStringArray(valuesstr, values);

		CComBSTR keyTimesstr;
		getAttribute(L"keyTimes", &keyTimesstr);
		if ((BSTR)keyTimesstr != NULL)
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
void SMILAnimateMotionElement::DoAnimationForElement(Element* target)
{
#if 0
	BOOL bAdditive = m_additive->m_value->m_value == ADDITIVE_SUM;

	double t = m_tsf/m_simpleDur;//(newLocalTime)/dur;	// TODO

	CComQIPtr<ILSMILTransformable> transformable = target;
	if (transformable)
	{
		gmMatrix3 matrix = gmMatrix3::identity();

		ILDOMElement* mpathElement = FindByTagNameNS(this, L"http://www.w3.org/2000/SMIL", L"mpath", FALSE);
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

					CComQIPtr<ILSMILPathElement> pathElement = refElement;
					if (pathElement)
					{
						CComQIPtr<ILSMILAnimatedPathData> pathData = pathElement;

						CComPtr<ILSMILPathSegList> seglist;
						pathData->get_animatedNormalizedPathSegList(&seglist);

						double length;
						static_cast<CLSMILPathSegList*>(seglist.p)->getLength(&length);

						double onlength = 0;
						double xt;
						double yt;
						double angle;
						static_cast<CLSMILPathSegList*>(seglist.p)->getPointOnLength(t*length, &xt, &yt, &angle);

						if (m_rotateType->m_value->m_value == SMIL_ROTATE_ANGLE)
							m_rotateAngle->m_value->m_value->get_value(&angle);
						else if (m_rotateType->m_value->m_value == SMIL_ROTATE_AUTO_REVERSE)
							angle += 180;

						matrix = gmMatrix3::rotate(angle) * gmMatrix3::translate(xt, yt);
					}
				}
			}
		}
		else if (m_path->m_specified)
		{
			CComPtr<ILSMILPathSegList> seglist = m_path->m_value->m_value->m_normalizedseglist;

			double length;
			static_cast<CLSMILPathSegList*>(seglist.p)->getLength(&length);

			double onlength = 0;
			double xt;
			double yt;
			double angle;
			static_cast<CLSMILPathSegList*>(seglist.p)->getPointOnLength(t*length, &xt, &yt, &angle);

			if (m_rotateType->m_value->m_value == SMIL_ROTATE_ANGLE)
				m_rotateAngle->m_value->m_value->get_value(&angle);
			else if (m_rotateType->m_value->m_value == SMIL_ROTATE_AUTO_REVERSE)
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

		for (int i = 0; i < CComQIPtr<CLDOMElementImplImpl>(target)->m_pNodes.GetSize(); i++)
		{
			CPSMILElementImpl* pSMILElement = (CPSMILElementImpl*)CComQIPtr<CLDOMElementImplImpl>(target)->m_pNodes[i];

			if (bAdditive)
			{
				pSMILElement->m_animateMotionMatrix *= matrix;
			}
			else
			{
				pSMILElement->m_animateMotionMatrix = matrix;
			}
		}
	}
	#endif
}

SVGPathSegList* SMILAnimateMotionElement::get_pathSegList()
{
	return m_path->m_value->m_value->m_seglist;
}

SVGPathSegList* SMILAnimateMotionElement::get_normalizedPathSegList()
{
	return m_path->m_value->m_value->m_normalizedseglist;
}

}	// Web
}
