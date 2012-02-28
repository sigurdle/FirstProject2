#include "stdafx.h"
#include "X3D2.h"
#include "MultiTexture.h"
#include "ImageTexture.h"

#include <algorithm>

namespace System
{
namespace x3d
{

X3DFieldDefinition* MultiTextureFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("mode", FieldType_MFString, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("source", FieldType_MFString, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("texture", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	/*
	SFFloat  [in,out] alpha            1     [0,1]
	SFColor  [in,out] color            1 1 1 [0,1] 
	MFString [in,out] function         []
	MFString [in,out] mode             []
	MFString [in,out] source           []
	MFNode   [in,out] texture          []    [X3DTextureNode]
	SFBool   [in,out] transparent      FALSE
	*/
};

NodeType MultiTexture::s_nodeType(WSTR("MultiTexture"), typeid(MultiTexture), MultiTextureFields, _countof(MultiTextureFields));

MultiTexture::MultiTexture() : X3DTextureNode(&s_nodeType)
{
// Cache pointers to relevant fields
	m_texture = static_cast<MFNode*>(getField(WSTR("texture")));
	m_mode = static_cast<MFString*>(getField(WSTR("mode")));
	m_source = static_cast<MFString*>(getField(WSTR("source")));
}

MultiTexture::~MultiTexture()
{
}

void MultiTexture::CreateTexture(Gui::ImmediateRenderContext* pGraphics)
{
//		m_texNames = new Gluint[texture->m_items.GetSize()];

	for (unsigned int i = 0; i < m_texture->m_items.GetSize(); i++)
	{
		X3DTextureNodeImplImpl* textureNode = dynamic_cast<X3DTextureNodeImplImpl*>(m_texture->m_items[i]);

		if (textureNode)
		{
			textureNode->CreateTexture(pGraphics->GetRT());
		}
	}
}

void MultiTexture::ApplyTexture(Gui::ImmediateRenderContext* pGraphics)
{
	ASSERT(0);
#if 0
	/*
	const GLubyte *extstrGL;
 // Setup the extensions

	extstrGL = glGetString(GL_EXTENSIONS);

	//MessageBox(NULL, (char*)extstrGL, "", MB_OK);

 // Check for multi-texture extension.

	if (strstr((const char*)extstrGL, "GL_ARB_multitexture"))
	*/
	{
		//pwdata->hasMultitexture = TRUE;

//		MFNode* texture = static_cast<MFNode*>(m_texture->m_value);
//		MFString* mode = static_cast<MFString*>(m_mode->m_value);

		int ntextures = m_texture->get_size();
		int nmodes = m_mode->get_size();
		int nsources = m_source->get_size();

		ntextures = std::min(16, ntextures);

		for (int i = 0; i < ntextures; i++)
		{
			//= static_cast<SFNode*>(<ILSFNode>(m_texture->m_items[i]).p);
			//<CLX3DTextureNodeImplImpl> textureNode = <CLX3DTextureNodeImplImpl>(sfnode->m_v));
			ImageTexture* imageTexture = static_cast<ImageTexture*>(m_texture->m_items[i]);

			pGraphics->ActiveTexture(GL_TEXTURE0 + i/*imageTexture->m_texName*/);
			//glEnable(GL_TEXTURE_2D);
			//glBindTexture
			imageTexture->ApplyTexture(pGraphics);

			StringW* tmode;
			
			if (i < nmodes)
				tmode = m_mode->get1Value(i);
			else
				tmode = WSTR("MODULATE");

			StringW* source;
			if (i < nsources)
				source = m_source->get1Value(i);
			else
				source = WSTR("");	// previous stage

			if (!std::wcscmp(tmode->c_str(), L"MODULATE"))
			{
				pGraphics->TexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}
			else if (!std::wcscmp(tmode->c_str(), L"REPLACE"))
			{
				pGraphics->TexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			}
			else if (!std::wcscmp(tmode->c_str(), L"DOTPRODUCT3"))
			{
				pGraphics->TexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
				pGraphics->TexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_DOT3_RGB);
				//pGraphics->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			}
			else
				ASSERT(0);

			if (*source == L"")
			{
			}
			else if (*source == L"WHITE")
			{
			}
			else
				ASSERT(0);

		//	ASSERT(glGetError() == GL_NO_ERROR);
		}

		pGraphics->ActiveTexture(GL_TEXTURE0);
	}
#endif
}

}	// x3d
}
