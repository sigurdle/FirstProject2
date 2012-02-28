#include "stdafx.h"
#include "LXML2.h"

//#include "../LXUI/http.h"

//#include "CSSStyleSheet.h"

/*
#include "CSSRuleList.h"

#include "CSSMediaRule.h"
#include "CSSImportRule.h"
#include "CSSCharsetRule.h"
#include "CSSFontFaceRule.h"
#include "SVGColorProfileRule.h"
#include "CSSUnknownRule.h"
#include "CSSCommentRule.h"

#include "CSSStream.h"

#include "../LXUI/Binder.h"
*/

namespace System
{
namespace Web
{

#if 0
#include "LDOMLocator.h"
#endif

	ErrorCode CreateDOMError(long offset, StringIn msg, IDOMError* *pError);

Style::IStyleDeclaration* CSSStyleSheet::CreateDeclaration()
{
	ASSERT(0);
	return NULL;
}

void CSSStyleSheet::AddRules(Style::SelectorList* selectors, Style::IStyleDeclaration* declarator)
{
	ASSERT(0);
}

size_t CSSStyleSheet::GetRuleCount()
{
	ASSERT(0);
	return 0;
}

Style::ICSSRule* CSSStyleSheet::GetRule(size_t index)
{
	ASSERT(0);
	return NULL;
}

void CSSStyleSheet::set_cssText(StringIn str)
{
	ASSERT(0);
}

/////////////////////////////////////////////////////////////////////////////
//
#if 0
ErrorCode /*CSSStyleSheet::*/ParseRule(CSSStream& stream, CSSStyleSheet* parentStyleSheet, CSSRule* parentRule, ICSSRuleListener* pListener, CSSRule* *pVal)
{
	*pVal = NULL;

//	stream->SkipSpaces();

	stream.getnextc();

	if (stream.m_c == L'/')
	{
		stream.getnextc();
		//if (c == L'*')
		stream.EatChar(L'*');
		{
			CSSCommentRule* p = new CSSCommentRule;
			//p->AddRef();

			p->m_textOffset[0] = stream.m_ipos-2;
			p->m_textOffset[1] = stream.m_ipos-2;
			p->m_textOffset[2] = stream.m_ipos;

			p->m_parentStyleSheet = parentStyleSheet;
			p->m_parentRule = parentRule;

			StringStream cssText;
			cssText << L"/*";

			while (!stream.eof())
			{
				if (stream.m_c == L'*')
				{
					stream.getnextc();
					if (stream.m_c == L'/')
					{
						stream.getnextc();
						break;
					}
				}

				cssText << (WCHAR)stream.m_c;
			}

			p->m_textOffset[3] = stream.m_ipos;

			stream.EatChar(L'*');
			stream.EatChar(L'/');

			p->m_textOffset[4] = stream.m_ipos;
			p->m_textOffset[5] = stream.m_ipos;

			cssText << L"*/";

			p->m_cssText = cssText->str();

			*pVal = p;
		}
	}
	else if (stream.m_c == L'@')	// at-rule
	{
		String id = stream.GetID();

		StringStream strbuilder;

		strbuilder << L"@";
		strbuilder << id;

		int curly = 0;

		while (!stream.eof())
		{
			strbuilder << (WCHAR)stream.m_c;

			if (stream.m_c == L'{')
			{
				curly++;
			}
			else if (stream.m_c == L'}')
			{
				curly--;
				if (curly == 0)
					break;
			}
			else if (stream.m_c == L';')
			{
				if (curly == 0)
				{
					break;
				}
			}
		}

		// Read spaces
		while (!stream.eof())
		{
			if (!isspace(stream.m_c))
			{
				break;
			}
			strbuilder << (WCHAR)stream.m_c;
			stream.getnextc();
		}

		String cssText = strbuilder->str();

		if (id == L"charset")
		{
			CSSCharsetRule* p = new CSSCharsetRule;
			if (p)
			{
			//	p->AddRef();
				p->m_parentStyleSheet = parentStyleSheet;
				p->m_parentRule = parentRule;

				p->set_cssText(cssText);

				*pVal = p;
			}
		}
		else if (id == L"import")
		{
			CSSImportRule* p = new CSSImportRule;
			if (p)
			{
			//	p->AddRef();
				p->m_parentStyleSheet = parentStyleSheet;
				p->m_parentRule = parentRule;

				p->set_cssText(cssText);

				*pVal = p;
			}
		}
		else if (id == L"fontface")
		{
			CSSFontFaceRule* p = new CSSFontFaceRule;
			if (p)
			{
			//	p->AddRef();
				p->m_parentStyleSheet = parentStyleSheet;
				p->m_parentRule = parentRule;

				p->set_cssText(cssText);

				*pVal = p;
			}
		}
		else if (id == L"media")
		{
			CSSMediaRule* p = new CSSMediaRule;
			if (p)
			{
				//p->AddRef();
				p->m_parentStyleSheet = parentStyleSheet;
				p->m_parentRule = parentRule;

				p->set_cssText(cssText);

				*pVal = p;
			}
		}
		else if (id == L"color-profile")
		{
			SVGColorProfileRule* p = new SVGColorProfileRule;
			if (p)
			{
//				p->AddRef();
				p->m_parentStyleSheet = parentStyleSheet;
				p->m_parentRule = parentRule;

				p->set_cssText(cssText);

				*pVal = p;
			}
		}
		/*
		else if (!tcscmp(id, L"charset"))
		{
		}
		*/
		else // Unknown at-rule
		{
			CSSUnknownRule* p = new CSSUnknownRule;
			if (p)
			{
				//p->AddRef();
				p->m_parentStyleSheet = parentStyleSheet;
				p->m_parentRule = parentRule;
				p->set_cssText(cssText);

				*pVal = p;
			}
		}
	}
	else
	{
		CSSStyleRule* p = new CSSStyleRule;
		if (p)
		{
			//p->AddRef();

			p->m_textOffset[0] = stream.m_ipos;

			p->m_parentStyleSheet = parentStyleSheet;
			p->m_parentRule = parentRule;

			StringStream cssText;

		// Skip selectors
			while (!stream.eof())
			{
				cssText << (WCHAR)stream.m_c;

				if (stream.m_c == L'{')
				{
					break;
				}

				stream.getnextc();
			}

			p->m_textOffset[1] = stream.m_ipos;

		// Skip style declaration
			stream.EatChar(L'{');
			int curly = 1;

			p->m_textOffset[2] = stream.m_ipos;

			while (!stream.eof())
			{
				cssText << (WCHAR)stream.m_c;

				p->m_textOffset[3] = stream.m_ipos;

				if (stream.m_c == '"')
				{
					stream.getnextc();

					//if (delimiter == L'\'' || L'\"')
					{
						while (!stream.eof())
						{
							cssText << (WCHAR)stream.m_c;

							if (stream.m_c == '\\')
							{
								stream.getnextc();
								cssText << (WCHAR)stream.m_c;
							}
							else if (stream.m_c == '"')
							{
								break;
							}
						}
					}
				}
				else if (stream.m_c == L'{')
				{
					curly++;
				}
				else if (stream.m_c == L'}')
				{
					curly--;
					if (curly == 0)
					{
						break;
					}
				}
			}

			p->m_textOffset[4] = stream.m_ipos;

			// Read spaces
			while (!stream.eof())
			{
				if (!isspace(stream.m_c))
				{
					break;
				}
				cssText << (WCHAR)stream.m_c;
				stream.getnextc();
			}

			p->m_textOffset[5] = stream.m_ipos;

			p->set_cssText(cssText->str());
			p->m_pListener = pListener;

			*pVal = p;
		}
	}
	return Success;
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CSSStyleSheet

CSSStyleSheet::CSSStyleSheet(Node* ownerNode, Style::CSSRule* ownerRule) :
	StyleSheet(ownerNode),
	m_ownerRule(ownerRule)
{
//	m_errorHandler = NULL;
	m_pListener = nullptr;

//	m_cssRules = new CSSRuleList;
}

#if 0
CSSStyleSheet::~CSSStyleSheet()
{
	ASSERT(m_pListener == NULL);
	ASSERT(m_handlers.size() == 0);
	delete m_cssRules;
}

void CSSStyleSheet::RemoveAll()
{
	for (int i = m_cssRules->m_rules.size()-1; i >= 0; i--)
	{
		deleteRule(i);
		/*
		CComQIPtr<ILCSSStyleRule> styleRule = m_cssRules->m_rules[i];
		if (styleRule)
		{
			static_cast<CSSStyleRule*>(styleRule.p)->m_pListener = NULL;
		}

		m_cssRules->m_rules[i]->Release();
		*/
	}
	//m_cssRules->m_rules.RemoveAll();
}
#endif

String CSSStyleSheet::get_type() const
{
	static ImmutableString<WCHAR> type(L"text/css");
	return &type;
}

#if 0
void CSSStyleSheet::ParseCSSText()
{
	TRY
	{
		CSSStream stream(m_cssText);
		stream.getnextc();

		stream.SkipSpaces();

		while (!stream.eof())
		{
			CSSRule* rule;
			ParseRule(stream, this, NULL, this, &rule);
			if (rule)
			{
				m_cssRules->m_rules.Add(rule);

				// Call handlers After it is inserted
				for (int i = 0; i < m_handlers.size(); i++)
				{
					ASSERT(0);
					//m_handlers[i]->handleCSSEvent(LCSSObject_Rule, LCSSEvent_Insert, this, rule);
				}

			//	rule.Detach();
			}

			stream.SkipSpaces();
		}
	}
	CATCH (Exception* e)
	{
		//TRACE("ERROR Parsing Stylesheet: %S\n", p);
		TRACE("ERROR Parsing Stylesheet\n");
		//MessageBox(NULL, _bstr_t(p), "CSS", MB_OK);

		// TODO, the errorhandler should already have been called
#if 0
		WCHAR msg[512];
		swprintf(msg, L"CSS: %s", p);

		if (m_ownerNode)
		{
			CComPtr<ILDOMDocument> ownerDocument;
			m_ownerNode->get_ownerDocument(&ownerDocument);
			if (ownerDocument)
			{
				long offset;
				m_ownerNode->getTextOffset(5, &offset);

				offset += stream->m_ipos;

				CComPtr<ILDOMError> error;
				CreateDOMError(LSEVERITY_ERROR, offset, msg, &error);

				ILDOMErrorHandler* errorHandler;
				ownerDocument->get_errorHandler(&errorHandler);

				if (errorHandler)
				{
					bool bContinue;
					errorHandler->handleError(error, &bContinue);
					if (!bContinue)
					{
					}
				}
			}
		}
#endif
	}

//	delete stream;
}

void CSSStyleSheet::UpdateCSSText()
{
	m_cssText = L"";

	for (int i = 0; i < m_cssRules->m_rules.size(); i++)
	{
		String str = m_cssRules->m_rules[i]->get_cssText();

		m_cssText += str;
		m_cssText += "\n";
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CSSStyleSheet

Style::CSSRule* CSSStyleSheet::get_ownerRule()
{
	return m_ownerRule;
}

#if 0
void CSSStyleSheet::set_cssText(StringIn newVal)
{
	m_cssText = newVal;

	RemoveAll();

	ParseCSSText();
	m_bCSSTextUpdated = true;

// hmm... ??
	if (m_pListener)
	{
		m_pListener->OnStyleSheetChanged(this);
	}

	/*
	for (int i = 0; i < m_handlers.GetSize(); i++)
	{
		m_handlers[i]->handleCSSEvent(this, 0);
	}
	*/
}
#endif

String CSSStyleSheet::get_cssText()
{
	ASSERT(0);
#if 0
	if (!m_bCSSTextUpdated)
	{
		UpdateCSSText();
		m_bCSSTextUpdated = true;
	}
#endif

	return m_cssText;
}

#if 0
CSSRuleList* CSSStyleSheet::get_cssRules()
{
	return m_cssRules;
}

unsigned int CSSStyleSheet::insertRule(StringIn rule, unsigned int index)
{
	ASSERT(rule != NULL);
	if (rule == NULL)
	{
		ASSERT(0);
		throw -1;
	}

	CSSStream stream(rule);

	CSSRule* cssrule;
	ParseRule(stream, this, NULL, this, &cssrule);

	if (cssrule)
	{
		ASSERT(0);
#if 0
		m_cssRules->m_rules.InsertAt(index, cssrule);

		if (m_pListener)
		{
			m_pListener->OnStyleSheetChanged(this);
		}

	// Call handlers After it is inserted
		for (int i = 0; i < m_handlers.size(); i++)
		{
			ASSERT(0);
		//	m_handlers[i]->handleCSSEvent(LCSSObject_Rule, LCSSEvent_Insert, this, m_cssRules->m_rules[index]);
		}

		/*
		if (pVal)
		{
			*pVal = index;
		}
		*/
#endif
	}

	return index;
}

void CSSStyleSheet::deleteRule(unsigned int index)
{
	ASSERT(0);
#if 0
	if (index >= 0 && index < m_cssRules->m_rules.size())
	{
	// Call handlers Before it is removed
		for (int i = 0; i < m_handlers.size(); i++)
		{
			ASSERT(0);
			//m_handlers[i]->handleCSSEvent(LCSSObject_Rule, LCSSEvent_Remove, this, m_cssRules->m_rules[index]);
		}

		ILCSSStyleRule* styleRule = dynamic_cast<ILCSSStyleRule*>(m_cssRules->m_rules[index]);
		if (styleRule)
		{
			static_cast<CSSStyleRule*>(styleRule)->m_pListener = NULL;
		}

//		m_cssRules->m_rules[index]->Release();
		m_cssRules->m_rules.RemoveAt(index);

		m_bCSSTextUpdated = FALSE;

		if (m_pListener)
		{
			m_pListener->OnStyleSheetChanged(this);
		}
	}
#endif
}
#endif

void CSSStyleSheet::set_disabled(bool newVal)
{
	m_disabled = newVal;
// TODO
}

#if 0
//virtual
void CSSStyleSheet::OnRuleChanged(CSSRule* pRule)
{
	m_bCSSTextUpdated = false;

	if (m_pListener)
	{
		m_pListener->OnStyleSheetChanged(this);
	}

#if 0
	for (int i = 0; i < m_handlers.GetSize(); i++)
	{
		m_handlers[i]->handleCSSEvent(this, 0);
	}
#endif
}

//////////////////////////////////////////////////
// Extensions

CSSSelectorList* CSSStyleSheet::createSelectorList()
{
	CSSSelectorList* p = new CSSSelectorList;
	if (p)
	{
		ASSERT(0);
		//*pVal = p;
//		(*pVal)->AddRef();
	}

	return p;
}

/*
class StylesheetLoaderCallback : public IBindCallback
{
public:

	HANDLE m_hDoneEvent;

	virtual ErrorCode OnObjectAvailable(Object* object, const sysstring& url)
	{
		return S_OK;
	}

	virtual ErrorCode OnDataAvailable(ULONG cbSize, ISequentialByteStream* stream)
	{
		return S_OK;
	}

	virtual ErrorCode OnDone()
	{
#if WIN32
		SetEvent(m_hDoneEvent);
#else
		ASSERT(0);
#endif

		return S_OK;
	}
};
*/

bool CSSStyleSheet::load(StringIn url)
{
	m_href = url;

	//StylesheetLoaderCallback* pCallback = new StylesheetLoaderCallback;

	//pCallback->m_hDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	UrlBinding binder;// = new UrlBinding;
	System::IO::ISequentialByteStream* stream = binder.BindToObject(m_href, NULL/*pCallback*/);

//	WaitForSingleObject(pCallback->m_hDoneEvent, INFINITE);

	load(stream);

	return true;
}

bool CSSStyleSheet::load(System::IO::ISequentialByteStream* stream)
{
	String textData;// = new OLECHAR[len];

	ULONG nRead;
	uint8 buffer[512];
	//int len = 0;
	do
	{
		nRead = stream->Read(buffer, 512);
		for (int i = 0; i < nRead; i++)
		{
			textData += (WCHAR)buffer[i];
		//	TRACE("%c", buffer[i]);
		}
		//len += nRead;
	}
	while (nRead == 512);

	/*
	//m_textLen = len;
	for (int i = 0; i < len; i++)
	{
		textData += buffer[i];
	}

	delete [] buffer;
	*/

	set_cssText(textData);

	return true;
}

#if 0
STDMETHODIMP CSSStyleSheet::ParseFromTextData(ITextData *pTextData)
{
	/*
#ifdef _DEBUG
		pTextData->save(L"C:\\last_loaded.css");
#endif
		*/

	pTextData->get_url(&m_href);

	BSTR text;
	pTextData->get_data(&text);

	return set_cssText(text);
}
#endif

IDOMLocator* CSSStyleSheet::getCurrentLocation()
{
	ASSERT(0);
	return NULL;
#if 0
	CComObject<CLDOMLocator>* locator;
	CComObject<CLDOMLocator>::CreateInstance(&locator);
	if (locator)
	{
#if 0
		locator->m_offset = m_fpos;
		locator->m_lineNumber = m_line;
		locator->m_columnNumber = m_column;
#endif
		locator->m_uri = m_href;
	}

	return locator;	// This AddRefs
#endif
}

// IPersistMoniker

#if 0
STDMETHODIMP CSSStyleSheet::GetClassID(CLSID __RPC_FAR *pClassID)
{
	return E_NOTIMPL;
}

STDMETHODIMP CSSStyleSheet::IsDirty()
{
	return E_NOTIMPL;
}

STDMETHODIMP CSSStyleSheet::Load(/* [in] */ BOOL fFullyAvailable, /* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc, /* [in] */ DWORD grfMode)
{
	m_curMoniker = pimkName;

//	CComPtr<IStream> stm;
//	pimkName->BindToStorage(pibc, NULL, IID_IStream, (void**)&stm);

	ITextData* textData;
	//textData.CoCreateInstance(CLSID_TextData);

	ASSERT(0);
#if 0
	CComQIPtr<IPersistMoniker> persistMoniker = m_textData;
	persistMoniker->Load(fFullyAvailable, pimkName, pibc, grfMode);

	BSTR text;
	pTextData->get_data(&text);

	LPOLESTR displayName;
	m_curMoniker->GetDisplayName(pibc, NULL, &displayName);
	m_href = displayName;
	CoTaskMemFree(displayName);
#endif
	return set_cssText(text);
}

STDMETHODIMP CSSStyleSheet::Save(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pbc, /* [in] */ BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CSSStyleSheet::SaveCompleted(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc)
{
	return E_NOTIMPL;
}

STDMETHODIMP CSSStyleSheet::GetCurMoniker(/* [out] */ IMoniker **ppimkName)
{
	if (ppimkName == NULL) return E_POINTER;
	*ppimkName = m_curMoniker;
	if (*ppimkName) (*ppimkName)->AddRef();
	return S_OK;
}
#endif

#endif

}	// Web
}
