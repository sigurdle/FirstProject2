#include "stdafx.h"
#include "X3D2.h"
#include "ImageTexture.h"

namespace System
{
namespace x3d
{

//extern ID3D10EffectScalarVariable* m_d3d10_ntexturesVariable;
//extern ID3D10EffectShaderResourceVariable* m_d3d10_texturesVariable;

#if 0
X3DFieldDefinition ImageTextureFields[] =
{
	X3DFieldDefinition(WSTR("metadata"), FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	X3DFieldDefinition(WSTR("repeatS"),	FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	X3DFieldDefinition(WSTR("repeatT"),	FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	X3DFieldDefinition(WSTR("url"), FieldType_MFString/*MFURL*/, SAIFieldAccess_inputOutput,-1),
	/*
	MFString [in,out] url     []   [urn]
	SFBool  []       repeatS TRUE
	SFBool  []       repeatT TRUE
  */
};

NodeType ImageTexture::s_nodeType("ImageTexture", typeid(ImageTexture), ImageTextureFields, _countof(ImageTextureFields));
#endif

NodeType* ImageTexture::nodeType(GetNodeType());

NodeType* ImageTexture::GetNodeType()
{
	static X3DFieldDefinition repeatS("repeatS", FieldType_SFBool, SAIFieldAccess_initializeOnly, offsetof(ImageTexture, m_repeatS));
	static X3DFieldDefinition repeatT("repeatT", FieldType_SFBool, SAIFieldAccess_initializeOnly, offsetof(ImageTexture, m_repeatT));
	static X3DFieldDefinition url("url", FieldType_MFString/*MFURL*/, SAIFieldAccess_inputOutput, offsetof(ImageTexture, m_url));

	static X3DFieldDefinition* fields[] =
	{
		&repeatS,
		&repeatT,
		&url,
		/*
		MFNode  [in]     addChildren             [X3DChildNode]
		MFNode  [in]     removeChildren          [X3DChildNode]
		MFNode  [in,out] children       []       [X3DChildNode]
		SFVec3f []       bboxCenter     0 0 0    (-8,8)
		SFVec3f []       bboxSize       -1 -1 -1 (0,8) or -1 -1 -1
		*/
	};

	static NodeType nodeType(WSTR("ImageTexture"), typeid(ImageTexture), fields, _countof(fields), X3DTexture2DNode::GetNodeType());
	return &nodeType;
}

ImageTexture::ImageTexture() : X3DTexture2DNode(GetNodeType()),
	m_url(new MFString(this)),
	m_repeatS(new SFBool(this, true)),
	m_repeatT(new SFBool(this, true))
{
//	m_pVideoFilter = NULL;

//	m_texName = 0;
	m_status = 0;

//	m_pVideoFilter = new CVideoFilter;
//		m_pVideoFilter->m_pTexture = this;

// Cache pointers to relevant fields
//	m_url = static_cast<MFString*>(getField(WSTR("url")));
//	m_repeatS = static_cast<SFBool*>(getField(WSTR("repeatS")));
//	m_repeatT = static_cast<SFBool*>(getField(WSTR("repeatT")));

// Set default values
//	SFBool* repeatS = static_cast<SFBool*>(m_repeatS);
//	SFBool* repeatT = static_cast<SFBool*>(m_repeatT);

//	m_repeatS->m_value = true;
//	m_repeatT->m_value = true;
}

ImageTexture::~ImageTexture()
{
	/*
	if (m_pVideoFilter)
	{
		delete m_pVideoFilter;
		m_pVideoFilter = NULL;
	}
	*/
}

//CVideoFilter* m_pVideoFilter;

void ImageTexture::CreateTexture(Graphics::RenderTarget* pGraphics)
{
	if (m_status == 0)
	{
	//	SFBool* repeatS = static_cast<SFBool*>(m_repeatS);
	//	SFBool* repeatT = static_cast<SFBool*>(m_repeatT);

		if (m_url->get_size() > 0)
		{
		//	CLMFURL::CURL& url = m_url->m_items[0];
			String url = m_url->get1Value(0);

			if (false)//url.od)
			{
#if 0
				CComPtr<IUnknown> unk;
				m_pScene->m_bifsContext->FindODById(url.od, &unk);
				<ILBaseFilter> filter = unk;
				if (filter)
				{
					m_status = 1;

					ASSERT(0);
#if 0
					// TODO
					CComPtr<ILPin> outpin;
					filter->GetPin(1, &outpin);

					outpin->Connect(m_pVideoFilter->m_pInput, NULL);

					filter->Run(0);
#endif
				}
#endif
			}
			else if (true)
			{
				m_status = 1;

				//	MessageBox(NULL, _bstr_t(url->m_v), "", MB_OK);

			//	sysstring url0 = url;//.string;
			//	m_pScene->m_url;

				/*
				TCHAR fullurl[512];
				{
					DWORD resultLen = sizeof(fullurl);
				//	InternetCombineUrl(ConvertS2A(m_pScene->m_url).c_str(), ConvertS2A(url0).c_str(), fullurl, &resultLen, 0);
				}
				*/
				FilePath filepath(m_scene->getWorldURL());

				filepath.set_NameExt(Filename(url));

				if (filepath.get_Ext() == "svg")
				{
					MessageBeep(-1);
				}
				else
				{
					Graphics::Bitmap* bitmap = Graphics::Bitmap::FromFile(filepath.get_FullPath());

					if (bitmap != NULL)//pBitmap->GetLastStatus() == LDraw::Ok)
					{
						m_status = -1;

						m_bitmap = bitmap;
						m_width = bitmap->GetWidth();
						m_height = bitmap->GetHeight();

#if 0
						pGraphics->GenTextures(1, &m_texName);

//							ASSERT(glError == GL_NO_ERROR);

						pGraphics->BindTexture(GL_TEXTURE_2D, m_texName);
//							ASSERT(glGetError() == GL_NO_ERROR);

#if USE_GL
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (m_repeatS->m_value)? GL_REPEAT : GL_CLAMP);
						ASSERT(glGetError() == GL_NO_ERROR);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (m_repeatT->m_value)? GL_REPEAT : GL_CLAMP);
						ASSERT(glGetError() == GL_NO_ERROR);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
						ASSERT(glGetError() == GL_NO_ERROR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
						ASSERT(glGetError() == GL_NO_ERROR);
#endif

						m_width = bitmap->GetWidth();
						m_height = bitmap->GetHeight();

						pGraphics->TexImage2D(GL_TEXTURE_2D, bitmap);
#endif
					}
				}
			}
		}
	}
}

void ImageTexture::ApplyTexture(Gui::ImmediateRenderContext* renderContext)
{
	Graphics::Direct3D10_I* pD10 = renderContext->GetRT()->m_d3d10;
	Graphics::OpenGL_I* pGL = renderContext->GetRT()->m_opengl;

	if (pD10)
	{
		if (m_bitmap)
		{
			pD10->m_d3d10_ntexturesVariable->SetInt(1);
			pD10->m_d3d10_texturesVariable->SetResourceArray(&m_bitmap->m_d3d10_shaderResourceView, 0, 1);
		}
	}
	else
	{
		ASSERT(0);
	}

#if 0
	if (m_status == -1)
	{
		pGraphics->BindTexture(GL_TEXTURE_2D, m_texName);
	//	ASSERT(glGetError() == GL_NO_ERROR);

		pGraphics->Enable(GL_TEXTURE_2D);
	//	ASSERT(glGetError() == GL_NO_ERROR);

		pGraphics->TexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//		ASSERT(glGetError() == GL_NO_ERROR);
	}
#endif
}

}	// x3d
}	// System
