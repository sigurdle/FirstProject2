#ifndef Web_ElementCSSInlineStyleI_h
#define Web_ElementCSSInlineStyleI_h

//#include "CSSStyleDeclaration.h"

namespace System
{
namespace Web
{

template<class T> class ElementCSSInlineStyleImpl :
//	public IBase,//ILElementCSSInlineStyle,
//	public ElementCSSInlineStyleImplImpl,
	public ICSSStyleDeclarationListener
{
public:

	CTOR ElementCSSInlineStyleImpl()
	{
	//	m_declaration = NULL;
	}

	/*
	int FinalConstruct()
	{
		HRESULT hr;

		hr = CComObject<CSSStyleDeclaration>::CreateInstance(&m_declaration);
		if (FAILED(hr)) return hr;
		m_declaration->AddRef();
		m_declaration->m_pListener = this;

		return 0;
	}

	void FinalRelease()
	{
		if (m_declaration)
		{
			m_declaration->m_pListener = NULL;
			m_declaration->Release();
			m_declaration = NULL;
		}
	}
	*/

	//CSSStyleDeclaration* m_declaration;

	CSSStyleDeclaration* get_style() const
	{
		return static_cast<const T*>(this)->m_styleDeclaration;
	}

	void OnStyleDeclChanged(CSSStyleDeclaration* pStyleDecl)
	{
		ASSERT(0);
#if 0
		if (static_cast<T*>(this)->m_bSetStyleAttribute == 0)
		{
			static_cast<T*>(this)->m_bSetStyleAttribute++;

			CComBSTR cssText;
			m_declaration->get_cssText(&cssText);

			((ILDOMElement*)static_cast<T*>(this))->setAttribute(L"style", cssText);

			static_cast<T*>(this)->m_bSetStyleAttribute--;
		}
#endif
	}
};

}	// Web
}

#endif // Web_ElementCSSInlineStyleI_h
