#include "stdafx.h"
#include "LXMLEditor2.h"
#include "LiquifyToolPlugin.h"

//#include "..\LXUI\Bezier.h"
#include "BrushDimensionsDlg.h"
#include "EElementImpl.h"
#include "ESVGPathElement.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CLiquifyTool

CLiquifyTool::CLiquifyTool()
{
	m_nTool = 0;

	m_dragging = 0;
	m_hit = 0;

	m_bBrushSizeVisible = false;

	m_twirlRate = 18;	// degrees
}

CLiquifyTool::~CLiquifyTool()
{
}

/*
LRESULT CLiquifyTool::CTimerWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	m_lt->OnTimer(m_view);
	return 0;
}
*/

void CLiquifyTool::DrawBrushOutline(ISVGView* view, MSWindows::HDC hDC, LDraw::PointD point)
{
		ASSERT(0);
#if 0
	CComQIPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILSVGMatrix> viewMatrix;
	{
		CComPtr<IEElement> rootEElement;
		view->GetEElement(&rootEElement);

		CComPtr<ILDOMElement> rootElement;
		rootEElement->get_domElement(&rootElement);

		CComQIPtr<ILSVGSVGElement> svgsvgElement = rootElement;

		double translateX;
		double translateY;
		window->get_currentTranslateX(&translateX);
		window->get_currentTranslateY(&translateY);

		double magnify;
		window->get_magnify(&magnify);

		CComPtr<ILSVGMatrix> mat1;
		svgsvgElement->createSVGMatrix(&mat1);
		CComPtr<ILSVGMatrix> mat;
		mat1->scaleNonUniform(magnify, magnify, &mat);
		mat->translate(translateX, translateY, &viewMatrix);
	}

	CComQIPtr<IPDBrushSettings> brushSettings = m_pAddin;

	CComPtr<ILSVGMatrix> brushmat;
	brushSettings->getBrushMatrix(&brushmat);

/*
	CComPtr<ILSVGMatrix> mat0;
	brushmat->translate(point.X, point.Y, &mat0);

	CComPtr<ILSVGMatrix> mat;
	viewMatrix->multiply(mat0, &mat);
*/
	CComPtr<ILSVGMatrix> mat0;
	brushmat->translate(point.X, point.Y, &mat0);

	CComPtr<ILSVGMatrix> mat;
	mat0->multiply(viewMatrix, &mat);

	SVGPoint bpoints[13];
	SetPointsEllipse(-1, -1, 1, 1, bpoints);

	POINT points[13];

	for (int i = 0; i < 13; i++)
	{
		SVGPoint xpt = bpoints[i].matrixTransform(mat);

		points[i].x = xpt.X+0.5;
		points[i].y = xpt.Y+0.5;
	}

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

	PolyBezier(hDC, points, 13);

	SelectObject(hDC, hOldBrush);
#endif
}

void CLiquifyTool::EraseBrushOutline(ISVGView* view)
{
	if (m_bBrushSizeVisible)
	{
#if 0
		HDC hDC = GetDC();
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		DrawBrushOutline(hDC, m_oldpt);
		m_bBrushSizeVisible = false;

		SetROP2(hDC, oldR2);
		ReleaseDC(hDC);
#endif
	}
}

void CLiquifyTool::AddTargetElement(CEXMLDocument* eDocument, Element* eElement)
{
	CESVGPathElement* ePathElement = dynamic_cast<CESVGPathElement*>(eElement);
	if (ePathElement)
	{
		CElement* pElement = new CElement;
		pElement->m_eElement = eElement;

#if 0
		CComPtr<IESVGPath> path;
		ePathElement->GetPath(&path);

		CComPtr<ILSVGPathSegList> seglist;
		path->GetPathSegList(&seglist);

		{
			double oldx, oldy;

			long numberOfItems;
			seglist->get_numberOfItems(&numberOfItems);

			for (unsigned long i = 0; i < numberOfItems; i++)
			{
				CComPtr<ILSVGPathSeg> seg;
				seglist->getItem(i, &seg);

				LSVGPathSegType segType;
				seg->get_pathSegType(&segType);

				if (segType == PATHSEG_MOVETO_ABS)
				{
					CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

					movetoabs->get_x(&oldx);
					movetoabs->get_y(&oldy);

					pElement->m_points.Add(PointD(oldx, oldy));
				}
				else if (segType == PATHSEG_LINETO_ABS)
				{
					CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

					linetoabs->get_x(&oldx);
					linetoabs->get_y(&oldy);

					pElement->m_points.Add(PointD(oldx, oldy));
					pElement->m_points.Add(PointD(oldx, oldy));
					pElement->m_points.Add(PointD(oldx, oldy));
				}
				else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
				{
					CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;

					double x, y, x1, y1, x2, y2;
					cubictoabs->get_x(&x);
					cubictoabs->get_y(&y);
					cubictoabs->get_x1(&x1);
					cubictoabs->get_y1(&y1);
					cubictoabs->get_x2(&x2);
					cubictoabs->get_y2(&y2);

					pElement->m_points.Add(PointD(x1, y1));
					pElement->m_points.Add(PointD(x2, y2));
					pElement->m_points.Add(PointD(x, y));

					oldx = x;
					oldy = y;
				}
			}
		}

		m_targetObjects.Add(pElement);
#endif
	}

	ASSERT(0);
#if 0
// Recursivaly add child elements
	LXML::Element* element = eElement->get_domElement();

	LXML::Node* node = element->get_firstChild();
	while (node)
	{
		LXML::Element* element = node;
		if (element)
		{
			CComPtr<IEElement> eElement;
			eDocument->GetEElementFromDOMElement(element, &eElement);

			AddTargetElement(eDocument, eElement);
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
}

ErrorCode CLiquifyTool::OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging)
{
	ASSERT(0);
#if 0
	LDraw::PointD wpt(mouse->wptx, mouse->wpty);
	m_woldpt = wpt;

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	if (!m_dragging)
	{
		if (mouse->nFlags & MK_ALT)	// Size brush
		{
			CComQIPtr<IPDBrushSettings> brushSettings = m_pAddin;
			brushSettings->get_brushWidth(&m_brushSize.X);
			brushSettings->get_brushHeight(&m_brushSize.Y);

			m_hit = 2;
			m_dragging = 1;
		}
		else
		{
			long nselected;
			viewGroup->GetSelectedCount(&nselected);

			if (nselected > 0)
			{
				for (int i = 0; i < nselected; i++)
				{
					CComPtr<IESelectedElement> selectedElement;
					viewGroup->GetSelectedElementN(i, &selectedElement);

					CComPtr<IEElement> eElement;
					selectedElement->get_eElement(&eElement);

					AddTargetElement(eDocument, eElement);

					/*
					PDObjectType objectType;
					pObject->m_object->get_objectType(&objectType);
					if (objectType == OBJECT_FRAME)
					{
						CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;

						pFrame->m_path->SetPolyPointsFromSegList();
						m_dragging = 1;
					}
					*/
				}

				if (m_targetObjects.GetSize() > 0)
				{
					switch (m_nTool)
					{
					case ID_SVGTOOL_TWIRL:
					case ID_SVGTOOL_PUCKER:
					case ID_SVGTOOL_BLOAT:
						{
							m_timerWnd.Create(NULL, CRect(0,0,0,0), NULL, WS_DISABLED);
							ASSERT(m_timerWnd.m_hWnd);
							m_timerWnd.m_view = view;
							m_timerWnd.m_lt = this;
							m_timerWnd.SetTimer(1, 10);
						}
						break;
					}

					m_dragging = 1;
				}

				if (m_dragging)
				{
					m_hit = 1;
				}
			}
		}
	}

	*pdragging = m_dragging;
#endif
	return Success;
}

void CLiquifyTool::Process(ISVGView* view, LDraw::PointD wpt)
{
	ASSERT(0);
#if 0
	CComQIPtr<IPDBrushSettings> brushSettings = m_pAddin;

	CComPtr<ILSVGMatrix> brushmat;
	brushSettings->getBrushMatrix(&brushmat);

	CComPtr<ILSVGMatrix> mat0;
	brushmat->translate(wpt.X, wpt.Y, &mat0);

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CElement* pObject = m_targetObjects[i];
		//CComQIPtr<IPDObject> object = pObject->m_object;

		CComQIPtr<IESVGPathElement> pathElement = pObject->m_eElement;

		CComPtr<ILDOMElement> domElement;
		pathElement->get_domElement(&domElement);

		CComQIPtr<ILSVGTransformable> transformable = domElement;

		CComPtr<ILSVGMatrix> ctm;
		transformable->getScreenCTM(&ctm);

		CComPtr<ILSVGMatrix> ictm;
		ctm->inverse(&ictm);

		CComPtr<ILSVGMatrix> mat;
		mat0->multiply(ictm, &mat);

		CComPtr<ILSVGMatrix> imat;
		mat->inverse(&imat);

		int numpoints = pObject->m_points.GetSize();
		SVGPoint* points = (SVGPoint*)pObject->m_points.GetData();

		{
			switch (m_nTool)
			{
			case ID_SVGTOOL_WARP:
				{
					SVGPoint xwpt = wpt.matrixTransform(imat);
					SVGPoint xwoldpt = m_woldpt.matrixTransform(imat);

					SVGPoint mouseDelta = SVGPoint(xwpt.X-xwoldpt.X, xwpt.Y-xwoldpt.Y);

					//	SVGPoint mouseDelta = SVGPoint(wpt.X-m_woldpt.X, wpt.Y-m_woldpt.Y).matrixTransform(imat);
					//double mouseDeltaY = wpt.Y-m_woldpt.Y;

					ATLTRACE("delta: %g %g\n", mouseDelta.X, mouseDelta.Y);

					for (int i = 0; i < numpoints; i++)
					{
					// Transform into brush space
						PointD xpt = points[i].matrixTransform(imat);

						double dx = xpt.X;
						double dy = xpt.Y;
						double _distance = dx*dx + dy*dy;

						if (_distance < 1.0)
						{
							double distance = sqrt(_distance);

							SVGPoint np;
							np.X = xpt.X + (1- distance)*mouseDelta.X;
							np.Y = xpt.Y + (1- distance)*mouseDelta.Y;
							
						// Transform back
							points[i] = np.matrixTransform(mat);
						}
					}
				}
				break;

			case ID_SVGTOOL_TWIRL:
				{
					double dangle = gmRadians(m_twirlRate);

					for (int i = 0; i < numpoints; i++)
					{
						PointD xpt = points[i].matrixTransform(imat);

						double dx = xpt.X-0;
						double dy = xpt.Y-0;
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

							SVGPoint np;
							np.X = cos(angle)*distance;
							np.Y = sin(angle)*distance;
							
						//	mat->transformPoint(&np, (PointD*)&points[i]);
							points[i] = np.matrixTransform(mat);

#if 0
							segment.m_bRecentAltered = true;
							segment.m_bAltered = true;
#endif
						}
						else
						{
						}
					}
				}
				break;

			case ID_SVGTOOL_PUCKER:
			case ID_SVGTOOL_BLOAT:
				{
					double dstrength;

					if (m_nTool == ID_SVGTOOL_PUCKER)
						dstrength = 1.8;
					else if (m_nTool == ID_SVGTOOL_BLOAT)
						dstrength = 1/1.8;
					
					for (int i = 0; i < numpoints; i++)
					{
					//	PointD xpt;
					//	imat->transformPoint((PointD*)&points[i], &xpt);
						PointD xpt = points[i].matrixTransform(imat);

						double dx = xpt.X-0;
						double dy = xpt.Y-0;
						double _distance = dx*dx + dy*dy;
						
						if (_distance < 1.0)
						{
							double distance = sqrt(_distance);
							if (distance == 0.0) distance = 0.0001;
							
							double newdistance = pow(distance/1, dstrength)*1;
							ASSERT((newdistance >= 0) && (newdistance <= 1));
							
							SVGPoint np;
							np.X = (dx * newdistance) / distance;
							np.Y = (dy * newdistance) / distance;
							
							points[i] = np.matrixTransform(mat);

#if 0
							segment.m_bRecentAltered = true;
							segment.m_bAltered = true;
#endif
						}
						else
						{
						}
					}
				}
				break;
			}
		}
	}
#endif
}

void CLiquifyTool::OnTimer(ISVGView* view)
{
	ASSERT(0);
#if 0
	SVGPoint wpt = m_woldpt;

	Process(view, wpt);

	CComPtr<IHTMLPaintSite> paintSite;
	view->GetPaintSite(&paintSite);

	paintSite->InvalidateRect(NULL);
#endif
}

ErrorCode CLiquifyTool::OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
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

	if (m_dragging)
	{
		CComPtr<IHTMLPaintSite> paintSite;
		view->GetPaintSite(&paintSite);

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
				DrawBrushOutline(view, hDC, m_wstartpt);
				m_bBrushSizeVisible = false;
			}

			CComQIPtr<IPDBrushSettings> brushSettings = m_pAddin;

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

			DrawBrushOutline(view, hDC, m_wstartpt);
			m_bBrushSizeVisible = true;

			SetROP2(hDC, oldR2);
			::ReleaseDC(hWnd, hDC);
		}
		else
		{
			switch (m_nTool)
			{
			case ID_SVGTOOL_WARP:
				{
					Process(view, wpt);

					CComPtr<IHTMLPaintSite> paintSite;
					view->GetPaintSite(&paintSite);

					paintSite->InvalidateRect(NULL);
				}
				break;
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
		//	m_bBrushSizeVisible = true;

			//InvalidateRect(&m_areaRect);	// TODO ?? remove
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
			DrawBrushOutline(view, hDC, m_woldpt);
			m_bBrushSizeVisible = false;
		}

		if (TRUE)
		{
			CComQIPtr<IPDBrushSettings> brushSettings = m_pAddin;

			VARIANT_BOOL showBrushSize;
			brushSettings->get_showBrushSize(&showBrushSize);
			if (showBrushSize)
			{
				DrawBrushOutline(view, hDC, wpt);
				m_bBrushSizeVisible = true;
			}
		}

		SetROP2(hDC, oldR2);
		ReleaseDC(hWnd, hDC);
	}

	m_oldpt = pt;
	m_woldpt = wpt;
#endif

	return Success;
}

ErrorCode CLiquifyTool::OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	if (m_dragging)
	{
		if (m_timerWnd.m_hWnd)
		{
			ASSERT(0);
#if 0
			m_timerWnd.KillTimer(1);
			m_timerWnd.DestroyWindow();
			m_timerWnd.m_view = NULL;
			m_timerWnd.m_lt = NULL;
#endif
		}

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CElement* pElement = m_targetObjects[i];
			delete pElement;
		}
		m_targetObjects.RemoveAll();

		m_dragging = 0;
	}

	return Success;
}

ErrorCode CLiquifyTool::OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	if (!(mouse->nFlags & MK_ALT))
	{
		::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_CROSSHAIR)));
	}
	else
	{
		::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_SIZEBRUSH)));
	}
#endif

	return Success;
}

ErrorCode CLiquifyTool::OnActivate(ILXMLEditorApp* app)
{
	return Success;
}

ErrorCode CLiquifyTool::OnDeactivate(ILXMLEditorApp* app)
{
	// TODO: Add your implementation code here

	return Success;
}

Web::Element* GetOwnerLayer(Web::Element* element);
LDraw::Color GetLayerColor(Web::Element* element);

ErrorCode CLiquifyTool::Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, UI::Graphics* pGraphics)
{
	if (m_dragging)
	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CElement* pObject = m_targetObjects[i];
			
			Web::Element* domElement = pObject->m_eElement->get_domElement();

			Web::Element* layer = GetOwnerLayer(domElement);

			LDraw::Color layerColor = GetLayerColor(layer);

			LDraw::Pen* pen = new LDraw::Pen(layerColor);

			long npoints = pObject->m_points.GetSize();
			LDraw::PointD* points = pObject->m_points.GetData();

			for (int n = 0; n < npoints-1; n += 3)
			{
				pGraphics->DrawBezier(pen,
					(float)points[n].X, (float)points[n].Y,
					(float)points[n+1].X, (float)points[n+1].Y,
					(float)points[n+2].X, (float)points[n+2].Y,
					(float)points[n+3].X, (float)points[n+3].Y);
			}
		}
	}

	return Success;
}

/////////////////////////////////////////////////////////////////////////////
// CLiquifyToolPlugin

//ErrorCode CLiquifyToolPlugin::Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
//{
ErrorCode CLiquifyToolPlugin::SetSite(ILXMLEditorPluginClass* self)
{
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

		app->AddTool(self, this, NULL, ID_SVGTOOL_WARP, L"Warp", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_TWIRL, L"Twirl", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_PUCKER, L"Pucker", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_BLOAT, L"Bloat", L"tool_ellipse.bmp");

		uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_LIQUIFYTOOLS);
#endif
	}
#endif
	return Success;

}

#if 0
ErrorCode CLiquifyToolPlugin::Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
{
	return S_OK;
}
#endif

ErrorCode CLiquifyToolPlugin::FindTool(/*[in]*/ long id, System::Object* *pdlg, /*[out,retval]*/ ISVGTool** pVal)
{
	*pVal = NULL;
ASSERT(0);
#if 0
	CComObject<CLiquifyTool>* pTool;
	CComObject<CLiquifyTool>::CreateInstance(&pTool);
	if (pTool)
	{
		pTool->m_pAddin = this;
		pTool->AddRef();
		pTool->m_nTool = id;

		*pVal = pTool;
	}
#endif
	return Success;
}

ErrorCode CLiquifyTool::Options(UI::Control* hParent)
{
	ASSERT(0);
#if 0
	CPropertySheet* sheet = new CPropertySheet("Tool", 0, NULL/*TODO GetMainHwnd()*/);

	CBrushDimensionsDlg	brush;
	brush.m_brushSettings = m_pAddin;
	sheet->AddPage(brush);

	sheet->DoModal();
#endif
	return Success;
}

}	// LXmlEdit
}
