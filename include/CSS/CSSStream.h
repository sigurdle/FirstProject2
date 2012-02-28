#ifndef Web_CSSStream_h
#define Web_CSSStream_h

namespace System
{
namespace Style
{

class CSSEXT CSSStream
{
public:
	CTOR CSSStream()
	{
	}

	CTOR CSSStream(IO::TextReader* stream);
	CTOR CSSStream(StringIn str);

	void Parse(IStyleSheet* stylesheet);

	void ParsePropertyList(IStyleDeclaration* declaration);
	void ParseDeclaration(IStyleDeclaration* declaration);
	void ParseStyleRule();
	void ParseRules();
	void ParseRule();

	SimpleSelector* ParseSingleSelector();
	SimpleSelectorSequence* ParseSingleSelectorSequence();
	Selector* ParseSelector();
	SelectorList* ParseSelectorList();

	bool eof();
	void getnextc();

protected:

	void EatChar(int c);
	void SkipSpaces();
	void SkipSpacesComments();

	String GetID();
	String GetString();
	void GetNSName(String& prefix, String& name);

	_Ptr<IO::TextReader> m_data;
	IStyleSheet* m_styleSheet;

	int m_c;

//	const WCHAR* m_ppos;
	int m_ipos;

//	String::iterator<WCHAR> m_data;
};

}	// Web
}

#endif // Web_CSSStream_h
