#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGBehavior.h"

#include "EXMLDocument.h"
#include "EXMLViewGroup.h"
#include "EXMLLayoutView.h"

#include "ESelectedElementImpl.h"
#include "ESelectedSVGPathElement.h"	// TODO remove

#if 0

HRESULT GetOwnerLayer(ILDOMElement* element, ILDOMElement* *pVal);
HRESULT SVGGetLayer(ILDOMElement* element, ILDOMElement* *pVal);
COLORREF GetLayerColor(ILDOMElement* element);

void Normalize(LDraw::RectF& rc)
{
	if (rc.Width < 0)
	{
		rc.X += rc.Width;
		rc.Width = -rc.Width;
	}

	if (rc.Height < 0)
	{
		rc.Y += rc.Height;
		rc.Height = -rc.Height;
	}
}

int CLSVGBehavior::FinalConstruct()
{
	return 0;
}

void CLSVGBehavior::FinalRelease()
{
	ATLTRACE("CLSVGBehavior::FinalRelease()\n");
}

// ILElementBehavior
STDMETHODIMP CLSVGBehavior::Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
{
	m_pBehaviorSite = pBehaviorSite;

	CComPtr<ILDOMElement> element;
	pBehaviorSite->GetElement(&element);

	IDispEventImpl<1, CLSVGBehavior, &DIID__ILSVGSVGElementEvents, &LIBID_LHTMLLib, 1, 0>::DispEventAdvise(element);
	IDispEventImpl<2, CLSVGBehavior, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->m_pDocument->m_app);
	IDispEventImpl<3, CLSVGBehavior, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());

#if 0
	// ??
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);
#endif

	m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &m_activeTool);

	return S_OK;
}

STDMETHODIMP CLSVGBehavior::Detach()
{
#if 0
	// ??
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);
#endif

	CComPtr<ILDOMElement> element;
	m_pBehaviorSite->GetElement(&element);

	IDispEventImpl<1, CLSVGBehavior, &DIID__ILSVGSVGElementEvents, &LIBID_LHTMLLib, 1, 0>::DispEventUnadvise(element);
	IDispEventImpl<2, CLSVGBehavior, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->m_pDocument->m_app);
	IDispEventImpl<3, CLSVGBehavior, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());

	return S_OK;
}

void __stdcall CLSVGBehavior::OnActiveToolChange()
{
	m_activeTool.Release();
	m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &m_activeTool);

	CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
	paintSite->InvalidateRect(NULL);
}

void __stdcall CLSVGBehavior::OnViewGroupSelectionChanged()
{
	CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;

	paintSite->InvalidateRect(NULL);
}

void __stdcall CLSVGBehavior::onmousedown(ILDOMEvent* evt)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMMouseEvent> mouseevt = evt;

	CComPtr<ILDOMAbstractView> view;
	mouseevt->get_view(&view);

	CComPtr<ILDOMAbstractView> bview;
	m_pBehaviorSite->GetView(&bview);

	if (view == bview)
	{
		long button;
		mouseevt->get_button(&button);
		if (button == 0)	// Left button
		{
			mouseevt->get_clientX(&m_clientX);
			mouseevt->get_clientY(&m_clientY);

			VARIANT_BOOL ctrlKey;
			mouseevt->get_ctrlKey(&ctrlKey);

			VARIANT_BOOL shiftKey;
			mouseevt->get_shiftKey(&shiftKey);

			VARIANT_BOOL altKey;
			mouseevt->get_altKey(&altKey);

			m_nFlags = 0;
			if (ctrlKey) m_nFlags |= MK_CONTROL;
			if (shiftKey) m_nFlags |= MK_SHIFT;
			if (altKey) m_nFlags |= MK_ALT;

			OnButtonDown(m_nFlags, CPoint(m_clientX, m_clientY), button, FALSE);
		}
	}
#endif
}

void __stdcall CLSVGBehavior::onmouseup(ILDOMEvent* evt)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMMouseEvent> mouseevt = evt;

	CComPtr<ILDOMAbstractView> view;
	mouseevt->get_view(&view);

	CComPtr<ILDOMAbstractView> bview;
	m_pBehaviorSite->GetView(&bview);

	//CComQIPtr<ILHTMLWindow> window = view;
	//double translateX;
	//double translateY;
	//window->get_currentTranslateX(&translateX);
	//window->get_currentTranslateY(&translateY);

	if (view == bview)
	{
		long x, y;
		mouseevt->get_clientX(&x);
		mouseevt->get_clientY(&y);

		//x -= translateX;
		//y -= translateY;

		VARIANT_BOOL ctrlKey;
		mouseevt->get_ctrlKey(&ctrlKey);

		VARIANT_BOOL shiftKey;
		mouseevt->get_shiftKey(&shiftKey);

		VARIANT_BOOL altKey;
		mouseevt->get_altKey(&altKey);

		m_nFlags = 0;
		if (ctrlKey) m_nFlags |= MK_CONTROL;
		if (shiftKey) m_nFlags |= MK_SHIFT;
		if (altKey) m_nFlags |= MK_ALT;

		OnButtonUp(m_nFlags, CPoint(x, y), 0);
	}

	evt->preventDefault();
#endif
}

void __stdcall CLSVGBehavior::onmousemove(ILDOMEvent* evt)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMMouseEvent> mouseevt = evt;

	CComPtr<ILDOMAbstractView> view;
	mouseevt->get_view(&view);

	CComPtr<ILDOMAbstractView> bview;
	m_pBehaviorSite->GetView(&bview);

	/*
	CComQIPtr<ILHTMLWindow> window = view;
	double translateX;
	double translateY;
	window->get_currentTranslateX(&translateX);
	window->get_currentTranslateY(&translateY);
	*/

	if (view == bview)
	{
		mouseevt->get_clientX(&m_clientX);
		mouseevt->get_clientY(&m_clientY);

		/*
		x -= translateX;
		y -= translateY;
		*/

		VARIANT_BOOL ctrlKey;
		mouseevt->get_ctrlKey(&ctrlKey);

		VARIANT_BOOL shiftKey;
		mouseevt->get_shiftKey(&shiftKey);

		VARIANT_BOOL altKey;
		mouseevt->get_altKey(&altKey);

		m_nFlags = 0;
		if (ctrlKey) m_nFlags |= MK_CONTROL;
		if (shiftKey) m_nFlags |= MK_SHIFT;
		if (altKey) m_nFlags |= MK_ALT;

		OnMouseMove(m_nFlags, CPoint(m_clientX, m_clientY));
	}
#endif
}

void __stdcall CLSVGBehavior::oncontextmenu(ILDOMEvent* evt)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMMouseEvent> mouseevt = evt;

	CComPtr<ILDOMAbstractView> view;
	mouseevt->get_view(&view);

	CComQIPtr<ILHTMLWindow> window = view;

	CComPtr<ILDOMAbstractView> bview;
	m_pBehaviorSite->GetView(&bview);

	if (view == bview)
	{
		long x, y;
		mouseevt->get_clientX(&x);
		mouseevt->get_clientY(&y);
		CPoint point(x,y);

		CComPtr<ILHTMLActiveView> oleActiveView;
		window->GetOleView(&oleActiveView);

		CComQIPtr<IOleWindow> oleView = oleActiveView;

		HWND hWnd;
		oleView->GetWindow(&hWnd);

		::ClientToScreen(hWnd, &point);

	//	CComQIPtr<IUIManager> uiManager = gIFrame;

		CComPtr<IMenuItem> menu;

		long count;
		m_viewGroup->GetSelectedCount(&count);

		if (count > 0)
		{
		//	uiManager->FindMenu(IDR_LAYOUTSEL, &menu);
		}
		else
		{
		//	uiManager->FindMenu(IDR_LAYOUTNOSEL, &menu);
		}

		CComPtr<IMenuItem> menu0;
		menu->GetSubMenu(0, &menu0);
		if (menu0)
		{
			CComQIPtr<ICommandTarget> target = m_layoutView;
			long selectedID;
			menu0->PopupMenu(target, point, 0, &selectedID);
		}
	}
#endif
}

void __stdcall CLSVGBehavior::onselect(ILDOMEvent* evt)
{
	long toolID = 0;

	if (m_activeTool)
	{
		m_pDocument->m_app->GetToolID(m_activeTool, &toolID);
	}

	if (toolID != ID_TOOL_TEXT)
	{
		evt->preventDefault();
	}
}

void __stdcall CLSVGBehavior::onkeydown(ILDOMEvent* evt)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILTextEvent> textevt = evt;

	CComPtr<ILDOMAbstractView> view;
	textevt->get_view(&view);

	CComPtr<ILDOMAbstractView> bview;
	m_pBehaviorSite->GetView(&bview);

	if (view == bview)
	{
		long virtKeyVal;
		textevt->get_virtKeyVal(&virtKeyVal);

		m_nFlags = 0;

		/*
		VARIANT_BOOL bLeftCtrl;
		textevt->checkModifer(DOM_VK_LEFT_CONTROL);

		VARIANT_BOOL bRightCtrl;
		textevt->checkModifer(DOM_VK_RIGHT_CONTROL);

		if (bLeftCtrl || bRightCtrl)
			nFlags |= MK_CONTROL;
			*/

		VARIANT_BOOL bLeftAlt;
		textevt->checkModifier(DOM_VK_LEFT_ALT, &bLeftAlt);
		if (bLeftAlt) m_nFlags |= MK_ALT;

	// TODO
		if (GetAsyncKeyState(VK_SHIFT) & (1<<15)) m_nFlags |= MK_SHIFT;
		if (GetAsyncKeyState(VK_CONTROL) & (1<<15)) m_nFlags |= MK_CONTROL;

		OnKeyDown(virtKeyVal);
	}
#endif
}

void __stdcall CLSVGBehavior::onkeyup(ILDOMEvent* evt)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILTextEvent> textevt = evt;

	CComPtr<ILDOMAbstractView> view;
	textevt->get_view(&view);

	CComPtr<ILDOMAbstractView> bview;
	m_pBehaviorSite->GetView(&bview);

	if (view == bview)
	{
		long virtKeyVal;
		textevt->get_virtKeyVal(&virtKeyVal);

		m_nFlags = 0;

		/*
		VARIANT_BOOL bLeftCtrl;
		textevt->checkModifer(DOM_VK_LEFT_CONTROL);

		VARIANT_BOOL bRightCtrl;
		textevt->checkModifer(DOM_VK_RIGHT_CONTROL);

		UINT nFlags = 0;
		if (bLeftCtrl || bRightCtrl)
			nFlags |= MK_CONTROL;
			*/

		VARIANT_BOOL bLeftAlt;
		textevt->checkModifier(DOM_VK_LEFT_ALT, &bLeftAlt);
		if (bLeftAlt) m_nFlags |= MK_ALT;

	// TODO
		if (GetAsyncKeyState(VK_SHIFT) & (1<<15)) m_nFlags |= MK_SHIFT;
		if (GetAsyncKeyState(VK_CONTROL) & (1<<15)) m_nFlags |= MK_CONTROL;

		OnKeyUp(virtKeyVal);
	}
#endif
}

void CLSVGBehavior::OnSetCursor()
{
	SetCursor(CPoint(m_clientX, m_clientY));
}

// ILHTMLPainter
STDMETHODIMP CLSVGBehavior::SetCursor(/*[in]*/ POINT pt)
{
	ASSERT(0);
#if 0
	UINT nFlags = m_nFlags;

	CComPtr<ISVGTool> activeTool;

	if (m_dragging)
	{
		activeTool = m_activeTool;
	}
	else
	{
		if (!(nFlags & MK_CONTROL))
			m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &activeTool);
		else
			m_pDocument->m_app->GetActiveTool(VARIANT_TRUE, &activeTool);
	}

	CComPtr<ILDOMDocument> document;
	m_pDocument->get_DOMDocument(&document);

	CComQIPtr<ILSVGSVGElement> svgsvgElement;
	document->get_documentElement((ILDOMElement**)&svgsvgElement);

	if (activeTool)
	{
		CComPtr<ILDOMAbstractView> view;
		m_pBehaviorSite->GetView(&view);

#if 0
		CComQIPtr<ILHTMLWindow> window = view;
		double translateX;
		double translateY;
		window->get_currentTranslateX(&translateX);
		window->get_currentTranslateY(&translateY);

		double magnify;
		window->get_magnify(&magnify);

		m_viewMatrix.Release();

		CComPtr<ILSVGMatrix> mat1;
		svgsvgElement->createSVGMatrix(&mat1);
		CComPtr<ILSVGMatrix> mat;
		mat1->scaleNonUniform(magnify, magnify, &mat);
		mat->translate(translateX, translateY, &m_viewMatrix);

		CComPtr<ILSVGMatrix> imatrix;
		m_viewMatrix->inverse(&imatrix);

	//	POINT pt = point;
#endif

	//	SVGPoint dpt;
	//	dpt.X = pt.x;
	//	dpt.Y = pt.y;

//		SVGPoint wpt = dpt.matrixTransform(imatrix);

		SVGMouse svgmouse;
		svgmouse.ptx = pt.x;
		svgmouse.pty = pt.y;
	//	svgmouse.dptx = dpt.X;
	//	svgmouse.dpty = dpt.Y;
	//	svgmouse.wptx = wpt.X;
	//	svgmouse.wpty = wpt.Y;
		svgmouse.nFlags = nFlags;

		return activeTool->OnSetCursor(this, &svgmouse);
	}
#endif

	return S_FALSE;
}

STDMETHODIMP CLSVGBehavior::Draw( 
            /* [in] */ RECT rcBounds,
            /* [in] */ RECT rcUpdate,
            /* [in] */ LONG lDrawFlags,
            /* [in] */ HDC hdc,
            /* [in] */ LPVOID pvDrawObject)
{
	ASSERT(0);
#if 0
	ASSERT(m_viewGroup);

	if (FALSE)
	{
		HPEN redPen	= (HPEN)CreatePen(PS_DOT, 0, RGB(0xff, 0x99, 0x99));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

		long lFirstLine = rcBounds.left;

		double m_lGridSize = 20;

		for (double i = lFirstLine; i <= rcBounds.right; i += m_lGridSize)
		{
			MoveToEx(hdc, i, rcBounds.top, NULL);
			LineTo(hdc, i, rcBounds.bottom);
		}

		lFirstLine = rcBounds.top;

		for (i = lFirstLine ; i <= rcBounds.bottom; i += m_lGridSize)
		{
			MoveToEx(hdc, rcBounds.left, i,  NULL);
			LineTo(hdc, rcBounds.right, i);
		}

		SelectObject(hdc, oldPen);
		DeleteObject(redPen);
	}

	//CEXMLDocument* pDocument = m_pDocument;

	CComPtr<ILDOMElement> element;
	m_pBehaviorSite->GetElement(&element);

	//CComPtr<ILDOMDocument> document;
	//m_pDocument->get_DOMDocument(&document);

	//CComPtr<ILDOMElement> documentElement;
	//document->get_documentElement(&documentElement);

	CComPtr<ILHTMLWindow> window;
	GetHTMLWindow(&window);

	CComQIPtr<ILSVGSVGElement> svgsvgElement = element;//documentElement;
	CComQIPtr<ILSMILElement> smilElement = element;

	if (svgsvgElement)
	{
//		m_viewMatrix.Release();
//		GetViewMatrix(&m_viewMatrix);

		{
			LDraw::Graphics graphics(hdc);
			LDraw::Graphics* pGraphics = &graphics;//LDraw::Graphics::FromHDC(hdc);

			if (TRUE)	// Draw page rect
			{
				double contentWidth;
				double contentHeight;
				window->get_contentWidth(&contentWidth);
				window->get_contentHeight(&contentHeight);

				/*
				double translateX;
				double translateY;
				window->get_currentTranslateX(&translateX);
				window->get_currentTranslateY(&translateY);

				double magnify;
				window->get_magnify(&magnify);

				w
				*/
				CComPtr<ILSVGMatrix> matrix;
				GetViewMatrix(&matrix);

				LDraw::Pen pen(LDraw::Color(0,0,0));
		//		graphics.DrawRectangle(&pen, float(translateX), float(translateY), float(contentWidth*magnify), float(contentHeight*magnify));

				RectD bounds(0, 0, contentWidth, contentHeight);

				SVGPoint pts[4] =
				{
					SVGPoint(bounds.X, bounds.Y),
					SVGPoint(bounds.X+bounds.Width, bounds.Y),
					SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height),
					SVGPoint(bounds.X, bounds.Y+bounds.Height),
				};

				LDraw::PointF xpts[4];

				for (int i = 0; i < 4; i++)
				{
					xpts[i] = pts[i].matrixTransform(matrix);
				}
				
				// Outline
				graphics.DrawLine(&pen, xpts[0], xpts[1]);
				graphics.DrawLine(&pen, xpts[1], xpts[2]);
				graphics.DrawLine(&pen, xpts[2], xpts[3]);
				graphics.DrawLine(&pen, xpts[3], xpts[0]);

			}

			CComPtr<ILDOMElement> element;
			m_pBehaviorSite->GetElement(&element);
			CComQIPtr<ILSVGGlyphElement> glyphElement = element;

			if (glyphElement)
			{
				CComPtr<ILDOMNode> parentNode;
				glyphElement->get_parentNode(&parentNode);

				CComQIPtr<ILSVGFontElement> fontElement = parentNode;
				if (fontElement)
				{
	#if 0
					CComPtr<ILDOMNodeList> nodes;
					fontElement->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"font-face", &nodes);

					long length;
					nodes->get_length(&length);
					if (length == 1)
					{
						CComPtr<ILDOMNode> node;
						nodes->item(0, &node);

						CComQIPtr<ILSVGFontFaceElement> fontFaceElement = node;
						ASSERT(fontFaceElement);

						if (fontFaceElement)
						{
							double ascent;
							fontFaceElement->get_ascent(&ascent);

							double descent;
							fontFaceElement->get_descent(&descent);

							LDraw::Pen pen(LDraw::Color(0, 0, 0));
			
							SVGPoint pt[8] =
							{
								SVGPoint((float)0, (float)99999),
								SVGPoint((float)0, (float)-descent),

							// baseline
								SVGPoint((float)0, (float)0),
								SVGPoint((float)99999, (float)0),

							// ascent
								SVGPoint((float)0, (float)ascent),
								SVGPoint((float)99999, (float)ascent),

							// descent
								SVGPoint((float)0, (float)-descent),
								SVGPoint((float)99999, (float)-descent),
							};

							pt[0] = pt[0].matrixTransform(m_viewMatrix);
							pt[1] = pt[1].matrixTransform(m_viewMatrix);
							pt[2] = pt[2].matrixTransform(m_viewMatrix);
							pt[3] = pt[3].matrixTransform(m_viewMatrix);
							pt[4] = pt[4].matrixTransform(m_viewMatrix);
							pt[5] = pt[5].matrixTransform(m_viewMatrix);
							pt[6] = pt[6].matrixTransform(m_viewMatrix);
							pt[7] = pt[7].matrixTransform(m_viewMatrix);

							graphics.DrawLine(&pen, pt[0], pt[1]);
							graphics.DrawLine(&pen, pt[2], pt[3]);
							graphics.DrawLine(&pen, pt[4], pt[5]);
							graphics.DrawLine(&pen, pt[6], pt[7]);
						}
					}
	#endif
				}
			}

			long nselected;
			m_viewGroup->GetSelectedCount(&nselected);

			for (int i = 0; i < nselected; i++)
			{
				CComPtr<IESelectedElement> selectedElement;
				m_viewGroup->GetSelectedElementN(i, &selectedElement);

				CComPtr<IEElement> pElement;
				selectedElement->get_eElement(&pElement);

				CComPtr<ILDOMElement> domElement;
				pElement->get_domElement(&domElement);

				CComPtr<ILDOMElement> layer;
				SVGGetLayer/*GetOwnerLayer*/(domElement, &layer);

				CComPtr<ILDOMElement> locatableElement = domElement;

				/*	// TODO: Done in selectedAnimation::GetScreenCTM
				if (TRUE)	// Account for animation
				{
					CComQIPtr<ILAnimationElement> animationElement = domElement;
					if (animationElement)
					{
						locatableElement.Release();
						animationElement->get_targetElement(&locatableElement);
					}
				}
				*/

			//	CComQIPtr<ILSVGTransformable> objectTransformable = locatableElement;
			//	if (objectTransformable)
				CComPtr<ILSVGMatrix> ctm0;
				selectedElement->GetScreenCTM(this, &ctm0);
				if (ctm0)
				{
					COLORREF layerColorRef = GetLayerColor(layer);
					LDraw::Color layerColor(GetRValue(layerColorRef), GetGValue(layerColorRef), GetBValue(layerColorRef));

					LDraw::Pen pen(layerColor);
					LDraw::SolidBrush brush(layerColor);

					if (static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferenceElement)
					{
						CComPtr<ILDOMElement> refElement;
						static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferenceElement->get_domElement(&refElement);

						CComPtr<ILDOMElement> refedElement;
						static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement->get_domElement(&refedElement);

						CComQIPtr<ILSVGMaskElement> maskElement = refedElement;

						CComQIPtr<ILSVGLocatable> refLocatable = refElement;
						if (refLocatable)
						{
	#if 0
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
	#endif
						}
					}

					CComPtr<ILSVGMatrix> ctm = ctm0;
					//ctm0->multiply(m_viewMatrix, &ctm);

						// Draw path outline

					if (!m_dragging)	// TODO, should ask tool
					{
#if 0
						CComQIPtr<IESVGDrawOutline> drawOutline = selectedElement;//pElement;
						if (drawOutline)
						{
							drawOutline->DrawOutline(&graphics, layerColor, ctm);
						}
#endif

						//if (!m_dragging || m_freeTransformMatrix == NULL)
						{
							CComQIPtr<IESVGDrawSelection> drawSelection = selectedElement;
							if (drawSelection)
							{
								drawSelection->DrawSelection(&graphics, layerColor, ctm);
							}
						}
					}
				}
			}

			if (m_dragging)
			{

				/*
				if (m_dragging == 10 || m_dragging == 11)
				{
					CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
					if (m_activeSpread)
						m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

					CComPtr<IPDLayer> layer;
					activeLayerGroup->get_layer(&layer);

					OLE_COLOR olelayerColor;
					layer->get_color(&olelayerColor);

					CComQIPtr<IPDRenderer> renderer;
					renderer.CoCreateInstance(CLSID_PDRenderer);

					renderer->put_targetHDC((HDC)&graphics);
					renderer->put_magnify(m_magnify);

					long spine;
					m_activeSpread->get_spine(&spine);

					double xoffset = (m_spine-spine)*pageWidth;

					renderer->RenderGuide(m_activeSpread, m_newGuide,
						olelayerColor,
						-(xoffset+100), -20, m_maxPages*pageWidth+200, pageHeight+40);
				}
				else if (m_activeLayer)
	*/			{
				//	OLE_COLOR layerColor;
				//	m_activeLayer->get_color(&layerColor);
					LDraw::Color layerColor(0, 0, 200);

					LDraw::Pen pen(layerColor);

				}
			}
		}

		CComPtr<ISVGTool> activeTool;
		m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &activeTool);
		if (activeTool)
		{
			activeTool->Paint(this, m_dragging, hdc);
		}

	//	graphics.Restore(state);
	}
	else if (smilElement)
	{
		{
			LDraw::Graphics graphics(hdc);
			LDraw::Graphics* pGraphics = &graphics;//LDraw::Graphics::FromHDC(hdc);

			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetActiveSelectedElement(&selectedElement);
			if (selectedElement)
			{
				CComPtr<IEElement> eElement;
				selectedElement->get_eElement(&eElement);

				CComPtr<ILDOMElement> element;
				eElement->get_domElement(&element);

				CComQIPtr<ILDOMViewCSS> cssView = window;

				CComPtr<ILCSSStyleDeclaration> style;
				cssView->getComputedStyle(element, NULL, &style);

				double left;
				double top;
				double width;
				double height;

				{
					CComPtr<ILCSSValue> value;
					style->getPropertyCSSValue(L"left", &value);
					CComQIPtr<ILCSSPrimitiveValue> pvalue = value;
					pvalue->getFloatValue(CSS_NUMBER, &left);
				}
				{
					CComPtr<ILCSSValue> value;
					style->getPropertyCSSValue(L"top", &value);
					CComQIPtr<ILCSSPrimitiveValue> pvalue = value;
					pvalue->getFloatValue(CSS_NUMBER, &top);
				}
				{
					CComPtr<ILCSSValue> value;
					style->getPropertyCSSValue(L"width", &value);
					CComQIPtr<ILCSSPrimitiveValue> pvalue = value;
					pvalue->getFloatValue(CSS_NUMBER, &width);
				}
				{
					CComPtr<ILCSSValue> value;
					style->getPropertyCSSValue(L"height", &value);
					CComQIPtr<ILCSSPrimitiveValue> pvalue = value;
					pvalue->getFloatValue(CSS_NUMBER, &height);
				}

				LDraw::Pen pen(LDraw::Color(0, 0, 255), 1);

				pGraphics->DrawRectangle(&pen, float(left), float(top), float(width), float(height));
			}
		}
	}
#endif

	return S_OK;
}

void CLSVGBehavior::InvalidateInvalidRect()
{
	CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;

	paintSite->InvalidateRect(NULL);

#if 0
	m_layoutView->Invalidate();	// TODO
#endif

#if 0
	SVGLib::ISVGSVGElementPtr svg = m_pDocument->GetDOMDocument()->documentElement;
	SVGLib::_tagSVGRect svgrect = svg->getInvalidBox();

	UpdateRect(svgrect);
#endif
}

HRESULT GetRefElementMatrix(ISVGView* view, ILSVGMatrix* *pVal);

STDMETHODIMP CLSVGBehavior::HitTest(/*[in]*/ IEElement* eelement, /*[in]*/ double ptx, /*[in]*/ double pty, /*[in]*/ long options, /*[in,out]*/ _SVGHitData* hitdata)
{
	CComQIPtr<IESVGElement> svgEElement;

// Clear it
	hitdata->anchor = -1;
	hitdata->segment = -1;
	hitdata->ctl = 0;
	hitdata->element = NULL;
	hitdata->selectedElement = NULL;

	SVGPoint pt(ptx, pty);

	CComPtr<ILSVGMatrix> elementMatrix;

	if (eelement == NULL)
	{
		if (m_viewGroup->m_activeReferencedElement)
		{
			svgEElement = m_viewGroup->m_activeReferencedElement;

			GetRefElementMatrix(this/*m_viewGroup*/, &elementMatrix);
		}
		else
		{
			CComPtr<ILDOMElement> element;
			m_pBehaviorSite->GetElement(&element);

			CComPtr<IEElement> eelement2;
			m_pDocument->GetEElementFromDOMElement(element, &eelement2);

			svgEElement = eelement2;
		}
	}
	else
		svgEElement = eelement;

	if (svgEElement)
	{
		CComPtr<ILSVGMatrix> matrix;

		CComPtr<ILSVGMatrix> viewMatrix;
		GetViewMatrix(&viewMatrix);

		if (elementMatrix)
		{
			elementMatrix->multiply(viewMatrix, &matrix);
		}
		else
			matrix = viewMatrix;

		return GetObjectUnderPoint(svgEElement, matrix, pt, options, hitdata);
	}

	return S_OK;
};

HRESULT CLSVGBehavior::GetObjectUnderPoint(IESVGElement* object, ILSVGMatrix* matrix, SVGPoint pt, int tool, _SVGHitData* hit/*, IEElement** pVal*/)
{
	ASSERT(0);
#if 0
	BOOL bHit = S_FALSE;

	CComPtr<ILHTMLWindow> window;
	GetHTMLWindow(&window);

	CComPtr<ILDOMDocument> document;
	m_pDocument->get_DOMDocument(&document);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	document->get_documentElement((ILDOMElement**)&svgsvgElement);

	CComPtr<IEElement> parentNode;
	object->get_parentNode(&parentNode);

	CComPtr<ILDOMElement> domElement;
	object->get_domElement(&domElement);

	CComPtr<ILDOMElement> locatableElement = domElement;

	/*
	if (TRUE)	// Account for animation
	{
	*/
		CComQIPtr<ILAnimationElement> animationElement = domElement;
		CComQIPtr<ILSVGAnimateMotionElement> animateMotion = domElement;
		if (animationElement != NULL && animateMotion == NULL)
		{
			locatableElement.Release();
			animationElement->get_targetElement(&locatableElement);
		}
	//}

	CComPtr<ILSVGMatrix> ctm0;
	CComQIPtr<ILSVGLocatable>(locatableElement)->getTransformMatrix(&ctm0);

	CComPtr<ILSVGMatrix> ctm;
	ctm0->multiply(matrix, &ctm);

//	window->svgGetScreenCTM(CComQIPtr<ILSVGElement>(locatableElement), &ctm);

// Try children
//	if (bHit == S_FALSE)
	{
		CComPtr<ILSVGMatrix> viewBoxMatrix;
		window->svgGetElementViewBoxMatrix(CComQIPtr<ILSVGElement>(domElement), &viewBoxMatrix);

		CComPtr<ILSVGMatrix> mat2;
		viewBoxMatrix->multiply(ctm, &mat2);

		CComPtr<ILDOMNode> domNode;
		domElement->get_lastChild(&domNode);

		while (domNode)
		{
			CComQIPtr<ILDOMElement> domElement2 = domNode;
			if (domElement2)
			{
				CComQIPtr<ISVGRenderElement> render = domElement2;
				if (render)
				{
					CComPtr<IEElement> eElement2;
					m_pDocument->GetEElementFromDOMElement(domElement2, &eElement2);

					CComQIPtr<IESVGElement> svgEElement = eElement2;

					if (svgEElement)
					{
					// Recurse
						GetObjectUnderPoint(svgEElement, mat2, pt, tool, hit);
						if (hit->element)
						{
							break;
						}
					}
				}
			}

			CComPtr<ILDOMNode> prevSibling;
			domNode->get_previousSibling(&prevSibling);
			domNode = prevSibling;
		}
	}

	if (hit->element == NULL)
	{
	#if 0
		if (tool == 4)	// Text tool
		{
			CComPtr<IPDMatrix> ictm;
			ctm->inverse(&ictm);

			PointD xpt;
			ictm->transformPoint((PointD*)&pt, &xpt);

			if (objectType == CONTENT_TEXT)
			{
				CComQIPtr<IPDContentText> text = object;

				BOOL bHit;
				text->getPosUnderPoint(xpt.x, xpt.y, &hit->pNode, &hit->offset, &bHit);
				if (bHit)
				{
					fobject = object;
					hit->hit = 1;
				}
			}
			else if (objectType == OBJECT_FRAME)
			{
				CComQIPtr<IPDObjectFrame> frame = object;

				CComPtr<IPDPathText> pathText;
				frame->get_pathText(&pathText);

				if (pathText)
				{
					BOOL bHit;
					pathText->getPosUnderPoint(xpt.x, xpt.y, &hit->pNode, &hit->offset, &bHit);
					if (bHit)
					{
						fobject = pathText;
						hit->hit = 1;
					}
				}
			}
		}
		else

			if (tool == 5)
		{
			// TODO, don't use this stuff here
			CComPtr<ILSVGMatrix> ictm;
			ctm->inverse(&ictm);

			PointD xpt;
			ictm->transformPoint((PointD*)&pt, &xpt);

			if (objectType == OBJECT_FRAME)
			{
				CComQIPtr<IPDObjectFrame> frame = object;

				//CComPtr<IPDPath> pdpath;
				//frame->get_path(&pdpath);

				BOOL bOver;// = IsPointOverPath(*(CDblPoint*)&xpt, pdpath, NULL);
				frame->IsPointOverStrokeOutline(xpt, &bOver);
				if (bOver)
				{
					fobject = object;
					hit->hit = 1;
				}
			}
		}
		else
	#endif
		{
			CComPtr<IESelectedElement> selectedObject;
			m_viewGroup->GetSelectedElement(object, &selectedObject);
			if (selectedObject)
			{
				if (bHit == S_FALSE)
				{
					bHit = selectedObject->HitTest(this, svgsvgElement, ctm, pt.X, pt.Y, tool, hit);
					if (bHit == S_OK)
					{
						hit->selectedElement = selectedObject;
						hit->element = object;
					}
				}
			}

			if (bHit == S_FALSE)
			{
				bHit = object->HitTest(this, svgsvgElement, ctm, pt.X, pt.Y, hit);

				if (bHit == S_OK)
				{
					hit->element = object;
				//	hit->hit = 1;
				}
			}

#if 0
			if (tool == 2)	// Direct selection tool
			{
				CComQIPtr<ILSVGPathElement> path = object->m_domElement;
				// check if hit on path
				if (path)
				{
					//CPathElement* pFrame = (CPathElement*)object;
					CESelectedSVGPathElement* pFrame = (CESelectedSVGPathElement*)pObject;
					//CComQIPtr<IPDObjectFrame> frame = object;

					//CComPtr<IPDPath> pdpath;
					//frame->get_path(&pdpath);

					//if (pFrame)	// Selected object
					{
						hit->anchor = pFrame->/*m_path->*/FindPoint(ctm, pt.X, pt.Y, hit->ctl);
						if (hit->anchor >= 0)
						{
							hit->path = pFrame;//pdpath;
						}
					}
	#if 0
					else	// Unselected object
					{
						pdpath->getPointNearAnchorPoint(ctm, pt.X, pt.Y, 3, &hit->anchor);
						if (hit->anchor >= 0)
						{
							hit->path = pdpath;
						}
					}
	#endif

	#if 0
					if (hit->anchor < 0)
					{
						BOOL bHit;
						pdpath->getPointNearPath(ctm, pt.x, pt.y, 2, &hit->segment,&hit->t, &bHit);
						if (bHit)
						{
							hit->path = pdpath;
						}
					}
	#endif
				}

#if 0
				if (hit->path == NULL)
				{
						/*
					if (pObject)
					{
						if (pObject->m_wrapPath)
						{
							hit->anchor = pObject->m_wrapPath->FindPoint(ctm, pt.x, pt.y, hit->ctl);
							if (hit->anchor >= 0)
							{
								hit->path = pObject->m_wrapPath->GetPDPath();
							}

							if (hit->anchor < 0)
							{
								BOOL bHit;
								pObject->m_wrapPath->GetPDPath()->getPointNearPath(ctm, pt.x, pt.y, 2, &hit->segment,&hit->t, &bHit);
								if (bHit)
								{
									hit->path = pObject->m_wrapPath->GetPDPath();
								}
							}
						}
					}
						*/
				}
#endif

				if (hit->path)
				{
					hit->hit = -1;
					fobject = object;
				}
			}
#endif
		}
	}

#if 0
	if (tool == 1)	// Selection tool
	{
		if (hit->element)
		{
			if (TRUE)
			{
				if (parentNode != NULL)
				{
					hit->element = object;////(*pVal = object)->AddRef();
					return S_OK;//object;
				}
			}
			else
			{
				/*
				ASSERT(parent);

				CComPtr<IEElement> parentParent;
				parentNode->get_parentNode(&parentParent);

				if (parentParent != NULL)
				{
					hit->element = object;//(*pVal = object)->AddRef();
					return S_OK;
				}
				*/
			}
		}
	}
	else if (tool == 3)	// Group selection tool
	{
#if 0
		if (fobject)
		{
			if (IsPDObjectSelected(object))
			{
				(*pVal = parent)->AddRef();
				return S_OK;//parent.Detach();
			}
		}
#endif
	}
#endif

	/*
	if (fobject)
		(*pVal = fobject)->AddRef();//.Detach();
		*/
	//else
	//	return NULL;
#endif

	return S_OK;
}

void CLSVGBehavior::OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk)
{
	ASSERT(0);
#if 0
	CEXMLDocument* pDocument = m_pDocument;

	/*
	if (pDocument->m_errors.GetSize()>0)	// TODO, use CountErrors() since there may be warnings in there
	{
		MessageBox(GetMainHwnd(), "There are errors in the document\nGo to SourceView and fix them first", "WebEditor", MB_OK);
		return;
	}
	*/

	CComPtr<ILDOMDocument> domdocument;
	m_pDocument->get_DOMDocument(&domdocument);

	CComQIPtr<ILSVGDocument> svgDocument = domdocument;
	if (svgDocument == NULL)
	{
	}
	else
	{
	//	CComPtr<ILDOMAbstractView> view;
	//	m_pBehaviorSite->GetView(&view);
	//	CComQIPtr<ILHTMLWindow> window = view;

	//	double magnify;
	//	window->get_magnify(&magnify);

		CComPtr<ILDOMDocument> document;
		m_pDocument->get_DOMDocument(&document);

		CComQIPtr<ILSVGSVGElement> svgsvgElement;
		document->get_documentElement((ILDOMElement**)&svgsvgElement);
		if (svgsvgElement == NULL) return;

	//	HWND hwnd = m_hWnd;

//		SetFocus(hwnd);

		m_point = point;

		if (!m_dragging)
		{
			CComPtr<ILDOMAbstractView> view;
			m_pBehaviorSite->GetView(&view);

			/*
			CComQIPtr<ILHTMLWindow> window = view;
			double translateX;
			double translateY;
			window->get_currentTranslateX(&translateX);
			window->get_currentTranslateY(&translateY);
			double magnify;
			window->get_magnify(&magnify);

			m_viewMatrix.Release();

			CComPtr<ILSVGMatrix> mat1;
			svgsvgElement->createSVGMatrix(&mat1);
			CComPtr<ILSVGMatrix> mat;
			mat1->scaleNonUniform(magnify, magnify, &mat);
			mat->translate(translateX, translateY, &m_viewMatrix);
			*/

			CComPtr<ILSVGMatrix> viewMatrix;
			GetViewMatrix(&viewMatrix);

			CComPtr<ILSVGMatrix> imatrix;
			viewMatrix->inverse(&imatrix);

			POINT pt = point;

			SVGPoint dpt;
			dpt.X = pt.x;
			dpt.Y = pt.y;

			SVGPoint wpt = dpt.matrixTransform(imatrix);

			m_activeTool.Release();

			if (!(nFlags & MK_CONTROL))
				m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &m_activeTool);// = gApp->m_pActivesvgActiveTool;
			else
				m_pDocument->m_app->GetActiveTool(VARIANT_TRUE, &m_activeTool);

			m_numMoves = 0;


			if (m_activeTool)
			{
				SVGMouse svgmouse;
				svgmouse.ptx = pt.x;
				svgmouse.pty = pt.y;
			//	svgmouse.dptx = dpt.X;
			//	svgmouse.dpty = dpt.Y;
				svgmouse.wptx = wpt.X;
				svgmouse.wpty = wpt.Y;
				svgmouse.nFlags = nFlags;
		//		svgmouse.bAlt = m_bAlt;

				m_activeTool->OnButtonDown(this, &svgmouse, &m_dragging);
			}

#if 0

			case ID_SVGTOOL_PATHPEN:
				{
					ASSERT(0);
#if 0
					if (TRUE)
					{
					//	CPDObjectFrameSelected* pObject = NULL;
						CPathElement* path = NULL;

						UINT nResource = 0;

						CHitData* hitdata = NULL;
						IWebElement* object;
						/*nResource = */GetObjectUnderPoint(dpt, m_svgActiveTool, &hitdata, &object);

						if (m_viewGroup->GetActiveElement())
						{
							nResource = m_viewGroup->GetActiveElement()->OnButtonDown(hitdata, nFlags, wpt);
						}

						if (nResource == 0)	// Create new path
						{
						}
					}
#endif
				}
				break;

#if 0
				case ID_SVGTOOL_PATHPEN:
				case TOOL_PENFREE:
				case TOOL_PENADD:
				case TOOL_PENDELETE:
				case TOOL_PENCORNER:
				{
					double x = pt.x;
					double y = pt.y;

					CPathElement* pathElement = NULL;
					CComQIPtr<ILSVGPathElement> path;
					CComQIPtr<ILSVGPathSegList> seglist;
					int cp = -1;
					int ctl = 0;
					double onCurve_t;
					long onCurve_segIndex = -1;

					UINT activeTool = gApp->m_svgActiveTool;

					_bstr_t tagName;
					
					if (pTargetElement)
					{
						BSTR btagName;
						pTargetElement->m_domElement->get_nodeName(&btagName);
						tagName = _bstr_t(btagName);
					}

					if (pTargetElement && !wcscmp(tagName, L"path"))
					{
						pathElement = (CPathElement*)pTargetElement;
						path = pathElement->m_domElement;
						seglist = GetPathSegList(pActiveElement);//pathData->normalizedPathSegList;

					//	pathElement->DrawPathCurve(seglist, m_magnifyMatrix, hDC);

						CComQIPtr<ILSVGLocatable> locatable = pTargetElement->m_domElement;
						CComQIPtr<ILSVGMatrix> matrix0;
						locatable->getScreenCTM(&matrix0);

						CComQIPtr<ILSVGMatrix> matrix;
						matrix0->multiply(m_magnifyMatrix, &matrix);

						cp = pathElement->FindPoint(seglist, matrix, x, y, ctl);
						if (cp < 0)
						{
							GetPointOnSegList(seglist, pt.x, pt.y, 4, &onCurve_segIndex, &onCurve_t);
						}

						if (gApp->m_svgActiveTool == ID_SVGTOOL_PATHPEN)
						{
							if (cp >= 0 && ctl == 0)
							{
								activeTool = TOOL_PENDELETE;
							}
							else if (onCurve_segIndex >= 0)
							{
								activeTool = TOOL_PENADD;
							}
						}
						else
						{
						}
					}

					switch (activeTool)
					{
					case TOOL_PENADD:
						{
							pathElement->InsertAnchorPoint(onCurve_segIndex, onCurve_t);
							pathElement->m_selectedPoints.Add(onCurve_segIndex);
						}
						break;

					case TOOL_PENDELETE:
						{
							pathElement->DeleteAnchorPoint(cp);
						}
						break;

					case TOOL_PENCORNER:
						{
							if (cp >= 0)
							{
								m_viewGroup->SetTargetElement(pathElement, 0);

								if (ctl == 0)
								{
									pathElement->m_selectedPoints.RemoveAll();

									seglist->LockUpdate();

									CPathSeg seg;
									seg = pathElement->GetPathSeg(seglist, cp);
									seg.x[0] = seg.x[1];
									seg.y[0] = seg.y[1];

									seg.x[2] = seg.x[1];
									seg.y[2] = seg.y[1];

									pathElement->PutPathSeg(seglist, cp, seg);

									seglist->UnlockUpdate();

									m_curveCp = cp;
									m_curveCtl = 1;
									pathElement->m_selectedPoints.Add(m_curveCp);

									m_hit = 1;	// Set both control points
								}
								else
								{
									m_curveCp = cp;
									m_curveCtl = ctl;

									m_hit = 2;	// Set only one control point
								}

								m_dragging = 1;
							}
						}
						break;

					case ID_SVGTOOL_PATHPEN:
						{
							if (seglist)
							{
								CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg;
								path->createSVGPathSegCurvetoCubicAbs(
									x, y,
									pathElement->m_lastx, pathElement->m_lasty,
									x, y,
									&seg);

								pathElement->m_lastx = x;
								pathElement->m_lasty = y;

								seglist->get_numberOfItems((unsigned long*)&m_curveCp);
								m_curveCtl = 1;

								pathElement->m_selectedPoints.RemoveAll();

								seglist->appendItem(seg, NULL);
							}
							else	// Create new path element
							{
								CComQIPtr<ILSVGPathElement> path;
								pDocument->GetDOMDocument()->createElement(L"path", (ILDOMElement**)&path);

#if 0
								_bstr_t style = gApp->m_pathSettings->m_domElement->getAttribute(L"style");
								if (style.length() > 0) path->setAttribute(L"style", style);
#endif

								CComQIPtr<ILSVGAnimatedPathData> pathData = path;

								pathData->get_normalizedPathSegList(&seglist);

								CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs;
								path->createSVGPathSegMovetoAbs(pt.x, pt.y, &movetoabs);

								seglist->appendItem(movetoabs, NULL);

								svgsvgElement->appendChild(path, NULL);
								pathElement = (CPathElement*)pDocument->m_pTree->FindDOMElement((ILDOMNode*)path);
								pathElement->m_lastx = x;
								pathElement->m_lasty = y;

								m_curveCp = 0;
								m_curveCtl = 1;

								m_viewGroup->SetTargetElement(pathElement, 0);
							}

							pathElement->m_selectedPoints.Add(m_curveCp);

							m_hit = 1;
							m_dragging = 1;
						}
						break;

					case TOOL_PENFREE:
						{
	#if 0
							int cp = -1;
							int ctl = 0;
							SVGLib::ISVGPathSegListPtr seglist;
							CPathElement* pathElement = NULL;

							if (pActiveElement && !wcscmp(pActiveElement->m_domElement->tagName, L"path"))
							{
								pathElement = (CPathElement*)pActiveElement;

								SVGLib::ISVGAnimatedPathDataPtr pathData = pActiveElement->m_domElement;
								seglist = pathData->normalizedPathSegList;

								cp = pathElement->FindPoint(seglist, pt.x, pt.y, ctl);
							}

							if (cp >= 0 && ctl == 0 && (cp == 0 || cp == seglist->numberOfItems-1))
							{
							// Continue from another subpath

								m_pActivePathElement = pathElement;

								SVGLib::ISVGPathSegCurvetoCubicAbsPtr curveto = seglist->getItem(cp);
								if (curveto)
								{
									m_pointArray.Add(CDblPoint(curveto->x, curveto->y));
								}
								else
								{
									SVGLib::ISVGPathSegMovetoAbsPtr moveto = seglist->getItem(cp);
									if (moveto)
									{
										m_pointArray.Add(CDblPoint(moveto->x, moveto->y));
									}
								}
							}
							else
							{
							// New Subpath
								m_pActivePathElement = NULL;
								m_pointArray.Add(CDblPoint(pt.x, pt.y));
							}

							m_dragging = 1;
	#endif
						}
						break;
					}
				}
				break;
#endif


				case TOOL_TWIRL:
					{
#if 0
						double dx = pt.x - m_pivotPt.x;
						double dy = pt.y - m_pivotPt.y;
						double l = sqrt(dx*dx + dy*dy);

						if (fabs(pt.x-m_pivotPt.x) < 8 &&
							fabs(pt.y-m_pivotPt.y) < 8)
						{
							m_hit = 2;
						}
						else if (fabs(l-m_effectRadius) < 8)
						{
							m_hit = 3;
						}
						else
						{
							for (int i = 0; i < m_pDocument->m_targetElements.GetSize(); i++)
							{
								CElement* pElement = m_pDocument->m_targetElements[i];

							// only process elements that support twirling
								if (!wcscmp(pElement->m_domElement->tagName, L"path"))
								{
									CPathElement* pathElement = (CPathElement*)pElement;

								//	pathElement->DrawPathCurve(hDC, GetMagnifyFactor());	// Erase

									pathElement->SetPolyPointsFromSegList();
								//	pathElement->DrawPolyPoints(hDC);
								}
							}

							m_hit = 1;

							{
								float x = m_pivotPt.x;
								float y = m_pivotPt.y;

								HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
								Ellipse(hDC, x-4, y-4, x+5, y+5);
								Ellipse(hDC, x-m_effectRadius, y-m_effectRadius, x+m_effectRadius, y+m_effectRadius);
								SelectObject(hDC, hOldBrush);
							}
						}

						m_dragging = 1;
#endif
					}
					break;

				case TOOL_TEXT:
					{
#if 0
						m_hit = 0;
						CElementImpl* pElement = pDocument->GetSvgElement()->GetElementUnderPoint(svgpt, m_magnifyMatrix, m_hit);

						CComQIPtr<ILSVGTextContentElement> textContent;
						if (pElement) textContent = pElement->m_domElement;

						if (textContent)
						{
							m_viewGroup->SetTargetElement(pElement, nFlags);

							textContent->getCharNumAtPosition(svgpt, &m_cursorPos);
							if (m_cursorPos >= 0)
							{
								m_initSelCharPos = m_cursorPos;
								m_startSelCharPos = m_cursorPos;
								m_endSelCharPos = m_cursorPos;

								m_pTextElement = (CTextElement*)pElement;

								m_hit = 1;
								m_dragging = 1;

								{
									/*
								CComQIPtr<ISVGTextContentElement> textContent = target;
								if (textContent)
								{
									CTextContent* pTextContent;
									textContent->GetNProp(L"pelement", (DWORD*)&pTextContent);
									pSVGElement->m_pSelectedTextElement = pTextContent->GetTextElement();

									long charpos = pSVGElement->m_pSelectedTextElement->getCharNumAtPosition(svgpt);
									if (charpos >= 0)
									{
										pSVGElement->m_initSelCharPos = charpos;
										pSVGElement->m_startSelCharPos = charpos;
										pSVGElement->m_endSelCharPos = charpos;

										m_dragging = 1;
									}
									else
									{
										pSVGElement->m_pSelectedTextElement = NULL;
									}
								}
								*/
								}
							}
						}
						else
						{
							CComQIPtr<ILSVGTextElement> textel;
							pDocument->GetDOMDocument()->createElement(L"text", (ILDOMElement**)&textel);

							double x; svgpt->get_x(&x);
							double y; svgpt->get_y(&y);

							ASSERT(0);
#if 0
							CComQIPtr<ILSVGAnimatedLength> ax;
							textel->get_x(&ax);
							CComQIPtr<ILSVGLength> xlength;
							ax->get_baseVal(&xlength);
							xlength->put_value(x);

							CComQIPtr<ILSVGAnimatedLength> ay;
							textel->get_y(&ay);
							CComQIPtr<ILSVGLength> ylength;
							ay->get_baseVal(&ylength);
							ylength->put_value(y);
#endif

							CComQIPtr<ILDOMText> text;
							pDocument->GetDOMDocument()->createTextNode(L"Hello", &text);
							textel->appendChild(text, NULL);

							svgsvgElement->appendChild(textel, NULL);

							m_pTextElement = (CTextElement*)pDocument->m_pTree->FindDOMElement((ILSVGElement*)textel);
							m_viewGroup->SetTargetElement(m_pTextElement, 0);
						}
#endif
					}
					break;

				case ID_SVGTOOL_CIRCLE:
				{
					m_radius = 0;
				//	Ellipse(hDC, m_startpt.x-m_radius, m_startpt.y-m_radius, m_startpt.x + m_radius+1, m_startpt.y + m_radius+1);

					m_dragging = 1;
				}
				break;

				case ID_SVGTOOL_ELLIPSE:
				{
				//	Ellipse(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);
					m_dragging = 1;
				}
				break;

				case TOOL_RECT:
				{
				//	Ellipse(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);
					m_dragging = 1;
				}
				break;

				case ID_SVGTOOL_LINE:
				{
				//	MoveToEx(hDC, m_startpt.x, m_startpt.y, NULL);
				//	LineTo(hDC, pt.x, pt.y);
					m_dragging = 1;
				}
				break;

				case TOOL_ZOOM:
					{
						m_dragging = 1;
						m_zoomRect.SetRectEmpty();
					}
					break;

				case TOOL_HAND:
					{
						::SetCursor(LoadCursor(_Module.m_hInst, MAKEINTRESOURCE(IDC_HAND2)));
						m_dragging = 1;
					}
					break;
			}
#endif

		//	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		//	SetROP2(hDC, oldR2);
		//	ReleaseDC(hwnd, hDC);

			if (m_dragging)
			{
				m_startDragCursor = ::GetCursor();
			//	SetCapture();

				m_startpoint = point;
				m_oldpoint = point;

				m_startpt = pt;
				m_oldpt = pt;

				m_dstartpt = dpt;
				m_dpt = m_dstartpt;
				m_doldpt = m_dpt;
			}
		}
	}
#endif
}

void CLSVGBehavior::OnButtonUp(UINT nFlags, POINT point, int iButton)
{
	CEXMLDocument* pDocument = m_pDocument;

	LXML::Document* domdocument = m_pDocument->get_DOMDocument();

	LSVG::SVGDocument* svgDocument = domdocument;

/*	if (svgDocument == NULL)
	{
	}
	else
		*/
	{
		LSVG::SVGSVGElement* svg = svgDocument->get_documentElement();
		ASSERT(svg != NULL);

//		long scrollposX = 0;// m_horz->get_pos(&scrollposX);
//		long scrollposY = 0;// m_vert->get_pos(&scrollposY);

		POINT pt = point;
/*		pt.x -= m_offset.x;
		pt.y -= m_offset.y;
		pt.x += scrollposX;
		pt.y += scrollposY;
*/
		if (m_dragging)
		{
			/*
			HDC hDC = GetDC(hwnd);
			IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom);
			POINT org;
			org.x = m_imageRect.left + m_offset.x-scrollposX;
			org.y = m_imageRect.left + m_offset.y-scrollposY;
			POINT oldOrg;
			SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);
			int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
			*/

			ReleaseCapture();
			m_dragging = 0;

			SVGMouse svgmouse;
			svgmouse.ptx = pt.x;
			svgmouse.pty = pt.y;
		//	svgmouse.wtpx = wpt.X;	// TODO
		//	svgmouse.wpty = wpt.Y;
			svgmouse.nFlags = nFlags;
		//	svgmouse.bAlt = m_bAlt;

			m_activeTool->OnButtonUp(this, &svgmouse);

		// TODO, don't always do this
			CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
			paintSite->InvalidateRect(NULL);

#if 0
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetActiveSelectedElement(&selectedElement);

			CComPtr<IEElement> pActiveElement;
			if (selectedElement)
				selectedElement->get_eElement(&pActiveElement);

			switch (gApp->m_svgActiveTool)
			{
			case ID_SVGTOOL_SELECT:
				{
					InvalidateInvalidRect();

					CComQIPtr<IOleUndoManager> undoManager;
					pDocument->get_undoManager(&undoManager);

					if (m_hit == 1)
					{
#if 0
						CComObject<CWEUndoMoveObjects>* pUndo;
						CComObject<CWEUndoMoveObjects>::CreateInstance(&pUndo);
						//pUndo->AddRef();

						pUndo->m_pDocument = pDocument;
						pUndo->m_dx = m_oldpt.x-m_startpt.x;
						pUndo->m_dy = m_oldpt.y-m_startpt.y;
						pUndo->m_bSourceEditLast = pDocument->m_bSourceEditLast;
						pUndo->m_sourceText = m_sourceText;

						for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
						{
							CComPtr<IWebElement> pElement;
							m_viewGroup->m_targetElements[i]->get_eElement(&pElement);

							GUID guid;
							pElement->m_domElement->get_uniqID(&guid);
							pUndo->m_targetElements.Add(guid);
						}

						undoManager->Add(pUndo);

						pDocument->m_bSourceEditLast = false;
						m_sourceText = NULL;
#endif
					}
					else
					{
					}
				}
				break;


#if 0
			case TOOL_TWIRL:
				{
					if (m_hit == 1)
					{
						for (int i = 0; i < m_pDocument->m_targetElements.GetSize(); i++)
						{
							CElement* pElement = m_pDocument->m_targetElements[i];
							if (!wcscmp(pElement->m_domElement->tagName, L"path"))
							{
								CPathElement* pathElement = (CPathElement*)pElement;

								SVGLib::ISVGAnimatedPathDataPtr pathData = pathElement->m_domElement;
								SVGLib::ISVGPathSegListPtr seglist = pathData->normalizedPathSegList;
								
								seglist->clear();
								pathElement->ConvertFlatToCurves(seglist);

								pathElement->m_subPoints.RemoveAll();
								pathElement->m_flatPoints.RemoveAll();
							}
						}

						{
							float x = m_pivotPt.x;
							float y = m_pivotPt.y;

							HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
							Ellipse(hDC, x-4, y-4, x+5, y+5);
							Ellipse(hDC, x-m_effectRadius, y-m_effectRadius, x+m_effectRadius, y+m_effectRadius);
							SelectObject(hDC, hOldBrush);
						}

						InvalidateInvalidRect();
					}
				}
				break;
#endif

			case ID_SVGTOOL_DIRECT:
				{
					if (m_hit == 0)	// Selection rectangle
					{
#if 0
						DrawFocusRect(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);

						if (!(nFlags & MK_SHIFT))
						{
							for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
							{
								CElement* pElement = pDocument->m_targetElements[i];
								if (!wcscmp(pElement->m_domElement->tagName, L"path"))
								{
									((CPathElement*)pElement)->m_selectedPoints.RemoveAll();
								}
							}
						}

						double x1, y1, x2, y2;

						if (m_startpt.x < m_oldpt.x)
						{
							x1 = m_startpt.x;
							x2 = m_oldpt.x;
						}
						else
						{
							x2 = m_startpt.x;
							x1 = m_oldpt.x;
						}

						if (m_startpt.y < m_oldpt.y)
						{
							y1 = m_startpt.y;
							y2 = m_oldpt.y;
						}
						else
						{
							y2 = m_startpt.y;
							y1 = m_oldpt.y;
						}

						pDocument->m_pTree->SelectPointsInRect(x1, y1, x2, y2);
#endif
					}
					else
					{
					//	Invalidate();
						InvalidateInvalidRect();
					}
				}
				break;
		
			case ID_SVGTOOL_PATHPEN:
				{
					//Invalidate();
					InvalidateInvalidRect();
				}
				break;
				
#if 0
			case TOOL_PENFREE:
				{
					SVGLib::ISVGPathElementPtr path;
					
					if (m_pActivePathElement)	// Add to already existing path
					{
						path = m_pActivePathElement->m_domElement;
					}
					else
					{
						path = m_pDocument->GetDOMDocument()->createElement(L"path");
					}
					
					SVGLib::ISVGAnimatedPathDataPtr pathData = path;
					
					g_pathElement = path;
					g_pathSegList = pathData->normalizedPathSegList;
					g_pathSize = g_pathSegList->numberOfItems;

					int size = m_pointArray.GetSize();
					FitCurve((Point2*)m_pointArray.GetData(), size, gApp->m_fitCurveError);		//  Fit the Bezier curves
					
					if (!m_pActivePathElement)
					{
						m_pDocument->GetDOMDocument()->documentElement->appendChild(path);
						CPathElement* pathElement = (CPathElement*)m_pDocument->m_pTree->FindDOMElement(path);
						m_pDocument->SetTargetElement(pathElement, 0);
					}
				}
				break;
#endif

			case ID_SVGTOOL_CIRCLE:
			case ID_SVGTOOL_ELLIPSE:
			case TOOL_RECT:
			case ID_SVGTOOL_LINE:
				{
					CComQIPtr<ILSVGElement> element;
					
					if (m_svgActiveTool == ID_SVGTOOL_CIRCLE)
					{
#if 0
						Ellipse(hDC, m_startpt.x-m_radius, m_startpt.y-m_radius, m_startpt.x + m_radius+1, m_startpt.y + m_radius+1);
						
						float cx = m_startpt.x;
						float cy = m_startpt.y;
						float r = m_radius;
						
						if (gApp->m_bCreateAsPath)
						{
							SVGLib::ISVGPathElementPtr path = m_pDocument->GetDOMDocument()->createElement(L"path");
							
							SVGLib::ISVGAnimatedPathDataPtr pathData = path;
							SVGLib::ISVGPathSegListPtr seglist = pathData->pathSegList;
							
							seglist->LockUpdate();
							SetPathSegListToEllipse(seglist, cx-r, cy-r, cx+r, cy+r);
							seglist->UnlockUpdate();
							
							element = path;
						}
						else
						{
							SVGLib::ISVGCircleElementPtr circle = m_pDocument->GetDOMDocument()->createElement(L"circle");
							circle->cx->baseVal->value = cx;
							circle->cy->baseVal->value = cy;
							circle->r->baseVal->value = r;
							
							element = circle;
						}
#endif
					}
					else if (m_svgActiveTool == ID_SVGTOOL_ELLIPSE)
					{
					//	Ellipse(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);
						
						if (abs(m_startpoint.x-point.x) < 2 || abs(m_startpoint.y-point.y) < 2)
						{
						}
						else
						{
							float width = m_oldpt.x - m_startpt.x;
							float height = m_oldpt.y - m_startpt.y;
							float cx = m_startpt.x + width/2;
							float cy = m_startpt.y + height/2;
							float rx = width/2;
							float ry = height/2;
							
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
								CComQIPtr<ILSVGEllipseElement> ellipse;
								pDocument->GetDOMDocument()->createElement(L"ellipse", (ILDOMElement**)&ellipse);

								{
									CComQIPtr<ILSVGAnimatedLength> alength;
									ellipse->get_cx(&alength);
									CComQIPtr<ILSVGLength> length;
									alength->get_baseVal(&length);
									length->put_value(cx);
								}

								{
									CComQIPtr<ILSVGAnimatedLength> alength;
									ellipse->get_cy(&alength);
									CComQIPtr<ILSVGLength> length;
									alength->get_baseVal(&length);
									length->put_value(cy);
								}

								{
									CComQIPtr<ILSVGAnimatedLength> alength;
									ellipse->get_rx(&alength);
									CComQIPtr<ILSVGLength> length;
									alength->get_baseVal(&length);
									length->put_value(rx);
								}

								{
									CComQIPtr<ILSVGAnimatedLength> alength;
									ellipse->get_ry(&alength);
									CComQIPtr<ILSVGLength> length;
									alength->get_baseVal(&length);
									length->put_value(ry);
								}

								element = ellipse;
							}
						}
					}
					else if (m_svgActiveTool == TOOL_RECT)
					{
#if 0
						SVGLib::ISVGRectElementPtr frect = gApp->m_rectSettings->m_domElement;
						int ewidth = frect->rx->baseVal->value*2;
						int eheight = frect->ry->baseVal->value*2;
						RoundRect(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y, ewidth, eheight);

						float x = m_startpt.x;
						float y = m_startpt.y;
						float width = m_oldpt.x - m_startpt.x;
						float height = m_oldpt.y - m_startpt.y;
						float rx = frect->rx->baseVal->value;
						float ry = frect->ry->baseVal->value;

						if (gApp->m_bCreateAsPath)
						{
							SVGLib::ISVGPathElementPtr path = m_pDocument->GetDOMDocument()->createElement(L"path");

							SVGLib::ISVGAnimatedPathDataPtr pathData = path;
							SVGLib::ISVGPathSegListPtr seglist = pathData->pathSegList;

							seglist->LockUpdate();
							SetPathSegListToRoundRect(seglist, x, y, x+width-1, y+height-1, rx, ry, TRUE);
							seglist->UnlockUpdate();

							element = path;
						}
						else
						{
							SVGLib::ISVGRectElementPtr rect = m_pDocument->GetDOMDocument()->createElement(L"rect");

							rect->x->baseVal->value = x;
							rect->y->baseVal->value = y;
							rect->width->baseVal->value = width;
							rect->height->baseVal->value = height;
							rect->rx->baseVal->value = rx;
							rect->ry->baseVal->value = ry;

							element = rect;
						}
#endif
					}
					else if (m_svgActiveTool == ID_SVGTOOL_LINE)
					{
						if (abs(m_startpoint.x-point.x) >= 2 && abs(m_startpoint.y-point.y) >= 2)
						{
							CComQIPtr<ILSVGLineElement> line;
							pDocument->GetDOMDocument()->createElement(L"line", (ILDOMElement**)&line);

							{
								CComQIPtr<ILSVGAnimatedLength> alength;
								line->get_x1(&alength);
								CComQIPtr<ILSVGLength> length;
								alength->get_baseVal(&length);
								length->put_value(m_newObjectBounds.X);
							}

							{
								CComQIPtr<ILSVGAnimatedLength> alength;
								line->get_y1(&alength);
								CComQIPtr<ILSVGLength> length;
								alength->get_baseVal(&length);
								length->put_value(m_newObjectBounds.Y);
							}

							{
								CComQIPtr<ILSVGAnimatedLength> alength;
								line->get_x2(&alength);
								CComQIPtr<ILSVGLength> length;
								alength->get_baseVal(&length);
								length->put_value(m_newObjectBounds.X+m_newObjectBounds.Width);
							}

							{
								CComQIPtr<ILSVGAnimatedLength> alength;
								line->get_y2(&alength);
								CComQIPtr<ILSVGLength> length;
								alength->get_baseVal(&length);
								length->put_value(m_newObjectBounds.Y+m_newObjectBounds.Height);
							}

							element = line;
						}
					}
					
					if (element)
					{
						ASSERT(0);
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
				}
				break;

			case TOOL_ZOOM:
				{
#if 0
					HDC hDC = GetDC(hwnd);
					IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom);
					POINT org;
					org.x = m_imageRect.left + m_offset.x-scrollposX;
					org.y = m_imageRect.left + m_offset.y-scrollposY;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
					HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
#endif

					double aspect = (double)m_imageRect.Height()/m_imageRect.Width();

#if 0
				// Erase old zoomrect
					Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

					SelectObject(hDC, hOldBrush);
					SetROP2(hDC, oldR2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
					ReleaseDC(hwnd, hDC);
#endif

					m_zoomRect.NormalizeRect();

					if (m_zoomRect.Width() <= 2 || m_zoomRect.Height() <= 2)
					{
						double x = m_startpt.x/m_magnify;
						double y = m_startpt.y/m_magnify;

					//	double docwidth = m_imageRect.Width();///m_magnify;
					//	double docheight = m_imageRect.Height();///m_magnify;

						if (!(nFlags & MK_SHIFT/*MK_ALT*/))	// Zoom in
						{
#if 0
							ZoomToRect2(
								x-m_imageRect.Width()/m_magnify/4.0,
								y-m_imageRect.Height()/m_magnify/4.0,
								x+m_imageRect.Width()/m_magnify/4.0,
								y+m_imageRect.Height()/m_magnify/4.0);
#endif
						}
						else	// Zoom out
						{
							ATLTRACE("Zoom out rect\n");
#if 0
							ZoomToRect2(
								x-m_imageRect.Width()/m_magnify,
								y-m_imageRect.Height()/m_magnify,
								x+m_imageRect.Width()/m_magnify,
								y+m_imageRect.Height()/m_magnify);
#endif
						}
					}
					else
					{
					//	ZoomToRect(m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);
#if 0
						ZoomToRect2(
							m_zoomRect.left/m_magnify,
							m_zoomRect.top/m_magnify,
							m_zoomRect.right/m_magnify,
							m_zoomRect.bottom/m_magnify
							);
#endif
					}
				}
				break;
			}
#endif

			/*
			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			SetROP2(hDC, oldR2);
			ReleaseDC(hwnd, hDC);
			*/
		}
	}
}

void CLSVGBehavior::OnMouseMove(UINT nFlags)
{
	OnMouseMove(nFlags, CPoint(m_clientX, m_clientY));
}

void CLSVGBehavior::OnMouseMove(UINT nFlags, POINT point)
{
	CEXMLDocument* pDocument = m_pDocument;

	CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;

	CComPtr<ILDOMDocument> domdocument;
	m_pDocument->get_DOMDocument(&domdocument);

	LSVG::SVGSVGElement* svgsvgElement = domdocument->get_documentElement();

	CComQIPtr<ILSVGDocument> svgDocument = domdocument;
	if (svgDocument == NULL)
	{
	}
	else
	{
/*
		CComPtr<ILDOMAbstractView> view;
		m_pBehaviorSite->GetView(&view);

		CComQIPtr<ILHTMLWindow> window = view;
		double translateX;
		double translateY;
		window->get_currentTranslateX(&translateX);
		window->get_currentTranslateY(&translateY);

		double magnify;
		window->get_magnify(&magnify);

		m_viewMatrix.Release();

		CComPtr<ILSVGMatrix> mat1;
		svgsvgElement->createSVGMatrix(&mat1);
		CComPtr<ILSVGMatrix> mat;
		mat1->scaleNonUniform(magnify, magnify, &mat);
		mat->translate(translateX, translateY, &m_viewMatrix);
*/
		CComPtr<ILSVGMatrix> viewMatrix;
		GetViewMatrix(&viewMatrix);

		CComPtr<ILSVGMatrix> imatrix;
		viewMatrix->inverse(&imatrix);

		POINT pt = point;

		SVGPoint dpt;
		dpt.X = pt.x;
		dpt.Y = pt.y;

		SVGPoint wpt = dpt.matrixTransform(imatrix);

		{
			if (m_activeTool)
			{
				SVGMouse svgmouse;
				svgmouse.ptx = pt.x;
				svgmouse.pty = pt.y;
				//svgmouse.dptx = dpt.X;
				//svgmouse.dpty = dpt.Y;
				svgmouse.wptx = wpt.X;
				svgmouse.wpty = wpt.Y;
				svgmouse.nFlags = nFlags;
	//			svgmouse.bAlt = m_bAlt;
				m_activeTool->OnMouseMove(this, &svgmouse);
			}


#if 0
			case ID_SVGTOOL_DIRECT:
			case ID_SVGTOOL_PATHPEN:
			//case ID_TOOL_PATHCORNER:
				{
					if (m_hit == 0)	// Selection Rectangle
					{
					//	DrawFocusRect(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);
					//	DrawFocusRect(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);
					}
					else
					{
#if 0
						ASSERT(m_curveCp >= 0);
#endif

						SVGPoint oldpt2 = woldpt;
						SVGPoint newpt2 = wpt;

						//LDraw::RectF totalrc(999999, 999999, -999999, -999999);

						if (m_hitdata == NULL/*m_curveCtl == 0*/)	// Clicked on anchor point
						{
							for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
							{
#if 0
								CESelectedElementImpl* pSelectedElement = m_viewGroup->m_targetElements[i];
								CElementImpl* pObject = pSelectedElement->GetElement();

								//LDraw::RectF invalidRc(999999, 999999, -999999, -999999);

								//CComQIPtr<IPDObject> object = pObject->m_object;
								//if (object)
								{
									/*
									PDObjectType objectType;
									object->get_objectType(&objectType);

									CComQIPtr<IPDMatrix> matrix;
									object->getScreenCTM(&matrix);

									CComQIPtr<IPDMatrix> inversematrix;
									matrix->inverse(&inversematrix);

									PointD xnewpt2;
									inversematrix->transformPoint(&newpt2, &xnewpt2);

									PointD xoldpt2;
									inversematrix->transformPoint(&oldpt2, &xoldpt2);
									*/
									CComQIPtr<ILSVGTransformable> transformable = pObject->m_domElement;
									if (transformable)
									{
										CComQIPtr<ILSVGMatrix> matrix;
										transformable->getScreenCTM(&matrix);

										CComQIPtr<ILSVGMatrix> inversematrix;
										matrix->inverse(&inversematrix);

										CComPtr<ILSVGPoint> svgPoint;
										svgsvgElement->createSVGPoint(&svgPoint);

										CComPtr<ILSVGPoint> xsvgPoint;

										//PointD xnewpt2;
										//inversematrix->transformPoint(&newpt2, &xnewpt2);
										svgPoint->put_x(newpt2.X);
										svgPoint->put_y(newpt2.Y);
										svgPoint->matrixTransform(inversematrix, &xsvgPoint);
										SVGPoint xnewpt2 = xsvgPoint;
										xsvgPoint.Release();

									//	PointD xoldpt2;
									//	inversematrix->transformPoint(&oldpt2, &xoldpt2);
										svgPoint->put_x(oldpt2.X);
										svgPoint->put_y(oldpt2.Y);
										svgPoint->matrixTransform(inversematrix, &xsvgPoint);
										SVGPoint xoldpt2 = xsvgPoint;
										xsvgPoint.Release();

										double xnewpt2x = xnewpt2.X;
										double xnewpt2y = xnewpt2.Y;
											
										double xoldpt2x = xoldpt2.X;
										double xoldpt2y = xoldpt2.Y;

#if 0
										CComQIPtr<ILSVGPathElement> path = pSelectedElement->GetElement()->m_domElement;

										if (path)
										{
											CESelectedSVGPathElement* pFrame = (CESelectedSVGPathElement*)pSelectedElement;
											pFrame->/*m_path->*/MovePoints(xnewpt2x-xoldpt2x, xnewpt2y-xoldpt2y, /*invalidRc,*/ false);
										}
#endif
										pSelectedElement->MoveSelectedPoints(m_hitdata, xnewpt2, xoldpt2, xnewpt2x-xoldpt2x, xnewpt2y-xoldpt2y/*, invalidRc,*/);

										/*
										if (pObject->m_wrapPath)
										{
											LDraw::RectF invalidRc2;
											pObject->m_wrapPath->MovePoints(xnewpt2x-xoldpt2x, xnewpt2y-xoldpt2y, invalidRc2, false);

											LDraw::RectF::Union(invalidRc, invalidRc, invalidRc2);
										}

										LDraw::RectF::Union(totalrc, totalrc, invalidRc);
										*/
									}
								}
#endif
							}
						}
						else	// Control point
						{
							ASSERT(0);
#if 0
						//	CPDObjectFrameSelected* pathElement = (CPDObjectFrameSelected*)m_pActiveObject;

							CComQIPtr<ILSVGTransformable> transformable = m_viewGroup->m_pActiveElement->GetElement()->m_domElement;

							CComQIPtr<ILSVGMatrix> matrix;
							transformable->getScreenCTM(&matrix);

							CComQIPtr<ILSVGMatrix> inversematrix;
							matrix->inverse(&inversematrix);

							SVGPoint xnewpt2 = newpt2.matrixTransform(inversematrix);
							SVGPoint xoldpt2 = oldpt2.matrixTransform(inversematrix);

							LDraw::RectF invalidRc;

							m_viewGroup->GetActiveElement()/*m_pActivePath*/->MoveSelectedPoints(m_hitdata, xnewpt2, xoldpt2, 0, 0);

#if 0
							if (m_hit == 1)	// Same length
							{
								m_pActivePath->GetPath()->SetControlPointsSameLength(m_curveCp, m_curveCtl, xnewpt2x, xnewpt2y/*, invalidRc*/);
							}
							else if (m_hit == 2)
							{
								m_pActivePath->GetPath()->SetPathSegControlPoints(m_curveCp, m_curveCtl, xnewpt2x, xnewpt2y/*, invalidRc*/);
							}
							else
								ASSERT(0);
#endif


							//LDraw::RectF::Union(totalrc, totalrc, invalidRc);
#endif
						}
					}
				}
				break;

#if 0
			case TOOL_PENFREE:
				{
					m_pointArray.Add(CDblPoint(pt.x, pt.y));
					
					int size = m_pointArray.GetSize();
					
				//	MoveToEx(hDC, m_pointArray[size-2].x, m_pointArray[size-2].y, NULL);
				//	LineTo(hDC, m_pointArray[size-1].x, m_pointArray[size-1].y);
				}
				break;
#endif

			case TOOL_TEXT:
				{
#if 0
					if (m_pTextElement)
					{
						CComQIPtr<ILSVGTextElement> text = m_pTextElement->m_domElement;

						long charpos;
						text->getCharNumAtPosition(svgpt, &charpos);

						if (charpos >= 0)
						{
							m_cursorPos = charpos;

							if (charpos < m_initSelCharPos)
							{
								m_startSelCharPos = charpos;
								m_endSelCharPos = m_initSelCharPos;
							}
							else
							{
								m_endSelCharPos = charpos;
								m_startSelCharPos = m_initSelCharPos;
							}

							text->selectSubString(m_startSelCharPos, m_endSelCharPos - m_startSelCharPos+1);

							paintSite->InvalidateRect(NULL);
						}
					}
#endif
				}
				break;


			case TOOL_TWIRL:
				{
#if 0
					if (m_hit == 1)
					{
						for (int i = 0; i < m_pDocument->m_targetElements.GetSize(); i++)
						{
							CElement* pElement = m_pDocument->m_targetElements[i];

							if (!wcscmp(pElement->m_domElement->tagName, L"path"))
							{
								CPathElement* pathElement = (CPathElement*)pElement;

							//	pathElement->DrawPolyPoints(hDC);

								pathElement->SetPolyPointsFromSegList();

							//	SVGLib::ISVGTransformPtr transform = pElement->GetMatrixTransform();

								double cx = m_pivotPt.x;
								double cy = m_pivotPt.y;

								double dangle;
								{
									static double doldvalue = 0;
									static double g_oldValue = 0;

									double radian;

									double dx = (double)(pt.x-cx);
									double dy = (double)(pt.y-cy);
									double distance = sqrt(dx*dx+dy*dy);
									double distance2 = distance;

									if (distance2 == 0.0) distance2 = 0.0001;
									radian = acos(dx/distance2);
									if (dy < 0) radian = M_PI*2 - radian;

									double dvalue = radian;//*(180.0/M_PI);

								//	long loldvalue;
								//	m_pProp->GetParamTags((PARAM_ANGLE_Value), &loldvalue, (TAG_DONE));

									if (m_numMoves == 0)
									{
										g_oldValue = radian;
										doldvalue = radian;
									//	g_oldValue = doldvalue;
									//	while (g_oldValue < 0) g_oldValue += M_PI*2;
									//	while (g_oldValue >= M_PI*2) g_oldValue -= M_PI*2;
									}

								//	double doldvalue = g_oldValue;//loldvalue/65536.0;

									double delta = dvalue - g_oldValue;

									if (delta < -M_PI)
									{
										delta = dvalue + (M_PI*2-g_oldValue);
									}
									else if (delta > M_PI)
									{
										delta = dvalue - g_oldValue - M_PI*2;
									}

									g_oldValue = dvalue;

									dvalue = doldvalue + delta;

									doldvalue = dvalue;

									dangle = dvalue;
								}

								/*
								double dangle;
								{
									double dx = pt.x - m_startpt.x;
									double dy = pt.y - m_startpt.y;

									double distance = sqrt(dx*dx + dy*dy);
									double distance2 = distance;

									if (distance2 == 0.0) distance2 = 0.00001;
									if (dy < 0) distance2 =-distance2;
									double angle = acos(dx/distance2);
									if (dy < 0) angle += M_PI;

									dangle = angle;// * 180/M_PI;
								}
								*/

								double maxdistance = m_effectRadius;

								int numpoints = pathElement->m_flatPoints.GetSize();
								DblPOINT* points = pathElement->m_flatPoints.GetData();

								for (int i = 0; i < numpoints; i++)
								{
									double dx = points[i].x-cx;
									double dy = points[i].y-cy;

									double distance = sqrt(dx*dx + dy*dy);

									if (distance < maxdistance)
									{
										if (distance == 0.0) distance = 0.01;

										double angle = acos(dx/distance);
										if (dy < 0) angle = M_PI*2 - angle;

										double addangle;
										addangle = ((maxdistance-distance)/maxdistance)*dangle;

										angle += addangle;

										double x2 = cos(angle)*distance;
										double y2 = sin(angle)*distance;

										points[i].x = x2 + cx;
										points[i].y = y2 + cy;
									}
									else
									{
									}
								}

							//	pathElement->DrawPolyPoints(hDC);
							}
						}
					}
					else
					{
						if (m_hit == 2)
						{
							m_pivotPt.x = pt.x;
							m_pivotPt.y = pt.y;
						}
						else if (m_hit == 3)
						{
							double dx = pt.x - m_pivotPt.x;
							double dy = pt.y - m_pivotPt.y;

							m_effectRadius = sqrt(dx*dx + dy*dy);
						}

						/*
						{
							float x = m_pivotPt.x;
							float y = m_pivotPt.y;

							HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
							Ellipse(hDC, x-4, y-4, x+5, y+5);
							Ellipse(hDC, x-m_effectRadius, y-m_effectRadius, x+m_effectRadius, y+m_effectRadius);
							SelectObject(hDC, hOldBrush);
						}
						*/
					}
#endif
				}
				break;
	
#endif

		//	m_oldpt = pt;

			m_numMoves++;
		}

		m_oldpt = pt;
		m_doldpt = m_dpt;
		m_oldpoint = m_point;
	}
}

void CLSVGBehavior::OnKeyDown(long virtKey)
{
	OnSetCursor();

	switch (virtKey)
	{
	case DOM_VK_DELETE://VK_DELETE:
		{
			m_layoutView->ClearSelection();
		}
		break;
	}

	OnMouseMove(m_nFlags);
}

void CLSVGBehavior::OnKeyUp(long nKey)
{
	/*
	UINT nFlags = 0;
	if (GetAsyncKeyState(VK_SHIFT) & (1<<15)) nFlags |= MK_SHIFT;
	if (GetAsyncKeyState(VK_CONTROL) & (1<<15)) nFlags |= MK_CONTROL;
	*/

	OnSetCursor();

	OnMouseMove(m_nFlags);
}

STDMETHODIMP CLSVGBehavior::GetViewGroup(IEXMLViewGroup **pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = m_viewGroup;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLSVGBehavior::GetSVGSVGElement(/*[out,retval]*/ ILSVGSVGElement* *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComPtr<IEXMLDocument> eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> document;
	eDocument->get_DOMDocument(&document);

	CComPtr<ILDOMElement> domElement;
	document->get_documentElement(&domElement);

	CComQIPtr<ILSVGSVGElement> svgsvgElement = domElement;

	*pVal = svgsvgElement.Detach();

	return S_OK;
}

STDMETHODIMP CLSVGBehavior::GetHTMLWindow(/*[out,retval]*/ ILHTMLWindow* *pVal)
{
	ASSERT(0);
#if 0
	if (pVal == NULL) return E_POINTER;

	CComPtr<ILDOMAbstractView> view;
	m_pBehaviorSite->GetView(&view);

	CComQIPtr<ILHTMLWindow> htmlWindow = view;

	*pVal = htmlWindow;
	(*pVal)->AddRef();
#endif

	return S_OK;
}

STDMETHODIMP CLSVGBehavior::GetViewMatrix(/*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(0);
#if 0
//	CComPtr<ILDOMAbstractView> view;
//	m_pBehaviorSite->GetView(&view);

	CComPtr<ILHTMLWindow> window;
	m_pBehaviorSite->GetWindow(&window)

	CComPtr<ILDOMElement> element;
	m_pBehaviorSite->GetElement(&element);
	CComQIPtr<ILSVGGlyphElement> glyphElement = element;

	CEXMLDocument* pDocument = m_pDocument;

	CComPtr<ILDOMDocument> document;
	m_pDocument->get_DOMDocument(&document);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	document->get_documentElement((ILDOMElement**)&svgsvgElement);

	double translateX;
	double translateY;
	window->get_currentTranslateX(&translateX);
	window->get_currentTranslateY(&translateY);

	double magnify;
	window->get_magnify(&magnify);

	//m_viewMatrix.Release();

	CComPtr<ILSVGMatrix> wmat;
	window->GetMatrix(&wmat);

	CComPtr<ILSVGMatrix> mat0;
	svgsvgElement->createSVGMatrix(&mat0);

	CComPtr<ILSVGMatrix> viewMatrix;

	if (glyphElement)
	{
		/*
		CComPtr<ILSVGMatrix> mat;
		mat1->translate(translateX, translateY, &mat);

		mat->scaleNonUniform(magnify, -magnify, &viewMatrix);
		*/
		CComPtr<ILSVGMatrix> mat1;
		mat0->scaleNonUniform(magnify, -magnify, &mat1);

		CComPtr<ILSVGMatrix> mat2;
		mat1->translate(translateX, translateY, &mat2);

		viewMatrix = mat2;
	}
	else
	{
		CComPtr<ILSVGMatrix> mat1;
		mat0->multiply(wmat, &mat1);

		CComPtr<ILSVGMatrix> mat2;
		mat1->scaleNonUniform(magnify, magnify, &mat2);

		CComPtr<ILSVGMatrix> mat3;
		mat2->translate(translateX, translateY, &mat3);

		viewMatrix = mat3;
	}

	*pVal = viewMatrix;
	(*pVal)->AddRef();
#endif

	return S_OK;
}

STDMETHODIMP CLSVGBehavior::GetEElement(IEElement **pVal)
{
	CComPtr<ILDOMElement> element;
	m_pBehaviorSite->GetElement(&element);

	return m_pDocument->GetEElementFromDOMElement(element, pVal);
}

#endif