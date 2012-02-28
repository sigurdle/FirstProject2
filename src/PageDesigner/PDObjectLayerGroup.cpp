#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "ObjectMap.h"
#include "PDLayer.h"
#include "PDObjectLayerGroup.h"
#include "PDObjectShape.h"

#include "PDDocument.h"

/////////////////////////
// CPDObjectLayerGroup

int CPDObjectLayerGroup::FinalConstruct()
{
	HRESULT hr;
	
	hr = CPDObjectGroupImpl<CPDObjectLayerGroup, IPDObjectLayerGroup>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CComObject<CPDGuides>::CreateInstance(&m_guides);
	if (FAILED(hr)) return hr;
	m_guides->AddRef();

	return S_OK;
}

void CPDObjectLayerGroup::FinalRelease()
{
	if (m_guides)
	{
		m_guides->Release();
		m_guides = NULL;
	}

	CPDObjectGroupImpl<CPDObjectLayerGroup, IPDObjectLayerGroup>::FinalRelease();
}

//virtual
void CPDObjectLayerGroup::CalculateBounds()
{
	CPDObjectGroupImpl<CPDObjectLayerGroup, IPDObjectLayerGroup>::CalculateBounds();

//	m_appearance->SetupChildrenLayers(this);
	m_expandedBBox = m_filterRect;//m_appearance->m_expandedRect;
//	CalculateScale(m_expandedBBox, m_matrix);
	m_scaleX = 1.0;
	m_scaleY = 1.0;

#if 0
//		CComQIPtr<IPDObjectGroup> parentgroup = m_parent;
//		if (parentgroup)
		if (m_parent)
		{
			static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_parent)->CalculateBounds();
		}
#endif
}

//virtual
void CPDObjectLayerGroup::Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
{
	m_backgroundBitmap = new Gdiplus::Bitmap((int)ceil(m_expandedBBox.Width*scaleX), (int)ceil(m_expandedBBox.Height*scaleY), PixelFormat32bppARGB);
	if (m_backgroundBitmap)
	{
		{
			Gdiplus::Graphics graphics(m_backgroundBitmap);

			graphics.SetSmoothingMode(pGraphics->GetSmoothingMode());

			graphics.ScaleTransform(scaleX, scaleY);
			graphics.TranslateTransform(-m_filterRect.X, -m_filterRect.Y);

			for (int i = 0; i < m_children->m_items.GetSize(); i++)
			{
				CComQIPtr<IPDObject> object = m_children->m_items[i];
				CPDObjectImpl<IPDObject>* pObject;

				pObject = static_cast<CPDObjectImpl<IPDObject>*>(object.p);

				pObject->Render(pRenderer, &graphics, scaleX, scaleY);
			}
		}

		double x = m_filterRect.X;
		double y = m_filterRect.Y;
		double width = m_filterRect.Width;
		double height = m_filterRect.Height;
		Gdiplus::RectF destRect((float)x, (float)y, (float)width, (float)height);

		double bitmapWidth = m_filterRect.Width*scaleX;//m_backgroundBitmap->GetWidth();
		double bitmapHeight = m_filterRect.Height*scaleY;//m_backgroundBitmap->GetHeight();

	//	pGraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

		pGraphics->DrawImage(
			m_backgroundBitmap,
			destRect,
			(float)0, (float)0, (float)bitmapWidth, (float)bitmapHeight,
			Gdiplus::UnitPixel/*,
			&imageAtt*/);

		delete m_backgroundBitmap;
		m_backgroundBitmap = NULL;
	}
}

STDMETHODIMP CPDObjectLayerGroup::getScreenBBox(RectD *pVal)
{
	// ????
	*pVal = m_bounds;//
	//ATLASSERT(0);
	return S_OK;
}

// INotifyGet
STDMETHODIMP CPDObjectLayerGroup::OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
{
	CalculateBounds();

	if (m_pDocument)	// TODO ????
	{
		m_pDocument->DistributeStories();
	}

	FireOnChanged(type, targetObject, dispID);
	return S_OK;
}

// CNotifySendImpl
STDMETHODIMP CPDObjectLayerGroup::FireOnChanged(NotifyType type, IUnknown* targetObject, /*IUnknown* immtargetObject,*/ DISPID dispID)
{
	if (m_lockCount == 0)
	{
		if (m_pDocument)
		{
			m_pDocument->FireOnChanged(type, targetObject, dispID);
		}
	}

	return CNotifySendImpl<CPDObjectLayerGroup>::FireOnChanged(type, targetObject, dispID);
}

// IObjectSerializable
STDMETHODIMP CPDObjectLayerGroup::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	CPDObjectGroupImpl<CPDObjectLayerGroup, IPDObjectLayerGroup>::Serialize(ar, node);

	node->putElement(L"layer", (IPDLayer*)m_layer);

	return S_OK;
}

STDMETHODIMP CPDObjectLayerGroup::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	CComQIPtr<IPDSpread> spread = pUnkExtra;
//	m_spread = spread;

	CComPtr<IPDDocument> document;
	spread->get_ownerDocument(&document);

	m_pDocument = static_cast<CPDDocument*>((IPDDocument*)document.p);

	CComPtr<IUnknown> layer;
	node->getElement(L"layer", NULL, &layer);
	m_layer = static_cast<CPDLayer*>((IPDLayer*)layer.p);

	CPDObjectGroupImpl<CPDObjectLayerGroup, IPDObjectLayerGroup>::Deserialize(ar, node, pUnkExtra);

	return S_OK;
}

STDMETHODIMP CPDObjectLayerGroup::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_PDObjectLayerGroup;
	return S_OK;
}
