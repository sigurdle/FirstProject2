#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(WaveformData*, WaveformVisual, Data, nullptr)
IMP_DEPENDENCY_PROPERTY(int64, WaveformVisual, AtSample, 0LL)
IMP_DEPENDENCY_PROPERTY(int64, WaveformVisual, SelectionStartSample, -1LL)
IMP_DEPENDENCY_PROPERTY(int64, WaveformVisual, SelectionEndSample, -1LL)
IMP_DEPENDENCY_PROPERTY(int64, WaveformVisual, SelectionInitSample, -1LL)
IMP_DEPENDENCY_PROPERTY(Brush*, WaveformVisual, ForegroundBrush, new SolidColorBrush(0.0f, 0.1f, 0.3f))
IMP_DEPENDENCY_PROPERTY(Brush*, WaveformVisual, SelectionBackgroundBrush, new SolidColorBrush(0.5f, 0.5f, 1.0f, 0.5f))

DependencyClass* WaveformVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_DataProperty(),
		get_AtSampleProperty(),
		get_SelectionStartSampleProperty(),
		get_SelectionEndSampleProperty(),
		get_SelectionInitSampleProperty(),
		get_ForegroundBrushProperty(),
		get_SelectionBackgroundBrushProperty(),
	};

	return &depclass;
}

WaveformVisual::WaveformVisual() : UIElement(get_Class())
{
	set_Width(800);
	set_Height(300);
}

void WaveformVisual::Render(ManagedRenderContext renderContext)
{
	static Brush* brush = get_ForegroundBrush();
	static Brush* atbrush = new SolidColorBrush(0,0,0);
//	static Brush* selectionbrush = new SolidColorBrush(0.5,0.5,1, 1);

	WaveformData* wdata = get_Data();
	if (wdata)
	{
		if (wdata->get_Format().wBitsPerSample == 16)
		{
			//if (wdata->m_wfx.nBlockAlign

			short* audioData = (short*)wdata->m_audioData;


		//	double width = 800;
			float height = 300;

			uint nsamples = 800;

			short* data = new short[nsamples];

			double scaleX = (double)wdata->m_nsamples / nsamples;
			double rscaleX = 1/scaleX;

			for (uint i = 0; i < nsamples; ++i)
			{
				uint actualsample = i * scaleX;
				short value = audioData[actualsample];
				/*
				if (i > 400)
				{
					MessageBeep(-1);
				}
				*/

				data[i] = value;
			}

			float scaleY = height / 65535;

			ID2D1PathGeometry* pD2D1Geometry;
			Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pD2D1Geometry);
			ID2D1GeometrySink* pGeometrySink;
			pD2D1Geometry->Open(&pGeometrySink);

			pGeometrySink->SetFillMode(D2D1_FILL_MODE_WINDING);
			pGeometrySink->BeginFigure(D2D1::Point2F(0, height/2), D2D1_FIGURE_BEGIN_FILLED);

			short* p;

			p = data;
			for (uint i = 0; i < nsamples; ++i)
			{
				short value2 = MAX(*p, 0);
				float y = height/2 - value2 * scaleY;

				pGeometrySink->AddLine(D2D1::Point2F(i, y));
				pGeometrySink->AddLine(D2D1::Point2F(i+1, y));
				++p;
			}

			p = data + nsamples;
			for (int i = nsamples-1; i >= 0; --i)
			{
				--p;
				short value2 = MIN(*p, 0);
				float y = height/2 - value2 * scaleY;

				pGeometrySink->AddLine(D2D1::Point2F(i+1, y));
				pGeometrySink->AddLine(D2D1::Point2F(i, y));
			}

			delete[] data;

			pGeometrySink->EndFigure(D2D1_FIGURE_END_CLOSED);
			pGeometrySink->Close();
			pGeometrySink->Release();

			renderContext.m_p->GetRT()->m_spRT->FillGeometry(pD2D1Geometry, brush->Create(renderContext.m_p, this));

			pD2D1Geometry->Release();

			if (true)
			{
				float x = get_AtSample() * rscaleX;
				renderContext.DrawLine(gm::PointF(x, 0), gm::PointF(x, height), atbrush, 1);
			}

			int64 selectionStartSample = get_SelectionStartSample();
			int64 selectionEndSample = get_SelectionEndSample();
			if (selectionStartSample != -1)
			{
				float x1 = selectionStartSample * rscaleX;
				float x2 = selectionEndSample * rscaleX;

				renderContext.FillRectangle(gm::RectF(x1, 0, x2-x1, height), get_SelectionBackgroundBrush());
			}
		}
		else if (wdata->get_Format().wBitsPerSample == 8)
		{
			ASSERT(0);
		}
	}
}

void WaveformVisual::OnMouseLeftButtonDoubleClick(MouseButtonEventArgs* args)
{
	WaveformData* wdata = get_Data();
	if (wdata)
	{
		set_SelectionInitSample(0);
		set_SelectionStartSample(0);
		set_SelectionEndSample(wdata->get_SampleCount64());
	}
}

void WaveformVisual::OnMouseLeftButtonDown(MouseButtonEventArgs* args)
{
	Point mouse = args->GetPosition(this);

	WaveformData* wdata = get_Data();
	if (wdata)
	{
		double height = 300;
		uint nsamples = 800;
		double scaleX = (double)wdata->m_nsamples / nsamples;
		double rscaleX = 1/scaleX;

		set_AtSample(mouse.X * scaleX);
		set_SelectionInitSample(mouse.X * scaleX);
		set_SelectionStartSample(mouse.X * scaleX);
		set_SelectionEndSample(mouse.X * scaleX);

		CaptureMouse();
	}
}

/*
void WaveformVisual::Play()
{
}
*/

void WaveformVisual::OnMouseLeftButtonUp(MouseButtonEventArgs* args)
{
	ReleaseMouseCapture();
}

void WaveformVisual::OnMouseMove(MouseEventArgs* args)
{
	if (get_IsMouseCaptured())
	{
		Point mouse = args->GetPosition(this);

		WaveformData* wdata = get_Data();

		double height = 300;
		uint nsamples = 800;
		double scaleX = (double)wdata->m_nsamples / nsamples;
		double rscaleX = 1/scaleX;

		int64 atsample = mouse.X * scaleX;
		if (atsample < get_SelectionInitSample())
		{
			set_SelectionStartSample(atsample);
			set_SelectionEndSample(get_SelectionInitSample());
		}
		else
		{
			set_SelectionStartSample(get_SelectionInitSample());
			set_SelectionEndSample(atsample);
		}

		set_AtSample(atsample);
	}
}

}	// Gui
}	// System
