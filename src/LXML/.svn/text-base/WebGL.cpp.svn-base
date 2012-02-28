#include "stdafx.h"
#include "LXML2.h"

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include "Graphics/openglext.h"

#ifndef GL_INVALID_FRAMEBUFFER_OPERATION
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x506
#endif

// OpenGL
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

namespace System
{
namespace Web
{

WebGLBuffer::~WebGLBuffer()
{
	m_context->MakeCurrent();
	m_context->m_glprocs->glDeleteBuffers(1, &m_nbuffer);
}

WebGLFramebuffer::~WebGLFramebuffer()
{
	m_context->MakeCurrent();
	m_context->m_glprocs->glDeleteFramebuffers(1, &m_nbuffer);
}

WebGLRenderbuffer::~WebGLRenderbuffer()
{
	m_context->MakeCurrent();
	m_context->m_glprocs->glDeleteRenderbuffers(1, &m_nbuffer);
}

WebGLShader::~WebGLShader()
{
	m_context->MakeCurrent();
	m_context->m_glprocs->glDeleteShader(m_nbuffer);
}

WebGLProgram::~WebGLProgram()
{
	m_context->MakeCurrent();
	m_context->m_glprocs->glDeleteProgram(m_nbuffer);
}

WebGLTexture::~WebGLTexture()
{
	m_context->MakeCurrent();
	glDeleteTextures(1, &m_nbuffer);
}

//////////////////////////////////////////////////////
// WebGLRenderingContext

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
		0,//16,                              // number of depth buffer bits.
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

HANDLE gl_handleD3D;
HANDLE gl_handles[2];

WebGLRenderingContext::WebGLRenderingContext(Graphics::Bitmap* bitmap) : m_bitmap(bitmap)
{
	if (bitmap == NULL)
	{
		raise(ArgumentNullException());
	}

	HWindow* win = new HWindow();
	win->CreateHidden();

	HWND m_hWnd = win->get_Hwnd();
	m_hDC = ::GetDC(m_hWnd);				// This gets the device context for our window
	SetupPixelFormat(m_hDC);			// Call the pixel format function

	m_hRC = wglCreateContext(m_hDC);	// Creates the rendering context
	if (m_hRC == NULL)
	{
		ASSERT(0);
		//throw std::exception("Couldn't create OpenGL context");
	}

	MakeCurrent();

	const char* m_glExtensions = (const char*)::glGetString(GL_EXTENSIONS);

//	Init(m_hDC, m_hRC);

	m_glprocs = new Graphics::GLProcs();

	ComPtr<IDirect3DDevice9> device;
	bitmap->m_d3d9_texture->GetDevice(&device);

	gl_handleD3D = m_glprocs->wglDXOpenDeviceNVX(device);
	if (gl_handleD3D == NULL)
	{
		raise(Exception());
	}

	GLuint gl_names[2];

	::BOOL success = m_glprocs->wglDXSetResourceShareHandleNVX(bitmap->m_d3d9_texture, bitmap->m_shared);
	ASSERT(success);

	glGenTextures(1, gl_names);

	gl_handles[0] = m_glprocs->wglDXRegisterObjectNVX(gl_handleD3D, bitmap->m_d3d9_texture,
											gl_names[0],
											GL_TEXTURE_2D,
											WGL_ACCESS_READ_WRITE_NVX);


	glBindTexture(GL_TEXTURE_2D, gl_names[0]);
	ASSERT(glGetError() == 0);

	//no filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	ASSERT(glGetError() == 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	ASSERT(glGetError() == 0);

	m_glprocs->glGenerateMipmap(GL_TEXTURE_2D);
	ASSERT(glGetError() == 0);

	uint fbo;
	m_glprocs->glGenFramebuffers(1, &fbo);

// attach the Direct3D buffers to an FBO
	m_glprocs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	ASSERT(glGetError() == 0);

	m_glprocs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gl_names[0], 0);
	ASSERT(glGetError() == 0);

	GLenum status = m_glprocs->glCheckFramebufferStatus(GL_FRAMEBUFFER);

	ASSERT(status == GL_FRAMEBUFFER_COMPLETE);

	//    <opengl renders to the render targets>
}

WebGLRenderingContext::WebGLRenderingContext(uint width, uint height)
{
	Graphics::D3D10Texture2D tex(Graphics::Direct10::get_D3DDevice(), width, height, DXGI_FORMAT_R8G8B8A8_UNORM, D3D10_USAGE_DEFAULT); 
	m_bitmap = new Graphics::Bitmap(Graphics::Direct10::get_D3DDevice(), tex);

	HWindow* win = new HWindow();
	win->CreateHidden();

	HWND m_hWnd = win->get_Hwnd();
	m_hDC = ::GetDC(m_hWnd);				// This gets the device context for our window
	SetupPixelFormat(m_hDC);			// Call the pixel format function

	m_hRC = wglCreateContext(m_hDC);	// Creates the rendering context
	if (m_hRC == NULL)
	{
		ASSERT(0);
		//throw std::exception("Couldn't create OpenGL context");
	}

	MakeCurrent();

	const char* m_glExtensions = (const char*)::glGetString(GL_EXTENSIONS);

//	Init(m_hDC, m_hRC);

	m_glprocs = new Graphics::GLProcs();

	GLuint gl_names[1];

	glGenTextures(1, gl_names);

	glBindTexture(GL_TEXTURE_2D, gl_names[0]);
	ASSERT(glGetError() == 0);

	//no filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	ASSERT(glGetError() == 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	ASSERT(glGetError() == 0);

	void* data = malloc(width*height*4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);

//	m_glprocs->glGenerateMipmap(GL_TEXTURE_2D);
//	ASSERT(glGetError() == 0);

	uint fbo;
	m_glprocs->glGenFramebuffers(1, &fbo);

// attach the Direct3D buffers to an FBO
	m_glprocs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	ASSERT(glGetError() == 0);

	m_glprocs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gl_names[0], 0);
	ASSERT(glGetError() == 0);

	GLenum status = m_glprocs->glCheckFramebufferStatus(GL_FRAMEBUFFER);

	ASSERT(status == GL_FRAMEBUFFER_COMPLETE);

	//    <opengl renders to the render targets>

	glViewport(0, 0, width, height);
}

WebGLRenderingContext::WebGLRenderingContext(IWebCanvas* canvas) : m_canvas(canvas)
{
	HWindow* win = new HWindow();
	win->CreateOverlapped(L"OpenGL");

	HWND m_hWnd = win->get_Hwnd();
	m_hDC = ::GetDC(m_hWnd);				// This gets the device context for our window
	SetupPixelFormat(m_hDC);			// Call the pixel format function

	m_hRC = wglCreateContext(m_hDC);	// Creates the rendering context
	if (m_hRC == NULL)
	{
		ASSERT(0);
		//throw std::exception("Couldn't create OpenGL context");
	}

	MakeCurrent();

	const char* m_glExtensions = (const char*)::glGetString(GL_EXTENSIONS);

//	Init(m_hDC, m_hRC);

	m_glprocs = new Graphics::GLProcs();

	if (m_glprocs->wglDXOpenDeviceNVX)
	{
		HANDLE h = m_glprocs->wglDXOpenDeviceNVX(Graphics::Direct10::get_D3DDevice());
		if (h)
		{
			DebugTrace("Successfully shared device");
		}
	}
}

WebGLRenderingContext::~WebGLRenderingContext()
{
}

Graphics::Bitmap* WebGLRenderingContext::get_bitmap()
{
	if (gl_handleD3D)
	{
		if (m_locked)
		{
			// unlock the render targets
			m_glprocs->wglDXUnlockObjectsNVX(gl_handleD3D, 1, gl_handles);
			m_locked = false;
		}
	}

	if (m_changed)
	{
		m_changed = false;

		Graphics::D3D10Texture2D tex(Graphics::Direct10::get_D3DDevice(), get_drawingBufferWidth(), get_drawingBufferHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, D3D10_USAGE_DYNAMIC); 

		D3D10_MAPPED_TEXTURE2D mapped;
		if (SUCCEEDED(tex.m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), D3D10_MAP_WRITE_DISCARD, 0, &mapped)))
		{
			glReadPixels(0, 0, get_drawingBufferWidth(), get_drawingBufferHeight(), GL_RGBA, GL_UNSIGNED_BYTE, mapped.pData/*m_bitmap->m_bitmapData*/);
			ASSERT(glGetError() == 0);

			tex.m_d3d10_texture->Unmap(D3D10CalcSubresource(0,0,0));

			Graphics::Direct10::get_D3DDevice()->CopyResource(m_bitmap->m_d3d10_texture, tex.m_d3d10_texture);
		}
	}

	return m_bitmap;
}

GLsizei WebGLRenderingContext::get_drawingBufferWidth()
{
	return get_bitmap()->get_Width();
}

GLsizei WebGLRenderingContext::get_drawingBufferHeight()
{
	return get_bitmap()->get_Height();
}

GLenum WebGLRenderingContext::checkFramebufferStatus(GLenum target)
{
	MakeCurrent();
	return m_glprocs->glCheckFramebufferStatus(target);
}

void WebGLRenderingContext::clear(GLbitfield mask)
{
	MakeCurrent();
	if (gl_handleD3D)
	{
		if (!m_locked)
		{
		// lock the render targets for GL access
			::BOOL success = m_glprocs->wglDXLockObjectsNVX(gl_handleD3D, 1, gl_handles);
			if (!success)
			{
				return;
			}
			m_locked = true;
		}
	}	
	::glClear(mask);

	m_changed = true;
}

void WebGLRenderingContext::clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	MakeCurrent();
	::glClearColor(red, green, blue, alpha);
}

void WebGLRenderingContext::clearDepth(GLclampf depth)
{
	MakeCurrent();
	::glClearDepth(depth);
}

void WebGLRenderingContext::clearStencil(GLint s)
{
	MakeCurrent();
	::glClearStencil(s);
}

void WebGLRenderingContext::colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	MakeCurrent();

	::glColorMask(red, green, blue, alpha);
}

void WebGLRenderingContext::drawArrays(GLenum mode, GLint first, GLsizei count)
{
	MakeCurrent();

	::glDrawArrays(mode, first, count);
	m_changed = true;
}

void WebGLRenderingContext::drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset)
{
	MakeCurrent();

	::glDrawElements(mode, count, type, (const void*)offset);
	m_changed = true;
}

WebGLBuffer* WebGLRenderingContext::createBuffer()
{
	MakeCurrent();

	uint nbuffer;
	m_glprocs->glGenBuffers(1, &nbuffer);
	if (nbuffer)
		return new WebGLBuffer(this, nbuffer);
	else
		return NULL;
}

WebGLFramebuffer* WebGLRenderingContext::createFramebuffer()
{
	MakeCurrent();

	uint nbuffer;
	m_glprocs->glGenFramebuffers(1, &nbuffer);
	if (nbuffer)
		return new WebGLFramebuffer(this, nbuffer);
	else
		return NULL;
}

GLenum WebGLRenderingContext::getError() throw (DOMException*)
{
	MakeCurrent();
	return ::glGetError();
}

void WebGLRenderingContext::activeTexture(GLenum texture)
{
	MakeCurrent();
	m_glprocs->glActiveTexture(texture);
}

void WebGLRenderingContext::bindBuffer(GLenum target, WebGLBuffer* buffer)
{
	MakeCurrent();
	m_glprocs->glBindBuffer(target, buffer->m_nbuffer);
}

void WebGLRenderingContext::bindFramebuffer(GLenum target, WebGLFramebuffer* framebuffer)
{
	MakeCurrent();
	m_glprocs->glBindBuffer(target, framebuffer->m_nbuffer);
}

void WebGLRenderingContext::bindRenderbuffer(GLenum target, WebGLRenderbuffer* renderbuffer)
{
	MakeCurrent();
	m_glprocs->glBindRenderbuffer(target, renderbuffer->m_nbuffer);
}

void WebGLRenderingContext::bindTexture(GLenum target, WebGLTexture* texture)
{
	MakeCurrent();
	glBindTexture(target, texture->m_nbuffer);
}

void WebGLRenderingContext::blendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	MakeCurrent();
	m_glprocs->glBlendColor(red, green, blue, alpha);
}

void WebGLRenderingContext::blendEquation(GLenum mode)
{
	MakeCurrent();
}

void WebGLRenderingContext::blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	MakeCurrent();
}

void WebGLRenderingContext::blendFunc(GLenum sfactor, GLenum dfactor)
{
	MakeCurrent();
	glBlendFunc(sfactor, dfactor);
}

void WebGLRenderingContext::blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	MakeCurrent();
	m_glprocs->glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void WebGLRenderingContext::attachShader(WebGLProgram* program, WebGLShader* shader)
{
	VerifyArgumentNotNull(program);
	VerifyArgumentNotNull(shader);

	MakeCurrent();
	m_glprocs->glAttachShader(program->m_nbuffer, shader->m_nbuffer);
}

GLboolean WebGLRenderingContext::isBuffer(WebGLBuffer* buffer)
{
	VerifyArgumentNotNull(buffer);

	MakeCurrent();
	return m_glprocs->glIsBuffer(buffer->m_nbuffer) != 0;
}

GLboolean WebGLRenderingContext::isFramebuffer(WebGLFramebuffer* framebuffer)
{
	VerifyArgumentNotNull(framebuffer);

	MakeCurrent();
	return m_glprocs->glIsFramebuffer(framebuffer->m_nbuffer) != 0;
}

void WebGLRenderingContext::linkProgram(WebGLProgram* program)
{
	VerifyArgumentNotNull(program);

	MakeCurrent();
	m_glprocs->glLinkProgram(program->m_nbuffer);
}

void WebGLRenderingContext::useProgram(WebGLProgram* program)
{
	VerifyArgumentNotNull(program);

	MakeCurrent();
	m_glprocs->glUseProgram(program->m_nbuffer);
}

void WebGLRenderingContext::shaderSource(WebGLShader* shader, StringIn source)
{
	ASSERT(0);	// TODO
	int length;

	MakeCurrent();
	m_glprocs->glShaderSource(shader->m_nbuffer, 1, NULL, &length);
}

String WebGLRenderingContext::getShaderInfoLog(WebGLShader* shader)
{
	VerifyArgumentNotNull(shader);

	const int bufSize = 512;
	char infoLog[bufSize];
	int length;
	MakeCurrent();
	m_glprocs->glGetShaderInfoLog(shader->m_nbuffer, bufSize, &length, infoLog);

	return String(string_copy(infoLog, length));
}

Variant WebGLRenderingContext::getRenderbufferParameter(GLenum target, GLenum pname)
{
	int param;
	MakeCurrent();
	m_glprocs->glGetRenderbufferParameteriv(target, pname, &param);
	return param;
}

void WebGLRenderingContext::frontFace(GLenum mode)
{
	MakeCurrent();
	glFrontFace(mode);
}

void WebGLRenderingContext::viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	MakeCurrent();
	glViewport(x, y, width, height);
}

}	// Web
}	// System
