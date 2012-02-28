#ifndef PIMAGE_H
#define PIMAGE_H

namespace System
{
namespace Web
{

class CGImages;

class WEBEXT CImage
{
public:
	CTOR CImage();

	~CImage()
	{
		/*
		if (m_gdipImage)
		{
			delete m_gdipImage;
			m_gdipImage = NULL;
		}
		*/
	}

	String m_url;

	CriticalSection m_lock;
	Graphics::Bitmap* m_bitmap;

	inline ErrorCode GetLoadStatus()
	{
		return m_loadStatus;
	}

	friend class CGImages;

protected:

	ErrorCode m_loadStatus;
	int m_refcount;
};

}	// w3c
}

#if 0

class LXUIEXT CGImages
{
public:
	~CGImages();

	CUPtrList m_images;

	CImage* FindImage(BSTR url);
	void RemoveImage(CImage* pImage);
	CImage* OpenImage(BSTR url);
};

extern LXUIEXT CGImages g_Images;

#endif

#endif // PIMAGE_H
