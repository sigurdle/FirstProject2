#include "stdafx.h"
#include "LXML2.h"

#include "CSSStyleRule.h"

#include "CSSStream.h"

/*
sysstring striptrailspaces(const OLECHAR* bstr)
{
	int len = wcslen(bstr);

	int i;
	for (i = len-1; i >= 0; i--)
	{
		if (!iswspace(bstr[i]))
			break;
	}

	return sysstring(bstr, i+1);
}
*/

namespace System
{
namespace Web
{

/////////////////////////////////////////////////////////////////////////////
// CSSStyleRule

CSSStyleRule::CSSStyleRule()
{
	m_bCSSTextUpdated = true;

	m_declaration = new CSSStyleDeclaration;
	m_selectorList = new CSSSelectorList;
}

CSSStyleRule::~CSSStyleRule()
{
	delete m_declaration;
	delete m_selectorList;
}

#if 0
{
	HRESULT hr;

	ASSERT(0);
#if 0
	hr = CComObject<CSSStyleDeclaration>::CreateInstance(&m_declaration);
	if (FAILED(hr)) return hr;
	m_declaration->AddRef();
	m_declaration->m_pListener = this;

	hr = CComObject<CSSSelectorList>::CreateInstance(&m_selectorList);
	if (FAILED(hr)) return hr;
//	m_selectorList->AddRef();
	m_selectorList->m_ownerRule = this;
#endif
	return 0;
}

void CSSStyleRule::FinalRelease()
{
	if (m_selectorList)
	{
//		m_selectorList->Release();
		m_selectorList = NULL;
	}

	if (m_declaration)
	{
		m_declaration->m_pListener = NULL;
//		m_declaration->Release();
		m_declaration = NULL;
	}
}
#endif

CSSStyleDeclaration* CSSStyleRule::get_style()
{
	return m_declaration;
}

String CSSStyleRule::get_selectorText()
{
	return m_selectorList->get_selectorText();
}

void CSSStyleRule::set_selectorText(StringIn newVal)
{
	m_selectorList->set_selectorText(newVal);
//	m_selectorText = newVal;
//	ParseSelectorText();

// TODO: remove below when m_selectorList implements listener
	m_bCSSTextUpdated = false;
	if (m_pListener)
	{
		m_pListener->OnRuleChanged(this);
	}
}

void CSSStyleRule::UpdateCSSText()
{
	ASSERT(0);
#if 0

	StringW* decl = m_declaration->get_cssText();

	m_cssText = m_selectorList->GetSelectorTextRef();
	m_cssText += OLESTR(" {");
	m_cssText += decl;
	m_cssText += OLESTR("}");
#endif
	m_bCSSTextUpdated = true;
}

void CSSStyleRule::ParseCSSText()
{
	//CSSStream* stream = NULL;

	TRY
	{
		CSSStream stream(m_cssText);

		stream.SkipSpacesComments();

	// Get selector text
		//String strbuilder(&buffer);

		String selectorText;

		int c;

		while (!stream.eof())
		{
			if (stream.m_c == L'{')
			{
				break;
			}

			selectorText += (WCHAR)stream.m_c;
			stream.getnextc();
		}

		stream.EatChar(L'{');

		ASSERT(0);
#if 0
		selectorText = selectorText.TrimRight();// = striptrailspaces(m_selectorText);
#endif
		String declarationText;

	// Get declaration text
		while (!stream.eof())
		{
			if (stream.m_c == '}')
			{
				break;
			}

			declarationText += (WCHAR)stream.m_c;
			stream.getnextc();
		}

		stream.EatChar(L'}');

	// Parse selector text
	//	ParseSelectorText();
		m_selectorList->set_selectorText(selectorText);

	// Parse declaration text
		m_declaration->set_cssText(declarationText);
	}
	CATCH (Exception* e)
	{
		DebugTrace("ERROR parsing style rule\n");
	//	TRACE("ERROR parsing style rule: %S\n", p);
	}

	//delete stream;
}

String CSSStyleRule::get_cssText()
{
	if (!m_bCSSTextUpdated)
		UpdateCSSText();

	return m_cssText;
}

void CSSStyleRule::set_cssText(StringIn newVal)
{
	m_cssText = newVal;//CLCSSRuleImpl<ILCSSStyleRule>::set_cssText(newVal);

	ParseCSSText();
	m_bCSSTextUpdated = true;
}

/*
#if 0
void CSSStyleRule::ParseSelector(CSSStream* stream, CSelector* pSelector)
{
	stream->SkipSpacesComments();

	CSimpleSelectorSequence* pSingleSelectorSequence = new CSimpleSelectorSequence;
	pSingleSelectorSequence->m_ownerSelector = pSelector;

	while (!stream->eof())
	{
		try
		{
			ParseSingleSelectorSequence(stream, pSingleSelectorSequence);
		}
		catch(WCHAR* msg)
		{
			delete pSingleSelectorSequence;
			throw msg;
		}

		//pSelector->m_simpleSelectorSequences.Add(pSingleSelectorSequence);

		stream->SkipSpacesComments();

		if (!stream->eof())
		{
			int c = stream->getnextc();
			if (c == L'>' || c == L'*' || c == L'+' || c == L'~')
			{
				pSingleSelectorSequence->m_combinator = c;
			}
			else
			{
				stream->ungetnextc();
				pSingleSelectorSequence->m_combinator = L' ';
			}

			stream->SkipSpacesComments();

			c = stream->getnextc();
			stream->ungetnextc();

			if (c == L',')	// End of this selector, start of new one
			{
				break;
			}

			if (!stream->eof())
			{
				CSimpleSelectorSequence* pRight = new CSimpleSelectorSequence;
				pRight->m_pLeft = pSingleSelectorSequence;
				pSingleSelectorSequence = pRight;
				pSingleSelectorSequence->m_ownerSelector = pSelector;
			}
		}
	}

	pSelector->m_pRight = pSingleSelectorSequence;

	pSelector->CalculateSpecificity();
}
#endif
*/

}	// Web
}
