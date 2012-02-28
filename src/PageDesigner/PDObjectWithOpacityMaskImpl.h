#pragma once

template <class T> class ATL_NO_VTABLE CPDObjectWithOpacityMaskImpl :
	public IPDObjectWithOpacityMask
{
public:
	CPDObjectWithOpacityMaskImpl()
	{
		m_opacityMaskEnabled = VARIANT_TRUE;
		m_opacityMaskLinked = VARIANT_TRUE;
		m_opacityMaskClip = VARIANT_FALSE;
		m_opacityMaskInvert = VARIANT_FALSE;
	}

	int FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		if (m_opacityMaskGroup)
		{
			CComQIPtr<INotifySend> cp = m_opacityMaskGroup;
			cp->Unadvise(static_cast<T*>(this));
		}
	}

	VARIANT_BOOL m_opacityMaskEnabled;
	VARIANT_BOOL m_opacityMaskLinked;
	VARIANT_BOOL m_opacityMaskClip;
	VARIANT_BOOL m_opacityMaskInvert;
	CComPtr<IPDObjectGroup> m_opacityMaskGroup;

	void Mask(Gdiplus::Bitmap* pBitmap, RectD filterRect, double scaleX, double scaleY, Gdiplus::SmoothingMode smoothingMode)
	{
		if (m_opacityMaskEnabled)
		{
			Gdiplus::Bitmap* pMask = GetOpacityMaskBitmap(filterRect, scaleX, scaleY, smoothingMode);
			if (pMask)
			{
				ProcessMaskBitmap(pMask, pBitmap);
				delete pMask;
			}
		}
	}

	Gdiplus::Bitmap* GetOpacityMaskBitmap(RectD filterRect, double scaleX, double scaleY, Gdiplus::SmoothingMode smoothingMode)
	{
		Gdiplus::Bitmap* pMask = NULL;

		if (m_opacityMaskGroup)
		{
			pMask = new Gdiplus::Bitmap((int)ceil(filterRect.Width*scaleX), (int)ceil(filterRect.Height*scaleY), PixelFormat32bppARGB);
			if (pMask)
			{
				CPDObjectGroup* pOpacityMaskGroup = static_cast<CPDObjectGroup*>(m_opacityMaskGroup.p);

				{
					Gdiplus::Graphics graphics(pMask);
					graphics.SetSmoothingMode(smoothingMode);

					graphics.ScaleTransform((float)scaleX, (float)scaleY);
					graphics.TranslateTransform((float)-filterRect.X, (float)-filterRect.Y);

					pOpacityMaskGroup->Render(NULL, &graphics, scaleX, scaleY);
				}
			}
		}

		return pMask;
	}

	void ProcessMaskBitmap(Gdiplus::Bitmap* pMask, Gdiplus::Bitmap* pBitmap)
	{
		ATLASSERT(pMask->GetWidth() == pBitmap->GetWidth());
		ATLASSERT(pMask->GetHeight() == pBitmap->GetHeight());

		Gdiplus::BitmapData bitmapData;
		pBitmap->LockBits(
			&Gdiplus::Rect(0, 0, pMask->GetWidth(), pMask->GetHeight()),
			Gdiplus::ImageLockModeWrite,
			PixelFormat32bppARGB,
			&bitmapData);

		Gdiplus::BitmapData maskData;
		pMask->LockBits(
			&Gdiplus::Rect(0, 0, pMask->GetWidth(), pMask->GetHeight()),
			Gdiplus::ImageLockModeRead,
			PixelFormat32bppARGB,
			&maskData);

		for (UINT y = 0; y < bitmapData.Height; y++)
		{
			ARGBPixel* bitmapPixel = (ARGBPixel*)((BYTE*)bitmapData.Scan0+bitmapData.Stride*y);
			ARGBPixel* maskPixel = (ARGBPixel*)((BYTE*)maskData.Scan0+maskData.Stride*y);

			for (UINT x = 0; x < bitmapData.Width; x++)
			{
				int maskOpacity = 255 - (int)maskPixel->alpha*((maskPixel->red + maskPixel->green + maskPixel->blue)/3)/255;

				bitmapPixel->alpha = bitmapPixel->alpha*maskOpacity/255;

				bitmapPixel++;
				maskPixel++;
			}
		}

		pBitmap->UnlockBits(&bitmapData);
		pMask->UnlockBits(&maskData);
	}

public:
	STDMETHODIMP get_opacityMaskGroup(/*[out, retval]*/ IPDObjectGroup* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_opacityMaskGroup;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP put_opacityMaskGroup(/*[in]*/ IPDObjectGroup* newVal)
	{
		if (!IsUnknownEqualUnknown(m_opacityMaskGroup, newVal))
		{
		// Release old (if any)
			if (m_opacityMaskGroup)
			{
				m_opacityMaskEnabled = VARIANT_FALSE;

				CComQIPtr<INotifySend> cp = m_opacityMaskGroup;
				cp->Unadvise(static_cast<T*>(this));

				{
					CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_opacityMaskGroup);
					pObject->m_parent = NULL;
					pObject->detachFromSpread();
				}

				static_cast<T*>(this)->FireOnChanged(NOTIFY_REMOVE, m_opacityMaskGroup, /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);

				m_opacityMaskGroup.Release();
			}

		// Set new
			m_opacityMaskGroup = newVal;

			if (m_opacityMaskGroup)
			{
				m_opacityMaskEnabled = VARIANT_TRUE;

				{
					CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_opacityMaskGroup);
					pObject->m_parent = static_cast<CPDObjectUnknownImpl<IPDObjectUnknown>*>((IPDObjectUnknown*)static_cast<T*>(this));
					pObject->attachToSpread(pObject->m_parent);
				}

				{
					CComQIPtr<INotifySend> cp = m_opacityMaskGroup;
					DWORD cookie;
					cp->Advise(static_cast<T*>(this), &cookie);
				}

				static_cast<T*>(this)->FireOnChanged(NOTIFY_ADD, m_opacityMaskGroup, /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);
			}
		}

		return S_OK;
	}

	STDMETHODIMP get_opacityMaskClip(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_opacityMaskClip;
		return S_OK;
	}

	STDMETHODIMP put_opacityMaskClip(/*[in]*/ VARIANT_BOOL newVal)
	{
		if ((m_opacityMaskClip == 0) != (newVal == 0))
		{
			m_opacityMaskClip = newVal;
			static_cast<T*>(this)->FireOnChanged(NOTIFY_MODIFY, static_cast<T*>(this)->GetUnknown(), /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);
		}

		return S_OK;
	}

	STDMETHODIMP get_opacityMaskInvert(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_opacityMaskInvert;
		return S_OK;
	}

	STDMETHODIMP put_opacityMaskInvert(/*[in]*/ VARIANT_BOOL newVal)
	{
		if ((m_opacityMaskInvert == 0) != (newVal == 0))
		{
			m_opacityMaskInvert = newVal;
			static_cast<T*>(this)->FireOnChanged(NOTIFY_MODIFY, static_cast<T*>(this)->GetUnknown(), /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);
		}

		return S_OK;
	}

	STDMETHODIMP get_opacityMaskEnabled(VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_opacityMaskEnabled;
		return S_OK;
	}

	STDMETHODIMP put_opacityMaskEnabled(VARIANT_BOOL newVal)
	{
		if ((m_opacityMaskEnabled == 0) != (newVal == 0))
		{
			m_opacityMaskEnabled = newVal;
			static_cast<T*>(this)->FireOnChanged(NOTIFY_MODIFY, static_cast<T*>(this)->GetUnknown(), /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);
		}

		return S_OK;
	}

	STDMETHODIMP get_opacityMaskLinked(VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_opacityMaskLinked;
		return S_OK;
	}

	STDMETHODIMP put_opacityMaskLinked(VARIANT_BOOL newVal)
	{
		if ((m_opacityMaskLinked == 0) != (newVal == 0))
		{
			m_opacityMaskLinked = newVal;
			static_cast<T*>(this)->FireOnChanged(NOTIFY_MODIFY, static_cast<T*>(this)->GetUnknown(), /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);
		}

		return S_OK;
	}

// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node)
	{
		node->putAttribute(L"opacityMask-clip", _variant_t(m_opacityMaskClip));
		node->putAttribute(L"opacityMask-invert", _variant_t(m_opacityMaskInvert));

		node->putElement(L"opacityMask-group", m_opacityMaskGroup);
		return S_OK;
	}

	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		_variant_t v;

		node->getAttribute(L"opacityMask-clip", &v);
		m_opacityMaskClip = v;

		node->getAttribute(L"opacityMask-invert", &v);
		m_opacityMaskInvert = v;

		node->getElement(L"opacityMask-group", NULL, (IUnknown**)&m_opacityMaskGroup);
		return S_OK;
	}
};
