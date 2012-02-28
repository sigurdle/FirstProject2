#include "stdafx.h"
#include "HTML2.h"

#include "SMILSeqElement.h"

namespace System
{
namespace Web
{

SMILSeqElement::SMILSeqElement(NamedNodeMap* attributes) : SMILElement(new PElementBase(this), attributes)
{
	m_timeContainerImpl = new ElementTimeContainerImpl(this);

	SetAllValues(this);	// ???
}

void SMILSeqElement::seekElement(double seekTo)
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

// TODO sequential
#if 0

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
			ASSERT(0);	// TODO remove

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
