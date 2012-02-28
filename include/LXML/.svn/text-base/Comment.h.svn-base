#ifndef w3c_Comment_h
#define w3c_Comment_h

namespace System
{
namespace Web
{

class WEBEXT Comment : public CharacterData
{
public:
	CTOR Comment();

	NodeType get_nodeType() const;
	String get_nodeName() const;

	Node* cloneNodeExport(Document* ownerDocument, bool deep) const;

protected:

	static ImmutableString<wchar_t> s_nodeName;
};

}	// w3c
}

#endif // w3c_Comment_h
