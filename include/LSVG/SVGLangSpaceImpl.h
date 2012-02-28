#ifndef __SVGLangSpaceImpl_h__
#define __SVGLangSpaceImpl_h__

namespace System
{
namespace Web
{

template <class T> class SVGLangSpaceImpl :
	public ISVGLangSpace
{
public:
// lang
	String get_xmllang()
	{
		ASSERT(0);
		return NULL;
;//		return ((ILDOMElement*)static_cast<T*>(this))->getAttributeNS(L"http://www.w3.org/XML/1998/namespace", L"lang", pVal);
	}

	void set_xmllang(StringIn newVal)
	{
		ASSERT(0);
		//return ((ILDOMElement*)static_cast<T*>(this))->setAttributeNS(L"http://www.w3.org/XML/1998/namespace", L"lang", newVal);
	}

// space
	String get_xmlspace()
	{
		ASSERT(0);
		return NULL;
		//return ((ILDOMElement*)static_cast<T*>(this))->getAttributeNS(L"http://www.w3.org/XML/1998/namespace", L"space", pVal);
	}

	void set_xmlspace(StringIn newVal)
	{
		ASSERT(0);
		//return ((ILDOMElement*)static_cast<T*>(this))->setAttributeNS(L"http://www.w3.org/XML/1998/namespace", L"space", newVal);
	}
};

}	// w3c
}

#endif // __SVGLangSpaceImpl_h__
