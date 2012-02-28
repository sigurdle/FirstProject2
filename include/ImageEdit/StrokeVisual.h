namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT StrokeVisual : public BElement
{
public:

	CTOR StrokeVisual();

	virtual void Render(Gui::ManagedRenderContext renderContext) override;

	void MoveTo(gm::PointF pos);
	void LineTo(Graphics::RenderTarget* rt, gm::PointF pos);
	void Blt(Graphics::RenderTarget* rt, Graphics::Bitmap* bitmap, gm::RectF dstRect, gm::vector4f colorMultiply, gm::vector4f colorTranslate = gm::vector4f());

	void CreateVertexBuffer();

	void ReloadEffect();

	DEPENDENCY_CLASS(StrokeVisual, BElement)

	vector<gm::PointF> m_points;
	float m_brushSize;
	float m_spacing;
	gm::vector4f m_colorMultiply;
	PaintBrush* m_brush;
	ID3D11Buffer* m_vertexBuffer;

	ImageDocument* m_document;

	gm::PointF m_oldpos;

	static void LoadEffect();

	static ID3DX11Effect* m_effect;
	static ID3DX11EffectTechnique* m_RenderTextureTechnique;

	static ID3DX11EffectMatrixVariable* m_modelViewVariable;
	static ID3DX11EffectMatrixVariable* m_projectionVariable;
	static ID3DX11EffectMatrixVariable* m_modelViewProjectionVariable;
	static ID3DX11EffectShaderResourceVariable* m_texture0Variable;
	static ID3DX11EffectShaderResourceVariable* m_texture1Variable;
	static ID3DX11EffectMatrixVariable* m_textureMatrix0Variable;
	static ID3DX11EffectMatrixVariable* m_textureMatrix1Variable;
	static ID3DX11EffectVectorVariable* m_colorTranslateVariable;
	static ID3DX11EffectVectorVariable* m_colorMultiplyVariable;

//	static ID3D10EffectVectorVariable* m_texelsPerPixelVariable;
	static ID3D11InputLayout* m_vertexLayout0;
};

}	// ImageEdit
}	// System
