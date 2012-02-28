#include "stdafx.h"
#include "LXML.h"
#include "AnimationElement.h"

namespace System
{
namespace Web
{

WEBEXT int ParseKeySplines(const WCHAR* s, vector<KeySpline*>& keySplines)
{
	const WCHAR* p = s;

	while (*p)
	{
		while (isspace(*p)) p++;

		double x1 = getfnumber(&p);
		if (p == NULL) return -1;

		while (isspace(*p)) p++;

		double y1 = getfnumber(&p);
		if (p == NULL) return -1;

		while (isspace(*p)) p++;

		double x2 = getfnumber(&p);
		if (p == NULL) return -1;

		while (isspace(*p)) p++;

		double y2 = getfnumber(&p);
		if (p == NULL) return -1;

		KeySpline* pKeySpline = new KeySpline;
	//	CComObject<CLKeySpline>::CreateInstance(&pKeySpline);
	//	pKeySpline->AddRef();

		pKeySpline->m_x1 = x1;
		pKeySpline->m_y1 = y1;
		pKeySpline->m_x2 = x2;
		pKeySpline->m_y2 = y2;

		keySplines.Add(pKeySpline);

		while (isspace(*p)) p++;

		if (*p != L';')
			break;

		p++;
	}

	return keySplines.GetSize();
}

ElementAnimate::ElementAnimate(Element* ownerElement, CalcModeType calcMode) : ElementAnimation(ownerElement)
{
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_additiveAttr), nullptr, S("additive"));
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_accumulateAttr), nullptr, S("accumulate"));
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_calcModeAttr), nullptr, S("calcMode"));

	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_fromAttr), nullptr, S("from"));
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_byAttr), nullptr, S("by"));
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_toAttr), nullptr, S("to"));

	m_fromValue = nullptr;
	m_toValue = nullptr;
	m_byValue = nullptr;

	/*
	m_calcMode = NULL;
	m_additive = NULL;
	m_accumulate = NULL;
	*/

#if 0
	m_ownerElement->AddXMLAttribute(NewNXMLAttr(&m_additive, WSTR(""), WSTR("additive"), WSTR("replace")));
	m_ownerElement->AddXMLAttribute(NewNXMLAttr(&m_accumulate, WSTR(""), WSTR("accumulate"), WSTR("none")));
#endif
	m_additive = ADDITIVE_REPLACE;
	m_accumulate = ACCUMULATE_NONE;
	m_calcMode = calcMode;

// Different base classes have different default here
//	m_ownerElement->AddXMLAttribute(NewNXMLAttr(&m_calcMode, NULL, WSTR("calcMode"), WSTR("linear")));
}

Object* ElementAnimate::GetValueObject(Object* prevValue, Object* baseValue)
{
	double t_ = /*m_currentSimpleTime*/m_tsf / m_dur;

	m_valueHandler->InterpolateValue(m_currentValue, m_fromValue, m_toValue, t_);
	return m_currentValue;

#if 0

	bool error = false;

	double t_ = /*m_currentSimpleTime*/m_tsf / m_dur;

	if (m_valuesValues.size() > 0)
	{
		ASSERT(0);
	}
	else if (m_fromValue)
	{
		double t = t_;

		if (m_toValue)
		{
			m_currentValue->InterpolateValue(m_fromValue, m_toValue, t);

			if (m_accumulate == ACCUMULATE_SUM)
			{
				for (int i = 0; i < m_iteration; i++)
				{
					m_currentValue->Add(m_toValue);
				}
			}
		}
		else if (m_byValue)
		{
			CValueType* toValue = m_pAttributeType->NewVal();
			toValue->CopyFrom(m_fromValue);
			toValue->Add(m_byValue);

			m_currentValue->InterpolateValue(m_fromValue, toValue, t);

			delete toValue;
		}
		else
		{
			error = true;
		}
	}
	else if (m_toValue)
	{
	//	f(t) = vcur + ((vto - vcur) * (t/d))

		double t = t_;

		CValueType* pCurVal = pAnimatedAttr->GetAnimVal();

		m_currentValue->InterpolateValue(pCurVal, m_toValue, t);
	}
	else if (m_byValue)
	{
		double t = t_;

		CValueType* fromValue = m_pAttributeType->NewVal();	// value of 0

		m_currentValue->InterpolateValue(fromValue, m_byValue, t);

		delete fromValue;

		bAdditive = true;
	}
	else
	{
		error = true;
	}
#endif
	return NULL;
}

void ElementAnimate::OnValueTypeChange(CValueType* pValue)
{
	ASSERT(0);
#if 0
	if (m_reentrance == 0)
	{
		m_reentrance++;

		if (pValue == m_fromValue)
		{
			m_ownerElement->setAttribute(WSTR("from"), m_fromValue->getStringValue());
		}
		else if (pValue == m_toValue)
		{
			m_ownerElement->setAttribute(WSTR("to"), m_toValue->getStringValue());
		}
		else if (pValue == m_byValue)
		{
			m_ownerElement->setAttribute(WSTR("by"), m_byValue->getStringValue());
		}
		else
		{
			System::StringW* str;
			ASSERT(0);
#if 0
			for (int i = 0; i < m_valuesValues.GetSize(); i++)
			{
				if (i > 0) str += L";";
				str += StringW(*m_valuesValues[i]);
			}
#endif
			m_ownerElement->setAttribute(WSTR("values"), str);
		}

		m_reentrance--;
	}
#endif
}

void ElementAnimate::SetValuesFromAttributes()
{
	if (m_reentrance == 0)
	{
		ASSERT(0);
#if 0
		m_reentrance++;

		m_animatedAttr = NULL;
		m_pAttributeType = NULL;
		m_keyTimes.RemoveAll();
		m_valuesValues.RemoveAll();
		m_fromValue = NULL;
		m_toValue = NULL;
		m_byValue = NULL;

		Element* thisNode = static_cast<T*>(this);//->GetUnknown();
		CComPtr<Element> target;
		get_targetElement(&target);

		if (target)
		{
			CComQIPtr<ILSMILAnimationTarget, &IID_ILSMILAnimationTarget> animtarget((IUnknown*)target);

			CComBSTR tagName;
			thisNode->get_localName(&tagName);	// Try local name first
			if (tagName.Length() == 0)
			{
				tagName.Empty();
				thisNode->get_tagName(&tagName);	// Then try full qualified name
			}

			CComBSTR attrName;
			thisNode->getAttribute(WSTR("attributeName"), &attrName);

			if (attrName.Length())
			{
				m_pAttributeType = NULL;	// The type of property being animated (factory class for creating new values of that type)
				m_animatedAttr = NULL;	// The attribute being animated

				if (!wcscmp(tagName, WSTR("set")) ||
					!wcscmp(tagName, WSTR("animate")) ||
					!wcscmp(tagName, WSTR("animateColor")) ||
					!wcscmp(tagName, WSTR("animateTransform")))
				{
					BSTR attrType = NULL;
					thisNode->getAttribute(WSTR("attributeType"), &attrType);

					CAnimationTarget* pAnimationTarget = static_cast<CAnimationTarget*>(animtarget.p);

					if ((attrType == NULL) || !wcscmp(attrType, WSTR("auto")))
					{
						int propertyIndex = GetCSSStyleIndex(attrName);
						if (propertyIndex >= 0)
						{
							CCSSPropertyType* pPropertyType = new CCSSPropertyType;
							pPropertyType->m_propertyIndex = propertyIndex;
							m_pAttributeType = pPropertyType;
						}
						else
						{
							m_animatedAttr = CComQIPtr<CLDOMElementImplImpl, &IID_IUnknown/*TODO*/>((IUnknown*)target)->GetXMLAttribute(attrName);
							m_pAttributeType = (CATXMLAttr*)m_animatedAttr;
						}
					}
					else if (!wcscmp(attrType, WSTR("CSS")))
					{
						int propertyIndex = GetCSSStyleIndex(attrName);
						if (propertyIndex >= 0)
						{
							CCSSPropertyType* pPropertyType = new CCSSPropertyType;
							pPropertyType->m_propertyIndex = propertyIndex;
							m_pAttributeType = pPropertyType;
						}
					}
					else if (!wcscmp(attrType, WSTR("XML")))
					{
						m_animatedAttr = CComQIPtr<CLDOMElementImplImpl, &IID_IUnknown/*TODO*/>((IUnknown*)target)->GetXMLAttribute(attrName);
						m_pAttributeType = (CATXMLAttr*)m_animatedAttr;
					}

					SysFreeString(attrType);

					if (m_pAttributeType)
					{
						BSTR fromstr;
						BSTR tostr;
						BSTR bystr;
						BSTR valuesstr;
						BSTR keySplinesstr;

						thisNode->getAttribute(WSTR("from"), &fromstr);
						thisNode->getAttribute(WSTR("to"), &tostr);
						thisNode->getAttribute(WSTR("by"), &bystr);
						thisNode->getAttribute(WSTR("values"), &valuesstr);
						thisNode->getAttribute(WSTR("keySplines"), &keySplinesstr);

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
							*m_fromValue = CComBSTR(fromstr);

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
							*m_byValue = CComBSTR(bystr);

							m_byValue->m_pListener = this;
						}

						m_currentValue = m_pAttributeType->NewVal();

						SysFreeString(fromstr);
						SysFreeString(tostr);
						SysFreeString(bystr);
						SysFreeString(valuesstr);
						SysFreeString(keySplinesstr);
					}
				}
			}
		}

		m_reentrance--;
#endif
	}
}

void ElementAnimate::OnSetTargetElement(Element* targetElement)
{
	if (m_targetElement)
	{
		// TODO
		ASSERT(0);
	}

	m_targetElement = targetElement;

	if (m_targetElement)
	{
		String attributeName = get_attributeName();

		Attr* attr = m_targetElement->getAttributeNode(attributeName);
		if (attr)
		{
			m_xmlAttribute = attr;

		//	IValueHandler* valueHandler = attr->m_callbacks->GetValueHandler();
			IValueHandler* valueHandler = attr->m_owner->GetValueHandler();
			if (valueHandler != m_valueHandler)	// If there's a different kind of value (different handler), then must reparse
			{
				m_valueHandler = valueHandler;

				if (m_fromAttr->get_specified())
				{
					m_fromValue = m_valueHandler->Create();
					m_valueHandler->ParseString(m_fromValue, m_fromAttr->get_value());
				}

				if (m_toAttr->get_specified())
				{
					m_toValue = m_valueHandler->Create();
					m_valueHandler->ParseString(m_toValue, m_toAttr->get_value());
				}

				if (m_byAttr->get_specified())
				{
					m_byValue = m_valueHandler->Create();
					m_valueHandler->ParseString(m_byValue, m_byAttr->get_value());
				}

				// ??
				m_currentValue = m_valueHandler->Create();
			}
		}
	}
}

void ElementAnimate::DoAnimationForElementAttr(CATAttr* pAnimatedAttr)
{
	bool bAdditive = m_additive == ADDITIVE_SUM;

	DoAnimationForElement2(pAnimatedAttr, bAdditive);

	ASSERT(0);
#if 0
	CValueType* pAnimVal = pAnimatedAttr->GetAnimVal();

	if (bAdditive)
	{
		pAnimVal->Add(m_currentValue);
	}
	else
	{
		pAnimVal->CopyFrom(m_currentValue);
	}
#endif
}

void ElementAnimate::DoAnimationForElement(Element* target)
{
	if (m_animatedAttr)	// XML Attribute
	{
		DoAnimationForElementAttr(m_animatedAttr);
	}
}

void ElementAnimate::DoAnimationForElement2(CATAttr* pAnimatedAttr, bool& bAdditive)
{

	ASSERT(0);
#if 0

	ASSERT(pAnimatedAttr != NULL);

	bool error = false;

	double t_ = /*m_currentSimpleTime*/m_tsf / m_dur;

	if (m_valuesValues.GetSize() > 0)
	{
		if (m_keyTimes.GetSize() == m_valuesValues.GetSize())
		{
			unsigned int numkeys = m_keyTimes.size();

			//double currentTime = (newLocalTime)/dur;

			int left = -1;
			int right = -1;

			for (int i = 0; i < numkeys; i++)
			{
				if (m_keyTimes[i] <= t_) left = i;
				else if (m_keyTimes[i] > t_) break;
			}

			right = left+1;

			if (left < 0) left = 0;
			if (right > numkeys-1) right = numkeys-1;

			if (m_calcMode == CALCMODE_DISCRETE)
			{
				m_currentValue->CopyFrom(m_valuesValues[left]);
			}
			else if (m_calcMode == CALCMODE_LINEAR)
			{
				double t;

				if (left != right)
				{
					t = (double)(t_ - m_keyTimes[left]) / (double)(m_keyTimes[right] - m_keyTimes[left]);
				}
				else	// left = right
				{
					t = 0;
				}

				m_currentValue->InterpolateValue(m_valuesValues[left], m_valuesValues[right], t);
			}
			else if (m_calcMode == CALCMODE_SPLINE)
			{
				if (m_keySplines.GetSize() > left)
				{
					double it = (double)(t_ - m_keyTimes[left]) / (double)(m_keyTimes[right] - m_keyTimes[left]);
					double ot;

					{
						double x0 = 0;
						double y0 = 0;
						double x1 = m_keySplines[left]->m_x1;
						double y1 = m_keySplines[left]->m_y1;
						double x2 = m_keySplines[left]->m_x2;
						double y2 = m_keySplines[left]->m_y2;
						double x3 = 1;
						double y3 = 1;

						for (double t = 0; t < 1; t += 0.001)
						{
							double cx = 3 * (x1 - x0);
							double cy = 3 * (y1 - y0);
							double bx = 3 * (x2 - x1) - cx;
							double by = 3 * (y2 - y1) - cy;
							double ax = x3 - x0 - cx - bx;
							double ay = y3 - y0 - cy - by;

							double xt = ax * t*t*t + bx * t*t + cx * t + x0;
							double yt = ay * t*t*t + by * t*t + cy * t + y0;

							if (xt >= it)
							{
								ot = yt;
								break;
							}
						}
					}

					m_currentValue->InterpolateValue(m_valuesValues[left], m_valuesValues[right], ot);
				}
				else
				{
					error = true;
				}
			}
		}
		else
		{
			error = true;
		}
	}
	else if (m_fromValue)
	{
		double t = t_;

		if (m_toValue)
		{
			m_currentValue->InterpolateValue(m_fromValue, m_toValue, t);

			if (m_accumulate == ACCUMULATE_SUM)
			{
				for (int i = 0; i < m_iteration; i++)
				{
					m_currentValue->Add(m_toValue);
				}
			}
		}
		else if (m_byValue)
		{
			CValueType* toValue = m_pAttributeType->NewVal();
			toValue->CopyFrom(m_fromValue);
			toValue->Add(m_byValue);

			m_currentValue->InterpolateValue(m_fromValue, toValue, t);

			delete toValue;
		}
		else
		{
			error = true;
		}
	}
	else if (m_toValue)
	{
	//	f(t) = vcur + ((vto - vcur) * (t/d))

		double t = t_;

		CValueType* pCurVal = pAnimatedAttr->GetAnimVal();

		m_currentValue->InterpolateValue(pCurVal, m_toValue, t);
	}
	else if (m_byValue)
	{
		double t = t_;

		CValueType* fromValue = m_pAttributeType->NewVal();	// value of 0

		m_currentValue->InterpolateValue(fromValue, m_byValue, t);

		delete fromValue;

		bAdditive = true;
	}
	else
	{
		error = true;
	}
#endif
}

ErrorCode ElementAnimate::InsertKeyTimeValue(/*[in]*/ double keyTime, StringIn value, /*[out,retval]*/ long *pindex)
{
	ASSERT(0);
#if 0
	int index;
	for (index = 0; index < m_keyTimes.GetSize(); index++)
	{
		if (m_keyTimes[index] > keyTime)
		{
			break;
		}
	}

	int i;

	vector<System::StringW*, __gc_allocator> values;
	for (i = 0; i < m_valuesValues.GetSize(); i++)
	{
		values.Add(m_valuesValues[i]->getStringValue());
	}

	m_keyTimes.InsertAt(index, keyTime);
	values.InsertAt(index, (value));

	System::StringW* valuesstr;
	for (i = 0; i < values.GetSize(); i++)
	{
		ASSERT(0);
#if 0
		if (i > 0) valuesstr += WSTR(";");
		valuesstr += values[i];
#endif
	}

	System::StringW* keytimesstr;
	ASSERT(0);
#if 0
	for (i = 0; i < m_keyTimes.GetSize(); i++)
	{
		if (i > 0) keytimesstr += WSTR(";");
		WCHAR str2[64];
		swprintf(str2, L"%g", m_keyTimes[i]);
		keytimesstr += str2;
	}
#endif
	m_ownerElement->setAttribute(WSTR("values"), valuesstr);
	m_ownerElement->setAttribute(WSTR("keyTimes"), keytimesstr);

	*pindex = index;
#endif
	return Success;
}

ErrorCode ElementAnimate::RemoveKeyTime(/*[in]*/ long index)
{
	ASSERT(0);
#if 0
	unsigned int i;

	vector<System::StringW*> values;
	for (i = 0; i < m_valuesValues.GetSize(); i++)
	{
		values.Add(m_valuesValues[i]->getStringValue());
	}

	m_keyTimes.RemoveAt(index);
	values.RemoveAt(index);

	System::StringW* valuesstr;
	for (i = 0; i < values.GetSize(); i++)
	{
		ASSERT(0);
#if 0
		if (i > 0) valuesstr += WSTR(";");
		valuesstr += values[i];
#endif
	}

	System::StringW* keytimesstr;
	for (i = 0; i < m_keyTimes.GetSize(); i++)
	{
		ASSERT(0);
#if 0
		if (i > 0) keytimesstr += WSTR(";");
		WCHAR str2[64];
		swprintf(str2, WSTR("%g"), m_keyTimes[i]);
		keytimesstr += str2;
#endif
	}

	m_ownerElement->setAttribute(WSTR("values"), valuesstr);
	m_ownerElement->setAttribute(WSTR("keyTimes"), keytimesstr);
#endif

	return Success;
}

#if 0
void ElementAnimate::DoAnimationForElement2(CATAttr* pAnimatedAttr, bool& bAdditive)
{
	ASSERT(pAnimatedAttr != NULL);

	bool error = false;

	double t_ = /*m_currentSimpleTime*/m_tsf / m_dur;

	if (m_valuesValues.GetSize() > 0)
	{
		if (m_keyTimes.GetSize() == m_valuesValues.GetSize())
		{
			int numkeys = m_keyTimes.GetSize();

			//double currentTime = (newLocalTime)/dur;

			int left = -1;
			int right = -1;

			for (int i = 0; i < numkeys; i++)
			{
				if (m_keyTimes[i] <= t_) left = i;
				else if (m_keyTimes[i] > t_) break;
			}

			right = left+1;

			if (left < 0) left = 0;
			if (right > numkeys-1) right = numkeys-1;

			if (m_calcMode == CALCMODE_DISCRETE)
			{
				m_currentValue->CopyFrom(m_valuesValues[left]);
			}
			else if (m_calcMode == CALCMODE_LINEAR)
			{
				double t;

				if (left != right)
				{
					t = (double)(t_ - m_keyTimes[left]) / (double)(m_keyTimes[right] - m_keyTimes[left]);
				}
				else	// left = right
				{
					t = 0;
				}

				m_currentValue->InterpolateValue(m_valuesValues[left], m_valuesValues[right], t);
			}
			else if (m_calcMode == CALCMODE_SPLINE)
			{
				if (m_keySplines.GetSize() > left)
				{
					double it = (double)(t_ - m_keyTimes[left]) / (double)(m_keyTimes[right] - m_keyTimes[left]);
					double ot;

					{
						double x0 = 0;
						double y0 = 0;
						double x1 = m_keySplines[left]->m_x1;
						double y1 = m_keySplines[left]->m_y1;
						double x2 = m_keySplines[left]->m_x2;
						double y2 = m_keySplines[left]->m_y2;
						double x3 = 1;
						double y3 = 1;

						for (double t = 0; t < 1; t += 0.001)
						{
							double cx = 3 * (x1 - x0);
							double cy = 3 * (y1 - y0);
							double bx = 3 * (x2 - x1) - cx;
							double by = 3 * (y2 - y1) - cy;
							double ax = x3 - x0 - cx - bx;
							double ay = y3 - y0 - cy - by;

							double xt = ax * t*t*t + bx * t*t + cx * t + x0;
							double yt = ay * t*t*t + by * t*t + cy * t + y0;

							if (xt >= it)
							{
								ot = yt;
								break;
							}
						}
					}

					m_currentValue->InterpolateValue(m_valuesValues[left], m_valuesValues[right], ot);
				}
				else
				{
					error = true;
				}
			}
		}
		else
		{
			error = true;
		}
	}
	else if (m_fromValue)
	{
		double t = t_;

		if (m_toValue)
		{
			m_currentValue->InterpolateValue(m_fromValue, m_toValue, t);

			if (m_accumulate == ACCUMULATE_SUM)
			{
				for (int i = 0; i < m_iteration; i++)
				{
					m_currentValue->Add(m_toValue);
				}
			}
		}
		else if (m_byValue)
		{
			CValueType* toValue = m_pAttributeType->NewVal();
			toValue->CopyFrom(m_fromValue);
			toValue->Add(m_byValue);

			m_currentValue->InterpolateValue(m_fromValue, toValue, t);

			delete toValue;
		}
		else
		{
			error = true;
		}
	}
	else if (m_toValue)
	{
	//	f(t) = vcur + ((vto - vcur) * (t/d))

		double t = t_;

		CValueType* pCurVal = pAnimatedAttr->GetAnimVal();

		m_currentValue->InterpolateValue(pCurVal, m_toValue, t);
	}
	else if (m_byValue)
	{
		double t = t_;

		CValueType* fromValue = m_pAttributeType->NewVal();	// value of 0

		m_currentValue->InterpolateValue(fromValue, m_byValue, t);

		delete fromValue;

		bAdditive = true;
	}
	else
	{
		error = true;
	}
}
#endif

}	// w3c
}
