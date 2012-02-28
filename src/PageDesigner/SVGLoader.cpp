#include "stdafx.h"

#if 0
#include "PageDesigner.h"
#include "SVGLoader.h"

ICSSValue* CSVGLoader::GetCSSValue(ISVGElement* element, BSTR cssname)
{
	CComQIPtr<IDOMDocument> document;
	element->get_ownerDocument(&document);

	CComQIPtr<IDOMViewCSS> cssView = document;

	ATLASSERT(cssView != NULL);

	CComPtr<ICSSValue> value;
	cssView->getComputedPropertyValue(element, NULL, cssname, &value);

	return value;
}

int CSVGLoader::GetPaint(ISVGElement* element, BSTR cssname, COLORREF& clr, CComPtr<ISVGElement>& urlElement)
{
	int ipaint = 0;

	CComQIPtr<ISVGPaint> paint = GetCSSValue(element, cssname);
	ATLASSERT(paint != NULL);	// ??

	_tagSVGPaintType paintType;
	paint->get_paintType(&paintType);

	if (paintType == SVG_PAINTTYPE_UNKNOWN)
	{
		ipaint = 0;
		//ATLASSERT(0);	// computed style is never inherited
//		ifill = 0;
		// Inherit ??
	}
	else
	{
		switch (paintType)
		{
#if 0
		case SVG_PAINTTYPE_URI_NONE:
		case SVG_PAINTTYPE_URI_CURRENTCOLOR:
		case SVG_PAINTTYPE_URI_RGBCOLOR:
		case SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR:
			{
				BSTR buri;
				paint->get_uri(&buri);
				_bstr_t uri = _bstr_t(buri);

				CComQIPtr<ISVGElement> svgelement = m_domElement;

				CComQIPtr<ISVGSVGElement> svgsvgElement;
				svgelement->get_ownerSVGElement(&svgsvgElement);

				svgsvgElement->getElementById(uri, (IDOMElement**)&urlElement);
				if (urlElement)
				{
					ipaint = 2;
				}
			}
			break;
#endif
		case SVG_PAINTTYPE_NONE:
			{
				ipaint = 0;
			}
			break;

		case SVG_PAINTTYPE_RGBCOLOR:
		case SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR:
			{
				CComQIPtr<IRGBColor> color;
				paint->get_rgbColor(&color);

				double red, green, blue;

				CComQIPtr<ICSSPrimitiveValue> redv;
				color->get_red(&redv);
				redv->getFloatValue(CSS_NUMBER, &red);

				CComQIPtr<ICSSPrimitiveValue> greenv;
				color->get_green(&greenv);
				greenv->getFloatValue(CSS_NUMBER, &green);

				CComQIPtr<ICSSPrimitiveValue> bluev;
				color->get_blue(&bluev);
				bluev->getFloatValue(CSS_NUMBER, &blue);

				if (red < 0) red = 0;
				else if (red > 255) red = 255;

				if (green < 0) green = 0;
				else if (green > 255) green = 255;

				if (blue < 0) blue = 0;
				else if (blue > 255) blue = 255;

				clr = RGB((BYTE)red, (BYTE)green, (BYTE)blue);

				ipaint = 1;
			}
		}
	}

	return ipaint;
}

double CSVGLoader::GetStrokeWidth(ISVGElement* element)
{
	CComQIPtr<ICSSPrimitiveValue> css = GetCSSValue(element, L"stroke-width");
	double value;
	css->getFloatValue(CSS_NUMBER, &value);
	return value;
}

double CSVGLoader::GetOpacity(ISVGElement* element)
{
	CComQIPtr<ICSSPrimitiveValue> css = GetCSSValue(element, L"opacity");
	double value;
	css->getFloatValue(CSS_NUMBER, &value);

	if (value < 0) value = 0;
	else if (value > 1) value = 1;

	return value;
}

double CSVGLoader::GetStrokeOpacity(ISVGElement* element)
{
	CComQIPtr<ICSSPrimitiveValue> css = GetCSSValue(element, L"stroke-opacity");
	double value;
	css->getFloatValue(CSS_NUMBER, &value);
	return value;
}

double CSVGLoader::GetFillOpacity(ISVGElement* element)
{
	CComQIPtr<ICSSPrimitiveValue> css = GetCSSValue(element, L"fill-opacity");
	double value;
	css->getFloatValue(CSS_NUMBER, &value);
	return value;
}

void CSVGLoader::SetFrameFill(IPDObjectFrame* pdframe, ISVGElement* element)
{
	// Fill
	COLORREF clr;
	CComPtr<ISVGElement> urlElement;
	int ifill = GetPaint(element, L"fill", clr, urlElement);

	if (ifill == 1)
	{
		CComPtr<IPDObjectFill> fill;
		fill.CoCreateInstance(CLSID_PDObjectFill);
		if (fill)
		{
			CComQIPtr<IPDObjectWithBrush> object = fill;

			CComPtr<IPDBrush> brush;
			object->get_brush(&brush);

			CComPtr<IPDColor> color;
			brush->setColor(&color);

			color->setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));

			pdframe->appendSubObject(object);
		}
	}
}

void CSVGLoader::SetFrameStroke(IPDObjectFrame* pdframe, ISVGElement* element)
{
	double strokeWeight = GetStrokeWidth(element);

	COLORREF clr;
	CComPtr<ISVGElement> urlElement;
	int istroke = GetPaint(element, L"stroke", clr, urlElement);

	if (istroke == 1)
	{
		CComPtr<IPDObjectStroke> stroke;
		stroke.CoCreateInstance(CLSID_PDObjectStroke);
		if (stroke)
		{
			CComQIPtr<IPDStrokeSettings> stroke2 = stroke;
			stroke2->put_strokeWeight(strokeWeight);

			CComQIPtr<IPDObjectWithBrush> object = stroke;

			CComPtr<IPDBrush> brush;
			object->get_brush(&brush);

			CComPtr<IPDColor> color;
			brush->setColor(&color);

			color->setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));

			pdframe->appendSubObject(object);
		}
	}
}

void CSVGLoader::SetTransform(IPDObject* pdobject, IDOMElement* element)
{
	CComQIPtr<IPDObjectTransformable> pdTransformable = pdobject;
	CComQIPtr<ISVGTransformable> svgTransformable = element;

	if (pdTransformable && svgTransformable)
	{
		CComPtr<ISVGAnimatedTransformList> alist;
		svgTransformable->get_transform(&alist);

		CComPtr<ISVGTransformList> list;
		alist->get_baseVal(&list);

		unsigned long length;
		list->get_numberOfItems(&length);

		CComPtr<ISVGMatrix> lmat;
		lmat.CoCreateInstance(CLSID_SVGMatrix);

		for (unsigned long i = 0; i < length; i++)
		{
			CComPtr<ISVGTransform> transform;
			list->getItem(i, &transform);

			CComPtr<ISVGMatrix> matrix;
			transform->get_matrix(&matrix);

			CComQIPtr<ISVGMatrix> m;
			lmat->multiply(matrix, &m);
			lmat = m;
		}

		double a; lmat->get_a(&a);
		double b; lmat->get_b(&b);
		double c; lmat->get_c(&c);
		double d; lmat->get_d(&d);
		double e; lmat->get_e(&e);
		double f; lmat->get_f(&f);

		CComPtr<IPDMatrix> pdmat;
		pdmat.CoCreateInstance(CLSID_PDMatrix);
		pdmat->put_a(a);
		pdmat->put_b(b);
		pdmat->put_c(c);
		pdmat->put_d(d);
		pdmat->put_e(e);
		pdmat->put_f(f);

		pdTransformable->put_transformMatrix(pdmat);
	}
}

void CSVGLoader::LoadLine(IPDObjectFrame* pdframe, ISVGLineElement* element)
{
	SetFrameFill(pdframe, element);
	SetFrameStroke(pdframe, element);

	SetTransform(pdframe, element);

	double x1;
	double y1;
	double x2;
	double y2;

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_x1(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&x1);
	}

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_y1(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&y1);
	}

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_x2(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&x2);
	}

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_y2(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&y2);
	}

	CComPtr<IPDPath> pdpath;
	pdframe->get_path(&pdpath);

	CComPtr<IPDSubPath> pdsubpath;
	pdpath->createSubPath(&pdsubpath);

	pdsubpath->setLine(x1, y1, x2, y2);

	pdpath->insertSubPath(-1, pdsubpath);
}

void CSVGLoader::LoadCircle(IPDObjectFrame* pdframe, ISVGCircleElement* element)
{
	SetFrameFill(pdframe, element);
	SetFrameStroke(pdframe, element);

	SetTransform(pdframe, element);

	double cx;
	double cy;
	double r;

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_cx(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&cx);
	}

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_cy(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&cy);
	}

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_r(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&r);
	}

	CComPtr<IPDPath> pdpath;
	pdframe->get_path(&pdpath);

	CComPtr<IPDSubPath> pdsubpath;
	pdpath->createSubPath(&pdsubpath);

	pdsubpath->setEllipse(cx-r, cy-r, cx+r, cy+r);

	pdpath->insertSubPath(-1, pdsubpath);
}

void CSVGLoader::LoadEllipse(IPDObjectFrame* pdframe, ISVGEllipseElement* element)
{
	SetFrameFill(pdframe, element);
	SetFrameStroke(pdframe, element);

	SetTransform(pdframe, element);

	double cx;
	double cy;
	double rx;
	double ry;

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_cx(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&cx);
	}

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_cy(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&cy);
	}

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_rx(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&rx);
	}

	{
		CComPtr<ISVGAnimatedLength> anim;
		element->get_ry(&anim);

		CComPtr<ISVGLength> length;
		anim->get_baseVal(&length);

		length->get_value(&ry);
	}

	CComPtr<IPDPath> pdpath;
	pdframe->get_path(&pdpath);

	CComPtr<IPDSubPath> pdsubpath;
	pdpath->createSubPath(&pdsubpath);

	pdsubpath->setEllipse(cx-rx, cy-ry, cx+rx, cy+ry);

	pdpath->insertSubPath(-1, pdsubpath);
}

void CSVGLoader::LoadPath(IPDObjectFrame* pdframe, ISVGPathElement* element)
{
	SetFrameFill(pdframe, element);
	SetFrameStroke(pdframe, element);

	SetTransform(pdframe, element);

	CComPtr<IPDPath> pdpath;
	pdframe->get_path(&pdpath);

	CComQIPtr<ISVGAnimatedPathData> pathdata = element;

	CComPtr<ISVGPathSegList> seglist;
	pathdata->get_normalizedPathSegList(&seglist);

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	CComPtr<IPDSubPath> pdsubpath;

	BezierPoint bpt;

	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ISVGPathSeg> seg;
		seglist->getItem(i, &seg);

		SVGPathSegType segType;
		seg->get_pathSegType(&segType);

		if (segType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ISVGPathSegMovetoAbs> moveto = seg;

			if (pdsubpath)
			{
				pdpath->insertSubPath(-1, pdsubpath);
				pdsubpath.Release();
			}

			pdpath->createSubPath(&pdsubpath);

			moveto->get_x(&bpt.x);
			moveto->get_y(&bpt.y);
			bpt.x1 = bpt.x;
			bpt.y1 = bpt.y;
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ISVGPathSegLinetoAbs> lineto = seg;
			ATLASSERT(0);
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ISVGPathSegCurvetoCubicAbs> curveto = seg;

			curveto->get_x1(&bpt.x2);
			curveto->get_y1(&bpt.y2);

			long index;
			pdsubpath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);

			curveto->get_x2(&bpt.x1);
			curveto->get_y2(&bpt.y1);
			curveto->get_x(&bpt.x);
			curveto->get_y(&bpt.y);
		}
		else if (segType == PATHSEG_CLOSEPATH)
		{
			bpt.x2 = bpt.x;
			bpt.y2 = bpt.y;

			long index;
			pdsubpath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);

			pdsubpath->put_closed(VARIANT_TRUE);

			pdpath->insertSubPath(-1, pdsubpath);
			pdsubpath.Release();
		}
		else
			ATLASSERT(0);
	}

	if (pdsubpath)
	{
		bpt.x2 = bpt.x;
		bpt.y2 = bpt.y;

		long index;
		pdsubpath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);

		pdpath->insertSubPath(-1, pdsubpath);
		pdsubpath.Release();
	}
}

BOOL CSVGLoader::LoadUse(IPDObjectSymbolInstance* instance, ISVGUseElement* useElement)
{
	SetTransform(instance, useElement);

	CComQIPtr<ISVGURIReference> uri = useElement;
	ATLASSERT(uri != NULL);

	double x;
	double y;

	{
		CComPtr<ISVGAnimatedLength> animx;
		useElement->get_x(&animx);

		CComPtr<ISVGLength> lengthx;
		animx->get_baseVal(&lengthx);

		lengthx->get_value(&x);
	}

	{
		CComPtr<ISVGAnimatedLength> animy;
		useElement->get_y(&animy);

		CComPtr<ISVGLength> lengthy;
		animy->get_baseVal(&lengthy);

		lengthy->get_value(&y);
	}

	CComPtr<ISVGAnimatedString> animstring;
	uri->get_href(&animstring);

	BSTR bhref;
	animstring->get_baseVal(&bhref);
	_bstr_t href = _bstr_t(bhref, false);

	BSTR href2 = &((BSTR)href)[1];	// Skip '#'

	CComPtr<IPDSymbol> symbol;
	m_pddoc->getSymbolByName(href2, &symbol);
	if (symbol)
	{
		instance->put_symbol(symbol);
		instance->setxy(x, y);

		return TRUE;
	}

	return FALSE;
}

void CSVGLoader::LoadGroup(IPDObjectGroup* pdgroup, IDOMElement* element)
{
	SetTransform(pdgroup, element);

	CComPtr<IDOMNodeList> childNodes;
	element->get_childNodes(&childNodes);

	unsigned long nchildNodes;
	childNodes->get_length(&nchildNodes);

	for (int i = 0; i < nchildNodes; i++)
	{
		CComPtr<IDOMNode> child;
		childNodes->item(i, &child);

		CComQIPtr<IDOMElement> element = child;
		if (element)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"g"))
			{
				CComPtr<IPDObjectGroup> pdgroup2;
				m_pddoc->createObjectGroup(GUID_NULL, &pdgroup2);

				LoadGroup(pdgroup2, element);

				pdgroup->appendObject(pdgroup2);
			}
			else if (!wcscmp(tagName, L"switch"))
			{
				LoadGroup(pdgroup, element);
			}
			else if (!wcscmp(tagName, L"symbol"))
			{
				CComPtr<IPDSymbol> symbol;
				symbol.CoCreateInstance(CLSID_PDSymbol);
				if (symbol)
				{
					BSTR bid;
					element->getAttribute(L"id", &bid);
					_bstr_t id = _bstr_t(bid, false);

					symbol->put_name(id);

					CComPtr<IPDObjectGroup> symbolGroup;
					m_pddoc->createObjectGroup(GUID_NULL, &symbolGroup);
					if (symbolGroup)
					{
						LoadGroup(symbolGroup, element);

						CComQIPtr<IPDObjectTransformable> transformable = symbolGroup;
						RectD bounds;
						transformable->get_bounds(&bounds);
						transformable->Move(-bounds.X, -bounds.Y);

						symbol->put_symbolObject(symbolGroup);
						m_pddoc->appendSymbol(symbol);
					}
				}
			}
			else if (!wcscmp(tagName, L"use"))
			{
				CComQIPtr<ISVGUseElement> useElement = element;

				CComPtr<IPDObjectSymbolInstance> instance;
				instance.CoCreateInstance(CLSID_PDObjectSymbolInstance);
				if (instance)
				{
					if (LoadUse(instance, useElement))
					{
						pdgroup->appendObject(instance);
					}
				}
			}
			else if (!wcscmp(tagName, L"path"))
			{
				CComQIPtr<ISVGPathElement> pathElement = element;

				CComPtr<IPDObjectFrame> frame;
				m_pddoc->createObjectFrame(&frame);
				if (frame)
				{
					LoadPath(frame, pathElement);

					pdgroup->appendObject(frame);
				}
			}
			else if (!wcscmp(tagName, L"line"))
			{
				CComQIPtr<ISVGLineElement> lineElement = element;

				CComPtr<IPDObjectFrame> frame;
				m_pddoc->createObjectFrame(&frame);
				if (frame)
				{
					LoadLine(frame, lineElement);

					pdgroup->appendObject(frame);
				}
			}
			else if (!wcscmp(tagName, L"circle"))
			{
				CComQIPtr<ISVGCircleElement> circleElement = element;

				CComPtr<IPDObjectFrame> frame;
				m_pddoc->createObjectFrame(&frame);
				if (frame)
				{
					LoadCircle(frame, circleElement);

					pdgroup->appendObject(frame);
				}
			}
			else if (!wcscmp(tagName, L"ellipse"))
			{
				CComQIPtr<ISVGEllipseElement> ellipseElement = element;

				CComPtr<IPDObjectFrame> frame;
				m_pddoc->createObjectFrame(&frame);
				if (frame)
				{
					LoadEllipse(frame, ellipseElement);

					pdgroup->appendObject(frame);
				}
			}
		}
	}
}

HRESULT CSVGLoader::Load(IPDDocument* pddoc, BSTR pathName, IPDObjectGroup* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	m_pddoc = pddoc;

	m_svgdoc.CoCreateInstance(CLSID_SVGDocument);
	if (m_svgdoc)
	{
		VARIANT_BOOL bloaded;
		m_svgdoc->load(pathName, &bloaded);
		if (bloaded)
		{
			CComPtr<ISVGSVGElement> svgelement;
			m_svgdoc->get_documentElement((IDOMElement**)&svgelement);

			CComPtr<IPDObjectGroup> pdgroup;
			m_pddoc->createObjectGroup(GUID_NULL, &pdgroup);

			LoadGroup(pdgroup, svgelement);

			(*pVal = pdgroup)->AddRef();

			return S_OK;
		}
	}

	return E_FAIL;
}
#endif