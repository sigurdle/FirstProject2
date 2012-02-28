#include "stdafx.h"
#include "LXML2.h"
#include "CDATASection.h"

namespace System
{
namespace Web
{

// static
ImmutableString<wchar_t> CDATASection::s_nodeName(L"#cdata_section");

CDATASection::CDATASection() : CharacterData(NULL)
{
}

NodeType CDATASection::get_nodeType() const
{
	return NODE_CDATA_SECTION;
}

String CDATASection::get_nodeName() const
{
	return &s_nodeName;
}

Node* CDATASection::cloneNodeExport(Document* ownerDocument,  bool deep) const
{
	CDATASection* newNode = new CDATASection;
	if (newNode)
	{
		newNode->m_ownerDocument = ownerDocument;
		newNode->m_data = m_data;

		return newNode;
	}

	return NULL;
}

}	// w3c
}
