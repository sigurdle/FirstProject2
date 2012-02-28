#include "stdafx.h"
#include "LXImageEditor.h"

#include "ImageLayerBitmap.h"

namespace System
{
namespace ImageEdit
{

CImageLayerBitmap::CImageLayerBitmap()
{
	m_parentGroup = NULL;
	m_document = NULL;

	m_name = NULL;

	m_pInitialBitmap = NULL;

	m_pBitmap = NULL;
	m_pBitmapDepth = NULL;
	m_pBitmapMask = NULL;
	m_groupMask = NULL;

	m_groupClipPath = NULL;
	m_pBitmapClipPath = NULL;	// Used??

	m_pBitmapFinal = NULL;

	m_group = NULL;

	m_matrix = LDraw::matrix3f::getIdentity();
	m_scaleX = 1;
	m_scaleY = 1;

	for (int i = 0; i < 16; i++)
	{
		m_effects[i] = NULL;
	}

//	m_group = new CGroupImageObject;
}

/*
int CImageLayerBitmap::FinalConstruct()
{
	HRESULT hr;

	//m_group->AddRef();

	return S_OK;
}

void CImageLayerBitmap::FinalRelease()
{
	if (m_group)
	{
	//	m_group->Release();
		m_group = NULL;
	}
}
*/

void CImageLayerBitmap::Render()
{
	if (m_pBitmap)
	{
		m_pBitmap = NULL;
		//delete m_pBitmap;
	}

	m_pBitmap = new LDraw::Bitmap(ceil(m_width*m_scaleX), ceil(m_height*m_scaleY), LDraw::PixelFormat_t::RGBAP_32);
	if (m_pBitmap)
	{
		{
			ASSERT(0);
#if 0
			UI::Graphics graphics(new LDraw::GraphicsO(m_pBitmap));

			graphics.DrawImage(m_pInitialBitmap,
				LDraw::RectF(0, 0, m_width*m_scaleX, m_height*m_scaleY),
				(float)0, (float)0, (float)m_width, (float)m_height/*,
				LDraw::UnitPixel*/);
#endif
		}

		for (int i = 0; i < m_group->m_objects.GetSize(); i++)
		{
			CStrokeObject* pStroke = m_group->m_objects[i];

			pStroke->Render(m_pBitmap, m_scaleX, m_scaleY);
		}
	}
}

CGroupImageObject* CImageLayerBitmap::GetGroupObject()
{
	return m_group;
}

CGroupImageObject* CImageLayerBitmap::GetMaskGroupObject()
{
	return NULL;
}

CGroupImageObject* CImageLayerBitmap::GetClipPathGroupObject()
{
	return NULL;
}

StringW* CImageLayerBitmap::GetName()
{
	return m_name;
}

}
}
