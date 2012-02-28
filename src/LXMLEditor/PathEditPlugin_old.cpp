#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "PathEditPlugin.h"

#include "ESVGPathElement.h"
#include "ESelectedSVGPathElement.h"

#include "ESelectedSVGPolyElement.h"

void GetNewElementInsertionAt(IEXMLViewGroup* viewGroup, ILDOMElement** pparentNode, ILDOMNode** pbeforeNode);

// Tool
STDMETHODIMP CPathEditTool::OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging)
{
	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> document;
	viewGroup->get_eXMLDocument(&document);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	SVGPoint wpt(mouse->wptx, mouse->wpty);

	m_dragging = 0;

	switch (m_nTool)
	{
	case ID_SVGTOOL_PATHPEN:
		{
			int nResource = 0;
			
			_SVGHitData m_hitdata;
			view->HitTest(NULL, mouse->ptx, mouse->pty, 1, &m_hitdata);
			
			long subpathcurveCp = -1;
			long nactivesubpathPoints = 0;
			VARIANT_BOOL activesubpathClosed = 0;
			CComPtr<IESVGSubPath> activesubpath;
			
			if (m_pActivePath)
			{
				ASSERT(m_hitdata.ctl/*m_curveCp*/ >= 0);
				if (TRUE)
				{
					CComPtr<IESVGPath> path;
					m_pActivePath->GetPath()->GetPath(&path);
					path->GetSubPathFromIndex(m_curveCp, &subpathcurveCp, &activesubpath);
				}
				else	// TODO remove this
				{
#if 0
					activesubpath = m_pActivePath->GetPath()->m_subPaths[0];
					activesubpath->get_pointCount(&subpathcurveCp);
					subpathcurveCp--;
#endif
				}
				
				//activesubpath->get_closed(&activesubpathClosed);
				activesubpath->get_pointCount(&nactivesubpathPoints);
			}
			
			if (m_hitdata.element/*object*/)
			{
				CComQIPtr<IESVGPathElement> pathElement = m_hitdata.element;
				
				CESelectedSVGPathElement* pPath = static_cast<CESelectedSVGPathElement*>(m_hitdata.selectedElement);//GetPDPathSelected(hitdata.path);
				
				if (m_hitdata.anchor >= 0)
				{
					CComPtr<IESVGSubPath> subpath;
					long subpathIndex;
					if (TRUE)
					{
						CComPtr<IESVGPath> path;
						pathElement->GetPath(&path);
						path->GetSubPathFromIndex(m_hitdata.anchor, &subpathIndex, &subpath);
					}
					/*
					else
					{
						subpath = path->m_subPaths[0];
						subpath->get_pointCount(&subpathIndex);
						subpathIndex--;
					}
					*/
					
					long nsubpathPoints;
					subpath->get_pointCount(&nsubpathPoints);
					
					VARIANT_BOOL closed;
					subpath->get_closed(&closed);
					
					if (nResource == 0)
					{
						if (m_pActivePath && m_pActivePath == pPath && activesubpath == subpath && !closed && m_hitdata.ctl == 0)
						{
							if ((subpathIndex == 0 && subpathcurveCp == nsubpathPoints-1) ||
								(subpathIndex == nsubpathPoints-1 && subpathcurveCp == 0))
							{
								// Close
								subpath->put_closed(VARIANT_TRUE);
								
								m_pActivePath = NULL;
								m_curveCp = -1;
								
								nResource = 1;
							}
							else if ((subpathIndex == 0 && subpathcurveCp == 0) ||
								(subpathIndex == nsubpathPoints-1 && subpathcurveCp == nsubpathPoints-1))
							{
								// Change first/last point on curve
								ASSERT(m_pActivePath);
								
								if (subpathcurveCp == 0)
									m_curveDir = m_curveCtl = -1;
								else
									m_curveDir = m_curveCtl = 1;
								
#if 0
								m_curveCp = hitdata.anchor;
#endif
								
								if (!m_pActivePath->IsAnchorSelected(m_hitdata.anchor/*m_curveCp*/))
									m_pActivePath->SelectAnchor(m_hitdata.anchor/*m_curveCp*/);
								
								m_dragging = 1;
#if 0
								m_hit = 2;
#endif
								
								nResource = 1;
							}
						}
					}
					
					if (nResource == 0)
					{
						if (m_pActivePath != NULL &&
							m_hitdata.ctl == 0 &&
							!closed &&
							!activesubpathClosed &&
							subpath != activesubpath &&
							(subpathcurveCp == 0 || subpathcurveCp == nactivesubpathPoints-1) &&
							(subpathIndex == 0 || subpathIndex == nsubpathPoints-1))
						{
							ASSERT(0);
#if 0
							// Connect
							
							m_pActivePath->DeselectAllPoints();//DeselectAll();
							
							m_pActivePath->GetPath()->removeSubPath(activesubpath);
							
							if (subpathcurveCp == nactivesubpathPoints-1)
							{
								activesubpath->reverse();
							}
							
							if (subpathIndex == 0)
							{
								subpath->reverse();
							}
							
							subpath->appendSubPathPoints(activesubpath);
							
							m_pActivePath = NULL;
							m_hitdata.anchor/*m_curveCp*/ = -1;
							
							nResource = 1;
#endif
						}
					}
					
					if (nResource == 0)
					{
						if (pPath &&
							!closed && m_hitdata.ctl == 0 &&
							((subpathIndex == 0) || (subpathIndex == nsubpathPoints-1)))
						{
							// Continue
							m_pActivePath = pPath;
							
							m_pActivePath->DeselectAllPoints();
							
							if (subpathIndex == nsubpathPoints-1)
								m_curveDir = m_hitdata.ctl/*m_curveCtl*/ = 1;
							else
								m_curveDir = m_hitdata.ctl/*m_curveCtl*/ = -1;
							
#if 0
							m_curveCp = hitdata.anchor;
#endif
							
							m_pActivePath->SelectAnchor(m_hitdata.anchor/*m_curveCp*/);
							
							nResource = 1;
						}
					}
					
					if (nResource == 0)
					{
						if (pPath && m_hitdata.ctl == 0)
						{
							// Delete anchor point
							pPath->DeleteAnchorPoint(m_hitdata.anchor);
							m_hitdata.anchor--;// ??? if (m_curveCp >= m_hitdata.anchor) m_curveCp--;
							
							nResource = 1;
						}
					}
			}
			else if (m_hitdata.segment >= 0)
			{
#if 0
				if (pPath)
				{
					pPath->DeselectAllPoints();
					
					m_pActivePath = pPath;
					m_curveCp = hitdata.segment+1;
					
					pPath->GetPDPath()->insertAnchorPointAt(hitdata.segment, hitdata.t);
					pPath->SelectAnchor(m_curveCp);
					
					m_curveDir = 1;
					m_curveCtl = 1;
#if 0
					m_hit = 1;
#endif
					m_dragging = 1;
					
					nResource = 1;
				}
#endif
			}
		}
		
		if (nResource == 0)
		{
			if (m_pActivePath &&
				(subpathcurveCp == 0 || subpathcurveCp == nactivesubpathPoints-1))
			{
				m_pActivePath->DeselectAllPoints();
				
				if (/*hitdata->*/m_curveDir == 1)	// Insert point at end
				{
					m_pActivePath->InsertPointAfter(m_curveCp, wpt.X, wpt.Y, wpt.X, wpt.Y, wpt.X, wpt.Y);
					/*m_hitdata.anchor++;//m_hitdata.ctl++;//*/m_curveCp++;
				}
				else if (m_curveDir == -1)	// Insert point at beginning
				{
					m_pActivePath->InsertPointBefore(m_hitdata.anchor/*m_curveCp*/, wpt.X, wpt.Y, wpt.X, wpt.Y, wpt.X, wpt.Y);
					m_curveCp--;
				}
				else
					ASSERT(0);
				
				m_pActivePath->SelectAnchor(m_curveCp);
			//	m_hitdata.ctl = /*m_curveCtl =*/ /*hitdata->*/m_curveDir;
				m_curveCtl = m_curveDir;
#if 0
				m_hit = 1;
#endif
				m_dragging = 1;
				
				nResource = 1;
			}
		}

		if (nResource == 0)
		{
			CComPtr<IEElement> rootElement;
			view->GetEElement(&rootElement);
			
			CComPtr<IEElement> eElement;
			document->createEElementNS(L"http://www.w3.org/2000/svg", L"path", &eElement);
			CESVGPathElement* pPathElement = static_cast<CESVGPathElement*>(eElement.p);

			// Set style
			{
				CComBSTR cssText;
				((CEXMLDocument*)document.p)->m_defaultStyle->get_cssText(&cssText);

				CComPtr<ILDOMElement> element;
				eElement->get_domElement(&element);
				element->setAttribute(L"style", cssText);
			}

			CComPtr<IESVGPath> path;
			pPathElement->GetPath(&path);
			/*
			CComQIPtr<IPDPath> pathData;
			path->get_path(&pathData);
			
			  CComQIPtr<IPDSubPath> subPath;
			  pathData->createSubPath(&subPath);
			  pathData->insertSubPath(-1, subPath);
			  
				 subPath->appendPoint(wpt.x, wpt.y, wpt.x, wpt.y, wpt.x, wpt.y, &m_curveCp);
				 ASSERT(m_curveCp == 0);
			*/
			CComObject<CSubPath>* subPath;
			CComObject<CSubPath>::CreateInstance(&subPath);
			subPath->AddRef();
			subPath->m_pPath = static_cast<CESVGPath*>(path.p);
			static_cast<CESVGPath*>(path.p)->m_subPaths.Add(subPath);
			subPath->m_segIndex = 0;
			subPath->appendPoint(wpt.X, wpt.Y, wpt.X, wpt.Y, wpt.X, wpt.Y, &m_curveCp);
			
			m_curveDir = m_curveCtl = 1;

			/*
			activeLayerGroup->appendObject(path);
			pObject = (CPDObjectFrameSelected*)SelectPDObject(path, 0, FALSE);
			*/
			rootElement->appendChild(eElement);
			
			CComPtr<IESelectedElement> selectedObject;
			viewGroup->ActivateElement(eElement, 0, &selectedObject);
			CESelectedSVGPathElement* pSelectedObject = static_cast<CESelectedSVGPathElement*>(selectedObject.p);
			
			m_pActivePath = pSelectedObject;
			
			pSelectedObject/*m_pActivePath*/->SelectAnchor(m_curveCp);
			
			/*
			m_hit = 1;
			*/
			m_dragging = 1;
			
			nResource = 1;
		}
		
#if 0
		if (nResource == 0)	// Create new path
		{
			//CPDObjectFrameSelected* pObject = NULL;
			CESelectedSVGPathElement* pSelectedObject = NULL;
			
			CComPtr<IESVGPathElement> pPath;
			document->createSVGPathElement(&pPath);
			
			// Create new path element
			CComPtr<ILSVGPathElement> path;
			pDocument->GetDOMDocument()->createElement(L"path", (ILDOMElement**)&path);
			
			svgsvgElement->appendChild(path, NULL);
			CPathElement* pPath = (CPathElement*)pDocument->m_pTree->FindDOMElement((ILSVGElement*)path);
			pSelectedObject = (CESelectedSVGPathElement*)m_viewGroup->SetTargetElement(pPath, 0);
			
			//	CComQIPtr<IPDObjectFrame> path;
			//	m_document->createObjectFrame(&path);
			
			/*
			CComQIPtr<IPDPath> pathData;
			path->get_path(&pathData);
			
			  CComQIPtr<IPDSubPath> subPath;
			  pathData->createSubPath(&subPath);
			  pathData->insertSubPath(-1, subPath);
			*/
			m_hitdata = new CHitData;
			
			CSubPath* subPath = new CSubPath;
			subPath->m_pPath = pPath;
			pPath->m_subPaths.Add(subPath);
			subPath->m_segIndex = 0;
			subPath->appendPoint(wpt.X, wpt.Y, wpt.X, wpt.Y, wpt.X, wpt.Y, &m_hitdata->anchor/*m_curveCp*/);
			ASSERT(m_hitdata->anchor/*m_curveCp*/ == 0);
			
			m_curveDir = m_hitdata.ctl/*m_curveCtl*/ = 1;
			
			m_pActivePath = pObject;//->m_path;
			
			pSelectedObject/*m_pActivePath*/->SelectAnchor(m_hitdata->anchor/*m_curveCp*/);
#if 0
			m_hit = 1;
#endif
			m_dragging = 1;
			
#if 0
			nResource = 1;
#endif
		}
#endif
		}
		break;
	
	case ID_SVGTOOL_POLYGON:
//	case ID_SVGTOOL_POLYLINE:
		{
			CComPtr<IEElement> rootElement;
			view->GetEElement(&rootElement);

			CComPtr<ILSVGSVGElement> svgsvgElement;
			rootElement->get_domElement((ILDOMElement**)&svgsvgElement);

			int nResource = 0;

			CComPtr<IESelectedElement> selectedElement;
			viewGroup->GetActiveSelectedElement(&selectedElement);
			CComQIPtr<IESelectedSVGPolyElement> selectedPolyElement = selectedElement;
			CComQIPtr<IESVGPolyElement> poly;
			if (selectedPolyElement)
				selectedPolyElement->get_eElement((IEElement**)&poly);

			_SVGHitData hitdata;
			view->HitTest(NULL, mouse->ptx, mouse->pty, 1, &hitdata);

			long npoints2 = 0;

			CComQIPtr<IESVGPolyElement> poly2 = hitdata.element;
			VARIANT_BOOL bClosed2;

			if (poly2)
			{
				poly2->get_pointCount(&npoints2);
				poly2->IsClosed(&bClosed2);
			}

			if (poly && poly == poly2)
			{
				if (m_curveDir == -1)
				{
					if (hitdata.anchor == npoints2-1)
						nResource = IDC_PENCLOSE;
					else if (hitdata.anchor == 0)
						;//nResource = IDC_PENCHANGELAST;
				}
				else if (m_curveDir == 1)
				{
					if (hitdata.anchor == npoints2-1)
						;//nResource = IDC_PENCHANGELAST;
					else if (hitdata.anchor == 0)
						nResource = IDC_PENCLOSE;
				}

				if (nResource == IDC_PENCLOSE)
				{
					selectedElement.Release();

					CComPtr<IEElement> eElement;
					poly->SetClosed(VARIANT_TRUE, &eElement);
					poly = eElement;

					viewGroup->ActivateElement(eElement, MK_SHIFT, &selectedElement);
					selectedPolyElement = selectedElement;
				}
			}

			if (nResource == 0)
			{
				if (poly && poly2 && poly != poly2)
				{
					if (m_curveDir)
					{
						if (!bClosed2 && hitdata.anchor == 0 || hitdata.anchor == npoints2-1)
						{
							nResource = IDC_PENCONNECT;

							CComPtr<ILDOMElement> domElement;
							poly->get_domElement(&domElement);

							CComPtr<ILDOMElement> domElement2;
							poly2->get_domElement(&domElement2);

						// Remove poly element
							CComPtr<ILDOMNode> parentNode;
							domElement->get_parentNode(&parentNode);
							parentNode->removeChild(domElement, NULL);

						// Add points on poly to poly2
							CComQIPtr<ILSVGAnimatedPoints> apoints = domElement;
							CComPtr<ILSVGPointList> points;
							apoints->get_points(&points);

							CComQIPtr<ILSVGAnimatedPoints> apoints2 = domElement2;
							CComPtr<ILSVGPointList> points2;
							apoints2->get_points(&points2);

							long npoints;
							points->get_numberOfItems(&npoints);

							long npoints2;
							points2->get_numberOfItems(&npoints2);

							for (int i = npoints-1; i >= 0; i--)
							{
								CComQIPtr<ILSVGPoint> point;
								points->getItem(i, &point);

								if (m_curveDir == 1 && hitdata.anchor == 0)
								{
									points2->insertItemBefore(point, 0, NULL);
								}
								else if (m_curveDir == 1 && hitdata.anchor == npoints2-1)
								{
									points2->appendItem(point, NULL);
								}
								else if (m_curveDir == -1 && hitdata.anchor == 0)
								{
									points2->insertItemBefore(point, npoints-1-i, NULL);
								}
								else if (m_curveDir == -1 && hitdata.anchor == npoints2-1)
								{
									points2->insertItemBefore(point, npoints2, NULL);
								}
								else
									ASSERT(0);
							}

							selectedElement.Release();
							viewGroup->ActivateElement(poly2, 0, &selectedElement);
							selectedPolyElement = selectedElement;
						}
					}
				}
			}

			if (nResource == 0)
			{
				if (poly2 && (poly != poly2 || m_curveDir == 0))
				{
				//	if (m_curveDir == 0)
					{
						if (hitdata.anchor == 0 || hitdata.anchor == npoints2-1)
						{
							if (hitdata.anchor == 0)
								m_curveDir = -1;
							else
								m_curveDir = 1;

							if (poly != poly2)
							{
								selectedElement.Release();
								viewGroup->ActivateElement(poly2, 0, &selectedElement);
							}
							selectedPolyElement = selectedElement;

							static_cast<CESelectedSVGPolyElement*>(selectedPolyElement.p)->DeselectAllPoints();
							static_cast<CESelectedSVGPolyElement*>(selectedPolyElement.p)->SelectAnchor(hitdata.anchor);

							nResource = IDC_PENCONTINUE;
						}
					}
				}
			}

			if (nResource == 0)
			{
				if (poly && poly == poly2)
				{
					if (hitdata.anchor >= 0)
					{
						CComPtr<ILDOMElement> domElement;
						poly->get_domElement(&domElement);
						CComQIPtr<ILSVGAnimatedPoints> apoints = domElement;
						CComPtr<ILSVGPointList> points;
						apoints->get_points(&points);

						static_cast<CESelectedSVGPolyElement*>(selectedPolyElement.p)->DeselectAllPoints();

						CComPtr<ILSVGPoint> oldpoint;
						points->removeItem(hitdata.anchor, &oldpoint);

						nResource = IDC_PENDELETE;
					}
					else if (hitdata.segment >= 0)
					{
						CComPtr<ILDOMElement> domElement;
						poly->get_domElement(&domElement);
						CComQIPtr<ILSVGAnimatedPoints> apoints = domElement;
						CComPtr<ILSVGPointList> points;
						apoints->get_points(&points);

						static_cast<CESelectedSVGPolyElement*>(selectedPolyElement.p)->DeselectAllPoints();

						CComPtr<ILSVGPoint> A;
						points->getItem(hitdata.segment, &A);
						double ax, ay;
						A->get_x(&ax);
						A->get_y(&ay);

						CComPtr<ILSVGPoint> B;
						points->getItem(hitdata.segment+1, &B);
						double bx, by;
						B->get_x(&bx);
						B->get_y(&by);

						CComPtr<ILSVGPoint> point;
						svgsvgElement->createSVGPoint(&point);
						point->put_x(ax + (bx-ax)*hitdata.t);
						point->put_y(ay + (by-ay)*hitdata.t);

						points->insertItemBefore(point, hitdata.segment+1, NULL);

						nResource = IDC_PENADD;
					}
				}
			}

			if (nResource == 0)
			{
				if (poly == NULL || m_curveDir == 0)
				{
					CComPtr<IEElement> eElement;
					document->createEElementNS(L"http://www.w3.org/2000/svg", L"polyline", &eElement);

					CComPtr<ILDOMElement> element;
					eElement->get_domElement(&element);

					CComQIPtr<ILSVGAnimatedPoints> apoints = element;
					ASSERT(apoints);

					CComPtr<ILSVGPointList> points;
					apoints->get_points(&points);
					ASSERT(points);

					CComPtr<ILSVGPoint> point;
					svgsvgElement->createSVGPoint(&point);
					point->put_x(wpt.X);
					point->put_y(wpt.Y);

					points->appendItem(point, NULL);

					m_curveDir = 1;

				// Set style
					{
						CComBSTR cssText;
						((CEXMLDocument*)document.p)->m_defaultStyle->get_cssText(&cssText);

						CComPtr<ILDOMElement> element;
						eElement->get_domElement(&element);
						element->setAttribute(L"style", cssText);
					}

					rootElement->appendChild(eElement);

					selectedElement.Release();
					viewGroup->ActivateElement(eElement, 0, &selectedElement);
					selectedPolyElement = selectedElement;

					poly = eElement;
					nResource = IDC_PENNEW;
				}
			}

			if (nResource == IDC_PENNEW || nResource == 0)
			{
				CComPtr<ILDOMElement> domElement;
				poly->get_domElement(&domElement);
				CComQIPtr<ILSVGAnimatedPoints> apoints = domElement;
				CComPtr<ILSVGPointList> points;
				apoints->get_points(&points);

				//CComQIPtr<ILSVGTransformable> transformable = domElement;
				CComPtr<ILSVGMatrix> ctm;
				/*
				transformable->getScreenCTM(&ctm);
				*/
				window->svgGetScreenCTM(CComQIPtr<ILSVGElement>(domElement), &ctm);
				CComPtr<ILSVGMatrix> ictm;
				ctm->inverse(&ictm);

				SVGPoint xpt = wpt.matrixTransform(ictm);

				CComPtr<ILSVGPoint> point;
				svgsvgElement->createSVGPoint(&point);
				point->put_x(xpt.X);
				point->put_y(xpt.Y);

				static_cast<CESelectedSVGPolyElement*>(selectedPolyElement.p)->DeselectAllPoints();

				ASSERT(m_curveDir != 0);

				if (m_curveDir == 1)
				{
					points->appendItem(point, NULL);

					long npoints;
					points->get_numberOfItems(&npoints);

					static_cast<CESelectedSVGPolyElement*>(selectedPolyElement.p)->SelectAnchor(npoints-1);
				}
				else
				{
					points->insertItemBefore(point, 0, NULL);
					static_cast<CESelectedSVGPolyElement*>(selectedPolyElement.p)->SelectAnchor(0);
				}

				m_dragging = 1;
			}
		}
		break;
		
	case ID_SVGTOOL_PENCIL:
		{
			ASSERT(m_points.GetSize() == 0);
			m_dragging = 1;
		}
		break;
	}

	m_woldpt = wpt;

	*pdragging = m_dragging;

	return S_OK;
}

#include "GraphicsGems.h"

typedef Point2 *BezierCurve;
void FitCurve(Point2	*d, int nPts, double error);

extern CComQIPtr<ILSVGPathElement> g_pathElement;
extern ILSVGPathSegList* g_pathSegList;
extern int g_pathSize;

STDMETHODIMP CPathEditTool::OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> document;
	eDocument->get_DOMDocument(&document);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	if (m_dragging)
	{
		switch (m_nTool)
		{
		case ID_SVGTOOL_PENCIL:
			{
				CComPtr<ILDOMElement> activeParentNode;
				CComPtr<ILDOMNode> beforeNode;
				GetNewElementInsertionAt(viewGroup, &activeParentNode, &beforeNode);

				CComPtr<ILDOMElement> pathElement;
				document->createElementNS(L"http://www.w3.org/2000/svg", L"path", &pathElement);
				if (pathElement)
				{
					CComQIPtr<ILSVGAnimatedPathData> pathData = pathElement;

					CComPtr<ILSVGPathSegList> seglist;
					pathData->get_pathSegList(&seglist);

					g_pathElement = pathElement;
					g_pathSegList = seglist;

				//	int count = 0;
				//	for (int sub = 0; sub < m_subPoints.GetSize(); sub++)
					{
						//int size = m_subPoints[sub];
						PointD* points = m_points.GetData();//m_flatPoints.GetData() + count;
						//count += size;

						g_pathSize = 0;
						double	error = 25.0;		//  Squared error

						FitCurve((Point2*)points, m_points.GetSize(), error);		//  Fit the Bezier curves
					}

					activeParentNode->insertBefore(pathElement, CComVariant(beforeNode), NULL);
				}

				m_points.RemoveAll();
			}
			break;
		}

		m_dragging = 0;
	}

	return S_OK;
}

STDMETHODIMP CPathEditTool::OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	SVGPoint wpt(mouse->wptx, mouse->wpty);
	SVGPoint woldpt = m_woldpt;

	if (m_dragging)
	{
		switch (m_nTool)
		{
		case ID_SVGTOOL_PATHPEN:
			{
				//CComQIPtr<IESVGElement> path = m_pActivePath;
				if (m_pActivePath/*path*/)
				{
					CESVGPathElement* pPath = m_pActivePath->GetPath();//static_cast<CPathElement*>(path.p);
					//CPathElement* pPath = (CPathElement*)pDocument->m_pTree->FindDOMElement((ILSVGElement*)path);
					
					CComPtr<ILDOMElement> object;
					pPath->get_domElement(&object);
					
					//CComQIPtr<ILSVGTransformable> objectTransformable = object;

					CComPtr<ILSVGMatrix> ctm;
					window->svgGetScreenCTM((ILSVGElement*)object.p, &ctm);	// Maybe getCTM2()
				//	objectTransformable->getScreenCTM(&ctm);

					CComPtr<ILSVGMatrix> ictm;
					ctm->inverse(&ictm);
					
					SVGPoint xpt = wpt.matrixTransform(ictm);
					SVGPoint xoldpt = woldpt.matrixTransform(ictm);
					
					if (TRUE/*m_hit == 1*/)	// Same length
					{
						pPath->SetControlPointsSameLength(m_curveCp, m_curveCtl, xpt.X, xpt.Y/*, invalidRc*/);
					}
	#if 0	// Have this
					else if (m_hit == 2)
					{
						pPath->SetPathSegControlPoints(m_curveCp, m_curveCtl, xnewpt2.X, xnewpt2.Y/*, invalidRc*/);
					}
					else
						ASSERT(0);
	#endif
				}
			}
			break;
			
		case ID_SVGTOOL_POLYGON:
	//	case ID_SVGTOOL_POLYLINE:
			{
				CComPtr<IESelectedSVGPolyElement> selectedElement;
				viewGroup->GetActiveSelectedElement((IESelectedElement**)&selectedElement);

				if (selectedElement)
				{
					CComPtr<IEElement> eElement;
					selectedElement->get_eElement(&eElement);

					CComPtr<ILDOMElement> domElement;
					eElement->get_domElement(&domElement);

					//CComQIPtr<ILSVGTransformable> transformable = domElement;
					
					CComPtr<ILSVGMatrix> ctm;
					//transformable->getScreenCTM(&ctm);
					window->svgGetScreenCTM(CComQIPtr<ILSVGElement>(domElement), &ctm);

					CComPtr<ILSVGMatrix> ictm;
					ctm->inverse(&ictm);

					SVGPoint xpt = wpt.matrixTransform(ictm);

					CComQIPtr<ILSVGAnimatedPoints> apoints = domElement;

					CComPtr<ILSVGPointList> points;
					apoints->get_points(&points);

					long npoints;
					points->get_numberOfItems(&npoints);

					CComPtr<ILSVGPoint> point;
					if (m_curveDir == 1)
						points->getItem(npoints-1, &point);
					else
						points->getItem(0, &point);

					points->LockUpdate();

					point->put_x(xpt.X);
					point->put_y(xpt.Y);

					points->UnlockUpdate();
				}
			}
			break;

		case ID_SVGTOOL_PENCIL:
			{
				m_points.Add(wpt);
			}
			break;
		}
	}
	
	m_woldpt = wpt;
	
	return S_OK;
}

STDMETHODIMP CPathEditTool::OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	switch (m_nTool)
	{
	case ID_SVGTOOL_PATHPEN:
		{
			int nResource = 0;

			CComPtr<IESelectedElement> selectedElement;
			viewGroup->GetActiveSelectedElement(&selectedElement);
			CComQIPtr<IESelectedSVGPathElement> selectedPathElement = selectedElement;

			CComPtr<IESVGSubPath> subpath;
			long anchor = -1;

			CComPtr<IESVGPathElement> pathElement;
			if (selectedPathElement)
			{
				selectedPathElement->get_eElement((IEElement**)&pathElement);

				CComPtr<IESVGPath> path;
				pathElement->GetPath(&path);

				path->GetSubPathFromIndex(m_curveCp, &anchor, &subpath);
			}

			_SVGHitData hitdata;
			view->HitTest(NULL, mouse->ptx, mouse->pty, 2, &hitdata);

			CComPtr<IESVGSubPath> subpath2;
			long npoints2 = 0;
			long anchor2 = -1;
			long segment2 = -1;
			VARIANT_BOOL bClosed2;

			CComQIPtr<IESVGPathElement> pathElement2 = hitdata.element;

			if (pathElement2)
			{
				CComPtr<IESVGPath> path2;
				pathElement2->GetPath(&path2);

				path2->GetSubPathFromIndex(hitdata.anchor, &anchor2, &subpath2);

				segment2 = hitdata.segment;

				subpath2->get_pointCount(&npoints2);
				subpath2->get_closed(&bClosed2);
			}

			if (subpath && subpath == subpath2)
			{
				if (hitdata.ctl == 0)
				{
					if (m_curveDir == -1)
					{
						if (anchor2 == npoints2-1)
							nResource = IDC_PENCLOSE;
						else if (anchor2 == 0)
							nResource = IDC_PENCHANGELAST;
					}
					else if (m_curveDir == 1)
					{
						if (anchor2 == npoints2-1)
							nResource = IDC_PENCHANGELAST;
						else if (anchor2 == 0)
							nResource = IDC_PENCLOSE;
					}
				}
				else
				{
				}
			}

			if (nResource == 0)
			{
				if (subpath && subpath2 && subpath != subpath2)
				{
					if (m_curveDir)
					{
						if (!bClosed2 && anchor2 == 0 || anchor2 == npoints2-1)
						{
							nResource = IDC_PENCONNECT;
						}
					}
				}
			}

			if (nResource == 0)
			{
				if (subpath2 && (subpath != subpath2 || m_curveDir == 0))
				{
				//	if (m_curveDir == 0)
					{
						if (anchor2 == 0 || anchor2 == npoints2-1)
						{
							nResource = IDC_PENCONTINUE;
						}
					}
				}
			}

			if (nResource == 0)
			{
				if (subpath && subpath == subpath2)
				{
					if (anchor2 >= 0 && hitdata.ctl == 0)
					{
						nResource = IDC_PENDELETE;
					}
					else if (segment2 >= 0)
					{
						nResource = IDC_PENADD;
					}
				}
			}

			if (nResource == 0)
			{
				if (subpath == NULL || m_curveDir == 0)
				{
					nResource = IDC_PENNEW;
				}
			}

			if (nResource == 0)
			{
			//	if (poly)
				{
				//	if (m_curveDir != 0)
					{
						nResource = IDC_PEN;
					}
				}
			}

			if (nResource)
			{
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource)));
				return S_OK;
			}
		}
		break;

	case ID_SVGTOOL_POLYGON:
		{
			int nResource = 0;

			CComPtr<IESelectedElement> selectedElement;
			viewGroup->GetActiveSelectedElement(&selectedElement);
			CComQIPtr<IESelectedSVGPolyElement> selectedPolyElement = selectedElement;
			CComPtr<IESVGPolyElement> poly;
			if (selectedPolyElement)
				selectedPolyElement->get_eElement((IEElement**)&poly);

			_SVGHitData hitdata;
			view->HitTest(NULL, mouse->ptx, mouse->pty, 1, &hitdata);

			long npoints2 = 0;

			CComQIPtr<IESVGPolyElement> poly2 = hitdata.element;
			VARIANT_BOOL bClosed2;

			if (poly2)
			{
				poly2->get_pointCount(&npoints2);
				poly2->IsClosed(&bClosed2);
			}

			if (poly && poly == poly2)
			{
				if (m_curveDir == -1)
				{
					if (hitdata.anchor == npoints2-1)
						nResource = IDC_PENCLOSE;
					else if (hitdata.anchor == 0)
						;//nResource = IDC_PENCHANGELAST;
				}
				else if (m_curveDir == 1)
				{
					if (hitdata.anchor == npoints2-1)
						;//nResource = IDC_PENCHANGELAST;
					else if (hitdata.anchor == 0)
						nResource = IDC_PENCLOSE;
				}
			}

			if (nResource == 0)
			{
				if (poly && poly2 && poly != poly2)
				{
					if (m_curveDir)
					{
						if (!bClosed2 && hitdata.anchor == 0 || hitdata.anchor == npoints2-1)
						{
							nResource = IDC_PENCONNECT;
						}
					}
				}
			}

			if (nResource == 0)
			{
				if (poly2 && (poly != poly2 || m_curveDir == 0))
				{
				//	if (m_curveDir == 0)
					{
						if (hitdata.anchor == 0 || hitdata.anchor == npoints2-1)
						{
							nResource = IDC_PENCONTINUE;
						}
					}
				}
			}

			if (nResource == 0)
			{
				if (poly && poly == poly2)
				{
					if (hitdata.anchor >= 0)
					{
						nResource = IDC_PENDELETE;
					}
					else if (hitdata.segment >= 0)
					{
						nResource = IDC_PENADD;
					}
				}
			}

			if (nResource == 0)
			{
				if (poly == NULL || m_curveDir == 0)
				{
					nResource = IDC_PENNEW;
				}
			}

			if (nResource == 0)
			{
			//	if (poly)
				{
				//	if (m_curveDir != 0)
					{
						nResource = IDC_PEN;
					}
				}
			}

			if (nResource)
			{
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource)));
				return S_OK;
			}
		}
		break;
	}

	return S_FALSE;
}

// Plugin
//STDMETHODIMP CPathEditPlugin::Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
//{
STDMETHODIMP CPathEditPlugin::SetSite(ILXMLEditorPluginClass* self)
{
	m_spAddinSite = self;

	if (m_spAddinSite)
	{
		CComPtr<ILXMLEditorApp> app;
		self->GetApp(&app);

		CComQIPtr<ILXAddin> lxapp = app;

		CComQIPtr<ILXAddinSite> site;
		lxapp->GetSite(&site);

		CComPtr<IUIManager> uiManager;
		site->GetUIManager((IUnknown**)&uiManager);

		app->AddTool(self, this, ID_SVGTOOL_PATHPEN, L"Pen");
		app->AddTool(self, this, ID_SVGTOOL_PATHADDANCHOR, L"Pen Add");
		app->AddTool(self, this, ID_SVGTOOL_PATHDELETEANCHOR, L"Pen Delete");
		app->AddTool(self, this, ID_SVGTOOL_PATHCORNER, L"Pen Corner");
		app->AddTool(self, this, ID_SVGTOOL_PENCIL, L"Pencil");

		app->AddTool(self, this, ID_SVGTOOL_POLYGON, L"Polygon");
	//	app->AddTool(self, this, ID_SVGTOOL_POLYLINE, L"Polyline");

		uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_PATHTOOLS);
	}

	return S_OK;
}

#if 0
STDMETHODIMP CPathEditPlugin::Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
{
	return S_OK;
}
#endif

STDMETHODIMP CPathEditPlugin::FindTool(/*[in]*/ long id, /*[out,retval]*/ ISVGTool** pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	CComObject<CPathEditTool>* pTool;
	CComObject<CPathEditTool>::CreateInstance(&pTool);
	if (pTool)
	{
		pTool->AddRef();
		pTool->m_nTool = id;

		*pVal = pTool;
	}

	return S_OK;
}

STDMETHODIMP CPathEditTool::Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, HDC hDC)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPathEditTool::OnActivate(ILXMLEditorApp* app)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPathEditTool::OnDeactivate(ILXMLEditorApp* app)
{
	m_curveDir = 0;
	m_pActivePath = NULL;

	return S_OK;
}

STDMETHODIMP CPathEditTool::Options(HWND hParent)
{
	// TODO: Add your implementation code here

	return S_OK;
}
