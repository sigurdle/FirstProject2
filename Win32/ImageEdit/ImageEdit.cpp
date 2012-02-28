// ImageEdit.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ImageEdit.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "Graphics")
#pragma comment(lib, "Imaging")
#pragma comment(lib, "GUI")

#pragma comment(lib, "D3D11")
#pragma comment(lib, "d3dx11")

namespace System
{
namespace ImageEdit
{

class StreamImp : public IStream
{
public:
	CTOR StreamImp(IBitmapTransferCallback* callback) : m_cRef(0)
	{
		m_origin = 0;
		m_size = 0;
		m_bufferpos = 0;

		m_y = 0;
		m_state = 0;

		m_callback = callback;
	}

	~StreamImp()
	{
		delete[] m_dstbuffer;
	}

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Read( 
        /* [length_is][size_is][out] */ void *pv,
        /* [in] */ ULONG cb,
        /* [out] */ ULONG *pcbRead)
	{
		return E_NOTIMPL;
	}

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Write( 
        /* [size_is][in] */ const void *pv,
        /* [in] */ ULONG cb,
        /* [out] */ ULONG *pcbWritten)
	{
		m_size += cb;

		if (m_state < 2)
		{
			memcpy(m_buffer+m_bufferpos, pv, cb);

			int state;
			do
			{
				state = m_state;

				switch (m_state)
				{
				case 0:
					{
						if (m_size >= 2)
						{
							if (m_buffer[0] != 'B' || m_buffer[1] != 'M')
							{
								return E_FAIL;
							}

							m_state = 1;
						}
					}
					break;

				case 1:
					{
						if (m_size >= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER))
						{
							m_bmih = *(BITMAPINFOHEADER*)(m_buffer+sizeof(BITMAPFILEHEADER));

							m_state = 2;
							//movmem(m_buffer, m_buffer, sizeof(BITMAPFILEHEADER)

							ASSERT(0);
#if 0

							m_bitmap = new LDraw::Bitmap(m_bmih.biWidth, -m_bmih.biHeight, m_bmih.biWidth*4, LDraw::PixelFormat_t::RGBAP_32, NULL);
						//	m_bitmap = new LDraw::Bitmap(m_bmih.biWidth, -m_bmih.biHeight, m_bmih.biWidth*3, LDraw::PixelFormat_t::RGB_24, NULL);
							m_bitmap->m_d3dDevice = UI::GetD3DDevice9();

							m_bitmap->m_d3dDevice->CreateTexture(m_bitmap->GetWidth(), m_bitmap->GetHeight(), 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_bitmap->m_texture.u.d3d, NULL);
							m_bitmap->m_d3dTexture = m_bitmap->m_texture.u.d3d;

							m_callback->OnTransferBitmap(m_bitmap);
						//	BitmapVisual* visual = new BitmapVisual;
						//	visual->set_Bitmap(m_bitmap);

						//	m_x = 0;
							m_y = 0;

						//	m_frame->set_Content(visual);

							m_dstsize = ROWBYTES_DWORD(m_bitmap->GetWidth(), 24);
							m_dstbuffer = new uint8[m_dstsize];
							m_dstoffset = 0;

							bitmapdata(m_buffer + sizeof(BITMAPFILEHEADER)+m_bmih.biSize, m_size - (sizeof(BITMAPFILEHEADER)+m_bmih.biSize));
#endif

						//	bfOffBits
						}
					}
					break;
				}
			}
			while (m_state != state);

			m_bufferpos += cb;
		}
		else
		{
			if (m_size >= sizeof(BITMAPFILEHEADER)+m_bmih.biSize)
			{
				bitmapdata((const uint8*)pv, cb);
			}
		}

		if (pcbWritten) *pcbWritten = cb;

		return S_OK;
	}

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Seek( 
        /* [in] */ LARGE_INTEGER dlibMove,
        /* [in] */ DWORD dwOrigin,
        /* [out] */ ULARGE_INTEGER *plibNewPosition)
	{
		switch (dwOrigin)
		{
		case STREAM_SEEK_SET:
			m_origin = dlibMove.QuadPart;
			break;

		case STREAM_SEEK_CUR:
			m_origin += dlibMove.QuadPart;
			break;

		case STREAM_SEEK_END:
			m_origin = m_size + dlibMove.QuadPart;
			break;

		default:
			return E_INVALIDARG;
		}

		return S_OK;
	}

    virtual HRESULT STDMETHODCALLTYPE SetSize( 
        /* [in] */ ULARGE_INTEGER libNewSize)
	{
		return E_NOTIMPL;
	}
    
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE CopyTo( 
        /* [unique][in] */ IStream *pstm,
        /* [in] */ ULARGE_INTEGER cb,
        /* [out] */ ULARGE_INTEGER *pcbRead,
        /* [out] */ ULARGE_INTEGER *pcbWritten)
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE Commit( 
        /* [in] */ DWORD grfCommitFlags)
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE Revert()
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE LockRegion( 
        /* [in] */ ULARGE_INTEGER libOffset,
        /* [in] */ ULARGE_INTEGER cb,
        /* [in] */ DWORD dwLockType)
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE UnlockRegion( 
        /* [in] */ ULARGE_INTEGER libOffset,
        /* [in] */ ULARGE_INTEGER cb,
        /* [in] */ DWORD dwLockType)
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE Stat( 
        /* [out] */ __RPC__out STATSTG *pstatstg,
        /* [in] */ DWORD grfStatFlag)
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE Clone( 
        /* [out] */ __RPC__deref_out_opt IStream **ppstm)
	{
		return E_NOTIMPL;
	}

public: // IUnknown

	ULONG __stdcall AddRef()
	{
		++m_cRef;
		return m_cRef;
	}

	ULONG __stdcall Release()
	{
		--m_cRef;
		if (m_cRef == 0)
		{
			delete this;
			return 0;
		}

		return m_cRef;
	}

	HRESULT __stdcall QueryInterface(const ::IID& riid, void** ppvObject)
	{
		if (riid == IID_IUnknown)
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_ISequentialStream)
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IStream)
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}

		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

private:

	void bitmapdata(const uint8* pb, unsigned int cb)
	{
		if (cb == 0) return;

		int i = 0;
		while (i < cb)
		{
			int cb2 = cb;
			if (m_dstoffset + cb2 > m_dstsize)
			{
				cb2 = m_dstsize - m_dstoffset;
			}
			memcpy(m_dstbuffer + m_dstoffset, pb+i, cb2);

			i += cb2;
			m_dstoffset += cb2;

			if (m_dstoffset == m_dstsize)
			{
				ASSERT(0);
#if 0
			//	RECT rect = {0,0,m_bitmap->GetWidth()*3,0};
				D3DLOCKED_RECT locked_rect;
				m_bitmap->m_d3dTexture->LockRect(0, &locked_rect, NULL/*&rect*/, 0);

				int srcPaddingBytes = ROWBYTES_DWORD(m_bitmap->GetWidth(), 24) - (m_bitmap->GetWidth()*3);//ROWBYTES_DWORD((m_bitmap->GetWidth()*3 + 3) & ~15) - (m_bitmap->GetWidth()*3);
				int dstPaddingBytes = locked_rect.Pitch - (m_bitmap->GetWidth()*4);

				const uint8* src = m_dstbuffer;
				uint8* dst = (uint8*)locked_rect.pBits + m_y*locked_rect.Pitch;

				int npixels = m_bitmap->GetWidth();

				for (int n = 0; n < npixels; n++)
				{
					dst[0] = src[0];
					dst[1] = src[1];
					dst[2] = src[2];
					dst[3] = 255;

					dst += 4;
					src += 3;
				}

				m_bitmap->m_d3dTexture->UnlockRect(0);

				++m_y;
				m_dstoffset = 0;
#endif
			}
		}
	}

	/// For ref counting implementation
	LONG m_cRef;

	int m_state;

//	int m_x;
	int m_y;

	int64 m_origin;
	int64 m_size;
	BITMAPINFOHEADER m_bmih;

	uint8* m_dstbuffer;
	int m_dstsize;
	int m_dstoffset;

	int m_bufferpos;
	uint8 m_buffer[512];

	IBitmapTransferCallback* m_callback;

	Graphics::Bitmap* m_bitmap;
};

class WiaTransferCallback : public IWiaTransferCallback
{
public: // Constructors, destructor
	CTOR WiaTransferCallback(IBitmapTransferCallback* callback) : m_cRef(0)
	{
		m_callback = callback;
	}

	~WiaTransferCallback()
	{
	}

public: // IWiaTransferCallback
	HRESULT __stdcall TransferCallback(LONG lFlags, WiaTransferParams* pWiaTransferParams)
	{
		HRESULT hr = S_OK;

		switch (pWiaTransferParams->lMessage)
		{
		case WIA_TRANSFER_MSG_STATUS:
			break;

		case WIA_TRANSFER_MSG_END_OF_STREAM:
			break;

		case WIA_TRANSFER_MSG_END_OF_TRANSFER:
			m_callback->OnTransferDone();
			break;

		default:
			break;
		}

		return hr;
	}

	HRESULT __stdcall GetNextStream(
		LONG    lFlags,
		BSTR    bstrItemName,
		BSTR    bstrFullItemName,
		IStream **ppDestination)
	{

		HRESULT hr = S_OK;

		//  Return a new stream for this item's data.
		//
		//hr = CreateDestinationStream(bstrItemName, ppDestination);

		StreamImp* p = new StreamImp(m_callback);
		p->AddRef();
		*ppDestination = p;

		return hr;
	}

public: // IUnknown

	ULONG __stdcall AddRef()
	{
		++m_cRef;
		return m_cRef;
	}

	ULONG __stdcall Release()
	{
		--m_cRef;
		if (m_cRef == 0)
		{
			delete this;
			return 0;
		}

		return m_cRef;
	}

	HRESULT __stdcall QueryInterface(const ::IID& riid, void** ppvObject)
	{
		if (riid == IID_IUnknown)
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IWiaTransferCallback)
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}

		return E_NOINTERFACE;
	}

private:
	/// For ref counting implementation
	LONG m_cRef;

	IBitmapTransferCallback* m_callback;
};

void PaintBrush::SetCircular()
{
	int size = 512+1;

//	DXGI_FORMAT pixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT pixelFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	unsigned int pixelBytes = 4*sizeof(float);
	unsigned int rowPitch = size*pixelBytes;
	void* sysMem = new byte[rowPitch*size*4*sizeof(float)];

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			// normalize
			float dx = (size/2 - x) / float(size/2);
			float dy = (size/2 - y) / float(size/2);

			float falpha = 1 - (dx*dx + dy*dy);

		//	float falpha = (size/2-sqrtf(float(dx*dx + dy*dy)));

			if (pixelFormat == DXGI_FORMAT_A8_UNORM)
			{
				int alpha = falpha * (256/(size/2));
				if (alpha < 0) alpha = 0;
				else if (alpha > 255) alpha = 255;

				ASSERT(alpha <= 255);

				uint8* dst = (uint8*)sysMem + rowPitch*y + x;
				*dst = alpha;
			}
			else if (pixelFormat == DXGI_FORMAT_R8G8B8A8_UNORM)
			{
				int alpha =  falpha * (256/(size/2));
				if (alpha < 0) alpha = 0;
				else if (alpha > 255) alpha = 255;

				ASSERT(alpha <= 255);

				uint8* dst = (uint8*)sysMem + rowPitch*y + x*4;

				dst[0] = 255;
				dst[1] = 255;
				dst[2] = 255;
				dst[3] = alpha;
			}
			else if (pixelFormat == DXGI_FORMAT_R32G32B32A32_FLOAT)
			{
			//	falpha = falpha * (256/(size/2));

				if (falpha < 0) falpha = 0;
				else if (falpha > 1) falpha = 1;

				float* dst = (float*)((byte*)sysMem + rowPitch*y + x*16);

				dst[0] = 1;
				dst[1] = 1;
				dst[2] = 1;
				dst[3] = falpha;
			}
		}
	}

	Graphics::D3D10Texture2D tex(Graphics::Direct10::get_D3DDevice(), size, size, pixelFormat, sysMem, rowPitch);
	m_bitmap = new Graphics::Bitmap(Graphics::Direct10::get_D3DDevice(), tex);//size, size, size*4, LDraw::PixelFormat_t::RGBAP_32, NULL);

	delete[] sysMem;
}

Graphics::Bitmap* CreateCheckboardBitmap(int width, int height, Graphics::Color color0, Graphics::Color color1)
{
	Graphics::MAPPED_TEXTURE2D mapped;
	mapped.RowPitch = width * 4;
	mapped.pData = new byte[mapped.RowPitch * height];

	int padding = (mapped.RowPitch - (width/2*4))>>2;

	uint32* p0;
	uint32* p1;
	uint32* p2;
	uint32* p3;
	
	p0 = (uint32*)mapped.pData;
	p1 = p0 + width/2;
	p2 = p0 + (mapped.RowPitch>>2)*width/2;
	p3 = p2 + width/2;

	Graphics::Color checkboardColors[2];

	checkboardColors[0] = color0;
	checkboardColors[1] = color1;

	for (int y = 0; y < height/2; y++)
	{
		for (int x = 0; x < width/2; x++)
		{
			*p0 = checkboardColors[0].GetValue();
			*p1 = checkboardColors[1].GetValue();
			*p2 = checkboardColors[1].GetValue();
			*p3 = checkboardColors[0].GetValue();

			++p0;
			++p1;
			++p2;
			++p3;
		}

		p0 += padding;
		p1 += padding;
		p2 += padding;
		p3 += padding;
	}

	Graphics::D3D10Texture2D tex(Graphics::Direct10::get_D3DDevice(), width, height, DXGI_FORMAT_R8G8B8A8_UNORM, mapped.pData, mapped.RowPitch);
	delete[] mapped.pData;

	return new Graphics::Bitmap(Graphics::Direct10::get_D3DDevice(), tex);
}

//////////////////////////////////////////
//

BrightnessContrastAdjustment::BrightnessContrastAdjustment()
{
}

double BrightnessContrastAdjustment::get_Brightness()
{
	return m_brightness;
}

void BrightnessContrastAdjustment::set_Brightness(double brightness)
{
	m_brightness = brightness;
//	PropertyChanged(this, WSTR("Brightness"));
}

double BrightnessContrastAdjustment::get_Contrast()
{
	return m_contrast;
}

void BrightnessContrastAdjustment::set_Contrast(double contrast)
{
	m_contrast = contrast;
//	PropertyChanged(this, WSTR("Brightness"));
}

//////////////////////////////////////////

class BlendCommand : public Object
{
public:
	CTOR BlendCommand()
	{
	}

	virtual void Render(Graphics::GraphicsO* pGraphics);

	Graphics::Bitmap* m_frameBuffer;

	IDirect3DSurface9* m_renderTarget;

	Graphics::Bitmap* m_bitmap;
	gm::RectF m_destRect;
	float m_srcX;
	float m_srcY;
	float m_srcWidth;
	float m_srcHeight;

	float m_opacity;
	uint32 m_blendMode;
	uint32 m_adjustmentMode;

	// Brightness/Contrast
	float m_brightness;
	float m_contrast;
};

void BlendCommand::Render(Graphics::GraphicsO* pGraphics)
{
	HRESULT hr;

	/*
	if (bitmap->m_texture == NULL)
	{
		bitmap->m_texture = m_device->CreateTexture2D(0, GL_RGBA, bitmap->GetWidth(), bitmap->GetHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, bitmap->m_bitmapData);
	}
	*/

	ASSERT(0);
#if 0
	pGraphics->EnsureEffectLoaded();

	pGraphics->m_device->SetPrimitiveTopology(GL_TRIANGLE_STRIP);
	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_res->m_vertexDeclaration1);

	LDraw::matrix4f modelView;
	pGraphics->m_device->GetFloatv(GL_MODELVIEW_MATRIX, (float*)modelView);

	LDraw::matrix4f projection;
	pGraphics->m_device->GetFloatv(GL_PROJECTION_MATRIX, (float*)projection);

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)LDraw::matrix4f::getIdentity());

//	matrix4f mat = matrix4f::getIdentity();
//	m_d3d9_effect->SetMatrix(m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)mat);

	//
//	D3DXHANDLE m_colorMatrixVariable = m_res->m_d3d9_effect->GetParameterByName(NULL, "colorMatrix");
//	D3DXHANDLE m_colorTranslateVariable = m_res->m_d3d9_effect->GetParameterByName(NULL, "colorTranslate");

//	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_vertexDeclaration1);

//	pGraphics->m_d3d9_effect->SetMatrix(pGraphics->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)matrix4f::getIdentity());

	/*
	LDraw::matrix4f colorMatrix(
		colorMatrix5x5.m[0][0], colorMatrix5x5.m[0][1], colorMatrix5x5.m[0][2], colorMatrix5x5.m[0][3],
		colorMatrix5x5.m[1][0], colorMatrix5x5.m[1][1], colorMatrix5x5.m[1][2], colorMatrix5x5.m[1][3],
		colorMatrix5x5.m[2][0], colorMatrix5x5.m[2][1], colorMatrix5x5.m[2][2], colorMatrix5x5.m[2][3],
		colorMatrix5x5.m[3][0], colorMatrix5x5.m[3][1], colorMatrix5x5.m[3][2], colorMatrix5x5.m[3][3]
		);

	m_res->m_d3d9_effect->SetMatrix(m_colorMatrixVariable, (D3DXMATRIX*)&colorMatrix);
	m_res->m_d3d9_effect->SetVector(m_colorTranslateVariable, (D3DXVECTOR4*)&colorMatrix5x5.m[4]);
	*/

	D3DXHANDLE vposScaleVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "vposScale");
	ASSERT(vposScaleVariable);

	if (m_frameBuffer)
	{
		float vposScale[4] = {1.0f / m_frameBuffer->GetWidth(), 1.0f / m_frameBuffer->GetHeight() };
		pGraphics->m_res->m_d3d9_effect->SetVector(vposScaleVariable, (D3DXVECTOR4*)vposScale);
	}

	D3DXHANDLE alphaMultiplyVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "alphaMultiply");
	ASSERT(alphaMultiplyVariable);

	D3DXHANDLE frameBufferTextureVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "frameBufferTexture");
	ASSERT(frameBufferTextureVariable);

	pGraphics->m_res->m_d3d9_effect->SetFloat(alphaMultiplyVariable, m_opacity);

	dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device)->m_d3dDevice->SetRenderTarget(0, m_renderTarget);

	if (m_frameBuffer)
	{
		hr = pGraphics->m_res->m_d3d9_effect->SetTexture(frameBufferTextureVariable, m_frameBuffer->m_texture.u.d3d);
		ASSERT(SUCCEEDED(hr));
	}

	if (m_adjustmentMode)
	{
		ASSERT(m_bitmap);
		pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, m_bitmap->m_texture.u.d3d);

		D3DXHANDLE colorTranslateVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "colorTranslate");
		ASSERT(colorTranslateVariable);
		D3DXVECTOR4 colorTranslate(m_brightness, m_brightness, m_brightness, m_brightness);
		pGraphics->m_res->m_d3d9_effect->SetVector(colorTranslateVariable, &colorTranslate);

		D3DXHANDLE colorContrastVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "colorContrast");
		ASSERT(colorContrastVariable);
		pGraphics->m_res->m_d3d9_effect->SetFloat(colorContrastVariable, m_contrast);

		D3DXHANDLE Technique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("BrightnessContrastTechnique");
		ASSERT(Technique);

		pGraphics->m_res->m_d3d9_effect->SetTechnique(Technique);
	}
	else
	{
		if (m_bitmap)
		{
			pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, m_bitmap->m_texture.u.d3d);
		}

		switch (m_blendMode)
		{
		case BLEND_NORM:
		{
			D3DXHANDLE BlendModeNormalTechnique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("BlendModeNormalTechnique");
			ASSERT(BlendModeNormalTechnique);

			pGraphics->m_res->m_d3d9_effect->SetTechnique(BlendModeNormalTechnique);
		//	pGraphics->m_res->m_d3d9_effect->SetTechnique(pGraphics->m_res->m_d3d9_RenderBitmapColorMatrixTechnique);
		}
		break;

		case BLEND_MUL:
		{
		//	pGraphics->m_res->m_d3d9_effect->SetTechnique(pGraphics->m_res->m_d3d9_technique1);
		//	pGraphics->m_res->m_d3d9_effect->SetTechnique(pGraphics->m_res->m_d3d9_RenderBitmapColorMatrixTechnique);

			D3DXHANDLE BlendModeMultiplyTechnique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("BlendModeMultiplyTechnique");
			ASSERT(BlendModeMultiplyTechnique);

			pGraphics->m_res->m_d3d9_effect->SetTechnique(BlendModeMultiplyTechnique);
		}
		break;

		case BLEND_DIFF:
		{
			D3DXHANDLE BlendModeDifferenceTechnique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("BlendModeDifferenceTechnique");
			ASSERT(BlendModeDifferenceTechnique);

			pGraphics->m_res->m_d3d9_effect->SetTechnique(BlendModeDifferenceTechnique);
		}
		break;

		}
	}

	float x = m_destRect.X;
	float y = m_destRect.Y;
	float width = m_destRect.Width;
	float height = m_destRect.Height;

	float texX = m_srcX / m_bitmap->GetWidth();
	float texY = m_srcY / m_bitmap->GetHeight();
	float texWidth = m_srcWidth / m_bitmap->GetWidth();
	float texHeight = m_srcHeight / m_bitmap->GetHeight();

	LDraw::VERTEX_XYZ_T2 vertices[4] =
	{
		{LDraw::vector3f(x, y, 0), LDraw::vector2f(texX, texY)},
		{LDraw::vector3f(x+width, y, 0), LDraw::vector2f(texX+texWidth, texY)},
		{LDraw::vector3f(x, y+height, 0), LDraw::vector2f(texX, texY+texHeight)},
		{LDraw::vector3f(x+width, y+height, 0), LDraw::vector2f(texX+texWidth, texY+texHeight)},
	};

	UINT nPasses;
	hr = pGraphics->m_res->m_d3d9_effect->Begin(&nPasses, 0);
	ASSERT(SUCCEEDED(hr));
	for (UINT nPass = 0; nPass < nPasses; ++nPass)
	{
		hr = pGraphics->m_res->m_d3d9_effect->BeginPass(nPass);
		ASSERT(SUCCEEDED(hr));

		pGraphics->m_device->DrawUP(4, vertices, sizeof(LDraw::VERTEX_XYZ_T2));

#if 0
		if (indexBuffer != NULL)
			m_device->DrawIndexed(0, count-1, count/*, GL_UNSIGNED_SHORT, m_indexOffset*/);
		else
			m_device->Draw(0, count);
#endif
		hr = pGraphics->m_res->m_d3d9_effect->EndPass();
		ASSERT(SUCCEEDED(hr));
	}
	hr = pGraphics->m_res->m_d3d9_effect->End();
	ASSERT(SUCCEEDED(hr));

//	hr = pGraphics->m_res->m_d3d9_effect->SetTexture(frameBufferTextureVariable, NULL);
//	ASSERT(SUCCEEDED(hr));
#endif
}


class BrushCommand : public Object
{
public:
	CTOR BrushCommand()
	{
	}

	virtual void Render(Graphics::GraphicsO* pGraphics);

//	LDraw::Bitmap* m_frameBuffer;
//	IDirect3DSurface9* m_renderTarget;

	Graphics::Bitmap* m_bitmap;
	Graphics::Bitmap* m_mask;
	gm::RectF m_destRect;
	float m_srcX;
	float m_srcY;
	float m_srcWidth;
	float m_srcHeight;

	float m_maskSrcX;
	float m_maskSrcY;
	float m_maskSrcWidth;
	float m_maskSrcHeight;

	float m_opacity;
	uint32 m_blendMode;
//	uint32 m_adjustmentMode;

	// Brightness/Contrast
//	float m_brightness;
//	float m_contrast;
};

void BrushCommand::Render(Graphics::GraphicsO* pGraphics)
{
	HRESULT hr;

	ASSERT(0);
#if 0

	/*
	if (bitmap->m_texture == NULL)
	{
		bitmap->m_texture = m_device->CreateTexture2D(0, GL_RGBA, bitmap->GetWidth(), bitmap->GetHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, bitmap->m_bitmapData);
	}
	*/

	pGraphics->EnsureEffectLoaded();

	pGraphics->m_device->SetPrimitiveTopology(GL_TRIANGLE_STRIP);
	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_res->m_vertexDeclaration2);

	LDraw::matrix4f modelView;
	pGraphics->m_device->GetFloatv(GL_MODELVIEW_MATRIX, (float*)modelView);

	LDraw::matrix4f projection;
	pGraphics->m_device->GetFloatv(GL_PROJECTION_MATRIX, (float*)projection);

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)LDraw::matrix4f::getIdentity());

//	matrix4f mat = matrix4f::getIdentity();
//	m_d3d9_effect->SetMatrix(m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)mat);

	//
//	D3DXHANDLE m_colorMatrixVariable = m_res->m_d3d9_effect->GetParameterByName(NULL, "colorMatrix");
//	D3DXHANDLE m_colorTranslateVariable = m_res->m_d3d9_effect->GetParameterByName(NULL, "colorTranslate");

//	D3DXHANDLE texelsPerPixelVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "texelsPerPixel");
//	ASSERT(texelsPerPixelVariable);
//	float texelsPerPixel[4] = {1.0f / m_bitmap->GetWidth(), 1.0f / m_bitmap->GetHeight()};
//	pGraphics->m_res->m_d3d9_effect->SetVector(texelsPerPixelVariable, (D3DXVECTOR4*)texelsPerPixel);

//	pGraphics->m_d3d9_effect->SetMatrix(pGraphics->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)matrix4f::getIdentity());

	/*
	LDraw::matrix4f colorMatrix(
		colorMatrix5x5.m[0][0], colorMatrix5x5.m[0][1], colorMatrix5x5.m[0][2], colorMatrix5x5.m[0][3],
		colorMatrix5x5.m[1][0], colorMatrix5x5.m[1][1], colorMatrix5x5.m[1][2], colorMatrix5x5.m[1][3],
		colorMatrix5x5.m[2][0], colorMatrix5x5.m[2][1], colorMatrix5x5.m[2][2], colorMatrix5x5.m[2][3],
		colorMatrix5x5.m[3][0], colorMatrix5x5.m[3][1], colorMatrix5x5.m[3][2], colorMatrix5x5.m[3][3]
		);

	m_res->m_d3d9_effect->SetMatrix(m_colorMatrixVariable, (D3DXMATRIX*)&colorMatrix);
	m_res->m_d3d9_effect->SetVector(m_colorTranslateVariable, (D3DXVECTOR4*)&colorMatrix5x5.m[4]);
	*/

	/*
	D3DXHANDLE vposScaleVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "vposScale");
	ASSERT(vposScaleVariable);

	if (m_frameBuffer)
	{
		float vposScale[4] = {1.0f / m_frameBuffer->GetWidth(), 1.0f / m_frameBuffer->GetHeight() };
		pGraphics->m_res->m_d3d9_effect->SetVector(vposScaleVariable, (D3DXVECTOR4*)vposScale);
	}

	D3DXHANDLE alphaMultiplyVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "alphaMultiply");
	ASSERT(alphaMultiplyVariable);

	D3DXHANDLE frameBufferTextureVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "frameBufferTexture");
	ASSERT(frameBufferTextureVariable);
	*/

//	pGraphics->m_res->m_d3d9_effect->SetFloat(alphaMultiplyVariable, m_opacity);
//	dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device)->m_d3dDevice->SetRenderTarget(0, m_renderTarget);
/*
	if (m_frameBuffer)
	{
		hr = pGraphics->m_res->m_d3d9_effect->SetTexture(frameBufferTextureVariable, m_frameBuffer->m_texture.u.d3d);
		ASSERT(SUCCEEDED(hr));
	}
*/
	{
		if (m_bitmap)
		{
			pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, m_bitmap->m_texture.u.d3d);
		}

		if (m_mask)
		{
			D3DXHANDLE texture1Variable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "texture1");
			ASSERT(texture1Variable);

			pGraphics->m_res->m_d3d9_effect->SetTexture(texture1Variable, m_mask->m_texture.u.d3d);

			D3DXHANDLE Technique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("BrushMaskTechnique");
			ASSERT(Technique);

			pGraphics->m_res->m_d3d9_effect->SetTechnique(Technique);
		//	pGraphics->m_res->m_d3d9_effect->SetTechnique(pGraphics->m_res->m_d3d9_RenderBitmapColorMatrixTechnique);
		}
		else
		{
			D3DXHANDLE Technique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("BrushTechnique");
			ASSERT(Technique);

			pGraphics->m_res->m_d3d9_effect->SetTechnique(Technique);
		}
	}

	float x = m_destRect.X;
	float y = m_destRect.Y;
	float width = m_destRect.Width;
	float height = m_destRect.Height;

	float texX = m_srcX / m_bitmap->GetWidth();
	float texY = m_srcY / m_bitmap->GetHeight();
	float texWidth = m_srcWidth / m_bitmap->GetWidth();
	float texHeight = m_srcHeight / m_bitmap->GetHeight();

	if (m_mask)
	{
		float tex1X = m_maskSrcX / m_mask->GetWidth();
		float tex1Y = m_maskSrcY / m_mask->GetHeight();
		float tex1Width = m_maskSrcWidth / m_mask->GetWidth();
		float tex1Height = m_maskSrcHeight / m_mask->GetHeight();

		LDraw::VERTEX_XYZ_T2_T2 vertices[4] =
		{
			{LDraw::vector3f(x, y, 0), LDraw::vector2f(texX, texY), LDraw::vector2f(tex1X, tex1Y)},
			{LDraw::vector3f(x+width, y, 0), LDraw::vector2f(texX+texWidth, texY), LDraw::vector2f(tex1X+tex1Width, tex1Y)},
			{LDraw::vector3f(x, y+height, 0), LDraw::vector2f(texX, texY+texHeight), LDraw::vector2f(tex1X, tex1Y+tex1Height)},
			{LDraw::vector3f(x+width, y+height, 0), LDraw::vector2f(texX+texWidth, texY+texHeight), LDraw::vector2f(tex1X+tex1Width, tex1Y+tex1Height)},
		};

		UINT nPasses;
		hr = pGraphics->m_res->m_d3d9_effect->Begin(&nPasses, 0);
		ASSERT(SUCCEEDED(hr));
		for (UINT nPass = 0; nPass < nPasses; ++nPass)
		{
			hr = pGraphics->m_res->m_d3d9_effect->BeginPass(nPass);
			ASSERT(SUCCEEDED(hr));

			pGraphics->m_device->DrawUP(4, vertices, sizeof(LDraw::VERTEX_XYZ_T2_T2));

			hr = pGraphics->m_res->m_d3d9_effect->EndPass();
			ASSERT(SUCCEEDED(hr));
		}
		hr = pGraphics->m_res->m_d3d9_effect->End();
		ASSERT(SUCCEEDED(hr));
	}
	else
	{
		LDraw::VERTEX_XYZ_T2 vertices[4] =
		{
			{LDraw::vector3f(x, y, 0), LDraw::vector2f(texX, texY)},
			{LDraw::vector3f(x+width, y, 0), LDraw::vector2f(texX+texWidth, texY)},
			{LDraw::vector3f(x, y+height, 0), LDraw::vector2f(texX, texY+texHeight)},
			{LDraw::vector3f(x+width, y+height, 0), LDraw::vector2f(texX+texWidth, texY+texHeight)},
		};

		UINT nPasses;
		hr = pGraphics->m_res->m_d3d9_effect->Begin(&nPasses, 0);
		ASSERT(SUCCEEDED(hr));
		for (UINT nPass = 0; nPass < nPasses; ++nPass)
		{
			hr = pGraphics->m_res->m_d3d9_effect->BeginPass(nPass);
			ASSERT(SUCCEEDED(hr));

			pGraphics->m_device->DrawUP(4, vertices, sizeof(LDraw::VERTEX_XYZ_T2));

			hr = pGraphics->m_res->m_d3d9_effect->EndPass();
			ASSERT(SUCCEEDED(hr));
		}
		hr = pGraphics->m_res->m_d3d9_effect->End();
		ASSERT(SUCCEEDED(hr));
	}
#endif
}

/////////////////////////////////////
// Element

Element::Element(ImageDocument* document) :
	m_document(document),
	m_transform(gm::matrix3f::getIdentity())
{
	m_visible = true;
	m_opacity = 1.0;

	//m_transform = LDraw::matrix3f::getIdentity();
}

double Element::get_Opacity()
{
	return m_opacity;
}

void Element::set_Opacity(double opacity)
{
	m_opacity = opacity;
//	PropertyChanged(this, WSTR("Opacity"));
}

/////////////////////////////////////////////////
// Group

Group::Group(ImageDocument* document) : Element(document)
{
	ASSERT(0);
//	m_subObjects = new ObservableCollection<Element*>;
}

Graphics::Bitmap* Group::get_Bitmap()
{
	return m_offscreenBitmap;
}

Group* Group::Clone()
{
	ASSERT(0);
	Group* p = new Group(m_document);
#if 0
	int count = m_subObjects->get_Count();
	for (int i = 0; i < count; i++)
	{
		Element* child = m_subObjects->get_Item(i);
		child->AddRef();
		p->m_subObjects->Add(child);
	}
#endif
	return p;
}

//int Group::Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics)
int Group::Render(ID3D10RenderTargetView* renderTarget, ID3D10RenderTargetView* renderTarget2, Graphics::Bitmap* targetBitmap, Graphics::Bitmap* targetBitmap2, Gui::ManagedRenderContext pGraphics)
{
	ASSERT(0);
	return 0;
}

/////////////////////////////////////////////////
// AdjustmentLayer

AdjustmentLayer::AdjustmentLayer(ImageDocument* document) : Element(document)
{
}

Element* AdjustmentLayer::Clone()
{
	ASSERT(0);
	return NULL;
}

Adjustment* AdjustmentLayer::get_Adjustment()
{
	return m_adjustment;
}

#if 0
void AdjustmentLayer::OnAdjustmentPropertyChanged(Object* sender, StringW* propertyName)
{
	//PropertyChanged(this, "AdjustmentSettings");
	list<BitmapEditor*>::iterator it = m_document->m_views.begin();
	while (it != m_document->m_views.end())
	{
		(*it)->Invalidate();
		++it;
	}
}
#endif

Graphics::Bitmap* AdjustmentLayer::get_Bitmap()
{
	return NULL;
}

int AdjustmentLayer::Render(ID3D10RenderTargetView* renderTarget, ID3D10RenderTargetView* renderTarget2, Graphics::Bitmap* targetBitmap, Graphics::Bitmap* targetBitmap2, Gui::ManagedRenderContext pGraphics)
{
#if 0
	BlendCommand* pCmd = new BlendCommand;

	pCmd->m_renderTarget = renderTarget2;
//	pCmd->m_frameBuffer = targetBitmap;
	pCmd->m_frameBuffer = NULL;

	/*
	pCmd->m_bitmap = m_bitmap;
//	pCmd->m_destRect = LDraw::RectF(0, 0, (float)m_bitmap->GetWidth(), (float)m_bitmap->GetHeight());
	pCmd->m_destRect = LDraw::RectF(0, 0, (float)targetBitmap->GetWidth(), (float)targetBitmap->GetHeight());
	pCmd->m_srcX = 0;
	pCmd->m_srcY = 0;
	pCmd->m_srcWidth = m_bitmap->GetWidth();
	pCmd->m_srcHeight = m_bitmap->GetHeight();
	*/

//	pCmd->m_bitmap = NULL;//m_bitmap;
	pCmd->m_bitmap = targetBitmap;//m_bitmap;
//	pCmd->m_destRect = LDraw::RectF(0, 0, (float)m_bitmap->GetWidth(), (float)m_bitmap->GetHeight());
	pCmd->m_destRect = LDraw::RectF(0, 0, (float)targetBitmap->GetWidth(), (float)targetBitmap->GetHeight());
//	pCmd->m_srcX = -m_x;
//	pCmd->m_srcY = -m_y;
	pCmd->m_srcX = 0;
	pCmd->m_srcY = 0;
	pCmd->m_srcWidth = targetBitmap->GetWidth();
	pCmd->m_srcHeight = targetBitmap->GetHeight();

	BrightnessContrastAdjustment* adjustment = dynamic_cast<BrightnessContrastAdjustment*>(m_adjustment);

	pCmd->m_opacity = float(m_opacity);
	pCmd->m_blendMode = m_blendMode;
	pCmd->m_adjustmentMode = ADJUST_BRIGHTNESS;
	pCmd->m_brightness = adjustment->m_brightness;
	pCmd->m_contrast = adjustment->m_contrast+1;

	dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands->AddCommand(pCmd);
#endif

	return 1;
}

///////////////////////////

ElementMask::ElementMask()
{
}

ElementMask::ElementMask(Element* element)
{
	m_element = element;
}

VisualMask::VisualMask()
{
}

VisualMask::VisualMask(Gui::Visual* visual)
{
	m_visual = visual;
}

/////////////////////////////////////////////////
// BitmapLayer

BitmapLayer::BitmapLayer(ImageDocument* document) : Layer(document)
{
//	m_paintBrush = new PaintBrush;
//	m_paintBrush->SetCircular();
}

BitmapLayer* BitmapLayer::Clone()
{
	ASSERT(0);
	return NULL;
}

void FillAlpha(int width, int height, int rowBytes, void* pv, uint8 value)
{
	uint8* pb = (uint8*)pv;
	int size = width*height;
	while (size--)
	{
		pb[3] = value;
		pb += 4;
	}

	/*
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
		}
	}
	*/
}

void Premultiply(int width, int height, int rowBytes, void* pv)
{
	uint8* pb = (uint8*)pv;
	int size = width*height;
	while (size--)
	{
		pb[0] = pb[0] * pb[3] / 255;
		pb[1] = pb[1] * pb[3] / 255;
		pb[2] = pb[2] * pb[3] / 255;
		pb += 4;
	}
}

void BitmapLayer::CreateR16F(int width, int height)
{
	ASSERT(0);
#if 0

	m_bitmap = new LDraw::Bitmap(width, height, width, LDraw::PixelFormat_t::GRAY_8, NULL);
	m_bitmap->m_d3dDevice = UI::GetD3DDevice9();

	//m_bitmap->m_d3dDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R16F, D3DPOOL_MANAGED, &m_bitmap->m_texture.u.d3d, NULL);
	m_bitmap->m_d3dDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R16F, D3DPOOL_DEFAULT, &m_bitmap->m_texture.u.d3d, NULL);
	m_bitmap->m_d3dTexture = m_bitmap->m_texture.u.d3d;
#endif
}

void BitmapLayer::CreateA8R8G8B8(int width, int height)
{
	ASSERT(0);
#if 0

	m_bitmap = new LDraw::Bitmap(width, height, width*4, LDraw::PixelFormat_t::RGBAP_32, NULL);
	m_bitmap->m_d3dDevice = UI::GetD3DDevice9();

	m_bitmap->m_d3dDevice->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_bitmap->m_texture.u.d3d, NULL);
	m_bitmap->m_d3dTexture = m_bitmap->m_texture.u.d3d;
#endif
}

Graphics::Bitmap* BitmapLayer::get_ThumbnailBitmap()
{
	return m_bitmap;
}

int BitmapLayer::Render(ID3D10RenderTargetView* renderTarget, ID3D10RenderTargetView* renderTarget2, Graphics::Bitmap* targetBitmap, Graphics::Bitmap* targetBitmap2, Gui::ManagedRenderContext pGraphics)
{
#if 0
	if (m_bitmap)
	{
		BlendCommand* pCmd = new BlendCommand;

		/*
		pCmd->m_bitmap = m_bitmap;
	//	pCmd->m_destRect = LDraw::RectF(0, 0, (float)m_bitmap->GetWidth(), (float)m_bitmap->GetHeight());
		pCmd->m_destRect = LDraw::RectF(0, 0, (float)targetBitmap->GetWidth(), (float)targetBitmap->GetHeight());
		pCmd->m_srcX = 0;
		pCmd->m_srcY = 0;
		pCmd->m_srcWidth = m_bitmap->GetWidth();
		pCmd->m_srcHeight = m_bitmap->GetHeight();
		*/

		pCmd->m_bitmap = m_bitmap;
	//	pCmd->m_destRect = LDraw::RectF(0, 0, (float)m_bitmap->GetWidth(), (float)m_bitmap->GetHeight());
		pCmd->m_destRect = LDraw::RectF(0, 0, (float)targetBitmap->GetWidth(), (float)targetBitmap->GetHeight());
		pCmd->m_srcX = -m_x;
		pCmd->m_srcY = -m_y;
		pCmd->m_srcWidth = targetBitmap->GetWidth();
		pCmd->m_srcHeight = targetBitmap->GetHeight();

		pCmd->m_opacity = float(m_opacity);
		pCmd->m_blendMode = m_blendMode;

		dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands->AddCommand(pCmd);

		if (m_blendMode == BLEND_NORM)
		{
			pCmd->m_renderTarget = renderTarget;
			pCmd->m_frameBuffer = targetBitmap2;
			return 0;
		}
		else
		{
			pCmd->m_renderTarget = renderTarget2;
			pCmd->m_frameBuffer = targetBitmap;
			return 1;
		}

#if 0
		// opacity
		LDraw::ColorMatrixF colorMatrix(	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
														0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
														0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
														0.0f, 0.0f, 0.0f, float(m_opacity), 0.0f,
														0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

		pGraphics->DrawImage(m_bitmap, LDraw::RectF(0, 0, (float)m_bitmap->GetWidth(), (float)m_bitmap->GetHeight()), 0, 0, m_bitmap->GetWidth(), m_bitmap->GetHeight(), LDraw::WrapModeClamp, &colorMatrix);
#endif
	}

	float width = 20;
	float height = 20;
//	float x = width/2;
//	float y = height/2;

	/*
	for (int i = 0; i < m_points.size(); i++)
	{
		pGraphics->DrawImage(
			m_paintBrush->m_bitmap,
			LDraw::RectF(m_points[i].X - width/2, m_points[i].Y - height/2, width, height),
			0, 0, m_paintBrush->m_bitmap->GetWidth(), m_paintBrush->m_bitmap->GetHeight());
	}
	*/
#endif

	return 0;
}

#if 0
UI::Histogram* BitmapLayer::get_Histogram()
{
	if (m_histogram == NULL)
	{
		m_histogram = new Histogram(m_bitmap);
	}

	return m_histogram;
}
#endif

/*
///////////////////////////////////////
// ShapesLayer

ShapesLayer::ShapesLayer()
{
}

void ShapesLayer::Render(IDirect3DSurface9* renderTarget, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics)
{
}

LDraw::Bitmap* ShapesLayer::get_Bitmap()
{
	return m_bitmap;
}

LDraw::Bitmap* ShapesLayer::get_ThumbnailBitmap()
{
	return m_bitmap;
}
*/

//Gui::DependencyClass BitmapEditor::Class(typeid(BitmapEditor));

PaintBrush* brush;

Gui::DependencyClass* BElement::get_Class()
{
	static Gui::DependencyClass Class(typeid(BElement), Visual::get_Class());
	return &Class;
}

BElement::BElement(Gui::DependencyClass* depClass) : Gui::Visual(depClass)
{
}

/*
gm::vector4f globalColor(0, 0, 0, 1.0f);
//float globalBrushSize = 40;

IMAGEEDITEXT void SetGlobalColor(float r, float g, float b)
{
	globalColor[0] = r;
	globalColor[1] = g;
	globalColor[2] = b;
}
*/

/*
IMAGEEDITEXT void SetGlobalBrushSize(float size)
{
	globalBrushSize = size;
}
*/

//BElement* currentMask;

/*
//ImageTool* m_tool = new PaintBrushTool;
IMAGEEDITEXT void SetTool(ImageTool* tool)
{
	m_tool = tool;
}
*/

//RectangularSelectionTool* 

/*
IMAGEEDITEXT void SetGlobalOpacity(float a)
{
	globalColor[3] = a;
}
*/

IMAGEEDITEXT Graphics::Bitmap* CreateBitmap(uint width, uint height, DXGI_FORMAT pixelFormat)
{
	// Create the render target texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
//	desc.Usage = D3D10_USAGE_DYNAMIC;

//	desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
//	desc.CPUAccessFlags |= D3D10_CPU_ACCESS_READ;

	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
//	desc.MiscFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	HRESULT hr = Graphics::Direct10::get_D3DDevice()->CreateTexture2D(&desc, NULL, &pTexture);

	Graphics::Bitmap* bitmap = new Graphics::Bitmap(Graphics::Direct10::get_D3DDevice(), pTexture);

	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // RGBA
	Graphics::Direct10::get_DeviceContext()->ClearRenderTargetView(bitmap->m_d3d10_renderTargetView, clearColor);

	return bitmap;
}

IMAGEEDITEXT Gui::Visual* Ellipse()
{
	Gui::FillGeometryVisual* g = new Gui::FillGeometryVisual();
	g->set_Geometry(new Gui::EllipseGeometry(160, 160, 140, 90));
	g->set_Brush(new Gui::SolidColorBrush(1, 0, 0, 1));
	return g;
}

ID3DX11Effect* MaskOutlineVisual::m_effect;
ID3DX11EffectTechnique* MaskOutlineVisual::m_renderSelectionTechnique;
ID3DX11EffectMatrixVariable* MaskOutlineVisual::m_modelViewProjectionVariable;
ID3DX11EffectMatrixVariable* MaskOutlineVisual::m_texture0MatrixVariable;
ID3DX11EffectVectorVariable* MaskOutlineVisual::m_texture1TranslateVariable;
ID3DX11EffectShaderResourceVariable* MaskOutlineVisual::m_texture0Variable;
ID3DX11EffectShaderResourceVariable* MaskOutlineVisual::m_texture1Variable;
ID3DX11EffectVectorVariable* MaskOutlineVisual::m_texelsPerPixelVariable;
ID3D11InputLayout* MaskOutlineVisual::m_vertexLayout0;

ID3DX11Effect* StrokeVisual::m_effect;
ID3DX11EffectTechnique* StrokeVisual::m_RenderTextureTechnique;

ID3DX11EffectMatrixVariable* StrokeVisual::m_modelViewVariable;
ID3DX11EffectMatrixVariable* StrokeVisual::m_projectionVariable;
ID3DX11EffectMatrixVariable* StrokeVisual::m_modelViewProjectionVariable;
ID3DX11EffectMatrixVariable* StrokeVisual::m_textureMatrix0Variable;
ID3DX11EffectMatrixVariable* StrokeVisual::m_textureMatrix1Variable;
ID3DX11EffectShaderResourceVariable* StrokeVisual::m_texture0Variable;
ID3DX11EffectShaderResourceVariable* StrokeVisual::m_texture1Variable;
ID3DX11EffectVectorVariable* StrokeVisual::m_colorTranslateVariable;
ID3DX11EffectVectorVariable* StrokeVisual::m_colorMultiplyVariable;

//ID3D10EffectVectorVariable* StrokeVisual::m_texelsPerPixelVariable;
ID3D11InputLayout* StrokeVisual::m_vertexLayout0;

IMAGEEDITEXT void Edit(Graphics::Bitmap* bitmap)
{
}

//HandTool* Tools::m_handTool = new HandTool;
//PaintBrushTool* Tools::m_paintbrushTool = new PaintBrushTool;

ID3D10PixelShader* m_normalShader;
ID3D10PixelShader* m_multiplyShader;
ID3D10PixelShader* m_screenShader;
ID3D10PixelShader* m_overlayShader;

void LoadEf()
{
	ID3D10Blob* pShader;
	ComPtr<ID3D10Blob> pError;

	HRESULT hr;
	hr = D3DX10CompileFromFile(IO::Path::Combine(IO::Path::GetDirectoryName(_Module.GetFullPath()), "..\\..\\..\\normal.ps").c_strw(), NULL, NULL, "main", "ps_4_0", D3D10_SHADER_OPTIMIZATION_LEVEL3, 0, NULL, &pShader, &pError, NULL);
//	hr = D3D10CompileShader(NULL, 0, IO::Path::Combine(IO::Path::GetDirectoryName(_Module.GetFullPath()), "..\\..\\..\\multiply.ps").c_str(), NULL, NULL, "main", "ps_3_0", D3D10_SHADER_OPTIMIZATION_LEVEL3, &pShader, &pError);
//	hr = D3D10CompileShader(NULL, 0, IO::Path::Combine(IO::Path::GetDirectoryName(_Module.GetFullPath()), "..\\..\\..\\screen.ps").c_str(), NULL, NULL, "main", "ps_3_0", D3D10_SHADER_OPTIMIZATION_LEVEL3, &pShader, &pError);

	Graphics::Direct10::get_D3DDevice()->CreatePixelShader(pShader->GetBufferPointer(), pShader->GetBufferSize(), &m_normalShader);
}

}	// ImageEdit
}	// System
