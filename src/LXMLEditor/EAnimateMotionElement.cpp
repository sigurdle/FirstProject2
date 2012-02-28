#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EAnimationElement.h"

#if 0
void DrawPathSegList(LSVG::CLSVGPathSegList* seglist, LDraw::GraphicsPath* path, LSVG::SVGMatrix* matrix);

BOOL GetPointNearPath(LSVG::CLSVGPathSegList* segList, LSVG::SVGMatrix* matrix, /*[in]*/ double mousex, /*[in]*/ double mousey, /*[in]*/ double tolerance, /*[out]*/ long* segindex, /*[out]*/ double* pt);

// IESVGDrawOutline
STDMETHODIMP CEAnimateMotionElement::DrawOutline(LDraw::Graphics* pGraphics, LDraw::Color color, LSVG::SVGMatrix* matrix)
{
	CComPtr<ILDOMElement> domElement = get_domElement();

	CComQIPtr<ILSVGAnimateMotionElement> animateMotion = domElement;

	CComPtr<ILSVGPathSegList> seglist = animateMotion->get_normalizedPathSegList();

	LDraw::Pen pen(color);

	LDraw::GraphicsPath graphicsPath;
	::DrawPathSegList(seglist, &graphicsPath, matrix);

	pGraphics->DrawPath(&pen, &graphicsPath);

	return S_OK;
}

STDMETHODIMP CEAnimateMotionElement::HitTest(ISVGView* view, LSVG::SVGSVGElement* svgsvgElement, LSVG::SVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit)
{
	CComQIPtr<ILSVGAnimateMotionElement> pathData = m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
	pathData->get_pathSegList(&seglist);

	if (GetPointNearPath(seglist, ctm, ptx, pty, 2, &hit->segment, &hit->t))
	{
		hit->element = this;
		return S_OK;
	}

	return CEElementImpl<IEElement>::HitTest(view, svgsvgElement, ctm, ptx, pty, hit);
}

#if 0
int CEAnimateMotionElement::GetFromTo(CArray<PointD,PointD>& values)
{
	ASSERT(0);
#if 0

	_bstr_t fromstr = m_domElement->getAttribute(L"from");
	_bstr_t tostr = m_domElement->getAttribute(L"to");

	if (fromstr.length() > 0 && tostr.length() > 0)
	{
		CArray<double,double> fromvalues;
		GetCommaSepNumberArray(CUString((BSTR)fromstr), fromvalues);

		CArray<double,double> tovalues;
		GetCommaSepNumberArray(CUString((BSTR)tostr), tovalues);

		if (fromvalues.GetSize() == 2 && tovalues.GetSize() == 2)
		{
			values.Add(CDblPoint(fromvalues[0], fromvalues[1]));
			values.Add(CDblPoint(tovalues[0], tovalues[1]));

			return values.GetSize();
		}
	}
#endif
	return 0;
}

int CEAnimateMotionElement::GetValues(CArray<LDraw::PointD,LDraw::PointD>& values)
{
#if 0
	_bstr_t valuesstr = m_domElement->getAttribute(L"values");
	if (valuesstr.length() > 0)
	{
	}
#endif
	ASSERT(0);

	return 0;
}
#endif

#endif