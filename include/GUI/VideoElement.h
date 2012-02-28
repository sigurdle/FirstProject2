namespace System
{
namespace Gui
{

interface IMediaControl
{
	virtual void Play() abstract;
	virtual void Pause() abstract;
	virtual void Stop() abstract;
};

class GUIEXT VideoElement : public UIElement, public IMediaControl, protected DShow::IVideoPresenter
{
public:

	CTOR VideoElement();

	virtual void Play() override;	// IMediaControl
	virtual void Pause() override;	// IMediaControl
	virtual void Stop() override;	// IMediaControl

	DEPENDENCY_PROPERTY(String, Url)

	DEPENDENCY_PROPERTY(unsigned int, VideoWidth)
	DEPENDENCY_PROPERTY(unsigned int, VideoHeight)

	DEPENDENCY_PROPERTY(double, CurrentTime)
	DEPENDENCY_PROPERTY(double, DurationTime)

	DEPENDENCY_PROPERTY(bool, IsPlaying)
	DEPENDENCY_PROPERTY(bool, IsStopped)
	DEPENDENCY_PROPERTY(bool, IsPaused)

	DEPENDENCY_PROPERTY(float, Volume)
	DEPENDENCY_PROPERTY(float, Balance)

	DEPENDENCY_CLASS(VideoElement, UIElement)

	Graphics::Bitmap* get_Bitmap()
	{
		return m_pBitmap;
	}

	DShow::IVideoPlayer* get_Video()
	{
		return m_pVideo;
	}

protected:

	virtual HRESULT Init(IDirect3DDevice9* d3ddev, uint width, uint height, ID3D10Texture2D* texture) override;	// IVideoPresenter
	virtual HRESULT DrawScene(IDirect3DDevice9* d3ddev, IDirect3DTexture9* texture) override;	// IVideoPresenter
//	virtual void SetSrcRect(float fTU, float fTV) override;	// IVideoPresenter

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;
	virtual void Render(ManagedRenderContext renderContext) override;
	virtual Graphics::Bitmap* GetBitmap(Graphics::RenderTarget* rt, int scaledWidth, int scaledHeight, float scaleX, float scaleY) override;

	DShow::IVideoPlayer* m_pVideo;
	Graphics::Bitmap* m_pBitmap;
};

}	// Gui
}	// System
