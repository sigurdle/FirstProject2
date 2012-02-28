#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDBrush.h"

#include "PDColor.h"
#include "PDGradient.h"

/////////////////////////
// CPDBrush

void CPDBrush::FinalRelease()
{
	if (m_color)
	{
		m_color->Unadvise(this);
		m_color->Release();
		m_color = NULL;
	}

	if (m_gradient)
	{
		m_gradient->Unadvise(this);
		m_gradient->Release();
		m_gradient = NULL;
	}

	if (m_swatch)
	{
		CComQIPtr<INotifySend> cp = m_swatch;
		cp->Unadvise(this);
		m_swatch.Release();
	}
}

STDMETHODIMP CPDBrush::get_brushType(PDBrushType *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_brushType;

	return S_OK;
}

STDMETHODIMP CPDBrush::put_brushType(PDBrushType newVal)
{
	m_brushType = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDBrush::get_swatch(IPDSwatch* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_swatch;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDBrush::put_swatch(IPDSwatch* newVal)
{
//	setNone();
	if (m_swatch)
	{
		CComQIPtr<INotifySend> cp = m_swatch;
		cp->Unadvise(this);
		m_swatch.Release();
	}

	m_swatch = newVal;

	if (m_swatch)
	{
		{
			CComQIPtr<INotifySend> cp = m_swatch;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		PDSwatchType swatchType;
		m_swatch->get_swatchType(&swatchType);

		if (swatchType == SWATCH_NONE)
			m_brushType = BRUSH_NONE;
		else if (swatchType == SWATCH_COLOR || swatchType == SWATCH_TINT)
			m_brushType = BRUSH_COLOR;
		else if (swatchType == SWATCH_GRADIENT)
			m_brushType = BRUSH_GRADIENT;
		else if (swatchType == SWATCH_PATTERN)
			m_brushType = BRUSH_PATTERN;
		else
			ATLASSERT(0);
	}
	else
		m_brushType = BRUSH_NONE;

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDBrush::get_gradient(IPDGradient **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_swatch)
	{
		CComQIPtr<IPDSwatchGradient> swatchGradient = m_swatch;
		if (swatchGradient)
		{
			swatchGradient->get_gradient(pVal);
		}
		else
			*pVal = NULL;
	}
	else
		*pVal = m_gradient;

	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPDBrush::get_color(IPDColor **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_swatch)
	{
		CComQIPtr<IPDSwatchColor> swatchColor;
		CComQIPtr<IPDSwatchTint> swatchTint;
		if (swatchColor = m_swatch)
		{
			swatchColor->get_color(pVal);
		}
		else if (swatchTint = m_swatch)
		{
			CComPtr<IPDSwatchColor> swatchColor;
			swatchTint->get_swatchColor(&swatchColor);

			swatchColor->get_color(pVal);
		}
		else
			*pVal = NULL;
	}
	else
		*pVal = m_color;

	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPDBrush::get_colorTint(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_colorTint;

	/*
	if (m_swatch)
	{
	}
	else
	*/

	return S_OK;
}

STDMETHODIMP CPDBrush::put_colorTint(double newVal)
{
	m_colorTint = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}


STDMETHODIMP CPDBrush::get_tintedColor(IPDColor **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDColor>* color;
	CComObject<CPDColor>::CreateInstance(&color);

	CComObject<CPDColor>* scolor;

	if (m_swatch)
	{
		CComQIPtr<IPDSwatchColor> swatchColor;
		CComQIPtr<IPDSwatchTint> swatchTint;
		if (swatchColor = m_swatch)
		{
			swatchColor->get_color((IPDColor**)&scolor);
		}
		else if (swatchTint = m_swatch)
		{
			CComPtr<IPDSwatchColor> swatchColor;
			swatchTint->get_swatchColor(&swatchColor);

			swatchColor->get_color((IPDColor**)&scolor);
		}
		else
			*pVal = NULL;

		color->m_colorMode = scolor->m_colorMode;
		color->m_channel[0] = 255-((255-scolor->m_channel[0])*m_colorTint);
		color->m_channel[1] = 255-((255-scolor->m_channel[1])*m_colorTint);
		color->m_channel[2] = 255-((255-scolor->m_channel[2])*m_colorTint);
		color->m_channel[3] = 255-((255-scolor->m_channel[3])*m_colorTint);
	}
	else
	{
		scolor = m_color;
		scolor->AddRef();

		color->m_colorMode = scolor->m_colorMode;
		color->m_channel[0] = scolor->m_channel[0];
		color->m_channel[1] = scolor->m_channel[1];
		color->m_channel[2] = scolor->m_channel[2];
		color->m_channel[3] = scolor->m_channel[3];
	}

	*pVal = color;
	(*pVal)->AddRef();

	scolor->Release();

	return S_OK;
}

STDMETHODIMP CPDBrush::get_tintedRGBColor(IPDColor **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDColor>* color;
	CComObject<CPDColor>::CreateInstance(&color);

	CComObject<CPDColor>* scolor;

	if (m_swatch)
	{
		CComQIPtr<IPDSwatchColor> swatchColor;
		CComQIPtr<IPDSwatchTint> swatchTint;
		if (swatchColor = m_swatch)
		{
			swatchColor->get_color((IPDColor**)&scolor);
		}
		else if (swatchTint = m_swatch)
		{
			CComPtr<IPDSwatchColor> swatchColor;
			swatchTint->get_swatchColor(&swatchColor);

			swatchColor->get_color((IPDColor**)&scolor);
		}
		else
			*pVal = NULL;

		color->m_colorMode = COLORMODE_RGB;
		color->m_channel[0] = 255-((255-scolor->m_channel[0])*m_colorTint);
		color->m_channel[1] = 255-((255-scolor->m_channel[1])*m_colorTint);
		color->m_channel[2] = 255-((255-scolor->m_channel[2])*m_colorTint);
	}
	else
	{
		scolor = m_color;
		scolor->AddRef();

		color->m_colorMode = COLORMODE_RGB;
		color->m_channel[0] = scolor->m_channel[0];
		color->m_channel[1] = scolor->m_channel[1];
		color->m_channel[2] = scolor->m_channel[2];
	}

	*pVal = color;
	(*pVal)->AddRef();

	scolor->Release();

	return S_OK;
}

STDMETHODIMP CPDBrush::setNone()
{
	m_brushType = BRUSH_NONE;
	/*
	if (m_swatch)
	{
		m_swatch.Release();
	}

	if (m_color)
	{
		m_color->Release();
		m_color = NULL;
	}

	if (m_gradient)
	{
		m_gradient->Release();
		m_gradient = NULL;
	}
	*/
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDBrush::setGradient(IPDGradient* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	m_brushType = BRUSH_GRADIENT;
//	setNone();

	if (m_swatch)
	{
		CComQIPtr<INotifySend> cp = m_swatch;
		cp->Unadvise(this);
		m_swatch.Release();
	}

	CComObject<CPDGradient>::CreateInstance(&m_gradient);
	m_gradient->AddRef();
	{
		DWORD cookie;
		m_gradient->Advise(this, &cookie);
	}

	*pVal = m_gradient;
	(*pVal)->AddRef();

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDBrush::setColor(IPDColor **pVal)
{
	if (pVal == NULL) return E_POINTER;

	//setNone();

	if (m_swatch)
	{
		CComQIPtr<INotifySend> cp = m_swatch;
		cp->Unadvise(this);
		m_swatch.Release();
	}

	if (m_color == NULL)
	{
		CComObject<CPDColor>::CreateInstance(&m_color);
		m_color->AddRef();
		{
			DWORD cookie;
			m_color->Advise(this, &cookie);
		}
	}

	if (m_brushType != BRUSH_COLOR)
	{
		m_brushType = BRUSH_COLOR;
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	}

	*pVal = m_color;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPDBrush::get_x1(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_x1;
	return S_OK;
}

STDMETHODIMP CPDBrush::put_x1(double newVal)
{
	m_x1 = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDBrush::get_y1(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_y1;
	return S_OK;
}

STDMETHODIMP CPDBrush::put_y1(double newVal)
{
	m_y1 = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDBrush::get_x2(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_x2;
	return S_OK;
}

STDMETHODIMP CPDBrush::put_x2(double newVal)
{
	m_x2 = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDBrush::get_y2(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_y2;
	return S_OK;
}

STDMETHODIMP CPDBrush::put_y2(double newVal)
{
	m_y2 = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDBrush::clone(IPDBrush **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDBrush>* pBrush;
	CComObject<CPDBrush>::CreateInstance(&pBrush);
	if (pBrush)
	{
		DWORD cookie;

		pBrush->m_brushType = m_brushType;

		if (m_swatch)
		{
			pBrush->m_swatch = m_swatch;
			CComQIPtr<INotifySend> cp = pBrush->m_swatch;
			cp->Advise(pBrush, &cookie);
		}

		if (m_color)
		{
			m_color->clone((IPDColor**)&pBrush->m_color);
			pBrush->m_color->Advise(pBrush, &cookie);
		}

		if (m_gradient)
		{
			m_gradient->clone((IPDGradient**)&pBrush->m_gradient);
			pBrush->m_gradient->Advise(pBrush, &cookie);
		}

		*pVal = pBrush;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDBrush::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"type", _variant_t((long)m_brushType));

	if (m_color)
	{
		node->serializeElement(L"color", (IPDColor*)m_color);
	}
	return S_OK;
}

STDMETHODIMP CPDBrush::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;
	node->getAttribute(L"type", &v);
	m_brushType = (PDBrushType)(long)v;

	if (m_brushType == BRUSH_COLOR)
	{
		CComObject<CPDColor>::CreateInstance(&m_color);
		m_color->AddRef();

		DWORD cookie;
		m_color->Advise(this, &cookie);

		node->deserializeElement(L"color", (IPDColor*)m_color, NULL);
	}

//	node->deserializeElement(L"color", (IPDColor*)m_color);
	return S_OK;
}

#if 0
STDMETHODIMP CPDBrush::saveAsXML(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node)
{
	CComQIPtr<IDOMElement> element = node;
	if (element)
	{
		WCHAR str[256];

		swprintf(str, L"%d", m_brushType);
		element->setAttribute(L"type", str);

		if (m_color)
		{
			CComPtr<IDOMElement> elementColor;
			document->createElement(L"color", &elementColor);
			m_color->saveAsXML(document, elementColor);
			element->appendChild(elementColor, NULL);
		}

		return S_OK;
	}
	else
		return E_FAIL;
}

IDOMElement* FindByTagName(IDOMElement* parent, BSTR tagName, BOOL bDeep = TRUE);

STDMETHODIMP CPDBrush::loadXML(/*[in]*/ IDOMNode* node)
{
	CComQIPtr<IDOMElement> element = node;
	if (element)
	{
		BSTR bstr;

		element->getAttribute(L"type", &bstr);
		m_brushType = (PDBrushType)atol(_bstr_t(bstr, false));

		CComPtr<IDOMElement> elementColor = FindByTagName(element, L"color", FALSE);
		if (elementColor)
		{
			CComObject<CPDColor>::CreateInstance(&m_color);
			m_color->AddRef();
			m_color->loadXML(elementColor);
		}

		return S_OK;
	}
	else
		return E_FAIL;
}
#endif

STDMETHODIMP CPDBrush::IsEqual(IPDBrush *brush)
{
	CPDBrush* pBrush = static_cast<CPDBrush*>(brush);
	if (brush == NULL) return S_FALSE;

	if (m_brushType != pBrush->m_brushType) return S_FALSE;

	if (m_brushType == BRUSH_COLOR)
	{
		if (m_color->m_colorMode != pBrush->m_color->m_colorMode) return S_FALSE;
		if (m_color->m_channel[0] != pBrush->m_color->m_channel[0]) return S_FALSE;
		if (m_color->m_channel[1] != pBrush->m_color->m_channel[1]) return S_FALSE;
		if (m_color->m_channel[2] != pBrush->m_color->m_channel[2]) return S_FALSE;
		if (m_color->m_colorMode == COLORMODE_CMYK) if (m_color->m_channel[3] != pBrush->m_color->m_channel[3]) return S_FALSE;
	}

	return S_OK;
}

STDMETHODIMP CPDBrush::setCommon(IPDBrush *brush)
{
	CPDBrush* pBrush = static_cast<CPDBrush*>(brush);

	if (m_brushType != tomUndefined)
	{
		if (m_brushType != pBrush->m_brushType)
		{
			m_brushType = (PDBrushType)tomUndefined;
		}
	}

	if (m_brushType == BRUSH_COLOR)
	{
		CComObject<CPDColor>* color2 = pBrush->m_color;

		for (int ch = 0; ch < 4; ch++)
		{
			if (m_color->m_channel[ch] != tomUndefined)
			{
				if (m_color->m_channel[ch] != color2->m_channel[ch])
					m_color->m_channel[ch] = tomUndefined;
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CPDBrush::getCommon(IPDBrush *brush)
{
	CPDBrush* pBrush = static_cast<CPDBrush*>(brush);

	if (pBrush->m_brushType != tomUndefined)
	{
		m_brushType = pBrush->m_brushType;
	}

	if (pBrush->m_brushType == BRUSH_COLOR)
	{
		for (int ch = 0; ch < 4; ch++)
		{
			if (pBrush->m_color->m_channel[ch] != tomUndefined)
				m_color->m_channel[ch] = pBrush->m_color->m_channel[ch];
		}
	}

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}
