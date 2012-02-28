#include "stdafx.h"
#include "Histogram.h"

#include <d3d9.h>

namespace System
{
namespace UI
{

Histogram::Histogram(LDraw::Bitmap* bitmap)
{
	Calc(bitmap);
}

void Histogram::Calc(LDraw::Bitmap* bitmap)
{
	uint8 r_lut[256];
	uint8 g_lut[256];
	uint8 b_lut[256];

	{
		for (int i = 0; i < 256; i++)
		{
			r_lut[i] = i;
			g_lut[i] = i;
			b_lut[i] = i;
		}
	}

	{
		for (int i = 0; i < 256; i++)
		{
			a_hist[i] = 0;
			r_hist[i] = 0;
			g_hist[i] = 0;
			b_hist[i] = 0;
			m_hist[i] = 0;
		}
	}

	D3DLOCKED_RECT locked_rect;
	bitmap->m_d3dTexture->LockRect(0, &locked_rect, NULL, 0);

	LDraw::BitmapData bitmapData;
//	bitmap->LockBits(NULL, LDraw::ImageLockModeRead, &bitmapData);
	bitmapData.Stride = locked_rect.Pitch;
	bitmapData.Scan0 = (uint8*)locked_rect.pBits;
	bitmapData.Width = bitmap->GetWidth();
	bitmapData.Height = bitmap->GetHeight();

	uint32 skip = (bitmapData.Stride>>2) - bitmapData.Width;
	LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)(bitmapData.Scan0);

	for (int y = 0; y < bitmapData.Height; y++)
	{
		for (int x = 0; x < bitmapData.Width; x++)
		{
			a_hist[in->a] ++;

			r_hist[in->r] ++;
			m_hist[r_lut[in->r]]++;

			g_hist[in->g] ++;
			m_hist[g_lut[in->g]]++;

			b_hist[in->b] ++;
			m_hist[b_lut[in->b]]++;

			in++;
		}

		in += skip;
	}

	//bitmap->UnlockBits(&bitmapData);
	bitmap->m_d3dTexture->UnlockRect(0);

#if 0
		list<HistogramView*>::iterator it = m_views.begin();
		while (it != m_views.end())
		{
			(*it)->Update();
			++it;
		}
	}

//	static_cast<Visual*>(GetRParent())->_OnRender(pGraphics);
	GetRParent()->_OnRender(pGraphics);
#endif
}

DependencyProperty* HistogramView::s_HistogramProperty = RegisterProperty(WSTR("Histogram"), typeid(Histogram), typeid(HistogramView));

HistogramView::HistogramView()
{
	m_channel = LV_HIST_RGB;
}

Histogram* HistogramView::get_Histogram()
{
	return static_cast<Histogram*>(GetValue(s_HistogramProperty));
}

void HistogramView::set_Histogram(Histogram* histogram)
{
	SetValue(s_HistogramProperty, histogram);
}

void HistogramView::Update()
{
	//InvalidateMeasure();
	InvalidateRender();
}

LDraw::SizeD HistogramView::MeasureOverride(LDraw::SizeD availSize)
{
	return LDraw::SizeD(256, 256);
}

void HistogramView::OnRender(UI::Graphics* pGraphics)
{
	long max_hist;
	long total = 0;
	long count = 0;
	uint32 *histogram;
	long scale_hist[256];
	uint32 composite_hist[256];
	double scale;

	Histogram* m_pHistogram = get_Histogram();

	if (m_pHistogram == NULL)
		return;

	switch (m_channel)
	{
	case LV_HIST_RED:
		{
		for (int y=0; y<256; y++)
		{
			composite_hist[y] = m_pHistogram->r_hist[y];
		}
		}
		break;
		
	case LV_HIST_GREEN:
		{
		for (int y=0; y<256; y++)
		{
			composite_hist[y] = m_pHistogram->g_hist[y];
		}
		}
		break;
		
	case LV_HIST_BLUE:
		{
		for (int y=0; y<256; y++)
		{
			composite_hist[y] = m_pHistogram->b_hist[y];
		}
		}
		break;
		
	case LV_HIST_ALPHA:
		{
		for (int y=0; y<256; y++) {
			composite_hist[y] = m_pHistogram->a_hist[y];
		}
		}
		break;
		
	default:
		{
		for (int y=0; y<256; y++)
		{
			composite_hist[y] = m_pHistogram->m_hist[y];
		}
		}
		break;
	}

	histogram = composite_hist;
	max_hist = composite_hist[0];

	{
		for (int y = 0; y < 256; y++)
		{
			if (histogram[y]) ++count;
			total += histogram[y];
			if (histogram[y] > max_hist) max_hist = histogram[y];			
		}
	}
	
	// like photoshop, 
	// Reset biggest value to four times the average, if that
	// is smaller (this lets large spikes poke above the top
	// of the graph, and gives more graph space to median values).

	LDraw::SizeD actualSize = get_ActualSize();

	if (count)
	{
		max_hist = (long)(MIN(max_hist, (4 * total / (double) count)));

		scale = ((double)actualSize.Height/(double)max_hist);
	} 
	else
	{
		scale = 1;
	}

	{
		for (int y = 0; y < 256; y++)
		{
			scale_hist[y] = (long)(scale * histogram[y]);
		}
	}

	if (true /*globals->freshHist*/)
	{
		__release<LDraw::GraphicsPathF> path = new LDraw::GraphicsPathF;
		path->AddMove(0, actualSize.Height);
		for (int y = 0; y < 256; y++)
		{
		//	MoveToEx(de->hDC, y, LV_HIST_HEIGHT, NULL);
		//	LineTo(de->hDC, y, (short)(LV_HIST_HEIGHT-scale_hist[y]-1));
			path->AddLine(y, (actualSize.Height-scale_hist[y]-1));
			path->AddLine(y+1, (actualSize.Height-scale_hist[y]-1));
		}
		path->AddLine(256, actualSize.Height);

	//	pGraphics->FillPath(new LDraw::SolidBrush(LDraw::Color(0,0,0)), path);
		pGraphics->DrawPath(new LDraw::Pen(LDraw::Color(0,0,0)), path);
	}
	else
	{
	}
}

}
}
