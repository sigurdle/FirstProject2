namespace System
{
namespace UI
{

class Histogram : public Object
{
public:
	CTOR Histogram();
	CTOR Histogram(LDraw::Bitmap* bitmap);

	uint32 a_hist[256];
	uint32 r_hist[256];
	uint32 g_hist[256];
	uint32 b_hist[256];
	uint32 m_hist[256];

	void Calc(LDraw::Bitmap* bitmap);

//	list<HistogramView*> m_views;
};

enum HistogramChannel
{
	LV_HIST_RGB,
	LV_HIST_RED,
	LV_HIST_GREEN,
	LV_HIST_BLUE,
	LV_HIST_ALPHA,
};

class HistogramView : public UI::FrameworkElement
{
public:
	CTOR HistogramView();

//	Histogram* m_pHistogram;

	HistogramChannel m_channel;

	HistogramChannel get_Channel()
	{
		return m_channel;
	}

	void set_Channel(HistogramChannel channel)
	{
		m_channel = channel;
		InvalidateRender();
	}

	Histogram* get_Histogram();
	void set_Histogram(Histogram* histogram);

	virtual void OnRender(UI::Graphics* pGraphics);

	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize);

	void Update();

	static DependencyProperty* s_HistogramProperty;
};

}
}
