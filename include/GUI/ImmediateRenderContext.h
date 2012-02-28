namespace System
{
namespace Gui
{

class GUIEXT ImmediateRenderContext : public RenderContext
{
public:

	CTOR ImmediateRenderContext(Graphics::RenderTarget* rt);
//	CTOR ImmediateRenderContext(ImmediateRenderContext* parent);

	Graphics::RenderTarget* GetRT() override
	{
		return m_rt;
	}

	virtual void Pop() override;
	virtual void PushTransform(Transform* transform) override;
	virtual void PushTransform(const gm::matrix3f& transform) override;

	virtual void SetAntialiasPerPrimitive(bool antialias) override;

	virtual void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width) override;
	virtual void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width, StrokeStyle* style) override;
	virtual void FillRectangle(gm::RectF rect, Brush* brush) override;
	virtual void DrawRectangle(gm::RectF rect, Brush* brush, float width) override;
	virtual void FillEllipse(float cx, float cy, float rx, float ry, Brush* brush) override;
	virtual void DrawEllipse(float cx, float cy, float rx, float ry, Brush* brush, float width) override;
	virtual void FillGeometry(const geometry& geom, Brush* brush);
	virtual void DrawGeometry(const geometry& geom, Brush* brush, float width);
	virtual void OutputText(StringIn text, Brush* brush, StringIn fontFamily, float fontSize, int fontWeight = 400);
	virtual void OutputText(StringIn text, Brush* brush, TextFormat* textFormat, gm::RectF layoutRect);
	virtual void DrawVisual(Visual* visual);
	virtual void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor);
	virtual void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor, const gm::RectF& srcRect) override;

	virtual void DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity) override;
	virtual void DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity, const gm::RectF& srcRect) override;

	class MatrixState
	{
	public:
		D3DXMATRIX view;
		D3DXMATRIX modelView;
		D3DXMATRIX modelViewProjection;
		D3DXMATRIX modelViewI;
		D3DXMATRIX modelViewProjectionI;
		bool m_modelViewI_Valid;
		bool m_modelViewProjection_Valid;
		bool m_hasProjection;
	};

//	stack<Matrix> m_modelViewMatrixStack;

	void PushModelViewProjection(const D3DXMATRIX& modelView, const D3DXMATRIX& projection)
	{
		MatrixState mat;
		mat.modelView = m_modelViewMatrix;
		mat.modelViewI = m_modelViewIMatrix;
		mat.modelViewProjection = m_modelViewProjectionMatrix;
		mat.m_modelViewI_Valid = m_modelViewIMatrix_Valid;
		mat.m_modelViewProjection_Valid = m_modelViewProjectionMatrix_Valid;

		mat.m_hasProjection = true;

		m_matrixStack.push(mat);
		m_projectionStack.push(m_projectionMatrix);

		m_projectionMatrix = projection;
		m_modelViewMatrix = modelView;
		m_modelViewIMatrix_Valid = false;
		m_modelViewProjectionMatrix_Valid = false;
	}

	void PushModelView(const D3DXMATRIX& modelView)
	{
		MatrixState mat;
		mat.modelView = m_modelViewMatrix;
		mat.modelViewI = m_modelViewIMatrix;
		mat.modelViewProjection = m_modelViewProjectionMatrix;

		mat.m_modelViewI_Valid = m_modelViewIMatrix_Valid;
		mat.m_modelViewProjection_Valid = m_modelViewProjectionMatrix_Valid;

		mat.m_hasProjection = false;

		m_matrixStack.push(mat);

		m_modelViewMatrix = modelView;
		m_modelViewIMatrix_Valid = false;
		m_modelViewProjectionMatrix_Valid = false;
	}

	void PopMatrix()
	{
		const MatrixState& mat = m_matrixStack.top();

		m_modelViewMatrix = mat.modelView;
		m_modelViewIMatrix = mat.modelViewI;
		m_modelViewProjectionMatrix = mat.modelViewProjection;

		m_modelViewIMatrix_Valid = mat.m_modelViewI_Valid;
		m_modelViewProjectionMatrix_Valid = mat.m_modelViewProjection_Valid;

		if (mat.m_hasProjection)
		{
			ASSERT(0);
		}

		m_matrixStack.pop();
	}

	/*
	void PushProjectionMatrix()
	{
		Matrix mat;
		mat.modelView = m_modelViewMatrix;
		mat.modelViewI = m_modelViewIMatrix;
		mat.modelViewProjection = m_modelViewProjectionMatrix;
		mat.m_modelViewI_Valid = m_modelViewMatrixI_Valid;
		mat.m_modelViewProjectionI_Valid = m_modelViewMatrixProjectionI_Valid;
		mat.m_hasProjection = true;

		m_modelViewMatrixStack.push(mat);
		m_projectionStack.push(m_projectionMatrix);
	}
	*/

	D3DXMATRIX& projectionMatrix()
	{
		return m_projectionMatrix;
	}

	D3DXMATRIX& viewMatrix()
	{
		return m_viewMatrix;
	}

	D3DXMATRIX& modelMatrix()
	{
		return m_modelMatrix;
	}

	D3DXMATRIX& modelViewMatrix();

	D3DXMATRIX& modelViewITMatrix()
	{
		D3DXMatrixTranspose(&m_modelViewITMatrix, &modelViewIMatrix());
		return m_modelViewITMatrix;
	}

	D3DXMATRIX& modelViewProjectionMatrix();
	D3DXMATRIX& modelViewIMatrix();

	stack<gm::matrix3f> m_transformStack;
	gm::matrix3f m_transform;
	Graphics::RenderTarget* m_rt;

	stack<MatrixState> m_matrixStack;
	stack<D3DXMATRIX> m_projectionStack;

//	ImmediateRenderContext* m_parent;

//protected:

	D3DXMATRIX m_modelMatrix;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_modelViewMatrix;
	D3DXMATRIX m_modelViewProjectionMatrix;
	D3DXMATRIX m_modelViewIMatrix;
	D3DXMATRIX m_modelViewTMatrix;
	D3DXMATRIX m_modelViewITMatrix;
	D3DXMATRIX m_projectionIMatrix;
	D3DXMATRIX m_projectionTMatrix;
	D3DXMATRIX m_projectionITMatrix;
	D3DXMATRIX m_modelViewProjectionIMatrix;
	D3DXMATRIX m_modelViewProjectionTMatrix;
	D3DXMATRIX m_modelViewProjectionITMatrix;

	vector<Graphics::Light> m_lights;
	int m_nLight;

	bool m_modelViewMatrix_Valid;
	bool m_modelViewProjectionMatrix_Valid;
	bool m_modelViewIMatrix_Valid;
	bool m_modelViewTMatrix_Valid;
	bool m_modelViewITMatrix_Valid;
};

}	// Gui
}	// System
