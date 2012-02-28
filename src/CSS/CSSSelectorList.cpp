#include "stdafx.h"
#include "CSS.h"

namespace System
{
namespace Style
{

SelectorList::SelectorList() : m_bCSSTextUpdated(true), m_ownerRule(NULL)
{
}

void SelectorList::ParseSelectorText()
{
	ASSERT(0);
#if 0

// Remove any previous parsing
	for (int i = 0; i < m_items.size(); i++)
	{
//		m_items[i]->Release();
	}
	m_items.clear();

//
	//CSSStream* stream = NULL;

	TRY
	{
		CSSStream stream(m_selectorText);

		while (!stream.eof())
		{
			BufferImp<WCHAR> buffer;
			StringBuilderW strbuilder(&buffer);

			while (!stream.eof())
			{
				int c = stream.getnextc();
				if (c == L',')
				{
					stream.ungetnextc();
					break;
				}

				strbuilder << (WCHAR)c;
			}

			StringW* selectorText = buffer.DetachToString();

			Selector* pSelector = new Selector;
			if (pSelector)
			{
//				pSelector->AddRef();
				pSelector->m_ownerRule = m_ownerRule;

				TRY
				{
					pSelector->set_selectorText(selectorText);

					/*
					if (FAILED(hr))
					{
					//	if (!handleError(CreateDOMError(LSEVERITY_ERROR, OLESTR("Invalid Selector text", getCurrentLocation()))
						{
							throw OLESTR("Invalid Selector text");
						}
					}
					*/

					m_items.Add(pSelector);
				}
				CATCH(OLECHAR* msg)
				{
//					pSelector->Release();
					THROW(msg);
				}
			}

			stream.SkipSpacesComments();

			int c = stream.getnextc();
			if (c == L',')
			{
				stream.SkipSpacesComments();
			}
		}
	}
	CATCH(OLECHAR* msg)
	{
	//	delete stream;
		THROW(msg);
	}

	//delete stream;
#endif
}

String SelectorList::get_selectorText()
{
	ASSERT(0);
#if 0

	if (!m_bCSSTextUpdated)
	{
		sysstring str = OLESTR("");
		for (int i = 0; i < m_items.size(); i++)
		{
			if (i > 0) str += OLESTR(",");
			str += m_items[i]->GetSelectorTextRef();
		}

		m_selectorText = str;

		m_bCSSTextUpdated = true;
	}
#endif

	return m_selectorText;
}

void SelectorList::set_selectorText(StringIn selectorText)
{
	// ? Set selector text regardless of parsing success?
	m_selectorText = selectorText;
	m_bCSSTextUpdated = true;

	TRY
	{
		ParseSelectorText();
	}
	CATCH (Exception* e)
	{
		THROW(e);
	}
}

size_t SelectorList::appendItem(StringIn selectorText)
{
	ASSERT(selectorText != nullptr);
	if (selectorText == nullptr) throw -1;//return E_INVALIDARG;

	Selector* pSelector = new Selector;

//	pSelector->AddRef();
	pSelector->m_ownerRule = m_ownerRule;

	pSelector->set_selectorText(selectorText);

	m_bCSSTextUpdated = false;

	//if (SUCCEEDED(hr)	// Add it even if it's invalid?
	return m_items.Add(pSelector);
}

}	// Style
}	// System
