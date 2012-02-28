#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"
#include "Text.h"

#include "PTextNode.h"

namespace System
{
namespace Web
{

ImmutableString<WCHAR> Text::s_nodeName(L"#text");

Text::Text() : CharacterData(new PText(this))
{
}

NodeType Text::get_nodeType() const
{
	return NODE_TEXT;
}

String Text::get_nodeName() const
{
	return &s_nodeName;
}

Node* Text::cloneNodeExport(Document* ownerDocument, bool deep) const
{
	Text* newNode = new Text;

	newNode->m_ownerDocument = ownerDocument;
	newNode->m_data = m_data;

	return newNode;
}

Text* Text::splitText(int offset)
{
	String olddata = m_data;

	Text* newText = new Text;
	newText->m_ownerDocument = m_ownerDocument;

// TODO, one of these can use the old buffer (and reallocate, so the next gc allocates only for the new size, when I implement that feature)

	newText->m_data = olddata.SubString(offset, olddata.GetLength() - offset);

	deleteData(offset, m_data.GetLength()-offset);
	//	m_data = SysAllocStringLen(olddata, offset);

		/*
		CComQIPtr<INotifySend> cp = this;//Node;
		if (cp)
		{
			cp->FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
		}
		*/

#if 0
		CComQIPtr<IDOMDocument> ownerDocument;
		get_ownerDocument(&ownerDocument);
		ASSERT(ownerDocument != NULL);

	////////////////////////////////
	// create an event notification for changing the text

		CComQIPtr<IDOMDocumentEvent> ownerDocumentEvent;
		ownerDocument->QueryInterface(&ownerDocumentEvent);
		ASSERT(ownerDocument != NULL);

		CComQIPtr<IDOMMutationEvent, &IID_IDOMMutationEvent> event;
		ownerDocumentEvent->createEvent(OLESTR("MutationEvent"), (IDOMEvent**)&event);
		bool doDefault;

	//
		event->initMutationEvent(OLESTR("DOMCharacterDataModified"), VARIANT_TRUE, VARIANT_FALSE, NULL, olddata, m_data, NULL, CHANGE_UNKNOWN);
		dispatchEvent(event, &doDefault);
	///////////////////////////////////////////
#endif

/*		CComQIPtr<IDOMNode> parentNode;
		get_parentNode(&parentNode);

		CComQIPtr<IDOMNode> nextSibling;
		get_nextSibling(&nextSibling);
*/
		//if (m_nextSibling != NULL)

	if (m_parentNode)
		m_parentNode->insertBefore(newText, m_nextSibling);
		//else
		//	m_parentNode->appendChild(newText, NULL);

	return newText;
}

}	// Web
}	// System
