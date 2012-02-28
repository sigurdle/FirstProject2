#include "stdafx.h"
#include "LXML2.h"
#include "CSSMediaRule.h"
#include "MediaList.h"
#include "CSSRuleList.h"

#include "CSSStream.h"

namespace System
{
namespace Web
{

ErrorCode ParseRule(CSSStream& stream, CSSStyleSheet* parentStyleSheet, CSSRule* parentRule, ICSSRuleListener* pListener, CSSRule* *pVal);

CSSMediaRule::CSSMediaRule()
{
	m_bCSSTextUpdated = true;
	m_media = NULL;

	m_pListener = NULL;

	m_media = new MediaList;
	m_cssRules = new CSSRuleList;
}

CSSMediaRule::~CSSMediaRule()
{
	ASSERT(m_pListener == NULL);
	delete m_cssRules;
}

/*
int CSSMediaRule::FinalConstruct()
{
	ErrorCode hr;

	m_media = new MediaList;
	//m_media->m_pListener = this;	// TODO

	m_cssRules = new CSSRuleList;

	return 0;
}

void CSSMediaRule::FinalRelease()
{
	if (m_cssRules)
	{
	//	m_cssRules->Release();
		m_cssRules = NULL;
	}

	if (m_media)
	{
		m_media->m_pListener = NULL;
	//	m_media->Release();
		m_media = NULL;
	}
}
*/

void CSSMediaRule::ParseCSSText()
{
	ASSERT(m_parentStyleSheet);

//	BOOL imports = TRUE;

	//CSSStream* stream;

	TRY
	{
		CSSStream stream(m_cssText);

		stream.EatChar(L'@');

		String id;

		id = stream.GetID();
		if (id == L"media")
			raise(Exception("Expected 'media'"));

		stream.SkipSpaces();

		String mediaText;

		while (!stream.eof())
		{
			if (stream.m_c == L'{')
			{
			//	stream.getnextc();
				break;
			}

			mediaText += (WCHAR)stream.m_c;
			stream.getnextc();
		}

		stream.EatChar(L'{');

		m_media->set_mediaText(mediaText);
	//	if (FAILED(hr))
	//		throw OLESTR("Invalid media list");

		stream.SkipSpaces();

		while (!stream.eof())
		{
			if (stream.m_c == L'}')
			{
				break;
			}

			CSSRule* rule;
			ParseRule(stream, m_parentStyleSheet, this, NULL/*this*/, &rule);
			if (rule)
			{
				m_cssRules->m_rules.Add(rule);
			}

			stream.SkipSpaces();
		}

		stream.EatChar(L'}');
	}
	CATCH (Exception* e)
	{
		TRACE("ERROR Parsing Stylesheet\n");
		//TRACE("ERROR Parsing Stylesheet: %S\n", p);
		//MessageBox(NULL, _bstr_t(p), "CSS", MB_OK);
	}

	//delete stream;
}

void CSSMediaRule::UpdateCSSText()
{
	ASSERT(0);

#if 0
	m_cssText = OLESTR("");

	// TODO medialist

	for (int i = 0; i < m_cssRules->m_rules.GetSize(); i++)
	{
		StringW* p = m_cssRules->m_rules[i]->get_cssText();

		m_cssText += p;

		m_cssText += OLESTR("\n");
	}

	m_bCSSTextUpdated = true;
#endif
}

MediaList* CSSMediaRule::get_media()
{
	return m_media;
}

CSSRuleList* CSSMediaRule::get_cssRules()
{
	return m_cssRules;
}

uint CSSMediaRule::insertRule(StringIn rule, long index)
{
	ASSERT(0);
	return 0;
}

void CSSMediaRule::deleteRule(uint index)
{
	ASSERT(0);
}

String CSSMediaRule::get_cssText()
{
	if (!m_bCSSTextUpdated)
	{
		UpdateCSSText();
		m_bCSSTextUpdated = true;
	}

	return m_cssText;//CSSRule<ILCSSMediaRule>::get_cssText(pVal);
}

void CSSMediaRule::set_cssText(StringIn newVal)
{
	m_cssText = newVal;

	ParseCSSText();
	m_bCSSTextUpdated = true;
}

CSSType CSSMediaRule::get_type() const
{
	return MEDIA_RULE;
}

}	// Web
}
