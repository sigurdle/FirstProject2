#include "stdafx.h"
//#include "LXML.h"
#include "LXML2.h"

#include "AnimationTarget.h"

#if 0
#include "PSVGElement.h"
#endif

#include "NodeList.h"

#include "Window.h"

namespace System
{
namespace Web
{

NodeList* AnimationTarget::get_animationElements()
{
// TODO, use CLDOMNodeList internally instead of CUPtrList
	NodeList* pNodeList = new NodeList;

	ASSERT(0);
#if 0

	UPOSITION pos = m_animationList.GetHeadPosition();
	while (pos)
	{
		AnimationElementImplImpl* pAnimation = (AnimationElementImplImpl*)m_animationList.GetNext(pos);

		ASSERT(0);
#if 0
		Node* node = dynamic_cast<Node*>(pAnimation);
		pNodeList->m_items.push_back(node);
#endif
	}
#endif
	return pNodeList;
}

}	// Web
}
