#include "stdafx.h"
#include "LXMLEditor2.h"

#include "EXMLDocument.h"	// TODO remove
#include "EXMLViewGroup.h"	// TODO remove

#include "BasicShapeTool.h"
//#include "BasicShapeToolPlugin.h"

//#include "../LXUI/Bezier.h"
#include "../gm/GraphicsGems.h"
#include "RectangularGridToolOptionsDlg.h"
#include "PolarGridToolOptionsDlg.h"

namespace System
{
namespace LXmlEdit
{

double GetLineAngle(double distance, double x1, double y1, double x2, double y2);

Web::Element* SVGGetLayer(Web::Element* element);
LDraw::Color GetLayerColor(Web::Element* element);

Web::SVGMatrix* GetRefElementMatrix(ISVGView* view);

void GetNewElementInsertionAt(CEXMLViewGroup* viewGroup, Web::Element** pparentNode, Web::Node** pbeforeNode);

/////////////////////////////////////////////////////////////////////////////
// CBasicShapeTool

CBasicShapeTool::CBasicShapeTool()
{
	m_pAddin = NULL;

	m_dragging = 0;

// Rectangular grid Tool
	m_rectgridHorzDivs = 5;
	m_rectgridVertDivs = 5;
	m_rectgridHorzSkew = 0;
	m_rectgridVertSkew = 0;
	m_outsideAsRect = true;

// Polar grid Tool
	m_polargridConcentricDivs = 5;
	m_polargridRadialDivs = 10;
	m_polargridConcentricSkew = 0;
	m_polargridRadialSkew = 0;
}

CBasicShapeTool::~CBasicShapeTool()
{
}

ErrorCode CBasicShapeTool::OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging)
{
	ASSERT(0);
#if 0
	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<ILDOMElement> insertAtParent;
	GetNewElementInsertionAt(viewGroup, &insertAtParent, NULL);
	if (insertAtParent == NULL/*static_cast<CEXMLViewGroup*>(viewGroup.p)->m_svgActiveContainer == NULL*/)
	{
		CComPtr<ILXMLEditorApp> editorApp;
		m_pAddin->m_spAddinSite->GetApp(&editorApp);

		CComPtr<ILXAddinSite> addinSite;
		CComQIPtr<ILXAddin> editorAddin = editorApp;
		editorAddin->GetSite(&addinSite);

		CComPtr<ILXFrameworkFrame> lxframe;
		addinSite->GetFrame(&lxframe);

		UI::Control* hWnd;
		CComQIPtr<IUIWnd> wnd = lxframe;
		wnd->get_hwnd(&hWnd);

		MessageBox(hWnd, "You must activate a layer", "LXMLEditor", MB_OK);
		return S_OK;
	}

	//LDraw::Point pt(mouse->ptx, mouse->pty);
	LDraw::PointD wpt(mouse->wptx, mouse->wpty);

	if (!m_dragging)
	{
		//m_startpt = pt;
		m_wstartpt = wpt;
		m_woldpt = wpt;
		m_wpt = wpt;

		m_newObjectBounds.X = m_wstartpt.X;
		m_newObjectBounds.Y = m_wstartpt.Y;
		m_newObjectBounds.Width = 0;
		m_newObjectBounds.Height = 0;

		m_dragging = 1;
		*pdragging = 1;

		window->captureMouse(VARIANT_TRUE);
	}
#endif

	return Success;
}

ErrorCode CBasicShapeTool::OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	LDraw::PointD wpt(mouse->wptx, mouse->wpty);
	m_wpt = wpt;

	if (m_dragging)
	{
		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<IHTMLPaintSite> paintSite;
		view->GetPaintSite(&paintSite);

		LDraw::RectD m_oldBounds = m_newObjectBounds;
		m_oldBounds.Normalize();

		m_newObjectBounds.X = m_wstartpt.X;
		m_newObjectBounds.Y = m_wstartpt.Y;
		m_newObjectBounds.Width = wpt.X-m_wstartpt.X;
		m_newObjectBounds.Height = wpt.Y-m_wstartpt.Y;

		if (m_nTool == ID_SVGTOOL_CIRCLE)
		{
			int size = max(abs(m_newObjectBounds.Width), abs(m_newObjectBounds.Height));

			m_newObjectBounds.Width = size * SGN(m_newObjectBounds.Width);
			m_newObjectBounds.Height = size * SGN(m_newObjectBounds.Height);
		}

		if (mouse->nFlags & MK_SHIFT)
		{
			if (m_nTool == ID_SVGTOOL_LINE)
			{
				double dx = wpt.X-m_wstartpt.X;
				double dy = wpt.Y-m_wstartpt.Y;

				double length = sqrt(dx*dx+dy*dy);

				double angle = GetLineAngle(length, m_wstartpt.X, m_wstartpt.Y, wpt.X, wpt.Y);

				double newangle = (int)(angle/(M_PI/4)+0.5)*(M_PI/4);

				double newx = m_wstartpt.X + cos(newangle)*length;
				double newy = m_wstartpt.Y + sin(newangle)*length;

				m_newObjectBounds.X = m_wstartpt.X;
				m_newObjectBounds.Y = m_wstartpt.Y;
				m_newObjectBounds.Width = newx-m_wstartpt.X;
				m_newObjectBounds.Height = newy-m_wstartpt.Y;
			}
			else
			{
				int size = max(abs(m_newObjectBounds.Width), abs(m_newObjectBounds.Height));

				m_newObjectBounds.Width = size * SGN(m_newObjectBounds.Width);
				m_newObjectBounds.Height = size * SGN(m_newObjectBounds.Height);
			}
		}

		if (mouse->nFlags & MK_ALT)
		{
			m_newObjectBounds.X -= m_newObjectBounds.Width;
			m_newObjectBounds.Y -= m_newObjectBounds.Height;
			m_newObjectBounds.Width *= 2;
			m_newObjectBounds.Height *= 2;
		}

		CComPtr<ILSVGMatrix> viewMatrix;
		view->GetViewMatrix(&viewMatrix);

		RectD rcd = m_newObjectBounds;
		rcd.Normalize();

		RectD rc = rcd;

		RectD totalrc;
		RectD::Union(totalrc, m_oldBounds, rc);

		LDraw::PointD pt0 = LDraw::PointD(totalrc.X, totalrc.Y).matrixTransform(viewMatrix);
		LDraw::PointD pt1 = LDraw::PointD(totalrc.X+totalrc.Width, totalrc.Y+totalrc.Height).matrixTransform(viewMatrix);

		totalrc = RectD(pt0.X, pt0.Y, pt1.X-pt0.X, pt1.Y-pt0.Y);

		totalrc.Normalize();

		CRect wrect(totalrc.X, totalrc.Y, totalrc.X+totalrc.Width, totalrc.Y+totalrc.Height);///GetWindowRectFromSpreadRect(totalrc);
		wrect.InflateRect(2, 2);

		paintSite->InvalidateRect(&wrect);
	}

	m_woldpt = wpt;
#endif
	return Success;
}

ErrorCode CBasicShapeTool::OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	if (m_dragging)
	{
		window->captureMouse(VARIANT_FALSE);

		CComPtr<IEXMLViewGroup> viewGroup;
		view->GetViewGroup(&viewGroup);

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<IEXMLDocument> edocument;
		viewGroup->get_eXMLDocument(&edocument);

		CComPtr<ILDOMDocument> document;
		edocument->get_DOMDocument(&document);

		CComPtr<ILDOMElement> activeParentNode;
		CComPtr<ILDOMNode> beforeNode;
		GetNewElementInsertionAt(viewGroup, &activeParentNode, &beforeNode);

		/*
		if (SVGIsGraphicContainer(static_cast<CWebXMLViewGroup*>(viewGroup.p)->m_svgActiveContainer))
		{
			static_cast<CWebXMLViewGroup*>(viewGroup.p)->m_svgActiveContainer->get_domNode(&activeParentNode);
			beforeNode = NULL;	// Append as last
		}
		else
		{
			CComPtr<ILDOMNode> node;
			static_cast<CWebXMLViewGroup*>(viewGroup.p)->m_svgActiveContainer->get_domNode(&node);
			node->get_parentNode(&activeParentNode);

			node->get_nextSibling(&beforeNode);
		}
		*/

		CComQIPtr<ILSVGElement> activeParentSVGElement = activeParentNode;

		CComQIPtr<ILSVGSVGElement> svgsvgElement = activeParentSVGElement;
		if (svgsvgElement == NULL)
			activeParentSVGElement->get_ownerSVGElement(&svgsvgElement);

	// First get the transformation of the parent
		CComPtr<ILSVGMatrix> parentCTM;

		CComQIPtr<ILSVGLocatable> parentLocatable = activeParentNode;
		if (parentLocatable)
		{
			// Don't include the window matrix here
			//window->svgGetScreenCTM(activeParentSVGElement, &parentCTM);
			parentLocatable->getScreenCTM(&parentCTM);
		}
		else
		{
			svgsvgElement->createSVGMatrix(&parentCTM);
		}

	// Then get the transformation of the reference element

		CComPtr<ILSVGMatrix> refMatrix;
		GetRefElementMatrix(view, &refMatrix);

		if (refMatrix)
		{
			CComPtr<ILSVGMatrix> mat;
			parentCTM->multiply(refMatrix, &mat);
			parentCTM = mat;
		}

		CComPtr<ILSVGMatrix> iparentCTM;
		parentCTM->inverse(&iparentCTM);

		LDraw::Point pt(mouse->ptx, mouse->pty);
		LDraw::PointD wpt(mouse->wptx, mouse->wpty);
		LDraw::PointD woldpt = m_woldpt;
		LDraw::PointD wstartpt = m_wstartpt;

		CComPtr<IEElement> eElement;

		switch (m_nTool)
		{
		case ID_SVGTOOL_LINE:
			{
				edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"line", &eElement);
				if (eElement)
				{
					CESVGLineElement* lineElement = dynamic_cast<CESVGLineElement*>(eElement);
					ASSERT(lineElement);

					double x1 = m_newObjectBounds.X;
					double y1 = m_newObjectBounds.Y;
					double x2 = m_newObjectBounds.X + m_newObjectBounds.Width;
					double y2 = m_newObjectBounds.Y + m_newObjectBounds.Height;

					lineElement->SetShape(x1, y1, x2, y2);
				}
			}
			break;

		case ID_SVGTOOL_RECTANGLE:
			{
				edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"rect", &eElement);
				if (eElement)
				{
					CESVGRectElement* rectElement = dynamic_cast<CESVGRectElement*>(eElement);
					ASSERT(rectElement);

					double x = m_newObjectBounds.X;
					double y = m_newObjectBounds.Y;
					double width = m_newObjectBounds.Width;
					double height = m_newObjectBounds.Height;

					rectElement->SetRectShape(x, y, width, height);
				}
			}
			break;

		case ID_SVGTOOL_ROUNDEDRECTANGLE:
			{
				edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"rect", &eElement);
				if (eElement)
				{
					CESVGRectElement* rectElement = dynamic_cast<CESVGRectElement*>(eElement);
					ASSERT(rectElement);

					double x = m_newObjectBounds.X;
					double y = m_newObjectBounds.Y;
					double width = m_newObjectBounds.Width;
					double height = m_newObjectBounds.Height;

					rectElement->SetRoundRectShape(x, y, width, height, 20, 20);
				}
			}
			break;

		case ID_SVGTOOL_CIRCLE:
			{
				edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"circle", &eElement);
				if (eElement)
				{
					CESVGCircleElement* circleElement = dynamic_cast<CESVGCircleElement*>(eElement);
					ASSERT(circleElement);

					double r = m_newObjectBounds.Width/2;
					double cx = m_newObjectBounds.X + r;
					double cy = m_newObjectBounds.Y + r;

					circleElement->SetShape(cx, cy, r);
				}
			}
			break;

		case ID_SVGTOOL_ELLIPSE:
			{
				//	CComQIPtr<ILSVGElement> element;
				CESVGEllipseElement* ellipseElement;
				
				/*
				if (abs(m_startpt.X-pt.X) < 2 || abs(m_startpt.Y-pt.Y) < 2)
				{
				}
				else
				*/
				{
					double rx = m_newObjectBounds.Width/2;
					double ry = m_newObjectBounds.Height/2;
					double cx = m_newObjectBounds.X + rx;
					double cy = m_newObjectBounds.Y + ry;

	#if 0
					if (gApp->m_bCreateAsPath)
					{
						SVGLib::ISVGPathElementPtr path = m_pDocument->GetDOMDocument()->createElement(L"path");
						
						SVGLib::ISVGAnimatedPathDataPtr pathData = path;
						SVGLib::ISVGPathSegListPtr seglist = pathData->pathSegList;
						
						seglist->LockUpdate();
						SetPathSegListToEllipse(seglist, cx-rx, cy-ry, cx+rx, cy+ry);
						seglist->UnlockUpdate();
						
						element = path;
					}
					else
	#endif
					{
						edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"ellipse", &eElement);
						
						ellipseElement = eElement;
						ellipseElement->SetShape(cx, cy, rx, ry);
						
						//eElement = ellipseElement;
					}
				}
			}
			break;

		case ID_SVGTOOL_RECTANGULARGRID:
			{
				CComPtr<IEElement> eG;
				edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"g", &eG);
				if (eG)
				{
					CComPtr<ILDOMElement> g;
					eG->get_domElement(&g);

					if (m_outsideAsRect)
					{
						CESVGRectElement* erect;
						edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"rect", (Element**)&erect);
						if (erect)
						{
							erect->SetRectShape(m_newObjectBounds.X, m_newObjectBounds.Y, m_newObjectBounds.Width, m_newObjectBounds.Height);

							CComPtr<ILDOMElement> rect;
							erect->get_domElement(&rect);

							g->appendChild(rect, NULL);
						}
					}

					{
						double P = m_rectgridHorzSkew;

						double height;
						if (P == 0)
							height = m_newObjectBounds.Height / (m_rectgridHorzDivs+1);
						else
							height = m_newObjectBounds.Height / (pow((1+P), m_rectgridHorzDivs+1)/((P+1)-1) - 1/((1+P)-1));

						double y = 0;

						for (int i = 0; i <= m_rectgridHorzDivs+1-m_outsideAsRect; i++)
						{
							if (i >= m_outsideAsRect)
							{
								CESVGLineElement* eline;
								edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"line", (Element**)&eline);
								if (eline)
								{
									eline->SetShape(m_newObjectBounds.X, m_newObjectBounds.Y+y, m_newObjectBounds.X+m_newObjectBounds.Width, m_newObjectBounds.Y+y);

									CComPtr<ILDOMElement> line;
									eline->get_domElement(&line);

									g->appendChild(line, NULL);
								}
							}

							y += height;
		
							height *= (P+1);
						}
					}

					{
						double P = m_rectgridVertSkew;

						double width;
						if (P == 0)
							width = m_newObjectBounds.Width / (m_rectgridVertDivs+1);
						else
							width = m_newObjectBounds.Width / (pow((1+P), m_rectgridVertDivs+1)/((P+1)-1) - 1/((1+P)-1));

						double x = 0;

						for (int i = 0; i <= m_rectgridVertDivs+1-m_outsideAsRect; i++)
						{
							if (i >= m_outsideAsRect)
							{
								CIESVGLineElement* eline;
								edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"line", (Element**)&eline);
								if (eline)
								{
									eline->SetShape(m_newObjectBounds.X+x, m_newObjectBounds.Y, m_newObjectBounds.X+x, m_newObjectBounds.Y+m_newObjectBounds.Height);

									CComPtr<ILDOMElement> line;
									eline->get_domElement(&line);

									g->appendChild(line, NULL);
								}
							}

							x += width;

							width *= (P+1);
						}
					}

					eElement = eG;
				}
			}
			break;

		case ID_SVGTOOL_POLARGRID:
			{
			}
			break;

			/*
		case ID_SVGTOOL_SVGELEMENT:
			{
				edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"svg", &eElement);
				if (eElement)
				{
					CComQIPtr<IESVGSVGElement> svgElement = eElement;
					ASSERT(rectElement);

					double x = m_newObjectBounds.X;
					double y = m_newObjectBounds.Y;
					double width = m_newObjectBounds.Width;
					double height = m_newObjectBounds.Height;

					svgElement->SetShape(x, y, width, height);
				}
			}
			break;
			*/

		case ID_SVGTOOL_FOREIGNOBJECT:
			{
				eElement = m_elementToPlace;
				m_elementToPlace.Release();

				double x = m_newObjectBounds.X;
				double y = m_newObjectBounds.Y;
				double width = m_newObjectBounds.Width;
				double height = m_newObjectBounds.Height;

				CComQIPtr<IESVGForeignObjectElement> f = eElement;
				CComQIPtr<IESVGVideoElement> v = eElement;
				if (f)
				{
					f->SetShape(x, y, width, height);
				}
				else if (v)
				{
					v->SetShape(x, y, width, height);
				}
				/*
				edocument->createEElementNS(L"http://www.w3.org/2000/svg", L"rect", &eElement);
				if (eElement)
				{
					CComQIPtr<IESVGRectElement> rectElement = eElement;
					ASSERT(rectElement);

					double x = m_newObjectBounds.X;
					double y = m_newObjectBounds.Y;
					double width = m_newObjectBounds.Width;
					double height = m_newObjectBounds.Height;

					rectElement->SetRoundRectShape(x, y, width, height, 20, 20);
				}
				*/
			}
			break;
		}

		if (eElement)
		{
			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			//if (m_nTool != ID_SVGTOOL_SVGELEMENT)
			{
				if (TRUE)
				{
					CComQIPtr<ILSVGTransformable> transformable = domElement;
					CComPtr<ILSVGAnimatedTransformList> atransformlist;
					transformable->get_transform(&atransformlist);

					CComPtr<ILSVGTransformList> transformlist;
					atransformlist->get_baseVal(&transformlist);

					CComPtr<ILSVGTransform> transform;
					svgsvgElement->createSVGTransformFromMatrix(iparentCTM, &transform);

					transformlist->appendItem(transform, NULL);
				}
			}

			CComBSTR cssText;
			((CEXMLDocument*)edocument.p)->m_defaultStyle->get_cssText(&cssText);
			if (cssText.Length())
			{
				domElement->setAttribute(L"style", cssText);
			}

			activeParentNode->insertBefore(domElement, CComVariant(beforeNode), NULL);

			viewGroup->ActivateElement(eElement, 0, NULL);

	#if 0
		//	_bstr_t style = gApp->m_pathSettings->m_domElement->getAttribute(L"style");
		//	if (style.length() > 0) element->setAttribute(L"style", style);
			
			CComObject<CWEUndoNewElement>* pUndo;
			CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
			if (pUndo)
			{
				//pUndo->AddRef();
				pUndo->m_pDocument = m_pDocument;//static_cast<CEXMLDocument*>(m_document.p);

				pUndo->DoInitial(m_pDocument->m_undoManager, element, svg, NULL);
			//	svg->appendChild(element, NULL);

				m_viewGroup->SetTargetElement(pDocument->m_pTree->FindDOMElement((ILDOMNode*)element), 0);
			}
	#endif
		}

		m_dragging = 0;
	}
#endif
	return Success;
}

ErrorCode CBasicShapeTool::OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_CROSSHAIR)));
#endif
	return Success;
}

ErrorCode CBasicShapeTool::Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, UI::Graphics* pGraphics)
{
	if (dragging)
	{
		CEXMLViewGroup* viewGroup = view->GetViewGroup();

		Element* rootEElement = view->GetEElement();

		Web::Element* rootElement = rootEElement->get_domElement();

		Web::SVGSVGElement* svgsvgElement = dynamic_cast<Web::SVGSVGElement*>(rootElement);

		Web::SVGMatrix* viewMatrix = view->GetViewMatrix();

		Web::CLHTMLWindow* window = view->GetHTMLWindow();

		double m_magnify;
		ASSERT(0);
#if 0
		window->get_magnify(&m_magnify);
#endif
		/*
		CComPtr<ILSVGMatrix> mat;
		svgsvgElement->createSVGMatrix(&mat);
		mat->scaleNonUniform(magnify, magnify, &viewMatrix);
		*/

		Web::Element* parentNode;
		GetNewElementInsertionAt(viewGroup, &parentNode, NULL);

		Web::Element* layer = SVGGetLayer(parentNode);
		LDraw::Color layerColor = GetLayerColor(layer);

		LDraw::PointD pt0 = viewMatrix->m_matrix.transform(LDraw::PointD(m_newObjectBounds.X, m_newObjectBounds.Y));
		LDraw::PointD pt1 = viewMatrix->m_matrix.transform(LDraw::PointD(m_newObjectBounds.X+m_newObjectBounds.Width, m_newObjectBounds.Y+m_newObjectBounds.Height));

		LDraw::RectD newObjectBounds(pt0.X, pt0.Y, pt1.X-pt0.X, pt1.Y-pt0.Y);
	//	RectD newObjectBounds = m_newObjectBounds;//(pt0.X, pt0.Y, pt1.X-pt0.X, pt1.Y-pt0.Y);

		//LDraw::Color layerColor = (GetRValue(clr), GetGValue(clr), GetBValue(clr));
		LDraw::Pen* pen = new LDraw::Pen(layerColor);

		switch (m_nTool)
		{
			/*
		case ID_SVGTOOL_SVGELEMENT:
			{
				graphics.DrawRectangle(&pen, (float)(newObjectBounds.X), (float)(newObjectBounds.Y), (float)(newObjectBounds.Width), (float)(newObjectBounds.Height));
			}
			break;
			*/

		case ID_SVGTOOL_CIRCLE:
		case ID_SVGTOOL_ELLIPSE:
			{
				pGraphics->DrawEllipse(pen, (float)(newObjectBounds.X), (float)(newObjectBounds.Y), (float)(newObjectBounds.Width), (float)(newObjectBounds.Height));
			}
			break;

		case ID_SVGTOOL_RECTANGLE:
			{
				pGraphics->DrawRectangle(pen, (float)(newObjectBounds.X), (float)(newObjectBounds.Y), (float)(newObjectBounds.Width), (float)(newObjectBounds.Height));
			}
			break;

		case ID_SVGTOOL_ROUNDEDRECTANGLE:
			{
				LDraw::GraphicsPathF path;
				path.AddRoundRect(newObjectBounds.X, newObjectBounds.Y, newObjectBounds.Width, newObjectBounds.Height, 20*m_magnify, 20*m_magnify);

				//graphics.DrawRectangle(&pen, (float)(m_newObjectBounds.X*m_magnify), (float)(m_newObjectBounds.Y*m_magnify), (float)(m_newObjectBounds.Width*m_magnify), (float)(m_newObjectBounds.Height*m_magnify));
				pGraphics->DrawPath(pen, &path);
			}
			break;

		case ID_SVGTOOL_LINE:
			{
				float x1 = (float)((newObjectBounds.X));
				float y1 = (float)((newObjectBounds.Y));
				float x2 = (float)((newObjectBounds.X+newObjectBounds.Width));
				float y2 = (float)((newObjectBounds.Y+newObjectBounds.Height));

				pGraphics->DrawLine(pen, x1, y1, x2, y2);
			}
			break;

		case ID_SVGTOOL_RECTANGULARGRID:
			{
				pGraphics->DrawRectangle(pen, (float)(newObjectBounds.X), (float)(newObjectBounds.Y), (float)(newObjectBounds.Width), (float)(newObjectBounds.Height));

				{
					double P = m_rectgridHorzSkew;

					double height;
					if (P == 0)
						height = newObjectBounds.Height / (m_rectgridHorzDivs+1);
					else
						height = newObjectBounds.Height / (pow((1+P), m_rectgridHorzDivs+1)/((P+1)-1) - 1/((1+P)-1));

					double y = 0;

					for (int i = 0; i < m_rectgridHorzDivs; i++)
					{
						y += height;
						pGraphics->DrawLine(pen, (float)(newObjectBounds.X), (float)(newObjectBounds.Y+y), (float)(newObjectBounds.X+newObjectBounds.Width), (float)(newObjectBounds.Y+y));

						height *= (P+1);
					}
				}

				{
					double P = m_rectgridVertSkew;

					double width;
					if (P == 0)
						width = newObjectBounds.Width / (m_rectgridVertDivs+1);
					else
						width = newObjectBounds.Width / (pow((1+P), m_rectgridVertDivs+1)/((P+1)-1) - 1/((1+P)-1));

					double x = 0;

					for (int i = 0; i < m_rectgridVertDivs; i++)
					{
						x += width;
						pGraphics->DrawLine(pen, (float)(newObjectBounds.X+x), (float)(newObjectBounds.Y), (float)(newObjectBounds.X+x), (float)(newObjectBounds.Y+newObjectBounds.Height));

						width *= (P+1);
					}
				}
			}
			break;

		case ID_SVGTOOL_POLARGRID:
			{
				double cx = newObjectBounds.X + newObjectBounds.Width/2;
				double cy = newObjectBounds.Y + newObjectBounds.Height/2;

				// Concentric Dividers
				{
					// rx
					double PX = m_polargridConcentricSkew;

					double width;
					if (PX == 0)
						width = (newObjectBounds.Width/2) / (m_polargridConcentricDivs+1);
					else
						width = (newObjectBounds.Width/2) / (pow((1+PX), m_polargridConcentricDivs+1)/((PX+1)-1) - 1/((PX+1)-1));

				// ry
					double PY = m_polargridConcentricSkew;

					double height;
					if (PY == 0)
						height = (newObjectBounds.Height/2) / (m_polargridConcentricDivs+1);
					else
						height = (newObjectBounds.Height/2) / (pow((1+PY), m_polargridConcentricDivs+1)/((PY+1)-1) - 1/((PY+1)-1));

					double ry = 0;
					double rx = 0;

					for (int i = 0; i < m_polargridConcentricDivs+1; i++)
					{
						rx += width;
						ry += height;

						pGraphics->DrawEllipse(pen, (float)(cx-rx), (float)(cy-ry), (float)(rx*2), (float)(ry*2));

						width *= (PX+1);
						height *= (PY+1);
					}
				}

				// Radial Dividers
				{
					double rx = newObjectBounds.Width/2;
					double ry = newObjectBounds.Height/2;

					// angle
					double P = m_polargridRadialSkew;

					double width;
					if (P == 0)
						width = (M_PI*2) / (m_polargridRadialDivs);
					else
						width = (M_PI*2) / (pow((1+P), m_polargridRadialDivs)/((P+1)-1) - 1/((P+1)-1));

					double angle = -M_PI/2;

					for (int i = 0; i < m_polargridRadialDivs; i++)
					{
						double x = cx + cos(angle) * rx;
						double y = cy + sin(angle) * ry;

						pGraphics->DrawLine(pen, float(cx), float(cy), float(x), float(y));

						angle += width;

						width *= (P+1);
					}
				}
			}
			break;

		case ID_SVGTOOL_FOREIGNOBJECT:
			{
				pGraphics->DrawRectangle(pen, (float)(newObjectBounds.X), (float)(newObjectBounds.Y), (float)(newObjectBounds.Width), (float)(newObjectBounds.Height));
			}
			break;
		}
	}

	return Success;
}

ErrorCode CBasicShapeTool::OnActivate(ILXMLEditorApp* app)
{
	// TODO: Add your implementation code here

	return Success;
}

ErrorCode CBasicShapeTool::OnDeactivate(ILXMLEditorApp* app)
{
	// TODO: Add your implementation code here

	return Success;
}

ErrorCode CBasicShapeTool::Options(UI::Control* hParent)
{
	switch (m_nTool)
	{
		case ID_SVGTOOL_RECTANGULARGRID:
			{
				CRectangularGridToolOptionsDlg dlg;

				dlg.m_horzDivs = m_rectgridHorzDivs;
				dlg.m_vertDivs = m_rectgridVertDivs;
				dlg.m_horzSkew = m_rectgridHorzSkew;
				dlg.m_vertSkew = m_rectgridVertSkew;
				dlg.m_outsideAsRect = m_outsideAsRect;

				if (dlg.DoModal(hParent) == IDOK)
				{
					m_rectgridHorzDivs = dlg.m_horzDivs;
					m_rectgridVertDivs = dlg.m_vertDivs;
					m_rectgridHorzSkew = dlg.m_horzSkew;
					m_rectgridVertSkew = dlg.m_vertSkew;
					m_outsideAsRect = dlg.m_outsideAsRect;
				}
			}
			break;

		case ID_SVGTOOL_POLARGRID:
			{
				CPolarGridToolOptionsDlg dlg;

				dlg.m_concentricDivs = m_polargridConcentricDivs;
				dlg.m_radialDivs = m_polargridRadialDivs;
				dlg.m_concentricSkew = m_polargridConcentricSkew;
				dlg.m_radialSkew = m_polargridRadialSkew;

				if (dlg.DoModal(hParent) == IDOK)
				{
					m_polargridConcentricDivs = dlg.m_concentricDivs;
					m_polargridRadialDivs = dlg.m_radialDivs;
					m_polargridConcentricSkew = dlg.m_concentricSkew;
					m_polargridRadialSkew = dlg.m_radialSkew;
				}
			}
			break;

		default:
			return Success_False;
	}

	return Success_True;
}

}	// LXmlEdit
}
