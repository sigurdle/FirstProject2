#ifndef __DOCUMENTPARSER_H_
#define __DOCUMENTPARSER_H_

namespace System
{
namespace Web
{

class WEBEXT DocumentParser
{
public:
	DocumentParser();

	bool m_utf8;

	long m_fpos;
	long m_line;
	long m_column;
//	int m_oldc;


	//bool m_bXML;

// Retrieved from TextData
	/*
	long m_textLen;
	const OLECHAR* m_textData;
	*/

#if 0
	IGetByte* m_stream;
#endif
	_Ptr<IO::TextReader> m_stream;

	wchar_t m_oldc[256];
	int m_stacked;

	bool m_bEOF;

// In order to be able to know when we've reached end of stream, we must read one byte
// ahead

	uint8 m_nextByte;

	int readbyte();

	bool eof();

	int getcnext();

	void ungetcnext();
};

}	// Web
}

#endif // __DOCUMENTPARSER_H_
