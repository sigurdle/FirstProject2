namespace System
{
namespace SAX
{

class Node;
class Attr;
class Element;
class Document;
class DOMError;
class DocumentType;
//class CDATASection;
//class ProcessingInstruction;
//class Comment;
class IDOMLocator;
class IDOMErrorHandler;

class XMLEXT SAXException : public Exception
{
public:

	CTOR SAXException(StringIn msg) : Exception(msg)
	{
	}
};

/*
	class QName
	{
	public:
		StringIn m_localName;
		StringIn m_qname;
	};
	*/

class XMLEXT Attr
{
public:
	StringIn m_prefix;
	StringIn m_localName;
	StringIn m_qname;

	StringIn m_value;
};

class XMLEXT Attributes : public Object
{
public:

	vector<Attr> m_items;
};

interface IContentHandler
{
	virtual void StartDocument() abstract;
	virtual void EndDocument() abstract;
	virtual void StartElement(StringIn uri, StringIn localName, StringIn qName, Attributes* attributes) abstract;
	virtual void EndElement(StringIn uri, StringIn localName, StringIn qName) abstract;
	virtual void StartPrefixMapping(StringIn prefix, StringIn Uri) abstract;
	virtual void EndPrefixMapping(StringIn prefix) abstract;
	virtual void _Text(StringIn str) abstract;
	virtual void _CDATASection(StringIn str) abstract;
	virtual void _Comment(StringIn str) abstract;
	virtual void _ProcessingInstruction(StringIn target, StringIn data) abstract;
};

class XMLEXT DefaultHandler : public Object, public IContentHandler
{
public:

	virtual void StartDocument() override
	{
	}

	virtual void EndDocument() override
	{
	}

	virtual void StartElement(StringIn uri, StringIn localName, StringIn qName, Attributes* attributes) override
	{
	}

	virtual void EndElement(StringIn uri, StringIn localName, StringIn qName) override
	{
	}

	virtual void StartPrefixMapping(StringIn prefix, StringIn Uri) override
	{
	}

	virtual void EndPrefixMapping(StringIn prefix) override
	{
	}

	virtual void _Text(StringIn str) override
	{
	}

	virtual void _CDATASection(StringIn str) override
	{
	}

	virtual void _Comment(StringIn str) override
	{
	}

	virtual void _ProcessingInstruction(StringIn target, StringIn data) override
	{
	}
};

class XMLEXT Parser : public Object
{
public:
	CTOR Parser();

	void set_ContentHandler(IContentHandler* handler);
	IContentHandler* get_ContentHandler();

	bool parse(IO::TextReader* reader);
	bool parse(IO::Stream* source);
	bool parse(StringIn url);
	bool parseXML(StringIn sourceText);

	Object* GetProperty(StringIn name);
	void SetProperty(StringIn name, Object* value);

protected:

	void getcnext();

	long loadXML2();

	String GetID();
	void GetNSID(String& ns, String& id);
	double GetNumber();
//	String GetAttrValue();
	String GetString();
	Attr GetAttrValue();
	void SkipSpaces();
	void CollectSpaces(IO::StringWriter& spaces);
	void EatChar(int c);
	int NextChar();

//	void elementDone(Element* element);

	bool handleError(DOMError* error);

	int ParseXMLHeader();
	DocumentType* ParseDOCTYPE();
	void ParseCDATASection();
	void ParseCommentNode();
	void ParseProcessingInstruction();
	void ParseText(Node* parentNode, String& data);
	void ParseElement(Node* parentNode, Node* nsResolverParent, int parentXmlSpacePreserve);
	bool ParseChildren(Node* parentNode, Node* nsResolverParent, int xmlSpacePreserve);

	IDOMLocator* getcnexturrentLocation();

	void ParseAttributes(Node* parent, Attributes* attributes);

//	bool validateToSchema(/*[in]*/ Document* schemaDoc);
//	bool parse();
	Document* get_document() const;

protected:

	inline bool eof()
	{
		return m_stream->state() & 1;
//		return m_stream.eof();
	//	return !(m_fpos < m_textLen);
	}

public:

	IContentHandler* m_handler;

	_Ptr<IO::TextReader> m_stream;
	String m_uri;
	Document* m_document;
	IDOMErrorHandler* m_errorHandler;

	map<String, String> m_prefixToUri;

	map<String, Object*> m_properties;

	size_t m_fpos;
	int m_line;
	int m_column;
	int m_oldc;
	WCHAR m_c;
	bool m_utf8;
};

}	// SAX
}	// System
