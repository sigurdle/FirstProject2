#include "stdafx.h"
#include "LXUI2.h"
#include "Image.h"

namespace System
{
namespace UI
{

FileImageSource::FileImageSource()
{
	m_bitmap = NULL;
	m_Filename = NULL;
	m_bTriedLoading = false;
}

FileImageSource::FileImageSource(StringW* Filename)
{
	m_bitmap = NULL;
	m_Filename = Filename;
	m_bTriedLoading = false;

	LoadImage();
}

FileImageSource::~FileImageSource()
{
}

void FileImageSource::LoadImage()
{
	if (!m_bTriedLoading)
	{
		m_bTriedLoading = true;
		Imaging::BitmapLoader* loader = new Imaging::BitmapLoader;
		loader->Load(m_Filename);
		m_bitmap = loader->GetBitmap();
	}
}

StringW* FileImageSource::get_Filename()
{
	return m_Filename;
}

void FileImageSource::set_Filename(StringW* newVal)
{
	/*
	if (m_pBitmap)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	*/

	m_Filename = newVal;
	m_bTriedLoading = false;

	LoadImage();
}

LDraw::Bitmap* FileImageSource::GetBitmap()
{
	return m_bitmap;
}

///////////////////////////
//

MemoryImageSource::MemoryImageSource(LDraw::Bitmap* bitmap) : m_bitmap(bitmap)
{
}

LDraw::Bitmap* MemoryImageSource::GetBitmap()
{
	return m_bitmap;
}

//////////////////////////////////////////////////////////////////////////
// Image

Image::Image()
{
	m_Source = NULL;
}

Image::Image(IImageSource* pSource)
{
	m_Source = pSource;
}

IImageSource* Image::get_Source()
{
	return m_Source;
}

void Image::set_Source(IImageSource* pSource)
{
	if (m_Source != pSource)
	{
		m_Source = pSource;
		InvalidateMeasure();
	}
}

// virtual
void Image::OnRender(Graphics* pGraphics)
{
	if (m_Source)
	{
		LDraw::Bitmap* bitmap = m_Source->GetBitmap();

		double m_Opacity = get_Opacity();
		if (m_Opacity > 0)
		{
			float opacity = m_Opacity;
			if (opacity > 1) opacity = 1;

			LDraw::CompositingMode oldCompositingMode = pGraphics->GetCompositingMode();

			LDraw::CompositingMode compositingMode;
			switch (get_CompositingMode())
			{
			case SourceOver: compositingMode = LDraw::CompositingModeSourceOver; break;
			case SourceCopy: compositingMode = LDraw::CompositingModeSourceCopy; break;
			case Xor: compositingMode = LDraw::CompositingModeXor; break;
			case Multiply: compositingMode = LDraw::CompositingModeMultiply; break;
			case Screen: compositingMode = LDraw::CompositingModeScreen; break;
			default:
				ASSERT(0);
			}
			pGraphics->SetCompositingMode(compositingMode);

#if 1
			// opacity
			LDraw::ColorMatrixF colorMatrix(	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
															0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
															0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
															0.0f, 0.0f, 0.0f, opacity, 0.0f,
															0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

		//	Gdiplus::ImageAttributes imageAtt;
		//	imageAtt.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);
#endif
			pGraphics->DrawImage(bitmap,
				LDraw::RectF(0, 0, float(m_computedSize.Width), float(m_computedSize.Height)),
				0, 0, bitmap->GetWidth(), bitmap->GetHeight(), LDraw::WrapModeClamp, &colorMatrix/*,
				Gdiplus::UnitPixel,
				&imageAtt*/);

			pGraphics->SetCompositingMode(oldCompositingMode);
		}
	}
}

// virtual
LDraw::SizeD Image::MeasureOverride(LDraw::SizeD availSize)
{
	if (m_Source)
	{
		LDraw::Bitmap* bitmap = m_Source->GetBitmap();
		if (bitmap)
		{
			return LDraw::SizeD(bitmap->GetWidth(), bitmap->GetHeight());
		}
	}

	return LDraw::SizeD(0, 0);
}

}	// UI
}
