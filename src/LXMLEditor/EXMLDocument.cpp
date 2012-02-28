#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "EXMLDocument.h"

#include "EElement.h"
#include "ESVGSVGElement.h"
#include "ESVGEllipseElement.h"
#include "ESVGCircleElement.h"
#include "ESVGRectElement.h"
#include "ESVGTextElement.h"
#include "ESVGPathElement.h"
#include "ESVGLineElement.h"
#include "ESVGImageElement.h"
#include "ESVGVideoElement.h"
#include "ESVGForeignObjectElement.h"
#include "ESVGGElement.h"
#include "ESVGSwitchElement.h"
#include "ESVGFilterElement.h"
#include "ESVGLinearGradientElement.h"
#include "ESVGUseElement.h"
#include "ESVGSymbolElement.h"
#include "EAnimationElement.h"
#include "EScriptElement.h"
#include "EStyleElement.h"

#include "SourceView.h"
#include "XMLGridView.h"
#include "EXMLLayoutView.h"
#include "HTMLFramesDesignView.h"
#include "SMILRegionsView.h"
#include "SMILTimeGraphView.h"
//#include "WebPreviewView.h"
#include "XSLTTemplatesDlg.h"
//#include "SchemaDiagramView.h"	// TODO, remove, use DTDView instead
#include "DTDView.h"

#include "ScriptOutlineDlg.h"
#include "SVGObjectsDlg.h"
#include "CSSPropertiesDlg.h"
#include "SVGSwatchesDlg.h"
#include "SVGFiltersDlg.h"
#include "SVGSymbolsDlg.h"
#include "SVGClipPathsDlg.h"
#include "SMILTransitionsDlg.h"
#include "EXMLDocumentStyleSheetsView.h"
#include "TestAttributesDlg.h"
#include "ElementTimeDlg.h"
#include "AnimateAttributesDlg.h"
#include "EditGradientDlg.h"
#include "EditFilterDlg.h"
#include "EColorDlg.h"
/////////////

#include "X3DView.h"
#include "SceneGraphDlg.h"

/////

#include "LXMLEditorApp.h"
#include "SVGBehavior.h"
#include "EXMLViewGroup.h"
#include "ESVGPolyElement.h"

#include "WEUndoNewElement.h"
#include "XPathQueryDlg.h"

#include "AssignXSLDlg.h"

#include "../LHTML/HTMLDocument.h"

#define XMLGRIDEXT DECLSPEC_DLLIMPORT
#include "../XMLEditCtls/XMLGridCtl.h"
#include "../XMLEditCtls/XMLGridDocument.h"
#ifdef _DEBUG
#pragma comment(lib, "../XMLEditCtls/Debug/XMLEditCtls.lib")
#else
#pragma comment(lib, "../XMLEditCtls/ReleaseMinSize/XMLEditCtls.lib")
#endif

#include "../LXUI/http.h"
#include "../LXUI/TextDocument.h"

#include "../LXML/ScriptSite.h"
//#include "../LXML/DocumentStyleImpl.h"

/*
#include "../LXML/LBoxWindow.h"
#include "../LXML/DOMLocator.h"
*/

#include "../LXML/DTDParser.h"
#include "../LXML/DTDDocument.h"
#include "../LXML/ASDTDModel.h"

namespace System
{
namespace LXmlEdit
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
class DOMError;

class XMLParser
{
public:
	XMLParser();

	bool m_utf8;

	long m_fpos;
	long m_line;
	long m_column;
	int m_oldc;
	//bool m_bXML;

// Retrieved from TextData
	long m_textLen;
	const OLECHAR* m_textData;

	inline bool eof()
	{
		return !(m_fpos < m_textLen);
	}

	int getcnext()
	{
		if (m_fpos < m_textLen)
		{
			int c = m_textData[m_fpos++];

			if (m_utf8)
			{
				if (c & 80)	// high bit set
				{
				}
			}

			if (c == '\n')
			{
				m_line++;
				m_column = 0;
			}
			else
				m_column++;

			m_oldc = c;
			return c;
		}
		else
		{
			ASSERT(0);
			throw WSTR("EOF");
			return EOF;
		}
	}

	void ungetcnext()
	{
	// TODO
		if (m_oldc == '\n') m_line--;
		m_fpos--;
	}

	System::StringW* m_uri;
#if 0
	ITextData* m_textDoc;
#endif
	CEXMLDocument* m_document;

#if 0
	ILHTMLActiveDocument* m_activeDocument;
#endif

	Web::IDOMErrorHandler* m_errorHandler;

	bool m_editMode;

//

	ErrorCode loadXML2();


	System::StringW* GetID();
	void GetNSID(System::StringW*& ns, System::StringW*& id);
	double GetNumber();
	System::StringW* GetAttrValue();
	System::StringW* GetString();
	void GetAttrValue(Attr* attr);
	void SkipSpaces();
	void CollectSpaces(System::StringBuilderW& spaces);
	void EatChar(int c);
	int NextChar();

	void elementDone(Element* element);

	bool handleError(DOMError* error)
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
	void ParseText(Node* parentNode, System::StringW*& data);

	Element* ParseElement(Node* parentNode, Node* nsResolverParent, int parentXmlSpacePreserve);
	bool ParseChildren(Node* parentNode, Node* nsResolverParent, int xmlSpacePreserve);

	Web::IDOMLocator* getcnexturrentLocation();

	void ParseAttributes(Node* parent, NamedNodeMap* attributes);

// Schema stuff
//	BOOL ValidateElement(IDOMElement *schemaElement, IDOMElement* element);
//	BOOL validateToSchema(IDOMElement* schemaElement);

	bool loadXML(System::StringW* sourceText);
	bool load(System::StringW* xmlSource);
#if 0//_WINDOWS
	bool load(IStream* xmlSource);
#endif
	bool validateToSchema(/*[in]*/ Document* schemaDoc);
	ErrorCode get_errorHandler(/*[out, retval]*/ Web::IDOMErrorHandler* *pVal);
	ErrorCode put_errorHandler(/*[in]*/ Web::IDOMErrorHandler* newVal);
	bool parse();
//	ErrorCode(get_sourceTextDoc)(/*[out, retval]*/ ITextData* *pVal);
//	ErrorCode(put_sourceTextDoc)(/*[in]*/ ITextData* newVal);
	CEXMLDocument* get_document() const;
	void put_document(CEXMLDocument* newVal);
};

// This version assumes c is a legal hex digit
int Hex2Number(OLECHAR c)
{
	ASSERT(iswxdigit(c));

	if (c <= L'9')
		return c - L'0';
	else
		return 10 + towlower(c) - L'a';
}

int strhex2int(const OLECHAR* p)
{
	int v = 0;
	while (*p)
	{
		v <<= 4;

		int n = Hex2Number(*p);
		v += n;

		p++;
	}

	return v;
}

OLECHAR GetUCode(const OLECHAR* ucode)
{
/*
				else if (!wcscmp(name, OLESTR("copy")))	// TODO ??? don't replace
				{
					str += L'©';
				}
				else if (!wcscmp(name, OLESTR("oslash")))	// TODO ??? don't replace
				{
					str += L'ø';
				}
				else if (!wcscmp(name, OLESTR("aring")))	// TODO ??? don't replace
				{
					str += L'å';
				}
*/

	if (!wcscmp(ucode, L"amp"))
		return '&';
	else if (!wcscmp(ucode, L"lt"))
		return '<';
	else if (!wcscmp(ucode, L"gt"))
		return '>';
	else if (!wcscmp(ucode, L"quot"))
		return '"';
	else if (!wcscmp(ucode, L"apos"))
		return '\'';
	else if (ucode[0] == L'#')
	{
		if (ucode[1] == L'x')
			return strhex2int(&ucode[2]);
		else
			return (OLECHAR)str2int(&ucode[1]);	// decimal
	}

	return 0;
}

class DOMError : public Object
{
public:
	System::StringW* m_message;
	Web::IDOMLocator* m_location;
	Web::DOMErrorSeverity m_severity;
};

DOMError* CreateDOMError(Web::DOMErrorSeverity severity, System::StringW* message, Web::IDOMLocator* location)
{
	DOMError* p = new DOMError;
	if (p)
	{
		p->m_severity = severity;
		p->m_message = message;
		p->m_location = location;
	}

	return p;
}

/////////////////////////////////////////////////////////////////////////////
// XMLParser

XMLParser::XMLParser()
{
#if 0
	m_activeDocument = NULL;
#endif
	m_errorHandler = NULL;
	m_editMode = false;

	m_textLen = 0L;
	m_textData = NULL;

	m_fpos = 0;
	m_line = 0;
	m_column = 0;
	m_oldc = EOF;

	m_utf8 = false;
}

void XMLParser::CollectSpaces(System::StringBuilderW& spaces)
{
	while (!eof())
	{
		int c = getcnext();

		if (!iswspace(c))
		{
			ungetcnext();
			break;
		}

		spaces << (WCHAR)c;
	}
}

System::StringW* XMLParser::GetID()
{
	BufferImp<WCHAR> buffer;
	StringBuilderW stream(&buffer);

	while (!eof())
	{
		WCHAR c = getcnext();

		if (!(iswalnum(c) || c == L':' || c == L'.' || c == L'-' || c == L'_'))
		{
			ungetcnext();
			break;
		}

		stream << c;
	}

	StringW* str = buffer.DetachToString();

	if (str->Length() == 0)
	{
		StringW* msg = WSTR("Expected ident");
		handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
		THROW(msg);
	}

	return str;
}

void XMLParser::GetNSID(System::StringW*& ns, System::StringW*& id)
{
	ns = NULL;
	id = NULL;

	BufferImp<WCHAR> buffer;
	StringBuilderW str(&buffer);

	while (!eof())
	{
		WCHAR c = getcnext();
		if (!(iswalnum(c) || c == ':' || c == '.' || c == '-' || c == '_'))
		{
			ungetcnext();
			break;
		}

		if (c == L':')
		{
			ns = buffer.DetachToString();
			//str.clear();// = WSTR("");
		}
		else
		{
			/*str =*/ str.Append(c);
		}
	}

	id = buffer.DetachToString();
}

System::StringW* XMLParser::GetString()
{
	ASSERT(0);
	return NULL;
#if 0

	SkipSpaces();

	int delimiter = getcnext();

	if (delimiter != L'\"' && delimiter != L'\'')
	{
		OLECHAR msg[64];
		swprintf(msg, OLESTR("Expected \" or ' at offset %d"), m_fpos);

		handleError(CreateDOMError(Web::LSEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
		throw msg;
	}

	sysstring str = OLESTR("");
	OLECHAR c;

	while (!eof())
	{
		c = getcnext();
		if (c == delimiter)
		{
			ungetcnext();
			break;
		}

		str += c;
	}

	EatChar(delimiter);
	SkipSpaces();

	return str;
#endif
}

void XMLParser::GetAttrValue(Attr* attr)
{
	DocumentType* doctype = m_document->get_doctype();

#if 0
	NamedNodeMap* entities = NULL;
	if (doctype)
	{
		entities = doctype->get_entities();
	}
#endif

//	SkipSpaces();

	int delimiter = getcnext();

	if (delimiter != L'\"' && delimiter != L'\'')
	{
		delimiter = 0;
		ungetcnext();
	}

	attr->setTextOffset(3, m_fpos);

	if (true)
	{
		if (delimiter == 0)
		{
			WCHAR msg[64];
			swprintf(msg, L"Expected \" or '");

			handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new System::StringW(string_copy(msg)), getcnexturrentLocation()));
			throw msg;
		}
	}

	WCHAR c;

	BufferImp<WCHAR> buffer;
	StringBuilderW strbuilder(&buffer);

	while (!eof())
	{
		c = getcnext();

		if (delimiter == 0)
		{
			if (iswspace(c) || c == L'>')
			{
				ungetcnext();
				break;
			}
		}
		else
		{
			if (c == delimiter)
			{
				ungetcnext();
				break;
			}
		}

		if (c == L'&')
		{
			ASSERT(0);
#if 0
			sysstring name = OLESTR("");

			bool bNumber = false;
			int c = getcnext();
			if (c == '#')
			{
				bNumber = true;
			}
			else
				ungetcnext();

			while (!eof())
			{
				c = getcnext();

				if (!iswalnum(c) && c != L'_') break;
				//if (c == L' ' || c == L'\t' || c == L'\n' || c == L'\r') break;
				//if (c == L'<') break;

				if (c == L';')
				{
				//	ungetcnext();
					break;
				}

				name += c;
			}

			if (c == L';')
			{
				uint16 uc;

				if (bNumber)
					uc = str2int(name.c_str());
				else
					uc = GetUCode(name.c_str());

				if (uc)
				{
					str += uc;
				}
				else
				{
					ASSERT(0);
#if 0
					if (entities)
					{
						if (TRUE)	// Use entity references
						{
							if (str.length())	// Create a text node for collected characters
							{
								Text* textNode = m_document->createTextNode(str.c_str());
								attr->appendChild(textNode);

								str = OLESTR("");
							}

							EntityReference* entityReference = m_document->createEntityReference(name.c_str());

							attr->appendChild(entityReference);
						}
						else
						{
							Node* entity = entities->getNamedItem(name.c_str());
							if (entity)
							{
								Entity* pEntity = dynamic_cast<Entity*>(entity);

								str += pEntity->m_value;
							}
							else
							{
								OLECHAR msg[256];
								swprintf(msg, OLESTR("Undeclared entity '%s'"), name.c_str());

								handleError(CreateDOMError(LSEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
								throw msg;
							}
						}
					}
#endif
				}
			}
			else
			{
				str += L'&';
				str += name;
				str += c;
			}
#endif
		}
		else
		{
			strbuilder << c;
		}
	}

	StringW* str = buffer.DetachToString();

	if (str->Length())	// Create a text node for collected characters
	{
		Text* textNode = m_document->createTextNode(str);
		attr->appendChild(textNode);

		str = NULL;
	}

//	attr->put_value(str);

	attr->setTextOffset(4, m_fpos);

	if (delimiter) EatChar(delimiter);
//	SkipSpaces();
}

void XMLParser::SkipSpaces()
{
	while (!eof())
	{
		int c = getcnext();

		if (!iswspace(c))
		{
			ungetcnext();
			break;
		}
	}
}

void XMLParser::EatChar(int c)
{
	int c2 = getcnext();
	if (c2 != c)
	{
		static WCHAR msg[64];
		swprintf(msg, L"Expected %c", c);

		handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new System::StringW(string_copy(msg)), getcnexturrentLocation()));
		throw msg;
	}
}

ProcessingInstruction* XMLParser::ParseProcessingInstruction()
{
	ASSERT(0);
	return NULL;
#if 0

// <? has been read

	int fpos0 = m_fpos;

	sysstring target = GetID();

	int fpos1 = m_fpos;

	SkipSpaces();

	int fpos2 = m_fpos;

	sysstring data;

	int c;

	while (!eof())
	{
		c = getcnext();
		if (c == L'?')
		{
			ungetcnext();
			break;
		}

		if (m_document)
		{
			data += c;
		}
	}

	int fpos3 = m_fpos;

	EatChar('?');
	EatChar('>');

	if (m_document)
	{
		ProcessingInstruction* pi = m_document->createProcessingInstruction(target.c_str(), data.c_str());
		if (pi)
		{
			pi->setTextOffset(0, fpos0-2);
			pi->setTextOffset(1, fpos0);	// start target
			pi->setTextOffset(2, fpos1);	// end of target

			pi->setTextOffset(3, fpos2);	// start of data
			pi->setTextOffset(4, fpos2);
			pi->setTextOffset(5, fpos3);
			pi->setTextOffset(6, fpos3);	// end of data

			pi->setTextOffset(7, m_fpos-2);
			pi->setTextOffset(8, m_fpos);		// after ?>

			pi->setTextOffset(9, m_fpos);	// TODO
		}

		return pi;
	}
	else
		return NULL;
#endif
}

Comment* XMLParser::ParseCommentNode()
{
	ASSERT(0);
	return NULL;
#if 0

	int offset1 = m_fpos;
	int offset2;

	sysstring data;

	int c;

	while (!eof())
	{
		offset2 = m_fpos;

		c = getcnext();
		if (c == L'-')
		{
			if (!eof())
			{
				int c2 = getcnext();
				if (c2 == L'-')
				{
					break;
				}
				ungetcnext();
			}
		}

		if (m_document)
		{
			data += c;
		}
	}

	EatChar('>');

	int offset3 = m_fpos;

	if (m_document)
	{
		Comment* comment = m_document->createComment(data.c_str());

		comment->setTextOffset(0, offset1-4);	// <!--

		comment->setTextOffset(1, offset1);
		comment->setTextOffset(2, offset1);

		comment->setTextOffset(3, offset2);
		comment->setTextOffset(4, offset2);

		comment->setTextOffset(5, offset3);
		comment->setTextOffset(6, offset3);
		comment->setTextOffset(7, offset3);
		comment->setTextOffset(8, offset3);
		comment->setTextOffset(9, offset3);

		return comment;
	}
	else
		return NULL;
#endif
}

void XMLParser::ParseText(Node* parentNode, System::StringW*& data)
{
	ASSERT(0);
#if 0

	int c;

	int startoffset = m_fpos-data.length();

	while (!eof())
	{
		c = getcnext();
		if (c == L'<')
		{
			ungetcnext();
			break;
		}

		if (c == '&')
		{
			sysstring t = OLESTR("");

			int c;
			while (!eof())
			{
				c = getcnext();
				if (c == ';') break;

				if (c == ' ' || c == '\t' || c == '\n' || c == '\r') break;
				if (c == '<') break;

				t += c;
			}

		// TODO?, should make sure there's a ';'

			uint16 uc = GetUCode(t.c_str());
			if (uc)
			{
				data += uc;
			}
			else
			{
				if (data.length())	// Create a text node for collected characters
				{
				// TODO: text Offsets
					Text* textNode = m_document->createTextNode(data.c_str());

					textNode->setTextOffset(0, startoffset);
					textNode->setTextOffset(1, startoffset);
					textNode->setTextOffset(2, startoffset);
					textNode->setTextOffset(3, startoffset+data.length());
					textNode->setTextOffset(4, startoffset+data.length());
					textNode->setTextOffset(5, startoffset+data.length());
					textNode->setTextOffset(6, startoffset+data.length());
					textNode->setTextOffset(7, startoffset+data.length());
					textNode->setTextOffset(8, startoffset+data.length());
					textNode->setTextOffset(9, startoffset+data.length());

					parentNode->appendChild(textNode);

					data = OLESTR("");
					startoffset = m_fpos;	// Reset for next text node
				}

				EntityReference* entityRef = m_document->createEntityReference(t.c_str());

				if (entityRef)
				{
					parentNode->appendChild(entityRef);
				}
			}
		}
		else
		{
			data += c;
		}
	}

	if (data.length())	// Create a text node for collected characters
	{
		Text* textNode = m_document->createTextNode(data.c_str());

		textNode->setTextOffset(0, startoffset);
		textNode->setTextOffset(1, startoffset);
		textNode->setTextOffset(2, startoffset);
		textNode->setTextOffset(3, startoffset+data.length());
		textNode->setTextOffset(4, startoffset+data.length());
		textNode->setTextOffset(5, startoffset+data.length());
		textNode->setTextOffset(6, startoffset+data.length());
		textNode->setTextOffset(7, startoffset+data.length());
		textNode->setTextOffset(8, startoffset+data.length());
		textNode->setTextOffset(9, startoffset+data.length());

		parentNode->appendChild(textNode);

		data = OLESTR("");
	}
#endif
}

CDATASection* XMLParser::ParseCDATASection()
{
	ASSERT(0);
	return NULL;
#if 0

	int offset0 = m_fpos-8;

	SkipSpaces();
	EatChar('[');
	SkipSpaces();

	sysstring data;

	int offset1 = m_fpos;

	while (!eof())
	{
		int startpos = m_fpos;

		if (getcnext() == L']' &&
			getcnext() == L']' &&
			getcnext() == L'>')
		{
		// End of cdata
			break;
		}

		int endpos = m_fpos;

		for (int i = startpos; i < endpos; i++)
		{
			//char c[2] = {0};
			//c[0] = textData[i];
			data += m_textData[i];//_bstr_t(c);
		}
	}

	if (data.length() > 0)
	{
		CDATASection* node = m_document->createCDATASection(data.c_str());

	// <![CDATA[
		node->setTextOffset(0, offset0);
		node->setTextOffset(1, offset0);
		node->setTextOffset(2, offset0);

	// Text content
		node->setTextOffset(3, offset1);
		node->setTextOffset(4, offset1);
		node->setTextOffset(5, m_fpos-3);
		node->setTextOffset(6, m_fpos-3);

	// ]]>
		node->setTextOffset(7, m_fpos);
		node->setTextOffset(8, m_fpos);
		node->setTextOffset(9, m_fpos);

		return node;
	}

	return NULL;
#endif
}

System::StringW* FindNamespaceURIFromAttributes(NamedNodeMap* attributes, System::StringW* prefix)
{
	long length = attributes->get_length();
	for (long i = 0; i < length; i++)
	{
		Attr* attr = dynamic_cast<Attr*>(attributes->item(i));

		/*
		BSTR battrName;
		attr->get_nodeName(&battrName);
		_bstr_t attrName = _bstr_t(battrName, false);
		*/

	//	if (!wcsicmp(attrName, OLESTR("xmlns", 5))

		System::StringW* attprefix = attr->get_prefix();

		if (*attprefix == L"xmlns")
		{
			System::StringW* attlocalname = attr->get_localName();
		//	if ((BSTR)attlocalname == NULL)
		//		attlocalname = OLESTR("");

		//	if ((SysStringLen(prefix) == 0 && SysStringLen(attlocalname) == 0) ||
		//		!wcscmp(attlocalname, prefix))
			if (*attlocalname == *prefix)
			{
				System::StringW* value = attr->get_value();
				return value;
			}
		}
	}

	return NULL;
}

System::StringW* FindNamespaceURI(Node* parent, NamedNodeMap* attributes, System::StringW* prefix)
{
	if (attributes)
	{
		System::StringW* namespaceURI = FindNamespaceURIFromAttributes(attributes, prefix);
		if (namespaceURI) return namespaceURI;
	}

// Try parent element
	if (parent)
	{
		Node* parentParent = parent->get_parentNode();

		NamedNodeMap* parentAttributes =	parent->get_attributes();
		return FindNamespaceURI(parentParent, parentAttributes, prefix);
	}

	return NULL;
}

void XMLParser::ParseAttributes(Node* parent, NamedNodeMap* attributes)
{
	int c;

	while (!eof())
	{
		int offset0 = m_fpos;

		BufferImp<WCHAR> buffer;
		StringBuilderW strbuilder(&buffer);
		CollectSpaces(strbuilder);
		StringW* spaces = buffer.DetachToString();

		c = getcnext();

		if (!iswalpha(c))
		{
			ungetcnext();
			for (int i = 0; i < spaces->Length(); i++)
			{
				ungetcnext();
			}
			break;
		}

		ungetcnext();

		int offset1 = m_fpos;

		StringW* attrPrefix;
		StringW* attrLocalName;
		GetNSID(attrPrefix, attrLocalName);

		if (attrLocalName == NULL)
		{
			StringW* msg = WSTR("Error parsing attributes");
			handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
			throw msg;
		}

		StringW* qualifiedName;
		if (attrPrefix != NULL && attrPrefix->Length())
		{
			qualifiedName = attrPrefix;
			ASSERT(0);
#if 0
			*qualifiedName += *WSTR(":");
			*qualifiedName += *attrLocalName;
#endif
		}
		else
		{
			qualifiedName = attrLocalName;
		}

		StringW* namespaceURI = NULL;

		if (attrPrefix)
		{
			if (*attrPrefix == L"xml")
			{
	// ??
				namespaceURI = WSTR("http://www.w3.org/XML/1998/namespace");
			}
			else if (*attrPrefix == L"xmlns")
			{
				namespaceURI = NULL;	// no namespace
			}
			else
			{
				namespaceURI = FindNamespaceURI(parent, attributes, attrPrefix);
				if (namespaceURI == NULL)
				{
					WCHAR msg[256];
					swprintf(msg, L"Namespace %s not found for attribute", attrPrefix->c_str());

					handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation()));
					throw msg;
				}
			}
		}

		Attr* pAttr = m_document->createAttributeNS(namespaceURI, qualifiedName);
		if (pAttr == NULL)
		{
			WCHAR msg[64];
			swprintf(msg, L"Invalid attribute name %s", qualifiedName->c_str());

			handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation()));
			throw msg;
		}

		pAttr->setTextOffset(0, offset0);	// space before attr name
		pAttr->setTextOffset(1, offset1);	// start of attr name
		pAttr->setTextOffset(2, m_fpos);		// end of attr name

		SkipSpaces();

		c = getcnext();

		if (c == L'=')
		{
			SkipSpaces();
			GetAttrValue(pAttr);
		}
		else
		{
			if (true)	// xml requires attribute value
			{
				WCHAR msg[64];
				swprintf(msg, L"Expected =");

			// However we only throw an error and not a fatalError
				if (!handleError(CreateDOMError(Web::SEVERITY_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation())))
				{
					throw msg;
				}
			}
			ungetcnext();

			pAttr->setTextOffset(3, m_fpos);
			pAttr->setTextOffset(4, m_fpos);
		}

		pAttr->setTextOffset(5, m_fpos);
		pAttr->setTextOffset(6, m_fpos);
		pAttr->setTextOffset(7, m_fpos);
		pAttr->setTextOffset(8, m_fpos);
		pAttr->setTextOffset(9, m_fpos);

		attributes->m_items.Add(pAttr);
	}

//	SkipSpaces();
}

bool XMLParser::ParseChildren(Node* parentNode, Node* nsResolverParent, int xmlSpacePreserve)
{
	bool bEndTag = false;

	Element* pLastElement = NULL;

	while (!eof())
	{
		int spacesStartOffset = m_fpos;

		BufferImp<WCHAR> buffer;
		StringBuilderW strbuilder(&buffer);
		CollectSpaces(strbuilder);
		StringW* spaces = buffer.DetachToString();

		if (pLastElement)
		{
			pLastElement->setTextOffset(9, m_fpos);
		//	pLastElement->Release();
			pLastElement = NULL;
		}

		if (eof()) break;

		int c = getcnext();

	//	if (c == EOF) break;

		if (c == L'<')
		{
			if (spaces->Length())
			{
				if (xmlSpacePreserve)	// preserve
				{
					Text* pText = new Text;
					pText->set_ownerDocument(m_document);
					pText->m_data = spaces;

					// TODO pText->m_whiteSpaceInElementContent = TRUE ??

					pText->setTextOffset(0, spacesStartOffset);
					pText->setTextOffset(1, spacesStartOffset);
					pText->setTextOffset(2, spacesStartOffset);
					pText->setTextOffset(3, spacesStartOffset+spaces->Length());
					pText->setTextOffset(4, spacesStartOffset+spaces->Length());
					pText->setTextOffset(5, spacesStartOffset+spaces->Length());
					pText->setTextOffset(6, spacesStartOffset+spaces->Length());
					pText->setTextOffset(7, spacesStartOffset+spaces->Length());
					pText->setTextOffset(8, spacesStartOffset+spaces->Length());
					pText->setTextOffset(9, spacesStartOffset+spaces->Length());

					parentNode->appendChild(pText);
				}

				spaces = WSTR("");
			}

			c = getcnext();

			if (c == L'!')
			{
				c = getcnext();
				if (c == L'[')	// CDATA section
				{
					StringW* id = GetID();
					if (*id == L"CDATA")
					{
						CDATASection* pCDATA = ParseCDATASection();
						if (pCDATA)
						{
							parentNode->appendChild(pCDATA);
						//	pCDATA->Release();
						}

					//	continue;
					}
					else
					{
						StringW* msg = WSTR("Expected CDATA");

						handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
						throw msg;
					}
				}
				else if (c == L'-')	// Comment
				{
					EatChar('-');

					Comment* comment = ParseCommentNode();

					parentNode->appendChild(comment);
				}
				else	// DOCTYPE or DTD declaration
				{
					ungetcnext();

					StringW* id = GetID();

					if (*id == L"DOCTYPE")
					{
						DocumentType* doctype = ParseDOCTYPE();

						parentNode->appendChild(doctype);
					}
					else if (*id == L"ENTITY")
					{
					}
					else if (*id == L"ELEMENT")
					{
					}
					else if (*id == L"ATTLIST")
					{
					}
					else if (*id == L"NOTATION")
					{
					}
					else
					{
						WCHAR msg[512];
						swprintf(msg, L"Unexpected ident %s", id->c_str());

						handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation()));
						throw msg;
					}
				}
			}
			else if (c == L'?')	// Processing instruction
			{
				ProcessingInstruction* pi = ParseProcessingInstruction();
				parentNode->appendChild(pi);
			}
			else if (c == L'/')	// End tag of this element
			{
				bEndTag = true;
				break;
			}
			else // Beginning of new element
			{
				ungetcnext();

				pLastElement = ParseElement(parentNode, nsResolverParent, xmlSpacePreserve);
			}
		}
		else	// Beginning of text element
		{
			ungetcnext();

			ParseText(parentNode, spaces);
		}
	}

	return bEndTag;
}

Element* XMLParser::ParseElement(Node* parentNode, Node* nsResolverParent, int parentXmlSpacePreserve)
{
	long startoffset = m_fpos-1;	// right before the <

	long startoffset1 = m_fpos;

	StringW* taglocalName;
	StringW* tagprefix;
	GetNSID(tagprefix, taglocalName);

//	ATLTRACE("<%S>\n", (WCHAR*)taglocalName);

	if (taglocalName == NULL)
	{
		StringW* msg = WSTR("Expected tagname after <");

		handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
		throw msg;
	}

	StringW* qualifiedName;
	if (tagprefix != NULL && tagprefix->Length())
	{
		BufferImp<WCHAR> buffer;
		StringBuilderW strbuilder(&buffer);
		strbuilder << *tagprefix << L':' << *taglocalName;
		qualifiedName = buffer.DetachToString();
	}
	else
	{
		qualifiedName = taglocalName;
	}

	long offset1 = m_fpos;
//	_bstr_t whitespace1 = CollectSpaces();
	//SkipSpaces();

// Parse the attributes
	NamedNodeMap* attributes = new NamedNodeMap;

// Add default attributes
	{
		TRACE("TODO\n");
#if 0
		CComQIPtr<ILDocumentAS, &IID_ILDocumentAS> documentAS((IUnknown*)m_document);

		<IASModel> asModel;
		documentAS->get_activeASModel(&asModel);

		if (asModel)
		{
			<IASNamedObjectMap> elementDeclarations;
			asModel->get_elementDeclarations(&elementDeclarations);

			sysstring tagName = (BSTR)taglocalName;

			<IASElementDeclaration> elementDecl;

			elementDeclarations->getNamedItem(tagName, (IASObject**)&elementDecl);
			if (elementDecl)
			{
				<IASNamedObjectMap> attributeDecls;
				elementDecl->get_ASAttributeDecls(&attributeDecls);

				long length;
				attributeDecls->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					<IASObject> object;
					attributeDecls->item(i, &object);

					CComQIPtr<IASAttributeDeclaration, &IID_IASAttributeDeclaration> attrDecl((IUnknown*)object);

					ASValueConstraint defaultType;
					attrDecl->get_defaultType(&defaultType);

					if (defaultType == DEFAULT_VC || defaultType == FIXED_VC)
					{
						CComBSTR name;
						attrDecl->get_nodeName(&name);

						CComBSTR dataValue;
						attrDecl->get_dataValue(&dataValue);

						if (dataValue.Length())
						{
							/*
							WCHAR* localName;
							{
								WCHAR* colon;
								if (colon = wcschr(qualifiedName, L':'))
									localName = colon+1;
								else
									localName = qualifiedName;
							}
							*/

						//	ATLTRACE("default attribute: %S=%S\n", (BSTR)name, (BSTR)dataValue);

							CComObject<CLDOMAttr>* pAttr;
							CComObject<CLDOMAttr>::CreateInstance(&pAttr);
							pAttr->AddRef();
							pAttr->m_ownerDocument = m_document;
						//	pAttr->m_ownerElement =
							pAttr->m_specified = VARIANT_FALSE;

							pAttr->put_nodeName(name);

							pAttr->put_nodeValue(dataValue);

							//m_document->createAttributeNS(NULL, localName, &attr);

							<Web::Node> p;
							attributes->setNamedItemNS(pAttr, &p);

							pAttr->Release();
						}
					}
				}
			}
		}
#endif
	}

	ParseAttributes(nsResolverParent, attributes);

	StringW* namespaceURI = FindNamespaceURI(nsResolverParent, attributes, tagprefix);
	if (tagprefix && namespaceURI == NULL)
	{
		delete attributes;

		WCHAR msg[512];
		swprintf(msg, L"Undefined namespace %s", tagprefix->c_str());

		handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation()));
		throw msg;
	}

	Element* element = m_document->createElementNS(namespaceURI, qualifiedName);
	element->set_attributes(attributes);	// Set the previously parsed attributes onto the element

#if 0
	// TODO, do this here??
	{
		CComQIPtr<CLDOMElementImplImpl>(element)->AddEventListeners(element/*, CComQIPtr<CLDOMDocumentImplImpl>(m_document)->m_pScriptSite*/);
	}
#endif

	StringW* xmlspace = element->getAttribute(WSTR("xml:space"));

	int xmlSpacePreserve;

	if (xmlspace)
		xmlSpacePreserve = (*xmlspace == L"preserve");
	else
		xmlSpacePreserve = parentXmlSpacePreserve;

	//attributes->Release();

	TRACE("TODO\n");
#if 0
	// Do this here this way?
	if (TRUE)
	{
		//CComQIPtr<CLDOMDocumentImplImpl> pDocument = m_document;
		CComQIPtr<CLDOMElementImplImpl>(element)->UpdateAnimationElements(element);
	}
#endif

	element->setTextOffset(0, startoffset);	// at the '...<'
	element->setTextOffset(1, startoffset1);	// at the '<...element'
	element->setTextOffset(2, offset1);	// <element...
	element->setTextOffset(3, m_fpos);	// <element attributes...>

	SkipSpaces();

	int c = getcnext();
	if (c == L'/')	// Immediate End tag of this element
	{
		SkipSpaces();
		EatChar('>');

		element->setTextOffset(4, m_fpos);
		element->setTextOffset(5, m_fpos);
		element->setTextOffset(6, m_fpos);
		element->setTextOffset(7, m_fpos);
		element->setTextOffset(8, m_fpos);
		element->setTextOffset(9, m_fpos);	// TODO

		parentNode->appendChild(element);

		elementDone(element);
		return element;
	}

	if (c != L'>')
	{
		WCHAR msg[64];
		swprintf(msg, L"Expected >");

		handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation()));
		throw msg;

		elementDone(element);
		return element;
	}

	element->setTextOffset(4, m_fpos);	// <tagName attributes>...

	parentNode->appendChild(element);

	bool bEndTag = ParseChildren(element, element/*NOTE, using element instead of nsResolverParent*/, xmlSpacePreserve);

// Required end tag

// ??
	element->setTextOffset(5, m_fpos-2);	// at </

	if (bEndTag)
	{
		SkipSpaces();	// TODO, remove this??

		element->setTextOffset(6, m_fpos);	// at </...element

		StringW* endtaglocalName;
		StringW* endtagprefix;
		GetNSID(endtagprefix, endtaglocalName);

		element->setTextOffset(7, m_fpos);	// at </element...>

		StringW* endnamespaceURI;

		if (*tagprefix == *endtagprefix)
		{
			endnamespaceURI = namespaceURI;
		}
		else
		{
			endnamespaceURI = FindNamespaceURI(parentNode, attributes, endtagprefix);
			if (endtagprefix && endnamespaceURI == NULL)
			//if (endtagprefix.length() > 0 && endnamespaceURI.length() == 0)
			{
				WCHAR msg[512];
				swprintf(msg, L"Undefined namespace %s", endtagprefix->c_str());

				handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation()));
				throw msg;
			}
		}

		SkipSpaces();

//		if (wcscmp(endtaglocalName.c_str(), taglocalName.c_str()) || wcscmp(namespaceURI.c_str(), endnamespaceURI.c_str()))
		if ((*endtaglocalName != *taglocalName) || (*namespaceURI != *endnamespaceURI))
		{
			WCHAR msg[512];
			swprintf(msg, L"End tag \"%s\" doesn't match \"%s\"", taglocalName->c_str(), endtaglocalName->c_str());

			handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation()));
			throw msg;

			elementDone(element);
			return element;
		}

		SkipSpaces();
		EatChar('>');
	}
	else
	{
		WCHAR msg[512];
		swprintf(msg, L"Missing endtag for \"%s\"", taglocalName->c_str());

		handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, new StringW(string_copy(msg)), getcnexturrentLocation()));
		throw msg;
	}

	element->setTextOffset(8, m_fpos);	// </element>...
	element->setTextOffset(9, m_fpos);	// TODO

	elementDone(element);

	return element;
}

void XMLParser::elementDone(Element* element)
{
#if 0
	BSTR btagName;
	element->get_tagName(&btagName);
	_bstr_t tagName = _bstr_t(btagName, false);

	if (!wcsicmp(tagName, OLESTR("script")))
	{
		if (!m_editMode)
		{
			CComQIPtr<IDispatch> scriptDisp;

			CComQIPtr<IHTMLDocument2> htmlDocument;
			CComQIPtr<ISVGDocument> svgDocument;

			if (htmlDocument = m_document)
			{
				htmlDocument->get_Script(&scriptDisp);
			}
			else if (svgDocument = m_document)
			{
				svgDocument->get_Script(&scriptDisp);
			}

			if (scriptDisp != NULL)
			{
				CComQIPtr<IActiveScript> activeScript = scriptDisp;
				CComQIPtr<IActiveScriptParse> activeScriptParse = scriptDisp;

				BSTR bsrc;
				element->getAttribute(OLESTR("src", &bsrc);
				_bstr_t src = _bstr_t(bsrc, false);
				if (src.length())
				{
					BSTR burl;
					m_textDoc->get_url(&burl);
					_bstr_t url = _bstr_t(burl, false);

					char dir[260] = {0};
					char path[260] = {0};
					if (url.length())
					{
						_splitpath(url, dir, path, NULL, NULL);
					}

					char abspath[260];
					_makepath(abspath, dir, path, src, NULL);

					CComQIPtr<ITextData> textfile;
					textfile.CoCreateInstance(CLSID_TextData);

					VARIANT_BOOL bloaded;
					textfile->load(_bstr_t(abspath), &bloaded);
					if (bloaded)
					{
						BSTR textdata;
						textfile->get_data(&textdata);

						ErrorCode hr;

						EXCEPINFO	excepinfo;
						hr = activeScriptParse->ParseScriptText(

							textdata,

							NULL,
							NULL,
							NULL,
							0,
							0,	// start line number
							SCRIPTTEXT_ISVISIBLE | SCRIPTTEXT_ISPERSISTENT,	// flags
							NULL,
							&excepinfo);
					}

					/*
					URL_COMPONENTS	url = {0};
					url.dwStructSize = sizeof(url);
					InternetCrackUrl(m_url, 0, 0, &url);
					InternetCombineUrl(
					*/
				}

				CComQIPtr<IDOMNode> node;
				element->get_firstChild(&node);
				if (node != NULL)
				{
					CComQIPtr<IDOMCharacterData> text = node;
					if (text)
					{
						BSTR textdata;
						text->get_data(&textdata);

						ErrorCode hr;

						EXCEPINFO	excepinfo;
						hr = activeScriptParse->ParseScriptText(

							textdata,

							NULL,
							NULL,
							NULL,
							0,
							0,	// start line number
							SCRIPTTEXT_ISVISIBLE | SCRIPTTEXT_ISPERSISTENT,	// flags
							NULL,
							&excepinfo);

						SysFreeString(textdata);

						//htmlDocument->close();
					}
				}
			}
		}
	}
	else if (!wcsicmp(tagName, OLESTR("style"))
	{
		CComQIPtr<IDOMNode> child;
		element->get_firstChild(&child);

		CComQIPtr<IDOMText> text = child;
		if (text)
		{
			BSTR btextdata;
			text->get_data(&btextdata);
			_bstr_t textdata = _bstr_t(btextdata, false);

			CComQIPtr<IDOMCSSStyleSheet> stylesheet;
			stylesheet.CoCreateInstance(CLSID_DOMCSSStyleSheet);

			CComQIPtr<IDocumentStyle> documentStyle = m_document;//getcnextontrollingUnknown();
			if (documentStyle)
			{
				CComQIPtr<IStyleSheetList> stylesheetList;
				documentStyle->get_styleSheets(&stylesheetList);

				stylesheetList->append(stylesheet);

				CComQIPtr<IHTMLStyleSheet> htmlstylesheet = stylesheet;
				htmlstylesheet->set_cssText(textdata);	// The stylesheet will parse the text
			}
		}
	}
#endif
//	Fire_ParsedElementDone(element);
}

CEXMLDocument* XMLParser::get_document() const
{
	return m_document;
}

void XMLParser::put_document(CEXMLDocument *newVal)
{
	m_document = newVal;
}

bool XMLParser::parse()
{
	return !loadXML2();
}

long XMLParser::ParseXMLHeader()
{
	System::StringW* xmlid = GetID();
	if (wcscmp(xmlid->c_str(), L"xml"))
	{
// Not an xml document
		//MessageBox(NULL, "Not an xml document", "XML", MB_OK);
		throw WSTR("Not an xml document");
	}

	//Read <?xml ... ?>
	while (!eof())
	{
		SkipSpaces();

		int c = getcnext();

		if (!iswalpha(c))
		{
			ungetcnext();
			break;
		}

		ungetcnext();

		System::StringW* name = GetID();

		SkipSpaces();
		EatChar(L'=');
		SkipSpaces();

		System::StringW* value = GetString();

		if (!wcscmp(name->c_str(), L"version"))
			;//m_version = value;
		else if (!wcscmp(name->c_str(), L"encoding"))
			;//m_encoding = value;
		else if (!wcscmp(name->c_str(), L"standalone"))
		{
			if (!wcscmp(value->c_str(), L"yes"))
				;//m_standalone = TRUE;
			else if (!wcscmp(value->c_str(), L"no"))
				;//m_standalone = FALSE;
			else
			{
				// TODO, create warning
				;//m_standalone = FALSE;
			}
		}

		SkipSpaces();
	}

	EatChar('?');
	SkipSpaces();
	EatChar('>');

	return 0;
}

DocumentType* XMLParser::ParseDOCTYPE()
{
// <!DOCTYPE has been read

#if 0
	USES_CONVERSION;
#endif

	DocumentType* doctype = new DocumentType;
	if (doctype)
	{
		doctype->set_ownerDocument(m_document);

		doctype->setTextOffset(0, m_fpos-9);
		doctype->setTextOffset(1, m_fpos-7);
		doctype->setTextOffset(2, m_fpos);

		SkipSpaces();

		doctype->setTextOffset(3, m_fpos);

		doctype->m_name = GetID();
		//doctype->m_name = name;//put_name(name);

		SkipSpaces();

		System::StringW* more = GetID();
		SkipSpaces();

		if (!wcscmp(more->c_str(), L"PUBLIC"))
		{
			doctype->m_publicId = GetString();

			SkipSpaces();

			int c = getcnext();
			ungetcnext();
			if (c != '>')
			{
				doctype->m_systemId = GetString();
			}
		}
		else if (!wcscmp(more->c_str(), L"SYSTEM"))
		{
			doctype->m_systemId = GetString();
		}
		else
		{
			System::StringW* msg = WSTR("Expected PUBLIC or SYSTEM");

			handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
			throw msg;
		}

		SkipSpaces();

	//	CComObject<CDTDDocument>::CreateInstance(&doctype->m_dtd);
	//	doctype->m_dtd->AddRef();

		doctype->setTextOffset(4, m_fpos);

	// Internal subset
		int c = getcnext();
		if (c == L'[')
		{
			ASSERT(0);
#if 0
			doctype->setTextOffset(5, m_fpos);

			CDTDParser dtdParser;
			dtdParser.m_document = m_document;//doctype->m_dtd;
			dtdParser.m_dtdDocument = doctype->m_dtd;
			dtdParser.m_parentNode = doctype->m_internalSubsetNode;

			dtdParser.m_eof = L']';
			dtdParser.m_textData = m_textData;
			dtdParser.m_errorHandler = m_errorHandler;
			dtdParser.m_line = m_line;
			dtdParser.m_column = m_column;
			dtdParser.m_fpos = m_fpos;

			ErrorCode hr = dtdParser.Parse2();

			m_line = dtdParser.m_line;
			m_column = dtdParser.m_column;
			m_fpos = dtdParser.m_fpos;

			doctype->setTextOffset(6, m_fpos);
			EatChar(L']');
#endif
		}
		else
			ungetcnext();	// ungetcnext [

		SkipSpaces();

		doctype->setTextOffset(7, m_fpos);

		EatChar(L'>');

		doctype->setTextOffset(8, m_fpos);
		doctype->setTextOffset(9, m_fpos);

		if (m_document)
		{
#if 0	// Done when node is inserted into document
			// External subset
			if (doctype->m_systemId.Length())
			{
				CComBSTR documentUrl;
				m_document->get_url(&documentUrl);

				TCHAR result[2048];
				{
					DWORD resultLen = sizeof(result);
					InternetCombineUrl(W2A(documentUrl), W2A(doctype->m_systemId), result, &resultLen, 0);
				}

				CDTDParser dtdParser;
				dtdParser.m_parentNode = doctype->m_dtd;
				dtdParser.m_dtdDocument = doctype->m_dtd;
				dtdParser.m_errorHandler = m_errorHandler;
				//dtdParser.m_url = _bstr_t(documentUrl);

				WCHAR* absurl = A2W(result);

				ATLTRACE("loading external subset: %s...", result);
				ErrorCode hr = dtdParser.loadURL(absurl);
				if (FAILED(hr))
				{
					OLECHAR msg[512];
					swprintf(msg, OLESTR("Failed to load external subset url: %s", absurl);

					if (!handleError(CreateDOMError(Web::LSEVERITY_ERROR, msg, getcnexturrentLocation())))
					{
						throw msg;
					}
				}

				ATLTRACE("done\n", result);
			}

			// Build and parse general entities
			{
				for (int i = 0; i < doctype->m_dtd->m_entityList.GetSize(); i++)
				{
					CEntity* pDTDEntity = doctype->m_dtd->m_entityList[i];

					if (pDTDEntity->m_c == 0)
					{
						<ILDOMDocumentFragment> fragment;
						m_document->parseFragment(pDTDEntity->m_value, NULL/*hm ??*/, &fragment);

						if (fragment)
						{
							CComObject<CLDOMEntity>* pEntity;
							CComObject<CLDOMEntity>::CreateInstance(&pEntity);
							if (pEntity)
							{
								pEntity->AddRef();

								pDTDEntity->m_domEntity = pEntity;
								pEntity->m_pDTDEntity = pDTDEntity;

								pEntity->m_name = pDTDEntity->m_name;
								pEntity->appendChild(fragment, NULL);

								<Web::Node> p;
								doctype->m_entities->setNamedItem(pEntity, &p);

								pEntity->Release();
							}
						}
					}
				}
			}

			/*
		// Finally convert the internal and external subset to AS model
			CComObject<CASDTDModel>* pModel;
			CComObject<CASDTDModel>::CreateInstance(&pModel);
			if (pModel)
			{
				pModel->AddRef();

				pModel->BuildFromDTDDocument(doctype->m_dtd);

				CComQIPtr<ILDocumentAS> documentAS = m_document;
				if (documentAS)
				{
					documentAS->put_activeASModel(pModel);
				}

				pModel->Release();
			}
			*/
#endif
		}
	}

	return doctype;
}

#if 0
#include "XMLSchema.h"
#endif

ErrorCode XMLParser::loadXML2()
{
//	USES_CONVERSION;

	TRACE("loadXML2()...\n");

//	m_document.Release();

#if 0
	m_textDoc->get_len(&m_textLen);
	m_textDoc->get_data(&m_textData);
#endif

	bool bXML;

	if (m_document == NULL)
	{
// Find out what kind of document this is
		DocumentType* doctype;

		m_line = 0;
		m_column = 0;
		m_oldc = EOF;
		m_fpos = 0;

		//m_bXML = false;

		try
		{
			SkipSpaces();

		// Read <?xml ... >
			EatChar('<');

			int c = getcnext();
			if (c == '?')
			{
				ParseXMLHeader();
				bXML = true;
			}
			else
			{
				ungetcnext();
				ungetcnext();
			}

			SkipSpaces();

		// Process document children
			while (!eof())
			{
				EatChar('<');
			//	SkipSpaces();

				int c = getcnext();
				if (c == L'!')
				{
					int c2 = getcnext();
					if (c2 == L'-')
					{
						int c3 = getcnext();
						if (c3 == L'-')
						{
							// Comment
							Comment* comment = ParseCommentNode();
						}
						else
						{
							ungetcnext();
							ungetcnext();
						}
					}
					else	// Maybe DOCTYPE
					{
						ungetcnext();

						System::StringW* id = GetID();
						if (id->Length() && !wcscmp(id->c_str(), L"DOCTYPE"))
						{
							if (doctype != NULL)	// Can only have one doctype node
							{
								System::StringW* msg = WSTR("Can only have one doctype node");

								if (!handleError(CreateDOMError(Web::SEVERITY_ERROR, msg, getcnexturrentLocation())))
								{
									throw msg;
								}
							}

							doctype = ParseDOCTYPE();
						}
						else
						{
							// Assume it's a DTD document

							ASSERT(0);
#if 0
							m_document.CoCreateInstance(CLSID_LDTDDocument);
#endif
							break;
							/*
							WCHAR* msg = OLESTR("Expected DOCTYPE";

							handleError(CreateDOMError(LSEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
							throw msg;
							*/

						}
					}
				}
				else if (c == L'?')
				{
					// Processing instruction
					ProcessingInstruction* pi = ParseProcessingInstruction();
				}
				else
				{
					ungetcnext();	// back up the character that wasn't a '!'

					SkipSpaces();

					System::StringW* taglocalName;
					System::StringW* tagprefix;
					GetNSID(tagprefix, taglocalName);

					if (taglocalName == 0)
					{
						System::StringW* msg = WSTR("Expected tagname after <");

						handleError(CreateDOMError(Web::SEVERITY_FATAL_ERROR, msg, getcnexturrentLocation()));
						throw msg;
					}

#if 0
					if (!wcscmp(taglocalName, OLESTR("html"))
					{
						m_document.CoCreateInstance(CLSID_LHTMLDocument);
					}
					else if (!wcscmp(taglocalName, OLESTR("svg"))
					{
						//m_document.CoCreateInstance(CLSID_LSVGDocument);
						m_document.CoCreateInstance(OLESTR("Web.LSVGDocument");
					}
					else if (!wcscmp(taglocalName, OLESTR("smil"))
					{
						m_document.CoCreateInstance(CLSID_LSMILDocument);
					}
					else if (!wcscmp(taglocalName, OLESTR("lxui"))
					{
						m_document.CoCreateInstance(OLESTR("LXUI.LXUIDocument");
					}
					else if (!wcscmp(taglocalName, OLESTR("nitf"))
					{
						m_document.CoCreateInstance(CLSID_LNITFDocument);
					}
					else if (!wcscmp(taglocalName, OLESTR("NewsML"))
					{
						m_document.CoCreateInstance(CLSID_LNewsMLDocument);
					}
#if 0
					else if (!wcscmp(taglocalName, OLESTR("schema"))
					{
						m_document.CoCreateInstance(CLSID_XMLSchemaDocument);
					}
#endif
					else
#endif
						ASSERT(0);
#if 0
					{
						m_document = new Web::CLDOMDocument;//.CoCreateInstance(CLSID_LDOMDocument);
					}
#endif

					if (m_document == NULL)
					{
						throw WSTR("Couldn't create document");
					}

#if 0
					CComQIPtr<CLDOMDocumentImplImpl>(m_document)->m_acDocument = m_activeDocument;
#endif
					ASSERT(0);
#if 0
					m_document->put_errorHandler(m_errorHandler);
#endif
				//	m_document->put_isXML(m_bXML);

					// hm.. do this here ?
					if (true)
					{
						Web::DocumentStyleImpl* documentStyle = dynamic_cast<Web::DocumentStyleImpl*>(m_document);
						if (documentStyle)
						{
#if 0//_WINDOWS
							TCHAR appdata[MAX_PATH];
							SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, appdata);

							CLCSSStyleSheet* stylesheet = new CLCSSStyleSheet;//.CoCreateInstance(CLSID_LCSSStyleSheet);
							if (stylesheet)
							{
								TCHAR pathname[MAX_PATH];
								_makepath(pathname, NULL, appdata, "LXFramework", NULL);

								TCHAR filename[MAX_PATH];

								if (!wcscmp(taglocalName, OLESTR("nitf")))
								{
									_makepath(filename, NULL, pathname, "nitf.css", NULL);
								}
								else if (!wcscmp(taglocalName, OLESTR("article")))	// DocBook
								{
									_makepath(filename, NULL, pathname, "docbook.css", NULL);
								}
								else if (!wcscmp(taglocalName, OLESTR("stylesheet")))
								{
									_makepath(filename, NULL, pathname, "xslt.css", NULL);
								}
								else if (!wcscmp(taglocalName, OLESTR("html")) ||
									!wcscmp(taglocalName, OLESTR("svg")) ||
									!wcscmp(taglocalName, OLESTR("lxui")))
								{
									_makepath(filename, NULL, pathname, "html.css", NULL);
								}

								//MessageBox(NULL, filename, "", MB_OK);

								stylesheet->Load(A2W(filename));

								<ILStyleSheetList> stylesheets;
								documentStyle->get_styleSheets(&stylesheets);
								stylesheets->append(stylesheet);
							}
#endif	// _WINDOWS
						}
					}

					break;
				}

				SkipSpaces();
			}
		}
		catch(OLECHAR* p)
		{
		// hm.. create document even if failed (NO????)
#if 0
			m_document.CoCreateInstance(OLESTR("Web.LSVGDocument");
#endif

			TRACE("\n\nERROR FIRST PASS XML: %S\n\n", p);
			return Error;
		}
	}
	else
	{
#if 0
		// TODO, remove all children
		Element* documentElement = m_document->get_documentElement();
		if (documentElement)
		{
			m_document->put_documentElement(NULL);
			m_document->removeChild(documentElement);
		}

		DocumentType* doctype = m_document->get_doctype();
		if (doctype)
		{
			//m_document->put_doctype(NULL);
			m_document->removeChild(doctype);
		}
#endif
	}

	if (m_document)
	{
#if 0
		if (m_textDoc)
		{
			CComBSTR url;
			m_textDoc->get_url(&url);
			m_document->put_url(url);
		}
#endif

		ErrorCode hr = Error;	// Assume error

		m_line = 0;
		m_column = 0;
		m_oldc = EOF;
		m_fpos = 0;

		m_document->setTextOffset(0, m_fpos);
		m_document->setTextOffset(1, m_fpos);
		m_document->setTextOffset(2, m_fpos);
		m_document->setTextOffset(3, m_fpos);
		m_document->setTextOffset(4, m_fpos);

#if 0
		CComQIPtr<ILDTDDocument, &IID_ILDTDDocument> dtdDocument((IUnknown*)m_document);
		if (dtdDocument)	// ???
		{
			CDTDParser dtdParser;
			dtdParser.m_document = m_document;//doctype->m_dtd;
			dtdParser.m_dtdDocument = static_cast<CDTDDocument*>(m_document.p);
			dtdParser.m_parentNode = m_document;//doctype->m_internalSubsetNode;

			//dtdParser.m_eof = L']';
			dtdParser.m_url = m_uri;
			dtdParser.m_textData = m_textData;
			dtdParser.m_errorHandler = m_errorHandler;
			dtdParser.m_line = m_line;
			dtdParser.m_column = m_column;
			dtdParser.m_fpos = m_fpos;

			CComObject<CASDTDModel>::CreateInstance(&static_cast<CDTDDocument*>(m_document.p)->m_pASModel);
			static_cast<CDTDDocument*>(m_document.p)->m_pASModel->AddRef();

			ErrorCode hr = dtdParser.Parse();

			static_cast<CDTDDocument*>(m_document.p)->m_pASModel->BuildFromDTDDocument(static_cast<CDTDDocument*>(m_document.p));

			return hr;
		}
#endif

#if 0
		CComQIPtr<CLDOMDocumentImplImpl>(m_document)->InitScripting();
#endif

		try
		{
			SkipSpaces();

		// Read <?xml ... >
			EatChar('<');
			SkipSpaces();

			int c = getcnext();
			if (c == '?')
			{
				ParseXMLHeader();
			}
			else
			{
				ungetcnext();
				ungetcnext();
			}

			SkipSpaces();

			ParseChildren(m_document, NULL, false/*xmlSpacePreserve*/);

	// Validate document

#if 0
			try
			{
				<Web::Element> documentElement;
				m_document->get_documentElement(&documentElement);
				if (documentElement)
				{
					BSTR bnoNSSchemaLocation;
					documentElement->getAttribute(OLESTR("xsi:noNamespaceSchemaLocation", &bnoNSSchemaLocation);
					_bstr_t noNSSchemaLocation = _bstr_t(bnoNSSchemaLocation, false);

					BSTR bschemaLocation;
					documentElement->getAttribute(OLESTR("xsi:schemaLocation", &bschemaLocation);
					_bstr_t schemaLocation = _bstr_t(bschemaLocation, false);

					_bstr_t schemaURL;

					if (schemaLocation.length())
					{
						_bstr_t uri;
						_bstr_t ns;

						OLECHAR* p = (BSTR)schemaLocation;

						// Get namespace part
						while (*p)
						{
							if (iswspace(*p)) break;
							WCHAR c2[2] = {*p, 0};
							ns += c2;
							p++;
						}

						while (iswspace(*p)) p++;

						// get uri part
						while (*p)
						{
						//	if (iswspace(*p)) break;
							WCHAR c2[2] = {*p, 0};
							uri += c2;
							p++;
						}

						schemaURL = uri;
					}

					if (schemaURL.length() == 0)
					{
						schemaURL = noNSSchemaLocation;
					}

					if (schemaURL.length())
					{
						char abspath[260];

						{
							BSTR burl;
							m_textDoc->get_url(&burl);
							_bstr_t url = _bstr_t(burl, false);

							char dir[260] = {0};
							char path[260] = {0};
							if (url.length())
							{
								_splitpath(url, dir, path, NULL, NULL);
							}

							_makepath(abspath, dir, path, schemaURL, NULL);
						}

						CComQIPtr<IXMLSchemaDocument> schemadoc;
						schemadoc.CoCreateInstance(CLSID_XMLSchemaDocument);
						VARIANT_BOOL bloadedSchema;
						schemadoc->load(_bstr_t(abspath), &bloadedSchema);
						if (bloadedSchema)
						{
							CComQIPtr<IDOMElement> mergeDocumentElement;
							schemadoc->get_documentElement(&mergeDocumentElement);

							CSchema* pSchema = new CSchema;
							pSchema->m_errorHandler = m_errorHandler;
						//	pSchema->m_schemaElement.CoCreateInstance(CLSID_DOMElement);

						// Copy the targetNamespace attribute (hm..)
							{
								BSTR b;
								mergeDocumentElement->getAttribute(OLESTR("targetNamespace", &b);
								if (b)
								{
									pSchema->m_targetNamespace = b;
									//pSchema->m_schemaElement->setAttribute(OLESTR("targetNamespace", b);
									SysFreeString(b);
								}
							}

							{
								BSTR b;
								mergeDocumentElement->getAttribute(OLESTR("elementFormDefault", &b);
								if (b)
								{
									pSchema->m_elementFormDefault = b;
									//pSchema->m_schemaElement->setAttribute(OLESTR("elementFormDefault", b);
									SysFreeString(b);
								}
							}

							{
								BSTR b;
								mergeDocumentElement->getAttribute(OLESTR("attributeFormDefault", &b);
								if (b)
								{
									pSchema->m_attributeFormDefault = b;
									//pSchema->m_schemaElement->setAttribute(OLESTR("attributeFormDefault", b);
									SysFreeString(b);
								}
							}

							pSchema->IncludeSchema(mergeDocumentElement);

						//
							pSchema->ValidateDocument(m_document);

							delete pSchema;
						}
					}
				}
			}
			catch(OLECHAR* p)
			{
				ATLTRACE("\n\nERROR VALIDATING XML: %S\n\n", p);
			}
#endif

			{
#if 0//_WINDOWS
				if (CComQIPtr<CLDOMDocumentImplImpl>(m_document)->m_pScriptSite->m_debugDocumentHelper)
				{
					BSTR textdata;
					m_textDoc->get_data(&textdata);
					// Note, not freeing

					ErrorCode hr = CComQIPtr<CLDOMDocumentImplImpl>(m_document)->m_pScriptSite->m_debugDocumentHelper->AddUnicodeText(textdata);
					ASSERT(SUCCEEDED(hr));
				}

			//	SCRIPTSTATE state;
			//	m_pScriptSite->m_activeScript->GetScriptState(&state);

			//	CComQIPtr<IActiveScriptParse> activeScriptParse = CComQIPtr<CLDOMDocumentImplImpl>(m_document)->m_pScriptSite->m_activeScript;

			//	CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = CComQIPtr<CLDOMDocumentImplImpl>(m_document)->m_pScriptSite->m_activeScript;

				CComQIPtr<CLDOMDocumentImplImpl/*, &IID_CLDOMDocumentImplImpl*/>((IUnknown*)m_document)->AddScripts(m_document);
			//	AddEventListeners(m_document);	// Already done
#endif	// _WINDOWS
			}

			TRACE("Successfully Parsed XML document\n");

			hr = Success;	// Completely successfull
		}
		catch(OLECHAR* p)
		{
			TRACE("\n\nPartially failed loading XML: %S\n\n", p);

			hr = Success_False;
		}

		m_document->setTextOffset(5, m_fpos);
		m_document->setTextOffset(6, m_fpos);
		m_document->setTextOffset(7, m_fpos);
		m_document->setTextOffset(8, m_fpos);
		m_document->setTextOffset(9, m_fpos);

		// Do this even if loading xml partially failed
		{

			if (m_document->m_documentElement)
			{
#if 0	// Had this
				{
					<Web::NodeList> extensionDefsElements;
					m_document->getElementsByTagNameNS(OLESTR("http://www.w3.org/2000/svg"), OLESTR("extensionDefs"), &extensionDefsElements);

					pDocument->BindElements(extensionDefsElements, pDocument->m_documentElement);
				}
#endif

#if 0	// TODO:Remove this
			// SMIL Animation (connect animate/set etc. elements to the elements they target)
				pDocument->BuildAnimationListForAllElements(pDocument->m_documentElement, pDocument->m_documentElement);
#endif
#if 0	// Had this
				pDocument->SetValuesOnAllAnimations(pDocument->m_documentElement);
#endif

#if 0	// Done during parsing
			// Set baseVal/animVal from attributes and parse 'style' attributes
				pDocument->UpdateAnimationElements(pDocument->m_documentElement);
#endif

#if 0	// Done automatically while document is being built ?
				pDocument->GetFirstIntervals(pDocument->m_documentElement);
#endif
			}

#if 0	// Had this
			{
				for (int i = 0; i < pDocument->m_pViews.GetSize(); i++)
				{
					ASSERT(0);
#if 0
					pDocument->m_pViews[i]->DoneParsing();
#endif
				}
			}
#endif
		}

		TRACE("loadXML2() hr=%d\n", hr);

		return hr;
	}
	else
		return Error;
}

bool XMLParser::validateToSchema(Document *schemaDoc)
{
/*
	CComQIPtr<IDOMElement> element;
	m_document->get_documentElement(&element);

	*pVal = ValidateElement(schemaDoc, element);
*/
	return Success;
}

bool XMLParser::load(System::StringW* xmlSource)
{
	System::IO::FileByteStream stream(xmlSource);

	uint32 size = (uint32)stream.GetSize();

	WCHAR* textData = new WCHAR[size];
	m_textLen = size;

	int i = 0;
	while (1)
	{
		uint8 byte;
		if (stream.Read(&byte, 1) != 1)
			break;

		textData[i] = byte;
		i++;
	}

//	delete stream;

	m_textData = textData;

	bool success = !loadXML2();

	//delete textData;

	return success;

	ASSERT(0);
	return false;
#if 0
	//USES_CONVERSION;

	StringA filename = DownloadFile(xmlSource.ToStringA().c_str());

	HANDLE hFile = CreateFile(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	DWORD nRead;
	uint8* buffer = NULL;// = new uint8[512];
	int len = 0;
	do
	{
		buffer = (uint8*)realloc(buffer, len+512);
		ReadFile(hFile, buffer+len, 512, &nRead, NULL);
		len += nRead;
	}
	while (nRead == 512);

	CloseHandle(hFile);

	m_document->m_textData->put_data(NULL, len);
//	m_document->m_textData->m_len = len;
	m_textLen = len;
	for (int i = 0; i < len; i++)
	{
		m_document->m_textData->get_data()[i] = buffer[i];
	}

	delete [] buffer;

	m_textData = m_document->m_textData->get_data();

	bool success = !loadXML2();

	//delete textData;

	return success;
#if 0
	if (success == NULL) return E_POINTER;
	*success = VARIANT_FALSE;

	if (m_textDoc == NULL)
	{
		CComQIPtr<ITextData, &IID_ITextData> textDoc;
		textDoc.CoCreateInstance(CLSID_TextData);

		m_textDoc = textDoc;
	}

	if (m_textDoc)
	{
		ErrorCode hr = E_FAIL;	// Assume failure

		if (V_VT(&xmlSource) == VT_BSTR)
		{
			m_uri = V_BSTR(&xmlSource);
			hr = m_textDoc->load(m_uri);
		}
		else if (V_VT(&xmlSource) == VT_UNKNOWN || V_VT(&xmlSource) == VT_DISPATCH)
		{
			CComQIPtr<IStream, &IID_IStream> stream = V_UNKNOWN(&xmlSource);

			if (stream)
			{
				CComQIPtr<IPersistStream> persistStream = m_textDoc;
				hr = persistStream->Load(stream);
			}
		}

		if (SUCCEEDED(hr))
		{
			hr = loadXML2();
		// S_FALSE means partial success, but we only mark this variable on a complete success
			if (hr == Success)
				*success = VARIANT_TRUE;
			else
				*success = VARIANT_FALSE;
		}
	}

// Should I release the textDoc if it hasn't been explicitly set?

	return Success;
#endif
#endif
}

bool XMLParser::loadXML(System::StringW* sourceText)
{
#if 0

	if (m_textDoc == NULL)
	{
		CComQIPtr<ITextData, &IID_ITextData> textDoc;
		textDoc.CoCreateInstance(CLSID_TextData);

		m_textDoc = textDoc;
	}

	m_textDoc->put_data(SysAllocString(sourceText));
#endif
	m_textLen = sourceText->Length();
	m_textData = sourceText->c_str();

	return !loadXML2();

// Should I release the textDoc if it hasn't been explicitly set?
}

ErrorCode XMLParser::get_errorHandler(Web::IDOMErrorHandler **pVal)
{
	*pVal = m_errorHandler;
//	if (*pVal) (*pVal)->AddRef();

	return Success;
}

ErrorCode XMLParser::put_errorHandler(Web::IDOMErrorHandler *newVal)
{
	m_errorHandler = newVal;
	return Success;
}

Web::IDOMLocator* XMLParser::getcnexturrentLocation()
{
	return NULL;
#if 0
	CLDOMLocator* locator = new CLDOMLocator;
	if (locator)
	{
		locator->m_offset = m_fpos;
		locator->m_lineNumber = m_line;
		locator->m_columnNumber = m_column;
		locator->m_uri = m_uri;
	}

	return locator;
#endif
}

///////////////////////////////////////////////////////////////////////////////

//IMPORTEXPORT Web::Element* GetElementByTagName(Web::Node* parentNode, BSTR tagName, BOOL bDeep = TRUE);
//IMPORTEXPORT Web::Element* GetElementByTagNameNS(Web::Node* parentNode, BSTR ns, BSTR tagName, BOOL bDeep = TRUE);

//#include "sqlext.h"

NamedRGBColor gLayerColors[] =
{
	NamedRGBColor(WSTR("Light Blue"), LDraw::Color(79, 153, 255)),
#if 0
	"Red", RGB(255, 0, 0),
	"Green", RGB(79, 255, 79),
	"Blue", RGB(0, 0, 255),
	"Yellow", RGB(255, 255, 79),
	"Magenta", RGB(255, 79, 255),
	"Cyan", RGB(0, 255, 255),
	"Gray", RGB(127, 127, 127),
	"Black", RGB(0, 0, 0),
	"Orange", RGB(255, 102, 0),
	"Dark Green", RGB(0, 84, 0),
	"Teal", RGB(0, 153, 153),
	"Tan", RGB(204, 153, 102),
	"Brown", RGB(153, 51, 0),
	"Violet", RGB(153, 51, 255),
	"Gold", RGB(255, 153, 0),
	"Dark Blue", RGB(0, 0, 135),
	"Pink", RGB(255, 153, 204),
	"Lavender", RGB(153, 153, 255),
	"Brick Red", RGB(153, 0, 0),
	"Olive Green", RGB(102, 102, 0),
	"Peach", RGB(255, 153, 153),
	"Burgundy", RGB(153, 0, 51),
	"Grass Green", RGB(153, 204, 0),
	"Ochre", RGB(153, 102, 0),
	"Purple", RGB(102, 0, 102),
	"Light Gray", RGB(186, 186, 186),
#endif
};

#define NUMLAYERCOLORS (sizeof(gLayerColors)/sizeof(NamedRGBColor))

int gNumLayerColors = NUMLAYERCOLORS;

#ifdef _DEBUG
void CEXMLDocument::ASSERT_NodeOffsets(Web::Node* node, Web::Node* exceptnode)
{
#if 0
	if (!IsUnknownEqualUnknown(node, exceptnode))
	{
		for (int i = 1; i < 10; i++)

		{
			long offset;
			node->getTextOffset(i-1, &offset);

			long offset1;
			node->getTextOffset(i, &offset1);

			ASSERT(offset >= 0);
			ASSERT(offset1 >= 0);
			ASSERT(offset1 >= offset);
		}

		CComPtr<ILDOMNamedNodeMap> attributes;
		node->get_attributes(&attributes);

		if (attributes)
		{
			long length;
			attributes->get_length(&length);

			for (int i = 0; i < length; i++)
			{
				CComPtr<Web::Node> attr;
				attributes->item(i, &attr);

				ASSERT_NodeOffsets(attr, exceptnode);
			}
		}

		CComPtr<Web::Node> child;
		node->get_firstChild(&child);
		while (child)
		{
			ASSERT_NodeOffsets(child, exceptnode);

			CComPtr<Web::Node> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}
	}
#endif
}

void CEXMLDocument::ASSERT_NodeOffsetsTextLen(Web::Node* node)
{
#if 0
	BSTR textdata;
	m_textDocument->get_data(&textdata);
	int textlen = SysStringLen(textdata);

	for (int i = 0; i < 10; i++)
	{
		long offset;
		node->getTextOffset(i, &offset);

		ASSERT(offset <= textlen);
	}

	CComPtr<ILDOMNamedNodeMap> attributes;
	node->get_attributes(&attributes);

	if (attributes)
	{
		long length;
		attributes->get_length(&length);

		for (int i = 0; i < length; i++)
		{
			CComPtr<Web::Node> attr;
			attributes->item(i, &attr);

			ASSERT_NodeOffsetsTextLen(attr);
		}
	}

	CComPtr<Web::Node> child;
	node->get_firstChild(&child);
	while (child)
	{
		ASSERT_NodeOffsetsTextLen(child);

		CComPtr<Web::Node> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
#endif
}

#endif

/////////////////////////////////////////////////////////////////////////////
// CEXMLDocument

CEXMLDocument::CEXMLDocument()
{
	m_fileTitle = NULL;
//	m_pTree = NULL;

	m_documentElement = NULL;
	m_childNodes = new NodeList;

//	m_documentClass = NULL;

	m_undoManager = NULL;

//	m_pActiveElement = NULL;
//	m_pActiveSelection = NULL;

//	m_pActiveAttr = NULL;
//	m_domActiveElement = NULL;

	m_activeKey = 0xffff;

	m_modified = 0;

	m_bPlaying = false;
	m_videoTimeID = 0;

//	m_activeTool = ID_SVGTOOL_SELECT;

	m_bSourceEditLast = true;	// Consider right after opening document as a source edit

	m_lockDOM = 0;
	m_lockSource = 0;

	m_svgNextLayerIndex = 0;

	m_idThreadUpdateSource = 0L;
	m_hThreadUpdateSource = NULL;

//	m_pElementBehaviorFactory = NULL;

	m_bookmarks = NULL;

	m_pathName = NULL;

	m_lastColor = WSTR("#000000");
	/*
	m_defaultColorRed = 0;
	m_defaultColorGreen = 0;
	m_defaultColorBlue = 0;
	*/

	m_lastGradient = WSTR("none");

	g_selectedSymbol = NULL;
}

CEXMLDocument::~CEXMLDocument()
{
	TRACE("~CEXMLDocument()\n");
}

#if 0
int CEXMLDocument::FinalConstruct()
{
	ErrorCode hr;

#if 0

	hr = m_defaultStyle.CoCreateInstance(CLSID_LCSSStyleDeclaration);
	if (FAILED(hr)) return hr;

//	hr = m_textDocument.CoCreateInstance(CLSID_TextData);
//	if (FAILED(hr)) return hr;

	hr = CComObject<CWEUndoManager>::CreateInstance(&m_undoManager);
	if (FAILED(hr)) return hr;
	m_undoManager->AddRef();

	CComObject<CTextBookmarkList>::CreateInstance(&m_bookmarks);
	m_bookmarks->AddRef();
#endif
	return Success;
}

void CEXMLDocument::FinalRelease()
{
	ASSERT(0);
#if 0
	if (m_bookmarks)
	{
		m_bookmarks->Release();
		m_bookmarks = NULL;
	}

	if (m_undoManager)
	{
		m_undoManager->Release();
		m_undoManager = NULL;
	}
#endif
}
#endif

ErrorCode CEXMLDocument::CloseDocument()
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	if (xmldocument)
	{
		RemoveEventListener();
		xmldocument->put_errorHandler(NULL);
	}

	// ASSERT(0);
#if 0
	if (m_textDocument)
	{
		IDispEventImpl<1, CEXMLDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>::DispEventUnadvise(m_textDocument);
	}
#endif

	int i;

#if 0
	for (i = m_viewGroups.GetSize()-1; i >= 0; i--)
	{
		CEXMLViewGroup* pViewGroup = (CEXMLViewGroup*)m_viewGroups[i];
		m_viewGroups.RemoveAt(i);

		pViewGroup->DestroyWindow();
		pViewGroup->Release();
	}
#endif

#if 0	// Do elsewhere
	for (i = 0; i < gApp->m_documents.GetSize(); i++)
	{
		if (gApp->m_documents[i] == this)
		{
			gApp->m_documents.RemoveAt(i);

			Release();
			break;
		}
	}
#endif
#endif
	return Success;
}

#if 0
// TODO, have *pVal
Element* CEXMLDocument::CreateElement(Web::Element* domElement)
{
	ASSERT(0);
	return NULL;
#if 0
	CComPtr<IUnknown> oldData;
	domElement->getUserData(L"E", &oldData);
	if (oldData)
	{
		CComQIPtr<IEElement> eElement = oldData;
		ASSERT(eElement);

		return eElement.p;
	}

	IEElement* pElement = NULL;

	BSTR btagName;
	domElement->get_localName(&btagName);
	if (SysStringLen(btagName) == 0)
	{
		domElement->get_tagName(&btagName);
	}
	_bstr_t tagName = _bstr_t(btagName, false);

	CComBSTR namespaceURI;
	domElement->get_namespaceURI(&namespaceURI);

	if (!cmpbstr(namespaceURI, L"http://www.w3.org/2000/svg"))
	{
		if (!wcscmp(tagName, L"svg"))
		{
			CComObject<CESVGSVGElement>* p;
			CComObject<CESVGSVGElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"mask"))
		{
			CComObject<CESVGElement>* p;
			CComObject<CESVGElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"filter"))
		{
			CComObject<CESVGFilterElement>* p;
			CComObject<CESVGFilterElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"circle"))
		{
			CComObject<CESVGCircleElement>* p;
			CComObject<CESVGCircleElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"ellipse"))
		{
			CComObject<CESVGEllipseElement>* p;
			CComObject<CESVGEllipseElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"line"))
		{
			CComObject<CESVGLineElement>* p;
			CComObject<CESVGLineElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"rect"))
		{
			CComObject<CESVGRectElement>* p;
			CComObject<CESVGRectElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"image"))
		{
			CComObject<CESVGImageElement>* p;
			CComObject<CESVGImageElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"video"))
		{
			CComObject<CESVGVideoElement>* p;
			CComObject<CESVGVideoElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"foreignObject"))
		{
			CComObject<CESVGForeignObjectElement>* p;
			CComObject<CESVGForeignObjectElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"path"))
		{
			CComObject<CESVGPathElement>* p;
			CComObject<CESVGPathElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"polyline"))
		{
			CComObject<CESVGPolyElement>* p;
			CComObject<CESVGPolyElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"polygon"))
		{
			CComObject<CESVGPolyElement>* p;
			CComObject<CESVGPolyElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"g"))
		{
			CComObject<CESVGGElement>* p;
			CComObject<CESVGGElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"switch"))
		{
			CComObject<CESVGSwitchElement>* p;
			CComObject<CESVGSwitchElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"use"))
		{
			CComObject<CESVGUseElement>* p;
			CComObject<CESVGUseElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"symbol"))
		{
			CComObject<CESVGSymbolElement>* p;
			CComObject<CESVGSymbolElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"text"))
		{
			CComObject<CESVGTextElement>* p;
			CComObject<CESVGTextElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"linearGradient"))
		{
			CComObject<CESVGLinearGradientElement>* p;
			CComObject<CESVGLinearGradientElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"animateMotion"))
		{
			CComObject<CEAnimateMotionElement>* p;
			CComObject<CEAnimateMotionElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"set") ||
					!wcscmp(tagName, L"animate") ||
					!wcscmp(tagName, L"animateColor") ||
					!wcscmp(tagName, L"animateTransform"))
		{
			CComObject<CEAnimateElement>* p;
			CComObject<CEAnimateElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"feBlend") ||
					!wcscmp(tagName, L"feColorMatrix") ||
					!wcscmp(tagName, L"feConvolveMatrix") ||
					!wcscmp(tagName, L"feComposite") ||
					!wcscmp(tagName, L"feDisplacementMap") ||
					!wcscmp(tagName, L"feFlood") ||
					!wcscmp(tagName, L"feGaussianBlur") ||
					!wcscmp(tagName, L"feImage") ||
					!wcscmp(tagName, L"feMerge") ||
					!wcscmp(tagName, L"feMorphology") ||
					!wcscmp(tagName, L"feOffset") ||
					!wcscmp(tagName, L"feSpecularLighting") ||
					!wcscmp(tagName, L"feTurbulence"))
		{
			CComObject<CSVGFEElement>* p;
			CComObject<CSVGFEElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"script"))
		{
			CComObject<CEScriptElement>* p;
			CComObject<CEScriptElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else if (!wcscmp(tagName, L"style"))
		{
			CComObject<CEStyleElement>* p;
			CComObject<CEStyleElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else
		{
			CComObject<CESVGElement>* p;
			CComObject<CESVGElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
	}
	else if (!cmpbstr(namespaceURI, L"http://www.w3.org/2001/SMIL20/Language") ||
				!cmpbstr(namespaceURI, L"http://www.w3.org/2000/SMIL20/CR/Language"))
	{
		if (	!wcscmp(tagName, L"set") ||
				!wcscmp(tagName, L"animate") ||
				!wcscmp(tagName, L"animateColor"))
		{
			CComObject<CEAnimateElement>* p;
			CComObject<CEAnimateElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
		else
		{
			CComObject<CEElement>* p;
			CComObject<CEElement>::CreateInstance(&p);
			p->AddRef();
			pElement = p;
		}
	}
	else
	{
		CComObject<CEElement>* p;
		CComObject<CEElement>::CreateInstance(&p);
		p->AddRef();
		pElement = p;
	}

	if (pElement)
	{
		CComPtr<IUnknown> oldData;
		domElement->setUserData(L"E", pElement, NULL, &oldData);

		pElement->put_ownerDocument(this);
		pElement->put_domElement(domElement);
	}

	return pElement;
#endif
}
#endif

void CEXMLDocument::InitTree()
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	ASSERT(xmldocument);

	ASSERT(m_pTree == NULL);
	if (m_pTree == NULL)
	{
		// TODO call CreateElement ??
		CComObject<CEElement>::CreateInstance(&m_pTree);
		if (m_pTree)
		{
			m_pTree->AddRef();
			m_pTree->m_domElement = xmldocument;
			m_pTree->m_pDocument = this;
		//	m_pTree->m_expanded = TRUE;

			BuildElementChildren(m_pTree);
		}
	}
#endif
}

void CEXMLDocument::Prepare()
{
	ErrorCode hr;

	ASSERT(0);
#if 0
	CComPtr<ITextData> textData;
	get_textData(&textData);

	hr = IDispEventImpl<1, CEXMLDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>::DispEventAdvise(textData);
	ASSERT(SUCCEEDED(hr));
#endif
}

ErrorCode CEXMLDocument::NewDocument()
{
	CEDocument::NewDocument();
	Prepare();

	return Success;
}

#if 0
ErrorCode CEXMLDocument::LoadDocumentByteArray(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success)
{
	CEDocument::LoadDocumentByteArray(dataArray, success);
	if (*success)
	{
		Prepare();

		CreateXMLDocumentFromTextData();

	ASSERT(0);
#if 0
		Fire_doneParsingDOM();
#endif
	}

	return Success;
}
#endif

bool CEXMLDocument::Load(System::StringW* url)
{
//	m_uri = xmlSource;

	m_textData = new TextDocument;
	dynamic_cast<System::EventTargetImpl*>(m_textData)->addEventListener(WSTR("TextInserted"), this, false);
	dynamic_cast<System::EventTargetImpl*>(m_textData)->addEventListener(WSTR("TextDeleted"), this, false);

	m_fileTitle = url;

	XMLParser parser;
	parser.m_document = this;

//	parser.m_errorHandler = m_errorHandler;
	bool success = parser.load(url);
	m_textData->SetData(parser.m_textData, parser.m_textLen);
	return success;
}

#if 0
// IPersist
ErrorCode CEXMLDocument::GetClassID(CLSID __RPC_FAR *pClassID)
{
	if (pClassID == NULL) return E_POINTER;
//	*pClassID = CLSID_EXMLDocument;
	return Success;
}

ErrorCode CEXMLDocument::IsDirty( void)
{
	return E_NOTIMPL;
}

// IPersistStream

ErrorCode CEXMLDocument::Load( 
		/* [unique][in] */ IStream *pStm)
{
	ErrorCode hr;

	hr = LoadDocument(pStm);

	if (FAILED(hr))
		return hr;

	Prepare();

	hr = CreateXMLDocumentFromTextData();

	ASSERT(0);
#if 0
	Fire_doneParsingDOM();
#endif
	return hr;
}

// IPersistFile

ErrorCode CEXMLDocument::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
	ErrorCode hr;

	hr = LoadDocument((BSTR)/*_bstr_t*/(pszFileName));

	if (FAILED(hr))
		return hr;

	Prepare();

	hr = CreateXMLDocumentFromTextData();

	ASSERT(0);
#if 0
	Fire_doneParsingDOM();
#endif
	return hr;
}

ErrorCode CEXMLDocument::Save(LPCOLESTR pszFileName, BOOL fRemember)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::SaveCompleted(LPCOLESTR pszFileName)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::GetCurFile(LPOLESTR __RPC_FAR *ppszFileName)
{
	return E_NOTIMPL;
}

// IPersistMoniker
ErrorCode CEXMLDocument::Load( 
      /* [in] */ BOOL fFullyAvailable,
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc,
      /* [in] */ DWORD grfMode)
{
	ErrorCode hr;

	ASSERT(0);
#if 0
	m_textData.CoCreateInstance(CLSID_TextData);
	CComQIPtr<IPersistMoniker> persistMoniker = m_textData;
	hr = persistMoniker->Load(fFullyAvailable, pimkName, pibc, grfMode);
	if (SUCCEEDED(hr))
	{
		CComPtr<ILLSParser> parser;
		parser.CoCreateInstance(CLSID_LLSParser);

		parser->parseTextData(m_textData, &m_document);

		if (m_document)
		{
			LPOLESTR displayName;
			pimkName->GetDisplayName(pibc, NULL, &displayName);
			m_pathName = displayName;
			m_fileTitle = PathFindFileName(m_pathName);
			CoTaskMemFree(displayName);

			m_lockSource++;

			Prepare();

			InitTree();

			AddRenderBehavior();

			SetupEventListener();

			Fire_doneParsingDOM();

			m_lockSource--;
		}
	}

	return hr;


#if 0
	hr = m_document.CoCreateInstance(CLSID_LHTMLActiveDocument);
	if (SUCCEEDED(hr))
	{
		CComQIPtr<IOleObject> spOleObject = m_document;
		if (spOleObject)
		{
			spOleObject->SetClientSite(this);

			CComQIPtr<IPersistMoniker> persistMoniker = m_document;
			if (persistMoniker)
			{
				m_document->put_errorHandler(this);

				hr = persistMoniker->Load(fFullyAvailable, pimkName, pibc, grfMode);
				if (SUCCEEDED(hr))
				{
					LPOLESTR displayName;
					pimkName->GetDisplayName(pibc, NULL, &displayName);
					m_pathName = displayName;
					m_fileTitle = PathFindFileName(m_pathName);
					CoTaskMemFree(displayName);

					m_lockSource++;

					Prepare();

					InitTree();

					AddRenderBehavior();

					SetupEventListener();

					Fire_doneParsingDOM();

					m_lockSource--;

					return Success;
				}
			}
		}
	}
#endif
#endif
	return E_FAIL;
}

ErrorCode CEXMLDocument::Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::SaveCompleted( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::GetCurMoniker( 
      /* [out] */ IMoniker **ppimkName)
{
	return E_NOTIMPL;
}
#endif

/////////////////////

void CEXMLDocument::AddRenderBehavior()
{
	Web::Document* xmldocument = get_DOMDocument();

	Web::Element* documentElement = xmldocument->get_documentElement();

	if (documentElement)
//	CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
//	if (svgsvgElement)
	{
/*		VARIANT vFactory;

		// Convert pGridFactory to the proper VARIANT data type 
		// for IHTMLElement2::AddBehavior
		V_VT(&vFactory) = VT_UNKNOWN;
		V_UNKNOWN(&vFactory) = static_cast<CLXMLEditorApp*>(m_app.p)->m_pElementBehaviorFactory;

		// AddRef because we've copied the pGridFactory pointer 
		V_UNKNOWN(&vFactory)->AddRef();
*/
		long cookie;
	ASSERT(0);
#if 0
		documentElement/*svgsvgElement*/->addBehavior(L"#factory#svg_edit", &CComVariant(GetUnknown()), &cookie);
#endif
	}
}

ErrorCode CEXMLDocument::CreateXMLDocumentFromTextData()
{
	ErrorCode hr = Error;

	ASSERT(0);

#if 0	// Have this ??
	m_lockSource++;

	CComPtr<ILDOMImplementation> impl;
	impl.CoCreateInstance(CLSID_LDOMImplementation);
	if (impl)
	{
		CComPtr<ILDOMBuilder> builder;
		impl->createDOMBuilder(0, NULL, &builder);
		builder->put_errorHandler(this);

		builder->parseTextData(m_textDocument, &m_xmldocument);
		if (m_xmldocument)
		{
#ifdef _DEBUG
			ASSERT_NodeOffsets(m_xmldocument, NULL);
#endif

			m_xmldocument->put_errorHandler(this);

			InitTree();

			CComPtr<Web::Element> documentElement;
			m_xmldocument->get_documentElement(&documentElement);
			if (documentElement)
			{
				CComBSTR tagName;
				documentElement->get_tagName(&tagName);

				CComBSTR nsURI;
				documentElement->get_namespaceURI(&nsURI);

				/*
				BSTR btagName;
				m_element->get_tagName(&btagName);
				_bstr_t tagName = _bstr_t(btagName, false);
				*/

				if (nsURI.Length() && !wcscmp(nsURI, L"http://www.w3.org/1999/XSL/Transform"))
				{
					m_documentClass = gApp->m_xsltDocuments;
				}
				else
				{
					m_documentClass = NULL;	// hm..
				}

				AddRenderBehavior();

				// If xsd schema (TODO, improve)
				if (!wcscmp(tagName, L"schema"))
				{
					ErrorCode hr = m_schemaModel.CoCreateInstance(CLSID_ASXMLSchemaModel);
					if (SUCCEEDED(hr))
					{
						m_schemaModel->put_xmlDocument(m_xmldocument);
					}
				}
			}

			SetupEventListener();

#if 0
			CComPtr<IASDTDModel> dtdModel;
			dtdModel.CoCreateInstance(L"ASDTDMod.ASDTDModel");//CoCreateInstance(CLSID_ASDTDModel);

			VARIANT_BOOL bsuccess;
			//dtdModel->load(L"C:\\nitf-3-0.dtd", &bsuccess);
			dtdModel->load(L"C:\\svg10.dtd", &bsuccess);
			if (bsuccess)
			{
				CComQIPtr<ILDocumentAS> documentAS = m_xmldocument;
				if (documentAS)
				{
					documentAS->put_activeASModel(dtdModel);
				}
			}
#endif

#if 0
			if (m_pTree && !m_pTree->m_childList.IsEmpty())
			{
				SetTargetElement((CElement*)m_pTree->m_childList.GetHead(), 0);
			}
#endif

			hr = Success;
		}
	}

	m_lockSource--;
#endif
	return hr;
}

void OffsetNodeOffsets(Node* node, int afterOffset, int offset)
{
	for (int i = 0; i < 10; i++)
	{
		long oldoffset = node->getTextOffset(i);

		if (oldoffset >= afterOffset)
		{
			node->setTextOffset(i, oldoffset+offset);
		}
	}

	NamedNodeMap* attributes = node->get_attributes();

	if (attributes)
	{
		long length = attributes->get_length();

		for (int i = 0; i < length; i++)
		{
			Node* attr = attributes->item(i);

			for (int j = 0; j < 10; j++)
			{
				long oldoffset = attr->getTextOffset(j);

				if (oldoffset >= afterOffset)
				{
					attr->setTextOffset(j, oldoffset+offset);
				}
			}
		}
	}

	Node* child = node->get_firstChild();
	while (child)
	{
		OffsetNodeOffsets(child, afterOffset, offset);

		child = child->get_nextSibling();
	}
}

void OffsetChildNodesOffsets(Web::Node* node, int afterOffset, int offset)
{
	ASSERT(0);
#if 0
	CComPtr<Web::Node> child;
	node->get_firstChild(&child);
	while (child)
	{
		OffsetNodeOffsets(child, afterOffset, offset);

		CComPtr<Web::Node> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
#endif
}

void OffsetSingleNodeOffsets(Web::Node* node, int afterOffset, int offset)
{
	for (int i = 0; i < 10; i++)
	{
		long oldoffset;
		node->getTextOffset(i, &oldoffset);

		if (oldoffset >= afterOffset)
		{
			node->setTextOffset(i, oldoffset+offset);
		}
	}
}

void OffsetNodeOffsets(Node* node, Node* exceptnode, int afterOffset, int offset)
{
	ASSERT(0);
#if 0
	if (!IsUnknownEqualUnknown(node, exceptnode))
	{
		for (int i = 0; i < 10; i++)
		{
			long oldoffset;
			node->getTextOffset(i, &oldoffset);

			if (oldoffset >= afterOffset)
			{
				node->setTextOffset(i, oldoffset+offset);
			}
		}

		CComPtr<ILDOMNamedNodeMap> attributes;
		node->get_attributes(&attributes);

		if (attributes)
		{
			long length;
			attributes->get_length(&length);

			for (int i = 0; i < length; i++)
			{
				CComPtr<Web::Node> attr;
				attributes->item(i, &attr);

				if (!IsUnknownEqualUnknown(attr, exceptnode))
				{
					for (int j = 0; j < 10; j++)
					{
						long oldoffset;
						attr->getTextOffset(j, &oldoffset);

						if (oldoffset >= afterOffset)
						{
							attr->setTextOffset(j, oldoffset+offset);
						}
					}
				}
			}
		}

		CComPtr<Web::Node> child;
		node->get_firstChild(&child);
		while (child)
		{
			OffsetNodeOffsets(child, exceptnode, afterOffset, offset);

			CComPtr<Web::Node> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}
	}
#endif
}

void CEXMLDocument::UpdateTitles()
{
	for (int i = 0; i < m_viewGroups.GetSize(); i++)
	{
		m_viewGroups[i]->UpdateTitles(m_viewGroups.GetSize()==1? -1: i);
	}
}

void CEXMLDocument::RemoveViewGroup(CEXMLViewGroup* pViewGroup)
{
	for (int i = 0; i < m_viewGroups.GetSize(); i++)
	{
		if (m_viewGroups[i] == pViewGroup)
		{
			pViewGroup->Close();
			delete pViewGroup;//->Release();
			m_viewGroups.RemoveAt(i);

			if (m_viewGroups.GetSize() == 0)	// Close document
			{
	ASSERT(0);
#if 0
				Release();
#endif			// TODO m_app->RemoveDocument(...)

			//	m_app->RemoveDocument()
			}

			return;
		}
	}

	ASSERT(0);
}

Web::Node* BuildNode(Node* node, Web::Document* ownerDocument, System::StringW* key)
{
	if (node->get_nodeType() == Web::NODE_DOCUMENT)
	{
		//CEXMLDocument* from = dynamic_cast<CEXMLDocument*>(node);

		Web::Document* document = new Web::HTMLDocument;
		node->setUserData(key, document);

		for (int i = 0; i < node->get_childNodes()->get_length(); i++)
		{
			document->appendChild(BuildNode(node->get_childNodes()->item(i), document, key));
		}

		return document;
	}
	else if (node->get_nodeType() == Web::NODE_ELEMENT)
	{
		Web::Element* element = ownerDocument->createElementNS(dynamic_cast<Element*>(node)->get_namespaceURI(), node->get_nodeName());
		node->setUserData(key, element);

		int i;

		for (i = 0; i < node->get_attributes()->get_length(); i++)
		{
			element->get_attributes()->setNamedItemNS(BuildNode(node->get_attributes()->item(i), ownerDocument, key));
		}

		for (i = 0; i < node->get_childNodes()->get_length(); i++)
		{
			element->appendChild(BuildNode(node->get_childNodes()->item(i), ownerDocument, key));
		}

		return element;
	}
	else if (node->get_nodeType() == Web::NODE_TEXT)
	{
		Text* p = dynamic_cast<Text*>(node);
		Web::Text* text = ownerDocument->createTextNode(p->get_data());
		node->setUserData(key, text);
		return text;
	}
	else if (node->get_nodeType() == Web::NODE_COMMENT)
	{
		Comment* p = dynamic_cast<Comment*>(node);
		Web::Comment* comment = ownerDocument->createComment(p->get_data());
		node->setUserData(key, comment);
		return comment;
	}
	else if (node->get_nodeType() == Web::NODE_ATTRIBUTE)
	{
		Attr* p = dynamic_cast<Attr*>(node);
		Web::Attr* attr = ownerDocument->createAttribute(p->get_localName());
		attr->set_value(p->get_value());
		node->setUserData(key, attr);
		return attr;
	}

	ASSERT(0);
	return NULL;
}

int CEXMLDocument::ShowViews(IEFrame* /*frame*/)
{
//	ASSERT(0);
//	CComPtr<ILXFrameworkFrame> frame;
//	static_cast<CLXMLEditorApp*>(m_app.p)->m_spAddinSite->GetFrame(&frame);

//	CComPtr<ILXFrameworkApp> app;
//	frame->GetApp(&app);

#if 0
	CComPtr<ILXUIMDIFrameElement> frameelement;
	frame->GetMDIFrame(&frameelement);

	CComPtr<ILXUIDocument> appdocument;
	frameelement->get_ownerDocument(&appdocument);
#endif

//	CComPtr<ILXUIElement> mdiclient;
//	frameelement->getMDIClientElement(&mdiclient);

#if 0
	CComPtr<Web::Element> mdiclient = GetElementByTagNameNS(frameelement, L"http://www.lerstad.com/2004/lxui", L"mdiclient", FALSE);

	if (mdiclient)
	{
		CComPtr<ILXUIElement> mdichild;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"mdichild", (Web::Element**)&mdichild);

		mdiclient->appendChild(mdichild, NULL);
	}
#endif

	UI::CDocumentWorkspace* pWorkspace = &m_app->m_xmlDocumentWorkspace;

#if 0
	CComQIPtr<ILXAddin> addin = m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);
#endif

#if 0
	CComPtr<IUIManager> uiManager;
	addinSite->GetUIManager((IUnknown**)&uiManager);
#endif

#if 0
	CComQIPtr<IUIMDIFrame> mdiframe = pFrame;
#endif

	CEXMLViewGroup* viewGroup = new CEXMLViewGroup;
//	CComObject<CEXMLViewGroup>::CreateInstance(&viewGroup);
	if (viewGroup)
	{
//		viewGroup->AddRef();
		viewGroup->SetDocument(this);

		if (false)
		{
#if 0
			CComPtr<ILDOMDocument> document;
			get_DOMDocument(&document);

			CComQIPtr<ILDOMDocumentView> documentView = document;

			CComPtr<ILDOMAbstractView> view;
			documentView->createView(&view);
			view.Detach();	// TODO, hold onto this
#endif
		}

		m_viewGroups.Add(viewGroup);

	// Create all views

	// Layout
		{
			viewGroup->m_views.Add(new UI::Rectangle());
		}
#if 0
		{
			CEXMLLayoutView* layoutView = new CEXMLLayoutView;
			if (layoutView)
			{
				UI::DockPanel::SetDock(layoutView, UI::DockPanel::Fill);
				layoutView->m_viewGroup = viewGroup;
				layoutView->m_view = pWorkspace->m_views[0];

				layoutView->ShowViews(NULL/*frame*/);
				
				Web::CHTMLWindow* pBrowser = new Web::CHTMLWindow;
				{
					layoutView->m_viewDocument = dynamic_cast<Web::Document*>(BuildNode(this, NULL, L"Layout"));

					dynamic_cast<Web::DocumentStyleImpl*>(layoutView->m_viewDocument)->loadDefaultStylesheet();

					layoutView->m_viewDocument->m_pWindow = pBrowser;
				//	pBrowser->m_imageRect = CRect(0, 0, 400, 400);
					pBrowser->m_htmTree = (Web::CPElement*)layoutView->m_viewDocument->get_documentElement()->m_pNode;
					pBrowser->m_htmTree->m_pWindow = pBrowser;
					pBrowser->m_htmTree->GetCSSPropertiesAndChildren();
					pBrowser->m_htmTree->CalculateBoundsAndChildren();
				}

				addEventListener(OLESTR("TextInserted"), layoutView, true);

				layoutView->set_VisualTree(pBrowser);
			}
#if 0
			viewGroup->m_views.Add(layoutView);
#endif
			viewGroup->m_layoutView = layoutView;	// hm..

#if 0
			ILXUIElement* e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);
			e->setAttribute(L"style", L"-moz-box-flex: 1;");

		//	CComPtr<IUnknown> old;
		//	e->setUserData(L"n", viewGroup->GetUnknown(), NULL, &old);

	//		CComObject<CEXMLLayoutFactory>* factory;
	//		CComObject<CEXMLLayoutFactory>::CreateInstance(&factory);
	//		factory->AddRef();

		//	VARIANT vFactory;
		//	V_VT(&vFactory) = VT_UNKNOWN;
		//	V_UNKNOWN(&vFactory) = static_cast<CLXMLEditorApp*>(m_app.p)->m_pElementBehaviorFactory;
		//	V_UNKNOWN(&vFactory)->AddRef();

			long cookie;
			e->addBehavior(L"#factory#xml_layout", &CComVariant(layoutView->GetUnknown()), &cookie);
#endif
			viewGroup->m_views.Add(layoutView/*e.Detach()*/);
		}
#endif

	// Source
		{
			CSourceView* sourceView = new CSourceView(viewGroup);
			//CComObject<CSourceView>::CreateInstance(&sourceView);
			if (sourceView)
			{
				UI::DockPanel::SetDock(sourceView, UI::DockPanel::Fill);
				//sourceView->m_viewGroup = viewGroup;
				sourceView->m_view = pWorkspace->m_views[1];

#if 0	// TODO, not checked that I don't need this
				sourceView->SetOwnerWindow(m_app);
#endif

				sourceView->set_Background(new UI::SolidColorBrush(new UI::Color(0, 255, 0)));
			}
			/*
			viewGroup->m_views.Add(sourceView);
			*/
#if 0
			ILXUIElement* e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"vbox", IID_ILXUIElement, (void**)&e);
			e->setAttribute(L"style", L"-moz-box-flex: 1;");

		//	CComPtr<IUnknown> old;
		//	e->setUserData(L"n", viewGroup->GetUnknown(), NULL, &old);

			/*
			VARIANT vFactory;
			V_VT(&vFactory) = VT_UNKNOWN;
			V_UNKNOWN(&vFactory) = static_cast<CLXMLEditorApp*>(m_app.p)->m_pElementBehaviorFactory;
			V_UNKNOWN(&vFactory)->AddRef();
			*/

			long cookie;
			e->addBehavior(NULL, &CComVariant(sourceView->GetUnknown()), &cookie);
#endif
			viewGroup->m_views.Add(sourceView/*e.Detach()*/);
		}

	// GridView
		{
			/*
			CComObject<CXMLGridView>* xmlgridView;
			CComObject<CXMLGridView>::CreateInstance(&xmlgridView);
			if (xmlgridView)
			{
				xmlgridView->m_viewGroup = viewGroup;
			}
			viewGroup->m_views.Add(xmlgridView);
			*/
		//	CXMLGridCtl* p = new CXMLGridCtl;
			CGridDocument* gridDocument = new CGridDocument(this);
			gridDocument->BuildChildren();
		//	p->m_pTree = gridDocument->m_childNodes; 
			
			viewGroup->m_views.Add(gridDocument->m_childNodes);
#if 0
			ILXUIElement* e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

	// FramesDesign
		{
			/*
			CComObject<CHTMLFramesDesignView>* framesDesignView;
			CComObject<CHTMLFramesDesignView>::CreateInstance(&framesDesignView);
			if (framesDesignView)
			{
				framesDesignView->m_document = this;
				framesDesignView->m_viewGroup = viewGroup;
			}
			viewGroup->m_views.Add(framesDesignView);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		//  TimeGraph
		{
			CSmilTimeGraphView* p = new CSmilTimeGraphView;
			p->m_viewGroup = viewGroup;
			p->BuildTree();

			viewGroup->m_views.Add(p);
#if 0
			CComObject<CSmilTimeGraphView>* pTimeGraphView;
			CComObject<CSmilTimeGraphView>::CreateInstance(&pTimeGraphView);
			if (pTimeGraphView)
			{
				//pTimeGraphView->m_pDocument = this;
				pTimeGraphView->m_viewGroup = viewGroup;
			}
/*
			viewGroup->m_views.Add(pTimeGraphView);
*/

			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);
#if 0
			e->setAttribute(L"style", L"-moz-box-flex: 1;");

			/*
			CComPtr<IUnknown> old;
			e->setUserData(L"n", viewGroup->GetUnknown(), NULL, &old);

			VARIANT vFactory;
			V_VT(&vFactory) = VT_UNKNOWN;
			V_UNKNOWN(&vFactory) = static_cast<CLXMLEditorApp*>(m_app.p)->m_pElementBehaviorFactory;
			V_UNKNOWN(&vFactory)->AddRef();
			*/

			long cookie;
			e->addBehavior(L"#factory#xml_timegraph", &CComVariant(pTimeGraphView->GetUnknown()), &cookie);
#endif
			viewGroup->m_views.Add(e.Detach());
#endif
		}

	// Scripts
		{
			/*
			CComObject<CScriptOutlineDlg>* p;
			CComObject<CScriptOutlineDlg>::CreateInstance(&p);
			if (p)
			{
				//uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SCRIPTSDLG, &p->m_menu);
				p->m_viewGroup = viewGroup;
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

	// Objects
		{
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComObject<CSVGObjectsDlg>* p;
			CComObject<CSVGObjectsDlg>::CreateInstance(&p);
			if (p)
			{
				//uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGOBJECTSDLG, &p->m_menu);
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[6];
			}
#if 0
			viewGroup->m_views.Add(p);
#endif

			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);
#if 0
			e->setAttribute(L"style", L"-moz-box-flex: 1;");

			/*
			CComPtr<IUnknown> old;
			e->setUserData(L"n", viewGroup->GetUnknown(), NULL, &old);

			VARIANT vFactory;
			V_VT(&vFactory) = VT_UNKNOWN;
			V_UNKNOWN(&vFactory) = static_cast<CLXMLEditorApp*>(m_app.p)->m_pElementBehaviorFactory;
			V_UNKNOWN(&vFactory)->AddRef();
			*/

			long cookie;
			e->addBehavior(L"#factory#objects", &CComVariant(p->GetUnknown()), &cookie);
#endif
			viewGroup->m_views.Add(e.Detach());
#endif
		}

	// CSS Properties
		{
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			/*
			CComObject<CCSSPropertiesDlg>* p;
			CComObject<CCSSPropertiesDlg>::CreateInstance(&p);
			if (p)
			{
				//uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGOBJECTSDLG, &p->m_menu);
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[7];
			}
			viewGroup->m_views.Add(p);
			*/
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

	// SVG Swatches
		{
			/*
			CComObject<CSVGSwatchesDlg>* p;
			CComObject<CSVGSwatchesDlg>::CreateInstance(&p);
			if (p)
			{
				//uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &p->m_menu);
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[8];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// Stylesheets
		{
			/*
			CComObject<CEXMLDocumentStyleSheetsView>* p;
			CComObject<CEXMLDocumentStyleSheetsView>::CreateInstance(&p);
			if (p)
			{
			//	uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &p->m_menu);
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[9];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// Element Inspector
		{
			/*
			CComObject<CInspectorDlg>* p;
			CComObject<CInspectorDlg>::CreateInstance(&p);
			if (p)
			{
			//	uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &p->m_menu);
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[10];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"content", IID_ILXUIElement, (void**)&e);

			/*
			CComPtr<IUnknown> old;
			e->setUserData(L"n", viewGroup->GetUnknown(), NULL, &old);

			VARIANT vFactory;
			V_VT(&vFactory) = VT_UNKNOWN;
			V_UNKNOWN(&vFactory) = static_cast<CLXMLEditorApp*>(m_app.p)->m_pElementBehaviorFactory;
			V_UNKNOWN(&vFactory)->AddRef();
			*/

#if 0
			long cookie;
			e->addBehavior(L"#factory#xml_inspector", &CComVariant(viewGroup->GetUnknown()), &cookie);
#endif
			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// SVG Filters
		{
			/*
			CComObject<CSVGFiltersDlg>* p;
			CComObject<CSVGFiltersDlg>::CreateInstance(&p);
			if (p)
			{
			//	uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &p->m_menu);
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[11];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// Animatable attributes
		{
			/*
			CComObject<CAnimateAttributesDlg>* p;
			CComObject<CAnimateAttributesDlg>::CreateInstance(&p);
			if (p)
			{
			//	uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &p->m_menu);
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[12];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// Symbols
		{
			/*
			CComObject<CSVGSymbolsDlg>* p;
			CComObject<CSVGSymbolsDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[13];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// Gradient
		{
			/*
			CComObject<CEditGradientDlg>* p;
			CComObject<CEditGradientDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[14];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// FilterGraph
		{
			/*
			CComObject<CEditFilterDlg>* p;
			CComObject<CEditFilterDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[15];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// ClipPaths
		{
			/*
			CComObject<CSVGClipPathsDlg>* p;
			CComObject<CSVGClipPathsDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[16];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// Color
		{
			/*
			CComObject<CEColorDlg>* p;
			CComObject<CEColorDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[17];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// Test Attributes (for children of <switch>)
		{
			/*
			CComObject<CTestAttributesDlg>* p;
			CComObject<CTestAttributesDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[18];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// SMIL Transitions
		{
			/*
			CComObject<CSMILTransitionsDlg>* p;
			CComObject<CSMILTransitionsDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[19];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		// ElementTime Attributes
		{
			/*
			CComObject<CElementTimeDlg>* p;
			CComObject<CElementTimeDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[20];
			}
			viewGroup->m_views.Add(p);
			*/
			viewGroup->m_views.Add(new UI::Rectangle());
#if 0
			CComPtr<ILXUIElement> e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"p", IID_ILXUIElement, (void**)&e);

			viewGroup->m_views.Add(e.Detach());
#endif
		}

		pWorkspace->Create(m_app->m_Canvas, viewGroup);
	}

	UpdateTitles();

#if 0
	CComPtr<IUIViewSheet> documentsSheet;

	if (static_cast<CLXMLEditorApp*>(m_app.p)->m_documentsSheet == NULL)
	{
		pFrame->CreateViewSheet(L"", NULL, &documentsSheet);
		static_cast<CLXMLEditorApp*>(m_app.p)->m_documentsSheets.Add(documentsSheet);
	}
	else
	{
		documentsSheet = static_cast<CLXMLEditorApp*>(m_app.p)->m_documentsSheet;
	}

	if (documentsSheet)
	{
		CComObject<CEXMLViewGroup>* viewGroup;
		CComObject<CEXMLViewGroup>::CreateInstance(&viewGroup);
		if (viewGroup)
		{
			viewGroup->AddRef();

			viewGroup->SetDocument(this);

			CComPtr<IUIViewSheet> viewGroupSheet;
			pFrame->CreateViewSheet(m_fileTitle, viewGroup, &viewGroupSheet);

			viewGroup->m_sheets.Add(viewGroupSheet);

			CComPtr<ILDOMDocument> xmldocument;
			get_DOMDocument(&xmldocument);

			xmldocument->get_documentElement(&viewGroup->m_outerElement);

			// Add a source text bookmark on the viewgroup's outerElement, so that when the source
			// text is changed and the DOM is reparsed, we can find back to the DOM outerElement
			if (viewGroup->m_outerElement)
			{
				long startOffset;
				viewGroup->m_outerElement->getTextOffset(0, &startOffset);

				long endOffset;
				viewGroup->m_outerElement->getTextOffset(2, &endOffset);

				addBookmark(NULL, startOffset, endOffset-startOffset, &viewGroup->m_outerElementTextBookmark);
			}

			m_viewGroups.Add(viewGroup);

		//	gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&viewGroup->m_spFrame);

		//	CComObject<CUIMDIChild>* child;
		//	CComObject<CUIMDIChild>::CreateInstance(&child);
		//	child->AddRef();
		//	gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

			CComObject<CEXMLViewGroup>* child = viewGroup;

			CComPtr<Web::Element> documentElement;
			xmldocument->get_documentElement(&documentElement);

			if (documentElement)
			{
				CComBSTR nsURI;
				documentElement->get_namespaceURI(&nsURI);

#if 0
				if (!wcscmp(nsURI, L"http://www.w3.org/1999/XSL/Transform"))
				{
				// XSL Templates
					CComObject<CXSLTTemplatesDlg>* templatesView;
					CComObject<CXSLTTemplatesDlg>::CreateInstance(&templatesView);
					if (templatesView)
					{
						uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XSLTEMPLATESVIEW, &templatesView->m_menu);
						templatesView->m_document = this;
						templatesView->m_viewGroup = viewGroup;
						viewGroup->m_views.Add(templatesView);

						viewGroup->m_spViewGroupSite->AddPage(templatesView, NULL);

					//	viewGroup->m_splitx = 160;
					}
				}
#endif
			}

			{
			// Layout
				CComObject<CEXMLLayoutView>* layoutView;
				CComObject<CEXMLLayoutView>::CreateInstance(&layoutView);
				if (layoutView)
				{
					uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLLAYOUTVIEW, &layoutView->m_menu);
					layoutView->m_document = this;

					layoutView->m_viewGroup = viewGroup;
					viewGroup->m_views.Add(layoutView);

					viewGroup->m_layoutView = layoutView;

					CComPtr<IUIDlgSite> dlgsite;
					static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->CreateDlgSite(L"Layout", layoutView, &dlgsite);

					CComQIPtr<IUIDockBar>(viewGroupSheet)->DockControlBar(dlgsite, NULL);
				}

			// Source
				CComObject<CSourceView>* sourceView;
				CComObject<CSourceView>::CreateInstance(&sourceView);
				if (sourceView)
				{
					uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLSOURCEVIEW, &sourceView->m_menu);
					sourceView->m_document = this;

					sourceView->m_viewGroup = viewGroup;
					viewGroup->m_views.Add(sourceView);

					CComPtr<IUIDlgSite> dlgsite;
					static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->CreateDlgSite(L"Source", sourceView, &dlgsite);

					CComQIPtr<IUIDockBar>(viewGroupSheet)->DockControlBar(dlgsite, NULL);

				//	viewGroup->m_spViewGroupSite->AddPage(sourceView, NULL);
				}

			// GridView
				CComObject<CXMLGridView>* xmlgridView;
				CComObject<CXMLGridView>::CreateInstance(&xmlgridView);
				if (xmlgridView)
				{
					uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLGRIDVIEW, &xmlgridView->m_menu);
					//xmlgridView->m_document = this;

					xmlgridView->m_viewGroup = viewGroup;
					viewGroup->m_views.Add(xmlgridView);

					CComPtr<IUIDlgSite> dlgsite;
					static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->CreateDlgSite(L"XML Grid", xmlgridView, &dlgsite);

					CComQIPtr<IUIDockBar>(viewGroupSheet)->DockControlBar(dlgsite, NULL);

				//	viewGroup->m_spViewGroupSite->AddPage(xmlgridView, NULL);
				}

			// FramesDesign
				CComObject<CHTMLFramesDesignView>* framesDesignView;
				CComObject<CHTMLFramesDesignView>::CreateInstance(&framesDesignView);
				if (framesDesignView)
				{
					uiManager->FindMenu(_Module.GetResourceInstance(), IDR_FRAMESDESIGNVIEW, &framesDesignView->m_menu);
					framesDesignView->m_document = this;

					framesDesignView->m_viewGroup = viewGroup;
					viewGroup->m_views.Add(framesDesignView);

					CComPtr<IUIDlgSite> dlgsite;
					static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->CreateDlgSite(L"Frames", framesDesignView, &dlgsite);

					CComQIPtr<IUIDockBar>(viewGroupSheet)->DockControlBar(dlgsite, NULL);

			//		viewGroup->m_spViewGroupSite->AddPage(framesDesignView, NULL);
				}

	#if 0
				CComQIPtr<ILDocumentStyle> documentStyle = xmldocument;
				if (documentStyle)
				{
					CComObject<CEXMLDocumentStyleSheetsView>* cssView;
					CComObject<CEXMLDocumentStyleSheetsView>::CreateInstance(&cssView);
					if (cssView)
					{
						cssView->m_viewGroup = viewGroup;

						CComPtr<ILStyleSheetList> styleSheetList;
						documentStyle->get_styleSheets(&styleSheetList);

						uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLSTYLESHEETSVIEW, &cssView->m_menu);
						cssView->m_styleSheetList = styleSheetList;
						viewGroup->m_spViewGroupSite->AddPage(cssView, NULL);
					}
				}
	#endif
	#if 0
			// SMIL Layout regions
				CComObject<CSmilRegionsView>* pSMILRegionsView;
				CComObject<CSmilRegionsView>::CreateInstance(&pSMILRegionsView);
				if (pSMILRegionsView)
				{
					//gApp->m_frame->FindMenu(IDR_FRAMESDESIGNVIEW, &pSMILRegionsView->m_menu);
					//pSMILRegionsView->m_document = this;
					//pSMILRegionsView->

					pSMILRegionsView->m_viewGroup = viewGroup;
					viewGroup->m_views.Add(pSMILRegionsView);

					child->AddPage(pSMILRegionsView, NULL);
				}
	#endif
	#if 0
			// SMIL/HTML TimeGraph
				CComObject<CSmilTimeGraphView>* pTimeGraphView;
				CComObject<CSmilTimeGraphView>::CreateInstance(&pTimeGraphView);
				if (pTimeGraphView)
				{
					gApp->m_frame->FindMenu(IDR_TIMEGRAPHVIEW, &pTimeGraphView->m_menu);
					pTimeGraphView->m_document = this;

					pTimeGraphView->m_viewGroup = viewGroup;
					viewGroup->m_views.Add(pTimeGraphView);

					child->AddPage(pTimeGraphView, NULL);
				}
	#endif

			// Abstract Schema (AS) View
				CComObject<CDTDView>* asView;
				CComObject<CDTDView>::CreateInstance(&asView);
				if (asView)
				{
					uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SCHEMAVIEW, &asView->m_menu);
					asView->m_viewGroup = viewGroup;

					CComPtr<IUIDlgSite> dlgsite;
					static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->CreateDlgSite(L"AS Schema", asView, &dlgsite);

					CComQIPtr<IUIDockBar>(viewGroupSheet)->DockControlBar(dlgsite, NULL);

				//	viewGroup->m_spViewGroupSite->AddPage(asView, NULL);
				}

	#if 0
			// Schema Diagram
				CComObject<CSchemaDiagramView>* pSchemaDiagramView;
				CComObject<CSchemaDiagramView>::CreateInstance(&pSchemaDiagramView);
				if (pSchemaDiagramView)
				{
					gApp->m_frame->FindMenu(IDR_SCHEMAVIEW, &pSchemaDiagramView->m_menu);
					pSchemaDiagramView->m_viewGroup = viewGroup;
					pSchemaDiagramView->m_asModel = m_schemaModel;
					viewGroup->m_views.Add(pSchemaDiagramView);

					child->AddPage(pSchemaDiagramView, NULL);
				}

			// Preview
				CComObject<CWebPreviewView>* previewView;
				CComObject<CWebPreviewView>::CreateInstance(&previewView);
				if (previewView)
				{
					gApp->m_frame->FindMenu(IDR_XMLPREVIEWVIEW, &previewView->m_menu);
					previewView->m_document = this;

					previewView->m_viewGroup = viewGroup;
					viewGroup->m_views.Add(previewView);

					child->AddPage(previewView, NULL);
				}
	#endif
			}

		//	child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);

		//	child->UpdateFrameTitle();

		/*
			if (FALSE)
			{
				CComPtr<IUIMDIChild> childFrame;
				mdiframe->CreateChildFrame(viewGroup->m_spViewGroupSite, &childFrame);
			}
			else
			*/
			{
				CComPtr<IUIDlgSite> dlgsite;
				viewGroupSheet->GetDlgSite(&dlgsite);
				CComQIPtr<IUIDockBar>(documentsSheet)->DockControlBar(dlgsite, NULL);

			//	documentsSheet->AddPage(viewGroup->m_spViewGroupSite, NULL);
			}
		}

		if (static_cast<CLXMLEditorApp*>(m_app.p)->m_documentsSheet == NULL)
		{
			CComPtr<IUIMDIChild> childFrame;
			mdiframe->CreateChildFrame(documentsSheet, &childFrame);

			static_cast<CLXMLEditorApp*>(m_app.p)->m_documentsSheet = documentsSheet;

			{
				{
					CComPtr<IUIDlgSheet> sheet;
					static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->CreateDlgSheet(NULL, &sheet);
					sheet->SetMinimized(TRUE);

#if 0
					{
						CComPtr<IUIDlgClass> rdlg;
						static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->RegisterDlg(14, L"Objects", 0, &rdlg);
						sheet->AddPage(rdlg, NULL);
					}

					{
						CComPtr<IUIDlgClass> rdlg;
						static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->RegisterDlg(5, L"Navigator", 0, &rdlg);
						sheet->AddPage(rdlg, NULL);
					}
#endif

					/*
					{
						CComPtr<IUIDlgClass> rdlg;
						RegisterDlg(CLSID_SelectionDlg, L"Selection", 0, &rdlg);
						sheet->AddPage(rdlg, NULL);
					}
					*/

				//	sheet0->AddDialog(sheet, NULL);
		//			sheet->Show();

					CComPtr<IUIFrame> frame = childFrame;

					/*
					CComPtr<IUIDockBar> dockBar;
					DWORD dwStyle;
					frame->CanDock(CRect(0,0,0,0), CBRS_ORIENT_HORZ, &dockBar, &dwStyle);
					*/

					CComPtr<IUIDlgSite> sheetSite;
					sheet->GetDlgSite(&sheetSite);
					frame->DockControlBar(sheetSite, 0, &CRect(0,0,0,0));
				}
			}

		}
	}

#if 0
	{
		{
			//  TimeGraph
			CComObject<CSmilTimeGraphView>* pTimeGraphView;
			CComObject<CSmilTimeGraphView>::CreateInstance(&pTimeGraphView);
			if (pTimeGraphView)
			{
				uiManager->FindMenu(_Module.GetResourceInstance(), IDR_TIMEGRAPHVIEW, &pTimeGraphView->m_menu);
				pTimeGraphView->m_document = this;

				pTimeGraphView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(pTimeGraphView);
			}

			CComQIPtr<IUIMDIFrame> mdiframe = pFrame;

			CComPtr<IUIMDIChild> childFrame;
			mdiframe->CreateChildFrame(pTimeGraphView, &childFrame);
		}
	}
#endif
#endif
	return Success;
}

Element* CEXMLDocument::GetSvgElement()
{
	ASSERT(0);

//	if (m_pTree)// && !m_pTree->m_children.())
//		return m_pTree->m_firstElement;//return (IEElement*)(m_pTree->m_childList.GetHead());
//	else
		return NULL;
}

#if 0
// IUIActivatable
ErrorCode CEXMLDocument::OnActivate(IUIActiveManager *uiManager)
{
#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		uiManager->ActivateObject(GetUnknown(), m_targetElements[i]/*->GetUnknown()*/);
	}

	gApp->m_ActiveDocument = this;
#endif

	uiManager->ActivateObject(GetUnknown(), m_undoManager->GetUnknown());

	return Success;
}

ErrorCode CEXMLDocument::OnDeactivate(IUIActiveManager *uiManager)
{
	return Success;
}
#endif
	//

#if 0
BOOL CEXMLDocument::NewDocument()
{
#if 0
	m_xmldoc.CoCreateInstance(CLSID_SVGDocument);
	ASSERT(m_xmldoc != NULL);

	BOOL success;
	m_xmldoc->loadXML(L"<svg width=\"340\" height=\"340\" />", &success);

	if (success == FALSE)
	{
		return FALSE;
	}

	put_filePath(L"");
	m_unnamedIndex = 0;//++gApp->m_unnamedIndex;

	BuildTree();
	SetTargetElement((CElement*)m_pTree->m_childList.GetHead(), 0);

	SetupEventListener();
#endif
	return TRUE;
}
#endif

void CEXMLDocument::SetupEventListener()
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComQIPtr<ILDOMEventTarget> eventTarget = xmldocument;
	ASSERT(eventTarget != NULL);

// Capture
	eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
#endif
}

void CEXMLDocument::RemoveEventListener()
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComQIPtr<ILDOMEventTarget> eventTarget = xmldocument;
	ASSERT(eventTarget != NULL);

// Capture
	eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->removeEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->removeEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
#endif
}

MSWindows::DWORD WINAPI UpdateSourceThreadProc(
  LPVOID lpParameter   // thread data
)
{
	ASSERT(0);
#if 0
	CoInitialize(NULL);

	CEXMLDocument* document = (CEXMLDocument*)lpParameter;

	document->UpdateSourceFromDOM();

	document->m_hThreadUpdateSource = NULL;
	document->m_idThreadUpdateSource = 0L;

	/*
	BSTR bstr;
	document->m_xmldocument->saveXML(NULL, &bstr);
*/


	CoUninitialize();
#endif
	return 0;
}

void CEXMLDocument::BuildElementChildren(Element* eElement)
{
	ASSERT(0);
#if 0
	CComPtr<Web::Node> domNode;
	eElement->get_domNode(&domNode);

	CComPtr<Web::Node> child;
	domNode->get_firstChild(&child);

	while (child != NULL)
	{
		CComQIPtr<Web::Element> element = child;
		if (element)
		{
			IEElement* pElement2 = CreateElement(element);
			if (pElement2)
			{
				BuildElementChildren(pElement2);
				eElement->appendChild(pElement2);
			}
		}

		CComPtr<Web::Node> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	/*
	// Empty node at end
	{
		CComObject<CEElement>* p;
		CComObject<CEElement>::CreateInstance(&p);
		p->AddRef();
		eElement->appendChild(p);
	}
	*/
#endif
}

void CEXMLDocument::handleEvent(System::Event* evt)
{
	System::StringW* type = evt->get_type();

	System::EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (evt->get_target() == m_textData)
		{
			if (*type == L"TextInserted")
			{
				TextDataEvent* tdEvt = dynamic_cast<TextDataEvent*>(evt);
				OnTextDocumentInsertedText(tdEvt->m_offset, tdEvt->m_len);
			}
			else if (*type == L"TextDeleted")
			{
				TextDataEvent* tdEvt = dynamic_cast<TextDataEvent*>(evt);
				OnTextDocumentDeletedText(tdEvt->m_offset, tdEvt->m_len);
			}
		}
	}
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComPtr<ITextData> textData;
	get_textData(&textData);

//	Fire_domevent(evt);
//	return Success;	// Test if this improves speed
//	ASSERT_NodeOffsets(m_xmldocument, NULL);, a newly inserted element woun't succeed on this

#if 0
	if (m_hThreadUpdateSource)
	{
		PostThreadMessage(m_idThreadUpdateSource, WM_QUIT, 0, 0);

		WaitForSingleObject(m_hThreadUpdateSource, INFINITE);

		CloseHandle(m_hThreadUpdateSource);
		m_hThreadUpdateSource = NULL;
		m_idThreadUpdateSource = 0L;
	}
#endif

	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, L"DOMNodeRemoved") ||
		!wcscmp(type, L"DOMNodeRemovedFromDocument"))
	{
		Fire_domevent(evt);

		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<Web::Node> node = target;

		for (int i = 0; i < m_viewGroups.GetSize(); i++)
		{
			for (int j = m_viewGroups[i]->m_targetElements.GetSize()-1; j >= 0; j--)
			{
				CComPtr<IEElement> eElement;
				m_viewGroups[i]->m_targetElements[j]->get_eElement(&eElement);

				CComPtr<Web::Node> node2;
				eElement->get_domNode(&node2);

				if (node2 == node)
				{
					if (m_viewGroups[i]->m_pActiveElement == m_viewGroups[i]->m_targetElements[j])
					{
						m_viewGroups[i]->m_pActiveElement = NULL;
					}
					m_viewGroups[i]->m_targetElements[j]->Release();
					m_viewGroups[i]->m_targetElements.RemoveAt(j);

					m_viewGroups[i]->Fire_SelectionChanged();
				}
			}
		}
	}

	if (!wcscmp(type, L"DOMNodeInserted"))
	{
		{
			// TODO
			for (int i = 0; i < m_viewGroups.GetSize(); i++)
			{
#if 0
				m_viewGroups[i]->m_outerElement.Release();
				m_xmldocument->get_documentElement(&m_viewGroups[i]->m_outerElement);
#endif
			}
		}

		CComQIPtr<ILDOMMutationEvent> mut = evt;
	
		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<Web::Node> node = target;

		CComQIPtr<Web::Element> element = node;
		if (element)
		{
			IEElement* eElement = CreateElement(element);
			BuildElementChildren(eElement);
		}

#if 0 // TODO, have this
		ASSERT(m_pTree->FindDOMElement(node) == NULL);	// Can't already exist in tree
#endif

		ASSERT(m_pTree != NULL);

		CComPtr<Web::Node> parentNode;
		mut->get_relatedNode(&parentNode);

#if 0
		CComQIPtr<Web::Element> parentElement = parentNode;	// TODO ??, what if it's document

		CComPtr<IEElement> pParent;
		GetEElementFromDOMElement(parentElement, &pParent);
		if (pParent)
		{
			ASSERT(pParent);
			CComQIPtr<Web::Element> element = node;
			if (element)
			{
				IEElement* pElement = CreateElement(element);
				if (pElement)
				{
					BuildElementChildren(pElement);

					ASSERT(0);
#if 0	// Had this
					UPOSITION pos = pParent->m_childList.GetHeadPosition();

					CComQIPtr<Web::Node> child;
					element->get_previousSibling(&child);

					while (child != NULL)
					{
						CComQIPtr<Web::Element> el = child;
						if (el)
						{
							pParent->m_childList.GetNext(pos);
						}

						CComPtr<Web::Node> prevSibling;
						child->get_previousSibling(&prevSibling);
						child = prevSibling;
					}

					pElement->m_parent = pParent;
					if (pos)
						pParent->m_childList.InsertBefore(pos, pElement);
					else
						pParent->m_childList.AddTail(pElement);
#endif
				}
			}
		}
#endif

	//	m_hThreadUpdateSource = CreateThread(NULL, 0, UpdateSourceThreadProc, (void*)this, 0, &m_idThreadUpdateSource);
	//	UpdateSourceFromDOM();

		// Update source text
		{
		//	UpdateSourceFromDOM();

			if (m_lockSource == 0)
			{
				m_lockDOM++;

				CComPtr<Web::Node> previousSibling;
				node->get_previousSibling(&previousSibling);

				CComPtr<Web::Node> nextSibling;
				node->get_nextSibling(&nextSibling);

				if (previousSibling == NULL && nextSibling == NULL)
				{
					// TODO, this may not be correct

				// Rebuild the entire string for the parentNode
					long startTextOffset;
					parentNode->getTextOffset(0, &startTextOffset);

					long endTextOffset;
					parentNode->getTextOffset(9/*5*//*4*/, &endTextOffset);

					CComBSTR xmltext;
					xmldocument->MakeFormattedString(parentNode, &xmltext);

					int difflen = xmltext.Length() - (endTextOffset-startTextOffset);
					/*
					OffsetNodeOffsets(m_xmldocument, endTextOffset+1, difflen);

					OffsetNodeOffsets(parentNode, 0, startTextOffset);
					*/

					OffsetNodeOffsets(parentNode, 0, startTextOffset);
					OffsetNodeOffsets(xmldocument, parentNode, endTextOffset, difflen);

					textData->replaceText(startTextOffset, endTextOffset-startTextOffset, xmltext);
				}
				else
				{
					CComBSTR xmltext;
					xmldocument->MakeFormattedString(node, &xmltext);

					if (previousSibling)
					{
						// Insert the text right after previous sibling node
						long endPreviousTextOffset;
						previousSibling->getTextOffset(9/*5*//*4*/, &endPreviousTextOffset);

						OffsetNodeOffsets(node, 0, -(int)xmltext.Length());
						OffsetNodeOffsets(xmldocument, previousSibling, endPreviousTextOffset, xmltext.Length());

						OffsetNodeOffsets(node, -(int)xmltext.Length(), xmltext.Length()+endPreviousTextOffset);

#ifdef _DEBUG
						ASSERT_NodeOffsets(xmldocument, NULL);
#endif
						textData->insertText(endPreviousTextOffset, xmltext, xmltext.Length());
					}
					else
					{
					// TODO, this may not be correct
						// Insert the text right before next sibling node
						long startNextTextOffset;
						nextSibling->getTextOffset(0, &startNextTextOffset);

						/*
						OffsetNodeOffsets(m_xmldocument, startNextTextOffset, xmltext.Length());
						OffsetNodeOffsets(node, 0, startNextTextOffset);
						*/
						OffsetNodeOffsets(node, 0, startNextTextOffset);
						OffsetNodeOffsets(xmldocument, node, startNextTextOffset, xmltext.Length());

#ifdef _DEBUG
						ASSERT_NodeOffsets(xmldocument, NULL);
#endif
						textData->insertText(startNextTextOffset, xmltext, xmltext.Length());
					}
				}

				m_lockDOM--;
			}
		}

		Fire_domevent(evt);
	}
	else if (!wcscmp(type, L"DOMNodeRemoved"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<Web::Node> node = target;

		CComPtr<Web::Node> parentNode;
		mut->get_relatedNode(&parentNode);

		ASSERT(m_pTree != NULL);

		CComQIPtr<Web::Element> parentElement = parentNode;

		/*
		CComPtr<IEElement> eParentElement;
		GetEElementFromDOMElement(parentElement, &eParentElement);
		eParentElement->
		*/

		{
			// TODO
			for (int i = 0; i < m_viewGroups.GetSize(); i++)
			{
#if 0	// Had this ??
				m_viewGroups[i]->DeselectAll();
#endif

#if 0
				m_viewGroups[i]->m_outerElement.Release();
				m_xmldocument->get_documentElement(&m_viewGroups[i]->m_outerElement);
#endif
			}
		}

#if 0	// Had this ?
		CElementImpl* pElement = m_pTree->FindDOMElement(node);
	//	ASSERT(pElement);
		if (pElement)
		{
			UPOSITION pos = pElement->m_parent->m_childList.Find(pElement);
			pElement->m_parent->m_childList.RemoveAt(pos);
			pElement->Release();
		}
#endif

	//	m_hThreadUpdateSource = CreateThread(NULL, 0, UpdateSourceThreadProc, (void*)this, 0, &m_idThreadUpdateSource);

		// Update source text
		{
		//	UpdateSourceFromDOM();

			if (m_lockSource == 0)
			{
				m_lockDOM++;

				long startTextOffset;
				node->getTextOffset(0, &startTextOffset);

				long endTextOffset;
				node->getTextOffset(9, &endTextOffset);

				OffsetNodeOffsets(xmldocument, node, endTextOffset, -(endTextOffset-startTextOffset));
#ifdef _DEBUG
				ASSERT_NodeOffsets(xmldocument, NULL);
#endif
				textData->deleteText(startTextOffset, endTextOffset-startTextOffset);

				m_lockDOM--;
			}
		}
	}
	else if (!wcscmp(type, L"DOMAttrModified"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		LDOMAttrChangeType attrChangeType;
		mut->get_attrChange(&attrChangeType);

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<Web::Node> node = target;

		CComPtr<Web::Node> attrNode;
		mut->get_relatedNode(&attrNode);
		CComQIPtr<ILDOMAttr> attr = attrNode;

		if (m_lockSource == 0)
		{
			m_lockDOM++;

			if (attrChangeType == CHANGE_MODIFICATION)
			{
				long startTextOffset;
				attrNode->getTextOffset(3, &startTextOffset);

				long endTextOffset;
				attrNode->getTextOffset(4, &endTextOffset);

				CComBSTR xmltext;
				mut->get_newValue(&xmltext);
				//m_xmldocument->saveXML(attr, &xmltext);


				int difflen = xmltext.Length() - (endTextOffset-startTextOffset);

				OffsetNodeOffsets(xmldocument, startTextOffset+1, difflen);
#ifdef _DEBUG
				ASSERT_NodeOffsets(xmldocument, NULL);
#endif
				textData->replaceText(startTextOffset, endTextOffset-startTextOffset, xmltext);
#ifdef _DEBUG
				ASSERT_NodeOffsetsTextLen(xmldocument);
#endif
			}
			else if (attrChangeType == CHANGE_ADDITION)
			{
				CComBSTR xmltext2;
				xmldocument->MakeFormattedString(attrNode, &xmltext2);

				OffsetNodeOffsets(attrNode, 0, 1);
				attrNode->setTextOffset(0, 0);

#ifdef _DEBUG
				ASSERT_NodeOffsets(attrNode, NULL);
#endif
				CComBSTR xmltext = L" ";
				xmltext.Append(xmltext2);

				long textOffset;
				node->getTextOffset(3/*2*/, &textOffset);

				ATLTRACE("ADDITION: '%S' %d %d\n", (BSTR)xmltext, textOffset, xmltext.Length());

				OffsetNodeOffsets(attrNode, 0, textOffset);
#ifdef _DEBUG
				ASSERT_NodeOffsets(attrNode, NULL);
#endif
				OffsetNodeOffsets(xmldocument, attrNode, textOffset+1, xmltext.Length());
			//	OffsetSingleNodeOffsets(node, textOffset, xmltext.Length());//node->setTextOffset(2, textOffset+xmltext.Length());
#ifdef _DEBUG
				ASSERT_NodeOffsets(xmldocument, NULL);
#endif
				textData->insertText(textOffset, xmltext, xmltext.Length());
#ifdef _DEBUG
				ASSERT_NodeOffsetsTextLen(xmldocument);
#endif
			}
			else if (attrChangeType == CHANGE_REMOVAL)
			{
				CComBSTR name;
				attrNode->get_nodeName(&name);
				long startTextOffset;
				attrNode->getTextOffset(0, &startTextOffset);
				//startTextOffset -= 1;	// preceding ' '

				long endTextOffset;
				attrNode->getTextOffset(5, &endTextOffset);

				ASSERT(endTextOffset >= startTextOffset);

				ATLTRACE("REMOVAL (%S): %d %d\n", (BSTR)name, startTextOffset, endTextOffset);

				OffsetNodeOffsets(xmldocument, endTextOffset, -(endTextOffset-startTextOffset));
#ifdef _DEBUG
				ASSERT_NodeOffsets(xmldocument, attrNode);
#endif
				textData->deleteText(startTextOffset, endTextOffset-startTextOffset);
#ifdef _DEBUG
				ASSERT_NodeOffsetsTextLen(xmldocument);
#endif
			}

			m_lockDOM--;
		}

		Fire_domevent(evt);
	}
	else if (!wcscmp(type, L"DOMCharacterDataModified"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMCharacterData> node = target;

		if (m_lockSource == 0)
		{
			m_lockDOM++;

			long startTextOffset;
			node->getTextOffset(1, &startTextOffset);

			long endTextOffset;
			node->getTextOffset(7/*8*/, &endTextOffset);	// TODO, this should eventually be 8

			CComBSTR data;
			//node->get_data(&data);	// TODO, can optimize
			xmldocument->MakeFormattedString(node, &data);
			OffsetNodeOffsets(node, NULL, 0, startTextOffset);

			int difflen = data.Length() - (endTextOffset-startTextOffset);
			//OffsetNodeOffsets(node, , textOffset);
			OffsetNodeOffsets(xmldocument, node/*NULL*/, startTextOffset+1, difflen);
#ifdef _DEBUG
			ASSERT_NodeOffsets(xmldocument, NULL);
#endif
			textData->replaceText(startTextOffset, endTextOffset-startTextOffset, data);

			m_lockDOM--;
		}

		Fire_domevent(evt);
	}
	else if (!wcscmp(type, L"DOMElementNameChanged"))
	{
		CComQIPtr<ILDOMMutationNameEvent> mutName = evt;

		CComPtr<ILDOMEventTarget> target;
		mutName->get_target(&target);
		CComQIPtr<Web::Element> node = target;

		if (m_lockSource == 0)
		{
			m_lockDOM++;

			long startTextOffset;
			node->getTextOffset(1, &startTextOffset);

			long endTextOffset;
			node->getTextOffset(2, &endTextOffset);

			long startTextOffset1;
			node->getTextOffset(6, &startTextOffset1);

			long endTextOffset1;
			node->getTextOffset(7, &endTextOffset1);

			CComBSTR xmltext;
			node->get_nodeName(&xmltext);

			int difflen = xmltext.Length() - (endTextOffset-startTextOffset);

			if (TRUE)	// EndTag
			{
				OffsetNodeOffsets(xmldocument, startTextOffset1+1, difflen);
#ifdef _DEBUG
				ASSERT_NodeOffsets(xmldocument, NULL);
#endif
				textData->replaceText(startTextOffset1, endTextOffset1-startTextOffset1, xmltext);
			}

			OffsetNodeOffsets(xmldocument, startTextOffset+1, difflen);
#ifdef _DEBUG
			ASSERT_NodeOffsets(xmldocument, NULL);
#endif
			textData->replaceText(startTextOffset, endTextOffset-startTextOffset, xmltext);

			m_lockDOM--;
		}

		Fire_domevent(evt);
	}
	else if (!wcscmp(type, L"DOMNodeRemovedFromDocument"))
	{
		Fire_domevent(evt);
	}
	else
	{
		Fire_domevent(evt);
	}
#endif
}

#if 0
double CEXMLDocument::GetWidth()
{
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComQIPtr<ILSVGDocument> svgdoc = xmldocument;
	if (svgdoc)
	{
		CComQIPtr<ILSVGSVGElement> svg;
		svgdoc->get_documentElement((Web::Element**)&svg);

		if (svg)
		{
			CComQIPtr<ILSVGAnimatedLength> width;
			svg->get_width(&width);

			CComQIPtr<ILSVGLength> animVal;
			width->get_animVal(&animVal);

			double value;
			animVal->get_value(&value);

			return value;
		}
	}

	return 0;
}

double CEXMLDocument::GetHeight()
{
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComQIPtr<ILSVGDocument> svgdoc = xmldocument;
	if (svgdoc)
	{
		CComQIPtr<ILSVGSVGElement> svg;
		svgdoc->get_documentElement((Web::Element**)&svg);
		if (svg)
		{
			CComQIPtr<ILSVGAnimatedLength> height;
			svg->get_height(&height);

			CComQIPtr<ILSVGLength> animVal;
			height->get_animVal(&animVal);

			double value;
			animVal->get_value(&value);

			return value;
		}
	}

	return 0;
}
#endif

ErrorCode CEXMLDocument::SetElementID(Web::Element* element, /*[out,retval]*/ System::StringW** pVal)
{
	ASSERT(0);
#if 0
	ASSERT(element != NULL);
	if (element == NULL) return E_POINTER;

	CComBSTR id;
	element->getAttribute(L"id", &id);
	if (id.Length())	// ID already set
	{
		if (pVal)
			*pVal = id.Detach();
		return Success;
	}

	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	// Create new unique ID
	int n = 1;
	do
	{
		WCHAR buf[32];
		swprintf(buf, L"XML_ID_%d", n);
		id = buf;

		CComPtr<Web::Element> element;
		xmldocument->getElementById(id, &element);
		if (element == NULL)
			break;

		n++;
	}
	while (1);

// TODO, create undo

	element->setAttribute(L"id", id);
	if (pVal)
		*pVal = id.Detach();
#endif
	return Success;
}

ErrorCode CEXMLDocument::FindOrCreateSVGDefs(Web::SVGElement* *pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComPtr<Web::SVGElement> svgDefsElement;

	CComPtr<Web::NodeList> nodeList;
	xmldocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"defs", &nodeList);
	if (nodeList)
	{
		long length;
		nodeList->get_length(&length);

		if (length)
		{
			nodeList->item(length-1, (Web::Node**)&svgDefsElement);
		}
	}

	if (svgDefsElement == NULL)	// Create a <defs> element
	{
		xmldocument->createElementNS(L"http://www.w3.org/2000/svg", L"defs", (Web::Element**)&svgDefsElement);
		if (svgDefsElement)
		{
			CComPtr<Web::Element> svgsvgElement;
			xmldocument->get_documentElement(&svgsvgElement);

			CComPtr<Web::Node> firstChild;
			svgsvgElement->get_firstChild(&firstChild);

			CComPtr<IOleUndoManager> undoManager = m_undoManager;
			//m_document->get_undoManager(&undoManager);

			CComObject<CWEUndoNewElement>* pUndo;
			CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
			if (pUndo)
			{
				pUndo->m_pDocument = this;//static_cast<CEXMLDocument*>(m_document.p);

				pUndo->DoInitial(undoManager, svgDefsElement, svgsvgElement, firstChild);
			}
		}
	}

	*pVal = svgDefsElement;
	(*pVal)->AddRef();
#endif
	return Success;
}

#if 0
ErrorCode CEXMLDocument::CreateElementNS(Web::Node* parentNode, BSTR namespaceURI, BSTR namespaceURI, Web::Element* *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComPtr<Web::SVGElement> svgDefsElement;

	Web::Element* element = FindByTagNameNS(parentNode,

	CComPtr<Web::NodeList> nodeList;
	xmldocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"defs", &nodeList);
	if (nodeList)
	{
		long length;
		nodeList->get_length(&length);

		if (length)
		{
			nodeList->item(length-1, (Web::Node**)&svgDefsElement);
		}
	}

	if (svgDefsElement == NULL)	// Create a <defs> element
	{
		xmldocument->createElementNS(L"http://www.w3.org/2000/svg", L"defs", (Web::Element**)&svgDefsElement);
		if (svgDefsElement)
		{
			CComPtr<Web::Element> svgsvgElement;
			xmldocument->get_documentElement(&svgsvgElement);

			CComPtr<Web::Node> firstChild;
			svgsvgElement->get_firstChild(&firstChild);

			CComPtr<IOleUndoManager> undoManager = m_undoManager;
			//m_document->get_undoManager(&undoManager);

			CComObject<CWEUndoNewElement>* pUndo;
			CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
			if (pUndo)
			{
				pUndo->m_pDocument = this;//static_cast<CEXMLDocument*>(m_document.p);

				pUndo->DoInitial(undoManager, svgDefsElement, svgsvgElement, firstChild);
			}
		}
	}

	*pVal = svgDefsElement;
	(*pVal)->AddRef();

	return Success;
}
#endif

Node* GetNodeFromOffsets(Node* element, long startoffset, long endoffset, long index0, long index1);
Node* GetNodeFromOffsets(Node* node, bool bAttrs, long startoffset, long endoffset, long index0, long index1);

void CEXMLDocument::OnTextDocumentContentChanged()
{
	ASSERT(0);
/*	for (int i = 0; i < m_textMarkers.GetSize(); i++)
	{
		delete m_textMarkers[i];
	}
	m_textMarkers.RemoveAll();
*/
	TextHasChangedReparseDOM();
}

void CEXMLDocument::OnTextDocumentInsertedText(long offset, long len)
{
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);
#endif

	ITextData* textData = get_textData();

#if 0
	for (int i = 0; i < m_bookmarks->m_items.GetSize(); i++)
	{
		// Text inserted before bookmark
		if (offset < m_bookmarks->m_items[i]->m_offset)
		{
			m_bookmarks->m_items[i]->m_offset += len;
		}
		// Text inserted inside bookmark
		else if (offset < m_bookmarks->m_items[i]->m_offset+m_bookmarks->m_items[i]->m_length)
		{
			m_bookmarks->m_items[i]->m_length += len;
		}
	}
#endif

	if (m_lockDOM == 0)
	{
		Attr* attr = dynamic_cast<Attr*>(GetNodeFromOffsets(this, offset, offset, 3, 4));
		if (attr)
		{
			long startTextOffset = attr->getTextOffset(3);
			long startEndOffset = attr->getTextOffset(4);
			WCHAR* data = textData->GetData();

			m_lockSource++;

			System::StringW* attrValue = new System::StringW(string_copy(&data[startTextOffset], (startEndOffset-startTextOffset)+len));

			attr->set_value(attrValue);

			OffsetNodeOffsets(this, startTextOffset+1, len);

			m_lockSource--;
		}
		else if (CharacterData* charData = dynamic_cast<CharacterData*>(GetNodeFromOffsets(this, offset, offset, 2, 4)))
		{
			long startTextOffset = charData->getTextOffset(2);
			long startEndOffset = charData->getTextOffset(4);
			WCHAR* data = textData->GetData();

			m_lockSource++;

			charData->insertData(offset - startTextOffset, new System::StringW(string_copy(data + offset, len)));

			OffsetNodeOffsets(this, startTextOffset+1, len);

			m_lockSource--;
		}
		else
		{
			ASSERT(0);
#if 0
			m_lockSource++;

			// Find the nearest anccestor element of the inserted text

			Web::Node* inNode = GetNodeFromOffsets(xmldocument, FALSE, offset, offset, 0, 8);
			ASSERT(inNode);

			CComPtr<Web::Node> parentNode;
			inNode->get_parentNode(&parentNode);

			OffsetNodeOffsets(xmldocument, offset+1, len);

			BSTR data;
			textData->get_data(&data);

			long outerStart;
			inNode->getTextOffset(0, &outerStart);

			long outerEnd;
			inNode->getTextOffset(9, &outerEnd);

			OffsetErrors(offset, len);
			RemoveErrorsInRange(outerStart, outerEnd/*-len*/);

		// TODO, I should be able to read from data directly instead of creating a temporay string
			CComBSTR str = SysAllocStringLen(&data[outerStart], outerEnd-outerStart);

			//MessageBox(NULL, _bstr_t(str), "", MB_OK);

			m_addOffset = outerStart;

			CComPtr<ILDOMDocumentFragment> fragment;
			ErrorCode hr = xmldocument->parseFragment(str, parentNode, &fragment);

			m_addOffset = 0;

			if (SUCCEEDED(hr))
			{
				OffsetChildNodesOffsets(fragment, 0, outerStart);

				// Validate the parsed nodes
				{
					CComPtr<Web::Node> node;
					fragment->get_firstChild(&node);
					while (node)
					{
						CComQIPtr<ILNodeEditVAL> nodeVAL = node;
						if (nodeVAL)
						{
							VARIANT_BOOL bValid;
							nodeVAL->isNodeValid(VARIANT_TRUE, STRICT_VALIDITY_CHECK, &bValid);
						}

						CComPtr<Web::Node> nextSibling;
						node->get_nextSibling(&nextSibling);
						node = nextSibling;
					}
				}

				CComPtr<Web::Node> replacedChild;
				parentNode->replaceChild(fragment, inNode, &replacedChild);
			}
			else
			{
				CComPtr<ILDOMNotWellformed> nwnode;
				xmldocument->createNotWellformed(str, &nwnode);

				nwnode->setTextOffset(0, 0);
				nwnode->setTextOffset(1, 0);
				nwnode->setTextOffset(2, 0);
				nwnode->setTextOffset(3, str.Length());
				nwnode->setTextOffset(4, str.Length());
				nwnode->setTextOffset(5, str.Length());
				nwnode->setTextOffset(6, str.Length());
				nwnode->setTextOffset(7, str.Length());
				nwnode->setTextOffset(8, str.Length());
				nwnode->setTextOffset(9, str.Length());

			//	OffsetChildNodesOffsets(nwnode, 0, outerStart);
				OffsetNodeOffsets(nwnode, NULL, 0, outerStart);

			//	CComPtr<Web::Node> removedChild;
			//	parentNode->removeChild(inNode, &removedChild);
				CComPtr<Web::Node> replacedChild;
				parentNode->replaceChild(nwnode, inNode, &replacedChild);
			}

			m_lockSource--;
#endif
		}

#if 0	// TODO had this
		Fire_doneParsingDOM();
#endif
	}
}

Web::Node* FindCommonContainer(Web::Node* node1, Web::Node* node2);
Web::Node* FindCommonContainerOuter(Web::Node* node1, Web::Node* node2);

void CEXMLDocument::OnTextDocumentDeletedText(long offset, long len)
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComPtr<ITextData> textData;
	get_textData(&textData);

	for (int i = m_bookmarks->m_items.GetSize()-1; i >= 0; i--)
	{
		// Text deleted before bookmark
		if (offset+len < m_bookmarks->m_items[i]->m_offset)
		{
			m_bookmarks->m_items[i]->m_offset -= len;
		}
		// Text deleted inside bookmark
		else if (offset+len < m_bookmarks->m_items[i]->m_offset+m_bookmarks->m_items[i]->m_length)
		{
			m_bookmarks->m_items[i]->m_length -= len;
		}
		// Text deleted partially inside bookmark
		else if (offset < m_bookmarks->m_items[i]->m_offset+m_bookmarks->m_items[i]->m_length)
		{
			m_bookmarks->m_items[i]->m_length -=
				(m_bookmarks->m_items[i]->m_offset+m_bookmarks->m_items[i]->m_length) - (offset) ;
		}

		if (m_bookmarks->m_items[i]->m_length <= 0)
		{
			m_bookmarks->m_items[i]->Release();
			m_bookmarks->m_items.RemoveAt(i);
		}
	}

	if (m_lockDOM == 0)
	{
		CComQIPtr<ILDOMAttr> attr = GetNodeFromOffsets(xmldocument, offset, offset+len, 3, 4);

		if (attr)
		{
			long startTextOffset;
			attr->getTextOffset(3, &startTextOffset);

			long startEndOffset;
			attr->getTextOffset(4, &startEndOffset);

			BSTR data;
			textData->get_data(&data);

			m_lockSource++;

			BSTR battrValue = SysAllocStringLen(&data[startTextOffset], (startEndOffset-startTextOffset)-len);

			attr->put_value(battrValue);

			OffsetNodeOffsets(xmldocument, startTextOffset+1, -len);

			SysFreeString(battrValue);

			m_lockSource--;
		}
		else
		{
			m_lockSource++;

			// Find the nearest ancestor element of the deleted text

			Web::Node* startNode = GetNodeFromOffsets(xmldocument, FALSE, offset, offset, 0, 8);
			Web::Node* endNode = GetNodeFromOffsets(xmldocument, FALSE, offset+len, offset+len, 0, 8);

			ASSERT(startNode);
			ASSERT(endNode);

			OffsetNodeOffsets(xmldocument, offset+1, -len);

			CComQIPtr<Web::Node> commonContainer = FindCommonContainer(startNode, endNode);

			ASSERT(commonContainer);

			long outerStart;
			commonContainer->getTextOffset(0, &outerStart);

			long outerEnd;
			commonContainer->getTextOffset(9, &outerEnd);

			OffsetErrors(offset+1, -len);
			RemoveErrorsInRange(outerStart, outerEnd);

			//outerEnd -= len;	// ? Do this after

			BSTR data;
			textData->get_data(&data);

		// TODO, I should be able to read from data directly instead of creating a temporay string
			CComBSTR str = SysAllocStringLen(&data[outerStart], outerEnd-outerStart);

		//	MessageBox(NULL, _bstr_t(str), "", MB_OK);

			CComPtr<Web::Node> parentNode;
			commonContainer->get_parentNode(&parentNode);

			m_addOffset = outerStart;

			CComPtr<ILDOMDocumentFragment> fragment;
			ErrorCode hr = xmldocument->parseFragment(str, parentNode, &fragment);

			m_addOffset = 0;

			if (SUCCEEDED(hr))
			{
				OffsetChildNodesOffsets(fragment, 0, outerStart);

				// Validate the parsed nodes
				{
					CComPtr<Web::Node> node;
					fragment->get_firstChild(&node);
					while (node)
					{
						CComQIPtr<ILNodeEditVAL> nodeVAL = node;
						if (nodeVAL)
						{
							VARIANT_BOOL bValid;
							nodeVAL->isNodeValid(VARIANT_TRUE, STRICT_VALIDITY_CHECK, &bValid);
						}

						CComPtr<Web::Node> nextSibling;
						node->get_nextSibling(&nextSibling);
						node = nextSibling;
					}
				}

				CComPtr<Web::Node> replacedChild;
				parentNode->replaceChild(fragment, commonContainer, &replacedChild);
			}
			else
			{
				CComPtr<ILDOMNotWellformed> nwnode;
				xmldocument->createNotWellformed(str, &nwnode);

				nwnode->setTextOffset(0, 0);
				nwnode->setTextOffset(1, 0);
				nwnode->setTextOffset(2, 0);
				nwnode->setTextOffset(3, str.Length());
				nwnode->setTextOffset(4, str.Length());
				nwnode->setTextOffset(5, str.Length());
				nwnode->setTextOffset(6, str.Length());
				nwnode->setTextOffset(7, str.Length());
				nwnode->setTextOffset(8, str.Length());
				nwnode->setTextOffset(9, str.Length());

				OffsetNodeOffsets(nwnode, NULL, 0, outerStart);

			//	CComPtr<Web::Node> removedChild;
			//	parentNode->removeChild(inNode, &removedChild);
				CComPtr<Web::Node> replacedChild;
				parentNode->replaceChild(nwnode, commonContainer, &replacedChild);

			//	CComPtr<Web::Node> removedChild;
			//	parentNode->removeChild(commonContainer, &removedChild);
			}

			m_lockSource--;
		}

		Fire_doneParsingDOM();
	}
#endif
}

Web::Node* FindDOMNodeFromBookmark(Web::Node* node, long offset, long length)
{
	ASSERT(0);
#if 0
	long offset0, offset2;

	node->getTextOffset(0, &offset0);
	node->getTextOffset(2, &offset2);

	if (offset == offset0 && length == offset2-offset0)
		return node;

	CComPtr<Web::Node> child;
	node->get_firstChild(&child);
	while (child)
	{
		Web::Node* fNode = FindDOMNodeFromBookmark(child, offset, length);
		if (fNode)
			return fNode;

		CComPtr<Web::Node> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
#endif
	return NULL;
}

void CEXMLDocument::TextHasChangedReparseDOM()
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComPtr<ITextData> textData;
	get_textData(&textData);

	if (m_lockDOM == 0)
//	if (m_bSourceEditLast == FALSE)
	{
		if (m_bSourceEditLast == false)
		{
		}

		m_bSourceEditLast = true;

		ClearErrors();

		m_lockSource++;

		{
			// TODO, had this
#if 0
			for (int i = 0; i < m_viewGroups.GetSize(); i++)
			{
				CWebXMLViewGroup* pViewGroup = m_viewGroups[i];

				pViewGroup->DeselectAll();

				CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = pViewGroup->m_layoutView->m_spUnknown;
				if (htmlActiveDoc)
				{
					htmlActiveDoc->SetElement(NULL);
				}
			}
#endif
		}
#if 0
		m_pTree->Release();
		m_pTree = NULL;
#endif

		BSTR btext;
		textData->get_data(&btext);

		VARIANT_BOOL bsuccess;
		xmldocument->loadXML(btext, &bsuccess);

		AddRenderBehavior();

#if 0	// Had this
		{
			for (int i = 0; i < m_viewGroups.GetSize(); i++)
			{
				CWebXMLViewGroup* pViewGroup = m_viewGroups[i];

				long offset, length;
				pViewGroup->m_outerElementTextBookmark->get_offset(&offset);
				pViewGroup->m_outerElementTextBookmark->get_length(&length);

				pViewGroup->m_outerElement = FindDOMNodeFromBookmark(xmldocument, offset, length);

				CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = pViewGroup->m_layoutView->m_spUnknown;
				if (htmlActiveDoc)
				{
					htmlActiveDoc->SetElement(pViewGroup->m_outerElement);
				}
			}
		}
#endif
#if 0
		InitTree();
#endif

		m_lockSource--;

		Fire_doneParsingDOM();
	}
#endif
}

// TODO, is this called??
void CEXMLDocument::UpdateSourceFromDOM()
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComPtr<ITextData> textData;
	get_textData(&textData);

// Update source text
	if (m_lockSource == 0)
	{
		m_lockDOM++;

		BSTR bxml;
		{
			DWORD n0 = GetTickCount();
			xmldocument->MakeFormattedString(NULL, &bxml);
			DWORD n1 = GetTickCount();

			ATLTRACE("saveXML/time: %ld\n", n1-n0);
		}

		//CComQIPtr<ITextDocument> textDocument;
		//get_textDocument(&textDocument);
		{
			textData->put_data(bxml);
		}

		m_lockDOM--;
	}
#endif
}

Element* CEXMLDocument::GetEElementFromDOMElement(Web::Element *domElement)
{
	if (domElement == NULL) throw -1;

	/*
	CComPtr<IUnknown> data;
	domElement->getUserData(L"E", &data);
	if (data == NULL)
	{
	}

	CreateElement

	CComQIPtr<IEElement> eElement = data;
	*/

	ASSERT(0);
	return NULL;
#if 0
	CComQIPtr<IEElement> eElement = CreateElement(domElement);

	return eElement;
#endif
}

Web::Document * CEXMLDocument::get_DOMDocument()
{
	return m_document;
}

ErrorCode CEXMLDocument::get_undoManager(IUndoManager **pVal)
{
	*pVal = m_undoManager;
	return Success;
}

#if 0
_bstr_t CEXMLDocument::GetTargetElementsXML()
{
	ASSERT(0);
//	_bstr_t strdata = L"<svg>";

	_bstr_t strdata = L"";

#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CElement* pElement = m_targetElements[i];

		CComQIPtr<IDOMElement> element = pElement->m_domElement;

		BSTR bxml;
		element->get_xml(&bxml);
		_bstr_t xml = _bstr_t(bxml, false);

		strdata += xml;
	}

//	strdata += L"</svg>";
#endif

	return strdata;
}

void CEXMLDocument::CopyTargetElementsToClipboard()
{
	_bstr_t strdata = GetTargetElementsXML();

	if (OpenClipboard(NULL))
	{
		EmptyClipboard();
		HGLOBAL hData = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, strdata.length()*2+2);

		BSTR p = (BSTR)GlobalLock(hData);
		CopyMemory(p, (BSTR)strdata, strdata.length()*2+2);

		SetClipboardData(CF_UNICODETEXT, hData);
		GlobalUnlock(hData);
	}
}

void CEXMLDocument::InsertSVGFragment(CComQIPtr<ILSVGDocument> xmldoc, CComQIPtr<Web::Node> parentNode, CComQIPtr<Web::Node> beforeNode)
{
	CComQIPtr<Web::Element> documentElement;
	xmldoc->get_documentElement(&documentElement);

	CComQIPtr<Web::Node> child;
	documentElement->get_firstChild(&child);
	while (child != NULL)
	{
		CComQIPtr<Web::Node> nextSibling;
		child->get_nextSibling(&nextSibling);

		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			if (beforeNode == NULL)
			{
				parentNode->appendChild(child, NULL);
			}
			else
			{
				parentNode->insertBefore(child, _variant_t(beforeNode), NULL);
			}
		}

		child = nextSibling;
	}
}

/*
void CEXMLDocument::DeleteTargetElements()
{
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CElement* pElement = (CElement*)m_targetElements[i];

		CComQIPtr<IDOMNode> parentNode;
		pElement->m_domElement->get_parentNode(&parentNode);
		ASSERT(parentNode);

		parentNode->removeChild(pElement->m_domElement, NULL);
	}
}
*/

Web::Node* GetElementFromUniqID(Web::Node* parent, GUID& guid);

//ErrorCode CEXMLDocument::GetElementFromGUID(GUID& guid, IEElement* *pVal)
	IEElement/*CElementImpl*/ * CEXMLDocument::GetElementFromGUID(GUID& guid)
{
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComQIPtr<Web::Element> documentElement;
	xmldocument->get_documentElement(&documentElement);

	Web::Node* node = GetElementFromUniqID(documentElement, guid);
	if (node)
	{
		CComQIPtr<Web::Element> element = node;

		CComPtr<IEElement> eElement;
		GetEElementFromDOMElement(element, &eElement);
		return eElement;
		//return m_pTree->FindDOMElement(node);
	}
	else
		return NULL;
}

#if 0
void CEXMLDocument::UpdateFrameTitles()
{
	for (int i = 0; i < m_viewGroups.GetSize(); i++)
	{
		CEXMLViewGroup* pViewGroup = (CEXMLViewGroup*)m_viewGroups[i];
		pViewGroup->UpdateFrameTitle();
	}
}
#endif

ErrorCode CEXMLDocument::Modify()
{
	m_modified++;

	if (m_modified == 1)	// Changed from not modified to modified
		UpdateTitles();

	return Success;
}
#endif

ErrorCode CEXMLDocument::Activate()
{
#if 0
	gApp->m_frame->MDIActivate(((CWebXMLViewGroup*)m_viewGroups[0])->m_hWnd);
#endif
	return Success;
}

#if 0
/*
ErrorCode CEXMLDocument::GetDocumentsClass(IDocumentsClass **pVal)
{
	ASSERT(pVal);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_documentClass;
	if (*pVal) (*pVal)->AddRef();
	return Success;
}
*/

// IHlinkSite
ErrorCode CEXMLDocument::QueryService(DWORD dwSiteData, REFGUID guidService,
	REFIID riid, IUnknown __RPC_FAR *__RPC_FAR *ppiunk)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::GetMoniker(DWORD dwSiteData, DWORD dwAssign,
	DWORD dwWhich, IMoniker __RPC_FAR *__RPC_FAR *ppimk)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::ReadyToNavigate(DWORD dwSiteData, DWORD dwReserved)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::OnNavigationComplete(DWORD dwSiteData, DWORD dwreserved,
	ErrorCode hrError, LPCWSTR pwzError)
{
	return E_NOTIMPL;
}

// IHlinkTarget
ErrorCode CEXMLDocument::SetBrowseContext(IHlinkBrowseContext* pihlbc)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::GetBrowseContext(IHlinkBrowseContext** ppihlbc)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::Navigate(DWORD grfHLNF, LPCWSTR pwzJumpLocation)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::GetMoniker(LPCWSTR pwzLocation, DWORD dwAssign, IMoniker** ppimkLocation)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLDocument::GetFriendlyName(LPCWSTR pwzLocation, LPWSTR* ppwzFriendlyName)
{
	return E_NOTIMPL;
}

// IOleDocumentSite
ErrorCode STDMETHODCALLTYPE CEXMLDocument::ActivateMe(/* [in] */ IOleDocumentView __RPC_FAR *pView)
{
	ASSERT(0);
#if 0
	m_layoutView
	CComQIPtr<IOleDocumentSite> docSite = m_document;
	return docSite->ActivateMe(pView);
#endif
	return E_FAIL;
}

BEGIN_CMD_MAP(CEXMLDocument)
// File
	CMD_HANDLER(ID_FILE_SAVE, OnFileSave)
	CMD_HANDLER(ID_FILE_SAVE_AS, OnFileSaveAs)
	CMD_HANDLER(ID_FILE_RELOAD, OnFileReload)

// Edit
	CMD_HANDLER(ID_EDIT_UNDO, OnEditUndo)
	CMD_UPDATE(ID_EDIT_UNDO, OnEditUndoUpdate)
	CMD_HANDLER(ID_EDIT_REDO, OnEditRedo)
	CMD_UPDATE(ID_EDIT_REDO, OnEditRedoUpdate)

	CMD_HANDLER(ID_EDIT_XPATHQUERY, OnXPathQuery)

// DocType

	CMD_HANDLER(ID_DTDSCHEMA_DOCTYPEDTD_SVG11, OnDocTypeSVG11)

// View
//	CMD_HANDLER(ID_VIEW_CSSEDITOR, OnViewCSSEditor)
	//CMD_HANDLER(&ID_VIEW_PREVIEW, OnViewPreview)

// XSL
	CMD_HANDLER(ID_XSL_ASSIGNXSL, OnAssignXSL)
	CMD_HANDLER(ID_XSL_GOTOXSL, OnGotoXSL)
	CMD_UPDATE(ID_XSL_GOTOXSL, OnGotoXSLUpdate)

// SMIL
	CMD_HANDLER(ID_SMILLAYOUTS_NEWTOPLAYOUT, OnSMILNewTopLayout)

END_CMD_MAP()

LRESULT CEXMLDocument::OnDocTypeSVG11(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> document;
//	m_document->GetDocument(&document);
	document = m_document;

	CComPtr<ILDOMImplementation> impl;
	document->get_implementation(&impl);

	CComPtr<ILDOMDocumentType> doctype;
	impl->createDocumentType(L"svg", L"-//W3C//DTD SVG 1.1//EN", L"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd", &doctype);

	CComPtr<Web::Node> p;
	document->adoptNode(doctype, &p);	// Set the doctype's ownerDocument

	CComPtr<ILDOMDocumentType> olddoctype;
	document->get_doctype(&olddoctype);

	if (olddoctype)
	{
		document->replaceChild(doctype, olddoctype, NULL);
	}
	else
	{
		CComPtr<Web::Node> firstChild;
		document->get_firstChild(&firstChild);

		document->insertBefore(doctype, _variant_t(firstChild), NULL);
	}

	return 0;
}

LRESULT CEXMLDocument::OnFileReload(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; m_viewGroups.GetSize(); i++)
	{
		CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroups[i]);

		for (int j = 0; j < pViewGroup->m_views.GetSize(); j++)
		{
		}
	}

#if 0
	m_xmldocument.Release();
	m_textDocument.Release();

	{
		ErrorCode hr;

		hr = LoadDocument(m_pathName);

		if (FAILED(hr))
			return hr;

		Prepare();

		hr = CreateXMLDocumentFromTextData();

		Fire_doneParsingDOM();
	}
#endif
	return 0;
}

LRESULT CEXMLDocument::OnXPathQuery(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CXPathQueryDlg dlg;
	dlg.m_document = this;

	dlg.DoModal();

	return 0;
}

LRESULT CEXMLDocument::OnSMILNewTopLayout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComQIPtr<ILSMILDocument> smildocument = xmldocument;
	if (smildocument)
	{
		CComPtr<Web::Element> topLayout;
		smildocument->createElement(L"topLayout", &topLayout);
		if (topLayout)
		{
			CComPtr<Web::Element> documentElement;
			smildocument->get_documentElement(&documentElement);

			if (documentElement)
			{
				CComPtr<Web::Element> head = GetElementByTagName(documentElement, L"head", FALSE);
				if (head == NULL)
				{
				}

				CComPtr<Web::Element> layout = GetElementByTagName(head, L"layout", FALSE);
				if (layout == NULL)
				{
				}

				layout->appendChild(topLayout, NULL);
			}
		}
	}

	return 0;
}

class CAttr
{
public:
	_bstr_t m_name;
	_bstr_t m_value;
};

class CAttributes
{
public:
	CArray<CAttr*,CAttr*> m_items;

	~CAttributes()
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			delete m_items[i];
		}
		m_items.RemoveAll();
	}

	CAttr* GetAttr(BSTR name)
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (!wcscmp(m_items[i]->m_name, name))
			{
				return m_items[i];
			}
		}

		return NULL;
	}

	_bstr_t GetAttrValue(BSTR name)
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (!wcscmp(m_items[i]->m_name, name))
			{
				return m_items[i]->m_value;
			}
		}

		return _bstr_t(L"");
	}
};

BOOL ParseAttributes(BSTR bstr, CAttributes* attributes)
{
	WCHAR* p = bstr;
	while (*p)
	{
		while (iswspace(*p)) p++;

		CWCharString name;

		while (iswalnum(*p))
		{
			name += *p;
			p++;
		}

		while (iswspace(*p)) p++;

		if (*p != L'=') break;
		p++;

		while (iswspace(*p)) p++;

		CWCharString value;

		WCHAR delimiter = *p++;
		if (delimiter != L'\'' && delimiter != L'"')
			break;

		while (*p)
		{
			if (*p == delimiter)
			{
				break;
			}

			value += *p;
			p++;
		}

		if (*p != delimiter) break;
		p++;

		CAttr* pAttr = new CAttr;
		pAttr->m_name = name;
		pAttr->m_value = value;

		attributes->m_items.Add(pAttr);
	}

	return TRUE;
}

ErrorCode CEXMLDocument::GetXSLProcessingInstruction(ILDOMProcessingInstruction** pVal)
{
	ASSERT(pVal);
	if (pVal == NULL) return E_POINTER;

	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComPtr<Web::Node> node;
	xmldocument->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMProcessingInstruction> pi = node;
		if (pi)
		{
			BSTR btarget;
			pi->get_target(&btarget);
			_bstr_t target = _bstr_t(btarget, false);

			if (!wcscmp(target, L"stylesheet"))
			{
				(*pVal = pi)->AddRef();
				return Success;
			}
		}

		CComPtr<Web::Node> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	*pVal = NULL;
	return Success;
};

LRESULT CEXMLDocument::OnGotoXSL(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMProcessingInstruction> pi;
	GetXSLProcessingInstruction(&pi);
	if (pi)
	{
		BSTR bdata;
		pi->get_data(&bdata);

		CAttributes attributes;
		ParseAttributes(bdata, &attributes);

		_bstr_t filepath = attributes.GetAttrValue(L"href");

		VARIANT_BOOL bsuccess;
		ASSERT(0);
#if 0
		gApp->OpenDocument(filepath, &bsuccess);
#endif

		SysFreeString(bdata);
	}

	return 0;
}

void CEXMLDocument::OnGotoXSLUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	CComPtr<ILDOMProcessingInstruction> pi;
	GetXSLProcessingInstruction(&pi);
	if (pi)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CEXMLDocument::OnAssignXSL(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CAssignXSLDlg dlg;

	CComPtr<ILDOMProcessingInstruction> pi;
	GetXSLProcessingInstruction(&pi);
	if (pi)
	{
		CComBSTR data;
		pi->get_data(&data);

		CAttributes attributes;
		ParseAttributes(data, &attributes);

		dlg.m_filepath = attributes.GetAttrValue(L"href");
	}

	if (dlg.DoModal() == IDOK)
	{
		WCHAR data[4096];
		swprintf(data, L"type=\"text/xsl\" href=\"%s\"", (BSTR)dlg.m_filepath);

		if (pi == NULL)
		{
			xmldocument->createProcessingInstruction(L"stylesheet", data, &pi);

			CComPtr<Web::Node> firstChild;
			xmldocument->get_firstChild(&firstChild);
			xmldocument->insertBefore(pi, _variant_t(firstChild), NULL);
		}
		else
		{
			pi->put_data(data);
		}

		Modify();
	}

	return 0;
}

#if 0
LRESULT CEXMLDocument::OnViewCSSEditor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComQIPtr<ILDocumentStyle> documentStyle = xmldocument;
	if (documentStyle)
	{
		CComPtr<ILStyleSheetList> styleSheetList;
		documentStyle->get_styleSheets(&styleSheetList);

		CComObject<CUIMDIChild>* child;
		CComObject<CUIMDIChild>::CreateInstance(&child);
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		{
			CComObject<CCSSStyleSheetView>* cssView;
			CComObject<CCSSStyleSheetView>::CreateInstance(&cssView);
			if (cssView)
			{
				gApp->m_frame->FindMenu(IDR_CSSSTYLESHEETVIEW, &cssView->m_menu);
				cssView->m_styleSheetList = styleSheetList;
				child->AddPage(cssView, NULL);
			}
		}

		child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
	}

	return 0;
}
#endif

LRESULT CEXMLDocument::OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pathName.length())
	{
		ErrorCode hr = SaveDocument(m_pathName);
		if (FAILED(hr))
		{
			MessageBox(NULL/*TODO: GetMainHwnd()*/, "Couldn't Save file", "LXMLEditor", MB_OK);
		}
	}
	else
	{
		OnFileSaveAs(wNotifyCode, wID, hWndCtl, bHandled);
	}

	return 0;
}

LRESULT CEXMLDocument::OnFileSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	ASSERT(0);
#if 0
	CComQIPtr<ILXAddin> addin = m_app;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> frame;
	addinSite->GetFrame(&frame);

	CComQIPtr<IUIWnd> wnd = frame;
	HWND hWnd;
	wnd->get_hwnd(&hWnd);

//	BSTR pathName;
//	m_webDocument->get_filePath(&pathName);

	TCHAR username[1024];
	TCHAR password[1024];
	TCHAR server[1024];
	TCHAR urlpath[1024];

	URL_COMPONENTS url_components = {0};
	url_components.dwStructSize = sizeof(url_components);
	//url_components.nScheme = INTERNET_SCHEME_FTP;
	//url_components.nPort = m_nPort;
	url_components.lpszUserName = username;
	url_components.dwUserNameLength = _countof(username);
	url_components.lpszPassword = password;
	url_components.dwPasswordLength = _countof(password);
	url_components.lpszHostName = server;
	url_components.dwHostNameLength = _countof(server);
	url_components.lpszUrlPath = urlpath;
	url_components.dwUrlPathLength = _countof(urlpath);

	InternetCrackUrl(m_pathName, m_pathName.length(), ICU_DECODE | ICU_ESCAPE, &url_components);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, urlpath);	// Initial filename

//	TCHAR curdir[MAX_PATH];
//	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = sizeof(OPENFILENAME_NT4A);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | /*OFN_PATHMUSTEXIST |*/ OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = _countof(sbuffer);
//	ofn.lpstrInitialDir = curdir;
//	ofn.lpstrFilter = FilesFilter;
//	ofn.nFilterIndex = 2;
	
	if (::GetSaveFileName(&ofn))
	{
		ErrorCode hr = SaveDocument(A2W(sbuffer));
		if (SUCCEEDED(hr))
		{
			UpdateTitles();
			/*
			for (int i = 0; i < m_viewGroups.GetSize(); i++)
			{
				m_viewGroups[i]->UpdateFrameTitle();
			}
			*/
		}
		else
		{
			MessageBox(hWnd, "Couldn't Save file", "LXMLEditor", MB_OK);
		}
	}
#endif

	return 0;
}

LRESULT CEXMLDocument::OnViewPreview(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	if (FALSE)
	{
		BYTE connstr[1024];

		SQLHENV henv;
		SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

		SQLHDBC hdbc;
		SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
		
		SQLSMALLINT connstrlength;
		SQLRETURN result = SQLDriverConnect(hdbc, GetDesktopWindow(), (LPBYTE)"", 0, connstr, 1024, &connstrlength, SQL_DRIVER_PROMPT);

	}
	else
	{
		CComQIPtr<IWebEditorFrame> frame;
		gApp->get_frame(&frame);

		CComQIPtr<IUIContextManager> uiManager;
		gApp->get_uiManager(&uiManager);

		CComQIPtr<ITextDocument> textDocument;
		get_textDocument(&textDocument);

		BSTR textdata;
		textDocument->get_data(&textdata);

		BOOL success;

	// Create a copy document (TODO, must optimize this)
		CComQIPtr<ITextDocument> textDocCopy;
		textDocCopy.CoCreateInstance(CLSID_TextDocument);
		textDocCopy->put_data(SysAllocString(textdata));

		CComQIPtr<IDOMDocumentContainer> documentContainerCopy;
		documentContainerCopy.CoCreateInstance(CLSID_DOMDocumentContainer);
		documentContainerCopy->put_sourceTextDoc(textDocCopy);
	//	documentContainerCopy->parse(&success);
	//	documentContainerCopy->put_sourceTextDoc(NULL);

		if (success)
		{
			CComQIPtr<IUIMDIChild> child;
			child.CoCreateInstance(CLSID_UIMDIChild);

			CComQIPtr<IWebPreviewView> previewView;
			previewView.CoCreateInstance(CLSID_WebPreviewView);
			previewView->Create(uiManager, L"Preview", (IID*)&CLSID_SvgLayoutView, NULL);
			previewView->put_documentContainer(documentContainerCopy);
			child->AddView(previewView, NULL);

//			child->CreateMDIChild(frame, NULL);
//			child.Detach();
		}
	}
#endif
	return 0;
}

LRESULT CEXMLDocument::OnEditUndo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_undoManager->UndoTo(NULL);
	return 0;
}

LRESULT CEXMLDocument::OnEditRedo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_undoManager->RedoTo(NULL);
	return 0;
}

void CEXMLDocument::OnEditUndoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	BSTR bdescription;
	ErrorCode hr = m_undoManager->GetLastUndoDescription(&bdescription);
	if (hr == Success)
	{
		bEnable = TRUE;
		pCmdUI->SetText(bdescription);
		SysFreeString(bdescription);
	}
	else
	{
		pCmdUI->SetText(L"Can't Undo");
	}

	pCmdUI->Enable(bEnable);
}

void CEXMLDocument::OnEditRedoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	BSTR bdescription;
	ErrorCode hr = m_undoManager->GetLastRedoDescription(&bdescription);
	if (hr == Success)
	{
		bEnable = TRUE;
		pCmdUI->SetText(bdescription);
		SysFreeString(bdescription);
	}
	else
	{
		pCmdUI->SetText(L"Can't Redo");
	}

	pCmdUI->Enable(bEnable);
}
#endif

CEXMLViewGroup* CEXMLDocument::GetActiveViewGroup()
{
	ASSERT(0);
	return NULL;
#if 0
// TODO ??
	CComQIPtr<IUIActiveManager> uiManager = m_app;

	CComPtr<IEXMLViewGroup> activeViewGroup;
	uiManager->GetActiveObjects(IID_IEXMLViewGroup, (IUnknown**)&activeViewGroup, 1, NULL);

	*pVal = activeViewGroup;
	if (*pVal) (*pVal)->AddRef();
#endif
}

ITextData* CEXMLDocument::get_textData()
{
	return m_textData;
}

DocumentType* CEXMLDocument::get_doctype()
{
	return NULL;
}

Comment* CEXMLDocument::createComment(System::StringW* data)
{
	Comment* p = new Comment;
	p->m_data = data;
	p->set_ownerDocument(this);
	return p;
}

Text* CEXMLDocument::createTextNode(System::StringW* data)
{
	Text* p = new Text;
	p->m_data = data;
	p->set_ownerDocument(this);
	return p;
}

CDATASection* CEXMLDocument::createCDATASection(System::StringW* data)
{
	CDATASection* p = new CDATASection;
	p->m_data = data;
	p->set_ownerDocument(this);
	return p;
}

ProcessingInstruction* CEXMLDocument::createProcessingInstruction(System::StringW* target, System::StringW* data)
{
	return NULL;
}

EntityReference* CEXMLDocument::createEntityReference(System::StringW* name)
{
	return NULL;
}

Attr* CEXMLDocument::createAttributeNS(System::StringW* namespaceURI, System::StringW* qualifiedName)
{
	Attr* p = new Attr;
	int ncolon = qualifiedName->Find(':');
	if (ncolon != -1)
	{
		p->m_prefix = new System::StringW(true, qualifiedName->c_str(), ncolon);
		p->m_localName = new System::StringW(string_copy(qualifiedName->c_str() + ncolon+1, qualifiedName->Length() - ncolon - 1));
	}
	else
	{
		p->m_localName = qualifiedName;
	}

	p->set_ownerDocument(this);

	return p;
}

Element* CEXMLDocument::createElementNS(System::StringW* namespaceURI, System::StringW* qualifiedName)
{
	Element* pElement;

	pElement = new CEElement;
	pElement->m_namespaceURI = namespaceURI;
	pElement->m_localName = qualifiedName;	// TODO

	pElement->set_ownerDocument(this);

	return pElement;
}

}	// LXmlEdit
}
