#ifndef __XMLPARSER_H
#define __XMLPARSER_H

#include "DocumentParser.h"

namespace System
{
namespace Web
{

	class CDATASection;
class DOMError;

class WEBEXT XMLParser : public SAX::DefaultHandler
{
public:
	CTOR XMLParser();

	String m_uri;
#if 0
	ITextData* m_textDoc;
#endif
	Document* m_document;

#if 0
	ILHTMLActiveDocument* m_activeDocument;
#endif

	IDOMErrorHandler* m_errorHandler;

//	bool m_editMode;

//

	ErrorCode loadXML2();

	String GetID();
	void GetNSID(String& ns, String& id);
	double GetNumber();
	String GetAttrValue();
	String GetString();
	void GetAttrValue(Attr* attr);
	void SkipSpaces();
	void CollectSpaces(String& spaces);
	void EatChar(int c);
	int NextChar();

	void elementDone(Element* element);

	bool handleError(DOMError* error)
	{
		if (m_errorHandler)
		{
			bool bContinue = false;
			ASSERT(0);
		//	m_errorHandler->handleError(error, &bContinue);
			return bContinue;
		}
		return false;
	}

	long ParseXMLHeader();
	DocumentType* ParseDOCTYPE();
	CDATASection* ParseCDATASection();
	Comment* ParseCommentNode();
	ProcessingInstruction* ParseProcessingInstruction();
	void ParseText(Node* parentNode, String& data);

	Element* ParseElement(Node* parentNode, Node* nsResolverParent, int parentXmlSpacePreserve);
	bool ParseChildren(Node* parentNode, Node* nsResolverParent, int xmlSpacePreserve);

	IDOMLocator* getcnexturrentLocation();

	void ParseAttributes(Node* parent, NamedNodeMap* attributes);

// Schema stuff
//	BOOL ValidateElement(IDOMElement *schemaElement, IDOMElement* element);
//	BOOL validateToSchema(IDOMElement* schemaElement);

	bool loadXML(StringIn sourceText);
	bool load(StringIn xmlSource);
	bool load(IO::Stream* stream);
//	bool load(IGetByte* stream);
	bool validateToSchema(/*[in]*/ Document* schemaDoc);
	IDOMErrorHandler* get_errorHandler();
	void set_errorHandler(IDOMErrorHandler* newVal);
	bool parse();
//	STDMETHOD(get_sourceTextDoc)(/*[out, retval]*/ ITextData* *pVal);
//	STDMETHOD(set_sourceTextDoc)(/*[in]*/ ITextData* newVal);
	Document* get_document() const;
	void set_document(Document* newVal);
};

#if 0

class WEBEXT XMLParser : public SAX::DefaultHandler
{
public:
	CTOR XMLParser();

	String m_uri;
#if 0
	ITextData* m_textDoc;
#endif
	Document* m_document;

#if 0
	ILHTMLActiveDocument* m_activeDocument;
#endif

	IDOMErrorHandler* m_errorHandler;

//	bool m_editMode;

//

	ErrorCode loadXML2();

	String GetID();
	void GetNSID(String& ns, String& id);
	double GetNumber();
	String GetAttrValue();
	String GetString();
	void GetAttrValue(Attr* attr);
	void SkipSpaces();
	void CollectSpaces(String& spaces);
	void EatChar(int c);
	int NextChar();

	void elementDone(Element* element);

	bool handleError(DOMError* error)
	{
		if (m_errorHandler)
		{
			bool bContinue = false;
			ASSERT(0);
		//	m_errorHandler->handleError(error, &bContinue);
			return bContinue;
		}
		return false;
	}

	long ParseXMLHeader();
	DocumentType* ParseDOCTYPE();
	CDATASection* ParseCDATASection();
	Comment* ParseCommentNode();
	ProcessingInstruction* ParseProcessingInstruction();
	void ParseText(Node* parentNode, String& data);

	Element* ParseElement(Node* parentNode, Node* nsResolverParent, int parentXmlSpacePreserve);
	bool ParseChildren(Node* parentNode, Node* nsResolverParent, int xmlSpacePreserve);

	IDOMLocator* getcnexturrentLocation();

	void ParseAttributes(Node* parent, NamedNodeMap* attributes);

// Schema stuff
//	BOOL ValidateElement(IDOMElement *schemaElement, IDOMElement* element);
//	BOOL validateToSchema(IDOMElement* schemaElement);

	bool loadXML(StringIn sourceText);
	bool load(StringIn xmlSource);
	bool load(Stream& stream);
//	bool load(IGetByte* stream);
	bool validateToSchema(/*[in]*/ Document* schemaDoc);
	IDOMErrorHandler* get_errorHandler();
	void set_errorHandler(IDOMErrorHandler* newVal);
	bool parse();
//	STDMETHOD(get_sourceTextDoc)(/*[out, retval]*/ ITextData* *pVal);
//	STDMETHOD(set_sourceTextDoc)(/*[in]*/ ITextData* newVal);
	Document* get_document() const;
	void set_document(Document* newVal);
};
#endif

}	// Web
}

#endif	// __DOMPARSER_H
