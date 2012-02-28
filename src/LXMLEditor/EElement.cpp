#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "EElement.h"

#include "EXMLDocument.h"

namespace System
{
namespace LXmlEdit
{

unsigned int NodeList::get_length() const
{
	return m_items.size();
}

Node* NodeList::item(unsigned int index)
{
	return m_items[index];
}

unsigned int NamedNodeMap::get_length() const
{
	return m_items.size();
}

Node* NamedNodeMap::item(unsigned int index)
{
	return m_items[index];
}

Node* NamedNodeMap::getNamedItemNS(System::StringW* namespaceURI, System::StringW* localName)
{
	for (int i = 0; i < m_items.size(); i++)
	{
		if (localName == m_items[i]->m_localName)
		{
			return m_items[i];
		}
	}

	return NULL;
}

/////////////////////////////

Node* Node::get_parentNode()
{
	return m_parentNode;
}

Node* Node::get_firstChild()
{
	return m_firstChild;
}

Node* Node::get_lastChild()
{
	return m_lastChild;
}

Node* Node::get_nextSibling()
{
	return m_nextSibling;
}

Node* Node::get_previousSibling()
{
	return m_previousSibling;
}

long Node::getTextOffset(long which) const
{
	ASSERT(which >= 0 && which < 10);
	return m_textOffset[which];
}

void Node::setTextOffset(long which, long offset)
{
	ASSERT(which >= 0 && which < 10);
	m_textOffset[which] = offset;
}

Node* Node::appendChild(Node* child)
{
	if (m_childNodes)
	{
		return insertNode(child, NULL);
	}
	else
		throw -1;
	return NULL;
}

Node* Node::insertBefore(Node* child, Node* before)
{
	if (m_childNodes)
	{
		return insertNode(child, before);
	}
	else
		throw -1;
	return NULL;
}

/////////////////////////////////////////////////////////////////
// CharacterData

uint CharacterData::get_length() const
{
	return m_data->Length();
}

System::StringW* CharacterData::get_data()
{
	return m_data;
}

void CharacterData::set_data(System::StringW* data)
{
	m_data = data;

	MutationEvent* evt = new MutationEvent;
	evt->InitEvent(WSTR("TextChanged"), true, false);
	dispatchEvent(evt);
}

/*
System::StringW* CharacterData::get_dataref() const
{
	return m_data;
}
*/

void CharacterData::deleteData(long offset, long count)
{
// TODO, improve this

	ASSERT(0);
#if 0

	System::StringW* data = sysstring(m_data.c_str(), offset);
	data += m_data.c_str()+offset+count;
	m_data = data;

	MutationEvent* evt = new MutationEvent;
	evt->m_offset = offset;
	evt->m_len = count;
	evt->initEvent(WSTR("TextDeleted"), true, false);
	dispatchEvent(evt);
#endif
}

void CharacterData::insertData(long offset, System::StringW* arg)
{
	ASSERT(0);
#if 0

// TODO, improve this
	sysstring data = sysstring(m_data.c_str(), offset);
	data += arg;
	data += m_data.c_str()+offset;
	m_data = data;

	MutationEvent* evt = new MutationEvent;
	evt->m_offset = offset;
	evt->m_len = arg.length();
	evt->initEvent(OLESTR("TextInserted"), true, false);
	dispatchEvent(evt);
#endif
}

System::StringW* CharacterData::substringData(unsigned int offset, unsigned int count) const
{
	//if (offset < 0) throw -1;
	if (offset+count > m_data->Length()) throw -1;

	return new System::StringW(string_copy(m_data->c_str() + offset, count));
}

////////////////////////////////////////////
//

NamedNodeMap* Element::get_attributes()
{
	return m_attributes;
}

void Element::set_attributes(NamedNodeMap* attributes)
{
	ASSERT(this);
	m_attributes = attributes;
}

System::StringW* Element::getAttribute(System::StringW* name)
{
	Node* node = m_attributes->getNamedItemNS(NULL, name);
	if (node)
		return dynamic_cast<Attr*>(node)->get_value();
	else
		return NULL;
}

}	// LXmlEdit
}

#if 0
CComQIPtr<ILSVGPathSegList> GetPathSegList(CElementImpl* pElement)
{
	ATLASSERT(0);
	CComQIPtr<ILSVGPathSegList> seglist;
	CPathElement* pathElement;
#if 0

	if (!wcscmp(pElement->m_domElement->tagName, L"path"))
	{
		pathElement = (CPathElement*)pElement;

		SVGLib::ISVGAnimatedPathDataPtr pathData = pElement->m_domElement;
		seglist = pathData->normalizedPathSegList;
	}
	else
	{
		SVGLib::ISVGAnimationElementPtr animation = pElement->m_domElement;
		if (animation)
		{
			SVGLib::ISVGPathElementPtr path = animation->targetElement;
			pathElement = (CPathElement*)pElement->m_pDocument->m_pTree->FindDOMElement(path);

			_bstr_t attrname = (pElement->m_pDocument->m_activeKey == -2)? L"from": L"to";
			_bstr_t pathstr = animation->getAttribute(attrname);

			seglist.CreateInstance("SVG.SVGPathSegList");
			ParsePathData(path, seglist, CUString((BSTR)pathstr));
		}
	}
#endif

	return seglist;
}
#endif

#if 0
void PutPathSegList(CElementImpl* pElement, CComQIPtr<ILSVGPathSegList> seglist)
{
#if 0
	if (!wcscmp(pElement->m_domElement->tagName, L"path"))
	{
	// Do nothing
	}
	else
	{
		SVGLib::ISVGAnimationElementPtr animation = pElement->m_domElement;
		if (animation)
		{
			_bstr_t attrname = (pElement->m_pDocument->m_activeKey == -2)? L"from": L"to";
			_bstr_t pathstr = StringFromPathSegList(seglist);

		//	SVGLib::ISVGPathElementPtr path = animation->targetElement;
		//	pathElement = (CPathElement*)pElement->m_pDocument->m_pTree->FindDOMElement(path);

			animation->setAttribute(attrname, pathstr);
		}
	}
#endif
}
#endif

#if 0
void CElementImpl::DrawBBox(HDC hDC)
{
	SVGLib::ISVGTransformablePtr transformable = m_domElement;

	if (transformable)
	{
		SVGLib::ISVGMatrixPtr matrix = transformable->getScreenCTM();

		SVGLib::ISVGPointPtr pt[4];
		pt[0].CreateInstance(L"SVG.SVGPoint");
		pt[1].CreateInstance(L"SVG.SVGPoint");
		pt[2].CreateInstance(L"SVG.SVGPoint");
		pt[3].CreateInstance(L"SVG.SVGPoint");

		SVGLib::_tagSVGRect rbbox = transformable->getRBBox();
		float x = rbbox.x;
		float y = rbbox.y;
		float width = rbbox.width;
		float height = rbbox.height;

		pt[0]->x = x;				pt[0]->y = y;
		pt[1]->x = x+width-1;	pt[1]->y = y;
		pt[2]->x = x+width-1;	pt[2]->y = y+height-1;
		pt[3]->x = x;				pt[3]->y = y+height-1;

		POINT ipt[4];

		for (int i = 0; i < 4; i++)
		{
			SVGLib::ISVGPointPtr xpt = pt[i]->matrixTransform(matrix);

			ipt[i].x = xpt->x;
			ipt[i].y = xpt->y;
		}

		MoveToEx(hDC, ipt[0].x, ipt[0].y, NULL);
		LineTo(hDC, ipt[1].x, ipt[1].y);
		LineTo(hDC, ipt[2].x, ipt[2].y);
		LineTo(hDC, ipt[3].x, ipt[3].y);
		LineTo(hDC, ipt[0].x, ipt[0].y);

/*
		draw->DrawLine(hDC, ipt[0].x, ipt[0].y, ipt[1].x, ipt[1].y);
		draw->DrawLine(hDC, ipt[1].x, ipt[1].y, ipt[2].x, ipt[2].y);
		draw->DrawLine(hDC, ipt[2].x, ipt[2].y, ipt[3].x, ipt[3].y);
		draw->DrawLine(hDC, ipt[3].x, ipt[3].y, ipt[0].x, ipt[0].y);
*/
	}
}
#endif

#if 0
CElementImpl* CElementImpl::GetTargetElement()
{
#if 0
	SVGLib::ISVGAnimationElementPtr animationElement = m_domElement;
	if (animationElement)
	{
		SVGLib::ISVGElementPtr targetDomElement = animationElement->targetElement;
		return m_pDocument->m_pTree->FindDOMElement(targetDomElement);
	}
	else
#endif
		return this;
}
#endif

#if 0
CElementImpl* CElementImpl::FindPointUnderPoint(ILSVGPoint* mousept, ILSVGMatrix* addmatrix, int& segindex, int& ctl)
{
	SVGLib::ISVGLocatablePtr locatable = m_domElement;
	if (locatable)
	{
		UPOSITION pos = m_childList.GetTailPosition();
		while (pos)
		{
			CElement* pElement = (CElement*)m_childList.GetPrev(pos);

			CElement* pFElement = pElement->FindPointUnderPoint(mousept, segindex, ctl);
			if (pFElement)
				return pFElement;
		}

		if (!wcscmp(m_domElement->tagName, L"path"))
		{
			CPathElement* pathElement = (CPathElement*)this;

			SVGLib::ISVGMatrixPtr matrix = locatable->getScreenCTM();
		/*
			SVGLib::ISVGMatrixPtr imatrix = matrix->inverse();

			SVGLib::ISVGPointPtr xpt = mousept->matrixTransform(imatrix);
*/


			SVGLib::ISVGAnimatedPathDataPtr pathData = m_domElement;
			SVGLib::ISVGPathSegListPtr seglist = pathData->normalizedPathSegList;

			ctl = 0;
			segindex = pathElement->FindPoint(seglist, matrix, mousept->x, mousept->y, ctl);
			if ((segindex >= 0) && (ctl == 0))
				return this;

			SVGLib::_tagSVGRect bbox = locatable->getBBox();

			if (mousept->x >= bbox.x && mousept->x <= bbox.x+bbox.width &&
				mousept->y >=  bbox.y && mousept->y <= bbox.y+bbox.height)
			{
				segindex = -1;
				return this;
			}
		}
	}
	return NULL;
}
#endif

#if 0
#endif

#if 0
CElementImpl* CElementImpl::BuildTree(ILDOMElement* domElement)
{
	CElementImpl* pElement = m_pDocument->CreateElement(domElement);
	if (pElement)
	{
		pElement->m_expanded = TRUE;

		CComPtr<ILDOMNode> child;
		domElement->get_firstChild(&child);

		while (child != NULL)
		{
			CComQIPtr<ILDOMElement> element = child;
			if (element)
			{
				CElementImpl* pElement2 = pElement->BuildTree(element);
				pElement->AddChildTail(pElement2);
			}

			CComPtr<ILDOMNode> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}
	}

	return pElement;
}
#endif

/*
void CElementImpl::SelectPointsInRect(double x1, double y1, double x2, double y2)
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CElement* pElement = (CElement*)m_childList.GetNext(pos);
		pElement->SelectPointsInRect(x1, y1, x2, y2);
	}
}
*/

/*
void CElementImpl::Move(double dx, double dy)
{
}


void CElementImpl::Scale(double cx, double cy, double sx, double sy)
{
}

void CElementImpl::DrawPathCurve(Gdiplus::Graphics* pGraphics, ILSVGMatrix* addmatrix)
{
}
*/
#if 0
void CElementImpl::DeleteSelected()
{
/*
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CElement* pElement = (CElement*)m_childList.GetNext(pos);
		if (pElement->m_selected)
		{
			pElement->m_domElement->parentNode->removeChild(pElement->m_domElement);
		}
	}
*/
}

void CElementImpl::DeselectAll()
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CElement* pElement = (CElement*)m_childList.GetNext(pos);
		pElement->m_selected = FALSE;
	}
}
#endif
