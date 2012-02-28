#include "stdafx.h"
#include "HueSaturate.h"

namespace System
{

double HueSaturate::get_Rotate()
{
	return m_rotate;
}

void HueSaturate::put_Rotate(double value)
{
	m_rotate = value;
	GetRParent()->InvalidateRender();
}

double HueSaturate::get_Saturate()
{
	return m_saturate;
}

void HueSaturate::put_Saturate(double value)
{
	m_saturate = value;
	GetRParent()->InvalidateRender();
}

void HueSaturate::OnRender(UI::Graphics* pGraphics)
{
	// Hue Rotate
	double radians = gmRadians(m_rotate);
	LDraw::matrix3f a =
		
		LDraw::matrix3f(	+0.213, +0.715, +0.072,
		+0.213, +0.715, +0.072,
		+0.213, +0.715, +0.072) +
		
		cos(radians) * LDraw::matrix3f(	+0.787, -0.715, -0.072,
		-0.213, +0.285, -0.072,
		-0.213, -0.715, +0.928) +
		
		sin(radians) *	LDraw::matrix3f(	-0.213, -0.715,+0.928,
		+0.143, +0.140,-0.283,
		-0.787, +0.715, +0.072);
	
	LDraw::ColorMatrixF cm(	a[0][0], a[0][1], a[0][2], 0, 0,
									a[1][0], a[1][1], a[1][2], 0, 0,
									a[2][0], a[2][1], a[2][2], 0, 0,
									0, 0, 0, 1, 0);

	// Saturate
	double s = m_saturate;
	LDraw::ColorMatrixF cm2(0.213+0.787*s, 0.715-0.715*s, 0.072-0.072*s, 0, 0,
									0.213-0.213*s, 0.715+0.285*s, 0.072-0.072*s, 0, 0,
									0.213-0.213*s, 0.715-0.715*s, 0.072+0.928*s, 0, 0,
									0, 0, 0, 1, 0);

	pGraphics->MultiplyColorTransform(cm * cm2);

	GetRParent()->_OnRender(pGraphics);
}

void HueRotateView::OnRender(UI::Graphics* pGraphics)
{
	double width = 110;
	double height = 110;
	pGraphics->TranslateTransform(width/2, height/2);

	//vertex[0] = gmVector3d(0, -m_computedSize.Height/2, 0);

	int nsectors = 48;

	for (int i = 0; i < nsectors; i++)
	{
		LDraw::PointF vertex[3];
		LDraw::Color col0 = LDraw::Color(255, 255, 255);
		LDraw::Color col1 = LDraw::Color::FromHLS((float)i/nsectors, 0.5, 1.0);
		LDraw::Color col2 = LDraw::Color::FromHLS((float)(i+1)/nsectors, 0.5, 1.0);

		vertex[0] = LDraw::PointF(0, 0);
		{
			double angle = i*(360.0/nsectors);

			double x = cos(gmRadians(angle))*width/2;
			double y = sin(gmRadians(angle))*height/2;

			vertex[1].X = x;
			vertex[1].Y = y;
		}

		{
			double angle = (i+1)*(360.0/nsectors);

			double x = cos(gmRadians(angle))*width/2;
			double y = sin(gmRadians(angle))*height/2;

			vertex[2].X = x;
			vertex[2].Y = y;
		}

		LDraw::Color color[3];

		color[0] = col0;
		color[1] = col1;
		color[2] = col2;

		pGraphics->FillTriangle(vertex, color, 0);
	}

	{
		double rotate = m_hue->get_Rotate();

		double x = cos(gmRadians(rotate))*(width/2 - 5);
		double y = sin(gmRadians(rotate))*(height/2 - 5);

		LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
		pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

		pGraphics->FillEllipse(new LDraw::SolidBrush(LDraw::Color(0, 0, 0)), x-5, y-5, 10, 10);
		pGraphics->FillEllipse(new LDraw::SolidBrush(LDraw::Color(255, 255, 255)), x-4, y-4, 8, 8);

		pGraphics->SetSmoothingMode(oldSmoothingMode);
	}
}

#if 0
void HueRotateView::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown")
		{
			evt->stopPropagation();

			if (m_dragging == 0)
			{
				m_dragging = 1;
				CaptureMouse();
			}
		}
		else if (*evt->get_type() == L"mouseup")
		{
			evt->stopPropagation();

			if (m_dragging)
			{
				m_dragging = 0;
				ReleaseMouseCapture();
			}
		}
		else if (*evt->get_type() == L"mousemove")
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseEvt = static_cast<UI::MouseEvent*>(evt);

			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			if (m_dragging)
			{
				double angle = gmDegrees(LDraw::GetLineAngleRadians(100/2, 100/2, point.X, point.Y));

				m_hue->put_Rotate(angle);
				InvalidateRender();
			}
		}
	}
}
#endif

}
