#ifndef __XPATHEVALUATOR_H_
#define __XPATHEVALUATOR_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace XPath
{
class XPathExpression;

class XPathExt XPathEvaluator
{
public:
	CTOR XPathEvaluator()
	{
	}

	virtual ~XPathEvaluator()
	{
	}

	XPathExpression* createExpression(StringIn expression, IXPathNSResolver* resolver);
#if 0
	STDMETHOD(createNSResolver)(ILDOMNode* nodeResolver, ILXPathNSResolver** pVal);
#endif
};

}	// XPath
}

#endif //__XPATHEVALUATOR_H_
