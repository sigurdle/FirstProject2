#ifndef x3d_ImageTexture_h
#define x3d_ImageTexture_h

namespace System
{
namespace x3d
{

class X3DEXT ImageTexture : 
	public X3DTexture2DNode,
	public X3DTextureNodeImplImpl
{
public:
	CTOR ImageTexture();
	~ImageTexture();

	virtual int GetWidth()
	{
		return m_width;
	}

	virtual int GetHeight()
	{
		return m_height;
	}

	/*
	virtual void* GetData()
	{
		if (m_pVideoFilter->m_pInput->m_pSample)
			return m_pVideoFilter->m_pInput->m_pSample->m_bits;
		else
			return NULL;
	}
	*/

	virtual void CreateTexture(Graphics::RenderTarget* rt) override;
	virtual void ApplyTexture(Gui::ImmediateRenderContext* pGraphics) override;

	Graphics::Bitmap* GetData()
	{
		return m_bitmap;
	}

public:

//	CVideoFilter* m_pVideoFilter;

	X3DMFIELD(MFString, url, Url)
	X3DSFIELD(SFBool, repeatS, RepeatS)
	X3DSFIELD(SFBool, repeatT, RepeatT)

	X3DNODE(ImageTexture, X3DTexture2DNode)

	/*
	MFString [in,out] url     []   [urn]
	SFBool  []       repeatS TRUE
	SFBool  []       repeatT TRUE
  */

	Graphics::Bitmap* m_bitmap;
	//unsigned int m_texName;
//	ID3D10Texture2D* m_texture;	// TODO remove
//	ID3D10ShaderResourceView* m_textureView;	// TODO remove

	int m_status;
	int m_width;
	int m_height;
};

}	// x3d
}

#endif // x3d_ImageTexture_h
