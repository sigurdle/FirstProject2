#include "stdafx.h"
#include "PImage.h"

namespace System
{
namespace w3c
{

CGImages::~CGImages()
{
}

CImage* CGImages::FindImage(BSTR url)
{
	UPOSITION pos = m_images.GetHeadPosition();
	while (pos)
	{
		CImage* pImage = (CImage*)m_images.GetNext(pos);
		if (!wcsicmp(pImage->m_url, url))
		{
			return pImage;
		}
	}

	return NULL;
}

void CGImages::RemoveImage(CImage* pImage)
{
	pImage->m_refcount--;

	if (pImage->m_refcount == 0)
	{
		UPOSITION pos = m_images.Find(pImage);
		m_images.RemoveAt(pos);
		delete pImage;
	}
}

CImage* CGImages::OpenImage(BSTR url)
{
	USES_CONVERSION;

	CImage* pImage = FindImage(url);
	if (pImage)
	{
		pImage->m_refcount++;
		return pImage;
	}
	else
	{
	// Even if it turns out we can't load image, we add CImage so we don't try to download the file again
		pImage = new CImage;
		pImage->m_refcount = 1;
		pImage->m_url = url;

		pImage->m_refcount++;	// TODO remove ??

#if _WINDOWS
		CComPtr<IStream> stream;
		HRESULT hr = URLOpenBlockingStream(0, W2A(url), &stream, 0, 0);
		if (SUCCEEDED(hr))
		{
			Gdiplus::Bitmap* gdipImage = new Gdiplus::Bitmap(stream);
			if (gdipImage)
			{
				pImage->m_loadStatus = (gdipImage->GetLastStatus() == Gdiplus::Ok)? S_OK: E_FAIL;

				if (FAILED(pImage->m_loadStatus))
				{
					ATLTRACE("Image loading failed: %S\n", url);
				}

				pImage->m_gdipImage = gdipImage;
			}
		}
#endif // _WINDOWS

		m_images.AddTail(pImage);
	}

	return pImage;
}

WEBEXT CGImages g_Images;

}
