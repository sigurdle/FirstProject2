#ifndef XSLT_h
#define XSLT_h

#ifndef XSLTEXT
#define XSLTEXT DECLSPEC_DLLIMPORT
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/XPath.typeinfo"
#else
#include "XPath/XPath.h"
#endif

// TODO, not this here
#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LXML.typeinfo"
#else
#include "LXML/LXML.h"
#endif

namespace System
{
namespace XSLT
{

class Context
{
public:
	XDM::IData* contextItem;
	int pos;
	int size;
};

class SequenceItem
{
public:

	CTOR SequenceItem(Web::Node* node)// : m_dataitem(NULL)
	{
		m_node = node;
	}

	/*
	SequenceItem(Web::DataItem& dataitem) : m_dataitem(dataitem)
	{
		m_node = NULL;
	}
	*/

	Web::Node* m_node;
//	Web::DataItem m_dataitem;
	double atomic;
};

class Sequence
{
public:
	vector<SequenceItem*> m_items;
};

class Template
{
public:
	Web::Element* m_element;
	XPath::XPathExpression* m_matchExp;
};

class XSLTEXT Document : public Object
{
public:

	CTOR Document(Web::Document* xsltDocument);

	Sequence* evaluate(Web::Document* resultDocument, Web::Element* templateRule, XDM::IData* contextNode);
	Web::Element* evaluateLiteral(Web::Document* resultDocument, Web::Element* literalElement, XDM::IData* contextNode);
	String SimpleContent(Web::Document* resultDocument, Web::Element* childelement, XDM::IData* contextNode);
	Web::DocumentFragment* transform(Web::Document* resultDocument, Web::Element* templateRule, XDM::IData* contextNode);

public:

	Web::Document* m_xsltDocument;

	vector<Template*> m_templates;
};

}	// XSLT
}	// System

#endif	// XSLT_h
