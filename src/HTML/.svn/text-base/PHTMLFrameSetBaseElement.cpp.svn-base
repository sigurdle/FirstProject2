#include "stdafx.h"
#include "HTML2.h"

#include "PHTMLFrameSetBaseElement.h"

namespace System
{
namespace Web
{

CHTMFrameNode::CHTMFrameNode(HTMLElement* element) : PHTMLElement(element)
{
	m_frameType = -1;
	//	m_pDocument = 0;
#if 0	//  Test without
	m_pParentFrame = NULL;
#endif
	m_pParentFrameSet = NULL;
	m_pParentWindow = NULL;
//	m_pUI = NULL;
}

CHTMFrameNode::~CHTMFrameNode()
{
}

#if 0 // Try without this
CHTMFrame* CHTMFrameNode::GetTopFrame()
{
	CHTMFrameNode* pFrame = this;

	while (pFrame->m_pParentFrame)
	{
		pFrame = pFrame->m_pParentFrame;
	}

	ASSERT(pFrame->m_type == 1);
	return (CHTMFrame*)pFrame;
}
#endif

}	// Web
}
