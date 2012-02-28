#ifndef Web_LinkStyleImpl_h
#define Web_LinkStyleImpl_h

//#include "CSSStyleSheet.h"

namespace System
{
namespace Web
{

class WEBEXT LinkStyleExternalImpl :
	public ILinkStyle/*,
	protected ICSSStyleSheetListener*/
{
public:

	CTOR LinkStyleExternalImpl()
	{
		m_styleSheet = NULL;
		m_cssreentrancy = 0;
	}

	~LinkStyleExternalImpl()
	{
		if (m_styleSheet)
		{
		// TODO, remove stylesheet from document stylesheets list?
			m_styleSheet->m_pListener = NULL;
			m_styleSheet->m_ownerNode = NULL;
			m_styleSheet = NULL;
		}
	}

	CSSStyleSheet* m_styleSheet;

	int m_cssreentrancy;

	virtual void OnStyleSheetChanged(CSSStyleSheet* pSheet)
	{
		if (m_cssreentrancy == 0)
		{
			m_cssreentrancy++;

			String cssText = m_styleSheet->get_cssText();

			ASSERT(0);
#if 0
			static_cast<T*>(this)->set_textContent(cssText);
#endif

			m_cssreentrancy--;
		}
	}

// ILinkStyle
	CSSStyleSheet* get_sheet()
	{
		return m_styleSheet;
	}
};

class WEBEXT LinkStyleStyleImpl :
	public Web::ILinkStyle/*,
	protected ICSSStyleSheetListener*/
{
public:

	CTOR LinkStyleStyleImpl(Web::Node* ownerNode)
	{
		m_styleSheet = new CSSStyleSheet(ownerNode, NULL/*ownerRule*/);
		m_cssreentrancy = 0;
	}

	/*
	int FinalConstruct()
	{
		ErrorCode hr;

		hr = CComObject<CSSStyleSheet>::CreateInstance(&m_styleSheet);
		if (FAILED(hr)) return hr;
		m_styleSheet->AddRef();
		m_styleSheet->m_ownerNode = static_cast<T*>(this);
		m_styleSheet->m_pListener = this;

		return 0;
	}

	void FinalRelease()
	{
		if (m_styleSheet)
		{
		// TODO, remove stylesheet from document stylesheets list?
			m_styleSheet->m_pListener = NULL;
			m_styleSheet->m_ownerNode = NULL;
			m_styleSheet->Release();
			m_styleSheet = NULL;
		}
	}
	*/

	CSSStyleSheet* m_styleSheet;

	int m_cssreentrancy;

	virtual void OnStyleSheetChanged(CSSStyleSheet* pSheet)
	{
		if (m_cssreentrancy == 0)
		{
			m_cssreentrancy++;

			String cssText = m_styleSheet->get_cssText();

			ASSERT(0);
#if 0
			static_cast<T*>(this)->set_textContent(cssText);
#endif
			m_cssreentrancy--;
		}
	}

#if 0
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
#if 0
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
					StringW cssText = m_styleSheet->get_cssText();

					chardata->set_data(cssText);
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
#endif

		return Success;
	}
#endif

// ILinkStyle
	CSSStyleSheet* get_sheet()
	{
		return m_styleSheet;
	}
};

}	// Web
}

#endif	// Web_LinkStyleImpl_h
