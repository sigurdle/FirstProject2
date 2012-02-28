// CSS.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CSS.h"

#pragma comment(lib, "LFC")

namespace System
{
namespace Style
{

CSSStream::CSSStream(IO::TextReader* stream) : m_data(stream)
{
}

CSSStream::CSSStream(StringIn str) : m_data(new IO::StringReader(str))
{
}

void CSSStream::GetNSName(String& prefix, String& name)
{
	String temp;

	while (!eof())
	{
		if (m_c == L'\\') // escaped symbol
		{
			getnextc();	// next character is real character

			if (!(isalnum(m_c) || (m_c == ':') || (m_c == '.') || (m_c == '-')))
			{
				break;
			}
		}

		if (m_c == L'|')
		{
			prefix = temp;
			temp = nullptr;
		}
		else
		{
			if (!(isalnum(m_c) || (m_c == '-')))
			{
				break;
			}

			temp += (WCHAR)m_c;
		}

		getnextc();
	}

	name = temp;

	if (name.GetLength() == 0)
		THROW(WSTR("Expected an identifer"));
}

SimpleSelector* CSSStream::ParseSingleSelector()
{
	if (isalpha(m_c))
	{
		CSimpleSelectorType* pSimpleSelector = new CSimpleSelectorType;

		String prefix;
		GetNSName(prefix, pSimpleSelector->m_name);	// element Type

		return pSimpleSelector;
	}
	else if (m_c == '*')	// universal
	{
		CSimpleSelectorUniversal* pSimpleSelector = new CSimpleSelectorUniversal;
		return pSimpleSelector;
	}
	else if (m_c == '.')	// class
	{
		CSimpleSelectorClass* pSimpleSelector = new CSimpleSelectorClass;
		pSimpleSelector->m_className = GetID();
		return pSimpleSelector;
	}
	else if (m_c == '#')	// id
	{
		CSimpleSelectorID* pSimpleSelector = new CSimpleSelectorID;
		pSimpleSelector->m_id = GetID();
		return pSimpleSelector;
	}
	else if (m_c == L'[')
	{
		CSimpleSelectorAttribute* pSimpleSelector = NULL;

		pSimpleSelector = new CSimpleSelectorAttribute;

		pSimpleSelector->m_attrName = GetID();

		if (m_c == L']')
		{
			getnextc();
			pSimpleSelector->m_attrMatch = 0;
		}
		else
		{
			if (m_c == L'=')
			{
				getnextc();
				pSimpleSelector->m_attrMatch = L'=';
			}
			else if (m_c == L'~' || m_c == L'|' || m_c == '^' || m_c == L'$' || m_c == L'*')
			{
				getnextc();
				pSimpleSelector->m_attrMatch = m_c;
				EatChar(L'=');
			}
			else
			{
				raise(Exception(L"Expected attribute value"));
			}

			// Get attribute value
			if (m_c == L'\'' || m_c == L'\"')
			{
				getnextc();
				pSimpleSelector->m_attrValue = GetString();
			}
			else
			{
				pSimpleSelector->m_attrValue = GetID();
			}
		}

		EatChar(L']');

		return pSimpleSelector;
	}
	else if (m_c == L':')	// pseudo-class or pseudo-element
	{
		//WCHAR* ppos = m_ppos;

		getnextc();
		int colon = m_c;
		if (m_c == ':')
		{
			getnextc();
		}

		String ident = GetID();

		if (colon == L':' ||

		// pseudo-element that is allowed to have only one : (for backwards-compatibility)
			ident == L"first-line" ||
			ident == L"first-letter" ||
			ident == L"before" ||
			ident == L"after")
		{
		//	m_ppos = ppos;
			//CPseudoElement* pPseudoElt = new CPseudoElement;

		//	pSimpleSelectorSequence->m_ownerSelector->m_pseudoElement = ident;

			ASSERT(0);
			return NULL;
		//	break;	// A pseudo-element is the last thing allowed
		}
		else	// pseudo-class
		{
			CSimpleSelectorPseudoClass* pSimpleSelector = NULL;

			if (ident.Compare(L"link"))
			{
				pSimpleSelector = new CPseudoClassLink;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"visited"))
			{
				pSimpleSelector = new CPseudoClassVisited;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"hover"))
			{
				pSimpleSelector = new CPseudoClassHover;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"active"))
			{
				pSimpleSelector = new CPseudoClassActive;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"focus"))
			{
				pSimpleSelector = new CPseudoClassFocus;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"enabled"))
			{
				pSimpleSelector = new CPseudoClassEnabled;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"disabled"))
			{
				pSimpleSelector = new CPseudoClassDisabled;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
		//
			else	// should this else be here ?
				if (!ident.Compare(L"root"))
			{
			}
			else if (!ident.Compare(L"nth-child"))
			{
				pSimpleSelector = new CPseudoClassFirstChild;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"nth-last-child"))
			{
				pSimpleSelector = new CPseudoClassFirstChild;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"nth-of-type"))
			{
			}
			else if (!ident.Compare(L"nth-last-of-type"))
			{
			}
			else if (!ident.Compare(L"first-child"))
			{
				pSimpleSelector = new CPseudoClassFirstChild;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else if (!ident.Compare(L"last-child"))
			{
			}
			else if (!ident.Compare(L"first-of-type"))
			{
			}
			else if (!ident.Compare(L"last-of-type"))
			{
			}
			else if (!ident.Compare(L"only-child"))
			{
				/*
				pSimpleSelector = new CPseudoClassFirstChild;
				pSimpleSelector->m_pseudoClassName = ident;

				pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				*/
			}
			else if (!ident.Compare(L"only-of-type"))
			{
				/*
				pSimpleSelector = new CPseudoClassFirstChild;
				pSimpleSelector->m_pseudoClassName = ident;

				pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				*/
			}
			else if (!ident.Compare(L"empty"))
			{
				pSimpleSelector = new CPseudoClassEmpty;
				pSimpleSelector->m_pseudoClassName = ident;

				return pSimpleSelector;
			}
			else
			{
#if 0	// TODO
				pSimpleSelector = new CSimpleSelectorPseudoClass;

				try
				{
					pSimpleSelector->m_pseudoClassName = ident;

					int c = stream->getnextc();
					if (c == L'(')
					{
						if (c == L'\'' || c == L'\"')
						{
							/*pSimpleSelector->m_attrValue =*/ stream->GetString();
						}
						else
						{
							/*pSimpleSelector->m_attrValue =*/ stream->GetID();
						}

						stream->EatChar(L')');
					}
				}
				catch(WCHAR* msg)
				{
					delete pSimpleSelector;
					THROW(msg);
				}
#endif
			}

		//	pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
		}
	}

	return NULL;
}

SimpleSelectorSequence* CSSStream::ParseSingleSelectorSequence()
{
	SimpleSelectorSequence* pSimpleSelectorSequence = new SimpleSelectorSequence;
/*
	A sequence of simple selectors is a chain of simple selectors that are not
	separated by a combinator. It always begins with a type selector or a
	universal selector. No other type selector or universal selector is allowed in the sequence. 
*/

	if (isalpha(m_c))
	{
		SimpleSelector* pSimpleSelector = ParseSingleSelector();
		pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
	}
	else
	{
		if (m_c == L'*')	// Universal selector
		{
			getnextc();
		}
		//else ; // Implied

		CSimpleSelectorUniversal* pSimpleSelector = new CSimpleSelectorUniversal;
		pSimpleSelectorSequence->m_items.push_back(pSimpleSelector);
	}

	while (m_c == '.' || m_c == '#' || m_c == '[' || m_c == ':')
	{
		SimpleSelector* simpleSelector = ParseSingleSelector();

		pSimpleSelectorSequence->m_items.push_back(simpleSelector);
	}

	return pSimpleSelectorSequence;
}

Selector* CSSStream::ParseSelector()
{
	Selector* pSelector = new Selector;

//	SimpleSelectorSequence* pSingleSelectorSequence = new SimpleSelectorSequence;

	SimpleSelectorSequence* pPrev = nullptr;

	while ((isalpha(m_c) ||
			m_c == L'*' ||
			m_c == '.' ||
			m_c == '#' ||
			m_c == '[' ||
			m_c == ':'))
	{
		SimpleSelectorSequence* pSingleSelectorSequence;
		pSingleSelectorSequence = ParseSingleSelectorSequence();
		pSingleSelectorSequence->m_ownerSelector = pSelector;
		pSingleSelectorSequence->m_pLeft = pPrev;
		pPrev = pSingleSelectorSequence;

		//pSelector->m_simpleSelectorSequences.Add(pSingleSelectorSequence);

		SkipSpacesComments();

		if (!eof())
		{
			if (m_c == L'>' || m_c == L'*' || m_c == L'+' || m_c == L'~')
			{
				pSingleSelectorSequence->m_combinator = m_c;
				getnextc();
			}
			else
			{
				pSingleSelectorSequence->m_combinator = L' ';
			}

			SkipSpacesComments();

			/*
			c = stream->getnextc();
			stream->ungetnextc();

			if (c == L',')	// End of this selector, start of new one
			{
				break;
			}
			*/

			/*
			if (!eof())
			{
				SimpleSelectorSequence* pRight = new SimpleSelectorSequence;
				pRight->m_pLeft = pSingleSelectorSequence;
				pSingleSelectorSequence = pRight;
				pSingleSelectorSequence->m_ownerSelector = this;
			}
			*/
		}
	}

	if (pPrev == nullptr)
	{
		ASSERT(0);
		raise(Exception(L"No selector"));
	}

	pSelector->m_pRight = pPrev;

	pSelector->CalculateSpecificity();

	return pSelector;
}

SelectorList* CSSStream::ParseSelectorList()
{
	SelectorList* selectorList = new SelectorList;
	while (!eof())
	{
		Selector* selector = ParseSelector();

		selectorList->m_items.push_back(selector);

		if (m_c != L',')
		{
			break;
		}

		getnextc();
	}

	return selectorList;
}

void CSSStream::ParsePropertyList(IStyleDeclaration* sp)
{
	SkipSpacesComments();

	while (isalpha(m_c))
	{
		String prefix;
		String propertyName;
		GetNSName(prefix, propertyName);

		EatChar(':');
		SkipSpacesComments();

		String propertyValue;

		while (!eof())
		{
			if (m_c == '}')
			{
				break;
			}

			if (m_c == ';')
			{
				break;
			}

			propertyValue += (WCHAR)m_c;
			getnextc();
		}

		sp->SetProperty(prefix, propertyName, propertyValue);

		if (m_c == ';')
		{
			getnextc();
			SkipSpacesComments();
		}
		else
		{
			break;
		}
	}
}

void CSSStream::ParseDeclaration(IStyleDeclaration* sp)
{
	if (m_c != '}')
	{
		ParsePropertyList(sp);
	}
}

void CSSStream::ParseStyleRule()
{
	SelectorList* selectors = ParseSelectorList();
	EatChar('{');
	IStyleDeclaration* declaration = m_styleSheet->CreateDeclaration();
	ParseDeclaration(declaration);
	EatChar('}');

	m_styleSheet->AddRules(selectors, declaration);
}

void CSSStream::ParseRule()
{
	ParseStyleRule();
}

void CSSStream::ParseRules()
{
	SkipSpacesComments();
	while (!eof())
	{
		ParseRule();
		SkipSpacesComments();
	}
}

void CSSStream::Parse(IStyleSheet* styleSheet)
{
	getnextc();

	m_styleSheet = styleSheet;
	ParseRules();
}

#if 0
CSSRule* CSSStream::ParseRule(CSSStyleSheet* parentStyleSheet, CSSRule* parentRule, ICSSRuleListener* pListener)
{
//	stream->SkipSpaces();

	getnextc();

	if (m_c == L'/')
	{
		getnextc();
		//if (c == L'*')
		EatChar(L'*');
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
	else if (m_c == L'@')	// at-rule
	{
		ASSERT(0);
#if 0
		String id = stream.GetID();

		StringStream strbuilder;

		strbuilder << L"@";
		strbuilder << id;

		int curly = 0;

		while (!stream.eof())
		{
			strbuilder << (WCHAR)m_c;

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

		pCallback->AtRule(id, cssText);

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
#endif
	}
	else
	{
		ParseStyleRule();
		if (p)
		{
		//	p->m_textOffset[0] = stream.m_ipos;

			p->m_parentStyleSheet = parentStyleSheet;
			p->m_parentRule = parentRule;

			StringStream cssText;

		// Skip selectors
			while (!stream.eof())
			{
				cssText << (WCHAR)stream.m_c;

				if (m_c == L'{')
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

void StyleSheet::Parse(Stream& stream)
{
	try
	{
		CSSStream stream(stream);
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
#endif

}
}
