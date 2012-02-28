#ifndef Web_HTMLDocument_h
#define Web_HTMLDocument_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLFramesCollection : public Object
//	public ILHTMLFramesCollection
{
public:
	CTOR HTMLFramesCollection()
	{
	}

//	CArray<ILDOMElement*,ILDOM
//	CLHTMLWindow* m_pOwnerDocument;

public:
	unsigned int get_length()
	{
		return 0;
	}

#if 0
	STDMETHOD(item)(unsigned int Index, /*[out,retval]*/ VARIANT* pvarResult)
	{
		return S_OK;
	}
#endif
};

class HTMLEXT HTMLDocument : 
	public Document,
	public EventTarget,
//	public DocumentViewImpl<HTMLDocument>,
	public DocumentEvent,
	public DocumentRangeImpl<HTMLDocument>,
	public CLDOMDocumentTraversalImpl<HTMLDocument>,

	//public DocumentCSSImpl<HTMLDocument>,
//	public DocumentASImpl<HTMLDocument>,
	public DocumentEditVALImpl<HTMLDocument>,
	public XPath::XPathEvaluator,//Impl<HTMLDocument>,

//	public IElementParallelTimeContainer,
//	public IDocumentEditVAL,	// ILNodeEditVAL

	public CNotifyGetImpl<HTMLDocument>,
	public CNotifySendImpl<HTMLDocument>
{
public:
	CTOR HTMLDocument();

	HTMLFramesCollection* m_frames;

	virtual void Seek(double tps);

#if 0
	double m_currentTimeSeconds;

	bool Seek(double seconds)
	{
	// TODO: remove this?
		bool bAny = DoAnimationsForAllElements(m_documentElement/*, m_currentTimeSeconds*/, seconds);

		m_currentTimeSeconds = seconds;

		return bAny;
	}
#endif


// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

public:
	String get_title();
	void set_title(StringIn newVal);
	HTMLElement* get_body();
	String get_namespaceURI();

//	LXML::Element* createElementNS(const sysstring& namespaceURI, const sysstring& qualifiedName);

	double get_simpleTime()
	{
		ASSERT(0);
		return 0;
#if 0
		if (m_documentElement)
		{
			CComPtr<ILDOMElement> body = GetElementByTagName(m_documentElement, L"body", FALSE);
			if (body)
			{
				CComQIPtr<ILElementTime> bodyTime = body;

				bodyTime->get_simpleTime(pVal);
			}
		}

		return S_OK;
#endif
	}

	double get_activeTime()
	{
		ASSERT(0);
		return 0;
#if 0
		if (m_documentElement)
		{
			CComPtr<ILDOMElement> body = GetElementByTagName(m_documentElement, L"body", FALSE);
			if (body)
			{
				CComQIPtr<ILElementTime> bodyTime = body;

				bodyTime->get_activeTime(pVal);
			}
		}
/*
		if (pVal == NULL) return E_POINTER;
		*pVal = m_activeTime;
		*/
		return S_OK;
#endif
	}


// IElementTimeContainer
	System::StringW* get_timeContainer()
	{
		ASSERT(0);
		return NULL;
#if 0
		if (m_documentElement)
		{
			CComPtr<ILDOMElement> body = GetElementByTagName(m_documentElement, L"body", FALSE);
			if (body)
			{
				CComQIPtr<ILElementTimeContainer> bodyTime = body;

				return bodyTime->get_timeContainer(pVal);
			}
		}

		*pVal = SysAllocString(L"none");	// ???
		return S_OK;
#endif
	}

	void seekElement(double seekTo);
};

}	// Web
}

#endif // Web_HTMLDocument_h
