// SwatchesList.cpp : Implementation of CSwatchesList

#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "SwatchesList.h"

void CreateGradient(CArray<Gdiplus::REAL, Gdiplus::REAL>& offsets, CArray<Gdiplus::Color,Gdiplus::Color&>& colors, IPDGradient* gradient);

/////////////////////////////////////////////////////////////////////////////
// CSwatchesList

extern TCHAR monitorProfile[];
extern TCHAR printerProfile[];
extern TCHAR targetProfile[];

HRESULT CSwatchesList::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	HDC hDC = di.hdcDraw;

	if (m_swatches)
	{
		Draw3DRect(hDC, m_areaRect.left-1, m_areaRect.top-1, m_areaRect.Width()+2, m_areaRect.Height()+2, RGB(0,0,0), RGB(0,0,0));

		long scrollposY; m_vert->get_pos(&scrollposY);

		if (IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
		{
			POINT oldOrg;
			SetViewportOrgEx(hDC, m_areaRect.left, m_areaRect.top - scrollposY, &oldOrg);
		// For CMYK conversion
			/*
			TCHAR colorDirectory[MAX_PATH];
			DWORD cbSize = sizeof(colorDirectory);
			GetColorDirectory(NULL, colorDirectory, &cbSize);

			HPROFILE hDestProfile = NULL;
			{
				TCHAR profilePath[MAX_PATH];
				_makepath(profilePath, NULL, colorDirectory, "sRGB Color Space Profile.ICM", NULL);

				PROFILE profile = {0};
				profile.dwType = PROFILE_FILENAME;
				profile.pProfileData = profilePath;
				profile.cbDataSize = (_tcslen(profilePath)+1)*sizeof(TCHAR);
				hDestProfile = OpenColorProfile(&profile, PROFILE_READ, FILE_SHARE_READ, OPEN_EXISTING);
				ATLASSERT(hDestProfile);
			}

			HPROFILE hTargetProfile = NULL;
			{
				TCHAR profilePath[MAX_PATH];
				_makepath(profilePath, NULL, colorDirectory, targetProfile, NULL);

				PROFILE profile = {0};
				profile.dwType = PROFILE_FILENAME;
				profile.pProfileData = profilePath;
				profile.cbDataSize = (_tcslen(profilePath)+1)*sizeof(TCHAR);
				hTargetProfile = OpenColorProfile(&profile, PROFILE_READ, FILE_SHARE_READ, OPEN_EXISTING);
				ATLASSERT(hTargetProfile);
			}

			LOGCOLORSPACE lcp = {0};
			lcp.lcsSignature = LCS_SIGNATURE;
			lcp.lcsVersion = 0x400;
			lcp.lcsSize = sizeof(lcp);
			lcp.lcsCSType = LCS_sRGB;
			lcp.lcsFilename;// = NULL; // ??

			HTRANSFORM hTransform = CreateColorTransform(&lcp, hDestProfile, hTargetProfile, BEST_MODE);
			ATLASSERT(hTransform);
			*/

		// Pattern for drawing ColorType symbols
			WORD bmdata[8] =
			{
				0xaaaa,
				0x5555,
				0xaaaa,
				0x5555,
				0xaaaa,
				0x5555,
				0xaaaa,
				0x5555,
			};

			HBITMAP hPatBitmap = CreateBitmap(8, 8, 1, 1, bmdata);
			ATLASSERT(hPatBitmap);

			HBRUSH hPatBrush = CreatePatternBrush(hPatBitmap);
			ATLASSERT(hPatBrush);
			DeleteObject(hPatBitmap);

		//
			HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

			LOGFONT lf;
			GetObject(hFont, sizeof(lf), &lf);
			lf.lfWeight = FW_BOLD;

			HFONT hFontSelected = CreateFontIndirect(&lf);
			HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

			long nswatches;
			m_swatches->get_length(&nswatches);

			int y = 0;

			for (int i = 0; i < nswatches; i++)
			{
				CComPtr<IPDSwatch> swatch;
				m_swatches->item(i, &swatch);

				//Rectangle(hDC, itemrect.left, itemrect.top, itemrect.right+1, itemrect.bottom+1);
				MoveToEx(hDC, 0, y+m_itemHeight, NULL);
				LineTo(hDC, m_areaRect.Width()+1, y+m_itemHeight);

				CRect itemrect(0, y+1, m_areaRect.Width(), y+m_itemHeight-1);
	//			itemrect.top += 1;
	//			itemrect.bottom -= 1;

				bool bSelected = IsSwatchSelected(swatch);

				if (bSelected)
					FillSolidRect(hDC, itemrect.left, itemrect.top+1, itemrect.Width(), itemrect.Height()-1, (bSelected)? GetSysColor(COLOR_HIGHLIGHT): GetSysColor(COLOR_WINDOW));

				int swatchSize = m_itemHeight-4;
				int swatchTop = (m_itemHeight-swatchSize)/2;
		//		CRect swatchRect(itemrect.left + 4, itemrect.top+itemrect.Height()/2-8, itemrect.left + 4 + 16, itemrect.top+itemrect.Height()/2-8+16);
				CRect swatchRect(itemrect.left + 4, itemrect.top+swatchTop, itemrect.left + 4 + swatchSize, itemrect.top+swatchTop+swatchSize);

				if (bSelected)
				{
					SelectObject(hDC, hFontSelected);
					SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
				}
				else
				{
					SelectObject(hDC, hFont);
					SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
				}

				SetBkMode(hDC, TRANSPARENT);

				BSTR bname;
				swatch->get_name(&bname);
				_bstr_t name = _bstr_t(bname, false);

				PDSwatchType swatchType;
				swatch->get_swatchType(&swatchType);

				CRect trect = itemrect;
				trect.left = swatchRect.right + 4;
				trect.right -= 30;

				if (swatchType == SWATCH_NONE)
				{
					FillSolidRect(hDC, &swatchRect, RGB(255, 255, 255));

					HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
					HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

					MoveToEx(hDC, swatchRect.left+1, swatchRect.bottom-1, NULL);
					LineTo(hDC, swatchRect.right-1, swatchRect.top+1);

					SelectObject(hDC, hOldPen);
					DeleteObject(hPen);

					HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
					Rectangle(hDC, swatchRect.left, swatchRect.top, swatchRect.right, swatchRect.bottom);
					SelectObject(hDC, hOldBrush);
				}
				else if (swatchType == SWATCH_COLOR ||
							swatchType == SWATCH_TINT)
				{
					CComPtr<IPDColor> color;
					CComQIPtr<IPDSwatchColor> swatchColor;

					if (swatchType == SWATCH_COLOR)
					{
						swatchColor = swatch;
						swatchColor->get_color(&color);
					}
					else
					{
						CComQIPtr<IPDSwatchTint> swatchTint = swatch;
						swatchTint->get_swatchColor(&swatchColor);

						swatchTint->get_finalColor(&color);

						CRect trect2 = trect;
						trect.right -= 28;
						trect2.left = trect.right;

						double tint;
						swatchTint->get_tint(&tint);

						CUString str;
						str.Format("%d %%", (int)(tint*100));

						DrawText(hDC, str, str.GetLength(), &trect2, DT_SINGLELINE | DT_VCENTER);
					}

					PDColorMode colorMode;
					color->get_colorMode(&colorMode);

					COLORREF clr;

					if (colorMode == COLORMODE_RGB)
					{
						double red; color->getChannel(0, &red);
						double green; color->getChannel(1, &green);
						double blue; color->getChannel(2, &blue);

						clr = RGB(red, green, blue);
					}
					else if (colorMode == COLORMODE_CMYK)
					{
	/*					if (hTransform)
						{
							double cyan; color->getChannel(0, &cyan);
							double magenta; color->getChannel(1, &magenta);
							double yellow; color->getChannel(2, &yellow);
							double black; color->getChannel(3, &black);

							COLOR incolor;
							incolor.cmyk.cyan = cyan*65535/255;
							incolor.cmyk.magenta = magenta*65535/255;
							incolor.cmyk.yellow = yellow*65535/255;
							incolor.cmyk.black = black*65535/255;

							COLOR outcolor;
							BOOL bSuccess = TranslateColors(hTransform, &incolor, 1, COLOR_CMYK, &outcolor, COLOR_RGB);
							ATLASSERT(bSuccess);

							clr = RGB(
								outcolor.rgb.red*255.0/65535,
								outcolor.rgb.green*255.0/65535,
								outcolor.rgb.blue*255.0/65535);
						}
						else
						*/
							clr = -1;
					}

					if (clr != -1)
					{
						HBRUSH hBrush = CreateSolidBrush(clr);
						HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

						Rectangle(hDC, swatchRect.left, swatchRect.top, swatchRect.right, swatchRect.bottom);

						SelectObject(hDC, hOldBrush);
						DeleteObject(hBrush);
					}

					{
						CRect rc(itemrect.right-15, itemrect.top+4, itemrect.right-15+10, itemrect.top+4+10);

						if (colorMode == COLORMODE_RGB)
						{
							Rectangle(hDC, rc.left, rc.top-1, rc.right+1, rc.bottom+1);

							FillSolidRect(hDC, rc.left+1, rc.top, 3, rc.Height(), RGB(255, 0, 0));
							FillSolidRect(hDC, rc.left+4, rc.top, 3, rc.Height(), RGB(0, 255, 0));
							FillSolidRect(hDC, rc.left+7, rc.top, 3, rc.Height(), RGB(0, 0, 255));
						}
						else if (colorMode == COLORMODE_CMYK)
						{
							//
							{
								HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
								HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

								POINT pts[3] =
								{
									rc.left, rc.top,
									rc.left+rc.Width(), rc.top,
									rc.left+rc.Width()/2, rc.top+rc.Height()/2,
								};

								Polygon(hDC, pts, 3);

								SelectObject(hDC, hOldBrush);
								DeleteObject(hBrush);
							}

							//
							{
								HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
								HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

								POINT pts[3] =
								{
									rc.right, rc.top,
									rc.right, rc.top+rc.Height(),
									rc.right-rc.Width()/2, rc.top+rc.Height()/2,
								};

								Polygon(hDC, pts, 3);

								SelectObject(hDC, hOldBrush);
								DeleteObject(hBrush);
							}

							//
							{
								HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
								HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

								POINT pts[3] =
								{
									rc.left, rc.bottom,
									rc.left+rc.Width(), rc.bottom,
									rc.left+rc.Width()/2, rc.bottom-rc.Height()/2,
								};

								Polygon(hDC, pts, 3);

								SelectObject(hDC, hOldBrush);
								DeleteObject(hBrush);
							}

							//
							{
								HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
								HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

								POINT pts[3] =
								{
									rc.left, rc.top,
									rc.left, rc.top+rc.Height(),
									rc.left+rc.Width()/2, rc.top+rc.Height()/2,
								};

								Polygon(hDC, pts, 3);

								SelectObject(hDC, hOldBrush);
								DeleteObject(hBrush);
							}
						}
					}

					{
						CRect rc(m_areaRect.right-28, y+4, m_areaRect.right-28+10, y+4+10);

						PDColorType colorType;
						swatchColor->get_colorType(&colorType);

						int oldBkMode = SetBkMode(hDC, OPAQUE);
						COLORREF oldTextClr = SetTextColor(hDC, RGB(100,100,100));
						COLORREF oldBkClr = SetBkColor(hDC, RGB(255,255,255));

						if (colorType == COLORTYPE_PROCESS)
						{
							HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hPatBrush);
							Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
							SelectObject(hDC, hOldBrush);
						}
						else if (colorType == COLORTYPE_SPOT)
						{
							Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);

							HPEN hPen = CreatePen(PS_SOLID, 1, RGB(120, 120, 120));
							HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hPatBrush);
							HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

							Ellipse(hDC, rc.left+2, rc.top+2, rc.right-2, rc.bottom-2);

							SelectObject(hDC, hOldBrush);
							SelectObject(hDC, hOldPen);
							DeleteObject(hPen);
						}
						else
							ATLASSERT(0);

						SetBkMode(hDC, oldBkMode);
						SetTextColor(hDC, oldTextClr);
						SetBkColor(hDC, oldBkClr);
					}
				}
				else if (swatchType == SWATCH_GRADIENT)
				{
					Gdiplus::Graphics graphics(hDC);

					CComQIPtr<IPDSwatchGradient> swatchGradient = swatch;

					CComPtr<IPDGradient> gradient;
					swatchGradient->get_gradient(&gradient);

					PDGradientType gradientType;
					gradient->get_type(&gradientType);

					Gdiplus::Rect rc(swatchRect.left, swatchRect.top, swatchRect.Width(), swatchRect.Height());

					CArray<Gdiplus::REAL, Gdiplus::REAL> offsets;
					CArray<Gdiplus::Color,Gdiplus::Color&> colors;

					CreateGradient(offsets, colors, gradient);

					if (gradientType == GRADIENT_LINEAR)
					{
						Gdiplus::LinearGradientBrush brush(rc, Gdiplus::Color(0,0,0), Gdiplus::Color(0,0,0), Gdiplus::LinearGradientModeHorizontal);
						brush.SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());

						graphics.FillRectangle(&brush, rc);
					}
					else if (gradientType == GRADIENT_RADIAL)
					{
						Gdiplus::GraphicsPath path;
						path.AddEllipse(rc);

						Gdiplus::PathGradientBrush brush(&path);
						brush.SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());

						graphics.FillRectangle(&brush, rc);
					}
					else
						ATLASSERT(0);
				}
				else if (swatchType == SWATCH_PATTERN)
				{
					Gdiplus::Graphics graphics(hDC);

					CComQIPtr<IPDSwatchPattern> swatchPattern = swatch;

					CComPtr<IPDObjectGroup> objectGroup;
					swatchPattern->get_objectGroup(&objectGroup);

					RectD bbox;
					objectGroup->getExpandedBBox(&bbox);

					int width = swatchRect.Width();
					int height = (bbox.Height * width/bbox.Width);//+0.5;

					if (height > swatchRect.Height())
					{
						height = swatchRect.Height();
						width = (bbox.Width * height/bbox.Height);//+0.5;
					}
					ATLASSERT(width <= bbox.Width);

					double magnify = width/bbox.Width;

					int left = (swatchRect.Width()-width)/2;
					int top = (swatchRect.Height()-height)/2;

					CComPtr<IPDRenderer> renderer;
					renderer.CoCreateInstance(CLSID_PDRenderer);
					if (renderer)
					{
						Gdiplus::Bitmap bitmap(width, height);
						{
							Gdiplus::Graphics bmgraphics(&bitmap);
							bmgraphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255)), 0, 0, width, height);

						//	Gdiplus::Graphics& bmgraphics = graphics;

						//	CComQIPtr<IPDObjectTransformable> transformable = objectGroup;
						//	RectD bounds;
						//	transformable->get_bounds(&bounds);

						//	bmgraphics.TranslateTransform(swatchRect.left+left, swatchRect.top+top);

							bmgraphics.ScaleTransform(magnify, magnify);
							bmgraphics.TranslateTransform(-bbox.X, -bbox.Y);
						//	bmgraphics.TranslateTransform(-bounds.X, -bounds.Y);

							renderer->put_magnify(magnify);
							renderer->put_targetHDC((HDC)&bmgraphics);

							renderer->RenderObject(objectGroup);
						}

						graphics.DrawImage(&bitmap, swatchRect.left+left, swatchRect.top+top);
					}
				}

				DrawText(hDC, name, name.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

				y += m_itemHeight;
			}

			SelectObject(hDC, hOldFont);

			DeleteObject(hFontSelected);
			DeleteObject(hPatBrush);
	/*
			if (hTransform) DeleteColorTransform(hTransform);
			if (hDestProfile) CloseColorProfile(hDestProfile);
			*/

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}
	}

	return S_OK;
}

LRESULT CSwatchesList::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CSwatchesList, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	return 0;
}

LRESULT CSwatchesList::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CSwatchesList, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CSwatchesList::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(&m_areaRect);

	return 0;
}

void CSwatchesList::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.InflateRect(-1, -1);

	long nswatches;

	if (m_swatches)
		m_swatches->get_length(&nswatches);
	else
		nswatches = 0;

	int height = nswatches*m_itemHeight;

	if (height > m_areaRect.Height())
	{
		m_areaRect.right -= 16;

		m_axvert.MoveWindow(m_areaRect.right, 0, 16, m_areaRect.bottom);
		m_vert->SetInfo(0, height, m_areaRect.Height());
	}
	else
	{
		m_axvert.MoveWindow(0, 0, 0, 0);
		m_vert->SetInfo(0, 0, m_areaRect.Height());
	}
}

LRESULT CSwatchesList::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposY; m_vert->get_pos(&scrollposY);

	CPoint pt = point;
	pt.y += scrollposY;

	if (m_swatches)
	{
		long nswatches;
		m_swatches->get_length(&nswatches);

		int swatchIndex = pt.y / m_itemHeight;

		if (swatchIndex >= 0 && swatchIndex < nswatches)
		{
			CComPtr<IPDSwatch> swatch;
			m_swatches->item(swatchIndex, &swatch);

			BOOL bSelected = IsSwatchSelected(swatch);

			if (!m_multiSelect)
			{
				if (!bSelected)
				{
					DeselectAll();

					SelectSwatch(swatch);
					m_selectedSwatchIndex = swatchIndex;

					Fire_ClickSwatch(swatch);
				}
			}
			else
			{
				if (nFlags & MK_CONTROL)	// Toggle selected
				{
					if (bSelected)
					{
						DeselectSwatch(swatch);
					}
					else
					{
						SelectSwatch(swatch);
						if (m_selectedSwatchIndex == -1) m_selectedSwatchIndex = swatchIndex;

						Fire_ClickSwatch(swatch);
					}
				}
				else
				{
					long startSel, endSel;

					if (!(nFlags & MK_SHIFT) || (m_selectedSwatchIndex == -1))
					{
						startSel = endSel = swatchIndex;
					}
					else if (swatchIndex > m_selectedSwatchIndex)
					{
						startSel = m_selectedSwatchIndex;
						endSel = swatchIndex;
					}
					else
					{
						startSel = swatchIndex;
						endSel = m_selectedSwatchIndex;
					}

					DeselectAll();

					for (long i = startSel; i <= endSel; i++)
					{
						CComPtr<IPDSwatch> swatch;
						m_swatches->item(i, &swatch);

						SelectSwatch(swatch);
					}

					if (!(nFlags & MK_SHIFT) || (m_selectedSwatchIndex == -1))
						m_selectedSwatchIndex = swatchIndex;

					Fire_ClickSwatch(swatch);
				}
			}

			InvalidateRect(&m_areaRect);
		}
	}

	return 0;
}

STDMETHODIMP CSwatchesList::get_swatches(IPDSwatches **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_swatches;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CSwatchesList::put_swatches(IPDSwatches *newVal)
{
	DeselectAll();

	if (m_swatches)
	{
		CComQIPtr<INotifySend> cp = m_swatches;
		cp->Unadvise(this);
	}

	m_swatches = newVal;

	if (m_swatches)
	{
		CComQIPtr<INotifySend> cp = m_swatches;
		DWORD cookie;
		cp->Advise(this, &cookie);
	}

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(&m_areaRect);
	}

	return S_OK;
}

STDMETHODIMP CSwatchesList::selectSwatch(IPDSwatch *swatch)
{
	DeselectAll();

	if (swatch)
	{
		SelectSwatch(swatch);
	}

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}

HRESULT __stdcall CSwatchesList::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &m_areaRect, &m_areaRect);

	return S_OK;
}

STDMETHODIMP CSwatchesList::getNextSelectedSwatch(long index, IPDSwatch **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (index < m_selectedSwatches.GetSize())
	{
		*pVal = m_selectedSwatches[index];
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CSwatchesList::get_multiSelect(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_multiSelect;
	return S_OK;
}

STDMETHODIMP CSwatchesList::put_multiSelect(VARIANT_BOOL newVal)
{
	m_multiSelect = newVal;
	return S_OK;
}

STDMETHODIMP CSwatchesList::get_showSwatchNone(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSwatchesList::put_showSwatchNone(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSwatchesList::get_showSwatchColor(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSwatchesList::put_showSwatchColor(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSwatchesList::get_showSwatchGradient(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSwatchesList::put_showSwatchGradient(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
