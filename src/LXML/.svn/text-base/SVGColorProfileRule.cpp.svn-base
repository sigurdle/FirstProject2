#include "stdafx.h"
#include "LXML2.h"
#include "SVGColorProfileRule.h"

#include "CSSStream.h"

namespace System
{
namespace Web
{

/*
int SVGColorProfileRule::FinalConstruct()
{
	m_descriptors = new CCSSDescriptors;
	//m_descriptors->AddRef();

	return 0;
}

void SVGColorProfileRule::FinalRelease()
{
	if (m_descriptors)
	{
	//	m_descriptors->Release();
		m_descriptors = NULL;
	}
}
*/

String SVGColorProfileRule::get_src()
{
	ASSERT(0);
	return NULL;//sysstring();
}

void SVGColorProfileRule::set_src(StringIn newVal)
{
	ASSERT(0);
}

String SVGColorProfileRule::get_name()
{
	ASSERT(0);
	return NULL;//sysstring();
}

void SVGColorProfileRule::set_name(StringIn newVal)
{
	ASSERT(0);
}

SVGRenderingIntent SVGColorProfileRule::get_renderingIntent()
{
	ASSERT(0);
	//*pVal = m_renderingIntent;
	return RENDERING_INTENT_UNKNOWN;
}

void SVGColorProfileRule::set_renderingIntent(SVGRenderingIntent newVal)
{
	ASSERT(0);
}

void SVGColorProfileRule::set_cssText(StringIn newVal)
{
	m_cssText = newVal;
	ParseCSSText();
	m_bCSSTextUpdated = true;
}

void SVGColorProfileRule::ParseCSSText()
{
	ASSERT(0);
#if 0

	ASSERT(m_parentStyleSheet);

//	BOOL imports = TRUE;

	CSSStream* stream;

	TRY
	{
		stream = new CSSStream(m_cssText);

		stream->EatChar(L'@');

		sysstring id;

		id = stream->GetID();
		if (tcscmp(id.c_str(), OLESTR("color-profile")))
			THROW(OLESTR("Expected 'color-profile'"));

		stream->SkipSpaces();

		stream->EatChar(L'{');

#if 0

		while (!stream->eof())
		{
			int c = stream->getc();
			stream->ungetc();
			if (c == L'}')
			{
				break;
			}

			CComPtr<ILCSSRule> rule;
			ParseRule(stream, m_parentStyleSheet, this, NULL/*this*/, &rule);
			if (rule)
			{
				m_cssRules->m_rules.Add(rule.Detach());
			}

			stream->SkipSpaces();
		}
#endif

		stream->EatChar(L'}');
	}
	CATCH(OLECHAR* p)
	{
	//	TRACE("ERROR Parsing Stylesheet: %S\n", p);
		TRACE("ERROR Parsing Stylesheet\n");
		//MessageBox(NULL, _bstr_t(p), "CSS", MB_OK);
	}

	delete stream;
#endif
}

}	// Web
}
