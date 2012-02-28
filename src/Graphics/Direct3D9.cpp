#include "StdAfx.h"
#include "Graphics.h"
//#include "GraphicsO.h"
//#include "gl.h"

//#include <windows.h>
#include <d3d9.h>
#include <D3dx9math.h>

#include <Cg/cg.h>
#include <Cg/cgD3D9.h>

#define D3D_MODELVIEW	D3DTS_WORLD

namespace System
{
namespace Graphics
{

Direct3D9_I::Direct3D9_I(IDirect3DDevice9* d3dDevice) :
	m_d3dDevice(d3dDevice),
	m_matrixMode(GL_MODELVIEW)
{
#if 0
	m_cgContext = ::cgCreateContext();
	::cgD3D9SetDevice(m_d3dDevice);
#endif
}

CGcontext Direct3D9_I::GetCGContext()
{
	return m_cgContext;
}

int Direct3D9_I::cgGetLatestProfile(unsigned int type)
{
	if (type == 8)	// CG_GL_VERTEX
	{
		return cgD3D9GetLatestVertexProfile();
	}
	else if (type == 9)	// CG_GL_FRAGMENT
	{
		return cgD3D9GetLatestPixelProfile();
	}
	else if (type == 10)	// CG_GL_GEOMETRY
	{
		VERIFY(0);
	}
	else
		throw std::exception("cgGetLatestProfile: Invalid type");

	return 0;
}

void Direct3D9_I::SetMatrixMode(GLenum mode)
{
	m_matrixMode = mode;
}

void Direct3D9_I::IdentityTransform()
{
	HRESULT hr;

	gm::matrix4f m = gm::matrix4f::getIdentity();

	switch (m_matrixMode)
	{
	case GL_MODELVIEW:
		hr = m_d3dDevice->SetTransform(D3D_MODELVIEW, (const D3DMATRIX*)(const float*)m);
		break;

	case GL_PROJECTION:
		hr = m_d3dDevice->SetTransform(D3DTS_PROJECTION, (const D3DMATRIX*)(const float*)m);
		break;
	}

	VERIFY(SUCCEEDED(hr));
}

void Direct3D9_I::TranslateTransform(float x, float y, float z)
{
	D3DXMATRIX matView;
	D3DXMatrixTranslation(&matView, x, y, z);

	HRESULT hr;

	switch (m_matrixMode)
	{
	case GL_MODELVIEW:
		hr = m_d3dDevice->MultiplyTransform(D3D_MODELVIEW, &matView);
		break;

	case GL_PROJECTION:
		hr = m_d3dDevice->MultiplyTransform(D3DTS_PROJECTION, &matView);
		break;
	}

	VERIFY(SUCCEEDED(hr));
}

void Direct3D9_I::ScaleTransform(float sx, float sy, float sz)
{
	D3DXMATRIX matView;
	D3DXMatrixScaling(&matView, sx, sy, sz);

	HRESULT hr;

	switch (m_matrixMode)
	{
	case GL_MODELVIEW:
		hr = m_d3dDevice->MultiplyTransform(D3D_MODELVIEW, &matView);
		break;

	case GL_PROJECTION:
		hr = m_d3dDevice->MultiplyTransform(D3DTS_PROJECTION, &matView);
		break;
	}

	VERIFY(SUCCEEDED(hr));
}

inline float DegreesToRadians(const float degrees)
{
	return degrees * (M_PI_f / 180);
}

void Direct3D9_I::RotateTransform(float angleDegrees, float x, float y, float z)
{
	D3DXMATRIX matView;
	D3DXVECTOR3 axis(x, y, z);
	D3DXMatrixRotationAxis(&matView, &axis, angleDegrees * (M_PI_f / 180));

	HRESULT hr;

	switch (m_matrixMode)
	{
	case GL_MODELVIEW:
		hr = m_d3dDevice->MultiplyTransform(D3D_MODELVIEW, &matView);
		break;

	case GL_PROJECTION:
		hr = m_d3dDevice->MultiplyTransform(D3DTS_PROJECTION, &matView);
		break;
	}

	VERIFY(SUCCEEDED(hr));
}

void Direct3D9_I::MultiplyTransform(const float m[16])
{
	HRESULT hr;

	switch (m_matrixMode)
	{
	case GL_MODELVIEW:
		hr = m_d3dDevice->MultiplyTransform(D3D_MODELVIEW, (const D3DMATRIX*)(const float*)m);
		break;

	case GL_PROJECTION:
		hr = m_d3dDevice->MultiplyTransform(D3DTS_PROJECTION, (const D3DMATRIX*)(const float*)m);
		break;
	}

	VERIFY(SUCCEEDED(hr));
}

void Direct3D9_I::SetTransform(const float m[16])
{
	HRESULT hr;

	switch (m_matrixMode)
	{
	case GL_MODELVIEW:
		hr = m_d3dDevice->SetTransform(D3D_MODELVIEW, (const D3DMATRIX*)(const float*)m);
		break;

	case GL_PROJECTION:
		hr = m_d3dDevice->SetTransform(D3DTS_PROJECTION, (const D3DMATRIX*)(const float*)m);
		break;
	}

	VERIFY(SUCCEEDED(hr));
}

void Direct3D9_I::SetTexture(int stage, Texture texture)
{
	m_d3dDevice->SetTexture(stage, texture.u.d3d);
}

void Direct3D9_I::Viewport(int x, int y, int width, int height)
{
	VERIFY(0);
}

void Direct3D9_I::SetClipPlane(int n, const float equation[4])
{
	HRESULT hr = m_d3dDevice->SetClipPlane(n, equation);
	ASSERT(SUCCEEDED(hr));
}

void Direct3D9_I::EnableClipPlanes(UINT mask)
{
	HRESULT hr = m_d3dDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, mask);
	ASSERT(SUCCEEDED(hr));
}

VertexDeclaration Direct3D9_I::CreateVertexDeclaration(VertexDeclElement* elements, unsigned int count, void* shader)
{
	if (count > MAXD3DDECLLENGTH)
	{
		throw std::exception("Too many vertex declaration elements");
	}

	D3DVERTEXELEMENT9 dwDecl[MAXD3DDECLLENGTH+1];

	int index = 0;

	for (size_t i = 0; i < count; ++i)
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
			throw std::exception("Invalid vertex declaration element usage");

		++index;
	}

	/*
	// Normal0
	dwDecl[index].Stream = 0;
	dwDecl[index].Offset = 12;
	dwDecl[index].Type = D3DDECLTYPE_FLOAT3;
	dwDecl[index].Method = D3DDECLMETHOD_DEFAULT;
	dwDecl[index].Usage = D3DDECLUSAGE_NORMAL;
	dwDecl[index].UsageIndex = 0;
	++index;

	if (false)
	{
		// Texcoord0
		dwDecl[index].Stream = 1;
		dwDecl[index].Offset = 0;
		dwDecl[index].Type = D3DDECLTYPE_FLOAT2;
		dwDecl[index].Method = D3DDECLMETHOD_DEFAULT;
		dwDecl[index].Usage = D3DDECLUSAGE_TEXCOORD;
		dwDecl[index].UsageIndex = 0;
		++index;

		// Position1
		dwDecl[index].Stream = 2;
		dwDecl[index].Offset = 0;
		dwDecl[index].Type = D3DDECLTYPE_FLOAT3;
		dwDecl[index].Method = D3DDECLMETHOD_DEFAULT;
		dwDecl[index].Usage = D3DDECLUSAGE_POSITION;
		dwDecl[index].UsageIndex = 1;
		++index;

		// Normal1
		dwDecl[index].Stream = 2;
		dwDecl[index].Offset = 12;
		dwDecl[index].Type = D3DDECLTYPE_FLOAT3;
		dwDecl[index].Method = D3DDECLMETHOD_DEFAULT;
		dwDecl[index].Usage = D3DDECLUSAGE_NORMAL;
		dwDecl[index].UsageIndex = 1;
		++index;
	}
	*/

	// End
	dwDecl[index].Stream = 0xFF;
	dwDecl[index].Offset = 0;
	dwDecl[index].Type = D3DDECLTYPE_UNUSED;
	dwDecl[index].Method = 0;
	dwDecl[index].Usage = 0;
	dwDecl[index].UsageIndex = 0;

	IDirect3DVertexDeclaration9* vertexDeclaration;
	HRESULT hr = m_d3dDevice->CreateVertexDeclaration(dwDecl, &vertexDeclaration);
	ASSERT(SUCCEEDED(hr));

	return VertexDeclaration(vertexDeclaration);

	/*
	m_state->m_vertexDeclarations.push_back(vertexDeclaration);

	unsigned int n = m_state->m_vertexDeclarations.size();

	return n;
	*/
}

void Direct3D9_I::PushMatrix()
{
	if (m_matrixMode == GL_MODELVIEW)
	{
		gm::matrix4f matrix;
		m_d3dDevice->GetTransform(D3D_MODELVIEW, (D3DMATRIX*)(float*)matrix);

		m_modelviewMatrixStack.push(matrix);
	}
	else if (m_matrixMode == GL_PROJECTION)
	{
		gm::matrix4f matrix;
		m_d3dDevice->GetTransform(D3DTS_PROJECTION, (D3DMATRIX*)(float*)matrix);

		m_projectionMatrixStack.push(matrix);
	}
	else if (m_matrixMode == GL_TEXTURE)
	{
		ASSERT(0);
	//	m_state->m_textureMatrixStack[m_state->m_activeTexture].push(m_state->m_textureMatrix[m_state->m_activeTexture]);
	}
}

void Direct3D9_I::PopMatrix()
{
	if (m_matrixMode == GL_MODELVIEW)
	{
		const gm::matrix4f& matrix = m_modelviewMatrixStack.top();
		m_d3dDevice->SetTransform(D3D_MODELVIEW, (const D3DMATRIX*)(const float*)matrix);
		m_modelviewMatrixStack.pop();
	}
	else if (m_matrixMode == GL_PROJECTION)
	{
		const gm::matrix4f& matrix = m_projectionMatrixStack.top();
		m_d3dDevice->SetTransform(D3DTS_PROJECTION, (const D3DMATRIX*)(const float*)matrix);
		m_projectionMatrixStack.pop();
	}
	else if (m_matrixMode == GL_TEXTURE)
	{
		ASSERT(0);
	//	const matrix4& matrix = m_state->m_textureMatrixStack[m_state->m_activeTexture].top();
	//	m_state->m_textureMatrixStack[m_state->m_activeTexture].pop();
			//m_d3dDevice->SetTransform(D3D_MODELVIEW, (D3DMATRIX*)(float*)m_state->m_modelview);
	}
}

IndexBuffer Direct3D9_I::GetIndexBuffer(UINT* pOffsetInBytes)
{
	IDirect3DIndexBuffer9* indexBuffer = NULL;

	HRESULT hr;
	hr = m_d3dDevice->GetIndices(&indexBuffer);
	ASSERT(SUCCEEDED(hr));

	D3DINDEXBUFFER_DESC desc;
	indexBuffer->GetDesc(&desc);

	if (*pOffsetInBytes)
		*pOffsetInBytes = m_startIndex << (desc.Format == D3DFMT_INDEX16? 1: 2);

	return IndexBuffer(indexBuffer, desc.Format == D3DFMT_INDEX16? GL_UNSIGNED_SHORT: GL_UNSIGNED_INT);
}

void Direct3D9_I::SetIndexBuffer(IndexBuffer indexBuffer, UINT offsetInBytes)
{
	if (indexBuffer.u.d3d)
	{
		D3DINDEXBUFFER_DESC desc;
		indexBuffer.u.d3d->GetDesc(&desc);

		if (desc.Format == D3DFMT_INDEX16)//if (indexBuffer.m_type == GL_UNSIGNED_SHORT)
		{
			if (offsetInBytes & 1) throw std::exception("Invalid offsetInBytes");
			m_startIndex = offsetInBytes / 2;
		}
		else
		{
			//ASSERT(indexBuffer.m_type == GL_UNSIGNED_INT);

			if (offsetInBytes & 3) throw std::exception("Invalid offsetInBytes");
			m_startIndex = offsetInBytes / 4;
		}
	}
	else
	{
		if (offsetInBytes != 0) throw std::exception("offsetInBytes must be null if indexBuffer = NULL");

		m_startIndex = 0;
	}

	HRESULT hr;
	hr = m_d3dDevice->SetIndices(indexBuffer.u.d3d);
	ASSERT(SUCCEEDED(hr));
}

IndexBuffer Direct3D9_I::CreateIndexBuffer(unsigned int type, unsigned int size, const void* data)
{
	D3DFORMAT format;

	if (type == GL_UNSIGNED_SHORT)
	{
		format = D3DFMT_INDEX16;
	}
	else if (type == GL_UNSIGNED_INT)
	{
		format = D3DFMT_INDEX32;
	}
	else
		throw std::exception("Invalid type");

	DWORD usage = D3DUSAGE_WRITEONLY;
	//usage |= D3DUSAGE_DYNAMIC;
	D3DPOOL pool = D3DPOOL_DEFAULT;//D3DPOOL_MANAGED/**/;

	IDirect3DIndexBuffer9* indexBuffer;
	HRESULT hr = m_d3dDevice->CreateIndexBuffer(size, usage, format, pool, &indexBuffer, NULL);
	ASSERT(SUCCEEDED(hr));

	if (data)
	{
		void* pb;
		indexBuffer->Lock(0, size, &pb, 0);
		memcpy(pb, data, size);
		indexBuffer->Unlock();
	}

	return IndexBuffer(indexBuffer, type);
}

VertexBuffer Direct3D9_I::CreateVertexBuffer(unsigned int size, const void* data, unsigned int bufferUsage)
{
	IDirect3DVertexBuffer9* vertexBuffer;

	DWORD usage = D3DUSAGE_WRITEONLY;
	//usage |= D3DUSAGE_DYNAMIC;
	D3DPOOL pool = D3DPOOL_DEFAULT;//D3DPOOL_MANAGED/**/;

	HRESULT hr = m_d3dDevice->CreateVertexBuffer(size, usage, 0, pool, &vertexBuffer, NULL);
	ASSERT(SUCCEEDED(hr));

	if (data)
	{
		void* pb;
		vertexBuffer->Lock(0, size, &pb, 0);
		memcpy(pb, data, size);
		vertexBuffer->Unlock();
	}

	return VertexBuffer(vertexBuffer);
}

void Direct3D9_I::IndexBufferSubData_(IndexBuffer buffer, unsigned int offset, unsigned int size, const void* data)
{
	IDirect3DIndexBuffer9* indexBuffer = buffer.u.d3d;

	UINT flags = 0;//D3DLOCK_NOOVERWRITE;	// TODO

	void* pv;
	indexBuffer->Lock(offset, size, &pv, flags);
	memcpy(pv, data, size);
	indexBuffer->Unlock();
}

void Direct3D9_I::VertexBufferSubData_(VertexBuffer buffer, unsigned int offset, unsigned int size, const void* data)
{
	IDirect3DVertexBuffer9* vertexBuffer = buffer.u.d3d;

	UINT flags = 0;//D3DLOCK_NOOVERWRITE;	// TODO

	void* pv;
	vertexBuffer->Lock(offset, size, &pv, flags);
	memcpy(pv, data, size);
	vertexBuffer->Unlock();
}

void Direct3D9_I::Enable(GLenum cap)
{
	switch (cap)
	{
		case GL_NORMALIZE:
			m_d3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
			break;

		case GL_LIGHTING:
			m_d3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			break;

		case GL_DEPTH_TEST:
			m_d3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			break;

		default:
			VERIFY(0);
	}
}

void Direct3D9_I::Disable(GLenum cap)
{
	switch (cap)
	{
		case GL_NORMALIZE:
			m_d3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
			break;

		case GL_LIGHTING:
			m_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			break;

		case GL_DEPTH_TEST:
			m_d3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			break;

		default:
			VERIFY(0);
	}
}

void Direct3D9_I::SetVertexBuffer(unsigned int stream, VertexBuffer vertexBuffer, unsigned int offsetInBytes, unsigned int stride)
{
	HRESULT hr;
	hr = m_d3dDevice->SetStreamSource(stream, vertexBuffer.u.d3d, offsetInBytes, stride);
	ASSERT(SUCCEEDED(hr));
}

void Direct3D9_I::SetVertexBuffers(unsigned int start, unsigned int numBuffers, VertexBuffer* vertexBuffers, const unsigned int* strides, const unsigned int* byteOffsets)
{
	for (unsigned int i = 0; i < numBuffers; i++)
	{
		HRESULT hr;
		hr = m_d3dDevice->SetStreamSource(start+i, vertexBuffers[i].u.d3d, byteOffsets[i], strides[i]);
		ASSERT(SUCCEEDED(hr));
	}
}

IDirect3DDevice9* Direct3D9_I::GetD3D9Device()
{
	return m_d3dDevice;
}

void Direct3D9_I::Clear(uint32 mask)
{
	DWORD d3dmask = 0;

	if (mask & GL_COLOR_BUFFER_BIT) d3dmask |= D3DCLEAR_TARGET;
	if (mask & GL_DEPTH_BUFFER_BIT) d3dmask |= D3DCLEAR_ZBUFFER;
	if (mask & GL_STENCIL_BUFFER_BIT) d3dmask |= D3DCLEAR_STENCIL;

	float clearDepth = 1.0f;
	HRESULT hr = m_d3dDevice->Clear(0, NULL, d3dmask, 0x00000000, clearDepth, 0);
	ASSERT(SUCCEEDED(hr));
}

void Direct3D9_I::DepthMask(bool mask)
{
	HRESULT hr = m_d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, mask);
	ASSERT(SUCCEEDED(hr));
}

Texture Direct3D9_I::CreateTexture1D(GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels)
{
	IDirect3DTexture9* d3dTexture;
	m_d3dDevice->CreateTexture(width, 1/*height*/, 1/*level*/, D3DUSAGE_AUTOGENMIPMAP/*D3DUSAGE_RENDERTARGET*/, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED/* D3DPOOL_DEFAULT*/, &d3dTexture, NULL);
//	m_d3dDevice->CreateTexture(width, height, 1, 0/*D3DUSAGE_RENDERTARGET*/, D3DFMT_R8G8B8, D3DPOOL_MANAGED/* D3DPOOL_DEFAULT*/, &d3dTexture);

//	texImage->m_d3dTexture = d3dTexture;

	D3DLOCKED_RECT rc;
	d3dTexture->LockRect(0, &rc, NULL, 0);

	uint8* dst = (uint8*)rc.pBits;
	uint8* src = (uint8*)pixels;

	for (int x = 0; x < width; x++)
	{
		dst[0] = src[0];
		dst[1] = src[1];
		dst[2] = src[2];
		dst[3] = src[3];

	//	dst[0] = src[2];	// b
	//	dst[1] = src[1];	// g
	//	dst[2] = src[0];	// r

		dst += 4;
		src += 4;
	}

	d3dTexture->UnlockRect(0);
//	d3dTexture->GenerateMipSubLevels();

	return Texture(this, d3dTexture);
}

Texture Direct3D9_I::CreateTexture2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
{
//	TexImage* texImage = m_state->m_texImage[m_state->m_texBinding[m_state->m_activeTexture][target - GL_TEXTURE_1D]/* - 1*/];

	D3DFORMAT d3dformat;
	switch (internalformat)
	{
	case GL_RGB:
		d3dformat = D3DFMT_R8G8B8;
		break;

//	case 4:
	case GL_RGBA:
		d3dformat = D3DFMT_A8R8G8B8;
		break;

	case GL_LUMINANCE:
		d3dformat = D3DFMT_L8;
		break;

	default:
		throw std::exception("Invalid internalformat");
	}

	int srcStride;

	// TODO
	switch (format)
	{
	case GL_BGR:
		srcStride = width*3;
		break;

	case GL_BGRA:
		srcStride = width*4;
		break;

	case GL_LUMINANCE:
		srcStride = width;
		break;

	default:
		throw std::exception("Invalid format");
	}

	IDirect3DTexture9* d3dTexture;
	m_d3dDevice->CreateTexture(width, height, 1/*level*/, D3DUSAGE_AUTOGENMIPMAP/*D3DUSAGE_RENDERTARGET*/, d3dformat, D3DPOOL_MANAGED/* D3DPOOL_DEFAULT*/, &d3dTexture, NULL);
//	m_d3dDevice->CreateTexture(width, height, 1, 0/*D3DUSAGE_RENDERTARGET*/, D3DFMT_R8G8B8, D3DPOOL_MANAGED/* D3DPOOL_DEFAULT*/, &d3dTexture);

//	texImage->m_d3dTexture = d3dTexture;

	if (pixels)
	{
		D3DLOCKED_RECT rc;
		d3dTexture->LockRect(0, &rc, NULL, 0);
		for (int y = 0; y < height; y++)
		{
			uint8* dst = (uint8*)rc.pBits + rc.Pitch * y;
			uint8* src = (uint8*)pixels + y * srcStride;

			if (format == GL_BGRA)
			{
				for (int x = 0; x < width; x++)
				{
					dst[0] = src[0];
					dst[1] = src[1];
					dst[2] = src[2];
					dst[3] = src[3];

				//	dst[0] = src[2];	// b
				//	dst[1] = src[1];	// g
				//	dst[2] = src[0];	// r

					dst += 4;
					src += 4;
				}
			}
			else if (format == GL_BGR)
			{
				for (int x = 0; x < width; x++)
				{
					dst[0] = src[0];
					dst[1] = src[1];
					dst[2] = src[2];
					dst[3] = 255;

				//	dst[0] = src[2];	// b
				//	dst[1] = src[1];	// g
				//	dst[2] = src[0];	// r

					dst += 4;
					src += 3;
				}
			}
			else
			{
				ASSERT(0);
			}
		}

		d3dTexture->UnlockRect(0);
	}
//	d3dTexture->GenerateMipSubLevels();

	return Texture(this, d3dTexture);
}

void Direct3D9_I::GetFloatv(GLenum pname, GLfloat* params)
{
	switch (pname)
	{
	case GL_MODELVIEW_MATRIX:
		{
			m_d3dDevice->GetTransform(D3D_MODELVIEW, (D3DMATRIX*)params);
		}
		break;

	case GL_PROJECTION_MATRIX:
		{
			m_d3dDevice->GetTransform(D3DTS_PROJECTION, (D3DMATRIX*)params);
		}
		break;

	default:
		ASSERT(0);
		throw std::exception("GetFloatv: Invalid pname");
	}
}

void Direct3D9_I::SetPrimitiveTopology(unsigned int primitiveTopology)
{
	m_primitiveTopology = primitiveTopology;
}

void Direct3D9_I::Draw(UINT first, UINT count)
{
	D3DPRIMITIVETYPE primitiveType;
	UINT primcount;

	switch (m_primitiveTopology)
	{
	case GL_POINTS:
		primitiveType = D3DPT_POINTLIST;
		primcount = count;
		break;

	case GL_LINES:
		primitiveType = D3DPT_LINELIST;
		primcount = count / 2;
		break;

	case GL_LINE_STRIP:
		primitiveType = D3DPT_LINESTRIP;
		primcount = count - 1;
		break;

	case GL_TRIANGLES:
		primitiveType = D3DPT_TRIANGLELIST;
		primcount = count / 3;
		break;

	case GL_TRIANGLE_STRIP:
		primitiveType = D3DPT_TRIANGLESTRIP;
		primcount = count - 2;
		break;

	case GL_TRIANGLE_FAN:
		primitiveType = D3DPT_TRIANGLEFAN;
		primcount = count - 2;
		break;

	default:
		ASSERT(0);
		throw std::exception("DrawArrays: Invalid mode");
		return;
	}

	HRESULT hr;
	hr = m_d3dDevice->DrawPrimitive(primitiveType, first, primcount);
	ASSERT(SUCCEEDED(hr));
}

void Direct3D9_I::DrawUP(/*unsigned int mode,*/ UINT count, void* data, int stride)
{
	D3DPRIMITIVETYPE primitiveType;
	UINT primcount;

	switch (m_primitiveTopology)
	{
	case GL_POINTS:
		primitiveType = D3DPT_POINTLIST;
		primcount = count;
		break;

	case GL_LINES:
		primitiveType = D3DPT_LINELIST;
		primcount = count / 2;
		break;

	case GL_LINE_STRIP:
		primitiveType = D3DPT_LINESTRIP;
		primcount = count - 1;
		break;

	case GL_TRIANGLES:
		primitiveType = D3DPT_TRIANGLELIST;
		primcount = count / 3;
		break;

	case GL_TRIANGLE_STRIP:
		primitiveType = D3DPT_TRIANGLESTRIP;
		primcount = count - 2;
		break;

	case GL_TRIANGLE_FAN:
		primitiveType = D3DPT_TRIANGLEFAN;
		primcount = count - 2;
		break;

	default:
		ASSERT(0);
		throw std::exception("DrawArraysUP: Invalid mode");
		return;
	}

	HRESULT hr;
	hr = m_d3dDevice->DrawPrimitiveUP(primitiveType, primcount, data, stride);
	ASSERT(SUCCEEDED(hr));
}

void Direct3D9_I::DrawIndexed(/*GLenum mode,*/ int start, int end, UINT count/*, GLenum type, int startIndex*/)
{
	D3DPRIMITIVETYPE primitiveType;
	unsigned int primcount;

	switch (m_primitiveTopology)
	{
	case GL_POINTS:
		primitiveType = D3DPT_POINTLIST;
		primcount = count;
		break;

	case GL_LINES:
		primitiveType = D3DPT_LINELIST;
		primcount = count / 2;
		break;

	case GL_LINE_STRIP:
		primitiveType = D3DPT_LINESTRIP;
		VERIFY(0);
		break;

	case GL_TRIANGLES:
		primitiveType = D3DPT_TRIANGLELIST;
		primcount = count / 3;
		break;

	case GL_TRIANGLE_STRIP:
		primitiveType = D3DPT_TRIANGLESTRIP;
		VERIFY(0);
		break;

	case GL_TRIANGLE_FAN:
		primitiveType = D3DPT_TRIANGLEFAN;
		primcount = count - 2;
		break;

	default:
		ASSERT(0);
		throw std::exception("DrawRangeElements: Invalid mode");
		return;
	}

	int baseVertexIndex = 0;	// Not supported
			// (since OpenGL doesn't have any corresponding ?)

	int startIndex = m_startIndex;

	HRESULT hr;
	hr = m_d3dDevice->DrawIndexedPrimitive(primitiveType, baseVertexIndex, start, end-start+1, startIndex, primcount);
	ASSERT(SUCCEEDED(hr));
}

void Direct3D9_I::DeleteVertexDeclaration(VertexDeclaration decl)
{
	if (decl.u.d3d)
	{
		decl.u.d3d->Release();
	}
}

void Direct3D9_I::SetVertexDeclaration(VertexDeclaration decl)
{
	HRESULT hr = m_d3dDevice->SetVertexDeclaration(decl.u.d3d);
	ASSERT(SUCCEEDED(hr));
}

void Direct3D9_I::cgBindProgram(CGprogram cgProgram)
{
	::cgD3D9SetDevice(m_d3dDevice);
	ASSERT(::cgGetError() == 0);

	::cgD3D9BindProgram(cgProgram);
	ASSERT(::cgGetError() == 0);
}

void Direct3D9_I::cgLoadProgram(CGprogram cgProgram)
{
	::cgD3D9SetDevice(m_d3dDevice);
	ASSERT(::cgGetError() == 0);

	// TODO ?
	::cgD3D9LoadProgram(cgProgram, CG_FALSE, 0);
	ASSERT(::cgGetError() == 0);
}

}	// Graphics
}	// System
