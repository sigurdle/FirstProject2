#ifndef System_XPath_h
#define System_XPath_h

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#ifndef XPathExt
#define XPathExt DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace XDM
{

interface IData
{
	virtual IData* getParent() = 0;
	virtual unsigned int getPosition() = 0;

//	virtual System::StringW* getName() = 0;
//	virtual System::StringW* getNamespaceURI() = 0;

	virtual IData* getRoot() = 0;

	virtual unsigned int getAttributeCount() = 0;
	virtual System::Variant getAttributeValue(unsigned int index) = 0;
	virtual String getAttributeName(unsigned int index) = 0;
	virtual String getAttributeNamespaceURI(unsigned int index) = 0;
	virtual System::Type* getAttributeType(unsigned int index) = 0;

	virtual unsigned int getChildCount() = 0;
	virtual bool IsChildText(unsigned int index) = 0;
	virtual String getChildName(unsigned int index) = 0;
	virtual String getChildNamespaceURI(unsigned int index) = 0;
	virtual System::Type* getChildType(unsigned int index) = 0;
	virtual IData* getChildElement(unsigned int index) = 0;
	virtual String getChildText(unsigned int index) = 0;

	virtual Object* GetObject() = 0;
};

}	// XDM
}	// System

namespace System
{
namespace XPath
{

class XPathExpression;
class XPathResult;
class ExpList;
class AxisStep;
class StepList;

class XPathException : public SystemException
{
public:

	CTOR XPathException(StringIn reason) : SystemException(reason)
	{
	}
};

enum XPathResultType
{
	ANY_TYPE	= 0,
	NUMBER_TYPE	= 1,
	STRING_TYPE	= 2,
	BOOLEAN_TYPE	= 3,
	NODE_SET_TYPE	= 4,
	SINGLE_NODE_TYPE	= 5
};
   
    class ILXPathSetSnapshot
    {
    public:
        virtual /* [helpstring][propget] */ ErrorCode get_length( 
            /* [retval][out] */ long *pVal) = 0;
     
#if 0
        virtual /* [helpstring] */ ErrorCode item( 
            /* [in] */ long index,
            /* [retval][out] */ Web::Node **pVal) = 0;
#endif
    };
    

interface IXPathNSResolver
{
	virtual String lookupNamespaceURI(StringIn prefix) = 0;
};
    
    
    class ILXPathEvaluator
    {
    public:
#if 0
        virtual /* [helpstring][id] */ ErrorCode STDMETHODCALLTYPE createExpression( 
            /* [in] */ BSTR expression,
            /* [in] */ ILXPathNSResolver *resolver,
            /* [retval][out] */ ILXPathExpression **pVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode STDMETHODCALLTYPE createNSResolver( 
            /* [in] */ Node *nodeResolver,
            /* [retval][out] */ ILXPathNSResolver **pVal) = 0;
#endif   
    };

class XPathExt QName
{
public:
	CTOR QName(StringIn ns, StringIn local) :
		m_ns(ns),
		m_local(local)
	{
	}

	String m_ns;
	String m_local;
};

class XPathExt Exp : public Object
{
public:

	enum
	{
		K_PATH,
		K_BINOP,
		K_UNOP,
		K_NUMBER,
		K_CONTEXTITEM,
		K_FUNCALL,
		K_INSTANCEOF,
	}
	kind;

	CTOR Exp()
	{
	}

	double number;
};

class XPathExt PathExp : public Exp
{
public:
	CTOR PathExp(StepList* path);

	StepList* m_path;
};

class XPathExt BinopExp : public Exp
{
public:
	CTOR BinopExp(Exp* left, int op, Exp* right);

	Exp* m_left;
	Exp* m_right;
	int m_op;
};

class XPathExt UnopExp : public Exp
{
public:

	CTOR UnopExp(Exp* exp, int op);

	Exp* m_exp;
	int m_op;
};

class XPathExt ContextItemExp : public Exp
{
public:
	CTOR ContextItemExp()
	{
		kind = K_CONTEXTITEM;
	}
};

class XPathExt FunctionCallExp : public Exp
{
public:
	CTOR FunctionCallExp(QName* name, ExpList* args) : m_name(name), m_args(args)
	{
		kind = K_FUNCALL;
	}

	QName* m_name;
	ExpList* m_args;
};

class AxisContext
{
public:
};

class XPathExt NodeTest : public Object
{
public:
	/*
	CTOR NodeTest(QName* qname)
	{
		kind = K_NAMETEST;
		m_qname = qname;
	}

	CTOR NodeTest(QName* elementname, QName* _typename)
	{
		kind = K_ELEMENTTEST;
		ElementTest.m_elementname = elementname;
		ElementTest.m_typename = _typename;
	}
	*/

	enum
	{
		K_NAMETEST,
		K_ELEMENTTEST,
	}
	kind;

	union
	{
		QName* m_qname;

		struct
		{
			QName* m_elementname;
			QName* m_typename;
		}
		ElementTest;
	};
};

class XPathExt NameNodeTest : public NodeTest
{
public:
	CTOR NameNodeTest(QName* qname)
	{
		kind = K_NAMETEST;
		m_qname = qname;
	}
};

class XPathExt ElementNodeTest : public NodeTest
{
public:
	CTOR ElementNodeTest(QName* elementname, QName* _typename)
	{
		kind = K_ELEMENTTEST;
		ElementTest.m_elementname = elementname;
		ElementTest.m_typename = _typename;
	}
};

class XPathExt InstanceOfExp : public Exp
{
public:
	CTOR InstanceOfExp(Exp* exp, NodeTest* nodeTest)
	{
		kind = K_INSTANCEOF;
		m_exp = exp;
		m_nodeTest = nodeTest;
	}

	Exp* m_exp;
	NodeTest* m_nodeTest;
};

class XPathExt Step : public Object
{
public:
	enum Kind
	{
		Axis,
		Filter,
	};

	virtual Kind GetKind() = 0;

	ExpList* m_predicates;
};

class XPathExt AxisStep : public Step
{
public:

	virtual Kind GetKind()
	{
		return Axis;
	}

	enum AxisType
	{
		K_ANCESTOR,
		K_ANCESTOR_OR_SELF,
		K_ATTRIBUTE,
		K_CHILD,
		K_DESCENDANT,
		K_DESCENDANT_OR_SELF,
		K_FOLLOWING,
		K_FOLLOWING_SIBLING,
		K_NAMESPACE,
		K_PARENT,
		K_PRECEDING,
		K_PRECEDING_SIBLING,
		K_SELF,
	}
	m_axis;

	NodeTest* m_nodeTest;

	CTOR AxisStep(int axis, NodeTest* nodeTest, ExpList* predicates)
	{
		m_axis = (AxisType)axis;
		m_nodeTest = nodeTest;
		m_predicates = predicates;
	}
};

class XPathExt FilterStep : public Step
{
public:
	CTOR FilterStep(Exp* exp, ExpList* predicates)
	{
		m_exp = exp;
		m_predicates = predicates;
	}

	virtual Kind GetKind()
	{
		return Filter;
	}

	Exp* m_exp;
};

/*
class StepExpr
{
public:

	StepExpr(AxisStep* axisStep)
	{
		m_kind = Axis;
		m_axisStep = axisStep;
	}

	StepExpr(FilterStep* filterStep)
	{
		m_kind = Filter;
		m_filterStep = filterStep;
	}

	union
	{
		AxisStep* m_axisStep;
		FilterStep* m_filterStep;
	};
};
*/

class XPathExt StepList : public Object
{
public:
	CTOR StepList(Step* _head, StepList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	Step* head;
	StepList* tail;
};

/*
struct Predicate
{
	CTOR Predicate(Exp* exp)
	{
		exp = exp;
	}

	Exp* m_exp;
};
*/

class XPathExt ExpList : public Object
{
public:
	CTOR ExpList(Exp* _head, ExpList* _tail)
	{
		ASSERT(_head);

		head = _head;
		tail = _tail;
	}

	Exp* head;
	ExpList* tail;
};

class XPathExt DataItem
{
public:
	CTOR DataItem(XDM::IData* data, int attributeIndex = -1)
	{
		m_data = data;
		m_attributeIndex = attributeIndex;
	}

	String ToString();

	XDM::IData* m_data;
	int m_attributeIndex;
};

class XPathExt DataList : public Object
{
public:
	vector<DataItem> m_items;
};

class XPathExt AxisIterator
{
public:
	bool Iterate();
	bool AtEnd();

	int m_axis;
	int m_contextSize;
	int m_contextPos;
	XDM::IData* m_contextParentItem;
	XDM::IData* m_contextItem;

	DataItem GetItem();
};

class XPathExt ExprResult
{
public:
	enum
	{
		K_BOOL,
		K_INTEGER,
		K_NUMBER,
		K_STRING,
		K_NODELIST,
	}
	m_kind;

	CTOR ExprResult()
	{
	}

	CTOR ExprResult(DataList* nodelist)
	{
		m_kind = K_NODELIST;
		m_nodeList = nodelist;
	}

	CTOR ExprResult(bool value)
	{
		m_kind = K_BOOL;
		m_boolValue = value;
	}

	CTOR ExprResult(int value)
	{
		m_kind = K_INTEGER;
		m_intValue = value;
	}

	CTOR ExprResult(double value)
	{
		m_kind = K_NUMBER;
		m_numberValue = value;
	}

	CTOR ExprResult(String value)
	{
		m_kind = K_STRING;
		m_stringValue = value.m_stringObject;
	}

	CTOR ExprResult(StringIn value)
	{
		m_kind = K_STRING;
		m_stringValue = value._stringObject();
	}

	union
	{
		bool m_boolValue;
		int m_intValue;
		double m_numberValue;
	};

	union
	{
		DataList* m_nodeList;
		StringObject* m_stringValue;
	};
};

//Exp* PathExp(StepList* steps);
Exp* NumberExp(double number);

ExprResult* evaluate(Exp* exp, XDM::IData* contextNode, int contextPosition, int contextSize);

XPathExt bool xpath_boolean(ExprResult* obj);

}	// XPath
}	// System

#include "XPathExpression.h"
#include "XPathResult.h"
#include "XPathEvaluator.h"

#endif // System_XPath_h
