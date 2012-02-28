#ifndef __DOMIMPLEMENTATION_H_
#define __DOMIMPLEMENTATION_H_

//#include "resource.h"       // main symbols

#include "LXMLImpl.h"

namespace System
{
namespace Web
{

class Document;
class DocumentType;

class WEBEXT DOMImplementation : public System::Object
{
public:
	CTOR DOMImplementation();
	~DOMImplementation();

	Document* createDocument(StringIn namespaceURI, StringIn qualifiedName, DocumentType* doctype);
	DocumentType* createDocumentType(StringIn qualifiedName, StringIn publicId, StringIn systemId);
	ILSParser* createLSParser(short mode, StringIn schemaType);
	bool hasFeature(StringIn feature, StringIn version);

	static DOMImplementation* get_DOMImplementation();

public:

	static DOMImplementation* s_DOMImplementation;
	vector<IXMLImplementation*> m_implList;
};

}	// w3c
}

#endif // __DOMIMPLEMENTATION_H_
