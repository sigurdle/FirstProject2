#include "stdafx.h"
#include "LXML2.h"
#include "MutationEvent.h"

namespace System
{
namespace Web
{

MutationEvent::MutationEvent()
{
	m_attrChange = CHANGE_UNKNOWN;
}

Node* MutationEvent::get_relatedNode() const
{
	return m_relatedNode;
}

String MutationEvent::get_prevValue() const
{
	return m_prevValue;
}

String MutationEvent::get_newValue() const
{
	return m_newValue;
}

String MutationEvent::get_attrName() const
{
	return m_attrName;
}

DOMAttrChangeType MutationEvent::get_attrChange() const
{
	return m_attrChange;
}

void MutationEvent::initMutationEvent(StringIn typeArg, bool canBubbleArg, bool cancelableArg, Node *relatedNodeArg, StringIn prevValueArg, StringIn newValueArg, StringIn attrNameArg, DOMAttrChangeType attrChangeArg)
{
//	ASSERT(relatedNodeArg != NULL);

// Call base event init
	initEvent(typeArg, canBubbleArg, cancelableArg);

// Mutation specific
	m_relatedNode = relatedNodeArg;
	m_newValue = newValueArg;
	m_prevValue = prevValueArg;
	m_attrChange = attrChangeArg;
	m_attrName = attrNameArg;

//	ASSERT(m_relatedNode != NULL);
}

}	// w3c
}
