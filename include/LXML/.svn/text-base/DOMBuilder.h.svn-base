#ifndef __LSPARSER_H__
#define __LSPARSER_H__

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class LSParser : public System::Object
//	public ILLSParser
{
public:
	CTOR LSParser()
	{
	}

	IDOMErrorHandler* m_errorHandler;

// IDOMBuilder
public:
	IDOMErrorHandler* get_errorHandler();
	void set_errorHandler(IDOMErrorHandler* newVal);
#if 0
	STDMETHOD(parseTextData)(/*[in]*/ ITextData* textData, /*[out,retval]*/ Document* *pVal);
#endif
#if 0
	STDMETHOD(parseASURI)(/*[in]*/ BSTR uri, /*[in]*/ BSTR schemaType, /*[out,retval]*/ IASModel* *pVal);
#endif
	ErrorCode parseURI(StringIn uri, /*[out,retval]*/ Document* *pVal);
};

}	// w3c
}

#endif // __LSPARSER_H__
