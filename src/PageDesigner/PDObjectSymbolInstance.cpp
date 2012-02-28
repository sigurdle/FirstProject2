// PDObjectSymbolInstance.cpp : Implementation of CPDObjectSymbolInstance
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDObjectGroup.h"

#include "PDObjectSymbolInstance.h"

HRESULT GetTransformRectBoundingBox(IPDMatrix* mat, RectD* bounds, RectD* pVal);

/////////////////////////////////////////////////////////////////////////////
// CPDObjectSymbolInstance

int CPDObjectSymbolInstance::FinalConstruct()
{
	HRESULT hr;

	hr = CPDObjectImpl<IPDObjectSymbolInstance>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDObjectSymbolInstance>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceImpl<CPDObjectSymbolInstance, IPDObjectWithAppearance>::FinalConstruct();
	if (FAILED(hr)) return hr;

	return 0;
}

void CPDObjectSymbolInstance::FinalRelease()
{
	if (m_symbol)
	{
		CComQIPtr<INotifySend> cp = m_symbol;
		cp->Unadvise(this);
	}

	CPDObjectImpl<IPDObjectSymbolInstance>::FinalRelease();
	CPDObjectTransformableImpl<CPDObjectSymbolInstance>::FinalRelease();
	CPDObjectWithAppearanceImpl<CPDObjectSymbolInstance, IPDObjectWithAppearance>::FinalRelease();
}

STDMETHODIMP CPDObjectSymbolInstance::get_x(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_x;
	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstance::get_y(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_y;
	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstance::setxy(double x, double y)
{
	m_x = x;
	m_y = y;

	CalculateBounds();
	
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstance::Move(/*[in]*/ double dx, /*[in]*/ double dy)
{
	setxy(m_x+dx, m_y+dy);

	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstance::get_symbol(IPDSymbol **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_symbol;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstance::put_symbol(IPDSymbol *newVal)
{
	if (m_symbol)
	{
		CComQIPtr<INotifySend> cp = m_symbol;
		cp->Unadvise(this);
	}

	m_symbol = newVal;

	if (m_symbol)
	{
		CComQIPtr<INotifySend> cp = m_symbol;
		DWORD cookie;
		cp->Advise(this, &cookie);
	}

	CalculateBounds();

	return S_OK;
}

// INotifyGet
STDMETHODIMP CPDObjectSymbolInstance::OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
{
	CalculateBounds();

	FireOnChanged(type, targetObject, dispID);

	return S_OK;
}

#if 0
//virtual
void CPDObjectSymbolInstance::Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics)
{
	if (m_symbol)
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
	}
}
#endif

//virtual
void CPDObjectSymbolInstance::CalculateBounds()
{
	m_bounds.X = 0;
	m_bounds.Y = 0;
	m_bounds.Width = 0;
	m_bounds.Height = 0;

	m_filterRect.X = 0;
	m_filterRect.Y = 0;
	m_filterRect.Width = 0;
	m_filterRect.Height = 0;

	if (m_symbol)
	{
		CComPtr<IPDObject> symbolObject;
		m_symbol->get_symbolObject(&symbolObject);

	// Get bbox
		CComQIPtr<IPDObjectTransformable> transformable = symbolObject;

		RectD symbolBounds;
		transformable->get_bounds(&symbolBounds);

		m_bounds.X = m_x;
		m_bounds.Y = m_y;
		m_bounds.Width = symbolBounds.Width;
		m_bounds.Height = symbolBounds.Height;

	// Get expanded bbox
		symbolObject->getExpandedBBox(&m_filterRect);
		m_filterRect.X += m_x;
		m_filterRect.Y += m_y;

	// and bbox when transformed
		GetTransformRectBoundingBox(m_matrix, &m_bounds, &m_xbounds);
	}

	m_appearance->SetupChildrenLayers(this);

	m_expandedBBox = m_appearance->m_expandedRect;

	CalculateScale(m_expandedBBox, m_matrix);
	
	if (m_parent)	// hm.. ?
	{
		static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_parent)->CalculateBounds();
	}
}

STDMETHODIMP CPDObjectSymbolInstance::Render2(/*[in]*/ DWORD dwBitmap, DWORD dwGraphics, double scaleX, double scaleY)
{
	Gdiplus::Graphics& graphics = *(Gdiplus::Graphics*)dwGraphics;
//	Gdiplus::Graphics* pGraphics = (Gdiplus::Graphics*)dwGraphics;

	Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)dwBitmap;
//	Gdiplus::Graphics graphics(pBitmap);

	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

//	graphics.ScaleTransform(scaleX, scaleY/*, Gdiplus::MatrixOrderAppend*/);
//	graphics.TranslateTransform(-m_filterRect.X, -m_filterRect.Y);

	if (m_symbol)
	{
		CComPtr<IPDObject> symbolObject;
		m_symbol->get_symbolObject(&symbolObject);

		CPDObject* pObject = (CPDObject*)static_cast<CPDObjectImpl<IPDObject>*>(symbolObject.p);

//		Gdiplus::Matrix oldmat;
//		pGraphics->GetTransform(&oldmat);

//		pGraphics->ScaleTransform(scaleX, scaleY, Gdiplus::MatrixOrderAppend);
		graphics.TranslateTransform(m_x, m_y);

		pObject->Render(NULL, &graphics, scaleX, scaleY);

		Mask(pBitmap, m_filterRect, scaleX, scaleY, Gdiplus::SmoothingModeHighQuality);

//		pGraphics->SetTransform(&oldmat);
	}

	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstance::getScreenBBox(RectD *pVal)
{
	CComPtr<IPDMatrix> ctm;
	getScreenCTM(&ctm);

	GetTransformRectBoundingBox(ctm, &m_bounds, pVal);

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDObjectSymbolInstance::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	HRESULT hr;

	hr = CPDObjectImpl<IPDObjectSymbolInstance>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

//	CPDObjectWrappableImpl<CPDObjectFrame>::Serialize(ar, node);
//	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDObjectSymbolInstance>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

//	CPDObjectWithOpacityMaskImpl<CPDObjectFrame>::Serialize(ar, node);
//	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceImpl<CPDObjectSymbolInstance, IPDObjectWithAppearance>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

	node->putAttribute(L"x", _variant_t(m_x));
	node->putAttribute(L"y", _variant_t(m_y));

	node->putElement(L"symbol", m_symbol);

	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstance::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	HRESULT hr;

	hr = CPDObjectImpl<IPDObjectSymbolInstance>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDObjectSymbolInstance>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceImpl<CPDObjectSymbolInstance, IPDObjectWithAppearance>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	_variant_t v;

	node->getAttribute(L"x", &v);
	m_x = v;

	node->getAttribute(L"y", &v);
	m_y = v;

	node->getElement(L"symbol", NULL, (IUnknown**)&m_symbol);

	CalculateBounds();

	return S_OK;
}
