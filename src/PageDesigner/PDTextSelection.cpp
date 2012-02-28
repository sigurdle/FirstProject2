#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDTextSelection.h"

#include "PDStory.h"

int CompareTreePosition(ILDOMNode* pThis, ILDOMNode* pNode);

ILDOMNode* RightMost(ILDOMNode* node, long& offset)
{
	CComPtr<ILDOMNode> lastChild;
	node->get_lastChild(&lastChild);

	if (lastChild)
	{
		return RightMost(lastChild, offset);
	}

	CComQIPtr<ILDOMCharacterData> text = node;
	if (text)
	{
		BSTR bdata;
		text->get_data(&bdata);
		_bstr_t data = _bstr_t(bdata);

		offset = data.length();
	}
	else
		ATLASSERT(0);

	return node;
}

ILDOMNode* PreviousTextOrNonEmptyElement(ILDOMNode* node)
{
	VARIANT_BOOL hasChildNodes;
	LDOMNodeType nodeType;

	CComPtr<ILDOMNode> previousSibling;
	node->get_previousSibling(&previousSibling);

	if (previousSibling)
	{
		previousSibling->get_nodeType(&nodeType);
		previousSibling->hasChildNodes(&hasChildNodes);
	}

	while (previousSibling && (nodeType == NODE_ELEMENT && !hasChildNodes))
	{
		CComPtr<ILDOMNode> previousSibling2;
		previousSibling->get_previousSibling(&previousSibling2);
		previousSibling = previousSibling2;

		if (previousSibling)
		{
			previousSibling->get_nodeType(&nodeType);
			previousSibling->hasChildNodes(&hasChildNodes);
		}
	}

	if (previousSibling)
		return previousSibling.Detach();
	else
		return NULL;
}

HRESULT MoveCursorLeft(ILDOMNode* startContainer, long startOffset, ILDOMNode* *container, long* offset)
{
	if (startOffset > 0)
	{
		(*container = startContainer)->AddRef();
		*offset = startOffset-1;

		return S_OK;
	}
	else
	{
		CComPtr<ILDOMNode> node;
		node = startContainer;

		CComPtr<ILDOMNode> previousSibling = PreviousTextOrNonEmptyElement(node);

		while (previousSibling == NULL)
		{
			CComPtr<ILDOMNode> parentNode;
			node->get_parentNode(&parentNode);
			node = parentNode;
			if (node == NULL) break;

			previousSibling = PreviousTextOrNonEmptyElement(node);
		}

		if (previousSibling)
		{
			node = RightMost(previousSibling, startOffset);

			(*container = node)->AddRef();
			*offset = startOffset-1;

			return S_OK;
		}
	}

	return S_FALSE;
}

ILDOMNode* LeftMost(ILDOMNode* node, long& offset)
{
	CComPtr<ILDOMNode> firstChild;
	node->get_firstChild(&firstChild);

	if (firstChild)
	{
		return LeftMost(firstChild, offset);
	}

	CComQIPtr<ILDOMCharacterData> text = node;
	if (text)
	{
		offset = 0;
	}
	else
		ATLASSERT(0);

	return node;
}

ILDOMNode* NextTextOrNonEmptyElement(ILDOMNode* node)
{
	VARIANT_BOOL hasChildNodes;
	LDOMNodeType nodeType;

	CComPtr<ILDOMNode> nextSibling;
	node->get_nextSibling(&nextSibling);

	if (nextSibling)
	{
		nextSibling->get_nodeType(&nodeType);
		nextSibling->hasChildNodes(&hasChildNodes);
	}

	while (nextSibling && (nodeType == NODE_ELEMENT && !hasChildNodes))
	{
		CComPtr<ILDOMNode> nextSibling2;
		nextSibling->get_nextSibling(&nextSibling2);
		nextSibling = nextSibling2;

		if (nextSibling)
		{
			nextSibling->get_nodeType(&nodeType);
			nextSibling->hasChildNodes(&hasChildNodes);
		}
	}

	if (nextSibling)
		return nextSibling.Detach();
	else
		return NULL;
}

HRESULT MoveCursorRight(ILDOMNode* startContainer, long startOffset, ILDOMNode* *container, long* offset)
{
	CComQIPtr<ILDOMCharacterData> text = startContainer;
	BSTR bdata;
	text->get_data(&bdata);
	_bstr_t data = _bstr_t(bdata, false);

	if (startOffset < data.length())
	{
		(*container = startContainer)->AddRef();
		*offset = startOffset+1;

		return S_OK;
	}
	else
	{
		CComPtr<ILDOMNode> node;
		node = startContainer;

		CComPtr<ILDOMNode> nextSibling = NextTextOrNonEmptyElement(node);

		while (nextSibling == NULL)
		{
			CComPtr<ILDOMNode> parentNode;
			node->get_parentNode(&parentNode);
			node = parentNode;
			if (node == NULL) break;

			nextSibling = NextTextOrNonEmptyElement(node);
		}

		if (nextSibling)
		{
			node = LeftMost(nextSibling, startOffset);

			(*container = node)->AddRef();
			*offset = startOffset+1;

			return S_OK;
		}
	}

	return S_FALSE;
}

HRESULT CPDTextSelection::ExtendIt(ILDOMNode* container, long offset, int bShift)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;

// Dectivate previous range
//	uiManager->DeactivateObject(m_range);

	if (bShift)
	{
		CComPtr<ILDOMNode> startContainer;
		long startOffset;

		CComPtr<ILDOMNode> endContainer;
		long endOffset;

		if (container == m_initContainer)	// start and end share container
		{
			startContainer = container;
			endContainer = container;

			if (offset < m_initOffset)
			{
				startOffset = offset;
				endOffset = m_initOffset;
			}
			else
			{
				startOffset = m_initOffset;
				endOffset = offset;
			}
		}
		else
		{
			int cmp = CompareTreePosition(container, m_initContainer);
			ATLASSERT(cmp != 0);

			if (cmp == -1)
			{
				startContainer = container;
				startOffset = offset;

				endContainer = m_initContainer;
				endOffset = m_initOffset;
			}
			else
			{
				startContainer = m_initContainer;
				startOffset = m_initOffset;

				endContainer = container;
				endOffset = offset;
			}
		}

		m_domrange->setStart(startContainer, startOffset);
		m_domrange->setEnd(endContainer, endOffset);
	}
	else
	{
		m_initContainer = container;
		m_initOffset = offset;

		m_domrange->setStart(container, offset);
		m_domrange->setEnd(container, offset);
	}

	m_curContainer = container;
	m_curOffset = offset;

	// Activate new range
//	uiManager->ActivateObject(GetUnknown(), m_range);

	return S_OK;
}

#include "PDContentText.h"

HRESULT CPDTextSelection::MoveCursorHome(ILDOMNode *curContainer, long curOffset, ILDOMNode **container, long *offset)
{
	CComPtr<IPDObjectText> objectText;
	m_story->GetObjectTextFromRangePosition(curContainer, curOffset, &objectText);

	CComQIPtr<IPDContentText> contentText = objectText;
	if (contentText)
	{
		CPDContentText* pContentText = static_cast<CPDContentText*>(contentText.p);

		CBox* pBox = pContentText->m_pBox->FindBox(curContainer, curOffset);
		if (pBox)
		{
			CLineBox* pLine = pBox->GetParentLineBox();
			if (pLine)
			{
				CTextContentBox* pTextContent = NULL;
				CBox* pBox2 = pLine;
				while (pBox2)
				{
					if (pBox2->m_children.GetSize() == 0)
					{
						pTextContent = (CTextContentBox*)pBox2;
						break;
					}

					pBox2 = pBox2->m_children[0];
				}

				(*container = pTextContent->m_node)->AddRef();
				*offset = pTextContent->m_start;// + ((pTextContent->m_type == 11)? 0: ((CWordBox*)pTextContent)->m_text.length()-1);

				return S_OK;
			}
		}
	}

	return S_FALSE;
}

HRESULT CPDTextSelection::MoveCursorEnd(ILDOMNode *curContainer, long curOffset, ILDOMNode **container, long *offset)
{
	CComPtr<IPDObjectText> objectText;
	m_story->GetObjectTextFromRangePosition(curContainer, curOffset, &objectText);

	CComQIPtr<IPDContentText> contentText = objectText;
	if (contentText)
	{
		CPDContentText* pContentText = static_cast<CPDContentText*>(contentText.p);

		CBox* pBox = pContentText->m_pBox->FindBox(curContainer, curOffset);
		if (pBox)
		{
			CLineBox* pLine = pBox->GetParentLineBox();
			if (pLine)
			{
				CTextContentBox* pTextContent = NULL;
				CBox* pBox2 = pLine;
				while (pBox2)
				{
					if (pBox2->m_children.GetSize() == 0)
					{
						pTextContent = (CTextContentBox*)pBox2;
						break;
					}

					pBox2 = pBox2->m_children[pBox2->m_children.GetSize()-1];
				}

				CComQIPtr<ILDOMText> text = pTextContent->m_node;
				BSTR bdata;
				text->get_data(&bdata);
				int blen = SysStringLen(bdata);
				SysFreeString(bdata);

				(*container = pTextContent->m_node)->AddRef();
				*offset = pTextContent->m_start + ((pTextContent->m_type == 11)? 0: ((CWordBox*)pTextContent)->m_text.length()-1);
				if (blen-1 == *offset) (*offset)++;

				return S_OK;
			}
		}
	}

	return S_FALSE;
}

HRESULT CPDTextSelection::MoveCursorUp(ILDOMNode *curContainer, long curOffset, ILDOMNode **container, long *offset)
{
	// TODO: Add your implementation code here

	return S_OK;
}

HRESULT CPDTextSelection::MoveCursorDown(ILDOMNode *curContainer, long curOffset, ILDOMNode **container, long *offset)
{
	CComPtr<IPDObjectText> objectText;
	m_story->GetObjectTextFromRangePosition(curContainer, curOffset, &objectText);

	CComQIPtr<IPDContentText> contentText = objectText;
	if (contentText)
	{
		CPDContentText* pContentText = static_cast<CPDContentText*>(contentText.p);

		CTextContentBox* pWord = (CTextContentBox*)pContentText->m_pBox->FindBox(curContainer, curOffset);
		if (pWord)
		{
			ATLASSERT(pWord->m_type == 10 || pWord->m_type == 11);

			Gdiplus::RectF rc = pWord->GetAbsInnerRect();
			double x = rc.X + pWord->GetCharOffset(curOffset - pWord->m_start);

			CLineBox* pLine = pWord->GetParentLineBox();
			if (pLine)
			{
				CLineBox* pNextLine = (CLineBox*)pLine->GetNextSibling();
				if (pNextLine)
				{
					ATLASSERT(pNextLine->m_type == 2);

					if (pNextLine->getPosUnderPoint(x, pNextLine->GetAbsInnerRect().Y, container, offset))
					{
						return S_OK;
					}
				}
				else
				{
					// Try in next text box
				}
			}
		}
	}

	return S_FALSE;
}

STDMETHODIMP CPDTextSelection::EndKey(long Unit, long Extend, long *pDelta)
{
	CComPtr<ILDOMNode> container;
	long offset;
	if (MoveCursorEnd(m_curContainer, m_curOffset, &container, &offset) == S_OK)
	{
		ExtendIt(container, offset, Extend);
	}

	return S_OK;
}

STDMETHODIMP CPDTextSelection::HomeKey(long Unit, long Extend, long *pDelta)
{
	CComPtr<ILDOMNode> container;
	long offset;
	if (MoveCursorHome(m_curContainer, m_curOffset, &container, &offset) == S_OK)
	{
		ExtendIt(container, offset, Extend);
	}

	return S_OK;
}

STDMETHODIMP CPDTextSelection::MoveRight(long Unit, long Count, long Extend, long *pDelta)
{
	CComPtr<ILDOMNode> container;
	long offset;
	if (MoveCursorRight(m_curContainer, m_curOffset, &container, &offset) == S_OK)
	{
		ExtendIt(container, offset, Extend);
	}

	return S_OK;
}

STDMETHODIMP CPDTextSelection::MoveLeft(long Unit, long Count, long Extend, long *pDelta)
{
	CComPtr<ILDOMNode> container;
	long offset;
	if (MoveCursorLeft(m_curContainer, m_curOffset, &container, &offset) == S_OK)
	{
		ExtendIt(container, offset, Extend);
	}

	return S_OK;
}

STDMETHODIMP CPDTextSelection::MoveUp(long Unit, long Count, long Extend, long *pDelta)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextSelection::MoveDown(long Unit, long Count, long Extend, long *pDelta)
{
	CComPtr<ILDOMNode> container;
	long offset;
	if (MoveCursorDown(m_curContainer, m_curOffset, &container, &offset) == S_OK)
	{
		ExtendIt(container, offset, Extend);
	}
	return S_OK;
}

STDMETHODIMP CPDTextSelection::Set(ILDOMNode *node, long offset)
{
	m_initContainer = node;
	m_initOffset = offset;

	m_curContainer = m_initContainer;
	m_curOffset = m_initOffset;

	m_domrange->setStart(m_initContainer, m_initOffset);
	m_domrange->setEnd(m_initContainer, m_initOffset);

	return S_OK;
}

STDMETHODIMP CPDTextSelection::MoveDOM(ILDOMNode *node, long offset)
{
	CComPtr<ILDOMNode> startContainer;
	long startOffset;

	CComPtr<ILDOMNode> endContainer;
	long endOffset;

	if (node == m_initContainer)	// start and end share container
	{
		startContainer = node;
		endContainer = node;

		if (offset < m_initOffset)
		{
			startOffset = offset;
			endOffset = m_initOffset;
		}
		else
		{
			startOffset = m_initOffset;
			endOffset = offset;
		}
	}
	else
	{
		int cmp = CompareTreePosition(node, m_initContainer);
		ATLASSERT(cmp != 0);

		if (cmp == -1)
		{
			startContainer = node;
			startOffset = offset;

			endContainer = m_initContainer;
			endOffset = m_initOffset;
		}
		else
		{
			startContainer = m_initContainer;
			startOffset = m_initOffset;

			endContainer = node;
			endOffset = offset;
		}
	}

	m_curContainer = node;
	m_curOffset = offset;

	m_domrange->setStart(startContainer, startOffset);
	m_domrange->setEnd(endContainer, endOffset);

	return S_OK;
}

STDMETHODIMP CPDTextSelection::TypeText(BSTR bstr)
{
	CComPtr<ILDOMNode> startContainer;
	long startOffset;
	m_domrange->get_startContainer(&startContainer);
	m_domrange->get_startOffset(&startOffset);

	CComQIPtr<ILDOMText> text = startContainer;
	if (text)
	{
		text->insertData(startOffset, bstr);

	//	CComPtr<ILDOMNode> container;
	//	long offset;

		MoveRight(tomCharacter, 1, 0, NULL);

		return S_OK;
	}

	return E_FAIL;
}
