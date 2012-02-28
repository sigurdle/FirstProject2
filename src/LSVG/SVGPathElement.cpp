#include "stdafx.h"
#include "LSVG2.h"
#include "SVGPathElement.h"
#include "PSVGPathElement.h"

//#include "LSVGPathSegList.h"

#include "../HTML/SVGPathSegClosePath.h"
#include "../HTML/SVGPathSegMovetoAbs.h"
#include "../HTML/SVGPathSegMovetoRel.h"
#include "../HTML/SVGPathSegLinetoAbs.h"
#include "../HTML/SVGPathSegLinetoRel.h"
#include "../HTML/SVGPathSegCurvetoCubicAbs.h"
#include "../HTML/SVGPathSegCurvetoCubicRel.h"
#include "../HTML/SVGPathSegCurvetoCubicSmoothAbs.h"
#include "../HTML/SVGPathSegCurvetoCubicSmoothRel.h"
#include "../HTML/SVGPathSegCurvetoQuadraticAbs.h"
#include "../HTML/SVGPathSegCurvetoQuadraticRel.h"
#include "../HTML/SVGPathSegCurvetoQuadraticSmoothAbs.h"
#include "../HTML/SVGPathSegCurvetoQuadraticSmoothRel.h"
#include "../HTML/SVGPathSegLinetoHorizontalAbs.h"
#include "../HTML/SVGPathSegLinetoHorizontalRel.h"
#include "../HTML/SVGPathSegLinetoVerticalAbs.h"
#include "../HTML/SVGPathSegLinetoVerticalRel.h"

namespace System
{
namespace Web
{

SVGPathElement::SVGPathElement() : SVGTransformableElement(new PSVGPathElement(this))
{
	SetAllValues(this);	// ???
}

#if 0
/////////////////////////////////////////////////////////////////////////////
// SVGPathElement

STDMETHODIMP SVGPathElement::createSVGPathSegClosePath(ILSVGPathSegClosePath **ppResult)
{
	CComObject<CLSVGPathSegClosePath>* seg_closepath;
	CComObject<CLSVGPathSegClosePath>::CreateInstance(&seg_closepath);

	(*ppResult = seg_closepath)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegMovetoAbs(double x, double y, ILSVGPathSegMovetoAbs **ppResult)
{
	CComObject<CLSVGPathSegMovetoAbs>* seg_movetoabs;
	CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&seg_movetoabs);
	seg_movetoabs->set_x(x);
	seg_movetoabs->set_y(y);

	(*ppResult = seg_movetoabs)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegMovetoRel(double x, double y, ILSVGPathSegMovetoRel **ppResult)
{
	CComObject<CLSVGPathSegMovetoRel>* seg_movetorel;
	CComObject<CLSVGPathSegMovetoRel>::CreateInstance(&seg_movetorel);
	seg_movetorel->set_x(x);
	seg_movetorel->set_y(y);

	(*ppResult = seg_movetorel)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegLinetoAbs(double x, double y, ILSVGPathSegLinetoAbs **ppResult)
{
	CComObject<CLSVGPathSegLinetoAbs>* seg_linetoabs;
	CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg_linetoabs);
	seg_linetoabs->set_x(x);
	seg_linetoabs->set_y(y);

	(*ppResult = seg_linetoabs)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegLinetoRel(double x, double y, ILSVGPathSegLinetoRel **ppResult)
{
	CComObject<CLSVGPathSegLinetoRel>* seg_linetorel;
	CComObject<CLSVGPathSegLinetoRel>::CreateInstance(&seg_linetorel);
	seg_linetorel->set_x(x);
	seg_linetorel->set_y(y);

	(*ppResult = seg_linetorel)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegCurvetoCubicAbs(double x, double y, double x1, double y1, double x2, double y2, ILSVGPathSegCurvetoCubicAbs **ppResult)
{
	CComObject<CLSVGPathSegCurvetoCubicAbs>* seg_curvetocubicabs;
	CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg_curvetocubicabs);
	seg_curvetocubicabs->set_x(x);
	seg_curvetocubicabs->set_y(y);
	seg_curvetocubicabs->set_x1(x1);
	seg_curvetocubicabs->set_y1(y1);
	seg_curvetocubicabs->set_x2(x2);
	seg_curvetocubicabs->set_y2(y2);

	(*ppResult = seg_curvetocubicabs)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegCurvetoCubicRel(double x, double y, double x1, double y1, double x2, double y2, ILSVGPathSegCurvetoCubicRel **ppResult)
{
	CComObject<CLSVGPathSegCurvetoCubicRel>* seg_curvetocubicrel;
	CComObject<CLSVGPathSegCurvetoCubicRel>::CreateInstance(&seg_curvetocubicrel);
	seg_curvetocubicrel->set_x(x);
	seg_curvetocubicrel->set_y(y);
	seg_curvetocubicrel->set_x1(x1);
	seg_curvetocubicrel->set_y1(y1);
	seg_curvetocubicrel->set_x2(x2);
	seg_curvetocubicrel->set_y2(y2);

	(*ppResult = seg_curvetocubicrel)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegCurvetoQuadraticAbs(double x, double y, double x1, double y1, ILSVGPathSegCurvetoQuadraticAbs **pVal)
{
	CComObject<CLSVGPathSegCurvetoQuadraticAbs>* seg;
	CComObject<CLSVGPathSegCurvetoQuadraticAbs>::CreateInstance(&seg);
	seg->set_x(x);
	seg->set_y(y);
	seg->set_x1(x1);
	seg->set_y1(y1);

	(*pVal = seg)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegCurvetoQuadraticRel(double x, double y, double x1, double y1, ILSVGPathSegCurvetoQuadraticRel **pVal)
{
	CComObject<CLSVGPathSegCurvetoQuadraticRel>* seg;
	CComObject<CLSVGPathSegCurvetoQuadraticRel>::CreateInstance(&seg);
	seg->set_x(x);
	seg->set_y(y);
	seg->set_x1(x1);
	seg->set_y1(y1);

	(*pVal = seg)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegLinetoHorizontalAbs(double x, ILSVGPathSegLinetoHorizontalAbs **pVal)
{
	CComObject<CLSVGPathSegLinetoHorizontalAbs>* seg;
	CComObject<CLSVGPathSegLinetoHorizontalAbs>::CreateInstance(&seg);
	seg->set_x(x);

	(*pVal = seg)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegLinetoHorizontalRel(double x, ILSVGPathSegLinetoHorizontalRel **pVal)
{
	CComObject<CLSVGPathSegLinetoHorizontalRel>* seg;
	CComObject<CLSVGPathSegLinetoHorizontalRel>::CreateInstance(&seg);
	seg->set_x(x);

	(*pVal = seg)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegLinetoVerticalAbs(double y, ILSVGPathSegLinetoVerticalAbs **pVal)
{
	CComObject<CLSVGPathSegLinetoVerticalAbs>* seg;
	CComObject<CLSVGPathSegLinetoVerticalAbs>::CreateInstance(&seg);
	seg->set_y(y);

	(*pVal = seg)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegLinetoVerticalRel(double y, ILSVGPathSegLinetoVerticalRel **pVal)
{
	CComObject<CLSVGPathSegLinetoVerticalRel>* seg;
	CComObject<CLSVGPathSegLinetoVerticalRel>::CreateInstance(&seg);
	seg->set_y(y);

	(*pVal = seg)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegCurvetoCubicSmoothAbs(double x, double y, double x2, double y2, ILSVGPathSegCurvetoCubicSmoothAbs **pVal)
{
	CComObject<CLSVGPathSegCurvetoCubicSmoothAbs>* seg;
	CComObject<CLSVGPathSegCurvetoCubicSmoothAbs>::CreateInstance(&seg);
	seg->set_x(x);
	seg->set_y(y);
	seg->set_x2(x2);
	seg->set_y2(y2);

	(*pVal = seg)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegCurvetoCubicSmoothRel(double x, double y, double x2, double y2, ILSVGPathSegCurvetoCubicSmoothRel **pVal)
{
	CComObject<CLSVGPathSegCurvetoCubicSmoothRel>* seg;
	CComObject<CLSVGPathSegCurvetoCubicSmoothRel>::CreateInstance(&seg);
	seg->set_x(x);
	seg->set_y(y);
	seg->set_x2(x2);
	seg->set_y2(y2);

	(*pVal = seg)->AddRef();

	return S_OK;
}

STDMETHODIMP SVGPathElement::createSVGPathSegCurvetoQuadraticSmoothAbs(double x, double y, ILSVGPathSegCurvetoQuadraticSmoothAbs **pVal)
{
	CComObject<CLSVGPathSegCurvetoQuadraticSmoothAbs>* seg;
	CComObject<CLSVGPathSegCurvetoQuadraticSmoothAbs>::CreateInstance(&seg);
	seg->set_x(x);
	seg->set_y(y);

	(*pVal = seg)->AddRef();

	return S_OK;
}

// ILSVGAnimatedPathData

STDMETHODIMP SVGPathElement::createSVGPathSegCurvetoQuadraticSmoothRel(double x, double y, ILSVGPathSegCurvetoQuadraticSmoothRel **pVal)
{
	CComObject<CLSVGPathSegCurvetoQuadraticSmoothRel>* seg;
	CComObject<CLSVGPathSegCurvetoQuadraticSmoothRel>::CreateInstance(&seg);
	seg->set_x(x);
	seg->set_y(y);

	(*pVal = seg)->AddRef();

	return S_OK;
}

#endif

}
}
