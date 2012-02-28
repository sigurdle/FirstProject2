#include "stdafx.h"
#include "LXML2.h"

namespace System
{
namespace Web
{

MutationNameEvent::MutationNameEvent()
{
}

String MutationNameEvent::get_prevNamespaceURI() const
{
	return m_prevNamespaceURI;
}

String MutationNameEvent::get_prevNodeName() const
{
	return m_prevNodeName;
}

void MutationNameEvent::initMutationNameEventNS(
	StringIn namespaceURI,
	StringIn typeArg,
	bool canBubbleArg,
	bool cancelableArg,
	Node* relatedNodeArg,
	StringIn prevNamespaceURI,
	StringIn prevNodeName)
{
	initEvent(typeArg, canBubbleArg, cancelableArg);

	m_relatedNode = relatedNodeArg;

	m_prevNamespaceURI = prevNamespaceURI;
	m_prevNodeName = prevNodeName;
}

}	// Web

}
