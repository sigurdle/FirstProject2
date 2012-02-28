#include "stdafx.h"
#include "LSVG2.h"

#include "SVGAnimateTransformElement.h"

/*
#include "SVGTransform.h"
#include "SVGTransformList.h"
#include "SVGAnimatedTransformList.h"
*/

namespace System
{
namespace Web
{

void GetTranslateValues(const WCHAR* param_string, double& x, double& y);
void GetScaleValues(const WCHAR* param_string, double& sx, double& sy);
void GetRotateValues(const WCHAR* param_string, double &deg, double& cx, double& cy);
void GetSkewValues(const WCHAR* param_string, double &deg);
void GetMatrixValues(const WCHAR* param_string, SVGMatrix* matrix);

class CAttributeTransformType : public CAttributeType
{
public:
	virtual CValueType* NewVal()
	{
		CValueTypeWrapper<CreateInstanceT<SVGTransform> >* p = new CValueTypeWrapper<CreateInstanceT<SVGTransform> >;
		p->m_value->m_type = m_type;

		return p;
	}

	SVGTransformType m_type;
};

SVGAnimateTransformElement::SVGAnimateTransformElement(NamedNodeMap* attributes) :
	SVGAnimationElement(new PSVGElement(this), attributes, CALCMODE_LINEAR)
{
//	AddXMLAttribute(NewNXMLAttr(&m_animateImpl->m_calcMode, NULL, WSTR("calcMode"), WSTR("linear")));

//	SetAllValues(this);	// ???
}

//virtual
void SVGAnimateTransformElement::SetValuesFromAttributes()
{
	ASSERT(0);
#if 0
	if (m_reentrance == 0)
	{
		m_reentrance++;

		if (m_pAttributeType)
		{
		//	delete m_pAttributeType;
			m_pAttributeType = NULL;
		}

		for (int i = 0; i < m_valuesValues.GetSize(); i++)
		{
			m_valuesValues[i]->m_pListener = NULL;
			m_valuesValues[i]->Release();
		}
		m_keyTimes.RemoveAll();
		m_valuesValues.RemoveAll();

		if (m_fromValue)
		{
			m_fromValue->m_pListener = NULL;
			m_fromValue->Release();
			m_fromValue = NULL;
		}

		if (m_toValue)
		{
			m_toValue->m_pListener = NULL;
			m_toValue->Release();
			m_toValue = NULL;
		}

		if (m_byValue)
		{
			m_byValue->m_pListener = NULL;
			m_byValue->Release();
			m_byValue = NULL;
		}

	///////////////
		ILDOMElement* thisNode = static_cast<T*>(this);//->GetUnknown();

		CComPtr<ILDOMElement> target;
		get_targetElement(&target);

		if (target)
		{
			CComQIPtr<ILSMILAnimationTarget> animtarget = target;

			CComBSTR tagName;
			thisNode->get_localName(&tagName);	// Try local name first
			if (tagName.Length() == 0)
			{
				tagName.Empty();
				thisNode->get_tagName(&tagName);	// Then try full qualified name
			}

			CComBSTR attrName;
			thisNode->getAttribute(L"attributeName", &attrName);

			if (attrName.Length())
			{
				m_pAttributeType = NULL;	// The type of property being animated (factory class for creating new values of that type)
				m_animatedAttr = NULL;	// The attribute being animated

			//	BSTR attrType = NULL;
			//	thisNode->getAttribute(L"attributeType", &attrType);

				CComBSTR type;
				getAttribute(L"type", &type);
				if (type.Length() == 0)
				{
					type = L"translate";	// Default
				}

				CAttributeTransformType* pTransformType = new CAttributeTransformType;

				if (!wcscmp(type, L"translate")) pTransformType->m_type = SVG_TRANSFORM_TRANSLATE;
				else if (!wcscmp(type, L"scale")) pTransformType->m_type = SVG_TRANSFORM_SCALE;
				else if (!wcscmp(type, L"rotate")) pTransformType->m_type = SVG_TRANSFORM_ROTATE;
				else if (!wcscmp(type, L"skewX")) pTransformType->m_type = SVG_TRANSFORM_SKEWX;
				else if (!wcscmp(type, L"skewY")) pTransformType->m_type = SVG_TRANSFORM_SKEWY;
				else if (!wcscmp(type, L"matrix")) pTransformType->m_type = SVG_TRANSFORM_MATRIX;
				else	// Unsupported transform type
				{
					delete pTransformType;
					pTransformType = NULL;
				}

				m_pAttributeType = pTransformType;

		//		SysFreeString(attrType);

				if (m_pAttributeType)
				{
					CAnimationTarget* pAnimationTarget = static_cast<CAnimationTarget*>(animtarget.p);

					m_animatedAttr = CComQIPtr<CLDOMElementImplImpl>(target)->GetXMLAttribute(attrName);

					BSTR fromstr;
					BSTR tostr;
					BSTR bystr;
					BSTR valuesstr;
					BSTR keySplinesstr;

					thisNode->getAttribute(L"from", &fromstr);
					thisNode->getAttribute(L"to", &tostr);
					thisNode->getAttribute(L"by", &bystr);
					thisNode->getAttribute(L"values", &valuesstr);
					thisNode->getAttribute(L"keySplines", &keySplinesstr);

					m_bInError = FALSE;

					if (valuesstr)
					{
						CArray<CWCharString,CWCharString> values;
						GetSemicolonSepStringArray(valuesstr, values);

						CComBSTR keyTimesstr;
						thisNode->getAttribute(L"keyTimes", &keyTimesstr);
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

					SysFreeString(fromstr);
					SysFreeString(tostr);
					SysFreeString(bystr);
					SysFreeString(valuesstr);
					SysFreeString(keySplinesstr);
				}
			}
		}

		m_reentrance--;
	}
#endif
}

//virtual
void SVGAnimateTransformElement::DoAnimationForElement(CATAttr* pAnimatedAttr)
{
	bool bAdditive = m_animateImpl->get_additive() == ADDITIVE_SUM;
	m_animateImpl->m_currentValue = m_animateImpl->m_pAttributeType->NewVal();

	m_animateImpl->DoAnimationForElement2(pAnimatedAttr, bAdditive);

	CValueType* pAnimVal = pAnimatedAttr->GetAnimVal();

//	CATXMLAttr2T<CreateInstance<CLSVGAnimatedTransformList>, CValueTypeWrapper<CreateInstance<SVGTransformList> > >* pAnimatedTransform = static_cast<CATXMLAttr2T<CreateInstance<CLSVGAnimatedTransformList>, CValueTypeWrapper<CreateInstance<SVGTransformList> > >*>(pAnimatedAttr);
//	SVGTransformList* transformlist = pAnimatedTransform->m_animated->m_animVal->m_value;//CComQIPtr<ILSVGAnimatedTransformList> animtransform;

	SVGTransformList* transformlist = static_cast<CValueTypeWrapper<CreateInstanceT<SVGTransformList> >*>(pAnimVal)->m_value;
	SVGTransform* transform = static_cast<CValueTypeWrapper<CreateInstanceT<SVGTransform> >*>(m_animateImpl->m_currentValue)->m_value;

	if (bAdditive)
	{
		transformlist->insertItemBefore(transform, 0);
	}
	else
	{
		transformlist->clear();
		transformlist->appendItem(transform);
	}

	/*
	if (bAdditive)
	{
		*pAnimVal += m_currentValue;
	}
	else
	{
		*pAnimVal = m_currentValue;
	}
	*/
}

}	// w3c
}

#if 0
// virtual
void SVGAnimateTransformElement::DoAnimationForElement(ILDOMElement* target)
{
	BOOL bAdditive = m_additive->m_value->m_value == ADDITIVE_SUM;

	double t = m_tsf / m_simpleDur;// ???(newLocalTime)/dur;	// TODO

	CATXMLAttr2T<CreateInstance<CLSVGAnimatedTransformList>, CValueTypeWrapper<CreateInstance<SVGTransformList> > >* pAnimatedTransform = static_cast<CATXMLAttr2T<CreateInstance<CLSVGAnimatedTransformList>, CValueTypeWrapper<CreateInstance<SVGTransformList> > >*>(m_animatedAttr);
	SVGTransformList* transformlist = pAnimatedTransform->m_animated->m_animVal->m_value;//CComQIPtr<ILSVGAnimatedTransformList> animtransform;

	if (transformlist)
	{
		CComObject<SVGTransform>* transform;
		CComObject<SVGTransform>::CreateInstance(&transform);
		if (transform)
		{
			transform->AddRef();

			CComBSTR type;
			getAttribute(L"type", &type);
			if (type.Length() == 0)
			{
				type = L"translate";	// Default
			}

			CComBSTR fromstr;
			getAttribute(L"from", &fromstr);
			
			CComBSTR tostr;
			getAttribute(L"to", &tostr);

			if (!wcscmp(type, L"translate"))
			{
				double from_x, from_y;
				GetTranslateValues(fromstr, from_x, from_y);

				double to_x, to_y;
				GetTranslateValues(tostr, to_x, to_y);

				double x = from_x + (to_x-from_x)*t;
				double y = from_y + (to_y-from_y)*t;

				transform->SetTranslate(x, y);
			}
			else if (!wcscmp(type, L"scale"))
			{
				double from_sx, from_sy;
				GetScaleValues(fromstr, from_sx, from_sy);

				double to_sx, to_sy;
				GetScaleValues(tostr, to_sx, to_sy);

				double sx = from_sx + (to_sx-from_sx)*t;
				double sy = from_sy + (to_sy-from_sy)*t;

				transform->SetScale(sx, sy);
			}
			else if (!wcscmp(type, L"rotate"))
			{
				double from_deg, from_cx, from_cy;
				GetRotateValues(fromstr, from_deg, from_cx, from_cy);

				double to_deg, to_cx, to_cy;
				GetRotateValues(tostr, to_deg, to_cx, to_cy);

				double deg = from_deg + (to_deg-from_deg)*t;
				double cx = from_cx + (to_cx-from_cx)*t;
				double cy = from_cy + (to_cy-from_cy)*t;

				transform->SetRotate(deg, cx, cy);
			}
			else if (!wcscmp(type, L"skewX"))
			{
			}
			else if (!wcscmp(type, L"skewY"))
			{
			}
			else if (!wcscmp(type, L"matrix"))
			{
			}

			if (bAdditive)
			{
				transformlist->insertItemBefore(transform, 0, NULL);
			}
			else
			{
				transformlist->clear();
				transformlist->appendItem(transform, NULL);
			}

			transform->Release();
		}
	}
}
#endif
