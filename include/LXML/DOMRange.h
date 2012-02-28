#ifndef Web_DOMRange_h
#define Web_DOMRange_h

namespace System
{
namespace Web
{

class DocumentRangeImplImpl;

class WEBEXT Range : public Object,
	protected CNotifySendImpl<Range>
{
public:
	CTOR Range();
	~Range();

	void insertNode(Node* node);
	void surroundContents(Node* newParent);
	DocumentFragment* cloneContents() const;
	DocumentFragment* extractContents();
	void detach();
	String toString();
	Range* cloneRange() const;
	void deleteContents();
	void selectNodeContents(Node* refNode);
	void selectNode(Node* refNode);
	void collapse(bool toStart);
	void setEndAfter(Node* refNode);
	void setEndBefore(Node* refNode);
	void setStartAfter(Node* refNode);
	void setStartBefore(Node* refNode);
	void setEnd(Node* refNode, int offset);
	void setStart(Node* refNode, int offset);
	Node* get_commonAncestorContainer() const;
	bool get_collapsed() const;
	int get_endOffset() const;
	Node* get_endContainer() const;
	int get_startOffset() const;
	Node* get_startContainer() const;

	DocumentRangeImplImpl* m_pDocumentRange;

protected:

	bool extract2(Node* node, Node* parent, int& hitStart);
	void delete2(Node* node, int& hitStart, int& hitEnd);

	Node* m_commonAncestorContainer;
	Node* m_startContainer;
	Node* m_endContainer;
	int m_startOffset;
	int m_endOffset;
	bool m_startIsDeeperThanEnd;

	friend class CharacterData;
};

}	// Web
}	// System

#endif // Web_DOMRange_h
