#ifndef Web_CSSRule_h
#define Web_CSSRule_h

namespace System
{
namespace Web
{

interface ICSSRuleListener
{
	virtual void OnRuleChanged(CSSRule* pRule) = 0;
};

class CSSEXT CSSRule : public Object, public ICSSRule
{
public:
	CTOR CSSRule()
	{
		m_parentStyleSheet = NULL;
		m_parentRule = NULL;

		m_textOffset[0] = -1;
		m_textOffset[1] = -1;
		m_textOffset[2] = -1;
		m_textOffset[3] = -1;
		m_textOffset[4] = -1;
		m_textOffset[5] = -1;

		m_pListener = NULL;
	}

	~CSSRule()
	{
		ASSERT(m_pListener == NULL);
		ASSERT(m_userdataList.GetSize() == 0);	// May be legal strictly speaking, woun't affect release build

		for (unsigned int i = 0; i < m_userdataList.GetSize(); i++)
		{
			delete m_userdataList[i];
		}
		m_userdataList.RemoveAll();
	}

	class CUserData
	{
	public:
		String m_key;
		Object* m_data;
	};

	virtual CSSType get_type() const;
	virtual CSSRule* get_parentRule();
	virtual CSSStyleSheet* get_parentStyleSheet();
	virtual String get_cssText();
	virtual void set_cssText(StringIn newVal);

	virtual void set_parentRule(CSSRule* newVal);
	virtual void set_parentStyleSheet(CSSStyleSheet* newVal);

public:

	long m_textOffset[6];

	vector<CUserData*> m_userdataList;

	ICSSRuleListener* m_pListener;

	String m_cssText;
	CSSStyleSheet* m_parentStyleSheet;
	CSSRule* m_parentRule;
};

}	// Web
}

#if 0
template <class IBase> class LXUIEXT CSSRule :
	public CSSRuleImplImpl,
	public IBase
{
public:
	STDMETHOD(get_type)(/*[out, retval]*/ LCSSType *pVal)
	{
		return CSSRuleImplImpl::get_type(pVal);
	}
	STDMETHOD(get_parentRule)(/*[out, retval]*/ ILCSSRule* *pVal)
	{
		return CSSRuleImplImpl::get_parentRule(pVal);
	}
	STDMETHOD(get_parentStyleSheet)(/*[out, retval]*/ ILCSSStyleSheet* *pVal)
	{
		return CSSRuleImplImpl::get_parentStyleSheet(pVal);
	}
	STDMETHOD(get_cssText)(/*[out, retval]*/ BSTR *pVal)
	{
		return CSSRuleImplImpl::get_cssText(pVal);
	}
	STDMETHOD(set_cssText)(/*[in]*/ BSTR newVal)
	{
		return CSSRuleImplImpl::set_cssText(newVal);
	}
	STDMETHOD(getTextOffset)(/*[in]*/ long index, /*[out,retval]*/ long* pVal)
	{
		*pVal = m_textOffset[index];
		return S_OK;
	}
	STDMETHOD(setTextOffset)(/*[in]*/ long index, /*[in]*/ long offset)
	{
		m_textOffset[index] = offset;
		return S_OK;
	}
	STDMETHOD(setUserData)(const StringW& key, /*[in]*/ Object* data, /*[out,retval]*/ Object* *pVal)
	{
		ASSERT(key != NULL);
		if (key == NULL) return E_INVALIDARG;

		for (int i = 0; i < m_userdataList.GetSize(); i++)
		{
			if (!wcscmp(m_userdataList[i]->m_key, key))
			{
				if (pVal)
				{
					*pVal = m_userdataList[i]->m_data;
			//		(*pVal)->AddRef();
				}

				if (data)
				{
					m_userdataList[i]->m_data = data;
				}
				else
				{
					delete m_userdataList[i];
					m_userdataList.RemoveAt(i);
				}
			}
		}

		if (data)
		{
			CUserData* pUserData = new CUserData;
			pUserData->m_key = key;
			pUserData->m_data = data;

			m_userdataList.Add(pUserData);
		}

		if (pVal)
			*pVal = NULL;

		return S_OK;
	}
	STDMETHOD(getUserData)(const StringW& key, /*[out,retval]*/ Object* *pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) THROW(-1);

		for (int i = 0; i < m_userdataList.GetSize(); i++)
		{
			if (!wcscmp(m_userdataList[i]->m_key, key))
			{
				*pVal = m_userdataList[i]->m_data;
//				(*pVal)->AddRef();
				return S_OK;
			}
		}

		*pVal = NULL;
		return S_OK;
	}
};

#endif

#endif	// Web_CSSRule_h
