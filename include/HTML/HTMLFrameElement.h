#ifndef Web_HTMLFrameElement_h
#define Web_HTMLFrameElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLFrameElement :
	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLFrameElement>,
	public ElementEditVALImpl<HTMLFrameElement>,
	public IEmbeddingElement,
//
	public Net::IBindCallback,

	protected CNotifyGetImpl<HTMLFrameElement>,
	protected CNotifySendImpl<HTMLFrameElement>
{
public:
	CTOR HTMLFrameElement(NamedNodeMap* attributes);
	~HTMLFrameElement();

	inline PHTMLFrameElement* GetPElement()
	{
		return (PHTMLFrameElement*)m_pNode;
	}

	ErrorCode Load();

	ErrorCode OnObjectAvailable(Object* object, StringIn url);
	virtual ErrorCode OnDataAvailable(size_t cbSize, IO::Stream* stream)
	{
		return Success;
	}
	virtual ErrorCode OnDone()
	{
		return Success;
	}

//	void OnDocumentReady(DownloadDocument* document);

	long get_frameSpacing();
	void set_frameSpacing(long newVal);
	/*
	long get_border();
	void set_border(long newVal);
	*/
	String get_scrolling();
	void set_scrolling(StringIn newVal);
	bool get_noResize();
	void set_noResize(bool newVal);
	String get_src();
	void set_src(StringIn newVal);
	String get_name();
	void set_name(StringIn newVal);
#if 0
	STDMETHOD(get_marginHeight)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_marginHeight)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_marginWidth)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_marginWidth)(/*[in]*/ VARIANT newVal);
#endif
	String get_longDesc();
	void set_longDesc(StringIn newVal);
	String get_frameBorder();
	void set_frameBorder(StringIn newVal);

	Document* get_contentDocument();
	IWindow* get_contentWindow();

	Attr* get_srcAttr()
	{
		return m_src;
	}

	Attr* get_nameAttr()
	{
		return m_name;
	}

// IHTMLFrameBase2
#if 0
        virtual /* [id][propget] */ ErrorCode STDMETHODCALLTYPE get_contentWindow( 
            /* [out][retval] */ IHTMLWindow2 **p)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [bindable][displaybind][id][propput] */ ErrorCode STDMETHODCALLTYPE put_onload( 
            /* [in] */ VARIANT v)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [bindable][displaybind][id][propget] */ ErrorCode STDMETHODCALLTYPE get_onload( 
            /* [out][retval] */ VARIANT *p)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [bindable][displaybind][id][propput] */ ErrorCode STDMETHODCALLTYPE put_onreadystatechange( 
            /* [in] */ VARIANT v)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [bindable][displaybind][id][propget] */ ErrorCode STDMETHODCALLTYPE get_onreadystatechange( 
            /* [out][retval] */ VARIANT *p)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [id][propget] */ ErrorCode STDMETHODCALLTYPE get_readyState( 
            /* [out][retval] */ BSTR *p)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [id][propput] */ ErrorCode STDMETHODCALLTYPE put_allowTransparency( 
            /* [in] */ VARIANT_BOOL v)
		  {
			  return E_NOTIMPL;
		  }
        
        virtual /* [id][propget] */ ErrorCode STDMETHODCALLTYPE get_allowTransparency( 
            /* [out][retval] */ VARIANT_BOOL *p)
		  {
			  return E_NOTIMPL;
		  }
#endif

public:

	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<LongValue> > >* m_marginWidth;
	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<LongValue> > >* m_marginHeight;

//	CLXUIFrameContent* m_pFrameContent;
	Gui::FrameworkElement* m_pFrameContent;

protected:

// EventTarget
	virtual bool dispatchEvent2(Event* evt, bool bCapture);

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

	virtual void OnAttrValueChanged(StringIn /*nodeName*/, Attr* attr);

	Attr* m_src;
	Attr* m_name;
};

}	// Web
}

#endif // Web_HTMLFrameElement_h
