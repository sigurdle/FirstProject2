#include "StdAfx.h"
#include "Graphics.h"
//#include "gl.h"

//#include <windows.h>

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include "openglext.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <Cg/cgD3D9.h>

namespace System
{
namespace Graphics
{

GLProcs::GLProcs()
{
/*
The OpenGL library supports multiple implementations of its functions. Extension functions supported in one rendering context
are not necessarily available in a separate rendering context. Thus, for a given rendering context in an application, use the
function addresses returned by the wglGetProcAddress function only. 
*/

//	memset(m_glprocs, 0, sizeof(GLProcs));

	// WGL_NV_dx_interop
	/*
	wglDXOpenDeviceNV = (PFNWGLDXOPENDEVICENVPROC)wglGetProcAddress("wglDXOpenDeviceNV");
	wglDXCloseDeviceNV = (PFNWGLDXCLOSEDEVICENVPROC)wglGetProcAddress("wglDXCloseDeviceNV");

	wglDXSetResourceShareHandleNV = (PFNWGLDXSETRESOURCESHAREHANDLENVPROC)wglGetProcAddress("wglDXSetResourceShareHandleNV");
	wglDXRegisterObjectNV = (PFNWGLDXREGISTEROBJECTNVPROC)wglGetProcAddress("wglDXRegisterObjectNV");

	wglDXLockObjectsNV = (PFNWGLDXLOCKOBJECTSNVPROC)wglGetProcAddress("wglDXLockObjectsNV");
	wglDXUnlockObjectsNV = (PFNWGLDXUNLOCKOBJECTSNVPROC)wglGetProcAddress("wglDXUnlockObjectsNV");
	*/

	// WGL_NVX_dx_interop
	wglDXOpenDeviceNVX = (PFNWGLDXOPENDEVICENVXPROC)wglGetProcAddress("wglDXOpenDeviceNVX");
	wglDXCloseDeviceNVX = (PFNWGLDXCLOSEDEVICENVXPROC)wglGetProcAddress("wglDXCloseDeviceNVX");

	wglDXSetResourceShareHandleNVX = (PFNWGLDXSETRESOURCESHAREHANDLENVXPROC)wglGetProcAddress("wglDXSetResourceShareHandleNVX");

	wglDXRegisterObjectNVX = (PFNWGLDXREGISTEROBJECTNVXPROC)wglGetProcAddress("wglDXRegisterObjectNVX");
	wglDXUnregisterObjectNVX = (PFNWGLDXUNREGISTEROBJECTNVXPROC)wglGetProcAddress("wglDXUnregisterObjectNVX");

	wglDXLockObjectsNVX = (PFNWGLDXLOCKOBJECTSNVXPROC)wglGetProcAddress("wglDXLockObjectsNVX");
	wglDXUnlockObjectsNVX = (PFNWGLDXUNLOCKOBJECTSNVXPROC)wglGetProcAddress("wglDXUnlockObjectsNVX");

	// OpenGL 1.2
	glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)wglGetProcAddress("glDrawRangeElements");

	// OpenGL 1.3
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)wglGetProcAddress("glClientActiveTexture");

	glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)wglGetProcAddress("glMultiTexCoord1f");
	glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)wglGetProcAddress("glMultiTexCoord2f");
	glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)wglGetProcAddress("glMultiTexCoord3f");
	glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)wglGetProcAddress("glMultiTexCoord4f");

	// OpenGL 1.4
	glFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC)wglGetProcAddress("glFogCoordPointer");
	glSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC)wglGetProcAddress("glSecondaryColorPointer");

	// OpenGL 1.5
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");

	// OpenGL 2.0
	glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)wglGetProcAddress("glStencilOpSeparate");

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");

	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
	glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
	glUniform2i = (PFNGLUNIFORM2IPROC)wglGetProcAddress("glUniform2i");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");
	glUniform3i = (PFNGLUNIFORM3IPROC)wglGetProcAddress("glUniform3i");
	glUniform3iv = (PFNGLUNIFORM3IVPROC)wglGetProcAddress("glUniform3iv");
	glUniform4i = (PFNGLUNIFORM4IPROC)wglGetProcAddress("glUniform4i");
	glUniform4iv = (PFNGLUNIFORM4IVPROC)wglGetProcAddress("glUniform4iv");

	glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)wglGetProcAddress("glUniformMatrix2fv");
	glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)wglGetProcAddress("glUniformMatrix3fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");

	glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)wglGetProcAddress("glVertexAttrib1f");
	glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)wglGetProcAddress("glVertexAttrib1fv");
	glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)wglGetProcAddress("glVertexAttrib2f");
	glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)wglGetProcAddress("glVertexAttrib2fv");
	glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)wglGetProcAddress("glVertexAttrib3f");
	glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)wglGetProcAddress("glVertexAttrib3fv");
	glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)wglGetProcAddress("glVertexAttrib4f");
	glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)wglGetProcAddress("glVertexAttrib4fv");

	// 3.0

	glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");;
	glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
	glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
	glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");

	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");;
	glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeletebrameBuffers");;
	glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)wglGetProcAddress("glIsFramebuffer");
	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
	glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");

	glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)wglGetProcAddress("glFramebufferTexture1D");
	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
	glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3D");

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
}

__declspec(thread) OpenGLContext* OpenGLContext::s_current;

void OpenGLContext::MakeCurrent()
{
	if (s_current != this)
	{
		s_current = this;
		wglMakeCurrent(m_hDC, m_hRC);
	}
}

void SetupPixelFormat(HDC hDC)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),   // size of structure.
		1,                               // always 1.

		PFD_DRAW_TO_WINDOW |             // support window
		PFD_SUPPORT_OPENGL |             // support OpenGl
		PFD_DOUBLEBUFFER,                // support double buffering

		PFD_TYPE_RGBA,                   // support RGBA
		24,                              // bit color mode
		0, 0, 0, 0, 0, 0,                // ignore color bits
		0,                               // no alpha buffer
		0,                               // ignore shift bit
		0,                               // no accumulation buffer
		0, 0, 0, 0,                      // ignore accumulation bits.
		16,                              // number of depth buffer bits.
		0,                               // number of stencil buffer bits.
		0,                               // 0 means no auxiliary buffer
		PFD_MAIN_PLANE,                  // The main drawing plane
		0,                               // this is reserved
		0, 0, 0                       // layer masks ignored.
	};
	
	int nPixelFormat;
	// This chooses the best pixel format and returns index.
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// This set pixel format to device context.
	SetPixelFormat(hDC, nPixelFormat, &pfd);

	// Get the full description of this pixel format
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
}

OpenGL_I::OpenGL_I(HDC hDC, HGLRC hRC)
{
	m_vertexDeclaration = NULL;

	Init(hDC, hRC);
}

#if 0
OpenGL_I::OpenGL_I(HWND hWnd, WindowSurfDesc& desc)
{
	m_hWnd = hWnd;
	m_hDC = ::GetDC(hWnd);				// This gets the device context for our window
	SetupPixelFormat(m_hDC);			// Call the pixel format function

	m_hRC = wglCreateContext(m_hDC);	// Creates the rendering context
	if (m_hRC == NULL)
	{
		ASSERT(0);
		//throw std::exception("Couldn't create OpenGL context");
	}

	Init(m_hDC, m_hRC);

	if (true)	// Here, or in another method?
	{
		RECT clientRect;
		GetClientRect(m_hWnd, &clientRect);

		int clientWidth = clientRect.right;
		int clientHeight = clientRect.bottom;

		if (clientHeight == 0) clientHeight = 1;

		MakeCurrent();
		glViewport(0, 0, clientWidth, clientHeight); // resets the viewport to new dimensions.
	}
}
#endif

OpenGL_I::~OpenGL_I()
{
}

void OpenGL_I::Init(HDC hDC, HGLRC hRC)
{
	if (hDC == NULL) raise(ArgumentNullException());
	if (hRC == NULL) raise(ArgumentNullException());

	m_hDC = hDC;
	m_hRC = hRC;

	MakeCurrent();

	m_glExtensions = (const char*)::glGetString(GL_EXTENSIONS);
	ASSERT(::glGetError() == 0);

	m_GL_ARB_multitexture = strstr(m_glExtensions, "GL_ARB_multitexture") != NULL;
	m_GL_EXT_bgra = strstr(m_glExtensions, "GL_EXT_bgra") != NULL;
	m_GL_EXT_geometry_shader4 = strstr(m_glExtensions, "GL_EXT_geometry_shader4") != NULL;
	m_GL_EXT_draw_instanced = strstr(m_glExtensions, "GL_EXT_draw_instanced") != NULL;

	m_GL_ARB_framebuffer_object = strstr(m_glExtensions, "GL_ARB_framebuffer_object") != NULL;
	m_GL_EXT_framebuffer_object = strstr(m_glExtensions, "GL_EXT_framebuffer_object") != NULL;
	m_GL_EXT_framebuffer_blit = strstr(m_glExtensions, "GL_EXT_framebuffer_blit") != NULL;
	m_GL_EXT_framebuffer_multisample = strstr(m_glExtensions, "GL_EXT_framebuffer_multisample") != NULL;

	::glGetIntegerv(GL_MAX_LIGHTS, &m_glMaxLights);
	ASSERT(::glGetError() == 0);
	ASSERT(m_glMaxLights >= 8);

	::glGetIntegerv(GL_MAX_CLIP_PLANES, &m_glMaxClipPlanes);
	ASSERT(::glGetError() == 0);
	ASSERT(m_glMaxClipPlanes >= 6);

	::glGetIntegerv(GL_MAX_TEXTURE_COORDS, &m_glMaxTextureCoords);
	ASSERT(::glGetError() == 0);

	::glGetIntegerv(GL_MAX_TEXTURE_UNITS, &m_glMaxTextureUnits);
	ASSERT(::glGetError() == 0);

	::glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &m_glMaxVertexAttribs);
	ASSERT(::glGetError() == 0);

	::glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &m_glMaxVertexUniformComponents);
	ASSERT(::glGetError() == 0);

	::glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_glMaxTextureImageUnits);
	ASSERT(::glGetError() == 0);

	::glGetIntegerv(GL_MAX_VARYING_FLOATS, &m_glMaxVaryingFloats);
	ASSERT(::glGetError() == 0);

	::glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &m_glMaxVertexTextureImageUnits);
	ASSERT(::glGetError() == 0);

	::glGetIntegerv(GL_MAX_DRAW_BUFFERS, &m_glMaxDrawBuffers);
	ASSERT(::glGetError() == 0);

	m_glprocs = new GLProcs;

	// TODO
	// framebuffer_object

	// CG
	if (false)
	{
		m_cgContext = cgCreateContext();
		ASSERT(cgGetError() == 0);

		/*
		// ??
		::cgGLEnableProfile(CG_PROFILE_ARBVP1);
		ASSERT(cgGetError() == 0);
		::cgGLEnableProfile(CG_PROFILE_ARBFP1);
		ASSERT(cgGetError() == 0);
		*/
	}

	return;
}

bool OpenGL_I::WindowResized()
{
	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);

	int clientWidth = clientRect.right;
	int clientHeight = clientRect.bottom;

	if (clientHeight == 0) clientHeight = 1;

	MakeCurrent();
	glViewport(0, 0, clientWidth, clientHeight); // resets the viewport to new dimensions.

	return true;
}

void OpenGL_I::Shutdown()
{
	if (m_hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hRC);
	}

	if (m_hWnd && m_hDC)
	{
		ReleaseDC(m_hWnd, m_hDC);
	}
}

void OpenGL_I::BeginDraw()
{
	// Do nothing
}

void OpenGL_I::EndDraw()
{
	// Do nothing
}

void OpenGL_I::Present()
{
	::SwapBuffers(m_hDC);
}

IDirect3DDevice9* OpenGL_I::GetD3D9Device()
{
	return NULL;
}

CGcontext OpenGL_I::GetCGContext()
{
	return m_cgContext;
}

int OpenGL_I::cgGetLatestProfile(unsigned int type)
{
	return cgGLGetLatestProfile((CGGLenum)type);
}

void OpenGL_I::DeleteVertexDeclaration(VertexDeclaration decl)
{
	if (decl.u.gl)
	{
		decl.u.gl->Release();
	}
}

void OpenGL_I::Enable(GLenum cap)
{
	MakeCurrent();

	::glEnable(cap);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::Disable(GLenum cap)
{
	MakeCurrent();

	::glDisable(cap);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::Clear(uint32 mask)
{
	MakeCurrent();

	if (!m_depthMask)
	{
		::glDepthMask(true);
		ASSERT(::glGetError() == 0);
	}

	::glClear(mask);
	ASSERT(::glGetError() == 0);

	if (!m_depthMask)
	{
		::glDepthMask(false);
		ASSERT(::glGetError() == 0);
	}
}

void OpenGL_I::Viewport(int x, int y, int width, int height)
{
	MakeCurrent();

	::glViewport(x, y, width, height);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::SetClipPlane(int n, const float equation[4])
{
	VERIFY(0);
}

void OpenGL_I::EnableClipPlanes(UINT mask)
{
	VERIFY(0);
}

void OpenGL_I::DepthMask(bool mask)
{
	MakeCurrent();

	m_depthMask = mask;

	::glDepthMask(mask);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::GetFloatv(GLenum pname, GLfloat* params)
{
	MakeCurrent();

	::glGetFloatv(pname, params);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::SetMatrixMode(GLenum mode)
{
	MakeCurrent();

	::glMatrixMode(mode);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::PushMatrix()
{
	MakeCurrent();

//	glMatrixMode(m_matrixMode);
//	ASSERT(glGetError() == 0);

	::glPushMatrix();
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::PopMatrix()
{
	MakeCurrent();

//	glMatrixMode(m_matrixMode);
//	ASSERT(glGetError() == 0);

	::glPopMatrix();
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::IdentityTransform()
{
	MakeCurrent();

	::glLoadIdentity();
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::TranslateTransform(float x, float y, float z)
{
	MakeCurrent();

	::glTranslatef(x, y, z);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::ScaleTransform(float sx, float sy, float sz)
{
	MakeCurrent();

	::glScalef(sx, sy, sz);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::RotateTransform(float angle, float x, float y, float z)
{
	MakeCurrent();

	::glRotatef(angle, x, y, z);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::SetTransform(const float m[16])
{
	MakeCurrent();

	::glLoadMatrixf(m);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::MultiplyTransform(const float m[16])
{
	MakeCurrent();

	::glMultMatrixf(m);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::DrawUP(UINT count, void* data, int stride)
{
//	m_glprocs->glBindBuffer(GL_ARRAY_BUFFER, 0);
	//ASSERT(::glGetError() == 0);

	unsigned int mode = m_primitiveTopology;

	for (unsigned int i = 0; i < m_vertexDeclaration->m_count; i++)
	{
		D3DVERTEXELEMENT9* element = &m_vertexDeclaration->m_elements[i];

		if (element->Stream == 0)	// Only stream 0
		{
			int size;
			int datatype;

			switch (element->Type)
			{
			case D3DDECLTYPE_FLOAT1:
				size = 1;
				datatype = GL_FLOAT;
				break;

			case D3DDECLTYPE_FLOAT2:
				size = 2;
				datatype = GL_FLOAT;
				break;

			case D3DDECLTYPE_FLOAT3:
				size = 3;
				datatype = GL_FLOAT;
				break;

			case D3DDECLTYPE_FLOAT4:
				size = 4;
				datatype = GL_FLOAT;
				break;

			case D3DDECLTYPE_D3DCOLOR:
				size = 4;
				datatype = GL_UNSIGNED_BYTE;
				break;

			default:
				VERIFY(0);
			}

			if (true)
			{
				CGparameter param = (CGparameter)element->Usage;
			//	::cgGLEnableClientState(param);
				::cgGLSetParameterPointer(param, size, datatype, stride, (uint8*)data + element->Offset);
				ASSERT(::cgGetError() == 0);
			}
			else
			{
				switch (element->Usage)
				{
				case D3DDECLUSAGE_POSITION:
					{
						::glVertexPointer(size, datatype, stride, (void*)(element->Offset));
						ASSERT(::glGetError() == 0);
					}
					break;

				case D3DDECLUSAGE_NORMAL:
					{
						::glNormalPointer(datatype, stride, (void*)(element->Offset));
						ASSERT(::glGetError() == 0);
					}
					break;

				case D3DDECLUSAGE_COLOR:
					{
						::glColorPointer(size, datatype, stride, (void*)(element->Offset));
						ASSERT(::glGetError() == 0);
					}
					break;

				case D3DDECLUSAGE_TEXCOORD:
					{
						m_glprocs->glClientActiveTexture(GL_TEXTURE0 + element->UsageIndex);
						ASSERT(::glGetError() == 0);

						::glTexCoordPointer(size, datatype, stride, (void*)(element->Offset));
						ASSERT(::glGetError() == 0);
					}
					break;

				case 255:
				//default:
					{
						bool normalized = false;	// ??
						m_glprocs->glVertexAttribPointer(element->UsageIndex, size, datatype, normalized, stride, (void*)(element->Offset));
						ASSERT(::glGetError() == 0);
					}
					break;

				default:
					VERIFY(0);
				}
			}
		}
	}

	int error = ::glGetError();
	ASSERT(error == 0);

	::glDrawArrays(mode, 0, count);
	error = ::glGetError();
	ASSERT(error == 0);
}

void OpenGL_I::SetVertexBuffer(UINT stream, VertexBuffer vertexBuffer, UINT offsetInBytes, UINT stride)
{
	MakeCurrent();

	for (unsigned int i = 0; i < m_vertexDeclaration->m_count; i++)
	{
		D3DVERTEXELEMENT9* element = &m_vertexDeclaration->m_elements[i];

		if (element->Stream == stream)
		{
			int size;
			int datatype;

			switch (element->Type)
			{
			case D3DDECLTYPE_FLOAT1:
				size = 1;
				datatype = GL_FLOAT;
				break;

			case D3DDECLTYPE_FLOAT2:
				size = 2;
				datatype = GL_FLOAT;
				break;

			case D3DDECLTYPE_FLOAT3:
				size = 3;
				datatype = GL_FLOAT;
				break;

			case D3DDECLTYPE_FLOAT4:
				size = 4;
				datatype = GL_FLOAT;
				break;

			case D3DDECLTYPE_D3DCOLOR:
				size = 4;
				datatype = GL_UNSIGNED_BYTE;
				break;

			default:
				VERIFY(0);
			}

			m_glprocs->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.u.n);
			ASSERT(::glGetError() == 0);

			switch (element->Usage)
			{
			case D3DDECLUSAGE_POSITION:
				{
					::glVertexPointer(size, datatype, stride, (void*)(offsetInBytes + element->Offset));
					ASSERT(::glGetError() == 0);
				}
				break;

			case D3DDECLUSAGE_NORMAL:
				{
					::glNormalPointer(datatype, stride, (void*)(offsetInBytes + element->Offset));
					ASSERT(::glGetError() == 0);
				}
				break;

			case D3DDECLUSAGE_COLOR:
				{
					::glColorPointer(size, datatype, stride, (void*)(offsetInBytes + element->Offset));
					ASSERT(::glGetError() == 0);
				}
				break;

			case D3DDECLUSAGE_TEXCOORD:
				{
					m_glprocs->glClientActiveTexture(GL_TEXTURE0 + element->UsageIndex);
					ASSERT(::glGetError() == 0);

					::glTexCoordPointer(size, datatype, stride, (void*)(offsetInBytes + element->Offset));
					ASSERT(::glGetError() == 0);
				}
				break;

			case 255:
			//default:
				{
					bool normalized = false;	// ??
					m_glprocs->glVertexAttribPointer(element->UsageIndex, size, datatype, normalized, stride, (void*)(offsetInBytes + element->Offset));
					ASSERT(::glGetError() == 0);
				}
				break;

			default:
				VERIFY(0);
			}
		}
	}
}

IndexBuffer OpenGL_I::GetIndexBuffer(UINT* pOffsetInBytes)
{
	MakeCurrent();

	if (*pOffsetInBytes)
		*pOffsetInBytes = m_indexBufferOffsetInBytes;

	VERIFY(0);
	return IndexBuffer();
}

void OpenGL_I::SetIndexBuffer(IndexBuffer indexBuffer, UINT offsetInBytes)
{
	MakeCurrent();

	m_glprocs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.u.n);
	ASSERT(glGetError() == 0);

	m_indexBufferOffsetInBytes = offsetInBytes;
}

Texture OpenGL_I::CreateTexture1D(GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels)
{
	VERIFY(0);
	return Texture();
}

Texture OpenGL_I::CreateTexture2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
{
	MakeCurrent();

	unsigned int nTexture;
	glGenTextures(1, &nTexture);
	ASSERT(glGetError() == 0);

	glBindTexture(GL_TEXTURE_2D, nTexture);
	ASSERT(glGetError() == 0);

	glTexImage2D(GL_TEXTURE_2D, level, internalformat, width, height, border, format, type, pixels);
	ASSERT(glGetError() == 0);

	return Texture(this, nTexture, GL_TEXTURE_2D);
}

void OpenGL_I::SetTexture(int stage, Texture texture)
{
	m_glprocs->glActiveTexture(GL_TEXTURE0 + stage);
	::glBindTexture(GL_TEXTURE_2D, texture.u.n);
	ASSERT(::glGetError() == 0);
	//	glEnable(GL_TEXTURE_2D);
}

VertexBuffer OpenGL_I::CreateVertexBuffer(unsigned int size, const void* data, unsigned int bufferUsage)
{
	MakeCurrent();

	/*
	if (m_cgContext)
	{
		CGbuffer buffer = cgGLCreateBuffer(m_cgContext, size, data, bufferUsage);
		return VertexBuffer(buffer);
	}
	else
	*/
	{
	//	int usage = GL_STATIC_DRAW;	// TODO

		unsigned int nBuffer;
		m_glprocs->glGenBuffers(1, &nBuffer);
		int error = ::glGetError();
		ASSERT(error == 0);

		m_glprocs->glBindBuffer(GL_ARRAY_BUFFER, nBuffer);
		ASSERT(::glGetError() == 0);

		m_glprocs->glBufferData(GL_ARRAY_BUFFER, size, data, bufferUsage);
		ASSERT(::glGetError() == 0);

		return VertexBuffer(nBuffer);
	}
}

void OpenGL_I::VertexBufferSubData_(VertexBuffer buffer, unsigned int offset, unsigned int size, const void* data)
{
	MakeCurrent();
	m_glprocs->glBufferSubData(buffer.u.n, offset, size, data);
}

IndexBuffer OpenGL_I::CreateIndexBuffer(unsigned int type, unsigned int size, const void* data)
{
	// We only support these to be compatible with D3D
	if (type != GL_UNSIGNED_SHORT && type != GL_UNSIGNED_INT)
	{
		raise(Exception("Invalid type"));
	}

	MakeCurrent();

	int usage = GL_STATIC_DRAW;	// TODO

	unsigned int nBuffer;
	m_glprocs->glGenBuffers(1, &nBuffer);
	ASSERT(::glGetError() == 0);

	m_glprocs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nBuffer);
	ASSERT(::glGetError() == 0);

	m_glprocs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	ASSERT(::glGetError() == 0);

	return IndexBuffer(nBuffer, type);
}

void OpenGL_I::IndexBufferSubData_(IndexBuffer buffer, unsigned int offset, unsigned int size, const void* data)
{
	MakeCurrent();
	m_glprocs->glBufferSubData(buffer.u.n, offset, size, data);
}

VertexDeclaration OpenGL_I::CreateVertexDeclaration(VertexDeclElement* elements, unsigned int count, void* shader)
{
	if (count > 64)
	{
		raise(Exception("Too many vertex declaration elements"));
	}

	VertexDeclarationGL* vertexDeclaration = new VertexDeclarationGL;
	vertexDeclaration->AddRef();
	vertexDeclaration->m_elements = new D3DVERTEXELEMENT9[count+1];
	vertexDeclaration->m_count = count;

	D3DVERTEXELEMENT9* dwDecl = vertexDeclaration->m_elements;

	uint index = 0;

	for (uint i = 0; i < count; ++i)
	{
		dwDecl[index].Stream = elements[i].stream;
		dwDecl[index].Offset = elements[i].offset;
		dwDecl[index].Method = D3DDECLMETHOD_DEFAULT;
		dwDecl[index].UsageIndex = elements[i].usageIndex;

		switch (elements[i].type)
		{
		case DECLTYPE_FLOAT1:	dwDecl[index].Type = D3DDECLTYPE_FLOAT1;	break;
		case DECLTYPE_FLOAT2:	dwDecl[index].Type = D3DDECLTYPE_FLOAT2;	break;
		case DECLTYPE_FLOAT3:	dwDecl[index].Type = D3DDECLTYPE_FLOAT3;	break;
		case DECLTYPE_FLOAT4:	dwDecl[index].Type = D3DDECLTYPE_FLOAT4;	break;
		default:
			throw std::exception("Invalid vertex declaration element type");
		}

		if (false)
		{
			CGprogram program = (CGprogram)shader;

			CGparameter param = cgGetNamedParameter(program, elements[i].usage);
			ASSERT(param);

			dwDecl[index].Usage = (int)param;
		}
		else
		{

			if (strcmp(elements[i].usage, "POSITION") == 0)
			{
				dwDecl[index].Usage = D3DDECLUSAGE_POSITION;
			}
			else if (strcmp(elements[i].usage, "NORMAL") == 0)
			{
				dwDecl[index].Usage = D3DDECLUSAGE_NORMAL;
			}
			else if (strcmp(elements[i].usage, "COLOR") == 0)
			{
				dwDecl[index].Usage = D3DDECLUSAGE_COLOR;
			}
			else if (strcmp(elements[i].usage, "TEXCOORD") == 0)
			{
				dwDecl[index].Usage = D3DDECLUSAGE_TEXCOORD;
			}
			else
			{
			//	throw std::exception("Invalid vertex declaration element usage");

				dwDecl[index].Usage = (_D3DDECLUSAGE)255;
			}
		}

		++index;
	}

	// End
	dwDecl[index].Stream = 0xFF;
	dwDecl[index].Offset = 0;
	dwDecl[index].Type = D3DDECLTYPE_UNUSED;
	dwDecl[index].Method = 0;
	dwDecl[index].Usage = 0;
	dwDecl[index].UsageIndex = 0;

	return VertexDeclaration(vertexDeclaration);
}

void OpenGL_I::Draw(/*GLenum mode,*/ UINT first, UINT count)
{
	MakeCurrent();

	unsigned int mode = m_primitiveTopology;

	::glDrawArrays(mode, first, count);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::DrawIndexed(/*GLenum mode,*/ int start, int end, UINT count/*, GLenum type, int startIndex*/)
{
	MakeCurrent();

	unsigned int mode = m_primitiveTopology;

	//int indexSize = (type == GL_UNSIGNED_SHORT)? 1: 2;
	//int indicesOffsetInBytes = startIndex << indexSize;
//	unsigned int type = GL_UNSIGNED_SHORT;	// TODO
	unsigned int type = GL_UNSIGNED_INT;	// TODO

	m_glprocs->glDrawRangeElements(mode, start, end, count, type, (void*)m_indexBufferOffsetInBytes);
	ASSERT(::glGetError() == 0);
}

void OpenGL_I::SetPrimitiveTopology(unsigned int primitiveTopology)
{
	m_primitiveTopology = primitiveTopology;
}

void OpenGL_I::SetVertexDeclaration(VertexDeclaration decl)
{
	MakeCurrent();

	m_vertexDeclaration = decl.u.gl;

	::glDisableClientState(GL_VERTEX_ARRAY);
	ASSERT(::glGetError() == 0);

	::glDisableClientState(GL_NORMAL_ARRAY);
	ASSERT(::glGetError() == 0);

	::glDisableClientState(GL_COLOR_ARRAY);
	ASSERT(::glGetError() == 0);

	for (int i = 0; i < 8; ++i)
	{
		m_glprocs->glClientActiveTexture(GL_TEXTURE0+i);
		ASSERT(glGetError() == 0);

		::glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		ASSERT(::glGetError() == 0);
	}

	for (int i = 0; i < 8; ++i)
	{
		m_glprocs->glDisableVertexAttribArray(i);
		ASSERT(::glGetError() == 0);
	}

	for (unsigned int i = 0; i < m_vertexDeclaration->m_count; ++i)
	{
		D3DVERTEXELEMENT9* element = &m_vertexDeclaration->m_elements[i];

		/*
		int size;
		int datatype;
		switch (element->Type)
		{
		case D3DDECLTYPE_FLOAT1:
			size = 1;
			datatype = GL_FLOAT;
			break;

		case D3DDECLTYPE_FLOAT2:
			size = 2;
			datatype = GL_FLOAT;
			break;

		case D3DDECLTYPE_FLOAT3:
			size = 3;
			datatype = GL_FLOAT;
			break;

		case D3DDECLTYPE_FLOAT4:
			size = 4;
			datatype = GL_FLOAT;
			break;

		case D3DDECLTYPE_D3DCOLOR:
			size = 4;
			datatype = GL_UNSIGNED_BYTE;
			break;

		default:
			VERIFY(0);
		}
		*/

		if (false)
		{
			CGparameter param = (CGparameter)element->Usage;
			::cgGLEnableClientState(param);
		}
		else
		{
			switch (element->Usage)
			{
			case D3DDECLUSAGE_POSITION:
				{
					glEnableClientState(GL_VERTEX_ARRAY);
					ASSERT(glGetError() == 0);
				}
				break;

			case D3DDECLUSAGE_NORMAL:
				{
					glEnableClientState(GL_NORMAL_ARRAY);
					ASSERT(glGetError() == 0);
				}
				break;

			case D3DDECLUSAGE_COLOR:
				{
					glEnableClientState(GL_COLOR_ARRAY);
					ASSERT(glGetError() == 0);
				}
				break;

			case D3DDECLUSAGE_TEXCOORD:
				{
					m_glprocs->glClientActiveTexture(GL_TEXTURE0 + element->UsageIndex);
					ASSERT(glGetError() == 0);

					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					ASSERT(glGetError() == 0);
				}
				break;

			case 255:
				{
					m_glprocs->glEnableVertexAttribArray(element->UsageIndex);
					ASSERT(::glGetError() == 0);
				}
				break;

			default:
				ASSERT(0);
			}
		}
	}

//		for (int i = 0; i 
//		glEnableClientState(GL_TEXCOORD_ARRAY);
//		glEnableClientState(GL_COLOR_ARRAY);
//					glEnableClientState(GL_NORMAL_ARRAY);
//				glEnableClientState(GL_VERTEX_ARRAY);

}

void OpenGL_I::cgBindProgram(CGprogram cgProgram)
{
	MakeCurrent();

	::cgGLEnableProfile(::cgGetProgramProfile(cgProgram));
	ASSERT(::cgGetError() == 0);

	::cgGLBindProgram(cgProgram);
	ASSERT(::cgGetError() == 0);
}

void OpenGL_I::cgLoadProgram(CGprogram cgProgram)
{
	MakeCurrent();

	::cgGLLoadProgram(cgProgram);
	ASSERT(::cgGetError() == 0);
}

}	// LDraw
}
