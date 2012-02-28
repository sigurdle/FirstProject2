#ifndef __DOMPARSER_H
#define __DOMPARSER_H

#include "DocumentParser.h"

#if 0

namespace LXML
{

class Node;
class Element;
class Attr;
class Document;
class Comment;
class Text;
class CDATASection;
class DocumentType;
class ProcessingInstruction;
class NamedNodeMap;
class CLDOMError;

class WEBEXT CDOMParser : public DocumentParser
{
public:
	CTOR CDOMParser();

	System::StringW* m_uri;
#if 0
	ITextData* m_textDoc;
#endif
	Document* m_document;

#if 0
	ILHTMLActiveDocument* m_activeDocument;
#endif

	ILDOMErrorHandler* m_errorHandler;

//	bool m_editMode;

//

	HRESULT loadXML2();

//	bool load(IGetByte* stream);

	System::StringW* GetID();
	void GetNSID(System::StringW* &ns, System::StringW* &id);
	double GetNumber();
	System::StringW* GetAttrValue();
	System::StringW* GetString();
	void GetAttrValue(Attr* attr);
	void SkipSpaces();
	void CollectSpaces(System::StringBuilderW& spaces);
	void EatChar(int c);
	int NextChar();

//	void elementDone(Element* element);

	bool handleError(CLDOMError* error);

	long ParseXMLHeader();
	DocumentType* ParseDOCTYPE();
	CDATASection* ParseCDATASection();
	Comment* ParseCommentNode();
	ProcessingInstruction* ParseProcessingInstruction();
	void ParseText(Node* parentNode, System::StringW* & data);

//	Element* ParseElement(Node* parentNode, Node* nsResolverParent, int parentXmlSpacePreserve);
//	bool ParseChildren(Node* parentNode, Node* nsResolverParent, int xmlSpacePreserve);

	ILDOMLocator* getcnexturrentLocation();

	void ParseAttributes(Node* parent, NamedNodeMap* attributes);

// Schema stuff
//	BOOL ValidateElement(IDOMElement *schemaElement, IDOMElement* element);
//	BOOL validateToSchema(IDOMElement* schemaElement);

	bool loadXML(System::StringW* sourceText);
	bool load(System::StringW* xmlSource);
	bool load(System::IO::ISequentialByteStream* stream);
	bool validateToSchema(/*[in]*/ Document* schemaDoc);
	STDMETHOD(get_errorHandler)(/*[out, retval]*/ ILDOMErrorHandler* *pVal);
	STDMETHOD(put_errorHandler)(/*[in]*/ ILDOMErrorHandler* newVal);
	bool parse();
//	STDMETHOD(get_sourceTextDoc)(/*[out, retval]*/ ITextData* *pVal);
//	STDMETHOD(set_sourceTextDoc)(/*[in]*/ ITextData* newVal);
	Document* get_document() const;
	void set_document(Document* newVal);
};

}	// LXML

#endif

#endif	// __DOMPARSER_H
