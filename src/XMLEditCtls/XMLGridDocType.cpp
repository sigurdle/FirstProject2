#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridNode.h"
#include "XMLGridDocType.h"
#include "XMLGridElement.h"
#include "XMLGridCharacterData.h"

#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr);

////////////////////////////////////////////////////////////////////////
// CGridDTDElement

// virtual
void CGridDTDElement::Size(MSWindows::HDC hDC, int width)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDTDElement> element = m_domNode;

	/*
	{
		CComBSTR value;
		entity->get_value(&value);

		if (width < 10) width = 10;

		CRect rc(0, 0, width-2, 0);
		ATLASSERT(rc.Width() >= 0);
		DrawText(hDC, sysstring(value), value.Length(), &rc, DT_CALCRECT | DT_EDITCONTROL | DT_WORDBREAK);

		m_size.cx = max(width, rc.Width());
		m_size.cy = rc.Height()+2;
	}
	*/

	m_size.cx += 80;
	m_size.cy = 18;
//	m_contentRect.OffsetRect(80, 0);
#endif
}

// virtual
void CGridDTDElement::Draw(MSWindows::HDC hDC, bool bSelected)
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	CComQIPtr<ILDTDElement> element = m_domNode;

	CRect rc(0, 0, m_size.cx, m_size.cy);

	CComBSTR name;
	element->get_name(&name);

	CComBSTR text = L"ELEMENT ";
	text += name;

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	CRect namerect(0, 0, 80, m_size.cy);
	DrawText(hDC, W2A(text), text.Length(), &namerect, DT_SINGLELINE);
	DrawTopLeft(hDC, &namerect, RGB(200,200,200));
#endif
}

////////////////////////////////////////////////////////////////////////
// CGridDTDElement

// virtual
void CGridDTDAttList::Size(MSWindows::HDC hDC, int width)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDTDAttList> attlist = m_domNode;

	/*
	{
		CComBSTR value;
		entity->get_value(&value);

		if (width < 10) width = 10;

		CRect rc(0, 0, width-2, 0);
		ATLASSERT(rc.Width() >= 0);
		DrawText(hDC, sysstring(value), value.Length(), &rc, DT_CALCRECT | DT_EDITCONTROL | DT_WORDBREAK);

		m_size.cx = max(width, rc.Width());
		m_size.cy = rc.Height()+2;
	}
	*/

	m_size.cx += 80;
	m_size.cy = 18;
//	m_contentRect.OffsetRect(80, 0);
#endif
}

// virtual
void CGridDTDAttList::Draw(MSWindows::HDC hDC, bool bSelected)
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	CComQIPtr<ILDTDAttList> attlist = m_domNode;

	CRect rc(0, 0, m_size.cx, m_size.cy);

	CComBSTR name;
	attlist->get_name(&name);

	CComBSTR text = L"ATTLIST ";
	text += name;

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	CRect namerect(0, 0, 80, m_size.cy);
	DrawText(hDC, W2A(text), text.Length(), &namerect, DT_SINGLELINE);
	DrawTopLeft(hDC, &namerect, RGB(200,200,200));
#endif
}

////////////////////////////////////////////////////////////////////////
// CGridEntity

// virtual
void CGridEntity::BuildChildren()
{
	ASSERT(0);
#if 0
	LXmlEdit::Node* child = m_domNode->get_firstChild();
	while (child != NULL)
	{
		LDOMNodeType nodeType = child->get_nodeType();

		if (nodeType == LNODE_DOCUMENT_TYPE)
		{
			CGridNode* pChild = m_pUI->CreateGridNode(child);

			m_childList.AddTail(pChild);

			pChild->BuildChildren();
		}
		else if (nodeType == LNODE_ELEMENT)
		{
			CGridNode* pChild = m_pUI->CreateGridNode(child);

			static_cast<CGridElement*>(pChild)->BuildChildren();

			m_childList.AddTail(pChild);
		}
		else if (nodeType == LNODE_TEXT || nodeType == LNODE_COMMENT || nodeType == LNODE_CDATA_SECTION)
		{
			CGridNode* pChild = m_pUI->CreateGridNode(child);

			m_childList.AddTail(pChild);
		}
		else if (nodeType == LNODE_ENTITY_REFERENCE)
		{
			CGridNode* pChild = m_pUI->CreateGridNode(child);

			m_childList.AddTail(pChild);
		}
		else if (nodeType == LNODE_NOT_WELLFORMED)
		{
			CGridNode* pChild = m_pUI->CreateGridNode(child);

			m_childList.AddTail(pChild);
		}

		child = child->get_nextSibling();
	}

//	RebuildChildList();
#endif
}

// virtual
void CGridEntity::Size(MSWindows::HDC hDC, int width)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDTDEntity> entity = m_domNode;

	{
		CComBSTR value;
		entity->get_value(&value);

		if (width < 10) width = 10;

		CRect rc(0, 0, width-2, 0);
		ATLASSERT(rc.Width() >= 0);
		DrawText(hDC, sysstring(value), value.Length(), &rc, DT_CALCRECT | DT_EDITCONTROL | DT_WORDBREAK);

		m_size.cx = max(width, rc.Width());
		m_size.cy = rc.Height()+2;
	}

	m_size.cx += 80;
//	m_contentRect.OffsetRect(80, 0);
#endif
}

// virtual
void CGridEntity::Draw(MSWindows::HDC hDC, bool bSelected)
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	CComQIPtr<ILDTDEntity> entity = m_domNode;

	CRect rc(0, 0, m_size.cx, m_size.cy);

	CComBSTR name;
	entity->get_name(&name);

	CComBSTR value;
	entity->get_value(&value);

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	CRect namerect(0, 0, 80, m_size.cy);
	DrawText(hDC, W2A(name), name.Length(), &namerect, DT_SINGLELINE);
	DrawTopLeft(hDC, &namerect, RGB(200,200,200));

	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

	CRect valuerect(80, 0, m_size.cx, m_size.cy);
	DrawText(hDC, W2A(value), value.Length(), &valuerect, DT_WORDBREAK | DT_EDITCONTROL);
	DrawTopLeft(hDC, &valuerect, RGB(200,200,200));
#endif
}

#if 0
////////////////////////////////////////////////////////////////////////
// CGridDTDComment

// virtual
void CGridDTDComment::Size(HDC hDC, int width)
{
	CComQIPtr<ILDTDComment> comment = m_object;

	{
		CComBSTR data;
		comment->get_data(&data);

		if (width < 10) width = 10;

		CRect rc(0, 0, width-2, 0);
		ATLASSERT(rc.Width() >= 0);
		DrawText(hDC, sysstring(data), data.Length(), &rc, DT_CALCRECT | DT_EDITCONTROL | DT_WORDBREAK);

		m_size.cx = max(width, rc.Width());
		m_size.cy = rc.Height()+2;
	}

	m_size.cx += 80;
//	m_contentRect.OffsetRect(80, 0);
}

// virtual
void CGridDTDComment::Draw(HDC hDC, BOOL bSelected)
{
	USES_CONVERSION;

	CComQIPtr<ILDTDComment> comment = m_object;

	CRect rc(0, 0, m_size.cx, m_size.cy);

	CComBSTR data;
	comment->get_data(&data);

	CRect namerect(0, 0, 80, m_size.cy);
	DrawTopLeft(hDC, &namerect, RGB(200,200,200));

	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

	CRect valuerect(80, 0, m_size.cx, m_size.cy);
	DrawText(hDC, W2A(data), data.Length(), &valuerect, DT_WORDBREAK | DT_EDITCONTROL);
	DrawTopLeft(hDC, &valuerect, RGB(200,200,200));
}
#endif

#if 0
///////////////////////////////////////////////////////////////////////
// CGridDTDDocument

// virtual
void CGridDTDDocument::BuildChildren()
{
	CComQIPtr<ILDTDDocument> internalSubset = m_object;
//	doctype->get_internalDTD(&internalSubset);

	if (internalSubset)
	{
		long length;
		internalSubset->get_length(&length);

		for (int i = 0; i < length; i++)
		{
			CComPtr<ILDTDObject> object;
			internalSubset->item(i, &object);

			_DTDObjectType objectType;
			object->get_objectType(&objectType);

			if (objectType == DTD_ENTITY)
			{
				CComObject<CGridEntity>* pEntity;
				CComObject<CGridEntity>::CreateInstance(&pEntity);
				pEntity->AddRef();

				pEntity->m_pUI = m_pUI;
				pEntity->m_object = object;

				m_childList.AddTail(pEntity);
			}
			else if (objectType == DTD_ELEMENT)
			{
				CComObject<CGridDTDElement>* p;
				CComObject<CGridDTDElement>::CreateInstance(&p);
				p->AddRef();

				p->m_pUI = m_pUI;
				p->m_object = object;

				m_childList.AddTail(p);
			}
			else if (objectType == DTD_ATTLIST)
			{
				CComObject<CGridDTDAttList>* p;
				CComObject<CGridDTDAttList>::CreateInstance(&p);
				p->AddRef();

				p->m_pUI = m_pUI;
				p->m_object = object;

				m_childList.AddTail(p);
			}
			else if (objectType == DTD_COMMENT)
			{
				CComObject<CGridDTDComment>* pEntity;
				CComObject<CGridDTDComment>::CreateInstance(&pEntity);
				pEntity->AddRef();

				pEntity->m_pUI = m_pUI;
				pEntity->m_object = object;

				m_childList.AddTail(pEntity);
			}
		}
	}
}

// virtual
void CGridDTDDocument::BuildXML(IStream* stream)
{
	ATLASSERT(0);
}

// virtual
sysstring CGridDTDDocument::GetNodeName()
{
	BSTR bnodeName;
	m_domElement->get_nodeName(&bnodeName);
	return sysstring(bnodeName, false);
}

// virtual
void CGridDTDDocument::Size(HDC hDC, int width)
{
//	m_size.cx = max(width, 40);
//	m_size.cy = 20;

//	CComBSTR tagName = L"DOCTYPE";
	//m_domElement->get_nodeName(&tagName);

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);
/*
	CRect rc(0,0,0,0);
	DrawText(hDC, sysstring(tagName), tagName.Length(), &rc, DT_CALCRECT | DT_SINGLELINE);
*/
//	m_nameHeight = rc.Height();

	//width = max(width, 20+rc.Width());
	width -= 20;
	if (width < 0) width = 0;

	m_size.cx = width;
	m_size.cy = 0;

	if (m_expanded)
	{
		SizeContent(hDC, width);
	}
	//else
	//	m_size.cx = width;

	{
		int y = /*m_parent? m_nameHeight:*/ 0;

		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);

			if (m_parent)
				pChild->m_pos.x = 20;
			pChild->m_pos.y = y;

			y += pChild->m_size.cy;
		}
	}

	m_size.cx += 20;
	//m_size.cy += m_nameHeight;

}

// virtual
void CGridDTDDocument::Draw(HDC hDC, BOOL bSelected)
{
	USES_CONVERSION;

//	CComQIPtr<ILDOMDocumentType> doctype = m_domElement;

//	CComBSTR name;
//	doctype->get_name(&name);

	/*
	{
		sysstring text = L"DOCTYPE";

		CRect trect(16, 0, m_size.cx-1, m_nameHeight);

//	sysstring tagName = GetNodeName();

		SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);
		DrawText(hDC, text, text.length(), &trect, DT_SINGLELINE | DT_END_ELLIPSIS);
	}
	*/

	CRect rc(0, 0, m_size.cx, m_size.cy);

	//DrawText(hDC, W2A(name), name.Length(), &rc, DT_SINGLELINE);

	DrawTopLeft(hDC, &rc, RGB(200,200,200));

// Draw children
	if (m_expanded)
	{
		POINT oldOrg;
		OffsetViewportOrgEx(hDC, 20, 0/*m_nameHeight*/, &oldOrg);

		DrawContent(hDC, bSelected);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	}

	DrawExpand(hDC, FALSE);
}
#endif

///////////////////////////////////////////////////////////////////////
// CGridDocType

// virtual
void CGridDocType::BuildChildren()
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMDocumentType> doctype = m_domNode;

	CComQIPtr<ILDOMInternalSubsetNode> internalSubset;
	doctype->get_internalSubsetNode(&internalSubset);

//	CComPtr<ILDTDDocument> internalSubset;
//	doctype->get_internalDTD(&internalSubset);

	if (internalSubset)
	{
		CComPtr<ILDOMNodeList> nodes;
		internalSubset->get_childNodes(&nodes);

		long length;
		nodes->get_length(&length);

		for (int i = 0; i < length; i++)
		{
		ATLASSERT(0);

#if 0
			CComPtr<ILDOMNode> object;
			nodes->item(i, &object);

			_LDOMNodeType objectType;
			object->get_nodeType(&objectType);

			if (objectType == DTD_ENTITY)
			{
				CComObject<CGridEntity>* p;
				CComObject<CGridEntity>::CreateInstance(&p);
				p->AddRef();

				p->m_pUI = m_pUI;
				p->m_domElement = object;

				p->m_parent = this;
				m_childList.AddTail(p);
			}
			else if (objectType == LNODE_COMMENT)
			{
				CComObject<CGridCharacterData>* p;
				CComObject<CGridCharacterData>::CreateInstance(&p);
				p->AddRef();

				p->m_pUI = m_pUI;
				p->m_domElement = object;

				p->m_parent = this;
				m_childList.AddTail(p);
			}
#endif
		}
	}
#endif
}

// virtual
void CGridDocType::BuildXML(System::StringBuilderW& stream)
{
	ASSERT(0);
}

// virtual
void CGridDocType::BuildXML(System::IO::ISequentialByteStream* stream)
{
	ASSERT(0);
}

// virtual
System::StringW* CGridDocType::GetNodeName()
{
	return m_domNode->get_nodeName();
}

// virtual
void CGridDocType::Size(MSWindows::HDC hDC, int width)
{
//	m_size.cx = max(width, 40);
//	m_size.cy = 20;

	ASSERT(0);
#if 0

	CComBSTR tagName = L"DOCTYPE";
	//m_domElement->get_nodeName(&tagName);

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	CRect rc(0,0,0,0);
	DrawText(hDC, sysstring(tagName), tagName.Length(), &rc, DT_CALCRECT | DT_SINGLELINE);

	m_nameHeight = rc.Height();

	width = max(width, 20+rc.Width());
	width -= 20;
	if (width < 0) width = 0;

	m_size.cx = width;
	m_size.cy = 0;

	if (m_expanded)
	{
		SizeContent(hDC, width);
	}
	//else
	//	m_size.cx = width;

	{
		int y = m_parent? m_nameHeight: 0;

		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);

			if (m_parent)
				pChild->m_pos.x = 20;
			pChild->m_pos.y = y;

			y += pChild->m_size.cy;
		}
	}

	m_size.cx += 20;
	m_size.cy += m_nameHeight;

#endif
}

// virtual
void CGridDocType::Draw(MSWindows::HDC hDC, bool bSelected)
{
	//USES_CONVERSION;

	ASSERT(0);
#if 0

	CComQIPtr<ILDOMDocumentType> doctype = m_domNode;

	CComBSTR name;
	doctype->get_name(&name);

	{
		sysstring text = L"DOCTYPE";

		CRect trect(16, 0, m_size.cx-1, m_nameHeight);

//	sysstring tagName = GetNodeName();

		SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);
		DrawText(hDC, text, text.length(), &trect, DT_SINGLELINE | DT_END_ELLIPSIS);
	}

	CRect rc(0, 0, m_size.cx, m_size.cy);

	//DrawText(hDC, W2A(name), name.Length(), &rc, DT_SINGLELINE);

	DrawTopLeft(hDC, &rc, RGB(200,200,200));

// Draw children
	if (m_expanded)
	{
		POINT oldOrg;
		OffsetViewportOrgEx(hDC, 20, m_nameHeight, &oldOrg);

		DrawContent(hDC, bSelected);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	}

	DrawExpand(hDC, FALSE);
#endif
}

}
