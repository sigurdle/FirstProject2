#pragma once

//#include "EElementImpl.h"
#include "ESVGElementImpl.h"

#include "ESelectedAnimationElement.h"

namespace System
{
namespace LXmlEdit
{

class CEAnimationElementImpl
//	public Element//IEAnimationElement
{
public:
/*	CAnimationElement();

	int GetKeyTimes(CArray<double,double>& keyTimes);
	void PutKeyTimes(CArray<double,double>& keyTimes);

	int GetValues(CArray<CUString,CUString>& values);

	void InsertKeyTime(double keyTime);
	*/

	int GetKeyTimes(Array<double>& keyTimes)
	{
	#if 0
		_bstr_t str_keyTimes = m_domElement->getAttribute(L"keyTimes");

		if (str_keyTimes.length() > 0)
		{
			return GetCommaSepNumberArray(CUString((BSTR)str_keyTimes), keyTimes);
		}
	#endif

		return 0;
	}

	int GetValues(Array<System::StringW*>& values)
	{
	#if 0
		_bstr_t str_values = m_domElement->getAttribute(L"values");

		if (str_values.length() > 0)
		{
			return GetCommaSepStringArray(CUString((BSTR)str_values), values);
		}
	#endif

		return 0;
	}

	void PutKeyTimes(Array<double>& keyTimes)
	{
	#if 0
		CUString str = SetCommaSepNumberArray(keyTimes);
		m_domElement->setAttribute(L"keyTimes", _bstr_t(str));
	#endif
	}

	void InsertKeyTime(double keyTime)
	{
		Array<double> keyTimes;
		GetKeyTimes(keyTimes);

		for (int i = 0; i < keyTimes.GetSize(); i++)
		{
			if (keyTimes[i] > keyTime)
			{
				keyTimes.InsertAt(i, keyTime);
				goto Here;
			}
		}

		keyTimes.Add(keyTime);

	Here:

		PutKeyTimes(keyTimes);
	}
};

class CEAnimateElement :
	public CESVGElementImpl,
	public CEAnimationElementImpl//<CEAnimateElement>
{
public:

	//ErrorCode(Move)(double dx, double dy);

	ErrorCode CreateSelectedElement(CEXMLViewGroup* viewGroup, IESelectedElement* *pVal)
	{
	ASSERT(0);
#if 0
		CComObject<CESelectedAnimationElement>* pSelectedElement;
		CComObject<CESelectedAnimationElement>::CreateInstance(&pSelectedElement);
		pSelectedElement->AddRef();
		pSelectedElement->m_pElement = this;
		pSelectedElement->m_viewGroup = viewGroup;

		CComQIPtr<ILAnimationElement> animationElement = m_domElement;

		// Have it like this?
		CComPtr<ILDOMElement> targetElement;
		animationElement->get_targetElement(&targetElement);
		if (targetElement)
		{
			CComPtr<IEElement> etargetElement;
			m_pDocument->GetEElementFromDOMElement(targetElement, &etargetElement);

			etargetElement->CreateSelectedElement(viewGroup, &pSelectedElement->m_selectedTargetElement);
		}

		*pVal = pSelectedElement;
#endif
		return Success;
	}
};

class CEAnimateMotionElement :
	public Element,
	public CEAnimationElementImpl,//<CEAnimateMotionElement>,
	public IESVGDrawOutline
{
public:
	CEAnimateMotionElement()
	{
	}

	/*
	_bstr_t m_activeAttr;

	int GetValues(CArray<PointD,PointD>& values);
	int GetFromTo(CArray<PointD,PointD>& values);
	*/

	IESelectedElement* CreateSelectedElement(CEXMLViewGroup* viewGroup)
	{
		ASSERT(0);
		return NULL;
#if 0
		CESelectedAnimationElement* pSelectedElement = new CESelectedAnimationElement;
		pSelectedElement->m_pElement = this;
		pSelectedElement->m_viewGroup = viewGroup;

		return pSelectedElement;
#endif
	}

	ErrorCode HitTest(ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit);

// IESVGDrawOutline
void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
