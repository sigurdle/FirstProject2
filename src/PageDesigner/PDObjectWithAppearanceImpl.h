#pragma once

#include "PDMatrix.h"
#include "PDAppearance.h"
class CPDRenderer;
//#include "PDRenderer.h"

template <class T, class IBase> class ATL_NO_VTABLE CPDObjectWithAppearanceImpl :
	public IBase//IPDObjectWithAppearance
{
public:
	CPDObjectWithAppearanceImpl()
	{
		m_appearance = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CComObject<CPDAppearance>::CreateInstance(&m_appearance);
		if (FAILED(hr)) return hr;
		m_appearance->AddRef();

		CComQIPtr<INotifyGet> get = static_cast<T*>(this)->GetUnknown();
		if (get)
		{
			DWORD cookie;
			m_appearance->Advise(get, &cookie);
		}

		return S_OK;
	}

	void FinalRelease()
	{
		if (m_appearance)
		{
			CComQIPtr<INotifyGet> get = static_cast<T*>(this)->GetUnknown();
			if (get)
			{
				m_appearance->Unadvise(get);
			}

			m_appearance->Release();
			m_appearance = NULL;
		}
	}

	CComObject<CPDAppearance>* m_appearance;

public:
	STDMETHODIMP get_appearance(IPDAppearance **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_appearance;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP put_appearance(IPDAppearance *newVal)
	{
		ATLASSERT(0);
		return S_OK;
	}
	STDMETHOD(get_filterRect)(/*[out, retval]*/ RectD *pVal)
	{
		*pVal = static_cast<T*>(this)->m_filterRect;
		return S_OK;
	}

	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
	{
		ATLASSERT(m_appearance);

		double finalScaleX = static_cast<T*>(this)->m_scaleX*scaleX;
		double finalScaleY = static_cast<T*>(this)->m_scaleY*scaleY;

		if (m_appearance->m_firstChild == NULL)
		{
			Gdiplus::Matrix oldmat;
			pGraphics->GetTransform(&oldmat);

			Gdiplus::Matrix matrix(
				(float)static_cast<T*>(this)->m_matrix->m_matrix[0][0], (float)static_cast<T*>(this)->m_matrix->m_matrix[0][1],
				(float)static_cast<T*>(this)->m_matrix->m_matrix[1][0], (float)static_cast<T*>(this)->m_matrix->m_matrix[1][1],
				(float)static_cast<T*>(this)->m_matrix->m_matrix[2][0], (float)static_cast<T*>(this)->m_matrix->m_matrix[2][1]);
			pGraphics->MultiplyTransform(&matrix);

			//pGraphics->ScaleTransform((float)scaleX, (float)scaleY);
			//graphics.TranslateTransform(-m_filterRect.X, -m_filterRect.Y);

			static_cast<T*>(this)->Render2(NULL, (DWORD)pGraphics, scaleX, scaleY);

			pGraphics->SetTransform(&oldmat);
		}
		else
		{
			Gdiplus::Bitmap* pBitmap = m_appearance->ProcessEffects(this, finalScaleX, finalScaleY);
			if (pBitmap)
			{
				Gdiplus::Matrix oldmat;
				pGraphics->GetTransform(&oldmat);

				Gdiplus::Matrix matrix(
					(float)static_cast<T*>(this)->m_matrix->m_matrix[0][0], (float)static_cast<T*>(this)->m_matrix->m_matrix[0][1],
					(float)static_cast<T*>(this)->m_matrix->m_matrix[1][0], (float)static_cast<T*>(this)->m_matrix->m_matrix[1][1],
					(float)static_cast<T*>(this)->m_matrix->m_matrix[2][0], (float)static_cast<T*>(this)->m_matrix->m_matrix[2][1]);
				pGraphics->MultiplyTransform(&matrix);

				// opacity
				Gdiplus::ColorMatrix colorMatrix = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
													0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
													0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
													0.0f, 0.0f, 0.0f, (float)static_cast<T*>(this)->m_opacity, 0.0f,
													0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

			// Create an ImageAttributes object and set its color matrix.
				Gdiplus::ImageAttributes imageAtt;
				imageAtt.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

				double x = m_appearance->m_expandedRect.X;
				double y = m_appearance->m_expandedRect.Y;
				double width = m_appearance->m_expandedRect.Width;
				double height = m_appearance->m_expandedRect.Height;
				Gdiplus::RectF destRect((float)x, (float)y, (float)width, (float)height);

				double bitmapWidth = m_appearance->m_expandedRect.Width*finalScaleX;//pBitmap->GetWidth();
				double bitmapHeight = m_appearance->m_expandedRect.Height*finalScaleY;//pBitmap->GetHeight();

			//	ATLASSERT(bitmapWidth == (int)ceil(width*finalScaleX));
			//	ATLASSERT(bitmapHeight == (int)ceil(height*finalScaleY));

			//	pGraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

				pGraphics->DrawImage(
					pBitmap,
					destRect,
					(float)0, (float)0, (float)bitmapWidth, (float)bitmapHeight,
					Gdiplus::UnitPixel,
					&imageAtt);

				pGraphics->SetTransform(&oldmat);

				delete pBitmap;
			}
		}
	}

// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node)
	{
		node->serializeElement(L"filter", static_cast<IUnknown*>((IPDAppearance*)m_appearance));
		//node->putElement(L"filter", static_cast<IUnknown*>((IPDAppearance*)m_appearance));
		return S_OK;
	}
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		node->deserializeElement(L"filter", static_cast<IUnknown*>((IPDAppearance*)m_appearance), NULL);
		/*
	// TODO, have it so that appearance is (de)serialized directly below 'filter' element

		if (m_appearance)
		{
			m_appearance->Release();
			m_appearance = NULL;
		}

		CComPtr<IUnknown> p;
		node->getElement(L"filter", NULL, &p);
		m_appearance = static_cast<CComObject<CPDAppearance>*>((IPDAppearance*)p.p);
		m_appearance->AddRef();
		*/

		return S_OK;
	}
};
