namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT MaskOutlineVisual : public Gui::Visual
{
public:
	CTOR MaskOutlineVisual() : Gui::Visual(get_Class())
	{
		m_enabled = true;
	}

	virtual void Render(Gui::ManagedRenderContext renderContext) override;

	void Render(Graphics::RenderTarget* pGraphics);

	ID3D11Buffer* m_vertexBuffer;

	Mask* m_mask;

	Graphics::Bitmap* m_pattern;
	gm::RectF m_destRect;
	float m_srcX;
	float m_srcY;
	float m_srcWidth;
	float m_srcHeight;

	float m_patternSrcX;
	float m_patternSrcY;

	bool m_enabled;

//	float m_opacity;
//	uint32 m_blendMode;
//	uint32 m_adjustmentMode;

	// Brightness/Contrast
//	float m_brightness;
//	float m_contrast;

	DEPENDENCY_CLASS(MaskOutlineVisual, Gui::Visual)

	static ID3DX11Effect* m_effect;
	static ID3DX11EffectTechnique* m_renderSelectionTechnique;

	static ID3DX11EffectMatrixVariable* m_modelViewProjectionVariable;
	static ID3DX11EffectShaderResourceVariable* m_texture0Variable;
	static ID3DX11EffectShaderResourceVariable* m_texture1Variable;
	static ID3DX11EffectMatrixVariable* m_texture0MatrixVariable;
	static ID3DX11EffectVectorVariable* m_texture1TranslateVariable;

	static ID3DX11EffectVectorVariable* m_texelsPerPixelVariable;
	static ID3D11InputLayout* m_vertexLayout0;
};

}	// ImageEdit
}	// System
