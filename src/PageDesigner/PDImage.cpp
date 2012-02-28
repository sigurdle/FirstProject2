#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDImage.h"

#include "PDDocument.h"

/////////////////////////
// CPDImage

void CPDImage::Render(Gdiplus::Graphics* graphics, Gdiplus::RectF& destRect)
{
	Gdiplus::ImageAttributes imageAtt;
//	imageAtt.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

	graphics->DrawImage(
		m_image,
		destRect,
		0, 0, m_image->GetWidth(), m_image->GetHeight(),
		Gdiplus::UnitPixel, 
		&imageAtt);
}

STDMETHODIMP CPDImage::get_pathName(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pathName.copy();
	return S_OK;
}

STDMETHODIMP CPDImage::put_pathName(BSTR newVal)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CPDImage::get_width(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_image->GetWidth();
	return S_OK;
}

STDMETHODIMP CPDImage::get_height(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_image->GetHeight();
	return S_OK;
}

STDMETHODIMP CPDImage::get_privateImage(DWORD *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = (DWORD)m_image;
	return S_OK;
}

STDMETHODIMP CPDImage::put_privateImage(DWORD newVal)
{
	m_image = (Gdiplus::Image*)newVal;
	return S_OK;
}

STDMETHODIMP CPDImage::SetProp(BSTR name, DWORD value)
{
	m_userdata = value;
	return S_OK;
}

STDMETHODIMP CPDImage::GetProp(BSTR name, DWORD *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_userdata;
	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDImage::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"imagepath", _variant_t(m_pathName));
	return S_OK;
}

STDMETHODIMP CPDImage::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	if (m_image)
	{
		delete m_image;
		m_image = NULL;
	}

	_variant_t v;

	node->getAttribute(L"imagepath", &v);
	m_pathName = v;
	m_image = new Gdiplus::Image(m_pathName);

	return S_OK;
}
