#pragma once

#include "ESVGElementImpl.h"
#include "ESelectedElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESelectedSVGLinearGradientElement : 
	public CESelectedElementImpl<IESelectedElement>,
	public IESVGDrawOutline
{
public:
	CESelectedSVGLinearGradientElement()
	{
	}

	~CESelectedSVGLinearGradientElement()
	{
	}

public:

	ErrorCode GetScreenCTM(ISVGView* view, Web::SVGMatrix* *pVal);
	ErrorCode GetRBBox(/*[in]*/ ISVGView* view, /*[out,retval]*/ Web::ISVGRect* *pVal);

	ErrorCode GetScreenBBox(/*[in]*/ ISVGView* view, /*[out,retval]*/ Web::ISVGRect* *pVal)
	{
		// TODO
		return GetRBBox(view, pVal);
	}

// IESVGDrawOutline
	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);

#if 0
	ErrorCode(Move)(/*[in]*/ double dx, /*[in]*/ double dy)
	{
		CComQIPtr<IESVGElement> esvgElement = m_pElement;
		if (esvgElement)
		{
			esvgElement->Move(dx, dy);
		}
		return S_OK;
	}
#endif
};

class CESVGLinearGradientElement :
	public CESVGElementImpl,
//	public IESVGSimpleShapeElement,
	public IESVGDrawOutline
{
public:
	CESVGLinearGradientElement()
	{
	}


	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability(/*[out,retval]*/ long* pVal)
	{
		return 1;
	}
//	virtual void Scale(double cx, double cy, double sx, double sy);
//	virtual void DrawPathCurve(HDC hDC, ILSVGMatrix* addmatrix);

	ErrorCode SetShape(/*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);

// IESVGDrawOutline
	ErrorCode DrawOutline(UI::Graphics* pGraphics, LDraw::Color& color, Web::SVGMatrix* matrix);

// IESVGSimpleShapeElement
//	ErrorCode(DrawPathSegList)(/*[in]*/ ILSVGPathElement* pathElement, /*[in]*/ ILSVGPathSegList* seglist);

	//virtual
	ErrorCode CreateSelectedElement(CEXMLViewGroup* viewGroup, IESelectedElement* *pVal)
	{
		ASSERT(0);
#if 0
		CComObject<CESelectedSVGLinearGradientElement>* pSelectedElement;
		CComObject<CESelectedSVGLinearGradientElement>::CreateInstance(&pSelectedElement);
		pSelectedElement->AddRef();
		pSelectedElement->m_pElement = this;
		pSelectedElement->m_viewGroup = viewGroup;

		*pVal = pSelectedElement;
#endif
		return Success;
	}
};

}	// LXmlEdit
}
