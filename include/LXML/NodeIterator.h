#ifndef __DOMNODEITERATOR_H__
#define __DOMNODEITERATOR_H__

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class CLDOMDocumentTraversalImplImpl;

class WEBEXT CLDOMNodeIterator : public Object, public INodeIterator
{
public:
	CTOR CLDOMNodeIterator();
	~CLDOMNodeIterator();

	void detach();
	Node* previousNode();
	Node* nextNode();
	bool get_expandEntityReferences();
	FilterShow get_whatToShow();
	INodeFilter* get_filter();
	Node* get_root();

public:

	Node* m_referenceNode;

	Node* m_root;
	INodeFilter* m_filter;
	FilterShow m_whatToShow;
	bool m_expandEntityReferences;

	CLDOMDocumentTraversalImplImpl* m_pDocumentTraversal;
};

}	// Web
}

#endif // __DOMNODEITERATOR_H__
