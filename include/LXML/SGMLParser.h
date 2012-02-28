#ifndef __SGMLPARSER_H
#define __SGMLPARSER_H

#include "DocumentParser.h"

namespace Web
{
namespace Web
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

/////////////////////////////////////////////////////////////////////////////
// SGMLParser
class WEBEXT SGMLParser : public DocumentParser
{
public:
	CTOR SGMLParser();

	String m_uri;
#if 0
	ITextData* m_textDoc;
#endif
	Document* m_document;

	ILDOMErrorHandler* m_errorHandler;

//	bool m_editMode;

	HRESULT loadXML2();

	String GetID();
	void GetNSID(String& ns, String& id);
	double GetNumber();
	sysstring GetAttrValue();
	sysstring GetString();
	void GetAttrValue(Attr* attr);
	void SkipSpaces();
	void CollectSpaces(sysstring& spaces);
	void EatChar(int c);
	int NextChar();

	void elementDone(Element* element);

	bool handleError(CLDOMError* error)
	{
		if (m_errorHandler)
		{
			bool bContinue;
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
	void ParseText(Node* parentNode, sysstring& data);

	Element* ParseElement(Node* parentNode, Node* nsResolverParent, int parentXmlSpacePreserve);
	bool ParseChildren(Node* parentNode, Node* nsResolverParent, int xmlSpacePreserve);

	ILDOMLocator* getcnexturrentLocation();

	void ParseAttributes(Node* parent, NamedNodeMap* attributes);

// Schema stuff
//	BOOL ValidateElement(IDOMElement *schemaElement, IDOMElement* element);
//	BOOL validateToSchema(IDOMElement* schemaElement);

	bool loadXML(const sysstring& sourceText);
	bool load(const sysstring& xmlSource);
#if 0//_WINDOWS
	bool load(IStream* xmlSource);
#endif
	bool validateToSchema(/*[in]*/ Document* schemaDoc);
#if 0
	STDMETHOD(get_editMode)(/*[out, retval]*/ bool *pVal);
	STDMETHOD(set_editMode)(/*[in]*/ bool newVal);
#endif
	STDMETHOD(get_errorHandler)(/*[out, retval]*/ ILDOMErrorHandler* *pVal);
	STDMETHOD(set_errorHandler)(/*[in]*/ ILDOMErrorHandler* newVal);
	bool parse();
//	STDMETHOD(get_sourceTextDoc)(/*[out, retval]*/ ITextData* *pVal);
//	STDMETHOD(set_sourceTextDoc)(/*[in]*/ ITextData* newVal);
	Document* get_document() const;
	void set_document(Document* newVal);
};

}	// LXML
}

#endif	// __DOMPARSER_H
