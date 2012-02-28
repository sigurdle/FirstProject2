#include "stdafx.h"
#include "LXML2.h"

#include "CSSImportRule.h"
#include "CSSStyleSheet.h"
#include "CSSStream.h"

namespace System
{
namespace Web
{

CSSImportRule::CSSImportRule()
{
//	m_bCSSTextUpdated = true;
	m_styleSheet = NULL;

//	m_pListener = NULL;
}

CSSImportRule::~CSSImportRule()
{
//		ASSERT(m_pListener == NULL);
}

#if 0
int CSSImportRule::FinalConstruct()
{
//	HRESULT hr;

	/*
	hr = CComObject<CLCSSStyleDeclaration>::CreateInstance(&m_declaration);
	if (FAILED(hr)) return hr;
	m_declaration->AddRef();
	m_declaration->m_pListener = this;
	*/

	return 0;
}

void CSSImportRule::FinalRelease()
{
	if (m_styleSheet)
	{
		//m_styleSheet->m_pListener = NULL;
//		m_styleSheet->Release();
		m_styleSheet = NULL;
	}
}
#endif

void CSSImportRule::LoadHref(StringIn href)
{
	m_href = href;

	ASSERT(m_styleSheet == NULL);

	m_styleSheet = new CSSStyleSheet(NULL/*ownerNode*/, this);
	if (m_styleSheet)
	{
	//	m_styleSheet->AddRef();

		m_styleSheet->load(m_href);
	}
}

String CSSImportRule::get_href() const
{
	return m_href;
}

MediaList* CSSImportRule::get_media()
{
	ASSERT(0);	// TODO

	return NULL;
}

CSSStyleSheet* CSSImportRule::get_styleSheet()
{
	ASSERT(0);
#if 0
	if (m_styleSheet == NULL)
	{
#if WIN32
		WCHAR result[2048];

		String href = m_parentStyleSheet->get_href();

		if (href.GetLength() == 0)	// Internal stylesheet, get href of ownerDocument
		{
			Node* ownerNode;
			ASSERT(0);
#if 0
			m_parentStyleSheet->get_ownerNode(&ownerNode);
#endif
			Document* ownerDocument = ownerNode->get_ownerDocument();

			href = ownerDocument->get_url();
		}

		DWORD resultLenBytes = sizeof(result) - sizeof(result[0]);	// The length does not include the null terminator
		InternetCombineUrl(CStringw(href).c_str(), CStringw(m_href).c_str(), result, &resultLenBytes, 0);

		LoadHref(result);
#else
		ASSERT(0);
#endif
	}
#endif
	return m_styleSheet;
}

void CSSImportRule::set_cssText(StringIn newVal)
{
	//CSSStream* stream;

	TRY
	{
		m_cssText = newVal;//CLCSSRuleImpl<ILCSSImportRule>::set_cssText(newVal);

		CSSStream stream(newVal);
		stream.getnextc();

		stream.EatChar(L'@');

		String id;

		id = stream.GetID();
		if (id == L"import")
			THROW(WSTR("Expected 'import'"));

		stream.SkipSpaces();

		id = stream.GetID();
		if (id == L"url")
			THROW(WSTR("Expected url"));

		stream.EatChar(L'(');

		String url;

		int delimiter = stream.m_c;

		if (delimiter == L'\'' || delimiter == L'\"')
		{
			url = stream.GetString();
			/*
			while (!stream->eof())
			{
				int c = stream->getc();
				if (c == delimiter)
				{
					stream->ungetc();
					break;
				}

				url += c;
			}

			stream->EatChar(delimiter);
			*/
		}
		else
		{
			while (!stream.eof())
			{
				if (stream.m_c == L')')
				{
					break;
				}

				//WCHAR c2[] = {c, 0};
				url += (WCHAR)stream.m_c;
				stream.getnextc();
			}
		}

		stream.EatChar(L')');

		m_href = url;

		/*
		SkipSpaces();

		if (getc() != L';')
		{
			ungetc();
		}

		SkipSpaces();
		*/
	}
	CATCH (Exception* e)
	{
		//delete stream;

		//MessageBox(NULL, _bstr_t(msg), "CSS", MB_OK);
		THROW(e);
	}

	//delete stream;
}

CSSType CSSImportRule::get_type() const
{
	return IMPORT_RULE;
}

}	// Web
}
