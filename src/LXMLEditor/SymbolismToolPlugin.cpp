#include "stdafx.h"
#include "LXMLEditor2.h"
#include "SymbolismToolPlugin.h"

#include "ESVGElementImpl.h"
#include "EXMLDocument.h"
#include "EXMLViewGroup.h"

namespace System
{
namespace LXmlEdit
{

double GetLineAngle(double x1, double y1, double x2, double y2);
double GetLineAngle(double distance, double x1, double y1, double x2, double y2);

//extern ILSVGElement* g_selectedSymbol;

/////////////////////////////////////////////////////////////////////////////
// CSymbolismToolPlugin

ErrorCode CSymbolismTool::OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging)
{
	ASSERT(0);
#if 0
	SVGPoint wpt(mouse->wptx, mouse->wpty);

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> domDocument;
	eDocument->get_DOMDocument(&domDocument);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	domDocument->get_documentElement((ILDOMElement**)&svgsvgElement);

	switch (m_nTool)
	{
	case ID_SVGTOOL_SYMBOL_SPRAYER:
		{
			if (static_cast<CEXMLDocument*>(eDocument.p)->g_selectedSymbol == NULL)
			{
				MessageBox(NULL/*TODO*/, "Please select a symbol from the Symbols palette first", "WebEditor", MB_OK);
				return Success;
			}

			CComQIPtr<ILDOMElement> gElement;

			// First check for existing symbolset
			CComPtr<IESelectedElement> selectedElement;
			viewGroup->GetActiveSelectedElement(&selectedElement);
			if (selectedElement)
			{
				CComPtr<IEElement> eElement;
				selectedElement->get_eElement(&eElement);

				CComPtr<ILDOMElement> domElement;
				eElement->get_domElement(&domElement);

				gElement = domElement;
				if (gElement)
				{
					VARIANT_BOOL bSymbolSet;
					gElement->hasAttribute(L"symbolSet", &bSymbolSet);
					if (bSymbolSet)
					{
						m_symbolSetGElement = eElement;
					}
				}
			}

		// Create new symbol set
			if (m_symbolSetGElement == NULL)
			{
				domDocument->createElementNS(L"http://www.w3.org/2000/svg", L"g", &gElement);

				gElement->setAttribute(L"symbolSet", L"yes");	// Extension

				CComPtr<ILDOMElement> documentElement;
				domDocument->get_documentElement(&documentElement);

				documentElement->appendChild(gElement, NULL);
			//	m_symbolSetGElement = NULL;	// TODO remove
				eDocument->GetEElementFromDOMElement(gElement, &m_symbolSetGElement);

				viewGroup->ActivateElement(m_symbolSetGElement, 0, NULL);
			}

			if (m_symbolSetGElement)
			{
				m_minX = wpt.X;
				m_minY = wpt.Y;
				m_maxX = wpt.X+1;
				m_maxY = wpt.Y+1;

				m_counter = 0;

				m_dragging = 1;
			}
		}
		break;

	case ID_SVGTOOL_SYMBOL_SIZER:
		{
			CComPtr<IESelectedElement> selectedElement;
			viewGroup->GetActiveSelectedElement(&selectedElement);

			if (selectedElement)
			{
				CComPtr<IEElement> eElement;
				selectedElement->get_eElement(&eElement);

				m_symbolSetGElement = eElement;	// TODO check that it's a symbolset

				CComPtr<ILDOMElement> element;
				eElement->get_domElement(&element);

				CComPtr<ILDOMNode> node;
				element->get_firstChild(&node);
				while (node)
				{
					CComQIPtr<ILSVGUseElement> useElement = node;
					if (useElement)
					{
						CSymbolInstance* pInstance = new CSymbolInstance;
						pInstance->m_element = useElement;

						CComPtr<ILSVGRect> _bbox;
						window->svgGetRBBox(pInstance->m_element, &_bbox);
						SVGRect bbox = _bbox;

						m_instances.Add(pInstance);

						pInstance->m_position.X = bbox.X + bbox.Width/2;
						pInstance->m_position.Y = bbox.Y + bbox.Height/2;

						svgsvgElement->createSVGMatrix(&pInstance->m_matrix);
					}

					CComPtr<ILDOMNode> nextSibling;
					node->get_nextSibling(&nextSibling);
					node = nextSibling;
				}

				m_counter = 0;
				m_dragging = 1;
			}
		}
	}

#if 0
	if (mouse->nFlags & MK_ALT)	// Size brush
	{
		CComQIPtr<IPDBrushSettings> brushSettings = gIApp;
		brushSettings->get_brushWidth(&m_brushSize.X);
		brushSettings->get_brushHeight(&m_brushSize.Y);

		m_hit = 2;
		m_dragging = 1;
	}
	else
	{
#if 0
		if (m_targetObjects.GetSize() > 0)
		{
			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CPDObjectSelected* pObject = m_targetObjects[i];
				if (pObject->m_wrapPath)
				{
					pObject->m_wrapPath->SetPolyPointsFromSegList();
					m_dragging = 1;
				}

				PDObjectType objectType;
				pObject->m_object->get_objectType(&objectType);
				if (objectType == OBJECT_FRAME)
				{
					CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;

					pFrame->m_path->SetPolyPointsFromSegList();
					m_dragging = 1;
				}
			}

			if (m_dragging)
			{
				m_hit = 1;
			}
		}
#endif
	}
#endif

	*pdragging = m_dragging;
#endif

	return Success;
}

ErrorCode CSymbolismTool::OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	LDraw::Point pt(mouse->ptx, mouse->pty);
	SVGPoint wpt(mouse->wptx, mouse->wpty);
//	SVGPoint wstartpt = m_wstartpt;

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<IHTMLPaintSite> paintSite;
	view->GetPaintSite(&paintSite);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> domDocument;
	eDocument->get_DOMDocument(&domDocument);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	domDocument->get_documentElement((ILDOMElement**)&svgsvgElement);

	double m_brushRadius = 30;
	double m_brushRadiusSquared = m_brushRadius*m_brushRadius;

	if (m_dragging)
	{
		switch (m_nTool)
		{
		case ID_SVGTOOL_SYMBOL_SPRAYER:
			{
				ATLASSERT(m_symbolSetGElement);

				if (!(mouse->nFlags & MK_ALT))	// Add symbols
				{
					if ((m_counter % 10) == 0)
					{
						CSymbolInstance* pInstance = new CSymbolInstance;
						m_instances.Add(pInstance);

						pInstance->m_position.X = wpt.X + (m_minX+(m_maxX-m_minX)/2-wpt.X)/(m_maxX-m_minX)/2*m_brushRadius;
						pInstance->m_position.Y = wpt.Y + (m_minY+(m_maxY-m_minY)/2-wpt.Y)/(m_maxY-m_minY)/2*m_brushRadius;

						//CComPtr<ILSVGMatrix> mat0;
						svgsvgElement->createSVGMatrix(&pInstance->m_matrix);
					}

					m_counter++;

					for (int i = 0; i < m_instances.GetSize(); i++)
					{
						CSymbolInstance* pInstance = m_instances[i];
						double dx = (pInstance->m_position.X-wpt.X);
						double dy = (pInstance->m_position.Y-wpt.Y);

						double distanceSquared = dx*dx+dy*dy;
						double distance = sqrt(distanceSquared);

						double angle = GetLineAngle(distance, wpt.X, wpt.Y, pInstance->m_position.X, pInstance->m_position.Y);

						distance += m_brushRadius/distance;

						pInstance->m_position.X = wpt.X + cos(angle)*distance;
						pInstance->m_position.Y = wpt.Y + sin(angle)*distance;

						m_minX = min(m_minX, pInstance->m_position.X);
						m_minY = min(m_minY, pInstance->m_position.Y);
						m_maxX = max(m_maxX, pInstance->m_position.X);
						m_maxY = max(m_maxY, pInstance->m_position.Y);
					}
				}
				else	// Remove symbols
				{
				}

				paintSite->InvalidateRect(NULL);
			}
			break;

		case ID_SVGTOOL_SYMBOL_SIZER:
			{
				for (int i = 0; i < m_instances.GetSize(); i++)
				{
					CSymbolInstance* pInstance = m_instances[i];

					CComPtr<ILSVGRect> _bbox;
					window->svgGetRBBox(pInstance->m_element, &_bbox);
					SVGRect bbox = _bbox;

					PointD pos;
					pos.X = bbox.X + bbox.Width/2;
					pos.Y = bbox.Y + bbox.Height/2;

					double dx = wpt.X-pos.X;
					double dy = wpt.Y-pos.Y;

					double distance = sqrt(dx*dx + dy*dy);

					double d = distance/30.0;
					double maxscale = 1.05;

					if (d < 1)
					{
						double scale = 1 + (1-d) * (maxscale-1);

						CComPtr<ILSVGMatrix> mat0;// = pInstance->m_matrix;
						svgsvgElement->createSVGMatrix(&mat0);

						CComPtr<ILSVGMatrix> mat1;
						mat0->translate(bbox.Width/2, bbox.Height/2, &mat1);

						CComPtr<ILSVGMatrix> mat2;
						mat1->scaleNonUniform(scale, scale, &mat2);

						CComPtr<ILSVGMatrix> mat3;
						mat2->translate(-bbox.Width/2, -bbox.Height/2, &mat3);

						CComPtr<ILSVGMatrix> mat4;
						pInstance->m_matrix->multiply(mat3, &mat4);

						pInstance->m_matrix = mat4;
					}
				}

				paintSite->InvalidateRect(NULL);
			}
			break;
		}
	}
#if 0

	if (m_dragging)
	{
		if (m_hit == 2)	// Size brush
		{
			CComPtr<ILHTMLActiveView> oleActiveView;
			window->GetOleView(&oleActiveView);

			CComQIPtr<IOleWindow> oleView = oleActiveView;

			long innerWidth;
			long innerHeight;
			window->get_innerWidth(&innerWidth);
			window->get_innerHeight(&innerHeight);

			CRect m_areaRect;
			m_areaRect.left = 0;
			m_areaRect.top = 0;
			m_areaRect.right = innerWidth;
			m_areaRect.bottom = innerHeight;

			UI::Control* hWnd;
			oleView->GetWindow(&hWnd);

			HDC hDC = ::GetDC(hWnd);
			IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

			int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

			if (m_bBrushSizeVisible)
			{
				DrawBrushOutline(view, hDC, m_startpt);
				m_bBrushSizeVisible = false;
			}

			CComQIPtr<IPDBrushSettings> brushSettings;// = gIApp;

			double brushAngle;
			brushSettings->get_brushAngle(&brushAngle);

			CComPtr<ILSVGMatrix> mat;
			mat.CoCreateInstance(CLSID_LSVGMatrix);

			CComPtr<ILSVGMatrix> imat;
			mat->rotate(-brushAngle, &imat);

		//	double brushWidth;
		//	double brushHeight;
		//	brushSettings->get_brushWidth(&brushWidth);
		//	brushSettings->get_brushHeight(&brushHeight);

			SVGPoint xstartpt = m_wstartpt.matrixTransform(imat);
			SVGPoint xpt = wpt.matrixTransform(imat);

			double brushWidth = m_brushSize.X + (xpt.X-xstartpt.X)*2;
			double brushHeight = m_brushSize.Y + (xpt.Y-xstartpt.Y)*2;

			if (mouse->nFlags & MK_SHIFT)
			{
				brushWidth = max(brushWidth, brushHeight);
				brushHeight = brushWidth;
			}

			brushSettings->put_brushWidth(brushWidth);
			brushSettings->put_brushHeight(brushHeight);

			DrawBrushOutline(view, hDC, m_startpt);
			m_bBrushSizeVisible = true;

			SetROP2(hDC, oldR2);
			::ReleaseDC(hWnd, hDC);
		}
		else
		{
	#if 0
			CComQIPtr<IPDBrushSettings> brushSettings;// = gIApp;

			CComPtr<IPDMatrix> brushmat;
			brushSettings->getBrushMatrix(&brushmat);

			CComPtr<IPDMatrix> mat0;
			brushmat->translate(wpt.x, wpt.y, &mat0);

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CPDObjectSelected* pObject = m_targetObjects[i];
				CComQIPtr<IPDObject> object = pObject->m_object;

				if (object)
				{
					PDObjectType objectType;
					pObject->m_object->get_objectType(&objectType);

					if (objectType == OBJECT_FRAME)
					{
						CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
						CPathSelection* pPath = pFrame->m_path;

						CComPtr<IPDMatrix> ctm;		object->getScreenCTM(&ctm);
						CComPtr<IPDMatrix> ictm;	ctm->inverse(&ictm);

						CComPtr<IPDMatrix> mat;
						mat0->multiply(ictm, &mat);

						CComPtr<IPDMatrix> imat;
						mat->inverse(&imat);

						for (int nsubpath = 0; nsubpath < pPath->m_flatSubPaths.GetSize(); nsubpath++)
						{
							CFlatSubPath* subpath = pPath->m_flatSubPaths[nsubpath];

							int pointsIndex = 0;

							for (int nseg = 0; nseg < subpath->m_flatSegments.GetSize(); nseg++)
							{
								CFlatSegment& segment = subpath->m_flatSegments[nseg];

								int numpoints = segment.m_pointCount;
								DblPOINT* points = subpath->m_flatPoints.GetData() + pointsIndex;
								pointsIndex += numpoints;

								if (m_activeTool == ID_TOOL_TWIRL)
								{
									double dangle = 1;

									for (int i = 0; i < numpoints; i++)
									{
										PointD xpt;
										imat->transformPoint((PointD*)&points[i], &xpt);

										double dx = xpt.x-0;
										double dy = xpt.y-0;
										double _distance = dx*dx + dy*dy;

										if (_distance < 1.0)
										{
											double distance = sqrt(_distance);

											if (distance == 0.0) distance = 0.0001;

											double angle = acos(dx/distance);
											if (dy < 0) angle = M_PI*2 - angle;

											double addangle;
											addangle = ((1-distance)/1)*dangle;

											angle += addangle;

											PointD np;
											np.x = cos(angle)*distance;
											np.y = sin(angle)*distance;

											mat->transformPoint(&np, (PointD*)&points[i]);

											segment.m_bRecentAltered = true;
											segment.m_bAltered = true;
										}
										else
										{
										}
									}
								}
								else if (m_activeTool == ID_TOOL_BULGE)
								{
									double dstrength = 0.7;

									for (int i = 0; i < numpoints; i++)
									{
										PointD xpt;
										imat->transformPoint((PointD*)&points[i], &xpt);

										double dx = xpt.x-0;
										double dy = xpt.y-0;
										double _distance = dx*dx + dy*dy;

										if (_distance < 1.0)
										{
											double distance = sqrt(_distance);
											if (distance == 0.0) distance = 0.0001;

											double newdistance = pow(distance/1, dstrength)*1;
											ATLASSERT((newdistance >= 0) && (newdistance <= 1));

											PointD np;
											np.x = (dx * newdistance) / distance;
											np.y = (dy * newdistance) / distance;

											mat->transformPoint(&np, (PointD*)&points[i]);

											segment.m_bRecentAltered = true;
											segment.m_bAltered = true;
										}
										else
										{
										}
									}
								}
							}
						}

						pPath->MoreFlatDetail();
					}
				}
			}

			/*
			VARIANT_BOOL showBrushSize;
			brushSettings->get_showBrushSize(&showBrushSize);
			if (showBrushSize)
			{
				HDC hDC = GetDC();
				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
				DrawBrushOutline(hDC, m_point);
				SetROP2(hDC, oldR2);
				ReleaseDC(hDC);

				m_bBrushSizeVisible = true;
			}
			*/
			m_bBrushSizeVisible = true;

			InvalidateRect(&m_areaRect);	// TODO ?? remove
	#endif
		}
	}
	else
	{
		CComPtr<ILHTMLActiveView> oleActiveView;
		window->GetOleView(&oleActiveView);

		CComQIPtr<IOleWindow> oleView = oleActiveView;

		long innerWidth;
		long innerHeight;
		window->get_innerWidth(&innerWidth);
		window->get_innerHeight(&innerHeight);

		CRect m_areaRect;
		m_areaRect.left = 0;
		m_areaRect.top = 0;
		m_areaRect.right = innerWidth;
		m_areaRect.bottom = innerHeight;

		UI::Control* hWnd;
		oleView->GetWindow(&hWnd);

		HDC hDC = ::GetDC(hWnd);
		IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		if (m_bBrushSizeVisible)
		{
			DrawBrushOutline(view, hDC, m_oldpt);
			m_bBrushSizeVisible = false;
		}

		if (TRUE)
		{
			CComQIPtr<IPDBrushSettings> brushSettings;// = gIApp;

			VARIANT_BOOL showBrushSize;
			brushSettings->get_showBrushSize(&showBrushSize);
			if (showBrushSize)
			{
				DrawBrushOutline(view, hDC, pt);
				m_bBrushSizeVisible = true;
			}
		}

		SetROP2(hDC, oldR2);
		ReleaseDC(hWnd, hDC);
	}

	m_oldpt = pt;
	m_woldpt = wpt;
#endif
#endif

	return Success;
}

ErrorCode CSymbolismTool::OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	if (m_dragging)
	{
		CComPtr<IEXMLViewGroup> viewGroup;
		view->GetViewGroup(&viewGroup);

		CComPtr<IEXMLDocument> eDocument;
		viewGroup->get_eXMLDocument(&eDocument);

		CComPtr<ILDOMDocument> domDocument;
		eDocument->get_DOMDocument(&domDocument);

		if (TRUE)
		{
			CComPtr<ILDOMElement> symbol = static_cast<CEXMLDocument*>(eDocument.p)->g_selectedSymbol;

			CComQIPtr<ILSVGFitToViewBox> viewBox = symbol;

			CComPtr<ILSVGAnimatedRect> asvgrect;
			viewBox->get_viewBox(&asvgrect);

			CComPtr<ILSVGRect> svgrect;
			asvgrect->get_baseVal(&svgrect);
			SVGRect rect = svgrect;

			for (int i = 0; i < m_instances.GetSize(); i++)
			{
				CSymbolInstance* pInstance = m_instances[i];

				CComPtr<ILDOMElement> symbolsetElement;
				m_symbolSetGElement->get_domElement(&symbolsetElement);

				CComBSTR id;
				symbol->getAttribute(L"id", &id);

				_bstr_t uri = _bstr_t(L"#") + (BSTR)id;

				CComPtr<ILSVGUseElement> useElement;
				domDocument->createElementNS(L"http://www.w3.org/2000/svg", L"use", (ILDOMElement**)&useElement);
				if (useElement)
				{
					CComQIPtr<ILSVGURIReference> uriReference = useElement;

					CComPtr<ILSVGAnimatedString> a = uriReference->get_href();
					a->put_baseVal(uri);

					// x
					{
						CComQIPtr<ILSVGAnimatedLength> alength = useElement->get_x();
						CComPtr<ILSVGLength> length = alength->get_baseVal();

						length->put_value(pInstance->m_position.X-15);
					}

					// y
					{
						CComQIPtr<ILSVGAnimatedLength> alength = useElement->get_y();
						CComPtr<ILSVGLength> length = alength->get_baseVal();

						length->put_value(pInstance->m_position.Y-15);
					}

					// width
					{
						CComQIPtr<ILSVGAnimatedLength> alength = useElement->get_width();
						CComPtr<ILSVGLength> length = alength->get_baseVal();
						
						length->put_value(rect.Width);
					}

					// height
					{
						CComQIPtr<ILSVGAnimatedLength> alength = useElement->get_height();
						CComPtr<ILSVGLength> length = alength->get_baseVal();
						
						length->put_value(rect.Height);
					}

					symbolsetElement->appendChild(useElement, NULL);
				}

				delete pInstance;
			}
			m_instances.RemoveAll();
		}

#if 0	// Have this
		m_symbolSetGElement = NULL;
#endif
		m_instances.RemoveAll();

		m_dragging = 0;
	}
#endif
	return Success;
}

ErrorCode CSymbolismTool::OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{

	return Success_False;
}

ErrorCode CSymbolismTool::OnActivate(ILXMLEditorApp* app)
{
	return Success;
}

ErrorCode CSymbolismTool::OnDeactivate(ILXMLEditorApp* app)
{
	// TODO: Add your implementation code here

	return Success;
}

Web::Element* GetOwnerLayer(Web::Element* element);
LDraw::Color GetLayerColor(Web::Element* element);

ErrorCode CSymbolismTool::Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, UI::Graphics* pGraphics)
{
	if (/*m_dragging ||*/ m_symbolSetGElement)
	{
		CEXMLViewGroup* viewGroup = view->GetViewGroup();
		CEXMLDocument* eDocument = viewGroup->get_eXMLDocument();
		Web::Document* domDocument = eDocument->get_DOMDocument();
		Web::Element* domElement = m_symbolSetGElement->get_domElement();
		Web::SVGElement* svgElement = dynamic_cast<Web::SVGElement*>(domElement);
		Web::SVGSVGElement* svgsvgElement = svgElement->get_ownerSVGElement();
		Web::SVGMatrix* matrix = new Web::SVGMatrix;
		Web::Element* layer = GetOwnerLayer(domElement);
		LDraw::Color layerColor = GetLayerColor(layer);
		Element* eElement = eDocument->GetEElementFromDOMElement(eDocument->g_selectedSymbol);
		IESVGDrawOutline* drawOutline = dynamic_cast<IESVGDrawOutline*>(eElement);

		for (int i = 0; i < m_instances.GetSize(); i++)
		{
			CSymbolInstance* pInstance = m_instances[i];

			pGraphics->TranslateTransform((float)pInstance->m_position.X-15, (float)pInstance->m_position.Y-15);

		//	CComPtr<ILSVGMatrix> matrix;
		//	svgsvgElement->createSVGMatrix(&matrix);

			drawOutline->DrawOutline(pGraphics, layerColor, pInstance->m_matrix);

			pGraphics->TranslateTransform(-(float)(pInstance->m_position.X-15), -(float)(pInstance->m_position.Y-15));

			/*
			graphics.DrawRectangle(&pen,
				LDraw::RectF((float)pInstance->m_position.X-15, (float)pInstance->m_position.Y-15, 30, 30));
				*/
		}
	}

	return Success;
}

/////////////////////////////////////////////////////////////////////////////
// CLiquifyToolPlugin

//ErrorCode CSymbolismToolPlugin::Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
//{
ErrorCode CSymbolismToolPlugin::SetSite(ILXMLEditorPluginClass* self)
{
	ASSERT(0);
#if 0
	m_spAddinSite = self;

	if (m_spAddinSite)
	{
		CComPtr<ILXMLEditorApp> app;
		self->GetApp(&app);
		CComQIPtr<ILXAddin> lxapp = app;

		CComQIPtr<ILXAddinSite> site;
		lxapp->GetSite(&site);

		ASSERT(0);
#if 0
		CComPtr<IUIManager> uiManager;
		site->GetUIManager((IUnknown**)&uiManager);

		app->AddTool(self, this, NULL, ID_SVGTOOL_SYMBOL_SPRAYER, L"Symbol Sprayer", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_SYMBOL_SHIFTER, L"Symbol Shifter", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_SYMBOL_SCRUNCHER, L"Symbol Scruncher", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_SYMBOL_SIZER, L"Symbol Sizer", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_SYMBOL_SPINNER, L"Symbol Spinner", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_SYMBOL_SCREENER, L"Symbol Screener", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_SYMBOL_STYLER, L"Symbol Styler", L"tool_ellipse.bmp");

		uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_SYMBOLISMTOOLS);
#endif
	}
#endif
	return Success;
}

ErrorCode CSymbolismToolPlugin::FindTool(/*[in]*/ long id, System::Object* *pdlg, /*[out,retval]*/ ISVGTool** pVal)
{
	*pVal = NULL;

	ASSERT(0);
#if 0
	<CSymbolismTool>* pTool;
	CComObject<CSymbolismTool>::CreateInstance(&pTool);
	if (pTool)
	{
		pTool->AddRef();
		pTool->m_nTool = id;

		*pVal = pTool;
	}
#endif

	return Success;
}

ErrorCode CSymbolismTool::Options(UI::Control* hParent)
{
	// TODO: Add your implementation code here

	return Success;
}

}	// LXmlEdit
}
