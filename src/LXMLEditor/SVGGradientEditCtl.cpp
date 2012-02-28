// SVGGradientEditCtl.cpp : Implementation of CSVGGradientEditCtl

#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGGradientEditCtl.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CSVGGradientEditCtl

// TODO, optimize this another way
inline void SetMedianPixel(RGBTRIPLE *rgbDest, RGBTRIPLE *rgbSrc, LONG median)
{
	if (median <= 0)
	{
		*rgbDest = *rgbSrc;
	}
	else if (median >= 255)
	{
		;
	}
	else
	{
		rgbDest->rgbtRed = rgbSrc->rgbtRed + ((((short)rgbDest->rgbtRed - rgbSrc->rgbtRed) * median + 127) >> 8);
		rgbDest->rgbtGreen = rgbSrc->rgbtGreen + ((((short)rgbDest->rgbtGreen - rgbSrc->rgbtGreen) * median + 127) >> 8);
		rgbDest->rgbtBlue = rgbSrc->rgbtBlue + ((((short)rgbDest->rgbtBlue - rgbSrc->rgbtBlue) * median + 127) >> 8);
	}
}

//#include "EditGradientDlg.h"

ARGBPixel* CreateGradient(ILSVGGradientElement* gradient, UINT TotalColors)
{
	ARGBPixel*	ColorSpread;
	ColorSpread = (ARGBPixel*)GlobalAlloc(0, TotalColors*sizeof(ARGBPixel));

	double last_offset = -1;
	int s_last_offset = -1;

	int last_red;
	int last_green;
	int last_blue;
	int last_alpha;

	CComPtr<ILDOMNode> node;
	gradient->get_firstChild(&node);
	while (node != NULL)
	{
		CComQIPtr<ILSVGStopElement> stop = node;
		if (stop)
		{
			CComPtr<ILSVGAnimatedNumber> animoffset;
			stop->get_offset(&animoffset);

			double offset;
			animoffset->get_animVal(&offset);

			if (offset < 0) offset = 0;
			else if (offset > 1) offset = 1;
			if (offset < last_offset) offset = last_offset;

			CComQIPtr<ILSVGStylable> stylableStop = stop;

			CComQIPtr<ILCSSStyleDeclaration> style;
			stylableStop->get_style(&style);

		// stop-color
			CComPtr<ILSVGColor> csscolor;
			style->getPropertyCSSValue(L"stop-color", (ILCSSValue**)&csscolor);

			CComPtr<ILRGBColor> rgbColor;
			csscolor->get_rgbColor(&rgbColor);

			double fred;
			{
				CComPtr<ILCSSPrimitiveValue> cssred;
				rgbColor->get_red(&cssred);
				cssred->getFloatValue(CSS_NUMBER, &fred);
			}

			double fgreen;
			{
				CComPtr<ILCSSPrimitiveValue> cssgreen;
				rgbColor->get_green(&cssgreen);
				cssgreen->getFloatValue(CSS_NUMBER, &fgreen);
			}

			double fblue;
			{
				CComPtr<ILCSSPrimitiveValue> cssblue;
				rgbColor->get_blue(&cssblue);
				cssblue->getFloatValue(CSS_NUMBER, &fblue);
			}

		// stop-opacity
			double fopacity;
			{
				CComPtr<ILCSSPrimitiveValue> cssopacity;
				style->getPropertyCSSValue(L"stop-opacity", (ILCSSValue**)&cssopacity);
				if (cssopacity)
					cssopacity->getFloatValue(CSS_NUMBER, &fopacity);
				else
					fopacity = 1;
			}
			int opacity = (int)(fopacity*255);
			if (opacity < 0) opacity = 0;
			else if (opacity > 255) opacity = 255;
		//

			int dest_red = (int)fred;
			int dest_green = (int)fgreen;
			int dest_blue = (int)fblue;
			int dest_alpha = opacity;

			if (last_offset < 0)
			{
				last_offset = 0;
				s_last_offset = 0;
				last_red = dest_red;
				last_green = dest_green;
				last_blue = dest_blue;
				last_alpha = dest_alpha;
			}

			int s_offset = ((TotalColors)*offset);

			int length = s_offset - s_last_offset;

			for (int j = 0, i = s_last_offset; i < s_offset; i++, j++)
			{
				ColorSpread[i].red = last_red + j * ((double)(dest_red - last_red)/length);
				ColorSpread[i].green = last_green + j * ((double)(dest_green - last_green)/length);
				ColorSpread[i].blue = last_blue + j * ((double)(dest_blue - last_blue)/length);
				ColorSpread[i].alpha = last_alpha + j * ((double)(dest_alpha - last_alpha)/length);
			}

			last_red = dest_red;
			last_green = dest_green;
			last_blue = dest_blue;
			last_alpha = dest_alpha;
			s_last_offset = s_offset;
			last_offset = offset;
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

// Finish of to 100%
	for (int i = s_last_offset; i < TotalColors; i++)
	{
		ColorSpread[i].red = last_red;
		ColorSpread[i].green = last_green;
		ColorSpread[i].blue = last_blue;
		ColorSpread[i].alpha = last_alpha;
	}

	return ColorSpread;
}


void CSVGGradientEditCtl::PrepareRange()
{
   if (m_colorSpread)
	{
		GlobalFree(m_colorSpread);
		m_colorSpread = NULL;
	}

	if (m_gradient != NULL)
	{
		m_colorSpread = CreateGradient(m_gradient, m_totalColors);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSVGGradientEditCtl dialog


long CSVGGradientEditCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	return 0;
}

long CSVGGradientEditCtl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   if (m_colorSpread)
	{
		GlobalFree(m_colorSpread);
		m_colorSpread = NULL;
	}
	return 0;
}

long CSVGGradientEditCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_previewRect.left = 8;
	m_previewRect.top = 2;
	m_previewRect.right = max(40, client.right-8);
	m_previewRect.bottom = 40;

	m_totalColors = m_previewRect.Width();

	PrepareRange();

	InvalidateRect(NULL, TRUE);

	return 0;
}

void CSVGGradientEditCtl::NewColor(COLORREF newrgb)
{
	PrepareRange();
	InvalidatePreview();
	InvalidateGradient();
}

void CSVGGradientEditCtl::PaintGradient(HDC hDC)
{ 
	int	patx = 4;
	int	paty = 4;

	int	xc, yc;
	int	col, row;

	xc = 0;
	col = 0;

	int width = m_previewRect.Width();
	int height = m_previewRect.Height()-17-10;

	BITMAPINFO	bmi = {0};
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biPlanes = 1;
	int rowbytes = ROWBYTES(width, 24);

	LPBYTE bits = (LPBYTE)GlobalAlloc(0, rowbytes * height);

	for (int x = 0; x < width; x++)
	{
		int	index = x;

		if (m_colorSpread[index].alpha == 255)
		{
			for (int y = 0; y < height; y++)
			{
				RGBTRIPLE* rgbdest = (RGBTRIPLE*)(bits + rowbytes*(height-y-1) + x*3);

				rgbdest->rgbtRed = m_colorSpread[index].red;
				rgbdest->rgbtGreen = m_colorSpread[index].green;
				rgbdest->rgbtBlue = m_colorSpread[index].blue;
			}
		}
		else
		{
			yc = 0;
			row = 0;

			for (int y = 0; y < height; y++)
			{
				RGBTRIPLE* rgbdest = (RGBTRIPLE*)(bits + rowbytes*(height-y-1) + x*3);

				RGBTRIPLE	rgb;
				rgb.rgbtRed = m_colorSpread[index].red;
				rgb.rgbtGreen = m_colorSpread[index].green;
				rgb.rgbtBlue = m_colorSpread[index].blue;

				if ((col+row) & 1)
				{
					rgbdest->rgbtRed = 255;
					rgbdest->rgbtGreen = 255;
					rgbdest->rgbtBlue = 255;
				}
				else
				{
					rgbdest->rgbtRed = 200;
					rgbdest->rgbtGreen = 200;
					rgbdest->rgbtBlue = 200;
				}
		
				::SetMedianPixel(rgbdest, &rgb, 255-m_colorSpread[index].alpha);

				if (++yc == paty)
				{
					yc = 0;
					row++;
				}
			}
		}

		if (++xc == patx)
		{
			xc = 0;
			col++;
		}
	}

	SetDIBitsToDevice(hDC,
		m_previewRect.left, m_previewRect.top, width, height,
		0, 0,
		0, height,
		bits, &bmi,
		DIB_RGB_COLORS);

	GlobalFree(bits);
}

void DrawKnob(HDC hDC, int x, int y, ILSVGStopElement* knob, BOOL bSelected)
{
	HPEN	hOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);
	HBRUSH	hOldBrush = (HBRUSH)GetCurrentObject(hDC, OBJ_BRUSH);

	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	Rectangle(hDC, x-5, y+6, x+5+1, y+16+1);

	HPEN	whitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hDC, whitePen);
	MoveToEx(hDC, x-4, y+15, NULL);
	LineTo(hDC, x-4, y+7);
	LineTo(hDC, x+4, y+7);

	HPEN	grayPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	SelectObject(hDC, grayPen);
	LineTo(hDC, x+4, y+15);
	LineTo(hDC, x-5, y+15);

	HPEN	blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hDC, blackPen);

	if (bSelected)
	{
		POINT	pt[3] =
		{
			x-5, y+6,
			x, y,
			x+5, y+6
		};

		SelectObject(hDC, GetStockObject(BLACK_BRUSH));
		Polygon(hDC, pt, 3);
	}
	else
	{
		MoveToEx(hDC, x-5, y+6, NULL);
		LineTo(hDC, x, y);
		LineTo(hDC, x+5, y+6);
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(whitePen);
	DeleteObject(grayPen);
	DeleteObject(blackPen);
}

void CSVGGradientEditCtl::InvalidateKnob(ILSVGStopElement* stop)
{
	InvalidateRect(NULL, TRUE);
}

void CSVGGradientEditCtl::InvalidateGradient()
{
	InvalidateRect(&CRect(m_previewRect.left, m_previewRect.bottom-17-10,
		m_previewRect.right, m_previewRect.bottom-17), TRUE);
}

void CSVGGradientEditCtl::InvalidateKnobs()
{
	InvalidateRect(&CRect(m_previewRect.left-5, m_previewRect.bottom-17,
		m_previewRect.right+5, m_previewRect.bottom), TRUE);
}

void CSVGGradientEditCtl::InvalidatePreview()
{
	InvalidateRect(&CRect(m_previewRect.left, m_previewRect.top,
		m_previewRect.right, m_previewRect.bottom-17-10), TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CSVGGradientEditCtl message handlers

LRESULT CSVGGradientEditCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, FALSE);

	return 0;
}

LRESULT CSVGGradientEditCtl::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonUp(wParam, point, 0);

	return 0;
}

LRESULT CSVGGradientEditCtl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnMouseMove(wParam, point);

	return 0;
}

void CSVGGradientEditCtl::OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk) 
{
	if (point.x > m_previewRect.left-8 && point.y < m_previewRect.right+8 &&
		point.y > m_previewRect.top && point.y < m_previewRect.bottom)
	{
		if (m_canEditStops)
		{
			POINT pt = point;
			pt.x -= m_previewRect.left;

			CComQIPtr<ILSVGStopElement> onStop;// = NULL;

			CComQIPtr<ILSVGStopElement> stop;
			m_gradient->get_firstChild((ILDOMNode**)&stop);

			CComQIPtr<ILDOMNode> beforeNode = stop;

			while (stop != NULL)
			{
				double offset;
				CComQIPtr<ILSVGAnimatedNumber> aoffset;
				stop->get_offset(&aoffset);
				aoffset->get_baseVal(&offset);

				int x = (int)(offset*m_previewRect.Width());

				if (abs(pt.x-x) < 8)
				{
					onStop = stop;
				}

				CComQIPtr<ILDOMNode> nextSibling;
				stop->get_nextSibling(&nextSibling);
				stop = nextSibling;

				if (pt.x > x)
				{
					beforeNode = stop;
				}
			}

			if (iButton == 0)
			{
				if (onStop)	// Already used
				{
	#if 0	// Have this
					CElement* pElement = m_pElement->m_pDocument->m_pTree->FindDOMElement((IDOMNode*)onStop);
					m_pElement->m_pDocument->SetTargetElement(pElement, 0);
	#endif
					m_activeStop = onStop;	// hm instead of above (change this)
				}
				else
				{
					if (beforeNode == NULL)
					{
						m_gradient->get_firstChild(&beforeNode);
					}

					CUString str;

					float offset = (float)pt.x / m_previewRect.Width();

					CComQIPtr<ILDOMDocument> document;
					m_pElement->get_ownerDocument(&document);

					CComQIPtr<ILSVGStopElement> stop;
					document->createElementNS(L"http://www.w3.org/2000/svg", L"stop", (ILDOMElement**)&stop);

					CComQIPtr<ILSVGAnimatedNumber> aoffset;
					stop->get_offset(&aoffset);
					aoffset->put_baseVal(offset);

					CComQIPtr<ILSVGStylable> stylable = stop;

					CComQIPtr<ILCSSStyleDeclaration> style;
					stylable->get_style(&style);

					str.Format("#%2.2X%2.2X%2.2X", m_colorSpread[pt.x].red, m_colorSpread[pt.x].green, m_colorSpread[pt.x].blue);
					style->setProperty(L"stop-color", _bstr_t(str), L"");

					str.Format("%g", m_colorSpread[pt.x].alpha/255.0);
					style->setProperty(L"stop-opacity", _bstr_t(str), L"");

					m_gradient->insertBefore(stop, _variant_t(beforeNode), NULL);

	#if 0	// Have this
					CElement* pElement = m_pElement->m_pDocument->m_pTree->FindDOMElement((IDOMNode*)stop);
					m_pElement->m_pDocument->SetTargetElement(pElement, 0);
	#endif
					m_activeStop = stop;	// hm instead of above (change this)
				}

				if (m_activeStop != NULL)
				{
					SetCapture();
					m_dragging = TRUE;

				//	OnMouseMove(nFlags, point);
				}
			}
			else
			{
	#if 0
				if (onStop)
				{
					m_pElement->m_pDocument->ActivateElement((CElement*)m_pElement->m_parent, 0);
					onStop->parentNode->removeChild(onStop);
				}
	#endif
			}
		}
	}
}

void CSVGGradientEditCtl::OnMouseMove(UINT nFlags, POINT point) 
{
	if (m_dragging)
	{
		POINT pt = point;
		pt.x -= m_previewRect.left;

		float offset = (float)pt.x/m_previewRect.Width();

		if (offset < 0) offset = 0;
		else if (offset > 1) offset = 1;

	//	CUString str; str.Format("%g", offset);
	//	m_activeStop->setAttribute(L"offset", _bstr_t(str));
		CComPtr<ILSVGAnimatedNumber> aoffset;
		m_activeStop->get_offset(&aoffset);
		aoffset->put_baseVal(offset);

	// Sort the stops so they are in the right order

		/*
		CArray<ISVGStopElement*, ISVGStopElement*> stops;

		CComQIPtr<ISVGStopElement> stop;
		m_gradient->get_firstChild((IDOMNode**)&stop);
		while (stop != NULL)
		{
			stops.Add(stop);

			CComQIPtr<IDOMNode> nextSibling;
			stop->get_nextSibling(&nextSibling);
			stop = nextSibling;
		}

		int total = stops.GetSize();
		for (int i = 0; i < total; i++)
		{
			int min_index = i;

			for (int j = i+1; j < total; j++)
			{
				double offset_j = atof(stops[j]->getAttribute(L"offset"));
				double offset_min_index = atof(stops[min_index]->getAttribute(L"offset"));

				if (offset_j < offset_min_index)
				{
					min_index = j;
				}
			}

			if (i != min_index)
			{
				if (stops[min_index]->nextSibling == stops[i])
				{
					SVGLib::IDOMNodePtr before = stops[i]->nextSibling;
					if (before)
						m_gradient->insertBefore(stops[min_index], before);
					else
						m_gradient->appendChild(stops[min_index]);
				}
				else if (stops[i]->nextSibling == stops[min_index])
				{
					SVGLib::IDOMNodePtr before = stops[min_index]->nextSibling;
					if (before)
						m_gradient->insertBefore(stops[i], before);
					else
						m_gradient->appendChild(stops[i]);
				}
				else
				{
				}

				SVGLib::ISVGStopElement* temp = stops[i];
				stops[i] = stops[min_index];
				stops[min_index] = temp;
			}
		}
		*/

		//PrepareRange();// remove this (?)
		//Invalidate();	// remove this (?)

		UpdateWindow();
	}
}

void CSVGGradientEditCtl::OnButtonUp(UINT nFlags, POINT point, int iButton) 
{
	if (m_dragging)
	{
		m_dragging = FALSE;
		ReleaseCapture();

		if (m_activeStop)
		{
			Fire_EndDragStopElement(m_activeStop);
		}
	}
}

HRESULT CSVGGradientEditCtl::OnDraw(ATL_DRAWINFO& di)
{
	HDC hDC = di.hdcDraw;
	CDCHandle dc(hDC);

	CRect rcBounds = *(CRect*)di.prcBounds;

	dc.FillSolidRect(&rcBounds, m_clrBackColor);

	if (m_gradient != NULL)
	{
		/*	????
		FillRect(hDC, &CRect(m_previewRect.left, m_previewRect.bottom-17,
			m_previewRect.right, m_previewRect.bottom), (HBRUSH)GetStockObject(LTGRAY_BRUSH));
			*/

		if (m_canEditStops)
		{
			CComPtr<ILDOMNode> child;
			m_gradient->get_firstChild(&child);

			while (child != NULL)
			{
				CComQIPtr<ILSVGStopElement> stop = child;
				if (stop != NULL)
				{
					double offset;
					CComPtr<ILSVGAnimatedNumber> aoffset;
					stop->get_offset(&aoffset);
					aoffset->get_baseVal(&offset);

					int x = m_previewRect.left+(offset*m_previewRect.Width());
					int y = m_previewRect.bottom-17;
					DrawKnob(hDC, x, y, stop, (stop == m_activeStop));
				}

				CComPtr<ILDOMNode> nextSibling;
				child->get_nextSibling(&nextSibling);
				child = nextSibling;
			}
	/*
			if (m_activeStop)
			{
				SVGLib::ISVGStylablePtr stylableStop = m_activeStop;
				_bstr_t str_color = stylableStop->style->getPropertyValue(L"stop-color");
				COLORREF color = ConvertColor(str_color);
			}
	*/
		}

		PaintGradient(hDC);
	}

	return S_OK;
}

/*
void CSVGGradientEditCtl::handleEvent(SVGLib::IDOMEvent* evt)
{
	if (m_pElement)
	{
		PrepareRange();

		if (GetHwnd())
		{
			Invalidate();
		}
	}
}

BOOL CSVGGradientEditCtl::OnEraseBkgnd(HDC hDC) 
{
	if (m_pElement && m_gradient != NULL)
	{
		int state = SaveDC(hDC);

		ExcludeClipRect(hDC, m_previewRect.left, m_previewRect.top, m_previewRect.right, m_previewRect.bottom);

		SUB()->OnEraseBkgnd(hDC);

		RestoreDC(hDC, state);

		return TRUE;
	}
	else
		return SUB()->OnEraseBkgnd(hDC);
}
*/


STDMETHODIMP CSVGGradientEditCtl::SetSVGElement(IUnknown *element)
{
	if (m_pElement)
	{
		if (m_gradient)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = m_gradient;

		// Capture
			eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
		}
	}

	m_pElement = element;

	if (m_pElement)
	{
		CComQIPtr<ILSVGGradientElement> gradient = m_pElement;

		if (gradient != NULL)
		{
			m_activeStop.Release();// = NULL;
		}
		else
		{
			CComQIPtr<ILSVGStopElement> stop = m_pElement;
			if (stop != NULL)
			{
				CComPtr<ILDOMNode> parent;
				stop->get_parentNode(&parent);

				gradient = parent;
				m_activeStop = stop;
			}
		}

		if (m_gradient != gradient)
		{
			m_gradient = gradient;

			PrepareRange();
		}

		if (m_gradient != NULL)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = m_gradient;

		// Capture
			eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->addEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->addEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
		}
	}
	else
	{
		m_gradient.Release();// = NULL;
	}

	if (m_hWnd)
	{
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CSVGGradientEditCtl::get_canEditStops(VARIANT_BOOL *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_canEditStops;
	return S_OK;
}

STDMETHODIMP CSVGGradientEditCtl::put_canEditStops(VARIANT_BOOL newVal)
{
	if (m_canEditStops != newVal)
	{
		m_canEditStops = newVal;

		if (m_hWnd)
		{
			Invalidate();
		}
	}

	return S_OK;
}

// ILDOMEventListener
STDMETHODIMP CSVGGradientEditCtl::handleEvent(ILDOMEvent* evt)
{
	PrepareRange();

	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}

#endif