#include "stdafx.h"
#include "HTML2.h"
#include "HTMLImageElement.h"

#include "PHTMLImageElement.h"
#include "LXML/PImage.h"

#include "JFIF/JFIF.h"
#pragma comment(lib, "JFIF")

#include "PNG/PNGFormat.h"
#pragma comment(lib, "PNG")

#include "GIF/GIF.h"
#pragma comment(lib, "GIF")

namespace System
{
namespace Web
{
extern CGImages g_Images;

HTMLImageElement::HTMLImageElement(NamedNodeMap* attributes) : HTMLElement(new PHTMLImageElement(this), attributes)
{
	m_widthAttr = NULL;
	m_heightAttr = NULL;
	m_srcAttr = NULL;

	m_pImage = NULL;

	/*
	PHTMLImageElement* pElement = new PHTMLImageElement;
	pElement->m_pNode = this;
	m_pNode = pElement;
	*/
}

HTMLImageElement::~HTMLImageElement()
{
	/*
	if (m_pBitmap)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	*/
}

int HTMLImageElement::ReadJPEG(IO::Stream* stream)
{
	ASSERT(0);
#if 0
	Imaging::JPEGDecoder* jfif = new Imaging::JPEGDecoder(stream);
	if (jfif->ReadMarker(stream) == 0)
	{
		if (jfif->ReadHeader() != 0)
			return -1;

		int width = jfif->GetWidth();
		int height = jfif->GetHeight();

		m_pImage->m_bitmap = new LDraw::Bitmap(width, height, LDraw::PixelFormat_t::RGB_24);

	//	m_pNode->m_pWindow->InvalidateRender();	// Rerender now that we've allocated the bitmap
		m_pNode->m_pWindow->ArrangeOverride(m_pNode->m_pWindow->get_ActualSize());	// Rerender now that we've allocated the bitmap

		jfif->StartScans();

		LDraw::BitmapData bitmapdata;
		{
			for (int y = 0; y < height; y++)
			{
				jfif->NextScanline();

				m_pImage->m_lock.Lock();
				m_pImage->m_bitmap->LockBits(&LDraw::RectI(0, y, width, height), LDraw::ImageLockModeWrite, &bitmapdata);
				uint8* dest = bitmapdata.Scan0;// + bitmapdata.Stride*y;

				if (true)
				{
					jfif->CopyScanline(dest, dest+1, dest+2, 3);
				}
				else
				{
					jfif->CopyScanlineGray(dest, 1);
				}
				m_pImage->m_bitmap->UnlockBits(&bitmapdata);
				m_pImage->m_lock.Unlock();

				if ((y & 7) == 0)
				{
					m_pNode->m_pWindow->RenderChanged();
				//	p->m_pNode->m_pWindow->InvalidateRender();
				}
			}

			//p->m_pNode->m_pWindow->RenderChanged();
		}
		//m_pImage->m_bitmap.UnlockBits(&bitmapdata);

		jfif->EndScans();

		return 0;
	}
	else
#endif
		return -1;
}

int HTMLImageElement::ReadPNG(IO::Stream* stream)
{
	ASSERT(0);
#if 0
	ULONG nRead;

	uint32 format;
	nRead = stream->Read(&format, 4);
	if (nRead != 4)
	{
	//	nRead = stream->Read(&format, 4);
		return -1;
	}

	if (format != 0x474e5089/*PNG*/ && format != 0x474e4a8b/*JNG*/)
	{
		return -1;
	}

	uint32 value;
	nRead = stream->Read(&value, 4);
	if (nRead != 4)
	{
		return -1;
	}
	if (value != 0x0a1a0a0d)
	{
		return -1;
	}

	Imaging::NGFormat* png;

	if (format == 0x474e5089)
	{
		png = new Imaging::PNGDecoder;
	}
	else
	{
		png = new Imaging::JNGDecoder;
	}

	png->SetStream(stream);
	png->ReadHeader();
	png->CreateImage();

	LDraw::PixelFormat_t pixelformat;
	if (png->GetColorType() == 6)	// rgb+alpha
	{
		pixelformat = LDraw::PixelFormat_t::RGBAP_32;
	}
	else if (png->GetColorType() == 4)	// grayscale+alpha
	{
		pixelformat = LDraw::PixelFormat_t::RGBAP_32;
	}
	else
	{
		//vih->vih->bmiHeader.biBitCount = 24;//m_pFilter->m_pInputPin->m_bitcount;
		pixelformat = LDraw::PixelFormat_t::RGB_24;
	}

	int width = png->GetWidth();
	int height = png->GetHeight();

	m_pImage->m_bitmap = new LDraw::Bitmap(width, height, pixelformat);

//	m_pNode->m_pWindow->InvalidateRender();	// Rerender now that we've allocated the bitmap
	m_pNode->m_pWindow->ArrangeOverride(m_pNode->m_pWindow->get_ActualSize());	// Rerender now that we've allocated the bitmap

	png->GetImage()->StartScan();

	LDraw::BitmapData bitmapdata;
	{
		if (((Imaging::PNGDecoder*)png)->m_ihdr.Interlace == 0)
		{
			for (int row = 0; row < height; row++)
			{
				m_pImage->m_lock.Lock();
				m_pImage->m_bitmap->LockBits(&LDraw::RectI(0, row, width, 1), LDraw::ImageLockModeWrite, &bitmapdata);

				uint8* dest = bitmapdata.Scan0;// + bitmapdata.Stride*row;

				int hr = png->GetImage()->ReadScanline(dest);

				m_pImage->m_bitmap->UnlockBits(&bitmapdata);
				m_pImage->m_lock.Unlock();

				if (hr < 0)
				{
					break;
				}

				if ((row & 7) == 0)
				{
					m_pNode->m_pWindow->RenderChanged();
				}
			}
		}
		else if (((Imaging::PNGDecoder*)png)->m_ihdr.Interlace == 1)
		{
			for (int npass = 0; npass < 7; npass++)
			{
				int h;

				switch (npass)
				{
				case 0: h = (height+7)/8; break;
				case 1: h = (height+7)/8; break;
				case 2: h = (height+3)/8; break;
				case 3: h = (height+3)/4; break;
				case 4: h = (height+1)/4; break;
				case 5: h = (height+1)/2; break;
				case 6: h = (height)/2; break;
				}

				for (int row = 0; row < h; row++)
				{
					if (npass == 6)
					{
						m_pImage->m_lock.Lock();
						m_pImage->m_bitmap->LockBits(&LDraw::RectI(0, (1+row*2), width, 1), LDraw::ImageLockModeWrite, &bitmapdata);

						uint8* dest = bitmapdata.Scan0;// + bitmapdata.Stride*(1+row*2);

						int hr = png->GetImage()->ReadScanline(dest);
						m_pImage->m_bitmap->UnlockBits(&bitmapdata);
						m_pImage->m_lock.Unlock();

						if (hr < 0)
							break;
					}
					else
					{
						if (((Imaging::PNGDecoder*)png)->m_image->m_imageStream->DecodeScanline() < 0)
							break;
					}

					/*
					if ((row & 7) == 0)
					{
						m_pNode->m_pWindow->RenderChanged();
					}
					*/
				}
				m_pNode->m_pWindow->RenderChanged();

				((Imaging::PNGDecoder*)png)->NextPass();
			}
		}
	}

	m_pNode->m_pWindow->RenderChanged();
#endif
	return 0;
}

int HTMLImageElement::ReadGIF(IO::Stream* stream)
{
	ASSERT(0);
#if 0
	Imaging::GIFDecoder* gifFile = new Imaging::GIFDecoder;
	ErrorCode hr = gifFile->Open(stream);
	if (hr < 0)
		return -1;

	gifFile->AddNextFrame();

	int width = gifFile->GetWidth();
	int height = gifFile->GetHeight();

	m_pImage->m_bitmap = new LDraw::Bitmap(width, height, LDraw::PixelFormat_t::RGB_24);

//	m_pNode->m_pWindow->InvalidateRender();	// Rerender now that we've allocated the bitmap

	// TODO, have this as a method on node
	PNode* p = m_pNode;
	do
	{
		p->m_bArrangeValid = false;
		p = p->m_rparent;
	}
	while (p);

	m_pNode->m_pWindow->ArrangeOverride(m_pNode->m_pWindow->get_ActualSize());	// Rerender now that we've allocated the bitmap

	gifFile->StartScan(gifFile->m_frames[0]);

	LDraw::BitmapData bitmapdata;
//	m_pImage->m_bitmap.LockBits(&LDraw::RectI(0, 0, width, height), LDraw::ImageLockModeWrite, &bitmapdata);
	{
		for (int y = 0; y < height; y++)
		{
			m_pImage->m_lock.Lock();
			m_pImage->m_bitmap->LockBits(&LDraw::RectI(0, y, width, 1), LDraw::ImageLockModeWrite, &bitmapdata);
			uint8* dest = bitmapdata.Scan0;// + bitmapdata.Stride*y;

			int hr = gifFile->ReadScanline(gifFile->m_frames[0], dest, 24);

			m_pImage->m_bitmap->UnlockBits(&bitmapdata);
			m_pImage->m_lock.Unlock();

			if (hr < 0)
				break;

			m_pNode->m_pWindow->RenderChanged();
		}
	}

//	m_pImage->m_bitmap.UnlockBits(&bitmapdata);

	m_pNode->m_pWindow->RenderChanged();
#endif
	return 0;
}

DWORD WINAPI ThreadFunc(void* lpParameter)
{
	HTMLImageElement* p = (HTMLImageElement*)lpParameter;

//	ISequentialByteStream* stream = new FileByteStream(p->m_pImage->m_url);
//	stream->AddRef();

//	LXML:DownloadDocument* downloader = new DownloadDocument;

	Net::UrlBinding* binder = new Net::UrlBinding;
	_Ptr<IO::Stream> stream = binder->BindToObject(p->m_pImage->m_url, NULL/*downloader*//*pBrowser*/);

	int n;
	for (n = 0; n < 3; n++)
	{
		int ret = -1;

		switch (n)
		{
		case 0:
			{
				ret = p->ReadJPEG(stream);
			}
			break;

		case 1:
			{
				ret = p->ReadGIF(stream);
			}
			break;

		case 2:
			{
				ret = p->ReadPNG(stream);
			}
			break;
		}

		if (ret == 0)
			break;

		ASSERT(0);
		//stream.Seek(0, System::IO::STREAM_SEEK_SET);
	}

	/*
	if (n == 3)
	{
		int ret = p->ReadPNG(stream);
		ASSERT(0);
	}
	*/

	//stream->Release();

	return 0;
}

CImage* HTMLImageElement::GetImage()
{
	if (m_pImage == NULL)
	{
		if (false)
		{
			String src = get_src();
			if (src.GetLength())
			{
				WCHAR result[2048];
				{
					String documentUrl = m_ownerDocument->get_url();
					// documentUrl = _bstr_t(bdocumentUrl, false);

					String baseUrl = documentUrl;

					ASSERT(0);
#if 0
					DWORD resultLen = sizeof(result) - sizeof(result[0]);
					InternetCombineUrlW(baseUrl->c_str(), src->c_str(), result, &resultLen, 0);
#endif
				}

			//	StringA localfilename = DownloadFile(result);

				m_pImage = new CImage;//LXML::g_Images.OpenImage(Convert2W(result));
				m_pImage->m_url = string_copy(result);

				DWORD threadId;
				
				::CreateThread(NULL, 0, ThreadFunc, this, 0, &threadId);

			}
		}
	}

	return m_pImage;
}

String HTMLImageElement::get_src()
{
	return getAttribute("src");
}

void HTMLImageElement::set_src(StringIn newVal)
{
	setAttribute("src", newVal);
}

gm::Sizei HTMLImageElement::GetImageSize()
{
	gm::Sizei size;

	ASSERT(0);
#if 0
	BSTR b;

	getAttribute(L"width", &b);
	_bstr_t strwidth = _bstr_t(b, false);

	getAttribute(L"height", &b);
	_bstr_t strheight = _bstr_t(b, false);

	// TODO : percentages

// If both width/height attributes are set, we don't even need to load
// the image to have the dimensions
	if (strwidth.length() && strheight.length())
	{
		size.Width = str2int(strwidth);
		size.Height = str2int(strheight);
	}
	else
	{
		LDraw::Size imageSize;
		imageSize.Width = -1;
		imageSize.Height = -1;

		CImage* pImage = GetImage();

		if (pImage)
		{
			LDraw::Image* pGdipImage = pImage->m_gdipImage;
			if (pGdipImage && pGdipImage->GetLastStatus() == 0)
			{
				imageSize.Width = pGdipImage->GetWidth();
				imageSize.Height = pGdipImage->GetHeight();
			}
		}

	// If only w, aspect in h, & vice versa

		if (strwidth.length())
		{
			size.Width = atol(strwidth);
			size.Height = size.Width * (double)imageSize.Height/imageSize.Width;
		}
		else if (strheight.length())
		{
			size.Height = atol(strheight);
			size.Width = size.Height * (double)imageSize.Width/imageSize.Height;
		}
		else	// None are specified, use dimensions from the image file
		{
			size = imageSize;
		}
	}
#endif
	return size;
}

int HTMLImageElement::get_width()
{
	return GetImageSize().Width;
}

void HTMLImageElement::set_width(int newVal)
{
	ASSERT(0);
//	setAttribute(L"width", _bstr_t(_variant_t(newVal)));
}

int HTMLImageElement::get_height()
{
	return GetImageSize().Height;
}

void HTMLImageElement::set_height(int newVal)
{
	ASSERT(0);
//	setAttribute(L"height", sysstring(_variant_t(newVal)));
}

}	// Web
}
