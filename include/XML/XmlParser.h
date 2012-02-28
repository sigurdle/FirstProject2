#pragma once

namespace System
{


namespace XmlData
{

class IDOMErrorHandler
{
};

class IDOMLocator
{
};

class DOMError;

class XMLParser
{
public:
	XMLParser();

	inline bool eof()
	{
		return m_stream->state() & 1;
//		return m_stream.eof();
	//	return !(m_fpos < m_textLen);
	}

	void getcnext();

	long loadXML2();

	String GetID();
	void GetNSID(String& ns, String& id);
	double GetNumber();
//	String GetAttrValue();
	String GetString();
	void GetAttrValue(Attr* attr);
	void SkipSpaces();
	void CollectSpaces(IO::StringWriter& spaces);
	void EatChar(int c);
	int NextChar();

	void elementDone(Element* element);

	bool handleError(DOMError* error);

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

	bool load(IO::TextReader* reader);
	bool load(IO::Stream* source);
	bool load(StringIn url);
	bool loadXML(StringIn sourceText);

	bool validateToSchema(/*[in]*/ Document* schemaDoc);
	bool parse();
	Document* get_document() const;

	bool m_utf8;

	WCHAR m_c;

	long m_fpos;
	long m_line;
	long m_column;
	int m_oldc;
	//bool m_bXML;

	_Ptr<IO::TextReader> m_stream;
	String m_uri;
	Document* m_document;
	IDOMErrorHandler* m_errorHandler;
};

}	// XmlData
}	// System
