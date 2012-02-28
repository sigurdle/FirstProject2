#ifndef x3d_MultiTexture_h
#define x3d_MultiTexture_h

namespace System
{
namespace x3d
{

class X3DEXT MultiTexture : 
	public X3DTextureNode,
	public X3DTextureNodeImplImpl
{
public:
	CTOR MultiTexture();
	~MultiTexture();

	//Gluint* m_texNames;

// CLX3DTextureNodeImplImpl
	virtual int GetWidth()
	{
		return 0;
		/*
		if (m_pVideoFilter->m_pInput->m_mediaType)
		{
			long width;
			m_pVideoFilter->m_pInput->m_mediaType->GetWidth(&width);

			return width;
		}
		else
			return 0;
			*/
	}

	virtual int GetHeight()
	{
		return 0;
		/*
		if (m_pVideoFilter->m_pInput->m_mediaType)
		{
			long height;
			m_pVideoFilter->m_pInput->m_mediaType->GetHeight(&height);

			return height;
		}
		else
			return 0;
			*/
	}

	virtual void* GetData()
	{
		return NULL;
		/*
		if (m_pVideoFilter->m_pInput->m_pSample)
			return m_pVideoFilter->m_pInput->m_pSample->m_bits;
		else
			return NULL;
			*/
	}

	virtual void CreateTexture(Gui::ImmediateRenderContext* pGraphics);

	virtual void ApplyTexture(Gui::ImmediateRenderContext* pGraphics);

	static NodeType s_nodeType;

	/*
	SFFloat  [in,out] alpha            1     [0,1]
	SFColor  [in,out] color            1 1 1 [0,1] 
	MFString [in,out] function         []
	MFString [in,out] mode             []
	MFString [in,out] source           []
	MFNode   [in,out] texture          []    [X3DTextureNode]
	SFBool   [in,out] transparent      FALSE
  */

protected:

	MFNode* m_texture;
	MFString* m_mode;
	MFString* m_source;
};

}	// x3d
}

#endif // x3d_MultiTexture_h
