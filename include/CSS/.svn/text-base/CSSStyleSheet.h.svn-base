#ifndef Web_CSSStyleSheet_h
#define Web_CSSStyleSheet_h

namespace System
{
namespace Web
{

class CSSRule;
class CSSRuleList;
class CSSStyleSheet;

interface ICSSStyleSheetListener
{
	virtual void OnStyleSheetChanged(CSSStyleSheet* pSheet) = 0;
};

class XMLEXT CSSStyleSheet : 
	public StyleSheet,
	protected ICSSRuleListener,
	protected CNotifySendImpl<CSSStyleSheet>
{
public:
	CTOR CSSStyleSheet(Web::Node* ownerNode, CSSRule* ownerRule);
	~CSSStyleSheet();

	Web::IDOMErrorHandler* m_errorHandler;

	ICSSStyleSheetListener* m_pListener;
	vector<ICSSStyleSheetHandler*> m_handlers;

	void UpdateCSSText();
	void ParseCSSText();

	void RemoveAll();

	Web::IDOMLocator* getCurrentLocation();

	virtual void OnRuleChanged(CSSRule* pRule);

#if 0
// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
	{
		m_bCSSTextUpdated = FALSE;
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}
#endif

	CSSRule* get_ownerRule() const;
	CSSRuleList* get_cssRules();
	unsigned int insertRule(StringIn rule, unsigned int index);
	void deleteRule(unsigned int index);

// Extensions
	CSSSelectorList* createSelectorList();

// StyleSheet
	void set_cssText(StringIn newVal);
	String get_cssText();

	String get_type() const;

	void set_disabled(bool newVal);

	IDOMErrorHandler* get_errorHandler()
	{
		return m_errorHandler;
	}
	void set_errorHandler(Web::IDOMErrorHandler* newVal)
	{
		m_errorHandler = newVal;
	}

//	STDMETHOD(set_href)(BSTR newVal);	// Is this the way to load a stylesheet ??

// Extensions
	void addHandler(/*[in]*/ ICSSStyleSheetHandler *handler)
	{
		ASSERT(handler != NULL);
		if (handler == NULL) THROW(-1);
		m_handlers.Add(handler);
	}
	void removeHandler(/*[in]*/ ICSSStyleSheetHandler *handler)
	{
		for (unsigned int i = 0; i < m_handlers.GetSize(); i++)
		{
			if (m_handlers[i] == handler)
			{
				ASSERT(0);
				//m_handlers.RemoveAt(i);
				return;
			}
		}

		ASSERT(0);
		throw -1;
	}

	bool load(StringIn url);
	bool load(System::IO::ISequentialByteStream* stream);

public:

	CSSRuleList* m_cssRules;

protected:

	String m_cssText;
	CSSRule* m_ownerRule;
	bool m_bCSSTextUpdated;
};

}	// Web
}

#endif // Web_CSSStyleSheet_h
