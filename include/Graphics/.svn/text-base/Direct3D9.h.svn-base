namespace System
{
namespace Graphics
{

class GfxExt Direct3D9_I : public GraphicsI
{
public:
	CTOR Direct3D9_I(IDirect3DDevice9* d3dDevice);

	virtual IDirect3DDevice9* GetD3D9Device();
	virtual CGcontext GetCGContext();
	virtual int cgGetLatestProfile(unsigned int type);

	virtual void Viewport(int x, int y, int width, int height);
	virtual void SetClipPlane(int n, const float equation[4]);
	virtual void EnableClipPlanes(UINT mask);

	virtual void SetPrimitiveTopology(unsigned int mode);
	virtual void Draw(UINT first, UINT count);
	virtual void DrawIndexed(int start, int end, UINT count/*, unsigned int type, int startIndex*/);
	virtual void DrawUP(UINT count, void* data, int stride);

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

	virtual VertexBuffer CreateVertexBuffer(unsigned int size, const void* data, unsigned int bufferUsage);
	virtual void VertexBufferSubData_(VertexBuffer buffer, unsigned int offset, unsigned int size, const void* data);

	virtual Texture CreateTexture1D(int level, int internalformat, int width, int border, unsigned int format, unsigned int type, const void *pixels);
	virtual Texture CreateTexture2D(int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels);

	virtual IndexBuffer GetIndexBuffer(unsigned int* pOffsetInBytes);
	virtual void SetIndexBuffer(IndexBuffer indexBuffer, unsigned int offsetInBytes);

	virtual void SetVertexBuffer(UINT stream, VertexBuffer vertexBuffer, UINT byteOffset, UINT stride);

	virtual void SetVertexBuffers(UINT start, UINT numBuffers, VertexBuffer* vertexBuffers, const UINT* strides, const UINT* byteOffsets);

	virtual void SetMatrixMode(unsigned int mode);
	virtual void PushMatrix();
	virtual void PopMatrix();

	virtual void Enable(unsigned int cap);
	virtual void Disable(unsigned int cap);

	virtual void Clear(uint32 mask);
	virtual void DepthMask(bool mask);

	virtual void GetFloatv(unsigned int pname, float* params);

// CG
	virtual void cgBindProgram(CGprogram cgProgram);
	virtual void cgLoadProgram(CGprogram cgProgram);

public:

	IDirect3DDevice9* m_d3dDevice;

	stack<gm::matrix4f> m_modelviewMatrixStack;
	stack<gm::matrix4f> m_projectionMatrixStack;

	unsigned int m_primitiveTopology;

//	unsigned int m_primitiveType;
	unsigned int m_startIndex;
	unsigned int m_matrixMode;

	// CG
	CGcontext m_cgContext;
};

}	// Graphics
}	// System
