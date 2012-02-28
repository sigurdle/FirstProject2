#ifndef XPathExpression_h
#define XPathExpression_h

namespace System
{
namespace XPath
{

class XPathExt XPathExpression : public Object
{
public:
	CTOR XPathExpression()
	{
		m_exp = NULL;
	}

	XPathResult* evaluate(XDM::IData* contextNode);
	XPathResult* evaluate(XDM::IData* contextNode, XPathResultType type, XPathResult* result);
	bool evaluateContaining(XDM::IData* contextNode);

public:

	Exp* m_exp;
};

}	// XPath
}

#endif	// __XPATHEXPRESSION_H_
