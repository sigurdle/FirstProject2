#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDGradientStop.h"

#include "PDColor.h"
#include "PDGradient.h"

/////////////////////////
// CPDGradientStop

void CPDGradientStop::FinalRelease()
{
	if (m_color)
	{
		CComQIPtr<INotifySend> cp = m_color;
		cp->Unadvise(this);

		m_color->Release();
		m_color = NULL;
	}

	if (m_swatch)
	{
		CComQIPtr<INotifySend> cp = m_swatch;
		cp->Unadvise(this);

		m_swatch.Release();
	}
}

STDMETHODIMP CPDGradientStop::get_middle(/*[out, retval]*/ double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_middle;
	return S_OK;
}

STDMETHODIMP CPDGradientStop::put_middle(/*[in]*/ double newVal)
{
	m_middle = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDGradientStop::get_offset(/*[out, retval]*/ double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_offset;
	return S_OK;
}

STDMETHODIMP CPDGradientStop::put_offset(/*[in]*/ double newVal)
{
	m_offset = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDGradientStop::getFinalColor(IPDColor **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_color)
	{
		*pVal = m_color;
		(*pVal)->AddRef();
	}
	else if (m_swatch)
	{
		CComQIPtr<IPDSwatchColor> swatchColor = m_swatch;
		if (swatchColor)
		{
			swatchColor->get_color(pVal);
		}
		else
		{
			CComQIPtr<IPDSwatchTint> swatchTint = m_swatch;
			if (swatchTint)
			{
				ATLASSERT(0);
			//	swatchTint->get_color(pVal);
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CPDGradientStop::get_color(/*[out, retval]*/ IPDColor* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_color)
	{
		*pVal = m_color;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDGradientStop::get_swatch(IPDSwatch **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_swatch)
	{
		*pVal = m_swatch;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDGradientStop::put_swatch(IPDSwatch *newVal)
{
	if (m_swatch)
	{
		CComQIPtr<INotifySend> cp = m_swatch;
		cp->Unadvise(this);
	}

	if (m_color)
	{
		m_color->Unadvise(this);

		m_color->Release();
		m_color = NULL;
	}

	m_swatch = newVal;

	if (m_swatch)
	{
		CComQIPtr<INotifySend> cp = m_swatch;
		DWORD cookie;
		cp->Advise(this, &cookie);
	}

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDGradientStop::setColorRGB(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue)
{
	if (m_swatch)
	{
		CComQIPtr<INotifySend> cp = m_swatch;
		cp->Unadvise(this);
		m_swatch.Release();
	}

	if (m_color == NULL)
	{
		CComObject<CPDColor>::CreateInstance(&m_color);
		if (m_color)
		{
			m_color->AddRef();

			DWORD cookie = 0;
			m_color->Advise(this, &cookie);
			ATLASSERT(cookie);
		}
	}

	if (m_color)
	{
		m_color->m_colorMode = COLORMODE_RGB;
		m_color->m_channel[0] = red;
		m_color->m_channel[1] = green;
		m_color->m_channel[2] = blue;
		m_color->m_channel[3] = 0;
	}

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDGradientStop::get_parent(IPDGradient **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_parent;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDGradientStop::get_previousSibling(IPDGradientStop **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_previousSibling;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDGradientStop::get_nextSibling(IPDGradientStop **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_nextSibling;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDGradientStop::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"offset", _variant_t((float)m_offset));
	node->putAttribute(L"middle", _variant_t((float)m_middle));

	if (m_color)
	{
		node->serializeElement(L"color", (IPDColor*)m_color);
	}

	return S_OK;
}

STDMETHODIMP CPDGradientStop::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;

	node->getAttribute(L"offset", &v);
	m_offset = v;

	node->getAttribute(L"middle", &v);
	m_middle = v;

	ATLASSERT(m_color == NULL);
	CComObject<CPDColor>::CreateInstance(&m_color);
	if (m_color)
	{
		m_color->AddRef();
		if (SUCCEEDED(node->deserializeElement(L"color", (IPDColor*)m_color, NULL)))
		{
			DWORD cookie;
			m_color->Advise(this, &cookie);
		}
		else
		{
			m_color->Release();
			m_color = NULL;
		}
	}

	return S_OK;
}
