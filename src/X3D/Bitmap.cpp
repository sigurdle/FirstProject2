#include "stdafx.h"
#include "X3D2.h"
#include "Bitmap.h"

namespace System
{
namespace x3d
{

NodeType Bitmap::s_nodeType(WSTR("Bitmap"), typeid(Bitmap), NULL, 0);

Bitmap::Bitmap() : X3DGeometryNode(&s_nodeType)
{
// Cache pointers to relevant fields
	m_scale = static_cast<SFVec2f*>(getField(WSTR("scale")));

// Set defaults
	m_scale->m_value[0] = m_scale->m_value[1] = -1;
}

void Bitmap::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* textureNode)
{
	ASSERT(0);
#if 0

	if (true)
	{
		if (textureNode)
		{
			// TODO
			//CLMovieTexture* pMovieTexture = static_cast<CLMovieTexture*>(textureNode);

			//ILVideoMediaType* videoMediaType = pMovieTexture->m_pVideoFilter->m_pInput->m_mediaType;
			//if (videoMediaType)
			{
				long imageWidth = textureNode->GetWidth();
				long imageHeight = textureNode->GetHeight();
				//videoMediaType->GetWidth(&imageWidth);
				//videoMediaType->GetHeight(&imageHeight);

				if (imageWidth > 0 && imageHeight > 0)
				{
					float destWidth;
					float destHeight;

					if (m_scale->m_value[0] == -1)
					{
						destWidth = imageWidth;
					}
					else
					{
						destWidth = imageWidth * m_scale->m_value[0];
					}

					if (m_scale->m_value[1] == -1)
					{
						destHeight = imageHeight;
					}
					else
					{
						destHeight = imageHeight * m_scale->m_value[1];
					}

					//if (textureNode->m_pVideoFilter->m_pInput->m_pSample)
					//{

					pDC->m_pGraphics3D->glBegin(GL_QUADS);

					pDC->m_pGraphics3D->glTexCoordf(0, 0);
					pDC->m_pGraphics3D->glVertexf(-destWidth/2, destHeight/2, 0);

					pDC->m_pGraphics3D->glTexCoordf(1, 0);
					pDC->m_pGraphics3D->glVertexf(destWidth/2, destHeight/2, 0);

					pDC->m_pGraphics3D->glTexCoordf(1, 1);
					pDC->m_pGraphics3D->glVertexf(destWidth/2, -destHeight/2, 0);

					pDC->m_pGraphics3D->glTexCoordf(0, 1);
					pDC->m_pGraphics3D->glVertexf(-destWidth/2, -destHeight/2, 0);

					pDC->m_pGraphics3D->glEnd();

#if 0
					void* pixels = textureNode->GetData();//pMovieTexture->m_pVideoFilter->m_pInput->m_pSample->m_bits;

					if (pixels)
					{
						glRasterPos2f(0.0f, 0.0f);	// TODO ??
						ASSERT(glGetError() == GL_NO_ERROR);

						//destWidth *= 4;
						//destHeight *= 4;

						glPixelZoom(destWidth / imageWidth, destHeight / imageHeight);
						ASSERT(glGetError() == GL_NO_ERROR);

						glDrawPixels(imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);
						ASSERT(glGetError() == GL_NO_ERROR);
					}
#endif
				}
			}
		}
	}
	else
	{
	}
#if 0
	glRectf(
		-m_size->m_value[0]/2, -m_size->m_value[1]/2,
		m_size->m_value[0]/2, m_size->m_value[1]/2);
#endif

#if 0
	glBegin(GL_QUADS);

	SFVec3f* size = static_cast<SFVec3f*>(m_size->m_value);
	gmVector3 s = size->m_v;

	// front (cw)
	/*
	glVertex3d(-m_boxSize[0]/2, -m_boxSize[1]/2, m_boxSize[2]/2);
	glVertex3d(m_boxSize[0]/2, -m_boxSize[1]/2, m_boxSize[2]/2);
	glVertex3d(m_boxSize[0]/2, m_boxSize[1]/2, m_boxSize[2]/2);
	glVertex3d(-m_boxSize[0]/2, m_boxSize[1]/2, m_boxSize[2]/2);
	*/

	// front (ccw)
	lglNormal(	gmVector3(-s[0]/2, -s[1]/2, s[2]/2),
					gmVector3(-s[0]/2, s[1]/2, s[2]/2),
					gmVector3(s[0]/2, s[1]/2, s[2]/2));

	glVertex3d(-s[0]/2, -s[1]/2, s[2]/2);
	glVertex3d(-s[0]/2, s[1]/2, s[2]/2);
	glVertex3d(s[0]/2, s[1]/2, s[2]/2);
	glVertex3d(s[0]/2, -s[1]/2, s[2]/2);

	// left side
	lglNormal(	gmVector3(-s[0]/2, -s[1]/2, s[2]/2),
					gmVector3(-s[0]/2, -s[1]/2, -s[2]/2),
					gmVector3(-s[0]/2, s[1]/2, -s[2]/2));

	glVertex3d(-s[0]/2, -s[1]/2, s[2]/2);
	glVertex3d(-s[0]/2, -s[1]/2, -s[2]/2);
	glVertex3d(-s[0]/2, s[1]/2, -s[2]/2);
	glVertex3d(-s[0]/2, s[1]/2, s[2]/2);

	glEnd();
#endif
#endif
}

}	// x3d
}

