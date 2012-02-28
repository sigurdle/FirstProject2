#ifndef Web_Stylesheet_h
#define Web_Stylesheet_h

namespace System
{
namespace Web
{

//class Node;
//class ProcessingInstructionStylesheet;

	/*
class HTMLLinkElement;

class MediaList;
class LinkStyleExternalImpl;
*/

#if 0
interface IStyleSheetOwner
{
};

class CSSEXT StyleSheet : public Object
{
public:
	CTOR StyleSheet(IStyleSheetOwner* ownerNode);
	~StyleSheet();

	virtual String get_title() const;
	virtual void set_title(StringIn newVal);

	virtual String get_href() const;
	virtual String get_type() const;

	StyleSheet* get_parentStyleSheet();
	IStyleSheetOwner* get_ownerNode();
	bool get_disabled() const;
	MediaList* get_media();

protected:

	/*
	friend class LinkStyleExternalImpl;
	friend class ProcessingInstructionStylesheet;
	friend class HTMLLinkElement;
*/

	StyleSheet* m_parentStyleSheet;
	Web::IStyleSheetOwner* m_ownerNode;
	MediaList* m_media;
	String m_href;
	bool m_disabled;
};
#endif

}	// Web
}

#endif	// Web_Stylesheet_h
