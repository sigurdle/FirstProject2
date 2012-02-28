#include "stdafx.h"
#include "LXUI2.h"
#include "ColorSlider.h"
#include "SolidColorBrush.h"
#include "Polyline.h"
#include "Canvas.h"

namespace System
{
namespace UI
{

	/*
void Draw3dRect(LDraw::Graphics* pGraphics, LDraw::BBoxi& rect, LDraw::Color clrTopLeft, LDraw::Color clrBottomRight);
void Draw3dRect(LDraw::Graphics* pGraphics, float x, float y, float width, float height, LDraw::Color clrTopLeft, LDraw::Color clrBottomRight);

void inline SetRGBTriple(RGBTRIPLE* triple, BYTE r, BYTE g, BYTE b)
{
	triple->rgbtRed = r;
	triple->rgbtGreen = g;
	triple->rgbtBlue = b;
}
*/

SliderKnob::SliderKnob()
{
	Shapes::Polyline* p = new Shapes::Polyline;
	PointCollection* points = new PointCollection;

	points->Add(Point(-5, 8));
	points->Add(Point(0, 0));
	points->Add(Point(5, 8));

	p->set_Fill(new SolidColorBrush(Color::FromRgb(255, 255, 255)));

	p->set_Points(points);

	set_VisualTree(p);
}

LDraw::SizeD SliderKnob::OnMeasure(LDraw::SizeD availSize)
{
	return LDraw::SizeD(10, 8);
}

void SliderKnob::OnArrange(LDraw::SizeD finalSize)
{
	m_expandedBBox.X = -5;
}

/////////////////////////////////////////////////////////////////////////////
// ColorSlider

ColorSlider::ColorSlider()
{
	m_dragging = 0;
	m_type = 3;
	m_channel = 0;
	m_colorMode = 2;	// RGB

	m_pos = 0;

	m_fromValue = Color::FromRgb(0,0,0);
	m_toValue = Color::FromRgb(255, 255, 255);
	m_bEnabled = true;

	EnsureVisual();
}

void ColorSlider::EnsureVisual()
{
	ASSERT(0);
#if 0

	DockPanel* panel = new DockPanel;
	{

		{
			Border* p = new Border(new Thickness(new Length(1.0), new Length(0.0), new Length(1.0), new Length(0.0)));
		//	p->m_LeftBrush = new SolidColorBrush(new Color(60, 60, 60));
		//	p->m_TopBrush = new SolidColorBrush(new Color(60, 60, 60));
		//	p->m_RightBrush = new SolidColorBrush(new Color(255, 255, 255));
		//	p->m_BottomBrush = new SolidColorBrush(new Color(255, 255, 255));

			{
				m_canvas = new Canvas;

				m_knob = new SliderKnob;
				Canvas::SetLeft(m_knob, new Length(m_pos* get_ActualSize().Width));
				m_canvas->AddRChild(m_knob);
				m_canvas->set_Height(new Length(8));

				p->set_Child(m_canvas);
			}
			DockPanel::SetDock(p, DockPanel::Bottom);
			panel->AddRChild(p);
		}

		{
			Border* p = new Border(new Thickness(new Length(1)));
			/*
			p->m_LeftBrush = new SolidColorBrush(Color(60, 60, 60));
			p->m_TopBrush = new SolidColorBrush(Color(60, 60, 60));
			p->m_RightBrush = new SolidColorBrush(Color(255, 255, 255));
			p->m_BottomBrush = new SolidColorBrush(Color(255, 255, 255));
			*/

			LinearGradientBrush* gradient = new LinearGradientBrush(m_fromValue, m_toValue, new Point(0, 0), new Point(1, 0));
			p->set_Background(gradient);

			DockPanel::SetDock(p, DockPanel::Fill);
			panel->AddRChild(p);
		}
	}

//	p->set_Content(panel);

	set_VisualTree(panel);
	InvalidateMeasure();
#endif
}

#if 0
void ColorSlider::handleEvent(Event* evt)
{
	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		StringW* type = evt->get_type();

		if (type == MouseEvent::mousedown)
		{
			evt->stopPropagation();
			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			OnLButtonDown(point);
		}
		else if (type == MouseEvent::mouseup)
		{
			evt->stopPropagation();
			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			OnLButtonUp();
		}
		else if (type == MouseEvent::mousemove)
		{
			evt->stopPropagation();
			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			OnMouseMove(point);
		}
	}
}
#endif

LDraw::SizeD ColorSlider::ArrangeOverride(LDraw::SizeD finalSize)
{
	m_knob->m_computedLeft = m_pos * m_computedSize.Width;
	return finalSize;
//	return Control::ArrangeOverride(finalSize);
}

/*
void ColorSlider::OnMeasure(LDraw::SizeD availSize)
{
	m_desiredSize.Height = 16;
}
*/

#if 0
//HRESULT ColorSlider::OnDraw(ATL_DRAWINFO& di)
void ColorSlider::OnRender2(LDraw::Graphics* pGraphics)
{
	ASSERT((m_type >= 0) && (m_type <= 3)); 

#if 0
//	BBoxi client = *(BBoxi*)di.prcBounds;
//	BBoxi	client = m_rcPos;

//	BBoxi client(m_RenderBounds.X, m_RenderBounds.Y, m_RenderBounds.X+m_RenderBounds.Width, m_RenderBounds.Y+m_RenderBounds.Height);
	BBoxi client(m_RenderBounds.X, m_RenderBounds.Y, m_RenderBounds.X+m_computedWidth, m_RenderBounds.Y+m_computedHeight);

	BBoxi sliderRect = client;
	sliderRect.left += 3;
	sliderRect.right -= 3;
	sliderRect.bottom -= 5;

	if (!m_bEnabled)
	{
//		dc.Draw3dRect(&sliderRect, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	}
	else
	{
		if (m_bEnabled == 1)
		{
	#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

			int bytesPerRow = ROWBYTES(sliderRect.Width(), 24);
			BITMAPINFOHEADER	bmi;
			ZeroMemory(&bmi, sizeof(bmi));
			bmi.biSize = sizeof(BITMAPINFOHEADER);
			bmi.biWidth = sliderRect.Width();
			bmi.biHeight = sliderRect.Height();
			bmi.biPlanes = 1;
			bmi.biBitCount = 24;
			bmi.biCompression = BI_RGB;
			bmi.biSizeImage = bytesPerRow*sliderRect.Height();

			LPBYTE bits = (LPBYTE)GlobalAlloc(0, bmi.biSizeImage);

			if (bits)
			{
				int from[4] = {GetRValue(m_fromValue), GetGValue(m_fromValue), GetBValue(m_fromValue)};
				int to[4] = {GetRValue(m_toValue), GetGValue(m_toValue), GetBValue(m_toValue)};

				for (int x = 0; x < sliderRect.Width(); x++)
				{
					RGBTRIPLE rgb;

					int value = (x*256)/sliderRect.Width();

					int v[4];

					for (int i = 0; i < 3; i++)
					{
						v[i] = from[i] + (to[i]-from[i])*value/255;
					}

					if (m_colorMode == 1)	// Grayscale
					{
						rgb.rgbtRed = value;
						rgb.rgbtGreen = value;
						rgb.rgbtBlue = value;
					}
					else if (m_colorMode == 2)	// RGB
					{
						rgb.rgbtRed = v[0];
						rgb.rgbtGreen = v[1];
						rgb.rgbtBlue = v[2];
					}
					else if (m_colorMode == 3)	// HSB
					{
						COLORREF clr = HLStoRGB(HLS(v[0], v[1], v[2]));
						rgb.rgbtRed = GetRValue(clr);
						rgb.rgbtGreen = GetGValue(clr);
						rgb.rgbtBlue = GetBValue(clr);
					}

					LPBYTE p = (bits + x*3);

					for (int y = 0; y < sliderRect.Height(); y++)
					{
						*(RGBTRIPLE*)p = rgb;
						p += bytesPerRow;
					}
				}

				/*
				if (TRUE)
				{
					DrawDibDraw(m_ddc, hDC,
						1, 1, width, height,
						&bmi, bits,
						0, 0, width, height,
						((m_type == 2)? DDF_SAME_HDC: 0) | DDF_BACKGROUNDPAL);
				}
				else
				*/
				{
#if 0
					dc.SetDIBitsToDevice(
						sliderRect.left, sliderRect.top, sliderRect.Width(), sliderRect.Height(),
						0, 0, 0, sliderRect.Height(),
						bits, (LPBITMAPINFO)&bmi,
						DIB_RGB_COLORS);
#endif
					Gdiplus::Bitmap bitmap((BITMAPINFO*)&bmi, bits);

					pGraphics->DrawImage(&bitmap, 0, 0);
				}

				GlobalFree(bits);
			}
		}

	//	HDC hdc = pGraphics->GetHDC();
	//	CDCHandle dc(hdc);

		Draw3dRect(pGraphics, sliderRect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DHILIGHT));
		sliderRect.InflateRect(-1,-1);

		Draw3dRect(pGraphics, sliderRect, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DDKSHADOW));
		sliderRect.InflateRect(-1,-1);

		if (m_pos >= 0 && m_pos <= 255)	// Defined
		{
			sliderRect.left -= 1;
			sliderRect.right += 1;

			int x = sliderRect.left + (double)(m_pos*(sliderRect.Width()-1))/(256) + 0.5;
			int y = sliderRect.bottom+1;

		//	ATLTRACE("draw: %d, %d\n", sliderRect.left, sliderRect.Width());

			POINT pts[3] =
			{
				x, y,
				x-4, y+4,
				x+4, y+4,
			};

			//dc.Polygon(pts, 3);
		}

		//pGraphics->ReleaseHDC(hdc);
	}
#endif
}
#endif

void ColorSlider::OnLButtonDown(LDraw::PointD point)
{
	if (m_bEnabled)
	{
		if (!m_dragging)
		{
			m_dragging = 1;
			ASSERT(0);
#if 0
			SetCapture();
#endif
			OnMouseMove(point);
		}
	}
}

void ColorSlider::OnLButtonUp()
{
	if (m_dragging)
	{
		m_dragging = 0;
		ASSERT(0);
#if 0
		ReleaseCapture();
#endif
	}
}

void ColorSlider::OnMouseMove(LDraw::PointD point)
{
	if (m_dragging)
	{
	//	BBoxi	client = m_rcPos;
		LDraw::BBoxi client(0, 0, m_computedSize.Width, m_computedSize.Height);

		LDraw::BBoxi sliderRect = client;
		sliderRect.left += 3+1;
		sliderRect.right -= 3+1;
		sliderRect.bottom -= 5;

		point.X -= sliderRect.left;//client.left;
		point.Y -= client.top;

	//	ATLTRACE("mousemove: x:%d,width:%d\n", point.x, sliderRect.Width());

		double pos;

		if (true)	// Horizontal
			pos = (point.X)/(sliderRect.GetWidth());
		else
			;

		if (pos < 0) pos = 0;
		else if (pos > 1) pos = 1;

		if (pos != m_pos)
		{
			m_pos = pos;

			/*
			if (m_channel < 3)
			{
				BYTE	red = GetRValue(m_rgb);
				BYTE	green = GetGValue(m_rgb);
				BYTE	blue = GetBValue(m_rgb);

				if (m_channel == 0)
					m_rgb = RGB(pos, green, blue);
				else if (m_channel == 1)
					m_rgb = RGB(red, pos, blue);
				else
					m_rgb = RGB(red, green, pos);
			}
			*/
		/*
			else if (m_slide < 6)
			{
				COLORREF	hls = RGBtoHLS(m_rgb);
				BYTE	hue = GetHValue(hls);
				BYTE	lum = GetLValue(hls);
				BYTE	sat = GetSValue(hls);

				if (m_slide == 3)
					m_rgb = HLStoRGB(HLS(pos, lum, sat));
				else if (m_slide == 4)
					m_rgb = HLStoRGB(HLS(hue, pos, sat));
				else
					m_rgb = HLStoRGB(HLS(hue, lum, pos));
			}
			*/
			/*
			else	// Grayscale
			{
			//	m_rgb = RGB(pos, pos, pos);
			}
			*/

#if 0
			SliderEvent* evt = new SliderEvent;
			evt->InitEvent(WSTR("ValueChange"), true, true);
			evt->m_pos = pos;

			dispatchEvent(evt);
			set_pos(pos);
			;//Fire_SetPos(m_pos);
			InvalidateRender();//Rect(m_hWndParent, NULL, TRUE);

			delete evt;
#endif
		}
	}
}

long ColorSlider::get_channel()
{
	return m_channel;
}

void ColorSlider::set_channel(long newVal)
{
	m_channel = newVal;
	Invalidate();
}

LDraw::Color ColorSlider::get_rgb()
{
	if (m_channel == 0)
	{
		return LDraw::Color(m_pos*255, m_fromValue.get_G(), m_fromValue.get_B());
	}
	else if (m_channel == 1)
	{
		return LDraw::Color(m_fromValue.get_R(), m_pos*255, m_fromValue.get_B());
	}
	else if (m_channel == 2)
	{
		return LDraw::Color(m_fromValue.get_R(), m_fromValue.get_G(), m_pos*255);
	}
	else
		THROW(-1);
	/*
	else if (m_channel == 3)
	{
		*pVal = RGB(m_pos, GetGValue(m_fromVal), GetBValue(m_fromVal));
	}
	*/

//	*pVal = m_rgb;
}

void ColorSlider::set_rgb(uint32 newVal)
{
	/*
	if (m_channel == 0)
	{
		m_fromValue = RGB(0, GetGValue(newVal), GetBValue(newVal));
		m_toValue = RGB(255, GetGValue(newVal), GetBValue(newVal));
		m_pos = GetRValue(newVal);
	}
	else if (m_channel == 1)
	{
		m_fromValue = RGB(GetRValue(newVal), 0, GetBValue(newVal));
		m_toValue = RGB(GetRValue(newVal), 255, GetBValue(newVal));
		m_pos = GetGValue(newVal);
	}
	else if (m_channel == 2)
	{
		m_fromValue = RGB(GetRValue(newVal), GetGValue(newVal), 0);
		m_toValue = RGB(GetRValue(newVal), GetGValue(newVal), 255);
		m_pos = GetBValue(newVal);
	}
	else if (m_channel == 3)
	{
		m_fromValue = CMYK(GetCValue(newVal), GetMValue(newVal), GetYValue(newVal), 0);
		m_toValue = CMYK(GetCValue(newVal), GetMValue(newVal), GetYValue(newVal), 255);
	}
	*/

	Invalidate();
}

long ColorSlider::get_colorMode()
{
	return m_colorMode;
}

void ColorSlider::set_colorMode(long newVal)
{
	if (m_colorMode != newVal)
	{
		m_colorMode = newVal;

		Invalidate();
	}
}

Color ColorSlider::get_fromValue()
{
	return m_fromValue;
}

void ColorSlider::set_fromValue(Color newVal)
{
	m_fromValue = newVal;
	EnsureVisual();
	Invalidate();//Measure();
	ASSERT(0);
#if 0
	get_VisualTree()->InvalidateRender();//Measure();
#endif
}

Color ColorSlider::get_toValue()
{
	return m_toValue;
}

void ColorSlider::set_toValue(Color newVal)
{
	m_toValue = newVal;
	EnsureVisual();
	Invalidate();//Measure();
	ASSERT(0);
#if 0
	get_VisualTree()->InvalidateRender();//Measure();
#endif
}

double ColorSlider::get_pos()
{
	return m_pos;
}

void ColorSlider::set_pos(double newVal)
{
	m_pos = newVal;
	Canvas::SetLeft(m_knob, m_pos* get_ActualSize().Width);
	m_canvas->InvalidateArrange();
	Invalidate();
}

}	// UI
}
