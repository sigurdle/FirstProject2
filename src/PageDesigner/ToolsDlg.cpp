// ToolsDlg.cpp : Implementation of CToolsDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "ToolsDlg.h"

// TODO: remove this
#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"
extern CPageDesignerApp* gApp;

/////////////////////////////////////////////////////////////////////////////
// CToolsDlg

STDMETHODIMP CToolsDlg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IToolsDlg
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

LRESULT CToolsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	CComObject<CUIMenuDlg>::CreateInstance(&m_menuDlg);//.CoCreateInstance(CLSID_UIMenuDlg);
	m_menuDlg->AddRef();

	CComPtr<IMenuItem> menu;
	uiManager->FindMenu(IDR_TOOLS, &menu);

	CComPtr<IMenuItem> menu0;
	menu->GetSubMenu(0, &menu0);

	CComQIPtr<ICommandTarget> targetFrame = gIFrame;
	m_menuDlg->CreateForMenuItem(menu0, m_hWnd, targetFrame, -1);

	menu.Detach();	// ?? Doesn't CreateForMenuItem AddRef()?

	return 0;
}

LRESULT CToolsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	if (m_menuDlg)
	{
		m_menuDlg->DestroyWindow();
		m_menuDlg->Release();
		m_menuDlg = NULL;
	}

	return 0;
}

LRESULT CToolsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	HWND hwnddlg;
	CComQIPtr<IUIDlg> dlg = m_menuDlg;
	dlg->get_hwnd(&hwnddlg);

	::MoveWindow(hwnddlg, 0, 0, client.right, client.bottom-64, TRUE);

	double nwidth = (client.Width()-2)/3.0;

	m_brushTypeRect[0].SetRect(1, client.bottom-16, 1+nwidth, client.bottom-1);
	m_brushTypeRect[1].SetRect(1+nwidth, client.bottom-16, 1+nwidth+nwidth, client.bottom-1);
	m_brushTypeRect[2].SetRect(1+nwidth+nwidth, client.bottom-16, 1+nwidth+nwidth+nwidth, client.bottom-1);

	return 0;
}

//extern Gdiplus::Brush* GetGdiBrush(IPDBrush* brush, PDBrushType brushType = BRUSH_NONE);

#include "PDObjectGroup.h"

void CreateGradient(CArray<Gdiplus::REAL, Gdiplus::REAL>& offsets, CArray<Gdiplus::Color,Gdiplus::Color&>& colors, IPDGradient* gradient);

Gdiplus::Brush* GetGdiBrush2(IPDBrush* brush)
{
	Gdiplus::Brush* pBrush = NULL;

	PDBrushType brushType;
	brush->get_brushType(&brushType);

	if (brushType == (PDBrushType)tomUndefined)
	{
	}
	else if (brushType == BRUSH_COLOR)
	{
		CComPtr<IPDColor> color;
		brush->get_color(&color);

		double v;

		color->getChannel(0, &v);
		if (v == tomUndefined) return NULL;

		color->getChannel(1, &v);
		if (v == tomUndefined) return NULL;

		color->getChannel(2, &v);
		if (v == tomUndefined) return NULL;

		CComPtr<IPDColor> tintedcolor;
		brush->get_tintedRGBColor(&tintedcolor);
		if (tintedcolor)
		{
			double red; tintedcolor->getChannel(0, &red);
			double green; tintedcolor->getChannel(1, &green);
			double blue; tintedcolor->getChannel(2, &blue);

			pBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, red, green, blue));
		}
	}
	else if (brushType == BRUSH_GRADIENT)
	{
		CComPtr<IPDGradient> gradient;
		brush->get_gradient(&gradient);

		if (gradient)
		{
			PDGradientType gradientType;
			gradient->get_type(&gradientType);

			double x1; brush->get_x1(&x1);
			double y1; brush->get_y1(&y1);
			double x2; brush->get_x2(&x2);
			double y2; brush->get_y2(&y2);

			CArray<Gdiplus::REAL, Gdiplus::REAL> offsets;
			CArray<Gdiplus::Color,Gdiplus::Color&> colors;

			CreateGradient(offsets, colors, gradient);

			if (gradientType == GRADIENT_LINEAR)
			{
				Gdiplus::LinearGradientBrush* pGradBrush = new Gdiplus::LinearGradientBrush(
						Gdiplus::Point(x1, y1),
						Gdiplus::Point(x2, y2),
						Gdiplus::Color(0,0,0,0), Gdiplus::Color(0,0,0,0));
				pGradBrush->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());

				pBrush = pGradBrush;
			}
			else if (gradientType == GRADIENT_RADIAL)
			{
				double dx = x2-x1;
				double dy = y2-y1;
				double radius = sqrt(dx*dx+dy*dy);

				Gdiplus::GraphicsPath path;
				path.AddEllipse((float)(x1-radius), (float)(y1-radius), (float)(x1+radius), (float)(y1+radius));

				Gdiplus::PathGradientBrush* pGradBrush = new Gdiplus::PathGradientBrush(&path);
				pGradBrush->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());

				pBrush = pGradBrush;
			}
			else
				ATLASSERT(0);
		}
	}
	else if (brushType == BRUSH_PATTERN)
	{
		CComPtr<IPDSwatch> swatch;
		brush->get_swatch(&swatch);

		CComQIPtr<IPDSwatchPattern> swatchPattern = swatch;

		CComPtr<IPDObjectGroup> objectGroup;
		swatchPattern->get_objectGroup(&objectGroup);

		if (objectGroup)
		{
			CPDObjectGroup* pGroup = static_cast<CPDObjectGroup*>(objectGroup.p);

			RectD bounds;
			pGroup->get_bounds(&bounds);

			Gdiplus::Bitmap bitmap(bounds.Width, bounds.Height);
			{
				Gdiplus::Graphics graphics(&bitmap);
				//graphics.ScaleTransform(swatchRect.Width()/bounds.Width, swatchRect.Height()/bounds.Height);
				graphics.TranslateTransform(-bounds.X, -bounds.Y);

				pGroup->Render(NULL, &graphics, 1, 1/*TODO*/);
			}

			Gdiplus::TextureBrush* pTexBrush = new Gdiplus::TextureBrush(&bitmap);

			pBrush = pTexBrush;
		}
	}

	return pBrush;
}

void DrawBrush(Gdiplus::Graphics* pGraphics, Gdiplus::Rect& rc, Gdiplus::GraphicsPath& path, IPDBrush* brush)
{
	ATLASSERT(brush);

	PDBrushType brushType;
	brush->get_brushType(&brushType);

	if (brushType == BRUSH_NONE)
	{
		pGraphics->FillPath(&Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255)), &path);

		Gdiplus::Pen redpen(Gdiplus::Color(255, 0, 0), 2);
		pGraphics->DrawLine(&redpen, rc.GetLeft()+0, rc.GetBottom()-1, rc.GetRight()-2, rc.GetTop()+0);
	}
	else
	{
		Gdiplus::Brush* pBrush = GetGdiBrush2(brush);

		if (pBrush)
		{
			pGraphics->FillPath(pBrush, &path);
			delete pBrush;
		}
		else
		{
			Gdiplus::Font font(L"Arial", 12);
			pGraphics->DrawString(L"?", 1, &font, Gdiplus::PointF(rc.X, rc.Y), &Gdiplus::SolidBrush(Gdiplus::Color(0,0,0)));
		}
	}
}

void DrawBrush(Gdiplus::Graphics* pGraphics, Gdiplus::Rect& rc, IPDBrush* brush, int bFill)
{
	Gdiplus::GraphicsPath path;
	if (bFill)
	{
		path.AddRectangle(rc);
	}
	else
	{
		Gdiplus::Rect innerrc(rc.X+4, rc.Y+4, rc.Width-8-1, rc.Height-8-1);

		Gdiplus::Pen blackpen(Gdiplus::Color(0,0,0));
		pGraphics->DrawRectangle(&blackpen, innerrc);

	//	innerrc.X--;
	//	innerrc.Y--;
		innerrc.Width++;
		innerrc.Height++;

		path.AddRectangle(rc);
		path.AddRectangle(innerrc);
	}

	DrawBrush(pGraphics, rc, path, brush);
}

void DrawBrushWithOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Rect& rc, IPDBrush* brush, int bFill)
{
	Gdiplus::Pen blackpen(Gdiplus::Color(0,0,0));

	Gdiplus::Rect rc2 = rc;
	rc2.Width--;
	rc2.Height--;

	pGraphics->DrawRectangle(&blackpen, rc2);

	rc2.X++;
	rc2.Y++;
	rc2.Width--;
	rc2.Height--;

	DrawBrush(pGraphics, rc2, brush, bFill);
}

void DrawStrokeFill(Gdiplus::Graphics* pGraphics, int top, IPDBrush* strokeBrush, IPDBrush* fillBrush, int m_strokeOrFill)
{
	Gdiplus::Rect strokerc(2+14, top+2+14, 28, 28);
	Gdiplus::Rect fillrc(2, top+2, 28, 28);

	if (m_strokeOrFill == 0)
	{
		DrawBrushWithOutline(pGraphics, fillrc, fillBrush, 1);
		pGraphics->SetClip(fillrc);
		DrawBrushWithOutline(pGraphics, strokerc, strokeBrush, 0);
	}
	else
	{
		DrawBrushWithOutline(pGraphics, strokerc, strokeBrush, 0);
		pGraphics->SetClip(strokerc);
		DrawBrushWithOutline(pGraphics, fillrc, fillBrush, 1);
	}
}

LRESULT CToolsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	CRect client;
	GetClientRect(&client);

	int top = client.bottom-64;

	FillSolidRect(hDC, 0, top, client.right, 64, GetSysColor(COLOR_MENU));
	Draw3DRect(hDC, 0, top, client.right, 64-16, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
	Draw3DRect(hDC, 0, top+48, client.right, 16, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

	CComPtr<IPDBrush> strokeBrush;
	CComPtr<IPDBrush> fillBrush;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectStroke> stroke;
		CComQIPtr<IPDObjectFill> fill;

		CComPtr<IPDBrush> brush;
		m_targetObjects[i]->get_brush(&brush);

		if (stroke = m_targetObjects[i])
		{
			if (i == 0)
			{
				strokeBrush = brush;
			}
			else if (strokeBrush && (brush->IsEqual(strokeBrush) == S_FALSE))
			{
				strokeBrush.Release();
			}
		}
		else if (fill = m_targetObjects[i])
		{
			if (i == 0)
			{
				fillBrush = brush;
			}
			else if (fillBrush && (brush->IsEqual(fillBrush) == S_FALSE))
			{
				fillBrush.Release();
			}
		}
	}


	{
		Gdiplus::Graphics graphics(hDC);

	//	DrawStrokeFill(&graphics, top, strokeBrush, fillBrush, m_strokeOrFill);
	}

#if 0
	CComPtr<IPDBrush> strokeBrush;
	CComPtr<IPDBrush> fillBrush;

	if (m_targetObjects.GetSize() == 0)
	{
		m_default->get_strokeBrush(&strokeBrush);
		m_default->get_fillBrush(&fillBrush);
	}
	else
	{
		// TODO
		for (int i = 0; i < min(m_targetObjects.GetSize(), 1); i++)
		{
			CComPtr<IPDObjectFrame> frame = m_targetObjects[i];

			frame->get_strokeBrush(&strokeBrush);
			frame->get_fillBrush(&fillBrush);
		}
	}

	{
		Gdiplus::Graphics graphics(hDC);

		DrawStrokeFill(&graphics, top, strokeBrush, fillBrush);

		Gdiplus::Pen blackpen(Gdiplus::Color(0,0,0));

		{
			Gdiplus::Point pts[] =
			{
				Gdiplus::Point(2+30, top+7),
				Gdiplus::Point(2+30+3, top+7-3),
				Gdiplus::Point(2+30+3, top+7+3),
			};

			graphics.FillPolygon(&Gdiplus::SolidBrush(Gdiplus::Color(0,0,0)), pts, 3);
		}

		graphics.DrawLine(&blackpen, 2+30+3, top+7, 2+30+3+3, top+7);
		graphics.DrawLine(&blackpen, 2+30+3+3, top+7, 2+30+3+3+2, top+7+2);
		graphics.DrawLine(&blackpen, 2+30+3+3+2, top+7+2, 2+30+3+3+2, top+7+2+3);

		{
			Gdiplus::Point pts[] =
			{
				Gdiplus::Point(2+30+3+3+2, top+7+2+3+3),
				Gdiplus::Point(2+30+3+3+2-3, top+7+2+3),
				Gdiplus::Point(2+30+3+3+2+3, top+7+2+3),
			};

			graphics.FillPolygon(&Gdiplus::SolidBrush(Gdiplus::Color(0,0,0)), pts, 3);
		}

		DrawBrush(&graphics,
			Gdiplus::Rect(m_brushTypeRect[0].left+1, m_brushTypeRect[0].top+1, m_brushTypeRect[0].Width()-2, m_brushTypeRect[0].Height()-2),
			(gApp->m_strokeOrFill == 0)? strokeBrush: fillBrush, BRUSH_COLOR);

		DrawBrush(&graphics,
			Gdiplus::Rect(m_brushTypeRect[1].left+1, m_brushTypeRect[1].top+1, m_brushTypeRect[1].Width()-2, m_brushTypeRect[1].Height()-2),
			(gApp->m_strokeOrFill == 0)? strokeBrush: fillBrush, BRUSH_GRADIENT);

		DrawBrush(&graphics,
			Gdiplus::Rect(m_brushTypeRect[2].left+1, m_brushTypeRect[2].top+1, m_brushTypeRect[2].Width()-2, m_brushTypeRect[2].Height()-2),
			NULL, BRUSH_NONE);
	}

	for (int i = 0; i < 3; i++)
	{
		PDBrushType brushType = (PDBrushType)-1;

		if (gApp->m_strokeOrFill == 0)
		{
			if (strokeBrush) strokeBrush->get_brushType(&brushType);
		}
		else
		{
			if (fillBrush) fillBrush->get_brushType(&brushType);
		}

		if ((i == 0 && brushType == BRUSH_COLOR) ||
			(i == 1 && brushType == BRUSH_GRADIENT) ||
			(i == 2 && brushType == BRUSH_NONE))
		{
			Draw3DRect(hDC, &m_brushTypeRect[i], GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
		}
		else
		{
			Draw3DRect(hDC, &m_brushTypeRect[i], GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
		}
	}
#endif

	EndPaint(&ps);
	return 0;
}

LRESULT CToolsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	int top = client.bottom-64;

	CRect strokerc(2+14, top+2+14, 2+14+28, top+2+14+28);
	CRect fillrc(2, 2+top, 2+28, top+2+28);
#if 0
	if (point.y >= client.bottom-16)
	{
		int type = -1;
		if (m_brushTypeRect[0].PtInRect(point))	// Color
		{
			type = 0;
		}
		else if (m_brushTypeRect[1].PtInRect(point))	// Gradient
		{
			type = 1;
		}
		else if (m_brushTypeRect[2].PtInRect(point))	// None
		{
			type = 2;
		}

		if (type >= 0)
		{
			if (m_targetObjects.GetSize() == 0)
			{
					CComPtr<IPDBrush> brush;
					if (gApp->m_strokeOrFill == 0)
						m_default->get_strokeBrush(&brush);
					else
						m_default->get_fillBrush(&brush);
			
					if (type == 0)
					{
						brush->put_brushType(BRUSH_COLOR);
					}
					else if (type == 1)
					{
						brush->put_brushType(BRUSH_GRADIENT);
					}
					else if (type == 2)
					{
						brush->put_brushType(BRUSH_NONE);
					}
			}
			else
			{
				for (int i = 0; i < m_targetObjects.GetSize(); i++)
				{
					CComPtr<IPDObjectFrame> frame = m_targetObjects[i];

					CComPtr<IPDBrush> brush;
					if (gApp->m_strokeOrFill == 0)
						frame->get_strokeBrush(&brush);
					else
						frame->get_fillBrush(&brush);

					if (type == 0)
					{
						brush->put_brushType(BRUSH_COLOR);
					}
					else if (type == 1)
					{
						brush->put_brushType(BRUSH_GRADIENT);
					}
					else if (type == 2)
					{
						brush->put_brushType(BRUSH_NONE);
					}
				}
			}
		}
	}
	else if (point.y > top)
	{
		CComQIPtr<IUIManager> uiManager = gApp->m_frame;

		if (gApp->m_strokeOrFill == 0)
		{
			if (strokerc.PtInRect(point))
			{
			}
			else if (fillrc.PtInRect(point))
			{
				gApp->m_strokeOrFill = 1;

				CComPtr<IPDBrush> brush;

				if (m_targetObjects.GetSize() == 0)
				{
				}
				else
				{
				}

//				uiManager->ActivateObject();
			}
		}
		else
		{
			if (fillrc.PtInRect(point))
			{
			}
			else if (strokerc.PtInRect(point))
			{
				gApp->m_strokeOrFill = 0;
			}
		}
	}
#endif
	Invalidate();

	return 0;
}

STDMETHODIMP CToolsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDObjectWithBrush> withbrush = object;
	if (withbrush = object)
	{
		m_targetObjects.Add(withbrush);
		withbrush.Detach();

		*cookie = m_targetObjects.GetSize();

		CComQIPtr<IPDObjectStroke> stroke = object;
		if (stroke)
			m_strokeOrFill = 0;
		else
			m_strokeOrFill = 1;

//		SetControlValues();

		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CToolsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(object, m_targetObjects[i]))
		{
			m_targetObjects[i]->Release();
			m_targetObjects.RemoveAt(i);
			break;
		}
	}

	Invalidate();

//	SetControlValues();

	return S_OK;
}
