#include "stdafx.h"
#include "LSVG2.h"
#include "SVGImageElement.h"
#include "PSVGImageElement.h"

#include "LXML/PImage.h"

#include <Wininet.h>

namespace System
{
namespace Web
{

SVGImageElement::SVGImageElement(NamedNodeMap* attributes) :
	SVGTransformableElement(new PSVGImageElement(this), attributes),

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>(this, NULL, WSTR("x"), WSTR("0")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>(this, NULL, WSTR("y"), WSTR("0")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(this, NULL, WSTR("width")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>(this, NULL, WSTR("height")),
	AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>(this, NULL, WSTR("preserveAspectRatio"), WSTR("xMidYMid meet"))
{
	m_bTriedLoaded = false;
	m_pImage = NULL;
	m_pSVGDocumentView = NULL;
}

SVGImageElement::~SVGImageElement()
{
	if (m_pSVGDocumentView)
	{
		m_pSVGDocumentView->Free();
//		m_pSVGDocumentView->Release();
		m_pSVGDocumentView = NULL;
	}
//	m_document.Release();
}

ISVGAnimatedLength* SVGImageElement::get_x()
{
	return x_attr();
}

ISVGAnimatedLength* SVGImageElement::get_y()
{
	return y_attr();
}

ISVGAnimatedLength* SVGImageElement::get_width()
{
	return width_attr();
}

ISVGAnimatedLength* SVGImageElement::get_height()
{
	return height_attr();
}

ISVGAnimatedPreserveAspectRatio* SVGImageElement::get_preserveAspectRatio()
{
	return preserveAspectRatio_attr();
}

// SVG 1.2
Document* SVGImageElement::getImageDocument()
{
	return m_document;
}

//////////////////////////////////////////////////////////////

ErrorCode SVGImageElement::Load()
{
	if (!m_bTriedLoaded)
	{
		m_bTriedLoaded = true;

		ASSERT(m_document == NULL);
		ASSERT(m_pSVGDocumentView == NULL);
		ASSERT(m_pImage == NULL);

		String src = href_attr()->m_animVal;//GetAnimVal()->m_value;//getStringValue();//m_animated->m_animVal->m_value;
		if (src)
		{
#if 0
			if (!wcsncmp(src, L"data:", 5))
			{
				// Try to load it as raster bitmap
				m_document.Release();
				m_pImage = g_Images.OpenImage(src);
			}
			else
#endif
			{
				WCHAR result[2048];
				{
					String documentUrl = m_ownerDocument->get_url();

					DWORD resultLen = sizeof(result);
					InternetCombineUrl(CStringw(documentUrl).c_str(), CStringw(src).c_str(), result, &resultLen, 0);
				}

				/*
				m_document.CoCreateInstance(CLSID_LSVGDocument);
				VARIANT_BOOL bSVGDocument;
				m_document->load(_variant_t(result), &bSVGDocument);
				if (!bSVGDocument)
					*/
				{
					// Try to load it as raster bitmap
				//	m_document.Release();
				//	m_pImage = g_Images.OpenImage(new StringW(string_copy(result)));

					Net::UrlBinding binding;
					_Ptr<IO::Stream> stream = binding.BindToObject(String(string_copy(result)), NULL);

					//Imaging::BitmapLoader loader;
				//	loader.Load(stream);

					m_pImage = new CImage;
					m_pImage->m_bitmap = Graphics::Bitmap::FromStream(stream);
				}

				return 0;
			}
		}
	}

	return Error;
}

CImage* SVGImageElement::GetImage()
{
	Load();
	return m_pImage;
}

CHTMLWindow* SVGImageElement::GetSVGDocumentView()
{
	Load();
	return NULL;

	ASSERT(0);
#if 0
	if (m_document)
	{
		if (m_pSVGDocumentView == NULL)
		{
			CComObject<CHTMLWindow>::CreateInstance(&m_pSVGDocumentView);
			if (m_pSVGDocumentView)
			{
				m_pSVGDocumentView->AddRef();

			// ??
				m_pSVGDocumentView->m_imageRect.left = 0;
				m_pSVGDocumentView->m_imageRect.top = 0;
				m_pSVGDocumentView->m_imageRect.right = 600;
				m_pSVGDocumentView->m_imageRect.bottom = 600;

				m_pSVGDocumentView->m_pView->SetDocument(m_document);
			}
		}

		return m_pSVGDocumentView;
	}
#endif
	return NULL;
}

}	// Web
}	// System
