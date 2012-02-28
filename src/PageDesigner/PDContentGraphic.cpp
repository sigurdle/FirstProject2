#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDContentGraphic.h"

#include "ObjectMap.h"
#include "PDDocument.h"
#include "PDImage.h"
#include "PDLayer.h"
#include "PDObjectGroup.h"
#include "PDObjectShape.h"
#include "PDAppearance.h"

HRESULT GetTransformRectBoundingBox(IPDMatrix* mat, RectD* bounds, RectD* pVal);

/////////////////////////
// CPDContentGraphic

int CPDContentGraphic::FinalConstruct()
{
	HRESULT hr;

	hr = CPDObjectTransformableImpl<CPDContentGraphic>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceImpl<CPDContentGraphic, IPDObjectWithAppearance>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectImpl<IPDContentGraphic>::FinalConstruct();
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CPDContentGraphic::FinalRelease()
{
	if (m_image)
	{
		m_image->Release();
		m_image = NULL;
	}

	CPDObjectWithAppearanceImpl<CPDContentGraphic, IPDObjectWithAppearance>::FinalRelease();
	CPDObjectTransformableImpl<CPDContentGraphic>::FinalRelease();
	CPDObjectImpl<IPDContentGraphic>::FinalRelease();
}

//virtual
void CPDContentGraphic::CalculateBounds()
{
	m_bounds.X = 0;
	m_bounds.Y = 0;
	m_bounds.Width = 0;
	m_bounds.Height = 0;

	if (m_image)
	{
		m_bounds.X = m_x;
		m_bounds.Y = m_y;
		m_bounds.Width = m_image->m_image->GetWidth();
		m_bounds.Height = m_image->m_image->GetHeight();

		GetTransformRectBoundingBox(m_matrix, &m_bounds, &m_xbounds);		
	}

	m_filterRect = m_bounds;

	m_appearance->SetupChildrenLayers(this);

	m_expandedBBox = m_appearance->m_expandedRect;

	CalculateScale(m_expandedBBox, m_matrix);

	if (m_parent)
	{
		// TODO Have this ???
		static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_parent)->CalculateBounds();
	}
}

//virtual
STDMETHODIMP CPDContentGraphic::Render2(/*[in]*/ DWORD dwBitmap, DWORD dwGraphics, double scaleX, double scaleY)
{
	Gdiplus::Graphics& graphics = *(Gdiplus::Graphics*)dwGraphics;
//	Gdiplus::Graphics* pGraphics = (Gdiplus::Graphics*)dwGraphics;
//	Gdiplus::Matrix oldmat;
//	pGraphics->GetTransform(&oldmat);

	Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)dwBitmap;
//	Gdiplus::Graphics graphics(pBitmap);

	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

//	graphics.ScaleTransform(scaleX, scaleY/*, Gdiplus::MatrixOrderAppend*/);
//	graphics.TranslateTransform(-m_filterRect.X, -m_filterRect.Y);

	if (m_image)
	{
		double x = m_x;
		double y = m_y;
		double width = m_image->m_image->GetWidth();
		double height = m_image->m_image->GetHeight();

		Gdiplus::RectF destRect(x, y, width, height);
		m_image->Render(&graphics, destRect);

		Mask(pBitmap, m_filterRect, scaleX, scaleY, Gdiplus::SmoothingModeHighQuality);
	}

//	pGraphics->SetTransform(&oldmat);

	return S_OK;
}

#if 0
//virtual
void CPDContentGraphic::Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics)
{
//	Gdiplus::GraphicsState state = graphics->Save();

//	CPDObjectFrame* pFrame = static_cast<CPDObjectFrame*>((IPDObjectFrame*)m_parent);
//	graphics->SetClip(pFrame->m_gdppath, Gdiplus::CombineModeIntersect);

	if (m_image)
	{
		m_appearance->SetupChildrenLayers(this);

		Gdiplus::Bitmap* pBitmap = m_appearance->ProcessEffects(this, 1, 1);
		if (pBitmap)
		{
			Gdiplus::Matrix oldmat;
			pGraphics->GetTransform(&oldmat);

			Gdiplus::Matrix matrix(
				m_matrix->m_matrix[0][0], m_matrix->m_matrix[0][1],
				m_matrix->m_matrix[1][0], m_matrix->m_matrix[1][1],
				m_matrix->m_matrix[2][0], m_matrix->m_matrix[2][1]);
			pGraphics->MultiplyTransform(&matrix);

			double x = m_appearance->m_expandedRect.X;
			double y = m_appearance->m_expandedRect.Y;

			pGraphics->DrawImage(pBitmap, (float)x, (float)y);

			pGraphics->SetTransform(&oldmat);

			delete pBitmap;
		}

/*
		Gdiplus::Matrix oldmat;
		graphics->GetTransform(&oldmat);

		Gdiplus::Matrix matrix(
			m_matrix->m_matrix[0][0], m_matrix->m_matrix[0][1],
			m_matrix->m_matrix[1][0], m_matrix->m_matrix[1][1],
			m_matrix->m_matrix[2][0], m_matrix->m_matrix[2][1]);
		graphics->MultiplyTransform(&matrix);

		double x = m_x;
		double y = m_y;
		double width = m_image->m_image->GetWidth();
		double height = m_image->m_image->GetHeight();

		Gdiplus::RectF destRect(x, y, width, height);
		m_image->Render(graphics, destRect);

		graphics->SetTransform(&oldmat);
*/
	}
	else
	{
		Gdiplus::Pen pen(Gdiplus::Color(0,0,0));

		CComQIPtr<IPDObjectTransformable> parent = m_parent;
		RectD framebounds;
		parent->get_bounds(&framebounds);

	// Draw a cross
		pGraphics->DrawLine(&pen,
			(float)framebounds.X, (float)framebounds.Y,
			(float)(framebounds.X+framebounds.Width), (float)(framebounds.Y+framebounds.Height));

		pGraphics->DrawLine(&pen,
			(float)(framebounds.X+framebounds.Width), (float)framebounds.Y,
			(float)(framebounds.X), (float)(framebounds.Y+framebounds.Height));
	}

//	graphics->Restore(state);
}
#endif

STDMETHODIMP CPDContentGraphic::getScreenBBox(RectD *pVal)
{
	CComPtr<IPDMatrix> ctm;
	getScreenCTM(&ctm);

	GetTransformRectBoundingBox(ctm, &m_bounds, pVal);

	return S_OK;
}

STDMETHODIMP CPDContentGraphic::Move(/*[in]*/ double dx, /*[in]*/ double dy)
{
	return setxy(m_x+dx, m_y+dy);
}

STDMETHODIMP CPDContentGraphic::get_image(IPDImage **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_image;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDContentGraphic::put_image(IPDImage *newVal)
{
	CComObject<CPDImage>* pimage = m_image;
	if (pimage)
	{
		pimage->AddRef();
		m_image->Release();
	}

	m_image = static_cast<CComObject<CPDImage>*>(newVal);
	m_image->AddRef();

	if (pimage)
	{
		pimage->Release();
	}

	CalculateBounds();

	return S_OK;
}

STDMETHODIMP CPDContentGraphic::get_objectType(PDObjectType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = CONTENT_GRAPHIC;
	return S_OK;
}

STDMETHODIMP CPDContentGraphic::get_x(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_x;
	return S_OK;
}

STDMETHODIMP CPDContentGraphic::get_y(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_y;
	return S_OK;
}

STDMETHODIMP CPDContentGraphic::setxy(double x, double y)
{
	m_x = x;
	m_y = y;

	CalculateBounds();

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDContentGraphic::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	HRESULT hr;

	hr = CPDObjectImpl<IPDContentGraphic>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

//	CPDObjectWrappableImpl<CPDObjectFrame>::Serialize(ar, node);
//	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDContentGraphic>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

//	CPDObjectWithOpacityMaskImpl<CPDObjectFrame>::Serialize(ar, node);
//	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceImpl<CPDContentGraphic, IPDObjectWithAppearance>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

	node->putAttribute(L"x", _variant_t(m_x));
	node->putAttribute(L"y", _variant_t(m_y));

	CComQIPtr<IObjectSerializable> image = m_image;
	if (image)
	{
		node->serializeElement(L"image", image);
	}

	return S_OK;
}

STDMETHODIMP CPDContentGraphic::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	if (m_image)
	{
		m_image->Release();
		m_image = NULL;
	}

	HRESULT hr;

	hr = CPDObjectImpl<IPDContentGraphic>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDContentGraphic>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceImpl<CPDContentGraphic, IPDObjectWithAppearance>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	_variant_t v;

	node->getAttribute(L"x", &v);
	m_x = v;

	node->getAttribute(L"y", &v);
	m_y = v;

	CComObject<CPDImage>::CreateInstance(&m_image);
	if (m_image)
	{
		m_image->AddRef();

		CComQIPtr<IObjectSerializable> image = m_image;
		if (image)
		{
			node->deserializeElement(L"image", image, NULL);
		}
	}

	CalculateBounds();

	return S_OK;
}
