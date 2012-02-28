#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridCtl.h"
#include "XMLGridDocument.h"

namespace System
{

// virtual
void CGridDocument::BuildXML(System::IO::ISequentialByteStream* stream)
{
	ULONG cb;

	ASSERT(0);
#if 0

	ATLASSERT(sizeof(_LDOMNodeType) == 4);
	_LDOMNodeType nodeType = LNODE_ELEMENT;
	stream->Write(&nodeType, 4, NULL);

	CComBSTR((BSTR)GetNodeName()).WriteToStream(stream);

	int nchildren = m_childList.GetCount();
	if (TRUE)
		nchildren -= 1;

	stream->Write(&nchildren, 4, &cb);

// Children
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pItem = (CGridItem*)m_childList.GetNext(pos);

		pItem->BuildXML(stream);
	}
#endif
}

// virtual
void CGridDocument::BuildXML(System::StringBuilderW& stream)
{
	//sysstring str = L"";
	ASSERT(0);
#if 0

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pItem = (CGridItem*)m_childList.GetNext(pos);

		sysstring str2 = pItem->BuildXML();

		str += str2;
	}
#endif
}

// virtual
void CGridDocument::BuildChildren()
{
	m_childNodes = new ChildNodes;

	LXmlEdit::Node* child = m_domNode->get_firstChild();
	while (child != NULL)
	{
		Web::NodeType nodeType = child->get_nodeType();

		//if (nodeType == LNODE_DOCUMENT_TYPE)
		{
			CGridNode* pChild = m_pUI->CreateGridNode(child);

			pChild->BuildChildren();

			m_childNodes->AddRChild(pChild);
			m_childNodes->m_items.push_back(pChild);
		}

		child = child->get_nextSibling();
	}

	if (true)
	{
		//CGridEmpty* pEmpty = new CGridEmpty;
		//AddChildTail(pEmpty);
	}

//	RebuildChildList();
}

}
