#include "stdafx.h"

#if 0
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "SVGExport.h"

void CSVGExport::SaveFilter(IPDAppearance* pdfilter, ISVGFilterElement* filterElement)
{
	filterElement->setAttribute(L"filterUnits", L"objectBoundingBox");

	CComPtr<IObjectMap> primitives;
	pdfilter->get_filterEffects(&primitives);

//	CComPtr<IDOMNodeList> filterChildNodes;
//	filterElement->get_childNodes(&filterChildNodes);

	long nprimitives;
	primitives->get_length(&nprimitives);

	for (int nprimitive = 0; nprimitive < nprimitives; nprimitive++)
	{
		CComPtr<IPDFilterPrimitive> primitive;
		primitives->item(nprimitive, (IUnknown**)&primitive);

		CComPtr<IPluginFilter> pluginFilter;
		primitive->get_pluginFilter(&pluginFilter);

		CComQIPtr<IObjectSerializable> serializable = pluginFilter;
		if (serializable)
		{
			CLSID clsid;
			serializable->GetClassID(&clsid);

			CComPtr<ISVGElement> feSVGElement;
			int npins = 0;

			if (clsid == CLSID_FEGaussianBlur)
			{
				CComQIPtr<IFEGaussianBlur> fe = pluginFilter;
				npins = 1;

				double devx, devy;
				fe->get_stdDeviationX(&devx);
				fe->get_stdDeviationY(&devy);

				CComPtr<ISVGFEGaussianBlurElement> element;
				m_svgdoc->createElement(L"feGaussianBlur", (IDOMElement**)&element);
				if (element)
				{
					if (TRUE)
					{
						WCHAR str[64];
						swprintf(str, L"%g %g", devx, devy);
						element->setAttribute(L"stdDeviation", str);
					}
					else
					{
						CComPtr<ISVGAnimatedNumber> stdDeviationX;
						CComPtr<ISVGAnimatedNumber> stdDeviationY;

						element->get_stdDeviationX(&stdDeviationX);
						element->get_stdDeviationY(&stdDeviationY);

						stdDeviationX->put_baseVal(devx);
						stdDeviationY->put_baseVal(devy);
					}

					feSVGElement = element;
				}
			}
			else if (clsid == CLSID_FEOffset)
			{
				CComQIPtr<IFEOffset> fe = pluginFilter;
				npins = 1;

				double dx;
				double dy;

				fe->get_dx(&dx);
				fe->get_dy(&dy);

				CComPtr<ISVGFEOffsetElement> element;
				m_svgdoc->createElement(L"feOffset", (IDOMElement**)&element);
				if (element)
				{
					WCHAR str[64];

					swprintf(str, L"%g", dx);
					element->setAttribute(L"dx", str);

					swprintf(str, L"%g", dy);
					element->setAttribute(L"dy", str);

					feSVGElement = element;
				}
			}
			else if (clsid == CLSID_FEComposite)
			{
				CComQIPtr<IFEComposite> fe = pluginFilter;
				npins = 2;

				long op;
				fe->get_op(&op);

				CComPtr<ISVGFECompositeElement> element;
				m_svgdoc->createElement(L"feComposite", (IDOMElement**)&element);
				if (element)
				{
					_bstr_t opstr;
					switch (op)
					{
					case 0: opstr = L"over"; break;
					case 1: opstr = L"in"; break;
					case 2: opstr = L"out"; break;
					case 3: opstr = L"atop"; break;
					case 4: opstr = L"xor"; break;
					case 5: opstr = L"arithmetic"; break;
					default:
						ATLASSERT(0);
					}

					element->setAttribute(L"operator", opstr);

					feSVGElement = element;
				}
			}

			if (feSVGElement)
			{
				for (int npin = 0; npin < npins; npin++)
				{
					CComPtr<IPDFilterPrimitive> in;
					primitive->GetInPin(npin, &in);

					if (in)
					{
						_bstr_t instr;

						long type;
						in->GetType(&type);

						if (type)
						{
							switch (type)
							{
							case IN_SOURCEGRAPHIC:		instr = L"SourceGraphic"; break;
							case IN_SOURCEALPHA:			instr = L"SourceAlpha"; break;
							case IN_BACKGROUNDGRAPHIC:	instr = L"BackgroundImage"; break;
							case IN_BACKGROUNDALPHA:	instr = L"BackgroundAlpha"; break;
							}
						}
						else
						{
							for (int index = nprimitive-1; index >= 0; index--)
							{
								CComPtr<IPDFilterPrimitive> primitive2;
								primitives->item(index, (IUnknown**)&primitive2);

								if (primitive2 == in)
								{
									break;
								}
							}
							ATLASSERT(index >= 0);

							WCHAR str[16];
							swprintf(str, L"fe%d", index);
							instr = str;
						}

						if (npin == 0)
							feSVGElement->setAttribute(L"in", instr);
						else if (npin == 1)
							feSVGElement->setAttribute(L"in2", instr);
						else
							ATLASSERT(0);
					}
				}

				WCHAR resultstr[16];
				swprintf(resultstr, L"fe%d", nprimitive);
				feSVGElement->setAttribute(L"result", resultstr);

				filterElement->appendChild(feSVGElement, NULL);
			}
		}
	}
}

void CSVGExport::SaveTransform(IPDObject* pdObject, ISVGElement* svgElement)
{
	CComQIPtr<IPDObjectTransformable> pdTransformable = pdObject;
	CComQIPtr<ISVGTransformable> svgTransformable = svgElement;

	if (pdTransformable && svgTransformable)
	{
		CComPtr<IPDMatrix> mat;
		pdTransformable->get_transformMatrix(&mat);

		double a; mat->get_a(&a);
		double b; mat->get_b(&b);
		double c; mat->get_c(&c);
		double d; mat->get_d(&d);
		double e; mat->get_e(&e);
		double f; mat->get_f(&f);

		if (	(a != 1.0) || (b != 0.0) ||
				(c != 0.0) || (d != 1.0) ||
				(e != 0.0) || (f != 0.0))
		{
			CComPtr<ISVGMatrix> svgmat;
			m_svgsvgelement->createSVGMatrix(&svgmat);
			svgmat->put_a(a);
			svgmat->put_b(b);
			svgmat->put_c(c);
			svgmat->put_d(d);
			svgmat->put_e(e);
			svgmat->put_f(f);

			CComPtr<ISVGTransform> transform;
			m_svgsvgelement->createSVGTransformFromMatrix(svgmat, &transform);

			CComPtr<ISVGAnimatedTransformList> atransformList;
			svgTransformable->get_transform(&atransformList);

			CComPtr<ISVGTransformList> transformList;
			atransformList->get_baseVal(&transformList);

			transformList->appendItem(transform, NULL);
		}
	}
}

void CSVGExport::SavePath(IPDPath* pdpath, ISVGPathElement* pathElement, ISVGPathSegList* seglist)
{
	long nsubpaths;
	pdpath->get_subPathCount(&nsubpaths);

	for (int nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		pdpath->getSubPath(nsubpath, &subpath);

		VARIANT_BOOL closed;
		subpath->get_closed(&closed);

		long npoints;
		subpath->get_pointCount(&npoints);

		BezierPoint bpt0;
		subpath->getPoint(0, &bpt0);

		BezierPoint _bpt0 = bpt0;

		CComPtr<ISVGPathSegMovetoAbs> moveto;
		pathElement->createSVGPathSegMovetoAbs(bpt0.x, bpt0.y, &moveto);
		seglist->appendItem(moveto, NULL);

		for (int i = 1; i < npoints; i++)
		{
			BezierPoint bpt;
			subpath->getPoint(i, &bpt);

			CComPtr<ISVGPathSegCurvetoCubicAbs> cubicto;
			pathElement->createSVGPathSegCurvetoCubicAbs(
				bpt.x, bpt.y,		// x,y
				bpt0.x2, bpt0.y2,	// x1,y1
				bpt.x1, bpt.y1,	// x2,y2
				&cubicto);
			seglist->appendItem(cubicto, NULL);

			bpt0 = bpt;
		}

		if (closed)
		{
			CComPtr<ISVGPathSegCurvetoCubicAbs> cubicto;
			pathElement->createSVGPathSegCurvetoCubicAbs(
				_bpt0.x, _bpt0.y,		// x,y
				bpt0.x2, bpt0.y2,	// x1,y1
				_bpt0.x1, _bpt0.y1,	// x2,y2
				&cubicto);
			seglist->appendItem(cubicto, NULL);

			CComPtr<ISVGPathSegClosePath> close;
			pathElement->createSVGPathSegClosePath(&close);
			seglist->appendItem(close, NULL);
		}
	}
}

void CSVGExport::SaveObjectFilter(IPDObject* pdobject, ISVGFilterElement* *pVal)
{
	CComPtr<ISVGFilterElement> filterElement;

	CComQIPtr<IPDObjectWithAppearance> withAppearance = pdobject;
	if (withAppearance)
	{
		CComPtr<IPDAppearance> pdfilter;
		withAppearance->get_appearance(&pdfilter);

		CComPtr<IObjectMap> primitives;
		pdfilter->get_filterEffects(&primitives);

		long nprimitives;
		primitives->get_length(&nprimitives);
		if (nprimitives > 0)
		{
			m_svgdoc->createElement(L"filter", (IDOMElement**)&filterElement);
			if (filterElement)
			{
				m_nUriRefs++;
				WCHAR strid[64];
				swprintf(strid, L"id%d", m_nUriRefs);

				filterElement->setAttribute(L"id", strid);
				SaveFilter(pdfilter, filterElement);
			}
		}
	}

	*pVal = filterElement;
	if (*pVal) (*pVal)->AddRef();
}

void CSVGExport::SetFilterURI(ISVGElement *element, ISVGFilterElement* filterElement)
{
	if (filterElement)
	{
		CComQIPtr<ISVGStylable> stylable = element;
		CComPtr<IDOMCSSStyleDeclaration> style;
		stylable->get_style(&style);

		BSTR bid;
		filterElement->getAttribute(L"id", &bid);

		WCHAR buf[64];
		swprintf(buf, L"url(#%s)", bid);
		style->setProperty(L"filter", buf, L"");

		SysFreeString(bid);
	}
}

void CSVGExport::SaveObjectFrame(ISVGElement* group, IPDObjectFrame* pdframe)
{
	CComPtr<ISVGFilterElement> filterElement;
	SaveObjectFilter(pdframe, &filterElement);
	if (filterElement) group->appendChild(filterElement, NULL);

	CComPtr<IPDPath> pdpath;
	pdframe->get_path(&pdpath);

	CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokefill = pdframe;

	CComPtr<IObjectMap> subobjects;
	strokefill->get_subObjects(&subobjects);

	long nsubobjects;
	subobjects->get_length(&nsubobjects);

	bool bSimple = true;

	CComQIPtr<IPDObjectFill> fill;
	CComQIPtr<IPDObjectStroke> stroke;

	for (int i = 0; i < nsubobjects; i++)
	{
		CComPtr<IPDObjectWithBrush> withBrush;
		subobjects->item(i, (IUnknown**)&withBrush);

		PDObjectType objectType;
		withBrush->get_objectType(&objectType);

		CComPtr<IPDBrush> brush;
		withBrush->get_brush(&brush);

		if (i == 0 && objectType == PATH_FILL) fill = withBrush;
		else if (i == 1 && objectType == PATH_STROKE) stroke = withBrush;
	}

	if (bSimple)
	{
		CComPtr<ISVGPathElement> pathElement;
		m_svgdoc->createElement(L"path", (IDOMElement**)&pathElement);

		SaveTransform(pdframe, pathElement);

		CComQIPtr<ISVGAnimatedPathData> pathdata = pathElement;

		CComPtr<ISVGPathSegList> seglist;
		pathdata->get_normalizedPathSegList(&seglist);

		SavePath(pdpath, pathElement, seglist);

		CComQIPtr<ISVGStylable> stylable = pathElement;
		CComPtr<IDOMCSSStyleDeclaration> style;
		stylable->get_style(&style);

		if (fill)
		{
		// Fill color
			CComPtr<IPDBrush> brush;
			fill->get_brush(&brush);

			CComPtr<IPDColor> color;
			brush->get_tintedRGBColor(&color);
			double red; color->getChannel(0, &red);
			double green; color->getChannel(1, &green);
			double blue; color->getChannel(2, &blue);

			WCHAR buf[64];
			swprintf(buf, L"#%2.2X%2.2X%2.2X", (int)red, (int)green, (int)blue);

			style->setProperty(L"fill", buf, L"");
		}

		if (stroke)
		{
		// Stroke color
			CComPtr<IPDBrush> brush;
			stroke->get_brush(&brush);

			CComPtr<IPDColor> color;
			brush->get_tintedRGBColor(&color);
			double red; color->getChannel(0, &red);
			double green; color->getChannel(1, &green);
			double blue; color->getChannel(2, &blue);

			WCHAR buf[64];

			swprintf(buf, L"#%2.2X%2.2X%2.2X", (int)red, (int)green, (int)blue);
			style->setProperty(L"stroke", buf, L"");

		// stroke weight
			CComQIPtr<IPDStrokeSettings> stroke2 = stroke;
			double strokeWeight;
			stroke2->get_strokeWeight(&strokeWeight);
			swprintf(buf, L"%g", strokeWeight);
			style->setProperty(L"stroke-width", buf, L"");
		}

		SetFilterURI(pathElement, filterElement);

		group->appendChild(pathElement, NULL);
	}
	else
	{
	}
}

void CSVGExport::SaveObjectGroup(ISVGElement* group, IPDObjectGroup* pdgroup)
{
	CComPtr<ISVGElement> g;
	m_svgdoc->createElement(L"g", (IDOMElement**)&g);

	SaveTransform(pdgroup, g);

	CComPtr<ISVGFilterElement> filterElement;
	SaveObjectFilter(pdgroup, &filterElement);
	if (filterElement) group->appendChild(filterElement, NULL);
	SetFilterURI(g, filterElement);

	// enable-background
	{
		CComQIPtr<ISVGStylable> stylable = g;
		CComPtr<IDOMCSSStyleDeclaration> style;
		stylable->get_style(&style);

		long enableBackground;
		pdgroup->get_enableBackground(&enableBackground);

		if (enableBackground == 1)
			style->setProperty(L"enable-background", L"new", L"");
	}

	CComPtr<IObjectMap> children;
	pdgroup->get_children(&children);
	
	long nchildren;
	children->get_length(&nchildren);

	for (long i = 0; i < nchildren; i++)
	{
		CComPtr<IPDObject> object;
		children->item(i, (IUnknown**)&object);

		PDObjectType objectType;
		object->get_objectType(&objectType);

		if (objectType == OBJECT_GROUP)
		{
			CComQIPtr<IPDObjectGroup> pdgroup2 = object;
			SaveObjectGroup(g, pdgroup2);
		}
		else if (objectType == OBJECT_FRAME)
		{
			CComQIPtr<IPDObjectFrame> frame = object;

			SaveObjectFrame(g, frame);
		}
	}

	group->appendChild(g, NULL);
}

HRESULT CSVGExport::Export(BSTR pathName, IPDSpread* spread)
{
	if (spread == NULL) return E_INVALIDARG;

	if (SUCCEEDED(m_svgdoc.CoCreateInstance(CLSID_SVGDocument)))
	{
		VARIANT_BOOL bloaded;
		m_svgdoc->loadXML(L"<?xml version=\"1.0\" ?><svg/>", &bloaded);

		m_svgdoc->get_documentElement((IDOMElement**)&m_svgsvgelement);

		CComPtr<IObjectMap> layergroups;
		spread->get_layergroups(&layergroups);

		m_nUriRefs = 0;

		long nlayergroups;
		layergroups->get_length(&nlayergroups);
		for (long nlayergroup = 0; nlayergroup < nlayergroups; nlayergroup++)
		{
			CComPtr<IPDObjectGroup> pdgroup;
			layergroups->item(nlayergroup, (IUnknown**)&pdgroup);

			SaveObjectGroup(m_svgsvgelement, pdgroup);
		}

		VARIANT_BOOL bsaved;
		m_svgdoc->save(pathName, &bsaved);

		if (bsaved)
			return S_OK;
	}

	return E_FAIL;
}
#endif