#ifndef w3c_Text_h
#define w3c_Text_h

namespace System
{
namespace Web
{

class WEBEXT Text : public CharacterData
{
public:
	CTOR Text();

	Text* splitText(int offset);
	String get_wholeText()
	{
		ASSERT(0);
		return nullptr;
	}

	NodeType get_nodeType() const;
	String get_nodeName() const;

	Node* cloneNodeExport(Document* ownerDocument, bool deep) const;

private:

	static ImmutableString<wchar_t> s_nodeName;

	friend class PText;
};

}	// w3c
}

#endif // w3c_Text_h
