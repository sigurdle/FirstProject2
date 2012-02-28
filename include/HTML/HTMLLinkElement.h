#ifndef Web_HTMLLinkElement_h
#define Web_HTMLLinkElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLLinkElement : 
	public HTMLElement,
//	public CLElementEditASImpl<HTMLLinkElement>,
	public ElementEditVALImpl<HTMLLinkElement>,
//	public ILLinkStyle,
	public LinkStyleExternalImpl

//	public ILElementEditVAL,	// ILNodeEditVAL
{
public:
	CTOR HTMLLinkElement(NamedNodeMap* attributes);

	String get_type();
	void set_type(StringIn newVal);
	String get_rel();
	void set_rel(StringIn newVal);
	String get_href();
	void set_href(StringIn newVal);

	void LoadStyleSheet();

	Attr* get_typeAttr()
	{
		return m_typeAttr;
	}

	Attr* get_relAttr()
	{
		return m_relAttr;
	}

	Attr* get_hrefAttr()
	{
		return m_hrefAttr;
	}

protected:

	Attr* m_typeAttr;
	Attr* m_relAttr;
	Attr* m_hrefAttr;

/*
	STDMETHODIMP addedtodocument()
	{
		LoadStyleSheet();

		return S_OK;
	}
	STDMETHODIMP removedfromdocument()
	{
		return S_OK;
	}
	*/

#if 0
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		static int reentrance = 0;

		if (m_fireReentrance == 0)
		{
			m_fireReentrance++;

			// TODO don't always do this
			{
				CComBSTR media;
				getAttribute(L"media", &media);
				m_styleSheet->m_media->put_mediaText(media);
			}

			/*
		// If the stylesheet has changes, update the first textnode's text
			if (IsUnknownEqualUnknown(immtargetObject, m_styleSheet))
			{
				CComPtr<ILDOMNode> firstchild;
				get_firstChild(&firstchild);
				CComQIPtr<ILDOMCharacterData> chardata = firstchild;

				if (chardata)
				{
					BSTR bcssText;
					m_styleSheet->get_cssText(&bcssText);

					chardata->put_data(bcssText);

					SysFreeString(bcssText);
				}
			}
		// If the textnode's text changed, update the stylesheet
			else
			{
			// The first text child contains the source of the stylesheet
				CComPtr<ILDOMNode> firstchild;
				get_firstChild(&firstchild);
				CComQIPtr<ILDOMCharacterData> chardata = firstchild;
				if (chardata)
				{
					BSTR bdata;
					chardata->get_data(&bdata);

					m_styleSheet->set_cssText(bdata);

					SysFreeString(bdata);
				}
			}
*/

			FireOnChanged(type, targetObject, dispID);

			m_fireReentrance--;
		}

		LoadStyleSheet();

		FireOnChanged(type, targetObject, dispID);

		return Success;
	}
#endif

// EventTarget
	virtual bool dispatchEvent2(Event* evt, bool bCapture);
};

}	// Web
}

#endif // Web_HTMLLinkElement_h
