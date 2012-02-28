namespace System
{
namespace Graphics
{

class GfxExt RenderTargetStoreState
{
public:
	UINT m_numOldViewports;
	D3D10_VIEWPORT m_oldViewports[8];

	ID3D10RenderTargetView* m_pOldRenderTargetView;
	ID3D10DepthStencilView* m_pOldDepthStencilView;
};

class GfxExt RenderTarget : public Object
{
public:

	CTOR RenderTarget();
	CTOR RenderTarget(ID2D1RenderTarget* d2d1RenderTarget);
	CTOR RenderTarget(GraphicsI* gi, HWND hWnd, WindowSurfDesc& desc);
	CTOR RenderTarget(GraphicsI* gi, IDXGISwapChain* swapChain, ID3D10RenderTargetView* pRenderTargetView);
	CTOR RenderTarget(GraphicsI* gi, ID3D10Texture2D* pRenderTargetTexture, ID3D10RenderTargetView* pRenderTargetView);

	virtual ~RenderTarget();

	void Create(GraphicsI* gi,
		IDXGISwapChain* swapChain,
		ID3D10RenderTargetView* pRenderTargetView);

	void Create(GraphicsI* gi,
		ID3D10Texture2D* pRenderTargetTexture,
		ID3D10RenderTargetView* pRenderTargetView);

	virtual void Destroy();

	virtual void Present();

	virtual void BeginDraw(RenderTargetStoreState* state);
	virtual void EndDraw(RenderTargetStoreState* state);

	virtual bool WindowResized();

	void SetTransform(const D2D1_MATRIX_3X2_F& transform);

	GraphicsI* m_gi;	// abstract opengl or d3d10, or ...
	OpenGL_I* m_opengl;	// concrete
	Direct3D10_I* m_d3d10;	// concrete

	HWND m_hWnd;

	// D3D
	IDXGISwapChain* m_swapChain;
	ID3D10Texture2D* m_pRenderTargetTexture;
	ID3D10RenderTargetView* m_pRenderTargetView;

	ID3D11Texture2D* m_pRenderTargetTexture11;
	ID3D11RenderTargetView* m_pRenderTargetView11;

	ID3D10Texture2D* m_pDepthStencil;
	ID3D10DepthStencilView* m_pDepthStencilView;

	ID2D1RenderTarget* m_spRT;

	RenderTarget* m_parentRenderTarget;

	gm::matrix3f m_transform3x3;
	gm::matrix4f m_modelView;
	gm::matrix4f m_projection;
	gm::matrix4f m_modelViewProjection;

private:

	RenderTarget& operator = (const RenderTarget&);
};

}	// Graphics
}	// System
