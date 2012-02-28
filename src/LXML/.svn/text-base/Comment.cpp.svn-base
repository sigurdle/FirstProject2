#include "stdafx.h"
#include "LXML2.h"
#include "Comment.h"

namespace System
{
namespace Web
{

Comment::Comment() : CharacterData(NULL)
{
}

NodeType Comment::get_nodeType() const
{
	return NODE_COMMENT;
}

// static
ImmutableString<WCHAR> Comment::s_nodeName(L"#comment");

String Comment::get_nodeName() const
{
	return &s_nodeName;
}

Node* Comment::cloneNodeExport(Document* ownerDocument, bool deep) const
{
	Comment* newNode = new Comment;

	newNode->m_ownerDocument = ownerDocument;
	newNode->m_data = m_data;

	return newNode;
}

}	// Web
}
