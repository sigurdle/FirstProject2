namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT BitmapLayer : public Layer
{
public:

	CTOR BitmapLayer(ImageDocument* document);

	virtual BitmapLayer* Clone();
	virtual int Render(ID3D10RenderTargetView* renderTarget, ID3D10RenderTargetView* renderTarget2, Graphics::Bitmap* targetBitmap, Graphics::Bitmap* targetBitmap2, Gui::ManagedRenderContext pGraphics);
//	virtual int Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics);
//	virtual int Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics);
	virtual Graphics::Bitmap* get_ThumbnailBitmap();

	virtual Graphics::Bitmap* get_Bitmap()
	{
		return m_bitmap;
	}

	void CreateA8R8G8B8(int width, int height);
	void CreateA8(int width, int height);
	void CreateR16F(int width, int height);

//	UI::Histogram* get_Histogram();

public:

//	UI::Histogram* m_histogram;

	Graphics::Bitmap* m_bitmap;
	Video* m_video;

	float m_x;
	float m_y;

	/*
	PaintBrush* m_paintBrush;
	vector<LDraw::PointF> m_points;
	*/
};

}
}
