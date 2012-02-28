#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

class IESVGDrawSelection
{
public:
	virtual ErrorCode DrawSelection(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix) = 0;
};

class CHitData;

template<class IBase> class CESelectedElementImpl :
	public IBase
{
public:
	CESelectedElementImpl()
	{
		m_pElement = NULL;
		m_viewGroup = NULL;
	}

	~CESelectedElementImpl()
	{
	}

	Element* m_pElement;

	CEXMLViewGroup* m_viewGroup;

// IESelectedUnknown
	ErrorCode get_selectedType(/*[out,retval]*/ long *pVal)
	{
		*pVal = 1;
		return Success;
	}
//

	/*
	virtual BOOL OnButtonDown(CHitData* hitdata, int nTool, UINT nFlags, LDraw::PointD wpt)
	{
		return FALSE;
	}
	*/

	virtual void MoveSelectedPoints(CHitData* hitdata, LDraw::PointD xnewpt2, LDraw::PointD xoldpt2, double dx, double dy/*LDraw::RectF& invalidBounds,*/)
	{
	}

	ErrorCode HitTest(ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, long tool, _SVGHitData* hit)
	{
#if 0
		LDraw::PointD pt(ptx, pty);

		CComQIPtr<ILDOMElement> domElement;
		m_pElement->get_domElement(&domElement);

	// get bounding box
		CComQIPtr<ILSVGTransformable> objectTransformable = domElement;
		SVGRect bounds;
		if (objectTransformable)
		{
			CComPtr<ILSVGRect> svgbounds;
			objectTransformable->getRBBox(&svgbounds);
			bounds = svgbounds;
		}

	// Check corner and center points
		LDraw::PointD pts[9] =
		{
			LDraw::PointD(bounds.X+bounds.Width/2, bounds.Y+bounds.Height/2),	// center point

			LDraw::PointD(bounds.X, bounds.Y),
			LDraw::PointD(bounds.X+bounds.Width/2, bounds.Y),
			LDraw::PointD(bounds.X+bounds.Width, bounds.Y),
			LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
			LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height),
			LDraw::PointD(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
			LDraw::PointD(bounds.X, bounds.Y+bounds.Height),
			LDraw::PointD(bounds.X, bounds.Y+bounds.Height/2),
		};

/*		CComPtr<ILLDraw::PointD> LDraw::PointD;
		svgsvgElement->createLDraw::PointD(&LDraw::PointD);
*/
		LDraw::PointD xpts[9];
		for (int npt = 0; npt < 9; npt++)
		{
/*			LDraw::PointD->put_x(pts[npt].X);
			LDraw::PointD->put_y(pts[npt].Y);

			CComPtr<ILLDraw::PointD> xLDraw::PointD;
			LDraw::PointD->matrixTransform(ctm, &xLDraw::PointD);
*/
			xpts[npt] = pts[npt].matrixTransform(ctm);//xLDraw::PointD;
		}

		for (npt = 0; npt < 9; npt++)
		{
			if ((fabs(pt.X-xpts[npt].X) <= 3) && (fabs(pt.X-xpts[npt].Y) <= 3))
			{
			//	CHitData* hit = new CHitData;
			//	*phit = hit;
				hit->hit = npt+1;
				return S_OK;
			}
		}
#endif
		return Success_False;
	}

	ErrorCode get_eElement(Element* *pVal)
	{
		ASSERT(m_pElement != NULL);	// Must have been set right after object creation
		if (m_pElement == NULL) return Error;

		*pVal = m_pElement;

		return Success;
	}

	ErrorCode put_eElement(Element* newVal)
	{
		ASSERT(m_pElement == NULL);	// Can only be set once
		if (m_pElement != NULL) return Error;

		ASSERT(newVal);
		m_pElement = newVal;

		return Success;
	}

	void Move(ISVGView* view, /*[in]*/ double dx, /*[in]*/ double dy)
	{
		CESVGElementImpl* esvgElement = dynamic_cast<CESVGElementImpl*>(m_pElement);
		if (esvgElement)
		{
			esvgElement->Move(view, dx, dy);
		}
	}

	ErrorCode DeleteSelection()
	{
		return Success_False;
	}

	Web::SVGMatrix* GetScreenCTM(ISVGView* view)
	{
		ASSERT(0);
		return NULL;
#if 0
		LXML::CHTMLWindow* window = view->GetHTMLWindow();
		
		Element> domElement
		m_pElement->get_domElement(&domElement);

		ASSERT(0);
		return 0;
#if 0
		return window->svgGetScreenCTM2(CComQIPtr<ILSVGElement>(domElement), pVal);
#endif
#endif
	}

	Web::ISVGRect* GetRBBox(/*[in]*/ ISVGView* view)
	{
		ASSERT(0);
		return NULL;
#if 0
		LXML::CHTMLWindow* window = view->GetHTMLWindow();

		CComPtr<ILDOMElement> domElement;
		m_pElement->get_domElement(&domElement);

		return window->svgGetRBBox(CComQIPtr<ILSVGElement>(domElement), pVal);
#endif
	}

	Web::ISVGRect* GetScreenBBox(/*[in]*/ ISVGView* view)
	{
		ASSERT(0);
		return NULL;
#if 0
		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<ILDOMElement> domElement;
		m_pElement->get_domElement(&domElement);

		return window->svgGetScreenBBox(CComQIPtr<ILSVGElement>(domElement), pVal);
#endif
	}
};

class CESelectedElement : 
	public CESelectedElementImpl<IESelectedElement>
{
public:
	CESelectedElement()
	{
	}

	~CESelectedElement()
	{
	}

};

}	// LXmlEdit
}
