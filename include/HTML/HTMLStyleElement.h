#ifndef Web_HTMLStyleElement_h
#define Web_HTMLStyleElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLStyleElement : 
	public HTMLElement,
//	public CLElementEditASImpl<HTMLStyleElement>,
	public ElementEditVALImpl<HTMLStyleElement>,
	public LinkStyleStyleImpl,//<HTMLStyleElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<HTMLStyleElement>,
	protected CNotifySendImpl<HTMLStyleElement>
{
public:
	CTOR HTMLStyleElement(NamedNodeMap* attributes);

	CSSStyleSheet* get_styleSheet();
	String get_media();
	void set_media(StringIn newVal);
	String get_type();
	void set_type(StringIn newVal);
	bool get_disabled() const;
	void set_disabled(bool newVal);

	Attr* get_mediaAttr()
	{
		return m_mediaAttr;
	}

	Attr* get_typeAttr()
	{
		return m_typeAttr;
	}

protected:

	Attr* m_mediaAttr;
	Attr* m_typeAttr;

#if 0
// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, Object *targetObject, Object *immtargetObject, DISPID dispID)
	{
		if (m_cssreentrancy == 0)
		{
			m_cssreentrancy++;

			// TODO don't always do this
			{
				sysstring media = getAttribute(OLESTR("media"));
				m_styleSheet->get_media()->put_mediaText(media);
			}

		// If the textnode's text changed, update the stylesheet
			{
			// The first text child contains the source of the stylesheet
			//	CComPtr<ILDOMNode> firstchild;
			//	get_firstChild(&firstchild);
			//	CComQIPtr<ILDOMCharacterData> chardata = firstchild;
			//	if (chardata)
				{
					sysstring data = get_textContent();

					m_styleSheet->set_cssText(data);
				}
			}
	
			m_cssreentrancy--;
		}

		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}
#endif

	void OnChanged();

// EventTarget
	virtual bool dispatchEvent2(Event* evt, bool bCapture);

/*
	STDMETHODIMP addedtodocument()
	{
		ASSERT(m_ownerDocument);

		CComQIPtr<ILDocumentStyle> documentStyle = m_ownerDocument;
		if (documentStyle)
		{
			CComPtr<ILStyleSheetList> styleSheetList;
			documentStyle->get_styleSheets(&styleSheetList);

			styleSheetList->append(m_styleSheet);
		}

		return S_OK;
	}
	STDMETHODIMP removedfromdocument()
	{
		return S_OK;
	}
	*/

#if 0
	// INotifySend
	STDMETHODIMP FireOnChanged(NotifyType type, IUnknown* targetObject, /*IUnknown* immtargetObject,*/ DISPID dispID)
	{
		OnChanged(type, targetObject, GetUnknown(), dispID);
		return CNotifySendImpl<HTMLStyleElement>::FireOnChanged(type, targetObject, dispID);
	}
#endif

#if 0
// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
	{
		CLLinkStyleImpl<HTMLStyleElement>::OnChanged(type, targetObject, immtargetObject, dispID);

		static int reentrance = 0;

		if (m_fireReentrance == 0)
		{
			m_fireReentrance++;

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

			FireOnChanged(type, targetObject, dispID);

			m_fireReentrance--;
		}

		return S_OK;
	}
#endif

};

}	// Web
}

#endif // Web_HTMLStyleElement_h
