#ifndef __DTDPARSER_H
#define __DTDPARSER_H

namespace System
{
namespace Web
{

class DTDDocument;
class CEntity;
class CLDTDElement;
class CNotation;
class CAttlist;

class CDTDParser;
class CDTDContentModel;
class CLDOMComment;

class CCP
{
public:
	CDTDParser* m_pDTDDocument;

	int m_type;

	CTOR CCP()
	{
		m_pDTDDocument = NULL;
		m_type = 0;
	}

	virtual CDTDContentModel* BuildCM()
	{
		return NULL;
	}
};

class CCPElement : public CCP
{
public:
	System::StringW* m_ns;
	System::StringW* m_name;

	CTOR CCPElement()
	{
		m_type = 1;
	}

	virtual CDTDContentModel* BuildCM()
	{
		return NULL;
	}
};

class CCPChoiceSeq : public CCP
{
public:
	vector<CCP*> m_children;
	int m_minOccurs;
	int m_maxOccurs;
	ASContentModelTypeOp m_listOperator;

	CTOR CCPChoiceSeq()
	{
		m_type = 2;
		m_minOccurs = 1;
		m_maxOccurs = 1;
		m_listOperator = (ASContentModelTypeOp)-1;
	}

	virtual CDTDContentModel* BuildCM()
	{
		return NULL;
	}
};

class CDTDParser
{
public:
	CTOR CDTDParser()
	{
#if 0
		m_document = NULL;
		m_parentNode = NULL;
#endif
		m_dtdDocument = NULL;

		m_eof = 0;//EOF;
		m_textData = NULL;
	}

	System::StringW* m_url;

//	CComQIPtr<ITextData> m_textDoc;
	const OLECHAR* m_textData;
	int m_textLen;
	IDOMErrorHandler* m_errorHandler;

	DTDDocument* m_dtdDocument;
#if 0
	Document* m_document;
	Node* m_parentNode;
#endif

	long m_line;
	long m_column;
	long m_fpos;

	int m_eof;

	int m_efpos;
	CEntity* m_pInsideEntity;

	bool eof();

	int _getcnext();
	void _ungetcnext();

	int getcnext();
	void ungetcnext();

	int getcnext_noexpand();

	System::StringW* GetID();
	void GetNSID(System::StringW* ns, System::StringW* id);
	void SkipSpaces();
	System::StringW* GetString();
	void EatChar(int c);

	void ParseElementContentSpec(CLDTDElement* pElement);
	CCPChoiceSeq* ParseChoiceSeq();
	CCP* ParseCP();

	void ExtSubsetDecl();

	void ParseEntity(CEntity* pEntity);
	void ParseNotation(CNotation* pNotation);
	void ParseElement(CLDTDElement* pElement);
	void ParseAttlist(CAttlist* pAttlist);
	void ParseComment(CLDOMComment* pComment);
	void IgnoreSectContents();
	void IncludeSect();

	IDOMLocator* GetCurrentLocation();

	bool handleError(IDOMError* error)
	{
		if (m_errorHandler)
		{
			bool bContinue = m_errorHandler->handleError(error);
			return bContinue;
		}

		ASSERT(0);
		return false;
	}

//	void LoadDocument(BSTR pathName);
	ErrorCode Parse();
	ErrorCode Parse2();

	ErrorCode loadURL(System::StringW* url);

//	STDMETHOD(parseTextData)(/*[in]*/ ITextData* textData, /*[out,retval]*/ bool* pVal);
//	STDMETHOD(get_errorHandler)(/*[out, retval]*/ ILDOMErrorHandler* *pVal);
//	STDMETHOD(put_errorHandler)(/*[in]*/ ILDOMErrorHandler* newVal);
};

}	// Web
}

#endif
