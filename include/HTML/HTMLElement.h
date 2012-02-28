#ifndef Web_HTMLElement_h
#define Web_HTMLElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLElement : public Element
{
public:

	CTOR HTMLElement(PElementBase* pelement);
	CTOR HTMLElement(PElementBase* pelement, NamedNodeMap* attributes);

	String get_className();
	void set_className(StringIn newVal);

	Attr* get_classAttr()
	{
		return m_classAttr;
	}

	ElementTimeContainerImpl* m_timeContainerImpl;

	static ImmutableString<WCHAR> s_className_str;

// Extensions (similar to MSHTML)

#if 0
	STDMETHODIMP get_outerHTML(/*[out,retval]*/ BSTR *pVal)
	{
		return m_ownerDocument->saveXML(_variant_t((ILDOMNode*)static_cast<T*>(this)), pVal);
	}

	STDMETHODIMP put_outerHTML(/*[in]*/ BSTR newVal)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP get_innerHTML(/*[out,retval]*/ BSTR *pVal)
	{
		return get_markupContent(pVal);
	}

	STDMETHODIMP seut_innerHTML(/*[in]*/ BSTR newVal)
	{
		return set_markupContent(newVal);
	}

	STDMETHOD(get_innerText)(BSTR *pVal)
	{
		return get_textContent(pVal);
	}

	STDMETHOD(set_innerText)(BSTR newVal)
	{
		return set_textContent(newVal);
	}
#endif

	Object* get_onmousedown();
	void set_onmousedown(Object* listener);

	Object* get_onmouseup();
	void set_onmouseup(Object* listener);

	Object* get_onmousemove();
	void set_onmousemove(Object* listener);

// event handler DOM attributes
	/*
           attribute EventListener onabort;
           attribute EventListener onbeforeunload;
           attribute EventListener onblur;
           attribute EventListener onchange;
           attribute EventListener onclick;
           attribute EventListener oncontextmenu;
           attribute EventListener ondblclick;
           attribute EventListener ondrag;
           attribute EventListener ondragend;
           attribute EventListener ondragenter;
           attribute EventListener ondragleave;
           attribute EventListener ondragover;
           attribute EventListener ondragstart;
           attribute EventListener ondrop;
           attribute EventListener onerror;
           attribute EventListener onfocus;
           attribute EventListener onhashchange;
           attribute EventListener onkeydown;
           attribute EventListener onkeypress;
           attribute EventListener onkeyup;
           attribute EventListener onload;
           attribute EventListener onmessage;
           attribute EventListener onmousedown;
           attribute EventListener onmousemove;
           attribute EventListener onmouseout;
           attribute EventListener onmouseover;
           attribute EventListener onmouseup;
           attribute EventListener onmousewheel;
           attribute EventListener onresize;
           attribute EventListener onscroll;
           attribute EventListener onselect;
           attribute EventListener onstorage;
           attribute EventListener onsubmit;
           attribute EventListener onunload;
			  */
protected:

	Object* m_onmousedown;
	Object* m_onmouseup;
	Object* m_onmousemove;

	Attr* m_classAttr;
};

}	// Web
}

#endif // Web_HTMLElement_h
