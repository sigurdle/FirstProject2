#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "ObjectMap.h"
#include "PDLayer.h"
#include "PDObjectGroup.h"
#include "PDObjectShape.h"

#include "PDDocument.h"

/////////////////////////
// CPDObjectGroup

int CPDObjectGroup::FinalConstruct()
{
	HRESULT hr;

	hr = CPDObjectWrappableImpl<CPDObjectGroup>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDObjectGroup>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceImpl<CPDObjectGroup, IPDObjectWithAppearance>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectGroupImpl<CPDObjectGroup, IPDObjectGroup>::FinalConstruct();
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CPDObjectGroup::FinalRelease()
{
	CPDObjectWrappableImpl<CPDObjectGroup>::FinalRelease();
	CPDObjectTransformableImpl<CPDObjectGroup>::FinalRelease();
	CPDObjectWithAppearanceImpl<CPDObjectGroup, IPDObjectWithAppearance>::FinalRelease();
	CPDObjectGroupImpl<CPDObjectGroup, IPDObjectGroup>::FinalRelease();
}

//virtual
void CPDObjectGroup::CalculateBounds()
{
	CPDObjectGroupImpl<CPDObjectGroup, IPDObjectGroup>::CalculateBounds();

	m_appearance->SetupChildrenLayers(this);

	m_expandedBBox = m_appearance->m_expandedRect;

	CalculateScale(m_expandedBBox, m_matrix);

//		CComQIPtr<IPDObjectGroup> parentgroup = m_parent;
//		if (parentgroup)
	if (m_parent)
	{
		static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_parent)->CalculateBounds();
	}
}

STDMETHODIMP CPDObjectGroup::Render2(/*[in]*/ DWORD dwBitmap, DWORD dwGraphics, double scaleX, double scaleY)
{
	Gdiplus::Graphics& graphics = *(Gdiplus::Graphics*)dwGraphics;
//	Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)dwBitmap;

//	Gdiplus::Graphics graphics(pBitmap);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

//	graphics.ScaleTransform(scaleX, scaleY);
//	graphics.TranslateTransform(-m_filterRect.X, -m_filterRect.Y);

	for (int i = 0; i < m_children->m_items.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_children->m_items[i];
		CPDObjectImpl<IPDObject>* pObject;

		pObject = static_cast<CPDObjectImpl<IPDObject>*>(object.p);

		pObject->Render(NULL, &graphics, scaleX, scaleY);
	}

	return S_OK;
}

STDMETHODIMP CPDObjectGroup::Scale(double originx, double originy, double sx, double sy)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDObjectGroup::get_objectType(PDObjectType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = OBJECT_GROUP;
	return S_OK;
}

STDMETHODIMP CPDObjectGroup::put_textWrap(/*[in]*/ PDTextWrap newVal)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CPDObjectGroup::IsRectangular(VARIANT_BOOL *pVal)
{
	*pVal = VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CPDObjectGroup::getScreenBBox(RectD *pVal)
{
	CComPtr<IPDMatrix> ctm;
	getScreenCTM(&ctm);

	GetTransformRectBoundingBox(ctm, &m_bounds, pVal);

	return S_OK;
}

STDMETHODIMP CPDObjectGroup::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_PDObjectGroup;
	return S_OK;
}
