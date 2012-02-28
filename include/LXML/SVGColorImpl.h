#ifndef w3c_SVGCOLORIMPL_h__
#define w3c_SVGCOLORIMPL_h__

namespace System
{
namespace Web
{

class WEBEXT SVGColorBase :
	public CSSValue,
	protected IRGBColorListener,
	protected ISVGICCColorListener
{
public:
	CTOR SVGColorBase();
	~SVGColorBase();

	void SetRGBColor(Graphics::Color clr);
	ErrorCode SetRGBColor(const WCHAR* s, const WCHAR* *pp = NULL);
	ErrorCode SetICCColor(const WCHAR* s, const WCHAR* *pp = NULL);

	SVGColorType get_colorType() const
	{
		return m_colorType;
	}

	virtual RGBColor* get_rgbColor()
	{
		return m_rgbColor;
	}

	virtual SVGICCColor* get_iccColor()
	{
		return m_iccColor;
	}

	virtual void setRGBColor(StringIn rgbColor);
	virtual void setRGBColorICCColor(StringIn rgbColor, StringIn iccColor);
	virtual void setColor(SVGColorType colorType, StringIn rgbColor, StringIn iccColor);
	virtual String get_cssText();

//protected:
public:
	RGBColor* m_rgbColor;
	SVGICCColor* m_iccColor;
	SVGColorType m_colorType;
};

}	// Web
}

#if 0
class LXUIEXT SVGColorImpl :
	public SVGColorImplImpl
{
public:
	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
		if (m_rgbColor)
		{
			m_rgbColor->m_pListener = NULL;
//			m_rgbColor->Release();
			m_rgbColor = NULL;
		}

		if (m_iccColor)
		{
			m_iccColor->m_pListener = NULL;
//			m_iccColor->Release();
			m_iccColor = NULL;
		}
	}

///
	STDMETHOD(get_colorType)(LSVGColorType *pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;
		*pVal = m_colorType;
		return S_OK;
	}

	STDMETHOD(get_rgbColor)(ILRGBColor **pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;
		*pVal = m_rgbColor;
//		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(get_iccColor)(/*[out, retval]*/ ILSVGICCColor* *pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;
		*pVal = m_iccColor;
//		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(setRGBColor)(BSTR rgbColor)
	{
		ASSERT(rgbColor != NULL);
		if (rgbColor == NULL) return E_INVALIDARG;

		if (SetRGBColor(rgbColor) == S_OK)
		{
			m_colorType = SVG_COLORTYPE_RGBCOLOR;
			return S_OK;
		}

		return E_FAIL;
	}

	STDMETHOD(setRGBColorICCColor)(/*[in]*/ BSTR rgbColor, /*[in]*/ BSTR iccColor)
	{
		ASSERT(rgbColor != NULL);
		if (rgbColor == NULL) return E_INVALIDARG;

		ASSERT(iccColor != NULL);
		if (iccColor == NULL) return E_INVALIDARG;

		if (SetRGBColor(rgbColor) == S_OK)
		{
			if (SetICCColor(iccColor) == S_OK)
			{
				m_colorType = SVG_COLORTYPE_RGBCOLOR_ICCCOLOR;
				return S_OK;
			}
		}

		return E_FAIL;
	}

	STDMETHOD(setColor)(/*[in]*/ LSVGColorType colorType, /*[in]*/ BSTR rgbColor, /*[in]*/ BSTR iccColor)
	{
		if (	colorType == SVG_COLORTYPE_RGBCOLOR ||
				colorType == SVG_COLORTYPE_RGBCOLOR_ICCCOLOR)
		{
			if (rgbColor == NULL)
				return E_INVALIDARG;

			if (SetRGBColor(rgbColor) != S_OK)
				return E_FAIL;

			if (colorType == SVG_COLORTYPE_RGBCOLOR_ICCCOLOR)
			{
				if (iccColor == NULL)
					return E_INVALIDARG;

				if (SetICCColor(iccColor) != S_OK)
					return E_FAIL;
			}
		}

		m_colorType = colorType;

		m_bCSSTextUpdated = false;

	// TODO, notify

		return S_OK;
	}

	// ILCSSValue
	STDMETHODIMP get_cssText(BSTR *pVal)
	{
		if (!m_bCSSTextUpdated)
		{
			OLECHAR buf[64];

			swprintf(buf, OLESTR("#%2.2X%2.2X%2.2X"),
				(int)m_rgbColor->m_red->m_floatValueUserUnit,
				(int)m_rgbColor->m_green->m_floatValueUserUnit,
				(int)m_rgbColor->m_blue->m_floatValueUserUnit);

			m_cssText = buf;
			m_bCSSTextUpdated = true;
		}

		return CSSValueImplImpl::get_cssText(pVal);
	}

// TODO, remove this
	STDMETHODIMP set_cssText(BSTR newVal)
	{
		ASSERT(0);
		return E_FAIL;
#if 0
		ErrorCode hr = SVGColorImplImpl::set_cssText(newVal);
		// if (FAILED(hr)) return hr; // Should probably do that, but LXMLEditor relies on setting any value, also invalid ones

		m_bCSSTextUpdated = true;
		m_cssValueType = CSS_CUSTOM;
		m_cssText = newVal;//CSSValueImpl<IBase>::set_cssText(newVal);

		return hr;
#endif
	}
};
#endif

#endif // w3c_SVGCOLORIMPL_H__
