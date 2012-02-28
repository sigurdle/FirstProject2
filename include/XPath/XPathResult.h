#ifndef __XPATHRESULT_H_
#define __XPATHRESULT_H_

//#include "XPath.h"

namespace System
{
namespace XPath
{

class CXPathSetSnapshot;

class XPathExt XPathResult : public Object
{
public:
	CTOR XPathResult()
	{
#if 0
		type = ANY_TYPE;
		nodesetval = NULL;
		boolval = 0;
		floatval = 0;
		stringval = NULL;
		user = NULL;
		index = 0;
		user2 = NULL;
		index2 = 0;
#endif
		m_result = NULL;
	}

	virtual String ToString() override;

	ExprResult* m_result;
	
#if 0
	LXPathResultType type;
//	_xmlNodeSet* nodesetval;
	CComObject<CXPathSetSnapshot>* nodesetval;
	int boolval;
	double floatval;
	unsigned char /*xmlChar*/ *stringval;
	void *user;
	int index;
	void *user2;
	int index2;
#endif

public:
#if 0
	STDMETHOD(get_resultType)(LXPathResultType *pVal);
	STDMETHOD(get_numberValue)(double *pVal);
	STDMETHOD(get_stringValue)(BSTR *pVal);
	STDMETHOD(get_booleanValue)(bool *pVal);
	STDMETHOD(get_singleNodeValue)(ILDOMNode* *pVal);
//	STDMETHOD(getSetSnapshot)(bool ordered, IXPathSetSnapshot** pVal);

	STDMETHOD(get_snapshotLength)(/*[out, retval]*/ long *pVal);
	STDMETHOD(snapshotItem)(/*[in]*/ long index, /*[out,retval]*/ ILDOMNode** pVal);
#endif
};

}	// XPath
}

#endif // __XPATHRESULT_H_
