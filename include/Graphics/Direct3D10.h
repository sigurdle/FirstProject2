namespace System
{
namespace Graphics
{

typedef ID3D11ShaderResourceView ID3DShaderResourceView;
typedef ID3DX11EffectVectorVariable ID3DEffectVectorVariable;
typedef ID3DX11EffectMatrixVariable ID3DEffectMatrixVariable;
typedef ID3DX11EffectShaderResourceVariable ID3DEffectShaderResourceVariable;

class GfxExt Direct3D10_I : public GraphicsI
{
public:

	static Direct3D10_I* GetCurrent();

//	static Direct3D10_I* Create(HWND hwnd);

	ID3D10ShaderResourceView* CreateShaderResourceView(ID3D10Resource* resource);

	UINT Begin(ID3DX10EffectTechnique* technique);
	void Apply(ID3DX10EffectTechnique* technique, UINT nPass);

	void VariableSetFloatVector(ID3DX10EffectVectorVariable* variable, const float* v);
	void VariableSetMatrix(ID3DX10EffectMatrixVariable* variable, const float* m);
	void VariableSetResource(ID3DX10EffectShaderResourceVariable* variable, ID3D10ShaderResourceView* resourceView);

	ID3D10Blob* CompileShader(LPCWSTR filename, LPCSTR profile);
	long CreateVertexShader(ID3D10Blob* blob, ID3D10VertexShader** pp);
	long CreatePixelShader(ID3D10Blob* blob, ID3D10PixelShader** pp);
	void VSSetShader(ID3D10VertexShader* shader);
	void PSSetShader(ID3D10PixelShader* shader);
	void CreateRenderTargetView();

	virtual void BeginDraw() override;
	virtual void EndDraw() override;

	virtual void Shutdown() override;
//	virtual bool WindowResized() override;

	virtual IDirect3DDevice9* GetD3D9Device();
	virtual CGcontext GetCGContext();
	virtual int cgGetLatestProfile(unsigned int type);

	virtual void Viewport(int x, int y, int width, int height);
	virtual void SetClipPlane(int n, const float equation[4]);
	virtual void EnableClipPlanes(UINT mask);

	virtual void SetPrimitiveTopology(unsigned int mode);
	virtual void Draw(/*unsigned int mode,*/ UINT first, UINT count);
	virtual void DrawIndexed(/*unsigned int mode,*/ int start, int end, UINT count/*, unsigned int type, int startIndex*/);
	virtual void DrawUP(/*unsigned int mode,*/ UINT count, void* data, int stride);

	virtual void SetTexture(int stage, Texture texture);

	virtual VertexDeclaration CreateVertexDeclaration(VertexDeclElement* elements, unsigned int count, void* shader);
	virtual void SetVertexDeclaration(VertexDeclaration vertexDecl);
	virtual void DeleteVertexDeclaration(VertexDeclaration vertexDecl);

	virtual void IdentityTransform();
	virtual void TranslateTransform(float x, float y, float z);
	virtual void ScaleTransform(float sx, float sy, float sz);
	virtual void RotateTransform(float angleDegrees, float x, float y, float z);
	virtual void MultiplyTransform(const float m[16]);
	virtual void SetTransform(const float m[16]);

	virtual IndexBuffer CreateIndexBuffer(unsigned int type, unsigned int size, const void* data);
	virtual void IndexBufferSubData_(IndexBuffer buffer, unsigned int offset, unsigned int size, const void* data);
	virtual void VertexBufferSubData_(VertexBuffer buffer, unsigned int offset, unsigned int size, const void* data);

	virtual VertexBuffer CreateVertexBuffer(unsigned int size, const void* data, unsigned int bufferUsage);

	virtual void SetVertexBuffers(UINT start, UINT numBuffers, VertexBuffer* vertexBuffers, const UINT* strides, const UINT* byteOffsets);

	virtual Texture CreateTexture1D(int level, int internalformat, int width, int border, unsigned int format, unsigned int type, const void *pixels);
	virtual Texture CreateTexture2D(int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels);

	virtual IndexBuffer GetIndexBuffer(UINT* pOffsetInBytes);
	virtual void SetIndexBuffer(IndexBuffer indexBuffer, unsigned int offsetInBytes);

	virtual void SetVertexBuffer(UINT stream, VertexBuffer vertexBuffer, UINT byteOffset, UINT stride);

	virtual void SetMatrixMode(unsigned int mode);
	virtual void PushMatrix();	// TODO remove
	virtual void PopMatrix();	// TODO remove

	virtual void Enable(unsigned int cap);
	virtual void Disable(unsigned int cap);

	virtual void Clear(uint32 mask);
	virtual void DepthMask(bool mask);

	virtual void GetFloatv(unsigned int pname, float* params);

// CG
	virtual void cgBindProgram(CGprogram cgProgram);
	virtual void cgLoadProgram(CGprogram cgProgram);

public:

	int m_indexBufferFormat;

	ID3D10Device* m_device;
	ID3D10Device1* m_device1;
	ID3D11Device* m_device11;
	ID3D11DeviceContext* m_deviceContext;

	unsigned int m_matrixMode;
	gm::matrix4f m_modelviewMatrix;
	gm::matrix4f m_projectionMatrix;

	stack<gm::matrix4f> m_modelviewMatrixStack;	// TODO remove
	stack<gm::matrix4f> m_projectionMatrixStack;	// TODO remove

// TODO, not here

	void Load2();

	ID3DX10Effect* m_d3d10_effect;

	ID3DX10EffectTechnique* m_phongLightTechnique;
	ID3D10InputLayout* m_phongLightInputLayout;

	ID3DX10EffectTechnique* m_phongLightTexTechnique;
	ID3D10InputLayout* m_phongLightTexInputLayout;

	ID3DX10EffectTechnique* m_colorTexTechnique;
	ID3D10InputLayout* m_colorTexInputLayout;

	ID3DX10EffectTechnique* m_solidColorTechnique;
	ID3D10InputLayout* m_solidColorInputLayout;

	ID3DX10EffectVectorVariable* m_d3d10_viewPositionVariable;
	ID3DX10EffectMatrixVariable* m_d3d10_modelVariable;
	ID3DX10EffectMatrixVariable* m_d3d10_viewVariable;
	ID3DX10EffectMatrixVariable* m_d3d10_projectionVariable;
	ID3DX10EffectMatrixVariable* m_d3d10_modelViewVariable;
	ID3DX10EffectMatrixVariable* m_d3d10_modelViewProjectionVariable;
	ID3DX10EffectMatrixVariable* m_d3d10_modelViewITVariable;
	ID3DX10EffectMatrixVariable* m_d3d10_modelViewProjectionITVariable;

	ID3DX10EffectVariable* m_d3d10_materialVariable;

	ID3DX10EffectScalarVariable* m_d3d10_nlightsVariable;
	ID3DX10EffectVariable* m_d3d10_lightsVariable;

	ID3DX10EffectScalarVariable* m_d3d10_ntexturesVariable;
	ID3DX10EffectShaderResourceVariable* m_d3d10_texturesVariable;

	ID3DX10EffectShaderResourceVariable* m_d3d10_HeightMapTexture;

	ID3DX10EffectScalarVariable* m_d3d10_fogTypeVariable;
	ID3DX10EffectVectorVariable* m_d3d10_fogColorVariable;
	ID3DX10EffectScalarVariable* m_d3d10_fogDistanceSquaredVariable;

	// CG
//	CGcontext m_cgContext;

protected:

	CTOR Direct3D10_I();

	static Direct3D10_I* s_Current;
};

}	// Graphics
}	// System
