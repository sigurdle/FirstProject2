// SelectionToolPlugin.cpp : Implementation of CSelectionToolPlugin
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "SelectionToolPlugin.h"

#include "EXMLViewGroup.h"	// TODO Remove
#include "ESelectedSVGPathElement.h"	// TODO remove
#include "ESelectedSVGPolyElement.h"	// TODO remove
#include "ESelectedAnimationElement.h"	// TODO remove

#include "WEUndoMoveObjects.h"
//#include "WEUndoNewElement.h"

#if 0

HRESULT SVGGetLayer(ILDOMElement* element, ILDOMElement* *pVal);
COLORREF GetLayerColor(ILDOMElement* element);

HRESULT SetProperty(IUnknown* unk, BSTR name, VARIANT var);
_variant_t GetProperty(IUnknown* unk, BSTR name);

LDraw::PointD GetPathSegP2(LSVG::CLSVGPathSegList* seglist, int index)
{
	PointD P;

	CComPtr<ILSVGPathSeg> seg;
	seglist->getItem(index, &seg);

//	long numberOfItems;
//	seglist->get_numberOfItems(&numberOfItems);

	LSVGPathSegType segType;
	seg->get_pathSegType(&segType);
	
	if (segType == PATHSEG_CURVETO_CUBIC_ABS)
	{
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg0 = seg;
		seg0->get_x2(&P.X);
		seg0->get_y2(&P.Y);
	}
	else
	{
		P.X = GetProperty(seg, L"x2");
		P.Y = GetProperty(seg, L"y2");
	}

	return P;
}

PointD GetPathSegP3(ILSVGPathSegList* seglist, int index)
{
	PointD P;

	CComPtr<ILSVGPathSeg> seg;
	seglist->getItem(index, &seg);

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	if (index < numberOfItems-1)
	{
		CComPtr<ILSVGPathSeg> seg1;
		seglist->getItem(index+1, &seg1);

		LSVGPathSegType segType;
		seg1->get_pathSegType(&segType);

		if (segType > PATHSEG_MOVETO_REL)	// Still in same subpath
		{
			P.X = GetProperty(seg1, L"x1");
			P.Y = GetProperty(seg1, L"y1");

			return P;
		}
	}

	P.X = GetProperty(seg, L"x3");
	P.Y = GetProperty(seg, L"y3");

	return P;
}

double GetLineDistance(double x1, double y1, double x2, double y2);
double GetLineAngle(double distance, double x1, double y1, double x2, double y2);

double GetLineAngle(double x1, double y1, double x2, double y2);

double getRotation(ILSVGMatrix* mat)
{
	SVGPoint v0(0, 0);
	v0 = v0.matrixTransform(mat);

	SVGPoint v1(10, 0);
	v1 = v1.matrixTransform(mat);

//	gmVector2 v0 = m_matrix.transform(gmVector2(0, 0));
//	gmVector2 v1 = m_matrix.transform(gmVector2(10, 0));

	return GetLineAngle(v0.X, v0.Y, v1.X, v1.Y) * (180/M_PI);
}

HRESULT GetRefElementMatrix(ISVGView* view, ILSVGMatrix* *pVal)
{
	ASSERT(0);
#if 0
	*pVal = NULL;

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

	if (static_cast<CEXMLViewGroup*>(viewGroup.p)->m_activeReferenceElement)
	{
		CComPtr<ILDOMElement> refElement;
		static_cast<CEXMLViewGroup*>(viewGroup.p)->m_activeReferenceElement->get_domElement(&refElement);

		CComPtr<ILDOMElement> refedElement;
		static_cast<CEXMLViewGroup*>(viewGroup.p)->m_activeReferencedElement->get_domElement(&refedElement);

		CComQIPtr<ILSVGMaskElement> maskElement = refedElement;

		CComQIPtr<ILSVGLocatable> refLocatable = refElement;
		if (refLocatable)
		{
			CComPtr<ILSVGMatrix> refMatrix;
			window->svgGetScreenCTM((ILSVGElement*)refElement.p, &refMatrix);

			CComPtr<ILSVGRect> svgRect;
			window->svgGetRBBox((ILSVGElement*)refElement.p, &svgRect);
			SVGRect bbox(svgRect);

			if (maskElement)
			{
				CComPtr<ILSVGAnimatedEnumeration> acontentUnits;
				maskElement->get_maskContentUnits(&acontentUnits);

				long contentUnits;
				acontentUnits->get_baseVal(&contentUnits);

				if (contentUnits == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
				{
					CComPtr<ILSVGMatrix> mat0;
					svgsvgElement->createSVGMatrix(&mat0);

					CComPtr<ILSVGMatrix> mat1;
					mat0->scaleNonUniform(bbox.Width, bbox.Height, &mat1);

					CComPtr<ILSVGMatrix> mat2;
					mat1->translate(bbox.X, bbox.Y, &mat2);

					CComPtr<ILSVGMatrix> mat3;
					refMatrix->multiply(mat2, &mat3);
					refMatrix = mat3;
				}
			}

			//CComPtr<ILSVGMatrix> mat0;
			//ctm0->multiply(refMatrix, &mat0);
			//refMatrix = mat0;

			*pVal = refMatrix;
			(*pVal)->AddRef();
		}
	}
#endif

	return S_OK;
}

//HRESULT GetElementMatrix(IEElement* eElement, IWebXMLViewGroup* viewGroup, ILSVGMatrix* *pVal)
HRESULT GetElementMatrix(IEElement* eElement, ISVGView* view, ILSVGMatrix* *pVal)
{
	ASSERT(0);
#if 0
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILDOMDocument> domDocument;
	eDocument->get_DOMDocument(&domDocument);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	domDocument->get_documentElement((ILDOMElement**)&svgsvgElement);

//
	CComPtr<ILDOMElement> domElement;
	eElement->get_domElement(&domElement);

	if (TRUE)	// Account for animation
	{
		CComQIPtr<ILAnimationElement> animationElement = domElement;
		if (animationElement)
		{
		// Draw the animations targetElement instead of the animation element
			CComPtr<ILDOMElement> targetElement;
			animationElement->get_targetElement(&targetElement);

			domElement = targetElement;

			CComPtr<IEElement> eElement2;
			eDocument->GetEElementFromDOMElement(domElement, &eElement2);
			eElement = eElement2;
		}
	}

	CComQIPtr<ILSVGLocatable> objectTransformable = domElement;
	if (objectTransformable)
	{
		CComPtr<ILSVGMatrix> ctm0;
		window->svgGetScreenCTM2((ILSVGElement*)domElement.p, &ctm0);

		/*
		if (static_cast<CWebXMLViewGroup*>(viewGroup)->m_activeReferenceElement)
		{
			CComPtr<ILDOMElement> refElement;
			static_cast<CWebXMLViewGroup*>(viewGroup)->m_activeReferenceElement->get_domElement(&refElement);

			CComPtr<ILDOMElement> refedElement;
			static_cast<CWebXMLViewGroup*>(viewGroup)->m_activeReferencedElement->get_domElement(&refedElement);

			CComQIPtr<ILSVGMaskElement> maskElement = refedElement;

			CComQIPtr<ILSVGLocatable> refLocatable = refElement;
			if (refLocatable)
			{
				CComPtr<ILSVGMatrix> refMatrix;
				refLocatable->getScreenCTM(&refMatrix);

				CComPtr<ILSVGRect> svgRect;
				refLocatable->getRBBox(&svgRect);
				SVGRect bbox(svgRect);

				if (maskElement)
				{
					CComPtr<ILSVGAnimatedEnumeration> acontentUnits;
					maskElement->get_maskContentUnits(&acontentUnits);

					long contentUnits;
					acontentUnits->get_baseVal(&contentUnits);

					if (contentUnits == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
					{
						CComPtr<ILSVGMatrix> mat0;
						svgsvgElement->createSVGMatrix(&mat0);

						CComPtr<ILSVGMatrix> mat1;
						mat0->scaleNonUniform(bbox.Width, bbox.Height, &mat1);

						CComPtr<ILSVGMatrix> mat2;
						mat1->translate(bbox.X, bbox.Y, &mat2);

						CComPtr<ILSVGMatrix> mat3;
						ctm0->multiply(mat2, &mat3);

						ctm0 = mat3;
					}
				}

				CComPtr<ILSVGMatrix> mat0;
				ctm0->multiply(refMatrix, &mat0);
				ctm0 = mat0;
			}
		}
		*/

		CComPtr<ILSVGMatrix> refMatrix;
		GetRefElementMatrix(view, &refMatrix);
		if (refMatrix)
		{
			CComPtr<ILSVGMatrix> mat0;
			ctm0->multiply(refMatrix, &mat0);
			ctm0 = mat0;
		}

		*pVal = ctm0;
		(*pVal)->AddRef();
	}
#endif

	return S_OK;
}

void SelectRectElement(ISVGView* view, ILSVGElement* element, ILSVGRect* rect)
{
	ASSERT(0);
#if 0
	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILSVGElement> svgElement = node;
		if (svgElement)
		{
			VARIANT_BOOL bIn;
			window->SVGCheckGeometryIntersection(svgElement, rect, &bIn);
			if (bIn)
			{
				CComPtr<IEElement> eElement;
				eDocument->GetEElementFromDOMElement(svgElement, &eElement);
				viewGroup->ActivateElement(eElement, MK_SHIFT, NULL);
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CSelectionToolPlugin

STDMETHODIMP CSelectionTool::OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging)
{
	ASSERT(0);
#if 0
	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	SVGPoint pt(mouse->ptx, mouse->pty);
	SVGPoint wpt(mouse->wptx, mouse->wpty);
//	SVGPoint dpt(mouse->ptx, mouse->pty);

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> domDocument;
	eDocument->get_DOMDocument(&domDocument);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	view->GetSVGSVGElement(&svgsvgElement);

	m_dragging = 0;

	switch (m_nTool)
	{
		case ID_SVGTOOL_SELECT:
		{
			CComPtr<IESelectedElement> selectedElement;
			m_hit = HitTestActiveElement(view, mouse, &selectedElement);
			if (m_hit)
			{
			// The element is selected, but must make it the active selected element
				CComPtr<IEElement> eElement;
				selectedElement->get_eElement(&eElement);
				viewGroup->ActivateElement(eElement, 0, NULL);

				m_dragging = 1;

				*pdragging = 1;
			}
			else
			{
				_SVGHitData hitdata;
				view->HitTest(NULL, mouse->ptx, mouse->pty, 1, &hitdata);

				CComPtr<IESelectedElement> selectedElement;
				viewGroup->ActivateElement(hitdata.element, mouse->nFlags, &selectedElement);

				if (selectedElement)
				{
					::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_SELECT_SELECTED)));
					m_dragging = 1;
				}
				else
				{
					m_dragging = 2;
				}

				*pdragging = 1;

				m_hit = 1;
			}
	#if 0

			m_hit = 0;
			CElementImpl* pElement = pDocument->GetSvgElement()->GetElementUnderPoint(svgpt0, m_magnifyMatrix, m_hit);
		//	pDocument->SetTargetElement(pElement, nFlags);

			m_hit = 1;
			m_dragging = 1;

			if (pActiveElement)
			{
				if (!wcscmp(pActiveElement->m_domElement->tagName, L"motionPath"))
				{
					CAnimateMotionElement* pAnimateMotion = (CAnimateMotionElement*)pActiveElement;
				/*
					_bstr_t path = pElement->m_domElement->getAttribute(L"path");
					_bstr_t values = pElement->m_domElement->getAttribute(L"values");
					_bstr_t from = pElement->m_domElement->getAttribute(L"from");
					_bstr_t to = pElement->m_domElement->getAttribute(L"to");

					if (path.length() > 0)
					{
					}
					else if (values.length() > 0)
					{
					}
					else if (from.length() > 0 && to.length() > 0)
					{
						CArray<double,double> fromvalues;
						GetCommaSepValuesArray(CUString((BSTR)from), fromvalues);

						CArray<double,double> tovalues;
						GetCommaSepValuesArray(CUString((BSTR)to), tovalues);

						if (fromvalues.GetSize() == 2 && tovalues.GetSize() == 2)
						{
							float x = fromvalues[0];
							float y = fromvalues[1];

							float x2 = tovalues[0];
							float y2 = tovalues[1];
						}
					}
					*/
				}
				else
				{
					SVGLib::ISVGTransformablePtr locatable = pActiveElement->m_domElement;
					if (locatable)
					{
						SVGLib::_tagSVGRect rbbox = locatable->getBBox();

						RECT bbox = {rbbox.x, rbbox.y, rbbox.x + rbbox.width, rbbox.y + rbbox.height};

						if (m_hit == 2)
						{
							m_centerPt.x = bbox.right;
							m_centerPt.y = bbox.bottom;
						}
						/*
						else if (m_hit == 3)
						{
							cx = left += dx;
							bottom += dy;
						}
						else if (m_hit == 4)
						{
							left += dx;
						}
						else if (m_hit == 5)
						{
							right += dx;
							top += dy;
						}
						*/
						else if (m_hit == 6)
						{
							m_centerPt.x = bbox.left;
							m_centerPt.y = bbox.top;
						}
						/*
						else if (m_hit == 7)
						{
							right += dx;
						}
						else if (m_hit == 8)
						{
							top += dy;
						}
						else if (m_hit == 9)
						{
							bottom += dy;
						}
						*/


						m_dragging = 1;
					}
				}
			}
	#endif

			if (m_dragging)
			{
				svgsvgElement->createSVGMatrix(&m_xmat);
			}
		}
		break;

	case ID_SVGTOOL_DIRECT:
		{
			//m_hitdata = new CHitData;
			/*
			IWebElement* object;
			m_hitdata = NULL;
			GetObjectUnderPoint(dpt, m_bAlt? 3: 2, &m_hitdata, &object);
			*/

			_SVGHitData& hitdata = m_hitdata;

			{
				CComPtr<IESelectedElement> selectedElement;
				viewGroup->GetActiveSelectedElement(&selectedElement);
				CComQIPtr<IESelectedAnimationElement> selectedAnimation = selectedElement;
				if (selectedAnimation)
				{
					CComPtr<IEElement> eElement;
					selectedElement->get_eElement(&eElement);

					view->HitTest(eElement, mouse->ptx, mouse->pty, 2, &hitdata);
				}
				else
				{
					view->HitTest(NULL, mouse->ptx, mouse->pty, 2, &hitdata);
				}
			}
			
			CComPtr<IESelectedElement> selectedElement;

		// If didn't hit any path, select normal way
			// Do I need this first if (?)
			if (hitdata.anchor < 0 && hitdata.segment < 0)
			{
				viewGroup->ActivateElement(hitdata.element, mouse->nFlags, &selectedElement);
			}
			else
			{
				if (hitdata.selectedElement/*m_viewGroup->IsElementTarget(object)*//*IsPDObjectSelected(object)*/)
				{
					viewGroup->ActivateElement(hitdata.element, 0, &selectedElement);
					//SelectPDObject(object, 0, FALSE);
				}
				else
				{
					viewGroup->ActivateElement(hitdata.element, mouse->nFlags, &selectedElement);
					//SelectPDObject(object, nFlags, FALSE);
				}
			}

			CComQIPtr<IESelectedSVGPoints> selectedPoints;

			CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;
			if (selectedAnimationElement)
			{
				selectedPoints = ((CESelectedAnimationElement*)selectedAnimationElement.p)->m_selectedTargetElement;
			}
			else
			{
				selectedPoints = selectedElement;
			}

			//CComQIPtr<IESVGPathElement> path = hitdata.element;
			//CComQIPtr<IESVGPolyElement> poly = hitdata.element;

			if (hitdata.anchor >= 0)
			{
				if (hitdata.ctl == 0)	// Clicked on anchor point
				{
					if (mouse->nFlags & MK_SHIFT)
					{
						VARIANT_BOOL bAnchorSelected;
						selectedPoints->IsAnchorSelected(hitdata.anchor, &bAnchorSelected);

						// Toggle selection of anchor point
						if (bAnchorSelected)
						{
							selectedPoints->DeselectAnchor(hitdata.anchor);
						}
						else
						{
							selectedPoints->SelectAnchor(hitdata.anchor);

							m_dragging = 1;
						}
					}
					else
					{
						VARIANT_BOOL bAnchorSelected;
						selectedPoints->IsAnchorSelected(hitdata.anchor, &bAnchorSelected);

						if (!bAnchorSelected)
						{
							long nselectedCount;
							viewGroup->GetSelectedCount(&nselectedCount);

							for (int i = 0; i < nselectedCount; i++)
							{
								CComPtr<IESelectedElement> selectedElement;
								viewGroup->GetSelectedElementN(i, &selectedElement);

								CComQIPtr<IESelectedSVGPoints> selectedPoints;

								CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;
								if (selectedAnimationElement)
								{
									selectedPoints = ((CESelectedAnimationElement*)selectedAnimationElement.p)->m_selectedTargetElement;
								}
								else
								{
									selectedPoints = selectedElement;
								}

								if (selectedPoints)
								{
									selectedPoints->DeselectAllPoints();
								}
							}
				#if 0
									m_pActivePath = pPath;	// ??
									m_curveCp = hitdata.anchor;
									m_curveCtl = hitdata.ctl;
				#endif

							selectedPoints->SelectAnchor(hitdata.anchor);
						}

						m_dragging = 1;
					}
				}
				else	// Move control point
				{
			#if 0
							m_pActivePath = pPath;
							m_curveCp = hitdata.anchor;
							m_curveCtl = hitdata.ctl;
			#endif

					m_hit = 2;	//
					m_dragging = 1;
				}
			}
			else if (hitdata.segment >= 0)	// Clicked on segment
			{
				VARIANT_BOOL bSegmentSelected;
				selectedPoints->IsSegmentSelected(hitdata.segment, &bSegmentSelected);

				if (bSegmentSelected)
				{
					if (!(mouse->nFlags & MK_SHIFT))
					{
						selectedPoints->DeselectSegment(hitdata.segment);
					}
				}
				else
				{
					selectedPoints->SelectSegment(hitdata.segment);
					//m_pActivePath = pPath;	// ??
				}
			}
			else
			{
				// Direct Selection Rectangle
				m_hit = 0;
				m_dragging = 1;
			}
		}
		break;

	case ID_TOOL_TEXT:
		{
			CComPtr<IEElement> rootElement;
			view->GetEElement(&rootElement);

			CComPtr<IEElement> eElement;

			eDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"text", &eElement);
			if (eElement)
			{
				CComPtr<ILDOMElement> textElement;
				eElement->get_domElement(&textElement);

				textElement->setAttribute(L"x", _bstr_t(_variant_t(wpt.X)));
				textElement->setAttribute(L"y", _bstr_t(_variant_t(wpt.Y)));

				CComPtr<ILDOMText> text;
				domDocument->createTextNode(L"", &text);

				textElement->appendChild(text, NULL);

				{
					CComBSTR cssText;
					((CEXMLDocument*)eDocument.p)->m_defaultStyle->get_cssText(&cssText);
					if (cssText.Length())
					{
						CComPtr<ILDOMElement> element;
						eElement->get_domElement(&element);
						element->setAttribute(L"style", cssText);
					}
				}

				rootElement->appendChild(eElement);

				viewGroup->ActivateElement(eElement, 0, NULL);

				window->LocateCursor(text, 0);
			}
		}
		break;

	case ID_TOOL_TEXTPATH:
		{
			_SVGHitData hitdata;
			view->HitTest(NULL, mouse->ptx, mouse->pty, 1, &hitdata);

			if (hitdata.element)
			{
				if (hitdata.segment >= 0 || hitdata.anchor >= 0)
				{
					CComQIPtr<IESVGPathElement> ePathElement = hitdata.element;
					if (ePathElement)
					{
						CComPtr<ILDOMElement> pathElement;
						ePathElement->get_domElement(&pathElement);

						CComBSTR pathid;
						eDocument->SetElementID(pathElement, &pathid);

						if (pathid.Length())
						{
							CComPtr<IEElement> rootElement;
							view->GetEElement(&rootElement);

							CComPtr<IEElement> eElement;

							eDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"text", &eElement);
							if (eElement)
							{
								CComPtr<ILDOMElement> textElement;
								eElement->get_domElement(&textElement);

								/*
								textElement->setAttribute(L"x", _bstr_t(_variant_t(wpt.X)));
								textElement->setAttribute(L"y", _bstr_t(_variant_t(wpt.Y)));
								*/

								CComPtr<ILDOMElement> textPathElement;
								domDocument->createElementNS(L"http://www.w3.org/2000/svg", L"textPath", &textPathElement);
								if (textPathElement)
								{
								//	CComQIPtr<ILSVGURIReference> uri = textPathElement;
								//	CComPtr<ILSVG
									textPathElement->setAttributeNS(L"http://www.w3.org/1999/xlink", L"xlink:href", _bstr_t(L"#") + (BSTR)pathid);

									textElement->appendChild(textPathElement, NULL);

									CComPtr<ILDOMText> text;
									domDocument->createTextNode(L"", &text);
									if (text)
									{
										textPathElement->appendChild(text, NULL);

										{
											CComBSTR cssText;
											((CEXMLDocument*)eDocument.p)->m_defaultStyle->get_cssText(&cssText);
											if (cssText.Length())
											{
												CComPtr<ILDOMElement> element;
												eElement->get_domElement(&element);
												element->setAttribute(L"style", cssText);
											}
										}

										rootElement->appendChild(eElement);

										CComPtr<IEElement> eTextPathElement;
										eDocument->GetEElementFromDOMElement(textPathElement, &eTextPathElement);

										viewGroup->ActivateElement(eElement, 0, NULL);

										window->LocateCursor(text, 0);
									}
								}
							}
						}
					}
				}
			}
		}
		break;

	case ID_SVGTOOL_GRADIENT:
		{
			m_dragging = 1;
		}
		break;

	case ID_TOOL_HAND:
		{
			CComPtr<ILHTMLWindow> window;
			view->GetHTMLWindow(&window);

			window->get_currentTranslateX(&m_currentTranslateX);
			window->get_currentTranslateY(&m_currentTranslateY);

			::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND2)));

			m_dragging = 1;
		}
		break;

	case ID_TOOL_ZOOM:
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

			HWND hWnd;
			oleView->GetWindow(&hWnd);

			HDC hDC = ::GetDC(hWnd);
			IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
			POINT org;
			org.x = m_areaRect.left;// + /*m_offset.x*/-scrollposX;
			org.y = m_areaRect.top;// + /*m_offset.y*/-scrollposY;
			POINT oldOrg;
			SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

			int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

			m_zoomRect.left = pt.X;
			m_zoomRect.top = pt.Y;
			m_zoomRect.right = pt.X;
			m_zoomRect.bottom = pt.Y;

			Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

			SelectObject(hDC, hOldBrush);
			SetROP2(hDC, oldR2);

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			ReleaseDC(hWnd, hDC);

			m_dragging = 1;
		}
		break;
	}

	m_startpt = pt;
	m_oldpt = pt;

	m_wstartpt = wpt;
	m_woldpt = wpt;

//	m_doldpt = dpt;

	if (m_dragging)
	{
		window->captureMouse(VARIANT_TRUE);
	}

	*pdragging = m_dragging;
#endif

	return S_OK;
}

STDMETHODIMP CSelectionTool::OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	SVGPoint pt(mouse->ptx, mouse->pty);
	SVGPoint startpt = m_startpt;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> domDocument;
	eDocument->get_DOMDocument(&domDocument);

	if (m_dragging)
	{
		window->captureMouse(VARIANT_FALSE);

		switch (m_nTool)
		{
		case ID_SVGTOOL_SELECT:
			{
				if (m_dragging == 1)
				{
					if (m_hit == 1)	// Move
					{
						if (mouse->nFlags & MK_ALT)	// Duplicate
						{
							long nSelected;
							viewGroup->GetSelectedCount(&nSelected);

							CArray<IEElement*,IEElement*> elements;

							int i;

							for (i = 0; i < nSelected; i++)
							{
								CComPtr<IESelectedElement> selectedElement;
								viewGroup->GetSelectedElementN(i, &selectedElement);

								CComPtr<IEElement> eElement;
								selectedElement->get_eElement(&eElement);

								CComPtr<ILDOMElement> domElement;
								eElement->get_domElement(&domElement);

								CComQIPtr<ISVGRenderElement> svgRender = domElement;
								if (svgRender)
								{
									elements.Add(eElement);
								}
							}

							for (i = 0; i < elements.GetSize(); i++)
							{
								CComPtr<IEElement> pElement = elements[i];

								CComQIPtr<IESVGElement> svgEElement = pElement;
								if (svgEElement)
								{
									CComPtr<ILDOMElement> domElement;
									svgEElement->get_domElement(&domElement);

									CComPtr<ILDOMElement> clone;
									domElement->cloneNode(VARIANT_TRUE, (ILDOMNode**)&clone);

									if (clone)
									{
										CComPtr<ILDOMNode> parentNode;
										domElement->get_parentNode(&parentNode);

										CComPtr<ILDOMNode> nextSibling;
										domElement->get_nextSibling(&nextSibling);

										parentNode->insertBefore(clone, CComVariant(nextSibling), NULL);

										CComPtr<IEElement> eClone;
										eDocument->GetEElementFromDOMElement(clone, &eClone);

										CComQIPtr<IESVGElement> esvgClone = eClone;

										esvgClone->Move(view, 20, 20);

										viewGroup->ActivateElement(esvgClone, (i == 0)?0: MK_SHIFT, NULL);
										/*
									CComPtr<ILSVGMatrix> ictm;
									ctm->inverse(&ictm);

									SVGPoint xpt = wpt.matrixTransform(ictm);
									SVGPoint xoldpt = woldpt.matrixTransform(ictm);

									svgEElement->Move(xpt.X-xoldpt.X, xpt.Y-xoldpt.Y);
									*/
									}
								}
							}
						}
						else
						{
							if (pt.X != startpt.X || pt.Y != startpt.Y)
							{
								CComObject<CWEUndoMoveObjects>* pUndo;
								CComObject<CWEUndoMoveObjects>::CreateInstance(&pUndo);
								if (pUndo)
								{
								//	pUndo->m_dx = pt.X - startpt.X;
								//	pUndo->m_dy = pt.Y - startpt.Y;
									pUndo->m_pDocument = static_cast<CEXMLDocument*>(eDocument.p);

									//pUndo->Do(undoManager);

									long nSelected;
									viewGroup->GetSelectedCount(&nSelected);

									for (int i = 0; i < nSelected; i++)
									{
										CComPtr<IESelectedElement> selectedElement;
										viewGroup->GetSelectedElementN(i, &selectedElement);

										CComPtr<IEElement> eElement;
										selectedElement->get_eElement(&eElement);

										CComQIPtr<IESVGElement> svgEElement = eElement;
										if (svgEElement)
										{
											CComPtr<ILDOMElement> object;
											svgEElement->get_domElement(&object);

											CComPtr<ILSVGMatrix> ctm;
											//GetElementMatrix(eElement, view, &ctm);
											selectedElement->GetScreenCTM(view, &ctm);

											CComPtr<ILSVGMatrix> ictm;
											ctm->inverse(&ictm);

											SVGPoint xpt = pt.matrixTransform(ictm);
											SVGPoint xstartpt = startpt.matrixTransform(ictm);

											GUID uniqID;
											object->get_uniqID(&uniqID);

											pUndo->m_targetElements.Add(uniqID);
											pUndo->m_deltas.Add(PointD(xpt.X-xstartpt.X, xpt.Y-xstartpt.Y));

											selectedElement->Move(view, xpt.X-xstartpt.X, xpt.Y-xstartpt.Y);
										}
									}

									pUndo->m_bRedo = true;
#if 0
									pUndo->Do(pUndo->m_pDocument->m_undoManager);
#endif
								}
							}
						}
					}
					else	// Scale
					{
						CComPtr<IESelectedElement> selectedElement;
						viewGroup->GetActiveSelectedElement(&selectedElement);

						CComPtr<IEElement> eelement;
						selectedElement->get_eElement(&eelement);//= m_viewGroup->m_pActiveElement->GetElement();

						CComQIPtr<IESVGElement> esvgelement = eelement;
						if (esvgelement)
						{
							CComQIPtr<ILSVGMatrix> ctm;
							//GetElementMatrix(esvgelement, view, &ctm);
							selectedElement->GetScreenCTM(view, &ctm);

							CComQIPtr<ILSVGElement> domelement;
							eelement->get_domElement((ILDOMElement**)&domelement);

							//CComQIPtr<ILSVGTransformable> transformable = domelement;

							CComPtr<ILSVGRect> svgbounds;
							//window->svgGetRBBox(domelement, &svgbounds);
							selectedElement->GetRBBox(view, &svgbounds);
							SVGRect bounds = svgbounds;

							/*
							CComQIPtr<ILSVGMatrix> ctm;
							transformable->getScreenCTM(&ctm);

							if (static_cast<CWebXMLViewGroup*>(viewGroup.p)->m_activeReferenceElement)
							{
								CComPtr<ILDOMElement> refElement;
								static_cast<CWebXMLViewGroup*>(viewGroup.p)->m_activeReferenceElement->get_domElement(&refElement);

								CComQIPtr<ILSVGLocatable> refLocatable = refElement;
								if (refLocatable)
								{
									CComPtr<ILSVGMatrix> refMatrix;
									refLocatable->getScreenCTM(&refMatrix);

									CComPtr<ILSVGMatrix> mat0;
									ctm->multiply(refMatrix, &mat0);
									ctm = mat0;
								}
							}
							*/

							CComQIPtr<ILSVGMatrix> ictm;
							ctm->inverse(&ictm);

							SVGPoint xpt = pt.matrixTransform(ictm);
							SVGPoint xoldpt = startpt.matrixTransform(ictm);

							double left = bounds.X;
							double top = bounds.Y;
							double right = bounds.X + bounds.Width;
							double bottom = bounds.Y + bounds.Height;

						// top
							if (m_hit == 2)
							{
								left += xpt.X-xoldpt.X;
								top += xpt.Y-xoldpt.Y;
							}
							else if (m_hit == 3)
							{
								top += xpt.Y-xoldpt.Y;
							}
							else if (m_hit == 4)
							{
								right += xpt.X-xoldpt.X;
								top += xpt.Y-xoldpt.Y;
							}
						//
							else if (m_hit == 5)
							{
								right += xpt.X-xoldpt.X;
							}
							else if (m_hit == 6)
							{
								right += xpt.X-xoldpt.X;
								bottom += xpt.Y-xoldpt.Y;
							}
						//
							else if (m_hit == 7)
							{
								bottom += xpt.Y-xoldpt.Y;
							}
						//
							else if (m_hit == 8)
							{
								left += xpt.X-xoldpt.X;
								bottom += xpt.Y-xoldpt.Y;
							}
	//
							else if (m_hit == 9)
							{
								left += xpt.X-xoldpt.X;
							}

							esvgelement->Resize(view, left, top, right-left, bottom-top);
						}
					}
				}
#if 0
				else if (m_dragging == 2)	// Select rectangle
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

					HWND hWnd;
					oleView->GetWindow(&hWnd);

					HDC hDC = ::GetDC(hWnd);

					IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

					CRect oldrect(m_startpt.X, m_startpt.Y, m_oldpt.X, m_oldpt.Y);
					//CRect rect(m_startpt.x, m_startpt.y, pt.x, pt.y);

					oldrect.NormalizeRect();

					DrawFocusRect(hDC, &oldrect);

					ReleaseDC(hWnd, hDC);

				////

					CComPtr<ILSVGSVGElement> svgsvgElement;
					view->GetSVGSVGElement(&svgsvgElement);

					CComPtr<ILSVGRect> svgRect;
					svgsvgElement->createSVGRect(&svgRect);
					svgRect->put_x(m_wstartpt.X);
					svgRect->put_y(m_wstartpt.Y);
					svgRect->put_width(m_woldpt.X-m_wstartpt.X);
					svgRect->put_height(m_woldpt.Y-m_wstartpt.Y);

					SelectRectElement(view, svgsvgElement, svgRect);
				}
#endif
			}
			break;

		case ID_SVGTOOL_DIRECT:
			{
				if (m_hitdata.ctl == 0)	// Clicked on anchor point
				{
					long nselectedCount;
					viewGroup->GetSelectedCount(&nselectedCount);

					for (int i = 0; i < nselectedCount; i++)
					{
						CComPtr<IESelectedElement> selectedElement;
						viewGroup->GetSelectedElementN(i, &selectedElement);

						//CESelectedElementImpl* pSelectedElement = m_viewGroup->m_targetElements[i];
						CComPtr<IEElement> eElement;
						selectedElement->get_eElement(&eElement);

						CComPtr<ILDOMElement> pObject;
						eElement->get_domElement(&pObject);

						CComQIPtr<ILSVGElement> svgElement = pObject;

						CComPtr<ILSVGSVGElement> svgsvgElement;
						svgElement->get_ownerSVGElement(&svgsvgElement);

						//CElementImpl* pObject = pSelectedElement->GetElement();

						//Gdiplus::RectF invalidRc(999999, 999999, -999999, -999999);

						//CComQIPtr<IPDObject> object = pObject->m_object;
						//if (object)
						{
							CComPtr<ILSVGMatrix> ctm;
							GetElementMatrix(eElement, view, &ctm);

							if (ctm)
//							CComQIPtr<ILSVGTransformable> transformable = pObject;
//							if (transformable)
							{
//								CComQIPtr<ILSVGMatrix> matrix;
//								transformable->getScreenCTM(&matrix);

								CComPtr<ILSVGMatrix> ictm;
								ctm->inverse(&ictm);

								CComPtr<ILSVGPoint> svgPoint;
								svgsvgElement->createSVGPoint(&svgPoint);

								CComPtr<ILSVGPoint> xsvgPoint;

								//PointD xnewpt2;
								//inversematrix->transformPoint(&newpt2, &xnewpt2);
								svgPoint->put_x(pt.X);
								svgPoint->put_y(pt.Y);
								svgPoint->matrixTransform(ictm, &xsvgPoint);
								SVGPoint xnewpt2 = xsvgPoint;
								xsvgPoint.Release();

							//	PointD xoldpt2;
							//	inversematrix->transformPoint(&oldpt2, &xoldpt2);
								svgPoint->put_x(m_startpt.X);
								svgPoint->put_y(m_startpt.Y);
								svgPoint->matrixTransform(ictm, &xsvgPoint);
								SVGPoint xoldpt2 = xsvgPoint;
								xsvgPoint.Release();

								double xnewpt2x = xnewpt2.X;
								double xnewpt2y = xnewpt2.Y;

								double xoldpt2x = xoldpt2.X;
								double xoldpt2y = xoldpt2.Y;

								CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;
								CComQIPtr<IESelectedSVGPathElement> selectedPathElement = selectedElement;
								CComQIPtr<IESelectedSVGPolyElement> selectedPolyElement = selectedElement;

								if (selectedPathElement)
								{
									CESelectedSVGPathElement* pSelectedElement = static_cast<CESelectedSVGPathElement*>(selectedElement.p);
									pSelectedElement->MoveSelectedPoints(&m_hitdata, xnewpt2, xoldpt2/*, invalidRc,*/);
								}
								else if (selectedPolyElement)
								{
									CESelectedSVGPolyElement* pSelectedElement = static_cast<CESelectedSVGPolyElement*>(selectedElement.p);
									pSelectedElement->MoveSelectedPoints(&m_hitdata, xnewpt2, xoldpt2/*, invalidRc,*/);
								}
								else if (selectedAnimationElement)
								{
									CESelectedAnimationElement* pSelectedElement = static_cast<CESelectedAnimationElement*>(selectedElement.p);
									pSelectedElement->MoveSelectedPoints(&m_hitdata, xnewpt2, xoldpt2);
								}
							}
						}
					}
				}
				else	// Control point
				{
					CComPtr<IESelectedElement> selectedElement;
					viewGroup->GetActiveSelectedElement(&selectedElement);

					CComPtr<IEElement> eElement;
					selectedElement->get_eElement(&eElement);

					CComQIPtr<IESVGElement> esvgElement = eElement;

					CComPtr<ILDOMElement> domElement;
					eElement->get_domElement(&domElement);

					CComPtr<ILSVGMatrix> ctm;
					GetElementMatrix(eElement, view, &ctm);

					CComPtr<ILSVGMatrix> ictm;
					ctm->inverse(&ictm);

					SVGPoint xnewpt2 = pt.matrixTransform(ictm);
					SVGPoint xoldpt2 = m_startpt.matrixTransform(ictm);

					double ctlx = m_oldpt.X;
					double ctly = m_oldpt.Y;

					CComPtr<ILSVGPathSegList> seglist;

					CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;
					if (selectedAnimationElement)
					{
						CComQIPtr<ILAnimateXXX> animateXXX = domElement;

						long index;
						selectedAnimationElement->GetKeyTimeSelected(m_hitdata.selectedKeyFrameIndex, &index);

						CComPtr<ILSMILAttributeValue> attribute;
						animateXXX->GetValue(index, &attribute);

						CComPtr<IUnknown> object;
						attribute->getObject(&object);

						CComQIPtr<ILSVGPointList> points = object;
						CComQIPtr<ILSVGPathSegListValue> seglistvalue = object;

						/*
						if (points)
						{
							HRESULT hr = ((CESVGPolyElement*)((CESelectedSVGPolyElement*)m_selectedTargetElement.p)->m_pElement)->HitTest(points, view, svgsvgElement, ctm, ptx, pty, hit);
							if (hr == S_OK)
								return hr;
						}
						else if (seglistvalue)
						*/
						{
							seglistvalue->get_pathSegList(&seglist);
						}
					}
					else
					{
						CComQIPtr<ILSVGAnimatedPathData> pathData = domElement;
						pathData->get_pathSegList(&seglist);
					}

					seglist->LockUpdate();

					long numberOfItems;
					seglist->get_numberOfItems(&numberOfItems);

					CComPtr<ILSVGPathSeg> seg;
					seglist->getItem(m_hitdata.anchor, &seg);

					PointD pts[3];
				//	pts[0].X = GetProperty(seg, L"x2");
				//	pts[0].Y = GetProperty(seg, L"y2");
					pts[0] = GetPathSegP2(seglist, m_hitdata.anchor);
					pts[1].X = GetProperty(seg, L"x");
					pts[1].Y = GetProperty(seg, L"y");
					//pts[2].X = GetProperty(seg, L"x3");
					//pts[2].Y = GetProperty(seg, L"y3");
					pts[2] = GetPathSegP3(seglist, m_hitdata.anchor);
					pts[1+m_hitdata.ctl].X = ctlx;
					pts[1+m_hitdata.ctl].Y = ctly;

					double angle = GetLineAngle(ctlx, ctly, pts[1].X, pts[1].Y);
					double distance = GetLineDistance(pts[1].X, pts[1].Y, pts[1-m_hitdata.ctl].X, pts[1-m_hitdata.ctl].Y);

					pts[1-m_hitdata.ctl].X = cos(angle)*distance + pts[1].X;
					pts[1-m_hitdata.ctl].Y = sin(angle)*distance + pts[1].Y;

					SetProperty(seg, L"x2", _variant_t(pts[0].X));
					SetProperty(seg, L"y2", _variant_t(pts[0].Y));
					SetProperty(seg, L"x3", _variant_t(pts[2].X));
					SetProperty(seg, L"y3", _variant_t(pts[2].Y));

					if (m_hitdata.anchor < numberOfItems-1)
					{
						CComPtr<ILSVGPathSeg> seg;
						seglist->getItem(m_hitdata.anchor+1, &seg);

						LSVGPathSegType segType;
						seg->get_pathSegType(&segType);

						if (segType > PATHSEG_MOVETO_REL)	// Still in same subpath
						{
							SetProperty(seg, L"x1", _variant_t(pts[2].X));
							SetProperty(seg, L"y1", _variant_t(pts[2].Y));
						}
					}

					seglist->UnlockUpdate();

#if 0
					if (m_hit == 1)	// Same length
					{
						static_cast<CESVGPathElement*>(esvgElement.p)->SetControlPointsSameLength(m_hitdata.ctl/*m_curveCp*/, m_hitdata.ctl/*m_curveCtl*/, xnewpt2.X, xnewpt2.Y/*, invalidRc*/);
					}
					else if (m_hit == 2)
					{
						static_cast<CESVGPathElement*>(esvgElement.p)->SetPathSegControlPoints(m_hitdata.anchor/*m_curveCp*/, m_hitdata.ctl/*m_curveCtl*/, xnewpt2.X, xnewpt2.Y/*, invalidRc*/);
					}
					else
						ASSERT(0);
#endif
				}
			}
			break;

		case ID_SVGTOOL_GRADIENT:
			{
				long nSelected;
				viewGroup->GetSelectedCount(&nSelected);

				for (int i = 0; i < nSelected; i++)
				{
					CComPtr<IESelectedElement> selectedElement;
					viewGroup->GetSelectedElementN(i, &selectedElement);

					CComPtr<IEElement> eElement;
					selectedElement->get_eElement(&eElement);

					CComPtr<ILDOMElement> domElement;
					eElement->get_domElement(&domElement);

					CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
					if (stylable)
					{
						CComPtr<ILCSSStyleDeclaration> style;
						stylable->get_style(&style);

						CComPtr<ILSVGPaint> paint;
						style->getPropertyCSSValue(L"fill", (ILCSSValue**)&paint);
						if (paint)
						{
							//LSVGPaintType paintType;
							//paint->get_paintType(&paintType);

							CComBSTR uri;
							paint->get_uri(&uri);
							//if (paintType == 
							if (uri.Length())
							{
							//	if (((BSTR)uri)[0] == L'#')
								{
								//	BSTR uri2 = &((BSTR)uri)[1];
									BSTR uri2 = uri;

									CComPtr<ILDOMElement> uriElement;
									domDocument->getElementById(uri2, &uriElement);
									if (uriElement)
									{
										CComQIPtr<ILSVGLinearGradientElement> linearGradientElement = uriElement;
										if (linearGradientElement)
										{
											{
												CComPtr<ILSVGAnimatedLength> a;
												linearGradientElement->get_x1(&a);
												CComPtr<ILSVGLength> l;
												a->get_baseVal(&l);
												l->put_value(m_wstartpt.X);
											}
											{
												CComPtr<ILSVGAnimatedLength> a;
												linearGradientElement->get_y1(&a);
												CComPtr<ILSVGLength> l;
												a->get_baseVal(&l);
												l->put_value(m_wstartpt.Y);
											}
											{
												CComPtr<ILSVGAnimatedLength> a;
												linearGradientElement->get_x2(&a);
												CComPtr<ILSVGLength> l;
												a->get_baseVal(&l);
												l->put_value(m_woldpt.X);
											}
											{
												CComPtr<ILSVGAnimatedLength> a;
												linearGradientElement->get_y2(&a);
												CComPtr<ILSVGLength> l;
												a->get_baseVal(&l);
												l->put_value(m_woldpt.Y);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			break;

		case ID_TOOL_ZOOM:
			{
				long innerWidth;
				long innerHeight;
				window->get_innerWidth(&innerWidth);
				window->get_innerHeight(&innerHeight);

				CRect m_areaRect;
				m_areaRect.left = 0;
				m_areaRect.top = 0;
				m_areaRect.right = innerWidth;
				m_areaRect.bottom = innerHeight;

				// Erase zoomRect
				{
					CComPtr<ILHTMLActiveView> oleActiveView;
					window->GetOleView(&oleActiveView);

					CComQIPtr<IOleWindow> oleView = oleActiveView;

					HWND hWnd;
					oleView->GetWindow(&hWnd);

					HDC hDC = ::GetDC(hWnd);
					IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
					POINT org;
					org.x = m_areaRect.left;
					org.y = m_areaRect.top;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
					HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

					Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

					SelectObject(hDC, hOldBrush);
					SetROP2(hDC, oldR2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
					ReleaseDC(hWnd, hDC);
				}

				double m_magnify;
				window->get_magnify(&m_magnify);

				double aspect = (double)m_areaRect.Height()/m_areaRect.Width();

				m_zoomRect.NormalizeRect();

				if (m_zoomRect.Width() <= 2 || m_zoomRect.Height() <= 2)
				{
					double x = m_startpt.X;
					double y = m_startpt.Y;

					if (!(mouse->nFlags & MK_ALT))	// Zoom in
					{
						ZoomToRect2(view,
							x-m_areaRect.Width()/4.0,
							y-m_areaRect.Height()/4.0,
							x+m_areaRect.Width()/4.0,
							y+m_areaRect.Height()/4.0);
					}
					else	// Zoom out
					{
						ZoomToRect2(view,
							x-m_areaRect.Width(),
							y-m_areaRect.Height(),
							x+m_areaRect.Width(),
							y+m_areaRect.Height());
					}
				}
				else
				{
					ZoomToRect2(view,
						m_zoomRect.left,
						m_zoomRect.top,
						m_zoomRect.right,
						m_zoomRect.bottom);
				}
			}
			break;
		}

		m_dragging = 0;
		m_xmat.Release();
	}
#endif

	return S_OK;
}

STDMETHODIMP CSelectionTool::OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	SVGPoint pt(mouse->ptx, mouse->pty);
	SVGPoint oldpt = m_oldpt;

	/*
	SVGPoint wpt(mouse->wptx, mouse->wpty);
	SVGPoint dpt(mouse->dptx, mouse->dpty);
	SVGPoint woldpt = m_woldpt;
	*/

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	view->GetSVGSVGElement(&svgsvgElement);

	CComPtr<IHTMLPaintSite> paintSite;
	view->GetPaintSite(&paintSite);

	if (m_dragging)
	{
		switch (m_nTool)
		{
		case ID_SVGTOOL_SELECT:
			{
	/*					if (m_numMoves == 0)
				{
					if (pDocument->m_bSourceEditLast)
					{
					// Remember the source text before any changes to the DOM occurs
						CComQIPtr<ITextData> textDocument;
						m_pDocument->get_textDocument(&textDocument);
						BSTR p; textDocument->get_data(&p);
						m_sourceText = SysAllocString(p);	// Make a copy
					}
				}
	*/

				if (m_dragging == 1)
				{
					if (m_hit >= 2)	// Scale object
					{
						CComPtr<IESelectedElement> selectedElement;
						viewGroup->GetActiveSelectedElement(&selectedElement);

						CComPtr<IEElement> eelement;
						selectedElement->get_eElement(&eelement);//= m_viewGroup->m_pActiveElement->GetElement();

						CComQIPtr<IESVGElement> esvgelement = eelement;
						if (esvgelement)
						{
							CComQIPtr<ILSVGMatrix> ctm;
							//GetElementMatrix(esvgelement, view, &ctm);
							selectedElement->GetScreenCTM(view, &ctm);

							CComQIPtr<ILSVGElement> domelement;
							eelement->get_domElement((ILDOMElement**)&domelement);

							//CComQIPtr<ILSVGTransformable> transformable = domelement;

							CComPtr<ILSVGRect> svgbounds;
							//window->svgGetRBBox(domelement, &svgbounds);
							selectedElement->GetRBBox(view, &svgbounds);
							SVGRect bounds = svgbounds;

							/*
							CComQIPtr<ILSVGMatrix> ctm;
							transformable->getScreenCTM(&ctm);

							if (static_cast<CWebXMLViewGroup*>(viewGroup.p)->m_activeReferenceElement)
							{
								CComPtr<ILDOMElement> refElement;
								static_cast<CWebXMLViewGroup*>(viewGroup.p)->m_activeReferenceElement->get_domElement(&refElement);

								CComQIPtr<ILSVGLocatable> refLocatable = refElement;
								if (refLocatable)
								{
									CComPtr<ILSVGMatrix> refMatrix;
									refLocatable->getScreenCTM(&refMatrix);

									CComPtr<ILSVGMatrix> mat0;
									ctm->multiply(refMatrix, &mat0);
									ctm = mat0;
								}
							}
							*/

							CComQIPtr<ILSVGMatrix> ictm;
							ctm->inverse(&ictm);

							SVGPoint xpt = pt.matrixTransform(ictm);
							SVGPoint xoldpt = m_startpt.matrixTransform(ictm);

							double left = bounds.X;
							double top = bounds.Y;
							double right = bounds.X + bounds.Width;
							double bottom = bounds.Y + bounds.Height;

						// top
							if (m_hit == 2)
							{
								left += xpt.X-xoldpt.X;
								top += xpt.Y-xoldpt.Y;
							}
							else if (m_hit == 3)
							{
								top += xpt.Y-xoldpt.Y;
							}
							else if (m_hit == 4)
							{
								right += xpt.X-xoldpt.X;
								top += xpt.Y-xoldpt.Y;
							}
						//
							else if (m_hit == 5)
							{
								right += xpt.X-xoldpt.X;
							}
							else if (m_hit == 6)
							{
								right += xpt.X-xoldpt.X;
								bottom += xpt.Y-xoldpt.Y;
							}
						//
							else if (m_hit == 7)
							{
								bottom += xpt.Y-xoldpt.Y;
							}
						//
							else if (m_hit == 8)
							{
								left += xpt.X-xoldpt.X;
								bottom += xpt.Y-xoldpt.Y;
							}
	//
							else if (m_hit == 9)
							{
								left += xpt.X-xoldpt.X;
							}

							SVGRect newbounds(left, top, right-left, bottom-top);

							CComPtr<ILSVGMatrix> mat0;
							svgsvgElement->createSVGMatrix(&mat0);
						
							CComPtr<ILSVGMatrix> mat1;
							mat0->translate(-bounds.X, -bounds.Y, &mat1);

							CComPtr<ILSVGMatrix> mat2;
							mat1->scaleNonUniform(newbounds.Width/bounds.Width, newbounds.Height/bounds.Height, &mat2);

							CComPtr<ILSVGMatrix> mat3;
							mat2->translate(newbounds.X, newbounds.Y, &mat3);

						//	CComPtr<ILSVGMatrix> mat4;
						//	mat3->inverse(&mat4);

							m_xmat = mat3;

							paintSite->InvalidateRect(NULL);
						}
					}
					else	// Move object(s)
					{
					//	Gdiplus::RectF totalrc(999999, 999999, -999999, -999999);

						CComPtr<ILSVGMatrix> mat;
						svgsvgElement->createSVGMatrix(&mat);
						
						CComPtr<ILSVGMatrix> xmat;
						mat->translate(pt.X-m_startpt.X, pt.Y-m_startpt.Y, &xmat);
						m_xmat = xmat;

						paintSite->InvalidateRect(NULL);
					}
				}
				else if (m_dragging == 2)	// Select rectangle
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

					HWND hWnd;
					oleView->GetWindow(&hWnd);

					HDC hDC = ::GetDC(hWnd);

					IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

				/*
					HDC hDC = GetDC();
					POINT org;
					org.x = m_areaRect.left -scrollposX;
					org.y = m_areaRect.top -scrollposY;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);
					*/

					CRect oldrect(m_startpt.X, m_startpt.Y, m_oldpt.X, m_oldpt.Y);
					CRect rect(m_startpt.X, m_startpt.Y, pt.X, pt.Y);

					oldrect.NormalizeRect();
					rect.NormalizeRect();

					DrawFocusRect(hDC, &oldrect);
					DrawFocusRect(hDC, &rect);

					ReleaseDC(hWnd, hDC);
				}
			}
			break;

		case ID_SVGTOOL_DIRECT:
			{
				if (m_hitdata.ctl == 0)	// Clicked on anchor point
				{
				}
				else	// Control point
				{
					CComPtr<IESelectedElement> selectedElement;
					viewGroup->GetActiveSelectedElement(&selectedElement);

					CComPtr<IEElement> eElement;
					selectedElement->get_eElement(&eElement);

					CComQIPtr<IESVGElement> esvgElement = eElement;

					CComPtr<ILDOMElement> domElement;
					eElement->get_domElement(&domElement);

					CComPtr<ILSVGMatrix> ctm;
					GetElementMatrix(eElement, view, &ctm);

					CComPtr<ILSVGMatrix> ictm;
					ctm->inverse(&ictm);

					SVGPoint xnewpt2 = pt.matrixTransform(ictm);
					SVGPoint xoldpt2 = oldpt.matrixTransform(ictm);

					paintSite->InvalidateRect(NULL);

#if 0
					if (m_hit == 1)	// Same length
					{
						static_cast<CESVGPathElement*>(esvgElement.p)->SetControlPointsSameLength(m_hitdata.ctl/*m_curveCp*/, m_hitdata.ctl/*m_curveCtl*/, xnewpt2.X, xnewpt2.Y/*, invalidRc*/);
					}
					else if (m_hit == 2)
					{
						static_cast<CESVGPathElement*>(esvgElement.p)->SetPathSegControlPoints(m_hitdata.anchor/*m_curveCp*/, m_hitdata.ctl/*m_curveCtl*/, xnewpt2.X, xnewpt2.Y/*, invalidRc*/);
					}
					else
						ASSERT(0);
#endif
				}
			}
			break;

		case ID_SVGTOOL_GRADIENT:
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

				HWND hWnd;
				oleView->GetWindow(&hWnd);

				HDC hDC = ::GetDC(hWnd);
				IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

			// Erase old line
				MoveToEx(hDC, m_startpt.X, m_startpt.Y, NULL);
				LineTo(hDC, m_oldpt.X, m_oldpt.Y);

			// Draw new line
				MoveToEx(hDC, m_startpt.X, m_startpt.Y, NULL);
				LineTo(hDC, pt.X, pt.Y);

				SetROP2(hDC, oldR2);

				ReleaseDC(hWnd, hDC);
			}
			break;

		case ID_TOOL_HAND:
			{
				m_currentTranslateX -= m_oldpt.X - pt.X;
				m_currentTranslateY -= m_oldpt.Y - pt.Y;

				window->setCurrentTranslate(m_currentTranslateX, m_currentTranslateY);
			}
			break;

		case ID_TOOL_ZOOM:
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

				HWND hWnd;
				oleView->GetWindow(&hWnd);

				HDC hDC = ::GetDC(hWnd);
				IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
				POINT org;
				org.x = m_areaRect.left;// + /*m_offset.x*/-scrollposX;
				org.y = m_areaRect.top;// + /*m_offset.y*/-scrollposY;
				POINT oldOrg;
				SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

			// Erase old zoomrect
				Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

				double aspect = (double)m_areaRect.Height()/m_areaRect.Width();

				m_zoomRect.left = m_startpt.X;
				m_zoomRect.top = m_startpt.Y;
				if ((double)abs(pt.X-m_startpt.X)/m_areaRect.Width() > (double)abs(pt.Y-m_startpt.Y)/m_areaRect.Height())
				{
					double aspect = (double)m_areaRect.Height()/m_areaRect.Width();
					m_zoomRect.right = pt.X;
					m_zoomRect.bottom = m_startpt.Y + (pt.X-m_startpt.X)*aspect;
				}
				else
				{
					double aspect = (double)m_areaRect.Width()/m_areaRect.Height();
					m_zoomRect.right = m_startpt.X + (pt.Y-m_startpt.Y)*aspect;
					m_zoomRect.bottom = pt.Y;
				}

			// Draw new zoomrect
				Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

				SelectObject(hDC, hOldBrush);
				SetROP2(hDC, oldR2);

				SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
				ReleaseDC(hWnd, hDC);
			}
			break;
		}
	}

//	m_doldpt = dpt;
//	m_woldpt = wpt;
	m_oldpt = pt;
#endif

	return S_OK;
}

int CSelectionTool::HitTestActiveElement(ISVGView* view, SVGMouse* mouse, IESelectedElement* *pVal)
{
	ASSERT(pVal != NULL);
	*pVal = NULL;

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> domDocument;
	eDocument->get_DOMDocument(&domDocument);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	domDocument->get_documentElement((ILDOMElement**)&svgsvgElement);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

//	CComPtr<ILSVGMatrix> viewMatrix;
//	view->GetViewMatrix(&viewMatrix);

	long count;
	viewGroup->GetSelectedCount(&count);

	for (int i = 0; i < count; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		viewGroup->GetSelectedElementN(i, &selectedElement);

		/*
		CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;
		if (selectedAnimationElement)
		{
			CComPtr<ILDOMElement> targetElement;
			// TODO
		}
		*/

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<IESelectedElement> selectedTargetElement;

		if (TRUE)	// Account for animation
		{
			CComQIPtr<ILAnimationElement> animationElement = domElement;
			if (animationElement)
			{
				selectedTargetElement = static_cast<CESelectedAnimationElement*>(selectedElement.p)->m_selectedTargetElement;
				if (selectedTargetElement)
				{
					//CComPtr<ILDOMElement> targetElement;
					//animationElement->get_targetElement(&targetElement);

					eElement.Release();
					selectedTargetElement->get_eElement(&eElement);

					domElement.Release();
					eElement->get_domElement(&domElement);
					//selected
					//eDocument->GetEElementFromDOMElement(domElement, &eElement);
				}
			}
			else
				selectedTargetElement = selectedElement;
		}

		if (selectedTargetElement)
		{
			CComPtr<ILSVGMatrix> ctm0;
			//GetElementMatrix(eElement, view, &ctm0);
			selectedTargetElement->GetScreenCTM(view, &ctm0);
			if (ctm0)
			{
				CComQIPtr<ILSVGElement> svgElement = domElement;

				CComPtr<ILSVGMatrix> ctm = ctm0;
				//ctm0->multiply(viewMatrix, &ctm);

				CComQIPtr<IESVGElement> esvgElement = eElement;

				if (esvgElement)
				{
					long resizability;
					esvgElement->GetResizability(&resizability);

					CComPtr<ILSVGRect> svgbounds;
					//window->svgGetRBBox(svgElement, &svgbounds);
					selectedTargetElement->GetRBBox(view, &svgbounds);

					SVGRect bounds = svgbounds;

					SVGPoint pts[9] =
					{
						SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height/2),	// center point

						SVGPoint(bounds.X, bounds.Y),
						SVGPoint(bounds.X+bounds.Width/2, bounds.Y),
						SVGPoint(bounds.X+bounds.Width, bounds.Y),
						SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
						SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height),
						SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
						SVGPoint(bounds.X, bounds.Y+bounds.Height),
						SVGPoint(bounds.X, bounds.Y+bounds.Height/2),
					};

					int count = (resizability == 1)? 9: 1;

					for (int i = 0; i < count; i++)
					{
						SVGPoint xpt = pts[i].matrixTransform(ctm);

						if (fabs(mouse->ptx - xpt.X) < 4 && fabs(mouse->pty - xpt.Y) < 4)
						{
							*pVal = selectedElement;
							(*pVal)->AddRef();
							return i+1;
						}
					}
				}
			}
		}
	}

	return 0;
}

STDMETHODIMP CSelectionTool::OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	switch (m_nTool)
	{
	case ID_SVGTOOL_SELECT:
		{
			int nResource = 0;

			CComPtr<IESelectedElement> selectedElement;
			int nhit = HitTestActiveElement(view, mouse, &selectedElement);

			if (selectedElement)
			{
				ASSERT(nhit >= 0);

				CComPtr<IEElement> eElement;
				selectedElement->get_eElement(&eElement);

				CComPtr<ILDOMElement> domElement;
				eElement->get_domElement(&domElement);

				CComPtr<ILSVGMatrix> ctm;
				//window->svgGetScreenCTM2((ILSVGElement*)domElement.p, &ctm);
				selectedElement->GetScreenCTM(view, &ctm);

				if (nhit >= 2)
				{
					double angle = getRotation(ctm);

					switch (nhit)
					{
					case 2: angle -= 45; break;
					case 3: angle += 0; break;
					case 4: angle += 45; break;
					case 5: angle += 90; break;
					case 6: angle += 135; break;
					case 7: angle += 180; break;
					case 8: angle += 225; break;
					case 9: angle += 270; break;
					}

					if (angle < 0) angle += 360;
					if (angle >= 360) angle -= 360;

					UINT nCursors[8] =
					{
						IDC_SIZE_NS,
						IDC_SIZE_NESW,
						IDC_SIZE_WE,
						IDC_SIZE_NWSE,
						IDC_SIZE_NS,
						IDC_SIZE_NESW,
						IDC_SIZE_WE,
						IDC_SIZE_NWSE,
					};

					if (angle < 22.5)			nResource = nCursors[0];
					else if (angle < 45)		nResource = nCursors[1];
					else if (angle < 67.5)	nResource = nCursors[1];
					else if (angle < 90)		nResource = nCursors[2];
					else if (angle < 112.5)	nResource = nCursors[2];
					else if (angle < 135)	nResource = nCursors[3];
					else if (angle < 157.5)	nResource = nCursors[3];
					else if (angle < 180)	nResource = nCursors[4];
					else if (angle < 202.5)	nResource = nCursors[4];
					else if (angle < 225)	nResource = nCursors[5];
					else if (angle < 247.5)	nResource = nCursors[5];
					else if (angle < 270)	nResource = nCursors[6];
					else if (angle < 292.5)	nResource = nCursors[6];
					else if (angle < 315)	nResource = nCursors[7];
					else if (angle < 337.5)	nResource = nCursors[7];
					else if (angle < 360)	nResource = nCursors[0];
					else
						ASSERT(0);
				}
				else if (nhit == 1)
				{
					if (mouse->nFlags & MK_ALT)
						nResource = IDC_SELECT_DUPLICATE;
					else
						nResource = IDC_SELECT_SELECTED;
				}
			}
			else
			{
				_SVGHitData hitdata;
				view->HitTest(NULL, mouse->ptx, mouse->pty, 1, &hitdata);

				if (hitdata.element)
				{
					CComPtr<IESelectedElement> selectedElement;
					viewGroup->GetSelectedElement(hitdata.element, &selectedElement);

					if (selectedElement)
					{
						if (mouse->nFlags & MK_ALT)
							nResource = IDC_SELECT_DUPLICATE;
						else
							nResource = IDC_SELECT_SELECTED;
					}
					else
					{
						nResource = IDC_SELECT_UNSELECTED;
					}
				}
				else
				{
					nResource = IDC_SELECT;
				}
			}

			if (nResource)
			{
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource)));
				return S_OK;
			}
		}
		break;

	case ID_SVGTOOL_DIRECT:
		{
			int nResource = 0;

			_SVGHitData hitdata;

			CComPtr<IESelectedElement> selectedElement;
			viewGroup->GetActiveSelectedElement(&selectedElement);
			CComQIPtr<IESelectedAnimationElement> selectedAnimation = selectedElement;
			if (selectedAnimation)
			{
				CComPtr<IEElement> eElement;
				selectedElement->get_eElement(&eElement);

				view->HitTest(eElement, mouse->ptx, mouse->pty, 2, &hitdata);
			}
			else
			{
				view->HitTest(NULL, mouse->ptx, mouse->pty, 2, &hitdata);
			}

			if (hitdata.anchor >= 0)
			{
				if (hitdata.ctl == 0)
					nResource = IDC_DIRECT_SELECTEDANCHOR;
				else
					nResource = IDC_DIRECT_SELECTEDCONTROL;
			}
			else if (hitdata.segment >= 0)
			{
				nResource = IDC_DIRECT_SELECTEDSEGMENT;
			}
			else
			{
				nResource = IDC_DIRECT;
			}

			if (nResource)
			{
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource)));
				return S_OK;
			}
		}
		break;

	case ID_TOOL_TEXT:
		{
			int nResource = IDC_TEXTNEW;

			_SVGHitData hitdata;
			view->HitTest(NULL, mouse->ptx, mouse->pty, 2, &hitdata);

			if (hitdata.element)
			{
				CComPtr<ILDOMElement> element;
				hitdata.element->get_domElement(&element);

				CComQIPtr<ILSVGTextContentElement> textContent = element;
				if (textContent)
				{
					nResource = 0;
				}
			}

			if (nResource)
			{
				MessageBeep(-1);
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource)));
				return S_OK;
			}
		}
		break;

	case ID_TOOL_TEXTPATH:
		{
			int nResource = IDC_TEXTPATH;

			_SVGHitData hitdata;
			view->HitTest(NULL, mouse->ptx, mouse->pty, 1, &hitdata);

			if (hitdata.element)
			{
				if (hitdata.segment >= 0 || hitdata.anchor >= 0)
				{
					nResource = IDC_TEXTPATHPLUS;
				}
			}

			if (nResource)
			{
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource)));
				return S_OK;
			}
		}
		break;

	case ID_TOOL_HAND:
		{
			::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND0)));

			return S_OK;
		}
		break;

	case ID_TOOL_ZOOM:
		{
			if (mouse->nFlags & MK_ALT)
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_ZOOMOUT)));
			else
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_ZOOMIN)));

			return S_OK;
		}
		break;
	}

	return S_FALSE;
}

#if 0
RectD CalculateFilterRegion(ILSVGFilterElement* filterElement, ILSVGElement* referencingElement)
{
	ASSERT(pReferencingElement != NULL);

	CLSVGFilterElement* psvgElement = static_cast<CLSVGFilterElement*>(m_pNode);

	CLSVGLength* xLength = psvgElement->m_x->m_animated->m_animVal->m_value;
	CLSVGLength* yLength = psvgElement->m_y->m_animated->m_animVal->m_value;
	CLSVGLength* widthLength = psvgElement->m_width->m_animated->m_animVal->m_value;
	CLSVGLength* heightLength = psvgElement->m_height->m_animated->m_animVal->m_value;

	RectD rect;

	if (psvgElement->m_filterUnits->m_animated->m_animVal->m_value->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
	{
		rect = pReferencingElement->m_bounds;
	}
	else	// SVG_UNIT_TYPE_USERSPACEONUSE
	{
		rect = pReferencingElement->GetViewportElement()->GetViewBox();
	}

	RectD filterRegion;

	if (xLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		filterRegion.X = rect.X + (xLength->m_valueInSpecifiedUnits * rect.Width/100);
	else
		filterRegion.X = xLength->m_value;

	if (yLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		filterRegion.Y = rect.Y + (yLength->m_valueInSpecifiedUnits * rect.Height/100);
	else
		filterRegion.Y = yLength->m_value;

	if (widthLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		filterRegion.Width = (widthLength->m_valueInSpecifiedUnits * rect.Width/100);
	else
		filterRegion.Width = widthLength->m_value;

	if (heightLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		filterRegion.Height = (heightLength->m_valueInSpecifiedUnits * rect.Height/100);
	else
		filterRegion.Height = heightLength->m_value;

	return filterRegion;
}
#endif

double GetSVGLengthValue(ILSVGLength* length, double total)
{
	LSVGLengthType unit;
	length->get_unitType(&unit);

	if (unit == SVG_LENGTHTYPE_PERCENTAGE)
	{
		double specified;
		length->get_valueInSpecifiedUnits(&specified);

		return specified*total/100;
	}
	else
	{
		double value;
		length->get_value(&value);
		return value;
	}
}

STDMETHODIMP CSelectionTool::Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, HDC hDC)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> domDocument;
	eDocument->get_DOMDocument(&domDocument);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	domDocument->get_documentElement((ILDOMElement**)&svgsvgElement);

	Gdiplus::Graphics graphics(hDC);

	if (m_nTool == ID_SVGTOOL_SELECT)
	{
		/*	// No need ?
		CComPtr<ILSVGMatrix> m_viewMatrix;
		view->GetViewMatrix(&m_viewMatrix);
		*/

		CComPtr<IEElement> refedEElement = static_cast<CEXMLViewGroup*>(viewGroup.p)->m_activeReferencedElement;
		CComPtr<IEElement> refEElement = static_cast<CEXMLViewGroup*>(viewGroup.p)->m_activeReferenceElement;

		if (refedEElement && refEElement)
		{
			//ASSERT(refEElement);

			CComPtr<ILDOMElement> refedElement;
			refedEElement->get_domElement(&refedElement);

			CComPtr<ILDOMElement> refElement;
			refEElement->get_domElement(&refElement);
			CComQIPtr<ILSVGElement> refsvgElement = refElement;

			CComQIPtr<ILSVGFilterElement> filterElement = refedElement;
			CComQIPtr<ILSVGMaskElement> maskElement = refedElement;

			if (filterElement)
			{
				/*
				CComPtr<ILSVGAnimatedLength> alength;
				filterElement->get_x(&alength);

				CComPtr<ILSVGLength> x;
				alength->get_baseVal(&x);
				*/

				CComPtr<ILSVGRect> svgRect;
				window->svgGetFilterRegion(refsvgElement, &svgRect);
				//SVGRect filterRect = svgRect;

				{
					CComPtr<ILDOMElement> layer;
					SVGGetLayer(refElement, &layer);

					COLORREF layerColorRef = GetLayerColor(layer);
					Gdiplus::Color layerColor(GetRValue(layerColorRef), GetGValue(layerColorRef), GetBValue(layerColorRef));

					Gdiplus::Pen pen(layerColor);

					CComQIPtr<ILSVGLocatable> locatable = refElement;

					// Draw bounding box
					if (locatable)
					{
						/*
						CComPtr<ILSVGRect> svgbounds;
						window->svgGetRBBox(static_cast<ILSVGElement*>(domElement.p), &svgbounds);
						*/

						CComPtr<ILSVGMatrix> ctm0;
						//locatable->getScreenCTM(&ctm0);
						window->svgGetScreenCTM(CComQIPtr<ILSVGElement>(refElement), &ctm0);

						CComPtr<ILSVGMatrix> ctm = ctm0;
						//ctm0->multiply(m_viewMatrix, &ctm);

						SVGRect bounds = svgRect;

						SVGPoint pts[9] =
						{
							SVGPoint(bounds.X, bounds.Y),
							SVGPoint(bounds.X+bounds.Width/2, bounds.Y),
							SVGPoint(bounds.X+bounds.Width, bounds.Y),
							SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
							SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height),
							SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
							SVGPoint(bounds.X, bounds.Y+bounds.Height),
							SVGPoint(bounds.X, bounds.Y+bounds.Height/2),

							SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height/2),	// center point
						};

						Gdiplus::PointF xpts[9];

						for (int i = 0; i < 9; i++)
						{
							/*
							CComPtr<ILSVGPoint> svgPoint;
							svgsvgElement->createSVGPoint(&svgPoint);
							svgPoint->put_x(pts[i].X);
							svgPoint->put_y(pts[i].Y);

							CComPtr<ILSVGPoint> xsvgPoint;
							svgPoint->matrixTransform(ctm, &xsvgPoint);

							xpts[i] = SVGPoint(xsvgPoint);
							*/
							xpts[i] = pts[i].matrixTransform(ctm);
						}
						
						// Outline
						graphics.DrawLine(&pen, xpts[0], xpts[2]);
						graphics.DrawLine(&pen, xpts[2], xpts[4]);
						graphics.DrawLine(&pen, xpts[4], xpts[6]);
						graphics.DrawLine(&pen, xpts[6], xpts[0]);
					}
				}

				return 0;
			}
			else if (maskElement)
			{
				CComPtr<ILSVGAnimatedEnumeration> amaskUnits;
				maskElement->get_maskUnits(&amaskUnits);

				long maskUnits;
				amaskUnits->get_baseVal(&maskUnits);

				CComPtr<ILSVGAnimatedLength> ax; maskElement->get_x(&ax);
				CComPtr<ILSVGLength> x; ax->get_baseVal(&x);

				CComPtr<ILSVGAnimatedLength> ay; maskElement->get_y(&ay);
				CComPtr<ILSVGLength> y; ay->get_baseVal(&y);

				CComPtr<ILSVGAnimatedLength> awidth; maskElement->get_width(&awidth);
				CComPtr<ILSVGLength> width; awidth->get_baseVal(&width);

				CComPtr<ILSVGAnimatedLength> aheight; maskElement->get_height(&aheight);
				CComPtr<ILSVGLength> height; aheight->get_baseVal(&height);

				SVGRect rect;

				if (maskUnits == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
				{
					CComPtr<ILSVGRect> svgRect;
					window->svgGetRBBox(refsvgElement, &svgRect);
					rect = svgRect;
				}
				else if (maskUnits == SVG_UNIT_TYPE_USERSPACEONUSE)
				{
					CComPtr<ILSVGElement> viewportElement;
					refsvgElement->get_viewportElement(&viewportElement);
				//	ASSERT(0);
					//rect = pReferencingElement->GetViewportElement()->GetViewBox();

					CComPtr<ILSVGRect> svgRect;
					window->svgGetRBBox(viewportElement, &svgRect);
					rect = svgRect;
				}
				else
					ASSERT(0);

				SVGRect maskRegion;

				if (SVGLength(x).GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
					maskRegion.X = rect.X + (SVGLength(x).GetValueInSpecifiedUnits() * rect.Width/100);
				else
					maskRegion.X = SVGLength(x).GetValue();

				if (SVGLength(y).GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
					maskRegion.Y = rect.Y + (SVGLength(y).GetValueInSpecifiedUnits() * rect.Height/100);
				else
					maskRegion.Y = SVGLength(y).GetValue();

				if (SVGLength(width).GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
					maskRegion.Width = (SVGLength(width).GetValueInSpecifiedUnits() * rect.Width/100);
				else
					maskRegion.Width = SVGLength(width).GetValue();

				if (SVGLength(height).GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
					maskRegion.Height = (SVGLength(height).GetValueInSpecifiedUnits() * rect.Height/100);
				else
					maskRegion.Height = SVGLength(height).GetValue();

			//////////

				CComPtr<ILDOMElement> refElement;
				refEElement->get_domElement(&refElement);

				CComPtr<ILDOMElement> layer;
				SVGGetLayer(refElement, &layer);

				COLORREF layerColorRef = GetLayerColor(layer);
				Gdiplus::Color layerColor(GetRValue(layerColorRef), GetGValue(layerColorRef), GetBValue(layerColorRef));

				Gdiplus::Pen pen(layerColor);

				CComQIPtr<ILSVGLocatable> locatable = refElement;

				// Draw bounding box
				if (locatable)
				{
					/*
					CComPtr<ILSVGRect> svgbounds;
					window->svgGetRBBox(static_cast<ILSVGElement*>(domElement.p), &svgbounds);
					*/

					CComPtr<ILSVGMatrix> ctm0;
					//locatable->getScreenCTM(&ctm0);
					window->svgGetScreenCTM2(CComQIPtr<ILSVGElement>(refElement), &ctm0);

					CComPtr<ILSVGMatrix> ctm = ctm0;
					//ctm0->multiply(m_viewMatrix, &ctm);

					SVGRect bounds = maskRegion;

					SVGPoint pts[9] =
					{
						SVGPoint(bounds.X, bounds.Y),
						SVGPoint(bounds.X+bounds.Width/2, bounds.Y),
						SVGPoint(bounds.X+bounds.Width, bounds.Y),
						SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
						SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height),
						SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
						SVGPoint(bounds.X, bounds.Y+bounds.Height),
						SVGPoint(bounds.X, bounds.Y+bounds.Height/2),

						SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height/2),	// center point
					};

					Gdiplus::PointF	xpts[9];

					for (int i = 0; i < 9; i++)
					{
						CComPtr<ILSVGPoint> svgPoint;
						svgsvgElement->createSVGPoint(&svgPoint);
						svgPoint->put_x(pts[i].X);
						svgPoint->put_y(pts[i].Y);

						CComPtr<ILSVGPoint> xsvgPoint;
						svgPoint->matrixTransform(ctm, &xsvgPoint);

						xpts[i] = SVGPoint(xsvgPoint);
					}
					
					// Outline
					graphics.DrawLine(&pen, xpts[0], xpts[2]);
					graphics.DrawLine(&pen, xpts[2], xpts[4]);
					graphics.DrawLine(&pen, xpts[4], xpts[6]);
					graphics.DrawLine(&pen, xpts[6], xpts[0]);
				}
			}
		}

		long count;
		viewGroup->GetSelectedCount(&count);

		for (int i = 0; i < count; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			if (TRUE)	// Account for animation
			{
				CComQIPtr<ILAnimationElement> animationElement = domElement;
				CComQIPtr<ILSVGAnimateMotionElement> animateMotion = domElement;
				if (animationElement != NULL && animateMotion == NULL)
				{
				// Draw the animations targetElement instead of the animation element
					CComPtr<ILDOMElement> targetElement;
					animationElement->get_targetElement(&targetElement);

					domElement = targetElement;

					eElement.Release();
					eDocument->GetEElementFromDOMElement(domElement, &eElement);
				}
			}

			if (domElement)
			{
				CComPtr<ILDOMElement> layer;
				SVGGetLayer(domElement, &layer);

				COLORREF layerColorRef = GetLayerColor(layer);
				Gdiplus::Color layerColor(GetRValue(layerColorRef), GetGValue(layerColorRef), GetBValue(layerColorRef));

				Gdiplus::Pen pen(layerColor);
				Gdiplus::SolidBrush brush(layerColor);

				CComPtr<ILSVGMatrix> ctm0;
		//		GetElementMatrix(eElement, view, &ctm0);
				selectedElement->GetScreenCTM(view, &ctm0);

				if (ctm0)
				{
					CComPtr<ILSVGMatrix> ctm;
					//ctm0->multiply(m_viewMatrix, &ctm);

					if (m_dragging == 1/* && m_hit == 1*/)
					{
						if (m_hit >= 2)	// Scale
						{
							CComPtr<IESelectedElement> activeSelectedElement;
							viewGroup->GetActiveSelectedElement(&activeSelectedElement);

							if (activeSelectedElement == selectedElement)
							{
								m_xmat->multiply(ctm0, &ctm);
							}
							else
							{
								ctm = ctm0;
							}
						}
						else	// Move
						{
							//ctm0->translate(m_oldpt.X-m_startpt.X, m_oldpt.Y-m_startpt.Y, &ctm);
							ctm0->multiply(m_xmat, &ctm);
						//	m_xmat->multiply(ctm0, &ctm);
						}
					}
					else
					{
						ctm = ctm0;
					}

					CComQIPtr<IESVGElement> esvgElement = eElement;

					CComQIPtr<IESVGDrawOutline> drawOutline = /*eElement;*/selectedElement;//pElement;
					if (drawOutline)
					{
						drawOutline->DrawOutline(&graphics, layerColor, ctm);
					}

					if (esvgElement)
					{
						// Draw bounding box
						//if (objectTransformable)
						{
							CComPtr<ILSVGRect> svgbounds;
							//window->svgGetRBBox(static_cast<ILSVGElement*>(domElement.p), &svgbounds);
							selectedElement->GetRBBox(view, &svgbounds);

							SVGRect bounds = svgbounds;

							SVGPoint pts[9] =
							{
								SVGPoint(bounds.X, bounds.Y),
								SVGPoint(bounds.X+bounds.Width/2, bounds.Y),
								SVGPoint(bounds.X+bounds.Width, bounds.Y),
								SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
								SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height),
								SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
								SVGPoint(bounds.X, bounds.Y+bounds.Height),
								SVGPoint(bounds.X, bounds.Y+bounds.Height/2),

								SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height/2),	// center point
							};

							Gdiplus::PointF xpts[9];

							for (int i = 0; i < 9; i++)
							{
								/*
								CComPtr<ILSVGPoint> svgPoint;
								svgsvgElement->createSVGPoint(&svgPoint);
								svgPoint->put_x(pts[i].X);
								svgPoint->put_y(pts[i].Y);

								CComPtr<ILSVGPoint> xsvgPoint;
								svgPoint->matrixTransform(ctm, &xsvgPoint);

								xpts[i] = SVGPoint(xsvgPoint);
								*/
								xpts[i] = pts[i].matrixTransform(ctm);
							}
							
							// Outline
							graphics.DrawLine(&pen, xpts[0], xpts[2]);
							graphics.DrawLine(&pen, xpts[2], xpts[4]);
							graphics.DrawLine(&pen, xpts[4], xpts[6]);
							graphics.DrawLine(&pen, xpts[6], xpts[0]);
							
							if (!m_dragging)
							{
								long resizability;
								esvgElement->GetResizability(&resizability);

								if (resizability == 0)
								{
									int i = 8;	// Center only
									graphics.FillRectangle(&brush, (int)(xpts[i].X-2), (int)(xpts[i].Y-2), (4), (4));
								}
								else if (resizability == 1)
								{
									// Size handles
									for (i = 0; i < 9; i++)
									{
										graphics.FillRectangle(&brush, (int)(xpts[i].X-2), (int)(xpts[i].Y-2), (4), (4));
									}
								}
							}
							else
							{
								// Center X
								int cx = (int)(xpts[8].X);
								int cy = (int)(xpts[8].Y);
								
								graphics.DrawLine(&pen, cx-2, cy+2, cx+2, cy-2);
								graphics.DrawLine(&pen, cx-2, cy-2, cx+2, cy+2);
							}
						}
					}
				}
			}
		}
	}
	else if (m_nTool == ID_SVGTOOL_DIRECT)
	{
		if (m_dragging)
		{
			CComPtr<IESelectedElement> selectedElement;
			viewGroup->GetActiveSelectedElement(&selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComQIPtr<IESVGElement> esvgElement = eElement;

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			CComPtr<ILDOMElement> layer;
			SVGGetLayer(domElement, &layer);

			COLORREF layerColorRef = GetLayerColor(layer);
			Gdiplus::Color layerColor(GetRValue(layerColorRef), GetGValue(layerColorRef), GetBValue(layerColorRef));
			Gdiplus::Pen pen(layerColor);

			CComPtr<ILSVGMatrix> ctm;
			GetElementMatrix(eElement, view, &ctm);

			CComPtr<ILSVGMatrix> ictm;
			ctm->inverse(&ictm);

			/*
			SVGPoint xnewpt2 = pt.matrixTransform(ictm);
			SVGPoint xoldpt2 = m_startpt.matrixTransform(ictm);
			*/

			if (m_hitdata.ctl == 0)	// Clicked on anchor point
			{
			}
			else	// Control point
			{
				double ctlx = m_oldpt.X;
				double ctly = m_oldpt.Y;

				// Change x2,y2,x3,y3 of this segment and 

				CComPtr<ILSVGPathSegList> seglist;

				CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;
				if (selectedAnimationElement)
				{
					CComQIPtr<ILAnimateXXX> animateXXX = domElement;

					long index;
					selectedAnimationElement->GetKeyTimeSelected(m_hitdata.selectedKeyFrameIndex, &index);

					CComPtr<ILSMILAttributeValue> attribute;
					animateXXX->GetValue(index, &attribute);

					CComPtr<IUnknown> object;
					attribute->getObject(&object);

					CComQIPtr<ILSVGPointList> points = object;
					CComQIPtr<ILSVGPathSegListValue> seglistvalue = object;

					/*
					if (points)
					{
						HRESULT hr = ((CESVGPolyElement*)((CESelectedSVGPolyElement*)m_selectedTargetElement.p)->m_pElement)->HitTest(points, view, svgsvgElement, ctm, ptx, pty, hit);
						if (hr == S_OK)
							return hr;
					}
					else if (seglistvalue)
					*/
					{
						seglistvalue->get_pathSegList(&seglist);
					}
				}
				else
				{
					CComQIPtr<ILSVGAnimatedPathData> pathData = domElement;
					pathData->get_pathSegList(&seglist);
				}

				long numberOfItems;
				seglist->get_numberOfItems(&numberOfItems);

				CComPtr<ILSVGPathSeg> seg;
				seglist->getItem(m_hitdata.anchor, &seg);

				LSVGPathSegType segType;
				seg->get_pathSegType(&segType);

				PointD pts[3];
				pts[0] = GetPathSegP2(seglist, m_hitdata.anchor);
				pts[1].X = GetProperty(seg, L"x");
				pts[1].Y = GetProperty(seg, L"y");
				pts[2] = GetPathSegP3(seglist, m_hitdata.anchor);
				pts[1+m_hitdata.ctl].X = ctlx;
				pts[1+m_hitdata.ctl].Y = ctly;

				double angle = GetLineAngle(ctlx, ctly, pts[1].X, pts[1].Y);
				double distance = GetLineDistance(pts[1].X, pts[1].Y, pts[1-m_hitdata.ctl].X, pts[1-m_hitdata.ctl].Y);

				pts[1-m_hitdata.ctl].X = cos(angle)*distance + pts[1].X;
				pts[1-m_hitdata.ctl].Y = sin(angle)*distance + pts[1].Y;

				if (m_hitdata.anchor > 0)
				{
					if (segType != PATHSEG_MOVETO_ABS && segType != PATHSEG_MOVETO_REL)
					{
						double x1 = GetProperty(seg, L"x1");
						double y1 = GetProperty(seg, L"y1");

						CComPtr<ILSVGPathSeg> seg0;
						seglist->getItem(m_hitdata.anchor-1, &seg0);
						double x0 = GetProperty(seg0, L"x");
						double y0 = GetProperty(seg0, L"y");

						graphics.DrawBezier(&pen, float(x0), float(y0), float(x1), float(y1), float(pts[0].X), float(pts[0].Y), float(pts[1].X), float(pts[1].Y));
					}
				}

				if (m_hitdata.anchor < numberOfItems-1)
				{
					CComPtr<ILSVGPathSeg> seg;
					seglist->getItem(m_hitdata.anchor+1, &seg);

					LSVGPathSegType segType;
					seg->get_pathSegType(&segType);

					if (segType > PATHSEG_MOVETO_REL)	// Still in same subpath
					{
						PointD P2 = GetPathSegP2(seglist, m_hitdata.anchor+1);
						double x = GetProperty(seg, L"x");
						double y = GetProperty(seg, L"y");

						graphics.DrawBezier(&pen, float(pts[1].X), float(pts[1].Y), float(pts[2].X), float(pts[2].Y), float(P2.X), float(P2.Y), float(x), float(y));
					}
				}

				graphics.DrawLine(&pen, float(pts[1].X), float(pts[1].Y), float(pts[0].X), float(pts[0].Y));
				graphics.DrawLine(&pen, float(pts[1].X), float(pts[1].Y), float(pts[2].X), float(pts[2].Y));
			}
		}
		else
		{
			long count;
			viewGroup->GetSelectedCount(&count);

			for (int i = 0; i < count; i++)
			{
				CComPtr<IESelectedElement> selectedElement;
				viewGroup->GetSelectedElementN(i, &selectedElement);

				CComPtr<IEElement> eElement;
				selectedElement->get_eElement(&eElement);

				//CComQIPtr<IESVGElement> esvgElement = eElement;

				CComPtr<ILDOMElement> domElement;
				eElement->get_domElement(&domElement);

				CComPtr<ILDOMElement> layer;
				SVGGetLayer(domElement, &layer);

				COLORREF layerColorRef = GetLayerColor(layer);
				Gdiplus::Color layerColor(GetRValue(layerColorRef), GetGValue(layerColorRef), GetBValue(layerColorRef));
				Gdiplus::Pen pen(layerColor);

				CComPtr<ILSVGMatrix> ctm;
		//		GetElementMatrix(eElement, view, &ctm0);
				selectedElement->GetScreenCTM(view, &ctm);

				CComQIPtr<IESVGDrawOutline> drawOutline = selectedElement;//eElement;//selectedElement;//pElement;
				if (drawOutline)
				{
					drawOutline->DrawOutline(&graphics, layerColor, ctm);
				}
			}
		}
	}
#endif

	return S_OK;
}

STDMETHODIMP CSelectionTool::OnActivate(ILXMLEditorApp* app)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSelectionTool::OnDeactivate(ILXMLEditorApp* app)
{
	// TODO: Add your implementation code here

	return S_OK;
}

void CSelectionTool::ZoomToRect2(ISVGView* view, double left, double top, double right, double bottom)
{
	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	ASSERT(0);
#if 0
	window->ZoomToRect(left, top, right-left, bottom-top, VARIANT_TRUE);
#endif
}

STDMETHODIMP CSelectionTool::Options(HWND hParent)
{
	// TODO: Add your implementation code here

	return S_OK;
}

// Plugin
STDMETHODIMP CSelectionToolPlugin::SetSite(ILXMLEditorPluginClass* self)
{
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

		app->AddTool(self, this, NULL, ID_SVGTOOL_SELECT, L"Select", L"tool_select.png");
		app->AddTool(self, this, NULL, ID_SVGTOOL_DIRECT, L"Direct", L"tool_direct.bmp");

		app->AddTool(self, this, NULL, ID_TOOL_TEXT, L"Text", L"tool_text.bmp");
		app->AddTool(self, this, NULL, ID_TOOL_TEXTPATH, L"Text Path", L"tool_textpath.bmp");

		app->AddTool(self, this, NULL, ID_SVGTOOL_GRADIENT, L"Gradient", L"tool_ellipse.bmp");

		app->AddTool(self, this, NULL, ID_TOOL_HAND, L"Hand", L"tool_hand.bmp");
		app->AddTool(self, this, NULL, ID_TOOL_ZOOM, L"Zoom", L"tool_zoom.bmp");

		uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_SELECTTOOLS);
#endif
	}

	return S_OK;
}

#if 0
STDMETHODIMP CSelectionToolPlugin::Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
{
	return S_OK;
}
#endif

STDMETHODIMP CSelectionToolPlugin::FindTool(/*[in]*/ long id, IUnknown* *pdlg, /*[out,retval]*/ ISVGTool** pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	CComObject<CSelectionTool>* pTool;
	CComObject<CSelectionTool>::CreateInstance(&pTool);
	if (pTool)
	{
		pTool->AddRef();
		pTool->m_nTool = id;

		*pVal = pTool;
	}

	return S_OK;
}

#endif