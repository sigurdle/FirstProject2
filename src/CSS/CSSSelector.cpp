#include "stdafx.h"
#include "CSS.h"

namespace System
{
namespace Style
{

Selector::Selector() :
	m_ownerRule(nullptr),
	m_pRight(nullptr),
	m_selectorText(nullptr),
	m_pseudoElement(nullptr),
	m_singleSelectorRule(nullptr)
{
}

Selector::~Selector()
{
	if (m_pRight)
	{
		delete m_pRight;
		m_pRight = nullptr;
	}
}

//virtual
bool CSimpleSelectorType::MatchesElement(ICSSElementResolver* pElement)
{
	/*
	CComQIPtr<ILDOMElement> element = pElement->m_pNode;
	ASSERT(element);
*/
	String name = pElement->get_typeName();
/*	element->get_localName(&name);
	if (name.Length()==0)
	{
		name.Empty();
		element->get_tagName(&name);
	}
	*/

	if (name != m_name)
	{
		return false;
	}

#if 0
	if ((BSTR)m_namespaceURI == NULL)	// Will match any namespace, also undeclared ones
	{
	}
	else if (m_namespaceURI.Length()==0)	// Will match those with undeclared namespace
	{
		CComBSTR namespaceURI;
		element->get_namespaceURI(&namespaceURI);

		if (namespaceURI.Length() > 0)
			return FALSE;
	}
	else	// Match exactly namespace
	{
		CComBSTR namespaceURI;
		element->get_namespaceURI(&namespaceURI);

		if (namespaceURI.Length() != m_namespaceURI.Length())	// If they're not of equal length, we know they're different
			return FALSE;

		if (tcscmp(namespaceURI, m_namespaceURI))
			return FALSE;
	}
#endif

	return true;
}

// virtual
bool CSimpleSelectorClass::MatchesElement(ICSSElementResolver* pElement)
{
	//CComQIPtr<ILDOMElement> element = pElement->m_pNode;

	String value = pElement->getAttribute(WSTR("class"));

	ASSERT(0);
#if 0

	if (value)//->Length())
	{
		const WCHAR* p = value->c_str();

		while (isspace(*p)) p++;

		while (*p)
		{
			const WCHAR* start = p;
			while (*p && !std::isspace(*p))
			{
				p++;
			}

			if (!std::wcsncmp(start, m_className->c_str(), p-start))
			{
				return true;
			}

			while (isspace(*p)) p++;
		}
	}
#endif

	return false;
}

inline int WCSICMP(const WCHAR* a, const WCHAR* b)
{
	if (a == NULL && b == NULL)
		return 0;
	else if (a == NULL)
		return -1;
	else if (b == NULL)
		return 1;
	else
		return _wcsicmp(a, b);
}

// virtual
bool CSimpleSelectorAttribute::MatchesElement(ICSSElementResolver* pElement)
{
	ASSERT(0);
#if 0

//	CComQIPtr<ILDOMElement> element = pElement->m_pNode;

	if (m_attrMatch == 0) // Represents the att attribute, whatever the value of the attribute
	{
		bool b = pElement->hasAttribute(m_attrName);
		if (b)
		{
			return true;
		}
	}
	else
	{
		String value = pElement->getAttribute(m_attrName);

		switch (m_attrMatch)
		{
		case L'=': // Represents the att attribute with value exactly "val"
			{
				if (!WCSICMP(value->c_str(), m_attrValue->c_str()))
				{
					return true;
				}
			}
			break;

		case L'~': // Represents the att attribute whose value is a space-separated list of words, one of which is exactly "val"
			{
				const WCHAR* p = value->c_str();

				while (std::isspace(*p)) p++;

				while (*p)
				{
					const WCHAR* start = p;
					while (*p && !std::isspace(*p))
					{
						p++;
					}

					if (!std::wcsncmp(start, m_attrValue->c_str(), p-start))
						return true;

					while (std::isspace(*p)) p++;
				}
			}
			break;

		case L'|': // Represents the att attribute, its value either being exactly "val" or beginning with "val" immediately followed by "-"
			{
				if (std::wcsncmp(value->c_str(), m_attrValue->c_str(), m_attrValue->Length()))
					return false;

				ASSERT(value->Length() >= m_attrValue->Length());

			// Now we know that that they match on first,
			// now the next must be either '\0' or '-'

				if (value->Length() == m_attrValue->Length())
					return true;

				if ((value->c_str())[m_attrValue->Length()] == L'-')
					return  true;
			}
			break;

		case L'^': // Represents the att attribute whose value begins with the prefix "val"
			{
				if (!_wcsnicmp(value->c_str(), m_attrValue->c_str(), m_attrValue->Length()))
				{
					return true;
				}
			}
			break;

		case L'$': // Represents the att attribute whose value ends with the suffix "val"
			{
				ASSERT(0);
				if (value.GetLength() < m_attrValue.GetLength())
					return false;

#if 0

				if (_wcsicmp(&(value->c_str())[value->Length()-m_attrValue->Length()], m_attrValue->c_str()))
					return true;
#endif
				if (value.RightOf(value.GetLength()-3) == m_attrValue)
					return true;
			}
			break;

		case L'*': // Represents the att attribute whose value contains at least one instance of the substring "val"
			{
				ASSERT(0);
#if 0
				if (std::wcsstr(value->c_str(), m_attrValue->c_str()))
					return true;
#endif
			}
			break;

		default:
			ASSERT(0);
		}
	}
#endif
	return false;
}

//////////////////////////////////////////////////////////////////////////
// CSelector

/*
A selector's specificity is calculated as follows: 

negative selectors are counted like their simple selectors argument 
count the number of ID attributes in the selector (= a) 
count the number of other attributes and pseudo-classes in the selector (= b) 
count the number of element names in the selector (= c) 
ignore pseudo-elements.
*/

void Selector::CalculateSpecificity()
{
	uint a = 0;
	uint b = 0;
	uint c = 0;

	SimpleSelectorSequence* pSimpleSelectorSequence = m_pRight;

	while (pSimpleSelectorSequence != NULL)
	{
		for (uint j = 0; j < pSimpleSelectorSequence->m_items.GetSize(); j++)
		{
			SimpleSelector* pSimpleSelector = pSimpleSelectorSequence->m_items[j];
			
			switch (pSimpleSelector->m_kind)
			{
			case SimpleSelectorKind_id:
				{
					a++;
				}
				break;
				
			case SimpleSelectorKind_class:
			case SimpleSelectorKind_attribute:
				{
					b++;
				}
				break;
				
			case SimpleSelectorKind_type:
				{
					c++;
				}
				break;
			}
		}

		pSimpleSelectorSequence = pSimpleSelectorSequence->m_pLeft;
	}

	m_specificity = a*100 + b*10 + c;
}

//void /*CSSStyleRule::*/GetNSName(CSSStream& stream, String& prefix, String& name);

#if 0
void Selector::ParseSingleSelectorSequence(CSSStream& stream, SimpleSelectorSequence* pSimpleSelectorSequence)
{
/*
	A sequence of simple selectors is a chain of simple selectors that are not
	separated by a combinator. It always begins with a type selector or a
	universal selector. No other type selector or universal selector is allowed in the sequence. 
*/

//	const WCHAR* ppos = stream.m_ppos;

	if (isalpha(stream.m_c))
	{
		CSimpleSelectorType* pSimpleSelector = new CSimpleSelectorType;

		String prefix;
		/*m_ownerRule->*/GetNSName(stream, prefix, pSimpleSelector->m_name);	// element Type

		//pSimpleSelector->m_name = GetID();
		//if (ns.L

		pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
	}
	else
	{
		if (stream.m_c == L'*')	// Universal selector
		{
			stream.getnextc();
		}
		//else ; // Implied

		CSimpleSelectorUniversal* pSimpleSelector = new CSimpleSelectorUniversal;
		pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
	}

	while (!stream.eof())
	{
		if (stream.m_c == '.')	// class
		{
			CSimpleSelectorClass* pSimpleSelector = new CSimpleSelectorClass;

			TRY
			{
				pSimpleSelector->m_className = stream.GetID();
			}
			CATCH (Exception* e)
			{
				delete pSimpleSelector;
				THROW(e);
			}

			pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
		}
		else if (stream.m_c == '#')	// id
		{
			CSimpleSelectorID* pSimpleSelector = new CSimpleSelectorID;

			TRY
			{
				pSimpleSelector->m_id = stream.GetID();
			}
			CATCH (Exception* e)
			{
				delete pSimpleSelector;
				THROW(e);
			}

			pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
		}
		else if (stream.m_c == L'[')
		{
			CSimpleSelectorAttribute* pSimpleSelector = NULL;

			TRY
			{
				pSimpleSelector = new CSimpleSelectorAttribute;

				pSimpleSelector->m_attrName = stream.GetID();

				if (stream.m_c == L']')
				{
					stream.getnextc();
					pSimpleSelector->m_attrMatch = 0;
				}
				else
				{
					if (stream.m_c == L'=')
					{
						stream.getnextc();
						pSimpleSelector->m_attrMatch = L'=';
					}
					else if (stream.m_c == L'~' || stream.m_c == L'|' || stream.m_c == '^' || stream.m_c == L'$' || stream.m_c == L'*')
					{
						stream.getnextc();
						pSimpleSelector->m_attrMatch = stream.m_c;
						stream.EatChar(L'=');
					}
					else
					{
						raise(Exception(L"Expected attribute value"));
					}

					// Get attribute value
					if (stream.m_c == L'\'' || stream.m_c == L'\"')
					{
						stream.getnextc();
						pSimpleSelector->m_attrValue = stream.GetString();
					}
					else
					{
						pSimpleSelector->m_attrValue = stream.GetID();
					}
				}

				stream.EatChar(L']');
			}
			CATCH (Exception* e)
			{
				delete pSimpleSelector;
				THROW(e);
			}

			pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
		}
		else if (stream.m_c == L':')	// pseudo-class or pseudo-element
		{
			//WCHAR* ppos = m_ppos;

			stream.getnextc();
			int colon = stream.m_c;
			if (stream.m_c == ':')
			{
				stream.getnextc();
			}

			String ident = stream.GetID();

			if (colon == L':' ||

			// pseudo-element that is allowed to have only one : (for backwards-compatibility)
				ident == L"first-line" ||
				ident == L"first-letter" ||
				ident == L"before" ||
				ident == L"after")
			{
			//	m_ppos = ppos;
				//CPseudoElement* pPseudoElt = new CPseudoElement;

				pSimpleSelectorSequence->m_ownerSelector->m_pseudoElement = ident;

				break;	// A pseudo-element is the last thing allowed
			}
			else	// pseudo-class
			{
				CSimpleSelectorPseudoClass* pSimpleSelector = NULL;

				if (ident.Compare(L"link"))
				{
					pSimpleSelector = new CPseudoClassLink;
					pSimpleSelector->m_pseudoClassName = ident;

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				}
				else if (!ident.Compare(L"visited"))
				{
					pSimpleSelector = new CPseudoClassVisited;
					pSimpleSelector->m_pseudoClassName = ident;

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				}
				else if (!ident.Compare(L"hover"))
				{
					pSimpleSelector = new CPseudoClassHover;
					pSimpleSelector->m_pseudoClassName = ident;

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				}
				else if (!ident.Compare(L"active"))
				{
					pSimpleSelector = new CPseudoClassActive;
					pSimpleSelector->m_pseudoClassName = ident;

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				}
				else if (!ident.Compare(L"focus"))
				{
					pSimpleSelector = new CPseudoClassFocus;
					pSimpleSelector->m_pseudoClassName = ident;

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				}
				else if (!ident.Compare(L"enabled"))
				{
					pSimpleSelector = new CPseudoClassEnabled;
					pSimpleSelector->m_pseudoClassName = ident;

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				}
				else if (!ident.Compare(L"disabled"))
				{
					pSimpleSelector = new CPseudoClassDisabled;
					pSimpleSelector->m_pseudoClassName = ident;

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
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

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
				}
				else if (!ident.Compare(L"nth-last-child"))
				{
					pSimpleSelector = new CPseudoClassFirstChild;
					pSimpleSelector->m_pseudoClassName = ident;

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
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

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
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

					pSimpleSelectorSequence->m_items.Add(pSimpleSelector);
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
		else
		{
			break;
		}
	}

	// TODO
	/*
	if (ppos == stream.m_ppos)
	{
		THROW(WSTR("Empty Single Selector Sequence"));
	}
	*/

//	ATLTRACE("...done\n");
}
#endif

void Selector::set_selectorText(StringIn newVal)
{

	m_selectorText = newVal;

	ASSERT(0);
#if 0

//	CSSStream* stream = NULL;

	TRY
	{
		CSSStream stream(m_selectorText);

		SimpleSelectorSequence* pSingleSelectorSequence = new SimpleSelectorSequence;
		pSingleSelectorSequence->m_ownerSelector = this;

		while (!stream.eof())
		{
			TRY
			{
				ParseSingleSelectorSequence(stream, pSingleSelectorSequence);
			}
			CATCH(WCHAR* msg)
			{
				//CreateDOMError(LSEVERITY_ERROR, msg, getCurrentLocation());
				delete pSingleSelectorSequence;
				THROW(msg);
			}

			//pSelector->m_simpleSelectorSequences.Add(pSingleSelectorSequence);

			stream.SkipSpacesComments();

			if (!stream.eof())
			{
				if (stream.m_c == L'>' || stream.m_c == L'*' || stream.m_c == L'+' || stream.m_c == L'~')
				{
					pSingleSelectorSequence->m_combinator = stream.m_c;
					stream.getnextc();
				}
				else
				{
					pSingleSelectorSequence->m_combinator = L' ';
				}

				stream.SkipSpacesComments();

				/*
				c = stream->getnextc();
				stream->ungetnextc();

				if (c == L',')	// End of this selector, start of new one
				{
					break;
				}
				*/

				if (!stream.eof())
				{
					SimpleSelectorSequence* pRight = new SimpleSelectorSequence;
					pRight->m_pLeft = pSingleSelectorSequence;
					pSingleSelectorSequence = pRight;
					pSingleSelectorSequence->m_ownerSelector = this;
				}
			}
		}

		m_pRight = pSingleSelectorSequence;

		CalculateSpecificity();
	}
	CATCH (Exception* e)
	{
	//	delete stream;

		THROW(e);
	}
#endif
	//delete stream;
}

}	// Web
}
