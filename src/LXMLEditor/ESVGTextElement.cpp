#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

//#include "WebXMLDocument.h"

#include "ESVGTextElement.h"

#if 0

void DrawPathSegList(ILSVGPathSegList* seglist, HDC iDC, ILSVGMatrix* xform);

STDMETHODIMP CESVGTextElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGTextElement> text = m_domElement;

	// x
	if (dx != 0)
	{
		CComPtr<ILSVGAnimatedLengthList> all;
		text->get_x(&all);

		CComPtr<ILSVGLengthList> ll;
		all->get_baseVal(&ll);

		long numberOfItems;
		ll->get_numberOfItems(&numberOfItems);
		for (int i = 0; i < numberOfItems; i++)
		{
			CComPtr<ILSVGLength> l;
			ll->getItem(i, &l);

			double v;
			l->get_value(&v);
			l->put_value(v+dx);
		}
	}

	// y
	if (dy != 0)
	{
		CComPtr<ILSVGAnimatedLengthList> all;
		text->get_y(&all);

		CComPtr<ILSVGLengthList> ll;
		all->get_baseVal(&ll);

		long numberOfItems;
		ll->get_numberOfItems(&numberOfItems);
		for (int i = 0; i < numberOfItems; i++)
		{
			CComPtr<ILSVGLength> l;
			ll->getItem(i, &l);

			double v;
			l->get_value(&v);
			l->put_value(v+dy);
		}
	}

	return S_OK;
}

#endif