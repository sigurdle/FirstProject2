#include "stdafx.h"
#include "HTML2.h"

#include "SMILParElement.h"

namespace System
{
namespace Web
{

SMILParElement::SMILParElement(NamedNodeMap* attributes) : SMILElement(new PElementBase(this), attributes)
{
	m_timeContainerImpl = new ElementTimeContainerImpl(this);

	SetAllValues(this);	// ???
}

#if 0
void Seek(ILDOMElement* element, double seekTo)
{
	CComQIPtr<ILElementTime> elementTime = node;
	if (elementTime)
	{
		elementTime->Seek(seekTo);
	}

	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> childelement = node;
		if (childelement)
		{
			Seek(element
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}
#endif

#if 0
STDMETHODIMP CLSMILParElement::Seek(/*[in]*/ double parentSimpleTime)
{
	if (m_pCurrentInterval)
	{
		if (parentSimpleTime > m_parentSimpleTime)	// Seeking Forward
		{
			while (1)	// loop
			{
				if (m_pCurrentInterval)
				{
					// Check if going from inactive to active on the current interval
					if (	m_parentSimpleTime <= m_pCurrentInterval->m_begin &&
							!m_pCurrentInterval->m_bActive &&
							parentSimpleTime >= m_pCurrentInterval->m_begin)	// From inactive to active
					{
						m_pCurrentInterval->m_bActive = TRUE;
						//static_cast<CLSMILRegionElement*>(region.p)->Activate(m_pCurrentInterval->m_begin, this);
					}

					// Check if ending the current interval
					if (m_pCurrentInterval->m_bActive//m_parentSimpleTime < m_pCurrentInterval->m_end)
						&&	parentSimpleTime >= m_pCurrentInterval->m_end)	// From active to stopped
					{
					//
						m_parentSimpleTime = m_pCurrentInterval->m_end;
						EndCurrentIntervalAt(m_pCurrentInterval->m_end);

						continue;
					}
					else
					{
						if (m_restart->m_value->m_value == RESTART_ALWAYS)
						{
							CComObject<CLTimeInstance>* pInstanceTime = GetNextInstanceTime(m_pCurrentInterval->m_begin);

							if (pInstanceTime &&
								(parentSimpleTime >= *pInstanceTime && *pInstanceTime < m_pCurrentInterval->m_end))
							{
								m_parentSimpleTime = *pInstanceTime;
								EndCurrentIntervalAt(*pInstanceTime);

								continue;
							}
						}
					}
				}

				m_parentSimpleTime = parentSimpleTime;
				break;
			}
		}
		else
		{
		}

		if (m_pCurrentInterval)
		{
			double activeTime = parentSimpleTime - m_pCurrentInterval->m_begin;
			double simpleTime = REMAINDER(activeTime, m_simpleDur);

			m_tau = activeTime;

		// Seek children
			CComPtr<ILDOMNode> node;
			get_firstChild(&node);
			while (node)
			{
				CComQIPtr<ILElementTime> elementTime = node;
				if (elementTime)
				{
					elementTime->Seek(simpleTime);
				}

				CComPtr<ILDOMNode> nextSibling;
				node->get_nextSibling(&nextSibling);
				node = nextSibling;
			}
		}
	}

	return S_OK;
}
#endif

void SMILParElement::seekElement(double seekTo)
{
	m_timeContainerImpl->Seek(seekTo/1000);

/*
	m_activeTime = seekTo/1000;

	CComPtr<ILDOMNode> node;
	get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILElementTime> elementTime = node;
		if (elementTime)
		{
			elementTime->seekElement(seekTo);
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
	*/

#if 0
// TODO sequential

	m_activeChildren->m_items.RemoveAll();

	m_activeTime = seekTo;

	if (m_documentElement)
	{
		CComPtr<ILDOMElement> body = FindByTagName(m_documentElement, L"body", FALSE);
		if (body)
		{
			// TODO, call body->seekElement ?

			CComPtr<ILDOMNode> node;
			body->get_firstChild(&node);
			while (node)
			{
				CComQIPtr<ILElementTime> elementTime = node;
				if (elementTime)
				{
					elementTime->seekElement(seekTo);
				}

				CComQIPtr<ILSMILMediaElement> mediaElement = node;
				if (mediaElement)
				{
					m_activeChildren->m_items.Add(mediaElement.Detach());
				}

				CComPtr<ILDOMNode> nextSibling;
				node->get_nextSibling(&nextSibling);
				node = nextSibling;
			}
		}
		else
			ATLASSERT(0);	// TODO remove

		{
		// TODO, fix up here
			CLSMILDocument* pDocument = this;//((CLDOMDocument*)m_ownerDocument);

			for (int n = 0; n < pDocument->m_pElements.GetSize(); n++)
			{
#if 0
				pDocument->m_pElements[n]->Flow();
#endif

				if (pDocument->m_pElements[n]->m_pUI)
				{
					pDocument->m_pElements[n]->m_pUI->InvalidateRect(
						&pDocument->m_pElements[n]->m_client, FALSE);
				}
			}
		}
	}
#endif
}

}	// Web
}
