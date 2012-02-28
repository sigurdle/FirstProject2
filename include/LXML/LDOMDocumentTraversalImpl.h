#ifndef __LDOMDOCUMENTTRAVERSALIMPL_H
#define __LDOMDOCUMENTTRAVERSALIMPL_H

#include "NodeIterator.h"

namespace System
{
namespace Web
{

class CLDOMDocumentTraversalImplImpl //:	public IDocumentTraversal
{
public:
	vector<CLDOMNodeIterator*> m_iterators;
};

template<class T> class CLDOMDocumentTraversalImpl :
	public CLDOMDocumentTraversalImplImpl
{
public:
	INodeIterator* createNodeIterator(
										/*[in]*/ Node* root,
										/*[in]*/ FilterShow whatToShow,
										/*[in]*/ INodeFilter* filter,
										/*[in]*/ bool entityReferenceExpansion)
	{
		if (root == NULL) throw std::exception("Invalid argument");//return E_INVALIDARG;

		ASSERT(0);
		CLDOMNodeIterator* pIterator = NULL;//new CLDOMNodeIterator;

		pIterator->m_root = root;
		pIterator->m_filter = filter;
		pIterator->m_whatToShow = whatToShow;
		pIterator->m_expandEntityReferences = entityReferenceExpansion;

		pIterator->m_pDocumentTraversal = static_cast<T*>(this);
		m_iterators.Add(pIterator);

		return pIterator;
	}
};

}	// Web
}

#endif
