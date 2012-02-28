namespace System
{
namespace Graphics
{

struct GLProcs;

// NOTE: Not dllexport class because of d
class OpenGLContext
{
public:

	virtual GfxExt ~OpenGLContext()	// export this
	{
	}

	GfxExt void MakeCurrent();

	HDC m_hDC;                           // Device context
	HGLRC m_hRC;                         // Rendering context
	Graphics::GLProcs* m_glprocs;

	static __declspec(thread) OpenGLContext* s_current;
};

class GfxExt OpenGL_I : public GraphicsI, public OpenGLContext
{
public:
	CTOR OpenGL_I(HDC hDC, HGLRC hRC);
//	DrawExt CTOR OpenGL_I(HWND hWnd, WindowSurfDesc& desc);

	~OpenGL_I();

	virtual void Present();

	virtual void BeginDraw() override;
	virtual void EndDraw() override;

	virtual void Shutdown() override;
	virtual bool WindowResized();

	virtual IDirect3DDevice9* GetD3D9Device();
	virtual CGcontext GetCGContext();

	virtual int cgGetLatestProfile(unsigned int type);

	virtual void Viewport(int x, int y, int width, int height);
	virtual void SetClipPlane(int n, const float equation[4]);
	virtual void EnableClipPlanes(UINT mask);

	virtual void SetPrimitiveTopology(unsigned int primitiveTopology);
	virtual void Draw(/*unsigned int mode,*/ UINT first, UINT count);
	virtual void DrawIndexed(/*unsigned int mode,*/ int start, int end, UINT count/*, unsigned int type, int startIndex*/);
	virtual void DrawUP(/*unsigned int mode,*/ UINT count, void* data, int stride);

	virtual Texture CreateTexture1D(int level, int internalformat, int width, int border, unsigned int format, unsigned int type, const void *pixels);
	virtual Texture CreateTexture2D(int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels);

	virtual void SetTexture(int stage, Texture texture);

	virtual void SetMatrixMode(unsigned int mode);
	virtual void PushMatrix();
	virtual void PopMatrix();

	virtual void Enable(unsigned int cap);
	virtual void Disable(unsigned int cap);

	virtual void IdentityTransform();
	virtual void TranslateTransform(float x, float y, float z);
	virtual void ScaleTransform(float sx, float sy, float sz);
	virtual void RotateTransform(float angleDegrees, float x, float y, float z);
	virtual void MultiplyTransform(const float m[16]);
	virtual void SetTransform(const float m[16]);

	virtual IndexBuffer CreateIndexBuffer(unsigned int type, unsigned int size, const void* data);
	virtual void IndexBufferSubData_(IndexBuffer buffer, unsigned int offset, unsigned int size, const void* data);

	virtual VertexDeclaration CreateVertexDeclaration(VertexDeclElement* elements, unsigned int count, void* shader);
	virtual void SetVertexDeclaration(VertexDeclaration vertexDecl);
	virtual void DeleteVertexDeclaration(VertexDeclaration vertexDecl);

	virtual VertexBuffer CreateVertexBuffer(unsigned int size, const void* data, unsigned int bufferUsage);
	virtual void VertexBufferSubData_(VertexBuffer buffer, unsigned int offset, unsigned int size, const void* data);

	virtual IndexBuffer GetIndexBuffer(unsigned int* pOffsetInBytes);
	virtual void SetIndexBuffer(IndexBuffer indexBuffer, unsigned int offsetInBytes);

	virtual void SetVertexBuffer(UINT stream, VertexBuffer vertexBuffer, UINT byteOffset, UINT stride);

	virtual void Clear(uint32 mask);
	virtual void DepthMask(bool mask);

	virtual void GetFloatv(unsigned int pname, float* params);

// CG
	virtual void cgBindProgram(CGprogram cgProgram);
	virtual void cgLoadProgram(CGprogram cgProgram);

protected:

	void Init(HDC hDC, HGLRC hRC);

public:

	HWND m_hWnd;

	unsigned int m_primitiveTopology;
	unsigned int m_indexBufferOffsetInBytes;

	VertexDeclarationGL* m_vertexDeclaration;

	const char* m_glExtensions;
//	GLProcs* m_glprocs;

	int m_glMaxLights;
	int m_glMaxClipPlanes;
	int m_glMaxTextureUnits;
	int m_glMaxTextureCoords;
	int m_glMaxVertexAttribs;	// = 16; // ARB_vertex_shader

	int m_glMaxVertexUniformComponents;// = 512; // ARB_vertex_shader
	int m_glMaxVaryingFloats;// = 32; // ARB_vertex_shader
	int m_glMaxVertexTextureImageUnits;// = 0; // ARB_vertex_shader
	int m_glMaxCombinedTextureImageUnits;// = 2; // ARB_vertex_shader
	int m_glMaxTextureImageUnits;// = 2; // ARB_fragment_shader
	int m_glMaxFragmentUniformComponents;// = 64;// ARB_fragment_shader
	int m_glMaxDrawBuffers;// = 1; // proposed ARB_draw_buffers

	bool m_GL_ARB_multitexture : 1;
	bool m_GL_EXT_bgra : 1;
	bool m_GL_EXT_geometry_shader4 : 1;
	bool m_GL_EXT_draw_instanced : 1;
	bool m_GL_NV_geometry_program4 : 1;

	bool m_GL_ARB_framebuffer_object : 1;	// This instead of all below
	bool m_GL_EXT_framebuffer_object : 1;
	bool m_GL_EXT_framebuffer_blit : 1;
	bool m_GL_EXT_framebuffer_multisample : 1;
	bool m_GL_EXT_packed_depth_stencil : 1;

	bool m_depthMask;

	// CG
	CGcontext m_cgContext;
};

}	// Graphics
}	// System
